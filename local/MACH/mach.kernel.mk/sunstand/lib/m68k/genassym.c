/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	genassym.c,v $
 * Revision 2.2  89/07/12  00:22:01  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
#ifndef lint
static  char sccsid[] = "@(#)genassym.c 1.3 88/02/08";
#endif

/*
 * Copyright (c) 1987 by Sun Microsystems, Inc.
 */

#include <machine/reg.h>
#include <mon/sunromvec.h>
#include <mon/keyboard.h>

main()
{
	register struct regs *rp = (struct regs *)0;

	printf("#define\tCACR_CLEAR 0x%x\n", 0x8);
	printf("#define\tCACR_ENABLE 0x%x\n", 0x1);
	printf("#define\tV_TRANSLATION 0x%x\n", &romp->v_translation);
	printf("#define\tR_SP 0x%x\n", &rp->r_sp);
	printf("#define\tR_SR 0x%x\n", ((int)&rp->r_sr) + sizeof (short));
	exit(0);
}

