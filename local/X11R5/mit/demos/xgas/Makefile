# Makefile generated by imake - do not edit!
# $XConsortium: imake.c,v 1.51 89/12/12 12:37:30 jim Exp $

# -------------------------------------------------------------------------
# Makefile generated from "Imake.tmpl" and <Imakefile>
# $XConsortium: Imake.tmpl,v 1.139 91/09/16 08:52:48 rws Exp $
#
# Platform-specific parameters may be set in the appropriate <vendor>.cf
# configuration files.  Site-specific parameters should be set in the file
# site.def.  Full rebuilds are recommended if any parameters are changed.
#
# If your C preprocessor does not define any unique symbols, you will need
# to set BOOTSTRAPCFLAGS when rebuilding imake (usually when doing
# "make World" the first time).
#

# -------------------------------------------------------------------------
# site-specific configuration parameters that need to come before
# the platform-specific parameters - edit site.def to change

# site:  $XConsortium: site.def,v 1.2 91/07/30 20:26:44 rws Exp $

# -------------------------------------------------------------------------
# platform-specific configuration parameters - edit hpbsd.cf to change

# platform:  $XConsortium: hpbsd.cf,v 1.1 91/09/27 12:10:52 mark Exp $

# operating system:             BSD 4.4Alpha

# -------------------------------------------------------------------------
# site-specific configuration parameters that go after
# the platform-specific parameters - edit site.def to change

# site:  $XConsortium: site.def,v 1.2 91/07/30 20:26:44 rws Exp $

            SHELL = 	/bin/sh

              TOP = ../../.
      CURRENT_DIR = ./demos/xgas

               AR = ar clq
  BOOTSTRAPCFLAGS =
               CC = gcc
               AS = as

         COMPRESS = compress
              CPP = /usr/libexec/gcc2/cpp $(STD_CPP_DEFINES)
    PREPROCESSCMD = gcc -E $(STD_CPP_DEFINES)
          INSTALL = install
               LD = ld
             LINT = lint
      LINTLIBFLAG = -C
         LINTOPTS = -axz
               LN = ln -s
             MAKE = make
               MV = mv
               CP = cp

           RANLIB = ranlib
  RANLIBINSTFLAGS =

               RM = rm -f
            TROFF = psroff
         MSMACROS = -ms
              TBL = tbl
              EQN = eqn
     STD_INCLUDES =
  STD_CPP_DEFINES = -traditional
      STD_DEFINES =
 EXTRA_LOAD_FLAGS =
  EXTRA_LIBRARIES =
             TAGS = ctags

    PROTO_DEFINES =

     INSTPGMFLAGS =

     INSTBINFLAGS = -m 0755
     INSTUIDFLAGS = -m 4755
     INSTLIBFLAGS = -m 0644
     INSTINCFLAGS = -m 0444
     INSTMANFLAGS = -m 0444
     INSTDATFLAGS = -m 0444
    INSTKMEMFLAGS = -g kmem -m 2755

     TOP_INCLUDES = -I$(TOP)

      CDEBUGFLAGS = -O
        CCOPTIONS =

      ALLINCLUDES = $(INCLUDES) $(EXTRA_INCLUDES) $(TOP_INCLUDES) $(STD_INCLUDES)
       ALLDEFINES = $(ALLINCLUDES) $(STD_DEFINES) $(EXTRA_DEFINES) $(PROTO_DEFINES) $(DEFINES)
           CFLAGS = $(CDEBUGFLAGS) $(CCOPTIONS) $(ALLDEFINES)
        LINTFLAGS = $(LINTOPTS) -DLINT $(ALLDEFINES)

           LDLIBS = $(SYS_LIBRARIES) $(EXTRA_LIBRARIES)

        LDOPTIONS = $(CDEBUGFLAGS) $(CCOPTIONS) $(LOCAL_LDFLAGS)

   LDCOMBINEFLAGS = -X -r
      DEPENDFLAGS =

        MACROFILE = hpbsd.cf
           RM_CMD = $(RM) *.CKP *.ln *.BAK *.bak *.o core errs ,* *~ *.a .emacs_* tags TAGS make.log MakeOut

    IMAKE_DEFINES =

         IRULESRC = $(CONFIGSRC)
        IMAKE_CMD = $(NEWTOP)$(IMAKE) -I$(NEWTOP)$(IRULESRC) $(IMAKE_DEFINES)

     ICONFIGFILES = $(IRULESRC)/Imake.tmpl $(IRULESRC)/Imake.rules 			$(IRULESRC)/Project.tmpl $(IRULESRC)/site.def 			$(IRULESRC)/$(MACROFILE) $(EXTRA_ICONFIGFILES)

# -------------------------------------------------------------------------
# X Window System Build Parameters
# $XConsortium: Project.tmpl,v 1.138.1.1 92/11/11 09:49:19 rws Exp $

# -------------------------------------------------------------------------
# X Window System make variables; this need to be coordinated with rules

          PATHSEP = /
        USRLIBDIR = /usr/lib
           BINDIR = /usr/bin/X11
          INCROOT = /usr/include
     BUILDINCROOT = $(TOP)
      BUILDINCDIR = $(BUILDINCROOT)/X11
      BUILDINCTOP = ..
           INCDIR = $(INCROOT)/X11
           ADMDIR = /usr/adm
           LIBDIR = $(USRLIBDIR)/X11
        CONFIGDIR = $(LIBDIR)/config
       LINTLIBDIR = $(USRLIBDIR)/lint

          FONTDIR = $(LIBDIR)/fonts
         XINITDIR = $(LIBDIR)/xinit
           XDMDIR = $(LIBDIR)/xdm
           TWMDIR = $(LIBDIR)/twm
          MANPATH = /usr/man
    MANSOURCEPATH = $(MANPATH)/man
        MANSUFFIX = n
     LIBMANSUFFIX = 3
           MANDIR = $(MANSOURCEPATH)$(MANSUFFIX)
        LIBMANDIR = $(MANSOURCEPATH)$(LIBMANSUFFIX)
           NLSDIR = $(LIBDIR)/nls
        PEXAPIDIR = $(LIBDIR)/PEX
      XAPPLOADDIR = $(LIBDIR)/app-defaults
       FONTCFLAGS = -t

     INSTAPPFLAGS = $(INSTDATFLAGS)

            IMAKE = $(IMAKESRC)/imake
           DEPEND = $(DEPENDSRC)/makedepend
              RGB = $(RGBSRC)/rgb

            FONTC = $(BDFTOPCFSRC)/bdftopcf

        MKFONTDIR = $(MKFONTDIRSRC)/mkfontdir
        MKDIRHIER = 	/bin/sh $(SCRIPTSRC)/mkdirhier.sh

        CONFIGSRC = $(TOP)/config
       DOCUTILSRC = $(TOP)/doc/util
        CLIENTSRC = $(TOP)/clients
          DEMOSRC = $(TOP)/demos
           LIBSRC = $(TOP)/lib
          FONTSRC = $(TOP)/fonts
       INCLUDESRC = $(TOP)/X11
        SERVERSRC = $(TOP)/server
          UTILSRC = $(TOP)/util
        SCRIPTSRC = $(UTILSRC)/scripts
       EXAMPLESRC = $(TOP)/examples
       CONTRIBSRC = $(TOP)/../contrib
           DOCSRC = $(TOP)/doc
           RGBSRC = $(TOP)/rgb
        DEPENDSRC = $(UTILSRC)/makedepend
         IMAKESRC = $(CONFIGSRC)
         XAUTHSRC = $(LIBSRC)/Xau
          XLIBSRC = $(LIBSRC)/X
           XMUSRC = $(LIBSRC)/Xmu
       TOOLKITSRC = $(LIBSRC)/Xt
       AWIDGETSRC = $(LIBSRC)/Xaw
       OLDXLIBSRC = $(LIBSRC)/oldX
      XDMCPLIBSRC = $(LIBSRC)/Xdmcp
      BDFTOSNFSRC = $(FONTSRC)/bdftosnf
      BDFTOSNFSRC = $(FONTSRC)/clients/bdftosnf
      BDFTOPCFSRC = $(FONTSRC)/clients/bdftopcf
     MKFONTDIRSRC = $(FONTSRC)/clients/mkfontdir
         FSLIBSRC = $(FONTSRC)/lib/fs
    FONTSERVERSRC = $(FONTSRC)/server
     EXTENSIONSRC = $(TOP)/extensions
         XILIBSRC = $(EXTENSIONSRC)/lib/xinput
        PEXLIBSRC = $(EXTENSIONSRC)/lib/PEXlib
      PHIGSLIBSRC = $(EXTENSIONSRC)/lib/PEX

  DEPEXTENSIONLIB = $(EXTENSIONSRC)/lib/libXext.a
     EXTENSIONLIB = 			  $(DEPEXTENSIONLIB)

          DEPXLIB = $(DEPEXTENSIONLIB) $(XLIBSRC)/libX11.a
             XLIB = $(EXTENSIONLIB) 			 $(XLIBSRC)/libX11.a

      DEPXAUTHLIB = $(XAUTHSRC)/libXau.a
         XAUTHLIB = 			 $(DEPXAUTHLIB)
      DEPXDMCPLIB = $(XDMCPLIBSRC)/libXdmcp.a
         XDMCPLIB = 			 $(DEPXDMCPLIB)

        DEPXMULIB = $(XMUSRC)/libXmu.a
           XMULIB = 			 $(DEPXMULIB)

       DEPOLDXLIB = $(OLDXLIBSRC)/liboldX.a
          OLDXLIB = 			 $(DEPOLDXLIB)

      DEPXTOOLLIB = $(TOOLKITSRC)/libXt.a
         XTOOLLIB = 			 $(DEPXTOOLLIB)

        DEPXAWLIB = $(AWIDGETSRC)/libXaw.a
           XAWLIB = 			 $(DEPXAWLIB)

        DEPXILIB = $(XILIBSRC)/libXi.a
           XILIB = 			 $(DEPXILIB)

       DEPPEXLIB = $(PEXLIBSRC)/libPEX5.a
          PEXLIB = 			 $(DEPPEXLIB)

        DEPPHIGSLIB = $(PHIGSLIBSRC)/libphigs.a
           PHIGSLIB = 			 $(DEPPHIGSLIB)

       DEPXBSDLIB = $(LIBSRC)/Berk/libXbsd.a
          XBSDLIB = 			 $(DEPXBSDLIB)

 LINTEXTENSIONLIB = $(EXTENSIONSRC)/lib/llib-lXext.ln
         LINTXLIB = $(XLIBSRC)/llib-lX11.ln
          LINTXMU = $(XMUSRC)/llib-lXmu.ln
        LINTXTOOL = $(TOOLKITSRC)/llib-lXt.ln
          LINTXAW = $(AWIDGETSRC)/llib-lXaw.ln
           LINTXI = $(XILIBSRC)/llib-lXi.ln
          LINTPEX = $(PEXLIBSRC)/llib-lPEX5.ln
        LINTPHIGS = $(PHIGSLIBSRC)/llib-lphigs.ln

          DEPLIBS = $(LOCAL_LIBRARIES)

         DEPLIBS1 = $(DEPLIBS)
         DEPLIBS2 = $(DEPLIBS)
         DEPLIBS3 = $(DEPLIBS)

# -------------------------------------------------------------------------
# Imake rules for building libraries, programs, scripts, and data files
# rules:  $XConsortium: Imake.rules,v 1.123 91/09/16 20:12:16 rws Exp $

# -------------------------------------------------------------------------
# start of Imakefile

# $XConsortium: Imakefile,v 1.7 91/08/26 13:34:51 rws Exp $
#
#  xgas
#
#  Copyright 1987, 1988 Massachusetts Institute of Technology
#
#  Permission to use, copy, modify, and distribute this software and its
#  documentation for any purpose and without fee is hereby granted, provided
#  that the above copyright notice appear in all copies and that both that
#  copyright notice and this permission notice appear in supporting
#  documentation, and that the name of M.I.T. not be used in advertising or
#  publicity pertaining to distribution of the software without specific,
#  written prior permission.  M.I.T. makes no representations about the
#  suitability of this software for any purpose.  It is provided "as is"
#  without express or implied warranty.
#
#  Author:    Dave Sternlicht X Consortium
#  Created:   November 27, 1990.
#  Modified to convert nroff to c:   Larry Medwin, April 14, 1991
#

        DEFINES = $(IEEE_DEFS) $(SIGNAL_DEFINES)
        DEPLIBS = $(DEPXAWLIB) $(DEPXMULIB) $(DEPXTOOLLIB) $(DEPXLIB)
LOCAL_LIBRARIES = $(XAWLIB) $(XMULIB) $(XTOOLLIB) $(XLIB)
  SYS_LIBRARIES = -lm
           DOCNS = doc.n quick.n
           DOCSRCS = doc.c quick.c
           DOCOBJS = doc.o quick.o
           SRCS = main.c dynamics.c chamber.c timestep.c molecule.c util.c                   help.c XGas.c $(DOCSRCS) man.c

           OBJS = main.o dynamics.o chamber.o timestep.o molecule.o util.o                   help.o XGas.o $(DOCOBJS) man.o

       INCLUDES = -I$(TOOLKITSRC) -I$(TOP)

 PROGRAM = xgas

all:: xgas

xgas: $(OBJS) $(DEPLIBS)
	$(RM) $@
	$(CC) -o $@ $(OBJS) $(LDOPTIONS) $(LOCAL_LIBRARIES) $(LDLIBS) $(EXTRA_LOAD_FLAGS)

saber_xgas:: $(SRCS)
	# load $(ALLDEFINES) $(SRCS) $(LOCAL_LIBRARIES) $(SYS_LIBRARIES) $(EXTRA_LIBRARIES)

osaber_xgas:: $(OBJS)
	# load $(ALLDEFINES) $(OBJS) $(LOCAL_LIBRARIES) $(SYS_LIBRARIES) $(EXTRA_LIBRARIES)

install:: xgas
	-@if [ -d $(DESTDIR)$(BINDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(BINDIR)); fi
	$(INSTALL) -c $(INSTPGMFLAGS)  xgas $(DESTDIR)$(BINDIR)

install.man:: xgas.man
	-@if [ -d $(DESTDIR)$(MANDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(MANDIR)); fi
	$(INSTALL) -c $(INSTMANFLAGS) xgas.man $(DESTDIR)$(MANDIR)/xgas.$(MANSUFFIX)

depend:: $(DEPEND)

$(DEPEND):
	@echo "checking $@ over in $(DEPENDSRC) first..."; \
	cd $(DEPENDSRC); $(MAKE); \
	echo "okay, continuing in $(CURRENT_DIR)"

depend::
	$(DEPEND) $(DEPENDFLAGS) -s "# DO NOT DELETE" -- $(ALLDEFINES) -- $(SRCS)

lint:
	$(LINT) $(LINTFLAGS) $(SRCS) $(LINTLIBS)
lint1:
	$(LINT) $(LINTFLAGS) $(FILE) $(LINTLIBS)

clean::
	$(RM) $(PROGRAM)

install:: XGas.ad
	-@if [ -d $(DESTDIR)$(XAPPLOADDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(XAPPLOADDIR)); fi
	$(INSTALL) -c $(INSTAPPFLAGS) XGas.ad $(DESTDIR)$(XAPPLOADDIR)/XGas

depend:: $(SRCS) $(DOCNS)

$(DOCSRCS):: $(DOCNS)

# -------------------------------------------------------------------------
# common rules for all Makefiles - do not edit

emptyrule::

clean::
	$(RM_CMD) "#"*

Makefile:: $(IMAKE)

$(IMAKE):
	@(cd $(IMAKESRC); if [ -f Makefile ]; then \
	echo "checking $@ in $(IMAKESRC) first..."; $(MAKE) all; else \
	echo "bootstrapping $@ from Makefile.ini in $(IMAKESRC) first..."; \
	$(MAKE) -f Makefile.ini BOOTSTRAPCFLAGS="$(BOOTSTRAPCFLAGS)"; fi; \
	echo "okay, continuing in $(CURRENT_DIR)")

Makefile::
	-@if [ -f Makefile ]; then set -x; \
	$(RM) Makefile.bak; $(MV) Makefile Makefile.bak; \
	else exit 0; fi
	$(IMAKE_CMD) -DTOPDIR=$(TOP) -DCURDIR=$(CURRENT_DIR)

tags::
	$(TAGS) -w *.[ch]
	$(TAGS) -xw *.[ch] > TAGS

saber:
	# load $(ALLDEFINES) $(SRCS)

osaber:
	# load $(ALLDEFINES) $(OBJS)

# -------------------------------------------------------------------------
# empty rules for directories that do not have SUBDIRS - do not edit

install::
	@echo "install in $(CURRENT_DIR) done"

install.man::
	@echo "install.man in $(CURRENT_DIR) done"

Makefiles::

includes::

# -------------------------------------------------------------------------
# dependencies generated by makedepend

# DO NOT DELETE

main.o: xgas.h ../.././X11/StringDefs.h ../.././X11/Intrinsic.h
main.o: ../.././X11/Xlib.h /usr/include/sys/types.h
main.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
main.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
main.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
main.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
main.o: /usr/include/string.h ../.././X11/Core.h ../.././X11/Composite.h
main.o: ../.././X11/Constraint.h ../.././X11/Object.h ../.././X11/RectObj.h
main.o: ../.././X11/Xaw/Form.h ../.././X11/Xaw/Command.h
main.o: ../.././X11/Xaw/Label.h ../.././X11/Xaw/Simple.h
main.o: ../.././X11/Xmu/Converters.h ../.././X11/Xaw/Scrollbar.h
main.o: ../.././X11/Xaw/Box.h ../.././X11/Xaw/AsciiText.h
main.o: ../.././X11/Xaw/Text.h ../.././X11/Xaw/TextSink.h
main.o: ../.././X11/Xaw/TextSrc.h ../.././X11/Xaw/AsciiSrc.h
main.o: ../.././X11/Xaw/AsciiSink.h ../.././X11/Xaw/Toggle.h XGas.h
main.o: /usr/include/math.h xgas.icon ../.././X11/Shell.h
dynamics.o: xgas.h ../.././X11/StringDefs.h ../.././X11/Intrinsic.h
dynamics.o: ../.././X11/Xlib.h /usr/include/sys/types.h
dynamics.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
dynamics.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
dynamics.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
dynamics.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
dynamics.o: /usr/include/string.h ../.././X11/Core.h ../.././X11/Composite.h
dynamics.o: ../.././X11/Constraint.h ../.././X11/Object.h
dynamics.o: ../.././X11/RectObj.h ../.././X11/Xaw/Form.h
dynamics.o: ../.././X11/Xaw/Command.h ../.././X11/Xaw/Label.h
dynamics.o: ../.././X11/Xaw/Simple.h ../.././X11/Xmu/Converters.h
dynamics.o: ../.././X11/Xaw/Scrollbar.h ../.././X11/Xaw/Box.h
dynamics.o: ../.././X11/Xaw/AsciiText.h ../.././X11/Xaw/Text.h
dynamics.o: ../.././X11/Xaw/TextSink.h ../.././X11/Xaw/TextSrc.h
dynamics.o: ../.././X11/Xaw/AsciiSrc.h ../.././X11/Xaw/AsciiSink.h
dynamics.o: ../.././X11/Xaw/Toggle.h XGas.h /usr/include/math.h
chamber.o: xgas.h ../.././X11/StringDefs.h ../.././X11/Intrinsic.h
chamber.o: ../.././X11/Xlib.h /usr/include/sys/types.h
chamber.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
chamber.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
chamber.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
chamber.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
chamber.o: /usr/include/string.h ../.././X11/Core.h ../.././X11/Composite.h
chamber.o: ../.././X11/Constraint.h ../.././X11/Object.h
chamber.o: ../.././X11/RectObj.h ../.././X11/Xaw/Form.h
chamber.o: ../.././X11/Xaw/Command.h ../.././X11/Xaw/Label.h
chamber.o: ../.././X11/Xaw/Simple.h ../.././X11/Xmu/Converters.h
chamber.o: ../.././X11/Xaw/Scrollbar.h ../.././X11/Xaw/Box.h
chamber.o: ../.././X11/Xaw/AsciiText.h ../.././X11/Xaw/Text.h
chamber.o: ../.././X11/Xaw/TextSink.h ../.././X11/Xaw/TextSrc.h
chamber.o: ../.././X11/Xaw/AsciiSrc.h ../.././X11/Xaw/AsciiSink.h
chamber.o: ../.././X11/Xaw/Toggle.h XGas.h /usr/include/math.h
timestep.o: xgas.h ../.././X11/StringDefs.h ../.././X11/Intrinsic.h
timestep.o: ../.././X11/Xlib.h /usr/include/sys/types.h
timestep.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
timestep.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
timestep.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
timestep.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
timestep.o: /usr/include/string.h ../.././X11/Core.h ../.././X11/Composite.h
timestep.o: ../.././X11/Constraint.h ../.././X11/Object.h
timestep.o: ../.././X11/RectObj.h ../.././X11/Xaw/Form.h
timestep.o: ../.././X11/Xaw/Command.h ../.././X11/Xaw/Label.h
timestep.o: ../.././X11/Xaw/Simple.h ../.././X11/Xmu/Converters.h
timestep.o: ../.././X11/Xaw/Scrollbar.h ../.././X11/Xaw/Box.h
timestep.o: ../.././X11/Xaw/AsciiText.h ../.././X11/Xaw/Text.h
timestep.o: ../.././X11/Xaw/TextSink.h ../.././X11/Xaw/TextSrc.h
timestep.o: ../.././X11/Xaw/AsciiSrc.h ../.././X11/Xaw/AsciiSink.h
timestep.o: ../.././X11/Xaw/Toggle.h XGas.h /usr/include/math.h
molecule.o: xgas.h ../.././X11/StringDefs.h ../.././X11/Intrinsic.h
molecule.o: ../.././X11/Xlib.h /usr/include/sys/types.h
molecule.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
molecule.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
molecule.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
molecule.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
molecule.o: /usr/include/string.h ../.././X11/Core.h ../.././X11/Composite.h
molecule.o: ../.././X11/Constraint.h ../.././X11/Object.h
molecule.o: ../.././X11/RectObj.h ../.././X11/Xaw/Form.h
molecule.o: ../.././X11/Xaw/Command.h ../.././X11/Xaw/Label.h
molecule.o: ../.././X11/Xaw/Simple.h ../.././X11/Xmu/Converters.h
molecule.o: ../.././X11/Xaw/Scrollbar.h ../.././X11/Xaw/Box.h
molecule.o: ../.././X11/Xaw/AsciiText.h ../.././X11/Xaw/Text.h
molecule.o: ../.././X11/Xaw/TextSink.h ../.././X11/Xaw/TextSrc.h
molecule.o: ../.././X11/Xaw/AsciiSrc.h ../.././X11/Xaw/AsciiSink.h
molecule.o: ../.././X11/Xaw/Toggle.h XGas.h /usr/include/math.h
util.o: xgas.h ../.././X11/StringDefs.h ../.././X11/Intrinsic.h
util.o: ../.././X11/Xlib.h /usr/include/sys/types.h
util.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
util.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
util.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
util.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
util.o: /usr/include/string.h ../.././X11/Core.h ../.././X11/Composite.h
util.o: ../.././X11/Constraint.h ../.././X11/Object.h ../.././X11/RectObj.h
util.o: ../.././X11/Xaw/Form.h ../.././X11/Xaw/Command.h
util.o: ../.././X11/Xaw/Label.h ../.././X11/Xaw/Simple.h
util.o: ../.././X11/Xmu/Converters.h ../.././X11/Xaw/Scrollbar.h
util.o: ../.././X11/Xaw/Box.h ../.././X11/Xaw/AsciiText.h
util.o: ../.././X11/Xaw/Text.h ../.././X11/Xaw/TextSink.h
util.o: ../.././X11/Xaw/TextSrc.h ../.././X11/Xaw/AsciiSrc.h
util.o: ../.././X11/Xaw/AsciiSink.h ../.././X11/Xaw/Toggle.h XGas.h
util.o: /usr/include/math.h
help.o: xgas.h ../.././X11/StringDefs.h ../.././X11/Intrinsic.h
help.o: ../.././X11/Xlib.h /usr/include/sys/types.h
help.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
help.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
help.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
help.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
help.o: /usr/include/string.h ../.././X11/Core.h ../.././X11/Composite.h
help.o: ../.././X11/Constraint.h ../.././X11/Object.h ../.././X11/RectObj.h
help.o: ../.././X11/Xaw/Form.h ../.././X11/Xaw/Command.h
help.o: ../.././X11/Xaw/Label.h ../.././X11/Xaw/Simple.h
help.o: ../.././X11/Xmu/Converters.h ../.././X11/Xaw/Scrollbar.h
help.o: ../.././X11/Xaw/Box.h ../.././X11/Xaw/AsciiText.h
help.o: ../.././X11/Xaw/Text.h ../.././X11/Xaw/TextSink.h
help.o: ../.././X11/Xaw/TextSrc.h ../.././X11/Xaw/AsciiSrc.h
help.o: ../.././X11/Xaw/AsciiSink.h ../.././X11/Xaw/Toggle.h XGas.h
help.o: /usr/include/math.h ../.././X11/Shell.h
XGas.o: ../.././X11/IntrinsicP.h ../.././X11/Intrinsic.h ../.././X11/Xlib.h
XGas.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGas.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGas.o: /usr/include/machine/types.h ../.././X11/X.h ../.././X11/Xfuncproto.h
XGas.o: ../.././X11/Xosdefs.h /usr/include/stddef.h ../.././X11/Xutil.h
XGas.o: ../.././X11/Xresource.h /usr/include/string.h ../.././X11/Core.h
XGas.o: ../.././X11/Composite.h ../.././X11/Constraint.h ../.././X11/Object.h
XGas.o: ../.././X11/RectObj.h ../.././X11/CoreP.h ../.././X11/CompositeP.h
XGas.o: ../.././X11/ConstrainP.h ../.././X11/ObjectP.h ../.././X11/RectObjP.h
XGas.o: ../.././X11/StringDefs.h XGasP.h XGas.h
