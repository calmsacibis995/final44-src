
CFLAGS= -O 
LDFLAGS= 

OBJECTS= defs.o  jsh.o mpx.o

jsh:		$(OBJECTS)
		$(CC) $(CFLAGS) $(LDFLAGS) -o jsh $(OBJECTS)

print:
		list makefile defs.h defs.c jsh.c mpx.c | lp -dxhole



defs.o newmain.o mpx.o : defs.h


install:	jsh
		/etc/install -o -f /usr/bin jsh
		chown root /usr/bin/jsh
		chgrp sys /usr/bin/jsh
		chmod 4755 /usr/bin/jsh

clobber:	clean
		rm -f jsh

clean:		
		rm -f  *.o

