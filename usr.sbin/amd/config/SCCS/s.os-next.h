h51756
s 00002/00002/00051
d D 8.1 93/06/06 11:51:50 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00052
d D 5.5 92/02/09 08:31:25 pendry 5 4
c merge in new release
e
s 00003/00007/00050
d D 5.4 91/05/12 15:59:12 pendry 4 3
c checkpoint for network tape
e
s 00011/00009/00046
d D 5.3 91/04/25 08:34:11 bostic 3 2
c had to move the additional info down, scripts couldn't find the copyright
e
s 00002/00012/00053
d D 5.2 91/03/17 13:49:41 pendry 2 1
c from amd5.3 alpha11
e
s 00065/00000/00000
d D 5.1 91/03/17 11:49:05 pendry 1 0
c date and time created 91/03/17 11:49:05 by pendry
e
u
U
t
T
I 1
D 3
/* $Id: os-next.h,v 5.2.1.1 90/10/21 22:31:00 jsp Exp $ */

E 3
/*
D 3
 * NeXT OS definitions for Amd (automounter)
 *
 * By Bill Trost, Reed College
 * trost%reed@cse.ogi.edu,
 *
 * Derived from the Sun 3.2 definitions for Amd (os-sos3.h).
 *
E 3
 * Copyright (c) 1990 Jan-Simon Pendry
 * Copyright (c) 1990 Imperial College of Science, Technology & Medicine
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
D 2
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by Imperial College of Science, Technology and Medicine, London, UK.
 * The names of the College and University may not be used to endorse
 * or promote products derived from this software without specific
 * prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
I 3
D 4
 */

/* $Id: os-next.h,v 5.2.1.1 90/10/21 22:31:00 jsp Exp $ */

/*
 * NeXT OS definitions for Amd (automounter)
E 4
 *
I 4
D 5
 * $Id: os-next.h,v 5.2.1.3 91/05/07 22:19:51 jsp Alpha $
E 5
I 5
 * $Id: os-next.h,v 5.2.2.1 1992/02/09 15:10:33 jsp beta $
E 5
 *
 * NeXT OS definitions for Amd (automounter)
E 4
 * By Bill Trost, Reed College
 * trost%reed@cse.ogi.edu,
 *
 * Derived from the Sun 3.2 definitions for Amd (os-sos3.h).
E 3
 */

/*
 * Does the compiler grok void *	(NeXT uses gcc)
 */
#define VOIDP

/*
 * Which version of the Sun RPC library we are using
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define RPC_3

/*
 * Which version of the NFS interface are we using.
 * This is the implementation release number, not
 * the protocol revision number.
 */
#define NFS_3

/*
 * Name of filesystem types
 */
#define MOUNT_TYPE_UFS	MOUNT_UFS
#define MOUNT_TYPE_NFS	MOUNT_NFS
#undef MTAB_TYPE_UFS
#define MTAB_TYPE_UFS	"4.3"

/*
 * Where to get NFS definitions
 */
I 2
D 4
 * %sccs.include.redist.c%
E 4
E 2
#define NFS_HDR "misc-next.h"
E 1
