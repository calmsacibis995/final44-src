h16236
s 00023/00011/00692
d D 8.6 94/04/16 15:25:21 bostic 20 19
c run the environment and arguments through strvis, so we don't
c whack on the terminal
c From: "Chris G. Demetriou" <cgd@nobozo.CS.Berkeley.EDU>
e
s 00001/00001/00702
d D 8.5 94/04/02 10:01:18 pendry 19 18
c add 1994 copyright
e
s 00053/00060/00650
d D 8.4 94/04/02 09:58:39 pendry 18 17
c prettyness police
e
s 00026/00025/00684
d D 8.3 93/09/23 19:08:46 bostic 17 16
c changes for 4.4BSD-Lite requested by USL
e
s 00003/00003/00706
d D 8.2 93/09/22 16:05:44 bostic 16 15
c changes for 4.4BSD-Lite requested by USL
e
s 00002/00002/00707
d D 8.1 93/05/31 15:05:44 bostic 15 14
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00026/00020/00683
d D 5.14 93/04/29 13:18:43 bostic 14 13
c use err/warn to C library, cast size values to printf(3) to int
e
s 00007/00006/00696
d D 5.13 92/07/09 18:56:59 torek 13 12
c new process time
e
s 00001/00001/00701
d D 5.12 92/07/06 12:53:54 bostic 12 11
c page wait state no longer exists
e
s 00242/00126/00460
d D 5.11 92/06/05 18:56:54 bostic 11 10
c ANSI prototypes (two real bugs)
e
s 00073/00061/00513
d D 5.10 92/04/03 14:55:48 mckusick 10 9
c update from Steve McCanne for Sun compatible kvm
e
s 00004/00004/00570
d D 5.9 91/07/01 17:01:20 karels 9 8
c newvm changes for memory size
e
s 00002/00002/00572
d D 5.8 91/07/01 15:41:37 bostic 8 7
c writeable strings
e
s 00001/00001/00573
d D 5.7 91/06/03 16:55:40 bostic 7 6
c fix err routine, make everyone use it; minor ANSI cleanups
e
s 00007/00001/00567
d D 5.6 91/05/06 17:16:46 karels 6 5
c rm more stuff the newvm system doesn't have; left-adjust numeric wchans
e
s 00007/00005/00561
d D 5.5 91/03/27 15:49:45 marc 5 4
c its \not/ an error to specify a keyword twice
e
s 00065/00006/00501
d D 5.4 91/03/27 15:04:19 karels 4 3
c new vm
e
s 00002/00004/00505
d D 5.3 91/03/20 17:50:37 bostic 3 2
c do seconds scaling correctly
e
s 00007/00003/00502
d D 5.2 91/02/08 13:16:29 bostic 2 1
c SCCS replaces %[IM]%, free of charge
e
s 00505/00000/00000
d D 5.1 91/02/08 10:58:10 bostic 1 0
c Put print/keyword routines into separate modules; delete attime.c, use
c strftime(3) instead; put combination keywords into main keyword list,
c sort, delete aliases, and use bsearch(3); don't fail if nlist fails or
c devices aren't found.  Whack the manual page for consistency, correctness.
e
u
U
t
T
I 1
/*-
D 15
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 15
I 15
D 19
 * Copyright (c) 1990, 1993
E 19
I 19
 * Copyright (c) 1990, 1993, 1994
E 19
 *	The Regents of the University of California.  All rights reserved.
E 15
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

D 4
#include <machine/pte.h>

E 4
#include <sys/param.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/proc.h>
#include <sys/stat.h>
D 4
#include <sys/vmparam.h>
#include <sys/vm.h>
E 4
D 14
#include <math.h>
I 11
#include <nlist.h>
E 11
#include <tzfile.h>
I 11
#include <stdio.h>
E 11
#include <stddef.h>
#include <string.h>
#include "ps.h"
E 14

I 4
D 17
#ifdef SPPWAIT
E 17
I 17
#ifdef P_PPWAIT
E 17
#define NEWVM
#endif

#ifdef NEWVM
D 14
#include <vm/vm.h>
E 14
#include <sys/ucred.h>
D 14
#include <sys/kinfo_proc.h>
E 14
I 14
#include <sys/sysctl.h>
#include <vm/vm.h>
E 14
#else
#include <machine/pte.h>
#include <sys/vmparam.h>
#include <sys/vm.h>
#endif

I 14
#include <err.h>
#include <math.h>
#include <nlist.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 20
#include <vis.h>
E 20
#include <tzfile.h>

#include "ps.h"

E 14
I 11
D 18
static void printval __P((char*, struct var *));

E 18
void
E 11
E 4
printheader()
{
D 18
	register VAR *v;
I 5
	register struct varent *vent;
E 18
I 18
	VAR *v;
	struct varent *vent;
E 18
E 5

D 5
	for (v = vhead; v; v = v->next) {
E 5
I 5
	for (vent = vhead; vent; vent = vent->next) {
		v = vent->var;
E 5
		if (v->flag & LJUST) {
D 5
			if (v->next == NULL)	/* last one */
E 5
I 5
			if (vent->next == NULL)	/* last one */
E 5
D 11
				(void) printf("%s", v->header);
E 11
I 11
				(void)printf("%s", v->header);
E 11
			else
D 11
				(void) printf("%-*s", v->width, v->header);
E 11
I 11
				(void)printf("%-*s", v->width, v->header);
E 11
		} else
D 11
			(void) printf("%*s", v->width, v->header);
E 11
I 11
			(void)printf("%*s", v->width, v->header);
E 11
D 5
		if (v->next != NULL)
E 5
I 5
		if (vent->next != NULL)
E 5
D 11
			(void) putchar(' ');
E 11
I 11
			(void)putchar(' ');
E 11
	}
D 11
	(void) putchar('\n');
E 11
I 11
	(void)putchar('\n');
E 11
}

D 5
command(k, v)
E 5
I 5
D 11
command(k, v, next)
E 11
I 11
void
command(k, ve)
E 11
E 5
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
D 18
	extern int termwidth, totwidth;
E 18
I 11
	VAR *v;
I 20
	int left;
	char *cp, *vis_env, *vis_args;
E 20
E 11

I 20
	if ((vis_args = malloc(strlen(k->ki_args) * 4 + 1)) == NULL)
		err(1, NULL);
	strvis(vis_args, k->ki_args, VIS_TAB | VIS_NL | VIS_NOSLASH);
	if (k->ki_env) {
		if ((vis_env = malloc(strlen(k->ki_env) * 4 + 1)) == NULL)
			err(1, NULL);
		strvis(vis_env, k->ki_env, VIS_TAB | VIS_NL | VIS_NOSLASH);
	} else
		vis_env = NULL;

E 20
D 5
	if (v->next == NULL) {
E 5
I 5
D 11
	if (next == NULL) {
E 11
I 11
	v = ve->var;
	if (ve->next == NULL) {
E 11
E 5
		/* last field */
D 10
		if (termwidth == UNLIMITED)
E 10
I 10
		if (termwidth == UNLIMITED) {
D 20
			if (k->ki_env)
D 11
				(void) printf("%s ", k->ki_env);
E 10
			(void) printf("%s", k->ki_args);
E 11
I 11
				(void)printf("%s ", k->ki_env);
			(void)printf("%s", k->ki_args);
E 20
I 20
			if (vis_env)
				(void)printf("%s ", vis_env);
			(void)printf("%s", vis_args);
E 20
E 11
D 10
		else {
E 10
I 10
		} else {
E 10
D 18
			register int left = termwidth - (totwidth - v->width);
D 10
			register char *cp = k->ki_args;
E 10
I 10
			register char *cp;
E 18
I 18
D 20
			int left = termwidth - (totwidth - v->width);
			char *cp;
E 18
E 10

E 20
I 20
			left = termwidth - (totwidth - v->width);
E 20
			if (left < 1) /* already wrapped, just use std width */
				left = v->width;
I 10
D 20
			cp = k->ki_env;
			if (cp != 0) {
E 20
I 20
			if ((cp = vis_env) != NULL) {
E 20
				while (--left >= 0 && *cp)
D 11
					(void) putchar(*cp++);
E 11
I 11
					(void)putchar(*cp++);
E 11
				if (--left >= 0)
					putchar(' ');
			}
D 20
			cp = k->ki_args;
E 10
			while (--left >= 0 && *cp)
E 20
I 20
			for (cp = vis_args; --left >= 0 && *cp != '\0';)
E 20
D 11
				(void) putchar(*cp++);
E 11
I 11
				(void)putchar(*cp++);
E 11
		}
	} else
I 10
		/* XXX env? */
E 10
D 11
		(void) printf("%-*.*s", v->width, v->width, k->ki_args);
E 11
I 11
D 20
		(void)printf("%-*.*s", v->width, v->width, k->ki_args);
E 20
I 20
		(void)printf("%-*.*s", v->width, v->width, vis_args);
	free(vis_args);
	if (vis_env != NULL)
		free(vis_env);
E 20
E 11
D 10

E 10
}

D 11
ucomm(k, v)
E 11
I 11
void
ucomm(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
D 10
	(void) printf("%-*s", v->width, k->ki_p->p_comm);
E 10
I 10
D 11
	(void) printf("%-*s", v->width, KI_PROC(k)->p_comm);
E 11
I 11
	VAR *v;

	v = ve->var;
	(void)printf("%-*s", v->width, KI_PROC(k)->p_comm);
E 11
E 10
}

D 11
logname(k, v)
E 11
I 11
void
logname(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
I 4
#ifndef NEWVM
E 4
D 10
	(void) printf("%-*s", v->width, k->ki_p->p_logname);
E 10
I 10
D 11
	(void) printf("%-*s", v->width, KI_PROC(k)->p_logname);
E 11
I 11
	(void)printf("%-*s", v->width, KI_PROC(k)->p_logname);
E 11
E 10
I 4
D 17
#else /* NEWVM */
E 17
I 17
#else
E 17
D 10
	(void) printf("%-*s", v->width, k->ki_e->e_login);
E 10
I 10
D 11
	(void) printf("%-*s", v->width, KI_EPROC(k)->e_login);
E 11
I 11
	(void)printf("%-*s", v->width, KI_EPROC(k)->e_login);
E 11
E 10
D 17
#endif /* NEWVM */
E 17
I 17
#endif
E 17
E 4
}

D 11
state(k, v)
E 11
I 11
void
state(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
D 18
	register struct proc *p;
	register int flag;
	register char *cp;
E 18
I 18
	struct proc *p;
	int flag;
	char *cp;
E 18
	VAR *v;
E 11
	char buf[16];
D 11
	register char *cp = buf;
D 10
	register struct proc *p = k->ki_p;
E 10
I 10
	register struct proc *p = KI_PROC(k);
E 10
	register flag = p->p_flag;
E 11

I 11
	v = ve->var;
	p = KI_PROC(k);
	flag = p->p_flag;
	cp = buf;

E 11
	switch (p->p_stat) {

	case SSTOP:
		*cp = 'T';
		break;

	case SSLEEP:
D 17
		if (flag & SSINTR)	/* interuptable (long) */
E 17
I 17
		if (flag & P_SINTR)	/* interuptable (long) */
E 17
			*cp = p->p_slptime >= MAXSLP ? 'I' : 'S';
		else
D 12
			*cp = (flag & SPAGE) ? 'P' : 'D';
E 12
I 12
			*cp = 'D';
E 12
		break;

	case SRUN:
	case SIDL:
		*cp = 'R';
		break;

	case SZOMB:
		*cp = 'Z';
		break;

	default:
		*cp = '?';
	}
	cp++;
D 17
	if (flag & SLOAD) {
E 17
I 17
	if (flag & P_INMEM) {
E 17
I 4
#ifndef NEWVM
E 4
		if (p->p_rssize > p->p_maxrss)
			*cp++ = '>';
I 4
#endif
E 4
	} else
		*cp++ = 'W';
	if (p->p_nice < NZERO)
		*cp++ = '<';
	else if (p->p_nice > NZERO)
		*cp++ = 'N';
I 6
#ifndef NEWVM
E 6
	if (flag & SUANOM)
		*cp++ = 'A';
	else if (flag & SSEQL)
		*cp++ = 'S';
I 6
#endif
E 6
D 17
	if (flag & STRC)
E 17
I 17
	if (flag & P_TRACED)
E 17
		*cp++ = 'X';
D 4
	if (flag & SWEXIT)
E 4
I 4
D 17
	if (flag & SWEXIT && p->p_stat != SZOMB)
E 17
I 17
	if (flag & P_WEXIT && p->p_stat != SZOMB)
E 17
E 4
		*cp++ = 'E';
I 4
#ifdef NEWVM
D 17
	if (flag & SPPWAIT)
E 17
I 17
	if (flag & P_PPWAIT)
E 17
#else
E 4
	if (flag & SVFORK)
I 4
#endif
E 4
		*cp++ = 'V';
I 6
#ifdef NEWVM
D 17
	if (flag & (SSYS|SLOCK|SKEEP|SPHYSIO))
E 17
I 17
	if (flag & (P_SYSTEM | P_NOSWAP | P_PHYSIO))
E 17
#else
E 6
	if (flag & (SSYS|SLOCK|SULOCK|SKEEP|SPHYSIO))
I 6
#endif
E 6
		*cp++ = 'L';
D 10
	if (k->ki_e->e_flag & EPROC_SLEADER)
E 10
I 10
	if (KI_EPROC(k)->e_flag & EPROC_SLEADER)
E 10
		*cp++ = 's';
D 10
	if ((flag & SCTTY) && k->ki_e->e_pgid == k->ki_e->e_tpgid)
E 10
I 10
D 17
	if ((flag & SCTTY) && KI_EPROC(k)->e_pgid == KI_EPROC(k)->e_tpgid)
E 17
I 17
	if ((flag & P_CONTROLT) && KI_EPROC(k)->e_pgid == KI_EPROC(k)->e_tpgid)
E 17
E 10
		*cp++ = '+';
	*cp = '\0';
D 11
	(void) printf("%-*s", v->width, buf);
E 11
I 11
	(void)printf("%-*s", v->width, buf);
E 11
}

D 11
pri(k, v)
E 11
I 11
void
pri(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
D 10
	(void) printf("%*d", v->width, k->ki_p->p_pri - PZERO);
E 10
I 10
D 11
	(void) printf("%*d", v->width, KI_PROC(k)->p_pri - PZERO);
E 11
I 11
	VAR *v;

	v = ve->var;
D 16
	(void)printf("%*d", v->width, KI_PROC(k)->p_pri - PZERO);
E 16
I 16
	(void)printf("%*d", v->width, KI_PROC(k)->p_priority - PZERO);
E 16
E 11
E 10
}

D 11
uname(k, v)
E 11
I 11
void
uname(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
I 4
#ifndef NEWVM
E 4
D 10
	(void) printf("%-*s", v->width, user_from_uid(k->ki_p->p_uid, 0));
E 10
I 10
D 11
	(void) printf("%-*s", v->width, user_from_uid(KI_PROC(k)->p_uid, 0));
E 11
I 11
D 14
	(void)printf("%-*s", v->width, user_from_uid(KI_PROC(k)->p_uid, 0));
E 11
E 10
I 4
#else /* NEWVM */
D 11
	(void) printf("%-*s", v->width,
E 11
I 11
	(void)printf("%-*s", v->width,
E 11
D 10
		user_from_uid(k->ki_e->e_ucred.cr_uid, 0));
E 10
I 10
		user_from_uid(KI_EPROC(k)->e_ucred.cr_uid, 0));
E 10
#endif /* NEWVM */
E 14
I 14
	(void)printf("%-*s",
	    (int)v->width, user_from_uid(KI_PROC(k)->p_uid, 0));
#else
	(void)printf("%-*s",
	    (int)v->width, user_from_uid(KI_EPROC(k)->e_ucred.cr_uid, 0));
#endif
E 14
E 4
}

D 11
runame(k, v)
E 11
I 11
void
runame(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
I 4
#ifndef NEWVM
E 4
D 10
	(void) printf("%-*s", v->width, user_from_uid(k->ki_p->p_ruid, 0));
E 10
I 10
D 11
	(void) printf("%-*s", v->width, user_from_uid(KI_PROC(k)->p_ruid, 0));
E 11
I 11
D 14
	(void)printf("%-*s", v->width, user_from_uid(KI_PROC(k)->p_ruid, 0));
E 11
E 10
I 4
#else /* NEWVM */
D 11
	(void) printf("%-*s", v->width,
E 11
I 11
	(void)printf("%-*s", v->width,
E 11
D 10
		user_from_uid(k->ki_e->e_pcred.p_ruid, 0));
E 10
I 10
		user_from_uid(KI_EPROC(k)->e_pcred.p_ruid, 0));
E 10
#endif /* NEWVM */
E 14
I 14
	(void)printf("%-*s",
	    (int)v->width, user_from_uid(KI_PROC(k)->p_ruid, 0));
#else
	(void)printf("%-*s",
	    (int)v->width, user_from_uid(KI_EPROC(k)->e_pcred.p_ruid, 0));
#endif
E 14
E 4
}

D 11
tdev(k, v)
E 11
I 11
void
tdev(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
D 10
	dev_t dev = k->ki_e->e_tdev;
E 10
I 10
D 11
	dev_t dev = KI_EPROC(k)->e_tdev;
E 11
I 11
	VAR *v;
	dev_t dev;
	char buff[16];
E 11
E 10

I 11
	v = ve->var;
	dev = KI_EPROC(k)->e_tdev;
E 11
	if (dev == NODEV)
D 11
		(void) printf("%*s", v->width, "??");
E 11
I 11
		(void)printf("%*s", v->width, "??");
E 11
	else {
D 11
		char buff[16];

		(void) sprintf(buff, "%d/%d", major(dev), minor(dev));
		(void) printf("%*s", v->width, buff);
E 11
I 11
		(void)snprintf(buff, sizeof(buff),
		    "%d/%d", major(dev), minor(dev));
		(void)printf("%*s", v->width, buff);
E 11
	}
}

D 11
tname(k, v)
E 11
I 11
void
tname(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;
E 11
	dev_t dev;
D 11
	char *ttname, *devname();
E 11
I 11
	char *ttname;
E 11

I 11
	v = ve->var;
E 11
D 10
	dev = k->ki_e->e_tdev;
E 10
I 10
	dev = KI_EPROC(k)->e_tdev;
E 10
	if (dev == NODEV || (ttname = devname(dev, S_IFCHR)) == NULL)
D 11
		(void) printf("%-*s", v->width, "??");
E 11
I 11
		(void)printf("%-*s", v->width, "??");
E 11
	else {
		if (strncmp(ttname, "tty", 3) == 0)
			ttname += 3;
D 11
		(void) printf("%*.*s%c", v->width-1, v->width-1, ttname,
E 11
I 11
		(void)printf("%*.*s%c", v->width-1, v->width-1, ttname,
E 11
D 10
			k->ki_e->e_flag & EPROC_CTTY ? ' ' : '-');
E 10
I 10
			KI_EPROC(k)->e_flag & EPROC_CTTY ? ' ' : '-');
E 10
	}
}

D 11
longtname(k, v)
E 11
I 11
void
longtname(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;
E 11
	dev_t dev;
D 11
	char *ttname, *devname();
E 11
I 11
	char *ttname;
E 11

I 11
	v = ve->var;
D 13

E 13
E 11
D 10
	dev = k->ki_e->e_tdev;
E 10
I 10
	dev = KI_EPROC(k)->e_tdev;
E 10
	if (dev == NODEV || (ttname = devname(dev, S_IFCHR)) == NULL)
D 11
		(void) printf("%-*s", v->width, "??");
E 11
I 11
		(void)printf("%-*s", v->width, "??");
E 11
	else
D 11
		(void) printf("%-*s", v->width, ttname);
E 11
I 11
		(void)printf("%-*s", v->width, ttname);
E 11
}

D 11
started(k, v)
E 11
I 11
void
started(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;
E 11
	static time_t now;
	struct tm *tp;
	char buf[100];

I 11
	v = ve->var;
E 11
D 10
	if (!k->ki_u) {
E 10
I 10
	if (!k->ki_u.u_valid) {
E 10
D 11
		(void) printf("%-*s", v->width, "-");
E 11
I 11
		(void)printf("%-*s", v->width, "-");
E 11
		return;
	}

D 10
	tp = localtime(&k->ki_u->u_start.tv_sec);
E 10
I 10
	tp = localtime(&k->ki_u.u_start.tv_sec);
E 10
	if (!now)
		(void)time(&now);
D 2
	if (now - k->ki_u->u_start.tv_sec < 24 * SECSPERHOUR)
		(void) strftime(buf, sizeof(buf) - 1, "%l:%M%p", tp);
E 2
I 2
D 10
	if (now - k->ki_u->u_start.tv_sec < 24 * SECSPERHOUR) {
E 10
I 10
	if (now - k->ki_u.u_start.tv_sec < 24 * SECSPERHOUR) {
E 10
D 8
		static char *fmt = "%l:@M%p";
E 8
I 8
D 18
		static char fmt[] = "%l:@M%p";
E 8
		fmt[3] = '%';			/* I *hate* SCCS... */
E 18
I 18
		/* I *hate* SCCS... */
		static char fmt[] = __CONCAT("%l:%", "M%p");
E 18
D 11
		(void) strftime(buf, sizeof(buf) - 1, fmt, tp);
E 11
I 11
		(void)strftime(buf, sizeof(buf) - 1, fmt, tp);
E 11
E 2
D 2
	else if (now - k->ki_u->u_start.tv_sec < 7 * SECSPERDAY)
		(void) strftime(buf, sizeof(buf) - 1, "%a%I%p", tp);
E 2
I 2
D 10
	} else if (now - k->ki_u->u_start.tv_sec < 7 * SECSPERDAY) {
E 10
I 10
	} else if (now - k->ki_u.u_start.tv_sec < 7 * SECSPERDAY) {
E 10
D 8
		static char *fmt = "%a@I%p";
E 8
I 8
D 18
		static char fmt[] = "%a@I%p";
E 8
		fmt[2] = '%';			/* I *hate* SCCS... */
E 18
I 18
		/* I *hate* SCCS... */
		static char fmt[] = __CONCAT("%a%", "I%p");
E 18
D 11
		(void) strftime(buf, sizeof(buf) - 1, fmt, tp);
E 11
I 11
		(void)strftime(buf, sizeof(buf) - 1, fmt, tp);
E 11
E 2
D 2
	else
E 2
I 2
	} else
E 2
D 11
		(void) strftime(buf, sizeof(buf) - 1, "%e%b%y", tp);
	(void) printf("%-*s", v->width, buf);
E 11
I 11
		(void)strftime(buf, sizeof(buf) - 1, "%e%b%y", tp);
	(void)printf("%-*s", v->width, buf);
E 11
}

D 11
lstarted(k, v)
E 11
I 11
void
lstarted(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;
E 11
	char buf[100];

I 11
	v = ve->var;
D 13

E 13
E 11
D 10
	if (!k->ki_u) {
E 10
I 10
	if (!k->ki_u.u_valid) {
E 10
D 11
		(void) printf("%-*s", v->width, "-");
E 11
I 11
		(void)printf("%-*s", v->width, "-");
E 11
		return;
	}
D 11
	(void) strftime(buf, sizeof(buf) -1, "%C",
E 11
I 11
	(void)strftime(buf, sizeof(buf) -1, "%C",
E 11
D 10
	    localtime(&k->ki_u->u_start.tv_sec));
E 10
I 10
	    localtime(&k->ki_u.u_start.tv_sec));
E 10
D 11
	(void) printf("%-*s", v->width, buf);
E 11
I 11
	(void)printf("%-*s", v->width, buf);
E 11
}

D 11
wchan(k, v)
E 11
I 11
void
wchan(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
D 10
	if (k->ki_p->p_wchan) {
D 4
		if (k->ki_p->p_pri > PZERO)
E 4
I 4
		if (k->ki_p->p_wmesg)
E 4
			(void) printf("%-*.*s", v->width, v->width, k->ki_e->e_wmesg);
E 10
I 10
	if (KI_PROC(k)->p_wchan) {
		if (KI_PROC(k)->p_wmesg)
D 11
			(void) printf("%-*.*s", v->width, v->width, 
E 11
I 11
			(void)printf("%-*.*s", v->width, v->width, 
E 11
				      KI_EPROC(k)->e_wmesg);
E 10
		else
D 6
			(void) printf("%*x", v->width,
E 6
I 6
D 11
			(void) printf("%-*x", v->width,
E 11
I 11
			(void)printf("%-*x", v->width,
E 11
E 6
D 10
			    (int)k->ki_p->p_wchan &~ KERNBASE);
E 10
I 10
			    (int)KI_PROC(k)->p_wchan &~ KERNBASE);
E 10
	} else
D 11
		(void) printf("%-*s", v->width, "-");
E 11
I 11
		(void)printf("%-*s", v->width, "-");
E 11
}

#define pgtok(a)        (((a)*NBPG)/1024)

D 11
vsize(k, v)
E 11
I 11
void
vsize(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
D 11
	(void) printf("%*d", v->width,
E 11
I 11
	VAR *v;

	v = ve->var;
	(void)printf("%*d", v->width,
E 11
I 4
#ifndef NEWVM
E 4
D 10
	    pgtok(k->ki_p->p_dsize + k->ki_p->p_ssize + k->ki_e->e_xsize));
E 10
I 10
D 17
	    pgtok(KI_PROC(k)->p_dsize + KI_PROC(k)->p_ssize + KI_EPROC(k)->e_xsize));
E 10
I 4
#else /* NEWVM */
E 17
I 17
	    pgtok(KI_PROC(k)->p_dsize +
	        KI_PROC(k)->p_ssize + KI_EPROC(k)->e_xsize));
#else
E 17
D 10
	    pgtok(k->ki_e->e_vm.vm_dsize + k->ki_e->e_vm.vm_ssize +
		k->ki_e->e_vm.vm_tsize));
E 10
I 10
	    pgtok(KI_EPROC(k)->e_vm.vm_dsize + KI_EPROC(k)->e_vm.vm_ssize +
		KI_EPROC(k)->e_vm.vm_tsize));
E 10
D 17
#endif /* NEWVM */
E 17
I 17
#endif
E 17
E 4
}

D 11
rssize(k, v)
E 11
I 11
void
rssize(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
I 4
#ifndef NEWVM
E 4
D 11
	(void) printf("%*d", v->width,
E 11
I 11
	(void)printf("%*d", v->width,
E 11
D 10
	    pgtok(k->ki_p->p_rssize + (k->ki_e->e_xccount ?
	    (k->ki_e->e_xrssize / k->ki_e->e_xccount) : 0)));
E 10
I 10
	    pgtok(KI_PROC(k)->p_rssize + (KI_EPROC(k)->e_xccount ?
	    (KI_EPROC(k)->e_xrssize / KI_EPROC(k)->e_xccount) : 0)));
E 10
I 4
D 17
#else /* NEWVM */
E 17
I 17
#else
E 17
	/* XXX don't have info about shared */
D 10
	(void) printf("%*d", v->width, pgtok(k->ki_e->e_vm.vm_rssize));
E 10
I 10
D 11
	(void) printf("%*d", v->width, pgtok(KI_EPROC(k)->e_vm.vm_rssize));
E 11
I 11
	(void)printf("%*d", v->width, pgtok(KI_EPROC(k)->e_vm.vm_rssize));
E 11
E 10
D 17
#endif /* NEWVM */
E 17
I 17
#endif
E 17
E 4
}

D 11
p_rssize(k, v)		/* doesn't account for text */
E 11
I 11
void
p_rssize(k, ve)		/* doesn't account for text */
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
I 4
#ifndef NEWVM
E 4
D 10
	(void) printf("%*d", v->width, pgtok(k->ki_p->p_rssize));
E 10
I 10
D 11
	(void) printf("%*d", v->width, pgtok(KI_PROC(k)->p_rssize));
E 11
I 11
	(void)printf("%*d", v->width, pgtok(KI_PROC(k)->p_rssize));
E 11
E 10
I 4
D 17
#else /* NEWVM */
E 17
I 17
#else
E 17
D 10
	(void) printf("%*d", v->width, pgtok(k->ki_e->e_vm.vm_rssize));
E 10
I 10
D 11
	(void) printf("%*d", v->width, pgtok(KI_EPROC(k)->e_vm.vm_rssize));
E 11
I 11
	(void)printf("%*d", v->width, pgtok(KI_EPROC(k)->e_vm.vm_rssize));
E 11
E 10
D 17
#endif /* NEWVM */
E 17
I 17
#endif
E 17
E 4
}

D 11
cputime(k, v)
E 11
I 11
void
cputime(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
D 18
	extern int sumrusage;
E 18
I 11
	VAR *v;
E 11
	long secs;
	long psecs;	/* "parts" of a second. first micro, then centi */
	char obuff[128];

I 11
	v = ve->var;
E 11
D 10
	if (k->ki_p->p_stat == SZOMB || k->ki_u == NULL) {
E 10
I 10
	if (KI_PROC(k)->p_stat == SZOMB || !k->ki_u.u_valid) {
E 10
		secs = 0;
		psecs = 0;
	} else {
D 10
		secs = k->ki_p->p_utime.tv_sec +
			k->ki_p->p_stime.tv_sec;
		psecs = k->ki_p->p_utime.tv_usec +
			k->ki_p->p_stime.tv_usec;
E 10
I 10
D 13
		secs = KI_PROC(k)->p_utime.tv_sec +
			KI_PROC(k)->p_stime.tv_sec;
		psecs = KI_PROC(k)->p_utime.tv_usec +
			KI_PROC(k)->p_stime.tv_usec;
E 13
I 13
		/*
		 * This counts time spent handling interrupts.  We could
		 * fix this, but it is not 100% trivial (and interrupt
		 * time fractions only work on the sparc anyway).	XXX
		 */
		secs = KI_PROC(k)->p_rtime.tv_sec;
		psecs = KI_PROC(k)->p_rtime.tv_usec;
E 13
E 10
		if (sumrusage) {
D 10
			secs += k->ki_u->u_cru.ru_utime.tv_sec +
				k->ki_u->u_cru.ru_stime.tv_sec;
			psecs += k->ki_u->u_cru.ru_utime.tv_usec +
				k->ki_u->u_cru.ru_stime.tv_usec;
E 10
I 10
			secs += k->ki_u.u_cru.ru_utime.tv_sec +
				k->ki_u.u_cru.ru_stime.tv_sec;
			psecs += k->ki_u.u_cru.ru_utime.tv_usec +
				k->ki_u.u_cru.ru_stime.tv_usec;
E 10
		}
		/*
		 * round and scale to 100's
		 */
		psecs = (psecs + 5000) / 10000;
D 3
		if (psecs >= 100) {
			psecs -= 100;
			secs++;
		}
E 3
I 3
		secs += psecs / 100;
		psecs = psecs % 100;
E 3
	}
D 11
	(void) sprintf(obuff, "%3ld:%02ld.%02ld", secs/60, secs%60, psecs);
	(void) printf("%*s", v->width, obuff);
E 11
I 11
	(void)snprintf(obuff, sizeof(obuff),
	    "%3ld:%02ld.%02ld", secs/60, secs%60, psecs);
	(void)printf("%*s", v->width, obuff);
E 11
}

double
getpcpu(k)
	KINFO *k;
{
D 18
	extern fixpt_t ccpu;
	extern int fscale, nlistread, rawcpu;
E 18
	struct proc *p;
	static int failure;

	if (!nlistread)
		failure = donlist();
	if (failure)
		return (0.0);

D 10
	p = k->ki_p;
E 10
I 10
	p = KI_PROC(k);
E 10
#define	fxtofl(fixpt)	((double)(fixpt) / fscale)

	/* XXX - I don't like this */
D 16
	if (p->p_time == 0 || (p->p_flag & SLOAD) == 0)
E 16
I 16
D 17
	if (p->p_swtime == 0 || (p->p_flag & SLOAD) == 0)
E 17
I 17
	if (p->p_swtime == 0 || (p->p_flag & P_INMEM) == 0)
E 17
E 16
		return (0.0);
	if (rawcpu)
		return (100.0 * fxtofl(p->p_pctcpu));
	return (100.0 * fxtofl(p->p_pctcpu) /
D 16
		(1.0 - exp(p->p_time * log(fxtofl(ccpu)))));
E 16
I 16
		(1.0 - exp(p->p_swtime * log(fxtofl(ccpu)))));
E 16
}

D 11
pcpu(k, v)
E 11
I 11
void
pcpu(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
D 11
	(void) printf("%*.1f", v->width, getpcpu(k));
E 11
I 11
	VAR *v;

	v = ve->var;
	(void)printf("%*.1f", v->width, getpcpu(k));
E 11
}

double
getpmem(k)
	KINFO *k;
{
D 9
	extern int ecmx, nlistread;
E 9
I 9
D 18
	extern int mempages, nlistread;
E 18
E 9
	static int failure;
	struct proc *p;
	struct eproc *e;
	double fracmem;
	int szptudot;

	if (!nlistread)
		failure = donlist();
	if (failure)
		return (0.0);

D 10
	p = k->ki_p;
	e = k->ki_e;
E 10
I 10
	p = KI_PROC(k);
	e = KI_EPROC(k);
E 10
D 17
	if ((p->p_flag & SLOAD) == 0)
E 17
I 17
	if ((p->p_flag & P_INMEM) == 0)
E 17
		return (0.0);
I 4
#ifndef NEWVM
E 4
	szptudot = UPAGES + clrnd(ctopt(p->p_dsize + p->p_ssize + e->e_xsize));
D 9
	fracmem = ((float)p->p_rssize + szptudot)/CLSIZE/ecmx;
E 9
I 9
	fracmem = ((float)p->p_rssize + szptudot)/CLSIZE/mempages;
E 9
	if (p->p_textp && e->e_xccount)
D 9
		fracmem += ((float)e->e_xrssize)/CLSIZE/e->e_xccount/ecmx;
E 9
I 9
		fracmem += ((float)e->e_xrssize)/CLSIZE/e->e_xccount/mempages;
E 9
I 4
D 17
#else /* NEWVM */
E 17
I 17
#else
E 17
	/* XXX want pmap ptpages, segtab, etc. (per architecture) */
	szptudot = UPAGES;
	/* XXX don't have info about shared */
D 9
	fracmem = ((float)e->e_vm.vm_rssize + szptudot)/CLSIZE/ecmx;
E 9
I 9
	fracmem = ((float)e->e_vm.vm_rssize + szptudot)/CLSIZE/mempages;
E 9
D 17
#endif /* NEWVM */
E 17
I 17
#endif
E 17
E 4
	return (100.0 * fracmem);
}

D 11
pmem(k, v)
E 11
I 11
void
pmem(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
D 11
	(void) printf("%*.1f", v->width, getpmem(k));
E 11
I 11
	VAR *v;

	v = ve->var;
	(void)printf("%*.1f", v->width, getpmem(k));
E 11
}

D 11
pagein(k, v)
E 11
I 11
void
pagein(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
D 10
	(void) printf("%*d", v->width, k->ki_u ? k->ki_u->u_ru.ru_majflt : 0);
E 10
I 10
D 11
	(void) printf("%*d", v->width, 
		      k->ki_u.u_valid ? k->ki_u.u_ru.ru_majflt : 0);
E 11
I 11
	VAR *v;

	v = ve->var;
	(void)printf("%*d", v->width, 
	    k->ki_u.u_valid ? k->ki_u.u_ru.ru_majflt : 0);
E 11
E 10
}

D 11
maxrss(k, v)
E 11
I 11
void
maxrss(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
I 4
#ifndef NEWVM	/* not yet */
E 4
D 10
	if (k->ki_p->p_maxrss != (RLIM_INFINITY/NBPG))
		(void) printf("%*d", v->width, pgtok(k->ki_p->p_maxrss));
E 10
I 10
	if (KI_PROC(k)->p_maxrss != (RLIM_INFINITY/NBPG))
D 11
		(void) printf("%*d", v->width, pgtok(KI_PROC(k)->p_maxrss));
E 11
I 11
		(void)printf("%*d", v->width, pgtok(KI_PROC(k)->p_maxrss));
E 11
E 10
	else
I 4
D 17
#endif /* NEWVM */
E 17
I 17
#endif
E 17
E 4
D 11
		(void) printf("%*s", v->width, "-");
E 11
I 11
		(void)printf("%*s", v->width, "-");
E 11
}

D 11
tsize(k, v)
E 11
I 11
void
tsize(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
I 4
#ifndef NEWVM
E 4
D 10
	(void) printf("%*d", v->width, pgtok(k->ki_e->e_xsize));
E 10
I 10
D 11
	(void) printf("%*d", v->width, pgtok(KI_EPROC(k)->e_xsize));
E 11
I 11
	(void)printf("%*d", v->width, pgtok(KI_EPROC(k)->e_xsize));
E 11
E 10
I 4
D 17
#else /* NEWVM */
E 17
I 17
#else
E 17
D 10
	(void) printf("%*d", v->width, pgtok(k->ki_e->e_vm.vm_tsize));
E 10
I 10
D 11
	(void) printf("%*d", v->width, pgtok(KI_EPROC(k)->e_vm.vm_tsize));
E 11
I 11
	(void)printf("%*d", v->width, pgtok(KI_EPROC(k)->e_vm.vm_tsize));
E 11
E 10
D 17
#endif /* NEWVM */
E 17
I 17
#endif
E 17
E 4
}

I 4
#ifndef NEWVM
E 4
D 11
trss(k, v)
E 11
I 11
void
trss(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
D 10
	(void) printf("%*d", v->width, pgtok(k->ki_e->e_xrssize));
E 10
I 10
D 11
	(void) printf("%*d", v->width, pgtok(KI_EPROC(k)->e_xrssize));
E 11
I 11
	VAR *v;

	v = ve->var;
	(void)printf("%*d", v->width, pgtok(KI_EPROC(k)->e_xrssize));
E 11
E 10
}
I 4
D 17
#endif /* NEWVM */
E 17
I 17
#endif
E 17
E 4

/*
 * Generic output routines.  Print fields from various prototype
 * structures.
 */
I 18
static void
printval(bp, v)
	char *bp;
	VAR *v;
{
	static char ofmt[32] = "%";
	char *fcp, *cp;

	cp = ofmt + 1;
	fcp = v->fmt;
	if (v->flag & LJUST)
		*cp++ = '-';
	*cp++ = '*';
	while (*cp++ = *fcp++);

	switch (v->type) {
	case CHAR:
		(void)printf(ofmt, v->width, *(char *)bp);
		break;
	case UCHAR:
		(void)printf(ofmt, v->width, *(u_char *)bp);
		break;
	case SHORT:
		(void)printf(ofmt, v->width, *(short *)bp);
		break;
	case USHORT:
		(void)printf(ofmt, v->width, *(u_short *)bp);
		break;
	case LONG:
		(void)printf(ofmt, v->width, *(long *)bp);
		break;
	case ULONG:
		(void)printf(ofmt, v->width, *(u_long *)bp);
		break;
	case KPTR:
		(void)printf(ofmt, v->width, *(u_long *)bp &~ KERNBASE);
		break;
	default:
		errx(1, "unknown type %d", v->type);
	}
}

E 18
D 11
pvar(k, v)
E 11
I 11
void
pvar(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
D 10
	printval((char *)((char *)k->ki_p + v->off), v);
E 10
I 10
	printval((char *)((char *)KI_PROC(k) + v->off), v);
E 10
}

D 11
evar(k, v)
E 11
I 11
void
evar(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
D 10
	printval((char *)((char *)k->ki_e + v->off), v);
E 10
I 10
	printval((char *)((char *)KI_EPROC(k) + v->off), v);
E 10
}

D 11
uvar(k, v)
E 11
I 11
void
uvar(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
D 10
	if (k->ki_u)
		printval((char *)((char *)k->ki_u + v->off), v);
E 10
I 10
	if (k->ki_u.u_valid)
		printval((char *)((char *)&k->ki_u + v->off), v);
E 10
	else
D 11
		(void) printf("%*s", v->width, "-");
E 11
I 11
		(void)printf("%*s", v->width, "-");
E 11
}

D 11
rvar(k, v)
E 11
I 11
void
rvar(k, ve)
E 11
	KINFO *k;
D 11
	VAR *v;
E 11
I 11
	VARENT *ve;
E 11
{
I 11
	VAR *v;

	v = ve->var;
E 11
D 10
	if (k->ki_u)
		printval((char *)((char *)(&k->ki_u->u_ru) + v->off), v);
E 10
I 10
	if (k->ki_u.u_valid)
		printval((char *)((char *)(&k->ki_u.u_ru) + v->off), v);
E 10
	else
D 11
		(void) printf("%*s", v->width, "-");
E 11
I 11
		(void)printf("%*s", v->width, "-");
E 11
D 18
}

I 11
static void
E 11
printval(bp, v)
	char *bp;
	VAR *v;
{
	static char ofmt[32] = "%";
D 11
	register char *cp = ofmt+1, *fcp = v->fmt;
E 11
I 11
	register char *fcp, *cp;
E 11

I 11
	cp = ofmt + 1;
	fcp = v->fmt;
E 11
	if (v->flag & LJUST)
		*cp++ = '-';
	*cp++ = '*';
	while (*cp++ = *fcp++);

	switch (v->type) {
	case CHAR:
D 11
		(void) printf(ofmt, v->width, *(char *)bp);
E 11
I 11
		(void)printf(ofmt, v->width, *(char *)bp);
E 11
		break;
	case UCHAR:
D 11
		(void) printf(ofmt, v->width, *(u_char *)bp);
E 11
I 11
		(void)printf(ofmt, v->width, *(u_char *)bp);
E 11
		break;
	case SHORT:
D 11
		(void) printf(ofmt, v->width, *(short *)bp);
E 11
I 11
		(void)printf(ofmt, v->width, *(short *)bp);
E 11
		break;
	case USHORT:
D 11
		(void) printf(ofmt, v->width, *(u_short *)bp);
E 11
I 11
		(void)printf(ofmt, v->width, *(u_short *)bp);
E 11
		break;
	case LONG:
D 11
		(void) printf(ofmt, v->width, *(long *)bp);
E 11
I 11
		(void)printf(ofmt, v->width, *(long *)bp);
E 11
		break;
	case ULONG:
D 11
		(void) printf(ofmt, v->width, *(u_long *)bp);
E 11
I 11
		(void)printf(ofmt, v->width, *(u_long *)bp);
E 11
		break;
	case KPTR:
D 11
		(void) printf(ofmt, v->width, *(u_long *)bp &~ KERNBASE);
E 11
I 11
		(void)printf(ofmt, v->width, *(u_long *)bp &~ KERNBASE);
E 11
		break;
	default:
D 7
		error("unknown type %d", v->type);
E 7
I 7
D 14
		err("unknown type %d", v->type);
E 14
I 14
		errx(1, "unknown type %d", v->type);
E 14
E 7
	}
E 18
}
E 1
