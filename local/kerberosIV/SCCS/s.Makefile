h16697
s 00000/00000/00020
d D 8.1 93/06/01 23:06:51 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00018
d D 5.3 93/02/27 10:27:52 bostic 3 2
c need .CURDIR for install
e
s 00007/00000/00012
d D 5.2 92/07/16 10:51:56 bostic 2 1
c install include files, too
e
s 00012/00000/00000
d D 5.1 90/06/25 18:15:44 bostic 1 0
c date and time created 90/06/25 18:15:44 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

# do compile_et and make_* first, used by other directories

SUBDIR=	compile_et make_fp make_ip make_key_perm make_odd make_p make_p_table \
	make_s_table

SUBDIR+=acl des kdb krb ext_srvtab kdb_destroy kdb_edit kdb_init kdb_util \
	kdestroy kerberos kinit klist ksrvtgt kstash register registerd \
	make_keypair man

I 2
IFILES=	des.h kadm.h kadm_err.h kparse.h krb.h krb_db.h krb_err.h \
	mit-copyright.h

beforeinstall:
D 3
	cd include; install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${IFILES} \
E 3
I 3
	cd ${.CURDIR}/include; \
	    install -c -o ${BINOWN} -g ${BINGRP} -m 444 ${IFILES} \
E 3
	    ${DESTDIR}/usr/include/kerberosIV

E 2
.include <bsd.subdir.mk>
E 1
