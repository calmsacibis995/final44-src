/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	xycom.h,v $
 * Revision 2.5  92/02/04  21:18:31  mja
 * 	Picked up changes from SunOS 4.1.1 for use with Sun4.
 * 	[92/02/02  19:31:51  berman]
 * 
 * Revision 2.4  90/07/03  16:49:42  mrt
 * 	Merged mt Xinu 2.6MSD Changes.
 * 	[90/05/17  18:16:18  mrt]
 * 
 * Revision 2.3  89/03/09  21:49:52  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:59:30  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)xycom.h 1.1 86/09/25 SMI	*/

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */
#ifndef	XYCOM_H_
#define XYCOM_H_

/*
 * Common definitions for Xylogics disk drivers.  Names are prefixed
 * with 'xy', but these definitions also apply to the xd driver.
 */

/*
 * States for the command block flags
 */
#define	XY_FBSY		0x0001		/* cmdblock in use */
#define	XY_FRDY		0x0002		/* cmdblock ready for execution */
#define	XY_DONE		0x0004		/* operation completed */
#define	XY_FAILED	0x0008		/* command failed */
#define	XY_WANTED	0x0010		/* process waiting for iopb */
#define	XY_WAIT		0x0020		/* process waiting for completion */
#define	XY_INFRD	0x0040		/* in bad block forwarding */
#define	XY_INRST	0x0080		/* in a restore */
#define	XY_FNLRST	0x0100		/* in final restore (cmd failed) */
#define	XY_NOMSG	0x0200		/* suppress error messages */
#define	XY_DIAG		0x0400		/* diagnostic mode */
#define	XY_NOCHN	0x0800		/* don't chain this command */
#define	XY_INWCHK	0x8000		/* command in write-check */

/*
 * States for the ctlr structure flags
 */
#define	XY_C_PRESENT	0x01		/* ctlr exists */
#define	XY_C_24BIT	0x02		/* 24 bit addressing mode */
#define	XY_C_NOCHN	0x04		/* no chaining of iopbs */

/*
 * States for the unit structure flags
 */
#define	XY_UN_PRESENT	0x01		/* unit is online */
#define	XY_UN_ATTACHED	0x02		/* unit has been attached */


/*
 * Write Check defines
 */

#define	XY_REWRITE_MAX	5		/*
					 * how many times to attempt to
					 * rewrite blocks that didn't
					 * verify correctly.
					 */
/*
 * Modes to execute a command
 */
#define XY_SYNCH	0		/* synchronous */
#define XY_ASYNCH	1		/* interrupt, no wait on iopb */
#define XY_ASYNCHWAIT	2		/* interrupt, wait on iopb */

/*
 * Error message control -- if a given bit is set, those errors are
 * printed. All others are suppressed.
 */
#define EL_FORWARD	0x0001		/* block forwarding message */
#define EL_FIXED	0x0002		/* fixed error message */
#define EL_RETRY	0x0004		/* retry message */
#define EL_RESTR	0x0008		/* restore message */
#define EL_RESET	0x0010		/* reset message */
#define EL_FAIL		0x0020		/* failure message */

/*
 * The classes of errors.
 */
#define XY_SUCC		0x00		/* success -- no error */
#define XY_ERCOR	0x01		/* corrected error */
#define XY_ERTRY	0x02		/* retryable error */
#define XY_ERBSY	0x03		/* drive busy error */
#define XY_ERFLT	0x04		/* drive faulted error */
#define XY_ERHNG	0x05		/* controller hung error */
#define XY_ERFTL	0x06		/* fatal error */

/*
 * Struct for defining actions to be taken for each class of error.
 */
struct xyerract {
	u_char	retry;		/* number of retries */
	u_char	restore;	/* number of drive resets */
	u_char	reset;		/* number of controller resets */
};

/*
 * Struct for defining each recognizable error.
 * Because of the sparse population, an array is not used.
 */
struct xyerror {
	u_char	errno;		/* error number */
	u_char	errlevel;	/* error level (corrected, fatal, etc) */
	u_char	errtype;	/* error type (media vs nonmedia) */
	char	*errmsg;	/* error message */
};

/*
 * Miscellaneous defines.
 */
#define b_cylin b_resid			/* used for disksort */
#define XYNUNIT		32		/* max # of units on system */
#define XYNLPART	MAXPARTITIONS	/* # of logical partitions (8) */
#define	UNITSHIFT	3
#define UNIT(dev)	((dev >> UNITSHIFT) % XYNUNIT)
#define LPART(dev)	(dev % XYNLPART)
#define	MINOR(u, p)	(((u) << UNITSHIFT) | (p))
#define NOLPART		(-1)		/* used for 'non-partition commands */
#define SECSIZE		512
#define XYWATCHTIMO	20		/* seconds till disk check */
#define XYLOSTINTTIMO	4		/* seconds till lost interrupt */
#define	XY_IN		0		/* command reads data */
#define	XY_OUT		1		/* command writes data */
#define XYDEFTRKLEN	24		/* length of manufacturer's defect */

/*
 * Structure definition and macros for manufacturer's list.
 */
#define	XY_MANDEFSIZE	24

struct xydefinfo {
	u_char	info[XY_MANDEFSIZE];
};

#define	XY_MAN_SYNC(x)		(x[0])
#define	XY_MAN_CYL(x)		(((x[1] & 0x7f) << 8) + x[2])
#define	XY_MAN_HEAD(x)		(x[3])
#define	XY_MAN_BFI(x, y)	((x[5 + 4 * y] << 8) + x[6 + 4 * y])
#define	XY_MAN_LEN(x, y)	((x[7 + 4 * y] << 8) + x[8 + 4 * y])
#define	XY_MAN_LAST(x)		(x[21])

#define	XY_TRK_BAD(x)		(x[1] & 0x80)

#define	XY_SYNCBYTE		0x19
#define	XY_LASTBYTE		0xf0

#define	XY_MAN_CYL_HI(x)	(x[1])
#define	XY_MAN_CYL_LO(x)	(x[2])
#define	XY_MAN_ZERO(x)		(x[4])
#define	XY_MAN_WR_BFI(x, y, z)	x[5 + 4*y] = z>>8; x[6 + 4*y] = z;
#define	XY_MAN_WR_LEN(x, y, z)	x[7 + 4*y] = z>>8; x[8 + 4*y] = z;
#define	XY_MAN_MRK_TRK_BAD(x)	x[1] |= 0x80
#define	XY_MAN_DEFECT_BEGIN	10
#define	XY_MAN_DEFECT_END	55


/*
 * Macros for sector headers that don't hold data.
 */
#define	XY_HDR_SPARE	0xdddddddd		/* header for spare sector */
#define	XY_HDR_RUNT	0xeeeeeeee		/* header for runt sector */
#define	XY_HDR_SLIP	0xfefefefe		/* header for slipped sector */
#define	XY_HDR_ZAP	0xffffffff		/* header for zapped sector */

#endif	XYCOM_H_
