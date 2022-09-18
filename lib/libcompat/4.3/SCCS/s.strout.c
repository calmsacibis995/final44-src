h33735
s 00000/00000/00031
d D 8.1 93/06/04 16:26:48 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00001/00026
d D 5.3 91/04/20 14:12:54 bostic 5 4
c new copyright; att/bsd/shared
e
s 00002/00002/00025
d D 5.2 86/03/09 20:54:31 donn 4 3
c added LIBC_SCCS condition for sccs ids
e
s 00004/00001/00023
d D 5.1 85/06/05 13:44:18 mckusick 3 2
c Add copyright
e
s 00001/00001/00023
d D 4.2 85/02/13 15:49:17 serge 2 1
c autoconfigure FILE array using getdtablesize() 
c changed all struct _iobuf to FILE 
c many miscellaneous changes
e
s 00024/00000/00000
d D 4.1 80/12/21 16:50:58 wnj 1 0
c date and time created 80/12/21 16:50:58 by wnj
e
u
U
t
T
I 5
/*-
 * %sccs.include.proprietary.c%
 */

E 5
I 1
D 3
/* %W% (Berkeley) %G% */
E 3
I 3
D 4
#ifndef lint
E 4
I 4
#if defined(LIBC_SCCS) && !defined(lint)
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
D 5
#endif LIBC_SCCS and not lint
E 5
I 5
#endif /* LIBC_SCCS and not lint */
E 5
E 4

E 3
#include	<stdio.h>

_strout(count, string, adjust, file, fillch)
register char *string;
register count;
int adjust;
D 2
register struct _iobuf *file;
E 2
I 2
register FILE *file;
E 2
{
	while (adjust < 0) {
		if (*string=='-' && fillch=='0') {
			putc(*string++, file);
			count--;
		}
		putc(fillch, file);
		adjust++;
	}
	while (--count>=0)
		putc(*string++, file);
	while (adjust) {
		putc(fillch, file);
		adjust--;
	}
}
E 1
