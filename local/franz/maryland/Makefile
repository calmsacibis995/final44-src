#	Makefile for /usr/lib/lisp
# this directory contains the lisp coded portion of the standard 
# lisp system and other useful lisp programs. 
# The command 'make all' insures that all source files are compiled
# The command 'make install' installs these files in the standard
# place (/usr/lib/lisp).  This is only useful of course if the current
# directory is not /usr/lib/lisp.
#
# Updated to include uom files - liz 10/5/82
#
#--- Default paths and programs:
LibDir = /g/liz/uomlisp/lib
CopyTo = /dev/null
Liszt = liszt 

#--- ReqSrc: required source for building lisp system
# Last two lines are uom lisp files
#
UMReqSrc = tlev-uom.l uommacs.l uomfuncs.l nlispx.l lispbreak.l \
	new-load.l flavors.l vanilla.l gwd.c ldefs.h load-liszt

ReqSrc = charmac.l common0.l common1.l common2.l \
	syntax.l  macros.l  vector.l array.l pp.l  version.l \
	${UMReqSrc}

#--- OtherSrc: other lisp coded library files
OtherSrc = machacks.l loop.l ucifnc.l  ucido.l jkfmacs.l trace.l syscall.l\
	cmumacs.l cmufncs.l fix.l step.l cmufile.l cmutpl.l cmuedit.l \
	structinit.l struct.l prof.l yaps.l

#--- UtilSrc: source for utility programs
UtilSrc =  tackon.c

UMReqObj = tlev-uom.o uommacs.o uomfuncs.o nlispx.o lispbreak.o \
	new-load.o flavors.o vanilla.o gwd.o

ReqObj = charmac.o common0.o common1.o common2.o \
	syntax.o  macros.o  vector.o array.o pp.o version.o \
	${UMReqObj}

OtherObj = machacks.o loop.o ucifnc.o  ucido.o jkfmacs.o trace.o syscall.o\
	cmumacs.o cmufncs.o fix.o step.o cmufile.o cmutpl.o cmuedit.o \
	structinit.o struct.o prof.o yaps.o

UtilObj = tackon

#--- AllSrc: all source files required for lisp system
AllSrc = Makefile ReadMe buildlisp.l cmuenv.l ${ReqSrc} ${OtherSrc} ${UtilSrc}

AllObj = ${ReqObj} ${OtherObj} ${UtilObj}
    
all: ${AllObj}

required: ${ReqObj} ${UtilObj}
	@echo "*** Required Objects Done ***"

uomrequired: ${UMReqObj}

nlispx.o lispbreak.o new-load.o flavors.o uomfuncs.o: uommacs.o

new-load.o: gwd.o

.SUFFIXES: .l

.l.o:
	${Liszt}  -q $* 

machacks.o: machacks.l
	${Liszt} -q machacks 

loop.o: loop.l
	${Liszt} -mq loop  

structinit.o: structinit.l
	${Liszt} -mq structinit 

struct.o: struct.l
	${Liszt} -mq struct  
${AllSrc}:
	sccs get $@

# How to compile special Maryland things

# vanilla.o really depends on there being .o's for all of the stuff
# that's loaded in, but since it hardly ever needs to be remade, I'm
# not including those dependencies.
vanilla.o: vanilla.l
	echo "(progn (setq lisp-library-directory '${LibDir}) \
		     (load 'flavors) \
		     (load 'uommacs) \
		     (load 'uomfuncs) \
		     (load 'new-load) \
		     (load1 'vanilla.l) \
		     (compile 'vanilla '-q '-nf) \
		      nil)" \
	     | ${Liszt}
	-rm -f vanilla.ctmp

# If you're using a liszt that doesn't contain the objects in the
# second make, use the second make.
yaps.o: yaps.l
	echo "(progn (load1 'yaps.l) (compile 'yaps '-q '-nf) nil)" \
	     | ${Liszt}
	-rm -f yaps.ctmp

# yaps.o: yaps.l flavors.o uommacs.o uomfuncs.o new-load.o
#	echo "(progn (load 'flavors) \
#		     (load 'uommacs) \
#		     (load 'uomfuncs) \
#		     (load 'new-load) \
#		     (load1 'yaps.l) \
#		     (compile 'yaps '-q '-nf '-x) \
#		      nil)" \
#	     | ${Liszt}
#	-rm -f yaps.ctmp

gwd.o: gwd.c
	cc -c gwd.c

sources: ${AllSrc}

xref:
	lxref ${AllSrc} > xref

tackon: tackon.c
	cc -O -o tackon tackon.c

echofiles:
	@echo ${ReqSrc} ${OtherSrc}

echorequired:
	@echo ${ReqSrc}
	
copysource: ${AllSrc}
	(tar cf - ${AllSrc} | (cd ${CopyTo} ; tar xf -))

copyobjects: ${AllObj}
	(tar cf - ${AllObj} | (cd ${CopyTo} ; tar xf -))

scriptcatall: ${AllSrc}
	@(X=`pwd` ; cd ${CdTo} ; scriptcat $$X lib ${AllSrc})

as:
	@echo "Grabbing as from /bin"
	cp /bin/as as

nld:
	@echo "Grabbing nld from /bin"
	cp /bin/ld nld

clean: 
	-rm -f *.o 
	-rm -f *.blat 
	-rm -f *.x
