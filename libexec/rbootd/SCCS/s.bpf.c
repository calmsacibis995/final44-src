h35804
s 00002/00002/00394
d D 8.1 93/06/04 19:02:41 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00395
d D 5.3 93/06/04 19:02:11 bostic 4 2
c put the Regents copyright last so 44yank works
e
s 00002/00002/00394
d R 8.1 93/06/04 18:58:15 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00014/00016/00382
d D 5.2 92/07/23 16:42:15 bostic 2 1
c Welcome to the Wonderful World of ANSI C!
e
s 00398/00000/00000
d D 5.1 92/07/23 15:44:49 bostic 1 0
c date and time created 92/07/23 15:44:49 by bostic
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 Regents of the University of California.
E 4
 * Copyright (c) 1988, 1992 The University of Utah and the Center
 *	for Software Science (CSS).
I 4
D 5
 * Copyright (c) 1992 Regents of the University of California.
E 4
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * the Center for Software Science of the University of Utah Computer
 * Science Department.  CSS requests users of this software to return
 * to css-dist@cs.utah.edu any improvements that they make and grant
 * CSS redistribution rights.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * Utah $Hdr: bpf.c 3.1 92/07/06$
 * Author: Jeff Forys, University of Utah CSS
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 2
#include "defs.h"

#include <ctype.h>
#include <syslog.h>
#include <strings.h>

E 2
I 2
#include <sys/param.h>
E 2
#include <sys/ioctl.h>
D 2
#include <sys/file.h>
#include <sys/errno.h>
E 2
I 2
#include <sys/socket.h>
E 2

#include <net/if.h>
#include <net/bpf.h>

I 2
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>
#include "defs.h"
E 2
#include "pathnames.h"

D 2
extern int errno;

E 2
static int BpfFd = -1;
static unsigned BpfLen = 0;
static u_char *BpfPkt = NULL;

/*
**  BpfOpen -- Open and initialize a BPF device.
**
**	Parameters:
**		None.
**
**	Returns:
**		File descriptor of opened BPF device (for select() etc).
**
**	Side Effects:
**		If an error is encountered, the program terminates here.
*/
D 2

E 2
int
BpfOpen()
{
	struct ifreq ifr;
	char bpfdev[32];
	int n = 0;

	/*
	 *  Open the first available BPF device.
	 */
	do {
		(void) sprintf(bpfdev, _PATH_BPF, n++);
		BpfFd = open(bpfdev, O_RDWR);
	} while (BpfFd < 0 && (errno == EBUSY || errno == EPERM));

	if (BpfFd < 0) {
		syslog(LOG_ERR, "bpf: no available devices: %m");
		Exit(0);
	}

	/*
	 *  Set interface name for bpf device, get data link layer
	 *  type and make sure it's type Ethernet.
	 */
	(void) strncpy(ifr.ifr_name, IntfName, sizeof(ifr.ifr_name));
	if (ioctl(BpfFd, BIOCSETIF, (caddr_t)&ifr) < 0) {
		syslog(LOG_ERR, "bpf: ioctl(BIOCSETIF,%s): %m", IntfName);
		Exit(0);
	}

	/*
	 *  Make sure we are dealing with an Ethernet device.
	 */
	if (ioctl(BpfFd, BIOCGDLT, (caddr_t)&n) < 0) {
		syslog(LOG_ERR, "bpf: ioctl(BIOCGDLT): %m");
		Exit(0);
	}
	if (n != DLT_EN10MB) {
		syslog(LOG_ERR,"bpf: %s: data-link type %d unsupported",
		       IntfName, n);
		Exit(0);
	}

	/*
	 *  On read(), return packets immediately (do not buffer them).
	 */
	n = 1;
	if (ioctl(BpfFd, BIOCIMMEDIATE, (caddr_t)&n) < 0) {
		syslog(LOG_ERR, "bpf: ioctl(BIOCIMMEDIATE): %m");
		Exit(0);
	}

	/*
	 *  Try to enable the chip/driver's multicast address filter to
	 *  grab our RMP address.  If this fails, try promiscuous mode.
	 *  If this fails, there's no way we are going to get any RMP
	 *  packets so just exit here.
	 */
#ifdef MSG_EOR
	ifr.ifr_addr.sa_len = RMP_ADDRLEN + 2;
#endif
	ifr.ifr_addr.sa_family = AF_UNSPEC;
	bcopy(&RmpMcastAddr[0], (char *)&ifr.ifr_addr.sa_data[0], RMP_ADDRLEN);
	if (ioctl(BpfFd, SIOCADDMULTI, (caddr_t)&ifr) < 0) {
		syslog(LOG_WARNING,
		    "bpf: can't add mcast addr (%m), setting promiscuous mode");

		if (ioctl(BpfFd, BIOCPROMISC, (caddr_t)0) < 0) {
			syslog(LOG_ERR, "bpf: can't set promiscuous mode: %m");
			Exit(0);
		}
	}

	/*
	 *  Ask BPF how much buffer space it requires and allocate one.
	 */
	if (ioctl(BpfFd, BIOCGBLEN, (caddr_t)&BpfLen) < 0) {
		syslog(LOG_ERR, "bpf: ioctl(BIOCGBLEN): %m");
		Exit(0);
	}
	if (BpfPkt == NULL)
		BpfPkt = (u_char *)malloc(BpfLen);

	if (BpfPkt == NULL) {
		syslog(LOG_ERR, "bpf: out of memory (%u bytes for bpfpkt)",
		       BpfLen);
		Exit(0);
	}

	/*
	 *  Write a little program to snarf RMP Boot packets and stuff
	 *  it down BPF's throat (i.e. set up the packet filter).
	 */
	{
#define	RMP	((struct rmp_packet *)0)
		static struct bpf_insn bpf_insn[] = {
		    { BPF_LD|BPF_B|BPF_ABS,  0, 0, (long)&RMP->hp_llc.dsap },
		    { BPF_JMP|BPF_JEQ|BPF_K, 0, 5, IEEE_DSAP_HP },
		    { BPF_LD|BPF_H|BPF_ABS,  0, 0, (long)&RMP->hp_llc.cntrl },
		    { BPF_JMP|BPF_JEQ|BPF_K, 0, 3, IEEE_CNTL_HP },
		    { BPF_LD|BPF_H|BPF_ABS,  0, 0, (long)&RMP->hp_llc.dxsap },
		    { BPF_JMP|BPF_JEQ|BPF_K, 0, 1, HPEXT_DXSAP },
		    { BPF_RET|BPF_K,         0, 0, RMP_MAX_PACKET },
		    { BPF_RET|BPF_K,         0, 0, 0x0 }
		};
#undef	RMP
		static struct bpf_program bpf_pgm = {
		    sizeof(bpf_insn)/sizeof(bpf_insn[0]), bpf_insn
		};

		if (ioctl(BpfFd, BIOCSETF, (caddr_t)&bpf_pgm) < 0) {
			syslog(LOG_ERR, "bpf: ioctl(BIOCSETF): %m");
			Exit(0);
		}
	}

	return(BpfFd);
}

/*
**  BPF GetIntfName -- Return the name of a network interface attached to
**		the system, or 0 if none can be found.  The interface
**		must be configured up; the lowest unit number is
**		preferred; loopback is ignored.
**
**	Parameters:
**		errmsg - if no network interface found, *errmsg explains why.
**
**	Returns:
**		A (static) pointer to interface name, or NULL on error.
**
**	Side Effects:
**		None.
*/
D 2

E 2
char *
BpfGetIntfName(errmsg)
	char **errmsg;
{
	struct ifreq ibuf[8], *ifrp, *ifend, *mp;
	struct ifconf ifc;
	int fd;
	int minunit, n;
	char *cp;
	static char device[sizeof(ifrp->ifr_name)];
	static char errbuf[128] = "No Error!";

	if (errmsg != NULL)
		*errmsg = errbuf;

	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		(void) strcpy(errbuf, "bpf: socket: %m");
		return(NULL);
	}
	ifc.ifc_len = sizeof ibuf;
	ifc.ifc_buf = (caddr_t)ibuf;

#ifdef OSIOCGIFCONF
	if (ioctl(fd, OSIOCGIFCONF, (char *)&ifc) < 0 ||
	    ifc.ifc_len < sizeof(struct ifreq)) {
		(void) strcpy(errbuf, "bpf: ioctl(OSIOCGIFCONF): %m");
		return(NULL);
	}
#else
	if (ioctl(fd, SIOCGIFCONF, (char *)&ifc) < 0 ||
	    ifc.ifc_len < sizeof(struct ifreq)) {
		(void) strcpy(errbuf, "bpf: ioctl(SIOCGIFCONF): %m");
		return(NULL);
	}
#endif
	ifrp = ibuf;
	ifend = (struct ifreq *)((char *)ibuf + ifc.ifc_len);
	
	mp = 0;
	minunit = 666;
	for (; ifrp < ifend; ++ifrp) {
		if (ioctl(fd, SIOCGIFFLAGS, (char *)ifrp) < 0) {
			(void) strcpy(errbuf, "bpf: ioctl(SIOCGIFFLAGS): %m");
			return(NULL);
		}

		/*
		 *  If interface is down or this is the loopback interface,
		 *  ignore it.
		 */
		if ((ifrp->ifr_flags & IFF_UP) == 0 ||
#ifdef IFF_LOOPBACK
		    (ifrp->ifr_flags & IFF_LOOPBACK))
#else
		    (strcmp(ifrp->ifr_name, "lo0") == 0))
#endif
			continue;

		for (cp = ifrp->ifr_name; !isdigit(*cp); ++cp)
			;
		n = atoi(cp);
		if (n < minunit) {
			minunit = n;
			mp = ifrp;
		}
	}

	(void) close(fd);
	if (mp == 0) {
		(void) strcpy(errbuf, "bpf: no interfaces found");
		return(NULL);
	}

	(void) strcpy(device, mp->ifr_name);
	return(device);
}

/*
**  BpfRead -- Read packets from a BPF device and fill in `rconn'.
**
**	Parameters:
**		rconn - filled in with next packet.
**		doread - is True if we can issue a read() syscall.
**
**	Returns:
**		True if `rconn' contains a new packet, False otherwise.
**
**	Side Effects:
**		None.
*/
D 2

E 2
int
BpfRead(rconn, doread)
	RMPCONN *rconn;
	int doread;
{
	register int datlen, caplen, hdrlen;
	static u_char *bp = NULL, *ep = NULL;
	int cc;

	/*
	 *  The read() may block, or it may return one or more packets.
	 *  We let the caller decide whether or not we can issue a read().
	 */
	if (doread) {
		if ((cc = read(BpfFd, (char *)BpfPkt, (int)BpfLen)) < 0) {
			syslog(LOG_ERR, "bpf: read: %m");
			return(0);
		} else {
			bp = BpfPkt;
			ep = BpfPkt + cc;
		}
	}

#define bhp ((struct bpf_hdr *)bp)
	/*
	 *  If there is a new packet in the buffer, stuff it into `rconn'
	 *  and return a success indication.
	 */
	if (bp < ep) {
		datlen = bhp->bh_datalen;
		caplen = bhp->bh_caplen;
		hdrlen = bhp->bh_hdrlen;

		if (caplen != datlen)
			syslog(LOG_ERR,
			       "bpf: short packet dropped (%d of %d bytes)",
			       caplen, datlen);
		else if (caplen > sizeof(struct rmp_packet))
			syslog(LOG_ERR, "bpf: large packet dropped (%d bytes)",
			       caplen);
		else {
			rconn->rmplen = caplen;
			bcopy((char *)&bhp->bh_tstamp, (char *)&rconn->tstamp,
			      sizeof(struct timeval));
			bcopy((char *)bp + hdrlen, (char *)&rconn->rmp, caplen);
		}
		bp += BPF_WORDALIGN(caplen + hdrlen);
		return(1);
	}
#undef bhp

	return(0);
}

/*
**  BpfWrite -- Write packet to BPF device.
**
**	Parameters:
**		rconn - packet to send.
**
**	Returns:
**		True if write succeeded, False otherwise.
**
**	Side Effects:
**		None.
*/
D 2

E 2
I 2
int
E 2
BpfWrite(rconn)
	RMPCONN *rconn;
{
	if (write(BpfFd, (char *)&rconn->rmp, rconn->rmplen) < 0) {
		syslog(LOG_ERR, "write: %s: %m", EnetStr(rconn));
		return(0);
	}

	return(1);
}

/*
D 2
**  BpfOpen -- Close a BPF device.
E 2
I 2
**  BpfClose -- Close a BPF device.
E 2
**
**	Parameters:
**		None.
**
**	Returns:
**		Nothing.
**
**	Side Effects:
**		None.
*/
D 2

E 2
I 2
void
E 2
BpfClose()
{
	struct ifreq ifr;

	if (BpfPkt != NULL) {
		free((char *)BpfPkt);
		BpfPkt = NULL;
	}

	if (BpfFd == -1)
		return;

#ifdef MSG_EOR
	ifr.ifr_addr.sa_len = RMP_ADDRLEN + 2;
#endif
	ifr.ifr_addr.sa_family = AF_UNSPEC;
	bcopy(&RmpMcastAddr[0], (char *)&ifr.ifr_addr.sa_data[0], RMP_ADDRLEN);
	if (ioctl(BpfFd, SIOCDELMULTI, (caddr_t)&ifr) < 0)
		(void) ioctl(BpfFd, BIOCPROMISC, (caddr_t)0);

	(void) close(BpfFd);
	BpfFd = -1;
}
E 1
