/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	table.c,v $
 * Revision 2.1.1.1  90/02/09  17:28:33  rvb
 * 	Add Intel copyright
 * 	[90/02/09            rvb]
 * 
 */

/*
 * 			INTEL CORPORATION PROPRIETARY INFORMATION
 *
 *	This software is supplied under the terms of a license  agreement or 
 *	nondisclosure agreement with Intel Corporation and may not be copied 
 *	nor disclosed except in accordance with the terms of that agreement.
 *
 *	Copyright 1988 Intel Corporation
 * Copyright 1988, 1989 by Intel Corporation
 */

#define NGDTENT		6
#define GDTLIMIT	48	/* NGDTENT * 8 */

/*  Segment Descriptor
 *
 * 31          24         19   16                 7           0
 * ------------------------------------------------------------
 * |             | |B| |A|       | |   |1|0|E|W|A|            |
 * | BASE 31..24 |G|/|0|V| LIMIT |P|DPL|  TYPE   | BASE 23:16 |
 * |             | |D| |L| 19..16| |   |1|1|C|R|A|            |
 * ------------------------------------------------------------
 * |                             |                            |
 * |        BASE 15..0           |       LIMIT 15..0          |
 * |                             |                            |
 * ------------------------------------------------------------
 */

struct seg_desc {
	unsigned short	limit_15_0;
	unsigned short	base_15_0;
	unsigned char	base_23_16;
	unsigned char	bit_15_8;
	unsigned char	bit_23_16;
	unsigned char	base_31_24;
	};


struct seg_desc	Gdt[NGDTENT] = {
	{0x0, 0x0, 0x0, 0x0, 0x0, 0x0},		/* 0x0 : null */
	{0xFFFF, 0x1000, 0x0, 0x9E, 0x40, 0x0},	/* 0x8 : boot code */
	{0xFFFF, 0x1000, 0x0, 0x92, 0x40, 0x0},	/* 0x10 : boot data */
	{0xFFFF, 0x1000, 0x0, 0x9E, 0x0, 0x0},	/* 0x18 : boot code, 16 bits */
	{0xFFFF, 0x0, 0x0, 0x92, 0xCF, 0x0},	/* 0x20 : init data */
	{0xFFFF, 0x0, 0x0, 0x9E, 0xCF, 0x0}	/* 0x28 : init code */
	};


struct pseudo_desc {
	unsigned short	limit;
	unsigned short	base_low;
	unsigned short	base_high;
	};

struct pseudo_desc Gdtr = { GDTLIMIT, 0x1200, 0 }; 
			/* boot is loaded at 4k, Gdt is located at 4k+512 */
