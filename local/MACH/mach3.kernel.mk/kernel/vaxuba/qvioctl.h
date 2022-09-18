/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	qvioctl.h,v $
 * Revision 2.2  91/03/16  15:04:17  rpd
 * 	Fixed ioctl definitions for ANSI C.
 * 	[91/02/20            rpd]
 * 
 * Revision 2.1  89/08/03  16:42:08  rwd
 * Created.
 * 
 * Revision 2.3  89/02/26  11:07:20  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/24  03:08:35  mwyoung
 * 	Corrected include file references.
 * 	[88/08/22  19:08:17  mwyoung]
 * 
 *  5-Dec-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	Declare the background color for corsor invert.
 *
 * 19-Jun-85  Avadis Tevanian (avie) at Carnegie-Mellon University
 *	Added hacks for reverse video printing on screen and fancy (!)
 *	led handling on keyboard.
 *
 */

/*
 *	@(#)qvioctl.h	1.7 (ULTRIX) 4/24/85
 * Ioctl definitions for the qvss.
 *
 */

#include <vaxuba/qevent.h>
#include <sys/ioctl.h>
#include <vaxuba/qvreg.h>

struct qv_kpcmd {
	char nbytes;		/* number of bytes in parameter */
	unsigned char cmd;	/* command to be sent, peripheral bit will */
				/* be forced by driver */
	unsigned char par[2];	/* bytes of parameters to be sent */
};
/*
 * qvss information block
 */

#ifdef	MACH
struct cursor_icon {
	short data[16];
};

#endif	MACH
struct qv_info {
	short	mswitches;		/* current value of mouse buttons */
	vsCursor tablet;		/* current tablet position	*/
	short	tswitches;		/* current tablet buttons NI!	*/
	vsCursor cursor;		/* current cursor position	*/
	short	row;			/* screen row			*/
	short	col;			/* screen col			*/
	short	max_row;		/* max character row		*/
	short	max_col;		/* max character col		*/
	short	max_x;			/* max x position		*/
	short	max_y;			/* max y position		*/
	short	max_cur_x;		/* max cursor y position 	*/
	short	max_cur_y;		/* max cursor y position	*/
	char	*bitmap;		/* bit map position		*/
	short	*scanmap;		/* scanline map position	*/
	short	*cursorbits;		/* cursor bit position		*/
	struct	qvdevice *qvaddr;	/* virtual address of the csr	*/
	vsEvent *ibuff;			/* pointer to event queue	*/
	int 	iqsize;			/* may assume power of two 	*/
	int 	ihead;			/* atomic write			*/
	int 	itail;			/* atomic read			*/
	vsCursor mouse;			/* atomic read/write		*/
	vsBox	mbox;			/* atomic read/write		*/
	short	mthreshold;		/* mouse motion parameter	*/
	short	mscale;			/* mouse scale factor (if 
					   negative, then do square).	*/
#ifdef	MACH
	struct  cursor_icon cursor_icon;/* actual data for "on" cursor  */
	short	char_invert;		/* invert character display	*/
#endif	MACH
};
typedef struct qv_info vsIoAddr;

#define QIOCGINFO 	_IOR('q', 1, struct qv_info)	/* get the info	 */
#define QIOCSMSTATE	_IOW('q', 2, vsCursor)		/* set mouse pos */
#define QIOCINIT	_IO('q', 4)			/* init screen   */
#define QIOCKPCMD	_IOW('q', 5, struct qv_kpcmd)	/* keybd. per. cmd */
#define QIOCADDR	_IOR('q', 6, struct qv_info *)	/* get address */

#ifdef	MACH
#define QIOCLIGHT	_IOW('q', 111, int)		/* light interval */
#define QIOCMOUSE	_IOW('q', 112, int)		/* mouse interval */
#define QIOCREVERSE	_IOW('q', 113, int)		/* reverse video */
#define QIOCFADE	_IOW('q', 114, int)		/* fade screen */
#define QIOCCURSOR	_IOW('q', 115, int)		/* new cursor */
#define QIOCCURSORON	_IOW('q', 116, int)		/* cursor blink rate */
#define QIOCCURSOROFF	_IOW('q', 117, int)		/* cursor blink rate */
#define QIOCCURSORICON	_IOW('q', 118, struct cursor_icon)	/* new cursor */
#define QIOCLEDPATTERN	_IOW('q', 119, int)		/* cylon, ... */
#define QIOCLEDINTERVAL	_IOW('q', 120, int)		/* refresh interval */
#define LED_OFF		0				/* no led movement */
#define LED_COUNT	1				/* led counter */
#define LED_ROTATE	2				/* led rotate */
#define LED_CYLON	3				/* led cylon mode */
#define QIOCSETUP	_IOW('q', 121, int)		/* do a setup */
#define	QV100		100
#define	QV260		260
#endif	MACH
