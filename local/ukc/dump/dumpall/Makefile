#	Makefile	1.2	1/8/84

SRC=doadump.sh dumpall.sh

all:
	@echo use make install

install: $(SRC)
	install -c -m 750 doadump.sh /etc/doadump
	install -c -m 750 dumpall.sh /etc/dumpall

$(SRC):
	sccs get $@
