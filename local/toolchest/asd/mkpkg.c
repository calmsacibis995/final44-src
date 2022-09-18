/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include "asd.h"

main (argc, argv)
	int argc;
	char **argv;
{
	register int i;

	getargs (argc, argv, "vD:", (int (*)) 0);

	pkgstart();
	for (i = optind; i < argc; i++)
		pkgfile (argv[i]);

	i = pkgend();

	return i;
}
