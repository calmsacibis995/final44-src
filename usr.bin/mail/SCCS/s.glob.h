h18362
s 00002/00002/00072
d D 8.1 93/06/06 15:07:51 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00074
d D 5.21 92/06/26 12:03:13 bostic 38 37
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00000/00001/00074
d D 5.20 90/06/25 00:01:35 edward 37 36
c remove call of _fwalk
e
s 00001/00011/00074
d D 5.19 90/06/01 16:58:47 bostic 36 35
c new copyright notice
e
s 00001/00001/00084
d D 5.18 88/10/20 19:40:36 edward 35 34
c non-flexname portability fix (from Ian Darwin, darwin!ian)
e
s 00000/00001/00085
d D 5.17 88/08/17 14:23:40 edward 34 33
c don't need to keep the name of mailrc around
e
s 00000/00001/00086
d D 5.16 88/08/09 17:57:49 edward 33 32
c DEAD added, mbox changed to MBOX
e
s 00000/00001/00087
d D 5.15 88/07/07 22:57:10 edward 32 31
c got rid of unused command "local" and some undocumented command names
e
s 00001/00000/00087
d D 5.14 88/07/07 09:34:45 edward 31 30
c merged even more functionality into send()
e
s 00004/00006/00083
d D 5.13 88/07/07 06:55:14 edward 30 29
c removed some unnecessary global vars, dynamically allocate some others,
c added spreserve to fix the no sreset when sourcing kludge
e
s 00000/00001/00089
d D 5.12 88/07/06 20:44:26 edward 29 28
c removed global uid variable
e
s 00010/00005/00080
d D 5.11 88/06/29 21:01:45 bostic 28 27
c install approved copyright notice
e
s 00000/00002/00085
d D 5.10 88/06/19 04:20:58 edward 27 26
c rationalized mail sending code: keep h_to, h_cc, h_bcc, h_smopts as lists
c not strings; h_seq deleted; now understands <...> addresses; and many more.
c should be much cleaner and somewhat faster.
e
s 00000/00003/00087
d D 5.9 88/06/18 14:54:20 edward 26 25
c removed support for -r, -h, and rmail
e
s 00002/00003/00088
d D 5.8 88/06/17 15:05:06 edward 25 24
c cleaned up file handling code, now allows "mbox" variable
e
s 00000/00002/00091
d D 5.7 88/06/16 21:50:29 edward 24 23
c replaced intty and outtty by value("interactive"), ~ only in interactive mode
e
s 00003/00002/00090
d D 5.6 88/06/16 19:23:04 edward 23 22
c let "crt" default to the screen height from TIOCGWINSZ
e
s 00000/00001/00092
d D 5.5 88/06/11 03:32:29 edward 22 21
c changed the way -N is handled
e
s 00004/00003/00089
d D 5.4 88/06/09 22:24:30 edward 21 20
c new commands saveignore, saveretain, and savediscard
e
s 00008/00002/00084
d D 5.3 88/02/18 17:03:57 bostic 20 19
c written by Kurt Shoens; added Berkeley specific header
e
s 00002/00001/00084
d D 5.2 87/05/18 12:28:29 edward 19 18
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00007/00001/00078
d D 5.1 85/06/06 10:47:37 dist 18 17
c Add copyright
e
s 00002/00000/00077
d D 2.11 85/04/18 18:20:06 serge 17 16
c modified to work with new stdio; added retain command; fixed several bugs
e
s 00002/00004/00075
d D 2.10 83/08/11 22:16:11 sam 16 15
c standardize sccs keyword lines
e
s 00002/00001/00077
d D 2.9 83/01/29 18:48:32 leres 15 14
c Added pointer for local host names
e
s 00001/00000/00077
d D 2.8 82/07/28 23:17:01 kurt 14 13
c added ignored header hash table 
c 
e
s 00001/00002/00076
d D 2.7 82/06/24 23:55:48 kurt 13 12
c Made "mailname" an array rather than going through the subterfuge 
c of making mailname usually point to mailspace since you used to be able 
c to core dump mail using the old scheme... 
c 
e
s 00001/00000/00077
d D 2.6 82/02/13 21:24:01 kurt 12 11
c added global "loading" to indicate that reading of user's 
c .mailrc or /usr/lib/Mail.rc is in progress. 
c 
e
s 00001/00000/00076
d D 2.5 81/12/10 12:55:50 kurt 11 10
c added global variable baud -- output speed rate 
c 
e
s 00001/00000/00075
d D 2.4 81/09/16 14:36:21 kurt 10 9
c added global altnames -- list of alternative names for this user 
c 
e
s 00001/00001/00074
d D 2.3 81/08/12 17:21:59 kurt 9 8
c changed size of exponential string table so that it can make a string large
c enough to fill all of memory
e
s 00001/00000/00074
d D 2.2 81/07/20 17:09:00 kurt 8 7
c added global Tflag which is set to the file name given after -T:
c on exit from Mail, the article-id's of all messages read or deleted will
c be recorded here
e
s 00000/00000/00074
d D 2.1 81/07/01 11:11:19 kurt 7 6
c Release to Heidi Stettner
e
s 00001/00000/00073
d D 1.6 81/02/06 09:41:29 kas 6 5
c added noheader flag to suppress initial header print
e
s 00001/00000/00072
d D 1.5 80/10/18 18:15:34 kas 5 4
c added global variable cond -- current state of conditionals
e
s 00001/00001/00071
d D 1.4 80/10/17 00:41:44 kas 4 3
c max size of user names changed to PATHSIZE
e
s 00001/00000/00071
d D 1.3 80/10/16 16:18:09 kas 3 2
c added global flag shudann which causes lex() to print out
c the headers the next time it is convenient
e
s 00002/00000/00069
d D 1.2 80/10/10 11:59:59 kas 2 1
c added readonly flag; added pipef so that stop() can be sure
c to close the popen opened by type() with pclose instead of fclose()
e
s 00069/00000/00000
d D 1.1 80/10/08 09:53:39 kas 1 0
c date and time created 80/10/08 09:53:39 by kas
e
u
U
f b 
t
T
I 16
D 18
/*	%M%	%I%	%E%	*/
E 18
I 18
/*
D 39
 * Copyright (c) 1980 Regents of the University of California.
D 20
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 20
I 20
 * All rights reserved.
E 39
I 39
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 39
 *
D 36
 * Redistribution and use in source and binary forms are permitted
D 28
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 28
I 28
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
E 36
I 36
 * %sccs.include.redist.c%
E 36
E 28
E 20
 *
 *	%W% (Berkeley) %G%
 */
E 18

E 16
I 1
/*
 * A bunch of global variable declarations lie herein.
 * def.h must be included first.
D 16
 */

/*
D 15
 * Sccs Id = "%W% %G%";
E 15
I 15
 * Sccs Id = "%W% %G%;
E 16
E 15
 */

int	msgCount;			/* Count of messages read in */
D 30
int	mypid;				/* Current process id */
E 30
int	rcvmode;			/* True if receiving mail */
int	sawcom;				/* Set after first command */
D 26
int	hflag;				/* Sequence number for network -h */
char	*rflag;				/* -r address for network */
E 26
I 8
char	*Tflag;				/* -T temp file for netnews */
E 8
D 30
char	nosrc;				/* Don't source /usr/lib/Mail.rc */
E 30
I 6
D 22
char	noheader;			/* Suprress initial header listing */
E 22
E 6
D 27
int	selfsent;			/* User sent self something */
E 27
int	senderr;			/* An error while checking */
int	edit;				/* Indicates editing a file */
I 2
int	readonly;			/* Will be unable to rewrite file */
E 2
int	noreset;			/* String resets suspended */
int	sourcing;			/* Currently reading variant file */
I 12
int	loading;			/* Loading user definitions */
E 12
I 3
D 19
int	shudann;			/* Print headers when possible */
E 19
I 5
int	cond;				/* Current state of conditional exc. */
E 5
E 3
FILE	*itf;				/* Input temp file buffer */
FILE	*otf;				/* Output temp file buffer */
I 2
D 37
FILE	*pipef;				/* Pipe file we have opened */
E 37
E 2
int	image;				/* File descriptor for image of msg */
FILE	*input;				/* Current command input file */
D 25
char	*editfile;			/* Name of file being edited */
E 25
D 27
char	*sflag;				/* Subject given from non tty */
E 27
D 24
int	outtty;				/* True if standard output a tty */
int	intty;				/* True if standard input a tty */
E 24
I 11
D 23
int	baud;				/* Output baud rate */
E 23
E 11
D 25
char	mbox[PATHSIZE];			/* Name of mailbox file */
D 13
char	*mailname;			/* Name of system mailbox */
char	mailspace[PATHSIZE];		/* Space norm alloc'd for name */
E 13
I 13
char	mailname[PATHSIZE];		/* Name of system mailbox */
E 25
I 25
char	mailname[PATHSIZE];		/* Name of current file */
char	prevfile[PATHSIZE];		/* Name of previous file */
E 25
E 13
D 29
int	uid;				/* The invoker's user id */
E 29
D 30
char	mailrc[PATHSIZE];		/* Name of startup file */
char	deadletter[PATHSIZE];		/* Name of #/dead.letter */
char	homedir[PATHSIZE];		/* Path name of home directory */
D 4
char	myname[9];			/* My login id */
E 4
I 4
char	myname[PATHSIZE];		/* My login id */
E 30
I 30
D 34
char	*mailrc;			/* Name of startup file */
E 34
D 33
char	*deadletter;			/* Name of #/dead.letter */
E 33
char	*homedir;			/* Path name of home directory */
char	*myname;			/* My login name */
E 30
E 4
off_t	mailsize;			/* Size of system mailbox */
int	lexnumber;			/* Number of TNUMBER from scan() */
char	lexstring[STRINGLEN];		/* String from TSTRING, scan() */
int	regretp;			/* Pointer to TOS of regret tokens */
int	regretstack[REGDEP];		/* Stack of regretted tokens */
D 35
char	*stringstack[REGDEP];		/* Stack of regretted strings */
E 35
I 35
char	*string_stack[REGDEP];		/* Stack of regretted strings */
E 35
int	numberstack[REGDEP];		/* Stack of regretted numbers */
struct	message	*dot;			/* Pointer to current message */
struct	message	*message;		/* The actual message structure */
struct	var	*variables[HSHSIZE];	/* Pointer to active var list */
struct	grouphead	*groups[HSHSIZE];/* Pointer to active groups */
I 14
D 21
struct	ignore		*ignore[HSHSIZE];/* Pointer to ignored fields */
I 17
struct	ignore		*retain[HSHSIZE];/* Pointer to retained fields */
int	nretained;			/* Number of retained fields */
E 21
I 21
struct	ignoretab	ignore[2];	/* ignored and retained fields
					   0 is ignore, 1 is retain */
struct	ignoretab	saveignore[2];	/* ignored and retained fields
					   on save to folder */
I 31
struct	ignoretab	ignoreall[2];	/* special, ignore all headers */
E 31
E 21
E 17
E 14
I 10
char	**altnames;			/* List of alternate names for user */
I 15
D 32
char	**localnames;			/* List of aliases for our local host */
E 32
E 15
E 10
int	debug;				/* Debug flag set */
D 26
int	rmail;				/* Being called as rmail */
E 26
I 19
int	screenwidth;			/* Screen width, or best guess */
D 23
int	screenheight;			/* Screen height, or best guess */
E 23
I 23
int	screenheight;			/* Screen height, or best guess,
					   for "header" command */
int	realscreenheight;		/* the real screen height */
E 23
E 19

#include <setjmp.h>

jmp_buf	srbuf;


/*
 * The pointers for the string allocation routines,
 * there are NSPACE independent areas.
 * The first holds STRINGSIZE bytes, the next
 * twice as much, and so on.
 */

D 9
#define	NSPACE	8			/* Total number of string spaces */
E 9
I 9
#define	NSPACE	25			/* Total number of string spaces */
E 9
struct strings {
	char	*s_topFree;		/* Beginning of this area */
	char	*s_nextFree;		/* Next alloctable place here */
	unsigned s_nleft;		/* Number of bytes left here */
} stringdope[NSPACE];
E 1
