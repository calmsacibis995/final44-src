h16101
s 00000/00000/00024
d D 8.1 93/06/10 22:43:45 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00024/00000/00000
d D 7.1 93/06/10 22:43:43 bostic 1 0
c date and time created 93/06/10 22:43:43 by bostic
e
u
U
t
T
I 1
/*-
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* from: $Header: bpf_compat.h,v 1.1 92/05/22 15:33:20 mccanne Exp $ (LBL) */

/*
 * Some hacks for compatibility across SunOS and 4.4BSD.  We emulate malloc
 * and free with mbuf clusters.  We store a pointer to the mbuf in the first
 * word of the mbuf and return 8 bytes passed the start of data (for double
 * word alignment).  We cannot just use offsets because clusters are not at
 * a fixed offset from the associated mbuf.  Sorry for this kludge.
 */
#define malloc(size, type, canwait) bpf_alloc(size, canwait)
#define free(cp, type) m_free(*(struct mbuf **)(cp - 8))
#define M_WAITOK M_WAIT

/* This mapping works for our purposes. */
#define ERESTART EINTR
E 1
