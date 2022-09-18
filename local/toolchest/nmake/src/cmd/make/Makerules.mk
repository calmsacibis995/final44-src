/*
 * G. S. Fowler
 * AT&T Bell Laboratories
 *
 * default make rules
 *
 * conventions:
 *
 *	internal make names match the RE \.[.A-Z][.A-Z0-9]*
 *	internal shell names match the RE _[a-z][a-z0-9]*_
 *	${!:-$$} is the proper way to generate tmp file names
 *	every (non-builtin shell) command should use a make variable
 *	the flags for command $(XYZ) are $(XYZFLAGS)
 */

#include "configure.h"

.STAMP. = "@(#)Makerules (AT&T Bell Laboratories) 08/30/85a"

/*
 * implicit makefile names -- tried in order
 */

.MAKEFILES : Makefile makefile

/*
 * common directories
 */

BINDIR = $(ROOT|HOME)/bin
ETCDIR = $(ROOT|HOME)/etc
INCLUDEDIR = $(ROOT|HOME)/include
LIBDIR = $(ROOT|HOME)/lib
MANDIR = $(ROOT|HOME)/man/man

/*
 * preset symbols
 */

AR = ar
ARFLAGS = r
AS = as
CC = cc
CCFLAGS = -O
CHMOD = chmod
CP = cp
CPIO = cpio
CPIOFLAGS = -ocv
CPP = /lib/cpp
CTAGS = ctags
ED = ed
F77 = f77

#if SCCS
GET = get
#endif

INSTALL = install
INSTALLDIR = $(BINDIR)
LD = ld
LEX = lex

#if exists(/usr/lib/lint/)
LINTLIB = /usr/lib/lint
#else
LINTLIB = /usr/lib
#endif
LINT1 = $(LINTLIB)/lint1
LINT2 = $(LINTLIB)/lint2

LN = ln
LP = lp

#if release(system5)
LPROF = lprof
#endif

MV = mv
PR = pr
RANLIB = ranlib
RM = rm
RMFLAGS = -f
SED = sed
TAR = tar
TARFLAGS = cvf

#if SCCS
UNGET = $(RM) $(RMFLAGS)
#endif

YACC = yacc
YACCFLAGS = -d

/*
 * special symbols
 */

.FILES. =
.OBJECTS = $(.FILES:G=.o:BS=.o)
.OUTPUT =
.SOURCES = $(.FILES:T=F:N=[!-]*[!.]?) $(.FILES:T=F:N=[!-]*.[!ao])

/*
 * stop expansion of certain state variables
 */

.NOEXPAND : .ATTRIBUTE

(AS) (ASFLAGS) (CC) (CCFLAGS) (LD) (LDFLAGS) (LDLIBRARIES) (LEX) (LEXFLAGS) (YACC) (YACCFLAGS) : .NOEXPAND

/*
 * special rules
 */

#if SCCS
.PREFIXES : s.
#endif

.SOURCE : .
.SUFFIXES : .o .c .r .f .y .l .s .sh .h .a

/*
 * suffix attributes
 */

.ARCHIVE : .a
.CURRENT : .a .o
.SEARCH : .c .h .y .l

/*
 * prefix rules
 */

#if SCCS
* : s.* .CURRENT .FOREGROUND
	$(GET) $(GETFLAGS) -p -s $(>) > $(<)
#endif

/*
 * single suffix rules
 */

* : * (CC) (LDFLAGS) (LDLIBRARIES)
	$(CC) $(LDFLAGS) $(CCFLAGS:N=-[!DIOU]*) $(F77FLAGS:N=-[!DIOU]*) $(&:A!=.NOEXPAND:T=D=-[!DIOUl]*) -o $(<) $(*) $(LDLIBRARIES)

*.a : * (AR) (ARFLAGS)
	$(AR) $(ARFLAGS) $(<) $(>) $(ARUPDATE)
	$(RM) $(RMFLAGS) $(>)

* : *.c (CC) (CCFLAGS) (LDFLAGS) (LDLIBRARIES)
	$(CC) $(CCFLAGS) $(LDFLAGS) -o $(<) $(*) $(LDLIBRARIES)

* : *.r *.f (F77) (F77FLAGS) (LDFLAGS) (LDLIBRARIES)
	$(F77) $(F77FLAGS) $(LDFLAGS) -o $(<) $(*) $(LDLIBRARIES)

* : *.s (CC) (ASFLAGS) (LDFLAGS) (LDLIBRARIES)
	$(CC) $(ASFLAGS) $(LDFLAGS) -o $(<) $(*) $(LDLIBRARIES)

* : *.sh
	if	test '$(&:T=E)' != ''
#if release(system5)
	then	echo '$(&:T=E)' > $(<)
#else
	then	read _first_ < $(>)
		case $_first_ in
		\#!*)	echo $_first_ > $(<) ;;
		*)	> $(<) ;;
		esac
		echo '$(&:T=E)' >> $(<)
#endif
		cat $(>) >> $(<)
	else	$(CP) $(>) $(<)
	fi
	$(CHMOD) +x $(<)

/*
 * double suffix rules
 */

*.o : *.c (CC) (CCFLAGS)
	$(CC) $(CCFLAGS) -c $(>)

*.o : *.r *.f (F77) (F77FLAGS)
	$(F77) $(F77FLAGS) -c $(>)

*.o : *.l (CC) (CCFLAGS) (LEX) (LEXFLAGS)
	$(@.l.c)
	$(CC) $(CCFLAGS) -c $(>:DBS=.c)
	$(RM) $(RMFLAGS) $(>:DBS=.c)

*.o : *.s (AS) (ASFLAGS)
	$(AS) $(ASFLAGS) -o $(<:BS) $(>)

*.o : *.y .FOREGROUND (CC) (CCFLAGS) (YACC) (YACCFLAGS)
	$(@.y.c)
	$(CC) $(CCFLAGS) -c $(>:DBS=.c)
	$(RM) $(RMFLAGS) $(>:DBS=.c)

*.c : *.l (LEX) (LEXFLAGS)
	$(LEX) $(LEXFLAGS) $(>)
	$(MV) lex.yy.c $(>:DBS=.c)

*.c : *.y .FOREGROUND (YACC) (YACCFLAGS)
	$(YACC) $(YACCFLAGS) $(>)
	if	test -s y.tab.h
	then	if	cmp -s y.tab.h $(>:DBS=.h)
		then	$(RM) $(RMFLAGS) y.tab.h
		else	$(MV) y.tab.h $(>:DBS=.h)
		fi
	fi
	$(MV) y.tab.c $(>:DBS=.c)

#if exists(/usr/add-on/S/)

/*
 * S specific rules -- S source must have suffix .S
 */

SHOME = /usr/add-on/S
SINCLUDE = $(SHOME)/newfun/include

M4 = m4
RATFOR = ratfor

.SUFFIXES : .S .m
.SOURCE.m : $(SINCLUDE)

(M4) (M4FLAGS) (RATFOR) (RATFORFLAGS) (F77) (F77FLAGS) : .NOEXPAND

*.o : *.S (M4) (M4FLAGS) (RATFOR) (RATFORFLAGS) (F77) (F77FLAGS) (SHOME)
	$(RM) $(RMFLAGS) $(<:D=/tmp:B:S=.*)
	$(M4) $(M4FLAGS) $(&:A!=.NOEXPAND:T=D) $(SINCLUDE)/u/mach.m $(SINCLUDE)/ratfor.m $(>) > $(<:D=/tmp:B:S=.r)
	$(RATFOR) $(RATFORFLAGS) "-6&" < $(<:D=/tmp:B:S=.r) > $(<:D=/tmp:B:S=.f)
	$(F77) $(F77FLAGS) -c $(<:D=/tmp:B:S=.f)
	$(RM) $(RMFLAGS) $(<:D=/tmp:B:S=.*)

.SHEADER : .USE $$(<<:BS=.m)
	echo "g/(\`/s// /\ng/',\`*/s//	/\ng/'*)/s///\n1,\$s/^/#/\nw $(<)\nq" | $(ED) - $(>)
#endif

/*
 * .USE command scripts
 */

.DOINSTALL : .USE
	if	test -f $(<)
	then	$(MV) $(<) $(<).old
	fi
	ignore $(CP) $(>) $(<)

#if machine(balance8000)
.READONLY : .NOTOUCH { }
#else
.READONLY : .USE .IMPLICIT
	$(@.READONLY$(>:S)|@$(>:S).o)

.READONLY.c : .USE .IMPLICIT
#if architecture(vax) || architecture(tahoe)
#if release(bsd) || release(research)
	$(CC) $(CCFLAGS) -R -c $(>)
#elif release(system5)
	$(CC) $(CCFLAGS) -Wa,-r -c $(>)
#endif
#else
#if release(apollo)
	occ $(CCFLAGS) -S $(>)
#else
	$(CC) $(CCFLAGS) -S $(>)
#endif
#if architecture(ibm370) || release(uts)
	$(SED) -e 's/^\([ 	]*\.*\)idat/\1code/' $(<:BS=.s) > c.${!:-$$}.s
#elif release(sun)
	$(SED) -e 's/^\([ 	]*\.*\)data$/\1text/' $(<:BS=.s) > c.${!:-$$}.s
#else
	$(SED) -e 's/^\([ 	]*\.*\)data/\1text/' $(<:BS=.s) > c.${!:-$$}.s
#endif
	$(AS) $(ASFLAGS) -o $(<:BS) c.${!:-$$}.s
	$(RM) $(RMFLAGS) $(<:BS=.s) c.${!:-$$}.s
#endif

.READONLY.l : .USE .IMPLICIT
	$(LEX) $(LEXFLAGS) $(>)
	$(MV) lex.yy.c $(>:D:P=l.:B=lex:S=.c)
	$(ED) - $(>:D:P=l.:B=lex:S=.c) > l.dat.c <<!
	/struct yysvf[ 	]*{/;.,/}/p
	/define[ 	][ 	]*YYTYPE/p
	/struct yywork[ 	]*{/s/^.*}/&;\\
	struct yywork /
	-p
	$(@.YYFIX:/YY/yycrank/)
	$(@.YYFIX:/YY/yyvstop/)
	$(@.YYFIX:/YY/yysvec/)
	$(@.YYFIX:/YY/yymatch/)
	$(@.YYFIX:/YY/yyextra/)
	w
	q
	!
#if architecture(vax) || architecture(tahoe)
#if release(bsd) || release(research)
	$(CC) $(CCFLAGS) -R -c l.dat.c
#elif release(system5)
	$(CC) $(CCFLAGS) -Wa,-r -c l.dat.c
#endif
#else
#if release(apollo)
	occ $(CCFLAGS) -S l.dat.c
#else
	$(CC) $(CCFLAGS) -S l.dat.c
#endif
#if architecture(ibm370) || release(uts)
	$(SED) -e 's/^\([ 	]*\.*\)idat/\1code/' l.dat.s > l.${!:-$$}.s
#elif release(sun)
	$(SED) -e 's/^\([ 	]*\.*\)data$/\1text/' l.dat.s > l.${!:-$$}.s
#else
	$(SED) -e 's/^\([ 	]*\.*\)data/\1text/' l.dat.s > l.${!:-$$}.s
#endif
	$(AS) $(ASFLAGS) -o l.dat.o l.${!:-$$}.s
#endif
	$(CC) $(CCFLAGS) -c $(>:D:P=l.:B=lex:S=.c)
	$(LD) -r $(&:A!=.NOEXPAND:T=D=-[!DIOUl]*) -o $(<:BS) l.dat.o l.lex.o
	$(RM) $(RMFLAGS) l.*.* $(>:D:P=l.:B=lex:S=.c)

.READONLY.y : .USE .IMPLICIT
	$(YACC) $(YACCFLAGS) $(>)
	if	test -s y.tab.h
	then	if	cmp -s y.tab.h $(>:DBS=.h)
		then	$(RM) $(RMFLAGS) y.tab.h
		else	$(MV) y.tab.h $(>:DBS=.h)
		fi
	fi
	$(MV) y.tab.c $(>:D:P=y.:B=yac:S=.c)
	$(ED) - $(>:D:P=y.:B=yac:S=.c) > y.dat.c <<!
	g/typedef.*yyt[a-z]*;/p
	$(@.YYFIX:/YY/yyexca/)
	$(@.YYFIX:/YY/yyact/)
	$(@.YYFIX:/YY/yypact/)
	$(@.YYFIX:/YY/yypgo/)
	$(@.YYFIX:/YY/yyr1/)
	$(@.YYFIX:/YY/yyr2/)
	$(@.YYFIX:/YY/yychk/)
	$(@.YYFIX:/YY/yydef/)
#if release(system5)
	/^#[ 	]*ifndef[ 	][ 	]*YYDEBUG/;/^#[ 	]*endif/p
	/^#[ 	]*if[ 	][ 	]*YYDEBUG/p
	$(@.YYFIX:/YY/yytoks/)
	$(@.YYFIX:/YY/yyreds/)
	/^#[ 	]*endif/p
#endif
	w
	q
	!
#if architecture(vax) || architecture(tahoe)
#if release(bsd) || release(research)
	$(CC) $(CCFLAGS) -R -c y.dat.c
#elif release(system5)
	$(CC) $(CCFLAGS) -Wa,-r -c y.dat.c
#endif
#else
#if release(apollo)
	occ $(CCFLAGS) -S y.dat.c
#else
	$(CC) $(CCFLAGS) -S y.dat.c
#endif
#if architecture(ibm370) || release(uts)
	$(SED) -e 's/^\([ 	]*\.*\)idat/\1code/' y.dat.s > y.${!:-$$}.s
#elif release(sun)
	$(SED) -e 's/^\([ 	]*\.*\)data$/\1text/' y.dat.s > y.${!:-$$}.s
#else
	$(SED) -e 's/^\([ 	]*\.*\)data/\1text/' y.dat.s > y.${!:-$$}.s
#endif
	$(AS) $(ASFLAGS) -o y.dat.o y.${!:-$$}.s
#endif
	$(CC) $(CCFLAGS) -c $(>:D:P=y.:B=yac:S=.c)
	$(LD) -r $(&:A!=.NOEXPAND:T=D=-[!DIOUl]*) -o $(<:BS) y.dat.o y.yac.o
	$(RM) $(RMFLAGS) y.*.* $(>:D:P=y.:B=yac:S=.c)

.YYFIX:
	/^\(.*\)YY[ 	]*\[]/s//extern \1 YY[];\\
	\1 YY []/
	.ka
	/}/kb
	'a,'bp
	'a,'bd
#endif

/*
 * operator rules
 */

"::" : .MAKE .OPERATOR
	.FILES.$(<:B) := $(>:N=[!.]*) $(>:N=.[!A-Z]*)
	.FILES. += $\(.FILES.$(<:B))
	.TARGETS += $(<)
	.ALL : $(<)
	$(.OUTPUT:T=N).OUTPUT := $(<:B)
	.TMP1 =
	$(@:T=V).TMP1 = { $(@:V) }
	.TMP2 := $(>:N=-l*:/$/.a/)
	.TMP2 := $(.TMP2:/-l/lib/)
	$(<) : .NULL $(>:N=.[a-zA-Z]*) $(>:N=*.ld) $(>:N=*.sh:B) $(>:G=.o:BS=.o) $(>:N=*(*)) $(>:N=[!-]*.a) $(.TMP2) $(.TMP1)
	.TMP1 := $(>:G=.o)
	.TMP2 := $(>:N=*.*:G=)
	$(.TMP1:T=N)$(.TMP2:T=V)$(<) : .IMPLICIT
	.TMP1 := $(>:N=*(*))
	.TMP2 := $(>:G=.o:BS=.o)
	$(.TMP1:T=V)$(.TMP2:T=V)$(.TMP2) : $(.TMP1)
	.TMP1 := $(>:N=[!-]*.y)
	$(.TMP1:T=V)$(.TMP1:BS=.h) : .DONTCARE
	.TMP1 := $(INSTALLDIR:N=$(BINDIR))
	$(.TMP1:T=N).TMP2 := $(INSTALLDIR)
	$(.TMP1:T=V).TMP2 := $(<:N=*.a)
	$(.TMP1:T=V)$(.TMP2:T=V).TMP2 := $(LIBDIR)
	$(.TMP1:T=V)$(.TMP2:T=N).TMP2 := $(BINDIR)
	$(.INSTALL.$(<):T=V).TMP2 := $(.INSTALL.$(<))
	.TMP1 := $(<:N=$(<:D=$(.TMP2):BS))
	$(.TMP1:T=N)$(<:D=$(.TMP2):BS) : .DOINSTALL $(<)
	$(.TMP1:T=N).INSTALL : $(<:D=$(.TMP2):BS)
	.TMP1 := $(>:N=*.[1-9]*)
	$(.TMP1:T=V).TMP2 = $(.TMP1:N=*.1*:D=$$$(MANDIR)1:PBS) $(.TMP1:N=*.2*:D=$$$(MANDIR)2:PBS) \
		$(.TMP1:N=*.3*:D=$$$(MANDIR)3:PBS) $(.TMP1:N=*.4*:D=$$$(MANDIR)4:PBS) \
		$(.TMP1:N=*.5*:D=$$$(MANDIR)5:PBS) $(.TMP1:N=*.6*:D=$$$(MANDIR)6:PBS) \
		$(.TMP1:N=*.7*:D=$$$(MANDIR)7:PBS) $(.TMP1:N=*.8*:D=$$$(MANDIR)8:PBS) \
		$(.TMP1:N=*.9*:D=$$$(MANDIR)9:PBS)
	$(.TMP1:T=V)$(.TMP2:T=B) : .DOINSTALL $(.TMP1)
	$(.TMP1:T=V).INSTALL : $(.TMP2)
	.TMP1 := $(>:N=-l*)
	$(.TMP1:T=V)$(.TMP1) : .DONTCARE

#if DEBUG
/*
 * experimental operator -- gsf
 * used for a.out targets with only one source, skipping the .o file
 */

":-" : .MAKE .OPERATOR
	.FILES.$(<:B) := $(>)
	.FILES. += $\(.FILES.$(<:B))
	.TARGETS += $(>:N=*.[!aho]:DB)
	.TMP1 =
	$(@:T=V).TMP1 = { $(@:V) }
	.ALL : $(>:N=*.[!aho]:DB) $(.TMP1)
	$(.OUTPUT:T=N).OUTPUT := $(<:B)
	.TMP1 := $(<:N=$(<:D=$(INSTALLDIR):BS))
	$(.TMP1:T=N)$(>:N=*.[!aho]:D=$(INSTALLDIR):B) : .DOINSTALL $$(<:B)
	$(.TMP1:T=N).INSTALL : $(>:N=*.[!aho]:D=$(INSTALLDIR):B)
	.TMP1 := $(>:N=*(*))
	$(.TMP1:T=V)$(>:G=.o:BS=.o) : $(.TMP1)
	.TMP1 := $(>:N=*.a)
	$(.TMP1:T=V)LDLIBRARIES += $(.TMP1)
	.TMP1 := $(>:N=-l*)
	$(.TMP1:T=V)$(.TMP1) : .DONTCARE
	$(.TMP1:T=V)LDLIBRARIES += $(.TMP1)
#endif

/*
 * make scripts
 */

.GENFILES : .MAKE .NOTOUCH
	.TMP1 := $(?)
	$(.TMP1:T=V).FILES := $(.TMP1:P=$\(.FILES.:B:S=\))
	$(.TMP1:T=V)$(.FILES:T=N)$(:E=$(.TMP1)\: files not found)
	$(.TMP1:T=N).FILES = $(.FILES.)
	.FILES += $(MAKEFILE)

.MAKEINIT : .MAKE
	$(SRCPATH:T=V).SOURCE .SOURCE.h : .INSERT . $(SRCPATH:/\:/ /)
	.TMP1 := $("(CCFLAGS)":T=S)	/* this binds (CCFLAGS) */
	CCFLAGS += $(*.SOURCE.h:/^/-I/) $$(&:A!=.NOEXPAND:T=D)
#if exists(/usr/include/CC/)
	.TMP1 = /usr/include/CC
#elif exists(/usr/local/include/CC/)
	.TMP1 = /usr/local/include/CC
#else
	.TMP1 =
#endif
	.TMP2 := $(CC:N=*CC)
	$(.TMP2:T=N).TMP1 =
	$(-X:T=N).SOURCE.h : $(.TMP1) /usr/include
	$(-X:T=N).SOURCE.a : /lib /usr/lib

.UPDATE : .GENFILES .UPDATE0 $$(UTIME:/^$/($$(<<)))
.UPDATE0 : .NOTOUCH .MAKE
	.TMP1 := $(.SOURCES)
	.TMP2 := { $$$(@$(<<<:/.U/./)) }
	.SOURCES = $(>)
	.OPTIONS : -x
	$(UTIME:/^$/($(<<<))/) : .CLEAR $(.TMP1) $(.TMP2)
.UPDATE.FILE : .MAKE .NOTOUCH
	$(UTIME:T=N)UTIME := $(.OUTPUT|"files":DPBS=$(<<:/.U/./:F=L))

/*
 * common actions
 *
 *	$(.FILES)	:: source files from command args (via .GENFILES)
 *	$(.FILES.)	all :: source files
 *	$(.FILES.targ)	source files for :: target targ
 *	$(.OBJECTS)	object files generated by $(.FILES)
 *	$(.OUTPUT)	common action output base name
 *	$(.SOURCES)	printable source files in $(.FILES)
 *	$(UTIME)	time stamp file for .U* actions
 */

.ARCH : .GENFILES
	$(AR) ru $(.OUTPUT|"files":DPBS=.arch) `echo $(.SOURCES) | sort -u`

.CLEAN : .GENFILES
	$(RM) $(RMFLAGS) $(.OBJECTS:T=F$(-m:T=N?!=*[/]*))

.CLOBBER : .CLEAN
	$(RM) $(RMFLAGS) $("core":T=F) $(MAKEFILE:BS=.m[os]) $(.TARGETS:T=F$(-m:T=N?!=*[/]*))

.CPIO : .GENFILES
	echo $(.SOURCES) | tr ' ' '\012' | sort -u | $(CPIO) $(CPIOFLAGS) > $(.OUTPUT|"files":DPBS=.cpio)

.CTAGS : .GENFILES
	$(CTAGS) $(CTAGSFLAGS) $(.SOURCES:N=*.[cfhly])

.INSTALL : .ALL

.LINT : .MAKE .NOTOUCH
	.OPTIONS : -xFMOj1 +m
	$(-n:T=N).OPTIONS : -s
#if release(system5)
	LINT1 += -H$$(<<:BS=.lh)
#elif release(research)
	LINT1 += -S$$(<<:BS=.lh)
#endif
	LINTLIBRARIES += $(LINTLIB)/llib-lc.ln
	.GLOBAL .GLOBAL.a : $$(<<:T=T?.LINT0)
	.LINT0 : .NOTOUCH { $(RM) $(RMFLAGS) $(<<:BS=.ln) }
	$(*.SUFFIXES:T=T) : { }
	.TMP1 = $(*.SUFFIXES://&.o)
	$(.TMP1:T=T) : { }
	*.o : *.c { echo $(>):
	{ $(CPP) $(CCFLAGS:N=-[DIU]*) -C -Dlint $(>) | $(LINT1) $(LINTFLAGS) -b >> $(<<:BS=.ln) ;} 2>&1 }
	*.o : *.y { echo $(>):
	$(@.y.c)
	{ $(CPP) $(CCFLAGS:N=-[DIU]*) -C -Dlint $(>:DBS=.c) | $(LINT1) $(LINTFLAGS) >> $(<<:BS=.ln) ;} 2>&1
	$(RM) $(RMFLAGS) $(>:DBS=.c) }
	*.o : *.l { echo $(>):
	$(@.l.c)
	{ $(CPP) $(CCFLAGS:N=-[DIU]*) -C -Dlint $(>:DBS=.c) | $(LINT1) $(LINTFLAGS) >> $(<<:BS=.ln) ;} 2>&1
	$(RM) $(RMFLAGS) $(>:DBS=.c) }
	* : *.a { ...
	$(RM) $(RMFLAGS) $(<:BS=.ln) }
	* : * { echo $(<)::
	cat $(<:BS=.ln) $(*:N=[!-]*.a:T=T:BS=.ln) $(*:N=-l*:C@@$(LINTLIB)/llib&.ln@) $(LINTLIBRARIES) > /usr/tmp/l$$.ln
#if release(system5)
	if	test -s $(<:BS=.lh)
	then	_x_=-H$(<:BS=.lh)
	else	_x_=
	fi
	$(LINT2) -T/usr/tmp/l$$.ln $_x_ $(LINTFLAGS)
#elif release(research)
	$(LINT2) /usr/tmp/l$$.ln -S$(<:BS=.lh) $(LINTFLAGS)
#else
	$(LINT2) /usr/tmp/l$$.ln $(LINTFLAGS)
#endif
	$(RM) $(RMFLAGS) /usr/tmp/l$$.ln $(<:BS=.l[hn]) $(*:N=[!-]*.a:T=T:BS=.l[hn]) }

#if release(system5)
.LPROF : .MAKE .NOTOUCH
	.OPTIONS : -xFMO
	.GLOBAL : .LPROF0 .LPROF1 $$(<<:DBS=.cnt)
	.LPROF0 : .MAKE .NOTOUCH { .LPROFFILES= }
	.LPROF1 : .POST { $(LPROF) $(LPROFFLAGS) -r "$(.LPROFFILES:/^ //)" -o $(<<) -c $(<<:DBS=.cnt) }
	.TMP1 = $(*.SUFFIXES://&.o)
	$(.TMP1:T=T) : { }
	*.o : *.c *.l *.y .MAKE { .LPROFFILES += $(>) }
	* : * *.a { }
#endif

.PRINT : .GENFILES
	$(PR) $(PRFLAGS) $(.SOURCES:N!=*.[0-9]*) | $(LP) $(LPFLAGS)

.TAR : .GENFILES
	$(TAR) $(TARFLAGS) $(.OUTPUT|"files":DPBS=.tar) `echo $(.SOURCES) | tr ' ' '\012' | sort -u`

.UARCH : .UPDATE.FILE .UPDATE

.UCPIO : .UPDATE.FILE .UPDATE

.UPRINT : .UPDATE

.UTAR : .UPDATE.FILE .UPDATE
