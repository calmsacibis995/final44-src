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
 * $Log:	xpr.c,v $
 * Revision 2.6  89/03/09  20:17:38  rpd
 * 	More cleanup.
 * 
 * Revision 2.5  89/02/25  18:10:59  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.4  89/01/23  22:19:24  af
 * 	Make xprflags unsigned
 * 	[89/01/10            af]
 * 
 * Revision 2.3  89/01/15  16:28:32  rpd
 * 	Use decl_simple_lock_data.
 * 	[89/01/15  15:09:52  rpd]
 * 
 * Revision 2.2  88/12/19  02:48:30  mwyoung
 * 	Fix include file references.
 * 	[88/11/22  02:17:01  mwyoung]
 * 	
 * 	Separate initialization into two phases.
 * 	[88/11/22  01:13:11  mwyoung]
 * 
 *  6-Jan-88  Michael Young (mwyoung) at Carnegie-Mellon University
 *	Eliminate use of arg6 in order to allow a more shapely event structure
 *
 * 30-Dec-87  David Golub (dbg) at Carnegie-Mellon University
 *	Delinted.
 *
 *  7-Dec-87  Richard Sanzi (sanzi) at Carnegie-Mellon University
 *	Added xpr_save() routine.
 *
 */ 
/*
 * xpr silent tracing circular buffer.
 */

#include <kern/xpr.h>
#include <kern/lock.h>
#include <machine/cpu.h>
#include <machine/machparam.h>		/* for splhigh */
#include <vm/vm_kern.h>

decl_simple_lock_data(,xprlock)

int nxprbufs = 0;	/* Number of contiguous xprbufs allocated */
unsigned int xprflags = 0;	/* Bit mask of xpr flags enabled */
struct xprbuf *xprbase;	/* Pointer to circular buffer nxprbufs*sizeof(xprbuf)*/
struct xprbuf *xprptr;	/* Currently allocated xprbuf */
struct xprbuf *xprlast;	/* Pointer to end of circular buffer */

/*VARARGS1*/
xpr(msg, arg1, arg2, arg3, arg4, arg5, arg6)
	char *msg;
{
	register s;
	register struct xprbuf *x;

#ifdef	lint
	arg6++;
#endif	lint

	/* If we aren't initialized, ignore trace request */
	if (!nxprbufs)
		return;
	/* Gaurd against all interrupts and allocate next buffer */
	s = splhigh();
	simple_lock(&xprlock);
	x = xprptr++;
	if (xprptr >= xprlast) {
		/* wrap around */
		xprptr = xprbase;
	}
	simple_unlock(&xprlock);
	splx(s);
	x->msg = msg;
	x->arg1 = arg1;
	x->arg2 = arg2;
	x->arg3 = arg3;
	x->arg4 = arg4;
	x->arg5 = arg5;
	x->timestamp = XPR_TIMESTAMP;
	x->cpuinfo = cpu_number();
}

xprbootstrap()
{
	simple_lock_init(&xprlock);
	if (nxprbufs == 0)
		return;	/* assume XPR support not desired */
	xprbase = (struct xprbuf *)kmem_alloc(kernel_map, 
			(vm_size_t)(nxprbufs * sizeof(struct xprbuf)));
	xprlast = &xprbase[nxprbufs];
	xprptr = xprbase;
}

int		xprinitial = 0;

xprinit()
{
	xprflags |= xprinitial;
}

/*
 *	Save 'number' of xpr buffers to the area provided by buffer.
 */

xpr_save(buffer,number)
struct xprbuf *buffer;
int number;
{
    int i,s;
    struct xprbuf *x;
    s = splhigh();
    simple_lock(&xprlock);
    if (number > nxprbufs) number = nxprbufs;
    x = xprptr;
    
    for (i = number - 1; i >= 0 ; i-- ) {
	if (--x < xprbase) {
	    /* wrap around */
	    x = xprlast - 1;
	}
	bcopy(x,&buffer[i],sizeof(struct xprbuf));
    }
    simple_unlock(&xprlock);
    splx(s);
}

