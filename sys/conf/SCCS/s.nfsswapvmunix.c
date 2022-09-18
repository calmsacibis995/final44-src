h41955
s 00002/00002/00124
d D 8.1 93/06/10 21:15:44 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00008/00007/00118
d D 7.2 92/10/11 08:45:35 bostic 2 1
c make kernel includes standard
e
s 00125/00000/00000
d D 7.1 91/03/04 22:31:20 mckusick 1 0
c diskless support from Rick Macklem
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Sample NFS swapvmunix configuration file.
 * This should be filled in by the bootstrap program.
 * See /sys/nfs/nfsdiskless.h for details of the fields.
 */

D 2
#include "../sys/param.h"
#include "../sys/conf.h"
#include "../sys/socket.h"
#include "../sys/mount.h"
#include "../net/if.h"
#include "../nfs/nfsv2.h"
#include "../nfs/nfsdiskless.h"
E 2
I 2
#include <sys/param.h>
#include <sys/conf.h>
#include <sys/socket.h>
#include <sys/mount.h>

#include <net/if.h>
#include <nfs/nfsv2.h>
#include <nfs/nfsdiskless.h>
E 2

extern int nfs_mountroot();
int (*mountroot)() = nfs_mountroot;

dev_t	rootdev = NODEV;
dev_t	argdev  = NODEV;
dev_t	dumpdev = NODEV;

struct	swdevt swdevt[] = {
	{ NODEV,	0,	5000 },	/* happy:/u/swap.dopey  */
	{ 0, 0, 0 }
};
struct nfs_diskless nfs_diskless = {
	{ { 'q', 'e', '0', '\0' },
	  { 0x10, 0x2, { 0x0, 0x0, 0x83, 0x68, 0x30, 0x2, } },
	  { 0x10, 0x2, { 0x0, 0x0, 0x83, 0x68, 0x30, 0xff, } },
	  { 0x10, 0x0, { 0x0, 0x0, 0xff, 0xff, 0xff, 0x0, } },
 	},
	{ 0x10, 0x2, { 0x0, 0x0, 0x83, 0x68, 0x30, 0x12, } },
	{
	  (struct sockaddr *)0, SOCK_DGRAM, 0, (nfsv2fh_t *)0,
	  0, 8192, 8192, 10, 100, (char *)0,
	},
	{
		0xf,
		0x9,
		0x0,
		0x0,
		0x1,
		0x0,
		0x0,
		0x0,
		0xc,
		0x0,
		0x0,
		0x0,
		0x6,
		0x0,
		0x0,
		0x0,
		0x27,
		0x18,
		0x79,
		0x27,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
	},
	{ 0x10, 0x2, { 0x8, 0x1, 0x83, 0x68, 0x30, 0x5, } },
	"happy",
	{
	  (struct sockaddr *)0, SOCK_DGRAM, 0, (nfsv2fh_t *)0,
	  0, 8192, 8192, 10, 100, (char *)0,
	},
	{
		0x0,
		0x9,
		0x0,
		0x0,
		0x1,
		0x0,
		0x0,
		0x0,
		0xc,
		0x0,
		0x0,
		0x0,
		0x2,
		0x0,
		0x0,
		0x0,
		0xd0,
		0x48,
		0x42,
		0x25,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
		0x0,
	},
	{ 0x10, 0x2, { 0x8, 0x1, 0x83, 0x68, 0x30, 0x5, } },
	"happy",
};
E 1
