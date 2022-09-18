# $XConsortium: Makefile,v 5.3 91/02/16 09:59:48 rws Exp $
###################################################################
# Copyright (c) 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.
# 
#                         All Rights Reserved
# 
# Permission to use, copy, modify, and distribute this software and its 
# documentation for any purpose and without fee is hereby granted, 
# provided that the above copyright notice appear in all copies and that
# both that copyright notice and this permission notice appear in 
# supporting documentation, and that the names of Sun Microsystems,
# the X Consortium, and MIT not be used in advertising or publicity 
# pertaining to distribution of the software without specific, written 
# prior permission.  
# 
# SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
# INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
# SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
# DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
# ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
# SOFTWARE.
#
##################################################################


# Makefile for Newt library and ipp (interpreter pre-processor).
# Default target is to make both, and clean up intermediate files. 

#destination directory for objects, intermediate files, and the libnewt.a 
# library (or destination directory for a "copy").
DESTDIR = .
# Newt directory, where "make" is performed
# (needed because lex and yacc require a cd)
MAKEDIR = .

# default is empty for this user-configuration flag:
I_CFLAGS =

SRC = Makefile config.h debugger.c debugger.h interpret.c interpret.h \
	ipp.c looper.h looper.yacc looper.lex var.c var.h

CFLAGS = -g $(I_CFLAGS) -I$(MAKEDIR) 
OBJS =  $(DESTDIR)/y.tab.o $(DESTDIR)/var.o $(DESTDIR)/interpret.o $(DESTDIR)/debugger.o 

default: $(DESTDIR)/libnewt.a $(DESTDIR)/ipp clean

src: $(SRC)

copy: 
	cp $(SRC) $(DESTDIR)

$(DESTDIR)/libnewt.a: $(OBJS) 
	ar cr $@ $(OBJS)
	ranlib $@ 

$(DESTDIR)/lex.yy.c: looper.lex
	cd $(DESTDIR); lex $(MAKEDIR)/looper.lex

$(DESTDIR)/y.tab.c: looper.yacc 
	cd $(DESTDIR); yacc $(MAKEDIR)/looper.yacc

$(DESTDIR)/y.tab.o: $(DESTDIR)/y.tab.c $(DESTDIR)/lex.yy.c var.h looper.h \
debugger.h interpret.h
	cc $(CFLAGS) -o $@ -c $(DESTDIR)/y.tab.c

$(DESTDIR)/var.o: var.c var.h looper.h
	cc $(CFLAGS) -o $@ -c var.c

$(DESTDIR)/interpret.o: config.h interpret.c looper.h
	cc $(CFLAGS) -o $@ -c interpret.c

$(DESTDIR)/debugger.o: debugger.c debugger.h looper.h
	cc $(CFLAGS) -o $@ -c debugger.c

$(DESTDIR)/ipp: ipp.c config.h
	cc $(CFLAGS) -o $(DESTDIR)/ipp ipp.c

clean:
	rm -f $(DESTDIR)/lex.yy.c $(DESTDIR)/y.tab.c  $(OBJS) 
