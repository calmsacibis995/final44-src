/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	fp.h,v $
 * Revision 2.2  89/02/25  20:21:43  gm0w
 * 	Changes for cleanup.
 * 
 * 11-Oct-85  Robert V Baron (rvb) at Carnegie-Mellon University
 *	header for the "n" stack trace.  Used to describe a stack frame.
 *
 */

struct frame {
	int *f_handler;
	struct f_fm {
		unsigned int : 5;
		unsigned int fm_psw : 11;
		unsigned int fm_mask : 12;
		unsigned int : 1;
		unsigned int fm_s : 1;
		unsigned int fm_spa : 2;
	} f_msk ;
	int *f_ap ;
	struct frame *f_fp ;
	unsigned char *f_pc ;
	int f_r0[12] ;
} ;

#define f_psw f_msk.f_fmask
#define f_mask f_msk.fm_mask
#define f_s f_msk.fm_s
#define f_spa f_msk.fm_spa
