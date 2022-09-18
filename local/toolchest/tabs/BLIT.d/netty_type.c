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
#include <setjmp.h>

/*
 *	Determine if we are running netty
 *
 *	Remove the system() calls if you don't care about echo
 *
 */

#define TRUE	1
#define FALSE	0
#define BUF	64

extern int catch_alarm ();

jmp_buf time_out;

main ()
{
	char buffer[BUF];

	system ("stty raw -echo");		/* no echo the slow way */

	signal (SIGALRM, catch_alarm);

	write (1, "\033?", 2);

	if (setjmp (time_out) == FALSE)
	{
		alarm (1);

		fgets (buffer, BUF, stdin);
	}

	alarm (0);

	system ("stty -raw echo");		/* echo the slow way */

	if (strncmp (buffer, "netty", 5) == 0)
		printf ("yes\n");
	else
		printf ("no\n");

}

catch_alarm ()
{
	longjmp (time_out, TRUE);
}
