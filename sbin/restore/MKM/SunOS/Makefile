#
# Copyright (c) 1983 Regents of the University of California.
# All rights reserved.  The Berkeley software License Agreement
# specifies the terms and conditions for redistribution.
#
#	%Z%%M% %I% %E% SMI; from UCB 5.3 9/7/85
#
BINS= restore
OBJS= dirs.o interactive.o main.o restore.o \
	symtab.o tape.o utilities.o dumprmt.o
SRCS= $(OBJS:.o=.c)
HDRS= restore.h

LDFLAGS= -Bstatic
CFLAGS= -DRRESTORE -Dsunos -O -I.

.KEEP_STATE:

.INIT: $(HDRS)

all: $(BINS)

$(BINS): $(OBJS) $(DUMPOBJS)
	cc -o $@ $(OBJS) $(DUMPOBJS)

install: $(BINS)
	install -d $(DESTDIR)/usr/etc
	install -s -m 4755 $(BINS) $(DESTDIR)/usr/etc
	-rm -f $(DESTDIR)/usr/etc/rrestore
	ln -s restore $(DESTDIR)/usr/etc/rrestore

clean:
	$(RM) $(BINS) $(OBJS) $(DUMPOBJS)

lint: $(SRCS)
	$(LINT.c) $(SRCS)

print:
	@pr /usr/include/protocols/dumprestore.h restore.h $(SRCS) $(DUMPSRCS)
