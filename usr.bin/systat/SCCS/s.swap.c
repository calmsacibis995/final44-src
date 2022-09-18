h03889
s 00003/00004/00227
d D 8.3 95/04/29 11:50:50 bostic 26 25
c change devname(3) to return NULL on error
e
s 00002/00002/00229
d D 8.2 94/02/21 21:14:51 bostic 25 24
c type of 'blocksize' should be long not int.
c From: ralphc@pyramid.com (Ralph Campbell)
e
s 00002/00002/00229
d D 8.1 93/06/06 16:29:36 bostic 24 23
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00231
d D 5.15 93/06/02 18:55:47 mckusick 23 22
c getbsize and devname moved to libc
e
s 00166/00228/00065
d D 5.14 93/05/21 15:46:04 mckusick 22 21
c update for new vm system
e
s 00006/00006/00287
d D 5.13 92/09/02 11:56:37 bostic 21 20
c nl is an exported curses function
e
s 00006/00006/00287
d D 5.12 92/07/24 12:41:22 bostic 20 19
c rename nlst to nl globally so can use vmstat's names.c; should not
c be a semantic change for any of these files
e
s 00049/00036/00244
d D 5.11 92/07/23 18:10:59 bostic 19 18
c Elan's new kvm version; update copyright/header; lint
e
s 00045/00063/00235
d D 5.10 91/06/26 13:50:23 marc 18 17
c changes for new kernel, plus use kvm
e
s 00002/00011/00296
d D 5.9 91/06/04 16:51:25 marc 17 16
c lookup device name using devname()
e
s 00008/00008/00299
d D 5.8 91/02/04 23:18:49 torek 16 15
c fix gcc-detected lint
e
s 00000/00001/00307
d D 5.7 90/02/25 22:51:58 donn 15 14
c Remove redundant reference to dir.h.
e
s 00002/00002/00306
d D 5.6 89/05/29 17:27:52 mckusick 14 13
c merge in vnodes
e
s 00033/00036/00275
d D 5.5 89/05/11 10:57:55 bostic 13 12
c file reorg, pathnames.h, paths.h; some reformatting
e
s 00002/00000/00309
d D 5.4 86/07/20 10:58:22 sam 12 11
c range check number of swap devices
e
s 00003/00000/00306
d D 5.3 86/01/12 15:26:27 sam 11 10
c add tahoe
e
s 00003/00003/00303
d D 5.2 85/12/11 16:08:16 bloom 10 9
c fix problem with losing /vmunix in the middle, a bit of lint cleanup
e
s 00008/00002/00298
d D 5.1 85/05/30 16:27:02 mckusick 9 8
c Add copyright
e
s 00000/00003/00300
d D 1.8 85/05/01 01:34:39 sam 8 7
c major rework; fixup netstat stuff; pull disk cmds into common file; change 
c everthing related to disks to use dk_ndrive and global selction; use getw where possible
e
s 00020/00024/00283
d D 1.7 85/04/29 00:43:04 sam 7 6
c cleanup window handling, use subwindows exclusively
e
s 00010/00000/00297
d D 1.6 84/08/09 19:13:07 mckusick 6 5
c update to new sources from sam; weed out unnecessary #includes
e
s 00161/00126/00136
d D 1.5 83/10/02 20:45:55 sam 5 4
c reorganize window management to allow display routines to set 
c up optimal window definitions
e
s 00028/00009/00234
d D 1.4 83/10/02 15:09:47 sam 4 3
c add some sanity checks
e
s 00160/00219/00083
d D 1.3 83/10/02 14:40:33 sam 3 2
c add init routine and mbuf display; redo swap space display
e
s 00219/00194/00083
d D 1.2 83/10/01 21:22:55 sam 2 1
c 1st version of swap usage; must redo to show swap in use rather than free
e
s 00277/00000/00000
d D 1.1 83/10/01 12:21:03 sam 1 0
c date and time created 83/10/01 12:21:03 by sam
e
u
U
t
T
I 9
D 19
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 19
I 19
/*-
D 24
 * Copyright (c) 1980, 1992 The Regents of the University of California.
 * All rights reserved.
E 24
I 24
 * Copyright (c) 1980, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 24
 *
D 22
 * %sccs.include.proprietary.c%
E 22
I 22
 * %sccs.include.redist.c%
E 22
E 19
 */

E 9
I 1
#ifndef lint
D 7
static char *sccsid = "%W% (Lucasfilm) %G%";
E 7
I 7
D 9
static char *sccsid = "%W% (Berkeley) %G%";
E 7
#endif
E 9
I 9
static char sccsid[] = "%W% (Berkeley) %G%";
D 19
#endif not lint
E 19
I 19
#endif /* not lint */
E 19
E 9

I 19
D 22
#include <sys/types.h>
#include <sys/dmap.h>
E 22
I 22
/*
 * swapinfo - based on a program of the same name by Kevin Lahey
 */
E 22

I 22
#include <sys/param.h>
#include <sys/buf.h>
#include <sys/conf.h>
#include <sys/ioctl.h>
#include <sys/map.h>
#include <sys/stat.h>

#include <kvm.h>
E 22
#include <nlist.h>
I 22
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

E 22
E 19
#include "systat.h"
I 18
D 19
#ifdef NOTDEF
E 18
I 6
D 8
#include <sys/param.h>
E 8
D 15
#include <sys/dir.h>
E 15
#include <sys/user.h>
#include <sys/proc.h>
D 18
#include <sys/text.h>
E 18
#include <sys/conf.h>
D 8
#include <sys/file.h>
E 8
D 18
#include <sys/vmmac.h>
E 18
I 17
#include <sys/stat.h>
E 17
#include <machine/pte.h>
I 13
#include <paths.h>
I 18
#endif NOTDEF
E 19
I 19
#include "extern.h"
E 19
E 18
E 13
D 8
#include <nlist.h>
E 8
E 6

I 19
D 22
long ntext, textp;
struct text *xtext;
E 22
I 22
D 26
extern char *devname __P((int, int));
E 26
extern char *getbsize __P((int *headerlenp, long *blocksizep));
void showspace __P((char *header, int hlen, long blocksize));
E 22

D 22
static void swaplabel __P((int, int, int));
static void vsacct __P((struct dmap *));
static int swapdisplay __P((int, int, int));
static int dmtoindex __P((int));
E 22
I 22
kvm_t	*kd;
E 22

I 22
struct nlist syms[] = {
	{ "_swapmap" },	/* list of free swap areas */
#define VM_SWAPMAP	0
	{ "_nswapmap" },/* size of the swap map */
#define VM_NSWAPMAP	1
	{ "_swdevt" },	/* list of swap devices and sizes */
#define VM_SWDEVT	2
	{ "_nswap" },	/* size of largest swap device */
#define VM_NSWAP	3
	{ "_nswdev" },	/* number of swap devices */
#define VM_NSWDEV	4
	{ "_dmmax" },	/* maximum size of a swap block */
#define VM_DMMAX	5
	0
};

static int nswap, nswdev, dmmax, nswapmap;
static struct swdevt *sw;
D 25
static long *perdev;
E 25
I 25
static long *perdev, blocksize;
E 25
static struct map *swapmap, *kswapmap;
static struct mapent *mp;
D 25
static int nfree, hlen, blocksize;
E 25
I 25
static int nfree, hlen;
E 25

#define	SVAR(var) __STRING(var)	/* to force expansion */
#define	KGET(idx, var) \
	KGET1(idx, &var, sizeof(var), SVAR(var))
#define	KGET1(idx, p, s, msg) \
	KGET2(syms[idx].n_value, p, s, msg)
#define	KGET2(addr, p, s, msg) \
	if (kvm_read(kd, addr, p, s) != s) { \
		error("cannot read %s: %s", msg, kvm_geterr(kd)); \
		return (0); \
	}

E 22
E 19
D 5
#include <sys/map.h>
#include <sys/conf.h>
I 3
#include <sys/text.h>
E 3

/* these don't belong here */
I 3
#define X_PROC          0
#define X_NPROC         1
#define X_USRPTMAP      4
#define X_USRPT         5
E 3
#define X_NSWAP         6
D 3
#define X_SWAPMAP       7
#define X_NSWAPMAP      8
E 3
#define X_DMMIN         9
#define X_DMMAX         10
#define X_NSWDEV        11
I 2
#define	X_SWDEVT	12
I 3
#define	X_NTEXT		13
#define	X_TEXT		14
#define	X_DMTEXT	15
E 3
E 2

D 3
static  int dmmin;
static  int dmmax;
static  int nswdev;
static  int nswapmap;
static  int nswap;
static  struct map *swapmap;
I 2
static	short *buckets;
static	short *overflow;
E 3
I 3
int	dmmin;
int	dmmax;
int	dmtext;
int	nswdev;
#define	MAXSWAPDEV	4
short	buckets[MAXSWAPDEV][NDMAP];
E 3
struct	swdevt *swdevt;
I 3
struct	proc *kprocp;
int	ntext;
int	textaddr;
struct	text *xtext;
E 3
E 2

D 3
fetchswap()
E 3
I 3
initswap()
E 5
I 5
WINDOW *
openswap()
E 5
E 3
{
I 5
D 7
	static WINDOW *w = NULL;
E 7
E 5
D 13

E 13
D 3
        if (nswapmap == 0) {
                nswapmap = getw(nlst[X_NSWAPMAP].n_value);
                swapmap = (struct map *)calloc(nswapmap, sizeof (struct map));
                nswap = getw(nlst[X_NSWAP].n_value);
E 3
I 3
D 5
        if (nswdev == 0) {
E 3
                dmmin = getw(nlst[X_DMMIN].n_value);
                dmmax = getw(nlst[X_DMMAX].n_value);
I 3
                dmtext = getw(nlst[X_DMTEXT].n_value);
E 3
                nswdev = getw(nlst[X_NSWDEV].n_value);
I 2
D 3
		buckets = (short *)calloc(nswdev, sizeof (short));
		overflow = (short *)calloc(nswdev, sizeof (short));
E 3
		swdevt = (struct swdevt *)calloc(nswdev, sizeof (*swdevt));
		klseek(kmem, nlst[X_SWDEVT].n_value, L_SET);
		read(kmem, swdevt, nswdev * sizeof (struct swdevt));
D 3
		swapmap->m_name = "swap";
E 2
                return;
E 3
I 3
		ntext = getw(nlst[X_NTEXT].n_value);
D 4
		xtext = (struct text *)calloc(ntext, sizeof (struct text));
E 4
		textaddr = getw(nlst[X_TEXT].n_value);
E 3
        }
D 3
        klseek(kmem, getw(nlst[X_SWAPMAP].n_value), L_SET);
        read(kmem, swapmap, nswapmap * sizeof (struct map));
E 3
I 3
        if (procp == NULL) {
                procp = getw(nlst[X_PROC].n_value);
                nproc = getw(nlst[X_NPROC].n_value);
D 4
                kprocp = (struct proc *)malloc(sizeof (*kprocp) * nproc);
E 4
        }
I 4
	if (xtext == NULL)
		xtext = (struct text *)calloc(ntext, sizeof (struct text));
	if (kprocp == NULL)
                kprocp = (struct proc *)calloc(nproc, sizeof (struct proc));
E 4
        if (usrpt != NULL)
                return;
	usrpt = (struct pte *)nlst[X_USRPT].n_value;
	Usrptma = (struct pte *)nlst[X_USRPTMAP].n_value;
D 4
	pt = (struct p_times *)malloc(nproc * sizeof (struct p_times));
E 4
I 4
	if (pt == NULL)
		pt = (struct p_times *)malloc(nproc * sizeof (struct p_times));
E 5
I 5
D 7
        if (w == NULL)
		w = newwin(20, 70, 3, 5);
	return (w);
E 7
I 7
	return (subwin(stdscr, LINES-5-1, 0, 5, 0));
E 7
E 5
E 4
E 3
D 2
        swapmap->m_name = "swap";
E 2
}

I 19
void
E 19
I 3
D 5
fetchswap()
E 5
I 5
closeswap(w)
	WINDOW *w;
E 5
{
D 13

E 13
I 4
D 5
	if (kprocp == NULL) {
                kprocp = (struct proc *)malloc(sizeof (*kprocp) * nproc);
		if (kprocp == NULL)
			return;
	}
E 4
        lseek(kmem, procp, L_SET);
D 4
        read(kmem, kprocp, sizeof (struct proc) * nproc);
E 4
I 4
        if (read(kmem, kprocp, sizeof (struct proc) * nproc) !=
	    sizeof (struct proc) * nproc) {
		error("couldn't read proc table");
E 5
I 5
	if (w == NULL)
E 5
		return;
D 5
	}
	if (xtext == NULL) {
		xtext = (struct text *)calloc(ntext, sizeof (struct text));
		if (xtext == NULL)
			return;
	}
E 4
	lseek(kmem, textaddr, L_SET);
D 4
	read(kmem, xtext, ntext * sizeof (struct text));
E 4
I 4
	if (read(kmem, xtext, ntext * sizeof (struct text)) !=
	    sizeof (struct text) * ntext)
		error("couldn't read text table");
E 5
I 5
D 7
	move(5, 0);
	clrtobot();
E 7
	wclear(w);
	wrefresh(w);
I 7
	delwin(w);
E 7
E 5
E 4
}

I 18
D 19
#ifdef NOTDEF
E 19
E 18
E 3
I 2
D 5
#ifdef vax
char	*devnames[] =
     { "hp", "ht", "up", "rk", "sw", "tm", "ts", "mt", "tu", "ra", "ut",
       "rb", "rx", "rl" };
#endif
E 5
I 5
D 22
int	dmmin;
int	dmmax;
int	dmtext;
int	nswdev;
#define	MAXSWAPDEV	4
short	buckets[MAXSWAPDEV][NDMAP];
struct	swdevt *swdevt;
E 5
int	colwidth;
I 18
D 19
#endif NOTDEF
E 19
E 18

I 19
void
E 19
E 2
D 5
labelswap()
{
I 2
	register int i, j;
I 3
	register int row;
E 3
E 2

I 2
	if (nswdev == 0)
D 3
		fetchswap();
E 3
I 3
		initswap();
E 3
	if (nswdev == 0) {
		mvaddstr(22, 0, "Can't find number of swap devices.\n");
		return;
	}
E 2
        move(5, 0);
D 2
        clrtoeol();
        mvaddstr(5, 20, "/0   /5   /10  /15  /20  /25  /30  /35  /40  /45  /50");
E 2
I 2
	colwidth = (70 - (nswdev - 1)) / nswdev;
I 3
	row = swaplabel(5, dmtext, 1);
	(void) swaplabel(row, dmmax, 0);
}

swaplabel(row, dmbound, donames)
	register int row;
	int dmbound, donames;
{
	register int i, j;

E 3
	for (i = 0; i < nswdev; i++) {
D 3
		move(5, 5 + i * (1 + colwidth) + (colwidth - 3) / 2);
		printw("%s%d", devnames[major(swdevt[i].sw_dev)],
		    minor(swdevt[i].sw_dev) >> 3);
E 3
I 3
		if (donames) {
			move(row, 5 + i * (1 + colwidth) + (colwidth - 3) / 2);
			printw("%s%d", devnames[major(swdevt[i].sw_dev)],
			    minor(swdevt[i].sw_dev) >> 3);
		}
E 3
		for (j = 0; j + 5 < colwidth; j += 5) {
D 3
			move(6, 5 + i * (1 + colwidth) + j);
E 3
I 3
			move(row + donames, 5 + i * (1 + colwidth) + j);
E 3
			printw("/%-2d  ", j);
		}
	}
D 3
	for (j = 0, i = dmmax; i >= dmmin; i /= 2, j++) {
E 3
I 3
	row += 1 + donames;
	for (j = 0, i = dmmin; i <= dmbound; i *= 2, j++, row++) {
E 3
		int k;

D 3
		mvprintw(7 + j, 0, "%4d|", i);
E 3
I 3
		mvprintw(row, 0, "%4d|", i);
E 3
		for (k = 1; k < nswdev; k++)
D 3
			mvwaddch(wnd, 4 + j, k * (1 + colwidth) - 1, '|');
E 3
I 3
			mvwaddch(wnd, row - 3, k * (1 + colwidth) - 1, '|');
E 3
	}
I 3
	return (row);
E 3
E 2
}

E 5
I 3
D 18
extern union {
D 13
        struct  user user;
        char    upages[UPAGES][NBPG];
E 13
I 13
	struct  user user;
	char    upages[UPAGES][NBPG];
E 13
} user;
#define u       user.user

E 18
E 3
showswap()
E 22
I 22
initswap()
E 22
{
I 18
D 19
#ifdef NOTDEF
E 19
I 19
D 22
#ifdef notdef	
E 19
E 18
I 2
D 13
        register int i, j;
E 13
I 13
	register int i, j;
E 13
I 3
	register struct proc *pp;
	register struct text *xp;
E 3
E 2
	register int row;
I 3
	register int ts;
	register swblk_t *dp;
E 22
I 22
	int i;
	char msgbuf[BUFSIZ];
	static int once = 0;
E 22
E 3
D 2
        register int i, j, free;
#ifdef notdef
        register struct mapent *me;
E 2

D 2
        free = 0;
        for (me = (struct mapent *)(swapmap+1);
            me < (struct mapent *)&swapmap[nswapmap]; me++)
                free += me->m_size;
        free /= nswdev;
        for (i = 0; i < nswdev; i++)
                for (space = free; space > 0; space -= j) {
                        j = rmalloc(swapmap, dev));
                        if (j == 0)
                                break;
                }
#else
	for (row = 5, i = dmmax; i >= dmmin; i /= 2, row++) {
		j = 0;
		while (rmalloc(swapmap, i) != 0)
			j++;
                mvwprintw(wnd, row, 10, "%5d", i);
                wmove(wnd, row, 15);
                wclrtoeol(wnd);
                while (j--)
                        waddch(wnd, 'X');
        }
E 2
I 2
D 4
	if (nswdev == 0)
E 4
I 4
D 22
	if (xtext == 0)
E 4
		return;
D 3
	for (row = 4, i = dmmax; i >= dmmin; i /= 2, row++) {
move(22, 0); clrtoeol(); printw("size %d", i); refresh();
		do {
			j = rmalloc(swapmap, i);
			if (j)
				buckets[(j / dmmax) % nswdev]++;
		} while (j);
		for (j = 0; j < nswdev; j++) {
			register int k;
move(21 - j, 0); clrtoeol();
printw("buckets[%d]=%d", j, buckets[j]);
refresh();
			wmove(wnd, row, j * (1 + colwidth));
			k = MIN(buckets[j], colwidth);
			while (k--)
				waddch(wnd, 'X');
			k = MAX(colwidth - buckets[j], 0);
			while (k--)
				waddch(wnd, ' ');
			buckets[j] = 0;
E 3
I 3
	for (xp = xtext; xp < &xtext[ntext]; xp++) {
D 14
		if (xp->x_iptr == NULL)
E 14
I 14
		if (xp->x_vptr == NULL)
E 14
			continue;
		ts = ctod(xp->x_size);
		dp = xp->x_daddr;
		for (i = 0; i < ts; i += dmtext) {
			j = ts - i;
			if (j > dmtext)
				j = dmtext;
#define	swatodev(addr)	(((addr) / dmmax) % nswdev)
			buckets[swatodev(*dp)][dmtoindex(j)]++;
			dp++;
E 22
I 22
	if (once)
		return (1);
	if (kvm_nlist(kd, syms)) {
		strcpy(msgbuf, "systat: swap: cannot find");
		for (i = 0; syms[i].n_name != NULL; i++) {
			if (syms[i].n_value == 0) {
				strcat(msgbuf, " ");
				strcat(msgbuf, syms[i].n_name);
			}
E 22
E 3
		}
I 3
D 14
		if ((xp->x_flag & XPAGI) && xp->x_ptdaddr)
E 14
I 14
D 22
		if ((xp->x_flag & XPAGV) && xp->x_ptdaddr)
E 14
			buckets[swatodev(xp->x_ptdaddr)]
			    [dmtoindex(ctod(ctopt(xp->x_size)))]++;
E 22
I 22
		error(msgbuf);
		return (0);
E 22
E 3
	}
I 3
D 7
	row = swapdisplay(4, dmtext, 'X');
E 7
I 7
D 22
	row = swapdisplay(2, dmtext, 'X');
E 7
I 4
	if (kprocp == NULL)
		return;
E 4
D 13
        for (i = 0, pp = kprocp; i < nproc; i++, pp++) {
E 13
I 13
D 18
	for (i = 0, pp = kprocp; i < nproc; i++, pp++) {
E 18
I 18
	/* TODO - traverse procs { */
E 18
E 13
		if (pp->p_stat == 0 || pp->p_stat == SZOMB)
			continue;
		if (pp->p_flag & SSYS)
			continue;
D 4
		if (getu(pp) == 0) {
			error("showswap: getu failed on pid %d", pp->p_pid);
E 4
I 4
		if (getu(pp) == 0)
E 4
			continue;
D 4
		}
E 4
		vsacct(&u.u_dmap);
		vsacct(&u.u_smap);
E 3
D 19
#ifdef notdef
E 19
D 3
	printf("overflow:");
	for (i = 0; i < nswdev; i++)
		printf("\t%d", overflow[i]);
	printf("\n");
E 3
I 3
		if ((pp->p_flag & SLOAD) == 0)
			vusize(pp);
E 22
I 22
	KGET(VM_NSWAP, nswap);
	KGET(VM_NSWDEV, nswdev);
	KGET(VM_DMMAX, dmmax);
	KGET(VM_NSWAPMAP, nswapmap);
	KGET(VM_SWAPMAP, kswapmap);	/* kernel `swapmap' is a pointer */
	if ((sw = malloc(nswdev * sizeof(*sw))) == NULL ||
	    (perdev = malloc(nswdev * sizeof(*perdev))) == NULL ||
	    (mp = malloc(nswapmap * sizeof(*mp))) == NULL) {
		error("swap malloc");
		return (0);
E 22
E 3
E 2
D 19
#endif
E 19
I 3
D 13
        }
E 13
I 13
	}
E 13
D 7
	(void) swapdisplay(row + 1, dmmax, 'X');
E 7
I 7
D 22
	(void) swapdisplay(1+row, dmmax, 'X');
I 18
D 19
#endif NOTDEF
E 19
I 19
#endif
E 22
I 22
	KGET1(VM_SWDEVT, sw, nswdev * sizeof(*sw), "swdevt");
	once = 1;
	return (1);
E 22
E 19
E 18
E 7
E 3
}

I 7
D 22
#define	OFFSET	5			/* left hand column */

I 19
static int
E 19
E 7
D 2
#ifdef notdef
up(size)
        register int size;
{
        register int i, block;

        i = 0;
        block = dmmin;
        while (i < size) {
                i += block;
                if (block < dmmax)
                        block *= 2;
        }
        return (i);
}
#endif

E 2
D 3
/*
 * Allocate 'size' units from the given
 * map. Return the base of the allocated space.
 * In a map, the addresses are increasing and the
 * list is terminated by a 0 size.
 *
 * Algorithm is first-fit.
 *
 * This routine knows about the interleaving of the swapmap
 * and handles that.
 */
long
rmalloc(mp, size)
D 2
        register struct map *mp;
        long size;
E 2
I 2
	register struct map *mp;
	long size;
E 3
I 3
swapdisplay(baserow, dmbound, c)
D 19
	int baserow, dmbound;
	char c;
E 19
I 19
	int baserow, dmbound, c;
E 22
I 22
void
fetchswap()
E 22
E 19
E 3
E 2
{
I 18
D 19
#ifdef NOTDEF
E 19
I 19
D 22
#ifdef notdef	
E 19
E 18
D 2
        register struct mapent *ep = (struct mapent *)(mp+1);
        register int addr;
        register struct mapent *bp;
        swblk_t first, rest;
E 2
I 2
D 3
	register struct mapent *ep = (struct mapent *)(mp+1);
	register int addr;
	register struct mapent *bp;
	swblk_t first, rest;
E 3
I 3
	register int i, j, k, row;
	register short *pb;
	char buf[10];
E 22
I 22
	int s, e, i;
E 22
E 3
E 2

D 2
        if (size <= 0 || size > dmmax)
                return (0);
        /*
         * Search for a piece of the resource map which has enough
         * free space to accomodate the request.
         */
        for (bp = ep; bp->m_size; bp++) {
                if (bp->m_size >= size) {
                        /*
                         * If allocating from swapmap,
                         * then have to respect interleaving
                         * boundaries.
                         */
                        if (nswdev > 1 &&
                            (first = dmmax - bp->m_addr%dmmax) < bp->m_size) {
                                if (bp->m_size - first < size)
                                        continue;
                                addr = bp->m_addr + first;
                                rest = bp->m_size - first - size;
                                bp->m_size = first;
                                if (rest)
                                        rmfree(mp, rest, addr+size);
                                return (addr);
                        }
                        /*
                         * Allocate from the map.
                         * If there is no space left of the piece
                         * we allocated from, move the rest of
                         * the pieces to the left.
                         */
                        addr = bp->m_addr;
                        bp->m_addr += size;
                        if ((bp->m_size -= size) == 0) {
                                do {
                                        bp++;
                                        (bp-1)->m_addr = bp->m_addr;
                                } while ((bp-1)->m_size = bp->m_size);
                        }
                        if (addr % CLSIZE)
                                return (0);
                        return (addr);
                }
        }
        return (0);
}
E 2
I 2
D 3
	if (size <= 0 || size > dmmax)
		return (0);
	/*
	 * Search for a piece of the resource map which has enough
	 * free space to accomodate the request.
	 */
	for (bp = ep; bp->m_size; bp++) {
		if (bp->m_size >= size) {
			/*
			 * If allocating from swapmap,
			 * then have to respect interleaving
			 * boundaries.
			 */
			if (nswdev > 1 &&
			    (first = dmmax - bp->m_addr%dmmax) < bp->m_size) {
				if (bp->m_size - first < size)
					continue;
				addr = bp->m_addr + first;
				rest = bp->m_size - first - size;
				bp->m_size = first;
				if (rest)
					rmfree(mp, rest, addr+size);
				return (addr);
E 3
I 3
D 22
	for (row = baserow, i = dmmin; i <= dmbound; i *= 2, row++) {
		for (j = 0; j < nswdev; j++) {
			pb = &buckets[j][row - baserow];
D 7
			wmove(wnd, row, j * (1 + colwidth));
E 7
I 7
			wmove(wnd, row, OFFSET + j * (1 + colwidth));
E 7
			k = MIN(*pb, colwidth);
			if (*pb > colwidth) {
				sprintf(buf, " %d", *pb);
				k -= strlen(buf);
				while (k--)
					waddch(wnd, c);
				waddstr(wnd, buf);
			} else {
				while (k--)
					waddch(wnd, c);
				k = MAX(colwidth - *pb, 0);
				while (k--)
					waddch(wnd, ' ');
E 3
			}
D 3
			/*
			 * Allocate from the map.
			 * If there is no space left of the piece
			 * we allocated from, move the rest of
			 * the pieces to the left.
			 */
			addr = bp->m_addr;
			bp->m_addr += size;
			if ((bp->m_size -= size) == 0) {
				do {
					bp++;
					(bp-1)->m_addr = bp->m_addr;
				} while ((bp-1)->m_size = bp->m_size);
			}
			if (addr % CLSIZE)
				return (0);
			return (addr);
E 3
I 3
			*pb = 0;
E 3
		}
	}
D 3
	return (0);
E 3
I 3
	return (row);
I 18
D 19
#endif NOTDEF
E 19
I 19
#endif
E 19
E 18
E 3
}
E 22
I 22
	s = nswapmap * sizeof(*mp);
	if (kvm_read(kd, (long)kswapmap, mp, s) != s)
		error("cannot read swapmap: %s", kvm_geterr(kd));
E 22
E 2

I 19
D 22
static void
E 19
D 3
/*
 * Free the previously allocated space at addr
 * of size units into the specified map.
 * Sort addr into map and combine on
 * one or both ends if possible.
 */
rmfree(mp, size, addr)
D 2
        struct map *mp;
        long size, addr;
E 2
I 2
	struct map *mp;
	long size, addr;
E 3
I 3
vsacct(dmp)
	register struct dmap *dmp;
E 3
E 2
{
I 18
D 19
#ifdef NOTDEF
E 19
I 19
#ifdef notdef	
E 19
E 18
D 2
        struct mapent *firstbp;
        register struct mapent *bp;
        register int t;
E 2
I 2
D 3
	struct mapent *firstbp;
	register struct mapent *bp;
	register int t;
E 3
I 3
	register swblk_t *ip;
	register int blk = dmmin, index = 0;
E 22
I 22
	/* first entry in map is `struct map'; rest are mapent's */
	swapmap = (struct map *)mp;
	if (nswapmap != swapmap->m_limit - (struct mapent *)kswapmap)
		error("panic: swap: nswapmap goof");
E 22
E 3
E 2

D 2
        /*
         * Both address and size must be
         * positive, or the protocol has broken down.
         */
        if (addr <= 0 || size <= 0)
                goto badrmfree;
        /*
         * Locate the piece of the map which starts after the
         * returned space (or the end of the map).
         */
        firstbp = bp = (struct mapent *)(mp + 1);
        for (; bp->m_addr <= addr && bp->m_size != 0; bp++)
                continue;
        /*
         * If the piece on the left abuts us,
         * then we should combine with it.
         */
        if (bp > firstbp && (bp-1)->m_addr+(bp-1)->m_size >= addr) {
                /*
                 * Check no overlap (internal error).
                 */
                if ((bp-1)->m_addr+(bp-1)->m_size > addr)
                        goto badrmfree;
                /*
                 * Add into piece on the left by increasing its size.
                 */
                (bp-1)->m_size += size;
                /*
                 * If the combined piece abuts the piece on
                 * the right now, compress it in also,
                 * by shifting the remaining pieces of the map over.
                 */
                if (bp->m_addr && addr+size >= bp->m_addr) {
                        if (addr+size > bp->m_addr)
                                goto badrmfree;
                        (bp-1)->m_size += bp->m_size;
                        while (bp->m_size) {
                                bp++;
                                (bp-1)->m_addr = bp->m_addr;
                                (bp-1)->m_size = bp->m_size;
                        }
                }
                goto done;
        }
        /*
         * Don't abut on the left, check for abutting on
         * the right.
         */
        if (addr+size >= bp->m_addr && bp->m_size) {
                if (addr+size > bp->m_addr)
                        goto badrmfree;
                bp->m_addr -= size;
                bp->m_size += size;
                goto done;
        }
        /*
         * Don't abut at all.  Make a new entry
         * and check for map overflow.
         */
        do {
                t = bp->m_addr;
                bp->m_addr = addr;
                addr = t;
                t = bp->m_size;
                bp->m_size = size;
                bp++;
        } while (size = t);
        /*
         * Segment at bp is to be the delimiter;
         * If there is not room for it 
         * then the table is too full
         * and we must discard something.
         */
        if (bp+1 > mp->m_limit) {
                /*
                 * Back bp up to last available segment.
                 * which contains a segment already and must
                 * be made into the delimiter.
                 * Discard second to last entry,
                 * since it is presumably smaller than the last
                 * and move the last entry back one.
                 */
                bp--;
E 2
I 2
D 3
	/*
	 * Both address and size must be
	 * positive, or the protocol has broken down.
	 */
	if (addr <= 0 || size <= 0)
		goto badrmfree;
	/*
	 * Locate the piece of the map which starts after the
	 * returned space (or the end of the map).
	 */
	firstbp = bp = (struct mapent *)(mp + 1);
	for (; bp->m_addr <= addr && bp->m_size != 0; bp++)
		continue;
	/*
	 * If the piece on the left abuts us,
	 * then we should combine with it.
	 */
	if (bp > firstbp && (bp-1)->m_addr+(bp-1)->m_size >= addr) {
		/*
		 * Check no overlap (internal error).
		 */
		if ((bp-1)->m_addr+(bp-1)->m_size > addr)
			goto badrmfree;
		/*
		 * Add into piece on the left by increasing its size.
		 */
		(bp-1)->m_size += size;
		/*
		 * If the combined piece abuts the piece on
		 * the right now, compress it in also,
		 * by shifting the remaining pieces of the map over.
		 */
		if (bp->m_addr && addr+size >= bp->m_addr) {
			if (addr+size > bp->m_addr)
				goto badrmfree;
			(bp-1)->m_size += bp->m_size;
			while (bp->m_size) {
				bp++;
				(bp-1)->m_addr = bp->m_addr;
				(bp-1)->m_size = bp->m_size;
			}
E 3
I 3
D 22
	for (ip = dmp->dm_map; dmp->dm_alloc > 0; ip++) {
		if (ip - dmp->dm_map >= NDMAP) {
			error("vsacct NDMAP");
			break;
E 3
		}
D 3
		goto done;
E 3
I 3
		if (*ip == 0)
			error("vsacct *ip == 0");
		buckets[swatodev(*ip)][index]++;
		dmp->dm_alloc -= blk;
		if (blk < dmmax) {
			blk *= 2;
			index++;
		}
E 3
	}
I 18
D 19
#endif NOTDEF
E 19
I 19
#endif
E 19
E 18
D 3
	/*
	 * Don't abut on the left, check for abutting on
	 * the right.
	 */
	if (addr+size >= bp->m_addr && bp->m_size) {
		if (addr+size > bp->m_addr)
			goto badrmfree;
		bp->m_addr -= size;
		bp->m_size += size;
		goto done;
	}
	/*
	 * Don't abut at all.  Make a new entry
	 * and check for map overflow.
	 */
	do {
		t = bp->m_addr;
		bp->m_addr = addr;
		addr = t;
		t = bp->m_size;
		bp->m_size = size;
		bp++;
	} while (size = t);
	/*
	 * Segment at bp is to be the delimiter;
	 * If there is not room for it 
	 * then the table is too full
	 * and we must discard something.
	 */
	if (bp+1 > mp->m_limit) {
		/*
		 * Back bp up to last available segment.
		 * which contains a segment already and must
		 * be made into the delimiter.
		 * Discard second to last entry,
		 * since it is presumably smaller than the last
		 * and move the last entry back one.
		 */
		bp--;
		overflow[((bp-1)->m_addr % dmmax) / nswdev] += 
		    (bp-1)->m_size;
E 2
#ifdef notdef
D 2
                printf("%s: rmap ovflo, lost [%d,%d)\n", mp->m_name,
                    (bp-1)->m_addr, (bp-1)->m_addr+(bp-1)->m_size);
E 2
I 2
		printf("%s: rmap ovflo, lost [%d,%d)\n", mp->m_name,
		    (bp-1)->m_addr, (bp-1)->m_addr+(bp-1)->m_size);
E 2
#endif
D 2
                bp[-1] = bp[0];
                bp[0].m_size = bp[0].m_addr = 0;
        }
E 2
I 2
		bp[-1] = bp[0];
		bp[0].m_size = bp[0].m_addr = 0;
	}
E 2
done:
D 2
        return;
E 2
I 2
	return;
E 2
badrmfree:
D 2
        ;
#ifdef notdef
        printf("bad rmfree\n");
#endif
E 2
I 2
	printf("bad rmfree\n");
E 3
I 3
}
E 22
I 22
	/*
	 * Count up swap space.
	 */
	nfree = 0;
	bzero(perdev, nswdev * sizeof(*perdev));
	for (mp++; mp->m_addr != 0; mp++) {
		s = mp->m_addr;			/* start of swap region */
		e = mp->m_addr + mp->m_size;	/* end of region */
		nfree += mp->m_size;
E 22

I 19
D 22
static int
E 19
dmtoindex(dm)
	int dm;
{
I 18
D 19
#ifdef NOTDEF
E 19
I 19
#ifdef notdef	
E 19
E 18
	register int i, j;
E 22
I 22
		/*
		 * Swap space is split up among the configured disks.
		 * The first dmmax blocks of swap space some from the
		 * first disk, the next dmmax blocks from the next, 
		 * and so on.  The list of free space joins adjacent
		 * free blocks, ignoring device boundries.  If we want
		 * to keep track of this information per device, we'll
		 * just have to extract it ourselves.
		 */
E 22

D 22
	for (j = 0, i = dmmin; i <= dmmax; i *= 2, j++)
		if (dm <= i)
			return (j);
	error("dmtoindex(%d)", dm);
	return (NDMAP - 1);
I 18
D 19
#endif NOTDEF
E 19
I 19
#endif
E 19
E 18
I 5
}
E 22
I 22
		/* calculate first device on which this falls */
		i = (s / dmmax) % nswdev;
		while (s < e) {		/* XXX this is inefficient */
			int bound = roundup(s + 1, dmmax);
E 22

D 20
static struct nlist nlst[] = {
E 20
I 20
D 21
static struct nlist nl[] = {
E 21
I 21
D 22
static struct nlist namelist[] = {
E 21
E 20
D 18
#define X_PROC          0
D 13
        { "_proc" },
E 13
I 13
	{ "_proc" },
E 13
#define X_NPROC         1
D 13
        { "_nproc" },
E 13
I 13
	{ "_nproc" },
E 13
#define X_USRPTMAP      2
D 13
        { "_Usrptmap" },
E 13
I 13
	{ "_Usrptmap" },
E 13
#define X_USRPT         3
D 13
        { "_usrpt" },
E 13
I 13
	{ "_usrpt" },
E 13
#define X_NSWAP         4
E 18
I 18
#define X_FIRST		0
#define X_NSWAP         0
E 18
D 13
        { "_nswap" },
E 13
I 13
	{ "_nswap" },
E 13
D 18
#define X_DMMIN         5
E 18
I 18
#define X_DMMIN         1
E 18
D 13
        { "_dmmin" },
E 13
I 13
	{ "_dmmin" },
E 13
D 18
#define X_DMMAX         6
E 18
I 18
#define X_DMMAX         2
E 18
D 13
        { "_dmmax" },
E 13
I 13
	{ "_dmmax" },
E 13
D 18
#define	X_DMTEXT	7
E 18
I 18
#define	X_DMTEXT	3
E 18
	{ "_dmtext" },
D 18
#define X_NSWDEV        8
E 18
I 18
#define X_NSWDEV        4
E 18
D 13
        { "_nswdev" },
E 13
I 13
	{ "_nswdev" },
E 13
D 18
#define	X_SWDEVT	9
E 18
I 18
#define	X_SWDEVT	5
E 18
	{ "_swdevt" },
D 18
#define	X_NTEXT		10
E 18
I 18
#define	X_NTEXT		6
E 18
	{ "_ntext" },
D 18
#define	X_TEXT		11
E 18
I 18
#define	X_TEXT		7
E 18
	{ "_text" },
D 13
        { "" }
E 13
I 13
	{ "" }
E 13
};

I 19
int
E 19
initswap()
{
D 13

E 13
D 18
	if (nlst[X_PROC].n_type == 0) {
D 13
		nlist("/vmunix", nlst);
E 13
I 13
		nlist(_PATH_UNIX, nlst);
E 13
		if (nlst[X_PROC].n_type == 0) {
E 18
I 18
D 19
#ifdef NOTDEF
E 19
I 19
#ifdef notdef	
E 19
D 20
	if (nlst[X_FIRST].n_type == 0) {
D 19
		kvm_nlist(nlst);
E 19
I 19
		if (kvm_nlist(kd, nlst)) {
			nlsterr(nlst);
E 20
I 20
D 21
	if (nl[X_FIRST].n_type == 0) {
		if (kvm_nlist(kd, nl)) {
			nlsterr(nl);
E 21
I 21
	if (namelist[X_FIRST].n_type == 0) {
		if (kvm_nlist(kd, namelist)) {
			nlsterr(namelist);
E 21
E 20
			return(0);
E 22
I 22
			if (bound > e)
				bound = e;
			perdev[i] += bound - s;
			if (++i >= nswdev)
				i = 0;
			s = bound;
E 22
		}
E 19
D 20
		if (nlst[X_FIRST].n_type == 0) {
E 20
I 20
D 21
		if (nl[X_FIRST].n_type == 0) {
E 21
I 21
D 22
		if (namelist[X_FIRST].n_type == 0) {
E 21
E 20
E 18
D 13
			error("namelist on /vmunix failed");
E 13
I 13
			error("namelist on %s failed", _PATH_UNIX);
E 13
D 10
			return;
E 10
I 10
			return(0);
E 10
		}
E 22
	}
D 13
        if (nswdev == 0) {
                dmmin = getw(nlst[X_DMMIN].n_value);
                dmmax = getw(nlst[X_DMMAX].n_value);
                dmtext = getw(nlst[X_DMTEXT].n_value);
                nswdev = getw(nlst[X_NSWDEV].n_value);
E 13
I 13
D 22
	if (nswdev == 0) {
D 16
		dmmin = getw(nlst[X_DMMIN].n_value);
		dmmax = getw(nlst[X_DMMAX].n_value);
		dmtext = getw(nlst[X_DMTEXT].n_value);
		nswdev = getw(nlst[X_NSWDEV].n_value);
E 16
I 16
D 18
		dmmin = getword(nlst[X_DMMIN].n_value);
		dmmax = getword(nlst[X_DMMAX].n_value);
		dmtext = getword(nlst[X_DMTEXT].n_value);
		nswdev = getword(nlst[X_NSWDEV].n_value);
E 18
I 18
		NREAD(X_DMMIN, &dmmin, LONG);
		NREAD(X_DMMAX, &dmmax, LONG);
		NREAD(X_DMTEXT, &dmtext, LONG);
		NREAD(X_NSWDEV, &nswdev, LONG);
E 18
E 16
E 13
I 12
		if (nswdev > MAXSWAPDEV)
			nswdev = MAXSWAPDEV;
E 12
		swdevt = (struct swdevt *)calloc(nswdev, sizeof (*swdevt));
D 18
		klseek(kmem, nlst[X_SWDEVT].n_value, L_SET);
		read(kmem, swdevt, nswdev * sizeof (struct swdevt));
D 16
		ntext = getw(nlst[X_NTEXT].n_value);
		textp = getw(nlst[X_TEXT].n_value);
E 16
I 16
		ntext = getword(nlst[X_NTEXT].n_value);
		textp = getword(nlst[X_TEXT].n_value);
E 18
I 18
		NREAD(X_SWDEVT, swdevt, nswdev * sizeof (struct swdevt));
		NREAD(X_NTEXT, &ntext, LONG);
		NREAD(X_TEXT, &textp, LONG);
E 18
E 16
D 13
        }
        if (procp == NULL) {
                procp = getw(nlst[X_PROC].n_value);
                nproc = getw(nlst[X_NPROC].n_value);
        }
E 13
I 13
	}
D 18
	if (procp == NULL) {
D 16
		procp = getw(nlst[X_PROC].n_value);
		nproc = getw(nlst[X_NPROC].n_value);
E 16
I 16
		procp = getword(nlst[X_PROC].n_value);
		nproc = getword(nlst[X_NPROC].n_value);
E 16
	}
E 18
E 13
	if (xtext == NULL)
		xtext = (struct text *)calloc(ntext, sizeof (struct text));
D 18
	if (kprocp == NULL)
D 13
                kprocp = (struct proc *)calloc(nproc, sizeof (struct proc));
        if (usrpt != NULL)
D 10
                return;
E 10
I 10
                return(1);
E 13
I 13
		kprocp = (struct proc *)calloc(nproc, sizeof (struct proc));
	if (usrpt != NULL)
		return(1);
E 13
E 10
	usrpt = (struct pte *)nlst[X_USRPT].n_value;
	Usrptma = (struct pte *)nlst[X_USRPTMAP].n_value;
	if (pt == NULL)
		pt = (struct p_times *)malloc(nproc * sizeof (struct p_times));
E 18
I 10
	return(1);
I 18
D 19
#endif NOTDEF
E 19
I 19
#endif
E 22
E 19
E 18
E 10
}

I 19
void
E 19
D 22
fetchswap()
{
D 13

E 13
D 18
	if (nlst[X_PROC].n_type == 0)
E 18
I 18
D 19
#ifdef NOTDEF
E 19
I 19
#ifdef notdef	
E 19
D 20
	if (nlst[X_FIRST].n_type == 0)
E 20
I 20
D 21
	if (nl[X_FIRST].n_type == 0)
E 21
I 21
	if (namelist[X_FIRST].n_type == 0)
E 21
E 20
E 18
		return;
D 18
	if (kprocp == NULL) {
D 13
                kprocp = (struct proc *)malloc(sizeof (*kprocp) * nproc);
E 13
I 13
		kprocp = (struct proc *)malloc(sizeof (*kprocp) * nproc);
E 13
		if (kprocp == NULL)
			return;
	}
D 13
        lseek(kmem, procp, L_SET);
        if (read(kmem, kprocp, sizeof (struct proc) * nproc) !=
E 13
I 13
	lseek(kmem, procp, L_SET);
	if (read(kmem, kprocp, sizeof (struct proc) * nproc) !=
E 13
	    sizeof (struct proc) * nproc) {
		error("couldn't read proc table");
		return;
	}
E 18
I 18
	/*
	 * TODO - read procs
	 */
E 18
	if (xtext == NULL) {
		xtext = (struct text *)calloc(ntext, sizeof (struct text));
		if (xtext == NULL)
			return;
	}
D 18
	lseek(kmem, textp, L_SET);
	if (read(kmem, xtext, ntext * sizeof (struct text)) !=
	    sizeof (struct text) * ntext)
E 18
I 18
	if (!KREAD(textp, xtext, ntext * sizeof (struct text)))
E 18
		error("couldn't read text table");
I 18
D 19
#endif NOTDEF
E 19
I 19
#endif
E 19
E 18
}

I 19
void
E 22
E 19
D 17
#ifdef vax
char	*devnames[] =
     { "hp", "ht", "up", "rk", "sw", "tm", "ts", "mt", "tu", "ra", "ut",
       "rb", "rx", "rl" };
#endif
I 11
#ifdef tahoe
char	*devnames[] = { "ud", "vd", "xp", "cy", "sw" };
#endif
E 11

E 17
labelswap()
{
I 18
D 19
#ifdef NOTDEF
E 19
I 19
D 22
#ifdef notdef	
E 19
E 18
D 10
	register int i, j;
E 10
	register int row;
E 22
I 22
D 26
	char *header;
E 26
I 26
	char *header, *p;
E 26
	int row, i;
E 22

D 22
	if (nswdev == 0) {
		error("Don't know how many swap devices.\n");
		return;
E 22
I 22
	row = 0;
	wmove(wnd, row, 0); wclrtobot(wnd);
	header = getbsize(&hlen, &blocksize);
	mvwprintw(wnd, row++, 0, "%-5s%*s%9s  %55s",
	    "Disk", hlen, header, "Used",
	    "/0%  /10% /20% /30% /40% /50% /60% /70% /80% /90% /100%");
	for (i = 0; i < nswdev; i++) {
D 26
		mvwprintw(wnd, i + 1, 0, "%-5s",
		    devname(sw[i].sw_dev, S_IFBLK));
E 26
I 26
		p = devname(sw[i].sw_dev, S_IFBLK);
		mvwprintw(wnd, i + 1, 0, "%-5s", p == NULL ? "??" : p);
E 26
E 22
	}
D 7
        move(5, 0);
	colwidth = (70 - (nswdev - 1)) / nswdev;
	row = swaplabel(5, dmtext, 1);
E 7
I 7
D 22
	colwidth = (COLS - OFFSET - (nswdev - 1)) / nswdev;
	row = swaplabel(0, dmtext, 1);
E 7
	(void) swaplabel(row, dmmax, 0);
I 18
D 19
#endif NOTDEF
E 19
I 19
#endif
E 22
E 19
E 18
}

I 19
D 22
static void
E 19
swaplabel(row, dmbound, donames)
	register int row;
	int dmbound, donames;
E 22
I 22
void
showswap()
E 22
{
I 18
D 19
#ifdef NOTDEF
E 19
I 19
D 22
#ifdef notdef	
E 19
E 18
	register int i, j;
E 22
I 22
	int col, row, div, i, j, avail, npfree, used, xsize, xfree;
E 22

I 22
	div = blocksize / 512;
	avail = npfree = 0;
E 22
	for (i = 0; i < nswdev; i++) {
D 7
		if (donames) {
			move(row, 5 + i * (1 + colwidth) + (colwidth - 3) / 2);
			printw("%s%d", devnames[major(swdevt[i].sw_dev)],
			    minor(swdevt[i].sw_dev) >> 3);
		}
		for (j = 0; j + 5 < colwidth; j += 5) {
			move(row + donames, 5 + i * (1 + colwidth) + j);
			printw("/%-2d  ", j);
		}
E 7
I 7
D 22
		if (donames)
			mvwprintw(wnd,
			    row, OFFSET + i*(1 + colwidth) + (colwidth - 3)/2,
D 17
			    "%s%d", devnames[major(swdevt[i].sw_dev)],
			        minor(swdevt[i].sw_dev) >> 3);
E 17
I 17
			    "%s", devname(swdevt[i].sw_dev, S_IFBLK));
E 17
		for (j = 0; j + 5 < colwidth; j += 5)
			mvwprintw(wnd, row + donames,
			    OFFSET + i*(1 + colwidth) + j, "/%-2d  ", j);
E 22
I 22
		col = 5;
		mvwprintw(wnd, i + 1, col, "%*d", hlen, sw[i].sw_nblks / div);
		col += hlen;
		/*
		 * Don't report statistics for partitions which have not
		 * yet been activated via swapon(8).
		 */
		if (!sw[i].sw_freed) {
			mvwprintw(wnd, i + 1, col + 8,
			    "0  *** not available for swapping ***");
			continue;
		}
		xsize = sw[i].sw_nblks;
		xfree = perdev[i];
		used = xsize - xfree;
		mvwprintw(wnd, i + 1, col, "%9d  ", used / div);
		for (j = (100 * used / xsize + 1) / 2; j > 0; j--)
			waddch(wnd, 'X');
		npfree++;
		avail += xsize;
E 22
E 7
	}
D 22
	row += 1 + donames;
	for (j = 0, i = dmmin; i <= dmbound; i *= 2, j++, row++) {
		int k;

D 7
		mvprintw(row, 0, "%4d|", i);
E 7
I 7
		mvwprintw(wnd, row, 0, "%4d|", i);
E 7
		for (k = 1; k < nswdev; k++)
D 7
			mvwaddch(wnd, row - 3, k * (1 + colwidth) - 1, '|');
E 7
I 7
			mvwaddch(wnd, row, OFFSET + k*(1 + colwidth) - 1, '|');
E 22
I 22
	/* 
	 * If only one partition has been set up via swapon(8), we don't
	 * need to bother with totals.
	 */
	if (npfree > 1) {
		used = avail - nfree;
		mvwprintw(wnd, i + 1, 0, "%-5s%*d%9d  ",
		    "Total", hlen, avail / div, used / div);
		for (j = (100 * used / avail + 1) / 2; j > 0; j--)
			waddch(wnd, 'X');
E 22
E 7
	}
D 22
	return (row);
I 18
D 19
#endif NOTDEF
E 19
I 19
#endif
E 22
E 19
E 18
E 5
E 3
E 2
}
E 1
