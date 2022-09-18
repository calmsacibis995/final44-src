h28938
s 00002/00002/00033
d D 8.1 93/06/10 21:21:31 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00008/00027
d D 7.3 91/05/07 09:46:10 hibler 3 2
c fd -> vn
e
s 00001/00001/00034
d D 7.2 90/11/04 19:22:49 mckusick 2 1
c update identifier from Utah
e
s 00035/00000/00000
d D 7.1 90/05/08 22:06:36 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 4
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: fdioctl.h 1.1 89/11/20$
E 2
I 2
 * from: Utah $Hdr: fdioctl.h 1.1 90/07/09$
E 2
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Ioctl definitions for file (vnode) disk pseudo-device.
 */

#define FDISKFILE	"/etc/fdisks"	/* default config file */

D 3
struct fd_ioctl {
	char	*fd_file;	/* pathname of file to mount */
	int	fd_size;	/* (returned) size of disk */
E 3
I 3
struct vn_ioctl {
	char	*vn_file;	/* pathname of file to mount */
	int	vn_size;	/* (returned) size of disk */
E 3
};

/*
D 3
 * Before you can use a unit, it must be configured with FDIOCSET.
E 3
I 3
 * Before you can use a unit, it must be configured with VNIOCSET.
E 3
 * The configuration persists across opens and closes of the device;
D 3
 * an FDIOCCLR must be used to reset a configuration.  An attempt to
 * FDIOCSET an already active unit will return EBUSY.
E 3
I 3
 * an VNIOCCLR must be used to reset a configuration.  An attempt to
 * VNIOCSET an already active unit will return EBUSY.
E 3
 */
D 3
#define FDIOCSET	_IOWR('F', 0, struct fd_ioctl)	/* enable disk */
#define FDIOCCLR	_IOW('F', 1, struct fd_ioctl)	/* disable disk */
E 3
I 3
#define VNIOCSET	_IOWR('F', 0, struct vn_ioctl)	/* enable disk */
#define VNIOCCLR	_IOW('F', 1, struct vn_ioctl)	/* disable disk */
E 3
E 1
