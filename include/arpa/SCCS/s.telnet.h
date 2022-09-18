h24705
s 00010/00007/00284
d D 8.2 93/12/15 11:28:03 dab 26 25
c Add support for the new ENVIRON opton
e
s 00002/00002/00289
d D 8.1 93/06/02 20:01:38 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00006/00284
d D 5.16 93/04/05 17:06:36 dab 24 23
c Fixes for gcc2 warning messages.
e
s 00007/00001/00283
d D 5.15 92/12/18 14:12:44 dab 23 22
c Add defines for Flowcontrol option and
c fix the SLC_NAME_OK() macro.
e
s 00005/00000/00279
d D 5.14 91/04/03 16:07:00 bostic 22 21
c protect all user-level include files against reinclusion
e
s 00009/00005/00270
d D 5.13 91/03/22 01:43:31 dab 21 20
c upgrade authentication/encryption to latest & greatest
e
s 00002/00003/00273
d D 5.12 91/03/05 13:05:46 dab 20 19
c Make TELOPT_ENCRYPT 38, it's official option number.
e
s 00101/00018/00175
d D 5.11 91/02/28 21:35:21 dab 19 18
c Add support for encryption and authentication
e
s 00012/00003/00181
d D 5.10 90/06/28 13:08:13 borman 18 17
c Add XDISPLOC, ENVIRON, SOFT_TAB and LIT_ECHO definitions
e
s 00020/00003/00164
d D 5.9 90/06/19 19:11:24 kfall 17 16
c add definitions for Kerberized telnet (from Athena)
e
s 00001/00011/00166
d D 5.8 90/06/01 14:02:30 bostic 16 15
c new copyright notice
e
s 00005/00003/00172
d D 5.7 89/11/14 10:04:05 borman 15 14
c Add new MODE_ definitions for new version of telnet
e
s 00001/00001/00174
d D 5.6 89/09/01 13:11:18 borman 14 13
c Move NTELOPTS outside of the #ifdef TELOPTS
e
s 00073/00001/00102
d D 5.5 89/08/21 15:00:18 borman 13 12
c Add support for LINEMODE option
e
s 00012/00002/00091
d D 5.4 89/02/15 20:06:17 minshall 12 11
c Mods from CMU.
e
s 00010/00005/00083
d D 5.3 88/06/27 16:37:44 bostic 11 10
c install approved copyright notice
e
s 00008/00002/00080
d D 5.2 88/04/21 09:07:17 bostic 10 9
c add Berkeley specific header
e
s 00008/00001/00074
d D 5.1 85/05/30 09:47:15 dist 9 8
c Add copyright
e
s 00003/00003/00072
d D 4.8 85/03/27 09:45:29 karels 8 7
c add EOR
e
s 00003/00002/00072
d D 4.7 85/03/24 15:26:21 sam 7 6
c botched number of options
e
s 00016/00010/00058
d D 4.6 85/03/24 15:03:14 sam 6 5
c add qualifiers for ttype negotiation; fill in other options
e
s 00005/00002/00063
d D 4.5 85/03/24 13:06:05 sam 5 4
c add terminal type telnet option
e
s 00001/00001/00064
d D 4.4 82/03/16 21:31:08 root 4 3
c back to comments for sccs id
e
s 00001/00002/00064
d D 4.3 82/03/16 21:25:28 root 3 2
c set up sccsid's
e
s 00023/00018/00043
d D 4.2 82/03/01 11:50:12 sam 2 1
c fix up definitions of options
e
s 00061/00000/00000
d D 4.1 82/02/28 10:34:14 root 1 0
c date and time created 82/02/28 10:34:14 by root
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/

E 3
I 3
D 4
static char sccsid[] = "%W% (Berkeley) %G%";
E 4
I 4
D 9
/*	%M%	%I%	%E%	*/
E 9
I 9
/*
D 25
 * Copyright (c) 1983 Regents of the University of California.
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
D 16
 * Redistribution and use in source and binary forms are permitted
D 11
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 11
I 11
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
E 16
I 16
 * %sccs.include.redist.c%
E 16
E 11
E 10
 *
 *	%W% (Berkeley) %G%
 */

I 22
#ifndef _TELNET_H_
#define	_TELNET_H_

E 22
E 9
E 4
E 3
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
I 8
#define EOR     239             /* end of record (transparent mode) */
I 13
#define	ABORT	238		/* Abort process */
#define	SUSP	237		/* Suspend process */
#define	xEOF	236		/* End of file: EOF is already used... */
E 13
E 8

#define SYNCH	242		/* for telfunc calls */

D 6
/* telnet options */
E 6
I 6
#ifdef TELCMDS
char *telcmds[] = {
I 13
	"EOF", "SUSP", "ABORT", "EOR",
E 13
	"SE", "NOP", "DMARK", "BRK", "IP", "AO", "AYT", "EC",
D 19
	"EL", "GA", "SB", "WILL", "WONT", "DO", "DONT", "IAC",
E 19
I 19
	"EL", "GA", "SB", "WILL", "WONT", "DO", "DONT", "IAC", 0,
E 19
};
I 19
#else
extern char *telcmds[];
#endif

E 19
I 13
#define	TELCMD_FIRST	xEOF
#define	TELCMD_LAST	IAC
D 24
#define	TELCMD_OK(x)	((x) <= TELCMD_LAST && (x) >= TELCMD_FIRST)
E 24
I 24
#define	TELCMD_OK(x)	((unsigned int)(x) <= TELCMD_LAST && \
			 (unsigned int)(x) >= TELCMD_FIRST)
E 24
#define	TELCMD(x)	telcmds[(x)-TELCMD_FIRST]
E 13
D 19
#endif
E 19
E 6

I 6
/* telnet options */
E 6
#define TELOPT_BINARY	0	/* 8-bit data path */
#define TELOPT_ECHO	1	/* echo */
D 2
#define	TELOPT_RCP	2
#define	TELOPT_SGA	3
#define	TELOPT_NAME	4
#define	TELOPT_STATUS	5
#define	TELOPT_TM	6
#define	TELOPT_RCTE	7
#define TELOPT_NAOL 	8
#define TELOPT_NAOP 	9
#define TELOPT_NAOCRD	10
#define TELOPT_NAOHTS	11
#define TELOPT_NAOHTD	12
#define TELOPT_NAOFFD	13
#define TELOPT_NAOVTS	14
#define TELOPT_NAOVTD	15
#define TELOPT_NAOLFD	16
#define TELOPT_XASCII	17
#define TELOPT_EXOPL	255
E 2
I 2
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
I 5
D 6
/* 22-23 are assigned */
E 6
I 6
#define	TELOPT_SUPDUPOUTPUT 22	/* supdup output */
#define	TELOPT_SNDLOC	23	/* send location */
E 6
#define	TELOPT_TTYPE	24	/* terminal type */
I 6
#define	TELOPT_EOR	25	/* end or record */
E 6
E 5
D 12
#define TELOPT_EXOPL	255	/* extended-options-list */
E 12
I 12
#define	TELOPT_TUID	26	/* TACACS user identification */
#define	TELOPT_OUTMRK	27	/* output marking */
#define	TELOPT_TTYLOC	28	/* terminal location number */
#define	TELOPT_3270REGIME 29	/* 3270 regime */
#define	TELOPT_X3PAD	30	/* X.3 PAD */
#define	TELOPT_NAWS	31	/* window size */
#define	TELOPT_TSPEED	32	/* terminal speed */
#define	TELOPT_LFLOW	33	/* remote flow control */
I 13
#define TELOPT_LINEMODE	34	/* Linemode option */
I 18
#define TELOPT_XDISPLOC	35	/* X Display Location */
D 26
#define TELOPT_ENVIRON	36	/* Environment variables */
E 26
I 26
#define TELOPT_OLD_ENVIRON 36	/* Old - Environment variables */
E 26
E 18
I 17
D 19
#define	TELOPT_AUTHENTICATION 45 /* XXX Auto Authenticate */
E 19
I 19
#define	TELOPT_AUTHENTICATION 37/* Authenticate */
I 20
#define	TELOPT_ENCRYPT	38	/* Encryption option */
I 26
#define TELOPT_NEW_ENVIRON 39	/* New - Environment variables */
E 26
E 20
E 19
E 17
E 13
#define	TELOPT_EXOPL	255	/* extended-options-list */
E 12
E 2

D 6
#ifdef TELCMDS
char *telcmds[] = {
	"SE", "NOP", "DMARK", "BRK", "IP", "AO", "AYT", "EC",
	"EL", "GA", "SB", "WILL", "WONT", "DO", "DONT", "IAC",
};
#endif

E 6
D 14
#ifdef TELOPTS
E 14
D 5
char *telopts[] = {
E 5
I 5
D 7
#define	NTELOPTS	25
E 7
I 7
D 12
#define	NTELOPTS	(1+TELOPT_EOR)
E 12
I 12
D 13
#define	NTELOPTS	(1+TELOPT_LFLOW)
E 13
I 13
D 17
#define	NTELOPTS	(1+TELOPT_LINEMODE)
E 17
I 17
D 19
#define	NTELOPTS	(1+TELOPT_AUTHENTICATION)
E 19
I 19
D 20
#define	TELOPT_ENCRYPT	51	/* Encryption option - EXPERIMENTAL */
E 20

D 26
#define	NTELOPTS	(1+TELOPT_ENCRYPT)
E 26
I 26
#define	NTELOPTS	(1+TELOPT_NEW_ENVIRON)
E 26
E 19
E 17
I 14
#ifdef TELOPTS
E 14
E 13
E 12
E 7
D 19
char *telopts[NTELOPTS] = {
E 19
I 19
char *telopts[NTELOPTS+1] = {
E 19
E 5
	"BINARY", "ECHO", "RCP", "SUPPRESS GO AHEAD", "NAME",
	"STATUS", "TIMING MARK", "RCTE", "NAOL", "NAOP",
	"NAOCRD", "NAOHTS", "NAOHTD", "NAOFFD", "NAOVTS",
D 2
	"NAOVTD", "NAOLFD", "EXTEND ASCII",
E 2
I 2
	"NAOVTD", "NAOLFD", "EXTEND ASCII", "LOGOUT", "BYTE MACRO",
D 5
	"DATA ENTRY TERMINAL", "SUPDUP"
E 5
I 5
D 6
	"DATA ENTRY TERMINAL", "SUPDUP", "#22", "#23", "TTYPE",
E 6
I 6
D 8
	"DATA ENTRY TERMINAL", "SUPDUP", "SUPDUP OUTPUT", "SEND LOCATION",
D 7
	"TERMINAL TYPE", "END OF RECORD",
E 7
I 7
	    "TERMINAL TYPE",
	"END OF RECORD",
E 8
I 8
	"DATA ENTRY TERMINAL", "SUPDUP", "SUPDUP OUTPUT",
	"SEND LOCATION", "TERMINAL TYPE", "END OF RECORD",
I 12
	"TACACS UID", "OUTPUT MARKING", "TTYLOC",
	"3270 REGIME", "X.3 PAD", "NAWS", "TSPEED", "LFLOW",
I 13
D 17
	"LINEMODE",
E 17
I 17
D 18
	"LINEMODE", "UNKNOWN 35", "UNKNOWN 36", "UNKNOWN 37",
	"UNKNOWN 38", "UNKNOWN 39", "UNKNOWN 40", "UNKNOWN 41",
E 18
I 18
D 19
	"LINEMODE", "XDISPLOC", "ENVIRON",
	"UNKNOWN 37", "UNKNOWN 38", "UNKNOWN 39", "UNKNOWN 40", "UNKNOWN 41",
E 18
	"UNKNOWN 42", "UNKNOWN 43", "UNKNOWN 44", "AUTHENTICATION",
E 19
I 19
D 26
	"LINEMODE", "XDISPLOC", "ENVIRON", "AUTHENTICATION",
D 20
	"38", "39", "40", "41", "42", "43", "44", "45", "46",
	"47", "48", "49", "50", "X-ENCRYPT",
E 20
I 20
	"ENCRYPT",
E 26
I 26
	"LINEMODE", "XDISPLOC", "OLD-ENVIRON", "AUTHENTICATION",
	"ENCRYPT", "NEW-ENVIRON",
E 26
E 20
	0,
E 19
E 17
E 13
E 12
E 8
E 7
E 6
E 5
E 2
};
I 13
#define	TELOPT_FIRST	TELOPT_BINARY
D 17
#define	TELOPT_LAST	TELOPT_LINEMODE
E 17
I 17
D 19
#define	TELOPT_LAST	TELOPT_AUTHENTICATION
E 19
I 19
D 26
#define	TELOPT_LAST	TELOPT_ENCRYPT
E 26
I 26
#define	TELOPT_LAST	TELOPT_NEW_ENVIRON
E 26
E 19
E 17
D 24
#define	TELOPT_OK(x)	((x) <= TELOPT_LAST && (x) >= TELOPT_FIRST)
E 24
I 24
#define	TELOPT_OK(x)	((unsigned int)(x) <= TELOPT_LAST)
E 24
#define	TELOPT(x)	telopts[(x)-TELOPT_FIRST]
E 13
#endif
I 6

/* sub-option qualifiers */
#define	TELQUAL_IS	0	/* option is... */
#define	TELQUAL_SEND	1	/* send option */
I 18
#define	TELQUAL_INFO	2	/* ENVIRON: informational version of IS */
I 19
#define	TELQUAL_REPLY	2	/* AUTHENTICATION: client version of IS */
I 21
#define	TELQUAL_NAME	3	/* AUTHENTICATION: client version of IS */
E 21
E 19
E 18
I 13

I 23
#define	LFLOW_OFF		0	/* Disable remote flow control */
#define	LFLOW_ON		1	/* Enable remote flow control */
#define	LFLOW_RESTART_ANY	2	/* Restart output on any char */
#define	LFLOW_RESTART_XON	3	/* Restart output only on XON */

E 23
/*
 * LINEMODE suboptions
 */

#define	LM_MODE		1
#define	LM_FORWARDMASK	2
#define	LM_SLC		3

#define	MODE_EDIT	0x01
#define	MODE_TRAPSIG	0x02
#define	MODE_ACK	0x04
I 18
#define MODE_SOFT_TAB	0x08
#define MODE_LIT_ECHO	0x10
E 18

D 18
#define	MODE_MASK	(MODE_EDIT|MODE_TRAPSIG|MODE_ACK)
E 18
I 18
#define	MODE_MASK	0x1f
E 18

/* Not part of protocol, but needed to simplify things... */
D 15
#define MODE_FLOW		0x40
#define MODE_ECHO		0x80
#define MODE_FORCE		0x20
E 15
I 15
#define MODE_FLOW		0x0100
#define MODE_ECHO		0x0200
#define MODE_INBIN		0x0400
#define MODE_OUTBIN		0x0800
#define MODE_FORCE		0x1000
E 15

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

D 19
#define	SLC_NAMES	"0", "SYNCH", "BRK", "IP", "AO", "AYT", "EOR", \
E 19
I 19
/*
 * For backwards compatability, we define SLC_NAMES to be the
 * list of names if SLC_NAMES is not defined.
 */
#define	SLC_NAMELIST	"0", "SYNCH", "BRK", "IP", "AO", "AYT", "EOR", \
E 19
			"ABORT", "EOF", "SUSP", "EC", "EL", "EW", "RP", \
D 19
			"LNEXT", "XON", "XOFF", "FORW1", "FORW2"
E 19
I 19
			"LNEXT", "XON", "XOFF", "FORW1", "FORW2", 0,
#ifdef	SLC_NAMES
char *slc_names[] = {
	SLC_NAMELIST
};
#else
extern char *slc_names[];
#define	SLC_NAMES SLC_NAMELIST
#endif
E 19

I 19
D 23
#define	SLC_NAME_OK(x)	((x) >= 0 && (x) < NSLC)
E 23
I 23
D 24
#define	SLC_NAME_OK(x)	((x) >= 0 && (x) <= NSLC)
E 24
I 24
#define	SLC_NAME_OK(x)	((unsigned int)(x) <= NSLC)
E 24
E 23
#define SLC_NAME(x)	slc_names[x]

E 19
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
I 18

D 26
#define	ENV_VALUE	0
#define	ENV_VAR		1
E 26
I 26
#define	OLD_ENV_VAR	1
#define	OLD_ENV_VALUE	0
#define	NEW_ENV_VAR	0
#define	NEW_ENV_VALUE	1
E 26
#define	ENV_ESC		2
I 23
#define ENV_USERVAR	3
E 23
E 18
I 17

/*
 * AUTHENTICATION suboptions
 */

D 19
#define	TELQUAL_AUTHTYPE_NONE		0
#define	TELQUAL_AUTHTYPE_PRIVATE	1
#define	TELQUAL_AUTHTYPE_KERBEROS	2
E 19
I 19
/*
 * Who is authenticating who ...
 */
#define	AUTH_WHO_CLIENT		0	/* Client authenticating server */
#define	AUTH_WHO_SERVER		1	/* Server authenticating client */
#define	AUTH_WHO_MASK		1
E 19

D 19
/* Kerberos-specific */
E 19
I 19
/*
 * amount of authentication done
 */
#define	AUTH_HOW_ONE_WAY	0
#define	AUTH_HOW_MUTUAL		2
#define	AUTH_HOW_MASK		2
E 19

D 19
#define	TELQUAL_AUTHTYPE_KERBEROS_V4		4
#define	TELQUAL_AUTHTYPE_KERBEROS_V5		5
#define	TELQUAL_AUTHTYPE_KERBEROS_USERNAME	1
E 19
I 19
#define	AUTHTYPE_NULL		0
#define	AUTHTYPE_KERBEROS_V4	1
#define	AUTHTYPE_KERBEROS_V5	2
#define	AUTHTYPE_SPX		3
#define	AUTHTYPE_MINK		4
#define	AUTHTYPE_CNT		5

#define	AUTHTYPE_TEST		99

#ifdef	AUTH_NAMES
char *authtype_names[] = {
	"NULL", "KERBEROS_V4", "KERBEROS_V5", "SPX", "MINK", 0,
};
#else
extern char *authtype_names[];
#endif

D 24
#define	AUTHTYPE_NAME_OK(x)	((x) >= 0 && (x) < AUTHTYPE_CNT)
E 24
I 24
#define	AUTHTYPE_NAME_OK(x)	((unsigned int)(x) < AUTHTYPE_CNT)
E 24
#define	AUTHTYPE_NAME(x)	authtype_names[x]

/*
 * ENCRYPTion suboptions
 */
#define	ENCRYPT_IS		0	/* I pick encryption type ... */
#define	ENCRYPT_SUPPORT		1	/* I support encryption types ... */
#define	ENCRYPT_REPLY		2	/* Initial setup response */
#define	ENCRYPT_START		3	/* Am starting to send encrypted */
#define	ENCRYPT_END		4	/* Am ending encrypted */
#define	ENCRYPT_REQSTART	5	/* Request you start encrypting */
#define	ENCRYPT_REQEND		6	/* Request you send encrypting */
D 21
#define	ENCRYPT_CNT		7
E 21
I 21
#define	ENCRYPT_ENC_KEYID	7
#define	ENCRYPT_DEC_KEYID	8
#define	ENCRYPT_CNT		9
E 21

#define	ENCTYPE_ANY		0
D 21
#define	ENCTYPE_KRBDES		1
#define	ENCTYPE_CNT		2
E 21
I 21
#define	ENCTYPE_DES_CFB64	1
#define	ENCTYPE_DES_OFB64	2
#define	ENCTYPE_CNT		3
E 21

#ifdef	ENCRYPT_NAMES
char *encrypt_names[] = {
	"IS", "SUPPORT", "REPLY", "START", "END",
D 21
	"REQUEST-START", "REQUEST-END",
E 21
I 21
	"REQUEST-START", "REQUEST-END", "ENC-KEYID", "DEC-KEYID",
E 21
	0,
};
char *enctype_names[] = {
D 21
	"ANY", "KRBDES",  0,
E 21
I 21
	"ANY", "DES_CFB64",  "DES_OFB64",  0,
E 21
};
#else
extern char *encrypt_names[];
extern char *enctype_names[];
#endif


D 24
#define	ENCRYPT_NAME_OK(x)	((x) >= 0 && (x) < ENCRYPT_CNT)
E 24
I 24
#define	ENCRYPT_NAME_OK(x)	((unsigned int)(x) < ENCRYPT_CNT)
E 24
#define	ENCRYPT_NAME(x)		encrypt_names[x]

D 24
#define	ENCTYPE_NAME_OK(x)	((x) >= 0 && (x) < ENCTYPE_CNT)
E 24
I 24
#define	ENCTYPE_NAME_OK(x)	((unsigned int)(x) < ENCTYPE_CNT)
E 24
#define	ENCTYPE_NAME(x)		enctype_names[x]
I 22

#endif /* !_TELNET_H_ */
E 22
E 19
E 17
E 13
E 6
E 1
