h33046
s 00000/00000/00027
d D 8.1 93/06/11 17:39:55 bostic 9 8
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00004/00015
d D 7.7 93/06/11 17:39:53 bostic 8 6
c make tags, links work for 4.4BSD
e
s 00000/00000/00019
d R 8.1 93/06/11 15:59:10 bostic 7 6
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00017/00011
d D 7.6 92/07/24 15:34:05 bostic 6 5
c fix? tags
e
s 00001/00001/00027
d D 7.5 92/05/05 09:34:38 bostic 5 4
c fix links target
e
s 00005/00001/00023
d D 7.4 92/05/05 09:34:24 karels 4 3
c fix tags
e
s 00001/00001/00023
d D 7.3 91/06/09 12:28:49 karels 3 2
c don't rm tags after making them
e
s 00000/00007/00024
d D 7.2 91/05/09 00:11:15 bostic 2 1
c makefile's don't need copyrights
e
s 00031/00000/00000
d D 7.1 91/05/09 00:09:33 bostic 1 0
c date and time created 91/05/09 00:09:33 by bostic
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

D 8
# Makefile for i386 tags file
E 8
I 8
# Makefile for i386 links, tags file
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
TI386=	../i386/tags
SI386=	../i386/i386/*.[ch] ../i386/include/*.h ../i386/isa/*.[ch]
AI386=	../i386/i386/*.s
E 6
I 6
D 8
I386=	/sys/i386/conf/*.[ch] /sys/i386/eisa/*.[ch] /sys/i386/i386/*.[ch] \
E 8
I 8
DIRS=	conf eisa floppy i386 include isa mca scripts

links::
	-for i in ${DIRS}; do \
	    (cd $$i && { rm -f tags; ln -s ${SYSTAGS} tags; }) done

I386=	/sys/i386/eisa/*.[ch] /sys/i386/i386/*.[ch] \
E 8
	/sys/i386/include/*.[ch] /sys/i386/isa/*.[ch]
AI386=	/sys/i386/i386/*.s
E 6

D 6
# Directories in which to place i386 tags links
D 3
DI386=	isa i386 include
E 3
I 3
DI386=	eisa isa mca include
E 3

D 4
tags:
E 4
I 4
tags: FRC
E 4
	-ctags -dtf ${TI386} ${COMM} ${SI386}
E 6
I 6
tags::
D 8
	-ctags -dt ${COMM} ${I386}
E 8
I 8
	-ctags -wdt ${COMM} ${I386}
E 8
E 6
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${AI386} | \
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
D 6
		>> ${TI386}
	sort -o ${TI386} ${TI386}

links:
	-for i in ${DI386}; do \
D 5
	    cd $$i && rm -f tags; ln -s ../tags tags; done
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
