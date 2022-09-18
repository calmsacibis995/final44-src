/* 
 * Mach Operating System
 * Copyright (c) 1991,1989,1988 Carnegie Mellon University
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
 * $Log:	cpu_data.c,v $
 * Revision 2.4  91/06/19  12:00:28  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:57:50  rvb]
 * 
 * 	Support for VaxStation 3100: new processor cvax + different
 * 	memory and bus.
 * 	[91/06/04            rvb]
 * 
 * Revision 2.3  91/05/14  17:42:09  mrt
 * 	Correcting copyright
 * 
 * Revision 2.2  91/05/08  13:15:14  dbg
 * 	Changed to new copyright.
 * 	[91/04/25            dbg]
 * 
 * Revision 2.1  89/08/03  16:22:57  rwd
 * Created.
 * 
 * 23-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */

#include <platforms.h>

#include <vax/cpu_data.h>

/*
 * Descriptions for various models of Vaxes.
 *
 * The table is indexed by cpu type.
 */

#if VAX780
extern struct model_dep	ka780_model;
#define	ka780	&ka780_model
#else
#define	ka780	0
#endif
#if VAX750
extern struct model_dep	ka750_model;
#define	ka750	&ka750_model
#else
#define	ka750	0
#endif
#if VAX730
extern struct model_dep	ka730_model;
#define	ka730	&ka730_model
#else
#define	ka730	0
#endif
#if VAX8600
extern struct model_dep	ka8600_model;
#define	ka8600	&ka8600_model
#else
#define	ka8600	0
#endif
#if VAX820
extern struct model_dep	ka820_model;
#define	ka820	&ka820_model
#else
#define	ka820	0
#endif
#if VAX8800
extern struct model_dep	ka8800_model;
#define	ka8800	&ka8800_model
#else
#define	ka8800	0
#endif
#if VAX630
extern struct model_dep	ka630_model;
#define	ka630	&ka630_model
#else
#define	ka630	0
#endif
#if VAX650
extern struct model_dep	ka650_model;
#define	ka650	&ka650_model
#else
#define	ka650	0
#endif
#if VAX6200
extern struct model_dep	ka6200_model;
#define	ka6200	&ka6200_model
#else
#define ka6200	0
#endif
#if VAX3100
extern struct model_dep	ka42_model;
#define	ka42	&ka42_model
#else
#define ka42	0
#endif


struct model_dep *
	cpu_descriptions[] = {
	0,		/* no CPU type 0 */
	ka780,
	ka750,
	ka730,
	ka8600,
	ka820,		/* 5 */
	ka8800,
	0,		/* no support for uVAX-I */
	ka630,
	0,		/* 9 - missing */
	ka650,
	ka6200,
	0,		/* 12 - missing */
	ka42,
};
