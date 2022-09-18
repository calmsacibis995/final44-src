/* $XConsortium: XDestAssoc.c,v 10.17 91/02/08 13:11:50 rws Exp $ */
/* Copyright    Massachusetts Institute of Technology    1985	*/

/*
Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation, and that the name of M.I.T. not be used in advertising or
publicity pertaining to distribution of the software without specific,
written prior permission.  M.I.T. makes no representations about the
suitability of this software for any purpose.  It is provided "as is"
without express or implied warranty.
*/

#include "Xlibint.h"
#include "X10.h"

/*
 * XDestroyAssocTable - Destroy (free the memory associated with)
 * an XAssocTable.  
 */
XDestroyAssocTable(table)
	register XAssocTable *table;
{
	register int i;
	register XAssoc *bucket;
	register XAssoc *Entry, *entry_next;

	/* Free the buckets. */
	for (i = 0; i < table->size; i++) {
		bucket = &table->buckets[i];
		for (
	        	Entry = bucket->next;
			Entry != bucket;
			Entry = entry_next
		) {
		        entry_next = Entry->next;
			Xfree((char *)Entry);
		}
	}

	/* Free the bucket array. */
	Xfree((char *)table->buckets);

	/* Free the table. */
	Xfree((char *)table);
}

