h03333
s 00023/00023/00511
d D 8.3 95/05/30 20:13:20 dab 7 6
c Code cleanup, use mem*() instead of b*()
e
s 00010/00004/00524
d D 8.2 95/02/16 11:25:13 dab 6 5
c Fix a problem with KRB4 mutual authentication where
c the key that was generated for encryption was not a valid key.
c Also put in some bug fixes, and a couple of spelling fixes.
e
s 00002/00002/00526
d D 8.1 93/06/04 17:35:54 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00021/00015/00507
d D 5.4 93/05/20 10:51:36 dab 4 3
c Fix all the "#if defined(ENCRYPTION)" lines to just
c be "#ifdef ENCRYPTION", so that unifdef can be used to strip
c out all the encryption code.
e
s 00091/00064/00431
d D 5.3 92/12/18 14:11:05 dab 3 2
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Latest version of Kerberos V stuff
c Bug fixes
e
s 00118/00062/00377
d D 5.2 91/03/22 13:17:51 dab 2 1
c Upgrade to the latest & greatest authentication/encryption
e
s 00439/00000/00000
d D 5.1 91/02/28 22:01:30 dab 1 0
c date and time created 91/02/28 22:01:30 by dab
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

#ifdef	KRB4
#include <sys/types.h>
#include <arpa/telnet.h>
#include <stdio.h>
D 3
#if	defined(ENCRYPT)
#define	__NEED_ENCRYPT__
#undef	ENCRYPT
#endif
E 3
D 7
#include <des.h>        /* BSD wont include this in krb.h, so we do it here */
E 7
I 7
#include <des.h>	/* BSD wont include this in krb.h, so we do it here */
E 7
#include <krb.h>
D 3
#if	defined(__NEED_ENCRYPT__) && !defined(ENCRYPT)
#define	ENCRYPT
#undef	__NEED_ENCRYPT__
#endif
E 3
#ifdef	__STDC__
#include <stdlib.h>
#endif
#ifdef	NO_STRING_H
#include <strings.h>
#else
#include <string.h>
#endif

#include "encrypt.h"
#include "auth.h"
#include "misc.h"

D 3
int cksum P((unsigned char *, int));
E 3
I 3
int kerberos4_cksum P((unsigned char *, int));
E 3
int krb_mk_req P((KTEXT, char *, char *, char *, u_long));
int krb_rd_req P((KTEXT, char *, char *, u_long, AUTH_DAT *, char *));
int krb_kntoln P((AUTH_DAT *, char *));
int krb_get_cred P((char *, char *, char *, CREDENTIALS *));
int krb_get_lrealm P((char *, int));
int kuserok P((AUTH_DAT *, char *));

extern auth_debug_mode;

static unsigned char str_data[1024] = { IAC, SB, TELOPT_AUTHENTICATION, 0,
			  		AUTHTYPE_KERBEROS_V4, };
I 2
static unsigned char str_name[1024] = { IAC, SB, TELOPT_AUTHENTICATION,
					TELQUAL_NAME, };
E 2

#define	KRB_AUTH	0		/* Authentication data follows */
#define	KRB_REJECT	1		/* Rejected (reason might follow) */
D 2
#define	KRB_ACCEPT	2		/* Accepted (name might follow) */
#define	KRB_NEWKEY	3		/* A new session key follows */
#define	KRB_NAME	4		/* Name to authenticate for */
E 2
I 2
#define	KRB_ACCEPT	2		/* Accepted */
D 3
#define	KRB_CHALLANGE	3		/* Challange for mutual auth. */
E 3
I 3
#define	KRB_CHALLENGE	3		/* Challenge for mutual auth. */
E 3
#define	KRB_RESPONSE	4		/* Response for mutual auth. */
E 2

I 3
#define KRB_SERVICE_NAME   "rcmd"

E 3
static	KTEXT_ST auth;
static	char name[ANAME_SZ];
static	AUTH_DAT adat = { 0 };
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
static Block	session_key	= { 0 };
D 3
#endif
E 3
I 2
static Schedule sched;
D 3
static Block	challange	= { 0 };
E 3
I 3
static Block	challenge	= { 0 };
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
E 3
E 2

	static int
D 2
Data(type, d, c)
E 2
I 2
Data(ap, type, d, c)
	Authenticator *ap;
E 2
	int type;
	void *d;
	int c;
{
D 2
        unsigned char *p = str_data + 6;
E 2
I 2
D 7
        unsigned char *p = str_data + 4;
E 7
I 7
	unsigned char *p = str_data + 4;
E 7
E 2
	unsigned char *cd = (unsigned char *)d;

	if (c == -1)
		c = strlen((char *)cd);

D 7
        if (auth_debug_mode) {
                printf("%s:%d: [%d] (%d)",
                        str_data[3] == TELQUAL_IS ? ">>>IS" : ">>>REPLY",
                        str_data[3],
                        type, c);
                printd(d, c);
                printf("\r\n");
        }
E 7
I 7
	if (auth_debug_mode) {
		printf("%s:%d: [%d] (%d)",
			str_data[3] == TELQUAL_IS ? ">>>IS" : ">>>REPLY",
			str_data[3],
			type, c);
		printd(d, c);
		printf("\r\n");
	}
E 7
I 2
	*p++ = ap->type;
	*p++ = ap->way;
E 2
	*p++ = type;
D 7
        while (c-- > 0) {
                if ((*p++ = *cd++) == IAC)
                        *p++ = IAC;
        }
        *p++ = IAC;
        *p++ = SE;
E 7
I 7
	while (c-- > 0) {
		if ((*p++ = *cd++) == IAC)
			*p++ = IAC;
	}
	*p++ = IAC;
	*p++ = SE;
E 7
	if (str_data[3] == TELQUAL_IS)
		printsub('>', &str_data[2], p - (&str_data[2]));
D 7
        return(net_write(str_data, p - str_data));
E 7
I 7
	return(net_write(str_data, p - str_data));
E 7
}

	int
kerberos4_init(ap, server)
	Authenticator *ap;
	int server;
{
D 3
	if (server)
E 3
I 3
	FILE *fp;

	if (server) {
E 3
		str_data[3] = TELQUAL_REPLY;
D 3
	else
E 3
I 3
		if ((fp = fopen(KEYFILE, "r")) == NULL)
			return(0);
		fclose(fp);
	} else {
E 3
		str_data[3] = TELQUAL_IS;
I 3
	}
E 3
D 2
	str_data[4] = ap->type;
	str_data[5] = ap->way;
E 2
	return(1);
}

char dst_realm_buf[REALM_SZ], *dest_realm = NULL;
int dst_realm_sz = REALM_SZ;

	int
kerberos4_send(ap)
	Authenticator *ap;
{
	KTEXT_ST auth;
I 4
#ifdef	ENCRYPTION
E 4
	Block enckey;
I 4
#endif	/* ENCRYPTION */
E 4
	char instance[INST_SZ];
	char *realm;
	char *krb_realmofhost();
	char *krb_get_phost();
	CREDENTIALS cred;
D 2
#if	defined(ENCRYPT)
	Schedule krb_sched;
#endif
E 2
	int r;
D 3
	
E 3
I 3

D 7
	printf("[ Trying KERBEROS4 ... ]\n");	
E 7
I 7
	printf("[ Trying KERBEROS4 ... ]\n");
E 7
E 3
	if (!UserNameRequested) {
		if (auth_debug_mode) {
			printf("Kerberos V4: no user name supplied\r\n");
		}
		return(0);
	}

D 7
	bzero(instance, sizeof(instance));
E 7
I 7
	memset(instance, 0, sizeof(instance));
E 7
I 3

E 3
	if (realm = krb_get_phost(RemoteHostName))
		strncpy(instance, realm, sizeof(instance));
I 3

E 3
	instance[sizeof(instance)-1] = '\0';

	realm = dest_realm ? dest_realm : krb_realmofhost(RemoteHostName);
I 3

E 3
	if (!realm) {
D 3
		if (auth_debug_mode) {
			printf("Kerberos V4: no realm for %s\r\n", RemoteHostName);
		}
E 3
I 3
		printf("Kerberos V4: no realm for %s\r\n", RemoteHostName);
E 3
		return(0);
	}
D 3
	if (r = krb_mk_req(&auth, "rcmd", instance, realm, 0L)) {
		if (auth_debug_mode) {
			printf("mk_req failed: %s\r\n", krb_err_txt[r]);
		}
E 3
I 3
	if (r = krb_mk_req(&auth, KRB_SERVICE_NAME, instance, realm, 0L)) {
		printf("mk_req failed: %s\r\n", krb_err_txt[r]);
E 3
		return(0);
	}
D 3
	if (r = krb_get_cred("rcmd", instance, realm, &cred)) {
		if (auth_debug_mode) {
			printf("get_cred failed: %s\r\n", krb_err_txt[r]);
		}
E 3
I 3
	if (r = krb_get_cred(KRB_SERVICE_NAME, instance, realm, &cred)) {
		printf("get_cred failed: %s\r\n", krb_err_txt[r]);
E 3
		return(0);
	}
D 2
	if (!Data(KRB_NAME, (void *)UserNameRequested, -1)) {
E 2
I 2
	if (!auth_sendname(UserNameRequested, strlen(UserNameRequested))) {
E 2
		if (auth_debug_mode)
			printf("Not enough room for user name\r\n");
		return(0);
	}
	if (auth_debug_mode)
		printf("Sent %d bytes of authentication data\r\n", auth.length);
D 2
	if (!Data(KRB_AUTH, (void *)auth.dat, auth.length)) {
E 2
I 2
	if (!Data(ap, KRB_AUTH, (void *)auth.dat, auth.length)) {
E 2
		if (auth_debug_mode)
			printf("Not enough room for authentication data\r\n");
		return(0);
	}
I 3
D 4
#if	defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
E 3
D 2
#if	defined(ENCRYPT)
	des_key_sched(cred.session, krb_sched);
	des_set_random_generator_seed(cred.session);
	des_new_random_key(session_key);
	des_ecb_encrypt(session_key, enckey, krb_sched, 1);
	Data(KRB_NEWKEY, (void *)enckey, sizeof(enckey));
#endif
E 2
I 2
	/*
	 * If we are doing mutual authentication, get set up to send
D 3
	 * the challange, and verify it when the response comes back.
E 3
I 3
	 * the challenge, and verify it when the response comes back.
E 3
	 */
	if ((ap->way & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL) {
		register int i;

		des_key_sched(cred.session, sched);
D 6
		des_set_random_generator_seed(cred.session);
D 3
		des_new_random_key(challange);
		des_ecb_encrypt(challange, session_key, sched, 1);
E 3
I 3
		des_new_random_key(challenge);
		des_ecb_encrypt(challenge, session_key, sched, 1);
E 6
I 6
		des_init_random_number_generator(cred.session);
		des_new_random_key(session_key);
		des_ecb_encrypt(session_key, session_key, sched, 0);
		des_ecb_encrypt(session_key, challenge, sched, 0);
E 6
E 3
		/*
D 3
		 * Increment the challange by 1, and encrypt it for
E 3
I 3
		 * Increment the challenge by 1, and encrypt it for
E 3
		 * later comparison.
		 */
		for (i = 7; i >= 0; --i) {
			register int x;
D 3
			x = (unsigned int)challange[i] + 1;
			challange[i] = x;	/* ignore overflow */
E 3
I 3
			x = (unsigned int)challenge[i] + 1;
			challenge[i] = x;	/* ignore overflow */
E 3
			if (x < 256)		/* if no overflow, all done */
				break;
		}
D 3
		des_ecb_encrypt(challange, challange, sched, 1);
E 3
I 3
		des_ecb_encrypt(challenge, challenge, sched, 1);
E 3
	}
I 3
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
E 3
E 2
D 7
	
E 7
I 7

E 7
	if (auth_debug_mode) {
D 3
		printf("CK: %d:", cksum(auth.dat, auth.length));
E 3
I 3
		printf("CK: %d:", kerberos4_cksum(auth.dat, auth.length));
E 3
		printd(auth.dat, auth.length);
		printf("\r\n");
		printf("Sent Kerberos V4 credentials to server\r\n");
	}
	return(1);
}

	void
kerberos4_is(ap, data, cnt)
	Authenticator *ap;
	unsigned char *data;
	int cnt;
{
I 4
#ifdef	ENCRYPTION
E 4
	Session_Key skey;
	Block datablock;
I 4
#endif	/* ENCRYPTION */
E 4
	char realm[REALM_SZ];
	char instance[INST_SZ];
D 2
	Schedule sched;
E 2
	int r;

	if (cnt-- < 1)
		return;
	switch (*data++) {
D 2
	case KRB_NAME: {
		char user[256];

		if (cnt > 255)
			cnt = 255;
		strncpy(user, (char *)data, cnt);
		user[cnt] = 0;
		auth_encrypt_user(user);
		return;
	    }
E 2
	case KRB_AUTH:
		if (krb_get_lrealm(realm, 1) != KSUCCESS) {
D 2
			Data(KRB_REJECT, (void *)"No local V4 Realm.", -1);
E 2
I 2
			Data(ap, KRB_REJECT, (void *)"No local V4 Realm.", -1);
E 2
			auth_finished(ap, AUTH_REJECT);
			if (auth_debug_mode)
				printf("No local realm\r\n");
			return;
		}
D 7
		bcopy((void *)data, (void *)auth.dat, auth.length = cnt);
E 7
I 7
		memmove((void *)auth.dat, (void *)data, auth.length = cnt);
E 7
		if (auth_debug_mode) {
			printf("Got %d bytes of authentication data\r\n", cnt);
D 3
			printf("CK: %d:", cksum(auth.dat, auth.length));
E 3
I 3
			printf("CK: %d:", kerberos4_cksum(auth.dat, auth.length));
E 3
			printd(auth.dat, auth.length);
			printf("\r\n");
		}
		instance[0] = '*'; instance[1] = 0;
D 3
		if (r = krb_rd_req(&auth, "rcmd", instance, 0, &adat, "")) {
E 3
I 3
		if (r = krb_rd_req(&auth, KRB_SERVICE_NAME,
				   instance, 0, &adat, "")) {
E 3
			if (auth_debug_mode)
				printf("Kerberos failed him as %s\r\n", name);
D 2
			Data(KRB_REJECT, (void *)krb_err_txt[r], -1);
E 2
I 2
			Data(ap, KRB_REJECT, (void *)krb_err_txt[r], -1);
E 2
			auth_finished(ap, AUTH_REJECT);
			return;
		}
I 3
#ifdef	ENCRYPTION
E 3
D 7
		bcopy((void *)adat.session, (void *)session_key, sizeof(Block));
E 7
I 7
		memmove((void *)session_key, (void *)adat.session, sizeof(Block));
E 7
I 3
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
E 3
		krb_kntoln(&adat, name);
D 2
		Data(KRB_ACCEPT, (void *)name, -1);
E 2
I 2
D 3
		Data(ap, KRB_ACCEPT, (void *)0, 0);
E 3
I 3

		if (UserNameRequested && !kuserok(&adat, UserNameRequested))
			Data(ap, KRB_ACCEPT, (void *)0, 0);
		else
			Data(ap, KRB_REJECT,
				(void *)"user is not authorized", -1);
E 3
E 2
		auth_finished(ap, AUTH_USER);
D 3
		if (auth_debug_mode) {
			printf("Kerberos accepting him as %s\r\n", name);
		}
E 3
D 2
		return;
	case KRB_NEWKEY:
#if	defined(ENCRYPT)
		if (VALIDKEY(session_key)) {
			des_key_sched(session_key, sched);
			bcopy((void *)data, (void *)datablock, sizeof(Block));
			des_ecb_encrypt(datablock, session_key, sched, 0);
			skey.type = SK_DES;
			skey.length = 8;
			skey.data = session_key;
			encrypt_session_key(&skey, 1);
E 2
I 2
		break;

D 3
	case KRB_CHALLANGE:
E 3
I 3
	case KRB_CHALLENGE:
D 4
#if	!defined(ENCRYPTION)
E 4
I 4
#ifndef	ENCRYPTION
E 4
		Data(ap, KRB_RESPONSE, (void *)0, 0);
D 4
#else
E 4
I 4
#else	/* ENCRYPTION */
E 4
E 3
		if (!VALIDKEY(session_key)) {
			/*
			 * We don't have a valid session key, so just
			 * send back a response with an empty session
			 * key.
			 */
			Data(ap, KRB_RESPONSE, (void *)0, 0);
			break;
E 2
		}
D 2
#endif
		return;
E 2
I 2

I 6
		/*
		 * Initialize the random number generator since it's
		 * used later on by the encryption routine.
		 */
		des_init_random_number_generator(session_key);
E 6
		des_key_sched(session_key, sched);
D 7
		bcopy((void *)data, (void *)datablock, sizeof(Block));
E 7
I 7
		memmove((void *)datablock, (void *)data, sizeof(Block));
E 7
		/*
D 3
		 * Take the received encrypted challange, and encrypt
E 3
I 3
		 * Take the received encrypted challenge, and encrypt
E 3
		 * it again to get a unique session_key for the
		 * ENCRYPT option.
		 */
		des_ecb_encrypt(datablock, session_key, sched, 1);
		skey.type = SK_DES;
		skey.length = 8;
		skey.data = session_key;
		encrypt_session_key(&skey, 1);
		/*
D 3
		 * Now decrypt the received encrypted challange,
E 3
I 3
		 * Now decrypt the received encrypted challenge,
E 3
		 * increment by one, re-encrypt it and send it back.
		 */
D 3
		des_ecb_encrypt(datablock, challange, sched, 0);
E 3
I 3
		des_ecb_encrypt(datablock, challenge, sched, 0);
E 3
D 6
		for (r = 7; r >= 0; r++) {
E 6
I 6
		for (r = 7; r >= 0; r--) {
E 6
			register int t;
D 3
			t = (unsigned int)challange[r] + 1;
			challange[r] = t;	/* ignore overflow */
E 3
I 3
			t = (unsigned int)challenge[r] + 1;
			challenge[r] = t;	/* ignore overflow */
E 3
			if (t < 256)		/* if no overflow, all done */
				break;
		}
D 3
		des_ecb_encrypt(challange, challange, sched, 1);
		Data(ap, KRB_RESPONSE, (void *)challange, sizeof(challange));
E 3
I 3
		des_ecb_encrypt(challenge, challenge, sched, 1);
		Data(ap, KRB_RESPONSE, (void *)challenge, sizeof(challenge));
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
E 3
		break;

E 2
	default:
		if (auth_debug_mode)
			printf("Unknown Kerberos option %d\r\n", data[-1]);
D 2
		Data(KRB_REJECT, 0, 0);
		return;
E 2
I 2
		Data(ap, KRB_REJECT, 0, 0);
		break;
E 2
	}
}

	void
kerberos4_reply(ap, data, cnt)
	Authenticator *ap;
	unsigned char *data;
	int cnt;
{
I 4
#ifdef	ENCRYPTION
E 4
	Session_Key skey;
I 4
#endif	/* ENCRYPTION */
E 4

	if (cnt-- < 1)
		return;
	switch (*data++) {
	case KRB_REJECT:
		if (cnt > 0) {
			printf("[ Kerberos V4 refuses authentication because %.*s ]\r\n",
				cnt, data);
		} else
			printf("[ Kerberos V4 refuses authentication ]\r\n");
		auth_send_retry();
		return;
	case KRB_ACCEPT:
D 2
		if (cnt > 0) {
			printf("[ Kerberos V4 accepts you as %.*s ]\n", cnt, data);
		} else
			printf("[ Kerberos V4 accepts you ]\n", cnt, data);
E 2
I 2
		printf("[ Kerberos V4 accepts you ]\n");
		if ((ap->way & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL) {
			/*
D 3
			 * Send over the encrypted challange.
E 3
I 3
			 * Send over the encrypted challenge.
E 3
		 	 */
D 3
			Data(ap, KRB_CHALLANGE, (void *)session_key,
E 3
I 3
D 4
#if	!defined(ENCRYPTION)
E 4
I 4
#ifndef	ENCRYPTION
E 4
			Data(ap, KRB_CHALLENGE, (void *)0, 0);
D 4
#else
E 4
I 4
#else	/* ENCRYPTION */
E 4
			Data(ap, KRB_CHALLENGE, (void *)session_key,
E 3
						sizeof(session_key));
E 2
D 3
#if	defined(ENCRYPT)
E 3
D 2
		skey.type = SK_DES;
		skey.length = 8;
		skey.data = session_key;
		encrypt_session_key(&skey, 0);
E 2
I 2
			des_ecb_encrypt(session_key, session_key, sched, 1);
			skey.type = SK_DES;
			skey.length = 8;
			skey.data = session_key;
			encrypt_session_key(&skey, 0);
E 2
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
I 2
			return;
		}
E 2
		auth_finished(ap, AUTH_USER);
		return;
I 2
	case KRB_RESPONSE:
I 3
D 4
#if	defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
E 3
		/*
D 3
		 * Verify that the response to the challange is correct.
E 3
I 3
		 * Verify that the response to the challenge is correct.
E 3
		 */
		if ((cnt != sizeof(Block)) ||
D 3
		    (0 != memcmp((void *)data, (void *)challange,
						sizeof(challange))))
E 3
I 3
		    (0 != memcmp((void *)data, (void *)challenge,
						sizeof(challenge))))
E 3
		{
D 3
			printf("[ Kerberos V4 challange failed!!! ]\r\n");
E 3
I 3
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
			printf("[ Kerberos V4 challenge failed!!! ]\r\n");
E 3
			auth_send_retry();
			return;
I 3
D 4
#if	defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
E 3
		}
D 3
		printf("[ Kerberos V4 challange successful ]\r\n");
E 3
I 3
		printf("[ Kerberos V4 challenge successful ]\r\n");
E 3
		auth_finished(ap, AUTH_USER);
I 3
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
E 3
		break;
E 2
	default:
		if (auth_debug_mode)
			printf("Unknown Kerberos option %d\r\n", data[-1]);
		return;
	}
}

	int
kerberos4_status(ap, name, level)
	Authenticator *ap;
	char *name;
	int level;
{
	if (level < AUTH_USER)
		return(level);

	if (UserNameRequested && !kuserok(&adat, UserNameRequested)) {
		strcpy(name, UserNameRequested);
		return(AUTH_VALID);
	} else
		return(AUTH_USER);
}

#define	BUMP(buf, len)		while (*(buf)) {++(buf), --(len);}
#define	ADDC(buf, len, c)	if ((len) > 0) {*(buf)++ = (c); --(len);}

	void
kerberos4_printsub(data, cnt, buf, buflen)
	unsigned char *data, *buf;
	int cnt, buflen;
{
	char lbuf[32];
	register int i;

	buf[buflen-1] = '\0';		/* make sure its NULL terminated */
	buflen -= 1;

	switch(data[3]) {
D 2
	case KRB_NAME:			/* Name to authenticate for */
		strncpy((char *)buf, " NAME ", buflen);
		goto common;

E 2
	case KRB_REJECT:		/* Rejected (reason might follow) */
		strncpy((char *)buf, " REJECT ", buflen);
		goto common;

	case KRB_ACCEPT:		/* Accepted (name might follow) */
		strncpy((char *)buf, " ACCEPT ", buflen);
	common:
		BUMP(buf, buflen);
		if (cnt <= 4)
			break;
		ADDC(buf, buflen, '"');
		for (i = 4; i < cnt; i++)
			ADDC(buf, buflen, data[i]);
		ADDC(buf, buflen, '"');
		ADDC(buf, buflen, '\0');
		break;

	case KRB_AUTH:			/* Authentication data follows */
		strncpy((char *)buf, " AUTH", buflen);
		goto common2;

D 2
	case KRB_NEWKEY:		/* A new session key follows */
		strncpy((char *)buf, " NEWKEY", buflen);
E 2
I 2
D 3
	case KRB_CHALLANGE:
		strncpy((char *)buf, " CHALLANGE", buflen);
E 3
I 3
	case KRB_CHALLENGE:
		strncpy((char *)buf, " CHALLENGE", buflen);
E 3
		goto common2;

	case KRB_RESPONSE:
		strncpy((char *)buf, " RESPONSE", buflen);
E 2
		goto common2;

	default:
		sprintf(lbuf, " %d (unknown)", data[3]);
		strncpy((char *)buf, lbuf, buflen);
	common2:
		BUMP(buf, buflen);
		for (i = 4; i < cnt; i++) {
			sprintf(lbuf, " %d", data[i]);
			strncpy((char *)buf, lbuf, buflen);
			BUMP(buf, buflen);
		}
		break;
	}
}

	int
D 3
cksum(d, n)
E 3
I 3
kerberos4_cksum(d, n)
E 3
	unsigned char *d;
	int n;
{
	int ck = 0;

I 3
	/*
	 * A comment is probably needed here for those not
	 * well versed in the "C" language.  Yes, this is
	 * supposed to be a "switch" with the body of the
	 * "switch" being a "while" statement.  The whole
	 * purpose of the switch is to allow us to jump into
	 * the middle of the while() loop, and then not have
	 * to do any more switch()s.
	 *
	 * Some compilers will spit out a warning message
	 * about the loop not being entered at the top.
	 */
E 3
	switch (n&03)
	while (n > 0) {
	case 0:
D 3
		ck ^= *d++ << 24;
E 3
I 3
		ck ^= (int)*d++ << 24;
E 3
		--n;
	case 3:
D 3
		ck ^= *d++ << 16;
E 3
I 3
		ck ^= (int)*d++ << 16;
E 3
		--n;
	case 2:
D 3
		ck ^= *d++ << 8;
E 3
I 3
		ck ^= (int)*d++ << 8;
E 3
		--n;
	case 1:
D 3
		ck ^= *d++;
E 3
I 3
		ck ^= (int)*d++;
E 3
		--n;
	}
	return(ck);
}
#endif

#ifdef notdef

prkey(msg, key)
	char *msg;
	unsigned char *key;
{
	register int i;
	printf("%s:", msg);
	for (i = 0; i < 8; i++)
		printf(" %3d", key[i]);
	printf("\r\n");
}
#endif
E 1
