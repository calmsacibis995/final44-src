h55127
s 00041/00000/00000
d D 5.1 90/06/25 15:33:48 bostic 1 0
c date and time created 90/06/25 15:33:48 by bostic
e
u
U
t
T
I 1
(*
 * Test program for dbx call command.
 *)

module main;
from io import writef, output;

var global : integer;

procedure startup ;
var
    mainlocal : integer;
begin
    global := 2;
    mainlocal := 19;
    p1();
    p2(mainlocal);
    p3("test", 3);
end startup;

procedure p1 ();
begin
    writef(output, "in p1\n");
    global := 4;
end p1;

procedure p2 (frommain : integer);
begin
    writef(output, "in p2(%d)\n", frommain);
    global := 9;
end p2;

procedure p3 (s : array of char; i : integer);
begin
    writef(output, "in p3(%s, %d)\n", s, i);
    global := 10;
end p3;

begin
    startup;
end main.
E 1
