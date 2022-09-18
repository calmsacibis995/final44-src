h00701
s 00012/00012/00042
d D 8.2 95/04/28 17:07:58 christos 7 6
c Updated to the latest version from the NetBSD source
e
s 00002/00002/00052
d D 8.1 93/06/06 15:14:13 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00015/00016/00039
d D 5.5 93/05/24 14:45:27 bostic 5 4
c update, bug fix, ANSI C, lint from Christos Zoulas
c see SCCS/README.christos for details
e
s 00015/00002/00040
d D 5.4 90/12/28 18:06:56 bostic 4 3
c replace hash.c; speedup/cleanup from Chris Torek
e
s 00001/00011/00041
d D 5.3 90/06/01 17:06:59 bostic 3 2
c new copyright notice
e
s 00024/00012/00028
d D 5.2 90/03/11 15:59:15 bostic 2 1
c add Berkeley specific copyright
e
s 00040/00000/00000
d D 5.1 90/03/11 15:58:54 bostic 1 0
c release 2.1 of pmake
e
u
U
t
T
I 1
D 2
/*-
 * buf.h --
 *	Header for users of the buf library.
E 2
I 2
/*
D 6
 * Copyright (c) 1988, 1989, 1990 The Regents of the University of California.
 * Copyright (c) 1988, 1989 by Adam de Boor
E 6
I 6
 * Copyright (c) 1988, 1989, 1990, 1993
 *	The Regents of the University of California.  All rights reserved.
E 6
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
E 2
I 2
D 3
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
E 3
I 3
 * %sccs.include.redist.c%
E 3
E 2
 *
D 2
 *	"$Id: buf.h,v 2.1 89/07/03 15:49:36 adam Exp $ SPRITE (Berkeley)"
E 2
I 2
 *	%W% (Berkeley) %G%
 */

/*-
 * buf.h --
 *	Header for users of the buf library.
E 2
 */

#ifndef _BUF_H
#define _BUF_H

#include    "sprite.h"

D 4
typedef struct Buffer *Buffer;
E 4
D 7
typedef unsigned char Byte;
E 7
I 7
typedef char Byte;
E 7

I 4
typedef struct Buffer {
    int	    size; 	/* Current size of the buffer */
    int     left;	/* Space left (== size - (inPtr - buffer)) */
    Byte    *buffer;	/* The buffer itself */
    Byte    *inPtr;	/* Place to write to */
    Byte    *outPtr;	/* Place to read from */
} *Buffer;

E 4
D 5
Buffer	    	  Buf_Init();	    /* Initialize a buffer */
void	    	  Buf_Destroy();    /* Destroy a buffer */
D 4
void	    	  Buf_AddByte();    /* Add a single byte to a buffer */
E 4
void	    	  Buf_AddBytes();   /* Add a range of bytes to a buffer */
int	    	  Buf_GetByte();    /* Get a byte from a buffer */
int	    	  Buf_GetBytes();   /* Get multiple bytes */
void		  Buf_UngetByte();  /* Push a byte back into the buffer */
void		  Buf_UngetBytes(); /* Push many bytes back into the buf */
Byte	    	  *Buf_GetAll();    /* Get them all */
void	    	  Buf_Discard();    /* Throw away some of the bytes */
int	    	  Buf_Size();	    /* See how many are there */
I 4

E 5
/* Buf_AddByte adds a single byte to a buffer. */
#define	Buf_AddByte(bp, byte) \
D 5
	(--(bp)->left <= 0 ? Buf_OvAddByte(bp, byte) : \
		(void)(*(bp)->inPtr++ = (byte), *(bp)->inPtr = 0))
E 5
I 5
	(void) (--(bp)->left <= 0 ? Buf_OvAddByte(bp, byte), 1 : \
		(*(bp)->inPtr++ = (byte), *(bp)->inPtr = 0), 1)
E 5

D 5
void	Buf_OvAddByte();		/* adds a byte when buffer overflows */
E 4

E 5
#define BUF_ERROR 256

D 5
#endif _BUF_H
E 5
I 5
D 7
void	 Buf_AddBytes __P((Buffer, int, Byte *));
void	 Buf_Destroy __P((Buffer, Boolean));
void	 Buf_Discard __P((Buffer, int));
Byte	*Buf_GetAll __P((Buffer, int *));
int	 Buf_GetByte __P((Buffer));
int	 Buf_GetBytes __P((Buffer, int, Byte *));
Buffer	 Buf_Init __P((int));
void	 Buf_OvAddByte __P((Buffer, int));
int	 Buf_Size __P((Buffer));
void	 Buf_UngetByte __P((Buffer, int));
void	 Buf_UngetBytes __P((Buffer, int, Byte *));
E 7
I 7
void Buf_OvAddByte __P((Buffer, int));
void Buf_AddBytes __P((Buffer, int, Byte *));
void Buf_UngetByte __P((Buffer, int));
void Buf_UngetBytes __P((Buffer, int, Byte *));
int Buf_GetByte __P((Buffer));
int Buf_GetBytes __P((Buffer, int, Byte *));
Byte *Buf_GetAll __P((Buffer, int *));
void Buf_Discard __P((Buffer, int));
int Buf_Size __P((Buffer));
Buffer Buf_Init __P((int));
void Buf_Destroy __P((Buffer, Boolean));
E 7

#endif /* _BUF_H */
E 5
E 1
