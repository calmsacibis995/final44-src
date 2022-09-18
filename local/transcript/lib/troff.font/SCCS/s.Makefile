h35372
s 00005/00001/00036
d D 1.2 90/10/19 19:16:37 karels 2 1
c actually need to install now
e
s 00037/00000/00000
d D 1.1 90/10/19 18:58:57 karels 1 0
c original version
e
u
U
t
T
I 1
# transcript/lib/troff.font/Makefile.bsd
#
# Copyright (C) 1985 Adobe Systems Incorporated
#
# Makefile for troff width tables and pscat correspondence tables
#
# See pscatmap(8) and the .map files for more information.
#
# If you add a font family to your PostScript/troff database,
# add it to the FAMILIES line in this makefile, then do a "make".

.SUFFIXES: .ct .map

#######################################################################
# Here are the family names, the face names are gotten from the .map files

FAMILIES = Times.ct Helvetica.ct
I 2
FILES=	Times.head Times.ct ftR ftI ftB ftS \
	Helvetica.head Helvetica.ct ftH ftHI ftHB ftHS
E 2

#######################################################################

install: ${FAMILIES}
I 2
	-mkdir $${TROFFFONTDIR?undefined}
	cp -p ${FILES} $${TROFFFONTDIR?undefined}
E 2

.map.ct:
D 2
	../pscatmap $*.map
E 2
I 2
	$${PSLIBDIR-/usr/local/lib/ps}/pscatmap $*.map
E 2
	make `awk -f doto.awk $*.map`
	awk -f head.awk $*.map >$*.head

# If you want to be able to check the ".c" files, remove the last 
# rule line (the "rm").
.c.o:
	cc -c $*.c
	mv $*.o $*
	strip $*
	rm $*.c

clean:
	rm -f - *.ct *.head *.c *.o ft? ft?? *BAK *CKP .emacs_[0-9]*
E 1
