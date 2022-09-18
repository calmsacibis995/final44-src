/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	svc_auth.h,v $
 * Revision 2.3  89/02/25  19:15:31  gm0w
 * 	Changes for cleanup.
 * 
 * Revision 2.2  89/01/18  01:04:23  jsb
 * 	Include file references.
 * 	[89/01/17  14:34:29  jsb]
 * 
 */
/* @(#)svc_auth.h	1.1 87/06/19 3.2/4.3NFSSRC */
/* @(#)svc_auth.h	1.2 86/10/28 NFSSRC */
/*      @(#)svc_auth.h 1.1 86/09/24 SMI      */

/*
 * svc_auth.h, Service side of rpc authentication.
 * 
 * Copyright (C) 1984, Sun Microsystems, Inc.
 */


/*
 * Server side authenticator
 */
extern enum auth_stat _authenticate();
