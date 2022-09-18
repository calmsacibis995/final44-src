/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	installboot.c,v $
 * Revision 2.2  89/07/12  00:11:21  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03  23:29:34  jjc]
 * 
 */
#ifndef lint
static        char sccsid[] = "@(#)installboot.c 1.7 88/02/08 Copyr 1983 Sun Micro";
#endif

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */


/*
 * installboot.c 
 *
 * Install the bootblk program in the boot block.
 * The real boot program will be read via a table
 * of entries that point to where the boot program
 * is stored in the file system.
 */

#include <stdio.h>
#include <sys/exec.h>
#include <sys/file.h>
#include <sys/param.h>
#include <sys/time.h>
#if	MACH
#include <sys/fs.h>
#include <sys/inode.h>
#else	MACH
#include <sys/vnode.h>
#include <ufs/fs.h>
#include <ufs/inode.h>
#endif	MACH
#include <sys/stat.h>
#include <sys/dir.h>

#define NDBLKS		64
#define SECTORSIZE      512
#define SUPERADDR       (16*SECTORSIZE)
#define BOOTBLKSIZE	(16-1)*SECTORSIZE

char	vflg = 0;
char	lflg = 0;

#ifdef DEBUG
char	tflg = 0;
#endif	/* DEBUG */

struct  fs      ufs;
struct  dinode  dinode;
char *malloc();
FILE *fopen();
FILE *fclose();
char bb[BOOTBLKSIZE];

/* VARARGS2 */
extern char *sprintf();

/*
 * entries in table to describe location of boot on disk
 * written by installboot
 */
struct blktab {
	unsigned int	b_blknum:24;	/* starting block number */
	unsigned int	b_size:8;	/* number of DEV_BSIZE byte blocks */
};

struct biblk {
	struct blktab 	bi_blks[NDBLKS];
	int		bi_size;
	int		bi_checksum;
} biblk;

main(argc, argv)
	register int argc;
	register char *argv[];
{
	register int i;
	register int fd;
	register char *bootfile;
	register char *protobootblk;
	register char *bootdevice;

	if (argc < 4 || argc >5) {
#ifdef DEBUG
		fprintf(stderr, "Usage: %s [-vlt] bootfile protobootblk bootdevice\n", *argv);
#else
		fprintf(stderr, "Usage: %s [-vl] bootfile protobootblk bootdevice\n", *argv);
#endif	/* DEBUG */
		exit(1);
	}

	/* check arguments */
	if (argv[1][0] == '-') {
		for (i = 1; argv[1][i]; i++) {
			switch (argv[1][i]) {
#ifdef DEBUG
			case 't':		/* testing */
				tflg++;
				lflg++;		/* fall through */
#endif	/* DEBUG */
			case 'v':
				vflg++;		/* be verbose */
				break;
			case 'l':
				lflg++;
				break;		/* list blocks */
			default:
				break;
			}
		}
		bootfile = argv[2];
		protobootblk = argv[3];
		bootdevice = argv[4];
	} else {
		bootfile = argv[1];
		protobootblk = argv[2];
		bootdevice = argv[3];
	}

	if (geteuid() != 0) {
		fprintf(stderr, "%s: Not super user\n", *argv);
		exit(1);
	}

	/* make sure the booter is on the disk for getblks() */
	if ((fd = open(bootfile, O_RDWR)) == -1) {
		perror("bootfile open");
		exit(1);
	}
	fsync(fd);
	close(fd);

	if (vflg) {
		printf("Primary boot: %s\n", protobootblk);
		printf("Secondary boot: %s\n", bootfile);
		printf("Boot device: %s\n", bootdevice);
	}

#ifdef DEBUG
	if (vflg)       {
		printf ("Boot: bzero(0x%x, 0x%x)\n", &biblk, sizeof(biblk));
	}
#endif	/* DEBUG */

	bzero((char *)&biblk, sizeof(biblk));

	getblks(bootfile, bootdevice);

	if (lflg) {
		printf("Block locations:\n");
		printf("startblk size\n");
		for (i = 0;
		     biblk.bi_blks[i].b_size && biblk.bi_blks[i].b_blknum;
		     i++) {
			printf("%x\t   %x\n",
			    biblk.bi_blks[i].b_blknum, biblk.bi_blks[i].b_size);
		}
	}

	if ((fd = open(protobootblk, O_RDONLY)) == -1) {
		perror("open");
		exit(1);
	}

	if ((i = tdsize(fd)) > BOOTBLKSIZE) {
		printf("%s > 0x%x (0x%x), will not fit in boot block\n",
			protobootblk, BOOTBLKSIZE, i);
		exit(1);
	}

	/*
	 * Read in the prototype bootblk.   Note that we are
	 * assuming that it still has a header, but we skip
	 * over that so that we write out a bootblock to the
	 * device with no header.
	 */
	if ((int)lseek(fd, (off_t) sizeof (struct exec), 0) == -1) {
		perror("seek");
		exit(1);
	}
	if (read(fd, bb, i) != i) {
		perror("read");
		exit(1);
	}
	close(fd);

#ifdef DEBUG
	if (tflg) {
		printf("Bootblk size: %d\n", i);
	}
#endif 	/* DEBUG */

	/*
	 * get the size of the text and data of the real boot program
	 */
	if ((fd = open(bootfile, O_RDWR)) == -1) {
		fprintf(stderr, "can't open of %s\n", bootfile);
		exit(1);
	}

	/*
	 * calculate and write a checksum of the real boot program
	 * in the bootblk to assure that the blocks that we read in
	 * belong to the right boot program
	 */
	chksum(fd);
	close(fd);

	if (vflg) {
		printf("Boot size: 0x%x\n", biblk.bi_size);
		printf("Boot checksum: 0x%x\n", biblk.bi_checksum);
	}

	/*
	 * save the information about the blocks of the real boot
	 * into the boot block
	 */
#ifdef DEBUG
	if (vflg) {
		printf("Boot: bcopy(0x%x, 0x%x, 0x%x)\n",
			&biblk, bb + sizeof(int),
			sizeof(biblk));
	}
#endif	/* DEBUG */

	bcopy((char *) &biblk, bb + sizeof(int), sizeof(biblk));

#ifdef DEBUG
	if (vflg)
		printf("Block information written to bootblock\n");
	if (tflg)		/* if testing don't write anything */
		 exit(0);
#endif 	/* DEBUG */

	/*
	 * open bootdevice file
	 */
	if ((fd = open(bootdevice, O_RDWR)) == -1) {
		perror("open");
		exit(1);
	}

#ifdef DEBUG
	if (vflg)
		printf("Boot device opened\n");
#endif	/* DEBUG */

	if ((int) lseek(fd, (off_t) SECTORSIZE, 0) == -1) { /* skip the label */
		perror("lseek");
		exit(1);
	}
	
	/*
	 * write out the boot block
	 */
	if (write(fd, bb, BOOTBLKSIZE) == -1) {
		perror("write of boot block failed");
		exit(1);
	}

#ifdef DEBUG
	if (vflg)
		printf("Bootblock written to device\n");
#endif	/* DEBUG */

	printf("Boot block installed\n");
	
	/*
	 * make sure the boot program is marked 0400 and owned by root
	 */
	chown(bootfile, 0, 3);		/* chown root bootfile */
	chmod(bootfile, 0444);		/* chmod 444 bootfile */

}

getblks(file, device)
	char *file;
	char *device;
{
        register int	devfd;
        register int	*blk;
        register int	size;
	register int	bt;
	register int	spf;
	register int	fpb;
	register int	i, j;
	unsigned int	spb;
	struct  stat    statb;
	struct	stat	statrd;
	struct	stat	statd;
	char	*dstr;
	struct	fs *fs;
        int     inode;
        int     block;
        int     offset;
	int	indirect;
	int	seekaddr;
	char	buf[64];
	extern	char *strchr();

	/*
	 * check booter
	 */
	if (stat(file, &statb) == -1) {
		fprintf(stderr, "File %s not found\n", file);
		exit(1);
	}
	inode = statb.st_ino;

	/*
	 * check bootdevice
	 */
	if (stat(device, &statrd) == -1) {
		fprintf(stderr,
			"bootdevice %s doesn't make sense (couldn't stat)\n",
			device);
		exit(1);
	}

	/*
	 * check that the device we are going to write is a raw device
	 */
	if ((statrd.st_mode & S_IFMT) != S_IFCHR) {
		fprintf(stderr,
			"%s not raw device\n", device);
		exit(1);
	}

	/*
 	 * look for /dev/r____, build name of block device
	 * used for booting, check it
	 */
	dstr = strchr(device, 'r');
	dstr++;
	sprintf(buf, "/dev/%s", dstr);
	if (stat(buf, &statd) == -1) {
		fprintf(stderr,
			"couldn't stat block bootdevice %s\n", buf);
		exit(1);
	}

	/*
	 * if the file's device (st_dev) == the device's device (st_rdev)
	 * the file is on the device 
	 */
	if ((int)statb.st_dev != (int)statd.st_rdev) { 
		fprintf(stderr,
			 "bootfile %s not on bootdevice %s\n", file, device);
		exit(1);
	}
 
	/*
	 * now find the device it is located on and open it
	 */
	devfd = getdevice(statb.st_dev);

	/*
	 * read in and check the superblock
	 */
	if ((int) lseek(devfd, (off_t) SUPERADDR, 0) == NULL) {
		fprintf(stderr, "Seek to superblock failed\n");
		exit(1);
	}
        fs = &ufs;
        if (read(devfd, (char *) fs, sizeof (struct fs)) == -1) {
                fprintf(stderr, "Read of superblock failed\n");
                exit(1);
        }
	if (fs->fs_magic != FS_MAGIC) {
		fprintf(stderr, "Not a superblock\n");
		exit(1);
	}

	block = itod(fs, inode);
	offset = itoo(fs, inode);
	seekaddr = fsbtodb(fs, block) * SECTORSIZE;
	seekaddr += offset*sizeof(struct dinode);
	if ((int) lseek(devfd, (off_t) seekaddr, 0) == -1) {
		fprintf(stderr, "Seek to block %d offset %d failed\n",
			block, offset);
		exit(1);
	}
	if (read(devfd, (char *) &dinode, sizeof(dinode)) == -1) {
		fprintf(stderr, "Read of inode %d failed\n", inode);
		exit(1);
	}

	bt = 0;
	spf = fs->fs_fsize / SECTORSIZE;	/* sectors per frag */
	fpb = fs->fs_bsize / fs->fs_fsize;	/* frags per block */
	spb = fpb * spf;			/* sectors per block */
	size = dinode.di_size;

	/* get first level blocks pointers */
        for (i = 0; i < NDADDR && size > 0; i++) {
		u_int	temp_bsize;

                size -= fs->fs_bsize;
		/* 
		 * try to coalesce sequential blocks
		 * into a blktab single entry
		 */
		if ( (bt > 0) && 
		     ((biblk.bi_blks[bt-1].b_blknum + fpb)
		      == fsbtodb(fs, dinode.di_db[i])) ) {
			temp_bsize = biblk.bi_blks[bt-1].b_size;
			biblk.bi_blks[bt-1].b_size = temp_bsize + spb;
		} else {
			biblk.bi_blks[bt].b_blknum = fsbtodb(fs, dinode.di_db[i]);
			biblk.bi_blks[bt].b_size = (spb & 0xff);
			bt++;
		}
        }
        blk = (int *) malloc((unsigned) fs->fs_bsize);

	/* now go for indirect blocks */
	for (i = 0; i < NIADDR && size > 0; i++) {
		indirect = dinode.di_ib[i];
		seekaddr = fsbtodb(fs, indirect) * SECTORSIZE;
		if ((int) lseek(devfd, (off_t) seekaddr, 0) == -1) {
			fprintf(stderr, "Seek to indirect block %d failed\n",
				indirect);
			exit(1);
		}
		if (read(devfd, (char *) blk, (int) fs->fs_bsize) == -1) {
			fprintf(stderr, "Read of indirect block %d failed\n",
				indirect);
			exit(1);
		}
		/* save block numbers from indirect blocks */
		for (j = 0; j < fs->fs_bsize/sizeof(int) && size > 0; j++) {
			u_int	temp_bsize;

			if ( (bt > 0) && 
			     ((biblk.bi_blks[bt-1].b_blknum + fpb)
			      == fsbtodb(fs, blk[j])) ) {
				temp_bsize = biblk.bi_blks[bt-1].b_size;
				biblk.bi_blks[bt-1].b_size = temp_bsize + spb;
			} else {
				biblk.bi_blks[bt].b_blknum = fsbtodb(fs, blk[j]);
				biblk.bi_blks[bt].b_size = (spb & 0xff);
				bt++;
			}
			size -= fs->fs_bsize;
		}
	}
}

getdevice(dev)
        register dev_t dev;
{
        register DIR *dirp;
        register struct direct *dp;
        register int fd;
        struct stat statb;
        char buf[100];
 
        dirp = opendir("/dev");
        if (dirp == NULL) {
                fprintf(stderr, "cannot open /dev\n");
                exit(1);
        }
        while (dp = readdir(dirp)) {
#if	MACH
                if (dp->d_ino == 0) {
#else	MACH
                if (dp->d_fileno == 0) {
#endif	MACH
                        continue;
                }
                sprintf(buf, "/dev/%s", dp->d_name);
                if (stat(buf, &statb) == -1) {
                        continue;
                }
                if ((statb.st_rdev == dev) && 
		    ((statb.st_mode & S_IFMT) == S_IFBLK)) {
                        fd = open(buf, 0);
                        if (fd < 0) {
                                fprintf(stderr, "cannot open %s\n", buf);
                                exit(1);
			}
			return (fd);
                }
        }
        fprintf(stderr, "Device %x not found (NFS file?).\n", dev & 0xffff);
        exit (1);
}

/*
 * read the header of the file and return 
 * the sum of its text and data segments
 */
tdsize(bootfd)
	register int bootfd;
{
	char buf[(sizeof (struct exec) * 2) + 4];
	register struct exec *e;

	if (read(bootfd, buf, sizeof (struct exec))== -1) {
		printf("trouble reading header\n");
	}
	e = (struct exec *)buf;

#ifdef DEBUG
	if (vflg) {
		printf("tdsize: test 0x%x data 0x%x\n", e->a_text, e->a_data);
	}
#endif	/* DEBUG */

	return(e->a_text + e->a_data);
}


chksum(fd)
	register int fd;
{
	register unsigned int sum;
	register int *p;
	register int x;
	register int size;
	int buf[ DEV_BSIZE / sizeof (int) ];
	
	/*
	 * the boot prgram loaded by the bootblk must not
	 * have a header and should be stripped.
	 */
	lseek(fd, (off_t)0, 0);

	sum = 0;
	size = 0;
	bzero ((char *) buf, sizeof buf);

	while (x = read(fd, (char *) buf, sizeof buf)) {
		size += x;
		for (p = buf; x > 0; x -= 4) {
			 sum += *p++;
		}
		bzero ((char *) buf, sizeof buf);
	}

	biblk.bi_size = size;
	biblk.bi_checksum = sum;
}

