/*
 * $XConsortium: skyScrInit.c,v 1.2 91/07/16 13:17:01 jap Exp $
 *
 * Copyright IBM Corporation 1987,1988,1989,1990,1991
 *
 * All Rights Reserved
 *
 * License to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notice appear in all copies and that
 * both that copyright notice and this permission notice appear in
 * supporting documentation, and that the name of IBM not be
 * used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.
 *
 * IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 * ALL IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS, AND 
 * NONINFRINGEMENT OF THIRD PARTY RIGHTS, IN NO EVENT SHALL
 * IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
 * ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
 * SOFTWARE.
 *
*/

/*
 * skyScrInit.c - initialize display
 */

#include <sys/types.h>
#include <sys/hft.h>
#include <sys/entdisp.h>
#include <sys/rcm_win.h>
#include <sys/aixgsc.h>

#include "X.h"
#include "screenint.h"
#include "scrnintstr.h"
#include "pixmapstr.h"
#include "cursorstr.h"
#include "ibmScreen.h"
#include "ibmTrace.h"

#include "skyHdwr.h"
#include "skyReg.h"


#define DEVMAX       6
unsigned long   SKYWAY_OFFSET[DEVMAX] ;
unsigned long   SKYWAY_VRAM_START[DEVMAX] ;
unsigned long   IOREG[DEVMAX] ;
unsigned long   COPREG[DEVMAX] ;
unsigned long   SKYWAY_DMA0[DEVMAX] ;
unsigned long   SKYWAY_DMA1[DEVMAX] ;
unsigned long   SKYWAY_DMA2[DEVMAX] ;
unsigned long   SKYWAY_DMA3[DEVMAX] ;
unsigned long   SKYWAY_TILEOFFSET[DEVMAX] ;

unsigned int skyHandle ;
pointer      pSkywayFrame ;


int skyScreenInit(index)
int index ;
{
	struct  sky_map skyRegMap ;
	make_gp skyHdwrInfo ;
	unsigned long segAddr ;

	TRACE(("skyScreenInit entered\n"));

	if (ioctl(ibmScreenFD(index), HFHANDLE, &skyHandle) < 0 )
	{
	        TRACE(("get skyHandle failed"));
	        return -1 ;
	}

	skyHdwrInfo.pData = (genericPtr) &skyRegMap ;
	skyHdwrInfo.length = sizeof(skyRegMap);

	/* get hardware info */

	if (aixgsc (skyHandle, MAKE_GP, &skyHdwrInfo))
	{
	        TRACE(("aixgsc MAKE_GP failed\n"));
	        return -1 ;
	}

	segAddr = (unsigned long *) skyHdwrInfo.segment ;
	SKYWAY_OFFSET[index] = segAddr;
	SKYWAY_VRAM_START[index] = segAddr | skyRegMap.vr_addr ;
	IOREG[index] = segAddr | skyRegMap.io_addr   ;
	COPREG[index] = segAddr | skyRegMap.cp_addr  ;
	pSkywayFrame = SKYWAY_VRAM_START[index] ;

	TRACE (("skyScreenInit: SEGADDR is %x\n", segAddr));
	TRACE (("skyScreenInit: VRAM_OFFSET is %x\n", SKYWAY_OFFSET[index]));
	TRACE (("skyScreenInit: VRAM_START  is %x\n", SKYWAY_VRAM_START[index]));
	TRACE (("skyScreenInit: IOREG  is %x\n", IOREG[index]));
	TRACE (("skyScreenInit: COPREG is %x\n", COPREG[index]));
	TRACE (("skyScreenInit: FRAMEADDR %x\n", pSkywayFrame));

	return 0 ;
}
