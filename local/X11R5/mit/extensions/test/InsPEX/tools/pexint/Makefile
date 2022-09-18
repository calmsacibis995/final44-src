
# $XConsortium: Makefile,v 5.7 93/01/04 18:18:39 hersh Exp $
###################################################################
# Copyright (c) 1989, 1990, 1991,1990 by Sun Microsystems, Inc. and the X Consortium.
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


# Makefile for pexint, the PEX interpreter and libinspex.a, 
# for the InsPEX test suite
# note: give CPPFLAGS=-DBUG to work around SunPEX bits_per_rgb bug
#       give CPPFLAGS=-DNEWT to compile the interpreter

# destination directory for objects and intermediate C files of pexint 
DESTBIN = $(INSPEXDEST)/bin
# destination directory for objects of libinspex.a
DESTLIB = $(INSPEXDEST)/lib
# directories for PEX include and library files
PEXINCDIR = /home/`hostname`/pex/include
PEXLIBDIR = /home/`hostname`/pex/lib
# these flags are for any specialized compile flags; empty by default
I_CFLAGS = 
I_LDFLAGS =
#directory for Xlib include and library files - default
# to same as for PEX.
XINCDIR = $(PEXINCDIR)
XLIBDIR = $(PEXLIBDIR)

DEBUGOPT = -g 
IPP = $(DESTBIN)/ipp
SRCDIR = $$INSPEXHOME/tools/pexint
NEWTDIR = $$INSPEXHOME/tools/newt
CFLAGS = $(DEBUGOPT) $(I_CFLAGS) $(CPPFLAGS) -I$(XINCDIR) -I$(PEXINCDIR) -I$(SRCDIR)
LDFLAGS = $(DEBUGOPT) $(I_LDFLAGS) -L$(PEXLIBDIR) -L$(XLIBDIR) 
LIBS = ../../../../lib/PEX/libphigs.a -lX11 -lm -ll -lXext

SRC = Makefile NewTvararg.h computils.c computils.h computils.m \
	config.h datautils.c datautils.h datautils.m imath.h \
	logmsg.c logmsg.h logmsg.m pexapi.h pexapi.k pexapi.m \
	pixutils.c pixutils.h pixutils.m portable.h \
	testutils.c testutils.h testutils.m \
	utility.c utility.h utility.k utility.m \
	xfutils.c xfutils.h xfutils.m xlib.h xlib.k xlib.m

PEXINTOBJS =  $(DESTBIN)/libnewt.a $(DESTBIN)/interface.o $(DESTBIN)/Ipexapi.o \
	$(DESTBIN)/Idatautils.o $(DESTBIN)/Iutility.o $(DESTBIN)/Ixlib.o \
	$(DESTBIN)/computils.o $(DESTBIN)/datautils.o \
	$(DESTBIN)/utility.o $(DESTBIN)/pixutils.o $(DESTBIN)/xfutils.o \
	$(DESTBIN)/testutils.o $(DESTBIN)/logmsg.o 

LIBINSPEXOBJS =  \
	$(DESTLIB)/computils.o $(DESTLIB)/datautils.o \
	$(DESTLIB)/utility.o $(DESTLIB)/pixutils.o $(DESTLIB)/xfutils.o \
	$(DESTLIB)/testutils.o $(DESTLIB)/logmsg.o 


pexint: $(DESTBIN)/pexint

libinspex.a: $(DESTLIB)/libinspex.a

src: $(SRC)

copy:
	cp $(SRC) $(DESTDIR)

$(DESTBIN)/pexint: $(PEXINTOBJS) 
	cc -o $@ $(LDFLAGS) $(PEXINTOBJS) $(LIBS)

$(DESTLIB)/libinspex.a: $(LIBINSPEXOBJS) 
	ar cr $@ $(LIBINSPEXOBJS)
	ranlib $@

$(DESTBIN)/interface.c: testutils.m xfutils.m computils.m logmsg.m pixutils.m \
xfutils.h testutils.h  computils.h logmsg.h pixutils.h portable.h \
$(DESTBIN)/Ipexapi.c $(DESTBIN)/Idatautils.c \
$(DESTBIN)/Iutility.c  $(DESTBIN)/Ixlib.c $(IPP)
	cat testutils.m xfutils.m computils.m logmsg.m pixutils.m > inspexint.m
	cat testutils.h xfutils.h computils.h logmsg.h pixutils.h > inspexint.h
	$(IPP) -n -i inspexint.h -u Ipexapi \
	-u Idatautils -u Iutility \
	-u Ixlib -l $(DESTBIN)/interface inspexint.m

$(DESTBIN)/Ipexapi.c: pexapi.m pexapi.h pexapi.k $(IPP)
	$(IPP) -n -k pexapi.k -i pexapi.h -l $(DESTBIN)/Ipexapi pexapi.m

$(DESTBIN)/Idatautils.c:  datautils.m datautils.h $(IPP)
	$(IPP) -n -i datautils.h -l $(DESTBIN)/Idatautils datautils.m 

$(DESTBIN)/Iutility.c: utility.m utility.k utility.h $(IPP)
	$(IPP) -n -k utility.k -i utility.h -l $(DESTBIN)/Iutility utility.m

$(DESTBIN)/Ixlib.c: xlib.m xlib.k xlib.h $(IPP)
	$(IPP) -n -k xlib.k -i xlib.h -l $(DESTBIN)/Ixlib xlib.m

$(DESTBIN)/interface.o: config.h $(DESTBIN)/interface.c inspexint.h
	cc $(CFLAGS) -o $@ -c $(DESTBIN)/interface.c

$(DESTBIN)/pixutils.o $(DESTLIB)/pixutils.o: pixutils.c pixutils.h logmsg.h portable.h
	cc $(CFLAGS) -o $@ -c pixutils.c

$(DESTBIN)/utility.o $(DESTLIB)/utility.o: utility.c utility.h
	cc $(CFLAGS) -o $@ -c utility.c

$(DESTBIN)/xfutils.o $(DESTLIB)/xfutils.o: xfutils.c imath.h logmsg.h xfutils.h
	cc $(CFLAGS) -o $@ -c xfutils.c

$(DESTBIN)/testutils.o $(DESTLIB)/testutils.o: testutils.c testutils.h NewTvararg.h imath.h pixutils.h logmsg.h portable.h
	cc $(CFLAGS) -o $@ -c testutils.c

$(DESTBIN)/datautils.o $(DESTLIB)/datautils.o: datautils.c datautils.h NewTvararg.h
	cc $(CFLAGS) -o $@ -c datautils.c

$(DESTBIN)/logmsg.o $(DESTLIB)/logmsg.o: logmsg.c logmsg.h
	cc $(CFLAGS) -o $@ -c logmsg.c

$(DESTBIN)/computils.o $(DESTLIB)/computils.o: computils.c computils.h logmsg.h imath.h NewTvararg.h
	cc $(CFLAGS) -o $@ -c computils.c

$(DESTBIN)/Ipexapi.o: config.h $(DESTBIN)/Ipexapi.c
	cc $(CFLAGS) -o $@ -c $(DESTBIN)/Ipexapi.c

$(DESTBIN)/Iutility.o: config.h $(DESTBIN)/Iutility.c
	cc $(CFLAGS) -o $@ -c $(DESTBIN)/Iutility.c

$(DESTBIN)/Ixlib.o: config.h $(DESTBIN)/Ixlib.c
	cc $(CFLAGS) -o $@ -c $(DESTBIN)/Ixlib.c

$(DESTBIN)/Idatautils.o: config.h $(DESTBIN)/Idatautils.c
	cc $(CFLAGS) -o $@ -c $(DESTBIN)/Idatautils.c

$(DESTBIN)/libnewt.a:
	cd $(NEWTDIR); \
	make DESTDIR=$(DESTBIN) MAKEDIR=$(NEWTDIR) $(DESTBIN)/libnewt.a

$(DESTBIN)/ipp:
	cd $(NEWTDIR) ; \
	make DESTDIR=$(DESTBIN) MAKEDIR=$(NEWTDIR) $(DESTBIN)/ipp
clean:
	rm -f $(DESTBIN)/interface.[cho] core $(DESTBIN)/I*.[cho] 

