/*
 *  $Id: isis_rtrace.c,v 1.8 1992/10/08 19:55:06 jch Exp $
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"

/* called with: fmt, args */
#ifdef	STDARG
/*VARARGS2*/
void
dprintf(char *fmt, ...)
#else	/* STDARG */
void
dprintf(va_alist)
va_dcl
#endif	/* STDARG */
{
    va_list	args;
#ifdef	STDARG

    va_start(args, fmt);
#else	/* STDARG */
    char	*fmt;

    va_start(args);

    fmt = va_arg(args, char *);
#endif	/* STDARG */

/* 	fprintf(debugLog.fp, "%d: ", getpid());*/
	vfprintf(debugLog.fp, fmt, args);

	va_end(args);
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
