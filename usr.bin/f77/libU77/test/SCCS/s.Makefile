h19017
s 00007/00000/00000
d D 5.1 90/06/25 14:07:04 bostic 1 0
c date and time created 90/06/25 14:07:04 by bostic
e
u
U
t
T
I 1
TESTS = actst argtst chdtst ertst fktst gpctst idtst loctst seektst sigtst \
	statst timtst

all:	$(TESTS)

$(TESTS):
	f77 -O $*.f -o $*
E 1
