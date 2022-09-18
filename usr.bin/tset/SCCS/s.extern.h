h43964
s 00002/00002/00032
d D 8.1 93/06/09 22:53:55 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00033
d D 5.2 91/12/24 10:33:33 bostic 2 1
c add the -a, -d, -p and -r options back in
e
s 00034/00000/00000
d D 5.1 91/12/22 18:54:34 bostic 1 0
c date and time created 91/12/22 18:54:34 by bostic
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
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* This should be in <termcap.h> instead. */
extern char PC;
extern short ospeed;
int	 tgetent __P((char *, char *));
int	 tgetflag __P((char *));
int	 tgetnum __P((char *));
char	*tgetstr __P((char *, char **));
char	*tgoto __P((char *, int, int));
int	 tputs __P((char *, int, void (*) __P((int))));

extern struct termios mode, oldmode;
extern int columns, isreset, lines;
extern int erasechar, intrchar, killchar;

D 2
void	 add_mapping __P((char *));
E 2
I 2
void	 add_mapping __P((char *, char *));
E 2
void	 cat __P((char *));
void	 err __P((const char *, ...));
char	*get_termcap_entry __P((char *, char **));
char	*mapped __P((char *));
void	 outc __P((int));
void	 reset_mode __P((void));
void	 set_control_chars __P((void));
void	 set_conversions __P((int));
void	 set_init __P((void));
void	 wrtermcap __P((char *));
E 1
