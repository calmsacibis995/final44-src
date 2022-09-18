h50120
s 00002/00002/00115
d D 1.5 93/07/27 09:16:23 bostic 5 4
c checkpoint; Mike Karels left this checked out.
e
s 00000/00001/00117
d D 1.4 86/11/13 15:43:02 jaap 4 3
c Fixed lf again (Table too wide gave wrong name)
e
s 00003/00002/00115
d D 1.3 86/11/10 16:10:15 jaap 3 2
c Fixed .lf request (I hope)
e
s 00005/00004/00112
d D 1.2 85/10/02 14:37:16 jaap 2 1
c Removed a lot of commented out debug code, takes now -d argument
c for debug output. some tidy up.
e
s 00116/00000/00000
d D 1.1 85/10/01 18:09:03 jaap 1 0
c date and time created 85/10/01 18:09:03 by jaap
e
u
U
t
T
I 1
#ifndef lint
D 5
static char sccsid[] = "%W% (CWI) %E%";
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
E 5
#endif lint


D 2
 /* te.c: error message control, input line count */
E 2
I 2
/*
 * error message control
 * input
 * line count
 */
E 2

#include "defs.h"
#include "ext.h"

error(s)
char   *s;
{
	fprintf(stderr, "\n%s: line %d: %s\n", ifile, iline, s);
	fprintf(stderr, "tbl quits\n");
	exit(1);
}

/*
 * get a line from the input
 */
char *
gets1(s)
char   *s;
{
	char   *p;
	register int     nbl = 0;

next:
	iline++;
	p = fgets(s, BUFSIZ, tabin);
	/*
	 * Undocumented feature: tables can be arbitrarily split in
	 * various files
	 */
	while(p == NULL){
		if(swapin() == 0)
			return(0);
		p = fgets(s, BUFSIZ, tabin);
	}

	/*
	 * Clumsy support for .lf request (jna)
	 */
	if(p[0] == '.' && p[1] == 'l' && p[2] == 'f'){
D 3
		sscanf(p+3, "%d", &iline);
		printf(".lf %d %s\n", iline, ifile);
E 3
I 3
D 4
		char oldname[BUFSIZ];
E 4
		sscanf(p+3, "%d %s", &iline, oldname);
		printf(".lf %d %s\n", iline, strlen(oldname) ? oldname: ifile);
E 3
		goto next;
	}

	while(*s)
	
		s++;
	s--;

	/*
	 * remove \n fom input
	 */
	if(*s == '\n')
		*s-- = 0;

	/*
	 * is last character a \ ?
	 */
	for(nbl = 0; *s == '\\' && s > p; s--)
		nbl++;

	/*
	 * Then fold escaped nl if in table
	 */
	if(linstart && nbl % 2)
		(void) gets1(s + 1);
D 2
/*
printf(".\\\" gets1 returns %s\n", p);
*/
E 2
	return(p);
}

D 5
#define BACKMAX 500
E 5
I 5
#define BACKMAX 2048
E 5
static char    backup[BACKMAX];
static char   *backp = backup;

un1getc(c){
	if(c == '\n')
		iline--;
	*backp++ = c;
	if(backp >= backup + BACKMAX)
		error("too much backup");
}

get1char(){
	register int     c;
	if(backp > backup)
		c = *--backp;
	else
		c = getc(tabin);
	if(c == EOF){
		if(swapin() == 0)
			error("unexpected EOF");
		c = getc(tabin);
	}
	if(c == '\n')
		iline++;
	return(c);
}

backrest(cp)
char *cp;
{
	register char *s;
	for(s=cp; *s; s++)
		;
	un1getc('\n');
	while (s>cp)
		un1getc(*--s);
}
E 1
