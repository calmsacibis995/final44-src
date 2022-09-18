h36003
s 00006/00002/00084
d D 4.2 91/04/18 16:44:11 bostic 2 1
c new copyright; att/bsd/shared
e
s 00086/00000/00000
d D 4.1 83/05/06 23:30:11 tut 1 0
c date and time created 83/05/06 23:30:11 by tut
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
static char *sccsid = "%W% (Berkeley) %G%";
#endif
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include "refer..c"
#define punctuat(c) (c=='.' || c=='?' || c=='!' || c==',' || c==';' || c==':')

static gate = 0;
static char buff[BUFSIZ];

output(s)
char *s;
{
	if (gate)
		fputs(buff,ftemp);
	else
		gate = 1;
	strcpy(buff, s);
	if (strlen(buff) > BUFSIZ)
		err("one buff too big (%d)!", BUFSIZ);
}

append(s)
char *s;
{
	char *p;
	int lch;

	trimnl(buff);
	for (p = buff; *p; p++)
		;
	lch = *--p;
	if (postpunct && punctuat(lch))
		*p = NULL;
	else /* pre-punctuation */
		switch (lch) {
		case '.': 
		case '?':
		case '!':
		case ',':
		case ';':
		case ':':
			*p++ = lch;
			*p = NULL;
		}
	strcat(buff, s);
	if (postpunct)
		switch(lch) {
		case '.': 
		case '?':
		case '!':
		case ',':
		case ';':
		case ':':
			for(p = buff; *p; p++)
				;
			if (*--p == '\n')
				*p = NULL;
			*p++ = lch;
			*p++ = '\n';
			*p = NULL;
		}
	if (strlen(buff) > BUFSIZ)
		err("output buff too long (%d)", BUFSIZ);
}

flout()
{
	if (gate)
		fputs(buff,ftemp);
	gate = 0;
}

char *
trimnl(ln)
char *ln;
{
	register char *p = ln;

	while (*p)
		p++;
	p--;
	if (*p == '\n')
		*p = 0;
	return(ln);
}
E 1
