#	@(#)Makefile	5.16 (Berkeley) 4/26/91

PROG=	routed
SRCS=	af.c if.c input.c main.c output.c startup.c tables.c timer.c \
	trace.c inet.c
MAN8=	routed.0
SUBDIR=	query trace
DPADD=	${LIBUTIL} ${LIBCOMPAT}
LDADD=	-lutil -lcompat

.include <bsd.prog.mk>

