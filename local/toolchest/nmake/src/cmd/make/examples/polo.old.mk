/*
 * original:	Rob Petterson		attunix!rcp2
 *
 * polo makefile -- new version is in polo.mk
 */

FILES=bldgr.c block.h blocks.h call.h dreloc.h fentry.h fentrys.h func.c func.h \
	get.c get.h ibrpos.h infile.c infile.h inst.c inst.h ispec.c ispec.h \
	ld.c ldtbread.c misc.c oper.c oper.h order.c outfile.c polo.h \
	polostruct.h print.c rmunch.c sdi.c sdi.h vol.h

LP=/usr/bin/lp 
LPFLAGS=-omode=lhws -omail=sfbc!rcp2 -dlaser

PRFLAGS=-f

CCFLAGS=-g

LDFLAGS=-g 

.PRECIOUS: $(FILES:N=*.h)

.GLOBAL.o:	(CCFLAGS)

polo :: $(FILES) -lld -lmalloc

backup: 
	ls $(FILES) makefile  | cpio -oc > /usr/tmp/polo
	uucp -C /usr/tmp/polo sfbc!/sgs2/rcp2/rje/polo.backup
	rm -f /usr/tmp/polo
