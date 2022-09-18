h19241
s 00005/00005/00053
d D 8.1 93/06/06 16:24:32 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00002/00043
d D 4.3 91/04/18 18:07:56 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00000/00044
d D 4.2 91/02/02 17:54:45 torek 2 1
c putw => putword; argument declarations (all from gcc -W)
e
s 00044/00000/00000
d D 4.1 82/12/18 15:10:34 sam 1 0
c date and time created 82/12/18 15:10:34 by sam
e
u
U
t
T
I 3
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% %G%";
#endif
E 3
I 3
D 4
char copyright[] =
"%Z% Copyright (c) 1991 The Regents of the University of California.\n\
 All rights reserved.\n";
E 4
I 4
static char copyright[] =
"%Z% Copyright (c) 1991, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 4
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include "spell.h"
/* add entries to hash table for use by spell
   preexisting hash table is first argument
   words to be added are standard input
   if no hash table is given, create one from scratch
*/

main(argc,argv)
I 2
int argc;
E 2
char **argv;
{
	register i, j;
	long h;
	register long *lp;
	char word[NW];
	register char *wp;

	if(!prime(argc,argv)) {
		fprintf(stderr,
		    "spellin: cannot initialize hash table\n");
		exit(1);
	}
	while (fgets(word, sizeof(word), stdin)) {
		for (i=0; i<NP; i++) {
			for (wp = word, h = 0, lp = pow2[i];
				 (j = *wp) != '\0'; ++wp, ++lp)
				h += j * *lp;
			h %= p[i];
			set(h);
		}
	}
#ifdef gcos
	freopen((char *)NULL, "wi", stdout);
#endif
	if (fwrite((char *)tab, sizeof(*tab), TABSIZE, stdout) != TABSIZE) {
		fprintf(stderr,
		    "spellin: trouble writing hash table\n");
		exit(1);
	}
	return(0);
}
E 1
