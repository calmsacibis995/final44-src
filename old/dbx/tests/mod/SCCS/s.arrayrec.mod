h46199
s 00029/00000/00000
d D 5.1 90/06/25 15:33:39 bostic 1 0
c date and time created 90/06/25 15:33:39 by bostic
e
u
U
t
T
I 1
(*
 * Test of arrays of records.
 *)

module main;
type
    Rec = record
	charValue : char;
	intValue : integer;
	subrange : [0..1000];
	realValue : real;
    end;
    Arr = array [1..10] of Rec;
var
    a : Arr;
begin
    a[1].charValue := 'c';
    a[1].intValue := 3;
    a[1].subrange := 10;
    a[1].realValue := 3.4;
    a[2].charValue := 'd';
    a[2].intValue := 4;
    a[2].subrange := 11;
    a[2].realValue := 4.5;
    a[3].charValue := 'e';
    a[3].intValue := 5;
    a[3].subrange := 12;
    a[3].realValue := 5.6;
end main.
E 1
