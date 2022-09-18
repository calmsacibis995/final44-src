h31122
s 00005/00004/00054
d D 1.2 90/01/02 14:45:20 jaap 2 1
c just saving current version, shutting up Charlie
e
s 00058/00000/00000
d D 1.1 88/03/09 15:35:57 jaap 1 0
c date and time created 88/03/09 15:35:57 by jaap
e
u
U
t
T
I 1
# A sample Makefile for psfig stuff

P	= paper
Draft	=

# Change these to reflect your installation
D 2
Ditroff	= ditroff
Eqn	= eqn
E 2
I 2
Ditroff	= /usr/src/local/local/ditroff/ditroff
Eqn	= dieqn -Tpsc
Tbl	= tbl -Tpsc
E 2

D 2
Macros	= -ms
E 2
I 2
Macros	= -mns
E 2
MyMacs	= paper.tmac ../lib/psfig.tmac

# This should be the *modified* psdit
Psdit	= psdit

Psfig	= psfig $(Draft) -Dfigs
Docs	= $P.ps eqn.ps pro.ps

whattodo:
	@echo "Make what?"

pages: $P.ps
	getpages $P.ps

$P.pr: $P.ps
	psprint -e -r $P.ps

$P.ps: $P.pfg
	$(Ditroff) -Tpsc $(Macros) $(MyMacs) $P.pfg > $P.dtrf
	$(Psdit) $P.dtrf > $P.ps

$P.tek: $P.pfg
	$(Ditroff) -Ttc $(Macros) $(MyMacs) $P.pfg > $P.tc
	tc $P.tc
	
$P.pfg: $P.eqn
	$(Psfig) <$P.eqn >$P.pfg

$P.eqn: $P.tbl
	$(Eqn) -Tpsc <$P.tbl >$P.eqn

$P.tbl: $P.pic
D 2
	tbl <$P.pic >$P.tbl
E 2
I 2
	$(Tbl) <$P.pic >$P.tbl
E 2

$P.pic: $P.ms
	pic <$P.ms >$P.pic
	
count: $P.ms
	deroff $P.ms | wc -w

spell: #spell
#spell: $P.ms
	spell $P.ms >'#'spell

tidy:
	-rm -f *.BAK *.CKP core a.out
clean: tidy
	-rm -f *.tc *.dtrf *.pfg *.eqn *.tbl *.pic '#'* $P.ps.* $P.ps *.out
E 1
