h44447
s 00013/00002/00022
d D 1.2 89/02/23 21:27:21 mckusick 2 1
c reorganize into three parts instead of one big project
e
s 00024/00000/00000
d D 1.1 89/02/23 18:47:28 mckusick 1 0
c date and time created 89/02/23 18:47:28 by mckusick
e
u
U
t
T
I 1
.\"     %W%     %E%
.LP
\fB\s+4G. Proposed Research\fP\s-4
.PP
The recent invasion of the DARPA Internet by a quickly reproducing worm
highlighted the need for a thorough review of the access
safeguards built into the system.
We will conduct a complete audit of the system
utilities, especially network servers,
to check for and eliminate unintended system access mechanisms.
D 2
Part of this proposal includes the addition and integration of a real
E 2
I 2
.PP
The current security model of 4.3BSD is based
on the model of privileged ports.
The model assumes that a reserved range of port identifiers
can only be allocated by trusted processes.
As workstations have replaced central timesharing computers,
it has become easy for users to attain an authorization
that allows them to improperly obtain a privileged port.
Once they obtain a privileged port,
they can impersonate other users on the network.
To eliminate the impersonation of other users on the network,
the proposal includes the addition and integration of a real
E 2
authentication mechanism for utilities such as
D 2
telnet, login, remote shell, etc.
E 2
I 2
telnet, login, remote shell, and other network based services.
E 2
.PP
A group within the Internet Engineering Task Force has been drafting
a Host Requirements standard for Internet hosts.
We reviewed this draft recently and joined the working group.
For the most part, the existing Berkeley TCP/IP and networking application
software conforms with the draft.
We will review conformance with the Host Requirements standard
at the same time that we review the robustness of the network software.
We expect that some additions will have to be made
to the kernel network protocols to make them compliant.
.bp
E 1
