/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	mode.h,v $
 * Revision 1.3  89/02/27  21:34:05  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 */

/*	mode.h	4.2	81/05/14	*/

#include "machine.h"
/*
 * sdb/adb - common definitions for old srb style code
 */

#define MAXCOM	64
#define MAXARG	32
#define LINSIZ	512

typedef	short	INT;
typedef	int		VOID;
typedef	char		BOOL;
typedef	char		*string_t;
typedef	char		msg[];
typedef	struct map	map;
typedef	map		*map_t;
typedef	struct bkpt	bkpt;
typedef	bkpt		*bkpt_t;


/* file address maps */
struct map {
	long	b1;
	long	e1;
	long	f1;
	long	b2;
	long	e2;
	long	f2;
	INT	ufd;
};

struct bkpt {
	long	loc;
	long	ins;
	INT	count;
	INT	initcnt;
	INT	flag;
	char	comm[MAXCOM];
	bkpt	*nxtbkpt;
};

typedef	struct reglist	REGLIST;
typedef	REGLIST		*REGPTR;
struct reglist {
	string_t	rname;
	INT	roffs;
	int	*rkern;
};
