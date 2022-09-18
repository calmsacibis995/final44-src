h57081
s 00000/00000/00028
d D 5.2 91/04/29 18:50:12 sklower 2 1
c version for Networking 2 tape
e
s 00028/00000/00000
d D 5.1 90/09/03 18:55:34 sklower 1 0
c date and time created 90/09/03 18:55:34 by sklower
e
u
U
t
T
I 1
all:	lib/x25lib.a x25config nimd/nimd x29d/x29d

install:	all
	install -s -m 755 x25config /etc/x25config
	(cd nimd; make install)
	(cd x29d; make install)
	@echo don't forget to edit /etc/rc.local

lib/x25lib.a:
	(cd lib; make)

x25config:	x25config.c lib/x25lib.a
	cc -O x25config.c lib/x25lib.a -o x25config

nimd/nimd:
	(cd nimd; make)

x29d/x29d:
	(cd x29d; make)

clean:
	(cd lib; make clean)
	(cd nimd; make clean)
	(cd x29d; make clean)
	rm -f core *.o *.CKP .emacs*

cleanall:	clean
	rm -f x25config lib/x25lib.a nimd/nimd x29d/x29d
E 1
