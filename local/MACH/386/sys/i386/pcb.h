/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/* 
 * HISTORY
 * $Log:	pcb.h,v $
 * Revision 1.7.1.7  90/12/07  22:53:24  rvb
 * 	Add t_bitmap to allow v8086 tasks do vga and other groovy stuff
 * 	directly.
 * 	[90/11/27            rvb]
 * 
 * Revision 1.7.1.6  90/07/27  11:24:37  rvb
 * 	Fix Intel Copyright as per B. Davies authorization.
 * 	[90/07/27            rvb]
 * 
 * Revision 1.7.1.5  90/06/07  08:04:55  rvb
 * 	Tweak comment for status word in fpstate.	[kupfer]
 * 
 * Revision 1.7.1.4  90/04/15  11:45:50  rvb
 * 	Fix t_bitmapbase to be a short as advertised.
 * 	[90/04/11            rvb]
 * 
 * Revision 1.7.1.3  90/02/28  15:48:19  rvb
 * 	Revision 1.13  89/11/16  16:24:28  kupfer
 * 		Add workaround for Errata 17 for B1 step 80386s (coprocessor
 * 		instruction that spans page boundary).
 * 
 * 	Revision 1.12  89/11/02  14:15:38  kupfer
 * 		Try to rely less on magic numbers.  Resurrect pcb_synch.
 * 
 * Revision 1.14  90/02/26  17:54:24  kupfer
 * Synch with CMU.  h/w workarounds ifdef'd by h/w type.
 * 
 * Revision 1.7.1.2  90/01/08  13:29:06  rvb
 *	Add Intel copyright.
 *	[90/01/08            rvb]
 *   
 * Revision 1.7.1.1  89/11/21  12:45:30  rvb
 *	Flush some dead fields in pcb_.
 *	[89/11/21            rvb]
 *
 * Revision 1.11  89/09/26  11:56:10  lance
 * X109 checkin
 * 
 * Revision 1.7  89/09/25  12:25:17  rvb
 * 	File was provided by Intel 9/18/89.
 * 	[89/09/23            rvb]
 * 
 * Revision 1.6  89/09/20  17:26:43  rvb
 * 	Revision 1.9  89/09/14  13:07:24  kupfer
 * 	Add some comments.  Also add prototypes for a couple functions in
 * 	pcb.c.
 * 
 * 	Revision 1.8  89/08/07  17:28:54  kupfer
 * 	Better handling of single-step traps.  Some reformatting.
 * 
 * 	Revision 1.7  89/07/07  17:55:26  kupfer
 * 	X79 merge, 2nd attempt.
 * 
 * Revision 1.5  89/07/17  10:38:15  rvb
 * 	Olivetti Changes to X79 upto 5/9/89:
 * 	[89/07/11            rvb]
 * 
 * Revision 1.4  89/03/09  20:03:18  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/26  12:32:53  gm0w
 * 	Changes for cleanup.
 * 
 */
 
/*
  Copyright 1988, 1989 by Intel Corporation, Santa Clara, California.

		All Rights Reserved

Permission to use, copy, modify, and distribute this software and
its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appears in all
copies and that both the copyright notice and this permission notice
appear in supporting documentation, and that the name of Intel
not be used in advertising or publicity pertaining to distribution
of the software without specific, written prior permission.

INTEL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
IN NO EVENT SHALL INTEL BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#ifndef	_PCB_
#define _PCB_

#include <sys/types.h>
#include <i386/fpreg.h>

/* Flags Register */

typedef struct tss386_flags {
	u_int	fl_cf	:  1,		/* carry/borrow */
			:  1,		/* reserved */
		fl_pf	:  1,		/* parity */
			:  1,		/* reserved */
		fl_af	:  1,		/* carry/borrow */
			:  1,		/* reserved */
		fl_zf	:  1,		/* zero */
		fl_sf	:  1,		/* sign */
		fl_tf	:  1,		/* trace */
		fl_if	:  1,		/* interrupt enable */
		fl_df	:  1,		/* direction */
		fl_of	:  1,		/* overflow */
		fl_iopl :  2,		/* I/O privilege level */
		fl_nt	:  1,		/* nested task */
			:  1,		/* reserved */
		fl_rf	:  1,		/* reset */
		fl_vm	:  1,		/* virtual 86 mode */
		fl_res	: 14;		/* reserved */
} tss386_flags_t;

#define PS_C		0x0001		/* carry bit			*/
#define PS_P		0x0004		/* parity bit			*/
#define PS_AC		0x0010		/* auxiliary carry bit		*/
#define PS_Z		0x0040		/* zero bit			*/
#define PS_N		0x0080		/* negative bit			*/
#define PS_T		0x0100		/* trace enable bit		*/
#define PS_IE		0x0200		/* interrupt enable bit		*/
#define PS_D		0x0400		/* direction bit		*/
#define PS_V		0x0800		/* overflow bit			*/
#define PS_IOPL		0x3000		/* I/O privilege level		*/
#define PS_NT		0x4000		/* nested task flag		*/
#define PS_RF		0x10000		/* Reset flag			*/
#define PS_VM		0x20000		/* Virtual 86 mode flag		*/

/*
 * Maximum I/O address that will be in TSS bitmap
 */
#define MAXTSSIOADDR	0x3ff

struct tss386 {
	u_long	t_link;
	u_long	t_esp0;
	u_long	t_ss0;
	u_long	t_esp1;
	u_long	t_ss1;
	u_long	t_esp2;
	u_long	t_ss2;
	u_long	t_cr3;
	u_long	t_eip;
	u_long	t_eflags;
	u_long	t_eax;
	u_long	t_ecx;
	u_long	t_edx;
	u_long	t_ebx;
	u_long	t_esp;
	u_long	t_ebp;
	u_long	t_esi;
	u_long	t_edi;
	u_long	t_es;
	u_long	t_cs;
	u_long	t_ss;
	u_long	t_ds;
	u_long	t_fs;
	u_long	t_gs;
	u_long	t_ldt;
	u_short	t_t;
	u_short	t_bitmapbase;
	u_char	t_bitmap[(MAXTSSIOADDR+1)>>3];
};

/*
 * 386 TSS definition
 */

struct pcb {

	struct tss386 pcb_tss;

	/* 
	 * Software extensions.  Note that the fpvalid and fps fields 
	 * are assumed to be adjacent (see ldt_init()).
	 * XXX - It would[ be better if fpstate.state were a struct 
	 *       instead of a byte array, but I don't know anything 
	 *       about the '287 layout. -mdk
	 */
	struct pt_entry *pcb_cr3;	/* page directory pointer - CR3 */
	int	pcb_context[7];		/* save context for kernel */
	int	pcb_fpvalid;		/* saved fp state is valid */
	struct	fpstate {
		u_char	state[FP_STATE_BYTES];	
					/* 287/387 saved state; see fpreg.h */
		int	status;		/* status word from last exception */
	} pcb_fps;
	int	pcb_flags;
	/* 
	 * Start of COPROC_SPANPAGE_BUG fields.  These aren't ifdef'd, 
	 * because user programs have no way of knowing whether the 
	 * kernel was config'd for that fix.
	 */
	int	pcb_last_uip;		/* prev. user IP at interrupt */
	int	pcb_ip_same;		/* number times IP was the same */
	/* End of COPROC_SPANPAGE_BUG fields. */
};


#define		PS_USER		3
#define		PS_KERNEL	0


/* 
 * Flags.
 * 
 * PSF_SINGLESTEP can be set if there is a debug trap in system mode.
 * The flag tells syscall() to set the single-step flag in the user's
 * flags register, so that the user will be put back into single-step
 * mode after returning from the syscall.
 */

#define PSF_SINGLESTEP	0x1


/* 
 * Public functions exported by pcb.c.
 */

extern void pcb_synch();

#if	defined(__STDC__) || defined(__GNUC__)
extern void pcb_init(/*struct thread *thread, vm_offset_t ksp*/);
extern void ldt_init(/*struct seg_desc *ldt, char *fpstart, int fpsize*/);
#endif	/* __STDC__ || __GNUC__ */

#endif	/* _PCB_ */
