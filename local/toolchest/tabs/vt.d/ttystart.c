/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include <signal.h>
#include "vt.h"

ttystart ()
{
	extern char *getenv();
	extern int die ();
	extern int die_gracefully ();
	register char   *tp;

	cp_start ();

	setbuf (stdout, ttobuf);

	uncook ();

	tp = (char *) getenv ("TERM");
	if (tp == NULL)
	{
		cook ();
		tp =  "The env. variable TERM is not defined.\n";
		write (1, tp, strlen (tp));
		die ();
	}
	else
		sttype (tp);

 	signal (SIGBUS, die);
 	signal (SIGSEGV, die);
 	signal (SIGINT, die_gracefully);
 	signal (SIGQUIT, die_gracefully);
}

die_gracefully ()
{
	die (0);
}
