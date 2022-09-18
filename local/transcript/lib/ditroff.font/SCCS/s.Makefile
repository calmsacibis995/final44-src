h48169
s 00001/00001/00085
d D 1.3 88/03/31 22:32:43 edward 3 2
c strip comments out of charset to allow SCCS ID
e
s 00053/00047/00033
d D 1.2 88/03/26 19:56:33 karels 2 1
c add new fonts for Laserwriter-Plus, other fixes
e
s 00080/00000/00000
d D 1.1 87/09/15 12:40:36 edward 1 0
c date and time created 87/09/15 12:40:36 by edward
e
u
U
t
T
I 1
D 2
#	%W% %G%
E 2
I 2
#	%W% (Berkeley) %G%
E 2
# lib/ditroff.font/Makefile
#
# Copyright (c) 1984 Adobe Systems Incorporated. All Rights Reserved.
# PostScript is a trademark of Adobe Systems Incorporated.
# RCSID: $Header: Makefile,v 2.1 85/11/24 12:24:55 shore Rel $

# see README for more information
# makedev is the ditroff program that builds device descriptions

I 2
# Berkeley changes:
# 17 February, 1987.  Edward Wang (edward@arpa)
#	added stipple fonts and avoid forking new makes.

E 2
LOADFONTS = R I B BI H HB C CB S SS
D 2
MOREFONTS = HO HD CO CD
E 2
I 2
LOADF = R.aux I.aux B.aux BI.aux H.aux HB.aux C.aux CB.aux S.aux SS.aux
MOREFONTS = HO HD CO CD A AO AB AD \
	K KI KB KD NB ND NI NR \
	PB PD PI PR V VB VD VO ZC ZD
MOREF = HO.aux HD.aux CO.aux CD.aux A.aux AO.aux AB.aux AD.aux \
	K.aux KI.aux KB.aux KD.aux NB.aux ND.aux NI.aux NR.aux \
	PB.aux PD.aux PI.aux PR.aux V.aux VB.aux VD.aux VO.aux ZC.aux ZD.aux
MOREOUT = HO.out HD.out CO.out CD.out A.out AO.out AB.out AD.out \
	K.out KI.out KB.out KD.out NB.out ND.out NI.out NR.out \
	PB.out PD.out PI.out PR.out V.out VB.out VD.out VO.out ZC.out ZD.out
STIPPLES = cf ug mg
ALLFONTS = $(LOADF) $(MOREF)
E 2

D 2
FONTNAMES = ${LOADFONTS} ${MOREFONTS}
TEMPFILES = temp.header temp.spaces temp.trailer temp.aux
E 2
I 2
.SUFFIXES: .out .aux .map
E 2

I 2
# how to make a .aux (and the file with the same name with no extension)
# from a .map (this is input to makedev)

.map.aux:
	./afmdit $* ..

.aux.out:
	$$MAKEDEV $*

# how to make a .out (and a .aux) from a .map
# just do the above two steps

.map.out:
	./afmdit $* ..
	$$MAKEDEV $*

all: makedev DESC.out moreout

E 2
programs:

D 2
install: makedev all
E 2
I 2
install: all
E 2
	rm -rf $$DITDIR/devpsc
	mkdir $$DITDIR/devpsc
D 2
	cp *.aux *.map *.out DESC $$DITDIR/devpsc
	cd $$DITDIR/devpsc ; chown $$OWNER . * ; chgrp $$GROUP . * ; \
		chmod 755 . ; chmod 644 *.aux *.map *.out DESC
E 2
I 2
	-chmod 755 $$DITDIR/devpsc
	-chown $$OWNER.$$GROUP $$DITDIR/devpsc
	install -c -m 644 -o $$OWNER -g $$GROUP *.aux *.map *.out DESC \
		$$DITDIR/devpsc
	cd $$DITDIR/devpsc; ln C.map CW.map; ln C.out CW.out; ln C.aux CW.aux
E 2

makedev:
D 2
	test -r "$$MAKEDEV"
E 2
I 2
	test -r $$MAKEDEV
	-chmod +x afmdit
E 2

D 2
all DESC.out: ${LOADFONTS} moreout
E 2
I 2
DESC.out: DESC $(LOADF)
E 2
	$$MAKEDEV DESC

D 2
allfonts: ${FONTNAMES}
E 2
I 2
moreout: $(MOREOUT)
E 2

D 2
moreout: ${MOREFONTS}
	$$MAKEDEV $?
E 2
I 2
allfonts: $(ALLFONTS)
E 2

D 2
${LOADFONTS}:
	make ${MFLAGS} $@.font
E 2
I 2
$(ALLFONTS): afmdit.awk
E 2

D 2
${MOREFONTS}:
	-rm -f $@.font
	make ${MFLAGS} $@.font

${FONTNAMES}: DESC afmdit.awk Makefile

E 2
DESC: afmdit.awk Makefile charset devspecs
	rm -f DESC
	echo "# ditroff device description for PostScript" >> DESC
	echo "# PostScript is a trademark of Adobe Systems Incorporated">>DESC
D 2
	echo ${LOADFONTS} | awk '{print "fonts", NF, $$0}' >> DESC
	cat devspecs >>DESC
E 2
I 2
	echo fonts `echo $(LOADFONTS) | wc -w` $(LOADFONTS) >> DESC
	echo stipples `echo $(STIPPLES) | wc -w` $(STIPPLES) >> DESC
	cat devspecs >> DESC
E 2
	echo "charset" >> DESC
D 3
	cat charset >> DESC
E 3
I 3
	sed -e "/^#/d" charset >> DESC
E 3

clean:
D 2
	rm -f ${FONTNAMES} ${TEMPFILES} core DESC *.out *.font *.aux *.CKP *.BAK .emacs_[0-9]* temp*
E 2
I 2
	rm -f $(LOADFONTS) $(MOREFONTS) core DESC *.out *.aux temp.* \
		*.CKP *.BAK
E 2

D 2
.SUFFIXES: .out .font .map

# how to make a .font from a .map
# note that .font is a placeholder,  the file of interest has
# the same name with no extension (this is input to makedev)

.map.font:
	/bin/rm -f - ${TEMPFILES}
	./afmdit $* ..
	touch $*.font
	/bin/rm -f -  ${TEMPFILES}

# how to make a .out from a .font (again, the .font is dropped)

.font.out: DESC
	$$MAKEDEV $*

# how to make a .out from a .map
# just do the above two steps

.map.out:
	make ${MFLAGS} $@.font
	make ${MFLAGS} $@.out
E 2
E 1
