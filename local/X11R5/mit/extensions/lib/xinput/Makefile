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

              TOP = ../../../.
      CURRENT_DIR = ./extensions/lib/xinput

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

# $XConsortium: Imakefile,v 1.11 91/07/24 15:38:57 rws Exp $

# $XConsortium: Library.tmpl,v 1.12 92/03/20 15:05:19 rws Exp $

         CC = gcc
  CCOPTIONS =
STD_DEFINES =
CDEBUGFLAGS = -O

INCLUDES = -I$(TOP) -I$(INCLUDESRC) -I$(XLIBSRC) -I../../include
SRCS = XAllowDv.c 		  XChgDCtl.c 		  XChgFCtl.c 		  XChgKbd.c 		  XChgKMap.c 		  XChgPnt.c 		  XChgProp.c 		  XCloseDev.c 		  XDevBell.c 		  XExtToWire.c 		  XGetBMap.c 		  XGetDCtl.c 		  XGetFCtl.c 		  XGetKMap.c 		  XGetMMap.c 		  XGetProp.c 		  XGetVers.c 		  XGMotion.c 		  XGrabDev.c 		  XGrDvBut.c 		  XGrDvKey.c 		  XGtFocus.c 		  XGtSelect.c 		  XListDev.c 		  XOpenDev.c 		  XQueryDv.c 		  XSelect.c 		  XSetBMap.c 		  XSetDVal.c 		  XSetMMap.c 		  XSetMode.c 		  XSndExEv.c 		  XStFocus.c 		  XUngrDev.c 		  XUngrDvB.c 		  XUngrDvK.c 		  XExtInt.c

OBJS = XAllowDv.o 		  XChgDCtl.o 		  XChgFCtl.o 		  XChgKbd.o 		  XChgKMap.o 		  XChgPnt.o 		  XChgProp.o 		  XCloseDev.o 		  XDevBell.o 		  XExtToWire.o 		  XGetBMap.o 		  XGetDCtl.o 		  XGetFCtl.o 		  XGetKMap.o 		  XGetMMap.o 		  XGetProp.o 		  XGetVers.o 		  XGMotion.o 		  XGrabDev.o 		  XGrDvBut.o 		  XGrDvKey.o 		  XGtFocus.o 		  XGtSelect.o 		  XListDev.o 		  XOpenDev.o 		  XQueryDv.o 		  XSelect.o 		  XSetBMap.o 		  XSetDVal.o 		  XSetMMap.o 		  XSetMode.o 		  XSndExEv.o 		  XStFocus.o 		  XUngrDev.o 		  XUngrDvB.o 		  XUngrDvK.o 		  XExtInt.o

       LINTLIBS = $(LINTXLIB) $(LINTXEXT)

all::
	$(_NULLCMD_)
	$(_NULLCMD_)
	$(_NULLCMD_)

includes::
	$(_NULLCMD_)
	$(_NULLCMD_)
	$(_NULLCMD_)

.c.o:
	$(_NULLCMD_)
	$(_NULLCMD_)
	$(_NULLCMD_)
	$(RM) $@
	$(CC) -c $(CFLAGS) $(_NOOP_) $*.c

clean::
	$(_NULLCMD_)
	$(_NULLCMD_)
	$(_NULLCMD_)

all:: libXi.a

libXi.a: $(OBJS)
	$(RM) $@
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

install:: libXi.a
	-@if [ -d $(DESTDIR)$(USRLIBDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(USRLIBDIR)); fi
	$(INSTALL) -c $(INSTLIBFLAGS) libXi.a $(DESTDIR)$(USRLIBDIR)
	$(RANLIB) $(RANLIBINSTFLAGS) $(DESTDIR)$(USRLIBDIR)/libXi.a

lintlib:: llib-lXi.ln

llib-lXi.ln: $(SRCS)
	$(RM) $@
	$(LINT) $(LINTLIBFLAG)Xi $(LINTFLAGS) $(SRCS)

install.ln:: llib-lXi.ln
	-@if [ -d $(DESTDIR)$(LINTLIBDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(LINTLIBDIR)); fi
	$(INSTALL) -c $(INSTLIBFLAGS) llib-lXi.ln $(DESTDIR)$(LINTLIBDIR)

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

XAllowDv.o: ../../include/XI.h ../../include/XIproto.h
XAllowDv.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XAllowDv.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XAllowDv.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XAllowDv.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XAllowDv.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XAllowDv.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XAllowDv.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XAllowDv.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XAllowDv.o: /usr/include/stdlib.h /usr/include/string.h
XAllowDv.o: ../../include/XInput.h ../../include/extutil.h
XChgDCtl.o: ../../include/XI.h ../../include/XIproto.h
XChgDCtl.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XChgDCtl.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XChgDCtl.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XChgDCtl.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XChgDCtl.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XChgDCtl.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XChgDCtl.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XChgDCtl.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XChgDCtl.o: /usr/include/stdlib.h /usr/include/string.h
XChgDCtl.o: ../../include/XInput.h ../../include/extutil.h
XChgFCtl.o: ../../include/XI.h ../../include/XIproto.h
XChgFCtl.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XChgFCtl.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XChgFCtl.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XChgFCtl.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XChgFCtl.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XChgFCtl.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XChgFCtl.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XChgFCtl.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XChgFCtl.o: /usr/include/stdlib.h /usr/include/string.h
XChgFCtl.o: ../../include/XInput.h ../../include/extutil.h
XChgKbd.o: ../../include/XI.h ../../include/XIproto.h ../../.././X11/Xproto.h
XChgKbd.o: ../../.././X11/Xmd.h ../../.././X11/Xprotostr.h ../../.././X11/X.h
XChgKbd.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XChgKbd.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XChgKbd.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XChgKbd.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XChgKbd.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XChgKbd.o: /usr/include/errno.h ../../.././X11/Xfuncs.h /usr/include/stdlib.h
XChgKbd.o: /usr/include/string.h ../../include/XInput.h
XChgKbd.o: ../../include/extutil.h
XChgKMap.o: ../../include/XI.h ../../include/XIproto.h
XChgKMap.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XChgKMap.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XChgKMap.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XChgKMap.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XChgKMap.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XChgKMap.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XChgKMap.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XChgKMap.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XChgKMap.o: /usr/include/stdlib.h /usr/include/string.h
XChgKMap.o: ../../include/XInput.h ../../include/extutil.h
XChgPnt.o: ../../include/XI.h ../../include/XIproto.h ../../.././X11/Xproto.h
XChgPnt.o: ../../.././X11/Xmd.h ../../.././X11/Xprotostr.h ../../.././X11/X.h
XChgPnt.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XChgPnt.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XChgPnt.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XChgPnt.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XChgPnt.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XChgPnt.o: /usr/include/errno.h ../../.././X11/Xfuncs.h /usr/include/stdlib.h
XChgPnt.o: /usr/include/string.h ../../include/XInput.h
XChgPnt.o: ../../include/extutil.h
XChgProp.o: ../../include/XI.h ../../include/XIproto.h
XChgProp.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XChgProp.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XChgProp.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XChgProp.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XChgProp.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XChgProp.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XChgProp.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XChgProp.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XChgProp.o: /usr/include/stdlib.h /usr/include/string.h
XChgProp.o: ../../include/XInput.h ../../include/extutil.h
XCloseDev.o: ../../include/XIproto.h ../../.././X11/Xproto.h
XCloseDev.o: ../../.././X11/Xmd.h ../../.././X11/Xprotostr.h
XCloseDev.o: ../../.././X11/X.h ../../.././X11/Xlibint.h
XCloseDev.o: ../../.././X11/Xlib.h /usr/include/sys/types.h
XCloseDev.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
XCloseDev.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
XCloseDev.o: ../../.././X11/Xfuncproto.h ../../.././X11/Xosdefs.h
XCloseDev.o: /usr/include/stddef.h /usr/include/errno.h
XCloseDev.o: ../../.././X11/Xfuncs.h /usr/include/stdlib.h
XCloseDev.o: /usr/include/string.h ../../include/XI.h ../../include/XInput.h
XCloseDev.o: ../../include/extutil.h
XDevBell.o: ../../include/XI.h ../../include/XIproto.h
XDevBell.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XDevBell.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XDevBell.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XDevBell.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XDevBell.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XDevBell.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XDevBell.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XDevBell.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XDevBell.o: /usr/include/stdlib.h /usr/include/string.h
XDevBell.o: ../../include/XInput.h ../../include/extutil.h
XExtToWire.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XExtToWire.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XExtToWire.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XExtToWire.o: /usr/include/machine/types.h ../../.././X11/X.h
XExtToWire.o: ../../.././X11/Xfuncproto.h ../../.././X11/Xosdefs.h
XExtToWire.o: /usr/include/stddef.h ../../.././X11/Xproto.h
XExtToWire.o: ../../.././X11/Xmd.h ../../.././X11/Xprotostr.h
XExtToWire.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XExtToWire.o: /usr/include/stdlib.h /usr/include/string.h
XExtToWire.o: ../../include/XInput.h ../../include/XIproto.h
XExtToWire.o: ../../include/extutil.h
XGetBMap.o: ../../include/XI.h ../../include/XIproto.h
XGetBMap.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGetBMap.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGetBMap.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGetBMap.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGetBMap.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGetBMap.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGetBMap.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGetBMap.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGetBMap.o: /usr/include/stdlib.h /usr/include/string.h
XGetBMap.o: ../../include/XInput.h ../../include/extutil.h
XGetDCtl.o: ../../include/XI.h ../../include/XIproto.h
XGetDCtl.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGetDCtl.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGetDCtl.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGetDCtl.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGetDCtl.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGetDCtl.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGetDCtl.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGetDCtl.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGetDCtl.o: /usr/include/stdlib.h /usr/include/string.h ../../.././X11/Xlib.h
XGetDCtl.o: ../../include/XInput.h ../../include/extutil.h
XGetFCtl.o: ../../include/XI.h ../../include/XIproto.h
XGetFCtl.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGetFCtl.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGetFCtl.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGetFCtl.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGetFCtl.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGetFCtl.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGetFCtl.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGetFCtl.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGetFCtl.o: /usr/include/stdlib.h /usr/include/string.h ../../.././X11/Xlib.h
XGetFCtl.o: ../../include/XInput.h ../../include/extutil.h
XGetKMap.o: ../../include/XI.h ../../include/XIproto.h
XGetKMap.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGetKMap.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGetKMap.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGetKMap.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGetKMap.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGetKMap.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGetKMap.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGetKMap.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGetKMap.o: /usr/include/stdlib.h /usr/include/string.h
XGetKMap.o: ../../include/XInput.h ../../include/extutil.h
XGetMMap.o: ../../include/XI.h ../../include/XIproto.h
XGetMMap.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGetMMap.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGetMMap.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGetMMap.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGetMMap.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGetMMap.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGetMMap.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGetMMap.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGetMMap.o: /usr/include/stdlib.h /usr/include/string.h
XGetMMap.o: ../../include/XInput.h ../../include/extutil.h
XGetProp.o: ../../include/XI.h ../../include/XIproto.h
XGetProp.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGetProp.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGetProp.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGetProp.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGetProp.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGetProp.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGetProp.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGetProp.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGetProp.o: /usr/include/stdlib.h /usr/include/string.h
XGetProp.o: ../../include/XInput.h ../../include/extutil.h
XGetVers.o: ../../include/XIproto.h ../../.././X11/Xproto.h
XGetVers.o: ../../.././X11/Xmd.h ../../.././X11/Xprotostr.h
XGetVers.o: ../../.././X11/X.h ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGetVers.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGetVers.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGetVers.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGetVers.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGetVers.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGetVers.o: /usr/include/stdlib.h /usr/include/string.h ../../include/XI.h
XGetVers.o: ../../include/XInput.h ../../include/extutil.h
XGMotion.o: ../../include/XI.h ../../include/XIproto.h
XGMotion.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGMotion.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGMotion.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGMotion.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGMotion.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGMotion.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGMotion.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGMotion.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGMotion.o: /usr/include/stdlib.h /usr/include/string.h
XGMotion.o: ../../include/XInput.h ../../include/extutil.h
XGrabDev.o: ../../include/XI.h ../../include/XIproto.h
XGrabDev.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGrabDev.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGrabDev.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGrabDev.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGrabDev.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGrabDev.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGrabDev.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGrabDev.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGrabDev.o: /usr/include/stdlib.h /usr/include/string.h
XGrabDev.o: ../../include/XInput.h ../../include/extutil.h
XGrDvBut.o: ../../include/XI.h ../../include/XIproto.h
XGrDvBut.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGrDvBut.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGrDvBut.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGrDvBut.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGrDvBut.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGrDvBut.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGrDvBut.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGrDvBut.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGrDvBut.o: /usr/include/stdlib.h /usr/include/string.h
XGrDvBut.o: ../../include/XInput.h ../../include/extutil.h
XGrDvKey.o: ../../include/XI.h ../../include/XIproto.h
XGrDvKey.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGrDvKey.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGrDvKey.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGrDvKey.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGrDvKey.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGrDvKey.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGrDvKey.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGrDvKey.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGrDvKey.o: /usr/include/stdlib.h /usr/include/string.h
XGrDvKey.o: ../../include/XInput.h ../../include/extutil.h
XGtFocus.o: ../../include/XI.h ../../include/XIproto.h
XGtFocus.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGtFocus.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGtFocus.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGtFocus.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGtFocus.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGtFocus.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGtFocus.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGtFocus.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGtFocus.o: /usr/include/stdlib.h /usr/include/string.h
XGtFocus.o: ../../include/XInput.h ../../include/extutil.h
XGtSelect.o: ../../include/XI.h ../../include/XIproto.h
XGtSelect.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XGtSelect.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XGtSelect.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XGtSelect.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XGtSelect.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XGtSelect.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XGtSelect.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XGtSelect.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XGtSelect.o: /usr/include/stdlib.h /usr/include/string.h
XGtSelect.o: ../../.././X11/Xproto.h ../../include/XInput.h
XGtSelect.o: ../../include/extutil.h
XListDev.o: ../../.././X11/Xproto.h ../../.././X11/Xlibint.h
XListDev.o: ../../.././X11/Xlib.h /usr/include/sys/types.h
XListDev.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
XListDev.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
XListDev.o: ../../.././X11/X.h ../../.././X11/Xfuncproto.h
XListDev.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XListDev.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XListDev.o: ../../.././X11/Xprotostr.h /usr/include/errno.h
XListDev.o: ../../.././X11/Xfuncs.h /usr/include/stdlib.h
XListDev.o: /usr/include/string.h ../../include/XIproto.h ../../include/XI.h
XListDev.o: ../../include/XInput.h ../../include/extutil.h
XOpenDev.o: ../../include/XI.h ../../include/XIproto.h
XOpenDev.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XOpenDev.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XOpenDev.o: ../../include/XInput.h ../../.././X11/Xlibint.h
XOpenDev.o: ../../.././X11/Xlib.h /usr/include/sys/types.h
XOpenDev.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
XOpenDev.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
XOpenDev.o: ../../.././X11/Xfuncproto.h ../../.././X11/Xosdefs.h
XOpenDev.o: /usr/include/stddef.h /usr/include/errno.h
XOpenDev.o: ../../.././X11/Xfuncs.h /usr/include/stdlib.h
XOpenDev.o: /usr/include/string.h ../../include/extutil.h
XQueryDv.o: ../../include/XI.h ../../include/XIproto.h
XQueryDv.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XQueryDv.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XQueryDv.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XQueryDv.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XQueryDv.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XQueryDv.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XQueryDv.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XQueryDv.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XQueryDv.o: /usr/include/stdlib.h /usr/include/string.h
XQueryDv.o: ../../include/XInput.h ../../include/extutil.h
XSelect.o: ../../include/XI.h ../../include/XIproto.h ../../.././X11/Xproto.h
XSelect.o: ../../.././X11/Xmd.h ../../.././X11/Xprotostr.h ../../.././X11/X.h
XSelect.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XSelect.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XSelect.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XSelect.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XSelect.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XSelect.o: /usr/include/errno.h ../../.././X11/Xfuncs.h /usr/include/stdlib.h
XSelect.o: /usr/include/string.h ../../.././X11/Xproto.h
XSelect.o: ../../include/XInput.h ../../include/extutil.h
XSetBMap.o: ../../include/XI.h ../../include/XIproto.h
XSetBMap.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XSetBMap.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XSetBMap.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XSetBMap.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XSetBMap.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XSetBMap.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XSetBMap.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XSetBMap.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XSetBMap.o: /usr/include/stdlib.h /usr/include/string.h
XSetBMap.o: ../../include/XInput.h ../../include/extutil.h
XSetDVal.o: ../../include/XI.h ../../include/XIproto.h
XSetDVal.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XSetDVal.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XSetDVal.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XSetDVal.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XSetDVal.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XSetDVal.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XSetDVal.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XSetDVal.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XSetDVal.o: /usr/include/stdlib.h /usr/include/string.h
XSetDVal.o: ../../include/XInput.h ../../include/extutil.h
XSetMMap.o: ../../include/XI.h ../../include/XIproto.h
XSetMMap.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XSetMMap.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XSetMMap.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XSetMMap.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XSetMMap.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XSetMMap.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XSetMMap.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XSetMMap.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XSetMMap.o: /usr/include/stdlib.h /usr/include/string.h
XSetMMap.o: ../../include/XInput.h ../../include/extutil.h
XSetMode.o: ../../include/XI.h ../../include/XIproto.h
XSetMode.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XSetMode.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XSetMode.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XSetMode.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XSetMode.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XSetMode.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XSetMode.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XSetMode.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XSetMode.o: /usr/include/stdlib.h /usr/include/string.h
XSetMode.o: ../../include/XInput.h ../../include/extutil.h
XSndExEv.o: ../../include/XI.h ../../include/XIproto.h
XSndExEv.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XSndExEv.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XSndExEv.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XSndExEv.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XSndExEv.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XSndExEv.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XSndExEv.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XSndExEv.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XSndExEv.o: /usr/include/stdlib.h /usr/include/string.h
XSndExEv.o: ../../include/XInput.h ../../include/extutil.h
XStFocus.o: ../../include/XI.h ../../include/XIproto.h
XStFocus.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XStFocus.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XStFocus.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XStFocus.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XStFocus.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XStFocus.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XStFocus.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XStFocus.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XStFocus.o: /usr/include/stdlib.h /usr/include/string.h
XStFocus.o: ../../include/XInput.h ../../include/extutil.h
XUngrDev.o: ../../include/XI.h ../../include/XIproto.h
XUngrDev.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XUngrDev.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XUngrDev.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XUngrDev.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XUngrDev.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XUngrDev.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XUngrDev.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XUngrDev.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XUngrDev.o: /usr/include/stdlib.h /usr/include/string.h
XUngrDev.o: ../../include/XInput.h ../../include/extutil.h
XUngrDvB.o: ../../include/XI.h ../../include/XIproto.h
XUngrDvB.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XUngrDvB.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XUngrDvB.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XUngrDvB.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XUngrDvB.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XUngrDvB.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XUngrDvB.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XUngrDvB.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XUngrDvB.o: /usr/include/stdlib.h /usr/include/string.h
XUngrDvB.o: ../../include/XInput.h ../../include/extutil.h
XUngrDvK.o: ../../include/XI.h ../../include/XIproto.h
XUngrDvK.o: ../../.././X11/Xproto.h ../../.././X11/Xmd.h
XUngrDvK.o: ../../.././X11/Xprotostr.h ../../.././X11/X.h
XUngrDvK.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XUngrDvK.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XUngrDvK.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
XUngrDvK.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XUngrDvK.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XUngrDvK.o: /usr/include/errno.h ../../.././X11/Xfuncs.h
XUngrDvK.o: /usr/include/stdlib.h /usr/include/string.h
XUngrDvK.o: ../../include/XInput.h ../../include/extutil.h
XExtInt.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
XExtInt.o: /usr/include/machine/ansi.h ../../include/XI.h
XExtInt.o: ../../include/XIproto.h ../../.././X11/Xproto.h
XExtInt.o: ../../.././X11/Xmd.h ../../.././X11/Xprotostr.h ../../.././X11/X.h
XExtInt.o: ../../.././X11/Xlibint.h ../../.././X11/Xlib.h
XExtInt.o: /usr/include/sys/types.h /usr/include/machine/endian.h
XExtInt.o: /usr/include/machine/types.h ../../.././X11/Xfuncproto.h
XExtInt.o: ../../.././X11/Xosdefs.h /usr/include/stddef.h
XExtInt.o: /usr/include/errno.h ../../.././X11/Xfuncs.h /usr/include/stdlib.h
XExtInt.o: /usr/include/string.h ../../include/XInput.h
XExtInt.o: ../../include/extutil.h
