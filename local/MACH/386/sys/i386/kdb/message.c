/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	message.c,v $
 * Revision 1.4.1.2  90/05/14  13:18:33  rvb
 * 	Bring kdb up to Mach 2.5 production quality:
 * 		Flush dead definitions
 * 	[90/05/10            rvb]
 * 
 * Revision 1.4.1.1  90/01/08  13:27:26  rvb
 * 	Code cleanup -- flush dead code.
 * 	[90/01/08            rvb]
 * 
 * Revision 1.4  89/03/09  20:01:22  rpd
 * 	More cleanup.
 * 
 * Revision 1.3  89/02/27  21:33:52  mrt
 * 	We will minimally sanitize this kdb till something better comes
 * 	along.
 * 	[89/02/27            rvb]
 * 
 */

static	char sccsid[] = "@(#)message.c	4.3 8/11/83";

/*
 *
 *	UNIX debugger
 *
 */

typedef	char		msg[];

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
