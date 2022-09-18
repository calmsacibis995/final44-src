h08272
s 00003/00003/00103
d D 8.14 95/05/29 09:01:42 eric 29 28
c delete cs-riscos.cf from targets list
e
s 00001/00000/00105
d D 8.13 95/05/23 12:11:11 eric 28 27
c add MAILER(mail11)
e
s 00002/00002/00103
d D 8.12 95/05/18 08:21:02 eric 27 26
c add mailspool.cs.mc
e
s 00003/00003/00102
d D 8.11 95/04/21 09:03:11 eric 26 25
c oops....  a few file name typos
e
s 00034/00018/00071
d D 8.10 95/04/21 08:39:05 eric 25 24
c cleanup of DOMAIN and OSTYPE to try to avoid common errors
e
s 00002/00001/00087
d D 8.9 94/11/20 17:23:44 eric 24 23
c FEATURE(local_procmail) and MAILER(procmail)
e
s 00001/00000/00087
d D 8.8 94/11/13 16:25:02 eric 23 22
c add FEATURE(procmail)
e
s 00001/00000/00086
d D 8.7 94/11/13 15:51:38 eric 22 21
c delete notsticky; add stickyhost
e
s 00001/00001/00085
d D 8.6 94/06/26 15:32:46 eric 21 20
c add huginn.cf
e
s 00001/00000/00085
d D 8.5 93/12/01 11:55:30 eric 20 19
c add riscos-cs-exposed.cf to the default list
e
s 00001/00000/00084
d D 8.4 93/10/15 17:58:02 eric 19 18
c add osf files
e
s 00032/00002/00052
d D 8.3 93/08/25 16:17:18 eric 18 17
c update dependencies
e
s 00001/00001/00053
d D 8.2 93/08/21 15:15:18 eric 17 16
c add clientproto.cf
e
s 00000/00000/00054
d D 8.1 93/06/07 10:06:41 bostic 16 15
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00000/00053
d D 6.7 93/05/01 09:02:30 eric 15 14
c add python.cf
e
s 00001/00000/00052
d D 6.6 93/04/26 14:51:24 eric 14 13
c add hpux config files
e
s 00001/00001/00051
d D 6.5 93/02/27 12:04:19 eric 13 12
c add auspex.cf
e
s 00002/00001/00050
d D 6.4 93/02/27 08:24:46 eric 12 11
c create tcpproto.cf and uucpproto.cf
e
s 00000/00002/00051
d D 6.3 93/02/14 15:12:40 eric 11 10
c delete feature/no_wildcard_MX.m4 and m4/boilerplate.m4
e
s 00001/00001/00052
d D 6.2 93/01/07 10:21:57 eric 10 9
c s2000 => s2k
e
s 00000/00000/00053
d D 6.1 92/12/21 16:09:36 eric 9 8
c Release 6
e
s 00001/00001/00052
d D 5.8 92/11/16 20:04:29 eric 8 7
c add alpha.cf and s2000.cf
e
s 00001/00001/00052
d D 5.7 92/11/14 08:21:32 eric 7 6
c remove hacks for dead m4 versions
e
s 00001/00001/00052
d D 5.6 92/11/14 08:09:35 eric 6 5
c fix botch with current directory
e
s 00001/00001/00052
d D 5.5 92/11/13 22:56:58 eric 5 4
c quote versionid to avoid # problems
e
s 00001/00001/00052
d D 5.4 92/11/13 21:43:55 eric 4 3
c make it so it will work in other environments
e
s 00001/00001/00052
d D 5.3 92/07/24 10:23:58 eric 3 2
c mail.mc => mail.cs.mc; add mail.eecs.mc
e
s 00006/00002/00047
d D 5.2 92/07/21 14:31:23 bostic 2 1
c build into the obj directory
e
s 00049/00000/00000
d D 5.1 92/07/21 14:10:02 bostic 1 0
c date and time created 92/07/21 14:10:02 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

I 25
#
#  This Makefile uses the new Berkeley "make" program.  See Makefile.dist
#  for a more vanilla version.
#
#  Configuration files are created using "m4 file.mc > file.cf";
#  this may be easier than tweaking the Makefile.  You do need to
#  have a fairly modern M4 available (GNU m4 works).  On SunOS, use
#  /usr/5bin/m4.
#

E 25
M4=	m4
#M4=	/usr/src/usr.bin/m4/obj/m4
CHMOD=	chmod
ROMODE=	444
RM=	rm -f

.SUFFIXES:  .mc .cf

.mc.cf:
	$(RM) $@
D 2
	$(M4) $< > $@
E 2
I 2
D 4
	(cd ${.CURDIR} && $(M4) $< > obj/$@)
E 4
I 4
D 5
	(cd ${.CURDIR} && $(M4) ${@:R}.mc > obj/$@)
E 5
I 5
D 6
	cd ${.CURDIR} && echo DOIT | $(M4) ${@:R}.mc - > obj/$@
E 6
I 6
D 7
	(cd ${.CURDIR} && echo DOIT | $(M4) ${@:R}.mc - > obj/$@)
E 7
I 7
	(cd ${.CURDIR} && $(M4) ${@:R}.mc > obj/$@)
E 7
E 6
E 5
E 4
E 2
	$(CHMOD) $(ROMODE) $@

D 25
ALL=	cs-hidden.cf cs-exposed.cf \
I 14
	hpux-cs-exposed.cf hpux-cs-hidden.cf \
I 20
	riscos-cs-exposed.cf \
E 20
E 14
	sunos3.5-cs-exposed.cf sunos3.5-cs-hidden.cf \
	sunos4.1-cs-exposed.cf sunos4.1-cs-hidden.cf \
	ultrix4.1-cs-exposed.cf ultrix4.1-cs-hidden.cf \
I 19
	osf1-cs-exposed.cf osf1-cs-hidden.cf \
E 19
D 3
	mail.cf ucbvax.cf vangogh.cf \
E 3
I 3
D 21
	mail.cs.cf mail.eecs.cf ucbvax.cf vangogh.cf \
E 21
I 21
	mail.cs.cf mail.eecs.cf huginn.cf ucbvax.cf vangogh.cf \
E 21
E 3
D 8
	chez.cf knecht.cf cogsci.cf
E 8
I 8
D 10
	chez.cf knecht.cf cogsci.cf alpha.cf s2000.cf
E 10
I 10
D 12
	chez.cf knecht.cf cogsci.cf alpha.cf s2k.cf
E 12
I 12
D 13
	chez.cf knecht.cf cogsci.cf alpha.cf s2k.cf \
E 13
I 13
	chez.cf knecht.cf cogsci.cf alpha.cf s2k.cf auspex.cf \
I 15
	python.cf \
E 15
E 13
D 17
	tcpproto.cf uucpproto.cf
E 17
I 17
	clientproto.cf tcpproto.cf uucpproto.cf
E 25
I 25
ALL=	generic-hpux9.cf generic-osf1.cf generic-solaris2.cf \
		generic-sunos4.1.cf generic-ultrix4.cf \
D 26
	cs-hpux9.cf cs-riscos.cf cs-solarix2.cf \
		cs-sunos4.1.cf cs-ultrix4.1.cf cs-osf1-cs.cf \
	s2k-ultrix4.1.cf s2k-osf1.cf \
E 26
I 26
D 29
	cs-hpux9.cf cs-riscos.cf cs-solaris2.cf \
		cs-sunos4.1.cf cs-ultrix4.cf cs-osf1.cf \
	s2k-ultrix4.cf s2k-osf1.cf \
E 29
I 29
	cs-hpux9.cf cs-osf1.cf cs-solaris2.cf \
		cs-sunos4.1.cf cs-ultrix4.cf \
	s2k-osf1.cf s2k-ultrix4.cf \
E 29
E 26
D 27
	chez.cs.cf huginn.cs.cf mail.cs.cf mail.eecs.cf python.cs.cf \
		ucbarpa.cf ucbvax.cf vangogh.cs.cf
E 27
I 27
	chez.cs.cf huginn.cs.cf mail.cs.cf mail.eecs.cf mailspool.cs.cf \
		python.cs.cf ucbarpa.cf ucbvax.cf vangogh.cs.cf
E 27
E 25
E 17
E 12
E 10
E 8

all: $(ALL)

D 2
clean:
E 2
I 2
clean cleandir:
E 2
	$(RM) $(ALL) core

I 2
depend install: 

E 2
# this is overkill, but....
D 18
M4FILES=../domain/cs.exposed.m4 \
	../domain/cs.hidden.m4 \
E 18
I 18
M4FILES=\
E 18
D 25
	../domain/Berkeley.m4 \
I 18
	../domain/cs.exposed.m4 \
	../domain/cs.hidden.m4 \
	../domain/eecs.hidden.m4 \
	../domain/s2k.m4 \
E 25
I 25
	../domain/Berkeley.EDU.m4 \
	../domain/CS.Berkeley.EDU.m4 \
	../domain/EECS.Berkeley.EDU.m4 \
	../domain/S2K.Berkeley.EDU.m4 \
E 25
	../feature/allmasquerade.m4 \
	../feature/always_add_domain.m4 \
I 25
	../feature/bestmx_is_local.m4 \
E 25
	../feature/bitdomain.m4 \
	../feature/domaintable.m4 \
I 24
	../feature/local_procmail.m4 \
E 24
	../feature/mailertable.m4 \
	../feature/nocanonify.m4 \
	../feature/nodns.m4 \
	../feature/notsticky.m4 \
	../feature/nouucp.m4 \
	../feature/nullclient.m4 \
I 23
D 24
	../feature/procmail.m4 \
E 24
E 23
	../feature/redirect.m4 \
I 25
	../feature/smrsh.m4 \
E 25
I 22
	../feature/stickyhost.m4 \
E 22
E 18
D 11
	../feature/no_wildcard_MX.m4 \
E 11
	../feature/use_cw_file.m4 \
I 18
	../feature/uucpdomain.m4 \
E 18
	../hack/cssubdomain.m4 \
D 11
	../m4/boilerplate.m4 \
E 11
	../m4/cf.m4 \
I 18
	../m4/nullrelay.m4 \
E 18
	../m4/proto.m4 \
	../m4/version.m4 \
I 18
	../mailer/fax.m4 \
E 18
	../mailer/local.m4 \
I 28
	../mailer/mail11.m4 \
E 28
I 25
	../mailer/pop.m4 \
E 25
I 24
	../mailer/procmail.m4 \
E 24
	../mailer/smtp.m4 \
I 18
	../mailer/usenet.m4 \
E 18
	../mailer/uucp.m4 \
I 18
	../ostype/aix3.m4 \
I 25
	../ostype/amdahl-uts.m4 \
	../ostype/aux.m4 \
E 25
E 18
	../ostype/bsd4.3.m4 \
	../ostype/bsd4.4.m4 \
I 18
D 25
	../ostype/hpux.m4 \
E 25
I 25
	../ostype/bsdi1.0.m4 \
	../ostype/dgux.m4 \
	../ostype/domainos.m4 \
	../ostype/dynix3.2.m4 \
	../ostype/hpux9.m4 \
E 25
	../ostype/irix.m4 \
	../ostype/linux.m4 \
	../ostype/nextstep.m4 \
	../ostype/osf1.m4 \
I 25
	../ostype/ptx2.m4 \
E 25
E 18
	../ostype/riscos4.5.m4 \
I 25
	../ostype/sco3.2.m4 \
E 25
I 18
	../ostype/solaris2.m4 \
E 18
	../ostype/sunos3.5.m4 \
	../ostype/sunos4.1.m4 \
I 18
	../ostype/svr4.m4 \
E 18
D 25
	../ostype/ultrix4.1.m4 \
E 25
I 25
	../ostype/ultrix4.m4 \
E 25
I 18
	../siteconfig/uucp.cogsci.m4 \
	../siteconfig/uucp.old.arpa.m4 \
	../siteconfig/uucp.ucbarpa.m4 \
	../siteconfig/uucp.ucbvax.m4 \
E 18

$(ALL):  $(M4FILES)
I 2

.include <bsd.prog.mk>
E 2
E 1
