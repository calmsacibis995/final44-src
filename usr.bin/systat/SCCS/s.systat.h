h32390
s 00002/00002/00032
d D 8.1 93/06/06 16:29:46 bostic 18 17
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00033
d D 5.10 93/05/21 15:34:24 mckusick 17 16
c update header to reflect redistributable status
e
s 00001/00001/00033
d D 5.9 92/09/02 11:56:39 bostic 16 15
c nl is an exported curses function
e
s 00001/00001/00033
d D 5.8 92/07/24 12:41:23 bostic 15 14
c rename nlst to nl globally so can use vmstat's names.c; should not
c be a semantic change for any of these files
e
s 00009/00045/00025
d D 5.7 92/07/23 18:12:49 bostic 14 13
c Elan's new kvm version; update copyright/header, lint
e
s 00006/00031/00064
d D 5.6 91/06/26 13:50:29 marc 13 12
c changes for new kernel, plus use kvm
e
s 00001/00001/00094
d D 5.5 91/02/04 23:18:47 torek 12 11
c fix gcc-detected lint
e
s 00002/00002/00093
d D 5.4 90/03/12 09:27:15 karels 11 10
c use MAXHOSTNAMELEN
e
s 00003/00000/00092
d D 5.3 89/05/29 17:28:46 mckusick 10 9
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00001/00001/00091
d D 5.2 86/07/20 10:58:09 sam 9 8
c dk.h->dkstat.h
e
s 00007/00001/00085
d D 5.1 85/05/30 16:27:38 mckusick 8 7
c Add copyright
e
s 00021/00006/00065
d D 1.6 85/05/01 01:34:47 sam 7 6
c major rework; fixup netstat stuff; pull disk cmds into common file; change 
c everthing related to disks to use dk_ndrive and global selction; use getw where possible
e
s 00006/00001/00065
d D 1.5 85/04/28 00:37:42 sam 6 5
c add vsta in; add help command (minimal); make loadav display something 
c which can be turned off
e
s 00022/00048/00044
d D 1.4 84/08/09 19:13:16 mckusick 5 4
c update to new sources from sam; weed out unnecessary #includes
e
s 00001/00000/00091
d D 1.3 83/10/02 22:00:16 sam 4 2
c add command prefix recognition
e
s 00001/00000/00091
d R 1.3 83/10/02 21:41:48 sam 3 2
c define getcmd
e
s 00022/00004/00069
d D 1.2 83/10/02 20:46:13 sam 2 1
c reorganize window management to allow display routines to set 
c up optimal window definitions
e
s 00073/00000/00000
d D 1.1 83/10/01 12:21:05 sam 1 0
c date and time created 83/10/01 12:21:05 by sam
e
u
U
t
T
I 1
D 8
/*      %M%     %I%     %E%     */
E 8
I 8
D 14
/*
D 11
 * Copyright (c) 1980 Regents of the University of California.
E 11
I 11
 * Copyright (c) 1980, 1989 Regents of the University of California.
E 11
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
/*-
D 18
 * Copyright (c) 1980, 1989, 1992 The Regents of the University of California.
 * All rights reserved.
E 18
I 18
 * Copyright (c) 1980, 1989, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 18
E 14
 *
I 14
D 17
 * %sccs.include.proprietary.c%
E 17
I 17
 * %sccs.include.redist.c%
E 17
 *
E 14
 *	%W% (Berkeley) %G%
 */
E 8

D 5
#include <sys/param.h>
#include <sys/dir.h>
#include <sys/user.h>
#include <sys/proc.h>
#include <sys/timeb.h>
#include <sys/vm.h>
#include <sys/file.h>
I 2
#include <sys/map.h>
#include <sys/conf.h>
#include <sys/text.h>
E 2

#include <machine/pte.h>

#include <nlist.h>
#include <pwd.h>
#include <math.h>
E 5
I 5
D 7
#include <sys/dk.h>
E 7
I 7
D 14
#include <netdb.h>
#include <nlist.h>
#include <signal.h>
E 14
E 7
E 5
#include <curses.h>
I 10
D 14
#include <math.h>
E 14
E 10
D 5
#include <signal.h>
#include <ctype.h>
E 5

I 7
D 14
#include <sys/param.h>
I 10
D 13
#include <sys/types.h>
E 13
E 10
#include <sys/file.h>
D 9
#include <sys/dk.h>
E 9
I 9
#include <sys/dkstat.h>
E 9

#include <netinet/in.h>
#include <arpa/inet.h>

E 14
E 7
D 2
struct  nlist nlst[];

E 2
D 13
struct p_times {
        short   pt_pid;
        float   pt_pctcpu;
        int     pt_uid;
        int     pt_paddr;
        struct  proc *pt_pp;
} *pt;
I 5
long    nproc, procp;
struct	proc *kprocp;
E 5

struct procs {
        int     pid;
        char    cmd[16];
} procs[200];
int     numprocs;

struct users {
        int     k_uid;
        char    k_name[16];
} known[30];
I 5
int     numknown;
E 5

E 13
I 2
struct  cmdtab {
        char    *c_name;		/* command name */
D 14
        int     (*c_refresh)();		/* display refresh */
        int     (*c_fetch)();		/* sets up data structures */
        int     (*c_label)();		/* label display */
E 14
I 14
        void    (*c_refresh)();		/* display refresh */
        void    (*c_fetch)();		/* sets up data structures */
        void    (*c_label)();		/* label display */
E 14
	int	(*c_init)();		/* initialize namelist, etc. */
	WINDOW	*(*c_open)();		/* open display */
D 14
	int	(*c_close)();		/* close display */
E 14
I 14
	void	(*c_close)();		/* close display */
E 14
I 5
	int	(*c_cmd)();		/* display command interpreter */
E 5
D 6
	char	c_flags;		/* been initialized (right now) */
E 6
I 6
	char	c_flags;		/* see below */
E 6
};

I 6
#define	CF_INIT		0x1		/* been initialized */
#define	CF_LOADAV	0x2		/* display w/ load average */

E 6
D 14
struct	cmdtab *curcmd;
struct	cmdtab cmdtab[];
I 4
struct	cmdtab *lookup();
E 4

E 2
D 5
char    *kmemf;
char    *memf;
char    *swapf;
int     kmem;
int     mem;
int     swap;
D 2
int     pcbpf;
int     argaddr;
E 2
int     col;
long    nproc;
long    procp;
I 2
struct	proc *kprocp;
long	ntext;
long	textp;
E 5
I 5
D 13
int     kmem, mem, swap;
E 13
int     naptime, col;

long	ntext, textp;
E 5
struct	text *xtext;
E 2
D 5
double  ccpu;
E 5
I 5

I 10
D 13
int	fscale;
E 10
E 5
double  lccpu;
E 13
I 6
double	avenrun[3];
E 6
D 5
char    *malloc();
I 2
char    *calloc();
E 2
char    *namp;
char    *strncpy();
char    c;
char    hostname[32];
int     numprocs;
int     numknown;
int     naptime;
int     maxind;
long    getw();
float   total;
int     factor;
double  lave;
int     dellave;
struct  passwd *getpwuid();
char    pidname[30];
E 5
I 5

D 13
char    *kmemf, *memf, *swapf;
E 13
D 7
char	dr_name[DK_NDRIVE][10];
int	ndrives;
int	hz;
I 6
int	phz;
E 6
float	dk_mspw[DK_NDRIVE];
E 7
I 7
int	hz, phz;
char	**dr_name;
int	dk_ndrive;
int	*dk_select;
float	*dk_mspw;
E 7
D 11
char    c, *namp, hostname[32];
E 11
I 11
char    c, *namp, hostname[MAXHOSTNAMELEN];
E 11
I 7

int	nports;
int	nhosts;
int	protos;
E 14
#define	TCP	0x1
#define	UDP	0x2
E 7
D 14

E 5
D 13
struct  pte *usrpt;
struct  pte *Usrptma;

E 13
WINDOW  *wnd;
I 5
int	CMDLINE;

char    *malloc(), *calloc(), *strncpy();
E 14
D 12
long    getw();
E 12
I 12
D 13
long    getword();
E 13
I 13

#define KREAD(addr, buf, len)  kvm_ckread((addr), (buf), (len))
D 15
#define NVAL(indx)  nlst[(indx)].n_value
E 15
I 15
D 16
#define NVAL(indx)  nl[(indx)].n_value
E 16
I 16
#define NVAL(indx)  namelist[(indx)].n_value
E 16
E 15
#define NPTR(indx)  (void *)NVAL((indx))
#define NREAD(indx, buf, len) kvm_ckread(NPTR((indx)), (buf), (len))
#define LONG	(sizeof (long))
E 13
E 12
E 5
E 1
