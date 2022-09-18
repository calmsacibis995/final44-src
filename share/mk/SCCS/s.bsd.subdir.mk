h29904
s 00000/00000/00080
d D 8.1 93/06/08 11:35:50 bostic 11 10
c 4.4BSD snapshot (revision 8.1)
e
s 00011/00000/00069
d D 5.10 91/08/07 16:34:08 karels 10 9
c add manpages, maninstall, objdir
e
s 00001/00001/00068
d D 5.9 91/02/01 14:43:13 bostic 9 8
c need a semi-colon before the done
e
s 00011/00001/00058
d D 5.8 90/06/22 19:05:23 bostic 8 7
c checkpoint .mk files
e
s 00013/00010/00046
d D 5.7 90/05/10 20:23:02 bostic 7 6
c do install right
e
s 00002/00000/00054
d D 5.6 90/05/10 17:23:10 bostic 6 5
c add sccs id
e
s 00012/00014/00042
d D 5.5 90/05/10 17:16:55 bostic 5 4
c cleanup, doesn't need bsd.global.mk
e
s 00037/00024/00019
d D 5.4 90/05/08 13:42:48 bostic 4 3
c checkpoint, the world rebuilds
e
s 00005/00005/00038
d D 5.3 90/03/17 15:16:46 bostic 3 2
c fixes for object directories (add CURDIR)
e
s 00001/00001/00042
d D 5.2 90/03/16 12:01:46 bostic 2 1
c alphabetical order
e
s 00043/00000/00000
d D 5.1 90/03/16 08:48:31 bostic 1 0
c date and time created 90/03/16 08:48:31 by bostic
e
u
U
t
T
I 6
#	%W% (Berkeley) %G%

E 6
I 1
D 4
# A Makefile for handling subdirectories.
# Machine dependent subdirectories take precedence.
#
#	%W% (Berkeley) %G%
#
E 4
I 4
D 5
.include <bsd.global.mk>
E 4

E 5
D 4
# user defines:
#	SUBDIR -- the list of subdirectories to be processed

# the default target.
E 4
.MAIN: all

I 8
STRIP?=	-s

BINGRP?=	bin
BINOWN?=	bin
BINMODE?=	555

E 8
D 4
# The standard targets change to the subdirectory and make the
# target.
E 4
D 5
STDALL STDDEPEND STDCLEAN STDCLEANDIR STDLINT STDINSTALL STDTAGS: .USE
E 5
I 5
_SUBDIRUSE: .USE
E 5
	@for entry in ${SUBDIR}; do \
D 4
		(echo "===> $$entry"; \
D 3
		if test -d $${entry}.${MACHINE}; then \
			cd $${entry}.${MACHINE}; \
E 3
I 3
		if test -d ${.CURDIR}/$${entry}.${MACHINE}; then \
E 4
I 4
		(if test -d ${.CURDIR}/$${entry}.${MACHINE}; then \
			echo "===> $${entry}.${MACHINE}"; \
E 4
			cd ${.CURDIR}/$${entry}.${MACHINE}; \
E 3
		else \
I 4
			echo "===> $$entry"; \
E 4
D 3
			cd $${entry}; \
E 3
I 3
			cd ${.CURDIR}/$${entry}; \
E 3
		fi; \
D 7
		${MAKE} ${.TARGET}) \
E 7
I 7
D 9
		${MAKE} ${.TARGET:realinstall=install}) \
E 9
I 9
		${MAKE} ${.TARGET:realinstall=install}); \
E 9
E 7
	done

D 4
# If the user has not specified the target, use the standard version.
E 4
I 4
D 5
${SUBDIR}::
E 5
I 5
D 8
${SUBDIR}:
E 8
I 8
${SUBDIR}::
E 8
E 5
	@if test -d ${.TARGET}.${MACHINE}; then \
		cd ${.CURDIR}/${.TARGET}.${MACHINE}; \
	else \
		cd ${.CURDIR}/${.TARGET}; \
	fi; \
	${MAKE} all

.if !target(all)
E 4
D 5
all: STDALL
E 5
I 5
all: _SUBDIRUSE
E 5
I 4
.endif

.if !target(clean)
E 4
D 2
depend: STDDEPEND
E 2
D 5
clean: STDCLEAN
E 5
I 5
clean: _SUBDIRUSE
E 5
I 4
.endif

.if !target(cleandir)
E 4
D 5
cleandir: STDCLEANDIR
E 5
I 5
cleandir: _SUBDIRUSE
E 5
I 4
.endif

.if !target(depend)
E 4
I 2
D 5
depend: STDDEPEND
E 5
I 5
depend: _SUBDIRUSE
E 5
I 4
.endif

I 10
.if !target(manpages)
manpages: _SUBDIRUSE
.endif

E 10
I 7
.if !target(install)
.if !target(beforeinstall)
beforeinstall:
.endif
.if !target(afterinstall)
afterinstall:
.endif
install: afterinstall
afterinstall: realinstall
realinstall: beforeinstall _SUBDIRUSE
.endif
I 10
.if !target(maninstall)
maninstall: _SUBDIRUSE
.endif
E 10

E 7
.if !target(lint)
E 4
E 2
D 5
lint: STDLINT
E 5
I 5
lint: _SUBDIRUSE
I 8
.endif

.if !target(obj)
obj: _SUBDIRUSE
I 10
.endif

.if !target(objdir)
objdir: _SUBDIRUSE
E 10
E 8
E 5
D 4
install: STDINSTALL
E 4
I 4
.endif

.if !target(tags)
E 4
D 5
tags: STDTAGS
E 5
I 5
tags: _SUBDIRUSE
E 5
I 4
D 7
.endif
E 4

D 4
# If trying to make one of the subdirectories, change to it and make
# the default target.
${SUBDIR}:
	@if test -d ${.TARGET}.${MACHINE}; then \
D 3
		cd ${.TARGET}.${MACHINE}; \
E 3
I 3
		cd ${.CURDIR}/${.TARGET}.${MACHINE}; \
E 3
	else \
D 3
		cd ${.TARGET}; \
E 3
I 3
		cd ${.CURDIR}/${.TARGET}; \
E 3
	fi; \
	${MAKE}
E 4
I 4
.if !target(install)
.if target(beforeinstall)
D 5
install: beforeinstall
install: STDINSTALL
.else
install: STDINSTALL
E 5
I 5
beforeinstall:
E 5
.endif
I 5
realinstall: _SUBDIRUSE
install: afterinstall
afterinall: realinstall
E 7
E 5
.endif
E 4
E 1
