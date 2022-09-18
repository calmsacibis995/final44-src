/* 
 * Mach Operating System
 * Copyright (c) 1990 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dkstat.h,v $
 * Revision 2.2  90/07/03  16:50:08  mrt
 * 	Merged mt Xinu 2.6 MSD changes.
 * 	[90/05/17  18:18:15  mrt]
 * 
 *	Got rid of float dk_mspw as it will not work within kernel
 * 	[90/05/17            emg]
 * 
 */
/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)dkstat.h	7.2 (Berkeley) 5/21/88
 */

/*
 * Instrumentation
 */
#define	CPUSTATES	4

#define	CP_USER		0
#define	CP_NICE		1
#define	CP_SYS		2
#define	CP_IDLE		3

#define	DK_NDRIVE	8

#ifdef KERNEL
long	cp_time[CPUSTATES];
int	dk_ndrive;
int	dk_busy;
long	dk_time[DK_NDRIVE];
long	dk_seek[DK_NDRIVE];
long	dk_xfer[DK_NDRIVE];
long	dk_wds[DK_NDRIVE];
#if	MACH
long	dk_mspw[DK_NDRIVE];
#else	/* MACH */
float	dk_mspw[DK_NDRIVE];
#endif	/* MACH */

long	tk_nin;
long	tk_nout;
#endif
