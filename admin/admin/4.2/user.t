.DA
.TL
User Contributed Software
.PP
The subtree /usr/src/new contains programs contributed by the user
community.  The following software is included:
.DS C
.TS
lb lb lb
l l l.
Directory	Description	Contributor(s)

apl	APL system	Purdue
bib	bibliography system	Arizona
courier	remote procedure call package	Eric Cooper, Berkeley
cpm	CP/M floppy access package	Helge Skrivervik
dsh	distributed shell	Dave Presotto, Berkeley
hyper	Hyperchannel support tools	Steve Glaser, Tektronix
icon	ICON system	Arizona
learn	learn lessons for vi	Pavel Curtis, Cornell
mh	MH mail system	Rand Corporation
news	``readnews'' bulletin board system	Matt Glickman, Berkeley
notes	notes files bulletin board system	Illinois
rcs	revision control system	Walter Tichy, Purdue
sccstorcs	sccs to rcs conversion kit	Ken Greer, HP
spms	software project management system	Peter Nicklin, Berkeley
tools	miscellaneous tools	John Kunze, Berkeley
.TE
.DE
.PP
The individuals responsible for the software should be identified in
the accompanying 4.2BSD documents which describe the user contributed
software.  All software included here has been written by outside
parties; we gratefully acknowledge their contributions.
.PP
This subtree may be extracted from the 4.2BSD second tape by the command
.DS
mt fsf;  cd /usr/src/new;  tar x
.DE
The organization of this subtree is such that a single make command
will compile and/or install the contributed software.  To compile 
everything, simply type
.DS
make
.DE
Once this is done, to install the software in the /usr/new area of
the file system type
.DS
make install
.DE
All subdirectories have README files and individual makefiles.  If
you want only some of the software contained here go to the appropriate
directories and use the previous commands to compile and install the
desired system.  As distributed, all software located here is set up
to be installed in ${DESTDIR}/usr/new, where DESTDIR is a make macro
which can be supplied on the command line.  Consult each directory's
README file for the information needed to change this.
.PP
The software included here is in use at Berkeley, or other sites
running 4.2BSD (or an earlier derivative). Please remember that this is
contributed software and, as such, we do not ``support'' it in the same
manner as that software which is part of the standard distribution.
Each subsystem has a README file in it's root directory. This file
should be consulted to find an interested party to which bugs and/or
bug fixes should be sent. In certain cases these people are located at
Berkeley; this does not imply they are part of the Computer Systems
Research Group, please contact them as individuals.
.PP
.DS
Ralph Campbell
Sam Leffler
David Mosher
Peter Nicklin
.DE
