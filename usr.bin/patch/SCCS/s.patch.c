h33588
s 00000/00000/00800
d D 8.1 93/06/06 15:52:35 bostic 10 9
c 4.4BSD snapshot (revision 8.1)
e
s 00355/01534/00445
d D 5.9 88/02/18 10:20:36 bostic 9 8
c complete new version
e
s 00004/00004/01975
d D 5.8 86/05/18 07:39:31 van 8 7
c bug from J.Lepreau (apply_hunk adding extra line)
e
s 00076/00052/01903
d D 5.7 86/03/29 21:41:22 van 7 6
c fixed problems from J. Lepreau w/ diff -c1 output and 
c freeing memory twice.  Fixed problems from D. Kingston with 
c omitted context (using fix suggested by L.Wall, not Doug's). 
c Check for running off end of patch arrays if more than MAXHUNKSIZE 
c lines in patch and upped MAXHUNKSIZE from 500 to 2000.  Output 
c .rej file in new context diff format if input file is from new 
c context diff (so patch will be able to process .rej file).
e
s 00026/00007/01929
d D 5.6 86/03/07 09:20:45 bloom 6 5
c fix problems with premature EOF's, add flag to disable autoreverse
e
s 00012/00004/01924
d D 5.5 86/01/09 20:31:47 mckusick 5 4
c check for null string before calling strlen()
e
s 00009/00001/01919
d D 5.4 85/11/25 00:11:12 van 4 3
c fix for omitted new context lines at eof.  (better fix 
c coming soon)
e
s 00003/00001/01917
d D 5.3 85/08/16 20:00:49 mckusick 3 2
c off by one error (sez van@lbl)
e
s 00132/00005/01786
d D 5.2 85/08/16 18:36:43 mckusick 2 1
c changes for 4.3BSD diff -c (from van@lbl)
e
s 01791/00000/00000
d D 5.1 85/08/16 18:33:12 mckusick 1 0
c original from Larry Wall
e
u
U
t
T
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

I 9
char rcsid[] =
	"$Header: patch.c,v 2.0.1.4 87/02/16 14:00:04 lwall Exp $";

E 9
/* patch - a program to apply diffs to original files
 *
D 9
 * $Header: patch.c,v 1.3 85/03/26 15:07:43 lwall Exp $
E 9
I 9
 * Copyright 1986, Larry Wall
E 9
 *
D 9
 * Copyright 1984, Larry Wall
 *
E 9
 * This program may be copied as long as you don't try to make any
 * money off of it, or pretend that you wrote it.
 *
 * $Log:	patch.c,v $
I 9
 * Revision 2.0.1.4  87/02/16  14:00:04  lwall
 * Short replacement caused spurious "Out of sync" message.
 * 
 * Revision 2.0.1.3  87/01/30  22:45:50  lwall
 * Improved diagnostic on sync error.
 * Moved do_ed_script() to pch.c.
 * 
 * Revision 2.0.1.2  86/11/21  09:39:15  lwall
 * Fuzz factor caused offset of installed lines.
 * 
 * Revision 2.0.1.1  86/10/29  13:10:22  lwall
 * Backwards search could terminate prematurely.
 * 
 * Revision 2.0  86/09/17  15:37:32  lwall
 * Baseline for netwide release.
 * 
 * Revision 1.5  86/08/01  20:53:24  lwall
 * Changed some %d's to %ld's.
 * Linted.
 * 
 * Revision 1.4  86/08/01  19:17:29  lwall
 * Fixes for machines that can't vararg.
 * Added fuzz factor.
 * Generalized -p.
 * General cleanup.
 * 
E 9
I 2
 * 85/08/15 van%ucbmonet@berkeley
 * Changes for 4.3bsd diff -c.
 *
E 2
 * Revision 1.3  85/03/26  15:07:43  lwall
 * Frozen.
 * 
 * Revision 1.2.1.9  85/03/12  17:03:35  lwall
 * Changed pfp->_file to fileno(pfp).
 * 
 * Revision 1.2.1.8  85/03/12  16:30:43  lwall
 * Check i_ptr and i_womp to make sure they aren't null before freeing.
 * Also allow ed output to be suppressed.
 * 
 * Revision 1.2.1.7  85/03/12  15:56:13  lwall
 * Added -p option from jromine@uci-750a.
 * 
 * Revision 1.2.1.6  85/03/12  12:12:51  lwall
 * Now checks for normalness of file to patch.
 * 
 * Revision 1.2.1.5  85/03/12  11:52:12  lwall
 * Added -D (#ifdef) option from joe@fluke.
 * 
 * Revision 1.2.1.4  84/12/06  11:14:15  lwall
 * Made smarter about SCCS subdirectories.
 * 
 * Revision 1.2.1.3  84/12/05  11:18:43  lwall
 * Added -l switch to do loose string comparison.
 * 
 * Revision 1.2.1.2  84/12/04  09:47:13  lwall
 * Failed hunk count not reset on multiple patch file.
 * 
 * Revision 1.2.1.1  84/12/04  09:42:37  lwall
 * Branch for sdcrdcf changes.
 * 
 * Revision 1.2  84/11/29  13:29:51  lwall
 * Linted.  Identifiers uniqified.  Fixed i_ptr malloc() bug.  Fixed
 * multiple calls to mktemp().  Will now work on machines that can only
 * read 32767 chars.  Added -R option for diffs with new and old swapped.
 * Various cosmetic changes.
 * 
 * Revision 1.1  84/11/09  17:03:58  lwall
 * Initial revision
 * 
 */

D 9
#define DEBUGGING
E 9
I 9
#include "INTERN.h"
#include "common.h"
#include "EXTERN.h"
#include "version.h"
#include "util.h"
#include "pch.h"
#include "inp.h"
E 9

D 9
/* shut lint up about the following when return value ignored */

#define Signal (void)signal
#define Unlink (void)unlink
#define Lseek (void)lseek
#define Fseek (void)fseek
#define Fstat (void)fstat
#define Pclose (void)pclose
#define Close (void)close
#define Fclose (void)fclose
#define Fflush (void)fflush
#define Sprintf (void)sprintf
#define Mktemp (void)mktemp
#define Strcpy (void)strcpy
#define Strcat (void)strcat

#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <signal.h>

/* constants */

#define TRUE (1)
#define FALSE (0)

D 7
#define MAXHUNKSIZE 500
E 7
I 7
#define MAXHUNKSIZE 2000
E 7
#define MAXLINELEN 1024
#define BUFFERSIZE 1024
#define ORIGEXT ".orig"
#define SCCSPREFIX "s."
#define GET "get -e %s"
#define RCSSUFFIX ",v"
#define CHECKOUT "co -l %s"

/* handy definitions */

#define Null(t) ((t)0)
#define Nullch Null(char *)
#define Nullfp Null(FILE *)

#define Ctl(ch) (ch & 037)

#define strNE(s1,s2) (strcmp(s1,s2))
#define strEQ(s1,s2) (!strcmp(s1,s2))
#define strnNE(s1,s2,l) (strncmp(s1,s2,l))
#define strnEQ(s1,s2,l) (!strncmp(s1,s2,l))

/* typedefs */

typedef char bool;
typedef long LINENUM;			/* must be signed */
typedef unsigned MEM;			/* what to feed malloc */

/* globals */

int Argc;				/* guess */
char **Argv;

struct stat filestat;			/* file statistics area */

char serrbuf[BUFSIZ];			/* buffer for stderr */
char buf[MAXLINELEN];			/* general purpose buffer */
FILE *pfp = Nullfp;			/* patch file pointer */
FILE *ofp = Nullfp;			/* output file pointer */
FILE *rejfp = Nullfp;			/* reject file pointer */

LINENUM input_lines = 0;		/* how long is input file in lines */
LINENUM last_frozen_line = 0;		/* how many input lines have been */
					/* irretractibly output */

#define MAXFILEC 2
int filec = 0;				/* how many file arguments? */
char *filearg[MAXFILEC];

char *outname = Nullch;
char rejname[128];

char *origext = Nullch;

char TMPOUTNAME[] = "/tmp/patchoXXXXXX";
char TMPINNAME[] = "/tmp/patchiXXXXXX";	/* you might want /usr/tmp here */
char TMPREJNAME[] = "/tmp/patchrXXXXXX";
char TMPPATNAME[] = "/tmp/patchpXXXXXX";

LINENUM last_offset = 0;
#ifdef DEBUGGING
int debug = 0;
#endif
bool verbose = TRUE;
bool reverse = FALSE;
I 6
bool noreverse = FALSE;
bool skip_this_patch = FALSE;
E 6
bool usepath = FALSE;
bool canonicalize = FALSE;

#define CONTEXT_DIFF 1
#define NORMAL_DIFF 2
#define ED_DIFF 3
I 2
#define NEW_CONTEXT_DIFF 4
E 2
int diff_type = 0;

int do_defines = 0;			/* patch using ifdef, ifndef, etc. */
char if_defined[128];			/* #ifdef xyzzy */
char not_defined[128];			/* #ifndef xyzzy */
char else_defined[] = "#else\n";	/* #else */
char end_defined[128];			/* #endif xyzzy */

char *revision = Nullch;		/* prerequisite revision, if any */

E 9
/* procedures */

I 9
void reinitialize_almost_everything();
void get_some_switches();
E 9
LINENUM locate_hunk();
I 9
void abort_hunk();
void apply_hunk();
void init_output();
void init_reject();
void copy_till();
void spew_output();
void dump_line();
E 9
bool patch_match();
bool similar();
D 9
char *malloc();
char *savestr();
char *strcpy();
char *strcat();
char *sprintf();		/* usually */
int my_exit();
bool rev_in_string();
char *fetchname();
long atol();
long lseek();
char *mktemp();
E 9
I 9
void re_input();
void my_exit();
E 9

D 9
/* patch type */
E 9
I 9
/* Apply a set of diffs as appropriate. */
E 9

D 9
bool there_is_another_patch();
bool another_hunk();
char *pfetch();
int pch_line_len();
LINENUM pch_first();
LINENUM pch_ptrn_lines();
LINENUM pch_newfirst();
LINENUM pch_repl_lines();
LINENUM pch_end();
LINENUM pch_context();
LINENUM pch_hunk_beg();
char pch_char();
char *pfetch();
char *pgets();

/* input file type */

char *ifetch();

/* apply a context patch to a named file */

E 9
main(argc,argv)
int argc;
char **argv;
{
    LINENUM where;
I 9
    LINENUM newwhere;
    LINENUM fuzz;
    LINENUM mymaxfuzz;
E 9
    int hunk = 0;
    int failed = 0;
    int i;

D 9
    setbuf(stderr,serrbuf);
E 9
I 9
    setbuf(stderr, serrbuf);
E 9
    for (i = 0; i<MAXFILEC; i++)
	filearg[i] = Nullch;
    Mktemp(TMPOUTNAME);
    Mktemp(TMPINNAME);
    Mktemp(TMPREJNAME);
    Mktemp(TMPPATNAME);

    /* parse switches */
    Argc = argc;
    Argv = argv;
    get_some_switches();
    
    /* make sure we clean up /tmp in case of disaster */
    set_signals();

    for (
	open_patch_file(filearg[1]);
	there_is_another_patch();
	reinitialize_almost_everything()
    ) {					/* for each patch in patch file */

	if (outname == Nullch)
	    outname = savestr(filearg[0]);
    
	/* initialize the patched file */
D 9
	init_output(TMPOUTNAME);
E 9
I 9
	if (!skip_rest_of_patch)
	    init_output(TMPOUTNAME);
E 9
    
	/* for ed script just up and do it and exit */
	if (diff_type == ED_DIFF) {
	    do_ed_script();
	    continue;
	}
    
	/* initialize reject file */
	init_reject(TMPREJNAME);
    
	/* find out where all the lines are */
D 9
	scan_input(filearg[0]);
E 9
I 9
	if (!skip_rest_of_patch)
	    scan_input(filearg[0]);
E 9
    
	/* from here on, open no standard i/o files, because malloc */
D 9
	/* might misfire */
E 9
I 9
	/* might misfire and we can't catch it easily */
E 9
    
	/* apply each hunk of patch */
	hunk = 0;
	failed = 0;
I 9
	out_of_mem = FALSE;
E 9
	while (another_hunk()) {
	    hunk++;
D 9
	    where = locate_hunk();
	    if (hunk == 1 && where == Null(LINENUM)) {
					/* dwim for reversed patch? */
		pch_swap();
		reverse = !reverse;
		where = locate_hunk();	/* try again */
		if (where == Null(LINENUM)) {
		    pch_swap();		/* no, put it back to normal */
		    reverse = !reverse;
I 6
		} else if (noreverse) {
		    pch_swap();		/* put it back to normal */
		    reverse = !reverse;
		    say("Ignoring previously applied (or reversed) patch.\n");
		    skip_this_patch = TRUE;
E 9
I 9
	    fuzz = Nulline;
	    mymaxfuzz = pch_context();
	    if (maxfuzz < mymaxfuzz)
		mymaxfuzz = maxfuzz;
	    if (!skip_rest_of_patch) {
		do {
		    where = locate_hunk(fuzz);
		    if (hunk == 1 && where == Nulline && !force) {
						/* dwim for reversed patch? */
			if (!pch_swap()) {
			    if (fuzz == Nulline)
				say1("\
Not enough memory to try swapped hunk!  Assuming unswapped.\n");
			    continue;
			}
			reverse = !reverse;
			where = locate_hunk(fuzz);  /* try again */
			if (where == Nulline) {	    /* didn't find it swapped */
			    if (!pch_swap())         /* put it back to normal */
				fatal1("Lost hunk on alloc error!\n");
			    reverse = !reverse;
			}
			else if (noreverse) {
			    if (!pch_swap())         /* put it back to normal */
				fatal1("Lost hunk on alloc error!\n");
			    reverse = !reverse;
			    say1("\
Ignoring previously applied (or reversed) patch.\n");
			    skip_rest_of_patch = TRUE;
			}
			else {
			    ask3("\
%seversed (or previously applied) patch detected!  %s -R? [y] ",
				reverse ? "R" : "Unr",
				reverse ? "Assume" : "Ignore");
			    if (*buf == 'n') {
				ask1("Apply anyway? [n] ");
				if (*buf != 'y')
				    skip_rest_of_patch = TRUE;
				where = Nulline;
				reverse = !reverse;
				if (!pch_swap())  /* put it back to normal */
				    fatal1("Lost hunk on alloc error!\n");
			    }
			}
		    }
		} while (!skip_rest_of_patch && where == Nulline &&
		    ++fuzz <= mymaxfuzz);

		if (skip_rest_of_patch) {		/* just got decided */
		    Fclose(ofp);
		    ofp = Nullfp;
E 9
E 6
		}
D 9
		else {
		    say("%seversed (or previously applied) patch detected!  %s -R.\n",
			reverse ? "R" : "Unr",
			reverse ? "Assuming" : "Ignoring");
		}
E 9
	    }
D 6
	    if (where == Null(LINENUM)) {
E 6
I 6
D 9
	    if (where == Null(LINENUM) || skip_this_patch) {
E 9
I 9

	    newwhere = pch_newfirst() + last_offset;
	    if (skip_rest_of_patch) {
E 9
E 6
		abort_hunk();
		failed++;
		if (verbose)
D 9
		    say("Hunk #%d failed.\n",hunk);
E 9
I 9
		    say3("Hunk #%d ignored at %ld.\n", hunk, newwhere);
E 9
	    }
I 9
	    else if (where == Nulline) {
		abort_hunk();
		failed++;
		if (verbose)
		    say3("Hunk #%d failed at %ld.\n", hunk, newwhere);
	    }
E 9
	    else {
		apply_hunk(where);
D 9
		if (verbose)
E 9
I 9
		if (verbose) {
		    say3("Hunk #%d succeeded at %ld", hunk, newwhere);
		    if (fuzz)
			say2(" with fuzz %ld", fuzz);
E 9
		    if (last_offset)
D 9
			say("Hunk #%d succeeded (offset %d line%s).\n",
			  hunk,last_offset,last_offset==1?"":"s");
		    else
			say("Hunk #%d succeeded.\n", hunk);
E 9
I 9
			say3(" (offset %ld line%s)",
			    last_offset, last_offset==1L?"":"s");
		    say1(".\n");
		}
E 9
	    }
	}
I 9

	if (out_of_mem && using_plan_a) {
	    Argc = Argc_last;
	    Argv = Argv_last;
	    say1("\n\nRan out of memory using Plan A--trying again...\n\n");
	    continue;
	}
E 9
    
	assert(hunk);
    
	/* finish spewing out the new file */
D 9
	spew_output();
E 9
I 9
	if (!skip_rest_of_patch)
	    spew_output();
E 9
	
	/* and put the output where desired */
	ignore_signals();
D 9
	move_file(TMPOUTNAME,outname);
E 9
I 9
	if (!skip_rest_of_patch) {
	    if (move_file(TMPOUTNAME, outname) < 0) {
		toutkeep = TRUE;
		chmod(TMPOUTNAME, filemode);
	    }
	    else
		chmod(outname, filemode);
	}
E 9
	Fclose(rejfp);
	rejfp = Nullfp;
	if (failed) {
	    if (!*rejname) {
		Strcpy(rejname, outname);
		Strcat(rejname, ".rej");
	    }
D 9
	    say("%d out of %d hunks failed--saving rejects to %s\n",
		failed, hunk, rejname);
	    move_file(TMPREJNAME,rejname);
E 9
I 9
	    if (skip_rest_of_patch) {
		say4("%d out of %d hunks ignored--saving rejects to %s\n",
		    failed, hunk, rejname);
	    }
	    else {
		say4("%d out of %d hunks failed--saving rejects to %s\n",
		    failed, hunk, rejname);
	    }
	    if (move_file(TMPREJNAME, rejname) < 0)
		trejkeep = TRUE;
E 9
	}
	set_signals();
    }
    my_exit(0);
}

I 9
/* Prepare to find the next patch to do in the patch file. */

void
E 9
reinitialize_almost_everything()
{
    re_patch();
    re_input();

    input_lines = 0;
    last_frozen_line = 0;

    filec = 0;
D 9
    if (filearg[0] != Nullch) {
E 9
I 9
    if (filearg[0] != Nullch && !out_of_mem) {
E 9
	free(filearg[0]);
	filearg[0] = Nullch;
    }

    if (outname != Nullch) {
	free(outname);
	outname = Nullch;
    }

    last_offset = 0;

    diff_type = 0;

    if (revision != Nullch) {
	free(revision);
	revision = Nullch;
    }

    reverse = FALSE;
I 6
D 9
    skip_this_patch = FALSE;
E 9
I 9
    skip_rest_of_patch = FALSE;
E 9
E 6

    get_some_switches();

    if (filec >= 2)
D 9
	fatal("You may not change to a different patch file.\n");
E 9
I 9
	fatal1("You may not change to a different patch file.\n");
E 9
}

I 9
/* Process switches and filenames up to next '+' or end of list. */

void
E 9
get_some_switches()
{
D 9
    register char *s;
E 9
I 9
    Reg1 char *s;
E 9

    rejname[0] = '\0';
I 9
    Argc_last = Argc;
    Argv_last = Argv;
E 9
    if (!Argc)
	return;
    for (Argc--,Argv++; Argc; Argc--,Argv++) {
	s = Argv[0];
D 9
	if (strEQ(s,"+")) {
E 9
I 9
	if (strEQ(s, "+")) {
E 9
	    return;			/* + will be skipped by for loop */
	}
	if (*s != '-' || !s[1]) {
	    if (filec == MAXFILEC)
D 9
		fatal("Too many file arguments.\n");
E 9
I 9
		fatal1("Too many file arguments.\n");
E 9
	    filearg[filec++] = savestr(s);
	}
	else {
	    switch (*++s) {
	    case 'b':
		origext = savestr(Argv[1]);
		Argc--,Argv++;
		break;
	    case 'c':
		diff_type = CONTEXT_DIFF;
		break;
	    case 'd':
D 9
		if (chdir(Argv[1]) < 0)
		    fatal("Can't cd to %s.\n",Argv[1]);
		Argc--,Argv++;
E 9
I 9
		if (!*++s) {
		    Argc--,Argv++;
		    s = Argv[0];
		}
		if (chdir(s) < 0)
		    fatal2("Can't cd to %s.\n", s);
E 9
		break;
	    case 'D':
D 9
	    	do_defines++;
		Sprintf(if_defined, "#ifdef %s\n", Argv[1]);
		Sprintf(not_defined, "#ifndef %s\n", Argv[1]);
		Sprintf(end_defined, "#endif %s\n", Argv[1]);
		Argc--,Argv++;
E 9
I 9
	    	do_defines = TRUE;
		if (!*++s) {
		    Argc--,Argv++;
		    s = Argv[0];
		}
		Sprintf(if_defined, "#ifdef %s\n", s);
		Sprintf(not_defined, "#ifndef %s\n", s);
		Sprintf(end_defined, "#endif /* %s */\n", s);
E 9
		break;
	    case 'e':
		diff_type = ED_DIFF;
		break;
I 9
	    case 'f':
		force = TRUE;
		break;
	    case 'F':
		if (*++s == '=')
		    s++;
		maxfuzz = atoi(s);
		break;
E 9
	    case 'l':
		canonicalize = TRUE;
		break;
	    case 'n':
		diff_type = NORMAL_DIFF;
		break;
I 9
	    case 'N':
		noreverse = TRUE;
		break;
E 9
	    case 'o':
		outname = savestr(Argv[1]);
		Argc--,Argv++;
		break;
	    case 'p':
D 9
		usepath = TRUE;	/* do not strip path names */
E 9
I 9
		if (*++s == '=')
		    s++;
		strippath = atoi(s);
E 9
		break;
	    case 'r':
D 9
		Strcpy(rejname,Argv[1]);
E 9
I 9
		Strcpy(rejname, Argv[1]);
E 9
		Argc--,Argv++;
		break;
	    case 'R':
		reverse = TRUE;
		break;
I 6
D 9
	    case 'N':
		noreverse = TRUE;
		break;
E 9
E 6
	    case 's':
		verbose = FALSE;
		break;
I 9
	    case 'S':
		skip_rest_of_patch = TRUE;
		break;
	    case 'v':
		version();
		break;
E 9
#ifdef DEBUGGING
	    case 'x':
		debug = atoi(s+1);
		break;
#endif
	    default:
D 9
		fatal("Unrecognized switch: %s\n",Argv[0]);
E 9
I 9
		fatal2("Unrecognized switch: %s\n", Argv[0]);
E 9
	    }
	}
    }
}

I 9
/* Attempt to find the right place to apply this hunk of patch. */

E 9
LINENUM
D 9
locate_hunk()
E 9
I 9
locate_hunk(fuzz)
LINENUM fuzz;
E 9
{
D 9
    register LINENUM first_guess = pch_first() + last_offset;
    register LINENUM offset;
E 9
I 9
    Reg1 LINENUM first_guess = pch_first() + last_offset;
    Reg2 LINENUM offset;
E 9
    LINENUM pat_lines = pch_ptrn_lines();
D 9
    register LINENUM max_pos_offset = input_lines - first_guess
E 9
I 9
    Reg3 LINENUM max_pos_offset = input_lines - first_guess
E 9
				- pat_lines + 1; 
D 9
    register LINENUM max_neg_offset = first_guess - last_frozen_line - 1
				- pch_context();
E 9
I 9
    Reg4 LINENUM max_neg_offset = first_guess - last_frozen_line - 1
				+ pch_context();
E 9

    if (!pat_lines)			/* null range matches always */
	return first_guess;
    if (max_neg_offset >= first_guess)	/* do not try lines < 0 */
	max_neg_offset = first_guess - 1;
D 9
    if (first_guess <= input_lines && patch_match(first_guess,(LINENUM)0))
E 9
I 9
    if (first_guess <= input_lines && patch_match(first_guess, Nulline, fuzz))
E 9
	return first_guess;
    for (offset = 1; ; offset++) {
D 9
	bool check_after = (offset <= max_pos_offset);
	bool check_before = (offset <= max_pos_offset);
E 9
I 9
	Reg5 bool check_after = (offset <= max_pos_offset);
	Reg6 bool check_before = (offset <= max_neg_offset);
E 9

D 9
	if (check_after && patch_match(first_guess,offset)) {
E 9
I 9
	if (check_after && patch_match(first_guess, offset, fuzz)) {
E 9
#ifdef DEBUGGING
	    if (debug & 1)
D 9
		printf("Offset changing from %d to %d\n",last_offset,offset);
E 9
I 9
		say3("Offset changing from %ld to %ld\n", last_offset, offset);
E 9
#endif
	    last_offset = offset;
	    return first_guess+offset;
	}
D 9
	else if (check_before && patch_match(first_guess,-offset)) {
E 9
I 9
	else if (check_before && patch_match(first_guess, -offset, fuzz)) {
E 9
#ifdef DEBUGGING
	    if (debug & 1)
D 9
		printf("Offset changing from %d to %d\n",last_offset,-offset);
E 9
I 9
		say3("Offset changing from %ld to %ld\n", last_offset, -offset);
E 9
#endif
	    last_offset = -offset;
	    return first_guess-offset;
	}
	else if (!check_before && !check_after)
D 9
	    return Null(LINENUM);
E 9
I 9
	    return Nulline;
E 9
    }
}

D 9
/* we did not find the pattern, dump out the hunk so they can handle it */
E 9
I 9
/* We did not find the pattern, dump out the hunk so they can handle it. */
E 9

I 9
void
E 9
abort_hunk()
{
D 9
    register LINENUM i;
    register LINENUM pat_end = pch_end();
E 9
I 9
    Reg1 LINENUM i;
    Reg2 LINENUM pat_end = pch_end();
E 9
    /* add in last_offset to guess the same as the previous successful hunk */
D 9
    int oldfirst = pch_first() + last_offset;
    int newfirst = pch_newfirst() + last_offset;
    int oldlast = oldfirst + pch_ptrn_lines() - 1;
    int newlast = newfirst + pch_repl_lines() - 1;
E 9
I 9
    LINENUM oldfirst = pch_first() + last_offset;
    LINENUM newfirst = pch_newfirst() + last_offset;
    LINENUM oldlast = oldfirst + pch_ptrn_lines() - 1;
    LINENUM newlast = newfirst + pch_repl_lines() - 1;
    char *stars = (diff_type == NEW_CONTEXT_DIFF ? " ****" : "");
    char *minuses = (diff_type == NEW_CONTEXT_DIFF ? " ----" : " -----");
E 9

D 9
    fprintf(rejfp,"***************\n");
E 9
I 9
    fprintf(rejfp, "***************\n");
E 9
    for (i=0; i<=pat_end; i++) {
	switch (pch_char(i)) {
	case '*':
D 7
	    fprintf(rejfp,"*** %d,%d\n", oldfirst, oldlast);
E 7
I 7
D 9
	    if (diff_type == NEW_CONTEXT_DIFF)
		fprintf(rejfp,"*** %d,%d ****\n", oldfirst, oldlast);
E 9
I 9
	    if (oldlast < oldfirst)
		fprintf(rejfp, "*** 0%s\n", stars);
	    else if (oldlast == oldfirst)
		fprintf(rejfp, "*** %ld%s\n", oldfirst, stars);
E 9
	    else
D 9
		fprintf(rejfp,"*** %d,%d\n", oldfirst, oldlast);
E 9
I 9
		fprintf(rejfp, "*** %ld,%ld%s\n", oldfirst, oldlast, stars);
E 9
E 7
	    break;
	case '=':
D 9
	    fprintf(rejfp,"--- %d,%d -----\n", newfirst, newlast);
E 9
I 9
	    if (newlast < newfirst)
		fprintf(rejfp, "--- 0%s\n", minuses);
	    else if (newlast == newfirst)
		fprintf(rejfp, "--- %ld%s\n", newfirst, minuses);
	    else
		fprintf(rejfp, "--- %ld,%ld%s\n", newfirst, newlast, minuses);
E 9
	    break;
	case '\n':
D 9
	    fprintf(rejfp,"%s", pfetch(i));
E 9
I 9
	    fprintf(rejfp, "%s", pfetch(i));
E 9
	    break;
	case ' ': case '-': case '+': case '!':
D 9
	    fprintf(rejfp,"%c %s", pch_char(i), pfetch(i));
E 9
I 9
	    fprintf(rejfp, "%c %s", pch_char(i), pfetch(i));
E 9
	    break;
	default:
D 9
	    say("Fatal internal error in abort_hunk().\n"); 
E 9
I 9
	    say1("Fatal internal error in abort_hunk().\n"); 
E 9
	    abort();
	}
    }
}

D 9
/* we found where to apply it (we hope), so do it */
E 9
I 9
/* We found where to apply it (we hope), so do it. */
E 9

I 9
void
E 9
apply_hunk(where)
LINENUM where;
{
D 9
    register LINENUM old = 1;
    register LINENUM lastline = pch_ptrn_lines();
    register LINENUM new = lastline+1;
    register int def_state = 0;	/* -1 = ifndef, 1 = ifdef */
E 9
I 9
    Reg1 LINENUM old = 1;
    Reg2 LINENUM lastline = pch_ptrn_lines();
    Reg3 LINENUM new = lastline+1;
#define OUTSIDE 0
#define IN_IFNDEF 1
#define IN_IFDEF 2
#define IN_ELSE 3
    Reg4 int def_state = OUTSIDE;
    Reg5 bool R_do_defines = do_defines;
    Reg6 LINENUM pat_end = pch_end();
E 9

    where--;
    while (pch_char(new) == '=' || pch_char(new) == '\n')
	new++;
    
    while (old <= lastline) {
	if (pch_char(old) == '-') {
	    copy_till(where + old - 1);
D 9
	    if (do_defines) {
		if (def_state == 0) {
E 9
I 9
	    if (R_do_defines) {
		if (def_state == OUTSIDE) {
E 9
		    fputs(not_defined, ofp);
D 9
		    def_state = -1;
		} else
		if (def_state == 1) {
E 9
I 9
		    def_state = IN_IFNDEF;
		}
		else if (def_state == IN_IFDEF) {
E 9
		    fputs(else_defined, ofp);
D 9
		    def_state = 2;
E 9
I 9
		    def_state = IN_ELSE;
E 9
		}
		fputs(pfetch(old), ofp);
	    }
	    last_frozen_line++;
	    old++;
	}
I 9
	else if (new > pat_end)
	    break;
E 9
	else if (pch_char(new) == '+') {
	    copy_till(where + old - 1);
D 9
	    if (do_defines) {
		if (def_state == -1) {
E 9
I 9
	    if (R_do_defines) {
		if (def_state == IN_IFNDEF) {
E 9
		    fputs(else_defined, ofp);
D 9
		    def_state = 2;
		} else
		if (def_state == 0) {
E 9
I 9
		    def_state = IN_ELSE;
		}
		else if (def_state == OUTSIDE) {
E 9
		    fputs(if_defined, ofp);
D 9
		    def_state = 1;
E 9
I 9
		    def_state = IN_IFDEF;
E 9
		}
	    }
D 9
	    fputs(pfetch(new),ofp);
E 9
I 9
	    fputs(pfetch(new), ofp);
E 9
	    new++;
	}
	else {
	    if (pch_char(new) != pch_char(old)) {
D 9
		say("Out-of-sync patch, lines %d,%d\n",
		    pch_hunk_beg() + old - 1,
		    pch_hunk_beg() + new - 1);
E 9
I 9
		say3("Out-of-sync patch, lines %ld,%ld--mangled text or line numbers, maybe?\n",
		    pch_hunk_beg() + old,
		    pch_hunk_beg() + new);
E 9
#ifdef DEBUGGING
D 9
		printf("oldchar = '%c', newchar = '%c'\n",
E 9
I 9
		say3("oldchar = '%c', newchar = '%c'\n",
E 9
		    pch_char(old), pch_char(new));
#endif
		my_exit(1);
	    }
	    if (pch_char(new) == '!') {
		copy_till(where + old - 1);
D 9
		if (do_defines) {
		   fputs(not_defined,ofp);
		   def_state = -1;
E 9
I 9
		if (R_do_defines) {
		   fputs(not_defined, ofp);
		   def_state = IN_IFNDEF;
E 9
		}
		while (pch_char(old) == '!') {
D 9
		    if (do_defines) {
			fputs(pfetch(old),ofp);
E 9
I 9
		    if (R_do_defines) {
			fputs(pfetch(old), ofp);
E 9
		    }
		    last_frozen_line++;
		    old++;
		}
D 9
		if (do_defines) {
E 9
I 9
		if (R_do_defines) {
E 9
		    fputs(else_defined, ofp);
D 9
		    def_state = 2;
E 9
I 9
		    def_state = IN_ELSE;
E 9
		}
		while (pch_char(new) == '!') {
D 9
		    fputs(pfetch(new),ofp);
E 9
I 9
		    fputs(pfetch(new), ofp);
E 9
		    new++;
		}
D 9
		if (do_defines) {
E 9
I 9
		if (R_do_defines) {
E 9
		    fputs(end_defined, ofp);
D 9
		    def_state = 0;
E 9
I 9
		    def_state = OUTSIDE;
E 9
		}
	    }
	    else {
		assert(pch_char(new) == ' ');
		old++;
		new++;
	    }
	}
    }
D 9
    if (new <= pch_end() && pch_char(new) == '+') {
E 9
I 9
    if (new <= pat_end && pch_char(new) == '+') {
E 9
	copy_till(where + old - 1);
D 9
	if (do_defines) {
	    if (def_state == 0) {
E 9
I 9
	if (R_do_defines) {
	    if (def_state == OUTSIDE) {
E 9
	    	fputs(if_defined, ofp);
D 9
		def_state = 1;
	    } else
	    if (def_state == -1) {
E 9
I 9
		def_state = IN_IFDEF;
	    }
	    else if (def_state == IN_IFNDEF) {
E 9
		fputs(else_defined, ofp);
D 9
		def_state = 2;
E 9
I 9
		def_state = IN_ELSE;
E 9
	    }
	}
D 9
	while (new <= pch_end() && pch_char(new) == '+') {
	    fputs(pfetch(new),ofp);
E 9
I 9
	while (new <= pat_end && pch_char(new) == '+') {
	    fputs(pfetch(new), ofp);
E 9
	    new++;
	}
    }
D 9
    if (do_defines && def_state) {
E 9
I 9
    if (R_do_defines && def_state != OUTSIDE) {
E 9
	fputs(end_defined, ofp);
    }
}

D 9
do_ed_script()
{
    FILE *pipefp, *popen();
    bool this_line_is_command = FALSE;
    register char *t;
    long beginning_of_this_line;
E 9
I 9
/* Open the new file. */
E 9

D 9
    Unlink(TMPOUTNAME);
    copy_file(filearg[0],TMPOUTNAME);
    if (verbose)
	Sprintf(buf,"/bin/ed %s",TMPOUTNAME);
    else
	Sprintf(buf,"/bin/ed - %s",TMPOUTNAME);
    pipefp = popen(buf,"w");
    for (;;) {
	beginning_of_this_line = ftell(pfp);
	if (pgets(buf,sizeof buf,pfp) == Nullch) {
	    next_intuit_at(beginning_of_this_line);
	    break;
	}
	for (t=buf; isdigit(*t) || *t == ','; t++) ;
	this_line_is_command = (isdigit(*buf) &&
	  (*t == 'd' || *t == 'c' || *t == 'a') );
	if (this_line_is_command) {
	    fputs(buf,pipefp);
	    if (*t != 'd') {
		while (pgets(buf,sizeof buf,pfp) != Nullch) {
		    fputs(buf,pipefp);
		    if (strEQ(buf,".\n"))
			break;
		}
	    }
	}
	else {
	    next_intuit_at(beginning_of_this_line);
	    break;
	}
    }
    fprintf(pipefp,"w\n");
    fprintf(pipefp,"q\n");
    Fflush(pipefp);
    Pclose(pipefp);
    ignore_signals();
    move_file(TMPOUTNAME,outname);
    set_signals();
}

E 9
I 9
void
E 9
init_output(name)
char *name;
{
D 9
    ofp = fopen(name,"w");
E 9
I 9
    ofp = fopen(name, "w");
E 9
    if (ofp == Nullfp)
D 9
	fatal("patch: can't create %s.\n",name);
E 9
I 9
	fatal2("patch: can't create %s.\n", name);
E 9
}

I 9
/* Open a file to put hunks we can't locate. */

void
E 9
init_reject(name)
char *name;
{
D 9
    rejfp = fopen(name,"w");
E 9
I 9
    rejfp = fopen(name, "w");
E 9
    if (rejfp == Nullfp)
D 9
	fatal("patch: can't create %s.\n",name);
E 9
I 9
	fatal2("patch: can't create %s.\n", name);
E 9
}

D 9
move_file(from,to)
char *from, *to;
{
    char bakname[512];
    register char *s;
    int fromfd;
    register int i;
E 9
I 9
/* Copy input file to output, up to wherever hunk is to be applied. */
E 9

D 9
    /* to stdout? */

    if (strEQ(to,"-")) {
#ifdef DEBUGGING
	if (debug & 4)
	    say("Moving %s to stdout.\n",from);
#endif
	fromfd = open(from,0);
	if (fromfd < 0)
	    fatal("patch: internal error, can't reopen %s\n",from);
	while ((i=read(fromfd,buf,sizeof buf)) > 0)
	    if (write(1,buf,i) != 1)
		fatal("patch: write failed\n");
	Close(fromfd);
	return;
    }

    Strcpy(bakname,to);
    Strcat(bakname,origext?origext:ORIGEXT);
    if (stat(to,&filestat) >= 0) {	/* output file exists */
	dev_t to_device = filestat.st_dev;
	ino_t to_inode  = filestat.st_ino;
	char *simplename = bakname;
	
	for (s=bakname; *s; s++) {
	    if (*s == '/')
		simplename = s+1;
	}
	/* find a backup name that is not the same file */
	while (stat(bakname,&filestat) >= 0 &&
		to_device == filestat.st_dev && to_inode == filestat.st_ino) {
	    for (s=simplename; *s && !islower(*s); s++) ;
	    if (*s)
		*s = toupper(*s);
	    else
		Strcpy(simplename, simplename+1);
	}
	while (unlink(bakname) >= 0) ;	/* while() is for benefit of Eunice */
#ifdef DEBUGGING
	if (debug & 4)
	    say("Moving %s to %s.\n",to,bakname);
#endif
	if (link(to,bakname) < 0) {
	    say("patch: can't backup %s, output is in %s\n",
		to,from);
	    return;
	}
	while (unlink(to) >= 0) ;
    }
#ifdef DEBUGGING
    if (debug & 4)
	say("Moving %s to %s.\n",from,to);
#endif
    if (link(from,to) < 0) {		/* different file system? */
	int tofd;
	
	tofd = creat(to,0666);
	if (tofd < 0) {
	    say("patch: can't create %s, output is in %s.\n",
	      to, from);
	    return;
	}
	fromfd = open(from,0);
	if (fromfd < 0)
	    fatal("patch: internal error, can't reopen %s\n",from);
	while ((i=read(fromfd,buf,sizeof buf)) > 0)
	    if (write(tofd,buf,i) != i)
		fatal("patch: write failed\n");
	Close(fromfd);
	Close(tofd);
    }
    Unlink(from);
}

copy_file(from,to)
char *from, *to;
{
    int tofd;
    int fromfd;
    register int i;
    
    tofd = creat(to,0666);
    if (tofd < 0)
	fatal("patch: can't create %s.\n", to);
    fromfd = open(from,0);
    if (fromfd < 0)
	fatal("patch: internal error, can't reopen %s\n",from);
    while ((i=read(fromfd,buf,sizeof buf)) > 0)
	if (write(tofd,buf,i) != i)
	    fatal("patch: write (%s) failed\n", to);
    Close(fromfd);
    Close(tofd);
}

E 9
I 9
void
E 9
copy_till(lastline)
D 9
register LINENUM lastline;
E 9
I 9
Reg1 LINENUM lastline;
E 9
{
D 9
    if (last_frozen_line > lastline)
	say("patch: misordered hunks! output will be garbled.\n");
    while (last_frozen_line < lastline) {
	dump_line(++last_frozen_line);
E 9
I 9
    Reg2 LINENUM R_last_frozen_line = last_frozen_line;

    if (R_last_frozen_line > lastline)
	say1("patch: misordered hunks! output will be garbled.\n");
    while (R_last_frozen_line < lastline) {
	dump_line(++R_last_frozen_line);
E 9
    }
I 9
    last_frozen_line = R_last_frozen_line;
E 9
}

I 9
/* Finish copying the input file to the output file. */

void
E 9
spew_output()
{
D 9
    copy_till(input_lines);		/* dump remainder of file */
E 9
I 9
#ifdef DEBUGGING
    if (debug & 256)
	say3("il=%ld lfl=%ld\n",input_lines,last_frozen_line);
#endif
    if (input_lines)
	copy_till(input_lines);		/* dump remainder of file */
E 9
    Fclose(ofp);
    ofp = Nullfp;
}

I 9
/* Copy one line from input to output. */

void
E 9
dump_line(line)
LINENUM line;
{
D 9
    register char *s;
E 9
I 9
    Reg1 char *s;
    Reg2 char R_newline = '\n';
E 9

D 9
    for (s=ifetch(line,0); putc(*s,ofp) != '\n'; s++) ;
E 9
I 9
    /* Note: string is not null terminated. */
    for (s=ifetch(line, 0); putc(*s, ofp) != R_newline; s++) ;
E 9
}

D 9
/* does the patch pattern match at line base+offset? */
E 9
I 9
/* Does the patch pattern match at line base+offset? */
E 9

bool
D 9
patch_match(base,offset)
E 9
I 9
patch_match(base, offset, fuzz)
E 9
LINENUM base;
LINENUM offset;
I 9
LINENUM fuzz;
E 9
{
D 9
    register LINENUM pline;
    register LINENUM iline;
    register LINENUM pat_lines = pch_ptrn_lines();
E 9
I 9
    Reg1 LINENUM pline = 1 + fuzz;
    Reg2 LINENUM iline;
    Reg3 LINENUM pat_lines = pch_ptrn_lines() - fuzz;
E 9

D 9
    for (pline = 1, iline=base+offset; pline <= pat_lines; pline++,iline++) {
E 9
I 9
    for (iline=base+offset+fuzz; pline <= pat_lines; pline++,iline++) {
E 9
	if (canonicalize) {
D 9
	    if (!similar(ifetch(iline,(offset >= 0)),
E 9
I 9
	    if (!similar(ifetch(iline, (offset >= 0)),
E 9
			 pfetch(pline),
			 pch_line_len(pline) ))
		return FALSE;
	}
D 9
	else if (strnNE(ifetch(iline,(offset >= 0)),
E 9
I 9
	else if (strnNE(ifetch(iline, (offset >= 0)),
E 9
		   pfetch(pline),
		   pch_line_len(pline) ))
	    return FALSE;
    }
    return TRUE;
}

D 9
/* match two lines with canonicalized white space */
E 9
I 9
/* Do two lines match with canonicalized white space? */
E 9

bool
similar(a,b,len)
D 9
register char *a, *b;
register int len;
E 9
I 9
Reg1 char *a;
Reg2 char *b;
Reg3 int len;
E 9
{
    while (len) {
	if (isspace(*b)) {		/* whitespace (or \n) to match? */
	    if (!isspace(*a))		/* no corresponding whitespace? */
		return FALSE;
	    while (len && isspace(*b) && *b != '\n')
		b++,len--;		/* skip pattern whitespace */
	    while (isspace(*a) && *a != '\n')
		a++;			/* skip target whitespace */
	    if (*a == '\n' || *b == '\n')
		return (*a == *b);	/* should end in sync */
	}
	else if (*a++ != *b++)		/* match non-whitespace chars */
	    return FALSE;
	else
	    len--;			/* probably not necessary */
    }
    return TRUE;			/* actually, this is not reached */
					/* since there is always a \n */
}

D 9
/* input file with indexable lines abstract type */
E 9
I 9
/* Exit with cleanup. */
E 9

D 9
bool using_plan_a = TRUE;
static long i_size;			/* size of the input file */
static char *i_womp;			/* plan a buffer for entire file */
static char **i_ptr;			/* pointers to lines in i_womp */

static int tifd = -1;			/* plan b virtual string array */
static char *tibuf[2];			/* plan b buffers */
static LINENUM tiline[2] = {-1,-1};	/* 1st line in each buffer */
static LINENUM lines_per_buf;		/* how many lines per buffer */
static int tireclen;			/* length of records in tmp file */

re_input()
{
    if (using_plan_a) {
	i_size = 0;
	/*NOSTRICT*/
	if (i_ptr != Null(char**))
	    free((char *)i_ptr);
	if (i_womp != Nullch)
	    free(i_womp);
	i_womp = Nullch;
	i_ptr = Null(char **);
    }
    else {
	using_plan_a = TRUE;		/* maybe the next one is smaller */
	Close(tifd);
	tifd = -1;
	free(tibuf[0]);
	free(tibuf[1]);
	tibuf[0] = tibuf[1] = Nullch;
	tiline[0] = tiline[1] = -1;
	tireclen = 0;
    }
}

scan_input(filename)
char *filename;
{
    bool plan_a();

    if (!plan_a(filename))
	plan_b(filename);
}

/* try keeping everything in memory */

bool
plan_a(filename)
char *filename;
{
    int ifd;
    register char *s;
    register LINENUM iline;

    if (stat(filename,&filestat) < 0) {
	Sprintf(buf,"RCS/%s%s",filename,RCSSUFFIX);
	if (stat(buf,&filestat) >= 0 || stat(buf+4,&filestat) >= 0) {
	    Sprintf(buf,CHECKOUT,filename);
	    if (verbose)
		say("Can't find %s--attempting to check it out from RCS.\n",
		    filename);
	    if (system(buf) || stat(filename,&filestat))
		fatal("Can't check out %s.\n",filename);
	}
	else {
	    Sprintf(buf,"SCCS/%s%s",SCCSPREFIX,filename);
	    if (stat(buf,&filestat) >= 0 || stat(buf+5,&filestat) >= 0) {
		Sprintf(buf,GET,filename);
		if (verbose)
		    say("Can't find %s--attempting to get it from SCCS.\n",
			filename);
		if (system(buf) || stat(filename,&filestat))
		    fatal("Can't get %s.\n",filename);
	    }
	    else
		fatal("Can't find %s.\n",filename);
	}
    }
    if ((filestat.st_mode & S_IFMT) & ~S_IFREG)
	fatal("%s is not a normal file--can't patch.\n",filename);
    i_size = filestat.st_size;
    /*NOSTRICT*/
    i_womp = malloc((MEM)(i_size+2));
    if (i_womp == Nullch)
	return FALSE;
    if ((ifd = open(filename,0)) < 0)
	fatal("Can't open file %s\n",filename);
    /*NOSTRICT*/
    if (read(ifd,i_womp,(int)i_size) != i_size) {
	Close(ifd);
	free(i_womp);
	return FALSE;
    }
    Close(ifd);
    if (i_womp[i_size-1] != '\n')
	i_womp[i_size++] = '\n';
    i_womp[i_size] = '\0';

    /* count the lines in the buffer so we know how many pointers we need */

    iline = 0;
    for (s=i_womp; *s; s++) {
	if (*s == '\n')
	    iline++;
    }
    /*NOSTRICT*/
    i_ptr = (char **)malloc((MEM)((iline + 2) * sizeof(char *)));
    if (i_ptr == Null(char **)) {	/* shucks, it was a near thing */
	free((char *)i_womp);
	return FALSE;
    }
    
    /* now scan the buffer and build pointer array */

    iline = 1;
    i_ptr[iline] = i_womp;
    for (s=i_womp; *s; s++) {
	if (*s == '\n')
	    i_ptr[++iline] = s+1;	/* these are NOT null terminated */
    }
    input_lines = iline - 1;

    /* now check for revision, if any */

    if (revision != Nullch) { 
	if (!rev_in_string(i_womp)) {
	    ask("This file doesn't appear to be the %s version--patch anyway? [n] ",
		revision);
	    if (*buf != 'y')
		fatal("Aborted.\n");
	}
	else if (verbose)
	    say("Good.  This file appears to be the %s version.\n",
		revision);
    }
    return TRUE;			/* plan a will work */
}

/* keep (virtually) nothing in memory */

plan_b(filename)
char *filename;
{
    FILE *ifp;
    register int i = 0;
    register int maxlen = 1;
    bool found_revision = (revision == Nullch);

    using_plan_a = FALSE;
    if ((ifp = fopen(filename,"r")) == Nullfp)
	fatal("Can't open file %s\n",filename);
    if ((tifd = creat(TMPINNAME,0666)) < 0)
	fatal("Can't open file %s\n",TMPINNAME);
    while (fgets(buf,sizeof buf, ifp) != Nullch) {
	if (revision != Nullch && !found_revision && rev_in_string(buf))
	    found_revision = TRUE;
	if ((i = strlen(buf)) > maxlen)
	    maxlen = i;			/* find longest line */
    }
    if (revision != Nullch) {
	if (!found_revision) {
	    ask("This file doesn't appear to be the %s version--patch anyway? [n] ",
		revision);
	    if (*buf != 'y')
		fatal("Aborted.\n");
	}
	else if (verbose)
	    say("Good.  This file appears to be the %s version.\n",
		revision);
    }
    Fseek(ifp,0L,0);		/* rewind file */
    lines_per_buf = BUFFERSIZE / maxlen;
    tireclen = maxlen;
    tibuf[0] = malloc((MEM)(BUFFERSIZE + 1));
    tibuf[1] = malloc((MEM)(BUFFERSIZE + 1));
    if (tibuf[1] == Nullch)
	fatal("Can't seem to get enough memory.\n");
    for (i=1; ; i++) {
	if (! (i % lines_per_buf))	/* new block */
	    if (write(tifd,tibuf[0],BUFFERSIZE) < BUFFERSIZE)
		fatal("patch: can't write temp file.\n");
	if (fgets(tibuf[0] + maxlen * (i%lines_per_buf), maxlen + 1, ifp)
	  == Nullch) {
	    input_lines = i - 1;
	    if (i % lines_per_buf)
		if (write(tifd,tibuf[0],BUFFERSIZE) < BUFFERSIZE)
		    fatal("patch: can't write temp file.\n");
	    break;
	}
    }
    Fclose(ifp);
    Close(tifd);
    if ((tifd = open(TMPINNAME,0)) < 0) {
	fatal("Can't reopen file %s\n",TMPINNAME);
    }
}

/* fetch a line from the input file, \n terminated, not necessarily \0 */
char *
ifetch(line,whichbuf)
register LINENUM line;
int whichbuf;				/* ignored when file in memory */
{
    if (line < 1 || line > input_lines)
	return "";
    if (using_plan_a)
	return i_ptr[line];
    else {
	LINENUM offline = line % lines_per_buf;
	LINENUM baseline = line - offline;

	if (tiline[0] == baseline)
	    whichbuf = 0;
	else if (tiline[1] == baseline)
	    whichbuf = 1;
	else {
	    tiline[whichbuf] = baseline;
	    Lseek(tifd,(long)baseline / lines_per_buf * BUFFERSIZE,0);
	    if (read(tifd,tibuf[whichbuf],BUFFERSIZE) < 0)
		fatal("Error reading tmp file %s.\n",TMPINNAME);
	}
	return tibuf[whichbuf] + (tireclen*offline);
    }
}

/* patch abstract type */

static long p_filesize;			/* size of the patch file */
static LINENUM p_first;			/* 1st line number */
static LINENUM p_newfirst;		/* 1st line number of replacement */
static LINENUM p_ptrn_lines;		/* # lines in pattern */
static LINENUM p_repl_lines;		/* # lines in replacement text */
static LINENUM p_end = -1;		/* last line in hunk */
static LINENUM p_max;			/* max allowed value of p_end */
static LINENUM p_context = 3;		/* # of context lines */
static LINENUM p_input_line = 0;	/* current line # from patch file */
static char *p_line[MAXHUNKSIZE];	/* the text of the hunk */
static char p_char[MAXHUNKSIZE];	/* +, -, and ! */
static int p_len[MAXHUNKSIZE];		/* length of each line */
static int p_indent;			/* indent to patch */
static long p_base;			/* where to intuit this time */
static long p_start;			/* where intuit found a patch */

re_patch()
{
    p_first = (LINENUM)0;
    p_newfirst = (LINENUM)0;
    p_ptrn_lines = (LINENUM)0;
    p_repl_lines = (LINENUM)0;
    p_end = (LINENUM)-1;
    p_max = (LINENUM)0;
    p_indent = 0;
}

open_patch_file(filename)
char *filename;
{
    if (filename == Nullch || !*filename || strEQ(filename,"-")) {
	pfp = fopen(TMPPATNAME,"w");
	if (pfp == Nullfp)
	    fatal("patch: can't create %s.\n",TMPPATNAME);
	while (fgets(buf,sizeof buf,stdin) != NULL)
	    fputs(buf,pfp);
	Fclose(pfp);
	filename = TMPPATNAME;
    }
    pfp = fopen(filename,"r");
    if (pfp == Nullfp)
	fatal("patch file %s not found\n",filename);
    Fstat(fileno(pfp), &filestat);
    p_filesize = filestat.st_size;
    next_intuit_at(0L);			/* start at the beginning */
}

bool
there_is_another_patch()
{
    bool no_input_file = (filearg[0] == Nullch);
    
    if (p_base != 0L && p_base >= p_filesize) {
	if (verbose)
	    say("done\n");
	return FALSE;
    }
    if (verbose)
	say("Hmm...");
    diff_type = intuit_diff_type();
    if (!diff_type) {
	if (p_base != 0L) {
	    if (verbose)
		say("  Ignoring the trailing garbage.\ndone\n");
	}
	else
	    say("  I can't seem to find a patch in there anywhere.\n");
	return FALSE;
    }
    if (verbose)
	say("  %sooks like %s to me...\n",
	    (p_base == 0L ? "L" : "The next patch l"),
	    diff_type == CONTEXT_DIFF ? "a context diff" :
I 2
	    diff_type == NEW_CONTEXT_DIFF ? "a new-style context diff" :
E 2
	    diff_type == NORMAL_DIFF ? "a normal diff" :
	    "an ed script" );
    if (p_indent && verbose)
	say("(Patch is indented %d space%s.)\n",p_indent,p_indent==1?"":"s");
    skip_to(p_start);
    if (no_input_file) {
D 6
	if (filearg[0] == Nullch) {
E 6
I 6
	while (filearg[0] == Nullch) {
E 6
	    ask("File to patch: ");
	    filearg[0] = fetchname(buf);
	}
D 6
	else if (verbose) {
E 6
I 6
	if (verbose) {
E 6
	    say("Patching file %s...\n",filearg[0]);
	}
    }
    return TRUE;
}

intuit_diff_type()
{
    long this_line = 0;
    long previous_line;
    long first_command_line = -1;
    bool last_line_was_command = FALSE;
    bool this_line_is_command = FALSE;
I 2
    bool last_line_was_stars = FALSE;
    bool this_line_is_stars = FALSE;
E 2
    register int indent;
    register char *s, *t;
    char *oldname = Nullch;
    char *newname = Nullch;
    bool no_filearg = (filearg[0] == Nullch);

    Fseek(pfp,p_base,0);
    for (;;) {
	previous_line = this_line;
	last_line_was_command = this_line_is_command;
I 2
	last_line_was_stars = this_line_is_stars;
E 2
	this_line = ftell(pfp);
	indent = 0;
	if (fgets(buf,sizeof buf,pfp) == Nullch) {
	    if (first_command_line >= 0L) {
					/* nothing but deletes!? */
		p_start = first_command_line;
		return ED_DIFF;
	    }
	    else {
		p_start = this_line;
		return 0;
	    }
	}
	for (s = buf; *s == ' ' || *s == '\t'; s++) {
	    if (*s == '\t')
		indent += 8 - (indent % 8);
	    else
		indent++;
	}
	for (t=s; isdigit(*t) || *t == ','; t++) ; 
	this_line_is_command = (isdigit(*s) &&
	  (*t == 'd' || *t == 'c' || *t == 'a') );
	if (first_command_line < 0L && this_line_is_command) { 
	    first_command_line = this_line;
	    p_indent = indent;		/* assume this for now */
	}
	if (strnEQ(s,"*** ",4))
	    oldname = fetchname(s+4);
	else if (strnEQ(s,"--- ",4)) {
	    newname = fetchname(s+4);
	    if (no_filearg) {
		if (oldname && newname) {
		    if (strlen(oldname) < strlen(newname))
			filearg[0] = oldname;
		    else
			filearg[0] = newname;
		}
		else if (oldname)
		    filearg[0] = oldname;
		else if (newname)
		    filearg[0] = newname;
	    }
	}
	else if (strnEQ(s,"Index:",6)) {
	    if (no_filearg) 
		filearg[0] = fetchname(s+6);
					/* this filearg might get limboed */
	}
	else if (strnEQ(s,"Prereq:",7)) {
	    for (t=s+7; isspace(*t); t++) ;
	    revision = savestr(t);
	    for (t=revision; *t && !isspace(*t); t++) ;
	    *t = '\0';
	    if (!*revision) {
		free(revision);
		revision = Nullch;
	    }
	}
	if ((!diff_type || diff_type == ED_DIFF) &&
	  first_command_line >= 0L &&
	  strEQ(s,".\n") ) {
	    p_indent = indent;
	    p_start = first_command_line;
	    return ED_DIFF;
	}
D 2
	if ((!diff_type || diff_type == CONTEXT_DIFF) &&
		 strnEQ(s,"********",8)) {
E 2
I 2
	this_line_is_stars = strnEQ(s,"********",8);
	if ((!diff_type || diff_type == CONTEXT_DIFF) && last_line_was_stars &&
		 strnEQ(s,"*** ",4)) {
	    /* if this is a new context diff the character just before */
	    /* the newline is a '*'. */
	    while (*s != '\n')
		s++;
E 2
	    p_indent = indent;
D 2
	    p_start = this_line;
	    return CONTEXT_DIFF;
E 2
I 2
	    p_start = previous_line;
	    return (*(s-1) == '*' ? NEW_CONTEXT_DIFF : CONTEXT_DIFF);
E 2
	}
	if ((!diff_type || diff_type == NORMAL_DIFF) && 
	  last_line_was_command &&
	  (strnEQ(s,"< ",2) || strnEQ(s,"> ",2)) ) {
	    p_start = previous_line;
	    p_indent = indent;
	    return NORMAL_DIFF;
	}
    }
}

char *
fetchname(at)
char *at;
{
    char *s = savestr(at);
    char *name;
    register char *t;
    char tmpbuf[200];

    for (t=s; isspace(*t); t++) ;
    name = t;
    for (; *t && !isspace(*t); t++)
	if (!usepath)
	    if (*t == '/')
		name = t+1;
    *t = '\0';
    name = savestr(name);
    Sprintf(tmpbuf,"RCS/%s",name);
    free(s);
    if (stat(name,&filestat) < 0) {
	Strcat(tmpbuf,RCSSUFFIX);
	if (stat(tmpbuf,&filestat) < 0 && stat(tmpbuf+4,&filestat) < 0) {
	    Sprintf(tmpbuf,"SCCS/%s%s",SCCSPREFIX,name);
	    if (stat(tmpbuf,&filestat) < 0 && stat(tmpbuf+5,&filestat) < 0) {
		free(name);
		name = Nullch;
	    }
	}
    }
    return name;
}

next_intuit_at(file_pos)
long file_pos;
{
    p_base = file_pos;
}

skip_to(file_pos)
long file_pos;
{
    char *ret;

    assert(p_base <= file_pos);
    if (verbose && p_base < file_pos) {
	Fseek(pfp,p_base,0);
	say("The text leading up to this was:\n--------------------------\n");
	while (ftell(pfp) < file_pos) {
	    ret = fgets(buf,sizeof buf,pfp);
	    assert(ret != Nullch);
	    say("|%s",buf);
	}
	say("--------------------------\n");
    }
    else
	Fseek(pfp,file_pos,0);
}

bool
another_hunk()
{
    register char *s;
    char *ret;
D 2
    int context = 0;
E 2
I 2
    register int context = 0;
E 2

    while (p_end >= 0) {
	free(p_line[p_end--]);
    }
    assert(p_end == -1);

    p_max = MAXHUNKSIZE;		/* gets reduced when --- found */
    if (diff_type == CONTEXT_DIFF) {
	long line_beginning = ftell(pfp);
	LINENUM repl_beginning = 0;

	ret = pgets(buf,sizeof buf, pfp);
	if (ret == Nullch || strnNE(buf,"********",8)) {
	    next_intuit_at(line_beginning);
	    return FALSE;
	}
	p_context = 100;
	while (p_end < p_max) {
	    ret = pgets(buf,sizeof buf, pfp);
	    if (ret == Nullch) {
		if (p_max - p_end < 4)
		    Strcpy(buf,"  \n");	/* assume blank lines got chopped */
		else
		    fatal("Unexpected end of file in patch.\n");
	    }
	    p_input_line++;
	    if (strnEQ(buf,"********",8))
		fatal("Unexpected end of hunk at line %d.\n",
		    p_input_line);
	    p_char[++p_end] = *buf;
	    switch (*buf) {
	    case '*':
		if (p_end != 0)
		    fatal("Unexpected *** at line %d: %s", p_input_line, buf);
		context = 0;
		p_line[p_end] = savestr(buf);
		for (s=buf; *s && !isdigit(*s); s++) ;
I 7
		if (!isdigit(*s))
		    fatal("Malformed patch at line %d: %s", p_input_line, buf);
E 7
		p_first = (LINENUM) atol(s);
		while (isdigit(*s)) s++;
		for (; *s && !isdigit(*s); s++) ;
D 7
		p_ptrn_lines = ((LINENUM)atol(s)) - p_first + 1;
E 7
I 7
		if (!isdigit(*s))
		    p_ptrn_lines = 1;
		else
		    p_ptrn_lines = ((LINENUM)atol(s)) - p_first + 1;
E 7
		break;
	    case '-':
		if (buf[1] == '-') {
		    if (p_end != p_ptrn_lines + 1 &&
			p_end != p_ptrn_lines + 2)
			fatal("Unexpected --- at line %d: %s",
			    p_input_line,buf);
		    repl_beginning = p_end;
		    context = 0;
		    p_line[p_end] = savestr(buf);
		    p_char[p_end] = '=';
		    for (s=buf; *s && !isdigit(*s); s++) ;
I 7
		    if (!isdigit(*s))
			fatal("Malformed patch at line %d: %s",
			      p_input_line, buf);
E 7
		    p_newfirst = (LINENUM) atol(s);
		    while (isdigit(*s)) s++;
		    for (; *s && !isdigit(*s); s++) ;
D 7
		    p_max = ((LINENUM)atol(s)) - p_newfirst + 1 + p_end;
E 7
I 7
		    if (!isdigit(*s))
			p_max = p_newfirst;
		    else
			p_max = ((LINENUM)atol(s));
		    p_max += 1 + p_end - p_newfirst;
		    if (p_max >= MAXHUNKSIZE)
			fatal("Hunk too large (%d lines) at line %d: %s",
			      p_max - p_end, p_input_line, buf);
E 7
		    break;
		}
		/* FALL THROUGH */
	    case '+': case '!':
		if (context > 0) {
		    if (context < p_context)
			p_context = context;
		    context = -100;
		}
		p_line[p_end] = savestr(buf+2);
		break;
	    case '\t': case '\n':	/* assume the 2 spaces got eaten */
		p_line[p_end] = savestr(buf);
		if (p_end != p_ptrn_lines + 1) {
		    context++;
		    p_char[p_end] = ' ';
		}
		break;
	    case ' ':
		context++;
		p_line[p_end] = savestr(buf+2);
		break;
	    default:
		fatal("Malformed patch at line %d: %s",p_input_line,buf);
	    }
D 5
	    p_len[p_end] = strlen(p_line[p_end]);
E 5
I 5
D 7
	    p_len[p_end] = 0;
	    if (p_line[p_end] != 0)
E 7
I 7
	    /* set up p_len for strncmp() so we don't have to */
	    /* assume null termination */
	    if (p_line[p_end])
E 7
		p_len[p_end] = strlen(p_line[p_end]);
E 5
D 7
					/* for strncmp() so we do not have */
					/* to assume null termination */
E 7
I 7
	    else
		p_len[p_end] = 0;
E 7
	}
	if (p_end >=0 && !p_ptrn_lines)
	    fatal("No --- found in patch at line %d\n", pch_hunk_beg());
I 2
	p_repl_lines = p_end - repl_beginning;
I 8
	p_char[p_end+1] = '^';	/* add a stopper for apply_hunk */
E 8
    }
    else if (diff_type == NEW_CONTEXT_DIFF) {
	long line_beginning = ftell(pfp);
	LINENUM repl_beginning = 0;
	LINENUM fillcnt = 0;
	LINENUM fillsrc;
	LINENUM filldst;

	ret = pgets(buf,sizeof buf, pfp);
	if (ret == Nullch || strnNE(buf,"********",8)) {
	    next_intuit_at(line_beginning);
	    return FALSE;
	}
	p_context = 0;
	while (p_end < p_max) {
I 3
D 7
	    line_beginning = ftell(pfp);
E 7
E 3
	    ret = pgets(buf,sizeof buf, pfp);
	    if (ret == Nullch) {
		if (p_max - p_end < 4)
		    Strcpy(buf,"  \n");	/* assume blank lines got chopped */
D 4
		else
E 4
I 4
D 7
		else if (p_end == repl_beginning) {
		    /* redundant 'new' context lines were omitted - set up */
		    /* to fill them in from the the old file's context */
		    fillsrc = 1;
		    filldst = p_end + 1;
		    fillcnt = p_max - repl_beginning;
		    p_end = p_max;
		    break;
		} else
E 7
I 7
		else
E 7
E 4
		    fatal("Unexpected end of file in patch.\n");
	    }
	    p_input_line++;
	    p_char[++p_end] = *buf;
	    switch (*buf) {
D 6
	    case '*':
		if (strnEQ(buf,"********",8)) {
E 6
I 6
	    case '*':	/* another hunk */
D 7
	    case 'd':	/* another hunk in a different file */
	    case 'B':	/* ditto */
	    case 'C':	/* ditto */
	    case 'F':	/* ditto */
	    case 'O':	/* ditto */
		if (strnEQ(buf,"********",8) ||
		    strnEQ(buf,"diff",4) ||
	    	    strnEQ(buf,"Binary files ",13) ||
	    	    strnEQ(buf,"Files ",6) ||
		    strnEQ(buf,"Common subdirectories: ",23) ||
		    strnEQ(buf,"Only in ",8)) {
E 6
		    if (p_end != repl_beginning + 1)
			fatal("Unexpected end of hunk at line %d.\n",
				p_input_line);
		    /* redundant 'new' context lines were omitted - set up */
		    /* to fill them in from the the old file's context */
		    fillsrc = 1;
		    filldst = p_end;
D 3
		    fillcnt = p_max - p_end;
E 3
I 3
		    fillcnt = p_max - repl_beginning;
E 3
		    p_end = p_max;
I 3
		    Fseek(pfp, line_beginning, 0); /* backup the diff input */
E 3
		    break;
		}
E 7
I 7
		if (strnEQ(buf,"********",8))
		    fatal("Unexpected end of hunk at line %d.\n",
			    p_input_line);

E 7
		if (p_end != 0)
		    fatal("Unexpected *** at line %d: %s", p_input_line, buf);
		context = 0;
		p_line[p_end] = savestr(buf);
		for (s=buf; *s && !isdigit(*s); s++) ;
I 7
		if (!isdigit(*s))
		    fatal("Malformed patch at line %d: %s", p_input_line, buf);
E 7
		p_first = (LINENUM) atol(s);
		while (isdigit(*s)) s++;
		for (; *s && !isdigit(*s); s++) ;
D 7
		p_ptrn_lines = ((LINENUM)atol(s)) - p_first + 1;
E 7
I 7
		if (!isdigit(*s))
		    p_ptrn_lines = 1;
		else
		    p_ptrn_lines = ((LINENUM)atol(s)) - p_first + 1;
E 7
		break;
	    case '-':
		if (buf[1] == '-') {
		    if (p_end != p_ptrn_lines + 1) {
			if (p_end == 1) {
			    /* `old' lines were omitted - set up to fill them */
			    /* in from 'new' context lines. */
			    p_end = p_ptrn_lines + 1;
			    fillsrc = p_end + 1;
			    filldst = 1;
			    fillcnt = p_ptrn_lines;
			} else
			    fatal("Unexpected --- at line %d: %s",
				p_input_line,buf);
		    }
		    repl_beginning = p_end;
		    p_line[p_end] = savestr(buf);
		    p_char[p_end] = '=';
		    for (s=buf; *s && !isdigit(*s); s++) ;
I 7
		    if (!isdigit(*s))
			fatal("Malformed patch at line %d: %s",
			      p_input_line, buf);
E 7
		    p_newfirst = (LINENUM) atol(s);
		    while (isdigit(*s)) s++;
		    for (; *s && !isdigit(*s); s++) ;
D 7
		    p_max = ((LINENUM)atol(s)) - p_newfirst + 1 + p_end;
E 7
I 7
		    if (!isdigit(*s))
			p_max = p_newfirst;
		    else
			p_max = ((LINENUM)atol(s));
		    p_max += 1 + p_end - p_newfirst;
		    if (p_max >= MAXHUNKSIZE)
			fatal("Hunk too large (%d lines) at line %d: %s",
			      p_max - p_end, p_input_line, buf);
		    if (p_max - p_end == context) {
			/* redundant 'new' context lines were omitted */
			/* set up to fill them in from the the old file's */
			/* context */
			fillsrc = 1;
			filldst = p_end + 1;
			fillcnt = p_max - repl_beginning;
			p_end = p_max;
		    }
E 7
		    break;
		}
		/* FALL THROUGH */
	    case '+': case '!':
		if (context > 0 && p_context == 0) {
		    p_context = context;
		}
		p_line[p_end] = savestr(buf+2);
		break;
	    case '\t': case '\n':	/* assume the 2 spaces got eaten */
		p_line[p_end] = savestr(buf);
D 8
		if (p_end != p_ptrn_lines + 1) {
		    context++;
		    p_char[p_end] = ' ';
		}
E 8
I 8
		context++;
		p_char[p_end] = ' ';
E 8
		break;
	    case ' ':
		context++;
		p_line[p_end] = savestr(buf+2);
		break;
	    default:
		fatal("Malformed patch at line %d: %s",p_input_line,buf);
	    }
D 5
	    p_len[p_end] = strlen(p_line[p_end]);
E 5
I 5
D 7
	    p_len[p_end] = 0;
	    if (p_line[p_end] != 0)
E 7
I 7
	    /* set up p_len for strncmp() so we don't have to */
	    /* assume null termination */
	    if (p_line[p_end])
E 7
		p_len[p_end] = strlen(p_line[p_end]);
E 5
D 7
					/* for strncmp() so we do not have */
					/* to assume null termination */
E 7
I 7
	    else
		p_len[p_end] = 0;
E 7
	}
	if (p_end >=0 && !p_ptrn_lines)
	    fatal("No --- found in patch at line %d\n", pch_hunk_beg());

	/* if there were omitted context lines, fill them in */
	if (fillcnt) {
	    while (fillcnt-- > 0) {
		while (p_char[fillsrc] != ' ')
		    fillsrc++;
D 7
		p_line[filldst] = p_line[fillsrc];
E 7
I 7
		if (p_line[fillsrc])
		    p_line[filldst] = savestr (p_line[fillsrc]);
		else
		    p_line[filldst] = p_line[fillsrc];
E 7
		p_char[filldst] = p_char[fillsrc];
		p_len[filldst] = p_len[fillsrc];
		fillsrc++; filldst++;
	    }
I 7
	    assert(filldst==p_end+1 || filldst==repl_beginning);
E 7
D 6
	    assert(fillsrc==p_end+1 || fillsrc==repl_beginning);
	    assert(filldst==p_end+1 || filldst==repl_beginning);
E 6
	}
E 2
	p_repl_lines = p_end - repl_beginning;
I 8
	p_char[p_end+1] = '^';	/* add a stopper for apply_hunk */
E 8
    }
    else {				/* normal diff--fake it up */
	char hunk_type;
	register int i;
	LINENUM min, max;
	long line_beginning = ftell(pfp);

	p_context = 0;
	ret = pgets(buf,sizeof buf, pfp);
	p_input_line++;
	if (ret == Nullch || !isdigit(*buf)) {
	    next_intuit_at(line_beginning);
	    return FALSE;
	}
	p_first = (LINENUM)atol(buf);
	for (s=buf; isdigit(*s); s++) ;
	if (*s == ',') {
	    p_ptrn_lines = (LINENUM)atol(++s) - p_first + 1;
	    while (isdigit(*s)) s++;
	}
	else
	    p_ptrn_lines = (*s != 'a');
	hunk_type = *s;
	if (hunk_type == 'a')
	    p_first++;			/* do append rather than insert */
	min = (LINENUM)atol(++s);
	for (; isdigit(*s); s++) ;
	if (*s == ',')
	    max = (LINENUM)atol(++s);
	else
	    max = min;
	if (hunk_type == 'd')
	    min++;
	p_end = p_ptrn_lines + 1 + max - min + 1;
	p_newfirst = min;
	p_repl_lines = max - min + 1;
	Sprintf(buf,"*** %d,%d\n", p_first, p_first + p_ptrn_lines - 1);
	p_line[0] = savestr(buf);
	p_char[0] = '*';
	for (i=1; i<=p_ptrn_lines; i++) {
	    ret = pgets(buf,sizeof buf, pfp);
	    p_input_line++;
	    if (ret == Nullch)
		fatal("Unexpected end of file in patch at line %d.\n",
		  p_input_line);
	    if (*buf != '<')
		fatal("< expected at line %d of patch.\n", p_input_line);
	    p_line[i] = savestr(buf+2);
D 5
	    p_len[i] = strlen(p_line[i]);
E 5
I 5
D 7
	    p_len[i] = 0;
	    if (p_line[i] != 0)
E 7
I 7
	    if (p_line[i])
E 7
		p_len[i] = strlen(p_line[i]);
I 7
	    else
		p_len[i] = 0;
E 7
E 5
	    p_char[i] = '-';
	}
	if (hunk_type == 'c') {
	    ret = pgets(buf,sizeof buf, pfp);
	    p_input_line++;
	    if (ret == Nullch)
		fatal("Unexpected end of file in patch at line %d.\n",
		    p_input_line);
	    if (*buf != '-')
		fatal("--- expected at line %d of patch.\n", p_input_line);
	}
	Sprintf(buf,"--- %d,%d\n",min,max);
	p_line[i] = savestr(buf);
	p_char[i] = '=';
	for (i++; i<=p_end; i++) {
	    ret = pgets(buf,sizeof buf, pfp);
	    p_input_line++;
	    if (ret == Nullch)
		fatal("Unexpected end of file in patch at line %d.\n",
		    p_input_line);
	    if (*buf != '>')
		fatal("> expected at line %d of patch.\n", p_input_line);
	    p_line[i] = savestr(buf+2);
D 5
	    p_len[i] = strlen(p_line[i]);
E 5
I 5
D 7
	    p_len[i] = 0;
	    if (p_line[i] != 0)
E 7
I 7
	    /* set up p_len for strncmp() so we don't have to */
	    /* assume null termination */
	    if (p_line[i])
E 7
		p_len[i] = strlen(p_line[i]);
I 7
	    else
		p_len[i] = 0;
E 7
E 5
	    p_char[i] = '+';
	}
    }
    if (reverse)			/* backwards patch? */
	pch_swap();
#ifdef DEBUGGING
    if (debug & 2) {
	int i;
	char special;

	for (i=0; i <= p_end; i++) {
	    if (i == p_ptrn_lines)
		special = '^';
	    else
		special = ' ';
	    printf("%3d %c %c %s",i,p_char[i],special,p_line[i]);
	}
    }
#endif
    return TRUE;
}

char *
pgets(bf,sz,fp)
char *bf;
int sz;
FILE *fp;
{
    char *ret = fgets(bf,sz,fp);
    register char *s;
    register int indent = 0;

    if (p_indent && ret != Nullch) {
	for (s=buf; indent < p_indent && (*s == ' ' || *s == '\t'); s++) {
	    if (*s == '\t')
		indent += 8 - (indent % 7);
	    else
		indent++;
	}
	if (buf != s)
	    Strcpy(buf,s);
    }
    return ret;
}

pch_swap()
{
    char *tp_line[MAXHUNKSIZE];		/* the text of the hunk */
    char tp_char[MAXHUNKSIZE];		/* +, -, and ! */
    int tp_len[MAXHUNKSIZE];		/* length of each line */
    register LINENUM i, n;
    bool blankline = FALSE;
    register char *s;

    i = p_first;
    p_first = p_newfirst;
    p_newfirst = i;
    
    /* make a scratch copy */

    for (i=0; i<=p_end; i++) {
	tp_line[i] = p_line[i];
	tp_char[i] = p_char[i];
	tp_len[i] = p_len[i];
    }

    /* now turn the new into the old */

    i = p_ptrn_lines + 1;
    if (tp_char[i] == '\n') {		/* account for possible blank line */
	blankline = TRUE;
	i++;
    }
    for (n=0; i <= p_end; i++,n++) {
	p_line[n] = tp_line[i];
	p_char[n] = tp_char[i];
	if (p_char[n] == '+')
	    p_char[n] = '-';
	p_len[n] = tp_len[i];
    }
    if (blankline) {
	i = p_ptrn_lines + 1;
	p_line[n] = tp_line[i];
	p_char[n] = tp_char[i];
	p_len[n] = tp_len[i];
	n++;
    }
    assert(p_char[0] == '=');
    p_char[0] = '*';
    for (s=p_line[0]; *s; s++)
	if (*s == '-')
	    *s = '*';

    /* now turn the old into the new */

    assert(tp_char[0] == '*');
    tp_char[0] = '=';
    for (s=tp_line[0]; *s; s++)
	if (*s == '*')
	    *s = '-';
    for (i=0; n <= p_end; i++,n++) {
	p_line[n] = tp_line[i];
	p_char[n] = tp_char[i];
	if (p_char[n] == '-')
	    p_char[n] = '+';
	p_len[n] = tp_len[i];
    }
    assert(i == p_ptrn_lines + 1);
    i = p_ptrn_lines;
    p_ptrn_lines = p_repl_lines;
    p_repl_lines = i;
}

LINENUM
pch_first()
{
    return p_first;
}

LINENUM
pch_ptrn_lines()
{
    return p_ptrn_lines;
}

LINENUM
pch_newfirst()
{
    return p_newfirst;
}

LINENUM
pch_repl_lines()
{
    return p_repl_lines;
}

LINENUM
pch_end()
{
    return p_end;
}

LINENUM
pch_context()
{
    return p_context;
}

pch_line_len(line)
LINENUM line;
{
    return p_len[line];
}

char
pch_char(line)
LINENUM line;
{
    return p_char[line];
}

char *
pfetch(line)
LINENUM line;
{
    return p_line[line];
}

LINENUM
pch_hunk_beg()
{
    return p_input_line - p_end - 1;
}

char *
savestr(s)
register char *s;
{
    register char  *rv,
                   *t;

    t = s;
    while (*t++);
    rv = malloc((MEM) (t - s));
    if (rv == NULL)
	fatal ("patch: out of memory (savestr)\n");
    t = rv;
    while (*t++ = *s++);
    return rv;
}

E 9
I 9
void
E 9
my_exit(status)
int status;
{
    Unlink(TMPINNAME);
D 9
    Unlink(TMPOUTNAME);
    Unlink(TMPREJNAME);
    Unlink(TMPPATNAME);
    exit(status);
}

#ifdef lint

/*VARARGS ARGSUSED*/
say(pat) char *pat; { ; }
/*VARARGS ARGSUSED*/
fatal(pat) char *pat; { ; }
/*VARARGS ARGSUSED*/
ask(pat) char *pat; { ; }

#else lint

say(pat,arg1,arg2,arg3)
char *pat;
int arg1,arg2,arg3;
{
    fprintf(stderr,pat,arg1,arg2,arg3);
    Fflush(stderr);
}

fatal(pat,arg1,arg2,arg3)
char *pat;
int arg1,arg2,arg3;
{
    say(pat,arg1,arg2,arg3);
    my_exit(1);
}

ask(pat,arg1,arg2,arg3)
char *pat;
int arg1,arg2,arg3;
{
    int ttyfd = open("/dev/tty",2);
    int r;

    say(pat,arg1,arg2,arg3);
    if (ttyfd >= 0) {
	r = read(ttyfd, buf, sizeof buf);
	Close(ttyfd);
E 9
I 9
    if (!toutkeep) {
	Unlink(TMPOUTNAME);
E 9
    }
D 9
    else
	r = read(2, buf, sizeof buf);
    if (r <= 0)
	buf[0] = 0;
}
#endif lint

bool
rev_in_string(string)
char *string;
{
    register char *s;
    register int patlen;

    if (revision == Nullch)
	return TRUE;
    patlen = strlen(revision);
    for (s = string; *s; s++) {
	if (isspace(*s) && strnEQ(s+1,revision,patlen) && 
		isspace(s[patlen+1] )) {
	    return TRUE;
	}
E 9
I 9
    if (!trejkeep) {
	Unlink(TMPREJNAME);
E 9
    }
D 9
    return FALSE;
}

set_signals()
{
    /*NOSTRICT*/
    if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
	Signal(SIGHUP, my_exit);
    /*NOSTRICT*/
    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
	Signal(SIGINT, my_exit);
}

ignore_signals()
{
    /*NOSTRICT*/
    Signal(SIGHUP, SIG_IGN);
    /*NOSTRICT*/
    Signal(SIGINT, SIG_IGN);
E 9
I 9
    Unlink(TMPPATNAME);
    exit(status);
E 9
}
E 1
