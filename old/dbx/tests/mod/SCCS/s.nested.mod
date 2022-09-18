h33005
s 00030/00000/00000
d D 5.1 90/06/25 15:34:06 bostic 1 0
c date and time created 90/06/25 15:34:06 by bostic
e
u
U
t
T
I 1
(*
 * Test of nested procedures and modules.
 *)

module main;
var
    i, k : integer;

procedure p (var i : integer);
var
    j, k : integer;

    procedure nestedp (var j : integer);
    var
	i : integer;
    begin
	i := j + 2;
	j := i;
    end nestedp;

begin
    j := i + 1;
    nestedp(j);
    i := j;
end p;

begin
    i := 3;
    p(i);
end main.
E 1
