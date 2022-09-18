h19144
s 00005/00005/00440
d D 8.1 93/06/09 22:58:05 bostic 12 11
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00020/00435
d D 5.7 91/02/26 14:57:15 bostic 11 10
c ANSI fixes
e
s 00001/00011/00454
d D 5.6 90/06/01 16:12:51 bostic 10 9
c new copyright notice
e
s 00004/00003/00461
d D 5.5 89/05/10 22:31:30 bostic 9 8
c file reorg, pathnames.h, paths.h
e
s 00017/00006/00447
d D 5.4 88/09/15 14:43:58 bostic 8 6
c add Berkeley specific copyright
e
s 00041/00004/00449
d R 5.4 87/04/29 17:35:59 bostic 7 6
c bug report 4.2BSD/ucb/196
e
s 00013/00019/00440
d D 5.3 86/01/13 20:30:09 mckusick 6 5
c check return values from memory allocation (from sun!gorodish!guy)
e
s 00019/00006/00440
d D 5.2 85/06/18 18:27:21 bloom 5 4
c fix problems with multiple line strings
e
s 00016/00001/00430
d D 5.1 85/05/31 09:41:09 dist 4 3
c Add copyright
e
s 00002/00000/00429
d D 4.3 82/06/27 10:33:14 root 3 2
c error exit inserted
e
s 00001/00001/00428
d D 4.2 81/05/07 22:07:14 mark 2 1
c made more portable by using "r+" to fopen, not "a"
e
s 00429/00000/00000
d D 4.1 80/10/01 17:29:45 bill 1 0
c date and time created 80/10/01 17:29:45 by bill
e
u
U
t
T
I 1
D 4
static char *sccsid = "%W% (Berkeley) %G%";
E 4
I 4
/*
D 8
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 8
I 8
D 12
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 12
I 12
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 12
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 10
I 10
 * %sccs.include.redist.c%
E 10
E 8
 */

#ifndef lint
D 12
char copyright[] =
D 8
"%Z% Copyright (c) 1980 Regents of the University of California.\n\
E 8
I 8
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
E 8
 All rights reserved.\n";
E 12
I 12
static char copyright[] =
"%Z% Copyright (c) 1980, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 12
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 8
#endif not lint
E 8
I 8
#endif /* not lint */
E 8

E 4
D 9
#include <stdio.h>
#include <ctype.h>
E 9
#include <sys/types.h>
#include <signal.h>
I 11
#include <errno.h>
#include <unistd.h>
E 11
I 9
#include <stdio.h>
#include <ctype.h>
I 11
#include <string.h>
E 11
#include "pathnames.h"
E 9

/*
 * xstr - extract and hash strings in a C program
 *
 * Bill Joy UCB
 * November, 1978
 */

D 6
#define	ignore(a)	Ignore((char *) a)
E 6
I 6
#define	ignore(a)	((void) a)
E 6

D 11
char	*calloc();
E 11
off_t	tellpt;
off_t	hashit();
D 11
char	*mktemp();
int	onintr();
E 11
I 11
void	onintr();
E 11
char	*savestr();
D 11
char	*strcat();
char	*strcpy();
E 11
off_t	yankstr();

off_t	mesgpt;
char	*strings =	"strings";

int	cflg;
int	vflg;
int	readstd;

main(argc, argv)
	int argc;
	char *argv[];
{

	argc--, argv++;
	while (argc > 0 && argv[0][0] == '-') {
		register char *cp = &(*argv++)[1];

		argc--;
		if (*cp == 0) {
			readstd++;
			continue;
		}
		do switch (*cp++) {

		case 'c':
			cflg++;
			continue;

		case 'v':
			vflg++;
			continue;

		default:
			fprintf(stderr, "usage: xstr [ -v ] [ -c ] [ - ] [ name ... ]\n");
		} while (*cp);
	}
	if (signal(SIGINT, SIG_IGN) == SIG_DFL)
		signal(SIGINT, onintr);
	if (cflg || argc == 0 && !readstd)
		inithash();
	else
D 9
		strings = mktemp(savestr("/tmp/xstrXXXXXX"));
E 9
I 9
D 11
		strings = mktemp(savestr(_PATH_TMP));
E 11
I 11
		strings = mktemp(strdup(_PATH_TMP));
E 11
E 9
	while (readstd || argc > 0) {
		if (freopen("x.c", "w", stdout) == NULL)
			perror("x.c"), exit(1);
		if (!readstd && freopen(argv[0], "r", stdin) == NULL)
			perror(argv[0]), exit(2);
		process("x.c");
		if (readstd == 0)
			argc--, argv++;
		else
			readstd = 0;
	};
	flushsh();
	if (cflg == 0)
		xsdotc();
	if (strings[0] == '/')
		ignore(unlink(strings));
	exit(0);
}

I 5
char linebuf[BUFSIZ];

E 5
process(name)
	char *name;
{
	char *cp;
D 5
	char linebuf[BUFSIZ];
E 5
	register int c;
	register int incomm = 0;
I 5
	int ret;
E 5

D 5
	printf("char\txstr[];\n");
E 5
I 5
	printf("extern char\txstr[];\n");
E 5
	for (;;) {
		if (fgets(linebuf, sizeof linebuf, stdin) == NULL) {
			if (ferror(stdin)) {
				perror(name);
				exit(3);
			}
			break;
		}
		if (linebuf[0] == '#') {
			if (linebuf[1] == ' ' && isdigit(linebuf[2]))
				printf("#line%s", &linebuf[1]);
			else
				printf("%s", linebuf);
			continue;
		}
		for (cp = linebuf; c = *cp++;) switch (c) {
			
		case '"':
			if (incomm)
				goto def;
D 5
			printf("(&xstr[%d])", (int) yankstr(&cp));
E 5
I 5
			if ((ret = (int) yankstr(&cp)) == -1)
				goto out;
			printf("(&xstr[%d])", ret);
E 5
			break;

		case '\'':
			if (incomm)
				goto def;
			putchar(c);
			if (*cp)
				putchar(*cp++);
			break;

		case '/':
			if (incomm || *cp != '*')
				goto def;
			incomm = 1;
			cp++;
			printf("/*");
			continue;

		case '*':
			if (incomm && *cp == '/') {
				incomm = 0;
				cp++;
				printf("*/");
				continue;
			}
			goto def;
		
def:
		default:
			putchar(c);
			break;
		}
	}
I 5
out:
E 5
	if (ferror(stdout))
		perror("x.c"), onintr();
}

off_t
yankstr(cpp)
	register char **cpp;
{
	register char *cp = *cpp;
	register int c, ch;
	char dbuf[BUFSIZ];
	register char *dp = dbuf;
	register char *tp;

	while (c = *cp++) {
		switch (c) {

		case '"':
			cp++;
			goto out;

		case '\\':
			c = *cp++;
			if (c == 0)
				break;
D 5
			if (c == '\n')
E 5
I 5
			if (c == '\n') {
				if (fgets(linebuf, sizeof linebuf, stdin) 
				    == NULL) {
					if (ferror(stdin)) {
						perror("x.c");
						exit(3);
					}
					return(-1);
				}
				cp = linebuf;
E 5
				continue;
I 5
			}
E 5
			for (tp = "b\bt\tr\rn\nf\f\\\\\"\""; ch = *tp++; tp++)
				if (c == ch) {
					c = *tp;
					goto gotc;
				}
			if (!octdigit(c)) {
				*dp++ = '\\';
				break;
			}
			c -= '0';
			if (!octdigit(*cp))
				break;
			c <<= 3, c += *cp++ - '0';
			if (!octdigit(*cp))
				break;
			c <<= 3, c += *cp++ - '0';
			break;
		}
gotc:
		*dp++ = c;
	}
out:
	*cpp = --cp;
	*dp = 0;
	return (hashit(dbuf, 1));
}

octdigit(c)
	char c;
{

	return (isdigit(c) && c != '8' && c != '9');
}

inithash()
{
	char buf[BUFSIZ];
	register FILE *mesgread = fopen(strings, "r");

	if (mesgread == NULL)
		return;
	for (;;) {
		mesgpt = tellpt;
		if (fgetNUL(buf, sizeof buf, mesgread) == NULL)
			break;
		ignore(hashit(buf, 0));
	}
	ignore(fclose(mesgread));
}

fgetNUL(obuf, rmdr, file)
	char *obuf;
	register int rmdr;
	FILE *file;
{
	register c;
	register char *buf = obuf;

	while (--rmdr > 0 && (c = xgetc(file)) != 0 && c != EOF)
		*buf++ = c;
	*buf++ = 0;
	return ((feof(file) || ferror(file)) ? NULL : 1);
}

xgetc(file)
	FILE *file;
{

	tellpt++;
	return (getc(file));
}

#define	BUCKETS	128

struct	hash {
	off_t	hpt;
	char	*hstr;
	struct	hash *hnext;
	short	hnew;
} bucket[BUCKETS];

off_t
hashit(str, new)
	char *str;
	int new;
{
	int i;
	register struct hash *hp, *hp0;

	hp = hp0 = &bucket[lastchr(str) & 0177];
	while (hp->hnext) {
		hp = hp->hnext;
		i = istail(str, hp->hstr);
		if (i >= 0)
			return (hp->hpt + i);
	}
D 6
	hp = (struct hash *) calloc(1, sizeof (*hp));
E 6
I 6
	if ((hp = (struct hash *) calloc(1, sizeof (*hp))) == NULL) {
		perror("xstr");
		exit(8);
	}
E 6
	hp->hpt = mesgpt;
D 11
	hp->hstr = savestr(str);
E 11
I 11
	if (!(hp->hstr = strdup(str))) {
		(void)fprintf(stderr, "xstr: %s\n", strerror(errno));
		exit(1);
	}
E 11
	mesgpt += strlen(hp->hstr) + 1;
	hp->hnext = hp0->hnext;
	hp->hnew = new;
	hp0->hnext = hp;
	return (hp->hpt);
}

flushsh()
{
	register int i;
	register struct hash *hp;
	register FILE *mesgwrit;
	register int old = 0, new = 0;

	for (i = 0; i < BUCKETS; i++)
		for (hp = bucket[i].hnext; hp != NULL; hp = hp->hnext)
			if (hp->hnew)
				new++;
			else
				old++;
	if (new == 0 && old != 0)
		return;
D 2
	mesgwrit = fopen(strings, old ? "a" : "w");
E 2
I 2
	mesgwrit = fopen(strings, old ? "r+" : "w");
I 3
	if (mesgwrit == NULL)
		perror(strings), exit(4);
E 3
E 2
	for (i = 0; i < BUCKETS; i++)
		for (hp = bucket[i].hnext; hp != NULL; hp = hp->hnext) {
			found(hp->hnew, hp->hpt, hp->hstr);
			if (hp->hnew) {
				fseek(mesgwrit, hp->hpt, 0);
				ignore(fwrite(hp->hstr, strlen(hp->hstr) + 1, 1, mesgwrit));
				if (ferror(mesgwrit))
					perror(strings), exit(4);
			}
		}
D 6
	ignore(fclose(mesgwrit));
E 6
I 6
	if (fclose(mesgwrit) == EOF)
		perror(strings), exit(4);
E 6
}

found(new, off, str)
	int new;
	off_t off;
	char *str;
{
D 5
	register char *cp;

E 5
	if (vflg == 0)
		return;
	if (!new)
		fprintf(stderr, "found at %d:", (int) off);
	else
		fprintf(stderr, "new at %d:", (int) off);
	prstr(str);
	fprintf(stderr, "\n");
}

prstr(cp)
	register char *cp;
{
	register int c;

	while (c = (*cp++ & 0377))
		if (c < ' ')
			fprintf(stderr, "^%c", c + '`');
		else if (c == 0177)
			fprintf(stderr, "^?");
		else if (c > 0200)
			fprintf(stderr, "\\%03o", c);
		else
			fprintf(stderr, "%c", c);
}

xsdotc()
{
	register FILE *strf = fopen(strings, "r");
	register FILE *xdotcf;

	if (strf == NULL)
		perror(strings), exit(5);
	xdotcf = fopen("xs.c", "w");
	if (xdotcf == NULL)
		perror("xs.c"), exit(6);
	fprintf(xdotcf, "char\txstr[] = {\n");
	for (;;) {
		register int i, c;

		for (i = 0; i < 8; i++) {
			c = getc(strf);
			if (ferror(strf)) {
				perror(strings);
				onintr();
			}
			if (feof(strf)) {
				fprintf(xdotcf, "\n");
				goto out;
			}
			fprintf(xdotcf, "0x%02x,", c);
		}
		fprintf(xdotcf, "\n");
	}
out:
	fprintf(xdotcf, "};\n");
	ignore(fclose(xdotcf));
	ignore(fclose(strf));
}

D 11
char *
savestr(cp)
	register char *cp;
{
D 6
	register char *dp = (char *) calloc(1, strlen(cp) + 1);
E 6
I 6
	register char *dp;
E 6

I 6
	if ((dp = (char *) calloc(1, strlen(cp) + 1)) == NULL) {
		perror("xstr");
		exit(8);
	}
E 6
	return (strcpy(dp, cp));
}

E 11
D 6
Ignore(a)
	char *a;
{

	a = a;
}

ignorf(a)
	int (*a)();
{

	a = a;
}

E 6
lastchr(cp)
	register char *cp;
{

	while (cp[0] && cp[1])
		cp++;
	return (*cp);
}

istail(str, of)
	register char *str, *of;
{
	register int d = strlen(of) - strlen(str);

	if (d < 0 || strcmp(&of[d], str) != 0)
		return (-1);
	return (d);
}

I 11
void
E 11
onintr()
{

D 6
	ignorf(signal(SIGINT, SIG_IGN));
E 6
I 6
	ignore(signal(SIGINT, SIG_IGN));
E 6
	if (strings[0] == '/')
		ignore(unlink(strings));
	ignore(unlink("x.c"));
	ignore(unlink("xs.c"));
	exit(7);
}
E 1
