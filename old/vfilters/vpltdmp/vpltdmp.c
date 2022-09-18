/*
 * Copyright (c) 1981 Regents of the University of California.
 * All rights reserved.
 *
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
 */

#ifndef lint
char copyright[] =
"@(#) Copyright (c) 1981 Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "@(#)vpltdmp.c	5.4 (Berkeley) 6/1/90";
#endif /* not lint */

/*
 *  reads raster file created by vplot and dumps it onto the
 *  Varian or Versatec plotter.
 *  Input comes from file descriptor 0, output is to file descriptor 1.
 */
#include <stdio.h>
#include <sys/vcmd.h>

#define IN	0
#define OUT	1

static	char *Sid = "@(#)vpltdmp.c	5.4\t6/1/90";

int	plotmd[] = { VPLOT };
int	prtmd[]  = { VPRINT };

char	buf[BUFSIZ];		/* output buffer */

int	lines;			/* number of raster lines printed */
int	varian;			/* 0 for versatec, 1 for varian. */
int	BYTES_PER_LINE;		/* number of bytes per raster line. */
int	PAGE_LINES;		/* number of raster lines per page. */

char	*name, *host, *acctfile;

main(argc, argv)
	int argc;
	char *argv[];
{
	register int n;

	while (--argc) {
		if (**++argv == '-') {
			switch (argv[0][1]) {
			case 'x':
				BYTES_PER_LINE = atoi(&argv[0][2]) / 8;
				varian = BYTES_PER_LINE == 264;
				break;

			case 'y':
				PAGE_LINES = atoi(&argv[0][2]);
				break;

			case 'n':
				argc--;
				name = *++argv;
				break;

			case 'h':
				argc--;
				host = *++argv;
			}
		} else
			acctfile = *argv;
	}

	n = putplot();

	ioctl(OUT, VSETSTATE, prtmd);
	if (varian)
		write(OUT, "\f", 2);
	else
		write(OUT, "\n\n\n\n\n", 6);
	account(name, host, *argv);
	exit(n);
}

putplot()
{
	register char *cp;
	register int bytes, n;

	cp = buf;
	bytes = 0;
	ioctl(OUT, VSETSTATE, plotmd);
	while ((n = read(IN, cp, sizeof(buf))) > 0) {
		if (write(OUT, cp, n) != n)
			return(1);
		bytes += n;
	}
	/*
	 * Make sure we send complete raster lines.
	 */
	if ((n = bytes % BYTES_PER_LINE) > 0) {
		n = BYTES_PER_LINE - n;
		for (cp = &buf[n]; cp > buf; )
			*--cp = 0;
		if (write(OUT, cp, n) != n)
			return(1);
		bytes += n;
	}
	lines += bytes / BYTES_PER_LINE;
	return(0);
}

account(who, from, acctfile)
	char *who, *from, *acctfile;
{
	register FILE *a;

	if (who == NULL || acctfile == NULL)
		return;
	if (access(acctfile, 02) || (a = fopen(acctfile, "a")) == NULL)
		return;
	/*
	 * Varian accounting is done by 8.5 inch pages;
	 * Versatec accounting is by the (12 inch) foot.
	 */
	fprintf(a, "t%6.2f\t", (double)lines / (double)PAGE_LINES);
	if (from != NULL)
		fprintf(a, "%s:", from);
	fprintf(a, "%s\n", who);
	fclose(a);
}
