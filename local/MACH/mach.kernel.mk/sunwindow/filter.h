/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	filter.h,v $
 * Revision 2.4  89/03/09  21:57:31  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:04:54  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*      @(#)filter.h 1.2 86/10/08 SMI      */

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#ifndef	FILTER_H_
#define FILTER_H_

struct filter_rec {
	char           *key_name;
	int             key_num;
	char           *class;
	char          **call;
};

struct filter_rec **parse_filter_table();
/* parse_filter_table(in)
 *	STREAM         *in;
 */

void free_filter_table();
/* free_filter_table(table)
 *	struct filter_rec **table;
 */

#endif
