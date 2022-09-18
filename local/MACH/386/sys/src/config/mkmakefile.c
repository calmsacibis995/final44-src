/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mkmakefile.c,v $
 * Revision 2.19.1.1  90/02/01  13:37:36  rvb
 * 	Cast all sprintf's (void).
 * 	Allow for profiling I386.
 * 	[90/01/22            rvb]
 * 
 * Revision 2.19  89/09/09  16:23:18  rvb
 * 	Set maxusers min and default for i386 to 2.
 * 	[89/09/09            rvb]
 * 
 * Revision 2.18  89/07/11  13:38:17  jjc
 * 	Made changes for Sun 4.
 * 	[89/07/05  20:18:51  jjc]
 * 
 * Revision 2.17  89/05/30  10:42:14  rvb
 * 	For MIPS, swapgeneric.c is in the gdir not .
 * 	[89/05/30  08:34:23  rvb]
 * 
 * Revision 2.16  89/04/10  00:26:10  rpd
 * 	Don't unlink the old Makefile; rename it to Makefile.old.
 * 	This works around a problem with in-kernel AFS.
 * 
 * Revision 2.15  89/03/09  21:12:53  rpd
 * 	More cleanup.
 * 
 * Revision 2.14  89/02/25  19:24:15  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.13  89/02/19  18:43:03  rpd
 * 	Moved fopenp, VPATH declarations to config.h.
 * 	
 * 	Added migmachinefiles, migdebugmachinefiles.
 * 
 * Revision 2.12  89/02/07  22:55:50  mwyoung
 * Code cleanup cataclysm.
 * 
 * Revision 2.11  89/01/31  01:21:47  rpd
 * 	Change final system build rule to cause all interface files to
 * 	be built first.  Parallel makes break without this.
 * 	This is not quite right because it forces the
 * 	debug interfaces to be built even when they're not used.
 * 	[89/01/26            dlb]
 * 
 * 	Add ${BASE} hack to SOURCE_DIR to allow use of old pmake until
 * 	mja and company properly support the Multimax.
 * 	[88/10/13            dlb]
 * 
 * Revision 2.10  89/01/23  22:24:03  af
 * 	Lots of changes:
 * 		1. Spit out SOBJS and COBJS as .o's derived from CFILES
 * 	and SFILES respectively. ($(SOBJS): assym.h)
 * 		2. Spit out makevariables AFTER %MACHDEP expansion.
 * 		3. Expand makevariables and options in forward order.
 * 		4. Generalize SQT FASTOBJS to ORDERED.  Files labeled
 * 	ordered have rules generated but do not appear in OBJS, so you
 * 	get to say where they belong.
 * 		5. Generalized (and purged) volatile ...  Now if you have
 * 	a "|" at the end of a line in the files file, all the remaining
 * 	text will be include in the rule expansion.
 * 		6. MAXDSIZ is now in confdep.h
 * 		7. cpu names are treated like options to enable "files"
 * 		8. Support for MIPS and I386
 * 	[89/01/09            rvb]
 * 
 * Revision 2.9  88/11/23  16:42:39  rpd
 * 	Added PRELDDEPS to dependencies for vmunix.sys lines.
 * 	Like LDDEPS, but come before LDOBJS instead of after.
 * 	[88/11/05  13:47:21  rpd]
 * 
 * Revision 2.8  88/08/09  18:03:04  rvb
 * Treat vax like ns32000 and emit \; at the end of the rules
 * 
 * Revision 2.7  88/07/29  03:21:05  rpd
 * Changed get_VPATH, to ensure that the current directory is first on VPATH.
 * This makes config compatible with make in its use of VPATH.
 * 
 * Revision 2.6  88/07/19  20:48:31  mwyoung
 * Move ${P} up against ":" for ".sys" lines.
 * 
 * Revision 2.5  88/07/19  17:46:13  mwyoung
 * Put backslashes at the end of compilation rules lines for all
 * architectures, not just NS32000.  Ideally, the parallel make
 * program would run the last *non-empty* line in parallel, making
 * this unnecessary, but it doesn't.
 * 
 * Revision 2.4  88/07/15  16:11:00  mja
 * Added get_VPATH() routine and changed to fopenp() configuration
 * files from ../conf along VPATH.
 * 
 * 30-Jun-88  Robert Baron (rvb) at Carnegie-Mellon University
 *	Generate vax rules on one line for parallel build just like for
 *	ns3200's.
 *
 *  6-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Remove "Makefile" from the "all:" dependency.
 *
 *  3-Jun-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Allow filenames starting with "./" to be included in the "files"
 *	file(s).
 *
 * 28-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Allow source directory to be other than "..".
 *
 *  5-Feb-88  Sue LoVerso (sue) at Encore Computer Corporation
 *	Added .ORDER to "all:" target string so that with parallel
 *	make those particular dependencies will get done serially.
 *
 * 14-Dec-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Allow profiling for sun3.  And
 *	Do not replace LIBS line by LIBS_P in Makefile.<template> when
 *	profiling -- why would I want a different library?
 *
 * 09-Nov-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Move load dependencies to *.sys where they belong instead of
 *	*.swap;  added SYSDEPS variable to final system build rule.
 *	[ V5.1(XF21) ]
 *
 * 27-Oct-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	Treat balance drivers like any other driver.
 *
 * 10-Oct-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Define LOAD variable (with all target system names) at end of
 *	%LOAD macro expansion.
 *	[ V5.1(XF18) ]
 *
 * 29-May-87  David Black (dlb) at Carnegie-Mellon University
 *	mmax profiling changes: use -p because -pg doesn't work,
 *		don't define GPROF.EX.
 *
 * 27-Apr-87  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Removed code which knew about RDB and TCC symbols, since
 *	they weren't doing anything useful anymore anyway.
 *
 * 22-Apr-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Reduce minimum users for VAX from 8 to 2.
 *	[ V5.1(F10) ]
 *
 * 27-Mar-87  Robert Baron (rvb) at Carnegie-Mellon University
 *	allow profiling for mmax and sqt
 *
 *  2-Mar-87  Rich Sanzi (sanzi) at Carnegie-Mellon University
 *	Added code in do_machdep() to redefine LIBS when we are building
 *	a profiled kernel.
 *
 * 27-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Make C and S rule change apply for ns32000 only (which includes
 *	Sequent at this time).  This should be done a better way.
 *
 * 27-Feb-87  Rich Sanzi (sanzi) at Carnegie-Mellon University
 *	Added MACHINE_ROMP to types of machines which we can profile.
 *
 * 24-Feb-87  David L. Black (dlb) at Carnegie-Mellon University
 *	Also do C and S rule change of 21-Feb-87 on Multimax (ns32000).
 *
 * 21-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	The name of the Makefile template is now Makefile.template.
 *
 * 21-Feb-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Cause C and S rules to be generated on the "same" line... they
 *	are actually on different lines, but use \ at the end to make
 *	think they are on the same line (only done if running on Sequent).
 *
 * 13-Feb-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Added leading '#' character comment line capability to
 *	read_files() so that we can start maintaining history logs in
 *	those files also.
 *	[ V5.1(F2) ]
 *
 * 29-Jan-87  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Umax_memconf -> memconf.mmax
 *
 * 19-Jan-87  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed to use ../conf/Makefile as the standard machine
 *	independent template makefile but to then substitute the
 *	contents of ../conf/Makefile.<machinename> for a "%MACHDEP"
 *	(although the size of the machine dependent descriptions is now
 *	typically very small).
 *	[ V5.1(F1) ]
 *
 * 08-Jan-87  Robert Beck (beck) at Sequent Computer Systems, Inc.
 *	Add MACHINE_SQT cases.  SQT assumes "sedit" for now.
 *
 * 16-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Made a new routine (do_files) which subsumes do_cfiles and
 *	do_sfiles.  This is also now used for handling binary-only files
 *	which have a .b extension and are referenced with BFILES.
 *
 * 13-Nov-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Get gmon.ex in ../machine instead of /usr/src.
 *
 * 27-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in David Black's changes for the Multimax.
 *
 * 22-Oct-86  Jonathan J. Chew (jjc) at Carnegie-Mellon University
 *	Merged in Dave Golub's and my changes for the Sun:
 *		1) Added code to allow listing in the "files" file any
 *		   object files that don't have a corresponding source
 *		   file.
 *		2) Changed "do_rules" to produce an action to have the
 *		   preprocessor create an intermediate file to pass to
 *		   the assembler rather than pipe it in because the Sun
 *		   68020 assembler must have an input file.
 *		3) Modified "makefile" to include name of machine in 
 *		   definition of "IDENT".
 *		4) Modified "do_systemspec" to link mbglue.o into vmunix.
 *
 *  4-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Changed all references of CMUCS to CMU.
 *
 *  4-Oct-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Change kernel build to not execute the "make Makefile."
 *	Instead, it directly executes the "md" command, saving the time
 *	for make to search the Makefile for the command.
 *
 * 27-Sep-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Removed %MAKEFILE definition (now defined again in
 *	template); changed to generate %RULES in terms of macros
 *	which are also defined in template rather than wiring the
 *	commands in here; changed to generate only minimal load and
 *	swap rules so the details can again all be defined in the
 *	template;  changed to send parameters to a header file
 *	rather than the PARAM variable; fixed copy_dependencies() to
 *	avoid replicating the salutation and blank lines every time.
 *
 *	N.B.  The machine type specific constructs for the SUN and
 *	RT which used to be generated here and were removed have not
 *	been merged into the template makefiles for each of these
 *	machines since there was no simple way to test them on a Vax.
 *	I'll be happy to assist whoever ends up merging them for these
 *	machines.  Also, the various template makefiles need to be
 *	generated from a common master source before much longer but I
 *	don't have any good ideas at the moment.
 *
 * 10-Sep-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	We also create an empty "M.n" file to avoid startup errors.
 *
 *  4-Sep-86  Bill Bolosky (bolosky) at Carnegie-Mellon University
 *	Eliminated emulate.o if not makeing for a vax.
 *
 * 29-Aug-86  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Added "Makefile" to the list of objects for "all".
 *
 *  6-Aug-86  David Golub (dbg) at Carnegie-Mellon University
 *	added lines for newvers > vers.c.  Also dropped "first" check
 *	   for stepping vers.
 *
 * 10-Jul-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Removed cputype initialization in the IDENT variable.  It is
 *	now sent to a header file instead.
 *
 * 24-Jun-86  Mike Accetta (mja) at Carnegie-Mellon University
 *	Fixed not to close a NULL file pointer if no previous
 *	makefile exists when attempting to copy dependencies.
 *
 * 20-Jun-86  Robert V. Baron (rvb) at Carnegie-Mellon University
 *	3# And dependencies from an existing Makefile are appended.
 *
 * 25-Jan-86  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Upgraded to 4.3.
 *
 * 17-Oct-85  Mike Accetta (mja) at Carnegie-Mellon University
 *	Changed to turn OPTIONS symbols internally into pseudo-device
 *	entries for file lines beginning with "OPTIONS/" so that
 *	include files are generated for these symbols.
 *
 * 12-Aug-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Modified to process files ending in ".s" with the preprocessor
 *	and assembler.
 *
 */

/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef	lint
static char sccsid[] = "@(#)mkmakefile.c	5.9 (Berkeley) 5/6/86";
#endif	not lint

/*
 * Build the makefile for the system, from
 * the information in the files files and the
 * additional files for the machine being compiled to.
 */

#include <stdio.h>
#include <ctype.h>
#include "y.tab.h"
#include "config.h"

#define next_word(fp, wd) \
	{ register char *word = get_word(fp); \
	  if (word == (char *)EOF) \
		return; \
	  else \
		wd = word; \
	}

static	struct file_list *fcur;
char *tail();

/*
 * Lookup a file, by name.
 */
struct file_list *
fl_lookup(file)
	register char *file;
{
	register struct file_list *fp;

	for (fp = ftab ; fp != 0; fp = fp->f_next) {
		if (eq(fp->f_fn, file))
			return (fp);
	}
	return (0);
}

/*
 * Lookup a file, by final component name.
 */
struct file_list *
fltail_lookup(file)
	register char *file;
{
	register struct file_list *fp;

	for (fp = ftab ; fp != 0; fp = fp->f_next) {
		if (eq(tail(fp->f_fn), tail(file)))
			return (fp);
	}
	return (0);
}

/*
 * Make a new file list entry
 */
struct file_list *
new_fent()
{
	register struct file_list *fp;

	fp = (struct file_list *) malloc(sizeof *fp);
	fp->f_needs = 0;
	fp->f_next = 0;
	fp->f_flags = 0;
	fp->f_type = 0;
	fp->f_extra = (char *) 0;
	if (fcur == 0)
		fcur = ftab = fp;
	else
		fcur->f_next = fp;
	fcur = fp;
	return (fp);
}

char	*COPTS;
static	struct users {
	int	u_default;
	int	u_min;
	int	u_max;
} users[] = {
	{ 24, 2, 1024 },		/* MACHINE_VAX */
	{  8, 2, 32 },			/* MACHINE_SUN */
	{ 16, 4, 32 },			/* MACHINE_ROMP */
	{  8, 2, 32 },			/* MACHINE_SUN2 */
	{  8, 2, 32 },			/* MACHINE_SUN3 */
	{ 24, 8, 1024},			/* MACHINE_MMAX */
	{ 32, 8, 1024},			/* MACHINE_SQT */
	{  8, 2, 32 },			/* MACHINE_SUN4 */
	{  2, 2, 1024 },		/* MACHINE_I386 */
	{ 32, 8, 1024 },		/* MACHINE_IX */
	{ 32, 8, 1024 },		/* MACHINE_MIPSY */
	{ 32, 8, 1024 },		/* MACHINE_MIPS*/
};
#define NUSERS	(sizeof (users) / sizeof (users[0]))

char *
get_VPATH()
{
    static char *vpath = NULL;
    extern char *getenv();

    if ((vpath == NULL) &&
	((vpath = getenv("VPATH")) != NULL) &&
	(*vpath != ':')) {
	register char *buf = malloc((unsigned)(strlen(vpath) + 2));

	vpath = strcat(strcpy(buf, ":"), vpath);
    }

    return vpath ? vpath : "";
}


/*
 * Build the makefile from the skeleton
 */
makefile()
{
	FILE *ifp, *ofp;
	FILE *dfp;
	char pname[BUFSIZ];
	char line[BUFSIZ];
	struct opt *op;
	struct users *up;
	extern int build_cputypes();
	extern int build_confdep();

	read_files();
	(void) sprintf(line, "%s/Makefile.template", config_directory);
	ifp = fopenp(VPATH, line, pname, "r");
	if (ifp == 0) {
		perror(line);
		exit(1);
	}
	dfp = fopen(path("Makefile"), "r");
	rename(path("Makefile"), path("Makefile.old"));
	if ((ofp = fopen(path("M.d"), "w")) == NULL) {
		perror(path("M.d"));
		/* We'll let this error go */
	}
	else
	 	fclose(ofp);
	ofp = fopen(path("Makefile"), "w");
	if (ofp == 0) {
		perror(path("Makefile"));
		exit(1);
	}
	fprintf(ofp, "SOURCE_DIR=${BASE}%s\n", source_directory);

	if (machine == MACHINE_SUN || machine == MACHINE_SUN2 
	    || machine == MACHINE_SUN3 || machine == MACHINE_SUN4)
		fprintf(ofp, "IDENT=-D%s -D%s", machinename, raise(ident));
	else
		fprintf(ofp, "IDENT=-D%s", raise(ident));
	if (profiling)
		fprintf(ofp, " -DGPROF");
	if (cputype == 0) {
		printf("cpu type must be specified\n");
		exit(1);
	}
	do_build("cputypes.h", build_cputypes);
	for (op = opt; op; op = op->op_next)
		if (op->op_value)
			fprintf(ofp, " -D%s=\"%s\"", op->op_name, op->op_value);
		else
			fprintf(ofp, " -D%s", op->op_name);
	fprintf(ofp, "\n");
	if (hadtz == 0)
		printf("timezone not specified; gmt assumed\n");
	if ((unsigned)machine > NUSERS) {
		printf("maxusers config info isn't present, using vax\n");
		up = &users[MACHINE_VAX-1];
	} else
		up = &users[machine-1];
	if (maxusers == 0) {
		printf("maxusers not specified; %d assumed\n", up->u_default);
		maxusers = up->u_default;
	} else if (maxusers < up->u_min) {
		printf("minimum of %d maxusers assumed\n", up->u_min);
		maxusers = up->u_min;
	} else if (maxusers > up->u_max)
		printf("warning: maxusers > %d (%d)\n", up->u_max, maxusers);
	do_build("confdep.h", build_confdep);
	while (fgets(line, BUFSIZ, ifp) != 0) {
		if (*line == '%')
			goto percent;
		if (profiling && strncmp(line, "COPTS=", 6) == 0) {
			register char *cp;
			if (machine != MACHINE_MMAX)
			    fprintf(ofp,
				"GPROF.EX=$(SOURCE_DIR)/%s/gmon.ex\n", machinename);
			cp = index(line, '\n');
			if (cp)
				*cp = 0;
			cp = line + 6;
			while (*cp && (*cp == ' ' || *cp == '\t'))
				cp++;
			COPTS = malloc((unsigned)(strlen(cp) + 1));
			if (COPTS == 0) {
				printf("config: out of memory\n");
				exit(1);
			}
			strcpy(COPTS, cp);
			if (machine == MACHINE_MIPSY || machine == MACHINE_MIPS) {
				fprintf(ofp, "%s ${CCPROFOPT}\n", line);
				fprintf(ofp, "PCOPTS=%s\n", cp);
			} else if (machine == MACHINE_MMAX)
				fprintf(ofp, "%s -p\n",line);
			else
				fprintf(ofp, "%s -pg\n", line);
			continue;
		}
		fprintf(ofp, "%s", line);
		continue;
	percent:
		if (eq(line, "%OBJS\n"))
			do_objs(ofp, "OBJS=", -1);
		else if (eq(line, "%CFILES\n")) {
			do_files(ofp, "CFILES=", 'c');
			do_objs(ofp, "COBJS=", 'c');
		} else if (eq(line, "%SFILES\n")) {
			do_files(ofp, "SFILES=", 's');
			do_objs(ofp, "SOBJS=", 's');
		} else if (eq(line, "%BFILES\n"))
			do_files(ofp, "BFILES=", 'b');
		else if (eq(line, "%MACHDEP\n")) {
			do_machdep(ofp);
			for (op = mkopt; op; op = op->op_next)
				fprintf(ofp, "%s=%s\n", op->op_name, op->op_value);
		} else if (eq(line, "%ORDERED\n"))
			do_ordered(ofp);
		else if (eq(line, "%RULES\n"))
			do_rules(ofp);
		else if (eq(line, "%LOAD\n"))
			do_load(ofp);
		else
			fprintf(stderr,
			    "Unknown %% construct in generic makefile: %s",
			    line);
	}
	if (dfp != NULL)
	{
		copy_dependencies(dfp, ofp);
		(void) fclose(dfp);
	}
	(void) fclose(ifp);
	(void) fclose(ofp);
}

/*
 * Read in the information about files used in making the system.
 * Store it in the ftab linked list.
 */
read_files()
{
	FILE *fp;
	register struct file_list *tp, *pf;
	register struct device *dp;
	register struct opt *op;
	char *wd, *this, *needs, *devorprof;
	int options;
	int not_option;
	int ordered;
	int sedit;				/* SQT */
	char pname[BUFSIZ];
	char fname[1024];
	char *rest = (char *) 0;
	struct cputype *cp;
	int nreqs, first = 1, configdep, isdup;

	ftab = 0;
	(void) sprintf(fname, "%s/files", config_directory);
openit:
	fp = fopenp(VPATH, fname, pname, "r");
	if (fp == 0) {
		perror(fname);
		exit(1);
	}
next:
	options = 0;
	rest = (char *) 0;
	/*
	 * filename	[ standard | optional ] [ config-dependent ]
	 *	[ dev* | profiling-routine ] [ device-driver]
	 */
	/*
	 * MACHINE_SQT ONLY:
	 *
	 * filename	[ standard | optional ] 
	 *	[ config-dependent | ordered | sedit ]
	 *	[ dev* | profiling-routine ] [ device-driver]
	 */
	wd = get_word(fp);
	if (wd == (char *)EOF) {
		(void) fclose(fp);
		if (first == 1) {
			(void) sprintf(fname, "%s/files.%s", config_directory, machinename);
			first++;
			goto openit;
		}
		if (first == 2) {
			(void) sprintf(fname, "files.%s", raise(ident));
			first++;
			fp = fopenp(VPATH, fname, pname, "r");
			if (fp != 0)
				goto next;
		}
		return;
	}
	if (wd == 0)
		goto next;
	/*
	 *  Allow comment lines beginning witha '#' character.
	 */
	if (*wd == '#')
	{
		while ((wd=get_word(fp)) && wd != (char *)EOF)
			;
		goto next;
	}
	this = ns(wd);
	next_word(fp, wd);
	if (wd == 0) {
		printf("%s: No type for %s.\n",
		    fname, this);
		exit(1);
	}
	if ((pf = fl_lookup(this)) && (pf->f_type != INVISIBLE || pf->f_flags))
		isdup = 1;
	else
		isdup = 0;
	tp = 0;
	if (first == 3 && (tp = fltail_lookup(this)) != 0)
		printf("%s: Local file %s overrides %s.\n",
		    fname, this, tp->f_fn);
	nreqs = 0;
	devorprof = "";
	configdep = 0;
	ordered = 0;
	sedit = 1;				/* SQT: assume sedit for now */
	needs = 0;
	if (eq(wd, "standard"))
		goto checkdev;
	if (!eq(wd, "optional")) {
		printf("%s: %s must be optional or standard\n", fname, this);
		exit(1);
	}
	if (strncmp(this, "OPTIONS/", 8) == 0)
		options++;
	not_option = 0;
nextopt:
	next_word(fp, wd);
	if (wd == 0)
		goto doneopt;
	if (eq(wd, "config-dependent")) {
		configdep++;
		goto nextopt;
	}
	if (eq(wd, "ordered")) {
		ordered++;
		goto nextopt;
	}
	if (machine == MACHINE_SQT && eq(wd, "sedit")) {
		sedit++;
		goto nextopt;
	}
	if (eq(wd, "not")) {
		not_option = !not_option;
		goto nextopt;
	}
	devorprof = wd;
	if (eq(wd, "device-driver") || eq(wd, "profiling-routine")) {
		next_word(fp, wd);
		goto save;
	}
	nreqs++;
	if (needs == 0 && nreqs == 1)
		needs = ns(wd);
	if (isdup)
		goto invis;
	if (options)
	{
		register struct opt *op;
		struct opt *lop = 0;
		struct device tdev;

		/*
		 *  Allocate a pseudo-device entry which we will insert into
		 *  the device list below.  The flags field is set non-zero to
		 *  indicate an internal entry rather than one generated from
		 *  the configuration file.  The slave field is set to define
		 *  the corresponding symbol as 0 should we fail to find the
		 *  option in the option list.
		 */
		init_dev(&tdev);
		tdev.d_name = ns(wd);
		tdev.d_type = PSEUDO_DEVICE;
		tdev.d_flags++;
		tdev.d_slave = 0;

		for (op=opt; op; lop=op, op=op->op_next)
		{
			char *od = raise(ns(wd));

			/*
			 *  Found an option which matches the current device
			 *  dependency identifier.  Set the slave field to
			 *  define the option in the header file.
			 */
			if (strcmp(op->op_name, od) == 0)
			{
				tdev.d_slave = 1;
				if (lop == 0)
					opt = op->op_next;
				else
					lop->op_next = op->op_next;
				free(op);
				op = 0;
			 }
			free(od);
			if (op == 0)
				break;
		}
		newdev(&tdev);
	}
 	for (dp = dtab; dp != 0; dp = dp->d_next) {
		if (eq(dp->d_name, wd) && (dp->d_type != PSEUDO_DEVICE || dp->d_slave)) {
			if (not_option)
				goto invis;	/* dont want file if option present */
			else
				goto nextopt;
		}
	}
	if (not_option)
		goto nextopt;		/* want file if option missing */
	for (op = opt; op != 0; op = op->op_next)
		if (op->op_value == 0 && opteq(op->op_name, wd)) {
			if (nreqs == 1) {
				free(needs);
				needs = 0;
			}
			goto nextopt;
		}
	for (cp = cputype; cp; cp = cp->cpu_next)
		if (opteq(cp->cpu_name, wd)) {
			if (nreqs == 1) {
				free(needs);
				needs = 0;
			}
			goto nextopt;
		}
invis:
	while ((wd = get_word(fp)) != 0)
		;
	if (tp == 0)
		tp = new_fent();
	tp->f_fn = this;
	tp->f_type = INVISIBLE;
	tp->f_needs = needs;
	tp->f_flags = isdup;
	goto next;

doneopt:
	if (nreqs == 0) {
		printf("%s: what is %s optional on?\n",
		    fname, this);
		exit(1);
	}

checkdev:
	if (wd) {
		if (*wd == '|')
			goto getrest;
		next_word(fp, wd);
		if (wd) {
			if (eq(wd, "config-dependent")) {
				configdep++;
				goto checkdev;
			}
			if (eq(wd, "ordered")) {
				ordered++;
				goto checkdev;
			}
			if (machine == MACHINE_SQT && eq(wd, "sedit")) {
				sedit++;
				goto checkdev;
			}
			devorprof = wd;
			next_word(fp, wd);
		}
	}

save:
getrest:
	if (wd) {
		if (*wd == '|') {
			rest = ns(get_rest(fp));
		} else {
			printf("%s: syntax error describing %s\n",
			       fname, this);
			exit(1);
		}
	}
	if (eq(devorprof, "profiling-routine") && profiling == 0)
		goto next;
	if (tp == 0)
		tp = new_fent();
	tp->f_fn = this;
	tp->f_extra = rest;
	if (options)
		tp->f_type = INVISIBLE;
	else
	if (eq(devorprof, "device-driver"))
		tp->f_type = DRIVER;
	else if (eq(devorprof, "profiling-routine"))
		tp->f_type = PROFILING;
	else
		tp->f_type = NORMAL;
	tp->f_flags = 0;
	if (configdep)
		tp->f_flags |= CONFIGDEP;
	if (ordered)
		tp->f_flags |= ORDERED;
	if (sedit)				/* SQT */
		tp->f_flags |= SEDIT;
	tp->f_needs = needs;
	if (pf && pf->f_type == INVISIBLE)
		pf->f_flags = 1;		/* mark as duplicate */
	goto next;
}

opteq(cp, dp)
	char *cp, *dp;
{
	char c, d;

	for (; ; cp++, dp++) {
		if (*cp != *dp) {
			c = isupper(*cp) ? tolower(*cp) : *cp;
			d = isupper(*dp) ? tolower(*dp) : *dp;
			if (c != d)
				return (0);
		}
		if (*cp == 0)
			return (1);
	}
}
put_source_file_name(fp, tp)
	FILE *fp;
	register struct file_list *tp;
{
	if ((tp->f_fn[0] == '.') && (tp->f_fn[1] == '/'))
		fprintf(fp, "%s ", tp->f_fn);
	 else
		fprintf(fp, "$(SOURCE_DIR)/%s ", tp->f_fn);
}

do_objs(fp, msg, ext)
	char	*msg;
	int	ext;
	FILE *fp;
{
	register struct file_list *tp, *fl;
	register int lpos, len;
	register char *cp, och, *sp;
	char swapname[32];

	fprintf(fp, msg);
	lpos = strlen(msg);
	for (tp = ftab; tp != 0; tp = tp->f_next) {
		if (tp->f_type == INVISIBLE)
			continue;

		/*
		 *	Check for '.o' file in list
		 */
		cp = tp->f_fn + (len = strlen(tp->f_fn)) - 1;
		if ((ext == -1 && tp->f_flags & ORDERED) ||		/* not in objs */
		    (ext != -1 && *cp != ext))
			continue;
		else if (*cp == 'o') {
			if (len + lpos > 72) {
				lpos = 8;
				fprintf(fp, "\\\n\t");
			}
			put_source_file_name(fp, tp);
			fprintf(fp, " ");
			lpos += len + 1;
			continue;
		}
		sp = tail(tp->f_fn);
		for (fl = conf_list; fl; fl = fl->f_next) {
			if (fl->f_type != SWAPSPEC)
				continue;
			(void) sprintf(swapname, "swap%s.c", fl->f_fn);
			if (eq(sp, swapname))
				goto cont;
		}
		cp = sp + (len = strlen(sp)) - 1;
		och = *cp;
		*cp = 'o';
		if (len + lpos > 72) {
			lpos = 8;
			fprintf(fp, "\\\n\t");
		}
		fprintf(fp, "%s ", sp);
		lpos += len + 1;
		*cp = och;
cont:
		;
	}
	if (lpos != 8)
		putc('\n', fp);
}

/* not presently used and probably broken,  use ORDERED instead */
do_ordered(fp)
	FILE *fp;
{
	register struct file_list *tp, *fl;
	register int lpos, len;
	register char *cp, och, *sp;
	char swapname[32];

	fprintf(fp, "ORDERED=");
	lpos = 10;
	for (tp = ftab; tp != 0; tp = tp->f_next) {
		if ((tp->f_flags & ORDERED) != ORDERED)
			continue;
		sp = tail(tp->f_fn);
		cp = sp + (len = strlen(sp)) - 1;
		och = *cp;
		*cp = 'o';
		if (len + lpos > 72) {
			lpos = 8;
			fprintf(fp, "\\\n\t");
		}
		fprintf(fp, "%s ", sp);
		lpos += len + 1;
		*cp = och;
cont:
		;
	}
	if (lpos != 8)
		putc('\n', fp);
}

do_files(fp, msg, ext)
	FILE	*fp;
	char	*msg;
	char	ext;
{
	register struct file_list *tp;
	register int lpos, len;

	fprintf(fp, msg);
	lpos = 8;
	for (tp = ftab; tp != 0; tp = tp->f_next) {
		if (tp->f_type == INVISIBLE)
			continue;
		if (tp->f_fn[strlen(tp->f_fn)-1] != ext)
			continue;
		/*
		 * Always generate a newline.
		 * Our Makefile's aren't readable anyway.
		 */

		lpos = 8;
		fprintf(fp, "\\\n\t");
		put_source_file_name(fp, tp);
		lpos += len + 1;
	}
	if (lpos != 8)
		putc('\n', fp);
}

/*
 *  Include machine dependent makefile in output
 */

do_machdep(ofp)
	FILE *ofp;
{
	int c;
	FILE *ifp;
	char pname[BUFSIZ];
	char line[BUFSIZ];

	(void) sprintf(line, "%s/Makefile.%s", config_directory, machinename);
	ifp = fopenp(VPATH, line, pname, "r");
	if (ifp == 0) {
		perror(line);
		exit(1);
	}
	while (fgets(line, BUFSIZ, ifp) != 0) {
#ifdef	whydef
		if (profiling && (strncmp(line, "LIBS=", 5) == 0)) 
			fprintf(ofp,"LIBS=${LIBS_P}\n");
		else
#endif	whydef
			fputs(line, ofp);
	}
	fclose(ifp);
}



/*
 *  Format configuration dependent parameter file.
 */

build_confdep(fp)
	FILE *fp;
{
	fprintf(fp,
	    "#define TIMEZONE %d\n#define MAXUSERS %d\n#define DST %d\n",
	    timezone, maxusers, dst);
	fprintf(fp,
	    "#define MAXDSIZ 0x%x\n", maxdsiz);
}



/*
 *  Format cpu types file.
 */

build_cputypes(fp)
	FILE *fp;
{
	struct cputype *cp;

	for (cp = cputype; cp; cp = cp->cpu_next)
		fprintf(fp, "#define\t%s\t1\n", cp->cpu_name);
}



/*
 *  Build a define parameter file.  Create it first in a temporary location and
 *  determine if this new contents differs from the old before actually
 *  replacing the original (so as not to introduce avoidable extraneous
 *  compilations).
 */

do_build(name, format)
	char *name;
	int (*format)();
{
	static char temp[]="#config.tmp";
	FILE *tfp, *ofp;
	int c;

	tfp = fopen(path(temp), "w+");
	if (tfp == 0) {
		perror(path(temp));
		exit(1);
	}
	unlink(path(temp));
	(*format)(tfp);
	ofp = fopen(path(name), "r");
	if (ofp != 0)
	{
		fseek(tfp, 0, 0);
		while ((c = fgetc(tfp)) != EOF)
			if (fgetc(ofp) != c)
				goto copy;
		if (fgetc(ofp) == EOF)
			goto same;
		
	}
copy:
	if (ofp)
		fclose(ofp);
	ofp = fopen(path(name), "w");
	if (ofp == 0) {
		perror(path(name));
		exit(1);
	}
	fseek(tfp, 0, 0);
	while ((c = fgetc(tfp)) != EOF)
		fputc(c, ofp);
same:
	fclose(ofp);
	fclose(tfp);
}

char *
tail(fn)
	char *fn;
{
	register char *cp;

	cp = rindex(fn, '/');
	if (cp == 0)
		return (fn);
	return (cp+1);
}

/*
 * Create the makerules for each file
 * which is part of the system.
 * Devices are processed with the special c2 option -i
 * which avoids any problem areas with i/o addressing
 * (e.g. for the VAX); assembler files are processed by as.
 */
do_rules(f)
	FILE *f;
{
	register char *cp, *np, och, *tp;
	register struct file_list *ftp;
	char *extras;
	char *nl = "; \\";
	char *source_dir;

for (ftp = ftab; ftp != 0; ftp = ftp->f_next) {
	if (ftp->f_type == INVISIBLE)
		continue;
	cp = (np = ftp->f_fn) + strlen(ftp->f_fn) - 1;
	och = *cp;
	/*
	 *	Don't compile '.o' files
	 */
	if (och == 'o')
		continue;
	/*
	 *	Determine where sources should come from
	 */
	if ((np[0] == '.') && (np[1] == '/')) {
		source_dir = "";
		np += 2;
	} else
		source_dir = "$(SOURCE_DIR)/";
	*cp = '\0';
	if (och == 'o') {
		fprintf(f, "%so: %so\n\t${O_RULE_1A}%s%.*s${O_RULE_1B}\n\n",
			   tail(np), np, source_dir, tp-np, np);
		continue;
	}
	fprintf(f, "%so: %s%s%c\n", tail(np), source_dir, np, och);
	tp = tail(np);
	if (och == 's') {
	    switch (machine) {
		case MACHINE_MIPSY:
		case MACHINE_MIPS:
			switch (ftp->f_type) {
			case NORMAL:
			case DRIVER:
				fprintf(f, "\t@${RM} %so\n", tp);
				fprintf(f, "\t${CC} ${CCASFLAGS}%s %s%s%ss\n\n",
				    (ftp->f_extra?ftp->f_extra:""), extras, source_dir, np);
				break;

			case PROFILING:
				if (!profiling)
					continue;
				fprintf(f, "\t@${RM} %so\n", tp);
				fprintf(f, "\t${CC} ${CCPASFLAGS}%s %s%s%ss\n\n",
				    (ftp->f_extra?ftp->f_extra:""), extras, source_dir, np);
				break;

			default:
				printf("Don't know rules for %s.s\n", np);
				break;
			}
			break;
		default:
		fprintf(f, "\t${S_RULE_1A}%s%.*s${S_RULE_1B}%s\n",
				source_dir, tp-np, np, nl);
		fprintf(f, "\t${S_RULE_2}%s\n", nl);
		fprintf(f, "\t${S_RULE_3}\n\n");
	    }
	    continue;
	}
	if (och == 'b') {
		fprintf(f, "\t${B_RULE_1A}%s%.*s${B_RULE_1B}\n\n", 
			source_dir, tp-np, np);
		continue;
	}
	if (ftp->f_flags & CONFIGDEP)
	{
	    fprintf(stderr,
	     "config: %s%c: \"config-dependent\" obsolete; include \"confdep.h\" instead\n", np, och);
	}
	else
		extras = "";
	switch (ftp->f_type) {

	case NORMAL:
		switch (machine) {

		case MACHINE_MIPSY:
		case MACHINE_MIPS:
			fprintf(f, "\t@${RM} %so\n", tp);
			fprintf(f, "\t${CC} ${CCNFLAGS}%s %s%s%sc\n\n",
				(ftp->f_extra?ftp->f_extra:""), extras, source_dir, np);
			continue;
#if	0
		case MACHINE_SQT:
			if (ftp->f_flags & SEDIT) {
				fprintf(f, "\t${CC} -SO ${COPTS} %s%s%sc | \\\n", extras, source_dir, np);
				fprintf(f, "\t${SEDCMD} | ${C2} | ${AS} ${CAFLAGS} -o %so\n\n", tp);
			} else {
				fprintf(f, "\t${CC} -c -O ${COPTS} %s%s%sc\n\n",
					source_dir, extras, np);
			}
			break;
#endif	0
		default:
			goto common;
		}
		break;

	case DRIVER:
		switch (machine) {

		case MACHINE_MIPSY:
		case MACHINE_MIPS:
			fprintf(f, "\t@${RM} %so\n", tp);
			fprintf(f, "\t${CC} ${CCDFLAGS}%s %s%s%sc\n\n",
				(ftp->f_extra?ftp->f_extra:""), extras, source_dir, np);
			continue;
		default:
			extras = "_D";
			goto common;
		}
		break;

	case PROFILING:
		if (!profiling)
			continue;
		if (COPTS == 0) {
			fprintf(stderr,
			    "config: COPTS undefined in generic makefile");
			COPTS = "";
		}
		switch (machine) {
			case MACHINE_MIPSY:
			case MACHINE_MIPS:
				fprintf(f, "\t@${RM} %so\n", tp);
				fprintf(f, "\t${CC} ${CCPFLAGS}%s %s../%sc\n\n",
				    (ftp->f_extra?ftp->f_extra:""), extras, np);
				continue;
			case MACHINE_VAX:
			case MACHINE_ROMP:
			case MACHINE_SQT:
			case MACHINE_MMAX:
			case MACHINE_SUN3:
			case MACHINE_SUN4:
			case MACHINE_I386:
				extras = "_P";
				goto common;
			default:
			fprintf(stderr,
			    "config: don't know how to profile kernel on this cpu\n");
			break;
		}

	common:
		fprintf(f, "\t${C_RULE_1A%s}", extras);
		if (ftp->f_extra)
			fprintf(f, "%s", ftp->f_extra);
		fprintf(f, "%s%.*s${C_RULE_1B%s}%s\n",
			   source_dir, (tp-np), np, extras, nl);
		fprintf(f, "\t${C_RULE_2%s}%s\n", extras, nl);
		fprintf(f, "\t${C_RULE_3%s}%s\n", extras, nl);
		fprintf(f, "\t${C_RULE_4%s}\n\n", extras);
		break;

	default:
		printf("Don't know rules for %s\n", np);
		break;
	}
	*cp = och;
}
}

/*
 * Create the load strings
 */
do_load(f)
	register FILE *f;
{
	register struct file_list *fl;
	int first = 1;
	struct file_list *do_systemspec();

	fl = conf_list;
	while (fl) {
		if (fl->f_type != SYSTEMSPEC) {
			fl = fl->f_next;
			continue;
		}
		fl = do_systemspec(f, fl, first);
		if (first)
			first = 0;
	}
	fprintf(f, "LOAD =");
	for (fl = conf_list; fl != 0; fl = fl->f_next)
		if (fl->f_type == SYSTEMSPEC)
			fprintf(f, " %s", fl->f_needs);
#ifdef	multimax
	fprintf(f, "\n\nall .ORDER: ${LOAD}\n");
#else	multimax
	fprintf(f, "\n\nall: ${LOAD}\n");
#endif	multimax
	fprintf(f, "\n");
}


struct file_list *
do_systemspec(f, fl, first)
	FILE *f;
	register struct file_list *fl;
	int first;
{

	fprintf(f, "migfiles ::\n\n");
	fprintf(f, "migmachinefiles ::\n\n");
	fprintf(f, "migdebugfiles ::\n\n");
	fprintf(f, "migdebugmachinefiles ::\n\n");

	fprintf(f, "%s .ORDER: migfiles migmachinefiles migdebugfiles migdebugmachinefiles %s.sys ${SYSDEPS}\n",
		fl->f_needs, fl->f_needs);
	fprintf(f, "\t${SYS_RULE_1}\n");
	fprintf(f, "\t${SYS_RULE_2}\n");
	fprintf(f, "\t${SYS_RULE_3}\n");
	fprintf(f, "\t${SYS_RULE_4}\n\n");
	do_swapspec(f, fl->f_fn, fl->f_needs);
	for (fl = fl->f_next; fl != NULL && fl->f_type == SWAPSPEC; fl = fl->f_next)
		continue;
	return (fl);
}

do_swapspec(f, name, system)
	char *system;
	FILE *f;
	register char *name;
{

	char *gdir = eq(name, "generic")?"$(SOURCE_DIR)/machine/":"";

	fprintf(f, "%s.sys:${P} ${PRELDDEPS} ${LDOBJS} ${LDDEPS}\n\n", system);
	fprintf(f, "%s.swap: swap%s.o\n", system, name);
	fprintf(f, "\t@cp swap%s.o $@\n\n", name);
	fprintf(f, "swap%s.o: %sswap%s.c ${SWAPDEPS}\n", name, gdir, name);
	if (machine == MACHINE_MIPSY || machine == MACHINE_MIPS) {
		fprintf(f, "\t@${RM} swap%s.o\n", name);
		fprintf(f, "\t${CC} ${CCNFLAGS} %sswap%s.c\n\n", gdir, name);
	} else {
		fprintf(f, "\t${C_RULE_1A}%s${C_RULE_1B}\n", gdir);
		fprintf(f, "\t${C_RULE_2}\n");
		fprintf(f, "\t${C_RULE_3}\n");
		fprintf(f, "\t${C_RULE_4}\n\n");
	}
}

char *
raise(str)
	register char *str;
{
	register char *cp = str;

	while (*str) {
		if (islower(*str))
			*str = toupper(*str);
		str++;
	}
	return (cp);
}

#define OLDSALUTATION "# DO NOT DELETE THIS LINE"

#define LINESIZE 1024
static char makbuf[LINESIZE];		/* one line buffer for makefile */

copy_dependencies(makin, makout)
register FILE *makin, *makout;
{
	register int oldlen = (sizeof OLDSALUTATION - 1);

	while (fgets(makbuf, LINESIZE, makin) != NULL) {
		if (! strncmp(makbuf, OLDSALUTATION, oldlen))
			break;
	}
	while (fgets(makbuf, LINESIZE, makin) != NULL) {
		if (oldlen != 0)
		{
			if (makbuf[0] == '\n')
				continue;
			else
				oldlen = 0;
		}
		fputs(makbuf, makout);
	}
}
