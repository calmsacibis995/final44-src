#
#	%M%	(CWI)	%I%	%E%
#
DESTDIR=
LIBDIR= /usr/local/lib/ditroff/font/devnver
SOURCEFONTS = ../../devhar/fonts/R ../../devhar/fonts/I ../../devhar/fonts/B \
	../../devhar/fonts/BI ../../devhar/fonts/Vl ../../devhar/fonts/vl \
	../../devhar/fonts/V ../../devhar/fonts/v ../../devhar/fonts/S \
	../../devhar/fonts/Sm ../../devhar/fonts/Bs ../../devhar/fonts/G3 \
	../../devhar/fonts/RS ../../devhar/fonts/Rs ../../devhar/fonts/SO \
	../../devhar/fonts/Vm ../../devhar/fonts/bI ../../devhar/fonts/bS \
	../../devhar/fonts/bb ../../devhar/fonts/bi ../../devhar/fonts/br \
	../../devhar/fonts/bs ../../devhar/fonts/cI ../../devhar/fonts/cb \
	../../devhar/fonts/ci ../../devhar/fonts/cr ../../devhar/fonts/fs \
	../../devhar/fonts/lI ../../devhar/fonts/lb ../../devhar/fonts/li \
	../../devhar/fonts/lp ../../devhar/fonts/lr ../../devhar/fonts/vm \
	../../devhar/fonts/sR ../../devhar/fonts/TR
STANDARDFONTS = R I B BI Vl vl V v S Sm
EXTRAFONTS = Bs G3 RS Rs SO Vm bI bS bb bi br bs cI cb ci cr fs lI lb li lp lr\
	vm sR TR
FONTFILES = B.out BI.out Bs.out DESC.out G3.out I.out R.out RS.out Rs.out\
	S.out SO.out Sm.out V.out Vl.out Vm.out bI.out bS.out bb.out bi.out\
	br.out bs.out cI.out cb.out ci.out cr.out fs.out lI.out lb.out li.out\
	lp.out lr.out v.out vl.out vm.out sR.out TR.out

all:	binaryfonts ../../utilities/makedev

sourcefonts: ${SOURCEFONTS} sourcefonts
	rm -rf ${STANDARDFONTS} ${EXTRAFONTS}
	for i in ${SOURCEFONTS}; do\
		ln $$i `basename $$i`;	done
	touch sourcefonts

DESC:	../../devhar/fonts/DESC sed.script
	sed.script > DESC

binaryfonts:	DESC sourcefonts ${STANDARDFONTS} ${EXTRAFONTS}
	../../utilities/makedev DESC ${EXTRAFONTS}
	touch binaryfonts
	-if test -f MadeMakedev; then rm MadeMakedev ../../utilities/makedev; fi

install:	all
	for i in ${FONTFILES}; do\
	install -c -m 644 $$i ${DESTDIR}${LIBDIR}/$$i; done

../../utilities/makedev:
	cd ../../utilities; make makedev
	touch MadeMakedev

cmp:	all
	@echo Comparing ...
	@-for i in ${FONTFILES}; do\
	cmp $$i ${DESTDIR}${LIBDIR}/$$i; done

print:
	print DESC ${STANDARDFONTS} ${EXTRAFONTS}

clean:
	rm -f *.out binaryfonts sourcefonts ${STANDARDFONTS} ${EXTRAFONTS} DESC
