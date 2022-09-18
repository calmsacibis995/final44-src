h03890
s 00062/00000/00000
d D 1.1 88/07/21 17:35:40 marc 1 0
c date and time created 88/07/21 17:35:40 by marc
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
 *  gsort - sort an array of strings
 *
 *   David Korn
 *   AT&T Bell Laboratories
 *   Room 5D-112
 *   Murray Hill, N. J. 07974
 *   Tel. x7975
 *
 *  Derived from Bourne Shell
 */

extern int strcmp();

/*
 * sort the array of strings argv with n elements
 */

void	gsort(argv,n)
char *argv[];
{
	register int 	i, j, m;
	int  k;
	for(j=1; j<=n; j*=2);
	for(m=2*j-1; m/=2;)
	{
		k=n-m;
		for(j=0; j<k; j++)
		{
			for(i=j; i>=0; i-=m)
			{
				register char **ap;
				ap = &argv[i];
				if(strcmp(ap[m],ap[0])>0)
					break;
				else
				{
					char *s;
					s=ap[m];
					ap[m]=ap[0];
					ap[0]=s;
				}
			}
		}
	}
}

E 1
