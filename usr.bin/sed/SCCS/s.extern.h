h50566
s 00002/00002/00031
d D 8.1 93/06/06 16:16:10 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00033
d D 5.7 93/05/18 14:46:18 elan 7 6
c Strnchr() -> memchr().
e
s 00003/00002/00031
d D 5.6 93/04/14 06:22:35 elan 6 5
c make sed work on 8-bit objects
c TK checking in for Elan Amir
e
s 00001/00001/00032
d D 5.5 92/08/30 12:07:08 bostic 5 4
c don't access entries multiple times; from Diomidis
e
s 00004/00001/00029
d D 5.4 92/08/28 15:26:15 bostic 4 3
c change calling convention of mf_fgets, cspace; new externs
c match and maxnsub
e
s 00000/00001/00030
d D 5.3 92/08/24 20:47:59 bostic 3 2
c we can't survive some of the compile errors, just die
e
s 00001/00001/00030
d D 5.2 92/08/24 12:26:52 bostic 2 1
c fix prototype
e
s 00031/00000/00000
d D 5.1 92/08/23 18:25:59 bostic 1 0
c date and time created 92/08/23 18:25:59 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Diomidis Spinellis.
D 8
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Diomidis Spinellis of Imperial College, University of London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

extern struct s_command *prog;
extern struct s_appends *appends;
I 4
extern regmatch_t *match;
extern size_t maxnsub;
E 4
extern u_long linenum;
extern int appendnum;
D 3
extern int compile_errors;
E 3
extern int lastline;
extern int aflag, eflag, nflag;
extern char *fname;

I 6
void	 cfclose __P((struct s_command *, struct s_command *));
E 6
void	 compile __P((void));
I 6
void	 cspace __P((SPACE *, char *, size_t, enum e_spflag));
E 6
char	*cu_fgets __P((char *, int));
void	 err __P((int, const char *, ...));
D 4
char	*mf_fgets __P((size_t *));
E 4
I 4
int	 mf_fgets __P((SPACE *, enum e_spflag));
E 4
void	 process __P((void));
I 6
D 7
char 	*strnchr __P((const char *, int c, size_t));
E 7
E 6
char	*strregerror __P((int, regex_t *));
void	*xmalloc __P((u_int));
void	*xrealloc __P((void *, u_int));
D 2
void	 cfclose(struct s_command *cp);
E 2
I 2
D 5
void	 cfclose __P((struct s_command *));
E 5
I 5
D 6
void	 cfclose __P((struct s_command *, struct s_command *));
E 5
I 4
void	 cspace __P((SPACE *, char *, size_t, enum e_spflag));
E 6
E 4
E 2
E 1
