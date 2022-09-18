h26500
s 00002/00002/00083
d D 8.1 93/06/06 16:32:16 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00081
d D 5.3 93/05/20 10:49:21 dab 4 2
c Mostly, this changes all the "#if defined(ENCRYPTION)"
c lines to "#ifdef ENCRYPTION".  This will allow unifdef
c to be used to strip out the encryption code for
c foreign exports.  This also fixes up the usage statement.
e
s 00004/00004/00081
d R 5.3 93/05/20 10:37:11 dab 3 2
c Mostly this changes "#if defined(ENCRYPTION)" to
c "#ifdef ENCRYPTION".  This will allow unifdef to be
e
s 00002/00002/00083
d D 5.2 92/12/18 14:06:41 dab 2 1
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Add Sun/SVR4 Streams support
c Allow for more ptys
c Environ suboption USERVAR support
c New Telnet Flowcontrol suboption support
c Server -k option to default to no kludge linemode
c Server -U option, allow only registered hosts to connect
e
s 00085/00000/00000
d D 5.1 91/03/01 02:13:33 dab 1 0
c date and time created 91/03/01 02:13:33 by dab
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
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
D 4
#if	defined(ENCRYPTION) || defined(AUTHENTICATION)
E 4
I 4
#if	defined(AUTHENTICATION) || defined(ENCRYPTION)
E 4
E 2
#include <sys/types.h>
#include <arpa/telnet.h>
#include <libtelnet/encrypt.h>
#include <libtelnet/misc.h>

#include "general.h"
#include "ring.h"
#include "externs.h"
#include "defines.h"
#include "types.h"

	int
net_write(str, len)
	unsigned char *str;
	int len;
{
	if (NETROOM() > len) {
		ring_supply_data(&netoring, str, len);
		if (str[0] == IAC && str[1] == SE)
			printsub('>', &str[2], len-2);
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
D 4
#if	defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
E 2
	if (encrypt_output)
		ring_encrypt(&netoring, encrypt_output);
	else
		ring_clearto(&netoring);
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
}

	int
telnet_spin()
{
	return(-1);
}

	char *
telnet_getenv(val)
	char *val;
{
	return((char *)env_getvalue((unsigned char *)val));
}

	char *
telnet_gets(prompt, result, length, echo)
	char *prompt;
	char *result;
	int length;
	int echo;
{
	extern char *getpass();
	extern int globalmode;
	int om = globalmode;
	char *res;

	TerminalNewMode(-1);
	if (echo) {
		printf("%s", prompt);
		res = fgets(result, length, stdin);
	} else if (res = getpass(prompt)) {
		strncpy(result, res, length);
		res = result;
	}
	TerminalNewMode(om);
	return(res);
}
D 4
#endif
E 4
I 4
#endif	/* defined(AUTHENTICATION) || defined(ENCRYPTION) */
E 4
E 1
