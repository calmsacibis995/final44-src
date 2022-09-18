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
 * $Log:	vmtp_syscalls.c,v $
 * Revision 2.4  89/03/09  19:34:34  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/26  11:31:31  gm0w
 * 	Changes for cleanup.
 * 
 * 11-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	VMTP_INVOKE: fixed putsegblock to work with a segment in kernel
 *	space.
 *
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *	VMTP_INVOKE: added support for split invoke call.
 *
 */
 

#include <mach_vmtp.h>

#if	MACH_VMTP

#define VMTP_INVOKE	1

/*
 * vmtp_syscalls.c			2/26/87
 * Written by Joyo Wijaya and Erik Nordmark 
 * This code contains socket related system calls a la uipc_syscalls.c 
 * but these system calls are VMTP specific.
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/file.h>
#include <sys/buf.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <mach/machine/vm_param.h>
#include <netinet/in.h>
#include <netinet/vmtp_so.h>
#include <netinet/vmtp.h>
#include <netinet/vmtp_ip.h>
#include <netinet/esp_probe.h>


/*
 * System call interface to the socket abstraction.
 */

extern 	struct	file *getsock();
extern	struct fileops socketops;

/*
 * System call interface to the vmtp specific socket routines
 */


/*
 * Invoke a message transaction
 * 	invoke(s, func, mcb, segptr, segsize)
 */

invoke()
{
	register struct a {
		int 		s;
#if	VMTP_INVOKE
		int		func;
#endif	VMTP_INVOKE
		struct vmtpmcb 	*message;
		caddr_t		segptr;
		int		segsize;
	} *uap = (struct a *)u.u_ap;
	register struct socket *so;
	struct mbuf *msg = NULL;
	struct mbuf *seg = NULL;
	int segsize;
	register struct file *fp;
	int writeaccess;		/* Saved during transaction */

#ifdef	VMTP_DEBUG
	printf("invoke(): s = %d\n", uap->s);
#endif
	fp = getsock(uap->s);
	if (fp == NULL)
		return;
	so = (struct socket *)fp->f_data;
	if (so->so_type != SOCK_TRANSACT) {
		u.u_error = EOPNOTSUPP;
		return;
	}

	u.u_error = sockargs(&msg, uap->message, sizeof(struct vmtpmcb), 
				MT_HEADER);
	if (u.u_error)
		return;

	if (uap->segsize < 0 || uap->segsize > VMTP_MAXSEGSIZE) { 
		u.u_error = EINVAL;
		m_free(msg);
		return;
	}

#define mcb (mtod(msg, struct vmtpmcb *))

	writeaccess = vmtp_writeaccess(mcb->vm_code);

#if	VMTP_INVOKE
	if (u.u_error = soinvoke(so, uap->func, msg, uap->segptr, &seg)) 
#else	VMTP_INVOKE
	if (u.u_error = soinvoke(so, msg, uap->segptr, &seg)) 
#endif	VMTP_INVOKE
		return;

#if	VMTP_INVOKE
	if (uap->func & INVOKE_RESP) {
#endif	VMTP_INVOKE

#ifdef	VMTP_DEBUG
	printf("invoke(): output: segptr = 0x%x\n", (int)uap->segptr);
	vmtp_dumpmcb(mtod(msg, struct vmtpmcb *),"mcb","invoke(): output");
#endif	

	segsize = 0;
	if (vmtp_segmentdata(mcb->vm_code) && writeaccess) {
		if (seg != NULL) {
			segsize = MIN(uap->segsize, mcb->vm_segsize);
			u.u_error = putsegment(seg, uap->segptr, 
				&segsize,
				vmtp_usrdlvrmskset(mcb->vm_code) 
					? mcb->vm_dlvrmsk 
					: (u_long)0);
			if (u.u_error) {
				m_free(msg);
				return;
			}
		}
	} else if (seg != NULL)
		m_freem(seg);

#undef mcb

	u.u_error = sockresults(msg, uap->message, sizeof(struct vmtpmcb));

 	u.u_r.r_val1 = segsize;

#if	VMTP_INVOKE
	}
#endif	VMTP_INVOKE
	return;

} /* invoke */

/* 
 * 	Receive next request
 *		recvreq(s, mcb, segptr, segsize)
 */
recvreq()
{
	register struct a {
		int 		s;
		struct vmtpmcb 	*message;
		caddr_t		segptr;
		int		segsize;
	} *uap = (struct a *)u.u_ap;
	register struct socket *so;
	register struct mbuf *msg;
	struct mbuf *seg = NULL;
	register struct file *fp;
	int segsize;


#ifdef	VMTP_DEBUG
	printf("recvreq(): s = %d, segptr = 0x%x, segsize = 0x%x\n", 
		uap->s, (int)uap->segptr, uap->segsize);
#endif

	fp = getsock(uap->s);
	if (fp == NULL)
		return;
	so = (struct socket *)fp->f_data;
	if (so->so_type != SOCK_TRANSACT) {
		u.u_error = EOPNOTSUPP;
		return;
	}

	if (uap->segsize < 0 || uap->segsize > VMTP_MAXSEGSIZE) {
		u.u_error = EINVAL;
		return;
	}

	/* Mcb is strictly an out parameter, so it's not copied in! */
	MGET(msg, M_WAIT, MT_HEADER);
	if (msg == NULL)
		return (ENOBUFS);
	msg->m_len = sizeof(struct vmtpmcb);

#define mcb (mtod(msg, struct vmtpmcb *))


	u.u_error = sorecvreq(so, msg, &seg);
	if (u.u_error)
		return;

#ifdef	VMTP_DEBUG
	printf("recvreq(): output: segptr = 0x%x\n",(int)uap->segptr);
	vmtp_dumpmcb((mtod(msg, struct vmtpmcb *)),"mcb","recvreq(): output");
#endif	

	segsize = 0;
	if (vmtp_segmentdata(mcb->vm_code)) { 	/* always write access ?? */
		if (seg != NULL) {
			segsize = MIN(uap->segsize, mcb->vm_segsize);
			u.u_error = putsegment(seg, uap->segptr, 
				&segsize,
				vmtp_usrdlvrmskset(mcb->vm_code) 
					? mcb->vm_dlvrmsk 
					: (u_long)0);
			if (u.u_error) {
				m_free(msg);
				return;
			}
		}
	}
#undef mcb
	u.u_error = sockresults(msg, uap->message, sizeof(struct vmtpmcb));

	u.u_r.r_val1 = segsize;	
	return;

} /* recvreq */

/*
 * 	Send a reply to the client socket
 *		sendreply(s, mcb, segptr)
 */
sendreply()
{
	register struct a {
		int 		s;
		struct vmtpmcb 	*message;
		caddr_t		segptr;
	} *uap = (struct a *)u.u_ap;
	register struct file *fp;
	register struct socket *so;
	struct mbuf *msg;
	register struct mbuf *client;

#ifdef	VMTP_DEBUG
	printf("sendreply(): s = %d\n", uap->s);
#endif

	fp = getsock(uap->s);
	if (fp == NULL)
		return;
	so = (struct socket *)fp->f_data;
	if (so->so_type != SOCK_TRANSACT) {
		u.u_error = EOPNOTSUPP;
		return;
	}

	u.u_error = sockargs(&msg, uap->message, sizeof(struct vmtpmcb), 
				MT_HEADER);
	if (u.u_error)
		return;

	u.u_error = soreply(so, msg, uap->segptr);
	/* msg is freed in soreply */

} /* sendreply */

/* 
 * 	Forward a message transaction
 *		forward(s, mcb, newserver, segptr)
 */
forward()
{
	register struct a{
		int 		s;
		struct vmtpmcb 	*mcb;
		struct vmtpeid	newserver;
		caddr_t		segptr;
	} *uap = (struct a *)u.u_ap;
	register struct file *fp;
	register struct socket *so;
	struct mbuf *msg;
	register struct mbuf *nam;

#ifdef	VMTP_DEBUG
	printf("forward(): called!\n");
#endif

	fp = getsock(uap->s);
	if (fp == NULL)
		return;
	so = (struct socket *)fp->f_data;
	if (so->so_type != SOCK_TRANSACT) {
		u.u_error = EOPNOTSUPP;
		return;
	}

	u.u_error = sockargs(&msg, uap->mcb, sizeof(struct vmtpmcb), 
				MT_HEADER);
	if (u.u_error)
		return;

	nam = m_get(M_DONTWAIT, MT_SONAME);
	if (!nam) {
		u.u_error = ENOBUFS;
		return;
	}
	*(mtod(nam, struct vmtpeid *)) = uap->newserver;
	nam->m_len = sizeof(struct vmtpeid);

	u.u_error = soforward(so, msg, nam, uap->segptr);
	m_free(nam);
} /* forward */

/*
 *	Probe a VMTP entity returning some information
 *		probeentity(so, data)
 */
probeentity()
{
	register struct a{
		int 		s;
		struct espprobedata *data;
	} *uap = (struct a *)u.u_ap;
	register struct file *fp;
	register struct socket *so;
	struct mbuf *mdata;

#ifdef	VMTP_DEBUG
	printf("probeentity(): called!\n");
#endif

	fp = getsock(uap->s);
	if (fp == NULL)
		return;
	so = (struct socket *)fp->f_data;
	if (so->so_type != SOCK_TRANSACT) {
		u.u_error = EOPNOTSUPP;
		return;
	}

	u.u_error = sockargs(&mdata, uap->data, sizeof(struct espprobedata), 
				MT_HEADER);
	if (u.u_error)
		return;
	u.u_error = soprobeentity(so, mdata);
	if (u.u_error)
		return;
	
	u.u_error = sockresults(mdata, uap->data, sizeof(struct espprobedata));

} /* probeentity */

/*
 * 	Get the next reply	
 * 		getreply(so, mcb, segptr, segsize, timeout)
 */
getreply()
{
	register struct a {
		int 		s;
		struct vmtpmcb 	*message;
		caddr_t		segptr;
		int		segsize;
		int		timeout;
	} *uap = (struct a *)u.u_ap;
	register struct file *fp;
	register struct socket *so;
	register struct mbuf *msg;
	struct mbuf *seg = NULL;
	int segsize;


#ifdef	VMTP_DEBUG
printf("getreply(): s = %d, segptr = 0x%x, segsize = 0x%x, timeout = %d\n", 
		uap->s, (int)uap->segptr, uap->segsize, uap->timeout);
#endif

	fp = getsock(uap->s);
	if (fp == NULL)
		return;
	so = (struct socket *)fp->f_data;
	if (so->so_type != SOCK_TRANSACT) {
		u.u_error = EOPNOTSUPP;
		return;
	}

	if (uap->segsize < 0 || uap->segsize > VMTP_MAXSEGSIZE) {
		u.u_error = EINVAL;
		return;
	}

	/* Mcb is strictly an out parameter, so it's not copied in! */
	MGET(msg, M_WAIT, MT_HEADER);
	if (msg == NULL)
		return (ENOBUFS);
	msg->m_len = sizeof(struct vmtpmcb);

#define mcb (mtod(msg, struct vmtpmcb *))


	u.u_error = sogetreply(so, msg, &seg, uap->timeout);
	if (u.u_error)
		return;

#ifdef	VMTP_DEBUG
	printf("getreply(): output: segptr = 0x%x\n",(int)uap->segptr);
	vmtp_dumpmcb((mtod(msg, struct vmtpmcb *)),"mcb","getreply(): output");
#endif	

	segsize = 0;
	if (vmtp_segmentdata(mcb->vm_code)) { 	/* always write access ?? */
		if (seg != NULL) {
			segsize = MIN(uap->segsize, mcb->vm_segsize);
			u.u_error = putsegment(seg, uap->segptr, 
				&segsize,
				vmtp_usrdlvrmskset(mcb->vm_code) 
					? mcb->vm_dlvrmsk 
					: (u_long)0);
			if (u.u_error) {
				m_free(msg);
				return;
			}
		}
	}
#undef mcb
	u.u_error = sockresults(msg, uap->message, sizeof(struct vmtpmcb));

	u.u_r.r_val1 = segsize;	
	return;

} /* getreply */


sockresults(m, name, namelen)
	register struct mbuf *m;
	caddr_t name;
	register int namelen;
{
	register int error;

	if (namelen > MLEN)
		return (EINVAL);
	if (m->m_len != namelen)
		return (EINVAL);
	error = copyout(mtod(m, caddr_t), name, (u_int)namelen);

	m_free(m);
	return (error);
}


/*
 * putsegment(mbuf, segptr, seglen, mask)
 *
 * Copyout the segment from the mbuf. seglen denotes the max length on entry 
 * and will return the copied length. The mbuf chain is freed.
 *
 * The mask determines what parts of the segment to copy in chunks of 
 * VMTP_BLKSIZE. If the mask is zero the whole segment is copied.
 */
putsegment(mp, segptr, a_seglen, mask)
	struct mbuf 	*mp;
	caddr_t		segptr;
	int		*a_seglen;
	u_long		mask;
{
	register int	maxlen = *a_seglen;
	register int	blocklen;		/* size of continuous block  */
	caddr_t addr = segptr;
	struct mbuf	*m;
	register int 	error = 0;


#ifdef	VMTP_DEBUG
	printf("putsegment(): ");
	printf("mp = 0x%x segptr = 0x%x seglen = %d mask = 0x%x\n",
		(int)mp, (int)segptr, maxlen, mask);
#endif

	*a_seglen = 0;
	m = mp;

	if (mask) {

#ifdef	VMTP_DEBUG
		printf("putsegment(): the mask is set\n");
#endif

		while (mask && (maxlen > 0)) { /* mask optimization only */ 
			while (!(mask & 0x01) && (maxlen > 0)) {
				mask >>= 1;
				addr = (caddr_t)((int)addr + VMTP_BLKSIZE);
				maxlen -= VMTP_BLKSIZE;
			}
			/* Collect a block */
			blocklen = 0;
			while ((mask & 0x01) && (maxlen > 0)) {
				mask >>= 1;
				blocklen += VMTP_BLKSIZE;
				maxlen -= VMTP_BLKSIZE;
			}
			if (maxlen < 0)
				blocklen += maxlen;
			error = putsegblock(&m, &addr, blocklen);
			if (error) {
				*a_seglen = 0;
				goto free;			
			}
			*a_seglen += blocklen;
		}

	} else {

		error = putsegblock(&m, &addr, maxlen);
		if (!error) 
			*a_seglen = (int)addr - (int)segptr;
	}

free:

#ifdef	VMTP_DEBUG
	if (m)
		if (m->m_len > 3) {
			/*
			 * There can be up to 3 bytes left due to the padding
 			 * of the packets to multiples of 4 bytes!
			 */
		     printf("putsegment(): There is excess data not copied\n");
		}
	printf("putsegment(): copied totally %d bytes\n",*a_seglen);
#endif

 	m_freem(mp);		/* Free parts not copied too */

	return (error);

} /* putsegment */

/*
 * Copy a specified length of a segment starting at addr from m.
 * The new address is returned and m is modified to point to next data.
 */
int putsegblock(a_m, a_addr, len)
	struct mbuf **a_m;
	caddr_t *a_addr;
	register int len;
{
	register int mlen;		/* length copied from one mbuf */
	register int addr = (int)*a_addr;
	register struct mbuf *oldm,	/* old mbuf */
		    	*m;
	register int error;
	
	m = *a_m;
	if (m == NULL || len == 0)
		return 0;

	while (m != NULL && len > 0) {

		mlen = MIN(m->m_len, len);
#ifdef	VMTP_DEBUG
	printf("putsegblock(): copying out 0x%x bytes to address 0x%x\n",
		mlen, addr);
#endif

#if	VMTP_INVOKE
		if ((((caddr_t)addr) >= ((caddr_t)VM_MIN_KERNEL_ADDRESS)) &&
			    	(((caddr_t)addr) <= ((caddr_t)VM_MAX_KERNEL_ADDRESS))) {
			bcopy(mtod(m, caddr_t), (caddr_t)addr, mlen);
			error = 0;
		} else {
#endif	VMTP_INVOKE
		error = copyout(mtod(m, caddr_t), (caddr_t)addr, mlen);
#if	VMTP_INVOKE
		}
#endif	VMTP_INVOKE
		if (error)
			return error;
		len -= mlen;
		addr += mlen;
		oldm = m;
		m = m->m_next;
	}
	
	*a_addr = (caddr_t)addr;

	oldm->m_len -= mlen;
	if (oldm->m_len) {
		oldm->m_off += mlen;
		*a_m = oldm;
	} else {
		*a_m = m;
	}

#ifdef	VMTP_DEBUG
	printf("putsegblock():  done!\n");
#endif

	return 0;		
		
} /* putsegblock */

#endif	MACH_VMTP
