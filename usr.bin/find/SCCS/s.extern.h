h02637
s 00001/00002/00051
d D 8.3 94/04/16 13:56:14 bostic 7 6
c option() is now static to option.c
e
s 00001/00001/00052
d D 8.2 94/04/01 07:20:28 bostic 6 5
c return error status to main for an exit status
e
s 00002/00002/00051
d D 8.1 93/06/06 14:38:39 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00052
d D 5.4 93/05/01 11:51:33 bostic 4 3
c use library err/warn(3) functions; lint, prettiness police
e
s 00001/00000/00052
d D 5.3 91/07/19 15:05:09 bostic 3 2
c add -path, -fstype rdonly; document values for PLAN->flags
e
s 00001/00002/00051
d D 5.2 91/05/24 15:36:36 bostic 2 1
c change find to do an fchdir on exec/ok; this means that the -r
c option can go away and everybody gets the speedup
e
s 00053/00000/00000
d D 5.1 91/05/24 15:14:09 bostic 1 0
c date and time created 91/05/24 15:14:09 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
D 7
 * Copyright (c) 1991, 1993
E 7
I 7
 * Copyright (c) 1991, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <sys/cdefs.h>

void	 brace_subst __P((char *, char **, char *, int));
void	*emalloc __P((unsigned int));
D 4
void	 err __P((const char *, ...));
E 4
PLAN	*find_create __P((char ***));
D 6
void	 find_execute __P((PLAN *, char **));
E 6
I 6
int	 find_execute __P((PLAN *, char **));
E 6
PLAN	*find_formplan __P((char **));
PLAN	*not_squish __P((PLAN *));
I 4
D 7
OPTION	*option __P((char *));
E 7
E 4
PLAN	*or_squish __P((PLAN *));
PLAN	*paren_squish __P((PLAN *));
struct stat;
void	 printlong __P((char *, char *, struct stat *));
int	 queryuser __P((char **));

PLAN	*c_atime __P((char *));
PLAN	*c_ctime __P((char *));
PLAN	*c_depth __P((void));
PLAN	*c_exec __P((char ***, int));
PLAN	*c_follow __P((void));
PLAN	*c_fstype __P((char *));
PLAN	*c_group __P((char *));
PLAN	*c_inum __P((char *));
PLAN	*c_links __P((char *));
PLAN	*c_ls __P((void));
PLAN	*c_name __P((char *));
PLAN	*c_newer __P((char *));
PLAN	*c_nogroup __P((void));
PLAN	*c_nouser __P((void));
I 3
PLAN	*c_path __P((char *));
E 3
PLAN	*c_perm __P((char *));
PLAN	*c_print __P((void));
PLAN	*c_prune __P((void));
PLAN	*c_size __P((char *));
PLAN	*c_type __P((char *));
PLAN	*c_user __P((char *));
PLAN	*c_xdev __P((void));
PLAN	*c_openparen __P((void));
PLAN	*c_closeparen __P((void));
PLAN	*c_mtime __P((char *));
PLAN	*c_not __P((void));
PLAN	*c_or __P((void));

D 2
extern int ftsoptions;
extern int isdeprecated, isdepth, isoutput, isrelative, isxargs;
E 2
I 2
extern int ftsoptions, isdeprecated, isdepth, isoutput, isxargs;
E 2
E 1
