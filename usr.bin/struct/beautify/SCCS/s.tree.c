h63521
s 00000/00000/00247
d D 8.1 93/06/06 16:27:29 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00241
d D 5.1 91/04/16 16:44:14 bostic 5 4
c new copyright; att/bsd/shared
e
s 00000/00002/00243
d D 4.4 91/02/05 18:59:28 bostic 4 3
c don't redeclare malloc
e
s 00004/00001/00241
d D 4.3 88/07/22 17:10:57 bostic 3 2
c ANSIfication
e
s 00003/00003/00239
d D 4.2 87/03/24 02:19:03 lepreau 2 1
c purge old init syntax
e
s 00242/00000/00000
d D 4.1 83/02/11 15:45:11 rrh 1 0
c date and time created 83/02/11 15:45:11 by rrh
e
u
U
t
T
I 5
/*-
 * %sccs.include.proprietary.c%
 */

E 5
I 1
#ifndef lint
D 5
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

# include "y.tab.h"
#include "b.h"
#include <stdio.h>

I 3
D 4
extern char *malloc();
E 3

E 4
I 3
struct node *
E 3
addroot(string,type,n1,n2)
char *string;
int type;
struct node *n1, *n2;
	{
	struct node *p;
D 3
	p = malloc(sizeof(*p));
E 3
I 3
	p = (struct node *)malloc(sizeof(*p));
E 3
	p->left = n1;
	p->right = n2;
	p->op = type;
	p->lit = malloc(slength(string) + 1);
	str_copy(string,p->lit,slength(string) + 1);
	return(p);
	}


freetree(tree)
struct node *tree;
	{
	if (tree)
		{freetree(tree->left);
		freetree(tree->right);
		freenode(tree);
		}
	}

freenode(treenode)
struct node *treenode;
	{
	free(treenode->lit);
	free(treenode);
	}

D 2
int compop[]	{	'&',	'|',	'<',	'>',	xxeq,	xxle,	xxne,	xxge};
int notop[]	{	'|',	'&',	xxge,	xxle,	xxne,	'>',	xxeq,	'<'};
char *opstring[]	{ "||",  "&&",	">=",	"<=", "!=",	">",	"==",	"<"};
E 2
I 2
int compop[] =	{	'&',	'|',	'<',	'>',	xxeq,	xxle,	xxne,	xxge};
int notop[] =	{	'|',	'&',	xxge,	xxle,	xxne,	'>',	xxeq,	'<'};
char *opstring[] =	{ "||",  "&&",	">=",	"<=", "!=",	">",	"==",	"<"};
E 2

I 3
struct node *
E 3
checkneg(tree,neg)		/* eliminate nots if possible */
struct node *tree;
int neg;
	{
	int i;
	struct node *t;
	if (!tree) return(0);
	for (i =  0; i < 8; ++i)
		if (tree->op == compop[i]) break;
	if (i > 1 && i <  8 && tree ->left ->op == '-' && str_eq(tree->right->lit,"0"))
		{
		t = tree->right;
		tree->right = tree->left->right;
		freenode(t);
		t = tree->left;
		tree->left = tree->left->left;
		freenode(t);
		}


	if (neg)
		{
		if (tree ->op == '!')
			{
			t = tree->left;
			freenode(tree);
			return(checkneg(t,0));
			}
			if (i < 8)
				{
				tree->op = notop[i];
				free(tree->lit);
				tree->lit = malloc(slength(opstring[i])+1);
				str_copy(opstring[i],tree->lit, slength(opstring[i])+1);
				if (tree->op == '&' || tree->op == '|')
					{
					tree->left = checkneg(tree->left,1);
					tree->right = checkneg(tree->right,1);
					}
				return(tree);
				}
		if (tree->op == xxident && str_eq(tree->lit,".false."))
			str_copy(".true.",tree->lit, slength(".true.")+1);
		else if (tree->op == xxident && str_eq(tree->lit,".true."))
			{
			free(tree->lit);
			tree->lit = malloc(slength(".false.")+1);
			str_copy(".false.",tree->lit, slength(".false.")+1);
			}
		else
			{
			tree = addroot("!",'!',tree,0);
			tree->lit = malloc(2);
			str_copy("!",tree->lit, slength("!")+1);
			}
		return(tree);
		}
	else
		if (tree->op == '!')
			{
			t = tree;
			tree = tree->left;
			freenode(t);
			return(checkneg(tree,1));
			}
	else
		{tree->left = checkneg(tree->left,0);
		tree->right = checkneg(tree->right,0);
		return(tree);
		}
	}

yield(tree,fprec)
struct node *tree;
int fprec;				/* fprec is precedence of father of this node */
	{
	int paren,p;
	static int oplast;			/* oplast = 1 iff last char printed was operator */
	if (!tree) return;
	p = prec(tree ->op);
	paren = (p < fprec || (oplast && tree->op == xxuminus)) ? 1 : 0;

	if (paren)
		{
		putout('(',"(");
		oplast = 0;
		}

	switch(tree->op)
		{
		case xxuminus:
			tree->op = '-';
		case '!':
			putout(tree->op,tree->lit);
			oplast = 1;
			yield(tree->left,p);
			break;
		case '&':
		case '|':
		case '<':
		case '>':
		case xxeq:
		case xxle:
		case xxge:
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			yield(tree->left,p);
			putout(tree->op, tree->lit);
			oplast = 1;
			yield(tree->right,p);
			break;
		case xxidpar:
			yield(tree->left,0);
			putout('(',"(");
			oplast = 0;
			yield(tree->right,0);
			putout('(',")");
			oplast = 0;
			break;
		default:
			yield(tree->left,p);
			putout(tree->op, tree->lit);
			oplast = 0;
			yield(tree->right,p);
			break;
		}
	if (paren)
		{
		putout(')',")");
		oplast = 0;
		}
	}

puttree(tree)
struct node *tree;
	{
	yield(tree,0);
	freetree(tree);
	}


prec(oper)
int oper;
	{
	switch(oper)
		{
		case ',':		return(0);
		case '|':	return(1);
		case '&':	return(2);
		case '!':	return(3);

		case '<':		case '>':		case xxeq:
		case xxne:	case xxle:	case xxge:
				return(4);
		case '+':
	case '-':		return(5);
		case '*':
	case '/':		return(6);
		case xxuminus:	return(7);
		case '^':	return(8);
		default:	return(9);
		}
	}
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
	fprintf(2,"string %s too long to be copied by str_copy at address %d\n",
			*s,ptr);
	exit(1);
	}
str_eq(s,t)
char s[],t[];
	{int j;
	for (j = 0; s[j] == t[j]; j++)
		{if (s[j] == '\0') return(1);}
	return(0);
	}

slength(s)			/* return number of chars in s, not counting '\0' */
char *s;
	{
	int i;
	if (!s) return(-1);
	for (i = 0; s[i] != '\0'; i++);
	return(i);
	}
E 1
