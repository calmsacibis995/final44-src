/* $XConsortium: pexUtils.h,v 5.1 91/02/16 09:57:36 rws Exp $ */

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

#ifndef PEXUTILS_H
#define PEXUTILS_H

#include "ddpex.h"

/* declarations for the utilities in pexUtils.c */
extern listofObj  *puCreateList();
extern void	puDeleteList();
extern short	puInList();
extern short	puAddToList();
extern short	puRemoveFromList();
extern short	puCopyList();
extern short	puMergeLists();
extern int	puBuffRealloc();
extern void	puInitList();
extern int	puCountList();

/* useful macros to use with lists */
#define PU_TRUE	1
#define PU_FALSE 0

#define	PU_BAD_LIST	-1	/* error returned by list utilities */
 
#define PU_EMPTY_LIST( plist )  \
	(plist)->numObj = 0

#define PU_REMOVE_LAST_OBJ( plist )     \
	if ( (plist)->numObj > 0 )      (plist)->numObj--

/* useful macros to use with ddBuffer */
#define PU_BUF_HDR_SIZE(pBuffer) \
	(int) (((char *) pBuffer->pBuf) - ((char *) pBuffer->pHead))

#define PU_BUF_TOO_SMALL(pBuffer,minSize) \
	((minSize) > ((pBuffer->bufSize) - PU_BUF_HDR_SIZE(pBuffer) + 1))

#define PU_CHECK_BUFFER_SIZE( pBuffer, size ) 				\
    if ( PU_BUF_TOO_SMALL((pBuffer), (size)) )				\
	if (puBuffRealloc((pBuffer), (ddULONG)(size)) != Success )	\
	{								\
	    (pBuffer)->dataSize = 0;					\
	    return( BadAlloc );						\
        }

/*
    useful macro for ensuring that lists of shorts allocate full longwords
 */
#define MAKE_EVEN(_n)  \
	( (_n)%2 ? (_n)+1 : (_n) )


#endif	/* PEXUTILS_H */
