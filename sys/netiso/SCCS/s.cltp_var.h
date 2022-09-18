h15937
s 00002/00002/00026
d D 8.1 93/06/10 23:18:58 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00027
d D 7.3 90/06/28 21:44:11 bostic 3 2
c new copyright notice
e
s 00000/00000/00038
d D 7.2 90/01/16 23:15:23 sklower 2 1
c checkpoint for initial shipment to NIST
e
s 00038/00000/00000
d D 7.1 89/11/15 19:41:07 sklower 1 0
c date and time created 89/11/15 19:41:07 by sklower
e
u
U
t
T
I 1
/*
D 4
 * Copyright (c) 1989 Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
D 3
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
 *
 *	%W% (Berkeley) %G%
 */

#define UD_TPDU_type	0x40	/* packet type */

#define CLTPOVAL_SRC	0xc1	/* Source TSAP -- required */
#define CLTPOVAL_DST	0xc2	/* Destination TSAP -- required */
#define CLTPOVAL_CSM	0xc3	/* Checksum parameter -- optional */

struct	cltpstat {
	int	cltps_hdrops;
	int	cltps_badsum;
	int	cltps_badlen;
	int	cltps_noport;
	int	cltps_ipackets;
	int	cltps_opackets;
};

#ifdef KERNEL
struct	isopcb cltb;
struct	cltpstat cltpstat;
#endif
E 1
