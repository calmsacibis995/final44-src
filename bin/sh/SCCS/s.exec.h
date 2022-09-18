h45677
s 00001/00001/00041
d D 8.3 95/06/08 19:50:21 christos 5 4
c Obey PATH=newpath command
e
s 00012/00019/00030
d D 8.2 95/05/04 17:59:41 christos 4 3
c 
e
s 00002/00002/00047
d D 8.1 93/05/31 15:18:59 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00047
d D 5.2 92/06/23 17:58:03 marc 2 1
c unsetfunc returns status
e
s 00049/00000/00000
d D 5.1 91/03/07 20:27:28 bostic 1 0
c date and time created 91/03/07 20:27:28 by bostic
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

/* values of cmdtype */
#define CMDUNKNOWN -1		/* no entry in table for command */
#define CMDNORMAL 0		/* command is an executable program */
#define CMDBUILTIN 1		/* command is a shell builtin */
#define CMDFUNCTION 2		/* command is a shell function */


struct cmdentry {
	int cmdtype;
	union param {
		int index;
		union node *func;
	} u;
};


extern char *pathopt;		/* set by padvance */

D 4
#ifdef __STDC__
void shellexec(char **, char **, char *, int);
char *padvance(char **, char *);
void find_command(char *, struct cmdentry *, int);
int find_builtin(char *);
void hashcd(void);
void changepath(char *);
void defun(char *, union node *);
D 2
void unsetfunc(char *);
E 2
I 2
int unsetfunc(char *);
E 2
#else
void shellexec();
char *padvance();
void find_command();
int find_builtin();
void hashcd();
void changepath();
void defun();
D 2
void unsetfunc();
E 2
I 2
int unsetfunc();
E 2
#endif
E 4
I 4
void shellexec __P((char **, char **, char *, int));
char *padvance __P((char **, char *));
int hashcmd __P((int, char **));
D 5
void find_command __P((char *, struct cmdentry *, int));
E 5
I 5
void find_command __P((char *, struct cmdentry *, int, char *));
E 5
int find_builtin __P((char *));
void hashcd __P((void));
void changepath __P((char *));
void deletefuncs __P((void));
void getcmdentry __P((char *, struct cmdentry *));
void addcmdentry __P((char *, struct cmdentry *));
void defun __P((char *, union node *));
int unsetfunc __P((char *));
E 4
E 1
