h26203
s 00002/00002/00071
d D 8.1 93/06/02 19:53:36 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00036/00021/00037
d D 7.4 91/05/04 15:08:06 karels 4 3
c (since 7.2:) change filedesc to point to one array of files/flags;
c initial allocation is in filedesc0 along with header, and expanded tables
c replace that one rather than augmenting it
e
s 00014/00033/00044
d D 7.3 91/03/17 15:34:00 karels 3 2
c more-or-less working with new proc & user structs
e
s 00005/00002/00072
d D 7.2 91/02/05 17:04:25 bostic 2 1
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00074/00000/00000
d D 7.1 91/01/10 23:37:32 mckusick 1 0
c date and time created 91/01/10 23:37:32 by mckusick
e
u
U
t
T
I 1
/*
D 5
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

D 2
#ifndef _FILEDESC_
E 2
I 2
D 4
#ifndef _FILEDESC_H_
#define _FILEDESC_H_

E 4
E 2
/*
D 4
 * This structure is used for the management of descriptors.
 * It may be shared by multiple threads.
E 4
I 4
 * This structure is used for the management of descriptors.  It may be
 * shared by multiple processes.
E 4
 *
D 4
 * A process is initially started out with NDFILE worth of
 * descriptors, selected to be enough for typical applications
 * based on the historic limit of 20 open files. Additional
D 3
 * descriptors may be allocated up to a system defined limit
 * defined by the global variable nofile; the initial value
 * of nofile is set to NOFILE. The initial expansion is set to
 * NDEXTENT; each time it runs out it is doubled until nofile
 * is reached. NDEXTENT should be selected to be the biggest
 * multiple of OFILESIZE (see below) that will fit in a
 * power-of-two sized piece of memory.
E 3
I 3
 * descriptors may be allocated up to a process' resource limit.
 * The initial expansion is set to NOEXTENT; each time it runs out,
 * it is doubled until the resource limit is reached. NOEXTENT should
 * be selected to be the biggest multiple of OFILESIZE (see below)
E 4
I 4
 * A process is initially started out with NDFILE descriptors stored within
 * this structure, selected to be enough for typical applications based on
 * the historical limit of 20 open files (and the usage of descriptors by
 * shells).  If these descriptors are exhausted, a larger descriptor table
 * may be allocated, up to a process' resource limit; the internal arrays
 * are then unused.  The initial expansion is set to NDEXTENT; each time
 * it runs out, it is doubled until the resource limit is reached. NDEXTENT
 * should be selected to be the biggest multiple of OFILESIZE (see below)
E 4
 * that will fit in a power-of-two sized piece of memory.
E 3
 */
D 3
#define NDFILE		20
#define NDEXTENT	25
E 3
I 3
D 4
#define NOEXTENT	25		/* 125 bytes in 128-byte alloc. */ 
E 4
I 4
#define NDFILE		20
#define NDEXTENT	50		/* 250 bytes in 256-byte alloc. */ 
E 4
E 3

struct filedesc {
I 3
	struct	file **fd_ofiles;	/* file structures for open files */
	char	*fd_ofileflags;		/* per-process open file flags */
E 3
	struct	vnode *fd_cdir;		/* current directory */
	struct	vnode *fd_rdir;		/* root directory */
I 3
	int	fd_nfiles;		/* number of open files allocated */
D 4
	int	fd_lastfile;		/* high-water mark of fd_ofiles */
	int	fd_freefile;		/* approx. next free file */
E 4
I 4
	u_short	fd_lastfile;		/* high-water mark of fd_ofiles */
	u_short	fd_freefile;		/* approx. next free file */
E 4
E 3
	u_short	fd_cmask;		/* mask for file creation */
	u_short	fd_refcnt;		/* reference count */
D 3
	short	fd_lastfile;		/* high-water mark of fd_ofile */
	short	fd_maxfiles;		/* maximum number of open files */
	struct	file *fd_ofile[NDFILE];	/* file structures for open files */
	struct	file **fd_moreofiles;	/* the rest of the open files */
	char	fd_ofileflags[NDFILE];	/* per-process open file flags */
	char	*fd_moreofileflags;	/* the rest of the open file flags */
	long	fd_spare;		/* unused to round up to power of two */
E 3
};

/*
I 4
 * Basic allocation of descriptors:
 * one of the above, plus arrays for NDFILE descriptors.
 */
struct filedesc0 {
	struct	filedesc fd_fd;
	/*
	 * These arrays are used when the number of open files is
	 * <= NDFILE, and are then pointed to by the pointers above.
	 */
	struct	file *fd_dfiles[NDFILE];
	char	fd_dfileflags[NDFILE];
};

/*
E 4
 * Per-process open flags.
 */
#define	UF_EXCLOSE 	0x01		/* auto-close on exec */
#define	UF_MAPPED 	0x02		/* mapped from device */

/*
D 4
 * Data structure access macros.
E 4
I 4
 * Storage required per open file descriptor.
E 4
 */
D 3
#if !defined(vax) && !defined(tahoe)
#define OFILE(fd, indx) ((indx) < NDFILE ? \
	(fd)->fd_ofile[indx] : \
	(fd)->fd_moreofiles[(indx) - NDFILE])
#define OFILEFLAGS(fd, indx) ((indx) < NDFILE ? \
	(fd)->fd_ofileflags[indx] : \
	(fd)->fd_moreofileflags[(indx) - NDFILE])
E 3
I 3
D 4
#define OFILE(fd, indx)	((fd)->fd_ofiles[indx])
#define OFILEFLAGS(fd, indx) ((fd)->fd_ofileflags[indx])
E 4
E 3
#define OFILESIZE (sizeof(struct file *) + sizeof(char))
D 3
#else
/* PCC cannot handle above as lvalues */
struct file **ofilefunc();
char *ofileflagsfunc();
#define OFILE(fd, indx) *ofilefunc(fd, indx)
#define OFILEFLAGS(fd, indx) *ofileflagsfunc(fd, indx)
#define OFILESIZE (sizeof(struct file *) + sizeof(char))
#endif
E 3

I 4
#ifdef KERNEL
E 4
/*
 * Kernel global variables and routines.
 */
D 3
extern struct filedesc *fddup();
extern int nofile;
E 3
I 3
D 4
extern struct filedesc *fdcopy();
E 3
D 2
#endif _FILEDESC_
E 2
I 2

#endif /* !_FILEDESC_H_ */
E 4
I 4
int	fdalloc __P((struct proc *p, int want, int *result));
int	fdavail __P((struct proc *p, int n));
int	falloc __P((struct proc *p, struct file **resultfp, int *resultfd));
struct	filedesc *fdcopy __P((struct proc *p));
void	fdfree __P((struct proc *p));
#endif
E 4
E 2
E 1
