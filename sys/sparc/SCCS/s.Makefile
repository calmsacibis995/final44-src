h63015
s 00000/00000/00029
d D 8.1 93/06/11 17:40:36 bostic 5 4
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00003/00018
d D 7.3 93/06/11 17:40:35 bostic 4 2
c make tags, links work for 4.4BSD
e
s 00000/00000/00021
d R 8.1 93/06/11 15:07:18 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00015/00012/00006
d D 7.2 92/07/24 15:44:15 bostic 2 1
c fix? tags
e
s 00018/00000/00000
d D 7.1 92/07/13 00:41:12 torek 1 0
c date and time created 92/07/13 00:41:12 by torek
e
u
U
t
T
I 1
#	%W% (Berkeley) %G%
D 2
#
# from: $Header: Makefile,v 1.11 92/06/03 21:48:05 leres Exp $ (LBL)
E 2

D 2
# Location of tags file
TAGS=	../../compile/GENERIC/tags
TAGS1=	../compile/GENERIC/tags1
E 2
I 2
D 4
# Makefile for sparc tags file
E 4
I 4
# Makefile for sparc links, tags file
E 4
E 2

D 2
# Directories in which to place sparc tags links
DSPARC=	dev fpu include rcons sbus sparc sunos
E 2
I 2
.include "../kern/Make.tags.inc"
E 2

all:
D 2
	@echo '"make links" only'
E 2
I 2
D 4
	@echo "make tags only"
E 4
I 4
	@echo "make links or tags only"
E 4
E 2

I 4
DIRS=	conf dev fpu include rcons sbus sparc sunos

links::
	-for i in ${DIRS}; do \
	    (cd $$i && { rm -f tags; ln -s ${SYSTAGS} tags; }) done

E 4
D 2
links:
	-for i in ${DSPARC}; do \
	    (cd $$i && rm -f tags; ln -s ${TAGS}); done
	rm -f tags ; ln -s ${TAGS1} tags
E 2
I 2
SPARC=	/sys/sparc/dev/*.[ch] /sys/sparc/fpu/*.[ch] \
	/sys/sparc/include/*.[ch] /sys/sparc/rcons/*.[ch] \
	/sys/sparc/sbus/*.[ch] /sys/sparc/sparc/*.[ch] \
	/sys/sparc/sunos/*.[ch]
ASPARC=	/sys/sparc/sparc/*.s

tags::
D 4
	-ctags -dt ${COMM} ${SPARC}
E 4
I 4
	-ctags -wdt ${COMM} ${SPARC}
E 4
	egrep "^ENTRY(.*)|^ALTENTRY(.*)" ${ASPARC} | \
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
		>> tags
	sort -o tags tags
I 4
	chown bin.wsrc tags
	chmod 444 tags
E 4
E 2
E 1
