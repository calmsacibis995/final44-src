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
 * $Log:	mdb_dis.c,v $
 * Revision 2.2  89/02/25  20:25:19  gm0w
 * 	Changes for cleanup.
 * 
 */
/*
 *	File:	vax/mdb_dis.c	--	interface to disassembler
 *	Author:	Robert V. Baron
 *
 *	Copyright (C) 1987, Robert V. Baron
 *
 *	Kernel debugger.
 */

#include <mdb/mdb.h>

extern	mpr_address_string();
extern	int dis7xx_init();
extern	ucharp dis7xx();

static int inited = 0;
static struct dbg_state *hss;
static unsigned char valuchar(addr){ return VALuchar(addr, hss);}
static ucharp number_string_hss(addr){ mpr_number_string(addr, hss); return hss->address_string;}

	/*
	 * cnt == 0 is a special hack for the stack print stuff.
	 * It prints one entry but does not emit the trailing nl.
	 */
ucharp
mdb_dis(pt, cnt, dp)
ucharp pt;
int cnt;
register struct dbg_state *dp;
{
register int count = cnt;
ucharp ins;
long len;

	if (!inited++) {
		hss = dp;
		dis7xx_init(valuchar, number_string_hss);
	}

	do {

		if (mdb_entryaddress(pt, dp) && !VALuchar(pt, dp))
			pt += 2;
		mpr_address(pt, dp);		/* next char goes to col 17 */
		dis7xx(pt, &len);
		if (cnt)
			printf("\n");
		pt += len;
	} while (--count > 0);

	return pt;
}
