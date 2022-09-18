h34975
s 00011/00028/01018
d D 8.10 95/05/04 16:56:35 mckusick 37 36
c use getvfsbyname to find filesystem type number
e
s 00008/00011/01038
d D 8.9 95/04/28 14:55:38 bostic 36 34
c This fixes some bogosity when different kinds of `-fstype' option are
c mixed; e.g. `-fstype local ! -fstype fdesc'.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00006/00003/01046
d R 8.9 95/04/28 14:42:59 bostic 35 34
c This fixes some bogosity when different kinds of `-fstype' option are
c mixed; e.g. `-fstype local ! -fstype fdesc'.
c From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00002/00000/01047
d D 8.8 94/08/05 16:32:23 mckusick 34 33
c white-out is on an ifdef
e
s 00007/00003/01040
d D 8.7 94/07/28 03:38:44 pendry 33 32
c changes for whiteouts and union filesystem
e
s 00007/00009/01036
d D 8.6 94/04/01 07:27:25 bostic 32 31
c lint
e
s 00001/00001/01044
d D 8.5 94/04/01 07:26:11 bostic 31 30
c lint
e
s 00002/00002/01043
d D 8.4 94/02/21 21:08:40 bostic 30 29
c find . -nouser would show all files which *have* a valid owner
c From: "Chris G. Demetriou" <cgd@postgres.Berkeley.EDU>
e
s 00001/00001/01044
d D 8.3 94/01/23 18:18:45 mckusick 29 28
c last vestage of MOUNT_PC
e
s 00001/00001/01044
d D 8.2 94/01/23 12:18:03 bostic 28 27
c MOUNT_PC -> MOUNT_MSDOS
e
s 00002/00002/01043
d D 8.1 93/06/06 14:39:03 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00003/01030
d D 5.26 93/05/01 12:04:25 bostic 26 25
c correct -n for time ranges, so that "-mtime -1" is < 1, not < 0
c THIS APPEARS TO VIOLATE POSIX 1003.2
e
s 00128/00104/00905
d D 5.25 93/05/01 11:51:36 bostic 25 24
c use library err/warn(3) functions; lint, prettiness police
e
s 00007/00012/01002
d D 5.24 93/02/19 13:35:10 marc 24 23
c allow +/- on most operators
e
s 00018/00011/00996
d D 5.23 92/07/27 08:32:02 bostic 23 22
c fix -size (trailing character not set in c_size); cleanup signed
c and trailing character handline
e
s 00002/00000/01005
d D 5.22 92/06/29 14:45:37 bostic 22 21
c new include file, fnmatch.h
e
s 00002/00002/01003
d D 5.21 92/06/29 14:38:46 bostic 21 20
c FNM_QUOTE now the default for fnmatch, reverse return value
e
s 00017/00017/00988
d D 5.20 92/01/27 11:20:53 bostic 20 19
c fts_statb -> fts_statp
e
s 00001/00000/01004
d D 5.19 91/12/05 08:41:38 bostic 19 18
c mount.h needs param.h and ucred.h, now
e
s 00096/00052/00908
d D 5.18 91/07/19 15:05:12 bostic 18 17
c add -path, -fstype rdonly; document values for PLAN->flags
e
s 00010/00007/00950
d D 5.17 91/05/24 15:36:40 bostic 17 16
c change find to do an fchdir on exec/ok; this means that the -r
c option can go away and everybody gets the speedup
e
s 00060/00099/00897
d D 5.16 91/05/24 15:17:10 bostic 16 15
c return to the original find syntax (newsyntax.c -> main.c, delete
c oldsyntax.c; create extern.h for ANSI prototypes; create true error routine;
c make NEW macro a real routine
e
s 00028/00028/00968
d D 5.15 91/05/23 18:53:29 bostic 15 14
c T_USER used in the kernel, included by <sys/param.h> -- change to
c be N_ instead.  Make it an enum while we're there...
e
s 00013/00016/00983
d D 5.14 91/03/10 11:37:04 bostic 14 13
c ANSI, error routine; use new fts routines which set errno correctly
c so there's lots less work to do here.
e
s 00004/00004/00995
d D 5.13 91/01/02 16:06:19 bostic 13 12
c e_len are int's; use MAXPATHLEN, not 1024
c bug report 4.3BSD-reno/usr.bin/5
e
s 00026/00000/00973
d D 5.12 90/11/18 11:56:46 bostic 12 11
c Fix fstype function.  Statfs follows symlinks, find wants the link's
c file system, not where it points.
c Test case is "ln -s nonexistent_file foo; find foo fstype local"
e
s 00004/00005/00969
d D 5.11 90/11/15 13:03:02 bostic 11 10
c use getchar() for queryuser function; lots of minor lint
e
s 00022/00011/00952
d D 5.10 90/11/15 12:32:37 bostic 10 9
c don't require stat(2) information for xdev function; lint;
c make status variables consistent
e
s 00004/00002/00959
d D 5.9 90/10/22 09:52:25 bostic 9 8
c add -r option, allowing -exec/-ok to do relative traversal
e
s 00001/00001/00960
d D 5.8 90/06/30 18:23:55 trent 8 7
c declaration boo-boo
e
s 00004/00003/00957
d D 5.7 90/06/30 18:18:45 trent 7 6
c two bugs: 'perm' primary didn't work because setmode() and getmode() were used incorrectly; 'type' primary didn't work correctly (thought sockets & symlinks were regular files).  both fixes from Mike Hibler (mike@cs.utah.edu)
e
s 00001/00000/00959
d D 5.6 90/06/24 23:06:18 bostic 6 5
c set curdev, otherwise we'll statfs on every file
e
s 00005/00006/00954
d D 5.5 90/05/22 15:00:49 bostic 5 4
c fts now has flag to keep from crossing mount points
e
s 00043/00041/00917
d D 5.4 90/05/20 13:13:49 bostic 4 3
c add fstype "local"; remove FIND_{TRUE,FALSE}; rename fts fields
e
s 00001/00001/00957
d D 5.3 90/05/15 19:55:22 bostic 3 2
c string.h is ANSI C include file
e
s 00001/00000/00957
d D 5.2 90/05/12 15:28:33 bostic 2 1
c define strerror() return
e
s 00957/00000/00000
d D 5.1 90/04/16 17:23:06 bostic 1 0
c new version derived from Cimarron Taylor's
e
u
U
t
T
I 1
/*-
D 27
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
 * This code is derived from software contributed to Berkeley by
 * Cimarron D. Taylor of the University of California, Berkeley.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 13
#include <sys/types.h>
E 13
I 13
#include <sys/param.h>
I 19
#include <sys/ucred.h>
E 19
E 13
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/mount.h>
I 22

I 25
#include <err.h>
E 25
E 22
I 10
D 14
#include <sys/errno.h>
E 14
I 14
#include <errno.h>
I 25
#include <fnmatch.h>
#include <fts.h>
E 25
E 14
E 10
#include <grp.h>
#include <pwd.h>
D 25
#include <fts.h>
I 22
#include <fnmatch.h>
E 22
#include <unistd.h>
#include <tzfile.h>
E 25
#include <stdio.h>
I 14
#include <stdlib.h>
E 14
I 2
D 3
#include <strings.h>
E 3
I 3
#include <string.h>
I 25
#include <tzfile.h>
#include <unistd.h>

E 25
E 3
E 2
#include "find.h"

D 18
#define	FIND_EQUAL	0
#define	FIND_LESSTHAN	1
#define	FIND_GREATER	2

E 18
D 4
#define	FIND_FALSE	0
#define	FIND_TRUE	1

E 4
D 25
#define	COMPARE(a, b) { \
	switch(plan->flags) { \
D 18
	case FIND_EQUAL: \
E 18
I 18
	case F_EQUAL: \
E 18
		return(a == b); \
D 18
	case FIND_LESSTHAN: \
E 18
I 18
	case F_LESSTHAN: \
E 18
		return(a < b); \
D 18
	case FIND_GREATER: \
E 18
I 18
	case F_GREATER: \
E 18
		return(a > b); \
	} \
D 4
	return(FIND_FALSE); \
E 4
I 4
	return(0); \
E 25
I 25
#define	COMPARE(a, b) {							\
	switch (plan->flags) {						\
	case F_EQUAL:							\
		return (a == b);					\
	case F_LESSTHAN:						\
		return (a < b);						\
	case F_GREATER:							\
		return (a > b);						\
	default:							\
		abort();						\
	}								\
E 25
E 4
}

D 16
#define NEW(t, f) { \
	new = (PLAN *)emalloc(sizeof(PLAN)); \
	new->type = t; \
	new->eval = f; \
	new->flags = 0; \
	new->next = NULL; \
}
E 16
I 16
D 25
static PLAN *palloc __P((enum ntype, int (*)()));
E 25
I 25
static PLAN *palloc __P((enum ntype, int (*) __P((PLAN *, FTSENT *))));
E 25
E 16

/*
 * find_parsenum --
 *	Parse a string of the form [+-]# and return the value.
 */
D 23
long
find_parsenum(plan, option, str, endch)
E 23
I 23
static long
D 24
find_parsenum(plan, option, str, nosign, endch)
E 24
I 24
D 25
find_parsenum(plan, option, str, endch)
E 25
I 25
find_parsenum(plan, option, vp, endch)
E 25
E 24
E 23
	PLAN *plan;
D 25
	char *option, *str, *endch;
E 25
I 25
	char *option, *vp, *endch;
E 25
I 23
D 24
	int nosign;
E 24
E 23
{
	long value;
D 25
	char *endchar;		/* pointer to character ending conversion */
E 25
I 25
D 26
	char *endchar, *str;	/* pointer to character ending conversion */
E 26
I 26
	char *endchar, *str;	/* Pointer to character ending conversion. */
E 26
E 25
I 10
D 16
	void bad_arg();
E 16
E 10
    
D 26
	/* determine comparison from leading + or - */
E 26
I 26
	/* Determine comparison from leading + or -. */
E 26
D 25
	switch(*str) {
E 25
I 25
	str = vp;
	switch (*str) {
E 25
	case '+':
I 23
D 24
		if (nosign)
			err("%s: %s", option, "signed value not permitted");
E 24
E 23
		++str;
D 18
		plan->flags = FIND_GREATER;
E 18
I 18
		plan->flags = F_GREATER;
E 18
		break;
	case '-':
I 23
D 24
		if (nosign)
			err("%s: %s", option, "signed value not permitted");
E 24
E 23
		++str;
D 18
		plan->flags = FIND_LESSTHAN;
E 18
I 18
		plan->flags = F_LESSTHAN;
E 18
		break;
	default:
D 18
		plan->flags = FIND_EQUAL;
E 18
I 18
		plan->flags = F_EQUAL;
E 18
		break;
	}
    
	/*
D 23
	 * convert the string with strtol().  Note, if strtol() returns zero
E 23
I 23
	 * Convert the string with strtol().  Note, if strtol() returns zero
E 23
	 * and endchar points to the beginning of the string we know we have
	 * a syntax error.
	 */
	value = strtol(str, &endchar, 10);
D 23
	if (!value && endchar == str ||
	    endchar[0] && (!endch || endchar[0] != *endch))
E 23
I 23
	if (value == 0 && endchar == str)
E 23
D 16
		bad_arg(option, "illegal numeric value");
E 16
I 16
D 25
		err("%s: %s", option, "illegal numeric value");
E 25
I 25
		errx(1, "%s: %s: illegal numeric value", option, vp);
E 25
I 23
	if (endchar[0] && (endch == NULL || endchar[0] != *endch))
D 25
		err("%s: %s", option, "illegal trailing character");
E 25
I 25
		errx(1, "%s: %s: illegal trailing character", option, vp);
E 25
E 23
E 16
	if (endch)
		*endch = endchar[0];
D 25
	return(value);
E 25
I 25
	return (value);
E 25
}

/*
I 26
 * The value of n for the inode times (atime, ctime, and mtime) is a range,
 * i.e. n matches from (n - 1) to n 24 hour periods.  This interacts with
 * -n, such that "-mtime -1" would be less than 0 days, which isn't what the
 * user wanted.  Correct so that -1 is "less than 1".
 */
#define	TIME_CORRECT(p, ttype)						\
	if ((p)->type == ttype && (p)->flags == F_LESSTHAN)		\
		++((p)->t_data);

/*
E 26
 * -atime n functions --
 *
 *	True if the difference between the file access time and the
 *	current time is n 24 hour periods.
D 26
 *
E 26
 */
I 25
int
E 25
f_atime(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
	extern time_t now;

D 4
	COMPARE((now - entry->statb.st_atime + SECSPERDAY - 1) / SECSPERDAY,
	    plan->t_data);
E 4
I 4
D 20
	COMPARE((now - entry->fts_statb.st_atime +
E 20
I 20
	COMPARE((now - entry->fts_statp->st_atime +
E 20
	    SECSPERDAY - 1) / SECSPERDAY, plan->t_data);
E 4
}
 
PLAN *
c_atime(arg)
	char *arg;
{
	PLAN *new;

	ftsoptions &= ~FTS_NOSTAT;

D 15
	NEW(T_ATIME, f_atime);
E 15
I 15
D 16
	NEW(N_ATIME, f_atime);
E 15
	new->t_data = find_parsenum(new, "-atime", arg, (char *)NULL);
E 16
I 16
	new = palloc(N_ATIME, f_atime);
D 23
	new->t_data = find_parsenum(new, "-atime", arg, NULL);
E 23
I 23
D 24
	new->t_data = find_parsenum(new, "-atime", arg, 0, NULL);
E 24
I 24
	new->t_data = find_parsenum(new, "-atime", arg, NULL);
I 26
	TIME_CORRECT(new, N_ATIME);
E 26
E 24
E 23
E 16
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
/*
 * -ctime n functions --
 *
 *	True if the difference between the last change of file
 *	status information and the current time is n 24 hour periods.
 */
I 25
int
E 25
f_ctime(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
	extern time_t now;

D 4
	COMPARE((now - entry->statb.st_ctime + SECSPERDAY - 1) / SECSPERDAY,
	    plan->t_data);
E 4
I 4
D 20
	COMPARE((now - entry->fts_statb.st_ctime +
E 20
I 20
	COMPARE((now - entry->fts_statp->st_ctime +
E 20
	    SECSPERDAY - 1) / SECSPERDAY, plan->t_data);
E 4
}
 
PLAN *
c_ctime(arg)
	char *arg;
{
	PLAN *new;

	ftsoptions &= ~FTS_NOSTAT;

D 15
	NEW(T_CTIME, f_ctime);
E 15
I 15
D 16
	NEW(N_CTIME, f_ctime);
E 16
I 16
	new = palloc(N_CTIME, f_ctime);
E 16
E 15
D 23
	new->t_data = find_parsenum(new, "-ctime", arg, (char *)NULL);
E 23
I 23
D 24
	new->t_data = find_parsenum(new, "-ctime", arg, 0, NULL);
E 24
I 24
	new->t_data = find_parsenum(new, "-ctime", arg, NULL);
I 26
	TIME_CORRECT(new, N_CTIME);
E 26
E 24
E 23
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}

/*
 * -depth functions --
 *
 *	Always true, causes descent of the directory hierarchy to be done
 *	so that all entries in a directory are acted on before the directory
 *	itself.
 */
D 25
/* ARGSUSED */
E 25
I 25
int
E 25
f_always_true(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	return(FIND_TRUE);
E 4
I 4
D 25
	return(1);
E 25
I 25
	return (1);
E 25
E 4
}
 
PLAN *
c_depth()
{
D 11
	extern int depth;
E 11
D 16
	PLAN *new;
    
E 16
D 10
	depth = 1;
E 10
I 10
	isdepth = 1;
E 10

D 15
	NEW(T_DEPTH, f_always_true);
E 15
I 15
D 16
	NEW(N_DEPTH, f_always_true);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_DEPTH, f_always_true));
E 25
I 25
	return (palloc(N_DEPTH, f_always_true));
E 25
E 16
}
 
/*
 * [-exec | -ok] utility [arg ... ] ; functions --
 *
 *	True if the executed utility returns a zero value as exit status.
 *	The end of the primary expression is delimited by a semicolon.  If
 *	"{}" occurs anywhere, it gets replaced by the current pathname.
 *	The current directory for the execution of utility is the same as
 *	the current directory when the find utility was started.
 *
 *	The primary -ok is different in that it requests affirmation of the
 *	user before executing the utility.
 */
I 25
int
E 25
f_exec(plan, entry)
	register PLAN *plan;
	FTSENT *entry;
{
I 17
	extern int dotfd;
E 17
	register int cnt;
D 10
	char *find_subst();
E 10
D 14
	union wait pstat;
	pid_t pid, waitpid();
E 14
I 14
	pid_t pid;
	int status;
E 14
I 10
D 11
	void find_subst();
E 11
I 11
D 16
	void brace_subst();
E 16
E 11
E 10

	for (cnt = 0; plan->e_argv[cnt]; ++cnt)
		if (plan->e_len[cnt])
D 11
			find_subst(plan->e_orig[cnt], &plan->e_argv[cnt],
E 11
I 11
			brace_subst(plan->e_orig[cnt], &plan->e_argv[cnt],
E 11
D 4
			    entry->path, plan->e_len[cnt]);
E 4
I 4
D 9
			    entry->fts_path, plan->e_len[cnt]);
E 9
I 9
D 17
			    entry->fts_accpath, plan->e_len[cnt]);
E 17
I 17
			    entry->fts_path, plan->e_len[cnt]);
E 17
E 9
E 4

D 11
	if (plan->flags && !find_queryuser(plan->e_argv))
E 11
I 11
D 18
	if (plan->flags && !queryuser(plan->e_argv))
E 18
I 18
	if (plan->flags == F_NEEDOK && !queryuser(plan->e_argv))
E 18
E 11
D 4
		return(FIND_FALSE);
E 4
I 4
D 25
		return(0);
E 25
I 25
		return (0);
E 25
E 4

D 25
	switch(pid = vfork()) {
E 25
I 25
	switch (pid = vfork()) {
E 25
	case -1:
D 14
		(void)fprintf(stderr, "find: fork: %s.\n", strerror(errno));
E 14
I 14
D 16
		error("fork", errno);
E 14
		exit(1);
E 16
I 16
D 25
		err("fork: %s", strerror(errno));
E 25
I 25
		err(1, "fork");
E 25
E 16
		/* NOTREACHED */
	case 0:
I 17
		if (fchdir(dotfd)) {
D 25
			(void)fprintf(stderr,
			    "find: chdir: %s\n", strerror(errno));
E 25
I 25
			warn("chdir");
E 25
			_exit(1);
		}
E 17
		execvp(plan->e_argv[0], plan->e_argv);
D 14
		(void)fprintf(stderr,
		    "find: %s: %s.\n", plan->e_argv[0], strerror(errno));
E 14
I 14
D 16
		error(plan->e_argv[0], errno);
E 14
		exit(1);
E 16
I 16
D 17
		err("%s: %s", plan->e_argv[0], strerror(errno));
E 16
		/* NOTREACHED */
E 17
I 17
D 25
		(void)fprintf(stderr,
		    "find: %s: %s\n", plan->e_argv[0], strerror(errno));
E 25
I 25
		warn("%s", plan->e_argv[0]);
E 25
		_exit(1);
E 17
	}
D 14
	pid = waitpid(pid, &pstat, 0);
D 4
	return(pid == -1 || pstat.w_status ? FIND_FALSE : FIND_TRUE);
E 4
I 4
	return(pid != -1 && !pstat.w_status);
E 14
I 14
	pid = waitpid(pid, &status, 0);
D 25
	return(pid != -1 && WIFEXITED(status) && !WEXITSTATUS(status));
E 25
I 25
	return (pid != -1 && WIFEXITED(status) && !WEXITSTATUS(status));
E 25
E 14
E 4
}
 
/*
 * c_exec --
 *	build three parallel arrays, one with pointers to the strings passed
 *	on the command line, one with (possibly duplicated) pointers to the
 *	argv array, and one with integer values that are lengths of the
 *	strings, but also flags meaning that the string has to be massaged.
 */
PLAN *
c_exec(argvp, isok)
	char ***argvp;
	int isok;
{
I 9
D 10
	extern int relative;
E 10
E 9
	PLAN *new;			/* node returned */
	register int cnt;
	register char **argv, **ap, *p;
I 10
D 16
	void bad_arg();
E 16
E 10

D 9
	ftsoptions |= FTS_NOCHDIR;
E 9
I 9
D 10
	if (!relative)
E 10
I 10
D 17
	if (!isrelative)
E 10
		ftsoptions |= FTS_NOCHDIR;
E 17
E 9
D 10
	output_specified = 1;
E 10
I 10
D 14
	isoutput = isstopdnx = 1;
E 14
I 14
	isoutput = 1;
E 14
E 10
    
D 15
	NEW(T_EXEC, f_exec);
E 15
I 15
D 16
	NEW(N_EXEC, f_exec);
E 16
I 16
	new = palloc(N_EXEC, f_exec);
E 16
E 15
D 18
	new->flags = isok;
E 18
I 18
	if (isok)
		new->flags = F_NEEDOK;
E 18

	for (ap = argv = *argvp;; ++ap) {
		if (!*ap)
D 16
			bad_arg(isok ? "-ok" : "-exec", "no terminating \";\"");
E 16
I 16
D 25
			err("%s: %s",
			    isok ? "-ok" : "-exec", "no terminating \";\"");
E 25
I 25
			errx(1,
			    "%s: no terminating \";\"", isok ? "-ok" : "-exec");
E 25
E 16
		if (**ap == ';')
			break;
	}

	cnt = ap - *argvp + 1;
	new->e_argv = (char **)emalloc((u_int)cnt * sizeof(char *));
	new->e_orig = (char **)emalloc((u_int)cnt * sizeof(char *));
D 13
	new->e_len = (int *)emalloc((u_int)cnt * sizeof(u_char));
E 13
I 13
	new->e_len = (int *)emalloc((u_int)cnt * sizeof(int));
E 13

	for (argv = *argvp, cnt = 0; argv < ap; ++argv, ++cnt) {
		new->e_orig[cnt] = *argv;
		for (p = *argv; *p; ++p)
			if (p[0] == '{' && p[1] == '}') {
D 13
				new->e_argv[cnt] = emalloc((u_int)1024);
				new->e_len[cnt] = 1024;
E 13
I 13
				new->e_argv[cnt] = emalloc((u_int)MAXPATHLEN);
				new->e_len[cnt] = MAXPATHLEN;
E 13
				break;
			}
		if (!*p) {
			new->e_argv[cnt] = *argv;
			new->e_len[cnt] = 0;
		}
	}
	new->e_argv[cnt] = new->e_orig[cnt] = NULL;

	*argvp = argv + 1;
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
 
/*
 * -follow functions --
 *
 *	Always true, causes symbolic links to be followed on a global
 *	basis.
 */
PLAN *
c_follow()
{
D 16
	PLAN *new;
    
E 16
	ftsoptions &= ~FTS_PHYSICAL;
	ftsoptions |= FTS_LOGICAL;

D 15
	NEW(T_FOLLOW, f_always_true);
E 15
I 15
D 16
	NEW(N_FOLLOW, f_always_true);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_FOLLOW, f_always_true));
E 25
I 25
	return (palloc(N_FOLLOW, f_always_true));
E 25
E 16
}
 
/*
 * -fstype functions --
 *
 *	True if the file is of a certain type.
 */
I 25
int
E 25
f_fstype(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 5
	extern dev_t curdev;
E 5
I 5
	static dev_t curdev;	/* need a guaranteed illegal dev value */
	static int first = 1;
E 5
	struct statfs sb;
D 4
	static short curtype;
E 4
I 4
	static short val;
I 12
	char *p, save[2];
E 12
E 4

D 18
	/* only check when we cross mount point */
E 18
I 18
	/* Only check when we cross mount point. */
E 18
D 4
	if (curdev != entry->statb.st_dev) {
		if (statfs(entry->name, &sb)) {
E 4
I 4
D 5
	if (curdev != entry->fts_statb.st_dev) {
E 5
I 5
D 20
	if (first || curdev != entry->fts_statb.st_dev) {
I 6
		curdev = entry->fts_statb.st_dev;
E 20
I 20
	if (first || curdev != entry->fts_statp->st_dev) {
		curdev = entry->fts_statp->st_dev;
E 20
I 12

		/*
		 * Statfs follows symlinks; find wants the link's file system,
		 * not where it points.
		 */
		if (entry->fts_info == FTS_SL ||
		    entry->fts_info == FTS_SLNONE) {
D 25
			if (p = rindex(entry->fts_accpath, '/'))
E 25
I 25
D 31
			if (p = strrchr(entry->fts_accpath, '/'))
E 31
I 31
			if ((p = strrchr(entry->fts_accpath, '/')) != NULL)
E 31
E 25
				++p;
			else
				p = entry->fts_accpath;
			save[0] = p[0];
			p[0] = '.';
			save[1] = p[1];
			p[1] = '\0';
			
		} else 
			p = NULL;

E 12
E 6
E 5
D 16
		if (statfs(entry->fts_accpath, &sb)) {
E 4
D 14
			(void)fprintf(stderr, "find: %s: %s.\n",
D 4
			    entry->name, strerror(errno));
E 4
I 4
			    entry->fts_accpath, strerror(errno));
E 14
I 14
			error(entry->fts_accpath, errno);
E 14
E 4
			exit(1);
		}
E 16
I 16
		if (statfs(entry->fts_accpath, &sb))
D 25
			err("%s: %s", entry->fts_accpath, strerror(errno));
E 25
I 25
			err(1, "%s", entry->fts_accpath);
E 25
E 16
I 12

		if (p) {
			p[0] = save[0];
			p[1] = save[1];
		}

E 12
I 5
		first = 0;
E 5
D 4
		curtype = sb.f_type;
E 4
I 4
D 18
		val = plan->flags == MOUNT_NONE ? sb.f_flags : sb.f_type;
E 18
I 18
D 25
		switch(plan->flags) {
E 25
I 25
D 36
		switch (plan->flags) {
E 25
		case F_MTFLAG:
			val = sb.f_flags;
			break;
		case F_MTTYPE:
			val = sb.f_type;
			break;
I 25
		default:
			abort();
E 25
		}
E 36
I 36

		/*
		 * Further tests may need both of these values, so
		 * always copy both of them.
		 */
		val = sb.f_flags;
		val = sb.f_type;
E 36
E 18
E 4
	}
D 4
	return(plan->flags == curtype);
E 4
I 4
D 18
	return(plan->flags == MOUNT_NONE ?
	    val & MNT_LOCAL : val == plan->flags);
E 18
I 18
D 36
	switch(plan->flags) {
E 36
I 36
	switch (plan->flags) {
E 36
	case F_MTFLAG:
D 25
		return(val & plan->mt_data);	
E 25
I 25
		return (val & plan->mt_data);	
E 25
	case F_MTTYPE:
D 25
		return(val == plan->mt_data);
E 25
I 25
		return (val == plan->mt_data);
	default:
		abort();
E 25
	}
E 18
E 4
}
 
PLAN *
c_fstype(arg)
	char *arg;
{
	register PLAN *new;
I 37
	struct vfsconf vfc;
E 37
    
	ftsoptions &= ~FTS_NOSTAT;
    
D 15
	NEW(T_FSTYPE, f_fstype);
E 15
I 15
D 16
	NEW(N_FSTYPE, f_fstype);
E 16
I 16
	new = palloc(N_FSTYPE, f_fstype);
I 37

	/*
	 * Check first for a filesystem name.
	 */
	if (getvfsbyname(arg, &vfc) == 0) {
		new->flags = F_MTTYPE;
		new->mt_data = vfc.vfc_typenum;
		return (new);
	}

E 37
E 16
E 15
D 25
	switch(*arg) {
E 25
I 25
	switch (*arg) {
E 25
I 4
	case 'l':
		if (!strcmp(arg, "local")) {
D 18
			new->flags = MOUNT_NONE;
E 18
I 18
			new->flags = F_MTFLAG;
			new->mt_data = MNT_LOCAL;
E 18
D 25
			return(new);
E 25
I 25
			return (new);
E 25
		}
		break;
E 4
D 37
	case 'm':
		if (!strcmp(arg, "mfs")) {
D 18
			new->flags = MOUNT_MFS;
E 18
I 18
			new->flags = F_MTTYPE;
			new->mt_data = MOUNT_MFS;
E 18
D 25
			return(new);
E 25
I 25
			return (new);
E 25
		}
		break;
	case 'n':
		if (!strcmp(arg, "nfs")) {
D 18
			new->flags = MOUNT_NFS;
E 18
I 18
			new->flags = F_MTTYPE;
			new->mt_data = MOUNT_NFS;
E 18
D 25
			return(new);
E 25
I 25
			return (new);
E 25
		}
		break;
	case 'p':
D 29
		if (!strcmp(arg, "pc")) {
E 29
I 29
		if (!strcmp(arg, "msdos")) {
E 29
D 18
			new->flags = MOUNT_PC;
E 18
I 18
			new->flags = F_MTTYPE;
D 28
			new->mt_data = MOUNT_PC;
E 28
I 28
			new->mt_data = MOUNT_MSDOS;
E 28
E 18
D 25
			return(new);
E 25
I 25
			return (new);
E 25
		}
		break;
E 37
I 18
	case 'r':
		if (!strcmp(arg, "rdonly")) {
			new->flags = F_MTFLAG;
			new->mt_data = MNT_RDONLY;
D 25
			return(new);
E 25
I 25
D 37
			return (new);
E 25
		}
		break;
E 18
	case 'u':
		if (!strcmp(arg, "ufs")) {
D 18
			new->flags = MOUNT_UFS;
E 18
I 18
			new->flags = F_MTTYPE;
			new->mt_data = MOUNT_UFS;
E 37
E 18
D 25
			return(new);
E 25
I 25
			return (new);
E 25
		}
		break;
	}
D 16
	(void)fprintf(stderr, "find: unknown file type %s.\n", arg);
	exit(1);
E 16
I 16
D 25
	err("unknown file type %s", arg);
E 25
I 25
	errx(1, "%s: unknown file type", arg);
E 25
E 16
	/* NOTREACHED */
}
 
/*
 * -group gname functions --
 *
 *	True if the file belongs to the group gname.  If gname is numeric and
 *	an equivalent of the getgrnam() function does not return a valid group
 *	name, gname is taken as a group ID.
 */
I 25
int
E 25
f_group(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	return(entry->statb.st_gid == plan->g_data ? FIND_TRUE : FIND_FALSE);
E 4
I 4
D 20
	return(entry->fts_statb.st_gid == plan->g_data);
E 20
I 20
D 25
	return(entry->fts_statp->st_gid == plan->g_data);
E 25
I 25
	return (entry->fts_statp->st_gid == plan->g_data);
E 25
E 20
E 4
}
 
PLAN *
c_group(gname)
	char *gname;
{
	PLAN *new;
	struct group *g;
	gid_t gid;
I 10
D 16
	void bad_arg();
E 16
E 10
    
	ftsoptions &= ~FTS_NOSTAT;

	g = getgrnam(gname);
	if (g == NULL) {
		gid = atoi(gname);
		if (gid == 0 && gname[0] != '0')
D 16
			bad_arg("-group", "no such group");
E 16
I 16
D 25
			err("%s: %s", "-group", "no such group");
E 25
I 25
			errx(1, "-group: %s: no such group", gname);
E 25
E 16
	} else
		gid = g->gr_gid;
    
D 15
	NEW(T_GROUP, f_group);
E 15
I 15
D 16
	NEW(N_GROUP, f_group);
E 16
I 16
	new = palloc(N_GROUP, f_group);
E 16
E 15
	new->g_data = gid;
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}

/*
 * -inum n functions --
 *
 *	True if the file has inode # n.
 */
I 25
int
E 25
f_inum(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	COMPARE(entry->statb.st_ino, plan->i_data);
E 4
I 4
D 20
	COMPARE(entry->fts_statb.st_ino, plan->i_data);
E 20
I 20
	COMPARE(entry->fts_statp->st_ino, plan->i_data);
E 20
E 4
}
 
PLAN *
c_inum(arg)
	char *arg;
{
	PLAN *new;
    
	ftsoptions &= ~FTS_NOSTAT;
    
D 15
	NEW(T_INUM, f_inum);
E 15
I 15
D 16
	NEW(N_INUM, f_inum);
E 16
I 16
	new = palloc(N_INUM, f_inum);
E 16
E 15
D 23
	new->i_data = find_parsenum(new, "-inum", arg, (char *)NULL);
E 23
I 23
D 24
	new->i_data = find_parsenum(new, "-inum", arg, 1, NULL);
E 24
I 24
	new->i_data = find_parsenum(new, "-inum", arg, NULL);
E 24
E 23
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
 
/*
 * -links n functions --
 *
 *	True if the file has n links.
 */
I 25
int
E 25
f_links(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	COMPARE(entry->statb.st_nlink, plan->l_data);
E 4
I 4
D 20
	COMPARE(entry->fts_statb.st_nlink, plan->l_data);
E 20
I 20
	COMPARE(entry->fts_statp->st_nlink, plan->l_data);
E 20
E 4
}
 
PLAN *
c_links(arg)
	char *arg;
{
	PLAN *new;
    
	ftsoptions &= ~FTS_NOSTAT;
    
D 15
	NEW(T_LINKS, f_links);
E 15
I 15
D 16
	NEW(N_LINKS, f_links);
E 16
I 16
	new = palloc(N_LINKS, f_links);
E 16
E 15
D 11
	new->l_data = find_parsenum(new, "-links", arg, (char *)NULL);
E 11
I 11
D 23
	new->l_data = (nlink_t)find_parsenum(new, "-links", arg, (char *)NULL);
E 23
I 23
D 24
	new->l_data = (nlink_t)find_parsenum(new, "-links", arg, 1, NULL);
E 24
I 24
	new->l_data = (nlink_t)find_parsenum(new, "-links", arg, NULL);
E 24
E 23
E 11
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
 
/*
 * -ls functions --
 *
 *	Always true - prints the current entry to stdout in "ls" format.
 */
D 25
/* ARGSUSED */
E 25
I 25
int
E 25
f_ls(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
I 10
D 17
	void printlong();

E 17
E 10
D 4
	printlong(entry->path, entry->accpath, &entry->statb);
	return(FIND_TRUE);
E 4
I 4
D 20
	printlong(entry->fts_path, entry->fts_accpath, &entry->fts_statb);
E 20
I 20
	printlong(entry->fts_path, entry->fts_accpath, entry->fts_statp);
E 20
D 25
	return(1);
E 25
I 25
	return (1);
E 25
E 4
}
 
PLAN *
c_ls()
{
D 16
	PLAN *new;
    
E 16
	ftsoptions &= ~FTS_NOSTAT;
D 10
	output_specified = 1;
E 10
I 10
	isoutput = 1;
E 10
    
D 15
	NEW(T_LS, f_ls);
E 15
I 15
D 16
	NEW(N_LS, f_ls);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_LS, f_ls));
E 25
I 25
	return (palloc(N_LS, f_ls));
E 25
E 16
}

/*
I 18
 * -mtime n functions --
 *
 *	True if the difference between the file modification time and the
 *	current time is n 24 hour periods.
 */
I 25
int
E 25
f_mtime(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
	extern time_t now;

D 20
	COMPARE((now - entry->fts_statb.st_mtime + SECSPERDAY - 1) /
E 20
I 20
	COMPARE((now - entry->fts_statp->st_mtime + SECSPERDAY - 1) /
E 20
	    SECSPERDAY, plan->t_data);
}
 
PLAN *
c_mtime(arg)
	char *arg;
{
	PLAN *new;

	ftsoptions &= ~FTS_NOSTAT;

	new = palloc(N_MTIME, f_mtime);
D 23
	new->t_data = find_parsenum(new, "-mtime", arg, (char *)NULL);
E 23
I 23
D 24
	new->t_data = find_parsenum(new, "-mtime", arg, 0, NULL);
E 24
I 24
	new->t_data = find_parsenum(new, "-mtime", arg, NULL);
I 26
	TIME_CORRECT(new, N_MTIME);
E 26
E 24
E 23
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}

/*
E 18
 * -name functions --
 *
 *	True if the basename of the filename being examined
 *	matches pattern using Pattern Matching Notation S3.14
 */
I 25
int
E 25
f_name(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	return(fnmatch(plan->c_data, entry->name, FNM_QUOTE) ?
	    FIND_TRUE : FIND_FALSE);
E 4
I 4
D 21
	return(fnmatch(plan->c_data, entry->fts_name, FNM_QUOTE));
E 21
I 21
D 25
	return(!fnmatch(plan->c_data, entry->fts_name, 0));
E 25
I 25
	return (!fnmatch(plan->c_data, entry->fts_name, 0));
E 25
E 21
E 4
}
 
PLAN *
c_name(pattern)
	char *pattern;
{
	PLAN *new;

D 15
	NEW(T_NAME, f_name);
E 15
I 15
D 16
	NEW(N_NAME, f_name);
E 16
I 16
	new = palloc(N_NAME, f_name);
E 16
E 15
	new->c_data = pattern;
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
 
/*
 * -newer file functions --
 *
 *	True if the current file has been modified more recently
 *	then the modification time of the file named by the pathname
 *	file.
 */
I 25
int
E 25
f_newer(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	return(entry->statb.st_mtime > plan->t_data ? FIND_TRUE : FIND_FALSE);
E 4
I 4
D 20
	return(entry->fts_statb.st_mtime > plan->t_data);
E 20
I 20
D 25
	return(entry->fts_statp->st_mtime > plan->t_data);
E 25
I 25
	return (entry->fts_statp->st_mtime > plan->t_data);
E 25
E 20
E 4
}
 
PLAN *
c_newer(filename)
	char *filename;
{
	PLAN *new;
	struct stat sb;
    
	ftsoptions &= ~FTS_NOSTAT;

D 16
	if (stat(filename, &sb)) {
D 14
		(void)fprintf(stderr, "find: %s: %s.\n",
		    filename, strerror(errno));
E 14
I 14
		error(filename, errno);
E 14
		exit(1);
	}
D 15
	NEW(T_NEWER, f_newer);
E 15
I 15
	NEW(N_NEWER, f_newer);
E 16
I 16
	if (stat(filename, &sb))
D 25
		err("%s: %s", filename, strerror(errno));
E 25
I 25
		err(1, "%s", filename);
E 25
	new = palloc(N_NEWER, f_newer);
E 16
E 15
	new->t_data = sb.st_mtime;
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
 
/*
 * -nogroup functions --
 *
 *	True if file belongs to a user ID for which the equivalent
 *	of the getgrnam() 9.2.1 [POSIX.1] function returns NULL.
 */
D 25
/* ARGSUSED */
E 25
I 25
int
E 25
f_nogroup(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	return(group_from_gid(entry->statb.st_gid, 1) ? FIND_FALSE : FIND_TRUE);
E 4
I 4
D 10
	return(group_from_gid(entry->fts_statb.st_gid, 1));
E 10
I 10
	char *group_from_gid();

D 20
	return(group_from_gid(entry->fts_statb.st_gid, 1) ? 1 : 0);
E 20
I 20
D 25
	return(group_from_gid(entry->fts_statp->st_gid, 1) ? 1 : 0);
E 25
I 25
D 30
	return (group_from_gid(entry->fts_statp->st_gid, 1) ? 1 : 0);
E 30
I 30
	return (group_from_gid(entry->fts_statp->st_gid, 1) ? 0 : 1);
E 30
E 25
E 20
E 10
E 4
}
 
PLAN *
c_nogroup()
{
D 16
	PLAN *new;
    
E 16
	ftsoptions &= ~FTS_NOSTAT;

D 15
	NEW(T_NOGROUP, f_nogroup);
E 15
I 15
D 16
	NEW(N_NOGROUP, f_nogroup);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_NOGROUP, f_nogroup));
E 25
I 25
	return (palloc(N_NOGROUP, f_nogroup));
E 25
E 16
}
 
/*
 * -nouser functions --
 *
 *	True if file belongs to a user ID for which the equivalent
 *	of the getpwuid() 9.2.2 [POSIX.1] function returns NULL.
 */
D 25
/* ARGSUSED */
E 25
I 25
int
E 25
f_nouser(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	return(user_from_uid(entry->statb.st_uid, 1) ? FIND_FALSE : FIND_TRUE);
E 4
I 4
D 10
	return(user_from_uid(entry->fts_statb.st_uid, 1));
E 10
I 10
	char *user_from_uid();

D 20
	return(user_from_uid(entry->fts_statb.st_uid, 1) ? 1 : 0);
E 20
I 20
D 25
	return(user_from_uid(entry->fts_statp->st_uid, 1) ? 1 : 0);
E 25
I 25
D 30
	return (user_from_uid(entry->fts_statp->st_uid, 1) ? 1 : 0);
E 30
I 30
	return (user_from_uid(entry->fts_statp->st_uid, 1) ? 0 : 1);
E 30
E 25
E 20
E 10
E 4
}
 
PLAN *
c_nouser()
{
D 16
	PLAN *new;
    
E 16
	ftsoptions &= ~FTS_NOSTAT;

D 15
	NEW(T_NOUSER, f_nouser);
E 15
I 15
D 16
	NEW(N_NOUSER, f_nouser);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_NOUSER, f_nouser));
E 25
I 25
	return (palloc(N_NOUSER, f_nouser));
E 25
E 16
}
 
/*
I 18
 * -path functions --
 *
 *	True if the path of the filename being examined
 *	matches pattern using Pattern Matching Notation S3.14
 */
I 25
int
E 25
f_path(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 21
	return(fnmatch(plan->c_data, entry->fts_path, FNM_QUOTE));
E 21
I 21
D 25
	return(!fnmatch(plan->c_data, entry->fts_path, 0));
E 25
I 25
	return (!fnmatch(plan->c_data, entry->fts_path, 0));
E 25
E 21
}
 
PLAN *
c_path(pattern)
	char *pattern;
{
	PLAN *new;

	new = palloc(N_NAME, f_path);
	new->c_data = pattern;
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
 
/*
E 18
 * -perm functions --
 *
 *	The mode argument is used to represent file mode bits.  If it starts
 *	with a leading digit, it's treated as an octal mode, otherwise as a
 *	symbolic mode.
 */
I 25
int
E 25
f_perm(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
	mode_t mode;

D 4
	mode = entry->statb.st_mode &
E 4
I 4
D 20
	mode = entry->fts_statb.st_mode &
E 20
I 20
	mode = entry->fts_statp->st_mode &
E 20
E 4
	    (S_ISUID|S_ISGID|S_ISTXT|S_IRWXU|S_IRWXG|S_IRWXO);
D 18
	if (plan->flags)
E 18
I 18
	if (plan->flags == F_ATLEAST)
E 18
D 25
		return((plan->m_data | mode) == mode);
E 25
I 25
		return ((plan->m_data | mode) == mode);
E 25
	else
D 25
		return(mode == plan->m_data);
E 25
I 25
		return (mode == plan->m_data);
E 25
	/* NOTREACHED */
}
 
PLAN *
c_perm(perm)
	char *perm;
{
	PLAN *new;
I 7
D 8
	mode_t *set;
E 8
I 8
D 14
	mode_t *set, *setmode();
E 14
I 14
	mode_t *set;
E 14
I 10
D 16
	void bad_arg();
E 16
E 10
E 8
E 7

	ftsoptions &= ~FTS_NOSTAT;

D 15
	NEW(T_PERM, f_perm);
E 15
I 15
D 16
	NEW(N_PERM, f_perm);
E 16
I 16
	new = palloc(N_PERM, f_perm);
E 16
E 15

	if (*perm == '-') {
D 18
		new->flags = 1;
E 18
I 18
		new->flags = F_ATLEAST;
E 18
		++perm;
	}

D 7
	if (setmode(perm))
E 7
I 7
	if ((set = setmode(perm)) == NULL)
E 7
D 16
		bad_arg("-perm", "illegal mode string");
E 16
I 16
D 25
		err("%s: %s", "-perm", "illegal mode string");
E 25
I 25
		err(1, "-perm: %s: illegal mode string", perm);
E 25
E 16

D 7
	new->m_data = getmode(0);
E 7
I 7
	new->m_data = getmode(set, 0);
E 7
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
 
/*
 * -print functions --
 *
 *	Always true, causes the current pathame to be written to
 *	standard output.
 */
D 25
/* ARGSUSED */
E 25
I 25
int
E 25
f_print(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	(void)printf("%s\n", entry->path);
	return(FIND_TRUE);
E 4
I 4
	(void)printf("%s\n", entry->fts_path);
D 25
	return(1);
E 25
I 25
	return (1);
E 25
E 4
}
 
PLAN *
c_print()
{
D 16
	PLAN *new;
    
E 16
D 10
	output_specified = 1;
E 10
I 10
	isoutput = 1;
E 10

D 15
	NEW(T_PRINT, f_print);
E 15
I 15
D 16
	NEW(N_PRINT, f_print);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_PRINT, f_print));
E 25
I 25
	return (palloc(N_PRINT, f_print));
E 25
E 16
}
 
/*
 * -prune functions --
 *
 *	Prune a portion of the hierarchy.
 */
D 25
/* ARGSUSED */
E 25
I 25
int
E 25
f_prune(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
	extern FTS *tree;

D 10
	if (ftsset(tree, entry, FTS_SKIP)) {
E 10
I 10
D 16
	if (fts_set(tree, entry, FTS_SKIP)) {
E 10
D 14
		(void)fprintf(stderr,
D 4
		    "find: %s: %s.\n", entry->path, strerror(errno));
E 4
I 4
		    "find: %s: %s.\n", entry->fts_path, strerror(errno));
E 14
I 14
		error(entry->fts_path, errno);
E 14
E 4
		exit(1);
	}
E 16
I 16
	if (fts_set(tree, entry, FTS_SKIP))
D 25
		err("%s: %s", entry->fts_path, strerror(errno));
E 16
D 4
	return(FIND_TRUE);
E 4
I 4
	return(1);
E 25
I 25
		err(1, "%s", entry->fts_path);
	return (1);
E 25
E 4
}
 
PLAN *
c_prune()
{
D 16
	PLAN *new;

D 15
	NEW(T_PRUNE, f_prune);
E 15
I 15
	NEW(N_PRUNE, f_prune);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_PRUNE, f_prune));
E 25
I 25
	return (palloc(N_PRUNE, f_prune));
E 25
E 16
}
 
/*
 * -size n[c] functions --
 *
 *	True if the file size in bytes, divided by an implementation defined
 *	value and rounded up to the next integer, is n.  If n is followed by
 *	a c, the size is in bytes.
 */
#define	FIND_SIZE	512
static int divsize = 1;

I 25
int
E 25
f_size(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
	off_t size;

D 4
	size = divsize ?
	    (entry->statb.st_size + FIND_SIZE - 1) / FIND_SIZE :
	    entry->statb.st_size;
E 4
I 4
D 20
	size = divsize ? (entry->fts_statb.st_size + FIND_SIZE - 1) /
	    FIND_SIZE : entry->fts_statb.st_size;
E 20
I 20
	size = divsize ? (entry->fts_statp->st_size + FIND_SIZE - 1) /
	    FIND_SIZE : entry->fts_statp->st_size;
E 20
E 4
	COMPARE(size, plan->o_data);
}
 
PLAN *
c_size(arg)
	char *arg;
{
	PLAN *new;
	char endch;
    
	ftsoptions &= ~FTS_NOSTAT;

D 15
	NEW(T_SIZE, f_size);
E 15
I 15
D 16
	NEW(N_SIZE, f_size);
E 16
I 16
	new = palloc(N_SIZE, f_size);
E 16
E 15
D 23
	new->o_data = find_parsenum(new, "-size", arg, &endch);
E 23
I 23
	endch = 'c';
D 24
	new->o_data = find_parsenum(new, "-size", arg, 1, &endch);
E 24
I 24
	new->o_data = find_parsenum(new, "-size", arg, &endch);
E 24
E 23
	if (endch == 'c')
		divsize = 0;
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
 
/*
 * -type c functions --
 *
D 33
 *	True if the type of the file is c, where c is b, c, d, p, or f for
 *	block special file, character special file, directory, FIFO, or
 *	regular file, respectively.
E 33
I 33
 *	True if the type of the file is c, where c is b, c, d, p, f or w
 *	for block special file, character special file, directory, FIFO,
 *	regular file or whiteout respectively.
E 33
 */
I 25
int
E 25
f_type(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	return(entry->statb.st_mode & plan->m_data ? FIND_TRUE : FIND_FALSE);
E 4
I 4
D 7
	return(entry->fts_statb.st_mode & plan->m_data);
E 7
I 7
D 20
	return((entry->fts_statb.st_mode & S_IFMT) == plan->m_data);
E 20
I 20
D 25
	return((entry->fts_statp->st_mode & S_IFMT) == plan->m_data);
E 25
I 25
	return ((entry->fts_statp->st_mode & S_IFMT) == plan->m_data);
E 25
E 20
E 7
E 4
}
 
PLAN *
c_type(typestring)
	char *typestring;
{
	PLAN *new;
	mode_t  mask;
I 10
D 16
	void bad_arg();
E 16
E 10
    
	ftsoptions &= ~FTS_NOSTAT;

	switch (typestring[0]) {
	case 'b':
		mask = S_IFBLK;
		break;
	case 'c':
		mask = S_IFCHR;
		break;
	case 'd':
		mask = S_IFDIR;
		break;
	case 'f':
		mask = S_IFREG;
		break;
	case 'l':
		mask = S_IFLNK;
		break;
	case 'p':
		mask = S_IFIFO;
		break;
	case 's':
		mask = S_IFSOCK;
I 33
		break;
I 34
#ifdef FTS_WHITEOUT
E 34
	case 'w':
		mask = S_IFWHT;
		ftsoptions |= FTS_WHITEOUT;
E 33
		break;
I 34
#endif /* FTS_WHITEOUT */
E 34
	default:
D 16
		bad_arg("-type", "unknown type");
E 16
I 16
D 25
		err("%s: %s", "-type", "unknown type");
E 25
I 25
		errx(1, "-type: %s: unknown type", typestring);
E 25
E 16
	}
    
D 15
	NEW(T_TYPE, f_type);
E 15
I 15
D 16
	NEW(N_TYPE, f_type);
E 16
I 16
	new = palloc(N_TYPE, f_type);
E 16
E 15
	new->m_data = mask;
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
 
/*
 * -user uname functions --
 *
 *	True if the file belongs to the user uname.  If uname is numeric and
 *	an equivalent of the getpwnam() S9.2.2 [POSIX.1] function does not
 *	return a valid user name, uname is taken as a user ID.
 */
I 25
int
E 25
f_user(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
D 4
	return(entry->statb.st_uid == plan->u_data ? FIND_TRUE : FIND_FALSE);
E 4
I 4
D 20
	return(entry->fts_statb.st_uid == plan->u_data);
E 20
I 20
D 25
	return(entry->fts_statp->st_uid == plan->u_data);
E 25
I 25
	return (entry->fts_statp->st_uid == plan->u_data);
E 25
E 20
E 4
}
 
PLAN *
c_user(username)
	char *username;
{
	PLAN *new;
	struct passwd *p;
	uid_t uid;
I 10
D 16
	void bad_arg();
E 16
E 10
    
	ftsoptions &= ~FTS_NOSTAT;

	p = getpwnam(username);
	if (p == NULL) {
		uid = atoi(username);
		if (uid == 0 && username[0] != '0')
D 16
			bad_arg("-user", "no such user");
E 16
I 16
D 25
			err("%s: %s", "-user", "no such user");
E 25
I 25
			errx(1, "-user: %s: no such user", username);
E 25
E 16
	} else
		uid = p->pw_uid;

D 15
	NEW(T_USER, f_user);
E 15
I 15
D 16
	NEW(N_USER, f_user);
E 16
I 16
	new = palloc(N_USER, f_user);
E 16
E 15
	new->u_data = uid;
D 25
	return(new);
E 25
I 25
	return (new);
E 25
}
 
/*
 * -xdev functions --
 *
 *	Always true, causes find not to decend past directories that have a
 *	different device ID (st_dev, see stat() S5.6.2 [POSIX.1])
D 5
 *
 *	Note: this checking is done in find_execute().
E 5
 */
PLAN *
c_xdev()
{
D 5
	extern int xdev;
E 5
D 16
	PLAN *new;
    
E 16
D 5
	xdev = 1;
E 5
D 10
	ftsoptions &= ~FTS_NOSTAT;
E 10
I 5
	ftsoptions |= FTS_XDEV;
E 5

D 15
	NEW(T_XDEV, f_always_true);
E 15
I 15
D 16
	NEW(N_XDEV, f_always_true);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_XDEV, f_always_true));
E 25
I 25
	return (palloc(N_XDEV, f_always_true));
E 25
E 16
}

/*
 * ( expression ) functions --
 *
 *	True if expression is true.
 */
I 25
int
E 25
f_expr(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
	register PLAN *p;
	register int state;

	for (p = plan->p_data[0];
	    p && (state = (p->eval)(p, entry)); p = p->next);
D 25
	return(state);
E 25
I 25
	return (state);
E 25
}
 
/*
D 15
 * T_OPENPAREN and T_CLOSEPAREN nodes are temporary place markers.  They are
E 15
I 15
 * N_OPENPAREN and N_CLOSEPAREN nodes are temporary place markers.  They are
E 15
 * eliminated during phase 2 of find_formplan() --- the '(' node is converted
D 15
 * to a T_EXPR node containing the expression and the ')' node is discarded.
E 15
I 15
 * to a N_EXPR node containing the expression and the ')' node is discarded.
E 15
 */
PLAN *
c_openparen()
{
D 16
	PLAN *new;

D 15
	NEW(T_OPENPAREN, (int (*)())-1);
E 15
I 15
	NEW(N_OPENPAREN, (int (*)())-1);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_OPENPAREN, (int (*)())-1));
E 25
I 25
	return (palloc(N_OPENPAREN, (int (*)())-1));
E 25
E 16
}
 
PLAN *
c_closeparen()
{
D 16
	PLAN *new;

D 15
	NEW(T_CLOSEPAREN, (int (*)())-1);
E 15
I 15
	NEW(N_CLOSEPAREN, (int (*)())-1);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_CLOSEPAREN, (int (*)())-1));
E 25
I 25
	return (palloc(N_CLOSEPAREN, (int (*)())-1));
E 25
E 16
}
 
D 18
/*
 * -mtime n functions --
 *
 *	True if the difference between the file modification time and the
 *	current time is n 24 hour periods.
 */
f_mtime(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
	extern time_t now;

D 4
	COMPARE((now - entry->statb.st_mtime + SECSPERDAY - 1) / SECSPERDAY,
	    plan->t_data);
E 4
I 4
	COMPARE((now - entry->fts_statb.st_mtime + SECSPERDAY - 1) /
	    SECSPERDAY, plan->t_data);
E 4
}
 
PLAN *
c_mtime(arg)
	char *arg;
{
	PLAN *new;

	ftsoptions &= ~FTS_NOSTAT;

D 15
	NEW(T_MTIME, f_mtime);
E 15
I 15
D 16
	NEW(N_MTIME, f_mtime);
E 16
I 16
	new = palloc(N_MTIME, f_mtime);
E 16
E 15
	new->t_data = find_parsenum(new, "-mtime", arg, (char *)NULL);
	return(new);
}

E 18
/*
 * ! expression functions --
 *
 *	Negation of a primary; the unary NOT operator.
 */
I 25
int
E 25
f_not(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
	register PLAN *p;
	register int state;

	for (p = plan->p_data[0];
	    p && (state = (p->eval)(p, entry)); p = p->next);
D 25
	return(!state);
E 25
I 25
	return (!state);
E 25
}
 
PLAN *
c_not()
{
D 16
	PLAN *new;

D 15
	NEW(T_NOT, f_not);
E 15
I 15
	NEW(N_NOT, f_not);
E 15
	return(new);
E 16
I 16
D 25
	return(palloc(N_NOT, f_not));
E 25
I 25
	return (palloc(N_NOT, f_not));
E 25
E 16
}
 
/*
 * expression -o expression functions --
 *
 *	Alternation of primaries; the OR operator.  The second expression is
 * not evaluated if the first expression is true.
 */
I 25
int
E 25
f_or(plan, entry)
	PLAN *plan;
	FTSENT *entry;
{
	register PLAN *p;
	register int state;

	for (p = plan->p_data[0];
	    p && (state = (p->eval)(p, entry)); p = p->next);

	if (state)
D 4
		return(FIND_TRUE);
E 4
I 4
D 25
		return(1);
E 25
I 25
		return (1);
E 25
E 4

	for (p = plan->p_data[1];
	    p && (state = (p->eval)(p, entry)); p = p->next);
D 25
	return(state);
E 25
I 25
	return (state);
E 25
}

PLAN *
c_or()
{
I 16
D 25
	return(palloc(N_OR, f_or));
E 25
I 25
	return (palloc(N_OR, f_or));
E 25
}

static PLAN *
palloc(t, f)
	enum ntype t;
D 25
	int (*f)();
E 25
I 25
	int (*f) __P((PLAN *, FTSENT *));
E 25
{
E 16
	PLAN *new;

D 15
	NEW(T_OR, f_or);
E 15
I 15
D 16
	NEW(N_OR, f_or);
E 15
	return(new);
E 16
I 16
D 32
	if (new = malloc(sizeof(PLAN))) {
		new->type = t;
		new->eval = f;
		new->flags = 0;
		new->next = NULL;
D 25
		return(new);
E 25
I 25
		return (new);
E 25
	}
D 25
	err("%s", strerror(errno));
E 25
I 25
	err(1, NULL);
E 25
	/* NOTREACHED */
E 32
I 32
	if ((new = malloc(sizeof(PLAN))) == NULL)
		err(1, NULL);
	new->type = t;
	new->eval = f;
	new->flags = 0;
	new->next = NULL;
	return (new);
E 32
E 16
}
E 1
