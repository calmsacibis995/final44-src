h26384
s 00017/00000/00000
d D 5.1 90/06/25 15:34:01 bostic 1 0
c date and time created 90/06/25 15:34:01 by bostic
e
u
U
t
T
I 1
module main;
from imptypes import RT;
import imported;
type
    RT = pointer to record
	i, j : integer;
    end;
var
    p : imported.T;
    q : imported.OT;
    r : RT;
begin
    new(r);
    r^.i := 3;
    r^.j := 4;
    imported.Blah;
end main.
E 1
