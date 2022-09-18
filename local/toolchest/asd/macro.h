/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/*
 *	Miscellaneous Macro Definitions
 */

#define snum(X)   (((uint)(X) >> 17) & 0x7F)	/* byte addr to segment numb */
#define pnum(X)   (((uint)(X) >> 11) & 0x1FFF)	/* byte addr to virtual page */
#define poff(X)   ((uint)(X) & 0x7FF)		/* page offset */
#define soff(X)   ((uint)(X) & 0x1FFFF)		/* segment offset */

#define dtob(X)   ((X) << 9)			/* disk blocks to bytes */
#define btod(X)   (((X) + 0x1FF) >> 9)		/* bytes to disk blocks */
#define ptob(X)   ((X) << 11)			/* pages to bytes */
#define btop(X)   (((X) + 0x7FF) >> 11)		/* bytes to pages */
#define ptod(X)   ((X) << 2)			/* pages to disk blocks */
#define dtop(X)   (((X) + 0x3) >> 2)		/* disk blocks to pages */
#define ptos(X)   (((X) + 0x3F) >> 6)		/* pages to segments */
#define stob(X)   ((X) << 17)			/* segments to bytes */

#define major(x)  (int)((unsigned)x>>8)		/* major part of a device */
#define bmajor(x) (int)(((unsigned)x>>8)&037)	/* block device major */
#define brdev(x)  (x&0x1fff)			/* block device */

#define minor(x)  (int)(x&0377)			/* minor part of a device */
#define makedev(x,y)	(dev_t)(((x)<<8) | (y))	/* make a device number */

#define	usermode(ps)	(ps & PS_PSBR)		/* user mode psw */
#define critical(ps)	((ps & PS_EXL) != 0)	/* in a critical region */

#define lobyte(X) (((unsigned char *)&X)[0])
#define hibyte(X) (((unsigned char *)&X)[1])
#define loword(X) (((ushort *)&X)[0])
#define hiword(X) (((ushort *)&X)[1])

/* <@(#)macro.h	1.3> */
