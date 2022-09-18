/* $XConsortium: assure.h,v 5.2 91/02/18 11:15:44 rws Exp $ */

/***********************************************************
Copyright 1989, 1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

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

/* Must #include <stdio.h> */
#ifdef DEBUG
extern	int	phigs_self_check;	/* could use each bit separately */

# define assure(ex)						\
		{if (!(ex))					\
			fprintf(stderr,				\
			"Assertion failed: file %s, line %d:\n  ex \n",\
				__FILE__, __LINE__);}
# define _assure(ex)	assure(ex)
# define ASSURE(code)	code
# define IFDEBUG(code)	code
# define IFNDEBUG(code)
#else
# define _assure(ex) ;
# define  assure(ex) ;
# define ASSURE(code)
# define IFDEBUG(code)
# define IFNDEBUG(code)	code
#endif
