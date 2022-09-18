h43800
s 00002/00002/00043
d D 8.1 93/06/10 21:20:42 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00044
d D 5.3 93/02/01 11:20:04 torek 3 2
c rcsid
e
s 00005/00000/00040
d D 5.2 92/07/23 14:00:49 torek 2 1
c /sys/scsi moves to /sys/dev/scsi; add LBL acknowledgement requirement
e
s 00040/00000/00000
d D 5.1 92/07/10 00:03:06 torek 1 0
c date and time created 92/07/10 00:03:06 by torek
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
 *	California, Lawrence Berkeley Laboratories.
 *
E 2
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
D 3
 * from: $Header: scsi_ioctl.h,v 1.2 92/05/15 11:24:02 torek Exp $ (LBL)
E 3
I 3
 * from: $Header: scsi_ioctl.h,v 1.3 92/12/02 03:54:19 torek Exp $ (LBL)
E 3
 */

/*
 * SCSI ioctls (`format' mode).
 *
 * Format mode allows a privileged process to issue direct SCSI commands
 * to a drive (it is intended primarily to allow on-line formatting).
 * SDIOCSFORMAT sets format mode (nonzero arg => on, zero arg => off).
 * When in format mode, only the process that issued the SDIOCSFORMAT
 * can read or write the drive.
 *
 * In format mode, the process is expected to
 *	- do SDIOCSCSICOMMAND to supply cdb for next SCSI op
 *	- do read or write as appropriate for cdb
 *	- if I/O error, optionally do SDIOCSENSE to get completion
 *	  status and sense data from last SCSI operation.
 */

struct scsi_fmt_sense {
	u_int	status;		/* completion status of last op */
	u_char	sense[28];	/* sense data (if any) from last op */
};

#define	SDIOCSFORMAT		_IOW('S', 1, int)
#define	SDIOCGFORMAT		_IOR('S', 2, int)
#define	SDIOCSCSICOMMAND	_IOW('S', 3, struct scsi_cdb)
#define	SDIOCSENSE		_IOR('S', 4, struct scsi_fmt_sense)
E 1
