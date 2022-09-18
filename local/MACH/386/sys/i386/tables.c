/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	tables.c,v $
 * Revision 2.2.1.3  90/12/07  22:53:33  rvb
 * 	Add t_bitmap to allow v8086 tasks do vga and other groovy stuff
 * 	directly.
 * 	[90/11/27            rvb]
 * 
 * Revision 2.2.1.2  90/11/27  13:40:31  rvb
 * 	Change Prime copyright as per Peter J. Weyman authorization.
 * 	[90/11/19            rvb]
 * 
 * Revision 2.2.1.1  89/10/22  11:31:43  rvb
 * 	Revision 1.2  89/10/12  12:19:27  kupfer
 * 	Allow breakpoint trap in user mode.
 * 
 * Revision 2.2  89/09/25  12:32:52  rvb
 * 	This is UNPUBLISHED PROPRIETARY SOURCE CODE of Prime Computer, Inc.
 * 	[89/09/23            rvb]
 * 
 */

/*
Copyright (c) 1988,1989 Prime Computer, Inc.  Natick, MA 01760
All Rights Reserved.

Permission to use, copy, modify, and distribute this
software and its documentation for any purpose and
without fee is hereby granted, provided that the above
copyright notice appears in all copies and that both the
copyright notice and this permission notice appear in
supporting documentation, and that the name of Prime
Computer, Inc. not be used in advertising or publicity
pertaining to distribution of the software without
specific, written prior permission.

THIS SOFTWARE IS PROVIDED "AS IS", AND PRIME COMPUTER,
INC. DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  IN
NO EVENT SHALL PRIME COMPUTER, INC.  BE LIABLE FOR ANY
SPECIAL, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY
DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR
PROFITS, WHETHER IN ACTION OF CONTRACT, NEGLIGENCE, OR
OTHER TORTIOUS ACTION, ARISING OUR OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include <sys/types.h>
#include <i386/pmap.h>
#include <mach/i386/vm_param.h>
#include <i386/pcb.h>

pt_entry_t kpde[];	/* kernel's page descriptor table */


extern trap_handler(), system_call(), interrupt(), vstart(), sig_clean();

/*
**    386 Interrupt Descriptor Table - TRAPS
*/

extern trp_divr(), trp_debg(), int__nmi(), trp_brpt(); 
extern trp_over(), flt_bnds(), flt_opcd(), flt_ncpr(); 
extern abt_dblf(), abt_over(), flt_btss(), flt_bseg();
extern flt_bstk(), flt_prot(), trp_0x0F(), flt_page();
extern flt_bcpr(), trp_0x11(), trp_0x12(), trp_0x13();
extern trp_0x14(), trp_0x15(), trp_0x16(), trp_0x17();
extern trp_0x18(), trp_0x19(), trp_0x1A(), trp_0x1B();
extern trp_0x1C(), trp_0x1D(), trp_0x1E(), trp_0x1F();
extern trp_0x20(), trp_0x21(), trp_0x22(), trp_0x23();
extern trp_0x24(), trp_0x25(), trp_0x26(), trp_0x27();
extern trp_0x28(), trp_0x29(), trp_0x2A(), trp_0x2B();
extern trp_0x2C(), trp_0x2D(), trp_0x2E(), trp_0x2F();
extern trp_0x30(), trp_0x31(), trp_0x32(), trp_0x33();
extern trp_0x34(), trp_0x35(), trp_0x36(), trp_0x37();
extern trp_0x38(), trp_0x39(), trp_0x3A(), trp_0x3B();
extern trp_0x3C(), trp_0x3D(), trp_0x3E(), trp_0x3F();

/*
**   386 Interrupt Descriptor Table - INTERRUPTS
*/

extern int_0x00(), int_0x01(), int_0x02(), int_0x03();
extern int_0x04(), int_0x05(), int_0x06(), int_0x07();
extern int_0x08(), int_0x09(), int_0x0A(), int_0x0B();
extern int_0x0C(), int_0x0D(), int_0x0E(), int_0x0F();
extern int_0x10(), int_0x11(), int_0x12(), int_0x13();
extern int_0x14(), int_0x15(), int_0x16(), int_0x17();
extern int_0x18(), int_0x19(), int_0x1A(), int_0x1B();
extern int_0x1C(), int_0x1D(), int_0x1E(), int_0x1F();
extern int_0x20(), int_0x21(), int_0x22(), int_0x23();
extern int_0x24(), int_0x25(), int_0x26(), int_0x27();
extern int_0x28(), int_0x29(), int_0x2A(), int_0x2B();
extern int_0x2C(), int_0x2D(), int_0x2E(), int_0x2F();
extern int_0x30(), int_0x31(), int_0x32(), int_0x33();
extern int_0x34(), int_0x35(), int_0x36(), int_0x37();
extern int_0x38(), int_0x39(), int_0x3A(), int_0x3B();
extern int_0x3C(), int_0x3D(), int_0x3E(), int_0x3F();
extern int_0x40(), int_0x41(), int_0x42(), int_0x43();
extern int_0x44(), int_0x45(), int_0x46(), int_0x47();
extern int_0x48(), int_0x49(), int_0x4A(), int_0x4B();
extern int_0x4C(), int_0x4D(), int_0x4E(), int_0x4F();
extern int_0x50(), int_0x51(), int_0x52(), int_0x53();
extern int_0x54(), int_0x55(), int_0x56(), int_0x57();
extern int_0x58(), int_0x59(), int_0x5A(), int_0x5B();
extern int_0x5C(), int_0x5D(), int_0x5E(), int_0x5F();
extern int_0x60(), int_0x61(), int_0x62(), int_0x63();
extern int_0x64(), int_0x65(), int_0x66(), int_0x67();
extern int_0x68(), int_0x69(), int_0x6A(), int_0x6B();
extern int_0x6C(), int_0x6D(), int_0x6E(), int_0x6F();
extern int_0x70(), int_0x71(), int_0x72(), int_0x73();
extern int_0x74(), int_0x75(), int_0x76(), int_0x77();
extern int_0x78(), int_0x79(), int_0x7A(), int_0x7B();
extern int_0x7C(), int_0x7D(), int_0x7E(), int_0x7F();
extern int_0x80(), int_0x81(), int_0x82(), int_0x83();
extern int_0x84(), int_0x85(), int_0x86(), int_0x87();
extern int_0x88(), int_0x89(), int_0x8A(), int_0x8B();
extern int_0x8C(), int_0x8D(), int_0x8E(), int_0x8F();
extern int_0x90(), int_0x91(), int_0x92(), int_0x93();
extern int_0x94(), int_0x95(), int_0x96(), int_0x97();
extern int_0x98(), int_0x99(), int_0x9A(), int_0x9B();
extern int_0x9C(), int_0x9D(), int_0x9E(), int_0x9F();
extern int_0xA0(), int_0xA1(), int_0xA2(), int_0xA3();
extern int_0xA4(), int_0xA5(), int_0xA6(), int_0xA7();
extern int_0xA8(), int_0xA9(), int_0xAA(), int_0xAB();
extern int_0xAC(), int_0xAD(), int_0xAE(), int_0xAF();
extern int_0xB0(), int_0xB1(), int_0xB2(), int_0xB3();
extern int_0xB4(), int_0xB5(), int_0xB6(), int_0xB7();
extern int_0xB8(), int_0xB9(), int_0xBA(), int_0xBB();
extern int_0xBC(), int_0xBD(), int_0xBE(), int_0xBF();

extern struct tss386 ktss, ltss, dftss;
extern struct fakegate idt[]; 

/*
 *	386 Global Descriptor Table
 */

struct fakedesc gdt[GDTSZ] = {
/* 00 */ nulldesc(),
/* 01 */ mkdesc((char *)&gdt[0], GDTSZ*sizeof(struct fakedesc), 0x93,0), 
/* 02 */ mkdesc((char *)&idt[0], IDTSZ*sizeof(struct fakegate), 0x92, 0), 
/* 03 */ nulldesc() ,
/* 04 */ nulldesc() ,
/* 05 */ nulldesc() ,
/* 06 */ nulldesc() ,
/* 07 */ nulldesc() ,
/* 08 */ nulldesc() ,
/* 09 */ nulldesc() ,	
/* 0A */ nulldesc() ,	
/* 0B */ nulldesc() ,
/* 0C */ nulldesc() ,
/* 0D */ nulldesc() ,
/* 0E */ nulldesc() ,
/* 0F */ nulldesc() ,
/* 10 */ nulldesc() ,
/* 11 */ nulldesc() ,
/* 12 */ nulldesc() ,
/* 13 */ nulldesc() ,
/* 14 */ nulldesc() ,
/* 15 */ nulldesc() ,
/* 16 */ nulldesc() ,
/* 17 */ nulldesc() ,
/* 18 */ nulldesc() ,
/* 19 */ nulldesc() ,
/* 1A */ nulldesc() ,
/* 1B */ nulldesc() ,
/* 1C */ nulldesc() ,
/* 1D */ nulldesc() ,
/* 1E */ nulldesc() ,
/* 1F */ nulldesc() ,
/* 20 */ nulldesc() ,
/* 21 */ nulldesc() ,
/* 22 */ nulldesc() ,
/* 23 */ nulldesc() ,
/* 24 */ nulldesc() ,
/* 25 */ nulldesc() ,
/* 26 */ nulldesc() ,
/* 27 */ nulldesc() ,
/* 28 */ kldtdesc(0),
/* 29 */ ktssdesc((char *)&ktss),
/* 2A */ ktssdesc((char *)&ktss),
/* 2B */ ktextdesc(0),
/* 2C */ kdatadesc(0),
/* 2D */ ktssdesc((char *)&dftss),
/* 2E */ ktssdesc((char *)&ltss),
/* 2F */ nulldesc() ,
/* 30 */ nulldesc() ,
/* 31 */ nulldesc() ,
/* 32 */ nulldesc() ,
/* 33 */ nulldesc() ,
/* 34 */ nulldesc() ,
/* 35 */ nulldesc() ,
/* 36 */ nulldesc() ,
};


struct fakegate idt[IDTSZ] = {
/* 00 */	mktrpg(trp_divr),
/* 01 */	mkintg(trp_debg), 
/* 02 */	mkintg(int__nmi),	
/* 03 */	mkusrtrpg(trp_brpt),
/* 04 */	mktrpg(trp_over),
/* 05 */	mktrpg(flt_bnds),
/* 06 */	mktrpg(flt_opcd),
/* 07 */	mktrpg(flt_ncpr),
/* 08 */	{(long)0L,(short)DFTSSSEL,(char)0,(char)(GATE_KACC|GATE_TSS)},
/* 09 */	mktrpg(abt_over),
/* 0A */	mktrpg(flt_btss),
/* 0B */	mktrpg(flt_bseg),
/* 0C */	mktrpg(flt_bstk),
/* 0D */	mktrpg(flt_prot),
/* 0E */	mktrpg(flt_page),
/* 0F */	mktrpg(trp_0x0F),
/* 10 */	mktrpg(flt_bcpr),
/* 11 */	mktrpg(trp_0x11),
/* 12 */	mktrpg(trp_0x12),
/* 13 */	mktrpg(trp_0x13),
/* 14 */	mktrpg(trp_0x14),
/* 15 */	mktrpg(trp_0x15),
/* 16 */	mktrpg(trp_0x16),
/* 17 */	mktrpg(trp_0x17),
/* 18 */	mktrpg(trp_0x18),
/* 19 */	mktrpg(trp_0x19),
/* 1A */	mktrpg(trp_0x1A),
/* 1B */	mktrpg(trp_0x1B),
/* 1C */	mktrpg(trp_0x1C),
/* 1D */	mktrpg(trp_0x1D),
/* 1E */	mktrpg(trp_0x1E),
/* 1F */	mktrpg(trp_0x1F),
/* 20 */	mktrpg(trp_0x20),
/* 21 */	mktrpg(trp_0x21),
/* 22 */	mktrpg(trp_0x22),
/* 23 */	mktrpg(trp_0x23),
/* 24 */	mktrpg(trp_0x24),
/* 25 */	mktrpg(trp_0x25),
/* 26 */	mktrpg(trp_0x26),
/* 27 */	mktrpg(trp_0x27),
/* 28 */	mktrpg(trp_0x28),
/* 29 */	mktrpg(trp_0x29),
/* 2A */	mktrpg(trp_0x2A),
/* 2B */	mktrpg(trp_0x2B),
/* 2C */	mktrpg(trp_0x2C),
/* 2D */	mktrpg(trp_0x2D),
/* 2E */	mktrpg(trp_0x2E),
/* 2F */	mktrpg(trp_0x2F),
/* 30 */	mktrpg(trp_0x30),
/* 31 */	mktrpg(trp_0x31),
/* 32 */	mktrpg(trp_0x32),
/* 33 */	mktrpg(trp_0x33),
/* 34 */	mktrpg(trp_0x34),
/* 35 */	mktrpg(trp_0x35),
/* 36 */	mktrpg(trp_0x36),
/* 37 */	mktrpg(trp_0x37),
/* 38 */	mktrpg(trp_0x38),
/* 39 */	mktrpg(trp_0x39),
/* 3A */	mktrpg(trp_0x3A),
/* 3B */	mktrpg(trp_0x3B),
/* 3C */	mktrpg(trp_0x3C),
/* 3D */	mktrpg(trp_0x3D),
/* 3E */	mktrpg(trp_0x3E),
/* 3F */	mktrpg(trp_0x3F),
/* 00 */	mkintg(int_0x00),
/* 01 */	mkintg(int_0x01),
/* 02 */	mkintg(int_0x02),
/* 03 */	mkintg(int_0x03),
/* 04 */	mkintg(int_0x04),
/* 05 */	mkintg(int_0x05),
/* 06 */	mkintg(int_0x06),
/* 07 */	mkintg(int_0x07),
/* 08 */	mkintg(int_0x08),
/* 09 */	mkintg(int_0x09),
/* 0A */	mkintg(int_0x0A),
/* 0B */	mkintg(int_0x0B),
/* 0C */	mkintg(int_0x0C),
/* 0D */	mkintg(int_0x0D),
/* 0E */	mkintg(int_0x0E),
/* 0F */	mkintg(int_0x0F),
/* 10 */	mkintg(int_0x10),
/* 11 */	mkintg(int_0x11),
/* 12 */	mkintg(int_0x12),
/* 13 */	mkintg(int_0x13),
/* 14 */	mkintg(int_0x14),
/* 15 */	mkintg(int_0x15),
/* 16 */	mkintg(int_0x16),
/* 17 */	mkintg(int_0x17),
/* 18 */	mkintg(int_0x18),
/* 19 */	mkintg(int_0x19),
/* 1A */	mkintg(int_0x1A),
/* 1B */	mkintg(int_0x1B),
/* 1C */	mkintg(int_0x1C),
/* 1D */	mkintg(int_0x1D),
/* 1E */	mkintg(int_0x1E),
/* 1F */	mkintg(int_0x1F),
/* 20 */	mkintg(int_0x20),
/* 21 */	mkintg(int_0x21),
/* 22 */	mkintg(int_0x22),
/* 23 */	mkintg(int_0x23),
/* 24 */	mkintg(int_0x24),
/* 25 */	mkintg(int_0x25),
/* 26 */	mkintg(int_0x26),
/* 27 */	mkintg(int_0x27),
/* 28 */	mkintg(int_0x28),
/* 29 */	mkintg(int_0x29),
/* 2A */	mkintg(int_0x2A),
/* 2B */	mkintg(int_0x2B),
/* 2C */	mkintg(int_0x2C),
/* 2D */	mkintg(int_0x2D),
/* 2E */	mkintg(int_0x2E),
/* 2F */	mkintg(int_0x2F),
/* 30 */	mkintg(int_0x30),
/* 31 */	mkintg(int_0x31),
/* 32 */	mkintg(int_0x32),
/* 33 */	mkintg(int_0x33),
/* 34 */	mkintg(int_0x34),
/* 35 */	mkintg(int_0x35),
/* 36 */	mkintg(int_0x36),
/* 37 */	mkintg(int_0x37),
/* 38 */	mkintg(int_0x38),
/* 39 */	mkintg(int_0x39),
/* 3A */	mkintg(int_0x3A),
/* 3B */	mkintg(int_0x3B),
/* 3C */	mkintg(int_0x3C),
/* 3D */	mkintg(int_0x3D),
/* 3E */	mkintg(int_0x3E),
/* 3F */	mkintg(int_0x3F),
/* 40 */	mkintg(int_0x40),
/* 41 */	mkintg(int_0x41),
/* 42 */	mkintg(int_0x42),
/* 43 */	mkintg(int_0x43),
/* 44 */	mkintg(int_0x44),
/* 45 */	mkintg(int_0x45),
/* 46 */	mkintg(int_0x46),
/* 47 */	mkintg(int_0x47),
/* 48 */	mktrpg(int_0x48),
/* 49 */	mktrpg(int_0x49),
/* 4A */	mktrpg(int_0x4A),	
/* 4B */	mktrpg(int_0x4B),
/* 4C */	mktrpg(int_0x4C),
/* 4D */	mktrpg(int_0x4D),
/* 4E */	mktrpg(int_0x4E),
/* 4F */	mktrpg(int_0x4F),
/* 50 */	mktrpg(int_0x50),
/* 51 */	mktrpg(int_0x51),
/* 52 */	mktrpg(int_0x52),
/* 53 */	mktrpg(int_0x53),
/* 54 */	mktrpg(int_0x54),
/* 55 */	mktrpg(int_0x55),
/* 56 */	mktrpg(int_0x56),
/* 57 */	mktrpg(int_0x57),
/* 58 */	mktrpg(int_0x58),
/* 59 */	mktrpg(int_0x59),
/* 5A */	mktrpg(int_0x5A),
/* 5B */	mktrpg(int_0x5B),
/* 5C */	mktrpg(int_0x5C),
/* 5D */	mktrpg(int_0x5D),
/* 5E */	mktrpg(int_0x5E),
/* 5F */	mktrpg(int_0x5F),
/* 60 */	mktrpg(int_0x60),
/* 61 */	mktrpg(int_0x61),
/* 62 */	mktrpg(int_0x62),
/* 63 */	mktrpg(int_0x63),
/* 64 */	mktrpg(int_0x64),
/* 65 */	mktrpg(int_0x65),
/* 66 */	mktrpg(int_0x66),
/* 67 */	mktrpg(int_0x67),
/* 68 */	mktrpg(int_0x68),
/* 69 */	mktrpg(int_0x69),
/* 6A */	mktrpg(int_0x6A),
/* 6B */	mktrpg(int_0x6B),
/* 6C */	mktrpg(int_0x6C),
/* 6D */	mktrpg(int_0x6D),
/* 6E */	mktrpg(int_0x6E),
/* 6F */	mktrpg(int_0x6F),	
/* 70 */	mktrpg(int_0x70),	
/* 71 */	mktrpg(int_0x71),	
/* 72 */	mktrpg(int_0x72),	
/* 73 */	mktrpg(int_0x73),	
/* 74 */	mktrpg(int_0x74),	
/* 75 */	mktrpg(int_0x75),	
/* 76 */	mktrpg(int_0x76),	
/* 77 */	mktrpg(int_0x77),	
/* 78 */	mktrpg(int_0x78),	
/* 79 */	mktrpg(int_0x79),	
/* 7A */	mktrpg(int_0x7A),	
/* 7B */	mktrpg(int_0x7B),	
/* 7C */	mktrpg(int_0x7C),	
/* 7D */	mktrpg(int_0x7D),	
/* 7E */	mktrpg(int_0x7E),	
/* 7F */	mktrpg(int_0x7F),	
/* 80 */	mktrpg(int_0x80),	
/* 81 */	mktrpg(int_0x81),	
/* 82 */	mktrpg(int_0x82),	
/* 83 */	mktrpg(int_0x83),	
/* 84 */	mktrpg(int_0x84),	
/* 85 */	mktrpg(int_0x85),
/* 86 */	mktrpg(int_0x86),
/* 87 */	mktrpg(int_0x87),
/* 88 */	mktrpg(int_0x88),
/* 89 */	mktrpg(int_0x89),
/* 8A */	mktrpg(int_0x8A),
/* 8B */	mktrpg(int_0x8B),
/* 8C */	mktrpg(int_0x8C),
/* 8D */	mktrpg(int_0x8D),
/* 8E */	mktrpg(int_0x8E),
/* 8F */	mktrpg(int_0x8F),
/* 90 */	mktrpg(int_0x90),
/* 91 */	mktrpg(int_0x91),
/* 92 */	mktrpg(int_0x92),
/* 93 */	mktrpg(int_0x93),
/* 94 */	mktrpg(int_0x94),
/* 95 */	mktrpg(int_0x95),
/* 96 */	mktrpg(int_0x96),
/* 97 */	mktrpg(int_0x97),
/* 98 */	mktrpg(int_0x98),
/* 99 */	mktrpg(int_0x99),
/* 9A */	mktrpg(int_0x9A),
/* 9B */	mktrpg(int_0x9B),
/* 9C */	mktrpg(int_0x9C),
/* 9D */	mktrpg(int_0x9D),
/* 9E */	mktrpg(int_0x9E),
/* 9F */	mktrpg(int_0x9F),
/* A0 */	mktrpg(int_0xA0),
/* A1 */	mktrpg(int_0xA1),
/* A2 */	mktrpg(int_0xA2),
/* A3 */	mktrpg(int_0xA3),
/* A4 */	mktrpg(int_0xA4),
/* A5 */	mktrpg(int_0xA5),
/* A6 */	mktrpg(int_0xA6),
/* A7 */	mktrpg(int_0xA7),
/* A8 */	mktrpg(int_0xA8),
/* A9 */	mktrpg(int_0xA9),
/* AA */	mktrpg(int_0xAA),
/* AB */	mktrpg(int_0xAB),
/* AC */	mktrpg(int_0xAC),
/* AD */	mktrpg(int_0xAD),
/* AE */	mktrpg(int_0xAE),
/* AF */	mktrpg(int_0xAF),
/* B0 */	mktrpg(int_0xB0),
/* B1 */	mktrpg(int_0xB1),
/* B2 */	mktrpg(int_0xB2),
/* B3 */	mktrpg(int_0xB3),
/* B4 */	mktrpg(int_0xB4),
/* B5 */	mktrpg(int_0xB5),
/* B6 */	mktrpg(int_0xB6),
/* B7 */	mktrpg(int_0xB7),
/* B8 */	mktrpg(int_0xB8),
/* B9 */	mktrpg(int_0xB9),
/* BA */	mktrpg(int_0xBA),
/* BB */	mktrpg(int_0xBB),
/* BC */	mktrpg(int_0xBC),
/* BD */	mktrpg(int_0xBD),
/* BE */	mktrpg(int_0xBE),
/* BF */	mktrpg(int_0xBF),
};

struct tss386 ltss = {0};		/* uprt.s dumps stuff here. It's never read */

extern char df_stack[];

struct tss386 ktss = {
			0L,
			(unsigned long) &df_stack[KERNEL_STACK_SIZE],
			(unsigned long)KDSSEL,
			(unsigned long) &df_stack[KERNEL_STACK_SIZE],
			(unsigned long)KDSSEL,
			(unsigned long) &df_stack[KERNEL_STACK_SIZE],
			(unsigned long)KDSSEL,
			(unsigned long)(&kpde[0])-VM_MIN_KERNEL_ADDRESS,	/* cr3 */
			(unsigned long) vstart,			/* eip */
			0L,					/* flags */
			0L,					/* eax */
			0L,					/* ecx */
			0L,					/* edx */
			0L,					/* ebx */
			(unsigned long) &df_stack[KERNEL_STACK_SIZE],
			0L,					/* ebp */
			0L,					/* esi */
			0L,					/* edi */
			(unsigned long)KDSSEL,			/* es */
			(unsigned long)KCSSEL,			/* cs */
			(unsigned long)KDSSEL,			/* ss */
			(unsigned long)KDSSEL,			/* ds */
			0L,					/* fs */
			0L,					/* gs */
			0L,					/* ldt */
			0L,					/* t */
			0xFFFF0000,				/* base */
};

struct tss386 dftss = {
			0L,
			(unsigned long)&df_stack[0xFFC],
			(unsigned long)KDSSEL,
			0L,
			0L,
			0L,
			0L,
			(unsigned long)(&kpde[0]),	/* cr3 */
			(unsigned long) abt_dblf,
			0L,				/* flags */
			0L,
			0L,
			0L,
			0L,
			(unsigned long)&df_stack[0xFFC],
			0L,
			0L,
			0L,
			(unsigned long)KDSSEL,
			(unsigned long)KCSSEL,
			(unsigned long)KDSSEL,
			(unsigned long)KDSSEL,
			(unsigned long)KDSSEL,
			(unsigned long)KDSSEL,
			(unsigned long)LDTSEL,
			0L,					/* t */
			0xFFFF0000,				/* base */
};

struct fakegate scall_dscr = {
		(unsigned long)system_call, KCSSEL, 1, GATE_UACC|GATE_386CALL
};


struct fakegate sigret_dscr = {
		(unsigned long)sig_clean, KCSSEL, 1, GATE_UACC|GATE_386CALL
};

