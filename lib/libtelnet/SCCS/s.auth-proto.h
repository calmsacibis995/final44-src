h22511
s 00002/00002/00068
d D 8.1 93/06/04 17:34:58 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00069
d D 5.3 92/12/18 14:11:17 dab 3 2
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Latest version of Kerberos V stuff
c Bug fixes
e
s 00000/00007/00070
d D 5.2 91/03/22 13:17:46 dab 2 1
c Upgrade to the latest & greatest authentication/encryption
e
s 00077/00000/00000
d D 5.1 91/02/28 22:01:27 dab 1 0
c date and time created 91/02/28 22:01:27 by dab
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
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Copyright (C) 1990 by the Massachusetts Institute of Technology
 *
 * Export of this software from the United States of America is assumed
 * to require a specific license from the United States Government.
 * It is the responsibility of any person or organization contemplating
 * export to obtain such a license before exporting.
 * 
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 */

#if	!defined(P)
#ifdef	__STDC__
#define	P(x)	x
#else
#define	P(x)	()
#endif
#endif

D 3
#if	defined(AUTHENTICATE)
E 3
I 3
#if	defined(AUTHENTICATION)
E 3
Authenticator *findauthenticator P((int, int));

void auth_init P((char *, int));
int auth_cmd P((int, char **));
void auth_request P((void));
void auth_send P((unsigned char *, int));
void auth_send_retry P((void));
void auth_is P((unsigned char *, int));
void auth_reply P((unsigned char *, int));
void auth_finished P((Authenticator *, int));
int auth_wait P((char *));
void auth_disable_name P((char *));
void auth_gen_printsub P((unsigned char *, int, unsigned char *, int));

D 2
#ifdef	SIMPLE_AUTH
int simple_auth_init P((Authenticator *, int));
int simple_auth_send P((Authenticator *));
void simple_auth_is_reply P((Authenticator *, unsigned char *, int));
void simple_auth_printsub P((unsigned char *, int, unsigned char *, int));
#endif

E 2
#ifdef	KRB4
int kerberos4_init P((Authenticator *, int));
int kerberos4_send P((Authenticator *));
void kerberos4_is P((Authenticator *, unsigned char *, int));
void kerberos4_reply P((Authenticator *, unsigned char *, int));
int kerberos4_status P((Authenticator *, char *, int));
void kerberos4_printsub P((unsigned char *, int, unsigned char *, int));
#endif

#ifdef	KRB5
int kerberos5_init P((Authenticator *, int));
int kerberos5_send P((Authenticator *));
void kerberos5_is P((Authenticator *, unsigned char *, int));
void kerberos5_reply P((Authenticator *, unsigned char *, int));
int kerberos5_status P((Authenticator *, char *, int));
void kerberos5_printsub P((unsigned char *, int, unsigned char *, int));
#endif
#endif
E 1
