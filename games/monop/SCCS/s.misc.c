h04884
s 00002/00002/00244
d D 8.1 93/05/31 17:26:49 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00087/00246
d D 5.6 93/03/25 05:38:34 bostic 6 5
c remove shell escape, since would be setuid games
e
s 00004/00005/00329
d D 5.5 91/02/28 14:18:34 bostic 5 4
c ANSI
e
s 00001/00011/00333
d D 5.4 90/06/01 13:11:48 bostic 4 3
c new copyright notice
e
s 00001/00000/00343
d D 5.3 89/03/05 20:46:59 bostic 3 2
c pwd.h needs sys/types.h
e
s 00011/00006/00332
d D 5.2 88/06/18 14:54:46 bostic 2 1
c install approved copyright notice
e
s 00338/00000/00000
d D 5.1 88/01/02 20:53:26 bostic 1 0
c date and time created 88/01/02 20:53:26 by bostic
e
u
U
t
T
I 1
/*
D 2
 * Copyright (c) 1987 Regents of the University of California.
E 2
I 2
D 7
 * Copyright (c) 1980 Regents of the University of California.
E 2
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
D 4
 * Redistribution and use in source and binary forms are permitted
D 2
 * provided that this notice is preserved and that due credit is given
 * to the University of California at Berkeley. The name of the University
 * may not be used to endorse or promote products derived from this
 * software without specific prior written permission. This software
 * is provided ``as is'' without express or implied warranty.
E 2
I 2
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
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

# include	"monop.ext"
# include	<ctype.h>
# include	<signal.h>

D 6
# define	execsh(sh)	execl(sh, shell_name[roll(1, num_names)-1], 0)

static char	*shell_def	= "/bin/csh",
		*shell_name[]	= {
			".Hi Mom!",
			".Kick Me",
			".I'm really the next process down",
			".Hi Kids!",
			".This space for rent",
			".Singin' in the rain....",
			".I am but a Cog in the Wheel of Life",
			".Look out!!! Behind you!!!!!",
			".Looking for a good time, sailor?",
			".I don't get NO respect...",
			".Augghh!  You peeked!"
		};

static int	num_names	= sizeof shell_name / sizeof (char *);;

char	*shell_in();

E 6
/*
 *	This routine executes a truncated set of commands until a
 * "yes or "no" answer is gotten.
 */
getyn(prompt)
reg char	*prompt; {

	reg int	com;

	for (;;)
		if ((com=getinp(prompt, yn)) < 2)
			return com;
		else
			(*func[com-2])();
}
/*
 *	This routine tells the player if he's out of money.
 */
notify() {

	if (cur_p->money < 0)
		printf("That leaves you $%d in debt\n", -cur_p->money);
	else if (cur_p->money == 0)
		printf("that leaves you broke\n");
	else if (fixing && !told_em && cur_p->money > 0) {
		printf("-- You are now Solvent ---\n");
		told_em = TRUE;
	}
}
/*
 *	This routine switches to the next player
 */
next_play() {

	player = ++player % num_play;
	cur_p = &play[player];
	num_doub = 0;
}
/*
 *	This routine gets an integer from the keyboard after the
 * given prompt.
 */
get_int(prompt)
reg char	*prompt; {

	reg int		num;
	reg char	*sp;
	char		buf[257];

	for (;;) {
inter:
		printf(prompt);
		num = 0;
		for (sp = buf; (*sp=getchar()) != '\n'; sp++)
			if (*sp == -1)	/* check for interrupted system call */
				goto inter;
		if (sp == buf)
			continue;
		for (sp = buf; isspace(*sp); sp++)
			continue;
		for (; isdigit(*sp); sp++)
			num = num * 10 + *sp - '0';
		if (*sp == '\n')
			return num;
		else
			printf("I can't understand that\n");
	}
}
/*
 *	This routine sets the monopoly flag from the list given.
 */
set_ownlist(pl)
int	pl; {

	reg int	num;		/* general counter		*/
	reg MON	*orig;		/* remember starting monop ptr	*/
	reg OWN	*op;		/* current owned prop		*/
	OWN	*orig_op;		/* origianl prop before loop	*/

	op = play[pl].own_list;
#ifdef DEBUG
	printf("op [%d] = play[pl [%d] ].own_list;\n", op, pl);
#endif
	while (op) {
#ifdef DEBUG
		printf("op->sqr->type = %d\n", op->sqr->type);
#endif
		switch (op->sqr->type) {
		  case UTIL:
#ifdef DEBUG
			printf("  case UTIL:\n");
#endif
			for (num = 0; op && op->sqr->type == UTIL; op = op->next)
				num++;
			play[pl].num_util = num;
#ifdef DEBUG
			printf("play[pl].num_util = num [%d];\n", num);
#endif
			break;
		  case RR:
#ifdef DEBUG
			printf("  case RR:\n");
#endif
			for (num = 0; op && op->sqr->type == RR; op = op->next) {
#ifdef DEBUG
				printf("iter: %d\n", num);
				printf("op = %d, op->sqr = %d, op->sqr->type = %d\n", op, op->sqr, op->sqr->type);
#endif
				num++;
			}
			play[pl].num_rr = num;
#ifdef DEBUG
			printf("play[pl].num_rr = num [%d];\n", num);
#endif
			break;
		  case PRPTY:
#ifdef DEBUG
			printf("  case PRPTY:\n");
#endif
			orig = op->sqr->desc->mon_desc;
			orig_op = op;
			num = 0;
			while (op && op->sqr->desc->mon_desc == orig) {
#ifdef DEBUG
				printf("iter: %d\n", num);
#endif
				num++;
#ifdef DEBUG
				printf("op = op->next ");
#endif
				op = op->next;
#ifdef DEBUG
				printf("[%d];\n", op);
#endif
			}
#ifdef DEBUG
			printf("num = %d\n");
#endif
			if (orig == 0) {
				printf("panic:  bad monopoly descriptor: orig = %d\n", orig);
				printf("player # %d\n", pl+1);
				printhold(pl);
				printf("orig_op = %d\n", orig_op);
				printf("orig_op->sqr->type = %d (PRPTY)\n", op->sqr->type);
				printf("orig_op->next = %d\n", op->next);
				printf("orig_op->sqr->desc = %d\n", op->sqr->desc);
				printf("op = %d\n", op);
				printf("op->sqr->type = %d (PRPTY)\n", op->sqr->type);
				printf("op->next = %d\n", op->next);
				printf("op->sqr->desc = %d\n", op->sqr->desc);
				printf("num = %d\n", num);
			}
#ifdef DEBUG
			printf("orig->num_in = %d\n", orig->num_in);
#endif
			if (num == orig->num_in)
				is_monop(orig, pl);
			else
				isnot_monop(orig);
			break;
		}
	}
}
/*
 *	This routine sets things up as if it is a new monopoly
 */
is_monop(mp, pl)
reg MON	*mp;
int	pl; {

	reg char	*sp;
	reg int		i;

	mp->owner = pl;
	mp->num_own = mp->num_in;
	for (i = 0; i < mp->num_in; i++)
		mp->sq[i]->desc->monop = TRUE;
	mp->name = mp->mon_n;
}
/*
 *	This routine sets things up as if it is no longer a monopoly
 */
isnot_monop(mp)
reg MON	*mp; {

	reg char	*sp;
	reg int		i;

	mp->owner = -1;
	for (i = 0; i < mp->num_in; i++)
		mp->sq[i]->desc->monop = FALSE;
	mp->name = mp->not_m;
}
/*
 *	This routine gives a list of the current player's routine
 */
list() {

	printhold(player);
}
/*
 *	This routine gives a list of a given players holdings
 */
list_all() {

	reg int	pl;

	while ((pl=getinp("Whose holdings do you want to see? ", name_list)) < num_play)
		printhold(pl);
}
/*
 *	This routine gives the players a chance before it exits.
 */
I 5
void
E 5
quit() {

	putchar('\n');
	if (getyn("Do you all really want to quit? ", yn) == 0)
		exit(0);
D 5
	signal(2, quit);
E 5
I 5
	signal(SIGINT, quit);
E 5
}
/*
 *	This routine copies one structure to another
 */
cpy_st(s1, s2, size)
reg int	*s1, *s2, size; {

	size /= 2;
	while (size--)
		*s1++ = *s2++;
D 6
}
/*
 *	This routine forks off a shell.  It uses the users login shell
 */
shell_out() {

	static char	*shell = NULL;

	printline();
	if (shell == NULL)
		shell = shell_in();
D 5
	fflush();
E 5
I 5
	fflush(stdout);
E 5
	if (!fork()) {
		signal(SIGINT, SIG_DFL);
		execsh(shell);
	}
	ignoresigs();
	wait();
	resetsigs();
	putchar('\n');
	printline();
}
/*
 *	This routine looks up the users login shell
 */
I 3
# include	<sys/types.h>
E 3
# include	<pwd.h>

D 5
struct passwd	*getpwuid();

E 5
char		*getenv();

char *
shell_in() {

	reg struct passwd	*pp;
	reg char		*sp;

	if ((sp = getenv("SHELL")) == NULL) {
		pp = getpwuid(getuid());
		if (pp->pw_shell[0] != '\0')
			return pp->pw_shell;
		else
			return shell_def;
		/*return (*(pp->pw_shell) != '\0' ? pp->pw_shell : shell_def);*/
	}
	return sp;
}
/*
 *	This routine sets things up to ignore all the signals.
 */
ignoresigs() {

	reg int	i;

	for (i = 0; i < NSIG; i++)
		signal(i, SIG_IGN);
}
/*
 *	This routine sets up things as they were before.
 */
resetsigs() {

	reg int	i;

	for (i = 0; i < NSIG; i++)
		signal(i, SIG_DFL);
D 5
	signal(2, quit);
E 5
I 5
	signal(SIGINT, quit);
E 6
E 5
}
E 1
