# $XConsortium: Makefile,v 5.7 93/01/04 18:19:19 hersh Exp $
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


# Makefile for InsPEX C-based test programs

# an arbitrary default - real values are supplied on make command
# line by inspex.sh
PEXINCDIR = /home/`hostname`/pex/include
PEXLIBDIR = /home/`hostname`/pex/lib
# these may be needed if different from above
XINCDIR = /home/`hostname`/pex/include
XLIBDIR = /home/`hostname`/pex/lib

# default is empty for these user-supplied flags
I_CFLAGS = 
I_LDFLAGS =

PEXINCLUDE = -I$(PEXINCDIR) -I$(XINCDIR)
INSPEXINCLUDE = -I$(INSPEXHOME)/tools/pexint -I$(INSPEXDEST)/include
PEXLIB = -L$(PEXLIBDIR)  -L$(XLIBDIR)
INSPEXLIB = -L$(INSPEXDEST)/lib
LIBS = $(INSPEXDEST)/lib/libinspex.a $(PEXLIBDIR)/libphigs.a -lX11 -lm -lXext

LDFLAGS = -g $(I_LDFLAGS) $(PEXLIB) $(INSPEXLIB) $(LIBS)
CFLAGS = -g  $(I_CFLAGS) $(CPPFLAGS) $(PEXINCLUDE) $(INSPEXINCLUDE)

CTESTS = elemcon9 copyall2 errhandle1 errhandle2\
	pdt wdt1 wdt2 wdt3 wdt4 wdt5 wdt6

TARGET = $(CTESTS)

$(TARGET): $$@.c $(INSPEXDEST)/lib/libinspex.a
	cc $(CFLAGS)  $@.c -o $@ $(LDFLAGS)

$(INSPEXDEST)/lib/libinspex.a:
	cd $(INSPEXHOME)/tools/pexint; \
	make PEXINCDIR=$(PEXINCDIR) PEXLIBDIR=$(PEXLIBDIR) libinspex.a



