h30573
s 00001/00001/00012
d D 1.2 84/08/01 11:19:44 pc 2 1
c Stop echo command being echoed
e
s 00013/00000/00000
d D 1.1 84/08/01 10:56:58 pc 1 0
c date and time created 84/08/01 10:56:58 by pc
e
u
U
t
T
I 1
#	%M%	%I%	%G%

SRC=doadump.sh dumpall.sh

all:
D 2
	echo use make install
E 2
I 2
	@echo use make install
E 2

install: $(SRC)
	install -c -m 750 doadump.sh /etc/doadump
	install -c -m 750 dumpall.sh /etc/dumpall

$(SRC):
	sccs get $@
E 1
