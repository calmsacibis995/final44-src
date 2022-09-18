h00434
s 00002/00002/00032
d D 8.1 93/06/11 15:12:11 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 7.1 93/04/20 18:45:27 torek 1 0
c date and time created 93/04/20 18:45:27 by torek
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * This software was developed by the Computer Systems Engineering group
 * at Lawrence Berkeley Laboratory under DARPA contract BG 91-66 and
 * contributed to Berkeley.
 *
 * All advertising materials mentioning features or use of this software
 * must display the following acknowledgement:
 *	This product includes software developed by the University of
 *	California, Lawrence Berkeley Laboratory.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *
 * from: $Header: openpromio.h,v 1.2 93/04/20 11:14:46 torek Exp $
 */

struct opiocdesc {
	int	op_nodeid;		/* passed or returned node id */
	int	op_namelen;		/* length of op_name */
	char	*op_name;		/* pointer to field name */
	int	op_buflen;		/* length of op_buf (value-result) */
	char	*op_buf;		/* pointer to field value */
};

#define	OPIOCGET	_IOWR('O', 1, struct opiocdesc) /* get openprom field */
#define	OPIOCSET	_IOW('O', 2, struct opiocdesc) /* set openprom field */
#define	OPIOCNEXTPROP	_IOWR('O', 3, struct opiocdesc) /* get next property */
#define	OPIOCGETOPTNODE	_IOR('O', 4, int)	/* get openprom field */
#define	OPIOCGETNEXT	_IOWR('O', 5, int)	/* get next node of node */
#define	OPIOCGETCHILD	_IOWR('O', 6, int)	/* get first child of node */
E 1
