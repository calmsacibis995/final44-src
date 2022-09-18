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
 *
 *	cm_get_keys is a function for pulling keywords (separated by
 *	spaces or tabs) out of a string.  The function allocates
 *	space for them and contructs an array of key structs for later
 *	use by the Uhlir parsing routine.
 *
 *	If the second argument is TRUE the keywords will be sorted.
 *	Keywords MUST be sorted to be used with cmkey ();
 *
 */

extern char    *cm_make_str ();

static struct keys      _cm_keys[MAX_KEYS + 1];

struct keys    *cm_get_keys (field_ptr, sort)
struct field_item *field_ptr;
boole sort;
{
	extern int strcmp ();
	char   *str[MAX_KEYS + 1];
	char    tmp_str[FORM_BUF];
	struct keys    *start_keys = _cm_keys;
	register char  *tmp_ptr;
	register char  *src_ptr;
	register int    index;
	int     n_keys;
	char   *error;

	error = "Too many keys specified.";

	for (index = 0; index < MAX_KEYS; index++)
	{
		if (_cm_keys[index].kstr)
		{
			free (_cm_keys[index].kstr);
			_cm_keys[index].kstr = 0;
		}
	}

	src_ptr = field_ptr -> keywords;
	tmp_ptr = tmp_str;
	index = 0;

	while ((*src_ptr == ' ') || (*src_ptr == '\t'))
		src_ptr++;

	while (*src_ptr != '\0')
	{

		if ((*src_ptr == ' ') || (*src_ptr == '\t'))
		{
			*tmp_ptr = '\0';
			str[index] = cm_make_str (tmp_str, tmp_ptr - tmp_str);
			index++;
			if (index >= MAX_KEYS)
			{
				Print_Message (stdwindow, 0, error);
				return (0);
			}
			tmp_ptr = tmp_str;
			while ((*src_ptr == ' ') || (*src_ptr == '\t'))
				src_ptr++;
		}
		else
		{
			*tmp_ptr++ = *src_ptr++;
		}
	}

	if (tmp_ptr != tmp_str)
	{
		*tmp_ptr = '\0';
		str[index] = cm_make_str (tmp_str, tmp_ptr - tmp_str);

		index++;
		if (index >= MAX_KEYS)
		{
			Print_Message (stdwindow, 0, error);
			return (0);
		}
	}

	if (sort)
		gsort (str, &str[index], strcmp);

	n_keys = index;

	for (index = 0; index < n_keys; index++)
	{
		_cm_keys[index].kstr = str[index];
		_cm_keys[index].kval = index;
	}

	_cm_keys[n_keys].kstr = 0;
	_cm_keys[n_keys].kval = 0;

	return (_cm_keys);
}

static char   *
cm_make_str (string, len)
char   *string;
int     len;
{
	register char   *ptr;
	extern char    *malloc ();

	if (len < 1)
		return (NULL);
	ptr = malloc (len + MXTRA);
	if (ptr == 0)
	{
		Print_Message (stdwindow, 0,
			"Cannot allocate key word space.");
		return (0);
	}
	strcpy (ptr, string);
	return (ptr);
}
