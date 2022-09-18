/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	dbx_sundev.c,v $
 * Revision 2.3  89/03/09  21:40:55  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:50:35  gm0w
 * 	Changes for cleanup.
 * 
 */
#ifndef	lint
static	char sccsid[] = "@(#)dbx_sundev.c 1.1 86/02/03 Copyr 1985 Sun Micro";
#endif

/*
 * This file is optionally brought in by including a
 * "psuedo-device dbx" line in the config file.  It is
 * compiled using the "-g" flag to generate structure
 * information which is used by dbx with the -k flag.
 */

#include <sys/param.h>
#include <sys/buf.h>
#include <sys/time.h>

#include <sundev/mbvar.h>
#include <sundev/vuid_event.h>
#include <sundev/dmctl.h>

#include <ar.h>
#if	NAR > 0
#include <sundev/arreg.h>
#endif	NAR > 0

#include <bwtwo.h>
#if	NBWTWO > 0
#include <sundev/bw2reg.h>
#endif	NBWTWO > 0

#include <ip.h>
#if	NIP > 0
#include <sundev/ipreg.h>
#endif	NIP > 0

#include <kb.h>
#if	NKB > 0
#include <sundev/kbd.h>
#include <sundev/kbdreg.h>
#include <sundev/kbio.h>
#endif	NKB > 0

#include <ms.h>
#if	NMS > 0
#include <sundev/msreg.h>
#endif	NMS > 0

#include <mti.h>
#if	NMTI > 0
#include <sundev/mtireg.h>
#endif	NMTI > 0

#include <sky.h>
#if	NSKY > 0
#include <sundev/skyreg.h>
#endif	NSKY > 0

#include <sc.h>
#include <si.h>
#if	NSI > 0 || NSC > 0
#include <sundev/sireg.h>	/* XXX - scsi.h shouldn't require sireg.h */
#include <sundev/screg.h>	/* XXX - scsi.h shouldn't require screg.h */
#include <sundev/scsi.h>
#endif	NSC > 0 || NSC > 0

#include <st.h>
#if	NST > 0
#include <sundev/streg.h>
#endif	NST > 0

#include <mt.h>
#if	NMT > 0
#include <sundev/tmreg.h>
#endif	NMT > 0

#include <tod.h>
#if	NTOD > 0
#include <sundev/todreg.h>
#endif	NTOD > 0

#include <vp.h>
#if	NVP > 0
#include <sundev/vpreg.h>
#endif	NVP > 0

#include <vpc.h>
#if	NVPC > 0
#include <sundev/vpcreg.h>
#endif	NVPC > 0

#include <xy.h>
#include <xt.h>
#if	NXY > 0 || NXT > 0
#include <sundev/xycreg.h>
#endif	NXY > 0 || NXT > 0
#if	NXT > 0
#include <sundev/xtreg.h>
#endif	NXT > 0
#if	NXY > 0
#include <sundev/xyreg.h>
#endif	NXY > 0

#include <zs.h>
#if	NZS > 0
#include <sundev/zscom.h>
#include <sundev/zsreg.h>
#include <sundev/zsvar.h>
#endif	NZS > 0
