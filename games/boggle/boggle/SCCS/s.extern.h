h45137
s 00000/00000/00045
d D 8.1 93/06/11 14:44:55 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00045/00000/00000
d D 5.1 93/06/11 14:44:43 bostic 1 0
c date and time created 93/06/11 14:44:43 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

void	 addword __P((char *));
void	 badword __P((void));
char	*batchword __P((FILE *));
void	 checkdict __P((void));
int	 checkword __P((char *, int, int *));
void	 cleanup __P((void));
void	 delay __P((int));
long	 dictseek __P((FILE *, long, int));
void	 findword __P((void));
void	 flushin __P((FILE *));
char	*getline __P((char *));
void	 getword __P((char *));
int	 help __P((void));
int	 inputch __P((void));
int	 loaddict __P((FILE *));
int	 loadindex __P((char *));
void	 newgame __P((char *));
char	*nextword __P((FILE *));
FILE	*opendict __P((char *));
void	 playgame __P((void));
void	 prompt __P((char *));
void	 prtable __P((char *[],
	    int, int, int, void (*)(char *[], int), int (*)(char *[], int)));
void	 putstr __P((char *));
void	 redraw __P((void));
void	 results __P((void));
int	 setup __P((int, long));
void	 showboard __P((char *));
void	 showstr __P((char *, int));
void	 showword __P((int));
void	 starttime __P((void));
void	 startwords __P((void));
void	 stoptime __P((void));
int	 timerch __P((void));
void	 usage __P((void));
int	 validword __P((char *));
E 1
