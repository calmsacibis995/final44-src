/* 
 * Mach Operating System
 * Copyright (c) 1991,1990,1989 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	machspl.h,v $
 * Revision 2.2  93/05/15  21:32:40  mrt
 * 	Used to be machparam.h
 * 	[93/05/15            mrt]
 * 
 * Revision 2.4  93/01/14  18:00:34  danner
 * 	Proper spl typing.
 * 	[92/12/01            af]
 * 
 * Revision 2.3  91/05/14  17:44:22  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:19:21  dbg
 * 	Add inline definitions for GCC.
 * 	[91/03/21            dbg]
 * 
 * Revision 2.1  89/08/03  16:15:49  rwd
 * Created.
 * 
 * 28-Apr-89  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */
#ifndef	_VAX_MACHSPL_H_
#define	_VAX_MACHSPL_H_

#ifndef	ASSEMBLER
typedef int	spl_t;
#endif

/*
 *	Machine-dependent SPL definitions.
 *
 *	The VAX handles SPLs with 'inline'.
 */
#ifdef	__GNUC__

#define	splz(x) \
	({ int _spl__;	\
	asm volatile("mfpr $18, %0; mtpr %1, $18" \
		     : "=&g" (_spl__) \
		     : "g" ((int)(x)) \
		     ); \
	_spl__; })

#define	spl0()		splz(0)
#define	spl1()		splz(1)
#define	splsoftclock()	splz(8)
#define	splhdw()	splz(0xf)
#define	splnet()	splz(0xc)
#define	spl4()		splz(0x14)
#define	splbio()	splz(0x15)
#define	spltty()	splz(0x15)
#define	spl5()		splz(0x15)
#define	splimp()	splz(0x16)
#define	splvm()		splz(0x16)
#define	spl6()		splz(0x16)
#define	spl7()		splz(0x17)
#define	splclock()	splz(0x18)
#define	splsched()	splz(0x18)
#define	splhigh()	splz(0x1c)
#define	splblock()	splz(0x1f)

#define	splx(x) \
	({ \
	asm volatile("mtpr %0, $18" : : "g" ((int)(x)) ); \
	0; })
			/* XXX returns 0 only to cast to 'void' */

#define	setsoftclock() \
	asm volatile("mtpr $0x8, $0x14")

#endif	/* __GNUC__ */

#endif	/* _VAX_MACHSPL_H_ */
