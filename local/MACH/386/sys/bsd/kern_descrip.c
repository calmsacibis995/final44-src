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
 * $Log:	kern_descrip.c,v $
 * Revision 2.6.3.1  90/04/24  08:08:22  rvb
 * 	Taken from mainline for change Revision 2.7.
 * 	[90/04/20            rvb]
 * 
 * Revision 2.7  90/03/27  18:27:07  dlb
 * 	Split closef() into closef() and freefp().  The latter is called
 * 	by the former and by routines that need to free a file pointer
 * 	that has not been fully initialized (due to open errors, etc.)
 * 	Fix from Mike Kupfer (kupfer@orc.olivetti.com).
 * 	[90/03/26            dlb]
 * 
 * Revision 2.6  89/04/22  15:19:50  gm0w
 * 	Changed to use new inode access macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.5  89/02/25  14:23:50  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  89/02/09  04:30:41  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.3  89/01/18  00:34:43  jsb
 * 	Vnode support.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.2  88/08/24  01:18:06  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  23:10:14  mwyoung]
 * 
 *
 * 18-Aug-87  Peter King (king) at NeXT
 *	MACH_VFS: Merge VFS changes:
 *			Support credentials record user in fd's.
 *
 *  7-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Merge VICE changes -- include vice.h and change to #if VICE.
 *
 * 28-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added check for bogus file reference count in closef (to
 *	hopefully catch RFS bugs).
 *
 *  2-Dec-86  Jay Kistler (jjk) at Carnegie-Mellon University
 *	VICE:  added hooks for ITC/Andrew remote file system.
 *
 * 17-May-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Added explicit hook in flock() into rfs_finode()
 *	for a remote file.
 *	
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 18-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	CS_RFS:  Added explicit hook in fstat() into remote system
 *	call handling.
 *	[V1(1)]
 */
 
#include <mach_rfs.h>
#include <vice.h>

/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)kern_descrip.c	7.1 (Berkeley) 6/5/86
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/kernel.h>
#include <sys/inode.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/mount.h>
#include <sys/stat.h>

#include <sys/ioctl.h>

/*
 * Descriptor management.
 */

/*
 * TODO:
 *	eliminate u.u_error side effects
 */

/*
 * System calls on descriptors.
 */
getdtablesize()
{
	u.u_r.r_val1 = NOFILE;
}

getdopt()
{
}

setdopt()
{
}

dup()
{
	register struct a {
		int	i;
	} *uap = (struct a *) u.u_ap;
	struct file *fp;
	int j;

	if (uap->i &~ 077) { uap->i &= 077; dup2(); return; }	/* XXX */

	GETF(fp, uap->i);
	j = ufalloc(0);
	if (j < 0)
		return;
	dupit(j, fp, u.u_pofile[uap->i] &~ UF_EXCLOSE);
}

dup2()
{
	register struct a {
		int	i, j;
	} *uap = (struct a *) u.u_ap;
	register struct file *fp;

	GETF(fp, uap->i);
	if (uap->j < 0 || uap->j >= NOFILE) {
		u.u_error = EBADF;
		return;
	}
	u.u_r.r_val1 = uap->j;
	if (uap->i == uap->j)
		return;
	if (u.u_ofile[uap->j]) {
		if (u.u_pofile[uap->j] & UF_MAPPED)
			munmapfd(uap->j);
		closef(u.u_ofile[uap->j]);
		if (u.u_error)
			return;
	}
	dupit(uap->j, fp, u.u_pofile[uap->i] &~ UF_EXCLOSE);
}

dupit(fd, fp, flags)
	int fd;
	register struct file *fp;
	register int flags;
{

	u.u_ofile[fd] = fp;
	u.u_pofile[fd] = flags;
	fp->f_count++;
	if (fd > u.u_lastfile)
		u.u_lastfile = fd;
}

/*
 * The file control system call.
 */
fcntl()
{
	register struct file *fp;
	register struct a {
		int	fdes;
		int	cmd;
		int	arg;
	} *uap;
	register i;
	register char *pop;

	uap = (struct a *)u.u_ap;
	GETF(fp, uap->fdes);
	pop = &u.u_pofile[uap->fdes];
	switch(uap->cmd) {
	case F_DUPFD:
		i = uap->arg;
		if (i < 0 || i >= NOFILE) {
			u.u_error = EINVAL;
			return;
		}
		if ((i = ufalloc(i)) < 0)
			return;
		dupit(i, fp, *pop &~ UF_EXCLOSE);
		break;

	case F_GETFD:
		u.u_r.r_val1 = *pop & 1;
		break;

	case F_SETFD:
		*pop = (*pop &~ 1) | (uap->arg & 1);
		break;

	case F_GETFL:
		u.u_r.r_val1 = fp->f_flag+FOPEN;
		break;

	case F_SETFL:
		fp->f_flag &= FCNTLCANT;
		fp->f_flag |= (uap->arg-FOPEN) &~ FCNTLCANT;
		u.u_error = fset(fp, FNDELAY, fp->f_flag & FNDELAY);
		if (u.u_error)
			break;
		u.u_error = fset(fp, FASYNC, fp->f_flag & FASYNC);
		if (u.u_error)
			(void) fset(fp, FNDELAY, 0);
		break;

	case F_GETOWN:
		u.u_error = fgetown(fp, &u.u_r.r_val1);
		break;

	case F_SETOWN:
		u.u_error = fsetown(fp, uap->arg);
		break;

	default:
		u.u_error = EINVAL;
	}
}

fset(fp, bit, value)
	struct file *fp;
	int bit, value;
{

	if (value)
		fp->f_flag |= bit;
	else
		fp->f_flag &= ~bit;
	return (fioctl(fp, (int)(bit == FNDELAY ? FIONBIO : FIOASYNC),
	    (caddr_t)&value));
}

fgetown(fp, valuep)
	struct file *fp;
	int *valuep;
{
	int error;

	switch (fp->f_type) {

	case DTYPE_SOCKET:
		*valuep = ((struct socket *)fp->f_data)->so_pgrp;
		return (0);

	default:
		error = fioctl(fp, (int)TIOCGPGRP, (caddr_t)valuep);
		*valuep = -*valuep;
		return (error);
	}
}

fsetown(fp, value)
	struct file *fp;
	int value;
{

	if (fp->f_type == DTYPE_SOCKET) {
		((struct socket *)fp->f_data)->so_pgrp = value;
		return (0);
	}
	if (value > 0) {
		struct proc *p = pfind(value);
		if (p == 0)
			return (ESRCH);
		value = p->p_pgrp;
	} else
		value = -value;
	return (fioctl(fp, (int)TIOCSPGRP, (caddr_t)&value));
}

fioctl(fp, cmd, value)
	struct file *fp;
	int cmd;
	caddr_t value;
{

	return ((*fp->f_ops->fo_ioctl)(fp, cmd, value));
}

close()
{
	struct a {
		int	i;
	} *uap = (struct a *)u.u_ap;
	register int i = uap->i;
	register struct file *fp;
	register u_char *pf;

	GETF(fp, i);
	pf = (u_char *)&u.u_pofile[i];
	if (*pf & UF_MAPPED)
		munmapfd(i);
	u.u_ofile[i] = NULL;
	while (u.u_lastfile >= 0 && u.u_ofile[u.u_lastfile] == NULL)
		u.u_lastfile--;
	*pf = 0;
	closef(fp);
	/* WHAT IF u.u_error ? */
}

fstat()
{
	register struct file *fp;
	register struct a {
		int	fdes;
		struct	stat *sb;
	} *uap;
	struct stat ub;

	uap = (struct a *)u.u_ap;
	GETF(fp, uap->fdes);
	switch (fp->f_type) {

#if	MACH_RFS
	/*
	 *  The original code probably should have included fstat() in the file
	 *  ops structure in which case these explicit hooks could have been
	 *  avoided but ...
	 */
	case DTYPE_RFSINO:
		u.u_error = rfs_fstat(fp);
		return;
	case DTYPE_RFSCTL:
		u.u_error = rfsC_fstat(fp);
		return;
#endif	MACH_RFS
#if	VICE
	case DTYPE_VICEINO:
		u.u_error = rmt_fstat_fop(fp, uap->sb);
		return;
#endif	VICE
	case DTYPE_INODE:
		u.u_error = STAT_INODE((struct inode *)fp->f_data, &ub);
		break;

	case DTYPE_SOCKET:
		u.u_error = soo_stat((struct socket *)fp->f_data, &ub);
		break;

	default:
		panic("fstat");
		/*NOTREACHED*/
	}
	if (u.u_error == 0)
		u.u_error = copyout((caddr_t)&ub, (caddr_t)uap->sb,
		    sizeof (ub));
}

/*
 * Allocate a user file descriptor.
 */
ufalloc(i)
	register int i;
{

	for (; i < NOFILE; i++)
		if (u.u_ofile[i] == NULL) {
			u.u_r.r_val1 = i;
			u.u_pofile[i] = 0;
			if (i > u.u_lastfile)
				u.u_lastfile = i;
			return (i);
		}
	u.u_error = EMFILE;
	return (-1);
}

ufavail()
{
	register int i, avail = 0;

	for (i = 0; i < NOFILE; i++)
		if (u.u_ofile[i] == NULL)
			avail++;
	return (avail);
}

struct	file *lastf;
/*
 * Allocate a user file descriptor
 * and a file structure.
 * Initialize the descriptor
 * to point at the file structure.
 */
struct file *
falloc()
{
	register struct file *fp;
	register i;

	i = ufalloc(0);
	if (i < 0)
		return (NULL);
	if (lastf == 0)
		lastf = file;
	for (fp = lastf; fp < fileNFILE; fp++)
		if (fp->f_count == 0)
			goto slot;
	for (fp = file; fp < lastf; fp++)
		if (fp->f_count == 0)
			goto slot;
	tablefull("file");
	u.u_error = ENFILE;
	return (NULL);
slot:
	u.u_ofile[i] = fp;
	fp->f_count = 1;
	fp->f_data = 0;
	fp->f_offset = 0;
	u.u_identity->id_ref++;
	fp->f_identity = u.u_identity;
	lastf = fp + 1;
	return (fp);
}

/*
 * Convert a user supplied file descriptor into a pointer
 * to a file structure.  Only task is to check range of the descriptor.
 * Critical paths should use the GETF macro.
 */
struct file *
getf(f)
	register int f;
{
	register struct file *fp;

	if ((unsigned)f >= NOFILE || (fp = u.u_ofile[f]) == NULL) {
		u.u_error = EBADF;
		return (NULL);
	}
	return (fp);
}

/*
 * Internal form of close.
 * Decrement reference count on file structure.  Cleanup if zero.
 */
closef(fp)
	register struct file *fp;
{

	if (fp == NULL)
		return;
	if (fp->f_count > 1) {
		fp->f_count--;
		return;
	}
	if (fp->f_count != 1)
		panic("closef: f_count not 1");
	(*fp->f_ops->fo_close)(fp);
	freefp(fp);
}
  
/* 
 * Mark file table slot as unused and free any objects that it holds.  
 * Most code should use closef, except when cleaning up after a 
 * partially-completed operation.
 */
freefp(fp)
register struct file *fp;
{
	if (fp == NULL)
		return;
	if (fp->f_count != 1)
		panic("freefp: f_count not 1");
	if (!fp->f_identity)
		panic("freefp: no identity");
  
	free_identity(fp->f_identity);
	fp->f_identity = NULL;
	fp->f_count = 0;
}


/*
 * Apply an advisory lock on a file descriptor.
 */
flock()
{
	register struct a {
		int	fd;
		int	how;
	} *uap = (struct a *)u.u_ap;
	register struct file *fp;

	GETF(fp, uap->fd);
	if (fp->f_type != DTYPE_INODE) {
#if	MACH_RFS
		/*
		 *  Perform remote system call handling if necessary.
		 */
		if (fp->f_type == DTYPE_RFSINO)
		{
			extern struct file *rfs_finode();

			(void) rfs_finode(fp);
		}
		else
#endif	MACH_RFS
#if	VICE
		/*
		 *  Perform ITC/Andrew remote system call handling if necessary.
		 */
		if (fp->f_type == DTYPE_VICEINO)
		{
			extern struct file *rmt_fdes();

			(void) rmt_fdes(fp);
		}
		else
#endif	VICE
		u.u_error = EOPNOTSUPP;
		return;
	}
	if (uap->how & LOCK_UN) {
		UNLOCK_FILE(fp, FSHLOCK|FEXLOCK);
		return;
	}
	if ((uap->how & (LOCK_SH | LOCK_EX)) == 0)
	{
		u.u_error = EINVAL;
		return;
	}
	if (uap->how & LOCK_EX)
		uap->how &= ~LOCK_SH;
	/* avoid work... */
	if ((fp->f_flag & FEXLOCK) && (uap->how & LOCK_EX) ||
	    (fp->f_flag & FSHLOCK) && (uap->how & LOCK_SH))
		return;
	u.u_error = LOCK_FILE(fp, uap->how);
}
