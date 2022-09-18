/*
 *  $Id: tzset.c,v 1.9 1992/10/08 19:59:12 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"

/*
 *	Emulation of tzset.  Just ignore it.
 */

#if	__GNUC__ >= 2
PROTOTYPE(tzset,
	  void,
	  (void));
#endif	/* __GNUC__ >= 2*/

void
tzset()
{
}


/*
 * %(Copyright)
 */
