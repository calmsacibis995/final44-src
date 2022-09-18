h48796
s 00002/00002/00058
d D 8.1 93/06/11 15:08:27 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/00058
d D 7.3 93/04/20 05:51:51 torek 3 2
c spelling
e
s 00005/00000/00055
d D 7.2 92/07/21 16:38:00 bostic 2 1
c update the contribution notice; LBL requires acknowledgement
e
s 00055/00000/00000
d D 7.1 92/07/13 00:41:30 torek 1 0
c date and time created 92/07/13 00:41:30 by torek
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
 * from: $Header: kbio.h,v 1.3 92/06/17 05:35:49 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: kbio.h,v 1.4 92/11/26 01:16:32 torek Exp $ (LBL)
E 3
 */

/*
 * The following is a minimal emulation of Sun's `kio' structures
 * and related operations necessary to make X11 happy (i.e., make it
 * compile, and make old X11 binaries run).
 */

/*
 * The kiockey structure apparently gets and/or sets keyboard mappings.
 * It seems to be kind of useless, but X11 uses it (according to the
 * comments) to figure out when a Sun 386i has a type-4 keyboard but
 * claims to have a type-3 keyboard.  We need just enough to cause the
 * appropriate ioctl to return the appropriate magic value.
 *
 * KIOCGETKEY fills in kio_entry from kio_station.  Not sure what tablemask
 * is for; X sets it before the call, so it is not an output, but we do not
 * care anyway.  KIOCSDIRECT is supposed to tell the kernel whether to send
 * keys to the console or to X; we just send them to X whenever the keyboard
 * is open at all.  (XXX may need to change this later)
 *
 * Keyboard commands and types are defined in kbd.h as they are actually
 * real hardware commands and type numbers.
 */
struct kiockey {
	int	kio_tablemask;	/* whatever */
	u_char	kio_station;	/* key number */
	u_char	kio_entry;	/* HOLE if not present */
	char	kio_text[10];	/* the silly escape sequences (unsupported) */
};

#define	HOLE	0x302		/* value for kio_entry to say `really type 3' */

#define	KIOCTRANS	_IOW('k', 0, int)	/* set translation mode */
			/* (we only accept TR_UNTRANS_EVENT) */
#define	KIOCGETKEY	_IOWR('k', 2, struct kiockey) /* fill in kio_entry */
#define	KIOCGTRANS	_IOR('k', 5, int)	/* get translation mode */
#define	KIOCCMD		_IOW('k', 8, int)	/* X uses this to ring bell */
#define	KIOCTYPE	_IOR('k', 9, int)	/* get keyboard type */
#define	KIOCSDIRECT	_IOW('k', 10, int)	/* keys to console? */

#define	TR_UNTRANS_EVENT	3
E 1
