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
#include "vt.h"
#include "windows.h"
#include "fields.h"

main ()
{
	struct field_item      *f[3];
	extern int      cmmatch ();
	extern int      read_match ();

	Start_Form ('_', ' ');

	Print_Center (stdwindow, 1, FANORMAL, "Hicks' Best Match Example");

/*
 *	Create the string field to proceed the best match field
 *
 */
	f[0] = New_Field (5, 38, CMSTR, "____________________",
			0,
			0);
	Set_Label (f[0], "left", "Regular String: ", FANORMAL);
	Set_Tab_Movement (f[0], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (f[0], TRUE);

/*
 *	The application defined best match field
 *
 */
	f[1] = New_Field (7, 38, CMKEY, "____________________",
			0,
			"four score and seven years ago");
	Set_Label (f[1], "left", "Hicks' Style Keyword: ", FANORMAL);
	Set_Tab_Movement (f[1], TRUE, TRUE, TRUE, TRUE, FALSE);
	Set_Auto_Advance (f[1], TRUE);

/*
 *	Change the type to the application supplied routine
 *
 */
	f[1] -> type = cmmatch;
	f[1] -> read_routine = read_match;

/*
 *	Create a confirmation field that will be collected last
 *
 */
	f[2] = New_Field (9, 38, CMCFM, "_", 0, 0);
	Set_Label (f[2], "left", "Confirm: ", FANORMAL);
	Set_Tab_Movement (f[2], TRUE, TRUE, TRUE, TRUE, FALSE);

/*
 *	Process the form
 *
 */
	Show_List (f, 3);

	Get_List (f, 3, FALSE, FALSE);

	End_Form ();
}

/*
 *	cmmatch (field_ptr)
 *
 *	This function determines which menu item is the best match
 *	with the user's response.  This routine calls crosscor() to
 *	get a score between each item and the user's response.  If
 *	the score is less than zero, best match is "no match".
 *
 *	This function depends on the work done in the function
 *	read_match ().
 *
 */

#define NOMATCH "The current entry does not match any of the keywords"

cmmatch (field_ptr)
struct field_item      *field_ptr;
{
	register struct keys   *key_list;
	char   *error;

	error = "The current string has no matches";

	if (!cm_start (field_ptr, error, error))
		return;

	if (field_ptr -> cmflg & CMHLP)
	{
		key_list = (struct keys *) cm_get_keys (field_ptr, TRUE);
		while (key_list -> kstr)
		{
			prhlp (field_ptr, (key_list++) -> kstr, TRUE, TRUE);
		}
		if ((field_ptr -> fnflg & FNHLP) == 0)
		{
			prhlp (field_ptr, "Enter an abbreviation.", FALSE, FALSE);
		}
		field_ptr -> cmflg |= CMNOP;
		return;
	}

	/* if we got here via something other than read_match () */
	/* this will happen if the read match routine is linked to */
	/* another field */
	if (field_ptr -> user_pointer == NULL)
		check_match (field_ptr, field_ptr -> txbuf, FALSE);

	if (field_ptr -> user_pointer != NULL)
	{
		if (field_ptr -> cmflg & CMCMP)
		{
			field_ptr -> txptr = field_ptr -> txbuf;
			*(field_ptr -> txbuf) = '\0';
			complete (field_ptr, field_ptr -> user_pointer);
			field_ptr -> cmflg |= CMREP;
		}
		else
		{
			strcpy (field_ptr -> txbuf, field_ptr -> user_pointer);
		}
		return;
	}

	field_ptr -> cmflg |= CMNOP;
	error_fields = error;
	return;
}

read_match (field_ptr)
register struct field_item     *field_ptr;
{
	register char  *resp_ptr;
	register char  *txbuf_ptr;
	char    response[FORM_BUF];
	char   *format;
	int     rc;

	format = "Best Match: %s";

	txbuf_ptr = field_ptr -> txbuf;
	while ((chartyp[*txbuf_ptr & 0377] == PUNC) &&
			(txbuf_ptr < field_ptr -> txptr))
	{
		txbuf_ptr++;
	}

	for (resp_ptr = response; txbuf_ptr < field_ptr -> txptr &&
			(chartyp[*txbuf_ptr & 0377] != PUNC); )
	{
		*resp_ptr++ = *txbuf_ptr++;
	}
	*resp_ptr = '\0';

	check_match (field_ptr, response, TRUE);

	rc = getachar (field_ptr);

	return (rc);
}

check_match (field_ptr, response, interactive)
struct field_item      *field_ptr;
char   *response;
int interactive;
{
	static char     match_str[FORM_BUF];
	struct keys    *best_key;
	register struct keys   *key_list;
	register int    score;
	register int    biggest;
	char   *format;

	format = "Best Match: %s";

	key_list = (struct keys *) cm_get_keys (field_ptr, TRUE);

	biggest = 0;
	while (key_list -> kstr)
	{
		score = crosscor (response, key_list -> kstr, FALSE);
		if (score > biggest)
		{
			biggest = score;
			best_key = key_list;
		}
		key_list++;
	}

	if (biggest)
	{
		strcpy (match_str, best_key -> kstr);
		field_ptr -> user_pointer = match_str;
		if (interactive)
			Print_Message (field_ptr -> meswin, FANORMAL,
					format, match_str);
	}
	else
	{
		field_ptr -> user_pointer = NULL;
		if (!interactive)
			return;
		if (*response)
		{
			beep ();
			Print_Message (field_ptr -> meswin, FANORMAL,
					format, NOMATCH);
		}
		else
		{
			Print_Message (field_ptr -> meswin, FANORMAL,
					format, "[The field is empty]");
		}
	}
}

/*
 *
 *	cross coorelation routine for determining best matches
 *
 *	crosscor (s, t, type)
 *
 *	"s" is the user's response
 *	"t" is the word the response will be scored against
 *	"type" is FALSE for menu match, TRUE for spelling corrector
 *
 *	This procedure produces correlation scores between two words
 *	(user's response and menu item).  It is important that the
 *	user's response is the first argument and the menu item is
 *	the second.
 */

/*	scores correlation between two words (user's response and list item).
	It is important that the user's response is the first argument and
	the list item is the second.
*/

crosscor( s, t, type )
char	s[];	/* user's response */
char	t[];	/* the word the response will be scored against */
char	type;	/* type = 0 for menu match, 1 for spelling corrector */
{
	int	i = 0;
	int	j = 0;
	int	k = 0;
	int	lens;
	int	lent;
	int	tot = 0;
	char	v[FORM_BUF];

	if( ( lens = strlen( s ) ) == 0 )
		return( -1 );
	if( ( lent = strlen( t ) ) == 0 )
		return( -1 );

	strcpy( v, t );
	if( v[ 0 ] == s[ 0 ] )
		tot += 30;
	for( ; s[ i ]; i++ ) {
		for( ; t[ j ]; j++ ) {
			if( s[ i ] == v[ j ] ) {
				v[ j ] = ' ';
				tot += 30 - j ;
				if( ( i ) && ( j ) )
					if( s[ i - 1 ] == t[ j - 1 ] )
						tot += 30 - j;
				else 
					if( ( s[ i + 1 ] == t[ j + 1 ] ) & ( s[ i + 1 ] ) )
						tot += 30 - j;
				if( j < k ) {
					k = j;
					break;
				}
				else {
					tot += 30 - j;
					k = j;
				}
				break;
			}
		}
		if( type == 1 )
			tot += ( lens - lent ) * 30;
		if( t[ j ] == NULL )
			tot -= 90;
	}
	if( tot )
		return( tot );
	else
		return( -1 );
}	

