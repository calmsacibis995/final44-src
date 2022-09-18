h24995
s 00002/00002/00230
d D 8.1 93/06/10 21:47:55 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00010/00002/00222
d D 7.7 92/12/26 16:49:53 hibler 7 6
c Utah update (mostly disklabels)
e
s 00035/00024/00189
d D 7.6 92/06/18 21:33:14 hibler 6 5
c merge with latest Utah version
e
s 00001/00001/00212
d D 7.5 92/02/14 19:41:41 sklower 5 4
c gnu cpp balks on single apostrophes in asm comments.
e
s 00055/00002/00158
d D 7.4 91/05/07 10:05:39 hibler 4 3
c DIO-II support 
e
s 00007/00004/00153
d D 7.3 91/05/05 13:42:25 bostic 3 2
c add bootdev variable (not used by HP), rename openfirst to firstopen
e
s 00006/00001/00151
d D 7.2 90/05/25 16:18:04 mckusick 2 1
c "update from Mike Hibler at Utah"
e
s 00152/00000/00000
d D 7.1 90/05/08 22:46:13 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
/*
 * Copyright (c) 1988 University of Utah.
D 8
 * Copyright (c) 1982, 1990 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1982, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * the Systems Programming Group of the University of Utah Computer
 * Science Department.
 *
 * %sccs.include.redist.c%
 *
D 4
 * from: Utah $Hdr: srt0.c 1.8 88/12/03$
E 4
I 4
D 6
 * from: Utah $Hdr: srt0.c 1.12 91/04/25$
E 6
I 6
D 7
 * from: Utah $Hdr: srt0.c 1.15 92/06/18$
E 7
I 7
 * from: Utah $Hdr: srt0.c 1.18 92/12/21$
E 7
E 6
E 4
 *
 *	%W% (Berkeley) %G%
 */

/*
 * Startup code for standalone system
 */

	.globl	begin
	.globl	_end
	.globl	_edata
	.globl	_main
	.globl	_configure
D 3
	.globl	_openfirst
E 3
I 3
D 6
	.globl	_bootdev
E 6
	.globl	_firstopen
E 3
	.globl	__rtt
D 2
	.globl	_lowram,_howto,_devtype
E 2
I 2
D 4
	.globl	_lowram,_howto,_devtype,_internalhpib
E 4
I 4
D 6
	.globl	_lowram,_howto,_devtype,_internalhpib,_machineid
E 6
I 6
	.globl	_bootdev,_howto,_lowram,_machineid
	.globl	_internalhpib
E 6
E 4
E 2

	STACK =    0xfffff000	| below the ROM page
	BOOTTYPE = 0xfffffdc0
	LOWRAM =   0xfffffdce
I 2
	SYSFLAG =  0xfffffed2	| system flags
E 2
	MSUS =	   0xfffffedc	| MSUS (?) structure
	VECTORS =  0xfffffee0	| beginning of jump vectors
	NMIRESET = 0xffffff9c	| reset vector
	BUSERR =   0xfffffffc
	MAXADDR =  0xfffff000
	NBPG =     4096
I 4
	MMUCMD =   0x005f400c	| MMU command/status register
E 4

	.data
D 3
_lowram:
E 3
I 3
_bootdev:
E 3
	.long	0
I 3
D 6
_devtype:
	.long	0
E 6
E 3
_howto:
	.long	0
D 3
_devtype:
E 3
I 3
_lowram:
E 3
	.long	0
I 4
_machineid:
	.long	0
E 4

	.text
begin:
	movl	#STACK,sp
	moveq	#47,d0		| # of vectors - 1
	movl	#VECTORS+2,a0	| addr part of first vector
vecloop:
	movl	#trap,a0@	| make it direct to trap
	addql	#6,a0		| move to next vector addr
	dbf	d0,vecloop	| go til done
	movl	#NMIRESET,a0	| NMI keyboard reset addr
	movl	#nmi,a0@	| catch in reset routine
I 4
/*
 * Determine our CPU type and look for internal HP-IB
 * (really only care about detecting 320 (no DIO-II) right now).
 */
	lea	_machineid,a0
	movl	#0x808,d0
	movc	d0,cacr		| clear and disable on-chip cache(s)
	movl	#0x200,d0	| data freeze bit
	movc	d0,cacr		|   only exists on 68030
	movc	cacr,d0		| read it back
	tstl	d0		| zero?
D 6
	jeq	is68020		| yes, we have 68020
E 6
I 6
	jeq	not68030	| yes, we have 68020/68040
E 6
	movl	#0x808,d0
	movc	d0,cacr		| clear data freeze bit again
I 6

E 6
	movl	#0x80,MMUCMD	| set magic cookie
	movl	MMUCMD,d0	| read it back
	btst	#7,d0		| cookie still on?
	jeq	not370		| no, 360 or 375
	movl	#4,a0@		| consider a 370 for now
	movl	#0,MMUCMD	| clear magic cookie
	movl	MMUCMD,d0	| read it back
	btst	#7,d0		| still on?
	jeq	ihpibcheck	| no, a 370
	movl	#5,a0@		| yes, must be a 340
	jra	ihpibcheck
not370:
	movl	#3,a0@		| type is at least a 360
	movl	#0,MMUCMD	| clear magic cookie2
	movl	MMUCMD,d0	| read it back
	btst	#16,d0		| still on?
	jeq	ihpibcheck	| no, a 360
	movl	#6,a0@		| yes, must be a 345/375/400
	jra	ihpibcheck
I 6
not68030:
	bset	#31,d0		| data cache enable bit
	movc	d0,cacr		|   only exists on 68040
	movc	cacr,d0		| read it back
	tstl	d0		| zero?
	beq	is68020		| yes, we have 68020
	moveq	#0,d0		| now turn it back off
	movec	d0,cacr		|   before we access any data
	.long	0x4e7b0004	| movc d0,itt0
	.long	0x4e7b0005	| movc d0,itt1
	.long	0x4e7b0006	| movc d0,dtt0
	.long	0x4e7b0007	| movc d0,dtt1
D 7
	movl	#7,a0@		| we have a 380
E 7
I 7
	.word	0xf4d8		| cinva bc
	movl	MMUCMD,d0	| get MMU register
	lsrl	#8,d0		| get apparent ID
	cmpb	#6,d0		| id == 6?
	jeq	is33mhz		| yes, we have a 433s
	movl	#7,a0@		| no, we have a 380/425t
	jra	ihpibcheck
is33mhz:
	movl	#8,a0@		| 433s (XXX 425s returns same ID, ugh!)
E 7
	jra	ihpibcheck
E 6
is68020:
	movl	#1,a0@		| consider a 330 for now
	movl	#1,MMUCMD	| a 68020, write HP MMU location
	movl	MMUCMD,d0	| read it back
	btst	#0,d0		| zero?
	jeq	ihpibcheck	| yes, a 330
	movl	#0,a0@		| no, consider a 320 for now
	movl	#0x80,MMUCMD	| set magic cookie
	movl	MMUCMD,d0	| read it back
	btst	#7,d0		| cookie still on?
	jeq	ihpibcheck	| no, just a 320
	movl	#2,a0@		| yes, a 350
ihpibcheck:
	movl	#0,MMUCMD	| make sure MMU is off
E 4
I 2
	btst	#5,SYSFLAG	| do we have an internal HP-IB?
	jeq	boottype	| yes, continue
	clrl	_internalhpib	| no, clear the internal address
I 4
/*
D 6
 * If this is a reboot, extract howto/devtype stored by kernel
E 6
I 6
 * If this is a reboot, extract howto/bootdev stored by kernel
E 6
 */
E 4
boottype:
E 2
	cmpw	#12,BOOTTYPE	| is this a reboot (REQ_REBOOT)?
	jne	notreboot	| no, skip
D 6
	movl	#MAXADDR,a0	| find last page
	movl	a0@+,d7		| and extract howto, devtype
E 6
I 6
	lea	MAXADDR,a0	| find last page
	movl	a0@+,d7		| and extract howto, bootdev
E 6
	movl	a0@+,d6		|   from where doboot() left them
	jra	boot1
/*
D 6
 * At this point we do not know which logical hpib the given select
 * code refers to.  So we just put the select code in the adaptor field
 * where hpibinit() can replace it with the logical hpib number.
 * Note that this may clobber the B_DEVMAGIC field but that isn't set
 * til later anyway.
E 6
I 6
 * At this point we do not know which logical device the MSUS select
 * code refers to so we cannot construct bootdev.  So we just punt
 * and let configure() construct it.
E 6
 */
notreboot:
I 6
	moveq	#0,d6		| make sure bootdev is invalid
E 6
	cmpw	#18,BOOTTYPE	| does the user want to interact?
	jeq	askme		| yes, go to it
D 6
	movl	MSUS,d1		| no, get rom info
	movw	d1,d6		| MSUS comes with SC in upper, unit in lower
	swap	d6		| put in place
	movw	#2,d6		| assume 'a' partition of rd disk
E 6
	moveq	#0,d7		| default to RB_AUTOBOOT
	jra	boot1
askme:
D 6
	moveq	#7,d6		| default to HP-IB at sc7
	lslw	#8,d6		| position as adaptor number
	swap	d6		| put in place (note implied unit 0)
	movw	#2,d6		| assume 'a' partition of rd disk
E 6
	moveq	#3,d7		| default to RB_SINGLE|RB_ASKNAME
boot1:
D 6
	movl	d6,_devtype	| save devtype and howto
E 6
I 6
	movl	d6,_bootdev	| save bootdev and howto
E 6
	movl	d7,_howto	|   globally so all can access
	movl	LOWRAM,d0	| read lowram value from bootrom
	addl	#NBPG,d0	| must preserve this for bootrom to reboot
	andl	#0xfffff000,d0	| round to next page
	movl	d0,_lowram	| stash that value
start:
	movl	#_edata,a2	| start of BSS
	movl	#_end,a3	| end
clr:
	clrb	a2@+		| clear BSS
	cmpl	a2,a3		| done?
	bne	clr		| no, keep going
	jsr	_configure	| configure critical devices
D 3
	movl	#1,_openfirst	| mark this as the first open
E 3
I 3
	movl	#1,_firstopen	| mark this as the first open
E 3
	jsr	_main		| lets go
__rtt:
	movl	#3,_howto	| restarts get RB_SINGLE|RB_ASKNAME
	jmp	start

/*
 * probe a location and see if it causes a bus error
 */
	.globl	_badaddr
_badaddr:
	movl	BUSERR,__bsave	| save ROM bus error handler address
	movl	sp,__ssave	| and current stack pointer
	movl	#catchbad,BUSERR| plug in our handler
	movl	sp@(4),a0	| address to probe
	movw	a0@,d1		| do it
D 5
	movl	__bsave,BUSERR	| if we got here, it didn't fault
E 5
I 5
D 6
	movl	__bsave,BUSERR	| if we got here, it didn''t fault /* XXX cpp */
E 6
I 6
	movl	__bsave,BUSERR	| if we got here, it did not fault
E 6
E 5
	clrl	d0		| return that this was not a bad addr
	rts

catchbad:
	movl	__bsave,BUSERR	| got a bus error, so restore old handler
	movl	__ssave,sp	| manually restore stack
	moveq	#1,d0		| indicate that we got a fault
	rts			| return to caller of badaddr()

__bsave:
	.long	0
__ssave:
	.long	0

	.globl	_trap
trap:
	moveml	#0xFFFF,sp@-	| save registers
	movl	sp,sp@-		| push pointer to frame
	jsr	_trap		| call C routine to deal with it
I 6
	tstl	d0
	jeq	Lstop
	addql	#4,sp
	moveml	sp@+,#0x7FFF
	addql	#8,sp
	rte
Lstop:
E 6
	stop	#0x2700		| stop cold

nmi:
	movw	#18,BOOTTYPE	| mark as system switch
	jsr	_kbdnmi		| clear the interrupt
	jra	begin		| start over

#ifdef ROMPRF
	.globl	_romout
_romout:
	movl	sp@(4),d0	| line number
	movl	sp@(8),a0	| string
	jsr	0x150		| do it
	rts
#endif
E 1
