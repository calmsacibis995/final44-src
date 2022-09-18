/* $XConsortium: miStruct.h,v 5.3 92/11/17 17:32:06 hersh Exp $ */


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

#ifndef MISTRUCT_H
#define MISTRUCT_H

#include "X.h"
#include "PEXproto.h"
#include "ddpex.h"

typedef ddpex4rtn	(*cssTableType)();

typedef struct {
	ddUSHORT		elementType;
	ddUSHORT		pexOClength;
	/* concatenate imp. dep. data definitions here */
	/* sample server definitions are listed later in this file */
} miGenericStr;
	
typedef struct _miCSSElement {
	struct _miCSSElement	*prev, *next;
	diStructHandle		pStruct;
	miGenericStr		element;	/* replace this with imp.
						 * dep. data structure */
} miGenericElementStr, *miGenericElementPtr;

typedef struct _miCSSElementHead {
	struct _miCSSElementHead	*next, *prev;
} miElementHeadStr;

#define	EL_HEAD_SIZE	sizeof(miElementHeadStr)

typedef struct _miStructHeader {
	/* the resource id is in the dipex resource structure */
	ddUSHORT		editMode;
	ddULONG			numElements;
	ddULONG			totalSize;	/* of elements when in PEX format */
	miGenericElementPtr	pZeroElement;	/* dummy */
	miGenericElementPtr	pLastElement;	/* dummy */
	miGenericElementPtr	pCurrElement;
	ddLONG			currElementOffset;
	listofObj		*parents;
	listofObj		*children;
	listofObj		*wksPostedTo;	/* directly posted to */
	listofObj		*wksAppearOn;	/* indirectly, thru inherit.*/
	ddULONG			refCount;	/* for search context & pick measure */
	ddBOOL			freeFlag;	/* keep structure until no sc or
						 * pick measure uses it */
} miStructStr, *miStructPtr;

/* sample server element definitions */

/* all fixed sized elements use the PEX protocol format and are not
 * defined explicitely 
 */

/*
 * See ddpex2.h for data definitions for the others
 */

/* traverser state info. passed to level 4 traverser which is used by
 * level 4 structure traversal and by level 3 mixed mode traversal.
 * When following initial path before pick/search, don't want to
 * follow all execute structure elements, only follow ones in search
 * path. Also, when following initial path, don't want to call
 * primitive OCS because actual pick/search isn't done until
 * start path has been traversed.  Use this enum value to determine
 * when to follow exec.str element and when to bypass primitives
 */
typedef enum {
	ES_YES = 0,		/* do 'normal' traversal */
	ES_POP = 1,		/* pick or search is done, pop out of traverser */
	ES_FOLLOW_PICK = 2,	/* follow initial pick path before picking */
	ES_FOLLOW_SEARCH = 3	/* follow initial search path before search */
} miExecStrState;

/* added to allow SI to do pick last */
typedef struct _miPPLevel {
  ddPickPath pp;
  struct _miPPLevel *up;
} miPPLevel;


/*
 * level 3 traversal doesn't do picking or search, so it ALWAYS sets
 * exec_str_flag to YES and the element pointers to NULL
 */
typedef struct {
	miExecStrState	exec_str_flag;
	ddULONG		pickId;
	ddULONG		ROCoffset;
	ddPickPath	*p_curr_pick_el;
	ddElementRef	*p_curr_sc_el;
	ddSHORT		max_depth;	/* max depth reached in pick or search */
        miPPLevel       *p_pick_path;
}  miTraverserState;

#endif	/* MISTRUCT_H */
