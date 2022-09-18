/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	ipstructs.h,v $
 * Revision 2.3  89/03/09  22:35:42  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/26  11:04:17  gm0w
 * 	Updated copyright.
 * 	[89/02/23            gm0w]
 * 
 */
/*
** Structures to communicate with the driver and definitions of ioctl
** calls.
*/
#ifdef	KERNEL
#include <sys/ioctl.h>
#else	KERNEL
#include <sys/ioctl.h>
#endif	KERNEL

struct ipPoints 
	{
	short pointcount;
	short *ppoint;
	};
struct iptrack
	{
	short status;
	short control;
	short x, y;
	};
struct  ipsysreg {
	short  cmd;
	short  isr;
	short  psr;
	short  rsr;
	short  dw;
	};
struct  ip_alloc {
	int   resource;		/* display resource to allocate */
	long  unit;		/* resource unit number */
	};
struct  ip_gtu {
	char  cntl0;		/* control reg. 0 */
	char  status;		/* Status reg. */
	short arrayptr;		/* Array pointer */
	char  cntl1;		/* control reg. 1 */
	};

/* The following definitions are used with the ip_alloc structure for
allocating resources in an IP8500 */

#define IP_PROC		0001	/* DVP or GTU resource identifier */
#define IP_DVP		0001	/* unit no.  for DVP */
#define IP_GTU		0020	/* unit no.  for GTU */

#define GTU_1KMEM	0004	/* 1KMEM bit in GTU control-0 reg. */

/* Now we define the ioctl function calls */

#define IPINIT		_IO(i,1)
#define IP_TB_SET	_IOW(i,3,struct iptrack)
#define IP_TB_GET	_IOR(i,4,struct iptrack)
#define IP_TB_SIG	_IOW(i,5,int)
#define IP_SYS_GET	_IOR(i,6,struct ipsysreg)
#define IP_ALL_SYS_GET	_IOR(i,7,struct ipsysreg)
#define IP_POINTS	_IOW(i,10,struct ipPoints)
#define IP_ALLOC	_IOW(i,11,struct ip_alloc)
#define IP_DEALLOC	_IOW(i,12,struct ip_alloc)
#define IP_GO		_IOW(i,13,int)
#define IP_LGTU_ARY	_IOW(i,14,struct ip_gtu)
#define IP_LGTU_C0	_IOW(i,15,struct ip_gtu)
#define IP_LGTU_C1	_IOW(i,16,struct ip_gtu)
#define IP_RGTU		_IOR(i,17,struct ip_gtu)
#define IP_GTU_RESET	_IOW(i,20,struct ip_gtu)
