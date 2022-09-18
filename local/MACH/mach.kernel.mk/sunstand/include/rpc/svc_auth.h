/*
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	svc_auth.h,v $
 * Revision 2.2  89/07/11  23:27:50  jjc
 * 	     Picked up from SunOS 4.0.
 * 	[89/07/03            jjc]
 * 
 */
/*      @(#)svc_auth.h 1.7 88/02/08 SMI      */

/*
 * svc_auth.h, Service side of rpc authentication.
 * 
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */


/*
 * Server side authenticator
 */
extern enum auth_stat _authenticate();
