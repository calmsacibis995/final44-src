/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include <setjmp.h>
#include "fields.h"

/*
 *	cmkey (field_ptr)
 *
 *	This function looks for a keyword.  field_ptr -> keywords
 *	contains a string of keywords (separated by spaces or tabs).
 *	If the current field uniquely matches exactly one of the
 *	keywords in the table then that keyword (string) is returned.
 *	All keywords that the current field is an initial match for
 *	are listed in the help message.
 *
 *	Keywords are matched by searching the table linearly from
 *	the begining (alphabetically least entry.)  When an entry
 *	is found which is (alphabetically) >= the current field it
 *	is marked as the first possible match.  Scanning then
 *	continues as long as the current field is an initial match
 *	of the keywords.  The first keyword which is not initially
 *	matched is marked as the last possible match.
 *
 *	The keywords between fmatch and lmatch are the possible
 *	matches.  *fmatch matches but *lmatch does not even if
 *	fmatch == lmatch.  This scheme was cooked up by Uhlir.
 */

cmkey (field_ptr)
struct field_item *field_ptr;
{
	_cmkey (field_ptr, FALSE);
}

cmkey_list (field_ptr)
struct field_item *field_ptr;
{
	_cmkey (field_ptr, TRUE);
}

struct keys *_sort_keys ();

static int
_cmkey (field_ptr, listp)
struct field_item *field_ptr;
int listp;
{
	register struct keys   *fmatch;
	register struct keys   *lmatch;
	struct keys    *tfmatch;
	struct keys    *tlmatch;
	char *error1;
	char *error2;

	error1 = "More than one keyword matches";
	error2 = "No keyword matches";

	field_ptr -> fndfv = 0;
	if (!cm_start (field_ptr, error1, error2)) return;

	if (listp)
	{
		fmatch = _sort_keys (field_ptr -> keywords);
	}
	else
	{
		fmatch = (struct keys  *) cm_get_keys (field_ptr, TRUE);
	}

	while ((fmatch -> kstr != 0) &&
			(imatch (field_ptr -> txbuf, fmatch -> kstr, 0, field_ptr -> attribute & FACASE) > 0))
	{
		fmatch++;
	}

	lmatch = fmatch;
	while ((lmatch -> kstr != 0) &&
			(imatch (field_ptr -> txbuf, lmatch -> kstr, 1, field_ptr -> attribute & FACASE) != 0))
	{
		lmatch++;
	}

	if (field_ptr -> cmflg & CMHLP)
	{
		tfmatch = fmatch;
		tlmatch = lmatch;

/*
 *	Nothing match code
 */
		if((lmatch - fmatch) == 0)
		{

			prhlp (field_ptr,
			"The current entry does not match any of the keywords.",
			FALSE, FALSE);

/*
 *	This piece of code will print all of the items if nothing matches
 */

			if (listp)
			{
				tfmatch = _sort_keys (field_ptr -> keywords);
			}
			else
			{
				tfmatch = (struct keys  *) cm_get_keys (field_ptr, TRUE);
			}
			tlmatch = tfmatch;
			while(tlmatch->kstr != 0)
			{
				tlmatch++;
			}
		}

		while (tfmatch < tlmatch)
		{
			prhlp (field_ptr, (tfmatch++) -> kstr, TRUE, TRUE);
		}

		if ((field_ptr -> fnflg & FNHLP) == 0)
		{
			prhlp (field_ptr, "Enter a keyword.", FALSE, FALSE);
		}

		field_ptr -> cmflg |= CMNOP;
		return;
	}

	switch (lmatch - fmatch)
	{
		case 0: 
			field_ptr -> cmflg |= CMNOP;
			error_fields = error2;
			return;

		case 1: 
			complete (field_ptr, fmatch -> kstr);
			if (field_ptr -> cmflg & CMCMP)
			{
				field_ptr -> cmflg |= CMREP;
			}

			if (f_length (field_ptr -> y_pos, fmatch -> kstr) <= field_ptr -> length)
				strcpy (field_ptr -> txbuf, fmatch -> kstr);
			if (listp)
				field_ptr -> fndfv = fmatch -> kval;
			return;

		default: 
			if (strlen (field_ptr -> txbuf) ==
				strlen (fmatch -> kstr))
			{
				if ((field_ptr -> cmflg & CMCMP) == 0)
				{
					if (f_length (field_ptr -> y_pos, fmatch -> kstr) <= field_ptr -> length)
					{
						strcpy (field_ptr -> txbuf, fmatch -> kstr);
						if (listp)
							field_ptr -> fndfv = fmatch -> kval;
						return;
					}
				}
			}

			field_ptr -> cmflg |= (CMNOP | CMNUQ);
			error_fields = error1;
			return;
	}
}

static struct keys *
_sort_keys (keys)
struct keys keys[];
{
	extern int _cmp_keys ();
	static struct keys      _cm_f_keys[MAX_KEYS + 1];
	register int index;
	register int count;
	struct keys *local_keys[MAX_KEYS + 1];
	struct keys *key_ptr;

	key_ptr = keys;
	count = 0;
	while(key_ptr -> kstr != 0)
	{
		local_keys[count] = key_ptr++;
		count++;
		if (count > MAX_KEYS)	/* Don't sort Long Lists */
		{
			return (keys);
		}
	}

	gsort (local_keys, &local_keys[count], _cmp_keys);

	for (index = 0; index < count; index++)
	{
		_cm_f_keys[index].kstr = local_keys[index] -> kstr;
		_cm_f_keys[index].kval = local_keys[index] -> kval;
	}
	_cm_f_keys[count].kstr = 0;

	return (_cm_f_keys);
}

static int
_cmp_keys (arg1, arg2)
register struct keys *arg1;
register struct keys *arg2;
{
	return (strcmp (arg1 -> kstr, arg2 -> kstr));
}
