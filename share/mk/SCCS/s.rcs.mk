h24943
s 00012/00000/00000
d D 5.1 90/03/23 08:19:53 bostic 1 0
c date and time created 90/03/23 08:19:53 by bostic
e
u
U
t
T
I 1
# for RCS
.SUFFIXES: .out .a .ln .o .c .F .f .e .r .y .l .s .cl .p .h \
	       .c,v .y,v .l,v .s,v .h,v .8 .7 .6 .5 .4 .3 .2 .1 .0

CI=		/usr/new/ci
CIFLAGS=

CO=		/usr/new/co
COFLAGS=

.c,v.c .y,v.y .l,v.l .s,v.s .h,v.h:
	${CO} ${COFLAGS} ${.IMPSRC} ${.TARGET}
E 1
