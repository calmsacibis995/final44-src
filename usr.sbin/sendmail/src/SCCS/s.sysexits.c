h47218
s 00001/00001/00157
d D 8.5 95/05/24 08:53:51 eric 27 26
c new code requires conf.h -- just include sendmail.h
e
s 00007/00005/00151
d D 8.4 95/04/22 15:58:52 eric 26 25
c updates for new status system codes and Multipart/Report drafts
e
s 00115/00000/00041
d D 8.3 95/04/22 11:07:05 eric 25 24
c allow error mailer to take DSN status code
e
s 00001/00001/00040
d D 8.2 95/04/21 09:56:40 eric 24 23
c update copyright notice
e
s 00002/00002/00039
d D 8.1 93/06/07 10:32:24 bostic 23 22
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00023/00018/00018
d D 6.3 93/03/13 22:53:25 eric 22 21
c change tagging of errors that need errno attached
e
s 00007/00033/00029
d D 6.2 93/03/06 10:52:55 eric 21 20
c don't automatically print errno in usrerr -- it can be too misleading
e
s 00000/00000/00062
d D 6.1 92/12/21 16:07:57 eric 20 19
c Release 6
e
s 00001/00011/00061
d D 5.6 90/06/01 19:04:45 bostic 19 18
c new copyright notice
e
s 00011/00009/00061
d D 5.5 88/06/30 14:59:57 bostic 18 17
c install approved copyright notice
e
s 00023/00027/00047
d D 5.4 88/04/01 15:35:50 bostic 17 16
c add CONFIG error, #78, for local configuration botches
e
s 00016/00010/00058
d D 5.3 88/03/13 19:53:26 bostic 16 15
c add Berkeley specific header
e
s 00000/00002/00068
d D 5.2 85/06/07 22:20:14 miriam 15 14
m 
c Resolve duplicate SccsId
e
s 00014/00000/00056
d D 5.1 85/06/07 15:17:03 dist 14 13
m 
c Add copyright
e
s 00028/00000/00028
d D 4.3 85/05/24 10:54:49 eric 13 12
m 
c Changes from Bill Nowicki <sun!rose!nowicki> and Jay Lepreau <lepreau@utah-cs>:
c Fix "bad file number" problem; improve error reporting; try to keep messages
c closer to their original order.  Also, drop "safe" mode in readcf since we
c never run setuid when -C is specified.
e
s 00001/00000/00027
d D 4.2 83/07/31 10:46:19 eric 12 11
m 
c Add EX_NOPERM to sysexits.h for kre
e
s 00000/00000/00027
d D 4.1 83/07/25 19:43:10 eric 11 10
m 
c 4.2 release version
e
s 00001/00001/00026
d D 3.6 83/01/04 13:10:01 eric 10 9
m 
c change format of deferred message to be consistent with other messages
e
s 00013/00013/00014
d D 3.5 82/08/31 10:06:08 eric 9 8
c clean up reply code processing some more; in particular, give more
c detail in many messages.  process connection failures correctly.
e
s 00013/00012/00014
d D 3.4 82/08/29 17:32:57 eric 8 7
c fix serious botch in SMTP reply code delta; change a bunch of
c "Internal error" codes to a new "Remote protocol error" -- so that
c I don't get blamed for things that other systems do.
e
s 00002/00001/00024
d D 3.3 81/12/06 12:38:57 eric 7 6
c cleanup so it will go through lint without any fancy grep -v's;
c change the way SCCS Id's are handled.
e
s 00001/00000/00024
d D 3.2 81/10/15 20:38:07 eric 6 5
c add EX_TEMPFAIL
e
s 00000/00000/00024
d D 3.1 81/03/07 14:27:08 eric 5 4
c ----- delivermail ==> postbox -----
e
s 00000/00000/00024
d D 2.1 80/11/05 11:00:08 eric 4 3
c release 2
e
s 00003/00000/00021
d D 1.3 80/08/02 13:50:02 eric 3 2
c cleaned up comments
e
s 00002/00000/00019
d D 1.2 80/07/25 22:04:26 eric 2 1
c add ID keywords
e
s 00019/00000/00000
d D 1.1 80/06/23 08:24:42 eric 1 0
e
u
U
f b 
f i 
t
T
I 14
/*
I 18
D 24
 * Copyright (c) 1983 Eric P. Allman
E 24
I 24
 * Copyright (c) 1983, 1995 Eric P. Allman
E 24
E 18
D 16
**  Sendmail
**  Copyright (c) 1983  Eric P. Allman
**  Berkeley, California
**
**  Copyright (c) 1983 Regents of the University of California.
**  All rights reserved.  The Berkeley software License Agreement
**  specifies the terms and conditions for redistribution.
*/
E 16
I 16
D 23
 * Copyright (c) 1988 Regents of the University of California.
 * All rights reserved.
E 23
I 23
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
E 23
 *
D 19
 * Redistribution and use in source and binary forms are permitted
D 18
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
 *
 *  Sendmail
 *  Copyright (c) 1983  Eric P. Allman
 *  Berkeley, California
E 18
I 18
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 18
 */
E 16

#ifndef lint
D 16
static char	SccsId[] = "%W% (Berkeley) %G%";
#endif not lint
E 16
I 16
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 16

E 14
I 1
D 17
# include <sysexits.h>
I 7
# include "useful.h"
E 17
I 17
D 27
#include <sysexits.h>
E 27
I 27
#include <sendmail.h>
E 27
E 17
E 7

I 2
D 7
static char	SccsId[] = "%W%	%G%";
E 7
I 7
D 15
SCCSID(%W%	%Y%	%G%);
E 7
E 2

E 15
I 3
/*
D 17
**  SYSEXITS.C -- error messages corresponding to sysexits.h
*/
E 3
I 2

E 2
char	*SysExMsg[] =
{
E 17
I 17
D 22
 *  SYSEXITS.C -- error messages corresponding to sysexits.h
 */
char *SysExMsg[] = {
E 17
D 8
	/* 64 */	"Bad usage",
	/* 65 */	"Data format error",
	/* 66 */	"Cannot open input",
	/* 67 */	"User unknown",
	/* 68 */	"Host unknown",
	/* 69 */	"Service unavailable",
	/* 70 */	"Internal error",
	/* 71 */	"Operating system error",
	/* 72 */	"System file missing",
	/* 73 */	"Can't create output",
	/* 74 */	"I/O error",
I 6
	/* 75 */	"Temporary failure",
E 8
I 8
D 9
	/* 64 USAGE */		"Bad usage",
	/* 65 DATAERR */	"Data format error",
	/* 66 NOINPUT */	"Cannot open input",
	/* 67 NOUSER */		"User unknown",
	/* 68 NOHOST */		"Host unknown",
	/* 69 UNAVAILABLE */	"Service unavailable",
	/* 70 SOFTWARE */	"Internal error",
	/* 71 OSERR */		"Operating system error",
	/* 72 OSFILE */		"System file missing",
	/* 73 CANTCREAT */	"Can't create output",
	/* 74 IOERR */		"I/O error",
	/* 75 TEMPFAIL */	"Temporary failure",
	/* 76 PROTOCOL */	"Remote protocol error",
E 9
I 9
	/* 64 USAGE */		"500 Bad usage",
	/* 65 DATAERR */	"501 Data format error",
D 21
	/* 66 NOINPUT */	"550 Cannot open input",
E 21
I 21
	/* 66 NOINPUT */	"550 Cannot open input: %s",
E 21
	/* 67 NOUSER */		"550 User unknown",
	/* 68 NOHOST */		"550 Host unknown",
	/* 69 UNAVAILABLE */	"554 Service unavailable",
D 21
	/* 70 SOFTWARE */	"554 Internal error",
	/* 71 OSERR */		"451 Operating system error",
	/* 72 OSFILE */		"554 System file missing",
	/* 73 CANTCREAT */	"550 Can't create output",
	/* 74 IOERR */		"451 I/O error",
E 21
I 21
	/* 70 SOFTWARE */	"554 Internal error: %s",
	/* 71 OSERR */		"451 Operating system error: %s",
	/* 72 OSFILE */		"554 System file missing: %s",
	/* 73 CANTCREAT */	"550 Can't create output: %s",
	/* 74 IOERR */		"451 I/O error: %s",
E 21
D 10
	/* 75 TEMPFAIL */	"250 Temporary failure",
E 10
I 10
	/* 75 TEMPFAIL */	"250 Deferred",
E 10
	/* 76 PROTOCOL */	"554 Remote protocol error",
I 12
D 21
	/* 77 NOPERM */		"550 Insufficient permission",
E 21
I 21
	/* 77 NOPERM */		"550 Insufficient permission: %s",
E 21
I 17
	/* 78 CONFIG */		"554 Local configuration error",
E 22
I 22
**  SYSEXITS.C -- error messages corresponding to sysexits.h
**
**	If the first character of the string is a colon, interpolate
**	the current errno after the rest of the string.
*/

char *SysExMsg[] =
{
	/* 64 USAGE */		" 500 Bad usage",
	/* 65 DATAERR */	" 501 Data format error",
	/* 66 NOINPUT */	":550 Cannot open input",
	/* 67 NOUSER */		" 550 User unknown",
	/* 68 NOHOST */		" 550 Host unknown",
	/* 69 UNAVAILABLE */	" 554 Service unavailable",
	/* 70 SOFTWARE */	":554 Internal error",
	/* 71 OSERR */		":451 Operating system error",
	/* 72 OSFILE */		":554 System file missing",
	/* 73 CANTCREAT */	":550 Can't create output",
	/* 74 IOERR */		":451 I/O error",
	/* 75 TEMPFAIL */	" 250 Deferred",
	/* 76 PROTOCOL */	" 554 Remote protocol error",
	/* 77 NOPERM */		":550 Insufficient permission",
	/* 78 CONFIG */		" 554 Local configuration error",
E 22
E 17
E 12
E 9
E 8
E 6
};

D 17
int	N_SysEx = sizeof SysExMsg / sizeof SysExMsg[0];
I 13
/*
**  STATSTRING -- return string corresponding to an error status
**
**	Parameters:
**		stat -- the status to decode.
**
**	Returns:
**		The string corresponding to that status
**
**	Side Effects:
**		none.
*/
E 17
I 17
int N_SysEx = sizeof(SysExMsg) / sizeof(SysExMsg[0]);
I 25
/*
**  DSNTOEXITSTAT -- convert DSN-style error code to EX_ style.
**
**	Parameters:
**		dsncode -- the text of the DSN-style code.
**
**	Returns:
**		The corresponding exit status.
*/

int
dsntoexitstat(dsncode)
	char *dsncode;
{
	int code2, code3;

	/* first the easy cases.... */
	if (*dsncode == '2')
		return EX_OK;
	if (*dsncode == '4')
		return EX_TEMPFAIL;

	/* now decode the other two field parts */
	if (*++dsncode == '.')
		dsncode++;
	code2 = atoi(dsncode);
	while (*dsncode != '\0' && *dsncode != '.')
		dsncode++;
	if (*dsncode != '\0')
		dsncode++;
	code3 = atoi(dsncode);

	/* and do a nested switch to work them out */
	switch (code2)
	{
	  case 0:	/* Other or Undefined status */
		return EX_UNAVAILABLE;

	  case 1:	/* Address Status */
		switch (code3)
		{
		  case 0:	/* Other Address Status */
			return EX_DATAERR;

D 26
		  case 1:	/* Bad mailbox address */
E 26
I 26
		  case 1:	/* Bad destination mailbox address */
E 26
		  case 6:	/* Mailbox has moved, No forwarding address */
			return EX_NOUSER;

D 26
		  case 2:	/* Bad system address */
E 26
I 26
		  case 2:	/* Bad destination system address */
		  case 8:	/* Bad senders system address */
E 26
			return EX_NOHOST;

D 26
		  case 3:	/* Bad mailbox address syntax */
E 26
I 26
		  case 3:	/* Bad destination mailbox address syntax */
		  case 7:	/* Bad senders mailbox address syntax */
E 26
			return EX_USAGE;

D 26
		  case 4:	/* Mailbox address ambiguous */
E 26
I 26
		  case 4:	/* Destination mailbox address ambiguous */
E 26
			return EX_UNAVAILABLE;

D 26
		  case 5:	/* Address valid */
E 26
I 26
		  case 5:	/* Destination address valid */
E 26
			return EX_OK;
		}
		break;

	  case 2:	/* Mailbox Status */
		switch (code3)
		{
		  case 0:	/* Other or Undefined mailbox status */
		  case 1:	/* Mailbox disabled, not acccepting messages */
		  case 2:	/* Mailbox full */
		  case 4:	/* Mailing list expansion problem */
			return EX_UNAVAILABLE;

		  case 3:	/* Message length exceeds administrative lim */
			return EX_DATAERR;
		}
		break;

	  case 3:	/* System Status */
		return EX_OSERR;

	  case 4:	/* Network and Routing Status */
		switch (code3)
		{
		  case 0:	/* Other or undefined network or routing stat */
			return EX_IOERR;

		  case 1:	/* No answer from host */
		  case 3:	/* Routing server failure */
		  case 5:	/* Network congestion */
			return EX_TEMPFAIL;

		  case 2:	/* Bad connection */
			return EX_IOERR;

		  case 4:	/* Unable to route */
			return EX_PROTOCOL;

		  case 6:	/* Routing loop detected */
			return EX_CONFIG;

		  case 7:	/* Delivery time expired */
			return EX_UNAVAILABLE;
		}
		break;

	  case 5:	/* Protocol Status */
		return EX_PROTOCOL;

	  case 6:	/* Message Content or Media Status */
		return EX_UNAVAILABLE;

	  case 7:	/* Security Status */
		return EX_DATAERR;
	}
	return EX_CONFIG;
}
E 25
E 17
D 21

I 17
/*
 *  STATSTRING -- return string corresponding to an error status
 *
 *	Parameters:
 *		stat -- the status to decode.
 *
 *	Returns:
 *		The string corresponding to that status
 *
 *	Side Effects:
 *		none.
 */
E 17
char *
statstring(stat)
	int stat;
{
D 17
	static char ebuf[100];
E 17
I 17
	static char ebuf[50];
E 17

	stat -= EX__BASE;
D 17
	if (stat < 0 || stat >= N_SysEx)
	{
		(void) sprintf(ebuf, "554 Unknown status %d", stat + EX__BASE);
		return (ebuf);
E 17
I 17
	if (stat < 0 || stat >= N_SysEx) {
		(void)sprintf(ebuf, "554 Unknown status %d", stat + EX__BASE);
		return(ebuf);
E 17
	}
D 17

	return (SysExMsg[stat]);
E 17
I 17
	return(SysExMsg[stat]);
E 17
}
E 21
E 13
E 1
