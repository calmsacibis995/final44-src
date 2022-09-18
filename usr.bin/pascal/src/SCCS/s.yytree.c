h12326
s 00002/00002/00169
d D 8.1 93/06/06 16:14:03 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00165
d D 5.2 91/04/16 16:05:21 bostic 6 5
c new copyright; att/bsd/shared
e
s 00007/00003/00163
d D 5.1 85/06/05 15:17:07 dist 5 4
c Add copyright
e
s 00000/00000/00166
d D 2.1 84/02/08 20:44:53 aoki 4 3
c synchronize to version 2
e
s 00000/00000/00166
d D 1.3 83/09/19 07:02:37 thien 3 2
c Restoring to unlinted version
e
s 00040/00030/00126
d D 1.2 83/08/19 05:05:31 thien 2 1
c The changes were made to allow successful linting
e
s 00156/00000/00000
d D 1.1 80/08/27 19:57:36 peter 1 0
c date and time created 80/08/27 19:57:36 by peter
e
u
U
t
T
I 1
D 5
/* Copyright (c) 1979 Regents of the University of California */
E 5
I 5
D 6
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 6
I 6
/*-
D 7
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 7
I 7
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 *
 * %sccs.include.redist.c%
E 6
 */
E 5

I 2
#ifndef lint
E 2
D 5
static	char sccsid[] = "%Z%%M% %I% %G%";
I 2
#endif
E 5
I 5
static char sccsid[] = "%W% (Berkeley) %G%";
D 6
#endif not lint
E 6
I 6
#endif /* not lint */
E 6
E 5
E 2

#include "whoami.h"
#include "0.h"
#include "tree.h"
I 2
#include "tree_ty.h"
E 2

extern	int *spacep;

/*
 * LIST MANIPULATION ROUTINES
 *
 * The grammar for Pascal is written left recursively.
 * Because of this, the portions of parse trees which are to resemble
 * lists are in the somewhat inconvenient position of having
 * the nodes built from left to right, while we want to eventually
 * have as semantic value the leftmost node.
 * We could carry the leftmost node as semantic value, but this
 * would be inefficient as to add a new node to the list we would
 * have to chase down to the end.  Other solutions involving a head
 * and tail pointer waste space.
 *
 * The simple solution to this apparent dilemma is to carry along
 * a pointer to the leftmost node in a list in the rightmost node
 * which is the current semantic value of the list.
 * When we have completed building the list, we can retrieve this
 * left end pointer very easily; neither adding new elements to the list
 * nor finding the left end is thus expensive.  As the bottommost node
 * has an unused next pointer in it, no space is wasted either.
 *
 * The nodes referred to here are of the T_LISTPP type and have
 * the form:
 *
 *	T_LISTPP	some_pointer		next_element
 *
 * Here some_pointer points to the things of interest in the list,
 * and next_element to the next thing in the list except for the
 * rightmost node, in which case it points to the leftmost node.
 * The next_element of the rightmost node is of course zapped to the
 * NIL pointer when the list is completed.
 *
 * Thinking of the lists as tree we heceforth refer to the leftmost
 * node as the "top", and the rightmost node as the "bottom" or as
 * the "virtual root".
 */

/*
 * Make a new list
 */
I 2
struct tnode *
E 2
newlist(new)
D 2
	register int *new;
E 2
I 2
	register struct tnode *new;
E 2
{

D 2
	if (new == NIL)
		return (NIL);
	return (tree3(T_LISTPP, new, spacep));
E 2
I 2
	if (new == TR_NIL)
		return (TR_NIL);
	return ((struct tnode *) tree3(T_LISTPP, (int) new,
					(struct tnode *) spacep));
E 2
}

/*
 * Add a new element to an existing list
 */
I 2
struct tnode *
E 2
addlist(vroot, new)
D 2
	register int *vroot;
	int *new;
E 2
I 2
	register struct tnode *vroot;
	struct tnode *new;
E 2
{
D 2
	register int *top;
E 2
I 2
	register struct tnode *top;
E 2

D 2
	if (new == NIL)
E 2
I 2
	if (new == TR_NIL)
E 2
		return (vroot);
D 2
	if (vroot == NIL)
E 2
I 2
	if (vroot == TR_NIL)
E 2
		return (newlist(new));
D 2
	top = vroot[2];
	vroot[2] = spacep;
	return (tree3(T_LISTPP, new, top));
E 2
I 2
	top = vroot->list_node.next;
	vroot->list_node.next = (struct tnode *) spacep;
	return ((struct tnode *) tree3(T_LISTPP, (int) new, top));
E 2
}

/*
 * Fix up the list which has virtual root vroot.
 * We grab the top pointer and return it, zapping the spot
 * where it was so that the tree is not circular.
 */
I 2
struct tnode *
E 2
fixlist(vroot)
D 2
	register int *vroot;
E 2
I 2
	register struct tnode *vroot;
E 2
{
D 2
	register int *top;
E 2
I 2
	register struct tnode *top;
E 2

D 2
	if (vroot == NIL)
		return (NIL);
	top = vroot[2];
	vroot[2] = NIL;
E 2
I 2
	if (vroot == TR_NIL)
		return (TR_NIL);
	top = vroot->list_node.next;
	vroot->list_node.next = TR_NIL;
E 2
	return (top);
}


/*
 * Set up a T_VAR node for a qualified variable.
 * Init is the initial entry in the qualification,
 * or NIL if there is none.
 *
 * if we are building pTrees, there has to be an extra slot for 
 * a pointer to the namelist entry of a field, if this T_VAR refers
 * to a field name within a WITH statement.
 * this extra field is set in lvalue, and used in VarCopy.
 */
I 2
struct tnode *
E 2
setupvar(var, init)
	char *var;
D 2
	register int *init;
E 2
I 2
	register struct tnode *init;
E 2
{

D 2
	if (init != NIL)
E 2
I 2
	if (init != TR_NIL)
E 2
		init = newlist(init);
#	ifndef PTREE
D 2
	    return (tree4(T_VAR, NOCON, var, init));
E 2
I 2
	    return (tree4(T_VAR, NOCON, (struct tnode *) var, init));
E 2
#	else
D 2
	    return tree5( T_VAR , NOCON , var , init , NIL );
E 2
I 2
	    return tree5( T_VAR, NOCON, (struct tnode *) var, init, TR_NIL );
E 2
#	endif
}

    /*
     *	set up a T_TYREC node for a record
     *
     *	if we are building pTrees, there has to be an extra slot for 
     *	a pointer to the namelist entry of the record.
     *	this extra field is filled in in gtype, and used in RecTCopy.
     */
D 2
setuptyrec( line , fldlst )
E 2
I 2
struct tnode *
setuptyrec( line , fldlist )
E 2
    int	line;
D 2
    int	*fldlst;
E 2
I 2
    struct tnode *fldlist;
E 2
    {

#	ifndef PTREE
D 2
	    return tree3( T_TYREC , line , fldlst );
E 2
I 2
	    return tree3( T_TYREC , line , fldlist );
E 2
#	else
D 2
	    return tree4( T_TYREC , line , fldlst , NIL );
E 2
I 2
	    return tree4( T_TYREC , line , fldlst , TR_NIL );
E 2
#	endif
    }

    /*
     *	set up a T_FIELD node for a field.
     *
     *	if we are building pTrees, there has to be an extra slot for
     *	a pointer to the namelist entry of the field.
     *	this extra field is set in lvalue, and used in SelCopy.
     */
I 2
struct tnode *
E 2
setupfield( field , other )
D 2
    int	*field;
    int	*other;
E 2
I 2
    struct tnode *field;
    struct tnode *other;
E 2
    {

#	ifndef PTREE
D 2
	    return tree3( T_FIELD , field , other );
E 2
I 2
	    return tree3( T_FIELD , (int) field , other );
E 2
#	else
D 2
	    return tree4( T_FIELD , field , other , NIL );
E 2
I 2
	    return tree4( T_FIELD , (int) field , other , TR_NIL );
E 2
#	endif
    }
E 1
