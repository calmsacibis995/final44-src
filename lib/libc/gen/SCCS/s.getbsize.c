h30682
s 00002/00002/00078
d D 8.1 93/06/04 12:02:06 bostic 7 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00078
d R 8.1 93/05/31 14:24:11 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00008/00074
d D 5.5 93/04/28 17:28:28 bostic 5 4
c use err/warn(3); getbsize no longer needs the program name
e
s 00002/00001/00080
d D 5.4 92/10/17 15:06:27 bostic 4 3
c snprintf returns printed length, not actual length
e
s 00044/00040/00037
d D 5.3 92/03/09 14:37:52 bostic 3 2
c do it right, from Chris Torek
e
s 00002/00001/00075
d D 5.2 92/03/09 14:31:34 bostic 2 1
c make block size a long
e
s 00076/00000/00000
d D 5.1 92/03/01 16:59:09 bostic 1 0
c date and time created 92/03/01 16:59:09 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

I 5
#include <err.h>
E 5
#include <stdio.h>
#include <stdlib.h>
I 5
#include <string.h>
E 5

char *
D 5
getbsize(prog, headerlenp, blocksizep)
	char *prog;
E 5
I 5
getbsize(headerlenp, blocksizep)
E 5
D 2
	int *headerlenp, *blocksizep;
E 2
I 2
	int *headerlenp;
	long *blocksizep;
E 2
{
	static char header[20];
D 3
	long blocksize;
	char *ep, *p;
E 3
I 3
	long n, max, mul, blocksize;
	char *ep, *p, *form;
E 3

D 3
#define	Kb	1024
#define	Mb	1048576
#define	Gb	1073741824
E 3
I 3
#define	KB	(1024L)
#define	MB	(1024L * 1024L)
#define	GB	(1024L * 1024L * 1024L)
#define	MAXB	GB		/* No tera, peta, nor exa. */
	form = "";
E 3
	if ((p = getenv("BLOCKSIZE")) != NULL && *p != '\0') {
D 3
		blocksize = strtol(p, &ep, 10);
		switch(*ep) {
E 3
I 3
		if ((n = strtol(p, &ep, 10)) < 0)
			goto underflow;
		if (n == 0)
			n = 1;
		if (*ep && ep[1])
			goto fmterr;
		switch (*ep) {
E 3
		case 'G': case 'g':
D 3
			if (ep[1])
				goto fmterr;
			if (blocksize > 1)
				goto overflow;
			*headerlenp = snprintf(header, sizeof(header),
			    "%dG-blocks", blocksize);
			*blocksizep = blocksize * Gb;
			return (header);
		case 'M': case 'm':
			if (ep[1])
				goto fmterr;
			*headerlenp = snprintf(header, sizeof(header),
			    "%dM-blocks", blocksize);
			*blocksizep = blocksize * Mb;
			return (header);
E 3
I 3
			form = "G";
			max = MAXB / GB;
			mul = GB;
			break;
E 3
		case 'K': case 'k':
D 3
			if (ep[1])
				goto fmterr;
			*headerlenp = snprintf(header, sizeof(header),
			    "%dK-blocks", blocksize);
			*blocksizep = blocksize * Kb;
			return (header);
E 3
I 3
			form = "K";
			max = MAXB / KB;
			mul = KB;
			break;
		case 'M': case 'm':
			form = "M";
			max = MAXB / MB;
			mul = MB;
			break;
E 3
		case '\0':
D 3
			if (blocksize > Gb) {
overflow:			(void)fprintf(stderr,
				    "%s: maximum blocksize is 1G\n", prog);
				blocksize = 512;
			} else if (blocksize < 512) {
				(void)fprintf(stderr,
				    "%s: minimum blocksize is 512\n", prog);
				blocksize = 512;
			}
E 3
I 3
			max = MAXB;
			mul = 1;
E 3
			break;
		default:
D 5
fmterr:			(void)fprintf(stderr,
			    "%s: %s: unknown blocksize\n", prog, p);
E 5
I 5
fmterr:			warnx("%s: unknown blocksize", p);
E 5
D 3
			blocksize = 512;
E 3
I 3
			n = 512;
			mul = 1;
E 3
			break;
		}
I 3
		if (n > max) {
D 5
			(void)fprintf(stderr,
			    "%s: maximum blocksize is %dG\n", prog, MAXB / GB);
E 5
I 5
			warnx("maximum blocksize is %dG", MAXB / GB);
E 5
			n = max;
		}
		if ((blocksize = n * mul) < 512) {
D 5
underflow:		(void)fprintf(stderr,
			    "%s: minimum blocksize is 512\n", prog);
E 5
I 5
underflow:		warnx("minimum blocksize is 512");
E 5
			form = "";
			blocksize = n = 512;
		}
E 3
	} else
D 3
		blocksize = 512;
E 3
I 3
		blocksize = n = 512;
E 3

D 3
	*headerlenp = snprintf(header, sizeof(header), "%d-blocks", blocksize);
E 3
I 3
D 4
	*headerlenp = snprintf(header, sizeof(header), "%d%s-blocks", n, form);
E 4
I 4
	(void)snprintf(header, sizeof(header), "%d%s-blocks", n, form);
	*headerlenp = strlen(header);
E 4
E 3
	*blocksizep = blocksize;
	return (header);
}
E 1
