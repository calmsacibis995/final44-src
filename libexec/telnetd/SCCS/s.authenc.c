h10564
s 00001/00001/00064
d D 8.2 95/05/30 22:02:42 dab 5 4
c code cleanup, change b*() to mem*()
c Add setting up of LINEMODE environment variable.
e
s 00002/00002/00063
d D 8.1 93/06/04 19:06:48 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00061
d D 5.3 93/05/20 11:37:55 dab 3 2
c Several fixes.  The big one is that all of the
c code that was "#if defined(ENCRYPTION)" is now changed
c to "#ifdef ENCRYPTION", so that all the encryption code
c can be stripped out using unifdef.
c Other fixes:
c 	Add support for HP-UX (untested...)
c 	Simplification of the ENV_HACK stuff
c 	Add in UNICOS 8.0 secure system changes
c 	Clean up the option processing
c 	Fix up the usage() statement
e
s 00002/00002/00063
d D 5.2 92/12/18 14:05:39 dab 2 1
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00065/00000/00000
d D 5.1 91/03/01 02:16:10 dab 1 0
c date and time created 91/03/01 02:16:10 by dab
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 2
#if	defined(ENCRYPT) || defined(AUTHENTICATE)
E 2
I 2
D 3
#if	defined(ENCRYPTION) || defined(AUTHENTICATION)
E 3
I 3
#if	defined(AUTHENTICATION) || defined(ENCRYPTION)
E 3
E 2
#include "telnetd.h"
#include <libtelnet/misc.h>

	int
net_write(str, len)
	unsigned char *str;
	int len;
{
	if (nfrontp + len < netobuf + BUFSIZ) {
D 5
		bcopy((void *)str, (void *)nfrontp, len);
E 5
I 5
		memmove((void *)nfrontp, (void *)str, len);
E 5
		nfrontp += len;
		return(len);
	}
	return(0);
}

	void
net_encrypt()
{
D 2
#if	defined(ENCRYPT)
E 2
I 2
D 3
#if	defined(ENCRYPTION)
E 3
I 3
#ifdef	ENCRYPTION
E 3
E 2
	char *s = (nclearto > nbackp) ? nclearto : nbackp;
	if (s < nfrontp && encrypt_output) {
		(*encrypt_output)((unsigned char *)s, nfrontp - s);
	}
	nclearto = nfrontp;
D 3
#endif
E 3
I 3
#endif /* ENCRYPTION */
E 3
}

	int
telnet_spin()
{
	ttloop();
	return(0);
}

	char *
telnet_getenv(val)
	char *val;
{
	extern char *getenv();
	return(getenv(val));
}

	char *
telnet_gets(prompt, result, length, echo)
	char *prompt;
	char *result;
	int length;
	int echo;
{
	return((char *)0);
}
D 3
#endif
E 3
I 3
#endif	/* defined(AUTHENTICATION) || defined(ENCRYPTION) */
E 3
E 1
