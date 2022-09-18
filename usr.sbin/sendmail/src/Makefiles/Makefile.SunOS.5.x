#
#  This Makefile is designed to work on the old "make" program.  It does
#  not use the obj subdirectory.  It also does not install documentation
#  automatically -- think of it as a quick start for sites that have the
#  old make program (I recommend that you get and port the new make if you
#  are going to be doing any signficant work on sendmail).
#
#  This has been tested on Solaris 2.3.
#
#	@(#)Makefile.SunOS.5.x	8.9 (Berkeley) 2/6/95
#

# use O=-O (usual) or O=-g (debugging)
# warning: do not use -O with gcc
O=	

CC=	gcc

# define the database mechanism used for alias lookups:
#	-DNDBM -- use new DBM
#	-DNEWDB -- use new Berkeley DB
#	-DNIS -- include NIS support
# The really old (V7) DBM library is no longer supported.
# See READ_ME for a description of how these flags interact.
#
DBMDEF=	-DNDBM -DNIS -DNISPLUS

# environment definitions (e.g., -D_AIX3)
# include -DSOLARIS_2_3 for version 2.3 and higher
ENVDEF=	-DSOLARIS_2_3

# see also conf.h for additional compilation flags

# include directories
INCDIRS=-I/usr/sww/include/db

# library directories
LIBDIRS=-L/usr/sww/lib

# libraries required on your system
LIBS=	-lresolv -lsocket -lnsl -lelf

# location of sendmail binary (usually /usr/sbin or /usr/lib)
BINDIR=	${DESTDIR}/usr/lib

# location of sendmail.st file (usually /var/log or /usr/lib)
STDIR=	${DESTDIR}/var/log

# location of sendmail.hf file (usually /usr/share/misc or /usr/lib)
HFDIR=	${DESTDIR}/etc/mail

# additional .o files needed
OBJADD=

# things to be made before compilation begins
BEFORE=	sysexits.h

###################  end of user configuration flags  ######################

CFLAGS=	-I. $O ${INCDIRS} ${DBMDEF} ${ENVDEF}

OBJS=	alias.o arpadate.o clock.o collect.o conf.o convtime.o daemon.o \
	deliver.o domain.o envelope.o err.o headers.o macro.o main.o \
	map.o mci.o mime.o parseaddr.o queue.o readcf.o recipient.o \
	savemail.o srvrsmtp.o stab.o stats.o sysexits.o \
	trace.o udb.o usersmtp.o util.o version.o ${OBJADD}

LINKS=	${DESTDIR}/usr/ucb/newaliases ${DESTDIR}/usr/ucb/mailq
BINOWN=	root
BINGRP=	sys
BINMODE=6555
INSTALL=/usr/ucb/install

ALL=	sendmail aliases.0 mailq.0 newaliases.0 sendmail.0

all: ${ALL}

sendmail: ${BEFORE} ${OBJS}
	${CC} -o sendmail ${OBJS} ${LIBDIRS} ${LIBS}

sysexits.h:
	if [ -r /usr/ucbinclude/sysexits.h ]; \
	then \
		ln -s /usr/ucbinclude/sysexits.h; \
	fi

NROFF=	nroff -h

aliases.0: aliases.5
	${NROFF} -mandoc aliases.5 > aliases.0

mailq.0: mailq.1
	${NROFF} -mandoc mailq.1 > mailq.0

newaliases.0: newaliases.1
	${NROFF} -mandoc newaliases.1 > newaliases.0

sendmail.0: sendmail.8
	${NROFF} -mandoc sendmail.8 > sendmail.0

install: install-sendmail install-docs

install-sendmail: sendmail
	${INSTALL} -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} sendmail ${BINDIR}
	for i in ${LINKS}; do rm -f $$i; ln -s ${BINDIR}/sendmail $$i; done
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m 644 /dev/null \
	    ${STDIR}/sendmail.st
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m 444 sendmail.hf ${HFDIR}

# doesn't actually install them -- you may want to install pre-nroff versions
install-docs: aliases.0 mailq.0 newaliases.0 sendmail.0

clean:
	rm -f ${OBJS} sendmail aliases.0 mailq.0 newaliases.0 sendmail.0

# dependencies
#   gross overkill, and yet still not quite enough....
${OBJS}: sendmail.h conf.h
