h03885
s 00002/00002/00214
d R 8.2 94/01/12 15:21:42 mckusick 10 9
c ifdef sun => ifdef sparc
e
s 00002/00002/00214
d D 8.1 93/06/06 22:22:18 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00039/00001/00177
d D 5.8 93/03/27 16:49:29 ralph 8 7
c added mips case
e
s 00007/00003/00171
d D 5.7 92/09/02 11:58:06 bostic 7 6
c add luna68k
e
s 00005/00005/00169
d D 5.6 92/09/02 11:57:36 bostic 6 5
c nl is an exported curses function
e
s 00069/00030/00105
d D 5.5 92/07/24 12:44:38 bostic 5 4
c make names.c useable by systat; read_names now returns a value instead
c of exiting, add support (completely untested) for Sun's
e
s 00012/00012/00123
d D 5.4 92/06/23 10:46:33 mccanne 4 3
c port to new kvm
e
s 00001/00001/00134
d D 5.3 92/06/17 15:53:56 bostic 3 2
c hpux stuff moved
e
s 00004/00003/00131
d D 5.2 91/06/04 20:35:15 karels 2 1
c fix hp300 bugs
e
s 00134/00000/00000
d D 5.1 91/04/23 17:18:00 bostic 1 0
c date and time created 91/04/23 17:18:00 by bostic
e
u
U
t
T
I 1
/*-
D 9
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 7
#if !defined(hp300) && !defined(tahoe) && !defined(vax)
E 7
I 7
D 8
#if !defined(hp300) && !defined(tahoe) && !defined(vax) && !defined(luna68k)
E 8
I 8
#if !defined(hp300) && !defined(tahoe) && !defined(vax) && \
	!defined(luna68k) && !defined(mips)
E 8
E 7
char *defdrives[] = { 0 };
#endif

D 7
#ifdef hp300
E 7
I 7
#if defined(hp300) || defined(luna68k)
#if defined(hp300)
E 7
D 3
#include <hp300/dev/device.h>
E 3
I 3
#include <hp/dev/device.h>
I 7
#else
#include <luna68k/dev/device.h>
#endif
E 7
E 3

D 2
char *defdrives[] = { "rd0", "rd1", "rd2", 0 };
E 2
I 2
char *defdrives[] = { "sd0", "sd1", "sd2", "rd0", "rd1", "rd2", 0 };
E 2

D 5
void
E 5
I 5
int
E 5
read_names()
{
	register char *p;
	register u_long hp;
	static char buf[BUFSIZ];
	struct hp_device hdev;
	struct driver hdrv;
	char name[10];

D 6
	hp = nl[X_HPDINIT].n_value;
E 6
I 6
	hp = namelist[X_HPDINIT].n_value;
E 6
	if (hp == 0) {
D 5
		(void) fprintf(stderr,
		    "vmstat: disk init info not in namelist\n");
		exit(1);
E 5
I 5
		(void)fprintf(stderr,
		    "disk init info not in namelist\n");
		return (0);
E 5
	}
	p = buf;
	for (;; hp += sizeof hdev) {
D 4
		(void)kvm_read((void *)hp, &hdev, sizeof hdev);
E 4
I 4
		(void)kvm_read(kd, hp, &hdev, sizeof hdev);
E 4
		if (hdev.hp_driver == 0)
			break;
D 2
		if (hdev.hp_dk < 0 || hdev.hp_alive == 0)
E 2
I 2
		if (hdev.hp_dk < 0 || hdev.hp_alive == 0 ||
		    hdev.hp_cdriver == 0)
E 2
			continue;
D 4
		(void)kvm_read(hdev.hp_driver, &hdrv, sizeof hdrv);
		(void)kvm_read(hdrv.d_name, name, sizeof name);
E 4
I 4
		(void)kvm_read(kd, (u_long)hdev.hp_driver, &hdrv, sizeof hdrv);
		(void)kvm_read(kd, (u_long)hdrv.d_name, name, sizeof name);
E 4
		dr_name[hdev.hp_dk] = p;
D 2
		p += sprintf(p, "%s%d", name, hdev.hp_unit);
E 2
I 2
		p += sprintf(p, "%s%d", name, hdev.hp_unit) + 1;
E 2
	}
I 5
	return (1);
E 5
}
D 7
#endif /* hp300 */
E 7
I 7
#endif /* hp300 || luna68k */
E 7

#ifdef tahoe
#include <tahoe/vba/vbavar.h>

char *defdrives[] = { "dk0", "dk1", "dk2", 0 };

D 5
void
E 5
I 5
int
E 5
read_names()
{
	register char *p;
	struct vba_device udev, *up;
	struct vba_driver udrv;
	char name[10];
	static char buf[BUFSIZ];

D 6
	up = (struct vba_device *) nl[X_VBDINIT].n_value;
E 6
I 6
	up = (struct vba_device *)namelist[X_VBDINIT].n_value;
E 6
	if (up == 0) {
		(void) fprintf(stderr,
D 5
		    "vmstat: disk init info not in namelist\n");
		exit(1);
E 5
I 5
		    "disk init info not in namelist\n");
		return (0);
E 5
	}
	p = buf;
	for (;; up += sizeof udev) {
D 4
		(void)kvm_read(up, &udev, sizeof udev);
E 4
I 4
		(void)kvm_read(kd, up, &udev, sizeof udev);
E 4
		if (udev.ui_driver == 0)
			break;
		if (udev.ui_dk < 0 || udev.ui_alive == 0)
			continue;
D 4
		(void)kvm_read(udev.ui_driver, &udrv, sizeof udrv);
		(void)kvm_read(udrv.ud_dname, name, sizeof name);
E 4
I 4
		(void)kvm_read(kd, udev.ui_driver, &udrv, sizeof udrv);
		(void)kvm_read(kd, udrv.ud_dname, name, sizeof name);
E 4
		dr_name[udev.ui_dk] = p;
		p += sprintf(p, "%s%d", name, udev.ui_unit);
	}
I 5
	return (1);
E 5
}
#endif /* tahoe */

#ifdef vax
#include <vax/uba/ubavar.h>
#include <vax/mba/mbavar.h>

char *defdrives[] = { "hp0", "hp1", "hp2", 0 };

D 5
void
E 5
I 5
int
E 5
read_names()
{
	register char *p;
	unsigned long mp, up;
	struct mba_device mdev;
	struct mba_driver mdrv;
	struct uba_device udev;
	struct uba_driver udrv;
	char name[10];
	static char buf[BUFSIZ];

D 6
	mp = nl[X_MBDINIT].n_value;
	up = nl[X_UBDINIT].n_value;
E 6
I 6
	mp = namelist[X_MBDINIT].n_value;
	up = namelist[X_UBDINIT].n_value;
E 6
	if (mp == 0 && up == 0) {
D 5
		(void) fprintf(stderr,
		    "vmstat: disk init info not in namelist\n");
		exit(1);
E 5
I 5
		(void)fprintf(stderr,
		    "disk init info not in namelist\n");
		return (0);
E 5
	}
	p = buf;
D 5
	if (mp) for (;; mp += sizeof mdev) {
D 4
		(void)kvm_read(mp, &mdev, sizeof mdev);
E 4
I 4
		(void)kvm_read(kd, mp, &mdev, sizeof mdev);
E 4
		if (mdev.mi_driver == 0)
			break;
		if (mdev.mi_dk < 0 || mdev.mi_alive == 0)
			continue;
D 4
		(void)kvm_read(mdev.mi_driver, &mdrv, sizeof mdrv);
		(void)kvm_read(mdrv.md_dname, name, sizeof name);
E 4
I 4
		(void)kvm_read(kd, mdev.mi_driver, &mdrv, sizeof mdrv);
		(void)kvm_rea(kd, mdrv.md_dname, name, sizeof name);
E 4
		dr_name[mdev.mi_dk] = p;
		p += sprintf(p, "%s%d", name, mdev.mi_unit);
E 5
I 5
	if (mp)
		for (;; mp += sizeof mdev) {
			(void)kvm_read(kd, mp, &mdev, sizeof mdev);
			if (mdev.mi_driver == 0)
				break;
			if (mdev.mi_dk < 0 || mdev.mi_alive == 0)
				continue;
			(void)kvm_read(kd, mdev.mi_driver, &mdrv, sizeof mdrv);
			(void)kvm_rea(kd, mdrv.md_dname, name, sizeof name);
			dr_name[mdev.mi_dk] = p;
			p += sprintf(p, "%s%d", name, mdev.mi_unit);
		}
	if (up)
		for (;; up += sizeof udev) {
			(void)kvm_read(kd, up, &udev, sizeof udev);
			if (udev.ui_driver == 0)
				break;
			if (udev.ui_dk < 0 || udev.ui_alive == 0)
				continue;
			(void)kvm_read(kd, udev.ui_driver, &udrv, sizeof udrv);
			(void)kvm_read(kd, udrv.ud_dname, name, sizeof name);
			dr_name[udev.ui_dk] = p;
			p += sprintf(p, "%s%d", name, udev.ui_unit);
		}
	return (1);
}
#endif /* vax */

#ifdef sun
#include <sundev/mbvar.h>

int
read_names()
{
	static int once = 0;
	struct mb_device mdev;
	struct mb_driver mdrv;
	short two_char;
	char *cp = (char *) &two_char;
	register struct mb_device *mp;

D 6
	mp = (struct mb_device *)nl[X_MBDINIT].n_value;
E 6
I 6
	mp = (struct mb_device *)namelist[X_MBDINIT].n_value;
E 6
	if (mp == 0) {
		(void)fprintf(stderr,
		    "disk init info not in namelist\n");
		return (0);
E 5
	}
D 5
	if (up) for (;; up += sizeof udev) {
D 4
		(void)kvm_read(up, &udev, sizeof udev);
E 4
I 4
		(void)kvm_read(kd, up, &udev, sizeof udev);
E 4
		if (udev.ui_driver == 0)
E 5
I 5
	for (;; ++mp) {
		(void)kvm_read(kd, mp++, &mdev, sizeof(mdev));
		if (mdev.md_driver == 0)
E 5
			break;
D 5
		if (udev.ui_dk < 0 || udev.ui_alive == 0)
E 5
I 5
		if (mdev.md_dk < 0 || mdev.md_alive == 0)
E 5
			continue;
D 4
		(void)kvm_read(udev.ui_driver, &udrv, sizeof udrv);
		(void)kvm_read(udrv.ud_dname, name, sizeof name);
E 4
I 4
D 5
		(void)kvm_read(kd, udev.ui_driver, &udrv, sizeof udrv);
		(void)kvm_read(kd, udrv.ud_dname, name, sizeof name);
E 4
		dr_name[udev.ui_dk] = p;
		p += sprintf(p, "%s%d", name, udev.ui_unit);
E 5
I 5
		(void)kvm_read(kd, mdev.md_driver, &mdrv, sizeof(mdrv));
		(void)kvm_read(kd, mdrv.mdr_dname, &two_char, sizeof(two_char));
		(void)sprintf(dr_name[mdev.md_dk],
		    "%c%c%d", cp[0], cp[1], mdev.md_unit);
E 5
	}
I 5
	return(1);
E 5
}
D 5
#endif /* vax */
E 5
I 5
#endif /* sun */
I 8

#if defined(mips)
#include <pmax/dev/device.h>

char *defdrives[] = { "rz0", "rz1", "rz2", "rz3", "rz4", "rz5", "rz6", 0 };

int
read_names()
{
	register char *p;
	register u_long sp;
	static char buf[BUFSIZ];
	struct scsi_device sdev;
	struct driver hdrv;
	char name[10];

	sp = namelist[X_SCSI_DINIT].n_value;
	if (sp == 0) {
		(void)fprintf(stderr, "disk init info not in namelist\n");
		return (0);
	}
	p = buf;
	for (;; sp += sizeof sdev) {
		(void)kvm_read(kd, sp, &sdev, sizeof sdev);
		if (sdev.sd_driver == 0)
			break;
		if (sdev.sd_dk < 0 || sdev.sd_alive == 0 ||
		    sdev.sd_cdriver == 0)
			continue;
		(void)kvm_read(kd, (u_long)sdev.sd_driver, &hdrv, sizeof hdrv);
		(void)kvm_read(kd, (u_long)hdrv.d_name, name, sizeof name);
		dr_name[sdev.sd_dk] = p;
		p += sprintf(p, "%s%d", name, sdev.sd_unit) + 1;
	}
	return (1);
}
#endif /* mips */
E 8
E 5
E 1
