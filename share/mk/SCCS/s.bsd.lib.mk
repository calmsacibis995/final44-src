h53543
s 00001/00001/00170
d D 8.3 94/04/22 11:21:10 bostic 43 42
c don't remove tags files on cleanup
e
s 00002/00002/00169
d D 8.2 94/04/02 16:39:36 bostic 42 41
c prettiness police
e
s 00000/00000/00171
d D 8.1 93/06/08 11:35:46 bostic 41 39
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00000/00171
d R 5.39 93/05/19 17:15:34 bostic 40 39
c build tags 444
e
s 00006/00002/00165
d D 5.38 93/02/10 20:51:21 bostic 39 38
c break up .o removal, C library command lines too long
e
s 00000/00008/00167
d D 5.37 93/02/04 19:16:27 ralph 38 37
c removed mips special case since gcc tools available now
e
s 00002/00002/00173
d D 5.36 92/11/30 23:34:25 bostic 37 36
c make ctags work better when obj is a directory
e
s 00002/00002/00173
d D 5.35 92/07/29 14:38:40 bostic 36 35
c remove core.${PROG}, not core
e
s 00001/00001/00174
d D 5.34 92/07/06 17:25:59 torek 35 34
c add .m4 suffix (for the sparc)
e
s 00001/00001/00174
d D 5.33 92/07/03 04:18:14 torek 34 33
c compensate for gcc -M spacing
e
s 00003/00007/00172
d D 5.32 92/03/20 20:46:58 bostic 33 32
c change mips definitions to work for NOPROFILE instead
e
s 00002/00000/00177
d D 5.31 91/12/12 16:54:33 marc 32 31
c don't install profiled libs on mips (yet)
e
s 00000/00000/00177
d D 5.30 91/12/02 15:35:01 marc 31 29
i 30
c merge in 5.26.1.1
e
s 00012/00000/00158
d D 5.26.1.1 91/12/02 15:33:50 marc 30 26
c mips changes
e
s 00008/00002/00157
d D 5.29 91/11/20 09:51:26 bostic 29 28
c change so -DNOMAN doesn't make or install man pages
e
s 00001/00001/00158
d D 5.28 91/09/09 15:23:20 bostic 28 27
c don't need to use old nroff anymore
e
s 00001/00000/00158
d D 5.27 91/08/07 16:33:29 bostic 27 26
c add manpages
e
s 00001/00001/00157
d D 5.26 91/05/02 13:41:26 bostic 26 25
c use the old nroff for now, until all the man pages converted
e
s 00007/00001/00151
d D 5.25 91/04/30 17:13:20 bostic 25 24
c add NOPROFILED define to not build profiled library
e
s 00001/00001/00151
d D 5.24 91/04/30 16:50:41 bostic 24 23
c groff doesn't like -h
e
s 00002/00002/00150
d D 5.23 91/03/21 12:14:27 bostic 23 22
c ar -s option renamed to -T (Sys V compatibility)
c 
e
s 00002/00002/00150
d D 5.22 91/03/12 09:23:51 bostic 22 21
c add -s flag to ar by default
e
s 00000/00006/00152
d D 5.21 91/03/05 16:26:15 bostic 21 20
c assembly stuff didn't work, and I don't really see any need for it.
e
s 00002/00000/00156
d D 5.20 91/03/02 11:44:27 bostic 20 19
c ranlib when build, places in the source tree use their own libraries
e
s 00002/00001/00154
d D 5.19 91/01/19 19:08:51 bostic 19 18
c change all suffixes in the SRCS list to .o, for OBJS list
e
s 00001/00001/00154
d D 5.18 91/01/14 17:01:56 bostic 18 17
c be quieter...
e
s 00006/00001/00149
d D 5.17 90/12/14 11:50:15 bostic 17 16
c make obj create /usr/obj directory as well
e
s 00001/00001/00149
d D 5.16 90/06/26 17:53:09 bostic 16 15
c if I had any intelligence, I'd be fucking dangers.
e
s 00001/00001/00149
d D 5.15 90/06/25 00:24:57 bostic 15 14
c forgot to use LIBDIR in one place
e
s 00004/00002/00146
d D 5.14 90/06/23 16:01:39 bostic 14 13
c delete the library so modules don't hang around, do quick load
e
s 00003/00000/00145
d D 5.13 90/06/23 15:53:13 bostic 13 12
c do dependencies for .po's as well as .o's
e
s 00019/00003/00126
d D 5.12 90/06/22 19:05:19 bostic 12 11
c checkpoint .mk files
e
s 00009/00012/00120
d D 5.11 90/06/01 10:30:11 bostic 11 10
c make tags work right, make OBJS additive for libc
e
s 00012/00000/00120
d D 5.10 90/05/17 16:16:46 bostic 10 9
c needs to install LINKS too
e
s 00001/00001/00119
d D 5.9 90/05/13 12:04:27 bostic 9 8
c libU77 needs fortran
e
s 00004/00001/00116
d D 5.8 90/05/12 19:44:49 bostic 8 7
c need rules to create manual pages
e
s 00002/00002/00115
d D 5.7 90/05/11 12:15:19 bostic 7 6
c comment out lint libraries for now
e
s 00012/00012/00105
d D 5.6 90/05/11 12:03:45 bostic 6 5
c move LIB defs here, get rid of reorder, minor cleanups
e
s 00001/00000/00116
d D 5.5 90/05/10 17:23:05 bostic 5 4
c add sccs id
e
s 00003/00004/00113
d D 5.4 90/05/10 17:19:32 bostic 4 3
c clean up suffix list, don't need bsd.global.mk
e
s 00028/00007/00089
d D 5.3 90/05/10 17:12:29 bostic 3 2
c do standard targets inline
e
s 00037/00044/00059
d D 5.2 90/05/08 13:42:44 bostic 2 1
c checkpoint, the world rebuilds
e
s 00103/00000/00000
d D 5.1 90/03/23 08:21:13 bostic 1 0
c date and time created 90/03/23 08:21:13 by bostic
e
u
U
f b 
t
T
I 5
#	%W% (Berkeley) %G%
E 5
I 1
D 2
LIBDIR=		/usr/lib
LINTLIBDIR=	/usr/libdata/lint
SORT=		/usr/bin/sort
CTAGS=		/usr/bin/ctags
E 2
I 2
D 4
.include <bsd.global.mk>
E 4
E 2

D 2
.MAIN: all

DEPENDFILE=	.depend
.if exists(.depend)
.include ".depend"
E 2
I 2
.if exists(${.CURDIR}/../Makefile.inc)
.include "${.CURDIR}/../Makefile.inc"
E 2
.endif

I 6
LIBDIR?=	/usr/lib
LINTLIBDIR?=	/usr/libdata/lint
LIBGRP?=	bin
LIBOWN?=	bin
LIBMODE?=	444

I 12
STRIP?=	-s

BINGRP?=	bin
BINOWN?=	bin
BINMODE?=	555

E 12
E 6
I 2
.MAIN: all

E 2
D 4
# minor mods to prefer .s to a .c, and add .po
E 4
I 4
D 6
# prefer .s to a .c, add .po, remove stuff not used in the BSD tree
E 6
I 6
# prefer .s to a .c, add .po, remove stuff not used in the BSD libraries
E 6
E 4
.SUFFIXES:
D 4
.SUFFIXES: .out .a .ln .o .po .s .c .F .f .e .r .y .l .cl .p .h \
                .8 .7 .6 .5 .4 .3 .2 .1 .0
E 4
I 4
D 8
.SUFFIXES: .out .o .po .s .c .y .l
E 8
I 8
D 9
.SUFFIXES: .out .o .po .s .c .y .l .8 .7 .6 .5 .4 .3 .2 .1 .0
E 9
I 9
D 35
.SUFFIXES: .out .o .po .s .c .f .y .l .8 .7 .6 .5 .4 .3 .2 .1 .0
E 35
I 35
.SUFFIXES: .out .o .po .s .c .f .y .l .8 .7 .6 .5 .4 .3 .2 .1 .0 .m4
E 35
E 9

.8.0 .7.0 .6.0 .5.0 .4.0 .3.0 .2.0 .1.0:
D 24
	nroff -man -h ${.IMPSRC} > ${.TARGET}
E 24
I 24
D 26
	nroff -mandoc ${.IMPSRC} > ${.TARGET}
E 26
I 26
D 28
	/usr/old/bin/nroff -mandoc ${.IMPSRC} > ${.TARGET}
E 28
I 28
	nroff -man ${.IMPSRC} > ${.TARGET}
E 28
E 26
E 24
E 8

E 4
.c.o:
	${CC} ${CFLAGS} -c ${.IMPSRC} 
	@${LD} -x -r ${.TARGET}
D 2
	@${MV} a.out ${.TARGET}
E 2
I 2
	@mv a.out ${.TARGET}
E 2

.c.po:
	${CC} -p ${CFLAGS} -c ${.IMPSRC} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
D 2
	@${MV} a.out ${.TARGET}
E 2
I 2
	@mv a.out ${.TARGET}
E 2

I 30
D 38
.if (${MACHINE} == "mips")
NOPROFILE=1
I 33
.endif

E 38
E 33
E 30
.s.o:
I 30
D 33
	${AS} ${CFLAGS:M-[ID]*} ${AINC} -o ${.TARGET} ${.IMPSRC}
	@${LD} -x -r ${.TARGET}
	@mv a.out ${.TARGET}
.else
.s.o:
E 33
E 30
	${CPP} -E ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} | \
	    ${AS} -o ${.TARGET}
	@${LD} -x -r ${.TARGET}
D 2
	@${MV} a.out ${.TARGET}
E 2
I 2
	@mv a.out ${.TARGET}
E 2

.s.po:
	${CPP} -E -DPROF ${CFLAGS:M-[ID]*} ${AINC} ${.IMPSRC} | \
	    ${AS} -o ${.TARGET}
	@${LD} -X -r ${.TARGET}
D 2
	@${MV} a.out ${.TARGET}
E 2
I 2
	@mv a.out ${.TARGET}
I 30
D 33
.endif
E 33
E 30
E 2

MANALL=	${MAN1} ${MAN2} ${MAN3} ${MAN4} ${MAN5} ${MAN6} ${MAN7} ${MAN8}
I 27
manpages: ${MANALL}
E 27

D 6
all: ranlib llib-l${LIB}.ln ${MANALL}
E 6
I 6
D 25
all: lib${LIB}.a lib${LIB}_p.a ${MANALL}# llib-l${LIB}.ln
E 25
I 25
.if !defined(NOPROFILE)
_LIBS=lib${LIB}.a lib${LIB}_p.a
.else
_LIBS=lib${LIB}.a
.endif

D 29
all: ${_LIBS} ${MANALL}# llib-l${LIB}.ln
E 29
I 29
all: ${_LIBS} # llib-l${LIB}.ln
.if !defined(NOMAN)
all: ${MANALL}
.endif
E 29
E 25
E 6

D 2
ranlib: reorder
E 2
I 2
D 6
ranlib: lib${LIB}.a lib${LIB}_p.a
E 2
	ranlib lib${LIB}.a
	ranlib lib${LIB}_p.a

D 2
STDREORDER: lib${LIB}.a lib${LIB}_p.a .USE
E 2
I 2
.if target(reorder)
ranlib: reorder
.endif
E 2

E 6
D 2
reorder: STDREORDER

E 2
D 11
OBJS=	${SRCS:S/.c$/.o/g:S/.f$/.o/g:S/.s$/.o/g}
E 11
I 11
D 19
OBJS+=	${SRCS:S/.c$/.o/g:S/.f$/.o/g:S/.s$/.o/g}
E 19
I 19
OBJS+=	${SRCS:R:S/$/.o/g}

E 19
E 11
lib${LIB}.a:: ${OBJS}
	@echo building standard ${LIB} library
D 2
	@ar cr lib${LIB}.a `lorder ${OBJS} | tsort`
E 2
I 2
D 14
	@${AR} cr lib${LIB}.a `lorder ${OBJS} | tsort` ${LDADD}
E 14
I 14
	@rm -f lib${LIB}.a
I 30
D 38
.if (${MACHINE} == "mips")
	@${AR} cq lib${LIB}.a `lorder ${OBJS} | tsort` ${LDADD}
.else
E 38
E 30
D 22
	@${AR} cq lib${LIB}.a `lorder ${OBJS} | tsort` ${LDADD}
E 22
I 22
D 23
	@${AR} csq lib${LIB}.a `lorder ${OBJS} | tsort` ${LDADD}
E 23
I 23
	@${AR} cTq lib${LIB}.a `lorder ${OBJS} | tsort` ${LDADD}
I 30
D 38
.endif
E 38
E 30
E 23
E 22
I 20
	ranlib lib${LIB}.a
E 20
E 14
E 2

D 11
POBJS=	${OBJS:.o=.po}
E 11
I 11
POBJS+=	${OBJS:.o=.po}
E 11
lib${LIB}_p.a:: ${POBJS}
	@echo building profiled ${LIB} library
D 2
	@ar cr lib${LIB}_p.a `lorder ${POBJS} | tsort`
E 2
I 2
D 14
	@${AR} cr lib${LIB}_p.a `lorder ${POBJS} | tsort` ${LDADD}
E 14
I 14
D 16
	@rm -f lib${LIB}.a
E 16
I 16
	@rm -f lib${LIB}_p.a
E 16
D 22
	@${AR} cq lib${LIB}_p.a `lorder ${POBJS} | tsort` ${LDADD}
E 22
I 22
D 23
	@${AR} csq lib${LIB}_p.a `lorder ${POBJS} | tsort` ${LDADD}
E 23
I 23
	@${AR} cTq lib${LIB}_p.a `lorder ${POBJS} | tsort` ${LDADD}
E 23
E 22
I 20
	ranlib lib${LIB}_p.a
E 20
E 14
E 2

llib-l${LIB}.ln: ${SRCS}
D 2
	lint -C${LIB} ${CFLAGS} ${.ALLSRC:M*.c}
E 2
I 2
	${LINT} -C${LIB} ${CFLAGS} ${.ALLSRC:M*.c}
E 2

D 2
clean: STDCLEAN
STDCLEAN: .USE
E 2
I 2
D 3
STDCLEAN:
E 3
I 3
.if !target(clean)
clean:
E 3
E 2
D 36
	rm -f a.out Errs errs mklog core ${CLEANFILES} ${OBJS} ${POBJS} \
E 36
I 36
D 39
	rm -f a.out Errs errs mklog ${CLEANFILES} ${OBJS} ${POBJS} \
E 39
I 39
	rm -f ${OBJS}
	rm -f ${POBJS}
D 42
	rm -f a.out Errs errs mklog ${CLEANFILES} \
E 42
I 42
	rm -f a.out [Ee]rrs mklog ${CLEANFILES} \
E 42
E 39
E 36
	    profiled/*.o lib${LIB}.a lib${LIB}_p.a llib-l${LIB}.ln
I 3
.endif
E 3

D 2
cleandir: clean STDCLEANDIR
STDCLEANDIR: .USE
	rm -f ${MANALL} ${TAGSFILE} ${DEPENDFILE}
E 2
I 2
D 3
STDCLEANDIR:
E 3
I 3
.if !target(cleandir)
cleandir:
D 36
	rm -f a.out Errs errs mklog core ${CLEANFILES} ${OBJS} ${POBJS} \
E 36
I 36
D 39
	rm -f a.out Errs errs mklog ${CLEANFILES} ${OBJS} ${POBJS} \
E 39
I 39
	rm -f ${OBJS}
	rm -f ${POBJS}
D 42
	rm -f a.out Errs errs mklog ${CLEANFILES} \
E 42
I 42
	rm -f a.out [Ee]rrs mklog ${CLEANFILES} \
E 42
E 39
E 36
	    profiled/*.o lib${LIB}.a lib${LIB}_p.a llib-l${LIB}.ln
E 3
D 11
	rm -f ${MANALL} tags .depend
E 11
I 11
D 43
	rm -f ${MANALL} ${.CURDIR}/tags .depend
E 43
I 43
	rm -f ${MANALL} .depend
E 43
E 11
I 3
.endif
E 3
E 2

D 2
depend: .depend
.depend: STDDEPEND
E 2
D 3
STDDEPEND: ${SRCS} .USE
E 3
I 3
.if !target(depend)
depend: .depend
.depend: ${SRCS}
E 3
D 2
	mkdep ${CFLAGS:M-[ID]*} ${.ALLSRC}
E 2
I 2
	mkdep ${CFLAGS:M-[ID]*} ${AINC} ${.ALLSRC}
I 13
D 18
	(TMP=/tmp/_depend$$$$; \
E 18
I 18
	@(TMP=/tmp/_depend$$$$; \
E 18
D 34
	    sed -e 's/^\([^\.]*\).o:/\1.o \1.po:/' < .depend > $$TMP; \
E 34
I 34
	    sed -e 's/^\([^\.]*\).o *:/\1.o \1.po:/' < .depend > $$TMP; \
E 34
	    mv $$TMP .depend)
E 13
I 3
.endif
E 3
E 2

D 2
tags: ${SRCS} STDTAGS
E 2
I 2
D 3
STDINSTALL:
E 3
I 3
.if !target(install)
.if !target(beforeinstall)
beforeinstall:
.endif

realinstall: beforeinstall
I 6
	ranlib lib${LIB}.a
E 6
E 3
	install -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} lib${LIB}.a \
	    ${DESTDIR}${LIBDIR}
	${RANLIB} -t ${DESTDIR}${LIBDIR}/lib${LIB}.a
I 32
D 33
.if (${MACHINE} != "mips")
E 33
I 33
.if !defined(NOPROFILE)
E 33
E 32
I 6
	ranlib lib${LIB}_p.a
E 6
	install -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    lib${LIB}_p.a ${DESTDIR}${LIBDIR}
D 15
	${RANLIB} -t ${DESTDIR}/usr/lib/lib${LIB}_p.a
E 15
I 15
	${RANLIB} -t ${DESTDIR}${LIBDIR}/lib${LIB}_p.a
I 32
.endif
E 32
E 15
D 7
	install -c -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    llib-l${LIB}.ln ${DESTDIR}${LINTLIBDIR}
E 7
I 7
#	install -c -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
#	    llib-l${LIB}.ln ${DESTDIR}${LINTLIBDIR}
I 10
.if defined(LINKS) && !empty(LINKS)
	@set ${LINKS}; \
	while test $$# -ge 2; do \
		l=${DESTDIR}$$1; \
		shift; \
		t=${DESTDIR}$$1; \
		shift; \
		echo $$t -\> $$l; \
		rm -f $$t; \
		ln $$l $$t; \
	done; true
.endif
E 10
E 7

D 3
STDLINT:
E 3
I 3
install: afterinstall
D 6
afterinstall: realinstall
E 6
I 6
D 29
afterinstall: realinstall maninstall
E 29
I 29
afterinstall: realinstall
.if !defined(NOMAN)
afterinstall: maninstall
.endif
E 29
E 6
.endif
E 3

E 2
D 3
STDTAGS: .USE
E 3
I 3
.if !target(lint)
lint:
.endif

.if !target(tags)
D 12
tags:
E 3
D 2
	${CTAGS} ${.ALLSRC:M*.c}
	${SED} -e 's;../gen/;/usr/src/lib/libc/gen/;' \
E 2
I 2
D 11
	tags ${.ALLSRC:M*.c}
	sed -e 's;../gen/;/usr/src/lib/libc/gen/;' \
E 2
	    -e 's;../compat-43/;/usr/src/lib/libc/gen/;' \
	    < tags > tags.tmp
E 11
I 11
	cd ${.CURDIR}; ctags -f /dev/stdout ${.ALLSRC:M*.c} | \
E 12
I 12
tags: ${SRCS}
D 37
	-cd ${.CURDIR}; ctags -f /dev/stdout ${.ALLSRC:M*.c} | \
E 12
	    sed "s;\${.CURDIR}/;;" > tags
E 37
I 37
	-ctags -f /dev/stdout ${.ALLSRC:M*.c} | \
	    sed "s;\${.CURDIR}/;;" > ${.CURDIR}/tags
E 37
E 11
D 21
.if !empty(SRCS:M*.s)
D 11
	egrep -o "^ENTRY(.*)|^SYSCALL(.*)" ${.ALLSRC:M*.s} | sed \
	"s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \`pwd\`/\1 /^\2(\3\4$$/;" \
	>> tags.tmp
D 2
	${SORT} tags.tmp -o tags.tmp
E 2
I 2
	sort tags.tmp -o tags.tmp
E 11
I 11
D 12
	cd ${.CURDIR}; egrep -o "^ENTRY(.*)|^SYSCALL(.*)" ${.ALLSRC:M*.s} | \
E 12
I 12
	-cd ${.CURDIR}; egrep -o "^ENTRY(.*)|^SYSCALL(.*)" ${.ALLSRC:M*.s} | \
E 12
	    sed \
	    "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \`pwd\`/\1 /^\2(\3\4$$/;" \
	    >> tags; sort -o tags tags
E 11
E 2
.endif
E 21
D 2
	${MV} tags.tmp tags
E 2
I 2
D 11
	mv tags.tmp tags
E 11
I 3
.endif
E 3
E 2

D 6
.include <bsd.own.mk>
E 6
I 6
.include <bsd.man.mk>
I 12
.if !target(obj)
.if defined(NOOBJ)
obj:
.else
obj:
	@cd ${.CURDIR}; rm -rf obj; \
	here=`pwd`; dest=/usr/obj/`echo $$here | sed 's,/usr/src/,,'`; \
D 17
	echo "$$here -> $$dest"; ln -s $$dest obj
E 17
I 17
	echo "$$here -> $$dest"; ln -s $$dest obj; \
	if test -d /usr/obj -a ! -d $$dest; then \
		mkdir -p $$dest; \
	else \
		true; \
	fi;
E 17
.endif
.endif
E 12
E 6
D 2

install: STDINSTALL
STDINSTALL: MANINSTALL .USE
	${INSTALL} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} lib${LIB}.a \
	    ${DESTDIR}${LIBDIR}
	${RANLIB} -t ${DESTDIR}${LIBDIR}/lib${LIB}.a
	${INSTALL} -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    lib${LIB}_p.a ${DESTDIR}${LIBDIR}
	${RANLIB} -t ${DESTDIR}/usr/lib/lib${LIB}_p.a
	${INSTALL} -c -o ${LIBOWN} -g ${LIBGRP} -m ${LIBMODE} \
	    llib-l${LIB}.ln ${DESTDIR}${LINTLIBDIR}
E 2
I 2
D 3
.include <bsd.stdtarg.mk>
E 3
E 2
E 1
