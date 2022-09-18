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
 * $Log:	pcbheadsw.h,v $
 * Revision 2.3  89/03/09  20:45:47  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  19:00:49  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 */
/*
 * pcbheadsw.h
 */


struct pcbheadsw {
    short protocol;
    struct inpcb *head;
};

