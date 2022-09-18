h39512
s 00001/00001/00124
d D 8.2 94/01/21 19:43:17 bostic 5 4
c typo
e
s 00002/00002/00123
d D 8.1 93/06/10 21:42:37 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00016/00000/00109
d D 7.3 92/06/05 15:37:00 hibler 3 2
c merge latest Utah hp300 code including 68040 support
e
s 00022/00010/00087
d D 7.2 91/05/07 10:02:08 hibler 2 1
c break out FP related exceptions for future 68040 support
e
s 00097/00000/00000
d D 7.1 90/05/08 18:15:43 mckusick 1 0
c merge in hp300 support from Utah
e
u
U
t
T
I 1
| Copyright (c) 1988 University of Utah
D 4
| Copyright (c) 1990 Regents of the University of California.
| All rights reserved.
E 4
I 4
| Copyright (c) 1990, 1993
D 5
|	Regents of the University of California.  All rights reserved.
E 5
I 5
|	The Regents of the University of California.  All rights reserved.
E 5
E 4
|
| %sccs.include.redist.gas%
|
|	%W% (Berkeley) %G%
|
I 3
#ifdef HPFPLIB
/*
 * XXX the HP FP library mishandles "normal" F-line faults causing
 * the kernel to crash, hence we detect it ourselves rather than just
 * vectoring to "_fline".  We also always catch unsupported data type
 * faults ourselves for no particular reason.
 */
#define	_fpbsun		_bsun
#define	_fpinex		_inex
#define	_fpdz		_dz
#define	_fpunfl		_unfl
#define	_fpoperr	_operr
#define	_fpovfl		_ovfl
#define	_fpsnan		_snan
#else
E 3
I 2
#define	_fpbsun		_fpfault
#define	_fpinex		_fpfault
#define	_fpdz		_fpfault
#define	_fpunfl		_fpfault
#define	_fpoperr	_fpfault
#define	_fpovfl		_fpfault
#define	_fpsnan		_fpfault
I 3
#endif
E 3

E 2
	.text
	.globl	_buserr,_addrerr
	.globl	_illinst,_zerodiv,_chkinst,_trapvinst,_privinst,_trace
	.globl	_badtrap
	.globl	_spurintr,_lev1intr,_lev2intr,_lev3intr
	.globl	_lev4intr,_lev5intr,_lev6intr,_lev7intr
	.globl	_trap0,_trap1,_trap2,_trap15
I 2
	.globl	_fpfline, _fpunsupp, _fpfault
	.globl	_fpbsun, _fpinex, _fpdz, _fpunfl, _fpoperr, _fpovfl, _fpsnan
	.globl	_trap12
E 2

I 2
Lvectab:
E 2
	.long	0x4ef80400	/* 0: jmp 0x400:w (unused reset SSP) */
	.long	0		/* 1: NOT USED (reset PC) */
	.long	_buserr		/* 2: bus error */
	.long	_addrerr	/* 3: address error */
	.long	_illinst	/* 4: illegal instruction */
	.long	_zerodiv	/* 5: zero divide */
	.long	_chkinst	/* 6: CHK instruction */
	.long	_trapvinst	/* 7: TRAPV instruction */
	.long	_privinst	/* 8: privilege violation */
	.long	_trace		/* 9: trace */
	.long	_illinst	/* 10: line 1010 emulator */
D 2
	.long	_illinst	/* 11: line 1111 emulator */
E 2
I 2
	.long	_fpfline	/* 11: line 1111 emulator */
E 2
	.long	_badtrap	/* 12: unassigned, reserved */
	.long	_coperr		/* 13: coprocessor protocol violation */
	.long	_fmterr		/* 14: format error */
	.long	_badtrap	/* 15: uninitialized interrupt vector */
	.long	_badtrap	/* 16: unassigned, reserved */
	.long	_badtrap	/* 17: unassigned, reserved */
	.long	_badtrap	/* 18: unassigned, reserved */
	.long	_badtrap	/* 19: unassigned, reserved */
	.long	_badtrap	/* 20: unassigned, reserved */
	.long	_badtrap	/* 21: unassigned, reserved */
	.long	_badtrap	/* 22: unassigned, reserved */
	.long	_badtrap	/* 23: unassigned, reserved */
	.long	_spurintr	/* 24: spurious interrupt */
	.long	_lev1intr	/* 25: level 1 interrupt autovector */
	.long	_lev2intr	/* 26: level 2 interrupt autovector */
	.long	_lev3intr	/* 27: level 3 interrupt autovector */
	.long	_lev4intr	/* 28: level 4 interrupt autovector */
	.long	_lev5intr	/* 29: level 5 interrupt autovector */
	.long	_lev6intr	/* 30: level 6 interrupt autovector */
	.long	_lev7intr	/* 31: level 7 interrupt autovector */
	.long	_trap0		/* 32: syscalls */
	.long	_trap1		/* 33: sigreturn syscall or breakpoint */
	.long	_trap2		/* 34: breakpoint or sigreturn syscall */
	.long	_illinst	/* 35: TRAP instruction vector */
	.long	_illinst	/* 36: TRAP instruction vector */
	.long	_illinst	/* 37: TRAP instruction vector */
	.long	_illinst	/* 38: TRAP instruction vector */
	.long	_illinst	/* 39: TRAP instruction vector */
	.long	_illinst	/* 40: TRAP instruction vector */
	.long	_illinst	/* 41: TRAP instruction vector */
	.long	_illinst	/* 42: TRAP instruction vector */
	.long	_illinst	/* 43: TRAP instruction vector */
D 2
	.long	_illinst	/* 44: TRAP instruction vector */
E 2
I 2
	.long	_trap12		/* 44: TRAP instruction vector */
E 2
	.long	_illinst	/* 45: TRAP instruction vector */
	.long	_illinst	/* 46: TRAP instruction vector */
	.long	_trap15		/* 47: TRAP instruction vector */
D 2
 	.long	_fptrap		/* 48: FPCP branch/set on unordered cond */
 	.long	_fptrap		/* 49: FPCP inexact result */
 	.long	_fptrap		/* 50: FPCP divide by zero */
 	.long	_fptrap		/* 51: FPCP underflow */
 	.long	_fptrap		/* 52: FPCP operand error */
 	.long	_fptrap		/* 53: FPCP overflow */
 	.long	_fptrap		/* 54: FPCP signalling NAN */
E 2
I 2
 	.long	_fpbsun		/* 48: FPCP branch/set on unordered cond */
 	.long	_fpinex		/* 49: FPCP inexact result */
 	.long	_fpdz		/* 50: FPCP divide by zero */
 	.long	_fpunfl		/* 51: FPCP underflow */
 	.long	_fpoperr	/* 52: FPCP operand error */
 	.long	_fpovfl		/* 53: FPCP overflow */
 	.long	_fpsnan		/* 54: FPCP signalling NAN */
E 2

D 2
	.long	_badtrap	/* 55: unassigned, reserved */
E 2
I 2
	.long	_fpunsupp	/* 55: FPCP unimplemented data type */
E 2
	.long	_badtrap	/* 56: unassigned, reserved */
	.long	_badtrap	/* 57: unassigned, reserved */
	.long	_badtrap	/* 58: unassigned, reserved */
	.long	_badtrap	/* 59: unassigned, reserved */
	.long	_badtrap	/* 60: unassigned, reserved */
	.long	_badtrap	/* 61: unassigned, reserved */
	.long	_badtrap	/* 62: unassigned, reserved */
	.long	_badtrap	/* 63: unassigned, reserved */
#define BADTRAP16	.long	_badtrap,_badtrap,_badtrap,_badtrap,\
				_badtrap,_badtrap,_badtrap,_badtrap,\
				_badtrap,_badtrap,_badtrap,_badtrap,\
				_badtrap,_badtrap,_badtrap,_badtrap
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
	BADTRAP16		/* 64-255: user interrupt vectors */
E 1
