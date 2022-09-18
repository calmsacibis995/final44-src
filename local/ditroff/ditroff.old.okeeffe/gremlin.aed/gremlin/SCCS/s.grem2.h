h35771
s 00001/00002/00007
d D 1.2 83/04/18 15:23:17 slatteng 2 1
c DLS taekeover
e
s 00009/00000/00000
d D 1.1 83/04/18 13:52:11 slatteng 1 0
c date and time created 83/04/18 13:52:11 by slatteng
e
u
U
t
T
I 1
D 2

/* grem2.h -
E 2
I 2
/* %W%	%G%
E 2
 *      This is an include file for database macros.
 */
#define DBNextElt(elt) elt->nextelt
#define DBNextofSet(elt) elt->setnext
#define DBNullelt(elt) ( elt == NULL )
#define Nullpoint(pt)  ( pt->x == nullpt )
#define PTNextPoint(pt) pt->nextpt
E 1
