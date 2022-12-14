/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
static char ID[] = "@(#)sputl (AT&T IS) 01/08/82a";
/*
 * The intent here is to provide a means to make the value of
 * bytes in an io-stream correspond to the value of the long
 * in the memory while doing the io a `long' at a time.
 * Files written and read in this way are machine-independent.
 *
 */
#include <values.h>

int
sputl(w, buffer)
register long w;
register char *buffer;
{
	register int i = BITSPERBYTE * sizeof(long);

	while ((i -= BITSPERBYTE) >= 0)
		*buffer++ = (char) (w >> i);
}
