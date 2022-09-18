# $XConsortium: Makefile,v 5.3 91/07/08 18:18:28 hersh Exp $
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

# Makefile for Inspector, the InsPEX image comparison tool
# note: give CPPFLAGS=-DBUG to work around old server bits_per_rgb bug

# Destination directory for objects and the executable
INSPEXDEST  = /tmp/inspex_test
DESTBIN = $(INSPEXDEST)/bin

# X11 libs and include directory
XVIEWHOME = /usr/openwin

# required libraries for XView and Athena Widgets:
XVLIBS = -lxview -lolgx -lX11 -lm
AWLIBS = -lXaw -lXmu -lXt -lXext -lX11 -lm

CFLAGS= -g  -I$(XVIEWHOME)/share/include $(CPPFLAGS)

#LDFLAGS=-Bstatic -L$(XVIEWHOME)/lib $(XVLIBS)
LDFLAGS=-L$(XVIEWHOME)/lib $(XVLIBS)

#AW_LDFLAGS=-Bstatic -L$(XVIEWHOME)/lib $(AWLIBS)
AW_LDFLAGS=$(AWLIBS)

SRC = Makefile inspector.c imagelib.c imagelib.h portable.h \
	toolkit.c toolkit.h toolkitaw.c toolkitaw.h

OBJ = $(DESTBIN)/inspector.o $(DESTBIN)/toolkit.o $(DESTBIN)/imagelib.o 
AWOBJ = $(DESTBIN)/awinspector.o $(DESTBIN)/toolkitaw.o $(DESTBIN)/imagelib.o 

src: $(SRC)

copy:
	cp $(SRC) $(DESTDIR)

inspector: $(DESTBIN)/inspector

$(DESTBIN)/imagelib.o: imagelib.c imagelib.h portable.h
	$(CC) $(CFLAGS) -o $@ -c imagelib.c

$(DESTBIN)/toolkit.o: toolkit.c toolkit.h
	$(CC) $(CFLAGS) -o $@ -c toolkit.c

$(DESTBIN)/inspector.o: inspector.c toolkit.h imagelib.h 
	$(CC) $(CFLAGS) -o $@ -c inspector.c

$(DESTBIN)/inspector: $(OBJ)
	$(CC) -o $(DESTBIN)/inspector $(OBJ) $(LDFLAGS)

# targets for Athena Widgets version: uses different toolkit files,
# and a separate compilation of inspector.c (awinspector.o)
# using the different toolkit header file.

awinspector: $(DESTBIN)/awinspector

$(DESTBIN)/toolkitaw.o: toolkitaw.c toolkitaw.h
	$(CC) $(CFLAGS) -o $@ -c toolkitaw.c

$(DESTBIN)/awinspector.o: inspector.c toolkitaw.h imagelib.h 
	$(CC) -DATHENA $(CFLAGS) -o $@ -c inspector.c

$(DESTBIN)/awinspector: $(AWOBJ)
	$(CC) -o $@ $(AWOBJ) $(AW_LDFLAGS)
	


