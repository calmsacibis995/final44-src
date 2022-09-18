LibDir = /usr/lib/lisp/portable
D = /tmp
HOLE=	2097152 #if you change this you must recompile rlc.c

GenSrc = low.c lowaux.s lisp.c eval.c eval2.c inits.c io.c error.c sysat.c \
	lam1.c lam2.c lam3.c lam4.c lam5.c lam6.c lam7.c lam8.c lam9.c lamr.c \
	fex1.c fex2.c fex3.c fex4.c fexr.c\
	fpipe.c bigmath.c\
	subbig.c pbignum.c divbig.c inewint.s ffasl.c  fasl.c vsyscall.s\
	qfuncl.c trace.c evalf.c frame.c lamgc.c vax.c alloc.c data.c

GenObj = low.o lowaux.o lisp.o eval.o eval2.o inits.o io.o error.o sysat.o \
	lam1.o lam2.o lam3.o lam4.o lam5.o lam6.o lam7.o lam8.o lam9.o lamr.o \
	fex1.o fex2.o fex3.o fex4.o fexr.o\
	fpipe.o bigmath.o\
	subbig.o pbignum.o divbig.o inewint.o ffasl.o  fasl.o vsyscall.o\
	qfuncl.o trace.o evalf.o frame.o   lamgc.o vax.o

Includes = h/config.h 	h/global.h 	h/oaout.h 	h/vaxframe.h \
	h/catchfram.h 	h/dfuncs.h 	h/gtabs.h 	h/sigtab.h \
	h/chars.h 	h/frame.h 	h/lfuncs.h 	h/structs.h \
	h/chkrtab.h 	h/gc.h 		h/naout.h 	h/types.h \
	h/lconf.h	h/ltypes.h

# utilities
#
UtilSrc = fixpbig.e
UtilObj = 

ProfFlag = # -XP
ProfFlag2 = # -DPROF

ForVMS = # -DVMS

NoProfSrc = lamnop.c dmcount.s
NoProfObj = lamnop.o dmcount.o

ProfSrc = lamp.c mcount.s mon.c
ProfObj = lamp.o mcount.o mon.o

TStartupSrc = crt0.s
TStartupObj = crt0.o

TXtraSrc =
TXtraObj = alloc.o data.o

TSrc = ${GenSrc} ${TStartupSrc} ${TXtraSrc} ${NoProfSrc} ${Includes}
TObj = ${GenObj} ${TStartupObj} ${TXtraObj} ${NoProfObj}

HStartupSrc = hcrt0.s
HStartupObj = hcrt0.o

HXtraSrc = rlc.c 
HXtraObj = rlc.o Salloc.o Sdata.o

HSrc = ${GenSrc} ${HStartupSrc} ${HXtraSrc} ${NoProfSrc} ${Includes}
HObj = ${GenObj} ${HStartupObj} ${HXtraObj} ${NoProfObj}

AllSrc = Makefile ChangeLog ${GenSrc} ${TStartupSrc} ${HStartupSrc}\
	${TXtraSrc} ${HXtraSrc} ${NoProfSrc} ${ProfSrc} ${Includes} ${UtilSrc}

TagSrc = ${GenSrc} ${TStartupSrc} ${HStartupSrc}\
	${TXtraSrc} ${HXtraSrc} ${NoProfSrc} ${ProfSrc} ${Includes} ${UtilSrc}

AllObj = ${GenObj} ${TStartupObj} ${HStartupObj}  ${TXtraObj} ${HXtraObj}\
	 ${NoProfObj} ${ProfObj} ${UtilObj}

AllFiles = ${AllSrc} ${AllObj}

CFLAGS = -O -Ih -DPORTABLE # -p -g


.SUFFIXES : .c.l
.c.o :
	@csh -cfe "echo $*.c;\
	rm -f $*.o;\
	/lib/cpp $< -Ih -DPORTABLE ${ForVMS} |\
	/lib/ccom ${ProfFlag} |\
	sed -f fixpbig.e |\
	/lib/c2 > $D/$*.s;\
	as -o $*.o $D/$*.s;\
	rm $D/$*.s"

.l.o :
	liszt $< > #resc
	@echo liszt $< done

qfuncl.o: qfuncl.c
	cc -DPORTABLE -Ih -E ${ProfFlag2} qfuncl.c | as -o qfuncl.o

bigmath.o: bigmath.c
	cc -DPORTABLE -Ih -E ${ProfFlag2} bigmath.c | as -o bigmath.o

tlisp:  ${TSrc} fixpbig.e ${TObj} 
	rm -f tlisp
	ld -x -o tlisp -e start ${TObj} -lm -lc -ltermlib
	ls -l tlisp

vlisp:  ${USOURCES} ${TOBJS} 
	rm -f vlisp
	ld -x -o vlisp -e start ${TOBJS} -lm -lc -ltermlib
	ls -l vlisp

hlisp:  ${HSrc} fixpbig.e ${HObj} 
	rm -f hlisp
	ld -x -H $(HOLE) -o hlisp -e hstart ${HObj} -lm -lc -ltermlib
	ls -l hlisp

data.o: h/sigtab.h

rlc.o: rlc.c 
	cc -DPORTABLE -c -O -DHOLE=${HOLE} rlc.c

low.o: low.c
	cc -DPORTABLE -Ih -R -c low.c

Salloc.o: alloc.c
	(echo "# define HOLE"; cat alloc.c) > Zalloc.c ; make Zalloc.o;\
	rm Zalloc.c; mv Zalloc.o Salloc.o
	
Sdata.o: data.c
	(echo "# define HOLE"; cat data.c) > Zdata.c ; make Zdata.o;\
	rm Zdata.c; mv Zdata.o Sdata.o

clean:
	rm -f *.o

mylisp: tlisp ${LibDir}
	rm -f mylisp
	(cd ${LibDir} ; make)
	echo "(progn (setq build:map 'map\
			   build:lisp-type 'franz\
		           lisp-library-directory '${LibDir}\
			   build:dir '${LibDir}\
			   lisp-object-directory '${ObjDir})\
		     (load '${LibDir}/buildlisp.l)\
	             (dumplisp mylisp))" | ./tlisp
	${LibDir}/tackon map mylisp
