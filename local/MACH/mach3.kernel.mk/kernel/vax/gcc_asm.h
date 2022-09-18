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
 * $Log:	gcc_asm.h,v $
 * Revision 2.4  91/07/31  18:18:41  dbg
 * 	Make bcopy and bzero handle sizes over 64K, so that we can
 * 	eliminate blkcpy and blkclr.
 * 	[91/07/26            dbg]
 * 
 * Revision 2.3  91/05/14  17:43:12  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:17:06  dbg
 * 	Take this file seriously.
 * 	[91/03/26            dbg]
 * 
 */

#ifndef	_VAX_GCC_ASM_H_
#define	_VAX_GCC_ASM_H_

/*
 * GCC asm replacements for weird VAX instructions.
 */

#define	bcopy(src,dst,len) \
	({ \
	    if ((len) <= 65535) { \
		asm("movc3 %0,%1,%2" \
		    : \
		    : "g" (len), "m" (*(char *)(src)), "m" (*(char *)(dst)) \
		    : "r0", "r1", "r2", "r3", "r4", "r5"); \
	    } \
	    else { \
		_bcopy((src),(dst),(len)); \
	    } \
	})
	   
#define	bzero(dst,len) \
	({ \
	    if ((len) <= 65535) { \
		asm("movc5 $0,%1,$0,%0,%1" \
		    : \
		    : "g" (len), "m" (*(char *)(dst)) \
		    : "r0", "r1", "r2", "r3", "r4", "r5"); \
	    } \
	    else { \
		_bzero((dst),(len)); \
	    } \
	})
	   
#define	bcmp(src,dst,len) \
	({ register int _result__ asm("r0"); \
	   asm("cmpc3 %0,%1,%2" \
		: \
		: "g" (len), "m" (*(char *)(src)), "m" (*(char *)(dst)) \
		: "r0", "r1", "r2", "r3"); \
	   _result__; })

#define	ovbcopy(src,dst,len) (bcopy((src),(dst),(len)))

#define	ffs(l) \
	({ register int _result__; \
	   asm("ffs $0,$32,%1,%0; bneq 0f; mnegl $1,%0; 0:" \
		: "=g" (_result__) \
		: "g" ((int)(l)) \
		); \
	   _result__ + 1; })

#define	ntohl(l) \
	({ register int _r__,_s__; \
	   _s__ = (l); \
	   asm("rotl $-8,%1,%0; insv %0,$16,$8,%0; rotl $8,%1,%1; movb %1,%0"\
		: "=&g" (_r__) \
		: "g" (_s__) \
		); \
	   _r__; })

#define	htonl(l)	(ntohl(l))

#define	copyin(from, to, size) \
	({ register char *_src__ asm("r1"); \
	   register char *_dst__ asm("r3"); \
	   register int   _len__ asm("r5"); \
	   register int	  _result__ asm("r0"); \
	   _src__ = (char *) (from); \
	   _dst__ = (char *) (to); \
	   _len__ = (size); \
	   asm volatile("jsb _Copyin" \
		     : "=g" (_result__) \
		     : "r" (_src__), "r" (_dst__), "r" (_len__) \
		     : "r1", "r2", "r3", "r4", "r5"); \
	   _result__; })

#define	copyout(from, to, size) \
	({ register char *_src__ asm("r1"); \
	   register char *_dst__ asm("r3"); \
	   register int   _len__ asm("r5"); \
	   register int	  _result__ asm("r0"); \
	   _src__ = (char *) (from); \
	   _dst__ = (char *) (to); \
	   _len__ = (size); \
	   asm volatile("jsb _Copyout" \
		     : "=g" (_result__) \
		     : "r" (_src__), "r" (_dst__), "r" (_len__) \
		     : "r1", "r2", "r3", "r4", "r5"); \
	   _result__; })

#define	copyinmsg(from, to, size)	(copyin(from, to, size))
#define	copyoutmsg(from, to, size)	(copyout(from, to, size))

#endif	/* _VAX_GCC_ASM_H_ */
