.TH ASD 8
.(B
.tl @Copyright (c) 1984, 1985, 1986, 1987@@AT&T All Rights Reserved@
.(E 2
.SH NAME
mkpkg, inspkg, seal, unseal \- automatic software distribution
.SH SYNOPSIS
.B mkpkg
[ options ] files
.PP
.B inspkg
[ options ] files
.PP
.B seal
[
.B \-k
]
[
.B \-K
keyfile
]
[
file ...
]
.PP
.B unseal
[
.B \-k
]
[
.B \-K
keyfile
]
[
file ...
]
.SH DESCRIPTION
These commands are the basis of automatic software distribution
as used in
.IR ship (1).
.PP
.I Mkpkg
collects files and directories into a `package',
which is written on the standard output.
It reads the standard input for remarks to include in the package,
and will prompt for these if the standard output is a terminal.
.PP
.I Inspkg
opens packages and installs their contents,
printing the remarks included in the package.
Since
.I inspkg
has no special privileges,
installation should be done by the
owner of the files being installed
or by the super-user.
.PP
The information contained in a package
includes the full pathnames of the objects,
links among the objects,
their owners, groups,
file modes, and modification dates.
Owners and groups are stored as their
character representations, to avoid problems if systems use different
numeric codes for a single owner or group.
Nonexistent objects are noted for deletion by
.I inspkg.
.PP
Options are:
.TP 
.B
\-v
Verbose mode.
.TP
.B
\-n
If packaging, don't ask for remarks.
If installing, skip the actual installation,
but do backup if requested.
.TP
.B
\-b
Backup mode,
meaningful only with
.I inspkg.
Write on the standard output a package
that contains everything that was destroyed
during installation.
.TP
.BI \-D path1=path2
Pretend that a pathname beginning with
.I path1
really begins with
.IR path2 .
.PP
A package is an archive
(see
.IR ar (1))
with a component named
`instructions' that contains installation information.
.PP
.I Seal
produces on the standard output a file containing the same information as
the concatenation of all its input files,
in a form suitable for shipment by
.IR mail .
If no input
.I files
are specified,
.I seal
reads its standard input.
.PP
.I Unseal
reads files produced by
.I seal
and produces the original file contents as its output.
.PP
A sealed file includes a checksum; if the
.B \-k
option is specified,
.I seal
prompts for a key
to encrypt the data before
calculating the checksum.
.PP
If the
.B \-K
option is specified, the program uses the first line of
the given
.I keyfile
to supply the key.
Subsequent lines are ignored.
.SH SEE ALSO
ship(1)
.SH BUGS
File names with embedded white space are mishandled.
