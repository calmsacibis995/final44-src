h17586
s 00002/00002/00463
d D 8.1 93/06/06 11:41:49 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00000/00456
d D 5.6 93/05/22 02:34:12 pendry 6 5
c use strerror
e
s 00010/00001/00446
d D 5.5 92/05/31 10:42:29 pendry 5 4
c code refresh
e
s 00001/00001/00446
d D 5.4 92/02/09 08:49:18 pendry 4 3
c merge in new release
e
s 00003/00002/00444
d D 5.3 91/05/12 15:56:37 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00445
d D 5.2 91/03/17 13:34:25 pendry 2 1
c from amd5.3 alpha11
e
s 00458/00000/00000
d D 5.1 91/03/17 12:05:24 pendry 1 0
c date and time created 91/03/17 12:05:24 by pendry
e
u
U
t
T
I 1
/*
D 3
 * $Id: xutil.c,v 5.2.1.4 91/03/17 17:42:22 jsp Alpha $
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 7
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
D 2
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: xutil.c,v 5.2.1.5 91/05/07 22:18:43 jsp Alpha $
E 4
I 4
D 5
 * $Id: xutil.c,v 5.2.2.1 1992/02/09 15:09:13 jsp beta $
E 5
I 5
 * $Id: xutil.c,v 5.2.2.3 1992/03/07 10:36:09 jsp Exp $
E 5
E 4
 *
E 3
 */

#include "config.h"
#ifdef HAS_SYSLOG
#include <syslog.h>
#endif /* HAS_SYSLOG */
I 6
#ifdef HAS_STRERROR
#include <string.h>
#endif
E 6

FILE *logfp = stderr;		/* Log errors to stderr initially */
#ifdef HAS_SYSLOG
int syslogging;
#endif /* HAS_SYSLOG */
int xlog_level = XLOG_ALL & ~XLOG_MAP & ~XLOG_STATS;
int xlog_level_init = ~0;

/*
 * List of log options
 */
struct opt_tab xlog_opt[] = {
	{ "all", XLOG_ALL },		/* All messages */
#ifdef DEBUG
	{ "debug", XLOG_DEBUG },	/* Debug messages */
#endif /* DEBUG */
	{ "error", XLOG_ERROR },	/* Non-fatal system errors */
	{ "fatal", XLOG_FATAL },	/* Fatal errors */
	{ "info", XLOG_INFO },		/* Information */
	{ "map", XLOG_MAP },		/* Map errors */
	{ "stats", XLOG_STATS },	/* Additional statistical information */
	{ "user", XLOG_USER },		/* Non-fatal user errors */
	{ "warn", XLOG_WARNING },	/* Warnings */
	{ "warning", XLOG_WARNING },	/* Warnings */
	{ 0, 0 }
};

voidp xmalloc(len)
int len;
{
	voidp p;
	int retries = 600;

I 5
	/*
	 * Avoid malloc's which return NULL for malloc(0)
	 */
	if (len == 0)
		len = 1;

E 5
	do {
		p = (voidp) malloc((unsigned) len);
		if (p) {
#if defined(DEBUG) && defined(DEBUG_MEM)
			Debug(D_MEM) plog(XLOG_DEBUG, "Allocated size %d; block %#x", len, p);
#endif /* defined(DEBUG) && defined(DEBUG_MEM) */
			return p;
		}
		if (retries > 0) {
			plog(XLOG_ERROR, "Retrying memory allocation");
			sleep(1);
		}
	} while (--retries);

	plog(XLOG_FATAL, "Out of memory");
	going_down(1);

	abort();

	return 0;
}

voidp xrealloc(ptr, len)
voidp ptr;
int len;
{
#if defined(DEBUG) && defined(DEBUG_MEM)
	Debug(D_MEM) plog(XLOG_DEBUG, "Reallocated size %d; block %#x", len, ptr);
#endif /* defined(DEBUG) && defined(DEBUG_MEM) */
I 5

	if (len == 0)
		len = 1;
E 5

	if (ptr)
		ptr = (voidp) realloc(ptr, (unsigned) len);
	else
		ptr = (voidp) xmalloc((unsigned) len);

	if (!ptr) {
		plog(XLOG_FATAL, "Out of memory in realloc");
		going_down(1);
		abort();
	}
	return ptr;
}

#if defined(DEBUG) && defined(DEBUG_MEM)
xfree(f, l, p)
char *f;
int l;
voidp p;
{
	Debug(D_MEM) plog(XLOG_DEBUG, "Free in %s:%d: block %#x", f, l, p);
#undef free
	free(p);
}
#endif /* defined(DEBUG) && defined(DEBUG_MEM) */
#ifdef DEBUG_MEM
static int mem_bytes;
static int orig_mem_bytes;
static void checkup_mem(P_void)
{
extern struct mallinfo __mallinfo;
	if (mem_bytes != __mallinfo.uordbytes) {
		if (orig_mem_bytes == 0)
			mem_bytes = orig_mem_bytes = __mallinfo.uordbytes;
		else {
			fprintf(logfp, "%s[%d]: ", progname, mypid);
			if (mem_bytes < __mallinfo.uordbytes) {
				fprintf(logfp, "ALLOC: %d bytes",
					__mallinfo.uordbytes - mem_bytes);
			} else {
				fprintf(logfp, "FREE: %d bytes",
					mem_bytes - __mallinfo.uordbytes);
			}
			mem_bytes = __mallinfo.uordbytes;
			fprintf(logfp, ", making %d missing\n",
				mem_bytes - orig_mem_bytes);
		}
	}
	malloc_verify();
}
#endif /* DEBUG_MEM */

/*
 * Take a log format string and expand occurences of %m
 * with the current error code take from errno.
 */
INLINE
static void expand_error(f, e)
char *f;
char *e;
{
I 6
#ifndef HAS_STRERROR
E 6
	extern int sys_nerr;
	extern char *sys_errlist[];
I 6
#endif
E 6
	char *p;
	int error = errno;

	for (p = f; *e = *p; e++, p++) {
		if (p[0] == '%' && p[1] == 'm') {
			char *errstr;
I 6
#ifdef HAS_STRERROR
			errstr = strerror(error);
#else
E 6
			if (error < 0 || error >= sys_nerr)
				errstr = 0;
			else
				errstr = sys_errlist[error];
I 6
#endif
E 6
			if (errstr)
				strcpy(e, errstr);
			else
				sprintf(e, "Error %d", error);
			e += strlen(e) - 1;
			p++;
		}
	}
}

/*
 * Output the time of day and hostname to the logfile
 */
static void show_time_host_and_name(lvl)
int lvl;
{
static time_t last_t = 0;
static char *last_ctime = 0;
	time_t t = clocktime();
	char *sev;
	extern char *ctime();

#if defined(DEBUG) && defined(PARANOID)
extern char **gargv;
#endif /* defined(DEBUG) && defined(PARANOID) */

	if (t != last_t) {
		last_ctime = ctime(&t);
		last_t = t;
	}

	switch (lvl) {
	case XLOG_FATAL:	sev = "fatal:"; break;
	case XLOG_ERROR: 	sev = "error:"; break;
	case XLOG_USER:		sev = "user: "; break;
	case XLOG_WARNING:	sev = "warn: "; break;
	case XLOG_INFO:		sev = "info: "; break;
	case XLOG_DEBUG:	sev = "debug:"; break;
	case XLOG_MAP:		sev = "map:  "; break;
	case XLOG_STATS:	sev = "stats:"; break;
	default:		sev = "hmm:  "; break;
	}
	fprintf(logfp, "%15.15s %s %s[%d]/%s ",
		last_ctime+4, hostname,
#if defined(DEBUG) && defined(PARANOID)
		gargv[0],
#else
		progname,
#endif /* defined(DEBUG) && defined(PARANOID) */
		mypid,
		sev);
}

#ifdef DEBUG
/*VARARGS1*/
void dplog(fmt, j,s,_,p,e,n,d,r,y)
char *fmt;
char *j, *s, *_, *p, *e, *n, *d, *r, *y;
{
	plog(XLOG_DEBUG, fmt, j,s,_,p,e,n,d,r,y);
}

#endif /* DEBUG */
/*VARARGS1*/
void plog(lvl, fmt, j,s,_,p,e,n,d,r,y)
int lvl;
char *fmt;
char *j, *s, *_, *p, *e, *n, *d, *r, *y;
{
	char msg[1024];
	char efmt[1024];
	char *ptr = msg;

	if (!(xlog_level & lvl))
		return;

#ifdef DEBUG_MEM
	checkup_mem();
#endif /* DEBUG_MEM */

	expand_error(fmt, efmt);
	sprintf(ptr, efmt, j,s,_,p,e,n,d,r,y);
	ptr += strlen(ptr);
	if (ptr[-1] == '\n')
		*--ptr  = '\0';
#ifdef HAS_SYSLOG
	if (syslogging) {
		switch(lvl) {	/* from mike <mcooper@usc.edu> */
		case XLOG_FATAL:	lvl = LOG_CRIT; break;
		case XLOG_ERROR: 	lvl = LOG_ERR; break;
		case XLOG_USER:		lvl = LOG_WARNING; break;
		case XLOG_WARNING:	lvl = LOG_WARNING; break;
		case XLOG_INFO:		lvl = LOG_INFO; break;
		case XLOG_DEBUG:	lvl = LOG_DEBUG; break;
		case XLOG_MAP:		lvl = LOG_DEBUG; break;
		case XLOG_STATS:	lvl = LOG_INFO; break;
		default:		lvl = LOG_ERR; break;
		}
		syslog(lvl, "%s", msg);
		return;
	}
#endif /* HAS_SYSLOG */

	*ptr++ = '\n';
	*ptr = '\0';

	/*
	 * Mimic syslog header
	 */
	show_time_host_and_name(lvl);
	fwrite(msg, ptr - msg, 1, logfp);
	fflush(logfp);
}

void show_opts P((int ch, struct opt_tab *opts));
void show_opts(ch, opts)
int ch;
struct opt_tab *opts;
{
	/*
	 * Display current debug options
	 */
	int i;
	int s = '{';
	fprintf(stderr, "\t[-%c {no}", ch);
	for (i = 0; opts[i].opt; i++) {
		fprintf(stderr, "%c%s", s, opts[i].opt);
		s = ',';
	}
	fputs("}]\n", stderr);
}

int cmdoption P((char *s, struct opt_tab *optb, int *flags));
int cmdoption(s, optb, flags)
char *s;
struct opt_tab *optb;
int *flags;
{
	char *p = s;
	int errs = 0;

	while (p && *p) {
		int neg;
		char *opt;
		struct opt_tab *dp, *dpn = 0;

		s = p;
		p = strchr(p, ',');
		if (p)
			*p = '\0';

		if (s[0] == 'n' && s[1] == 'o') {
			opt = s + 2;
			neg = 1;
		} else {
			opt = s;
			neg = 0;
		}

		/*
		 * Scan the array of debug options to find the
		 * corresponding flag value.  If it is found
		 * then set (or clear) the flag (depending on
		 * whether the option was prefixed with "no").
		 */
		for (dp = optb; dp->opt; dp++) {
			if (strcmp(opt, dp->opt) == 0)
				break;
			if (opt != s && !dpn && strcmp(s, dp->opt) == 0)
				dpn = dp;
		}

		if (dp->opt || dpn) {
			if (!dp->opt) {
				dp = dpn;
				neg = !neg;
			}
			if (neg)
				*flags &= ~dp->flag;
			else
				*flags |= dp->flag;
		} else {
			/*
			 * This will log to stderr when parsing the command line
			 * since any -l option will not yet have taken effect.
			 */
			plog(XLOG_USER, "option \"%s\" not recognised", s);
			errs++;
		}
		/*
		 * Put the comma back
		 */
		if (p)
			*p++ = ',';
	}

	return errs;
}

/*
 * Switch on/off logging options
 */
int switch_option(opt)
char *opt;
{
	int xl = xlog_level;
	int rc = cmdoption(opt, xlog_opt, &xl);
	if (rc) {
		rc = EINVAL;
	} else {
		/*
		 * Keep track of initial log level, and
		 * don't allow options to be turned off.
		 */
		if (xlog_level_init == ~0)
			xlog_level_init = xl;
		else
			xl |= xlog_level_init;
		xlog_level = xl;
	}
	return rc;
}

/*
 * Change current logfile
 */
int switch_to_logfile P((char *logfile));
int switch_to_logfile(logfile)
char *logfile;
{
	FILE *new_logfp = stderr;

	if (logfile) {
#ifdef HAS_SYSLOG
		syslogging = 0;
#endif /* HAS_SYSLOG */
		if (strcmp(logfile, "/dev/stderr") == 0)
			new_logfp = stderr;
		else if (strcmp(logfile, "syslog") == 0) {
#ifdef HAS_SYSLOG
			syslogging = 1;
			new_logfp = stderr;
#if defined(LOG_CONS) && defined(LOG_NOWAIT)
			openlog(progname, LOG_PID|LOG_CONS|LOG_NOWAIT,
				LOG_DAEMON);
#else
			/* 4.2 compat mode - XXX */
			openlog(progname, LOG_PID);
#endif /* LOG_CONS && LOG_NOWAIT */
#else
			plog(XLOG_WARNING, "syslog option not supported, logging unchanged");
#endif /* HAS_SYSLOG */
		} else {
			(void) umask(orig_umask);
			new_logfp = fopen(logfile, "a");
			umask(0);
		}
	}

	/*
	 * If we couldn't open a new file, then continue using the old.
	 */
	if (!new_logfp && logfile) {
		plog(XLOG_USER, "%s: Can't open logfile: %m", logfile);
		return 1;
	}
	/*
	 * Close the previous file
	 */
	if (logfp && logfp != stderr)
		(void) fclose(logfp);
	logfp = new_logfp;
	return 0;
}

time_t clock_valid = 0;
time_t xclock_valid = 0;
#ifndef clocktime
time_t clocktime(P_void)
{
	time_t now = time(&clock_valid);
	if (xclock_valid > now) {
		/*
		 * Someone set the clock back!
		 */
		plog(XLOG_WARNING, "system clock reset");
		reschedule_timeouts(now, xclock_valid);
	}
	return xclock_valid = now;
}
#endif /* clocktime */
E 1
