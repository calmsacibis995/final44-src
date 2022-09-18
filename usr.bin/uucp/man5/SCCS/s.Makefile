h29556
s 00000/00000/00014
d D 8.1 93/06/06 22:17:30 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00014/00000/00000
d D 5.1 91/03/02 13:14:20 bostic 1 0
c date and time created 91/03/02 13:14:20 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

MAN5=	L-devices.0 L-dialcodes.0 L.aliases.0 L.cmds.0 L.sys.0 USERFILE.0

all: ${MAN5}

clean depend lint tags:

cleandir:
	rm -f ${MAN5}

install: maninstall

.include <bsd.prog.mk>
E 1
