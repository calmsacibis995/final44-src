h38154
s 00002/00002/00084
d D 8.1 93/06/06 16:35:10 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00085
d D 5.5 90/06/01 17:48:26 bostic 11 10
c new copyright notice
e
s 00003/00002/00093
d D 5.4 89/05/11 09:38:48 bostic 10 9
c file reorg, pathnames.h, paths.h
e
s 00015/00004/00080
d D 5.3 88/09/02 12:04:55 bostic 9 8
c add Berkeley specific copyright
e
s 00002/00002/00082
d D 5.2 87/12/22 13:50:20 bostic 8 7
c make ANSI C compatible
e
s 00007/00001/00077
d D 5.1 85/04/30 12:30:02 dist 7 6
c Add copyright
e
s 00005/00006/00073
d D 4.6 83/06/25 01:15:27 sam 6 5
c so much...clean up after ralph's merge of wendel and mo code;
c purge VMUNIX include since changes for signals make it no longer portable 
c to systems other than 4.2; fix ventel for no echo strapping; do setjmps 
c instead of assuming interrupted system calls; purge lcmd, if people use 
e
s 00025/00007/00054
d D 4.5 83/06/15 13:53:38 ralph 5 4
c changes for local info, parity, vadic auto dialers
e
s 00000/00000/00061
d D 4.4 81/11/29 22:51:35 sam 4 3
c reformatting
e
s 00000/00000/00061
d D 4.3 81/11/20 10:45:24 sam 3 2
c cosmetics
e
s 00002/00000/00059
d D 4.2 81/06/02 10:00:24 sam 2 1
c added echocheck mode for ftp (from decvax!shannon)
e
s 00059/00000/00000
d D 4.1 81/05/09 16:45:30 root 1 0
c date and time created 81/05/09 16:45:30 by root
e
u
U
t
T
I 7
/*
D 9
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 9
I 9
D 12
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
 *
D 11
 * Redistribution and use in source and binary forms are permitted
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
E 11
I 11
 * %sccs.include.redist.c%
E 11
E 9
 */

E 7
I 1
D 6
/*	%M%	%I%	%E%	*/
E 6
I 6
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 7
#endif
E 7
I 7
D 9
#endif not lint
E 9
I 9
#endif /* not lint */
E 9
E 7

E 6
#include "tip.h"
I 10
#include "pathnames.h"
E 10

/*
 * Definition of variables
 */
value_t vtable[] = {
	{ "beautify",	BOOL,			(READ|WRITE)<<PUBLIC,
	  "be",		(char *)TRUE },
	{ "baudrate",	NUMBER|IREMOTE|INIT,	(READ<<PUBLIC)|(WRITE<<ROOT),
	  "ba",		(char *)&BR },
	{ "dialtimeout",NUMBER,			(READ<<PUBLIC)|(WRITE<<ROOT),
	  "dial",	(char *)60 },
	{ "eofread",	STRING|IREMOTE|INIT,	(READ|WRITE)<<PUBLIC,
	  "eofr",	(char *)&IE },
D 5
	{ "eofwrite",	STRING|IREMOTE|INIT,	((READ|WRITE)<<PUBLIC),
E 5
I 5
	{ "eofwrite",	STRING|IREMOTE|INIT,	(READ|WRITE)<<PUBLIC,
E 5
	  "eofw",	(char *)&OE },
	{ "eol",	STRING|IREMOTE|INIT,	(READ|WRITE)<<PUBLIC,
	  NOSTR,	(char *)&EL },
	{ "escape",	CHAR,			(READ|WRITE)<<PUBLIC,
	  "es",		(char *)'~' },
D 5
	{ "exceptions",	STRING|INIT,		(READ|WRITE)<<PUBLIC,
	  "ex",		"\t\n\b\f" },
E 5
I 5
	{ "exceptions",	STRING|INIT|IREMOTE,	(READ|WRITE)<<PUBLIC,
	  "ex",		(char *)&EX },
E 5
	{ "force",	CHAR,			(READ|WRITE)<<PUBLIC,
D 5
	  "fo",		(char *)(char)CTRL(p) },
E 5
I 5
D 8
	  "fo",		(char *)CTRL(p) },
E 8
I 8
	  "fo",		(char *)CTRL('p') },
E 8
E 5
	{ "framesize",	NUMBER|IREMOTE|INIT,	(READ|WRITE)<<PUBLIC,
	  "fr",		(char *)&FS },
	{ "host",	STRING|IREMOTE|INIT,	READ<<PUBLIC,
	  "ho",		(char *)&HO },
D 6
#ifdef ACULOG
	{ "lock",	STRING|INIT,		(READ|WRITE)<<ROOT,
	  NOSTR,	"/tmp/aculock" },
E 6
	{ "log",	STRING|INIT,		(READ|WRITE)<<ROOT,
D 10
	  NOSTR,	"/usr/adm/aculog" },
E 10
I 10
	  NOSTR,	_PATH_ACULOG },
E 10
D 6
#endif
E 6
	{ "phones",	STRING|INIT|IREMOTE,	READ<<PUBLIC,
	  NOSTR,	(char *)&PH },
D 5
	{ "prompt",	CHAR,			(READ<<PUBLIC)|(WRITE<<ROOT),
E 5
I 5
	{ "prompt",	CHAR,			(READ|WRITE)<<PUBLIC,
E 5
	  "pr",		(char *)'\n' },
	{ "raise",	BOOL,			(READ|WRITE)<<PUBLIC,
	  "ra",		(char *)FALSE },
	{ "raisechar",	CHAR,			(READ|WRITE)<<PUBLIC,
D 8
	  "rc",		(char *)CTRL(a) },
E 8
I 8
	  "rc",		(char *)CTRL('a') },
E 8
D 5
	{ "record",	STRING|INIT,		(READ|WRITE)<<PUBLIC,
	  "rec",	"tip.record" },
E 5
I 5
	{ "record",	STRING|INIT|IREMOTE,	(READ|WRITE)<<PUBLIC,
	  "rec",	(char *)&RE },
E 5
	{ "remote",	STRING|INIT|IREMOTE,	READ<<PUBLIC,
	  NOSTR,	(char *)&RM },
	{ "script",	BOOL,			(READ|WRITE)<<PUBLIC,
	  "sc",		(char *)FALSE },
	{ "tabexpand",	BOOL,			(READ|WRITE)<<PUBLIC,
	  "tab",	(char *)FALSE },
	{ "verbose",	BOOL,			(READ|WRITE)<<PUBLIC,
	  "verb",	(char *)TRUE },
	{ "SHELL",	STRING|ENVIRON|INIT,	(READ|WRITE)<<PUBLIC,
D 10
	  NULL,		"/bin/sh" },
E 10
I 10
	  NULL,		_PATH_BSHELL },
E 10
	{ "HOME",	STRING|ENVIRON,		(READ|WRITE)<<PUBLIC,
	  NOSTR,	NOSTR },
I 2
	{ "echocheck",	BOOL,			(READ|WRITE)<<PUBLIC,
	  "ec",		(char *)FALSE },
I 5
	{ "disconnect",	STRING|IREMOTE|INIT,	(READ|WRITE)<<PUBLIC,
	  "di",		(char *)&DI },
	{ "tandem",	BOOL,			(READ|WRITE)<<PUBLIC,
	  "ta",		(char *)TRUE },
	{ "linedelay",	NUMBER|IREMOTE|INIT,	(READ|WRITE)<<PUBLIC,
	  "ldelay",	(char *)&DL },
	{ "chardelay",	NUMBER|IREMOTE|INIT,	(READ|WRITE)<<PUBLIC,
	  "cdelay",	(char *)&CL },
	{ "etimeout",	NUMBER|IREMOTE|INIT,	(READ|WRITE)<<PUBLIC,
	  "et",		(char *)&ET },
	{ "rawftp",	BOOL,			(READ|WRITE)<<PUBLIC,
	  "raw",	(char *)FALSE },
	{ "halfduplex",	BOOL,			(READ|WRITE)<<PUBLIC,
	  "hdx",	(char *)FALSE },
	{ "localecho",	BOOL,			(READ|WRITE)<<PUBLIC,
	  "le",		(char *)FALSE },
D 6
	{ "parity",	STRING|INIT|IREMOTE,		(READ|WRITE)<<PUBLIC,
E 6
I 6
	{ "parity",	STRING|INIT|IREMOTE,	(READ|WRITE)<<PUBLIC,
E 6
	  "par",	(char *)&PA },
E 5
E 2
	{ NOSTR, NULL, NULL, NOSTR, NOSTR }
};
E 1
