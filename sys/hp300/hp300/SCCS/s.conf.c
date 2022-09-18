h52996
s 00003/00003/00376
d D 8.5 95/01/09 18:27:38 cgd 21 20
c strategy returns void, ioctl cmd arg is u_long
e
s 00012/00066/00367
d D 8.4 95/01/03 00:18:55 mckusick 20 19
c add types to devices (from mycroft)
e
s 00023/00000/00410
d D 8.3 94/11/21 15:16:36 mckusick 19 18
c add istty to identify vnodes that reference ttys in spec_open
e
s 00011/00005/00399
d D 8.2 93/11/14 13:32:00 hibler 18 17
c add iszerodev predicate
e
s 00002/00002/00402
d D 8.1 93/06/10 21:40:36 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00086/00000/00318
d D 7.16 93/04/28 19:22:07 mckusick 16 15
c add security routines iskmemdev, isdisk, and chrtoblk
e
s 00018/00004/00300
d D 7.15 92/12/27 09:45:18 hibler 15 14
c add [bc]dev_ldisk_init for disks with close routines (i.e. labels)
e
s 00007/00007/00297
d D 7.14 92/10/11 09:42:31 bostic 14 13
c make kernel includes standard
e
s 00001/00010/00303
d D 7.13 92/07/09 17:07:54 mckusick 13 12
c mmap'ed clocks are gone (at least for now)
e
s 00002/00002/00311
d D 7.12 92/06/05 15:36:52 hibler 12 11
c merge latest Utah hp300 code including 68040 support
e
s 00001/00001/00312
d D 7.11 92/03/01 15:25:05 mckusick 11 10
c rd disks depend on NRD not NSD (net2/sys/6)
e
s 00002/00001/00311
d D 7.10 92/02/15 18:14:57 mckusick 10 9
c need to include proc.h; dump routine currently takes no parameters
e
s 00005/00001/00307
d D 7.9 91/05/28 17:35:07 mckusick 9 8
c add entry for exabyte tape
e
s 00130/00132/00178
d D 7.8 91/05/10 10:43:45 karels 8 7
c reformatting; no two-space indents!
e
s 00252/00243/00058
d D 7.7 91/05/09 22:56:43 donn 7 6
c 99% rewritten from scratch to be compatible with prototypes.  Still needs
c drastic simplification, especially for cdevsw stuff.
e
s 00017/00009/00284
d D 7.6 91/05/07 10:03:25 hibler 6 5
c fd -> vn
e
s 00015/00000/00278
d D 7.5 91/03/19 18:25:44 mccanne 5 4
c add bpf
e
s 00148/00148/00130
d D 7.4 91/03/19 16:12:36 karels 4 3
c nodev split to enodev/enxio; rename /dev/tty; try to fix conflict
c with "fd"
e
s 00006/00006/00272
d D 7.3 90/12/16 16:36:00 bostic 3 2
c kernel reorg
e
s 00003/00002/00275
d D 7.2 90/12/05 18:53:32 mckusick 2 1
c update from Mike Hibler for new VM and other machine support
e
s 00277/00000/00000
d D 7.1 90/05/08 18:09:06 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
D 7
/*
 * Copyright (c) 1982, 1990 Regents of the University of California.
E 7
I 7
/*-
D 17
 * Copyright (c) 1991 The Regents of the University of California.
E 7
 * All rights reserved.
E 17
I 17
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 17
 *
 * %sccs.include.redist.c%
 *
D 7
 *	%W% (Berkeley) %G%
E 7
I 7
 *      %W% (Berkeley) %G%
E 7
 */

D 3
#include "param.h"
#include "systm.h"
#include "buf.h"
#include "ioctl.h"
#include "tty.h"
#include "conf.h"
E 3
I 3
D 14
#include "sys/param.h"
#include "sys/systm.h"
#include "sys/buf.h"
#include "sys/ioctl.h"
I 10
#include "sys/proc.h"
E 10
#include "sys/tty.h"
#include "sys/conf.h"
E 14
I 14
#include <sys/param.h>
#include <sys/systm.h>
#include <sys/buf.h>
#include <sys/ioctl.h>
#include <sys/proc.h>
I 16
#include <sys/vnode.h>
E 16
#include <sys/tty.h>
#include <sys/conf.h>
E 14
E 3

D 4
int	nulldev(), nodev(), rawread(), rawwrite(), swstrategy();
E 4
I 4
D 7
int	nullop(), enxio(), enodev(), rawread(), rawwrite(), swstrategy();
E 7
I 7
D 8
int	rawread __P((dev_t, struct uio *, int));
int	rawwrite __P((dev_t, struct uio *, int));
int	swstrategy __P((struct buf *));
int	ttselect __P((dev_t, int, struct proc *));
E 8
I 8
int	rawread		__P((dev_t, struct uio *, int));
int	rawwrite	__P((dev_t, struct uio *, int));
D 21
int	swstrategy	__P((struct buf *));
E 21
I 21
void	swstrategy	__P((struct buf *));
E 21
int	ttselect	__P((dev_t, int, struct proc *));
E 8
E 7
E 4

I 7
D 8
#define dev_type_open(n)	int n __P((dev_t, int, int, struct proc *))
#define dev_type_close(n)	int n __P((dev_t, int, int, struct proc *))
#define dev_type_strategy(n)	int n __P((struct buf *))
#define dev_type_ioctl(n) \
  int n __P((dev_t, int, caddr_t, int, struct proc *))
E 8
I 8
#define	dev_type_open(n)	int n __P((dev_t, int, int, struct proc *))
#define	dev_type_close(n)	int n __P((dev_t, int, int, struct proc *))
D 21
#define	dev_type_strategy(n)	int n __P((struct buf *))
E 21
I 21
#define	dev_type_strategy(n)	void n __P((struct buf *))
E 21
#define	dev_type_ioctl(n) \
D 21
	int n __P((dev_t, int, caddr_t, int, struct proc *))
E 21
I 21
	int n __P((dev_t, u_long, caddr_t, int, struct proc *))
E 21
E 8

/* bdevsw-specific types */
D 8
#define dev_type_dump(n)	int n __P((dev_t))
#define dev_type_size(n)	int n __P((dev_t))
E 8
I 8
D 10
#define	dev_type_dump(n)	int n __P((dev_t))
E 10
I 10
#define	dev_type_dump(n)	int n __P(())
E 10
#define	dev_type_size(n)	int n __P((dev_t))
E 8

D 8
#define	dev_decl(n,t) \
  __CONCAT(dev_type_,t)(__CONCAT(n,t))
E 8
I 8
#define	dev_decl(n,t)	__CONCAT(dev_type_,t)(__CONCAT(n,t))
E 8
#define	dev_init(c,n,t) \
D 8
  (c > 0 ? __CONCAT(n,t) : (__CONCAT(dev_type_,t)((*))) enxio)
E 8
I 8
	(c > 0 ? __CONCAT(n,t) : (__CONCAT(dev_type_,t)((*))) enxio)
E 8

/* bdevsw-specific initializations */
D 8
#define	dev_size_init(c,n) \
  (c > 0 ? __CONCAT(n,size) : 0)
E 8
I 8
#define	dev_size_init(c,n)	(c > 0 ? __CONCAT(n,size) : 0)
E 8

D 8
#define bdev_decl(n) \
  dev_decl(n,open); dev_decl(n,close); dev_decl(n,strategy); \
  dev_decl(n,ioctl); dev_decl(n,dump); dev_decl(n,size)
E 8
I 8
#define	bdev_decl(n) \
	dev_decl(n,open); dev_decl(n,close); dev_decl(n,strategy); \
	dev_decl(n,ioctl); dev_decl(n,dump); dev_decl(n,size)
E 8

I 15
/* disk without close routine */
E 15
D 8
#define bdev_disk_init(c,n) \
  { dev_init(c,n,open), (dev_type_close((*))) nullop, \
    dev_init(c,n,strategy), dev_init(c,n,ioctl), \
    dev_init(c,n,dump), dev_size_init(c,n), 0 }
E 8
I 8
#define	bdev_disk_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
	dev_init(c,n,dump), dev_size_init(c,n), 0 }
E 8

I 15
/* disk with close routine */
#define	bdev_ldisk_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
D 20
	dev_init(c,n,dump), dev_size_init(c,n), 0 }
E 20
I 20
	dev_init(c,n,dump), dev_size_init(c,n), D_DISK }
E 20

E 15
D 8
#define bdev_tape_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), \
    dev_init(c,n,strategy), dev_init(c,n,ioctl), \
    dev_init(c,n,dump), 0, B_TAPE }
E 8
I 8
#define	bdev_tape_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), \
	dev_init(c,n,strategy), dev_init(c,n,ioctl), \
D 20
	dev_init(c,n,dump), 0, B_TAPE }
E 20
I 20
	dev_init(c,n,dump), 0, D_TAPE }
E 20
E 8

D 8
#define	bdev_swap_init() \
  { (dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
    swstrategy, (dev_type_ioctl((*))) enodev, \
    (dev_type_dump((*))) enodev, 0, 0 }
E 8
I 8
#define	bdev_swap_init() { \
	(dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
	swstrategy, (dev_type_ioctl((*))) enodev, \
D 20
	(dev_type_dump((*))) enodev, 0, 0 }
E 20
I 20
	(dev_type_dump((*))) enodev, 0 }
E 20
E 8

D 8
#define bdev_notdef()	bdev_tape_init(0,no)
E 8
I 8
#define	bdev_notdef()	bdev_tape_init(0,no)
E 8
bdev_decl(no);	/* dummy declarations */

E 7
#include "ct.h"
I 9
#include "st.h"
E 9
D 7
#if NCT > 0
int	ctopen(),ctclose(),ctstrategy(),ctread(),ctwrite(),ctdump(),ctioctl();
#else
D 4
#define	ctopen		nodev
#define	ctclose		nodev
#define	ctstrategy	nodev
#define	ctread		nodev
#define	ctwrite		nodev
#define	ctdump		nodev
#define	ctioctl		nodev
E 4
I 4
#define	ctopen		enxio
#define	ctclose		enxio
#define	ctstrategy	enxio
#define	ctread		enxio
#define	ctwrite		enxio
#define	ctdump		enxio
#define	ctioctl		enxio
E 4
#endif
 
E 7
#include "rd.h"
D 7
#if NRD > 0
int	rdopen(),rdstrategy(),rdread(),rdwrite(),rddump(),rdioctl(),rdsize();
#else
D 4
#define	rdopen		nodev
#define	rdstrategy	nodev
#define	rdread		nodev
#define	rdwrite		nodev
#define	rddump		nodev
#define	rdioctl		nodev
E 4
I 4
#define	rdopen		enxio
#define	rdstrategy	enxio
#define	rdread		enxio
#define	rdwrite		enxio
#define	rddump		enxio
#define	rdioctl		enxio
E 4
#define	rdsize		0
#endif
 
E 7
#include "sd.h"
D 7
#if NSD > 0
int	sdopen(),sdstrategy(),sdread(),sdwrite(),sddump(),sdioctl(),sdsize();
#else
D 4
#define	sdopen		nodev
#define	sdstrategy	nodev
#define	sdread		nodev
#define	sdwrite		nodev
#define	sddump		nodev
#define	sdioctl		nodev
E 4
I 4
#define	sdopen		enxio
#define	sdstrategy	enxio
#define	sdread		enxio
#define	sdwrite		enxio
#define	sddump		enxio
#define	sdioctl		enxio
E 4
#define	sdsize		0
#endif
 
E 7
#include "cd.h"
D 7
#if NCD > 0
int	cdopen(),cdstrategy(),cdread(),cdwrite(),cddump(),cdioctl(),cdsize();
#else
D 4
#define	cdopen		nodev
#define	cdstrategy	nodev
#define	cdread		nodev
#define	cdwrite		nodev
#define	cddump		nodev
#define	cdioctl		nodev
E 4
I 4
#define	cdopen		enxio
#define	cdstrategy	enxio
#define	cdread		enxio
#define	cdwrite		enxio
#define	cddump		enxio
#define	cdioctl		enxio
E 4
#define	cdsize		0
#endif
 
E 7
I 6
#include "vn.h"
D 7
#if NVN > 0
int	vnopen(),vnstrategy(),vnread(),vnwrite(),vndump(),vnioctl(),vnsize();
#else
#define	vnopen		enxio
#define	vnstrategy	enxio
#define	vnread		enxio
#define	vnwrite		enxio
#define	vndump		enxio
#define	vnioctl		enxio
#define	vnsize		0
#endif
 
E 7
I 7

bdev_decl(ct);
I 9
bdev_decl(st);
E 9
bdev_decl(rd);
bdev_decl(sd);
bdev_decl(cd);
bdev_decl(vn);

E 7
E 6
D 4
#include "fd.h"
#if NFD > 0
int	fdopen(),fdstrategy(),fdread(),fdwrite(),fddump(),fdioctl(),fdsize();
#else
#define	fdopen		nodev
#define	fdstrategy	nodev
#define	fdread		nodev
#define	fdwrite		nodev
#define	fddump		nodev
#define	fdioctl		nodev
#define	fdsize		0
#endif

E 4
struct bdevsw	bdevsw[] =
{
D 7
	{ ctopen,	ctclose,	ctstrategy,	ctioctl,	/*0*/
	  ctdump,	0,		B_TAPE },
D 4
	{ nodev,	nodev,		nodev,		nodev,		/*1*/
	  nodev,	0,		0 },
	{ rdopen,	nulldev,	rdstrategy,	rdioctl,	/*2*/
E 4
I 4
	{ enxio,	enxio,		enxio,		enxio,		/*1*/
	  enxio,	0,		0 },
	{ rdopen,	nullop,		rdstrategy,	rdioctl,	/*2*/
E 4
	  rddump,	rdsize,		0 },
D 4
	{ nodev,	nodev,		swstrategy,	nodev,		/*3*/
	  nodev,	0,		0 },
	{ sdopen,	nulldev,	sdstrategy,	sdioctl,	/*4*/
E 4
I 4
	{ enodev,	enodev,		swstrategy,	enodev,		/*3*/
	  enodev,	0,		0 },
	{ sdopen,	nullop,		sdstrategy,	sdioctl,	/*4*/
E 4
	  sddump,	sdsize,		0 },
D 4
	{ cdopen,	nulldev,	cdstrategy,	cdioctl,	/*5*/
E 4
I 4
	{ cdopen,	nullop,		cdstrategy,	cdioctl,	/*5*/
E 4
	  cddump,	cdsize,		0 },
D 4
	{ fdopen,	nulldev,	fdstrategy,	fdioctl,	/*6*/
	  fddump,	fdsize,		0 },
E 4
I 4
D 6
	/* 6 was "fd" vnode device */
E 6
I 6
	{ vnopen,	nullop,		vnstrategy,	vnioctl,	/*6*/
	  vndump,	vnsize,		0 },
E 7
I 7
	bdev_tape_init(NCT,ct),	/* 0: cs80 cartridge tape */
	bdev_notdef(),		/* 1 */
D 15
	bdev_disk_init(NRD,rd),	/* 2: hpib disk */
E 15
I 15
	bdev_ldisk_init(NRD,rd),/* 2: hpib disk */
E 15
	bdev_swap_init(),	/* 3: swap pseudo-device */
D 15
	bdev_disk_init(NSD,sd),	/* 4: scsi disk */
E 15
I 15
	bdev_ldisk_init(NSD,sd),/* 4: scsi disk */
E 15
	bdev_disk_init(NCD,cd),	/* 5: concatenated disk driver */
	bdev_disk_init(NVN,vn),	/* 6: vnode disk driver (swap to files) */
I 9
	bdev_tape_init(NST,st),	/* 7: exabyte tape */
E 9
E 7
E 6
E 4
};
I 7

E 7
int	nblkdev = sizeof (bdevsw) / sizeof (bdevsw[0]);

D 4
int	cnopen(),cnclose(),cnread(),cnwrite(),cnioctl(),cnselect();
E 4
I 4
D 7
int	cnopen(), cnclose(), cnread(),  cnwrite(), cnioctl(), cnselect();
E 7
I 7
/* cdevsw-specific types */
D 8
#define dev_type_read(n)	int n __P((dev_t, struct uio *, int))
#define dev_type_write(n)	int n __P((dev_t, struct uio *, int))
#define dev_type_stop(n)	int n __P((struct tty *, int))
#define dev_type_reset(n)	int n __P((int))
E 8
I 8
#define	dev_type_read(n)	int n __P((dev_t, struct uio *, int))
#define	dev_type_write(n)	int n __P((dev_t, struct uio *, int))
#define	dev_type_stop(n)	int n __P((struct tty *, int))
#define	dev_type_reset(n)	int n __P((int))
E 8
#define	dev_type_select(n)	int n __P((dev_t, int, struct proc *))
#define	dev_type_map(n)	int n __P(())
E 7
E 4

D 4
int	syopen(),syread(),sywrite(),syioctl(),syselect();
E 4
I 4
D 7
int	cttyopen(), cttyread(), cttywrite(), cttyioctl(), cttyselect();
E 7
I 7
D 8
#define cdev_decl(n) \
  dev_decl(n,open); dev_decl(n,close); dev_decl(n,read); \
  dev_decl(n,write); dev_decl(n,ioctl); dev_decl(n,stop); \
  dev_decl(n,reset); dev_decl(n,select); dev_decl(n,map); \
  dev_decl(n,strategy); extern struct tty __CONCAT(n,_tty)[]
E 8
I 8
#define	cdev_decl(n) \
	dev_decl(n,open); dev_decl(n,close); dev_decl(n,read); \
	dev_decl(n,write); dev_decl(n,ioctl); dev_decl(n,stop); \
	dev_decl(n,reset); dev_decl(n,select); dev_decl(n,map); \
	dev_decl(n,strategy); extern struct tty __CONCAT(n,_tty)[]
E 8
E 7
E 4

D 7
int 	mmrw();
#define	mmselect	seltrue
E 7
I 7
#define	dev_tty_init(c,n)	(c > 0 ? __CONCAT(n,_tty) : 0)
E 7

I 7
/* open, read, write, ioctl, strategy */
D 8
#define	cdev_disk_init(c,n) \
  { dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
    dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
    (dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
    dev_init(c,n,strategy) }
E 8
I 8
#define	cdev_disk_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
D 20
	dev_init(c,n,strategy) }
E 20
I 20
	dev_init(c,n,strategy), D_DISK }
E 20
E 8

/* open, close, read, write, ioctl, strategy */
I 15
#define	cdev_ldisk_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
D 20
	dev_init(c,n,strategy) }
E 20
I 20
	dev_init(c,n,strategy), D_TAPE }
E 20

/* open, close, read, write, ioctl, strategy */
E 15
D 8
#define	cdev_tape_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
    dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
    (dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
    dev_init(c,n,strategy) }
E 8
I 8
#define	cdev_tape_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
	dev_init(c,n,strategy) }
E 8

/* open, close, read, write, ioctl, stop, tty */
D 8
#define	cdev_tty_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
    dev_init(c,n,write), dev_init(c,n,ioctl), dev_init(c,n,stop), \
    (dev_type_reset((*))) nullop, dev_tty_init(c,n), ttselect, \
    (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_tty_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), dev_init(c,n,stop), \
	(dev_type_reset((*))) nullop, dev_tty_init(c,n), ttselect, \
D 20
	(dev_type_map((*))) enodev, 0 }
E 20
I 20
	(dev_type_map((*))) enodev, 0, D_TTY }
E 20
E 8

D 8
#define cdev_notdef() \
  { (dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
    (dev_type_read((*))) enodev, (dev_type_write((*))) enodev, \
    (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
    (dev_type_reset((*))) nullop, 0, seltrue, \
    (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_notdef() { \
	(dev_type_open((*))) enodev, (dev_type_close((*))) enodev, \
	(dev_type_read((*))) enodev, (dev_type_write((*))) enodev, \
	(dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, \
	(dev_type_map((*))) enodev, 0 }
E 8

cdev_decl(no);			/* dummy declarations */

cdev_decl(cn);
/* open, close, read, write, ioctl, select -- XXX should be a tty */
D 8
#define	cdev_cn_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
    dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
    (dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
    (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_cn_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
D 20
	(dev_type_map((*))) enodev, 0 }
E 20
I 20
	(dev_type_map((*))) enodev, 0, D_TTY }
E 20
E 8

cdev_decl(ctty);
/* open, read, write, ioctl, select -- XXX should be a tty */
D 8
#define	cdev_ctty_init(c,n) \
  { dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
    dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
    (dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
    (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_ctty_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, 0, dev_init(c,n,select), \
D 20
	(dev_type_map((*))) enodev, 0 }
E 20
I 20
	(dev_type_map((*))) enodev, 0, D_TTY }
E 20
E 8

dev_type_read(mmrw);
D 18
/* read/write */
E 18
I 18
dev_type_map(mmmap);
/* read, write, mmap */
E 18
D 8
#define	cdev_mm_init(c,n) \
  { (dev_type_open((*))) nullop, (dev_type_close((*))) nullop, mmrw, \
    mmrw, (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) nullop, \
    (dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_mm_init(c,n) { \
	(dev_type_open((*))) nullop, (dev_type_close((*))) nullop, mmrw, \
	mmrw, (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) nullop, \
D 18
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, 0 }
E 18
I 18
	(dev_type_reset((*))) nullop, 0, seltrue, mmmap, 0 }
E 18
E 8

/* read, write, strategy */
D 8
#define	cdev_swap_init(c,n) \
  { (dev_type_open((*))) nullop, (dev_type_close((*))) nullop, rawread, \
    rawwrite, (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
    (dev_type_reset((*))) nullop, 0, (dev_type_select((*))) enodev, \
    (dev_type_map((*))) enodev, dev_init(c,n,strategy) }
E 8
I 8
#define	cdev_swap_init(c,n) { \
	(dev_type_open((*))) nullop, (dev_type_close((*))) nullop, rawread, \
	rawwrite, (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, (dev_type_select((*))) enodev, \
	(dev_type_map((*))) enodev, dev_init(c,n,strategy) }
E 8

E 7
#include "pty.h"
D 7
#if NPTY > 0
int	ptsopen(),ptsclose(),ptsread(),ptswrite(),ptsstop();
int	ptcopen(),ptcclose(),ptcread(),ptcwrite(),ptcselect();
int	ptyioctl();
struct	tty pt_tty[];
#else
D 4
#define ptsopen		nodev
#define ptsclose	nodev
#define ptsread		nodev
#define ptswrite	nodev
#define ptcopen		nodev
#define ptcclose	nodev
#define ptcread		nodev
#define ptcwrite	nodev
#define ptyioctl	nodev
E 4
I 4
#define ptsopen		enxio
#define ptsclose	enxio
#define ptsread		enxio
#define ptswrite	enxio
#define ptcopen		enxio
#define ptcclose	enxio
#define ptcread		enxio
#define ptcwrite	enxio
#define ptyioctl	enxio
E 4
#define	pt_tty		0
D 4
#define	ptcselect	nodev
#define	ptsstop		nulldev
E 4
I 4
#define	ptcselect	enxio
#define	ptsstop		nullop
E 4
#endif
E 7
I 7
#define	pts_tty		pt_tty
#define	ptsioctl	ptyioctl
cdev_decl(pts);
#define	ptc_tty		pt_tty
#define	ptcioctl	ptyioctl
cdev_decl(ptc);
E 7

I 7
/* open, close, read, write, ioctl, tty, select */
D 8
#define	cdev_ptc_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
    dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
    (dev_type_reset((*))) nullop, dev_tty_init(c,n), dev_init(c,n,select), \
    (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_ptc_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
	(dev_type_reset((*))) nullop, dev_tty_init(c,n), dev_init(c,n,select), \
D 20
	(dev_type_map((*))) enodev, 0 }
E 20
I 20
	(dev_type_map((*))) enodev, 0, D_TTY }
E 20
E 8

cdev_decl(log);
/* open, close, read, ioctl, select -- XXX should be a generic device */
D 8
#define	cdev_log_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
    (dev_type_write((*))) enodev, dev_init(c,n,ioctl), \
    (dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
    dev_init(c,n,select), (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_log_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	(dev_type_write((*))) enodev, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	dev_init(c,n,select), (dev_type_map((*))) enodev, 0 }
E 8

cdev_decl(ct);
I 9
cdev_decl(st);
E 9
cdev_decl(sd);
cdev_decl(rd);

D 12
/* XXX shouldn't this be optional? */
E 12
I 12
#include "grf.h"
E 12
cdev_decl(grf);
/* open, close, ioctl, select, map -- XXX should be a map device */
D 8
#define	cdev_grf_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), (dev_type_read((*))) nullop, \
    (dev_type_write((*))) nullop, dev_init(c,n,ioctl), \
    (dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
    dev_init(c,n,select), dev_init(c,n,map), 0 }
E 8
I 8
#define	cdev_grf_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), (dev_type_read((*))) nullop, \
	(dev_type_write((*))) nullop, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	dev_init(c,n,select), dev_init(c,n,map), 0 }
E 8

E 7
#include "ppi.h"
D 7
#if NPPI > 0
D 2
int	ppiopen(),ppiclose(),ppiread(),ppiwrite();
E 2
I 2
int	ppiopen(),ppiclose(),ppiread(),ppiwrite(),ppiioctl();
E 2
#else
D 4
#define ppiopen		nodev
#define ppiclose	nodev
#define ppiread		nodev
#define ppiwrite	nodev
I 2
#define ppiioctl	nodev
E 4
I 4
#define ppiopen		enxio
#define ppiclose	enxio
#define ppiread		enxio
#define ppiwrite	enxio
#define ppiioctl	enxio
E 4
E 2
#endif
E 7
I 7
cdev_decl(ppi);
/* open, close, read, write, ioctl -- XXX should be a generic device */
D 8
#define	cdev_ppi_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
    dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
    (dev_type_reset((*))) nullop, 0, (dev_type_select((*))) enodev, \
    (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_ppi_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
D 20
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
E 20
I 20
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) nullop, \
E 20
	(dev_type_reset((*))) nullop, 0, (dev_type_select((*))) enodev, \
	(dev_type_map((*))) enodev, 0 }
E 8
E 7

I 7
#include "dca.h"
cdev_decl(dca);

E 7
#include "ite.h"
D 7
#if NITE > 0
int	iteopen(),iteclose(),iteread(),itewrite(),iteioctl();
struct	tty ite_tty[];
#else
D 4
#define iteopen		nodev
#define iteclose	nodev
#define iteread		nodev
#define itewrite	nodev
#define itestop		nulldev
#define iteioctl	nodev
E 4
I 4
#define iteopen		enxio
#define iteclose	enxio
#define iteread		enxio
#define itewrite	enxio
#define itestop		nullop
#define iteioctl	enxio
E 4
#define ite_tty		0
#endif
E 7
I 7
cdev_decl(ite);
/* open, close, read, write, ioctl, tty -- XXX should be a tty! */
D 8
#define	cdev_ite_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
    dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
    (dev_type_reset((*))) nullop, dev_tty_init(c,n), ttselect, \
    (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_ite_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, dev_tty_init(c,n), ttselect, \
D 20
	(dev_type_map((*))) enodev, 0 }
E 20
I 20
	(dev_type_map((*))) enodev, 0, D_TTY }
E 20
E 8
E 7

D 7
#include "dca.h"
#if NDCA > 0
int	dcaopen(),dcaclose(),dcaread(),dcawrite(),dcastop(),dcaioctl();
struct	tty dca_tty[];
#else
D 4
#define dcaopen		nodev
#define dcaclose	nodev
#define dcaread		nodev
#define dcawrite	nodev
#define dcastop		nulldev
#define dcaioctl	nodev
E 4
I 4
#define dcaopen		enxio
#define dcaclose	enxio
#define dcaread		enxio
#define dcawrite	enxio
#define dcastop		nullop
#define dcaioctl	enxio
E 4
#define dca_tty		0
#endif
E 7
I 7
/* XXX shouldn't this be optional? */
cdev_decl(hil);
/* open, close, read, ioctl, select, map -- XXX should be a map device */
D 8
#define	cdev_hil_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
    (dev_type_write((*))) nullop, dev_init(c,n,ioctl), \
    (dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
    dev_init(c,n,select), dev_init(c,n,map), 0 }
E 8
I 8
#define	cdev_hil_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	(dev_type_write((*))) nullop, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	dev_init(c,n,select), dev_init(c,n,map), 0 }
E 8
E 7

#include "dcm.h"
D 7
#if NDCM > 0
int	dcmopen(),dcmclose(),dcmread(),dcmwrite(),dcmstop(),dcmioctl();
struct	tty dcm_tty[];
#else
D 4
#define dcmopen		nodev
#define dcmclose	nodev
#define dcmread		nodev
#define dcmwrite	nodev
#define dcmstop		nulldev
#define dcmioctl	nodev
E 4
I 4
#define dcmopen		enxio
#define dcmclose	enxio
#define dcmread		enxio
#define dcmwrite	enxio
#define dcmstop		nullop
#define dcmioctl	enxio
E 4
#define dcm_tty		0
#endif
E 7
I 7
cdev_decl(dcm);
E 7

I 7
cdev_decl(cd);

E 7
D 13
#include "clock.h"
D 7
#if NCLOCK > 0
int	clockopen(),clockclose(),clockioctl(),clockmap();
#else
D 4
#define clockopen	nodev
#define clockclose	nodev
#define clockioctl	nodev
#define clockmap	nodev
E 4
I 4
#define clockopen	enxio
#define clockclose	enxio
#define clockioctl	enxio
#define clockmap	enxio
E 4
#endif
E 7
I 7
cdev_decl(clock);
/* open, close, ioctl, map -- XXX should be a map device */
D 8
#define	cdev_clock_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), (dev_type_read((*))) nullop, \
    (dev_type_write((*))) nullop, dev_init(c,n,ioctl), \
    (dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
    (dev_type_select((*))) nullop, dev_init(c,n,map), 0 }
E 8
I 8
#define	cdev_clock_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), (dev_type_read((*))) nullop, \
	(dev_type_write((*))) nullop, dev_init(c,n,ioctl), \
	(dev_type_stop((*))) enodev, (dev_type_reset((*))) nullop, 0, \
	(dev_type_select((*))) nullop, dev_init(c,n,map), 0 }
E 8
E 7

E 13
I 5
D 7
#include "bpfilter.h"
#if NBPFILTER > 0
int	bpfopen(),bpfclose(),bpfread(),bpfwrite(),bpfioctl(),bpfselect();
#else
#define bpfopen		enxio
#define bpfclose	enxio
#define bpfread		enxio
#define bpfwrite	enxio
#define bpfioctl	enxio
#define bpfselect	enxio
#endif
E 7
I 7
cdev_decl(vn);
/* open, read, write, ioctl -- XXX should be a disk */
D 8
#define	cdev_vn_init(c,n) \
  { dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
    dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
    (dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
    0 }
E 8
I 8
#define	cdev_vn_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) nullop, dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) nullop, 0, seltrue, (dev_type_map((*))) enodev, \
D 20
	0 }
E 20
I 20
	(dev_type_strategy((*))) nullop, D_DISK }
E 20
E 8
E 7

E 5
D 7
int	logopen(),logclose(),logread(),logioctl(),logselect();
E 7
I 7
dev_type_open(fdopen);
/* open */
D 8
#define	cdev_fd_init(c,n) \
  { dev_init(c,n,open), (dev_type_close((*))) enodev, \
    (dev_type_read((*))) enodev, (dev_type_write((*))) enodev, \
    (dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
    (dev_type_reset((*))) enodev, 0, (dev_type_select((*))) enodev, \
    (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_fd_init(c,n) { \
	dev_init(c,n,open), (dev_type_close((*))) enodev, \
	(dev_type_read((*))) enodev, (dev_type_write((*))) enodev, \
	(dev_type_ioctl((*))) enodev, (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) enodev, 0, (dev_type_select((*))) enodev, \
	(dev_type_map((*))) enodev, 0 }
E 8
E 7

I 4
D 7
int	fdopen();
E 7
I 7
#include "bpfilter.h"
cdev_decl(bpf);
/* open, close, read, write, ioctl, select -- XXX should be generic device */
D 8
#define	cdev_bpf_init(c,n) \
  { dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
    dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
    (dev_type_reset((*))) enodev, 0, dev_init(c,n,select), \
    (dev_type_map((*))) enodev, 0 }
E 8
I 8
#define	cdev_bpf_init(c,n) { \
	dev_init(c,n,open), dev_init(c,n,close), dev_init(c,n,read), \
	dev_init(c,n,write), dev_init(c,n,ioctl), (dev_type_stop((*))) enodev, \
	(dev_type_reset((*))) enodev, 0, dev_init(c,n,select), \
	(dev_type_map((*))) enodev, 0 }
E 8
E 7

E 4
D 7
int	ttselect(), seltrue();

int	grfopen(),grfclose(),grfioctl(),grfselect(),grfmap();

int	hilopen(),hilclose(),hilioctl(),hilmap(),hilselect(),hilread();

E 7
struct cdevsw	cdevsw[] =
{
D 4
	cnopen,		cnclose,	cnread,		cnwrite,	/*0*/
	cnioctl,	nulldev,	nulldev,	NULL,
	cnselect,	nodev,		NULL,
	syopen,		nulldev,	syread,		sywrite,	/*1*/
	syioctl,	nulldev,	nulldev,	NULL,
	syselect,	nodev,		NULL,
	nulldev,	nulldev,	mmrw,		mmrw,		/*2*/
	nodev,		nulldev,	nulldev,	NULL,
	mmselect,	nodev,		NULL,
	nulldev,	nulldev,	rawread,	rawwrite,	/*3*/
	nodev,		nodev,		nulldev,	NULL,
	nodev,		nodev,		swstrategy,
	ptsopen,	ptsclose,	ptsread,	ptswrite,	/*4*/
	ptyioctl,	ptsstop,	nulldev,	pt_tty,
	ttselect,	nodev,		NULL,
	ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*5*/
	ptyioctl,	nulldev,	nulldev,	pt_tty,
	ptcselect,	nodev,		NULL,
	logopen,	logclose,	logread,	nodev,		/*6*/
	logioctl,	nodev,		nulldev,	NULL,
	logselect,	nodev,		NULL,
	ctopen,		ctclose,	ctread,		ctwrite,	/*7*/
	ctioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		ctstrategy,
	sdopen,		nulldev,	sdread,		sdwrite,	/*8*/
	sdioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		sdstrategy,
	rdopen,		nulldev,	rdread,		rdwrite,	/*9*/
	rdioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		rdstrategy,
	grfopen,	grfclose,	nulldev,	nulldev,	/*10*/
	grfioctl,	nodev,		nulldev,	NULL,
	grfselect,	grfmap,		NULL,
	ppiopen,	ppiclose,	ppiread,	ppiwrite,	/*11*/
D 2
	nodev,		nodev,		nulldev,	NULL,
E 2
I 2
	ppiioctl,	nodev,		nulldev,	NULL,
E 2
	nodev,		nodev,		NULL,
	dcaopen,	dcaclose,	dcaread,	dcawrite,	/*12*/
	dcaioctl,	dcastop,	nulldev,	dca_tty,
	ttselect,	nodev,		NULL,
	iteopen,	iteclose,	iteread,	itewrite,	/*13*/
	iteioctl,	nodev,		nulldev,	ite_tty,
	ttselect,	nodev,		NULL,
	hilopen,	hilclose,	hilread,	nulldev,	/*14*/
	hilioctl,	nodev,		nulldev,	NULL,
	hilselect,	hilmap,		NULL,
	dcmopen,	dcmclose,	dcmread,	dcmwrite,	/*15*/
	dcmioctl,	dcmstop,	nulldev,	dcm_tty,
	ttselect,	nodev,		NULL,
	nodev,		nodev,		nodev,		nodev,		/*16*/
	nodev,		nodev,		nulldev,	NULL,
	seltrue,	nodev,		NULL,
	cdopen,		nulldev,	cdread,		cdwrite,	/*17*/
	cdioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		cdstrategy,
	clockopen,	clockclose,	nulldev,	nulldev,	/*18*/
	clockioctl,	nodev,		nulldev,	NULL,
	nulldev,	clockmap,	NULL,
	fdopen,		nulldev,	fdread,		fdwrite,	/*19*/
	fdioctl,	nodev,		nulldev,	NULL,
	seltrue,	nodev,		NULL,
E 4
I 4
D 7
	{ cnopen,	cnclose,	cnread,		cnwrite,	/*0*/
	  cnioctl,	nullop,		nullop,		NULL,
	  cnselect,	enodev,		NULL },
	{ cttyopen,	nullop,		cttyread,	cttywrite,	/*1*/
	  cttyioctl,	nullop,		nullop,		NULL,
	  cttyselect,	enodev,		NULL },
	{ nullop,	nullop,		mmrw,		mmrw,		/*2*/
	  enodev,	nullop,		nullop,		NULL,
	  mmselect,	enodev,		NULL },
	{ nullop,	nullop,		rawread,	rawwrite,	/*3*/
	  enodev,	enodev,		nullop,		NULL,
	  enodev,	enodev,		swstrategy },
	{ ptsopen,	ptsclose,	ptsread,	ptswrite,	/*4*/
	  ptyioctl,	ptsstop,	nullop,		pt_tty,
	  ttselect,	enodev,		NULL },
	{ ptcopen,	ptcclose,	ptcread,	ptcwrite,	/*5*/
	  ptyioctl,	nullop,		nullop,		pt_tty,
	  ptcselect,	enodev,		NULL },
	{ logopen,	logclose,	logread,	enodev,		/*6*/
	  logioctl,	enodev,		nullop,		NULL,
	  logselect,	enodev,		NULL },
	{ ctopen,	ctclose,	ctread,		ctwrite,	/*7*/
	  ctioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		ctstrategy },
	{ sdopen,	nullop,		sdread,		sdwrite,	/*8*/
	  sdioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		sdstrategy },
	{ rdopen,	nullop,		rdread,		rdwrite,	/*9*/
	  rdioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		rdstrategy },
	{ grfopen,	grfclose,	nullop,		nullop,		/*10*/
	  grfioctl,	enodev,		nullop,		NULL,
	  grfselect,	grfmap,		NULL },
	{ ppiopen,	ppiclose,	ppiread,	ppiwrite,	/*11*/
	  ppiioctl,	enodev,		nullop,		NULL,
	  enodev,	enodev,		NULL },
	{ dcaopen,	dcaclose,	dcaread,	dcawrite,	/*12*/
	  dcaioctl,	dcastop,	nullop,		dca_tty,
	  ttselect,	enodev,		NULL },
	{ iteopen,	iteclose,	iteread,	itewrite,	/*13*/
	  iteioctl,	enodev,		nullop,		ite_tty,
	  ttselect,	enodev,		NULL },
	{ hilopen,	hilclose,	hilread,	nullop,		/*14*/
	  hilioctl,	enodev,		nullop,		NULL,
	  hilselect,	hilmap,		NULL },
	{ dcmopen,	dcmclose,	dcmread,	dcmwrite,	/*15*/
	  dcmioctl,	dcmstop,	nullop,		dcm_tty,
	  ttselect,	enodev,		NULL },
	{ enodev,	enodev,		enodev,		enodev,		/*16*/
	  enodev,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		NULL },
	{ cdopen,	nullop,		cdread,		cdwrite,	/*17*/
	  cdioctl,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		cdstrategy },
	{ clockopen,	clockclose,	nullop,		nullop,		/*18*/
	  clockioctl,	enodev,		nullop,		NULL,
	  nullop,	clockmap,	NULL },
D 6
#ifdef notdef
	{ fdopen,	nullop,		fdread,		fdwrite,	/*19*/
	  fdioctl,	enodev,		nullop,		NULL,
E 6
I 6
	{ vnopen,	nullop,		vnread,		vnwrite,	/*19*/
	  vnioctl,	enodev,		nullop,		NULL,
E 6
	  seltrue,	enodev,		NULL },
D 6
#else
	{ enodev,	enodev,		enodev,		enodev,		/*19*/
	  enodev,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		NULL },
#endif
E 6
	{ enodev,	enodev,		enodev,		enodev,		/*20*/
	  enodev,	enodev,		nullop,		NULL,
	  seltrue,	enodev,		NULL },
	{ fdopen,	enodev,		enodev,		enodev,		/*21*/
	  enodev,	enodev,		enodev,		NULL,
	  enodev,	enodev,		NULL },
I 5
	{ bpfopen,	bpfclose,	bpfread,	bpfwrite,	/*22*/
	  bpfioctl,	enodev,		enodev,		NULL,
	  bpfselect,	enodev,		NULL },
E 7
I 7
	cdev_cn_init(1,cn),		/* 0: virtual console */
	cdev_ctty_init(1,ctty),		/* 1: controlling terminal */
	cdev_mm_init(1,mm),		/* 2: /dev/{null,mem,kmem,...} */
	cdev_swap_init(1,sw),		/* 3: /dev/drum (swap pseudo-device) */
	cdev_tty_init(NPTY,pts),	/* 4: pseudo-tty slave */
	cdev_ptc_init(NPTY,ptc),	/* 5: pseudo-tty master */
	cdev_log_init(1,log),		/* 6: /dev/klog */
	cdev_tape_init(NCT,ct),		/* 7: cs80 cartridge tape */
D 15
	cdev_disk_init(NSD,sd),		/* 8: scsi disk */
D 11
	cdev_disk_init(NSD,rd),		/* 9: hpib disk */
E 11
I 11
	cdev_disk_init(NRD,rd),		/* 9: hpib disk */
E 15
I 15
	cdev_ldisk_init(NSD,sd),	/* 8: scsi disk */
	cdev_ldisk_init(NRD,rd),	/* 9: hpib disk */
E 15
E 11
D 12
	cdev_grf_init(1,grf),		/* 10: frame buffer */
E 12
I 12
	cdev_grf_init(NGRF,grf),	/* 10: frame buffer */
E 12
	cdev_ppi_init(NPPI,ppi),	/* 11: printer/plotter interface */
	cdev_tty_init(NDCA,dca),	/* 12: built-in single-port serial */
	cdev_ite_init(NITE,ite),	/* 13: console terminal emulator */
	cdev_hil_init(1,hil),		/* 14: human interface loop */
	cdev_tty_init(NDCM,dcm),	/* 15: 4-port serial */
	cdev_notdef(),			/* 16 */
	cdev_disk_init(NCD,cd),		/* 17: concatenated disk */
D 13
	cdev_clock_init(NCLOCK,clock),	/* 18: mapped clock */
E 13
I 13
	cdev_notdef(),			/* 18 */
E 13
	cdev_vn_init(NVN,vn),		/* 19: vnode disk */
D 9
	cdev_notdef(),			/* 20 */
E 9
I 9
	cdev_tape_init(NST,st),		/* 20: exabyte tape */
E 9
	cdev_fd_init(1,fd),		/* 21: file descriptor pseudo-dev */
	cdev_bpf_init(NBPFILTER,bpf),	/* 22: berkeley packet filter */
E 7
E 5
E 4
};
I 7

E 7
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
I 16

/*
 * Routine that identifies /dev/mem and /dev/kmem.
 *
 * A minimal stub routine can always return 0.
 */
iskmemdev(dev)
	dev_t dev;
{

D 18
	if (major(dev) == 2 && (minor(dev) == 0 || minor(dev) == 1))
		return (1);
	return (0);
E 18
I 18
	return (major(dev) == 2 && minor(dev) < 2);
}

iszerodev(dev)
	dev_t dev;
{

	return (major(dev) == 2 && minor(dev) == 12);
E 18
D 20
}

/*
I 19
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
	case 15:
		return (1);
	default:
		return (0);
	}
}

/*
E 19
 * Routine to determine if a device is a disk.
 *
 * A minimal stub routine can always return 0.
 */
isdisk(dev, type)
	dev_t dev;
	int type;
{

	switch (major(dev)) {
	case 2:
	case 4:
	case 5:
	case 6:
		if (type == VBLK)
			return (1);
		return (0);
	case 8:
	case 9:
	case 17:
	case 19:
		if (type == VCHR)
			return (1);
		/* fall through */
	default:
		return (0);
	}
	/* NOTREACHED */
E 20
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
	/* 7 */		0,
	/* 8 */		4,
	/* 9 */		2,
	/* 10 */	NODEV,
	/* 11 */	NODEV,
	/* 12 */	NODEV,
	/* 13 */	NODEV,
	/* 14 */	NODEV,
	/* 15 */	NODEV,
	/* 16 */	NODEV,
	/* 17 */	5,
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
E 16
E 1
