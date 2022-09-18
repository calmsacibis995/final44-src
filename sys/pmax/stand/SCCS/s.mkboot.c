h51553
s 00005/00005/00169
d D 8.1 93/06/10 23:31:30 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00009/00165
d D 7.6 93/02/15 11:22:38 ralph 6 5
c use old DS3100 style entry point for SCSI disk I/O
e
s 00006/00013/00168
d D 7.5 92/10/24 14:30:35 ralph 5 4
c changed to allow any size boot program (i.e., more than 15 sectors).
e
s 00004/00004/00177
d D 7.4 92/10/11 11:28:16 bostic 4 3
c make kernel includes standard
e
s 00040/00033/00141
d D 7.3 92/04/19 09:08:05 ralph 3 2
c changed for disklabel support.
e
s 00004/00005/00170
d D 7.2 92/03/07 10:00:12 ralph 2 1
c fixes for ds5000
e
s 00175/00000/00000
d D 7.1 92/01/07 20:45:20 mckusick 1 0
c contributed by Ralph Campbell
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1992 Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
D 7
char copyright[] =
"%Z% Copyright (c) 1992 Regents of the University of California.\n\
 All rights reserved.\n";
E 7
I 7
static char copyright[] =
"%Z% Copyright (c) 1992, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 7
#endif not lint

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif not lint

I 4
#include <sys/param.h>
#include <sys/exec.h>
#include <sys/disklabel.h>
E 4
#include <stdio.h>
D 2
#include "types.h"
#include "exec.h"
#include "../include/param.h"
E 2
I 2
D 3
#include "sys/param.h"
#include "sys/exec.h"
E 2
#include "../dev/devDiskLabel.h"
E 3
I 3
D 4
#include "param.h"
#include "exec.h"
#include "disklabel.h"
E 4
E 3

I 3
D 4
#include "dec_boot.h"
E 4
I 4
#include <pmax/stand/dec_boot.h>
E 4

E 3
D 5
/* this is the size of the standard ULTRIX boot */
#define MAXBOOTSIZE (15 * DEV_BSIZE)

E 5
I 3
struct	Dec_DiskBoot decBootInfo;
E 3
char	block[DEV_BSIZE];
D 3
char	*dev, *bootfname;
E 3
I 3
char	*bootfname, *xxboot, *bootxx;
E 3

/*
D 3
 * installboot bootprog device
E 3
I 3
 * This program takes a boot program and splits it into xxboot and bootxx
 * files for the disklabel program. The disklabel program should be used to
 * label and install the boot program onto a new disk.
 *
 * mkboot bootprog xxboot bootxx
E 3
 */
main(argc, argv)
	int argc;
	char *argv[];
{
	register int i, n;
D 3
	int ifd, ofd;
	Dec_DiskBoot decBootInfo;
E 3
I 3
	int ifd, ofd1, ofd2;
E 3
	int nsectors;
	long loadAddr;
	long execAddr;
	long length;

D 3
	if (argc != 3)
E 3
I 3
	if (argc != 4)
E 3
		usage();
D 3
	dev = argv[2];
	i = strlen(dev);
E 3
	bootfname = argv[1];
I 3
	xxboot = argv[2];
	bootxx = argv[3];
E 3
	ifd = open(bootfname, 0, 0);
	if (ifd < 0) {
		perror(bootfname);
		exit(1);
	}
D 3
	ofd = open(dev, 2, 0);
	if (ofd < 0) {
	deverr:
		perror(dev);
E 3
I 3
	ofd1 = creat(xxboot, 0666);
	if (ofd1 < 0) {
	xxboot_err:
		perror(xxboot);
E 3
		exit(1);
	}
I 3
	ofd2 = creat(bootxx, 0666);
	if (ofd2 < 0) {
	bootxx_err:
		perror(bootxx);
		exit(1);
	}
E 3

	/*
	 * Check for exec header and skip to code segment.
	 */
D 6
	if (!DecHeader(ifd, &loadAddr, &execAddr, &length)) {
E 6
I 6
	if (!GetHeader(ifd, &loadAddr, &execAddr, &length)) {
E 6
		fprintf(stderr, "Need impure text format (OMAGIC) file\n");
		exit(1);
	}
D 5
	if (length > MAXBOOTSIZE) {
		fprintf(stderr, "boot program is too big (%d > %d)\n",
			length, MAXBOOTSIZE);
		exit(1);
	}
E 5

	/*
	 * Write the boot information block.
	 */
	decBootInfo.magic = DEC_BOOT_MAGIC;
	decBootInfo.mode = 0;
	decBootInfo.loadAddr = loadAddr;
	decBootInfo.execAddr = execAddr;
	decBootInfo.map[0].numBlocks = nsectors =
		(length + DEV_BSIZE - 1) >> DEV_BSHIFT;
	decBootInfo.map[0].startBlock = 1;
	decBootInfo.map[1].numBlocks = 0;
D 3
	if (lseek(ofd, (long)(DEC_BOOT_SECTOR * DEV_BSIZE), 0) < 0 ||
	    write(ofd, (char *)&decBootInfo, sizeof(decBootInfo)) !=
	    sizeof(decBootInfo)) {
		perror(dev);
		fprintf(stderr, "Sector write %d failed: ", DEC_BOOT_SECTOR);
		exit(1);
	}
	if (lseek(ofd, (long)(1 * DEV_BSIZE), 0) < 0)
		goto deverr;
E 3
I 3
	if (write(ofd1, (char *)&decBootInfo, sizeof(decBootInfo)) !=
	    sizeof(decBootInfo) || close(ofd1) != 0)
		goto xxboot_err;
E 3

I 5
	printf("load %x, start %x, len %d, nsectors %d\n", loadAddr, execAddr,
		length, nsectors);

E 5
	/*
D 3
	 * Write the remaining code to the correct place on the disk.
E 3
I 3
	 * Write the boot code to the bootxx file.
E 3
	 */
	for (i = 0; i < nsectors && length > 0; i++) {
D 3
		bzero(block, DEV_BSIZE);
		n = length < DEV_BSIZE ? length : DEV_BSIZE;
E 3
I 3
		if (length < DEV_BSIZE) {
			n = length;
			bzero(block, DEV_BSIZE);
		} else
			n = DEV_BSIZE;
E 3
		if (read(ifd, block, n) != n) {
			perror(bootfname);
			break;
		}
		length -= n;
D 3
		if (write(ofd, block, DEV_BSIZE) != DEV_BSIZE) {
			perror(dev);
E 3
I 3
		if (write(ofd2, block, DEV_BSIZE) != DEV_BSIZE) {
			perror(bootxx);
E 3
			break;
		}
	}
D 3
	printf("Wrote %d sectors\n", i);
E 3
	if (length > 0)
		printf("Warning: didn't reach end of boot program!\n");
	exit(0);
}

usage()
{
D 3
	printf("Usage: installboot bootprog device\n");
E 3
I 3
	printf("Usage: mkboot bootprog xxboot bootxx\n");
E 3
	printf("where:\n");
D 5
	printf("\t\"bootprog\" is a -N format file < %d bytes long\n",
	       MAXBOOTSIZE);
D 3
	printf("\t\"device\" should be the 'a' partition of a bootable disk\n");
	printf("WARNING!!  If the 'c' partition contains a file system, %s\n",
	       "DON'T RUN THIS!!");
E 3
I 3
	printf("\t\"xxboot\" is the name of the first boot block\n");
	printf("\t\"bootxx\" is the name of the remaining boot blocks.\n");
E 5
I 5
	printf("\t\"bootprog\" is a -N format file\n");
	printf("\t\"xxboot\" is the file name for the first boot block\n");
	printf("\t\"bootxx\" is the file name for the remaining boot blocks.\n");
E 5
E 3
	exit(1);
}

/*
 *----------------------------------------------------------------------
 *
D 6
 * DecHeader -
E 6
I 6
 * GetHeader -
E 6
 *
D 2
 *	Check if the header is a dec (coff) file.
E 2
I 2
D 6
 *	Check if the header is a DEC (COFF) file.
E 6
I 6
 *	Check if the header is an a.out file.
E 6
E 2
 *
 * Results:
 *	Return true if all went ok.
 *
 * Side effects:
D 6
 *	None.
E 6
I 6
 *	bootFID is left ready to read the text & data sections.
 *	length is set to the size of the text + data sections.
E 6
 *
 *----------------------------------------------------------------------
 */
D 6
DecHeader(bootFID, loadAddr, execAddr, length)
E 6
I 6
GetHeader(bootFID, loadAddr, execAddr, length)
E 6
	int bootFID;	/* Handle on the boot program */
	long *loadAddr;	/* Address to start loading boot program. */
	long *execAddr;	/* Address to start executing boot program. */
	long *length;	/* Length of the boot program. */
{
	struct exec aout;
	int bytesRead;

	if (lseek(bootFID, 0, 0) < 0) {
		perror(bootfname);
		return 0;
	}
	bytesRead = read(bootFID, (char *)&aout, sizeof(aout));
D 6
	if (bytesRead != sizeof(aout) || aout.ex_fhdr.magic != COFF_MAGIC ||
	    aout.a_magic != OMAGIC)
E 6
I 6
	if (bytesRead != sizeof(aout) || aout.a_magic != OMAGIC)
E 6
		return 0;
D 6
	*loadAddr = aout.ex_aout.codeStart;
E 6
I 6
	*loadAddr = aout.a_entry;
E 6
	*execAddr = aout.a_entry;
	*length = aout.a_text + aout.a_data;
	if (lseek(bootFID, N_TXTOFF(aout), 0) < 0) {
		perror(bootfname);
		return 0;
	}
D 2
	printf("Input file is coff format\n");
E 2
I 2
D 6
	printf("Input file is COFF format\n");
E 6
I 6
	printf("Input file is a.out format\n");
E 6
E 2
D 5
	printf("load %x, start %x, len %d\n", *loadAddr, *execAddr, *length);
E 5
	return 1;
}
E 1
