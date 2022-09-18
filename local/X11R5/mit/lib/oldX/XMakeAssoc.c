/* $XConsortium: XMakeAssoc.c,v 10.18 91/01/06 12:09:28 rws Exp $ */
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

void insque();
struct qelem {
	struct    qelem *q_forw;
	struct    qelem *q_back;
	char q_data[1];
};
/*
 * XMakeAssoc - Insert data into an XAssocTable keyed on an XId.
 * Data is inserted into the table only once.  Redundant inserts are
 * meaningless (but cause no problems).  The queue in each association
 * bucket is sorted (lowest XId to highest XId).
 */
XMakeAssoc(dpy, table, x_id, data)
	register Display *dpy;
	register XAssocTable *table;
	register XID x_id;
	register caddr_t data;
{
	int hash;
	register XAssoc *bucket;
	register XAssoc *Entry;
	register XAssoc *new_entry;
	
	/* Hash the XId to get the bucket number. */
	hash = x_id & (table->size - 1);
	/* Look up the bucket to get the entries in that bucket. */
	bucket = &table->buckets[hash];
	/* Get the first entry in the bucket. */
	Entry = bucket->next;

	/* If (Entry != bucket), the bucket is empty so make */
	/* the new entry the first entry in the bucket. */
	/* if (Entry == bucket), the we have to search the */
	/* bucket. */
	if (Entry != bucket) {
		/* The bucket isn't empty, begin searching. */
		/* If we leave the for loop then we have either passed */
		/* where the entry should be or hit the end of the bucket. */
		/* In either case we should then insert the new entry */
		/* before the current value of "Entry". */
		for (; Entry != bucket; Entry = Entry->next) {
			if (Entry->x_id == x_id) {
				/* Entry has the same XId... */
				if (Entry->display == dpy) {
					/* Entry has the same Display... */
					/* Therefore there is already an */
					/* entry with this XId and Display, */
					/* reset its data value and return. */
					Entry->data = data;
					return;
				}
				/* We found an association with the right */
				/* id but the wrong display! */
				continue;
			}
			/* If the current entry's XId is greater than the */
			/* XId of the entry to be inserted then we have */
			/* passed the location where the new XId should */
			/* be inserted. */
			if (Entry->x_id > x_id) break;
		}
        }

	/* If we are here then the new entry should be inserted just */
	/* before the current value of "Entry". */
	/* Create a new XAssoc and load it with new provided data. */
	new_entry = (XAssoc *)Xmalloc(sizeof(XAssoc));
	if (new_entry == NULL) {
		/* Malloc failed! */
		errno = ENOMEM;
		(*_XIOErrorFunction)(dpy);
	}
	new_entry->display = dpy;
	new_entry->x_id = x_id;
	new_entry->data = data;

	/* Insert the new entry. */
	insque((struct qelem *)new_entry, (struct qelem *)Entry->prev);
}

