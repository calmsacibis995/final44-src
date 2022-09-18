h31284
s 00023/00000/00000
d D 5.1 90/06/25 15:34:07 bostic 1 0
c date and time created 90/06/25 15:34:07 by bostic
e
u
U
t
T
I 1
(*
 * Test of dealing with an opaque type that is never defined.
 *)

module main;

from imptypes import RT;
from io import Writef, output;

type
    T = record
	a : integer;
	b : RT;
	c : integer;
    end;

var r : T;

begin
    r.a := 3;
    r.c := 4;
    Writef(output, "this is a test\n");
end main.
E 1
