h35197
s 00001/00001/00013
d D 5.2 91/04/29 18:41:25 sklower 2 1
c /sys/h doesn't exist in BSD systems anymore
e
s 00014/00000/00000
d D 5.1 90/09/07 19:26:55 sklower 1 0
c date and time created 90/09/07 19:26:55 by sklower
e
u
U
t
T
I 1
x29d:	x29d.o
	cc x29d.o -o x29d ../lib/x25lib.a

install:	x29d
	install -s -m 740 x29d /etc/x29d

D 2
x29d.o:	../h/x29.h /sys/h/ioctl.h ../lib/x25lib.a
E 2
I 2
x29d.o:	../h/x29.h
E 2
	cc -O -c -DCCITT x29d.c

lint:
	lint -hbaxu -DCCITT x29d.c

clean:
	rm -f core *.o *.CKP .emacs*
E 1
