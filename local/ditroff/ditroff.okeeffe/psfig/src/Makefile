CFLAGS = -g
OBJS = main.o lineio.o item.o troff.o cmds.o keywords.o macros.o
SRCS = main.c lineio.c item.c troff.c cmds.c keywords.c macros.c
HDRS = psfig.h item.h

.c.o:
	-rm -f $@
	cc -c $(CFLAGS) $<

psfig : $(OBJS) 
	-rm -f psfig
	cc ${CFLAGS} -o psfig $(OBJS)

$(OBJS) : psfig.h
item.o cmds.o keywords.o: item.h

lint: $(SRCS) $(HDRS)
	lint $(SRCS)

tidy:
	-rm -f *.BAK *.CKP a.out
clean: tidy
	-rm -f *.o core '#'*
