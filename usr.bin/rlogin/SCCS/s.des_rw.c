h44960
s 00002/00002/00175
d D 8.1 93/06/06 16:09:28 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00005/00162
d D 5.9 93/03/04 18:31:46 bostic 10 9
c Craig Leres prototyping fixes, plus some of mine
e
s 00004/00000/00163
d D 5.8 91/02/25 17:23:54 bostic 9 7
c ANSI Fixes
e
s 00000/00152/00011
d D 5.7.1.1 90/10/21 18:14:43 mckusick 8 7
c delete data-stream encryption for the foreign sites (4.3-Reno)
e
s 00004/00002/00159
d D 5.7 90/10/21 18:13:25 mckusick 7 6
c use ifdef's that unifdef can understand
e
s 00002/00000/00159
d D 5.6 90/09/27 21:46:14 mckusick 6 5
c break out -x functionality into #ifdef CRYPT
e
s 00002/00003/00157
d D 5.5 90/06/01 17:40:51 bostic 5 4
c put reasonable SCCS headers on
e
s 00001/00011/00159
d D 5.4 90/06/01 17:32:41 bostic 4 3
c new copyright notice
e
s 00001/00007/00169
d D 5.3 90/05/11 22:57:23 kfall 3 2
c include kerberosIV/des.h before kerberosIV/krb.h
e
s 00002/00003/00174
d D 5.2 90/04/03 12:06:14 bostic 2 1
c include files moved to kerberosIV, not /usr/include
e
s 00177/00000/00000
d D 5.1 89/08/20 14:20:28 kfall 1 0
c date and time created 89/08/20 14:20:28 by kfall
e
u
U
f b 
t
T
I 1
D 5
/*
E 5
I 5
/*-
E 5
D 11
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
D 4
 * Redistribution and use in source and binary forms are permitted
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 */

D 5

E 5
D 3
/*
 *	$Source:$
 *	$Header:$
 */


E 3
#ifndef lint
D 5
static char sccsid[] = "@(#)des_rw.c	1.7 (Berkeley) 2/6/89";
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
#endif /* not lint */

I 6
D 7
#if defined(KERBEROS) && defined(CRYPT)
E 7
I 7
D 8
#ifdef CRYPT
#ifdef KERBEROS
E 7
E 6
D 2
#include <sys/types.h>
E 2
#include <sys/param.h>
I 10

E 10
D 2
#include <krb.h>
#include <des.h>
E 2
I 2
D 3
#include <kerberosIV/krb.h>
E 3
#include <kerberosIV/des.h>
I 3
#include <kerberosIV/krb.h>
I 9
D 10
#include <time.h>
#include <unistd.h>
E 10
I 10

E 10
#include <stdlib.h>
#include <string.h>
I 10
#include <time.h>
#include <unistd.h>
E 10
E 9
E 3
E 2

D 10
extern long		random();
E 10
static unsigned char	des_inbuf[10240], storage[10240], *store_ptr;
static bit_64		*key;
static u_char		*key_schedule;

I 10
/* XXX these should be in a kerberos include file */
int	krb_net_read __P((int, char *, int));
#ifdef notdef
/* XXX too hard to make this work */
int	des_pcbc_encrypt __P((des_cblock *, des_cblock *, long,
	    des_key_schedule, des_cblock *, int));
#endif

E 10
/*
 * NB: These routines will not function properly if NBIO
 * 	is set
 */

/*
 * des_set_key
 *
 * Set des encryption/decryption key for use by the des_read and
 * des_write routines
 *
 * The inkey parameter is actually the DES initial vector,
 * and the insched is the DES Key unwrapped for faster decryption
 */

void
des_set_key(inkey, insched)
	bit_64		*inkey;
	u_char		*insched;
{
	key = inkey;
	key_schedule = insched;
}

void
des_clear_key()
{
	bzero((char *) key, sizeof(C_Block));
	bzero((char *) key_schedule, sizeof(Key_schedule));
}
	

int
des_read(fd, buf, len)
	int fd;
	register char *buf;
	int len;
{
	int nreturned = 0;
	long net_len, rd_len;
	int nstored = 0;

	if (nstored >= len) {
		(void) bcopy(store_ptr, buf, len);
		store_ptr += len;
		nstored -= len;
		return(len);
	} else if (nstored) {
		(void) bcopy(store_ptr, buf, nstored);
		nreturned += nstored;
		buf += nstored;
		len -= nstored;
		nstored = 0;
	}
	
D 10
	if (krb_net_read(fd, &net_len, sizeof(net_len)) != sizeof(net_len)) {
E 10
I 10
	if (krb_net_read(fd, (char *)&net_len, sizeof(net_len)) !=
	    sizeof(net_len)) {
E 10
		/* XXX can't read enough, pipe
		   must have closed */
		return(0);
	}
	net_len = ntohl(net_len);
	if (net_len <= 0 || net_len > sizeof(des_inbuf)) {
		/* preposterous length; assume out-of-sync; only
		   recourse is to close connection, so return 0 */
		return(0);
	}
	/* the writer tells us how much real data we are getting, but
	   we need to read the pad bytes (8-byte boundary) */
	rd_len = roundup(net_len, 8);
D 10
	if (krb_net_read(fd, des_inbuf, rd_len) != rd_len) {
E 10
I 10
	if (krb_net_read(fd, (char *)des_inbuf, rd_len) != rd_len) {
E 10
		/* pipe must have closed, return 0 */
		return(0);
	}
	(void) des_pcbc_encrypt(des_inbuf,	/* inbuf */
			    storage,		/* outbuf */
			    net_len,		/* length */
			    key_schedule,	/* DES key */
			    key,		/* IV */
			    DECRYPT);		/* direction */

	if(net_len < 8)
		store_ptr = storage + 8 - net_len;
	else
		store_ptr = storage;

	nstored = net_len;
	if (nstored > len) {
		(void) bcopy(store_ptr, buf, len);
		nreturned += len;
		store_ptr += len;
		nstored -= len;
	} else {
		(void) bcopy(store_ptr, buf, nstored);
		nreturned += nstored;
		nstored = 0;
	}
	
	return(nreturned);
}

static	unsigned char des_outbuf[10240];	/* > longest write */

int
des_write(fd, buf, len)
	int fd;
	char *buf;
	int len;
{
	static	int	seeded = 0;
	static	char	garbage_buf[8];
	long net_len, garbage;

	if(len < 8) {
		if(!seeded) {
			seeded = 1;
			srandom((int) time((long *)0));
		}
		garbage = random();
		/* insert random garbage */
		(void) bcopy(&garbage, garbage_buf, MIN(sizeof(long),8));
		/* this "right-justifies" the data in the buffer */
		(void) bcopy(buf, garbage_buf + 8 - len, len);
	}
	/* pcbc_encrypt outputs in 8-byte (64 bit) increments */

	(void) des_pcbc_encrypt((len < 8) ? garbage_buf : buf,
			    des_outbuf,
			    (len < 8) ? 8 : len,
			    key_schedule,	/* DES key */
			    key,		/* IV */
			    ENCRYPT);

	/* tell the other end the real amount, but send an 8-byte padded
	   packet */
	net_len = htonl(len);
	(void) write(fd, &net_len, sizeof(net_len));
	(void) write(fd, des_outbuf, roundup(len,8));
	return(len);
}
I 6
D 7
#endif /* KERBEROS && CRYPT */
E 7
I 7
#endif /* KERBEROS */
#endif /* CRYPT */
E 8
E 7
E 6
E 1
