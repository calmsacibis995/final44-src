h56894
s 00000/00000/00027
d D 8.1 93/06/11 17:40:07 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00005/00014
d D 7.7 93/06/11 17:39:29 bostic 8 6
c make tags, links work for 4.4BSD
e
s 00000/00000/00019
d R 8.1 93/06/10 21:26:45 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00018/00011
d D 7.6 92/07/24 15:28:37 bostic 6 5
c fix? tags
e
s 00001/00001/00028
d D 7.5 92/05/05 09:33:05 bostic 5 4
c fix links target
e
s 00005/00005/00024
d D 7.4 92/05/05 09:32:21 karels 4 3
c tags
e
s 00001/00001/00028
d D 7.3 91/06/09 12:27:38 karels 3 2
c don't rm tags after making them
e
s 00000/00007/00029
d D 7.2 91/05/09 00:11:01 bostic 2 1
c makefile's don't need copyrights
e
s 00036/00000/00000
d D 7.1 91/05/09 00:09:50 bostic 1 0
c date and time created 91/05/09 00:09:50 by bostic
e
u
U
t
T
I 1
D 2
#
# Copyright (c) 1991 The Regents of the University of California.
# All rights reserved.
#
# %sccs.include.redist.sh
#
E 2
#	%W% (Berkeley) %G%
D 2
#
E 2

D 4
COMM=	../net/*.[ch] ../netimp/*.[ch] ../netinet/*.[ch] ../netns/*.[ch] \
	../netiso/*.[ch] ../netccitt/*.[ch] \
	../kern/*.c ../ufs/*.[ch] ../nfs/*.[ch] ../vm/*.[ch] ../sys/*.h

E 4
D 8
# Makefile for hp300 tags file
E 8
I 8
# Makefile for hp300 links, tags files
E 8

I 4
.include "../kern/Make.tags.inc"

E 4
all:
D 6
	@echo "make tags or links only"
E 6
I 6
D 8
	@echo "make tags only"
E 8
I 8
	@echo "make links or tags only"
E 8
E 6

D 6
THP300=	../hp300/tags
SHP300=	../hp300/hp300/*.[ch] ../hp300/include/*.h \
	../hp300/hpux/*.[ch] ../hp300/dev/*.[ch]
AHP300=	../hp300/hp300/*.s
E 6
I 6
D 8
HP300=	/sys/hp/dev/*.[ch] /sys/hp/hpux/*.[ch] /sys/hp300/conf/*.[ch] \
	/sys/hp300/dev/*.[ch] /sys/hp300/hp300/*.[ch] /sys/hp300/include/*.[ch]
E 8
I 8
DIRS=	conf dev hp300 include scripts

links::
	-for i in ${DIRS}; do \
	    (cd $$i && { rm -f tags; ln -s ${SYSTAGS} tags; }) done

HP300=	/sys/hp/dev/*.[ch] /sys/hp/hpux/*.[ch] /sys/hp300/dev/*.[ch] \
	/sys/hp300/hp300/*.[ch] /sys/hp300/include/*.[ch]
E 8
AHP300=	/sys/hp300/hp300/*.s
E 6

D 6
# Directories in which to place hp300 tags links
D 3
DHP300=	hp300 dev hpux include
E 3
I 3
DHP300=	dev hpux include
E 3

D 4
tags:
E 4
I 4
tags: FRC
E 4
	-ctags -dtf ${THP300} ${COMM} ${SHP300}
E 6
I 6
tags::
D 8
	-ctags -dt ${COMM} ${HP300}
E 8
I 8
	-ctags -wdt ${COMM} ${HP300}
E 8
E 6
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${AHP300} | \
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
D 6
		>> ${THP300}
	sort -o ${THP300} ${THP300}

links:
	-for i in ${DHP300}; do \
D 5
	    cd ../$$i && rm -f tags; ln -s ../tags tags; done
E 5
I 5
	    (cd $$i && rm -f tags; ln -s ../tags tags); done
E 5
I 4

FRC:
E 6
I 6
		>> tags
	sort -o tags tags
I 8
	chown bin.wsrc tags
	chmod 444 tags
E 8
E 6
E 4
E 1
