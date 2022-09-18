/*
 *  $Id: ffs.c,v 1.2 1992/10/08 19:58:53 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"

/*
 * Emulation of ffs()
 */

#if	__GNUC__ >= 2
PROTOTYPE(ffs,
	  int,
	  (int));
#endif	/* __GNUC__ >= 2*/
int
ffs __PF1(arg, int)
{
    register int i;

    for (i = 1; arg; arg >>= 1, i++) {
	if (arg & 0x01) {
	    return i;
	}
    }

    return 0;
}


/*
 * %(Copyright)
 */
