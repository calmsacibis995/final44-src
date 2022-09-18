/*
 *  $Id: getpagesize.c,v 1.2 1992/10/08 19:58:59 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"

/*
 * Emulation of getpagesize()
 */

#if	__GNUC__ >= 2
PROTOTYPE(getpagesize,
	  int,
	  (void));
#endif	/* __GNUC__ >= 2*/
int
getpagesize __PF0(void)
{
    return BUFSIZ;
}


/*
 * %(Copyright)
 */
