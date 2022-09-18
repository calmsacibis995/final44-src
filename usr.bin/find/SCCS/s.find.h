h20740
s 00002/00002/00079
d D 8.1 93/06/06 14:38:54 bostic 11 10
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00001/00068
d D 5.10 93/05/01 11:51:35 bostic 10 9
c use library err/warn(3) functions; lint, prettiness police
e
s 00012/00003/00057
d D 5.9 91/07/19 15:05:11 bostic 9 8
c add -path, -fstype rdonly; document values for PLAN->flags
e
s 00001/00006/00059
d D 5.8 91/05/24 15:17:09 bostic 8 7
c return to the original find syntax (newsyntax.c -> main.c, delete
c oldsyntax.c; create extern.h for ANSI prototypes; create true error routine;
c make NEW macro a real routine
e
s 00010/00032/00055
d D 5.7 91/05/23 18:53:28 bostic 7 6
c T_USER used in the kernel, included by <sys/param.h> -- change to
c be N_ instead.  Make it an enum while we're there...
e
s 00001/00001/00086
d D 5.6 91/04/27 13:37:40 bostic 6 5
c add -X flag to make the world safe for xargs
e
s 00002/00002/00085
d D 5.5 91/04/16 14:27:30 bostic 5 4
c Reiser cpp fix
e
s 00004/00001/00083
d D 5.4 91/03/10 11:37:03 bostic 4 3
c ANSI, error routine; use new fts routines which set errno correctly
c so there's lots less work to do here.
e
s 00001/00001/00083
d D 5.3 90/11/15 13:03:00 bostic 3 2
c use getchar() for queryuser function; lots of minor lint
e
s 00002/00002/00082
d D 5.2 90/11/15 12:23:55 bostic 2 1
c make status variables consistent
e
s 00084/00000/00000
d D 5.1 90/04/16 17:23:04 bostic 1 0
c new version derived from Cimarron Taylor's
e
u
U
t
T
I 1
/*-
D 11
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 11
I 11
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 11
 *
 * This code is derived from software contributed to Berkeley by
 * Cimarron D. Taylor of the University of California, Berkeley.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

I 7
/* node type */
enum ntype {
	N_AND = 1, 				/* must start > 0 */
	N_ATIME, N_CLOSEPAREN, N_CTIME, N_DEPTH, N_EXEC, N_EXPR, N_FOLLOW,
	N_FSTYPE, N_GROUP, N_INUM, N_LINKS, N_LS, N_MTIME, N_NAME, N_NEWER,
D 9
	N_NOGROUP, N_NOT, N_NOUSER, N_OK, N_OPENPAREN, N_OR, N_PERM, N_PRINT,
	N_PRUNE, N_SIZE, N_TYPE, N_USER, N_XDEV,
E 9
I 9
	N_NOGROUP, N_NOT, N_NOUSER, N_OK, N_OPENPAREN, N_OR, N_PATH,
	N_PERM, N_PRINT, N_PRUNE, N_SIZE, N_TYPE, N_USER, N_XDEV,
E 9
};

E 7
/* node definition */
typedef struct _plandata {
	struct _plandata *next;			/* next node */
D 10
	int (*eval)();				/* node evaluation function */
E 10
I 10
	int (*eval)				/* node evaluation function */
	    __P((struct _plandata *, FTSENT *));
E 10
I 9
#define	F_EQUAL		1			/* [acm]time inum links size */
#define	F_LESSTHAN	2
#define	F_GREATER	3
#define	F_NEEDOK	1			/* exec ok */
#define	F_MTFLAG	1			/* fstype */
#define	F_MTTYPE	2
#define	F_ATLEAST	1			/* perm */
E 9
	int flags;				/* private flags */
D 7
	int type;				/* plan node type */
E 7
I 7
	enum ntype type;			/* plan node type */
E 7
	union {
		gid_t _g_data;			/* gid */
		ino_t _i_data;			/* inode */
		mode_t _m_data;			/* mode mask */
		nlink_t _l_data;		/* link count */
		off_t _o_data;			/* file size */
		time_t _t_data;			/* time value */
		uid_t _u_data;			/* uid */
I 9
		short _mt_data;			/* mount flags */
E 9
		struct _plandata *_p_data[2];	/* PLAN trees */
		struct _ex {
			char **_e_argv;		/* argv array */
			char **_e_orig;		/* original strings */
			int *_e_len;		/* allocated length */
		} ex;
		char *_a_data[2];		/* array of char pointers */
		char *_c_data;			/* char pointer */
	} p_un;
I 9
} PLAN;
E 9
#define	a_data	p_un._a_data
#define	c_data	p_un._c_data
#define	i_data	p_un._i_data
#define	g_data	p_un._g_data
#define	l_data	p_un._l_data
#define	m_data	p_un._m_data
I 9
#define	mt_data	p_un._mt_data
E 9
#define	o_data	p_un._o_data
#define	p_data	p_un._p_data
#define	t_data	p_un._t_data
#define	u_data	p_un._u_data
#define	e_argv	p_un.ex._e_argv
#define	e_orig	p_un.ex._e_orig
#define	e_len	p_un.ex._e_len
I 10

typedef struct _option {
	char *name;			/* option name */
	enum ntype token;		/* token type */
	PLAN *(*create)();		/* create function: DON'T PROTOTYPE! */
#define	O_NONE		0x01		/* no call required */
#define	O_ZERO		0x02		/* pass: nothing */
#define	O_ARGV		0x04		/* pass: argv, increment argv */
#define	O_ARGVP		0x08		/* pass: *argv, N_OK || N_EXEC */
	int flags;
} OPTION;
E 10
D 9
} PLAN;
E 9
D 7

/* node types */
#define	T_AND		1		/* must start at >0 */
#define	T_ATIME		2
#define	T_CLOSEPAREN	3
#define	T_CTIME		4
#define	T_DEPTH		5
#define	T_EXEC		6
#define	T_EXPR		7
#define	T_FOLLOW	8
#define	T_FSTYPE	9
#define	T_GROUP		10
#define	T_INUM		11
#define	T_LINKS		12
#define	T_LS		13
#define	T_MTIME		14
#define	T_NAME		15
#define	T_NEWER		16
#define	T_NOGROUP	17
#define	T_NOT		18
#define	T_NOUSER	19
#define	T_OK    	20
#define	T_OPENPAREN	21
#define	T_OR		22
#define	T_PERM		23
#define	T_PRINT		24
#define	T_PRUNE		25
#define	T_SIZE		26
#define	T_TYPE		27
#define	T_USER		28
#define	T_XDEV		29
E 7

I 4
D 5
#define	error(p, n) \
	(void)fprintf(stderr, "find: %s: %s\n", p, strerror(n));
E 5
I 5
D 8
#define	error(name, number) \
	(void)fprintf(stderr, "find: %s: %s\n", name, strerror(number));
E 5

E 4
D 2
extern int errno;
extern int ftsoptions, output_specified;
E 2
I 2
extern int ftsoptions;
D 4
extern int isdeprecated, isdepth, isoutput, isrelative, isstopdnx;
E 4
I 4
D 6
extern int isdeprecated, isdepth, isoutput, isrelative;
E 6
I 6
extern int isdeprecated, isdepth, isoutput, isrelative, isxargs;
E 6
E 4
E 2
D 3
char *emalloc();
E 3
I 3
void *emalloc();
E 8
I 8
#include "extern.h"
E 8
E 3
E 1
