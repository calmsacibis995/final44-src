h15216
s 00053/00000/00062
d D 8.2 95/03/30 11:26:23 mckusick 8 7
c massive update to incorporate version 3 protocol from Rick Macklem
e
s 00002/00002/00060
d D 8.1 93/06/10 23:40:03 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00060
d D 7.5 92/01/14 12:41:10 mckusick 6 5
c update from Rick Macklem (including leases)
e
s 00001/00011/00060
d D 7.4 90/06/28 21:54:19 bostic 5 4
c new copyright notice
e
s 00003/00001/00068
d D 7.3 90/05/14 11:35:29 mckusick 4 3
c "update from Rick Macklem adding TCP support to NFS"
e
s 00001/00002/00068
d D 7.2 89/12/20 12:30:58 mckusick 3 1
c "December update from Rick Macklem"
e
s 00000/00000/00070
d R 7.2 89/08/30 20:30:17 macklem 2 1
c first buffer cache implementation; name cache usage; code cleanups
e
s 00070/00000/00000
d D 7.1 89/07/05 11:32:29 mckusick 1 0
c first bootable NFS from Rick Macklem
e
u
U
t
T
I 1
/*
D 7
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * This code is derived from software contributed to Berkeley by
 * Rick Macklem at The University of Guelph.
 *
D 5
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
E 5
I 5
 * %sccs.include.redist.c%
E 5
 *
 *	%W% (Berkeley) %G%
 */

I 8

#ifndef _NFS_RPCV2_H_
#define _NFS_RPCV2_H_

E 8
/*
 * Definitions for Sun RPC Version 2, from
D 3
 * "Remote Procedure Call Protocol Specification" in the manual
 * "Networking on the Sun Workstation", Part #800-1324-03 Rev. B
E 3
I 3
 * "RPC: Remote Procedure Call Protocol Specification" RFC1057
E 3
 */

/* Version # */
#define	RPC_VER2	2

D 4
/* Authentication Flavours */
E 4
I 4
/* Authentication */
E 4
#define	RPCAUTH_NULL	0
#define	RPCAUTH_UNIX	1
#define	RPCAUTH_SHORT	2
I 8
#define RPCAUTH_KERB4	4
E 8
I 6
#define	RPCAUTH_NQNFS	300000
E 6
I 4
#define	RPCAUTH_MAXSIZ	400
I 8
#define	RPCVERF_MAXSIZ	12	/* For Kerb, can actually be 400 */
E 8
#define	RPCAUTH_UNIXGIDS 16
E 4

I 8
/*
 * Constants associated with authentication flavours.
 */
#define RPCAKN_FULLNAME	0
#define RPCAKN_NICKNAME	1

E 8
/* Rpc Constants */
#define	RPC_CALL	0
#define	RPC_REPLY	1
#define	RPC_MSGACCEPTED	0
#define	RPC_MSGDENIED	1
#define	RPC_PROGUNAVAIL	1
#define	RPC_PROGMISMATCH	2
#define	RPC_PROCUNAVAIL	3
#define	RPC_GARBAGE	4		/* I like this one */
#define	RPC_MISMATCH	0
D 6
#define	RPC_AUTHFAIL	1
E 6
I 6
#define	RPC_AUTHERR	1
E 6

/* Authentication failures */
#define	AUTH_BADCRED	1
#define	AUTH_REJECTCRED	2
#define	AUTH_BADVERF	3
#define	AUTH_REJECTVERF	4
#define	AUTH_TOOWEAK	5		/* Give em wheaties */

/* Sizes of rpc header parts */
#define	RPC_SIZ		24
#define	RPC_REPLYSIZ	28

/* RPC Prog definitions */
#define	RPCPROG_MNT	100005
#define	RPCMNT_VER1	1
#define	RPCMNT_MOUNT	1
#define	RPCMNT_DUMP	2
#define	RPCMNT_UMOUNT	3
#define	RPCMNT_UMNTALL	4
#define	RPCMNT_EXPORT	5
#define	RPCMNT_NAMELEN	255
#define	RPCMNT_PATHLEN	1024
#define	RPCPROG_NFS	100003
I 8

/*
 * Structures used for RPCAUTH_KERB4.
 */
struct nfsrpc_fullverf {
	u_long		t1;
	u_long		t2;
	u_long		w2;
};

struct nfsrpc_fullblock {
	u_long		t1;
	u_long		t2;
	u_long		w1;
	u_long		w2;
};

struct nfsrpc_nickverf {
	u_long			kind;
	struct nfsrpc_fullverf	verf;
};

/*
 * and their sizes in bytes.. If sizeof (struct nfsrpc_xx) != these
 * constants, well then things will break in mount_nfs and nfsd.
 */
#define RPCX_FULLVERF	12
#define RPCX_FULLBLOCK	16
#define RPCX_NICKVERF	16

#ifdef NFSKERB
XXX
#else
typedef u_char			NFSKERBKEY_T[2];
typedef u_char			NFSKERBKEYSCHED_T[2];
#endif
#define NFS_KERBSRV	"rcmd"		/* Kerberos Service for NFS */
#define NFS_KERBTTL	(30 * 60)	/* Credential ttl (sec) */
#define NFS_KERBCLOCKSKEW (5 * 60)	/* Clock skew (sec) */
#define NFS_KERBW1(t)	(*((u_long *)(&((t).dat[((t).length + 3) & ~0x3]))))
#endif
E 8
E 1
