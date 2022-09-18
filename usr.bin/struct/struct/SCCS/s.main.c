h51032
s 00000/00000/00077
d D 8.1 93/06/06 16:30:10 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00071
d D 4.2 91/04/16 16:48:55 bostic 2 1
c new copyright; att/bsd/shared
e
s 00073/00000/00000
d D 4.1 83/02/11 15:45:10 rrh 1 0
c date and time created 83/02/11 15:45:10 by rrh
e
u
U
t
T
I 2
/*-
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include <signal.h>
#include <stdio.h>
#include "1.defs.h"
#include "def.h"


char (*input)(), (*unput)();
FILE *outfd	= stdout;



main(argc,argv)
int argc;
char *argv[];
	{
	int anyoutput;
	int dexit();
	char *getargs();
	char input1(), unput1(), input2(), unput2();
	anyoutput = FALSE;
	getargs(argc,argv);
	if (debug == 2) debfd = stderr;
	else if (debug)
		debfd = fopen("debug1","w");

	if (signal(SIGINT, SIG_IGN) !=SIG_IGN)
		signal(SIGINT,dexit);
	prog_init();

	for (;;)
		{
		++routnum;
		routerr = 0;

		input = input1;
		unput = unput1;
		if (!mkgraph()) break;
		if (debug) prgraph();
		if (routerr) continue;

		if (progress)fprintf(stderr,"build:\n");
		build();
		if (debug) prtree();
		if (routerr) continue;

		if (progress)fprintf(stderr,"structure:\n");
		structure();
		if (debug) prtree();
		if (routerr) continue;
		input = input2;
		unput = unput2;

		if (progress)fprintf(stderr,"output:\n");
		output();
		if (routerr) continue;
		anyoutput = TRUE;
		freegraf();
		}
	if (anyoutput)
		exit(0);
	else
		exit(1);
	}


dexit()
	{
	exit(1);
	}
E 1
