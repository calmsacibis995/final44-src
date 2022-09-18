h35957
s 00032/00000/00000
d D 5.1 90/06/25 15:37:17 bostic 1 0
c date and time created 90/06/25 15:37:17 by bostic
e
u
U
t
T
I 1
(*
 * Test of nested functions.
 *)

program nested (input, output);
var
    i, k : integer;

function f (var i : integer) : integer;
var
    j, k : integer;

    function nestedf (var j : integer) : integer;
    var
	i : integer;
    begin
	i := j + 2;
	j := i;
	nestedf := j;
    end;

begin
    j := i + 1;
    i := nestedf(j);
    i := j;
    f := i;
end;

begin
    i := 3;
    i := f(i);
end.
E 1
