h22029
s 00017/00019/00008
d D 7.4 90/05/03 17:47:23 sklower 4 3
c first crack at torek changes, may need bug fixes
e
s 00007/00003/00020
d D 7.3 86/12/15 20:26:49 sam 3 2
c lint
e
s 00001/00000/00022
d D 7.2 86/11/20 14:44:20 sam 2 1
c add BADRAD definition
e
s 00022/00000/00000
d D 7.1 86/11/20 12:22:04 sam 1 0
c date and time created 86/11/20 12:22:04 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	%W% (Berkeley) %G%
 */
E 3

D 4
#include "../kdb/redef.h"

char	*BADCOM	=  "bad command";
char	*BADSYM	=  "symbol not found";
char	*BADLOC	=  "automatic variable not found";
char	*NOCFN	=  "c routine not found";
char	*NOMATCH =  "cannot locate value";
char	*BADKET	=  "unexpected ')'";
char	*NOADR	=  "address expected";
char	*BADVAR	=  "bad variable";
D 3
char	*BADTXT	=  "text address not found";
char	*BADDAT	=  "data address not found";
E 3
char	*ADWRAP	=  "address wrap around";
char	*BADEQ	=  "unexpected `='";
char	*BADSYN	=  "syntax error";
char	*NOEOR	=  "newline expected";
char	*NOBKPT	=  "no breakpoint set";
char	*SZBKPT	=  "bkpt command too long";
char	*EXBKPT	=  "too many breakpoints";
char	*BADMOD	=  "bad modifier";
I 2
char	*BADRAD =  "invalid radix";
E 4
I 4
char	*kdbBADCOM	=  "bad command";
char	*kdbBADSYM	=  "symbol not found";
char	*kdbBADLOC	=  "automatic variable not found";
char	*kdbNOCFN	=  "c routine not found";
char	*kdbNOMATCH =  "cannot locate value";
char	*kdbBADKET	=  "unexpected ')'";
char	*kdbNOADR	=  "address expected";
char	*kdbBADVAR	=  "bad variable";
char	*kdbADWRAP	=  "address wrap around";
char	*kdbBADEQ	=  "unexpected `='";
char	*kdbBADSYN	=  "syntax error";
char	*kdbNOEOR	=  "newline expected";
char	*kdbNOBKPT	=  "no breakpoint set";
char	*kdbSZBKPT	=  "bkpt command too long";
char	*kdbEXBKPT	=  "too many breakpoints";
char	*kdbBADMOD	=  "bad modifier";
char	*kdbBADRAD =  "invalid radix";
E 4
E 2
E 1
