/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 *
 */

/*
 ************************************************************************
 *	File:	regs.c
 *	Author:	Robert V. Baron
 *
 *	Print the register values.
 *
 * HISTORY
 * $Log:	regs.c,v $
 * Revision 2.3  89/02/26  14:35:08  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  88/08/08  13:45:49  rvb
 * Created.
 * 
 *
 ************************************************************************
 */

main(r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,r10,r11,ap)
{
register int rr11, rr10, rr9, rr8, rr7, rr6;

	printf("r0 .. r4:   %x %x %x %x %x\n", r0, r1, r2, r3, r4);
	printf("r5 .. r9:   %x %x %x %x %x\n", r5, r6, r7, r8, r9);
	printf("r10 .. r11: %x %x\n", r10, r11);
	open(".", 0);
	exit();
}
