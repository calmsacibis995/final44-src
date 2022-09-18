h43514
s 00002/00002/00814
d D 8.9 95/01/09 17:54:23 cgd 52 51
c 64-bit changes: casts, and ioctl cmds are u_longs
e
s 00006/00001/00810
d D 8.8 94/10/09 21:04:09 mckusick 51 50
c When the line discipline is changed from term to slip,
c ttyclose() is called and then slopen(). This leaves t_state
c cleared. Set TS_ISOPEN and TS_XCLUDE so further opens on /dev/xxx
c see that the device is still being used by the slip process (from ralph)
e
s 00000/00002/00811
d D 8.7 94/08/05 16:44:39 mckusick 50 49
c delete redundant declaration of time (from cgd)
e
s 00001/00000/00812
d D 8.6 94/02/01 22:08:10 cgd 49 48
c get SLIP ioctl and BPF info from <net/slip.h>
e
s 00000/00001/00812
d D 8.5 94/01/12 09:31:21 bostic 48 47
c lint
e
s 00127/00030/00686
d D 8.4 94/01/07 18:19:37 cgd 47 46
c add BPF support. compress all packets. stabilize error-prone lines.
e
s 00000/00001/00716
d D 8.3 94/01/04 21:48:10 bostic 46 45
c lint
e
s 00000/00002/00717
d D 8.2 93/09/21 08:02:00 bostic 45 44
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00717
d D 8.1 93/06/10 22:44:53 bostic 44 43
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00003/00706
d D 7.32 93/06/04 17:31:25 bostic 43 42
c prototype everything
e
s 00000/00008/00709
d D 7.31 93/02/25 16:45:14 sklower 42 41
c MULTICAST is now standard
e
s 00023/00022/00694
d D 7.30 92/10/11 11:49:01 bostic 41 40
c make kernel includes standard
e
s 00031/00001/00685
d D 7.29 92/07/06 15:28:45 sklower 40 39
c multicast changes from lbl
e
s 00001/00000/00685
d D 7.28 92/06/02 21:14:09 mckusick 39 38
c init if_next to NULL
e
s 00004/00002/00681
d D 7.27 92/03/15 00:21:12 torek 38 37
c set ip before we use it; gcc lint
e
s 00002/00002/00681
d D 7.26 92/01/30 11:43:29 torek 37 36
c checked in for torek by sklower; Mike agrees to all these changes
e
s 00010/00055/00673
d D 7.25 92/01/14 17:35:13 karels 36 35
c remove compat crap, other cleanups; remove old port-number peek
c for fast queue (use IP TOS instead)
e
s 00056/00039/00672
d D 7.24 92/01/14 16:08:41 karels 35 34
c check in temporary version with compatibility hacks
e
s 00013/00012/00698
d D 7.23 91/10/16 15:52:53 william 34 33
c added link level control bits so we can pass mode info to a given 
c link layer protocol. for example, to enable slip compression.
e
s 00010/00009/00700
d D 7.22 91/04/20 16:38:44 karels 33 32
c new proc, user; rm user.h; remove TIOCGETD hack returning unit
e
s 00001/00011/00708
d D 7.21 90/06/28 21:30:58 bostic 32 31
c new copyright notice
e
s 00000/00001/00719
d D 7.20 90/04/05 11:47:10 marc 31 30
c drop unnecessary include of dir.h (checked in by sklower)
e
s 00075/00039/00645
d D 7.19 90/01/20 17:33:42 sam 30 29
c update from van: add "auto enable" of compression (if auto 
c enable flag is set on if and a compressed packet is received, then 
c enable compression on output); also separates i/o mru/mtu 
e
s 00010/00000/00674
d D 7.18 89/09/25 13:22:10 sklower 29 28
c put in SNMP changes
e
s 00027/00028/00647
d D 7.17 89/09/04 12:51:28 karels 28 27
c minor cleanups
e
s 00273/00251/00402
d D 7.16 89/06/30 18:15:54 karels 27 26
c merge new code from van, sundry cleanups
e
s 00125/00021/00528
d D 7.15 89/06/29 09:04:36 william 26 25
c checkpoint; working without compression
e
s 00015/00005/00534
d D 7.14 89/06/22 13:05:16 william 25 24
c fixed induced bug due to new link layer support (thx mike), added
c support for loss of carrier determination for sliplogin
e
s 00003/00002/00536
d D 7.13 89/04/26 18:56:17 mckusick 24 23
c use new form of suser()
e
s 00001/00001/00537
d D 7.12 89/04/25 11:06:25 mckusick 23 22
c ../machine => machine
e
s 00006/00005/00532
d D 7.11 89/04/22 12:11:14 sklower 22 20
c checkpoint at first working tp4 connection; before gnodes
e
s 00000/00000/00546
d D 7.6.1.2 89/02/15 08:59:10 karels 21 16
i 19 18 17
c update branch for net release
e
s 00023/00032/00514
d D 7.10 88/10/12 14:41:18 karels 20 19
c mark state of working kernel before var. length sockaddrs
e
s 00010/00005/00536
d D 7.9 88/06/27 18:59:34 bostic 19 18
c install approved copyright notice
e
s 00001/00001/00540
d D 7.8 88/05/20 12:03:30 karels 18 17
c make the code agree with the comment
e
s 00004/00004/00537
d D 7.7 88/04/07 13:20:54 karels 17 15
c CLBYTES => MCLBYTES
e
s 00001/00001/00540
d D 7.6.1.1 88/03/15 12:28:34 karels 16 15
c branch for network release (dk.h for dkstat.h XXX)
e
s 00006/00017/00535
d D 7.6 88/03/15 12:27:52 karels 15 13
c from torek, don't let OACTIVE get out of sync with BUSY/outq.c_cc
e
s 00006/00018/00534
d R 7.6 88/03/15 12:25:55 karels 14 13
c from torek
e
s 00013/00001/00539
d D 7.5 87/12/30 11:57:30 bostic 13 12
c add Berkeley header
e
s 00001/00003/00539
d D 7.4 87/08/13 13:36:39 bostic 12 11
c include mtpr.h for tahoe too
e
s 00001/00001/00541
d D 7.3 87/05/08 11:12:05 sam 11 10
c dk.h -> dkstat.h (from rusty@weyl.berkeley.edu)
e
s 00003/00000/00539
d D 7.2 86/09/04 11:35:31 karels 10 9
c MCLALLOC must be called at splimp
e
s 00000/00000/00539
d D 7.1 86/06/04 23:40:20 mckusick 9 8
c 4.3BSD release version
e
s 00001/00001/00538
d D 5.8 86/06/03 09:42:38 karels 8 7
c use the right include
e
s 00001/00001/00538
d D 5.7 86/05/15 09:27:52 karels 7 6
c I prefer this fix...
e
s 00002/00002/00537
d D 5.6 86/05/14 20:16:56 mckusick 6 5
c serial line crashes on big packets or heavy traffic (from Keith Muller)
e
s 00002/00000/00537
d D 5.5 86/05/03 08:49:46 mckusick 5 4
c make forward progress for large packets (from Keith Muller)
e
s 00004/00000/00533
d D 5.4 86/03/17 12:26:07 karels 4 3
c drop and return error if no carrier
e
s 00182/00112/00351
d D 5.3 86/02/23 23:22:46 karels 3 2
c lint
e
s 00004/00001/00459
d D 5.2 86/02/09 19:27:25 karels 2 1
c Berkelify
e
s 00460/00000/00000
d D 5.1 86/02/09 17:14:19 karels 1 0
c from Chris Torek, from Rick Adams
e
u
U
f b 
t
T
I 2
D 13
/*	%W% (Berkeley) %G% */
E 13
I 13
/*
D 27
 * Copyright (c) 1987 Regents of the University of California.
E 27
I 27
D 36
 * Copyright (c) 1987, 1989 Regents of the University of California.
E 36
I 36
D 44
 * Copyright (c) 1987, 1989, 1992 Regents of the University of California.
E 36
E 27
 * All rights reserved.
E 44
I 44
 * Copyright (c) 1987, 1989, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 44
 *
D 32
 * Redistribution and use in source and binary forms are permitted
D 19
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 19
I 19
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 32
I 32
 * %sccs.include.redist.c%
E 32
E 19
 *
 *	%W% (Berkeley) %G%
 */
E 13

E 2
I 1
/*
 * Serial Line interface
 *
 * Rick Adams
 * Center for Seismic Studies
 * 1300 N 17th Street, Suite 1450
 * Arlington, Virginia 22209
 * (703)276-7900
 * rick@seismo.ARPA
 * seismo!rick
 *
D 3
 * Some things done here could obviously be done in a better way,
 * but they were done this way to minimize the number of files
 * that had to be changed to accomodate this device.
D 2
 * A lot of this code belongs in the tty driver.
E 2
 *
E 3
 * Pounded on heavily by Chris Torek (chris@mimsy.umd.edu, umcp-cs!chris).
D 3
 * N.B.: this belongs in netinet, not vaxif, the way it stands now.
E 3
I 3
 * N.B.: this belongs in netinet, not net, the way it stands now.
E 3
I 2
 * Should have a link-layer type designation, but wouldn't be
 * backwards-compatible.
E 2
 *
 * Converted to 4.3BSD Beta by Chris Torek.
I 3
 * Other changes made at Berkeley, based in part on code by Kirk Smith.
I 26
D 27
 * W. Jolitz, added slip abort & time domain window
 * also added Van Jacobson's hdr compression code
E 27
I 27
 * W. Jolitz added slip abort.
 *
 * Hacked almost beyond recognition by Van Jacobson (van@helios.ee.lbl.gov).
 * Added priority queuing for "interactive" traffic; hooks for TCP
 * header compression; ICMP filtering (at 2400 baud, some cretin
 * pinging you can use up all your bandwidth).  Made low clist behavior
 * more robust and slightly less likely to hang serial line.
 * Sped up a bunch of things.
 * 
 * Note that splimp() is used throughout to block both (tty) input
 * interrupts and network activity; thus, splimp must be >= spltty.
E 27
E 26
E 3
 */

D 27
/* $Header: if_sl.c,v 1.12 85/12/20 21:54:55 chris Exp $ */
E 27
I 27
D 34
/* $Header: if_sl.c,v 1.7 89/05/31 02:24:52 van Exp $ */
E 34
I 34
D 35
/* $Header: /usr/src/sys/net/RCS/if_sl.c,v 1.1 91/08/30 11:14:57 william Exp Locker: william $ */
E 34
E 27
/* from if_sl.c,v 1.11 84/10/04 12:54:47 rick Exp */

E 35
#include "sl.h"
#if NSL > 0

I 47
#include "bpfilter.h"

E 47
D 41
#include "param.h"
I 26
D 31
#include "dir.h"
E 31
E 26
I 25
D 33
#include "user.h"
E 33
I 33
#include "proc.h"
E 33
E 25
#include "mbuf.h"
#include "buf.h"
I 3
D 11
#include "dk.h"
E 11
I 11
D 16
#include "dkstat.h"
E 16
I 16
#include "dk.h"
E 16
E 11
E 3
#include "socket.h"
#include "ioctl.h"
I 3
#include "file.h"
E 3
#include "tty.h"
I 26
#include "kernel.h"
#include "conf.h"
I 37
#include "machine/cpu.h"
E 41
I 41
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/mbuf.h>
#include <sys/buf.h>
#include <sys/dkstat.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <sys/tty.h>
#include <sys/kernel.h>
#include <sys/conf.h>
E 41
E 37
E 26
D 33
#include "errno.h"
E 33

D 3
#include "../net/if.h"
#include "../net/netisr.h"
#include "../net/route.h"
E 3
I 3
D 41
#include "if.h"
I 29
#include "if_types.h"
E 29
#include "netisr.h"
#include "route.h"
E 41
I 41
#include <machine/cpu.h>
E 41
I 37

I 41
#include <net/if.h>
#include <net/if_types.h>
#include <net/netisr.h>
#include <net/route.h>

E 41
E 37
#if INET
E 3
D 33
#include "../netinet/in.h"
#include "../netinet/in_systm.h"
I 8
#include "../netinet/in_var.h"
E 8
#include "../netinet/ip.h"
E 33
I 33
D 41
#include "netinet/in.h"
#include "netinet/in_systm.h"
#include "netinet/in_var.h"
#include "netinet/ip.h"
E 41
I 41
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/in_var.h>
#include <netinet/ip.h>
E 41
#else
Huh? Slip without inet?
E 33
I 26
D 27
#include "slcompress.h"
E 27
E 26
D 8
#include "../netinet/ip_var.h"
E 8
I 3
#endif
I 26
D 27
#include "if_slvar.h"
E 27
E 26
E 3
D 37

D 12
#ifdef vax
#include "../vax/mtpr.h"
#endif vax
E 12
I 12
D 23
#include "../machine/mtpr.h"
E 23
I 23
#include "machine/mtpr.h"
E 37
E 23
E 12

I 27
D 41
#include "slcompress.h"
#include "if_slvar.h"
E 41
I 41
#include <net/slcompress.h>
#include <net/if_slvar.h>
I 49
#include <net/slip.h>
E 49
E 41

I 47
#if NBPFILTER > 0
#include <sys/time.h>
#include <net/bpf.h>
#endif

E 47
E 27
/*
D 3
 * N.B.: SLMTU is now a hard limit on input packet size.  Some limit
 * is required, lest we use up all mbufs in the case of deleterious data
 * dribbling down the line.
E 3
I 3
D 27
 * N.B.: SLMTU is now a hard limit on input packet size.
D 17
 * SLMTU must be <= CLBYTES - sizeof(struct ifnet *).
E 17
I 17
 * SLMTU must be <= MCLBYTES - sizeof(struct ifnet *).
E 27
I 27
D 30
 * SLMTU is a hard limit on input packet size.  To simplify the code
E 30
I 30
 * SLMAX is a hard limit on input packet size.  To simplify the code
E 30
 * and improve performance, we require that packets fit in an mbuf
D 30
 * cluster, that there be enough extra room for the ifnet pointer that
 * IP input requires and, if we get a compressed packet, there's
 * enough extra room to expand the header into a max length tcp/ip
 * header (128 bytes).  So, SLMTU can be at most
D 28
 * 	MCLBYTES - sizeof(struct ifnet *) - 128 
E 28
I 28
 * 	MCLBYTES - 128 
E 30
I 30
 * cluster, and if we get a compressed packet, there's enough extra
 * room to expand the header into a max length tcp/ip header (128
 * bytes).  So, SLMAX can be at most
 *	MCLBYTES - 128
E 30
E 28
 *
D 30
 * To insure we get good interactive response, the MTU wants to be
 * the smallest size that amortizes the header cost.  (Remember
 * that even with type-of-service queuing, we have to wait for any
 * in-progress packet to finish.  I.e., we wait, on the average,
 * 1/2 * mtu / cps, where cps is the line speed in characters per
 * second.  E.g., 533ms wait for a 1024 byte MTU on a 9600 baud
 * line.  The average compressed header size is 6-8 bytes so any
 * MTU > 90 bytes will give us 90% of the line bandwidth.  A 100ms
 * wait is tolerable (500ms is not), so want an MTU around 256.
 * (Since TCP will send 212 byte segments (to allow for 40 byte
 * headers), the typical packet size on the wire will be around 220
 * bytes).  In 4.3tahoe+ systems, we can set an MTU in a route
 * so we do that & leave the interface MTU relatively high (so we
 * don't IP fragment when acting as a gateway to someone using a
 * stupid MTU).
E 30
I 30
 * SLMTU is a hard limit on output packet size.  To insure good
 * interactive response, SLMTU wants to be the smallest size that
 * amortizes the header cost.  (Remember that even with
 * type-of-service queuing, we have to wait for any in-progress
 * packet to finish.  I.e., we wait, on the average, 1/2 * mtu /
 * cps, where cps is the line speed in characters per second.
 * E.g., 533ms wait for a 1024 byte MTU on a 9600 baud line.  The
 * average compressed header size is 6-8 bytes so any MTU > 90
 * bytes will give us 90% of the line bandwidth.  A 100ms wait is
 * tolerable (500ms is not), so want an MTU around 296.  (Since TCP
 * will send 256 byte segments (to allow for 40 byte headers), the
 * typical packet size on the wire will be around 260 bytes).  In
 * 4.3tahoe+ systems, we can set an MTU in a route so we do that &
 * leave the interface MTU relatively high (so we don't IP fragment
 * when acting as a gateway to someone using a stupid MTU).
 *
 * Similar considerations apply to SLIP_HIWAT:  It's the amount of
 * data that will be queued 'downstream' of us (i.e., in clists
 * waiting to be picked up by the tty output interrupt).  If we
 * queue a lot of data downstream, it's immune to our t.o.s. queuing.
 * E.g., if SLIP_HIWAT is 1024, the interactive traffic in mixed
 * telnet/ftp will see a 1 sec wait, independent of the mtu (the
 * wait is dependent on the ftp window size but that's typically
 * 1k - 4k).  So, we want SLIP_HIWAT just big enough to amortize
 * the cost (in idle time on the wire) of the tty driver running
 * off the end of its clists & having to call back slstart for a
 * new packet.  For a tty interface with any buffering at all, this
 * cost will be zero.  Even with a totally brain dead interface (like
 * the one on a typical workstation), the cost will be <= 1 character
 * time.  So, setting SLIP_HIWAT to ~100 guarantees that we'll lose
 * at most 1% while maintaining good interactive response.
E 30
E 27
E 17
E 3
 */
D 27
#define	SLMTU	1006
I 3
#define	SLIP_HIWAT	1000	/* don't start a new packet if HIWAT on queue */
#define	CLISTRESERVE	1000	/* Can't let clists get too low */
E 3

E 27
I 27
D 28
#define	SLMTU	576
#define BUFOFFSET (128+sizeof(struct ifnet **))
E 28
I 28
D 30
#define	SLMTU		576
E 30
D 47
#define BUFOFFSET	128
E 47
I 47
#if NBPFILTER > 0
#define	BUFOFFSET	(128+sizeof(struct ifnet **)+SLIP_HDRLEN)
#else
#define	BUFOFFSET	(128+sizeof(struct ifnet **))
#endif
E 47
D 30
#define	SLBUFSIZE	(SLMTU + BUFOFFSET)
E 28
#define	SLIP_HIWAT	1024	/* don't start a new packet if HIWAT on queue */
E 30
I 30
#define	SLMAX		(MCLBYTES - BUFOFFSET)
#define	SLBUFSIZE	(SLMAX + BUFOFFSET)
#define	SLMTU		296
#define	SLIP_HIWAT	roundup(50,CBSIZE)
E 30
#define	CLISTRESERVE	1024	/* Can't let clists get too low */
I 28

E 28
E 27
D 26
struct sl_softc {
	struct	ifnet sc_if;	/* network-visible interface */
	short	sc_flags;	/* see below */
	short	sc_ilen;	/* length of input-packet-so-far */
	struct	tty *sc_ttyp;	/* pointer to tty structure */
	char	*sc_mp;		/* pointer to next available buf char */
D 3
	char	sc_buf[SLMTU];	/* input buffer */
E 3
I 3
	char	*sc_buf;	/* input buffer */
E 3
} sl_softc[NSL];
E 26
I 26
/*
 * SLIP ABORT ESCAPE MECHANISM:
 *	(inspired by HAYES modem escape arrangement)
 *	1sec escape 1sec escape 1sec escape { 1sec escape 1sec escape }
D 35
 *	signals a "soft" exit from slip mode by usermode process
E 35
I 35
 *	within window time signals a "soft" exit from slip mode by remote end
I 36
 *	if the IFF_DEBUG flag is on.
E 36
E 35
D 27
 *	(hard exit unimplemented -- currently system dependant)
E 27
 */
E 26
D 36

E 36
D 26
/* flags */
#define	SC_ESCAPED	0x0001	/* saw a FRAME_ESCAPE */
E 26
I 26
#define	ABT_ESC		'\033'	/* can't be t_intr - distant host must know it*/
D 35
#define ABT_WAIT	1	/* in seconds - idle before an escape & after */
#define ABT_RECYCLE	(5*2+2)	/* in seconds - time window processing abort */
E 35
I 35
D 47
#define ABT_IDLE	1	/* in seconds - idle before an escape */
#define ABT_COUNT	3	/* count of escapes for abort */
#define ABT_WINDOW	(ABT_COUNT*2+2)	/* in seconds - time to count */
E 47
I 47
#define	ABT_IDLE	1	/* in seconds - idle before an escape */
#define	ABT_COUNT	3	/* count of escapes for abort */
#define	ABT_WINDOW	(ABT_COUNT*2+2)	/* in seconds - time to count */
E 47
E 35
E 26
D 15
#define	SC_OACTIVE	0x0002	/* output tty is active */
E 15

I 26
D 27
/* a "soft" abort means to pass a suggestion to user code to abort slip */
E 27
D 35
#define ABT_SOFT	3	/* count of escapes */
E 35
D 36

I 35
#ifdef nomore
E 35
D 27
/* a "hard" abort means to force abort slip within the kernel -- process jam? */
#define ABT_HARD	5	/* count of escapes */

E 27
/*
D 27
 * SLIP TIME WINDOW:
 *	Only accept packets with octets that come at least this often.
 *	With non-reliable but fast modems (FAX, Packet Radio), we assume that
 *	packets come in groups (time domain), and that fractional groups that
 *	come erratically are just noise that will foul subsequent packets.
 *	We reject them on a time filter basis.
 *
 *	This is a very coarse filter, because error correcting modems like the
 *	telebit take there own sweet time encoding/decoding packets. If you
 *	are using an MNP,PEP or other such arrangement, this won't help much.
 *	If you are using packet radio, use the millisecond time val with
 *	as small a resolution as possible. In any case, the coarse filter
 *	saves noisey lines about 50 % of the time.
E 27
I 27
 * The following disgusting hack gets around the problem that IP TOS
D 28
 * can't be set in BSD/Sun OS yet.  We want to put "interactive"
 * traffic on a high priority queue.  To decide if traffic is
 * interactive, we check that a) it is TCP and b) one of it's ports
 * if telnet, rlogin or ftp control.
E 28
I 28
 * can't be set yet.  We want to put "interactive" traffic on a high
 * priority queue.  To decide if traffic is interactive, we check that
 * a) it is TCP and b) one of its ports is telnet, rlogin or ftp control.
E 28
E 27
 */
I 27
static u_short interactive_ports[8] = {
	0,	513,	0,	0,
	0,	21,	0,	23,
};
#define INTERACTIVE(p) (interactive_ports[(p) & 7] == (p))
I 35
#endif
E 35
E 27

E 36
D 27
#define	TIME_WINDOW	2	/* max seconds between valid packet chars */
E 27
I 27
struct sl_softc sl_softc[NSL];
E 27

D 27
struct sl_softc	 sl_softc[NSL];
E 27
I 27
#define FRAME_END	 	0xc0		/* Frame End */
#define FRAME_ESCAPE		0xdb		/* Frame Esc */
#define TRANS_FRAME_END	 	0xdc		/* transposed frame end */
#define TRANS_FRAME_ESCAPE 	0xdd		/* transposed frame esc */
E 27

E 26
D 27
#define FRAME_END	 	0300		/* Frame End */
#define FRAME_ESCAPE		0333		/* Frame Esc */
#define TRANS_FRAME_END	 	0334		/* transposed frame end */
#define TRANS_FRAME_ESCAPE 	0335		/* transposed frame esc */

E 27
D 45
#define t_sc T_LINEP

E 45
D 43
int sloutput(), slioctl(), ttrstrt();
E 43
I 29
D 50
extern struct timeval time;
E 29

E 50
I 43
static int slinit __P((struct sl_softc *));
static struct mbuf *sl_btom __P((struct sl_softc *, int));

E 43
/*
 * Called from boot code to establish sl interfaces.
 */
I 43
void
E 43
slattach()
{
	register struct sl_softc *sc;
	register int i = 0;

	for (sc = sl_softc; i < NSL; sc++) {
		sc->sc_if.if_name = "sl";
I 39
		sc->sc_if.if_next = NULL;
E 39
		sc->sc_if.if_unit = i++;
		sc->sc_if.if_mtu = SLMTU;
I 40
D 42
#ifdef MULTICAST
E 42
		sc->sc_if.if_flags =
		    IFF_POINTOPOINT | SC_AUTOCOMP | IFF_MULTICAST;
D 42
#else
E 40
D 36
		sc->sc_if.if_flags = IFF_POINTOPOINT;
E 36
I 36
		sc->sc_if.if_flags = IFF_POINTOPOINT | SC_AUTOCOMP;
I 40
#endif
E 42
E 40
E 36
I 29
		sc->sc_if.if_type = IFT_SLIP;
E 29
		sc->sc_if.if_ioctl = slioctl;
		sc->sc_if.if_output = sloutput;
D 27
		sc->sc_if.if_snd.ifq_maxlen = IFQ_MAXLEN;
E 27
I 27
		sc->sc_if.if_snd.ifq_maxlen = 50;
		sc->sc_fastq.ifq_maxlen = 32;
E 27
		if_attach(&sc->sc_if);
I 47
#if NBPFILTER > 0
		bpfattach(&sc->sc_bpf, &sc->sc_if, DLT_SLIP, SLIP_HDRLEN);
#endif
E 47
	}
}

I 27
static int
slinit(sc)
	register struct sl_softc *sc;
{
	register caddr_t p;

	if (sc->sc_ep == (u_char *) 0) {
		MCLALLOC(p, M_WAIT);
		if (p)
D 28
			sc->sc_ep = (u_char *)p + (BUFOFFSET + SLMTU);
E 28
I 28
			sc->sc_ep = (u_char *)p + SLBUFSIZE;
E 28
		else {
			printf("sl%d: can't allocate buffer\n", sc - sl_softc);
			sc->sc_if.if_flags &= ~IFF_UP;
			return (0);
		}
	}
D 30
	sc->sc_buf = sc->sc_ep - SLMTU;
E 30
I 30
	sc->sc_buf = sc->sc_ep - SLMAX;
E 30
	sc->sc_mp = sc->sc_buf;
	sl_compress_init(&sc->sc_comp);
	return (1);
}

E 27
/*
 * Line specific open routine.
 * Attach the given tty to the first available sl unit.
 */
I 3
/* ARGSUSED */
I 43
int
E 43
E 3
slopen(dev, tp)
	dev_t dev;
	register struct tty *tp;
{
I 33
	struct proc *p = curproc;		/* XXX */
E 33
	register struct sl_softc *sc;
	register int nsl;
I 24
	int error;
I 51
	int s;
E 51
E 24

D 3
	if (tp->t_sc != NULL)
E 3
I 3
D 24
	if (!suser())
		return (EPERM);
E 24
I 24
D 33
	if (error = suser(u.u_cred, &u.u_acflag))
E 33
I 33
	if (error = suser(p->p_ucred, &p->p_acflag))
E 33
		return (error);
I 27

E 27
E 24
	if (tp->t_line == SLIPDISC)
E 3
D 28
		return (EBUSY);
E 28
I 28
		return (0);
E 28

D 27
	for (nsl = 0, sc = sl_softc; nsl < NSL; nsl++, sc++)
E 27
I 27
	for (nsl = NSL, sc = sl_softc; --nsl >= 0; sc++)
E 27
		if (sc->sc_ttyp == NULL) {
D 27
			sc->sc_flags = 0;
			sc->sc_ilen = 0;
E 27
D 3
			sc->sc_mp = sc->sc_buf;
E 3
I 3
			if (slinit(sc) == 0)
				return (ENOBUFS);
I 26
D 27
#ifdef INET
			sl_compress_init(&sc->sc_comp);
#endif
E 27
E 26
E 3
			tp->t_sc = (caddr_t)sc;
			sc->sc_ttyp = tp;
I 29
			sc->sc_if.if_baudrate = tp->t_ospeed;
I 51
			s = spltty();
			tp->t_state |= TS_ISOPEN | TS_XCLUDE;
			splx(s);
E 51
E 29
I 3
			ttyflush(tp, FREAD | FWRITE);
E 3
			return (0);
		}
D 27

E 27
D 3
	return (ENOSPC);
E 3
I 3
	return (ENXIO);
E 3
}

/*
 * Line specific close routine.
 * Detach the tty from the sl unit.
D 43
 * Mimics part of ttyclose().
E 43
 */
I 43
void
E 43
slclose(tp)
	struct tty *tp;
{
	register struct sl_softc *sc;
	int s;

	ttywflush(tp);
I 27
	s = splimp();		/* actually, max(spltty, splnet) */
E 27
	tp->t_line = 0;
I 51
	tp->t_state = 0;
E 51
D 27
	s = splimp();		/* paranoid; splnet probably ok */
E 27
	sc = (struct sl_softc *)tp->t_sc;
	if (sc != NULL) {
		if_down(&sc->sc_if);
		sc->sc_ttyp = NULL;
		tp->t_sc = NULL;
I 3
D 27
		MCLFREE((struct mbuf *)sc->sc_buf);
E 27
I 27
D 28
		MCLFREE((struct mbuf *)(sc->sc_ep - (SLMTU + BUFOFFSET)));
E 28
I 28
		MCLFREE((caddr_t)(sc->sc_ep - SLBUFSIZE));
E 28
		sc->sc_ep = 0;
		sc->sc_mp = 0;
E 27
		sc->sc_buf = 0;
I 26
D 27
		sc->sc_mp = (char *) 4; /*XXX!?! */
E 27
E 26
E 3
	}
	splx(s);
}

/*
 * Line specific (tty) ioctl routine.
 * Provide a way to get the sl unit number.
 */
I 3
/* ARGSUSED */
I 43
int
E 43
E 3
sltioctl(tp, cmd, data, flag)
	struct tty *tp;
I 38
D 52
	int cmd;
E 52
I 52
	u_long cmd;
E 52
E 38
	caddr_t data;
I 38
	int flag;
E 38
{
I 26
	struct sl_softc *sc = (struct sl_softc *)tp->t_sc;
I 47
D 48
	int s;
E 48
E 47
D 46
	int s;
E 46
E 26

D 26
	if (cmd == TIOCGETD) {
		*(int *)data = ((struct sl_softc *)tp->t_sc)->sc_if.if_unit;
		return (0);
	}
I 25
	if (cmd == TIOCMGET) {
E 26
I 26
	switch (cmd) {
D 27
	case TIOCGETD:
E 27
I 27
D 33
	case TIOCGETD:				/* XXX */
	case SLIOGUNIT:
E 33
I 33
	case SLIOCGUNIT:
E 33
E 27
		*(int *)data = sc->sc_if.if_unit;
		break;
D 27
	case TIOCMGET:
E 26
		if (tp->t_state&TS_CARR_ON)
			*(int *)data = TIOCM_CAR ;
D 26
		else
			*(int *)data = 0 ;
		return (0);
E 26
I 26
		else	*(int *)data = 0 ;
E 27

I 35
D 36
#ifdef notdef
E 35
D 27
		if (sc->sc_flags&SC_ABORT)
			*(int *)data |= TIOCM_DTR ;
		break;
E 27
	case SLIOCGFLAGS:
D 34
		*(int *)data = sc->sc_flags;
E 34
I 34
		*(int *)data = sc->sc_if.if_flags;
E 34
		break;
I 35
#endif
E 35
I 27

E 27
	case SLIOCSFLAGS:
D 30
#define	SC_MASK	(SC_COMPRESS|SC_NOICMP)
E 30
I 30
D 34
#define	SC_MASK	0xffff
E 34
I 34
D 35
#define	LLC_MASK	(IFF_LLC0|IFF_LLC1|IFF_LLC2)
E 35
E 34
E 30
		s = splimp();
D 34
		sc->sc_flags =
		    (sc->sc_flags &~ SC_MASK) | ((*(int *)data) & SC_MASK);
E 34
I 34
D 35
		sc->sc_if.if_flags =
			(sc->sc_if.if_flags &~ LLC_MASK)
			| ((*(int *)data) & LLC_MASK);
E 35
I 35
		/* temp compat */
		sc->sc_if.if_flags &= ~(SC_COMPRESS | SC_NOICMP | SC_AUTOCOMP);
		if (*(int *)data & 0x2)
			sc->sc_if.if_flags |= SC_COMPRESS;
		if (*(int *)data & 0x4)
			sc->sc_if.if_flags |= SC_NOICMP;
		if (*(int *)data & 0x8)
			sc->sc_if.if_flags |= SC_AUTOCOMP;
E 35
E 34
		splx(s);
		break;
I 27

E 36
E 27
	default:
		return (-1);
E 26
	}
E 25
D 26
	return (-1);
E 26
I 26
	return (0);
E 26
}

/*
 * Queue a packet.  Start transmission if not active.
I 47
 * Compression happens in slstart; if we do it here, IP TOS
 * will cause us to not compress "background" packets, because
 * ordering gets trashed.  It can be done for all packets in slstart.
E 47
 */
D 43
sloutput(ifp, m, dst)
E 43
I 43
int
sloutput(ifp, m, dst, rtp)
E 43
D 28
	register struct ifnet *ifp;
E 28
I 28
	struct ifnet *ifp;
E 28
	register struct mbuf *m;
	struct sockaddr *dst;
I 43
	struct rtentry *rtp;
E 43
{
D 28
	register struct sl_softc *sc;
E 28
I 28
	register struct sl_softc *sc = &sl_softc[ifp->if_unit];
E 28
I 27
	register struct ip *ip;
	register struct ifqueue *ifq;
I 36
D 47
	register int p;
E 47
E 36
E 27
	int s;

	/*
	 * `Cannot happen' (see slioctl).  Someday we will extend
	 * the line protocol to support other address families.
	 */
	if (dst->sa_family != AF_INET) {
D 28
		printf("sl%d: af%d not supported\n", ifp->if_unit,
E 28
I 28
		printf("sl%d: af%d not supported\n", sc->sc_if.if_unit,
E 28
			dst->sa_family);
		m_freem(m);
I 35
		sc->sc_if.if_noproto++;
E 35
		return (EAFNOSUPPORT);
	}

D 28
	sc = &sl_softc[ifp->if_unit];
E 28
	if (sc->sc_ttyp == NULL) {
		m_freem(m);
		return (ENETDOWN);	/* sort of */
	}
I 4
D 47
	if ((sc->sc_ttyp->t_state & TS_CARR_ON) == 0) {
E 47
I 47
	if ((sc->sc_ttyp->t_state & TS_CARR_ON) == 0 &&
	    (sc->sc_ttyp->t_cflag & CLOCAL) == 0) {
E 47
		m_freem(m);
		return (EHOSTUNREACH);
	}
E 4
D 27
	s = splimp();
I 26
#ifdef INET
	if (sc->sc_flags & (SC_COMPRESS|SC_NOICMP)) {
		register struct ip *ip = mtod(m, struct ip *);
		if (ip->ip_p == IPPROTO_TCP) {
			/* add stuff to TOS routing */
			if (sc->sc_flags & SC_COMPRESS)
				(void) sl_compress_tcp(m, ip, &sc->sc_comp);
		} else if ((sc->sc_flags & SC_NOICMP) &&
		    ip->ip_p == IPPROTO_ICMP) {
			m_freem(m);
			splx(s);
			return (0);
E 27
I 27
D 28
	ifq = &ifp->if_snd;
E 28
I 28
	ifq = &sc->sc_if.if_snd;
I 38
	ip = mtod(m, struct ip *);
E 38
E 28
D 36
	if ((ip = mtod(m, struct ip *))->ip_p == IPPROTO_TCP) {
I 35
#ifdef nomore
E 35
		register int p = ((int *)ip)[ip->ip_hl];
E 36
I 36
D 47
	if (ip->ip_tos & IPTOS_LOWDELAY) {
		ifq = &sc->sc_fastq;
		p = 1;
	} else
		p = 0;
E 36
D 38

D 30
		if (INTERACTIVE(p & 0xffff) || INTERACTIVE(p >> 16))
E 30
I 30
D 36
		if (INTERACTIVE(p & 0xffff) || INTERACTIVE(p >> 16)) {
E 30
			ifq = &sc->sc_fastq;
I 30
			p = 1;
		} else
			p = 0;
I 35
#else
		register int p;
E 35
E 30

I 35
		if (ip->ip_tos & IPTOS_LOWDELAY) {
			ifq = &sc->sc_fastq;
			p = 1;
		} else
			p = 0;
#endif

E 36
I 36
	if ((ip = mtod(m, struct ip *))->ip_p == IPPROTO_TCP) {
E 38
I 38
	if (ip->ip_p == IPPROTO_TCP) {
E 38
E 36
E 35
D 34
		if (sc->sc_flags & SC_COMPRESS) {
E 34
I 34
		if (sc->sc_if.if_flags & SC_COMPRESS) {
E 34
D 30
			/* if two copies of sl_compress_tcp are running
			 * for the same line, the compression state can
			 * get screwed up.  We're assuming that sloutput
			 * was invoked at splnet so this isn't possible
			 * (this assumption is correct for 4.xbsd, x<=4).
			 * In a multi-threaded kernel, a lockout might
			 * be needed here. */
			p = sl_compress_tcp(m, ip, &sc->sc_comp);
E 30
I 30
			/*
			 * The last parameter turns off connection id
			 * compression for background traffic:  Since
			 * fastq traffic can jump ahead of the background
			 * traffic, we don't know what order packets will
			 * go on the line.
			 */
			p = sl_compress_tcp(m, ip, &sc->sc_comp, p);
E 30
			*mtod(m, u_char *) |= p;
E 27
		}
I 27
D 34
	} else if (sc->sc_flags & SC_NOICMP && ip->ip_p == IPPROTO_ICMP) {
E 34
I 34
	} else if (sc->sc_if.if_flags & SC_NOICMP && ip->ip_p == IPPROTO_ICMP) {
E 47
I 47
	if (sc->sc_if.if_flags & SC_NOICMP && ip->ip_p == IPPROTO_ICMP) {
E 47
E 34
		m_freem(m);
D 35
		return (0);
E 35
I 35
		return (ENETRESET);		/* XXX ? */
E 35
E 27
	}
I 47
	if (ip->ip_tos & IPTOS_LOWDELAY)
		ifq = &sc->sc_fastq;
E 47
D 27
#endif
E 26
	if (IF_QFULL(&ifp->if_snd)) {
		IF_DROP(&ifp->if_snd);
		splx(s);
E 27
I 27
	s = splimp();
	if (IF_QFULL(ifq)) {
		IF_DROP(ifq);
E 27
		m_freem(m);
I 27
		splx(s);
E 27
D 3
		sc->sc_if.if_collisions++;
E 3
I 3
		sc->sc_if.if_oerrors++;
E 3
		return (ENOBUFS);
	}
D 27
	IF_ENQUEUE(&ifp->if_snd, m);
E 27
I 27
	IF_ENQUEUE(ifq, m);
I 29
	sc->sc_if.if_lastchange = time;
E 29
E 27
D 15
	if ((sc->sc_flags & SC_OACTIVE) == 0) {
E 15
I 15
D 28
	if (sc->sc_ttyp->t_outq.c_cc == 0) {
E 15
		splx(s);
E 28
I 28
	if (sc->sc_ttyp->t_outq.c_cc == 0)
E 28
		slstart(sc->sc_ttyp);
D 28
	} else
		splx(s);
E 28
I 28
	splx(s);
E 28
	return (0);
}

/*
 * Start output on interface.  Get another datagram
 * to send from the interface queue and map it to
 * the interface before starting output.
 */
I 43
void
E 43
slstart(tp)
	register struct tty *tp;
{
	register struct sl_softc *sc = (struct sl_softc *)tp->t_sc;
	register struct mbuf *m;
D 3
	register int c, len;
	register u_char *mcp;
	int flush;
E 3
I 3
D 27
	register int len;
E 27
	register u_char *cp;
I 47
	register struct ip *ip;
E 47
D 15
	int flush, nd, np, n, s;
E 15
I 15
D 27
	int nd, np, n, s;
E 27
I 27
	int s;
E 27
E 15
	struct mbuf *m2;
I 47
#if NBPFILTER > 0
	u_char bpfbuf[SLMTU + SLIP_HDRLEN];
	register int len;
#endif
E 47
	extern int cfreecount;
E 3

D 3
	/*
	 * If there is more in the output queue, just send it now.
	 * We are being called in lieu of ttstart and must do what
	 * it would.
	 */
	if (tp->t_outq.c_cc > 0) {
		ttstart(tp);
		return;
	}
E 3
I 3
	for (;;) {
		/*
		 * If there is more in the output queue, just send it now.
		 * We are being called in lieu of ttstart and must do what
		 * it would.
		 */
D 27
		if (tp->t_outq.c_cc > 0)
			ttstart(tp);
		if (tp->t_outq.c_cc > SLIP_HIWAT)
			return;
E 3

E 27
I 27
		if (tp->t_outq.c_cc != 0) {
			(*tp->t_oproc)(tp);
			if (tp->t_outq.c_cc > SLIP_HIWAT)
				return;
		}
E 27
D 3
	/*
	 * This happens briefly when the line shuts down.
	 */
	if (sc == NULL)
		return;
E 3
I 3
		/*
		 * This happens briefly when the line shuts down.
		 */
		if (sc == NULL)
			return;
E 3

D 3
	/*
	 * Get a packet and map it to the interface.
	 */
	c = splimp();
	IF_DEQUEUE(&sc->sc_if.if_snd, m);
	if (m == NULL) {
		sc->sc_flags &= ~SC_OACTIVE;
		splx(c);
		return;
	}
	flush = !(sc->sc_flags & SC_OACTIVE);
	sc->sc_flags |= SC_OACTIVE;
	splx(c);
E 3
I 3
		/*
D 27
		 * If system is getting low on clists
		 * and we have something running already, stop here.
		 */
D 15
		if (cfreecount < CLISTRESERVE + SLMTU &&
		    sc->sc_flags & SC_OACTIVE)
E 15
I 15
D 18
		if (cfreecount < CLISTRESERVE + SLMTU && tp->t_outq.c_cc == 0)
E 18
I 18
		if (cfreecount < CLISTRESERVE + SLMTU && tp->t_outq.c_cc)
E 18
E 15
			return;
E 3

D 3
	/*
	 * The extra FRAME_END will start up a new packet, and thus
	 * will flush any accumulated garbage.  We do this whenever
	 * the line may have been idle for some time.
	 */
	if (flush)
		(void) putc(FRAME_END, &tp->t_outq);
E 3
I 3
		/*
E 27
		 * Get a packet and send it to the interface.
		 */
		s = splimp();
D 27
		IF_DEQUEUE(&sc->sc_if.if_snd, m);
E 27
I 27
		IF_DEQUEUE(&sc->sc_fastq, m);
D 35
		if (m == NULL)
E 35
I 35
		if (m)
			sc->sc_if.if_omcasts++;		/* XXX */
		else
E 35
			IF_DEQUEUE(&sc->sc_if.if_snd, m);
E 27
D 15
		if (m == NULL) {
			if (tp->t_outq.c_cc == 0)
				sc->sc_flags &= ~SC_OACTIVE;
			splx(s);
			return;
		}
		flush = !(sc->sc_flags & SC_OACTIVE);
		sc->sc_flags |= SC_OACTIVE;
E 15
		splx(s);
I 15
		if (m == NULL)
			return;
I 47

		/*
		 * We do the header compression here rather than in sloutput
		 * because the packets will be out of order if we are using TOS
		 * queueing, and the connection id compression will get
		 * munged when this happens.
		 */
#if NBPFILTER > 0
		if (sc->sc_bpf) {
			/*
			 * We need to save the TCP/IP header before it's
			 * compressed.  To avoid complicated code, we just
			 * copy the entire packet into a stack buffer (since
			 * this is a serial line, packets should be short
			 * and/or the copy should be negligible cost compared
			 * to the packet transmission time).
			 */
			register struct mbuf *m1 = m;
			register u_char *cp = bpfbuf + SLIP_HDRLEN;

			len = 0;
			do {
				register int mlen = m1->m_len;

				bcopy(mtod(m1, caddr_t), cp, mlen);
				cp += mlen;
				len += mlen;
			} while (m1 = m1->m_next);
		}
#endif
		if ((ip = mtod(m, struct ip *))->ip_p == IPPROTO_TCP) {
			if (sc->sc_if.if_flags & SC_COMPRESS)
				*mtod(m, u_char *) |= sl_compress_tcp(m, ip,
				    &sc->sc_comp, 1);
		}
#if NBPFILTER > 0
		if (sc->sc_bpf) {
			/*
			 * Put the SLIP pseudo-"link header" in place.  The
			 * compressed header is now at the beginning of the
			 * mbuf.
			 */
			bpfbuf[SLX_DIR] = SLIPDIR_OUT;
			bcopy(mtod(m, caddr_t), &bpfbuf[SLX_CHDR], CHDR_LEN);
			bpf_tap(sc->sc_bpf, bpfbuf, len + SLIP_HDRLEN);
		}
#endif
E 47
I 29
		sc->sc_if.if_lastchange = time;
I 34

E 34
E 29
I 27
		/*
		 * If system is getting low on clists, just flush our
		 * output queue (if the stuff was important, it'll get
		 * retransmitted).
		 */
		if (cfreecount < CLISTRESERVE + SLMTU) {
			m_freem(m);
			sc->sc_if.if_collisions++;
			continue;
		}
E 27
E 15
E 3
D 34

E 34
D 3
	while (m != NULL) {
		len = m->m_len;
		mcp = mtod(m, u_char *);
		while (--len >= 0) {
			c = *mcp++;
			if (c == FRAME_ESCAPE || c == FRAME_END) {
				if (putc(FRAME_ESCAPE, &tp->t_outq))
					goto full;
				c = c == FRAME_ESCAPE ? TRANS_FRAME_ESCAPE :
							TRANS_FRAME_END;
				if (putc(c, &tp->t_outq)) {
					(void) unputc(&tp->t_outq);
					goto full;
E 3
I 3
		/*
		 * The extra FRAME_END will start up a new packet, and thus
		 * will flush any accumulated garbage.  We do this whenever
		 * the line may have been idle for some time.
		 */
D 15
		if (flush)
E 15
I 15
D 27
		if (tp->t_outq.c_cc == 0)
E 27
I 27
		if (tp->t_outq.c_cc == 0) {
D 35
			++sc->sc_bytessent;
E 35
I 35
			++sc->sc_if.if_obytes;
E 35
E 27
E 15
			(void) putc(FRAME_END, &tp->t_outq);
I 27
		}
E 27

		while (m) {
D 27
			cp = mtod(m, u_char *);
			len = m->m_len;
			while (len > 0) {
E 27
I 27
			register u_char *ep;

			cp = mtod(m, u_char *); ep = cp + m->m_len;
			while (cp < ep) {
E 27
				/*
				 * Find out how many bytes in the string we can
				 * handle without doing something special.
				 */
D 27
				nd = locc(FRAME_ESCAPE, len, cp);
				np = locc(FRAME_END, len, cp);
				n = len - MAX(nd, np);
				if (n) {
E 27
I 27
				register u_char *bp = cp;

				while (cp < ep) {
					switch (*cp++) {
					case FRAME_ESCAPE:
					case FRAME_END:
						--cp;
						goto out;
					}
				}
				out:
				if (cp > bp) {
E 27
					/*
					 * Put n characters at once
					 * into the tty output queue.
					 */
D 27
					if (b_to_q((char *)cp, n, &tp->t_outq))
E 27
I 27
D 47
					if (b_to_q((char *)bp, cp - bp, &tp->t_outq))
E 47
I 47
					if (b_to_q((char *)bp, cp - bp,
					    &tp->t_outq))
E 47
E 27
						break;
I 5
D 27
					len -= n;
					cp += n;
E 27
I 27
D 35
					sc->sc_bytessent += cp - bp;
E 35
I 35
					sc->sc_if.if_obytes += cp - bp;
E 35
E 27
E 5
E 3
				}
D 3
			} else
				if (putc(c, &tp->t_outq))
					goto full;
E 3
I 3
				/*
				 * If there are characters left in the mbuf,
				 * the first one must be special..
				 * Put it out in a different form.
				 */
D 27
				if (len) {
E 27
I 27
				if (cp < ep) {
E 27
					if (putc(FRAME_ESCAPE, &tp->t_outq))
						break;
D 27
					if (putc(*cp == FRAME_ESCAPE ?
E 27
I 27
					if (putc(*cp++ == FRAME_ESCAPE ?
E 27
					   TRANS_FRAME_ESCAPE : TRANS_FRAME_END,
					   &tp->t_outq)) {
						(void) unputc(&tp->t_outq);
						break;
					}
D 27
					cp++;
					len--;
E 27
I 27
D 35
					sc->sc_bytessent += 2;
E 35
I 35
					sc->sc_if.if_obytes += 2;
E 35
E 27
				}
			}
			MFREE(m, m2);
			m = m2;
E 3
		}
D 3
		m = m_free(m);
E 3
I 3

		if (putc(FRAME_END, &tp->t_outq)) {
			/*
			 * Not enough room.  Remove a char to make room
			 * and end the packet normally.
			 * If you get many collisions (more than one or two
			 * a day) you probably do not have enough clists
			 * and you should increase "nclist" in param.c.
			 */
			(void) unputc(&tp->t_outq);
			(void) putc(FRAME_END, &tp->t_outq);
			sc->sc_if.if_collisions++;
D 27
		} else
			sc->sc_if.if_opackets++;
E 3
	}
I 3
}
E 3

D 3
	if (putc(FRAME_END, &tp->t_outq)) {
full:
		/*
		 * If you get many oerrors (more than one or two a day)
		 * you probably do not have enough clists and you should 
		 * increase "nclist" in param.c.
		 */
		(void) unputc(&tp->t_outq);	/* make room */
		putc(FRAME_END, &tp->t_outq);	/* end the packet */
		sc->sc_if.if_oerrors++;
	} else
		sc->sc_if.if_opackets++;
E 3
I 3
slinit(sc)
	register struct sl_softc *sc;
{
D 20
	struct mbuf *p;
E 20
I 20
	register caddr_t p;
E 20
E 3

D 3
	/*
	 * Start transmission.  Note that slstart, not ttstart, will be
	 * called when the transmission completes, be that after a single
	 * piece of what we have mapped, or be it after the entire thing
	 * has been sent.  That is why we need to check the output queue
	 * count at the top.
	 */
	ttstart(tp);
E 3
I 3
	if (sc->sc_buf == (char *) 0) {
I 10
D 15
		int s = splimp();

E 15
E 10
D 20
		MCLALLOC(p, 1);
E 20
I 20
		MCLALLOC(p, M_WAIT);
E 20
I 10
D 15
		splx(s);
E 15
E 10
		if (p) {
D 20
			sc->sc_buf = (char *)p;
			sc->sc_mp = sc->sc_buf + sizeof(struct ifnet *);
E 20
I 20
			sc->sc_buf = p;
			sc->sc_mp = p;
E 27
E 20
		} else {
D 27
			printf("sl%d: can't allocate buffer\n", sc - sl_softc);
			sc->sc_if.if_flags &= ~IFF_UP;
			return (0);
E 27
I 27
D 35
			++sc->sc_bytessent;
E 35
I 35
			++sc->sc_if.if_obytes;
E 35
			sc->sc_if.if_opackets++;
E 27
		}
I 29
D 35
		sc->sc_if.if_obytes = sc->sc_bytessent;
E 35
E 29
	}
D 27
	return (1);
E 27
E 3
}

/*
D 27
 * Copy data buffer to mbuf chain; add ifnet pointer ifp.
E 27
I 27
 * Copy data buffer to mbuf chain; add ifnet pointer.
E 27
 */
D 27
struct mbuf *
D 3
sl_btom(addr, len, ifp)
	register caddr_t addr;
E 3
I 3
sl_btom(sc, len, ifp)
	struct sl_softc *sc;
E 27
I 27
static struct mbuf *
sl_btom(sc, len)
	register struct sl_softc *sc;
E 27
E 3
	register int len;
D 27
	struct ifnet *ifp;
E 27
{
I 3
D 27
	register caddr_t cp;
E 3
	register struct mbuf *m, **mp;
D 3
	register int count;
E 3
I 3
	register unsigned count;
E 3
	struct mbuf *top = NULL;
E 27
I 27
D 28
	register u_char *cp;
E 28
	register struct mbuf *m;
E 27

I 3
D 25
	cp = sc->sc_buf + sizeof(struct ifnet *);
E 25
I 25
D 27
	cp = sc->sc_buf;
E 25
E 3
	mp = &top;
E 27
I 27
	MGETHDR(m, M_DONTWAIT, MT_DATA);
	if (m == NULL)
		return (NULL);
E 27
I 25

E 25
D 27
	while (len > 0) {
D 20
		MGET(m, M_DONTWAIT, MT_DATA);
E 20
I 20
D 22
		if (top == NULL)
E 22
I 22
		if (top == NULL) {
E 22
			MGETHDR(m, M_DONTWAIT, MT_DATA);
D 22
		else
E 22
I 22
		} else {
E 22
			MGET(m, M_DONTWAIT, MT_DATA);
I 22
		}
E 22
E 20
D 25
		if ((*mp = m) == NULL) {
E 25
I 25
		if (m == NULL) {
E 25
			m_freem(top);
E 27
I 27
	/*
D 28
	 * If we have more than MLEN bytes, it's cheaper to
E 28
I 28
	 * If we have more than MHLEN bytes, it's cheaper to
E 28
	 * queue the cluster we just filled & allocate a new one
	 * for the input buffer.  Otherwise, fill the mbuf we
	 * allocated above.  Note that code in the input routine
	 * guarantees that packet will fit in a cluster.
	 */
D 28
	cp = sc->sc_buf;
E 28
	if (len >= MHLEN) {
		MCLGET(m, M_DONTWAIT);
		if ((m->m_flags & M_EXT) == 0) {
D 28
			/* we couldn't get a cluster - if memory's this
			 * low, it's time to start dropping packets. */
			m_freem(m);
E 28
I 28
			/*
			 * we couldn't get a cluster - if memory's this
			 * low, it's time to start dropping packets.
			 */
			(void) m_free(m);
E 28
E 27
			return (NULL);
		}
D 3
		if (ifp) {
E 3
I 3
D 20
		if (ifp)
E 3
			m->m_off += sizeof(ifp);
E 20
I 20
D 27
		if (top == NULL) {
			m->m_pkthdr.rcvif = ifp;
			m->m_pkthdr.len = len;
D 22
			m->m_len = MPLEN;
E 22
I 22
			m->m_len = MHLEN;
E 22
		} else
			m->m_len = MLEN;
I 25
		*mp = m;
E 25
E 20
D 3
			count = MIN(len, MLEN - sizeof(ifp));
		} else {
			if (len >= NBPG) {
				struct mbuf *p;

				MCLGET(p, 1);
				if (p != NULL) {
					count = MIN(len, CLBYTES);
					m->m_off = (int)p - (int)m;
E 3
I 3
		/*
D 20
		 * If we have at least NBPG bytes,
		 * allocate a new page.  Swap the current buffer page
		 * with the new one.  We depend on having a space
		 * left at the beginning of the buffer
		 * for the interface pointer.
E 20
I 20
		 * If we have at least MINCLSIZE bytes,
		 * allocate a new page.  Swap the current
		 * buffer page with the new one.
E 20
		 */
D 20
		if (len >= NBPG) {
			MCLGET(m);
D 17
			if (m->m_len == CLBYTES) {
E 17
I 17
			if (m->m_len == MCLBYTES) {
E 20
I 20
		if (len >= MINCLSIZE) {
			MCLGET(m, M_DONTWAIT);
			if (m->m_flags & M_EXT) {
E 20
E 17
				cp = mtod(m, char *);
D 20
				m->m_off = (int)sc->sc_buf - (int)m;
E 20
I 20
				m->m_data = sc->sc_buf;
E 20
D 6
				sc->sc_buf = mtod(m, char *);
E 6
I 6
				sc->sc_buf = cp;
E 6
D 20
				if (ifp) {
					m->m_off += sizeof(ifp);
					count = MIN(len,
D 17
					    CLBYTES - sizeof(struct ifnet *));
E 17
I 17
					    MCLBYTES - sizeof(struct ifnet *));
E 17
E 3
				} else
D 3
					count = MIN(len, MLEN);
			} else
				count = MIN(len, MLEN);
E 3
I 3
D 17
					count = MIN(len, CLBYTES);
E 17
I 17
					count = MIN(len, MCLBYTES);
E 20
I 20
				count = MIN(len, MCLBYTES);
E 20
E 17
				goto nocopy;
			}
E 3
		}
D 3
		bcopy(addr, mtod(m, caddr_t), count);
E 3
I 3
D 20
		if (ifp)
			count = MIN(len, MLEN - sizeof(ifp));
		else
			count = MIN(len, MLEN);
E 20
I 20
		count = MIN(len, m->m_len);
E 20
		bcopy(cp, mtod(m, caddr_t), count);
nocopy:
E 3
		m->m_len = count;
D 20
		if (ifp) {
			m->m_off -= sizeof(ifp);
			m->m_len += sizeof(ifp);
			*mtod(m, struct ifnet **) = ifp;
			ifp = NULL;
		}
E 20
D 3
		addr += count;
E 3
I 3
		cp += count;
E 3
		len -= count;
		mp = &m->m_next;
	}
	return (top);
E 27
I 27
D 28
		sc->sc_ep = mtod(m, u_char *) + (BUFOFFSET + SLMTU);
		m->m_data = (caddr_t)cp;
E 28
I 28
		sc->sc_ep = mtod(m, u_char *) + SLBUFSIZE;
		m->m_data = (caddr_t)sc->sc_buf;
		m->m_ext.ext_buf = (caddr_t)((int)sc->sc_buf &~ MCLOFSET);
E 28
	} else
D 28
		bcopy((caddr_t)cp, mtod(m, caddr_t), len);
E 28
I 28
		bcopy((caddr_t)sc->sc_buf, mtod(m, caddr_t), len);
E 28

	m->m_len = len;
	m->m_pkthdr.len = len;
	m->m_pkthdr.rcvif = &sc->sc_if;
	return (m);
E 27
}

/*
 * tty interface receiver interrupt.
 */
I 43
void
E 43
slinput(c, tp)
	register int c;
	register struct tty *tp;
{
	register struct sl_softc *sc;
	register struct mbuf *m;
I 27
	register int len;
E 27
	int s;
I 47
#if NBPFILTER > 0
	u_char chdr[CHDR_LEN];
#endif
E 47

I 3
	tk_nin++;
E 3
	sc = (struct sl_softc *)tp->t_sc;
	if (sc == NULL)
		return;
I 26
D 27
	if (!(tp->t_state&TS_CARR_ON))	/*XXX*/
E 27
I 27
D 47
	if (!(tp->t_state&TS_CARR_ON))	/* XXX */
E 47
I 47
D 51
	if (c & TTY_ERRORMASK || ((tp->t_state & TS_CARR_ON) == 0 &&
E 51
I 51
	if ((c & TTY_ERRORMASK) || ((tp->t_state & TS_CARR_ON) == 0 &&
E 51
	    (tp->t_cflag & CLOCAL) == 0)) {
		sc->sc_flags |= SC_ERROR;
E 47
E 27
		return;
I 47
	}
	c &= TTY_CHARMASK;
E 47
E 26

D 27
	c &= 0xff;
E 27
I 27
D 35
	++sc->sc_bytesrcvd;
E 35
I 29
	++sc->sc_if.if_ibytes;
E 29
D 47
	c &= 0xff;			/* XXX */
E 47
E 27
I 26

D 27
	/* if we see an abort after "idle" time, count it */
	if ((c&0x7f) == ABT_ESC && time.tv_sec >= sc->sc_lasttime + ABT_WAIT) {
		sc->sc_abortcount++;
		/* record when the first abort escape arrived */
		if (sc->sc_abortcount == 1) sc->sc_starttime = time.tv_sec;
E 27
I 27
D 47
#ifdef ABT_ESC
E 47
D 34
	if (sc->sc_flags & SC_ABORT) {
E 34
I 34
D 35
	{
E 34
		/* if we see an abort after "idle" time, count it */
		if (c == ABT_ESC && time.tv_sec >= sc->sc_lasttime + ABT_WAIT) {
			sc->sc_abortcount++;
			/* record when the first abort escape arrived */
			if (sc->sc_abortcount == 1)
				sc->sc_starttime = time.tv_sec;
		}
		/*
		 * if we have an abort, see that we have not run out of time,
		 * or that we have an "idle" time after the complete escape
		 * sequence
		 */
		if (sc->sc_abortcount) {
			if (time.tv_sec >= sc->sc_starttime + ABT_RECYCLE)
E 35
I 35
	if (sc->sc_if.if_flags & IFF_DEBUG) {
		if (c == ABT_ESC) {
			/*
			 * If we have a previous abort, see whether
			 * this one is within the time limit.
			 */
			if (sc->sc_abortcount &&
			    time.tv_sec >= sc->sc_starttime + ABT_WINDOW)
E 35
				sc->sc_abortcount = 0;
D 35
			if (sc->sc_abortcount >= ABT_SOFT &&
			    time.tv_sec >= sc->sc_lasttime + ABT_WAIT) {
				slclose(tp);
				return;
E 35
I 35
			/*
			 * If we see an abort after "idle" time, count it;
			 * record when the first abort escape arrived.
			 */
			if (time.tv_sec >= sc->sc_lasttime + ABT_IDLE) {
				if (++sc->sc_abortcount == 1)
					sc->sc_starttime = time.tv_sec;
				if (sc->sc_abortcount >= ABT_COUNT) {
					slclose(tp);
					return;
				}
E 35
			}
D 35
		}
E 35
I 35
		} else
			sc->sc_abortcount = 0;
E 35
		sc->sc_lasttime = time.tv_sec;
E 27
	}
I 27
D 47
#endif
E 47
E 27

D 27
	/* if we have an abort, see that we have not run out of time, or
	   that we have an "idle" time after the complete escape sequence */
	if (sc->sc_abortcount) {
		if (time.tv_sec >= sc->sc_starttime + ABT_RECYCLE)
			sc->sc_abortcount = 0;
		if (sc->sc_abortcount >= ABT_SOFT
		&& time.tv_sec >= sc->sc_lasttime + ABT_WAIT)
			sc->sc_flags |= SC_ABORT;
	}
E 27
I 27
	switch (c) {
E 27

D 27
	if (sc->sc_ilen && time.tv_sec >= sc->sc_lasttime + TIME_WINDOW) {
		sc->sc_flags &= ~SC_ESCAPED;
		sc->sc_mp = sc->sc_buf;
		sc->sc_ilen = 0;
		sc->sc_if.if_ierrors++;
		return;
	}

	sc->sc_lasttime = time.tv_sec;

E 26
	if (sc->sc_flags & SC_ESCAPED) {
		sc->sc_flags &= ~SC_ESCAPED;
		switch (c) {

		case TRANS_FRAME_ESCAPE:
E 27
I 27
	case TRANS_FRAME_ESCAPE:
		if (sc->sc_escape)
E 27
			c = FRAME_ESCAPE;
D 27
			break;
E 27
I 27
		break;
E 27

D 27
		case TRANS_FRAME_END:
E 27
I 27
	case TRANS_FRAME_END:
		if (sc->sc_escape)
E 27
			c = FRAME_END;
D 27
			break;
E 27
I 27
		break;
E 27

D 27
		default:
			sc->sc_if.if_ierrors++;
D 3
			sc->sc_mp = sc->sc_buf;
E 3
I 3
D 25
			sc->sc_mp = sc->sc_buf + sizeof(struct ifnet *);
E 25
I 25
			sc->sc_mp = sc->sc_buf;
E 25
E 3
			sc->sc_ilen = 0;
			return;
		}
	} else {
		switch (c) {
E 27
I 27
	case FRAME_ESCAPE:
		sc->sc_escape = 1;
		return;
E 27

D 27
		case FRAME_END:
			if (sc->sc_ilen == 0)	/* ignore */
				return;
D 3
			m = sl_btom(sc->sc_buf, sc->sc_ilen, &sc->sc_if);
E 3
I 3
			m = sl_btom(sc, sc->sc_ilen, &sc->sc_if);
I 26
			sc->sc_mp = sc->sc_buf;
			sc->sc_ilen = 0;
E 26
E 3
			if (m == NULL) {
				sc->sc_if.if_ierrors++;
				return;
			}
D 3
			sc->sc_mp = sc->sc_buf;
E 3
I 3
D 25
			sc->sc_mp = sc->sc_buf + sizeof(struct ifnet *);
E 25
I 25
D 26
			sc->sc_mp = sc->sc_buf;
E 25
E 3
			sc->sc_ilen = 0;
E 26
			sc->sc_if.if_ipackets++;
I 26
#ifdef INET
			{ u_char type = *mtod(m, u_char *);
			  if (!(m = sl_uncompress_tcp(m, type&0xf0, &sc->sc_comp)))
				return;
			}
#endif
E 26
			s = splimp();
			if (IF_QFULL(&ipintrq)) {
				IF_DROP(&ipintrq);
				sc->sc_if.if_ierrors++;
				m_freem(m);
			} else {
				IF_ENQUEUE(&ipintrq, m);
				schednetisr(NETISR_IP);
			}
			splx(s);
			return;
E 27
I 27
	case FRAME_END:
I 47
		if(sc->sc_flags & SC_ERROR) {
			sc->sc_flags &= ~SC_ERROR;
			goto newpack;
		}
E 47
		len = sc->sc_mp - sc->sc_buf;
		if (len < 3)
			/* less than min length packet - ignore */
			goto newpack;
E 27

I 47
#if NBPFILTER > 0
		if (sc->sc_bpf) {
			/*
			 * Save the compressed header, so we
			 * can tack it on later.  Note that we
			 * will end up copying garbage in some
			 * cases but this is okay.  We remember
			 * where the buffer started so we can
			 * compute the new header length.
			 */
			bcopy(sc->sc_buf, chdr, CHDR_LEN);
		}
#endif

E 47
D 27
		case FRAME_ESCAPE:
			sc->sc_flags |= SC_ESCAPED;
			return;
E 27
I 27
		if ((c = (*sc->sc_buf & 0xf0)) != (IPVERSION << 4)) {
			if (c & 0x80)
				c = TYPE_COMPRESSED_TCP;
			else if (c == TYPE_UNCOMPRESSED_TCP)
				*sc->sc_buf &= 0x4f; /* XXX */
D 30
			len = sl_uncompress_tcp(&sc->sc_buf, len, (u_int)c,
						&sc->sc_comp);
			if (len <= 0)
E 30
I 30
			/*
			 * We've got something that's not an IP packet.
			 * If compression is enabled, try to decompress it.
			 * Otherwise, if `auto-enable' compression is on and
			 * it's a reasonable packet, decompress it and then
			 * enable compression.  Otherwise, drop it.
			 */
D 34
			if (sc->sc_flags & SC_COMPRESS) {
E 34
I 34
			if (sc->sc_if.if_flags & SC_COMPRESS) {
E 34
				len = sl_uncompress_tcp(&sc->sc_buf, len,
							(u_int)c, &sc->sc_comp);
				if (len <= 0)
					goto error;
D 34
			} else if ((sc->sc_flags & SC_AUTOCOMP) &&
E 34
I 34
			} else if ((sc->sc_if.if_flags & SC_AUTOCOMP) &&
E 34
			    c == TYPE_UNCOMPRESSED_TCP && len >= 40) {
				len = sl_uncompress_tcp(&sc->sc_buf, len,
							(u_int)c, &sc->sc_comp);
				if (len <= 0)
					goto error;
D 34
				sc->sc_flags |= SC_COMPRESS;
E 34
I 34
				sc->sc_if.if_flags |= SC_COMPRESS;
E 34
			} else
E 30
				goto error;
E 27
		}
I 47
#if NBPFILTER > 0
		if (sc->sc_bpf) {
			/*
			 * Put the SLIP pseudo-"link header" in place.
			 * We couldn't do this any earlier since
			 * decompression probably moved the buffer
			 * pointer.  Then, invoke BPF.
			 */
			register u_char *hp = sc->sc_buf - SLIP_HDRLEN;

			hp[SLX_DIR] = SLIPDIR_IN;
			bcopy(chdr, &hp[SLX_CHDR], CHDR_LEN);
			bpf_tap(sc->sc_bpf, hp, len + SLIP_HDRLEN);
		}
#endif
E 47
I 27
		m = sl_btom(sc, len);
		if (m == NULL)
			goto error;

		sc->sc_if.if_ipackets++;
I 29
		sc->sc_if.if_lastchange = time;
E 29
		s = splimp();
		if (IF_QFULL(&ipintrq)) {
			IF_DROP(&ipintrq);
			sc->sc_if.if_ierrors++;
I 29
			sc->sc_if.if_iqdrops++;
E 29
			m_freem(m);
		} else {
			IF_ENQUEUE(&ipintrq, m);
			schednetisr(NETISR_IP);
		}
		splx(s);
		goto newpack;
E 27
	}
D 6
	if (++sc->sc_ilen >= SLMTU) {
E 6
I 6
D 7
	if (sc->sc_ilen++ >= SLMTU) {
E 7
I 7
D 27
	if (++sc->sc_ilen > SLMTU) {
E 7
E 6
		sc->sc_if.if_ierrors++;
D 3
		sc->sc_mp = sc->sc_buf;
E 3
I 3
D 25
		sc->sc_mp = sc->sc_buf + sizeof(struct ifnet *);
E 25
I 25
		sc->sc_mp = sc->sc_buf;
E 25
E 3
		sc->sc_ilen = 0;
E 27
I 27
	if (sc->sc_mp < sc->sc_ep) {
		*sc->sc_mp++ = c;
		sc->sc_escape = 0;
E 27
		return;
	}
I 47

	/* can't put lower; would miss an extra frame */
	sc->sc_flags |= SC_ERROR;

E 47
D 27
	*sc->sc_mp++ = c;
E 27
I 27
error:
	sc->sc_if.if_ierrors++;
newpack:
D 30
	sc->sc_mp = sc->sc_buf = sc->sc_ep - SLMTU;
E 30
I 30
	sc->sc_mp = sc->sc_buf = sc->sc_ep - SLMAX;
E 30
	sc->sc_escape = 0;
E 27
}

/*
 * Process an ioctl request.
 */
I 43
int
E 43
slioctl(ifp, cmd, data)
	register struct ifnet *ifp;
D 52
	int cmd;
E 52
I 52
	u_long cmd;
E 52
	caddr_t data;
{
	register struct ifaddr *ifa = (struct ifaddr *)data;
D 40
	int s = splimp(), error = 0;
E 40
I 40
D 42
#ifdef MULTICAST
E 42
	register struct ifreq *ifr;
D 42
#endif
E 42
	register int s = splimp(), error = 0;
E 40

	switch (cmd) {

	case SIOCSIFADDR:
D 22
		if (ifa->ifa_addr.sa_family == AF_INET)
E 22
I 22
		if (ifa->ifa_addr->sa_family == AF_INET)
E 22
			ifp->if_flags |= IFF_UP;
		else
			error = EAFNOSUPPORT;
		break;

	case SIOCSIFDSTADDR:
D 22
		if (ifa->ifa_addr.sa_family != AF_INET)
E 22
I 22
		if (ifa->ifa_addr->sa_family != AF_INET)
E 22
			error = EAFNOSUPPORT;
		break;
I 40

D 42
#ifdef MULTICAST
E 42
	case SIOCADDMULTI:
	case SIOCDELMULTI:
		ifr = (struct ifreq *)data;
		if (ifr == 0) {
			error = EAFNOSUPPORT;		/* XXX */
			break;
		}
		switch (ifr->ifr_addr.sa_family) {

#ifdef INET
		case AF_INET:
			break;
#endif

		default:
			error = EAFNOSUPPORT;
			break;
		}
		break;
D 47
#endif
E 47
E 40

	default:
		error = EINVAL;
	}
	splx(s);
	return (error);
}
I 47
#endif
E 47
D 42
#endif
E 42
E 1
