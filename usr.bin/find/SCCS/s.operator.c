h38712
s 00002/00002/00242
d D 8.1 93/06/06 14:39:24 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00019/00016/00225
d D 5.5 93/05/01 11:51:40 bostic 5 4
c use library err/warn(3) functions; lint, prettiness police
e
s 00010/00011/00231
d D 5.4 91/05/24 15:17:14 bostic 4 3
c return to the original find syntax (newsyntax.c -> main.c, delete
c oldsyntax.c; create extern.h for ANSI prototypes; create true error routine;
c make NEW macro a real routine
e
s 00014/00014/00228
d D 5.3 91/05/23 18:53:30 bostic 3 2
c T_USER used in the kernel, included by <sys/param.h> -- change to
c be N_ instead.  Make it an enum while we're there...
e
s 00026/00024/00216
d D 5.2 90/11/15 13:03:06 bostic 2 1
c use getchar() for queryuser function; lots of minor lint
e
s 00240/00000/00000
d D 5.1 90/04/16 17:23:10 bostic 1 0
c new version derived from Cimarron Taylor's
e
u
U
t
T
I 1
/*-
D 6
 * Copyright (c) 1990 The Regents of the University of California.
 * All rights reserved.
E 6
I 6
 * Copyright (c) 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
 *
 * This code is derived from software contributed to Berkeley by
 * Cimarron D. Taylor of the University of California, Berkeley.
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#include <sys/types.h>
I 5

#include <err.h>
#include <fts.h>
E 5
#include <stdio.h>
I 5

E 5
#include "find.h"
    
I 2
D 4
void bad_arg();

E 4
E 2
/*
D 2
 * find_yanknode --
E 2
I 2
 * yanknode --
E 2
 *	destructively removes the top from the plan
 */
D 4
PLAN *
E 4
I 4
static PLAN *
E 4
D 2
find_yanknode(planp)    
E 2
I 2
yanknode(planp)    
E 2
	PLAN **planp;		/* pointer to top of plan (modified) */
{
	PLAN *node;		/* top node removed from the plan */
    
	if ((node = (*planp)) == NULL)
D 5
		return(NULL);
E 5
I 5
		return (NULL);
E 5
	(*planp) = (*planp)->next;
	node->next = NULL;
D 5
	return(node);
E 5
I 5
	return (node);
E 5
}
 
/*
D 2
 * find_yankexpr --
E 2
I 2
 * yankexpr --
E 2
 *	Removes one expression from the plan.  This is used mainly by
D 2
 *	find_squish_paren.  In comments below, an expression is either
 *	a simple node or a T_EXPR node containing a list of simple nodes.
E 2
I 2
 *	paren_squish.  In comments below, an expression is either a
D 3
 *	simple node or a T_EXPR node containing a list of simple nodes.
E 3
I 3
 *	simple node or a N_EXPR node containing a list of simple nodes.
E 3
E 2
 */
D 4
PLAN *
E 4
I 4
static PLAN *
E 4
D 2
find_yankexpr(planp)    
E 2
I 2
yankexpr(planp)    
E 2
	PLAN **planp;		/* pointer to top of plan (modified) */
{
	register PLAN *next;	/* temp node holding subexpression results */
	PLAN *node;		/* pointer to returned node or expression */
	PLAN *tail;		/* pointer to tail of subplan */
	PLAN *subplan;		/* pointer to head of ( ) expression */
	int f_expr();
    
	/* first pull the top node from the plan */
D 2
	if ((node = find_yanknode(planp)) == NULL)
E 2
I 2
	if ((node = yanknode(planp)) == NULL)
E 2
D 5
		return(NULL);
E 5
I 5
		return (NULL);
E 5
    
	/*
	 * If the node is an '(' then we recursively slurp up expressions
	 * until we find its associated ')'.  If it's a closing paren we
	 * just return it and unwind our recursion; all other nodes are
	 * complete expressions, so just return them.
	 */
D 3
	if (node->type == T_OPENPAREN)
E 3
I 3
	if (node->type == N_OPENPAREN)
E 3
		for (tail = subplan = NULL;;) {
D 2
			if ((next = find_yankexpr(planp)) == NULL)
E 2
I 2
			if ((next = yankexpr(planp)) == NULL)
E 2
D 4
				bad_arg("(", "missing closing ')'");
E 4
I 4
D 5
				err("%s: %s", "(", "missing closing ')'");
E 5
I 5
				err(1, "(: missing closing ')'");
E 5
E 4
			/*
			 * If we find a closing ')' we store the collected
			 * subplan in our '(' node and convert the node to
D 3
			 * a T_EXPR.  The ')' we found is ignored.  Otherwise,
E 3
I 3
			 * a N_EXPR.  The ')' we found is ignored.  Otherwise,
E 3
			 * we just continue to add whatever we get to our
			 * subplan.
			 */
D 3
			if (next->type == T_CLOSEPAREN) {
E 3
I 3
			if (next->type == N_CLOSEPAREN) {
E 3
				if (subplan == NULL)
D 4
					bad_arg("()", "empty inner expression");
E 4
I 4
D 5
					err("%s: %s",
					    "()", "empty inner expression");
E 5
I 5
					errx(1, "(): empty inner expression");
E 5
E 4
				node->p_data[0] = subplan;
D 3
				node->type = T_EXPR;
E 3
I 3
				node->type = N_EXPR;
E 3
				node->eval = f_expr;
				break;
			} else {
				if (subplan == NULL)
					tail = subplan = next;
				else {
					tail->next = next;
					tail = next;
				}
				tail->next = NULL;
			}
		}
D 5
	return(node);
E 5
I 5
	return (node);
E 5
}
 
/*
D 2
 * find_squish_paren --
E 2
I 2
 * paren_squish --
E 2
 *	replaces "parentheisized" plans in our search plan with "expr" nodes.
 */
PLAN *
D 2
find_squish_paren(plan)
E 2
I 2
paren_squish(plan)
E 2
	PLAN *plan;		/* plan with ( ) nodes */
{
	register PLAN *expr;	/* pointer to next expression */
	register PLAN *tail;	/* pointer to tail of result plan */
	PLAN *result;		/* pointer to head of result plan */
    
	result = tail = NULL;

	/*
D 2
	 * the basic idea is to have find_yankexpr do all our work and just
E 2
I 2
	 * the basic idea is to have yankexpr do all our work and just
E 2
	 * collect it's results together.
	 */
D 2
	while ((expr = find_yankexpr(&plan)) != NULL) {
E 2
I 2
	while ((expr = yankexpr(&plan)) != NULL) {
E 2
		/*
		 * if we find an unclaimed ')' it means there is a missing
		 * '(' someplace.
		 */
D 3
		if (expr->type == T_CLOSEPAREN)
E 3
I 3
		if (expr->type == N_CLOSEPAREN)
E 3
D 4
			bad_arg(")", "no beginning '('");
E 4
I 4
D 5
			err("%s: %s", ")", "no beginning '('");
E 5
I 5
			errx(1, "): no beginning '('");
E 5
E 4

		/* add the expression to our result plan */
		if (result == NULL)
			tail = result = expr;
		else {
			tail->next = expr;
			tail = expr;
		}
		tail->next = NULL;
	}
D 5
	return(result);
E 5
I 5
	return (result);
E 5
}
 
/*
D 2
 * find_squish_not --
E 2
I 2
 * not_squish --
E 2
 *	compresses "!" expressions in our search plan.
 */
PLAN *
D 2
find_squish_not(plan)
E 2
I 2
not_squish(plan)
E 2
	PLAN *plan;		/* plan to process */
{
	register PLAN *next;	/* next node being processed */
D 3
	register PLAN *node;	/* temporary node used in T_NOT processing */
E 3
I 3
	register PLAN *node;	/* temporary node used in N_NOT processing */
E 3
	register PLAN *tail;	/* pointer to tail of result plan */
	PLAN *result;		/* pointer to head of result plan */
    
	tail = result = next = NULL;
    
D 2
	while ((next = find_yanknode(&plan)) != NULL) {
E 2
I 2
	while ((next = yanknode(&plan)) != NULL) {
E 2
		/*
		 * if we encounter a ( expression ) then look for nots in
		 * the expr subplan.
		 */
D 3
		if (next->type == T_EXPR)
E 3
I 3
		if (next->type == N_EXPR)
E 3
D 2
			next->p_data[0] = find_squish_not(next->p_data[0]);
E 2
I 2
			next->p_data[0] = not_squish(next->p_data[0]);
E 2

		/*
		 * if we encounter a not, then snag the next node and place
		 * it in the not's subplan.  As an optimization we compress
		 * several not's to zero or one not.
		 */
D 3
		if (next->type == T_NOT) {
E 3
I 3
		if (next->type == N_NOT) {
E 3
			int notlevel = 1;

D 2
			node = find_yanknode(&plan);
E 2
I 2
			node = yanknode(&plan);
E 2
D 3
			while (node->type == T_NOT) {
E 3
I 3
			while (node->type == N_NOT) {
E 3
				++notlevel;
D 2
				node = find_yanknode(&plan);
E 2
I 2
				node = yanknode(&plan);
E 2
			}
			if (node == NULL)
D 4
				bad_arg("!", "no following expression");
E 4
I 4
D 5
				err("%s: %s", "!", "no following expression");
E 5
I 5
				errx(1, "!: no following expression");
E 5
E 4
D 3
			if (node->type == T_OR)
E 3
I 3
			if (node->type == N_OR)
E 3
D 4
				bad_arg("!", "nothing between ! and -o");
E 4
I 4
D 5
				err("%s: %s", "!", "nothing between ! and -o");
E 5
I 5
				errx(1, "!: nothing between ! and -o");
E 5
E 4
			if (notlevel % 2 != 1)
				next = node;
			else
				next->p_data[0] = node;
		}

		/* add the node to our result plan */
		if (result == NULL)
			tail = result = next;
		else {
			tail->next = next;
			tail = next;
		}
		tail->next = NULL;
	}
D 5
	return(result);
E 5
I 5
	return (result);
E 5
}
 
/*
D 2
 * find_squish_or --
E 2
I 2
 * or_squish --
E 2
 *	compresses -o expressions in our search plan.
 */
PLAN *
D 2
find_squish_or(plan)
E 2
I 2
or_squish(plan)
E 2
	PLAN *plan;		/* plan with ors to be squished */
{
	register PLAN *next;	/* next node being processed */
	register PLAN *tail;	/* pointer to tail of result plan */
	PLAN *result;		/* pointer to head of result plan */
    
	tail = result = next = NULL;
    
D 2
	while ((next = find_yanknode(&plan)) != NULL) {
E 2
I 2
	while ((next = yanknode(&plan)) != NULL) {
E 2
		/*
		 * if we encounter a ( expression ) then look for or's in
		 * the expr subplan.
		 */
D 3
		if (next->type == T_EXPR)
E 3
I 3
		if (next->type == N_EXPR)
E 3
D 2
			next->p_data[0] = find_squish_or(next->p_data[0]);
E 2
I 2
			next->p_data[0] = or_squish(next->p_data[0]);
E 2

		/* if we encounter a not then look for not's in the subplan */
D 3
		if (next->type == T_NOT)
E 3
I 3
		if (next->type == N_NOT)
E 3
D 2
			next->p_data[0] = find_squish_or(next->p_data[0]);
E 2
I 2
			next->p_data[0] = or_squish(next->p_data[0]);
E 2

		/*
		 * if we encounter an or, then place our collected plan in the
		 * or's first subplan and then recursively collect the
		 * remaining stuff into the second subplan and return the or.
		 */
D 3
		if (next->type == T_OR) {
E 3
I 3
		if (next->type == N_OR) {
E 3
			if (result == NULL)
D 4
				bad_arg("-o", "no expression before -o");
E 4
I 4
D 5
				err("%s: %s", "-o", "no expression before -o");
E 5
I 5
				errx(1, "-o: no expression before -o");
E 5
E 4
			next->p_data[0] = result;
D 2
			next->p_data[1] = find_squish_or(plan);
E 2
I 2
			next->p_data[1] = or_squish(plan);
E 2
			if (next->p_data[1] == NULL)
D 4
				bad_arg("-o", "no expression after -o");
E 4
I 4
D 5
				err("%s: %s", "-o", "no expression after -o");
E 4
			return(next);
E 5
I 5
				errx(1, "-o: no expression after -o");
			return (next);
E 5
		}

		/* add the node to our result plan */
		if (result == NULL)
			tail = result = next;
		else {
			tail->next = next;
			tail = next;
		}
		tail->next = NULL;
	}
D 5
	return(result);
E 5
I 5
	return (result);
E 5
}
E 1
