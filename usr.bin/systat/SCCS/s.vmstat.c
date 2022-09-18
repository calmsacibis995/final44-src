h50890
s 00036/00040/00625
d D 8.2 94/01/12 22:14:25 hibler 30 29
c get rid of v_vm_fault, page faults are back under v_faults again
e
s 00002/00002/00663
d D 8.1 93/06/06 16:29:52 bostic 29 28
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00663
d D 5.24 93/05/10 14:01:21 bostic 28 27
c prettiness police
e
s 00001/00001/00664
d D 5.23 93/05/08 18:46:11 mckusick 27 26
c ignore ourselves in the run queue
e
s 00006/00004/00659
d D 5.22 93/03/31 17:16:57 mckusick 26 25
c convert kinfo to sysctl
e
s 00011/00011/00652
d D 5.21 92/09/02 11:56:39 bostic 25 24
c nl is an exported curses function
e
s 00009/00009/00654
d D 5.20 92/07/24 12:41:24 bostic 24 23
c rename nlst to nl globally so can use vmstat's names.c; should not
c be a semantic change for any of these files
e
s 00001/00000/00662
d D 5.19 92/07/23 18:29:52 bostic 23 22
c needs unistd.h
e
s 00088/00076/00574
d D 5.18 92/07/23 18:16:30 bostic 22 21
c Elan's new kvm version; update copyright/header; lots of lint
e
s 00081/00064/00569
d D 5.17 91/08/28 18:38:30 mckusick 21 20
c update for new VM statistics
e
s 00032/00094/00601
d D 5.16 91/08/26 17:06:38 mckusick 20 19
c fix rate calculations
e
s 00000/00001/00695
d D 5.15 91/07/02 17:59:18 marc 19 18
c remove unused reference to pte.h
e
s 00096/00122/00600
d D 5.14 91/06/26 13:50:30 marc 18 17
c changes for new kernel, plus use kvm
e
s 00022/00014/00700
d D 5.13 91/02/04 23:18:41 torek 17 16
c fix gcc-detected lint
e
s 00063/00051/00651
d D 5.12 90/06/24 14:51:01 karels 16 15
c reorganize display to get in more disks
e
s 00010/00009/00692
d D 5.11 89/08/28 20:13:56 karels 15 14
c change pages/2 to kilobytes
e
s 00009/00008/00692
d D 5.10 89/05/11 10:57:57 bostic 14 13
c file reorg, pathnames.h, paths.h; some reformatting
e
s 00010/00007/00690
d D 5.9 87/10/03 13:53:01 karels 13 12
c show software interrupts
e
s 00006/00004/00691
d D 5.8 87/09/15 16:34:03 bostic 12 11
c disk name add/delete fix; bug report 4.3BSD/ucb/87
e
s 00023/00009/00672
d D 5.7 86/07/20 10:57:49 sam 11 10
c increase column width to handle larger memories
e
s 00001/00001/00680
d D 5.6 86/02/14 19:23:39 sam 10 9
c update from monet
e
s 00001/00001/00680
d D 5.5 86/01/12 15:26:29 sam 9 8
c add tahoe
e
s 00018/00008/00663
d D 5.4 85/12/11 16:08:30 bloom 8 7
c fix problem with losing /vmunix in the middle, a bit of lint cleanup
e
s 00045/00056/00626
d D 5.3 85/06/18 20:51:52 sam 7 6
c major rework; fixup netstat stuff; pull disk cmds into common file; change
c everything related to disks to use dk_ndrive and global section; use getw where
c possible
e
s 00409/00575/00273
d D 5.2 85/06/18 20:45:34 sam 6 5
c reorganized to work with systat
e
s 00013/00001/00835
d D 5.1 85/05/31 09:38:01 dist 5 4
c Add copyright
e
s 00013/00002/00823
d D 1.4 85/04/18 18:08:01 mckusick 4 3
c time out when the system clock has died
e
s 00017/00007/00808
d D 1.3 84/10/17 13:35:41 mckusick 3 2
c remember to layout intterupt names when redrawing
e
s 00256/00119/00559
d D 1.2 84/10/15 16:44:10 mckusick 2 1
c cleanups; add column detailing interrupts
e
s 00678/00000/00000
d D 1.1 84/05/12 21:05:25 sam 1 0
c date and time created 84/05/12 21:05:25 by sam
e
u
U
t
T
I 5
D 22
/*
D 16
 * Copyright (c) 1983 Regents of the University of California.
E 16
I 16
 * Copyright (c) 1983, 1989 Regents of the University of California.
E 16
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 22
I 22
/*-
D 29
 * Copyright (c) 1983, 1989, 1992 The Regents of the University of California.
 * All rights reserved.
E 29
I 29
 * Copyright (c) 1983, 1989, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 29
 *
 * %sccs.include.redist.c%
E 22
 */

E 5
I 1
#ifndef lint
I 5
D 6
char copyright[] =
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
 All rights reserved.\n";
#endif not lint

#ifndef lint
E 6
E 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 5
#endif
E 5
I 5
D 22
#endif not lint
E 22
I 22
#endif /* not lint */
E 22
E 5

/*
 * Cursed vmstat -- from Robert Elz.
 */
D 6
#include <curses.h>
#include <signal.h>
#include <nlist.h>
/*					this is STUPID!
#include <sys/time.h>
*/
E 6
I 6

D 22
#include "systat.h"

E 6
#include <ctype.h>
#include <utmp.h>
I 6
D 7
#include <nlist.h>
E 7

E 6
D 7
#include <sys/param.h>
E 7
D 18
#include <sys/vm.h>
E 18
I 18
#include <vm/vm.h>
E 22
I 22
#include <sys/param.h>
#include <sys/dkstat.h>
E 22
D 21
#include <sys/vmmeter.h>
E 21
E 18
D 6
#include <sys/dk.h>
E 6
I 6
D 7
#include <sys/file.h>
E 7
E 6
#include <sys/buf.h>
D 6
#include <vaxuba/ubavar.h>
#include <vaxmba/mbavar.h>
E 6
#include <sys/stat.h>
I 17
#include <sys/time.h>
E 17
D 16
#include <sys/dir.h>
E 16
#include <sys/user.h>
#include <sys/proc.h>
D 6
#include <vax/pte.h>
E 6
D 2
#include <sys/nami.h>
E 2
I 2
#include <sys/namei.h>
I 21
D 26
#include <sys/kinfo.h>
E 26
I 26
#include <sys/sysctl.h>
E 26
I 22
#include <vm/vm.h>
E 22
E 21
E 2

I 22
#include <signal.h>
#include <nlist.h>
#include <ctype.h>
#include <utmp.h>
E 22
I 2
D 6
/*
 * These constants define where the major pieces are laid out
 */
#define PROCSROW	13	/* uses 2 rows and 20 cols */
#define PROCSCOL	 0
#define NAMEIROW	20	/* uses 3 rows and 38 cols */
#define NAMEICOL	 0
#define GRAPHROW	16	/* uses 3 rows and 51 cols */
#define GRAPHCOL	 0
#define GENSTATROW	14	/* uses 8 rows and 11 cols */
#define GENSTATCOL	51
#define INTSROW		 2	/* uses all rows to bottom and 17 cols */
#define INTSCOL		63
#define STATROW		 0	/* uses 1 row and 68 cols */
#define STATCOL		 2
#define PAGEROW		 2	/* uses 11 rows and 26 cols */
#define PAGECOL		36
#define MEMROW		 2	/* uses 4 rows and 31 cols */
#define MEMCOL		 0
#define DISKROW		 7	/* uses 5 rows and 35 cols */
#define DISKCOL		 0
E 6
I 6
D 9
#include <vax/pte.h>
E 9
I 9
D 19
#include <machine/pte.h>
E 19
I 14
#include <paths.h>
I 22
#include <string.h>
#include <stdlib.h>
I 23
#include <unistd.h>
E 23
#include "systat.h"
#include "extern.h"
E 22
E 14
E 9
E 6

I 22
static struct Info {
	long	time[CPUSTATES];
	struct	vmmeter Cnt;
	struct	vmtotal Total;
	long	*dk_time;
	long	*dk_wds;
	long	*dk_seek;
	long	*dk_xfer;
	int	dk_busy;
	struct	nchstats nchstats;
	long	nchcount;
	long	*intrcnt;
} s, s1, s2, z;

#define	cnt s.Cnt
#define oldcnt s1.Cnt
#define	total s.Total
#define	nchtotal s.nchstats
#define	oldnchtotal s1.nchstats

static	enum state { BOOT, TIME, RUN } state = TIME;

static void allocinfo __P((struct Info *));
static void copyinfo __P((struct Info *, struct Info *));
static float cputime __P((int));
static void dinfo __P((int, int));
static void getinfo __P((struct Info *, enum state));
static void putint __P((int, int, int, int));
static void putfloat __P((double, int, int, int, int, int));
static int ucount __P((void));

E 22
I 4
D 6
/*
 * Maximum number of times that the clock may no longer advance.
 */
#define LOOPMAX	10
E 6
I 6
static	int ut;
I 22
static	char buf[26];
static	time_t t;
static	double etime;
static	float hertz;
static	int nintr;
static	long *intrloc;
static	char **intrname;
static	int nextintsrow;
E 22
E 6

I 22
struct	utmp utmp;


E 22
I 6
WINDOW *
openkre()
{

D 14
	ut = open("/etc/utmp", O_RDONLY);
E 14
I 14
	ut = open(_PATH_UTMP, O_RDONLY);
E 14
	if (ut < 0)
		error("No utmp");
D 14
        return (stdscr);
E 14
I 14
	return (stdscr);
E 14
}

I 22
void
E 22
closekre(w)
D 14
        WINDOW *w;
E 14
I 14
	WINDOW *w;
E 14
{

	(void) close(ut);
D 14
        if (w == NULL)
                return;
        wclear(w);
        wrefresh(w);
E 14
I 14
	if (w == NULL)
		return;
	wclear(w);
	wrefresh(w);
E 14
}

E 6
E 4
E 2
D 7
#if DK_NDRIVE > 6
#undef DK_NDRIVE
#define	DK_NDRIVE 6
#endif

D 6
char *fread();
long time();
float cputime();
char *asctime();
struct tm *localtime();
E 6
I 6
char	*fread();
E 7
D 17
long	time();
E 17
D 22
float	cputime();
D 7
char	*asctime();
struct	tm *localtime();
E 7
struct	utmp utmp;
E 22
E 6

D 6
void finish();
void docmd();
struct utmp utmp;

struct nlist name[] = {
E 6
I 6
D 18
static struct nlist name[] = {
E 6
	{ "_cp_time" },
E 18
I 18
D 24
static struct nlist nlst[] = {
E 24
I 24
D 25
static struct nlist nl[] = {
E 25
I 25
static struct nlist namelist[] = {
E 25
E 24
E 18
D 6
#define X_CPTIME 0
E 6
I 6
#define X_CPTIME	0
E 6
D 18
	{ "_rate" },
D 6
#define X_RATE 1
E 6
I 6
#define X_RATE		1
E 6
	{ "_total" },
E 18
I 18
	{ "_cp_time" },
#define X_CNT		1
	{ "_cnt" },
E 18
D 6
#define X_TOTAL 2
	{ "_avenrun" },
#define X_AVENRUN 3
E 6
I 6
#define X_TOTAL		2
E 6
D 18
	{ "_proc" },
D 6
#define X_PROC 4
E 6
I 6
#define X_PROC		3
E 6
	{ "_nproc" },
D 6
#define X_NPROC 5
	{ "_bootime" },
#define X_BOOTIME 6
	{ "_deficit" },
#define X_DEFICIT 7
	{ "_ubdinit" },
#define X_UBDINIT 8
	{ "_mbdinit" },
#define X_MBDINIT 9
E 6
I 6
#define X_NPROC		4
E 6
	{ "_sum" },
D 6
#define X_SUM 10
E 6
I 6
#define X_SUM		5
E 18
I 18
	{ "_total" },
D 22
#define X_VMSTAT	3
	{ "_vm_stat" },
#define	X_DK_BUSY	4
E 22
I 22
#define	X_DK_BUSY	3
E 22
E 18
E 6
	{ "_dk_busy" },
D 6
#define	X_DK_BUSY	11
E 6
I 6
D 18
#define	X_DK_BUSY	6
E 18
I 18
D 22
#define	X_DK_TIME	5
E 22
I 22
#define	X_DK_TIME	4
E 22
E 18
E 6
	{ "_dk_time" },
D 6
#define	X_DK_TIME	12
E 6
I 6
D 18
#define	X_DK_TIME	7
E 18
I 18
D 22
#define	X_DK_XFER	6
E 22
I 22
#define	X_DK_XFER	5
E 22
E 18
E 6
	{ "_dk_xfer" },
D 6
#define	X_DK_XFER	13
E 6
I 6
D 18
#define	X_DK_XFER	8
E 18
I 18
D 22
#define	X_DK_WDS	7
E 22
I 22
#define	X_DK_WDS	6
E 22
E 18
E 6
	{ "_dk_wds" },
D 6
#define	X_DK_WDS	14
E 6
I 6
D 18
#define	X_DK_WDS	9
E 6
	{ "_tk_nin" },
D 6
#define	X_TK_NIN	15
E 6
I 6
#define	X_TK_NIN	10
E 6
	{ "_tk_nout" },
D 6
#define	X_TK_NOUT	16
E 6
I 6
#define	X_TK_NOUT	11
E 18
I 18
D 22
#define	X_DK_SEEK	8
E 22
I 22
#define	X_DK_SEEK	7
E 22
E 18
E 6
	{ "_dk_seek" },
D 6
#define	X_DK_SEEK	17
	{ "_dk_mspw" },
#define	X_DK_MSPW	18
	{ "_hz" },
#define	X_HZ		19
	{ "_phz" },
#define	X_PHZ		20
E 6
I 6
D 18
#define	X_DK_SEEK	12
E 18
I 18
D 22
#define	X_NCHSTATS	9
E 22
I 22
#define	X_NCHSTATS	8
E 22
E 18
E 6
	{ "_nchstats" },
D 6
#define	X_NCHSTATS	21
E 6
I 6
D 18
#define	X_NCHSTATS	13
E 18
I 18
D 22
#define	X_INTRNAMES	10
E 22
I 22
#define	X_INTRNAMES	9
E 22
E 18
E 6
I 2
	{ "_intrnames" },
D 6
#define	X_INTRNAMES	22
E 6
I 6
D 18
#define	X_INTRNAMES	14
E 18
I 18
D 22
#define	X_EINTRNAMES	11
E 22
I 22
#define	X_EINTRNAMES	10
E 22
E 18
E 6
	{ "_eintrnames" },
D 6
#define	X_EINTRNAMES	23
E 6
I 6
D 18
#define	X_EINTRNAMES	15
E 18
I 18
D 22
#define	X_INTRCNT	12
E 22
I 22
#define	X_INTRCNT	11
E 22
E 18
E 6
	{ "_intrcnt" },
D 6
#define	X_INTRCNT	24
E 6
I 6
D 18
#define	X_INTRCNT	16
E 18
I 18
D 22
#define	X_EINTRCNT	13
E 22
I 22
#define	X_EINTRCNT	12
E 22
E 18
E 6
	{ "_eintrcnt" },
D 6
#define	X_EINTRCNT	25
E 6
I 6
D 18
#define	X_EINTRCNT	17
E 18
D 7
#ifdef vax
	{ "_ubdinit" },
#define X_UBDINIT	18
	{ "_mbdinit" },
#define X_MBDINIT	19
#endif
E 6
E 2
	{ 0 },
E 7
I 7
	{ "" },
E 7
};

D 6
struct Info {
	long time[CPUSTATES];
	struct vmmeter Rate;
	struct vmtotal Total;
	struct vmmeter Sum;
	struct forkstat Forkstat;
E 6
I 6
D 22
static struct Info {
	long	time[CPUSTATES];
D 18
	struct	vmmeter Rate;
E 18
I 18
	struct	vmmeter Cnt;
E 18
	struct	vmtotal Total;
D 18
	struct	vmmeter Sum;
	struct	forkstat Forkstat;
E 18
I 18
D 21
	struct	vm_statistics Vmstat;
E 21
E 18
E 6
D 7
	long	dk_time[DK_NDRIVE];
	long	dk_wds[DK_NDRIVE];
	long	dk_seek[DK_NDRIVE];
	long	dk_xfer[DK_NDRIVE];
E 7
I 7
	long	*dk_time;
	long	*dk_wds;
	long	*dk_seek;
	long	*dk_xfer;
E 7
D 6
	float	dk_mspw[DK_NDRIVE];
E 6
	int	dk_busy;
D 18
	long	tk_nin;
	long	tk_nout;
E 18
	struct	nchstats nchstats;
	long	nchcount;
I 2
	long	*intrcnt;
E 2
} s, s1, s2, z;

D 6

E 6
D 18
#define total s.Total
#define sum s.Sum
#define sumold s1.Sum
#define rate s.Rate
E 18
I 18
#define	cnt s.Cnt
#define oldcnt s1.Cnt
#define	total s.Total
D 21
#define	vmstat s.Vmstat
#define	oldvmstat s1.Vmstat
E 21
E 18
#define	nchtotal s.nchstats
#define	oldnchtotal s1.nchstats
D 18
#define oldrate s1.Rate
E 18
D 6
#define X(fld)	{t=s.fld[i]; s.fld[i]-=s1.fld[i]; if(state==TIME) s1.fld[i]=t;}
#define Y(fld)	{t = s.fld; s.fld -= s1.fld; if(state == TIME) s1.fld = t;}
#define Z(fld)	{t = s.nchstats.fld; s.nchstats.fld -= s1.nchstats.fld; \
	if(state == TIME) s1.nchstats.fld = t;}
E 6

D 6
int ut;
int kmem;
int deficit;
double avenrun[3];
long c;
char buf[26];
time_t t;
time_t bootime;
double etime;
int secs;
D 2
int delay = 1;
E 2
I 2
int delay = 5;
E 2
int hz;
int phz;
float hertz;
I 2
int nintr;
I 3
long *intrloc;
char **intrname;
E 6
I 6
static	char buf[26];
static	time_t t;
static	double etime;
static	float hertz;
static	int nintr;
static	long *intrloc;
static	char **intrname;
static	int nextintsrow;
E 6
E 3
E 2

D 6
char dr_name[DK_NDRIVE][10];
enum state { BOOT, TIME, RUN, STOP } state = TIME;
enum { NONE, SOME } dr_state[DK_NDRIVE];
E 6
I 6
static	enum state { BOOT, TIME, RUN } state = TIME;
D 7
static	enum { NONE, SOME } dr_state[DK_NDRIVE];
E 7
E 6

I 17
static void putint(), putfloat(), putrate();
static void getinfo(), allocinfo(), copyinfo(), dinfo();
static int ucount();

E 22
E 17
D 6
char cpuchar[CPUSTATES] = { '=' , '>', '-', ' ' };
char cpuorder[CPUSTATES] = { CP_SYS, CP_USER, CP_NICE, CP_IDLE };
E 6
I 6
/*
 * These constants define where the major pieces are laid out
 */
D 16
#define PROCSROW	13	/* uses 2 rows and 20 cols */
#define PROCSCOL	 0
#define NAMEIROW	20	/* uses 3 rows and 38 cols */
#define NAMEICOL	 0
#define GRAPHROW	16	/* uses 3 rows and 51 cols */
#define GRAPHCOL	 0
D 13
#define GENSTATROW	14	/* uses 8 rows and 11 cols */
E 13
I 13
#define GENSTATROW	14	/* uses 9 rows and 11 cols */
E 13
#define GENSTATCOL	51
#define INTSROW		 2	/* uses all rows to bottom and 17 cols */
#define INTSCOL		63
E 16
#define STATROW		 0	/* uses 1 row and 68 cols */
#define STATCOL		 2
D 16
#define PAGEROW		 2	/* uses 11 rows and 26 cols */
#define PAGECOL		36
E 16
#define MEMROW		 2	/* uses 4 rows and 31 cols */
#define MEMCOL		 0
D 16
#define DISKROW		 7	/* uses 5 rows and 35 cols */
E 16
I 16
#define PAGEROW		 2	/* uses 4 rows and 26 cols */
#define PAGECOL		36
#define INTSROW		 2	/* uses all rows to bottom and 17 cols */
#define INTSCOL		63
#define PROCSROW	 7	/* uses 2 rows and 20 cols */
#define PROCSCOL	 0
D 21
#define VMSTATROW	 7	/* uses 2 rows and 26 cols */
#define VMSTATCOL	25
D 20
#define FILLSTATROW	 7	/* uses 6 rows and 10 cols */
E 20
I 20
#define FILLSTATROW	 7	/* uses 3 rows and 10 cols */
E 20
#define FILLSTATCOL	53
E 21
I 21
#define GENSTATROW	 7	/* uses 2 rows and 30 cols */
#define GENSTATCOL	20
D 30
#define VMSTATROW	 7	/* uses 16 rows and 12 cols */
E 30
I 30
#define VMSTATROW	 7	/* uses 17 rows and 12 cols */
E 30
#define VMSTATCOL	48
E 21
#define GRAPHROW	10	/* uses 3 rows and 51 cols */
#define GRAPHCOL	 0
#define NAMEIROW	14	/* uses 3 rows and 38 cols */
#define NAMEICOL	 0
D 20
#define GENSTATROW	14	/* uses 9 rows and 11 cols */
E 20
I 20
D 21
#define GENSTATROW	11	/* uses 8 rows and 11 cols */
E 20
#define GENSTATCOL	52
E 21
#define DISKROW		18	/* uses 5 rows and 50 cols (for 9 drives) */
E 16
#define DISKCOL		 0
E 6

I 16
#define	DRIVESPACE	 9	/* max # for space */

#if DK_NDRIVE > DRIVESPACE
#define	MAXDRIVES	DRIVESPACE	 /* max # to display */
#else
#define	MAXDRIVES	DK_NDRIVE	 /* max # to display */
#endif

I 22
int
E 22
E 16
D 6
main(argc,argv)
	int argc;
	char **argv;
E 6
I 6
initkre()
E 6
{
D 6
	time_t now, lastime, starttime;
D 4
	int i, l, c;
E 4
I 4
	int i, l, c, loopcnt;
E 4
	int psiz;
	int interv;
	int hits;
	float f1, f2;
I 2
	int inttotal, nextintsrow;
D 3
	long *intrloc;
	char *intrnamebuf, **intrname, *cp, *calloc(), *malloc();
E 3
I 3
	char *intrnamebuf, *cp, *calloc(), *malloc();
E 6
I 6
	char *intrnamebuf, *cp;
	int i;
I 8
	static int once = 0;
E 8
E 6
E 3
E 2

D 6
	if (argc > 1)
		switch (c = argv[1][0] == '-' ? argv[1][1] : argv[1][0]) {

		case 't':
			state = TIME;
			break;

		case 'r':
			state = RUN;
			break;

		case 'b':
			state = BOOT;
			break;

			  case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			delay = c - '0';
			break;

E 6
I 6
D 18
	if (name[0].n_type == 0) {
D 14
		nlist("/vmunix",name);
E 14
I 14
		nlist(_PATH_UNIX,name);
E 14
		if (name[0].n_type == 0) {
E 18
I 18
D 24
	if (nlst[0].n_type == 0) {
D 22
		kvm_nlist(nlst);
E 22
I 22
		if (kvm_nlist(kd, nlst)) {
			nlisterr(nlst);
E 24
I 24
D 25
	if (nl[0].n_type == 0) {
		if (kvm_nlist(kd, nl)) {
			nlisterr(nl);
E 25
I 25
	if (namelist[0].n_type == 0) {
		if (kvm_nlist(kd, namelist)) {
			nlisterr(namelist);
E 25
E 24
			return(0);
		}
E 22
D 24
		if (nlst[0].n_type == 0) {
E 24
I 24
D 25
		if (nl[0].n_type == 0) {
E 25
I 25
		if (namelist[0].n_type == 0) {
E 25
E 24
E 18
			error("No namelist");
D 8
			return;
E 8
I 8
			return(0);
E 8
E 6
		}
D 6
	if ((kmem = open("/dev/kmem",0)) < 0) {
		fprintf(stderr, "No /dev/kmem \n");
		exit(1);
E 6
	}
D 6

	if ((ut = open("/etc/utmp", 0)) < 0) {
		fprintf(stderr, "No utmp\n");
		exit(1);
	}

	nlist("/vmunix",name);
	if (name[0].n_type == 0) {
		fprintf(stderr, "No namelist\n");
		exit(1);
	}
	lseek(kmem, (long)name[X_HZ].n_value, 0);
	read(kmem, &hz, sizeof hz);
	lseek(kmem, (long)name[X_PHZ].n_value, 0);
	read(kmem, &phz, sizeof phz);
E 6
D 22
	hertz = phz ? phz : hz;
E 22
I 22
	hertz = stathz ? stathz : hz;
E 22
D 6
	lseek(kmem, (long)name[X_DK_MSPW].n_value, 0);
	read(kmem, s.dk_mspw, sizeof s.dk_mspw);
E 6
I 6
D 7
	if (ndrives == 0) {
#ifdef vax
                read_names(name[X_MBDINIT].n_value, name[X_UBDINIT].n_value);
#endif
E 7
I 7
D 8
	dkinit();
	if (dk_ndrive) {
E 8
I 8
	if (! dkinit())
		return(0);
	if (dk_ndrive && !once) {
E 8
#define	allocate(e, t) \
    s./**/e = (t *)calloc(dk_ndrive, sizeof (t)); \
    s1./**/e = (t *)calloc(dk_ndrive, sizeof (t)); \
    s2./**/e = (t *)calloc(dk_ndrive, sizeof (t)); \
    z./**/e = (t *)calloc(dk_ndrive, sizeof (t));
		allocate(dk_time, long);
		allocate(dk_wds, long);
		allocate(dk_seek, long);
		allocate(dk_xfer, long);
I 8
		once = 1;
E 8
#undef allocate
E 7
	}
E 6
D 7
	for (i = 0; i < DK_NDRIVE; i++)
D 6
		if (s.dk_mspw[i] == 0.0)
E 6
I 6
		if (dk_mspw[i] == 0.0)
E 6
			dr_state[i] = NONE;
		else
			dr_state[i] = SOME;
E 7
D 6
	read_names();

D 2
	initscr();
	signal(SIGINT, finish);
	noecho();
	crmode();
	layout();
E 2
I 2
	nintr = (name[X_EINTRCNT].n_value -
		name[X_INTRCNT].n_value) / sizeof(long);
	intrloc = (long *) calloc(nintr, sizeof(long));
	intrname = (char **) calloc(nintr, sizeof(long));
	intrnamebuf = malloc(name[X_EINTRNAMES].n_value -
		name[X_INTRNAMES].n_value);
	if (intrnamebuf == NULL || intrname == NULL || intrloc == NULL) {
		fprintf(stderr, "vsta: out of memory\n");
		exit(1);
	}
	lseek(kmem, (long)name[X_INTRNAMES].n_value, 0);
	read(kmem, intrnamebuf, name[X_EINTRNAMES].n_value -
		name[X_INTRNAMES].n_value);
	for (cp = intrnamebuf, i = 0; i < nintr; i++) {
		intrname[i] = cp;
		cp += strlen(cp) + 1;
	}
	nextintsrow = INTSROW + 2;
	allocinfo(&s);
	allocinfo(&s1);
	allocinfo(&s2);
	allocinfo(&z);
E 2

	time(&lastime);
	starttime = lastime;
	getinfo(&s2, RUN);
D 2
	if (state == RUN)
		s1 = s2;
/*			if included, this starts TIME at zeroes, else == boot
	else if (state == TIME)
		getinfo(&s1, TIME)
*/
E 2
I 2
	switch (state) {
	case RUN:
		copyinfo(&s2, &s1);
		break;
	case TIME:
		getinfo(&s1, TIME);
		break;
	case BOOT:
		copyinfo(&z, &s1);
		break;
	default:
		fprintf(stderr, "vsta: bad state %d\n", state);
		exit(3);
		break;
	}
E 2
	lseek(kmem, (long)name[X_BOOTIME].n_value, 0);
	read(kmem, &bootime, sizeof bootime);
I 2

	initscr();
	signal(SIGINT, finish);
	noecho();
	crmode();
	layout();

E 2
D 4
	for (;;) {
E 4
I 4
	for (loopcnt = 0; loopcnt < LOOPMAX; loopcnt++) {
E 4
		while (state == STOP)
			waittty(delay*10);
		time(&now);
		strcpy(buf, ctime(&now));
		buf[16] = '\0';
		getinfo(&s, state);
		for (i = 0; i < DK_NDRIVE; i++) {
			X(dk_xfer); X(dk_seek); X(dk_wds); X(dk_time);
E 6
I 6
	if (nintr == 0) {
D 18
		nintr = (name[X_EINTRCNT].n_value -
			name[X_INTRCNT].n_value) / sizeof (long);
E 18
I 18
D 24
		nintr = (nlst[X_EINTRCNT].n_value -
			nlst[X_INTRCNT].n_value) / sizeof (long);
E 24
I 24
D 25
		nintr = (nl[X_EINTRCNT].n_value -
			nl[X_INTRCNT].n_value) / sizeof (long);
E 24
E 18
		intrloc = (long *) calloc(nintr, sizeof (long));
		intrname = (char **) calloc(nintr, sizeof (long));
D 18
		intrnamebuf = malloc(name[X_EINTRNAMES].n_value -
			name[X_INTRNAMES].n_value);
E 18
I 18
D 22
		intrnamebuf = malloc(nlst[X_EINTRNAMES].n_value -
E 22
I 22
D 24
		intrnamebuf = (char *) malloc(nlst[X_EINTRNAMES].n_value -
E 22
			nlst[X_INTRNAMES].n_value);
E 24
I 24
		intrnamebuf = (char *) malloc(nl[X_EINTRNAMES].n_value -
			nl[X_INTRNAMES].n_value);
E 25
I 25
		nintr = (namelist[X_EINTRCNT].n_value -
			namelist[X_INTRCNT].n_value) / sizeof (long);
		intrloc = calloc(nintr, sizeof (long));
		intrname = calloc(nintr, sizeof (long));
		intrnamebuf = malloc(namelist[X_EINTRNAMES].n_value -
			namelist[X_INTRNAMES].n_value);
E 25
E 24
E 18
		if (intrnamebuf == 0 || intrname == 0 || intrloc == 0) {
			error("Out of memory\n");
D 8
			return;
E 8
I 8
			if (intrnamebuf)
				free(intrnamebuf);
			if (intrname)
				free(intrname);
			if (intrloc)
				free(intrloc);
			nintr = 0;
			return(0);
E 8
E 6
		}
D 6
		Y(tk_nin); Y(tk_nout);
		etime = 0;
D 3
		for(i=0; i<CPUSTATES; i++) {
E 3
I 3
		for(i = 0; i < CPUSTATES; i++) {
E 3
			X(time);
			etime += s.time[i];
E 6
I 6
D 18
		lseek(kmem, (long)name[X_INTRNAMES].n_value, L_SET);
		read(kmem, intrnamebuf, name[X_EINTRNAMES].n_value -
			name[X_INTRNAMES].n_value);
E 18
I 18
		NREAD(X_INTRNAMES, intrnamebuf, NVAL(X_EINTRNAMES) -
			NVAL(X_INTRNAMES));
E 18
		for (cp = intrnamebuf, i = 0; i < nintr; i++) {
			intrname[i] = cp;
			cp += strlen(cp) + 1;
E 6
		}
D 6
		if (etime < 5.0)	/* < 5 ticks - ignore this trash */
			continue;
I 4
		loopcnt = 0;
E 4
D 2
	/*
		if (etime == 0.0)
			etime = 1.0;
	*/
E 2
		etime /= hertz;
I 2
		inttotal = 0;
		for (i = 0; i < nintr; i++) {
			if (s.intrcnt[i] == 0)
				continue;
			if (intrloc[i] == 0) {
				if (nextintsrow == LINES)
					continue;
				intrloc[i] = nextintsrow++;
				mvprintw(intrloc[i], INTSCOL + 9, "%-8.8s",
					intrname[i]);
			}
			X(intrcnt);
			l = (int)((float)s.intrcnt[i]/etime + 0.5);
			inttotal += l;
			putint(l, intrloc[i], INTSCOL, 8);
		}
		putint(inttotal, INTSROW + 1, INTSCOL, 8);
E 2
		Z(ncs_goodhits); Z(ncs_badhits); Z(ncs_miss);
		Z(ncs_long); Z(ncs_pass2); Z(ncs_2passes);
		s.nchcount = nchtotal.ncs_goodhits + nchtotal.ncs_badhits +
		    nchtotal.ncs_miss + nchtotal.ncs_long;
		if (state == TIME)
			s1.nchcount = s.nchcount;

		psiz = 0;
		f2 = 0.0;
D 3
		for (c=0; c<CPUSTATES; c++) {
E 3
I 3
		for (c = 0; c < CPUSTATES; c++) {
E 3
			i = cpuorder[c];
			f1 = cputime(i);
			f2 += f1;
			l = (int) ((f2 + 1.0) / 2.0) - psiz;
D 2
			putfloat(f1, 15, 10 + 11*c, 4, 1, 0);
			move(17, 5+psiz);
E 2
I 2
D 3
			putfloat(f1, GRAPHROW, GRAPHCOL + 5 + 11*c, 4, 1, 0);
E 3
I 3
			if (c == 0)
				putfloat(f1, GRAPHROW, GRAPHCOL + 1, 5, 1, 0);
			else
				putfloat(f1, GRAPHROW, GRAPHCOL + 12 * c,
					5, 1, 0);
E 3
			move(GRAPHROW + 2, psiz);
E 2
			psiz += l;
			while (l-- > 0)
				addch(cpuchar[c]);
		}
D 2
	
		putint(ucount(), 1, 1, 3);
		putfloat(avenrun[0], 1, 18, 6, 2, 0);
		putfloat(avenrun[1], 1, 24, 6, 2, 0);
		putfloat(avenrun[2], 1, 30, 6, 2, 0);
		mvaddstr(1, 58, buf);
		putint(total.t_arm/2, 5, 5, 5);
		putint(total.t_armtxt/2, 5, 10, 5);
		putint(total.t_avm/2, 5, 15, 5);
		putint(total.t_avmtxt/2, 5, 20, 5);
		putint(total.t_rm/2, 6, 5, 5);
		putint(total.t_rmtxt/2, 6, 10, 5);
		putint(total.t_vm/2, 6, 15, 5);
		putint(total.t_vmtxt/2, 6, 20, 5);
		putint(total.t_free/2, 5, 27, 5);
		putint(total.t_rq, 17, 62, 3);
		putint(total.t_pw, 17, 65, 3);
		putint(total.t_dw, 17, 68, 3);
		putint(total.t_sl, 17, 71, 3);
		putint(total.t_sw, 17, 74, 3);
		putrate(rate.v_swtch, oldrate.v_swtch, 3, 75, 4);
		putrate(rate.v_trap, oldrate.v_trap, 4, 75, 4);
		putrate(rate.v_syscall, oldrate.v_syscall, 5, 75, 4);
		putrate(rate.v_intr, oldrate.v_intr, 6, 75, 4);
		putrate(rate.v_pdma, oldrate.v_pdma, 7, 75, 4);
		putrate(rate.v_faults, oldrate.v_faults, 8, 75, 4);
		putrate(rate.v_scan, oldrate.v_scan, 9, 75, 4);
		putrate(rate.v_rev, oldrate.v_rev, 10, 75, 4);
		putrate(rate.v_pgin, oldrate.v_pgin, 5, 45, 5);
		putrate(rate.v_pgout, oldrate.v_pgout, 5, 50, 5);
		putrate(rate.v_swpin, oldrate.v_swpin, 5, 55, 5);
		putrate(rate.v_swpout, oldrate.v_swpout, 5, 60, 5);
		putrate(rate.v_pgpgin, oldrate.v_pgpgin, 6, 45, 5);
		putrate(rate.v_pgpgout, oldrate.v_pgpgout, 6, 50, 5);
		putrate(rate.v_pswpin, oldrate.v_pswpin, 6, 55, 5);
		putrate(rate.v_pswpout, oldrate.v_pswpout, 6, 60, 5);
		putrate(rate.v_pgrec, oldrate.v_pgrec, 9, 40, 3);
		putrate(rate.v_intrans, oldrate.v_intrans, 9, 44, 2);
		putrate(rate.v_xsfrec, oldrate.v_xsfrec, 9, 47, 3);
		putrate(rate.v_xifrec, oldrate.v_xifrec, 9, 51, 3);
		putrate(rate.v_pgfrec, oldrate.v_pgfrec, 9, 55, 3);
		putrate(rate.v_dfree, oldrate.v_dfree, 9, 59, 3);
		putrate(rate.v_seqfree, oldrate.v_seqfree, 9, 63, 3);
		putrate(rate.v_zfod, oldrate.v_zfod, 11, 40, 8);
		putrate(rate.v_nzfod, oldrate.v_nzfod, 12, 40, 8);
		putrate(rate.v_exfod, oldrate.v_exfod, 11, 54, 8);
		putrate(rate.v_nexfod, oldrate.v_nexfod, 12, 54, 8);
E 2
I 2

		putint(ucount(), STATROW, STATCOL, 3);
		putfloat(avenrun[0], STATROW, STATCOL + 17, 6, 2, 0);
		putfloat(avenrun[1], STATROW, STATCOL + 23, 6, 2, 0);
		putfloat(avenrun[2], STATROW, STATCOL + 29, 6, 2, 0);
		mvaddstr(STATROW, STATCOL + 53, buf);
		putint(total.t_arm/2, MEMROW + 2, MEMCOL + 4, 5);
		putint(total.t_armtxt/2, MEMROW + 2, MEMCOL + 9, 5);
		putint(total.t_avm/2, MEMROW + 2, MEMCOL + 14, 5);
		putint(total.t_avmtxt/2, MEMROW + 2, MEMCOL + 19, 5);
		putint(total.t_rm/2, MEMROW + 3, MEMCOL + 4, 5);
		putint(total.t_rmtxt/2, MEMROW + 3, MEMCOL + 9, 5);
		putint(total.t_vm/2, MEMROW + 3, MEMCOL + 14, 5);
		putint(total.t_vmtxt/2, MEMROW + 3, MEMCOL + 19, 5);
		putint(total.t_free/2, MEMROW + 2, MEMCOL + 26, 5);
		putint(total.t_rq, PROCSROW + 1, PROCSCOL + 5, 3);
		putint(total.t_pw, PROCSROW + 1, PROCSCOL + 8, 3);
		putint(total.t_dw, PROCSROW + 1, PROCSCOL + 11, 3);
		putint(total.t_sl, PROCSROW + 1, PROCSCOL + 14, 3);
		putint(total.t_sw, PROCSROW + 1, PROCSCOL + 17, 3);
		putrate(rate.v_swtch, oldrate.v_swtch, 
			GENSTATROW, GENSTATCOL, 7);
		putrate(rate.v_trap, oldrate.v_trap, 
			GENSTATROW + 1, GENSTATCOL, 7);
		putrate(rate.v_syscall, oldrate.v_syscall, 
			GENSTATROW + 2, GENSTATCOL, 7);
		putrate(rate.v_intr, oldrate.v_intr, 
			GENSTATROW + 3, GENSTATCOL, 7);
		putrate(rate.v_pdma, oldrate.v_pdma, 
			GENSTATROW + 4, GENSTATCOL, 7);
		putrate(rate.v_faults, oldrate.v_faults, 
			GENSTATROW + 5, GENSTATCOL, 7);
		putrate(rate.v_scan, oldrate.v_scan, 
			GENSTATROW + 6, GENSTATCOL, 7);
		putrate(rate.v_rev, oldrate.v_rev, 
			GENSTATROW + 7, GENSTATCOL, 7);
		putrate(rate.v_pgin, oldrate.v_pgin, PAGEROW + 2,
			PAGECOL + 5, 5);
		putrate(rate.v_pgout, oldrate.v_pgout, PAGEROW + 2,
			PAGECOL + 10, 5);
		putrate(rate.v_swpin, oldrate.v_swpin, PAGEROW + 2,
			PAGECOL + 15, 5);
		putrate(rate.v_swpout, oldrate.v_swpout, PAGEROW + 2,
			PAGECOL + 20, 5);
		putrate(rate.v_pgpgin, oldrate.v_pgpgin, PAGEROW + 3,
			PAGECOL + 5, 5);
		putrate(rate.v_pgpgout, oldrate.v_pgpgout, PAGEROW + 3,
			PAGECOL + 10, 5);
		putrate(rate.v_pswpin, oldrate.v_pswpin, PAGEROW + 3,
			PAGECOL + 15, 5);
		putrate(rate.v_pswpout, oldrate.v_pswpout, PAGEROW + 3,
			PAGECOL + 20, 5);
		putrate(rate.v_pgrec, oldrate.v_pgrec, PAGEROW + 6, PAGECOL, 3);
		putrate(rate.v_intrans, oldrate.v_intrans, PAGEROW + 6,
			PAGECOL + 4, 2);
		putrate(rate.v_xsfrec, oldrate.v_xsfrec, PAGEROW + 6,
			PAGECOL + 7, 3);
		putrate(rate.v_xifrec, oldrate.v_xifrec, PAGEROW + 6,
			PAGECOL + 11, 3);
		putrate(rate.v_pgfrec, oldrate.v_pgfrec, PAGEROW + 6,
			PAGECOL + 15, 3);
		putrate(rate.v_dfree, oldrate.v_dfree, PAGEROW + 6,
			PAGECOL + 19, 3);
		putrate(rate.v_seqfree, oldrate.v_seqfree, PAGEROW + 6,
			PAGECOL + 23, 3);
		putrate(rate.v_zfod, oldrate.v_zfod, PAGEROW + 8, PAGECOL, 8);
		putrate(rate.v_nzfod, oldrate.v_nzfod, PAGEROW + 9, PAGECOL, 8);
		putrate(rate.v_exfod, oldrate.v_exfod, PAGEROW + 8,
			PAGECOL + 14, 8);
		putrate(rate.v_nexfod, oldrate.v_nexfod, PAGEROW + 9,
			PAGECOL + 14, 8);
E 2
		putfloat (
			rate.v_nzfod == 0 ?
				0.0
			: state != RUN ?
				( 100.0 * rate.v_zfod / rate.v_nzfod )
			: rate.v_nzfod == oldrate.v_nzfod ?
				0.0
			:
				( 100.0 * (rate.v_zfod-oldrate.v_zfod)
				/ (rate.v_nzfod-oldrate.v_nzfod) )
D 2
			, 13
			, 40
E 2
I 2
			, PAGEROW + 10
			, PAGECOL
E 2
			, 8
			, 2
			, 1
		);
		putfloat (
			rate.v_nexfod == 0 ?
				0.0
			: state != RUN ?
				( 100.0 * rate.v_exfod / rate.v_nexfod )
			: rate.v_nexfod == oldrate.v_nexfod ?
				0.0
			:
				( 100.0 * (rate.v_exfod-oldrate.v_exfod)
				/ (rate.v_nexfod-oldrate.v_nexfod) )
D 2
			, 13
			, 54
E 2
I 2
			, PAGEROW + 10
			, PAGECOL + 14
E 2
			, 8
			, 2
			, 1
		);
		c = 1;
		for (i = 0; i < DK_NDRIVE; i++)
			if (dr_state[i] == SOME)
D 2
				dinfo(i, c++*5);
E 2
I 2
				dinfo(i, c++);
E 2

D 2
		putint(s.nchcount, 21, 6, 5);
		putint(nchtotal.ncs_goodhits, 21, 14, 4);
E 2
I 2
		putint(s.nchcount, NAMEIROW + 2, NAMEICOL, 9);
		putint(nchtotal.ncs_goodhits, NAMEIROW + 2, NAMEICOL + 9, 9);
E 2
#define nz(x)	((x) ? (x) : 1)
		putfloat(nchtotal.ncs_goodhits * 100.0 / nz(s.nchcount),
D 2
		   21, 19, 4, 0, 1);
		putint(nchtotal.ncs_pass2, 21, 28, 4);
E 2
I 2
		   NAMEIROW + 2, NAMEICOL + 19, 4, 0, 1);
		putint(nchtotal.ncs_pass2, NAMEIROW + 2, NAMEICOL + 23, 9);
E 2
		putfloat(nchtotal.ncs_pass2 * 100.0 / nz(s.nchcount),
D 2
		   21, 34, 4, 0, 1);
E 2
I 2
		   NAMEIROW + 2, NAMEICOL + 34, 4, 0, 1);
E 2
#undef nz
		move(LINES-1,0);
		refresh();
		waittty(delay);
E 6
I 6
		nextintsrow = INTSROW + 2;
		allocinfo(&s);
		allocinfo(&s1);
		allocinfo(&s2);
		allocinfo(&z);
E 6
	}
I 4
D 6
	clear();
	mvprintw(2, 10, "THE SYSTEM CLOCK HAS DIED!");
	refresh();
	sleep(5);
	finish();
E 6
I 6
	getinfo(&s2, RUN);
	copyinfo(&s2, &s1);
I 8
	return(1);
E 8
E 6
E 4
}

I 22
void
E 22
D 6
/* calculate number of users on the system */
ucount()
E 6
I 6
fetchkre()
E 6
{
D 6
	register int nusers = 0;
E 6
I 6
	time_t now;
E 6

D 6
	while (read(ut, &utmp, sizeof(utmp)))
		if (utmp.ut_name[0] != '\0')
			nusers++;

	lseek(ut, 0L, 0);
	return(nusers);
E 6
I 6
	time(&now);
	strcpy(buf, ctime(&now));
	buf[16] = '\0';
	getinfo(&s, state);
E 6
}

I 22
void
E 22
I 7
D 16
#define	MAXDRIVES	6		/* max # to display */

E 16
E 7
D 6
float
cputime(indx)
int indx;
E 6
I 6
labelkre()
E 6
{
D 6
	double t;
	register i;

	t = 0;
D 3
	for (i=0; i<CPUSTATES; i++)
E 3
I 3
	for (i = 0; i < CPUSTATES; i++)
E 3
		t += s.time[i];
	if (t == 0.0)
		t = 1.0;
	return(s.time[indx] * 100.0 / t);
}

void
finish()
{
	mvcur(0, COLS-1, LINES-1, 0);
	endwin();
	exit(0);

}

waittty(period)
{
	int inbits = 1 << 0;
	struct timeval tv;

	tv.tv_usec = 0;
	tv.tv_sec = period;

	select(32, &inbits, 0, 0, &tv);
	if (inbits & (1 << 0))
		docmd();
}

void
docmd()
{
	int c;
	static enum state oldstate;

	c = getchar() & 0177;

	switch ( c ) {
		  case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		delay = c - '0';
		state = TIME;
		break;
	case 'r':
D 2
		s1 = s2;
E 2
I 2
		copyinfo(&s2, &s1);
E 2
		state = RUN;
		break;
	case 'b':
		state = BOOT;
D 2
		s1 = z;
E 2
I 2
		copyinfo(&z, &s1);
E 2
		break;
	case 't':
		state = TIME;
		break;
	case 'l': case 'l'&037:
		layout();
		if (state == STOP)
			state = oldstate;
		break;
	case 'z':
		if (state == RUN)
			getinfo(&s1, RUN);
		else if (state == STOP)
			state = oldstate;
		break;
	case 'q': case 0177:
		finish();
		/* NOTREACHED */
	case ' ': case '0':
		if (state == STOP) {
			state = oldstate;
			break;
		}
		oldstate = state;
		state = STOP;
		break;

	default:
		if (state == STOP)
			state = oldstate;
	}
}

layout()
{
E 6
D 28
	register i, j;
E 28
I 28
	register int i, j;
E 28

	clear();
D 2
	mvprintw(1, 5, "users    Load");
	mvprintw(3, 1, "Mem     REAL    VIRTUAL ");
	mvprintw(4, 1, "      Tot Text  Tot Text");
	mvprintw(5, 1, "Act");
	mvprintw(6, 1, "All");
E 2
I 2
	mvprintw(STATROW, STATCOL + 4, "users    Load");
D 11
	mvprintw(MEMROW, MEMCOL, "Mem     REAL    VIRTUAL ");
	mvprintw(MEMROW + 1, MEMCOL, "      Tot Text  Tot Text");
E 11
I 11
D 21
	mvprintw(MEMROW, MEMCOL, "Mem     REAL     VIRTUAL");
	mvprintw(MEMROW + 1, MEMCOL, "      Tot Text   Tot Text");
E 21
I 21
	mvprintw(MEMROW, MEMCOL, "Mem:KB  REAL        VIRTUAL");
	mvprintw(MEMROW + 1, MEMCOL, "      Tot Share    Tot  Share");
E 21
E 11
	mvprintw(MEMROW + 2, MEMCOL, "Act");
	mvprintw(MEMROW + 3, MEMCOL, "All");
E 2

D 2
	mvprintw(4, 28, "Free");
E 2
I 2
D 11
	mvprintw(MEMROW + 1, MEMCOL + 27, "Free");
E 11
I 11
D 21
	mvprintw(MEMROW + 1, MEMCOL + 28, "Free");
E 21
I 21
	mvprintw(MEMROW + 1, MEMCOL + 31, "Free");
E 21
E 11
E 2

D 2
	mvprintw(3, 40, "        PAGING    SWAPING ");
	mvprintw(4, 40, "        in  out   in  out ");
	mvprintw(5, 40, "count");
	mvprintw(6, 40, "pages");
E 2
I 2
D 16
	mvprintw(PAGEROW, PAGECOL, "        PAGING    SWAPING ");
E 16
I 16
	mvprintw(PAGEROW, PAGECOL,     "        PAGING   SWAPPING ");
E 16
	mvprintw(PAGEROW + 1, PAGECOL, "        in  out   in  out ");
	mvprintw(PAGEROW + 2, PAGECOL, "count");
	mvprintw(PAGEROW + 3, PAGECOL, "pages");
E 2

D 2
	mvprintw( 3, 71, "Csw");
	mvprintw( 4, 71, "Trp");
	mvprintw( 5, 71, "Sys");
	mvprintw( 6, 71, "Int");
	mvprintw( 7, 71, "Pdm");
	mvprintw( 8, 71, "Flt");
	mvprintw( 9, 71, "Scn");
	mvprintw(10, 71, "Rev");
E 2
I 2
D 16
	mvprintw(INTSROW, INTSCOL, " Interrupts");
E 16
I 16
	mvprintw(INTSROW, INTSCOL + 3, " Interrupts");
E 16
	mvprintw(INTSROW + 1, INTSCOL + 9, "total");
E 2

D 2
	mvprintw(8, 40, "Rec It F/S F/F RFL Fre SFr");
E 2
I 2
D 21
	mvprintw(GENSTATROW, GENSTATCOL + 8, "Csw");
	mvprintw(GENSTATROW + 1, GENSTATCOL + 8, "Trp");
	mvprintw(GENSTATROW + 2, GENSTATCOL + 8, "Sys");
	mvprintw(GENSTATROW + 3, GENSTATCOL + 8, "Int");
	mvprintw(GENSTATROW + 4, GENSTATCOL + 8, "Pdm");
D 13
	mvprintw(GENSTATROW + 5, GENSTATCOL + 8, "Flt");
	mvprintw(GENSTATROW + 6, GENSTATCOL + 8, "Scn");
	mvprintw(GENSTATROW + 7, GENSTATCOL + 8, "Rev");
E 13
I 13
	mvprintw(GENSTATROW + 5, GENSTATCOL + 8, "Sof");
	mvprintw(GENSTATROW + 6, GENSTATCOL + 8, "Flt");
D 18
	mvprintw(GENSTATROW + 7, GENSTATCOL + 8, "Scn");
	mvprintw(GENSTATROW + 8, GENSTATCOL + 8, "Rev");
E 18
I 18
	mvprintw(GENSTATROW + 7, GENSTATCOL + 8, "Cow");
E 21
I 21
D 30
	mvprintw(VMSTATROW, VMSTATCOL + 10, "vmflt");
	mvprintw(VMSTATROW + 1, VMSTATCOL + 10, "cow");
	mvprintw(VMSTATROW + 2, VMSTATCOL + 10, "objlk");
	mvprintw(VMSTATROW + 3, VMSTATCOL + 10, "objht");
	mvprintw(VMSTATROW + 4, VMSTATCOL + 10, "zfod");
	mvprintw(VMSTATROW + 5, VMSTATCOL + 10, "nzfod");
	mvprintw(VMSTATROW + 6, VMSTATCOL + 10, "%%zfod");
	mvprintw(VMSTATROW + 7, VMSTATCOL + 10, "kern");
	mvprintw(VMSTATROW + 8, VMSTATCOL + 10, "wire");
	mvprintw(VMSTATROW + 9, VMSTATCOL + 10, "act");
	mvprintw(VMSTATROW + 10, VMSTATCOL + 10, "inact");
	mvprintw(VMSTATROW + 11, VMSTATCOL + 10, "free");
	mvprintw(VMSTATROW + 12, VMSTATCOL + 10, "daefr");
	mvprintw(VMSTATROW + 13, VMSTATCOL + 10, "prcfr");
	mvprintw(VMSTATROW + 14, VMSTATCOL + 10, "react");
	mvprintw(VMSTATROW + 15, VMSTATCOL + 10, "scan");
E 30
I 30
	mvprintw(VMSTATROW + 0, VMSTATCOL + 10, "cow");
	mvprintw(VMSTATROW + 1, VMSTATCOL + 10, "objlk");
	mvprintw(VMSTATROW + 2, VMSTATCOL + 10, "objht");
	mvprintw(VMSTATROW + 3, VMSTATCOL + 10, "zfod");
	mvprintw(VMSTATROW + 4, VMSTATCOL + 10, "nzfod");
	mvprintw(VMSTATROW + 5, VMSTATCOL + 10, "%%zfod");
	mvprintw(VMSTATROW + 6, VMSTATCOL + 10, "kern");
	mvprintw(VMSTATROW + 7, VMSTATCOL + 10, "wire");
	mvprintw(VMSTATROW + 8, VMSTATCOL + 10, "act");
	mvprintw(VMSTATROW + 9, VMSTATCOL + 10, "inact");
	mvprintw(VMSTATROW + 10, VMSTATCOL + 10, "free");
	mvprintw(VMSTATROW + 11, VMSTATCOL + 10, "daefr");
	mvprintw(VMSTATROW + 12, VMSTATCOL + 10, "prcfr");
	mvprintw(VMSTATROW + 13, VMSTATCOL + 10, "react");
	mvprintw(VMSTATROW + 14, VMSTATCOL + 10, "scan");
	mvprintw(VMSTATROW + 15, VMSTATCOL + 10, "hdrev");
E 30
	if (LINES - 1 > VMSTATROW + 16)
D 30
		mvprintw(VMSTATROW + 16, VMSTATCOL + 10, "hdrev");
	if (LINES - 1 > VMSTATROW + 17)
		mvprintw(VMSTATROW + 17, VMSTATCOL + 10, "intrn");
E 30
I 30
		mvprintw(VMSTATROW + 16, VMSTATCOL + 10, "intrn");
E 30
E 21
E 18
E 13
E 2

D 2
	mvprintw(11, 49, " zf");
	mvprintw(12, 49, "nzf");
	mvprintw(13, 49, "%%zf");
	mvprintw(11, 63, " xf");
	mvprintw(12, 63, "nxf");
	mvprintw(13, 63, "%%xf");
E 2
I 2
D 16
	mvprintw(PAGEROW + 5, PAGECOL, "Rec It F/S F/F RFL Fre SFr");
E 16
I 16
D 18
	mvprintw(VMSTATROW, VMSTATCOL, "Rec It F/S F/F RFL Fre SFr");
E 18
I 18
D 21
	mvprintw(VMSTATROW, VMSTATCOL, "Rec    F/S F/F RFL Fre SFr");
E 21
I 21
	mvprintw(GENSTATROW, GENSTATCOL, "  Csw  Trp  Sys  Int  Sof  Flt");
E 21
E 18
E 16
E 2

D 2
	mvprintw(15, 5, " Sys   . %% User   . %% Nice   . %% Idle   . %%");
	mvprintw(15,57, "Procs  r  p  d  s  w");
	mvprintw(16, 5, "|    |    |    |    |    |    |    |    |    |    |");
E 2
I 2
D 16
	mvprintw(PAGEROW + 8, PAGECOL + 9, " zf");
	mvprintw(PAGEROW + 9, PAGECOL + 9, "nzf");
	mvprintw(PAGEROW + 10, PAGECOL + 9, "%%zf");
	mvprintw(PAGEROW + 8, PAGECOL + 23, " xf");
	mvprintw(PAGEROW + 9, PAGECOL + 23, "nxf");
	mvprintw(PAGEROW + 10, PAGECOL + 23, "%%xf");
E 16
I 16
D 21
	mvprintw(FILLSTATROW, FILLSTATCOL + 7, " zf");
	mvprintw(FILLSTATROW + 1, FILLSTATCOL + 7, "nzf");
	mvprintw(FILLSTATROW + 2, FILLSTATCOL + 7, "%%zf");
D 20
	mvprintw(FILLSTATROW + 3, FILLSTATCOL + 7, " xf");
	mvprintw(FILLSTATROW + 4, FILLSTATCOL + 7, "nxf");
	mvprintw(FILLSTATROW + 5, FILLSTATCOL + 7, "%%xf");
E 20
E 16
E 2

E 21
D 2
	mvprintw(19, 0, "Namei         Sys-cache     Proc-cache");
	mvprintw(20, 0, "      Calls   hits    %%     hits     %%");
	mvprintw( 8, 0, "Discs");
	mvprintw( 9, 0, "seeks");
	mvprintw(10, 0, "xfers");
	mvprintw(11, 0, " blks");
	mvprintw(12, 0, " msps");
E 2
I 2
	mvprintw(GRAPHROW, GRAPHCOL,
D 3
		" Sys   . %% User   . %% Nice   . %% Idle   . %%");
E 3
I 3
		"    . %% Sys    . %% User    . %% Nice    . %% Idle");
E 3
D 21
	mvprintw(PROCSROW, PROCSCOL, "Procs  r  p  d  s  w");
E 21
I 21
	mvprintw(PROCSROW, PROCSCOL, "Proc:r  p  d  s  w");
E 21
	mvprintw(GRAPHROW + 1, GRAPHCOL,
		"|    |    |    |    |    |    |    |    |    |    |");

	mvprintw(NAMEIROW, NAMEICOL, "Namei         Sys-cache     Proc-cache");
	mvprintw(NAMEIROW + 1, NAMEICOL,
		"    Calls     hits    %%     hits     %%");
	mvprintw(DISKROW, DISKCOL, "Discs");
	mvprintw(DISKROW + 1, DISKCOL, "seeks");
	mvprintw(DISKROW + 2, DISKCOL, "xfers");
	mvprintw(DISKROW + 3, DISKCOL, " blks");
	mvprintw(DISKROW + 4, DISKCOL, " msps");
E 2
	j = 0;
D 7
	for (i = 0; i < DK_NDRIVE; i++)
		if (dr_state[i] == SOME) {
E 7
I 7
	for (i = 0; i < dk_ndrive && j < MAXDRIVES; i++)
		if (dk_select[i]) {
E 7
D 2
			mvprintw(8, 5 + 5*j, "  %3.3s", dr_name[j]);
E 2
I 2
			mvprintw(DISKROW, DISKCOL + 5 + 5 * j,
				"  %3.3s", dr_name[j]);
E 2
			j++;
		}
I 3
	for (i = 0; i < nintr; i++) {
		if (intrloc[i] == 0)
			continue;
		mvprintw(intrloc[i], INTSCOL + 9, "%-8.8s", intrname[i]);
	}
E 3
}

I 6
#define X(fld)	{t=s.fld[i]; s.fld[i]-=s1.fld[i]; if(state==TIME) s1.fld[i]=t;}
#define Y(fld)	{t = s.fld; s.fld -= s1.fld; if(state == TIME) s1.fld = t;}
#define Z(fld)	{t = s.nchstats.fld; s.nchstats.fld -= s1.nchstats.fld; \
	if(state == TIME) s1.nchstats.fld = t;}
I 20
#define PUTRATE(fld, l, c, w) \
	Y(fld); \
	putint((int)((float)s.fld/etime + 0.5), l, c, w)
E 20
I 11
#define MAXFAIL 5
E 11

static	char cpuchar[CPUSTATES] = { '=' , '>', '-', ' ' };
static	char cpuorder[CPUSTATES] = { CP_SYS, CP_USER, CP_NICE, CP_IDLE };

I 22
void
E 22
showkre()
{
	float f1, f2;
D 8
	int psiz, interv, hits, inttotal;
E 8
I 8
	int psiz, inttotal;
E 8
	int i, l, c;
I 11
	static int failcnt = 0;
E 11

D 7
	for (i = 0; i < DK_NDRIVE; i++) {
E 7
I 7
	for (i = 0; i < dk_ndrive; i++) {
E 7
		X(dk_xfer); X(dk_seek); X(dk_wds); X(dk_time);
	}
D 18
	Y(tk_nin); Y(tk_nout);
E 18
	etime = 0;
	for(i = 0; i < CPUSTATES; i++) {
		X(time);
		etime += s.time[i];
	}
D 11
	if (etime < 5.0)	/* < 5 ticks - ignore this trash */
E 11
I 11
	if (etime < 5.0) {	/* < 5 ticks - ignore this trash */
		if (failcnt++ >= MAXFAIL) {
			clear();
			mvprintw(2, 10, "The alternate system clock has died!");
			mvprintw(3, 10, "Reverting to ``pigs'' display.");
			move(CMDLINE, 0);
			refresh();
			failcnt = 0;
			sleep(5);
			command("pigs");
		}
E 11
		return;
I 11
	}
	failcnt = 0;
E 11
	etime /= hertz;
	inttotal = 0;
	for (i = 0; i < nintr; i++) {
		if (s.intrcnt[i] == 0)
			continue;
		if (intrloc[i] == 0) {
			if (nextintsrow == LINES)
				continue;
			intrloc[i] = nextintsrow++;
			mvprintw(intrloc[i], INTSCOL + 9, "%-8.8s",
				intrname[i]);
		}
		X(intrcnt);
		l = (int)((float)s.intrcnt[i]/etime + 0.5);
		inttotal += l;
		putint(l, intrloc[i], INTSCOL, 8);
	}
	putint(inttotal, INTSROW + 1, INTSCOL, 8);
	Z(ncs_goodhits); Z(ncs_badhits); Z(ncs_miss);
	Z(ncs_long); Z(ncs_pass2); Z(ncs_2passes);
	s.nchcount = nchtotal.ncs_goodhits + nchtotal.ncs_badhits +
	    nchtotal.ncs_miss + nchtotal.ncs_long;
	if (state == TIME)
		s1.nchcount = s.nchcount;

	psiz = 0;
	f2 = 0.0;
D 22
	for (c = 0; c < CPUSTATES; c++) {
E 22
I 22

	/* 
	 * Last CPU state not calculated yet.
	 */
	for (c = 0; c < CPUSTATES - 1; c++) {
E 22
		i = cpuorder[c];
		f1 = cputime(i);
		f2 += f1;
		l = (int) ((f2 + 1.0) / 2.0) - psiz;
		if (c == 0)
			putfloat(f1, GRAPHROW, GRAPHCOL + 1, 5, 1, 0);
		else
			putfloat(f1, GRAPHROW, GRAPHCOL + 12 * c,
				5, 1, 0);
		move(GRAPHROW + 2, psiz);
		psiz += l;
		while (l-- > 0)
			addch(cpuchar[c]);
	}

	putint(ucount(), STATROW, STATCOL, 3);
	putfloat(avenrun[0], STATROW, STATCOL + 17, 6, 2, 0);
	putfloat(avenrun[1], STATROW, STATCOL + 23, 6, 2, 0);
	putfloat(avenrun[2], STATROW, STATCOL + 29, 6, 2, 0);
	mvaddstr(STATROW, STATCOL + 53, buf);
D 15
	putint(total.t_arm/2, MEMROW + 2, MEMCOL + 4, 5);
	putint(total.t_armtxt/2, MEMROW + 2, MEMCOL + 9, 5);
D 11
	putint(total.t_avm/2, MEMROW + 2, MEMCOL + 14, 5);
	putint(total.t_avmtxt/2, MEMROW + 2, MEMCOL + 19, 5);
E 11
I 11
	putint(total.t_avm/2, MEMROW + 2, MEMCOL + 14, 6);
	putint(total.t_avmtxt/2, MEMROW + 2, MEMCOL + 20, 5);
E 11
	putint(total.t_rm/2, MEMROW + 3, MEMCOL + 4, 5);
	putint(total.t_rmtxt/2, MEMROW + 3, MEMCOL + 9, 5);
D 11
	putint(total.t_vm/2, MEMROW + 3, MEMCOL + 14, 5);
	putint(total.t_vmtxt/2, MEMROW + 3, MEMCOL + 19, 5);
	putint(total.t_free/2, MEMROW + 2, MEMCOL + 26, 5);
E 11
I 11
	putint(total.t_vm/2, MEMROW + 3, MEMCOL + 14, 6);
	putint(total.t_vmtxt/2, MEMROW + 3, MEMCOL + 20, 5);
	putint(total.t_free/2, MEMROW + 2, MEMCOL + 27, 5);
E 15
I 15
D 21
#define pgtokb(pg)	((pg) * NBPG / 1024)
	putint(pgtokb(total.t_arm), MEMROW + 2, MEMCOL + 4, 5);
	putint(pgtokb(total.t_armtxt), MEMROW + 2, MEMCOL + 9, 5);
	putint(pgtokb(total.t_avm), MEMROW + 2, MEMCOL + 14, 6);
	putint(pgtokb(total.t_avmtxt), MEMROW + 2, MEMCOL + 20, 5);
	putint(pgtokb(total.t_rm), MEMROW + 3, MEMCOL + 4, 5);
	putint(pgtokb(total.t_rmtxt), MEMROW + 3, MEMCOL + 9, 5);
	putint(pgtokb(total.t_vm), MEMROW + 3, MEMCOL + 14, 6);
	putint(pgtokb(total.t_vmtxt), MEMROW + 3, MEMCOL + 20, 5);
	putint(pgtokb(total.t_free), MEMROW + 2, MEMCOL + 27, 5);
E 15
E 11
	putint(total.t_rq, PROCSROW + 1, PROCSCOL + 5, 3);
	putint(total.t_pw, PROCSROW + 1, PROCSCOL + 8, 3);
	putint(total.t_dw, PROCSROW + 1, PROCSCOL + 11, 3);
	putint(total.t_sl, PROCSROW + 1, PROCSCOL + 14, 3);
	putint(total.t_sw, PROCSROW + 1, PROCSCOL + 17, 3);
D 18
	putrate(rate.v_swtch, oldrate.v_swtch, 
E 18
I 18
D 20
	putrate(cnt.v_swtch, oldcnt.v_swtch, 
E 18
		GENSTATROW, GENSTATCOL, 7);
D 18
	putrate(rate.v_trap, oldrate.v_trap, 
E 18
I 18
	putrate(cnt.v_trap, oldcnt.v_trap, 
E 18
		GENSTATROW + 1, GENSTATCOL, 7);
D 18
	putrate(rate.v_syscall, oldrate.v_syscall, 
E 18
I 18
	putrate(cnt.v_syscall, oldcnt.v_syscall, 
E 18
		GENSTATROW + 2, GENSTATCOL, 7);
D 18
	putrate(rate.v_intr, oldrate.v_intr, 
E 18
I 18
	putrate(cnt.v_intr, oldcnt.v_intr, 
E 18
		GENSTATROW + 3, GENSTATCOL, 7);
D 18
	putrate(rate.v_pdma, oldrate.v_pdma, 
E 18
I 18
	putrate(cnt.v_pdma, oldcnt.v_pdma, 
E 18
		GENSTATROW + 4, GENSTATCOL, 7);
D 13
	putrate(rate.v_faults, oldrate.v_faults, 
E 13
I 13
D 18
	putrate(rate.v_soft, oldrate.v_soft, 
E 18
I 18
	putrate(cnt.v_soft, oldcnt.v_soft, 
E 18
E 13
		GENSTATROW + 5, GENSTATCOL, 7);
D 13
	putrate(rate.v_scan, oldrate.v_scan, 
E 13
I 13
D 18
	putrate(rate.v_faults, oldrate.v_faults, 
E 18
I 18
	putrate(vmstat.faults, oldvmstat.faults, 
E 18
E 13
		GENSTATROW + 6, GENSTATCOL, 7);
D 13
	putrate(rate.v_rev, oldrate.v_rev, 
E 13
I 13
D 18
	putrate(rate.v_scan, oldrate.v_scan, 
E 18
I 18
	putrate(vmstat.cow_faults, oldvmstat.cow_faults, 
E 18
E 13
		GENSTATROW + 7, GENSTATCOL, 7);
I 13
D 18
	putrate(rate.v_rev, oldrate.v_rev, 
		GENSTATROW + 8, GENSTATCOL, 7);
E 13
	putrate(rate.v_pgin, oldrate.v_pgin, PAGEROW + 2,
E 18
I 18
	putrate(vmstat.pageins, oldvmstat.pageins, PAGEROW + 2,
E 18
		PAGECOL + 5, 5);
D 18
	putrate(rate.v_pgout, oldrate.v_pgout, PAGEROW + 2,
E 18
I 18
	putrate(vmstat.pageouts, oldvmstat.pageouts, PAGEROW + 2,
E 18
		PAGECOL + 10, 5);
D 18
	putrate(rate.v_swpin, oldrate.v_swpin, PAGEROW + 2,
E 18
I 18
	putrate(cnt.v_swpin, oldcnt.v_swpin, PAGEROW + 2,	/* - */
E 18
		PAGECOL + 15, 5);
D 18
	putrate(rate.v_swpout, oldrate.v_swpout, PAGEROW + 2,
E 18
I 18
	putrate(cnt.v_swpout, oldcnt.v_swpout, PAGEROW + 2,	/* - */
E 18
		PAGECOL + 20, 5);
D 18
	putrate(rate.v_pgpgin, oldrate.v_pgpgin, PAGEROW + 3,
E 18
I 18
	putrate(cnt.v_pgpgin, oldcnt.v_pgpgin, PAGEROW + 3,	/* ? */
E 18
		PAGECOL + 5, 5);
D 18
	putrate(rate.v_pgpgout, oldrate.v_pgpgout, PAGEROW + 3,
E 18
I 18
	putrate(cnt.v_pgpgout, oldcnt.v_pgpgout, PAGEROW + 3,	/* ? */
E 18
		PAGECOL + 10, 5);
D 18
	putrate(rate.v_pswpin, oldrate.v_pswpin, PAGEROW + 3,
E 18
I 18
	putrate(cnt.v_pswpin, oldcnt.v_pswpin, PAGEROW + 3,	/* - */
E 18
		PAGECOL + 15, 5);
D 18
	putrate(rate.v_pswpout, oldrate.v_pswpout, PAGEROW + 3,
E 18
I 18
	putrate(cnt.v_pswpout, oldcnt.v_pswpout, PAGEROW + 3,	/* - */
E 18
		PAGECOL + 20, 5);
D 16
	putrate(rate.v_pgrec, oldrate.v_pgrec, PAGEROW + 6, PAGECOL, 3);
	putrate(rate.v_intrans, oldrate.v_intrans, PAGEROW + 6,
		PAGECOL + 4, 2);
	putrate(rate.v_xsfrec, oldrate.v_xsfrec, PAGEROW + 6,
		PAGECOL + 7, 3);
	putrate(rate.v_xifrec, oldrate.v_xifrec, PAGEROW + 6,
		PAGECOL + 11, 3);
	putrate(rate.v_pgfrec, oldrate.v_pgfrec, PAGEROW + 6,
		PAGECOL + 15, 3);
	putrate(rate.v_dfree, oldrate.v_dfree, PAGEROW + 6,
		PAGECOL + 19, 3);
	putrate(rate.v_seqfree, oldrate.v_seqfree, PAGEROW + 6,
		PAGECOL + 23, 3);
	putrate(rate.v_zfod, oldrate.v_zfod, PAGEROW + 8, PAGECOL, 8);
	putrate(rate.v_nzfod, oldrate.v_nzfod, PAGEROW + 9, PAGECOL, 8);
	putrate(rate.v_exfod, oldrate.v_exfod, PAGEROW + 8,
		PAGECOL + 14, 8);
	putrate(rate.v_nexfod, oldrate.v_nexfod, PAGEROW + 9,
		PAGECOL + 14, 8);
E 16
I 16

D 18
	putrate(rate.v_pgrec, oldrate.v_pgrec, VMSTATROW + 1, VMSTATCOL, 3);
	putrate(rate.v_intrans, oldrate.v_intrans, VMSTATROW + 1,
		VMSTATCOL + 4, 2);
	putrate(rate.v_xsfrec, oldrate.v_xsfrec, VMSTATROW + 1,
E 18
I 18
	putrate(vmstat.reactivations, oldvmstat.reactivations,
		VMSTATROW + 1, VMSTATCOL, 3);
	putrate(cnt.v_xsfrec, oldcnt.v_xsfrec, VMSTATROW + 1,
E 18
		VMSTATCOL + 7, 3);
D 18
	putrate(rate.v_xifrec, oldrate.v_xifrec, VMSTATROW + 1,
E 18
I 18
	putrate(cnt.v_xifrec, oldcnt.v_xifrec, VMSTATROW + 1,
E 18
		VMSTATCOL + 11, 3);
D 18
	putrate(rate.v_pgfrec, oldrate.v_pgfrec, VMSTATROW + 1,
E 18
I 18
	putrate(cnt.v_pgfrec, oldcnt.v_pgfrec, VMSTATROW + 1,
E 18
		VMSTATCOL + 15, 3);
D 18
	putrate(rate.v_dfree, oldrate.v_dfree, VMSTATROW + 1,
E 18
I 18
	putrate(cnt.v_dfree, oldcnt.v_dfree, VMSTATROW + 1,
E 18
		VMSTATCOL + 19, 3);
D 18
	putrate(rate.v_seqfree, oldrate.v_seqfree, VMSTATROW + 1,
E 18
I 18
	putrate(cnt.v_seqfree, oldcnt.v_seqfree, VMSTATROW + 1,
E 18
		VMSTATCOL + 23, 3);

D 18
	putrate(rate.v_zfod, oldrate.v_zfod, FILLSTATROW, FILLSTATCOL, 6);
	putrate(rate.v_nzfod, oldrate.v_nzfod, FILLSTATROW + 1, FILLSTATCOL, 6);
	putrate(rate.v_exfod, oldrate.v_exfod, FILLSTATROW + 3,
E 18
I 18
	putrate(vmstat.zero_fill_count, oldvmstat.zero_fill_count,
		FILLSTATROW, FILLSTATCOL, 6);
	/******* begin XXX
	putrate(cnt.v_nzfod, oldcnt.v_nzfod, FILLSTATROW + 1, FILLSTATCOL, 6);
	putrate(cnt.v_exfod, oldcnt.v_exfod, FILLSTATROW + 3,
E 18
		FILLSTATCOL, 6);
D 18
	putrate(rate.v_nexfod, oldrate.v_nexfod, FILLSTATROW + 4,
E 18
I 18
	putrate(cnt.v_nexfod, oldcnt.v_nexfod, FILLSTATROW + 4,
E 18
		FILLSTATCOL, 6);
E 16
	putfloat (
D 18
		rate.v_nzfod == 0 ?
E 18
I 18
		cnt.v_nzfod == 0 ?
E 18
			0.0
		: state != RUN ?
D 18
			( 100.0 * rate.v_zfod / rate.v_nzfod )
		: rate.v_nzfod == oldrate.v_nzfod ?
E 18
I 18
			( 100.0 * cnt.v_zfod / cnt.v_nzfod )
		: cnt.v_nzfod == oldcnt.v_nzfod ?
E 18
			0.0
		:
D 18
			( 100.0 * (rate.v_zfod-oldrate.v_zfod)
			/ (rate.v_nzfod-oldrate.v_nzfod) )
E 18
I 18
			( 100.0 * (cnt.v_zfod-oldcnt.v_zfod)
			/ (cnt.v_nzfod-oldcnt.v_nzfod) )
E 18
D 16
		, PAGEROW + 10
		, PAGECOL
		, 8
E 16
I 16
		, FILLSTATROW + 2
		, FILLSTATCOL
		, 6
E 16
		, 2
		, 1
	);
	putfloat (
D 18
		rate.v_nexfod == 0 ?
E 18
I 18
		cnt.v_nexfod == 0 ?
E 18
			0.0
		: state != RUN ?
D 18
			( 100.0 * rate.v_exfod / rate.v_nexfod )
		: rate.v_nexfod == oldrate.v_nexfod ?
E 18
I 18
			( 100.0 * cnt.v_exfod / cnt.v_nexfod )
		: cnt.v_nexfod == oldcnt.v_nexfod ?
E 18
			0.0
		:
D 18
			( 100.0 * (rate.v_exfod-oldrate.v_exfod)
			/ (rate.v_nexfod-oldrate.v_nexfod) )
E 18
I 18
			( 100.0 * (cnt.v_exfod-oldcnt.v_exfod)
			/ (cnt.v_nexfod-oldcnt.v_nexfod) )
E 18
D 16
		, PAGEROW + 10
		, PAGECOL + 14
		, 8
E 16
I 16
		, FILLSTATROW + 5
		, FILLSTATCOL
		, 6
E 16
		, 2
		, 1
	);
I 18
	******* end XXX */
E 18
I 16

E 16
D 7
	c = 1;
	for (i = 0; i < DK_NDRIVE; i++)
		if (dr_state[i] == SOME)
			dinfo(i, c++);
E 7
I 7
D 12
	c = 0;
	for (i = 0; i < dk_ndrive && c < MAXDRIVES; i++)
		if (dk_select[i])
E 12
I 12
	mvprintw(DISKROW,DISKCOL+5,"                              ");
E 20
I 20
	PUTRATE(Cnt.v_swtch, GENSTATROW, GENSTATCOL, 7);
	PUTRATE(Cnt.v_trap, GENSTATROW + 1, GENSTATCOL, 7);
	PUTRATE(Cnt.v_syscall, GENSTATROW + 2, GENSTATCOL, 7);
	PUTRATE(Cnt.v_intr, GENSTATROW + 3, GENSTATCOL, 7);
	PUTRATE(Cnt.v_pdma, GENSTATROW + 4, GENSTATCOL, 7);
	PUTRATE(Cnt.v_soft, GENSTATROW + 5, GENSTATCOL, 7);
	PUTRATE(Vmstat.faults, GENSTATROW + 6, GENSTATCOL, 7);
	PUTRATE(Vmstat.cow_faults, GENSTATROW + 7, GENSTATCOL, 7);
	PUTRATE(Vmstat.pageins, PAGEROW + 2, PAGECOL + 5, 5);
	PUTRATE(Vmstat.pageouts, PAGEROW + 2, PAGECOL + 10, 5);
E 21
I 21
#define pgtokb(pg)	((pg) * cnt.v_page_size / 1024)
	putint(pgtokb(total.t_arm), MEMROW + 2, MEMCOL + 3, 6);
	putint(pgtokb(total.t_armshr), MEMROW + 2, MEMCOL + 9, 6);
	putint(pgtokb(total.t_avm), MEMROW + 2, MEMCOL + 15, 7);
	putint(pgtokb(total.t_avmshr), MEMROW + 2, MEMCOL + 22, 7);
	putint(pgtokb(total.t_rm), MEMROW + 3, MEMCOL + 3, 6);
	putint(pgtokb(total.t_rmshr), MEMROW + 3, MEMCOL + 9, 6);
	putint(pgtokb(total.t_vm), MEMROW + 3, MEMCOL + 15, 7);
	putint(pgtokb(total.t_vmshr), MEMROW + 3, MEMCOL + 22, 7);
	putint(pgtokb(total.t_free), MEMROW + 2, MEMCOL + 29, 6);
D 27
	putint(total.t_rq, PROCSROW + 1, PROCSCOL + 3, 3);
E 27
I 27
	putint(total.t_rq - 1, PROCSROW + 1, PROCSCOL + 3, 3);
E 27
	putint(total.t_pw, PROCSROW + 1, PROCSCOL + 6, 3);
	putint(total.t_dw, PROCSROW + 1, PROCSCOL + 9, 3);
	putint(total.t_sl, PROCSROW + 1, PROCSCOL + 12, 3);
	putint(total.t_sw, PROCSROW + 1, PROCSCOL + 15, 3);
D 30
	PUTRATE(Cnt.v_vm_faults, VMSTATROW, VMSTATCOL + 3, 6);
	PUTRATE(Cnt.v_cow_faults, VMSTATROW + 1, VMSTATCOL + 3, 6);
	PUTRATE(Cnt.v_lookups, VMSTATROW + 2, VMSTATCOL + 3, 6);
	PUTRATE(Cnt.v_hits, VMSTATROW + 3, VMSTATCOL + 3, 6);
	PUTRATE(Cnt.v_zfod, VMSTATROW + 4, VMSTATCOL + 4, 5);
	PUTRATE(Cnt.v_nzfod, VMSTATROW + 5, VMSTATCOL + 3, 6);
E 30
I 30
	PUTRATE(Cnt.v_cow_faults, VMSTATROW + 0, VMSTATCOL + 3, 6);
	PUTRATE(Cnt.v_lookups, VMSTATROW + 1, VMSTATCOL + 3, 6);
	PUTRATE(Cnt.v_hits, VMSTATROW + 2, VMSTATCOL + 3, 6);
	PUTRATE(Cnt.v_zfod, VMSTATROW + 3, VMSTATCOL + 4, 5);
	PUTRATE(Cnt.v_nzfod, VMSTATROW + 4, VMSTATCOL + 3, 6);
E 30
	putfloat(cnt.v_nzfod == 0 ? 0.0 : (100.0 * cnt.v_zfod / cnt.v_nzfod),
D 30
		 VMSTATROW + 6, VMSTATCOL + 2, 7, 2, 1);
	putint(pgtokb(cnt.v_kernel_pages), VMSTATROW + 7, VMSTATCOL, 9);
	putint(pgtokb(cnt.v_wire_count), VMSTATROW + 8, VMSTATCOL, 9);
	putint(pgtokb(cnt.v_active_count), VMSTATROW + 9, VMSTATCOL, 9);
	putint(pgtokb(cnt.v_inactive_count), VMSTATROW + 10, VMSTATCOL, 9);
	putint(pgtokb(cnt.v_free_count), VMSTATROW + 11, VMSTATCOL, 9);
	PUTRATE(Cnt.v_dfree, VMSTATROW + 12, VMSTATCOL, 9);
	PUTRATE(Cnt.v_pfree, VMSTATROW + 13, VMSTATCOL, 9);
	PUTRATE(Cnt.v_reactivated, VMSTATROW + 14, VMSTATCOL, 9);
	PUTRATE(Cnt.v_scan, VMSTATROW + 15, VMSTATCOL, 9);
E 30
I 30
		 VMSTATROW + 5, VMSTATCOL + 2, 7, 2, 1);
	putint(pgtokb(cnt.v_kernel_pages), VMSTATROW + 6, VMSTATCOL, 9);
	putint(pgtokb(cnt.v_wire_count), VMSTATROW + 7, VMSTATCOL, 9);
	putint(pgtokb(cnt.v_active_count), VMSTATROW + 8, VMSTATCOL, 9);
	putint(pgtokb(cnt.v_inactive_count), VMSTATROW + 9, VMSTATCOL, 9);
	putint(pgtokb(cnt.v_free_count), VMSTATROW + 10, VMSTATCOL, 9);
	PUTRATE(Cnt.v_dfree, VMSTATROW + 11, VMSTATCOL, 9);
	PUTRATE(Cnt.v_pfree, VMSTATROW + 12, VMSTATCOL, 9);
	PUTRATE(Cnt.v_reactivated, VMSTATROW + 13, VMSTATCOL, 9);
	PUTRATE(Cnt.v_scan, VMSTATROW + 14, VMSTATCOL, 9);
	PUTRATE(Cnt.v_rev, VMSTATROW + 15, VMSTATCOL, 9);
E 30
	if (LINES - 1 > VMSTATROW + 16)
D 30
		PUTRATE(Cnt.v_rev, VMSTATROW + 16, VMSTATCOL, 9);
	if (LINES - 1 > VMSTATROW + 17)
		PUTRATE(Cnt.v_intrans, VMSTATROW + 17, VMSTATCOL, 9);
E 30
I 30
		PUTRATE(Cnt.v_intrans, VMSTATROW + 16, VMSTATCOL, 9);
E 30
	PUTRATE(Cnt.v_pageins, PAGEROW + 2, PAGECOL + 5, 5);
	PUTRATE(Cnt.v_pageouts, PAGEROW + 2, PAGECOL + 10, 5);
E 21
	PUTRATE(Cnt.v_swpin, PAGEROW + 2, PAGECOL + 15, 5);	/* - */
	PUTRATE(Cnt.v_swpout, PAGEROW + 2, PAGECOL + 20, 5);	/* - */
	PUTRATE(Cnt.v_pgpgin, PAGEROW + 3, PAGECOL + 5, 5);	/* ? */
	PUTRATE(Cnt.v_pgpgout, PAGEROW + 3, PAGECOL + 10, 5);	/* ? */
	PUTRATE(Cnt.v_pswpin, PAGEROW + 3, PAGECOL + 15, 5);	/* - */
	PUTRATE(Cnt.v_pswpout, PAGEROW + 3, PAGECOL + 20, 5);	/* - */
D 21
	PUTRATE(Vmstat.reactivations, VMSTATROW + 1, VMSTATCOL, 3);
	PUTRATE(Cnt.v_xsfrec, VMSTATROW + 1, VMSTATCOL + 7, 3);
	PUTRATE(Cnt.v_xifrec, VMSTATROW + 1, VMSTATCOL + 11, 3);
	PUTRATE(Cnt.v_pgfrec, VMSTATROW + 1, VMSTATCOL + 15, 3);
	PUTRATE(Cnt.v_dfree, VMSTATROW + 1, VMSTATCOL + 19, 3);
	PUTRATE(Cnt.v_seqfree, VMSTATROW + 1, VMSTATCOL + 23, 3);
	PUTRATE(Vmstat.zero_fill_count, FILLSTATROW, FILLSTATCOL, 6);
	PUTRATE(Cnt.v_nzfod, FILLSTATROW + 1, FILLSTATCOL, 6);
	putfloat(cnt.v_nzfod == 0 ? 0.0 : (100.0 * cnt.v_zfod / cnt.v_nzfod),
		 FILLSTATROW + 2, FILLSTATCOL, 6, 2, 1);
E 21
I 21
	PUTRATE(Cnt.v_swtch, GENSTATROW + 1, GENSTATCOL, 5);
	PUTRATE(Cnt.v_trap, GENSTATROW + 1, GENSTATCOL + 5, 5);
	PUTRATE(Cnt.v_syscall, GENSTATROW + 1, GENSTATCOL + 10, 5);
	PUTRATE(Cnt.v_intr, GENSTATROW + 1, GENSTATCOL + 15, 5);
	PUTRATE(Cnt.v_soft, GENSTATROW + 1, GENSTATCOL + 20, 5);
D 22
	PUTRATE(Cnt.v_faults, GENSTATROW + 1, GENSTATCOL + 25, 5);
E 22
I 22
D 30
/*	PUTRATE(Cnt.v_faults, GENSTATROW + 1, GENSTATCOL + 25, 5);*/
E 30
I 30
	PUTRATE(Cnt.v_faults, GENSTATROW + 1, GENSTATCOL + 25, 5);
E 30
E 22
E 21
	mvprintw(DISKROW, DISKCOL + 5, "                              ");
E 20
	for (i = 0, c = 0; i < dk_ndrive && c < MAXDRIVES; i++)
		if (dk_select[i]) {
			mvprintw(DISKROW, DISKCOL + 5 + 5 * c,
				"  %3.3s", dr_name[i]);
E 12
			dinfo(i, ++c);
E 7
D 12

E 12
I 12
		}
E 12
	putint(s.nchcount, NAMEIROW + 2, NAMEICOL, 9);
	putint(nchtotal.ncs_goodhits, NAMEIROW + 2, NAMEICOL + 9, 9);
#define nz(x)	((x) ? (x) : 1)
	putfloat(nchtotal.ncs_goodhits * 100.0 / nz(s.nchcount),
	   NAMEIROW + 2, NAMEICOL + 19, 4, 0, 1);
	putint(nchtotal.ncs_pass2, NAMEIROW + 2, NAMEICOL + 23, 9);
	putfloat(nchtotal.ncs_pass2 * 100.0 / nz(s.nchcount),
	   NAMEIROW + 2, NAMEICOL + 34, 4, 0, 1);
#undef nz
}

I 22
int
E 22
cmdkre(cmd, args)
	char *cmd, *args;
{
D 8
	static enum state oldstate;
E 8

	if (prefix(cmd, "run")) {
		copyinfo(&s2, &s1);
		state = RUN;
		return (1);
	}
	if (prefix(cmd, "boot")) {
		state = BOOT;
		copyinfo(&z, &s1);
		return (1);
	}
	if (prefix(cmd, "time")) {
		state = TIME;
		return (1);
	}
	if (prefix(cmd, "zero")) {
		if (state == RUN)
			getinfo(&s1, RUN);
		return (1);
	}
D 7
	return (0);
E 7
I 7
	return (dkcmd(cmd, args));
E 7
}

/* calculate number of users on the system */
D 17
static
E 17
I 17
static int
E 17
ucount()
{
	register int nusers = 0;

	if (ut < 0)
		return (0);
	while (read(ut, &utmp, sizeof(utmp)))
		if (utmp.ut_name[0] != '\0')
			nusers++;

	lseek(ut, 0L, L_SET);
	return (nusers);
}

static float
cputime(indx)
	int indx;
{
	double t;
D 28
	register i;
E 28
I 28
	register int i;
E 28

	t = 0;
	for (i = 0; i < CPUSTATES; i++)
		t += s.time[i];
	if (t == 0.0)
		t = 1.0;
	return (s.time[indx] * 100.0 / t);
}

D 17
static
E 17
I 17
static void
E 17
E 6
D 22
putrate(r, or, l, c, w)
I 17
	int r, or, l, c, w;
E 17
{
I 6

E 6
D 18
	if (state != TIME) {
		if (state == RUN)
			r -= or;
		putint((int)((float)r/etime + 0.5), l, c, w);
	} else
		putint(r, l, c, w);
E 18
I 18
	if (state == RUN || state == TIME)
		r -= or;
	putint((int)((float)r/etime + 0.5), l, c, w);
E 18
}

I 6
D 17
static
E 17
I 17
static void
E 22
E 17
E 6
putint(n, l, c, w)
I 17
	int n, l, c, w;
E 17
{
	char b[128];

	move(l, c);
	if (n == 0) {
		while (w-- > 0)
			addch(' ');
		return;
	}
	sprintf(b, "%*d", w, n);
	if (strlen(b) > w) {
		while (w-- > 0)
			addch('*');
		return;
	}
	addstr(b);
}

I 6
D 17
static
E 17
I 17
static void
E 17
E 6
putfloat(f, l, c, w, d, nz)
D 6
float f;
E 6
I 6
D 22
	float f;
E 22
I 22
	double f;
E 22
I 17
	int l, c, w, d, nz;
E 17
E 6
{
	char b[128];

	move(l, c);
	if (nz && f == 0.0) {
D 17
		while (w-- > 0)
E 17
I 17
		while (--w >= 0)
E 17
			addch(' ');
		return;
	}
	sprintf(b, "%*.*f", w, d, f);
	if (strlen(b) > w) {
D 17
		while (w-- > 0)
E 17
I 17
		while (--w >= 0)
E 17
			addch('*');
		return;
	}
	addstr(b);
}

D 6
/*
 * Read the drive names out of kmem.
 * ARGH ARGH ARGH ARGH !!!!!!!!!!!!
 */

#define steal(where, var) lseek(kmem, where, 0); read(kmem, &var, sizeof var);
read_names()
{
	struct mba_device mdev;
	register struct mba_device *mp;
	struct mba_driver mdrv;
	short two_char;
	char *cp = (char *) &two_char;
	struct uba_device udev, *up;
	struct uba_driver udrv;

	mp = (struct mba_device *) name[X_MBDINIT].n_value;
	up = (struct uba_device *) name[X_UBDINIT].n_value;
	if (up == 0)
	{
		fprintf(stderr, "vsta: Disk init info not in namelist\n");
		exit(1);
	}
	if (mp)
	while(1)
	{
		steal(mp++, mdev);
		if (mdev.mi_driver == 0)
			break;
		if (mdev.mi_dk < 0 || mdev.mi_alive == 0)
			continue;
		steal(mdev.mi_driver, mdrv);
		steal(mdrv.md_dname, two_char);
		sprintf(dr_name[mdev.mi_dk], "%c%c%d", cp[0], cp[1], mdev.mi_unit);
	}
	while(1)
	{
		steal(up++, udev);
		if (udev.ui_driver == 0)
			break;
		if (udev.ui_dk < 0 || udev.ui_alive == 0)
			continue;
		steal(udev.ui_driver, udrv);
		steal(udrv.ud_dname, two_char);
		sprintf(dr_name[udev.ui_dk], "%c%c%d", cp[0], cp[1], udev.ui_unit);
	}
}

E 6
I 6
D 17
static
E 17
I 17
static void
E 17
E 6
getinfo(s, st)
	struct Info *s;
	enum state st;
{
I 21
D 26
	int size;
E 26
I 26
	int mib[2], size;
E 26
	extern int errno;
E 21
D 6
	lseek(kmem, (long)name[X_CPTIME].n_value,0);
E 6
I 6

D 18
	lseek(kmem, (long)name[X_CPTIME].n_value,L_SET);
E 6
	read(kmem, s->time, sizeof s->time);
	if (st != TIME) {
D 6
		lseek(kmem, (long)name[X_SUM].n_value, 0);
E 6
I 6
		lseek(kmem, (long)name[X_SUM].n_value, L_SET);
E 6
D 7
		read(kmem, &s->Rate, sizeof &s->Rate);
E 7
I 7
		read(kmem, &s->Rate, sizeof s->Rate);
E 7
	} else {
D 6
		lseek(kmem, (long)name[X_RATE].n_value,0);
E 6
I 6
		lseek(kmem, (long)name[X_RATE].n_value,L_SET);
E 6
		read(kmem, &s->Rate, sizeof s->Rate);
	}
D 6
	lseek(kmem, (long)name[X_DEFICIT].n_value,0);
	read(kmem, deficit, sizeof deficit);
	lseek( kmem, (long)name[X_AVENRUN].n_value, 0 );
	read( kmem, avenrun, sizeof(avenrun) );
	lseek(kmem, (long)name[X_TOTAL].n_value,0);
E 6
I 6
	lseek(kmem, (long)name[X_TOTAL].n_value, L_SET);
E 6
	read(kmem, &s->Total, sizeof s->Total);
D 6
	lseek(kmem, (long)name[X_DK_BUSY].n_value, 0);
E 6
I 6
D 7
	lseek(kmem, (long)name[X_DK_BUSY].n_value,  L_SET);
E 6
 	read(kmem, &s->dk_busy, sizeof s->dk_busy);
E 7
I 7
D 17
	s->dk_busy = getw(name[X_DK_BUSY].n_value);
E 17
I 17
	s->dk_busy = getword(name[X_DK_BUSY].n_value);
E 17
E 7
D 6
 	lseek(kmem, (long)name[X_DK_TIME].n_value, 0);
E 6
I 6
 	lseek(kmem, (long)name[X_DK_TIME].n_value,  L_SET);
E 6
D 7
 	read(kmem, s->dk_time, sizeof s->dk_time);
E 7
I 7
 	read(kmem, s->dk_time, dk_ndrive * sizeof (long));
E 7
D 6
 	lseek(kmem, (long)name[X_DK_XFER].n_value, 0);
E 6
I 6
 	lseek(kmem, (long)name[X_DK_XFER].n_value,  L_SET);
E 6
D 7
 	read(kmem, s->dk_xfer, sizeof s->dk_xfer);
E 7
I 7
 	read(kmem, s->dk_xfer, dk_ndrive * sizeof (long));
E 7
D 6
 	lseek(kmem, (long)name[X_DK_WDS].n_value, 0);
E 6
I 6
 	lseek(kmem, (long)name[X_DK_WDS].n_value,  L_SET);
E 6
D 7
 	read(kmem, s->dk_wds, sizeof s->dk_wds);
D 6
 	lseek(kmem, (long)name[X_TK_NIN].n_value, 0);
E 6
I 6
 	lseek(kmem, (long)name[X_TK_NIN].n_value,  L_SET);
E 6
 	read(kmem, &s->tk_nin, sizeof s->tk_nin);
D 6
 	lseek(kmem, (long)name[X_TK_NOUT].n_value, 0);
E 6
I 6
 	lseek(kmem, (long)name[X_TK_NOUT].n_value,  L_SET);
E 6
 	read(kmem, &s->tk_nout, sizeof s->tk_nout);
E 7
I 7
 	read(kmem, s->dk_wds, dk_ndrive * sizeof (long));
E 7
D 6
	lseek(kmem, (long)name[X_DK_SEEK].n_value, 0);
E 6
I 6
	lseek(kmem, (long)name[X_DK_SEEK].n_value,  L_SET);
E 6
D 7
	read(kmem, s->dk_seek, sizeof s->dk_seek);
E 7
I 7
	read(kmem, s->dk_seek, dk_ndrive * sizeof (long));
D 17
	s->tk_nin = getw(name[X_TK_NIN].n_value);
	s->tk_nout = getw(name[X_TK_NOUT].n_value);
E 17
I 17
	s->tk_nin = getword(name[X_TK_NIN].n_value);
	s->tk_nout = getword(name[X_TK_NOUT].n_value);
E 17
E 7
D 6
	lseek(kmem, (long)name[X_NCHSTATS].n_value, 0);
E 6
I 6
	lseek(kmem, (long)name[X_NCHSTATS].n_value,  L_SET);
E 6
	read(kmem, &s->nchstats, sizeof s->nchstats);
I 2
D 6
	lseek(kmem, (long)name[X_INTRCNT].n_value, 0);
E 6
I 6
	lseek(kmem, (long)name[X_INTRCNT].n_value,  L_SET);
E 6
	read(kmem, s->intrcnt, nintr * sizeof (long));
E 18
I 18
	NREAD(X_CPTIME, s->time, sizeof s->time);
	NREAD(X_CNT, &s->Cnt, sizeof s->Cnt);
D 21
	NREAD(X_TOTAL, &s->Total, sizeof s->Total);
	NREAD(X_VMSTAT, &s->Vmstat, sizeof s->Vmstat);
E 21
	NREAD(X_DK_BUSY, &s->dk_busy, LONG);
	NREAD(X_DK_TIME, s->dk_time, dk_ndrive * LONG);
	NREAD(X_DK_XFER, s->dk_xfer, dk_ndrive * LONG);
	NREAD(X_DK_WDS, s->dk_wds, dk_ndrive * LONG);
	NREAD(X_DK_SEEK, s->dk_seek, dk_ndrive * LONG);
	NREAD(X_NCHSTATS, &s->nchstats, sizeof s->nchstats);
	NREAD(X_INTRCNT, s->intrcnt, nintr * LONG);
I 21
	size = sizeof(s->Total);
D 26
	if (getkerninfo(KINFO_METER, &s->Total, &size, 0) < 0) {
		error("Can't get kerninfo: %s\n", strerror(errno));
E 26
I 26
	mib[0] = CTL_VM;
	mib[1] = VM_METER;
	if (sysctl(mib, 2, &s->Total, &size, NULL, 0) < 0) {
		error("Can't get kernel info: %s\n", strerror(errno));
E 26
		bzero(&s->Total, sizeof(s->Total));
	}
E 21
E 18
E 2
}

I 6
D 17
static
E 17
I 17
static void
E 17
E 6
I 2
allocinfo(s)
	struct Info *s;
{

	s->intrcnt = (long *) malloc(nintr * sizeof(long));
	if (s->intrcnt == NULL) {
D 8
		fprintf(stderr, "vsta: out of memory\n");
E 8
I 8
		fprintf(stderr, "systat: out of memory\n");
E 8
		exit(2);
	}
}

I 6
D 17
static
E 17
I 17
static void
E 17
E 6
copyinfo(from, to)
D 7
	struct Info *from, *to;
E 7
I 7
	register struct Info *from, *to;
E 7
{
D 7
	register int i, *fip = from->intrcnt, *tip = to->intrcnt;
E 7
I 7
	long *time, *wds, *seek, *xfer;
D 8
	int *intrcnt;
E 8
I 8
	long *intrcnt;
E 8
E 7

I 18
	/*
	 * time, wds, seek, and xfer are malloc'd so we have to
	 * save the pointers before the structure copy and then 
	 * copy by hand.
	 */
E 18
I 7
	time = to->dk_time; wds = to->dk_wds; seek = to->dk_seek;
	xfer = to->dk_xfer; intrcnt = to->intrcnt;
E 7
	*to = *from;
D 7
	to->intrcnt = tip;
	for (i = 0; i < nintr; i++)
		*tip++ = *fip++;
E 7
I 7
	bcopy(from->dk_time, to->dk_time = time, dk_ndrive * sizeof (long));
	bcopy(from->dk_wds, to->dk_wds = wds, dk_ndrive * sizeof (long));
	bcopy(from->dk_seek, to->dk_seek = seek, dk_ndrive * sizeof (long));
	bcopy(from->dk_xfer, to->dk_xfer = xfer, dk_ndrive * sizeof (long));
	bcopy(from->intrcnt, to->intrcnt = intrcnt, nintr * sizeof (int));
E 7
}

I 6
D 17
static
E 17
I 17
static void
E 17
E 6
E 2
dinfo(dn, c)
I 17
	int dn, c;
E 17
{
	double words, atime, itime, xtime;

I 2
	c = DISKCOL + c * 5;
E 2
	atime = s.dk_time[dn];
D 10
	atime /= 60.0;
E 10
I 10
	atime /= hertz;
E 10
	words = s.dk_wds[dn]*32.0;	/* number of words transferred */
D 6
	xtime = s.dk_mspw[dn]*words;	/* transfer time */
E 6
I 6
	xtime = dk_mspw[dn]*words;	/* transfer time */
E 6
	itime = atime - xtime;		/* time not transferring */
	if (xtime < 0)
		itime += xtime, xtime = 0;
	if (itime < 0)
		xtime += itime, itime = 0;
D 2
	putint((int)((float)s.dk_seek[dn]/etime+0.5), 9, c, 5);
	putint((int)((float)s.dk_xfer[dn]/etime+0.5), 10, c, 5);
	putint((int)(words/etime/512.0 + 0.5), 11, c, 5);
E 2
I 2
	putint((int)((float)s.dk_seek[dn]/etime+0.5), DISKROW + 1, c, 5);
	putint((int)((float)s.dk_xfer[dn]/etime+0.5), DISKROW + 2, c, 5);
	putint((int)(words/etime/512.0 + 0.5), DISKROW + 3, c, 5);
E 2
	if (s.dk_seek[dn])
D 2
		putfloat(itime*1000.0/s.dk_seek[dn], 12, c, 5, 1, 1);
E 2
I 2
		putfloat(itime*1000.0/s.dk_seek[dn], DISKROW + 4, c, 5, 1, 1);
E 2
	else
D 2
		putint(0, 12, c, 5);
E 2
I 2
		putint(0, DISKROW + 4, c, 5);
E 2
}
E 1
