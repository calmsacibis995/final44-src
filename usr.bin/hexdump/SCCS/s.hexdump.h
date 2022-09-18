h07387
s 00002/00002/00070
d D 8.1 93/06/06 14:50:01 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00001/00072
d D 5.6 92/09/13 11:16:51 ralph 6 5
c odoffset is only used in odsyntax.c, don't define here.
e
s 00024/00001/00049
d D 5.5 92/07/14 14:30:34 bostic 5 4
c fix for quads; prototype and cleanup in general
e
s 00001/00011/00049
d D 5.4 90/06/01 16:52:39 bostic 4 3
c new copyright notice
e
s 00001/00001/00059
d D 5.3 90/05/07 21:07:54 bostic 3 2
c fix bug so doesn't match first line in file of all NULL's
e
s 00010/00009/00050
d D 5.2 89/08/29 22:18:22 bostic 2 1
c trimming trailing blanks is too hard; the last revision handles most of the
c cases -- the one I quit on is where you have:
c 	"%06.6_ao "  12/1 "%3o "
c 	"\t\t" "%_p"
c 	"\n"
c You'd have to read-ahead and figure out what's going to be printed from
c future format strings to know if the current line should be blank padded.
e
s 00059/00000/00000
d D 5.1 89/08/29 18:36:24 bostic 1 0
c date and time created 89/08/29 18:36:24 by bostic
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

typedef struct _pr {
	struct _pr *nextpr;		/* next print unit */
#define	F_ADDRESS	0x001		/* print offset */
D 2
#define	F_C		0x002		/* %_c */
#define	F_CHAR		0x004		/* %c */
#define	F_DBL		0x008		/* %[EefGf] */
#define	F_INT		0x010		/* %[di] */
#define	F_P		0x020		/* %_p */
#define	F_STR		0x040		/* %s */
#define	F_U		0x080		/* %_u */
#define	F_UINT		0x100		/* %[ouXx] */
#define	F_TEXT		0x200		/* no conversions */
E 2
I 2
#define	F_BPAD		0x002		/* blank pad */
#define	F_C		0x004		/* %_c */
#define	F_CHAR		0x008		/* %c */
#define	F_DBL		0x010		/* %[EefGf] */
#define	F_INT		0x020		/* %[di] */
#define	F_P		0x040		/* %_p */
#define	F_STR		0x080		/* %s */
#define	F_U		0x100		/* %_u */
#define	F_UINT		0x200		/* %[ouXx] */
#define	F_TEXT		0x400		/* no conversions */
E 2
	u_int flags;			/* flag values */
	int bcnt;			/* byte count */
	char *cchar;			/* conversion character */
	char *fmt;			/* printf format */
	char *nospace;			/* no whitespace version */
} PR;

typedef struct _fu {
	struct _fu *nextfu;		/* next format unit */
	struct _pr *nextpr;		/* next print unit */
#define	F_IGNORE	0x01		/* %_A */
#define	F_SETREP	0x02		/* rep count set, not default */
	u_int flags;			/* flag values */
	int reps;			/* repetition count */
	int bcnt;			/* byte count */
	char *fmt;			/* format string */
} FU;

typedef struct _fs {			/* format strings */
	struct _fs *nextfs;		/* linked list of format strings */
	struct _fu *nextfu;		/* linked list of format units */
	int bcnt;
} FS;

extern FS *fshead;			/* head of format strings list */
extern int blocksize;			/* data block size */
D 3
enum _vflag { ALL, DUP, WAIT };		/* -v values */
E 3
I 3
enum _vflag { ALL, DUP, FIRST, WAIT };	/* -v values */
E 3
D 5
char *emalloc();
E 5
I 5

void	 add __P((char *));
void	 addfile __P((char *));
void	 badcnt __P((char *));
void	 badconv __P((char *));
void	 badfmt __P((char *));
void	 badsfmt __P((void));
void	 bpad __P((PR *));
void	 conv_c __P((PR *, u_char *));
void	 conv_u __P((PR *, u_char *));
void	 display __P((void));
void	 doskip __P((char *, int));
void	 err __P((const char *, ...));
void	*emalloc __P((int));
void	 escape __P((char *));
u_char	*get __P((void));
void	 newsyntax __P((int, char ***));
int	 next __P((char **));
void	 nomem __P((void));
D 6
void	 odoffset __P((int, char ***));
E 6
void	 oldsyntax __P((int, char ***));
void	 rewrite __P((FS *));
int	 size __P((FS *));
void	 usage __P((void));
E 5
E 1
