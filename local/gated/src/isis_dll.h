/*
 *  isis_dll.h,v 1.11 1993/01/07 22:39:13 jch Exp
 */

/* %(Copyright.header) */

#ifndef _dll_h
#define _dll_h
/*
 *	Generic doubly-linked list manipulation macros
 */
typedef struct _DLList {
	struct _DLList *forw, *back;
} DLList;

/* Iterate forward through the DLList */
#define IterateDLListForw(ptr, head, cast)\
	for (ptr = (cast)((head)->forw); \
		ptr != (cast)((head)); \
		ptr = ((cast)((DLList *)ptr)->forw))

/* Iterate backward through the DLList */
#define IterateDLListBack(ptr, head, cast)\
	for (ptr = (cast)((head)->back); \
		ptr != (cast)((head)); \
		ptr = ((cast)((DLList *)ptr)->back))

/* return the next item forward */
#define DLListForw(elem, cast)\
	((cast)(((DLList *)(elem))->forw))

/* return the next item backward */
#define DLListBack(elem, cast)\
	((cast)(((DLList *)(elem))->back))

/* return next item forward, or NULL if at end of list */
#define DLListNext(elem, head, cast)\
	((DLListForw(elem, DLList *) == head) ? ((cast)(NULL)) : (DLListForw(elem, cast)))

/* return next item backward, or NULL if at end of list */
#define DLListPrev(elem, head, cast)\
	((DLListBack(elem, DLList *) == head) ? ((cast)(NULL)) : (DLListBack(elem, cast)))

#define DLListEmpty(head)\
	(((DLList *)head)->forw == head)

#define DLLInsque(elem, prev)\
	INSQUE(elem, prev);

#define DLLRemque(elem)\
	REMQUE(elem);

#define DLLInit(links)\
	((links)->forw = (links)->back = (DLList *)(links))

#endif 	/* _dll_h */


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
