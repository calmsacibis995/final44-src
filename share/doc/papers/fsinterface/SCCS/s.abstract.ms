h59851
s 00007/00000/00040
d D 5.2 91/04/16 17:46:44 bostic 2 1
c new copyright; att/bsd/shared
e
s 00040/00000/00000
d D 5.1 90/06/05 17:56:04 bostic 1 0
c date and time created 90/06/05 17:56:04 by bostic
e
u
U
t
T
I 2
.\" Copyright (c) 1986 The Regents of the University of California.
.\" All rights reserved.
.\"
.\" %sccs.include.redist.man%
.\"
.\"	%W% (Berkeley) %G%
.\"
E 2
I 1
.TL
Toward a Compatible Filesystem Interface
.AU
Michael J. Karels
Marshall Kirk McKusick
.AI
Computer Systems Research Group
Computer Science Division
Department of Electrical Engineering and Computer Science
University of California, Berkeley
Berkeley, California  94720
.LP
As network or remote filesystems have been implemented for
.UX ,
several stylized interfaces between the filesystem implementation
and the rest of the kernel have been developed.
Notable among these are Sun Microsystems' virtual filesystem interface
using vnodes, Digital Equipment's Generic File System architecture,
and AT&T's File System Switch.
Each design attempts to isolate filesystem-dependent details
below the generic interface and to provide a framework within which
new filesystems may be incorporated.
However, each of these interfaces is different from
and incompatible with the others.
Each of them addresses somewhat different design goals.
Each was based upon a different starting version of
.UX ,
targetted a different set of filesystems with varying characteristics,
and uses a different set of primitive operations provided by the filesystem.
The current study compares the various filesystem interfaces.
Criteria for comparison include generality, completeness, robustness,
efficiency and esthetics.
As a result of this comparison, a proposal for a new filesystem interface
is advanced that includes the best features of the existing implementations.
The proposal adopts the calling convention for name lookup introduced
in 4.3BSD.
A prototype implementation is described.
This proposal and the rationale underlying its development
have been presented to major software vendors
as an early step toward convergence upon a compatible filesystem interface.
E 1
