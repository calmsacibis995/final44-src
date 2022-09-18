h15959
s 00000/00000/00070
d D 8.1 93/06/08 18:32:15 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00002/00068
d D 6.4 93/06/08 18:31:59 bostic 7 5
c do roff .c files by hand
e
s 00002/00002/00068
d R 8.1 93/06/04 16:45:21 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00027/00063
d D 6.3 91/04/17 10:37:56 bostic 5 4
c new copyright; att/bsd/shared
e
s 00021/00004/00069
d D 6.2 89/03/17 11:32:23 bostic 4 3
c add Berkeley specific copyright notices
e
s 00007/00016/00066
d D 6.1 86/04/24 00:01:06 mckusick 3 2
c document distributed with 4.3BSD
e
s 00000/00000/00082
d D 5.1 86/04/24 00:00:53 mckusick 2 1
c document distributed with 4.2BSD
e
s 00082/00000/00000
d D 4.1 86/04/24 00:00:41 mckusick 1 0
c document distributed with 4.1BSD
e
u
U
t
T
I 1
D 5
/*
D 4
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 4
I 4
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
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
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
 */

#ifndef lint
I 4
char copyright[] =
"%Z% Copyright (c) 1980 The Regents of the University of California.\n\
 All rights reserved.\n";
#endif /* not lint */

#ifndef lint
E 4
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif not lint
E 4
I 4
#endif /* not lint */
E 4

E 5
I 5
D 7
.\" Copyright (c) 1980 The Regents of the University of California.
.\" All rights reserved.
E 7
I 7
.\" Copyright (c) 1980, 1993
.\"	 The Regents of the University of California.  All rights reserved.
E 7
.\"
.\" %sccs.include.redist.roff%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 5
D 3
main() {
E 3
I 3
extern int	_putchar();
E 3

I 3
main()
{
E 3
	reg char	*sp;
D 3
	char		*getenv();
	int		_putchar(), die();
E 3

	srand(getpid());		/* initialize random sequence */

	if (isatty(0)) {
	       gettmode();
D 3
	       if (sp=getenv("TERM"))
E 3
I 3
	       if ((sp = getenv("TERM")) != NULL)
E 3
		       setterm(sp);
		signal(SIGINT, die);
	}
	else {
		printf("Need a terminal on %d\n", _tty_ch);
		exit(1);
	}
	_puts(TI);
	_puts(VS);

	noecho();
	nonl();
	tputs(CL, NLINES, _putchar);
	for (;;) {
		makeboard();		/* make the board setup */
		puton('*');		/* put on '*'s */
		puton(' ');		/* cover up with ' 's */
	}
}

D 3
/*
 * _putchar defined for tputs() (and _puts())
 */
_putchar(c)
reg char	c; {

	putchar(c);
}

E 3
puton(ch)
D 3
char	ch; {

	static int	lasty, lastx;
E 3
I 3
char	ch;
{
E 3
	reg LOCS	*lp;
	reg int		r;
	reg LOCS	*end;
	LOCS		temp;
I 3
	static int	lasty, lastx;
E 3

	end = &Layout[Numstars];
	for (lp = Layout; lp < end; lp++) {
		r = rand() % Numstars;
		temp = *lp;
		*lp = Layout[r];
		Layout[r] = temp;
	}

	for (lp = Layout; lp < end; lp++)
			/* prevent scrolling */
		if (!AM || (lp->y < NLINES - 1 || lp->x < NCOLS - 1)) {
			mvcur(lasty, lastx, lp->y, lp->x);
			putchar(ch);
			lasty = lp->y;
			if ((lastx = lp->x + 1) >= NCOLS)
				if (AM) {
					lastx = 0;
					lasty++;
				}
				else
					lastx = NCOLS - 1;
		}
}
E 1
