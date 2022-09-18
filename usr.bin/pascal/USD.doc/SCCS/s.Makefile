h36667
s 00003/00002/00121
d D 8.3 94/06/01 18:23:13 mckusick 10 9
c too hard to create program sources, so don't remove them
e
s 00021/00020/00102
d D 8.2 94/05/25 12:15:56 mckusick 9 8
c correct to make runnable
e
s 00000/00000/00122
d D 8.1 93/08/14 10:03:48 mckusick 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00031/00027/00091
d D 6.4 93/07/29 15:36:49 elan 7 5
c Made px, pi, pxp, and pix variables -- makes it easier.
e
s 00000/00000/00118
d R 8.1 93/06/08 18:09:40 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00116
d D 6.3 93/06/05 16:10:33 bostic 5 4
c new doc.mk; document numbering changes for 4.4BSD
e
s 00048/00036/00070
d D 6.2 90/06/30 15:02:33 bostic 4 3
c new doc makefiles
e
s 00036/00032/00070
d D 6.1 86/05/07 14:53:32 mckusick 3 2
c document distributed with 4.3BSD
e
s 00006/00000/00096
d D 5.1 86/05/07 14:53:04 mckusick 2 1
c document distributed with 4.2BSD
e
s 00096/00000/00000
d D 4.1 86/05/07 14:52:39 mckusick 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 1
D 4
#
# Copyright (c) 1980 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
E 4
#	%W% (Berkeley) %G%
D 4
#
# This makefile assumes that csh is running the figures
#
D 3
DEV = -x
E 3
I 3
PRINTER=Pdp
TROFF=	ditroff -${PRINTER}
TBL=	dtbl -${PRINTER}
LPR=	lpr -n -${PRINTER}
E 3
SEC = ?
FIGURES=\
	firstout firstobjout firstobjout2\
	bigger2.p bigger3.p bigout1 bigger6.p bigout2 bigout3 bigout4\
	primeout1 primeout2\
	digitsout synerrout synerr2out\
	mismout clashout sinout1 sinout2\
	exprout typequout primeout3\
	katout copydataout kat2out katscript xxxxqqqout xxxxqqqout2\
	primes primes-d\
	comments1.p commentsout
E 4
I 2
D 3
TROFF=	vtroff
E 3

E 2
D 3
puman: ${FIGURES}
	soelim puman${SEC}.n | tbl | csh -cf '/usr/ucb/vtroff -t ${DEV} >lpr'
	vpr -t lpr
E 3
I 3
D 4
manual: lpr.${PRINTER}
	${LPR} lpr.${PRINTER}
E 4
I 4
D 5
DIR=	ps1/04.pascal
E 5
I 5
DIR=	psd/07.pascal
E 5
SRCS=	puman0.n puman1.n puman2.n puman3.n puman4.n puman5.n pumanA.n
FIGURES=firstout firstobjout firstobjout2 bigger2.p bigger3.p bigout1 \
	bigger6.p bigout2 bigout3 bigout4 primeout1 primeout2 digitsout \
	synerrout synerr2out mismout clashout sinout1 sinout2 exprout \
	typequout primeout3 katout copydataout kat2out katscript \
	xxxxqqqout xxxxqqqout2 primes primes-d comments1.p commentsout
D 10
CLEANFILES+=csfix ${FIGURES}
E 10
I 10
#CLEANFILES+=csfix ${FIGURES}
E 10
I 7
D 9
PXP=/usr/src/usr.bin/pascal/pxp/pxp
PI=/usr/src/usr.bin/pascal/pi/pi
PX=/usr/src/usr.bin/pascal/px/px
PIX=/usr/src/usr.bin/pascal/pix/pix
E 9
I 9
MACROS= -ms
PXP=/usr/src/usr.bin/pascal/pxp/obj/pxp
PI=/usr/src/usr.bin/pascal/pi/obj/pi
PX=/usr/src/usr.bin/pascal/px/obj/px
PIX=/usr/src/usr.bin/pascal/pix/obj/pix
E 9
E 7
E 4
E 3
I 2

I 3
D 4
lpr.${PRINTER}: ${FIGURES}
	soelim puman${SEC}.n | ${TBL} | csh -cf '${TROFF} -t >lpr.${PRINTER}'
E 4
I 4
D 5
paper.${PRINTER}: ${FIGURES}
E 5
I 5
D 9
paper.ps: ${FIGURES}
E 9
I 9
D 10
paper.ps: ${FIGURES} ${SRCS}
E 10
I 10
#paper.ps: ${FIGURES} ${SRCS}
paper.ps: ${SRCS}
E 10
E 9
E 5
	${SOELIM} ${SRCS} | ${TBL} | ${ROFF} > ${.TARGET}
E 4

E 3
D 4
troff:	${FIGURES}
D 3
	soelim puman${SEC}.n | tbl | ${TROFF}
E 3
I 3
	soelim puman${SEC}.n | ${TBL} | ${TROFF}
E 4
I 4
.include <bsd.doc.mk>
E 4
E 3

E 2
csfix:
D 4
	cc -O csfix.c -o csfix
E 4
I 4
	${CC} -O ${.CURDIR}/csfix.c -o ${.TARGET}

E 4
firstout: first.p csfix
D 3
	-csh -cf 'pix first.p |& expand | csfix >firstout'
E 3
I 3
D 7
	-csh -cf 'pix -g first.p |& expand | csfix >firstout'
E 7
I 7
D 9
	-csh -cf '$(PIX) -g first.p |& expand | csfix >firstout'
E 9
I 9
	-csh -cf '$(PIX) -g first.p |& expand | ./csfix >firstout'
E 9
E 7
I 4

E 4
E 3
firstobjout: first.p
D 3
	-csh -cf 'pi first.p >& firstobjout ; px >& firstobjout'
E 3
I 3
D 7
	-csh -cf 'pi -g first.p >& firstobjout ; px >& firstobjout'
E 7
I 7
	-csh -cf '$(PI) -g first.p >& firstobjout ; $(PX) >& firstobjout'
E 7
I 4

E 4
E 3
firstobjout2: first.p
D 3
	-csh -cf 'pi -p first.p >& firstobjout2 ; px >& firstobjout2'
E 3
I 3
D 7
	-csh -cf 'pi -g -p first.p >& firstobjout2 ; px >& firstobjout2'
E 7
I 7
	-csh -cf '$(PI) -g -p first.p >& firstobjout2 ; $(PX) >& firstobjout2'
E 7
I 4

E 4
E 3
bigger2.p: bigger.p
D 4
	-expand bigger.p >bigger2.p
E 4
I 4
	-expand bigger.p > bigger2.p

E 4
bigger3.p: bigger2.p csfix
D 4
	cat -n bigger2.p | expand | csfix -d >bigger3.p
E 4
I 4
D 9
	cat -n bigger2.p | expand | csfix -d > bigger3.p
E 9
I 9
	cat -n bigger2.p | expand | ./csfix -d > bigger3.p
E 9

E 4
bigout1: bigger.p csfix
D 3
	-csh -cf 'pix bigger.p |& expand | csfix  >bigout1'
E 3
I 3
D 7
	-csh -cf 'pix -g bigger.p |& expand | csfix  >bigout1'
E 7
I 7
D 9
	-csh -cf '$(PIX) -g bigger.p |& expand | csfix  >bigout1'
E 9
I 9
	-csh -cf '$(PIX) -g bigger.p |& expand | ./csfix  >bigout1'
E 9
E 7
I 4

E 4
E 3
bigger6.p: bigger5.p csfix
D 9
	cat -n bigger5.p | expand | csfix -d >bigger6.p
E 9
I 9
	cat -n bigger5.p | expand | ./csfix -d >bigger6.p
E 9
I 4

E 4
bigout2: bigger4.p
D 3
	-csh -cf 'pix bigger4.p |& expand >bigout2'
E 3
I 3
D 7
	-csh -cf 'pix -g bigger4.p |& expand >bigout2'
E 7
I 7
	-csh -cf '$(PIX) -g bigger4.p |& expand >bigout2'
E 7
I 4

E 4
E 3
bigout3: bigger7.p
D 3
	-csh -cf 'pix bigger7.p |& expand >bigout3'
E 3
I 3
D 7
	-csh -cf 'pix -g bigger7.p |& expand >bigout3'
E 7
I 7
	-csh -cf '$(PIX) -g bigger7.p |& expand >bigout3'
E 7
I 4

E 4
E 3
bigout4: bigger7.p
D 3
	-csh -cf '(pix bigger7.p >/dev/null) |& expand > bigout4'
E 3
I 3
D 7
	-csh -cf '(pix -g bigger7.p >/dev/null) |& expand > bigout4'
E 7
I 7
	-csh -cf '($(PIX) -g bigger7.p >/dev/null) |& expand > bigout4'
E 7
I 4

E 4
E 3
primeout1: primes.p csfix
D 3
	-csh -cf 'pix -l -z primes.p |& expand | csfix - >primeout1'
E 3
I 3
D 7
	-csh -cf 'pix -g -l -z primes.p |& expand | csfix - >primeout1'
E 7
I 7
D 9
	-csh -cf '$(PIX) -g -l -z primes.p |& expand | csfix - >primeout1'
E 9
I 9
	-csh -cf '$(PIX) -g -l -z primes.p |& expand | ./csfix - >primeout1'
E 9
E 7
I 4

E 4
E 3
primeout2: primes.p csfix
D 7
	-csh -cf 'pxp -z primes.p |& expand | csfix - >primeout2'
E 7
I 7
D 9
	-csh -cf '$(PXP) -z primes.p |& expand | csfix - >primeout2'
E 9
I 9
	-csh -cf '$(PXP) -z primes.p |& expand | ./csfix - >primeout2'
E 9
E 7
I 4

E 4
digitsout: digits.p csfix
D 3
	-csh -cf 'pi digits.p |& expand | csfix >digitsout'
E 3
I 3
D 7
	-csh -cf 'pi -g digits.p |& expand | csfix >digitsout'
E 7
I 7
D 9
	-csh -cf '$(PI) -g digits.p |& expand | csfix >digitsout'
E 9
I 9
	-csh -cf '$(PI) -g digits.p |& expand | ./csfix >digitsout'
E 9
E 7
I 4

E 4
E 3
synerrout: synerr.p csfix
D 3
	-csh -cf 'pi -l synerr.p |& expand | csfix >synerrout'
E 3
I 3
D 7
	-csh -cf 'pi -g -l synerr.p |& expand | csfix >synerrout'
E 7
I 7
D 9
	-csh -cf '$(PI) -g -l synerr.p |& expand | csfix >synerrout'
E 9
I 9
	-csh -cf '$(PI) -g -l synerr.p |& expand | ./csfix >synerrout'
E 9
E 7
I 4

E 4
E 3
synerr2out: synerr2.p csfix
D 3
	-csh -cf 'pix -l synerr2.p |& expand | csfix >synerr2out'
E 3
I 3
D 7
	-csh -cf 'pix -g -l synerr2.p |& expand | csfix >synerr2out'
E 7
I 7
D 9
	-csh -cf '$(PIX) -g -l synerr2.p |& expand | csfix >synerr2out'
E 9
I 9
	-csh -cf '$(PIX) -g -l synerr2.p |& expand | ./csfix >synerr2out'
E 9
E 7
I 4

E 4
E 3
mismout: mism.p csfix
D 3
	-csh -cf 'pi -l mism.p |& expand | csfix >mismout'
E 3
I 3
D 7
	-csh -cf 'pi -g -l mism.p |& expand | csfix >mismout'
E 7
I 7
D 9
	-csh -cf '$(PI) -g -l mism.p |& expand | csfix >mismout'
E 9
I 9
	-csh -cf '$(PI) -g -l mism.p |& expand | ./csfix >mismout'
E 9
E 7
I 4

E 4
E 3
clashout: clash.p
D 3
	-csh -cf 'pi clash.p |& expand >clashout'
E 3
I 3
D 7
	-csh -cf 'pi -g clash.p |& expand >clashout'
E 7
I 7
	-csh -cf '$(PI) -g clash.p |& expand >clashout'
E 7
I 4

E 4
E 3
sinout1: sin1.p
D 3
	-csh -cf 'pi sin1.p |& expand >sinout1'
E 3
I 3
D 7
	-csh -cf 'pi -g sin1.p |& expand >sinout1'
E 7
I 7
	-csh -cf '$(PI) -g sin1.p |& expand >sinout1'
E 7
I 4

E 4
E 3
sinout2: sin2.p
D 3
	-csh -cf 'pi sin2.p |& expand >sinout2'
E 3
I 3
D 7
	-csh -cf 'pi -g sin2.p |& expand >sinout2'
E 7
I 7
	-csh -cf '$(PI) -g sin2.p |& expand >sinout2'
E 7
I 4

E 4
E 3
exprout: expr.p
D 3
	-pi -l expr.p | expand >exprout
E 3
I 3
D 7
	-pi -g -l expr.p | expand >exprout
E 7
I 7
	-$(PI) -g -l expr.p | expand >exprout
E 7
I 4

E 4
E 3
typequout: typequ.p
D 3
	-pi typequ.p >typequout
E 3
I 3
D 7
	-pi -g typequ.p >typequout
E 7
I 7
	-$(PI) -g typequ.p >typequout
E 7
I 4

E 4
E 3
primeout3: primes2.p csfix
D 3
	-csh -cf 'pix primes2.p |& expand | csfix -d >primeout3'
E 3
I 3
D 7
	-csh -cf 'pix -g primes2.p |& expand | csfix -d >primeout3'
E 7
I 7
D 9
	-csh -cf '$(PIX) -g primes2.p |& expand | csfix -d >primeout3'
E 9
I 9
	-csh -cf '$(PIX) -g primes2.p |& expand | ./csfix -d >primeout3'
E 9
E 7
I 4

E 4
E 3
katout: kat.p csfix primes
D 3
	-csh -cf 'pix -l kat.p <primes |& expand | csfix -d >katout'
E 3
I 3
D 7
	-csh -cf 'pix -g -l kat.p <primes |& expand | csfix -d >katout'
E 7
I 7
D 9
	-csh -cf '$(PIX) -g -l kat.p <primes |& expand | csfix -d >katout'
E 9
I 9
	-csh -cf '$(PIX) -g -l kat.p <primes |& expand | ./csfix -d >katout'
E 9
E 7
I 4

E 4
E 3
copydataout: copydata.p csfix
D 3
	-csh -cf 'pix -l copydata.p |& expand | csfix -d >copydataout'
E 3
I 3
D 7
	-csh -cf 'pix -g -l copydata.p |& expand | csfix -d >copydataout'
E 7
I 7
D 9
	-csh -cf '$(PIX) -g -l copydata.p |& expand | csfix -d >copydataout'
E 9
I 9
	-csh -cf '$(PIX) -g -l copydata.p |& expand | ./csfix -d >copydataout'
E 9
E 7
E 3
D 4
kat2out: kat2.p
E 4
I 4

kat2out: kat2.p csfix
E 4
D 3
	-csh -cf 'pi kat2.p ; obj primes |& csfix -d >kat2out'
E 3
I 3
D 7
	-csh -cf 'pi -g kat2.p ; obj primes |& csfix -d >kat2out'
E 7
I 7
D 9
	-csh -cf '$(PI) -g kat2.p ; obj primes |& csfix -d >kat2out'
E 9
I 9
	-csh -cf '$(PI) -g kat2.p ; obj primes |& ./csfix -d >kat2out'
E 9
E 7
I 4

E 4
E 3
xxxxqqqout: kat2.p
D 3
	-pi kat2.p
E 3
I 3
D 7
	-pi -g kat2.p
E 7
I 7
	-$(PI) -g kat2.p
E 7
E 3
	-csh -cf 'obj xxxxqqq >& xxxxqqqout'
I 4

E 4
xxxxqqqout2: kat2.p
D 3
	-pi -p kat2.p
E 3
I 3
D 7
	-pi -g -p kat2.p
E 7
I 7
	-$(PI) -g -p kat2.p
E 7
E 3
	-csh -cf 'obj xxxxqqq >& xxxxqqqout2'
I 4

E 4
primes: primes.p
D 3
	-pix -p primes.p > primes
E 3
I 3
D 7
	-pix -g -p primes.p > primes
E 7
I 7
	-$(PIX) -g -p primes.p > primes
E 7
E 3
D 4
primes-d: primes
E 4
I 4

primes-d: primes csfix
E 4
D 9
	csfix -d <primes >primes-d
E 9
I 9
	./csfix -d <primes >primes-d
E 9
I 4

E 4
katscript: katin
D 3
	-csh -cf 'pi kat2.p ; obj katin >& katscript'
E 3
I 3
D 7
	-csh -cf 'pi -g kat2.p ; obj katin >& katscript'
E 7
I 7
	-csh -cf '$(PI) -g kat2.p ; obj katin >& katscript'
E 7
E 3
	-ed - katscript < fixkatscript
I 4

E 4
comments1.p: comments.p
	-expand comments.p >comments1.p
I 4

E 4
commentsout: comments.p
D 7
	-csh -cf 'pxp comments.p |& expand >commentsout'
E 7
I 7
	-csh -cf '$(PXP) comments.p |& expand >commentsout'
E 7
	-ed - commentsout < fixcomments
D 4
clean:
D 3
	-rm csfix pmon.out obj lpr ${FIGURES}
E 3
I 3
	-rm csfix pmon.out obj lpr.${PRINTER} ${FIGURES} errs Errs
E 4
E 3
E 1
