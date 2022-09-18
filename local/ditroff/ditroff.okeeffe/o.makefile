PREFIX = SCCS/s.
CFLAGS= -O -DBSD42
CFILES=n1.c n2.c n3.c n4.c n5.c t6.c n7.c n8.c n9.c t10.c ni.c nii.c hytab.c suftab.c
HFILES=tdef.h v.h d.h s.h tw.h dev.h
TFILES=n1.o n2.o n3.o n4.o n5.o t6.o n7.o n8.o n9.o t10.o ni.o nii.o hytab.o suftab.o
NFILES=n1.o n2.o n3.o n4.o n5.o n6.o n7.o n8.o n9.o n10.o ni.o nii.o hytab.o suftab.o

a.out:	$(TFILES)
	cc -i $(CFLAGS) $(TFILES) 

nroff:	$(NFILES)
	cc -o na.out -i $(CFLAGS) $(NFILES)
	@echo output in na.out

n1.o:	tdef.h d.h v.h tw.h s.h ext.h ni.o
n2.o:	tdef.h d.h v.h tw.h s.h
n3.o:	tdef.h d.h v.h tw.h s.h
n4.o:	tdef.h d.h v.h tw.h s.h
n5.o:	tdef.h d.h v.h tw.h s.h
n6.o:	tdef.h d.h v.h tw.h s.h
t6.o:	tdef.h d.h v.h tw.h s.h dev.h ni.o
n7.o:	tdef.h d.h v.h tw.h s.h
n8.o:	tdef.h d.h v.h tw.h s.h
n9.o:	tdef.h d.h v.h tw.h s.h
n10.o:	tdef.h d.h v.h tw.h s.h
t10.o:	tdef.h d.h v.h tw.h s.h dev.h ni.o
ni.o:	tdef.h d.h v.h tw.h s.h
nii.o:	tdef.h d.h v.h tw.h s.h

hytab.o:	hytab.c

suftab.o:	suftab.c


list:
#	@print TODO n[1-6].c t6.c n[7-9].c [nt]10.c ni.c nii.c *.h
	@print n[1-6].c t6.c n[7-9].c [nt]10.c ni.c nii.c *.h

lint:
	lint -phc $(CFILES)

lib:
	cp a.out /usr/lib/troff.new
	strip /usr/lib/troff.new
	push fs /usr/lib/troff.new /usr/lib

dcat:	dcat.o draw.o dev.h
	cc -o dcat dcat.o draw.o -lm

d202:	d202.o draw.o dev.h
	cc -O -o d202 d202.o draw.o -lm

jc:	jc.o draw.o dev.h
	cc -O -o jc jc.o draw.o -lm

dcan:	dcan.o draw.o dev.h
	cc -O -o dcan dcan.o draw.o -lm

dsort:	dsort.o dev.h
	cc -i -O -o dsort dsort.o

daps:	daps.o draw.o aps.h dev.h
	cc -o daps daps.o draw.o -lm

dhar.o:	hcodes.h dev.h

dhar:	dhar.o draw.o llio.o
	cc -o dhar dhar.o llio.o draw.o -lm

dharf.o:	dev.h dharf.h
	cc -c -DFILTER dharf.c

dharf:	dharf.o draw.o
	cc -o dharf dharf.o draw.o /usr/cl/jaap/lpr/printcap.o -lm

drule:	drule.o draw.o llio.o dev.h
	cc -o drule drule.o llio.o draw.o -lm

llio.o:	llio.h hcodes.h

tc:	tc.o draw.o dev.h
	cc -O -o tc tc.o draw.o -lm

hc:	hc.o draw.o dev.h
	cc -O -o hc hc.o draw.o -lm

ta.o	: dev.h

ta:	ta.o draw.o dev.h
	cc -O -o ta ta.o draw.o -lm

makedev.o:	dev.h

makedev:	makedev.o
	cc -o makedev makedev.o

dumpdev.o:	dev.h

dumpdev:	dumpdev.o
	cc -o dumpdev dumpdev.o

dumpaps:	dumpaps.c
	cc dumpaps.c -o dumpaps

src:
	cp makefile $(CFILES) $(HFILES) /usr/src/local/local/ditroff

driverlist:
	pr d202.c dev.h dcat.c daps.c makedev.c /usr/src/cmd/troff/tc.c

backup:
	cp /usr/lib/troff.new /usr/lib/otroff.new

clean:
	rm *.o a.out make.out
