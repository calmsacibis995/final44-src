h25425
s 00006/00002/00064
d D 4.4 91/04/18 18:17:36 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00064
d D 4.3 89/08/09 10:49:57 mckusick 3 2
c spelling of weird (4.3BSD-tahoe/usr.bin/25)
e
s 00003/00001/00063
d D 4.2 83/08/11 21:14:42 sam 2 1
c standardize sccs keyword lines
e
s 00064/00000/00000
d D 4.1 83/02/12 19:06:40 shannon 1 0
c date and time created 83/02/12 19:06:40 by shannon
e
u
U
t
T
I 4
/*-
 * %sccs.include.proprietary.c%
 */

E 4
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
#ifndef lint
D 4
static char sccsid[] = "%W% %G%";
#endif
E 4
I 4
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 4
E 2

 /* t9.c: write lines for tables over 200 lines */
# include "t..c"
static useln;
yetmore()
{
for(useln=0; useln<MAXLIN && table[useln]==0; useln++);
if (useln>=MAXLIN)
D 3
	error("Wierd.  No data in table.");
E 3
I 3
	error("Weird.  No data in table.");
E 3
table[0]=table[useln];
for(useln=nlin-1; useln>=0 && (fullbot[useln] || instead[useln]); useln--);
if (useln<0)
D 3
	error("Wierd.  No real lines in table.");
E 3
I 3
	error("Weird.  No real lines in table.");
E 3
domore(leftover);
while (gets1(cstore=cspace) && domore(cstore))
	;
last =cstore;
return;
}
domore(dataln)
	char *dataln;
{
	int icol, ch;
if (prefix(".TE", dataln))
	return(0);
if (dataln[0] == '.' && !isdigit(dataln[1]))
	{
	puts(dataln);
	return(1);
	}
instead[0]=fullbot[0]=0;
if (dataln[1]==0)
switch(dataln[0])
	{
	case '_': fullbot[0]= '-'; putline(useln,0);  return(1);
	case '=': fullbot[0]= '='; putline(useln, 0); return(1);
	}
for (icol = 0; icol <ncol; icol++)
	{
	table[0][icol].col = dataln;
	table[0][icol].rcol=0;
	for(; (ch= *dataln) != '\0' && ch != tab; dataln++)
			;
	*dataln++ = '\0';
	switch(ctype(useln,icol))
		{
		case 'n':
			table[0][icol].rcol = maknew(table[0][icol].col);
			break;
		case 'a':
			table[0][icol].rcol = table[0][icol].col;
			table[0][icol].col= "";
			break;
		}
	while (ctype(useln,icol+1)== 's') /* spanning */
		table[0][++icol].col = "";
	if (ch == '\0') break;
	}
while (++icol <ncol)
	table[0][icol].col = "";
putline(useln,0);
return(1);
}
E 1
