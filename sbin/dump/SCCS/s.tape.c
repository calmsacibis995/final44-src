h56196
s 00001/00001/00832
d D 8.4 95/05/01 23:40:21 mckusick 44 43
c changes for new dinode definitions
e
s 00002/00002/00831
d D 8.3 95/04/28 10:29:26 bostic 43 42
c prettiness police; From: Charles Hannum <mycroft@NetBSD.ORG>
e
s 00003/00000/00830
d D 8.2 94/03/17 05:36:38 bostic 42 41
c When rdump aborts, it doesn't always properly close a remote tape.
c Consider an example: remote tape error.  tperror() gets called.
c If the user decides to punt the dump, it's aborted, and the
c remote is never properly closed.
c From: "Chris G. Demetriou" <cgd@sun-lamp.cs.berkeley.edu>
e
s 00002/00002/00828
d D 8.1 93/06/05 10:52:57 bostic 41 40
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00001/00826
d D 5.27 93/05/11 12:29:41 mckusick 40 39
c lint
e
s 00036/00037/00791
d D 5.26 93/01/25 15:36:05 mckusick 39 38
c cleanups from leres@lbl
e
s 00016/00012/00812
d D 5.25 92/07/16 12:40:00 bostic 38 37
c fix the prototypes, minor cleanup to signal handlers
e
s 00004/00002/00820
d D 5.24 92/07/02 16:20:16 mckusick 37 35
c writerec notes whether a record is a spcl record
e
s 00070/00000/00822
d D 5.23.1.1 92/06/18 14:29:25 mckusick 36 35
c debugging for slave processes
e
s 00047/00113/00775
d D 5.23 92/06/18 14:27:13 mckusick 35 33
c lint, fix for truncated output to pipes
e
s 00127/00447/00441
d R 5.23 92/05/26 10:05:31 mckusick 34 33
c back out -r5.19 to working flock based code
e
s 00003/00002/00885
d D 5.22 91/11/10 13:05:08 bostic 33 32
c break UFS up into FFS/UFS/LFS/MFS
e
s 00007/00001/00880
d D 5.21 91/07/26 17:05:32 mckusick 32 31
c minor update from romig to make sunos happy
e
s 00010/00000/00871
d D 5.20 91/07/23 21:06:31 mckusick 31 30
c temporarily add ifdef sunos (includes) to assist Steve Romig in debugging
e
s 00448/00126/00423
d D 5.19 91/07/23 21:05:38 mckusick 30 29
c put in EOT handling; merge dump and rdump;
c have slaves communicate using signals rather than flock
e
s 00034/00020/00515
d D 5.18 91/04/24 15:01:07 karels 29 28
c fix changes from last time: blockswritten isn't per volume (as the error msg
c said); more info on errors
e
s 00005/00004/00530
d D 5.17 91/03/07 17:49:56 mckusick 28 27
c verified to be free of AT&T code
e
s 00020/00003/00514
d D 5.16 91/03/07 11:37:26 karels 27 26
c prespecify multiple tape volumes
e
s 00020/00004/00497
d D 5.15 91/02/28 19:33:54 bostic 26 25
c ANSI; break #includes out of dump.h into separate files
e
s 00025/00035/00476
d D 5.14 91/02/28 18:51:38 mckusick 25 24
c KNF, misc naming cleanups
e
s 00011/00010/00500
d D 5.13 91/02/24 14:03:34 mckusick 24 23
c updates from Mike to make messages more media independent;
c add 'B' flag to specify number of blocks per volume
e
s 00055/00044/00455
d D 5.12 91/02/23 16:15:02 torek 23 22
c avoid multiply and divide when possible; fix gcc warnings;
c perror => strerror; quit via new quit() function
e
s 00005/00003/00494
d D 5.11 91/02/03 01:47:13 torek 22 21
c rewind => trewind (for ANSI C)
e
s 00003/00002/00494
d D 5.10 89/09/15 20:51:22 bostic 21 20
c POSIX signals
e
s 00006/00002/00490
d D 5.9 89/09/12 17:32:02 mckusick 20 19
c use pathnames.h; more explicit error message
e
s 00001/00001/00491
d D 5.8 87/02/23 18:06:28 mckusick 19 18
c convert SBLOCK to SBOFF; generalize dev_bsize
e
s 00002/00000/00490
d D 5.7 87/01/28 19:03:09 mckusick 18 17
c backward compatibility
e
s 00012/00003/00478
d D 5.6 86/10/21 15:52:03 mckusick 17 16
c new TS_TAPE header indicates the number of tape blocks to skip
c (in the c_count field) to find the first valid header on the volume
e
s 00001/00001/00480
d D 5.5 86/05/23 11:27:40 mckusick 16 15
c add newline to message
e
s 00019/00009/00462
d D 5.4 86/03/05 19:49:45 mckusick 15 14
c make lockfile generate a more senible error message
e
s 00105/00124/00366
d D 5.3 85/10/16 20:31:02 mckusick 14 13
c latest update from Don Speck
e
s 00160/00148/00330
d D 5.2 85/08/05 18:58:44 mckusick 13 12
c use flock instead of pipes to syncronize the slaves (from speck@cit-vlsi)
e
s 00008/00002/00470
d D 5.1 85/06/05 08:47:11 dist 12 11
c Add copyright
e
s 00038/00013/00434
d D 1.11 85/05/07 18:49:42 mckusick 11 10
c more fully check return values to isolate ring errors
e
s 00024/00002/00423
d D 1.10 85/05/04 16:44:34 mckusick 10 9
c must batch up reads from pipes
e
s 00249/00119/00176
d D 1.9 85/02/19 16:05:12 mckusick 9 8
c streaming dump mods using a ring of pipes (Caltech via speck@cit-vax)
e
s 00004/00003/00291
d D 1.8 84/12/16 17:57:17 sam 8 7
c replace copy loop with block copy
e
s 00017/00002/00277
d D 1.7 83/05/08 19:11:07 mckusick 7 6
c add ability to dump to standard output
e
s 00028/00008/00251
d D 1.6 83/02/11 12:58:39 sam 6 5
c merge from sun
e
s 00012/00011/00247
d D 1.5 82/01/05 01:37:27 mckusic 5 4
c parameterize BSIZE, FSIZE, and FRAG into fs_bsize, fs_fsize, and fs_frag
e
s 00022/00028/00236
d D 1.4 81/11/07 14:53:17 mckusic 4 3
c dump to "standard" (ie 1K file system) dump tapes
e
s 00006/00003/00258
d D 1.3 81/03/11 18:52:17 wnj 3 2
c dont wait for rewind a fixed length of time;;; use reopen until succeed
e
s 00003/00031/00258
d D 1.2 80/12/18 00:52:52 wnj 2 1
c dump moans about ``Mount next tape'' unnecessarily; dump is rude
e
s 00289/00000/00000
d D 1.1 80/10/13 17:30:30 root 1 0
c date and time created 80/10/13 17:30:30 by root
e
u
U
f b 
t
T
I 12
D 28
/*
D 27
 * Copyright (c) 1980 Regents of the University of California.
E 27
I 27
 * Copyright (c) 1980,1991 Regents of the University of California.
E 27
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 28
I 28
/*-
D 41
 * Copyright (c) 1980, 1991 The Regents of the University of California.
 * All rights reserved.
E 41
I 41
 * Copyright (c) 1980, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 41
 *
 * %sccs.include.redist.c%
E 28
 */

E 12
I 8
#ifndef lint
E 8
I 1
D 12
static	char *sccsid = "%W% (Berkeley) %G%";
I 8
#endif
E 12
I 12
static char sccsid[] = "%W% (Berkeley) %G%";
D 23
#endif not lint
E 23
I 23
#endif /* not lint */
E 23
E 12

I 31
D 39
#ifdef sunos
E 39
I 32
#include <sys/param.h>
E 32
D 39
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
E 39
I 39
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#ifdef sunos
#include <sys/vnode.h>

E 39
D 35
#include <sys/time.h>
#include <sys/dir.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
E 35
I 33
#include <ufs/fs.h>
I 39
#include <ufs/inode.h>
E 39
E 33
#else
E 31
I 23
D 26
#include "dump.h"
E 23
E 8
D 14
#include "dump.h"
E 14
I 9
D 13
#include <signal.h>
E 13
I 13
D 22
#include <sys/file.h>
E 22
I 22
#include <sys/types.h>
E 26
I 26
D 39
#include <sys/param.h>
E 26
I 23
#include <sys/wait.h>
E 39
D 26
#include <errno.h>
E 26
I 26
D 30
#include <ufs/dir.h>
E 30
D 33
#include <ufs/dinode.h>
E 33
I 33
D 35
#include <ufs/ufs/dinode.h>
E 35
D 44
#include <ufs/ffs/fs.h>
E 44
E 33
I 31
D 39
#endif
I 35
#include <sys/time.h>
E 39
#include <ufs/ufs/dinode.h>
I 44
#include <ufs/ffs/fs.h>
E 44
E 35
E 31
D 33
#include <ufs/fs.h>
E 33
D 39
#include <signal.h>
E 26
E 23
#include <fcntl.h>
E 39
I 39
#endif

E 39
I 26
#include <protocols/dumprestore.h>
I 39

E 39
#include <errno.h>
I 39
#include <fcntl.h>
E 39
I 30
#include <setjmp.h>
I 39
#include <signal.h>
#include <stdio.h>
E 39
E 30
#ifdef __STDC__
D 39
#include <unistd.h>
E 39
#include <stdlib.h>
#include <string.h>
I 39
#include <unistd.h>
#else
int	write(), read();
E 39
#endif
I 30
D 39
#include <sys/socket.h>
E 39
I 39

E 39
E 30
#include "dump.h"
E 26
E 22
I 14
D 23
#include "dump.h"
E 23
I 20
#include "pathnames.h"
E 20
E 14
E 13
E 9

D 4
char	tblock[NTREC][BSIZE];
daddr_t	tdaddr[NTREC];
int	trecno;
E 4
I 4
D 6
char	tblock[NTREC][TP_BSIZE];
E 6
I 6
D 17
char	(*tblock)[TP_BSIZE];	/* Pointer to malloc()ed buffer for tape */
int	writesize;		/* Size of malloc()ed buffer for tape */
E 6
int	trecno = 0;
E 17
I 17
D 30
char	(*tblock)[TP_BSIZE];	/* pointer to malloc()ed buffer for tape */
E 30
int	writesize;		/* size of malloc()ed buffer for tape */
long	lastspclrec = -1;	/* tape block number of last written header */
int	trecno = 0;		/* next record to write in current block */
I 24
extern	long blocksperfile;	/* number of blocks per output file */
E 24
E 17
I 6
D 9
extern int ntrec;		/* blocking factor on tape */
E 9
I 9
D 14
extern	int ntrec;		/* blocking factor on tape */
I 13
extern	int cartridge;
int	tenths; 		/* length of tape used per block written */
E 14
I 14
D 29
extern int ntrec;		/* blocking factor on tape */
extern int cartridge;
E 29
I 29
long	blocksthisvol;		/* number of blocks on current output file */
extern	int ntrec;		/* blocking factor on tape */
extern	int cartridge;
I 30
extern	char *host;
E 30
E 29
I 27
char	*nexttape;
E 27
D 26
extern int read(), write();
E 26
D 39
#ifdef RDUMP
D 30
extern char *host;
E 30
I 23
int	rmtopen(), rmtwrite();
void	rmtclose();
E 23
#endif RDUMP
E 14
E 13
E 9
E 6
E 4
D 30

E 30
I 30
void	rollforward();
E 30
I 23
int	atomic();
D 25
void	doslave(), enslave(), flusht(), killall();
E 25
I 25
void	doslave(), enslave(), flushtape(), killall();
E 39
E 25

I 39
static	int atomic __P((int (*)(), int, char *, int));
static	void doslave __P((int, int));
static	void enslave __P((void));
static	void flushtape __P((void));
static	void killall __P((void));
static	void rollforward __P((void));

E 39
E 23
I 6
/*
D 9
 * Allocate the buffer for tape operations.
 *
 * Depends on global variable ntrec, set from 'b' option in command line.
 * Returns 1 if successful, 0 if failed.
 *
 * For later kernel performance improvement, this buffer should be allocated
 * on a page boundary.
E 9
I 9
D 13
 * Streaming dump mods (Caltech) - disk block reading and tape writing
E 13
I 13
 * Concurrent dump mods (Caltech) - disk block reading and tape writing
E 13
 * are exported to several slave processes.  While one slave writes the
 * tape, the others read disk blocks; they pass control of the tape in
D 13
 * a ring via pipes.  The parent process traverses the filesystem and
 * sends daddr's, inode records, etc, through pipes to each slave.
 * Speed from Eagle to TU77 on VAX/780 is about 140 Kbytes/second.
 * #ifdef RDUMP version is CPU-limited to about 40 Kbytes/second.
E 13
I 13
D 30
 * a ring via flock().	The parent process traverses the filesystem and
E 30
I 30
 * a ring via signals. The parent process traverses the filesystem and
E 30
D 14
 * sends spclrec()'s and lists of daddr's to each slave via pipes.
 *
 * from "@(#)dumptape.c 2.1 (Berkeley+Caltech mods) 4/7/85";
E 14
I 14
D 25
 * sends spclrec()'s and lists of daddr's to the slaves via pipes.
E 25
I 25
 * sends writeheader()'s and lists of daddr's to the slaves via pipes.
I 30
 * The following structure defines the instruction packets sent to slaves.
E 30
E 25
E 14
E 13
E 9
 */
I 9
D 30
struct req {			/* instruction packets sent to slaves */
E 30
I 30
struct req {
E 30
	daddr_t dblk;
	int count;
D 30
} *req;
E 30
I 30
};
E 30
int reqsiz;

D 13
#define SLAVES 3		/* 2 slaves read disk while 3rd writes tape */
#define LAG 2			/* Write behind by LAG tape blocks (rdump) */
E 13
I 13
#define SLAVES 3		/* 1 slave writing, 1 reading, 1 for slack */
D 14
int slavepid[SLAVES];
E 13
int slavefd[SLAVES];		/* Pipes from master to each slave */
int rotor;			/* Current slave number */
int master;			/* Pid of master, for sending error signals */
int trace = 0;			/* Protocol trace; easily patchable with adb */
#define  tmsg	if (trace) msg
E 14
I 14
D 30
int slavefd[SLAVES];		/* pipes from master to each slave */
int slavepid[SLAVES];		/* used by killall() */
int rotor;			/* next slave to be instructed */
int master;			/* pid of master, for sending error signals */
int tenths;			/* length of tape used per block written */
E 30
I 30
struct slave {
	int tapea;		/* header number at start of this chunk */
	int count;		/* count to next header (used for TS_TAPE */
				/* after EOT) */
	int inode;		/* inode that we are currently dealing with */
	int fd;			/* FD for this slave */
	int pid;		/* PID for this slave */
	int sent;		/* 1 == we've sent this slave requests */
	int firstrec;		/* record number of this block */
	char (*tblock)[TP_BSIZE]; /* buffer for data blocks */
	struct req *req;	/* buffer for requests */
} slaves[SLAVES+1];
struct slave *slp;
E 30
E 14

I 30
char	(*nextblock)[TP_BSIZE];

int master;		/* pid of master, for sending error signals */
int tenths;		/* length of tape used per block written */
static int caught;	/* have we caught the signal to proceed? */
static int ready;	/* have we reached the lock point without having */
			/* received the SIGUSR2 signal from the prev slave? */
static jmp_buf jmpbuf;	/* where to jump to if we are ready when the */
			/* SIGUSR2 arrives from the previous slave */

E 30
I 23
int
E 23
D 13
#ifdef RDUMP
extern int rmtape;
#endif

E 13
D 14
/*
D 13
 * Allocate tape buffer contiguous with the array of instruction packets,
 * so they can be written with a single write call in flusht().
E 13
I 13
/* Allocate tape buffer contiguous with the array of instruction
 * packets, so flusht() can write them together with one write().
 * Align tape buffer on page boundary to speed up tape write().
E 13
 */
E 14
E 9
alloctape()
{
D 14

E 14
I 13
	int pgoff = getpagesize() - 1;
I 30
	char *buf;
	int i;
E 30
I 14

E 14
E 13
	writesize = ntrec * TP_BSIZE;
I 14
D 30
	reqsiz = ntrec * sizeof(struct req);
E 30
I 30
	reqsiz = (ntrec + 1) * sizeof(struct req);
E 30
E 14
I 13
	/*
D 14
	 * 92185 NEEDS 0.4"; 92181 NEEDS 0.8" to start/stop (see TU80 manual)
E 14
I 14
	 * CDC 92181's and 92185's make 0.8" gaps in 1600-bpi start/stop mode
	 * (see DEC TU80 User's Guide).  The shorter gaps of 6250-bpi require
	 * repositioning after stopping, i.e, streaming mode, where the gap is
	 * variable, 0.30" to 0.45".  The gap is maximal when the tape stops.
E 14
	 */
D 14
	tenths = writesize/density + (cartridge ? 16 : density == 625 ? 4 : 8);

E 13
D 9
	tblock = (char (*)[TP_BSIZE])malloc(writesize);
	return (tblock != NULL);
E 9
I 9
	reqsiz = ntrec * sizeof(struct req);
E 14
I 14
D 27
	tenths = writesize/density + (cartridge ? 16 : density == 625 ? 5 : 8);
E 27
I 27
	if (blocksperfile == 0)
		tenths = writesize / density +
		    (cartridge ? 16 : density == 625 ? 5 : 8);
E 27
	/*
	 * Allocate tape buffer contiguous with the array of instruction
D 25
	 * packets, so flusht() can write them together with one write().
E 25
I 25
	 * packets, so flushtape() can write them together with one write().
E 25
	 * Align tape buffer on page boundary to speed up tape write().
	 */
E 14
D 13
	req = (struct req *)malloc(reqsiz+writesize);	/* array of packets */
	tblock = (char (*)[TP_BSIZE]) &req[ntrec];	/* Tape buffer */
	return (req != NULL);
E 13
I 13
D 30
	req = (struct req *)malloc(reqsiz + writesize + pgoff);
	if (req == NULL)
		return(0);
	tblock = (char (*)[TP_BSIZE]) (((long)&req[ntrec] + pgoff) &~ pgoff);
D 14
	req = (struct req *)tblock;
	req = &req[-ntrec];	/* Cmd packets go in front of tape buffer */
E 14
I 14
	req = (struct req *)tblock - ntrec;
E 30
I 30
	for (i = 0; i <= SLAVES; i++) {
D 35
		buf = (char *) malloc(reqsiz + writesize + pgoff + TP_BSIZE);
E 35
I 35
		buf = (char *)
		    malloc((unsigned)(reqsiz + writesize + pgoff + TP_BSIZE));
E 35
		if (buf == NULL)
D 35
		  return(0);
E 35
I 35
			return(0);
E 35
		slaves[i].tblock = (char (*)[TP_BSIZE])
		    (((long)&buf[ntrec + 1] + pgoff) &~ pgoff);
		slaves[i].req = (struct req *)slaves[i].tblock - ntrec - 1;
	}
	slp = &slaves[0];
	slp->count = 1;
	slp->tapea = 0;
	slp->firstrec = 0;
	nextblock = slp->tblock;
E 30
E 14
	return(1);
E 13
E 9
}

D 9

E 9
I 9
D 14
/*
D 13
 * Send special record to be put on tape
E 13
I 13
 * Make copy of spclrec, to later send to tape writer.
E 13
 */
E 14
I 14
D 30

E 30
I 23
void
E 23
E 14
E 9
E 6
D 25
taprec(dp)
E 25
I 25
D 37
writerec(dp)
E 37
I 37
writerec(dp, isspcl)
E 37
E 25
D 5
char *dp;
E 5
I 5
	char *dp;
I 37
	int isspcl;
E 37
E 5
{
D 8
	register i;
E 8
D 14

D 4
	for(i=0; i<BSIZE; i++)
E 4
I 4
D 5
	for(i=0; i<TP_BSIZE; i++)
E 5
I 5
D 8
	for (i=0; i < TP_BSIZE; i++)
E 5
E 4
		tblock[trecno][i] = *dp++;
E 8
I 8
D 9
	bcopy(dp, tblock[trecno], TP_BSIZE);
E 8
D 4
	tdaddr[trecno] = 0;
E 4
	trecno++;
E 9
I 9
	tmsg("taprec %d\n", trecno);
E 14
D 30
	req[trecno].dblk = (daddr_t)0;
	req[trecno].count = 1;
D 13
	*(union u_spcl *)(*tblock++) = *(union u_spcl *)dp;
E 13
I 13
	*(union u_spcl *)(*tblock++) = *(union u_spcl *)dp;	/* movc3 */
E 30
I 30

	slp->req[trecno].dblk = (daddr_t)0;
	slp->req[trecno].count = 1;
	*(union u_spcl *)(*(nextblock)++) = *(union u_spcl *)dp;
E 30
I 17
D 37
	lastspclrec = spcl.c_tapea;
E 37
I 37
	if (isspcl)
		lastspclrec = spcl.c_tapea;
E 37
E 17
	trecno++;
E 13
E 9
	spcl.c_tapea++;
D 6
	if(trecno >= NTREC)
E 6
I 6
D 9
	if(trecno >= ntrec)
E 9
I 9
D 13
	if (++trecno >= ntrec)
E 13
I 13
D 23
	if(trecno >= ntrec)
E 23
I 23
	if (trecno >= ntrec)
E 23
E 13
E 9
E 6
D 25
		flusht();
E 25
I 25
		flushtape();
E 25
}

I 23
void
E 23
D 4
tapsrec(d)
daddr_t d;
E 4
I 4
D 25
dmpblk(blkno, size)
E 25
I 25
dumpblock(blkno, size)
E 25
	daddr_t blkno;
	int size;
E 4
{
I 4
D 5
	int avail, blks;
E 5
I 5
D 9
	int avail, tpblks, dblkno;
E 9
I 9
D 14
	int tpblks, dblkno;
	register int avail;
E 14
I 14
	int avail, tpblks, dblkno;
E 14
E 9
E 5
E 4

D 4
	if(d == 0)
		return;
	tdaddr[trecno] = d;
	trecno++;
	spcl.c_tapea++;
E 4
I 4
D 5
	if (size % FRAG != 0)
E 5
I 5
D 13
	if (size % TP_BSIZE != 0)
E 5
		msg("bad size to dmpblk: %d\n", size);
E 13
D 6
	avail = NTREC - trecno;
E 6
I 6
D 9
	avail = ntrec - trecno;
E 9
E 6
D 5
	for (blks = size / TP_BSIZE; blks > avail; ) {
		bread(blkno, tblock[trecno], TP_BSIZE * avail);
E 5
I 5
	dblkno = fsbtodb(sblock, blkno);
D 9
	for (tpblks = size / TP_BSIZE; tpblks > avail; ) {
		bread(dblkno, tblock[trecno], TP_BSIZE * avail);
E 9
I 9
D 23
	tpblks = size / TP_BSIZE;
E 23
I 23
	tpblks = size >> tp_bshift;
E 23
	while ((avail = MIN(tpblks, ntrec - trecno)) > 0) {
D 14
		tmsg("dmpblk %d\n", avail);
E 14
D 30
		req[trecno].dblk = dblkno;
		req[trecno].count = avail;
E 30
I 30
		slp->req[trecno].dblk = dblkno;
		slp->req[trecno].count = avail;
E 30
I 14
		trecno += avail;
E 14
E 9
E 5
D 13
		trecno += avail;
E 13
		spcl.c_tapea += avail;
D 9
		flusht();
E 9
I 9
D 13
		if (trecno >= ntrec)
E 13
I 13
D 14
		if ((trecno += avail) >= ntrec)
E 14
I 14
		if (trecno >= ntrec)
E 14
E 13
D 25
			flusht();
E 25
I 25
			flushtape();
E 25
E 9
D 5
		blkno += avail;
		blks -= avail;
E 5
I 5
D 19
		dblkno += avail * (TP_BSIZE / DEV_BSIZE);
E 19
I 19
D 23
		dblkno += avail * (TP_BSIZE / dev_bsize);
E 23
I 23
		dblkno += avail << (tp_bshift - dev_bshift);
E 23
E 19
		tpblks -= avail;
E 5
D 6
		avail = NTREC - trecno;
E 6
I 6
D 9
		avail = ntrec - trecno;
E 9
E 6
	}
D 5
	bread(blkno, tblock[trecno], TP_BSIZE * blks);
	trecno += blks;
	spcl.c_tapea += blks;
E 5
I 5
D 9
	bread(dblkno, tblock[trecno], TP_BSIZE * tpblks);
	trecno += tpblks;
	spcl.c_tapea += tpblks;
E 5
E 4
D 6
	if(trecno >= NTREC)
E 6
I 6
	if(trecno >= ntrec)
E 6
		flusht();
E 9
}

int	nogripe = 0;

I 9
D 23
tperror() {
E 23
I 23
void
D 38
tperror()
E 38
I 38
tperror(signo)
	int signo;
E 38
{
I 30

E 30
E 23
	if (pipeout) {
D 24
		msg("Tape write error on %s\n", tape);
E 24
I 24
		msg("write error on %s\n", tape);
E 24
D 23
		msg("Cannot recover\n");
		dumpabort();
E 23
I 23
		quit("Cannot recover\n");
E 23
		/* NOTREACHED */
	}
D 14
	msg("Tape write error on tape %d\n", tapeno);
E 14
I 14
D 24
	msg("Tape write error %d feet into tape %d\n", asize/120L, tapeno);
E 14
	broadcast("TAPE ERROR!\n");
E 24
I 24
D 29
	msg("write error %d blocks into volume %d\n", blockswritten, tapeno);
E 29
I 29
	msg("write error %d blocks into volume %d\n", blocksthisvol, tapeno);
E 29
	broadcast("DUMP WRITE ERROR!\n");
E 24
	if (!query("Do you want to restart?"))
D 38
		dumpabort();
E 38
I 38
		dumpabort(0);
E 38
D 24
	msg("This tape will rewind.  After it is rewound,\n");
	msg("replace the faulty tape with a new one;\n");
E 24
I 24
	msg("Closing this volume.  Prepare to restart with new media;\n");
E 24
	msg("this dump volume will be rewritten.\n");
I 13
	killall();
E 13
	nogripe = 1;
	close_rewind();
	Exit(X_REWRITE);
}

I 23
void
E 23
D 13
senderr()
{

D 11
	perror("dump: pipe error in command to slave");
E 11
I 11
	perror("  DUMP: pipe error in command to slave");
E 11
	dumpabort();
}

E 13
D 14
#ifdef RDUMP
tflush(cnt)
	int cnt;
E 14
I 14
D 38
sigpipe()
E 38
I 38
sigpipe(signo)
	int signo;
E 38
E 14
{
I 14

D 23
	msg("Broken pipe\n");
	dumpabort();
E 23
I 23
	quit("Broken pipe\n");
E 23
}

D 25
#ifdef RDUMP
/*
 * compatibility routine
 */
E 25
I 23
D 39
void
E 39
I 39
static void
E 39
E 23
D 25
tflush(i)
E 14
	int i;
E 25
I 25
flushtape()
E 25
I 14
{
I 30
	int i, blks, got;
	long lastfirstrec;
E 30
I 26
D 39
#ifndef __STDC__
D 30
	int write();
E 30
I 30
	int write(), read();
E 30
#endif
E 39

E 26
E 14
D 25

	for (i = 0; i < ntrec; i++)
		spclrec();
}
#endif RDUMP

I 23
void
E 23
E 9
flusht()
{
E 25
D 9
	register i, si;
	daddr_t d;
E 9
I 9
D 14
	int sig, siz = (char *)tblock - (char *)req;
E 14
I 14
D 30
	int siz = (char *)tblock - (char *)req;
E 30
I 30
	int siz = (char *)nextblock - (char *)slp->req;
E 30
E 14
E 9

I 9
D 14
	tmsg("flusht %d\n", siz);
D 13
	sig = sigblock(1<<SIGINT-1 | 1<<SIGIOT-1);  /* Don't interrupt write */
	if (write(slavefd[rotor], req, siz) != siz)
		senderr();
E 13
I 13
	sig = sigblock(1 << SIGINT-1);		/* Don't abort pipe write */
	if (write(slavefd[rotor], req, siz) != siz) {
		perror("  DUMP: pipe error in command to slave");
E 14
I 14
D 23
	if (atomic(write, slavefd[rotor], req, siz) != siz) {
		perror("  DUMP: error writing command pipe");
E 14
		dumpabort();
	}
E 13
D 14
	sigsetmask(sig);
E 14
	if (++rotor >= SLAVES) rotor = 0;
E 23
I 23
D 30
	if (atomic(write, slavefd[rotor], req, siz) != siz)
E 30
I 30
	slp->req[trecno].count = 0;			/* Sentinel */

D 35
	if (atomic(write, slp->fd, slp->req, siz) != siz)
E 35
I 35
	if (atomic(write, slp->fd, (char *)slp->req, siz) != siz)
E 35
E 30
		quit("error writing command pipe: %s\n", strerror(errno));
D 30
	if (++rotor >= SLAVES)
		rotor = 0;
E 23
	tblock = (char (*)[TP_BSIZE]) &req[ntrec];
E 30
I 30
	slp->sent = 1; /* we sent a request, read the response later */

	lastfirstrec = slp->firstrec;

	if (++slp >= &slaves[SLAVES])
		slp = &slaves[0];

	/* Read results back from next slave */
	if (slp->sent) {
D 35
		if (atomic(read, slp->fd, &got, sizeof got) != sizeof got) {
E 35
I 35
		if (atomic(read, slp->fd, (char *)&got, sizeof got)
		    != sizeof got) {
E 35
			perror("  DUMP: error reading command pipe in master");
D 38
			dumpabort();
E 38
I 38
			dumpabort(0);
E 38
		}
		slp->sent = 0;

		/* Check for end of tape */
		if (got < writesize) {
			msg("End of tape detected\n");

			/*
			 * Drain the results, don't care what the values were.
			 * If we read them here then trewind won't...
			 */
			for (i = 0; i < SLAVES; i++) {
				if (slaves[i].sent) {
D 35
					if (atomic(read, slaves[i].fd, &got,
					    sizeof got) != sizeof got) {
E 35
I 35
					if (atomic(read, slaves[i].fd,
					    (char *)&got, sizeof got)
					    != sizeof got) {
E 35
						perror("  DUMP: error reading command pipe in master");
D 38
						dumpabort();
E 38
I 38
						dumpabort(0);
E 38
					}
					slaves[i].sent = 0;
				}
			}

			close_rewind();
			rollforward();
			return;
		}
	}

	blks = 0;
	if (spcl.c_type != TS_END) {
		for (i = 0; i < spcl.c_count; i++)
			if (spcl.c_addr[i] != 0)
				blks++;
	}
	slp->count = lastspclrec + blks + 1 - spcl.c_tapea;
	slp->tapea = spcl.c_tapea;
	slp->firstrec = lastfirstrec + ntrec;
	slp->inode = curino;
	nextblock = slp->tblock;
E 30
E 9
D 4
	while(trecno < NTREC)
		tdaddr[trecno++] = 1;

loop:
	d = 0;
	for(i=0; i<NTREC; i++)
		if(tdaddr[i] != 0)
		if(d == 0 || tdaddr[i] < d) {
			si = i;
			d = tdaddr[i];
		}
	if(d != 0) {
		bread(d, tblock[si], BSIZE);
		tdaddr[si] = 0;
		goto loop;
	}
E 4
	trecno = 0;
D 6
	if (write(to, tblock[0], sizeof(tblock)) != sizeof(tblock) ){
E 6
I 6
D 9
	if (write(to, tblock[0], writesize) != writesize){
I 7
		if (pipeout) {
			msg("Tape write error on %s\n", tape);
			msg("Cannot recover\n");
			dumpabort();
			/* NOTREACHED */
		}
E 7
E 6
		msg("Tape write error on tape %d\n", tapeno);
		broadcast("TAPE ERROR!\n");
		if (query("Do you want to restart?")){
			msg("This tape will rewind.  After it is rewound,\n");
			msg("replace the faulty tape with a new one;\n");
D 2
			msg("this dump volumne will be rewritten.\n");
E 2
I 2
			msg("this dump volume will be rewritten.\n");
E 2
			/*
			 *	Temporarily change the tapeno identification
			 */
			tapeno--;
			nogripe = 1;
			close_rewind();
			nogripe = 0;
			tapeno++;
			Exit(X_REWRITE);
		} else {
			dumpabort();
			/*NOTREACHED*/
		}
	}

E 9
D 6
	asize += sizeof(tblock)/density;
E 6
I 6
D 13
	asize += writesize/density;
E 6
D 9
	asize += 7;
E 9
I 9
	asize += 7;			/* inter-record gap (why fixed?) */
E 13
I 13
	asize += tenths;
E 13
E 9
D 6
	blockswritten += NTREC;
E 6
I 6
	blockswritten += ntrec;
I 29
	blocksthisvol += ntrec;
E 29
E 6
D 7
	if (asize > tsize) {
E 7
I 7
D 24
	if (!pipeout && asize > tsize) {
E 24
I 24
	if (!pipeout && (blocksperfile ?
D 29
	    (blockswritten >= blocksperfile) : (asize > tsize))) {
E 29
I 29
	    (blocksthisvol >= blocksperfile) : (asize > tsize))) {
E 29
E 24
E 7
		close_rewind();
D 25
		otape();
E 25
I 25
D 30
		startnewtape();
E 30
I 30
		startnewtape(0);
E 30
E 25
	}
	timeest();
}

I 23
void
E 23
D 22
rewind()
E 22
I 22
trewind()
E 22
{
D 9
	int	secs;
I 3
	int f;
E 9
I 9
D 13
	register int f;
E 13
I 13
	int f;
I 30
	int got;
E 30
E 13
E 9
I 7

D 35
	if (pipeout)
		return;
E 35
E 7
E 3
D 9
#ifdef DEBUG
	msg("Waiting 10 seconds to rewind.\n");
	sleep(10);
E 9
I 9
D 30
	for (f = 0; f < SLAVES; f++)
		close(slavefd[f]);
E 30
I 30
	for (f = 0; f < SLAVES; f++) {
		/*
		 * Drain the results, but unlike EOT we DO (or should) care 
		 * what the return values were, since if we detect EOT after 
		 * we think we've written the last blocks to the tape anyway, 
		 * we have to replay those blocks with rollforward.
		 *
		 * fixme: punt for now.  
		 */
		if (slaves[f].sent) {
D 35
			if (atomic(read, slaves[f].fd, &got, sizeof got)
E 35
I 35
			if (atomic(read, slaves[f].fd, (char *)&got, sizeof got)
E 35
			    != sizeof got) {
				perror("  DUMP: error reading command pipe in master");
D 38
				dumpabort();
E 38
I 38
				dumpabort(0);
E 38
			}
			slaves[f].sent = 0;
			if (got != writesize) {
				msg("EOT detected in last 2 tape records!\n");
				msg("Use a longer tape, decrease the size estimate\n");
				quit("or use no size estimate at all.\n");
			}
		}
D 35
		close(slaves[f].fd);
E 35
I 35
		(void) close(slaves[f].fd);
E 35
	}
E 30
D 23
	while (wait(NULL) >= 0)    ;	/* wait for any signals from slaves */
E 23
I 23
	while (wait((int *)NULL) >= 0)	/* wait for any signals from slaves */
		/* void */;
I 35

	if (pipeout)
		return;

E 35
E 23
D 29
	msg("Tape rewinding\n");
E 29
I 29
	msg("Closing %s\n", tape);
I 30

E 30
E 29
#ifdef RDUMP
D 14
	rmtclose();
	while (rmtopen(tape, 0) < 0)
		sleep(10);
	rmtclose();
E 9
#else
E 14
I 14
	if (host) {
		rmtclose();
		while (rmtopen(tape, 0) < 0)
			sleep(10);
		rmtclose();
		return;
	}
D 30
#endif RDUMP
E 30
I 30
#endif
E 30
E 14
D 9
	/*
	 *	It takes about 3 minutes, 25secs to rewind 2300' of tape
	 */
D 3
	secs = (( (60*3) + 25)*asize)/(2300L*12L*10L);
	msg("Waiting %d seconds to rewind.\n", secs);
	sleep(secs);
E 3
I 3
	msg("Tape rewinding\n", secs);
E 9
D 25
	close(to);
E 25
I 25
D 35
	close(tapefd);
E 35
I 35
	(void) close(tapefd);
E 35
E 25
	while ((f = open(tape, 0)) < 0)
		sleep (10);
D 35
	close(f);
E 35
I 35
	(void) close(f);
E 35
E 3
D 13
#endif
E 13
I 13
D 14
#endif RDUMP
E 14
E 13
}

I 23
void
E 23
close_rewind()
{
I 7
D 9

	if (pipeout)
		return;
E 7
	close(to);
	if (!nogripe){
		rewind();
E 9
I 9
D 22
	rewind();
E 22
I 22
	trewind();
I 29
	if (nexttape)
		return;
E 29
E 22
	if (!nogripe) {
E 9
D 24
		msg("Change Tapes: Mount tape #%d\n", tapeno+1);
		broadcast("CHANGE TAPES!\7\7\n");
E 24
I 24
		msg("Change Volumes: Mount volume #%d\n", tapeno+1);
		broadcast("CHANGE DUMP VOLUMES!\7\7\n");
E 24
	}
D 9
	do{
		if (query ("Is the new tape mounted and ready to go?"))
			break;
		if (query ("Do you want to abort?")){
E 9
I 9
D 24
	while (!query("Is the new tape mounted and ready to go?"))
E 24
I 24
D 27
	while (!query("Is the new volume mounted and ready to go?"))
E 27
I 27
D 29
	while (nexttape == 0 &&
	    !query("Is the new volume mounted and ready to go?"))
E 29
I 29
	while (!query("Is the new volume mounted and ready to go?"))
E 29
E 27
E 24
D 14
		if (query("Do you want to abort?"))
E 14
I 14
		if (query("Do you want to abort?")) {
E 14
E 9
D 38
			dumpabort();
E 38
I 38
			dumpabort(0);
E 38
I 14
			/*NOTREACHED*/
		}
E 14
D 9
			/*NOTREACHED*/
		}
	} while (1);
E 9
}

I 36
#ifdef ROLLDEBUG
int do_sum(block)
     union u_spcl *block;

{
	char sum = 0;
	int i;

	for (i = 0; i < TP_BSIZE; i++) {
		sum = sum ^ block->dummy[i];
	}
	return(sum);
}
#endif

E 36
I 30
D 35
#ifdef ROLLDEBUG
int do_sum(block)
     union u_spcl *block;

{
	char sum = 0;
	int i;

	for (i = 0; i < TP_BSIZE; i++) {
		sum = sum ^ block->dummy[i];
	}
	return(sum);
}
#endif

E 35
void
rollforward()
{
	register struct req *p, *q, *prev;
	register struct slave *tslp;
D 35
	int i, next, size, savedtapea, got;
E 35
I 35
	int i, size, savedtapea, got;
E 35
	union u_spcl *ntb, *otb;
I 36
#ifdef ROLLDEBUG
	int j; 
#endif
E 36
D 35
#ifdef ROLLDEBUG
	int j; 
#endif
E 35
	tslp = &slaves[SLAVES];
	ntb = (union u_spcl *)tslp->tblock[1];

	/*
	 * Each of the N slaves should have requests that need to 
	 * be replayed on the next tape.  Use the extra slave buffers 
	 * (slaves[SLAVES]) to construct request lists to be sent to 
	 * each slave in turn.
	 */
	for (i = 0; i < SLAVES; i++) {
		q = &tslp->req[1];
		otb = (union u_spcl *)slp->tblock;

		/*
		 * For each request in the current slave, copy it to tslp. 
		 */
I 36
#ifdef ROLLDEBUG
		printf("replaying reqs to slave %d (%d)\n", slp - &slaves[0],
		    slp->pid);
		j = 0;
#endif
E 36
D 35
#ifdef ROLLDEBUG
		printf("replaying reqs to slave %d (%d)\n", slp - &slaves[0],
		    slp->pid);
		j = 0;
#endif
E 35

I 40
		prev = NULL;
E 40
		for (p = slp->req; p->count > 0; p += p->count) {
I 36
#ifdef ROLLDEBUG
			printf("    req %d count %d dblk %d\n",
			       j++, p->count, p->dblk);
			if (p->dblk == 0)
				printf("\tsum %x\n", do_sum(otb));
#endif
E 36
D 35
#ifdef ROLLDEBUG
			printf("    req %d count %d dblk %d\n",
			       j++, p->count, p->dblk);
			if (p->dblk == 0)
				printf("\tsum %x\n", do_sum(otb));
#endif
E 35
			*q = *p;
			if (p->dblk == 0)
				*ntb++ = *otb++; /* copy the datablock also */
			prev = q;
			q += q->count;
		}
I 40
		if (prev == NULL)
			quit("rollforward: protocol botch");
E 40
		if (prev->dblk != 0)
			prev->count -= 1;
		else
			ntb--;
		q -= 1;
		q->count = 0;
		q = &tslp->req[0];
		if (i == 0) {
			q->dblk = 0;
			q->count = 1;
			trecno = 0;
			nextblock = tslp->tblock;
			savedtapea = spcl.c_tapea;
			spcl.c_tapea = slp->tapea;
			startnewtape(0);
			spcl.c_tapea = savedtapea;
			lastspclrec = savedtapea - 1;
		}
		size = (char *)ntb - (char *)q;
D 35
		if (atomic(write, slp->fd, q, size) != size) {
E 35
I 35
		if (atomic(write, slp->fd, (char *)q, size) != size) {
E 35
			perror("  DUMP: error writing command pipe");
D 38
			dumpabort();
E 38
I 38
			dumpabort(0);
E 38
		}
		slp->sent = 1;
I 36
#ifdef ROLLDEBUG
		printf("after the shift:\n");
		j = 0;
		for (p = tslp->req; p->count > 0; p += p->count) {
			printf("    req %d count %d dblk %d\n",
			       j++, p->count, p->dblk);
			if (p->dblk == 0) {
				/* dump block also */
			}
		}
#endif
E 36
D 35
#ifdef ROLLDEBUG
		printf("after the shift:\n");
		j = 0;
		for (p = tslp->req; p->count > 0; p += p->count) {
			printf("    req %d count %d dblk %d\n",
			       j++, p->count, p->dblk);
			if (p->dblk == 0) {
				/* dump block also */
			}
		}
#endif
E 35
		if (++slp >= &slaves[SLAVES])
			slp = &slaves[0];

		q->count = 1;

		if (prev->dblk != 0) {
			/*
			 * If the last one was a disk block, make the 
			 * first of this one be the last bit of that disk 
			 * block...
			 */
			q->dblk = prev->dblk +
				prev->count * (TP_BSIZE / DEV_BSIZE);
			ntb = (union u_spcl *)tslp->tblock;
		} else {
			/*
			 * It wasn't a disk block.  Copy the data to its 
			 * new location in the buffer.
			 */
			q->dblk = 0;
			*((union u_spcl *)tslp->tblock) = *ntb;
			ntb = (union u_spcl *)tslp->tblock[1];
		}
	}
	slp->req[0] = *q;
	nextblock = slp->tblock;
	if (q->dblk == 0)
		nextblock++;
	trecno = 1;

	/*
	 * Clear the first slaves' response.  One hopes that it
	 * worked ok, otherwise the tape is much too short!
	 */
	if (slp->sent) {
D 35
		if (atomic(read, slp->fd, &got, sizeof got) != sizeof got) {
E 35
I 35
		if (atomic(read, slp->fd, (char *)&got, sizeof got)
		    != sizeof got) {
E 35
			perror("  DUMP: error reading command pipe in master");
D 38
			dumpabort();
E 38
I 38
			dumpabort(0);
E 38
		}
		slp->sent = 0;

		if (got != writesize) {
			quit("EOT detected at start of the tape!\n");
		}
	}
}

E 30
/*
D 9
 *	We implement taking and restoring checkpoints on
 *	the tape level.
E 9
I 9
D 30
 *	We implement taking and restoring checkpoints on the tape level.
E 9
 *	When each tape is opened, a new process is created by forking; this
 *	saves all of the necessary context in the parent.  The child
 *	continues the dump; the parent waits around, saving the context.
 *	If the child returns X_REWRITE, then it had problems writing that tape;
 *	this causes the parent to fork again, duplicating the context, and
 *	everything continues as if nothing had happened.
E 30
I 30
 * We implement taking and restoring checkpoints on the tape level.
 * When each tape is opened, a new process is created by forking; this
 * saves all of the necessary context in the parent.  The child
 * continues the dump; the parent waits around, saving the context.
 * If the child returns X_REWRITE, then it had problems writing that tape;
 * this causes the parent to fork again, duplicating the context, and
 * everything continues as if nothing had happened.
E 30
 */
D 30

E 30
I 23
void
E 23
D 25
otape()
E 25
I 25
D 30
startnewtape()
E 30
I 30
startnewtape(top)
	int top;
E 30
E 25
{
	int	parentpid;
	int	childpid;
	int	status;
	int	waitpid;
D 9
	int	sig_ign_parent();
E 9
D 13
	int	interrupt();
E 13
I 13
D 14
	int	(*interrupt)();
E 14
I 14
D 21
	int	(*interrupt)() = signal(SIGINT, SIG_IGN);
E 21
I 21
D 32
	sig_t	interrupt;
E 32
E 21
I 17
D 30
	int	blks, i;
E 30
I 30
D 35
	int	i;
E 35
E 30
I 27
	char	*p;
I 32
#ifdef sunos
D 35
	void	(*interrupt)();
E 35
I 35
	void	(*interrupt_save)();
E 35
D 39
	char	*index();
E 39
#else
D 35
	sig_t	interrupt;
E 35
I 35
	sig_t	interrupt_save;
E 35
#endif
E 32
E 27
E 17
E 14
E 13

I 21
D 35
	interrupt = signal(SIGINT, SIG_IGN);
E 35
I 35
	interrupt_save = signal(SIGINT, SIG_IGN);
E 35
E 21
D 9
	/*
	 *	Force the tape to be closed
	 */
	close(to);
E 9
	parentpid = getpid();

D 39
    restore_check_point:
E 39
I 39
restore_check_point:
E 39
D 13
	signal(SIGINT, interrupt);
	/*
	 *	All signals are inherited...
	 */
E 13
I 13
D 14
	interrupt = signal(SIGINT, SIG_IGN);
E 14
I 14
D 21
	signal(SIGINT, interrupt);
E 21
I 21
D 35
	(void)signal(SIGINT, interrupt);
E 35
I 35
	(void)signal(SIGINT, interrupt_save);
E 35
E 21
	/*
	 *	All signals are inherited...
	 */
E 14
E 13
	childpid = fork();
D 9
	if (childpid < 0){
E 9
I 9
	if (childpid < 0) {
E 9
		msg("Context save fork fails in parent %d\n", parentpid);
		Exit(X_ABORT);
	}
D 9
	if (childpid != 0){
E 9
I 9
	if (childpid != 0) {
E 9
		/*
		 *	PARENT:
		 *	save the context by waiting
		 *	until the child doing all of the work returns.
D 9
		 *	don't catch the interrupt 
E 9
I 9
		 *	don't catch the interrupt
E 9
		 */
I 14
		signal(SIGINT, SIG_IGN);
E 14
D 13
		signal(SIGINT, SIG_IGN);
E 13
#ifdef TDEBUG
		msg("Tape: %d; parent process: %d child process %d\n",
			tapeno+1, parentpid, childpid);
D 39
#endif TDEBUG
E 39
I 39
#endif /* TDEBUG */
E 39
D 9
		for (;;){
			waitpid = wait(&status);
			if (waitpid != childpid){
				msg("Parent %d waiting for child %d has another child %d return\n",
					parentpid, childpid, waitpid);
			} else
				break;
		}
		if (status & 0xFF){
E 9
I 9
		while ((waitpid = wait(&status)) != childpid)
			msg("Parent %d waiting for child %d has another child %d return\n",
				parentpid, childpid, waitpid);
		if (status & 0xFF) {
E 9
			msg("Child %d returns LOB status %o\n",
				childpid, status&0xFF);
		}
		status = (status >> 8) & 0xFF;
#ifdef TDEBUG
D 9
		switch(status){
E 9
I 9
		switch(status) {
E 9
			case X_FINOK:
				msg("Child %d finishes X_FINOK\n", childpid);
				break;
D 30
			case X_ABORT:
E 30
I 30
			case X_ABORT:	
E 30
				msg("Child %d finishes X_ABORT\n", childpid);
				break;
			case X_REWRITE:
				msg("Child %d finishes X_REWRITE\n", childpid);
				break;
			default:
D 9
				msg("Child %d finishes unknown %d\n", childpid,status);
E 9
I 9
				msg("Child %d finishes unknown %d\n",
D 14
				    childpid, status);
E 14
I 14
					childpid, status);
E 14
E 9
				break;
		}
D 39
#endif TDEBUG
E 39
I 39
#endif /* TDEBUG */
E 39
D 9
		switch(status){
E 9
I 9
		switch(status) {
E 9
			case X_FINOK:
				Exit(X_FINOK);
			case X_ABORT:
				Exit(X_ABORT);
			case X_REWRITE:
				goto restore_check_point;
			default:
				msg("Bad return code from dump: %d\n", status);
				Exit(X_ABORT);
		}
		/*NOTREACHED*/
	} else {	/* we are the child; just continue */
#ifdef TDEBUG
		sleep(4);	/* allow time for parent's message to get out */
		msg("Child on Tape %d has parent %d, my pid = %d\n",
			tapeno+1, parentpid, getpid());
D 14
#endif
I 13
		signal(SIGINT, interrupt);
E 14
I 14
D 39
#endif TDEBUG
E 39
I 39
#endif /* TDEBUG */
E 39
I 27
		/*
		 * If we have a name like "/dev/rmt0,/dev/rmt1",
		 * use the name before the comma first, and save
D 29
		 * the second name for next time.
E 29
I 29
		 * the remaining names for subsequent volumes.
E 29
		 */
D 29
		if (nexttape && *nexttape)
			tape = nexttape;
		if (p = index(tape, ',')) {
			*p = '\0';
			nexttape = p + 1;
		} else
			nexttape = NULL;
E 29
I 29
D 30
		tapeno++;		/* current tape sequence */
E 30
I 30
		tapeno++;               /* current tape sequence */
E 30
D 43
		if (nexttape || index(tape, ',')) {
E 43
I 43
		if (nexttape || strchr(tape, ',')) {
E 43
			if (nexttape && *nexttape)
				tape = nexttape;
D 40
			if (p = index(tape, ',')) {
E 40
I 40
D 43
			if ((p = index(tape, ',')) != NULL) {
E 43
I 43
			if ((p = strchr(tape, ',')) != NULL) {
E 43
E 40
				*p = '\0';
				nexttape = p + 1;
			} else
				nexttape = NULL;
			msg("Dumping volume %d on %s\n", tapeno, tape);
		}
E 29
E 27
E 14
E 13
D 9
		do{
D 7
			to = creat(tape, 0666);
E 7
I 7
			if (pipeout)
				to = 1;
			else
				to = creat(tape, 0666);
E 7
			if (to < 0) {
				if (!query("Cannot open tape. Do you want to retry the open?"))
					dumpabort();
			} else break;
		} while (1);
E 9
I 9
#ifdef RDUMP
D 14
		while ((to = rmtopen(tape, 2)) < 0)
#else
E 14
I 14
D 25
		while ((to = (host ? rmtopen(tape, 2) :
			pipeout ? 1 : creat(tape, 0666))) < 0)
E 25
I 25
		while ((tapefd = (host ? rmtopen(tape, 2) :
			pipeout ? 1 : open(tape, O_WRONLY|O_CREAT, 0666))) < 0)
E 25
D 30
#else RDUMP
E 14
D 25
		while ((to = pipeout ? 1 : creat(tape, 0666)) < 0)
E 25
I 25
		while ((tapefd =
			pipeout ? 1 : open(tape, O_WRONLY|O_CREAT, 0666)) < 0)
E 25
D 13
#endif
E 13
I 13
#endif RDUMP
E 30
I 30
#else
		while ((tapefd = (pipeout ? 1 : 
				  open(tape, O_WRONLY|O_CREAT, 0666))) < 0)
#endif
E 30
E 13
D 20
			if (!query("Cannot open tape.  Do you want to retry the open?"))
E 20
I 20
		    {
D 24
			msg("Cannot open tape \"%s\".\n", tape);
E 24
I 24
			msg("Cannot open output \"%s\".\n", tape);
E 24
			if (!query("Do you want to retry the open?"))
E 20
D 38
				dumpabort();
E 38
I 38
				dumpabort(0);
E 38
I 20
		}
E 20
E 9

I 9
		enslave();  /* Share open tape file descriptor with slaves */

E 9
		asize = 0;
D 29
		tapeno++;		/* current tape sequence */
E 29
I 29
		blocksthisvol = 0;
E 29
D 30
		newtape++;		/* new tape signal */
I 17
		blks = 0;
		if (spcl.c_type != TS_END)
			for (i = 0; i < spcl.c_count; i++)
				if (spcl.c_addr[i] != 0)
					blks++;
		spcl.c_count = blks + 1 - spcl.c_tapea + lastspclrec;
E 30
I 30
		if (top)
			newtape++;		/* new tape signal */
		spcl.c_count = slp->count; 
		/*
		 * measure firstrec in TP_BSIZE units since restore doesn't
		 * know the correct ntrec value...
		 */
		spcl.c_firstrec = slp->firstrec;
E 30
E 17
		spcl.c_volume++;
		spcl.c_type = TS_TAPE;
I 18
		spcl.c_flags |= DR_NEWHEADER;
E 18
D 25
		spclrec();
E 25
I 25
D 30
		writeheader(curino);
E 30
I 30
D 35
		writeheader(slp->inode);
E 35
I 35
		writeheader((ino_t)slp->inode);
E 35
E 30
E 25
I 18
		spcl.c_flags &=~ DR_NEWHEADER;
E 18
		if (tapeno > 1)
D 25
			msg("Tape %d begins with blocks from ino %d\n",
				tapeno, ino);
E 25
I 25
D 29
			msg("Tape %d begins with blocks from inode %d\n",
E 29
I 29
			msg("Volume %d begins with blocks from inode %d\n",
E 29
D 30
				tapeno, curino);
E 30
I 30
				tapeno, slp->inode);
E 30
E 25
	}
}

I 23
void
E 23
D 9
/*
 *	The parent still catches interrupts, but does nothing with them
 */
sig_ign_parent()
{
	msg("Waiting parent receives interrupt\n");
	signal(SIGINT, sig_ign_parent);
}

E 9
D 38
dumpabort()
E 38
I 38
dumpabort(signo)
	int signo;
E 38
{
I 30

E 30
I 9
	if (master != 0 && master != getpid())
D 13
		kill(master, SIGIOT);
E 9
D 2
	msg("The ENTIRE dump is aborted.  NO second chances (tough luck sucker).\n");
E 2
I 2
	msg("The ENTIRE dump is aborted.\n");
E 13
I 13
D 14
		kill(master, SIGPIPE);
E 14
I 14
D 35
		kill(master, SIGTERM);	/* Signals master to call dumpabort */
E 35
I 35
		/* Signals master to call dumpabort */
		(void) kill(master, SIGTERM);
E 35
E 14
	else {
		killall();
		msg("The ENTIRE dump is aborted.\n");
	}
I 42
#ifdef RDUMP
	rmtclose();
#endif
E 42
E 13
E 2
	Exit(X_ABORT);
}

I 23
D 39
void
E 39
I 39
__dead void
E 39
E 23
Exit(status)
I 22
	int status;
E 22
{
I 30

E 30
#ifdef TDEBUG
	msg("pid = %d exits with status %d\n", getpid(), status);
D 39
#endif TDEBUG
D 2
	henryexit(status);
}

#ifdef TDEBUG
exit(status)
	/*ARGSUSED*/
{
	fflush(stdout);
	fprintf(stderr, "Somebody called exit: halt executed\n");
	fflush(stderr);
	abort();
}

_exit(status)
	/*ARGSUSED*/
{
	fflush(stdout);
	fprintf(stderr, "Somebody called _exit: halt executed\n");
	fflush(stderr);
	abort();
}
#endif TDEBUG

henryexit(status)
	/* ARGSUSED */
{
	_cleanup();
	asm("	chmk	$1");
	asm("halt");
E 2
I 2
D 35
	exit(status);
E 35
I 35
	(void) exit(status);
E 39
I 39
#endif /* TDEBUG */
	exit(status);
E 39
E 35
I 9
}

D 13
#define OK 020
char tok = OK;
E 13
I 13
/*
D 14
 * prefer pipe(), but flock() barfs on them
E 14
I 14
D 30
 * could use pipe() for this if flock() worked on pipes
E 30
I 30
 * proceed - handler for SIGUSR2, used to synchronize IO between the slaves.
E 30
E 14
 */
I 23
void
E 23
D 30
lockfile(fd)
	int fd[2];
E 30
I 30
D 38
proceed()
E 38
I 38
proceed(signo)
	int signo;
E 38
E 30
{
D 30
	char tmpname[20];
E 30
E 13

I 13
D 20
	strcpy(tmpname, "/tmp/dumplockXXXXXX");
E 20
I 20
D 30
	strcpy(tmpname, _PATH_LOCK);
E 20
	mktemp(tmpname);
D 15
	if ((fd[1] = creat(tmpname, 0400)) < 0)
		return(fd[1]);
	fd[0] = open(tmpname, 0);
E 15
I 15
D 23
	if ((fd[1] = creat(tmpname, 0400)) < 0) {
		msg("Could not create lockfile ");
		perror(tmpname);
		dumpabort();
	}
	if ((fd[0] = open(tmpname, 0)) < 0) {
		msg("Could not reopen lockfile ");
		perror(tmpname);
		dumpabort();
	}
E 15
	unlink(tmpname);
E 23
I 23
	if ((fd[1] = creat(tmpname, 0400)) < 0)
		quit("cannot create lockfile %s: %s\n",
		    tmpname, strerror(errno));
	if ((fd[0] = open(tmpname, 0)) < 0)
		quit("cannot reopen lockfile %s: %s\n",
		    tmpname, strerror(errno));
	(void) unlink(tmpname);
E 30
I 30
	if (ready)
		longjmp(jmpbuf, 1);
	caught++;
E 30
E 23
D 15
	return (fd[0] < 0 ? fd[0] : 0);
E 15
}

I 23
void
E 23
E 13
enslave()
{
D 13
	int prev[2], next[2], cmd[2];	/* file descriptors for pipes */
D 11
	int i, j, slavepid;
E 11
I 11
	int i, j, ret, slavepid;
E 13
I 13
D 30
	int first[2], prev[2], next[2], cmd[2];     /* file descriptors */
E 30
I 30
	int cmd[2];
E 30
	register int i, j;
E 13
E 11

	master = getpid();
D 13
	signal(SIGPIPE, dumpabort);
	signal(SIGIOT, tperror); /* SIGIOT asks for restart from checkpoint */
	pipe(prev);
	for (i = rotor = 0; i < SLAVES; ++i) {
		if ((i < SLAVES - 1 && pipe(next) < 0) || pipe(cmd) < 0
				|| (slavepid = fork()) < 0) {
			perror("  DUMP: too many slaves");
E 13
I 13
D 14
	signal(SIGPIPE, dumpabort);  /* Slave quit/died/killed -> abort */
	signal(SIGIOT, tperror);     /* SIGIOT -> restart from checkpoint */
E 14
I 14
D 30
	signal(SIGTERM, dumpabort); /* Slave sends SIGTERM on dumpabort() */
E 30
I 30

	signal(SIGTERM, dumpabort);  /* Slave sends SIGTERM on dumpabort() */
E 30
	signal(SIGPIPE, sigpipe);
	signal(SIGUSR1, tperror);    /* Slave sends SIGUSR1 on tape errors */
E 14
D 30
	lockfile(first);
E 30
I 30
	signal(SIGUSR2, proceed);    /* Slave sends SIGUSR2 to next slave */

E 30
	for (i = 0; i < SLAVES; i++) {
D 30
		if (i == 0) {
			prev[0] = first[1];
			prev[1] = first[0];
E 30
I 30
		if (i == slp - &slaves[0]) {
			caught = 1;
E 30
		} else {
D 30
			prev[0] = next[0];
			prev[1] = next[1];
			flock(prev[1], LOCK_EX);
E 30
I 30
			caught = 0;
E 30
		}
D 15
		next[0] = first[0];
		next[1] = first[1];	    /* Last slave loops back */
		if ((i < SLAVES-1 && lockfile(next) < 0) || pipe(cmd) < 0
				|| (slavepid[i] = fork()) < 0) {
			perror("  DUMP: too many slaves (recompile smaller)");
E 15
I 15
D 30
		if (i < SLAVES - 1) {
			lockfile(next);
		} else {
			next[0] = first[0];
			next[1] = first[1];	    /* Last slave loops back */
		}
D 23
		if (pipe(cmd) < 0 || (slavepid[i] = fork()) < 0) {
			msg("too many slaves, %d (recompile smaller) ", i);
			perror("");
E 15
E 13
			dumpabort();
		}
E 23
I 23
		if (pipe(cmd) < 0 || (slavepid[i] = fork()) < 0)
E 30
I 30

		if (socketpair(AF_UNIX, SOCK_STREAM, 0, cmd) < 0 ||
		    (slaves[i].pid = fork()) < 0)
E 30
			quit("too many slaves, %d (recompile smaller): %s\n",
			    i, strerror(errno));
E 23
D 13
		if (i >= SLAVES - 1)
			next[1] = prev[1];	    /* Last slave loops back */
E 13
D 30
		slavefd[i] = cmd[1];
D 13
		if (slavepid == 0) {		    /* Slave starts up here */
E 13
I 13
D 14
		if (slavepid[i] == 0) {		    /* Slave starts up here */
E 14
I 14
		if (slavepid[i] == 0) { 	    /* Slave starts up here */
E 30
I 30

		slaves[i].fd = cmd[1];
		slaves[i].sent = 0;
		if (slaves[i].pid == 0) { 	    /* Slave starts up here */
E 30
E 14
E 13
			for (j = 0; j <= i; j++)
D 30
				close(slavefd[j]);
E 30
I 30
D 35
			        close(slaves[j].fd);
E 35
I 35
			        (void) close(slaves[j].fd);
E 35
E 30
D 13
			if (i < SLAVES - 1) {
				close(prev[1]);
				close(next[0]);
			} else {		    /* Insert initial token */
D 11
				if (write(next[1], &tok, 1) != 1)
					ringerr();
E 11
I 11
				if ((ret = write(next[1], &tok, 1)) != 1)
					ringerr(ret, "cannot start token");
E 11
			}
			doslave(i, cmd[0], prev[0], next[1]);
			close(next[1]);
			j = read(prev[0], &tok, 1);   /* Eat the final token */
#ifdef RDUMP				    /* Read remaining acknowledges */
			for (; j > 0 && (tok &~ OK) > 0; tok--) {
				if (rmtwrite2() != writesize && (tok & OK)) {
					kill(master, SIGIOT);
					tok &= ~OK;
				}
			}
#endif
E 13
I 13
D 14
			signal(SIGINT, SIG_IGN);     /* Master handles these */
			signal(SIGTERM, SIG_IGN);
			doslave(i, cmd[0], prev, next);
E 14
I 14
			signal(SIGINT, SIG_IGN);    /* Master handles this */
D 30
			doslave(cmd[0], prev, next);
E 30
I 30
			doslave(cmd[0], i);
E 30
E 14
E 13
			Exit(X_FINOK);
		}
D 30
		close(cmd[0]);
D 13
		close(next[1]);
		close(prev[0]);
		prev[0] = next[0];
E 13
I 13
		if (i > 0) {
			close(prev[0]);
			close(prev[1]);
		}
E 30
E 13
	}
D 13
	master = 0;
E 13
I 13
D 30
	close(first[0]);
	close(first[1]);
	master = 0; rotor = 0;
E 30
I 30
	
	for (i = 0; i < SLAVES; i++)
D 35
		atomic(write, slaves[i].fd, &slaves[(i + 1) % SLAVES].pid, 
		       sizeof slaves[0].pid);
E 35
I 35
		(void) atomic(write, slaves[i].fd, 
			      (char *) &slaves[(i + 1) % SLAVES].pid, 
		              sizeof slaves[0].pid);
E 35
		
	master = 0; 
E 30
E 13
}

I 23
void
E 23
D 13
/*
 * Somebody must have died, should never happen
 */
D 11
ringerr()
E 11
I 11
ringerr(code, msg, a1, a2)
	int code;
	char *msg;
	int a1, a2;
E 13
I 13
killall()
E 13
E 11
{
D 11
	perror("  DUMP: token passing error");
E 11
I 11
D 13
	char buf[BUFSIZ];
E 13
I 13
	register int i;
E 13

D 13
	fprintf(stderr, "  DUMP: ");
	sprintf(buf, msg, a1, a2);
	if (code < 0)
		perror(msg);
	else if (code == 0)
		fprintf(stderr, "%s: unexpected EOF\n", buf);
	else
		fprintf(stderr, "%s: code %d\n", buf, code);
E 11
	kill(master, SIGPIPE);
	Exit(X_ABORT);
E 13
I 13
	for (i = 0; i < SLAVES; i++)
D 30
		if (slavepid[i] > 0)
			kill(slavepid[i], SIGKILL);
E 30
I 30
		if (slaves[i].pid > 0)
D 35
			kill(slaves[i].pid, SIGKILL);
E 35
I 35
			(void) kill(slaves[i].pid, SIGKILL);
E 35
E 30
E 13
}

I 11
D 13
int childnum;
sigpipe()
E 13
I 13
/*
 * Synchronization - each process has a lockfile, and shares file
 * descriptors to the following process's lockfile.  When our write
 * completes, we release our lock on the following process's lock-
 * file, allowing the following process to lock it and proceed. We
 * get the lock back for the next cycle by swapping descriptors.
 */
I 23
D 39
void
E 39
I 39
static void
E 39
E 23
D 14
doslave(mynum,cmd,prev,next)
	int mynum, cmd, prev[2], next[2];
E 14
I 14
D 30
doslave(cmd, prev, next)
	register int cmd, prev[2], next[2];
E 30
I 30
doslave(cmd, slave_number)
	register int cmd;
        int slave_number;
E 30
E 14
E 13
{
I 13
D 14
	register int toggle = 0, firstdone = mynum;
E 14
I 14
D 30
	register int nread, toggle = 0;
I 29
	int nwrite;
E 30
I 30
	register int nread;
	int nextslave, size, wrote, eot_count;
E 30
E 29
I 26
D 39
#ifndef __STDC__
	int read();
#endif
E 39
I 36
#ifdef ROLLDEBUG
	int dodump = 2;
	FILE *out;
	char name[64];
#endif
E 36
I 30
D 35
#ifdef ROLLDEBUG
	int dodump = 2;
	FILE *out;
	char name[64];
#endif
E 35
E 30
E 26
E 14
E 13

D 13
	ringerr(childnum, "SIGPIPE raised");
}

E 11
doslave(num, cmd, prev, next)
	int num, cmd, prev, next;
{
I 11
	int ret;

E 11
	tmsg("slave %d\n", num);
	signal(SIGINT, SIG_IGN); 		/* Master handles it */
	signal(SIGTERM, SIG_IGN);
D 11
	signal(SIGPIPE, ringerr);
E 11
I 11
	signal(SIGPIPE, sigpipe);
	childnum = num;
E 13
I 13
D 14
	tmsg("slave %d\n", mynum);
E 14
E 13
E 11
D 25
	close(fi);
D 14
	if ((fi = open(disk, 0)) < 0) {		/* Need our own seek pointer */
E 14
I 14
D 23
	if ((fi = open(disk, 0)) < 0) { 	/* Need our own seek pointer */
E 14
D 13
		perror("  DUMP: can't reopen disk");
		kill(master, SIGPIPE);
E 13
I 13
		perror("  DUMP: slave couldn't reopen disk");
D 14
		kill(master, SIGPIPE);		/* dumpabort */
E 13
		Exit(X_ABORT);
E 14
I 14
		dumpabort();
E 14
	}
E 23
I 23
	if ((fi = open(disk, 0)) < 0) 	/* Need our own seek pointer */
E 25
I 25
	/*
	 * Need our own seek pointer.
	 */
D 35
	close(diskfd);
E 35
I 35
	(void) close(diskfd);
E 35
	if ((diskfd = open(disk, O_RDONLY)) < 0)
E 25
		quit("slave couldn't reopen disk: %s\n", strerror(errno));
I 30

E 30
E 23
D 10
	while (read(cmd, req, reqsiz) == reqsiz) {
E 10
I 10
D 11
	while (readpipe(cmd, req, reqsiz) == reqsiz) {
E 11
I 11
D 13
	while ((ret = readpipe(cmd, req, reqsiz)) == reqsiz) {
E 13
I 13
	/*
I 30
	 * Need the pid of the next slave in the loop...
	 */
D 35
	if ((nread = atomic(read, cmd, &nextslave, sizeof nextslave))
E 35
I 35
	if ((nread = atomic(read, cmd, (char *)&nextslave, sizeof nextslave))
E 35
	    != sizeof nextslave) {
		quit("master/slave protocol botched - didn't get pid of next slave.\n");
	}

I 36
#ifdef ROLLDEBUG
	sprintf(name, "slave.%d", slave_number);
	out = fopen(name, "w");
#endif
E 36
D 35
#ifdef ROLLDEBUG
	sprintf(name, "slave.%d", slave_number);
	out = fopen(name, "w");
#endif
E 35
	/*
E 30
D 14
	 * Get list of blocks to dump
E 14
I 14
	 * Get list of blocks to dump, read the blocks into tape buffer
E 14
	 */
D 14
	while (readpipe(cmd, req, reqsiz) > 0) {
E 14
I 14
D 30
	while ((nread = atomic(read, cmd, req, reqsiz)) == reqsiz) {
E 14
E 13
E 11
E 10
		register struct req *p = req;
		for (trecno = 0; trecno < ntrec; trecno += p->count, p += p->count) {
E 30
I 30
D 35
	while ((nread = atomic(read, cmd, slp->req, reqsiz)) == reqsiz) {
E 35
I 35
	while ((nread = atomic(read, cmd, (char *)slp->req, reqsiz)) == reqsiz) {
E 35
		register struct req *p = slp->req;
I 36
#ifdef ROLLDEBUG
		int req_count = 0;
#endif
E 36
D 35
		int j;
		struct req *rover;
		char (*orover)[TP_BSIZE];
E 35

D 35
		j = 0;
E 35
		for (trecno = 0; trecno < ntrec;
		     trecno += p->count, p += p->count) {
E 30
			if (p->dblk) {
D 13
				tmsg("%d READS %d\n", num, p->count);
E 13
I 13
D 14
				tmsg("%d READS %d\n", mynum, p->count);
E 14
E 13
D 30
				bread(p->dblk, tblock[trecno],
E 30
I 30
				bread(p->dblk, slp->tblock[trecno],
E 30
D 14
				    p->count * TP_BSIZE);
E 14
I 14
					p->count * TP_BSIZE);
E 14
			} else {
D 13
				tmsg("%d PIPEIN %d\n", num, p->count);
				if (p->count != 1)
D 11
					ringerr();
E 11
I 11
					ringerr(11, "%d PIPEIN %d", num,
						p->count);
E 11
D 10
				if (read(cmd, tblock[trecno], TP_BSIZE) != TP_BSIZE)
E 10
I 10
				if (readpipe(cmd, tblock[trecno], TP_BSIZE) != TP_BSIZE)
E 10
					senderr();
E 13
I 13
D 14
				tmsg("%d PIPEIN %d\n", mynum, p->count);
				if (p->count != 1 ||
				    readpipe(cmd, tblock[trecno], TP_BSIZE) <= 0) {
E 14
I 14
				if (p->count != 1 || atomic(read, cmd,
D 23
				    tblock[trecno], TP_BSIZE) != TP_BSIZE) {
E 14
D 16
					msg("Master/slave protocol botched");
E 16
I 16
					msg("Master/slave protocol botched.\n");
E 16
					dumpabort();
				}
E 23
I 23
D 30
				    tblock[trecno], TP_BSIZE) != TP_BSIZE)
E 30
I 30
D 35
				    slp->tblock[trecno], TP_BSIZE) != TP_BSIZE)
E 30
					quit("master/slave protocol botched.\n");
E 35
I 35
				    (char *)slp->tblock[trecno], 
				    TP_BSIZE) != TP_BSIZE)
				       quit("master/slave protocol botched.\n");
E 35
E 23
E 13
			}
I 36
#ifdef ROLLDEBUG
			if (dodump) {
				(void) fprintf(out, "    req %d count %d dblk %d\n",
					req_count++, p->count, p->dblk);
				if (p->dblk == 0) {
					(void) fprintf(out, "\tsum %x\n",
						do_sum(slp->tblock[trecno]));
				}
			}
#endif
E 36
I 30
D 35
#ifdef ROLLDEBUG
			if (dodump) {
				fprintf(out, "    req %d count %d dblk %d\n",
					j++, p->count, p->dblk);
				if (p->dblk == 0) {
					fprintf(out, "\tsum %x\n",
						do_sum(slp->tblock[trecno]));
				}
			}
#endif
E 35
E 30
		}
I 36
#ifdef ROLLDEBUG
		if (dodump) {
			(void) fprintf(out, "\n");
		}
		if (--dodump == 0) {
			(void) fclose(out);
		}
#endif
E 36
D 11
		if (read(prev, &tok, 1) != 1)
			ringerr();	/* Wait your turn */
E 11
I 11
D 13
		if ((ret = read(prev, &tok, 1)) != 1)
			ringerr(ret, "read token");	/* Wait your turn */
E 11
		tmsg("%d WRITE\n", num);
E 13
I 13
D 30
		flock(prev[toggle], LOCK_EX);	/* Wait our turn */
E 30
I 30
D 35
#ifdef ROLLDEBUG
		if (dodump) {
			fprintf(out, "\n");
		}
		if (--dodump == 0) {
			fclose(out);
		}
#endif
E 35
		if (setjmp(jmpbuf) == 0) {
			ready = 1;
			if (!caught)
D 35
				pause();
E 35
I 35
				(void) pause();
E 35
		}
		ready = 0;
		caught = 0;
E 30
D 14
		tmsg("%d WRITE\n", mynum);
E 14
I 14

I 30
		/* Try to write the data... */
		eot_count = 0;
		size = 0;

		while (eot_count < 10 && size < writesize) {
E 30
E 14
E 13
#ifdef RDUMP
D 13
		if (tok & OK) {
			rmtwrite0(writesize);
			rmtwrite1(tblock[0], writesize);
			tok++;		/* Number of writes in progress */
		}
		if (tok > (LAG|OK) && (--tok, rmtwrite2() != writesize)) {
E 13
I 13
D 14
#ifndef sun	/* Defer checking first write until next one is started */
		rmtwrite0(writesize);
		rmtwrite1(tblock[0],writesize);
		if (firstdone == 0) firstdone = -1;
		else if (rmtwrite2() != writesize) {
			rmtwrite2();		/* Don't care if another err */
E 13
#else
D 13
		if ((tok & OK) &&
		    write(to, tblock[0], writesize) != writesize) {
E 13
I 13
		/* Asynchronous writes can hang Suns; do it synchronously */
		if (rmtwrite(tblock[0],writesize) != writesize) {
#endif sun
#else		/* Local tape drive */
		if (write(to,tblock[0],writesize) != writesize) {
E 13
			perror(tape);
E 14
I 14
D 29
		if ((host ? rmtwrite(tblock[0], writesize)
D 25
			: write(to, tblock[0], writesize)) != writesize) {
E 25
I 25
			: write(tapefd, tblock[0], writesize)) != writesize) {
E 29
I 29
D 30
		if ((nwrite = (host ? rmtwrite(tblock[0], writesize)
			: write(tapefd, tblock[0], writesize))) != writesize) {
E 29
E 25
#else RDUMP
D 25
		if (write(to, tblock[0], writesize) != writesize) {
E 25
I 25
D 29
		if (write(tapefd, tblock[0], writesize) != writesize) {
E 29
I 29
		if ((nwrite = write(tapefd, tblock[0], writesize))
		    != writesize) {
E 29
E 25
E 14
D 13
#endif
E 13
I 13
#endif RDUMP
I 29
			if (nwrite == -1) 
				perror("write");
E 30
I 30
			if (host)
				wrote = rmtwrite(slp->tblock[0]+size,
				    writesize-size);
E 30
			else
D 30
				msg("short write: got %d instead of %d\n",
				    nwrite, writesize);
E 30
I 30
#endif
				wrote = write(tapefd, slp->tblock[0]+size,
				    writesize-size);
#ifdef WRITEDEBUG
			printf("slave %d wrote %d\n", slave_number, wrote);
#endif
			if (wrote < 0) 
				break;
			if (wrote == 0)
				eot_count++;
			size += wrote;
		}

#ifdef WRITEDEBUG
		if (size != writesize) 
		 printf("slave %d only wrote %d out of %d bytes and gave up.\n",
		     slave_number, size, writesize);
#endif

		if (eot_count > 0)
			size = 0;

		/*
		 * fixme: Pyramids running OSx return ENOSPC
		 * at EOT on 1/2 inch drives.
		 */
		if (size < 0) {
E 30
E 29
E 13
D 14
			kill(master, SIGIOT);	/* restart from checkpoint */
D 13
			tok &= ~OK;
E 13
I 13
			for (;;) sigpause(0);
E 14
I 14
D 35
			kill(master, SIGUSR1);
E 35
I 35
			(void) kill(master, SIGUSR1);
E 35
			for (;;)
D 35
				sigpause(0);
E 35
I 35
				(void) sigpause(0);
E 35
E 14
E 13
D 30
		}
D 11
		if (write(next, &tok, 1) != 1)
			ringerr(); /* Next slave's turn */
E 11
I 11
D 13
		if ((ret = write(next, &tok, 1)) != 1)
			ringerr(ret, "write token"); /* Next slave's turn */
E 13
I 13
		toggle ^= 1;
		flock(next[toggle], LOCK_UN);	/* Next slave's turn */
	}					/* Also jolts him awake */
E 30
I 30
		} else {
			/*
			 * pass size of write back to master
			 * (for EOT handling)
			 */
D 35
			atomic(write, cmd, &size, sizeof size);
E 35
I 35
			(void) atomic(write, cmd, (char *)&size, sizeof size);
E 35
		} 

		/*
		 * If partial write, don't want next slave to go.
		 * Also jolts him awake.
		 */
D 35
		kill(nextslave, SIGUSR2);
E 35
I 35
		(void) kill(nextslave, SIGUSR2);
E 35
	}
E 30
D 14
#ifdef RDUMP			/* One more time around, to check last write */
#ifndef sun
	flock(prev[toggle], LOCK_EX);
	tmsg("%d LAST\n", mynum);
	if (firstdone < 0 && rmtwrite2() != writesize) {
		kill(master, SIGIOT);
		for (;;)
			sigpause(0);
E 14
I 14
D 23
	if (nread != 0) {
		perror("  DUMP: error reading command pipe");
		dumpabort();
E 14
E 13
E 11
	}
E 23
I 23
	if (nread != 0)
		quit("error reading command pipe: %s\n", strerror(errno));
E 23
I 11
D 13
	if (ret != 0)
		ringerr(ret, "partial record?");
E 11
	tmsg("%d CLOSE\n", num);
E 13
I 13
D 14
	toggle ^= 1;
	flock(next[toggle], LOCK_UN);
#endif sun
#endif RDUMP
E 14
E 13
I 10
}

/*
D 14
 * Since a read from a pipe may not return all we asked for
 * we must loop until we get all we need
E 14
I 14
 * Since a read from a pipe may not return all we asked for,
 * or a write may not write all we ask if we get a signal,
 * loop until the count is satisfied (or error).
E 14
 */
I 23
D 39
int
E 39
I 39
static int
E 39
E 23
D 14
readpipe(fd, buf, cnt)
	int fd;
E 14
I 14
atomic(func, fd, buf, count)
D 39
	int (*func)(), fd, count;
E 39
I 39
	int (*func)(), fd;
E 39
E 14
	char *buf;
I 39
	int count;
E 39
D 14
	int cnt;
E 14
{
D 14
	int rd, got;
E 14
I 14
	int got, need = count;
E 14

D 14
	for (rd = cnt; rd > 0; rd -= got) {
		got = read(fd, buf, rd);
D 13
		if (got < 0)
			return (got);
		if (got == 0)
			return (cnt - rd);
E 13
I 13
		if (got <= 0) {
			if (rd == cnt && got == 0)
				return (0);		/* Normal EOF */
			msg("short pipe read");
			dumpabort();
		}
E 14
I 14
	while ((got = (*func)(fd, buf, need)) > 0 && (need -= got) > 0)
E 14
E 13
		buf += got;
D 14
	}
	return (cnt);
E 14
I 14
	return (got < 0 ? got : count - need);
E 14
E 10
E 9
E 2
}
E 1
