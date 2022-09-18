#
#	 %I%	(CWI)	%E%
#
# all this jazz needs to be cleaned up
#
LIBDIR = /usr/local/lib/ditroff/font/devver
MSOURCE = ../../utilities/makedev.c
FONTS = DESC CW ap bb bi bk br cb ch ci cl co cr cy db di dr \
	gb gf gi gk gr hb hn m mb mi mn mr ob oe oi or \
	pb pp sb sc sg sh si sl sr tB tI tR tS tb ti tr ts \
	R B I nr nb ni S

all: Makedev made.fonts

install:	all
	for i in ${FONTS}; do\
	install -c -m 644 $$i.out ${DESTDIR}${LIBDIR}/$$i.out; done


Makedev:	Makedev.c
	cc ${CFLAGS} -o Makedev Makedev.c

#
# create a special version of Makedev so dver will work properly
#
Makedev.c:	${MSOURCE}
	cat ${MSOURCE} | sed -e 's/\/dev.h/\/..&/' -e 's/#define.NFONT.*/#define	NFONT 65/' > Makedev.c

made.fonts:	${FONTS}
	./Makedev DESC CW ap bb bi bk br cb ch ci cl co cr cy db di dr gb gf gi gk gr hb hn m mb mi mn mr ob oe oi or pb pp sb sc sg sh si sl sr tB tI tR tS tb ti tr ts
	touch made.fonts

clean:
	rm -f *.out Makedev made.fonts
