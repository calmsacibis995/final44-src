.F+
delim ##
define "wd"		| width |
define "pretzel"	| pretzel.ps wd 1.3n |
.F-
.TL
Jaap
.PP
Characters designed this way can be used anywhere a standard character can
be used:
.EQ I
sum from {i = 0 } to "# pretzel #" ^x sup "# pretzel #" ^=^ 2 sin("#pretzel#")
.EN
.EQ I
sum from {i = 0 } to "x" ^x sup "x kul x" ^=^ 2 sin("x kul x")
.EN
One hint for use with 
