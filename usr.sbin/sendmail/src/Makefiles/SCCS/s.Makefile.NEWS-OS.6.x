h33178
s 00002/00000/00131
d D 8.3 95/06/20 06:31:00 eric 3 2
c add "depend:" entries everywhere
e
s 00011/00008/00120
d D 8.2 95/05/24 07:54:57 eric 2 1
c cleanup from Motonori Nakamura
e
s 00128/00000/00000
d D 8.1 95/05/14 09:17:53 eric 1 0
c date and time created 95/05/14 09:17:53 by eric
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
#  This has been tested on NEWS-OS 6.0.3
#
#	%W% (Berkeley) %G%
#

# use O=-O (usual) or O=-g (debugging)
O=	

# make sure that /bin/cc is used (do not use /usr/ucb/cc).
CC=	/bin/cc

# define the database mechanism used for alias lookups:
#	-DNDBM -- use new DBM
#	-DNEWDB -- use new Berkeley DB
#	-DNIS -- include NIS support
# The really old (V7) DBM library is no longer supported.
# See READ_ME for a description of how these flags interact.
#
DBMDEF=	-DNDBM -DNIS

# environment definitions (e.g., -D_AIX3)
D 2
ENVDEF= -DSYSLOG_BUFSIZE=256	# if you have a problem on syslog buffer size
E 2
I 2
# define SYSLOG_BUFSIZE=256 if you have a problem on syslog buffer size
# define SPT_TYPE=SPT_NONE if you are using NEWS-OS 6.0.1
ENVDEF= -DSYSLOG_BUFSIZE=256 # -DSPT_TYPE=SPT_NONE
E 2

# see also conf.h for additional compilation flags

# include directories
INCDIRS=-I/usr/sww/include

# library directories
LIBDIRS=-L/usr/sww/lib

# libraries required on your system
#  delete -l44bsd if you are not running BIND 4.9.x
#  -lndbm can be used instead of ndbm.o with NEWS-OS 6.1 or later
LIBS=   ndbm.o -lelf -lsocket -lnsl -lresolv # -l44bsd	# with NDBM
#LIBS=  -lelf -lsocket -lnsl -ldb -lresolv # -l44bsd	# with NEWDB

# location of sendmail binary (usually /usr/sbin or /usr/lib)
BINDIR=	${DESTDIR}/usr/lib

# location of sendmail.st file (usually /var/log or /usr/lib)
STDIR=	${DESTDIR}/etc

# location of sendmail.hf file (usually /usr/share/misc or /usr/lib)
HFDIR=	${DESTDIR}/usr/lib

# additional .o files needed
OBJADD=

# things to be made before compilation begins
BEFORE=	sysexits.h ndbm.o

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
	ln -s /usr/ucbinclude/sysexits.h .

ndbm.o:
	if [ ! -f /usr/include/ndbm.h ]; then \
D 2
		ln -n /usr/ucbinclude/ndbm.h .; \
E 2
I 2
		ln -s /usr/ucbinclude/ndbm.h .; \
E 2
	fi; \
	if [ -f /usr/lib/libndbm.a ]; then \
		ar x /usr/lib/libndbm.a ndbm.o; \
	else \
		ar x /usr/ucblib/libucb.a ndbm.o; \
	fi; \

I 2
#NROFF=	nroff -h
NROFF=	groff -Tascii
MANDOC=	-mandoc
E 2

D 2
NROFF=	nroff -h

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
I 3

depend:
E 3
E 1
