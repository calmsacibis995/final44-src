h51916
s 00004/00004/00053
d D 8.1 93/06/06 14:02:01 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00056
d D 5.8 92/09/16 10:54:44 elan 9 8
c copyright[] -> static
e
s 00004/00029/00053
d D 5.7 92/09/15 10:57:18 elan 8 7
c Added SCCS keypwrds.
e
s 00030/00004/00052
d D 5.6 92/09/01 11:11:32 elan 7 6
c Rewrote to use new getcap(3) library.  Major prototyping and cleanup.
e
s 00005/00003/00051
d D 5.5 92/07/21 10:30:27 bostic 6 5
c prototype lpr to fix quad's
e
s 00001/00011/00053
d D 5.4 90/06/01 18:46:01 bostic 5 4
c new copyright notice
e
s 00010/00005/00054
d D 5.3 88/06/30 18:00:02 bostic 4 3
c install approved copyright notice
e
s 00010/00004/00049
d D 5.2 88/05/05 18:08:17 bostic 3 2
c written by Ralph Campbell; add Berkeley specific header
e
s 00013/00001/00040
d D 5.1 85/06/06 10:05:50 dist 2 1
c Add copyright
e
s 00041/00000/00000
d D 4.1 83/10/14 11:28:40 ralph 1 0
c date and time created 83/10/14 11:28:40 by ralph
e
u
U
t
T
I 2
/*
D 8
 * Copyright (c) 1983 Regents of the University of California.
E 8
I 8
D 10
 * Copyright (c) 1983 The Regents of the University of California.
E 8
D 3
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
D 5
 * Redistribution and use in source and binary forms are permitted
D 4
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 4
I 4
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
E 5
I 5
D 7
 * %sccs.include.redist.c%
E 7
I 7
D 8
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
E 8
 *
D 8
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
E 8
I 8
 * %sccs.include.redist.c%
E 8
E 7
E 5
E 4
E 3
 */

E 2
I 1
#ifndef lint
I 2
D 9
char copyright[] =
E 9
I 9
static char copyright[] =
E 9
D 7
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 7
I 7
D 8
"@(#) Copyright (c) 1983 Regents of the University of California.\n\
E 8
I 8
D 10
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 8
E 7
 All rights reserved.\n";
E 10
I 10
"%Z% Copyright (c) 1983, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 10
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

#ifndef lint
E 2
D 7
static char sccsid[] = "%W% (Berkeley) %G%";
E 7
I 7
D 8
static char sccsid[] = "@(#)lptest.c	5.6 (Berkeley) 7/30/92";
E 8
I 8
static char sccsid[] = "%W% (Berkeley) %G%";
E 8
E 7
D 2
#endif
E 2
I 2
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3
E 2

I 6
#include <stdlib.h>
#include <stdio.h>

E 6
/*
 * lptest -- line printer test program (and other devices).
 */
D 6

#include <stdio.h>

E 6
I 6
D 7
int
E 7
I 7
void
E 7
E 6
main(argc, argv)
	int argc;
	char **argv;
{
	int len, count;
	register i, j, fc, nc;
	char outbuf[BUFSIZ];

	setbuf(stdout, outbuf);
	if (argc >= 2)
		len = atoi(argv[1]);
	else
		len = 79;
	if (argc >= 3)
		count = atoi(argv[2]);
	else
		count = 200;
	fc = ' ';
	for (i = 0; i < count; i++) {
		if (++fc == 0177)
			fc = ' ';
		nc = fc;
		for (j = 0; j < len; j++) {
			putchar(nc);
			if (++nc == 0177)
				nc = ' ';
		}
		putchar('\n');
	}
	(void) fflush(stdout);
I 6
	exit(0);
E 6
}
E 1
