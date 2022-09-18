h39084
s 00003/00004/00246
d D 6.4 88/06/08 12:54:40 karels 4 3
c mkdir libdir/manual; don't fork so many times
e
s 00018/00016/00232
d D 6.3 86/05/14 16:23:15 bloom 3 2
c split macro package
e
s 00035/00009/00213
d D 6.2 86/05/14 16:01:16 bloom 2 1
c add our lines for typesetting
e
s 00222/00000/00000
d D 6.1 86/04/29 19:55:38 cuccia 1 0
c date and time created 86/04/29 19:55:38 by cuccia
e
u
U
t
T
I 1
#
# Copyright (c) 1986 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W% (Berkeley) %G%
#
# $Header: Makefile 1.4 83/07/21 21:27:16 sklower Exp $
#	makefile for the franz lisp manual
#
D 3
# sources: lmacs: macros for the franz documents
E 3
I 3
# sources: ${MacroSrc}: macros for the franz documents
#	   ${TMacSrc}: macros for typesetting franz documents
E 3
#	   ch1.n  intro and description of types
#	   ch2.n  data structure access
#	   ch3.n  on arithmetic functions.
#	   ch4.n  special functions.
#	   ch5.n  i/o
#	   ch6.n  system functions
#	   ch7.n  reader
#	   ch8.n  functions and macros 
#	   ch9.n  arrays 
#	   ch10.n exception handling 
#	   ch11.n trace package 
#	   ch12.n liszt 
#	   ch13.n cmu top level
#	   ch14.n stepper 
#	   ch15.n fixit package
#	   ch16.n lisp editor
I 2
#	   ch17.n hash tables
E 2
#	   chb.n special symbols
#	   chc.n  short subjects


.SUFFIXES: .n .t .x .v .r .rx .q .qx .sp

# the syntax's have this meaning:
#  .n  nroff/troff source file
#  .t  troff output file, can be vpr -t 'ed 
#  .x  index file from a troff run, when collected and run through troff
#	again, an index is produced.
#  .v  this file never exists, but asking for it will cause a .t file to
#	be created and then vpr'ed.  the .t file will not be deleted.
#  .p  this file also never exists, but asking for it will cause TROFF
#	(usually vtroff or itroff) to be run directly on the file, leaving
#	no .t around.  This is used in /usr/doc for people who want to
#	run off a manual and are too lazy to read this makefile.
#  .r  nroff output file.
#  .rx  special index output from nroff run.  These files should be catted
#       together and then left around for lisp to read when given the help
#	command.
#
#  .q  nroff output file compatible with model 37
#  .qx index file for .q files.
#
#  .sp spell errors
#
# make install will install the nroff versions of the manual in the
# directory (LibDir/manual) where the auxfns0.l help command can find them.
#
LibDir = /usr/lib/lisp
CcodeDir = ../franz
CopyTo = /dev/null
TROFF=	ditroff
TBL=	dtbl
NROFF=  nroff
D 2
O = -Pdp
E 2
I 2
PRINTER = -Pdp
O = 
E 2
Append = ${LibDir}/append
# Rmt = is unecessary; you can say, make rall NROFF="'dali nroff'".
# better to just copy the doc directory to the remote machine and
# run it all there.

#--- Sources: 
#	We use the suffixes to tell make how to make a file.  Thus
#  we only specify the root and let the append function add the
#  appropriate suffix.

MacroSrc = lmacs
I 3
TMacSrc = tmacs
E 3

RootGenSrc = ch0 ch1 ch2 ch3 ch4 ch5 ch6 ch61 ch7 ch8 \
      ch9 ch10 ch11 ch12 ch13 ch14 ch15 ch16 ch17 chb chc

I 2
DocSrc= ch0.n ch1.n ch2.n ch3.n ch4.n ch5.n ch6.n ch7.n ch8.n \
	ch9.n ch10.n ch11.n ch12.n ch13.n ch14.n ch15.n ch16.n ch17.n

DocApp= chb.n chc.n

E 2
UtilSrc = Makefile indexsed mantags extrnames.awk fixmks.sed \
	franz.n

#-- can't get a expression for all source at make read time. must use
#   append to add .n to RootGenSrc


I 2
doc: paper app

paper:	paper.${PRINTER}
	lpr ${PRINTER} -n paper.${PRINTER}

D 3
paper.${PRINTER}: ${DocSrc} ${MacroSrc}
	${TBL} ${PRINTER} ${MacroSrc} ${DocSrc} | \
E 3
I 3
paper.${PRINTER}: ${DocSrc} ${TMacSrc}
	${TBL} ${PRINTER} ${TMacSrc} ${DocSrc} | \
E 3
		${TROFF} -t -me 1> paper.${PRINTER} 2> tindex

app: app.${PRINTER}
	lpr ${PRINTER} -n app.${PRINTER}

D 3
app.${PRINTER}: tindex ${MacroSrc} ${DocApp}
E 3
I 3
app.${PRINTER}: tindex ${TMacSrc} ${DocApp}
E 3
	echo ".Ib" | sort +2 tindex - | sed -f indexsed | \
D 3
		${TROFF} -t -me ${MacroSrc} - ${DocApp} > app.${PRINTER}
E 3
I 3
		${TROFF} -t -me ${TMacSrc} - ${DocApp} > app.${PRINTER}
E 3

E 2
D 4
all:
D 2
	make vall
E 2
I 2
	make rall
E 4
I 4
all: rall
E 4
E 2

rall: ${Append}
	make NROFF=${NROFF} O=${O} `${Append} .r ${RootGenSrc}` helpindex

vall: ${Append}
	make TROFF=${TROFF} O=${O} `${Append} .v ${RootGenSrc}` index.v

tall: ${Append}
	make TROFF=${TROFF} O=${O} `${Append} .t ${RootGenSrc}` index.t

cctall:
	make TROFF="troff -s12" tall

pall: ${Append}
	make TROFF=${TROFF} O=${O} `${Append} .p ${RootGenSrc}` pindex

troff: pall
      
qall: ${Append}
	make NROFF=${NROFF} O=${O} `${Append} .q ${RootGenSrc}` index.t

spall: ${Append}
	make TROFF=${TROFF} O=${O} `${Append} .q ${RootGenSrc}` index.t

# only a few files describe functions which are indexed.

.t.v:
D 2
	pr ${O} -t $*.t
E 2
I 2
	lpr ${PRINTER} -n $*.t
E 2

.n.t:	
D 2
	${TBL} ${O} lmacs $*.n | ${TROFF} -me ${O} -t 1> $*.t 2> $*.x
E 2
I 2
D 3
	${TBL} ${PRINTER} lmacs $*.n | \
E 3
I 3
	${TBL} ${PRINTER} ${MacroSrc} $*.n | \
E 3
		${TROFF} -me ${O} ${PRINTER} -t 1> $*.t 2> $*.x
E 2

.n.p:
D 2
	${TBL} ${O} lmacs $*.n | ${TROFF} -me ${O} 2> $*.x
E 2
I 2
D 3
	${TBL} ${PRINTER} lmacs $*.n | ${TROFF} -me ${O} ${PRINTER} 2> $*.x
E 3
I 3
	${TBL} ${PRINTER} ${MacroSrc} $*.n | ${TROFF} -me ${O} ${PRINTER} 2> $*.x
E 3
E 2

.n.x:
D 2
	${TBL} ${O} lmacs $*.n | ${TROFF} -me -z 2> $*.x
E 2
I 2
D 3
	${TBL} ${PRINTER} lmacs $*.n | ${TROFF} -me ${O} ${PRINTER} -z 2> $*.x
E 3
I 3
	${TBL} ${PRINTER} ${MacroSrc} $*.n | ${TROFF} -me ${O} ${PRINTER} -z 2> $*.x
E 3
E 2

.n.r:
D 2
	${TBL} ${O} lmacs $*.n | ${NROFF} -rb3 -me ${O} 1> $*.r 2> $*.rx
E 2
I 2
D 3
	tbl lmacs $*.n | ${NROFF} -rb3 -me ${O} 1> $*.r 2> $*.rx
E 3
I 3
	tbl ${MacroSrc} $*.n | ${NROFF} -rb3 -me ${O} 1> $*.r 2> $*.rx
E 3
E 2
	rm -f helpindex

.n.rx:
D 2
	${TBL} ${O} lmacs $*.n | ${NROFF} -rb3 -me 1> $*.r 2> $*.rx
E 2
I 2
D 3
	tbl lmacs $*.n | ${NROFF} -rb3 -me ${O} 1> $*.r 2> $*.rx
E 3
I 3
	tbl ${MacroSrc} $*.n | ${NROFF} -rb3 -me ${O} 1> $*.r 2> $*.rx
E 3
E 2
	rm -f helpindex

.n.q:
D 2
	${TBL} ${O} lmacs $*.n | ${NROFF} -me -T37 2> $*.qx | col > $*.q
E 2
I 2
D 3
	tbl lmacs $*.n | ${NROFF} -me -T37 ${O} 2> $*.qx | col > $*.q
E 3
I 3
	tbl ${MacroSrc} $*.n | ${NROFF} -me -T37 ${O} 2> $*.qx | col > $*.q
E 3
E 2

.n.sp:
	spell $*.n > $*.sp
	
D 4
install: 
	make O=${O} rall
E 4
I 4
install: rall
	-mkdir ${LibDir}/manual
E 4
	cp `${Append} .r ${RootGenSrc}` helpindex ${LibDir}/manual

clean:
I 2
	-rm -f paper.-[PT]* app.-[PT]* errs Errs make.out
E 2
	-rm -f *.r 
	-rm -f *.rx 
	-rm -f helpindex 
I 2
	-rm -f tindex 
E 2
	-rm -f *.t 
	-rm -f *.q 
	-rm -f *.x


findex:  ${Append}
	make `${Append} .x ${RootGenSrc}`
	echo ".Ib" > index
	sort +3 -o index index `${Append} .x ${RootGenSrc}`
	sed -f indexsed index > indexx 
D 3
	${Rmt} ${TROFF} -me lmacs indexx
E 3
I 3
	${Rmt} ${TROFF} -me ${MacroSrc} indexx
E 3

index.t: 
	make `${Append} .x ${RootGenSrc}`
	echo ".Ib" > index
	sort +3 -o index index `${Append} .x ${RootGenSrc}`
	sed -f indexsed index > indexx
D 3
	${TROFF} -me -x -t lmacs indexx > index.t
E 3
I 3
	${TROFF} -me -x -t ${MacroSrc} indexx > index.t
E 3

pindex: ${Append}
	make `${Append} .x ${RootGenSrc}`
	echo ".Ib" > index
	sort +3 -o index index `${Append} .x ${RootGenSrc}`
	sed -f indexsed index > indexx
D 3
	${TROFF} -me lmacs indexx
E 3
I 3
	${TROFF} -me ${MacroSrc} indexx
E 3

helpindex: ${Append}
	make `${Append} .rx ${RootGenSrc}`
	cat `${Append} .rx ${RootGenSrc}` | tr '\227' ' ' > helpindex

tags:	/dev/tty ${Append}
	awk -f mantags `${Append} .n ${RootGenSrc}` | sort > tags


${Append}: 
	(cd ../utils  ; make LibDir=${LibDir} ${Append})

# to create a database for lxref to use:
C-database: ${CcodeDir}/sysat.c
	grep "^	MK" ${CcodeDir}/sysat.c > mks
	sed -f fixmks.sed < mks > mks.fixed
	(echo "(Chome)" ; cat mks.fixed ) > C-database
	rm -f mks mks.fixed

doc-database: 
	awk -f extrnames.awk `${Append} .n ${RootGenSrc}`\
 	   | sed -f fixmks.sed > doc-database


bigxref: C-database doc-database
	${Append} -p ${LibDir}/ `(cd ${LibDir} ; make echorequired)` | \
		sed 's/\.l/.x/g' > lisplibfiles
	lxref doc-database  C-database  `cat lisplibfiles` > bigxref

# simple table of contents, just a listing of which function is
# documented in which chapter
tofc:  
	egrep "^.Lc|^.Lf|^.Lx|^.sh" `${Append} .n  ${RootGenSrc}` > tofc


copysource:
D 3
	(tar cf - ${MacroSrc} `${Append} .n ${RootGenSrc}` ${UtilSrc} | \
	 (cd ${CopyTo} ; tar xf -))
E 3
I 3
	(tar cf - ${MacroSrc} ${TMacSrc} `${Append} .n ${RootGenSrc}` \
		${UtilSrc} | (cd ${CopyTo} ; tar xf -))
E 3

scriptcatall: ${AllSrc} ${Append}
	@(cd .. ; scriptcat doc doc ${MacroSrc} `${Append} .n ${RootGenSrc}` ${UtilSrc})
	@(cd .. ; scriptcat doc lisplib/manual \
	      `${Append} .r ${RootGenSrc}` helpindex)

copymanual: ${Append}
	( cd ${FromDir}/manual ; \
	  cp `${Append} .r ${RootGenSrc}` helpindex ${CopyTo})


E 1
