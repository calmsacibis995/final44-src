h26267
s 00024/00000/00000
d D 5.1 90/06/25 15:34:09 bostic 1 0
c date and time created 90/06/25 15:34:09 by bostic
e
u
U
t
T
I 1
(*
 * Test of procedure variables.
 *)

module main;

procedure p (var i : integer);
begin
    i := 3;
end p;

procedure q ;
var
    t : procedure(var integer);
    j : integer;
begin
    t := p;
    t(j);
    j := j + 1;
end q;

begin
    q;
end main.
E 1
