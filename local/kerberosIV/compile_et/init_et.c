/*
 *
 * $Header: /a/guest/dglo/nuk/compile_et/RCS/init_et.c,v 1.3 1993/11/04 20:38:29 dglo Exp dglo $
 * $Source: /a/guest/dglo/nuk/compile_et/RCS/init_et.c,v $
 * $Locker: dglo $
 *
 * Copyright 1986 by MIT Information Systems and
 *	MIT Student Information Processing Board
 *
 * For copyright info, see mit-sipb-copyright.h.
 *
 */

#include <stdio.h>
#include "error_table.h"
#include "mit-sipb-copyright.h"
#include "et_proto.h"
#include "sys_proto.h"

static char copyright[] = "Copyright 1987 by MIT Student Information Processing Board";

/* useful */
typedef error_table *etp;
typedef etp *etpp;

etpp _et_list = (etpp)NULL;
static int n_allocated = 0, n_used = 0;

void
init_error_table(msgs, base, count)
	const char **msgs;
	register int base;
	int count;
{
	register int i;
	register etp new_et;
	register etpp list;

	if (!base || !count || !msgs)
		return;

	new_et = (etp)malloc(sizeof(error_table));
	new_et->msgs = msgs;
	new_et->base = base;
	new_et->n_msgs= count;

	list = _et_list;
	if (list == (etpp)NULL) {
		_et_list = (etpp) malloc(10*sizeof(etp));
		list = _et_list;
		if (list == (etpp)NULL)
			return;	/* oops */
		list[0] = new_et;
		list[1] = (etp)NULL;
		n_allocated = 10;
		n_used = 1;
		return;
	}
	for (i = 0; i < n_used; i++)
		if (list[i]->base == base)
			return;	/* avoid duplicates */
	if (n_used+2 > n_allocated) {
		n_allocated += 10; /* don't re-allocate too often */
		list = (etpp) realloc((char *)list,
				      (unsigned)n_allocated * sizeof(etp));
		_et_list = list;
		if (list == (etpp)NULL)
			return;	/* oops */
	}
	list[n_used++] = new_et;
	list[n_used] = (etp)NULL;
}
