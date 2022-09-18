
/* $XConsortium: var.c,v 5.1 91/02/16 09:59:59 rws Exp $ */

/*****************************************************************
Copyright (c) 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/



/* 
 * var.c
 * variable handling routines for NewT.
 *
 * These routines handle the setting and lookup of simple string variables.
 *
 * The routines set, and lookup have no requirements for what variable
 * names are supposed to look like, so any storage method may safely
 * be substituted inside them.  
 *
 * the function value() knows  about the looper's
 * variable name convention (i.e. that variables start with "@")
 * and evaluates its argument accordingly -- leaving it alone if it
 * is a constant, looking it up (perhaps recursively) if it is a variable.
 *
*/
#include <stdio.h>
#include <string.h>
#include "looper.h"
#include "var.h"

static VALTAB *val_table;


/* store a value under the name varname, removing a previous value if
 * it was there.
 * note that set does not allocate new space for variable names or
 * values.
*/
set(varname, value)
    char *varname, *value;
{
	VALTAB *entry ;

	/* search for previous values */
	for (entry=val_table;
	     entry != NULL && strcmp(entry->varname,varname) != 0;
	     entry=entry->next);
	if (entry==NULL) {
		/* no previous value: make new entry, add to front of list */
		entry = (VALTAB *) malloc(sizeof(VALTAB));
		entry->next = val_table;
		entry->varname = varname;
		val_table = entry;
	}
	entry->value = value;
}

/* return a pointer to the string value of the given variable, or 
 * NULL if not found 
*/
char *
lookup(varname)
    char *varname;
{
	VALTAB *entry;

	for (entry=val_table; entry != NULL; entry=entry->next) {
		if (strcmp(entry->varname,varname) == 0) {
			return(entry->value);
		}
	}
	/* if we got this far, it's not in list */
	return(NULL);
}


/* looper function for setting variable values.  If its second argument
 * is a variable, it looks up its value before making the assignment, 
 * to eliminate surprises due to reference-by-name (i.e. changing 
 * original variable's value and having it effect all variables
 * assigned that variable's value).  If desired, this effect could still
 * be achieved using "set".
*/
int
set_val(varname, value)
    char *varname, *value;
{
	char *base_value;

	if (is_var(value)) { 
		base_value = lookup(value);
		if (base_value==NULL) {
			fprintf(stderr,"ERROR-variable has no value\n");
			exit(1);
		}
		set(varname, base_value);
	} else {
		set (varname, value);
	}
}

/* looper function to return the value of a constant or variable.
 * if it's not a looper variable (i.e. has no leading "@"), just return
 * the argument.  Otherwise, recursively look up the value.
*/
char *
value(name)
  char *name;
{
	if (name == NULL) {
		return(NULL);
	} else if (is_var(name)) {
		return(value(lookup(name)));
	} else {
		return(name);
	}
}


/*********  Just a trial main, for debugging ******
main(argc, argv)
   int argc;
   char *argv;
{

	set_val("@arg1", "hello");
	set_val("@arg2", "world");
	set_val("@really1", "@arg1");
	set_val("@also1", "@really1");
	printf("%s, %s, %s, %s, %s\n", value("@arg1"), value("@arg2"),
			value("@really1"), value("@also1"),
			value("really"));
	set_val("@arg1", "goodbye");
	printf("%s, %s, %s, %s, %s\n", value("@arg1"), value("@arg2"),
			value("@really1"), value("@also1"),
			value("really"));
}
**********/
