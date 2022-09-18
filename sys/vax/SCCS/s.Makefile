h57003
s 00000/00000/00028
d D 8.1 93/06/11 17:40:44 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00014/00006/00014
d D 7.7 93/06/11 17:40:43 bostic 7 6
c make tags, links work for 4.4BSD
e
s 00010/00022/00010
d D 7.6 92/07/24 15:48:12 bostic 6 5
c fix? tags
e
s 00001/00001/00031
d D 7.5 92/05/05 09:33:11 bostic 5 4
c fix links target
e
s 00005/00001/00027
d D 7.4 92/05/05 09:31:57 karels 4 3
c tags
e
s 00001/00001/00027
d D 7.3 91/06/09 12:25:28 karels 3 2
c don't rm tags after making them
e
s 00000/00007/00028
d D 7.2 91/05/09 00:10:25 bostic 2 1
c makefile's don't need copyrights
e
s 00035/00000/00000
d D 7.1 91/05/09 00:10:07 bostic 1 0
c date and time created 91/05/09 00:10:07 by bostic
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

D 7
# Makefile for vax tags file
E 7
I 7
# Makefile for vax link, tags file
E 7

I 4
.include "../kern/Make.tags.inc"

E 4
all:
D 6
	@echo "make tags or links only"
E 6
I 6
D 7
	@echo "make tags only"
E 7
I 7
	@echo "make links or tags only"
E 7
E 6

D 6
TVAX=	../vax/tags
SVAX=	../vax/if/*.[ch]  ../vax/mba/*.[ch] ../vax/uba/*.[ch] \
	../vax/bi/*.[ch] ../vax/vax/*.[ch] ../vax/include/*.h
AVAX=	../vax/vax/*.s
E 6
I 6
D 7
VAX=	/sys/vax/bi/*.[ch] /sys/vax/conf/*.[ch] /sys/vax/if/*.[ch] \
	/sys/vax/include/*.[ch] /sys/vax/mba/*.[ch] /sys/vax/uba/*.[ch] \
	/sys/vax/vax/*.[ch]
E 7
I 7
DIRS=	bi cassette conf consolerl datakit dist floppy if include mba \
	mdec uba vax

links::
	-for i in ${DIRS}; do \
	    (cd $$i && { rm -f tags; ln -s ${SYSTAGS} tags; }) done

VAX=	/sys/vax/bi/*.[ch] /sys/vax/if/*.[ch] /sys/vax/include/*.[ch] \
	/sys/vax/mba/*.[ch] /sys/vax/uba/*.[ch] /sys/vax/vax/*.[ch]
E 7
AVAX=	/sys/vax/vax/*.s
E 6

D 6
# Directories in which to place vax tags links
D 3
DVAX=	if mba uba bi vax include
E 3
I 3
DVAX=	if mba uba bi include
E 3

D 4
tags:
E 4
I 4
tags: FRC
E 4
	-ctags -dtf ${TVAX} ${COMM} ${SVAX}
	egrep "^SCBVEC(.*)" ${AVAX} | \
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);X\3 \1 /^\2(\3\4$$/;" \
		>> ${TVAX}
	egrep "^ENTRY(.*)|^JSBENTRY(.*)" ${AVAX} | \
E 6
I 6
tags::
D 7
	-ctags -dt ${COMM} ${VAX}
E 7
I 7
	-ctags -wdt ${COMM} ${VAX}
E 7
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${AVAX} | \
E 6
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
D 6
		>> ${TVAX}
	sort -o ${TVAX} ${TVAX}

links:
	-for i in ${DVAX}; do \
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
I 7
	chown bin.wsrc tags
	chmod 444 tags
E 7
E 6
E 4
E 1
