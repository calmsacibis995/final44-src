h47023
s 00002/00000/00109
d D 8.4 95/06/20 06:30:53 eric 4 3
c add "depend:" entries everywhere
e
s 00001/00002/00108
d D 8.3 95/06/10 08:43:16 eric 3 2
c tested on 5.3, not 5.2, and cc, not gcc
e
s 00007/00005/00103
d D 8.2 95/04/10 13:11:27 eric 2 1
c macro-ize nroff stuff; use groff -Tascii by default
e
s 00108/00000/00000
d D 8.1 95/03/30 15:22:54 eric 1 0
c date and time created 95/03/30 15:22:54 by eric
e
u
U
t
T
I 1
#
#  This Makefile is designed to work on the old "make" program.  It does
#  not use the obj subdirectory.  It also does not install documentation
#  automatically -- think of it as a quick start for sites that have the
#  old make program (I recommend that you get and port the new make if you
#  are going to be doing any signficant work on sendmail).
#
D 3
#  Tested on IRIX 5.2 and 5.3 by Kari E. Hurtta <Kari.Hurtta@fmi.fi>.
E 3
I 3
#  Tested on IRIX 5.3 by Kari E. Hurtta <Kari.Hurtta@fmi.fi>.
E 3
#
#	%W% (Berkeley) %G%
#
SHELL=	/bin/sh

# use O=-O (usual) or O=-g (debugging)
O=	-O
D 3
CC=gcc
E 3

# define the database mechanisms available for map & alias lookups:
#	-DNDBM -- use new DBM
#	-DNEWDB -- use new Berkeley DB (requires -ldb)
#	-DNIS -- include NIS support (requires -lsun)
# The really old (V7) DBM library is no longer supported.
# See READ_ME for a description of how these flags interact.
#
DBMDEF=	-DNDBM -DNIS

# environment definitions (e.g., -D_AIX3)
ENVDEF= -DIRIX5

# see also conf.h for additional compilation flags

# include directories
INCDIRS=

# library directories
LIBDIRS=

# libraries required on your system
LIBS= -lmld -lmalloc -lsun

# location of sendmail binary (usually /usr/sbin or /usr/lib)
BINDIR=	${DESTDIR}/usr/lib

# location of sendmail.st file (usually /var/log or /usr/lib)
STDIR=	${DESTDIR}/usr/lib

# location of sendmail.hf file (usually /usr/share/misc or /usr/lib)
HFDIR=	${DESTDIR}/usr/lib

# additional .o files needed
OBJADD=

###################  end of user configuration flags  ######################

CFLAGS=	-I. $O ${INCDIRS} ${DBMDEF} ${ENVDEF}

OBJS=	alias.o arpadate.o clock.o collect.o conf.o convtime.o daemon.o \
	deliver.o domain.o envelope.o err.o headers.o macro.o main.o \
	map.o mci.o mime.o parseaddr.o queue.o readcf.o recipient.o \
	savemail.o srvrsmtp.o stab.o stats.o sysexits.o \
	trace.o udb.o usersmtp.o util.o version.o ${OBJADD}

LINKS=	${DESTDIR}/usr/bsd/newaliases ${DESTDIR}/usr/bsd/mailq
BINOWN=	root
BINGRP=	sys
BINMODE=6555

ALL=	sendmail aliases.0 mailq.0 newaliases.0 sendmail.0

all: ${ALL}

sendmail: ${BEFORE} ${OBJS}
	${CC} -o sendmail ${OBJS} ${LIBDIRS} ${LIBS}

D 2
NROFF=	nroff -h
E 2
I 2
#NROFF=	nroff -h
NROFF=	groff -Tascii
MANDOC=	-mandoc
E 2

aliases.0: aliases.5
D 2
	${NROFF} -mandoc aliases.5 > aliases.0
E 2
I 2
	${NROFF} ${MANDOC} aliases.5 > aliases.0
E 2

mailq.0: mailq.1
D 2
	${NROFF} -mandoc mailq.1 > mailq.0
E 2
I 2
	${NROFF} ${MANDOC} mailq.1 > mailq.0
E 2

newaliases.0: newaliases.1
D 2
	${NROFF} -mandoc newaliases.1 > newaliases.0
E 2
I 2
	${NROFF} ${MANDOC} newaliases.1 > newaliases.0
E 2

sendmail.0: sendmail.8
D 2
	${NROFF} -mandoc sendmail.8 > sendmail.0
E 2
I 2
	${NROFF} ${MANDOC} sendmail.8 > sendmail.0
E 2

install: install-sendmail install-docs

install-sendmail: sendmail
	install -u ${BINOWN} -g ${BINGRP} -m ${BINMODE} -f ${BINDIR} sendmail
	for i in ${LINKS}; do rm -f $$i; ln -s ${BINDIR}/sendmail $$i; done
	cp /dev/null ${STDIR}/sendmail.st
	chmod 644 ${STDIR}/sendmail.st
	chown ${BINOWN} ${STDIR}/sendmail.st
	chgrp ${BINGRP} ${STDIR}/sendmail.st
	install -u ${BINOWN} -g ${BINGRP} -m 444 -f ${HFDIR} sendmail.hf

# doesn't actually install them -- you may want to install pre-nroff versions
install-docs: aliases.0 mailq.0 newaliases.0 sendmail.0

clean:
	rm -f ${OBJS} sendmail aliases.0 mailq.0 newaliases.0 sendmail.0

# dependencies
#   gross overkill, and yet still not quite enough....
${OBJS}: sendmail.h conf.h
I 4

depend:
E 4
E 1
