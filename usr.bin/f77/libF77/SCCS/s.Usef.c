h27465
s 00014/00005/00036
d D 1.5 91/04/12 14:58:31 bostic 6 5
c new copyright; att/bsd/shared
e
s 00011/00007/00030
d D 1.4 90/02/25 18:57:31 donn 5 3
c Don't use '-f' on a system where the C compiler doesn't do automatic
c float to double promotion in expressions.
e
s 00011/00007/00030
d R 1.4 90/02/25 18:55:59 donn 4 3
c don't use 'cc -f' with compilers that don't do automatic double to
c float promotion.
e
s 00001/00002/00036
d D 1.3 87/09/14 14:57:59 bostic 3 2
c check first element in list; bug report 4.3BSD/usr.lib/58
e
s 00001/00001/00037
d D 1.2 85/08/01 17:28:55 bloom 2 1
c Fix sccsid line
e
s 00038/00000/00000
d D 1.1 85/07/30 16:44:08 jerry 1 0
c date and time created 85/07/30 16:44:08 by jerry
e
u
U
t
T
I 1
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 6
 *
D 2
 *	%W%	%G%	*/
E 2
I 2
D 6
 *	%W%	%G%
E 6
I 6
 * %sccs.include.proprietary.c%
E 6
E 2
 */
I 6

#ifndef lint
char copyright[] =
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 6

/*		returns '-f' if need to use -f to bypass C bug		*/

static char *needs_f[] = {
	"besj0_", "besj1_", "besjn_", "besy0_", "besy1_", "besyn_",
	"c_abs", "erf_", "erfc_", "r_abs", "r_acos", "r_asin",
	"r_atan", "r_atn2", "r_cos", "r_cosh", "r_exp", "r_imag",
	"r_int", "r_lg10", "r_log", "r_sign", "r_sin",
	"r_sinh", "r_sqrt", "r_tan", "r_tanh", "rand_", "random_",
	0,
	};

main(argc, argv)
int argc;
char **argv;
{
	char **ptr;
I 5
	float f;
E 5

D 5
	argv++;
	ptr = needs_f;
	while( *ptr != 0 ) {
D 3
		ptr++;
		if( strcmp( *ptr, *argv ) == 0 )
E 3
I 3
		if( strcmp( *ptr++, *argv ) == 0 )
E 3
		{
			printf("-f");
			exit(0);
E 5
I 5
	if (sizeof (f + f) != sizeof f)
	{
		argv++;
		ptr = needs_f;
		while( *ptr != 0 ) {
			if( strcmp( *ptr++, *argv ) == 0 )
			{
				printf("-f");
				exit(0);
			}
E 5
		}
	}
	printf(" ");
	exit(0);
}
E 1
