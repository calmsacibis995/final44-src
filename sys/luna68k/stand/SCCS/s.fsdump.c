h04127
s 00002/00002/00239
d D 8.1 93/06/10 22:29:17 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00000/00239
d D 7.3 93/02/10 15:50:32 akito 3 2
c add "tailor" option
e
s 00011/00007/00228
d D 7.2 93/02/09 18:17:36 akito 2 1
c added some partition for dump
e
s 00235/00000/00000
d D 7.1 92/12/13 03:50:12 akito 1 0
c date and time created 92/12/13 03:50:12 by akito
e
u
U
t
T
I 1
/*
 * Copyright (c) 1992 OMRON Corporation.
D 4
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * OMRON Corporation.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * fsdump.c -- dump and restore of File System
 * by A.Fujita, APR-26-1992
 */

#include <sys/param.h>
#include <sys/stat.h>
#define DKTYPENAMES
#include <sys/disklabel.h>
#include <luna68k/stand/status.h>
#include <luna68k/stand/omron_disklabel.h>

#define LABEL_SIZE 512

#define BUF_BLOCK	(20 * 12 * 38)			/* 20 Cylinder */
#define BUF_BYTES	BUF_BLOCK << DEV_BSHIFT

static u_char index[LABEL_SIZE];

struct disklabel *lp  = (struct disklabel *)((struct scd_dk_label *) index)->dkl_pad;

extern dev_t  rst0;
extern dev_t nrst0;

static u_char *dump_buf = (u_char *) 0x100000;

I 2
extern int scsi_device;
char cons_buf[100];
E 2

I 2

E 2
int
fsdump(argc, argv)
	int   argc;
	char *argv[];
{
	register int i, j, io;
	register char *p;
	register int status;
	register int block, bytes;
	int scsi_id, blk, nblks, size, mark;
	struct stat boot_stat;
	struct	partition *pp;
I 2
	scsi_id = scsi_device;
E 2

D 2
	scsi_id = 6;
E 2
I 2
	printf("Current SCSI device = ID %d\n", scsi_id);
	getline("Is it sure ? (y/n) ", cons_buf);

	if ((cons_buf[0] != 'y') && (cons_buf[0] != 'Y'))
		return(ST_ERROR);

E 2
	scsi_read_raw(scsi_id, 0, 1, index, LABEL_SIZE);

	for (i = 0; i < MAXPARTITIONS; i++) {
		pp = &(lp->d_partitions[i]);
D 2
/*
E 2
		if ((i != 0) &&
I 2
		    (i != 3) &&
E 2
		    (i != 4) &&
		    (i != 5)) {
D 2
 */
		if (i != 0) {
E 2
			pp->p_size = 0;
		}
I 3
		if (i == 5 && argc > 1 && !strcmp(argv[1], "tailor"))
			pp->p_size = 0;
E 3
	}

	st_rewind(rst0);

	printf("Boot Program		");
	io = open("sd(0,0)boot", 0);
	if (io >= 0) {
		printf("read ... ");
		size = read(io, dump_buf, 1048576);
		close(io);
		printf("%d bytes ... ", size);
		if (size <= 0) {
			printf("failed\n");
			return(ST_ERROR);
		}
		boot_stat.st_size = size;
	}

	printf("write ... ");
	status = stwrite(rst0, dump_buf, size);
	st_write_EOF(rst0);

	if (status < size) {
		printf("failed\n");
		return(ST_ERROR);
	}

	printf("done\n");

	printf("disklabel (index)\t");

	printf("write ... ");
	status = stwrite(rst0, index, LABEL_SIZE);
	st_write_EOF(rst0);

	if (status < LABEL_SIZE) {
		printf("failed\n");
		return(ST_ERROR);
	}

	printf("done\n\n");

	for (i = 0; i < MAXPARTITIONS; i++) {
		pp = &(lp->d_partitions[i]);
		if (pp->p_size > 0) {
			printf("%c: ", i + 'A');
			printf("size = %d(0x%s), ", pp->p_size, hexstr(pp->p_size, 8));
			printf("offset = %d(0x%s)\n", pp->p_offset, hexstr(pp->p_offset, 8));
			
			blk   = pp->p_offset;
			nblks = pp->p_size;
			size  = nblks << DEV_BSHIFT;

			block = BUF_BLOCK;
			bytes = BUF_BYTES;

			mark = nblks / block;
			if (nblks % block)
				mark++;
			for (j = 0; j < mark; j++)
				printf("-");
			for (j = 0; j < mark; j++)
				printf("%c", '\x08');

			while (nblks > 0) {
				if (nblks < block) {
					block = nblks;
					bytes = nblks << DEV_BSHIFT;
				}

				if (!scsi_read_raw(scsi_id, blk, block, dump_buf, bytes)) {
					printf("disk read failed !!!\n");
					return(ST_ERROR);
				}

				if (stwrite(rst0, dump_buf, bytes) < bytes) {
					printf("tape write failed !!!\n");
					return(ST_ERROR);
				}

				blk   += block;
				nblks -= block;
				size  -= bytes;

				printf("#");
			}

			st_write_EOF(rst0);
			printf("\n\n");
		}
	}
}
D 2

extern int scsi_device;
char cons_buf[100];
E 2

int
fsrestore(argc, argv)
	int   argc;
	char *argv[];
{
	register int i, j, status;
	register int block, bytes;
	int blk, nblks, size, mark;
	struct	partition *pp;

	printf("Current SCSI device = ID %d\n", scsi_device);
	getline("Is it sure ? (y/n) ", cons_buf);

	if ((cons_buf[0] != 'y') && (cons_buf[0] != 'Y'))
		return(ST_ERROR);

	st_rewind(rst0);

	st_skip(rst0);

	status = stread(rst0, index, LABEL_SIZE);

	st_skip(rst0);

	for (i = 0; i < MAXPARTITIONS; i++) {
		pp = &(lp->d_partitions[i]);
		if (pp->p_size > 0) {
			printf("%c: ", i + 'A');
			printf("size = %d(0x%s), ", pp->p_size, hexstr(pp->p_size, 8));
			printf("offset = %d(0x%s)\n", pp->p_offset, hexstr(pp->p_offset, 8));
			
			blk   = pp->p_offset;
			nblks = pp->p_size;
			size  = nblks << DEV_BSHIFT;

			block = BUF_BLOCK;
			bytes = BUF_BYTES;

			mark = nblks / block;
			if (nblks % block)
				mark++;
			for (j = 0; j < mark; j++)
				printf("-");
			for (j = 0; j < mark; j++)
				printf("%c", '\x08');

			while (nblks > 0) {
				if (nblks < block) {
					block = nblks;
					bytes = nblks << DEV_BSHIFT;
				}

				if (stread(rst0, dump_buf, bytes) != bytes) {
					printf("tape read failed !!!\n");
					return(ST_ERROR);
				}

				if (!scsi_write(blk, dump_buf, bytes)) {
					printf("disk write failed !!!\n");
					return(ST_ERROR);
				}

				blk   += block;
				nblks -= block;
				size  -= bytes;

				printf("#");
			}
			st_skip(rst0);
			printf("\n\n");
		}
	}
}
E 1
