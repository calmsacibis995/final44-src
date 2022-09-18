h41825
s 00000/00000/00030
d D 8.1 93/06/11 17:40:27 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00016/00008/00014
d D 7.3 93/06/11 17:40:25 bostic 4 2
c make tags, links work for 4.4BSD
e
s 00000/00000/00022
d R 8.1 93/06/10 23:47:59 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00012/00026/00010
d D 7.2 92/07/24 15:41:01 bostic 2 1
c fix? tags
e
s 00036/00000/00000
d D 7.1 92/07/24 14:36:40 bostic 1 0
c date and time created 92/07/24 14:36:40 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 4
# Makefile for news3400 tags file
E 4
I 4
# Makefile for news3400 links, tags file
E 4

.include "../kern/Make.tags.inc"

all:
D 2
	@echo "make tags or links only"
E 2
I 2
D 4
	@echo "make tags only"
E 4
I 4
	@echo "make links or tags only"
E 4
E 2

D 2
TNEWS=	../news3400/tags
SNEWS=	../news3400/news3400/*.[ch] \
	../news3400/include/*.h \
	../news3400/bm/*.[ch] \
	../news3400/fb/*.[ch] \
	../news3400/hbdev/*.[ch] \
	../news3400/if/*.[ch] \
	../news3400/iodev/*.[ch] \
	../news3400/iop/*.[ch] \
	../news3400/sio/*.[ch]
ANEWS=	../news3400/news3400/*.s
E 2
I 2
D 4
NEWS=	/sys/news3400/bm/*.[ch] /sys/news3400/conf/*.[ch] \
	/sys/news3400/fb/*.[ch] /sys/news3400/hbdev/*.[ch] \
	/sys/news3400/if/*.[ch] /sys/news3400/include/*.[ch] \
	/sys/news3400/iodev/*.[ch] /sys/news3400/iop/*.[ch] \
	/sys/news3400/news3400/*.[ch] /sys/news3400/sio/*.[ch]
E 4
I 4
DIRS=	bm conf fb hbdev if include iodev iop news3400 newsos sio

links::
	-for i in ${DIRS}; do \
	    (cd $$i && { rm -f tags; ln -s ${SYSTAGS} tags; }) done

NEWS=	/sys/news3400/bm/*.[ch] /sys/news3400/fb/*.[ch] \
	/sys/news3400/hbdev/*.[ch] /sys/news3400/if/*.[ch] \
	/sys/news3400/include/*.[ch] /sys/news3400/iodev/*.[ch] \
	/sys/news3400/iop/*.[ch] /sys/news3400/news3400/*.[ch] \
	/sys/news3400/sio/*.[ch]
E 4
ANEWS=	/sys/news3400/news3400/*.s
E 2

D 2
# Directories in which to place news3400 tags links
DNEWS=	news3400 include

tags: FRC
	-ctags -tf ${TNEWS} ${COMM} ${SNEWS}
	egrep "^LEAF(.*)|^ALEAF(.*)|^NON_LEAF(.*)" ${ANEWS} | \
E 2
I 2
tags::
D 4
	-ctags -dt ${COMM} ${NEWS}
E 4
I 4
	-ctags -wdt ${COMM} ${NEWS}
E 4
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${ANEWS} | \
E 2
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
D 2
		>> ${TNEWS}
	sort -o ${TNEWS} ${TNEWS}

links:
	-for i in ${DNEWS}; do \
	    cd ../$$i && rm -f tags; ln -s ../tags tags; done

FRC:
E 2
I 2
		>> tags
	sort -o tags tags
I 4
	chown bin.wsrc tags
	chmod 444 tags
E 4
E 2
E 1
