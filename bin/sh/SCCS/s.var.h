h60352
s 00015/00024/00077
d D 8.2 95/05/04 18:00:15 christos 3 2
c 
e
s 00002/00002/00099
d D 8.1 93/05/31 15:20:55 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00101/00000/00000
d D 5.1 91/03/07 20:28:05 bostic 1 0
c date and time created 91/03/07 20:28:05 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Kenneth Almquist.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Shell variables.
 */

/* flags */
#define VEXPORT		01	/* variable is exported */
#define VREADONLY	02	/* variable cannot be modified */
#define VSTRFIXED	04	/* variable struct is staticly allocated */
#define VTEXTFIXED	010	/* text is staticly allocated */
#define VSTACK		020	/* text is allocated on the stack */
#define VUNSET		040	/* the variable is not set */


struct var {
	struct var *next;		/* next entry in hash list */
	int flags;		/* flags are defined above */
	char *text;		/* name=value */
};


struct localvar {
	struct localvar *next;	/* next local variable in list */
	struct var *vp;		/* the variable that was made local */
	int flags;		/* saved flags */
	char *text;		/* saved text */
};


struct localvar *localvars;

#if ATTY
extern struct var vatty;
#endif
extern struct var vifs;
extern struct var vmail;
extern struct var vmpath;
extern struct var vpath;
extern struct var vps1;
extern struct var vps2;
#if ATTY
extern struct var vterm;
#endif

/*
 * The following macros access the values of the above variables.
 * They have to skip over the name.  They return the null string
 * for unset variables.
 */

#define ifsval()	(vifs.text + 4)
#define mailval()	(vmail.text + 5)
#define mpathval()	(vmpath.text + 9)
#define pathval()	(vpath.text + 5)
#define ps1val()	(vps1.text + 4)
#define ps2val()	(vps2.text + 4)
#if ATTY
#define termval()	(vterm.text + 5)
#endif

#if ATTY
#define attyset()	((vatty.flags & VUNSET) == 0)
#endif
#define mpathset()	((vmpath.flags & VUNSET) == 0)

D 3

#ifdef __STDC__
void initvar();
void setvar(char *, char *, int);
void setvareq(char *, int);
E 3
I 3
void initvar __P((void));
void setvar __P((char *, char *, int));
void setvareq __P((char *, int));
E 3
struct strlist;
D 3
void listsetvar(struct strlist *);
char *lookupvar(char *);
char *bltinlookup(char *, int);
char **environment();
int showvarscmd(int, char **);
void mklocal(char *);
void poplocalvars(void);
#else
void initvar();
void setvar();
void setvareq();
void listsetvar();
char *lookupvar();
char *bltinlookup();
char **environment();
int showvarscmd();
void mklocal();
void poplocalvars();
#endif
E 3
I 3
void listsetvar __P((struct strlist *)); 
char *lookupvar __P((char *));
char *bltinlookup __P((char *, int));
char **environment __P((void));
void shprocvar __P((void));
int showvarscmd __P((int, char **));
int exportcmd __P((int, char **));
int localcmd __P((int, char **));
void mklocal __P((char *));   
void poplocalvars __P((void));
int setvarcmd __P((int, char **));
int unsetcmd __P((int, char **));
E 3
E 1
