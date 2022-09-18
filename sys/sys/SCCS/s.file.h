h55302
s 00001/00001/00051
d D 8.3 95/01/09 18:16:10 cgd 40 39
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00007/00005/00045
d D 8.2 94/08/20 16:50:15 mckusick 39 38
c use new queue.h data structures
e
s 00002/00002/00048
d D 8.1 93/06/02 19:53:33 bostic 38 37
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00000/00047
d D 7.11 92/03/02 17:22:34 bostic 37 35
c declare struct proc, struct uio before using in prototypes
e
s 00002/00001/00046
d R 7.11 91/06/21 10:50:37 mckusick 36 35
c new calling convention for fo_close
e
s 00012/00023/00035
d D 7.10 91/06/04 13:25:27 bostic 35 34
c user programs need include of sys/{fcntl,unistd}.h
c minor prototype format cleanup
e
s 00008/00005/00050
d D 7.9 91/06/03 20:24:12 mckusick 34 33
c change to be dynamically allocated
e
s 00020/00005/00035
d D 7.8 91/04/15 23:25:11 mckusick 33 32
c add prototypes for file table ops
e
s 00006/00035/00034
d D 7.7 91/03/17 15:33:59 karels 32 31
c more-or-less working with new proc & user structs
e
s 00001/00011/00068
d D 7.6 90/06/28 21:58:50 bostic 31 30
c new copyright notice
e
s 00031/00079/00048
d D 7.5 90/05/25 18:04:30 bostic 30 29
c POSIX 1003.1
e
s 00001/00001/00126
d D 7.4 89/09/06 22:10:57 karels 29 28
c keep O_NONBLOCK after open
e
s 00018/00013/00109
d D 7.3 89/05/09 16:35:08 mckusick 28 27
c merge in vnodes
e
s 00003/00002/00119
d D 7.2 89/05/01 23:17:46 marc 27 26
c add O_NONBLOCK
e
s 00001/00001/00120
d D 7.1 86/06/04 23:22:32 mckusick 26 25
c 4.3BSD release version
e
s 00007/00001/00114
d D 6.3 85/06/08 14:57:05 mckusick 25 24
c Add copyright
e
s 00023/00006/00092
d D 6.2 83/09/23 16:28:54 karels 24 23
c fix fcntl
e
s 00000/00000/00098
d D 6.1 83/07/29 06:12:16 sam 23 22
c 4.2 distribution
e
s 00003/00001/00095
d D 4.19 83/06/13 23:03:44 sam 22 21
c put locking at a file table level rather than at descriptor
e
s 00000/00001/00096
d D 4.18 83/06/12 14:30:40 sam 21 20
c purge stat from generic ops
e
s 00002/00001/00095
d D 4.17 83/06/09 21:56:32 sam 20 19
c cleanup locking
e
s 00001/00001/00095
d D 4.16 83/06/03 13:39:40 sam 19 18
c must have definitions visible for users
e
s 00064/00054/00032
d D 4.15 83/05/27 13:58:10 sam 18 17
c bill did it (but I like it sorta)
e
s 00003/00003/00083
d D 4.14 82/11/13 23:08:06 sam 17 16
c merge 4.1b and 4.1c
e
s 00007/00000/00079
d D 4.13 82/10/10 17:12:11 root 16 15
c header file cleanup while moving vax files to their own directory
e
s 00050/00005/00029
d D 4.12 82/08/10 17:53:03 sam 15 14
c file locking and new open 
e
s 00011/00015/00023
d D 4.11 82/07/24 18:09:07 root 14 13
c merge with calder
e
s 00004/00005/00034
d D 4.10 81/11/14 16:50:55 wnj 13 12
c just before overlay of ip
e
s 00018/00019/00021
d D 4.9 81/11/08 16:40:14 wnj 12 11
c first listing
e
s 00000/00004/00040
d D 4.8 81/10/17 16:14:08 wnj 11 10
c cleanup (mpx removal, old tty removal, beginnings of select)
e
s 00004/00000/00040
d D 4.7 81/05/12 17:20:16 root 10 9
c bbn tcp/ip
e
s 00005/00000/00035
d D 4.6 81/04/28 03:01:55 root 9 8
c f_port, f_conn, FPORT
e
s 00002/00002/00033
d D 4.5 81/03/09 00:26:52 wnj 8 7
c lint
e
s 00002/00004/00033
d D 4.4 81/02/27 00:02:05 wnj 7 6
c move to pointer base to allow dyn allocation
e
s 00001/00001/00036
d D 4.3 81/02/19 21:40:26 wnj 6 5
c %G%->%E%
e
s 00003/00000/00034
d D 4.2 81/01/26 20:42:44 wnj 5 4
c chaos
e
s 00000/00000/00034
d D 4.1 80/11/09 17:00:53 bill 4 3
c stamp for 4bsd
e
s 00002/00002/00032
d D 3.3 80/09/27 17:54:24 bill 3 2
c char->short
e
s 00001/00001/00033
d D 3.2 80/06/07 02:57:25 bill 2 1
c %H%->%G%
e
s 00034/00000/00000
d D 3.1 80/04/09 16:23:49 bill 1 0
c date and time created 80/04/09 16:23:49 by bill
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%H%	*/
E 2
I 2
D 6
/*	%M%	%I%	%G%	*/
E 6
I 6
D 25
/*	%M%	%I%	%E%	*/
E 25
I 25
/*
D 26
 * Copyright (c) 1982 Regents of the University of California.
E 26
I 26
D 28
 * Copyright (c) 1982, 1986 Regents of the University of California.
E 26
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 28
I 28
D 38
 * Copyright (c) 1982, 1986, 1989 Regents of the University of California.
 * All rights reserved.
E 38
I 38
 * Copyright (c) 1982, 1986, 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 38
E 28
 *
I 28
D 31
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 31
I 31
 * %sccs.include.redist.c%
E 31
 *
E 28
 *	%W% (Berkeley) %G%
 */
E 25
E 6
E 2

I 34
D 35
#ifdef KERNEL
E 35
E 34
I 15
D 32
#ifdef KERNEL
I 30
#include "fcntl.h"
#include "unistd.h"
E 32
I 32
#include <sys/fcntl.h>
#include <sys/unistd.h>
E 32

I 35
#ifdef KERNEL
I 39
#include <sys/queue.h>

E 39
I 37
struct proc;
struct uio;

E 37
E 35
I 32
D 34
#ifdef KERNEL
E 34
E 32
E 30
E 15
/*
D 14
 * One file structure is allocated
 * for each open/creat/pipe call.
 * Main use is to hold the read/write
 * pointer associated with each open
 * file.
E 14
I 14
D 32
 * Descriptor table entry.
 * One for each kernel object.
E 32
I 32
D 35
 * Kernel descriptor table entry;
 * one for each open kernel vnode and socket.
E 35
I 35
 * Kernel descriptor table.
 * One entry for each open kernel vnode and socket.
E 35
E 32
E 14
 */
D 12
struct	file
{
D 3
	char	f_flag;
	char	f_count;		/* reference count */
E 3
I 3
	short	f_flag;
	short	f_count;		/* reference count */
E 3
	struct inode *f_inode;		/* pointer to inode structure */
E 12
I 12
D 30
struct	file {
E 30
I 30
struct file {
E 30
D 13
	short	f_flag;		/* read/write and type (socket or inode) */
	short	f_count;	/* reference count */
E 13
I 13
D 18
	short	f_flag;			/* see below */
E 18
I 18
D 22
	short	f_flag;		/* see below */
E 22
I 22
D 34
	int	f_flag;		/* see below */
E 34
I 34
D 39
	struct	file *f_filef;	/* list of active files */
	struct	file **f_fileb;	/* list of active files */
E 39
I 39
	LIST_ENTRY(file) f_list;/* list of active files */
E 39
	short	f_flag;		/* see fcntl.h */
E 34
I 30
#define	DTYPE_VNODE	1	/* file */
#define	DTYPE_SOCKET	2	/* communications endpoint */
E 30
E 22
E 18
I 14
	short	f_type;		/* descriptor type */
D 18
	char	f_nbhow;	/* state from dnblock */
	char	f_sighow;	/* state from dsignal */
E 14
	short	f_count;		/* reference count */
I 14
/* begin XXX */
E 14
	struct	inode *f_inode;		/* inode */
E 13
E 12
	union {
D 12
		off_t	f_offset;	/* read/write character pointer */
D 11
		struct chan *f_chan;	/* mpx channel pointer */
E 11
I 9
		struct port *f_port;	/* port (used for pipes, too) */
#ifdef CHAOS
		struct connection *f_conn;
#endif
I 10
#ifdef BBNNET
		struct ucb *f_ucb;      /* net connection block pointer */
#endif BBNNET
E 12
I 12
D 14
		struct f_in {
D 13
			struct inode *fi_inode;
E 13
			off_t fi_offset;
		} f_in;
		struct f_so {
			struct socket *fs_socket;
		} f_so;
E 14
I 14
		struct f_in { off_t fi_offset; } f_in;
		struct f_so { struct socket *fs_socket; } f_so;
E 14
E 12
E 10
E 9
I 5
D 7
#ifdef CHAOS
		struct connection *f_conn;
#endif
E 7
E 5
	} f_un;
D 14
};
E 14
I 12
#define f_offset	f_un.f_in.fi_offset
D 13
#define	f_inode		f_un.f_in.fi_inode
E 13
#define	f_socket	f_un.f_so.fs_socket
I 14
/* end XXX */
E 18
I 18
	short	f_count;	/* reference count */
	short	f_msgcount;	/* references from message queue */
I 28
	struct	ucred *f_cred;	/* credentials associated with descriptor */
E 28
	struct	fileops {
D 28
		int	(*fo_rw)();
E 28
I 28
D 33
		int	(*fo_read)();
		int	(*fo_write)();
E 28
		int	(*fo_ioctl)();
		int	(*fo_select)();
D 21
		int	(*fo_stat)();
E 21
		int	(*fo_close)();
E 33
I 33
D 35
		int	(*fo_read)__P((
				struct file *fp,
				struct uio *uio,
				struct ucred *cred));
		int	(*fo_write)__P((
				struct file *fp,
				struct uio *uio,
				struct ucred *cred));
		int	(*fo_ioctl)__P((
				struct file *fp,
				int com,
				caddr_t data,
				struct proc *p));
		int	(*fo_select)__P((
				struct file *fp,
				int which,
				struct proc *p));
		int	(*fo_close)__P((
				struct file *fp,
				struct proc *p));
E 35
I 35
		int	(*fo_read)	__P((struct file *fp, struct uio *uio,
					    struct ucred *cred));
		int	(*fo_write)	__P((struct file *fp, struct uio *uio,
					    struct ucred *cred));
D 40
		int	(*fo_ioctl)	__P((struct file *fp, int com,
E 40
I 40
		int	(*fo_ioctl)	__P((struct file *fp, u_long com,
E 40
					    caddr_t data, struct proc *p));
		int	(*fo_select)	__P((struct file *fp, int which,
					    struct proc *p));
		int	(*fo_close)	__P((struct file *fp, struct proc *p));
E 35
E 33
	} *f_ops;
D 34
	caddr_t	f_data;		/* inode */
E 34
	off_t	f_offset;
I 34
	caddr_t	f_data;		/* vnode or socket */
E 34
E 18
};
E 14
E 12

D 15
#ifdef	KERNEL
E 15
D 7
extern	struct file file[];		/* the file table itself */
E 7
I 7
D 8
extern	struct file *file, *fileNFILE;	/* the file table itself */
extern	int nfile;
E 8
I 8
D 12
struct	file *file, *fileNFILE;	/* the file table itself */
E 12
I 12
D 30
struct	file *file, *fileNFILE;
E 12
int	nfile;
E 8
E 7
D 13

E 13
D 28
struct	file *getf();
struct	file *falloc();
E 28
I 24
#endif
E 30
I 30
D 34
struct file *file, *fileNFILE;
int nfile;
E 34
I 34
D 39
extern struct file *filehead;	/* head of list of open files */
extern int maxfiles;		/* kernel limit on number of open files */
extern int nfiles;		/* actual number of open files */
E 39
I 39
LIST_HEAD(filelist, file);
extern struct filelist filehead;	/* head of list of open files */
extern int maxfiles;			/* kernel limit on number of open files */
extern int nfiles;			/* actual number of open files */
E 39
E 34
E 30
E 24
D 15
#endif
E 15

D 24
/* flags */
E 24
I 24
D 30
/*
 * flags- also for fcntl call.
 */
E 30
I 30
D 32
/* convert O_RDONLY/O_WRONLY/O_RDWR to FREAD/FWRITE */
E 30
E 24
D 12
#define	FREAD	01
#define	FWRITE	02
#define	FPIPE	04
D 11
#define	FMPX	010
#define	FMPY	020
#define	FMP	030
E 11
I 9
#define	FPORT	040
I 10
#define FNET    0100    /* this is a network entry */
E 12
I 12
D 14
#define	FINODE		0x0		/* descriptor of an inode (pseudo) */
E 14
D 15
#define	FREAD		0x1		/* descriptor read/receive'able */
#define	FWRITE		0x2		/* descriptor write/send'able */
D 14
#define	FSOCKET		0x4		/* descriptor of a socket */
I 13
#define	FPORTAL		0x8		/* descriptor of a portal */
E 14
I 14
/* note: other flags for f_flag defined in fcntl.h */
E 15
I 15
D 18
#define	FREAD		0x001		/* descriptor read/receive'able */
#define	FWRITE		0x002		/* descriptor write/send'able */
#define	FAPPEND		0x004		/* append on each write */
/* the following defines the bits that users can set in f_flag */
#define	FMODES	(FREAD|FWRITE|FAPPEND)
E 18
I 18
#define	FOPEN		(-1)
D 30
#define	FREAD		00001		/* descriptor read/receive'able */
#define	FWRITE		00002		/* descriptor write/send'able */
I 24
#ifndef	F_DUPFD
E 24
#define	FNDELAY		00004		/* no delay */
#define	FAPPEND		00010		/* append on each write */
I 24
#endif
E 24
#define	FMARK		00020		/* mark during gc() */
#define	FDEFER		00040		/* defer for next gc pass */
I 24
#ifndef	F_DUPFD
E 24
#define	FASYNC		00100		/* signal pgrp when data ready */
I 24
#endif
E 24
I 22
#define	FSHLOCK		00200		/* shared lock present */
#define	FEXLOCK		00400		/* exclusive lock present */
E 30
I 30
#define	FREAD		1
#define	FWRITE		2
E 30
E 22

D 30
/* bits to save after open */
D 24
#define	FMASK		00117	
#define	FCNTLCANT	(FREAD|FWRITE|FMARK|FDEFER)
I 19
#endif
E 24
I 24
D 27
#define	FMASK		00113
E 27
I 27
D 29
#define	FMASK		01113
E 29
I 29
#define	FMASK		(FASYNC|FAPPEND|FNDELAY|FWRITE|FREAD)
E 29
E 27
#define	FCNTLCANT	(FREAD|FWRITE|FMARK|FDEFER|FSHLOCK|FEXLOCK)
E 24
E 19

/* open only modes */
#define	FCREAT		01000		/* create if nonexistant */
#define	FTRUNC		02000		/* truncate to zero length */
#define	FEXCL		04000		/* error if already created */
E 18
D 19
#endif
E 19

I 24
#ifndef	F_DUPFD
/* fcntl(2) requests--from <fcntl.h> */
#define	F_DUPFD	0	/* Duplicate fildes */
#define	F_GETFD	1	/* Get fildes flags */
#define	F_SETFD	2	/* Set fildes flags */
#define	F_GETFL	3	/* Get file flags */
#define	F_SETFL	4	/* Set file flags */
#define	F_GETOWN 5	/* Get owner */
#define F_SETOWN 6	/* Set owner */
#endif

E 24
/*
D 18
 * User visible desriptor attributes.
 * These are supplied at open or flock time.
 * FRDONLY, FWRONLY, and FRDWR are
 * converted to FREAD and FWRITE on open.
E 18
I 18
 * User definitions.
E 18
 */
D 18
#define	FRDONLY		0x000		/* open for reading only */
#define	FWRONLY		0x001		/* open for writing only */
#define	FRDWR		0x002		/* open for reading and writing */
#define	FAPPEND		0x004		/* append on each write */
D 17
#define	FRDLOCK		0x008		/* apply read lock */
#define	FWRLOCK		0x010		/* apply write lock */
E 17
I 17
#define	FSHLOCK		0x008		/* apply shared lock */
#define	FEXLOCK		0x010		/* apply exclusive lock */
E 17
#define	FUNLOCK		0x100		/* release all locks */
#define	FCREATE		0x200		/* create file if nonexistant */
#define	FTRUNCATE	0x400		/* truncate file to size 0 on open */
#define	FNBLOCK		0x800		/* don't block on open */
E 18

D 18
/* these are for 3.0 "compatibility" */
#define	O_RDONLY	FRDONLY		/* open for read */
#define	O_WRONLY	FWRONLY		/* open for writing */
#define	O_RDWR		FRDWR		/* open for read & write */
#define	O_NDELAY	FNBLOCK 	/* non-blocking I/O */
#define	O_APPEND	FAPPEND		/* append */
#define	O_CREAT		FCREATE		/* open with file create */
#define	O_TRUNC		FTRUNCATE	/* open with truncation */
D 17
#define	O_EXCL		FWRLOCK		/* exclusive open */
E 17
I 17
#define	O_EXCL		FEXLOCK		/* exclusive open */
E 18
I 18
/*
 * Open call.
 */
#define	O_RDONLY	000		/* open for reading */
#define	O_WRONLY	001		/* open for writing */
#define	O_RDWR		002		/* open for read & write */
D 24
#define	O_NDELAY	004 		/* non-blocking open */
#define	O_APPEND	010		/* append on each write */
E 24
I 24
D 27
#define	O_NDELAY	FNDELAY		/* non-blocking open */
E 27
I 27
#define	O_NDELAY	FNDELAY		/* non-blocking open on file */
#define O_NONBLOCK	FNDELAY		/* ditto */
E 27
#define	O_APPEND	FAPPEND		/* append on each write */
E 24
#define	O_CREAT		FCREAT		/* open with file create */
#define	O_TRUNC		FTRUNC		/* open with truncation */
#define	O_EXCL		FEXCL		/* error on create if file exists */
E 30
I 30
/* kernel only versions -- deprecated, should be removed */
#define	FCREAT		O_CREAT
#define	FDEFER		O_DEFER
#define	FEXCL		O_EXCL
#define	FEXLOCK		O_EXLOCK
#define	FMARK		O_MARK
#define	FSHLOCK		O_SHLOCK
#define	FTRUNC		O_TRUNC
E 30
E 18
E 17

D 18
/* flags supplied to access call */
#define	FACCESS_EXISTS	0x0	/* does file exist */
#define	FACCESS_EXECUTE	0x1	/* is it executable by caller */
#define	FACCESS_WRITE	0x2	/* writable by caller */
#define	FACCESS_READ	0x4	/* readable by caller */
E 18
I 18
D 30
/*
 * Flock call.
 */
#define	LOCK_SH		1	/* shared lock */
#define	LOCK_EX		2	/* exclusive lock */
D 20
#define	LOCK_UN		4	/* unlock */
E 20
I 20
#define	LOCK_NB		4	/* don't block when locking */
#define	LOCK_UN		8	/* unlock */
E 30
I 30
/* bits to save after open */
#define	FMASK		(FREAD|FWRITE|O_APPEND|O_ASYNC|O_NONBLOCK)
/* bits not settable by fcntl(F_SETFL, ...) */
#define	FCNTLCANT	(FREAD|FWRITE|O_DEFER|O_EXLOCK|O_MARK|O_SHLOCK)
E 30
E 20
E 18

D 18
/* flags supplies to lseek call */
#define	FSEEK_ABSOLUTE	0x0	/* absolute offset */
#define	FSEEK_RELATIVE	0x1	/* relative to current offset */
#define	FSEEK_EOF	0x2	/* relative to end of file */
E 18
I 18
D 30
/*
 * Access call.
 */
#define	F_OK		0	/* does file exist */
#define	X_OK		1	/* is it executable by caller */
#define	W_OK		2	/* writable by caller */
#define	R_OK		4	/* readable by caller */
E 30
I 30
#else
E 30
E 18

D 18
/* file types which may be specified to mknod */
#define	FTYPE_CDEV	0x2000	/* character special device */
#define	FTYPE_DIR	0x4000	/* directory */
#define	FTYPE_BDEV	0x8000	/* block special device */
E 18
I 18
D 30
/*
 * Lseek call.
 */
#define	L_SET		0	/* absolute offset */
#define	L_INCR		1	/* relative to current offset */
#define	L_XTND		2	/* relative to end of file */
E 30
I 30
#include <sys/fcntl.h>
#include <sys/unistd.h>
E 30
E 18
I 16

I 18
D 30
#ifdef KERNEL
E 18
D 28
#define	GETF(fp, fd) { \
	if ((unsigned)(fd) >= NOFILE || ((fp) = u.u_ofile[fd]) == NULL) { \
		u.u_error = EBADF; \
		return; \
	} \
}
I 18
#define	DTYPE_INODE	1	/* file */
E 28
I 28
#define	DTYPE_VNODE	1	/* file */
E 28
#define	DTYPE_SOCKET	2	/* communications endpoint */
E 30
#endif
I 30

/* operation for lseek(2); renamed by POSIX 1003.1 to unistd.h */
#define	L_SET		0	/* set file offset to offset */
#define	L_INCR		1	/* set file offset to current plus offset */
#define	L_XTND		2	/* set file offset to EOF plus offset */
E 32
I 32
#endif /* KERNEL */
E 32
E 30
E 18
E 16
E 15
E 14
E 13
E 12
E 10
E 9
E 1
