h21004
s 00002/00002/00062
d D 8.1 93/06/10 23:31:24 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00064/00000/00000
d D 7.1 93/05/09 18:09:59 ralph 1 0
c date and time created 93/05/09 18:09:59 by ralph
e
u
U
t
T
I 1
/*-
D 2
 * Copyright (c) 1993 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <sys/disklabel.h>

#include <pmax/stand/dec_boot.h>

struct	disklabel label;
struct	Dec_DiskLabel dec_label;

/*
 * This program creates or updates the DEC label after 'disklabel'
 * has initialized the Berkeley disk label.
 * This program may be useful in sharing ULTRIX disks with 4.4 BSD but it
 * hasn't been tested much. Use at your own risk. 
 *
 * Usage: dec_label <disk>
 */

main(argc, argv)
	int argc;
	char *argv[];
{
	register int i;
	int fd;

	if (argc != 2) {
		fprintf(stderr, "Usage: dec_label <disk>\n");
		exit(1);
	}
	if ((fd = open(argv[1], O_RDWR, 0)) < 0)
		err(1, "%s", argv[1]);
	if (ioctl(fd, DIOCGDINFO, &label) < 0)
		err(1, "ioctl DIOCGDINFO");

	/* fill in DEC label */
	dec_label.magic = DEC_LABEL_MAGIC;
	dec_label.isPartitioned = 1;
	for (i = 0; i < DEC_NUM_DISK_PARTS; i++) {
		dec_label.map[i].numBlocks = label.d_partitions[i].p_size;
		dec_label.map[i].startBlock = label.d_partitions[i].p_offset;
		printf("%d: start %d size %d\n", i, dec_label.map[i].startBlock,
			dec_label.map[i].numBlocks);
	}
	if (lseek(fd, (off_t)DEC_LABEL_SECTOR * label.d_secsize, SEEK_SET) == -1)
		err(1, "lseek");
	if (write(fd, &dec_label, sizeof(dec_label)) != sizeof(dec_label))
		err(1, "write label");
	return (0);
}
E 1
