h60554
s 00406/00000/00000
d D 5.1 91/02/28 22:01:33 dab 1 0
c date and time created 91/02/28 22:01:33 by dab
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
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

#if	defined(AUTHENTICATE) && defined(ENCRYPT) && defined(SIMPLE_AUTH)
#if	defined(CRAY) || BSD > 43
#include <unistd.h>
#endif
#include <arpa/telnet.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/file.h>
#ifdef	__STDC__
#include <stdlib.h>
#endif

#include "encrypt.h"
#include "auth.h"
#include "key-proto.h"
#include "misc-proto.h"

/*
 * These are the negotiation options
 */
#define	N_USER		0	/* cnt data ... */
#define	N_CHALLANGE	1	/* 4 byte challange */
#define	N_VERIFY	2	/* 4 byte challange 4 byte session key */
#define	N_ACCEPT	3	/* no data needed */
#define	N_REJECT	4	/* no data needed */
#define	N_REQUEST	5	/* no data needed */
#define	N_CNT		6

#define	CPTR(x)		(((char *)&x) + sizeof(long) - 4)


static unsigned char str_reject[] = { IAC, SB, TELOPT_AUTHENTICATION, 0,
				     0, 0, N_REJECT, IAC, SE };
static unsigned char str_request[] = { IAC, SB, TELOPT_AUTHENTICATION, 0,
				      0, 0, N_REQUEST, IAC, SE };
static unsigned char str_accept[] = { IAC, SB, TELOPT_AUTHENTICATION, 0,
				     0, 0, N_ACCEPT, IAC, SE };

static unsigned char str_data[64] = { IAC, SB, TELOPT_AUTHENTICATION };

#define	Reject(ap)	(auth_finished(ap, AUTH_REJECT), \
			 (str_reject[3] == TELQUAL_REPLY ? 1 :\
			  printsub('>', &str_reject[2], sizeof(str_reject)-2)),\
			 net_write(str_reject, sizeof(str_reject)))
#define	Request()	((str_request[3] == TELQUAL_REPLY ? 1 :\
			printsub('>', &str_request[2], sizeof(str_request)-2)),\
			net_write(str_request, sizeof(str_request)))
#define	Accept()	((str_accept[3] == TELQUAL_REPLY ? 1 :\
			  printsub('>', &str_accept[2], sizeof(str_accept)-2)),\
			net_write(str_accept, sizeof(str_accept)))


	static void
Data(type, d, c)
	int type;
	void *d;
	int c;
{
	unsigned char *p = str_data + 6;
	unsigned char *cd = (unsigned char *)d;

	if (auth_debug_mode) {
		printf("%s:%d: [%d] (%d)",
			str_data[3] == TELQUAL_IS ? ">>>IS" : ">>>REPLY",
			str_data[3],
			type, c);
		printd(d, c);
		printf("\r\n");
	}
	*p++ = type;
	while (c-- > 0) {
		if ((*p++ = *cd++) == IAC)
			*p++ = IAC;
	}
	*p++ = IAC;
	*p++ = SE;
	if (str_data[3] == TELQUAL_IS)
		printsub('>', &str_data[2], p - &str_data[2]);
	net_write(str_data, p - str_data);
}

static Block		user_key;
static Block		session_key;
static Block		challange;
static Schedule		user_sched;

static unsigned char	user_name[64];
static Session_Key SKey = { SK_DES, 8, session_key };

	int
simple_auth_init(ap, server)
	Authenticator *ap;
	int server;
{
	bzero((void *)session_key, sizeof(Block));
	bzero((void *)user_key, sizeof(Block));
	bzero((void *)challange, sizeof(Block));
	bzero((void *)user_name, sizeof(user_name));

	str_data[3] =
	str_reject[3] =
	str_request[3] =
	str_accept[3] = server ? TELQUAL_REPLY : TELQUAL_IS;

	str_data[4] =
	str_reject[4] =
	str_request[4] =
	str_accept[4] = ap->type;

	str_data[5] =
	str_reject[5] =
	str_request[5] =
	str_accept[5] = ap->way;

	if (server)
		return(key_file_exists());
	return(1);
}

	int
simple_auth_send(ap)
	Authenticator *ap;
{
	char *n;
	char user_name[64];
	char passwd[32];

	if (n = telnet_getenv("USER"))  {
		strncpy((char *)user_name, n, sizeof(user_name));
		user_name[sizeof(user_name)-1] = 0;
		if (!user_name[0]) {
			return(0);
		}
	} else if (!telnet_gets("Telnet Encryption Name: ",
			        user_name, sizeof(user_name), 1)) {
		return(0);
	}
	if (!telnet_gets("Telnet Encryption Password: ",
			 passwd, sizeof(passwd), 0)) {
		bzero((void *)user_name, sizeof(user_name));
		return(0);
	}
	des_string_to_key(passwd, user_key);
	bzero((void *)passwd, sizeof(passwd));
	des_key_sched(user_key, user_sched);
	des_set_random_generator_seed(user_key);
	Data(N_USER, (void *)user_name, strlen((char *)user_name));
	return(1);
}

	void
simple_auth_is_reply(ap, data, cnt)
	Authenticator *ap;
	unsigned char *data;
	int cnt;
{
	Block		challange2, b;
	unsigned char	buf[64];

	if (auth_debug_mode) {
		printf("%s:%d: [%d] (%d)",
			data[-1] == TELQUAL_IS ? "IS" : "REPLY",
			data[-1],
			*data, cnt - 1);
		printd(data+1, cnt-1);
		printf("\r\n");
	}
	if (cnt-- < 0)
		return;

	switch(*data++) {
	case N_REJECT:
	reject:
		bzero((void *)user_name, sizeof(user_name));
		bzero((void *)user_key, sizeof(Block));
		bzero((void *)user_sched, sizeof(Schedule));
		bzero((void *)session_key, sizeof(Block));
		auth_send_retry();
		return;
	case N_USER:
		if (cnt < 1) {
			if (auth_debug_mode)
				printf("Rejected because no name\r\n");
			Reject(ap);
			goto reject;
		}
		if (cnt >= sizeof(user_name)) {
			if (auth_debug_mode)
				printf("Rejected because long name\r\n");
			bzero((void *)data, cnt);
			Reject(ap);
			goto reject;
		}

		bcopy((void *)data, (void *)user_name, cnt);
		user_name[cnt] = 0;
		key_lookup(user_name, user_key);
		bzero((void *)user_name, sizeof(user_name));
		if (!VALIDKEY(user_key)) {
			if (auth_debug_mode)
				printf("Rejected because invalid name\r\n");
			Reject(ap);
			goto reject;
		}
		des_key_sched(user_key, user_sched);
		des_set_random_generator_seed(user_key);
		des_new_random_key(challange);
		Data(N_CHALLANGE, (void *)challange, sizeof(Block));
		return;
	case N_CHALLANGE:
		if (cnt != sizeof(Block)) {
			if (auth_debug_mode)
				printf("Rejected because invalid challange size\r\n");
			Reject(ap);
			goto reject;
		}
		if (!VALIDKEY(user_key)) {
			if (auth_debug_mode)
				printf("Rejected because invalid key\r\n");
			Reject(ap);
			goto reject;
		}

		bcopy((void *)data, (void *)b, sizeof(Block));
		des_ecb_encrypt(b, challange, user_sched, 0);

		challange[4] ^= 0x42;

		des_new_random_key(session_key);

		des_ecb_encrypt(challange,
			        (BlockT)(buf),
				user_sched, 1);

		des_ecb_encrypt(session_key,
			        (BlockT)(buf + sizeof(Block)),
				user_sched, 1);

		Data(N_VERIFY, (void *)buf, sizeof(Block) * 2);
		return;
	case N_VERIFY:
		if (cnt != sizeof(Block) * 2) {
			if (auth_debug_mode)
				printf("Rejected because invalid verify size\r\n");
			Reject(ap);
			goto reject;
		}
		bcopy((void *)data, (void *)b, sizeof(Block));
		des_ecb_encrypt(b, challange2, user_sched, 0);

		des_ecb_encrypt(challange, b, user_sched, 0);
		bcopy((void *)b, (void *)challange, sizeof(Block));

		challange[4] ^= 0x42;

		if (!SAMEKEY(challange, challange2)) {
			if (auth_debug_mode)
				printf("Rejected because challange failed\r\n");
			Reject(ap);
			goto reject;
		}

		bcopy((void *)(data + sizeof(Block)), b, sizeof(Block));
		des_ecb_encrypt(b, session_key, user_sched, 0);

		bzero((void *)user_key, sizeof(Block));
		bzero((void *)user_sched, sizeof(Schedule));
		encrypt_session_key(&SKey, 1);
		auth_finished(ap, AUTH_OTHER);
		Accept();
		break;
	case N_ACCEPT:
		encrypt_session_key(&SKey, 0);
		break;
	}
}


#define	BUMP(buf, len)		while (*(buf)) {++(buf), --(len);}
#define	ADDC(buf, len, c)	if ((len) > 0) {*(buf)++ = (c); --(len);}

	void
simple_auth_printsub(data, cnt, buf, buflen)
	unsigned char *data, *buf;
	int cnt, buflen;
{
	char lbuf[32];
	register int i;

	buf[buflen-1] = '\0';		/* make sure its NULL terminated */
	buflen -= 1;

	switch(data[3]) {

	case N_USER:				/* cnt data ... */
		strncpy(buf, " USER ", buflen);
		BUMP(buf, buflen);
		if (cnt <= 4)
			break;
		ADDC(buf, buflen, '"');
		for (i = 4; i < cnt; i++)
			ADDC(buf, buflen, data[i]);
		ADDC(buf, buflen, '"');
		ADDC(buf, buflen, '\0');
		break;

	case N_CHALLANGE:			/* 4 byte challange */
		strncpy(buf, " CHALLANGE", buflen);
		goto common2;

	case N_VERIFY:		/* 4 byte challange 4 byte session key */
		strncpy(buf, " VERIFY", buflen);
		goto common2;

	case N_ACCEPT:				/* no data needed */
		strncpy(buf, " ACCEPT", buflen);
		goto common2;

	case N_REJECT:				/* no data needed */
		strncpy(buf, " REJECT", buflen);
		goto common2;

	case N_REQUEST:				/* no data needed */
		strncpy(buf, " REQUEST", buflen);
		goto common2;

	default:
		sprintf(lbuf, " %d (unknown)", data[3]);
		strncpy(buf, lbuf, buflen);
	common2:
		BUMP(buf, buflen);
		for (i = 4; i < cnt; i++) {
			sprintf(lbuf, " %d", data[i]);
			strncpy(buf, lbuf, buflen);
			BUMP(buf, buflen);
		}
		break;
	}
}

static char *keyfile = "/etc/telnet.keys";

	int
key_file_exists()
{
	return(access(keyfile, R_OK) == 0);
}

	void
key_lookup(name, key)
	unsigned char *name;
	Block key;
{
	FILE *fp = fopen(keyfile, "r");
	unsigned char buf[512];
	int i = strlen((char *)name);

	bzero((void *)key, sizeof(key));

	if (!fp)
		return;

	while (fgets((char *)buf, sizeof(buf), fp)) {
		if (!strncmp((char *)buf, (char *)name, i) && buf[i] == '\t') {
			unsigned char *p = buf + i + 1;
			while (*p && *p != '\n')
				++p;
			*p = 0;
			des_string_to_key((char *)buf+i+1, key);
			break;
		}
	}
	fclose(fp);
}
#endif
E 1
