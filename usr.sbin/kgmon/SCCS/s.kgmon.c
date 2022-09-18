h29842
s 00005/00005/00489
d D 8.1 93/06/06 13:57:44 bostic 27 26
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00356/00209/00138
d D 5.17 93/05/02 15:42:57 mckusick 26 25
c massive overhaul to get it to use sysctl on live kernels while still
c using the kvm library for dead kernels
e
s 00021/00013/00326
d D 5.16 93/04/29 09:17:35 mckusick 25 24
c use sysctl to start and stop profiling
e
s 00017/00031/00322
d D 5.15 93/04/20 17:30:11 mckusick 24 23
c update to reflect sizes being available in gmonparam structure
e
s 00225/00190/00128
d D 5.14 92/07/10 16:59:12 mckusick 23 22
c massive rewrite for new kernel profiling interface from mccanne at LBL
e
s 00122/00140/00196
d D 5.13 92/05/19 01:08:54 torek 22 21
c rewrite to use kvm library
e
s 00015/00002/00321
d D 5.12 91/07/01 12:21:39 karels 21 20
c disable kflag for new vm
e
s 00019/00009/00304
d D 5.11 91/06/06 10:22:18 bostic 20 19
c add -M, -N for consistency with other stat programs
c CMU/Mach fix; add exit(0) at end of main()
e
s 00001/00011/00312
d D 5.10 90/06/01 18:41:36 bostic 19 18
c new copyright notice
e
s 00001/00001/00322
d D 5.9 89/05/11 14:08:35 bostic 18 17
c file reorg, pathnames.h, paths.h
e
s 00008/00009/00315
d D 5.8 89/05/03 07:45:44 bostic 17 16
c fix botched fix for botched introduction of getopt
e
s 00002/00000/00322
d D 5.7 89/04/25 17:44:54 mckusick 16 15
c fix botched introduction of getopt
e
s 00028/00021/00294
d D 5.6 89/04/02 14:23:20 bostic 15 14
c add pathnames.h, lint/error message consistency
e
s 00015/00004/00300
d D 5.5 88/11/12 10:53:42 bostic 14 13
c written by Kirk McKusick; add Berkeley copyright notice
e
s 00065/00084/00239
d D 5.4 88/05/04 19:57:48 bostic 13 12
c add getopt, read dead kernels correctly, lint fluff
e
s 00003/00000/00320
d D 5.3 86/10/13 15:03:00 sam 12 11
c tahoe support
e
s 00023/00020/00297
d D 5.2 86/02/18 17:02:08 sam 11 10
c use L_SET, O_RDONLY; make vax dependency explicit
e
s 00014/00002/00303
d D 5.1 85/05/28 14:24:47 dist 10 9
c add copyright
e
s 00001/00003/00304
d D 4.9 83/08/11 22:51:32 sam 9 8
c standardize sccs keyword lines
e
s 00001/00001/00306
d D 4.8 83/07/01 03:14:19 sam 8 7
c nil pointer
e
s 00004/00001/00303
d D 4.7 83/03/10 18:51:12 sam 7 6
c from shannon
e
s 00014/00010/00290
d D 4.6 83/01/16 15:55:58 mckusick 6 5
c change -s to -p, no longer generate gmon.out by default
e
s 00009/00005/00291
d D 4.5 83/01/15 16:43:29 mckusick 5 4
c fix up exit codes; make messages more accurate
e
s 00011/00011/00285
d D 4.4 83/01/15 16:10:46 mckusick 4 3
c fix up exit codes; pte.h moves from sys => machine
e
s 00120/00047/00176
d D 4.3 83/01/15 15:41:17 mckusick 3 2
c new austere memory version; add wondrous flags
e
s 00001/00001/00222
d D 4.2 82/12/24 12:55:01 sam 2 1
c header files moved around a bit
e
s 00223/00000/00000
d D 4.1 82/06/21 00:52:43 mckusick 1 0
c date and time created 82/06/21 00:52:43 by mckusick
e
u
U
t
T
I 10
/*
D 14
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 14
I 14
D 22
 * Copyright (c) 1983 The Regents of the University of California.
E 22
I 22
D 27
 * Copyright (c) 1983, 1992 The Regents of the University of California.
E 22
 * All rights reserved.
E 27
I 27
 * Copyright (c) 1983, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 27
 *
D 19
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 14
 */

E 10
I 1
D 9
/* Copyright (c) 1982 Regents of the University of California */

E 9
#ifndef lint
D 9
static char sccsid[] = "%W% %E%";
E 9
I 9
D 10
static char sccsid[] = "%W% (Berkeley) %E%";
E 9
#endif
E 10
I 10
D 27
char copyright[] =
D 14
"%Z% Copyright (c) 1983 Regents of the University of California.\n\
E 14
I 14
D 22
"%Z% Copyright (c) 1983 The Regents of the University of California.\n\
E 22
I 22
"%Z% Copyright (c) 1983, 1992 The Regents of the University of California.\n\
E 22
E 14
 All rights reserved.\n";
E 27
I 27
static char copyright[] =
"%Z% Copyright (c) 1983, 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 27
D 13
#endif not lint
E 13
I 13
#endif /* not lint */
E 13

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 13
#endif not lint
E 13
I 13
#endif /* not lint */
E 13
E 10

D 15
#include <sys/param.h>
E 15
D 2
#include <sys/pte.h>
E 2
I 2
D 3
#include <machine/pte.h>
E 3
I 3
D 4
#include <sys/pte.h>
E 4
I 4
D 21
#include <machine/pte.h>
I 15

E 21
#include <sys/param.h>
I 21
D 22
#if BSD >= 199103
#define NEWVM
#endif
E 22
E 21
E 15
I 11
#include <sys/file.h>
I 25
#include <sys/sysctl.h>
E 25
I 21
D 22
#ifndef NEWVM
#include <machine/pte.h>
E 21
E 11
I 7
#include <sys/vm.h>
I 21
#endif
E 22
E 21
I 15
D 23
#include <sys/gprof.h>
E 23
I 23
#include <sys/gmon.h>
E 23
I 22
#include <errno.h>
#include <kvm.h>
#include <limits.h>
E 22
E 15
E 7
E 4
E 3
E 2
#include <stdio.h>
I 22
#include <stdlib.h>
#include <string.h>
E 22
#include <nlist.h>
#include <ctype.h>
D 3
#include <sys/crt0.h>
E 3
I 3
D 15
#include <sys/gprof.h>
E 15
I 15
D 18
#include "pathnames.h"
E 18
I 18
#include <paths.h>
E 18
E 15
E 3

D 23
#define	PROFILING_ON	0
D 13
#define PROFILING_OFF	3
E 13
I 13
#define	PROFILING_OFF	3
E 13

E 23
D 13
/*
 * froms is actually a bunch of unsigned shorts indexing tos
 */
u_short	*froms;
struct	tostruct *tos;
char	*s_lowpc;
E 13
D 22
u_long	s_textsize;
I 13
off_t	sbuf, klseek(), lseek();
E 13
int	ssiz;
D 13
off_t	sbuf;
E 13

E 22
struct nlist nl[] = {
D 22
#define	N_SYSMAP	0
	{ "_Sysmap" },
#define	N_SYSSIZE	1
	{ "_Syssize" },
#define N_FROMS		2
E 22
I 22
D 23
#define N_FROMS		0
E 22
	{ "_froms" },
D 22
#define	N_PROFILING	3
E 22
I 22
#define	N_PROFILING	1
E 22
	{ "_profiling" },
D 22
#define	N_S_LOWPC	4
E 22
I 22
#define	N_S_LOWPC	2
E 22
	{ "_s_lowpc" },
D 22
#define	N_S_TEXTSIZE	5
E 22
I 22
#define	N_S_TEXTSIZE	3
E 22
	{ "_s_textsize" },
D 22
#define	N_SBUF		6
E 22
I 22
#define	N_SBUF		4
E 22
	{ "_sbuf" },
D 22
#define N_SSIZ		7
E 22
I 22
#define N_SSIZ		5
E 22
	{ "_ssiz" },
D 22
#define	N_TOS		8
E 22
I 22
#define	N_TOS		6
E 22
	{ "_tos" },
E 23
I 23
#define	N_GMONPARAM	0
	{ "__gmonparam" },
D 24
#define	N_KCOUNT	1
	{ "_kcount" },
#define	N_PROFHZ	2
E 24
I 24
#define	N_PROFHZ	1
E 24
	{ "_profhz" },
E 23
	0,
};

I 23
D 26
/*
 * We should call this _gmonparam for consistency, but that would cause a 
 * problem if we want to profile this program itself.
 */
struct gmonparam gmonparam;
E 26
I 26
struct kvmvars {
	kvm_t	*kd;
	struct gmonparam gpm;
};
E 26

D 24
u_short *kcount;
E 24
D 26
int profhz;

E 23
I 11
D 13
#if defined(vax)
#define	clear(x)	((x) &~ 0x80000000)
#endif
I 12
#if defined(tahoe)
#define	clear(x)	((x) &~ 0xc0000000)
#endif
E 12

E 13
E 11
D 22
struct	pte *Sysmap;

D 13
char	*system = "/vmunix";
char	*kmemf = "/dev/kmem";
E 13
int	kmem;
E 22
I 22
kvm_t	*kd;
E 26
E 22
D 3
int	kflg;
E 3
I 3
D 6
int	bflag, hflag, kflag, rflag, sflag;
E 6
I 6
int	bflag, hflag, kflag, rflag, pflag;
E 6
int	debug = 0;
I 26
void	setprof __P((struct kvmvars *kvp, int state));
void	dumpstate __P((struct kvmvars *kvp));
void	reset __P((struct kvmvars *kvp));
E 26
E 3

D 23
main(argc, argv)
	int argc;
D 17
	char *argv[];
E 17
I 17
	char **argv;
E 23
I 23
D 26
#define KREAD(kd, addr, s)\
	kvm_read(kd, addr, (void *)(s), sizeof*(s)) != (sizeof*(s))

/*
 * Build the gmon header and write it to a file.
 */
void
D 24
dumphdr(FILE *fp, struct gmonparam *p, int ksize)
E 24
I 24
dumphdr(FILE *fp, struct gmonparam *p)
E 26
I 26
int
main(int argc, char **argv)
E 26
E 24
E 23
E 17
{
I 23
D 26
	struct gmonhdr h;
E 26
I 26
	extern char *optarg;
	extern int optind;
	int ch, mode, disp, accessmode;
	struct kvmvars kvmvars;
	char *system, *kmemf;
E 26

D 26
	/* zero out the unused fields */
	bzero(&h, sizeof(h));
E 26
I 26
	seteuid(getuid());
	kmemf = NULL;
	system = NULL;
	while ((ch = getopt(argc, argv, "M:N:bhpr")) != EOF) {
		switch((char)ch) {
E 26

D 26
	h.lpc = p->lowpc;
	h.hpc = p->highpc;
D 24
	h.ncnt = ksize + sizeof(h);
E 24
I 24
	h.ncnt = p->kcountsize + sizeof(h);
E 24
	h.version = GMONVERSION;
	h.profrate = profhz;
E 26
I 26
		case 'M':
			kmemf = optarg;
			kflag = 1;
			break;
E 26

D 26
	fwrite((char *)&h, sizeof(h), 1, fp);
E 26
I 26
		case 'N':
			system = optarg;
			break;

		case 'b':
			bflag = 1;
			break;

		case 'h':
			hflag = 1;
			break;

		case 'p':
			pflag = 1;
			break;

		case 'r':
			rflag = 1;
			break;

		default:
			(void)fprintf(stderr,
			    "usage: kgmon [-bhrp] [-M core] [-N system]\n");
			exit(1);
		}
	}
	argc -= optind;
	argv += optind;

#define BACKWARD_COMPATIBILITY
#ifdef	BACKWARD_COMPATIBILITY
	if (*argv) {
		system = *argv;
		if (*++argv) {
			kmemf = *argv;
			++kflag;
		}
	}
#endif
	if (system == NULL)
		system = _PATH_UNIX;
	accessmode = openfiles(system, kmemf, &kvmvars);
	mode = getprof(&kvmvars);
	if (hflag)
		disp = GMON_PROF_OFF;
	else if (bflag)
		disp = GMON_PROF_ON;
	else
		disp = mode;
	if (pflag)
		dumpstate(&kvmvars);
	if (rflag)
		reset(&kvmvars);
	if (accessmode == O_RDWR)
		setprof(&kvmvars, disp);
	(void)fprintf(stdout, "kgmon: kernel profiling is %s.\n",
		      disp == GMON_PROF_OFF ? "off" : "running");
	return (0);
E 26
}

/*
D 26
 * Dump a range of kernel memory to a file.
E 26
I 26
 * Check that profiling is enabled and open any ncessary files.
E 26
 */
D 26
void
dumpbuf(FILE *fp, u_long addr, int cc)
E 26
I 26
openfiles(system, kmemf, kvp)
	char *system;
	char *kmemf;
	struct kvmvars *kvp;
E 26
{
D 26
	int ret, n;
	char buf[8192];
E 26
I 26
	int mib[3], state, size, openmode;
	char errbuf[_POSIX2_LINE_MAX];
E 26

D 26
	while (cc > 0) {
		n = MIN(cc, sizeof(buf));
		if ((ret = kvm_read(kd, addr, buf, n)) != n) {
E 26
I 26
	if (!kflag) {
		mib[0] = CTL_KERN;
		mib[1] = KERN_PROF;
		mib[2] = GPROF_STATE;
		size = sizeof state;
		if (sysctl(mib, 3, &state, &size, NULL, 0) < 0) {
E 26
			(void)fprintf(stderr,
D 26
			    "kgmon: read kmem: read %d, got %d: %s\n",
			    n, ret, kvm_geterr(kd));
			exit(4);
E 26
I 26
			    "kgmon: profiling not defined in kernel.\n");
			exit(20);
E 26
		}
D 26
		if ((ret = fwrite(buf, n, 1, fp)) != 1) {
			perror("kgmon: gmon.out");
			exit(1);
E 26
I 26
		if (!(bflag || hflag || rflag ||
		    (pflag && state == GMON_PROF_ON)))
			return (O_RDONLY);
		(void)seteuid(0);
		if (sysctl(mib, 3, NULL, NULL, &state, size) >= 0)
			return (O_RDWR);
		(void)seteuid(getuid());
		kern_readonly(state);
		return (O_RDONLY);
	}
	openmode = (bflag || hflag || pflag || rflag) ? O_RDWR : O_RDONLY;
	kvp->kd = kvm_openfiles(system, kmemf, NULL, openmode, errbuf);
	if (kvp->kd == NULL) {
		if (openmode == O_RDWR) {
			openmode = O_RDONLY;
			kvp->kd = kvm_openfiles(system, kmemf, NULL, O_RDONLY,
			    errbuf);
E 26
		}
D 26
		addr += n;
		cc -= n;
E 26
I 26
		if (kvp->kd == NULL) {
			(void)fprintf(stderr, "kgmon: kvm_openfiles: %s\n",
			    errbuf);
			exit(2);
		}
		kern_readonly(GMON_PROF_ON);
E 26
	}
I 26
	if (kvm_nlist(kvp->kd, nl) < 0) {
		(void)fprintf(stderr, "kgmon: %s: no namelist\n", system);
		exit(3);
	}
	if (!nl[N_GMONPARAM].n_value) {
		(void)fprintf(stderr,
		    "kgmon: profiling not defined in kernel.\n");
		exit(20);
	}
	return (openmode);
E 26
}

/*
I 26
 * Suppress options that require a writable kernel.
 */
kern_readonly(mode)
	int mode;
{

	(void)fprintf(stderr, "kgmon: kernel read-only: ");
	if (pflag && mode == GMON_PROF_ON)
		(void)fprintf(stderr, "data may be inconsistent\n");
	if (rflag)
		(void)fprintf(stderr, "-r supressed\n");
	if (bflag)
		(void)fprintf(stderr, "-b supressed\n");
	if (hflag)
		(void)fprintf(stderr, "-h supressed\n");
	rflag = bflag = hflag = 0;
}

/*
 * Get the state of kernel profiling.
 */
getprof(kvp)
	struct kvmvars *kvp;
{
	int mib[3], size;

	if (kflag) {
		size = kvm_read(kvp->kd, nl[N_GMONPARAM].n_value, &kvp->gpm,
		    sizeof kvp->gpm);
	} else {
		mib[0] = CTL_KERN;
		mib[1] = KERN_PROF;
		mib[2] = GPROF_GMONPARAM;
		size = sizeof kvp->gpm;
		if (sysctl(mib, 3, &kvp->gpm, &size, NULL, 0) < 0)
			size = 0;
	}
	if (size != sizeof kvp->gpm) {
		(void)fprintf(stderr, "kgmon: cannot get gmonparam: %s\n",
		    kflag ? kvm_geterr(kvp->kd) : strerror(errno));
		exit (4);
	}
	return (kvp->gpm.state);
}

/*
E 26
 * Enable or disable kernel profiling according to the state variable.
 */
void
D 26
setprof(int state)
E 26
I 26
setprof(kvp, state)
	struct kvmvars *kvp;
	int state;
E 26
{
	struct gmonparam *p = (struct gmonparam *)nl[N_GMONPARAM].n_value;
I 25
D 26
	int mib[3], sz;
E 26
I 26
	int mib[3], sz, oldstate;
E 26
E 25

D 25
	if (kvm_write(kd, (u_long)&p->state, (void *)&state, sizeof(state)) !=
	    sizeof(state))
		(void)fprintf(stderr,
		    "kgmon: warning: can't turn profiling %s\n",
		    state == GMON_PROF_OFF ? "off" : "on");
E 25
I 25
	sz = sizeof(state);
	if (!kflag) {
		mib[0] = CTL_KERN;
		mib[1] = KERN_PROF;
		mib[2] = GPROF_STATE;
D 26
		if (sysctl(mib, 3, NULL, NULL, &state, sz) >= 0)
E 26
I 26
		if (sysctl(mib, 3, &oldstate, &sz, NULL, 0) < 0)
			goto bad;
		if (oldstate == state)
E 26
			return;
D 26
	} else if (kvm_write(kd, (u_long)&p->state, (void *)&state, sz) == sz)
E 26
I 26
		(void)seteuid(0);
		if (sysctl(mib, 3, NULL, NULL, &state, sz) >= 0) {
			(void)seteuid(getuid());
			return;
		}
		(void)seteuid(getuid());
	} else if (kvm_write(kvp->kd, (u_long)&p->state, (void *)&state, sz) 
	    == sz)
E 26
		return;
I 26
bad:
E 26
	(void)fprintf(stderr, "kgmon: warning: cannot turn profiling %s\n",
	    state == GMON_PROF_OFF ? "off" : "on");
E 25
}

/*
 * Build the gmon.out file.
 */
void
D 26
dumpstate(struct gmonparam *p)
E 26
I 26
dumpstate(kvp)
	struct kvmvars *kvp;
E 26
{
	register FILE *fp;
	struct rawarc rawarc;
	struct tostruct *tos;
	u_long frompc, addr;
D 26
	u_short *froms;
	int i, n;
E 26
I 26
	u_short *froms, *tickbuf;
	int mib[3], i;
	struct gmonhdr h;
E 26
	int fromindex, endfrom, toindex;
D 24
	u_int fromssize, tossize, ksize;
E 24

D 26
	setprof(GMON_PROF_OFF);
E 26
I 26
	setprof(kvp, GMON_PROF_OFF);
E 26
	fp = fopen("gmon.out", "w");
	if (fp == 0) {
		perror("gmon.out");
		return;
	}
D 24
	ksize = p->textsize / HISTFRACTION;
	dumphdr(fp, p, ksize);
	dumpbuf(fp, (u_long)kcount, ksize);
E 24
I 24
D 26
	dumphdr(fp, p);
	dumpbuf(fp, (u_long)p->kcount, p->kcountsize);
E 26
E 24

D 24
	fromssize = p->textsize / HASHFRACTION;
	froms = (u_short *)malloc(fromssize);
	i = kvm_read(kd, (u_long)p->froms, (void *)froms, fromssize);
	if (i != fromssize) {
E 24
I 24
D 26
	froms = (u_short *)malloc(p->fromssize);
	i = kvm_read(kd, (u_long)p->froms, (void *)froms, p->fromssize);
	if (i != p->fromssize) {
E 24
		(void)fprintf(stderr, "kgmon: read kmem: read %u, got %d: %s",
D 24
		    fromssize, i, strerror(errno));
E 24
I 24
		    p->fromssize, i, strerror(errno));
E 24
		exit(5);
E 26
I 26
	/*
	 * Build the gmon header and write it to a file.
	 */
	bzero(&h, sizeof(h));
	h.lpc = kvp->gpm.lowpc;
	h.hpc = kvp->gpm.highpc;
	h.ncnt = kvp->gpm.kcountsize + sizeof(h);
	h.version = GMONVERSION;
	h.profrate = getprofhz(kvp);
	fwrite((char *)&h, sizeof(h), 1, fp);

	/*
	 * Write out the tick buffer.
	 */
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROF;
	if ((tickbuf = (u_short *)malloc(kvp->gpm.kcountsize)) == NULL) {
		fprintf(stderr, "kgmon: cannot allocate kcount space\n");
		exit (5);
E 26
	}
D 24
	tossize = (p->textsize * ARCDENSITY / 100) * sizeof(struct tostruct);
	tos = (struct tostruct *)malloc(tossize);
	i = kvm_read(kd, (u_long)p->tos, (void *)tos, tossize);
	if (i != tossize) {
E 24
I 24
D 26
	tos = (struct tostruct *)malloc(p->tossize);
	i = kvm_read(kd, (u_long)p->tos, (void *)tos, p->tossize);
	if (i != p->tossize) {
E 24
		(void)fprintf(stderr, "kgmon: read kmem: read %u, got %d: %s",
D 24
		    tossize, i, kvm_geterr(kd));
E 24
I 24
		    p->tossize, i, kvm_geterr(kd));
E 26
I 26
	if (kflag) {
		i = kvm_read(kvp->kd, (u_long)kvp->gpm.kcount, (void *)tickbuf,
		    kvp->gpm.kcountsize);
	} else {
		mib[2] = GPROF_COUNT;
		i = kvp->gpm.kcountsize;
		if (sysctl(mib, 3, tickbuf, &i, NULL, 0) < 0)
			i = 0;
	}
	if (i != kvp->gpm.kcountsize) {
		(void)fprintf(stderr, "kgmon: read ticks: read %u, got %d: %s",
		    kvp->gpm.kcountsize, i,
		    kflag ? kvm_geterr(kvp->kd) : strerror(errno));
E 26
E 24
		exit(6);
	}
I 26
	if ((fwrite(tickbuf, kvp->gpm.kcountsize, 1, fp)) != 1) {
		perror("kgmon: writing tocks to gmon.out");
		exit(7);
	}
	free(tickbuf);

	/*
	 * Write out the arc info.
	 */
	if ((froms = (u_short *)malloc(kvp->gpm.fromssize)) == NULL) {
		fprintf(stderr, "kgmon: cannot allocate froms space\n");
		exit (8);
	}
	if (kflag) {
		i = kvm_read(kvp->kd, (u_long)kvp->gpm.froms, (void *)froms,
		    kvp->gpm.fromssize);
	} else {
		mib[2] = GPROF_FROMS;
		i = kvp->gpm.fromssize;
		if (sysctl(mib, 3, froms, &i, NULL, 0) < 0)
			i = 0;
	}
	if (i != kvp->gpm.fromssize) {
		(void)fprintf(stderr, "kgmon: read froms: read %u, got %d: %s",
		    kvp->gpm.fromssize, i,
		    kflag ? kvm_geterr(kvp->kd) : strerror(errno));
		exit(9);
	}
	if ((tos = (struct tostruct *)malloc(kvp->gpm.tossize)) == NULL) {
		fprintf(stderr, "kgmon: cannot allocate tos space\n");
		exit(10);
	}
	if (kflag) {
		i = kvm_read(kvp->kd, (u_long)kvp->gpm.tos, (void *)tos,
		    kvp->gpm.tossize);
	} else {
		mib[2] = GPROF_TOS;
		i = kvp->gpm.tossize;
		if (sysctl(mib, 3, tos, &i, NULL, 0) < 0)
			i = 0;
	}
	if (i != kvp->gpm.tossize) {
		(void)fprintf(stderr, "kgmon: read tos: read %u, got %d: %s",
		    kvp->gpm.tossize, i,
		    kflag ? kvm_geterr(kvp->kd) : strerror(errno));
		exit(11);
	}
E 26
	if (debug)
D 26
		(void)fprintf(stderr, "lowpc 0x%x, textsize 0x%x\n",
			      p->lowpc, p->textsize);
D 24
	endfrom = fromssize / sizeof(*froms);
E 24
I 24
	endfrom = p->fromssize / sizeof(*froms);
E 26
I 26
		(void)fprintf(stderr, "kgmon: lowpc 0x%x, textsize 0x%x\n",
			      kvp->gpm.lowpc, kvp->gpm.textsize);
	endfrom = kvp->gpm.fromssize / sizeof(*froms);
E 26
E 24
	for (fromindex = 0; fromindex < endfrom; ++fromindex) {
		if (froms[fromindex] == 0)
			continue;
D 26
		frompc = (u_long)p->lowpc +
		    (fromindex * HASHFRACTION * sizeof(*froms));
E 26
I 26
		frompc = (u_long)kvp->gpm.lowpc +
		    (fromindex * kvp->gpm.hashfraction * sizeof(*froms));
E 26
		for (toindex = froms[fromindex]; toindex != 0;
		   toindex = tos[toindex].link) {
			if (debug)
			    (void)fprintf(stderr,
D 26
			    "[mcleanup] frompc 0x%x selfpc 0x%x count %d\n" ,
			    frompc, tos[toindex].selfpc, tos[toindex].count);
E 26
I 26
			    "%s: [mcleanup] frompc 0x%x selfpc 0x%x count %d\n",
			    "kgmon", frompc, tos[toindex].selfpc,
			    tos[toindex].count);
E 26
			rawarc.raw_frompc = frompc;
			rawarc.raw_selfpc = (u_long)tos[toindex].selfpc;
			rawarc.raw_count = tos[toindex].count;
			fwrite((char *)&rawarc, sizeof(rawarc), 1, fp);
		}
	}
	fclose(fp);
}

/*
D 26
 * Zero out a region of kernel memory.
E 26
I 26
 * Get the profiling rate.
E 26
 */
int
D 26
kzero(u_long addr, int cc)
E 26
I 26
getprofhz(kvp)
	struct kvmvars *kvp;
E 26
{
D 26
	static char zbuf[MAXBSIZE];
E 26
I 26
	int mib[2], size, profrate;
	struct clockinfo clockrate;
E 26

D 26
	while (cc > 0) {
		register int n = MIN(cc, sizeof(zbuf));

		if (kvm_write(kd, addr, zbuf, n) != n)
			return (-1);
		addr += n;
		cc -= n;
E 26
I 26
	if (kflag) {
		profrate = 1;
		if (kvm_read(kvp->kd, nl[N_PROFHZ].n_value, &profrate,
		    sizeof profrate) != sizeof profrate)
			(void)fprintf(stderr, "kgmon: get clockrate: %s\n",
				kvm_geterr(kvp->kd));
		return (profrate);
E 26
	}
D 26
	return (0);
E 26
I 26
	mib[0] = CTL_KERN;
	mib[1] = KERN_CLOCKRATE;
	clockrate.profhz = 1;
	size = sizeof clockrate;
	if (sysctl(mib, 2, &clockrate, &size, NULL, 0) < 0)
		(void)fprintf(stderr, "kgmon: get clockrate: %s\n",
			strerror(errno));
	return (clockrate.profhz);
E 26
}

/*
 * Reset the kernel profiling date structures.
 */
void
D 26
reset(struct gmonparam *p)
E 26
I 26
reset(kvp)
	struct kvmvars *kvp;
E 26
{
I 26
	char *zbuf;
	u_long biggest;
	int mib[3];
E 26
D 24
	int fromssize, tossize, ksize;
E 24

D 26
	setprof(GMON_PROF_OFF);
E 26
I 26
	setprof(kvp, GMON_PROF_OFF);
E 26

D 24
	ksize = p->textsize / HISTFRACTION;
	if (kzero((u_long)kcount, ksize)) {
E 24
I 24
D 26
	if (kzero((u_long)p->kcount, p->kcountsize)) {
E 24
		(void)fprintf(stderr, "kgmon: sbuf write: %s\n",
		    kvm_geterr(kd));
		exit(7);
E 26
I 26
	biggest = kvp->gpm.kcountsize;
	if (kvp->gpm.fromssize > biggest)
		biggest = kvp->gpm.fromssize;
	if (kvp->gpm.tossize > biggest)
		biggest = kvp->gpm.tossize;
	if ((zbuf = (char *)malloc(biggest)) == NULL) {
		fprintf(stderr, "kgmon: cannot allocate zbuf space\n");
		exit(12);
E 26
	}
D 24
	fromssize = p->textsize / HASHFRACTION;
	if (kzero((u_long)p->froms, fromssize)) {
E 24
I 24
D 26
	if (kzero((u_long)p->froms, p->fromssize)) {
E 24
		(void)fprintf(stderr, "kgmon: kfroms write: %s\n",
		    kvm_geterr(kd));
		exit(8);
	}
D 24
	tossize = (p->textsize * ARCDENSITY / 100) * sizeof(struct tostruct);
	if (kzero((u_long)p->tos, tossize)) {
E 24
I 24
	if (kzero((u_long)p->tos, p->tossize)) {
E 24
		(void)fprintf(stderr, "kgmon: ktos write: %s\n",
		    kvm_geterr(kd));
		exit(9);
	}
}

int
main(int argc, char **argv)
{
E 23
D 3
	int i, j, k;
	char *cp;
	long conptr;
	int fd;
	int fromindex;
	u_long frompc;
	int toindex;
	struct rawarc rawarc;
	off_t kfroms, ktos;
	char buf[BUFSIZ];
	int debug = 0;
E 3
I 3
D 5
	int disp;
E 5
I 5
D 6
	int mode, disp, ronly = 0;
E 6
I 6
D 11
	int mode, disp, openmode = 0;
E 11
I 11
D 13
	int mode, disp, openmode = O_RDONLY;
E 13
I 13
	extern char *optarg;
	extern int optind;
	int ch, mode, disp, openmode;
D 22
	char *system, *kmemf, *malloc();
E 22
I 22
	char *system, *kmemf;
	char errbuf[_POSIX2_LINE_MAX];
E 22
E 13
E 11
E 6
E 5
E 3

D 13
	argc--, argv++;
I 3
D 8
	while (argv[0][0] == '-') {
E 8
I 8
	while (argc > 0 && argv[0][0] == '-') {
E 8
		switch (argv[0][1]) {
E 13
I 13
D 20
	while ((ch = getopt(argc, argv, "bhpr")) != EOF)
E 20
I 20
D 22
	kmemf = _PATH_KMEM;
	system = _PATH_UNIX;
E 22
I 22
	kmemf = NULL;
	system = NULL;
E 22
D 23
	while ((ch = getopt(argc, argv, "M:N:bhpr")) != EOF)
E 23
I 23
	while ((ch = getopt(argc, argv, "M:N:bhpr")) != EOF) {
E 23
E 20
		switch((char)ch) {
I 23

E 23
I 20
		case 'M':
			kmemf = optarg;
			kflag = 1;
			break;
I 23

E 23
		case 'N':
			system = optarg;
			break;
I 23

E 23
E 20
E 13
		case 'b':
D 20
			bflag++;
E 20
I 20
			bflag = 1;
E 20
I 6
D 11
			openmode = 2;
E 11
I 11
D 13
			openmode = O_RDWR;
E 13
E 11
E 6
			break;
I 23

E 23
		case 'h':
D 20
			hflag++;
E 20
I 20
			hflag = 1;
E 20
I 6
D 11
			openmode = 2;
E 11
I 11
D 13
			openmode = O_RDWR;
E 13
E 11
E 6
			break;
I 23

E 23
D 13
		case 'r':
			rflag++;
I 6
D 11
			openmode = 2;
E 11
I 11
			openmode = O_RDWR;
E 11
E 6
			break;
E 13
D 6
		case 's':
			sflag++;
E 6
I 6
		case 'p':
D 20
			pflag++;
E 20
I 20
			pflag = 1;
E 20
D 11
			openmode = 2;
E 11
I 11
D 13
			openmode = O_RDWR;
E 13
E 11
E 6
			break;
I 23

E 23
I 13
		case 'r':
D 20
			rflag++;
E 20
I 20
			rflag = 1;
E 20
			break;
I 23

E 23
E 13
		default:
D 6
			printf("Usage: kgmon [ -b -h -r -s system memory ]\n");
E 6
I 6
D 13
			printf("Usage: kgmon [ -b -h -r -p system memory ]\n");
E 13
I 13
D 15
			fputs("usage: kgmon [-bhrp] [system [core]]\n", stderr);
E 15
I 15
			(void)fprintf(stderr,
D 20
			    "usage: kgmon [-bhrp] [system [core]]\n");
E 20
I 20
			    "usage: kgmon [-bhrp] [-M core] [-N system]\n");
E 20
E 15
E 13
E 6
			exit(1);
E 26
I 26
	bzero(zbuf, biggest);
	if (kflag) {
		if (kvm_write(kvp->kd, (u_long)kvp->gpm.kcount, zbuf,
		    kvp->gpm.kcountsize) != kvp->gpm.kcountsize) {
			(void)fprintf(stderr, "kgmon: tickbuf zero: %s\n",
			    kvm_geterr(kvp->kd));
			exit(13);
E 26
		}
I 23
D 26
	}
E 23
I 17
	argc -= optind;
	argv += optind;
E 17
D 13
		argc--, argv++;
	}
E 13
I 13

D 17
	openmode = (bflag || hflag || pflag || rflag) ? O_RDWR : O_RDONLY;

I 16
	argv += optind + 1;
	argc -= optind + 1;
E 17
E 16
D 15
	kmemf = "/dev/kmem";
E 15
I 15
D 20
	kmemf = _PATH_KMEM;
E 20
I 20
#define BACKWARD_COMPATIBILITY
#ifdef	BACKWARD_COMPATIBILITY
E 20
E 15
E 13
E 3
D 17
	if (argc > 0) {
E 17
I 17
	if (*argv) {
E 17
		system = *argv;
D 17
		argv++, argc--;
I 13
		if (argc > 0) {
E 17
I 17
		if (*++argv) {
E 17
			kmemf = *argv;
D 17
			kflag++;
E 17
I 17
			++kflag;
E 26
I 26
		if (kvm_write(kvp->kd, (u_long)kvp->gpm.froms, zbuf,
		    kvp->gpm.fromssize) != kvp->gpm.fromssize) {
			(void)fprintf(stderr, "kgmon: froms zero: %s\n",
			    kvm_geterr(kvp->kd));
			exit(14);
E 26
E 17
		}
E 13
D 26
	}
D 13
	nlist(system, nl);
	if (nl[0].n_type == 0) {
E 13
I 13
D 20
	else
D 15
		system = "/vmunix";
E 15
I 15
		system = _PATH_UNIX;
E 20
I 20
#endif
E 20
E 15
D 23

E 23
D 22
	if (nlist(system, nl) < 0 || nl[0].n_type == 0) {
E 13
D 15
		fprintf(stderr, "%s: no namelist\n", system);
E 15
I 15
		(void)fprintf(stderr, "kgmon: %s: no namelist\n", system);
E 15
D 4
		exit(1);
E 4
I 4
		exit(2);
E 4
	}
D 13
	if (argc > 0) {
		kmemf = *argv;
D 3
		kflg++;
E 3
I 3
		kflag++;
E 13
I 13
	if (!nl[N_PROFILING].n_value) {
D 15
		fputs("profiling: not defined in kernel.\n", stderr);
E 15
I 15
		(void)fprintf(stderr,
		    "kgmon: profiling: not defined in kernel.\n");
E 15
		exit(10);
E 13
E 3
	}
I 17

E 22
I 22
	if (system == NULL)
		system = _PATH_UNIX;
E 22
D 25
	openmode = (bflag || hflag || pflag || rflag) ? O_RDWR : O_RDONLY;
E 25
I 25
	if (!kflag)
		openmode = rflag ? O_RDWR : O_RDONLY;
	else
		openmode = 
		    (bflag || hflag || pflag || rflag) ? O_RDWR : O_RDONLY;
E 25
E 17
D 6
	kmem = open(kmemf, 2);
E 6
I 6
D 22
	kmem = open(kmemf, openmode);
E 6
	if (kmem < 0) {
D 6
		kmem = open(kmemf, 0);
E 6
I 6
D 11
		openmode = 0;
E 11
I 11
		openmode = O_RDONLY;
E 11
		kmem = open(kmemf, openmode);
E 6
		if (kmem < 0) {
D 13
			fprintf(stderr, "cannot open ");
E 13
			perror(kmemf);
D 4
			exit(1);
E 4
I 4
			exit(3);
E 22
I 22
	kd = kvm_openfiles(system, kmemf, NULL, openmode, errbuf);
	if (kd == NULL) {
		if (openmode == O_RDWR) {
			openmode = O_RDONLY;
			kd = kvm_openfiles(system, kmemf, NULL, O_RDONLY,
			    errbuf);
E 26
I 26
		if (kvm_write(kvp->kd, (u_long)kvp->gpm.tos, zbuf,
		    kvp->gpm.tossize) != kvp->gpm.tossize) {
			(void)fprintf(stderr, "kgmon: tos zero: %s\n",
			    kvm_geterr(kvp->kd));
			exit(15);
E 26
E 22
E 4
		}
I 5
D 6
		ronly++;
E 6
E 5
D 3
		fprintf(stderr,
		    "%s opened read-only, data may be inconsistent\n",
		    kmemf);
E 3
I 3
D 15
		fprintf(stderr, "%s opened read-only\n", kmemf);
E 15
I 15
D 22
		(void)fprintf(stderr, "%s opened read-only\n", kmemf);
E 22
I 22
D 26
		if (kd == NULL) {
			(void)fprintf(stderr, "kgmon: kvm_openfiles: %s\n",
			    errbuf);
			exit(2);
		}
		(void)fprintf(stderr, "kgmon: kernel opened read-only\n");
E 22
E 15
D 5
		if (!sflag)
			fprintf(stderr, "data may be inconsistent\n");
E 5
		if (rflag)
D 15
			fprintf(stderr, "-r supressed\n");
E 15
I 15
			(void)fprintf(stderr, "-r supressed\n");
E 15
D 25
		if (bflag)
D 15
			fprintf(stderr, "-b supressed\n");
E 15
I 15
			(void)fprintf(stderr, "-b supressed\n");
E 15
		if (hflag)
D 15
			fprintf(stderr, "-h supressed\n");
E 15
I 15
			(void)fprintf(stderr, "-h supressed\n");
E 15
D 13
		rflag = 0;
		bflag = 0;
		hflag = 0;
E 13
I 13
		rflag = bflag = hflag = 0;
E 25
I 25
		rflag = 0;
E 26
I 26
		return;
E 26
E 25
E 13
E 3
	}
D 3
	if (kflg) {
E 3
I 3
D 22
	if (kflag) {
I 21
#ifdef NEWVM
E 22
I 22
D 26
	if (kvm_nlist(kd, nl) < 0) {
		(void)fprintf(stderr, "kgmon: %s: no namelist\n", system);
		exit(2);
E 26
I 26
	(void)seteuid(0);
	mib[0] = CTL_KERN;
	mib[1] = KERN_PROF;
	mib[2] = GPROF_COUNT;
	if (sysctl(mib, 3, NULL, NULL, zbuf, kvp->gpm.kcountsize) < 0) {
		(void)fprintf(stderr, "kgmon: tickbuf zero: %s\n",
		    strerror(errno));
		exit(13);
E 26
	}
D 23
	if (!nl[N_PROFILING].n_value) {
E 23
I 23
D 26
	if (!nl[N_GMONPARAM].n_value) {
E 23
E 22
		(void)fprintf(stderr,
D 22
		    "kgmon: can't do core files yet\n");
		exit(1);
#else
E 21
E 3
		off_t off;

D 11
		off = nl[N_SYSMAP].n_value & 0x7fffffff;
		lseek(kmem, off, 0);
E 11
I 11
D 13
		off = clear(nl[N_SYSMAP].n_value);
		lseek(kmem, off, L_SET);
E 11
		nl[N_SYSSIZE].n_value *= 4;
		Sysmap = (struct pte *)malloc(nl[N_SYSSIZE].n_value);
		if (Sysmap == 0) {
			perror("Sysmap");
D 4
			exit(1);
E 4
I 4
			exit(4);
E 13
I 13
		Sysmap = (struct pte *)
		   malloc((u_int)(nl[N_SYSSIZE].n_value * sizeof(struct pte)));
		if (!Sysmap) {
D 15
			fputs("arp: can't get memory for Sysmap.\n", stderr);
E 15
I 15
			(void)fprintf(stderr,
			    "kgmon: can't get memory for Sysmap.\n");
E 15
			exit(1);
E 13
E 4
		}
D 13
		read(kmem, Sysmap, nl[N_SYSSIZE].n_value);
E 13
I 13
		off = nl[N_SYSMAP].n_value & ~KERNBASE;
		(void)lseek(kmem, off, L_SET);
		(void)read(kmem, (char *)Sysmap,
		    (int)(nl[N_SYSSIZE].n_value * sizeof(struct pte)));
I 21
#endif
E 22
I 22
		    "kgmon: profiling not defined in kernel.\n");
		exit(10);
E 26
I 26
	mib[2] = GPROF_FROMS;
	if (sysctl(mib, 3, NULL, NULL, zbuf, kvp->gpm.fromssize) < 0) {
		(void)fprintf(stderr, "kgmon: froms zero: %s\n",
		    strerror(errno));
		exit(14);
E 26
E 22
E 21
E 13
	}
I 5
D 23
	mode = kfetch(N_PROFILING);
E 23
I 23
D 26
	if (KREAD(kd, nl[N_GMONPARAM].n_value, &gmonparam))
		(void)fprintf(stderr,
		    "kgmon: read kmem: %s\n", kvm_geterr(kd));
D 24
	if (KREAD(kd, nl[N_KCOUNT].n_value, &kcount))
		(void)fprintf(stderr, "kgmon: read kmem: %s\n",
			      kvm_geterr(kd));
E 24
	if (KREAD(kd, nl[N_PROFHZ].n_value, &profhz))
		(void)fprintf(stderr, "kgmon: read kmem: %s\n",
			      kvm_geterr(kd));

	mode = gmonparam.state;
E 23
E 5
I 3
	if (hflag)
D 23
		disp = PROFILING_OFF;
E 23
I 23
		disp = GMON_PROF_OFF;
E 23
	else if (bflag)
D 23
		disp = PROFILING_ON;
E 23
I 23
		disp = GMON_PROF_ON;
E 23
	else
D 5
		disp = kfetch(N_PROFILING);
	if (!sflag)
E 5
I 5
		disp = mode;
D 6
	if (!sflag) {
		if (ronly && mode == PROFILING_ON)
E 6
I 6
	if (pflag) {
D 11
		if (openmode == 0 && mode == PROFILING_ON)
E 11
I 11
D 23
		if (openmode == O_RDONLY && mode == PROFILING_ON)
E 23
I 23
D 25
		if (openmode == O_RDONLY && mode == GMON_PROF_ON)
E 25
I 25
		if (kflag && openmode == O_RDONLY && mode == GMON_PROF_ON)
E 25
E 23
E 11
E 6
D 15
			fprintf(stderr, "data may be inconsistent\n");
E 15
I 15
			(void)fprintf(stderr, "data may be inconsistent\n");
E 15
E 5
D 23
		dumpstate();
E 23
I 23
		dumpstate(&gmonparam);
E 26
I 26
	mib[2] = GPROF_TOS;
	if (sysctl(mib, 3, NULL, NULL, zbuf, kvp->gpm.tossize) < 0) {
		(void)fprintf(stderr, "kgmon: tos zero: %s\n",
		    strerror(errno));
		exit(15);
E 26
E 23
I 5
	}
E 5
D 26
	if (rflag)
D 23
		resetstate();
E 23
I 23
		reset(&gmonparam);
E 23
D 22
	turnonoff(disp);
E 22
I 22
D 25
	if (openmode == O_RDWR)
E 25
I 25
	if (!kflag || openmode == O_RDWR)
E 25
D 23
		turnonoff(disp);
E 22
I 5
D 15
	fprintf(stdout, "kernel profiling is %s.\n", disp ? "off" : "running");
E 15
I 15
	(void)fprintf(stdout,
	    "kernel profiling is %s.\n", disp ? "off" : "running");
I 20
	exit(0);
E 20
E 15
E 5
}
E 23
I 23
		setprof(disp);
	(void)fprintf(stdout, "kernel profiling is %s.\n",
		      disp == GMON_PROF_OFF ? "off" : "running");
E 23

D 23
dumpstate()
{
I 15
D 22
	extern int errno;
E 22
E 15
D 13
	int i;
	int fd;
	off_t kfroms, ktos;
	int fromindex, endfrom, fromssize, tossize;
	u_long frompc;
	int toindex;
E 13
	struct rawarc rawarc;
D 13
	char buf[BUFSIZ];
E 13
I 13
	struct tostruct *tos;
	u_long frompc;
D 22
	off_t kfroms, ktos;
E 22
	u_short *froms;		/* froms is a bunch of u_shorts indexing tos */
D 22
	int i, fd, fromindex, endfrom, fromssize, tossize, toindex;
D 15
	char buf[BUFSIZ], *s_lowpc, *malloc();
E 15
I 15
	char buf[BUFSIZ], *s_lowpc, *malloc(), *strerror();
E 22
I 22
	int i, n, ret, fd;
	int fromindex, endfrom, toindex;
	u_int fromssize, tossize;
	u_long s_textsize;
	off_t sbuf;
	char *s_lowpc;
	char buf[MAXBSIZE];
E 22
E 15
E 13

E 3
	turnonoff(PROFILING_OFF);
D 22
	fd = creat("gmon.out", 0666);
E 22
I 22
	fd = open("gmon.out", O_WRONLY | O_CREAT, 0666);
E 22
	if (fd < 0) {
		perror("gmon.out");
		return;
	}
D 22
	ssiz = kfetch(N_SSIZ);
E 22
	sbuf = kfetch(N_SBUF);
D 11
	klseek(kmem, (off_t)sbuf, 0);
E 11
I 11
D 13
	klseek(kmem, (off_t)sbuf, L_SET);
E 13
I 13
D 22
	(void)klseek(kmem, (off_t)sbuf, L_SET);
E 13
E 11
	for (i = ssiz; i > 0; i -= BUFSIZ) {
		read(kmem, buf, i < BUFSIZ ? i : BUFSIZ);
		write(fd, buf, i < BUFSIZ ? i : BUFSIZ);
E 22
I 22
	for (i = kfetch(N_SSIZ); i != 0; i -= n, sbuf += n) {
		n = i < sizeof(buf) ? i : sizeof(buf);
		if ((ret = kvm_read(kd, sbuf, buf, n)) != n) {
			(void)fprintf(stderr,
			    "kgmon: read kmem: read %d, got %d: %s\n",
			    n, ret, kvm_geterr(kd));
			exit(4);
		}
		if ((ret = write(fd, buf, n)) != n) {
			(void)fprintf(stderr,
			    "kgmon: write gmon.out: wrote %d, got %d: %s\n",
			    n, ret, strerror(errno));
		}
E 22
	}
	s_textsize = kfetch(N_S_TEXTSIZE);
D 3
	froms = (u_short *)malloc(s_textsize);
E 3
I 3
	fromssize = s_textsize / HASHFRACTION;
D 13
	froms = (u_short *)malloc(fromssize);
E 13
I 13
D 22
	froms = (u_short *)malloc((u_int)fromssize);
E 13
E 3
	kfroms = kfetch(N_FROMS);
D 11
	klseek(kmem, kfroms, 0);
E 11
I 11
D 13
	klseek(kmem, kfroms, L_SET);
E 13
I 13
	(void)klseek(kmem, kfroms, L_SET);
E 13
E 11
D 3
	for (i = 0; i < s_textsize; i += BUFSIZ) {
		j = s_textsize - i;
		if (j > BUFSIZ)
			j = BUFSIZ;
		k = read(kmem, ((char *)(froms)) + i, j);
		if (j != k) {
			fprintf(stderr, "read tos: loc %d, request %d, got %d",
			    i, j, k);
			perror("");
			exit(5);
		}
E 3
I 3
	i = read(kmem, ((char *)(froms)), fromssize);
E 22
I 22
	froms = (u_short *)malloc(fromssize);
	i = kvm_read(kd, kfetch(N_FROMS), (char *)froms, fromssize);
E 22
	if (i != fromssize) {
D 15
		fprintf(stderr, "read froms: request %d, got %d", fromssize, i);
D 13
		perror("");
E 13
I 13
		perror((char *)NULL);
E 15
I 15
D 22
		(void)fprintf(stderr, "read kmem: request %d, got %d: %s",
E 22
I 22
		(void)fprintf(stderr, "kgmon: read kmem: read %u, got %d: %s",
E 22
		    fromssize, i, strerror(errno));
E 15
E 13
		exit(5);
E 3
	}
D 3
	tos = (struct tostruct *)malloc(s_textsize);
E 3
I 3
	tossize = (s_textsize * ARCDENSITY / 100) * sizeof(struct tostruct);
D 13
	tos = (struct tostruct *)malloc(tossize);
E 13
I 13
D 22
	tos = (struct tostruct *)malloc((u_int)tossize);
E 13
E 3
	ktos = kfetch(N_TOS);
D 11
	klseek(kmem, ktos, 0);
E 11
I 11
D 13
	klseek(kmem, ktos, L_SET);
E 13
I 13
	(void)klseek(kmem, ktos, L_SET);
E 13
E 11
D 3
	for (i = 0; i < s_textsize; i += BUFSIZ) {
		j = s_textsize - i;
		if (j > BUFSIZ)
			j = BUFSIZ;
		k = read(kmem, ((char *)(tos)) + i, j);
		if (j != k) {
			fprintf(stderr, "read tos: loc %d, request %d, got %d",
			    i, j, k);
			perror("");
			exit(6);
		}
E 3
I 3
	i = read(kmem, ((char *)(tos)), tossize);
E 22
I 22
	tos = (struct tostruct *)malloc(tossize);
	i = kvm_read(kd, kfetch(N_TOS), (char *)tos, tossize);
E 22
	if (i != tossize) {
D 15
		fprintf(stderr, "read tos: request %d, got %d", tossize, i);
D 13
		perror("");
E 13
I 13
		perror((char *)NULL);
E 15
I 15
D 22
		(void)fprintf(stderr, "read kmem: request %d, got %d: %s",
		    tossize, i, strerror(errno));
E 22
I 22
		(void)fprintf(stderr, "kgmon: read kmem: read %u, got %d: %s",
		    tossize, i, kvm_geterr(kd));
E 22
E 15
E 13
		exit(6);
E 3
	}
	s_lowpc = (char *)kfetch(N_S_LOWPC);
	if (debug)
D 15
		fprintf(stderr, "s_lowpc 0x%x, s_textsize 0x%x\n",
E 15
I 15
		(void)fprintf(stderr, "s_lowpc 0x%x, s_textsize 0x%x\n",
E 15
		    s_lowpc, s_textsize);
D 3
	for (fromindex = 0; fromindex < s_textsize>>1; fromindex++) {
E 3
I 3
	endfrom = fromssize / sizeof(*froms);
	for (fromindex = 0; fromindex < endfrom; fromindex++) {
E 3
		if (froms[fromindex] == 0)
			continue;
D 3
		frompc = (u_long)s_lowpc + (fromindex<<1);
E 3
I 3
		frompc = (u_long)s_lowpc +
		    (fromindex * HASHFRACTION * sizeof(*froms));
E 3
		for (toindex = froms[fromindex]; toindex != 0;
		   toindex = tos[toindex].link) {
			if (debug)
D 15
			    fprintf(stderr,
E 15
I 15
			    (void)fprintf(stderr,
E 15
			    "[mcleanup] frompc 0x%x selfpc 0x%x count %d\n" ,
			    frompc, tos[toindex].selfpc, tos[toindex].count);
			rawarc.raw_frompc = frompc;
			rawarc.raw_selfpc = (u_long)tos[toindex].selfpc;
			rawarc.raw_count = tos[toindex].count;
D 13
			write(fd, &rawarc, sizeof (rawarc));
E 13
I 13
			write(fd, (char *)&rawarc, sizeof (rawarc));
E 13
		}
	}
	close(fd);
D 3
	turnonoff(PROFILING_ON);
E 3
}

I 22
int
zeroit(addr, len, zbuf, zsize)
	off_t addr;
	int len;
	char *zbuf;
	int zsize;
{
	register int n;

	while (len > 0) {
		n = len < zsize ? len : zsize;
		if (kvm_write(kd, addr, zbuf, n) != n)
			return (-1);
		addr += n;
		len -= n;
	}
E 23
	return (0);
E 26
I 26
	(void)seteuid(getuid());
	free(zbuf);
E 26
D 23
}

E 22
I 3
resetstate()
{
D 13
	int i;
E 13
D 22
	off_t kfroms, ktos;
D 13
	int fromssize, tossize;
E 13
I 13
	int i, fromssize, tossize;
E 13
	char buf[BUFSIZ];
E 22
I 22
	off_t sbuf, ktos;
	int ssiz, fromssize, tossize;
	u_long s_textsize;
	char zbuf[MAXBSIZE];
E 22

	turnonoff(PROFILING_OFF);
D 22
	bzero(buf, BUFSIZ);
	ssiz = kfetch(N_SSIZ);
	sbuf = kfetch(N_SBUF);
	ssiz -= sizeof(struct phdr);
	sbuf += sizeof(struct phdr);
D 11
	klseek(kmem, (off_t)sbuf, 0);
E 11
I 11
D 13
	klseek(kmem, (off_t)sbuf, L_SET);
E 13
I 13
	(void)klseek(kmem, (off_t)sbuf, L_SET);
E 13
E 11
	for (i = ssiz; i > 0; i -= BUFSIZ)
		if (write(kmem, buf, i < BUFSIZ ? i : BUFSIZ) < 0) {
			perror("sbuf write");
D 4
			exit(1);
E 4
I 4
			exit(7);
E 4
		}
E 22
I 22
	bzero(zbuf, sizeof(zbuf));
	ssiz = kfetch(N_SSIZ) - sizeof(struct phdr);
	sbuf = kfetch(N_SBUF) + sizeof(struct phdr);
	if (zeroit(sbuf, ssiz, zbuf, sizeof(zbuf))) {
		(void)fprintf(stderr, "kgmon: sbuf write: %s\n",
		    kvm_geterr(kd));
		exit(7);
	}
E 22
	s_textsize = kfetch(N_S_TEXTSIZE);
	fromssize = s_textsize / HASHFRACTION;
D 22
	kfroms = kfetch(N_FROMS);
D 11
	klseek(kmem, kfroms, 0);
E 11
I 11
D 13
	klseek(kmem, kfroms, L_SET);
E 13
I 13
	(void)klseek(kmem, kfroms, L_SET);
E 13
E 11
	for (i = fromssize; i > 0; i -= BUFSIZ)
		if (write(kmem, buf, i < BUFSIZ ? i : BUFSIZ) < 0) {
			perror("kforms write");
D 4
			exit(1);
E 4
I 4
			exit(8);
E 4
		}
E 22
I 22
	if (zeroit((off_t)kfetch(N_FROMS), fromssize, zbuf, sizeof(zbuf))) {
		(void)fprintf(stderr, "kgmon: kfroms write: %s\n",
		    kvm_geterr(kd));
		exit(8);
	}
E 22
	tossize = (s_textsize * ARCDENSITY / 100) * sizeof(struct tostruct);
	ktos = kfetch(N_TOS);
D 11
	klseek(kmem, ktos, 0);
E 11
I 11
D 13
	klseek(kmem, ktos, L_SET);
E 13
I 13
D 22
	(void)klseek(kmem, ktos, L_SET);
E 13
E 11
	for (i = tossize; i > 0; i -= BUFSIZ)
		if (write(kmem, buf, i < BUFSIZ ? i : BUFSIZ) < 0) {
			perror("ktos write");
D 4
			exit(1);
E 4
I 4
			exit(9);
E 4
		}
E 22
I 22
	if (zeroit((off_t)kfetch(N_TOS), tossize, zbuf, sizeof(zbuf))) {
		(void)fprintf(stderr, "kgmon: ktos write: %s\n",
		    kvm_geterr(kd));
		exit(9);
	}
E 22
}

E 3
turnonoff(onoff)
	int onoff;
{
D 13
	off_t off;

	if ((off = nl[N_PROFILING].n_value) == 0) {
		printf("profiling: not defined in kernel\n");
D 4
		exit(1);
E 4
I 4
		exit(10);
E 4
	}
D 11
	klseek(kmem, off, 0);
E 11
I 11
	klseek(kmem, off, L_SET);
E 11
	write(kmem, (char *)&onoff, sizeof (onoff));
E 13
I 13
D 22
	(void)klseek(kmem, (long)nl[N_PROFILING].n_value, L_SET);
	(void)write(kmem, (char *)&onoff, sizeof (onoff));
E 22
I 22

	if (kvm_write(kd, (off_t)nl[N_PROFILING].n_value,
	    (char *)&onoff, sizeof(onoff)) != sizeof(onoff))
		(void)fprintf(stderr,
		    "kgmon: warning: can't turn profiling %s\n",
		    onoff ? "off" : "on");
E 22
E 13
}

kfetch(index)
	int index;
{
	off_t off;
	int value;

	if ((off = nl[index].n_value) == 0) {
D 22
		printf("%s: not defined in kernel\n", nl[index].n_name);
E 22
I 22
		(void)fprintf(stderr, "kgmon: %s: not defined in kernel\n",
		    nl[index].n_name);
E 22
D 4
		exit(1);
E 4
I 4
		exit(11);
E 4
	}
D 11
	if (klseek(kmem, off, 0) == -1) {
E 11
I 11
D 22
	if (klseek(kmem, off, L_SET) == -1) {
E 11
		perror("lseek");
D 4
		exit(2);
E 4
I 4
		exit(12);
E 4
	}
	if (read(kmem, (char *)&value, sizeof (value)) != sizeof (value)) {
		perror("read");
E 22
I 22
	if (kvm_read(kd, off, (char *)&value, sizeof(value)) != sizeof(value)) {
		(void)fprintf(stderr, "kgmon: kvm_read(%s): %s\n",
		    nl[index].n_name, kvm_geterr(kd));
E 22
D 4
		exit(3);
E 4
I 4
		exit(13);
E 4
	}
	return (value);
E 23
D 22
}

I 13
off_t
E 13
klseek(fd, base, off)
D 13
	int fd, base, off;
E 13
I 13
	int fd, off;
	off_t base;
E 13
{
I 21

#ifndef NEWVM
E 21
D 13

D 3
	if (kflg) {
E 3
I 3
	if (kflag) {
E 3
		/* get kernel pte */
I 7
D 11
#if vax
E 7
		base &= 0x7fffffff;
D 7
		base = Sysmap[base >> 9].pg_pfnum * 512 + (base & 0x1ff);
E 7
I 7
#endif
E 11
I 11
		base = clear(base);
E 11
		base = ((int)ptob(Sysmap[btop(base)].pg_pfnum))+(base&(NBPG-1));
E 13
I 13
	if (kflag) {	/* get kernel pte */
		base &= ~KERNBASE;
		base = ctob(Sysmap[btop(base)].pg_pfnum) + (base & PGOFSET);
E 13
E 7
	}
I 21
#endif
E 21
	return (lseek(fd, base, off));
E 22
}
E 1
