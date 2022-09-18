h58707
s 00031/00000/00000
d D 1.1 88/07/21 17:34:31 marc 1 0
c date and time created 88/07/21 17:34:31 by marc
e
u
U
t
T
I 1
/*

 *      Copyright (c) 1984, 1985, 1986 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/* %W% */

/*
 *	UNIX shell
 *
 *	S. R. Bourne
 *	AT&T Bell Laboratories
 *
 */
#ifdef IH
#define TIMEOUT		7000	/* seconds elapsing before termination */
#else
#define TIMEOUT		0	/* seconds elapsing before termination */
#endif
#define TGRACE		60	/* grace period before termination */
				/* The time_warn message contains this number */
extern long	timeout;
extern MSG	timed_out;
extern MSG	time_warn;
E 1
