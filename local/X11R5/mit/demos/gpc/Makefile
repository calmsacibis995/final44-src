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
      CURRENT_DIR = ./demos/gpc

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

# $XConsortium: Imakefile,v 1.15 91/08/22 14:26:28 rws Exp $
#
# Copyright 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium
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
# INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN 0
# EVENT SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR
# CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
# USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
# OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

       INCLUDES = -I$(BUILDINCDIR)
LOCAL_LIBRARIES = $(PHIGSLIB) $(XMULIB) $(XLIB)
        DEPLIBS = $(DEPPHIGSLIB) $(DEPXMULIB) $(DEPXLIB)

SYS_LIBRARIES = -lm

SRCS =  basestat.c bif_lex.c bifbuild.c bifconfig.c bifparse.c bld_prim.c 	bld_str.c bld_view.c bldgeneric.c brf_ents.c brf_phead.c brf_trv.c 	db_tools.c doentity.c dummies.c fakefigs.c new_ents.c gen_ents.c 	init_bench.c listbufs.c maptools.c matrix.c 	traverser.c brf_except.c fillcont.c pixbuf.c stopwatch.c

OBJS =   basestat.o bif_lex.o bifbuild.o bifconfig.o bifparse.o bld_prim.o 	bld_str.o bld_view.o bldgeneric.o brf_ents.o brf_phead.o brf_trv.o 	db_tools.o doentity.o dummies.o fakefigs.o new_ents.o gen_ents.o 	init_bench.o listbufs.o maptools.o matrix.o 	traverser.o brf_except.o fillcont.o pixbuf.o stopwatch.o

# USING_PHIGS Build gpc for PHIGS_API
# HAVEPIXELS  Turns on code not particular to the SI, used in conjuction
#		with specialized GDP's or GSE's not supported by PEX_API

DEFINES = -DUSING_PHIGS

 PROGRAM = plbpex

all:: plbpex

plbpex: $(OBJS) $(DEPLIBS)
	$(RM) $@
	$(CC) -o $@ $(OBJS) $(LDOPTIONS) $(LOCAL_LIBRARIES) $(LDLIBS) $(EXTRA_LOAD_FLAGS)

saber_plbpex:: $(SRCS)
	# load $(ALLDEFINES) $(SRCS) $(LOCAL_LIBRARIES) $(SYS_LIBRARIES) $(EXTRA_LIBRARIES)

osaber_plbpex:: $(OBJS)
	# load $(ALLDEFINES) $(OBJS) $(LOCAL_LIBRARIES) $(SYS_LIBRARIES) $(EXTRA_LIBRARIES)

install:: plbpex
	-@if [ -d $(DESTDIR)$(BINDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(BINDIR)); fi
	$(INSTALL) -c $(INSTPGMFLAGS)  plbpex $(DESTDIR)$(BINDIR)

install.man:: plbpex.man
	-@if [ -d $(DESTDIR)$(MANDIR) ]; then set +x; \
	else (set -x; $(MKDIRHIER) $(DESTDIR)$(MANDIR)); fi
	$(INSTALL) -c $(INSTMANFLAGS) plbpex.man $(DESTDIR)$(MANDIR)/plbpex.$(MANSUFFIX)

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

bifparse::
	$(CP) bifparse.yacc bifparse.y
	$(YACC) -d -v bifparse.y
	$(MV) y.tab.c bifparse.c
	$(MV) y.tab.h bifparse.h
	$(RM) bifparse.y

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

basestat.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
basestat.o: /usr/include/machine/ansi.h biftypes.h bifbuild.h
basestat.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
basestat.o: /usr/include/sys/types.h /usr/include/machine/endian.h
basestat.o: /usr/include/machine/types.h ../.././X11/X.h
basestat.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
basestat.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
basestat.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
basestat.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
basestat.o: bifmacro.h globals.h ph_map.h
bif_lex.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
bif_lex.o: /usr/include/machine/ansi.h /usr/include/string.h
bif_lex.o: /usr/include/ctype.h /usr/include/runetype.h biftypes.h bifbuild.h
bif_lex.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
bif_lex.o: /usr/include/sys/types.h /usr/include/machine/endian.h
bif_lex.o: /usr/include/machine/types.h ../.././X11/X.h
bif_lex.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
bif_lex.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
bif_lex.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
bif_lex.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
bif_lex.o: bifparse.h globals.h ph_map.h brfexption.h
bifbuild.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
bifbuild.o: /usr/include/machine/ansi.h biftypes.h bifbuild.h
bifbuild.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
bifbuild.o: /usr/include/sys/types.h /usr/include/machine/endian.h
bifbuild.o: /usr/include/machine/types.h ../.././X11/X.h
bifbuild.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
bifbuild.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
bifbuild.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
bifbuild.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
bifbuild.o: new_ents.h bifparse.h db_tools.h doentity.h bifmacro.h globals.h
bifbuild.o: ph_map.h macfunct.h brftypes.h brfexption.h ../.././X11/Xfuncs.h
bifconfig.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
bifconfig.o: /usr/include/machine/ansi.h biftypes.h bifbuild.h
bifconfig.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
bifconfig.o: /usr/include/sys/types.h /usr/include/machine/endian.h
bifconfig.o: /usr/include/machine/types.h ../.././X11/X.h
bifconfig.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
bifconfig.o: /usr/include/stddef.h ../.././X11/Xutil.h
bifconfig.o: ../.././X11/Xresource.h ../.././X11/phigs/attr.h
bifconfig.o: ../.././X11/phigs/phigscfunc.h ../.././X11/phigs/phigsextrn.h
bifconfig.o: ../.././X11/phigs/phigserr.h bifparse.h bifmacro.h globals.h
bifconfig.o: ph_map.h brfexption.h
bifparse.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
bifparse.o: /usr/include/machine/ansi.h /usr/include/string.h
bifparse.o: /usr/include/ctype.h /usr/include/runetype.h bifbuild.h
bld_prim.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
bld_prim.o: /usr/include/machine/ansi.h ../.././X11/Xosdefs.h
bld_prim.o: /usr/include/stdlib.h biftypes.h bifbuild.h
bld_prim.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
bld_prim.o: /usr/include/sys/types.h /usr/include/machine/endian.h
bld_prim.o: /usr/include/machine/types.h ../.././X11/X.h
bld_prim.o: ../.././X11/Xfuncproto.h /usr/include/stddef.h
bld_prim.o: ../.././X11/Xutil.h ../.././X11/Xresource.h
bld_prim.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
bld_prim.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
bld_prim.o: new_ents.h bifparse.h db_tools.h doentity.h bifmacro.h globals.h
bld_prim.o: ph_map.h
bld_str.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
bld_str.o: /usr/include/machine/ansi.h biftypes.h bifbuild.h
bld_str.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
bld_str.o: /usr/include/sys/types.h /usr/include/machine/endian.h
bld_str.o: /usr/include/machine/types.h ../.././X11/X.h
bld_str.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
bld_str.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
bld_str.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
bld_str.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
bld_str.o: new_ents.h bifparse.h db_tools.h doentity.h bifmacro.h globals.h
bld_str.o: ph_map.h
bld_view.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
bld_view.o: /usr/include/machine/ansi.h biftypes.h bifbuild.h
bld_view.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
bld_view.o: /usr/include/sys/types.h /usr/include/machine/endian.h
bld_view.o: /usr/include/machine/types.h ../.././X11/X.h
bld_view.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
bld_view.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
bld_view.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
bld_view.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
bld_view.o: new_ents.h bifparse.h db_tools.h doentity.h bifmacro.h globals.h
bld_view.o: ph_map.h macfunct.h
bldgeneric.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
bldgeneric.o: /usr/include/machine/ansi.h biftypes.h bifbuild.h
bldgeneric.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
bldgeneric.o: /usr/include/sys/types.h /usr/include/machine/endian.h
bldgeneric.o: /usr/include/machine/types.h ../.././X11/X.h
bldgeneric.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
bldgeneric.o: /usr/include/stddef.h ../.././X11/Xutil.h
bldgeneric.o: ../.././X11/Xresource.h ../.././X11/phigs/attr.h
bldgeneric.o: ../.././X11/phigs/phigscfunc.h ../.././X11/phigs/phigsextrn.h
bldgeneric.o: ../.././X11/phigs/phigserr.h new_ents.h bifparse.h db_tools.h
bldgeneric.o: doentity.h bifmacro.h globals.h ph_map.h macfunct.h
brf_ents.o: /usr/include/math.h /usr/include/sys/cdefs.h /usr/include/stdio.h
brf_ents.o: /usr/include/machine/ansi.h /usr/include/string.h biftypes.h
brf_ents.o: bifbuild.h ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
brf_ents.o: /usr/include/sys/types.h /usr/include/machine/endian.h
brf_ents.o: /usr/include/machine/types.h ../.././X11/X.h
brf_ents.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
brf_ents.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
brf_ents.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
brf_ents.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
brf_ents.o: globals.h bifparse.h brf_ents.h brftypes.h bifmacro.h
brf_ents.o: brfexption.h
brf_phead.o: ../.././X11/Xos.h ../.././X11/Xosdefs.h /usr/include/sys/types.h
brf_phead.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
brf_phead.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
brf_phead.o: /usr/include/string.h /usr/include/fcntl.h /usr/include/unistd.h
brf_phead.o: /usr/include/sys/unistd.h /usr/include/sys/time.h
brf_phead.o: /usr/include/sys/time.h /usr/include/stdio.h brf_prt.h
brf_phead.o: biftypes.h bifbuild.h ../.././X11/phigs/phigs.h
brf_phead.o: ../.././X11/Xlib.h ../.././X11/X.h ../.././X11/Xfuncproto.h
brf_phead.o: /usr/include/stddef.h ../.././X11/Xutil.h
brf_phead.o: ../.././X11/Xresource.h ../.././X11/phigs/attr.h
brf_phead.o: ../.././X11/phigs/phigscfunc.h ../.././X11/phigs/phigsextrn.h
brf_phead.o: ../.././X11/phigs/phigserr.h globals.h brfexption.h
brf_trv.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
brf_trv.o: /usr/include/machine/ansi.h /usr/include/sys/time.h
brf_trv.o: /usr/include/sys/time.h brf_ents.h biftypes.h bifbuild.h
brf_trv.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
brf_trv.o: /usr/include/sys/types.h /usr/include/machine/endian.h
brf_trv.o: /usr/include/machine/types.h ../.././X11/X.h
brf_trv.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
brf_trv.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
brf_trv.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
brf_trv.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
brf_trv.o: bifmacro.h bifparse.h brftypes.h brf_set.h globals.h ph_map.h
brf_trv.o: brfexption.h stopwatch.h
db_tools.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
db_tools.o: /usr/include/machine/ansi.h ../.././X11/Xosdefs.h
db_tools.o: /usr/include/stdlib.h biftypes.h bifbuild.h
db_tools.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
db_tools.o: /usr/include/sys/types.h /usr/include/machine/endian.h
db_tools.o: /usr/include/machine/types.h ../.././X11/X.h
db_tools.o: ../.././X11/Xfuncproto.h /usr/include/stddef.h
db_tools.o: ../.././X11/Xutil.h ../.././X11/Xresource.h
db_tools.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
db_tools.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
db_tools.o: bifparse.h new_ents.h ph_map.h
doentity.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
doentity.o: /usr/include/machine/ansi.h bifbuild.h biftypes.h
doentity.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
doentity.o: /usr/include/sys/types.h /usr/include/machine/endian.h
doentity.o: /usr/include/machine/types.h ../.././X11/X.h
doentity.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
doentity.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
doentity.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
doentity.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
doentity.o: bifmacro.h db_tools.h globals.h ph_map.h ../.././X11/Xfuncs.h
fakefigs.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
fakefigs.o: /usr/include/machine/ansi.h ../.././X11/Xosdefs.h
fakefigs.o: /usr/include/stdlib.h ph_map.h biftypes.h bifbuild.h
fakefigs.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
fakefigs.o: /usr/include/sys/types.h /usr/include/machine/endian.h
fakefigs.o: /usr/include/machine/types.h ../.././X11/X.h
fakefigs.o: ../.././X11/Xfuncproto.h /usr/include/stddef.h
fakefigs.o: ../.././X11/Xutil.h ../.././X11/Xresource.h
fakefigs.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
fakefigs.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
fakefigs.o: globals.h bifmacro.h
new_ents.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
new_ents.o: /usr/include/machine/ansi.h ../.././X11/Xosdefs.h
new_ents.o: /usr/include/stdlib.h bifbuild.h biftypes.h
new_ents.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
new_ents.o: /usr/include/sys/types.h /usr/include/machine/endian.h
new_ents.o: /usr/include/machine/types.h ../.././X11/X.h
new_ents.o: ../.././X11/Xfuncproto.h /usr/include/stddef.h
new_ents.o: ../.././X11/Xutil.h ../.././X11/Xresource.h
new_ents.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
new_ents.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
new_ents.o: bifparse.h new_ents.h doentity.h db_tools.h bifmacro.h ph_map.h
new_ents.o: globals.h ../.././X11/Xfuncs.h
gen_ents.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
gen_ents.o: /usr/include/machine/ansi.h /usr/include/math.h
gen_ents.o: ../.././X11/Xosdefs.h /usr/include/stdlib.h biftypes.h bifbuild.h
gen_ents.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
gen_ents.o: /usr/include/sys/types.h /usr/include/machine/endian.h
gen_ents.o: /usr/include/machine/types.h ../.././X11/X.h
gen_ents.o: ../.././X11/Xfuncproto.h /usr/include/stddef.h
gen_ents.o: ../.././X11/Xutil.h ../.././X11/Xresource.h
gen_ents.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
gen_ents.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
gen_ents.o: bifparse.h bifmacro.h
init_bench.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
init_bench.o: /usr/include/machine/ansi.h biftypes.h bifbuild.h
init_bench.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
init_bench.o: /usr/include/sys/types.h /usr/include/machine/endian.h
init_bench.o: /usr/include/machine/types.h ../.././X11/X.h
init_bench.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
init_bench.o: /usr/include/stddef.h ../.././X11/Xutil.h
init_bench.o: ../.././X11/Xresource.h ../.././X11/phigs/attr.h
init_bench.o: ../.././X11/phigs/phigscfunc.h ../.././X11/phigs/phigsextrn.h
init_bench.o: ../.././X11/phigs/phigserr.h globals.h ph_map.h bifparse.h
init_bench.o: stopwatch.h ../.././X11/Xatom.h /usr/include/ctype.h
init_bench.o: /usr/include/runetype.h brfexption.h brftypes.h brfexmacro.h
listbufs.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
listbufs.o: /usr/include/machine/ansi.h biftypes.h bifbuild.h
listbufs.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
listbufs.o: /usr/include/sys/types.h /usr/include/machine/endian.h
listbufs.o: /usr/include/machine/types.h ../.././X11/X.h
listbufs.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
listbufs.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
listbufs.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
listbufs.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
listbufs.o: bifmacro.h ph_map.h
maptools.o: biftypes.h bifbuild.h ../.././X11/phigs/phigs.h
maptools.o: ../.././X11/Xlib.h /usr/include/sys/types.h
maptools.o: /usr/include/machine/endian.h /usr/include/sys/cdefs.h
maptools.o: /usr/include/machine/ansi.h /usr/include/machine/types.h
maptools.o: ../.././X11/X.h ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
maptools.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
maptools.o: /usr/include/stdio.h ../.././X11/phigs/attr.h
maptools.o: ../.././X11/phigs/phigscfunc.h ../.././X11/phigs/phigsextrn.h
maptools.o: ../.././X11/phigs/phigserr.h bifparse.h bifmacro.h ph_map.h
matrix.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
matrix.o: /usr/include/machine/ansi.h /usr/include/math.h biftypes.h
matrix.o: bifbuild.h ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
matrix.o: /usr/include/sys/types.h /usr/include/machine/endian.h
matrix.o: /usr/include/machine/types.h ../.././X11/X.h
matrix.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
matrix.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
matrix.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
matrix.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
matrix.o: bifmacro.h ph_map.h
traverser.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
traverser.o: /usr/include/machine/ansi.h bifbuild.h biftypes.h
traverser.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
traverser.o: /usr/include/sys/types.h /usr/include/machine/endian.h
traverser.o: /usr/include/machine/types.h ../.././X11/X.h
traverser.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
traverser.o: /usr/include/stddef.h ../.././X11/Xutil.h
traverser.o: ../.././X11/Xresource.h ../.././X11/phigs/attr.h
traverser.o: ../.././X11/phigs/phigscfunc.h ../.././X11/phigs/phigsextrn.h
traverser.o: ../.././X11/phigs/phigserr.h bifparse.h db_tools.h ph_map.h
brf_except.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
brf_except.o: /usr/include/machine/ansi.h biftypes.h bifbuild.h
brf_except.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
brf_except.o: /usr/include/sys/types.h /usr/include/machine/endian.h
brf_except.o: /usr/include/machine/types.h ../.././X11/X.h
brf_except.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
brf_except.o: /usr/include/stddef.h ../.././X11/Xutil.h
brf_except.o: ../.././X11/Xresource.h ../.././X11/phigs/attr.h
brf_except.o: ../.././X11/phigs/phigscfunc.h ../.././X11/phigs/phigsextrn.h
brf_except.o: ../.././X11/phigs/phigserr.h globals.h bifparse.h brfexption.h
brf_except.o: brftypes.h brfexmacro.h
fillcont.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
fillcont.o: /usr/include/machine/ansi.h ../.././X11/Xosdefs.h
fillcont.o: /usr/include/stdlib.h bifbuild.h biftypes.h
fillcont.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
fillcont.o: /usr/include/sys/types.h /usr/include/machine/endian.h
fillcont.o: /usr/include/machine/types.h ../.././X11/X.h
fillcont.o: ../.././X11/Xfuncproto.h /usr/include/stddef.h
fillcont.o: ../.././X11/Xutil.h ../.././X11/Xresource.h
fillcont.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
fillcont.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
fillcont.o: bifparse.h new_ents.h doentity.h db_tools.h bifmacro.h ph_map.h
fillcont.o: globals.h
pixbuf.o: /usr/include/stdio.h /usr/include/sys/cdefs.h
pixbuf.o: /usr/include/machine/ansi.h biftypes.h bifbuild.h
pixbuf.o: ../.././X11/phigs/phigs.h ../.././X11/Xlib.h
pixbuf.o: /usr/include/sys/types.h /usr/include/machine/endian.h
pixbuf.o: /usr/include/machine/types.h ../.././X11/X.h
pixbuf.o: ../.././X11/Xfuncproto.h ../.././X11/Xosdefs.h
pixbuf.o: /usr/include/stddef.h ../.././X11/Xutil.h ../.././X11/Xresource.h
pixbuf.o: ../.././X11/phigs/attr.h ../.././X11/phigs/phigscfunc.h
pixbuf.o: ../.././X11/phigs/phigsextrn.h ../.././X11/phigs/phigserr.h
pixbuf.o: bifmacro.h bifparse.h globals.h
stopwatch.o: ../.././X11/Xosdefs.h /usr/include/stdio.h
stopwatch.o: /usr/include/sys/cdefs.h /usr/include/machine/ansi.h
stopwatch.o: /usr/include/sys/types.h /usr/include/machine/endian.h
stopwatch.o: /usr/include/machine/types.h /usr/include/sys/time.h
stopwatch.o: /usr/include/sys/time.h stopwatch.h
