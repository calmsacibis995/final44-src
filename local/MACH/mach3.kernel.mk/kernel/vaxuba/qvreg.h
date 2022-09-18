/*
 ****************************************************************
 * Mach Operating System
 * Copyright (c) 1986 Carnegie-Mellon University
 *  
 * This software was developed by the Mach operating system
 * project at Carnegie-Mellon University's Department of Computer
 * Science. Software contributors as of May 1986 include Mike Accetta, 
 * Robert Baron, William Bolosky, Jonathan Chew, David Golub, 
 * Glenn Marcy, Richard Rashid, Avie Tevanian and Michael Young. 
 * 
 * Some software in these files are derived from sources other
 * than CMU.  Previous copyright and other source notices are
 * preserved below and permission to use such software is
 * dependent on licenses from those institutions.
 * 
 * Permission to use the CMU portion of this software for 
 * any non-commercial research and development purpose is
 * granted with the understanding that appropriate credit
 * will be given to CMU, the Mach project and its authors.
 * The Mach project would appreciate being notified of any
 * modifications and of redistribution of this software so that
 * bug fixes and enhancements may be distributed to users.
 *
 * All other rights are reserved to Carnegie-Mellon University.
 ****************************************************************
 */
/*
 * HISTORY
 * $Log:	qvreg.h,v $
 * Revision 2.2  91/05/08  13:33:19  dbg
 * 	Added volatile declarations.
 * 	[91/04/19            dbg]
 * 
 */

/* @(#)qvreg.h	1.2 (ULTRIX) 1/23/85 */

#ifndef	_VAXUBA_QVREG_H_
#define	_VAXUBA_QVREG_H_

#ifndef	__STDC__
/* undefine 'volatile' for stale C compilers */
#ifndef	volatile
#define	volatile
#endif
#endif

/*
 * QVSS definitions.
 */
struct qvdevice {
  volatile  unsigned short  qv_csr;	/* csr				*/
  volatile  unsigned short  qv_xcur;	/* cursor x-position		*/
  volatile  unsigned short  qv_mouse;	/* mouse position		*/
	    unsigned short  qv_spare1;
  volatile  unsigned short  qv_crtaddr;	/* crt controller address reg	*/
  volatile  unsigned short  qv_crtdata;	/* crt controller data register	*/
  volatile  unsigned short  qv_intdata;	/* int controller data register	*/
  volatile  unsigned short  qv_intcsr;	/* int controller command/status*/
	    unsigned short  qv_dummy[8];
  volatile  unsigned short  qv_uartmode;/* uart mode			*/
  volatile  unsigned short  qv_uartstatus;
					/* uart status			*/
  volatile  unsigned short  qv_uartcmd;	/* uart command			*/
  volatile  unsigned short  qv_uartdata;/* uart data			*/
	    unsigned short  qv_spare2;
  volatile  unsigned short  qv_uartintstatus;
					/* uart interrupt status	*/
};


/*
 * csr bit definitions
 */

#define	QV_19INCH	0x1
#define QV_VIDEO_ENA	0x4
#define QV_CUR_MODE	0x8
#define QV_VIDEO_LP	0x10
#define QV_TEST_BIT	0x20
#define QV_INT_ENABLE	0x40
#define QV_CURSOR_ON	0x80
#define QV_MOUSE_ANY	0x700
#define QV_MOUSE_A	0x100
#define QV_MOUSE_B	0x200
#define QV_MOUSE_C	0x400
#define QV_MEM_BANK	0x7800

/*
 * The following tables are used to translate LK201 key strokes
 * into ascii characters. The tables also support the special
 * function keys.
 */

#define SHIFT	0xae
#define LOCK	0xb0
#define REPEAT	0xb4
#define CNTRL	0xaf
#define ALLUP	0xb3

#endif	/* _VAXUBA_QVREG_H_ */
