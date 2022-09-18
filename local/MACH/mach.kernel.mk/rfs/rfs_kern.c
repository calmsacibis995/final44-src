/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * Copyright (c) 1986 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	rfs_kern.c,v $
 * Revision 2.14  91/11/11  16:15:23  mja
 * 	Don't assume that we always have an identity record in
 * 	rfsGetTicket().
 * 	[91/11/11  16:11:32  mja]
 * 
 * Revision 2.13  91/11/05  18:28:05  mja
 * 	Add missing <mach_afs.h> include.
 * 	[91/11/05  13:24:34  mja]
 * 
 * 	Move ticket file processing out to ticketdGetTicket();  move
 * 	ticket file diagnostics into rfsGetTicket().
 * 	[91/11/05  00:28:53  mja]
 * 
 * Revision 2.12  91/10/31  22:24:38  mja
 * 	Mark the ticket file as "bad" when we attempt to get an rfs ticket
 * 	and fail.  Also, fixed a core leak.
 * 	[91/10/30  15:37:58  chs]
 * 
 * Revision 2.11  91/09/02  19:49:58  berman
 * 	Conditionalized afs_Unlogme() under MACH_AFS.
 * 	[91/09/02            berman]
 * 
 * Revision 2.10  91/08/29  21:50:09  berman
 * 	Destroy any cached afs tickets at the same time we request the
 * 	ticketd destroy a ticket file.
 * 	[91/08/23  15:55:32  chs]
 * 
 * Revision 2.9  91/08/01  15:25:39  berman
 * 	Use the new MAXTKTFILELEN constant.
 * 	[91/07/31  23:26:51  chs]
 * 
 * 	Zero the connect message before we use it, since we don't
 * 	set all the fields.
 * 	Allocate space for the pathname too on a DESTTKT request.
 * 	[91/07/27  17:12:37  chs]
 * 
 * 	Send a ticketd DESTTKT request when the last reference to
 * 	a ticket file is deleted.
 * 	[91/07/23  15:18:22  chs]
 * 
 * 	Added support for kerberos authentication.
 * 	[91/07/22  11:49:08  chs]
 * 
 * Revision 2.8  89/10/10  10:56:05  mwyoung
 * 		Allow RFS links to be either symbolic link nodes or regular
 * 		file nodes.
 * 	[89/07/30            mwyoung]
 * 
 * Revision 2.7  89/04/22  15:27:01  gm0w
 * 	Changed to use new inode macros for manipulation of inodes.
 * 	[89/04/14            gm0w]
 * 
 * Revision 2.6  89/03/15  15:14:16  gm0w
 * 	changed include sys/rfs.h to rfs/rfs/h
 * 
 * Revision 2.5  89/02/25  14:45:00  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  89/02/09  04:32:25  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.3  89/01/18  00:39:29  jsb
 * 	Vnode support.
 * 	[89/01/13            jsb]
 * 
 * Revision 2.2  88/08/24  01:24:15  mwyoung
 * 	Removed RFS conditional entirely... this file isn't built unless
 * 	CMUCS_RFS is specified.
 * 	[88/08/23            mwyoung]
 * 	
 * 	Corrected include file references.
 * 	[88/08/22            mwyoung]
 * 
 * 07-Mar-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fix byte-order bug in rfsConnect() for non-CONNECT type
 *	messages.
 *	[ V5.1(F5) ]
 *
 * 05-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Updated to zero new remote root device and i-number fields of
 *	the control block when first created and preserve them when
 *	copied; fixed rfsError() to avoid closing down connection with
 *	only simulated ELOCAL errors.
 *	[ V5.1(F2) ]
 *
 * 01-Nov-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed to use new RFST_BANNER value in connect message.  This
 *	is a 32-bit value which is identical on all machine types.
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

/*	rfs_kern.c	CMU	82/01/20	*/

/*
 *  Remote file system - basic protocol services module
 */

#include <mach_fastlink.h>
#include <mach_afs.h>

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/buf.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/tty.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/inode.h>
#include <sys/map.h>
#include <sys/proc.h>
#include <sys/uio.h>
#include <rfs/rfs.h>
#include <rfs/ticketd.h>

/*
 *  rfsAttach - attach to a remote connection
 *
 *  ip = host name inode pointer (locked)
 *
 *  Attach to the remote connection for the current process and the
 *  specified host.  If a connection does not already exist, it will be
 *  established and entered into the process connection table.  The
 *  inode is unlocked.
 *
 *  Return: a pointer to the remote control block or NULL on error
 *  (with u.u_error set appropriately).     
 */

struct rfsConnectionBlock *
rfsAttach(ip)
    struct inode *ip;
{
    register struct rfsConnectionBlock *rcbp = NULL;
    int error;

    rfs_printf2(RFSD_C_TRACEIN, "<Att  ip=%X\n", ip);
    rcbp = rfsProcessConnection(ip);
    if (rcbp == NULL)
    {
	register struct rfsProcessEntry *rpep = rfsCurrentProcessEntry;

	rcbp = rfsGet(ip);
	if (rcbp == NULL)
	{
	    rfs_printf2(RFSD_C_TRACEOUT, ">Att  %d\n", u.u_error);
	    return(NULL);
	}
	if ((rcbp->rcb_rwp=rpep->rpe_rwp) != NULL)
	    rfsIncrCheckWho(rcbp->rcb_rwp);
	rfsEnQueueConnection(&rpep->rpe_rcbq, rcbp);
    }
    if
    (
      rcbp->rcb_so == NULL
      &&
      (
        rcbp->rcb_addr.s_addr != INADDR_ANY
        ||
	(u.u_rfscode != RFST_OPEN && u.u_rfscode != RFST_CREAT)
      )
    )
    {
	error = rfsEstablish(rcbp, rcbp->rcb_addr, rcbp->rcb_fport, 0, 1, RFSMAXRETRY);
	if (error)
	{
	    rfs_printf2(RFSD_C_TRACEOUT, ">Conn %d(Estab)\n", error);
	    u.u_error = error;
	    return(NULL);
	}
	error = rfsConnect(rcbp, RFST_CONNECT);
	if (error)
	{
	    rfs_printf2(RFSD_C_TRACEOUT, ">Att  %d(Conn)\n", error);
	    u.u_error = error;
	    return(NULL);
	}
    }
    rfsIncrCheck(rcbp);
    rfs_printf3(RFSD_C_TRACEOUT, ">Att  rcb=%X(%d)\n", rcbp, rcbp->rcb_refc);
    return(rcbp);
}



/*
 *  rfsProcessConnection - lookup connection between host and current process
 *
 *  ip = remote host link inode (locked)
 *
 *  Scan the process connection list for a connection block corresponding to
 *  the specified remote host.  
 *
 *  Return: NULL if no connection currently exists, otherwise releases the
 *  inode and returns a pointer to the approriate connection block.
 */

struct rfsConnectionBlock *
rfsProcessConnection(ip)
    register struct inode *ip;
{
    register struct rfsProcessEntry *rpep = rfsCurrentProcessEntry;
    register struct rfsConnectionQueue *rcbqp = &(rpep->rpe_rcbq);
    register struct rfsConnectionBlock *rcbp;

    rfs_printf2(RFSD_C_TRACEIN, "<PrCn i=%X\n", ip);
    for (rcbp = rfsConnectionFirst(rcbqp);
	 !rfsConnectionLast(rcbqp, rcbp);
	 rcbp = rfsConnectionNext(rcbp))
    {
	if (rcbp->rcb_ip == ip)
	{
	    FINISH_WITH_INODE(ip);
	    rfs_printf2(RFSD_C_TRACEOUT, ">PrCn rcb=%X\n", rcbp);
	    return(rcbp);
	}
    }
    rfs_printf1(RFSD_C_TRACEOUT, ">PrCn NULL\n");
    return(NULL);
}



/*
 *  rfsGet - allocate a remote control block for host
 *
 *  ip = remote host link pointer (locked)
 *
 *  Allocate a new remote connection block for the process.  Read the supplied
 *  remote link inode to determine its contact information and record it in the
 *  new remote connection block.  The inode pointer is unlocked.
 *
 *  Return: a pointer to the newly created remote control block or NULL
 *  if none are available.
 */

struct rfsConnectionBlock *
rfsGet(ip)
    struct inode *ip;
{
    register struct rfsConnectionBlock *rcbp;
    int error;
    int resid;

    rfs_printf2(RFSD_C_TRACEIN, "<Get  ip=%X\n", ip);
    rcbp = rfsConnectionAllocate();
    if (rcbp == NULL)
    {
	FINISH_WITH_INODE(ip);
	rfs_printf1(RFSD_C_TRACEOUT, ">Get  FULL\n");
	u.u_error = ENOBUFS;
	return(NULL);
    }

    rcbp->rcb_refc = 1;
    rcbp->rcb_so = NULL;
    rcbp->rcb_rwp = NULL;
    rcbp->rcb_lport = 0;
    rcbp->rcb_rinum = 0;
    rcbp->rcb_rdev  = NODEV;
#if	MACH_FASTLINK
    if (
#ifndef	lint
	(sizeof(rcbp->rcb_rl) < MAX_FASTLINK_SIZE) &&	/* constant */
#endif	lint
	use_fastlinks && (ip->i_icflags & IC_FASTLINK))
    {
        rcbp->rcb_rl = * ((struct rfsLink *) ip->i_symlink);
	error = 0;
	resid = sizeof(rcbp->rcb_rl) - ip->i_size;
	if (resid < 0)
	    resid = 0;
    }
     else
#endif	MACH_FASTLINK
    error = rdwri(UIO_READ, ip, (caddr_t)&rcbp->rcb_rl, sizeof(rcbp->rcb_rl), 0, 1, &resid);
    rcbp->rcb_flags = 0;
    if (error)
    {
 	rfs_printf2(RFSD_LOG|RFSD_C_TRACEOUT, "*Get  %d(name read)\n", error);
    free:
	rfsConnectionFree(rcbp);
	rcbp = NULL;
	FINISH_WITH_INODE(ip);
	goto out;
    }
    if (resid > sizeof(rcbp->rcb_rl)-sizeof(rcbp->rcb_addr))
    {
	u.u_error = EIO;
	rfs_printf2(RFSD_LOG|RFSD_C_TRACEOUT, "*Get  %d(link size)\n", u.u_error);
	goto free;
    }
    if (resid > sizeof(rcbp->rcb_rl)-sizeof(rcbp->rcb_addr)-sizeof(rcbp->rcb_fport) || rcbp->rcb_fport == 0)
    {
	extern int rfsPort;

	rcbp->rcb_fport = rfsPort;
    }
    if (resid > sizeof(rcbp->rcb_rl)-sizeof(rcbp->rcb_addr)-sizeof(rcbp->rcb_fport)-sizeof(rcbp->rcb_pvers))
	rcbp->rcb_pvers = 0;
    rcbp->rcb_ip = ip;
    /*
     *  Pre-calculate a value for adjustment of remote block device numbers
     *  so that they can never match local block device numbers and are
     *  unlikely to match remote ones.  This calulation yields an offset in
     *  the range [1,255-nblkdev] which is added to any remote block device
     *  number before passing it back to the application.
     */
    rcbp->rcb_majx = 
      (
	((rcbp->rcb_addr.s_addr&0xff0000)<<8)
	+
	(rcbp->rcb_addr.s_addr&0xff000000)
      )
      %
	(255-nblkdev)
      +
	1
      ;
    rcbp->rcb_cmask = -1; 
    UNLOCK_INODE(ip);
out:
    rfs_printf2(RFSD_C_TRACEOUT, ">Get  rcb=%X\n", rcbp);
    return(rcbp);
}



/*
 *  rfsGetTicket - get a Kerberos ticket for a remote host's rfs service
 *
 *  rwp = identity to get ticket for
 *  addr = ip address of the remote host (service)
 *  ticket = buffer to place the ticket in
 *
 *  Get a Kerberos ticket for rcmd.<hostname of addr> by making a request
 *  to the ticketd.  Return the ticket in the supplied buffer and the
 *  length in *ticketlen.
 *
 *  Return: 0 or an error number as appropriate.
 */

rfsGetTicket(rwp, addr, ticket, ticketlen)
register struct rfsWho *rwp;
struct in_addr addr;
caddr_t ticket;
u_short *ticketlen;
{
    int error = 0;
    union ticketd_req_un *req = NULL;
    struct ticketd_reply *reply = NULL;
    int errorval;

    req = (union ticketd_req_un *)kalloc(sizeof(*req));
    if (req == NULL)
	return ENOMEM;

    req->rfs.header.type = TICKETD_REQ_RFS;
    req->rfs.addr = addr;

    error = ticketdGetTicket(req, &reply, &errorval);

    if (error == 0) {
	*ticketlen = reply->authlen;
	bcopy(reply->auth, ticket, *ticketlen);
	kfree(reply, sizeof (struct ticketd_reply));
    } else {
	switch (errorval) {
	  case 26:	/* MK_AP_TGTEXP */
	    if (rwp && (rwp->rw_flags&RFSWHO_EXPTKTFILE) == 0) {
		uprintf("rfs: tickets have expired, renew with kinit\n");
	        rwp->rw_flags |= RFSWHO_EXPTKTFILE;
	    }
	    break;
	  case 76:	/* NO_TKT_FIL */
	    if (rwp && (rwp->rw_flags&RFSWHO_NOTKTFILE) == 0) {
		uprintf("rfs: no ticket file found, create with kinit\n");
	        rwp->rw_flags |= RFSWHO_NOTKTFILE;
	    }
	    break;
	  case 32:	/* RD_AP_EXP */
	    uprintf("rfs: ticket has expired\n");
	    break;
	  default:
	    /* no message, just fail silently */
	    break;
	}
    }
    kfree(req, sizeof(*req));

    return error;
}



/*
 *  rfsConnect - establish connection and perform initial connection protocol
 *
 *  rcbp = remote control block of connection to initialize
 *
 *  Open a connection to the remote host, send the initial connection message
 *  and handle the reply to initialize the remote connection block for this
 *  process and host.
 *
 *  Return: 0 or an error number as appropriate.
 */

rfsConnect(rcbp, type)
    register struct rfsConnectionBlock *rcbp;
    u_char type;
{
    register struct rfsWho *rwp = rcbp->rcb_rwp;
    struct rfsMsg rmsg;
    int error;
    u_short ticketlen;
    caddr_t ticket = NULL;

    (void)bzero((caddr_t)&rmsg, sizeof(rmsg));

    rfs_printf2(RFSD_C_TRACEIN, "<Conn rcb=%X\n", rcbp);

    if (type == RFST_CONNECT)
    {
	rmsg.rmsg_C_banner = RFST_BANNER;
    }
    else
    {
	rmsg.rmsg_C_banner = 0;
	rmsg.rmsg_C_code = type;
    }

    rmsg.rmsg_C_auth = 0;
    ticket = (caddr_t) kalloc(MAX_KTXT_LEN);
    if (ticket) {
	if (rfsGetTicket(rwp, rcbp->rcb_rl.rl_addr,
			 ticket, &ticketlen) == 0) {
	    rmsg.rmsg_C_auth = 1;
	}
    }

    rmsg.rmsg_C_cid = u.u_procp->p_pid;
    rfsLock(rcbp);
    if (error = rfsSend(rcbp, &rmsg, sizeof(rmsg.rmsg_header)+sizeof(rmsg.rmsg_C_cid)))
    {
	rfs_printf2(RFSD_C_TRACEOUT, ">Conn %d(Send)\n", error);
	goto fail;
    }

    /* simulate the use of krb_sendauth() */
    if (rmsg.rmsg_C_auth)
    {
	int ticketlenbuf = htonl(ticketlen);

	if (error = rfsSend(rcbp, "AUTHV0.1rfsV3   ", 16))
	    goto fail;

	if (error = rfsSend(rcbp, &ticketlenbuf, sizeof(int)))
	    goto fail;

	if (error = rfsSend(rcbp, ticket, ticketlen))
	    goto fail;
    }
    if (error = rfsReceive(rcbp, &rmsg, sizeof(rmsg.rmsg_header), (int)type))
    {
	rfs_printf2(RFSD_C_TRACEOUT, ">Conn %d(Recv)\n", error);
	goto fail;
    }
    rfsUnLock(rcbp);
    if ((error=rmsg.rmsg_errno) != 0)
	goto out;

done:
    if (ticket)
	kfree(ticket, MAX_KTXT_LEN);

    rfs_printf2(RFSD_C_TRACEOUT, ">Conn %d\n", error);
    return(error);

fail:
    rfsError(rcbp);
out:

    /*
     *  Release the remote connection so that another attempt will be made
     *  on the next operation.
     */
    rfsUnEstablish(rcbp);
    goto done;
}



/*
 *  rfsDetach - detach from remote connection block
 *
 *  rcbp = remote connection block
 *
 *  Decrement the reference count on the connection block.  On the last
 *  reference, release the inode, and release any associated remote connection.
 */

void
rfsDetach(rcbp)
    register struct rfsConnectionBlock *rcbp;
{
    rfs_printf3(RFSD_C_TRACEIN, "<Det  rcb=%X(%d)\n", rcbp, rcbp->rcb_refc);
    if (rcbp->rcb_refc == 1)
    {
	if (rcbp->rcb_rwp)
	    rfsDetachWho(rcbp->rcb_rwp);
	if (rcbp->rcb_ip)
 	{
	    LOCK_INODE(rcbp->rcb_ip);
	    FINISH_WITH_INODE(rcbp->rcb_ip);
	    rcbp->rcb_ip = NULL;
	}
	rfsUnEstablish(rcbp);
	rfsConnectionFree(rcbp);
	/* the connection block is now gone */
    }
    else
	rfsDecrCheck(rcbp);
    rfs_printf1(RFSD_C_TRACEOUT, ">Det\n");
}



/*
 *  rfsDetachWho - detach from remote identity entry
 *
 *  rwp = remote identity record
 *
 *  Decrement the reference count on the identity record.  On the last
 *  reference, release its storage.
 */

void
rfsDetachWho(rwp)
    register struct rfsWho *rwp;
{
    rfs_printf3(RFSD_C_TRACEIN, "<DetW rwp=%X(%d)\n", rwp, rwp->rw_refc);
    if (rwp->rw_refc == 1)
    {
	union ticketd_req_un req;
	int errorval;
#if	MACH_AFS
	extern int afs_UnlogMe();
#endif	MACH_AFS

	/* destroy the ticket file */
	req.desttkt.header.type = TICKETD_REQ_DESTTKT;
	(void) ticketdGetTicket(&req, (struct ticketd_reply **)0, &errorval);

#if	MACH_AFS
	/* destroy any cached afs tickets */
	afs_UnlogMe();
#endif	MACH_AFS

	/* free the rfs identity */
	rfsWhoFree(rwp);
    }
    else
	rfsDecrCheckWho(rwp);
    rfs_printf1(RFSD_C_TRACEOUT, ">DetW\n");
}



/*
 *  rfsNameLength - calculate length of pathname 
 *
 *  nip = namei structure for name
 *
 *  Iterate through each character of the specified pathname to determine its
 *  length.  The name is always stored in the buffer allocated by namei() in
 *  system space.
 *
 *  Return: the length of the pathname (excluding the trailing byte) or -1 on
 *  error with u.u_error set as appropriate (although errors should longer be
 *  possible with the name in system space).
 */

rfsNameLength(nip)
    struct nameidata *nip;
{
    return(strlen(nip->ni_dirp));
}



/*
 *  rfsCopy - copy a remote connection block
 *
 *  rcbp = remote connection block to copy
 *
 *  Allocate a new remote connection block, replicating the password, remote
 *  address, local port, device number adjustment and inode fields of the old
 *  remote connection block.  The new connection block has a reference count of
 *  1 and no active remote connection.
 *
 *  Return: the new connection block or NULL if none can be allocated.
 */

struct rfsConnectionBlock *
rfsCopy(rcbp)
struct rfsConnectionBlock *rcbp;
{
    register struct rfsConnectionBlock *crcbp;

    rfs_printf2(RFSD_C_TRACEIN, "<Copy rcb=%X\n", rcbp);
    crcbp = rfsConnectionAllocate();
    if (crcbp == NULL)
    {
	rfs_printf1(RFSD_C_TRACEOUT, ">Copy FULL\n");
	return(NULL);
    }

    crcbp->rcb_refc = 1;
    crcbp->rcb_so = NULL;
    crcbp->rcb_cmask = rcbp->rcb_cmask;
    crcbp->rcb_rdev = rcbp->rcb_rdev;
    crcbp->rcb_rinum = rcbp->rcb_rinum;
    crcbp->rcb_majx = rcbp->rcb_majx;
    crcbp->rcb_lport = rcbp->rcb_lport;
    crcbp->rcb_rl = rcbp->rcb_rl;
    crcbp->rcb_flags = 0;	/* overlays rad */
    LOCK_INODE(rcbp->rcb_ip);
    crcbp->rcb_ip = rcbp->rcb_ip;
    INCR_INODE(crcbp->rcb_ip);
    UNLOCK_INODE(rcbp->rcb_ip);
    crcbp->rcb_rwp = rcbp->rcb_rwp;
    if (crcbp->rcb_rwp)
	rfsIncrCheckWho(crcbp->rcb_rwp);
    rfs_printf2(RFSD_C_TRACEOUT, ">Copy rcb=%X\n", crcbp);
    return(crcbp);
}



/*
 *  rfsLock - lock remote control block
 *
 *  rcbp = remote control block
 */

void
rfsLock(rcbp)
register struct rfsConnectionBlock *rcbp;
{
    while (rcbp->rcb_flags&RFSF_LOCKED)
    {
	rcbp->rcb_flags |= RFSF_WANTED;
	sleep((caddr_t)&(rcbp->rcb_flags), PZERO-1);
    }
    rcbp->rcb_flags |= RFSF_LOCKED;
}



/*
 *  rfsUnLock - unlock remote control block
 *
 *  rcbp = remote control block
 */

void
rfsUnLock(rcbp)
register struct rfsConnectionBlock *rcbp;
{
    if ((rcbp->rcb_flags&RFSF_LOCKED) == 0)
	panic("rfsUnLock");
    if (rcbp->rcb_flags&RFSF_WANTED)
	wakeup((caddr_t)&(rcbp->rcb_flags));
    rcbp->rcb_flags &= ~(RFSF_LOCKED|RFSF_WANTED);
}



/*
 *  rfsError - set error status for connection
 *
 *  rcbp = remote connection block
 *
 *  Prevent any further sends on the connection, unlock it if necessary, and
 *  remember that we encountered a protocol error.  In the exceptional case
 *  that we are only simulating an error on the connection to continue local
 *  processing, avoid doing anything but unlocking the connection and clearing
 *  the local reply flag.
 */

void
rfsError(rcbp)
    register struct rfsConnectionBlock *rcbp;
{
    register struct rfsConnectionBlock *crcbp;

    /*
     *  Arrange not to close down the connection on the ELOCAL
     *  error since it isn't really an error.
     */
    if ((rcbp->rcb_flags&RFSF_LREPLY) == 0)
    {
	rcbp->rcb_flags |= RFSF_ERROR;
	rfsUnEstablish(rcbp);
    }
    if (rcbp->rcb_flags&RFSF_LOCKED)
	rfsUnLock(rcbp);
    if (rcbp->rcb_flags&RFSF_LREPLY)
    {
        rcbp->rcb_flags &= ~RFSF_LREPLY;
	return;
    }

    /*
     *  Always remove the errored block from the process list at this point
     *  since if we allow a new connection to be created using it (which will
     *  happen by default the first time it is used again), any file pointers
     *  which still point to it refer to open files on the old connection and
     *  can't be used on the new connection.  If the copy fails, we lose any
     *  name/password information but at least the file correspondence has been
     *  broken.  This also ensures that there is always at most one connection
     *  per remote host recorded per process.
     */
    LOCK_INODE(rcbp->rcb_ip);
    INCR_INODE(rcbp->rcb_ip);
    crcbp = rfsProcessConnection(rcbp->rcb_ip);
    if (crcbp != NULL)
    {
	if (crcbp == rcbp)
	{
	    register struct rfsConnectionQueue *rcbqp = &(rfsCurrentProcessEntry->rpe_rcbq);

	    crcbp = rfsCopy(rcbp);
	    rfsRemQueueConnection(rcbqp, rcbp);
	    rfsDetach(rcbp);
	    if ((rcbp=crcbp) != NULL)
		rfsEnQueueConnection(rcbqp, rcbp);
	}
    }
    else
    {
	FINISH_WITH_INODE(rcbp->rcb_ip);
    }
}
