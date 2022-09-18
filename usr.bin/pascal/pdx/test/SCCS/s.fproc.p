h35806
s 00002/00002/00054
d D 8.1 93/06/06 15:48:30 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00056/00000/00000
d D 5.1 91/04/16 14:58:54 bostic 1 0
c date and time created 91/04/16 14:58:54 by bostic
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

program fproc(output);
    var
    i :integer;

    procedure print(function frtn :integer);
	begin
	    write(frtn:3,'   formal routine =');
	end;

    procedure lvl1(function form: integer);
	label	1;
	var
	loc :integer;

	function eval :integer;
	    begin
		if loc = 8 then begin
			writeln(' non-local jump');
			goto 1;
		end;
		eval := loc;
	    end;

    begin
	loc := i;
	i := i - 1;
	if (loc = 4) or (loc = 8) then
		lvl1(eval)
	else if loc > 0 then
		lvl1(form);
1:	write('Stack frame:',loc:3,'   formal print =');
	print(form);
	writeln(form:3);
    end;

    function geval :integer;
	begin
	    geval := i;
	end;

    begin
	writeln('This should print levels 0-3, with formal values of 4.');
	writeln('Level 4 should jump to level 8.');
	writeln('Finally levels 8-10 should print with formal values of -1.');
	i := 10;
	lvl1(geval);
    end.
E 1
