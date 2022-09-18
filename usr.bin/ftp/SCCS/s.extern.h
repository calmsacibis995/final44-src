h09466
s 00001/00000/00126
d D 8.3 94/10/09 20:49:15 mckusick 3 2
c update to support passive mode (from cgd)
e
s 00000/00002/00126
d D 8.2 94/04/03 10:06:42 pendry 2 1
c eliminate local glob code
e
s 00128/00000/00000
d D 8.1 94/04/02 15:10:17 pendry 1 0
c date and time created 94/04/02 15:10:17 by pendry
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1994 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

struct timeval;
struct fd_set;

void    abort_remote __P((FILE *));
void    abortpt __P(());
void    abortrecv __P(());
void    abortsend __P(());
void	account __P((int, char **));
int	another __P((int *, char ***, char *));
void	blkfree __P((char **));
void	cd __P((int, char **));
void	cdup __P((int, char **));
void	changetype __P((int, int));
void	cmdabort __P(());
void	cmdscanner __P((int));
int	command __P(());
int	confirm __P((char *, char *));
FILE   *dataconn __P((char *));
void	delete __P((int, char **));
void	disconnect __P((int, char **));
void	do_chmod __P((int, char **));
void	do_umask __P((int, char **));
void	domacro __P((int, char **));
char   *domap __P((char *));
void	doproxy __P((int, char **));
char   *dotrans __P((char *));
int     empty __P((struct fd_set *, int));
void	fatal __P((char *));
D 2
char  **ftpglob __P((char *));
E 2
void	get __P((int, char **));
struct cmd *getcmd __P((char *));
int	getit __P((int, char **, int, char *));
int	getreply __P((int));
int	globulize __P((char **));
char   *gunique __P((char *));
void	help __P((int, char **));
char   *hookup __P((char *, int));
void	idle __P((int, char **));
int     initconn __P((void));
void	intr __P(());
void	lcd __P((int, char **));
int	login __P((char *));
void	lostpeer __P(());
void	ls __P((int, char **));
void	mabort __P((int));
void	macdef __P((int, char **));
void	makeargv __P((void));
void	makedir __P((int, char **));
void	mdelete __P((int, char **));
void	mget __P((int, char **));
void	mls __P((int, char **));
void	modtime __P((int, char **));
void	mput __P((int, char **));
char   *onoff __P((int));
void	newer __P((int, char **));
void	proxabort __P(());
void    proxtrans __P((char *, char *, char *));
void    psabort __P(());
void    pswitch __P((int));
void    ptransfer __P((char *, long, struct timeval *, struct timeval *));
void	put __P((int, char **));
void	pwd __P((int, char **));
void	quit __P((int, char **));
void	quote __P((int, char **));
void	quote1 __P((char *, int, char **));
void    recvrequest __P((char *, char *, char *, char *, int));
void	reget __P((int, char **));
char   *remglob __P((char **, int));
void	removedir __P((int, char **));
void	renamefile __P((int, char **));
void    reset __P((int, char **));
void	restart __P((int, char **));
void	rmthelp __P((int, char **));
void	rmtstatus __P((int, char **));
int	ruserpass __P((char *, char **, char **, char **));
void    sendrequest __P((char *, char *, char *, int));
void	setascii __P((int, char **));
void	setbell __P((int, char **));
void	setbinary __P((int, char **));
void	setcase __P((int, char **));
void	setcr __P((int, char **));
void	setdebug __P((int, char **));
void	setform __P((int, char **));
void	setftmode __P((int, char **));
void	setglob __P((int, char **));
void	sethash __P((int, char **));
void	setnmap __P((int, char **));
void	setntrans __P((int, char **));
I 3
void	setpassive __P((int, char **));
E 3
void	setpeer __P((int, char **));
void	setport __P((int, char **));
void	setprompt __P((int, char **));
void	setrunique __P((int, char **));
void	setstruct __P((int, char **));
void	setsunique __P((int, char **));
void	settenex __P((int, char **));
void	settrace __P((int, char **));
void	settype __P((int, char **));
void	setverbose __P((int, char **));
void	shell __P((int, char **));
void	site __P((int, char **));
void	sizecmd __P((int, char **));
char   *slurpstring __P((void));
void	status __P((int, char **));
void	syst __P((int, char **));
void    tvsub __P((struct timeval *, struct timeval *, struct timeval *));
void	user __P((int, char **));

extern jmp_buf	abortprox;
extern int	abrtflag;
extern struct	cmd cmdtab[];
extern FILE	*cout;
extern int	data;
D 2
extern char    *globerr;
E 2
extern char    *home;
extern jmp_buf	jabort;
extern int	proxy;
extern char	reply_string[];
extern off_t	restart_point;
extern int	NCMDS;
E 1
