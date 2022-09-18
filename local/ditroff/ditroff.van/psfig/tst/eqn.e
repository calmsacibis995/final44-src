.lf 1 -
.nf
.F+
delim ##
define "wd"		| width |
define "pretzel"	| pretzel.ps wd 1.3n |
.F-
.EQ I
.ds 11 \v'.3m'\s+5\(*S\s-5\v'-.3m'
.ds 12 "\f2i\fP
.ds 13 "\f2\(eq\fP
.as 12 "\^\*(13
.ds 13 "\f10\fP
.as 12 "\*(13
.ds 13 "\f2# pretzel #\fP
.nr 11 0\w'\s+0\*(11'
.nr 14 \n(11
.nr 12 0\w'\s-3\*(12'
.if \n(12>\n(14 .nr 14 \n(12
.nr 13 0\w'\s-3\*(13'
.if \n(13>\n(14 .nr 14 \n(13
.ds 14 \v'1m'\h'\n(14u-\n(12u/2u'\s-3\*(12\s+3\h'-\n(14u-\n(12u/2u'\v'-1m'\
\h'\n(14u-\n(11u/2u'\*(11\h'\n(14u-\n(11u/2u'\
\v'-1m'\h'-\n(14u-\n(13u/2u'\s-3\*(13\s+3\h'\n(14u-\n(13u/2u'\v'1m'\

.ds 11 "\|
.as 14 "\*(11
.ds 11 "\f2x\fP
.ds 12 "\f2# pretzel #\fP
.as 11 \v'-0.4m'\s-3\|\*(12\s+3\^\v'0.4m'
.as 14 "\*(11
.ds 11 "\|
.as 14 "\*(11
.ds 11 "\f2\(eq\fP
.as 14 "\*(11
.ds 11 "\|
.as 14 "\*(11
.ds 11 "\f12\fP
.as 14 "\*(11
.ds 11 "\f2sin\|\fP\f1(\fP
.as 14 "\*(11
.ds 11 "\f2#pretzel#\fP
.as 14 "\*(11
.ds 11 "\f1)\fP
.as 14 "\*(11
.ds 14 \x'0-0.5m'\*(14\x'0.8m'
.if 2.7m>\n(.v .ne 2.7m
.rn 14 10
\&\*(10
.EN
.lf 10
.EQ I
.ds 11 \v'.3m'\s+5\(*S\s-5\v'-.3m'
.ds 12 "\f2i\fP
.ds 13 "\f2\(eq\fP
.as 12 "\^\*(13
.ds 13 "\f10\fP
.as 12 "\*(13
.ds 13 "\f2x\fP
.nr 11 0\w'\s+0\*(11'
.nr 14 \n(11
.nr 12 0\w'\s-3\*(12'
.if \n(12>\n(14 .nr 14 \n(12
.nr 13 0\w'\s-3\*(13'
.if \n(13>\n(14 .nr 14 \n(13
.ds 14 \v'1m'\h'\n(14u-\n(12u/2u'\s-3\*(12\s+3\h'-\n(14u-\n(12u/2u'\v'-1m'\
\h'\n(14u-\n(11u/2u'\*(11\h'\n(14u-\n(11u/2u'\
\v'-1m'\h'-\n(14u-\n(13u/2u'\s-3\*(13\s+3\h'\n(14u-\n(13u/2u'\v'1m'\

.ds 11 "\|
.as 14 "\*(11
.ds 11 "\f2x\fP
.ds 12 "\f2x kul x\fP
.as 11 \v'-0.4m'\s-3\|\*(12\s+3\^\v'0.4m'
.as 14 "\*(11
.ds 11 "\|
.as 14 "\*(11
.ds 11 "\f2\(eq\fP
.as 14 "\*(11
.ds 11 "\|
.as 14 "\*(11
.ds 11 "\f12\fP
.as 14 "\*(11
.ds 11 "\f2sin\|\fP\f1(\fP
.as 14 "\*(11
.ds 11 "\f2x kul x\fP
.as 14 "\*(11
.ds 11 "\f1)\fP
.as 14 "\*(11
.ds 14 \x'0-0.5m'\*(14\x'0.8m'
.if 2.7m>\n(.v .ne 2.7m
.rn 14 10
\&\*(10
.EN
.lf 13
