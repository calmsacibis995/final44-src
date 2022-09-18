h54099
s 00002/00002/00351
d D 8.1 93/06/06 14:49:51 bostic 16 15
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00345
d D 5.15 93/05/17 08:35:25 bostic 15 14
c convert to new basic integral types
e
s 00002/00002/00351
d D 5.14 93/03/04 12:18:48 bostic 14 13
c off_t's may not be quad_t's on all systems
e
s 00117/00105/00236
d D 5.13 92/07/14 14:30:31 bostic 13 12
c fix for quads; prototype and cleanup in general
e
s 00022/00015/00319
d D 5.12 92/01/08 08:29:52 bostic 12 11
c skip wasn't right if not a regular file
e
s 00002/00001/00332
d D 5.11 91/03/09 08:27:42 bostic 11 10
c don't redefine malloc
e
s 00001/00011/00332
d D 5.10 90/06/01 16:52:29 bostic 10 9
c new copyright notice
e
s 00005/00001/00338
d D 5.9 90/06/01 14:41:02 bostic 9 8
c check for errors from fread(3)
e
s 00001/00001/00338
d D 5.8 90/05/25 16:13:01 bostic 8 7
c address already set in get()
e
s 00001/00001/00338
d D 5.7 90/05/15 19:59:37 bostic 7 6
c string.h is ANSI C include file
e
s 00002/00000/00337
d D 5.6 90/05/08 08:56:16 bostic 6 5
c define vflag here
e
s 00007/00003/00330
d D 5.5 90/05/07 21:07:50 bostic 5 4
c fix bug so doesn't match first line in file of all NULL's
e
s 00006/00003/00327
d D 5.4 89/09/07 17:56:24 bostic 4 3
c if no data printed, don't print ending address
e
s 00020/00002/00310
d D 5.3 89/08/29 23:01:40 bostic 3 2
c remove rest of blank trimming; fold bpad.c into display.c
e
s 00084/00091/00228
d D 5.2 89/08/29 22:18:18 bostic 2 1
c trimming trailing blanks is too hard; the last revision handles most of the
c cases -- the one I quit on is where you have:
c 	"%06.6_ao "  12/1 "%3o "
c 	"\t\t" "%_p"
c 	"\n"
c You'd have to read-ahead and figure out what's going to be printed from
c future format strings to know if the current line should be blank padded.
e
s 00319/00000/00000
d D 5.1 89/08/29 18:36:16 bostic 1 0
c date and time created 89/08/29 18:36:16 by bostic
e
u
U
t
T
I 1
/*
D 16
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 16
I 16
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 16
 *
D 10
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
E 10
I 10
 * %sccs.include.redist.c%
E 10
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/stat.h>
I 13

E 13
#include <unistd.h>
I 5
#include <errno.h>
E 5
#include <ctype.h>
#include <stdio.h>
I 11
#include <stdlib.h>
E 11
D 7
#include <strings.h>
E 7
I 7
#include <string.h>
E 7
#include "hexdump.h"

I 6
enum _vflag vflag = FIRST;

E 6
static off_t address;			/* address/offset in stream */
static off_t eaddress;			/* end address */
D 12
static off_t savaddress;		/* saved address/offset in stream */
E 12

I 2
D 13
#define PRINT { \
	switch(pr->flags) { \
	case F_ADDRESS: \
		(void)printf(pr->fmt, address); \
		break; \
	case F_BPAD: \
		(void)printf(pr->fmt, ""); \
		break; \
	case F_C: \
		conv_c(pr, bp); \
		break; \
	case F_CHAR: \
		(void)printf(pr->fmt, *bp); \
		break; \
	case F_DBL: { \
		double dval; \
		float fval; \
		switch(pr->bcnt) { \
		case 4: \
			bcopy((char *)bp, (char *)&fval, sizeof(fval)); \
			(void)printf(pr->fmt, fval); \
			break; \
		case 8: \
			bcopy((char *)bp, (char *)&dval, sizeof(dval)); \
			(void)printf(pr->fmt, dval); \
			break; \
		} \
		break; \
	} \
	case F_INT: { \
		int ival; \
		short sval; \
		switch(pr->bcnt) { \
		case 1: \
			(void)printf(pr->fmt, (int)*bp); \
			break; \
		case 2: \
			bcopy((char *)bp, (char *)&sval, sizeof(sval)); \
			(void)printf(pr->fmt, (int)sval); \
			break; \
		case 4: \
			bcopy((char *)bp, (char *)&ival, sizeof(ival)); \
			(void)printf(pr->fmt, ival); \
			break; \
		} \
		break; \
	} \
	case F_P: \
		(void)printf(pr->fmt, isprint(*bp) ? *bp : '.'); \
		break; \
	case F_STR: \
		(void)printf(pr->fmt, (char *)bp); \
		break; \
	case F_TEXT: \
		(void)printf(pr->fmt); \
		break; \
	case F_U: \
		conv_u(pr, bp); \
		break; \
	case F_UINT: { \
		u_int ival; \
		u_short sval; \
		switch(pr->bcnt) { \
		case 1: \
			(void)printf(pr->fmt, (u_int)*bp); \
			break; \
		case 2: \
			bcopy((char *)bp, (char *)&sval, sizeof(sval)); \
			(void)printf(pr->fmt, (u_int)sval); \
			break; \
		case 4: \
			bcopy((char *)bp, (char *)&ival, sizeof(ival)); \
			(void)printf(pr->fmt, ival); \
			break; \
		} \
		break; \
	} \
	} \
}
E 13
I 13
static inline void print __P((PR *, u_char *));
E 13

I 13
void
E 13
E 2
display()
{
	extern FU *endfu;
	register FS *fs;
	register FU *fu;
	register PR *pr;
	register int cnt;
	register u_char *bp;
	off_t saveaddress;
D 13
	u_char savech, *savebp, *get();
E 13
I 13
	u_char savech, *savebp;
E 13

	while (bp = get())
	    for (fs = fshead, savebp = bp, saveaddress = address; fs;
D 2
		fs = fs->nextfs, bp = savebp, address = saveaddress) {
E 2
I 2
		fs = fs->nextfs, bp = savebp, address = saveaddress)
E 2
		    for (fu = fs->nextfu; fu; fu = fu->nextfu) {
			if (fu->flags&F_IGNORE)
				break;
			for (cnt = fu->reps; cnt; --cnt)
			    for (pr = fu->nextpr; pr; address += pr->bcnt,
				bp += pr->bcnt, pr = pr->nextpr) {
D 2
				    if (eaddress && address >= eaddress) {
					    bpad(fu, pr, bp);
					    goto nextfs;
				    }
E 2
I 2
D 3
				    if (eaddress && address >= eaddress)
					    bpad(fu, pr);
E 3
I 3
				    if (eaddress && address >= eaddress &&
D 13
					!(pr->flags&(F_TEXT|F_BPAD)))
E 13
I 13
					!(pr->flags & (F_TEXT|F_BPAD)))
E 13
					    bpad(pr);
E 3
E 2
				    if (cnt == 1 && pr->nospace) {
					savech = *pr->nospace;
					*pr->nospace = '\0';
				    }
D 2
				    print(pr, bp);
E 2
I 2
D 13
				    PRINT;
E 13
I 13
				    print(pr, bp);
E 13
E 2
				    if (cnt == 1 && pr->nospace)
					*pr->nospace = savech;
			    }
		    }
D 2
nextfs:		;
		}
E 2
	if (endfu) {
		/*
D 4
		 * if eaddress not set, file size was multiple of blocksize,
		 * and no partial block ever found.
E 4
I 4
D 13
		 * if eaddress not set, error or file size was multiple of
E 13
I 13
		 * If eaddress not set, error or file size was multiple of
E 13
		 * blocksize, and no partial block ever found.
E 4
		 */
D 4
		if (!eaddress)
E 4
I 4
		if (!eaddress) {
			if (!address)
				return;
E 4
D 8
			eaddress = address + blocksize; 
E 8
I 8
			eaddress = address;
E 8
I 4
		}
E 4
		for (pr = endfu->nextpr; pr; pr = pr->nextpr)
			switch(pr->flags) {
			case F_ADDRESS:
D 14
				(void)printf(pr->fmt, eaddress);
E 14
I 14
				(void)printf(pr->fmt, (quad_t)eaddress);
E 14
				break;
			case F_TEXT:
				(void)printf(pr->fmt);
				break;
			}
D 2
	}
}

print(pr, bp)
	PR *pr;
	u_char *bp;
{
	switch(pr->flags) {
	case F_ADDRESS:
		(void)printf(pr->fmt, address);
		break;
	case F_C:
		conv_c(pr, bp);
		break;
	case F_CHAR:
		(void)printf(pr->fmt, *bp);
		break;
	case F_DBL: {
		double dval;
		float fval;

		switch(pr->bcnt) {
		case 4:
			bcopy((char *)bp, (char *)&fval, sizeof(fval));
			(void)printf(pr->fmt, fval);
			break;
		case 8:
			bcopy((char *)bp, (char *)&dval, sizeof(dval));
			(void)printf(pr->fmt, dval);
			break;
		}
		break;
	}
	case F_INT: {
		int ival;
		short sval;

		switch(pr->bcnt) {
		case 1:
			(void)printf(pr->fmt, (int)*bp);
			break;
		case 2:
			bcopy((char *)bp, (char *)&sval, sizeof(sval));
			(void)printf(pr->fmt, (int)sval);
			break;
		case 4:
			bcopy((char *)bp, (char *)&ival, sizeof(ival));
			(void)printf(pr->fmt, ival);
			break;
		}
		break;
	}
	case F_P:
		(void)printf(pr->fmt, isprint(*bp) ? *bp : '.');
		break;
	case F_STR:
		(void)printf(pr->fmt, (char *)bp);
		break;
	case F_TEXT:
		(void)printf(pr->fmt);
		break;
	case F_U:
		conv_u(pr, bp);
		break;
	case F_UINT: {
		u_int ival;
		u_short sval;

		switch(pr->bcnt) {
		case 1:
			(void)printf(pr->fmt, (u_int)*bp);
			break;
		case 2:
			bcopy((char *)bp, (char *)&sval, sizeof(sval));
			(void)printf(pr->fmt, (u_int)sval);
			break;
		case 4:
			bcopy((char *)bp, (char *)&ival, sizeof(ival));
			(void)printf(pr->fmt, ival);
			break;
		}
		break;
	}
E 2
	}
I 3
}

I 13
static inline void
print(pr, bp)
	PR *pr;
	u_char *bp;
{
D 15
	f4byte_t f4;
	f8byte_t f8;
	s2byte_t s2;
	s4byte_t s4;
	s8byte_t s8;
	u2byte_t u2;
	u4byte_t u4;
	u8byte_t u8;
E 15
I 15
	   double f8;
	    float f4;
	  int16_t s2;
	   int8_t s8;
	  int32_t s4;
	u_int16_t u2;
	u_int32_t u4;
	u_int64_t u8;
E 15

	switch(pr->flags) {
	case F_ADDRESS:
D 14
		(void)printf(pr->fmt, address);
E 14
I 14
		(void)printf(pr->fmt, (quad_t)address);
E 14
		break;
	case F_BPAD:
		(void)printf(pr->fmt, "");
		break;
	case F_C:
		conv_c(pr, bp);
		break;
	case F_CHAR:
		(void)printf(pr->fmt, *bp);
		break;
	case F_DBL:
		switch(pr->bcnt) {
		case 4:
			bcopy(bp, &f4, sizeof(f4));
			(void)printf(pr->fmt, f4);
			break;
		case 8:
			bcopy(bp, &f8, sizeof(f8));
			(void)printf(pr->fmt, f8);
			break;
		}
		break;
	case F_INT:
		switch(pr->bcnt) {
		case 1:
			(void)printf(pr->fmt, (quad_t)*bp);
			break;
		case 2:
			bcopy(bp, &s2, sizeof(s2));
			(void)printf(pr->fmt, (quad_t)s2);
			break;
		case 4:
			bcopy(bp, &s4, sizeof(s4));
			(void)printf(pr->fmt, (quad_t)s4);
			break;
		case 8:
			bcopy(bp, &s8, sizeof(s8));
			(void)printf(pr->fmt, s8);
			break;
		}
		break;
	case F_P:
		(void)printf(pr->fmt, isprint(*bp) ? *bp : '.');
		break;
	case F_STR:
		(void)printf(pr->fmt, (char *)bp);
		break;
	case F_TEXT:
		(void)printf(pr->fmt);
		break;
	case F_U:
		conv_u(pr, bp);
		break;
	case F_UINT:
		switch(pr->bcnt) {
		case 1:
			(void)printf(pr->fmt, (u_quad_t)*bp);
			break;
		case 2:
			bcopy(bp, &u2, sizeof(u2));
			(void)printf(pr->fmt, (u_quad_t)u2);
			break;
		case 4:
			bcopy(bp, &u4, sizeof(u4));
			(void)printf(pr->fmt, (u_quad_t)u4);
			break;
		case 8:
			bcopy(bp, &u8, sizeof(u8));
			(void)printf(pr->fmt, u8);
			break;
		}
		break;
	}
}

void
E 13
bpad(pr)
	PR *pr;
{
	static char *spec = " -0+#";
	register char *p1, *p2;

	/*
D 13
	 * remove all conversion flags; '-' is the only one valid
E 13
I 13
	 * Remove all conversion flags; '-' is the only one valid
E 13
	 * with %s, and it's not useful here.
	 */
	pr->flags = F_BPAD;
D 13
	*pr->cchar = 's';
E 13
I 13
	pr->cchar[0] = 's';
	pr->cchar[1] = '\0';
E 13
	for (p1 = pr->fmt; *p1 != '%'; ++p1);
	for (p2 = ++p1; *p1 && index(spec, *p1); ++p1);
	while (*p2++ = *p1++);
E 3
}

I 9
static char **_argv;

E 9
u_char *
get()
{
	extern enum _vflag vflag;
	extern int length;
	static int ateof = 1;
	static u_char *curp, *savp;
	register int n;
	int need, nread;
	u_char *tmpp;

	if (!curp) {
D 13
		curp = (u_char *)emalloc(blocksize);
		savp = (u_char *)emalloc(blocksize);
E 13
I 13
		curp = emalloc(blocksize);
		savp = emalloc(blocksize);
E 13
	} else {
		tmpp = curp;
		curp = savp;
		savp = tmpp;
D 12
		address = savaddress += blocksize;
E 12
I 12
		address += blocksize;
E 12
	}
	for (need = blocksize, nread = 0;;) {
		/*
		 * if read the right number of bytes, or at EOF for one file,
		 * and no other files are available, zero-pad the rest of the
		 * block and set the end flag.
		 */
		if (!length || ateof && !next((char **)NULL)) {
			if (need == blocksize)
				return((u_char *)NULL);
			if (vflag != ALL && !bcmp(curp, savp, nread)) {
				if (vflag != DUP)
					(void)printf("*\n");
				return((u_char *)NULL);
			}
			bzero((char *)curp + nread, need);
			eaddress = address + nread;
			return(curp);
		}
		n = fread((char *)curp + nread, sizeof(u_char),
		    length == -1 ? need : MIN(length, need), stdin);
		if (!n) {
I 9
			if (ferror(stdin))
				(void)fprintf(stderr, "hexdump: %s: %s\n",
				    _argv[-1], strerror(errno));
E 9
			ateof = 1;
			continue;
		}
		ateof = 0;
		if (length != -1)
			length -= n;
		if (!(need -= n)) {
D 5
			if (vflag == ALL || bcmp(curp, savp, blocksize)) {
				if (vflag == DUP)
E 5
I 5
			if (vflag == ALL || vflag == FIRST ||
			    bcmp(curp, savp, blocksize)) {
				if (vflag == DUP || vflag == FIRST)
E 5
					vflag = WAIT;
				return(curp);
			}
			if (vflag == WAIT)
				(void)printf("*\n");
			vflag = DUP;
D 12
			address = savaddress += blocksize;
E 12
I 12
			address += blocksize;
E 12
			need = blocksize;
			nread = 0;
		}
		else
			nread += n;
	}
}

extern off_t skip;			/* bytes to skip */

I 13
int
E 13
next(argv)
	char **argv;
{
D 13
	extern int errno, exitval;
E 13
I 13
	extern int exitval;
E 13
	static int done;
D 9
	static char **_argv;
E 9
	int statok;

	if (argv) {
		_argv = argv;
		return(1);
	}
	for (;;) {
		if (*_argv) {
			if (!(freopen(*_argv, "r", stdin))) {
				(void)fprintf(stderr, "hexdump: %s: %s\n",
				    *_argv, strerror(errno));
				exitval = 1;
				++_argv;
				continue;
			}
			statok = done = 1;
		} else {
			if (done++)
				return(0);
			statok = 0;
		}
		if (skip)
			doskip(statok ? *_argv : "stdin", statok);
		if (*_argv)
			++_argv;
		if (!skip)
			return(1);
	}
	/* NOTREACHED */
}

I 13
void
E 13
doskip(fname, statok)
	char *fname;
	int statok;
{
D 12
	extern int errno;
	struct stat sbuf;
E 12
I 12
	register int cnt;
	struct stat sb;
E 12

	if (statok) {
D 12
		if (fstat(fileno(stdin), &sbuf)) {
E 12
I 12
D 13
		if (fstat(fileno(stdin), &sb)) {
E 12
			(void)fprintf(stderr, "hexdump: %s: %s.\n",
			    fname, strerror(errno));
			exit(1);
		}
E 13
I 13
		if (fstat(fileno(stdin), &sb))
			err("%s: %s", fname, strerror(errno));
E 13
D 12
		if (skip >= sbuf.st_size) {
			skip -= sbuf.st_size;
			address += sbuf.st_size;
E 12
I 12
		if (S_ISREG(sb.st_mode) && skip >= sb.st_size) {
			address += sb.st_size;
			skip -= sb.st_size;
E 12
			return;
		}
	}
D 12
	if (fseek(stdin, skip, SEEK_SET)) {
		(void)fprintf(stderr, "hexdump: %s: %s.\n",
		    fname, strerror(errno));
		exit(1);
E 12
I 12
	if (S_ISREG(sb.st_mode)) {
D 13
		if (fseek(stdin, skip, SEEK_SET)) {
			(void)fprintf(stderr, "hexdump: %s: %s.\n",
			    fname, strerror(errno));
			exit(1);
		}
E 13
I 13
		if (fseek(stdin, skip, SEEK_SET))
			err("%s: %s", fname, strerror(errno));
E 13
		address += skip;
		skip = 0;
	} else {
		for (cnt = 0; cnt < skip; ++cnt)
			if (getchar() == EOF)
				break;
		address += cnt;
		skip -= cnt;
E 12
	}
D 12
	savaddress = address += skip;
	skip = 0;
E 12
}

D 13
char *
E 13
I 13
void *
E 13
emalloc(size)
	int size;
{
D 11
	char *p, *malloc();
E 11
I 11
D 13
	char *p;
E 13
I 13
	void *p;
E 13
E 11

D 13
	if (!(p = malloc((u_int)size)))
E 13
I 13
	if ((p = malloc((u_int)size)) == NULL)
E 13
		nomem();
	bzero(p, size);
	return(p);
}

I 13
void
E 13
nomem()
{
D 5
	(void)fprintf(stderr, "hexdump: out of memory.\n");
E 5
I 5
D 13
	extern int errno;

	(void)fprintf(stderr, "hexdump: %s.\n", strerror(errno));
E 5
	exit(1);
E 13
I 13
	err("%s", strerror(errno));
E 13
}
E 1
