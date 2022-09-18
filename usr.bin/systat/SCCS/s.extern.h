h29151
s 00002/00002/00090
d D 8.1 93/06/06 16:28:53 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00092/00000/00000
d D 5.1 92/07/23 17:51:58 bostic 1 0
c date and time created 92/07/23 17:51:58 by bostic
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
 * %sccs.include.redist.c%
 *
 *      %W% (Berkeley) %G%
 */

#include <sys/cdefs.h>
#include <fcntl.h>
#include <kvm.h>

extern struct	cmdtab *curcmd;
extern struct	cmdtab cmdtab[];
extern struct	text *xtext;
extern WINDOW	*wnd;
extern char	**dr_name;
extern char	c, *namp, hostname[];
extern double	avenrun[3];
extern float	*dk_mspw;
extern kvm_t	*kd;
extern long	ntext, textp;
extern int	*dk_select;
extern int	CMDLINE;
extern int	dk_ndrive;
extern int	hz, stathz;
extern int	naptime, col;
extern int	nhosts;
extern int	nports;
extern int	protos;
extern int	verbose;

struct inpcb;

int	 checkhost __P((struct inpcb *));
int	 checkport __P((struct inpcb *));
void	 closeiostat __P((WINDOW *));
void	 closekre __P((WINDOW *));
void	 closembufs __P((WINDOW *));
void	 closenetstat __P((WINDOW *));
void	 closepigs __P((WINDOW *));
void	 closeswap __P((WINDOW *));
int	 cmdiostat __P((char *, char *));
int	 cmdkre __P((char *, char *));
int	 cmdnetstat __P((char *, char *));
struct	 cmdtab *lookup __P((char *));
void	 command __P((char *));
void	 die __P((int));
void	 display __P((int));
int	 dkinit __P((void));
int	 dkcmd __P((char *, char *));
void	 error __P((const char *fmt, ...));
void	 fetchiostat __P((void));
void	 fetchkre __P((void));
void	 fetchmbufs __P((void));
void	 fetchnetstat __P((void));
void	 fetchpigs __P((void));
void	 fetchswap __P((void));
int	 initiostat __P((void));
int	 initkre __P((void));
int	 initmbufs __P((void));
int	 initnetstat __P((void));
int	 initpigs __P((void));
int	 initswap __P((void));
int	 keyboard __P((void));
int	 kvm_ckread __P((void *, void *, int));
void	 labeliostat __P((void));
void	 labelkre __P((void));
void	 labelmbufs __P((void));
void	 labelnetstat __P((void));
void	 labelpigs __P((void));
void	 labels __P((void));
void	 labelswap __P((void));
void	 load __P((void));
int	 netcmd __P((char *, char *));
void	 nlisterr __P((struct nlist []));
WINDOW	*openiostat __P((void));
WINDOW	*openkre __P((void));
WINDOW	*openmbufs __P((void));
WINDOW	*opennetstat __P((void));
WINDOW	*openpigs __P((void));
WINDOW	*openswap __P((void));
int	 prefix __P((char *, char *));
void	 showiostat __P((void));
void	 showkre __P((void));
void	 showmbufs __P((void));
void	 shownetstat __P((void));
void	 showpigs __P((void));
void	 showswap __P((void));
void	 status __P((void));
void	 suspend __P((int));
E 1
