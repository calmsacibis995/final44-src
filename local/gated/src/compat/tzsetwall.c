/*
 *  $Id: tzsetwall.c,v 1.9 1992/10/08 19:59:14 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"

/*
 *	Emulation of tzsetwall.  Unset TZ and then call tzset.
 */

#if	__GNUC__ >= 2
PROTOTYPE(tzsetwall,
	  void,
	  (void));
#endif	/* __GNUC__ >= 2*/

void
tzsetwall()
{
    unsetenv("TZ");

    tzset();
}


/*
 * %(Copyright)
 */
