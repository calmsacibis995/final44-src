h62140
s 00002/00002/00060
d D 8.1 93/05/31 15:06:00 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00008/00053
d D 5.5 92/06/05 18:56:58 bostic 5 4
c ANSI prototypes (two real bugs)
e
s 00008/00006/00053
d D 5.4 92/04/03 14:55:47 mckusick 4 3
c update from Steve McCanne for Sun compatible kvm
e
s 00001/00002/00058
d D 5.3 91/06/03 16:55:45 bostic 3 2
c fix err routine, make everyone use it; minor ANSI cleanups
e
s 00007/00002/00053
d D 5.2 91/03/27 15:49:36 marc 2 1
c its \not/ an error to specify a keyword twice
e
s 00055/00000/00000
d D 5.1 91/02/08 10:58:18 bostic 1 0
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
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#define	UNLIMITED	0	/* unlimited terminal width */
enum type { CHAR, UCHAR, SHORT, USHORT, LONG, ULONG, KPTR };

struct usave {
D 4
	struct	proc *u_procp;
E 4
	struct	timeval u_start;
	struct	rusage u_ru;
	struct	rusage u_cru;
	char	u_acflag;
I 4
	char	u_valid;
E 4
};

I 4
#define KI_PROC(ki) (&(ki)->ki_p->kp_proc)
#define KI_EPROC(ki) (&(ki)->ki_p->kp_eproc)

E 4
D 5
typedef struct _kinfo {
E 5
I 5
typedef struct kinfo {
E 5
D 4
	struct proc *ki_p;	/* proc structure */
	struct eproc *ki_e;	/* extra stuff */
	struct usave *ki_u;	/* interesting parts of user */
	char *ki_args;		/* exec args (should be char **) */
	char *ki_env;		/* environment (should be char **) */
E 4
I 4
	struct kinfo_proc *ki_p;	/* proc structure */
	struct usave ki_u;	/* interesting parts of user */
	char *ki_args;		/* exec args */
	char *ki_env;		/* environment */
E 4
} KINFO;

/* Variables. */
D 5
typedef struct _var {
E 5
I 5
typedef struct varent {
	struct varent *next;
	struct var *var;
} VARENT;

typedef struct var {
E 5
	char	*name;		/* name(s) of variable */
	char	*header;	/* default header */
	char	*alias;		/* aliases */
#define	COMM	0x01		/* needs exec arguments and environment (XXX) */
#define	LJUST	0x02		/* left adjust on output (trailing blanks) */
#define	USER	0x04		/* needs user structure */
	u_int	flag;
D 5
	int	(*oproc)();	/* output routine */
E 5
I 5
				/* output routine */
	void	(*oproc) __P((struct kinfo *, struct varent *));
E 5
	short	width;		/* printing width */
	/*
	 * The following (optional) elements are hooks for passing information
	 * to the generic output routines: pvar, evar, uvar (those which print
	 * simple elements from well known structures: proc, eproc, usave)
	 */
	int	off;		/* offset in structure */
	enum	type type;	/* type of element */
	char	*fmt;		/* printf format */
	char	*time;		/* time format */
	/*
	 * glue to link selected fields together
	 */
D 2
	struct _var *next;
E 2
} VAR;
D 5

D 2
extern VAR var[], *vhead, *vtail;
E 2
I 2
struct varent {
	VAR *var;
	struct varent *next;
};
E 5

D 3
extern VAR var[];
extern struct varent *vhead, *vtail;
E 3
I 3
#include "extern.h"
E 3
E 2
E 1
