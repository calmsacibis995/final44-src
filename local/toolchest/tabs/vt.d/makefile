# CFLAGS=-O -DSDIR=\"/usr/lib/emacs
# CFLAGS=-O -DTERMCAP
CFLAGS=-O -DVT_TERMINFO

OBJS=	beep.o cflush.o clear.o clrl.o cook.o \
	cpy_ret.o ctype.o dcost.o delc.o die.o \
	eprintf.o insrtc.o ioctl_hack.o lshift.o mgetchar.o \
	mgo.o nscan.o puts.o refresh.o rshift.o \
	sgo.o sputc.o sscroll.o sttype.o sxprintf.o \
	ttystart.o uncook.o unsert.o vadjust.o vputch.o \
	vshift.o vt.o xgo.o xprintf.o xputl.o


LOBJS=	beep.o clear.o delc.o insrtc.o mgetchar.o \
	puts.o refresh.o sputc.o sscroll.o sxprintf.o \
	cpy_ret.o nscan.o ttystart.o sttype.o dcost.o \
	die.o cook.o uncook.o ioctl_hack.o vadjust.o \
	mgo.o vshift.o xgo.o xprintf.o xputl.o \
	cflush.o clrl.o ctype.o lshift.o rshift.o \
	sgo.o unsert.o eprintf.o vputch.o vt.o


libvt.a: ${OBJS}
	-rm -f libvt.a
	ar q libvt.a ${LOBJS}


clean:
	-rm -f *.o *.output TERMCAP


lint:
	-lint ${CFLAGS} $(OBJS:.o=.c)


print:
	-lprint makefile *.c *.h


cpio:
	-find . -cpio /dev/rmt0


lorder:
	-lorder ${OBJS} | tsort | while read line1; \
	do \
		read line2; \
		read line3; \
		read line4; \
		read line5; \
		line="$$line1 $$line2 $$line3 $$line4 $$line5"; \
		echo "	$$line \\"; \
	done > lorder.output


objs:
	-echo ${OBJS} | tr " " "\012" | sort | while read line1; \
	do \
		read line2; \
		read line3; \
		read line4; \
		read line5; \
		line="$$line1 $$line2 $$line3 $$line4 $$line5"; \
		echo "	$$line \\"; \
	done > objs.output

ttest:	ttest.o libvt.a
	cc -o ttest ttest.o libvt.a -lcurses

TERMCAP: ${LOBJS} termlib.d/termcap.o termlib.d/tgoto.o termlib.d/tputs.o
	@ echo Did you do a "make clean" and recompile with -DTERMCAP?
	cd termlib.d;make
	-rm -f libvt.a
	ar q libvt.a ${LOBJS} \
		termlib.d/termcap.o termlib.d/tgoto.o termlib.d/tputs.o
	touch TERMCAP
