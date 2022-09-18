h36957
s 00002/00002/00051
d D 8.1 93/06/10 21:47:58 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00053/00000/00000
d D 7.1 90/05/08 22:45:58 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * vohldr.h: volume header for "LIF" format volumes
 */

struct	lifvol {
	short	vol_id;
	char	vol_label[6];
	int	vol_addr;
	short	vol_oct;
	short	vol_dummy;
	int	vol_dirsize;
	short	vol_version;
	short	vol_zero;
	int	vol_huh1;
	int	vol_huh2;
	int	vol_length;
};

struct	lifdir {
	char	dir_name[10];
	short	dir_type;
	int	dir_addr;
	int	dir_length;
	char	dir_toc[6];
	short	dir_flag;
	int	dir_exec;
};

/* load header for boot rom */
struct load {
	int address;
	int count;
};

#define VOL_ID		-32768
#define VOL_OCT		4096
#define	DIR_TYPE	-5822
#define DIR_FLAG	0x8001	/* dont ask me! */
#define	SECTSIZE	256
E 1
