h57528
s 00000/00000/00027
d D 8.1 93/06/11 17:40:41 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00006/00014
d D 7.7 93/06/11 17:40:40 bostic 7 6
c make tags, links work for 4.4BSD
e
s 00010/00023/00010
d D 7.6 92/07/24 15:46:30 bostic 6 5
c fix? tags
e
s 00001/00001/00032
d D 7.5 92/05/05 09:33:36 bostic 5 4
c fix links target
e
s 00005/00001/00028
d D 7.4 92/05/05 09:33:20 karels 4 3
c tags
e
s 00001/00001/00028
d D 7.3 91/06/09 12:30:47 karels 3 2
c don't rm tags after making them
e
s 00000/00007/00029
d D 7.2 91/05/09 00:10:42 bostic 2 1
c Makefile's don't need copyrights
e
s 00036/00000/00000
d D 7.1 91/05/09 00:10:00 bostic 1 0
c date and time created 91/05/09 00:10:00 by bostic
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
# Makefile for tahoe tags file
E 7
I 7
# Makefile for tahoe links, tags file
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
TTAHOE=	../tahoe/tags
STAHOE=	../tahoe/tahoe/*.[ch] ../tahoe/include/*.h ../tahoe/if/*.[ch] \
	../tahoe/vba/*.[ch] ../tahoe/align/*.[ch] ../tahoe/math/*.h
ATAHOE=	../tahoe/tahoe/*.s ../tahoe/math/*.s
E 6
I 6
D 7
TAHOE=	/sys/tahoe/conf/*.[ch] /sys/tahoe/if/*.[ch] \
	/sys/tahoe/include/*.[ch] /sys/tahoe/tahoe/*.[ch] \
	/sys/tahoe/vba/*.[ch]
E 7
I 7
DIRS=	align conf dist if include math tahoe vba

links::
	-for i in ${DIRS}; do \
	    (cd $$i && { rm -f tags; ln -s ${SYSTAGS} tags; }) done

TAHOE=	/sys/tahoe/if/*.[ch] /sys/tahoe/include/*.[ch] \
	/sys/tahoe/tahoe/*.[ch] /sys/tahoe/vba/*.[ch]
E 7
ATAHOE=	/sys/tahoe/tahoe/*.s
E 6

D 6

# Directories in which to place tahoe tags links
D 3
DTAHOE=	if vba align math include tahoe
E 3
I 3
DTAHOE=	if vba align math include
E 3

D 4
tags:
E 4
I 4
tags: FRC
E 4
	-ctags -dtf ${TTAHOE} ${COMM} ${STAHOE}
	egrep "^SCBVEC(.*)" ${ATAHOE} | \
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);X\3 \1 /^\2(\3\4$$/;" \
		>> ${TTAHOE}
	egrep "^ENTRY(.*)|^JSBENTRY(.*)" ${ATAHOE} | \
E 6
I 6
tags::
D 7
	-ctags -dt ${COMM} ${TAHOE}
E 7
I 7
	-ctags -wdt ${COMM} ${TAHOE}
E 7
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${ATAHOE} | \
E 6
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
D 6
		>> ${TTAHOE}
	sort -o ${TTAHOE} ${TTAHOE}

links:
	-for i in ${DTAHOE}; do \
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
