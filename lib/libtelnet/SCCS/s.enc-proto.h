h03241
s 00002/00002/00097
d D 8.1 93/06/04 17:35:15 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00097
d D 5.4 93/05/20 10:51:35 dab 4 3
c Fix all the "#if defined(ENCRYPTION)" lines to just
c be "#ifdef ENCRYPTION", so that unifdef can be used to strip
c out all the encryption code.
e
s 00010/00001/00089
d D 5.3 92/12/18 14:11:04 dab 3 2
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Latest version of Kerberos V stuff
c Bug fixes
e
s 00022/00009/00068
d D 5.2 91/03/22 13:17:49 dab 2 1
c Upgrade to the latest & greatest authentication/encryption
e
s 00077/00000/00000
d D 5.1 91/02/28 22:01:28 dab 1 0
c date and time created 91/02/28 22:01:28 by dab
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
#if	defined(ENCRYPT)
E 3
I 3
D 4
#if	defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
E 3
void encrypt_init P((char *, int));
Encryptions *findencryption P((int));
void encrypt_send_supprt P((void));
D 2
void encrypt_auto P((void));
E 2
I 2
void encrypt_auto P((int));
void decrypt_auto P((int));
E 2
void encrypt_is P((unsigned char *, int));
void encrypt_reply P((unsigned char *, int));
void encrypt_start_input P((int));
void encrypt_session_key P((Session_Key *, int));
void encrypt_end_input P((void));
void encrypt_start_output P((int));
void encrypt_end_output P((void));
void encrypt_send_request_start P((void));
void encrypt_send_request_end P((void));
void encrypt_send_end P((void));
void encrypt_wait P((void));
void encrypt_send_support P((void));
I 2
void encrypt_send_keyid P((int, unsigned char *, int, int));
E 2
int net_write P((unsigned char *, int));

#ifdef	TELENTD
void encrypt_wait P((void));
#else
int encrypt_cmd P((int, char **));
void encrypt_display P((void));
#endif
I 3

void krbdes_encrypt P((unsigned char *, int));
int krbdes_decrypt P((int));
int krbdes_is P((unsigned char *, int));
int krbdes_reply P((unsigned char *, int));
void krbdes_init P((int));
int krbdes_start P((int, int));
void krbdes_session P((Session_Key *, int));
void krbdes_printsub P((unsigned char *, int, unsigned char *, int));
E 3

D 2
void krbdes_encrypt P((unsigned char *, int));
int krbdes_decrypt P((int));
int krbdes_is P((unsigned char *, int));
int krbdes_reply P((unsigned char *, int));
void krbdes_init P((int));
int krbdes_start P((int, int));
void krbdes_session P((Session_Key *, int));
void krbdes_printsub P((unsigned char *, int, unsigned char *, int));
E 2
I 2
void cfb64_encrypt P((unsigned char *, int));
int cfb64_decrypt P((int));
void cfb64_init P((int));
int cfb64_start P((int, int));
int cfb64_is P((unsigned char *, int));
int cfb64_reply P((unsigned char *, int));
void cfb64_session P((Session_Key *, int));
int cfb64_keyid P((int, unsigned char *, int *));
void cfb64_printsub P((unsigned char *, int, unsigned char *, int));

void ofb64_encrypt P((unsigned char *, int));
int ofb64_decrypt P((int));
void ofb64_init P((int));
int ofb64_start P((int, int));
int ofb64_is P((unsigned char *, int));
int ofb64_reply P((unsigned char *, int));
void ofb64_session P((Session_Key *, int));
int ofb64_keyid P((int, unsigned char *, int *));
void ofb64_printsub P((unsigned char *, int, unsigned char *, int));
E 2

int  des_new_random_key P((Block));
void des_set_random_generator_seed P((Block));
void des_key_sched P((Block, Schedule));
void des_ecb_encrypt P((Block, Block, Schedule, int));
int  des_string_to_key P((char *, Block));
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
E 1
