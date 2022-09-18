h21585
s 00006/00003/00030
d D 8.4 95/01/09 18:16:07 cgd 12 11
c 64-bit changes: ioctl cmd -> u_long, some protos.  some style, return vals.
e
s 00002/00002/00031
d D 8.3 94/11/21 14:52:13 mckusick 11 9
c NOCRED becomes NULL
e
s 00001/00002/00031
d R 8.3 94/11/21 14:16:05 mckusick 10 9
c delete FSCRED; change NOCRED to be NULL
e
s 00003/00003/00030
d D 8.2 94/01/04 16:16:56 bostic 9 8
c A foolish consistency is the hobgoblin of little minds. -- Emerson
e
s 00002/00002/00031
d D 8.1 93/06/02 19:56:28 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00032
d D 7.7 93/05/24 23:24:34 torek 7 6
c pedantically ANSI, i.e., nothing after #else/#endif
e
s 00002/00001/00031
d D 7.6 93/04/28 17:11:13 mckusick 6 5
c add FSCRED to identify opens by filesystems
e
s 00004/00003/00028
d D 7.5 91/02/05 17:03:49 bostic 5 4
c first pass at function prototypes with cdefs.h
c protect include files included by other include files with #ifndef _NAME_H_
e
s 00001/00011/00030
d D 7.4 90/06/28 22:01:35 bostic 4 3
c new copyright notice
e
s 00000/00005/00041
d D 7.3 89/08/26 16:41:31 karels 3 2
c no real uid in credentials (no one should look at it!)
e
s 00001/00000/00045
d D 7.2 89/08/26 14:17:11 mckusick 2 1
c generalize the buffer pool so that NFS can become a client
e
s 00045/00000/00000
d D 7.1 89/04/24 19:09:47 mckusick 1 0
c first bootable vnodes
e
u
U
t
T
I 1
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
D 4
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
 *	%W% (Berkeley) %G%
 */

D 5
#ifndef _UCRED_
#define	_UCRED_
E 5
I 5
D 9
#ifndef _UCRED_H_
#define	_UCRED_H_
E 9
I 9
#ifndef _SYS_UCRED_H_
#define	_SYS_UCRED_H_
E 9
E 5

/*
 * Credentials.
 */
struct ucred {
	u_short	cr_ref;			/* reference count */
	uid_t	cr_uid;			/* effective user id */
	short	cr_ngroups;		/* number of groups */
	gid_t	cr_groups[NGROUPS];	/* groups */
D 3
	/*
	 * The following either should not be here,
	 * or should be treated as opaque
	 */
	uid_t	cr_ruid;		/* real uid */
E 3
};
#define cr_gid cr_groups[0]
I 2
D 6
#define NOCRED ((struct ucred *)-1)
E 6
I 6
D 11
#define NOCRED ((struct ucred *)-1)	/* no credential available */
#define FSCRED ((struct ucred *)-2)	/* filesystem credential */
E 11
I 11
#define NOCRED ((struct ucred *)0)	/* no credential available */
#define FSCRED ((struct ucred *)-1)	/* filesystem credential */
E 11
E 6
E 2

#ifdef KERNEL
#define	crhold(cr)	(cr)->cr_ref++
D 12
struct ucred *crget();
struct ucred *crcopy();
struct ucred *crdup();
E 12
I 12

struct ucred	*crcopy __P((struct ucred *cr));
struct ucred	*crdup __P((struct ucred *cr));
void		crfree __P((struct ucred *cr));
struct ucred	*crget __P((void));
int		suser __P((struct ucred *cred, u_short *acflag));
E 12
D 7
#endif KERNEL
E 7
I 7
#endif /* KERNEL */
E 7
D 5
#endif _UCRED_
E 5
I 5

D 9
#endif /* !_UCRED_H_ */
E 9
I 9
#endif /* !_SYS_UCRED_H_ */
E 9
E 5
E 1
