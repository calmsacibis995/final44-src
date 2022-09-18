h32306
s 00006/00002/00150
d D 4.3 91/04/18 16:33:11 bostic 3 2
c new copyright; att/bsd/shared
e
s 00003/00001/00149
d D 4.2 89/05/11 10:05:01 bostic 2 1
c file reorg, pathnames.h, paths.h
e
s 00150/00000/00000
d D 4.1 83/05/06 23:50:08 tut 1 0
c date and time created 83/05/06 23:50:08 by tut
e
u
U
t
T
I 3
/*-
 * %sccs.include.proprietary.c%
 */

E 3
I 1
#ifndef lint
D 3
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 3
I 3
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 3

#include <stdio.h>
I 2
#include "pathnames.h"

E 2
#define MAXLINE 750

int nh 500;
int saw[6000];
D 2
char *comname "/usr/lib/eign";
E 2
I 2
char *comname = _PATH_EIGN;
E 2

main (argc,argv)
char *argv[];
{

	int i, z;
	char *name;

	FILE *f;

	while (argc>1 && argv[1][0] == '-')
	{
		switch(argv[1][1])
		{
		case 'h':
			nh = atoi(argv[1]+2); 
			break;
		}
		argc--; 
		argv++;
	}
	if (argc<=1)
		dofile(stdin, "");
	else
		for(i=1; i<argc; i++)
		{
			f = fopen(name=argv[i], "r");
			if (f==NULL)
				err("No file %s",name);
			else
				dofile(f, name);
		}
	for(z=i=0; i<nh; i++)
	{
		if (saw[i]) z++;
	}
	printf("hashes %d used %d\n",nh,z);
}

dofile(f, name)
FILE *f;
char *name;
{
	/* read file f & spit out keys & ptrs */
	char line[MAXLINE], *s;
	char key[20], *p;
	int k 0;
	int c, lim;
	int alph 0;
	int used 0;
	long lp 0;

	while (fgets(line, MAXLINE, f))
	{
		k++;
		used=alph=0;
		lim = strlen(line);
		p = key;
		for(s=line; c= *s; s++)
		{
			if (isalpha(c) || isdigit(c))
			{
				if (alph++ < 6)
					*p++ = c;
			}
			else
			{
				*p = 0;
				if (outkey(p=key))
				{
					tkey(key,k);
					used=1;
				}
				alph=0;
			}
		}
		lp += lim;
	}
}

outkey( ky)
char *ky;
{
	int n;
	n = strlen(ky);
	if (n<3) return(0);
	if (isdigit(ky[0]))
		if (ky[0] != '1' || ky[1] != '9' || n!= 4) return(0);
	return(1);
}

hash (s)
char *s;
{
	int c, n, q;
	for(q=n=0; c= *s; s++)
		n += (c*n + c << (n%4));
	return(n);
}

err (s, a)
char *s;
{
	fprintf(stderr, "Error: ");
	fprintf(stderr, s, a);
	putc('\n', stderr);
}

prefix(t, s)
char *t, *s;
{
	int c, d;
	while ( (c= *t++) == *s++)
		if (c==0) return(1);
	return(c==0 ? 1: 0);
}

mindex(s, c)
char *s;
{
	register char *p;
	for( p=s; *p; p++)
		if (*p ==c)
			return(p);
	return(0);
}

tkey(s,nw)
char *s;
{
	int x;
	x = abs(hash(s)) % nh;
	/* if (saw[x]) printf("%d %d\n", x, nw); */
	saw[x]= nw;
}

abs(n)
{
	return(n>0 ? n : -n);
}
E 1
