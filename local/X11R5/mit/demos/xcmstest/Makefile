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
      CURRENT_DIR = ./demos/xcmstest

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

      SYS_LIBRARIES = -lm

            DEFINES =

            CMD_SRC = TekCMS_LT.c
            CMD_OBJ = TekCMS_LT.o
        LIBTEST_SRC = LibTest.c
        LIBTEST_OBJ = LibTest.o
       TESTINIT_SRC = TestInit.c
       TESTINIT_OBJ = TestInit.o
            TCI_SRC = TekCMS_TCI.c
            TCI_OBJ = TekCMS_TCI.o
           UTIL_SRC = TekCMSutil.c
           UTIL_OBJ = TekCMSutil.o
        GLOBALS_SRC = TekCMSglob.c
        GLOBALS_OBJ = TekCMSglob.o

               SRCS =                       $(LIBTEST_SRC)	                      $(TESTINIT_SRC)	                      $(UTIL_SRC)	                      $(GLOBALS_SRC)	                      $(CMD_SRC)	                      TekCMS_TCI.c

               OBJS =                       $(LIBTEST_OBJ)	                      $(TESTINIT_OBJ)	                      $(UTIL_OBJ)	                      $(GLOBALS_OBJ)	                      $(CMD_OBJ)	                      TekCMS_TCI.o

    LOCAL_LIBRARIES = $(XLIB)
            DEPLIBS = $(DEPXLIB)

 PROGRAM = xcmstest

all:: xcmstest

xcmstest: $(OBJS) $(DEPLIBS)
	$(RM) $@
	$(CC) -o $@ $(OBJS) $(LDOPTIONS) $(LOCAL_LIBRARIES) $(LDLIBS) $(EXTRA_LOAD_FLAGS)

saber_xcmstest:: $(SRCS)
	# load $(ALLDEFINES) $(SRCS) $(LOCAL_LIBRARIES) $(SYS_LIBRARIES) $(EXTRA_LIBRARIES)

osaber_xcmstest:: $(OBJS)
	# load $(ALLDEFINES) $(OBJS) $(LOCAL_LIBRARIES) $(SYS_LIBRARIES) $(EXTRA_LIBRARIES)

install:: xcmstest
	-@if [ -d $(DESTDIR)$(BINDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(BINDIR)); fi
	$(INSTALL) -c $(INSTPGMFLAGS)  xcmstest $(DESTDIR)$(BINDIR)

install.man:: xcmstest.man
	-@if [ -d $(DESTDIR)$(MANDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(MANDIR)); fi
	$(INSTALL) -c $(INSTMANFLAGS) xcmstest.man $(DESTDIR)$(MANDIR)/xcmstest.$(MANSUFFIX)

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

LibTest.o: LibTest.h ../.././X11/Xlib.h /usr/include/sys/types.h
LibTest.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
LibTest.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
LibTest.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
LibTest.o: /usr/include/stddef.h ../.././X11/Xlibint.h ../.././X11/Xproto.h
LibTest.o: ../.././X11/Xmd.h ../.././X11/Xprotostr.h /usr/include/errno.h
LibTest.o: ../.././X11/Xfuncs.h /usr/include/stdlib.h /usr/include/string.h
LibTest.o: /usr/include/stdio.h CmdTbl.h
TestInit.o: LibTest.h ../.././X11/Xlib.h /usr/include/sys/types.h
TestInit.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
TestInit.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
TestInit.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
TestInit.o: /usr/include/stddef.h /usr/include/stdio.h
TestInit.o: /usr/include/sys/stat.h /usr/include/sys/time.h
TestInit.o: /usr/include/sys/time.h ../.././X11/Xutil.h ../.././X11/Xatom.h
TestInit.o: TekCMS_TCI.h
TekCMSutil.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
TekCMSutil.o: /usr/include/machine/ansi.h ../.././X11/Xlib.h
TekCMSutil.o: /usr/include/sys/types.h /usr/include/machine/endian.h
TekCMSutil.o: /usr/include/machine/types.h ../.././X11/X.h
TekCMSutil.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
TekCMSutil.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xatom.h
TekCMSutil.o: ../.././X11/Xcms.h LibTest.h TekCMSglob.h
TekCMSglob.o: LibTest.h ../.././X11/Xlib.h /usr/include/sys/types.h
TekCMSglob.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
TekCMSglob.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
TekCMSglob.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
TekCMSglob.o: /usr/include/stddef.h ../.././X11/Xcms.h
TekCMS_LT.o: LibTest.h /usr/include/stdio.h /usr/include/sys/cdefs.h
TekCMS_LT.o: /usr/include/machine/ansi.h ../.././X11/Xlib.h
TekCMS_LT.o: /usr/include/sys/types.h /usr/include/machine/endian.h
TekCMS_LT.o: /usr/include/machine/types.h ../.././X11/X.h
TekCMS_LT.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
TekCMS_LT.o: /usr/include/stddef.h /usr/include/sys/stat.h
TekCMS_LT.o: /usr/include/sys/time.h /usr/include/sys/time.h
TekCMS_LT.o: ../.././X11/Xcms.h TestInit.h TekCMS_TCI.h TekCMSglob.h
TekCMS_LT.o: TekCMSutil.h /usr/include/stdlib.h
TekCMS_TCI.o: LibTest.h /usr/include/stdio.h /usr/include/sys/cdefs.h
TekCMS_TCI.o: /usr/include/machine/ansi.h ../.././X11/Xlib.h
TekCMS_TCI.o: /usr/include/sys/types.h /usr/include/machine/endian.h
TekCMS_TCI.o: /usr/include/machine/types.h ../.././X11/X.h
TekCMS_TCI.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
TekCMS_TCI.o: /usr/include/stddef.h ../.././X11/Xcms.h TekCMS_LT.h TestInit.h
