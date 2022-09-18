#
# Copyright (c) 1987 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%W%	(Berkeley)	%G%
#
MDIR=	/usr/local/man/cat1
SRCS=	Pnews.1 Rcc.1 Rnmail.1 Rpi.1 Spell.1 aedplot.1 \
	afm.1 backup10.1 bibtex.1 book.1 bs.1 \
	catdvi.1 checkin.1 checknews.1 checkout.1 compte.1 \
	copy.1 cpr.1 cref.1 ctroll.1 dd_codes.1 ddcodes.1 ddform.1 \
	ddgrep.1 ddinput.1 ddmerge.1 ddop.1 ddpr.1 ddsort.1 ddwc.1 \
	deqn.1 detex.1 dict.1 difftc.1 dis.1 ditroff.1 dl.1 doorcard.1 \
	dtbl.1 dterm.1 dvi2ps.1 dvi2x.1 dviimp.1 dvilpr.1 dviselect.1 \
	dvisun.1 edfn.1 enscript.1 eqn.1 et.1 f_files.1 focus.1 font.1 \
	form.1 garcon.1 gdump.1 gprint.1 gr2ps.1 gremlin.1 gremlinlib.1 \
	grn.1 gview.1 h19sys.1 ibmtex.1 ideal.1 inelim.1 inews.1 itroff.1 \
	jot.1 ksh.1 lstree.1 maitrd.1 mdc.1 \
	mm.1 mod2.1 mon.1 mtroll.1 nchk.1 netnews.1 newapl.1 newcal.1 \
	newscheck.1 newsetup.1 newsgroups.1 \
	ntex.1 pack.1 pf.1 pic.1 postscript.1 prolog.1 ps4014.1 \
	ps630.1 pscat.1 pscatmap.1 psdit.1 psfilters.1 psgrind.1 psplot.1 \
	psrev.1 psroff.1 pssun.1 ptroff.1 r2bib.1 r_files.1 rapid.1 \
	rapsum.1 readnews.1 recnews.1 recover.1 rescue.1 ri.1 rix.1 \
	rn.1 rsort.1 rx.1 scalepx.1 sendnews.1 \
	showtc.1 sno.1 sortrefs.1 spell.1 spice.1 splscr.1 strace.1 \
	tangle.1 tbe.1 tcsh.1 tdi.1 tempo.1 tex.1 texintro.1 texprep.1 \
	tf.1 tgrind.1 tores.1 tpg.1 tr2tex.1 transcript.1 trchange.1 troll.1 \
	trollsort.1 undump.1 uurec.1 uustat.1 uusub.1 vaxima.1 versaplot.1 \
	vsh.1 wdog.1 weave.1 winlib.1 xref.1 yank.1
OBJS=	Pnews.0 Rcc.0 Rnmail.0 Rpi.0 Spell.0 aedplot.0 \
	afm.0 backup10.0 bibtex.0 book.0 bs.0 \
	catdvi.0 checkin.0 checknews.0 checkout.0 compte.0 \
	copy.0 cpr.0 cref.0 ctroll.0 dd_codes.0 ddcodes.0 ddform.0 \
	ddgrep.0 ddinput.0 ddmerge.0 ddop.0 ddpr.0 ddsort.0 ddwc.0 \
	deqn.0 detex.0 dict.0 difftc.0 dis.0 ditroff.0 dl.0 doorcard.0 \
	dtbl.0 dterm.0 dvi2ps.0 dvi2x.0 dviimp.0 dvilpr.0 dviselect.0 \
	dvisun.0 edfn.0 enscript.0 eqn.0 et.0 f_files.0 focus.0 font.0 \
	form.0 garcon.0 gdump.0 gprint.0 gr2ps.0 gremlin.0 gremlinlib.0 \
	grn.0 gview.0 h19sys.0 ibmtex.0 ideal.0 inelim.0 inews.0 itroff.0 \
	jot.0 ksh.0 lstree.0 maitrd.0 mdc.0 \
	mm.0 mod2.0 mon.0 mtroll.0 nchk.0 netnews.0 newapl.0 newcal.0 \
	newscheck.0 newsetup.0 newsgroups.0 \
	ntex.0 pack.0 pf.0 pic.0 postscript.0 prolog.0 ps4014.0 \
	ps630.0 pscat.0 pscatmap.0 psdit.0 psfilters.0 psgrind.0 psplot.0 \
	psrev.0 psroff.0 pssun.0 ptroff.0 r2bib.0 r_files.0 rapid.0 \
	rapsum.0 readnews.0 recnews.0 recover.0 rescue.0 ri.0 rix.0 \
	rn.0 rsort.0 rx.0 scalepx.0 sendnews.0 \
	showtc.0 sno.0 sortrefs.0 spell.0 spice.0 splscr.0 strace.0 \
	tangle.0 tbe.0 tcsh.0 tdi.0 tempo.0 tex.0 texintro.0 texprep.0 \
	tf.0 tgrind.0 tores.0 tpg.0 tr2tex.0 transcript.0 trchange.0 troll.0 \
	trollsort.0 undump.0 uurec.0 uustat.0 uusub.0 vaxima.0 versaplot.0 \
	vsh.0 wdog.0 weave.0 winlib.0 xref.0 yank.0
LINKS=	ibmlatex.0 initex.0 virtex.0 troff.0 trchanges.0 ud.0

.SUFFIXES: .1 .0

.1.0:
	${DESTDIR}/usr/man/manroff $*.1 > $*.0

all: ${OBJS}

eqn.0:
	eqn eqn.1 | ${DESTDIR}/usr/man/manroff > $@

clean: FRC
	rm -f ${OBJS}

install: FRC
	cd ${DESTDIR}${MDIR}; rm -f *.0
	install -c -o bin -g bin -m 444 ${OBJS} ${DESTDIR}${MDIR}
	ln ${DESTDIR}${MDIR}/ibmtex.0 ${DESTDIR}${MDIR}/ibmlatex.0
	ln ${DESTDIR}${MDIR}/tex.0 ${DESTDIR}${MDIR}/initex.0
	ln ${DESTDIR}${MDIR}/tex.0 ${DESTDIR}${MDIR}/virtex.0
	ln ${DESTDIR}${MDIR}/ditroff.0 ${DESTDIR}${MDIR}/troff.0
	ln ${DESTDIR}${MDIR}/trchange.0 ${DESTDIR}${MDIR}/trchanges.0
	ln ${DESTDIR}${MDIR}/dl.0 ${DESTDIR}${MDIR}/ud.0

FRC:
