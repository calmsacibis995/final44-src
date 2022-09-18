/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dzqio.h,v $
 * Revision 2.3  89/03/09  22:34:17  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:02:46  gm0w
 * 	Updated copyright.
 * 	[89/02/23            gm0w]
 * 
 */
#ifdef	KERNEL
#include <ioctl.h>
#else
#include <sys/ioctl.h>
#endif

struct dzqerr {
	int nparity;		/* Number of parity errors */
	int nframe;		/* Number of framing errors */
	int nover_h;		/* Number of hardware overrun errors */
	int nover_s;		/* Number of software overrun errors */
	int maxchars;		/* Largest number of chars historically
				 * held in readbuf since last open */
};

#define DZQTRACECHARS 127
struct dzqtrace {
	char trace[DZQTRACECHARS];
};

#define DZQMODE		_IOW(d, 0, int)
#define		DZQASTEK	0
#define		DZQIRI		1
#define		DZQPUMA		2
#define		DZQPUMACR	3
#define DZQREPORT	_IOR(d, 1, struct dzqerr)
#define DZQTRACE	_IOR(d, 3, struct dzqtrace)
