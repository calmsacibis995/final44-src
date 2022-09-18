h34418
s 00024/00001/00380
d D 8.4 94/11/21 15:23:09 mckusick 13 12
c add istty for spec_open
e
s 00006/00007/00375
d D 8.3 93/12/06 20:18:50 akito 12 11
c sync up to hp300/hp300/conf.c   8.2 (Berkeley) 11/14/93
e
s 00006/00000/00376
d D 8.2 93/11/14 13:32:35 hibler 11 10
c add iszerodev predicate
e
s 00002/00002/00374
d D 8.1 93/06/10 22:25:07 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00083/00001/00293
d D 7.9 93/05/02 05:46:22 akito 9 8
c sync up to  hp300/hp300/conf.c     7.16
e
s 00018/00004/00276
d D 7.8 93/03/17 11:10:03 akito 8 7
c added ldist_init macros
e
s 00009/00001/00271
d D 7.7 92/12/26 12:00:09 akito 7 6
c add entry for keyboard driver
e
s 00011/00002/00261
d D 7.6 92/12/19 09:56:21 akito 6 5
c add fb device driver's entry
e
s 00007/00007/00256
d D 7.5 92/11/17 16:57:43 akito 5 4
c make kernel includes standard, again
e
s 00011/00008/00252
d D 7.4 92/11/17 16:48:02 akito 4 3
c add bmc driver entry
e
s 00007/00007/00253
d D 7.3 92/10/11 11:07:45 bostic 3 2
c make kernel includes standard
e
s 00002/00013/00258
d D 7.2 92/07/23 16:01:27 fujita 2 1
c update for 4.4BSD-alpha distribution
e
s 00271/00000/00000
d D 7.1 92/06/15 06:38:32 fujita 1 0
c date and time created 92/06/15 06:38:32 by fujita
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 OMRON Corporation.
D 10
 * Copyright (c) 1991, 1992 The Regents of the University of California.
 * All rights reserved.
E 10
I 10
 * Copyright (c) 1991, 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 10
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: hp300/hp300/conf.c	7.1 (Berkeley) 6/4/92
E 2
I 2
D 8
 * from: hp300/hp300/conf.c	7.13 (Berkeley) 7/9/92
E 8
I 8
D 9
 * from: hp300/hp300/conf.c	7.15 (Berkeley) 12/27/92
E 9
I 9
D 12
 * from: hp300/hp300/conf.c	7.16 (Berkeley) 4/28/93
E 12
I 12
 * from: hp300/hp300/conf.c	8.2 (Berkeley) 11/14/93
E 12
E 9
E 8
E 2
 *
 *	%W% (Berkeley) %G%
 */

D 3
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/buf.h"
#include "sys/ioctl.h"
#include "sys/proc.h"
#include "sys/tty.h"
#include "sys/conf.h"
E 3
I 3
D 4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
#include <sys/tty.h>
#include <sys/conf.h>
E 4
I 4
D 5
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/buf.h"
#include "sys/ioctl.h"
#include "sys/proc.h"
#include "sys/tty.h"
#include "sys/conf.h"
E 5
I 5
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
I 9
#include <sys/vnode.h>
E 9
#include <sys/tty.h>
#include <sys/conf.h>
E 5
E 4
E 3

int	rawread		__P((dev_t, struct uio *, int));
int	rawwrite	__P((dev_t, struct uio *, int));
int	swstrategy	__P((struct buf *));
int	ttselect	__P((dev_t, int, struct proc *));

#define	dev_type_open(n)	int n __P((dev_t, int, int, struct proc *))
#define	dev_type_close(n)	int n __P((dev_t, int, int, struct proc *))
#define	dev_type_strategy(n)	int n __P((struct buf *))
#define	dev_type_ioctl(n) \
	int n __P((dev_t, int, caddr_t, int, struct proc *))

/* bdevsw-specific types */
#define	dev_type_dump(n)	int n __P(())
#define	dev_type_size(n)	int n __P((dev_t))

#define	dev_decl(n,t)	__CONCAT(dev_type_,t)(__CONCAT(n,t))
#define	dev_init(c,n,t) \
	(c > 0 ? __CONCAT(n,t) : (__CONCAT(dev_type_,t)((*))) enxio)

/* bdevsw-specific initializations */
#define	dev_size_init(c,n)	(c > 0 ? __CONCAT(n,size) : 0)

#define	bdev_decl(n) \
	dev_decl(n,open); dev_decl(n,close); dev_decl(n,strategy); \
	dev_decl(n,ioctl); dev_decl(n,dump); dev_decl(n,size)

I 8
/* disk without close routine */
E 8
#define	bdev_disk_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
	dev_init(c,n,dump), dev_size_init(c,n), 0 }

I 8
/* disk with close routine */
#define	bdev_ldisk_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
	dev_init(c,n,dump), dev_size_init(c,n), 0 }

E 8
#define	bdev_tape_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
	dev_init(c,n,dump), 0, B_TAPE }

#define	bdev_swap_init() { \
	(dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
	swstrategy, (dev_type_ioctl((*))) enodev, \
	(dev_type_dump((*))) enodev, 0, 0 }

#define	bdev_notdef()	bdev_tape_init(0,no)
I 6

E 6
bdev_decl(no);	/* dummy declarations */

#include "st.h"
#include "sd.h"
#include "vn.h"

bdev_decl(st);
bdev_decl(sd);
bdev_decl(vn);

struct bdevsw	bdevsw[] =
{
	bdev_notdef(),		/* 0 */
	bdev_notdef(),		/* 1 */
D 8
	bdev_notdef(),		/* 2: ram disk */
E 8
I 8
	bdev_notdef(),		/* 2 */
E 8
	bdev_swap_init(),	/* 3: swap pseudo-device */
D 8
	bdev_disk_init(NSD,sd),	/* 4: scsi disk */
E 8
I 8
	bdev_ldisk_init(NSD,sd),/* 4: scsi disk */
E 8
	bdev_notdef(),		/* 5 */
	bdev_disk_init(NVN,vn),	/* 6: vnode disk driver (swap to files) */
	bdev_tape_init(NST,st),	/* 7: scsi tape */
};

int	nblkdev = sizeof (bdevsw) / sizeof (bdevsw[0]);

/* cdevsw-specific types */
#define	dev_type_read(n)	int n __P((dev_t, struct uio *, int))
#define	dev_type_write(n)	int n __P((dev_t, struct uio *, int))
#define	dev_type_stop(n)	int n __P((struct tty *, int))
#define	dev_type_reset(n)	int n __P((int))
#define	dev_type_select(n)	int n __P((dev_t, int, struct proc *))
#define	dev_type_map(n)	int n __P(())

#define	cdev_decl(n) \
	dev_decl(n,open); dev_decl(n,close); dev_decl(n,read); \
	dev_decl(n,write); dev_decl(n,ioctl); dev_decl(n,stop); \
	dev_decl(n,reset); dev_decl(n,select); dev_decl(n,map); \
	dev_decl(n,strategy); extern struct tty __CONCAT(n,_tty)[]

#define	dev_tty_init(c,n)	(c > 0 ? __CONCAT(n,_tty) : 0)

/* open, read, write, ioctl, strategy */
#define	cdev_disk_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
	dev_init(c,n,strategy) }

/* open, close, read, write, ioctl, strategy */
I 8
#define	cdev_ldisk_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
	dev_init(c,n,strategy) }

/* open, close, read, write, ioctl, strategy */
E 8
#define	cdev_tape_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
	dev_init(c,n,strategy) }

/* open, close, read, write, ioctl, stop, tty */
#define	cdev_tty_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), dev_init(c,n,stop), \
	(dev_type_reset((*))) nullop, dev_tty_init(c,n), ttselect, \
	(dev_type_map((*))) enodev, 0 }

#define	cdev_notdef() { \
	(dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
	(dev_type_read((*))) enodev, (dev_type_write((*))) enodev, \
	(dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, \
	(dev_type_map((*))) enodev, 0 }

cdev_decl(no);			/* dummy declarations */

cdev_decl(cn);
/* open, close, read, write, ioctl, select -- XXX should be a tty */
#define	cdev_cn_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

cdev_decl(ctty);
/* open, read, write, ioctl, select -- XXX should be a tty */
#define	cdev_ctty_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

dev_type_read(mmrw);
D 12
/* read/write */
E 12
I 12
dev_type_map(mmmap);
/* read, write, mmap */
E 12
#define	cdev_mm_init(c,n) { \
	(dev_type_open((*))) nullop, (dev_type_close((*))) nullop, mmrw, \
	mmrw, (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) nullop, \
D 12
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, 0 }
E 12
I 12
	(dev_type_reset((*))) nullop, 0, seltrue, mmmap, 0 }
E 12

/* read, write, strategy */
#define	cdev_swap_init(c,n) { \
	(dev_type_open((*))) nullop, (dev_type_close((*))) nullop, rawread, \
	rawwrite, (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, (dev_type_select((*))) enodev, \
	(dev_type_map((*))) enodev, dev_init(c,n,strategy) }

#include "pty.h"
#define	pts_tty		pt_tty
#define	ptsioctl	ptyioctl
cdev_decl(pts);
#define	ptc_tty		pt_tty
#define	ptcioctl	ptyioctl
cdev_decl(ptc);

/* open, close, read, write, ioctl, tty, select */
#define	cdev_ptc_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, dev_tty_init(c,n), dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

cdev_decl(log);
/* open, close, read, ioctl, select -- XXX should be a generic device */
#define	cdev_log_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	(dev_type_write((*))) enodev, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	dev_init(c,n,select), (dev_type_map((*))) enodev, 0 }

cdev_decl(st);
cdev_decl(sd);

I 6
cdev_decl(fb);
/* open, close, ioctl, mmap */
#define	cdev_fb_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), (dev_type_read((*))) nullop, \
	(dev_type_write((*))) nullop, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	dev_init(c,n,select), dev_init(c,n,map), 0 }

E 6
#include "sio.h"
cdev_decl(sio);

I 4
#include "bmc.h"
cdev_decl(bmc);

I 7
cdev_decl(kbd);
/* open, close, read, ioctl, select, map -- XXX should be a map device */
#define	cdev_kbd_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	(dev_type_write((*))) nullop, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
D 12
	dev_init(c,n,select), (dev_type_map((*))) nullop, 0 }
E 12
I 12
	ttselect, (dev_type_map((*))) nullop, 0 }
E 12

E 7
E 4
cdev_decl(cd);

D 2
/*
#include "clock.h"
cdev_decl(clock);
*/
/* open, close, ioctl, map -- XXX should be a map device */
#define	cdev_clock_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), (dev_type_read((*))) nullop, \
	(dev_type_write((*))) nullop, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	(dev_type_select((*))) nullop, dev_init(c,n,map), 0 }

E 2
cdev_decl(vn);
/* open, read, write, ioctl -- XXX should be a disk */
#define	cdev_vn_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
	0 }

dev_type_open(fdopen);
/* open */
#define	cdev_fd_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) enodev, \
	(dev_type_read((*))) enodev, (dev_type_write((*))) enodev, \
	(dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) enodev, 0, (dev_type_select((*))) enodev, \
	(dev_type_map((*))) enodev, 0 }

#include "bpfilter.h"
cdev_decl(bpf);
/* open, close, read, write, ioctl, select -- XXX should be generic device */
#define	cdev_bpf_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) enodev, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

struct cdevsw	cdevsw[] =
{
	cdev_cn_init(1,cn),		/* 0: virtual console */
	cdev_ctty_init(1,ctty),		/* 1: controlling terminal */
	cdev_mm_init(1,mm),		/* 2: /dev/{null,mem,kmem,...} */
	cdev_swap_init(1,sw),		/* 3: /dev/drum (swap pseudo-device) */
	cdev_tty_init(NPTY,pts),	/* 4: pseudo-tty slave */
	cdev_ptc_init(NPTY,ptc),	/* 5: pseudo-tty master */
	cdev_log_init(1,log),		/* 6: /dev/klog */
	cdev_notdef(),			/* 7 */
D 8
	cdev_disk_init(NSD,sd),		/* 8: scsi disk */
E 8
I 8
	cdev_ldisk_init(NSD,sd),	/* 8: scsi disk */
E 8
D 6
	cdev_notdef(),			/* 9: ram disk */
	cdev_notdef(),			/* 10 */
E 6
I 6
	cdev_notdef(),			/* 9 */
	cdev_fb_init(1,fb),		/* 10: frame buffer */
E 6
	cdev_notdef(),			/* 11 */
	cdev_tty_init(NSIO,sio),	/* 12: built-in single-port serial */
D 4
	cdev_notdef(),			/* 13 */
E 4
I 4
	cdev_tty_init(NBMC,bmc),	/* 13: console terminal emulator */
E 4
D 7
	cdev_notdef(),			/* 14 */
E 7
I 7
D 13
	cdev_kbd_init(2,kbd),		/* 14: kyeboard */
E 13
I 13
	cdev_kbd_init(2,kbd),		/* 14: keyboard */
E 13
E 7
	cdev_notdef(),			/* 15 */
	cdev_notdef(),			/* 16 */
	cdev_notdef(),			/* 17 */
D 2
	cdev_notdef(),			/* 18: mapped clock */
E 2
I 2
	cdev_notdef(),			/* 18 */
E 2
	cdev_vn_init(NVN,vn),		/* 19: vnode disk */
	cdev_tape_init(NST,st),		/* 20: scsi tape */
	cdev_fd_init(1,fd),		/* 21: file descriptor pseudo-dev */
	cdev_bpf_init(NBPFILTER,bpf),	/* 22: berkeley packet filter */
};

int	nchrdev = sizeof (cdevsw) / sizeof (cdevsw[0]);

int	mem_no = 2; 	/* major device number of memory special file */

/*
 * Swapdev is a fake device implemented
 * in sw.c used only internally to get to swstrategy.
 * It cannot be provided to the users, because the
 * swstrategy routine munches the b_dev and b_blkno entries
 * before calling the appropriate driver.  This would horribly
 * confuse, e.g. the hashing routines. Instead, /dev/drum is
 * provided as a character (raw) device.
 */
dev_t	swapdev = makedev(3, 0);
I 9

/*
 * Routine that identifies /dev/mem and /dev/kmem.
 *
 * A minimal stub routine can always return 0.
 */
iskmemdev(dev)
	dev_t dev;
{

D 12
	if (major(dev) == 2 && (minor(dev) == 0 || minor(dev) == 1))
		return (1);
	return (0);
E 12
I 12
	return (major(dev) == 2 && minor(dev) < 2);
E 12
}

I 11
iszerodev(dev)
	dev_t dev;
{
	return (major(dev) == 2 && minor(dev) == 12);
I 13
}

/*
 * Routine to determine if a device is a tty.
 *
 * A minimal stub routine can always return 0.
 */
istty(dev)
	dev_t dev;
{

	switch (major(dev)) {
	case 0:
	case 1:
	case 4:
	case 5:
	case 12:
	case 13:
	case 14:
		return (1);
	default:
		return (0);
	}
E 13
}

E 11
/*
 * Routine to determine if a device is a disk.
 *
 * A minimal stub routine can always return 0.
 */
isdisk(dev, type)
	dev_t dev;
	int type;
{

	switch (major(dev)) {
	case 4:
	case 6:
		if (type == VBLK)
			return (1);
		return (0);
	case 8:
	case 19:
		if (type == VCHR)
			return (1);
		/* fall through */
	default:
		return (0);
	}
	/* NOTREACHED */
}

#define MAXDEV	21
static int chrtoblktbl[MAXDEV] =  {
      /* VCHR */      /* VBLK */
	/* 0 */		NODEV,
	/* 1 */		NODEV,
	/* 2 */		NODEV,
	/* 3 */		NODEV,
	/* 4 */		NODEV,
	/* 5 */		NODEV,
	/* 6 */		NODEV,
	/* 7 */		NODEV,
	/* 8 */		4,
	/* 9 */		NODEV,
	/* 10 */	NODEV,
	/* 11 */	NODEV,
	/* 12 */	NODEV,
	/* 13 */	NODEV,
	/* 14 */	NODEV,
	/* 15 */	NODEV,
	/* 16 */	NODEV,
	/* 17 */	NODEV,
	/* 18 */	NODEV,
	/* 19 */	6,
	/* 20 */	7,
};
/*
 * Routine to convert from character to block device number.
 *
 * A minimal stub routine can always return NODEV.
 */
chrtoblk(dev)
	dev_t dev;
{
	int blkmaj;

	if (major(dev) >= MAXDEV || (blkmaj = chrtoblktbl[major(dev)]) == NODEV)
		return (NODEV);
	return (makedev(blkmaj, minor(dev)));
}
E 9
E 1
