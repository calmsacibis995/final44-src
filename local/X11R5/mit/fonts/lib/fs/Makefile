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
      CURRENT_DIR = ./fonts/lib/fs

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

# $XConsortium: Imakefile,v 1.10 91/07/24 18:36:33 keith Exp $

INCLUDES = -I$(FONTSRC)/include

SRCS =	FSClServ.c FSCloseFt.c FSConnServ.c FSErrDis.c FSErrHndlr.c	FSFlush.c FSFontInfo.c FSFtNames.c FSGetCats.c FSListCats.c	FSListExt.c FSMisc.c FSNextEv.c FSOpenFont.c FSOpenServ.c	FSQGlyphs.c FSQXExt.c FSQXInfo.c FSQuExt.c FSServName.c	FSSetCats.c FSSync.c FSSynchro.c FSlibInt.c

OBJS =	FSClServ.o FSCloseFt.o FSConnServ.o FSErrDis.o FSErrHndlr.o	FSFlush.o FSFontInfo.o FSFtNames.o FSGetCats.o FSListCats.o	FSListExt.o FSMisc.o FSNextEv.o FSOpenFont.o FSOpenServ.o	FSQGlyphs.o FSQXExt.o FSQXInfo.o FSQuExt.o FSServName.o	FSSetCats.o FSSync.o FSSynchro.o FSlibInt.o

CONN_DEFINES = -DTCPCONN -DUNIXCONN

all:: libFS.a

libFS.a: $(OBJS)
	$(RM) $@
	$(AR) $@ $(OBJS)
	$(RANLIB) $@

FSlibInt.o:	$(ICONFIGFILES)
	$(RM) $@
	$(CC) -c $(CFLAGS) $(CONN_DEFINES) $*.c

FSConnServ.o:	$(ICONFIGFILES)
	$(RM) $@
	$(CC) -c $(CFLAGS) $(CONN_DEFINES) $*.c

includes:: FSlib.h
	@case '${MFLAGS}' in *[i]*) set +e;; esac; \
	echo "	cd" ../../include; cd ../../include; \
	for i in FSlib.h; do (set -x; $(RM) $$i; $(LN) ../lib/fs/$$i .); done

depend:: $(DEPEND)

$(DEPEND):
	@echo "checking $@ over in $(DEPENDSRC) first..."; \
	cd $(DEPENDSRC); $(MAKE); \
	echo "okay, continuing in $(CURRENT_DIR)"

depend::
	$(DEPEND) $(DEPENDFLAGS) -s "# DO NOT DELETE" -- $(ALLDEFINES) -- $(SRCS)

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

FSClServ.o: FSlibint.h /usr/include/sys/types.h /usr/include/machine/endian.h
FSClServ.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
FSClServ.o: /usr/include/machine/types.h FSlib.h
FSClServ.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSClServ.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h FSlibos.h
FSClServ.o: ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSClServ.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSClServ.o: /usr/include/netdb.h /usr/include/sys/uio.h /usr/include/limits.h
FSClServ.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSClServ.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/errno.h
FSCloseFt.o: FSlibint.h /usr/include/sys/types.h
FSCloseFt.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSCloseFt.o: /usr/include/machine/ansi.h /usr/include/machine/types.h FSlib.h
FSCloseFt.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSCloseFt.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSCloseFt.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSCloseFt.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSCloseFt.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSCloseFt.o: /usr/include/limits.h /usr/include/machine/limits.h
FSCloseFt.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSCloseFt.o: /usr/include/string.h /usr/include/errno.h
FSConnServ.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
FSConnServ.o: /usr/include/machine/ansi.h ../../.././X11/Xos.h
FSConnServ.o: ../../.././X11/Xosdefs.h /usr/include/sys/types.h
FSConnServ.o: /usr/include/machine/endian.h /usr/include/machine/types.h
FSConnServ.o: /usr/include/string.h /usr/include/fcntl.h
FSConnServ.o: /usr/include/unistd.h /usr/include/sys/unistd.h
FSConnServ.o: /usr/include/sys/time.h /usr/include/sys/time.h FSlibint.h
FSConnServ.o: FSlib.h ../../.././fonts/include/FS.h
FSConnServ.o: ../../.././fonts/include/fsmasks.h
FSConnServ.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSConnServ.o: FSlibos.h ../../.././X11/Xfuncs.h /usr/include/netinet/in.h
FSConnServ.o: /usr/include/sys/ioctl.h /usr/include/netdb.h
FSConnServ.o: /usr/include/sys/uio.h /usr/include/limits.h
FSConnServ.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSConnServ.o: /usr/include/stdlib.h /usr/include/errno.h
FSConnServ.o: /usr/include/sys/socket.h /usr/include/netinet/tcp.h
FSErrDis.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
FSErrDis.o: /usr/include/machine/ansi.h ../../.././X11/Xos.h
FSErrDis.o: ../../.././X11/Xosdefs.h /usr/include/sys/types.h
FSErrDis.o: /usr/include/machine/endian.h /usr/include/machine/types.h
FSErrDis.o: /usr/include/string.h /usr/include/fcntl.h /usr/include/unistd.h
FSErrDis.o: /usr/include/sys/unistd.h /usr/include/sys/time.h
FSErrDis.o: /usr/include/sys/time.h FSlibint.h FSlib.h
FSErrDis.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSErrDis.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h FSlibos.h
FSErrDis.o: ../../.././X11/Xfuncs.h /usr/include/netinet/in.h
FSErrDis.o: /usr/include/sys/ioctl.h /usr/include/netdb.h
FSErrDis.o: /usr/include/sys/uio.h /usr/include/limits.h
FSErrDis.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSErrDis.o: /usr/include/stdlib.h /usr/include/errno.h
FSErrHndlr.o: FSlibint.h /usr/include/sys/types.h
FSErrHndlr.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSErrHndlr.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
FSErrHndlr.o: FSlib.h ../../.././fonts/include/FS.h
FSErrHndlr.o: ../../.././fonts/include/fsmasks.h
FSErrHndlr.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSErrHndlr.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSErrHndlr.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSErrHndlr.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSErrHndlr.o: /usr/include/limits.h /usr/include/machine/limits.h
FSErrHndlr.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSErrHndlr.o: /usr/include/string.h /usr/include/errno.h
FSFlush.o: FSlibint.h /usr/include/sys/types.h /usr/include/machine/endian.h
FSFlush.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
FSFlush.o: /usr/include/machine/types.h FSlib.h ../../.././fonts/include/FS.h
FSFlush.o: ../../.././fonts/include/fsmasks.h
FSFlush.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h FSlibos.h
FSFlush.o: ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSFlush.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSFlush.o: /usr/include/netdb.h /usr/include/sys/uio.h /usr/include/limits.h
FSFlush.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSFlush.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/errno.h
FSFontInfo.o: FSlibint.h /usr/include/sys/types.h
FSFontInfo.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSFontInfo.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
FSFontInfo.o: FSlib.h ../../.././fonts/include/FS.h
FSFontInfo.o: ../../.././fonts/include/fsmasks.h
FSFontInfo.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSFontInfo.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSFontInfo.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSFontInfo.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSFontInfo.o: /usr/include/limits.h /usr/include/machine/limits.h
FSFontInfo.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSFontInfo.o: /usr/include/string.h /usr/include/errno.h
FSFtNames.o: FSlibint.h /usr/include/sys/types.h
FSFtNames.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSFtNames.o: /usr/include/machine/ansi.h /usr/include/machine/types.h FSlib.h
FSFtNames.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSFtNames.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSFtNames.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSFtNames.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSFtNames.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSFtNames.o: /usr/include/limits.h /usr/include/machine/limits.h
FSFtNames.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSFtNames.o: /usr/include/string.h /usr/include/errno.h
FSGetCats.o: FSlibint.h /usr/include/sys/types.h
FSGetCats.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSGetCats.o: /usr/include/machine/ansi.h /usr/include/machine/types.h FSlib.h
FSGetCats.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSGetCats.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSGetCats.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSGetCats.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSGetCats.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSGetCats.o: /usr/include/limits.h /usr/include/machine/limits.h
FSGetCats.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSGetCats.o: /usr/include/string.h /usr/include/errno.h
FSListCats.o: FSlibint.h /usr/include/sys/types.h
FSListCats.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSListCats.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
FSListCats.o: FSlib.h ../../.././fonts/include/FS.h
FSListCats.o: ../../.././fonts/include/fsmasks.h
FSListCats.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSListCats.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSListCats.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSListCats.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSListCats.o: /usr/include/limits.h /usr/include/machine/limits.h
FSListCats.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSListCats.o: /usr/include/string.h /usr/include/errno.h
FSListExt.o: FSlibint.h /usr/include/sys/types.h
FSListExt.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSListExt.o: /usr/include/machine/ansi.h /usr/include/machine/types.h FSlib.h
FSListExt.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSListExt.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSListExt.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSListExt.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSListExt.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSListExt.o: /usr/include/limits.h /usr/include/machine/limits.h
FSListExt.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSListExt.o: /usr/include/string.h /usr/include/errno.h
FSMisc.o: FSlibint.h /usr/include/sys/types.h /usr/include/machine/endian.h
FSMisc.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
FSMisc.o: /usr/include/machine/types.h FSlib.h ../../.././fonts/include/FS.h
FSMisc.o: ../../.././fonts/include/fsmasks.h
FSMisc.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h FSlibos.h
FSMisc.o: ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSMisc.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSMisc.o: /usr/include/netdb.h /usr/include/sys/uio.h /usr/include/limits.h
FSMisc.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSMisc.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/errno.h
FSNextEv.o: FSlibint.h /usr/include/sys/types.h /usr/include/machine/endian.h
FSNextEv.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
FSNextEv.o: /usr/include/machine/types.h FSlib.h
FSNextEv.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSNextEv.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h FSlibos.h
FSNextEv.o: ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSNextEv.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSNextEv.o: /usr/include/netdb.h /usr/include/sys/uio.h /usr/include/limits.h
FSNextEv.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSNextEv.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/errno.h
FSOpenFont.o: FSlibint.h /usr/include/sys/types.h
FSOpenFont.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSOpenFont.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
FSOpenFont.o: FSlib.h ../../.././fonts/include/FS.h
FSOpenFont.o: ../../.././fonts/include/fsmasks.h
FSOpenFont.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSOpenFont.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSOpenFont.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSOpenFont.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSOpenFont.o: /usr/include/limits.h /usr/include/machine/limits.h
FSOpenFont.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSOpenFont.o: /usr/include/string.h /usr/include/errno.h
FSOpenServ.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
FSOpenServ.o: /usr/include/machine/ansi.h FSlibint.h /usr/include/sys/types.h
FSOpenServ.o: /usr/include/machine/endian.h /usr/include/machine/types.h
FSOpenServ.o: FSlib.h ../../.././fonts/include/FS.h
FSOpenServ.o: ../../.././fonts/include/fsmasks.h
FSOpenServ.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSOpenServ.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSOpenServ.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSOpenServ.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSOpenServ.o: /usr/include/limits.h /usr/include/machine/limits.h
FSOpenServ.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSOpenServ.o: /usr/include/string.h /usr/include/errno.h ../../.././X11/Xos.h
FSOpenServ.o: /usr/include/fcntl.h /usr/include/unistd.h
FSOpenServ.o: /usr/include/sys/unistd.h /usr/include/sys/time.h
FSOpenServ.o: /usr/include/sys/time.h
FSQGlyphs.o: FSlibint.h /usr/include/sys/types.h
FSQGlyphs.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSQGlyphs.o: /usr/include/machine/ansi.h /usr/include/machine/types.h FSlib.h
FSQGlyphs.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSQGlyphs.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSQGlyphs.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSQGlyphs.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSQGlyphs.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSQGlyphs.o: /usr/include/limits.h /usr/include/machine/limits.h
FSQGlyphs.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSQGlyphs.o: /usr/include/string.h /usr/include/errno.h
FSQXExt.o: FSlibint.h /usr/include/sys/types.h /usr/include/machine/endian.h
FSQXExt.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
FSQXExt.o: /usr/include/machine/types.h FSlib.h ../../.././fonts/include/FS.h
FSQXExt.o: ../../.././fonts/include/fsmasks.h
FSQXExt.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h FSlibos.h
FSQXExt.o: ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSQXExt.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSQXExt.o: /usr/include/netdb.h /usr/include/sys/uio.h /usr/include/limits.h
FSQXExt.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSQXExt.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/errno.h
FSQXInfo.o: FSlibint.h /usr/include/sys/types.h /usr/include/machine/endian.h
FSQXInfo.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
FSQXInfo.o: /usr/include/machine/types.h FSlib.h
FSQXInfo.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSQXInfo.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h FSlibos.h
FSQXInfo.o: ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSQXInfo.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSQXInfo.o: /usr/include/netdb.h /usr/include/sys/uio.h /usr/include/limits.h
FSQXInfo.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSQXInfo.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/errno.h
FSQuExt.o: FSlibint.h /usr/include/sys/types.h /usr/include/machine/endian.h
FSQuExt.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
FSQuExt.o: /usr/include/machine/types.h FSlib.h ../../.././fonts/include/FS.h
FSQuExt.o: ../../.././fonts/include/fsmasks.h
FSQuExt.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h FSlibos.h
FSQuExt.o: ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSQuExt.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSQuExt.o: /usr/include/netdb.h /usr/include/sys/uio.h /usr/include/limits.h
FSQuExt.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSQuExt.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/errno.h
FSServName.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
FSServName.o: /usr/include/machine/ansi.h ../../.././X11/Xosdefs.h
FSServName.o: /usr/include/stdlib.h
FSSetCats.o: FSlibint.h /usr/include/sys/types.h
FSSetCats.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSSetCats.o: /usr/include/machine/ansi.h /usr/include/machine/types.h FSlib.h
FSSetCats.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSSetCats.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSSetCats.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSSetCats.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSSetCats.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSSetCats.o: /usr/include/limits.h /usr/include/machine/limits.h
FSSetCats.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSSetCats.o: /usr/include/string.h /usr/include/errno.h
FSSync.o: FSlibint.h /usr/include/sys/types.h /usr/include/machine/endian.h
FSSync.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
FSSync.o: /usr/include/machine/types.h FSlib.h ../../.././fonts/include/FS.h
FSSync.o: ../../.././fonts/include/fsmasks.h
FSSync.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h FSlibos.h
FSSync.o: ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSSync.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSSync.o: /usr/include/netdb.h /usr/include/sys/uio.h /usr/include/limits.h
FSSync.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSSync.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/errno.h
FSSynchro.o: FSlibint.h /usr/include/sys/types.h
FSSynchro.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
FSSynchro.o: /usr/include/machine/ansi.h /usr/include/machine/types.h FSlib.h
FSSynchro.o: ../../.././fonts/include/FS.h ../../.././fonts/include/fsmasks.h
FSSynchro.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h
FSSynchro.o: FSlibos.h ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSSynchro.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSSynchro.o: /usr/include/netdb.h /usr/include/sys/uio.h
FSSynchro.o: /usr/include/limits.h /usr/include/machine/limits.h
FSSynchro.o: /usr/include/sys/syslimits.h /usr/include/stdlib.h
FSSynchro.o: /usr/include/string.h /usr/include/errno.h
FSlibInt.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
FSlibInt.o: /usr/include/machine/ansi.h FSlibint.h /usr/include/sys/types.h
FSlibInt.o: /usr/include/machine/endian.h /usr/include/machine/types.h
FSlibInt.o: FSlib.h ../../.././fonts/include/FS.h
FSlibInt.o: ../../.././fonts/include/fsmasks.h
FSlibInt.o: ../../.././fonts/include/FSproto.h ../../.././X11/Xmd.h FSlibos.h
FSlibInt.o: ../../.././X11/Xfuncs.h ../../.././X11/Xosdefs.h
FSlibInt.o: /usr/include/netinet/in.h /usr/include/sys/ioctl.h
FSlibInt.o: /usr/include/netdb.h /usr/include/sys/uio.h /usr/include/limits.h
FSlibInt.o: /usr/include/machine/limits.h /usr/include/sys/syslimits.h
FSlibInt.o: /usr/include/stdlib.h /usr/include/string.h /usr/include/errno.h
