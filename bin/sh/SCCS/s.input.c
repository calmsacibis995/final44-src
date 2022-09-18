h36694
s 00001/00000/00451
d D 8.3 95/06/08 21:47:21 christos 12 11
c added string.h
e
s 00017/00014/00434
d D 8.2 95/05/04 17:59:48 christos 11 10
c 
e
s 00002/00002/00446
d D 8.1 93/05/31 15:19:13 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00447
d D 5.8 92/07/15 10:01:55 marc 9 8
c propor declarations
e
s 00000/00001/00448
d D 5.7 92/07/15 09:15:16 marc 8 7
c is_interactive not used
e
s 00001/00001/00448
d D 5.6 92/06/23 18:38:47 marc 7 6
c histedit.h ==> myhistedit.h to avoid naming conflict
e
s 00119/00025/00330
d D 5.5 92/06/23 17:56:55 marc 6 5
c aliases and editing (and -v, sort of)
e
s 00002/00002/00353
d D 5.4 91/07/01 00:17:25 bostic 5 4
c change FNDELAY to O_NONBLOCK
e
s 00001/00002/00354
d D 5.3 91/04/12 18:22:19 marc 4 2
c typo
e
s 00001/00002/00354
d R 5.3 91/04/12 18:21:35 marc 3 2
c type
e
s 00017/00004/00339
d D 5.2 91/03/13 18:37:32 marc 2 1
c wrong source
e
s 00343/00000/00000
d D 5.1 91/03/07 20:27:32 bostic 1 0
c date and time created 91/03/07 20:27:32 by bostic
e
u
U
t
T
I 1
/*-
D 10
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 11
#include <stdio.h>	/* defines BUFSIZ */
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
I 12
#include <string.h>
E 12

E 11
/*
 * This file implements the input routines used by the parser.
 */

D 11
#include <stdio.h>	/* defines BUFSIZ */
E 11
#include "shell.h"
D 11
#include <fcntl.h>
#include <errno.h>
E 11
I 11
#include "redir.h"
E 11
#include "syntax.h"
#include "input.h"
#include "output.h"
I 6
#include "options.h"
E 6
#include "memalloc.h"
#include "error.h"
I 6
#include "alias.h"
#include "parser.h"
D 7
#include "histedit.h"
E 7
I 7
#include "myhistedit.h"
E 7
E 6

#define EOF_NLEFT -99		/* value of parsenleft when EOF pushed back */

I 6
MKINIT
struct strpush {
	struct strpush *prev;	/* preceding string on stack */
	char *prevstring;
	int prevnleft;
	struct alias *ap;	/* if push was associated with an alias */
};
E 6

/*
 * The parsefile structure pointed to by the global variable parsefile
 * contains information about the current file being read.
 */

MKINIT
struct parsefile {
I 6
	struct parsefile *prev;	/* preceding file on stack */
E 6
	int linno;		/* current line */
	int fd;			/* file descriptor (or -1 if string) */
	int nleft;		/* number of chars left in buffer */
	char *nextc;		/* next char in buffer */
D 6
	struct parsefile *prev;	/* preceding file on stack */
E 6
	char *buf;		/* input buffer */
I 6
	struct strpush *strpush; /* for pushing strings at this level */
	struct strpush basestrpush; /* so pushing one is fast */
E 6
};


int plinno = 1;			/* input line number */
MKINIT int parsenleft;		/* copy of parsefile->nleft */
char *parsenextc;		/* copy of parsefile->nextc */
MKINIT struct parsefile basepf;	/* top level input file */
char basebuf[BUFSIZ];		/* buffer for top level input file */
struct parsefile *parsefile = &basepf;	/* current input file */
char *pushedstring;		/* copy of parsenextc when text pushed back */
int pushednleft;		/* copy of parsenleft when text pushed back */
I 6
int init_editline = 0;		/* editline library initialized? */
int whichprompt;		/* 1 == PS1, 2 == PS2 */
E 6

I 6
EditLine *el;			/* cookie for editline package */

E 6
D 11
#ifdef __STDC__
STATIC void pushfile(void);
#else
STATIC void pushfile();
#endif
E 11
I 11
STATIC void pushfile __P((void));
E 11

D 11


E 11
#ifdef mkinit
INCLUDE "input.h"
INCLUDE "error.h"

INIT {
	extern char basebuf[];

	basepf.nextc = basepf.buf = basebuf;
}

RESET {
	if (exception != EXSHELLPROC)
		parsenleft = 0;            /* clear input buffer */
	popallfiles();
}

SHELLPROC {
	popallfiles();
}
#endif


/*
 * Read a line from the script.
 */

char *
pfgets(line, len)
	char *line;
D 11
	{
E 11
I 11
	int len;
{
E 11
	register char *p = line;
	int nleft = len;
	int c;

	while (--nleft > 0) {
		c = pgetc_macro();
		if (c == PEOF) {
			if (p == line)
				return NULL;
			break;
		}
		*p++ = c;
		if (c == '\n')
			break;
	}
	*p = '\0';
	return line;
}



/*
 * Read a character from the script, returning PEOF on end of file.
 * Nul characters in the input are silently discarded.
 */

int
pgetc() {
	return pgetc_macro();
}


/*
 * Refill the input buffer and return the next input character:
 *
D 6
 * 1) If a string was pushed back on the input, switch back to the regular
 *    buffer.
E 6
I 6
 * 1) If a string was pushed back on the input, pop it;
E 6
 * 2) If an EOF was pushed back (parsenleft == EOF_NLEFT) or we are reading
 *    from a string so we can't refill the buffer, return EOF.
 * 3) Call read to read in the characters.
 * 4) Delete all nul characters from the buffer.
 */

int
preadbuffer() {
	register char *p, *q;
	register int i;
I 6
	register int something;
	extern EditLine *el;
D 8
	extern int is_interactive;
E 8
E 6

D 6
	if (pushedstring) {
		parsenextc = pushedstring;
		pushedstring = NULL;
		parsenleft = pushednleft;
E 6
I 6
	if (parsefile->strpush) {
		popstring();
E 6
		if (--parsenleft >= 0)
D 6
			return *parsenextc++;
E 6
I 6
			return (*parsenextc++);
E 6
	}
	if (parsenleft == EOF_NLEFT || parsefile->buf == NULL)
		return PEOF;
	flushout(&output);
	flushout(&errout);
retry:
	p = parsenextc = parsefile->buf;
D 6
	i = read(parsefile->fd, p, BUFSIZ);
E 6
I 6
	if (parsefile->fd == 0 && el) {
D 9
		char *rl_cp;
E 9
I 9
		const char *rl_cp;
E 9
		int len;

		rl_cp = el_gets(el, &len);
		if (rl_cp == NULL) {
			i = 0;
			goto eof;
		}
		strcpy(p, rl_cp);  /* XXX - BUFSIZE should redesign so not necessary */
		i = len;

	} else {
D 11
regular_read:
E 11
		i = read(parsefile->fd, p, BUFSIZ - 1);
	}
eof:
E 6
	if (i <= 0) {
D 2
		if (i < 0 && errno == EINTR)
			goto retry;
		parsenleft = EOF_NLEFT;
		return PEOF;
E 2
I 2
                if (i < 0) {
                        if (errno == EINTR)
                                goto retry;
                        if (parsefile->fd == 0 && errno == EWOULDBLOCK) {
                                int flags = fcntl(0, F_GETFL, 0);
D 5
                                if (flags >= 0 && flags & FNDELAY) {
                                        flags &=~ FNDELAY;
E 5
I 5
                                if (flags >= 0 && flags & O_NONBLOCK) {
                                        flags &=~ O_NONBLOCK;
E 5
                                        if (fcntl(0, F_SETFL, flags) >= 0) {
D 4
                                                out2str("sh: turning off NDELAY
 mode\n");
E 4
I 4
						out2str("sh: turning off NDELAY mode\n");
E 4
                                                goto retry;
                                        }
                                }
                        }
                }
                parsenleft = EOF_NLEFT;
                return PEOF;
E 2
	}
D 6
	parsenleft = i - 1;
E 6
I 6
	parsenleft = i - 1;	/* we're returning one char in this call */
E 6

	/* delete nul characters */
I 6
	something = 0;
E 6
	for (;;) {
D 6
		if (*p++ == '\0')
E 6
I 6
		if (*p == '\0')
E 6
			break;
D 6
		if (--i <= 0)
			return *parsenextc++;		/* no nul characters */
E 6
I 6
		if (*p != ' ' && *p != '\t' && *p != '\n')
			something = 1;
		p++;
		if (--i <= 0) {
			*p = '\0';
			goto done;		/* no nul characters */
		}
E 6
	}
D 6
	q = p - 1;
E 6
I 6
	/*
	 * remove nuls
	 */
	q = p++;
E 6
	while (--i > 0) {
		if (*p != '\0')
			*q++ = *p;
		p++;
	}
I 6
	*q = '\0';
E 6
	if (q == parsefile->buf)
		goto retry;			/* buffer contained nothing but nuls */
	parsenleft = q - parsefile->buf - 1;
I 6

done:
	if (parsefile->fd == 0 && hist && something) {
		INTOFF;
		history(hist, whichprompt == 1 ? H_ENTER : H_ADD, 
			   parsefile->buf);
		INTON;
	}
	if (vflag) {
		/*
		 * This isn't right.  Most shells coordinate it with
		 * reading a line at a time.  I honestly don't know if its
		 * worth it.
		 */
		i = parsenleft + 1;
		p = parsefile->buf;
		for (; i--; p++) 
			out2c(*p)
		flushout(out2);
	}
E 6
	return *parsenextc++;
}

D 6

E 6
/*
 * Undo the last call to pgetc.  Only one character may be pushed back.
 * PEOF may be pushed back.
 */

void
pungetc() {
	parsenleft++;
	parsenextc--;
}

D 6

E 6
/*
D 6
 * Push a string back onto the input.  This code doesn't work if the user
 * tries to push back more than one string at once.
E 6
I 6
 * Push a string back onto the input at this current parsefile level.
 * We handle aliases this way.
E 6
 */
D 6

E 6
void
D 6
ppushback(string, length)
	char *string;
E 6
I 6
pushstring(s, len, ap)
	char *s;
	int len;
	void *ap;
E 6
	{
D 6
	pushedstring = parsenextc;
	pushednleft = parsenleft;
	parsenextc = string;
	parsenleft = length;
E 6
I 6
	struct strpush *sp;

	INTOFF;
/*dprintf("*** calling pushstring: %s, %d\n", s, len);*/
	if (parsefile->strpush) {
		sp = ckmalloc(sizeof (struct strpush));
		sp->prev = parsefile->strpush;
		parsefile->strpush = sp;
	} else
		sp = parsefile->strpush = &(parsefile->basestrpush);
	sp->prevstring = parsenextc;
	sp->prevnleft = parsenleft;
	sp->ap = (struct alias *)ap;
	if (ap)
		((struct alias *)ap)->flag |= ALIASINUSE;
	parsenextc = s;
	parsenleft = len;
	INTON;
E 6
}

I 11
void
E 11
I 6
popstring()
{
	struct strpush *sp = parsefile->strpush;
E 6

I 6
	INTOFF;
	parsenextc = sp->prevstring;
	parsenleft = sp->prevnleft;
/*dprintf("*** calling popstring: restoring to '%s'\n", parsenextc);*/
	if (sp->ap)
		sp->ap->flag &= ~ALIASINUSE;
	parsefile->strpush = sp->prev;
	if (sp != &(parsefile->basestrpush))
		ckfree(sp);
	INTON;
}
E 6

/*
 * Set the input to take input from a file.  If push is set, push the
 * old input onto the stack first.
 */

void
setinputfile(fname, push)
	char *fname;
D 11
	{
E 11
I 11
	int push;
{
E 11
	int fd;
	int fd2;

	INTOFF;
	if ((fd = open(fname, O_RDONLY)) < 0)
		error("Can't open %s", fname);
	if (fd < 10) {
		fd2 = copyfd(fd, 10);
		close(fd);
		if (fd2 < 0)
			error("Out of file descriptors");
		fd = fd2;
	}
	setinputfd(fd, push);
	INTON;
}


/*
 * Like setinputfile, but takes an open file descriptor.  Call this with
 * interrupts off.
 */

void
D 11
setinputfd(fd, push) {
E 11
I 11
setinputfd(fd, push)
	int fd, push;
{
E 11
	if (push) {
		pushfile();
		parsefile->buf = ckmalloc(BUFSIZ);
	}
	if (parsefile->fd > 0)
		close(parsefile->fd);
	parsefile->fd = fd;
	if (parsefile->buf == NULL)
		parsefile->buf = ckmalloc(BUFSIZ);
	parsenleft = 0;
	plinno = 1;
}


/*
 * Like setinputfile, but takes input from a string.
 */

void
setinputstring(string, push)
	char *string;
I 11
	int push;
E 11
	{
	INTOFF;
	if (push)
		pushfile();
	parsenextc = string;
	parsenleft = strlen(string);
	parsefile->buf = NULL;
	plinno = 1;
	INTON;
}



/*
 * To handle the "." command, a stack of input files is used.  Pushfile
 * adds a new entry to the stack and popfile restores the previous level.
 */

STATIC void
pushfile() {
	struct parsefile *pf;

	parsefile->nleft = parsenleft;
	parsefile->nextc = parsenextc;
	parsefile->linno = plinno;
	pf = (struct parsefile *)ckmalloc(sizeof (struct parsefile));
	pf->prev = parsefile;
	pf->fd = -1;
I 6
	pf->strpush = NULL;
	pf->basestrpush.prev = NULL;
E 6
	parsefile = pf;
}


void
popfile() {
	struct parsefile *pf = parsefile;

	INTOFF;
	if (pf->fd >= 0)
		close(pf->fd);
	if (pf->buf)
		ckfree(pf->buf);
I 6
	while (pf->strpush)
		popstring();
E 6
	parsefile = pf->prev;
	ckfree(pf);
	parsenleft = parsefile->nleft;
	parsenextc = parsefile->nextc;
	plinno = parsefile->linno;
	INTON;
}


/*
 * Return to top level.
 */

void
popallfiles() {
	while (parsefile != &basepf)
		popfile();
}



/*
 * Close the file(s) that the shell is reading commands from.  Called
 * after a fork is done.
 */

void
closescript() {
	popallfiles();
	if (parsefile->fd > 0) {
		close(parsefile->fd);
		parsefile->fd = 0;
	}
}
E 1
