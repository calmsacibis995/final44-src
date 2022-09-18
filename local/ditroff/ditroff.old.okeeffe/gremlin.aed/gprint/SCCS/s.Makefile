h63613
s 00004/00000/00009
d D 1.3 83/03/30 13:38:51 ralph 3 2
c modified mapping and scale factors to fit in square arrays.
e
s 00007/00021/00002
d D 1.2 83/03/02 13:51:15 ralph 2 1
c this version uses remote line printer software.
e
s 00023/00000/00000
d D 1.1 83/03/02 13:29:58 ralph 1 0
c date and time created 83/03/02 13:29:58 by ralph
e
u
U
t
T
I 3
#	%M%	%I%	%E%

E 3
I 2
CFLAGS = -O
LDFLAGS = -lm
OBJS = hdb.o hpoint.o hgraph.o main.o
E 2
I 1

D 2
OBJ= hdb.o hpoint.o hgraph.o main.o getlogin.o
E 2
I 2
gprint:  ${OBJS}
	cc -o gprint ${OBJS} ${LDFLAGS}
I 3

${OBJS}: gprint.h
E 3
E 2

D 2
all:   $(OBJ) gprint

hdb.o:   hdb.c 
	cc -c -g hdb.c 

hgraph.o:	hgraph.c
	cc -c -g hgraph.c

hpoint.o:	hpoint.c
	cc -c -g hpoint.c


main.o:   main.c 
	cc -c -g main.c 

gprint:  $(OBJ)
	cc -o gprint -g $(OBJ) -lm 

gdump: gdump.o getlogin.o
	cc -o gdump -g gdump.o getlogin.o
E 2
I 2
clean:
	rm -f *.o
E 2
E 1
