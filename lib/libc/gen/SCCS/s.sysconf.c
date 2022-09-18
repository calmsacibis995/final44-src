h23270
s 00002/00002/00160
d D 8.2 94/03/20 14:47:48 bostic 5 4
c sysconf(_SC_OPEN_MAX) and sysconf(_SC_CHILD_MAX) are still not useable
c as all they do is return -1  ((long)RLIM_INFINITY).  I've changed my version
c to use rlim_cur rather than rlim_max as that is what programs that use this
c expect to get
c From: Mark Davies <mark@Comp.VUW.AC.NZ>
e
s 00002/00002/00160
d D 8.1 93/06/04 12:05:40 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00006/00157
d D 5.3 93/05/24 15:36:12 bostic 3 2
c use getrlimit to get _SC_OPEN_MAX and RLIMIT_NPROC
c per-process limits are resources, not sysctl(3) variables
e
s 00049/00016/00114
d D 5.2 93/05/24 10:58:06 bostic 2 1
c KERN_MAXPROC -> KERN_MAXUPROC for _SC_CHILD_MAX; POSIX 1003.1 requires
c that CLK_TCK be returned for _SC_CLK_TCK; KERN_MAXFILES -> KERN_MAXUFILES for
c _SC_OPEN_MAX; add USER_STREAM_MAX for _SC_STREAM_MAX, USER_TZNAME_MAX for
c _SC_TZNAME_MAX; add _SC_2_CHAR_TERM, _SC_2_UPE; fix binary returns to return
c -1 on "no".
e
s 00129/00000/00000
d D 5.1 93/05/04 12:10:12 bostic 1 0
c date and time created 93/05/04 12:10:12 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Sean Eric Fagan of Cygnus Support.
 *
 * %sccs.include.redist.c%
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* LIBC_SCCS and not lint */

#include <sys/param.h>
#include <sys/sysctl.h>
I 3
#include <sys/time.h>
#include <sys/resource.h>
E 3

#include <errno.h>
#include <unistd.h>

I 2
/*
 * sysconf --
 *	get configurable system variables.
 *
 * XXX
 * POSIX 1003.1 (ISO/IEC 9945-1, 4.8.1.3) states that the variable values
 * not change during the lifetime of the calling process.  This would seem
 * to require that any change to system limits kill all running processes.
 * A workaround might be to cache the values when they are first retrieved
 * and then simply return the cached value on subsequent calls.  This is
 * less useful than returning up-to-date values, however.
 */
E 2
long
sysconf(name)
	int name;
{
	struct clockinfo clk;
I 3
	struct rlimit rl;
E 3
	size_t len;
	int mib[2], value;

I 2
	len = sizeof(value);

E 2
	switch (name) {
I 2
/* 1003.1 */
E 2
	case _SC_ARG_MAX:
		mib[0] = CTL_KERN;
		mib[1] = KERN_ARGMAX;
		break;
	case _SC_CHILD_MAX:
D 3
		mib[0] = CTL_KERN;
D 2
		mib[1] = KERN_MAXPROC;
E 2
I 2
		mib[1] = KERN_MAXUPROC;
E 2
		break;
E 3
I 3
D 5
		return (getrlimit(RLIMIT_NPROC, &rl) ? -1 : rl.rlim_max);
E 5
I 5
		return (getrlimit(RLIMIT_NPROC, &rl) ? -1 : rl.rlim_cur);
E 5
E 3
	case _SC_CLK_TCK:
I 2
		return (CLK_TCK);
	case _SC_JOB_CONTROL:
E 2
		mib[0] = CTL_KERN;
D 2
		mib[1] = KERN_CLOCKRATE;
		len = sizeof(struct clockinfo);
		return (sysctl(mib, 2,
		    &clk, &len, NULL, 0) == -1 ? -1 : clk.hz);
E 2
I 2
		mib[1] = KERN_JOB_CONTROL;
		goto yesno;
E 2
	case _SC_NGROUPS_MAX:
		mib[0] = CTL_KERN;
		mib[1] = KERN_NGROUPS;
		break;
	case _SC_OPEN_MAX:
D 3
		mib[0] = CTL_KERN;
D 2
		mib[1] = KERN_MAXFILES;
E 2
I 2
		mib[1] = KERN_MAXUFILES;
E 2
		break;
E 3
I 3
D 5
		return (getrlimit(RLIMIT_NOFILE, &rl) ? -1 : rl.rlim_max);
E 5
I 5
		return (getrlimit(RLIMIT_NOFILE, &rl) ? -1 : rl.rlim_cur);
E 5
E 3
D 2
	case _SC_JOB_CONTROL:
		mib[0] = CTL_KERN;
		mib[1] = KERN_JOB_CONTROL;
E 2
I 2
	case _SC_STREAM_MAX:
		mib[0] = CTL_USER;
		mib[1] = USER_STREAM_MAX;
E 2
		break;
I 2
	case _SC_TZNAME_MAX:
		mib[0] = CTL_USER;
		mib[1] = USER_TZNAME_MAX;
		break;
E 2
	case _SC_SAVED_IDS:
		mib[0] = CTL_KERN;
		mib[1] = KERN_SAVED_IDS;
D 2
		break;
E 2
I 2
		goto yesno;
E 2
	case _SC_VERSION:
		mib[0] = CTL_KERN;
		mib[1] = KERN_POSIX1;
		break;
I 2

/* 1003.2 */
E 2
	case _SC_BC_BASE_MAX:
		mib[0] = CTL_USER;
		mib[1] = USER_BC_BASE_MAX;
		break;
	case _SC_BC_DIM_MAX:
		mib[0] = CTL_USER;
		mib[1] = USER_BC_DIM_MAX;
		break;
	case _SC_BC_SCALE_MAX:
		mib[0] = CTL_USER;
		mib[1] = USER_BC_SCALE_MAX;
		break;
	case _SC_BC_STRING_MAX:
		mib[0] = CTL_USER;
		mib[1] = USER_BC_STRING_MAX;
		break;
	case _SC_COLL_WEIGHTS_MAX:
		mib[0] = CTL_USER;
		mib[1] = USER_COLL_WEIGHTS_MAX;
		break;
	case _SC_EXPR_NEST_MAX:
		mib[0] = CTL_USER;
		mib[1] = USER_EXPR_NEST_MAX;
		break;
	case _SC_LINE_MAX:
		mib[0] = CTL_USER;
		mib[1] = USER_LINE_MAX;
		break;
	case _SC_RE_DUP_MAX:
		mib[0] = CTL_USER;
		mib[1] = USER_RE_DUP_MAX;
		break;
	case _SC_2_VERSION:
		mib[0] = CTL_USER;
		mib[1] = USER_POSIX2_VERSION;
		break;
	case _SC_2_C_BIND:
		mib[0] = CTL_USER;
		mib[1] = USER_POSIX2_C_BIND;
D 2
		break;
E 2
I 2
		goto yesno;
E 2
	case _SC_2_C_DEV:
		mib[0] = CTL_USER;
		mib[1] = USER_POSIX2_C_DEV;
D 2
		break;
E 2
I 2
		goto yesno;
	case _SC_2_CHAR_TERM:
		mib[0] = CTL_USER;
		mib[1] = USER_POSIX2_CHAR_TERM;
		goto yesno;
E 2
	case _SC_2_FORT_DEV:
		mib[0] = CTL_USER;
		mib[1] = USER_POSIX2_FORT_DEV;
D 2
		break;
E 2
I 2
		goto yesno;
E 2
	case _SC_2_FORT_RUN:
		mib[0] = CTL_USER;
		mib[1] = USER_POSIX2_FORT_RUN;
D 2
		break;
E 2
I 2
		goto yesno;
E 2
	case _SC_2_LOCALEDEF:
		mib[0] = CTL_USER;
		mib[1] = USER_POSIX2_LOCALEDEF;
D 2
		break;
E 2
I 2
		goto yesno;
E 2
	case _SC_2_SW_DEV:
		mib[0] = CTL_USER;
		mib[1] = USER_POSIX2_SW_DEV;
I 2
		goto yesno;
	case _SC_2_UPE:
		mib[0] = CTL_USER;
		mib[1] = USER_POSIX2_UPE;
yesno:		if (sysctl(mib, 2, &value, &len, NULL, 0) == -1)
			return (-1);
		if (value == 0)
			return (-1);
		return (value);
E 2
		break;
	default:
		errno = EINVAL;
		return (-1);
	}
D 2
	len = sizeof(value);
E 2
	return (sysctl(mib, 2, &value, &len, NULL, 0) == -1 ? -1 : value); 
}
E 1
