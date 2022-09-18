/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	pr_util.h,v $
 * Revision 2.4  89/03/09  20:57:35  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:12:51  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)pr_util.h 1.3 87/01/08 SMI	*/

/*
 * Copyright (c) 1983, 1986 by Sun Microsystems, Inc.
 */

#ifndef	PR_UTIL_H_
#define PR_UTIL_H_

/*
 * Utilities for implementing pixrect operations.
 */

/*
 * Aids to handling overlapping source and destination.
 * Given the from and to pr_pos's, rop_direction tells
 * whether the rasterop is up or down and left or right,
 * encoded as the ROP_UP and ROP_LEFT bits or their absence.
 * The macros rop_is(up|down|left|right) can then be used.
 */
#define ROP_UP		0x1
#define ROP_LEFT	0x2

#define rop_direction(src, so, dst, do)	\
	    (   ( (((dst).x+(do).x) < ((src).x+(so).x)) << 1) | \
	          (((dst).y+(do).y) < ((src).y+(so).y))      )
#define rop_isleft(dir)		((dir)&ROP_LEFT)
#define rop_isup(dir)		((dir)&ROP_UP)
#define rop_isright(dir)	(((dir)&ROP_LEFT)==0)
#define rop_isdown(dir)		(((dir)&ROP_UP)==0)

/*
 * Aids to producing fast loops, either unrolled or very tight:
 *
 * Cases8(n, op) produces the dense case part of a case statement
 * for the cases [n+1..n+8), repeating ``op'' 1-8 times respectively.
 *
 * Rop_slowloop(n, op) produces a loop to do ``op'' n times, in little space.
 * 
 * Rop_fastloop(n, op) produces a loop to do ``op'' n times, in little time.
 *
 * Loop_d6(label, op) produces a dbra loop to do ``op'' the number of times
 * in register d6 (second non-pointer register variable).
 *
 * Loop_d6 is only possible on a 68000 family processor, and rop_fastloop
 * generates an unrolled loop only on a 68010 (assumes other processors 
 * will have some kind of I-cache).
 */
#ifdef	mc68000
/* generates a nice dbra loop */
#define rop_slowloop(n, op) \
	{ register int _loop = (n); \
		if (--_loop >= 0) do { op; } while (--_loop != -1); }

#define loopd6(label, op)						\
	if (0) {							\
		asm("label:");						\
		op;							\
	};								\
	asm("dbra	d6,label");
#else	mc68000
#define rop_slowloop(n, op) \
	{ register int _loop = (n); \
		while (--_loop >= 0) { op; } }
#endif	mc68000

#ifdef	mc68010
#define cases8(n, op)							\
	    case (n)+8: op; case (n)+7: op; case (n)+6: op;		\
	    case (n)+5: op; case (n)+4: op; case (n)+3: op;		\
	    case (n)+2: op; case (n)+1: op;				\

#define rop_fastloop(n, op) \
	{ register int _loop ; \
		for (_loop = (n); _loop > 15; _loop -= 16) \
	    		{ op; op; op; op; op; op; op; op; \
	      		  op; op; op; op; op; op; op; op; } \
	  	switch (_loop) { \
			cases8(8, op); \
			cases8(0, op); \
			case 0:	break; \
		} }
#else	mc68010
#define rop_fastloop	rop_slowloop
#endif	mc68010

/*
 * Alloctype(datatype) allocates a datatype structure using calloc
 * with the appropriate type cast.
 */
#define alloctype(datatype)						\
	    (datatype *)calloc(1, sizeof (datatype))

/*
 * Pr_product is used when doing multiplications involving pixrects,
 * and casts its arguments to that the compiler will use 16 by 16 multiplies.
 */
#ifdef	sun
#define pr_product(a, b)	((short)(a) * (short)(b))
#else
#define pr_product(a, b)	((a) * (b))
#endif

/*
 * Pr_area is the area of a rectangle.
 */
#define pr_area(size) pr_product((size).x, (size).y)

/*
 * Pr_devdata is used to keep track of the valloced/mmapped virtual
 * address of a device to prevent doing it more than necessary.
 */
struct pr_devdata {
	int	fd;	/* fd that pixrect owns and is expected to close */
	int	count;	/* reference count of this device */
	short	*va; 	/* valloced/mmapped virtual address managing */
	int	bytes;	/* size of va for use when unvalloc unmap */
	dev_t	rdev;	/* the device type, fd independent id of device */
	struct	pr_devdata *next;	/* Link to other similar devices */
};

#ifndef	KERNEL
struct	pixrect *pr_makefromfd();
#endif	!KERNEL

#ifdef	cplus
struct	pixrect *pr_makefromfd(int fd, struct pr_size size, int depth,
	    struct pr_devdata **devdata, struct pr_devdata **curdd,
	    int mmapbytes, privdatabytes, mmapoffsetbytes);
void	pr_unmakefromfd(int fd, struct pr_devdata **devdata);
#endif	cplus

#endif	PR_UTIL_H_
