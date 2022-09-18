h00377
s 00002/00002/00502
d D 8.1 93/06/06 15:07:11 bostic 33 32
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00025/00011/00479
d D 5.15 92/06/26 12:03:03 bostic 32 31
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00003/00003/00487
d D 5.14 90/06/25 00:01:25 edward 31 30
c remove call of _fwalk
e
s 00001/00011/00489
d D 5.13 90/06/01 16:57:28 bostic 30 29
c new copyright notice
e
s 00002/00000/00498
d D 5.12 89/02/06 00:51:03 edward 29 28
c added return 0 to some commands
e
s 00004/00006/00494
d D 5.11 89/01/16 01:34:18 edward 28 27
c don't catch SIGCONT, catch the stop signals instead,
c cleaned up quitting of mail and signal catch in general,
c could use more work
e
s 00014/00020/00486
d D 5.10 88/07/08 19:41:48 edward 27 26
c removed some functions in the C library
e
s 00009/00010/00497
d D 5.9 88/07/08 01:43:23 edward 26 25
c rationalized handling of child processes, cleaned up mail1 some more
e
s 00011/00074/00496
d D 5.8 88/07/07 09:34:38 edward 25 24
c merged even more functionality into send()
e
s 00012/00007/00558
d D 5.7 88/06/29 21:01:23 bostic 24 23
c install approved copyright notice
e
s 00044/00073/00521
d D 5.6 88/06/09 22:24:23 edward 23 22
c new commands saveignore, saveretain, and savediscard
e
s 00011/00005/00583
d D 5.5 88/02/18 17:03:29 bostic 22 21
c written by Kurt Shoens; added Berkeley specific header
e
s 00013/00010/00575
d D 5.4 87/05/18 12:28:53 edward 21 20
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00006/00002/00579
d D 5.3 85/09/10 20:29:53 serge 20 19
c made the write command delete the entire header, instead of only the first line
e
s 00001/00001/00580
d D 5.2 85/06/21 17:07:00 mckusick 19 18
c botched copyright
e
s 00008/00002/00573
d D 5.1 85/06/06 10:22:25 dist 18 17
c Add copyright
e
s 00062/00001/00513
d D 2.13 85/04/18 18:20:34 serge 17 16
c modified to work with new stdio; added retain command; fixed several bugs
e
s 00002/00002/00512
d D 2.12 84/08/08 17:06:11 ralph 16 15
c fix stdio flushing, don't mess with stdio buffers
e
s 00003/00003/00511
d D 2.11 83/08/11 22:13:30 sam 15 14
c standardize sccs keyword lines
e
s 00006/00004/00508
d D 2.10 82/10/21 05:38:38 carl 14 13
c Changes to support long mail sizes (long m_size).
c Call to msize(x) replaced by the inline expansion x->m_size.
e
s 00001/00001/00511
d D 2.9 82/07/29 09:28:55 kurt 13 12
c changed alloca to salloc since no alloca on pdp-11's, generally 
c 
e
s 00030/00007/00482
d D 2.8 82/07/29 09:13:08 kurt 12 11
c changed to disallow duplicate insertion of fields into the ignore list; 
c changed igshow() to sort the ignored fields before printing them. 
c 
e
s 00046/00001/00443
d D 2.7 82/07/28 23:07:24 kurt 11 10
c added routine igfield() to add new header fields to the ignore list; 
c added routine igshow() to print out the list of ignored header fields. 
c 
e
s 00003/00003/00441
d D 2.6 82/07/28 15:31:32 kurt 10 9
c changed clobber1 to clob1 to satisfy pdp-11 c compiler name length 
c restriction. 
c 
e
s 00001/00000/00443
d D 2.5 82/07/26 17:06:01 kurt 9 8
c added call on sigchild() after a fork to fix up retrofit signals 
c 
e
s 00028/00005/00415
d D 2.4 82/02/13 14:43:28 kurt 8 7
c put most of the code to do the save command in save1(), which 
c can be called with an extra argument to control marking messages with MSAVED. 
c Added copycmd() which uses save1() to avoid MSAVED'ing messages. 
c 
e
s 00009/00003/00411
d D 2.3 81/10/13 20:50:37 kurt 7 6
c changed "dp" command to say "At EOF" when executed on last message 
c 
e
s 00030/00000/00384
d D 2.2 81/09/09 11:18:48 kurt 6 5
c added command clobber which recurses, clobbering the stack
c with 0xFF.  Thus, when you suspect that someone is relying on the stack
c area being zero, you can catch it
e
s 00000/00000/00384
d D 2.1 81/07/01 11:08:04 kurt 5 4
c Release to Heidi Stettner
e
s 00002/00002/00382
d D 1.4 81/03/20 15:23:23 kas 4 3
c changed delete to touch message and clear preserve and mbox bits
e
s 00001/00003/00383
d D 1.3 80/10/17 00:21:40 kas 3 2
c on the first next command, next() no longer sets dot to 1
c but rather leaves it alone!
e
s 00010/00004/00376
d D 1.2 80/10/16 17:24:49 kas 2 1
c fixed bug in next command -- given a list of messages, it would
c never ``find'' the first one, but always take the following one
e
s 00380/00000/00000
d D 1.1 80/10/08 09:49:20 kas 1 0
c date and time created 80/10/08 09:49:20 by kas
e
u
U
f b 
t
T
I 18
/*
D 33
 * Copyright (c) 1980 Regents of the University of California.
D 22
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 22
I 22
 * All rights reserved.
E 33
I 33
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 33
 *
D 30
 * Redistribution and use in source and binary forms are permitted
D 24
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 24
I 24
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
E 30
I 30
 * %sccs.include.redist.c%
E 30
E 24
E 22
 */

E 18
I 1
D 15
#
E 15
I 15
D 22
#ifndef lint
D 17
static char sccsid[] = "%W% (Berkeley) %G%";
E 17
I 17
D 18
static char *sccsid = "%W% (Berkeley) %G%";
E 17
#endif
E 18
I 18
D 19
static char sccsid[] = "%W% (Berkeley) %G%";
E 19
I 19
static char *sccsid = "%W% (Berkeley) %G%";
E 19
#endif not lint
E 22
I 22
D 24
#ifdef notdef
E 24
I 24
#ifndef lint
E 24
static char sccsid[] = "%W% (Berkeley) %G%";
D 24
#endif /* notdef */
E 24
I 24
#endif /* not lint */
E 24
E 22
E 18
E 15

#include "rcv.h"
D 25
#include <sys/stat.h>
E 25
I 21
#include <sys/wait.h>
I 32
#include "extern.h"
E 32
E 21

/*
 * Mail -- a mail program
 *
 * More user commands.
 */
D 15

static char *SccsId = "%W% %G%";
E 15

/*
 * If any arguments were given, go to the next applicable argument
 * following dot, otherwise, go to the next applicable message.
 * If given as first command with no arguments, print first message.
 */
D 32

E 32
I 32
int
E 32
next(msgvec)
	int *msgvec;
{
	register struct message *mp;
	register int *ip, *ip2;
	int list[2], mdot;

	if (*msgvec != NULL) {

		/*
		 * If some messages were supplied, find the 
		 * first applicable one following dot using
		 * wrap around.
		 */

		mdot = dot - &message[0] + 1;
I 2

		/*
		 * Find the first message in the supplied
		 * message list which follows dot.
		 */

E 2
		for (ip = msgvec; *ip != NULL; ip++)
			if (*ip > mdot)
				break;
		if (*ip == NULL)
			ip = msgvec;
		ip2 = ip;
		do {
D 2
			if (*ip2 != NULL)
				ip2++;
			if (*ip2 == NULL)
				ip2 = msgvec;
E 2
			mp = &message[*ip2 - 1];
			if ((mp->m_flag & MDELETED) == 0) {
				dot = mp;
				goto hitit;
			}
I 2
			if (*ip2 != NULL)
				ip2++;
			if (*ip2 == NULL)
				ip2 = msgvec;
E 2
		} while (ip2 != ip);
		printf("No messages applicable\n");
		return(1);
	}

	/*
	 * If this is the first command, select message 1.
	 * Note that this must exist for us to get here at all.
	 */

D 3
	if (!sawcom) {
		dot = &message[0];
E 3
I 3
	if (!sawcom)
E 3
		goto hitit;
D 3
	}
E 3

	/*
	 * Just find the next good message after dot, no
	 * wraparound.
	 */

	for (mp = dot+1; mp < &message[msgCount]; mp++)
		if ((mp->m_flag & (MDELETED|MSAVED)) == 0)
			break;
	if (mp >= &message[msgCount]) {
		printf("At EOF\n");
		return(0);
	}
	dot = mp;
hitit:
	/*
	 * Print dot.
	 */

	list[0] = dot - &message[0] + 1;
	list[1] = NULL;
	return(type(list));
}

/*
D 8
 * Save the indicated messages at the end of the passed file name.
E 8
I 8
 * Save a message in a file.  Mark the message as saved
 * so we can discard when the user quits.
E 8
 */
I 32
int
E 32
D 8

E 8
save(str)
	char str[];
{
I 8

D 25
	return(save1(str, 1));
E 25
I 25
	return save1(str, 1, "save", saveignore);
E 25
}

/*
 * Copy a message to a file without affected its saved-ness
 */
I 32
int
E 32
copycmd(str)
	char str[];
{

D 25
	return(save1(str, 0));
E 25
I 25
	return save1(str, 0, "copy", saveignore);
E 25
}

/*
 * Save/copy the indicated messages at the end of the passed file name.
 * If mark is true, mark the message "saved."
 */
I 32
int
E 32
D 25
save1(str, mark)
E 25
I 25
save1(str, mark, cmd, ignore)
E 25
	char str[];
I 32
	int mark;
E 32
I 25
	char *cmd;
	struct ignoretab *ignore;
E 25
{
E 8
D 27
	register int *ip, mesg;
E 27
I 27
	register int *ip;
E 27
	register struct message *mp;
D 8
	char *file, *disp;
E 8
I 8
D 25
	char *file, *disp, *cmd;
E 8
D 14
	int f, *msgvec, lc, cc, t;
E 14
I 14
	int f, *msgvec, lc, t;
	long cc;
E 25
I 25
	char *file, *disp;
	int f, *msgvec;
E 25
E 14
	FILE *obuf;
D 25
	struct stat statb;
E 25

I 8
D 25
	cmd = mark ? "save" : "copy";
E 25
E 8
	msgvec = (int *) salloc((msgCount + 2) * sizeof *msgvec);
	if ((file = snarf(str, &f)) == NOSTR)
		return(1);
	if (!f) {
		*msgvec = first(0, MMNORM);
		if (*msgvec == NULL) {
D 8
			printf("No messages to save.\n");
E 8
I 8
			printf("No messages to %s.\n", cmd);
E 8
			return(1);
		}
		msgvec[1] = NULL;
	}
	if (f && getmsglist(str, msgvec, 0) < 0)
		return(1);
	if ((file = expand(file)) == NOSTR)
		return(1);
	printf("\"%s\" ", file);
D 16
	flush();
E 16
I 16
	fflush(stdout);
E 16
D 25
	if (stat(file, &statb) >= 0)
E 25
I 25
	if (access(file, 0) >= 0)
E 25
		disp = "[Appended]";
	else
		disp = "[New file]";
D 31
	if ((obuf = fopen(file, "a")) == NULL) {
E 31
I 31
	if ((obuf = Fopen(file, "a")) == NULL) {
E 31
		perror(NOSTR);
		return(1);
	}
D 14
	cc = lc = 0;
E 14
I 14
D 25
	cc = 0L;
	lc = 0;
E 25
E 14
	for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++) {
D 27
		mesg = *ip;
		touch(mesg);
		mp = &message[mesg-1];
E 27
I 27
		mp = &message[*ip - 1];
		touch(mp);
E 27
D 11
		if ((t = send(mp, obuf)) < 0) {
E 11
I 11
D 23
		if ((t = send(mp, obuf, 0)) < 0) {
E 23
I 23
D 25
		if ((t = send(mp, obuf, saveignore)) < 0) {
E 25
I 25
		if (send(mp, obuf, ignore, NOSTR) < 0) {
E 25
E 23
E 11
			perror(file);
D 31
			fclose(obuf);
E 31
I 31
			Fclose(obuf);
E 31
			return(1);
		}
D 25
		lc += t;
D 14
		cc += msize(mp);
E 14
I 14
		cc += mp->m_size;
E 25
E 14
D 8
		mp->m_flag |= MSAVED;
E 8
I 8
		if (mark)
			mp->m_flag |= MSAVED;
E 8
	}
	fflush(obuf);
	if (ferror(obuf))
		perror(file);
D 31
	fclose(obuf);
E 31
I 31
	Fclose(obuf);
E 31
D 14
	printf("%s %d/%d\n", disp, lc, cc);
E 14
I 14
D 25
	printf("%s %d/%ld\n", disp, lc, cc);
E 25
I 25
	printf("%s\n", disp);
E 25
E 14
	return(0);
}

/*
 * Write the indicated messages at the end of the passed
 * file name, minus header and trailing blank line.
 */
D 32

E 32
I 32
int
E 32
swrite(str)
	char str[];
{
D 25
	register int *ip, mesg;
	register struct message *mp;
	register char *file, *disp;
	char linebuf[BUFSIZ];
	int f, *msgvec, lc, cc, t;
	FILE *obuf, *mesf;
	struct stat statb;
E 25

D 25
	msgvec = (int *) salloc((msgCount + 2) * sizeof *msgvec);
	if ((file = snarf(str, &f)) == NOSTR)
		return(1);
	if ((file = expand(file)) == NOSTR)
		return(1);
	if (!f) {
		*msgvec = first(0, MMNORM);
		if (*msgvec == NULL) {
			printf("No messages to write.\n");
			return(1);
		}
		msgvec[1] = NULL;
	}
	if (f && getmsglist(str, msgvec, 0) < 0)
		return(1);
	printf("\"%s\" ", file);
D 16
	flush();
E 16
I 16
	fflush(stdout);
E 16
	if (stat(file, &statb) >= 0)
		disp = "[Appended]";
	else
		disp = "[New file]";
	if ((obuf = fopen(file, "a")) == NULL) {
		perror(NOSTR);
		return(1);
	}
	cc = lc = 0;
	for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++) {
		mesg = *ip;
		touch(mesg);
		mp = &message[mesg-1];
		mesf = setinput(mp);
D 20
		t = mp->m_lines - 2;
		readline(mesf, linebuf);
E 20
I 20
		t = mp->m_lines - 1;
		while (t-- > 0) {
			readline(mesf, linebuf);
			if (blankline(linebuf))
				break;
		}
E 20
		while (t-- > 0) {
			fgets(linebuf, BUFSIZ, mesf);
			fputs(linebuf, obuf);
			cc += strlen(linebuf);
		}
		lc += mp->m_lines - 2;
		mp->m_flag |= MSAVED;
	}
	fflush(obuf);
	if (ferror(obuf))
		perror(file);
	fclose(obuf);
	printf("%s %d/%d\n", disp, lc, cc);
	return(0);
E 25
I 25
	return save1(str, 1, "write", ignoreall);
E 25
}

/*
 * Snarf the file from the end of the command line and
 * return a pointer to it.  If there is no file attached,
 * just return NOSTR.  Put a null in front of the file
 * name so that the message list processing won't see it,
 * unless the file name is the only thing on the line, in
 * which case, return 0 in the reference flag variable.
 */

char *
snarf(linebuf, flag)
	char linebuf[];
	int *flag;
{
	register char *cp;

	*flag = 1;
	cp = strlen(linebuf) + linebuf - 1;

	/*
	 * Strip away trailing blanks.
	 */

D 21
	while (*cp == ' ' && cp > linebuf)
E 21
I 21
	while (cp > linebuf && isspace(*cp))
E 21
		cp--;
	*++cp = 0;

	/*
	 * Now search for the beginning of the file name.
	 */

D 21
	while (cp > linebuf && !any(*cp, "\t "))
E 21
I 21
	while (cp > linebuf && !isspace(*cp))
E 21
		cp--;
	if (*cp == '\0') {
		printf("No file specified.\n");
		return(NOSTR);
	}
D 21
	if (any(*cp, " \t"))
E 21
I 21
	if (isspace(*cp))
E 21
		*cp++ = 0;
	else
		*flag = 0;
	return(cp);
}

/*
 * Delete messages.
 */
D 32

E 32
I 32
int
E 32
delete(msgvec)
	int msgvec[];
{
D 28
	return(delm(msgvec));
E 28
I 28
	delm(msgvec);
	return 0;
E 28
}

/*
 * Delete messages, then type the new dot.
 */
D 32

E 32
I 32
int
E 32
deltype(msgvec)
	int msgvec[];
{
	int list[2];
I 7
	int lastdot;
E 7

I 7
	lastdot = dot - &message[0] + 1;
E 7
	if (delm(msgvec) >= 0) {
D 27
		list[0] = dot - &message[0];
		list[0]++;
E 27
I 27
		list[0] = dot - &message[0] + 1;
E 27
D 7
		touch(list[0]);
		list[1] = NULL;
		return(type(list));
E 7
I 7
		if (list[0] > lastdot) {
D 27
			touch(list[0]);
E 27
I 27
			touch(dot);
E 27
			list[1] = NULL;
			return(type(list));
		}
		printf("At EOF\n");
D 28
		return(0);
E 7
	}
	else {
E 28
I 28
	} else
E 28
		printf("No more messages\n");
D 28
		return(0);
	}
E 28
I 28
	return(0);
E 28
}

/*
 * Delete the indicated messages.
 * Set dot to some nice place afterwards.
 * Internal interface.
 */
D 32

E 32
I 32
int
E 32
delm(msgvec)
	int *msgvec;
{
	register struct message *mp;
D 27
	register *ip, mesg;
E 27
I 27
	register *ip;
E 27
	int last;

	last = NULL;
	for (ip = msgvec; *ip != NULL; ip++) {
D 27
		mesg = *ip;
		touch(mesg);
		mp = &message[mesg-1];
E 27
I 27
		mp = &message[*ip - 1];
		touch(mp);
E 27
D 4
		mp->m_flag |= MDELETED;
		mp->m_flag &= ~(MPRESERVE|MSAVED);
E 4
I 4
		mp->m_flag |= MDELETED|MTOUCH;
		mp->m_flag &= ~(MPRESERVE|MSAVED|MBOX);
E 4
D 27
		last = mesg;
E 27
I 27
		last = *ip;
E 27
	}
	if (last != NULL) {
		dot = &message[last-1];
		last = first(0, MDELETED);
		if (last != NULL) {
			dot = &message[last-1];
			return(0);
		}
		else {
			dot = &message[0];
			return(-1);
		}
	}

	/*
	 * Following can't happen -- it keeps lint happy
	 */

	return(-1);
}

/*
 * Undelete the indicated messages.
 */
D 32

E 32
I 32
int
E 32
undelete(msgvec)
	int *msgvec;
{
	register struct message *mp;
D 27
	register *ip, mesg;
E 27
I 27
	register *ip;
E 27

D 27
	for (ip = msgvec; ip-msgvec < msgCount; ip++) {
		mesg = *ip;
		if (mesg == 0)
			return;
		touch(mesg);
		mp = &message[mesg-1];
E 27
I 27
	for (ip = msgvec; *ip && ip-msgvec < msgCount; ip++) {
		mp = &message[*ip - 1];
		touch(mp);
E 27
		dot = mp;
		mp->m_flag &= ~MDELETED;
	}
I 29
	return 0;
E 29
}

/*
 * Interactively dump core on "core"
 */
D 32

E 32
I 32
int
E 32
core()
{
D 26
	register int pid;
D 21
	int status;
E 21
I 21
	union wait status;
E 26
I 26
	int pid;
	extern union wait wait_status;
E 26
E 21

D 26
	if ((pid = vfork()) == -1) {
E 26
I 26
	switch (pid = vfork()) {
	case -1:
E 26
		perror("fork");
		return(1);
D 26
	}
	if (pid == 0) {
E 26
I 26
	case 0:
E 26
I 9
D 21
		sigchild();
E 21
E 9
		abort();
		_exit(1);
	}
	printf("Okie dokie");
	fflush(stdout);
D 26
	while (wait(&status) != pid)
		;
D 21
	if (status & 0200)
E 21
I 21
	if (status.w_coredump)
E 21
		printf(" -- Core dumped\n");
E 26
I 26
	wait_child(pid);
	if (wait_status.w_coredump)
		printf(" -- Core dumped.\n");
E 26
	else
D 26
		printf("\n");
E 26
I 26
		printf(" -- Can't dump core.\n");
E 26
I 21
	return 0;
E 21
}
I 6

/*
 * Clobber as many bytes of stack as the user requests.
 */
I 32
int
E 32
clobber(argv)
	char **argv;
{
	register int times;

	if (argv[0] == 0)
		times = 1;
	else
		times = (atoi(argv[0]) + 511) / 512;
D 10
	clobber1(times);
E 10
I 10
	clob1(times);
I 29
	return 0;
E 29
E 10
}

/*
 * Clobber the stack.
 */
I 32
void
E 32
D 10
clobber1(n)
E 10
I 10
clob1(n)
I 32
	int n;
E 32
E 10
{
	char buf[512];
	register char *cp;

	if (n <= 0)
		return;
	for (cp = buf; cp < &buf[512]; *cp++ = 0xFF)
		;
D 10
	clobber1(n - 1);
E 10
I 10
	clob1(n - 1);
I 17
}

/*
 * Add the given header fields to the retained list.
 * If no arguments, print the current list of retained fields.
 */
I 32
int
E 32
retfield(list)
	char *list[];
{
D 23
	char field[BUFSIZ];
	register int h;
	register struct ignore *igp;
	char **ap;
E 23

D 23
	if (argcount(list) == 0)
		return(retshow());
	for (ap = list; *ap != 0; ap++) {
		istrcpy(field, *ap);

		if (member(field, retain))
			continue;

		h = hash(field);
		igp = (struct ignore *) calloc(1, sizeof (struct ignore));
D 21
		igp->i_field = calloc(strlen(field) + 1, sizeof (char));
E 21
I 21
		igp->i_field = calloc((unsigned) strlen(field) + 1,
			sizeof (char));
E 21
		strcpy(igp->i_field, field);
		igp->i_link = retain[h];
		retain[h] = igp;
		nretained++;
	}
	return(0);
E 23
I 23
	return ignore1(list, ignore + 1, "retained");
E 23
}

/*
D 23
 * Print out all currently retained fields.
E 23
I 23
 * Add the given header fields to the ignored list.
 * If no arguments, print the current list of ignored fields.
E 23
 */
I 32
int
E 32
D 23
retshow()
E 23
I 23
igfield(list)
	char *list[];
E 23
{
D 23
	register int h, count;
	struct ignore *igp;
	char **ap, **ring;
	int igcomp();
E 23

D 23
	count = 0;
	for (h = 0; h < HSHSIZE; h++)
		for (igp = retain[h]; igp != 0; igp = igp->i_link)
			count++;
	if (count == 0) {
		printf("No fields currently being retained.\n");
		return(0);
	}
	ring = (char **) salloc((count + 1) * sizeof (char *));
	ap = ring;
	for (h = 0; h < HSHSIZE; h++)
		for (igp = retain[h]; igp != 0; igp = igp->i_link)
			*ap++ = igp->i_field;
	*ap = 0;
D 21
	qsort(ring, count, sizeof (char *), igcomp);
E 21
I 21
	qsort((char *) ring, count, sizeof (char *), igcomp);
E 21
	for (ap = ring; *ap != 0; ap++)
		printf("%s\n", *ap);
	return(0);
E 23
I 23
	return ignore1(list, ignore, "ignored");
E 23
E 17
I 11
}

I 32
int
E 32
D 23
/*
 * Add the given header fields to the ignored list.
 * If no arguments, print the current list of ignored fields.
 */
igfield(list)
E 23
I 23
saveretfield(list)
E 23
	char *list[];
{
I 23

	return ignore1(list, saveignore + 1, "retained");
}

I 32
int
E 32
saveigfield(list)
	char *list[];
{

	return ignore1(list, saveignore, "ignored");
}

I 32
int
E 32
ignore1(list, tab, which)
	char *list[];
	struct ignoretab *tab;
	char *which;
{
E 23
	char field[BUFSIZ];
	register int h;
	register struct ignore *igp;
	char **ap;

D 27
	if (argcount(list) == 0)
E 27
I 27
	if (*list == NOSTR)
E 27
D 23
		return(igshow());
E 23
I 23
		return igshow(tab, which);
E 23
	for (ap = list; *ap != 0; ap++) {
I 12
D 23
		if (isign(*ap))
			continue;
E 23
E 12
		istrcpy(field, *ap);
I 23
		if (member(field, tab))
			continue;
E 23
		h = hash(field);
		igp = (struct ignore *) calloc(1, sizeof (struct ignore));
D 21
		igp->i_field = calloc(strlen(field) + 1, sizeof (char));
E 21
I 21
		igp->i_field = calloc((unsigned) strlen(field) + 1,
			sizeof (char));
E 21
		strcpy(igp->i_field, field);
D 23
		igp->i_link = ignore[h];
		ignore[h] = igp;
E 23
I 23
		igp->i_link = tab->i_head[h];
		tab->i_head[h] = igp;
		tab->i_count++;
E 23
	}
D 23
	return(0);
E 23
I 23
	return 0;
E 23
}

/*
D 23
 * Print out all currently ignored fields.
E 23
I 23
 * Print out all currently retained fields.
E 23
 */
I 32
int
E 32
D 23
igshow()
E 23
I 23
igshow(tab, which)
	struct ignoretab *tab;
	char *which;
E 23
{
D 12
	register int h, did;
E 12
I 12
D 23
	register int h, count;
E 23
I 23
	register int h;
E 23
E 12
	struct ignore *igp;
I 12
	char **ap, **ring;
	int igcomp();
E 12

D 12
	did = 0;
E 12
I 12
D 23
	count = 0;
E 12
	for (h = 0; h < HSHSIZE; h++)
D 12
		for (igp = ignore[h]; igp != 0; igp = igp->i_link) {
			printf("%s\n", igp->i_field);
			did++;
		}
	if (!did)
E 12
I 12
		for (igp = ignore[h]; igp != 0; igp = igp->i_link)
			count++;
	if (count == 0) {
E 12
		printf("No fields currently being ignored.\n");
I 12
		return(0);
E 23
I 23
	if (tab->i_count == 0) {
		printf("No fields currently being %s.\n", which);
		return 0;
E 23
	}
D 13
	ring = (char **) alloca((count + 1) * sizeof (char *));
E 13
I 13
D 23
	ring = (char **) salloc((count + 1) * sizeof (char *));
E 23
I 23
	ring = (char **) salloc((tab->i_count + 1) * sizeof (char *));
E 23
E 13
	ap = ring;
	for (h = 0; h < HSHSIZE; h++)
D 23
		for (igp = ignore[h]; igp != 0; igp = igp->i_link)
E 23
I 23
		for (igp = tab->i_head[h]; igp != 0; igp = igp->i_link)
E 23
			*ap++ = igp->i_field;
	*ap = 0;
D 21
	qsort(ring, count, sizeof (char *), igcomp);
E 21
I 21
D 23
	qsort((char *) ring, count, sizeof (char *), igcomp);
E 23
I 23
D 32
	qsort((char *) ring, tab->i_count, sizeof (char *), igcomp);
E 32
I 32
	qsort(ring, tab->i_count, sizeof (char *), igcomp);
E 32
E 23
E 21
	for (ap = ring; *ap != 0; ap++)
		printf("%s\n", *ap);
E 12
D 23
	return(0);
E 23
I 23
	return 0;
E 23
I 12
}

/*
 * Compare two names for sorting ignored field list.
 */
I 32
int
E 32
igcomp(l, r)
D 32
	char **l, **r;
E 32
I 32
	const void *l, *r;
E 32
{
D 32

D 23
	return(strcmp(*l, *r));
E 23
I 23
	return strcmp(*l, *r);
E 32
I 32
	return (strcmp(*(char **)l, *(char **)r));
E 32
E 23
E 12
E 11
E 10
}
E 6
E 1
