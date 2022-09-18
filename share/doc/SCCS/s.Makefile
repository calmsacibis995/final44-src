h50792
s 00000/00000/00007
d D 8.1 93/06/05 15:07:16 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00000/00002/00007
d D 5.3 93/06/05 15:07:12 bostic 4 3
c checkpoint
e
s 00001/00001/00008
d D 5.2 93/06/02 17:18:13 bostic 3 1
c ps1 and ps2 merge into psd
e
s 00002/00003/00006
d D 5.1.1.1 91/05/07 21:41:04 bostic 2 1
c branch for the 2nd network distribution
e
s 00009/00000/00000
d D 5.1 90/06/30 14:57:30 bostic 1 0
c new doc makefiles
e
u
U
f b 
t
T
I 1
#	%W% (Berkeley) %G%

D 2
D 4
# papers doesn't get distributed
# index, iso, and ucs aren't done yet
E 4
D 3
SUBDIR=	ps1 ps2 smm usd
E 3
I 3
SUBDIR=	psd smm usd
E 3
E 2
I 2
#Missing: index iso papers ps2 ucs
SUBDIR=	ps1 smm usd
E 2

all depend lint tags:

.include <bsd.subdir.mk>
E 1
