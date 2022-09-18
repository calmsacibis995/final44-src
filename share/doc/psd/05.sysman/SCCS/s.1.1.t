h48071
s 00030/00027/00296
d D 8.5 94/05/26 22:30:48 bostic 9 8
c cleanups and edits for accuracy
e
s 00003/00003/00320
d D 8.4 94/05/21 15:26:17 hibler 8 7
c minor syntax changes
e
s 00066/00039/00257
d D 8.3 94/05/20 06:06:51 karels 7 6
c touchups and improvements
e
s 00184/00077/00112
d D 8.2 94/05/16 10:09:32 mckusick 6 5
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00187
d D 8.1 93/06/08 18:05:07 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00185
d D 6.3 91/04/17 10:01:52 bostic 4 3
c new copyright; att/bsd/shared
e
s 00019/00010/00169
d D 6.2 86/05/12 01:00:40 karels 3 2
c update, correct, rephrase and re-propose
e
s 00000/00001/00179
d D 6.1 86/05/08 12:26:25 mckusick 2 1
c format updates for 4.3BSD
e
s 00180/00000/00000
d D 5.1 86/05/08 00:02:27 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 4
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 4
I 4
D 5
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 5
I 5
D 7
.\" Copyright (c) 1983, 1993
E 7
I 7
.\" Copyright (c) 1983, 1993, 1994
E 7
.\"	The Regents of the University of California.  All rights reserved.
E 5
.\"
.\" %sccs.include.redist.roff%
E 4
.\"
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" %M% %I% %E%
E 2
D 6
.sh "Processes and protection
.NH 3
Host and process identifiers
E 6
I 6
.Sh 2 "Processes and protection
D 7
.Sh 3 "Host and process identifiers
E 7
I 7
.Sh 3 "Host identifiers
E 7
E 6
.PP
D 6
Each UNIX host has associated with it a 32-bit host id, and a host
D 3
name of up to 255 characters.  These are set (by a privileged user)
E 3
I 3
name of up to 64 characters (as defined by MAXHOSTNAMELEN in
E 6
I 6
D 7
Each host has associated with it a 32-bit host id, and a host
E 7
I 7
D 9
Each host has associated with it a 32-bit host ID, and a host
E 7
name of up to MAXHOSTNAMELEN (64) characters (as defined in
E 9
I 9
Each host has associated with it an integer host ID, and a host
name of up to MAXHOSTNAMELEN (256) characters (as defined in
E 9
E 6
\fI<sys/param.h>\fP).
D 6
These are set (by a privileged user)
E 3
and returned by the calls:
E 6
I 6
These identifiers are set (by a privileged user) and retrieved using the
.Fn sysctl
interface described in section
.Xr 1.7.1 .
I 7
The host ID is seldom used (or set), and is deprecated.
E 7
For convenience and backward compatibility,
the following library routines are provided:
E 6
.DS
I 6
.Fd sethostid 1 "set host identifier
E 6
D 9
sethostid(hostid)
E 9
I 9
sethostid(hostid);
E 9
long hostid;
D 6

E 6
I 6
.DE
.DS
.Fd gethostid 0 "get host identifier
E 6
hostid = gethostid();
result long hostid;
D 6

E 6
I 6
.DE
.DS
.Fd sethostname 2 "set host name
E 6
D 9
sethostname(name, len)
E 9
I 9
sethostname(name, len);
E 9
char *name; int len;
D 6

E 6
I 6
.DE
.DS
.Fd gethostname 2 "get host name
E 6
D 9
len = gethostname(buf, buflen)
E 9
I 9
len = gethostname(buf, buflen);
E 9
result int len; result char *buf; int buflen;
.DE
I 7
.Sh 3 "Process identifiers
E 7
D 6
On each host runs a set of \fIprocesses\fP.
E 6
I 6
Each host runs a set of \fIprocesses\fP.
E 6
Each process is largely independent of other processes,
having its own protection domain, address space, timers, and
an independent set of references to system or user implemented objects.
.PP
Each process in a host is named by an integer
D 7
called the \fIprocess id\fP.  This number is
E 7
I 7
called the \fIprocess ID\fP.  This number is
E 7
in the range 1-30000
D 6
and is returned by
the \fIgetpid\fP routine:
E 6
I 6
and is returned by the
.Fn getpid
routine:
E 6
.DS
I 6
.Fd getpid 0 "get process identifier
E 6
pid = getpid();
D 7
result int pid;
E 7
I 7
result pid_t pid;
E 7
.DE
D 6
On each UNIX host this identifier is guaranteed to be unique;
E 6
I 6
On each host this identifier is guaranteed to be unique;
E 6
D 7
in a multi-host environment, the (hostid, process id) pairs are
E 7
I 7
in a multi-host environment, the (hostid, process ID) pairs are
E 7
guaranteed unique.
D 6
.NH 3
Process creation and termination
.PP
E 6
I 6
The parent process identifier can be obtained using the
.Fn getppid
routine:
.DS
.Fd getppid 0 "get parent process identifier
pid = getppid();
D 7
result int pid;
E 7
I 7
result pid_t pid;
E 7
.DE
.Sh 3 "Process creation and termination
.LP
E 6
A new process is created by making a logical duplicate of an
existing process:
.DS
I 6
.Fd fork 0 "create a new process
E 6
pid = fork();
D 7
result int pid;
E 7
I 7
result pid_t pid;
E 7
.DE
D 6
The \fIfork\fP call returns twice, once in the parent process, where
E 6
I 6
The
.Fn fork
call returns twice, once in the parent process, where
E 6
\fIpid\fP is the process identifier of the child,
and once in the child process where \fIpid\fP is 0.
D 9
The parent-child relationship induces a hierarchical structure on
E 9
I 9
The parent-child relationship imposes a hierarchical structure on
E 9
the set of processes in the system.
.PP
D 6
A process may terminate by executing an \fIexit\fP call:
E 6
I 6
For processes that are forking solely for the purpose of
.Fn execve 'ing
another program, the
.Fn vfork
system call provides a faster interface:
E 6
.DS
I 6
.Fd vfork 0 "create a new process
pid = vfork();
D 7
result int pid;
E 7
I 7
result pid_t pid;
E 7
.DE
Like
.Fn fork ,
the
.Fn vfork
call returns twice, once in the parent process, where
\fIpid\fP is the process identifier of the child,
and once in the child process where \fIpid\fP is 0.
I 7
The parent process is suspended until the child process calls
either \fIexecve\fP or \fIexit\fP.
E 7
.LP
A process may terminate by executing an
.Fn exit
call:
.DS
.Fd exit 1 "terminate a process
E 6
D 9
exit(status)
E 9
I 9
exit(status);
E 9
int status;
.DE
D 9
returning 8 bits of exit status to its parent.
E 9
I 9
The lower 8 bits of exit status are available to its parent.
E 9
.PP
When a child process exits or
terminates abnormally, the parent process receives
D 9
information about any
E 9
I 9
information about the
E 9
D 6
event which caused termination of the child process.  A
second call provides a non-blocking interface and may also be used
to retrieve information about resources consumed by the process during its
lifetime.
E 6
I 6
event which caused termination of the child process.
The interface allows the parent to wait for a particular process,
process group, or any direct descendent and
to retrieve information about resources consumed
by the process during its lifetime.
The request may be done either synchronously
(waiting for one of the requested processes to exit),
or asynchronously
(polling to see if any of the requested processes have exited):
E 6
.DS
D 6
#include <sys/wait.h>

pid = wait(astatus);
result int pid; result union wait *astatus;

pid = wait3(astatus, options, arusage);
result int pid; result union waitstatus *astatus;
E 6
I 6
.Fd wait4 4 "collect exit status of child
pid = wait4(wpid, astatus, options, arusage);
result pid_t pid; pid_t wpid; result int *astatus;
E 6
int options; result struct rusage *arusage;
.DE
.PP
A process can overlay itself with the memory image of another process,
passing the newly created process a set of parameters, using the call:
.DS
I 6
.Fd execve 3 "execute a new program
E 6
D 9
execve(name, argv, envp)
char *name, **argv, **envp;
E 9
I 9
execve(name, argv, envp);
char *name, *argv[], *envp[];
E 9
.DE
The specified \fIname\fP must be a file which is in a format recognized
by the system, either a binary executable file or a file which causes
the execution of a specified interpreter program to process its contents.
D 6
.NH 3
User and group ids
E 6
I 6
D 7
If the set-user-id mode bit is set,
the effective user-id is set to the owner of the file;
if the set-group-id mode bit is set,
the effective group-id is set to the group of the file.
Whether changed or not, the effective user-id is copied to the
saved user-id and the effective group-id is copied to the
saved group-id.
.Sh 3 "User and group ids
E 7
I 7
If the set-user-ID mode bit is set,
the effective user ID is set to the owner of the file;
if the set-group-ID mode bit is set,
the effective group ID is set to the group of the file.
Whether changed or not, the effective user ID is then copied to the
D 8
saved user Id, and the effective group Id is copied to the
saved group Id.
E 8
I 8
saved user ID, and the effective group ID is copied to the
saved group ID.
E 8
.Sh 3 "User and group IDs
E 7
E 6
.PP
D 7
Each process in the system has associated with it two user-id's:
D 3
a \fIreal user id\fP and a \fIeffective user id\fP, both non-negative 16 bit
integers.
E 3
I 3
D 6
a \fIreal user id\fP and a \fIeffective user id\fP, both 16 bit
E 6
I 6
a \fIreal user id\fP and a \fIeffective user id\fP, both 32-bit
E 6
unsigned integers (type \fBuid_t\fP).
E 3
D 6
Each process has an \fIreal accounting group id\fP and an \fIeffective
accounting group id\fP and a set of
D 3
\fIaccess group id's\fP.  The group id's are non-negative 16 bit integers.
E 3
I 3
\fIaccess group id's\fP.  The group id's are 16 bit unsigned integers
(type \fBgid_t\fP).
E 6
I 6
Each process has an \fIreal accounting group id\fP
and a set of \fIaccess group id's\fP
the first of which is the \fIeffective accounting group id\fP.
The group id's are 32-bit unsigned integers (type \fBgid_t\fP).
E 7
I 7
Each process in the system has associated with it three user IDs:
D 8
a \fIreal user ID\fP, a \fIeffective user ID\fP, and a \fIsaved user ID\fP,
E 8
I 8
a \fIreal user ID\fP, an \fIeffective user ID\fP, and a \fIsaved user ID\fP,
E 8
D 9
all 32-bit unsigned integers (type \fBuid_t\fP).
E 9
I 9
all unsigned integral types (\fBuid_t\fP).
E 9
Each process has a \fIreal group ID\fP
and a set of \fIaccess group IDs\fP,
the first of which is the \fIeffective group ID\fP.
D 9
The group IDs are 32-bit unsigned integers (type \fBgid_t\fP).
E 7
E 6
E 3
Each process may be in several different access groups, with the maximum
concurrent number of access groups a system compilation parameter,
D 3
the constant NGROUPS in the file <sys/param.h>, guaranteed to be at least 8.
E 3
I 3
the constant NGROUPS in the file \fI<sys/param.h>\fP,
D 6
guaranteed to be at least 8.
E 3
.PP
E 6
I 6
guaranteed to be at least eight.
E 9
I 9
The group IDs are unsigned integral types (\fBgid_t\fP).
Each process may be in multiple access groups.
The maximum concurrent number of access groups is a system compilation
parameter,
represented by the constant NGROUPS in the file \fI<sys/param.h>\fP.
It is guaranteed to be at least 16.
E 9
.LP
E 6
D 7
The real and effective user ids associated with a process are returned by:
E 7
I 7
The real group ID is used in process accounting and in testing whether
the effective group ID may be changed; it is not otherwise used for
access control.
The members of the access group ID set are used for access control.
Because the first member of the set is the effective group ID, which
is changed when executing a set-group-ID program, that element is normally
duplicated in the set so that access privileges for the original group
are not lost when using a set-group-ID program.
.LP
The real and effective user IDs associated with a process are returned by:
E 7
.DS
I 6
.Fd getuid 0 "get real user identifier
E 6
ruid = getuid();
D 3
result int ruid;
E 3
I 3
result uid_t ruid;
E 3
D 6

E 6
I 6
.DE
.DS
.Fd geteuid 0 "get effective user identifier
E 6
euid = geteuid();
D 3
result int euid;
E 3
I 3
result uid_t euid;
E 3
.DE
D 7
the real and effective accounting group ids by:
E 7
I 7
the real and effective group IDs by:
E 7
.DS
I 6
.Fd getgid 0 "get real group identifier
E 6
rgid = getgid();
D 3
result int rgid;
E 3
I 3
result gid_t rgid;
E 3
D 6

E 6
I 6
.DE
.DS
.Fd getegid 0 "get effective group identifier
E 6
egid = getegid();
D 3
result int egid;
E 3
I 3
result gid_t egid;
E 3
.DE
D 3
and the access group id set is returned by a \fIgetgroups\fP call:
E 3
I 3
D 6
The access group id set is returned by a \fIgetgroups\fP call*:
E 6
I 6
D 7
The access group id set is returned by a
E 7
I 7
The access group ID set is returned by a
E 7
.Fn getgroups
call:
E 6
E 3
.DS
I 6
.Fd getgroups 2 "get access group set
E 6
ngroups = getgroups(gidsetsize, gidset);
D 6
result int ngroups; int gidsetsize; result int gidset[gidsetsize];
E 6
I 6
result int ngroups; int gidsetsize; result gid_t gidset[gidsetsize];
E 6
.DE
I 3
D 6
.FS
* The type of the gidset array in getgroups and setgroups
remains integer for compatibility with 4.2BSD.
It may change to \fBgid_t\fP in future releases.
.FE
E 3
.PP
E 6
I 6
.LP
E 6
D 7
The user and group id's
E 7
I 7
The user and group IDs
E 7
D 6
are assigned at login time using the \fIsetreuid\fP, \fIsetregid\fP,
and \fIsetgroups\fP calls:
E 6
I 6
are assigned at login time using the
.Fn setuid ,
.Fn setgid ,
and
.Fn setgroups
calls:
E 6
.DS
D 6
setreuid(ruid, euid);
int ruid, euid;

setregid(rgid, egid);
int rgid, egid;

E 6
I 6
.Fd setuid 1 "set real, effective, and saved user identifiers
setuid(uid);
uid_t uid;
.DE
.DS
.Fd setgid 1 "set real, effective, and saved group identifiers
setgid(gid);
gid_t gid;
.DE
.DS
.Fd setgroups 2 "set access group set
E 6
D 9
setgroups(gidsetsize, gidset)
E 9
I 9
setgroups(gidsetsize, gidset);
E 9
D 6
int gidsetsize; int gidset[gidsetsize];
E 6
I 6
int gidsetsize; gid_t gidset[gidsetsize];
E 6
.DE
D 6
The \fIsetreuid\fP call sets both the real and effective user-id's,
while the \fIsetregid\fP call sets both the real
and effective accounting group id's.
Unless the caller is the super-user, \fIruid\fP
must be equal to either the current real or effective user-id,
and \fIrgid\fP equal to either the current real or effective
accounting group id.  The \fIsetgroups\fP call is restricted
to the super-user.
.NH 3
Process groups
E 6
I 6
D 7
These calls are restricted to the super-user.
E 7
The
.Fn setuid
D 7
call sets the real, effective, and saved user-id's, while the
E 7
I 7
call sets the real, effective, and saved user IDs,
and is permitted only if the specified \fIuid\fP is the current real user ID
or if the caller is the super-user.
The
E 7
.Fn setgid
D 7
call sets the real, effective, and saved group id's.
E 7
I 7
call sets the real, effective, and saved group IDs;
it is permitted only if the specified \fIgid\fP is the current real group ID
or if the caller is the super-user.
E 7
The
I 7
.Fn setgroups
call sets the access group ID set, and is restricted to the super-user.
.LP
The
E 7
.Fn seteuid
D 7
routine allows any process to set its effective user-id to either its
real or saved user-id:
E 7
I 7
routine allows any process to set its effective user ID to either its
real or saved user ID:
E 7
.DS
.Fd seteuid 1 "set effective user identifier
seteuid(uid);
uid_t uid;
.DE
The
.Fn setegid
D 7
routine allows any process to set its effective group-id to either its
real or saved group-id:
E 7
I 7
routine allows any process to set its effective group ID to either its
real or saved group ID:
E 7
.DS
.Fd setegid 1 "set effective group identifier
setegid(gid);
gid_t gid;
.DE
.Sh 3 "Sessions
E 6
.PP
I 6
When a user first logs onto the system,
they are put into a session with a controlling process
(usually a shell).
The session is created with the call:
.DS
.Fd setsid 0 "create a new session
pid = setsid();
result pid_t pid;
.DE
D 7
All subsequent processes created by the user will be part of the session.
E 7
I 7
D 9
All subsequent processes created by the user that do not call
.Fn setsid
E 9
I 9
All subsequent processes created by the user
(that do not call
.Fn setsid )
E 9
will be part of the session.
E 7
The session also has a login name associated with it
which is set using the privileged call:
.DS
.Fd setlogin 1 "set login name
setlogin(name);
char *name;
.DE
The login name can be retrieved using the call:
.DS
.Fd getlogin 0 "get login name
name = getlogin();
result char *name;
.DE
I 7
D 9
Unlike earlier systems, the return value of
E 9
I 9
Unlike historic systems, the value returned by
E 9
.Fn getlogin
D 9
can be trusted.
E 9
I 9
is stored in the kernel and can be trusted.
E 9
E 7
.Sh 3 "Process groups
.PP
E 6
D 7
Each process in the system is also normally associated with a \fIprocess
E 7
I 7
Each process in the system is also associated with a \fIprocess
E 7
group\fP.  The group of processes in a process group is sometimes
referred to as a \fIjob\fP and manipulated by high-level system
software (such as the shell).
I 7
All members of a process group are members of the same session.
E 7
The current process group of a process is returned by the
D 6
\fIgetpgrp\fP call:
E 6
I 6
.Fn getpgrp
call:
E 6
.DS
D 6
pgrp = getpgrp(pid);
result int pgrp; int pid;
E 6
I 6
.Fd getpgrp 0 "get process group
pgrp = getpgrp();
result pid_t pgrp;
E 6
.DE
When a process is in a specific process group it may receive
software interrupts affecting the group, causing the group to
suspend or resume execution or to be interrupted or terminated.
In particular, a system terminal has a process group and only processes
D 9
which are in the process group of the terminal may read from the
terminal, allowing arbitration of terminals among several different jobs.
E 9
I 9
which are in the process group of the terminal may read from the terminal,
allowing arbitration of a terminal among several different jobs.
E 9
D 6
.PP
The process group associated with a process may be changed by
the \fIsetpgrp\fP call:
E 6
I 6
.LP
The process group associated with a process may be changed by the
.Fn setpgid
call:
E 6
.DS
D 6
setpgrp(pid, pgrp);
E 6
I 6
.Fd setpgid 2 "set process group
setpgid(pid, pgrp);
E 6
D 9
int pid, pgrp;
E 9
I 9
pid_t pid, pgrp;
E 9
.DE
D 7
Newly created processes are assigned process id's distinct from all
E 7
I 7
Newly created processes are assigned process IDs distinct from all
E 7
processes and process groups, and the same process group as their
D 9
parent.  A normal (unprivileged) process may set its process group equal
D 6
to its process id.  A privileged process may set the process group of any
process to any value.
E 6
I 6
D 7
to its process id or to the value of any process group within its session.
E 7
I 7
to its process ID or to the value of any process group within its session.
E 9
I 9
parent.
Any process may set its process group equal to its process ID or
to the value of any process group within its session.
E 9
E 7
E 6
E 1
