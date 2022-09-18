.\" %M% %I% %E%
.ds ss 1
.sh "Kernel primitives
.PP
The facilities available to a UNIX user process are logically
divided into two parts: kernel facilities directly implemented by
UNIX code running in the operating system, and system facilities
implemented either by the system, or in cooperation with a
\fIserver process\fP.  These kernel facilities are described in
this section 1.
.PP
The facilities implemented in the kernel are those which define the
\fIUNIX virtual machine\fP which each process runs in.
Like many real machines, this virtual machine has memory management hardware,
an interrupt facility, timers and counters.  The UNIX
virtual machine also allows access to files and other objects through a set of
\fIdescriptors\fP.  Each descriptor resembles a device controller,
and supports a set of operations.  Like devices on real machines, some
of which are internal to the machine and some of which are external,
parts of the descriptor machinery are built-in to the operating system, while
other parts are often implemented in server processes on other machines.
The facilities provided through the descriptor machinery are described in
section 2.
.ds ss 2
