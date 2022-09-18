h65183
s 00002/00002/00037
d D 8.1 93/06/06 11:50:38 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00039/00000/00000
d D 5.1 92/05/31 10:41:14 pendry 1 0
c date and time created 92/05/31 10:41:14 by pendry
e
u
U
t
T
I 1
/*
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 2
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 */

#include <sys/fstyp.h>

struct ufs_args {
	char *fspec;
};

struct nfs_args {
        struct sockaddr_in      *addr;          /* file server address */
        fhandle_t               *fh;            /* File handle to be mounted */
        int                     flags;          /* flags */
        int                     wsize;          /* write size in bytes */
        int                     rsize;          /* read size in bytes */
        int                     timeo;          /* initial timeout in .1 secs *
/
        int                     retrans;        /* times to retry send */
        char                    *hostname;      /* server's name */
};
#define NFSMNT_SOFT     0x001   /* soft mount (hard is default) */
#define NFSMNT_WSIZE    0x002   /* set write size */
#define NFSMNT_RSIZE    0x004   /* set read size */
#define NFSMNT_TIMEO    0x008   /* set initial timeout (= 1.6 sec) */
#define NFSMNT_RETRANS  0x010   /* set number of request retrys */
#define NFSMNT_HOSTNAME 0x020   /* set hostname for error printf */
#define NFSMNT_INT	0x040	/* allow interrupts on hard mount */
E 1
