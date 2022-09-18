/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	genassym.c,v $
 * Revision 2.2  89/07/12  00:19:08  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
#ifndef lint
static  char sccsid[] = "@(#)genassym.c 1.2 88/02/08";
#endif

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#include <mon/sunromvec.h>

main()
{
	printf("#define\tINITGETKEY 0x%x\n", &romp->v_initgetkey);
	exit(0);
}

