h08082
s 00047/00000/00000
d D 5.1 90/05/02 08:39:06 bostic 1 0
c date and time created 90/05/02 08:39:06 by bostic
e
u
U
t
T
I 1
/* alloc.c - version 1.0.2 */
#ifdef LINT

/*
   a ridiculous definition, suppressing
	"possible pointer alignment problem" for (long *) malloc()
	"enlarg defined but never used"
	"ftell defined (in <stdio.h>) but never used"
   from lint
*/
#include <stdio.h>
long *
alloc(n) unsigned n; {
long dummy = ftell(stderr);
	if(n) dummy = 0;	/* make sure arg is used */
	return(&dummy);
}

#else

extern char *malloc();
extern char *realloc();

long *
alloc(lth)
register unsigned lth;
{
	register char *ptr;

	if(!(ptr = malloc(lth)))
		panic("Cannot get %d bytes", lth);
	return((long *) ptr);
}

long *
enlarge(ptr,lth)
register char *ptr;
register unsigned lth;
{
	register char *nptr;

	if(!(nptr = realloc(ptr,lth)))
		panic("Cannot reallocate %d bytes", lth);
	return((long *) nptr);
}

#endif LINT
E 1
