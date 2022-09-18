h36430
s 00001/00001/00327
d D 8.5 94/04/02 10:01:09 pendry 24 23
c add 1994 copyright
e
s 00011/00012/00317
d D 8.4 94/04/02 09:58:38 pendry 23 22
c prettyness police
e
s 00002/00002/00327
d D 8.3 93/09/23 19:08:41 bostic 22 21
c changes for 4.4BSD-Lite requested by USL
e
s 00004/00004/00325
d D 8.2 93/09/22 16:05:41 bostic 21 20
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00327
d D 8.1 93/05/31 15:05:38 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00321
d D 5.18 93/05/30 12:16:27 bostic 19 18
c Mike Karels at BSDI fixed the types for the rest of the keywords
e
s 00004/00004/00325
d D 5.17 93/05/28 22:52:17 bostic 18 17
c pid_t is now a long, not a short
e
s 00006/00006/00323
d D 5.16 93/04/29 13:18:25 bostic 17 16
c use err/warn from the C library
e
s 00004/00002/00325
d D 5.15 93/04/27 18:15:44 bostic 16 15
c kinfo_proc.h gone, stuff moved to <sys/sysctl.h>
e
s 00002/00002/00325
d D 5.14 92/11/29 02:26:28 torek 15 14
c p_cpu is a u_int, not a u_char
e
s 00006/00006/00321
d D 5.13 92/08/27 15:53:03 marc 14 13
c gack - uids and gids went to longs.  this shouldn't be hardwired into ps.
e
s 00008/00012/00319
d D 5.12 92/06/05 18:56:52 bostic 13 12
c ANSI prototypes (two real bugs)
e
s 00001/00001/00330
d D 5.11 92/03/01 20:53:11 ralph 12 11
c don't bsearch() the null entry.
e
s 00001/00001/00330
d D 5.10 91/10/22 16:13:22 marc 11 10
c command() was missing USER flag
e
s 00002/00001/00329
d D 5.9 91/06/03 17:26:28 bostic 10 8
c the format string gets modified by parsefmt -- don't use it twice
e
s 00013/00003/00327
d R 5.9 91/06/03 17:19:40 bostic 9 8
c copy format strings, so "ps -ll" works
e
s 00005/00009/00325
d D 5.8 91/06/03 16:55:37 bostic 8 7
c fix err routine, make everyone use it; minor ANSI cleanups
e
s 00003/00002/00331
d D 5.7 91/06/03 16:24:57 bostic 7 6
c don't print a space before the first keyword
e
s 00001/00001/00332
d D 5.6 91/05/06 16:03:05 karels 6 5
c ppid is in eproc now
e
s 00002/00002/00331
d D 5.5 91/04/08 11:35:26 bostic 5 4
c null indirection
e
s 00013/00004/00320
d D 5.4 91/03/27 15:49:48 marc 4 3
c its \not/ an error to specify a keyword twice
e
s 00102/00001/00222
d D 5.3 91/03/27 15:04:23 karels 3 2
c new vm
e
s 00000/00003/00223
d D 5.2 91/02/12 16:05:54 bostic 2 1
c delete "rusage" alias; delete -s option; change "trs" to "trss"
c two bugs: sortby needed to be initalized, typo in an error message
e
s 00210/00000/00000
d D 5.1 91/02/08 10:58:27 bostic 1 0
c Put print/keyword routines into separate modules; delete attime.c, use
c strftime(3) instead; put combination keywords into main keyword list,
c sort, delete aliases, and use bsearch(3); don't fail if nlist fails or
c devices aren't found.  Whack the manual page for consistency, correctness.
e
u
U
t
T
I 1
/*-
D 20
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 20
I 20
D 24
 * Copyright (c) 1990, 1993
E 24
I 24
 * Copyright (c) 1990, 1993, 1994
E 24
 *	The Regents of the University of California.  All rights reserved.
E 20
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/param.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/proc.h>
I 16

I 17
#include <err.h>
E 17
E 16
#include <errno.h>
I 16
#include <stddef.h>
E 16
#include <stdio.h>
I 8
#include <stdlib.h>
E 8
D 16
#include <stddef.h>
E 16
#include <string.h>
I 16

E 16
#include "ps.h"

I 3
D 22
#ifdef SPPWAIT
E 22
I 22
#ifdef P_PPWAIT
E 22
#define NEWVM
#endif

#ifdef NEWVM
#include <sys/ucred.h>
D 16
#include <sys/kinfo_proc.h>
E 16
I 16
#include <sys/sysctl.h>
E 16
#endif

E 3
D 13
int	command(), cputime(), evar(), logname(), longtname(), lstarted(),
	maxrss(), p_rssize(), pagein(), pcpu(), pmem(), pri(), pvar(),
	rssize(), runame(), rvar(), started(), state(), tdev(), tname(),
D 3
	trss(), tsize(), ucomm(), uname(), uvar(), vsize(), wchan();
E 3
I 3
	tsize(), ucomm(), uname(), uvar(), vsize(), wchan();
#ifndef NEWVM
int	trss();
#endif
E 13
I 13
static VAR *findvar __P((char *));
static int  vcmp __P((const void *, const void *));
E 13
E 3

#ifdef NOTINUSE
int	utime(), stime(), ixrss(), idrss(), isrss();
	{{"utime"}, "UTIME", USER, utime, 4},
	{{"stime"}, "STIME", USER, stime, 4},
	{{"ixrss"}, "IXRSS", USER, ixrss, 4},
	{{"idrss"}, "IDRSS", USER, idrss, 4},
	{{"isrss"}, "ISRSS", USER, isrss, 4},
#endif

/* Compute offset in common structures. */
#define	POFF(x)	offsetof(struct proc, x)
#define	EOFF(x)	offsetof(struct eproc, x)
#define	UOFF(x)	offsetof(struct usave, x)
#define	ROFF(x)	offsetof(struct rusage, x)

#define	UIDFMT	"u"
#define	UIDLEN	5
#define	PIDFMT	"d"
#define	PIDLEN	5
#define	USERLEN	8

VAR var[] = {
I 3
#ifdef NEWVM
E 3
	{"%cpu", "%CPU", NULL, 0, pcpu, 4},
	{"%mem", "%MEM", NULL, 0, pmem, 4},
I 3
D 14
	{"acflag", "ACFLG", NULL, 0, pvar, 3, POFF(p_acflag), SHORT, "x"},
E 14
I 14
	{"acflag", "ACFLG", NULL, 0, pvar, 3, POFF(p_acflag), USHORT, "x"},
E 14
	{"acflg", "", "acflag"},
	{"blocked", "", "sigmask"},
	{"caught", "", "sigcatch"},
D 11
	{"command", "COMMAND", NULL, COMM|LJUST, command, 16},
E 11
I 11
	{"command", "COMMAND", NULL, COMM|LJUST|USER, command, 16},
E 11
D 15
	{"cpu", "CPU", NULL, 0, pvar, 3, POFF(p_cpu), UCHAR, "d"},
E 15
I 15
D 21
	{"cpu", "CPU", NULL, 0, pvar, 3, POFF(p_cpu), ULONG, "d"},
E 21
I 21
	{"cpu", "CPU", NULL, 0, pvar, 3, POFF(p_estcpu), ULONG, "d"},
E 21
E 15
	{"cputime", "", "time"},
	{"f", "F", NULL, 0, pvar, 7, POFF(p_flag), LONG, "x"},
	{"flags", "", "f"},
	{"ignored", "", "sigignore"},
	{"inblk", "INBLK", NULL, USER, rvar, 4, ROFF(ru_inblock), LONG, "d"},
	{"inblock", "", "inblk"},
	{"jobc", "JOBC", NULL, 0, evar, 4, EOFF(e_jobc), SHORT, "d"},
	{"ktrace", "KTRACE", NULL, 0, pvar, 8, POFF(p_traceflag), LONG, "x"},
	{"ktracep", "KTRACEP", NULL, 0, pvar, 8, POFF(p_tracep), LONG, "x"},
	{"lim", "LIM", NULL, 0, maxrss, 5},
	{"login", "LOGIN", NULL, LJUST, logname, MAXLOGNAME},
	{"logname", "", "login"},
	{"lstart", "STARTED", NULL, LJUST|USER, lstarted, 28},
	{"majflt", "MAJFLT", NULL, USER, rvar, 4, ROFF(ru_majflt), LONG, "d"},
	{"minflt", "MINFLT", NULL, USER, rvar, 4, ROFF(ru_minflt), LONG, "d"},
	{"msgrcv", "MSGRCV", NULL, USER, rvar, 4, ROFF(ru_msgrcv), LONG, "d"},
	{"msgsnd", "MSGSND", NULL, USER, rvar, 4, ROFF(ru_msgsnd), LONG, "d"},
	{"ni", "", "nice"},
	{"nice", "NI", NULL, 0, pvar, 2, POFF(p_nice), CHAR, "d"},
	{"nivcsw", "NIVCSW", NULL, USER, rvar, 5, ROFF(ru_nivcsw), LONG, "d"},
	{"nsignals", "", "nsigs"},
	{"nsigs", "NSIGS", NULL, USER, rvar, 4, ROFF(ru_nsignals), LONG, "d"},
	{"nswap", "NSWAP", NULL, USER, rvar, 4, ROFF(ru_nswap), LONG, "d"},
	{"nvcsw", "NVCSW", NULL, USER, rvar, 5, ROFF(ru_nvcsw), LONG, "d"},
	{"nwchan", "WCHAN", NULL, 0, pvar, 6, POFF(p_wchan), KPTR, "x"},
	{"oublk", "OUBLK", NULL, USER, rvar, 4, ROFF(ru_oublock), LONG, "d"},
	{"oublock", "", "oublk"},
	{"p_ru", "P_RU", NULL, 0, pvar, 6, POFF(p_ru), KPTR, "x"},
	{"paddr", "PADDR", NULL, 0, evar, 6, EOFF(e_paddr), KPTR, "x"},
	{"pagein", "PAGEIN", NULL, USER, pagein, 6},
	{"pcpu", "", "%cpu"},
	{"pending", "", "sig"},
D 19
	{"pgid", "PGID", NULL, 0, evar, PIDLEN, EOFF(e_pgid), USHORT, PIDFMT},
E 19
I 19
	{"pgid", "PGID", NULL, 0, evar, PIDLEN, EOFF(e_pgid), ULONG, PIDFMT},
E 19
D 18
	{"pid", "PID", NULL, 0, pvar, PIDLEN, POFF(p_pid),SHORT, PIDFMT},
E 18
I 18
	{"pid", "PID", NULL, 0, pvar, PIDLEN, POFF(p_pid), LONG, PIDFMT},
E 18
	{"pmem", "", "%mem"},
D 6
	{"ppid", "PPID", NULL, 0, pvar, PIDLEN, POFF(p_ppid), SHORT, PIDFMT},
E 6
I 6
D 18
	{"ppid", "PPID", NULL, 0, evar, PIDLEN, EOFF(e_ppid), SHORT, PIDFMT},
E 18
I 18
	{"ppid", "PPID", NULL, 0, evar, PIDLEN, EOFF(e_ppid), LONG, PIDFMT},
E 18
E 6
	{"pri", "PRI", NULL, 0, pri, 3},
D 19
	{"re", "RE", NULL, 0, pvar, 3, POFF(p_time), CHAR, "d"},
E 19
I 19
D 21
	{"re", "RE", NULL, 0, pvar, 3, POFF(p_time), ULONG, "d"},
E 21
I 21
	{"re", "RE", NULL, 0, pvar, 3, POFF(p_swtime), ULONG, "d"},
E 21
E 19
	{"rgid", "RGID", NULL, 0, evar, UIDLEN, EOFF(e_pcred.p_rgid),
D 14
		USHORT, UIDFMT},
E 14
I 14
		ULONG, UIDFMT},
E 14
D 22
	{"rlink", "RLINK", NULL, 0, pvar, 8, POFF(p_rlink), KPTR, "x"},
E 22
I 22
	{"rlink", "RLINK", NULL, 0, pvar, 8, POFF(p_back), KPTR, "x"},
E 22
	{"rss", "RSS", NULL, 0, p_rssize, 4},
	{"rssize", "", "rsz"},
	{"rsz", "RSZ", NULL, 0, rssize, 4},
	{"ruid", "RUID", NULL, 0, evar, UIDLEN, EOFF(e_pcred.p_ruid),
D 14
		USHORT, UIDFMT},
E 14
I 14
		ULONG, UIDFMT},
E 14
	{"ruser", "RUSER", NULL, LJUST, runame, USERLEN},
	{"sess", "SESS", NULL, 0, evar, 6, EOFF(e_sess), KPTR, "x"},
D 21
	{"sig", "PENDING", NULL, 0, pvar, 8, POFF(p_sig), LONG, "x"},
E 21
I 21
	{"sig", "PENDING", NULL, 0, pvar, 8, POFF(p_siglist), LONG, "x"},
E 21
	{"sigcatch", "CAUGHT", NULL, 0, pvar, 8, POFF(p_sigcatch), LONG, "x"},
	{"sigignore", "IGNORED",
		NULL, 0, pvar, 8, POFF(p_sigignore), LONG, "x"},
	{"sigmask", "BLOCKED", NULL, 0, pvar, 8, POFF(p_sigmask), LONG, "x"},
D 19
	{"sl", "SL", NULL, 0, pvar, 3, POFF(p_slptime), CHAR, "d"},
E 19
I 19
	{"sl", "SL", NULL, 0, pvar, 3, POFF(p_slptime), ULONG, "d"},
E 19
	{"start", "STARTED", NULL, LJUST|USER, started, 8},
	{"stat", "", "state"},
	{"state", "STAT", NULL, 0, state, 4},
	{"svgid", "SVGID",
D 14
		NULL, 0, evar, UIDLEN, EOFF(e_pcred.p_svgid), USHORT, UIDFMT},
E 14
I 14
		NULL, 0, evar, UIDLEN, EOFF(e_pcred.p_svgid), ULONG, UIDFMT},
E 14
	{"svuid", "SVUID",
D 14
		NULL, 0, evar, UIDLEN, EOFF(e_pcred.p_svuid), USHORT, UIDFMT},
E 14
I 14
		NULL, 0, evar, UIDLEN, EOFF(e_pcred.p_svuid), ULONG, UIDFMT},
E 14
	{"tdev", "TDEV", NULL, 0, tdev, 4},
	{"time", "TIME", NULL, USER, cputime, 9},
D 19
	{"tpgid", "TPGID", NULL, 0, evar, 4, EOFF(e_tpgid), USHORT, PIDFMT},
E 19
I 19
	{"tpgid", "TPGID", NULL, 0, evar, 4, EOFF(e_tpgid), ULONG, PIDFMT},
E 19
	{"tsess", "TSESS", NULL, 0, evar, 6, EOFF(e_tsess), KPTR, "x"},
	{"tsiz", "TSIZ", NULL, 0, tsize, 4},
	{"tt", "TT", NULL, LJUST, tname, 3},
	{"tty", "TTY", NULL, LJUST, longtname, 8},
	{"ucomm", "UCOMM", NULL, LJUST, ucomm, MAXCOMLEN},
	{"uid", "UID", NULL, 0, evar, UIDLEN, EOFF(e_ucred.cr_uid),
D 14
		USHORT, UIDFMT},
E 14
I 14
		ULONG, UIDFMT},
E 14
	{"upr", "UPR", NULL, 0, pvar, 3, POFF(p_usrpri), CHAR, "d"},
	{"user", "USER", NULL, LJUST, uname, USERLEN},
	{"usrpri", "", "upr"},
	{"vsize", "", "vsz"},
	{"vsz", "VSZ", NULL, 0, vsize, 5},
	{"wchan", "WCHAN", NULL, LJUST, wchan, 6},
	{"xstat", "XSTAT", NULL, 0, pvar, 4, POFF(p_xstat), USHORT, "x"},
#else
	{"%cpu", "%CPU", NULL, 0, pcpu, 4},
	{"%mem", "%MEM", NULL, 0, pmem, 4},
E 3
	{"acflag", "ACFLG", NULL, USER, uvar, 3, UOFF(u_acflag), SHORT, "x"},
	{"acflg", "", "acflag"},
	{"blocked", "", "sigmask"},
	{"caught", "", "sigcatch"},
	{"command", "COMMAND", NULL, COMM|LJUST|USER, command, 16},
D 15
	{"cpu", "CPU", NULL, 0, pvar, 3, POFF(p_cpu), UCHAR, "d"},
E 15
I 15
	{"cpu", "CPU", NULL, 0, pvar, 3, POFF(p_cpu), ULONG, "d"},
E 15
	{"cputime", "", "time"},
	{"f", "F", NULL, 0, pvar, 7, POFF(p_flag), LONG, "x"},
	{"flags", "", "f"},
	{"ignored", "", "sigignore"},
	{"inblk", "INBLK", NULL, USER, rvar, 4, ROFF(ru_inblock), LONG, "d"},
	{"inblock", "", "inblk"},
	{"jobc", "JOBC", NULL, 0, evar, 4, EOFF(e_jobc), SHORT, "d"},
	{"ktrace", "KTRACE", NULL, 0, pvar, 8, POFF(p_traceflag), LONG, "x"},
	{"ktracep", "KTRACEP", NULL, 0, pvar, 8, POFF(p_tracep), LONG, "x"},
	{"lim", "LIM", NULL, 0, maxrss, 5},
	{"logname", "LOGNAME", NULL, LJUST, logname, MAXLOGNAME},
	{"lstart", "STARTED", NULL, LJUST|USER, lstarted, 28},
	{"majflt", "MAJFLT", NULL, USER, rvar, 4, ROFF(ru_majflt), LONG, "d"},
	{"minflt", "MINFLT", NULL, USER, rvar, 4, ROFF(ru_minflt), LONG, "d"},
	{"msgrcv", "MSGRCV", NULL, USER, rvar, 4, ROFF(ru_msgrcv), LONG, "d"},
	{"msgsnd", "MSGSND", NULL, USER, rvar, 4, ROFF(ru_msgsnd), LONG, "d"},
	{"ni", "", "nice"},
	{"nice", "NI", NULL, 0, pvar, 2, POFF(p_nice), CHAR, "d"},
	{"nivcsw", "NIVCSW", NULL, USER, rvar, 5, ROFF(ru_nivcsw), LONG, "d"},
	{"nsignals", "", "nsigs"},
	{"nsigs", "NSIGS", NULL, USER, rvar, 4, ROFF(ru_nsignals), LONG, "d"},
	{"nswap", "NSWAP", NULL, USER, rvar, 4, ROFF(ru_nswap), LONG, "d"},
	{"nvcsw", "NVCSW", NULL, USER, rvar, 5, ROFF(ru_nvcsw), LONG, "d"},
	{"nwchan", "WCHAN", NULL, 0, pvar, 6, POFF(p_wchan), KPTR, "x"},
	{"oublk", "OUBLK", NULL, USER, rvar, 4, ROFF(ru_oublock), LONG, "d"},
	{"oublock", "", "oublk"},
	{"p_ru", "P_RU", NULL, 0, pvar, 6, POFF(p_ru), KPTR, "x"},
	{"paddr", "PADDR", NULL, 0, evar, 6, EOFF(e_paddr), KPTR, "x"},
	{"pagein", "PAGEIN", NULL, USER, pagein, 6},
	{"pcpu", "", "%cpu"},
	{"pending", "", "sig"},
D 19
	{"pgid", "PGID", NULL, 0, evar, PIDLEN, EOFF(e_pgid), USHORT, PIDFMT},
E 19
I 19
	{"pgid", "PGID", NULL, 0, evar, PIDLEN, EOFF(e_pgid), ULONG, PIDFMT},
E 19
D 18
	{"pid", "PID", NULL, 0, pvar, PIDLEN, POFF(p_pid),SHORT, PIDFMT},
E 18
I 18
	{"pid", "PID", NULL, 0, pvar, PIDLEN, POFF(p_pid), LONG, PIDFMT},
E 18
	{"pmem", "", "%mem"},
	{"poip", "POIP", NULL, 0, pvar, 4, POFF(p_poip), SHORT, "d"},
D 18
	{"ppid", "PPID", NULL, 0, pvar, PIDLEN, POFF(p_ppid), SHORT, PIDFMT},
E 18
I 18
	{"ppid", "PPID", NULL, 0, pvar, PIDLEN, POFF(p_ppid), LONG, PIDFMT},
E 18
	{"pri", "PRI", NULL, 0, pri, 3},
D 19
	{"re", "RE", NULL, 0, pvar, 3, POFF(p_time), CHAR, "d"},
E 19
I 19
D 21
	{"re", "RE", NULL, 0, pvar, 3, POFF(p_time), ULONG, "d"},
E 21
I 21
	{"re", "RE", NULL, 0, pvar, 3, POFF(p_swtime), ULONG, "d"},
E 21
E 19
	{"rgid", "RGID", NULL, 0, pvar, UIDLEN, POFF(p_rgid), USHORT, UIDFMT},
	{"rlink", "RLINK", NULL, 0, pvar, 8, POFF(p_rlink), KPTR, "x"},
	{"rss", "RSS", NULL, 0, p_rssize, 4},
	{"rssize", "", "rsz"},
	{"rsz", "RSZ", NULL, 0, rssize, 4},
	{"ruid", "RUID", NULL, 0, pvar, UIDLEN, POFF(p_ruid), USHORT, UIDFMT},
D 2
	{"rusage", "",
		"minflt majflt nswap inblock oublock msgsnd msgrcv nsigs \
		 nvcsw nivcsw"},
E 2
	{"ruser", "RUSER", NULL, LJUST, runame, USERLEN},
	{"sess", "SESS", NULL, 0, evar, 6, EOFF(e_sess), KPTR, "x"},
	{"sig", "PENDING", NULL, 0, pvar, 8, POFF(p_sig), LONG, "x"},
	{"sigcatch", "CAUGHT", NULL, 0, pvar, 8, POFF(p_sigcatch), LONG, "x"},
	{"sigignore", "IGNORED",
		NULL, 0, pvar, 8, POFF(p_sigignore), LONG, "x"},
	{"sigmask", "BLOCKED", NULL, 0, pvar, 8, POFF(p_sigmask), LONG, "x"},
D 19
	{"sl", "SL", NULL, 0, pvar, 3, POFF(p_slptime), CHAR, "d"},
E 19
I 19
	{"sl", "SL", NULL, 0, pvar, 3, POFF(p_slptime), ULONG, "d"},
E 19
	{"start", "STARTED", NULL, LJUST|USER, started, 8},
	{"stat", "", "state"},
	{"state", "STAT", NULL, 0, state, 4},
	{"svgid", "SVGID",
		NULL, 0, pvar, UIDLEN, POFF(p_svgid), USHORT, UIDFMT},
	{"svuid", "SVUID",
		NULL, 0, pvar, UIDLEN, POFF(p_svuid), USHORT, UIDFMT},
	{"tdev", "TDEV", NULL, 0, tdev, 4},
	{"time", "TIME", NULL, USER, cputime, 9},
D 19
	{"tpgid", "TPGID", NULL, 0, evar, 4, EOFF(e_tpgid), USHORT, PIDFMT},
E 19
I 19
	{"tpgid", "TPGID", NULL, 0, evar, 4, EOFF(e_tpgid), ULONG, PIDFMT},
E 19
	{"trs", "TRS", NULL, 0, trss, 3},
	{"tsess", "TSESS", NULL, 0, evar, 6, EOFF(e_tsess), KPTR, "x"},
	{"tsiz", "TSIZ", NULL, 0, tsize, 4},
	{"tt", "TT", NULL, LJUST, tname, 3},
	{"tty", "TTY", NULL, LJUST, longtname, 8},
	{"ucomm", "UCOMM", NULL, LJUST, ucomm, MAXCOMLEN},
	{"uid", "UID", NULL, 0, pvar, UIDLEN, POFF(p_uid),USHORT, UIDFMT},
	{"upr", "UPR", NULL, 0, pvar, 3, POFF(p_usrpri), CHAR, "d"},
	{"uprocp", "UPROCP", NULL, USER, uvar, 6, UOFF(u_procp), KPTR, "x"},
	{"user", "USER", NULL, LJUST, uname, USERLEN},
	{"usrpri", "", "upr"},
	{"vsize", "", "vsz"},
	{"vsz", "VSZ", NULL, 0, vsize, 5},
	{"wchan", "WCHAN", NULL, LJUST, wchan, 6},
	{"xstat", "XSTAT", NULL, 0, pvar, 4, POFF(p_xstat), USHORT, "x"},
I 3
#endif
E 3
	{""},
};

I 13
void
E 13
showkey()
{
D 23
	extern int termwidth;
	register VAR *v;
	register int i, len;
	register char *p, *sep;
E 23
I 23
	VAR *v;
	int i;
	char *p, *sep;
E 23

	i = 0;
I 7
	sep = "";
E 7
	for (v = var; *(p = v->name); ++v) {
D 23
		len = strlen(p);
E 23
I 23
		int len = strlen(p);
E 23
		if (termwidth && (i += len + 1) > termwidth) {
			i = len;
			sep = "\n";
D 5
		}
E 5
I 5
D 7
		} else
			sep = " ";
E 7
I 7
		}
E 7
E 5
		(void) printf("%s%s", sep, p);
I 7
		sep = " ";
E 7
D 5
		sep = " ";
E 5
	}
	(void) printf("\n");
}

I 13
void
E 13
parsefmt(p)
	char *p;
{
I 10
	static struct varent *vtail;
E 10
D 23
	register VAR *v;
	register char *cp;
I 4
	register struct varent *vent;
E 23
E 4
D 13
	static VAR *findvar();
E 13

#define	FMTSEP	" \t,\n"
D 10
	while (p) {
E 10
I 10
	while (p && *p) {
I 23
		char *cp;
		VAR *v;
		struct varent *vent;

E 23
E 10
D 4
		while ((cp = strsep(&p, FMTSEP)) != NULL && *cp == '\0');
E 4
I 4
		while ((cp = strsep(&p, FMTSEP)) != NULL && *cp == '\0')
			/* void */;
E 4
		if (!(v = findvar(cp)))
			continue;
I 4
D 8
		if ((vent = (struct varent *)malloc(sizeof(struct varent))) == 
		    NULL) {
			(void)fprintf(stderr, "ps: no space\n");
			exit(1);
		}
E 8
I 8
		if ((vent = malloc(sizeof(struct varent))) == NULL)
D 17
			err("%s", strerror(errno));
E 17
I 17
			err(1, NULL);
E 17
E 8
		vent->var = v;
		vent->next = NULL;
E 4
		if (vhead == NULL)
D 4
			vhead = vtail = v;
E 4
I 4
			vhead = vtail = vent;
E 4
		else {
D 4
			vtail->next = v;
			vtail = v;
E 4
I 4
			vtail->next = vent;
			vtail = vent;
E 4
		}
	}
D 8
	if (!vhead) {
		(void)fprintf(stderr, "ps: no valid keywords\n");
		exit(1);
	}
E 8
I 8
	if (!vhead)
D 17
		err("no valid keywords\n");
E 17
I 17
		errx(1, "no valid keywords");
E 17
E 8
}

static VAR *
findvar(p)
	char *p;
{
D 23
	extern int eval;
E 23
	VAR *v, key;
	char *hp;
	int vcmp();

	key.name = p;

D 17
	hp = index(p, '=');
E 17
I 17
	hp = strchr(p, '=');
E 17
	if (hp)
		*hp++ = '\0';

	key.name = p;
D 13
	v = (VAR *)bsearch(&key, var,
D 12
	    sizeof(var)/sizeof(VAR), sizeof(VAR), vcmp);
E 12
I 12
		sizeof(var)/sizeof(VAR) - 1, sizeof(VAR), vcmp);
E 13
I 13
	v = bsearch(&key, var, sizeof(var)/sizeof(VAR) - 1, sizeof(VAR), vcmp);
E 13
E 12

	if (v && v->alias) {
		if (hp) {
D 17
			(void)fprintf(stderr,
			    "ps: %s: illegal keyword specification\n", p);
E 17
I 17
			warnx("%s: illegal keyword specification", p);
E 17
			eval = 1;
		}
		parsefmt(v->alias);
D 23
		return((VAR *)NULL);
E 23
I 23
		return ((VAR *)NULL);
E 23
	}
	if (!v) {
D 17
		(void)fprintf(stderr, "ps: keyword %s not found\n", p);
E 17
I 17
		warnx("%s: keyword not found", p);
E 17
		eval = 1;
	}
	if (hp)
		v->header = hp;
D 23
	return(v);
E 23
I 23
	return (v);
E 23
}

I 13
static int
E 13
vcmp(a, b)
D 13
        VAR *a, *b;
E 13
I 13
        const void *a, *b;
E 13
{
D 13
        return(strcmp(a->name, b->name));
E 13
I 13
D 23
        return(strcmp(((VAR *)a)->name, ((VAR *)b)->name));
E 23
I 23
        return (strcmp(((VAR *)a)->name, ((VAR *)b)->name));
E 23
E 13
}
E 1
