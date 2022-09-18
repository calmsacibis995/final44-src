h35844
s 00004/00004/00641
d D 8.3 95/05/30 20:13:25 dab 7 6
c Code cleanup, use mem*() instead of b*()
e
s 00020/00007/00625
d D 8.2 95/02/16 11:25:15 dab 6 5
c Fix a problem with KRB4 mutual authentication where
c the key that was generated for encryption was not a valid key.
c Also put in some bug fixes, and a couple of spelling fixes.
e
s 00002/00002/00630
d D 8.1 93/06/04 17:35:07 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00630
d D 5.4 93/05/20 10:51:40 dab 4 3
c Fix all the "#if defined(ENCRYPTION)" lines to just
c be "#ifdef ENCRYPTION", so that unifdef can be used to strip
c out all the encryption code.
e
s 00066/00004/00566
d D 5.3 92/12/18 14:11:18 dab 3 2
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Latest version of Kerberos V stuff
c Bug fixes
e
s 00076/00018/00494
d D 5.2 91/03/22 13:17:44 dab 2 1
c Upgrade to the latest & greatest authentication/encryption
e
s 00512/00000/00000
d D 5.1 91/02/28 22:01:27 dab 1 0
c date and time created 91/02/28 22:01:27 by dab
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


D 3
#if	defined(AUTHENTICATE)
E 3
I 3
#if	defined(AUTHENTICATION)
E 3
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#define	AUTH_NAMES
#include <arpa/telnet.h>
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
#include "misc-proto.h"
#include "auth-proto.h"

#define	typemask(x)		(1<<((x)-1))

I 3
#ifdef	KRB4_ENCPWD
extern krb4encpwd_init();
extern krb4encpwd_send();
extern krb4encpwd_is();
extern krb4encpwd_reply();
extern krb4encpwd_status();
extern krb4encpwd_printsub();
#endif

#ifdef	RSA_ENCPWD
extern rsaencpwd_init();
extern rsaencpwd_send();
extern rsaencpwd_is();
extern rsaencpwd_reply();
extern rsaencpwd_status();
extern rsaencpwd_printsub();
#endif

E 3
int auth_debug_mode = 0;
static 	char	*Name = "Noname";
static	int	Server = 0;
static	Authenticator	*authenticated = 0;
static	int	authenticating = 0;
static	int	validuser = 0;
D 2
static	char	valid_name[256];
E 2
static	unsigned char	_auth_send_data[256];
static	unsigned char	*auth_send_data;
static	int	auth_send_cnt = 0;

/*
 * Authentication types supported.  Plese note that these are stored
 * in priority order, i.e. try the first one first.
 */
Authenticator authenticators[] = {
I 3
#ifdef	SPX
	{ AUTHTYPE_SPX, AUTH_WHO_CLIENT|AUTH_HOW_MUTUAL,
				spx_init,
				spx_send,
				spx_is,
				spx_reply,
				spx_status,
				spx_printsub },
	{ AUTHTYPE_SPX, AUTH_WHO_CLIENT|AUTH_HOW_ONE_WAY,
				spx_init,
				spx_send,
				spx_is,
				spx_reply,
				spx_status,
				spx_printsub },
#endif
E 3
#ifdef	KRB5
I 3
# ifdef	ENCRYPTION
E 3
I 2
	{ AUTHTYPE_KERBEROS_V5, AUTH_WHO_CLIENT|AUTH_HOW_MUTUAL,
				kerberos5_init,
				kerberos5_send,
				kerberos5_is,
				kerberos5_reply,
				kerberos5_status,
				kerberos5_printsub },
I 3
D 4
# endif
E 4
I 4
# endif	/* ENCRYPTION */
E 4
E 3
E 2
	{ AUTHTYPE_KERBEROS_V5, AUTH_WHO_CLIENT|AUTH_HOW_ONE_WAY,
				kerberos5_init,
				kerberos5_send,
				kerberos5_is,
				kerberos5_reply,
				kerberos5_status,
				kerberos5_printsub },
#endif
#ifdef	KRB4
I 3
# ifdef ENCRYPTION
E 3
I 2
	{ AUTHTYPE_KERBEROS_V4, AUTH_WHO_CLIENT|AUTH_HOW_MUTUAL,
				kerberos4_init,
				kerberos4_send,
				kerberos4_is,
				kerberos4_reply,
				kerberos4_status,
				kerberos4_printsub },
I 3
D 4
# endif
E 4
I 4
# endif	/* ENCRYPTION */
E 4
E 3
E 2
	{ AUTHTYPE_KERBEROS_V4, AUTH_WHO_CLIENT|AUTH_HOW_ONE_WAY,
				kerberos4_init,
				kerberos4_send,
				kerberos4_is,
				kerberos4_reply,
				kerberos4_status,
				kerberos4_printsub },
#endif
I 3
#ifdef	KRB4_ENCPWD
	{ AUTHTYPE_KRB4_ENCPWD, AUTH_WHO_CLIENT|AUTH_HOW_MUTUAL,
				krb4encpwd_init,
				krb4encpwd_send,
				krb4encpwd_is,
				krb4encpwd_reply,
				krb4encpwd_status,
				krb4encpwd_printsub },
#endif
#ifdef	RSA_ENCPWD
	{ AUTHTYPE_RSA_ENCPWD, AUTH_WHO_CLIENT|AUTH_HOW_ONE_WAY,
				rsaencpwd_init,
				rsaencpwd_send,
				rsaencpwd_is,
				rsaencpwd_reply,
				rsaencpwd_status,
				rsaencpwd_printsub },
#endif
E 3
D 2
#ifdef	SIMPLE_AUTH
	{ AUTHTYPE_TEST,	AUTH_WHO_CLIENT|AUTH_HOW_ONE_WAY,
				simple_auth_init,
				simple_auth_send,
				simple_auth_is_reply,
				simple_auth_is_reply,
				0,
				simple_auth_printsub },
#endif
E 2
	{ 0, },
};

static Authenticator NoAuth = { 0 };

static int	i_support = 0;
static int	i_wont_support = 0;

	Authenticator *
findauthenticator(type, way)
	int type;
	int way;
{
	Authenticator *ap = authenticators;

	while (ap->type && (ap->type != type || ap->way != way))
		++ap;
	return(ap->type ? ap : 0);
}

	void
auth_init(name, server)
	char *name;
	int server;
{
	Authenticator *ap = authenticators;

	Server = server;
	Name = name;

	i_support = 0;
	authenticated = 0;
	authenticating = 0;
	while (ap->type) {
		if (!ap->init || (*ap->init)(ap, server)) {
			i_support |= typemask(ap->type);
			if (auth_debug_mode)
D 2
				printf(">>>%s: I support auth type %d\r\n",
E 2
I 2
				printf(">>>%s: I support auth type %d %d\r\n",
E 2
					Name,
D 2
					ap->type);
E 2
I 2
					ap->type, ap->way);
E 2
		}
I 6
		else if (auth_debug_mode)
			printf(">>>%s: Init failed: auth type %d %d\r\n",
				Name, ap->type, ap->way);
E 6
		++ap;
	}
}

	void
auth_disable_name(name)
	char *name;
{
	int x;
	for (x = 0; x < AUTHTYPE_CNT; ++x) {
		if (!strcasecmp(name, AUTHTYPE_NAME(x))) {
			i_wont_support |= typemask(x);
			break;
		}
	}
}

	int
getauthmask(type, maskp)
	char *type;
	int *maskp;
{
	register int x;

D 6
	if (strcasecmp(type, AUTHTYPE_NAME(0))) {
E 6
I 6
	if (!strcasecmp(type, AUTHTYPE_NAME(0))) {
E 6
		*maskp = -1;
		return(1);
	}

	for (x = 1; x < AUTHTYPE_CNT; ++x) {
		if (!strcasecmp(type, AUTHTYPE_NAME(x))) {
			*maskp = typemask(x);
			return(1);
		}
	}
	return(0);
}

	int
auth_enable(type)
D 6
	int type;
E 6
I 6
	char *type;
E 6
{
	return(auth_onoff(type, 1));
}

	int
auth_disable(type)
D 6
	int type;
E 6
I 6
	char *type;
E 6
{
	return(auth_onoff(type, 0));
}

	int
auth_onoff(type, on)
	char *type;
	int on;
{
D 6
	int mask = -1;
E 6
I 6
	int i, mask = -1;
E 6
	Authenticator *ap;

	if (!strcasecmp(type, "?") || !strcasecmp(type, "help")) {
D 7
                printf("auth %s 'type'\n", on ? "enable" : "disable");
E 7
I 7
		printf("auth %s 'type'\n", on ? "enable" : "disable");
E 7
		printf("Where 'type' is one of:\n");
		printf("\t%s\n", AUTHTYPE_NAME(0));
D 6
		for (ap = authenticators; ap->type; ap++)
E 6
I 6
		mask = 0;
		for (ap = authenticators; ap->type; ap++) {
			if ((mask & (i = typemask(ap->type))) != 0)
				continue;
			mask |= i;
E 6
			printf("\t%s\n", AUTHTYPE_NAME(ap->type));
I 6
		}
E 6
		return(0);
	}

	if (!getauthmask(type, &mask)) {
		printf("%s: invalid authentication type\n", type);
		return(0);
	}
D 6
	mask = getauthmask(type, &mask);
E 6
	if (on)
		i_wont_support &= ~mask;
	else
		i_wont_support |= mask;
	return(1);
}

	int
D 2
auth_togdebug()
E 2
I 2
auth_togdebug(on)
	int on;
E 2
{
D 2
	auth_debug_mode ^= 1;
E 2
I 2
	if (on < 0)
		auth_debug_mode ^= 1;
	else
		auth_debug_mode = on;
E 2
	printf("auth debugging %s\n", auth_debug_mode ? "enabled" : "disabled");
	return(1);
}

	int
auth_status()
{
	Authenticator *ap;
I 6
	int i, mask;
E 6

	if (i_wont_support == -1)
		printf("Authentication disabled\n");
	else
		printf("Authentication enabled\n");

D 6
	for (ap = authenticators; ap->type; ap++)
E 6
I 6
	mask = 0;
	for (ap = authenticators; ap->type; ap++) {
		if ((mask & (i = typemask(ap->type))) != 0)
			continue;
		mask |= i;
E 6
		printf("%s: %s\n", AUTHTYPE_NAME(ap->type),
			(i_wont_support & typemask(ap->type)) ?
					"disabled" : "enabled");
I 6
	}
E 6
	return(1);
}

/*
 * This routine is called by the server to start authentication
 * negotiation.
 */
	void
auth_request()
{
	static unsigned char str_request[64] = { IAC, SB,
						 TELOPT_AUTHENTICATION,
						 TELQUAL_SEND, };
	Authenticator *ap = authenticators;
	unsigned char *e = str_request + 4;

	if (!authenticating) {
		authenticating = 1;
		while (ap->type) {
			if (i_support & ~i_wont_support & typemask(ap->type)) {
				if (auth_debug_mode) {
D 2
					printf(">>>%s: Sending type %d\r\n",
						Name, ap->type);
E 2
I 2
					printf(">>>%s: Sending type %d %d\r\n",
						Name, ap->type, ap->way);
E 2
				}
				*e++ = ap->type;
				*e++ = ap->way;
			}
			++ap;
		}
		*e++ = IAC;
		*e++ = SE;
		net_write(str_request, e - str_request);
		printsub('>', &str_request[2], e - str_request - 2);
	}
}

/*
 * This is called when an AUTH SEND is received.
 * It should never arrive on the server side (as only the server can
 * send an AUTH SEND).
 * You should probably respond to it if you can...
 *
 * If you want to respond to the types out of order (i.e. even
 * if he sends  LOGIN KERBEROS and you support both, you respond
 * with KERBEROS instead of LOGIN (which is against what the
 * protocol says)) you will have to hack this code...
 */
	void
auth_send(data, cnt)
	unsigned char *data;
	int cnt;
{
	Authenticator *ap;
	static unsigned char str_none[] = { IAC, SB, TELOPT_AUTHENTICATION,
					    TELQUAL_IS, AUTHTYPE_NULL, 0,
					    IAC, SE };
	if (Server) {
		if (auth_debug_mode) {
			printf(">>>%s: auth_send called!\r\n", Name);
		}
		return;
	}

	if (auth_debug_mode) {
		printf(">>>%s: auth_send got:", Name);
		printd(data, cnt); printf("\r\n");
	}

	/*
	 * Save the data, if it is new, so that we can continue looking
	 * at it if the authorization we try doesn't work
	 */
	if (data < _auth_send_data ||
	    data > _auth_send_data + sizeof(_auth_send_data)) {
		auth_send_cnt = cnt > sizeof(_auth_send_data)
					? sizeof(_auth_send_data)
					: cnt;
D 7
		bcopy((void *)data, (void *)_auth_send_data, auth_send_cnt);
E 7
I 7
		memmove((void *)_auth_send_data, (void *)data, auth_send_cnt);
E 7
		auth_send_data = _auth_send_data;
	} else {
		/*
		 * This is probably a no-op, but we just make sure
		 */
		auth_send_data = data;
		auth_send_cnt = cnt;
	}
	while ((auth_send_cnt -= 2) >= 0) {
		if (auth_debug_mode)
			printf(">>>%s: He supports %d\r\n",
				Name, *auth_send_data);
		if ((i_support & ~i_wont_support) & typemask(*auth_send_data)) {
			ap = findauthenticator(auth_send_data[0],
					       auth_send_data[1]);
D 3
			if (!ap) {
				printf("Internal state error: cannot find authentication type %d a second time\r\n", *auth_send_data);
			} else if (ap->send) {
E 3
I 3
			if (ap && ap->send) {
E 3
				if (auth_debug_mode)
D 2
					printf(">>>%s: Trying %d\r\n",
						Name, *auth_send_data);
E 2
I 2
					printf(">>>%s: Trying %d %d\r\n",
						Name, auth_send_data[0],
							auth_send_data[1]);
E 2
				if ((*ap->send)(ap)) {
					/*
					 * Okay, we found one we like
					 * and did it.
					 * we can go home now.
					 */
					if (auth_debug_mode)
						printf(">>>%s: Using type %d\r\n",
							Name, *auth_send_data);
					auth_send_data += 2;
					return;
				}
			}
			/* else
			 *	just continue on and look for the
			 *	next one if we didn't do anything.
			 */
		}
		auth_send_data += 2;
	}
	net_write(str_none, sizeof(str_none));
	printsub('>', &str_none[2], sizeof(str_none) - 2);
	if (auth_debug_mode)
		printf(">>>%s: Sent failure message\r\n", Name);
	auth_finished(0, AUTH_REJECT);
I 3
#ifdef KANNAN
	/*
	 *  We requested strong authentication, however no mechanisms worked.
	 *  Therefore, exit on client end.
	 */
D 7
	printf("Unable to securely authenticate user ... exit\n"); 
E 7
I 7
	printf("Unable to securely authenticate user ... exit\n");
E 7
	exit(0);
#endif /* KANNAN */
E 3
}

	void
auth_send_retry()
{
	/*
	 * if auth_send_cnt <= 0 then auth_send will end up rejecting
	 * the authentication and informing the other side of this.
	 */
	auth_send(auth_send_data, auth_send_cnt);
}

	void
auth_is(data, cnt)
	unsigned char *data;
	int cnt;
{
	Authenticator *ap;

	if (cnt < 2)
		return;

	if (data[0] == AUTHTYPE_NULL) {
		auth_finished(0, AUTH_REJECT);
		return;
	}

	if (ap = findauthenticator(data[0], data[1])) {
		if (ap->is)
			(*ap->is)(ap, data+2, cnt-2);
	} else if (auth_debug_mode)
		printf(">>>%s: Invalid authentication in IS: %d\r\n",
			Name, *data);
}

	void
auth_reply(data, cnt)
	unsigned char *data;
	int cnt;
{
	Authenticator *ap;

	if (cnt < 2)
		return;

	if (ap = findauthenticator(data[0], data[1])) {
		if (ap->reply)
			(*ap->reply)(ap, data+2, cnt-2);
	} else if (auth_debug_mode)
		printf(">>>%s: Invalid authentication in SEND: %d\r\n",
			Name, *data);
I 2
}

	void
auth_name(data, cnt)
	unsigned char *data;
	int cnt;
{
	Authenticator *ap;
	unsigned char savename[256];

	if (cnt < 1) {
		if (auth_debug_mode)
			printf(">>>%s: Empty name in NAME\r\n", Name);
		return;
	}
	if (cnt > sizeof(savename) - 1) {
		if (auth_debug_mode)
			printf(">>>%s: Name in NAME (%d) exceeds %d length\r\n",
					Name, cnt, sizeof(savename)-1);
		return;
	}
D 7
	bcopy((void *)data, (void *)savename, cnt);
E 7
I 7
	memmove((void *)savename, (void *)data, cnt);
E 7
	savename[cnt] = '\0';	/* Null terminate */
	if (auth_debug_mode)
		printf(">>>%s: Got NAME [%s]\r\n", Name, savename);
	auth_encrypt_user(savename);
}

	int
auth_sendname(cp, len)
	unsigned char *cp;
	int len;
{
	static unsigned char str_request[256+6]
			= { IAC, SB, TELOPT_AUTHENTICATION, TELQUAL_NAME, };
	register unsigned char *e = str_request + 4;
	register unsigned char *ee = &str_request[sizeof(str_request)-2];

	while (--len >= 0) {
		if ((*e++ = *cp++) == IAC)
			*e++ = IAC;
		if (e >= ee)
			return(0);
	}
	*e++ = IAC;
	*e++ = SE;
	net_write(str_request, e - str_request);
	printsub('>', &str_request[2], e - &str_request[2]);
	return(1);
E 2
}

	void
auth_finished(ap, result)
	Authenticator *ap;
	int result;
{
	if (!(authenticated = ap))
		authenticated = &NoAuth;
	validuser = result;
}

	/* ARGSUSED */
	static void
auth_intr(sig)
	int sig;
{
	auth_finished(0, AUTH_REJECT);
}

	int
auth_wait(name)
	char *name;
{
	if (auth_debug_mode)
		printf(">>>%s: in auth_wait.\r\n", Name);

	if (Server && !authenticating)
		return(0);

	(void) signal(SIGALRM, auth_intr);
	alarm(30);
	while (!authenticated)
		if (telnet_spin())
			break;
	alarm(0);
	(void) signal(SIGALRM, SIG_DFL);

	/*
	 * Now check to see if the user is valid or not
	 */
	if (!authenticated || authenticated == &NoAuth)
		return(AUTH_REJECT);

	if (validuser == AUTH_VALID)
		validuser = AUTH_USER;

	if (authenticated->status)
		validuser = (*authenticated->status)(authenticated,
						     name, validuser);
	return(validuser);
}

	void
auth_debug(mode)
	int mode;
{
	auth_debug_mode = mode;
}

	void
auth_printsub(data, cnt, buf, buflen)
	unsigned char *data, *buf;
	int cnt, buflen;
{
	Authenticator *ap;

	if ((ap = findauthenticator(data[1], data[2])) && ap->printsub)
		(*ap->printsub)(data, cnt, buf, buflen);
	else
		auth_gen_printsub(data, cnt, buf, buflen);
}

	void
auth_gen_printsub(data, cnt, buf, buflen)
	unsigned char *data, *buf;
	int cnt, buflen;
{
	register unsigned char *cp;
	unsigned char tbuf[16];

	cnt -= 3;
	data += 3;
	buf[buflen-1] = '\0';
	buf[buflen-2] = '*';
	buflen -= 2;
	for (; cnt > 0; cnt--, data++) {
		sprintf((char *)tbuf, " %d", *data);
		for (cp = tbuf; *cp && buflen > 0; --buflen)
			*buf++ = *cp++;
		if (buflen <= 0)
			return;
	}
	*buf = '\0';
}
#endif
E 1
