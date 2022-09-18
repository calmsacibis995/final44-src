h20834
s 00010/00010/00029
d D 8.2 95/05/04 17:59:39 christos 4 3
c 
e
s 00002/00002/00037
d D 8.1 93/05/31 15:18:52 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00038
d D 5.2 91/04/12 18:20:49 marc 2 1
c add BLETCH comment to 'union node;'
e
s 00039/00000/00000
d D 5.1 91/03/07 20:27:26 bostic 1 0
c date and time created 91/03/07 20:27:26 by bostic
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

extern char *commandname;	/* currently executing command */
extern int exitstatus;		/* exit status of last command */
extern struct strlist *cmdenviron;  /* environment for builtin command */


struct backcmd {		/* result of evalbackcmd */
	int fd;			/* file descriptor to read from */
	char *buf;		/* buffer */
	int nleft;		/* number of chars in buffer */
	struct job *jp;		/* job structure for command */
};

D 4

#ifdef __STDC__
void evalstring(char *);
E 4
I 4
int evalcmd __P((int, char **));
void evalstring __P((char *));
E 4
D 2
union node;
E 2
I 2
union node;	/* BLETCH for ansi C */
E 2
D 4
void evaltree(union node *, int);
void evalbackcmd(union node *, struct backcmd *);
#else
void evalstring();
void evaltree();
void evalbackcmd();
#endif
E 4
I 4
void evaltree __P((union node *, int));
void evalbackcmd __P((union node *, struct backcmd *));
int bltincmd __P((int, char **));
int breakcmd __P((int, char **));
int returncmd __P((int, char **));
int falsecmd __P((int, char **));
int truecmd __P((int, char **));
int execcmd __P((int, char **));
E 4

/* in_function returns nonzero if we are currently evaluating a function */
#define in_function()	funcnest
extern int funcnest;
E 1
