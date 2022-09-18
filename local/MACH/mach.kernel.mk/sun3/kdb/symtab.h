/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	symtab.h,v $
 * Revision 2.3  89/02/25  19:43:15  gm0w
 * 	Changes for cleanup.
 * 
 */
/*	@(#)symtab.h 1.1 86/02/03 SMI	*/


struct asym {
	char	*s_name;
	int	s_type;
	struct	afield *s_f;
	int	s_fcnt, s_falloc;
	int	s_value;
	int	s_fileloc;
	struct	asym *s_link;
} **globals;
int	nglobals, NGLOBALS;

struct afield {
	char	*f_name;
	int	f_type;
	int	f_offset;
	struct	afield *f_link;
} *fields;
int	nfields, NFIELDS;

struct linepc {
	int	l_fileloc;
	int	l_pc;
} *linepc, *linepclast, *pcline;
int	nlinepc, NLINEPC;

/* need a string hash table here */

struct	asym *lookup(), *cursym;
struct	afield *fieldlookup(), *globalfield();
