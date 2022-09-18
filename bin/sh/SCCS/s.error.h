h43456
s 00006/00014/00073
d D 8.2 95/05/04 17:59:37 christos 3 2
c 
e
s 00002/00002/00085
d D 8.1 93/05/31 15:18:43 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00087/00000/00000
d D 5.1 91/03/07 20:27:23 bostic 1 0
c date and time created 91/03/07 20:27:23 by bostic
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
 * Types of operations (passed to the errmsg routine).
 */

#define E_OPEN 01	/* opening a file */
#define E_CREAT 02	/* creating a file */
#define E_EXEC 04	/* executing a program */


/*
 * We enclose jmp_buf in a structure so that we can declare pointers to
 * jump locations.  The global variable handler contains the location to
 * jump to when an exception occurs, and the global variable exception
 * contains a code identifying the exeception.  To implement nested
 * exception handlers, the user should save the value of handler on entry
 * to an inner scope, set handler to point to a jmploc structure for the
 * inner scope, and restore handler on exit from the scope.
 */

#include <setjmp.h>

struct jmploc {
	jmp_buf loc;
};

extern struct jmploc *handler;
extern int exception;

/* exceptions */
#define EXINT 0		/* SIGINT received */
#define EXERROR 1	/* a generic error */
#define EXSHELLPROC 2	/* execute a shell procedure */


/*
 * These macros allow the user to suspend the handling of interrupt signals
 * over a period of time.  This is similar to SIGHOLD to or sigblock, but
 * much more efficient and portable.  (But hacking the kernel is so much
 * more fun than worrying about efficiency and portability. :-))
 */

extern volatile int suppressint;
extern volatile int intpending;
extern char *commandname;	/* name of command--printed on error */

#define INTOFF suppressint++
D 3
#define INTON if (--suppressint == 0 && intpending) onint(); else
E 3
I 3
#define INTON { if (--suppressint == 0 && intpending) onint(); }
E 3
#define FORCEINTON {suppressint = 0; if (intpending) onint();}
#define CLEAR_PENDING_INT intpending = 0
#define int_pending() intpending

D 3
#ifdef __STDC__
void exraise(int);
void onint(void);
void error2(char *, char *);
void error(char *, ...);
char *errmsg(int, int);
#else
void exraise();
void onint();
void error2();
void error();
char *errmsg();
#endif
E 3
I 3
void exraise __P((int));
void onint __P((void));
void error2 __P((char *, char *));
void error __P((char *, ...));
char *errmsg __P((int, int));
E 3


/*
 * BSD setjmp saves the signal mask, which violates ANSI C and takes time,
 * so we use _setjmp instead.
 */

#ifdef BSD
#define setjmp(jmploc)	_setjmp(jmploc)
#define longjmp(jmploc, val)	_longjmp(jmploc, val)
#endif
E 1
