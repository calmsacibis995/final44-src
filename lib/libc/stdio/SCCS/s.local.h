h37680
s 00016/00016/00045
d D 8.3 94/07/03 15:06:21 mckusick 6 5
c declare variables extern and define only once (from ralph)
e
s 00001/00001/00060
d D 8.2 94/01/02 14:41:33 bostic 5 4
c fgetline(3) renamed to be fgetln(3)
e
s 00002/00002/00059
d D 8.1 93/06/04 13:07:53 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00060
d D 5.3 93/05/06 22:41:47 torek 3 2
c add __swhatbuf, internal routine for determining "proper" buffering
e
s 00014/00027/00046
d D 5.2 91/02/05 00:24:48 torek 2 1
c use __P prototype macro; add a few missing prototypes
e
s 00073/00000/00000
d D 5.1 91/01/20 21:34:55 bostic 1 0
c new stdio
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Information local to this implementation of stdio,
 * in particular, macros and private variables.
 */

D 2
#if __STDC__ || c_plusplus
extern int	__sflush(FILE *);
extern FILE	*__sfp(void);
extern int	__srefill(FILE *);
extern int	__sread(void *, char *, int);
extern int	__swrite(void *, char const *, int);
extern fpos_t	__sseek(void *, fpos_t, int);
extern int	__sclose(void *);
extern void	__sinit(void);
extern void	_cleanup(void);
extern void	(*__cleanup)(void);
extern void	__smakebuf(FILE *);
extern int	_fwalk(int (*)(FILE *));
#else /* __STDC__ || c_plusplus */
extern int	__sflush();
extern FILE	*__sfp();
extern int	__srefill();
extern int	__sread();
extern int	__swrite();
extern fpos_t	__sseek();
extern int	__sclose();
extern void	__sinit();
extern void	_cleanup();
extern void	(*__cleanup)();
extern void	__smakebuf();
extern int	__sfwalk();
#endif /* __STDC__ || c_plusplus */
E 2
I 2
D 6
int	__sflush __P((FILE *));
FILE	*__sfp __P((void));
int	__srefill __P((FILE *));
int	__sread __P((void *, char *, int));
int	__swrite __P((void *, char const *, int));
fpos_t	__sseek __P((void *, fpos_t, int));
int	__sclose __P((void *));
void	__sinit __P((void));
void	_cleanup __P((void));
void	(*__cleanup) __P((void));
void	__smakebuf __P((FILE *));
I 3
int	__swhatbuf __P((FILE *, size_t *, int *));
E 3
int	_fwalk __P((int (*)(FILE *)));
int	__swsetup __P((FILE *));
int	__sflags __P((const char *, int *));
E 6
I 6
extern int	__sflush __P((FILE *));
extern FILE	*__sfp __P((void));
extern int	__srefill __P((FILE *));
extern int	__sread __P((void *, char *, int));
extern int	__swrite __P((void *, char const *, int));
extern fpos_t	__sseek __P((void *, fpos_t, int));
extern int	__sclose __P((void *));
extern void	__sinit __P((void));
extern void	_cleanup __P((void));
extern void	(*__cleanup) __P((void));
extern void	__smakebuf __P((FILE *));
extern int	__swhatbuf __P((FILE *, size_t *, int *));
extern int	_fwalk __P((int (*)(FILE *)));
extern int	__swsetup __P((FILE *));
extern int	__sflags __P((const char *, int *));
E 6
E 2

D 6
extern int __sdidinit;
E 6
I 6
extern int	__sdidinit;
E 6

/*
 * Return true iff the given FILE cannot be written now.
 */
#define	cantwrite(fp) \
	((((fp)->_flags & __SWR) == 0 || (fp)->_bf._base == NULL) && \
	 __swsetup(fp))

/*
 * Test whether the given stdio file has an active ungetc buffer;
 * release such a buffer, without restoring ordinary unread data.
 */
#define	HASUB(fp) ((fp)->_ub._base != NULL)
#define	FREEUB(fp) { \
	if ((fp)->_ub._base != (fp)->_ubuf) \
		free((char *)(fp)->_ub._base); \
	(fp)->_ub._base = NULL; \
}

/*
D 5
 * test for an fgetline() buffer.
E 5
I 5
 * test for an fgetln() buffer.
E 5
 */
#define	HASLB(fp) ((fp)->_lb._base != NULL)
#define	FREELB(fp) { \
	free((char *)(fp)->_lb._base); \
	(fp)->_lb._base = NULL; \
}
E 1
