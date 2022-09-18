h07811
s 00009/00009/00210
d D 8.2 93/09/23 19:37:29 bostic 26 25
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00217
d D 8.1 93/06/06 16:29:31 bostic 25 24
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00218
d D 5.16 93/05/21 15:34:22 mckusick 24 23
c update header to reflect redistributable status
e
s 00005/00004/00214
d D 5.15 93/04/27 18:32:55 bostic 23 22
c <sys/kinfo_proc.h> moved to <sys/sysctl.h>
e
s 00002/00002/00216
d D 5.14 93/03/31 17:16:55 mckusick 22 21
c convert kinfo to sysctl
e
s 00002/00002/00216
d D 5.13 92/11/10 12:24:31 elan 21 20
c Converted to new curses(3) library.
e
s 00007/00008/00211
d D 5.12 92/09/02 11:56:36 bostic 20 19
c nl is an exported curses function
e
s 00006/00006/00213
d D 5.11 92/07/24 12:41:21 bostic 19 18
c rename nlst to nl globally so can use vmstat's names.c; should not
c be a semantic change for any of these files
e
s 00076/00083/00143
d D 5.10 92/07/23 18:09:33 bostic 18 17
c Elan's new kvm version; update copyright/header
c lots of reorganization
e
s 00084/00097/00142
d D 5.9 91/06/26 13:50:27 marc 17 16
c changes for new kernel, plus use kvm
e
s 00002/00003/00237
d D 5.8 91/02/04 23:18:52 torek 16 15
c fix gcc-detected lint
e
s 00002/00001/00238
d D 5.7 89/05/29 17:22:09 mckusick 15 14
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00115/00118/00124
d D 5.6 89/05/11 10:57:52 bostic 14 13
c file reorg, pathnames.h, paths.h; some reformatting
e
s 00000/00001/00242
d D 5.5 86/07/20 10:58:40 sam 13 12
c purge redundant include
e
s 00003/00003/00240
d D 5.4 85/12/11 16:08:07 bloom 12 11
c fix problem with losing /vmunix in the middle, a bit of lint cleanup
e
s 00004/00002/00239
d D 5.3 85/08/13 11:08:24 mckusick 11 10
c do not expand cpu percentages, only compress them
e
s 00022/00003/00219
d D 5.2 85/07/26 18:03:36 mckusick 10 9
c more accurate calculation of idle time
e
s 00011/00001/00211
d D 5.1 85/05/30 16:26:26 mckusick 9 8
c Add copyright
e
s 00000/00003/00212
d D 1.8 85/05/01 01:34:33 sam 8 7
c major rework; fixup netstat stuff; pull disk cmds into common file; change 
c everthing related to disks to use dk_ndrive and global selction; use getw where possible
e
s 00014/00020/00201
d D 1.7 85/04/29 00:42:58 sam 7 6
c cleanup window handling, use subwindows exclusively
e
s 00013/00000/00208
d D 1.6 84/08/09 19:13:01 mckusick 6 5
c update to new sources from sam; weed out unnecessary #includes
e
s 00004/00004/00204
d D 1.5 83/10/02 21:34:00 sam 5 4
c addjust window to display; expand user and process name fields
e
s 00043/00030/00165
d D 1.4 83/10/02 20:45:49 sam 4 3
c reorganize window management to allow display routines to set 
c up optimal window definitions
e
s 00014/00002/00181
d D 1.3 83/10/02 15:09:41 sam 3 2
c add some sanity checks
e
s 00015/00011/00168
d D 1.2 83/10/02 14:40:29 sam 2 1
c add init routine and mbuf display; redo swap space display
e
s 00179/00000/00000
d D 1.1 83/10/01 12:21:02 sam 1 0
c date and time created 83/10/01 12:21:02 by sam
e
u
U
t
T
I 9
D 18
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 18
I 18
/*-
D 25
 * Copyright (c) 1980, 1992 The Regents of the University of California.
 * All rights reserved.
E 25
I 25
 * Copyright (c) 1980, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 25
 *
D 24
 * %sccs.include.proprietary.c%
E 24
I 24
 * %sccs.include.redist.c%
E 24
E 18
 */

E 9
I 1
#ifndef lint
D 7
static char sccsid[] = "%W% (Lucasfilm) %G%";
E 7
I 7
static char sccsid[] = "%W% (Berkeley) %G%";
E 7
D 9
#endif
E 9
I 9
D 18
#endif not lint
E 18
I 18
#endif /* not lint */
E 18

/*
 * Pigs display from Bill Reeves at Lucasfilm
 */
E 9

D 18
#include "systat.h"
E 18
I 18
#include <sys/param.h>
#include <sys/dkstat.h>
E 18
I 6
D 8
#include <sys/param.h>
E 8
#include <sys/dir.h>
#include <sys/time.h>
#include <sys/proc.h>
I 17
D 22
#include <sys/kinfo.h>
E 22
I 22
#include <sys/sysctl.h>
E 22
D 23
#include <sys/kinfo_proc.h>
E 23
I 18

E 18
E 17
I 10
D 13
#include <sys/dk.h>
E 13
E 10
D 8
#include <sys/file.h>
#include <nlist.h>
E 8
D 23
#include <pwd.h>
E 23
I 23
#include <curses.h>
E 23
I 14
D 17
#include <paths.h>
E 17
I 17
D 18
#include <kvm.h>
E 18
I 18
#include <math.h>
D 23
#include <stdlib.h>
E 23
#include <nlist.h>
D 23
#include "systat.h"
E 23
I 23
#include <pwd.h>
#include <stdlib.h>

E 23
#include "extern.h"
I 23
#include "systat.h"
E 23
E 18
E 17
E 14
E 6

I 17
D 18
struct p_times {
	float   pt_pctcpu;
	struct  proc *pt_pp;
E 18
I 18
int compar __P((const void *, const void *));

static int nproc;
static struct p_times {
	float pt_pctcpu;
	struct kinfo_proc *pt_kp;
E 18
} *pt;
D 18
int	ptsize;
int	nproc;
int     fscale;
double  lccpu;
E 18

I 18
static long stime[CPUSTATES];
static int     fscale;
static double  lccpu;
E 18

E 17
I 4
WINDOW *
openpigs()
{
D 7
	static WINDOW *w = NULL;
E 7
D 14

E 14
D 7
	if (w == NULL)
D 5
		w = newwin(20, 70, 3, 5);
E 5
I 5
		w = newwin(20, 0, 3, 0);
E 5
        return (w);
E 7
I 7
	return (subwin(stdscr, LINES-5-1, 0, 5, 0));
E 7
}

I 18
void
E 18
closepigs(w)
	WINDOW *w;
{
D 14

E 14
	if (w == NULL)
		return;
D 7
	move(5, 20);
	clrtobot();
E 7
	wclear(w);
	wrefresh(w);
I 7
	delwin(w);
E 7
}
I 6

D 18
int	maxind;
int     factor;
float   total;
D 16
struct  passwd *getpwuid();
E 16
char    pidname[30];
I 10
long	stime[CPUSTATES];
E 18
D 17
double	idle;
E 17
E 10
E 6

I 18
void
E 18
E 4
showpigs()
{
D 14
        register short auid;
        register int i, j, y;
        register float max;
        register struct p_times *ptptr;
        struct p_times temppt;
        register struct users *knptr;
        char *getpname(), *pnamp;
E 14
I 14
D 18
	register short auid;
	register int i, j, y;
	register float max;
	register struct p_times *ptptr;
D 17
	struct p_times temppt;
	register struct users *knptr;
	char *getpname(), *pnamp;
E 17
I 17
	struct	p_times temppt;
E 18
I 18
	register int i, j, y, k;
E 18
	struct	eproc *ep;
D 18
	char *uname, *pname;
E 18
I 18
	float total;
	int factor;
	char *uname, *pname, pidname[30];
E 18
E 17
E 14

I 4
	if (pt == NULL)
		return;
E 4
D 14
        /* Accumulate the percent of cpu per user. */
        ptptr = pt;
        numprocs = 0;
        total = 0.0;
        for (i = 0; i < nproc; i++) {
                /* discard inactive processes */
                if (ptptr->pt_uid == -1) {
                        ptptr++;
                        continue;
                }
                /* Accumulate the percentage. */
                total += ptptr->pt_pctcpu;
                numprocs++;
                ptptr++;
        }
E 14
I 14
	/* Accumulate the percent of cpu per user. */
D 18
	ptptr = pt;
E 18
D 17
	numprocs = 0;
E 17
	total = 0.0;
D 18
	for (i = 0; i < nproc; i++) {
E 18
I 18
	for (i = 0; i <= nproc; i++) {
E 18
D 17
		/* discard inactive processes */
		if (ptptr->pt_uid == -1) {
			ptptr++;
			continue;
		}
E 17
		/* Accumulate the percentage. */
D 18
		total += ptptr->pt_pctcpu;
D 17
		numprocs++;
E 17
		ptptr++;
E 18
I 18
		total += pt[i].pt_pctcpu;
E 18
	}
E 14

D 10
        pt[numprocs].pt_pctcpu = 1.0 - total;
E 10
I 10
D 11
        pt[numprocs].pt_pctcpu = total / (1.0 - idle) * idle;
	total += pt[numprocs].pt_pctcpu;
E 11
I 11
D 14
        pt[numprocs].pt_pctcpu = idle;
E 14
I 14
D 17
	pt[numprocs].pt_pctcpu = idle;
E 14
	total += idle;
E 11
E 10
D 14
        pt[numprocs].pt_uid = -1;
        pt[numprocs].pt_pid = -1;
        pt[numprocs].pt_pp = NULL;
E 14
I 14
	pt[numprocs].pt_uid = -1;
	pt[numprocs].pt_pid = -1;
	pt[numprocs].pt_pp = NULL;
E 17
I 17
D 18
	total += pt[nproc].pt_pctcpu;	/* idle "process" */
E 17
E 14

E 18
I 11
	if (total < 1.0)
D 18
		total = 1.0;
E 18
I 18
 		total = 1.0;
E 18
E 11
D 10
        if (total < 1.0)
                total = 1.0;
E 10
D 14
        factor = 50.0/total;
E 14
I 14
	factor = 50.0/total;
E 14

D 7
        /* Find the top ten by executing a "bubble pass" ten times. */
        y = numprocs + 1 < 15 ? numprocs + 1 : 15;
E 7
I 7
D 14
        /* Find the top few by executing a "bubble pass" ten times. */
E 14
I 14
D 18
	/* Find the top few by executing a "bubble pass" ten times. */
E 14
D 17
	y = numprocs + 1;
E 17
I 17
	y = nproc + 1;
E 17
	if (y > wnd->_maxy-1)
		y = wnd->_maxy-1;
E 7
D 14
        for (i = 0; i < y; i++) {
                ptptr = &pt[i];
                max = -10000.0;
                maxind = i;
                for (j = i; j < numprocs + 1; j++) {
                        if (ptptr->pt_pctcpu > max) {
                                max = ptptr->pt_pctcpu;
                                maxind = j;
                        }
                        ptptr++;
                }
                if (maxind != i) {
                        temppt = pt[i];
                        pt[i] = pt[maxind];
                        pt[maxind] = temppt;
                }
        }
D 7

        /* Display the top fifteen. */
        y = 4;
E 7
I 7
        y = 1;
E 7
        ptptr = pt;
E 14
I 14
	for (i = 0; i < y; i++) {
		ptptr = &pt[i];
		max = -10000.0;
		maxind = i;
D 17
		for (j = i; j < numprocs + 1; j++) {
E 17
I 17
		for (j = i; j < nproc + 1; j++) {
E 17
			if (ptptr->pt_pctcpu > max) {
				max = ptptr->pt_pctcpu;
				maxind = j;
			}
			ptptr++;
		}
		if (maxind != i) {
			temppt = pt[i];
			pt[i] = pt[maxind];
			pt[maxind] = temppt;
		}
	}
E 18
I 18
        qsort(pt, nproc + 1, sizeof (struct p_times), compar);
E 18
	y = 1;
D 18
	ptptr = pt;
E 18
E 14
D 7
        i = numprocs+1 < 15 ? numprocs+1 : 15;
E 7
I 7
D 17
	i = numprocs + 1;
E 17
I 17
	i = nproc + 1;
E 17
D 21
	if (i > wnd->_maxy-1)
		i = wnd->_maxy-1;
E 21
I 21
	if (i > wnd->maxy-1)
		i = wnd->maxy-1;
E 21
E 7
D 14
        for (; i > 0 && ptptr->pt_pctcpu > 0.01; i--) {
                /* Find the user's name. */
                knptr = known;
                auid = ptptr->pt_uid;
                for (j = numknown - 1; j >= 0; j--) {
                        if (knptr->k_uid == auid) {
                                namp = knptr->k_name;
                                break;
                        }
                        knptr++;
                }
                if (j < 0) {
                        if (numknown < 30) {
                                knptr = &known[numknown];
                                namp = strncpy(knptr->k_name,
                                    getpwuid(auid)->pw_name, 15);
                                knptr->k_name[15] = '\0';
                                knptr->k_uid = auid;
                                numknown++;
                        } else
                                namp = getpwuid(auid)-> pw_name;
                }
                pnamp = getpname(ptptr->pt_pid, ptptr->pt_pp);
                wmove(wnd, y, 0);
                wclrtoeol(wnd);
                mvwaddstr(wnd, y, 0, namp);
D 5
                sprintf(pidname, "%8.8s", pnamp);
                mvwaddstr(wnd, y, 6, pidname);
                wmove(wnd, y++, 15);
E 5
I 5
                sprintf(pidname, "%10.10s", pnamp);
                mvwaddstr(wnd, y, 9, pidname);
                wmove(wnd, y++, 20);
E 5
                for (j = ptptr->pt_pctcpu*factor + 0.5; j > 0; j--)
                        waddch(wnd, 'X');
                ptptr++;
        }
E 14
I 14
D 17
	for (; i > 0 && ptptr->pt_pctcpu > 0.01; i--) {
		/* Find the user's name. */
		knptr = known;
		auid = ptptr->pt_uid;
		for (j = numknown - 1; j >= 0; j--) {
			if (knptr->k_uid == auid) {
				namp = knptr->k_name;
				break;
			}
			knptr++;
E 17
I 17
D 18
	for (; i > 0 && ptptr->pt_pctcpu > 0.01; i--, y++, ptptr++) {
		if (ptptr->pt_pp == NULL) {
E 18
I 18
	for (k = 0; i > 0 && pt[k].pt_pctcpu > 0.01; i--, y++, k++) {
		if (pt[k].pt_kp == NULL) {
E 18
			uname = "";
			pname = "<idle>";
E 17
		}
D 17
		if (j < 0) {
			if (numknown < 30) {
				knptr = &known[numknown];
				namp = strncpy(knptr->k_name,
				    getpwuid(auid)->pw_name, 15);
				knptr->k_name[15] = '\0';
				knptr->k_uid = auid;
				numknown++;
			} else
				namp = getpwuid(auid)-> pw_name;
E 17
I 17
		else {
D 18
			ep = kvm_geteproc(ptptr->pt_pp);
E 18
I 18
			ep = &pt[k].pt_kp->kp_eproc;
E 18
			uname = (char *)user_from_uid(ep->e_ucred.cr_uid, 0);
D 18
			pname = ptptr->pt_pp->p_comm;
E 18
I 18
			pname = pt[k].pt_kp->kp_proc.p_comm;
E 18
E 17
		}
D 17
		pnamp = getpname(ptptr->pt_pid, ptptr->pt_pp);
E 17
		wmove(wnd, y, 0);
		wclrtoeol(wnd);
D 17
		mvwaddstr(wnd, y, 0, namp);
		sprintf(pidname, "%10.10s", pnamp);
E 17
I 17
		mvwaddstr(wnd, y, 0, uname);
		sprintf(pidname, "%10.10s", pname, 0);
E 17
		mvwaddstr(wnd, y, 9, pidname);
D 17
		wmove(wnd, y++, 20);
E 17
I 17
		wmove(wnd, y, 20);
E 17
D 18
		for (j = ptptr->pt_pctcpu*factor + 0.5; j > 0; j--)
E 18
I 18
		for (j = pt[k].pt_pctcpu*factor + 0.5; j > 0; j--)
E 18
			waddch(wnd, 'X');
D 17
		ptptr++;
E 17
	}
E 14
D 7

        while (y < 19) {
                wmove(wnd, y++, 0);
                wclrtoeol(wnd);
        }
E 7
I 7
	wmove(wnd, y, 0); wclrtobot(wnd);
E 7
}

D 4
openpigs()
{

        kmemf = "/dev/kmem";
        kmem = open(kmemf, 0);
        if (kmem < 0) {
                perror(kmemf);
                exit(1);
        }
        memf = "/dev/mem";
        mem = open(memf, 0);
        if (mem < 0) {
                perror(memf);
                exit(1);
        }
        swapf = "/dev/drum";
        swap = open(swapf, 0);
        if (swap < 0) {
                perror(swapf);
                exit(1);
        }
}

/* these don't belong here */
E 4
I 4
D 19
static struct nlist nlst[] = {
E 19
I 19
D 20
static struct nlist nl[] = {
E 20
I 20
static struct nlist namelist[] = {
E 20
E 19
E 4
D 17
#define X_PROC          0
I 4
D 14
        { "_proc" },
E 14
I 14
	{ "_proc" },
E 14
E 4
#define X_NPROC         1
D 4
#define X_USRPTMAP      4
#define X_USRPT         5
E 4
I 4
D 14
        { "_nproc" },
E 14
I 14
	{ "_nproc" },
E 14
#define X_USRPTMAP      2
D 14
        { "_Usrptmap" },
E 14
I 14
	{ "_Usrptmap" },
E 14
#define X_USRPT         3
D 14
        { "_usrpt" },
E 14
I 14
	{ "_usrpt" },
E 14
I 10
#define X_CPTIME	4
E 17
I 17
#define X_FIRST		0
#define X_CPTIME	0
E 17
	{ "_cp_time" },
I 17
#define X_CCPU          1
	{ "_ccpu" },
#define X_FSCALE        2
	{ "_fscale" },

E 17
E 10
D 14
        { "" }
E 14
I 14
	{ "" }
E 14
};
E 4

I 18
int
E 18
D 4
struct proc *kprocp;

E 4
D 2
fetchpigs()
E 2
I 2
initpigs()
E 2
{
D 2
        register int i;
        register struct p_times *prt;
        register float time;
        register struct proc *pp;
E 2
D 14

E 14
I 4
D 17
	if (nlst[X_PROC].n_type == 0) {
D 14
		nlist("/vmunix", nlst);
E 14
I 14
		nlist(_PATH_UNIX, nlst);
E 14
		if (nlst[X_PROC].n_type == 0) {
D 14
			error("namelist on /vmunix failed");
E 14
I 14
			error("namelist on %s failed", _PATH_UNIX);
E 17
I 17
	fixpt_t ccpu;

D 19
	if (nlst[X_FIRST].n_type == 0) {
D 18
		kvm_nlist(nlst);
E 18
I 18
		if (kvm_nlist(kd, nlst)) {
			nlisterr(nlst);
E 19
I 19
D 20
	if (nl[X_FIRST].n_type == 0) {
		if (kvm_nlist(kd, nl)) {
			nlisterr(nl);
E 20
I 20
	if (namelist[X_FIRST].n_type == 0) {
		if (kvm_nlist(kd, namelist)) {
			nlisterr(namelist);
E 20
E 19
		        return(0);
		}
E 18
D 19
		if (nlst[X_FIRST].n_type == 0) {
E 19
I 19
D 20
		if (nl[X_FIRST].n_type == 0) {
E 20
I 20
		if (namelist[X_FIRST].n_type == 0) {
E 20
E 19
			error("namelist failed");
E 17
E 14
D 12
			return;
E 12
I 12
			return(0);
E 12
		}
	}
E 4
D 14
        if (procp == NULL) {
                procp = getw(nlst[X_PROC].n_value);
                nproc = getw(nlst[X_NPROC].n_value);
D 3
                kprocp = (struct proc *)malloc(sizeof (*kprocp) * nproc);
E 3
        }
E 14
I 14
D 17
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
E 14
I 3
	if (kprocp == NULL)
D 14
                kprocp = (struct proc *)calloc(nproc, sizeof (struct proc));
E 3
D 2
        if (usrpt == NULL) {
                usrpt = (struct pte *)nlst[X_USRPT].n_value;
                Usrptma = (struct pte *)nlst[X_USRPTMAP].n_value;
                pt = (struct p_times *)malloc(nproc * sizeof (struct p_times));
                return;
        }
E 2
I 2
        if (usrpt != NULL)
E 14
I 14
		kprocp = (struct proc *)calloc(nproc, sizeof (struct proc));
	if (usrpt != NULL)
E 14
D 12
		return;
E 12
I 12
		return(1);
E 12
	usrpt = (struct pte *)nlst[X_USRPT].n_value;
	Usrptma = (struct pte *)nlst[X_USRPTMAP].n_value;
D 3
	pt = (struct p_times *)malloc(nproc * sizeof (struct p_times));
E 3
I 3
	if (pt == NULL)
		pt = (struct p_times *)calloc(nproc, sizeof (struct p_times));
I 10
	lseek(kmem, (long)nlst[X_CPTIME].n_value, L_SET);
	read(kmem, stime, sizeof stime);
E 17
I 17
	KREAD(NPTR(X_CPTIME), stime, sizeof (stime));
	NREAD(X_CCPU, &ccpu, LONG);
	NREAD(X_FSCALE,  &fscale, LONG);
	lccpu = log((double) ccpu / fscale);

E 17
I 12
	return(1);
E 12
E 10
E 3
}

I 18
void
E 18
fetchpigs()
{
D 14
        register int i;
        register struct p_times *prt;
        register float time;
        register struct proc *pp;
E 14
I 14
	register int i;
D 18
	register struct p_times *prt;
E 18
	register float time;
	register struct proc *pp;
I 18
	register float *pctp;
	struct kinfo_proc *kpp;
E 18
E 14
I 10
	long ctime[CPUSTATES];
D 12
	char buf[25];
E 12
	double t;
I 18
	static int lastnproc = 0;
E 18
E 10

I 4
D 17
	if (nlst[X_PROC].n_type == 0)
E 17
I 17
D 19
	if (nlst[X_FIRST].n_type == 0)
E 19
I 19
D 20
	if (nl[X_FIRST].n_type == 0)
E 20
I 20
	if (namelist[X_FIRST].n_type == 0)
E 20
E 19
E 17
		return;
E 4
I 3
D 17
	if (kprocp == NULL) {
		kprocp = (struct proc *)calloc(nproc, sizeof (struct proc));
		if (kprocp == NULL)
			return;
E 17
I 17
D 18
	kvm_freeprocs();	/* clear previous buffer */
	if ((nproc = kvm_getprocs(KINFO_PROC_ALL, 0)) == -1) {
		error("%s", kvm_geterr());
E 18
I 18
D 20
	if ((kpp = 
	    kvm_getprocs(kd, KINFO_PROC_ALL, 0, &nproc)) == NULL) {
E 20
I 20
D 22
	if ((kpp = kvm_getprocs(kd, KINFO_PROC_ALL, 0, &nproc)) == NULL) {
E 22
I 22
	if ((kpp = kvm_getprocs(kd, KERN_PROC_ALL, 0, &nproc)) == NULL) {
E 22
E 20
		error("%s", kvm_geterr(kd));
E 18
		if (pt)
			free(pt);
D 18
		ptsize = 0;
E 18
		return;
E 17
	}
D 17
	if (pt == NULL) {
		pt = (struct p_times *)calloc(nproc, sizeof (struct p_times));
		if (pt == NULL)
			return;
E 17
I 17
D 18
	/*
	 * The nproc + 1'th entry is for the imaginary "idle"
	 * process to which we attribute the unused part of the cpu
	 */
	if ((nproc + 1) * sizeof (struct p_times) > ptsize) {
		if (pt)
			free(pt);
		ptsize = (nproc + 1) * sizeof (struct p_times);
		if ((pt = (struct p_times *)malloc(ptsize)) == NULL) {
			error("out of memory");
			die();
		}
E 18
I 18
	if (nproc > lastnproc) {
		free(pt);
D 26
		if ((pt = (struct p_times *) malloc 
		    ((nproc + 1) * sizeof(struct p_times))) == NULL) {
		    error("Out of memory");
		    die(0);
	    }

E 26
I 26
		if ((pt =
		    malloc((nproc + 1) * sizeof(struct p_times))) == NULL) {
			error("Out of memory");
			die(0);
		}
E 26
E 18
E 17
	}
I 18
	lastnproc = nproc;
E 18
E 3
E 2
D 14
        prt = pt;
        lseek(kmem, procp, L_SET);
        read(kmem, kprocp, sizeof (struct proc) * nproc);
        for (i = 0, pp = kprocp; i < nproc; i++, pp++) {
                time = pp->p_time;
                if (time == 0 || (pp->p_flag & SLOAD) == 0)
                        continue;
                prt->pt_pid = pp->p_pid;
                prt->pt_pp = pp;
                prt->pt_pctcpu = pp->p_pctcpu / (1.0 - exp(time * lccpu));
                prt->pt_uid = pp->p_uid;
                prt++;
        }
        for (; prt < &pt[nproc]; prt++)
                prt->pt_uid = -1;
E 14
I 14
D 17
	prt = pt;
	lseek(kmem, procp, L_SET);
	read(kmem, kprocp, sizeof (struct proc) * nproc);
	for (i = 0, pp = kprocp; i < nproc; i++, pp++) {
E 17
I 17
	/*
	 * calculate %cpu for each proc
	 */
D 18
	for (prt = pt; (pp = kvm_nextproc()) != NULL; prt++) {
		prt->pt_pp = pp;
E 18
I 18
	for (i = 0; i < nproc; i++) {
		pt[i].pt_kp = &kpp[i];
		pp = &kpp[i].kp_proc;
		pctp = &pt[i].pt_pctcpu;
E 18
E 17
D 26
		time = pp->p_time;
		if (time == 0 || (pp->p_flag & SLOAD) == 0)
E 26
I 26
		time = pp->p_swtime;
		if (time == 0 || (pp->p_flag & P_INMEM) == 0)
E 26
D 17
			continue;
		prt->pt_pid = pp->p_pid;
		prt->pt_pp = pp;
D 15
		prt->pt_pctcpu = pp->p_pctcpu / (1.0 - exp(time * lccpu));
E 15
I 15
		prt->pt_pctcpu = ((double) pp->p_pctcpu / fscale) /
				(1.0 - exp(time * lccpu));
E 15
		prt->pt_uid = pp->p_uid;
		prt++;
E 17
I 17
D 18
			prt->pt_pctcpu = 0;
E 18
I 18
			*pctp = 0;
E 18
		else
D 18
			prt->pt_pctcpu = ((double) pp->p_pctcpu / 
E 18
I 18
			*pctp = ((double) pp->p_pctcpu / 
E 18
					fscale) / (1.0 - exp(time * lccpu));
E 17
	}
D 17
	for (; prt < &pt[nproc]; prt++)
		prt->pt_uid = -1;
E 14
I 10
	lseek(kmem, (long)nlst[X_CPTIME].n_value, L_SET);
	read(kmem, ctime, sizeof ctime);
E 17
I 17
	/*
D 18
	 * and for the imaginary "idle" process, pt[nproc]
E 18
I 18
	 * and for the imaginary "idle" process
E 18
	 */
	KREAD(NPTR(X_CPTIME), ctime, sizeof (ctime));
E 17
	t = 0;
	for (i = 0; i < CPUSTATES; i++)
		t += ctime[i] - stime[i];
	if (t == 0.0)
		t = 1.0;
D 17
	idle = (ctime[CP_IDLE] - stime[CP_IDLE]) / t;
E 17
I 17
D 18
	pt[nproc].pt_pp = NULL;	
E 18
I 18
	pt[nproc].pt_kp = NULL;
E 18
	pt[nproc].pt_pctcpu = (ctime[CP_IDLE] - stime[CP_IDLE]) / t;
E 17
	for (i = 0; i < CPUSTATES; i++)
		stime[i] = ctime[i];
E 10
}

I 18
void
E 18
labelpigs()
{
D 14

E 14
D 4
        move(5, 0);
        clrtoeol();
E 4
I 4
D 7
        move(5, 0); clrtoeol();
E 4
        mvaddstr(5, 20,
E 7
I 7
D 26
	wmove(wnd, 0, 0); wclrtoeol(wnd);
E 26
I 26
	wmove(wnd, 0, 0);
	wclrtoeol(wnd);
E 26
D 14
        mvwaddstr(wnd, 0, 20,
E 7
                "/0   /10  /20  /30  /40  /50  /60  /70  /80  /90  /100");
E 14
I 14
	mvwaddstr(wnd, 0, 20,
	    "/0   /10  /20  /30  /40  /50  /60  /70  /80  /90  /100");
I 18
}

int
compar(a, b)
	const void *a, *b;
{
	return (((struct p_times *) a)->pt_pctcpu >
		((struct p_times *) b)->pt_pctcpu)? -1: 1;
E 18
E 14
}
E 1
