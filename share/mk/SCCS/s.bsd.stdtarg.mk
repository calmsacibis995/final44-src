h41502
s 00029/00000/00000
d D 5.1 90/05/10 17:11:55 bostic 1 0
c date and time created 90/05/10 17:11:55 by bostic
e
u
U
t
T
I 1
.if !target(clean)
clean: STDCLEAN
.endif

.if !target(cleandir)
cleandir: STDCLEANDIR
.endif

.if !target(depend)
depend: .depend
.depend: STDDEPEND
.endif

.if !target(lint)
lint: ${SRCS} STDLINT
.endif

.if !target(tags)
tags: ${SRCS} STDTAGS
.endif

.if !target(install)
.if target(beforeinstall)
install: beforeinstall
install: STDINSTALL mainstall
.else
install: STDINSTALL mainstall
.endif
.endif
E 1
