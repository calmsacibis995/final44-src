/*
 * make makefile
 */

DMAKEPP = "$(LIBDIR)/cpp"
DMAKERULES = "$(LIBDIR)/Makerules.mo"

#if exists(/bin/ksh)
DMAKESHELL = "/bin/ksh"				/* latest version	*/
#elif exists(/usr/lbin/ksh)
DMAKESHELL = "/usr/lbin/ksh"			/* not /bin/sh		*/
#elif exists(/usr/local/bin/ksh)
DMAKESHELL = "/usr/local/bin/ksh"		/* not /bin/sh		*/
#else
DMAKESHELL = "/bin/sh"				/* default		*/
#endif

PROFILE =
RANLIB =
SCAN =

#if exists(/bin/ranlib) || exists(/usr/bin/ranlib)
RANLIB = 1					/* manual ar sym dir	*/
#endif

.SOURCE.h : $(INCLUDEDIR)
.SOURCE.a : $(LIBDIR)

nmake :: README RELEASE HISTORY make-intro.0 nmake.1 Makerules.mk \
	make.h configure.h \
	gram.y archive.c bind.c command.c compile.c dump.c expand.c\
	main.c make.c malloc.c misc.c read.c scan.c state.c version.c\
	-lx (PROFILE)

main.o : (DMAKEPP) (DMAKESHELL) (DMAKERULES) (RANLIB)

gram.o version.o : .READONLY

state.o : (SCAN)

.INSTALL : rules

rules : $(DMAKERULES)

$(DMAKERULES) : Makerules.mk
	$(MAKE:) $(-) -bcf $(>)
	$(MV) $(>:BS=.mo) $(<)

/*
 * local installation of nmake, mkcv, mkold, Makerules.mo, cpp, default.h
 * this will change when /bin/make -> /bin/omake
 */

#if exists(/usr/local/ebin)
LOCALBIN=/usr/local/ebin
#elif exists(/usr/lbin)
LOCALBIN=/usr/lbin
#else
LOCALBIN=/usr/local/bin
#endif
LOCALINCLUDE=/usr/local/include
#if exists(/usr/local/elib)
LOCALLIB=/usr/local/elib
#elif exists(/usr/llib)
LOCALLIB=/usr/llib
#else
LOCALLIB=/usr/local/lib
#endif
#if exists(/usr/local/lman)
LOCALMAN=/usr/local/lman/man
#else
LOCALMAN=/usr/local/man/man
#endif

local : .local.init $(LOCALBIN)/nmake $(LOCALLIB)/Makerules.mo \
		$(LOCALLIB)/cpp $(LOCALLIB)/default.h $(LOCALBIN)/mkcv \
		$(LOCALLIB)/mkcv1 $(LOCALLIB)/mkcv2 $(LOCALBIN)/mkold \
		$(LOCALLIB)/mkold2 $(LOCALLIB)/libx.a $(LOCALMAN)1/nmake.1 \
		$(LOCALINCLUDE)/default.h $(LOCALINCLUDE)/generic.h \
		$(LOCALINCLUDE)/hash.h

$(LOCALBIN)/nmake : .DOINSTALL nmake

$(LOCALMAN)1/nmake.1 : nmake.1

$(LOCALLIB)/Makerules.mo : .DOINSTALL $(LIBDIR)/Makerules.mo

$(LOCALLIB)/cpp : .DOINSTALL $(LIBDIR)/cpp

$(LOCALLIB)/libx.a : .DOINSTALL libx.a

$(LOCALINCLUDE)/default.h : .DOINSTALL default.h

$(LOCALINCLUDE)/generic.h : .DOINSTALL generic.h

$(LOCALLIB)/default.h : .DOINSTALL default.h

$(LOCALINCLUDE)/hash.h : .DOINSTALL hash.h

$(LOCALBIN)/mkcv : .backup.sh $(BINDIR)/mkcv

$(LOCALLIB)/mkcv1 : .DOINSTALL $(LIBDIR)/mkcv1

$(LOCALLIB)/mkcv2 : .DOINSTALL $(LIBDIR)/mkcv2

$(LOCALBIN)/mkold : .backup.sh $(BINDIR)/mkold

$(LOCALLIB)/mkold2 : .DOINSTALL $(LIBDIR)/mkold2

.local.init : .MAKE .NOTOUCH
	DMAKEPP="$(LOCALLIB)/cpp"
	DMAKERULES="$(LOCALLIB)/Makerules.mo"

.backup.sh : .USE
	if	test -f $(<)
	then	$(MV) $(<) $(<).old
	fi
	$(SED) -e 's@.*DIR=.*@BINDIR=$(LOCALBIN) LIBDIR=$(LOCALLIB)@' < $(>) > $(<)
	$(CHMOD) +x $(<)
