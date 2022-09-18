h42064
s 00019/00000/00000
d D 1.1 84/10/21 15:04:30 opcode 1 0
c date and time created 84/10/21 15:04:30 by opcode
e
u
U
t
T
I 1
# %W%	%G%
# 
# Makefile for the SUN Gremlin picture editor.
# 
# Mark Opperman (opcode@monet.BERKELEY)

CC = 		cc

CFLAGS =	-fsingle

OBJ =		db.o graphics.o graphics2.o pix.o icondata.o sun.o\
		menu.o point.o undodb.o long1.o long2.o short.o help.o\
        	display.o path.o text.o strings.o startup.o main.o

all:            gremlin

gremlin:        ${OBJ}
		${CC} ${OBJ} ${CFLAGS} -lm -lsuntool -lsunwindow -lpixrect \
		-o gremlin
E 1
