h49806
s 00000/00001/00082
d D 8.2 94/01/07 15:05:47 bostic 6 5
c use C library error functions, not local one
e
s 00002/00002/00081
d D 8.1 93/06/05 11:11:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00003/00074
d D 5.4 93/02/11 08:28:38 bostic 4 3
c gcc -Wall from Craig Leres (no substantive changes)
e
s 00004/00004/00073
d D 5.3 93/02/10 14:47:51 bostic 3 2
c make declarations work with new prototypes in globh
e
s 00002/00001/00075
d D 5.2 92/12/02 01:04:30 mckusick 2 1
c add rst_closedir; new return value for pathsearch
e
s 00076/00000/00000
d D 5.1 92/10/24 16:00:12 bostic 1 0
c date and time created 92/10/24 16:00:12 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct entry	*addentry __P((char *, ino_t, int));
long		 addfile __P((char *, ino_t, int));
void		 badentry __P((struct entry *, char *));
void	 	 canon __P((char *, char *));
void		 checkrestore __P((void));
void		 closemt __P((void));
void		 createfiles __P((void));
void		 createleaves __P((char *));
void		 createlinks __P((void));
long		 deletefile __P((char *, ino_t, int));
void		 deleteino __P((ino_t));
D 3
ino_t		 dirlookup __P((char *));
E 3
I 3
ino_t		 dirlookup __P((const char *));
E 3
D 4
void	 	 done __P((int));
E 4
I 4
__dead void 	 done __P((int));
E 4
void		 dumpsymtable __P((char *, long));
D 6
void		 err __P((const char *, ...));
E 6
void	 	 extractdirs __P((int));
int		 extractfile __P((char *));
void		 findunreflinks __P((void));
char		*flagvalues __P((struct entry *));
void		 freeentry __P((struct entry *));
void		 freename __P((char *));
int	 	 genliteraldir __P((char *, ino_t));
char		*gentempname __P((struct entry *));
void		 getfile __P((void (*)(char *, long), void (*)(char *, long)));
void		 getvol __P((long));
void		 initsymtable __P((char *));
int	 	 inodetype __P((ino_t));
D 4
struct inotab	*inotablookup __P((ino_t));
E 4
int		 linkit __P((char *, char *, int));
struct entry	*lookupino __P((ino_t));
struct entry	*lookupname __P((char *));
long		 listfile __P((char *, ino_t, int));
ino_t		 lowerbnd __P((ino_t));
void		 mktempname __P((struct entry *));
void		 moveentry __P((struct entry *, char *));
void		 msg __P((const char *, ...));
char		*myname __P((struct entry *));
void		 newnode __P((struct entry *));
void		 newtapebuf __P((long));
long		 nodeupdates __P((char *, ino_t, int));
void	 	 onintr __P((int));
D 3
RST_DIR		*opendirfile __P((char *));
E 3
I 3
D 4
RST_DIR		*opendirfile __P((const char *));
E 4
E 3
void		 panic __P((const char *, ...));
void		 pathcheck __P((char *));
D 2
ino_t	 	 pathsearch __P((char *));
E 2
I 2
D 3
struct direct	*pathsearch __P((char *));
E 3
I 3
struct direct	*pathsearch __P((const char *));
E 3
E 2
void		 printdumpinfo __P((void));
void		 removeleaf __P((struct entry *));
void		 removenode __P((struct entry *));
void		 removeoldleaves __P((void));
void		 removeoldnodes __P((void));
void		 renameit __P((char *, char *));
int		 reply __P((char *));
D 3
RST_DIR		*rst_opendir __P((char *));
E 3
I 3
RST_DIR		*rst_opendir __P((const char *));
E 3
struct direct	*rst_readdir __P((RST_DIR *));
I 2
void		 rst_closedir __P((RST_DIR *dirp));
E 2
void	 	 runcmdshell __P((void));
char		*savename __P((char *));
void	 	 setdirmodes __P((int));
void		 setinput __P((char *));
void		 setup __P((void));
void	 	 skipdirs __P((void));
void		 skipfile __P((void));
void		 skipmaps __P((void));
void		 swabst __P((u_char *, u_char *));
void	 	 treescan __P((char *, ino_t, long (*)(char *, ino_t, int)));
ino_t		 upperbnd __P((ino_t));
long		 verifyfile __P((char *, ino_t, int));
void		 xtrnull __P((char *, long));
I 4

/* From ../dump/dumprmt.c */
void		rmtclose __P((void));
int		rmthost __P((char *));
int		rmtioctl __P((int, int));
int		rmtopen __P((char *, int));
int		rmtread __P((char *, int));
int		rmtseek __P((int, int));
E 4
E 1
