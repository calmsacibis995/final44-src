h42825
s 00000/00000/00021
d D 8.1 93/06/06 22:16:14 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00021/00000/00000
d D 5.1 91/04/24 17:50:31 bostic 1 0
c date and time created 91/04/24 17:50:31 by bostic
e
u
U
t
T
I 1
/*	inet_ntoa.c	4.1	83/06/12	*/

/*
 * Convert network-format internet address
 * to base 256 d.d.d.d representation.
 */
#include <sys/types.h>
#include <netinet/in.h>

char *
inet_ntoa(in)
	struct in_addr in;
{
	static char b[18];
	register char *p;

	p = (char *)&in;
#define	UC(b)	(((int)b)&0xff)
	sprintf(b, "%d.%d.%d.%d", UC(p[0]), UC(p[1]), UC(p[2]), UC(p[3]));
	return (b);
}
E 1
