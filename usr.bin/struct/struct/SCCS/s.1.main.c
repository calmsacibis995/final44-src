h46239
s 00000/00000/00021
d D 8.1 93/06/06 16:29:08 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00015
d D 4.2 91/04/16 16:48:34 bostic 2 1
c new copyright; att/bsd/shared
e
s 00017/00000/00000
d D 4.1 83/02/11 15:44:14 rrh 1 0
c date and time created 83/02/11 15:44:14 by rrh
e
u
U
t
T
I 2
/*-
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include <stdio.h>
#include "def.h"
int endbuf;

mkgraph()
	{
	if (!parse())
		return(FALSE);
	hash_check();
	hash_free();
	fingraph();
	return(TRUE);
	}
E 1
