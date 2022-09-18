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
 * $Log:	cpu_data.h,v $
 * Revision 2.5  91/06/19  12:00:32  rvb
 * 	Support for VaxStation 3100: new processor number
 * 	[91/06/04            rvb]
 * 
 * Revision 2.4  91/05/14  17:42:19  mrt
 * 	Correcting copyright
 * 
 * Revision 2.3  91/05/08  13:15:25  dbg
 * 	Remove cast from SYSTYPE to use in assembler code.
 * 	[91/04/12            dbg]
 * 
 * Revision 2.2  90/01/11  11:45:21  dbg
 * 	Add m_startcpu.
 * 	[89/12/19            dbg]
 * 
 * Revision 2.1  89/08/03  16:23:12  rwd
 * Created.
 * 
 * 23-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */

/*
 * VAX model-dependent information.
 */

/*
 * CPU type codes.  These are NOT necessarily the same as the number
 * obtained from the cpu SID register - some VAXen have the same SID.
 */

/*
 *	Need to finish processor type table		??rvb??
 */
#define SYSTYPE		(0x20040004)
#define SYSTYPE_PTR	((int *) SYSTYPE)

#define	VAX_780		1
#define	VAX_750		2
#define	VAX_730		3
#define VAX_8600	4
#define	VAX_820		5
#define VAX_8800	6
#define	VAX_1		7
#define	VAX_630		8
#define VAX_650		10
#define	VAX_6200	11
#define	VAX_3100	13

#define	VAX_MAX		13

#ifndef	ASSEMBLER
/*
 * Vector for model-dependent routines.
 */
struct model_dep {
	int	(*m_setup)();		/* setup needed before we can
					   talk to console */
	int	(*m_init)();		/* Initialize memory, find CPUS,
					   print CPU id */
	int	(*m_configure)();	/* configure devices */
	int	(*m_slave_config)();	/* configure slave CPU */
	int	(*m_reboot_ok)();	/* turn off reboot/restart inhibit
					   flags */
	int	(*m_crd)();		/* corrected read-data error */
	int	(*m_mchk)();		/* machine check */
	int	(*m_clear_mchk)();	/* clear machine check condition */
	int	(*m_haltcpu)();		/* halt or reboot CPU */
	int	(*m_interrupt)();	/* interrupt processor */
	int	m_cpuspeed;		/* relative speed of CPU (730 == 1) */
	int	(*m_startcpu)();	/* start CPU */
};
typedef struct model_dep *	cpu_model_t;

extern cpu_model_t	cpu_descriptions[];	/* table of all CPU types */
extern cpu_model_t	cpu_model;		/* entry for this machine */
extern int		cpu;			/* this cpu */

#endif	ASSEMBLER
