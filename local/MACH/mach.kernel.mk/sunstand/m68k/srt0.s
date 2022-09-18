/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	srt0.s,v $
 * Revision 2.2  89/07/12  00:25:37  jjc
 * 	Added 'exitto' and 'call' to pass 'esym' (end of loaded
 * 	symbol table) to the booted program.
 * 	[89/06/05            jjc]
 * 
 */

	.data
	.asciz	"@(#)srt0.s 1.4 88/02/08 Copyr 1985 Sun Micro";
	.even

#include "assym.s"

| Define the load address globally for readfile()
	.globl	_LOAD
_LOAD:
	.long	LOAD			| Actual address where we're loaded

| This variable is used in the DELAY macro.  5 is the right value for
| 68010's running 10MHz.  3 is the right value for 68020's running 16MHz
| with cache on.  (4x as fast at doing the delay loop.)  Other values
| should be empirically determined as needed.  Srt0.s sets this value
| based on the actual runtime environment encountered.
|
| It's critical that the value be no SMALLER than required, e.g. the
| DELAY macro guarantees a MINIMUM delay, not a maximum.
	.globl	_cpudelay
_cpudelay:
	.long	5			| Multiplier for DELAY macro.

	.text

|	Copyright (c) 1985 by Sun Microsystems, Inc.

|
| Startup code for standalone system
|

	.globl	_end
	.globl	_edata
	.globl	_main
	.globl	__exit
	.globl	__exitto

HIGH = 0x2700

	.globl	_start
_start:

#ifdef  BOOTBLOCK
| The following globals are filled in by installboot (qv)
| after bootxx is built.  They contain the block numbers
| where /boot may be found.
|
| This data table must be above _start, since only what is
| above _start is copied to high memory.   That means we
| have to jump over the data, hence _start1.
|
	.globl start1, _bootb, _bbsize, _bbchecksum
	jmp     start1
_bootb:
| should be NBLKENTRIES (64), see installboot.c
	.long   0,0,0,0,0,0,0,0         | room for boot_tab
	.long   0,0,0,0,0,0,0,0
	.long   0,0,0,0,0,0,0,0
	.long   0,0,0,0,0,0,0,0
	.long   0,0,0,0,0,0,0,0
	.long   0,0,0,0,0,0,0,0
	.long   0,0,0,0,0,0,0,0
	.long   0,0,0,0,0,0,0,0
_bbsize:        .long 0
_bbchecksum:    .long 0
start1:
#endif  /* BOOTBLOCK */
	movw	#HIGH,sr		| just in case

#ifdef sun2
				| map in enough extra pages to load /vmunix
LOWMASK = 0xfffff800
FC_MAP = 0x3
	movl	#0xc0000,d2		| first virt address to map
	movl	#0xfe300180,d3		| page map entry.
	movl	#0x300,d4		| number of pages to map
map:
	movl	d2,d0
	andw	#LOWMASK,d0		| mask out low address bits.
	movl	d0,a0
	lea	FC_MAP,a1		| get function code.
	movl	d3,d0
	movc	dfc,d1
	movc	a1,dfc
	movsl	d0,a0@
	movc	d1,dfc
	addl	#0x800,d2		| increment address
	addl	#0x1,d3			| increment page frame number.
	dbra	d4,map
	movl	#0x1,d4			| delay to avoid being over-
delay2:	movl	#0xffffffff,d5		| written by delayed packets
delay1:	dbra	d5,delay1
	dbra	d4,delay2
#endif /* sun2 */

leax:	lea	pc@(_start-(leax+2)),a0	| True current location of "_start"
	lea	_start:l,a1		| Desired      location of "_start"
	movl	a0,d3			| save source address (njl)
	movl	a1,d4			| save destination address (njl)
	cmpl	a0,a1
	jeq	gobegin			| If the same, just go do it.
	movl	#_end,d0		| Desired end of program
	subl	a1,d0			| Calculate length, round up.
	lsrl	#2,d0
	movl	d0,d5			| save length in words (njl)
movc:	movl	a0@+,a1@+		| Move it where it belongs.
	dbra	d0,movc

|	Test if 68020: Use the 68020 scaled indexing mode, which is ignored by
|	68000/68010.
gobegin:
	moveq	#is020-is010,d0		| Set up jump offset
|	jmp	pc@((is010-.)-(is020-is010),d0:w*2)	| Jump if 68010
	.word	0x4EFB
J:	.word	0x0200+(is010-J)-(is020-is010)
is020:
| Turn on the cache...
	moveq	#CACR_CLEAR+CACR_ENABLE,d0
	.long	0x4e7b0002		| movc	d0,cacr
	moveq	#3,d0			| Set the delay factor for 68020
	movl	d0,_cpudelay
is010:
	jmp	begin:l			| Force non-PCrel jump

begin:
| We create a stack below the booter for use by the thing we are loading
	movl    sp,LOAD-4:l
	movl    #LOAD-4,sp
	movl	#_edata,a0
clr:
	clrl	a0@+
	cmpl	#_end,a0
	ble	clr
#ifdef sun2
	jsr	_setkcontext
#endif
| reset translation table to prevent YYY
	movl    V_TRANSLATION,a0
	movl    a0@, d0
	movl    #1, a0@
	clrl	sp@-			| argv = 0 for now.
	clrl	sp@-			| argc = 0 for now.
	jsr	_main
	addqw	#8,sp
	jsr	_exit			| after main() returns, call exit().
| Just fall thru into __exit if exit() ever returns.

__exit:
	movl    LOAD-4:l,sp		| Restore caller's stack pointer
	rts				| Return to caller (PROM probably)

| Transfer control to a new program, passing on the same arguments that
| we (srt0.s) received when we were started.  Note that this does NOT call
| exit() -- you'd better close your files yourself.
__exitto:
	movl	sp@(4),a0		| Address to call
	lea    LOAD-4:l,sp		| Restore caller's stack pointer
	jra	a0@			| Jump to callee using caller's stk

#if	MACH_KDB
| void call(arg, go2, esym)
|	char	*arg			| character string argument
|	int	(*go2)();		| routine to call
|	int	esym			| end of loaded symbols
|
| Calls routine 'go2', passing 'arg' on the stack, and 'esym' in
| register d0 (yech).

	.globl	_call
_call:
	movl	sp@(8),a0		| address to call
	movl	sp@(12),d0		| esym
					| argument is in right place
					| on stack, under return address
	jra	a0@			| jump to program -
					| it will return to our caller

| Transfer control to a new program, passing on the same arguments that
| we (srt0.s) received when we were started.  Note that this does NOT call
| exit() -- you'd better close your files yourself.
| Passes end of loaded program in register d0 (yech).
	.globl	_exitto
_exitto:
	movl	sp@(4),a0		| Address to call
	movl	sp@(8),d0		| esym
	movl	LOAD-4:l,sp		| Restore caller's stack pointer
	jra	a0@			| Jump to callee using caller's stk
#endif	MACH_KDB
