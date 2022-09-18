h34045
s 00023/00000/00000
d D 5.1 90/06/25 15:34:21 bostic 1 0
c date and time created 90/06/25 15:34:21 by bostic
e
u
U
t
T
I 1
module main;
type
    ElementType = (CHAR, INT, REAL);
    VR = record
	case tag : ElementType of
	    CHAR:
		charValue : char;|
	    INT:
		intValue : integer;|
	    REAL:
		realValue : real;
	end;
    end;
var
    vr : VR;
begin
    vr.tag := CHAR;
    vr.charValue := 'c';
    vr.tag := INT;
    vr.intValue := 3;
    vr.tag := REAL;
    vr.realValue := 3.4;
end main.
E 1
