h35705
s 00001/00001/00032
d D 8.2 93/12/15 11:30:37 dab 11 10
c Add a #ifdef for HAS_CGETENT.
c Changes for Solaris support.
e
s 00000/00000/00033
d D 8.1 93/06/04 17:34:48 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00002/00032
d D 5.8 93/05/27 12:50:14 dab 9 8
c Change libtelnet so that instead of picking up
c the gettytab.c module from getty, it now uses its own
c version of getent() and getstr(), that use the newer
c library routines cgetent() and cgetstr().
e
s 00022/00000/00012
d D 5.7 93/05/21 10:17:27 dab 8 6
c Add "nocrypt" target to create a subdirectory
c with source with encryption removed.
e
s 00022/00000/00012
d R 5.7 93/05/21 09:47:18 dab 7 6
c Add "nocrypt" target to create a subdirectory
c with source with encryption removed.
e
s 00001/00001/00011
d D 5.6 93/01/05 14:00:02 dab 6 5
c Change -DDES_ENCRYPT to -DDES_ENCRYPTION
e
s 00001/00001/00011
d D 5.5 92/12/18 14:11:11 dab 5 4
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Latest version of Kerberos V stuff
c Bug fixes
e
s 00000/00007/00012
d D 5.4 91/05/07 11:13:59 bostic 4 3
c Makefile's don't get copyrights
e
s 00003/00003/00016
d D 5.3 91/03/22 13:17:46 dab 3 2
c Upgrade to the latest & greatest authentication/encryption
e
s 00006/00003/00013
d D 5.2 91/03/01 02:30:22 dab 2 1
c 
e
s 00016/00000/00000
d D 5.1 91/02/28 22:01:26 dab 1 0
c date and time created 91/02/28 22:01:26 by dab
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1991 The Regents of the University of California.
# All rights reserved.
#
# %sccs.include.redist.sh
#
E 4
#	%W% (Berkeley) %G%
D 4
#
E 4

LIB=	telnet
D 2
SRCS=	pow.c gcd.c msqrt.c mdiv.c mout.c mult.c madd.c util.c
SRCS=	auth.c encrypt.c genget.c getent.c kerberos.c \
	kerberos5.c krb_des.c misc.c simple_auth.c
E 2
I 2
D 9
SRCS=	auth.c encrypt.c genget.c getent.c gettytab.c misc.c
E 9
I 9
SRCS=	auth.c encrypt.c genget.c getent.c misc.c
E 9
D 3
SRCS+=	kerberos.c krb_des.c
#SRCS+=	kerberos5.c simple_auth.c
E 3
I 3
SRCS+=	kerberos.c enc_des.c
#SRCS+=	kerberos5.c
E 3
E 2
D 5
CFLAGS+= -DENCRYPT -DAUTHENTICATE
E 5
I 5
D 11
CFLAGS+= -DENCRYPTION -DAUTHENTICATION
E 11
I 11
CFLAGS+= -DENCRYPTION -DAUTHENTICATION -DHAS_CGETENT
E 11
E 5
I 2
D 3
CFLAGS+= -DKRB4 -DKRBDES_ENCRYPT -I/usr/include/kerberosIV
E 3
I 3
D 6
CFLAGS+= -DKRB4 -DDES_ENCRYPT -I/usr/include/kerberosIV
E 6
I 6
CFLAGS+= -DKRB4 -DDES_ENCRYPTION -I/usr/include/kerberosIV
E 6
E 3
E 2

I 8
# These are the sources that have encryption stuff in them.
CRYPT_SRC= auth.c enc-proto.h enc_des.c encrypt.c
CRYPT_SRC+= encrypt.h kerberos.c kerberos5.c krb4encpwd.c
CRYPT_SRC+= misc.c spx.c Makefile
NOCRYPT_DIR=${.CURDIR}/Nocrypt

E 8
I 2
D 9
.PATH:  ${.CURDIR}/../../libexec/getty
E 9
E 2
.include <bsd.lib.mk>
I 2

I 8
nocrypt:
#ifdef	ENCRYPTION
	@for i in ${CRYPT_SRC}; do \
	    if [ ! -d ${NOCRYPT_DIR} ]; then \
		echo Creating subdirectory ${NOCRYPT_DIR}; \
		mkdir ${NOCRYPT_DIR}; \
	    fi; \
	    echo ${NOCRYPT_DIR}/$$i; \
	    unifdef -UENCRYPTION ${.CURDIR}/$$i | \
		sed "s/ || defined(ENCRYPTION)//" > ${NOCRYPT_DIR}/$$i; \
	done

placeholder:
#else	/* ENCRYPTION */
	@echo "Encryption code already removed."
#endif	/* ENCRYPTION */
E 8
E 2
E 1
