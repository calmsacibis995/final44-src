#	%W% (Berkeley) %G%

BUILD=	ATT.c ATT.sh ATT.man ATT.gas ATT.semicolon ATT.roff ATT.tex \
	redist.c redist.sh redist.man redist.gas redist.semicolon \
	redist.roff redist.tex \
	SHARED.c SHARED.sh SHARED.man SHARED.gas SHARED.semicolon \
	SHARED.roff SHARED.tex

all: ${BUILD}

clean cleandir:
	cd includes; rm -f ${BUILD}

depend lint tags:

ATT.c: att.BASE
	cd includes; sed 's/^/ */' < ../att.BASE > $@
ATT.sh: att.BASE
	cd includes; sed 's/^/#/' < ../att.BASE > $@
ATT.man: att.BASE
	cd includes; sed 's/^/.\\"/' < ../att.BASE > $@
ATT.gas: att.BASE
	cd includes; sed 's/^/|/' < ../att.BASE > $@
ATT.tex: att.BASE
	cd includes; sed 's/^/%/' < ../att.BASE > $@
ATT.semicolon: att.BASE
	cd includes; sed 's/^/;/' < ../att.BASE > $@
ATT.roff: att.BASE
	cd includes; sed 's/^/.\\"/' < ../att.BASE > $@

redist.c: bsd.BASE
	cd includes; sed 's/^/ */' < ../bsd.BASE > $@
redist.sh: bsd.BASE
	cd includes; sed 's/^/#/' < ../bsd.BASE > $@
redist.man: bsd.BASE
	cd includes; sed 's/^/.\\"/' < ../bsd.BASE > $@
redist.gas: bsd.BASE
	cd includes; sed 's/^/|/' < ../bsd.BASE > $@
redist.tex: bsd.BASE
	cd includes; sed 's/^/%/' < ../bsd.BASE > $@
redist.semicolon: bsd.BASE
	cd includes; sed 's/^/;/' < ../bsd.BASE > $@
redist.roff: bsd.BASE
	cd includes; sed 's/^/.\\"/' < ../bsd.BASE > $@

SHARED.c: shared.BASE
	cd includes; sed 's/^/ */' < ../shared.BASE > $@
SHARED.sh: shared.BASE
	cd includes; sed 's/^/#/' < ../shared.BASE > $@
SHARED.man: shared.BASE
	cd includes; sed 's/^/.\\"/' < ../shared.BASE > $@
SHARED.gas: shared.BASE
	cd includes; sed 's/^/|/' < ../shared.BASE > $@
SHARED.tex: shared.BASE
	cd includes; sed 's/^/%/' < ../shared.BASE > $@
SHARED.semicolon: shared.BASE
	cd includes; sed 's/^/;/' < ../shared.BASE > $@
SHARED.roff: shared.BASE
	cd includes; sed 's/^/.\\"/' < ../shared.BASE > $@
