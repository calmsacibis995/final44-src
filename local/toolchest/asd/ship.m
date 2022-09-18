.TH SHIP 1
.(B
.tl @Copyright (c) 1984, 1985, 1986, 1987@@AT&T All Rights Reserved@
.(E 2
.SH NAME
ship \- automatic software distribution
.SH SYNOPSIS
.B ship 
files
.SH DESCRIPTION
.I Ship
distributes the named files to other computers, where
they are installed under the same names.
The shipper must be registered in the tables of
.IR asd (5).
.I Ship
will ask for a key to confirm the shipper's rights.
.PP
Links among the named files are imitated on the receiving computer.
Named files that do not exist on the sending
computer are deleted on the receiving computer.
.SH SEE ALSO
asd(8), asd(5)
