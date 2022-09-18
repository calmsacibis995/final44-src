h53065
s 00002/00002/00032
d D 8.1 93/06/06 16:45:50 bostic 10 9
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00033
d D 4.3 93/06/06 16:44:34 bostic 9 8
c fix redist notice
e
s 00002/00013/00032
d D 4.2 91/04/26 15:46:40 bostic 8 7
c new copyright; att/bsd/shared
e
s 00000/00000/00045
d D 4.1 88/12/04 15:12:47 minshall 7 6
c Release 4.1
e
s 00011/00005/00034
d D 3.3 88/07/09 10:51:44 bostic 6 5
c install approved copyright notice
e
s 00013/00000/00026
d D 3.2 88/03/28 12:23:50 bostic 5 4
c add Berkeley specific header
e
s 00000/00000/00026
d D 3.1 87/08/11 10:20:27 minshall 4 3
c New version numbering.
e
s 00004/00022/00022
d D 1.3 87/07/15 14:14:43 minshall 3 2
c New function.
e
s 00003/00003/00041
d D 1.2 87/05/20 12:24:49 minshall 2 1
c Null change.
e
s 00044/00000/00000
d D 1.1 87/05/18 15:09:52 minshall 1 0
c date and time created 87/05/18 15:09:52 by minshall
e
u
U
t
T
I 5
D 8
;
; Copyright (c) 1988 Regents of the University of California.
E 8
I 8
D 10
; Copyright (c) 1988 The Regents of the University of California.
E 8
; All rights reserved.
E 10
I 10
; Copyright (c) 1988, 1993
;	The Regents of the University of California.  All rights reserved.
E 10
;
D 8
; Redistribution and use in source and binary forms are permitted
D 6
; provided that this notice is preserved and that due credit is given
; to the University of California at Berkeley. The name of the University
; may not be used to endorse or promote products derived from this
; software without specific prior written permission. This software
; is provided ``as is'' without express or implied warranty.
E 6
I 6
; provided that the above copyright notice and this paragraph are
; duplicated in all such forms and that any documentation,
; advertising materials, and other materials related to such
; distribution and use acknowledge that the software was developed
; by the University of California, Berkeley.  The name of the
; University may not be used to endorse or promote products derived
; from this software without specific prior written permission.
; THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
; IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
; WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 8
I 8
D 9
; %sccs.include.redist.c%
E 9
I 9
; %sccs.include.redist.semicolon%
E 9
E 8
E 6
;
;	%W% (Berkeley) %G%
I 6
;
E 6

E 5
I 1
D 3
; $Header: /lapis_d/minshall/src/misc/minshall/src/netsys/RCS/support.asm,v 1.5 87/01/14 11:29:19 minshall Exp $


E 3
_TEXT	segment	byte public 'CODE'
_TEXT	ends

_DATA	segment	word public 'DATA'
_DATA	ends

CONST	segment	word public 'CONST'
CONST	ends

_BSS	segment word public 'BSS'
_BSS	ends

DGROUP	group	CONST, _BSS, _DATA

	assume	cs:_TEXT, ds:DGROUP, ss:DGROUP, es:DGROUP

_TEXT	segment
I 3
	public	_iret_subr
E 3

D 2
	public	dirconio
E 2
I 2
D 3
	public	_dirconio
E 2

D 2
dirconio	proc	near
E 2
I 2
_dirconio	proc	near
E 2
	push	bp
	mov	bp,sp

	mov	ah,01H		; test input
	int	16H
	mov	ax,0ffffH	; nothing read
	jz	dirconiodone
	mov	ah,00H		; consume the input
	int	16H

dirconiodone:

	mov	sp,bp
	pop	bp
	ret
D 2
dirconio	endp
E 2
I 2
_dirconio	endp
E 3
I 3
_iret_subr	proc	far
	iret
_iret_subr	endp
E 3
E 2

_TEXT	ends

	end
E 1
