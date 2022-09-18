h62046
s 00002/00002/00209
d D 8.1 93/06/10 23:31:33 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00013/00038/00198
d D 7.7 93/03/08 19:00:32 ralph 7 6
c use new err() function.
e
s 00024/00017/00212
d D 7.6 93/02/04 20:01:31 ralph 6 5
c modified to take a.out format kernel and make ECOFF file for DEC.
e
s 00002/00001/00227
d D 7.5 92/10/11 11:28:17 bostic 5 4
c make kernel includes standard
e
s 00018/00017/00210
d D 7.4 92/04/19 09:03:50 ralph 4 3
c fix argv indexing and fix writes so always 512 bytes.
e
s 00002/00002/00225
d D 7.3 92/03/30 09:28:33 bostic 3 2
c argc decremented by getopt
e
s 00086/00062/00141
d D 7.2 92/03/30 09:24:14 bostic 2 1
c KNR, BSD/ANSI stylistic changes
e
s 00203/00000/00000
d D 7.1 92/03/30 09:13:26 bostic 1 0
c date and time created 92/03/30 09:13:26 by bostic
e
u
U
t
T
I 1
/*-
D 8
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#include <stdio.h>
E 2
#include <sys/param.h>
I 2
#include <sys/stat.h>
E 2
#include <sys/exec.h>
I 5

E 5
I 2
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
I 7
#include <err.h>
E 7
E 2
D 4
#include "../dev/devDiskLabel.h"
E 4

I 4
D 5
#include "dec_boot.h"
E 5
I 5
#include <pmax/stand/dec_boot.h>
I 6
#include <pmax/stand/dec_exec.h>
E 6
E 5

E 4
D 2
char	block[DEV_BSIZE];
char	*tapedev, *rootdev, *bootfname;
E 2
I 2
D 7
void err __P((const char *, ...));
E 7
void usage __P((void));
E 2

I 4
struct	Dec_DiskBoot decBootInfo;
I 6
struct	coff_exec dec_exec;
I 7
extern char *__progname;		/* Program name, from crt0. */
E 7
E 6

E 4
/*
 * This program takes a kernel and the name of the special device file that
 * has the mini-root file system stored on it and creates a boot tape.
 * The -b option makes a bootfile that can load the kernel and mini-root
 * over the network using the 'boot 6/tftp/filename -m' PROM command.
 *
 * usage: mkboottape [-b] tapedev vmunix minirootdev size
 */
I 2
int
E 2
main(argc, argv)
	int argc;
	char *argv[];
{
	register int i, n;
D 2
	int ifd, ofd, rfd;
E 2
D 4
	Dec_DiskBoot decBootInfo;
E 4
	ProcSectionHeader shdr;
	struct exec aout;
D 2
	int nsectors;
E 2
	long loadAddr;
	long execAddr;
D 7
	long textoff;
E 7
I 7
	off_t textoff;
E 7
	long length;
	long rootsize;
D 2
	int makebootfile = 0;
E 2
I 2
	int ifd, ofd, rfd;
	int makebootfile;
	int nsectors;
	char block[DEV_BSIZE];
E 2

D 2
	if (argc > 1 && strcmp(argv[1], "-b") == 0) {
		argc--;
		argv++;
		makebootfile = 1;
	}
E 2
I 2
	makebootfile = 0;
	while ((i = getopt(argc, argv, "b")) != EOF)
		switch(i) {
		case 'b':
			makebootfile = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

E 2
D 3
	if (argc != 5)
E 3
I 3
	if (argc != 4)
E 3
		usage();
D 2
	tapedev = argv[1];
	bootfname = argv[2];
	rootdev = argv[3];
E 2
D 3
	rootsize = atoi(argv[4]);
E 3
D 2
	ifd = open(bootfname, 0, 0);
	if (ifd < 0) {
	bootferr:
		perror(bootfname);
		exit(1);
	}
	rfd = open(rootdev, 0, 0);
	if (rfd < 0) {
		perror(rootdev);
		exit(1);
	}
E 2
I 2

E 2
	if (makebootfile)
D 2
		ofd = creat(tapedev, 0666);
E 2
I 2
D 4
		ofd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, DEFFILEMODE);
E 4
I 4
		ofd = open(argv[0], O_CREAT|O_TRUNC|O_WRONLY, DEFFILEMODE);
E 4
E 2
	else
D 2
		ofd = open(tapedev, 2, 0);
	if (ofd < 0) {
	deverr:
		perror(tapedev);
		exit(1);
	}
E 2
I 2
D 4
		ofd = open(argv[1], O_RDWR, 0);
E 4
I 4
		ofd = open(argv[0], O_RDWR, 0);
E 4
	if (ofd < 0)
D 4
deverr:		err("%s: %s", argv[1], strerror(errno));
E 4
I 4
D 7
deverr:		err("%s: %s", argv[0], strerror(errno));
E 7
I 7
deverr:		err(1, "%s", argv[0]);
E 7
E 4
E 2

I 2
D 4
	if ((ifd = open(argv[2], O_RDONLY, 0)) < 0)
bootferr:	err("%s: %s", argv[2], strerror(errno));
E 4
I 4
	if ((ifd = open(argv[1], O_RDONLY, 0)) < 0)
D 7
bootferr:	err("%s: %s", argv[1], strerror(errno));
E 7
I 7
bootferr:	err(1, "%s", argv[1]);
E 7
E 4

D 4
	if ((rfd = open(argv[3], 0, 0)) < 0)
rooterr:	err("%s: %s", argv[3], strerror(errno));
E 4
I 4
	if ((rfd = open(argv[2], O_RDONLY, 0)) < 0)
D 7
rooterr:	err("%s: %s", argv[2], strerror(errno));
E 7
I 7
rooterr:	err(1, "%s", argv[2]);
E 7
E 4

I 3
D 4
	rootsize = atoi(argv[4]);
E 4
I 4
	rootsize = atoi(argv[3]);
E 4
E 3

E 2
	/*
	 * Check for exec header and skip to code segment.
	 */
D 2
	i = read(ifd, (char *)&aout, sizeof(aout));
	if (i != sizeof(aout) || aout.ex_fhdr.magic != COFF_MAGIC ||
	    aout.a_magic != OMAGIC) {
		fprintf(stderr, "Need impure text format (OMAGIC) file\n");
		exit(1);
	}
E 2
I 2
	if (read(ifd, &aout, sizeof(aout)) != sizeof(aout) ||
D 6
	    aout.ex_fhdr.magic != COFF_MAGIC || aout.a_magic != OMAGIC)
		err("need impure text format (OMAGIC) file");
E 6
I 6
D 7
	    aout.a_magic != OMAGIC)
		err("%s: need impure text format (OMAGIC) file", argv[1]);
E 7
I 7
	    aout.a_magic != OMAGIC) {
		fprintf(stderr, "%s: %s: need old text format (OMAGIC) file\n",
			__progname, argv[1]);
		exit(1);
	}
E 7
E 6

E 2
D 6
	loadAddr = aout.ex_aout.codeStart;
E 6
I 6
	loadAddr = aout.a_entry;
E 6
	execAddr = aout.a_entry;
	length = aout.a_text + aout.a_data;
	textoff = N_TXTOFF(aout);
D 2
	printf("Input file is COFF format\n");
	printf("load %x, start %x, len %d\n", loadAddr, execAddr, length);
E 2
I 2
D 6
	(void)printf("Input file is COFF format\n");
E 6
I 6
	(void)printf("Input file is a.out format\n");
E 6
	(void)printf("load %x, start %x, len %d\n", loadAddr, execAddr, length);
E 2

	/*
	 * Compute size of boot program rounded to page size + mini-root size.
	 */
	nsectors = (((length + aout.a_bss + NBPG - 1) & ~(NBPG - 1)) >>
D 2
		DEV_BSHIFT) + rootsize;
E 2
I 2
D 4
	    DEV_BSHIFT) + rootsize;
E 4
I 4
		DEV_BSHIFT) + rootsize;
E 4
E 2

	if (makebootfile) {
		/*
D 6
		 * Write modified ECOFF header.
E 6
I 6
		 * Write the ECOFF header.
E 6
		 */
D 6
		aout.ex_fhdr.numSections = 1;
		aout.ex_fhdr.numSyms = 0;
		aout.ex_fhdr.symPtr = 0;
		aout.a_text = nsectors << DEV_BSHIFT;
		aout.a_data = 0;
		aout.a_bss = 0;
		aout.ex_aout.heapStart = aout.ex_aout.bssStart =
			aout.ex_aout.codeStart + aout.a_text;
		if (write(ofd, (char *)&aout, sizeof(aout)) != sizeof(aout))
E 6
I 6
		dec_exec.magic = COFF_MAGIC;
		dec_exec.numSections = 1;
		dec_exec.optHeader = 56;
		dec_exec.flags = 7;
		dec_exec.aout_magic = OMAGIC;
		dec_exec.verStamp = 512;
		dec_exec.codeSize = nsectors << DEV_BSHIFT;
		dec_exec.entry = execAddr;
		dec_exec.codeStart = loadAddr;
		dec_exec.heapStart = dec_exec.bssStart =
			dec_exec.codeStart + aout.a_text;
		if (write(ofd, (char *)&dec_exec, sizeof(dec_exec)) !=
		    sizeof(dec_exec))
E 6
			goto deverr;
		strncpy(shdr.name, ".text", sizeof(shdr.name));
		shdr.physAddr = shdr.virtAddr = loadAddr;
D 6
		shdr.size = aout.a_text;
		shdr.sectionPtr = n = (sizeof(aout) + sizeof(shdr) + 15) & ~15;
E 6
I 6
		shdr.size = dec_exec.codeSize;
		shdr.sectionPtr = n =
			(sizeof(dec_exec) + sizeof(shdr) + 15) & ~15;
E 6
		shdr.relocPtr = 0;
		shdr.lnnoPtr = 0;
		shdr.numReloc = 0;
		shdr.numLnno = 0;
		shdr.flags = 0x20;
		if (write(ofd, (char *)&shdr, sizeof(shdr)) != sizeof(shdr))
			goto deverr;
D 6
		n -= sizeof(aout) + sizeof(shdr);
E 6
I 6
		n -= sizeof(dec_exec) + sizeof(shdr);
E 6
		if (write(ofd, block, n) != n)
			goto deverr;
	} else {
		/*
		 * Write the boot information block.
		 */
		decBootInfo.magic = DEC_BOOT_MAGIC;
		decBootInfo.mode = 0;
		decBootInfo.loadAddr = loadAddr;
		decBootInfo.execAddr = execAddr;
		decBootInfo.map[0].numBlocks = nsectors;
		decBootInfo.map[0].startBlock = 1;
		decBootInfo.map[1].numBlocks = 0;
		if (write(ofd, (char *)&decBootInfo, sizeof(decBootInfo)) !=
		    sizeof(decBootInfo))
			goto deverr;
	}
	/* seek to start of text */
D 2
	if (lseek(ifd, textoff, 0) < 0)
E 2
I 2
	if (lseek(ifd, textoff, SEEK_SET) < 0)
E 2
		goto bootferr;

	/*
	 * Write the remaining code to the correct place on the tape.
	 */
D 2
	i = length;
	while (i > 0) {
E 2
I 2
	for (i = length; i > 0; i -= n) {
E 2
		n = DEV_BSIZE;
		if (n > i)
			n = i;
		if (read(ifd, block, n) != n)
			goto bootferr;
D 4
		if (write(ofd, block, n) != n)
E 4
I 4
		if (write(ofd, block, DEV_BSIZE) != DEV_BSIZE)
E 4
			goto deverr;
D 2
		i -= n;
E 2
	}

	/*
	 * Pad the boot file with zeros to the start of the mini-root.
	 */
	bzero(block, DEV_BSIZE);
D 2
	i = ((nsectors - rootsize) << DEV_BSHIFT) - length;
	while (i > 0) {
E 2
I 2
D 4
	for (i = ((nsectors - rootsize) << DEV_BSHIFT) - length;
	    i > 0; i -= n) {
E 2
		n = DEV_BSIZE;
		if (n > i)
			n = i;
E 4
I 4
	i = ((nsectors - rootsize) << DEV_BSHIFT) -
		((length + DEV_BSIZE - 1) & ~(DEV_BSIZE - 1));
	n = DEV_BSIZE;
	for (; i > 0; i -= n) {
E 4
		if (write(ofd, block, n) != n)
			goto deverr;
D 2
		i -= n;
E 2
	}

	/*
	 * Write the mini-root to tape.
	 */
D 2
	i = rootsize;
	while (i > 0) {
		if (read(rfd, block, DEV_BSIZE) != DEV_BSIZE) {
			perror(rootdev);
			break;
		}
E 2
I 2
	for (i = rootsize; i > 0; i--) {
		if (read(rfd, block, DEV_BSIZE) != DEV_BSIZE)
			goto rooterr;
E 2
		if (write(ofd, block, DEV_BSIZE) != DEV_BSIZE)
			goto deverr;
D 2
		i--;
E 2
	}

D 2
	printf("Wrote %d sectors\n", nsectors);
E 2
I 2
D 7
	(void)printf("mkboottape: wrote %d sectors\n", nsectors);
E 7
I 7
	(void)printf("%s: wrote %d sectors\n", __progname, nsectors);
E 7
E 2
	exit(0);
}

I 2
void
E 2
usage()
{
D 2
	printf("Usage: mkboottape [-b] tapedev vmunix minirootdev size\n");
	printf("where:\n");
	printf("\t\"tapedev\" is the tape drive device\n");
	printf("\t\"vmunix\" is a -N format file\n");
	printf("\t\"minitrootdev\" is the character device of a mini-root file system disk\n");
	printf("\t\"size\" is the number of 512 byte blocks in the file system\n");
E 2
I 2
	(void)fprintf(stderr,
D 7
	    "usage: mkboottape [-b] tapedev vmunix minirootdev size\n");
E 7
I 7
	    "usage: %s [-b] tapedev vmunix minirootdev size\n", __progname);
E 7
E 2
	exit(1);
I 2
D 7
}

#if __STDC__
#include <stdarg.h>
#else
#include <varargs.h>
#endif

void
#if __STDC__
err(const char *fmt, ...)
#else
err(fmt, va_alist)
	char *fmt;
        va_dcl
#endif
{
	va_list ap;
#if __STDC__
	va_start(ap, fmt);
#else
	va_start(ap);
#endif
	(void)fprintf(stderr, "mkboottape: ");
	(void)vfprintf(stderr, fmt, ap);
	va_end(ap);
	(void)fprintf(stderr, "\n");
	exit(1);
	/* NOTREACHED */
E 7
E 2
}
E 1
