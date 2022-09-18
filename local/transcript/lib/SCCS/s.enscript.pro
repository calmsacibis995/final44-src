h12228
s 00002/00001/00040
d D 1.3 90/10/19 18:57:12 karels 3 2
c tuning
e
s 00006/00009/00035
d D 1.2 89/05/20 14:21:14 karels 2 1
c from helios (van jacobson)
e
s 00044/00000/00000
d D 1.1 89/05/20 14:20:32 karels 1 0
c original version from ???
e
u
U
t
T
I 1

% included prolog for enscript files
% last edit: shore Sat Nov  9 13:28:41 1985
% Copyright (c) 1983, 1984 Adobe Systems Incorporated
I 3
% %W% (Berkeley) %G%
E 3
D 2
% RCSID: $Header: enscript.pro,v 2.1 85/11/24 12:19:23 shore Rel $
E 2
I 2
% RCSID: $Header: enscript.pro,v 1.5 89/03/10 00:45:30 van Exp $
E 2
save/EnscriptJob exch def
/StartEnscriptDoc{$enscript begin}def
/$enscript 50 dict def $enscript begin
/EndEnscriptDoc{end}def
/S/show load def
/X{exch 0 rmoveto S}def
/Y{exch 0 exch rmoveto S}def
/B{3 1 roll moveto S}def
/F{$fd exch get setfont}def
/StartPage{/svpg save def .05 dup scale}def
/EndPage{svpg restore showpage}def
/DoPreFeed{/statusdict where{pop
 statusdict/prefeed known{statusdict exch/prefeed exch put 0}if}if pop}def
/Landscape{90 rotate 0 -15840 translate}def
/SetUpFonts
 {dup/$fd exch array def{findfont exch scalefont $fd 3 1 roll put}repeat}def
D 2
/InitGaudy{/TwoColumn exch def /BarLength exch def
 /ftD /Times-Bold findfont 12 UP scalefont def
 /ftF /Times-Roman findfont 14 UP scalefont def
 /ftP /Helvetica-Bold findfont 30 UP scalefont def}def
E 2
I 2
/InitGaudy{/TwoColumn exch def /BarLength exch def}def
E 2
/U{1440 mul}def
/UP{U 72 div}def
/LB{/pts exch UP def /charcolor exch def /boxcolor exch def /font exch def
 /label exch def /dy exch def /dx exch def /lly exch def /llx exch def
 gsave boxcolor setgray
 llx lly moveto dx 0 rlineto 0 dy rlineto dx neg 0 rlineto closepath fill
 /lines label length def
 /yp lly dy add dy lines pts mul sub 2 div sub pts .85 mul sub def
 font setfont charcolor setgray
 label {dup stringwidth pop 2 div llx dx 2 div add exch sub yp moveto show
   /yp yp pts sub def}forall grestore}def
/Gaudy{/Page exch def /Date exch def /File exch def /Comment exch def
D 2
 .25 U 10.2 U BarLength .1 sub U .25 U [File] ftF .97 0 14 LB
 .25 U 10.45 U BarLength .1 sub U .25 U [Comment] ftF 1 0 14 LB
 .25 U 10.2 U 1 U .5 U Date ftD .7 0 12 LB
 BarLength .75 sub U 10.2 U 1 U .5 U [Page] ftP .7 1 30 LB
E 2
I 2
 .25 U 10.2 U BarLength .1 sub U .25 U [File] $fd 2 get .97 0 14 LB
 .25 U 10.45 U BarLength .1 sub U .25 U [Comment] $fd 1 get 1 0 14 LB
 .25 U 10.2 U .75 U .5 U Date $fd 3 get .97 0 12 LB
D 3
 BarLength .5 sub U 10.2 U .75 U .5 U [Page] $fd 4 get .97 1 30 LB
E 3
I 3
 BarLength .5 sub U 10.2 U .75 U .5 U [Page] $fd 4 get .97 0 30 LB
E 3
E 2
 TwoColumn{BarLength 2 div .19 add U 10.2 U moveto 0 -10 U rlineto stroke}if
}def
end
E 1
