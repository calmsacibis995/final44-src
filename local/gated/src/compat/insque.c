/*
 *  $Id: insque.c,v 1.10 1993/06/02 23:46:21 jch Exp $
 */

/* %(Copyright.header) */

#include "include.h"

/*
 * C version of insque and remque functions
 */

#if	__GNUC__ >= 2
PROTOTYPE(insque,
	  void,
	  (qelement,
	   qelement));
PROTOTYPE(remque,
	  void,
	  (qelement));
#endif	/* __GNUC__ >= 2*/

void
insque __PF2(elem, qelement,
	     pred, qelement)
{
    elem->q_forw = pred->q_forw;
    elem->q_back = pred;

    pred->q_forw->q_back = elem;
    pred->q_forw = elem;
}

void
remque __PF1(elem, qelement)
{
    elem->q_forw->q_back = elem->q_back;
    elem->q_back->q_forw = elem->q_forw;
}


/*
 * %(Copyright)
 */
