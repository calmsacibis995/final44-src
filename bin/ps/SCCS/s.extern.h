h17762
s 00001/00001/00058
d D 8.3 94/04/02 10:01:03 pendry 9 8
c add 1994 copyright
e
s 00003/00000/00056
d D 8.2 94/04/02 09:58:41 pendry 8 7
c prettyness police
e
s 00002/00002/00054
d D 8.1 93/06/02 18:20:08 mckusick 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00056
d D 5.5 93/06/02 18:19:32 mckusick 6 4
c devname moves to libc
e
s 00002/00002/00055
d R 8.1 93/05/31 15:05:32 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00057
d D 5.4 93/04/29 13:19:12 bostic 4 3
c use err/warn from the C library
e
s 00043/00002/00015
d D 5.3 92/06/05 18:56:49 bostic 3 2
c ANSI prototypes (two real bugs)
e
s 00001/00001/00016
d D 5.2 91/06/03 17:19:00 bostic 2 1
c vtail doesn't need to be global
e
s 00017/00000/00000
d D 5.1 91/06/03 16:49:18 bostic 1 0
c date and time created 91/06/03 16:49:18 by bostic
e
u
U
t
T
I 1
/*-
D 7
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
D 9
 * Copyright (c) 1991, 1993
E 9
I 9
 * Copyright (c) 1991, 1993, 1994
E 9
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include <sys/cdefs.h>
E 3
I 3
struct kinfo;
struct nlist;
struct var;
struct varent;
E 3

I 8
extern fixpt_t ccpu;
extern int eval, fscale, mempages, nlistread, rawcpu;
extern int sumrusage, termwidth, totwidth;
E 8
extern VAR var[];
D 2
extern struct varent *vhead, *vtail;
E 2
I 2
D 3
extern struct varent *vhead;
E 3
I 3
extern VARENT *vhead;
E 3
E 2

__BEGIN_DECLS
I 3
void	 command __P((KINFO *, VARENT *));
void	 cputime __P((KINFO *, VARENT *));
D 6
char	*devname __P((dev_t, mode_t));
E 6
int	 donlist __P((void));
E 3
D 4
void	 err __P((const char *, ...));
E 4
I 3
void	 evar __P((KINFO *, VARENT *));
char	*fmt_argv __P((char **, char *, int));
double	 getpcpu __P((KINFO *));
double	 getpmem __P((KINFO *));
void	 logname __P((KINFO *, VARENT *));
void	 longtname __P((KINFO *, VARENT *));
void	 lstarted __P((KINFO *, VARENT *));
void	 maxrss __P((KINFO *, VARENT *));
void	 nlisterr __P((struct nlist *));
void	 p_rssize __P((KINFO *, VARENT *));
void	 pagein __P((KINFO *, VARENT *));
void	 parsefmt __P((char *));
void	 pcpu __P((KINFO *, VARENT *));
void	 pmem __P((KINFO *, VARENT *));
void	 pri __P((KINFO *, VARENT *));
void	 printheader __P((void));
void	 pvar __P((KINFO *, VARENT *));
void	 rssize __P((KINFO *, VARENT *));
void	 runame __P((KINFO *, VARENT *));
void	 rvar __P((KINFO *, VARENT *));
void	 showkey __P((void));
void	 started __P((KINFO *, VARENT *));
void	 state __P((KINFO *, VARENT *));
void	 tdev __P((KINFO *, VARENT *));
void	 tname __P((KINFO *, VARENT *));
#ifndef NEWVM
void	 trss __P((KINFO *, VARENT *));
#endif
void	 tsize __P((KINFO *, VARENT *));
void	 ucomm __P((KINFO *, VARENT *));
void	 uname __P((KINFO *, VARENT *));
void	 uvar __P((KINFO *, VARENT *));
void	 vsize __P((KINFO *, VARENT *));
void	 wchan __P((KINFO *, VARENT *));
E 3
__END_DECLS
E 1
