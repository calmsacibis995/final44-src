h62109
s 00002/00002/00114
d D 8.1 93/06/06 11:58:23 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00115
d D 5.3 92/02/09 08:44:32 pendry 3 2
c merge in new release
e
s 00003/00002/00113
d D 5.2 91/05/12 16:00:44 pendry 2 1
c checkpoint for network tape
e
s 00115/00000/00000
d D 5.1 91/03/17 13:41:25 pendry 1 0
c date and time created 91/03/17 13:41:25 by pendry
e
u
U
t
T
I 1
/*
D 2
 * $Id: config.h,v 5.2.1.3 91/03/17 17:38:39 jsp Alpha $
 *
E 2
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
I 2
 *
D 3
 * $Id: config.h,v 5.2.1.4 91/05/07 22:19:20 jsp Alpha $
E 3
I 3
 * $Id: config.h,v 5.2.2.1 1992/02/09 15:09:56 jsp beta $
E 3
 *
E 2
 */

/*
 * Get this in now so that OS_HDR can use it
 */
#ifdef __STDC__
#define	P(x) x
#define	P_void void
#define	Const const
#else
#define P(x) ()
#define P_void /* as nothing */
#define Const /* as nothing */
#endif /* __STDC__ */

#ifdef __GNUC__
#define INLINE /* __inline */
#else
#define	INLINE
#endif /* __GNUC__ */

/*
 * Pick up target dependent definitions
 */
#include "os-defaults.h"
#include OS_HDR

#ifdef VOIDP
typedef void *voidp;
#else
typedef char *voidp;
#endif /* VOIDP */

#include <stdio.h>
#include <sys/types.h>
#include <sys/errno.h>
extern int errno;
#include <sys/time.h>

#define clocktime() (clock_valid ? clock_valid : time(&clock_valid))
extern time_t time P((time_t *));
extern time_t clock_valid;	/* Clock needs recalculating */

extern char *progname;		/* "amd"|"mmd" */
extern char hostname[];		/* "kiska" */
extern int mypid;		/* Current process id */

#ifdef HAS_SYSLOG
extern int syslogging;		/* Really using syslog */
#endif /* HAS_SYSLOG */
extern FILE *logfp;		/* Log file */
extern int xlog_level;		/* Logging level */
extern int xlog_level_init;

extern int orig_umask;		/* umask() on startup */

#define	XLOG_FATAL	0x0001
#define	XLOG_ERROR	0x0002
#define	XLOG_USER	0x0004
#define	XLOG_WARNING	0x0008
#define	XLOG_INFO	0x0010
#define	XLOG_DEBUG	0x0020
#define	XLOG_MAP	0x0040
#define	XLOG_STATS	0x0080

#define XLOG_DEFSTR	"all,nomap,nostats"		/* Default log options */
#define XLOG_ALL	(XLOG_FATAL|XLOG_ERROR|XLOG_USER|XLOG_WARNING|XLOG_INFO|XLOG_MAP|XLOG_STATS)

#ifdef DEBUG
#define	D_ALL	(~0)

#ifdef DEBUG_MEM
#define free(x) xfree(__FILE__,__LINE__,x)
#endif /* DEBUG_MEM */

#define Debug(x) if (!(debug_flags & (x))) ; else
#define dlog Debug(D_FULL) dplog
#endif /* DEBUG */

/*
 * Option tables
 */
struct opt_tab {
	char *opt;
	int flag;
};

extern struct opt_tab xlog_opt[];

extern int cmdoption P((char*, struct opt_tab*, int*));
extern void going_down P((int));
#ifdef DEBUG
extern void dplog ();
/*extern void dplog P((char*, ...));*/
#endif /* DEBUG */
extern void plog ();
/*extern void plog P((int, char*, ...));*/
extern void show_opts P((int ch, struct opt_tab*));
extern char* strchr P((const char*, int)); /* C */
extern voidp xmalloc P((int));
extern voidp xrealloc P((voidp, int));
E 1
