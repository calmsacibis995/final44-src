h04217
s 00004/00001/00037
d D 1.4 88/03/04 17:08:32 jaap 4 3
c cleaning up
e
s 00009/00004/00029
d D 1.3 87/03/31 23:54:21 jaap 3 2
c Just checking in
e
s 00006/00002/00027
d D 1.2 85/02/01 00:42:13 jaap 2 1
c added entry for font sR for Han Noot
e
s 00029/00000/00000
d D 1.1 85/01/22 13:19:03 jaap 1 0
c date and time created 85/01/22 13:19:03 by jaap
e
u
U
t
T
I 1
#
#	%M%	(CWI)	%I%	%E%
#
DESTDIR=
D 3
LIBDIR= /usr/lib/ditroff/font/devhar
E 3
I 3
LIBDIR= /usr/local/lib/ditroff/font/devhar
E 3
STANDARDFONTS = R I B BI Vl vl V v S Sm
D 2
EXTRAFONTS = Bs G3 RS Rs SO Vm bI bS bb bi br bs cI cb ci cr fs lI lb li lp lr vm
E 2
I 2
EXTRAFONTS = Bs G3 RS Rs SO Vm bI bS bb bi br bs cI cb ci cr fs lI lb li lp lr\
D 3
	vm sR
E 3
I 3
	vm sR TR
E 3
E 2
FONTFILES = B.out BI.out Bs.out DESC.out G3.out I.out R.out RS.out Rs.out\
	S.out SO.out Sm.out V.out Vl.out Vm.out bI.out bS.out bb.out bi.out\
	br.out bs.out cI.out cb.out ci.out cr.out fs.out lI.out lb.out li.out\
D 2
	lp.out lr.out v.out vl.out vm.out
E 2
I 2
D 3
	lp.out lr.out v.out vl.out vm.out sR.out
E 3
I 3
	lp.out lr.out v.out vl.out vm.out sR.out TR.out
E 3
E 2

D 3
all:	binaryfonts ${FONTFILES}
E 3
I 3
all:	../../utilities/makedev binaryfonts 
E 3

I 4
$(LIBDIR):
	mkdir $(LIBDIR)

E 4
binaryfonts:	DESC ${STANDARDFONTS} ${EXTRAFONTS}
	../../utilities/makedev DESC ${EXTRAFONTS}
	touch binaryfonts
	-if test -f MadeMakedev; then rm MadeMakedev ../../utilities/makedev; fi

D 4
install:	all
E 4
I 4
install:	all $(LIBDIR)
E 4
	for i in ${FONTFILES}; do\
	install -c -m 644 $$i ${DESTDIR}${LIBDIR}/$$i; done

../../utilities/makedev:
	cd ../../utilities; make makedev
	touch MadeMakedev
I 3

cmp:	all
	@echo Comparing ...
	@-for i in ${FONTFILES}; do\
	cmp $$i ${DESTDIR}${LIBDIR}/$$i; done
E 3
I 2

print:
	print DESC ${STANDARDFONTS} ${EXTRAFONTS}
E 2

clean:
	rm -f *.out binaryfonts
E 1
