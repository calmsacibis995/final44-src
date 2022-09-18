h32332
s 00000/00000/00017
d D 8.1 93/06/27 18:44:34 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00016
d D 5.3 93/06/27 18:44:28 bostic 4 2
c Marc for some unknown reason added -g...
e
s 00000/00000/00017
d R 8.1 93/06/06 14:48:02 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00015
d D 5.2 93/02/10 17:23:36 marc 2 1
c MUST USE SPENCERS OLD REGEXP PACKAGE (available by searching 
c libcompat first -- BARF...)  
e
s 00016/00000/00000
d D 5.1 90/06/19 12:50:51 bostic 1 0
c date and time created 90/06/19 12:50:51 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

# -DSLOWSYS	invoke xread() for system time quirk on PDP, others?
# -DNOKANJI	default is for Japanese Unix.  undef only for raw
#		parity-marked search capability, not standard w/grep.
# -DCHINESE	for systems using EUC Chinese2 codes
# -Dstrrchr=rindex, -Dstrchr=index	as necessary

PROG=	egrep
D 2
CFLAGS+=-Dstrrchr=rindex -Dstrchr=index -DNOKANJI
E 2
I 2
D 4
CFLAGS+=-Dstrrchr=rindex -Dstrchr=index -DNOKANJI -g
E 4
I 4
CFLAGS+=-Dstrrchr=rindex -Dstrchr=index -DNOKANJI
E 4
LDADD= -lcompat	# must search compat to get spencers early regexp package
E 2
MAN1=	grep.0
LINKS=	${BINDIR}/egrep ${BINDIR}/grep ${BINDIR}/egrep ${BINDIR}/fgrep
MLINKS=	grep.1 egrep.1 grep.1 fgrep.1

.include "../../Makefile.inc"
.include <bsd.prog.mk>
E 1
