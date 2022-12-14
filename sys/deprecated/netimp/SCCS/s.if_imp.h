h25305
s 00001/00011/00221
d D 7.7 90/06/28 21:34:04 bostic 15 14
c new copyright notice
e
s 00007/00000/00225
d D 7.6 90/06/28 17:31:07 karels 14 13
c move link numbers from <netinet/in.h>
e
s 00011/00006/00214
d D 7.5 88/06/29 16:58:07 bostic 13 12
c install approved copyright notice
e
s 00004/00002/00216
d D 7.4 88/05/06 12:33:02 karels 12 11
c clean up queuing, keep message counts correctly, check for 1822L NOPs, etc
e
s 00021/00006/00197
d D 7.3 88/02/08 10:30:10 karels 11 10
c new copyrights; new IMP interface with H/W, using cb_output rather
c than cb_start (so can start RFNM timer when packet goes out, and output is
c round-robin by destination)
e
s 00066/00023/00137
d D 7.2 88/02/03 17:26:44 karels 10 9
c working with new up/down FSM, dropcount, statistics and host entry
e
s 00001/00001/00159
d D 7.1 86/06/04 23:56:02 mckusick 9 8
c 4.3BSD release version
e
s 00007/00001/00153
d D 6.2 85/06/08 12:32:08 mckusick 8 7
c Add copyright
e
s 00000/00000/00154
d D 6.1 83/07/29 07:15:29 sam 7 6
c 4.2 distribution
e
s 00002/00002/00152
d D 4.6 82/03/19 17:08:30 root 6 5
c IMPMTU fixup
e
s 00001/00009/00153
d D 4.5 82/03/16 13:53:54 root 5 4
c fixes to imp
e
s 00006/00006/00156
d D 4.4 82/02/21 12:14:32 sam 4 3
c cosmetics
e
s 00040/00016/00122
d D 4.3 82/02/12 15:17:32 wnj 3 2
c closer to a working imp driver
e
s 00001/00001/00137
d D 4.2 82/02/03 11:22:25 sam 2 1
c dropcnt -> 2
e
s 00138/00000/00000
d D 4.1 82/02/03 11:21:46 sam 1 0
c date and time created 82/02/03 11:21:46 by sam
e
u
U
t
T
I 1
D 8
/*	%M%	%I%	%E%	*/
E 8
I 8
/*
D 9
 * Copyright (c) 1982 Regents of the University of California.
E 9
I 9
D 11
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 9
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 11
I 11
D 13
 * Copyright (c) 1982,1986,1988 Regents of the University of California.
E 13
I 13
 * Copyright (c) 1982, 1986, 1988 Regents of the University of California.
E 13
 * All rights reserved.
E 11
 *
I 11
D 15
 * Redistribution and use in source and binary forms are permitted
D 13
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 13
I 13
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 13
 *
E 11
 *	%W% (Berkeley) %G%
 */
E 8

/*
 * Structure of IMP 1822 long leader.
 */
D 3
struct imp_leader {
	u_char	il_format;	/* leader format */
	u_char	il_network;	/* src/dest network */
	u_char	il_flags;	/* leader flags */
	u_char	il_mtype;	/* message type */
	u_char	il_htype;	/* handling type */
	u_char	il_host;	/* host number */
E 3
I 3
struct control_leader {
D 10
	u_char	dl_format;	/* leader format */
	u_char	dl_network;	/* src/dest network */
	u_char	dl_flags;	/* leader flags */
	u_char	dl_mtype;	/* message type */
	u_char	dl_htype;	/* handling type */
	u_char	dl_host;	/* host number */
E 3
D 5
	union {
D 3
		u_short	il_short;
		u_char	il_char[2];
	} ilun;
#define il_imp		ilun.il_short	/* imp field */
#define il_impno	ilun.il_char[1]	/* imp number */
#define il_lh		ilun.il_char[0]	/* logical host */
	u_char	il_link;	/* link number */
	u_char	il_subtype;	/* message subtype */
E 3
I 3
		u_short	dl_short;
		u_char	dl_char[2];
	} dlun;
D 4
#define dl_imp		dlun.dl_short	/* imp field */
#define dl_impno	dlun.dl_char[1]	/* imp number */
#define dl_lh		dlun.dl_char[0]	/* logical host */
E 4
I 4
#define	dl_imp		dlun.dl_short	/* imp field */
#define	dl_impno	dlun.dl_char[1]	/* imp number */
#define	dl_lh		dlun.dl_char[0]	/* logical host */
E 5
I 5
	u_short	dl_imp;		/* imp field */
E 5
E 4
	u_char	dl_link;	/* link number */
	u_char	dl_subtype;	/* message subtype */
E 10
I 10
	u_char	dl_format;	/* 1-8   leader format */
	u_char	dl_network;	/* 9-16  src/dest network */
	u_char	dl_flags;	/* 17-24 leader flags */
	u_char	dl_mtype;	/* 25-32 message type */
	u_char	dl_htype;	/* 33-40 handling type */
	u_char	dl_host;	/* 41-48 host number */
	u_short	dl_imp;		/* 49-64 imp field */
	u_char	dl_link;	/* 65-72 link number */
	u_char	dl_subtype;	/* 73-80 message subtype */
E 10
};

struct imp_leader {
	struct	control_leader il_dl;
#define	il_format	il_dl.dl_format
#define	il_network	il_dl.dl_network
#define	il_flags	il_dl.dl_flags
#define	il_mtype	il_dl.dl_mtype
#define	il_htype	il_dl.dl_htype
#define	il_host		il_dl.dl_host
#define	il_imp		il_dl.dl_imp
D 5
#define	il_impno	il_dl.dl_impno
#define	il_lh		il_dl.dl_lh
E 5
#define	il_link		il_dl.dl_link
#define	il_subtype	il_dl.dl_subtype
E 3
	u_short	il_length;	/* message length */
};

I 11
#define	IMP_MAXHOSTMSG	8	/* max messages in flight to a host */
E 11
D 2
#define	IMP_DROPCNT	3	/* # of noops from imp to ignore */
E 2
I 2
D 10
#define	IMP_DROPCNT	2	/* # of noops from imp to ignore */
E 10
I 10
#define	IMP_NOOPCNT	3	/* # of noops to send imp on reset */
E 10
E 2
D 3
#define	IMP_MTU		1019	/* max message size (bytes) */
E 3
I 3
D 6
/* don't use 1019 here, 'cuz odd numbers and word counts are confusing */
#define	IMP_MTU		(sizeof (struct imp_leader) + 1018) 
E 6
I 6
/* insure things are even... */
#define	IMPMTU		((8159 / NBBY) & ~01)
I 10
#define	IMP_RCVBUF	((8159 / NBBY + 2) & ~01)
E 10
E 6
E 3

/*
 * IMP-host flags
 */
I 12
#define	IMP_1822L_H2I	0xd	/* 1822L host-to-imp, 96-bit format */
#define	IMP_1822L_I2H	0xe	/* 1822L imp-to-host, 96-bit format */
E 12
#define	IMP_NFF		0xf	/* 96-bit (new) format */
#define	IMP_TRACE	0x8	/* trace message route */

D 4
#define IMP_DMASK	0x3	/* host going down mask */
E 4
I 4
D 10
#define	IMP_DMASK	0x3	/* host going down mask */
E 4

E 10
/*
 * IMP-host message types.
 */
#define	IMPTYPE_DATA		0	/* data for protocol */
#define	IMPTYPE_BADLEADER	1	/* leader error */
#define	IMPTYPE_DOWN		2	/* imp going down */
#define	IMPTYPE_NOOP		4	/* noop seen during initialization */
#define	IMPTYPE_RFNM		5	/* request for new messages */
#define	IMPTYPE_HOSTDEAD	6	/* host doesn't respond */
#define	IMPTYPE_HOSTUNREACH	7	/* host unreachable */
#define	IMPTYPE_BADDATA		8	/* data error */
#define	IMPTYPE_INCOMPLETE	9	/* incomplete message, send rest */
#define	IMPTYPE_RESET		10	/* reset complete */
/* non-blocking IMP interface */
#define	IMPTYPE_RETRY		11	/* IMP refused, try again */
#define	IMPTYPE_NOTIFY		12	/* IMP refused, will notify */
#define	IMPTYPE_TRYING		13	/* IMP refused, still rexmt'ng */
#define	IMPTYPE_READY		14	/* ready for next message */

/*
I 14
 * Link numbers
 */
#define	IMPLINK_IP		155
#define	IMPLINK_LOWEXPER	156
#define	IMPLINK_HIGHEXPER	158

/*
E 14
D 10
 * IMPTYPE_DOWN subtypes.
E 10
I 10
 * IMPTYPE_DOWN subtypes, in link number field.
E 10
 */
I 10
#define	IMP_DMASK		0x3	/* host going down mask */
E 10
#define	IMPDOWN_GOING		0	/* 30 secs */
#define	IMPDOWN_PM		1	/* hardware PM */
#define	IMPDOWN_RELOAD		2	/* software reload */
#define	IMPDOWN_RESTART		3	/* emergency restart */
I 10
#define	IMPDOWN_WHENMASK	0x3c	/* mask for "how soon" */
#define	IMPDOWN_WHENSHIFT	2	/* shift for "how soon" */
#define	IMPDOWN_WHENUNIT	5	/* unit for "how soon", 5 min. */
E 10

I 10
#define	IMPTV_DOWN	30		/* going down timer 30 secs */

#ifdef IMPMESSAGES
E 10
/*
I 10
 * Messages from IMP regarding why
 * it's going down.
 */
char *impmessage[] = {
	"in 30 seconds",
	"for hardware PM",
	"to reload software",
	"for emergency reset"
};
#endif

/*
E 10
 * IMPTYPE_BADLEADER subtypes.
 */
#define	IMPLEADER_ERR		0	/* error flip-flop set */
#define	IMPLEADER_SHORT		1	/* leader < 80 bits */
#define	IMPLEADER_TYPE		2	/* illegal type field */
#define	IMPLEADER_OPPOSITE	3	/* opposite leader type */

/*
 * IMPTYPE_HOSTDEAD subtypes.
 */
#define	IMPHOST_NORDY		1	/* ready-line negated */
#define	IMPHOST_TARDY		2	/* tardy receiving mesgs */
#define	IMPHOST_NOEXIST		3	/* NCC doesn't know host */
#define	IMPHOST_IMPSOFT		4	/* IMP software won't allow mesgs */
#define	IMPHOST_PM		5	/* host down for scheduled PM */
#define	IMPHOST_HARDSCHED	6	/* " " " " hardware work */
#define	IMPHOST_SOFTSCHED	7	/* " " " " software work */
#define	IMPHOST_RESTART		8	/* host down for emergency restart */
#define	IMPHOST_POWER		9	/* down because of power outage */
#define	IMPHOST_BREAKPOINT	10	/* host stopped at a breakpoint */
#define	IMPHOST_HARDWARE	11	/* hardware failure */
#define	IMPHOST_NOTUP		12	/* host not scheduled to be up */
/* 13-14 currently unused */
#define	IMPHOST_COMINGUP	15	/* host in process of coming up */

/*
 * IMPTYPE_HOSTUNREACH subtypes.
 */
#define	IMPREACH_IMP		0	/* destination IMP can't be reached */
#define	IMPREACH_HOSTUP		1	/* destination host isn't up */
#define	IMPREACH_LEADER		2	/* host doesn't support long leader */
#define	IMPREACH_PROHIBITED	3	/* communication is prohibited */

/*
 * IMPTYPE_INCOMPLETE subtypes.
 */
#define	IMPCOMPLETE_SLOW	0	/* host didn't take data fast enough */
#define	IMPCOMPLETE_TOOLONG	1	/* message was too long */
#define	IMPCOMPLETE_TIMEOUT	2	/* mesg transmission time > 15 sec. */
#define	IMPCOMPLETE_FAILURE	3	/* IMP/circuit failure */
#define	IMPCOMPLETE_NOSPACE	4	/* no resources within 15 sec. */
#define	IMPCOMPLETE_IMPIO	5	/* src IMP I/O failure during receipt */

/*
 * IMPTYPE_RETRY subtypes.
 */
#define	IMPRETRY_BUFFER		0	/* IMP buffer wasn't available */
#define	IMPRETRY_BLOCK		1	/* connection block unavailable */

I 10
D 11
#define	RFNMTIMER	(120*PR_SLOWHZ)	/* time to wait for RFNM for msg. */
E 11
I 11
D 12
#define	RFNMTIMER	(120*PR_SLOWHZ)	  /* time to wait for RFNM for msg. */
#define	IMP_OTIMER	(10*IFNET_SLOWHZ) /* max output time unless blocked */
E 12
I 12
#define	RFNMTIMER	(120*PR_SLOWHZ)	 /* time to wait for RFNM for msg. */
#define	IMP_OTIMER	(5*IFNET_SLOWHZ) /* max output time unless blocked */
E 12

E 11
E 10
/*
 * Data structure shared between IMP protocol module and hardware
 * interface driver.  Used to allow layering of IMP routines on top
D 10
 * of varying device drivers.  NOTE: there's a possible problem 
 * with ambiguity in the ``unit'' definition which is implicitly
 * shared by the both IMP and device code.  If we have two IMPs,
 * with each on top of a device of the same unit, things won't work.
 * The assumption is if you've got multiple IMPs, then they all run
 * on top of the same type of device, or they must have different units.
E 10
I 10
 * of varying device drivers.
E 10
 */
D 4
struct	impcb {
E 4
I 4
struct impcb {
I 10
	int	ic_hwunit;		/* H/W unit number */
	char	*ic_hwname;		/* H/W type name */
E 10
E 4
	char	ic_oactive;		/* output in progress */
	int	(*ic_init)();		/* hardware init routine */
D 11
	int	(*ic_start)();		/* hardware start output routine */
I 10
	int	(*ic_stop)();		/* hardware "drop ready" routine */
E 11
I 11
	int	(*ic_output)();		/* hardware output routine */
	int	(*ic_down)();		/* hardware "drop ready" routine */
E 11
E 10
};

/*
I 10
 * IMP software status per interface.
 * (partially shared with the hardware specific module)
 *
 * Each interface is referenced by a network interface structure,
 * imp_if, which the routing code uses to locate the interface.
 * This structure contains the output queue for the interface, its
 * address, ...  IMP specific structures used in connecting the
 * IMP software modules to the hardware specific interface routines
 * are stored here.  The common structures are made visible to the
 * interface driver by passing a pointer to the hardware routine
 * at "attach" time.
 */
struct imp_softc {
	struct	ifnet imp_if;		/* network visible interface */
	struct	impcb imp_cb;		/* hooks to hardware module */
	int	imp_state;		/* current state of IMP */
	int	imp_dropcnt;		/* used during initialization */
I 11
	struct	mbuf *imp_hosts;	/* Head of host table hash chains. */
	struct	mbuf *imp_hostq;	/* current round-robin-output mark */
	u_int	imp_hostent;		/* current round-robin-output mark */
	int	imp_msgready;		/* number of messages ready to send */
	u_long	imp_block;		/* times imp blocked output */
E 11
	u_long	imp_lostrfnm;		/* rfnm's timed out */
	u_long	imp_badrfnm;		/* rfnm/incompl after timeout/bogus */
	u_long	imp_incomplete;		/* incomplete's received */
	u_long	imp_garbage;		/* bad messages received */
};
I 11

E 11
struct	imp_softc *impattach();

/*
E 10
 * State of an IMP.
 */
D 10
#define	IMPS_DOWN	0		/* unavailable, don't use */
#define	IMPS_GOINGDOWN	1		/* been told we go down soon */
E 10
I 10
#define	IMPS_DOWN	0		/* unavailable, host not ready */
#define	IMPS_WINIT	1		/* imp not ready, waiting for init */
E 10
#define	IMPS_INIT	2		/* coming up */
#define	IMPS_UP		3		/* ready to go */
D 10
#define	IMPS_RESET	4		/* reset in progress */
E 10
I 10
#define	IMPS_GOINGDOWN	4		/* been told we go down soon */
E 10

D 10
#define	IMPTV_DOWN	(30*60)		/* going down timer 30 secs */
E 10
I 10
#define	IMPS_RUNNING(s)	((s) >= IMPS_UP)	/* ready for messages */
#define	IMPS_IMPREADY(s) ((s) >= IMPS_INIT)	/* IMP ready line on */
E 10
I 3

#ifdef IMPLEADERS
D 4
char * impleaders[IMPTYPE_READY+1] = {
E 4
I 4
char *impleaders[IMPTYPE_READY+1] = {
E 4
	"DATA", "BADLEADER", "DOWN", "bad", "NOOP", "RFNM", "HOSTDEAD",
	"HOSTUNREACH", "BADDATA", "INCOMPLETE", "RESET", "RETRY",
	"NOTIFY", "TRYING", "READY"
};
#endif
E 3
E 1
