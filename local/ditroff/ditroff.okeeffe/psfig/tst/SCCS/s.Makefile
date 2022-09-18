h12711
s 00012/00005/00004
d D 1.2 90/01/02 14:46:08 jaap 2 1
c just saving current version, shutting up Charlie
e
s 00009/00000/00000
d D 1.1 88/03/04 18:17:17 jaap 1 0
c date and time created 88/03/04 18:17:17 by jaap
e
u
U
t
T
I 1
D 2
Ditroff= /usr/local/ditroff -Tpsc
Psfig= ../src/psfig -D../doc/figs
E 2
I 2
Psfig= psfig -D../doc/figs
E 2
Macs= ../lib/psfig.tmac
I 2
Ditroff= /usr/src/local/local/ditroff/ditroff -Tpsc $(Macs) -
E 2
#
# A Modified psdit, of course. 
D 2
Psdit= /usr/bin/psdit  
E 2
I 2
Psdit= psdit
E 2

D 2
test.ps: test.trf
	$(Psfig) test.trf | $(Ditroff) -ms $(Macs) - | $(Psdit) > test.ps
E 2
I 2
eqn: eqn.tst
	dieqn -Tpsc eqn.tst | $(Psfig) | $(Ditroff)  | psdit > eqn.ps
eqn.out: eqn.tst
	dieqn -Tpsc eqn.tst | $(Psfig) | $(Ditroff)  > eqn.out

test.ps: test.out
	PSLIBDIR=/usr/src/local/local/psfig/tmp/; export PSLIBDIR; $(Psdit) test.out > test.ps
test.out: test.trf
	PSLIBDIR=/usr/src/local/local/psfig/tmp/; export PSLIBDIR; $(Psfig) test.trf | $(Ditroff) -ms $(Macs) -  > test.out
E 2
E 1
