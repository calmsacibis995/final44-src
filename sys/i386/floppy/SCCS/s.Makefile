h23279
s 00000/00000/00018
d D 8.1 93/06/11 15:26:19 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00017
d D 5.6 91/05/20 17:57:03 bostic 6 5
c delete rlogin, telnet and rsh already ehre
e
s 00002/00001/00016
d D 5.5 91/05/10 15:04:46 bostic 5 4
c cleanups
e
s 00004/00000/00013
d D 5.4 91/05/10 14:57:46 bostic 4 3
c clean bin, too
e
s 00005/00000/00008
d D 5.3 91/05/10 14:38:19 bostic 3 2
c add install label
e
s 00001/00001/00007
d D 5.2 91/05/09 18:13:59 bostic 2 1
c echo is built into the shell
e
s 00008/00000/00000
d D 5.1 91/05/03 19:34:13 bostic 1 0
c date and time created 91/05/03 19:34:13 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 2
SUBDIR=	arp bad144 cat cp dd disklabel dump echo ed fsck ftp ifconfig \
E 2
I 2
SUBDIR=	arp bad144 cat cp dd disklabel dump ed fsck ftp ifconfig \
E 2
D 6
	init ls mkdir mknod mount mv netstat newfs ping restore rlogin \
E 6
I 6
	init ls mkdir mknod mount mv netstat newfs ping restore \
E 6
	rm route rsh sh slattach stty sync tar telnet umount

I 4
.if make(clean) || make(cleandir)
SUBDIR+=bin
.endif

E 4
I 3
install:
	for i in ${SUBDIR}; do \
D 5
		mv $$i/obj/$$i bin/$$i \
E 5
I 5
		mv $$i/obj/$$i bin/$$i; \
E 5
	done
I 5
	cd bin; strip [a-z]*
E 5

E 3
.include <bsd.subdir.mk>

E 1
