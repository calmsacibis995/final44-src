h22723
s 00026/00037/00314
d D 5.3 91/01/20 20:09:59 corbett 3 2
c I simplified the code for printing conflicts.  -rpc
e
s 00001/00011/00350
d D 5.2 90/06/01 16:14:27 bostic 2 1
c new copyright notice
e
s 00361/00000/00000
d D 5.1 89/12/25 14:24:43 bostic 1 0
c date and time created 89/12/25 14:24:43 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Robert Paul Corbett.
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include "defs.h"

D 3

E 3
static short *null_rules;

verbose()
{
    register int i;

    if (!vflag) return;

    null_rules = (short *) MALLOC(nrules*sizeof(short));
    if (null_rules == 0) no_space();
    fprintf(verbose_file, "\f\n");
    for (i = 0; i < nstates; i++)
	print_state(i);
    FREE(null_rules);

    if (nunused)
	log_unused();
    if (SRtotal || RRtotal)
	log_conflicts();

    fprintf(verbose_file, "\n\n%d terminals, %d nonterminals\n", ntokens,
	    nvars);
    fprintf(verbose_file, "%d grammar rules, %d states\n", nrules - 2, nstates);
}


log_unused()
{
    register int i;
    register short *p;

    fprintf(verbose_file, "\n\nRules never reduced:\n");
    for (i = 3; i < nrules; ++i)
    {
	if (!rules_used[i])
	{
	    fprintf(verbose_file, "\t%s :", symbol_name[rlhs[i]]);
	    for (p = ritem + rrhs[i]; *p >= 0; ++p)
		fprintf(verbose_file, " %s", symbol_name[*p]);
	    fprintf(verbose_file, "  (%d)\n", i - 2);
	}
    }
}


log_conflicts()
{
    register int i;

    fprintf(verbose_file, "\n\n");
    for (i = 0; i < nstates; i++)
    {
	if (SRconflicts[i] || RRconflicts[i])
	{
	    fprintf(verbose_file, "State %d contains ", i);
	    if (SRconflicts[i] == 1)
		fprintf(verbose_file, "1 shift/reduce conflict");
	    else if (SRconflicts[i] > 1)
		fprintf(verbose_file, "%d shift/reduce conflicts",
			SRconflicts[i]);
	    if (SRconflicts[i] && RRconflicts[i])
		fprintf(verbose_file, ", ");
	    if (RRconflicts[i] == 1)
		fprintf(verbose_file, "1 reduce/reduce conflict");
	    else if (RRconflicts[i] > 1)
		fprintf(verbose_file, "%d reduce/reduce conflicts",
			RRconflicts[i]);
	    fprintf(verbose_file, ".\n");
	}
    }
}


print_state(state)
int state;
{
    if (state)
	fprintf(verbose_file, "\n\n");
    if (SRconflicts[state] || RRconflicts[state])
	print_conflicts(state);
    fprintf(verbose_file, "state %d\n", state);
    print_core(state);
    print_nulls(state);
    print_actions(state);
}


print_conflicts(state)
int state;
{
D 3
    register int symbol;
    register action *p, *q, *r;
E 3
I 3
    register int symbol, act, number;
    register action *p;
E 3

D 3
    for (p = parser[state]; p; p = q->next)
E 3
I 3
    symbol = -1;
    for (p = parser[state]; p; p = p->next)
E 3
    {
D 3
	q = p;
	if (p->action_code == ERROR || p->suppressed == 2)
E 3
I 3
	if (p->suppressed == 2)
E 3
	    continue;

D 3
	symbol = p->symbol;
	while (q->next && q->next->symbol == symbol)
	    q = q->next;
	if (state == final_state && symbol == 0)
E 3
I 3
	if (p->symbol != symbol)
E 3
	{
D 3
	    r = p;
	    for (;;)
	    {
		fprintf(verbose_file, "%d: shift/reduce conflict \
(accept, reduce %d) on $end\n", state, r->number - 2);
		if (r == q) break;
		r = r->next;
	    }
E 3
I 3
	    symbol = p->symbol;
	    number = p->number;
	    if (p->action_code == SHIFT)
		act = SHIFT;
	    else
		act = REDUCE;
E 3
	}
D 3
	else if (p != q)
E 3
I 3
	else if (p->suppressed == 1)
E 3
	{
D 3
	    r = p->next;
	    if (p->action_code == SHIFT)
E 3
I 3
	    if (state == final_state && symbol == 0)
E 3
	    {
D 3
		for (;;)
		{
		    if (r->action_code == REDUCE && p->suppressed != 2)
			fprintf(verbose_file, "%d: shift/reduce conflict \
(shift %d, reduce %d) on %s\n", state, p->number, r->number - 2,
				symbol_name[symbol]);
		    if (r == q) break;
		    r = r->next;
		}
E 3
I 3
		fprintf(verbose_file, "%d: shift/reduce conflict \
(accept, reduce %d) on $end\n", state, p->number - 2);
E 3
	    }
	    else
	    {
D 3
		for (;;)
E 3
I 3
		if (act == SHIFT)
E 3
		{
D 3
		    if (r->action_code == REDUCE && p->suppressed != 2)
			fprintf(verbose_file, "%d: reduce/reduce conflict \
(reduce %d, reduce %d) on %s\n", state, p->number - 2, r->number - 2,
				symbol_name[symbol]);
		    if (r == q) break;
		    r = r->next;
E 3
I 3
		    fprintf(verbose_file, "%d: shift/reduce conflict \
(shift %d, reduce %d) on %s\n", state, number, p->number - 2,
			    symbol_name[symbol]);
		}
		else
		{
		    fprintf(verbose_file, "%d: reduce/reduce conflict \
(reduce %d, reduce %d) on %s\n", state, number - 2, p->number - 2,
			    symbol_name[symbol]);
E 3
		}
	    }
	}
    }
}


print_core(state)
int state;
{
    register int i;
    register int k;
    register int rule;
    register core *statep;
    register short *sp;
    register short *sp1;

    statep = state_table[state];
    k = statep->nitems;

    for (i = 0; i < k; i++)
    {
	sp1 = sp = ritem + statep->items[i];

	while (*sp >= 0) ++sp;
	rule = -(*sp);
	fprintf(verbose_file, "\t%s : ", symbol_name[rlhs[rule]]);

        for (sp = ritem + rrhs[rule]; sp < sp1; sp++)
	    fprintf(verbose_file, "%s ", symbol_name[*sp]);

	putc('.', verbose_file);

	while (*sp >= 0)
	{
	    fprintf(verbose_file, " %s", symbol_name[*sp]);
	    sp++;
	}
	fprintf(verbose_file, "  (%d)\n", -2 - *sp);
    }
}


print_nulls(state)
int state;
{
    register action *p;
    register int i, j, k, nnulls;

    nnulls = 0;
    for (p = parser[state]; p; p = p->next)
    {
	if (p->action_code == REDUCE &&
		(p->suppressed == 0 || p->suppressed == 1))
	{
	    i = p->number;
	    if (rrhs[i] + 1 == rrhs[i+1])
	    {
		for (j = 0; j < nnulls && i > null_rules[j]; ++j)
		    continue;

		if (j == nnulls)
		{
		    ++nnulls;
		    null_rules[j] = i;
		}
		else if (i != null_rules[j])
		{
		    ++nnulls;
		    for (k = nnulls - 1; k > j; --k)
			null_rules[k] = null_rules[k-1];
		    null_rules[j] = i;
		}
	    }
	}
    }

    for (i = 0; i < nnulls; ++i)
    {
	j = null_rules[i];
	fprintf(verbose_file, "\t%s : .  (%d)\n", symbol_name[rlhs[j]],
		j - 2);
    }
    fprintf(verbose_file, "\n");
}


print_actions(stateno)
int stateno;
{
    register action *p;
    register shifts *sp;
    register int as;

    if (stateno == final_state)
	fprintf(verbose_file, "\t$end  accept\n");

    p = parser[stateno];
    if (p)
    {
	print_shifts(p);
	print_reductions(p, defred[stateno]);
    }

    sp = shift_table[stateno];
    if (sp && sp->nshifts > 0)
    {
	as = accessing_symbol[sp->shift[sp->nshifts - 1]];
	if (ISVAR(as))
	    print_gotos(stateno);
    }
}


print_shifts(p)
register action *p;
{
    register int count;
    register action *q;

    count = 0;
    for (q = p; q; q = q->next)
    {
	if (q->suppressed < 2 && q->action_code == SHIFT)
	    ++count;
    }

    if (count > 0)
    {
	for (; p; p = p->next)
	{
	    if (p->action_code == SHIFT && p->suppressed == 0)
		fprintf(verbose_file, "\t%s  shift %d\n",
			    symbol_name[p->symbol], p->number);
	}
    }
}


print_reductions(p, defred)
register action *p;
register int defred;
{
    register int k, anyreds;
    register action *q;

    anyreds = 0;
    for (q = p; q ; q = q->next)
    {
	if (q->action_code == REDUCE && q->suppressed < 2)
	{
	    anyreds = 1;
	    break;
	}
    }

    if (anyreds == 0)
	fprintf(verbose_file, "\t.  error\n");
    else
    {
	for (; p; p = p->next)
	{
	    if (p->action_code == REDUCE && p->number != defred)
	    {
		k = p->number - 2;
		if (p->suppressed == 0)
		    fprintf(verbose_file, "\t%s  reduce %d\n",
			    symbol_name[p->symbol], k);
	    }
	}

        if (defred > 0)
	    fprintf(verbose_file, "\t.  reduce %d\n", defred - 2);
    }
}


print_gotos(stateno)
int stateno;
{
    register int i, k;
    register int as;
    register short *to_state;
    register shifts *sp;

    putc('\n', verbose_file);
    sp = shift_table[stateno];
    to_state = sp->shift;
    for (i = 0; i < sp->nshifts; ++i)
    {
	k = to_state[i];
	as = accessing_symbol[k];
	if (ISVAR(as))
	    fprintf(verbose_file, "\t%s  goto %d\n", symbol_name[as], k);
    }
}
E 1
