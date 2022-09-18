h08782
s 00001/00011/00138
d D 5.2 90/06/01 16:04:48 bostic 2 1
c new copyright notice
e
s 00149/00000/00000
d D 5.1 89/05/23 10:04:45 bostic 1 0
c date and time created 89/05/23 10:04:45 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1983 The Regents of the University of California.
 * All rights reserved.
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Machine operators.
 */

#include "defs.h"
#include "ops.h"
#include "machine.h"

#ifndef public

/*
 * 68000 opcodes.
 */

#define IMDF "#0x%x"		/* immediate data format */

typedef struct {			
    unsigned short mask, match;
    int (*opfun)();
    char *farg;
} Optab;

#endif

public String bname[16] = {
    "ra", "sr", "hi", "ls", "cc", "cs", "ne",
    "eq", "vc", "vs", "pl", "mi", "ge", "lt", "gt", "le"
};

public String cname[16] = {
    "ra", "f", "hi", "ls", "cc", "cs", "ne",
    "eq", "vc", "vs", "pl", "mi", "ge", "lt", "gt", "le"
};

public String dbname[16] = {
    "t", "ra", "hi", "ls", "cc", "cs", "ne",
    "eq", "vc", "vs", "pl", "mi", "ge", "lt", "gt", "le"
};

public String shro[4] = { "as", "ls", "rox", "ro" };

public String bit[4] = { "btst", "bchg", "bclr", "bset" };

/*
 * order is important here
 */

public Optab optab[] = {
    0xF000, 0x1000, omove, "b",			/* move instructions */
    0xF000, 0x2000, omove, "l",
    0xF000, 0x3000, omove, "w",
    0xF000, 0x6000, obranch, 0,			/* branches   */
    0xFF00, 0x0000, oimmed, "or",		/* op class 0  */
    0xFF00, 0x0200, oimmed, "and",
    0xFF00, 0x0400, oimmed, "sub",
    0xFF00, 0x0600, oimmed, "add",
    0xFF00, 0x0A00, oimmed, "eor",
    0xFF00, 0x0C00, oimmed, "cmp",
    0xFF00, 0x0E00, omovs,  "movs",
    0xF100, 0x0100, biti, 0,
    0xF800, 0x0800, biti, 0,
    0xFFC0, 0x40C0, oneop, "move_from_sr\t",	/* op class 4 */
    0xFF00, 0x4000, soneop, "negx",
    0xFFC0, 0x42C0, oneop,  "movw	cc,",
    0xFF00, 0x4200, soneop, "clr",
    0xFFC0, 0x44C0, oneop, "move_to_ccr	",
    0xFF00, 0x4400, soneop, "neg",
    0xFFC0, 0x46C0, oneop, "move_to_sr	",
    0xFF00, 0x4600, soneop, "not",
    0xFFC0, 0x4800, oneop, "nbcd	",
    0xFFF8, 0x4840, oreg, "\tswap\td%D",
    0xFFC0, 0x4840, oneop, "pea	",
    0xFFF8, 0x4880, oreg, "\textw\td%D",
    0xFFF8, 0x48C0, oreg, "\textl\td%D",
    0xFB80, 0x4880, omovem, 0,
    0xFFC0, 0x4AC0, oneop, "tas	",
    0xFF00, 0x4A00, soneop, "tst",
    0xFFF0, 0x4E40, otrap, 0,
    0xFFF8, 0x4E50, olink, 0,
    0xFFFE, 0x4E7A, omovc, "\tmovc\t",
    0xFFF8, 0x4880, oreg, "\textw\td%D",
    0xFFF8, 0x48C0, oreg, "\textl\td%D",
    0xFFF8, 0x4E58, oreg, "\tunlk\ta%D",
    0xFFF8, 0x4E60, oreg, "\tmove\ta%D,usp",
    0xFFF8, 0x4E68, oreg, "\tmove\tusp,a%D",
    0xFFFF, 0x4E70, oprint, "reset",
    0xFFFF, 0x4E71, oprint, "nop",
    0xFFFF, 0x4E72, ostop, "\tstop\t0x%x",
    0xFFFF, 0x4E73, oprint, "rte",
    0xFFFF, 0x4E74, ortspop, "\trts\t0x%x",
    0xFFFF, 0x4E75, orts, "rts",
    0xFFFF, 0x4E76, oprint, "trapv",
    0xFFFF, 0x4E77, oprint, "rtr",
    0xFFC0, 0x4E80, jsrop, "jsr	",
    0xFFC0, 0x4EC0, jmpop, "jmp	",
    0xF1C0, 0x4180, ochk, "chk",
    0xF1C0, 0x41C0, ochk, "lea",
    0xF0F8, 0x50C8, odbcc, "\tdb%s\td%D,",
    0xF0C0, 0x50C0, oscc,  0,
    0xF100, 0x5000, oquick, "addq",
    0xF100, 0x5100, oquick, "subq",
    0xF000, 0x7000, omoveq, 0,
    0xF1C0, 0x80C0, ochk, "divu",
    0xF1C0, 0x81C0, ochk, "divs",
    0xF1F0, 0x8100, extend, "sbcd",
    0xF000, 0x8000, opmode, "or",
    0xF1C0, 0x91C0, opmode, "sub",
    0xF130, 0x9100, extend, "subx",
    0xF000, 0x9000, opmode, "sub",
    0xF1C0, 0xB1C0, opmode, "cmp",
    0xF138, 0xB108, extend, "cmpm",
    0xF100, 0xB000, opmode, "cmp",
    0xF100, 0xB100, opmode, "eor",
    0xF1C0, 0xC0C0, ochk, "mulu",
    0xF1C0, 0xC1C0, ochk, "muls",
    0xF1F8, 0xC188, extend, "exg",
    0xF1F8, 0xC148, extend, "exg",
    0xF1F8, 0xC140, extend, "exg",
    0xF1F0, 0xC100, extend, "abcd",
    0xF000, 0xC000, opmode, "and",
    0xF1C0, 0xD1C0, opmode, "add",
    0xF130, 0xD100, extend, "addx",
    0xF000, 0xD000, opmode, "add",
    0xF100, 0xE000, shroi, "r",
    0xF100, 0xE100, shroi, "l",
    0, 0, 0, 0
};

E 1
