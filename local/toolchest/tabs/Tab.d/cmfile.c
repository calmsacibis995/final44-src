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
#include <sys/types.h>
#include <sys/stat.h>

/*
 *	cmfile (field_ptr)
 *
 *	This function matches a file spec.
 *
 *	CMFILE-- Parse a file name.  Matches file names including
 *		 names with imbedded wild card characters:
 *
 *			% - match any single character
 *		    [a-x] - match with any character in the list
 *			* - match with any number of characters
 *
 *		 Groups of file names may be specified by separating
 *			the names by commas:
 *
 *			9: echo *.c,makefile,*.h
 *
 *		 fdb.fndfv contains the number of files to match.
 *			a negative number says wild card without
 *			completion demanded.  Otherwise wild carding
 *			is left entirely to the user.  When files
 *			are requested from the user (e.g. the remove
 *			command) wild carding should be only on user demand
 *			hence a positive number.  However if the
 *			filename is being used as a command name then
 *			wild carding (i.e. a neg. number) should be
 *			the default.
 *		fdb.fndfs contains the default path to be searched or
 *			the default file if the FNDEF flag is turned
 *			on.
 */

 /* Expand defines */
#define BYTESPERWORD	(sizeof(char *))
#define	ADR(x)		((char*)(x))
#define round(a,b)	(((int)((ADR(a)+b)-1))&~((b)-1))
#define BRKINCR		512

 /* Tabs Local Globals for Expand */
static char *_estakbot;
static char *_estaktop;
static char *_estack = 0;
static  jmp_buf _ejump;

 /* Dummy Routines to Make Expand Work */
extern char *endstak ();
extern char *locstak ();

 /* From expand.c */
extern int  addg ();

extern char *sbrk ();

cmfile (field_ptr)
register struct field_item *field_ptr;
{
    struct stat cmf_buf;		/* Struct for one file */

    char   *e_buffer;			/* Expansion string	 */
    char    e_any;			/* Any wild cards?	 */
    int     e_len;			/* End of the path	 */
    int     en_len;			/* Total length		 */

    int     t_count;			/* Help variables	 */
    int     h_count;
    int     l_count;			/* Loop file count	 */
    int     count;			/* Total file count	 */
    char    h_string[20];		/* Help string		 */

    struct argnod  *schain;		/* Struct for access	 */
    struct argnod  *lchain = 0;		/* Last chain		 */
    struct argnod  *xchain;		/* Current chain	 */

    char    comma = FALSE;		/* Any commas?		 */
    char   *ptr_atom;			/* Pointer to the atom	 */
    char   *rc;				/* Pointer to filename	 */
    char   *error1;
    char   *error2;
    char   *error3;

    error1 = "Too many files match the specification";
    error2 = "No files match";
    error3 = "Item specified is longer than the current field";

    if (!cm_start (field_ptr, error1, error2))
	return;

 /* Set stack for expand */

    if (_estack == 0)
    {
	if ((_estack = sbrk (EXP_BUFFER)) == (char *) - 1)
	{
	    _estack = 0;
	    field_ptr -> cmflg |= CMNOP;
	    error_fields = "Cannot allocate filename expansion space";
	    Print_Message (field_ptr -> meswin, Mess_Attribute, "%s", error_fields);
	    return;
	}
    }

    _estakbot = _estack;
    _estaktop = _estack + EXP_BUFFER - 1;

    if (setjmp (_ejump) == TRUE)
    {
	field_ptr -> cmflg |= CMNOP;
	error_fields = "Not enough space to expand the filename";
	Print_Message (field_ptr -> meswin, Mess_Attribute, "%s", error_fields);
	return;
    }

    count = 0;
    ptr_atom = field_ptr -> txbuf;
    if ((*ptr_atom == '\0') && (field_ptr -> cmflg & CMHLP))
	ptr_atom = "*";

    while (*ptr_atom)			/* Process the atom */
    {
	l_count = 0;
	e_buffer = _estakbot;
	*e_buffer = '\0';
	e_len = 0;

    /* Add on the default PATH */

	if (((field_ptr -> fnflg & FNDEF) == 0) &&
		((field_ptr -> fndfs) != 0))
	{
	    e_len = strlen (field_ptr -> fndfs);
	    if (&e_buffer[e_len] >= (_estack + EXP_BUFFER - 1))
	    {
		field_ptr -> cmflg |= CMNOP;
		error_fields = error1;
		return;
	    }
	    strcpy (e_buffer, field_ptr -> fndfs);
	}

	if (&e_buffer[e_len + strlen (ptr_atom)] >= (_estack + EXP_BUFFER - 1))
	{
	    field_ptr -> cmflg |= CMNOP;
	    error_fields = error1;
	    return;
	}

    /* Look for file separators to process next spec. */

	en_len = e_len;
	while (e_buffer[en_len++] = *ptr_atom)
	{
	    if ((*ptr_atom == ',') &&
		    (*(ptr_atom - 1) != '\\'))
	    {
		e_buffer[en_len - 1] = '\0';
		comma = TRUE;
		ptr_atom++;
		break;
	    }
	    ptr_atom++;
	}
	en_len--;
	_estakbot = (char *) round (_estakbot + (en_len + MXTRA), BYTESPERWORD);

	e_any = s_any (e_buffer, "*%[");/* Look for wild cards */

    /* Do the expansion - directory lookup */

	if ((*ptr_atom == '\0') &&
		((field_ptr -> cmflg & CMCMP) ||
		    (field_ptr -> cmflg & CMHLP)))
	{
	    if (e_any == FALSE)
	    {
		e_buffer[en_len++] = '*';
		e_buffer[en_len] = '\0';
	    }
	    l_count = expand (e_buffer, 0);
	    if ((l_count == 0) &&
		    (e_buffer[en_len - 1] != '*'))
	    {
		e_buffer[en_len++] = '*';
		e_buffer[en_len] = '\0';
		l_count = expand (e_buffer, 0);
	    }
	}
	else
	{
	    if (e_any)
	    {
		l_count = expand (e_buffer, 0);
	    }
	    else
	    {
		if (stat (e_buffer, &cmf_buf) == 0)
		{
		    l_count = 1;
		    addg ("\0", e_buffer, 0);
		}
	    }
	    if ((field_ptr -> fndfv < 0) &&
		    (l_count == 0) &&
		    (e_buffer[en_len - 1] != '*'))
	    {
		e_buffer[en_len++] = '*';
		e_buffer[en_len] = '\0';
		l_count = expand (e_buffer, 0);
	    }
	}

    /* Keep the chain connected between lookup's */

	if ((l_count > 0) && (count > 0))
	{
	    for (t_count = 0, schain = lchain;
		    t_count < (count - 1); t_count++)
	    {
		schain = schain -> argnxt;
	    }
	    schain -> argnxt = gchain;
	}
	if (l_count > 0)
	{
	    if (count == 0)
		lchain = gchain;
	    count += l_count;
	}
    }
    xchain = gchain;			/* Remember the last chain found */
    gchain = lchain;			/* Set gchain to top of the chain */
    cnt_gchain = count;

 /* Print the help information */

    if (field_ptr -> cmflg & CMHLP)
    {
	if (count > SHOW_FILES)
	    h_count = SHOW_FILES;
	else
	    h_count = count;

	arg_sort (count);

	for (t_count = 0, schain = gchain;
		t_count < h_count; t_count++)
	{
	    rc = (char *) strrchr (schain -> argval, '/');
	    if (rc == NULL)
		rc = schain -> argval;
	    else
		rc++;

	    prhlp (field_ptr, rc, TRUE, TRUE);
	    schain = schain -> argnxt;
	}

	if (h_count != count)
	{
	    sprintf (h_string,
		    " and %d more files", count - h_count);
	    prhlp (field_ptr, h_string, FALSE, FALSE);
	}

	if (count == 0)
	{
	    prhlp (field_ptr,
		    "The current entry does not match any valid filename.", FALSE, FALSE);
	}

	if ((field_ptr -> fnflg & FNHLP) == 0)
	{
	    prhlp (field_ptr, "Enter a file specification.", FALSE, FALSE);
	}

	field_ptr -> cmflg |= CMNOP;
	if (count > 0)
	    field_ptr -> cmflg |= CMNUQ;
	return;
    }

 /* Do the completion */

    if ((count > 0) &&
	    (count <= ((field_ptr -> fndfv < 0) ? -field_ptr -> fndfv :
		    field_ptr -> fndfv)))
    {
	if (l_count == 1)
	{
	    if (field_ptr -> cmflg & CMCMP)
	    {
		if (comma == TRUE)
		{
		    rc = (char *) strrchr (field_ptr -> txbuf, ',') + 1;
		    if (rc != field_ptr -> txptr)
		    {
			*rc = '\0';
			sprintf (_estakbot, "%s%s", field_ptr -> txbuf,
				&xchain -> argval[e_len]);
		    }
		    else
		    {
			*(rc - 1) = '\0';
			sprintf (_estakbot, "%s", field_ptr -> txbuf);
		    }
		    complete (field_ptr, _estakbot);
		    if (field_ptr -> cmflg & CMNOP)
		    {
			error_fields = error3;
			return;
		    }
		}
		else
		{
		    complete (field_ptr, &xchain -> argval[e_len]);
		}
	    }
	    else
	    {
		if (comma == FALSE)
		    strcpy (field_ptr -> txbuf, &xchain -> argval[e_len]);
	    }
	}
	else
	{
	    if (field_ptr -> cmflg & CMCMP)
	    {
		if (comma == TRUE)
		{
		    rc = (char *) strrchr (field_ptr -> txbuf, ',') + 1;
		    if (rc != field_ptr -> txptr)
		    {
			*rc = '\0';
			sprintf (_estakbot, "%s%s", field_ptr -> txbuf,
				&e_buffer[e_len]);
		    }
		    else
		    {
			*(rc - 1) = '\0';
			sprintf (_estakbot, "%s", field_ptr -> txbuf);
		    }
		    complete (field_ptr, _estakbot);
		    if (field_ptr -> cmflg & CMNOP)
		    {
			error_fields = error3;
			return;
		    }
		}
		else
		{
		    complete (field_ptr, &e_buffer[e_len]);
		    if (field_ptr -> cmflg & CMNOP)
		    {
			error_fields = error3;
			return;
		    }
		}
	    }
	}
	if (field_ptr -> cmflg & CMCMP)
	{
	    field_ptr -> cmflg |= CMREP;
	}

	return;
    }
    else
    {
	field_ptr -> cmflg |= CMNOP;
	if (count > 0)
	{
	    field_ptr -> cmflg |= CMNUQ;
	    error_fields = error1;
	}
	else
	{
	    error_fields = error2;
	}

	return;
    }
}

/*
 * Check a string for a list of chars
 */
s_any (str1, str2)
char   *str1;
char   *str2;
{
    while (*str1 != '\0')
    {
	if (any (*str1, str2))
	    return (TRUE);
	str1++;
    }
    return (FALSE);
}

any (c, s)
register char   c;
char   *s;
{
    register char   d;

    while (d = *s++)
    {
	if (d == c)
	{
	    return (TRUE);
	}
    }
    return (FALSE);
}

/*
 *	Stack routines to interact with the expand routine from the
 *	6.0 shell.
 */
char   *
endstak (argp)
register char  *argp;
{
    register char  *oldstak;

    *argp++ = 0;
    oldstak = _estakbot;
    _estakbot = _estaktop = (char *) round (argp, BYTESPERWORD);
    return (oldstak);
}

char   *
locstak ()
{
    if      (_estack + EXP_BUFFER - _estakbot < BRKINCR)
    {
	        longjmp (_ejump, TRUE);
    }
    return (_estakbot);
}

/*
 * Simple sort for argnods
 */
arg_sort (count)
register int count;
{
	extern int cmp_argnods ();
	extern struct argnod   *gchain;
	register struct argnod *xchain;
	register int index;
	struct argnod *x[512];		/* Only sort the first 512 names */
	struct argnod *save_ptr;

	if (count < 2)
		return;

	if (count > 512)
		count = 512;

	for (index = 0, xchain = gchain; index < count; index++)
	{
		x[index] = xchain;
		xchain = xchain -> argnxt;
	}

	gsort (x, &x[count], cmp_argnods);

	gchain = x[0];
	x[count - 1] -> argnxt = xchain;

	for (index = 1, xchain = gchain; index < count; index++)
	{
		xchain -> argnxt = x[index];
		xchain = x[index];
	}
}

static int
cmp_argnods (arg1, arg2)
register struct argnod *arg1;
register struct argnod *arg2;
{
	return (strcmp (arg1 -> argval, arg2 -> argval));
}
