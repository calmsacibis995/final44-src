/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	sun.h,v $
 * Revision 2.4  89/03/09  21:58:37  rpd
 * 	More cleanup.
 * 
 * Revision 2.3  89/02/25  20:05:56  gm0w
 * 	Added new copyright and #ifndef <filename>_H_ around whole
 * 	file as part of kernel cleanup.
 * 	[89/02/13            jjc]
 * 
 */
/*	@(#)sun.h 1.5 87/01/07 SMI */

/*
 * Copyright (c) 1985 by Sun Microsystems, Inc.
 */

#ifndef	SUN_H_
#define SUN_H_

#if	!(defined(stdio_DEFINED) || defined(FILE))
#include <stdio.h> 
FILE	*popen();
#endif

int atoi();
double atof();
char *ctime();
char *malloc();
char *calloc();
char *strcpy();
char *sprintf();

#ifndef	FALSE
#define FALSE 0
#endif
#ifndef	TRUE
#define TRUE 1
#endif

#ifndef	Bool_DEFINED
typedef enum {False = 0, True = 1} Bool;
#endif

#define strequal(s1, s2) (strcmp(s1, s2) == 0)
#define strdup(str)	 (strcpy(malloc((unsigned) strlen(str) + 1), str))
/*
 * Get some storage and copy a string. Note that str is evaluated twice,
 * so no side effects.
 */
#define ord(e)  ((int) (e))
/*
 * Make an enum usable as an integer
 * Successor or predecessor macros might also be convenient, but
 * much less so.
 */

#define FOREVER for (;;)

#ifndef	MIN
#define MIN(x, y) ( ((x) < (y)) ? (x) : (y) )
#endif

#ifndef	MAX
#define MAX(x, y) ( ((x) > (y)) ? (x) : (y) )
#endif

#ifndef	LINT_CAST
#ifdef	lint
#define LINT_CAST(arg)	(arg ? 0 : 0)
#else
#define LINT_CAST(arg)	(arg)
#endif	lint
#endif	LINT_CAST

#endif
