h21500
s 00000/00000/00039
d D 8.1 93/06/06 22:11:43 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00039/00000/00000
d D 5.1 91/04/24 17:37:39 bostic 1 0
c date and time created 91/04/24 17:37:39 by bostic
e
u
U
t
T
I 1
# @(#)Makefile	4.7 (Berkeley) 2/3/83

DESTDIR	=
CFLAGS=	-O

OBJS=	closedir.o opendir.o readdir.o seekdir.o telldir.o
DIST=	README Makefile ndir.h closedir.c opendir.c readdir.c \
	seekdir.c telldir.c directory.3s

.c.o:
	${CC} ${CFLAGS} -I. -c $*.c
	-ld -x -r $*.o
	mv a.out $*.o

libndir.a: ${OBJS}
	rm -f libndir.a
	ar cru libndir.a `lorder ${OBJS} | tsort`
	ranlib libndir.a

install: libndir.a
	cp ndir.h ${DESTDIR}/usr/include/ndir.h
	cp libndir.a ${DESTDIR}/usr/lib/libndir.a
	ranlib ${DESTDIR}/usr/lib/libndir.a
	cp directory.3s /usr/man/man3/directory.3s

clean:
	rm -f libndir.a ${OBJS}

dist: ${DIST}
	echo "#!/bin/csh" >dist
	echo "# Run this file as shell script" >> dist
	echo "mkdir ndir" >> dist
	echo "chdir ndir" >> dist
	for i in ${DIST}; do ( \
		echo "echo extracting $$i" >> dist; \
		echo "cat > $$i <<E*O*F" >> dist; \
		sed -e 's/\\/&&/g' -e 's/\$$/\\$$/g' $$i >> dist; \
		echo 'E*O*F' >> dist); done
	chmod 775 dist
E 1
