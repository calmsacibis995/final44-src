h22628
s 00001/00002/00046
d D 1.2 83/04/18 14:38:34 slatteng 2 1
c DLS takeover
e
s 00048/00000/00000
d D 1.1 83/04/18 13:45:19 slatteng 1 0
c date and time created 83/04/18 13:45:19 by slatteng
e
u
U
t
T
I 1
D 2

/* db3.c -
E 2
I 2
/* %W%	%G%
E 2
 *
 *
 * Copyright -C- 1982 Barry S. Roitblat
 *
 *       This file contains additional routines to implement the database
 * manipulations necessary for the gremlin picture editor.
 */

#include "gremlin.h"
#include "grem2.h"

/* the following variable is a pointer for the current set and is
 * available to the outside world.
 */

ELT *cset;

DBAddSet(element)
ELT *element;
/*
 *      This routine adds the element to the current set database.
 */

{
	ELT *elist;

	elist = cset;
	while ( !DBNullelt(elist) )             /* makes sure element not */
	{                                       /* already in list        */
		if (elist == element) return;
		elist = DBNextofSet(elist);
	};
	element->setnext = cset;
	cset = element;
}  /* end AddSet */

DBClearSet()
/*
 *      This routine clears the current set by setting the pointer
 * to a null element.
 */

{
	while ( !DBNullelt(cset) )
		cset = DBNextofSet(cset);
}  /* end ClearSet */
E 1
