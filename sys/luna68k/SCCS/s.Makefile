h30982
s 00001/00001/00026
d R 8.2 94/03/21 14:36:21 bostic 5 4
c add stand directory
e
s 00000/00000/00027
d D 8.1 93/06/11 17:40:22 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00013/00005/00014
d D 7.2 93/06/11 17:40:20 bostic 3 1
c make tags, links work for 4.4BSD
e
s 00000/00000/00019
d R 8.1 93/06/10 22:19:36 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00019/00000/00000
d D 7.1 92/07/24 15:36:59 bostic 1 0
c date and time created 92/07/24 15:36:59 by bostic
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%

D 3
# Makefile for luna68k tags file
E 3
I 3
# Makefile for luna68k links, tags file
E 3

.include "../kern/Make.tags.inc"

all:
D 3
	@echo "make tags only"
E 3
I 3
	@echo "make links or tags only"
E 3

D 3
ILUNA=	/sys/luna68k/conf/*.[ch] /sys/luna68k/dev/*.[ch] \
	/sys/luna68k/include/*.[ch] /sys/luna68k/luna68k/*.[ch]
E 3
I 3
DIRS=	conf dev font include luna68k

links::
	-for i in ${DIRS}; do \
	    (cd $$i && { rm -f tags; ln -s ${SYSTAGS} tags; }) done

ILUNA=	/sys/luna68k/dev/*.[ch] /sys/luna68k/include/*.[ch] \
	/sys/luna68k/luna68k/*.[ch]
E 3
ALUNA=	/sys/luna68k/luna68k/*.s

tags::
D 3
	-ctags -dt ${COMM} ${LUNA}
E 3
I 3
	-ctags -wdt ${COMM} ${LUNA}
E 3
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${ALUNA} | \
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
		>> tags
	sort -o tags tags
I 3
	chown bin.wsrc tags
	chmod 444 tags
E 3
E 1
