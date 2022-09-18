BINDIR	= /usr/local
CC	= cc -DFASTIO 

CFILES	= db1.c db2.c db3.c findaed.c graphics1.c graphics2.c graphics3.c  \
	menu.c point.c undodb.c long1.c long2.c short.c \
        textio.c display.c path.c config.c main.c

OBJ	= db1.o db2.o db3.o findaed.o graphics1.o graphics2.o graphics3.o  \
	menu.o point.o undodb.o long1.o long2.o short.o \
        textio.o display.o path.o config.o main.o

gremlin:  $(OBJ)
	$(CC) -o gremlin  $(OBJ) -lm -ltermlib

install:  $(BINDIR)/gremlin

$(BINDIR)/gremlin:  gremlin
	install -c -s gremlin $(BINDIR)/gremlin

clean:
	/bin/rm -f *.o gremlin

depend: 
	${CC} -M ${CFILES} | \
	sed -e ':loop' \
	    -e 's/\.\.\/[^ /]*\/\.\./../' \
	    -e 't loop' | \
	awk ' { if ($$1 != prev) { print rec; rec = $$0; prev = $$1; } \
		else { if (length(rec $$2) > 78) { print rec; rec = $$0; } \
		       else rec = rec " " $$2 } } \
	      END { print rec } ' > makedep
	echo '/^# DO NOT DELETE THIS LINE/+1,$$d' >eddep
	echo '$$r makedep' >>eddep
	echo 'w' >>eddep
	cp Makefile Makefile.bak
	ex - Makefile < eddep
	rm eddep makedep

# DO NOT DELETE THIS LINE -- make depend uses it

db1.o: db1.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h ./grem2.h
db1.o: /usr/include/ctype.h
db2.o: db2.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h ./grem2.h
db3.o: db3.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h ./grem2.h
findaed.o: findaed.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h
graphics1.o: graphics1.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h
graphics1.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
graphics1.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
graphics2.o: graphics2.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h
graphics2.o: ./grem2.h
graphics3.o: graphics3.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h
graphics3.o: /usr/include/sys/types.h /usr/include/sys/timeb.h
graphics3.o: /usr/include/signal.h /usr/include/sys/time.h /usr/include/time.h
menu.o: menu.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h
point.o: point.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h ./grem2.h
undodb.o: undodb.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h
undodb.o: ./grem2.h
long1.o: long1.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h ./grem2.h
long1.o: /usr/include/ctype.h
long2.o: long2.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h ./grem2.h
long2.o: /usr/include/ctype.h
short.o: short.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h ./grem2.h
short.o: /usr/include/signal.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
short.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
textio.o: textio.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h
textio.o: /usr/include/sgtty.h /usr/include/sys/ioctl.h
textio.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
display.o: display.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h
display.o: ./grem2.h
path.o: path.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h
path.o: /usr/include/pwd.h /usr/include/ctype.h
config.o: config.c
main.o: main.c ./gremlin.h /usr/include/stdio.h /usr/include/math.h ./grem2.h
main.o: /usr/include/signal.h /usr/include/sgtty.h /usr/include/sys/ioctl.h
main.o: /usr/include/sys/ttychars.h /usr/include/sys/ttydev.h
main.o: /usr/include/sys/types.h /usr/include/sys/stat.h
main.o: /usr/include/sys/time.h /usr/include/time.h
