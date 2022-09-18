h17422
s 00002/00002/00408
d D 8.2 95/04/28 17:07:57 christos 8 7
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00408
d D 8.1 93/06/06 15:14:09 bostic 7 6
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00009/00009/00401
d D 5.6 93/05/24 14:45:26 bostic 6 5
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00048/00055/00362
d D 5.5 90/12/28 18:06:54 bostic 5 4
c replace hash.c; speedup/cleanup from Chris Torek
e
s 00001/00011/00416
d D 5.4 90/06/01 17:06:52 bostic 4 3
c new copyright notice
e
s 00004/00004/00423
d D 5.3 90/03/19 09:51:29 bostic 3 2
c replace malloc with emalloc
e
s 00026/00016/00401
d D 5.2 90/03/11 16:50:53 bostic 2 1
c add Berkeley specific copyright notices
e
s 00417/00000/00000
d D 5.1 90/03/11 16:47:59 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * buf.c --
 *	Functions for automatically-expanded buffers.
E 2
I 2
/*
D 7
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 7
I 7
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 7
 * Copyright (c) 1989 by Berkeley Softworks
 * All rights reserved.
E 2
 *
D 2
 * Copyright (c) 1987 by the Regents of the University of California
E 2
I 2
 * This code is derived from software contributed to Berkeley by
 * Adam de Boor.
E 2
 *
D 2
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies.  The University of California
 * makes no representations about the suitability of this
 * software for any purpose.  It is provided "as is" without
 * express or implied warranty.
 *
 *
E 2
I 2
D 4
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 4
I 4
 * %sccs.include.redist.c%
E 4
E 2
 */
I 2

E 2
#ifndef lint
D 2
static char rcsid[] =
"$Id: buf.c,v 1.4 89/06/13 17:24:44 adam Exp $ SPRITE (Berkeley)";
#endif lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*-
 * buf.c --
 *	Functions for automatically-expanded buffers.
 */
E 2

#include    "sprite.h"
I 6
#include    "make.h"
E 6
#include    "buf.h"

D 5
typedef struct {
    int	    size; 	/* Current size of the buffer */
    Byte    *buffer;	/* The buffer itself */
    Byte    *inPtr;	/* Place to write to */
    Byte    *outPtr;	/* Place to read from */
} Buf, *BufPtr;

E 5
#ifndef max
#define max(a,b)  ((a) > (b) ? (a) : (b))
#endif

/*
 * BufExpand --
 * 	Expand the given buffer to hold the given number of additional
 *	bytes.
 *	Makes sure there's room for an extra NULL byte at the end of the
 *	buffer in case it holds a string.
 */
#define BufExpand(bp,nb) \
D 5
 	if (((bp)->size - ((bp)->inPtr - (bp)->buffer)) < (nb)+1) {\
E 5
I 5
 	if (bp->left < (nb)+1) {\
E 5
	    int newSize = (bp)->size + max((nb)+1,BUF_ADD_INC); \
	    Byte  *newBuf = (Byte *) realloc((bp)->buffer, newSize); \
	    \
	    (bp)->inPtr = newBuf + ((bp)->inPtr - (bp)->buffer); \
	    (bp)->outPtr = newBuf + ((bp)->outPtr - (bp)->buffer);\
	    (bp)->buffer = newBuf;\
	    (bp)->size = newSize;\
I 5
	    (bp)->left = newSize - ((bp)->inPtr - (bp)->buffer);\
E 5
	}

#define BUF_DEF_SIZE	256 	/* Default buffer size */
#define BUF_ADD_INC	256 	/* Expansion increment when Adding */
#define BUF_UNGET_INC	16  	/* Expansion increment when Ungetting */

/*-
 *-----------------------------------------------------------------------
D 5
 * Buf_AddByte --
 *	Add a single byte to the buffer.
E 5
I 5
 * Buf_OvAddByte --
 *	Add a single byte to the buffer.  left is zero or negative.
E 5
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The buffer may be expanded.
 *
 *-----------------------------------------------------------------------
 */
void
D 5
Buf_AddByte (buf, byte)
    Buffer  buf;
E 5
I 5
Buf_OvAddByte (bp, byte)
    register Buffer bp;
E 5
D 6
    Byte    byte;
E 6
I 6
    int    byte;
E 6
{
D 5
    register BufPtr  bp = (BufPtr) buf;
E 5
D 8

E 8
I 8
    int nbytes = 1;
E 8
I 5
    bp->left = 0;
E 5
D 8
    BufExpand (bp, 1);
E 8
I 8
    BufExpand (bp, nbytes);
E 8

D 5
    *bp->inPtr = byte;
    bp->inPtr += 1;
E 5
I 5
    *bp->inPtr++ = byte;
    bp->left--;
E 5

    /*
     * Null-terminate
     */
    *bp->inPtr = 0;
}

/*-
 *-----------------------------------------------------------------------
 * Buf_AddBytes --
 *	Add a number of bytes to the buffer.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	Guess what?
 *
 *-----------------------------------------------------------------------
 */
void
D 5
Buf_AddBytes (buf, numBytes, bytesPtr)
    Buffer  buf;
E 5
I 5
Buf_AddBytes (bp, numBytes, bytesPtr)
    register Buffer bp;
E 5
    int	    numBytes;
    Byte    *bytesPtr;
{
D 5
    register BufPtr  bp = (BufPtr) buf;
E 5

    BufExpand (bp, numBytes);

D 6
    bcopy (bytesPtr, bp->inPtr, numBytes);
E 6
I 6
    memcpy (bp->inPtr, bytesPtr, numBytes);
E 6
    bp->inPtr += numBytes;
I 5
    bp->left -= numBytes;
E 5

    /*
     * Null-terminate
     */
    *bp->inPtr = 0;
}

/*-
 *-----------------------------------------------------------------------
 * Buf_UngetByte --
 *	Place the byte back at the beginning of the buffer.
 *
 * Results:
 *	SUCCESS if the byte was added ok. FAILURE if not.
 *
 * Side Effects:
 *	The byte is stuffed in the buffer and outPtr is decremented.
 *
 *-----------------------------------------------------------------------
 */
void
D 5
Buf_UngetByte (buf, byte)
    Buffer  buf;
E 5
I 5
Buf_UngetByte (bp, byte)
    register Buffer bp;
E 5
D 6
    Byte    byte;
E 6
I 6
    int    byte;
E 6
{
D 5
    register BufPtr	bp = (BufPtr) buf;
E 5

    if (bp->outPtr != bp->buffer) {
D 5
	bp->outPtr -= 1;
E 5
I 5
	bp->outPtr--;
E 5
	*bp->outPtr = byte;
    } else if (bp->outPtr == bp->inPtr) {
	*bp->inPtr = byte;
D 5
	bp->inPtr += 1;
E 5
I 5
	bp->inPtr++;
	bp->left--;
E 5
	*bp->inPtr = 0;
    } else {
	/*
	 * Yech. have to expand the buffer to stuff this thing in.
	 * We use a different expansion constant because people don't
	 * usually push back many bytes when they're doing it a byte at
	 * a time...
	 */
	int 	  numBytes = bp->inPtr - bp->outPtr;
	Byte	  *newBuf;

D 3
	newBuf = (Byte *) malloc (bp->size + BUF_UNGET_INC);
E 3
I 3
	newBuf = (Byte *)emalloc(bp->size + BUF_UNGET_INC);
E 3
D 5
	bcopy ((Address)bp->outPtr,
			(Address)(newBuf+BUF_UNGET_INC), numBytes+1);
E 5
I 5
D 6
	bcopy ((char *)bp->outPtr,
			(char *)(newBuf+BUF_UNGET_INC), numBytes+1);
E 6
I 6
	memcpy ((char *)(newBuf+BUF_UNGET_INC), (char *)bp->outPtr, numBytes+1);
E 6
E 5
	bp->outPtr = newBuf + BUF_UNGET_INC;
	bp->inPtr = bp->outPtr + numBytes;
D 5
	free ((Address)bp->buffer);
E 5
I 5
	free ((char *)bp->buffer);
E 5
	bp->buffer = newBuf;
	bp->size += BUF_UNGET_INC;
I 5
	bp->left = bp->size - (bp->inPtr - bp->buffer);
E 5
	bp->outPtr -= 1;
	*bp->outPtr = byte;
    }
}

/*-
 *-----------------------------------------------------------------------
 * Buf_UngetBytes --
 *	Push back a series of bytes at the beginning of the buffer.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	outPtr is decremented and the bytes copied into the buffer.
 *
 *-----------------------------------------------------------------------
 */
void
D 5
Buf_UngetBytes (buf, numBytes, bytesPtr)
    Buffer  buf;
E 5
I 5
Buf_UngetBytes (bp, numBytes, bytesPtr)
    register Buffer bp;
E 5
    int	    numBytes;
    Byte    *bytesPtr;
{
D 5
    register BufPtr	bp = (BufPtr) buf;
E 5

    if (bp->outPtr - bp->buffer >= numBytes) {
	bp->outPtr -= numBytes;
D 6
	bcopy (bytesPtr, bp->outPtr, numBytes);
E 6
I 6
	memcpy (bp->outPtr, bytesPtr, numBytes);
E 6
    } else if (bp->outPtr == bp->inPtr) {
D 5
	Buf_AddBytes (buf, numBytes, bytesPtr);
E 5
I 5
	Buf_AddBytes (bp, numBytes, bytesPtr);
E 5
    } else {
	int 	  curNumBytes = bp->inPtr - bp->outPtr;
	Byte	  *newBuf;
	int 	  newBytes = max(numBytes,BUF_UNGET_INC);

D 3
	newBuf = (Byte *) malloc (bp->size + newBytes);
E 3
I 3
	newBuf = (Byte *)emalloc (bp->size + newBytes);
E 3
D 5
	bcopy((Address)bp->outPtr, (Address)(newBuf+newBytes), curNumBytes+1);
E 5
I 5
D 6
	bcopy((char *)bp->outPtr, (char *)(newBuf+newBytes), curNumBytes+1);
E 6
I 6
	memcpy((char *)(newBuf+newBytes), (char *)bp->outPtr, curNumBytes+1);
E 6
E 5
	bp->outPtr = newBuf + newBytes;
	bp->inPtr = bp->outPtr + curNumBytes;
D 5
	free ((Address)bp->buffer);
E 5
I 5
	free ((char *)bp->buffer);
E 5
	bp->buffer = newBuf;
	bp->size += newBytes;
I 5
	bp->left = bp->size - (bp->inPtr - bp->buffer);
E 5
	bp->outPtr -= numBytes;
D 5
	bcopy ((Address)bytesPtr, (Address)bp->outPtr, numBytes);
E 5
I 5
D 6
	bcopy ((char *)bytesPtr, (char *)bp->outPtr, numBytes);
E 6
I 6
	memcpy ((char *)bp->outPtr, (char *)bytesPtr, numBytes);
E 6
E 5
    }
}

/*-
 *-----------------------------------------------------------------------
 * Buf_GetByte --
 *	Return the next byte from the buffer. Actually returns an integer.
 *
 * Results:
 *	Returns BUF_ERROR if there's no byte in the buffer, or the byte
 *	itself if there is one.
 *
 * Side Effects:
 *	outPtr is incremented and both outPtr and inPtr will be reset if
 *	the buffer is emptied.
 *
 *-----------------------------------------------------------------------
 */
int
D 5
Buf_GetByte (buf)
    Buffer  buf;
E 5
I 5
Buf_GetByte (bp)
    register Buffer bp;
E 5
{
D 5
    BufPtr  bp = (BufPtr) buf;
E 5
    int	    res;

    if (bp->inPtr == bp->outPtr) {
	return (BUF_ERROR);
    } else {
	res = (int) *bp->outPtr;
	bp->outPtr += 1;
	if (bp->outPtr == bp->inPtr) {
	    bp->outPtr = bp->inPtr = bp->buffer;
D 5
	    bp->inPtr = 0;
E 5
I 5
	    bp->left = bp->size;
	    *bp->inPtr = 0;
E 5
	}
	return (res);
    }
}

/*-
 *-----------------------------------------------------------------------
 * Buf_GetBytes --
 *	Extract a number of bytes from the buffer.
 *
 * Results:
 *	The number of bytes gotten.
 *
 * Side Effects:
 *	The passed array is overwritten.
 *
 *-----------------------------------------------------------------------
 */
int
D 5
Buf_GetBytes (buf, numBytes, bytesPtr)
    Buffer  buf;
E 5
I 5
Buf_GetBytes (bp, numBytes, bytesPtr)
    register Buffer bp;
E 5
    int	    numBytes;
    Byte    *bytesPtr;
{
D 5
    BufPtr  bp = (BufPtr) buf;
E 5
    
    if (bp->inPtr - bp->outPtr < numBytes) {
	numBytes = bp->inPtr - bp->outPtr;
    }
D 6
    bcopy (bp->outPtr, bytesPtr, numBytes);
E 6
I 6
    memcpy (bytesPtr, bp->outPtr, numBytes);
E 6
    bp->outPtr += numBytes;

    if (bp->outPtr == bp->inPtr) {
	bp->outPtr = bp->inPtr = bp->buffer;
I 5
	bp->left = bp->size;
E 5
	*bp->inPtr = 0;
    }
    return (numBytes);
}

/*-
 *-----------------------------------------------------------------------
 * Buf_GetAll --
 *	Get all the available data at once.
 *
 * Results:
 *	A pointer to the data and the number of bytes available.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
Byte *
D 5
Buf_GetAll (buf, numBytesPtr)
    Buffer  buf;
E 5
I 5
Buf_GetAll (bp, numBytesPtr)
    register Buffer bp;
E 5
    int	    *numBytesPtr;
{
D 5
    BufPtr  bp = (BufPtr)buf;
E 5

    if (numBytesPtr != (int *)NULL) {
	*numBytesPtr = bp->inPtr - bp->outPtr;
    }
    
    return (bp->outPtr);
}

/*-
 *-----------------------------------------------------------------------
 * Buf_Discard --
 *	Throw away bytes in a buffer.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The bytes are discarded. 
 *
 *-----------------------------------------------------------------------
 */
void
D 5
Buf_Discard (buf, numBytes)
    Buffer  buf;
E 5
I 5
Buf_Discard (bp, numBytes)
    register Buffer bp;
E 5
    int	    numBytes;
{
D 5
    register BufPtr	bp = (BufPtr) buf;
E 5

    if (bp->inPtr - bp->outPtr <= numBytes) {
	bp->inPtr = bp->outPtr = bp->buffer;
I 5
	bp->left = bp->size;
E 5
	*bp->inPtr = 0;
    } else {
	bp->outPtr += numBytes;
    }
}

/*-
 *-----------------------------------------------------------------------
 * Buf_Size --
 *	Returns the number of bytes in the given buffer. Doesn't include
 *	the null-terminating byte.
 *
 * Results:
 *	The number of bytes.
 *
 * Side Effects:
 *	None.
 *
 *-----------------------------------------------------------------------
 */
int
Buf_Size (buf)
    Buffer  buf;
{
D 5
    return (((BufPtr)buf)->inPtr - ((BufPtr)buf)->outPtr);
E 5
I 5
    return (buf->inPtr - buf->outPtr);
E 5
}

/*-
 *-----------------------------------------------------------------------
 * Buf_Init --
 *	Initialize a buffer. If no initial size is given, a reasonable
 *	default is used.
 *
 * Results:
 *	A buffer to be given to other functions in this library.
 *
 * Side Effects:
 *	The buffer is created, the space allocated and pointers
 *	initialized.
 *
 *-----------------------------------------------------------------------
 */
Buffer
Buf_Init (size)
    int	    size; 	/* Initial size for the buffer */
{
D 5
    BufPtr  bp;	  	/* New Buffer */
E 5
I 5
    Buffer bp;	  	/* New Buffer */
E 5

D 3
    bp = (Buf *) malloc(sizeof(Buf));
E 3
I 3
D 5
    bp = (Buf *)emalloc(sizeof(Buf));
E 5
I 5
    bp = (Buffer)emalloc(sizeof(*bp));
E 5
E 3

    if (size <= 0) {
	size = BUF_DEF_SIZE;
    }
D 5
    bp->size = size;
D 3
    bp->buffer = (Byte *) malloc (size);
E 3
I 3
    bp->buffer = (Byte *)emalloc (size);
E 5
I 5
    bp->left = bp->size = size;
    bp->buffer = (Byte *)emalloc(size);
E 5
E 3
    bp->inPtr = bp->outPtr = bp->buffer;
    *bp->inPtr = 0;

D 5
    return ((Buffer) bp);
E 5
I 5
    return (bp);
E 5
}

/*-
 *-----------------------------------------------------------------------
 * Buf_Destroy --
 *	Nuke a buffer and all its resources.
 *
 * Results:
 *	None.
 *
 * Side Effects:
 *	The buffer is freed.
 *
 *-----------------------------------------------------------------------
 */
void
Buf_Destroy (buf, freeData)
    Buffer  buf;  	/* Buffer to destroy */
    Boolean freeData;	/* TRUE if the data should be destroyed as well */
{
D 5
    BufPtr  bp = (BufPtr) buf;
E 5
    
    if (freeData) {
D 5
	free ((Address)bp->buffer);
E 5
I 5
	free ((char *)buf->buffer);
E 5
    }
D 5
    free ((Address)bp);
E 5
I 5
    free ((char *)buf);
E 5
}
E 1
