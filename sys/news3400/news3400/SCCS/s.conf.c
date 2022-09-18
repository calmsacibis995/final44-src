h29797
s 00022/00000/00464
d D 8.3 94/11/21 15:27:49 mckusick 8 7
c add istty for spec_open
e
s 00006/00000/00458
d D 8.2 93/11/14 13:32:49 hibler 7 6
c add iszerodev predicate
e
s 00002/00002/00456
d D 8.1 93/06/11 15:02:32 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00105/00000/00353
d D 7.5 93/05/07 05:41:11 utashiro 5 4
c add security routines iskmemdev, isdisk, and chrtoblk
e
s 00006/00006/00347
d D 7.4 92/12/17 01:28:25 utashiro 4 3
c make kernel includes standard
e
s 00003/00001/00350
d D 7.3 92/06/26 18:22:01 utashiro 3 2
c use NBM for bitmap console
e
s 00009/00005/00342
d D 7.2 92/06/25 18:33:01 utashiro 2 1
c added ctty for /dev/tty
e
s 00347/00000/00000
d D 7.1 92/06/04 16:06:52 mckusick 1 0
c initial port from Kazumasa Utashiro
e
u
U
t
T
I 1
/*
D 6
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Kazumasa Utashiro of Software Research Associates, Inc.
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
I 5
#include <sys/proc.h>
#include <sys/vnode.h>
E 5
#include <sys/tty.h>
#include <sys/conf.h>
E 4

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
#define	dev_type_dump(n)	int n __P((dev_t))
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
	dev_init(c,n,dump), dev_size_init(c,n), 0 }

#define	bdev_tape_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
	dev_init(c,n,dump), 0, B_TAPE }

#define	bdev_swap_init() { \
	(dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
	swstrategy, (dev_type_ioctl((*))) enodev, \
	(dev_type_dump((*))) enodev, 0, 0 }

#define	bdev_notdef()	bdev_tape_init(0,no)
bdev_decl(no);	/* dummy declarations */

#include "sd.h"
#define sd_b_ioctl	sdioctl
#define sd_b_strategy	sdstrategy
#define sd_b_dump	sddump
#define sd_b_size	sdsize
bdev_decl(sd_b_);

#include "fd.h"
#define fd_b_ioctl	fdioctl
#define fd_b_strategy	fdstrategy
#define fd_b_dump	fddump
#define fd_b_size	fdsize
bdev_decl(fd_b_);

#include "vn.h"
bdev_decl(vn);

struct bdevsw	bdevsw[] =
{
	bdev_disk_init(NSD,sd_b_),  /* 0: SCSI disk */
	bdev_disk_init(NFD,fd_b_),  /* 1: floppy disk */
	bdev_notdef(),		    /* 2 */
	bdev_disk_init(NVN,vn),	    /* 3: vnode disk driver (swap to files) */
	bdev_swap_init(),	    /* 4: swap pseudo-device */
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
	dev_init(c,n,strategy) }

/* open, close, read, write, ioctl, strategy */
#define	cdev_tape_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), rawread, \
	rawwrite, dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
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

/* open, close, read, write, ioctl -- XXX should be tty */
#define	cdev_vc_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), dev_init(c,n,stop), \
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

cdev_decl(no);			/* dummy declarations */

#include "rs.h"
cdev_decl(rs);
cdev_decl(vc);
I 3

#include "bm.h"
E 3
cdev_decl(cn);

I 2
cdev_decl(ctty);
/* open, read, write, ioctl, select -- XXX should be a tty */
#define	cdev_ctty_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }

E 2
dev_type_read(mmrw);
/* read/write */
#define	cdev_mm_init(c,n) { \
	(dev_type_open((*))) nullop, (dev_type_close((*))) nullop, mmrw, \
	mmrw, (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, 0 }

#include "sd.h"
#define sd_c_read	sdread
#define sd_c_write	sdwrite
#define sd_c_ioctl	sdioctl
#define sd_c_reset	sdreset
#define sd_c_strategy	sdstrategy
#define sd_c_dump	sddump
#define sd_c_size	sdsize
cdev_decl(sd_c_);

#include "fd.h"
#define fd_c_read	fdread
#define fd_c_write	fdwrite
#define fd_c_ioctl	fdioctl
#define fd_c_reset	fdreset
#define fd_c_strategy	fdstrategy
#define fd_c_dump	fddump
#define fd_c_size	fdsize
cdev_decl(fd_c_);

#include "lp.h"
cdev_decl(lp);

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

#include "kb.h"
cdev_decl(kb);
/* open, close, write, ioctl */
#define	cdev_kb_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), (dev_type_read((*))) enodev, \
	dev_init(c,n,write), dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	seltrue, (dev_type_map((*))) enodev, \
	0 }

#include "ms.h"
#define msmap msmmap
cdev_decl(ms);
/* open, close, read, write, ioctl, select */
#define	cdev_ms_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
	0 }

#include "fb.h"
cdev_decl(fb);
/* open, close, ioctl, mmap */
#define	cdev_fb_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), (dev_type_read((*))) enodev, \
	(dev_type_write((*))) enodev, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, 0 }
/*
	(dev_type_reset((*))) nullop, 0, seltrue, dev_init(c,n,map), 0 }
*/

#include "st.h"
cdev_decl(st);

#include "lb.h"
cdev_decl(lbp);

#include "ir.h"
cdev_decl(ir);
/* open, close, read, ioctl */
#define	cdev_ir_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	(dev_type_write((*))) enodev, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	seltrue, (dev_type_map((*))) enodev, 0 }

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

cdev_decl(vn);
/* open, read, write, ioctl -- XXX should be a disk */
#define	cdev_vn_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
	0 }

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
	cdev_vc_init(1,vc),		/* 0: virtual console */
	cdev_tty_init(NRS,rs),		/* 1: rs232c */
D 2
	cdev_notdef(),			/* 2: sy? */
E 2
I 2
	cdev_ctty_init(1,ctty),		/* 2: controlling terminal */
E 2
	cdev_mm_init(1,mm),		/* 3: /dev/{null,mem,kmem,...} */
	cdev_disk_init(NSD,sd_c_),	/* 4: scsi disk */
	cdev_disk_init(NFD,fd_c_),     	/* 5: floppy disk */
	cdev_disk_init(NLP,lp),		/* 6: printer */
	cdev_swap_init(1,sw),		/* 7: /dev/drum (swap pseudo-device) */
	cdev_tty_init(NPTY,pts),	/* 8: pseudo-tty slave */
	cdev_ptc_init(NPTY,ptc),	/* 9: pseudo-tty master */
	cdev_notdef(),			/* 10: md (sony memory disk) */
	cdev_kb_init(NKB,kb),		/* 11: keyboard */
	cdev_ms_init(NMS,ms),		/* 12: mouse */
D 2
#ifdef notdef
E 2
	cdev_fd_init(1,fd),		/* 13: file descriptor pseudo-dev */
D 2
#else
	cdev_notdef(),			/* 13 */
#endif
E 2
	cdev_fb_init(NFB,fb),		/* 14: frame buffer */
	cdev_vn_init(NVN,vn),		/* 15: vnode disk */
	cdev_tape_init(NST,st),		/* 16: scsi tape */
	cdev_kb_init(NLB,lbp),		/* 17: lbp */
	cdev_ir_init(NIR,ir),		/* 18: image reader */
	cdev_notdef(),			/* 19: vme */
	cdev_notdef(),			/* 20: gpib */
	cdev_notdef(),			/* 21: rd */
D 3
	cdev_tty_init(1,cn),		/* 22: console display device*/
E 3
I 3
	cdev_tty_init(NBM,cn),		/* 22: console display device */
E 3
	cdev_notdef(),			/* 23: ether */
	cdev_bpf_init(NBPFILTER,bpf),	/* 24: berkeley packet filter */
	cdev_notdef(),			/* 25 */
	cdev_notdef(),			/* 26 */
	cdev_notdef(),			/* 27 */
	cdev_notdef(),			/* 28: scsi */
	cdev_notdef(),			/* 29: sony shm */
	cdev_notdef(),			/* 30: sony semaphoe? */
	cdev_notdef(),			/* 31: vvcrs */
	cdev_notdef(),			/* 32: fddi */
	cdev_log_init(1,log),		/* 33: /dev/klog */
	cdev_notdef(),			/* 34: image board */
	cdev_notdef(),			/* 35: sb? */
	cdev_notdef(),			/* 36: sbe? */
	cdev_notdef(),			/* 37: vd (safs) */
	cdev_notdef(),			/* 38: xd (safs) */
	cdev_notdef(),			/* 39: isdn */
	cdev_notdef(),			/* 40: rb */
	cdev_notdef(),			/* 41: gs */
	cdev_notdef(),			/* 42: rx */
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
I 5

/*
 * Routine that identifies /dev/mem and /dev/kmem.
 *
 * A minimal stub routine can always return 0.
 */
iskmemdev(dev)
	dev_t dev;
{

	if (major(dev) == 3 && (minor(dev) == 0 || minor(dev) == 1))
		return (1);
	return (0);
}

I 7
iszerodev(dev)
	dev_t dev;
{
	return (major(dev) == 3 && minor(dev) == 12);
}

E 7
/*
I 8
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
	case 2:
	case 8:
	case 9:
	case 11:
		return (1);
	default:
		return (0);
	}
}

/*
E 8
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
	case 3:
		if (type == VBLK)
			return (1);
		return (0);
	case 4:
	case 15:
		if (type == VCHR)
			return (1);
		/* FALLTHROUGH */
	default:
		return (0);
	}
	/* NOTREACHED */
}

#define MAXDEV	43
static int chrtoblktbl[MAXDEV] =  {
      /* VCHR */      /* VBLK */
	/* 0 */		NODEV,
	/* 1 */		NODEV,
	/* 2 */		NODEV,
	/* 3 */		NODEV,
	/* 4 */		0,
	/* 5 */		NODEV,
	/* 6 */		NODEV,
	/* 7 */		NODEV,
	/* 8 */		NODEV,
	/* 9 */		NODEV,
	/* 10 */	NODEV,
	/* 11 */	NODEV,
	/* 12 */	NODEV,
	/* 13 */	NODEV,
	/* 14 */	NODEV,
	/* 15 */	3,
	/* 16 */	NODEV,
	/* 17 */	NODEV,
	/* 18 */	NODEV,
	/* 19 */	NODEV,
	/* 20 */	NODEV,
	/* 21 */	NODEV,
	/* 22 */	NODEV,
	/* 23 */	NODEV,
	/* 24 */	NODEV,
	/* 25 */	NODEV,
	/* 26 */	NODEV,
	/* 27 */	NODEV,
	/* 28 */	NODEV,
	/* 29 */	NODEV,
	/* 30 */	NODEV,
	/* 31 */	NODEV,
	/* 32 */	NODEV,
	/* 33 */	NODEV,
	/* 34 */	NODEV,
	/* 35 */	NODEV,
	/* 36 */	NODEV,
	/* 37 */	NODEV,
	/* 38 */	NODEV,
	/* 39 */	NODEV,
	/* 40 */	NODEV,
	/* 41 */	NODEV,
	/* 42 */	NODEV,
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
E 5
E 1
