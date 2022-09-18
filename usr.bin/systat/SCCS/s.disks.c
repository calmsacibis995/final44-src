h27776
s 00002/00002/00171
d D 8.1 93/06/06 16:28:49 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00000/00169
d D 5.17 93/05/28 22:08:40 ralph 20 19
c add support for mips
e
s 00001/00001/00168
d D 5.16 93/05/21 15:34:14 mckusick 19 18
c update header to reflect redistributable status
e
s 00001/00001/00168
d D 5.15 92/09/02 11:57:01 bostic 18 17
c add luna68k
e
s 00004/00004/00165
d D 5.14 92/09/02 11:56:29 bostic 17 16
c nl is an exported curses function
e
s 00012/00133/00157
d D 5.13 92/07/24 12:40:07 bostic 16 15
c use vmstat's version of names.c
e
s 00006/00005/00284
d D 5.12 92/07/23 17:57:34 bostic 15 14
c update copyright/header notice
e
s 00034/00005/00255
d D 5.11 92/07/23 17:50:35 bostic 14 13
c Elan's new kvm lib version; kvm and lint stuff
e
s 00004/00005/00256
d D 5.10 91/06/26 13:50:26 marc 13 12
c changes for new kernel, plus use kvm
e
s 00004/00000/00257
d D 5.9 91/06/04 16:52:18 marc 12 11
c add stub for hp300
e
s 00002/00002/00255
d D 5.8 91/04/11 11:23:05 sklower 11 10
c kernel reorg for vax
e
s 00001/00001/00256
d D 5.7 91/02/04 23:19:00 torek 10 9
c fix gcc-detected lint
e
s 00001/00001/00256
d D 5.6 91/01/14 17:59:12 bostic 9 8
c kernel reorg
e
s 00015/00008/00242
d D 5.5 89/05/29 16:48:28 mckusick 8 7
c eliminate floating point from the kernel (from forys@cs.utah.edu)
e
s 00016/00016/00234
d D 5.4 89/05/11 10:57:40 bostic 7 6
c file reorg, pathnames.h, paths.h; some reformatting
e
s 00040/00004/00210
d D 5.3 86/01/12 15:26:22 sam 6 5
c add tahoe
e
s 00015/00008/00199
d D 5.2 85/12/11 16:07:27 bloom 5 4
c fix problem with losing /vmunix in the middle, a bit of lint cleanup
e
s 00007/00001/00200
d D 5.1 85/05/30 16:20:33 mckusick 4 3
c Add copyright
e
s 00094/00028/00107
d D 1.3 85/05/01 01:33:18 sam 3 2
c major rework; fixup netstat stuff; pull disk cmds into common file; change 
c everthing related to disks to use dk_ndrive and global selction; use getw where possible
e
s 00003/00001/00132
d D 1.2 84/08/09 19:13:47 mckusick 2 1
c update to new sources from sam; weed out unnecessary #includes
e
s 00133/00000/00000
d D 1.1 84/08/09 17:59:24 mckusick 1 0
c date and time created 84/08/09 17:59:24 by mckusick
e
u
U
t
T
I 4
D 15
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 15
I 15
/*-
D 21
 * Copyright (c) 1980, 1992 The Regents of the University of California.
 * All rights reserved.
E 21
I 21
 * Copyright (c) 1980, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 21
 *
D 19
 * %sccs.include.proprietary.c%
E 19
I 19
 * %sccs.include.redist.c%
E 19
E 15
 */

E 4
I 1
#ifndef lint
D 3
static char sccsid[] = "%W% (Lucasfilm) %G%";
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
E 3
D 4
#endif
E 4
I 4
D 15
#endif not lint
E 15
I 15
#endif /* not lint */
E 15
E 4

D 14
#include "systat.h"
E 14
I 14
#include <sys/types.h>
E 14
D 2

E 2
I 2
D 3
#include <sys/param.h>
E 3
E 2
#include <sys/buf.h>
I 16

E 16
I 14
#include <nlist.h>
E 14
I 2
D 3
#include <sys/file.h>
E 3
I 3
#include <ctype.h>
I 7
#include <paths.h>
I 14
#include <string.h>
#include <stdlib.h>
#include "systat.h"
#include "extern.h"
E 14
E 7

I 14
static void dkselect __P((char *, int, int []));
static int read_names __P((void));

E 14
D 16
static struct nlist nlst[] = {
E 16
I 16
D 17
static struct nlist nl[] = {
E 17
I 17
static struct nlist namelist[] = {
E 17
E 16
#define	X_DK_NDRIVE	0
	{ "_dk_ndrive" },
D 8
#define	X_DK_MSPW	1
	{ "_dk_mspw" },
E 8
I 8
#define	X_DK_WPMS	1
	{ "_dk_wpms" },
E 8
E 3
E 2
#ifdef vax
D 3
#include <vaxuba/ubavar.h>
#include <vaxmba/mbavar.h>
E 3
I 3
D 6
#define	X_MBDINIT	2
E 6
I 6
D 8
#define	X_MBDINIT	(X_DK_MSPW+1)
E 8
I 8
#define	X_MBDINIT	(X_DK_WPMS+1)
E 8
E 6
	{ "_mbdinit" },
D 6
#define	X_UBDINIT	3
E 6
I 6
D 8
#define	X_UBDINIT	(X_DK_MSPW+2)
E 8
I 8
#define	X_UBDINIT	(X_DK_WPMS+2)
E 8
E 6
	{ "_ubdinit" },
E 3
#endif
#ifdef sun
D 3
#include <sundev/mbvar.h>
E 3
I 3
D 6
#define	X_MBDINIT	2
E 6
I 6
D 8
#define	X_MBDINIT	(X_DK_MSPW+1)
E 8
I 8
#define	X_MBDINIT	(X_DK_WPMS+1)
E 8
E 6
	{ "_mbdinit" },
E 3
#endif
I 6
#ifdef tahoe
D 8
#define	X_VBDINIT	(X_DK_MSPW+1)
E 8
I 8
#define	X_VBDINIT	(X_DK_WPMS+1)
E 8
	{ "_vbdinit" },
#endif
I 16
D 18
#ifdef hp300
E 18
I 18
#if defined(hp300) || defined(luna68k)
E 18
#define X_HPDINIT       (X_DK_WPMS+1)
        { "_hp_dinit" }, 
#endif
I 20
#ifdef mips
#define X_SCSI_DINIT	(X_DK_WPMS+1)
	{ "_scsi_dinit" },
#endif
E 20
E 16
E 6
I 2
D 3
#include <ctype.h>
E 3
I 3
	{ "" },
};
E 3
E 2

I 14
D 16
int dk_ndrive;
int *dk_select;
E 16
float *dk_mspw;
I 16
int dk_ndrive, *dk_select;
E 16
char **dr_name;

I 16
#include "names.c"					/* XXX */

E 16
int
E 14
D 3
char dr_name[DK_NDRIVE][10];
E 3
I 3
dkinit()
{
	register int i;
	register char *cp;
	static int once = 0;
	static char buf[1024];
E 3

I 3
	if (once)
D 5
		return;
	once = 1;
E 5
I 5
		return(1);
E 5
D 7
	nlist("/vmunix", nlst);
E 7
I 7
D 13
	nlist(_PATH_UNIX, nlst);
E 13
I 13
D 14
	kvm_nlist(nlst);
E 14
I 14

D 16
	if (kvm_nlist(kd, nlst)) {
		nlisterr(nlst);
E 16
I 16
D 17
	if (kvm_nlist(kd, nl)) {
		nlisterr(nl);
E 17
I 17
	if (kvm_nlist(kd, namelist)) {
		nlisterr(namelist);
E 17
E 16
		return(0);
	}
E 14
E 13
E 7
D 16
	if (nlst[X_DK_NDRIVE].n_value == 0) {
E 16
I 16
D 17
	if (nl[X_DK_NDRIVE].n_value == 0) {
E 17
I 17
	if (namelist[X_DK_NDRIVE].n_value == 0) {
E 17
E 16
		error("dk_ndrive undefined in kernel");
D 5
		return;
E 5
I 5
		return(0);
E 5
	}
D 10
	dk_ndrive = getw(nlst[X_DK_NDRIVE].n_value);
E 10
I 10
D 13
	dk_ndrive = getword(nlst[X_DK_NDRIVE].n_value);
E 13
I 13
	NREAD(X_DK_NDRIVE, &dk_ndrive, LONG);
E 13
E 10
	if (dk_ndrive <= 0) {
D 7
		error("dk_ndrive=%d according to /vmunix", dk_ndrive);
E 7
I 7
		error("dk_ndrive=%d according to %s", dk_ndrive, _PATH_UNIX);
E 7
D 5
		return;
E 5
I 5
		return(0);
E 5
	}
	dk_mspw = (float *)calloc(dk_ndrive, sizeof (float));
D 8
	lseek(kmem, nlst[X_DK_MSPW].n_value, L_SET);
	read(kmem, dk_mspw, dk_ndrive * sizeof (float));
E 8
I 8
D 13
	lseek(kmem, nlst[X_DK_WPMS].n_value, L_SET);
E 13
	{
		long *wpms = (long *)calloc(dk_ndrive, sizeof(long));
D 13
		read(kmem, wpms, dk_ndrive * sizeof (long));
E 13
I 13
		KREAD(NPTR(X_DK_WPMS), wpms, dk_ndrive * sizeof (long));
E 13
		for (i = 0; i < dk_ndrive; i++)
			*(dk_mspw + i) = (*(wpms + i) == 0)? 0.0:
			                 (float) 1.0 / *(wpms + i);
		free(wpms);
	}
E 8
	dr_name = (char **)calloc(dk_ndrive, sizeof (char *));
	dk_select = (int *)calloc(dk_ndrive, sizeof (int));
	for (cp = buf, i = 0; i < dk_ndrive; i++) {
		dr_name[i] = cp;
		sprintf(dr_name[i], "dk%d", i);
		cp += strlen(dr_name[i]) + 1;
		if (dk_mspw[i] != 0.0)
			dk_select[i] = 1;
	}
D 5
	read_names();
E 5
I 5
D 6
	if (! read_names()) {
E 6
I 6
	if (!read_names()) {
E 6
		free(dr_name);
		free(dk_select);
		free(dk_mspw);
		return(0);
	}
	once = 1;
	return(1);
E 5
}

I 14
int
E 14
dkcmd(cmd, args)
	char *cmd, *args;
{
D 7

        if (prefix(cmd, "display") || prefix(cmd, "add")) {
                dkselect(args, 1, dk_select);
E 7
I 7
	if (prefix(cmd, "display") || prefix(cmd, "add")) {
		dkselect(args, 1, dk_select);
E 7
		return (1);
D 7
        }
        if (prefix(cmd, "ignore") || prefix(cmd, "delete")) {
                dkselect(args, 0, dk_select);
E 7
I 7
	}
	if (prefix(cmd, "ignore") || prefix(cmd, "delete")) {
		dkselect(args, 0, dk_select);
E 7
		return (1);
D 7
        }
        if (prefix(cmd, "drives")) {
E 7
I 7
	}
	if (prefix(cmd, "drives")) {
E 7
		register int i;

D 7
                move(CMDLINE, 0); clrtoeol();
                for (i = 0; i < dk_ndrive; i++)
                        if (dk_mspw[i] != 0.0)
                                printw("%s ", dr_name[i]);
                return (1);
        }
E 7
I 7
		move(CMDLINE, 0); clrtoeol();
		for (i = 0; i < dk_ndrive; i++)
			if (dk_mspw[i] != 0.0)
				printw("%s ", dr_name[i]);
		return (1);
	}
E 7
	return (0);
}
D 16

E 3
#define steal(where, var) \
D 13
	lseek(kmem, where, L_SET); read(kmem, &var, sizeof var);
E 13
I 13
	KREAD(where, &var, sizeof var)
E 13

#ifdef vax
D 3
read_names(mp, up)
	register struct mba_device *mp;
	register struct uba_device *up;
E 3
I 3
D 11
#include <vaxuba/ubavar.h>
#include <vaxmba/mbavar.h>
E 11
I 11
#include <vax/uba/ubavar.h>
#include <vax/mba/mbavar.h>
E 11

I 14
static int
E 14
read_names()
E 3
{
D 5
	static int once = 0;
E 5
	struct mba_device mdev;
	struct mba_driver mdrv;
	short two_char;
	char *cp = (char *)&two_char;
	struct uba_device udev;
	struct uba_driver udrv;
I 3
	register struct mba_device *mp;
	register struct uba_device *up;
E 3

D 3
	if (once)
		return;
	once++;
	if (up == 0) {
E 3
I 3
	mp = (struct mba_device *)nlst[X_MBDINIT].n_value;
	up = (struct uba_device *)nlst[X_UBDINIT].n_value;
	if (mp == 0 && up == 0) {
E 3
		error("Disk init info not in namelist\n");
D 5
		return;
E 5
I 5
		return(0);
E 5
	}
	if (mp) for (;;) {
		steal(mp++, mdev);
		if (mdev.mi_driver == 0)
			break;
		if (mdev.mi_dk < 0 || mdev.mi_alive == 0)
			continue;
		steal(mdev.mi_driver, mdrv);
		steal(mdrv.md_dname, two_char);
		sprintf(dr_name[mdev.mi_dk], "%c%c%d",
		    cp[0], cp[1], mdev.mi_unit);
	}
	if (up) for (;;) {
		steal(up++, udev);
		if (udev.ui_driver == 0)
			break;
		if (udev.ui_dk < 0 || udev.ui_alive == 0)
			continue;
		steal(udev.ui_driver, udrv);
		steal(udrv.ud_dname, two_char);
		sprintf(dr_name[udev.ui_dk], "%c%c%d",
		    cp[0], cp[1], udev.ui_unit);
	}
I 5
	return(1);
E 5
}
#endif

#ifdef sun
D 3
/*VARARGS*/
read_names(mp)
	register struct mb_device *mp;
E 3
I 3
#include <sundev/mbvar.h>

I 14
static int
E 14
read_names()
E 3
{
	static int once = 0;
	struct mb_device mdev;
	struct mb_driver mdrv;
	short two_char;
	char *cp = (char *) &two_char;
I 3
	register struct mb_device *mp;
E 3

D 3
	if (once)
		return;
	once++;
E 3
I 3
	mp = (struct mb_device *)nlst[X_MBDINIT].n_value;
E 3
	if (mp == 0) {
		error("Disk init info not in namelist\n");
D 5
		return;
E 5
I 5
		return(0);
E 5
	}
	for (;;) {
		steal(mp++, mdev);
		if (mdev.md_driver == 0)
			break;
		if (mdev.md_dk < 0 || mdev.md_alive == 0)
			continue;
		steal(mdev.md_driver, mdrv);
		steal(mdrv.mdr_dname, two_char);
		sprintf(dr_name[mdev.md_dk], "%c%c%d",
		    cp[0], cp[1], mdev.md_unit);
	}
I 5
	return(1);
I 6
}
#endif

#ifdef tahoe
D 9
#include <tahoevba/vbavar.h>
E 9
I 9
#include <tahoe/vba/vbavar.h>
E 9

/*
 * Read the drive names out of kmem.
 */
I 14
static int
E 14
read_names()
{
	struct vba_device udev, *up;
	struct vba_driver udrv;
	short two_char;
	char *cp = (char *)&two_char;

	up = (struct vba_device *) nlst[X_VBDINIT].n_value;
	if (up == 0) {
D 14
		fprintf(stderr, "vmstat: Disk init info not in namelist\n");
		exit(1);
E 14
I 14
		error("vmstat: Disk init info not in namelist\n");
		return (0);
E 14
	}
	for (;;) {
		steal(up++, udev);
		if (udev.ui_driver == 0)
			break;
		if (udev.ui_dk < 0 || udev.ui_alive == 0)
			continue;
		steal(udev.ui_driver, udrv);
		steal(udrv.ud_dname, two_char);
		sprintf(dr_name[udev.ui_dk], "%c%c%d",
		     cp[0], cp[1], udev.ui_unit);
	}
I 14
	return (1);
E 14
E 6
E 5
}
#endif

I 12
#ifdef hp300
D 14
read_names() {}
E 14
I 14
static int
read_names()
{
	/* XXX */
	return (1);
}
E 14
#endif
E 16

I 14
static void
E 14
E 12
dkselect(args, truefalse, selections)
	char *args;
	int truefalse, selections[];
{
	register char *cp;
	register int i;
	char *index();

	cp = index(args, '\n');
	if (cp)
		*cp = '\0';
	for (;;) {
		for (cp = args; *cp && isspace(*cp); cp++)
			;
		args = cp;
		for (; *cp && !isspace(*cp); cp++)
			;
		if (*cp)
			*cp++ = '\0';
		if (cp - args == 0)
			break;
D 3
		for (i = 0; i < DK_NDRIVE; i++)
E 3
I 3
		for (i = 0; i < dk_ndrive; i++)
E 3
			if (strcmp(args, dr_name[i]) == 0) {
D 3
				selections[i] = truefalse;
E 3
				if (dk_mspw[i] != 0.0)
D 3
					if (truefalse == 0)
						ndrives--;
					else
						ndrives++;
E 3
I 3
					selections[i] = truefalse;
				else
					error("%s: drive not configured",
					    dr_name[i]);
E 3
				break;
			}
D 3
		if (i >= DK_NDRIVE)
E 3
I 3
		if (i >= dk_ndrive)
E 3
			error("%s: unknown drive", args);
		args = cp;
	}
}
E 1
