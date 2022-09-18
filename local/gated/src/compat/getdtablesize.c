/*
 *  $Id: getdtablesize.c,v 1.9 1992/10/08 19:58:57 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"

/*
 *	Emulation of getdtablesize for 4.2 based systems.  Returns 20.
 */

#if	__GNUC__ >= 2
PROTOTYPE(getdtablesize,
	  int,
	  (void));
#endif	/* __GNUC__ >= 2*/

int
getdtablesize()
{
    return (20);
}


/*
 * %(Copyright)
 */
