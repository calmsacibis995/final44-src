/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	bootblk.c,v $
 * Revision 2.2  89/07/12  00:10:10  jjc
 * 	Taken from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
/*
 * @(#)bootblk.c 1.6 88/02/08 Copyr 1985 Sun Micro
 * bootblk.c - read blocks into memory to jump start the real 'boot' program
 */

#include "../lib/stand/saio.h"
#include "../lib/stand/param.h"
#include <a.out.h>
#include <sys/vm.h>
#include <sys/reboot.h>
#include <mon/sunromvec.h>

/*
 * Block zero is reserved for the label.
 * Blocks 1 through 15 are reserved for the boot block.
 * The boot block has a branch followed 64 entries for information
 * about the blocks of the real boot program followed by
 * a simple program to read them in.
 */

/*
 * entries in table to describe location of boot on disk
 * written by installboot program
 */
struct blktab {
	unsigned int	b_blknum:24;	/* starting block number */
	unsigned int	b_size:8;	/* number of DEV_BSIZE byte blocks */
};

struct saioreq iob;

extern struct blktab bootb[];
extern int bbsize;
extern int bbchecksum;

/*
 * Reads in the "real" boot program and jumps to it.  If this
 * attempt fails, prints "boot failed" and returns to its caller.
 *
 * It will try to determine if it is loading a Unix file by
 * looking at what should be the magic number.  If it makes
 * sense, it will use it; otherwise it jumps to the first
 * address of the blocks that it reads in.
 *
 * When it is created (by installboot) a list of starting
 * blocks and sizes is written into an array of 64 words
 * at the beginning of this program.  The information is
 * assumed to describe the blocks of the boot program which
 * are read in at LOAD and jumped to.
 */
main()
{
	register struct bootparam *bp;
	register struct saioreq *io;
	register int *addr;
	register unsigned sum;
	register struct exec *x;

	extern struct boottab *(devsw[]);

	bp = *(romp->v_bootparam);
	if (devsw[0] != (struct boottab *)0)
		bp->bp_boottab = devsw[0];

	io = &iob;
	io->si_boottab = bp->bp_boottab; /* Record pointer to boot table */
	io->si_ctlr = bp->bp_ctlr;
	io->si_unit = bp->bp_unit;
	io->si_boff = bp->bp_part;

	if (devopen(io)) {
		io->si_flgs = 0;
		goto failed;
	}
	io->si_flgs |= 1;

	if (sum = getboot(io) != -1) {
		sum = 0;
		for (addr = (int *)LOAD;
		     addr < (int *)(LOAD+bbsize);
		     addr++)
			sum += *addr;
		if (sum != bbchecksum)
			printf("checksum %x != %x, trying to boot anyway\n",
				sum, bbchecksum);
		x = (struct exec *)LOAD;
		if (x->a_magic == OMAGIC ||
		    x->a_magic == ZMAGIC ||
		    x->a_magic == NMAGIC)
			_exitto(LOAD + sizeof (struct exec));
		else
			_exitto(LOAD);
	}
failed:
	printf("boot-block startup failed\n");
}

getboot(io)
	register struct saioreq *io;
{
	register struct blktab *bt = (struct blktab *)bootb;
	register int i, size;

	for (io->si_ma = (char *)LOAD; bt->b_size; bt++) {
		io->si_offset = 0;
		io->si_bn = bt->b_blknum;	
		size = io->si_cc = bt->b_size << DEV_BSHIFT;
		if (i = devread(io) != size) {
			return(-1);
		}
		io->si_ma += io->si_cc;
	}
	return(0);
}

