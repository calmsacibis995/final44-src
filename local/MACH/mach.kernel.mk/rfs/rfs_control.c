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
 * $Log:	rfs_control.c,v $
 * Revision 2.10  91/11/05  18:27:54  mja
 * 	Also clear new RFSWHO_EXPTKTFILE and RFSWHO_NOTKTFILE flags on
 * 	re-kinit.
 * 	[91/11/05  00:40:00  mja]
 * 
 * Revision 2.9  91/09/01  17:38:28  berman
 * 	Initialize buffer length when writing and allow read without an
 * 	identity record in order to fix LOOKUP mode in rfsC_rw() which
 * 	had been broken by the introduction of TKTFILE mode there.
 * 	[91/08/31  18:03:41  mja]
 * 
 * Revision 2.8  91/08/01  15:25:30  berman
 * 	Put back the old auth control modes and make them no-ops.
 * 	Same with IDENTIFY.
 * 	Use the new MAXTKTFILELEN define.
 * 	[91/07/31  23:23:25  chs]
 * 
 * 	Try to keep the reference counts on ticket file names accurately...
 * 	only create a new structure if the name we're setting is different
 * 	from the current name.
 * 	[91/07/27  17:10:19  chs]
 * 
 * 	Changed behaviour in the case where we set the ticket file name
 * 	to be correct now that we are destroying unused ticket files.
 * 	[91/07/23  15:37:58  chs]
 * 
 * 	Added support for kerberos authentication.
 * 	Removed support for IDENTIFY ioctl, which didn't work anyway.
 * 	Added two new ioctls, NEWTKT and CACHESOCK.
 * 	[91/07/22  11:48:12  chs]
 * 
 * Revision 2.7  89/04/22  15:26:45  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.6  89/03/15  15:13:25  gm0w
 * 	changed include sys/rfs.h to rfs/rfs/h
 * 
 * Revision 2.5  89/02/25  14:44:40  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  89/02/09  04:32:13  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.3  89/01/18  00:38:20  jsb
 * 	Vnode support.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.2  88/08/24  01:22:31  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Removed RFS conditional entirely... this file isn't built unless
 * 	CMUCS_RFS is specified.
 * 	[88/08/23            mwyoung]
 * 
 *
 *  1-Mar-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Prevent compiler schain botch.
 *
 * 05-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added new RFSRW_LOOKUP mode which a privileged process can use
 *	to extract the remote portion of an apparently local pathname
 *	by writing the local pathname to the control file and reading
 *	back any local portion.
 *	[ V5.1(F2) ]
 *
 * 20-May-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created.
 *
 */

/*	rfs_control.c	CMU	86/05/20	*/

/*
 *  Remote file system - control operations module
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/ioctl.h>
#include <sys/tty.h>
#include <sys/dir.h>
#include <sys/file.h>
#include <sys/inode.h>
#include <sys/user.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <rfs/rfs.h>
#include <sys/inode.h>



/*
 *  rfsC_rw - common read/write call handling
 *
 *  fp   = file pointer
 *  rw   = read/write flag
 *  uiop = user I/O descriptor
 *
 *  Return: 0 on success or an error number as appropriate.
 */

rfsC_rw(fp, rw, uiop)
    struct file *fp;
    enum uio_rw rw;
    struct uio *uiop;
{
    register struct rfsProcessEntry *rpep = rfsCurrentProcessEntry;
    register struct rfsWho *rwp;
    register struct buf *bufp;
    register char *base;
    long tmplen;
    long *lenp;
    int error = 0;
    char tmpbuf[MAXTKTFILELEN];

    rfs_printf3(RFSD_S_TRACEIN, "<RWC %s(f=%X)\n", syscallnames[u.u_rfscode], fp);

    rwp = rpep->rpe_rwp;
    switch (rpep->rpe_rw)
    {
	case RFSRW_LOOKUP:
	{
	    if (rw == UIO_WRITE)
	    {
		if (rpep->rpe_bufp == NULL)
		    rpep->rpe_bufp = geteblk(MAXPATHLEN);
		rpep->rpe_bufp->b_bcount = MAXPATHLEN-1;
	    }
	    else
	    {
		if (rpep->rpe_bufp == NULL || (rpep->rpe_bufp->b_flags&B_ERROR) != 0)
		{
		    error = EINVAL;
		    goto out;
		}
	    }
	    bufp  = rpep->rpe_bufp;
	    base  = bufp->b_un.b_addr;
	    lenp = &(bufp->b_bcount);
	    break;
	}
	case RFSRW_TKTFILE:
	{
	    if (rw == UIO_WRITE) {
		base = (caddr_t) tmpbuf;
		tmplen = sizeof(tmpbuf);
		lenp = &tmplen;
	    }
	    else {
		if (rwp) {
		    base = rwp->rw_tktfile;
		    tmplen = rwp->rw_ltktfile;
		    lenp = &tmplen;
		} else
		    goto out;
	    }
	    break;
	}
	case RFSRW_NONE:
	{
	    error = EINVAL;
	    goto out;
	}
	case RFSRW_USER:
	case RFSRW_GROUP:
	case RFSRW_ACCOUNT:
	case RFSRW_PASSWORD:
	    goto out;

	default:
	    panic("rfsC_rw");
	    /*NOTREACHED*/
    }
    uiop->uio_offset = 0;
    error = uiomove(base, *lenp, rw, uiop);
    if (rw == UIO_WRITE)
    {
	*lenp  = uiop->uio_offset;
	if (error == 0) {
	    switch (rpep->rpe_rw) {
	      case RFSRW_LOOKUP:
		base[bufp->b_bcount] = 0;
		rfsCLookup(bufp);
		break;
	      case RFSRW_TKTFILE:
		if (rwp == NULL || rwp->rw_ltktfile == 0 ||
		    tmplen != rwp->rw_ltktfile ||
		    bcmp(tmpbuf, rwp->rw_tktfile, tmplen) != 0) {

		    /* only change the ticket file name if it's actually
		       different */

		    rwp = rfsWhoAllocate();
		    if (rwp == NULL)
			return(ENOBUFS);
		    bzero((caddr_t)rwp, sizeof(*rwp));
		    if (rpep->rpe_rwp) {
			rfsDetachWho(rpep->rpe_rwp);
		    }
		    rwp->rw_refc = 1;
		    rpep->rpe_rwp = rwp;

		    bcopy(tmpbuf, rwp->rw_tktfile, tmplen);
		    rwp->rw_ltktfile = tmplen;
		}
		break;
	    }
	}
    }
out:
    rfs_printf2(RFSD_S_TRACEOUT, ">RWC  %d\n", error);
    return(error);
}



/*
 *  rfsCLookup - lookup a pathname to determine if it is non-local
 *
 *  bufp = buffer for pathname
 */

rfsCLookup(bufp)
    register struct buf *bufp;
{
    struct inode *ip;
    NAME_CLOOKUP_DECL;

    NAME_CLOOKUP(bufp->b_un.b_addr, ip);
    if (ip != NULL)
    {
	FINISH_WITH_INODE(ip);
    }
    else
    {
	if (u.u_error == ERANGE)
	{
	    u.u_error = copystr(NAME_LOOKUP_PATH, bufp->b_un.b_addr,
			        MAXPATHLEN, &bufp->b_bcount);
	}
    }
    NAME_LOOKUP_FREE();
    if (u.u_error)
    {
	u.u_error = 0;
	bufp->b_flags |=  B_ERROR;
    }
    else
    {
	bufp->b_flags &= ~B_ERROR;
	bufp->b_bcount--;
    }
}



/*
 *  rfsC_ioctl - remote control ioctl() call
 *
 *  fp   = file pointer
 *  cmd  = ioctl command to execute
 *  data = pointer to argument block
 *
 *  Return: 0 on success or an error number as appropriate.
 */

rfsC_ioctl(fp, cmd, data)
    struct file *fp;
    int cmd;
    caddr_t data;
{
	    register struct rfsConnectionQueue *rcbqp;
	    register struct rfsConnectionBlock *rcbp;
    register struct rfsProcessEntry *rpep = rfsCurrentProcessEntry;
    int error = 0;

    rfs_printf4(RFSD_S_TRACEIN, "<IocC cmd=%X data=%X (f=%X)\n", cmd, *(int *)data, fp);
    switch (cmd)
    {
	case RFSIOCGETRW:
	{
	    *(rfsRW_t *)data = rpep->rpe_rw;
	    break;
	}
	case RFSIOCSETRW:
	{
	    switch (*(rfsRW_t *)data)
	    {
		case RFSRW_NONE:
		    u.u_rfs &= ~URFS_EROOT;
		    if (rpep->rpe_bufp)
		    {
			struct buf *bufp = rpep->rpe_bufp;

			rpep->rpe_bufp = NULL;
			brelse(bufp);
		    }
		    goto common;

		case RFSRW_LOOKUP:
		    if (!suser())
		    {
			error = u.u_error;
			break;
		    }
		    u.u_rfs |= URFS_EROOT;
		    goto common;

		case RFSRW_TKTFILE:
		case RFSRW_USER:
		case RFSRW_GROUP:
		case RFSRW_ACCOUNT:
		case RFSRW_PASSWORD:
		common:
		    rpep->rpe_rw = *(rfsRW_t *)data;
		    break;

		default:
		    error = EINVAL;
		    break;
	    }
	    break;
	}
	case RFSIOCNEWTKT:
	{
	    struct rfsWho *rwp = rpep->rpe_rwp;

	    if (rwp)
		rwp->rw_flags &= ~(RFSWHO_BADTKTFILE|RFSWHO_EXPTKTFILE|RFSWHO_NOTKTFILE);
	    break;
	}
	case RFSIOCCACHESOCK:
	{
	    extern char ticketd_socket_path[];
	    extern struct inode *ticketd_ip;
	    struct inode *ip;
	    register struct socket *so;

	    /* this code is stolen from bsd/uipc_usrreq.c */
	    CONNECT_TO_INODE(ticketd_socket_path, ip);
	    if (!INODE_TYPE(ip,SOCK)) {
		error = ENOTSOCK;
		break;
	    }
	    so = ip->i_socket;
	    if (so == 0) {
		error = ECONNREFUSED;
		break;
	    }
	    if (so->so_type != SOCK_STREAM) {
		error = EPROTOTYPE;
		break;
	    }
	    if ((so->so_options&SO_ACCEPTCONN) == 0) {
		error = ECONNREFUSED;
		break;
	    }

	    if (ticketd_ip)
		FINISH_WITH_INODE(ticketd_ip);

	    ticketd_ip = ip;
	    break;
        }
        case RFSIOCIDENTIFY:
	    break;
	default:
	{
	    error = EINVAL;
	    break;
	}
    }
    rfs_printf2(RFSD_S_TRACEOUT, ">IocC %d\n", error);
    return(error);
}



/*
 *  rfsC_select - remote control select() call
 *
 *  fp   = file pointer
 *  flag = read/write flag
 *
 *  Return: TRUE always (for now).
 *
 *  TODO:  finish this (somehow)
 */

/* ARGSUSED */
rfsC_select(fp, flag)
    struct file *fp;
    int flag;
{
    return(1);
}



/*
 *  rfs_close - remote control close() call
 *
 *  fp = file pointer
 */

rfsC_close(fp)
    struct file *fp;
{
    register struct rfsProcessEntry *rpep = rfsCurrentProcessEntry;

#ifdef	lint
    if (fp)
	;
#endif	lint
    /*
     *  Release any pathname buffer and clear error mode.
     */
    if (rpep->rpe_bufp)
    {
	struct buf *bufp = rpep->rpe_bufp;

	rpep->rpe_bufp = NULL;
	brelse(bufp);
    }
    u.u_rfs &= ~URFS_EROOT;
    return(0);
}



/*
 *  Remote control file descriptor operations dispatch table.
 *
 *  This is the table used by most standard file descriptor based system calls
 *  to dispatch to the proper processing routines (above) when the descriptor
 *  type is DTYPE_RFSCTL.
 */

struct 	fileops rfsCops =
	{ rfsC_rw, rfsC_ioctl, rfsC_select, rfsC_close };




/*
 *  rfsC_fstat - remote control fstat() call
 *
 *  fp  = file pointer
 *
 *  N.B.  This call is an explicit hook from fstat().
 *
 *  Return: EINVAL (always) for now.
 */

rfsC_fstat(fp)
    struct file *fp;
{
#ifdef	notdef
    register struct a {
	    int	fdes;
	    struct	stat *sb;
    } *uap = (struct a *)u.u_ap;
#endif	notdef

#ifdef	lint
    if (fp++) ;
#endif	lint

    return(EINVAL);
}
