h54444
s 00002/00002/00097
d D 8.1 93/06/06 11:56:49 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00098
d D 5.4 92/02/09 08:43:52 pendry 4 3
c merge in new release
e
s 00003/00002/00096
d D 5.3 91/05/12 15:59:44 pendry 3 2
c checkpoint for network tape
e
s 00001/00013/00097
d D 5.2 91/03/17 13:43:43 pendry 2 1
c from amd5.3 alpha11
e
s 00110/00000/00000
d D 5.1 91/03/17 11:02:38 pendry 1 0
c date and time created 91/03/17 11:02:38 by pendry
e
u
U
t
T
I 1
/*
D 3
 * $Id: fsi_dict.c,v 5.2 90/10/21 22:34:21 jsp Exp $
 *
E 3
 * Copyright (c) 1989 Jan-Simon Pendry
 * Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Jan-Simon Pendry at Imperial College, London.
 *
D 2
 * Redistribution and use in source and binary forms are permitted provided
 * that: (1) source distributions retain this entire copyright notice and
 * comment, and (2) distributions including binaries display the following
 * acknowledgement:  ``This product includes software developed by the
 * University of California, Berkeley and its contributors'' in the
 * documentation or other materials provided with the distribution and in
 * all advertising materials mentioning features or use of this software.
 * Neither the name of the University nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
I 3
 *
D 4
 * $Id: fsi_dict.c,v 5.2.1.1 91/05/07 22:19:08 jsp Alpha $
E 4
I 4
 * $Id: fsi_dict.c,v 5.2.2.1 1992/02/09 15:09:43 jsp beta $
E 4
 *
E 3
 */

/*
 * Dictionary support
 */

#include "../fsinfo/fsinfo.h"

static int dict_hash(k)
char *k;
{
	unsigned int h;
	
	for (h = 0; *k; h += *k++)
		;
	return h % DICTHASH;
}

dict *new_dict()
{
	dict *dp = ALLOC(dict);
	return dp;
}

static void dict_add_data(de, v)
dict_ent *de;
char *v;
{
	dict_data *dd = ALLOC(dict_data);
	dd->dd_data = v;
	ins_que(&dd->dd_q, de->de_q.q_back);
	de->de_count++;
}

static dict_ent *new_dict_ent(k)
char *k;
{
	dict_ent *de = ALLOC(dict_ent);
	de->de_key = k;
	init_que(&de->de_q);
	return de;
}

dict_ent *dict_locate(dp, k)
dict *dp;
char *k;
{
	dict_ent *de = dp->de[dict_hash(k)];
	while (de && !STREQ(de->de_key, k))
		de = de->de_next;

	return de;
}

void dict_add(dp, k, v)
dict *dp;
char *k, *v;
{
	dict_ent *de = dict_locate(dp, k);
	if (!de) {
		dict_ent **dep = &dp->de[dict_hash(k)];
		de = new_dict_ent(k);
		de->de_next = *dep;
		*dep = de;
	}
	dict_add_data(de, v);
}

int dict_iter(dp, fn)
dict *dp;
int (*fn)();
{
	int i;
	int errors = 0;

	for (i = 0; i < DICTHASH; i++) {
		dict_ent *de = dp->de[i];
		while (de) {
			errors += (*fn)(&de->de_q);
			de = de->de_next;
		}
	}
	return errors;
}
E 1
