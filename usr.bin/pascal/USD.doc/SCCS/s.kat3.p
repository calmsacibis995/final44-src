h44630
s 00000/00000/00023
d D 8.1 93/06/08 18:09:25 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00023/00000/00000
d D 5.1 90/06/07 16:14:45 bostic 1 0
c date and time created 90/06/07 16:14:45 by bostic
e
u
U
t
T
I 1
program kat(input, output);
var
    ch: char;
    i: integer;
    name: packed array [1..100] of char;
begin
    i := 1;
    repeat
        if i < argc then begin
            argv(i, name);
            reset(input, name);
            i := i + 1
        end;
        while not eof do begin
            while not eoln do begin
                read(ch);
                write(ch)
            end;
            readln;
            writeln
        end
    until i >= argc
end { kat }.
E 1
