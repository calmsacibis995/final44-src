/*
 *  $Id: strerror.c,v 1.9.4.1 1995/05/01 16:07:04 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"

/*
 * Emulation of ANSI strerror()
 */

const char *
strerror(errnum)
int errnum;
{
    static char message[30];
    extern int sys_nerr;
    extern char *sys_errlist[];

    if ((unsigned int) errnum < sys_nerr) {
	return sys_errlist[errnum];
    }

    sprintf(message, "Unknown error: %d", errnum);
    return message;
}


/*
 * %(Copyright)
 */
