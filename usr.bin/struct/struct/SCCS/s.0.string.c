h28349
s 00000/00000/00114
d D 8.1 93/06/06 16:28:40 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00108
d D 4.2 91/04/16 16:48:24 bostic 2 1
c new copyright; att/bsd/shared
e
s 00110/00000/00000
d D 4.1 83/02/11 15:43:58 rrh 1 0
c date and time created 83/02/11 15:43:58 by rrh
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

#include <stdio.h>
#include "def.h"
#include "1.defs.h"

str_copy(s,ptr,length)	/* copy s at ptr, return length of s */
char *s, *ptr;
int length;
	{int i;
	for (i = 0; i < length; i++)
		{
		ptr[i] = s[i];
		if (ptr[i] == '\0')
			return(i + 1);
		}
	faterr("string too long to be copied at given address:\n",s,"");
	}


find(s,ar,size)
char *s,*ar[];
int size;
	{
	int i;
	for (i=0; i < size; i++)
		{if (str_eq(s, ar[i])) return(i);}
	return(-1);
	}


str_eq(s,t)
char s[],t[];
	{int j;
	for (j = 0; s[j] == t[j]; j++)
		{if (s[j] == '\0') return(1);}
	return(0);
	}


classmatch(c,i)
char c;
int i;
	{switch(i)
		{case _digit:
			if ('0' <= c && c <= '9')  return(1);
			else return(0);

		case _letter:
			if ( ('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
				return(1);
			else return(0);

		case _diglet:  return(classmatch(c,_digit)||classmatch(c,_letter) );

		case _arith:
			if (050 <= c && c<= 057)  return(1);
			else return(0);
		case _nl:
			return(c=='\n');
		case _other:
			return(1);
		}
	}


copychars(cbeg,target,n)		/* copy n chars from cbeg to target */
char *cbeg, *target;
int n;
	{
	int i;
	for (i = 0; i < n; i++)
		target[i] = cbeg[i];
	}



copycs(cbeg,target,n)			/* copy n chars from cbeg to target, add '\0' */
char *cbeg, *target;
int n;
	{
	copychars(cbeg,target,n);
	target[n] = '\0';
	}


slength(s)			/* return number of chars in s, not counting '\0' */
char *s;
	{
	int i;
	if (!s) return(-1);
	for (i = 0; s[i] != '\0'; i++);
	return(i);
	}


concat(x,y)			/* allocate space, return xy */
char *x, *y;
	{
	char *temp;
	int i,j;
	i = slength(x);
	j = slength(y);
	temp = galloc(i + j + 1);
	sprintf(temp,"%s",x);
	sprintf(&temp[i],"%s",y);
	return(temp);
	}
E 1
