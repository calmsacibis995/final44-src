/*
 *  $Id: herrs.c,v 1.8 1992/10/08 19:59:02 jch Exp $
 */

/* %(Copyright.header) */


/*
 *	Nameserver errors for systems that define h_errno in netdb.h but
 *	don't have the error messages
 */

#ifdef __STDC__
const
#endif	/* __STDC__ */
char *h_errlist[] =
{
    "Error 0",
    "Unknown host",			/* 1 HOST_NOT_FOUND */
    "Host name lookup failure",		/* 2 TRY_AGAIN */
    "Unknown server error",		/* 3 NO_RECOVERY */
    "No address associated with name",	/* 4 NO_ADDRESS */
};
int h_nerr =
{sizeof(h_errlist) / sizeof(h_errlist[0])};


/*
 * %(Copyright)
 */
