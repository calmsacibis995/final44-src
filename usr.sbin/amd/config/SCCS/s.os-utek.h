h58619
s 00002/00002/00021
d D 8.1 93/06/06 11:52:24 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00022
d D 5.4 92/02/09 08:31:41 pendry 4 3
c merge in new release
e
s 00005/00005/00018
d D 5.3 91/05/12 15:59:06 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00022
d D 5.2 91/03/17 13:49:59 pendry 2 1
c from amd5.3 alpha11
e
s 00035/00000/00000
d D 5.1 91/03/17 11:49:08 pendry 1 0
c date and time created 91/03/17 11:49:08 by pendry
e
u
U
t
T
I 1
D 3
/* $Id: os-utek.h,v 5.2 91/03/03 20:22:54 jsp Alpha $ */

E 3
/*
D 3
 * Utek 4.0  definitions for Amd (automounter)
 *	from Bill Trost <trost%reed@cse.ogi.edu>
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
D 2
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: os-utek.h,v 5.2.1.1 91/05/07 22:20:06 jsp Alpha $
E 4
I 4
 * $Id: os-utek.h,v 5.2.2.1 1992/02/09 15:10:56 jsp beta $
E 4
 *
 * Utek 4.0  definitions for Amd (automounter)
 *	from Bill Trost <trost%reed@cse.ogi.edu>
E 3
 */

#define	UTEK
#define	__NFS_HEADER__		/* prevent re-inclusion of <sys/nfs.h> */
/* ... and fake the rest */
#include "os-sos3.h"
E 1
