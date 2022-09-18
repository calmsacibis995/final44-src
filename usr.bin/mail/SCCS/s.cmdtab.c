h42504
s 00001/00000/00091
d D 8.2 95/04/20 09:59:09 dab 34 33
c Add support for "inc" command and "autoinc" variable.
c Recognize timestamps in From lines created by SysV/Solaris
c Recognize MAILRC env variable for .mailrc location
c Change tty handling from sgtty to termios
c Turn off EXTPROC when editing headers so that it works
c correctly with Linemode telnet.
e
s 00002/00002/00089
d D 8.1 93/06/06 15:07:18 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00090
d D 5.12 92/06/26 12:03:06 bostic 32 31
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00001/00011/00100
d D 5.11 90/06/01 16:57:43 bostic 31 30
c new copyright notice
e
s 00002/00002/00109
d D 5.10 89/01/16 01:34:16 edward 30 29
c don't catch SIGCONT, catch the stop signals instead,
c cleaned up quitting of mail and signal catch in general,
c could use more work
e
s 00001/00005/00110
d D 5.9 88/07/07 22:57:08 edward 29 28
c got rid of unused command "local" and some undocumented command names
e
s 00005/00005/00110
d D 5.8 88/07/07 04:51:35 edward 28 27
c fixed up some command argument types
e
s 00012/00007/00103
d D 5.7 88/06/29 21:01:30 bostic 27 26
c install approved copyright notice
e
s 00004/00000/00106
d D 5.6 88/06/09 22:24:22 edward 26 25
c new commands saveignore, saveretain, and savediscard
e
s 00011/00005/00095
d D 5.5 88/02/18 17:03:36 bostic 25 24
c written by Kurt Shoens; added Berkeley specific header
e
s 00001/00001/00099
d D 5.4 87/05/18 12:28:25 edward 24 23
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00006/00000/00094
d D 5.3 85/09/15 17:13:13 serge 23 22
c added unread/Unread command
e
s 00001/00001/00093
d D 5.2 85/06/21 17:08:41 mckusick 22 21
c botched copyright
e
s 00008/00002/00086
d D 5.1 85/06/07 09:44:48 dist 21 20
c Add copyright
e
s 00005/00001/00083
d D 2.12 85/06/07 02:34:40 serge 20 19
c added "more" command
e
s 00003/00002/00081
d D 2.11 85/04/18 18:19:46 serge 19 18
c modified to work with new stdio; added retain command; fixed several bugs
e
s 00003/00003/00080
d D 2.10 83/08/11 22:14:04 sam 18 17
c standardize sccs keyword lines
e
s 00002/00001/00081
d D 2.9 83/01/29 18:23:58 leres 17 16
c Added local command
e
s 00005/00001/00077
d D 2.8 82/07/28 23:09:23 kurt 16 15
c added new commands Type, Print, ignore, and discard 
c 
e
s 00002/00000/00076
d D 2.7 82/02/14 19:49:58 kurt 15 14
c added entry for "folders" command -- list folders 
c 
e
s 00001/00000/00075
d D 2.6 82/02/14 19:27:12 kurt 14 13
c added command folder as a synonym for file 
c 
e
s 00002/00001/00073
d D 2.5 82/02/13 14:48:01 kurt 13 12
c added the "copy" command to copy messages into a file without 
c marking them with MSAVED. 
c 
e
s 00003/00003/00071
d D 2.4 81/10/26 20:09:14 kurt 12 11
c changed all references to exit() to rexit(), as they should be; 
c 
e
s 00002/00001/00072
d D 2.3 81/09/16 14:33:31 kurt 11 10
c added entry for new command "alternates" 
c 
e
s 00002/00001/00071
d D 2.2 81/09/09 11:18:57 kurt 10 9
c added command clobber
e
s 00000/00000/00072
d D 2.1 81/07/01 11:08:19 kurt 9 8
c Release to Heidi Stettner
e
s 00002/00002/00070
d D 1.8 81/03/20 15:26:58 kas 8 7
c mbox command now invokes function to set right bits
e
s 00004/00004/00068
d D 1.7 81/03/17 16:43:52 kas 7 6
c made conditional commands invokable while sending
e
s 00005/00005/00067
d D 1.6 81/01/12 16:27:35 kas 6 5
c Marked all mailing commands with R to prevent recursive invocation
e
s 00003/00003/00069
d D 1.5 81/01/05 17:32:38 kas 5 4
c changed the conditional command flag from C to F
e
s 00006/00002/00066
d D 1.4 80/10/18 18:11:39 kas 4 3
c added if/else/endif commands; marked file as "transparent"
c command which doesn't affect sawcom.
e
s 00002/00002/00066
d D 1.3 80/10/16 17:26:05 kas 3 2
c removed readonly restrictions from "edit" and "visual" --
c these commands now handle read only mode rationally
e
s 00010/00010/00058
d D 1.2 80/10/09 13:28:11 kas 2 1
c Changed parameters to "file" command to take an optional
c argument
e
s 00068/00000/00000
d D 1.1 80/10/08 09:49:30 kas 1 0
c date and time created 80/10/08 09:49:30 by kas
e
u
U
f b 
t
T
I 21
/*
D 33
 * Copyright (c) 1980 Regents of the University of California.
D 25
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 25
I 25
 * All rights reserved.
E 33
I 33
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 33
 *
D 31
 * Redistribution and use in source and binary forms are permitted
D 27
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 27
I 27
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
E 31
I 31
 * %sccs.include.redist.c%
E 31
E 27
E 25
 */

E 21
I 1
D 18
#
E 18
I 18
D 25
#ifndef lint
D 19
static char sccsid[] = "%W% (Berkeley) %G%";
E 19
I 19
D 21
static char *sccsid = "%W% (Berkeley) %G%";
E 19
#endif
E 21
I 21
D 22
static char sccsid[] = "%W% (Berkeley) %G%";
E 22
I 22
static char *sccsid = "%W% (Berkeley) %G%";
E 22
#endif not lint
E 25
I 25
D 27
#ifdef notdef
E 27
I 27
#ifndef lint
E 27
static char sccsid[] = "%W% (Berkeley) %G%";
D 27
#endif /* notdef */
E 27
I 27
#endif /* not lint */
E 27
E 25
E 21
E 18

#include "def.h"
I 32
#include "extern.h"
E 32

/*
 * Mail -- a mail program
 *
 * Define all of the command names and bindings.
 */
D 18

static char *SccsId = "%W% %G%";
E 18
D 32

extern int type(), preserve(), delete(), undelete(), next(), shell(), schdir();
D 24
extern int save(), help(), headers(), pdot(), strace(), respond(), editor();
E 24
I 24
extern int save(), help(), headers(), pdot(), respond(), editor();
E 24
D 12
extern int edstop(), exit(), pcmdlist(), sendmail(), from();
E 12
I 12
D 13
extern int edstop(), rexit(), pcmdlist(), sendmail(), from();
E 13
I 13
D 30
extern int edstop(), rexit(), pcmdlist(), sendmail(), from(), copycmd();
E 30
I 30
extern int quitcmd(), rexit(), pcmdlist(), sendmail(), from(), copycmd();
E 30
E 13
E 12
extern int messize(), psalloc(), deltype(), unset(), set(), source();
extern int pversion(), group(), top(), core(), null(), stouch(), visual();
D 4
extern int swrite(), dosh(), file(), echo(), Respond(), scroll();
E 4
I 4
extern int swrite(), dosh(), file(), echo(), Respond(), scroll(), ifcmd();
D 8
extern int elsecmd(), endifcmd();
E 8
I 8
D 10
extern int elsecmd(), endifcmd(), mboxit();
E 10
I 10
D 11
extern int elsecmd(), endifcmd(), mboxit(), clobber();
E 11
I 11
extern int elsecmd(), endifcmd(), mboxit(), clobber(), alternates();
I 15
D 16
extern int folders();
E 16
I 16
D 17
extern int folders(), igfield(), Type();
E 17
I 17
D 19
extern int local(), folders(), igfield(), Type();
E 19
I 19
D 20
extern int local(), folders(), igfield(), Type(), retfield();
E 20
I 20
D 29
extern int local(), folders(), igfield(), Type(), retfield(), more(), More();
E 29
I 29
extern int folders(), igfield(), Type(), retfield(), more(), More();
E 29
I 26
extern int saveigfield(), saveretfield();
E 26
I 23
extern int unread();	/* , Header(); */
E 32
E 23
E 20
E 19
E 17
E 16
E 15
E 11
E 10
E 8
E 4

struct cmd cmdtab[] = {
	"next",		next,		NDMLIST,	0,	MMNDEL,
	"alias",	group,		M|RAWLIST,	0,	1000,
	"print",	type,		MSGLIST,	0,	MMNDEL,
	"type",		type,		MSGLIST,	0,	MMNDEL,
I 16
	"Type",		Type,		MSGLIST,	0,	MMNDEL,
	"Print",	Type,		MSGLIST,	0,	MMNDEL,
E 16
D 2
	"visual",	visual,		I|MSGLIST,	0,	MMNORM,
E 2
I 2
D 3
	"visual",	visual,		W|I|MSGLIST,	0,	MMNORM,
E 3
I 3
	"visual",	visual,		I|MSGLIST,	0,	MMNORM,
E 3
E 2
	"top",		top,		MSGLIST,	0,	MMNDEL,
D 2
	"touch",	stouch,		MSGLIST,	0,	MMNDEL,
	"preserve",	preserve,	MSGLIST,	0,	MMNDEL,
	"delete",	delete,		P|MSGLIST,	0,	MMNDEL,
	"dp",		deltype,	MSGLIST,	0,	MMNDEL,
	"dt",		deltype,	MSGLIST,	0,	MMNDEL,
E 2
I 2
	"touch",	stouch,		W|MSGLIST,	0,	MMNDEL,
	"preserve",	preserve,	W|MSGLIST,	0,	MMNDEL,
	"delete",	delete,		W|P|MSGLIST,	0,	MMNDEL,
	"dp",		deltype,	W|MSGLIST,	0,	MMNDEL,
	"dt",		deltype,	W|MSGLIST,	0,	MMNDEL,
E 2
	"undelete",	undelete,	P|MSGLIST,	MDELETED,MMNDEL,
	"unset",	unset,		M|RAWLIST,	1,	1000,
D 6
	"mail",		sendmail,	M|I|STRLIST,	0,	0,
E 6
I 6
	"mail",		sendmail,	R|M|I|STRLIST,	0,	0,
E 6
D 2
	"mbox",		stouch,		MSGLIST,	0,	0,
E 2
I 2
D 8
	"mbox",		stouch,		W|MSGLIST,	0,	0,
E 8
I 8
	"mbox",		mboxit,		W|MSGLIST,	0,	0,
I 20
	"more",		more,		MSGLIST,	0,	MMNDEL,
	"page",		more,		MSGLIST,	0,	MMNDEL,
	"More",		More,		MSGLIST,	0,	MMNDEL,
	"Page",		More,		MSGLIST,	0,	MMNDEL,
I 23
	"unread",	unread,		MSGLIST,	0,	MMNDEL,
D 29
	"Unread",	unread,		MSGLIST,	0,	MMNDEL,
	"new",		unread,		MSGLIST,	0,	MMNDEL,
	"New",		unread,		MSGLIST,	0,	MMNDEL,
E 29
E 23
E 20
E 8
E 2
	"!",		shell,		I|STRLIST,	0,	0,
I 13
	"copy",		copycmd,	M|STRLIST,	0,	0,
E 13
D 28
	"chdir",	schdir,		M|STRLIST,	0,	0,
	"cd",		schdir,		M|STRLIST,	0,	0,
E 28
I 28
	"chdir",	schdir,		M|RAWLIST,	0,	1,
	"cd",		schdir,		M|RAWLIST,	0,	1,
E 28
	"save",		save,		STRLIST,	0,	0,
D 28
	"source",	source,		M|STRLIST,	0,	0,
E 28
I 28
	"source",	source,		M|RAWLIST,	1,	1,
E 28
	"set",		set,		M|RAWLIST,	0,	1000,
	"shell",	dosh,		I|NOLIST,	0,	0,
	"version",	pversion,	M|NOLIST,	0,	0,
	"group",	group,		M|RAWLIST,	0,	1000,
	"write",	swrite,		STRLIST,	0,	0,
	"from",		from,		MSGLIST,	0,	MMNORM,
D 2
	"file",		file,		M|NOLIST,	0,	0,
E 2
I 2
D 4
	"file",		file,		M|RAWLIST,	0,	1,
E 4
I 4
	"file",		file,		T|M|RAWLIST,	0,	1,
I 14
	"folder",	file,		T|M|RAWLIST,	0,	1,
I 15
D 28
	"folders",	folders,	T|M|RAWLIST,	0,	1,
E 28
I 28
	"folders",	folders,	T|M|NOLIST,	0,	0,
E 28
E 15
E 14
E 4
E 2
	"?",		help,		M|NOLIST,	0,	0,
	"z",		scroll,		M|STRLIST,	0,	0,
	"headers",	headers,	MSGLIST,	0,	MMNDEL,
	"help",		help,		M|NOLIST,	0,	0,
	"=",		pdot,		NOLIST,		0,	0,
D 6
	"Reply",	Respond,	I|MSGLIST,	0,	MMNDEL,
	"Respond",	Respond,	I|MSGLIST,	0,	MMNDEL,
	"reply",	respond,	I|MSGLIST,	0,	MMNDEL,
	"respond",	respond,	I|MSGLIST,	0,	MMNDEL,
E 6
I 6
	"Reply",	Respond,	R|I|MSGLIST,	0,	MMNDEL,
	"Respond",	Respond,	R|I|MSGLIST,	0,	MMNDEL,
	"reply",	respond,	R|I|MSGLIST,	0,	MMNDEL,
	"respond",	respond,	R|I|MSGLIST,	0,	MMNDEL,
E 6
D 2
	"edit",		editor,		I|MSGLIST,	0,	MMNORM,
E 2
I 2
D 3
	"edit",		editor,		W|I|MSGLIST,	0,	MMNORM,
E 3
I 3
	"edit",		editor,		I|MSGLIST,	0,	MMNORM,
E 3
E 2
D 7
	"echo",		echo,		RAWLIST,	0,	1000,
E 7
I 7
	"echo",		echo,		M|RAWLIST,	0,	1000,
E 7
D 28
	"quit",		edstop,		NOLIST, 	0,	0,
E 28
I 28
D 30
	"quit",		edstop,		NOLIST,		0,	0,
E 30
I 30
	"quit",		quitcmd,	NOLIST,		0,	0,
E 30
E 28
	"list",		pcmdlist,	M|NOLIST,	0,	0,
I 17
D 29
	"local",	local,		M|RAWLIST,	0,	1000,
E 29
E 17
D 12
	"xit",		exit,		M|NOLIST,	0,	0,
	"exit",		exit,		M|NOLIST,	0,	0,
E 12
I 12
	"xit",		rexit,		M|NOLIST,	0,	0,
	"exit",		rexit,		M|NOLIST,	0,	0,
E 12
	"size",		messize,	MSGLIST,	0,	MMNDEL,
D 2
	"hold",		preserve,	MSGLIST,	0,	MMNDEL,
E 2
I 2
	"hold",		preserve,	W|MSGLIST,	0,	MMNDEL,
I 4
D 5
	"if",		ifcmd,		C|RAWLIST,	1,	1,
	"else",		elsecmd,	C|RAWLIST,	0,	0,
	"endif",	endifcmd,	C|RAWLIST,	0,	0,
E 5
I 5
D 7
	"if",		ifcmd,		F|RAWLIST,	1,	1,
	"else",		elsecmd,	F|RAWLIST,	0,	0,
	"endif",	endifcmd,	F|RAWLIST,	0,	0,
E 7
I 7
	"if",		ifcmd,		F|M|RAWLIST,	1,	1,
	"else",		elsecmd,	F|M|RAWLIST,	0,	0,
	"endif",	endifcmd,	F|M|RAWLIST,	0,	0,
I 11
	"alternates",	alternates,	M|RAWLIST,	0,	1000,
I 16
	"ignore",	igfield,	M|RAWLIST,	0,	1000,
	"discard",	igfield,	M|RAWLIST,	0,	1000,
I 19
	"retain",	retfield,	M|RAWLIST,	0,	1000,
I 26
	"saveignore",	saveigfield,	M|RAWLIST,	0,	1000,
	"savediscard",	saveigfield,	M|RAWLIST,	0,	1000,
	"saveretain",	saveretfield,	M|RAWLIST,	0,	1000,
E 26
I 23
/*	"Header",	Header,		STRLIST,	0,	1000,	*/
E 23
E 19
E 16
E 11
E 7
E 5
E 4
E 2
	"core",		core,		M|NOLIST,	0,	0,
	"#",		null,		M|NOLIST,	0,	0,
I 10
	"clobber",	clobber,	M|RAWLIST,	0,	1,
I 34
	"inc",		inc,		T|NOLIST,	0,	0,
E 34
E 10
	0,		0,		0,		0,	0
};
E 1
