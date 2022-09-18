h21596
s 00000/00000/00042
d D 8.1 93/06/01 23:08:11 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00041
d D 5.4 93/05/25 17:32:16 bostic 4 3
c don't build profiled KERBEROS libraries
e
s 00014/00007/00027
d D 5.3 91/04/01 08:49:20 bostic 3 2
c dependencies were wrong??  (I've forgotten)
e
s 00001/00001/00033
d D 5.2 90/07/02 16:11:00 bostic 2 1
c clean p_table.h
e
s 00034/00000/00000
d D 5.1 90/06/25 11:37:01 bostic 1 0
c date and time created 90/06/25 11:37:01 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

LIB=	des
CFLAGS+=-DKERBEROS -I. -I${.CURDIR}/../include
SRCS=	cbc_encrypt.c cksum.c debug_decl.c des.c key_parity.c \
	key_sched.c new_rnd_key.c pcbc_encrypt.c quad_cksum.c \
	random_key.c read_password.c string_to_key.c util.c weak_key.c
D 2
CLEANFILES+=key_perm.h s_table.h ip.c p.c fp.c odd.h
E 2
I 2
CLEANFILES+=key_perm.h s_table.h ip.c p.c fp.c odd.h p_table.h
I 4
NOPROFILE=
E 4
E 2

TDIR=	${.CURDIR}/..
D 3
key_perm.h: ${TDIR}/make_key_perm/obj/make_key_perm
E 3
I 3
key_perm.h:
	cd ${TDIR}/make_key_perm; make
E 3
	${TDIR}/make_key_perm/obj/make_key_perm key_perm.h

D 3
p_table.h: ${TDIR}/make_p_table/obj/make_p_table
E 3
I 3
p_table.h:
	cd ${TDIR}/make_p_table; make
E 3
	${TDIR}/make_p_table/obj/make_p_table p_table.h

D 3
s_table.h: ${TDIR}/make_s_table/obj/make_s_table
E 3
I 3
s_table.h:
	cd ${TDIR}/make_s_table; make
E 3
	${TDIR}/make_s_table/obj/make_s_table s_table.h

D 3
ip.c: ${TDIR}/make_ip/obj/make_ip
E 3
I 3
ip.c:
	cd ${TDIR}/make_ip; make
E 3
	${TDIR}/make_ip/obj/make_ip ip.c

D 3
p.c: ${TDIR}/make_p/obj/make_p
E 3
I 3
p.c:
	cd ${TDIR}/make_p; make
E 3
	${TDIR}/make_p/obj/make_p p.c

D 3
fp.c: ${TDIR}/make_fp/obj/make_fp
E 3
I 3
fp.c:
	cd ${TDIR}/make_fp; make
E 3
	${TDIR}/make_fp/obj/make_fp fp.c

D 3
odd.h: ${TDIR}/make_odd/obj/make_odd
E 3
I 3
odd.h:
	cd ${TDIR}/make_odd; make
E 3
	${TDIR}/make_odd/obj/make_odd odd.h

.include <bsd.lib.mk>

${OBJS} ${POBJS} .depend: key_perm.h p_table.h s_table.h ip.c p.c fp.c odd.h
E 1
