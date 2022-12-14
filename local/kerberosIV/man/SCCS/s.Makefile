h25052
s 00000/00000/00016
d D 8.1 93/06/01 23:14:48 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00002/00011
d D 5.4 90/07/25 22:26:16 bostic 4 3
c kerberos in both section 1 an d3
e
s 00000/00007/00013
d D 5.3 90/07/01 10:49:40 bostic 3 2
c clean all the man pages
e
s 00015/00355/00005
d D 5.2 90/06/25 15:39:59 bostic 2 1
c do it the pmake way
e
s 00360/00000/00000
d D 5.1 90/06/25 15:29:49 bostic 1 0
c date and time created 90/06/25 15:29:49 by bostic
e
u
U
t
T
I 2
#	%W% (Berkeley) %G%
E 2
I 1

D 2
#
# This makefile is automatically generated by imake... do not modify
# or you may lose your changes when imake generates makefiles again.
# Ignore this message if you are not using imake.
#
#	$Source: /usr/src/kerberosIV/src/util/imake.includes/RCS/Imake.template,v $
#	$Author: steiner $
#	$Header: /usr/src/kerberosIV/src/util/imake.includes/RCS/Imake.template,v 4.3 88/12/09 15:41:52 steiner Exp Locker: kfall $
#
E 2
I 2
MAN1=	kdestroy.0 kerberos.0 kinit.0 klist.0 ksrvtgt.0
D 4
MAN3=	acl_check.0 des_crypt.0 kerberos.0 krb_realmofhost.0 krb_sendauth.0 \
E 4
I 4
MAN3=	acl_check.0 des_crypt.0 krb.0 krb_realmofhost.0 krb_sendauth.0 \
E 4
	krb_set_tkt_string.0 kuserok.0 tf_util.0
MAN5=	krb.conf.0 krb.realms.0
MAN8=	ext_srvtab.0 kdb_destroy.0 kdb_edit.0 kdb_init.0 kdb_util.0 kstash.0
MLINKS+=krb_realmofhost.3 realm.3
MLINKS+=des_crypt.3 des.3
D 4
MLINKS+=kerberos.3
E 4
I 4
MLINKS+=krb.3 kerberos.3 krb.3 krb_mk_req.3 krb.3 krb_rd_req.3
MLINKS+=krb.3 krb_kntoln.3 krb.3 krb_set_key.3 krb.3 krb_get_cred.3
MLINKS+=krb.3 krb_mk_priv.3 krb.3 krb_mk_safe.3 krb.3 krb_rd_safe.3
MLINKS+=krb.3 krb_mk_err.3 krb.3 krb_rd_err.3 krb.3 krb_ck_repl.3
E 4
MLINKS+=krb_sendauth.3 ksend.3
E 2

D 2
NEWTOP=../.
BUILDTOP=../.
E 2
I 2
D 3
all: ${MAN1} ${MAN3} ${MAN5} ${MAN8}
E 2

D 2
DEPEND=$(BUILDTOP)/util/makedepend/makedepend
E 2
I 2
clean depend lint tags:
E 2

D 2
IMAKE=$(BUILDTOP)/util/imake/imake -I$(BUILDTOP)/util/imake.includes
E 2
I 2
cleandir:
	rm -f ${MAN3}
E 2

E 3
D 2
INCLUDE= -I$(BUILDTOP)/include
CFLAGS=$(DBG) $(INCLUDE) $(DEFINES) $(GLOBAL_CDEFS)
LINTFLAGS=$(INCLUDE) $(DEFINES) $(GLOBAL_CDEFS)

#	$Source: /usr/src/kerberosIV/src/util/imake.includes/RCS/config.Imakefile,v $
#	$Author: kfall $
#	$Header: /usr/src/kerberosIV/src/util/imake.includes/RCS/config.Imakefile,v 4.24 90/03/26 15:18:42 kfall Exp Locker: kfall $
#

GLOBAL_CDEFS= -DBSD42 -DKERBEROS -DVFS \
	$(NOENCFLAG) $(DBMFLAG) $(SHMFLAG)

SRCTOP=/usr/src/kerberosIV/src

DESTDIR=/

USRDIR= /usr
SVRDIR= /usr/sbin
DAEMDIR= /usr/libexec
PROGDIR=/usr/bin
LIBDIR= /usr/lib
USRLIB= /usr/lib
LINTLIBDIR = /usr/libdata/lint
BINDIR= /usr/bin
UCBDIR= /dev/null
INCLDIR= /usr/include/kerberosIV
MANDIR= /usr/share/man
ETCDIR= /etc/kerberosIV
SLASHBINDIR= /bin

LINTLIBFLAG=-C

KRB_LIB=$(BUILDTOP)/lib/krb/libkrb.a
KRB_LIBDEP=$(KRB_LIB)
KRB_LINTLIB=$(BUILDTOP)/lib/krb/llib-lkrb.ln
KADM_LIB=$(BUILDTOP)/lib/kadm/libkadm.a
KADM_LIBDEP=$(KADM_LIB)
ACL_LIB=$(BUILDTOP)/lib/acl/libacl.a
ACL_LIBDEP=$(ACL_LIB)

NOENCFLAG=
DES_LIB=$(BUILDTOP)/lib/des/libdes.a
DES_LIBDEP=$(DES_LIB)
DES_LINTLIB=$(BUILDTOP)/lib/des/llib-ldes.ln

DBMFLAG=-DNDBM
KDB_LIB=$(BUILDTOP)/lib/kdb/libkdb.a
KDB_LIBDEP=$(KDB_LIB)

SHMFLAG=

COMPILE_ET= $(BUILDTOP)/util/et/compile_et

COM_ERR = $(BUILDTOP)/util/et/libcom_err.a

COM_ERR_DEP = $(COM_ERR)

MAKE_COMMANDS= $(BUILDTOP)/util/ss/make_commands

SS_LIB = $(BUILDTOP)/util/ss/libss.a

SS_LIBDEP = $(SS_LIB)

ARCHIVE= ar cru

RANLIB= ranlib

INSTALLFILE= install -c -m 444

INSTALLLIB= install -c -m 444

INSTALLPROG= install -c -m 555

INSTALLRAW= install

INSTALLSUID= install -c -m 4555 -o root

LD=ld

AS=as

LINT=lint

CC=cc

CCRO=cc -R

HCC=$(CC)

CPP=$(CC) -E

DBG=-O

HCFLAGS=$(CFLAGS)

TAGGER=etags

MAKE=make
RM=rm -f
MV=mv
CP=cp
LN=ln -s
LPR=lpr -p
CHMOD=chmod

DEF_UID = 258

#	$Source: /usr/src/kerberosIV/src/util/imake.includes/RCS/Imake.rules,v $
#	$Author: qjb $
#	$Header: /usr/src/kerberosIV/src/util/imake.includes/RCS/Imake.rules,v 4.15 89/09/26 14:34:51 qjb Exp Locker: kfall $
#

# $Source: /usr/src/kerberosIV/src/man/RCS/Imakefile,v $
# $Author: jtkohl $
# $Header: /usr/src/kerberosIV/src/man/RCS/Imakefile,v 4.3 89/07/27 18:38:04 jtkohl Exp Locker: kfall $
#
# Copyright 1987, 1988 by the Massachusetts Institute of Technology.
#
# For copying and distribution information,
# please see the file <mit-copyright.h>.
#
# Imakefile for manual pages.
#

SRCDIR=${SRCTOP}/man
#CODE=kerberos.1 klist.1 kdestroy.1 kinit.1 ksrvtgt.1 kpasswd.1 \
#	kerberos.3 krb_sendauth.3 \
#	des_crypt.3 kadmin.8 kadmind.8 ksrvutil.8 \
#	kerberos.point des.point ksend.point \
#	realm.point krb_realmofhost.3 krb_set_tkt_string.3 Imakefile \
#	krb.conf.5 krb.realms.5 \
#	rlogin.1 rsh.1 rcp.1 ksu.1 klogind.8 kshd.8 \
#	tftpd.8 tcom.8 tftp.1

CODE=kerberos.1 klist.1 kdestroy.1 kinit.1 ksrvtgt.1 kpasswd.1 \
	kerberos.3 krb_sendauth.3 \
	des_crypt.3 kadmin.8 kadmind.8 ksrvutil.8 \
	kerberos.point des.point ksend.point \
	realm.point krb_realmofhost.3 krb_set_tkt_string.3 Imakefile \
	krb.conf.5 krb.realms.5 kuserok.3 acl_check.3 tf_util.3

# NoManpage(1,kerberos.0)

all::
install:: klist.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename klist.0` ${DESTDIR}${MANDIR}/cat1/`basename klist.0`

all::
install:: kdestroy.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kdestroy.0` ${DESTDIR}${MANDIR}/cat1/`basename kdestroy.0`

all::
install:: kinit.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kinit.0` ${DESTDIR}${MANDIR}/cat1/`basename kinit.0`

all::
install:: ksrvtgt.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename ksrvtgt.0` ${DESTDIR}${MANDIR}/cat1/`basename ksrvtgt.0`

# NoManpage(1,kpasswd.0)

all::
install:: kerberos.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kerberos.0` ${DESTDIR}${MANDIR}/cat3/`basename kerberos.0`

all::
install:: des_crypt.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename des_crypt.0` ${DESTDIR}${MANDIR}/cat3/`basename des_crypt.0`

all::
install:: krb_sendauth.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename krb_sendauth.0` ${DESTDIR}${MANDIR}/cat3/`basename krb_sendauth.0`

all::
install:: krb_realmofhost.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename krb_realmofhost.0` ${DESTDIR}${MANDIR}/cat3/`basename krb_realmofhost.0`

all::
install:: krb_set_tkt_string.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename krb_set_tkt_string.0` ${DESTDIR}${MANDIR}/cat3/`basename krb_set_tkt_string.0`

all::
install:: kuserok.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kuserok.0` ${DESTDIR}${MANDIR}/cat3/`basename kuserok.0`

all::
install:: acl_check.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename acl_check.0` ${DESTDIR}${MANDIR}/cat3/`basename acl_check.0`

all::
install:: tf_util.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename tf_util.0` ${DESTDIR}${MANDIR}/cat3/`basename tf_util.0`

all::
install:: ext_srvtab.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename ext_srvtab.0` ${DESTDIR}${MANDIR}/cat8/`basename ext_srvtab.0`

all::
install:: kadmin.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kadmin.0` ${DESTDIR}${MANDIR}/cat8/`basename kadmin.0`

all::
install:: kadmind.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kadmind.0` ${DESTDIR}${MANDIR}/cat8/`basename kadmind.0`

all::
install:: ksrvutil.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename ksrvutil.0` ${DESTDIR}${MANDIR}/cat8/`basename ksrvutil.0`

all::
install:: kdb_destroy.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kdb_destroy.0` ${DESTDIR}${MANDIR}/cat8/`basename kdb_destroy.0`

all::
install:: kdb_edit.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kdb_edit.0` ${DESTDIR}${MANDIR}/cat8/`basename kdb_edit.0`

all::
install:: kdb_init.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kdb_init.0` ${DESTDIR}${MANDIR}/cat8/`basename kdb_init.0`

all::
install:: kdb_util.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kdb_util.0` ${DESTDIR}${MANDIR}/cat8/`basename kdb_util.0`

all::
install:: kstash.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename kstash.0` ${DESTDIR}${MANDIR}/cat8/`basename kstash.0`

all::
install:: krb.conf.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename krb.conf.0` ${DESTDIR}${MANDIR}/cat5/`basename krb.conf.0`

all::
install:: krb.realms.0
	$(INSTALLRAW) -m 444 -o bin -g bin `basename krb.realms.0` ${DESTDIR}${MANDIR}/cat5/`basename krb.realms.0`

# NoManpage(8,tftpd.8)
# NoManpage(8,tcom.8)
# NoManpage(1,tftp.1)

# Berkeley-derived man pages
# NoManpage(1,rlogin.1)
# NoManpage(1,rsh.1)
# NoManpage(1,rcp.1)
# NoManpage(1,ksu.1)
# NoManpage(8,klogind.8)
# NoManpage(8,kshd.8)

# Set up "pointers" to the section 3 manpages.

install:: kerberos.1x
kerberos.1x::
	nroff -man -h kerberos.1 > kerberos.1x
	${INSTALLRAW} -m 444 -o bin -g bin kerberos.1x ${MANDIR}/cat1/kerberos.0

DES	= des_read_password \
	string_to_key \
	random_key \
	des_set_key \
	ecb_encrypt \
	cbc_encrypt \
	pcbc_encrypt \
	cbc_cksum \
	quad_cksum

install:: des.point
	for i in ${DES} ; do \
		${INSTALLFILE} -c -o bin -g bin ${MANDIR}/cat3/des_crypt.0 ${MANDIR}/cat3/$$i.0; \
		done

KSEND	= \
	krb_recvauth \
	krb_net_write \
	krb_net_read

install:: ksend.point
	for i in ${KSEND} ; do \
		${INSTALLFILE} -c -o bin -g bin ${MANDIR}/cat3/krb_sendauth.0 ${MANDIR}/cat3/$$i.0; \
		done

REALM = \
	krb_get_phost \
	krb_get_krbhst \
	krb_get_admhst \
	krb_get_lrealm

install:: realm.point
	for i in ${REALM} ; do \
		${INSTALLFILE} -c -o bin -g bin ${MANDIR}/cat3/krb_realmofhost.0 ${MANDIR}/cat3/$$i.0; \
		done
KRB	= \
	krb_mk_req \
	krb_rd_req \
	krb_kntoln \
	krb_set_key \
	krb_get_cred \
	krb_mk_priv \
	krb_rd_priv \
	krb_mk_safe \
	krb_rd_safe \
	krb_mk_err \
	krb_rd_err \
	krb_ck_repl

install:: kerberos.point
	for i in ${KRB} ; do \
		${INSTALLFILE} -c -o bin -g bin ${MANDIR}/cat3/kerberos.0 ${MANDIR}/cat3/$$i.0; \
		done
#
#	@echo "Don't forget to execute makewhatis or catman" >&2
#	@echo "Also beware that older systems have man pages for" >&2
#	@echo "rsh.1c, rlogin.1c and rcp.1c which should be removed" >&2

depend:: $(SRCS)
	@echo "### Now computing dependencies"
	@$(DEPEND) -s "# DO NOT DELETE" -- $(CFLAGS) -- $(SRCS)

clean::
	$(RM) *~ \#* *.bak $(TAGSFILE)

tags::
	$(TAGGER) *.c *.h

Makefile::
	-$(RM) Makefile.bak; $(MV) Makefile Makefile.bak
	$(IMAKE) -DNEW_TOP=$(NEWTOP) -s Makefile

print:: ${CODE}
	${LPR} ${CODE}

src:: ${CODE}

${CODE}:
	$(RM) $@
	-$(LN) ${SRCDIR}/$@ $@

install::

Makefiles::

# DO NOT DELETE THIS LINE
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
