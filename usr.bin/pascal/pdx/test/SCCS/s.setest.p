h57514
s 00002/00002/00070
d D 8.1 93/06/06 15:49:01 bostic 2 1
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00072/00000/00000
d D 5.1 91/04/16 14:59:03 bostic 1 0
c date and time created 91/04/16 14:59:03 by bostic
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

program setest(input,output);

type
aset = set of 1..41;
sint = 0 .. 30000;

var
set1, set2 :aset;
ptr :^aset;
i :sint;

begin
writeln('Enter a number between 2 and 41.');
writeln('Numbers 2, 10..12, 17, and 37 print "false" all others "true".');
i := ord(input^);
read(i);
writeln('i =',i:2);
write('The set opcodes work :');
set1 := [5..15];
set2 := [10];
if set1 * [23] = [] then 
write(' []')
else
write(false:6);
if set1-set2 <> [5..9,11..15] then
   write(false:6);
new(ptr);
ptr^ := [2,10,37,i];
set1 := ptr^ - [1..3];
set2 := ptr^ + [10..12,17];
if ptr^ * set1 = set1 then
   write(' mul plus minus')
else
   write(false:6);
if (17 in [10..13,15..20,25..30]) and
   (not (22 in [1..17,36..41])) then
   write(' in')
else
   write(false:6);
if (set1 <> set2) and
   (set1 <  set2) and
   (set2 >  set1) and
   (set2 >= ptr^) and
   (set1 <= set2) and
   (set1 >= set1) and
   (set1 <= set1) and
   (card(set2) = 7) then
   write(' and rel')
else
   write(false:6);
if (set1 <> set1) or
   (set2 <  set1) or
   (set1 >  set2) or
   (ptr^ >= set2) or
   (set2 <= set1) or
   (set1 =  set2) or
   (17 in set2) then
   writeln(' or rel')
else
   writeln(false:6);
i := pred(i);
i := (i + i) div i;
end.
E 1
