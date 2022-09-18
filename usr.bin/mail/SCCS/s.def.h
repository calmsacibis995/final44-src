h32356
s 00001/00001/00249
d D 8.4 95/04/20 09:59:11 dab 56 55
c Add support for "inc" command and "autoinc" variable.
c Recognize timestamps in From lines created by SysV/Solaris
c Recognize MAILRC env variable for .mailrc location
c Change tty handling from sgtty to termios
c Turn off EXTPROC when editing headers so that it works
c correctly with Linemode telnet.
e
s 00002/00002/00248
d D 8.3 94/10/25 16:36:31 edward 55 54
c increased m_block and m_lines to longs
c m_lines has been known to overflow
e
s 00004/00001/00246
d D 8.2 94/03/21 17:35:14 bostic 54 53
c ftruncate() now expands files.  the macro that 'mail' uses to truncate
c files has to fflush() them first, lest data in the buffer be appended (after
c the truncate).  The resulting behaviour is that nulls get written to the mbox
c file before the mail does.
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/00245
d D 8.1 93/06/06 15:07:31 bostic 53 52
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00063/00234
d D 5.23 92/06/26 12:03:09 bostic 52 51
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00001/00000/00296
d D 5.22 90/06/25 00:01:59 edward 51 50
c remove call of _fwalk
e
s 00001/00011/00295
d D 5.21 90/06/01 16:58:02 bostic 50 49
c new copyright notice
e
s 00001/00001/00305
d D 5.20 90/05/15 20:01:39 bostic 49 48
c string.h is ANSI C include file
e
s 00002/00001/00304
d D 5.19 89/05/11 09:44:07 bostic 48 47
c file reorg, pathnames.h, paths.h
e
s 00001/00000/00304
d D 5.18 88/08/17 14:44:43 edward 47 46
c bug report from gumkowsk@nadc.arpa (fix is my own),
c handle unmatched quotes correctly and make null string match no sender
e
s 00001/00000/00303
d D 5.17 88/08/09 17:57:54 edward 46 45
c DEAD added, mbox changed to MBOX
e
s 00000/00002/00303
d D 5.16 88/07/08 19:42:03 edward 45 44
c removed some functions in the C library
e
s 00003/00004/00302
d D 5.15 88/07/07 06:55:24 edward 44 43
c removed some unnecessary global vars, dynamically allocate some others,
c added spreserve to fix the no sreset when sourcing kludge
e
s 00004/00002/00302
d D 5.14 88/07/07 02:48:24 edward 43 42
c rationalized calling of editors and starting processes in general
e
s 00010/00005/00294
d D 5.13 88/06/29 21:01:35 bostic 42 41
c install approved copyright notice
e
s 00001/00008/00298
d D 5.12 88/06/29 19:03:43 edward 41 40
c popen to Popen, pclose to Pclose, never call a shell in popen
e
s 00006/00006/00300
d D 5.11 88/06/19 04:21:07 edward 40 39
c rationalized mail sending code: keep h_to, h_cc, h_bcc, h_smopts as lists
c not strings; h_seq deleted; now understands <...> addresses; and many more.
c should be much cleaner and somewhat faster.
e
s 00000/00001/00306
d D 5.10 88/06/17 15:39:02 edward 39 38
c some general cleanup
e
s 00001/00000/00306
d D 5.9 88/06/17 15:05:17 edward 38 37
c cleaned up file handling code, now allows "mbox" variable
e
s 00000/00001/00306
d D 5.8 88/06/16 17:41:27 edward 37 36
c prehistoric (e.g., pre-sendmail) code removed
e
s 00001/00000/00306
d D 5.7 88/06/11 01:15:56 edward 36 35
c added -c -b -t flags, end echo with newline,
c from Tom Newcomb (newcomb@arpa)
e
s 00006/00003/00300
d D 5.6 88/06/09 22:24:33 edward 35 34
c new commands saveignore, saveretain, and savediscard
e
s 00008/00002/00295
d D 5.5 88/02/18 17:03:46 bostic 34 33
c written by Kurt Shoens; added Berkeley specific header
e
s 00000/00001/00297
d D 5.4 87/10/22 18:13:00 bostic 33 32
c ANSI C; sprintf now returns an int.
e
s 00014/00047/00284
d D 5.3 87/05/18 12:28:27 edward 32 31
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00006/00006/00325
d D 5.2 85/11/02 17:48:51 serge 31 29
c increase several limits to be more realistic (from ks@purdue-ecn)
e
s 00006/00006/00325
d R 5.2 85/11/02 17:46:47 serge 30 29
c increase several limits to be more realistic
e
s 00007/00001/00324
d D 5.1 85/06/06 10:47:12 dist 29 28
c Add copyright
e
s 00001/00001/00324
d D 2.15 85/04/18 18:19:57 serge 28 27
c modified to work with new stdio; added retain command; fixed several bugs
e
s 00000/00001/00325
d D 2.14 85/01/09 10:07:35 ralph 27 26
c use sigmask() macro instead of defining twice.
e
s 00001/00005/00325
d D 2.13 83/08/11 22:14:52 sam 26 25
c standardize sccs keyword lines
e
s 00007/00000/00323
d D 2.12 83/06/15 13:26:49 sam 25 24
c merge leres code
e
s 00011/00000/00312
d D 2.11 83/06/12 11:16:52 sam 24 23
c new signals
e
s 00004/00002/00308
d D 2.10 83/01/29 18:20:59 leres 23 22
c Removed extra definition for savestr() and added strcat()
c strcpy(), and cmpdomain()
e
s 00001/00000/00309
d D 2.9 83/01/22 15:54:45 leres 22 21
c Added declaration of icequal();
e
s 00005/00002/00304
d D 2.8 82/10/21 05:54:43 carl 21 20
c Changes to support long mail sizes (long m_size).
c Inserted a null definition of sigchild() if SIGRETRO is undefined.
c Deleted declaration of msize().
c Changed declaration of transmit() to long.
e
s 00008/00000/00298
d D 2.7 82/07/28 23:12:34 kurt 20 19
c added hash structure (ignore) to remember list of ignored fields. 
c 
e
s 00001/00001/00297
d D 2.6 82/07/26 17:08:03 kurt 19 18
c moved include of local.h to after system files to fix 
c redefined problems in retrofit 
c 
e
s 00001/00001/00297
d D 2.5 82/06/24 23:54:43 kurt 18 17
c Expanded PATHSIZE to 100, a more reasonable size 
c 
e
s 00001/00001/00297
d D 2.4 81/12/10 12:55:21 kurt 17 16
c removed define constant SCREEN, previously used for paging 
c headers 
c 
e
s 00001/00001/00297
d D 2.3 81/09/16 14:35:08 kurt 16 15
c Corrected the comment on the "M" command table bit -- setting it makes 
c it LEGAL to exected from send mde 
c 
e
s 00001/00001/00297
d D 2.2 81/08/12 17:21:18 kurt 15 14
c changed definition of LINESIZE to also be BUFSIZ -- make lines as long
c as the editor can handle
e
s 00000/00000/00298
d D 2.1 81/07/01 11:11:10 kurt 14 13
c Release to Heidi Stettner
e
s 00001/00000/00297
d D 1.12 81/04/01 13:00:20 kurt 13 12
c added return type of sigset
e
s 00011/00010/00286
d D 1.11 81/03/20 15:31:58 kas 12 11
c added MBOX bit for message flags
e
s 00002/00000/00294
d D 1.10 81/03/11 15:56:26 kas 11 10
c added return types of skin, name1
e
s 00001/00000/00293
d D 1.9 81/01/26 10:33:38 kas 10 9
c > char	*reedit();
e
s 00001/00000/00292
d D 1.8 81/01/12 16:37:10 kas 9 8
c added flag R for non-recursive commands
e
s 00001/00001/00291
d D 1.7 81/01/05 18:13:01 kas 8 7
c changed conditional command flag from C to F
e
s 00011/00000/00281
d D 1.6 80/10/18 18:15:07 kas 7 6
c added command flags C == command is a conditional command and
c thus should always be executed and T == command is transparent and does
c not affect sawcom; defined conditional constants:  CANY -- execute in
c either send or receive mode and CRCV/CSEND -- execute only in send/receive
c mode
e
s 00001/00000/00280
d D 1.5 80/10/17 00:40:28 kas 6 5
c added return type declaration for popen()
e
s 00003/00000/00277
d D 1.4 80/10/16 18:50:47 kas 5 3
c added message flags:
c   MNEW -- message arrived since mail last run
c   MREAD -- message has been read since it arrived
c   MSTATUS -- one of MNEW, MREAD changed during this session
e
s 00002/00000/00277
d R 1.4 80/10/16 18:39:40 kas 4 3
c added message flags MNEW and MREAD -- these are determined
c from the header field Status: when the message is read in and updated
c on the way out.
e
s 00002/00000/00275
d D 1.3 80/10/09 13:43:51 kas 3 2
c added W flag for commands which cannot be executed in 
c read only mode
e
s 00001/00001/00274
d D 1.2 80/10/08 18:50:14 kas 2 1
c Increased STRINGLEN to cope with larger Arpanet names
e
s 00275/00000/00000
d D 1.1 80/10/08 09:53:34 kas 1 0
c date and time created 80/10/08 09:53:34 by kas
e
u
U
f b 
t
T
I 1
D 26
#
E 26
I 26
D 29
/*	%M%	%I%	%E%	*/
E 29
I 29
/*
D 53
 * Copyright (c) 1980 Regents of the University of California.
D 34
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 34
I 34
 * All rights reserved.
E 53
I 53
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 53
 *
D 50
 * Redistribution and use in source and binary forms are permitted
D 42
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 42
I 42
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
E 50
I 50
 * %sccs.include.redist.c%
E 50
E 42
E 34
 *
 *	%W% (Berkeley) %G%
 */
E 29
E 26

D 19
#include "local.h"
E 19
D 28
#include <sys/types.h>
E 28
I 28
D 52
#include <sys/param.h>		/* includes <sys/types.h> */
E 28
D 32
#include <signal.h>
E 32
I 32
#include <sys/signal.h>
E 32
#include <stdio.h>
I 17
#include <sgtty.h>
I 32
#include <ctype.h>
D 49
#include <strings.h>
E 49
I 49
#include <string.h>
E 49
E 32
I 19
D 48
#include "local.h"
E 48
I 48
#include "pathnames.h"
E 48
E 19
E 17

E 52
D 32
#undef isalpha
#undef isdigit
D 26

/*
 * Sccs Id = "%W% %G%";
 */
E 26

E 32
/*
 * Mail -- a mail program
 *
D 32
 * Commands are:
 *	t <message list>		print out these messages
 *	r <message list>		reply to messages
 *	m <user list>			mail to users (analogous to send)
 *	e <message list>		edit messages
 *	c [directory]			chdir to dir or home if none
 *	x				exit quickly
 *	w <message list> file		save messages in file
 *	q				quit, save remaining stuff in mbox
 *	d <message list>		delete messages
 *	u <message list>		undelete messages
 *	h				print message headers
 *
E 32
 * Author: Kurt Shoens (UCB) March 25, 1978
 */

I 52
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <signal.h>
D 56
#include <sgtty.h>
E 56
I 56
#include <termios.h>
E 56
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "pathnames.h"

E 52
I 48
#define	APPEND				/* New mail goes to end of mailbox */
E 48

#define	ESCAPE		'~'		/* Default escape for sending */
D 31
#define	NMLSIZE		20		/* max names in a message list */
D 18
#define	PATHSIZE	35		/* Size of pathnames throughout */
E 18
I 18
#define	PATHSIZE	100		/* Size of pathnames throughout */
E 18
#define	NAMESIZE	20		/* Max size of user name */
#define	HSHSIZE		19		/* Hash size for aliases and vars */
E 31
I 31
#define	NMLSIZE		1024		/* max names in a message list */
D 44
#define	PATHSIZE	1024		/* Size of pathnames throughout */
#define	NAMESIZE	32		/* Max size of user name */
E 44
I 44
#define	PATHSIZE	MAXPATHLEN	/* Size of pathnames throughout */
E 44
#define	HSHSIZE		59		/* Hash size for aliases and vars */
E 31
D 44
#define	HDRFIELDS	3		/* Number of header fields */
E 44
D 15
#define	LINESIZE	512		/* max readable line width */
E 15
I 15
#define	LINESIZE	BUFSIZ		/* max readable line width */
E 15
D 17
#define	SCREEN		18		/* screen size in lines (effective) */
E 17
#define	STRINGSIZE	((unsigned) 128)/* Dynamic allocation units */
D 31
#define	MAXARGC		20		/* Maximum list of raw strings */
E 31
I 31
#define	MAXARGC		1024		/* Maximum list of raw strings */
E 31
#define	NOSTR		((char *) 0)	/* Null string pointer */
#define	MAXEXP		25		/* Maximum expansion of aliases */
I 32

E 32
#define	equal(a, b)	(strcmp(a,b)==0)/* A nice function to string compare */

struct message {
	short	m_flag;			/* flags, see below */
D 55
	short	m_block;		/* block number of this message */
E 55
	short	m_offset;		/* offset in block of message */
I 55
	long	m_block;		/* block number of this message */
E 55
D 21
	unsigned	m_size;		/* Bytes in the message */
E 21
I 21
	long	m_size;			/* Bytes in the message */
E 21
D 55
	short	m_lines;		/* Lines in the message */
E 55
I 55
	long	m_lines;		/* Lines in the message */
E 55
};

/*
 * flag bits.
 */

D 12
#define	MUSED		1		/* entry is used, but this bit isn't */
#define	MDELETED	2		/* entry has been deleted */
#define	MSAVED		4		/* entry has been saved */
#define	MTOUCH		8		/* entry has been noticed */
#define	MPRESERVE	16		/* keep entry in sys mailbox */
#define	MMARK		32		/* message is marked! */
#define	MODIFY		64		/* message has been modified */
I 5
#define	MNEW		128		/* message has never been seen */
#define	MREAD		256		/* message has been read sometime. */
#define	MSTATUS		512		/* message status has changed */
E 12
I 12
#define	MUSED		(1<<0)		/* entry is used, but this bit isn't */
#define	MDELETED	(1<<1)		/* entry has been deleted */
#define	MSAVED		(1<<2)		/* entry has been saved */
#define	MTOUCH		(1<<3)		/* entry has been noticed */
#define	MPRESERVE	(1<<4)		/* keep entry in sys mailbox */
#define	MMARK		(1<<5)		/* message is marked! */
#define	MODIFY		(1<<6)		/* message has been modified */
#define	MNEW		(1<<7)		/* message has never been seen */
#define	MREAD		(1<<8)		/* message has been read sometime. */
#define	MSTATUS		(1<<9)		/* message status has changed */
#define	MBOX		(1<<10)		/* Send this to mbox, regardless */
E 12
E 5

/*
I 32
 * Given a file address, determine the block number it represents.
 */
#define blockof(off)			((int) ((off) / 4096))
#define offsetof(off)			((int) ((off) % 4096))
#define positionof(block, offset)	((off_t)(block) * 4096 + (offset))

/*
E 32
 * Format of the command description table.
 * The actual table is declared and initialized
 * in lex.c
 */
D 52

E 52
struct cmd {
	char	*c_name;		/* Name of command */
	int	(*c_func)();		/* Implementor of the command */
	short	c_argtype;		/* Type of arglist (see below) */
	short	c_msgflag;		/* Required flags of messages */
	short	c_msgmask;		/* Relevant flags of messages */
};

/* Yechh, can't initialize unions */

#define	c_minargs c_msgflag		/* Minimum argcount for RAWLIST */
#define	c_maxargs c_msgmask		/* Max argcount for RAWLIST */

/*
 * Argument types.
 */

#define	MSGLIST	 0		/* Message list type */
#define	STRLIST	 1		/* A pure string */
#define	RAWLIST	 2		/* Shell string list */
#define	NOLIST	 3		/* Just plain 0 */
#define	NDMLIST	 4		/* Message list, no defaults */

#define	P	040		/* Autoprint dot after command */
#define	I	0100		/* Interactive command bit */
D 16
#define	M	0200		/* Illegal from send mode bit */
E 16
I 16
#define	M	0200		/* Legal from send mode bit */
E 16
I 3
#define	W	0400		/* Illegal when read only bit */
I 7
D 8
#define	C	01000		/* Is a conditional command */
E 8
I 8
#define	F	01000		/* Is a conditional command */
E 8
#define	T	02000		/* Is a transparent command */
I 9
#define	R	04000		/* Cannot be called from collect */
E 9
E 7
E 3

/*
 * Oft-used mask values
 */

#define	MMNORM		(MDELETED|MSAVED)/* Look at both save and delete bits */
#define	MMNDEL		MDELETED	/* Look only at deleted bit */

/*
 * Structure used to return a break down of a head
 * line (hats off to Bill Joy!)
 */

struct headline {
	char	*l_from;	/* The name of the sender */
	char	*l_tty;		/* His tty string (if any) */
	char	*l_date;	/* The entire date string */
};

#define	GTO	1		/* Grab To: line */
#define	GSUBJECT 2		/* Likewise, Subject: line */
#define	GCC	4		/* And the Cc: line */
#define	GBCC	8		/* And also the Bcc: line */
#define	GMASK	(GTO|GSUBJECT|GCC|GBCC)
				/* Mask of places from whence */

#define	GNL	16		/* Print blank line after */
#define	GDEL	32		/* Entity removed from list */
#define	GCOMMA	64		/* detract puts in commas */

/*
 * Structure used to pass about the current
 * state of the user-typed message header.
 */

struct header {
D 40
	char	*h_to;			/* Dynamic "To:" string */
	char	*h_subject;		/* Subject string */
	char	*h_cc;			/* Carbon copies string */
	char	*h_bcc;			/* Blind carbon copies */
I 36
	char	*h_smopts;		/* Sendmail options */
E 36
	int	h_seq;			/* Sequence for optimization */
E 40
I 40
	struct name *h_to;		/* Dynamic "To:" string */
	char *h_subject;		/* Subject string */
	struct name *h_cc;		/* Carbon copies string */
	struct name *h_bcc;		/* Blind carbon copies */
	struct name *h_smopts;		/* Sendmail options */
E 40
};

/*
 * Structure of namelist nodes used in processing
 * the recipients of mail and aliases and all that
 * kind of stuff.
 */

struct name {
	struct	name *n_flink;		/* Forward link in list. */
	struct	name *n_blink;		/* Backward list link */
	short	n_type;			/* From which list it came */
	char	*n_name;		/* This fella's name */
};

/*
 * Structure of a variable node.  All variables are
 * kept on a singly-linked list of these, rooted by
 * "variables"
 */

struct var {
	struct	var *v_link;		/* Forward link to next variable */
	char	*v_name;		/* The variable's name */
	char	*v_value;		/* And it's current value */
};

struct group {
	struct	group *ge_link;		/* Next person in this group */
	char	*ge_name;		/* This person's user name */
};

struct grouphead {
	struct	grouphead *g_link;	/* Next grouphead in list */
	char	*g_name;		/* Name of this group */
	struct	group *g_list;		/* Users in group. */
};

#define	NIL	((struct name *) 0)	/* The nil pointer for namelists */
#define	NONE	((struct cmd *) 0)	/* The nil pointer to command tab */
#define	NOVAR	((struct var *) 0)	/* The nil pointer to variables */
#define	NOGRP	((struct grouphead *) 0)/* The nil grouphead pointer */
#define	NOGE	((struct group *) 0)	/* The nil group pointer */

/*
I 20
 * Structure of the hash table of ignored header fields
 */
D 35
struct ignore {
	struct ignore	*i_link;	/* Next ignored field in bucket */
	char		*i_field;	/* This ignored field */
E 35
I 35
struct ignoretab {
	int i_count;			/* Number of entries */
	struct ignore {
		struct ignore *i_link;	/* Next ignored field in bucket */
		char *i_field;		/* This ignored field */
	} *i_head[HSHSIZE];
E 35
};

/*
E 20
 * Token values returned by the scanner used for argument lists.
 * Also, sizes of scanner-related things.
 */

#define	TEOL	0			/* End of the command line */
#define	TNUMBER	1			/* A message number */
#define	TDASH	2			/* A simple dash */
#define	TSTRING	3			/* A string (possibly containing -) */
#define	TDOT	4			/* A "." */
#define	TUP	5			/* An "^" */
#define	TDOLLAR	6			/* A "$" */
#define	TSTAR	7			/* A "*" */
#define	TOPEN	8			/* An '(' */
#define	TCLOSE	9			/* A ')' */
#define TPLUS	10			/* A '+' */
I 47
#define TERROR	11			/* A lexical error */
E 47

#define	REGDEP	2			/* Maximum regret depth. */
D 2
#define	STRINGLEN	16		/* Maximum length of string token */
E 2
I 2
D 31
#define	STRINGLEN	64		/* Maximum length of string token */
E 31
I 31
#define	STRINGLEN	1024		/* Maximum length of string token */
E 31
I 7

/*
 * Constants for conditional commands.  These describe whether
 * we should be executing stuff or not.
 */

#define	CANY		0		/* Execute in send or receive mode */
#define	CRCV		1		/* Execute in receive mode only */
#define	CSEND		2		/* Execute in send mode only */
E 7
E 2

/*
 * Kludges to handle the change from setexit / reset to setjmp / longjmp
 */

#define	setexit()	setjmp(srbuf)
#define	reset(x)	longjmp(srbuf, x)

/*
D 32
 * VM/UNIX has a vfork system call which is faster than forking.  If we
 * don't have it, fork(2) will do . . .
 */

#ifndef VMUNIX
#define	vfork()	fork()
#endif
I 21
#ifndef	SIGRETRO
#define	sigchild()
#endif
E 21

/*
I 24
 * 4.2bsd signal interface help...
 */
#ifdef VMUNIX
#define	sigset(s, a)	signal(s, a)
D 27
#define	mask(s)		(1 << ((s) - 1))
E 27
#define	sigsys(s, a)	signal(s, a)
#endif

/*
E 32
I 25
 * Truncate a file to the last character written. This is
 * useful just before closing an old file that was opened
 * for read/write.
 */
D 54
#define trunc(stream)	ftruncate(fileno(stream), (long) ftell(stream))
E 54
I 54
#define trunc(stream) {							\
	(void)fflush(stream); 						\
	(void)ftruncate(fileno(stream), (long)ftell(stream));		\
}
E 54
D 52

/*
E 25
E 24
 * Forward declarations of routine types to keep lint and cc happy.
 */

I 51
FILE	*Fopen();
E 51
FILE	*Fdopen();
I 41
FILE	*Popen();
E 41
FILE	*collect();
FILE	*infix();
D 43
FILE	*mesedit();
FILE	*mespipe();
E 43
I 43
FILE	*run_editor();
E 43
I 6
D 41
FILE	*popen();
E 41
E 6
FILE	*setinput();
char	**unpack();
D 41
char	*addto();
char	*arpafix();
E 41
char	*calloc();
char	*copy();
char	*copyin();
char	*detract();
char	*expand();
I 46
char	*getdeadletter();
E 46
char	*gets();
char	*hfield();
D 32
char	*index();
E 32
I 11
char	*name1();
E 11
char	*nameof();
char	*nextword();
char	*getenv();
I 44
char	*getname();
E 44
I 43
char	*fgets();
E 43
I 3
D 39
char	*getfilename();
E 39
I 38
D 44
char	*findmail();
E 44
E 38
E 3
D 32
char	*hcontents();
E 32
I 32
char	*ishfield();
char	*malloc();
I 43
char	*mktemp();
E 43
E 32
D 41
char	*netmap();
char	*netname();
E 41
char	*readtty();
I 10
char	*reedit();
E 10
D 32
char	*rename();
E 32
D 41
char	*revarpa();
D 32
char	*rindex();
E 32
char	*rpair();
E 41
char	*salloc();
char	*savestr();
D 23
char	*savestr();
E 23
I 11
char	*skin();
E 11
char	*snarf();
I 44
char	*username();
E 44
I 23
D 32
char	*strcat();
char	*strcpy();
E 32
I 32
D 33
char	*sprintf();
E 33
E 32
E 23
char	*value();
char	*vcopy();
char	*yankword();
off_t	fsize();
I 43
uid_t	getuid();
E 43
I 24
D 32
#ifndef VMUNIX
E 24
I 13
int	(*sigset())();
I 24
#endif
E 32
E 24
I 22
D 23
int	icequal();
E 23
E 22
E 13
struct	cmd	*lex();
struct	grouphead	*findgroup();
I 40
struct	name	*nalloc();
E 40
struct	name	*cat();
struct	name	*delname();
struct	name	*elide();
struct	name	*extract();
struct	name	*gexpand();
D 41
struct	name	*map();
E 41
struct	name	*outof();
struct	name	*put();
struct	name	*usermap();
D 37
struct	name	*verify();
E 37
struct	var	*lookup();
E 52
D 21
unsigned	int	msize();
E 21
I 21
D 45
long	transmit();
I 23
int	icequal();
E 45
D 32
int	cmpdomain();
E 32
E 23
E 21
E 1
