h26028
s 00000/00000/00027
d D 8.1 93/06/16 18:25:34 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00001/00001/00026
d D 7.5 93/06/16 18:25:09 mckusick 7 5
c final update from Ralph
e
s 00000/00000/00027
d R 8.1 93/06/11 17:40:32 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00004/00015
d D 7.4 93/06/11 17:40:30 bostic 5 3
c make tags, links work for 4.4BSD
e
s 00000/00000/00019
d R 8.1 93/06/10 22:37:24 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00009/00018/00010
d D 7.3 92/07/24 15:42:49 bostic 3 2
c fix? tags
e
s 00001/00001/00027
d D 7.2 92/05/05 09:34:07 bostic 2 1
c fix links target
e
s 00028/00000/00000
d D 7.1 92/01/07 20:52:41 mckusick 1 0
c date and time created 92/01/07 20:52:41 by mckusick
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 5
# Makefile for pmax tags file
E 5
I 5
# Makefile for pmax links, tags file
E 5

.include "../kern/Make.tags.inc"

all:
D 3
	@echo "make tags or links only"
E 3
I 3
D 5
	@echo "make tags only"
E 5
I 5
	@echo "make links or tags only"
E 5
E 3

D 3
TPMAX=	../pmax/tags
SPMAX=	../pmax/pmax/*.[ch] ../pmax/include/*.h ../pmax/dev/*.[ch]
APMAX=	../pmax/pmax/*.s
E 3
I 3
D 5
PMAX=	/sys/pmax/conf/*.[ch] /sys/pmax/dev/*.[ch] /sys/pmax/include/*.[ch] \
E 5
I 5
DIRS=	conf dev dist include pmax ultrix

links::
	-for i in ${DIRS}; do \
	    (cd $$i && { rm -f tags; ln -s ${SYSTAGS} tags; }) done

PMAX=	/sys/pmax/dev/*.[ch] /sys/pmax/include/*.[ch] \
E 5
	/sys/pmax/pmax/*.[ch] /sys/pmax/ultrix/*.[ch]
APMAX=	/sys/pmax/pmax/*.s
E 3

D 3
# Directories in which to place pmax tags links
DPMAX=	pmax dev include

tags: FRC
	-ctags -dtf ${TPMAX} ${COMM} ${SPMAX}
	egrep "^LEAF(.*)|^ALEAF(.*)|^NON_LEAF(.*)" ${APMAX} | \
E 3
I 3
tags::
D 5
	-ctags -dt ${COMM} ${PMAX}
E 5
I 5
	-ctags -wdt ${COMM} ${PMAX}
E 5
D 7
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${APMAX} | \
E 7
I 7
	egrep "^LEAF(.*)|^[AN]LEAF(.*)|^NON_LEAF(.*)" ${APMAX} | \
E 7
E 3
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
D 3
		>> ${TPMAX}
	sort -o ${TPMAX} ${TPMAX}

links:
	-for i in ${DPMAX}; do \
D 2
	    cd ../$$i && rm -f tags; ln -s ../tags tags; done
E 2
I 2
	    (cd $$i && rm -f tags; ln -s ../tags tags); done
E 2

FRC:
E 3
I 3
		>> tags
	sort -o tags tags
I 5
	chown bin.wsrc tags
	chmod 444 tags
E 5
E 3
E 1
