h16108
s 00002/00002/00032
d D 8.1 93/06/06 15:48:20 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00034/00000/00000
d D 5.1 91/04/16 14:58:51 bostic 1 0
c date and time created 91/04/16 14:58:51 by bostic
e
u
U
t
T
I 1
(*
D 2
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 2
I 2
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 2
 *
 * %sccs.include.redist.c%
 *
 *	%W% (Berkeley) %G%
 *)

(*
 * From peter@UCBERNIE Wed Apr 13 15:22:29 1983
 * Date: 13 Apr 83 14:04:39 PST (Wed)
 * From: peter@UCBERNIE (peter b. kessler)
 * Subject: try ``pi -t t.p ; obj'' and then ``print variant.b''
 * Message-Id: <8304132204.AA00797@UCBERNIE.ARPA>
 * Received: by UCBERNIE.ARPA (3.320/3.12)
 * 	id AA00797; 13 Apr 83 14:04:39 PST (Wed)
 * Received: from UCBERNIE.ARPA by UCBARPA.ARPA (3.332/3.19)
 * 	id AA01057; 13 Apr 83 15:22:23 PST (Wed)
 * To: linton@UCBERNIE
 * Status: R
 *)

program t(output);
    var
	variant : record case boolean of
			true: (b:boolean);
			false: (i:integer);
		    end;
    begin
	variant.i := -1;
	writeln(variant.b);
    end.

E 1
