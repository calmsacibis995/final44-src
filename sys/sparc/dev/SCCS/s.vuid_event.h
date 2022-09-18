h28320
s 00002/00002/00057
d D 8.1 93/06/11 15:08:33 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00057
d D 7.3 93/04/20 05:51:53 torek 3 2
c spelling
e
s 00005/00000/00054
d D 7.2 92/07/21 16:38:01 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00054/00000/00000
d D 7.1 92/07/13 00:41:31 torek 1 0
c date and time created 92/07/13 00:41:31 by torek
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
I 2
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
D 3
 *	California, Lawrence Berkeley Laboratories.
E 3
I 3
 *	California, Lawrence Berkeley Laboratory.
E 3
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: vuid_event.h,v 1.3 92/06/17 05:35:51 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: vuid_event.h,v 1.4 92/11/26 01:20:27 torek Exp $ (LBL)
E 3
 */

/*
 * The following is a minimal emulation of Sun's `Firm_event' structures
 * and related operations necessary to make X11 happy (i.e., make it
 * compile, and make old X11 binaries run).
 */
typedef struct firm_event {
	u_short	id;		/* key or MS_* or LOC_[XY]_DELTA */
	u_short	pad;		/* unused, at least by X11 */
	int	value;		/* VKEY_{UP,DOWN} or locator delta */
	struct	timeval time;
} Firm_event;

/*
 * Special `id' fields.  These weird numbers simply match the old binaries.
 * Others are in 0..0x7f and are keyboard key numbers (keyboard dependent!).
 */
#define	MS_LEFT		0x7f20	/* left mouse button */
#define	MS_MIDDLE	0x7f21	/* middle mouse button */
#define	MS_RIGHT	0x7f22	/* right mouse button */
#define	LOC_X_DELTA	0x7f80	/* mouse delta-X */
#define	LOC_Y_DELTA	0x7f81	/* mouse delta-Y */

/*
 * Special `value' fields.  These apply to keys and mouse buttons.  The
 * value of a mouse delta is the delta.  Note that positive deltas are
 * left and up (not left and down as you might expect).
 */
#define	VKEY_UP		0	/* key or button went up */
#define	VKEY_DOWN	1	/* key or button went down */

/*
 * The following ioctls are clearly intended to take things in and out
 * of `firm event' mode.  Since we always run in this mode (as far as
 * /dev/kbd and /dev/mouse are concerned, anyway), we always claim to
 * be in this mode and reject anything else.
 */
#define	VUIDSFORMAT	_IOW('v', 1, int)
#define	VUIDGFORMAT	_IOR('v', 2, int)
#define	VUID_FIRM_EVENT	1	/* the only format we support */
E 1
