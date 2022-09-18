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
 * $Log:	message.c,v $
 * Revision 2.5  89/03/09  22:17:30  rpd
 * 	More cleanup.
 * 
 * Revision 2.4  89/02/27  21:44:30  mrt
 * 	Make sccsid a comment.
 * 	[89/02/27            rvb]
 * 
 * Revision 2.3  89/02/25  20:22:44  gm0w
 * 	Changes for cleanup.
 * 
 *  3-Mar-88  Michael Young (mwyoung) at Carnegie-Mellon University.
 *	Delinted for kernel use.
 *
 */

/*
 *
 *	UNIX debugger
 *
 */

/* static	char sccsid[] = "@(#)message.c	4.3 8/11/83"; */

#include <vax/kdb/mac.h>
#include <vax/kdb/mode.h>

msg		BADMOD	=  "bad modifier";
msg		BADCOM	=  "bad command";
msg		BADSYM	=  "symbol not found";
msg		BADLOC	=  "automatic variable not found";
msg		NOCFN	=  "c routine not found";
msg		NOMATCH	=  "cannot locate value";
msg		NOBKPT	=  "no breakpoint set";
msg		BADKET	=  "unexpected ')'";
msg		NOADR	=  "address expected";
msg		BADVAR	=  "bad variable";
msg		EXBKPT	=  "too many breakpoints";
msg		ADWRAP	=  "address wrap around";
msg		BADEQ	=  "unexpected `='";
msg		BADSYN	=  "syntax error";
msg		NOEOR	=  "newline expected";
msg		SZBKPT	=  "bkpt: command too long";
