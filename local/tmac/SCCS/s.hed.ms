h52593
s 00001/00001/00087
d D 1.4 88/04/22 17:40:51 karels 4 3
c add keywords
e
s 00016/00012/00072
d D 1.3 88/04/22 17:09:39 karels 3 2
c adjust letterhead spacing for laserwriter (at least)
e
s 00011/00001/00073
d D 1.2 88/04/15 14:16:22 karels 2 1
c add postscript UC letterhead
e
s 00074/00000/00000
d D 1.1 88/04/15 12:02:28 karels 1 0
c 1984 version, owned by D. Slattengren
e
u
U
t
T
I 1
D 4
.	\" letter HEad
E 4
I 2
.	\" %W% %G%
I 4
.	\" letter HEad
E 4
E 2
.de HE
.nr xx \\n(.d
.nr xy \\n(.u
.nr xz \\n(.f
.LP
\0
.nr xw \\n(.s
.nf
D 3
.ie "\*(.T"ip" \{\
.	ft R \}
I 2
.ie "\*(.T"psc" \{\
.	ft R \}
E 2
.el \{\
.	ft cr\}
E 3
.ps 12
.vs 0.14i
.in 0
D 3
.ie "\*(.T"va" \{\
E 3
I 3
.ie "\*(.T"ip" \{\
.	po 0.4i
.	sp |0.5i
.	ft R \}
.el .ie "\*(.T"psc" \{\
.	po 0.85i
.	sp |0.7i
.	ft R \}
.el .ie "\*(.T"va" \{\
E 3
.	po 0.1i
D 3
.	sp |0.3i\}
E 3
I 3
.	sp |0.3i
.	ft cr\}
E 3
.el \{\
.	po 0.4i
D 3
.	sp |0.5i\}
E 3
I 3
.	sp |0.5i
.	ft cr\}
E 3
UNIVERSITY OF CALIFORNIA, BERKELEY
.sp 0.3i-1v
I 2
.ie "\*(.T"psc" \{\
D 3
\l'11.5c' \h'|13.7c'\l'4.2c'
E 3
I 3
\l'11.3c' \h'|13.5c'\l'4.2c'
E 3
.br
D 3
\s6BERKELEY    \(bu    DAVIS    \(bu    IRVINE    \(bu    LOS  ANGELES    \(bu    RIVERSIDE    \(bu    SAN  DIEGO    \(bu    SAN  FRANCISCO \h'|11.55c' \z\(uc \h'|14c' SANTA  BARBARA    \(bu    SANTA  CRUZ\s10
E 3
I 3
\s6\|BERKELEY    \(bu    DAVIS    \(bu    IRVINE    \(bu    LOS  ANGELES    \(bu    RIVERSIDE    \(bu    SAN  DIEGO    \(bu    SAN  FRANCISCO \h'|11.35c' \z\(uc \h'|13.85c' SANTA  BARBARA    \(bu    SANTA  CRUZ\s10
E 3
.sp -0.2c
D 3
\l'11.5c' \h'|13.7c'\l'4.2c'\s7 \}
E 3
I 3
\l'11.3c' \h'|13.5c'\l'4.2c'\s7 \}
E 3
.el \{\
E 2
.ps 7
\D't 0.013i'\D'l 4.5i 0'\h'0.83i'\D'l 1.85i 0'
.sp 0.13i-1v
\!s5
\D't 0.024i'\|BERKELEY \v'-0.035i'\D'l 0 0'\v'0.035i' DAVIS \v'-0.035i'\D'l 0 0'\v'0.035i' IRVINE \v'-0.035i'\D'l 0 0'\v'0.035i' LOS ANGELES \v'-0.035i'\D'l 0 0'\v'0.035i' RIVERSIDE \v'-0.035i'\D'l 0 0'\v'0.035i' SAN DIEGO \v'-0.035i'\D'l 0 0'\v'0.035i' SAN FRANCISCO\h'|4.9i'\u\f(slseal\fP\h'|5.475i'\dSANTA BARBARA \v'-0.035i'\D'l 0 0'\v'0.035i' SANTA CRUZ
.sp 0.07i-1v
D 2
\D't 0.013i'\D'l 4.5i 0'\h'0.83i'\D'l 1.85i 0'
E 2
I 2
\D't 0.013i'\D'l 4.5i 0'\h'0.83i'\D'l 1.85i 0' \}
E 2
.sp 0.5i-1v
\|COLLEGE OF ENGINEERING\h'|4.1i'BERKELEY, CALIFORNIA  94720
\|DEPARTMENT OF ELECTRICAL ENGINEERING
\0\0AND COMPUTER SCIENCES\D't 3u'
\|COMPUTER SCIENCE DIVISION
.ft \\n(xz
.ps \\n(xw
.if "\\$1"D" \{\.sp 4p
\\h'|4.1i'\\*(DY\}
.if \\n(xy .fi
.ie \\n(xx>\\n(.d .sp |\\n(xxu
.el .sp 0.3i
.vs
.in
.po
..
.	\" LT - letter
.de LT
.nr PO 1.1i
.if "\*(.T"va" .nr PO 0.8i
.po \\n(POu
.LP
.rs
.if n .sp 1i
.ll 8i
.ie n \{\
.ce 4
University of California
Computer Science Division
Berkeley, California  94720
\}
.el .HE \\$1
.if n .if "\\$1"D" \{.ce
\\*(DY\}
.ll
.in 0
.br
.if t .sp 3
.if n .sp
.nf
.if n .na
.rm CF
..
E 1
