h44349
s 00000/00000/00018
d D 8.1 93/06/04 16:32:45 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00016
d D 5.2 91/02/24 14:14:41 bostic 2 1
c Add include files to get prototype declarations, and fix bugs found.
e
s 00017/00000/00000
d D 5.1 90/05/03 17:47:29 bostic 1 0
c date and time created 90/05/03 17:47:29 by bostic
e
u
U
t
T
I 2
#include <regexp.h>
E 2
I 1
#include <stdio.h>

void
regerror(s)
D 2
char *s;
E 2
I 2
const char *s;
E 2
{
#ifdef ERRAVAIL
	error("regexp: %s", s);
#else
/*
	fprintf(stderr, "regexp(3): %s\n", s);
	exit(1);
*/
	return;	  /* let std. egrep handle errors */
#endif
	/* NOTREACHED */
}
E 1
