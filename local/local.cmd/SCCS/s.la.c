h63194
s 00009/00028/00043
d D 6.2 89/05/29 16:37:07 mckusick 2 1
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00071/00000/00000
d D 6.1 89/05/29 16:05:55 mckusick 1 0
c date and time created 89/05/29 16:05:55 by mckusick
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
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
 */

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * la - print load averages
 */
D 2
#include <sys/param.h>
#include <nlist.h>
E 2
#include <stdio.h>
D 2
#include <machine/pte.h>		/* VAX page table entry */
#include <sys/vm.h>
E 2

D 2
struct	nlist nl[] = {
	{ "_avenrun" },
#define	X_AVENRUN	0
	{ 0 },
};

E 2
double	avenrun[3];

main(argc,argv)
D 2
int argc;
char *argv[];
E 2
I 2
	int argc;
	char *argv[];
E 2
{
	register int kmem, mem;
D 2
	char obuf[BUFSIZ];
E 2

D 2
	setbuf(stdout, obuf);

	if ((kmem = open("/dev/kmem", 0)) < 0) {
		fprintf(stderr, "No kmem\n");
E 2
I 2
	if (getloadavg(avenrun, sizeof(avenrun) / sizeof(avenrun[0])) < 0) {
		fprintf(stderr, "%s: getloadavg: failed\n", argv[0]);
E 2
		exit(1);
	}
D 2
	nlist("/vmunix", nl);
	if (nl[0].n_type==0) {
		fprintf(stderr, "No namelist\n");
		exit(1);
	}
	lseek(kmem, (long)nl[X_AVENRUN].n_value, 0);
	read(kmem, avenrun, sizeof(avenrun));
E 2
I 2

E 2
	if ((argc > 1) && (! strcmp (argv[1],"-g"))) {
D 2
	  printf("1    5    15\n");
	  printf("Min  Min  Min\n");
	  printf("-------------\n");
	  }
E 2
I 2
		printf("1    5    15\n");
		printf("Min  Min  Min\n");
		printf("-------------\n");
	}
E 2
	printf("%.2f %.2f %.2f\n", avenrun[0], avenrun[1], avenrun[2]);
}
E 1
