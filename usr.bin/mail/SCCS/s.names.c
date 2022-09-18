h65356
s 00002/00002/00666
d D 8.1 93/06/06 15:08:18 bostic 30 29
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00667
d D 5.18 92/09/20 08:41:36 edward 29 28
c use close-on-exec and some other stuff to get rid of dtablesize dependency
e
s 00009/00000/00658
d D 5.17 92/06/26 12:03:20 bostic 28 27
c quad's broke it -- prototyped it rather than figure out the problem
e
s 00029/00019/00629
d D 5.16 90/06/25 00:01:12 edward 27 26
c remove call of _fwalk
e
s 00001/00011/00647
d D 5.15 90/06/01 16:59:38 bostic 26 25
c new copyright notice
e
s 00001/00001/00657
d D 5.14 89/05/11 09:44:16 bostic 25 24
c file reorg, pathnames.h, paths.h
e
s 00009/00026/00649
d D 5.13 88/07/08 19:41:38 edward 24 23
c removed some functions in the C library
e
s 00017/00042/00658
d D 5.12 88/07/08 01:43:20 edward 23 22
c rationalized handling of child processes, cleaned up mail1 some more
e
s 00007/00019/00693
d D 5.11 88/07/07 02:48:07 edward 22 21
c rationalized calling of editors and starting processes in general
e
s 00012/00007/00700
d D 5.10 88/06/29 21:01:58 bostic 21 20
c install approved copyright notice
e
s 00034/00087/00673
d D 5.9 88/06/19 04:20:49 edward 20 19
c rationalized mail sending code: keep h_to, h_cc, h_bcc, h_smopts as lists
c not strings; h_seq deleted; now understands <...> addresses; and many more.
c should be much cleaner and somewhat faster.
e
s 00001/00032/00759
d D 5.8 88/06/18 14:54:13 edward 19 18
c removed support for -r, -h, and rmail
e
s 00005/00078/00786
d D 5.7 88/06/16 17:40:50 edward 18 17
c prehistoric (e.g., pre-sendmail) code removed
e
s 00011/00005/00853
d D 5.6 88/02/18 17:04:09 bostic 17 16
c written by Kurt Shoens; added Berkeley specific header
e
s 00024/00026/00834
d D 5.5 87/05/18 13:04:54 edward 16 15
c lint
e
s 00018/00023/00842
d D 5.4 87/05/18 12:28:16 edward 15 14
c major rework: made faster, cleaned up, obsolete code removed,
c the whole thing should be chucked and written from scratch
e
s 00017/00006/00848
d D 5.3 85/11/10 01:19:04 serge 14 13
c fix infinite loop bug in yankword()
e
s 00001/00001/00853
d D 5.2 85/06/21 17:12:36 mckusick 13 12
c botched copyright
e
s 00007/00001/00847
d D 5.1 85/06/06 10:38:30 dist 12 11
c Add copyright
e
s 00003/00003/00845
d D 2.9 83/08/11 22:18:09 sam 11 10
c standardize sccs keyword lines
e
s 00021/00004/00827
d D 2.8 83/01/22 15:35:21 leres 10 9
c Modified delname() to use passed function to comapre name strings.
c Added cmpdomain() and support for verbose command/option.
e
s 00005/00005/00826
d D 2.7 82/12/26 21:16:11 eric 9 8
c change delivermail to sendmail throughout
e
s 00001/00000/00830
d D 2.6 82/07/26 17:10:03 kurt 8 7
c added call on sigchild() after fork() to fix retrofit signals 
c 
e
s 00002/00000/00828
d D 2.5 82/02/26 08:03:32 kurt 7 6
c changed isfileaddr() to think that names that begin with + 
c are file addresses. 
c 
e
s 00002/00003/00826
d D 2.4 81/09/16 14:34:01 kurt 6 5
c changed code in delname to ignore case when searching for 
c name to delete 
c 
e
s 00025/00001/00804
d D 2.3 81/09/10 19:34:37 kurt 5 4
c changed outof to be more careful about declaring an address
c to be that of a unix file:  it now knows that the address can be on
c another machine
e
s 00001/00004/00804
d D 2.2 81/08/19 17:50:23 kurt 4 3
c fixed name handling in unpack() to leave leading \'s in a name so that
c sendmail can see it
e
s 00000/00000/00808
d D 2.1 81/07/01 11:09:54 kurt 3 2
c Release to Heidi Stettner
e
s 00003/00003/00805
d D 1.2 81/04/01 12:58:39 kurt 2 1
c changed calls on signal to sigsys
e
s 00808/00000/00000
d D 1.1 80/10/08 09:50:55 kas 1 0
c date and time created 80/10/08 09:50:55 by kas
e
u
U
f b 
t
T
I 12
/*
D 30
 * Copyright (c) 1980 Regents of the University of California.
D 17
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 17
I 17
 * All rights reserved.
E 30
I 30
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 30
 *
D 26
 * Redistribution and use in source and binary forms are permitted
D 21
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 21
I 21
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
E 26
I 26
 * %sccs.include.redist.c%
E 26
E 21
E 17
 */

E 12
I 1
D 11
#
E 11
I 11
D 17
#ifndef lint
D 13
static char sccsid[] = "%W% (Berkeley) %G%";
E 13
I 13
static char *sccsid = "%W% (Berkeley) %G%";
E 13
D 12
#endif
E 12
I 12
#endif not lint
E 17
I 17
D 21
#ifdef notdef
E 21
I 21
#ifndef lint
E 21
static char sccsid[] = "%W% (Berkeley) %G%";
D 21
#endif /* notdef */
E 21
I 21
#endif /* not lint */
E 21
E 17
E 12
E 11

/*
 * Mail -- a mail program
 *
 * Handle name lists.
 */

#include "rcv.h"
I 28
#include <fcntl.h>
#include "extern.h"
E 28
I 15
D 23
#include <sys/wait.h>
E 23
E 15
D 11

static char *SccsId = "%W% %G%";
E 11

/*
I 18
D 20
 * Set of network separator characters.
 */
char	*metanet = "!%@";

/*
E 20
E 18
 * Allocate a single element of a name list,
 * initialize its name field to the passed
 * name and return it.
 */
D 20

E 20
struct name *
D 20
nalloc(str)
E 20
I 20
nalloc(str, ntype)
E 20
	char str[];
I 28
	int ntype;
E 28
{
	register struct name *np;

	np = (struct name *) salloc(sizeof *np);
	np->n_flink = NIL;
	np->n_blink = NIL;
D 20
	np->n_type = -1;
E 20
I 20
	np->n_type = ntype;
E 20
	np->n_name = savestr(str);
	return(np);
}

/*
 * Find the tail of a list and return it.
 */
D 20

E 20
struct name *
tailof(name)
	struct name *name;
{
	register struct name *np;

	np = name;
	if (np == NIL)
		return(NIL);
	while (np->n_flink != NIL)
		np = np->n_flink;
	return(np);
}

/*
 * Extract a list of names from a line,
 * and make a list of names from it.
 * Return the list or NIL if none found.
 */
D 20

E 20
struct name *
extract(line, ntype)
	char line[];
I 28
	int ntype;
E 28
{
	register char *cp;
	register struct name *top, *np, *t;
D 20
	char nbuf[BUFSIZ], abuf[BUFSIZ];
E 20
I 20
	char nbuf[BUFSIZ];
E 20

D 20
	if (line == NOSTR || strlen(line) == 0)
		return(NIL);
E 20
I 20
	if (line == NOSTR || *line == '\0')
		return NIL;
E 20
	top = NIL;
	np = NIL;
	cp = line;
	while ((cp = yankword(cp, nbuf)) != NOSTR) {
D 20
		if (np != NIL && equal(nbuf, "at")) {
D 16
			strcpy(abuf, nbuf);
E 16
I 16
			(void) strcpy(abuf, nbuf);
E 16
			if ((cp = yankword(cp, nbuf)) == NOSTR) {
D 16
				strcpy(nbuf, abuf);
E 16
I 16
				(void) strcpy(nbuf, abuf);
E 16
				goto normal;
			}
D 16
			strcpy(abuf, np->n_name);
E 16
I 16
			(void) strcpy(abuf, np->n_name);
E 16
			stradd(abuf, '@');
D 16
			strcat(abuf, nbuf);
E 16
I 16
			(void) strcat(abuf, nbuf);
E 16
			np->n_name = savestr(abuf);
			continue;
		}
normal:
		t = nalloc(nbuf);
		t->n_type = ntype;
E 20
I 20
		t = nalloc(nbuf, ntype);
E 20
		if (top == NIL)
			top = t;
		else
			np->n_flink = t;
		t->n_blink = np;
		np = t;
	}
D 20
	return(top);
E 20
I 20
	return top;
E 20
}

/*
 * Turn a list of names into a string of the same names.
 */
D 20

E 20
char *
detract(np, ntype)
	register struct name *np;
I 28
	int ntype;
E 28
{
	register int s;
	register char *cp, *top;
	register struct name *p;
	register int comma;

	comma = ntype & GCOMMA;
	if (np == NIL)
		return(NOSTR);
	ntype &= ~GCOMMA;
	s = 0;
	if (debug && comma)
		fprintf(stderr, "detract asked to insert commas\n");
	for (p = np; p != NIL; p = p->n_flink) {
		if (ntype && (p->n_type & GMASK) != ntype)
			continue;
		s += strlen(p->n_name) + 1;
		if (comma)
			s++;
	}
	if (s == 0)
		return(NOSTR);
	s += 2;
	top = salloc(s);
	cp = top;
	for (p = np; p != NIL; p = p->n_flink) {
		if (ntype && (p->n_type & GMASK) != ntype)
			continue;
		cp = copy(p->n_name, cp);
		if (comma && p->n_flink != NIL)
			*cp++ = ',';
		*cp++ = ' ';
	}
	*--cp = 0;
	if (comma && *--cp == ',')
		*cp = 0;
	return(top);
}

/*
 * Grab a single word (liberal word)
D 20
 * Throw away things between ()'s.
E 20
I 20
 * Throw away things between ()'s, and take anything between <>.
E 20
 */
D 20

E 20
char *
yankword(ap, wbuf)
	char *ap, wbuf[];
{
	register char *cp, *cp2;

I 14
	cp = ap;
E 14
D 20
	do {
D 14
		for (cp = ap; *cp && any(*cp, " \t,"); cp++)
			;
E 14
I 14
		while (*cp && any(*cp, " \t,"))
			cp++;
E 20
I 20
	for (;;) {
		if (*cp == '\0')
			return NOSTR;
E 20
E 14
		if (*cp == '(') {
D 14
			while (*cp && *cp != ')')
				cp++;
			if (*cp)
				cp++;
E 14
I 14
			register int nesting = 0;

			while (*cp != '\0') {
				switch (*cp++) {
				case '(':
					nesting++;
					break;
				case ')':
					--nesting;
					break;
				}
				if (nesting <= 0)
					break;
			}
E 14
D 20
		}
		if (*cp == '\0')
			return(NOSTR);
	} while (any(*cp, " \t,("));
	for (cp2 = wbuf; *cp && !any(*cp, " \t,("); *cp2++ = *cp++)
		;
E 20
I 20
		} else if (*cp == ' ' || *cp == '\t' || *cp == ',')
			cp++;
		else
			break;
	}
	if (*cp ==  '<')
		for (cp2 = wbuf; *cp && (*cp2++ = *cp++) != '>';)
			;
	else
D 24
		for (cp2 = wbuf; *cp && !any(*cp, " \t,("); *cp2++ = *cp++)
E 24
I 24
		for (cp2 = wbuf; *cp && !index(" \t,(", *cp); *cp2++ = *cp++)
E 24
			;
E 20
	*cp2 = '\0';
D 20
	return(cp);
E 20
I 20
	return cp;
E 20
}

/*
D 18
 * Verify that all the users in the list of names are
 * legitimate.  Bitch about and delink those who aren't.
 */

struct name *
verify(names)
	struct name *names;
{
D 15
	register struct name *np, *top, *t, *x;
	register char *cp;

E 15
D 9
#ifdef DELIVERMAIL
E 9
I 9
#ifdef SENDMAIL
I 15

E 15
E 9
	return(names);
#else
I 15
	register struct name *np, *top, *t, *x;
	register char *cp;

E 15
	top = names;
	np = names;
	while (np != NIL) {
		if (np->n_type & GDEL) {
			np = np->n_flink;
			continue;
		}
		for (cp = "!:@^"; *cp; cp++)
			if (any(*cp, np->n_name))
				break;
		if (*cp != 0) {
			np = np->n_flink;
			continue;
		}
		cp = np->n_name;
		while (*cp == '\\')
			cp++;
		if (equal(cp, "msgs") ||
		    getuserid(cp) != -1) {
			np = np->n_flink;
			continue;
		}
		fprintf(stderr, "Can't send to %s\n", np->n_name);
		senderr++;
		if (np == top) {
			top = np->n_flink;
			if (top != NIL)
				top->n_blink = NIL;
			np = top;
			continue;
		}
		x = np->n_blink;
		t = np->n_flink;
		x->n_flink = t;
		if (t != NIL)
			t->n_blink = x;
		np = t;
	}
	return(top);
#endif
}

/*
E 18
 * For each recipient in the passed name list with a /
 * in the name, append the message to the end of the named file
 * and remove him from the recipient list.
 *
 * Recipients whose name begins with | are piped through the given
 * program and removed.
 */
D 20

E 20
struct name *
outof(names, fo, hp)
	struct name *names;
	FILE *fo;
	struct header *hp;
{
	register int c;
D 15
	register struct name *np, *top, *t, *x;
	long now;
E 15
I 15
	register struct name *np, *top;
D 23
#ifdef CRAZYWOW
	register struct name *t, *x;
#endif
E 23
	time_t now, time();
E 15
D 23
	char *date, *fname, *shell, *ctime();
E 23
I 23
	char *date, *fname, *ctime();
E 23
	FILE *fout, *fin;
D 15
	int ispipe, s, pid;
E 15
I 15
	int ispipe;
E 15
	extern char tempEdit[];
I 15
D 23
	union wait s;
E 23
E 15

	top = names;
	np = names;
D 16
	time(&now);
E 16
I 16
	(void) time(&now);
E 16
	date = ctime(&now);
	while (np != NIL) {
D 5
		if (!any('/', np->n_name) && np->n_name[0] != '|') {
E 5
I 5
		if (!isfileaddr(np->n_name) && np->n_name[0] != '|') {
E 5
			np = np->n_flink;
			continue;
		}
		ispipe = np->n_name[0] == '|';
		if (ispipe)
			fname = np->n_name+1;
		else
			fname = expand(np->n_name);

		/*
		 * See if we have copied the complete message out yet.
		 * If not, do so.
		 */

		if (image < 0) {
D 27
			if ((fout = fopen(tempEdit, "a")) == NULL) {
E 27
I 27
			if ((fout = Fopen(tempEdit, "a")) == NULL) {
E 27
				perror(tempEdit);
				senderr++;
				goto cant;
			}
			image = open(tempEdit, 2);
D 16
			unlink(tempEdit);
E 16
I 16
			(void) unlink(tempEdit);
E 16
			if (image < 0) {
				perror(tempEdit);
				senderr++;
I 27
				(void) Fclose(fout);
E 27
				goto cant;
			}
I 29
			(void) fcntl(image, F_SETFD, 1);
E 29
D 27
			else {
D 23
				rewind(fo);
E 23
				fprintf(fout, "From %s %s", myname, date);
				puthead(hp, fout, GTO|GSUBJECT|GCC|GNL);
				while ((c = getc(fo)) != EOF)
D 16
					putc(c, fout);
E 16
I 16
					(void) putc(c, fout);
E 16
				rewind(fo);
D 16
				putc('\n', fout);
				fflush(fout);
E 16
I 16
				(void) putc('\n', fout);
				(void) fflush(fout);
E 16
				if (ferror(fout))
					perror(tempEdit);
D 16
				fclose(fout);
E 16
I 16
				(void) fclose(fout);
E 16
			}
E 27
I 27
			fprintf(fout, "From %s %s", myname, date);
			puthead(hp, fout, GTO|GSUBJECT|GCC|GNL);
			while ((c = getc(fo)) != EOF)
				(void) putc(c, fout);
			rewind(fo);
			(void) putc('\n', fout);
			(void) fflush(fout);
			if (ferror(fout))
				perror(tempEdit);
			(void) Fclose(fout);
E 27
		}

		/*
		 * Now either copy "image" to the desired file
		 * or give it as the standard input to the desired
		 * program as appropriate.
		 */

		if (ispipe) {
D 16
			wait(&s);
E 16
I 16
D 23
			(void) wait(&s);
E 23
I 23
			int pid;
			char *shell;

D 27
			/* XXX, can't really reuse the same image file */
E 27
I 27
			/*
			 * XXX
			 * We can't really reuse the same image file,
			 * because multiple piped recipients will
			 * share the same lseek location and trample
			 * on one another.
			 */
E 27
E 23
E 16
D 15
			switch (pid = fork()) {
E 15
I 15
D 22
			switch (fork()) {
E 15
			case 0:
I 8
D 15
				sigchild();
E 8
D 2
				signal(SIGHUP, SIG_IGN);
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
E 2
I 2
				sigsys(SIGHUP, SIG_IGN);
				sigsys(SIGINT, SIG_IGN);
				sigsys(SIGQUIT, SIG_IGN);
E 15
I 15
D 16
				signal(SIGHUP, SIG_IGN);
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
E 15
E 2
				close(0);
				dup(image);
				close(image);
E 16
I 16
				(void) signal(SIGHUP, SIG_IGN);
				(void) signal(SIGINT, SIG_IGN);
				(void) signal(SIGQUIT, SIG_IGN);
				(void) close(0);
				(void) dup(image);
				(void) close(image);
E 16
				if ((shell = value("SHELL")) == NOSTR)
					shell = SHELL;
				execl(shell, shell, "-c", fname, 0);
				perror(shell);
				exit(1);
				break;

			case -1:
				perror("fork");
E 22
I 22
			if ((shell = value("SHELL")) == NOSTR)
D 25
				shell = SHELL;
E 25
I 25
				shell = _PATH_CSHELL;
E 25
D 23
			if (start_command(shell,
					sigmask(SIGHUP)|sigmask(SIGINT)|
							sigmask(SIGQUIT),
					image, -1, "-c", fname, NOSTR) < 0) {
E 23
I 23
			pid = start_command(shell, sigmask(SIGHUP)|
					sigmask(SIGINT)|sigmask(SIGQUIT),
				image, -1, "-c", fname, NOSTR);
			if (pid < 0) {
E 23
E 22
				senderr++;
				goto cant;
			}
I 23
			free_child(pid);
E 23
D 22
		}
		else {
E 22
I 22
		} else {
E 22
D 27
			if ((fout = fopen(fname, "a")) == NULL) {
E 27
I 27
			int f;
			if ((fout = Fopen(fname, "a")) == NULL) {
E 27
				perror(fname);
				senderr++;
				goto cant;
			}
D 27
			fin = Fdopen(image, "r");
E 27
I 27
			if ((f = dup(image)) < 0) {
				perror("dup");
				fin = NULL;
			} else
				fin = Fdopen(f, "r");
E 27
			if (fin == NULL) {
				fprintf(stderr, "Can't reopen image\n");
D 16
				fclose(fout);
E 16
I 16
D 27
				(void) fclose(fout);
E 27
I 27
				(void) Fclose(fout);
E 27
E 16
				senderr++;
				goto cant;
			}
			rewind(fin);
			while ((c = getc(fin)) != EOF)
D 16
				putc(c, fout);
E 16
I 16
				(void) putc(c, fout);
E 16
			if (ferror(fout))
				senderr++, perror(fname);
D 16
			fclose(fout);
			fclose(fin);
E 16
I 16
D 27
			(void) fclose(fout);
			(void) fclose(fin);
E 27
I 27
			(void) Fclose(fout);
			(void) Fclose(fin);
E 27
E 16
		}
D 23

E 23
cant:
D 23

E 23
		/*
		 * In days of old we removed the entry from the
		 * the list; now for sake of header expansion
		 * we leave it in and mark it as deleted.
		 */
D 23

#ifdef CRAZYWOW
		if (np == top) {
			top = np->n_flink;
			if (top != NIL)
				top->n_blink = NIL;
			np = top;
			continue;
		}
		x = np->n_blink;
		t = np->n_flink;
		x->n_flink = t;
		if (t != NIL)
			t->n_blink = x;
		np = t;
#endif

E 23
		np->n_type |= GDEL;
		np = np->n_flink;
	}
	if (image >= 0) {
D 16
		close(image);
E 16
I 16
		(void) close(image);
E 16
		image = -1;
	}
	return(top);
I 5
}

/*
 * Determine if the passed address is a local "send to file" address.
 * If any of the network metacharacters precedes any slashes, it can't
 * be a filename.  We cheat with .'s to allow path names like ./...
 */
I 28
int
E 28
isfileaddr(name)
	char *name;
{
	register char *cp;
D 18
	extern char *metanet;
E 18

D 20
	if (any('@', name))
		return(0);
E 20
I 7
	if (*name == '+')
D 20
		return(1);
E 20
I 20
		return 1;
E 20
E 7
	for (cp = name; *cp; cp++) {
D 20
		if (*cp == '.')
			continue;
		if (any(*cp, metanet))
			return(0);
E 20
I 20
		if (*cp == '!' || *cp == '%' || *cp == '@')
			return 0;
E 20
		if (*cp == '/')
D 20
			return(1);
E 20
I 20
			return 1;
E 20
	}
D 20
	return(0);
E 20
I 20
	return 0;
E 20
E 5
}

/*
 * Map all of the aliased users in the invoker's mailrc
 * file and insert them into the list.
 * Changed after all these months of service to recursively
 * expand names (2/14/80).
 */

struct name *
usermap(names)
	struct name *names;
{
	register struct name *new, *np, *cp;
D 15
	struct name *getto;
E 15
	struct grouphead *gh;
	register int metoo;

	new = NIL;
	np = names;
D 15
	getto = NIL;
E 15
	metoo = (value("metoo") != NOSTR);
	while (np != NIL) {
		if (np->n_name[0] == '\\') {
			cp = np->n_flink;
			new = put(new, np);
			np = cp;
			continue;
		}
		gh = findgroup(np->n_name);
		cp = np->n_flink;
		if (gh != NOGRP)
			new = gexpand(new, gh, metoo, np->n_type);
		else
			new = put(new, np);
		np = cp;
	}
	return(new);
}

/*
 * Recursively expand a group name.  We limit the expansion to some
 * fixed level to keep things from going haywire.
 * Direct recursion is not expanded for convenience.
 */

struct name *
gexpand(nlist, gh, metoo, ntype)
	struct name *nlist;
	struct grouphead *gh;
I 28
	int metoo, ntype;
E 28
{
	struct group *gp;
	struct grouphead *ngh;
	struct name *np;
	static int depth;
	char *cp;

	if (depth > MAXEXP) {
		printf("Expanding alias to depth larger than %d\n", MAXEXP);
		return(nlist);
	}
	depth++;
	for (gp = gh->g_list; gp != NOGE; gp = gp->ge_link) {
		cp = gp->ge_name;
		if (*cp == '\\')
			goto quote;
		if (strcmp(cp, gh->g_name) == 0)
			goto quote;
		if ((ngh = findgroup(cp)) != NOGRP) {
			nlist = gexpand(nlist, ngh, metoo, ntype);
			continue;
		}
quote:
D 20
		np = nalloc(cp);
		np->n_type = ntype;
E 20
I 20
		np = nalloc(cp, ntype);
E 20
		/*
		 * At this point should allow to expand
		 * to self if only person in group
		 */
		if (gp == gh->g_list && gp->ge_link == NOGE)
			goto skip;
		if (!metoo && strcmp(cp, myname) == 0)
			np->n_type |= GDEL;
skip:
		nlist = put(nlist, np);
	}
	depth--;
	return(nlist);
}

D 20


E 20
/*
D 20
 * Compute the length of the passed name list and
 * return it.
 */

lengthof(name)
	struct name *name;
{
	register struct name *np;
	register int c;

	for (c = 0, np = name; np != NIL; c++, np = np->n_flink)
		;
	return(c);
}

/*
E 20
 * Concatenate the two passed name lists, return the result.
 */
D 20

E 20
struct name *
cat(n1, n2)
	struct name *n1, *n2;
{
	register struct name *tail;

	if (n1 == NIL)
		return(n2);
	if (n2 == NIL)
		return(n1);
	tail = tailof(n1);
	tail->n_flink = n2;
	n2->n_blink = tail;
	return(n1);
}

/*
 * Unpack the name list onto a vector of strings.
 * Return an error if the name list won't fit.
 */
D 20

E 20
char **
unpack(np)
	struct name *np;
{
	register char **ap, **top;
	register struct name *n;
D 16
	char *cp;
E 16
D 19
	char hbuf[10];
E 19
D 10
	int t, extra, metoo;
E 10
I 10
	int t, extra, metoo, verbose;
E 10

	n = np;
D 20
	if ((t = lengthof(n)) == 0)
E 20
I 20
	if ((t = count(n)) == 0)
E 20
		panic("No names to unpack");
D 20

E 20
	/*
	 * Compute the number of extra arguments we will need.
	 * We need at least two extra -- one for "mail" and one for
	 * the terminating 0 pointer.  Additional spots may be needed
D 19
	 * to pass along -r and -f to the host mailer.
E 19
I 19
	 * to pass along -f to the host mailer.
E 19
	 */
D 20

E 20
	extra = 2;
D 19
	if (rflag != NOSTR)
		extra += 2;
E 19
D 9
#ifdef DELIVERMAIL
E 9
I 9
D 18
#ifdef SENDMAIL
E 18
E 9
	extra++;
	metoo = value("metoo") != NOSTR;
	if (metoo)
		extra++;
I 10
	verbose = value("verbose") != NOSTR;
	if (verbose)
		extra++;
E 10
D 9
#endif DELIVERMAIL
E 9
I 9
D 18
#endif SENDMAIL
E 18
E 9
D 19
	if (hflag)
		extra += 2;
E 19
D 16
	top = (char **) salloc((t + extra) * sizeof cp);
E 16
I 16
	top = (char **) salloc((t + extra) * sizeof *top);
E 16
	ap = top;
	*ap++ = "send-mail";
D 19
	if (rflag != NOSTR) {
		*ap++ = "-r";
		*ap++ = rflag;
	}
E 19
D 9
#ifdef DELIVERMAIL
E 9
I 9
D 18
#ifdef SENDMAIL
E 18
E 9
	*ap++ = "-i";
	if (metoo)
		*ap++ = "-m";
I 10
	if (verbose)
		*ap++ = "-v";
E 10
D 9
#endif DELIVERMAIL
E 9
I 9
D 18
#endif SENDMAIL
E 18
E 9
D 19
	if (hflag) {
		*ap++ = "-h";
D 16
		sprintf(hbuf, "%d", hflag);
		*ap++ = savestr(hbuf);
E 16
I 16
		*ap++ = savestr(sprintf(hbuf, "%d", hflag));
E 16
	}
E 19
D 23
	while (n != NIL) {
		if (n->n_type & GDEL) {
			n = n->n_flink;
			continue;
		}
D 4
		cp = n->n_name;
		while (*cp == '\\')
			cp++;
		*ap++ = cp;
E 4
I 4
		*ap++ = n->n_name;
E 4
		n = n->n_flink;
	}
E 23
I 23
	for (; n != NIL; n = n->n_flink)
		if ((n->n_type & GDEL) == 0)
			*ap++ = n->n_name;
E 23
	*ap = NOSTR;
	return(top);
D 19
}

/*
 * See if the user named himself as a destination
 * for outgoing mail.  If so, set the global flag
 * selfsent so that we avoid removing his mailbox.
 */

mechk(names)
	struct name *names;
{
	register struct name *np;

	for (np = names; np != NIL; np = np->n_flink)
D 6
		if ((np->n_type & GDEL) == 0 && equal(myname, np->n_name)) {
E 6
I 6
		if ((np->n_type & GDEL) == 0 && equal(np->n_name, myname)) {
E 6
			selfsent++;
			return;
		}
E 19
}

/*
 * Remove all of the duplicates from the passed name list by
 * insertion sorting them, then checking for dups.
 * Return the head of the new list.
 */
D 20

E 20
struct name *
elide(names)
	struct name *names;
{
	register struct name *np, *t, *new;
	struct name *x;

	if (names == NIL)
		return(NIL);
	new = names;
	np = names;
	np = np->n_flink;
	if (np != NIL)
		np->n_blink = NIL;
	new->n_flink = NIL;
	while (np != NIL) {
		t = new;
D 24
		while (nstrcmp(t->n_name, np->n_name) < 0) {
E 24
I 24
		while (strcasecmp(t->n_name, np->n_name) < 0) {
E 24
			if (t->n_flink == NIL)
				break;
			t = t->n_flink;
		}

		/*
		 * If we ran out of t's, put the new entry after
		 * the current value of t.
		 */

D 24
		if (nstrcmp(t->n_name, np->n_name) < 0) {
E 24
I 24
		if (strcasecmp(t->n_name, np->n_name) < 0) {
E 24
			t->n_flink = np;
			np->n_blink = t;
			t = np;
			np = np->n_flink;
			t->n_flink = NIL;
			continue;
		}

		/*
		 * Otherwise, put the new entry in front of the
		 * current t.  If at the front of the list,
		 * the new guy becomes the new head of the list.
		 */

		if (t == new) {
			t = np;
			np = np->n_flink;
			t->n_flink = new;
			new->n_blink = t;
			t->n_blink = NIL;
			new = t;
			continue;
		}

		/*
		 * The normal case -- we are inserting into the
		 * middle of the list.
		 */

		x = np;
		np = np->n_flink;
		x->n_flink = t;
		x->n_blink = t->n_blink;
		t->n_blink->n_flink = x;
		t->n_blink = x;
	}

	/*
	 * Now the list headed up by new is sorted.
	 * Go through it and remove duplicates.
	 */

	np = new;
	while (np != NIL) {
		t = np;
D 24
		while (t->n_flink!=NIL &&
		    icequal(np->n_name,t->n_flink->n_name))
E 24
I 24
		while (t->n_flink != NIL &&
		       strcasecmp(np->n_name, t->n_flink->n_name) == 0)
E 24
			t = t->n_flink;
		if (t == np || t == NIL) {
			np = np->n_flink;
			continue;
		}
		
		/*
		 * Now t points to the last entry with the same name
		 * as np.  Make np point beyond t.
		 */

		np->n_flink = t->n_flink;
		if (t->n_flink != NIL)
			t->n_flink->n_blink = np;
		np = np->n_flink;
	}
	return(new);
}

/*
D 24
 * Version of strcmp which ignores case differences.
 */
D 20

E 20
nstrcmp(s1, s2)
	register char *s1, *s2;
{
	register int c1, c2;

	do {
		c1 = *s1++;
		c2 = *s2++;
	} while (c1 && c1 == c2);
	return(c1 - c2);
}

/*
E 24
 * Put another node onto a list of names and return
 * the list.
 */
D 20

E 20
struct name *
put(list, node)
	struct name *list, *node;
{
	node->n_flink = list;
	node->n_blink = NIL;
	if (list != NIL)
		list->n_blink = node;
	return(node);
}

/*
D 23
 * Determine the number of elements in
E 23
I 23
 * Determine the number of undeleted elements in
E 23
 * a name list and return it.
 */
I 28
int
E 28
D 20

E 20
count(np)
	register struct name *np;
{
D 20
	register int c = 0;
E 20
I 20
	register int c;
E 20

D 20
	while (np != NIL) {
		c++;
		np = np->n_flink;
	}
	return(c);
E 20
I 20
D 23
	for (c = 0; np != NIL; c++, np = np->n_flink)
		;
E 23
I 23
	for (c = 0; np != NIL; np = np->n_flink)
		if ((np->n_type & GDEL) == 0)
			c++;
E 23
	return c;
E 20
}

I 10
D 15
cmpdomain(name, dname)
	register char *name, *dname;
{
	char buf[BUFSIZ];

	strcpy(buf, dname);
	buf[strlen(name)] = '\0';
	return(icequal(name, buf));
}

E 15
E 10
/*
D 10
 * Delete the given name from a namelist.
E 10
I 10
D 24
 * Delete the given name from a namelist, using the passed
 * function to compare the names.
E 24
I 24
 * Delete the given name from a namelist.
E 24
E 10
 */
D 6

E 6
struct name *
D 10
delname(np, name)
E 10
I 10
D 24
delname(np, name, cmpfun)
E 24
I 24
delname(np, name)
E 24
E 10
	register struct name *np;
	char name[];
I 10
D 24
	int (* cmpfun)();
E 24
E 10
{
	register struct name *p;

	for (p = np; p != NIL; p = p->n_flink)
D 6
		if (equal(p->n_name, name)) {
E 6
I 6
D 10
		if (icequal(p->n_name, name)) {
E 10
I 10
D 24
		if ((* cmpfun)(p->n_name, name)) {
E 24
I 24
		if (strcasecmp(p->n_name, name) == 0) {
E 24
E 10
E 6
			if (p->n_blink == NIL) {
				if (p->n_flink != NIL)
					p->n_flink->n_blink = NIL;
				np = p->n_flink;
				continue;
			}
			if (p->n_flink == NIL) {
				if (p->n_blink != NIL)
					p->n_blink->n_flink = NIL;
				continue;
			}
			p->n_blink->n_flink = p->n_flink;
			p->n_flink->n_blink = p->n_blink;
		}
D 24
	return(np);
E 24
I 24
	return np;
E 24
D 18
}

/*
 * Call the given routine on each element of the name
 * list, replacing said value if need be.
 */

mapf(np, from)
	register struct name *np;
	char *from;
{
	register struct name *p;

	for (p = np; p != NIL; p = p->n_flink)
		p->n_name = netmap(p->n_name, from);
E 18
}

/*
 * Pretty print a name list
 * Uncomment it if you need it.
 */

I 15
/*
I 28
void
E 28
E 15
prettyprint(name)
	struct name *name;
{
	register struct name *np;

	np = name;
	while (np != NIL) {
		fprintf(stderr, "%s(%d) ", np->n_name, np->n_type);
		np = np->n_flink;
	}
	fprintf(stderr, "\n");
}
I 15
*/
E 15
E 1
