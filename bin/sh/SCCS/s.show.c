h38537
s 00069/00030/00346
d D 8.3 95/05/04 18:00:11 christos 8 7
c 
e
s 00024/00000/00352
d D 8.2 95/04/28 17:16:19 bostic 7 6
c add the documented in the manual but not implemented variable
c expansions.
c From: Christos Zoulas <christos@deshaw.com>
e
s 00002/00002/00350
d D 8.1 93/05/31 15:36:32 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00028/00350
d D 5.4 93/05/31 15:36:28 bostic 5 3
c fix the SCCS notice/copyright
e
s 00002/00002/00376
d R 8.1 93/05/31 15:20:42 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00004/00344
d D 5.3 92/07/15 09:10:41 marc 3 2
c trace to ./trace not $HOME/.trace
e
s 00014/00003/00334
d D 5.2 91/04/12 18:28:17 marc 2 1
c for debug; if HOME not set and root, write to /trace.
e
s 00337/00000/00000
d D 5.1 91/03/07 20:28:00 bostic 1 0
c date and time created 91/03/07 20:28:00 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
D 3
 * %sccs.include.redist.c%
E 3
I 3
D 5
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
E 5
I 5
 * %sccs.include.redist.c%
E 5
E 3
 */

#ifndef lint
D 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
I 3
D 5
static char sccsid[] = "@(#)show.c	5.2 (Berkeley) 4/12/91";
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
E 3
#endif /* not lint */

#include <stdio.h>
I 8
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

E 8
#include "shell.h"
#include "parser.h"
#include "nodes.h"
#include "mystring.h"
I 8
#include "show.h"
E 8


#ifdef DEBUG
D 8
static shtree(), shcmd(), sharg(), indent();
E 8
I 8
static void shtree __P((union node *, int, char *, FILE*));
static void shcmd __P((union node *, FILE *));
static void sharg __P((union node *, FILE *));
static void indent __P((int, char *, FILE *));
static void trstring __P((char *));
E 8


I 8
void
E 8
showtree(n)
	union node *n;
D 8
	{
E 8
I 8
{
E 8
	trputs("showtree called\n");
	shtree(n, 1, NULL, stdout);
}


D 8
static
E 8
I 8
static void
E 8
shtree(n, ind, pfx, fp)
	union node *n;
I 8
	int ind;
E 8
	char *pfx;
	FILE *fp;
D 8
	{
E 8
I 8
{
E 8
	struct nodelist *lp;
	char *s;

I 7
	if (n == NULL)
		return;

E 7
	indent(ind, pfx, fp);
	switch(n->type) {
	case NSEMI:
		s = "; ";
		goto binop;
	case NAND:
		s = " && ";
		goto binop;
	case NOR:
		s = " || ";
binop:
		shtree(n->nbinary.ch1, ind, NULL, fp);
	   /*    if (ind < 0) */
			fputs(s, fp);
		shtree(n->nbinary.ch2, ind, NULL, fp);
		break;
	case NCMD:
		shcmd(n, fp);
		if (ind >= 0)
			putc('\n', fp);
		break;
	case NPIPE:
		for (lp = n->npipe.cmdlist ; lp ; lp = lp->next) {
			shcmd(lp->n, fp);
			if (lp->next)
				fputs(" | ", fp);
		}
		if (n->npipe.backgnd)
			fputs(" &", fp);
		if (ind >= 0)
			putc('\n', fp);
		break;
	default:
		fprintf(fp, "<node type %d>", n->type);
		if (ind >= 0)
			putc('\n', fp);
		break;
	}
}



D 8
static
E 8
I 8
static void
E 8
shcmd(cmd, fp)
	union node *cmd;
	FILE *fp;
D 8
	{
E 8
I 8
{
E 8
	union node *np;
	int first;
	char *s;
	int dftfd;

	first = 1;
	for (np = cmd->ncmd.args ; np ; np = np->narg.next) {
		if (! first)
			putchar(' ');
		sharg(np, fp);
		first = 0;
	}
	for (np = cmd->ncmd.redirect ; np ; np = np->nfile.next) {
		if (! first)
			putchar(' ');
		switch (np->nfile.type) {
			case NTO:	s = ">";  dftfd = 1; break;
			case NAPPEND:	s = ">>"; dftfd = 1; break;
			case NTOFD:	s = ">&"; dftfd = 1; break;
			case NFROM:	s = "<";  dftfd = 0; break;
			case NFROMFD:	s = "<&"; dftfd = 0; break;
I 8
			default:  	s = "*error*"; dftfd = 0; break;
E 8
		}
		if (np->nfile.fd != dftfd)
			fprintf(fp, "%d", np->nfile.fd);
		fputs(s, fp);
		if (np->nfile.type == NTOFD || np->nfile.type == NFROMFD) {
			fprintf(fp, "%d", np->ndup.dupfd);
		} else {
			sharg(np->nfile.fname, fp);
		}
		first = 0;
	}
}



D 8
static
E 8
I 8
static void
E 8
sharg(arg, fp)
	union node *arg;
	FILE *fp;
	{
	char *p;
	struct nodelist *bqlist;
	int subtype;

	if (arg->type != NARG) {
		printf("<node type %d>\n", arg->type);
		fflush(stdout);
		abort();
	}
	bqlist = arg->narg.backquote;
	for (p = arg->narg.text ; *p ; p++) {
		switch (*p) {
		case CTLESC:
			putc(*++p, fp);
			break;
		case CTLVAR:
			putc('$', fp);
			putc('{', fp);
			subtype = *++p;
I 7
			if (subtype == VSLENGTH)
				putc('#', fp);

E 7
			while (*p != '=')
				putc(*p++, fp);
I 7

E 7
			if (subtype & VSNUL)
				putc(':', fp);
I 7

E 7
			switch (subtype & VSTYPE) {
			case VSNORMAL:
				putc('}', fp);
				break;
			case VSMINUS:
				putc('-', fp);
				break;
			case VSPLUS:
				putc('+', fp);
				break;
			case VSQUESTION:
				putc('?', fp);
				break;
			case VSASSIGN:
				putc('=', fp);
I 7
				break;
			case VSTRIMLEFT:
				putc('#', fp);
				break;
			case VSTRIMLEFTMAX:
				putc('#', fp);
				putc('#', fp);
				break;
			case VSTRIMRIGHT:
				putc('%', fp);
				break;
			case VSTRIMRIGHTMAX:
				putc('%', fp);
				putc('%', fp);
				break;
			case VSLENGTH:
E 7
				break;
			default:
				printf("<subtype %d>", subtype);
			}
			break;
		case CTLENDVAR:
		     putc('}', fp);
		     break;
		case CTLBACKQ:
		case CTLBACKQ|CTLQUOTE:
			putc('$', fp);
			putc('(', fp);
			shtree(bqlist->n, -1, NULL, fp);
			putc(')', fp);
			break;
		default:
			putc(*p, fp);
			break;
		}
	}
}


D 8
static
E 8
I 8
static void
E 8
indent(amount, pfx, fp)
I 8
	int amount;
E 8
	char *pfx;
	FILE *fp;
D 8
	{
E 8
I 8
{
E 8
	int i;

	for (i = 0 ; i < amount ; i++) {
		if (pfx && i == amount - 1)
			fputs(pfx, fp);
		putc('\t', fp);
	}
}
#endif



/*
 * Debugging stuff.
 */


FILE *tracefile;

I 2
#if DEBUG == 2
int debug = 1;
#else
int debug = 0;
#endif
E 2


D 8
trputc(c) {
E 8
I 8
void
trputc(c) 
	int c;
{
E 8
#ifdef DEBUG
	if (tracefile == NULL)
		return;
	putc(c, tracefile);
	if (c == '\n')
		fflush(tracefile);
#endif
}

D 8

trace(fmt, a1, a2, a3, a4, a5, a6, a7, a8)
	char *fmt;
	{
E 8
I 8
void
#if __STDC__
trace(const char *fmt, ...)
#else
trace(va_alist)
	va_dcl
#endif
{
E 8
#ifdef DEBUG
D 8
	if (tracefile == NULL)
		return;
	fprintf(tracefile, fmt, a1, a2, a3, a4, a5, a6, a7, a8);
	if (strchr(fmt, '\n'))
		fflush(tracefile);
E 8
I 8
	va_list va;
#if __STDC__
	va_start(va, fmt);
#else
	char *fmt;
	va_start(va);
	fmt = va_arg(va, char *);
E 8
#endif
I 8
	if (tracefile != NULL) {
		(void) vfprintf(tracefile, fmt, va);
		if (strchr(fmt, '\n'))
			(void) fflush(tracefile);
	}
	va_end(va);
#endif
E 8
}


I 8
void
E 8
trputs(s)
	char *s;
D 8
	{
E 8
I 8
{
E 8
#ifdef DEBUG
	if (tracefile == NULL)
		return;
	fputs(s, tracefile);
	if (strchr(s, '\n'))
		fflush(tracefile);
#endif
}


I 8
static void
E 8
trstring(s)
	char *s;
D 8
	{
E 8
I 8
{
E 8
	register char *p;
	char c;

#ifdef DEBUG
	if (tracefile == NULL)
		return;
	putc('"', tracefile);
	for (p = s ; *p ; p++) {
		switch (*p) {
		case '\n':  c = 'n';  goto backslash;
		case '\t':  c = 't';  goto backslash;
		case '\r':  c = 'r';  goto backslash;
		case '"':  c = '"';  goto backslash;
		case '\\':  c = '\\';  goto backslash;
		case CTLESC:  c = 'e';  goto backslash;
		case CTLVAR:  c = 'v';  goto backslash;
		case CTLVAR+CTLQUOTE:  c = 'V';  goto backslash;
		case CTLBACKQ:  c = 'q';  goto backslash;
		case CTLBACKQ+CTLQUOTE:  c = 'Q';  goto backslash;
backslash:	  putc('\\', tracefile);
			putc(c, tracefile);
			break;
		default:
			if (*p >= ' ' && *p <= '~')
				putc(*p, tracefile);
			else {
				putc('\\', tracefile);
				putc(*p >> 6 & 03, tracefile);
				putc(*p >> 3 & 07, tracefile);
				putc(*p & 07, tracefile);
			}
			break;
		}
	}
	putc('"', tracefile);
#endif
}


I 8
void
E 8
trargs(ap)
	char **ap;
D 8
	{
E 8
I 8
{
E 8
#ifdef DEBUG
	if (tracefile == NULL)
		return;
	while (*ap) {
		trstring(*ap++);
		if (*ap)
			putc(' ', tracefile);
		else
			putc('\n', tracefile);
	}
	fflush(tracefile);
#endif
}


I 8
void
E 8
opentrace() {
	char s[100];
D 8
	char *p;
E 8
	char *getenv();
I 8
#ifdef O_APPEND
E 8
	int flags;
I 8
#endif
E 8

#ifdef DEBUG
D 2
	if ((p = getenv("HOME")) == NULL)
		p = "/tmp";
E 2
I 2
	if (!debug)
		return;
I 3
#ifdef not_this_way
E 3
D 8
	if ((p = getenv("HOME")) == NULL) {
D 3
		if (getuid() == 0)
E 3
I 3
		if (geteuid() == 0)
E 3
			p = "/";
		else
			p = "/tmp";
E 8
I 8
	{
		char *p;
		if ((p = getenv("HOME")) == NULL) {
			if (geteuid() == 0)
				p = "/";
			else
				p = "/tmp";
		}
		scopy(p, s);
		strcat(s, "/trace");
E 8
	}
E 2
D 8
	scopy(p, s);
	strcat(s, "/trace");
E 8
I 3
#else
	scopy("./trace", s);
#endif /* not_this_way */
E 3
	if ((tracefile = fopen(s, "a")) == NULL) {
		fprintf(stderr, "Can't open %s\n", s);
D 2
		exit(2);
E 2
I 2
		return;
E 2
	}
#ifdef O_APPEND
	if ((flags = fcntl(fileno(tracefile), F_GETFL, 0)) >= 0)
		fcntl(fileno(tracefile), F_SETFL, flags | O_APPEND);
#endif
	fputs("\nTracing started.\n", tracefile);
	fflush(tracefile);
D 3
#endif
E 3
I 3
#endif /* DEBUG */
E 3
}
E 1
