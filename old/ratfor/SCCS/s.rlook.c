h62434
s 00000/00000/00075
d D 8.1 93/06/06 16:08:39 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00005/00001/00070
d D 1.3 91/04/16 14:45:34 bostic 3 2
c new copyright; att/bsd/shared
e
s 00004/00001/00067
d D 1.2 83/08/11 21:00:58 sam 2 1
c standardize sccs keyword lines
e
s 00068/00000/00000
d D 1.1 82/12/15 21:46:38 clemc 1 0
c date and time created 82/12/15 21:46:38 by clemc
e
u
U
t
Original BTL Ratfor System for 4.2
T
I 3
/*-
 * %sccs.include.proprietary.c%
 */

E 3
I 1
D 2
/* %W% (Berkeley) %G% */
E 2
I 2
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif
E 3
I 3
#endif /* not lint */
E 3

E 2
#define NULL 0
#define EOS 0
#define	HSHSIZ	101
struct	nlist {
	char	*name;
	char	*def;
	int	ydef;
	struct	nlist *next;
};

struct	nlist	*hshtab[HSHSIZ];
struct nlist	*lookup();
char	*install();
char	*malloc();
char	*copy();
int	hshval;

struct nlist *lookup(str)
char *str;
{
	register char *s1, *s2;
	register struct nlist *np;
	static struct nlist nodef;

	s1 = str;
	for (hshval = 0; *s1; )
		hshval += *s1++;
	hshval %= HSHSIZ;
	for (np = hshtab[hshval]; np!=NULL; np = np->next) {
		s1 = str;
		s2 = np->name;
		while (*s1++ == *s2)
			if (*s2++ == EOS)
				return(np);
	}
	return(&nodef);
}

char *install(nam, val, tran)
char *nam, *val;
int tran;
{
	register struct nlist *np;

	if ((np = lookup(nam))->name == NULL) {
		np = (struct nlist *)malloc(sizeof(*np));
		np->name = copy(nam);
		np->def = copy(val);
		np->ydef = tran;
		np->next = hshtab[hshval];
		hshtab[hshval] = np;
		return(np->def);
	}
	free(np->def);
	np->def = copy(val);
	return(np->def);
}

char *copy(s)
register char *s;
{
	register char *p, *s1;

	p = s1 = (char *) malloc((unsigned)strlen(s)+1);
	while (*s1++ = *s++);
	return(p);
}
E 1
