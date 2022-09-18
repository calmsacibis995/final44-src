h60743
s 00046/00000/00000
d D 5.1 90/10/11 11:35:54 bostic 1 0
c date and time created 90/10/11 11:35:54 by bostic
e
u
U
t
T
I 1
/*
 * A safer saner malloc, for careless programmers
 * $Revision: 6.8 $
 */

#include <stdio.h>
#include <curses.h>
#include "sc.h"

extern char *malloc();

#ifdef SYSV3
extern void free();
extern void exit();
#endif

char *
xmalloc(n)
unsigned n;
{
register char *ptr;

if ((ptr = malloc(n + sizeof(double))) == NULL)
    fatal("xmalloc: no memory");
*((int *) ptr) = 12345;		/* magic number */
return(ptr + sizeof(double));
}

xfree(p)
char *p;
{
if (p == NULL)
    fatal("xfree: NULL");
p -= sizeof(double);
if (*((int *) p) != 12345)
    fatal("xfree: storage not malloc'ed");
free(p);
}

fatal(str)
char *str;
{
    deraw();
    (void) fprintf(stderr,"%s\n", str);
    exit(1);
}
E 1
