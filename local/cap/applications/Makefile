# Makefile autoconfigured for a: \
	SunOS system on Wed Sep 14 03:40:09 PDT 1988



MFLAGS=
LFLAGS=
CC=cc
LD=ld
all:
	(cd lwsrv; make)
	(cd papif; make)
	(cd aufs; make)

install:
	(cd lwsrv; make install)
	(cd papif; make install)
	(cd aufs; make install)

clean:
	-(cd lwsrv; make clean)
	-(cd papif; make clean)
	-(cd aufs; make clean)

dist:
	@cat todist
	@(cd papif; make dist)
	@(cd lwsrv; make dist)
	@(cd aufs; make dist)

