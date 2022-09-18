h26072
s 00013/00030/00039
d D 8.2 95/05/04 17:59:56 christos 3 2
c 
e
s 00002/00002/00067
d D 8.1 93/05/31 15:19:43 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00069/00000/00000
d D 5.1 91/03/07 20:27:41 bostic 1 0
c date and time created 91/03/07 20:27:41 by bostic
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

struct stackmark {
	struct stack_block *stackp;
	char *stacknxt;
	int stacknleft;
};


extern char *stacknxt;
extern int stacknleft;
extern int sstrnleft;
extern int herefd;

D 3
#ifdef __STDC__
pointer ckmalloc(int);
pointer ckrealloc(pointer, int);
void free(pointer);		/* defined in C library */
char *savestr(char *);
pointer stalloc(int);
void stunalloc(pointer);
void setstackmark(struct stackmark *);
void popstackmark(struct stackmark *);
void growstackblock(void);
void grabstackblock(int);
char *growstackstr(void);
char *makestrspace(void);
void ungrabstackstr(char *, char *);
#else
pointer ckmalloc();
pointer ckrealloc();
void free();		/* defined in C library */
char *savestr();
pointer stalloc();
void stunalloc();
void setstackmark();
void popstackmark();
void growstackblock();
void grabstackblock();
char *growstackstr();
char *makestrspace();
void ungrabstackstr();
#endif
E 3
I 3
pointer ckmalloc __P((int));
pointer ckrealloc __P((pointer, int));
char *savestr __P((char *));
pointer stalloc __P((int));
void stunalloc __P((pointer));
void setstackmark __P((struct stackmark *));
void popstackmark __P((struct stackmark *));
void growstackblock __P((void));
void grabstackblock __P((int));
char *growstackstr __P((void));
char *makestrspace __P((void));
void ungrabstackstr __P((char *, char *));
E 3



#define stackblock() stacknxt
#define stackblocksize() stacknleft
#define STARTSTACKSTR(p)	p = stackblock(), sstrnleft = stackblocksize()
#define STPUTC(c, p)	(--sstrnleft >= 0? (*p++ = (c)) : (p = growstackstr(), *p++ = (c)))
D 3
#define CHECKSTRSPACE(n, p)	if (sstrnleft < n) p = makestrspace(); else
E 3
I 3
#define CHECKSTRSPACE(n, p)	{ if (sstrnleft < n) p = makestrspace(); }
E 3
#define USTPUTC(c, p)	(--sstrnleft, *p++ = (c))
#define STACKSTRNUL(p)	(sstrnleft == 0? (p = growstackstr(), *p = '\0') : (*p = '\0'))
#define STUNPUTC(p)	(++sstrnleft, --p)
#define STTOPC(p)	p[-1]
#define STADJUST(amount, p)	(p += (amount), sstrnleft -= (amount))
#define grabstackstr(p)	stalloc(stackblocksize() - sstrnleft)

#define ckfree(p)	free((pointer)(p))
E 1
