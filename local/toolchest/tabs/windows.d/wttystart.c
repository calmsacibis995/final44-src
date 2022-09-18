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
#include "windows.h"

/*
 *
 *	A ttystart for windows
 *
 */

wttystart ()
{
	extern char *getenv();
	extern char *sbrk();
	extern int die();
	extern int die_gracefully();
	extern char    ttobuf[BUFSIZ];
	register int index;
	register unsigned int *kmap_ptr;
	register char   *tp;

	setbuf (stdout, ttobuf);

	cp_start ();

	uncook ();

	tp = (char *) getenv ("TERM");
	if (tp == NULL)
	{
		cook ();
		tp =  "The env. variable TERM is not defined.\n";
		write (1, tp, strlen (tp));
		exit (1);
	}
	else
		wsttype (tp);

 	signal (SIGBUS, die);
 	signal (SIGSEGV, die);
 	signal (SIGINT, die_gracefully);
 	signal (SIGQUIT, die_gracefully);
}

die_gracefully ()
{
	die (0);
}
