h27190
s 00001/00000/00099
d D 8.4 94/10/09 20:49:19 mckusick 19 18
c update to support passive mode (from cgd)
e
s 00001/00001/00098
d D 8.3 94/04/02 15:11:08 pendry 18 17
c add 1994 copyright
e
s 00006/00014/00093
d D 8.2 94/04/02 15:06:48 pendry 17 16
c prettyness police
e
s 00002/00002/00105
d D 8.1 93/06/06 14:41:14 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00106
d D 5.9 90/06/01 15:52:00 bostic 15 14
c new copyright notice
e
s 00000/00002/00117
d D 5.8 89/10/03 15:10:25 bostic 14 13
c POSIX signals
e
s 00002/00000/00117
d D 5.7 89/05/26 12:54:17 rick 13 12
c add typedef for signal return for better portability
e
s 00005/00002/00112
d D 5.6 89/05/17 16:26:15 karels 12 11
c remember current server type setting, don't change until doing
c transfer; back to list/nlst in ascii; check type on proxy and primary server
c before doing text in binary
e
s 00010/00005/00104
d D 5.5 88/06/29 20:34:22 bostic 11 10
c install approved copyright notice
e
s 00008/00002/00101
d D 5.4 88/03/14 17:21:39 bostic 10 9
c add Berkeley specific headers
e
s 00006/00002/00097
d D 5.3 86/03/07 12:32:10 minshall 9 8
c Clean up for lint; change some stderr to stdout; bug fix
c (in ruserpass.c, routine rnetrc()).
e
s 00031/00002/00068
d D 5.2 86/02/03 14:41:10 minshall 8 7
c Changes from Steve Jacobson (from <csvsj@ucbopal>).
e
s 00007/00001/00063
d D 5.1 85/05/31 17:09:05 dist 7 6
c Add copyright
e
s 00000/00001/00064
d D 4.6 83/07/26 21:34:20 sam 6 5
c linger purge
e
s 00001/00000/00064
d D 4.5 83/06/19 23:08:33 sam 5 4
c fix m* cmds and add linger control
e
s 00004/00000/00060
d D 4.4 83/03/23 10:26:33 sam 4 3
c merge of changes from jsq@utexas-11
e
s 00001/00000/00059
d D 4.3 83/03/01 02:11:47 sam 3 2
c add doglob to control globbing
e
s 00002/00000/00057
d D 4.2 83/02/21 19:38:21 sam 2 1
c fixes from texas
e
s 00057/00000/00000
d D 4.1 83/01/15 16:53:22 sam 1 0
c date and time created 83/01/15 16:53:22 by sam
e
u
U
t
T
I 1
D 7
/*	%M%	%I%	%E%	*/
E 7
I 7
/*
D 8
 * Copyright (c) 1980 Regents of the University of California.
E 8
I 8
D 12
 * Copyright (c) 1985 Regents of the University of California.
E 12
I 12
D 16
 * Copyright (c) 1985, 1989 Regents of the University of California.
E 12
E 8
D 10
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 10
I 10
 * All rights reserved.
E 16
I 16
D 18
 * Copyright (c) 1985, 1989, 1993
E 18
I 18
 * Copyright (c) 1985, 1989, 1993, 1994
E 18
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 15
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
E 15
I 15
 * %sccs.include.redist.c%
E 15
E 11
E 10
 *
 *	%W% (Berkeley) %G%
 */
E 7

/*
 * FTP global variables.
 */

I 17
#include <sys/param.h>
#include <setjmp.h>

#include "extern.h"

E 17
/*
 * Options and other state info.
 */
int	trace;			/* trace packets exchanged */
I 4
int	hash;			/* print # for each buffer transferred */
int	sendport;		/* use PORT cmd for each data connection */
E 4
int	verbose;		/* print messages coming back from server */
int	connected;		/* connected to server */
int	fromatty;		/* input is from a terminal */
int	interactive;		/* interactively prompt on m* cmds */
int	debug;			/* debugging level */
int	bell;			/* ring bell on cmd completion */
I 3
int	doglob;			/* glob local file names */
I 5
D 6
int	linger;			/* linger on close of data connections */
E 6
E 5
E 3
int	autologin;		/* establish user account on connection */
D 8

E 8
I 8
int	proxy;			/* proxy server connection active */
int	proxflag;		/* proxy connection exists */
int	sunique;		/* store files on server with unique name */
int	runique;		/* store local files with unique name */
int	mcase;			/* map upper to lower case for mget names */
int	ntflag;			/* use ntin ntout tables for name translation */
int	mapflag;		/* use mapin mapout templates on file names */
int	code;			/* return/reply code for ftp command */
D 9
int	macroflg;		/* active macro */
E 9
int	crflag;			/* if 1, strip car. rets. on ascii gets */
char	pasv[64];		/* passive port for proxy data connection */
I 19
int	passivemode;		/* passive mode enabled */
E 19
char	*altarg;		/* argv[1] with no shell-like preprocessing  */
char	ntin[17];		/* input translation table */
char	ntout[17];		/* output translation table */
D 17
#include <sys/param.h>
E 17
char	mapin[MAXPATHLEN];	/* input map template */
char	mapout[MAXPATHLEN];	/* output map template */
E 8
char	typename[32];		/* name of file transfer type */
D 12
int	type;			/* file transfer type */
E 12
I 12
int	type;			/* requested file transfer type */
int	curtype;		/* current file transfer type */
E 12
char	structname[32];		/* name of file transfer structure */
int	stru;			/* file transfer structure */
char	formname[32];		/* name of file transfer format */
int	form;			/* file transfer format */
char	modename[32];		/* name of file transfer mode */
int	mode;			/* file transfer mode */
I 2
char	bytename[32];		/* local byte size in ascii */
int	bytesize;		/* local byte size in binary */
E 2

char	*hostname;		/* name of host connected to */
I 12
int	unix_server;		/* server is unix, can use binary for ascii */
int	unix_proxy;		/* proxy is unix, can use binary for ascii */
E 12

struct	servent *sp;		/* service spec for tcp/ftp */

D 17
#include <setjmp.h>
E 17
jmp_buf	toplevel;		/* non-local goto stuff for cmd scanner */

char	line[200];		/* input line buffer */
char	*stringbase;		/* current scan point in line buffer */
char	argbuf[200];		/* argument storage buffer */
char	*argbase;		/* current storage point in arg buffer */
int	margc;			/* count of arguments on input line */
char	*margv[20];		/* args parsed from input line */
I 8
int     cpend;                  /* flag: if != 0, then pending server reply */
int	mflag;			/* flag: if != 0, then active multi command */
E 8

int	options;		/* used during socket creation */

/*
 * Format of command table.
 */
struct cmd {
	char	*c_name;	/* name of command */
	char	*c_help;	/* help string */
	char	c_bell;		/* give bell when command completes */
I 4
	char	c_conn;		/* must be connected to use command */
I 8
	char	c_proxy;	/* proxy server may execute */
E 8
E 4
D 17
	int	(*c_handler)();	/* function to call */
E 17
I 17
	void	(*c_handler) __P((int, char **)); /* function to call */
E 17
};
I 8

struct macel {
	char mac_name[9];	/* macro name */
	char *mac_start;	/* start of macro in macbuf */
	char *mac_end;		/* end of macro in macbuf */
};

int macnum;			/* number of defined macros */
D 9
struct macel macros[16], *macpt;
E 9
I 9
struct macel macros[16];
E 9
char macbuf[4096];
E 8
D 17

extern	char *tail();
extern	char *index();
extern	char *rindex();
I 4
extern	char *remglob();
E 4
extern	int errno;
I 9
extern	char *mktemp();
extern	char *strncpy();
extern	char *strncat();
extern	char *strcat();
extern	char *strcpy();
E 17
I 13
D 14

typedef int sig_t;
E 14
E 13
E 9
E 1
