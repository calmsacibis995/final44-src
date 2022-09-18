/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fcntlcom.h,v $
 * Revision 2.2  89/07/12  00:12:22  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*	@(#)fcntlcom.h 1.2 88/02/08 SMI; from UCB fcntl.h 5.2 1/8/86	*/

/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#ifndef _FCNTLCOM_
#define _FCNTLCOM_

/*
 * Flag values accessible to open(2) and fcntl(2)
 *  (The first three can only be set by open)
 * O_NDELAY is defined in <sys/fcntl.h>, since it differs in the 4.2
 * and S5 environments.
 */
#define	O_RDONLY	0
#define	O_WRONLY	1
#define	O_RDWR		2
#define	O_APPEND	FAPPEND	/* append (writes guaranteed at the end) */
#define	O_CREAT		FCREAT	/* open with file create */
#define	O_TRUNC		FTRUNC	/* open with truncation */
#define	O_EXCL		FEXCL	/* error on create if file exists */
#define	O_SYNC		FSYNC	/* do all writes synchronously */

/* flags for F_GETFL, F_SETFL-- needed by <sys/file.h> */
#define	FNDELAY		000004		/* non-blocking I/O (4.2 style) */
#define	FAPPEND		000010		/* append on each write */
#define	FASYNC		000100		/* signal pgrp when data ready */
#define	FCREAT		001000		/* create if nonexistent */
#define	FTRUNC		002000		/* truncate to zero length */
#define	FEXCL		004000		/* error if already created */
#define	FNBIO		010000		/* non-blocking I/O (S5-style) */
#define	FSYNC		020000		/* synchronous writes */

/* fcntl(2) requests */
#define	F_DUPFD	0	/* Duplicate fildes */
#define	F_GETFD	1	/* Get fildes flags */
#define	F_SETFD	2	/* Set fildes flags */
#define	F_GETFL	3	/* Get file flags */
#define	F_SETFL	4	/* Set file flags */
#define	F_GETOWN 5	/* Get owner */
#define F_SETOWN 6	/* Set owner */
#define F_GETLK  7      /* Get record-locking information */
#define F_SETLK  8      /* Set or Clear a record-lock (Non-Blocking) */
#define F_SETLKW 9      /* Set or Clear a record-lock (Blocking) */

/* System-V record-locking options */
/* lockf(2) requests */
#define F_ULOCK 0       /* Unlock a previously locked region */
#define F_LOCK  1       /* Lock a region for exclusive use */ 
#define F_TLOCK 2       /* Test and lock a region for exclusive use */
#define F_TEST  3       /* Test a region for other processes locks */

/* fcntl(2) flags (l_type field of flock structure) */
#define F_RDLCK 1       /* read lock */
#define F_WRLCK 2       /* write lock */
#define F_UNLCK 3       /* remove lock(s) */

/* file segment locking set data type - information passed to system by user */
struct flock {
        short   l_type;		/* F_RDLCK, F_WRLCK, or F_UNLCK */
        short   l_whence;	/* flag to choose starting offset */
        long    l_start;	/* relative offset, in bytes */
        long    l_len;          /* length, in bytes; 0 means lock to EOF */
        short   l_pid;		/* returned with F_GETLK */
        short   l_xxx;		/* reserved for future use */
};

#endif !_FCNTLCOM_
