h52294
s 00012/00026/00026
d D 8.2 95/05/04 17:59:49 christos 4 3
c 
e
s 00002/00002/00050
d D 8.1 93/05/31 15:19:17 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00049
d D 5.2 92/06/23 18:02:59 marc 2 1
c routines for supporting aliases
e
s 00051/00000/00000
d D 5.1 91/03/07 20:27:33 bostic 1 0
c date and time created 91/03/07 20:27:33 by bostic
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

/* PEOF (the end of file marker) is defined in syntax.h */

/*
 * The input line number.  Input.c just defines this variable, and saves
 * and restores it when files are pushed and popped.  The user of this
 * package must set its value.
 */
extern int plinno;
extern int parsenleft;		/* number of characters left in input buffer */
extern char *parsenextc;	/* next character in input buffer */
I 2
extern int init_editline;	/* 0 == not setup, 1 == OK, -1 == failed */
E 2

D 4

#ifdef __STDC__
char *pfgets(char *, int);
int pgetc(void);
int preadbuffer(void);
void pungetc(void);
D 2
void ppushback(char *, int);
E 2
I 2
void pushstring(char *, int, void *);
E 2
void setinputfile(char *, int);
void setinputfd(int, int);
void setinputstring(char *, int);
void popfile(void);
void popallfiles(void);
void closescript(void);
#else
char *pfgets();
int pgetc();
int preadbuffer();
void pungetc();
D 2
void ppushback();
E 2
void setinputfile();
void setinputfd();
void setinputstring();
void popfile();
void popallfiles();
I 2
void pushstring();
E 2
void closescript();
#endif
E 4
I 4
char *pfgets __P((char *, int));
int pgetc __P((void));
int preadbuffer __P((void));
void pungetc __P((void));
void pushstring __P((char *, int, void *));
void popstring __P((void));
void setinputfile __P((char *, int));
void setinputfd __P((int, int));
void setinputstring __P((char *, int)); 
void popfile __P((void));
void popallfiles __P((void));
void closescript __P((void));
E 4

#define pgetc_macro()	(--parsenleft >= 0? *parsenextc++ : preadbuffer())
E 1
