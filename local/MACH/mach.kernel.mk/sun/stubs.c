/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	stubs.c,v $
 * Revision 2.5  89/07/11  13:55:35  jjc
 * 	Added gp1_sync().
 * 	[88/07/12            jjc]
 * 
 * Revision 2.4  89/03/09  21:31:15  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  19:31:57  gm0w
 * 	Removed else legs of MACH and CMU conditionals and fixed 
 * 	includes as part of kernel cleanup.
 * 	[89/02/08            jjc]
 * 
 * 26-Jun-87  William Bolosky (bolosky) at Carnegie-Mellon University
 *	Made QUOTA a #if-style option.
 *
 */

#ifndef	lint
static	char sccsid[] = "@(#)stubs.c 1.3 87/01/21 SMI";
#endif

/*
 * Stubs for routines that can't be configured
 * out with binary-only distribution.
 */
#include <quota.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/protosw.h>
#include <sys/domain.h>
#include <net/if.h>
#include <sys/param.h>
#include <sys/quota.h>


#if	!QUOTA
void qtinit() { }
struct dquot *getinoquota() { return ((struct dquot *)0); }
int chkdq() { return (0); }
int chkiq() { return (0); }
void dqrele() { }
int closedq() { return (0); }
#endif	!QUOTA

#define NND	0
#if	NND == 0
struct	ifnet *ndif;
ndintr() { }
nd_chknewaddr() { }
ndopen() { return (ENXIO); }
#endif	NND == 0

#include <ms.h>
#if	NMS == 0
msintr() { }
#endif	NMS == 0

#include <sky.h>
#if	defined(sun2)
#if	NSKY == 0
skysave() { }
skyrestore() { }
#endif	NSKY == 0

#include <pi.h>
#if	NPI == 0
short *piaddr, pilast;
piintr() {}
#endif	NPI == 0
#endif	defined(sun2)

#include <kb.h>
#if	NKB == 0
kbdreset() {}
kbdsettrans() {}
#endif	NKB == 0

#include <win.h>
#if	(NWIN == 0) && defined(sun2)

#if	NBWONE == 0
bw1_rop() {}
bw1_putcolormap() {}
#endif	NBWONE == 0

#if	NCGONE == 0
cg1_rop() {}
cg1_colormap() {}
#endif	NCGONE == 0

#endif	(NWIN == 0) && defined(sun2)

#include <gpone.h>
#if	NGPONE == 0
gp1_kern_sync () {}
gp1_sync () {}			/* for pixrect/cg2_{colormap,rop}.c */
kernsyncrestart () {}
#endif	NGPONE == 0

#include "cgtwo.h"
#if NCGTWO == 0
cgtwo_wait() {}			/* for pixrect/pr_dblbuf.c */
#endif NCGTWO == 0

#if NCGTWO == 0 && NGPONE == 0
cg2_putcolormap() {}		/* for pixrect/pr_dblbuf.c */
#endif NCGTWO == 0 && NGPONE == 0
#include "cgfour.h"

#if NCGFOUR == 0
cg4_putattributes() {}		/* for pixrect/pr_plngrp.c */
#endif NCGFOUR == 0

#include <zs.h>
#if	NZS == 0
zslevel6intr() { panic("level 6 interrupt and no ZS device configured"); }
#endif	NZS == 0

#include <ether.h>
#if	NETHER == 0
int arpioctl() { return (ENOPROTOOPT); }
int localetheraddr() { return (0); }
#endif	NETHER == 0


#ifndef	IPCSEMAPHORE
seminit() {}
semexit() {}
#endif	!IPCSEMAPHORE

#ifndef	IPCMESSAGE
msginit() {}
#endif	!IPCMESSAGE

#ifndef	IPCSHMEM
shmexec() {}
shmfork() {}
shmexit() {}
#endif	!IPCSHMEM

#include <fpa.h>
#if	NFPA == 0
int fpa_fork_context() { return (0); }
fpa_shutdown() {}
fpa_dorestore() {}
fpa_save() {}
fpa_restore() {}
#endif	NFPA == 0
