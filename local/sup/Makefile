# Copyright (c) 1991 Carnegie Mellon University
# All Rights Reserved.
# 
# Permission to use, copy, modify and distribute this software and its
# documentation is hereby granted, provided that both the copyright
# notice and this permission notice appear in all copies of the
# software, derivative works or modified versions, and any portions
# thereof, and that both notices appear in supporting documentation.
#
# CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
# CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
# ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
#
# Carnegie Mellon requests users of this software to return to
#
#  Software Distribution Coordinator   or   Software.Distribution@CS.CMU.EDU
#  School of Computer Science
#  Carnegie Mellon University
#  Pittsburgh PA 15213-3890
#
# any improvements or extensions that they make and grant Carnegie the rights
# to redistribute these changes.
######################################################################
# Makefile to build sup (the client side), supfilesrv (the repository
# side, and supscan (used by the repository. If you only want to sup
# files from CMU, just build sup.
# The header files: c.h, libc.h and sysent.h are only
# necessary if you are compiling on a non-Mach system. Likewise the
# files in libextra.a are normally found in libcs.a on a Mach system.
######################################################################

DEFS=-I. -UCMUCS -UCMU

CFLAGS= ${DEFS} -g -fwritable-strings

SUPCL			= supcmain.o supcvers.o supcparse.o supcname.o \
			  supcmisc.o supcmeat.o
SUPS			= scm.o scmio.o stree.o log.o supmsg.o
EXTRA			= atoo.o errmsg.o expand.o ffilecopy.o filecopy.o nxtarg.o  \
			  path.o quit.o run.o salloc.o skipto.o stree.o


PROGRAMS		= sup #supscan supfilesrv

LIBS			= libextra.a
sup_OFILES		= ${SUPCL} ${SUPS}
supfilesrv_OFILES	= supfilesrv.o scan.o ${SUPS}
supfilesrv_LIBS		= libextra.a
supscan_OFILES		= supscan.o stree.o scan.o


all: ${PROGRAMS}

sup: ${sup_OFILES} ${LIBS}
	${CC} ${CFLAGS} -o sup ${sup_OFILES} ${LIBS}

supfilesrv: ${supfilesrv_OFILES} ${supfilesrv_LIBS}
	${CC} ${CFLAGS} -o supfilesrv ${supfilesrv_OFILES} ${supfilesrv_LIBS}

supscan:  ${supscan_OFILES} ${LIBS}
	${CC} ${CFLAGS} -o supscan ${supscan_OFILES} ${LIBS}

libextra.a: ${EXTRA}
	ar r libextra.a $?
	ranlib libextra.a

clean:
	rm -f ${PROGRAMS} libextra.a *.o core a.out


scan.o:	sup.h
scm.o:	sup.h
scmio.o: sup.h supmsg.h
stree.o: sup.h
supcmain.o: sup.h supmsg.h supcdefs.h
supcmeat.o: sup.h supmsg.h supcdefs.h
supcmisc.o: sup.h supmsg.h supcdefs.h
supcname.o: sup.h supmsg.h supcdefs.h
supcparse.o: sup.h supmsg.h supcdefs.h
supfilesrv.o: sup.h supmsg.h
supmsg.o: sup.h supmsg.h
supscan.o: sup.h
