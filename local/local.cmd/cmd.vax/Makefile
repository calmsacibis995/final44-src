CFLAGS=	-O
LIBC=	/lib/libc.a
SRCS=	capfix.c
OBJS=	capfix.o

all: capfix

capfix: ${OBJS} ${LIBC}
	${CC} -o $@ ${CFLAGS} ${OBJS}

clean: FRC
	rm -f ${OBJS} core capfix

depend: FRC
	mkdep -p ${CFLAGS} ${SRCS}

install: FRC
	install -s -o bin -g bin -m 755 capfix ${DESTDIR}/usr/local/capfix

lint: FRC
	lint ${CFLAGS} ${SRCS}

tags: FRC
	ctags ${SRCS}

FRC:

# DO NOT DELETE THIS LINE -- mkdep uses it.
# DO NOT PUT ANYTHING AFTER THIS LINE, IT WILL GO AWAY.

capfix: capfix.c /usr/include/sys/ioctl.h /usr/include/sys/ttychars.h
capfix: /usr/include/sys/ttydev.h /usr/include/stdio.h

# IF YOU PUT ANYTHING HERE IT WILL GO AWAY
