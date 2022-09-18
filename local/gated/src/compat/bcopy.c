/*
 *  $Id: bcopy.c,v 1.8 1992/10/08 19:58:51 jch Exp $
 */

/* %(Copyright.header) */


#include "include.h"

#ifdef	NEED_BCOPY

#include <memory.h>

/*
 *	Emulations of bcopy, bcmp and bzero for systems that only have the mem routines.
 */

void
bcopy(src, dst, len)
const u_char *src;
u_char *dst;
size_t len;
{
    memcpy(dst, src, len);
}


void
bzero(s, len)
u_char *s;
size_t len;
{
    memset(s, 0, len);
}

int
bcmp(b1, b2, len)
const u_char *b1, *b2;
size_t len;
{
    return memcmp(b1, b2, len);
}

#endif	/* NEED_BCOPY */


/*
 * %(Copyright%)
 */
 
