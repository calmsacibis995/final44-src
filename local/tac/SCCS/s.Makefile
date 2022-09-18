h51253
s 00007/00047/00005
d D 1.2 90/11/08 16:28:58 karels 2 1
c new-style makefile
e
s 00052/00000/00000
d D 1.1 85/06/09 01:45:16 lepreau 1 0
c date and time created 85/06/09 01:45:16 by lepreau
e
u
U
t
T
I 1
#	%M%	%I%	%G%
#
D 2
DESTDIR=
BINDIR=	/usr/new
MANTYPE= n
E 2

D 2
CFLAGS=	-O
E 2
I 2
PROG=	tac
SCRIPT=	tmail.sh
MAN1=	tac.0 tmail.0
E 2

D 2
STD=	tac
SCRIPT=	tmail
MAN=	tac.1 tmail.1
E 2
I 2
afterinstall:
	install -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/tmail.sh ${DESTDIR}${BINDIR}/tmail
E 2

D 2
all:	${STD}

${STD}:
	cc ${CFLAGS} -o $@ $@.c

install: all
	install -s tac ${DESTDIR}${BINDIR}/tac
	install -m 755 -c tmail.sh ${DESTDIR}${BINDIR}/tmail
	-for i in ${MAN}; do \
	    (install -m 644 -c $$i \
	    ${DESTDIR}/usr/man/man${MANTYPE}/`basename $$i .1`.${MANTYPE}); \
	    done

clean:
	rm -f *.o ${STD} Makefile.bak makedep eddep a.out core errs 

depend:
	rm -f makedep
	for i in ${STD}; do \
		(${CC} -M $$i.c |sed 's/.o: /: /' >>makedep); done
	echo '/^# DO NOT DELETE THIS LINE/+2,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	chmod u+w Makefile
	cp Makefile Makefile.bak
	ed - Makefile < eddep
	rm -f eddep makedep
	echo '# DEPENDENCIES MUST END AT END OF FILE' >> Makefile
	echo '# IF YOU PUT STUFF HERE IT WILL GO AWAY' >> Makefile
	echo '# see make depend above' >> Makefile

# DO NOT DELETE THIS LINE -- make depend uses it

tac: tac.c
tac: /usr/include/sys/types.h
tac: /usr/include/sys/stat.h
tac: /usr/include/stdio.h
# DEPENDENCIES MUST END AT END OF FILE
# IF YOU PUT STUFF HERE IT WILL GO AWAY
# see make depend above
E 2
I 2
.include <bsd.prog.mk>
E 2
E 1
