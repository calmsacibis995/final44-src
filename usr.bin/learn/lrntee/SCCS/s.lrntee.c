h45309
s 00005/00005/00045
d D 8.1 93/06/06 15:01:51 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00002/00035
d D 4.4 91/04/17 18:02:16 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00001/00035
d D 4.3 86/05/15 17:58:33 bloom 3 2
c updates from John Kunze
e
s 00000/00000/00036
d D 4.2 83/04/26 01:23:55 mckusick 2 1
c 
e
s 00036/00000/00000
d D 4.1 83/04/26 01:21:12 mckusick 1 0
c date and time created 83/04/26 01:21:12 by mckusick
e
u
U
t
T
I 4
/*-
D 5
 * Copyright (c) 1986 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1986, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
D 4
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 4
I 4
D 5
char copyright[] =
"%Z% Copyright (c) 1986 The Regents of the University of California.\n\
 All rights reserved.\n";
E 5
I 5
static char copyright[] =
"%Z% Copyright (c) 1986, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 5
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4

main()
{
D 3
	int f, c;
E 3
I 3
	int f;
	char c;
E 3

	f = creat(".ocopy", 0666);
	while (read(0, &c, 1) == 1) {
		write (1, &c, 1);
		put(c, f);
	}
	fl(f);
	close(f);
}

static char ln[512];
char *p = ln;
put(c, f)
{
	*p++ = c;
	if (c == '\n') {
		fl(f);
		p=ln;
	}
}
fl(f)
{
	register char *s;

	s = ln;
	while (*s == '%' && *(s+1) == ' ')
		s += 2;
	write(f, s, p-s);
}
E 1
