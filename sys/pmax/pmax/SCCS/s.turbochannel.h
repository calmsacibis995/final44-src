h45136
s 00002/00002/00106
d D 8.1 93/06/10 23:08:02 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00107
d D 7.3 93/05/09 16:01:59 ralph 3 2
c use comments after #endif
e
s 00010/00001/00098
d D 7.2 92/11/15 16:30:35 ralph 2 1
c updates from Rick Macklem for maxine.
e
s 00099/00000/00000
d D 7.1 92/03/01 10:16:39 bostic 1 0
c date and time created 92/03/01 10:16:39 by bostic
e
u
U
t
T
I 1
/*-
D 4
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * This code is derived from software contributed to Berkeley by
 * The Mach Operating System project at Carnegie-Mellon University
 * and Ralph Campbell.
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 */

/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and
 * its documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" 
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND 
 * FOR ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 *
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 *
 * any improvements or extensions that they make and grant Carnegie the
 * rights to redistribute these changes.
 */

/*
 * 	Created, from the DEC specs:
 * 	"TURBOchannel Hardware Specification"
 * 	EK-369AA-OD-005, Version 005, July 1990
 *
 *	File: tc.h
 * 	Author: Alessandro Forin, Carnegie Mellon University
 *	Date:	9/90
 *
 *	Definitions for the TURBOchannel BUS.
 */

/*
I 2
 * Max conceivable number of slots on the TC
 */
#define	TC_MAX_SLOTS		8
#define	TC_MAX_LOGICAL_SLOTS	12

/*
E 2
 * Address map specifications for any TC option
 * These are offset from the option's base address
 */

#define TC_OFF_ROM		0x000003e0	/* required ROM info */
#define TC_OFF_PROTO_ROM	0x003c03e0	/* 'obsolete' alternate */

#define TC_ROM_TEST_DATA_SIZE	16
#define TC_ROM_SLEN		4
#define TC_ROM_LLEN		8

typedef struct {
	unsigned char	value;
	char		pad[3];
} tc_padded_char_t;

typedef struct {
	tc_padded_char_t	rom_width;	/* legal: 1 2 4 */
	tc_padded_char_t	rom_stride;	/* legal: 4 */
	tc_padded_char_t	rom_size;	/* legal: 0-255, unit: 8kb */
	tc_padded_char_t	slot_size;	/* legal: 1-128, unit: 4Mb */
	unsigned char		test_data[TC_ROM_TEST_DATA_SIZE];
						/* must always contain:
						/* x55 x00 xaa xff
						/* (each byte is repeated
						/*  rom_stride times) */
	tc_padded_char_t	firmware_rev[TC_ROM_LLEN];
	tc_padded_char_t	vendor_name[TC_ROM_LLEN];
	tc_padded_char_t	module_name[TC_ROM_LLEN];
	tc_padded_char_t	host_firmware_type[TC_ROM_SLEN];
} tc_rommap_t;

typedef struct {
	u_char	present;			/* and do we handle it */
	u_char	slot_size;			/* how many TC slots */
	u_char	rom_width;			/* bytewide or.. */
I 2
	u_char	unit;				/* Device unit number */
E 2
	char	module_name[TC_ROM_LLEN+1];	/* ROM name */
	char	module_id[TC_ROM_LLEN * 2+1];	/* vendor and rev */
D 2
	caddr_t	module_address;			/* TC starting address */
E 2
I 2
	u_long		k1seg_address;		/* TC starting address */
	char		*driver_name;		/* software name */
	void		(*intr)();		/* interrupt routine */
E 2
} tc_option_t;


#ifdef KERNEL
extern	tc_option_t	tc_slot_info[];

extern	void (*tc_slot_hand_fill) __P((tc_option_t *));
D 3
#endif KERNEL
E 3
I 3
#endif /* KERNEL */
E 3
E 1
