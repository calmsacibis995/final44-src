h06488
s 00030/00031/00009
d D 8.2 94/04/04 12:36:06 pendry 3 2
c eliminate local version of glob (cf ftp)
c clean up yacc grammar.  prettiness police.
e
s 00002/00002/00038
d D 8.1 93/06/04 18:48:17 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00040/00000/00000
d D 5.1 92/07/19 15:10:54 bostic 1 0
c date and time created 92/07/19 15:10:54 by bostic
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 3
void	  blkfree __P((char **));
char	**copyblk __P((char **));
void	  cwd __P((char *));
void	  delete __P((char *));
void	  dologout __P((int));
void	  fatal __P((char *));
int	  ftpd_pclose __P((FILE *));
FILE	 *ftpd_popen __P((char *, char *));
char	**ftpglob __P((char *));
char	  *getline __P((char *, int, FILE *));
void	  logwtmp __P((char *, char *, char *));
void	  lreply __P((int, const char *, ...));
void	  makedir __P((char *));
void	  nack __P((char *));
void	  pass __P((char *));
void	  passive __P((void));
void	  perror_reply __P((int, char *));
void	  pwd __P((void));
void	  removedir __P((char *));
void	  renamecmd __P((char *, char *));
char	 *renamefrom __P((char *));
void	  reply __P((int, const char *, ...));
void	  retrieve __P((char *, char *));
void	  send_file_list __P((char *));
void	  setproctitle __P((const char *, ...));
void	  statcmd __P((void));
void	  statfilecmd __P((char *));
void	  store __P((char *, char *, int));
void	  upper __P((char *));
void	  user __P((char *));
char	 *yyerror __P((char *));
E 3
I 3
void	blkfree __P((char **));
char  **copyblk __P((char **));
void	cwd __P((char *));
void	delete __P((char *));
void	dologout __P((int));
void	fatal __P((char *));
int	ftpd_pclose __P((FILE *));
FILE   *ftpd_popen __P((char *, char *));
char   *getline __P((char *, int, FILE *));
void	logwtmp __P((char *, char *, char *));
void	lreply __P((int, const char *, ...));
void	makedir __P((char *));
void	nack __P((char *));
void	pass __P((char *));
void	passive __P((void));
void	perror_reply __P((int, char *));
void	pwd __P((void));
void	removedir __P((char *));
void	renamecmd __P((char *, char *));
char   *renamefrom __P((char *));
void	reply __P((int, const char *, ...));
void	retrieve __P((char *, char *));
void	send_file_list __P((char *));
void	setproctitle __P((const char *, ...));
void	statcmd __P((void));
void	statfilecmd __P((char *));
void	store __P((char *, char *, int));
void	upper __P((char *));
void	user __P((char *));
void	yyerror __P((char *));
E 3
E 1
