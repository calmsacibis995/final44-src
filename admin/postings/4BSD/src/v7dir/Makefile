# @(#)Makefile	4.8 (Berkeley) 3/21/83

DESTDIR	=
CFLAGS=	-O

OBJS=	closedir.o opendir.o readdir.o scandir.o seekdir.o telldir.o
DIST=	README Makefile dir.h closedir.c opendir.c readdir.c \
	scandir.c seekdir.c telldir.c directory.3 scandir.3

.c.o:
	${CC} ${CFLAGS} -I. -c $*.c
	-ld -x -r $*.o
	mv a.out $*.o

libndir: ${OBJS}
	ar cru libndir.a ${OBJS}
	ranlib libndir.a

install: libndir
	cp ndir.h ${DESTDIR}/usr/include/ndir.h
	cp libndir.a ${DESTDIR}/usr/lib/libndir.a
	ranlib ${DESTDIR}/usr/lib/libndir.a
	cp directory.3 /usr/man/man3/directory.3
	cp scandir.3 /usr/man/man3/scandir.3

clean:
	rm -f libndir.a ${OBJS}
