/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	label.h,v $
 * Revision 2.2  89/07/12  00:13:00  jjc
 * 	Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*
 *
 * label - the security label structure
 */
#ifndef BLABEL
#define BLABEL

struct binary_label {
	short	sl_level;
	char	sl_categories[16];
	char	sl_unused[14];
};

typedef struct binary_label blabel_t;

#endif	BLABEL
