h49053
s 00065/00063/00673
d D 8.3 95/05/30 20:13:22 dab 7 6
c Code cleanup, use mem*() instead of b*()
e
s 00169/00017/00567
d D 8.2 93/12/15 11:31:51 dab 6 5
c The lastest Kerberos V code from MIT
e
s 00002/00002/00582
d D 8.1 93/06/04 17:36:10 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00011/00011/00573
d D 5.4 93/05/20 10:51:37 dab 4 3
c Fix all the "#if defined(ENCRYPTION)" lines to just
c be "#ifdef ENCRYPTION", so that unifdef can be used to strip
c out all the encryption code.
e
s 00184/00153/00400
d D 5.3 92/12/18 14:11:13 dab 3 2
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Latest version of Kerberos V stuff
c Bug fixes
e
s 00130/00072/00423
d D 5.2 91/03/22 13:17:52 dab 2 1
c Upgrade to the latest & greatest authentication/encryption
e
s 00495/00000/00000
d D 5.1 91/02/28 22:01:31 dab 1 0
c date and time created 91/02/28 22:01:31 by dab
e
u
U
t
T
I 3
/*
D 6
 *	$Source: /afs/athena.mit.edu/astaff/project/krb5/src/appl/telnet/libtelnet/RCS/kerberos5.c,v $
 *	$Author: jtkohl $
 *	$Id: kerberos5.c,v 1.3 91/07/19 16:37:57 jtkohl Exp Locker: tytso $
E 6
I 6
 *	$Source: /mit/krb5/.cvsroot/src/appl/telnet/libtelnet/kerberos5.c,v $
 *	$Author: tytso $
 *	$Id: kerberos5.c,v 5.3 1993/09/01 03:00:12 tytso Exp $
E 6
 */

#if !defined(lint) && !defined(SABER)
static
#ifdef __STDC__
const
#endif
D 6
char rcsid_kerberos5_c[] = "$Id: kerberos5.c,v 1.3 91/07/19 16:37:57 jtkohl Exp Locker: tytso $";
E 6
I 6
char rcsid_kerberos5_c[] = "$Id: kerberos5.c,v 5.3 1993/09/01 03:00:12 tytso Exp $";
E 6
#endif /* lint */

E 3
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
D 6
 * Export of this software from the United States of America is assumed
 * to require a specific license from the United States Government.
E 6
I 6
 * Export of this software from the United States of America may
 * require a specific license from the United States Government.
E 6
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


#ifdef	KRB5
#include <arpa/telnet.h>
#include <stdio.h>
#include <krb5/krb5.h>
I 6
#include <krb5/asn1.h>
E 6
#include <krb5/crc-32.h>
D 3
#include <krb5/libos-proto.h>
E 3
I 3
#include <krb5/los-proto.h>
#include <krb5/ext-proto.h>
#include <com_err.h>
E 3
#include <netdb.h>
#include <ctype.h>

D 3
#ifdef	__STDC__
#include <stdlib.h>
#endif
#ifdef	NO_STRING_H
#include <strings.h>
#else
#include <string.h>
#endif
E 3
D 6

E 6
I 3
/* kerberos 5 include files (ext-proto.h) will get an appropriate stdlib.h
   and string.h/strings.h */
D 7
 
E 7
I 7

E 7
E 3
#include "encrypt.h"
#include "auth.h"
#include "misc.h"

extern auth_debug_mode;

I 6
#ifdef	FORWARD
int forward_flags = 0;  /* Flags get set in telnet/main.c on -f and -F */
E 6
D 3
char *malloc();
E 3

I 6
/* These values need to be the same as those defined in telnet/main.c. */
/* Either define them in both places, or put in some common header file. */
D 7
#define OPTS_FORWARD_CREDS           0x00000002
#define OPTS_FORWARDABLE_CREDS       0x00000001
E 7
I 7
#define OPTS_FORWARD_CREDS	0x00000002
#define OPTS_FORWARDABLE_CREDS	0x00000001
E 7

void kerberos5_forward();

#endif	/* FORWARD */

E 6
static unsigned char str_data[1024] = { IAC, SB, TELOPT_AUTHENTICATION, 0,
			  		AUTHTYPE_KERBEROS_V5, };
I 2
D 3
static unsigned char str_name[1024] = { IAC, SB, TELOPT_AUTHENTICATION,
					TELQUAL_NAME, };
E 3
I 3
/*static unsigned char str_name[1024] = { IAC, SB, TELOPT_AUTHENTICATION,
					TELQUAL_NAME, };*/
E 3
E 2

D 6
#define	KRB_AUTH	0		/* Authentication data follows */
#define	KRB_REJECT	1		/* Rejected (reason might follow) */
D 2
#define	KRB_ACCEPT	2		/* Accepted (name might follow) */
#define	KRB_NEWKEY	3		/* New key to use */
#define KRB_NAME        4               /* Name to authenticate for */
E 2
I 2
#define	KRB_ACCEPT	2		/* Accepted */
D 3
#define	KRB_CHALLANGE	3		/* Challange for mutual auth. */
#define	KRB_RESPONSE	4		/* Response for mutual auth. */
E 3
I 3
#define	KRB_RESPONSE	3		/* Response for mutual auth. */
E 6
I 6
#define	KRB_AUTH		0	/* Authentication data follows */
#define	KRB_REJECT		1	/* Rejected (reason might follow) */
#define	KRB_ACCEPT		2	/* Accepted */
#define	KRB_RESPONSE		3	/* Response for mutual auth. */
E 6
E 3
E 2

I 6
#ifdef	FORWARD
#define KRB_FORWARD     	4       /* Forwarded credentials follow */
#define KRB_FORWARD_ACCEPT     	5       /* Forwarded credentials accepted */
#define KRB_FORWARD_REJECT     	6       /* Forwarded credentials rejected */
#endif	/* FORWARD */

E 6
static	krb5_data auth;
	/* telnetd gets session key from here */
static	krb5_tkt_authent *authdat = NULL;
I 3
/* telnet matches the AP_REQ and AP_REP with this */
static	krb5_authenticator authenticator;
E 3

D 3
#if	defined(ENCRYPT)
E 3
I 3
/* some compilers can't hack void *, so we use the Kerberos krb5_pointer,
   which is either void * or char *, depending on the compiler. */

#define Voidptr krb5_pointer

D 4
#if	defined(ENCRYPTION)
E 4
I 4
D 6
#ifdef	ENCRYPTION
E 6
E 4
E 3
Block	session_key;
D 4
#endif
E 4
I 4
D 6
#endif	/* ENCRYPTION */
E 6
I 6

E 6
E 4
I 2
D 3
static Schedule sched;
static Block	challange;
E 2

E 3
	static int
D 2
Data(type, d, c)
E 2
I 2
Data(ap, type, d, c)
	Authenticator *ap;
E 2
	int type;
D 3
	void *d;
E 3
I 3
	Voidptr d;
E 3
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
D 2
		c = strlen(d);
E 2
I 2
		c = strlen((char *)cd);
E 2

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
		printsub('>', &str_data[2], p - &str_data[2]);
D 7
        return(net_write(str_data, p - str_data));
E 7
I 7
	return(net_write(str_data, p - str_data));
E 7
}

	int
kerberos5_init(ap, server)
	Authenticator *ap;
	int server;
{
	if (server)
		str_data[3] = TELQUAL_REPLY;
	else
		str_data[3] = TELQUAL_IS;
D 2
	str_data[4] = ap->type;
	str_data[5] = ap->way;
E 2
D 7
        krb5_init_ets();
E 7
I 7
	krb5_init_ets();
E 7
	return(1);
}

	int
kerberos5_send(ap)
	Authenticator *ap;
{
	char **realms;
	char *name;
	char *p1, *p2;
	krb5_checksum ksum;
	krb5_octet sum[CRC32_CKSUM_LENGTH];
D 3
	krb5_data *server[4];
	krb5_data srvdata[3];
E 3
I 3
 	krb5_principal server;
E 3
	krb5_error_code r;
	krb5_ccache ccache;
	krb5_creds creds;		/* telnet gets session key from here */
	extern krb5_flags krb5_kdc_default_options;
I 3
	int ap_opts;
E 3

I 3
D 4
#if     defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
	krb5_keyblock *newkey = 0;
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4

E 3
	ksum.checksum_type = CKSUMTYPE_CRC32;
	ksum.contents = sum;
	ksum.length = sizeof(sum);
D 3
	bzero((void *)sum, sizeof(sum));
E 3
I 3
D 7
	bzero((Voidptr )sum, sizeof(sum));
E 3
	
        if (!UserNameRequested) {
                if (auth_debug_mode) {
                        printf("Kerberos V5: no user name supplied\r\n");
                }
                return(0);
        }
E 7
I 7
	memset((Voidptr )sum, 0, sizeof(sum));
E 7

I 7
	if (!UserNameRequested) {
		if (auth_debug_mode) {
			printf("Kerberos V5: no user name supplied\r\n");
		}
		return(0);
	}

E 7
	if (r = krb5_cc_default(&ccache)) {
		if (auth_debug_mode) {
			printf("Kerberos V5: could not get default ccache\r\n");
		}
		return(0);
	}

	if ((name = malloc(strlen(RemoteHostName)+1)) == NULL) {
		if (auth_debug_mode)
			printf("Out of memory for hostname in Kerberos V5\r\n");
		return(0);
	}

	if (r = krb5_get_host_realm(RemoteHostName, &realms)) {
		if (auth_debug_mode)
			printf("Kerberos V5: no realm for %s\r\n", RemoteHostName);
		free(name);
		return(0);
	}

	p1 = RemoteHostName;
	p2 = name;

	while (*p2 = *p1++) {
		if (isupper(*p2))
			*p2 |= 040;
		++p2;
	}

D 3
	srvdata[0].data = realms[0];
	srvdata[0].length = strlen(realms[0]);
	srvdata[1].data = "rcmd";
	srvdata[1].length = 4;
	srvdata[2].data = name;
	srvdata[2].length = p2 - name;
E 3
I 3
	if (r = krb5_build_principal_ext(&server,
					 strlen(realms[0]), realms[0],
D 6
					 4, "rcmd",
E 6
I 6
					 4, "host",
E 6
					 p2 - name, name,
					 0)) {
		if (auth_debug_mode) {
			printf("Kerberos V5: failure setting up principal (%s)\r\n",
			       error_message(r));
		}
		free(name);
		krb5_free_host_realm(realms);
		return(0);
	}
D 7
					 
E 7
E 3

D 3
	server[0] = &srvdata[0];
	server[1] = &srvdata[1];
	server[2] = &srvdata[2];
	server[3] = 0;

E 3
D 7
	bzero((char *)&creds, sizeof(creds));
E 7
I 7

	memset((char *)&creds, 0, sizeof(creds));
E 7
D 3
	creds.server = (krb5_principal)server;
E 3
I 3
	creds.server = server;
E 3

	if (r = krb5_cc_get_principal(ccache, &creds.client)) {
		if (auth_debug_mode) {
D 3
			printf("Keberos V5: failure on principal (%d)\r\n",
E 3
I 3
			printf("Kerberos V5: failure on principal (%s)\r\n",
E 3
				error_message(r));
		}
		free(name);
I 3
		krb5_free_principal(server);
E 3
		krb5_free_host_realm(realms);
		return(0);
	}

	if (r = krb5_get_credentials(krb5_kdc_default_options, ccache, &creds)) {
		if (auth_debug_mode) {
D 3
			printf("Keberos V5: failure on credentials(%d)\r\n",r);
E 3
I 3
			printf("Kerberos V5: failure on credentials(%d)\r\n",r);
E 3
		}
		free(name);
		krb5_free_host_realm(realms);
I 3
		krb5_free_principal(server);
E 3
		return(0);
	}

D 3
	r = krb5_mk_req_extended(0, &ksum, &creds.times,
				 krb5_kdc_default_options,
				 ccache, &creds, 0, &auth);
E 3
I 3
	if ((ap->way & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL)
	    ap_opts = AP_OPTS_MUTUAL_REQUIRED;
	else
	    ap_opts = 0;
D 7
	    
E 7
I 7

E 7
	r = krb5_mk_req_extended(ap_opts, &ksum, krb5_kdc_default_options, 0,
D 4
#if	defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
				 &newkey,
D 4
#else
E 4
I 4
#else	/* ENCRYPTION */
E 4
				 0,
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
				 ccache, &creds, &authenticator, &auth);
	/* don't let the key get freed if we clean up the authenticator */
	authenticator.subkey = 0;
E 3

	free(name);
	krb5_free_host_realm(realms);
I 3
	krb5_free_principal(server);
D 4
#if	defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
	if (newkey) {
	    /* keep the key in our private storage, but don't use it
	       yet---see kerberos5_reply() below */
	    if (newkey->keytype != KEYTYPE_DES) {
		if (creds.keyblock.keytype == KEYTYPE_DES)
		    /* use the session key in credentials instead */
D 7
		    memcpy((char *)session_key,
E 7
I 7
		    memmove((char *)session_key,
E 7
			   (char *)creds.keyblock.contents, sizeof(Block));
		else
		    /* XXX ? */;
	    } else {
D 7
		memcpy((char *)session_key, (char *)newkey->contents,
E 7
I 7
		memmove((char *)session_key, (char *)newkey->contents,
E 7
		       sizeof(Block));
	    }
	    krb5_free_keyblock(newkey);
	}
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
E 3
	if (r) {
		if (auth_debug_mode) {
D 3
			printf("Keberos V5: mk_req failed\r\n");
E 3
I 3
			printf("Kerberos V5: mk_req failed (%s)\r\n",
			       error_message(r));
E 3
		}
		return(0);
	}

D 2
        if (!Data(KRB_NAME, (void *)UserNameRequested, -1)) {
E 2
I 2
D 7
        if (!auth_sendname(UserNameRequested, strlen(UserNameRequested))) {
E 2
                if (auth_debug_mode)
                        printf("Not enough room for user name\r\n");
                return(0);
        }
E 7
I 7
	if (!auth_sendname(UserNameRequested, strlen(UserNameRequested))) {
		if (auth_debug_mode)
			printf("Not enough room for user name\r\n");
		return(0);
	}
E 7
D 2
	if (!Data(KRB_AUTH, auth.data, auth.length)) {
E 2
I 2
	if (!Data(ap, KRB_AUTH, auth.data, auth.length)) {
E 2
		if (auth_debug_mode)
			printf("Not enough room for authentication data\r\n");
		return(0);
	}
D 2
#if     defined(ENCRYPT)
	if (creds.keyblock.keytype == KEYTYPE_DES) {
		Schedule krb_sched;
		Block enckey;
E 2
I 2
D 3
	/*
	 * If we are doing mutual authentication, get set up to send
	 * the challange, and verify it when the response comes back.
	 */
	if (((ap->way & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL)
	    && (creds.keyblock.keytype == KEYTYPE_DES)) {
		register int i;
E 2

D 2
		des_key_sched(creds.keyblock.contents, krb_sched);
E 2
I 2
		des_key_sched(creds.keyblock.contents, sched);
E 2
		des_set_random_generator_seed(creds.keyblock.contents);
D 2
		des_new_random_key(session_key);
		des_ecb_encrypt(session_key, enckey, krb_sched, 1);
		Data(KRB_NEWKEY, (void *)enckey, sizeof(enckey));
E 2
I 2
		des_new_random_key(challange);
		des_ecb_encrypt(challange, session_key, sched, 1);
		/*
		 * Increment the challange by 1, and encrypt it for
		 * later comparison.
		 */
		for (i = 7; i >= 0; --i) {
			register int x;
			x = (unsigned int)challange[i] + 1;
			challange[i] = x;	/* ignore overflow */
			if (x < 256)		/* if no overflow, all done */
				break;
		}
		des_ecb_encrypt(challange, challange, sched, 1);
E 2
	}
D 2
#endif
E 2
I 2
	
E 3
E 2
	if (auth_debug_mode) {
		printf("Sent Kerberos V5 credentials to server\r\n");
	}
	return(1);
}

	void
kerberos5_is(ap, data, cnt)
	Authenticator *ap;
	unsigned char *data;
	int cnt;
{
	int r;
	struct hostent *hp;
	char *p1, *p2;
	static char *realm = NULL;
D 3
	krb5_data *server[4];
	krb5_data srvdata[3];
D 2
        Schedule sched;
E 2
        Session_Key skey;
E 3
I 3
	krb5_principal server;
	krb5_ap_rep_enc_part reply;
	krb5_data outbuf;
I 6
#ifdef ENCRYPTION
E 6
	Session_Key skey;
I 6
#endif	/* ENCRYPTION */
E 6
E 3
	char *name;
	char *getenv();
I 6
	krb5_data inbuf;
E 6

	if (cnt-- < 1)
		return;
	switch (*data++) {
D 2
        case KRB_NAME: {
                char user[256];

                if (cnt > 255)
                        cnt = 255;
                strncpy(user, data, cnt);
                user[cnt] = 0;
                auth_encrypt_user(user);
                return;
            }
E 2
	case KRB_AUTH:
		auth.data = (char *)data;
		auth.length = cnt;

		if (!(hp = gethostbyname(LocalHostName))) {
			if (auth_debug_mode)
				printf("Cannot resolve local host name\r\n");
D 2
			Data(KRB_REJECT, "Unknown local hostname.", -1);
E 2
I 2
			Data(ap, KRB_REJECT, "Unknown local hostname.", -1);
E 2
			auth_finished(ap, AUTH_REJECT);
			return;
		}

		if (!realm && (krb5_get_default_realm(&realm))) {
			if (auth_debug_mode)
D 3
				printf("Could not get defualt realm\r\n");
E 3
I 3
				printf("Could not get default realm\r\n");
E 3
D 2
			Data(KRB_REJECT, "Could not get default realm.", -1);
E 2
I 2
			Data(ap, KRB_REJECT, "Could not get default realm.", -1);
E 2
			auth_finished(ap, AUTH_REJECT);
			return;
		}

		if ((name = malloc(strlen(hp->h_name)+1)) == NULL) {
			if (auth_debug_mode)
				printf("Out of memory for hostname in Kerberos V5\r\n");
D 2
			Data(KRB_REJECT, "Out of memory.", -1);
E 2
I 2
			Data(ap, KRB_REJECT, "Out of memory.", -1);
E 2
			auth_finished(ap, AUTH_REJECT);
			return;
		}

		p1 = hp->h_name;
		p2 = name;

		while (*p2 = *p1++) {
			if (isupper(*p2))
				*p2 |= 040;
			++p2;
		}

D 3
		srvdata[0].data = realm;
		srvdata[0].length = strlen(realm);
		srvdata[1].data = "rcmd";
		srvdata[1].length = 4;
		srvdata[2].data = name;
		srvdata[2].length = p2 - name;

		server[0] = &srvdata[0];
		server[1] = &srvdata[1];
		server[2] = &srvdata[2];
		server[3] = 0;

E 3
		if (authdat)
			krb5_free_tkt_authent(authdat);
D 3
		if (r = krb5_rd_req_simple(&auth, server, 0, &authdat)) {
E 3
I 3

D 7
	        r = krb5_build_principal_ext(&server,
E 7
I 7
		r = krb5_build_principal_ext(&server,
E 7
					     strlen(realm), realm,
D 6
					     4, "rcmd",
E 6
I 6
					     4, "host",
E 6
					     p2 - name, name,
					     0);
		if (!r) {
		    r = krb5_rd_req_simple(&auth, server, 0, &authdat);
		    krb5_free_principal(server);
		}
		if (r) {
E 3
			char errbuf[128];

I 3
		    errout:
E 3
			authdat = 0;
			(void) strcpy(errbuf, "Read req failed: ");
			(void) strcat(errbuf, error_message(r));
D 2
			Data(KRB_REJECT, errbuf, -1);
E 2
I 2
			Data(ap, KRB_REJECT, errbuf, -1);
E 2
			if (auth_debug_mode)
				printf("%s\r\n", errbuf);
			return;
		}
		free(name);
I 3
		if ((ap->way & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL) {
		    /* do ap_rep stuff here */
		    reply.ctime = authdat->authenticator->ctime;
		    reply.cusec = authdat->authenticator->cusec;
		    reply.subkey = 0;	/* use the one he gave us, so don't
					   need to return one here */
		    reply.seq_number = 0; /* we don't do seq #'s. */

		    if (r = krb5_mk_rep(&reply,
					authdat->authenticator->subkey ?
					authdat->authenticator->subkey :
					authdat->ticket->enc_part2->session,
					&outbuf)) {
			goto errout;
		    }
		    Data(ap, KRB_RESPONSE, outbuf.data, outbuf.length);
D 7
		} 
E 7
I 7
		}
E 7
E 3
		if (krb5_unparse_name(authdat->ticket->enc_part2 ->client,
				      					&name))
			name = 0;
D 2
		Data(KRB_ACCEPT, name, name ? -1 : 0);
E 2
I 2
		Data(ap, KRB_ACCEPT, name, name ? -1 : 0);
E 2
		if (auth_debug_mode) {
D 3
			printf("Kerberos5 accepting him as ``%s''\r\n",
E 3
I 3
			printf("Kerberos5 identifies him as ``%s''\r\n",
E 3
							name ? name : "");
		}
D 7
                auth_finished(ap, AUTH_USER);
D 2
                return;
        case KRB_NEWKEY:
#if     defined(ENCRYPT)
		if (authdat && authdat->ticket->enc_part2->session->keytype
				== KEYTYPE_DES)
		{
			des_key_sched(authdat->ticket->enc_part2->session
							->contents, sched);
			des_ecb_encrypt(data, session_key, sched, 0);
			skey.type = SK_DES;
			skey.length = 8;
			skey.data = session_key;
			encrypt_session_key(&skey, 1);
E 2
I 2
D 3
		if (authdat->ticket->enc_part2->session->keytype != KEYTYPE_DES)
			break;
		bcopy((void *)authdat->ticket->enc_part2->session->contents,
		      (void *)session_key, sizeof(Block));
		break;
E 3
I 3
		
E 7
I 7
		auth_finished(ap, AUTH_USER);

E 7
		free(name);
	    	if (authdat->authenticator->subkey &&
		    authdat->authenticator->subkey->keytype == KEYTYPE_DES) {
D 7
		    bcopy((Voidptr )authdat->authenticator->subkey->contents,
			  (Voidptr )session_key, sizeof(Block));
E 7
I 7
		    memmove((Voidptr )session_key,
			   (Voidptr )authdat->authenticator->subkey->contents,
			   sizeof(Block));
E 7
		} else if (authdat->ticket->enc_part2->session->keytype ==
			   KEYTYPE_DES) {
D 7
		    bcopy((Voidptr )authdat->ticket->enc_part2->session->contents,
			  (Voidptr )session_key, sizeof(Block));
E 7
I 7
		    memmove((Voidptr )session_key,
			(Voidptr )authdat->ticket->enc_part2->session->contents,
			sizeof(Block));
E 7
		} else
		    break;
E 3
D 6

E 6
I 6
D 7
		
E 7
I 7

E 7
#ifdef ENCRYPTION
E 6
D 3
	case KRB_CHALLANGE:
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

		des_key_sched(session_key, sched);
		bcopy((void *)data, (void *)datablock, sizeof(Block));
		/*
		 * Take the received encrypted challange, and encrypt
		 * it again to get a unique session_key for the
		 * ENCRYPT option.
		 */
		des_ecb_encrypt(datablock, session_key, sched, 1);
E 3
		skey.type = SK_DES;
		skey.length = 8;
		skey.data = session_key;
		encrypt_session_key(&skey, 1);
I 6
#endif	/* ENCRYPTION */
E 6
D 3
		/*
		 * Now decrypt the received encrypted challange,
		 * increment by one, re-encrypt it and send it back.
		 */
		des_ecb_encrypt(datablock, challange, sched, 0);
		for (r = 7; r >= 0; r++) {
			register int t;
			t = (unsigned int)challange[r] + 1;
			challange[r] = t;	/* ignore overflow */
			if (t < 256)		/* if no overflow, all done */
				break;
		}
		des_ecb_encrypt(challange, challange, sched, 1);
		Data(ap, KRB_RESPONSE, (void *)challange, sizeof(challange));
E 3
		break;
I 6
#ifdef	FORWARD
	case KRB_FORWARD:
		inbuf.data = (char *)data;
		inbuf.length = cnt;
D 7
		if (r = rd_and_store_for_creds(&inbuf, authdat->ticket, 
E 7
I 7
		if (r = rd_and_store_for_creds(&inbuf, authdat->ticket,
E 7
					       UserNameRequested)) {
		    char errbuf[128];
D 7
		    
E 7
I 7

E 7
		    (void) strcpy(errbuf, "Read forwarded creds failed: ");
		    (void) strcat(errbuf, error_message(r));
		    Data(ap, KRB_FORWARD_REJECT, errbuf, -1);
		    if (auth_debug_mode)
		      printf("Could not read forwarded credentials\r\n");
		}
D 7
		else 
E 7
I 7
		else
E 7
		  Data(ap, KRB_FORWARD_ACCEPT, 0, 0);
		  if (auth_debug_mode)
		    printf("Forwarded credentials obtained\r\n");
		break;
#endif	/* FORWARD */
E 6
D 3

E 3
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
kerberos5_reply(ap, data, cnt)
	Authenticator *ap;
	unsigned char *data;
	int cnt;
{
D 7
        Session_Key skey;
E 7
I 7
	Session_Key skey;
E 7
I 3
	static int mutual_complete = 0;
E 3

	if (cnt-- < 1)
		return;
	switch (*data++) {
	case KRB_REJECT:
		if (cnt > 0) {
			printf("[ Kerberos V5 refuses authentication because %.*s ]\r\n",
				cnt, data);
		} else
			printf("[ Kerberos V5 refuses authentication ]\r\n");
		auth_send_retry();
		return;
	case KRB_ACCEPT:
D 2
		if (cnt > 0) {
			printf("[ Kerberos V5 accepts you as %.*s ]\n", cnt, data);
		} else
			printf("[ Kerberos V5 accepts you ]\n", cnt, data);
E 2
I 2
D 3
		printf("[ Kerberos V5 accepts you ]\n", cnt, data);
E 3
I 3
		if ((ap->way & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL &&
		    !mutual_complete) {
		    printf("[ Kerberos V5 accepted you, but didn't provide mutual authentication! ]\n");
		    auth_send_retry();
		    return;
		}
		if (cnt)
		    printf("[ Kerberos V5 accepts you as ``%.*s'' ]\n", cnt, data);
		else
		    printf("[ Kerberos V5 accepts you ]\n");
		auth_finished(ap, AUTH_USER);
I 6
#ifdef	FORWARD
		if (forward_flags & OPTS_FORWARD_CREDS)
		  kerberos5_forward(ap);
#endif	/* FORWARD */
E 6
		break;
	case KRB_RESPONSE:
E 3
		if ((ap->way & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL) {
D 3
			/*
			 * Send over the encrypted challange.
		 	 */
			Data(ap, KRB_CHALLANGE, (void *)session_key,
						sizeof(session_key));
E 2
#if	defined(ENCRYPT)
D 2
                skey.type = SK_DES;
                skey.length = 8;
                skey.data = session_key;
                encrypt_session_key(&skey, 0);
E 2
I 2
			des_ecb_encrypt(session_key, session_key, sched, 1);
E 3
I 3
		    /* the rest of the reply should contain a krb_ap_rep */
		    krb5_ap_rep_enc_part *reply;
		    krb5_data inbuf;
		    krb5_error_code r;
		    krb5_keyblock tmpkey;

		    inbuf.length = cnt;
		    inbuf.data = (char *)data;

		    tmpkey.keytype = KEYTYPE_DES;
		    tmpkey.contents = session_key;
		    tmpkey.length = sizeof(Block);

		    if (r = krb5_rd_rep(&inbuf, &tmpkey, &reply)) {
			printf("[ Mutual authentication failed: %s ]\n",
			       error_message(r));
			auth_send_retry();
			return;
		    }
		    if (reply->ctime != authenticator.ctime ||
			reply->cusec != authenticator.cusec) {
			printf("[ Mutual authentication failed (mismatched KRB_AP_REP) ]\n");
			auth_send_retry();
			return;
		    }
		    krb5_free_ap_rep_enc_part(reply);
D 4
#if	defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
E 3
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
D 2
                auth_finished(ap, AUTH_USER);
E 2
I 2
D 3
			return;
E 3
I 3
		    mutual_complete = 1;
E 3
		}
D 3
		auth_finished(ap, AUTH_USER);
E 3
E 2
		return;
I 6
#ifdef	FORWARD
	case KRB_FORWARD_ACCEPT:
		printf("[ Kerberos V5 accepted forwarded credentials ]\n");
		return;
	case KRB_FORWARD_REJECT:
		printf("[ Kerberos V5 refuses forwarded credentials because %.*s ]\r\n",
				cnt, data);
		return;
#endif	/* FORWARD */
E 6
I 2
D 3
	case KRB_RESPONSE:
		/*
		 * Verify that the response to the challange is correct.
		 */
		if ((cnt != sizeof(Block)) ||
		    (0 != memcmp((void *)data, (void *)challange,
						sizeof(challange))))
		{
			printf("[ Kerberos V5 challange failed!!! ]\r\n");
			auth_send_retry();
			return;
		}
		printf("[ Kerberos V5 challange successful ]\r\n");
		auth_finished(ap, AUTH_USER);
		break;
E 3
E 2
	default:
		if (auth_debug_mode)
			printf("Unknown Kerberos option %d\r\n", data[-1]);
		return;
	}
}

	int
kerberos5_status(ap, name, level)
	Authenticator *ap;
	char *name;
	int level;
{
	if (level < AUTH_USER)
		return(level);

	if (UserNameRequested &&
	    krb5_kuserok(authdat->ticket->enc_part2->client, UserNameRequested))
	{
		strcpy(name, UserNameRequested);
		return(AUTH_VALID);
	} else
		return(AUTH_USER);
}

#define	BUMP(buf, len)		while (*(buf)) {++(buf), --(len);}
D 3
#define	ADDC(buf, len, c)	if ((len) > 0) {*(buf)++ = (c); --(len));}
E 3
I 3
#define	ADDC(buf, len, c)	if ((len) > 0) {*(buf)++ = (c); --(len);}
E 3

	void
kerberos5_printsub(data, cnt, buf, buflen)
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
		strncpy(buf, " NAME ", buflen);
		goto common;

E 2
	case KRB_REJECT:		/* Rejected (reason might follow) */
D 2
		strncpy(buf, " REJECT ", buflen);
E 2
I 2
		strncpy((char *)buf, " REJECT ", buflen);
E 2
		goto common;

	case KRB_ACCEPT:		/* Accepted (name might follow) */
D 2
		strncpy(buf, " ACCEPT ", buflen);
E 2
I 2
		strncpy((char *)buf, " ACCEPT ", buflen);
E 2
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

I 3

E 3
	case KRB_AUTH:			/* Authentication data follows */
D 2
		strncpy(buf, " AUTH", buflen);
E 2
I 2
		strncpy((char *)buf, " AUTH", buflen);
E 2
D 3
		goto common2;

D 2
	case KRB_NEWKEY:		/* A new session key follows */
		strncpy(buf, " NEWKEY", buflen);
E 2
I 2
	case KRB_CHALLANGE:
		strncpy((char *)buf, " CHALLANGE", buflen);
E 3
E 2
		goto common2;

I 2
	case KRB_RESPONSE:
		strncpy((char *)buf, " RESPONSE", buflen);
		goto common2;

I 6
#ifdef	FORWARD
D 7
	case KRB_FORWARD:               /* Forwarded credentials follow */
E 7
I 7
	case KRB_FORWARD:		/* Forwarded credentials follow */
E 7
		strncpy((char *)buf, " FORWARD", buflen);
		goto common2;

D 7
	case KRB_FORWARD_ACCEPT:               /* Forwarded credentials accepted */
E 7
I 7
	case KRB_FORWARD_ACCEPT:	/* Forwarded credentials accepted */
E 7
		strncpy((char *)buf, " FORWARD_ACCEPT", buflen);
		goto common2;

D 7
	case KRB_FORWARD_REJECT:               /* Forwarded credentials rejected */
E 7
I 7
	case KRB_FORWARD_REJECT:	/* Forwarded credentials rejected */
E 7
					       /* (reason might follow) */
		strncpy((char *)buf, " FORWARD_REJECT", buflen);
		goto common2;
#endif	/* FORWARD */

E 6
E 2
	default:
		sprintf(lbuf, " %d (unknown)", data[3]);
D 2
		strncpy(buf, lbuf, buflen);
E 2
I 2
		strncpy((char *)buf, lbuf, buflen);
E 2
	common2:
		BUMP(buf, buflen);
		for (i = 4; i < cnt; i++) {
			sprintf(lbuf, " %d", data[i]);
D 2
			strncpy(buf, lbuf, buflen);
E 2
I 2
			strncpy((char *)buf, lbuf, buflen);
E 2
			BUMP(buf, buflen);
		}
		break;
	}
}
D 6
#endif
E 6
I 6

#ifdef	FORWARD
D 7
        void
E 7
I 7
	void
E 7
kerberos5_forward(ap)
     Authenticator *ap;
{
    struct hostent *hp;
    krb5_creds *local_creds;
    krb5_error_code r;
    krb5_data forw_creds;
    extern krb5_cksumtype krb5_kdc_req_sumtype;
    krb5_ccache ccache;
    int i;

D 7
    if (!(local_creds = (krb5_creds *) 
E 7
I 7
    if (!(local_creds = (krb5_creds *)
E 7
	  calloc(1, sizeof(*local_creds)))) {
D 7
	if (auth_debug_mode) 
E 7
I 7
	if (auth_debug_mode)
E 7
	  printf("Kerberos V5: could not allocate memory for credentials\r\n");
	return;
    }

    if (r = krb5_sname_to_principal(RemoteHostName, "host", 1,
				    &local_creds->server)) {
D 7
	if (auth_debug_mode) 
E 7
I 7
	if (auth_debug_mode)
E 7
	  printf("Kerberos V5: could not build server name - %s\r\n",
		 error_message(r));
	krb5_free_creds(local_creds);
	return;
    }

    if (r = krb5_cc_default(&ccache)) {
D 7
	if (auth_debug_mode) 
E 7
I 7
	if (auth_debug_mode)
E 7
	  printf("Kerberos V5: could not get default ccache - %s\r\n",
		 error_message(r));
	krb5_free_creds(local_creds);
	return;
    }

    if (r = krb5_cc_get_principal(ccache, &local_creds->client)) {
D 7
	if (auth_debug_mode) 
E 7
I 7
	if (auth_debug_mode)
E 7
	  printf("Kerberos V5: could not get default principal - %s\r\n",
		 error_message(r));
	krb5_free_creds(local_creds);
	return;
    }

    /* Get ticket from credentials cache */
    if (r = krb5_get_credentials(KRB5_GC_CACHED, ccache, local_creds)) {
D 7
	if (auth_debug_mode) 
E 7
I 7
	if (auth_debug_mode)
E 7
	  printf("Kerberos V5: could not obtain credentials - %s\r\n",
		 error_message(r));
	krb5_free_creds(local_creds);
	return;
    }

    if (r = get_for_creds(ETYPE_DES_CBC_CRC,
			  krb5_kdc_req_sumtype,
			  RemoteHostName,
			  local_creds->client,
			  &local_creds->keyblock,
			  forward_flags & OPTS_FORWARDABLE_CREDS,
			  &forw_creds)) {
D 7
	if (auth_debug_mode) 
E 7
I 7
	if (auth_debug_mode)
E 7
	  printf("Kerberos V5: error getting forwarded creds - %s\r\n",
		 error_message(r));
	krb5_free_creds(local_creds);
	return;
    }
D 7
    
E 7
I 7

E 7
    /* Send forwarded credentials */
    if (!Data(ap, KRB_FORWARD, forw_creds.data, forw_creds.length)) {
	if (auth_debug_mode)
	  printf("Not enough room for authentication data\r\n");
    }
    else {
	if (auth_debug_mode)
	  printf("Forwarded local Kerberos V5 credentials to server\r\n");
    }

    krb5_free_creds(local_creds);
}
#endif	/* FORWARD */

#endif /* KRB5 */
E 6
E 1
