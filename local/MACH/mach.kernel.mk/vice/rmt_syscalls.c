/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	rmt_syscalls.c,v $
 * Revision 2.8  89/03/09  22:45:48  rpd
 * 	More cleanup.
 * 
 * Revision 2.7  89/02/26  11:14:19  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.6  89/02/07  22:55:29  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.5  88/08/22  21:37:04  mja
 * 	Change to return EOPNOTSUPP for unexpected system call numbers (e.g.
 * 	xutimes()) rather than causing a panic();  CS_RFS => CMUCS_RFS.
 * 	[88/08/09  10:00:55  mja]
 * 	
 * 	Update rmt_namei() to make fsfull() check before returning so
 * 	that the common resource pause handling will trigerr for things
 * 	like open() and the like;  flush test RT_fsync alternative and
 * 	make RT_tryclose the default for the retriable close operation.
 * 	[88/08/08  18:05:24  mja]
 * 
 * Revision 2.4  88/07/15  16:20:01  mja
 * Fix to avoid clobbering u.u_error during resource pause check
 * in rmt_close() since things like execv() call us with an error
 * pending;  pre-close => try-close and correct to retry on any
 * error return from Venus.
 * 
 * 12-May-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Integrated fix by Bob Baron for new Vice pioctl() position.
 *	[ V5.1(XF24) ]
 *
 * 21-Apr-88  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added support for recoverable "try-close" operation;  fixed to
 *	record trailing component of program name during exec;  fixed
 *	bug which neglected to apply umask to new directory modes;
 *	fixed incorrect panic format bug in rmt_fdes(); changed to
 *	allocate/deallocate fs structure on mount/unmount to hold the
 *	file system name for resource pauses.
 *	[ V5.1(XF23) ]
 *
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Removed more lint.
 *
 *  4-Feb-88  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Applied bug fix from Jay Kistler to keep the kernel from
 *	panic-ing with an incorrect u.u_rmt_ncnt whenever renaming files
 *	using symbolic links to the local machine.  Fairly Bizzarre.
 *
 *  3-Oct-87  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Initialize "extra" in routine setpag().
 *
 * 25-Aug-87  Jay Kistler (jjk) at Carnegie Mellon University
 *	Changed manual string copy block in rmt_dual_paths() to use
 *	copystr() instead.  Added diagnostic information to be printed
 *	out when a bogus syscall number causes an RT_panic.
 *
 * 16-May-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Fixed handling of exect syscall (applicable to romp only).
 *
 * 16-Feb-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Updated rmt_syscall_map to reflect different syscall numbering
 *	among the various machine types.
 *
 *  5-Feb-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Corrected name lookup of "from" name in rmt_dual_path routine.
 *	CMUCS_RFS:  enabled "RFS namei" processing for all routines
 *	in this module.
 *
 * 30-Jan-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Changed semantics of rmt_fdes routine; previously it always
 *	returned a NULL fp, now it returns its argument fp if further
 *	local processing is required (and there were no errors).
 *	This only affects ftruncate currently.
 *
 * 26-Jan-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Removed KEEPNAMEBUF handling in "dual-path" syscalls as
 *	it turned out not to be necessary.
 *
 * 21-Jan-87  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Added code to handle core dumps in Vice.
 *
 * 22-Oct-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	Created from rfs_syscalls.c and Andrew's rmt_remote.c.
 *
 */

/*	rmt_syscalls.c	CMU	86/10/22	*/

/*
 * ITC Remote file system - kernel interface module
 */

#include <mach_rfs.h>
#include <vicefs.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/namei.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/mount.h>
#include <sys/inode.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/syslog.h>
#include <sys/vicermt.h>
#include <sys/fs.h>

#include <sys/ioctl.h>
#include <sys/viceioctl.h>

#if	MACH_RFS
/* Enable RFS namei processing by routines which call namei() in
   this module (only rmt_dual_paths()).
*/
#undef	namei
#define namei	rnamei
#endif	MACH_RFS


/*
 *  Remote file descriptor operations dispatch table.
 *
 *  This is the table used by most standard file descriptor based system calls
 *  to dispatch to the proper processing routines (below) when the descriptor
 *  type is DTYPE_VICEINO.
 */

extern int ino_rw(), rmt_ioctl_fop(), ino_select(), rmt_close_fop();
struct fileops	rmt_ops = { ino_rw, rmt_ioctl_fop, ino_select, rmt_close_fop };


/*
 *  Pseudo super-block buffers for resource pause.
 */

struct buf *rmt_fsbufp[NVICEFS] = {0};


static
u_short	rmt_syscall_map[] =
{
	RT_panic,			/*   0 = indir */
	RT_panic,			/*   1 = exit */
	RT_panic,			/*   2 = fork */
	RT_panic,			/*   3 = read */
	RT_panic,			/*   4 = write */
	RT_open,			/*   5 = open */
	RT_close,			/*   6 = close */
	RT_panic,			/*   7 = old wait */
	RT_open,			/*   8 = creat */
	RT_link,			/*   9 = link */
	RT_unlink,			/*  10 = unlink */
	RT_open,			/*  11 = execv */
	RT_chdir,			/*  12 = chdir */
	RT_panic,			/*  13 = old time */
	RT_panic,			/*  14 = mknod */
	RT_chmod,			/*  15 = chmod */
	RT_chown,			/*  16 = chown */
	RT_panic,			/*  17 = old break */
	RT_panic,			/*  18 = old stat */
	RT_panic,			/*  19 = lseek */
	RT_panic,			/*  20 = getpid */
	RT_panic,			/*  21 = mount */
	RT_panic,			/*  22 = umount */
	RT_panic,			/*  23 = old setuid */
	RT_panic,			/*  24 = getuid */
	RT_panic,			/*  25 = old stime */
	RT_panic,			/*  26 = ptrace */
	RT_panic,			/*  27 = old alarm */
	RT_panic,			/*  28 = old fstat */
	RT_panic,			/*  29 = opause */
	RT_panic,			/*  30 = old utime */
	RT_panic,			/*  31 = was stty */
	RT_panic,			/*  32 = was gtty */
	RT_access,			/*  33 = access */
	RT_panic,			/*  34 = old nice */
	RT_panic,			/*  35 = old ftime */
	RT_panic,			/*  36 = sync */
	RT_panic,			/*  37 = kill */
	RT_stat,			/*  38 = stat */
	RT_panic,			/*  39 = old setpgrp */
	RT_stat,			/*  40 = lstat */
	RT_panic,			/*  41 = dup */
	RT_panic,			/*  42 = pipe */
	RT_panic,			/*  43 = old times */
	RT_panic,			/*  44 = profil */
	RT_panic,			/*  45 = nosys */
	RT_panic,			/*  46 = old setgid */
	RT_panic,			/*  47 = getgid */
	RT_panic,			/*  48 = old sig */
	RT_panic,			/*  49 = reserved for USG */
	RT_panic,			/*  50 = reserved for USG */
	RT_panic,			/*  51 = turn acct off/on */
	RT_panic,			/*  52 = old set phys addr */
	RT_panic,			/*  53 = old lock in core */
	RT_ioctl,			/*  54 = ioctl */
	RT_panic,			/*  55 = reboot */
	RT_panic,			/*  56 = old mpxchan */
	RT_symlink,			/*  57 = symlink */
	RT_readlink,			/*  58 = readlink */
	RT_open,			/*  59 = execve */
	RT_panic,			/*  60 = umask */
	RT_chdir,			/*  61 = chroot */
	RT_panic,			/*  62 = fstat */
	RT_panic,			/*  63 = used internally */
	RT_panic,			/*  64 = getpagesize */
	RT_panic,			/*  65 = mremap */
	RT_panic,			/*  66 = vfork */
	RT_panic,			/*  67 = old vread */
	RT_panic,			/*  68 = old vwrite */
	RT_panic,			/*  69 = sbrk */
	RT_panic,			/*  70 = sstk */
	RT_panic,			/*  71 = mmap */
	RT_panic,			/*  72 = old vadvise */
	RT_panic,			/*  73 = munmap */
	RT_panic,			/*  74 = mprotect */
	RT_panic,			/*  75 = madvise */
	RT_panic,			/*  76 = vhangup */
	RT_panic,			/*  77 = old vlimit */
	RT_panic,			/*  78 = mincore */
	RT_panic,			/*  79 = getgroups */
	RT_panic,			/*  80 = setgroups */
	RT_panic,			/*  81 = getpgrp */
	RT_panic,			/*  82 = setpgrp */
	RT_panic,			/*  83 = setitimer */
	RT_panic,			/*  84 = wait */
	RT_panic,			/*  85 = swapon */
	RT_panic,			/*  86 = getitimer */
	RT_panic,			/*  87 = gethostname */
	RT_panic,			/*  88 = sethostname */
	RT_panic,			/*  89 = getdtablesize */
	RT_panic,			/*  90 = dup2 */
	RT_panic,			/*  91 = getdopt */
	RT_panic,			/*  92 = fcntl */
	RT_panic,			/*  93 = select */
	RT_panic,			/*  94 = setdopt */
	RT_fsync,			/*  95 = fsync */
	RT_panic,			/*  96 = setpriority */
	RT_panic,			/*  97 = socket */
	RT_panic,			/*  98 = connect */
	RT_panic,			/*  99 = accept */
	RT_panic,			/* 100 = getpriority */
	RT_panic,			/* 101 = send */
	RT_panic,			/* 102 = recv */
	RT_panic,			/* 103 = old socketaddr */
	RT_panic,			/* 104 = bind */
	RT_panic,			/* 105 = setsockopt */
	RT_panic,			/* 106 = listen */
	RT_panic,			/* 107 = old vtimes */
	RT_panic,			/* 108 = sigvec */
	RT_panic,			/* 109 = sigblock */
	RT_panic,			/* 110 = sigsetmask */
	RT_panic,			/* 111 = sigpause */
	RT_panic,			/* 112 = sigstack */
	RT_panic,			/* 113 = recvmsg */
	RT_panic,			/* 114 = sendmsg */
	RT_panic,			/* 115 = vtrace */
	RT_panic,			/* 116 = gettimeofday */
	RT_panic,			/* 117 = getrusage */
	RT_panic,			/* 118 = getsockopt */
	RT_panic,			/* 119 = nosys */
	RT_panic,			/* 120 = readv */
	RT_panic,			/* 121 = writev */
	RT_panic,			/* 122 = settimeofday */
	RT_fchown,			/* 123 = fchown */
	RT_fchmod,			/* 124 = fchmod */
	RT_panic,			/* 125 = recvfrom */
	RT_panic,			/* 126 = setreuid */
	RT_panic,			/* 127 = setregid */
	RT_rename,			/* 128 = rename */
	RT_truncate,			/* 129 = truncate */
	RT_ftruncate,			/* 130 = ftruncate */
	RT_flock,			/* 131 = flock */
	RT_panic,			/* 132 = nosys */
	RT_panic,			/* 133 = sendto */
	RT_panic,			/* 134 = shutdown */
	RT_panic,			/* 135 = socketpair */
	RT_mkdir,			/* 136 = mkdir */
	RT_rmdir,			/* 137 = rmdir */
	RT_utimes,			/* 138 = utimes */
	RT_panic,			/* 139 = used internally */
	RT_panic,			/* 140 = nosys */
	RT_panic,			/* 141 = getpeername */
	RT_panic,			/* 142 = gethostid */
	RT_panic,			/* 143 = sethostid */
	RT_panic,			/* 144 = getrlimit */
	RT_panic,			/* 145 = setrlimit */
	RT_panic,			/* 146 = killpg */
	RT_panic,			/* 147 = nosys */
	RT_panic,			/* 148 = quota */
	RT_panic,			/* 149 = qquota */
	RT_panic,			/* 150 = getsockname */
#ifdef	ibmrt
	RT_open,			/* 151 = exect */
	RT_panic,			/* 152 = nosys */
	RT_panic,			/* 153 = getfpemulator */
	RT_panic,			/* 154 = iopen */
	RT_panic,			/* 155 = iread */
	RT_panic,			/* 156 = iwrite */
	RT_panic,			/* 157 = iinc */
	RT_panic,			/* 158 = idec */
	RT_pioctl,			/* 159 = pioctl */
	RT_panic,			/* 160 = setpag */
	RT_panic,			/* 161 = icreate */
#endif	ibmrt
#ifdef	vax
        RT_panic,                	/* 151 = icreate */
        RT_panic,                  	/* 152 = iopen */
        RT_panic,                  	/* 153 = iread */
        RT_panic,                 	/* 154 = iwrite */
        RT_panic,			/* 155 = iinc */
        RT_panic,                   	/* 156 = idec */
        RT_pioctl,                 	/* 157 = pioctl */
        RT_panic,                 	/* 158 = setpag */
	RT_panic,			/* 159 = nosys */
	RT_panic,			/* 160 = nosys */
	RT_panic,			/* 161 = nosys */
	RT_panic,			/* 162 = nosys */
	RT_panic,			/* 163 = nosys */
	RT_panic,			/* 164 = nosys */
	RT_panic,			/* 165 = nosys */
	RT_panic,			/* 166 = nosys */
	RT_panic,			/* 167 = nosys */
	RT_panic,			/* 168 = nosys */
	RT_panic,			/* 169 = nosys */
	RT_panic,			/* 170 = nosys */
        RT_pioctl,                 	/* 171 = pioctl */
	RT_panic,			/* 172 = setpag */
	RT_panic,			/* 173 = icreate */
	RT_panic,			/* 174 = iopen */
	RT_panic,			/* 175 = iread */
	RT_panic,			/* 176 = iwrite */
	RT_panic,			/* 177 = iinc */
	RT_panic,			/* 178 = idec */
	RT_panic,			/* 179 = nosys */
	RT_panic,			/* 180 = nosys */
#endif	vax
#ifdef	sun3
	RT_panic,			/* 151 = nosys */
	RT_panic,			/* 152 = nosys */
	RT_panic,			/* 153 = nosys */
	RT_panic,			/* 154 = nosys */
	RT_panic,			/* 155 = nosys */
	RT_panic,			/* 156 = nosys */
	RT_panic,			/* 157 = nosys */
	RT_panic,			/* 158 = nosys */
	RT_panic,			/* 159 = nosys */
	RT_panic,			/* 160 = nosys */
	RT_panic,			/* 161 = nosys */
	RT_panic,			/* 162 = nosys */
	RT_panic,			/* 163 = nosys */
	RT_panic,			/* 164 = nosys */
	RT_panic,			/* 165 = nosys */
	RT_panic,			/* 166 = nosys */
	RT_panic,			/* 167 = nosys */
        RT_pioctl,                 	/* 168 = pioctl */
        RT_panic,                 	/* 169 = setpag */
        RT_panic,                	/* 170 = icreate */
        RT_panic,                  	/* 171 = iopen */
        RT_panic,                  	/* 172 = iread */
        RT_panic,                 	/* 173 = iwrite */
        RT_panic,                   	/* 174 = iinc */
        RT_panic,                   	/* 175 = idec */
#endif	sun3
};

#ifdef	impair_debugging
#define STATIC	static
#else	impair_debugging
#define STATIC	
#endif	impair_debugging
/*
 *  rs_map:  routine to map kernel syscall numbers into remote message types.
 */

STATIC u_short
rs_map(syscode)
    short	syscode;
{
    int	nsyscodes = sizeof(rmt_syscall_map) / sizeof(rmt_syscall_map[0]);

    return((syscode == -1) 			 ? RT_open: /* core dump */
	   (syscode < 0 || syscode >= nsyscodes) ? RT_unimpl:
	    					 rmt_syscall_map[syscode]);
}


/* 
 *  rmt_store_path_arg:  store a pathname in a message to be sent to an agent 
 *
 *  dev		= remote device
 *  arg_num	= number of args to store (0, 1, 2, ...)
 *
 *  The pathname argument in the buffer given by u.u_rmt_path_buf is stored in
 *  rmt.rt_imr (the structure that will be read later by the agent process).
 *  rmt.rt_imr.im_dsize is used to get the first available position in 
 *  rmt.rt_imr.im_data and is updated accordingly.
 *
 *  NB:  the rmt path buffer is NOT released.
*/

STATIC
rmt_store_path_arg(dev, arg_num)
    dev_t	dev;
    int		arg_num;	
{
    devhack(dev);
    register char 		*pathp = u.u_rmt_path;
    register struct im_arg	*argp  = &rmt.rt_imr.im_arg[arg_num];
    register char		*datap = &rmt.rt_imr.im_data[argp->im_aval = rmt.rt_imr.im_dsize];

    if (u.u_rmt_path_buf == NULL)
        panic("rmt_store_path_arg:  no path!");

    do 				/* copy pathname */
    {
    } while (*datap++ = *pathp++);
    rmt.rt_imr.im_dsize += (argp->im_asize = pathp - u.u_rmt_path);
}


/*
 *  rmt_storeNamedPathArg:  store a named path in a message
 *
 *  dev		= remote device
 *  pathname	= path to store
 *  argNum	= where to store it
 */

STATIC
rmt_storeNamedPathArg(dev, pathname, argNum)
    dev_t	dev;
    char 	*pathname;
    int		argNum;
{
    devhack(dev);
    register struct im_arg	*argp  = &rmt.rt_imr.im_arg[argNum];
    register char		*pathp = pathname;
    register char		*datap = &rmt.rt_imr.im_data[argp->im_aval = rmt.rt_imr.im_dsize];

    do 				/* copy pathname */
    {
    } while (*datap++ = *pathp++);
    rmt.rt_imr.im_dsize += (argp->im_asize = pathp - pathname);
}


/* 
 *  rmt_store_user_arg:  store a multi-byte argument from user space 
 *                       into a message for the agent .
 *
 *  dev		= remote device
 *  arg_num	= the number of the argument to store (0, 1, 2, ...)
 *  uaddr	= address in user space of the data structure
 *  size	= number of bytes
*/

STATIC
rmt_store_user_arg(dev, arg_num, uaddr, size)
    dev_t	dev;
    int		arg_num;	
    caddr_t	uaddr;
    int		size;
{
    devhack(dev);
    register struct im_arg	*argp;

    if (size > MAXPATHLEN || size <= 0) 
    {
        u.u_error = EINVAL;
        return;
    }

    argp = &rmt.rt_imr.im_arg[arg_num];
    u.u_error = copyin(uaddr, &rmt.rt_imr.im_data[argp->im_aval = rmt.rt_imr.im_dsize], (u_int) size);
    rmt.rt_imr.im_dsize += (argp->im_asize = size);
}


/* 
 *  rmt_check_arg:  verify validity of a non-integer argument passed 
 *                  from an agent process .
 *
 *  dev		= remote device
 *  arg_num	= the number of the argument to check (0, 1, 2, ...)
 *
 *  Returns:  -1 if there is something wrong, 0 otherwise
*/

STATIC
rmt_check_arg(dev,arg_num)
    dev_t		dev;
    register int	arg_num;
{
    devhack(dev);
    register struct im_arg	*argp = &rmt.rt_imw.im_arg[arg_num];

    return(    argp->im_asize == 0
	    || argp->im_aval + argp->im_asize > rmt.rt_imw.im_dsize
	    || argp->im_asize > MAXPATHLEN
	  ) ? -1 : 0;
}


STATIC struct inode *
rmt_single_path(ndp, nbp, rt_code)
    struct nameidata	*ndp;
    register struct buf	*nbp;
    u_short		rt_code;
{   /*  Rmt_namei() syscalls involving ONE pathname come here.  If the remote
	handler resolves the name out of it's name space (i.e. it encounters
	a symbolic link which points back to the local name space or to
	another Venus' name space), the new pathname is returned in the SAME
	name buf that we used to pass the original pathname, a pointer to the
	start of the name comes back in u.u_rmt_path, and u.u_error contains
	EABSPATH1.  We signal this event to namei() by setting u.u_error == 0.
	Namei() will then start over with this new name, iterating until the
	name is fully resolved in the local or a remote name space or until
	a real error occurs.  We signal that the syscall has been carried out
	remotely by setting u.u_error == EVICEOP.  This causes namei() to
	return (with value NULL) to its caller (which then skips local processing
	in the usual case).
    */
    dev_t	dev = u.u_rmt_dev;
    devhack(dev);

    u.u_rmt_path_buf = nbp;
    u.u_rmt_path = ndp->ni_dirp;
    u.u_rmt_follow1 = (ndp->ni_nameiop & FOLLOW);

    u.u_procp->p_flag |= SRMT;		/* Disable processing of STOP signal 
					   during the system call, so that 
                                           the buffer won't get tied up. */
    rmt_attach_rbuf(dev,1);

    switch(rt_code)
    {
        case RT_access:
            rmt_store_path_arg(dev, 0);
            rmt.rt_imr.im_arg[1].im_aval = u.u_ap[1];	/* mode */
            rmt_send(dev, RT_access);
            break;

        case RT_chdir:
            if (u.u_rmt_code != 12)
            {
                u.u_error = EINVAL;			/* chroot() not supported */
                break;
            }

            rmt_store_path_arg(dev, 0);
            rmt_send(dev, RT_chdir);
            if (u.u_error == 0) 
            {
                u.u_rmtWd.dev = dev;
                bcopy((caddr_t) rmt.rt_imw.im_wdfid, (caddr_t) u.u_rmtWd.fid, sizeof(u.u_rmtWd.fid));
                if (u.u_cdir)
                {
                    irele(u.u_cdir);
                    u.u_cdir = NULL;
                }
            }
            break;

        case RT_chmod:
            rmt_store_path_arg(dev, 0);
            rmt.rt_imr.im_arg[1].im_aval = u.u_ap[1];	/* mode */
            rmt_send(dev, RT_chmod);
            break;

        case RT_chown:
            rmt_store_path_arg(dev, 0);
            rmt.rt_imr.im_arg[1].im_aval = u.u_ap[1];	/* new uid */
            rmt.rt_imr.im_arg[2].im_aval = u.u_ap[2];	/* new gid */
            rmt_send(dev, RT_chown);
            break;

        case RT_mkdir:
            rmt_store_path_arg(dev, 0);
            rmt.rt_imr.im_arg[1].im_aval = u.u_ap[1]&~u.u_cmask; /* mode */
            rmt_send(dev, RT_mkdir);
            break;

        case RT_open:
            switch(u.u_rmt_code)
            {
                case 5:				/* open */
		{
		    struct a {
			char	*fname;
			int	mode;
			int	crtmode;
		    } *uap = (struct a *)u.u_ap;

 		    rmt_copen(dev, uap->mode, uap->crtmode);
                    break;
		}

                case 8:				/* creat */
		{
		    struct a {
			char	*fname;
			int	fmode;
		    } *uap = (struct a *)u.u_ap;

		    rmt_copen(dev, (O_WRONLY|O_CREAT|O_TRUNC), uap->fmode);
		    break;
		}

                case 11:			/* execv */
                case 59:			/* execve */
#ifdef	ibmrt
		case 151:			/* exect */
#endif	ibmrt
		{
                    rmt_kopen(dev, O_RDONLY, 0, 1);
		    if (u.u_error == 0)
		    {
			register char *cp, *sp;

			/*
			 *  Track down trailing pathname component of remote file name and save it
			 *  where execve() will expect it to be later.
			 */
			cp = ndp->ni_dirp;
			for (sp=cp; *cp; cp++)
			    if (*cp == '/')
				sp = cp;
			if (*sp == '/')
			    sp++;
			u.u_nd.ni_dent.d_namlen = cp-sp;
			if (u.u_nd.ni_dent.d_namlen > MAXCOMLEN)
			    u.u_nd.ni_dent.d_namlen = MAXCOMLEN;
			bcopy(sp, (caddr_t)u.u_nd.ni_dent.d_name, (unsigned)(u.u_nd.ni_dent.d_namlen + 1));
		    }
                    break;
		}

		case -1:			/* core dump */
		    rmt_kopen(dev, (O_WRONLY | O_TRUNC | O_CREAT), 0644, 0);
		    break;
            }
            break;

        case RT_pioctl:
        {
            struct a {
                char	*path;
                int	com;
                caddr_t	comarg;
                int	follow;
            } *uap = (struct a *)u.u_ap;
            struct ViceIoctl	data;

            u.u_error = copyin(uap->comarg, (caddr_t) &data, sizeof(data));
            if (u.u_error)
                break;
            rmt_store_path_arg(dev, 0);
            rmt.rt_imr.im_arg[1].im_aval = uap->com;
            if (data.in && data.in_size) 
            {
                rmt_store_user_arg(dev, 2, data.in, data.in_size);
                if (u.u_error)
                    break;
            }
            rmt_send(dev, RT_pioctl);
            if (u.u_error)
                break;
            if (data.out && data.out_size) 
            {
                if (   rmt_check_arg(dev, 0) == -1 
                    || rmt.rt_imw.im_arg[0].im_asize > data.out_size) 
                    u.u_error = EINVAL;		/* This is a lousy error code */
                else
                    u.u_error = copyout(&rmt.rt_imw.im_data[0], data.out, 
                                        (u_int) rmt.rt_imw.im_arg[0].im_asize);
            }
            break;
        }

        case RT_readlink:
        {
            register struct a {
                char	*name;
                char	*buf;
                int	count;
            } *uap = (struct a *)u.u_ap;

            rmt_store_path_arg(dev, 0);
            rmt_send(dev, RT_readlink);
            if (u.u_error)
                break;
            if (   rmt_check_arg(dev, 1) != 0 
                || rmt.rt_imw.im_arg[1].im_asize > uap->count) 
            {
                u.u_error = ENOENT;
                break;
            }
            u.u_error = copyout(&rmt.rt_imw.im_data[0], 
                                uap->buf, (u_int) rmt.rt_imw.im_arg[1].im_asize);
            u.u_r.r_val1 = rmt.rt_imw.im_arg[1].im_asize;
            break;
        }

        case RT_rmdir:
            rmt_store_path_arg(dev, 0);
            rmt_send(dev, RT_rmdir);
            break;

        case RT_stat:
        {
            register struct a {
                char		*fname;
                struct stat	*sb;
            } *uap = (struct a *)u.u_ap;

            rmt_store_path_arg(dev, 0);
            rmt_send(dev, RT_stat);
            if (!u.u_error)
                u.u_error = copyout((caddr_t)&rmt.rt_imw.im_data[0], 
                                    (caddr_t)uap->sb, sizeof(struct stat));
            break;
        }

        case RT_symlink:
        {
            register struct a {
                char	*target;
                char	*linkname;
            } *uap = (struct a *)u.u_ap;
            char	c;
            char	*cp = uap->target;
            int		target_len = 0;

            while (c = fubyte(cp))	/* recompute length of target name */
            {
                if (c < 0)
                {
                    u.u_error = EFAULT;
                    break;
                }
                cp++;
                target_len++;
            }

            rmt_store_user_arg(dev, 0, uap->target, target_len + 1);
            rmt_store_path_arg(dev, 1);
            rmt_send(dev, RT_symlink);
            break;
        }

        case RT_truncate:
            rmt_store_path_arg(dev, 0);
            rmt.rt_imr.im_arg[1].im_aval = u.u_ap[1];	/* truncated length */
            rmt_send(dev, RT_truncate);
            break;

        case RT_unlink:
            rmt_store_path_arg(dev, 0);
            rmt_send(dev, RT_unlink);
            break;

        case RT_utimes:
        {
            register struct a {
                char		*fname;
                struct timeval	(*tptr)[2];
            } *uap = (struct a *)u.u_ap;

            rmt_store_path_arg(dev, 0);
            rmt_store_user_arg(dev, 1, (caddr_t)uap->tptr, sizeof(*uap->tptr));
            rmt_send(dev, RT_utimes);
            break;
        }
    }

    if (u.u_error == EABSPATH1) 
        if (  (rmt.rt_flags&RT_WBUF)== 0 
            || rmt.rt_imw.im_client != u.u_procp->p_pid
            || rmt_check_arg(dev, 0) != 0)
        {
            printf("rmt_single_path: screw up!\n");
            u.u_error = EINVAL;		/* Better error code??? */
        }
        else 				/* New path to process */
        {
            u.u_error = 0;
            u.u_rmt_path = u.u_rmt_path_buf->b_un.b_addr;
            bcopy(rmt.rt_imw.im_data, u.u_rmt_path, (u_int) rmt.rt_imw.im_arg[0].im_asize);
            ndp->ni_dirp = u.u_rmt_path;
         }
    else
        if (!u.u_error)
            u.u_error = EVICEOP;

    rmtcleanup(dev);
    u.u_procp->p_flag &= ~SRMT;

    u.u_rmt_path_buf = NULL;
    return((struct inode *)NULL);	/* ALWAYS */
}


/*
 *  rmt_copen:  "user open" -- common code for rmt_open and rmt_create
 *
 *  dev		= remote device
 *  uflags	= user flags
 *  umode	= mode (crtmode or fmode)
*/

STATIC
rmt_copen(dev, uflags, umode)
    dev_t	dev;
    int		uflags;
    int		umode;
{
    register struct file	*fp = u.u_ofile[u.u_r.r_val1];
    struct inode		*ip;
    int		    		kflags = uflags - FOPEN;

    rmt_getfile(dev, &ip, uflags, umode, &fp->f_rmt_fileid, 0);
    if (ip) 
    {
	iunlock(ip);
	fp->f_flag = kflags & FMASK;
	fp->f_type = DTYPE_VICEINO;
	fp->f_ops  = &rmt_ops;
	fp->f_data = (caddr_t)ip;
    }
}


/*
 *  rmt_kopen:  "kernel open" -- common code for exec and core dump
 *
 *  dev		= remote device
 *  uflags	= user flags
 *  umode	= mode
 *  exec	= "open for exec" flag
*/

STATIC
rmt_kopen(dev, uflags, umode, exec)
    dev_t	dev;
    int		uflags;
    int		umode;
    int		exec;
{
    register struct file	*fp;
    int				fd;
    struct inode		*ip;
    int		    		kflags = uflags - FOPEN;

    fp = falloc();
    if (fp == NULL)
        return;
    fd = u.u_r.r_val1;
    rmt_getfile(dev, &ip, uflags, umode, &fp->f_rmt_fileid, exec);
    if (ip) 
    {
	fp->f_flag = kflags & FMASK;
	fp->f_type = DTYPE_VICEINO;
	fp->f_ops  = &rmt_ops;
	fp->f_data = (caddr_t)ip;
    }
    else			/* Deallocate fd and file on failure */
    {
        u.u_ofile[fd] = NULL;
        fp->f_count = 0;
        fp = NULL;
    }
}


/* 
 *  rmt_getfile:  get an inode pointer for a copy of a file from Vice.
 *
 *  dev		= remote device
 *  ipp		= returned inode pointer
 *  uflags	= open flags as in open(2)
 *  umode	= creation mode as in open(2)
 *  fileid	= returned file identifier for remote system
 *  exec	= 1 => open for execute
*/

STATIC
rmt_getfile(dev, ipp, uflags, umode, fileid, exec)
    dev_t		dev;		
    struct inode	**ipp;
    int			uflags;
    int			umode;
    int			*fileid;
    int			exec;
{
    devhack(dev);
    register struct inode	*ip;
    extern struct inode		*igetinode();

    *ipp = NULL;
    rmt_store_path_arg(dev, 0);
    rmt.rt_imr.im_arg[1].im_aval = uflags;
    rmt.rt_imr.im_arg[2].im_aval = umode & ~u.u_cmask;
    rmt.rt_imr.im_arg[3].im_aval = exec;
    rmt_send(dev, RT_open);
    if (u.u_error)
        return;
    *fileid = rmt.rt_imw.im_arg[0].im_aval;
    rmt_detach_wbuf(dev);
    ip = igetinode((dev_t)rmt.rt_imw.im_arg[1].im_aval,
                   (ino_t)rmt.rt_imw.im_arg[2].im_aval);

    if (u.u_error)
    {
	rmt_getfile_abort(dev, *fileid, RTE_NOFILE);
	return;
    }
    if ((ip->i_mode & IFMT) != IFREG)
    {
	iput(ip);
	rmt_getfile_abort(dev, *fileid, RTE_NOTREG);
	return;
    }

/*  
    if (text file busy)
    {
	iput(ip);
	rmt_getfile_abort(dev, *fileid, 0);
	u.u_error = ETXTBSY;
	return;
    }
*/

    ip->i_rmt_dev = dev;
    *ipp = ip;
}


/* 
 *  rmt_getfile_abort:  Abort a remote open request 
 *
 *  dev		= remote device
 *  fileid	= fileid supplied by agent on open
 *  error	= error code to return on close message to agent
 *                process. If this is 0, then no error is returned
 *                to the agent; also, u.u_error is not set (because
 *                evidently an error other than a problem with the
 *                agent has occurred).
 *
 *  N.B.  Only called when a file identifier has already been
 *        assigned by an agent process.
*/

STATIC
rmt_getfile_abort(dev, fileid, error)
    dev_t	dev;
    int		fileid;
    int		error;
{
    devhack(dev);

    rmt_attach_rbuf(dev,1);
    rmt.rt_imr.im_arg[0].im_aval = fileid;
    if (error)
    {
	u.u_error = EVICEERR;
	rmt.rt_imr.im_error = error;
    }
    rmt_send(dev, RT_close);
}


STATIC struct inode *
rmt_dual_paths(ndp, nbp, rt_code)
    struct nameidata	*ndp;
    register struct buf	*nbp;
    u_short		rt_code;
{   /*  Rmt_namei() syscalls involving TWO pathnames come here.  THIS SECTION
	IS A TOTAL HACK, but the requirement of providing compatibility with
	existing software (i.e. the RFS code) gave me no choice.  BEWARE!

	A syscall involving two names is legal only if they both resolve to
	the same device (either local or remote); otherwise an EXDEV error is
	returned from the call.  A major complication with the ITC/Andrew
	system is that it allows symbolic links across name spaces.  Thus, 
	when a namei() lookup identifies a name as being in the name space of
	a particular remote device, this is only a HINT; the name may
	eventually resolve to somewhere else.  When TWO names are involved in
	the operation, there are many more possibilities to consider.

	This routine may be entered in one of 3 situations:
	1/ The first name points to the name space of a remote device (although
	   there is no guarantee that it will remain there).  In this case, we
	   make a nested call of namei() on the second name.
	2/ The second name, looked up in a NON-NESTED call of namei(), points to
	   the name space of a remote device.  This can occur ONLY if the first
	   name resolved (fully) into the LOCAL name space.
	3/ The second name, looked up in the NESTED call of namei(), points to
	   the name space of a remote device (again, there is no guarantee that
	   it will remain there OR that it is the same remote device as name1's).

	We distinguish between the above three cases with the u-area variable
	u.u_rmt_ncnt.  Each case is discussed in the appropriate arm of the
	case statement below.

	The main UGLINESS of the whole arrangement arises from the need for
	communication between the two instances of rmt_namei() when there is
	an intervening namei() call.  To handle this communication, I have
	created a new variable in the u-area, u.u_rmt_saved_data which points 
	to a struct containing the necessary fields (a single struct handles
	communications in both directions).
    */

    switch(u.u_rmt_ncnt)
    {
        case 1:
        /* This corresponds to the case where namei() has (tentatively)
	   resolved name1 into a remote device's name space (and nothing is
	   yet known about name2). */

        {
            struct inode		*ip;
            struct nameidata		xndp;
            struct rmt_saved_data	rsd;

            rsd.rsd_dev = u.u_rmt_dev;		/* Save data for nested rmt_namei */
            rsd.rsd_nidata = ndp;
            rsd.rsd_nibuf = nbp;
            u.u_rmt_saved_data = &rsd;

            u.u_rmt_ncnt++;			/* Bump count for new state */

	    /* Now look up the second name. */

            xndp.ni_iov = &xndp.ni_iovec;
            xndp.ni_nameiop = CREATE | LOCKPARENT | NOCACHE;
            xndp.ni_segflg = UIO_USERSPACE;
            xndp.ni_dirp = (char *)u.u_ap[1];	/* second name */
            ip = namei(&xndp);
            u.u_rmt_dev = rsd.rsd_dev;		/* restore remote device pointer */
            u.u_rmt_requested = 1;		/* restore flag */
	    u.u_rmt_ncnt = 1;			/* reset state */

	    switch (u.u_error)
	    {
		case 0:
                /* Name2 is now DEFINITELY local, but we can't yet return a
		   cross-device error (EXDEV) because we're not certain that
		   name1 isn't local too (which would happen if the remote
		   name we have for it now is a symbolic link back to the local
		   name space).  So, we do an explicit check on name1 to see
		   whether it really points to the remote device. */

		{
		    if (ip != NULL)
                        iput(ip);		/* release the inode for name2 */
		    iput(xndp.ni_pdir);		/* release name2's parent inode */

                    u.u_rmt_path_buf = nbp;
                    u.u_rmt_path = ndp->ni_dirp;
                    u.u_rmt_follow1 = (ndp->ni_nameiop & FOLLOW);
                    rmt_checkPathName(u.u_rmt_dev);
                    if (u.u_rmt_path_buf)		/* new name1 */
                    {
                        u.u_error = 0;
                        ndp->ni_dirp = u.u_rmt_path;
                        u.u_rmt_path_buf = NULL;
                    }
                    else 				/* name1 DEFINITELY remote */
                        if (!u.u_error)
                            u.u_error = EXDEV;		/* Cross device op illegal */
		    break;
                }

		case EABSPATH1:
                /* The nested rmt_namei() has returned a new path for name1 in the
		   "rmt_saved_data" structure.  We must copy that path to our own
		   buffer, which we return to the outer namei() for more lookup.*/

		    if (ip != NULL)
		        panic("rmt_dual_paths:  ip != NULL");	/* DEBUG */
		{
		    u.u_error = copystr(rsd.rsd_nidata->ni_dirp, nbp->b_un.b_addr, MAXPATHLEN, (u_int *)0);
		    ndp->ni_dirp = nbp->b_un.b_addr;
		    break;
                }

		case EVICEOP:				/* Call completed remotely */
		default:				/* Real error */
		    if (ip != NULL)
		        panic("rmt_dual_paths:  ip != NULL");	/* DEBUG */
		    break;
	    }

            break;
        }

        case 2:
	/* This corresponds to the case where name2 has been found to be
	   (tentatively) remote from a NON-NESTED call of namei() (meaning that
	   name1 has been found to be DEFINITELY local).  Again, we can't yet
	   return a X-DEV error because we're not certain that name2 isn't local
	   too.  So, we do an explicit check on name2 to see whether it really
	   points to the remote device, or somewhere else (at least tentatively). */

	{
            u.u_rmt_path_buf = nbp;
            u.u_rmt_path = ndp->ni_dirp;
            u.u_rmt_follow1 = (ndp->ni_nameiop & FOLLOW);
            rmt_checkPathName(u.u_rmt_dev);
            if (u.u_rmt_path_buf)			/* new name2 */
            {
                u.u_error = 0;
                ndp->ni_dirp = u.u_rmt_path;
                u.u_rmt_path_buf = NULL;
            }
            else 					/* name2 DEFINITELY remote */
                if (!u.u_error)
                    u.u_error = EXDEV;			/* Cross device op illegal */
            break;
	}

        case 3:
	/* This corresponds to the NESTED call, where both name1 and name2 are
	   pointing to remote name spaces (although neither will necessarily
	   resolve there, nor are the remote devices necessarily the same).  The
	   parent rmt_namei() call will have saved data for us in a block pointed
	   to by the u.u_rmt_saved_data variable. */
        {
            struct rmt_saved_data	*rsd = u.u_rmt_saved_data;

            if (u.u_rmt_dev == rsd->rsd_dev)
	    /* Both names point to the same Venus (i.e. remote device). So, let's
	       try the remote op.  The call will either succeed, return a fatal
	       error, or indicate that one of the names resolved out of the
	       remote name space (EABSPATH1 indicates that the first name did;
	       EABSPATH2 that the second did [and that the first didn't]). 
	       rmt_rename_or_link() will copy the new name into the appropriate
	       buffer in the latter cases. */

            {
                u.u_rmt_follow1 = (rsd->rsd_nidata->ni_nameiop & FOLLOW);
                u.u_rmt_follow2 = (ndp->ni_nameiop & FOLLOW);
                rmt_rename_or_link(u.u_rmt_dev, rt_code, rsd->rsd_nidata->ni_dirp,
                                   rsd->rsd_nibuf, ndp->ni_dirp, nbp);
                switch (u.u_error)
                {
                    case 0:				/* success */
                        u.u_error = EVICEOP;
                        break;

                    case EABSPATH1:			/* new name1 */
                        /* Pass through error == EABSPATH1; this will tell the
		           parent rmt_namei() that it should (tell it's calling
			   namei() to) retry with the new name1. */
                        rsd->rsd_nidata->ni_dirp = rsd->rsd_nibuf->b_un.b_addr;
                        break;

                    case EABSPATH2:			/* new name2 */
			/* Setting error == 0 will tell our (NESTED) calling
			   namei() to retry with the new name2. */
                        u.u_error = 0;
                        ndp->ni_dirp = nbp->b_un.b_addr;
                        break;

                    default:				/* real error */
                        /* pass error through */
                        break;
                }
            }
            else
	    /* The names point to different veni.  We can't consider this an
	       error yet because they could still resolve to the same device
	       (remote or local) after symlink expansion.  So, let's do the
	       expansion. */
            {
               /* Check name1 first */

                u.u_rmt_path_buf = rsd->rsd_nibuf;
                u.u_rmt_path = rsd->rsd_nidata->ni_dirp;
                u.u_rmt_follow1 = (rsd->rsd_nidata->ni_nameiop & FOLLOW);
                rmt_checkPathName(rsd->rsd_dev);
                if (u.u_rmt_path_buf)			/* new name1 */
                {
                    /* Pass through error == EABSPATH1; this will tell the
		       parent rmt_namei() that it should (tell it's calling
		       namei() to) retry with the new name1. */
                    rsd->rsd_nidata->ni_dirp = u.u_rmt_path;
                    u.u_rmt_path_buf = NULL;
                }
                else 					/* name1 DEFINITELY  on venus1 */
                {   /* Now check name2 */

                    u.u_rmt_path_buf = nbp;
                    u.u_rmt_path = ndp->ni_dirp;
                    u.u_rmt_follow1 = (ndp->ni_nameiop & FOLLOW);
                    rmt_checkPathName(u.u_rmt_dev);
                    if (u.u_rmt_path_buf)		/* new name2 */
                    {
		        /* Setting error == 0 will tell our (NESTED) calling
			   namei() to retry with the new name2. */
                        u.u_error = 0;
                        ndp->ni_dirp = u.u_rmt_path;
                        u.u_rmt_path_buf = NULL;
                    }
                    else				/* name2 DEFINITELY  on venus2 */
                        if (!u.u_error)
                            u.u_error = EXDEV;		/* Different Veni--illegal */
                }
            }

            break;
        }

        default:
	    printf("u.u_rmt_ncnt == %x\n",u.u_rmt_ncnt);
            panic("rmt_namei:  illegal u.u_rmt_ncnt!!!");
    }

    return((struct inode *)NULL);	/* ALWAYS */
}


/* 
 *  rmt_rename_or_link:  handle a remote call involving two pathnames.  If either
 *                       name resolves out of the (specified remote) name space, copy
 *                       the new path back to the appropriate buffer.
 *
 *  dev		= remote device
 *  rt_code	= RT_link || RT_rename
 *  path1	= pointer to first pathname
 *  buf1	= buffer containing first pathname
 *  path2	= pointer to second pathname
 *  buf2	= buffer containing second pathname
*/

STATIC
rmt_rename_or_link(dev, rt_code, path1, buf1, path2, buf2)
    dev_t	dev;
    u_short	rt_code;
    char	*path1;
    struct buf	*buf1;
    char	*path2;
    struct buf	*buf2;
{
    devhack(dev);
    char	*pathp;			/* temporary path pointer */

    u.u_procp->p_flag |= SRMT;		/* Disable processing of STOP signal 
					   during the system call, so that 
                                           the buffer won't get tied up. */
    rmt_attach_rbuf(dev,1);
    rmt_storeNamedPathArg(dev, path1, 0);
    rmt_storeNamedPathArg(dev, path2, 1);
    rmt_send(dev, rt_code);

    if (u.u_error == EABSPATH1 || u.u_error == EABSPATH2)
        if (  (rmt.rt_flags&RT_WBUF)== 0 
            || rmt.rt_imw.im_client != u.u_procp->p_pid
            || rmt_check_arg(dev, 0) != 0)
        {
            printf("rmt_dual_paths: screw up!\n");
            u.u_error = EINVAL;		/* Better error code??? */
        }
        else 				/* New path to process */
        {
            pathp = (u.u_error == EABSPATH1 ? buf1: buf2)->b_un.b_addr;
            bcopy(rmt.rt_imw.im_data, pathp, (u_int) rmt.rt_imw.im_arg[0].im_asize);
        }

    rmtcleanup(dev);
    u.u_procp->p_flag &= ~SRMT;
    return (NULL);
}


/*
 *  rmt_checkPathName:  check that file is in the name space of a remote file system.
 *                      The file is in the name space unless u.u_error == EABSPATH1.
 *                      The name to check is assumed to be in u.u_rmt_path_buf and
 *                      the start pointed at by u.u_rmt_path.  If the name resolves
 *                      out of the remote name space, the new path is copied back
 *                      into u.u_rmt_path_buf (at the head).
 *  
 *
 *  dev	= remote device
*/

STATIC
rmt_checkPathName(dev)
    dev_t	dev;
{
    devhack(dev);

    u.u_procp->p_flag |= SRMT;		/* Disable processing of STOP signal 
					   during the system call, so that 
                                           the buffer won't get tied up. */

    rmt_attach_rbuf(dev,1);
    rmt_store_path_arg(dev, 0);
    rmt_send(dev, RT_stat);

    if (u.u_error == EABSPATH1)
        if (  (rmt.rt_flags&RT_WBUF)== 0 
            || rmt.rt_imw.im_client != u.u_procp->p_pid
            || rmt_check_arg(dev, 0) != 0)
        {
            printf("rmt_checkPathName: screw up!\n");
            u.u_error = EINVAL;		/* Better error code??? */
            u.u_rmt_path_buf = NULL;
        }
        else 				/* New path to process */
        {
            u.u_rmt_path = u.u_rmt_path_buf->b_un.b_addr;
            bcopy(rmt.rt_imw.im_data, u.u_rmt_path, (u_int) rmt.rt_imw.im_arg[0].im_asize);
        }
    else
    {
	u.u_error = 0;			/* Ignore other errors */
        u.u_rmt_path_buf = NULL;
    }

    rmtcleanup(dev);
    u.u_procp->p_flag &= ~SRMT;
    return (NULL);
}


/*
 *  rmt_namei:  perform remote syscall for a pathname(s).
 *
 *  ndp	= pointer to namei data structure
 *  nbp	= pointer to name buffer
 *
 *  Returns:  NULL (always) with u.u_error set as follows:
 *    0		- pathname resolved out of a Venus' namespace; new name in nbp,
 *		  pointer in ndp->ni_dirp;
 *    EVICEOP	- syscall was handled remotely;
 *    EABSPATH1	- can occur only with dual-pathname calls; used by a NESTED
 *    		  rmt_namei() call to indicate to the parent rmt_namei() that the
 *    		  first name resolved out of a Venus' name space;
 *    other	- real error occurred;
*/

struct inode *
rmt_namei(ndp, nbp)
    struct nameidata	*ndp;
    register struct buf	*nbp;
{
    u_short	rt_code = rs_map(u.u_rmt_code);
    struct inode *ip;
    int which;

    switch (rt_code)
    {
        case RT_panic:
	    printf("BAD syscall %d!\n", u.u_rmt_code);
	    panic("rmt_namei:  RT_panic!");
	    /*NOTREACHED*/
        case RT_unimpl:
	    u.u_error = EOPNOTSUPP;
	    return(NULL);
    }

    if (rt_code == RT_link || rt_code == RT_rename)
        ip = (struct inode *)rmt_dual_paths(ndp, nbp, rt_code);
    else
        ip = (struct inode *)rmt_single_path(ndp, nbp, rt_code);
    switch (u.u_error)
    {
	case ENOSPC:
	    which = URPW_FNOSPC|URPW_POLL;
	    goto nospace;
	case EDQUOT:
	    which = URPW_QNOSPC|URPW_POLL;
	    /* fall through */
	nospace:
	    fsfull(rmt_fsbufp[minor(u.u_rmt_dev)]->b_un.b_fs, which);
	    break;
    }
    return(ip);
}


/* 
 *  rmt_close_fop:  close an open remote file 
 *
 *  fp	= file pointer
*/

rmt_close_fop(fp)
    struct file	*fp;
{
    int which = 0;
    int doclose = 1;
    int error = u.u_error;

    /*
     *  The typical Vice resource exhaustion errors occur on the close when the
     *  cached file is stored to the file server.  The original RT_close
     *  operation is defined to be issued only once and any errors encountered
     *  are non-recoverable.  The new RT_tryclose operation is defined to be
     *  recoverable on errors, otherwise it is final as with RT_close.
     */
    do
    {
	u.u_error = 0;
	rmt_fop(fp, RT_tryclose);
	switch (u.u_error)
	{
	    case ENOSPC:
		which = URPW_FNOSPC|URPW_POLL;
		goto nospace;
	    case EDQUOT:
		which = URPW_QNOSPC|URPW_POLL;
		/* fall through */
	    nospace:
		fsfull(rmt_fsbufp[minor(((struct inode *)fp->f_data)->i_rmt_dev)]->b_un.b_fs, which);
		break;
	    /*
	     *  A try-close operation without any errors has already closed the
	     *  file in Venus.
	     */
	    case 0:
		doclose = 0;
		break;
	}
    } while (fspause(fp->f_flag&FNOSPC));

    if (u.u_error == 0)
	u.u_error = error;

    if (doclose)
	rmt_fop(fp, RT_close);
    ino_close(fp);
}



/* 
 *  rmt_fstat_fop:  get status of open remote file 
 *
 *  fp	= remote file pointer
 *  sb	= where to copy status
 *
 *  Return:  0 on success or an error number as appropriate.
*/

rmt_fstat_fop(fp, sb)
    struct file	*fp;
    struct stat	*sb;
{
    rmt_fop(fp, RT_fstat, (caddr_t)sb);
    return(u.u_error);
}


/* 
 *  rmt_ioctl_fop:  ioctl to an open remote file
 *
 *  fp		= file pointer
 *  com		= ioctl command to execute
 *  data	= pointer to argument block
 *
 *  Return: 0 on success or an error number as appropriate.
*/

rmt_ioctl_fop(fp, com, data)
    struct file	*fp;
    int 	com;
    caddr_t 	data;
{
    if (_VALIDVICEIOCTL(com))
        rmt_fop(fp, RT_ioctl, (caddr_t)com, data);
    else
        u.u_error = ino_ioctl(fp, com, data);

    return (u.u_error);
}


/*
 *  rmt_fop:  shared routine for fileop file descriptor call processing;
 *
 *  fp		= file descriptor
 *  rt_code	= remote syscall type
 *  arg1	= arbitrary arg for syscall handler
 *  arg2	= 	"	"	"	"
 *
 *  Return: NULL (always) with u.u_error set as appropriate.
 */

/* VARARGS */
rmt_fop(fp, rt_code, arg1, arg2)
    struct file *fp;
    u_short	rt_code;
    caddr_t	arg1;
    caddr_t	arg2;
{
    dev_t	dev = ((struct inode *)(fp->f_data))->i_rmt_dev;
    int		fileid = fp->f_rmt_fileid;
    devhack(dev);

    u.u_procp->p_flag |= SRMT;		/* Disable processing of STOP signal 
					   during the system call, so that 
                                           the buffer won't get tied up. */
    rmt_attach_rbuf(dev, 1);
    rmt.rt_imr.im_arg[0].im_aval = fileid;

    switch (rt_code)
    {
        case RT_close:
        case RT_tryclose:
            rmt_send(dev, rt_code);
            break;

        case RT_fstat:
        {
            struct stat	*sb = (struct stat *)arg1;

            rmt_send(dev, RT_fstat);
            if (u.u_error)
                break;
            u.u_error = copyout((caddr_t)&rmt.rt_imw.im_data[0], (caddr_t)sb,
                                sizeof(struct stat));
            break;
        }

        case RT_ioctl:
        {
            int			com = (int)arg1;
            struct ViceIoctl	*data = (struct ViceIoctl *)arg2;

            rmt.rt_imr.im_arg[1].im_aval = com;
            if (data->in && data->in_size) 
            {
                rmt_store_user_arg(dev, 2, data->in, data->in_size);
                if (u.u_error)
                    break;
            }
            rmt_send(dev, RT_ioctl);
            if (u.u_error)
                break;
            if (data->out && data->out_size) 
            {
                if (   rmt_check_arg(dev, 0) == -1 
                    || rmt.rt_imw.im_arg[0].im_asize > data->out_size) 
                    u.u_error = EINVAL;		/* This is a lousy error code */
                else
                    u.u_error = copyout(&rmt.rt_imw.im_data[0], data->out, 
                                        (u_int) rmt.rt_imw.im_arg[0].im_asize);
            }
            break;
        }
    }

    rmtcleanup(dev);
    u.u_procp->p_flag &= ~SRMT;
    return(NULL);		/* ALWAYS */
}


/*
 *  rmt_fdes:  non-fileops file descriptor call processing;
 *
 *  fp	= file descriptor
 *
 *  Return: the argument fp if further local processing is required and
 *	there was no error; NULL otherwise.  u.u_error is set to EVICEOP
 *	or a real error code if a real error occurred.
 */

struct file *
rmt_fdes(fp)
    struct file	*fp;
{
    u_short	rt_code = rs_map(u.u_rmt_code);
    dev_t	dev = ((struct inode *)(fp->f_data))->i_rmt_dev;
    int		fileid = fp->f_rmt_fileid;
    devhack(dev);

    u.u_procp->p_flag |= SRMT;		/* Disable processing of STOP signal 
					   during the system call, so that 
                                           the buffer won't get tied up. */
    rmt_attach_rbuf(dev,1);
    rmt.rt_imr.im_arg[0].im_aval = fileid;

    switch(rt_code)
    {
        case RT_fchmod:
            rmt.rt_imr.im_arg[1].im_aval = u.u_ap[1];	/* mode */
            break;

        case RT_fchown:
            rmt.rt_imr.im_arg[1].im_aval = u.u_ap[1];	/* new uid */
            rmt.rt_imr.im_arg[2].im_aval = u.u_ap[2];	/* new gid */
            break;

        case RT_ftruncate:
            rmt.rt_imr.im_arg[1].im_aval = u.u_ap[1];	/* truncated length */
            break;

        case RT_fsync:
            break;

        case RT_flock:
            rmt.rt_imr.im_arg[1].im_aval = u.u_ap[1];	/* operation */
            break;

        default:
            printf("RT_code=%d\n", rt_code);
            panic("rmt_fdes");
    }

    rmt_send(dev, rt_code);
    if (u.u_error == 0)
        u.u_error = EVICEOP;

    rmtcleanup(dev);
    u.u_procp->p_flag &= ~SRMT;
    if (rt_code == RT_ftruncate && u.u_error == EVICEOP)
	return(fp);
    else
	return((struct file *)NULL);
}


/* 
 *  rmt_mount:  "mount" a remote file system on a special remote mount device 
 *
 *  dev		= communications channel with the agent process
 *  ip		= indirect inode
 *  parent	= indirect inode's parent
*/

struct fs *
rmt_mount(dev, ip, parent)
    dev_t		dev;
    struct inode	*ip;
    struct inode	*parent;
{
    register struct mount  *mp;
    register struct buf *bp;
    int mdev;
    extern struct mount *getmountstruct ();

    mdev = minor(dev);
    if (mdev >= NVICEFS)
	u.u_error = ENXIO;
    mp = getmountstruct(dev);
    if (mp == 0)
	u.u_error = EBUSY;	/* This seems like the wrong error code!!
				   But this is the way it's documented,sigh */
    if (u.u_error) 
    {
	iput(ip);
	irele(parent);
	return(NULL);
    }
    bp = geteblk(SBSIZE);
    bzero((caddr_t)bp->b_un.b_addr, SBSIZE);
    if (rmt_fsbufp[mdev])
	panic("rmt_mount: super-block already set");
    rmt_fsbufp[mdev] = bp;
    mp->m_dev = dev;
    mp->m_inodp = ip;
    mp->m_remote = 1;
    mp->m_parent = parent;
    ip->i_flag |= IMOUNT;
    iunlock(ip);
    return(rmt_fsbufp[mdev]->b_un.b_fs);
}


/* 
 *  rmt_unmount:  "unmount" a remote file system. 
 *
 *  dev	= communications channel with the agent process
*/

rmt_unmount(dev)
    dev_t	dev;
{
    register struct mount  *mp;
    register struct inode  *ip;
    register struct buf *bp;
    int mdev;

    for (mp = &mount[0]; mp < &mount[NMOUNT]; mp++)
	if (mp->m_remote && dev == mp->m_dev)
	    goto found;
    return EINVAL;
found: 
    mdev = minor(dev);
    bp = rmt_fsbufp[mdev];
    if (bp == 0)
	panic("rmt_unmount: super-block is null");
    rmt_fsbufp[mdev] = 0;
    brelse(bp);
    ip = mp->m_inodp;
    ip->i_flag &= ~IMOUNT;
    irele(ip);
    irele(mp->m_parent);
    mp->m_dev = 0;
    mp->m_remote = 0;

    if (mp->m_bufp)			/*DEBUG*/
	panic("remote unmount:  buffer pointer not zero!");

    return 0;
}


/* 
 *  setpag:  set process authentication group
*/

setpag() 
{
    int	extra = 0;

    u.u_rmt_pag = time.tv_sec + ++extra;
}
