h60030
s 00000/00000/00033
d D 5.3 91/09/03 09:32:33 bostic 3 2
c New version from Oz Yigit
e
s 00001/00011/00032
d D 5.2 90/06/01 16:09:34 bostic 2 1
c new copyright notice
e
s 00043/00000/00000
d D 5.1 89/08/28 15:14:16 bostic 1 0
c date and time created 89/08/28 15:14:16 by bostic
e
u
U
t
T
I 1
/*
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Ozan Yigit.
 *
D 2
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
E 2
I 2
 * %sccs.include.redist.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

extern ndptr hashtab[];		/* hash table for macros etc.  */
extern char buf[];		/* push-back buffer	       */
extern char *bp;		/* first available character   */
extern char *endpbb;		/* end of push-back buffer     */
extern stae mstack[];		/* stack of m4 machine         */
extern char *ep;		/* first free char in strspace */
extern char *endest;		/* end of string space	       */
int sp; 			/* current m4  stack pointer   */
int fp; 			/* m4 call frame pointer       */
extern FILE *infile[];		/* input file stack (0=stdin)  */
extern FILE *outfile[];		/* diversion array(0=bitbucket)*/
extern FILE *active;		/* active output file pointer  */
extern char *m4temp;		/* filename for diversions     */
extern int ilevel;		/* input file stack pointer    */
extern int oindex;		/* diversion index..	       */
extern char *null;		/* as it says.. just a null..  */
extern char *m4wraps;		/* m4wrap string default..     */
extern char lquote;		/* left quote character  (`)   */
extern char rquote;		/* right quote character (')   */
extern char scommt;		/* start character for comment */
extern char ecommt;		/* end character for comment   */
E 1
