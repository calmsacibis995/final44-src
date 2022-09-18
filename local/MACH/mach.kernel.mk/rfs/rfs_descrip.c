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
 * $Log:	rfs_descrip.c,v $
 * Revision 2.8  90/07/03  16:46:50  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:11:30  mrt]
 * 
 * Revision 2.7  89/07/30  18:36:56  gm0w
 * 	Added getdirentries support to RFS.
 * 	[89/07/29            gm0w]
 * 
 * Revision 2.6  89/03/15  15:13:40  gm0w
 * 	changed include sys/rfs.h to rfs/rfs/h
 * 
 * Revision 2.5  89/02/25  14:44:47  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  89/02/09  04:32:16  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.3  89/01/18  00:38:43  jsb
 * 	Vnode support.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.2  88/08/24  01:23:23  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 	
 * 	Removed RFS conditional entirely... this file isn't built unless
 * 	CMUCS_RFS is specified.
 * 	[88/08/23            mwyoung]
 * 
 * 20-Jul-87  David Black (dlb) at Carnegie-Mellon University
 *	Removed Multimax compiler bug workaround.  Conversion of
 *	cpu_number() to a macro causes bug not to be tickled.
 *
 * 05-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed rfsRdWr() to use new rfsUIOReceive() and rfsUIOSend()
 *	routines which perform socket I/O with appropriate timeouts
 *	and/or signal recovery and to perform a non-local goto on exit
 *	if the routine was interrupted by a signal.
 *	[ V5.1(F5) ]
 *
 * 05-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Updated to zero pathname buffer pointer in U area for file
 *	descriptor based calls which should never allow a local
 *	pathname reply back from the remote server.
 *	[ V5.1(F2) ]
 *
 *  3-Nov-86  David L. Black (dlb) at Carnegie-Mellon University
 *	Added compiler bug workaround for Multimax
 *
 * 13-Dec-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Reorganized for new RFS name.
 *
 * 18-Jul-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Begin conversion for 4.2BSD.
 *
 * 20-Jan-82  Mike Accetta (mja) at Carnegie-Mellon University
 *	Created.
 *
 */

/*	rfs_descrip.c	CMU	82/01/20	*/

/*
 *  Remote file system - file descriptor based operations module
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



/*
 *  rfs_rw - common read/write call handling
 *
 *  fp   = file pointer
 *  rw   = read/write flag
 *  uiop = user I/O descriptor
 *
 *  Return: 0 on success or an error number as appropriate.
 */

rfs_rw(fp, rw, uiop)
    struct file *fp;
    enum uio_rw rw;
    struct uio *uiop;
{
    int error;
    int type;

    rfs_printf3(RFSD_S_TRACEIN, "<RW   %s(f=%X)\n", syscallnames[u.u_rfscode], fp);
    if (rw == UIO_READ && u.u_rfscode == RFST_READ)
	type = RFST_READ;
    else if (rw == UIO_READ)
	type = RFST_GETDIRENTS;
    else
	type = RFST_WRITE;
    error = rfsRdWr((struct rfsFileEntry *)fp->f_data, uiop, type);
    rfs_printf2(RFSD_S_TRACEOUT, ">RW   %d\n", error);
    return(error);
}



/*
 *  rfsRdWr - perform remote read/write operation
 *
 *  rfep = remote file entry
 *  uiop = user I/O descriptor
 *  type = read/write message type
 *
 *  Send the appropriate read or write message and process the reply.
 *
 *  Return: 0 on success with the user I/O descriptor updated or an error
 *  number as appropriate.
 */

rfsRdWr(rfep, uiop, type)
    register struct rfsFileEntry *rfep;
    struct uio *uiop;
    int type;
{
    register struct rfsConnectionBlock *rcbp = rfep->rfe_rcbp;
    struct rfsMsg rmsg;
    unsigned count;
    int error;

    rmsg.rmsg_A_code = type;
    rmsg.rmsg_A_desc = rfep->rfe_desc;
    rmsg.rmsg_A_ul_param = count = uiop->uio_resid;
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, &rmsg, sizeof (rmsg.rmsg_header)))
    {
	rfsError(rcbp);
	return(error);
    }
    *ni_nbpp(&u.u_nd) = 0;
    if (type == RFST_READ || type == RFST_GETDIRENTS)
    {
	if (error = rfsReceive(rcbp, &rmsg, sizeof (rmsg.rmsg_header), type))
	{
	    rfsError(rcbp);
	    return(error);
	}
	if (rmsg.rmsg_errno)
	{
	    rfsUnLock(rcbp);
	    return(error);
	}
	while (rmsg.rmsg_rval)
	{
	    unsigned ucount;

	    ucount = uiop->uio_resid;
	    error = rfsUIOReceive(rcbp, uiop);
	    if (error)
		break;
	    rmsg.rmsg_rval -= ucount-uiop->uio_resid;
	}
    }
    else
    {
	error = rfsUIOSend(rcbp, uiop);
	if (error)
	{
	    rfsError(rcbp);
	    rfs_printf2(RFSD_PROTOCOL, "*RdWr %d\n", error);
	    return(error);
	}
	if (error = rfsReceive(rcbp, &rmsg, sizeof(rmsg.rmsg_header), RFST_WRITE))
	{
	    rfsError(rcbp);
	    rfs_printf2(RFSD_PROTOCOL, "*RdWr %d\n", error);
	    return(error);
	}
	error = rmsg.rmsg_errno;
	uiop->uio_resid = count - rmsg.rmsg_rval;
    }
    rfsUnLock(rcbp);
    /*
     *  If a signal caused us to abort out of the system call, we handled it
     *  specially and must now reflect it correctly through the regular system
     *  call processing.  This is done here so that the lower level routines
     *  where the signal is first trapped need not concern themselves with any
     *  state that may need to be cleaned up by their callers back to this
     *  point.
     */
    if (rcbp->rcb_flags&RFSF_EINTR)
    {
	rcbp->rcb_flags &= ~RFSF_EINTR;
	longjmp(&u.u_qsave);
    }
    return(error);
}



/*
 *  rfs_ioctl - remote ioctl() call
 *
 *  fp   = file pointer
 *  cmd  = ioctl command to execute
 *  data = pointer to argument block
 *
 *  Return: 0 on success or an error number as appropriate.
 */

rfs_ioctl(fp, cmd, data)
    struct file *fp;
    int cmd;
    caddr_t data;
{
    struct rfsFileEntry *rfep = (struct rfsFileEntry *)fp->f_data;
    struct rfsConnectionBlock *rcbp = rfep->rfe_rcbp;
    struct rfsMsg *rmsgp;
    u_short size;
    int error;
    caddr_t kalloc();

    rfs_printf3(RFSD_S_TRACEIN, "<Ioct %s(f=%X)\n", syscallnames[u.u_rfscode], fp);
    size = IOCPARM_LEN(cmd);
    if (size > IOCPARM_MAX)
	return(EFAULT);
    rmsgp = (struct rfsMsg *)kalloc(sizeof(union rmsg_header) + size);
    if (rmsgp == NULL)
	panic("rfs_ioctl kalloc");
    rmsgp->rmsg_B_code = RFST_IOCTL;
    rmsgp->rmsg_B_desc = rfep->rfe_desc;
    rmsgp->rmsg_B_l_param = cmd;
    rmsgp->rmsg_B_bsize = size;
    if (size)
    {
	if (cmd&IOC_IN)
	    bcopy(data, (caddr_t)rmsgp->rmsg_B_buff, size);
	else
	    bzero((caddr_t)rmsgp->rmsg_B_buff, size);
    }
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, rmsgp, sizeof(union rmsg_header) + size))
    {
	rfsError(rcbp);
	goto out;
    }
    *ni_nbpp(&u.u_nd) = 0;
    if (error = rfsReceive(rcbp, rmsgp, sizeof(union rmsg_header) + size, RFST_IOCTL))
    {
	rfsError(rcbp);
	goto out;
    }
    rfsUnLock(rcbp);
    if ((error = rmsgp->rmsg_errno) == 0)
    {
	u.u_r.r_val1 = rmsgp->rmsg_rval;
	if ((cmd&IOC_OUT) && size)
	    bcopy(rmsgp->rmsg_B_buff, (caddr_t)data, size);
    }
out:
    kfree(rmsgp, sizeof(union rmsg_header) + size);
    rfs_printf2(RFSD_S_TRACEOUT, ">Ioct %d\n", error);
    /*
     *  Same as above.
     */
    if (rcbp->rcb_flags&RFSF_EINTR)
    {
	rcbp->rcb_flags &= ~RFSF_EINTR;
	longjmp(&u.u_qsave);
    }
    return(error);
}



/*
 *  rfs_select - remote select() call
 *
 *  fp   = file pointer
 *  flag = read/write flag
 *
 *  Return: TRUE always (for now).
 *
 *  TODO:  finish this (somehow)
 */

/* ARGSUSED */
rfs_select(fp, flag)
    struct file *fp;
    int flag;
{
    return(1);
}



/*
 *  rfs_close - remote close() call
 *
 *  fp = file pointer
 */

rfs_close(fp)
    struct file *fp;
{
    struct rfsFileEntry *rfep = (struct rfsFileEntry *)fp->f_data;
    struct rfsConnectionBlock *rcbp = rfep->rfe_rcbp;
    struct rfsMsg rmsg;
    int error;

    rfs_printf4(RFSD_S_TRACEIN, "<Clse f=%X(rfe=%X,rcb=%X)\n", fp, rfep, rcbp);
    rmsg.rmsg_A_code = RFST_CLOSE;
    rmsg.rmsg_B_desc = rfep->rfe_desc;
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, &rmsg, sizeof (rmsg.rmsg_header)))
    {
	rfsError(rcbp);
	goto out;
    }
    *ni_nbpp(&u.u_nd) = 0;
    if (error = rfsReceive(rcbp, &rmsg, sizeof (rmsg.rmsg_header), RFST_CLOSE))
    {
	rfsError(rcbp);
	goto out;
    }
    rfsUnLock(rcbp);
    error = rmsg.rmsg_errno;
out:
    rfsFileFree(rfep);
    rfsDetach(rcbp);
    rfs_printf2(RFSD_S_TRACEOUT, ">Clse %d\n", error);
    return(error);
}



/*
 *  Remote file descriptor operations dispatch table.
 *
 *  This is the table used by most standard file descriptor based system calls
 *  to dispatch to the proper processing routines (above) when the descriptor
 *  type is DTYPE_RFSINO.
 */

struct 	fileops rfsops =
	{ rfs_rw, rfs_ioctl, rfs_select, rfs_close };




/*
 *  rfs_open - remote open() call
 *
 *  rcbp = remote connection block
 *
 *  Return: NULL always with u.u_error set as appropriate.
 */

struct inode *
rfs_open(rcbp, nip)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
{
    struct a {
	char	*fname;
	int	mode;
	int	crtmode;
    } *uap = (struct a *) u.u_ap;

    return(rfs_copen(rcbp, nip, RFST_OPEN, uap->mode, uap->crtmode));
}



/*
 *  rfs_creat - remote creat() call
 *
 *  rcbp = remote connection block
 *
 *  Return: NULL always with u.u_error set as appropriate.
 */

struct inode *
rfs_creat(rcbp, nip)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
{
    struct a {
	char	*fname;
	int	fmode;
    } *uap = (struct a *)u.u_ap;

    return(rfs_copen(rcbp, nip, RFST_CREAT, FWRITE|FCREAT|FTRUNC, uap->fmode));
}



/*
 *  rfs_copen - common code for open and creat
 *
 *  rcbp = remote connection block
 *  nip  = namei structure for name
 *  type = open/creat type
 *  arg1 = first open/creat argument
 *  arg2 = second open/creat argument
 *
 *  Perform the remote open or create operation and if successfull allocate a
 *  file descriptor to record the remote connection for the now open file.
 *  If the open/create is for a control operation, just initialize the open
 *  file for future control operations without any network activity.
 *
 *  Return: NULL always with u.u_error set as appropriate.
 */

struct inode *
rfs_copen(rcbp, nip, type, arg1, arg2)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
    short type;
    short arg1;
    short arg2;
{
    register struct file *fp = u.u_ofile[u.u_r.r_val1];
    extern struct fileops rfsCops;

    /*
     *  A control file is indicated by a zero IP address contents in the link
     *  file.
     */
    if (rcbp->rcb_addr.s_addr == INADDR_ANY)
    {
	fp->f_type = DTYPE_RFSCTL;
	fp->f_ops  = &rfsCops;
	fp->f_data = 0;
    }
    else
    {
	struct rfsFileEntry *rfep;

	rfep = rfsOpCr(rcbp, nip, type, arg1, arg2);
	if (rfep == NULL)
	    goto out;
	fp->f_type = DTYPE_RFSINO;
	fp->f_ops  = &rfsops;
	fp->f_data = (caddr_t)rfep;
    }
    fp->f_offset = 0;
    if (type == RFST_OPEN)
	fp->f_flag = (arg1-FOPEN)&FMASK;
    else
	fp->f_flag = FWRITE;
out:
    return(NULL);
}



/*
 *  rfsOpCr - perfrom remote open or creatre operation
 *
 *  rcbp = remote connection block
 *  nip  = namei structure for name
 *  type = message type to send
 *  arg1 = first open/creat argument
 *  arg2 = second open/creat argument
 *
 *  Send the appropriate open or create message on the remote connection and
 *  create a new connection to use thereafter for the newly open file.
 *  The password field is zeroed in the new connection block since it won't
 *  be needed on that connection and it would be cumbersome to track the
 *  connection done later if we needed to zero it (such as before a reboot).
 *
 *  Return: the new remote connection block or NULL on error with u.u_error set
 *  as appropriate.
 */

struct rfsFileEntry *
rfsOpCr(rcbp, nip, type, arg1, arg2)
    register struct rfsConnectionBlock *rcbp;
    struct nameidata *nip;
    short type;
    short arg1;
    short arg2;
{
    register struct rfsFileEntry *rfep = NULL;
    register int len;
    struct rfsMsg rmsg;
    int error;

    rfs_printf4(RFSD_P_TRACEIN, "<OpCr t=%d,args=%o,%o\n", type, arg1, arg2);
    if ((rcbp->rcb_cmask != u.u_cmask) && (arg1&FCREAT))
    {
	error = rfsUmask(rcbp);
	if (error)
	    goto fail;
    }
    rmsg.rmsg_M_code = type;
    rmsg.rmsg_M_s_param1 = arg1;
    rmsg.rmsg_M_s_param2 = arg2;
    len = rfsNameLength(nip);
    if (len < 0)
    {
	rfs_printf2(RFSD_P_TRACEOUT, ">OpCr %d\n", u.u_error);
	return(NULL);
    }
    if ((rfep = rfsFileAllocate()) == NULL)
    {
	rfs_printf1(RFSD_P_TRACEOUT, "*OpCr (rfep)\n");
	error = ENOBUFS;
	goto out;
    }
    rmsg.rmsg_M_len = len;
    rfsLock(rcbp);
    error = rfsSend(rcbp, &rmsg, sizeof(rmsg.rmsg_header));
    if (error)
	goto fail;
    error = rfsSendString(rcbp, nip->ni_dirp, rmsg.rmsg_M_len);
    if (error)
	goto fail;
    error = rfsReceive(rcbp, &rmsg, sizeof (rmsg.rmsg_header), type);
    if (error)
	goto fail;
    rfsUnLock(rcbp);
    if (error = rmsg.rmsg_errno)
	goto out;
    rfep->rfe_desc = rmsg.rmsg_rval;
    rfep->rfe_rcbp = rcbp;
    rfsIncrCheck(rcbp);
    rfs_printf2(RFSD_P_TRACEOUT, ">OpCr rcb=%X\n", rcbp);
    return(rfep);

fail:
    rfsError(rcbp);
out:
    if (rfep)
	rfsFileFree(rfep);
    u.u_error = error;
    rfs_printf2(RFSD_P_TRACEOUT, ">OpCr %d\n", error);
    return(NULL);
}



/*
 *  rfs_finode - non fileops file descriptor call processing
 *
 *  fp = file descriptor
 *
 *  Dispatch through namei dispatch table to appropriate processing routine.
 *
 *  Return: NULL (always) with u.u_error set as appropriate.
 */

struct file *
rfs_finode(fp)
    struct file *fp;
{

    rfs_printf3(RFSD_S_TRACEIN, "<Fino %s(f=%X)\n", syscallnames[u.u_rfscode], fp);
    (void)(*(rfs_sysent[u.u_rfscode]))((struct rfsFileEntry *)fp->f_data);
    if (u.u_error == 0)
	u.u_error = ERFSREMOTE;
    rfs_printf2(RFSD_S_TRACEOUT, ">Fino %d\n", u.u_error);
    return(NULL);
}



/*
 *  rfs_lseek - remote lseek() call
 *
 *  rcbp = remote control block
 *
 *  Return: NULL (always) with u.u_error set as appropriate.
 */

struct inode *
rfs_lseek(rfep)
    register struct rfsFileEntry *rfep;
{
    register struct a {
	int	fd;
	off_t	off;
	int	sbase;
    } *uap = (struct a *)u.u_ap;

    u.u_error = rfsLseek(rfep, uap->off, uap->sbase, &u.u_r.r_off);
    return(NULL);
}



/*
 *  rfsLseek - perform remote lseek operation
 *
 *  rfep  = remote file entry
 *  off   = offset to seek to
 *  sbase = base for seek
 *  offp  = pointer for returned offset value
 *
 *  Perform the remote lseek operation and return its result in the supplied
 *  pointer.
 *
 *  Return: 0 or an error number as appropriate.
 */

rfsLseek(rfep, off, sbase, offp)
    struct rfsFileEntry *rfep;
    off_t off;
    int sbase;
    off_t *offp;
{
    struct rfsConnectionBlock *rcbp = rfep->rfe_rcbp;
    struct rfsMsg rmsg;
    int error;

    rmsg.rmsg_A_code = RFST_LSEEK;
    rmsg.rmsg_A_desc = rfep->rfe_desc;
    rmsg.rmsg_A_ul_param = off;
    rmsg.rmsg_A_s_param = sbase;
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, &rmsg, sizeof (rmsg.rmsg_header)))
    {
	rfsError(rcbp);
	goto fail;
    }
    *ni_nbpp(&u.u_nd) = 0;
    if (error = rfsReceive(rcbp, &rmsg, sizeof (rmsg.rmsg_header), RFST_LSEEK))
    {
	rfsError(rcbp);
	goto fail;
    }
    rfsUnLock(rcbp);
    if ((error = rmsg.rmsg_errno) == 0)
	*offp = rmsg.rmsg_rval;
fail:
    return(error);
}



/*
 *  rfs_fstat - remote fstat() call
 *
 *  fp  = file pointer
 *
 *  N.B.  This call is an explicit hook from fstat().
 *
 *  Return: 0 or an error number as appropriate.
 */

rfs_fstat(fp)
    struct file *fp;
{
    register struct rfsFileEntry *rfep = (struct rfsFileEntry *)fp->f_data;
    register struct rfsConnectionBlock *rcbp = rfep->rfe_rcbp;
    register struct a {
	    int	fdes;
	    struct	stat *sb;
    } *uap = (struct a *)u.u_ap;

    rfs_printf3(RFSD_S_TRACEIN, "<SysC %s(f=%X)\n", syscallnames[u.u_rfscode], fp);
    (void) rfs_stat1(rcbp, (struct nameidata *)NULL, rfep->rfe_desc, uap->sb, RFST_NFSTAT, 0);
    rfs_printf2(RFSD_S_TRACEOUT, ">SysC %d\n", u.u_error);
    return(u.u_error);
}



/*
 *  rfs_ofstat - remote ofstat() call
 *
 *  rcbp = remote connection blcok
 *
 *  Return: NULL (always) with u.u_error set as appropriate.  
 */

struct inode *
rfs_ofstat(rfep)
    struct rfsFileEntry *rfep;
{
    register struct a {
	    int	fdes;
	    struct	stat *sb;
    } *uap = (struct a *)u.u_ap;

    return(rfs_stat1(rfep->rfe_rcbp, (struct nameidata *)NULL, rfep->rfe_desc, uap->sb, RFST_OFSTAT, sizeof(struct stat)-32));
}



/*
 *  rfs_sysdesccall - common protocol handling for system calls on a descriptor
 *
 *  rcbp = remote connection
 *
 *  Currently handles: fchmod(), fchown(), flock(), fsync(), ftruncate().
 *
 *  Return: NULL (always) with u.u_error set as appropriate.
 *
 *  TODO:  merge common handling for other calls.
 */

struct inode *
rfs_sysdesccall(rfep)
    register struct rfsFileEntry *rfep;
{
    register struct rfsConnectionBlock *rcbp = rfep->rfe_rcbp;
    struct rfsMsg rmsg;
    register u_int mlen = sizeof(rmsg.rmsg_header);
    int code = u.u_rfscode;
    int error;

    rmsg.rmsg_A_code = code;
    rmsg.rmsg_A_desc = rfep->rfe_desc;
    switch(code)
    {
	case RFST_FSYNC:
	{
	    rmsg.rmsg_A_s_param = 0;
	    rmsg.rmsg_A_ul_param = 0;
	    break;
	}
	case RFST_FCHOWN:
	{
	    rmsg.rmsg_A_ul_param = u.u_ap[1];
	    rmsg.rmsg_A_s_param = u.u_ap[2];
	    break;
	}
	case RFST_FLOCK:
	case RFST_FCHMOD:
	case RFST_FTRUNCATE:
	{
	    rmsg.rmsg_A_s_param = 0;
	    rmsg.rmsg_A_ul_param = u.u_ap[1];
	    break;
	}
        default:
	{
	    panic("rfs_sysdesccall");
	    break;
	}
    }
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, &rmsg, mlen))
	goto fail;
    if (error = rfsReceive(rcbp, &rmsg, sizeof (rmsg.rmsg_header), code))
	goto fail;
    rfsUnLock(rcbp);
    u.u_error = rmsg.rmsg_errno;
    return(NULL);

fail:
    rfsError(rcbp);
    u.u_error = error;
    return(NULL);
}
