h50824
s 00004/00003/00270
d D 8.4 95/02/20 13:59:20 dab 9 8
c Fix f_extproc() routine so that it works.
e
s 00001/00001/00272
d D 8.3 94/04/02 10:02:21 pendry 8 7
c add 1994 copyright
e
s 00024/00014/00249
d D 8.2 94/04/01 03:39:11 pendry 7 6
c prettyness police
e
s 00002/00002/00261
d D 8.1 93/05/31 15:47:42 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00028/00227
d D 5.5 93/04/29 15:17:32 bostic 5 4
c use C library err/warn routines; make GCC 2 happy
e
s 00001/00001/00254
d D 5.4 93/04/17 07:50:06 bostic 4 3
c stty dumps core if you try to set the ispeed (ex: stty ispeed 0)
c From: John T Kohl <jtkohl@kolvir.blrc.ma.us>
e
s 00007/00001/00248
d D 5.3 91/06/10 07:39:44 bostic 3 2
c NULL-terminate cchar arrays for Chris; better information hiding
e
s 00022/00007/00227
d D 5.2 91/06/05 15:22:20 bostic 2 1
c distribute the rest of the main loop into the modes and cchars modules
c bsearch the cchars arrays, minor cleanups
e
s 00234/00000/00000
d D 5.1 91/06/05 08:04:36 bostic 1 0
c break out rest of keywords into function table that can be bsearch'd
c date and time created 91/06/05 08:04:36 by bostic
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
D 8
 * Copyright (c) 1991, 1993
E 8
I 8
 * Copyright (c) 1991, 1993, 1994
E 8
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 5

#include <err.h>
E 5
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
I 5

E 5
#include "stty.h"
#include "extern.h"

__BEGIN_DECLS
D 2
int	c_key __P((const void *, const void *));
E 2
void	f_all __P((struct info *));
void	f_cbreak __P((struct info *));
void	f_columns __P((struct info *));
void	f_dec __P((struct info *));
void	f_everything __P((struct info *));
void	f_extproc __P((struct info *));
void	f_ispeed __P((struct info *));
void	f_nl __P((struct info *));
void	f_ospeed __P((struct info *));
void	f_raw __P((struct info *));
void	f_rows __P((struct info *));
void	f_sane __P((struct info *));
void	f_size __P((struct info *));
void	f_speed __P((struct info *));
void	f_tty __P((struct info *));
__END_DECLS

D 3
static struct key keys[] = {
E 3
I 3
static struct key {
	char *name;				/* name */
	void (*f) __P((struct info *));		/* function */
#define	F_NEEDARG	0x01			/* needs an argument */
#define	F_OFFOK		0x02			/* can turn off */
	int flags;
} keys[] = {
E 3
D 5
	"all",		f_all,		0,
	"cbreak",	f_cbreak,	F_OFFOK,
	"cols",		f_columns,	F_NEEDARG,
	"columns",	f_columns,	F_NEEDARG,
	"cooked", 	f_sane,		0,
	"dec",		f_dec,		0,
	"everything",	f_everything,	0,
	"extproc",	f_extproc,	F_OFFOK,
D 4
	"ispeed",	f_ispeed,	0,
E 4
I 4
	"ispeed",	f_ispeed,	F_NEEDARG,
E 4
	"new",		f_tty,		0,
	"nl",		f_nl,		F_OFFOK,
	"old",		f_tty,		0,
	"ospeed",	f_ospeed,	F_NEEDARG,
	"raw",		f_raw,		F_OFFOK,
	"rows",		f_rows,		F_NEEDARG,
	"sane",		f_sane,		0,
	"size",		f_size,		0,
	"speed",	f_speed,	0,
	"tty",		f_tty,		0,
E 5
I 5
	{ "all",	f_all,		0 },
	{ "cbreak",	f_cbreak,	F_OFFOK },
	{ "cols",	f_columns,	F_NEEDARG },
	{ "columns",	f_columns,	F_NEEDARG },
	{ "cooked", 	f_sane,		0 },
	{ "dec",	f_dec,		0 },
	{ "everything",	f_everything,	0 },
	{ "extproc",	f_extproc,	F_OFFOK },
	{ "ispeed",	f_ispeed,	F_NEEDARG },
	{ "new",	f_tty,		0 },
	{ "nl",		f_nl,		F_OFFOK },
	{ "old",	f_tty,		0 },
	{ "ospeed",	f_ospeed,	F_NEEDARG },
	{ "raw",	f_raw,		F_OFFOK },
	{ "rows",	f_rows,		F_NEEDARG },
	{ "sane",	f_sane,		0 },
	{ "size",	f_size,		0 },
	{ "speed",	f_speed,	0 },
	{ "tty",	f_tty,		0 },
E 5
};

I 7
static int
c_key(a, b)
        const void *a, *b;
{

        return (strcmp(((struct key *)a)->name, ((struct key *)b)->name));
}

E 7
I 5
int
E 5
D 2
struct key *
ksearch(name)
	char *name;
E 2
I 2
ksearch(argvp, ip)
	char ***argvp;
	struct info *ip;
E 2
{
I 2
D 7
	register struct key *kp;
	register char *name;
E 2
	struct key tmp;
D 2
	int c_key __P((const void *, const void *));
E 2
I 2
	static int c_key __P((const void *, const void *));
E 7
I 7
	char *name;
	struct key *kp, tmp;
E 7
E 2

I 2
	name = **argvp;
	if (*name == '-') {
		ip->off = 1;
		++name;
	} else
		ip->off = 0;

E 2
	tmp.name = name;
D 2
	return((struct key *)bsearch(&tmp, keys,
	    sizeof(keys)/sizeof(struct key), sizeof(struct key), c_key));
E 2
I 2
	if (!(kp = (struct key *)bsearch(&tmp, keys,
	    sizeof(keys)/sizeof(struct key), sizeof(struct key), c_key)))
D 5
		return(0);
	if (!(kp->flags & F_OFFOK) && ip->off)
		err("illegal option -- %s\n%s", name, usage);
	if (kp->flags & F_NEEDARG && !(ip->arg = *++*argvp))
		err("option requires an argument -- %s\n%s", name, usage);
E 5
I 5
		return (0);
	if (!(kp->flags & F_OFFOK) && ip->off) {
		errx(1, "illegal option -- %s", name);
		usage();
	}
	if (kp->flags & F_NEEDARG && !(ip->arg = *++*argvp)) {
		errx(1, "option requires an argument -- %s", name);
		usage();
	}
E 5
	kp->f(ip);
D 5
	return(1);
E 5
I 5
	return (1);
E 5
E 2
}

D 5
static
E 5
I 5
D 7
static int
E 5
c_key(a, b)
        const void *a, *b;
{
D 5
        return(strcmp(((struct key *)a)->name, ((struct key *)b)->name));
E 5
I 5
        return (strcmp(((struct key *)a)->name, ((struct key *)b)->name));
E 5
}

E 7
void
f_all(ip)
	struct info *ip;
{
	print(&ip->t, &ip->win, ip->ldisc, BSD);
}

void
f_cbreak(ip)
	struct info *ip;
{
I 7

E 7
	if (ip->off)
		f_sane(ip);
	else {
		ip->t.c_iflag |= BRKINT|IXON|IMAXBEL;
		ip->t.c_oflag |= OPOST;
		ip->t.c_lflag |= ISIG|IEXTEN;
		ip->t.c_lflag &= ~ICANON;
		ip->set = 1;
	}
}

void
f_columns(ip)
	struct info *ip;
{
I 7

E 7
	ip->win.ws_col = atoi(ip->arg);
	ip->wset = 1;
}

void
f_dec(ip)
	struct info *ip;
{
I 7

E 7
	ip->t.c_cc[VERASE] = (u_char)0177;
	ip->t.c_cc[VKILL] = CTRL('u');
	ip->t.c_cc[VINTR] = CTRL('c');
	ip->t.c_lflag &= ~ECHOPRT;
	ip->t.c_lflag |= ECHOE|ECHOKE|ECHOCTL;
	ip->t.c_iflag &= ~IXANY;
	ip->set = 1;
}

void
f_everything(ip)
	struct info *ip;
{
I 7

E 7
	print(&ip->t, &ip->win, ip->ldisc, BSD);
}

void
f_extproc(ip)
	struct info *ip;
{
D 7
	int tmp;
E 7

D 9
	if (ip->set) {
D 7
		tmp = 1;
E 7
I 7
		int tmp = 1;
E 9
I 9
	if (ip->off) {
		int tmp = 0;
E 9
E 7
		(void)ioctl(ip->fd, TIOCEXT, &tmp);
	} else {
D 7
		tmp = 0;
E 7
I 7
D 9
		int tmp = 0;
E 9
I 9
		int tmp = 1;
E 9
E 7
		(void)ioctl(ip->fd, TIOCEXT, &tmp);
	}
I 9
	ip->set = 1;
E 9
}

void
f_ispeed(ip)
	struct info *ip;
{
I 7

E 7
	cfsetispeed(&ip->t, atoi(ip->arg));
	ip->set = 1;
}

void
f_nl(ip)
	struct info *ip;
{
I 7

E 7
	if (ip->off) {
		ip->t.c_iflag |= ICRNL;
		ip->t.c_oflag |= ONLCR;
	} else {
		ip->t.c_iflag &= ~ICRNL;
		ip->t.c_oflag &= ~ONLCR;
	}
	ip->set = 1;
}

void
f_ospeed(ip)
	struct info *ip;
{
I 7

E 7
	cfsetospeed(&ip->t, atoi(ip->arg));
	ip->set = 1;
}

void
f_raw(ip)
	struct info *ip;
{
I 7

E 7
	if (ip->off)
		f_sane(ip);
	else {
		cfmakeraw(&ip->t);
		ip->t.c_cflag &= ~(CSIZE|PARENB);
		ip->t.c_cflag |= CS8;
		ip->set = 1;
	}
}

void
f_rows(ip)
	struct info *ip;
{
I 7

E 7
	ip->win.ws_row = atoi(ip->arg);
	ip->wset = 1;
}

void
f_sane(ip)
	struct info *ip;
{
I 7

E 7
	ip->t.c_cflag = TTYDEF_CFLAG | (ip->t.c_cflag & CLOCAL);
	ip->t.c_iflag = TTYDEF_IFLAG;
	ip->t.c_iflag |= ICRNL;
	/* preserve user-preference flags in lflag */
#define	LKEEP	(ECHOKE|ECHOE|ECHOK|ECHOPRT|ECHOCTL|ALTWERASE|TOSTOP|NOFLSH)
	ip->t.c_lflag = TTYDEF_LFLAG | (ip->t.c_lflag & LKEEP);
	ip->t.c_oflag = TTYDEF_OFLAG;
	ip->set = 1;
}

void
f_size(ip)
	struct info *ip;
{
I 7

E 7
	(void)printf("%d %d\n", ip->win.ws_row, ip->win.ws_col);
}

void
f_speed(ip)
	struct info *ip;
{
I 7

E 7
	(void)printf("%d\n", cfgetospeed(&ip->t));
}

void
f_tty(ip)
	struct info *ip;
{
	int tmp;

	tmp = TTYDISC;
	if (ioctl(0, TIOCSETD, &tmp) < 0)
D 5
		err("TIOCSETD: %s", strerror(errno));
E 5
I 5
		err(1, "TIOCSETD");
E 5
}
E 1
