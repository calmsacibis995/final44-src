h11374
s 00015/00066/00316
d D 8.4 95/06/02 17:25:15 ralph 12 11
c final changes for pmax 4.4-Lite II release
e
s 00022/00000/00360
d D 8.3 94/11/21 15:25:44 mckusick 11 10
c add istty for spec_open
e
s 00006/00000/00354
d D 8.2 93/11/14 13:32:59 hibler 10 9
c add iszerodev predicate
e
s 00002/00002/00352
d D 8.1 93/06/10 23:06:30 bostic 9 8
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00081/00000/00273
d D 7.8 93/05/02 21:27:42 ralph 8 7
c added new security stuff.
e
s 00003/00003/00270
d D 7.7 93/04/05 21:42:40 ralph 7 6
c make graphics devices define mmap routines.
e
s 00004/00000/00269
d D 7.6 93/03/23 18:55:40 ralph 6 5
c changes from Rick Macklem
e
s 00025/00008/00244
d D 7.5 92/11/15 16:30:26 ralph 5 4
c updates from Rick Macklem for maxine.
e
s 00006/00006/00246
d D 7.4 92/10/11 11:23:05 bostic 4 3
c make kernel includes standard
e
s 00004/00000/00248
d D 7.3 92/03/07 09:57:32 ralph 3 2
c added support for ds5000
e
s 00002/00002/00246
d D 7.2 92/02/29 11:34:33 ralph 2 1
c use rawread and rawwrite for tz
e
s 00248/00000/00000
d D 7.1 92/01/07 17:29:19 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 9
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 4
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "ioctl.h"
#include "tty.h"
#include "conf.h"
E 4
I 4
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
I 8
#include <sys/proc.h>
#include <sys/vnode.h>
E 8
#include <sys/tty.h>
#include <sys/conf.h>
E 4

int	rawread		__P((dev_t, struct uio *, int));
int	rawwrite	__P((dev_t, struct uio *, int));
D 12
int	swstrategy	__P((struct buf *));
E 12
I 12
void	swstrategy	__P((struct buf *));
E 12
int	ttselect	__P((dev_t, int, struct proc *));

#define	dev_type_open(n)	int n __P((dev_t, int, int, struct proc *))
#define	dev_type_close(n)	int n __P((dev_t, int, int, struct proc *))
D 12
#define	dev_type_strategy(n)	int n __P((struct buf *))
E 12
I 12
#define	dev_type_strategy(n)	void n __P((struct buf *))
E 12
#define	dev_type_ioctl(n) \
D 12
	int n __P((dev_t, int, caddr_t, int, struct proc *))
E 12
I 12
	int n __P((dev_t, u_long, caddr_t, int, struct proc *))
E 12

/* bdevsw-specific types */
D 12
#define	dev_type_dump(n)	int n __P((dev_t))
E 12
I 12
#define	dev_type_dump(n)	int n __P(())
E 12
#define	dev_type_size(n)	int n __P((dev_t))

#define	dev_decl(n,t)	__CONCAT(dev_type_,t)(__CONCAT(n,t))
#define	dev_init(c,n,t) \
	(c > 0 ? __CONCAT(n,t) : (__CONCAT(dev_type_,t)((*))) enxio)

/* bdevsw-specific initializations */
#define	dev_size_init(c,n)	(c > 0 ? __CONCAT(n,size) : 0)

#define	bdev_decl(n) \
	dev_decl(n,open); dev_decl(n,close); dev_decl(n,strategy); \
	dev_decl(n,ioctl); dev_decl(n,dump); dev_decl(n,size)

#define	bdev_disk_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
D 12
	dev_init(c,n,dump), dev_size_init(c,n), 0 }
E 12
I 12
	dev_init(c,n,dump), dev_size_init(c,n), D_DISK }
E 12

#define	bdev_tape_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
D 12
	dev_init(c,n,dump), 0, B_TAPE }
E 12
I 12
	dev_init(c,n,dump), 0, D_TAPE }
E 12

#define	bdev_swap_init() { \
	(dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
	swstrategy, (dev_type_ioctl((*))) enodev, \
D 12
	(dev_type_dump((*))) enodev, 0, 0 }
E 12
I 12
	(dev_type_dump((*))) enodev, (dev_type_size((*))) enodev, 0 }
E 12

#define	bdev_notdef()	bdev_tape_init(0,no)
bdev_decl(no);	/* dummy declarations */

#include "rz.h"
#include "vn.h"

bdev_decl(rz);
bdev_decl(vn);

struct bdevsw	bdevsw[] =
{
	bdev_disk_init(NRZ,rz),	/* 0: SCSI disk */
	bdev_swap_init(),	/* 1: swap pseudo-device */
	bdev_disk_init(NVN,vn),	/* 2: vnode disk driver (swap to files) */
};

int	nblkdev = sizeof (bdevsw) / sizeof (bdevsw[0]);

/* cdevsw-specific types */
#define	dev_type_read(n)	int n __P((dev_t, struct uio *, int))
#define	dev_type_write(n)	int n __P((dev_t, struct uio *, int))
#define	dev_type_stop(n)	int n __P((struct tty *, int))
#define	dev_type_reset(n)	int n __P((int))
#define	dev_type_select(n)	int n __P((dev_t, int, struct proc *))
#define	dev_type_map(n)		int n __P(())

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
D 12
	dev_init(c,n,strategy) }
E 12
I 12
	dev_init(c,n,strategy), D_DISK }
E 12

/* open, close, read, write, ioctl, strategy */
#define	cdev_tape_init(c,n) { \
D 2
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
E 2
I 2
	dev_init(c,n,open), dev_init(c,n,close), rawread, \
	rawwrite, dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
E 2
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
D 12
	dev_init(c,n,strategy) }
E 12
I 12
	dev_init(c,n,strategy), D_TAPE }
E 12

/* open, close, read, write, ioctl, stop, tty */
#define	cdev_tty_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), dev_init(c,n,stop), \
	(dev_type_reset((*))) nullop, dev_tty_init(c,n), ttselect, \
D 12
	(dev_type_map((*))) enodev, 0 }
E 12
I 12
	(dev_type_map((*))) enodev, 0, D_TTY }
E 12

I 5
/* open, close, read, write, ioctl, select -- XXX should be a tty */
#define	cdev_cn_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
D 12
	(dev_type_map((*))) enodev, 0 }
E 12
I 12
	(dev_type_map((*))) enodev, 0, D_TTY }
E 12

E 5
#define	cdev_notdef() { \
	(dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
	(dev_type_read((*))) enodev, (dev_type_write((*))) enodev, \
	(dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, \
	(dev_type_map((*))) enodev, 0 }

cdev_decl(no);			/* dummy declarations */

D 5
cdev_decl(dc);
/* open, close, read, write, ioctl, select -- XXX should be a tty */
#define	cdev_dc_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, ttselect, \
	(dev_type_map((*))) enodev, 0 }
E 5
I 5
cdev_decl(cn);		/* console interface */
E 5

cdev_decl(ctty);
/* open, read, write, ioctl, select -- XXX should be a tty */
#define	cdev_ctty_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
D 12
	(dev_type_map((*))) enodev, 0 }
E 12
I 12
	(dev_type_map((*))) enodev, 0, D_TTY }
E 12

dev_type_read(mmrw);
/* read/write */
#define	cdev_mm_init(c,n) { \
	(dev_type_open((*))) nullop, (dev_type_close((*))) nullop, mmrw, \
	mmrw, (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, 0 }

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
D 12
	(dev_type_map((*))) enodev, 0 }
E 12
I 12
	(dev_type_map((*))) enodev, 0, D_TTY }
E 12

cdev_decl(log);
/* open, close, read, ioctl, select -- XXX should be a generic device */
#define	cdev_log_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	(dev_type_write((*))) enodev, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	dev_init(c,n,select), (dev_type_map((*))) enodev, 0 }

dev_type_open(fdopen);
/* open */
#define	cdev_fd_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) enodev, \
	(dev_type_read((*))) enodev, (dev_type_write((*))) enodev, \
	(dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) enodev, 0, (dev_type_select((*))) enodev, \
	(dev_type_map((*))) enodev, 0 }

#include "pm.h"
cdev_decl(pm);
#define	cdev_pm_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), \
D 7
	(dev_type_read((*))) enodev, (dev_type_write((*))) enodev, \
E 7
I 7
	(dev_type_read((*))) nullop, (dev_type_write((*))) nullop, \
E 7
	dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
D 7
	(dev_type_reset((*))) enodev, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }
E 7
I 7
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
	dev_init(c,n,map), 0 }
E 7

cdev_decl(rz);

#include "tz.h"
cdev_decl(tz);

cdev_decl(vn);
/* open, read, write, ioctl -- XXX should be a disk */
#define	cdev_vn_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
D 12
	0 }
E 12
I 12
	(dev_type_strategy((*))) nullop, D_DISK }
E 12

#include "bpfilter.h"
cdev_decl(bpf);
/* open, close, read, write, ioctl, select -- XXX should be generic device */
#define	cdev_bpf_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) enodev, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

I 3
#include "cfb.h"
cdev_decl(cfb);

I 5
#include "xcfb.h"
cdev_decl(xcfb);

I 6
#include "mfb.h"
cdev_decl(mfb);

E 6
#include "dtop.h"
cdev_decl(dtop);

#include "scc.h"
cdev_decl(scc);

#include "dc.h"
cdev_decl(dc);

E 5
E 3
struct cdevsw	cdevsw[] =
{
D 5
	cdev_dc_init(1,dc),		/* 0: virtual console */
E 5
I 5
	cdev_cn_init(1,cn),		/* 0: virtual console */
E 5
	cdev_ctty_init(1,ctty),		/* 1: controlling terminal */
	cdev_mm_init(1,mm),		/* 2: /dev/{null,mem,kmem,...} */
	cdev_swap_init(1,sw),		/* 3: /dev/drum (swap pseudo-device) */
	cdev_tty_init(NPTY,pts),	/* 4: pseudo-tty slave */
	cdev_ptc_init(NPTY,ptc),	/* 5: pseudo-tty master */
	cdev_log_init(1,log),		/* 6: /dev/klog */
	cdev_fd_init(1,fd),		/* 7: file descriptor pseudo-dev */
	cdev_pm_init(NPM,pm),		/* 8: frame buffer */
	cdev_disk_init(NRZ,rz),		/* 9: SCSI disk */
	cdev_tape_init(NTZ,tz),		/* 10: SCSI tape */
	cdev_vn_init(NVN,vn),		/* 11: vnode disk */
	cdev_bpf_init(NBPFILTER,bpf),	/* 12: berkeley packet filter */
I 3
	cdev_pm_init(NCFB,cfb),		/* 13: color frame buffer */
I 5
	cdev_pm_init(NXCFB,xcfb),	/* 14: maxine color frame buffer */
	cdev_tty_init(NDTOP,dtop),	/* 15: desktop bus interface */
	cdev_tty_init(NDC,dc),		/* 16: dc7085 serial interface */
	cdev_tty_init(NSCC,scc),	/* 17: scc 82530 serial interface */
I 6
	cdev_pm_init(NMFB,mfb),		/* 18: mono frame buffer */
E 6
E 5
E 3
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
dev_t	swapdev = makedev(1, 0);
I 8

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

I 10
iszerodev(dev)
	dev_t dev;
{
	return (major(dev) == 2 && minor(dev) == 12);
D 12
}

E 10
/*
I 11
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
	case 16:
	case 17:
		return (1);
	default:
		return (0);
	}
}

/*
E 11
 * Routine to determine if a device is a disk.
 *
 * A minimal stub routine can always return 0.
 */
isdisk(dev, type)
	dev_t dev;
	int type;
{

	switch (major(dev)) {
	case 0:
	case 2:
		if (type == VBLK)
			return (1);
		return (0);
	case 9:
	case 11:
		if (type == VCHR)
			return (1);
		/* FALLTHROUGH */
	default:
		return (0);
	}
	/* NOTREACHED */
E 12
}

#define MAXDEV	19
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
	/* 8 */		NODEV,
	/* 9 */		0,
	/* 10 */	NODEV,
	/* 11 */	2,
	/* 12 */	NODEV,
	/* 13 */	NODEV,
	/* 14 */	NODEV,
	/* 15 */	NODEV,
	/* 16 */	NODEV,
	/* 17 */	NODEV,
	/* 18 */	NODEV,
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
E 8
E 1
