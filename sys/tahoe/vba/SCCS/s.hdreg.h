h03168
s 00001/00011/00249
d D 7.4 90/06/28 22:27:18 bostic 4 3
c new copyright notice
e
s 00187/00199/00073
d D 7.3 89/03/07 14:59:47 bostic 3 2
c first working version
e
s 00142/00142/00130
d D 7.2 87/12/28 16:30:31 bostic 2 1
c reformat
e
s 00272/00000/00000
d D 7.1 87/10/13 13:36:02 bostic 1 0
c date and time created 87/10/13 13:36:02 by bostic
c original Harris source code
e
u
U
t
T
I 1
/*
D 3
 *  Include file for HCX Disk Controller (HDC).
E 3
I 3
 * Copyright (c) 1988 The Regents of the University of California.
 * All rights reserved.
E 3
 *
I 3
 * This code is derived from software contributed to Berkeley by
 * Harris Corp.
 *
D 4
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
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
 *
E 3
 *	%W% (Berkeley) %G%
 */

D 3
#define	TRUE		1
D 2
#define FALSE		0
#define HDC_READ	0
#define HDC_WRITE	1
#define HDC_MAXBUS	2		/* max# buses                       */
#define HDC_MAXCTLR	21		/* max# hdc controllers per bus     */
#define HDC_MAXDRIVE	4		/* max# drives per hdc controller   */
#define HDC_UNIT(x)	(minor(x) >> 3) /* the hdc unit number (0-31)       */
#define HDC_PARTITION(x) (minor(x)&0x07)/* the hdc partition number (0-7)   */
#define HDC_DEFPART	GB_MAXPART-1	/* partition# of def and diag cyls  */
#define HDC_SPB		2		/* sectors per block for hdc's      */
#define HDC_MID		HID_HDC		/* module id code for hdc's         */
#define HDC_REMOVABLE	80		/* lowest model# for removable disks*/
#define HDC_PHIO_SIZE	256		/* lword size of physical io buffer */
#define HDC_VDATA_SIZE	16		/* vendor data size (long words)    */
#define HDC_XSTAT_SIZE	128		/* size of extended status (lwords) */
#define HDC_MAXCHAIN	33		/* maximum number of data chains    */
#define HDC_MAXBC	64*1024		/* maximum byte count per data chain*/
#define HDC_MAXMCBS	32		/* max# mcb's the hdc can handle    */
#define HDC_MAXFLAWS	8000		/* max number of flaws per hdc disk */
#define HDC_REGISTER(x)	(hc->registers->x) /* io to an hdc register         */
#define HDC_DUMPSIZE	HDC_MAXBC/DEV_BSIZE*HDC_MAXCHAIN
E 2
I 2
#define	FALSE		0
E 3
I 3
#ifndef COMPAT_42
#define	COMPAT_42
#endif

E 3
#define	HDC_READ	0
#define	HDC_WRITE	1
I 3

E 3
#define	HDC_MAXBUS	2		/* max# buses */
#define	HDC_MAXCTLR	21		/* max# hdc controllers per bus */
#define	HDC_MAXDRIVE	4		/* max# drives per hdc controller */
D 3
#define	HDC_UNIT(x)	(minor(x) >> 3) /* the hdc unit number (0-31) */
#define	HDC_PARTITION(x) (minor(x)&0x07)/* the hdc partition number (0-7) */
#define	HDC_DEFPART	GB_MAXPART-1	/* partition# of def and diag cyls */
E 3
I 3
#define	HDC_MAXMCBS	32		/* max# mcb's the hdc can handle */
#define	HDC_MAXCHAIN	64		/* max# of data chains */
#define	HDC_MAXBC	64*1024		/* max# byte count per data chain */
#define	HDC_MAXFLAWS	8000		/* max# flaws per hdc disk */

E 3
#define	HDC_SPB		2		/* sectors per block for hdc's */
D 3
#define	HDC_MID		HID_HDC		/* module id code for hdc's */
#define	HDC_REMOVABLE	80		/* lowest model# for removable disks */
#define	HDC_PHIO_SIZE	256		/* lword size of physical io buffer */
E 3
#define	HDC_VDATA_SIZE	16		/* vendor data size (long words) */
D 3
#define	HDC_XSTAT_SIZE	128		/* size of extended status (lwords) */
#define	HDC_MAXCHAIN	33		/* maximum number of data chains */
#define	HDC_MAXBC	64*1024		/* maximum byte count per data chain */
#define	HDC_MAXMCBS	32		/* max# mcb's the hdc can handle */
#define	HDC_MAXFLAWS	8000		/* max number of flaws per hdc disk */
#define	HDC_REGISTER(x)	(hc->registers->x) /* io to an hdc register */
#define	HDC_DUMPSIZE	HDC_MAXBC/DEV_BSIZE*HDC_MAXCHAIN
E 3
I 3

#define	HDC_REG(x)	(hd->reg->x)	/* set an HDC register */
E 3
E 2
					/* number of blocks per dump record */
I 3
#define	HDC_DUMPSIZE	(HDC_MAXBC/DEV_BSIZE*HDC_MAXCHAIN)
E 3

/*
D 3
 * The following buf structure defines are used by the hdc handler.
 * These are required since the handler initiates strategy calls;
 * these calls require more function codes than just read/write,
 * and they like to directly specify the cyl/head/sector.
 * Note that b_upte and B_NOT1K are never used by the handler.
E 3
I 3
 * These are the 4 hdc i/o register addresses.  Writing to "master_mcb"
 * tells the hdc controller where the master mcb is and initiates hdc
 * operation. The hdc then reads the master mcb and all new mcb's in the
 * active mcb queue.  Writing to "module_id" causes the hdc to return the
 * hdc's module id word in the location specified by the address written
 * into the register.  "soft_reset" causes orderly shutdown of HDC; it's
 * unclear from the manual what "hard_reset" does, but it should never be
 * used as use while the HDC is active may cause format errors.
E 3
 */
I 3
struct registers {
	u_long	master_mcb,		/* set the master mcb address */
		module_id,		/* returns hdc's module id (hdc_mid) */
		soft_reset,		/* shut down the hdc */
		hard_reset;		/* send a system reset to the hdc */
};
E 3

D 2
#define B_LOCALIO	B_NOT1K
E 2
I 2
D 3
#define	B_LOCALIO	B_NOT1K
E 2

D 2
#define b_hdccommand	b_upte[0]
#define b_cyl		b_upte[1]
#define b_head		b_upte[2]
#define b_sector	b_upte[3]
E 2
I 2
#define	b_hdccommand	b_upte[0]
#define	b_cyl		b_upte[1]
#define	b_head		b_upte[2]
#define	b_sector	b_upte[3]
E 2

E 3
/*
D 3
 * These are the 4 hdc i/o register addresses.
 *
 * Writing to "master_mcb_reg" tells the hdc controller where the master
 * mcb is and initiates hdc operation. The hdc then reads the master mcb
 * and all new mcb's in the active mcb queue.
 *
 * Writing to "module_id_reg" causes the hdc to return the hdc's module id
 * word in the location specified by the address written into the register.
E 3
I 3
 * Definition for the module id returned by the hdc when "module_id"
 * is written to.  The format is defined by the hdc microcode.
E 3
 */
I 3
#define	HID_HDC		0x01		/* hvme_id for HDC */
#define	HDC_MID		HID_HDC		/* module id code for hdc's */
struct module_id {
	u_char	module_id,		/* module id; hdc's return HDC_MID */
		reserved,
		code_rev,		/* micro-code rev#; FF= not loaded */
		fit;			/* FIT test result; FF= no error */
};
E 3

D 3
typedef struct {
D 2
	unsigned long	master_mcb_reg;	/* set the master mcb address       */
	unsigned long	module_id_reg;	/* returns hdc's module id (hdc_mid)*/
	unsigned long	soft_reset_reg;	/* a write here shuts down the hdc  */
	unsigned long	hard_reset_reg;	/* send a system reset to the hdc   */
E 2
I 2
	unsigned long	master_mcb_reg;	/* set the master mcb address */
	unsigned long	module_id_reg;	/* returns hdc's module id (hdc_mid) */
	unsigned long	soft_reset_reg;	/* a write here shuts down the hdc */
	unsigned long	hard_reset_reg;	/* send a system reset to the hdc */
E 2
} hdc_regs_type;

E 3
/*
D 3
 * Definition for the module id returned by the hdc when "module_id_reg"
 * is written to. The format is defined by the hdc microcode.
 */

typedef struct {
D 2
	unsigned char	module_id;	/* module id; hdc's return HDC_MID  */
	unsigned char	reserved;	/*                                  */
	unsigned char	code_rev;	/* micro-code rev#; FF= not loaded  */
	unsigned char	fit;		/* FIT test result; FF= no error    */
E 2
I 2
	unsigned char	module_id;	/* module id; hdc's return HDC_MID */
	unsigned char	reserved;
	unsigned char	code_rev;	/* micro-code rev#; FF= not loaded */
	unsigned char	fit;		/* FIT test result; FF= no error */
E 2
} hdc_mid_type;

/*
 * This structure defines the mcb's. A portion of this structure is
 * used only by the software. The other portion is set up by software
 * and sent to the hdc firmware to perform an operation; the order
 * of this part of the mcb is determined by the controller firmware.
E 3
I 3
 * This structure defines the mcb's.  A portion of this structure is used
 * only by the software.  The other portion is set up by software and sent
 * to the hdc firmware to perform an operation; the order of this part of
 * the mcb is determined by the controller firmware.
E 3
 *
D 3
 * "forw_mcb" and "back_mcb" form a doubly-linked list of mcb's.
E 3
I 3
 * "context" is the software context word.  The hdc firmware copies the
 * contents of this word to the master mcb whenever the mcb has been
 * completed.  The virtual address of the mcb is usually saved here.
E 3
 *
D 3
 * "context" is the software context word. The hdc firmware copies the
 * the contents of this word to the master mcb whenever the mcb has been
 * completed. Currently the virtual address of the mcb is saved here.
 *
 * "forw_phaddr" forms a linked list of mcbs. The addresses are physical
E 3
I 3
 * "forw_phaddr" forms a linked list of mcbs.  The addresses are physical
E 3
 * since they are used by the hdc firmware.
 *
D 3
 * Bits in device control word #1 define the hdc command and
 * control the operation of the hdc.
 *
 * Bits in device control word #2 define the disk sector address
 * for the operation defined in dcw1.
E 3
I 3
 * Bits in device control word #1 define the hdc command and control the
 * operation of the hdc.  Bits in device control word #2 define the disk
 * sector address for the operation defined in control word #1.
E 3
 */
D 3

typedef struct {
D 2
	long	lwc;			/* long word count & data chain bit*/
	long	ta;			/* transfer address                */
E 2
I 2
	long	lwc;			/* long word count & data chain bit */
	long	ta;			/* transfer address */
E 2
} data_chain_type;

D 2
#define LWC_DATA_CHAIN	0x80000000	/* mask for data chain bit in lwc  */
E 2
I 2
#define LWC_DATA_CHAIN	0x80000000	/* mask for data chain bit in lwc */
E 2

D 2
struct mcb_struct ;
typedef struct mcb_struct mcb_type ;
E 2
I 2
struct mcb_struct;
typedef struct mcb_struct mcb_type;
E 2
struct mcb_struct {
D 2
					/* this part used only by software  */
	mcb_type	*forw_mcb;	/* pointer to next mcb in chain     */
E 2
I 2
					/* this part used only by software */
	mcb_type	*forw_mcb;	/* pointer to next mcb in chain */
E 2
	mcb_type	*back_mcb;	/* pointer to previous mcb in chain */
D 2
	struct buf	*buf_ptr;	/* ptr to buf structure for this mcb*/
	long		mcb_phaddr;	/* phaddr of hw's part of this mcb  */
E 2
I 2
	struct buf	*buf_ptr;	/* ptr to buf structure for this mcb */
	long		mcb_phaddr;	/* phaddr of hw's part of this mcb */
E 2

D 2
	                                /* this part is sent to the hdc hw  */
	unsigned long	forw_phaddr;	/* phys address of next mcb         */
	unsigned	priority  :  8;	/* device control word #1           */
	unsigned	interrupt :  1;	/*        "                         */
	unsigned	drive     :  7;	/*        "                         */
	unsigned	command   : 16;	/*        "             (see HCMD_) */
	unsigned	cyl       : 13;	/* device control word #2           */
	unsigned	head      :  9;	/*        "                         */
	unsigned	sector    : 10;	/*        "                         */
	unsigned long	reserved[2];	/*                                  */
	unsigned long	context;	/* software context word            */
	data_chain_type chain[HDC_MAXCHAIN];/* data chain and lword count   */
} ;
					/* defines for the "command"s       */
#define HCMD_STATUS	0x40		/* command: read drive status       */
#define HCMD_READ	0x60		/* command: read data               */
#define HCMD_VENDOR	0x6A		/* command: read vendor data        */
#define HCMD_VERIFY	0x6D		/* command: verify a track          */
#define HCMD_WRITE	0x70		/* command: write data              */
#define HCMD_FORMAT	0x7E		/* command: format a track          */
#define HCMD_CERTIFY	0x7F		/* command: certify a track         */
#define HCMD_WCS	0xD0		/* command: write control store     */
E 2
I 2
					/* this part is sent to the hdc hw */
	unsigned long	forw_phaddr;	/* phys address of next mcb */
	unsigned	priority  :  8;	/* device control word #1 */
	unsigned	interrupt :  1;	/*        "               */
	unsigned	drive     :  7;	/*        "               */
	unsigned	command   : 16;	/*        "   (see HCMD_) */
	unsigned	cyl       : 13;	/* device control word #2 */
	unsigned	head      :  9;	/*        "               */
	unsigned	sector    : 10;	/*        "               */
	unsigned long	reserved[2];	/*                        */
	unsigned long	context;	/* software context word */
	data_chain_type chain[HDC_MAXCHAIN];/* data chain and lword count */
E 3
I 3
#define	LWC_DATA_CHAIN	0x80000000	/* mask for data chain bit in wcount */
struct mcb {
	u_long	forw_phaddr;		/* phys address of next mcb */
	u_int	priority  :  8,		/* device control word #1 */
		interrupt :  1,		/*        "               */
		drive     :  7,		/*        "               */
		command   : 16,		/*        "   (see HCMD_) */
		cyl       : 13,		/* device control word #2 */
		head      :  9,		/*        "               */
		sector    : 10;		/*        "               */
	u_long	r1, r2,
		context;		/* software context word */
	struct chain {
		long	wcount,		/* word count */
			memadr;		/* transfer address */
	} chain[HDC_MAXCHAIN];		/* data chain */
E 3
};
					/* defines for the "command"s */
#define	HCMD_STATUS	0x40		/* command: read drive status */
#define	HCMD_READ	0x60		/* command: read data */
D 3
#define	HCMD_VENDOR	0x6A		/* command: read vendor data */
#define	HCMD_VERIFY	0x6D		/* command: verify a track */
E 3
I 3
#define	HCMD_VENDOR	0x6a		/* command: read vendor data */
#define	HCMD_VERIFY	0x6d		/* command: verify a track */
E 3
#define	HCMD_WRITE	0x70		/* command: write data */
D 3
#define	HCMD_FORMAT	0x7E		/* command: format a track */
#define	HCMD_CERTIFY	0x7F		/* command: certify a track */
#define	HCMD_WCS	0xD0		/* command: write control store */
E 3
I 3
#define	HCMD_FORMAT	0x7e		/* command: format a track */
#define	HCMD_CERTIFY	0x7f		/* command: certify a track */
#define	HCMD_WCS	0xd0		/* command: write control store */
E 3
E 2

/*
 * This structure defines the master mcb - one per hdc controller.
 * The order of this structure is determined by the controller firmware.
 * "R" and "W" indicate read-only and write-only.
 *
 * Bits in the module control long word, "mcl", control the invocation of
 * operations on the hdc.
 *
D 3
 * The hdc operates in queued mode or immediate mode.
 * In queued mode, it grabs new mcb's, prioritizes them, and adds
 * them to its queue; it knows if we've added any mcb's by checking
 * forw_phaddr to see if any are linked off of there.
E 3
I 3
 * The hdc operates in queued mode or immediate mode.  In queued mode, it
 * grabs new mcb's, prioritizes them, and adds them to its queue; it knows
 * if we've added any mcb's by checking forw_phaddr to see if any are
 * linked off of there.
E 3
 *
 * Bits in the master mcb's status word, "mcs", indicate the status
D 3
 * of the last-processed mcb. The MCS_ definitions define these bits.
E 3
I 3
 * of the last-processed mcb.  The MCS_ definitions define these bits.
E 3
 * This word is set to zero when the mcb queue is passed to the hdc
 * controller; the hdc controller then sets bits in this word.
 * We cannot modify the mcb queue until the hdc has completed an mcb
 * (the hdc sets the MCS_Q_DONE bit).
 *
 * The "context" word is copied from the context word of the completed
D 3
 * mcb. It is currently the virtual pointer to the completed mcb.
E 3
I 3
 * mcb.  It is currently the virtual pointer to the completed mcb.
E 3
 */
D 3

typedef struct {
D 2
	unsigned long	mcl;		/* W  module control lword (MCL_)   */
	unsigned long	interrupt;	/* W  interrupt acknowledge word    */
E 2
I 2
	unsigned long	mcl;		/* W  module control lword (MCL_) */
	unsigned long	interrupt;	/* W  interrupt acknowledge word */
E 2
	unsigned long	forw_phaddr;	/* W  physical address of first mcb */
D 2
	unsigned long	reserve1;	/*                                  */
	unsigned long	reserve2;	/*                                  */
E 2
I 2
	unsigned long	reserve1;
	unsigned long	reserve2;
E 2
	unsigned long	mcs;		/* R  status for last completed mcb */
D 2
	unsigned long	cmcb_phaddr;	/* W  physical addr of completed mcb*/
	unsigned long	context;	/* R  software context word         */
	unsigned long	xstatus[HDC_XSTAT_SIZE];/* R  xstatus of last mcb   */
E 2
I 2
	unsigned long	cmcb_phaddr;	/* W  physical addr of completed mcb */
	unsigned long	context;	/* R  software context word */
	unsigned long	xstatus[HDC_XSTAT_SIZE];/* R  xstatus of last mcb */
E 2
} master_mcb_type;

E 3
D 2
					/* definition of master mcb "mcl"   */
#define MCL_QUEUED	0x00000010	/* start queued execution of mcb's  */
#define MCL_IMMEDIATE	0x00000001	/* start immediate xqt of an mcb    */
E 2
I 2
					/* definition of master mcb "mcl" */
#define	MCL_QUEUED	0x00000010	/* start queued execution of mcb's */
#define	MCL_IMMEDIATE	0x00000001	/* start immediate xqt of an mcb */
E 2
D 3

E 3
D 2
					/* definition of master mcb "mcs"   */
#define MCS_DONE	0x00000080	/* an mcb is done; status is valid  */
#define MCS_FATALERROR	0x00000002	/* a fatal error occurred	    */
#define MCS_SOFTERROR	0x00000001	/* a recoverable error occurred     */
E 2
I 2
					/* definition of master mcb "mcs" */
#define	MCS_DONE	0x00000080	/* an mcb is done; status is valid */
#define	MCS_FATALERROR	0x00000002	/* a fatal error occurred */
#define	MCS_SOFTERROR	0x00000001	/* a recoverable error occurred */
E 2

I 3
struct master_mcb {
	u_long	mcw,			/* W  module control word (MCL_) */
		interrupt,		/* W  interrupt acknowledge word */
		forw_phaddr,		/* W  physical address of first mcb */
		r1, r2,
		mcs,			/* R  status for last completed mcb */
		cmcb_phaddr,		/* W  physical addr of completed mcb */
		context,		/* W  software context word */
#define	HDC_XSTAT_SIZE	128		/* size of extended status (lwords) */
		xstatus[HDC_XSTAT_SIZE];/* R  xstatus of last mcb */
};

E 3
/*
D 3
 * This structure defines the information returned by the hdc
 * controller for a "read drive status" (HCMD_STATUS) command.
 * The format of this structure is determined by the hdc firmware.
 * r1, r2, etc. are reserved for future use.
E 3
I 3
 * This structure defines the information returned by the hdc controller for
 * a "read drive status" (HCMD_STATUS) command.  The format of this structure
 * is determined by the hdc firmware.  r[1-11] are reserved for future use.
E 3
 */
D 3

typedef struct {
D 2
	unsigned long	drs;		/* drive status (see DRS_ below)    */
	unsigned long	r1;		/*                                  */
	unsigned long	r2;		/*                                  */
	unsigned long	r3;		/*                                  */
	unsigned short	max_cyl;	/* max logical cylinder address     */
	unsigned short	max_head;	/* max logical head address         */
	unsigned short	r4;		/*                                  */
	unsigned short	max_sector;	/* max logical sector address       */
	unsigned short	def_cyl;	/* definition track cylinder address*/
	unsigned short	def_cyl_count;	/* definition track cylinder count  */
	unsigned short	diag_cyl;	/* diagnostic track cylinder address*/
	unsigned short	diag_cyl_count;	/* diagnostic track cylinder count  */
	unsigned short	max_phys_cyl;	/* max physical cylinder address    */
	unsigned short	max_phys_head;	/* max physical head address        */
	unsigned short	r5;		/*                                  */
	unsigned short	max_phys_sector;/* max physical sector address      */
	unsigned short	r6;		/*                                  */
	unsigned short	id;		/* drive id (drive model)           */
	unsigned short	r7;		/*                                  */
	unsigned short	bytes_per_sec;	/* bytes/sector -vendorflaw conversn*/
	unsigned short	r8;		/*                                  */
	unsigned short	rpm;		/* disk revolutions per minute      */
	unsigned long	r9;		/*                                  */
	unsigned long	r10;		/*                                  */
	unsigned long	r11;		/*                                  */
E 2
I 2
	unsigned long	drs;		/* drive status (see DRS_ below) */
	unsigned long	r1;
	unsigned long	r2;
	unsigned long	r3;
	unsigned short	max_cyl;	/* max logical cylinder address */
	unsigned short	max_head;	/* max logical head address */
	unsigned short	r4;
	unsigned short	max_sector;	/* max logical sector address */
	unsigned short	def_cyl;	/* definition track cylinder address */
	unsigned short	def_cyl_count;	/* definition track cylinder count */
	unsigned short	diag_cyl;	/* diagnostic track cylinder address */
	unsigned short	diag_cyl_count;	/* diagnostic track cylinder count */
	unsigned short	max_phys_cyl;	/* max physical cylinder address */
	unsigned short	max_phys_head;	/* max physical head address */
	unsigned short	r5;
	unsigned short	max_phys_sector;/* max physical sector address */
	unsigned short	r6;
	unsigned short	id;		/* drive id (drive model) */
	unsigned short	r7;
	unsigned short	bytes_per_sec;	/* bytes/sector -vendorflaw conversn */
	unsigned short	r8;
	unsigned short	rpm;		/* disk revolutions per minute */
	unsigned long	r9;
	unsigned long	r10;
	unsigned long	r11;
E 2
} drive_stat_type;

E 3
D 2
					/* defines for drive_stat drs word  */
#define DRS_FAULT	0x00000080	/* drive is reporting a fault       */
#define DRS_RESERVED	0x00000040	/* drive is reserved by other port  */
#define DRS_WRITE_PROT	0x00000020	/* drive is write protected         */
#define DRS_ON_CYLINDER	0x00000002	/* drive heads are not moving now   */
#define DRS_ONLINE	0x00000001	/* drive is available for operation */
E 2
I 2
					/* defines for drive_stat drs word */
#define	DRS_FAULT	0x00000080	/* drive is reporting a fault */
#define	DRS_RESERVED	0x00000040	/* drive is reserved by other port */
#define	DRS_WRITE_PROT	0x00000020	/* drive is write protected */
#define	DRS_ON_CYLINDER	0x00000002	/* drive heads are not moving now */
#define	DRS_ONLINE	0x00000001	/* drive is available for operation */
E 2

I 3
struct status {
	u_long	drs,			/* drive status (see DRS_) */
		r1, r2, r3;
	u_short	max_cyl,		/* max logical cylinder address */
		max_head,		/* max logical head address */
		r4,
		max_sector,		/* max logical sector address */
		def_cyl,		/* definition track cylinder address */
		def_cyl_count,		/* definition track cylinder count */
		diag_cyl,		/* diagnostic track cylinder address */
		diag_cyl_count,		/* diagnostic track cylinder count */
		max_phys_cyl,		/* max physical cylinder address */
		max_phys_head,		/* max physical head address */
		r5,
		max_phys_sector,	/* max physical sector address */
		r6,
		id,			/* drive id (drive model) */
		r7,
		bytes_per_sec,		/* bytes/sector -vendorflaw conversn */
		r8,
		rpm;			/* disk revolutions per minute */
	u_long	r9, r10, r11;
};

#ifdef COMPAT_42
#define	GB_ID		"geometry"
#define	GB_ID_LEN 	sizeof(GB_ID)-1
#define	GB_MAXPART	8
#define	GB_VERSION	1

#define	HDC_DEFPART	GB_MAXPART-1	/* partition# of def and diag cyls */
#define	BPS		512		/* bytes per sector */

E 3
/*
D 3
 * hdc controller table. It contains information specific to each controller.
E 3
I 3
 * Geometry Block:
 *
 * The geometry block defines partition offsets and information about the
 * flaw maps on the flaw map track.  It resides on the first sector of the
 * flaw map track.  This structure is also used by vddc disk controllers.
 * In this case, the block resides at sector 0 of the disk.
 *
 * The geometry_sector structure defines the sector containing the geometry
 * block.  This sector is checksumed independent of the geometry information.
 * The fields in these structured which should never be moved are the id and
 * version fields in the geometry_block structure and the checksum field in
 * the geometry_sector structure.  This will provide for easy extensions in
 * the future.
E 3
 */

I 3
#define	DRIVE_TYPE	flaw_offset	/* For VDDC Geometry Blocks Only */

E 3
typedef struct {
D 2
	int		ctlr;		/* controller number (0-15)         */
E 2
I 2
D 3
	int		ctlr;		/* controller number (0-15) */
E 2
	hdc_regs_type	*registers;	/* base address of hdc io registers */
D 2
	mcb_type	*forw_active;	/* doubly linked list of            */
	mcb_type	*back_active;	/* .. active mcb's                  */
	mcb_type	*forw_free;	/* doubly linked list of            */
	mcb_type	*back_free;	/* .. free mcb's                    */
	mcb_type	*forw_wait;	/* doubly linked list of            */
	mcb_type	*back_wait;	/* .. waiting mcb's                 */
	hdc_mid_type	mid;		/* the module id is read to here    */
	long		master_phaddr;	/* physical address of master mcb   */
	master_mcb_type master_mcb;	/* the master mcb for this hdc      */
	mcb_type	mcbs[HDC_MAXMCBS];/* pool of mcb's for this hdc     */
E 2
I 2
	mcb_type	*forw_active;	/* doubly linked list of */
	mcb_type	*back_active;	/* .. active mcb's */
	mcb_type	*forw_free;	/* doubly linked list of */
	mcb_type	*back_free;	/* .. free mcb's */
	mcb_type	*forw_wait;	/* doubly linked list of */
	mcb_type	*back_wait;	/* .. waiting mcb's */
	hdc_mid_type	mid;		/* the module id is read to here */
	long		master_phaddr;	/* physical address of master mcb */
	master_mcb_type master_mcb;	/* the master mcb for this hdc */
	mcb_type	mcbs[HDC_MAXMCBS];/* pool of mcb's for this hdc */
E 2
} hdc_ctlr_type;
E 3
I 3
	char	id[GB_ID_LEN];		/* identifies the geometry block */
	long	version,		/* geometry block version number */
		flaw_offset,		/* flaw map byte offset in partition7 */
		flaw_size,		/* harris flaw map size in bytes */
		flaw_checksum,		/* sum of bytes in harris flaw map */
		unused[3];		/* --- available for use */
	struct par_tab {
		long	start,		/* starting 1K block number */
			length;		/* partition size in 1K blocks */
	} partition[GB_MAXPART];	/* partition definitions */
} geometry_block;
E 3

I 3
typedef struct {
	geometry_block	geometry_block;	/* disk geometry */
	char	filler[BPS - sizeof(geometry_block) - sizeof(long)];
	long	checksum;		/* sector checksum */
} geometry_sector;

E 3
/*
D 3
 * hdc unit table. It contains information specific to each hdc drive.
 * Some information is obtained from the profile prom and geometry block.
E 3
I 3
 * GB_CHECKSUM:
 *
 * This macro computes the checksum for the geometry sector and returns the
 * value.  Input to this macro is a pointer to the geometry_sector.  Pretty
 * useless, should at least have done an XOR.
E 3
 */
D 3

typedef struct {
D 2
	par_tab		partition[GB_MAXPART]; /* partition definitions     */
	int		ctlr;		/* the controller number (0-15)     */
	int		slave;		/* the slave number (0-4)           */
	int		unit;		/* the unit number (0-31)           */
	int		id;		/* identifies the disk model        */
	int		spc;		/* sectors per cylinder             */
	int		cylinders;	/* number of logical cylinders      */
	int		heads;		/* number of logical heads          */
	int		sectors;	/* number of logical sectors/track  */
	int		phys_cylinders;	/* number of physical cylinders     */
	int		phys_heads;	/* number of physical heads         */
E 2
I 2
	par_tab	partition[GB_MAXPART];	/* partition definitions */
	int		ctlr;		/* the controller number (0-15) */
	int		slave;		/* the slave number (0-4) */
	int		unit;		/* the unit number (0-31) */
	int		id;		/* identifies the disk model */
	int		spc;		/* sectors per cylinder */
	int		cylinders;	/* number of logical cylinders */
	int		heads;		/* number of logical heads */
	int		sectors;	/* number of logical sectors/track */
	int		phys_cylinders;	/* number of physical cylinders */
	int		phys_heads;	/* number of physical heads */
E 2
	int		phys_sectors;	/* number of physical sectors/track */
D 2
	int		def_cyl;	/* logical cylinder of drive def    */
	int		def_cyl_count;	/* number of logical def cylinders  */
	int		diag_cyl;	/* logical cylinder of diag area    */
E 2
I 2
	int		def_cyl;	/* logical cylinder of drive def */
	int		def_cyl_count;	/* number of logical def cylinders */
	int		diag_cyl;	/* logical cylinder of diag area */
E 2
	int		diag_cyl_count;	/* number of logical diag cylinders */
D 2
	int		rpm;		/* disk rpm                         */
	int		bytes_per_sec;	/* bytes/sector -vendorflaw conversn*/
	int		format;		/* TRUE= format program is using dsk*/
	mcb_type	phio_mcb;	/* mcb for handler physical io      */
	struct buf	phio_buf;	/* buf for handler physical io      */
	unsigned long	phio_data[HDC_PHIO_SIZE]; /* data for physical io   */
	struct buf	raw_buf;	/* buf structure for raw i/o        */
E 2
I 2
	int		rpm;		/* disk rpm */
	int		bytes_per_sec;	/* bytes/sector -vendorflaw conversn */
	int		format;		/* TRUE= format program is using dsk */
	mcb_type	phio_mcb;	/* mcb for handler physical io */
	struct buf	phio_buf;	/* buf for handler physical io */
	unsigned long	phio_data[HDC_PHIO_SIZE]; /* data for physical io */
	struct buf	raw_buf;	/* buf structure for raw i/o */
E 2
} hdc_unit_type;
E 3
I 3
#define GB_CHECKSUM(_gs_ptr, _checksum) { \
	register u_char *_ptr; \
	register u_long _i, _xsum; \
	_xsum = 0; \
	_ptr = (u_char *)(_gs_ptr); \
	for (_i = 0; _i < (sizeof(geometry_sector) - sizeof(long)); _i++) \
		_xsum += * _ptr++; \
	_checksum = _xsum; \
}
#endif /* COMPAT_42 */
E 3
E 1
