/* @(#)grem2.h	1.2	4/18/83
 *      This is an include file for database macros.
 */
#define DBNextElt(elt) elt->nextelt
#define DBNextofSet(elt) elt->setnext
#define DBNullelt(elt) ( elt == NULL )
#define Nullpoint(pt)  ( pt->x == nullpt )
#define PTNextPoint(pt) pt->nextpt
