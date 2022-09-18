.de PS	\" 	start picture (bwk) $1 is height, $2 is width in units
.if t .sp .3
.in (\\n(.lu-\\$2u)/2u
.ne \\$1u
..
.de PE
.in
.if t .sp .6
..
.de GS	\"	GRN called with C (default), L or R  (g1=width, g2=height)
.nr g7 (\\n(.lu-\\n(g1u)/2u
.if "\\$1"L" .nr g7 \\n(.iu
.if "\\$1"R" .nr g7 \\n(.lu-\\n(g1u
.in \\n(g7u
.ne \\n(g2u
..
.de GE
.in
.if t .sp .6
..
