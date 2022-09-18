/* $XConsortium: var.h,v 5.1 91/02/16 10:00:00 rws Exp $ */

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
 *  var.h - 
 * header file for var.c, containing variable manipulation functions
 * for NewT.
 * The first two functions, set and lookup, are general, and may
 * be easily replaced; set_val and value are looper-specific, using
 * the looper's concept of a variable (i.e. beginning with a "@")
 * to differentiate between constants and variables.
*/


typedef struct VALTAB_STRUCT {
	char *varname;
	char *value;
	struct VALTAB_STRUCT *next;
} VALTAB;


int set();			/* sets a variable value */
char *lookup();			/* looks up a variable */
int set_val();			/* sets a looper variable to a constant */
char *value();			/* looks up a looper variable/literal */



#define is_var(s)	(s[0]=='@')
