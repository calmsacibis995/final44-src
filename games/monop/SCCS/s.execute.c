h48320
s 00002/00002/00234
d D 8.1 93/05/31 17:26:32 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00007/00007/00229
d D 5.5 91/02/28 14:18:32 bostic 5 4
c ANSI
e
s 00001/00011/00235
d D 5.4 90/06/01 13:11:11 bostic 4 3
c new copyright notice
e
s 00011/00006/00235
d D 5.3 88/06/18 14:54:32 bostic 3 2
c install approved copyright notice
e
s 00008/00003/00233
d D 5.2 88/01/02 20:59:14 bostic 2 1
c John Gilmore's changes for ANSI C and general cleanup
e
s 00236/00000/00000
d D 5.1 88/01/02 20:53:23 bostic 1 0
c date and time created 88/01/02 20:53:23 by bostic
e
u
U
t
T
I 1
/*
D 3
 * Copyright (c) 1987 Regents of the University of California.
E 3
I 3
D 6
 * Copyright (c) 1980 Regents of the University of California.
E 3
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 3
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 3
I 3
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
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	"monop.ext"
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<sys/time.h>

# define	SEGSIZE	8192

typedef	struct stat	STAT;
typedef	struct tm	TIME;

extern char	etext[],	/* end of text space			*/
		rub();

static char	buf[257],
		*yn_only[]	= { "yes", "no"};

static bool	new_play;	/* set if move on to new player		*/

/*
 *	This routine executes the given command by index number
 */
execute(com_num)
reg int	com_num; {

	new_play = FALSE;	/* new_play is true if fixing	*/
	(*func[com_num])();
	notify();
	force_morg();
	if (new_play)
		next_play();
	else if (num_doub)
		printf("%s rolled doubles.  Goes again\n", cur_p->name);
}
/*
 *	This routine moves a piece around.
 */
do_move() {

	reg int		r1, r2;
	reg bool	was_jail;

	new_play = was_jail = FALSE;
	printf("roll is %d, %d\n", r1=roll(1, 6), r2=roll(1, 6));
	if (cur_p->loc == JAIL) {
		was_jail++;
		if (!move_jail(r1, r2)) {
			new_play++;
			goto ret;
		}
	}
	else {
		if (r1 == r2 && ++num_doub == 3) {
			printf("That's 3 doubles.  You go to jail\n");
			goto_jail();
			new_play++;
			goto ret;
		}
		move(r1+r2);
	}
	if (r1 != r2 || was_jail)
		new_play++;
ret:
	return;
}
/*
 *	This routine moves a normal move
 */
move(rl)
reg int	rl; {

	reg int	old_loc;

	old_loc = cur_p->loc;
	cur_p->loc = (cur_p->loc + rl) % N_SQRS;
	if (cur_p->loc < old_loc && rl > 0) {
		cur_p->money += 200;
		printf("You pass %s and get $200\n", board[0].name);
	}
	show_move();
}
/*
 *	This routine shows the results of a move
 */
show_move() {

	reg SQUARE	*sqp;

	sqp = &board[cur_p->loc];
	printf("That puts you on %s\n", sqp->name);
	switch (sqp->type) {
	  case SAFE:
		printf("That is a safe place\n");
		break;
	  case CC:
I 2
		cc(); break;
E 2
	  case CHANCE:
D 2
	  case SPEC:
		(*((int (*)())(sqp->desc)))();
		break;
E 2
I 2
		chance(); break;
	  case INC_TAX:
		inc_tax(); break;
	  case GOTO_J:
		goto_jail(); break;
	  case LUX_TAX:
		lux_tax(); break;
E 2
	  case PRPTY:
	  case RR:
	  case UTIL:
		if (sqp->owner < 0) {
			printf("That would cost $%d\n", sqp->cost);
			if (getyn("Do you want to buy? ") == 0) {
				buy(player, sqp);
				cur_p->money -= sqp->cost;
			}
			else if (num_play > 2)
				bid(sqp);
		}
		else if (sqp->owner == player)
			printf("You own it.\n");
		else
			rent(sqp);
	}
}
/*
 *	This routine saves the current game for use at a later date
 */
save() {

	reg char	*sp;
	reg int		outf, num;
D 5
	TIME		tme, *tp;
	int		*dat_end, junk[18];
E 5
I 5
	time_t		t;
	int		*dat_end;
	struct stat	sb;
E 5
	unsgn		start, end;

D 5
	tp = &tme;
E 5
	printf("Which file do you wish to save it in? ");
	sp = buf;
	while ((*sp++=getchar()) != '\n')
		continue;
	*--sp = '\0';

	/*
	 * check for existing files, and confirm overwrite if needed
	 */

D 5
	if (stat(buf, junk) > -1
E 5
I 5
	if (stat(buf, &sb) > -1
E 5
	    && getyn("File exists.  Do you wish to overwrite? ", yn_only) > 0)
		return;

	if ((outf=creat(buf, 0644)) < 0) {
		perror(buf);
		return;
	}
	printf("\"%s\" ", buf);
D 5
	time(tp);			/* get current time		*/
	strcpy(buf, ctime(tp));
E 5
I 5
	time(&t);			/* get current time		*/
	strcpy(buf, ctime(&t));
E 5
	for (sp = buf; *sp != '\n'; sp++)
		continue;
	*sp = '\0';
# if 0
	start = (((int) etext + (SEGSIZE-1)) / SEGSIZE ) * SEGSIZE;
# else
	start = 0;
# endif
	end = sbrk(0);
	while (start < end) {		/* write out entire data space */
		num = start + 16 * 1024 > end ? end - start : 16 * 1024;
		write(outf, start, num);
		start += num;
	}
	close(outf);
	printf("[%s]\n", buf);
}
/*
 *	This routine restores an old game from a file
 */
restore() {

	reg char	*sp;

	printf("Which file do you wish to restore from? ");
	for (sp = buf; (*sp=getchar()) != '\n'; sp++)
		continue;
	*sp = '\0';
	rest_f(buf);
}
/*
 *	This does the actual restoring.  It returns TRUE if the
 * backup was successful, else false.
 */
rest_f(file)
reg char	*file; {

	reg char	*sp;
	reg int		inf, num;
	char		buf[80];
	unsgn		start, end;
	STAT		sbuf;

	if ((inf=open(file, 0)) < 0) {
		perror(file);
		return FALSE;
	}
	printf("\"%s\" ", file);
	if (fstat(inf, &sbuf) < 0) {		/* get file stats	*/
		perror(file);
		exit(1);
	}
# if 0
	start = (((int) etext + (SEGSIZE-1)) / SEGSIZE ) * SEGSIZE;
# else
	start = 0;
# endif
	brk(end = start + sbuf.st_size);
	while (start < end) {		/* write out entire data space */
		num = start + 16 * 1024 > end ? end - start : 16 * 1024;
		read(inf, start, num);
		start += num;
	}
	close(inf);
D 5
	strcpy(buf, ctime(sbuf.st_mtime));
E 5
I 5
	strcpy(buf, ctime(&sbuf.st_mtime));
E 5
	for (sp = buf; *sp != '\n'; sp++)
		continue;
	*sp = '\0';
	printf("[%s]\n", buf);
	return TRUE;
}
E 1
