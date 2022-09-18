all:
	(cd cap; make)
	(cd afp; make)
	(cd afpc; make)

install:
	(cd cap; make install)
	(cd afp; make install)
	(cd afpc; make install)

clean:
	-(cd cap; make clean)
	-(cd afp; make clean)
	-(cd afpc; make clean)

dist:
	@cat todist
	@(cd cap; make dist)
	@(cd afp; make dist)
	@(cd afpc; make dist)

