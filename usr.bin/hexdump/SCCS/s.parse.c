h17577
s 00002/00002/00479
d D 8.1 93/06/06 14:50:14 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00071/00075/00410
d D 5.7 92/07/14 14:30:37 bostic 7 6
c fix for quads; prototype and cleanup in general
e
s 00011/00020/00474
d D 5.6 91/03/09 08:27:28 bostic 6 5
c fixing hexdump without doing an extra strdup()
e
s 00006/00002/00488
d D 5.5 91/03/07 22:11:23 donn 5 4
c Change add() to copy strings.
e
s 00001/00011/00489
d D 5.4 90/06/01 16:52:44 bostic 4 3
c new copyright notice
e
s 00001/00001/00499
d D 5.3 90/05/15 19:59:38 bostic 3 2
c string.h is ANSI C include file
e
s 00017/00001/00483
d D 5.2 90/05/08 08:57:04 bostic 2 1
c add %l[dioux] support
e
s 00484/00000/00000
d D 5.1 89/08/29 18:36:26 bostic 1 0
c date and time created 89/08/29 18:36:26 by bostic
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 4
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
D 7
#include <sys/file.h>
E 7
I 7

#include <errno.h>
#include <fcntl.h>
E 7
#include <stdio.h>
I 6
#include <stdlib.h>
E 6
#include <ctype.h>
D 3
#include <strings.h>
E 3
I 3
#include <string.h>
E 3
#include "hexdump.h"

FU *endfu;					/* format at end-of-data */

I 7
void
E 7
addfile(name)
	char *name;
{
	register char *p;
	FILE *fp;
	int ch;
	char buf[2048 + 1];

D 7
	if (!(fp = fopen(name, "r"))) {
		(void)fprintf(stderr, "hexdump: can't read %s.\n", name);
		exit(1);
	}
E 7
I 7
	if ((fp = fopen(name, "r")) == NULL)
		err("%s: %s\n", name, strerror(errno));
E 7
	while (fgets(buf, sizeof(buf), fp)) {
		if (!(p = index(buf, '\n'))) {
			(void)fprintf(stderr, "hexdump: line too long.\n");
			while ((ch = getchar()) != '\n' && ch != EOF);
			continue;
		}
		*p = '\0';
		for (p = buf; *p && isspace(*p); ++p);
		if (!*p || *p == '#')
			continue;
		add(p);
	}
	(void)fclose(fp);
}

I 7
void
E 7
D 5
add(fmt)
	char *fmt;
E 5
I 5
D 6
add(xfmt)
	char *xfmt;
E 6
I 6
add(fmt)
	char *fmt;
E 6
E 5
{
	register char *p;
	static FS **nextfs;
	FS *tfs;
	FU *tfu, **nextfu;
D 6
	char savech, *savep, *emalloc(), *strdup();
I 5
	char *fmt;
E 6
I 6
D 7
	char *savep, *emalloc();
E 7
I 7
	char *savep;
E 7
E 6

D 6
	if ((fmt = strdup(xfmt)) == NULL)
		nomem();
E 5

E 6
	/* start new linked list of format units */
D 7
	/* NOSTRICT */
	tfs = (FS *)emalloc(sizeof(FS));
E 7
I 7
	tfs = emalloc(sizeof(FS));
E 7
	if (!fshead)
		fshead = tfs;
	else
		*nextfs = tfs;
	nextfs = &tfs->nextfs;
	nextfu = &tfs->nextfu;

	/* take the format string and break it up into format units */
	for (p = fmt;;) {
		/* skip leading white space */
		for (; isspace(*p); ++p);
		if (!*p)
			break;

		/* allocate a new format unit and link it in */
D 7
		/* NOSTRICT */
		tfu = (FU *)emalloc(sizeof(FU));
E 7
I 7
		tfu = emalloc(sizeof(FU));
E 7
		*nextfu = tfu;
		nextfu = &tfu->nextfu;
		tfu->reps = 1;

		/* if leading digit, repetition count */
		if (isdigit(*p)) {
			for (savep = p; isdigit(*p); ++p);
			if (!isspace(*p) && *p != '/')
				badfmt(fmt);
			/* may overwrite either white space or slash */
D 6
			savech = *p;
			*p = '\0';
E 6
			tfu->reps = atoi(savep);
			tfu->flags = F_SETREP;
D 6
			*p = savech;
E 6
			/* skip trailing white space */
			for (++p; isspace(*p); ++p);
		}

		/* skip slash and trailing white space */
		if (*p == '/')
			while (isspace(*++p));

		/* byte count */
		if (isdigit(*p)) {
			for (savep = p; isdigit(*p); ++p);
			if (!isspace(*p))
				badfmt(fmt);
D 6
			savech = *p;
			*p = '\0';
E 6
			tfu->bcnt = atoi(savep);
D 6
			*p = savech;
E 6
			/* skip trailing white space */
			for (++p; isspace(*p); ++p);
		}

		/* format */
		if (*p != '"')
			badfmt(fmt);
D 6
		for (savep = ++p; *p != '"'; ++p);
		if (*p != '"')
			badfmt(fmt);
		savech = *p;
		*p = '\0';
		if (!(tfu->fmt = strdup(savep)))
E 6
I 6
		for (savep = ++p; *p != '"';)
			if (*p++ == 0)
				badfmt(fmt);
		if (!(tfu->fmt = malloc(p - savep + 1)))
E 6
			nomem();
I 6
		(void) strncpy(tfu->fmt, savep, p - savep);
		tfu->fmt[p - savep] = '\0';
E 6
		escape(tfu->fmt);
D 6
		*p++ = savech;
E 6
I 6
		p++;
E 6
	}
}

static char *spec = ".#-+ 0123456789";
I 7

int
E 7
size(fs)
	FS *fs;
{
	register FU *fu;
	register int bcnt, cursize;
	register char *fmt;
	int prec;

	/* figure out the data block size needed for each format unit */
	for (cursize = 0, fu = fs->nextfu; fu; fu = fu->nextfu) {
		if (fu->bcnt) {
			cursize += fu->bcnt * fu->reps;
			continue;
		}
		for (bcnt = prec = 0, fmt = fu->fmt; *fmt; ++fmt) {
			if (*fmt != '%')
				continue;
			/*
			 * skip any special chars -- save precision in
			 * case it's a %s format.
			 */
			while (index(spec + 1, *++fmt));
			if (*fmt == '.' && isdigit(*++fmt)) {
				prec = atoi(fmt);
				while (isdigit(*++fmt));
			}
			switch(*fmt) {
			case 'c':
				bcnt += 1;
				break;
			case 'd': case 'i': case 'o': case 'u':
			case 'x': case 'X':
				bcnt += 4;
				break;
			case 'e': case 'E': case 'f': case 'g': case 'G':
				bcnt += 8;
				break;
			case 's':
				bcnt += prec;
				break;
			case '_':
				switch(*++fmt) {
				case 'c': case 'p': case 'u':
					bcnt += 1;
					break;
				}
			}
		}
		cursize += bcnt * fu->reps;
	}
D 7
	return(cursize);
E 7
I 7
	return (cursize);
E 7
}

I 7
void
E 7
rewrite(fs)
	FS *fs;
{
	enum { NOTOKAY, USEBCNT, USEPREC } sokay;
	register PR *pr, **nextpr;
	register FU *fu;
	register char *p1, *p2;
D 7
	char savech, *fmtp;
E 7
I 7
	char savech, *fmtp, cs[3];
E 7
	int nconv, prec;

	for (fu = fs->nextfu; fu; fu = fu->nextfu) {
		/*
D 7
		 * break each format unit into print units; each
		 * conversion character gets its own.
E 7
I 7
		 * Break each format unit into print units; each conversion
		 * character gets its own.
E 7
		 */
		for (nconv = 0, fmtp = fu->fmt; *fmtp; nextpr = &pr->nextpr) {
D 7
			/* NOSTRICT */
			pr = (PR *)emalloc(sizeof(PR));
E 7
I 7
			pr = emalloc(sizeof(PR));
E 7
			if (!fu->nextpr)
				fu->nextpr = pr;
			else
				*nextpr = pr;

D 7
			/* skip preceding text and up to the next % sign */
E 7
I 7
			/* Skip preceding text and up to the next % sign. */
E 7
			for (p1 = fmtp; *p1 && *p1 != '%'; ++p1);

D 7
			/* only text in the string */
E 7
I 7
			/* Only text in the string. */
E 7
			if (!*p1) {
				pr->fmt = fmtp;
				pr->flags = F_TEXT;
				break;
			}

			/*
D 7
			 * get precision for %s -- if have a byte count, don't
E 7
I 7
			 * Get precision for %s -- if have a byte count, don't
E 7
			 * need it.
			 */
			if (fu->bcnt) {
				sokay = USEBCNT;
D 7
				/* skip to conversion character */
E 7
I 7
				/* Skip to conversion character. */
E 7
				for (++p1; index(spec, *p1); ++p1);
			} else {
D 7
				/* skip any special chars, field width */
E 7
I 7
				/* Skip any special chars, field width. */
E 7
				while (index(spec + 1, *++p1));
				if (*p1 == '.' && isdigit(*++p1)) {
					sokay = USEPREC;
					prec = atoi(p1);
					while (isdigit(*++p1));
D 7
				}
				else
E 7
I 7
				} else
E 7
					sokay = NOTOKAY;
			}

D 7
			p2 = p1 + 1;		/* set end pointer */
E 7
I 7
			p2 = p1 + 1;		/* Set end pointer. */
			cs[0] = *p1;		/* Set conversion string. */
			cs[1] = '\0';
E 7

			/*
D 7
			 * figure out the byte count for each conversion;
E 7
I 7
			 * Figure out the byte count for each conversion;
E 7
			 * rewrite the format as necessary, set up blank-
			 * padding for end of data.
			 */
D 7
			switch(*p1) {
E 7
I 7
			switch(cs[0]) {
E 7
			case 'c':
				pr->flags = F_CHAR;
				switch(fu->bcnt) {
				case 0: case 1:
					pr->bcnt = 1;
					break;
				default:
					p1[1] = '\0';
					badcnt(p1);
				}
				break;
			case 'd': case 'i':
				pr->flags = F_INT;
D 7
				goto sw1;
I 2
			case 'l':
				++p2;
				switch(p1[1]) {
				case 'd': case 'i':
					++p1;
					pr->flags = F_INT;
					goto sw1;
				case 'o': case 'u': case 'x': case 'X':
					++p1;
					pr->flags = F_UINT;
					goto sw1;
				default:
					p1[2] = '\0';
					badconv(p1);
				}
				/* NOTREACHED */
E 7
I 7
				goto isint;
E 7
E 2
			case 'o': case 'u': case 'x': case 'X':
				pr->flags = F_UINT;
D 7
sw1:				switch(fu->bcnt) {
E 7
I 7
isint:				cs[2] = '\0';
				cs[1] = cs[0];
				cs[0] = 'q';
				switch(fu->bcnt) {
E 7
				case 0: case 4:
					pr->bcnt = 4;
					break;
				case 1:
					pr->bcnt = 1;
					break;
				case 2:
					pr->bcnt = 2;
					break;
				default:
					p1[1] = '\0';
					badcnt(p1);
				}
				break;
			case 'e': case 'E': case 'f': case 'g': case 'G':
				pr->flags = F_DBL;
				switch(fu->bcnt) {
				case 0: case 8:
					pr->bcnt = 8;
					break;
				case 4:
					pr->bcnt = 4;
					break;
				default:
					p1[1] = '\0';
					badcnt(p1);
				}
				break;
			case 's':
				pr->flags = F_STR;
				switch(sokay) {
				case NOTOKAY:
					badsfmt();
				case USEBCNT:
					pr->bcnt = fu->bcnt;
					break;
				case USEPREC:
					pr->bcnt = prec;
					break;
				}
				break;
			case '_':
				++p2;
				switch(p1[1]) {
				case 'A':
					endfu = fu;
					fu->flags |= F_IGNORE;
					/* FALLTHROUGH */
				case 'a':
					pr->flags = F_ADDRESS;
					++p2;
					switch(p1[2]) {
					case 'd': case 'o': case'x':
D 7
						*p1 = p1[2];
E 7
I 7
						cs[0] = 'q';
						cs[1] = p1[2];
						cs[2] = '\0';
E 7
						break;
					default:
						p1[3] = '\0';
						badconv(p1);
					}
					break;
				case 'c':
					pr->flags = F_C;
D 7
					/* *p1 = 'c';	set in conv_c */
					goto sw2;
E 7
I 7
					/* cs[0] = 'c';	set in conv_c */
					goto isint2;
E 7
				case 'p':
					pr->flags = F_P;
D 7
					*p1 = 'c';
					goto sw2;
E 7
I 7
					cs[0] = 'c';
					goto isint2;
E 7
				case 'u':
					pr->flags = F_U;
D 7
					/* *p1 = 'c';	set in conv_u */
sw2:					switch(fu->bcnt) {
E 7
I 7
					/* cs[0] = 'c';	set in conv_u */
isint2:					switch(fu->bcnt) {
E 7
					case 0: case 1:
						pr->bcnt = 1;
						break;
					default:
						p1[2] = '\0';
						badcnt(p1);
					}
					break;
				default:
					p1[2] = '\0';
					badconv(p1);
				}
				break;
			default:
				p1[1] = '\0';
				badconv(p1);
			}

			/*
D 7
			 * copy to PR format string, set conversion character
E 7
I 7
			 * Copy to PR format string, set conversion character
E 7
			 * pointer, update original.
			 */
			savech = *p2;
D 7
			p1[1] = '\0';
			if (!(pr->fmt = strdup(fmtp)))
				nomem();
E 7
I 7
			p1[0] = '\0';
			pr->fmt = emalloc(strlen(fmtp) + 2);
			(void)strcpy(pr->fmt, fmtp);
			(void)strcat(pr->fmt, cs);
E 7
			*p2 = savech;
			pr->cchar = pr->fmt + (p1 - fmtp);
			fmtp = p2;

D 7
			/* only one conversion character if byte count */
			if (!(pr->flags&F_ADDRESS) && fu->bcnt && nconv++) {
				(void)fprintf(stderr,
				    "hexdump: byte count with multiple conversion characters.\n");
				exit(1);
			}
E 7
I 7
			/* Only one conversion character if byte count. */
			if (!(pr->flags&F_ADDRESS) && fu->bcnt && nconv++)
	    err("byte count with multiple conversion characters");
E 7
		}
		/*
D 7
		 * if format unit byte count not specified, figure it out
E 7
I 7
		 * If format unit byte count not specified, figure it out
E 7
		 * so can adjust rep count later.
		 */
		if (!fu->bcnt)
			for (pr = fu->nextpr; pr; pr = pr->nextpr)
				fu->bcnt += pr->bcnt;
	}
	/*
D 7
	 * if the format string interprets any data at all, and it's
E 7
I 7
	 * If the format string interprets any data at all, and it's
E 7
	 * not the same as the blocksize, and its last format unit
	 * interprets any data at all, and has no iteration count,
	 * repeat it as necessary.
	 *
D 7
	 * if, rep count is greater than 1, no trailing whitespace
E 7
I 7
	 * If, rep count is greater than 1, no trailing whitespace
E 7
	 * gets output from the last iteration of the format unit.
	 */
	for (fu = fs->nextfu;; fu = fu->nextfu) {
		if (!fu->nextfu && fs->bcnt < blocksize &&
		    !(fu->flags&F_SETREP) && fu->bcnt)
			fu->reps += (blocksize - fs->bcnt) / fu->bcnt;
		if (fu->reps > 1) {
			for (pr = fu->nextpr;; pr = pr->nextpr)
				if (!pr->nextpr)
					break;
			for (p1 = pr->fmt, p2 = NULL; *p1; ++p1)
				p2 = isspace(*p1) ? p1 : NULL;
			if (p2)
				pr->nospace = p2;
		}
		if (!fu->nextfu)
			break;
	}
I 7
#ifdef DEBUG
	for (fu = fs->nextfu; fu; fu = fu->nextfu) {
		(void)printf("fmt:");
		for (pr = fu->nextpr; pr; pr = pr->nextpr)
			(void)printf(" {%s}", pr->fmt);
		(void)printf("\n");
	}
#endif
E 7
}

D 7

E 7
I 7
void
E 7
escape(p1)
	register char *p1;
{
	register char *p2;

	/* alphabetic escape sequences have to be done in place */
	for (p2 = p1;; ++p1, ++p2) {
		if (!*p1) {
			*p2 = *p1;
			break;
		}
		if (*p1 == '\\')
			switch(*++p1) {
			case 'a':
			     /* *p2 = '\a'; */
				*p2 = '\007';
				break;
			case 'b':
				*p2 = '\b';
				break;
			case 'f':
				*p2 = '\f';
				break;
			case 'n':
				*p2 = '\n';
				break;
			case 'r':
				*p2 = '\r';
				break;
			case 't':
				*p2 = '\t';
				break;
			case 'v':
				*p2 = '\v';
				break;
			default:
				*p2 = *p1;
				break;
			}
	}
}

I 7
void
E 7
badcnt(s)
	char *s;
{
D 7
	(void)fprintf(stderr,
	    "hexdump: bad byte count for conversion character %s.\n", s);
	exit(1);
E 7
I 7
	err("%s: bad byte count", s);
E 7
}

I 7
void
E 7
badsfmt()
{
D 7
	(void)fprintf(stderr,
	    "hexdump: %%s requires a precision or a byte count.\n");
	exit(1);
E 7
I 7
	err("%%s: requires a precision or a byte count\n");
E 7
}

I 7
void
E 7
badfmt(fmt)
	char *fmt;
{
D 7
	(void)fprintf(stderr, "hexdump: bad format {%s}\n", fmt);
	exit(1);
E 7
I 7
	err("\"%s\": bad format\n", fmt);
E 7
}

I 7
void
E 7
badconv(ch)
	char *ch;
{
D 2
	(void)fprintf(stderr, "hexdump: bad conversion character %s.\n", ch);
E 2
I 2
D 7
	(void)fprintf(stderr, "hexdump: bad conversion character %%%s.\n", ch);
E 2
	exit(1);
E 7
I 7
	err("%%%s: bad conversion character\n", ch);
E 7
}
E 1
