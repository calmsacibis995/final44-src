CFLAGS= -O

dcat:	dcat.o draw.o dev.h
	cc -o dcat dcat.o draw.o -lm

d202:	d202.o draw.o dev.h
	cc -O -o d202 d202.o draw.o -lm

dcan:	dcan.o draw.o dev.h
	cc -O -o dcan dcan.o draw.o -lm

dsort:	dsort.o dev.h
	cc -i -O -o dsort dsort.o

daps:	daps.o draw.o aps.h dev.h
	cc -o daps daps.o draw.o -lm

tc:	tc.o draw.o dev.h
	cc -O -o tc tc.o draw.o -lm

hc:	hc.o draw.o dev.h
	cc -O -o hc hc.o draw.o -lm

ta:	ta.o draw.o dev.h
	cc -O -o ta ta.o draw.o -lm

dumpaps:	dumpaps.c
	cc dumpaps.c -o dumpaps

driverlist:
	pr d202.c dev.h dcat.c daps.c makedev.c /usr/src/cmd/troff/tc.c

backup:
	cp /usr/lib/troff.new /usr/lib/otroff.new

clean:
	rm *.o a.out make.out
