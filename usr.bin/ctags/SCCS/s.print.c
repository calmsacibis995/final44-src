h47639
s 00001/00001/00088
d D 8.3 94/04/02 10:08:45 pendry 7 6
c add 1994 copyright
e
s 00021/00020/00068
d D 8.2 94/04/01 13:02:00 pendry 6 5
c prettyness police
e
s 00002/00002/00086
d D 8.1 93/06/06 14:29:53 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00025/00083
d D 5.4 91/02/26 13:42:20 bostic 4 3
c ANSI fixes, use strdup instead of rolling your own
e
s 00001/00011/00107
d D 5.3 90/06/01 15:58:32 bostic 3 2
c new copyright notice
e
s 00015/00004/00103
d D 5.2 88/12/31 12:32:33 bostic 2 1
c original by Ken Arnold -- Berkeley copyright
e
s 00107/00000/00000
d D 5.1 87/03/16 17:57:35 bostic 1 0
c date and time created 87/03/16 17:57:35 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
D 5
 * Copyright (c) 1987 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
D 7
 * Copyright (c) 1987, 1993
E 7
I 7
 * Copyright (c) 1987, 1993, 1994
E 7
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
D 3
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif not lint
E 2
I 2
#endif /* not lint */
E 2

D 4
#include <sys/types.h>
#include <sys/file.h>
#include <ctags.h>
E 4
I 4
D 6
#include <unistd.h>
E 6
I 6
#include <limits.h>
E 6
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
I 6
#include <unistd.h>

E 6
#include "ctags.h"
E 4

D 6
extern char	searchar;		/* ex search character */

E 6
/*
 * getline --
 *	get the line the token of interest occurred on,
 *	prepare it for printing.
 */
I 6
void
E 6
getline()
{
D 6
	register long	saveftell;
	register int	c,
			cnt;
	register char	*cp;
E 6
I 6
	long	saveftell;
	int	c;
	int	cnt;
	char	*cp;
E 6

	saveftell = ftell(inf);
D 6
	(void)fseek(inf,lineftell,L_SET);
E 6
I 6
	(void)fseek(inf, lineftell, L_SET);
E 6
	if (xflag)
D 6
		for (cp = lbuf;GETC(!=,'\n');*cp++ = c);
E 6
I 6
		for (cp = lbuf; GETC(!=, '\n'); *cp++ = c)
			continue;
E 6
	/*
	 * do all processing here, so we don't step through the
	 * line more than once; means you don't call this routine
	 * unless you're sure you've got a keeper.
	 */
D 6
	else for (cnt = 0,cp = lbuf;GETC(!=,EOF) && cnt < ENDLINE;++cnt) {
		if (c == (int)'\\') {		/* backslashes */
E 6
I 6
	else for (cnt = 0, cp = lbuf; GETC(!=, EOF) && cnt < ENDLINE; ++cnt) {
		if (c == '\\') {		/* backslashes */
E 6
			if (cnt > ENDLINE - 2)
				break;
			*cp++ = '\\'; *cp++ = '\\';
			++cnt;
		}
		else if (c == (int)searchar) {	/* search character */
			if (cnt > ENDLINE - 2)
				break;
			*cp++ = '\\'; *cp++ = c;
			++cnt;
		}
D 6
		else if (c == (int)'\n') {	/* end of keep */
E 6
I 6
		else if (c == '\n') {	/* end of keep */
E 6
			*cp++ = '$';		/* can find whole line */
			break;
		}
		else
			*cp++ = c;
	}
	*cp = EOS;
D 6
	(void)fseek(inf,saveftell,L_SET);
E 6
I 6
	(void)fseek(inf, saveftell, L_SET);
E 6
}

/*
 * put_entries --
 *	write out the tags
 */
I 6
void
E 6
put_entries(node)
D 6
	register NODE	*node;
E 6
I 6
	NODE	*node;
E 6
{
D 6
	extern FILE	*outf;		/* ioptr for tags file */
	extern int	vflag;		/* -v: vgrind style output */
E 6

	if (node->left)
		put_entries(node->left);
	if (vflag)
		printf("%s %s %d\n",
D 6
		    node->entry,node->file,(node->lno + 63) / 64);
E 6
I 6
		    node->entry, node->file, (node->lno + 63) / 64);
E 6
	else if (xflag)
		printf("%-16s%4d %-16s %s\n",
D 6
		    node->entry,node->lno,node->file,node->pat);
E 6
I 6
		    node->entry, node->lno, node->file, node->pat);
E 6
	else
D 6
		fprintf(outf,"%s\t%s\t%c^%s%c\n",
		    node->entry,node->file,searchar,node->pat,searchar);
E 6
I 6
		fprintf(outf, "%s\t%s\t%c^%s%c\n",
		    node->entry, node->file, searchar, node->pat, searchar);
E 6
	if (node->right)
		put_entries(node->right);
D 4
}

char *
savestr(str)
	char	*str;
{
	register u_int	len;
	register char	*space;
	char	*malloc();

	len = strlen(str) + 1;
	if (!(space = malloc((u_int)len))) {
		/*
		 * should probably free up the tree, here,
		 * we're just as likely to fail here as we
		 * are when getting the NODE structure
		 */
		fputs("ctags: no more space.\n",stderr);
		exit(1);
	}
	bcopy(str,space,len);
	return(space);
E 4
}
E 1
