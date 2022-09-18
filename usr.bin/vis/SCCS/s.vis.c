h57143
s 00005/00005/00142
d D 8.1 93/06/06 22:22:13 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00012/00145
d D 5.1 91/04/18 18:41:31 bostic 3 2
c yank to 5.1, new copyright; att/bsd/shared
e
s 00061/00099/00096
d D 1.2 90/06/29 00:41:20 marc 2 1
c cencode -> vis; rewrite
e
s 00195/00000/00000
d D 1.1 90/05/15 14:27:54 marc 1 0
c date and time created 90/05/15 14:27:54 by marc
e
u
U
t
T
I 1
D 3
/*
E 3
I 3
/*-
E 3
D 4
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
D 4
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <stdio.h>
D 2
#include <cencode.h>
E 2
I 2
#include <vis.h>
E 2

D 2
int eflags, dflags, invert, strip, fold, foldwidth=80, none;
E 2
I 2
int eflags, fold, foldwidth=80, none, markeol, debug;
E 2

main(argc, argv) 
	char *argv[];
{
	extern char *optarg;
	extern int optind;
	extern int errno;
	FILE *fp;
	int ch;

D 2
	while ((ch = getopt(argc, argv, "nwcgovishfF:")) != EOF)
E 2
I 2
	while ((ch = getopt(argc, argv, "nwctsobfF:ld")) != EOF)
E 2
		switch((char)ch) {
		case 'n':
			none++;
			break;
		case 'w':
D 2
			eflags |= CENC_WHITE;
E 2
I 2
			eflags |= VIS_WHITE;
E 2
			break;
		case 'c':
D 2
			eflags |= CENC_CSTYLE;
E 2
I 2
			eflags |= VIS_CSTYLE;
E 2
			break;
D 2
		case 'g':
			eflags |= CENC_GRAPH;
E 2
I 2
		case 't':
			eflags |= VIS_TAB;
E 2
			break;
I 2
		case 's':
			eflags |= VIS_SAFE;
			break;
E 2
		case 'o':
D 2
			eflags |= CENC_OCTAL;
E 2
I 2
			eflags |= VIS_OCTAL;
E 2
			break;
D 2
		case 'v':	/* vis -v considered harmful */
			eflags |= CENC_GRAPH | CENC_OCTAL;
E 2
I 2
		case 'b':
			eflags |= VIS_NOSLASH;
E 2
			break;
D 2
		case 'i':
			invert++;
			break;
E 2
		case 'F':
			if ((foldwidth = atoi(optarg))<5) {
				fprintf(stderr, 
D 2
				 "vis: can't fold lines to less than 2 cols\n");
E 2
I 2
				 "vis: can't fold lines to less than 5 cols\n");
E 2
				exit(1);
			}
			/*FALLTHROUGH*/
		case 'f':
			fold++;		/* fold output lines to 80 cols */
			break;		/* using hidden newline */
D 2
		case 's':
			strip++;
E 2
I 2
		case 'l':
			markeol++;	/* mark end of line with \$ */
E 2
			break;
D 2
		case 'h':
			dflags |= CDEC_HAT;
E 2
I 2
#ifdef DEBUG
		case 'd':
			debug++;
E 2
			break;
I 2
#endif
E 2
		case '?':
		default:
			fprintf(stderr, 
D 2
		"usage: vis [-nwcgovifsh] [-F foldwidth]\n");
E 2
I 2
		"usage: vis [-nwctsobf] [-F foldwidth]\n");
E 2
			exit(1);
		}
	argc -= optind;
	argv += optind;

D 2
#define ALL	(CENC_CSTYLE | CENC_GRAPH | CENC_OCTAL)
	if (none)
		eflags &= ~ALL;
	else if (!(eflags&ALL))
		eflags |= ALL;
E 2
	if (*argv)
		while (*argv) {
			if ((fp=fopen(*argv, "r")) != NULL)
				process(fp, *argv);
			else
				fprintf(stderr, "vis: %s: %s\n", *argv,
				    (char *)strerror(errno));
			argv++;
		}
	else
		process(stdin, "<stdin>");
	exit(0);
}
	
process(fp, filename)
	FILE *fp;
	char *filename;
{
	static int col = 0;
D 2
	register char *cp = "X"+1;	/* so *(cp-1) starts out != '\n' */
	register int byte = 0;
E 2
I 2
	register char *cp = "\0"+1;	/* so *(cp-1) starts out != '\n' */
E 2
	register int c, rachar; 
	register char nc;
I 2
	char buff[5];
E 2
	
D 2
	/*
	 * Encode
	 */
	if (!invert) {
		c = getc(fp);
		while (c != EOF) {
			rachar = getc(fp);
			if (strip)
				c &= 0177;
			cp = cencode((char)c, eflags|CENC_RACHAR, (char)rachar);
			if (fold) {
				/*
				 * Keep track of printables and
				 * space chars (like fold(1)).
				 */
				for (;;) {
					switch(*cp) {
					case '\n':
					case '\r':
						col = 0;
						break;
					case '\t':
						col = col + 8 &~ 07;
						break;
					case '\b':
						col = col ? col - 1 : 0;
						break;
					default:
						col += strlen(cp);
					}
					if (col > (foldwidth-2)) {
						printf("\\\n");
						col = 0;
					} else
						break;
				}
			}
			do {
				putchar(*cp++);
			} while (*cp);
			c = rachar;
E 2
I 2
	c = getc(fp);
	while (c != EOF) {
		rachar = getc(fp);
		if (none) {
			cp = buff;
			*cp++ = c;
			if (c == '\\')
				*cp++ = '\\';
			*cp = '\0';
		} else if (markeol && c == '\n') {
			cp = buff;
			if ((eflags & VIS_NOSLASH) == 0)
				*cp++ = '\\';
			*cp++ = '$';
			*cp++ = '\n';
			*cp = '\0';
		} else 
			(void) vis(buff, (char)c, eflags, (char)rachar);

		cp = buff;
		if (fold) {
#ifdef DEBUG
			if (debug)
				printf("<%02d,", col);
#endif
			col = foldit(cp, col, foldwidth);
#ifdef DEBUG
			if (debug)
				printf("%02d>", col);
#endif
E 2
		}
D 2
		if (fold && *(cp-1) != '\n')
			printf("\\\n");
E 2
I 2
		do {
			putchar(*cp);
		} while (*++cp);
		c = rachar;
	}
E 2
	/*
D 2
	 * Decode
E 2
I 2
	 * terminate partial line with a hidden newline
E 2
	 */
D 2
	} else {
		while ((c = getc(fp)) != EOF) {
			byte++;
		again:
			switch(cdecode((char)c, &nc, dflags)) {
			case CDEC_NEEDMORE:
			case CDEC_NOCHAR:
				break;
			case CDEC_OK:
				putchar(nc);
				break;
			case CDEC_OKPUSH:
				putchar(nc);
				goto again;
			case CDEC_SYNBAD:
				fprintf(stderr, 
				    "vis: %s: offset: %d: can't decode\n", 
				    filename, byte);
				break;
			default:
				fprintf(stderr,
				    "vis: bad return value (can't happen)\n");
				exit(1);
			}
		}
		if (cdecode((char)0, &nc, CDEC_END) == CDEC_OK)
			putchar(nc);
	}
	exit(0);
E 2
I 2
	if (fold && *(cp-1) != '\n')
		printf("\\\n");
E 2
}
E 1
