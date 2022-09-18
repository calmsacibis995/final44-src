h49463
s 00024/00024/00093
d D 8.2 94/07/28 13:56:57 hibler 7 6
c put space around minus sign in pad expressions.  gcc2.5.8 complains
c about 0xNNNE-0xNNNN if the 'E' is immediately followed by a '-', thinks it
c is a constant in scientific notation and complains about malformed number.
e
s 00002/00002/00115
d D 8.1 93/06/10 21:33:04 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00004/00117
d D 7.5 92/10/11 09:23:56 bostic 5 4
c make kernel includes standard
e
s 00007/00005/00114
d D 7.4 92/06/05 15:31:07 hibler 4 3
c merge latest Utah hp300 code including 68040 support
e
s 00015/00004/00104
d D 7.3 91/05/07 09:50:54 hibler 3 2
c additional definitions for catseye
e
s 00001/00001/00107
d D 7.2 90/11/04 19:29:21 mckusick 2 1
c update identifier from Utah
e
s 00108/00000/00000
d D 7.1 90/05/08 22:06:39 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
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
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 2
 * from: Utah $Hdr: grf_tcreg.h 1.9 89/08/24$
E 2
I 2
D 3
 * from: Utah $Hdr: grf_tcreg.h 1.1 90/07/09$
E 3
I 3
D 4
 * from: Utah $Hdr: grf_tcreg.h 1.10 91/03/25$
E 4
I 4
 * from: Utah $Hdr: grf_tcreg.h 1.11 92/01/21$
E 4
E 3
E 2
 *
 *	%W% (Berkeley) %G%
 */

I 4
D 5
#ifdef KERNEL
#include "hp/dev/iotypes.h"	/* XXX */
#else
E 5
#include <hp/dev/iotypes.h>	/* XXX */
D 5
#endif
E 5

E 4
#define tccm_waitbusy(regaddr) \
	while (((struct tcboxfb *)(regaddr))->cmap_busy & 0x04) DELAY(100)

#define tc_waitbusy(regaddr,planes) \
	while (((struct tcboxfb *)(regaddr))->busy & planes) DELAY(100)

D 4
#define	vu_char		volatile u_char
#define	vu_short	volatile u_short

E 4
struct tcboxfb {
  u_char 	:8;
  vu_char 	reset;			/* reset register		0x01 */
  vu_char	fb_address;		/* frame buffer address 	0x02 */
  vu_char	interrupt;		/* interrupt register		0x03 */
  u_char	:8;
  vu_char	fbwmsb;			/* frame buffer width MSB	0x05 */
  u_char	:8;
  vu_char	fbwlsb;			/* frame buffer width MSB	0x07 */
  u_char	:8;
  vu_char	fbhmsb;			/* frame buffer height MSB	0x09 */
  u_char	:8;
  vu_char	fbhlsb;			/* frame buffer height MSB	0x0b */
  u_char	:8;
  vu_char	dwmsb;			/* display width MSB		0x0d */
  u_char	:8;
  vu_char	dwlsb;			/* display width MSB		0x0f */
  u_char	:8;
  vu_char	dhmsb;			/* display height MSB		0x11 */
  u_char	:8;
  vu_char	dhlsb;			/* display height MSB		0x13 */
  u_char	:8;
  vu_char	fbid;			/* Scondary frame buffer id	0x15 */
  u_char	:8;
  vu_char	bits;			/* square(0)/double-high(1) 	0x17 */
D 7
  u_char	f1[0x5b-0x17-1];
E 7
I 7
  u_char	f1[0x5b - 0x17 - 1];
E 7
  vu_char	num_planes;		/* number of color planes       0x5b */
  u_char	:8;
  vu_char	fbomsb;			/* frame buffer offset MSB	0x5d */
  u_char	:8;
  vu_char	fbolsb;			/* frame buffer offset LSB	0x5f */
D 7
  u_char	f2[0x4040-0x5f-1];
E 7
I 7
  u_char	f2[0x4040 - 0x5f - 1];
E 7
  vu_char 	vblank;			/* vertical blanking	      0x4040 */
  u_char	:8,:8,:8;
  vu_char	busy;			/* window move active	      0x4044 */
  u_char	:8,:8,:8;
  vu_char 	vtrace_request;		/* vert retrace intr request  0x4048 */
  u_char	:8,:8,:8;
  vu_char	move_request;		/* window move intr request   0x404C */
D 7
  u_char	f3[0x4080-0x404c-1];
E 7
I 7
  u_char	f3[0x4080 - 0x404c - 1];
E 7
  vu_char	nblank;			/* display enable planes      0x4080 */
D 7
  u_char 	f4[0x4088-0x4080-1];
E 7
I 7
  u_char 	f4[0x4088 - 0x4080 - 1];
E 7
  vu_char	wen;			/* write enable plane 	      0x4088 */
D 7
  u_char 	f5[0x408c-0x4088-1];
E 7
I 7
  u_char 	f5[0x408c - 0x4088 - 1];
E 7
  vu_char	ren;			/* read enable plane          0x408c */
D 7
  u_char 	f6[0x4090-0x408c-1];
E 7
I 7
  u_char 	f6[0x4090 - 0x408c - 1];
E 7
  vu_char	fben;			/* frame buffer write enable  0x4090 */
D 7
  u_char 	f7[0x409c-0x4090-1];
E 7
I 7
  u_char 	f7[0x409c - 0x4090 - 1];
E 7
  vu_char	wmove;			/* start window move 	      0x409c */
D 7
  u_char 	f8[0x40a0-0x409c-1];
E 7
I 7
  u_char 	f8[0x40a0 - 0x409c - 1];
E 7
  vu_char	blink;			/* enable blink planes 	      0x40a0 */
D 7
  u_char 	f9[0x40a8-0x40a0-1];
E 7
I 7
  u_char 	f9[0x40a8 - 0x40a0 - 1];
E 7
  vu_char	altframe;		/* enable alternate frame     0x40a8 */
D 7
  u_char 	f10[0x40ac-0x40a8-1];
E 7
I 7
  u_char 	f10[0x40ac - 0x40a8 - 1];
E 7
  vu_char	curon;			/* cursor control register    0x40ac */
D 7
  u_char	f11[0x40ea-0x40ac-1];
E 7
I 7
  u_char	f11[0x40ea - 0x40ac - 1];
E 7
  vu_char	prr;			/* pixel replacement rule     0x40ea */
D 7
  u_char	f12[0x40ef-0x40ea-1];
E 7
I 7
  u_char	f12[0x40ef - 0x40ea - 1];
E 7
  vu_char	wmrr;			/* move replacement rule      0x40ef */
D 7
  u_char 	f13[0x40f2-0x40ef-1];
E 7
I 7
  u_char 	f13[0x40f2 - 0x40ef - 1];
E 7
  vu_short 	source_x;		/* source x pixel # 	      0x40f2 */
D 7
  u_char 	f14[0x40f6-0x40f2-2];
E 7
I 7
  u_char 	f14[0x40f6 - 0x40f2 - 2];
E 7
  vu_short 	source_y;		/* source y pixel # 	      0x40f6 */
D 7
  u_char 	f15[0x40fa-0x40f6-2];
E 7
I 7
  u_char 	f15[0x40fa - 0x40f6 - 2];
E 7
  vu_short	dest_x;			/* dest x pixel # 	      0x40fa */
D 7
  u_char 	f16[0x40fe-0x40fa-2];
E 7
I 7
  u_char 	f16[0x40fe - 0x40fa - 2];
E 7
  vu_short	dest_y;			/* dest y pixel # 	      0x40fe */
D 7
  u_char 	f17[0x4102-0x40fe-2];
E 7
I 7
  u_char 	f17[0x4102 - 0x40fe - 2];
E 7
  vu_short	wwidth;			/* block mover pixel width    0x4102 */
D 7
  u_char	f18[0x4106-0x4102-2];
E 7
I 7
  u_char	f18[0x4106 - 0x4102 - 2];
E 7
  vu_short 	wheight;		/* block mover pixel height   0x4106 */
D 3
  u_char 	f19[0x6002-0x4106-2];
E 3
I 3
  /* Catseye */
D 7
  u_char	f19[0x4206-0x4106-2];
E 7
I 7
  u_char	f19[0x4206 - 0x4106 - 2];
E 7
  vu_short	rug_cmdstat;		/* RUG Command/Staus	      0x4206 */
D 7
  u_char	f20[0x4510-0x4206-2];
E 7
I 7
  u_char	f20[0x4510 - 0x4206 - 2];
E 7
  vu_short	vb_select;		/* Vector/BitBlt Select	      0x4510 */
  vu_short	tcntrl;			/* Three Operand Control      0x4512 */
  vu_short	acntrl;			/* BitBlt Mode		      0x4514 */
  vu_short	pncntrl;		/* Plane Control	      0x4516 */
D 7
  u_char	f21[0x4800-0x4516-2];
E 7
I 7
  u_char	f21[0x4800 - 0x4516 - 2];
E 7
  vu_short	catseye_status;		/* Catseye Status	      0x4800 */
  /* End of Catseye */
D 7
  u_char 	f22[0x6002-0x4800-2];
E 7
I 7
  u_char 	f22[0x6002 - 0x4800 - 2];
E 7
E 3
  vu_short	cmap_busy;		/* Color Ram busy	      0x6002 */
D 3
  u_char 	f20[0x60b2-0x6002-2];
E 3
I 3
D 7
  u_char 	f23[0x60b2-0x6002-2];
E 7
I 7
  u_char 	f23[0x60b2 - 0x6002 - 2];
E 7
E 3
  vu_short	rdata;			/* color map red data 	      0x60b2 */
  vu_short 	gdata;			/* color map green data       0x60b4 */
  vu_short	bdata;			/* color map blue data 	      0x60b6 */
  vu_short	cindex;			/* color map index 	      0x60b8 */
  vu_short	plane_mask;		/* plane mask select	      0x60ba */
D 3
  u_char 	f21[0x60f0-0x60ba-2];
E 3
I 3
D 7
  u_char 	f24[0x60f0-0x60ba-2];
E 7
I 7
  u_char 	f24[0x60f0 - 0x60ba - 2];
E 7
E 3
  vu_short 	strobe;			/* color map trigger 	      0x60f0 */
};
D 4

E 4
E 1
