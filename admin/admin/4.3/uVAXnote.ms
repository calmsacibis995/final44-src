.TL
Notes on MicroVAX II Support
in the 4.3BSD Distribution
.AU
Robert J. Kridle
.AI
mt Xinu
2560 Ninth Street, Suite 312
Berkeley, CA   94710

May 8, 1986
.PP
The 4.3BSD kernel can now be configured to run on the MicroVAX II as well
as the other machines discussed in \f2Installing and Operating 4.2BSD on the
VAX.\f1
This addition includes emulation code for all the VAX instructions missing
on the MicroVAX II and used by software in the distribution.
It does not include any floating point emulation; the target system must
be equipped with hardware floating point.
Some modification was required to the existing autoconfiguration code
and a couple of new drivers were written.
Many of the existing Unibus drivers work with little or no modification.
The MicroVAX I is not supported.
.PP
The distributed MicroVAX II kernel consists of the
recent integration of parts from a number of sources and is
definitely work in progress. 
Although the basic kernel integration is complete and has been tested
at least briefly, the MicroVAX II bootstrap drivers have not been integrated
with the rest of the booting and installing code. 
We hesitated to modify the booting and installing subsystems so close
to a distribution for fear of breaking the installation process for
other machines. In any case, we have no way to produce a distribution
on media suitable for the MicroVAX II.
.PP
Those who wish to work with 4.3BSD on MicroVAXen have two alternatives:
they can complete the integration of the bootstrap drivers and build a
bootable distribution on some media compatible with their MicroVAX, or
they may choose to devise an \f2ad hoc\f1 bootstrap by using a running
Ultrix system as a beachhead.
Some of the consequences of both of these alternatives are discussed below.
.PP
The user who wishes to complete the integration of the MicroVAX II portion
of the bootstrap and installation code will find most of the essential
components already present. The distribution includes sources for
standalone drivers
for the tsv05 and tk50 tape systems. In addition there are standalone
assembly language \f2tp\f1 modules and toggle bootstraps for both of
these devices (/usr/mdec/{tk,tsv}{boot,toggle}).
The major problem will be finding compatible media on which the MicroVAX II
distribution can be written.
Most MicroVAXen are not equipped with standard 1/2 inch magnetic tape.
Most other VAXen do not usually cohabit with TK50s.
.PP
Bootstrapping through an existing Ultrix system on an Ethernet
with a 4.3BSD MacroVAX is probably easier.
A MicroVAX II kernel can be created on the MacroVAX system and then transferred
to the MicroVAX II running Ultrix.
It can then be booted using the Ultrix bootstrap code already residing
in the first few blocks of the disk and in /boot.
Ultrix file systems are compatible and can be sucessfully used by
the 4.3BSD uVAX kernel.
Although not all Ultrix utilities will work correctly with a 4.3BSD
kernel, enough of them work to manage the tranfer of any of the
remaining distribution that is
desired to the MicroVAX II.
It is strongly suggested, however,
that one eventually converge on an all 4.3 system,
rather than some mixture of Ultrix and the 4.3 distribution.
.PP
Several limitations of the current 4.3BSD MicroVAX II should be mentioned.
There is currently no support for the QVSS display on the VAXstation II
or the QDSS display on the VAXstation II/GPX either as a console
or a graphics device. Some kind of ASCII terminal must be connected to
the MicroVAX console port.
The Q-Bus ethernet (DEQNA) and TMSCP (TK50) drivers in the
distributed system were recently supplied by
DEC and have replaced drivers which worked but had known problems.
The DEC drivers may have unknown problems although they have the advantage
of being written by individuals who presumably had access to at least
some technical documentation.
.PP
A number of people and companies made contributions to the MicroVAX
portion of the 4.3 kernel.
Rick Macklem of the University of Guelph modified 4.2 and later a beta
release of
4.3BSD to run on the MicroVAX II. He has been running these systems in
a production environment long enough to find many bugs.
Dave Slattengren of mt Xinu wrote the emulation code for the missing
MicroVAX instructions first in 'C' and later in assembly.
Dave and I also developed an independent 4.2 MicroVAX port.
As mentioned above, DEC contributed several drivers.
Mike Karels, Kirk Mckusick, and Jim Bloom lent enormous help as they do
to most everyone involved with 4BSD.
