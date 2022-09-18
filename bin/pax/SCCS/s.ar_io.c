h27068
s 00018/00016/01244
d D 8.2 94/04/18 14:02:15 bostic 10 9
c new version from Keith Muller (muller@sdcc3.ucsd.edu)
e
s 00002/00002/01258
d D 8.1 93/05/31 14:51:53 bostic 9 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/01258
d R 8.1 93/05/31 14:50:31 bostic 8 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00002/01258
d R 8.1 93/05/31 14:48:43 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/01226
d D 1.6 93/03/12 14:14:09 muller 6 5
c added routine to drain pipes. bug from donn seeley.
e
s 00007/00006/01219
d D 1.5 93/02/02 17:02:47 muller 5 4
c physblk no longer needs to be a global.
e
s 00029/00002/01196
d D 1.4 93/01/16 23:48:40 muller 4 3
c pax could create a archive with just a trailer if no files selected.
e
s 00174/00094/01024
d D 1.3 93/01/16 16:30:25 muller 3 2
c rewrote tape append operations using Donn Seeleys (BSDI) suggestion.
e
s 00143/00054/00975
d D 1.2 93/01/14 15:08:18 muller 2 1
c Repaired handling of tapes on append and made ar_close more robust.
e
s 01029/00000/00000
d D 1.1 92/12/17 19:22:18 muller 1 0
c date and time created 92/12/17 19:22:18 by muller
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992 Keith Muller.
D 9
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 9
I 9
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 9
 *
 * This code is derived from software contributed to Berkeley by
 * Keith Muller of the University of California, San Diego.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/mtio.h>
#include <sys/param.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>
#include <stdlib.h>
#include "pax.h"
#include "extern.h"

/*
D 2
 * Routines which handle the archive I/O device/file.
E 2
I 2
 * Routines which deal directly with the archive I/O device/file.
E 2
 */

#define DMOD		0666		/* default mode of created archives */
#define EXT_MODE	O_RDONLY	/* open mode for list/extract */
#define AR_MODE		(O_WRONLY | O_CREAT | O_TRUNC)	/* mode for archive */
#define APP_MODE	O_RDWR		/* mode for append */
#define STDO		"<STDOUT>"	/* psuedo name for stdout */
#define STDN		"<STDIN>"	/* psuedo name for stdin */
static int arfd = -1;			/* archive file descriptor */
D 4
static int artyp;			/* archive type: file/FIFO/tape */
E 4
I 4
static int artyp = ISREG;		/* archive type: file/FIFO/tape */
E 4
static int arvol = 1;			/* archive volume number */
static int lstrval = -1;		/* return value from last i/o */
static int io_ok;			/* i/o worked on volume after resync */
D 2
static int did_io;			/* ok i/o did occur on volume */
E 2
I 2
static int did_io;			/* did i/o ever occur on volume? */
E 2
static int done;			/* set via tty termination */
static struct stat arsb;		/* stat of archive device at open */
static int invld_rec;			/* tape has out of spec record size */
D 5
static int phyblk; 			/* size of physical block on TAPE */
E 5
I 3
static int wr_trail = 1;		/* trailer was rewritten in append */
I 4
static int can_unlnk = 0;		/* do we unlink null archives?  */
E 4
E 3
char *arcname;                  	/* printable name of archive */

static int get_phys __P((void));
extern sigset_t s_mask;

/*
 * ar_open()
 *	Opens the next archive volume. Determines the type of the device and
 *	sets up block sizes as required by the archive device and the format.
 *	Note: we may be called with name == NULL on the first open only.
 * Return:
 *	-1 on failure, 0 otherwise
 */

#if __STDC__
int
ar_open(char *name)
#else
int
ar_open(name)
	char *name;
#endif
{
        struct mtget mb;

	if (arfd != -1)
		(void)close(arfd);
	arfd = -1;
D 4
	phyblk = did_io = io_ok = invld_rec = 0;
E 4
I 4
D 5
	can_unlnk = phyblk = did_io = io_ok = invld_rec = 0;
E 5
I 5
	can_unlnk = did_io = io_ok = invld_rec = 0;
E 5
	artyp = ISREG;
E 4
	flcnt = 0;

	/*
	 * open based on overall operation mode
	 */
	switch (act) {
	case LIST:
	case EXTRACT:
		if (name == NULL) {
			arfd = STDIN_FILENO;
			arcname = STDN;
		} else if ((arfd = open(name, EXT_MODE, DMOD)) < 0)
D 2
			syswarn(1, errno, "Failed open to read on %s", name);
E 2
I 2
			syswarn(0, errno, "Failed open to read on %s", name);
E 2
		break;
	case ARCHIVE:
		if (name == NULL) {
			arfd = STDOUT_FILENO;
			arcname = STDO;
		} else if ((arfd = open(name, AR_MODE, DMOD)) < 0)
D 2
			syswarn(1, errno, "Failed open to write on %s", name);
E 2
I 2
			syswarn(0, errno, "Failed open to write on %s", name);
I 4
		else
			can_unlnk = 1;
E 4
E 2
		break;
	case APPND:
		if (name == NULL) {
			arfd = STDOUT_FILENO;
			arcname = STDO;
		} else if ((arfd = open(name, APP_MODE, DMOD)) < 0)
D 2
			syswarn(1, errno, "Failed open to read/write on %s",
E 2
I 2
			syswarn(0, errno, "Failed open to read/write on %s",
E 2
				name);
		break;
	case COPY:
		/*
		 * arfd not used in COPY mode
		 */
		arcname = "<NONE>";
		lstrval = 1;
		return(0);
	}
	if (arfd < 0)
		return(-1);

	/*
	 * set up is based on device type
	 */
	if (fstat(arfd, &arsb) < 0) {
D 2
		syswarn(1, errno, "Failed stat on %s", arcname);
E 2
I 2
		syswarn(0, errno, "Failed stat on %s", arcname);
I 4
		(void)close(arfd);
		arfd = -1;
		can_unlnk = 0;
E 4
E 2
		return(-1);
	}
	if (S_ISDIR(arsb.st_mode)) {
D 2
		warn(1, "Cannot write an archive on top of a directory %s",
E 2
I 2
		warn(0, "Cannot write an archive on top of a directory %s",
E 2
		    arcname);
I 4
		(void)close(arfd);
		arfd = -1;
		can_unlnk = 0;
E 4
		return(-1);
	}
I 4

E 4
	if (S_ISCHR(arsb.st_mode))
		artyp = ioctl(arfd, MTIOCGET, &mb) ? ISCHR : ISTAPE;
	else if (S_ISBLK(arsb.st_mode))
		artyp = ISBLK;
	else if ((lseek(arfd, (off_t)0L, SEEK_CUR) == -1) && (errno == ESPIPE))
		artyp = ISPIPE;
	else
		artyp = ISREG;

	/*
I 4
	 * make sure we beyond any doubt that we only can unlink regular files
	 * we created
	 */
	if (artyp != ISREG)
		can_unlnk = 0;
	/*
E 4
D 2
	 * if we are writing, were are done
E 2
I 2
	 * if we are writing, we are done
E 2
	 */
	if (act == ARCHIVE) {
		blksz = rdblksz = wrblksz;
		lstrval = 1;
		return(0);
	}

	/*
	 * set default blksz on read. APPNDs writes rdblksz on the last volume
	 * On all new archive volumes, we shift to wrblksz (if the user
	 * specified one, otherwize we will continue to use rdblksz). We
	 * must to set blocksize based on what kind of device the archive is
	 * stored.
	 */
	switch(artyp) {
	case ISTAPE:
		/*
		 * Tape drives come in at least two flavors. Those that support
		 * variable sized records and those that have fixed sized
		 * records. They must be treated differently. For tape drives
		 * that support variable sized records, we must make large
		 * reads to make sure we get the entire record, otherwise we
		 * will just get the first part of the record (up to size we
		 * asked). Tapes with fixed sized records may or may not return
		 * multiple records in a single read. We really do not care
		 * what the physical record size is UNLESS we are going to
		 * append. (We will need the physical block size to rewrite
		 * the trailer). Only when we are appending do we go to the
D 2
		 * effort to figure out the true* PHYSICAL record size.
E 2
I 2
		 * effort to figure out the true PHYSICAL record size.
E 2
		 */
		blksz = rdblksz = MAXBLK;
		break;
	case ISPIPE:
	case ISBLK:
	case ISCHR:
		/*
		 * Blocksize is not a major issue with these devices (but must
		 * be kept a multiple of 512). If the user specified a write
		 * block size, we use that to read. Under append, we must
		 * always keep blksz == rdblksz. Otherwise we go ahead and use
		 * the device optimal blocksize as (and if) returned by stat
		 * and if it is within pax specs.
		 */
		if ((act == APPND) && wrblksz) {
			blksz = rdblksz = wrblksz;
			break;
		}

		if ((arsb.st_blksize > 0) && (arsb.st_blksize < MAXBLK) &&
		    ((arsb.st_blksize % BLKMULT) == 0))
			rdblksz = arsb.st_blksize;
		else
			rdblksz = DEVBLK;
		/*
		 * For performance go for large reads when we can without harm
		 */
		if ((act == APPND) || (artyp == ISCHR))
			blksz = rdblksz;
		else
			blksz = MAXBLK;
		break;
	case ISREG:
		/*
		 * if the user specified wrblksz works, use it. Under appends
		 * we must always keep blksz == rdblksz
		 */
		if ((act == APPND) && wrblksz && ((arsb.st_size%wrblksz)==0)){
			blksz = rdblksz = wrblksz;
			break;
		}
		/*
		 * See if we can find the blocking factor from the file size
		 */
		for (rdblksz = MAXBLK; rdblksz > 0; rdblksz -= BLKMULT)
			if ((arsb.st_size % rdblksz) == 0)
				break;
		/*
		 * When we cannont find a match, we may have a flawed archive.
		 */
		if (rdblksz <= 0)
			rdblksz = FILEBLK;
		/*
		 * for performance go for large reads when we can
		 */
		if (act == APPND)
			blksz = rdblksz;
		else
			blksz = MAXBLK;
		break;
	default:
		/*
		 * should never happen, worse case, slow... 
		 */
		blksz = rdblksz = BLKMULT;
		break;
	}
	lstrval = 1;
	return(0);
}

/*
 * ar_close()
 *	closes archive device, increments volume number, and prints i/o summary
 */
#if __STDC__
void
ar_close(void)
#else
void
ar_close()
#endif
{
	FILE *outf;

I 3
	if (arfd < 0) {
		did_io = io_ok = flcnt = 0;
		return;
	}

E 3
I 2
	if (act == LIST)
		outf = stdout;
	else
		outf = stderr;

	/*
	 * Close archive file. This may take a LONG while on tapes (we may be
	 * forced to wait for the rewind to complete) so tell the user what is
	 * going on (this avoids the user hitting control-c thinking pax is
	 * broken).
	 */
D 3
	if (vflag && (arfd >= 0) && (artyp == ISTAPE)) {
		if (vfpart) {
E 3
I 3
	if (vflag && (artyp == ISTAPE)) {
		if (vfpart)
E 3
			(void)putc('\n', outf);
D 3
			vfpart = 0;
		}
E 3
D 10
		(void)fputs("pax: Waiting for tape drive close to complete...",
		    outf);
E 10
I 10
		(void)fprintf(outf,
			"%s: Waiting for tape drive close to complete...",
			argv0);
E 10
		(void)fflush(outf);
I 4
	}

	/*
	 * if nothing was written to the archive (and we created it), we remove
	 * it
	 */
	if (can_unlnk && (fstat(arfd, &arsb) == 0) && (S_ISREG(arsb.st_mode)) &&
	    (arsb.st_size == 0)) {
		(void)unlink(arcname);
		can_unlnk = 0;
E 4
	}

E 2
	(void)close(arfd);
I 2

D 3
	if (vflag && (arfd >= 0) && (artyp == ISTAPE)) {
E 3
I 3
	if (vflag && (artyp == ISTAPE)) {
E 3
		(void)fputs("done.\n", outf);
I 3
		vfpart = 0;
E 3
		(void)fflush(outf);
	}
E 2
	arfd = -1;
I 2

E 2
	if (!io_ok && !did_io) {
		flcnt = 0;
		return;
	}
	did_io = io_ok = 0;

	/*
	 * The volume number is only increased when the last device has data
I 2
	 * and we have already determined the archive format.
E 2
	 */
D 2
	++arvol;
E 2
I 2
	if (frmt != NULL)
		++arvol;

E 2
	if (!vflag) {
		flcnt = 0;
		return;
	}

	/*
	 * Print out a summary of I/O for this archive volume.
	 */
D 2
	if (act == LIST)
		outf = stdout;
	else
		outf = stderr;

	/*
	 * we need to go to the next line, partial output may be present
	 */
E 2
	if (vfpart) {
		(void)putc('\n', outf);
		vfpart = 0;
	}

I 2
	/*
	 * If we have not determined the format yet, we just say how many bytes
	 * we have skipped over looking for a header to id. there is no way we
	 * could have written anything yet.
	 */
	if (frmt == NULL) {
#	ifdef NET2_STAT
D 10
		(void)fprintf(outf, "pax: unknown format, %lu bytes skipped.\n",
E 10
I 10
		(void)fprintf(outf, "%s: unknown format, %lu bytes skipped.\n",
E 10
#	else
D 10
		(void)fprintf(outf, "pax: unknown format, %qu bytes skipped.\n",
E 10
I 10
		(void)fprintf(outf, "%s: unknown format, %qu bytes skipped.\n",
E 10
#	endif
D 10
		    rdcnt);
E 10
I 10
		    argv0, rdcnt);
E 10
		(void)fflush(outf);
		flcnt = 0;
		return;
	}

E 2
	(void)fprintf(outf,
#	ifdef NET2_STAT
D 2
	    "Pax %s vol %d: %lu files, %lu bytes read, %lu bytes written\n",
E 2
I 2
D 10
	    "pax: %s vol %d, %lu files, %lu bytes read, %lu bytes written.\n",
E 10
I 10
	    "%s: %s vol %d, %lu files, %lu bytes read, %lu bytes written.\n",
E 10
E 2
#	else
D 2
	    "Pax %s vol %d: %lu files, %qu bytes read, %qu bytes written\n",
E 2
I 2
D 10
	    "pax: %s vol %d, %lu files, %qu bytes read, %qu bytes written.\n",
E 10
I 10
	    "%s: %s vol %d, %lu files, %qu bytes read, %qu bytes written.\n",
E 10
E 2
#	endif
D 10
	    frmt->name, arvol-1, flcnt, rdcnt, wrcnt);
E 10
I 10
	    argv0, frmt->name, arvol-1, flcnt, rdcnt, wrcnt);
E 10
	(void)fflush(outf);
	flcnt = 0;
}

/*
I 6
 * ar_drain()
 *	drain any archive format independent padding from an archive read
 *	from a socket or a pipe. This is to prevent the process on the
 *	other side of the pipe from getting a SIGPIPE (pax will stop
 *	reading an archive once a format dependent trailer is detected).
 */
#if __STDC__
void
ar_drain(void)
#else
void
ar_drain()
#endif
{
	register int res;
	char drbuf[MAXBLK];

	/*
	 * we only drain from a pipe/socket. Other devices can be closed
	 * without reading up to end of file. We sure hope that pipe is closed
	 * on the other side so we will get an EOF.
	 */
	if ((artyp != ISPIPE) || (lstrval <= 0))
		return;

	/*
	 * keep reading until pipe is drained
	 */
	while ((res = read(arfd, drbuf, sizeof(drbuf))) > 0)
		;
	lstrval = res;
}

/*
E 6
 * ar_set_wr()
D 3
 *	special device dependent handling to switch from archive read to
 *	archive write on a single volume (an append). VERY device dependent.
 *	Note: for tapes, head is already positioned at the place we want to
 *	start writing.
E 3
I 3
 *	Set up device right before switching from read to write in an append.
 *	device dependent code (if required) to do this should be added here.
 *	For all archive devices we are already positioned at the place we want
 *	to start writing when this routine is called.
E 3
 * Return:
 *	0 if all ready to write, -1 otherwise
 */

#if __STDC__
int
ar_set_wr(void)
#else
int
ar_set_wr()
#endif
{
	off_t cpos;

I 3
	/*
	 * we must make sure the trailer is rewritten on append, ar_next()
	 * will stop us if the archive containing the trailer was not written
	 */
	wr_trail = 0;
	
E 3
	/* 
	 * Add any device dependent code as required here
	 */
	if (artyp != ISREG)
		return(0);
	/*
D 2
	 * Get rid of all the stuff after the current offset
E 2
I 2
	 * Ok we have an archive in a regular file. If we were rewriting a
	 * file, we must get rid of all the stuff after the current offset
	 * (it was not written by pax).
E 2
	 */
	if (((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0) ||
D 3
	    (ftruncate(arfd, cpos) < 0))
E 3
I 3
	    (ftruncate(arfd, cpos) < 0)) {
		syswarn(1, errno, "Unable to truncate archive file");
E 3
		return(-1);
I 3
	}
E 3
	return(0);
}

/*
 * ar_app_ok()
 *	check if the last volume in the archive allows appends. We cannot check
 *	this until we are ready to write since there is no spec that says all 
 *	volumes in a single archive have to be of the same type...
 * Return:
 *	0 if we can append, -1 otherwise.
 */

#if __STDC__
int
ar_app_ok(void)
#else
int
ar_app_ok()
#endif
{
	if (artyp == ISPIPE) {
		warn(1, "Cannot append to an archive obtained from a pipe.");
		return(-1);
	}

	if (!invld_rec)
		return(0);
D 2

E 2
D 10
	warn(1,"Cannot append, device record size %d does not support pax spec",
		rdblksz);
E 10
I 10
	warn(1,"Cannot append, device record size %d does not support %s spec",
		rdblksz, argv0);
E 10
	return(-1);
}

/*
 * ar_read()
 *	read up to a specified number of bytes from the archive into the
 *	supplied buffer. When dealing with tapes we may not always be able to
 *	read what we want.
 * Return:
 *	Number of bytes in buffer. 0 for end of file, -1 for a read error.
 */

#if __STDC__
int
ar_read(register char *buf, register int cnt)
#else
int
ar_read(buf, cnt)
	register char *buf;
	register int cnt;
#endif
{
	register int res = 0;

	/*
	 * if last i/o was in error, no more reads until reset or new volume
	 */
	if (lstrval <= 0)
		return(lstrval);

	/*
	 * how we read must be based on device type
	 */
	switch (artyp) {
	case ISTAPE:
		if ((res = read(arfd, buf, cnt)) > 0) {
			/*
			 * CAUTION: tape systems may not always return the same
			 * sized records so we leave blksz == MAXBLK. The
			 * physical record size that a tape drive supports is
			 * very hard to determine in a uniform and portable
			 * manner.
			 */
			io_ok = 1;
			if (res != rdblksz) {
				/*
				 * Record size changed. If this is happens on
D 2
				 * any record after the first, it may cause
				 * problem if we try to append. (We may not be
				 * able to space backwards the proper number
				 * of BYTES). Watch out for blocking which
				 * violates pax spec.
E 2
I 2
				 * any record after the first, we probably have
				 * a tape drive which has a fixed record size
				 * we are getting multiple records in a single
				 * read). Watch out for record blocking that
				 * violates pax spec (must be a multiple of
				 * BLKMULT).
E 2
				 */
				rdblksz = res;
				if (rdblksz % BLKMULT)
					invld_rec = 1;
			}
			return(res);
		}
		break;
	case ISREG:
	case ISBLK:
	case ISCHR:
	case ISPIPE:
	default:
		/*
		 * Files are so easy to deal with. These other things cannot
		 * be trusted at all. So when we are dealing with character
		 * devices and pipes we just take what they have ready for us
		 * and return. Trying to do anything else with them runs the
		 * risk of failure.
		 */
		if ((res = read(arfd, buf, cnt)) > 0) {
			io_ok = 1;
			return(res);
		}
		break;
	}

	/*
	 * We are in trouble at this point, something is broken...
	 */
	lstrval = res;
	if (res < 0)
		syswarn(1, errno, "Failed read on archive volume %d", arvol);
	else
		warn(0, "End of archive volume %d reached", arvol);
	return(res);
} 

/*
 * ar_write()
 *	Write a specified number of bytes in supplied buffer to the archive
 *	device so it appears as a single "block". Deals with errors and tries
 *	to recover when faced with short writes.
 * Return:
 *	Number of bytes written. 0 indicates end of volume reached and with no
 *	flaws (as best that can be detected). A -1 indicates an unrecoverable
 *	error in the archive occured.
 */

#if __STDC__
int
ar_write(register char *buf, register int bsz)
#else
int
ar_write(buf, bsz)
	register char *buf;
	register int bsz;
#endif
{
	register int res;
	off_t cpos;

	/*
	 * do not allow pax to create a "bad" archive. Once a write fails on
	 * an archive volume prevent further writes to it.
	 */
	if (lstrval <= 0)
		return(lstrval);

	if ((res = write(arfd, buf, bsz)) == bsz) {
I 3
		wr_trail = 1;
E 3
		io_ok = 1;
		return(bsz);
	}
D 3

E 3
	/*
	 * write broke, see what we can do with it. We try to send any partial
D 2
	 * writes that violate pax spec to the next archive volume.
E 2
I 2
	 * writes that may violate pax spec to the next archive volume.
E 2
	 */
	if (res < 0)
		lstrval = res;
	else
		lstrval = 0;

	switch (artyp) {
	case ISREG:
		if ((res > 0) && (res % BLKMULT)) {
			/*
		 	 * try to fix up partial writes which are not BLKMULT
			 * in size by forcing the runt record to next archive
			 * volume
		 	 */
			if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0)
				break;
			cpos -= (off_t)res;
			if (ftruncate(arfd, cpos) < 0)
				break;
			res = lstrval = 0;
			break;
		}
		if (res >= 0)
			break;
		/*
		 * if file is out of space, handle it like a return of 0
		 */
		if ((errno == ENOSPC) || (errno == EFBIG) || (errno == EDQUOT))
			res = lstrval = 0;
		break;
	case ISTAPE:
	case ISCHR:
	case ISBLK:
		if (res >= 0)
			break;
		if (errno == EACCES) {
			warn(0, "Write failed, archive is write protected.");
			res = lstrval = 0;
			return(0);
		}
		/*
		 * see if we reached the end of media, if so force a change to
		 * the next volume
		 */
		if ((errno == ENOSPC) || (errno == EIO) || (errno == ENXIO))
			res = lstrval = 0;
		break;
	case ISPIPE:
	default:
		/*
		 * we cannot fix errors to these devices
		 */
		break;
	}

	/*
	 * Better tell the user the bad news...
D 2
	 * if this is a block aligned archive format, it may be a bad archive.
	 * the format wants the header to start at a BLKMULT boundry. While
E 2
I 2
	 * if this is a block aligned archive format, we may have a bad archive
	 * if the format wants the header to start at a BLKMULT boundry. While
E 2
	 * we can deal with the mis-aligned data, it violates spec and other
	 * archive readers will likely fail. if the format is not block
D 2
	 * aligned, the user may be lucky.
E 2
I 2
	 * aligned, the user may be lucky (and the archive is ok).
E 2
	 */
D 3
	if (res >= 0)
E 3
I 3
	if (res >= 0) {
		if (res > 0)
			wr_trail = 1;
E 3
		io_ok = 1;
D 3
	if (res == 0)
E 3
I 3
	}

	/*
	 * If we were trying to rewrite the trailer and it didn't work, we
	 * must quit right away.
	 */
	if (!wr_trail && (res <= 0)) {
		warn(1,"Unable to append, trailer re-write failed. Quitting.");
		return(res);
	}
		
	if (res == 0) 
E 3
		warn(0, "End of archive volume %d reached", arvol);
	else if (res < 0)
		syswarn(1, errno, "Failed write to archive volume: %d", arvol);
	else if (!frmt->blkalgn || ((res % frmt->blkalgn) == 0))
		warn(0,"WARNING: partial archive write. Archive MAY BE FLAWED");
	else
		warn(1,"WARNING: partial archive write. Archive IS FLAWED");
	return(res);
}

/*
 * ar_rdsync()
 *	Try to move past a bad spot on a flawed archive as needed to continue
 *	I/O. Clears error flags to allow I/O to continue.
 * Return:
 *	0 when ok to try i/o again, -1 otherwise.
 */

#if __STDC__
int
ar_rdsync(void)
#else
int
ar_rdsync()
#endif
{
	long fsbz;
	off_t cpos;
	off_t mpos;
        struct mtop mb;

	/*
	 * Fail resync attempts at user request (done) or this is going to be
	 * an update/append to a existing archive. if last i/o hit media end,
	 * we need to go to the next volume not try a resync
	 */
	if ((done > 0) || (lstrval == 0))
		return(-1);

	if ((act == APPND) || (act == ARCHIVE)) {
		warn(1, "Cannot allow updates to an archive with flaws.");
		return(-1);
	}
	if (io_ok)
		did_io = 1;

	switch(artyp) {
	case ISTAPE:
		/*
		 * if the last i/o was a successful data transfer, we assume
		 * the fault is just a bad record on the tape that we are now
		 * past. If we did not get any data since the last resync try
		 * to move the tape foward one PHYSICAL record past any
		 * damaged tape section. Some tape drives are stubborn and need
		 * to be pushed.
		 */
		if (io_ok) {
			io_ok = 0;
			lstrval = 1;
			break;
		}
		mb.mt_op = MTFSR;
		mb.mt_count = 1;
		if (ioctl(arfd, MTIOCTOP, &mb) < 0)
			break;
		lstrval = 1;
		break;
	case ISREG:
	case ISCHR:
	case ISBLK:
		/*
		 * try to step over the bad part of the device.
		 */
		io_ok = 0;
		if (((fsbz = arsb.st_blksize) <= 0) || (artyp != ISREG))
			fsbz = BLKMULT;
		if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0)
			break;
		mpos = fsbz - (cpos % (off_t)fsbz);
		if (lseek(arfd, mpos, SEEK_CUR) < 0) 
			break;
		lstrval = 1;
		break;
	case ISPIPE:
	default:
		/*
		 * cannot recover on these archive device types
		 */
		io_ok = 0;
		break;
	}
	if (lstrval <= 0) {
D 2
		warn(1,"Unable to recover from an archive read failure.");
E 2
I 2
		warn(1, "Unable to recover from an archive read failure.");
E 2
		return(-1);
	}
	warn(0, "Attempting to recover from an archive read failure.");
	return(0);
}

/*
 * ar_fow()
 *	Move the I/O position within the archive foward the specified number of
 *	bytes as supported by the device. If we cannot move the requested
 *	number of bytes, return the actual number of bytes moved in skipped.
 * Return:
 *	0 if moved the requested distance, -1 on complete failure, 1 on
 *	partial move (the amount moved is in skipped)
 */

#if __STDC__
int
ar_fow(off_t sksz, off_t *skipped)
#else
int
ar_fow(sksz, skipped)
	off_t sksz;
	off_t *skipped;
#endif
{
	off_t cpos;
	off_t mpos;

	*skipped = 0;
	if (sksz <= 0)
		return(0);

	/*
	 * we cannot move foward at EOF or error
	 */
	if (lstrval <= 0)
		return(lstrval);

	/*
	 * Safer to read forward on devices where it is hard to find the end of
	 * the media without reading to it. With tapes we cannot be sure of the
	 * number of physical blocks to skip (we do not know physical block
	 * size at this point), so we must only read foward on tapes!
	 */
	if (artyp != ISREG) 
		return(0);

	/*
	 * figure out where we are in the archive
	 */
	if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) >= 0) {
		/* 
	 	 * we can be asked to move farther than there are bytes in this
		 * volume, if so, just go to file end and let normal buf_fill()
		 * deal with the end of file (it will go to next volume by
		 * itself)
	 	 */
		if ((mpos = cpos + sksz) > arsb.st_size) {
			*skipped = arsb.st_size - cpos;
			mpos = arsb.st_size;
		} else
			*skipped = sksz;
		if (lseek(arfd, mpos, SEEK_SET) >= 0)
			return(0);
	}
	syswarn(1, errno, "Foward positioning operation on archive failed");
	lstrval = -1;
	return(-1);
}

/*
 * ar_rev()
 *	move the i/o position within the archive backwards the specified byte
 *	count as supported by the device. With tapes drives we RESET rdblksz to
 *	the PHYSICAL blocksize.
 *	NOTE: We should only be called to move backwards so we can rewrite the
 *	last records (the trailer) of an archive (APPEND).
 * Return:
 *	0 if moved the requested distance, -1 on complete failure
 */

#if __STDC__
int
ar_rev(off_t sksz)
#else
int
ar_rev(sksz)
	off_t sksz;
#endif
{
	off_t cpos;
        struct mtop mb;
I 5
D 10
	register int phyblk;
E 10
I 10
	register int phyblk; 
E 10
E 5

D 3
	if (sksz <= 0)
		return(0);

E 3
	/*
D 3
	 * make sure we do not have a flawed archive
E 3
I 3
	 * make sure we do not have try to reverse on a flawed archive
E 3
	 */
	if (lstrval < 0)
		return(lstrval);

	switch(artyp) {
	case ISPIPE:
I 3
		if (sksz <= 0) 
			break;
E 3
		/*
		 * cannot go backwards on these critters
		 */
D 3
		break;
E 3
I 3
		warn(1, "Reverse positioning on pipes is not supported.");
		lstrval = -1;
		return(-1);
E 3
	case ISREG:
	case ISBLK:
	case ISCHR:
	default:
I 3
		if (sksz <= 0)
			break;

E 3
		/*
		 * For things other than files, backwards movement has a very
		 * high probability of failure as we really do not know the
		 * true attributes of the device we are talking to (the device
		 * may not even have the ability to lseek() in any direction).
D 3
		 * first we figure out where we are in the archive
E 3
I 3
		 * First we figure out where we are in the archive.
E 3
		 */
D 3
		if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0)
			break;
E 3
I 3
		if ((cpos = lseek(arfd, (off_t)0L, SEEK_CUR)) < 0) {
			syswarn(1, errno,
			   "Unable to obtain current archive byte offset");
			lstrval = -1;
			return(-1);
		}
E 3

		/*
		 * we may try to go backwards past the start when the archive
		 * is only a single record. If this hapens and we are on a
		 * multi volume archive, we need to go to the end of the
		 * previous volume and continue our movement backwards from
D 3
		 * there. (This is really hard to do and is NOT IMPLEMENTED)
E 3
I 3
		 * there.
E 3
		 */
		if ((cpos -= sksz) < (off_t)0L) {
			if (arvol > 1) {
D 3
				warn(1,"End of archive is on previous volume.");
E 3
I 3
				/*
				 * this should never happen
				 */
				warn(1,"Reverse position on previous volume.");
E 3
				lstrval = -1;
				return(-1);
			}
			cpos = (off_t)0L;
		}
D 3
		if (lseek(arfd, cpos, SEEK_SET) < 0)
			break;
		lstrval = 1;
		return(0);
E 3
I 3
		if (lseek(arfd, cpos, SEEK_SET) < 0) {
			syswarn(1, errno, "Unable to seek archive backwards");
			lstrval = -1;
			return(-1);
		}
		break;
E 3
	case ISTAPE:
		/*
	 	 * Calculate and move the proper number of PHYSICAL tape
D 3
		 * records. If the sksz is not an even multiple of the physical
E 3
I 3
		 * blocks. If the sksz is not an even multiple of the physical
E 3
		 * tape size, we cannot do the move (this should never happen).
		 * (We also cannot handler trailers spread over two vols).
I 3
		 * get_phys() also makes sure we are in front of the filemark.
E 3
	 	 */
D 5
		if (get_phys() < 0) {
E 5
I 5
		if ((phyblk = get_phys()) <= 0) {
E 5
D 3
			warn(1, "Cannot determine archive tape blocksize.");
			break;
E 3
I 3
			lstrval = -1;
			return(-1);
E 3
		}

I 3
		/*
		 * make sure future tape reads only go by physical tape block
		 * size (set rdblksz to the real size).
		 */
		rdblksz = phyblk;

		/*
		 * if no movement is required, just return (we must be after
		 * get_phys() so the physical blocksize is properly set)
		 */
		if (sksz <= 0)
			break;

		/*
		 * ok we have to move. Make sure the tape drive can do it.
		 */
E 3
		if (sksz % phyblk) {
D 3
			warn(1,"Tape drive cannot backspace %d bytes (%d phys)",
			    sksz, phyblk);
E 3
I 3
			warn(1,
			    "Tape drive unable to backspace requested amount");
E 3
			lstrval = -1;
			return(-1);
		}

D 3
		mb.mt_op = MTBSR;
		mb.mt_count = sksz/phyblk;
		if (ioctl(arfd, MTIOCTOP, &mb) < 0)
			break;

E 3
		/*
D 3
		 * reset rdblksz to be the device physical blocksize.
E 3
I 3
		 * move backwards the requested number of bytes
E 3
		 */
D 3
		rdblksz = phyblk;
		lstrval = 1;
		return(0);
E 3
I 3
		mb.mt_op = MTBSR;
		mb.mt_count = sksz/phyblk;
		if (ioctl(arfd, MTIOCTOP, &mb) < 0) {
			syswarn(1,errno, "Unable to backspace tape %d blocks.",
			    mb.mt_count);
			lstrval = -1;
			return(-1);
		}
		break;
E 3
	}
D 3
	syswarn(1, errno, "Reverse positioning operation on archive failed");
	lstrval = -1;
	return(-1);
E 3
I 3
	lstrval = 1;
	return(0);
E 3
}

/*
 * get_phys()
D 3
 *	Determine the physical block size on a tape drive. Should only be
D 2
 *	when at EOF.
E 2
I 2
 *	when at EOF. Tape drives are so inconsistant, while finding true record
 *	size should be a trival thing to figure out, it really is difficult and
 *	very likely to fail.
E 3
I 3
 *	Determine the physical block size on a tape drive. We need the physical
 *	block size so we know how many bytes we skip over when we move with 
 *	mtio commands. We also make sure we are BEFORE THE TAPE FILEMARK when
 *	return.
 *	This is one really SLOW routine...
E 3
E 2
 * Return:
D 5
 *	0 if ok, -1 otherwise
E 5
I 5
 *	physical block size if ok (ok > 0), -1 otherwise
E 5
 */

#if __STDC__
static int
get_phys(void)
#else
static int
get_phys()
#endif
{
I 3
	register int padsz = 0;
E 3
D 2
        struct mtop mb;
E 2
I 2
	register int res;
I 5
	register int phyblk;
E 5
	struct mtop mb;
E 2
D 3
	char scbuf1[MAXBLK];
	char scbuf2[MAXBLK];
E 3
I 3
	char scbuf[MAXBLK];
E 3

	/*
D 2
	 * We can only use this technique when we are at tape EOF (so the
	 * MTBSR will leave just a SINGLE PHYSICAL record between the head
	 * and the end of the tape). Since we may be called more than once,
	 * only the first phyblk detection will be used.
	 */
E 2
I 2
D 3
	 * We backspace one record and read foward. The read should tell us the
	 * true physical size.  We can only use this technique when we are at
	 * tape EOF (so the MTBSR will leave just a SINGLE PHYSICAL record
	 * between the head and the end of the tape file; the max we can then
	 * read should be just ONE physical record). Since we may be called
	 * more than once, only the first phyblk detection will be used.
 	 */
E 2
	if (phyblk > 0)
		return(0);
E 3
I 3
	 * move to the file mark, and then back up one record and read it.
	 * this should tell us the physical record size the tape is using.
	 */
	if (lstrval == 1) {
		/*
		 * we know we are at file mark when we get back a 0 from
		 * read()
		 */
		while ((res = read(arfd, scbuf, sizeof(scbuf))) > 0)
			padsz += res;
		if (res < 0) {
			syswarn(1, errno, "Unable to locate tape filemark.");
			return(-1);
		}
	}
E 3

D 3
	mb.mt_op = MTBSR;
E 3
I 3
	/*
	 * move backwards over the file mark so we are at the end of the
	 * last record.
	 */
	mb.mt_op = MTBSF;
E 3
	mb.mt_count = 1;
D 3
	if ((ioctl(arfd, MTIOCTOP, &mb) < 0) ||
D 2
	    ((phyblk = read(arfd, scbuf1, sizeof(scbuf1))) <= 0))
E 2
I 2
	    ((phyblk = read(arfd, scbuf1, sizeof(scbuf1))) <= 0)) {
E 3
I 3
	if (ioctl(arfd, MTIOCTOP, &mb) < 0) {
		syswarn(1, errno, "Unable to backspace over tape filemark.");
E 3
E 2
		return(-1);
I 2
	}
E 2

	/*
D 2
	 * check for consistancy, if we cannot repeat, abort. This can only be
	 * a guess, trailer blocks tend to be zero filled!
E 2
I 2
D 3
	 * We must be careful, we may not have been called with the tape head
	 * at the end of the tape.  We expect if we read again we will get the
	 * true blocksize. (We expect the true size on the second read because
	 * by pax spec the trailer is always in the last record, and we are
	 * only called after the trailer was seen. If this is not true, the
	 * archive is flawed and we will return a failure indication). After
	 * the second read we must adjust the head position so it is at the
	 * same place it was when we are called. We also check for consistancy,
	 * if we cannot repeat we return a failure.
E 3
I 3
	 * move backwards so we are in front of the last record and read it to
	 * get physical tape blocksize.
E 3
E 2
	 */
D 3
	if ((ioctl(arfd, MTIOCTOP, &mb) < 0) ||
D 2
	    (read(arfd, scbuf2, sizeof(scbuf2)) != phyblk) ||
	    (bcmp(scbuf1, scbuf2, phyblk) != 0))
E 2
I 2
	    ((res = read(arfd, scbuf2, sizeof(scbuf2))) <= 0))
E 3
I 3
	mb.mt_op = MTBSR;
	mb.mt_count = 1;
	if (ioctl(arfd, MTIOCTOP, &mb) < 0) {
		syswarn(1, errno, "Unable to backspace over last tape block.");
E 3
E 2
		return(-1);
I 3
	}
	if ((phyblk = read(arfd, scbuf, sizeof(scbuf))) <= 0) {
		syswarn(1, errno, "Cannot determine archive tape blocksize.");
		return(-1);
	}
E 3
I 2

	/*
D 3
	 * If we get a bigger size on the second read or the first read is not
	 * a multiple of the second read, we better not chance an append.
E 3
I 3
	 * read foward to the file mark, then back up in front of the filemark
	 * (this is a bit paranoid, but should be safe to do).
E 3
	 */
D 3
	if ((res > phyblk) || (phyblk % res))
E 3
I 3
	while ((res = read(arfd, scbuf, sizeof(scbuf))) > 0)
		;
	if (res < 0) {
		syswarn(1, errno, "Unable to locate tape filemark.");
E 3
		return(-1);
I 3
	}
	mb.mt_op = MTBSF;
	mb.mt_count = 1;
	if (ioctl(arfd, MTIOCTOP, &mb) < 0) {
		syswarn(1, errno, "Unable to backspace over tape filemark.");
		return(-1);
	}
E 3

	/*
D 3
	 * if both reads are the same size and the data is consistant we can
	 * go on with the append
E 3
I 3
	 * set lstrval so we know that the filemark has not been seen
E 3
	 */
D 3
	if (res == phyblk) {
		if (bcmp(scbuf1, scbuf2, phyblk) != 0)
			return(-1);
E 3
I 3
	lstrval = 1;

	/*
	 * return if there was no padding
	 */
	if (padsz == 0)
E 3
D 5
		return(0);
E 5
I 5
		return(phyblk);
E 5
D 3
	}
E 3

	/*
D 3
	 * We got two different block sizes. We were not at the tape EOF.
	 * So we try one more time, if the result is not consistant we abort.
E 3
I 3
	 * make sure we can move backwards over the padding. (this should
	 * never fail).
E 3
	 */
D 3
	if ((ioctl(arfd, MTIOCTOP, &mb) < 0) ||
	    (read(arfd, scbuf1, sizeof(scbuf1)) != res) ||
	    (bcmp(scbuf1, scbuf2, res) != 0))
E 3
I 3
	if (padsz % phyblk) {
		warn(1, "Tape drive unable to backspace requested amount");
E 3
		return(-1);
I 3
	}
E 3

	/*
D 3
	 * Ok, we assume the physical block size is in res. We need to adjust
	 * head position backwards based on the what we got on the first read.
	 * (must leave the head at the same place it was when we were called).
E 3
I 3
	 * move backwards over the padding so the head is where it was when
	 * we were first called (if required).
E 3
	 */
D 3
	mb.mt_count = (phyblk - res)/res;
	phyblk = res;
	if ((mb.mt_count == 0) || (ioctl(arfd, MTIOCTOP, &mb) < 0))
E 3
I 3
	mb.mt_op = MTBSR;
	mb.mt_count = padsz/phyblk;
	if (ioctl(arfd, MTIOCTOP, &mb) < 0) {
		syswarn(1,errno,"Unable to backspace tape over %d pad blocks",
		    mb.mt_count);
E 3
		return(-1);
I 3
	}
E 3
E 2
D 5
	return(0);
E 5
I 5
	return(phyblk);
E 5
}

/*
 * ar_next()
D 2
 *	prompts the user for the next volume in this archive. For devices we
 *	may allow the media to be changed. otherwise a new archive is prompted
 *	for. By pax spec, if there is no controlling tty or an eof is read on
 *	tty input, we quit pax.
E 2
I 2
 *	prompts the user for the next volume in this archive. For some devices
 *	we may allow the media to be changed. Otherwise a new archive is
 *	prompted for. By pax spec, if there is no controlling tty or an eof is
 *	read on tty input, we must quit pax.
E 2
 * Return:
 *	0 when ready to continue, -1 when all done
 */

#if __STDC__
int
ar_next(void)
#else
int
ar_next()
#endif
{
	char buf[PAXPATHLEN+2];
	static int freeit = 0;
	sigset_t o_mask;

	/*
D 2
	 * WE MUST CLOSE the device. A lot of devices must see last close, (so
E 2
I 2
	 * WE MUST CLOSE THE DEVICE. A lot of devices must see last close, (so
E 2
	 * things like writing EOF etc will be done) (Watch out ar_close() can
D 2
	 * also be called on a signal, so we must prevent a race.
E 2
I 2
	 * also be called via a signal handler, so we must prevent a race.
E 2
	 */
	if (sigprocmask(SIG_BLOCK, &s_mask, &o_mask) < 0)
D 2
		syswarn(1, errno, "Unable to set signal mask");
E 2
I 2
		syswarn(0, errno, "Unable to set signal mask");
E 2
	ar_close();
	if (sigprocmask(SIG_SETMASK, &o_mask, (sigset_t *)NULL) < 0)
D 2
		syswarn(1, errno, "Unable to restore signal mask");
E 2
I 2
		syswarn(0, errno, "Unable to restore signal mask");
E 2

D 3
	if (done)
E 3
I 3
	if (done || !wr_trail)
E 3
		return(-1);

D 10
	tty_prnt("\nATTENTION! Pax archive volume change required.\n");
E 10
I 10
	tty_prnt("\nATTENTION! %s archive volume change required.\n", argv0);
E 10

	/*
	 * if i/o is on stdin or stdout, we cannot reopen it (we do not know
D 2
	 * the name), the user will have to type it in.
E 2
I 2
	 * the name), the user will be forced to type it in.
E 2
	 */
	if (strcmp(arcname, STDO) && strcmp(arcname, STDN) && (artyp != ISREG)
	    && (artyp != ISPIPE)) {
		if (artyp == ISTAPE) {
			tty_prnt("%s ready for archive tape volume: %d\n",
				arcname, arvol);
			tty_prnt("Load the NEXT TAPE on the tape drive");
		} else {
			tty_prnt("%s ready for archive volume: %d\n",
				arcname, arvol);
			tty_prnt("Load the NEXT STORAGE MEDIA (if required)");
		}

		if ((act == ARCHIVE) || (act == APPND))
			tty_prnt(" and make sure it is WRITE ENABLED.\n");
		else
			tty_prnt("\n");

		for(;;) {
D 10
			tty_prnt("Type \"y\" to continue, \".\" to quit pax,");
E 10
I 10
			tty_prnt("Type \"y\" to continue, \".\" to quit %s,",
				argv0);
E 10
			tty_prnt(" or \"s\" to switch to new device.\nIf you");
			tty_prnt(" cannot change storage media, type \"s\"\n");
			tty_prnt("Is the device ready and online? > ");

			if ((tty_read(buf,sizeof(buf))<0) || !strcmp(buf,".")){
				done = 1;
				lstrval = -1;
D 10
				tty_prnt("Quitting pax!\n");
E 10
I 10
				tty_prnt("Quitting %s!\n", argv0);
E 10
				vfpart = 0;
				return(-1);
			}

			if ((buf[0] == '\0') || (buf[1] != '\0')) {
				tty_prnt("%s unknown command, try again\n",buf);
				continue;
			}

			switch (buf[0]) {
			case 'y':
			case 'Y':
				/*
				 * we are to continue with the same device
				 */
				if (ar_open(arcname) >= 0) 
					return(0);
				tty_prnt("Cannot re-open %s, try again\n",
					arcname);
				continue;
			case 's':
			case 'S':
				/*
				 * user wants to open a different device
				 */
				tty_prnt("Switching to a different archive\n");
				break;
			default:
				tty_prnt("%s unknown command, try again\n",buf);
				continue;
			}
			break;
		}
	} else
		tty_prnt("Ready for archive volume: %d\n", arvol);

	/*
	 * have to go to a different archive
	 */
	for (;;) {
D 10
		tty_prnt("Input archive name or \".\" to quit pax.\n");
E 10
I 10
		tty_prnt("Input archive name or \".\" to quit %s.\n", argv0);
E 10
		tty_prnt("Archive name > ");

		if ((tty_read(buf, sizeof(buf)) < 0) || !strcmp(buf, ".")) {
			done = 1;
			lstrval = -1;
D 10
			tty_prnt("Quitting pax!\n");
E 10
I 10
			tty_prnt("Quitting %s!\n", argv0);
E 10
			vfpart = 0;
			return(-1);
		}
		if (buf[0] == '\0') {
			tty_prnt("Empty file name, try again\n");
			continue;
		}
                if (!strcmp(buf, "..")) {
                        tty_prnt("Illegal file name: .. try again\n");
                        continue;
                }
		if (strlen(buf) > PAXPATHLEN) {
			tty_prnt("File name too long, try again\n");
			continue;
		}

		/*
		 * try to open new archive
		 */
		if (ar_open(buf) >= 0) {
			if (freeit) {
				(void)free(arcname);
				freeit = 0;
			}
			if ((arcname = strdup(buf)) == NULL) {
				done = 1;
				lstrval = -1;
D 2
				warn(1, "Cannot save archive name.");
E 2
I 2
				warn(0, "Cannot save archive name.");
E 2
				return(-1);
			}
			freeit = 1;
			break;
		}
		tty_prnt("Cannot open %s, try again\n", buf);
		continue;
	}
	return(0);
}
E 1
