/*
 *  $Id: setvbuf.c,v 1.1 1992/10/15 14:51:11 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"

/*
 *	Emulation of setvbuf().
 */

#if	__GNUC__ >= 2
PROTOTYPE(setvbuf,
	  int,
	  (FILE *,
	   caddr_t,
	   int,
	   size_t));
#endif	/* __GNUC__ >= 2*/

int
setvbuf __PF4(stream, FILE *,
	      buf, caddr_t,
	      type, int,
	      size, size_t)
{
    int rc = 0;

    switch (type) {
#ifdef	_IOFBF
    case _IOFBF:
	setbuffer(stream, buf, size);
	break;
#endif	/* _IOFBF */

    case _IOLBF:
	(void) setlinebuf(stream);
	break;

    case _IONBF:
	setbuf(stream, NULL);
	break;

    default:
	assert(FALSE);
    }

    return rc;
}
