h05530
s 00021/00032/00036
d D 8.2 95/05/04 18:00:05 christos 3 2
c 
e
s 00002/00002/00066
d D 8.1 93/05/31 15:20:17 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00068/00000/00000
d D 5.1 91/03/07 20:27:52 bostic 1 0
c date and time created 91/03/07 20:27:52 by bostic
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

#ifndef OUTPUT_INCL

I 3
#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

E 3
struct output {
	char *nextc;
	int nleft;
	char *buf;
	int bufsize;
	short fd;
	short flags;
};

extern struct output output;
extern struct output errout;
extern struct output memout;
extern struct output *out1;
extern struct output *out2;

D 3

#ifdef __STDC__
void outstr(char *, struct output *);
void out1str(char *);
void out2str(char *);
void outfmt(struct output *, char *, ...);
void out1fmt(char *, ...);
void fmtstr(char *, int, char *, ...);
/* void doformat(struct output *, char *, va_list); */
void doformat();
void emptyoutbuf(struct output *);
void flushall(void);
void flushout(struct output *);
void freestdout(void);
int xwrite(int, char *, int);
int xioctl(int, int, int);
#else
void outstr();
void out1str();
void out2str();
void outfmt();
void out1fmt();
void fmtstr();
/* void doformat(); */
void doformat();
void emptyoutbuf();
void flushall();
void flushout();
void freestdout();
int xwrite();
int xioctl();
#endif
E 3
I 3
void open_mem __P((char *, int, struct output *));
void out1str __P((const char *));
void out2str __P((const char *));
void outstr __P((const char *, struct output *));
void emptyoutbuf __P((struct output *));
void flushall __P((void));
void flushout __P((struct output *));
void freestdout __P((void));
void outfmt __P((struct output *, char *, ...));
void out1fmt __P((char *, ...)); 
void dprintf __P((char *, ...));
void fmtstr __P((char *, int, char *, ...));
void doformat __P((struct output *, char *, va_list));
int xwrite __P((int, char *, int));
int xioctl __P((int, unsigned long, char *));
E 3

#define outc(c, file)	(--(file)->nleft < 0? (emptyoutbuf(file), *(file)->nextc++ = (c)) : (*(file)->nextc++ = (c)))
#define out1c(c)	outc(c, out1);
#define out2c(c)	outc(c, out2);

#define OUTPUT_INCL
#endif
E 1
