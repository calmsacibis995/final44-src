h28243
s 00014/00000/00000
d D 1.1 84/12/14 12:58:13 opcode 1 0
c date and time created 84/12/14 12:58:13 by opcode
e
u
U
t
T
I 1
#
# %W%	%G%
#
# Mark Opperman (opcode@monet.BERKELEY)
#

libgremlin.a:	gremlinlib.o
		chmod 755 gremlinlib.o
		ar r libgremlin.a gremlinlib.o
		chmod 755 libgremlin.a
		ranlib libgremlin.a

gremlinlib.o:	gremlinlib.c gremlin.h
		cc -c -O gremlinlib.c
E 1
