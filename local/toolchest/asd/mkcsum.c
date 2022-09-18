/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include "seal.h"

unsigned long
mkcsum (csum, start, limit)
	register unsigned long csum;
	char *start, *limit;
{
	register int c;

	while (start < limit) {
		c = (unsigned char) *start++;
		if (csum & 1)
			csum = (csum >> 1) | CSHIBIT;
		else

			csum >>= 1;
		csum += c;
		csum &= CSMASK;
	}
	return csum;
}
