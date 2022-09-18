h63656
s 00002/00002/00163
d D 8.1 93/06/06 16:41:40 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00013/00162
d D 4.5 91/04/26 15:47:24 bostic 8 7
c new copyright; att/bsd/shared
e
s 00001/00001/00174
d D 4.4 89/09/01 15:54:17 borman 7 6
c move NTELOPTS out of #ifdef TELOPTS
e
s 00073/00001/00102
d D 4.3 89/08/21 16:11:47 borman 6 5
c Add support for LINEMODE option
e
s 00012/00002/00091
d D 4.2 89/03/20 20:44:49 minshall 5 4
c Newer telnet.h
e
s 00000/00000/00093
d D 4.1 88/12/04 15:12:40 minshall 4 3
c Release 4.1
e
s 00010/00005/00083
d D 1.3 88/06/29 20:10:11 bostic 3 2
c install approved copyright notice
e
s 00009/00003/00079
d D 1.2 88/03/28 12:57:07 bostic 2 1
c add Berkeley specific headers
e
s 00082/00000/00000
d D 1.1 87/06/18 10:56:08 minshall 1 0
c date and time created 87/06/18 10:56:08 by minshall
e
u
U
t
T
I 1
D 8
/*
 * Copyright (c) 1983 Regents of the University of California.
E 8
I 8
/*-
D 9
 * Copyright (c) 1983 The Regents of the University of California.
E 8
D 2
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
E 2
 *
D 2
 *	@(#)telnet.h	5.1 (Berkeley) 5/30/85
E 2
I 2
D 8
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 3
 *
 *	%W% (Berkeley) %G%
E 2
 */

/*
 * Definitions for the TELNET protocol.
 */
#define	IAC	255		/* interpret as command: */
#define	DONT	254		/* you are not to use option */
#define	DO	253		/* please, you use option */
#define	WONT	252		/* I won't use option */
#define	WILL	251		/* I will use option */
#define	SB	250		/* interpret as subnegotiation */
#define	GA	249		/* you may reverse the line */
#define	EL	248		/* erase the current line */
#define	EC	247		/* erase the current character */
#define	AYT	246		/* are you there */
#define	AO	245		/* abort output--but let prog finish */
#define	IP	244		/* interrupt process--permanently */
#define	BREAK	243		/* break */
#define	DM	242		/* data mark--for connect. cleaning */
#define	NOP	241		/* nop */
#define	SE	240		/* end sub negotiation */
#define EOR     239             /* end of record (transparent mode) */
I 6
#define	ABORT	238		/* Abort process */
#define	SUSP	237		/* Suspend process */
#define	xEOF	236		/* End of file: EOF is already used... */
E 6

#define SYNCH	242		/* for telfunc calls */

#ifdef TELCMDS
char *telcmds[] = {
I 6
	"EOF", "SUSP", "ABORT", "EOR",
E 6
	"SE", "NOP", "DMARK", "BRK", "IP", "AO", "AYT", "EC",
	"EL", "GA", "SB", "WILL", "WONT", "DO", "DONT", "IAC",
};
I 6
#define	TELCMD_FIRST	xEOF
#define	TELCMD_LAST	IAC
#define	TELCMD_OK(x)	((x) <= TELCMD_LAST && (x) >= TELCMD_FIRST)
#define	TELCMD(x)	telcmds[(x)-TELCMD_FIRST]
E 6
#endif

/* telnet options */
#define TELOPT_BINARY	0	/* 8-bit data path */
#define TELOPT_ECHO	1	/* echo */
#define	TELOPT_RCP	2	/* prepare to reconnect */
#define	TELOPT_SGA	3	/* suppress go ahead */
#define	TELOPT_NAMS	4	/* approximate message size */
#define	TELOPT_STATUS	5	/* give status */
#define	TELOPT_TM	6	/* timing mark */
#define	TELOPT_RCTE	7	/* remote controlled transmission and echo */
#define TELOPT_NAOL 	8	/* negotiate about output line width */
#define TELOPT_NAOP 	9	/* negotiate about output page size */
#define TELOPT_NAOCRD	10	/* negotiate about CR disposition */
#define TELOPT_NAOHTS	11	/* negotiate about horizontal tabstops */
#define TELOPT_NAOHTD	12	/* negotiate about horizontal tab disposition */
#define TELOPT_NAOFFD	13	/* negotiate about formfeed disposition */
#define TELOPT_NAOVTS	14	/* negotiate about vertical tab stops */
#define TELOPT_NAOVTD	15	/* negotiate about vertical tab disposition */
#define TELOPT_NAOLFD	16	/* negotiate about output LF disposition */
#define TELOPT_XASCII	17	/* extended ascic character set */
#define	TELOPT_LOGOUT	18	/* force logout */
#define	TELOPT_BM	19	/* byte macro */
#define	TELOPT_DET	20	/* data entry terminal */
#define	TELOPT_SUPDUP	21	/* supdup protocol */
#define	TELOPT_SUPDUPOUTPUT 22	/* supdup output */
#define	TELOPT_SNDLOC	23	/* send location */
#define	TELOPT_TTYPE	24	/* terminal type */
#define	TELOPT_EOR	25	/* end or record */
D 5
#define TELOPT_EXOPL	255	/* extended-options-list */
E 5
I 5
#define	TELOPT_TUID	26	/* TACACS user identification */
#define	TELOPT_OUTMRK	27	/* output marking */
#define	TELOPT_TTYLOC	28	/* terminal location number */
#define	TELOPT_3270REGIME 29	/* 3270 regime */
#define	TELOPT_X3PAD	30	/* X.3 PAD */
#define	TELOPT_NAWS	31	/* window size */
#define	TELOPT_TSPEED	32	/* terminal speed */
#define	TELOPT_LFLOW	33	/* remote flow control */
I 6
#define TELOPT_LINEMODE	34	/* Linemode option */
E 6
#define	TELOPT_EXOPL	255	/* extended-options-list */
E 5

D 7
#ifdef TELOPTS
E 7
D 5
#define	NTELOPTS	(1+TELOPT_EOR)
E 5
I 5
D 6
#define	NTELOPTS	(1+TELOPT_LFLOW)
E 6
I 6
#define	NTELOPTS	(1+TELOPT_LINEMODE)
I 7
#ifdef TELOPTS
E 7
E 6
E 5
char *telopts[NTELOPTS] = {
	"BINARY", "ECHO", "RCP", "SUPPRESS GO AHEAD", "NAME",
	"STATUS", "TIMING MARK", "RCTE", "NAOL", "NAOP",
	"NAOCRD", "NAOHTS", "NAOHTD", "NAOFFD", "NAOVTS",
	"NAOVTD", "NAOLFD", "EXTEND ASCII", "LOGOUT", "BYTE MACRO",
	"DATA ENTRY TERMINAL", "SUPDUP", "SUPDUP OUTPUT",
	"SEND LOCATION", "TERMINAL TYPE", "END OF RECORD",
I 5
	"TACACS UID", "OUTPUT MARKING", "TTYLOC",
	"3270 REGIME", "X.3 PAD", "NAWS", "TSPEED", "LFLOW",
I 6
	"LINEMODE",
E 6
E 5
};
I 6
#define	TELOPT_FIRST	TELOPT_BINARY
#define	TELOPT_LAST	TELOPT_LINEMODE
#define	TELOPT_OK(x)	((x) <= TELOPT_LAST && (x) >= TELOPT_FIRST)
#define	TELOPT(x)	telopts[(x)-TELOPT_FIRST]
E 6
#endif

/* sub-option qualifiers */
#define	TELQUAL_IS	0	/* option is... */
#define	TELQUAL_SEND	1	/* send option */
I 6

/*
 * LINEMODE suboptions
 */

#define	LM_MODE		1
#define	LM_FORWARDMASK	2
#define	LM_SLC		3

#define	MODE_EDIT	0x01
#define	MODE_TRAPSIG	0x02
#define	MODE_ACK	0x04

#define	MODE_MASK	(MODE_EDIT|MODE_TRAPSIG|MODE_ACK)

/* Not part of protocol, but needed to simplify things... */
#define MODE_FLOW		0x40
#define MODE_ECHO		0x80
#define MODE_FORCE		0x20

#define	SLC_SYNCH	1
#define	SLC_BRK		2
#define	SLC_IP		3
#define	SLC_AO		4
#define	SLC_AYT		5
#define	SLC_EOR		6
#define	SLC_ABORT	7
#define	SLC_EOF		8
#define	SLC_SUSP	9
#define	SLC_EC		10
#define	SLC_EL		11
#define	SLC_EW		12
#define	SLC_RP		13
#define	SLC_LNEXT	14
#define	SLC_XON		15
#define	SLC_XOFF	16
#define	SLC_FORW1	17
#define	SLC_FORW2	18

#define	NSLC		18

#define	SLC_NAMES	"0", "SYNCH", "BRK", "IP", "AO", "AYT", "EOR", \
			"ABORT", "EOF", "SUSP", "EC", "EL", "EW", "RP", \
			"LNEXT", "XON", "XOFF", "FORW1", "FORW2"

#define	SLC_NOSUPPORT	0
#define	SLC_CANTCHANGE	1
#define	SLC_VARIABLE	2
#define	SLC_DEFAULT	3
#define	SLC_LEVELBITS	0x03

#define	SLC_FUNC	0
#define	SLC_FLAGS	1
#define	SLC_VALUE	2

#define	SLC_ACK		0x80
#define	SLC_FLUSHIN	0x40
#define	SLC_FLUSHOUT	0x20
E 6
E 1
