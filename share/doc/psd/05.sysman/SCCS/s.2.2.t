h01614
s 00003/00000/00791
d D 8.8 94/06/01 18:16:35 ah 13 12
c page breaks for the 4.4BSD manuals
e
s 00005/00001/00786
d D 8.7 94/05/29 00:05:16 mckusick 12 11
c cleanup final nits
e
s 00017/00001/00770
d D 8.6 94/05/26 23:02:39 mckusick 11 10
c incorporate comments from Mike Hibler
e
s 00079/00071/00692
d D 8.5 94/05/26 22:30:57 bostic 10 9
c cleanups and edits for accuracy
e
s 00107/00107/00656
d D 8.4 94/05/20 10:49:35 mckusick 9 8
c move sections around to improve readability
e
s 00055/00020/00708
d D 8.3 94/05/20 06:07:00 karels 8 7
c touchups and improvements
e
s 00486/00202/00242
d D 8.2 94/05/16 10:09:42 mckusick 7 6
c massive overhaul to bring up to date for 4.4BSD
e
s 00002/00002/00442
d D 8.1 93/06/08 18:06:03 bostic 6 5
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00003/00440
d D 6.4 91/04/17 10:02:01 bostic 5 4
c new copyright; att/bsd/shared
e
s 00001/00001/00442
d D 6.3 86/05/12 01:23:30 karels 4 3
c spelling
e
s 00027/00022/00416
d D 6.2 86/05/12 01:01:22 karels 3 2
c update, correct, rephrase and re-propose
e
s 00001/00002/00437
d D 6.1 86/05/08 12:26:58 mckusick 2 1
c format updates for 4.3BSD
e
s 00439/00000/00000
d D 5.1 86/05/08 00:03:31 mckusick 1 0
c document distributed with 4.2BSD
e
u
U
t
T
I 1
D 5
.\" Copyright (c) 1983 Regents of the University of California.
.\" All rights reserved.  The Berkeley software License Agreement
.\" specifies the terms and conditions for redistribution.
E 5
I 5
D 6
.\" Copyright (c) 1983 The Regents of the University of California.
.\" All rights reserved.
E 6
I 6
D 8
.\" Copyright (c) 1983, 1993
E 8
I 8
.\" Copyright (c) 1983, 1993, 1994
E 8
.\"	The Regents of the University of California.  All rights reserved.
E 6
.\"
.\" %sccs.include.redist.roff%
E 5
.\"
.\"	%W% (Berkeley) %G%
.\"
I 13
.ne 1i
E 13
D 2
.\" %M% %I% %E%
E 2
D 7
.sh "File system
.NH 3
Overview
E 7
I 7
.Sh 2 "Filesystem
.Sh 3 "Overview
E 7
.PP
D 7
The file system abstraction provides access to a hierarchical
file system structure.
The file system contains directories (each of which may contain
E 7
I 7
The filesystem abstraction provides access to a hierarchical
filesystem structure.
The filesystem contains directories (each of which may contain
E 7
D 10
other sub-directories) as well as files and references to other
E 10
I 10
sub-directories) as well as files and references to other
E 10
objects such as devices and inter-process communications sockets.
.PP
Each file is organized as a linear array of bytes.  No record
boundaries or system related information is present in
a file.
Files may be read and written in a random-access fashion.
D 8
The user may read the data in a directory as though
E 8
I 8
If permitted by the underlying storage mechanism,
the user may read the data in a directory as though
E 8
it were an ordinary file to determine the names of the contained files,
but only the system may write into the directories.
D 7
The file system stores only a small amount of ownership, protection and usage
E 7
I 7
D 10
The filesystem stores only a small amount of ownership, protection and usage
E 7
information with a file.
E 10
D 7
.NH 3
Naming
E 7
I 7
.Sh 3 "Naming
E 7
.PP
D 7
The file system calls take \fIpath name\fP arguments.
E 7
I 7
The filesystem calls take \fIpath name\fP arguments.
E 7
These consist of a zero or more component \fIfile names\fP
D 3
separated by ``/'' characters, where each file name
is up to 255 ASCII characters excluding null and ``/''.
E 3
I 3
separated by ``/\^'' characters, where each file name
D 7
is up to 255 ASCII characters excluding null and ``/\^''.
E 7
I 7
D 10
is up to NAME_MAX (255) ASCII characters excluding null and ``/\^''.
Each pathname is up to PATH_MAX (1024) ASCII characters excluding null.
E 10
I 10
is up to NAME_MAX (255) characters excluding null and ``/\^''.
Each pathname is up to PATH_MAX (1024) characters excluding null.
E 10
E 7
E 3
.PP
Each process always has two naming contexts: one for the
D 7
root directory of the file system and one for the
E 7
I 7
root directory of the filesystem and one for the
E 7
current working directory.  These are used
by the system in the filename translation process.
D 3
If a path name begins with a ``/'', it is called
E 3
I 3
If a path name begins with a ``/\^'', it is called
E 3
a full path name and interpreted relative to the root directory context.
D 3
If the path name does not begin with a ``/'' it is called
E 3
I 3
If the path name does not begin with a ``/\^'' it is called
E 3
a relative path name and interpreted relative to the current directory
context.
.PP
I 8
The file name ``.'' in each directory refers to that directory.
E 8
D 7
The system limits
the total length of a path name to 1024 characters.
.PP
E 7
The file name ``..'' in each directory refers to
the parent directory of that directory.
D 3
The parent directory of a file system is always the systems root directory.
E 3
I 3
D 7
The parent directory of the root of the file system is always that directory.
E 3
.PP
The calls
E 7
I 7
D 10
The parent directory of the root of the filesystem is always that directory.
E 10
I 10
The parent directory of the root of the filesystem is itself.
E 10
.LP
The calls:
E 7
.DS
I 7
.Fd chdir 1 "change current working directory
E 7
chdir(path);
char *path;
D 7

E 7
I 7
.DE
.DS
.Fd fchdir 1 "change current working directory
fchdir(fd);
int fd;
.DE
.DS
.Fd chroot 1 "change root directory
E 7
D 10
chroot(path)
E 10
I 10
chroot(path);
E 10
char *path;
.DE
D 8
change the current working directory and root directory context of a process.
E 8
I 8
change the current working directory or root directory context of a process.
E 8
Only the super-user can change the root directory context of a process.
D 7
.NH 3
Creation and removal
E 7
I 7
.LP
Information about a filesystem that contains a particular
file can be obtained using the calls:
.DS
.Fd statfs 2 "get file system statistics
statfs(path, buf);
char *path; struct statfs *buf;
.DE
.DS
.Fd fstatfs 2 "get file system statistics
fstatfs(fd, buf);
int fd; struct statfs *buf;
.DE
.Sh 3 "Creation and removal
E 7
.PP
D 7
The file system allows directories, files, special devices,
and ``portals'' to be created and removed from the file system.
.NH 4
Directory creation and removal
.PP
A directory is created with the \fImkdir\fP system call:
E 7
I 7
The filesystem allows directories, files, special devices,
and fifos to be created and removed from the filesystem.
.Sh 4 "Directory creation and removal
.LP
A directory is created with the
.Fn mkdir
system call:
E 7
.DS
I 7
.Fd mkdir 2 "make a directory file
E 7
mkdir(path, mode);
D 7
char *path; int mode;
E 7
I 7
char *path; mode_t mode;
E 7
.DE
D 3
and removed with the \fIrmdir\fP system call:
E 3
I 3
D 7
where the mode is defined as for files (see below).
Directories are removed with the \fIrmdir\fP system call:
E 7
I 7
where the mode is defined as for files (see section
.Xr 2.2.3.2 ).
Directories are removed with the
.Fn rmdir
system call:
E 7
E 3
.DS
I 7
.Fd rmdir 1 "remove a directory file
E 7
rmdir(path);
char *path;
.DE
D 8
A directory must be empty if it is to be deleted.
E 8
I 8
A directory must be empty (other than the entries ``.'' and ``..'')
if it is to be deleted.
E 8
D 7
.NH 4
File creation
.PP
Files are created with the \fIopen\fP system call,
E 7
I 7
.LP
Although directories can be read as files,
the usual interface is to use the call:
E 7
.DS
I 7
.Fd getdirentries 4 "get directory entries in a filesystem independent format
D 10
getdirentries(fd, buf, nbytes, basep)
E 10
I 10
getdirentries(fd, buf, nbytes, basep);
E 10
int fd; char *buf; int nbytes; long *basep;
.DE
The
.Fn getdirentries
system call returns a canonical array of directory entries
D 10
in a filesystem independent format described in \fI<dirent.h>\fP.
E 10
I 10
in the filesystem independent format described in \fI<dirent.h>\fP.
E 10
Application programs usually use the library routines
.Fn opendir ,
.Fn readdir ,
and
.Fn closedir
D 10
that provide a more convenient interface to
E 10
I 10
which provide a more convenient interface than
E 10
.Fn getdirentries .
I 8
The \fIfts\fP package is provided
for recursive directory traversal.
E 8
.Sh 4 "File creation
.LP
D 8
Files are created with the
E 8
I 8
Files are opened and/or created with the
E 8
.Fn open
system call:
.DS
.Fd open 3 "open or create a file for reading or writing
E 7
fd = open(path, oflag, mode);
D 7
result int fd; char *path; int oflag, mode;
E 7
I 7
result int fd; char *path; int oflag; mode_t mode;
E 7
.DE
The \fIpath\fP parameter specifies the name of the
D 7
file to be created.  The \fIoflag\fP parameter must
D 3
include O_CREAT from below to cause the file to be created.  The protection
for the new file is specified in \fImode\fP.  Bits for \fIoflag\fP are
defined in <sys/file.h>:
E 3
I 3
include O_CREAT from below to cause the file to be created.
E 7
I 7
file to be opened.
The \fIoflag\fP parameter must
include O_CREAT to cause the file to be created.
E 7
Bits for \fIoflag\fP are
D 7
defined in \fI<sys/file.h>\fP:
E 7
I 7
defined in \fI<sys/fcntl.h>\fP:
E 7
E 3
.DS
D 7
._d
#define	O_RDONLY	000	/* open for reading */
#define	O_WRONLY	001	/* open for writing */
#define	O_RDWR	002	/* open for read & write */
#define	O_NDELAY	004 	/* non-blocking open */
#define	O_APPEND	010	/* append on each write */
#define	O_CREAT	01000	/* open with file create */
#define	O_TRUNC	02000	/* open with truncation */
#define	O_EXCL	04000	/* error on create if file exists */
E 7
I 7
.TS
l l.
O_RDONLY	/* open for reading only */
O_WRONLY	/* open for writing only */
O_RDWR	/* open for reading and writing */
O_NONBLOCK	/* no delay */
O_APPEND	/* set append mode */
O_SHLOCK	/* open with shared file lock */
O_EXLOCK	/* open with exclusive file lock */
O_ASYNC	/* signal pgrp when data ready */
O_FSYNC	/* synchronous writes */
O_CREAT	/* create if nonexistent */
O_TRUNC	/* truncate to zero length */
O_EXCL	/* error if already exists */
.TE
E 7
.DE
.PP
One of O_RDONLY, O_WRONLY and O_RDWR should be specified,
D 7
indicating what types of operations are desired to be performed
E 7
I 7
indicating what types of operations are desired to be done
E 7
on the open file.  The operations will be checked against the user's
D 7
access rights to the file before allowing the \fIopen\fP to succeed.
Specifying O_APPEND causes writes to automatically append to the
file.
E 7
I 7
access rights to the file before allowing the
.Fn open
to succeed.
D 10
Specifying O_APPEND causes writes to automatically append to the file.
E 10
I 10
Specifying O_APPEND causes all writes to be appended to the file.
E 10
Specifying O_TRUNC causes the file to be truncated when opened.
E 7
D 10
The flag O_CREAT causes the file to be created if it does not
D 3
exist, with the specified \fImode\fP, owned by the current user
E 3
I 3
exist, owned by the current user
E 3
and the group of the containing directory.
I 3
D 8
The protection for the new file is specified in \fImode\fP.
The file mode is used as a three digit octal number.
E 8
I 8
The protection for the new file is specified in \fImode\fP
E 10
I 10
The flag O_CREAT causes the file to be created if it does not exist,
owned by the current user and the group of the containing directory.
The permissions for the new file are specified in \fImode\fP
E 10
as the OR of the appropriate permissions as defined in \fI<sys/stat.h>\fP:
.DS
.TS
l l.
S_IRWXU	/* RWX for owner */
S_IRUSR	/* R for owner */
S_IWUSR	/* W for owner */
S_IXUSR	/* X for owner */
S_IRWXG	/* RWX for group */
S_IRGRP	/* R for group */
S_IWGRP	/* W for group */
S_IXGRP	/* X for group */
S_IRWXO	/* RWX for other */
S_IROTH	/* R for other */
S_IWOTH	/* W for other */
S_IXOTH	/* X for other */
I 10
S_ISUID	/* set user id */
S_ISGID /* set group id */
S_ISTXT /* sticky bit */
E 10
.TE
.DE
.LP
D 10
Historically, the file mode has been used as a three digit octal number.
E 8
Each digit encodes read access as 4, write access as 2 and execute
access as 1, or'ed together.  The 0700 bits describe owner
access, the 070 bits describe the access rights for processes in the same
group as the file, and the 07 bits describe the access rights
for other processes.
E 10
I 10
Historically, the file mode has been used as a four digit octal number.
The bottom three digits encode read access as 4, write access as 2 and
execute access as 1, or'ed together.
The 0700 bits describe owner access, the 070 bits describe the access
rights for processes in the same group as the file, and the 07 bits
describe the access rights for other processes.
The 7000 bits encode set user ID as 4000, set group ID as 2000, and the
sticky bit as 1000.
E 10
I 7
D 8
The process \fIumask\fP clears specified permissions.
E 8
I 8
The mode specified to
.Fn open
is modified by 
the process \fIumask\fP; permissions specified in the
\fIumask\fP are cleared in the mode of the created file.
E 8
The \fIumask\fP can be changed with the call:
.DS
.Fd umask 1 "set file creation mode mask
oldmask = umask(newmask);
result mode_t oldmask; mode_t newmask;
.DE
E 7
E 3
.PP
D 10
If the open specifies to create the file with O_EXCL
D 7
and the file already exists, then the \fIopen\fP will fail
without affecting the file in any way.  This provides a
simple exclusive access facility.
E 7
I 7
and the file already exists, then the
E 10
I 10
If the O_EXCL flag is set, and the file already exists, then the
E 10
.Fn open
will fail without affecting the file in any way.
This mechanism provides a simple exclusive access facility.
E 7
I 3
D 10
If the file exists but is a symbolic link, the open will fail
regardless of the existence of the file specified by the link.
E 3
D 7
.NH 4
Creating references to devices
E 7
I 7
The O_SHLOCK and O_EXLOCK allow the file to be atomically
E 10
I 10
For security reasons,
if the O_EXCL flag is set and the file is a symbolic link,
the open will fail regardless of the existence of the file
referenced by the link.
The O_SHLOCK and O_EXLOCK flags allow the file to be atomically
E 10
.Fn open 'ed
and
.Fn flock 'ed;
see section
D 9
.Xr 2.2.8
E 9
I 9
.Xr 2.2.7
E 9
for the semantics of
.Fn flock
style locks.
I 11
The O_ASYNC flag enables the SIGIO signal to be sent to
the process group of the opening process when I/O is possible,
e.g., upon availability of data to be read.
E 11
.Sh 4 "Creating references to devices
E 7
.PP
D 7
The file system allows entries which reference peripheral devices.
E 7
I 7
The filesystem allows entries which reference peripheral devices.
E 7
Peripherals are distinguished as \fIblock\fP or \fIcharacter\fP
devices according by their ability to support block-oriented
operations.
Devices are identified by their ``major'' and ``minor''
device numbers.  The major device number determines the kind
of peripheral it is, while the minor device number indicates
D 10
one of possibly many peripherals of that kind.
E 10
I 10
either one of possibly many peripherals of that kind, or special
characteristics of the peripheral.
E 10
D 7
Structured devices have all operations performed internally
E 7
I 7
Structured devices have all operations done internally
E 7
D 8
in ``block'' quantities while
unstructured devices often have a number of
D 7
special \fIioctl\fP operations, and may have input and output
D 3
performed in large units.
E 3
I 3
performed in varying units.
E 3
The \fImknod\fP call creates special entries:
E 7
I 7
special
.Fn ioctl
operations, and may have input and output
done in varying units.
E 8
I 8
in ``block'' quantities while unstructured devices
may have input and output done in varying units, and
may act as a non-seekable communications channel rather than a random-access
device.
E 8
The
.Fn mknod
call creates special entries:
E 7
.DS
I 7
.Fd mknod 3 "make a special file node
E 7
mknod(path, mode, dev);
D 7
char *path; int mode, dev;
E 7
I 7
char *path; mode_t mode; dev_t dev;
E 7
.DE
where \fImode\fP is formed from the object type
and access permissions.  The parameter \fIdev\fP is a configuration
dependent parameter used to identify specific character or
D 3
block i/o devices.
E 3
I 3
block I/O devices.
E 3
D 7
.NH 4
Portal creation\(dg
.PP
.FS
D 2
\(dg The \fIportal\fP call is not implemented in 4.2BSD.
E 2
I 2
\(dg The \fIportal\fP call is not implemented in 4.3BSD.
E 2
.FE
The call
E 7
I 7
.LP
Fifo's can be created in the filesystem using the call:
E 7
.DS
D 7
fd = portal(name, server, param, dtype, protocol, domain, socktype)
result int fd; char *name, *server, *param; int dtype, protocol;
int domain, socktype;
E 7
I 7
.Fd mkfifo 2 "make a fifo file
mkfifo(path, mode);
char *path; mode_t mode;
E 7
.DE
D 7
places a \fIname\fP in the file system name space that causes connection to a
server process when the name is used.
The portal call returns an active portal in \fIfd\fP as though an
access had occurred to activate an inactive portal, as now described.
.PP
D 4
When an inactive portal is accesseed, the system sets up a socket
E 4
I 4
When an inactive portal is accessed, the system sets up a socket
E 4
of the specified \fIsocktype\fP in the specified communications
\fIdomain\fP (see section 2.3), and creates the \fIserver\fP process,
giving it the specified \fIparam\fP as argument to help it identify
the portal, and also giving it the newly created socket as descriptor
number 0.  The accessor of the portal will create a socket in the same
\fIdomain\fP and \fIconnect\fP to the server.  The user will then
\fIwrap\fP the socket in the specified \fIprotocol\fP to create an object of
the required descriptor type \fIdtype\fP and proceed with the
operation which was in progress before the portal was encountered.
.PP
While the server process holds the socket (which it received as \fIfd\fP
from the \fIportal\fP call on descriptor 0 at activation) further references
will result in connections being made to the same socket.
.NH 4
File, device, and portal removal
.PP
A reference to a file, special device or portal may be removed with the
\fIunlink\fP call,
E 7
I 7
D 10
The \fImode\fP parameter is used solely specify the access permissions
on the newly created fifo.
E 10
I 10
The \fImode\fP parameter is used solely to specify the access
permissions of the newly created fifo.
E 10
I 9
.Sh 4 "Links and renaming
.PP
Links allow multiple names for a file to exist.
Links exist independently of the file to which they are linked.
.PP
Two types of links exist, \fIhard\fP links and \fIsymbolic\fP
links.  A hard link is a reference counting mechanism that
allows a file to have multiple names within the same filesystem.
Each link to a file is equivalent, referring to the file independently
of any other name.
Symbolic links cause string substitution
during the pathname interpretation process, and refer to a file name
rather than referring directly to a file.
.PP
Hard links and symbolic links have different
properties.  A hard link ensures that the target
file will always be accessible, even after its original
directory entry is removed; no such guarantee exists for a symbolic link.
D 11
Symbolic links can span filesystems boundaries.
E 11
I 11
Unlike hard links,
symbolic links can refernce directories and span filesystems boundaries.
An
.Fn lstat
I 12
(see section
.Xr 2.2.4 )
E 12
call on a hard link will return the information about the
D 12
file (or directory) that the link references.
E 12
I 12
file (or directory) that the link references while an
.Fn lstat
call on a symbolic link will return information about the link itself.
E 12
A symbolic link does not have an owner,
group, permissions, access and modification times, etc.
The only attributes returned from an
.Fn lstat
that refer to the symbolic link itself
are the file type (S_IFLNK), size, blocks, and link count (always 1).
The other attributes are filled in from
the directory that contains the link.
E 11
.LP
The following calls create a new link, named \fIpath2\fP,
to \fIpath1\fP:
.DS
.Fd link 2 "make a hard file link
link(path1, path2);
char *path1, *path2;
.DE
.DS
.Fd symlink 2 "make a symbolic link to a file
symlink(path1, path2);
char *path1, *path2;
.DE
The
.Fn unlink
primitive may be used to remove
either type of link. 
.LP
If a file is a symbolic link, the ``value'' of the
link may be read with the
.Fn readlink
call:
.DS
.Fd readlink 3 "read value of a symbolic link
len = readlink(path, buf, bufsize);
result int len; char *path; result char *buf; int bufsize;
.DE
D 10
This call returns, in \fIbuf\fP, the null-terminated string
substituted into pathnames passing through \fIpath\fP\|.
E 10
I 10
This call returns, in \fIbuf\fP, the string substituted into
pathnames passing through \fIpath\fP\|.
(This string is not NULL terminated.)
E 10
.LP
Atomic renaming of filesystem resident objects is possible with the
.Fn rename
call:
.DS
.Fd rename 2 "change the name of a file
rename(oldname, newname);
char *oldname, *newname;
.DE
where both \fIoldname\fP and \fInewname\fP must be
in the same filesystem.
I 10
If either \fIoldname\fP or \fInewname\fP is a directory,
then the other also must be a directory for the
.Fn rename
to succeed.
E 10
If \fInewname\fP exists and is a directory, then it must be empty.
E 9
.Sh 4 "File, device, and fifo removal
.LP
A reference to a file, special device or fifo may be removed with the
.Fn unlink
call:
E 7
.DS
I 7
.Fd unlink 1 "remove directory entry
E 7
unlink(path);
char *path;
.DE
The caller must have write access to the directory in which
the file is located for this call to be successful.
I 8
When the last name for a file has been removed, the file may no longer
be opened; the file itself is removed once any existing references
have been closed.
E 8
D 7
.NH 3
Reading and modifying file attributes
.PP
E 7
I 7
.LP
All current access to a file can be revoked using the call:
.DS
.Fd revoke 1 "revoke file access
revoke(path);
char *path;
.DE
Subsequent operations on any descriptors open at the time of the
.Fn revoke
fail, with the exceptions that a
D 10
.Fn read
from a character device file which has been
revoked returns a count of zero (end of file), and a
E 10
.Fn close
D 10
call will succeed.
E 10
I 10
call will succeed, and a
.Fn read
from a character device file which has been revoked returns a count
of zero (end of file).
E 10
If the file is a special file for a device which is open,
the device close function is called as if all open references
to the file had been closed.
.Fn Open 's
done after the
.Fn revoke
D 8
will succeed.
E 8
I 8
may succeed.
E 8
This call is most useful for revoking access to a terminal line after
a hangup in preparation for reuse by a new login session.
I 8
Access to a controlling terminal is automatically revoked
when the session leader for the session exits.
E 8
.Sh 3 "Reading and modifying file attributes
.LP
E 7
Detailed information about the attributes of a file
may be obtained with the calls:
.DS
D 7
#include <sys/stat.h>

E 7
I 7
.Fd stat 2 "get file status
E 7
stat(path, stb);
char *path; result struct stat *stb;
D 7

E 7
I 7
.DE
.DS
.Fd fstat 2 "get file status
E 7
fstat(fd, stb);
int fd; result struct stat *stb;
.DE
The \fIstat\fP structure includes the file
type, protection, ownership, access times,
size, and a count of hard links.
If the file is a symbolic link, then the status of the link
itself (rather than the file the link references)
D 7
may be found using the \fIlstat\fP call:
E 7
I 7
D 10
may be found using the
E 10
I 10
may be obtained using the
E 10
.Fn lstat
call:
E 7
.DS
I 7
.Fd lstat 2 "get file status
E 7
lstat(path, stb);
char *path; result struct stat *stb;
.DE
.PP
D 7
Newly created files are assigned the user id of the
process that created it and the group id of the directory
E 7
I 7
D 10
Newly created files are assigned the user-id of the
process that created it and the group-id of the directory
E 7
in which it was created.  The ownership of a file may
D 7
be changed by either of the calls
E 7
I 7
be changed by either of the calls:
E 10
I 10
Newly created files are assigned the user ID of the process that created
them and the group ID of the directory in which they were created.
The ownership of a file may be changed by either of the calls:
E 10
E 7
.DS
I 7
.Fd chown 3 "change owner and group of a file
E 7
chown(path, owner, group);
D 10
char *path; int owner, group;
E 10
I 10
char *path; uid_t owner; gid_t group;
E 10
D 7

E 7
I 7
.DE
.DS
.Fd fchown 3 "change owner and group of a file
E 7
fchown(fd, owner, group);
D 10
int fd, owner, group;
E 10
I 10
int fd, uid_t owner; gid_t group;
E 10
.DE
.PP
In addition to ownership, each file has three levels of access
protection associated with it.  These levels are owner relative,
D 10
group relative, and global (all users and groups).  Each level
of access has separate indicators for read permission, write
permission, and execute permission.
E 10
I 10
group relative, and other.
Each level of access has separate indicators for read permission,
write permission, and execute permission.
E 10
The protection bits associated with a file may be set by either
of the calls:
.DS
I 7
.Fd chmod 2 "change mode of file
E 7
chmod(path, mode);
D 10
char *path; int mode;
E 10
I 10
char *path; mode_t mode;
E 10
D 7

E 7
I 7
.DE
.DS
.Fd fchmod 2 "change mode of file
E 7
fchmod(fd, mode);
D 10
int fd, mode;
E 10
I 10
int fd, mode_t mode;
E 10
.DE
where \fImode\fP is a value indicating the new protection
D 3
of the file.  The file mode is a three digit octal number.
Each digit encodes read access as 4, write access as 2 and execute
access as 1, or'ed together.  The 0700 bits describe owner
access, the 070 bits describe the access rights for processes in the same
group as the file, and the 07 bits describe the access rights
for other processes. 
E 3
I 3
D 7
of the file, as listed in section 2.2.3.2.
E 7
I 7
of the file, as listed in section
.Xr 2.2.3.2 .
E 7
E 3
.PP
I 7
D 8
Each file has a set of thirty-two flags associated with it.
E 8
I 8
Each file has a set of flags stored as a bit mask associated with it.
E 8
These flags are returned in the \fIstat\fP structure and
are set using the calls:
.DS
.Fd chflags 2 "set file flags
chflags(path, flags);
char *path; u_long flags;
.DE
.DS
.Fd fchflags 2 "set file flags
fchflags(fd, flags);
int fd; u_long flags;
.DE
I 13
.ne 1i
E 13
The flags specified are formed by or'ing the following values:
.DS
.TS
l l.
UF_NODUMP	Do not dump the file.
UF_IMMUTABLE	The file may not be changed.
UF_APPEND	The file may only be appended to.
SF_IMMUTABLE	The file may not be changed.
SF_APPEND	The file may only be appended to.
.TE
.DE
D 8
The UF_IMMUTABLE and UF_APPEND
E 8
I 8
The UF_NODUMP, UF_IMMUTABLE and UF_APPEND
E 8
flags may be set or unset by either the owner of a file or the super-user.
The SF_IMMUTABLE and SF_APPEND
flags may only be set or unset by the super-user.
They may be set at any time, but normally may only be unset when
the system is in single-user mode.
.LP
E 7
Finally, the access and modify times on a file may be set by the call:
.DS
I 7
.Fd utimes 2 "set file access and modification times
E 7
D 10
utimes(path, tvp)
E 10
I 10
utimes(path, tvp);
E 10
char *path; struct timeval *tvp[2];
.DE
D 7
This is particularly useful when moving files between media, to
preserve relationships between the times the file was modified.
.NH 3
Links and renaming
E 7
I 7
This is particularly useful when moving files between media,
D 10
to preserve relationships between the times the file was modified.
E 10
I 10
to preserve file access and modification times.
E 10
D 9
.Sh 3 "Links and renaming
E 9
I 9
.Sh 3 "Checking accessibility
E 9
E 7
.PP
D 7
Links allow multiple names for a file
to exist.  Links exist independently of the file linked to.
E 7
I 7
D 9
Links allow multiple names for a file to exist.
Links exist independently of the file to which they are linked.
E 7
.PP
Two types of links exist, \fIhard\fP links and \fIsymbolic\fP
links.  A hard link is a reference counting mechanism that
D 7
allows a file to have multiple names within the same file
system.  Symbolic links cause string substitution
E 7
I 7
allows a file to have multiple names within the same filesystem.
I 8
Each link to a file is equivalent, referring to the file independently
of any other name.
E 8
Symbolic links cause string substitution
E 7
D 8
during the pathname interpretation process.
E 8
I 8
during the pathname interpretation process, and refer to a file name
rather than referring directly to a file.
E 8
.PP
Hard links and symbolic links have different
D 7
properties.  A hard link insures the target
E 7
I 7
D 8
properties.  A hard link ensures the target
E 8
I 8
properties.  A hard link ensures that the target
E 8
E 7
file will always be accessible, even after its original
directory entry is removed; no such guarantee exists for a symbolic link.
D 7
Symbolic links can span file systems boundaries.
.PP
E 7
I 7
Symbolic links can span filesystems boundaries.
.LP
E 7
The following calls create a new link, named \fIpath2\fP,
to \fIpath1\fP:
E 9
I 9
A process running with
different real and effective user-ids
may interrogate the accessibility of a file to the
real user by using the
.Fn access
call:
E 9
.DS
I 7
D 9
.Fd link 2 "make a hard file link
E 7
link(path1, path2);
char *path1, *path2;
E 9
I 9
.Fd access 2 "check access permissions of a file or pathname
accessible = access(path, how);
result int accessible; char *path; int how;
E 9
D 7

E 7
I 7
.DE
I 9
D 10
Here \fIhow\fP is constructed by or'ing the following bits, defined
E 10
I 10
\fIHow\fP is constructed by OR'ing the following bits, defined
E 10
in \fI<unistd.h>\fP:
E 9
.DS
D 9
.Fd symlink 2 "make a symbolic link to a file
E 7
symlink(path1, path2);
char *path1, *path2;
E 9
I 9
.TS
l l.
F_OK	/* file exists */
D 10
X_OK	/* file is executable */
E 10
I 10
X_OK	/* file is executable/searchable */
E 10
W_OK	/* file is writable */
R_OK	/* file is readable */
.TE
E 9
.DE
I 9
The presence or absence of advisory locks does not affect the
result of
.Fn access .
.PP
E 9
D 7
The \fIunlink\fP primitive may be used to remove
E 7
I 7
The
D 9
.Fn unlink
primitive may be used to remove
E 7
either type of link. 
D 7
.PP
E 7
I 7
.LP
E 7
If a file is a symbolic link, the ``value'' of the
D 7
link may be read with the \fIreadlink\fP call,
E 7
I 7
link may be read with the
.Fn readlink
call:
E 9
I 9
.Fn pathconf
and
.Fn fpathconf
D 10
functions provides a method for applications to determine the current
E 10
I 10
functions provide a method for applications to determine the current
E 10
value of a configurable system limit or option variable associated
with a pathname or file descriptor:
E 9
E 7
.DS
I 7
D 9
.Fd readlink 3 "read value of a symbolic link
E 7
len = readlink(path, buf, bufsize);
D 7
result int len; result char *path, *buf; int bufsize;
E 7
I 7
result int len; char *path; result char *buf; int bufsize;
E 9
I 9
.Fd pathconf 2 "get configurable pathname variables
D 10
ans = pathconf(path, name)
result int ans; char *path; int name;
E 10
I 10
ans = pathconf(path, name);
result long ans; char *path; int name;
E 10
E 9
E 7
.DE
D 9
This call returns, in \fIbuf\fP, the null-terminated string
substituted into pathnames passing through \fIpath\fP\|.
D 7
.PP
Atomic renaming of file system resident objects is possible
with the \fIrename\fP call:
E 7
I 7
.LP
Atomic renaming of filesystem resident objects is possible with the
.Fn rename
call:
E 9
E 7
.DS
I 7
D 9
.Fd rename 2 "change the name of a file
E 7
rename(oldname, newname);
char *oldname, *newname;
E 9
I 9
.Fd fpathconf 2 "get configurable pathname variables
D 10
ans = fpathconf(fd, name)
result int ans; int fd, name;
E 10
I 10
ans = fpathconf(fd, name);
result long ans; int fd, name;
E 10
E 9
.DE
D 9
where both \fIoldname\fP and \fInewname\fP must be
D 7
in the same file system.
E 7
I 7
in the same filesystem.
E 7
If \fInewname\fP exists and is a directory, then it must be empty.
E 9
I 9
For
.Fn pathconf ,
the \fIpath\fP argument is the name of a file or directory.
For
.Fn fpathconf ,
the \fIfd\fP argument is an open file descriptor.
The \fIname\fP argument specifies the system variable to be queried.
Symbolic constants for each name value are found in the include file
\fI<unistd.h>\fP.
E 9
D 7
.NH 3
Extension and truncation
E 7
I 7
.Sh 3 "Extension and truncation
E 7
.PP
Files are created with zero length and may be extended
simply by writing or appending to them.  While a file is
open the system maintains a pointer into the file
indicating the current location in the file associated with
the descriptor.  This pointer may be moved about in the
file in a random access fashion.
D 7
To set the current offset into a file, the \fIlseek\fP
call may be used,
E 7
I 7
To set the current offset into a file, the
.Fn lseek
call may be used:
E 7
.DS
I 7
.Fd lseek 3 "reposition read/write file offset
E 7
oldoffset = lseek(fd, offset, type);
result off_t oldoffset; int fd; off_t offset; int type;
.DE
I 13
.ne 1i
E 13
D 3
where \fItype\fP is given in <sys/file.h> as one of,
E 3
I 3
D 7
where \fItype\fP is given in \fI<sys/file.h>\fP as one of:
E 7
I 7
D 10
where \fItype\fP is given in \fI<sys/unistd.h>\fP as one of:
E 10
I 10
where \fItype\fP is defined by \fI<unistd.h>\fP as one of:
E 10
E 7
E 3
.DS
D 7
._d
#define	L_SET	0	/* set absolute file offset */
#define	L_INCR	1	/* set file offset relative to current position */
#define	L_XTND	2	/* set offset relative to end-of-file */
E 7
I 7
.TS
l l.
SEEK_SET	/* set file offset to offset */
SEEK_CUR	/* set file offset to current plus offset */
SEEK_END	/* set file offset to EOF plus offset */
.TE
E 7
.DE
D 7
The call ``lseek(fd, 0, L_INCR)''
E 7
I 7
The call ``lseek(fd, 0, SEEK_CUR)''
E 7
returns the current offset into the file.
.PP
D 10
Files may have ``holes'' in them.  Holes are void areas in the
linear extent of the file where data has never been
written.  These may be created by seeking to
a location in a file past the current end-of-file and writing.
E 10
I 10
Files may have ``holes'' in them.
Holes are areas in the linear extent of the file where data has never
been written.
These may be created by seeking to a location in a file past the
current end-of-file and writing.
E 10
Holes are treated by the system as zero valued bytes.
D 7
.PP
E 7
I 7
.LP
E 7
D 9
A file may be truncated with either of the calls:
E 9
I 9
A file may be extended or truncated with either of the calls:
E 9
.DS
I 7
.Fd truncate 2 "truncate a file to a specified length
E 7
truncate(path, length);
D 7
char *path; int length;

E 7
I 7
char *path; off_t length;
.DE
.DS
.Fd ftruncate 2 "truncate a file to a specified length
E 7
ftruncate(fd, length);
D 7
int fd, length;
E 7
I 7
int fd; off_t length;
E 7
.DE
D 9
reducing the size of the specified file to \fIlength\fP bytes.
E 9
I 9
changing the size of the specified file to \fIlength\fP bytes.
E 9
D 7
.NH 3
Checking accessibility
E 7
.PP
I 7
Unless opened with the O_FSYNC flag,
writes to files are held for an indeterminate period of time
in the system buffer cache.
The call:
.DS
.Fd fsync 1 "synchronize in-core state of a file with that on disk
D 10
fsync(fd)
E 10
I 10
fsync(fd);
E 10
int fd;
.DE
ensures that the contents of a file are committed to disk
before returning.
This feature is used by applications such as editors that
D 10
want to ensure the integrity of a new file before
deleting the backup copy.
E 10
I 10
want to ensure the integrity of a new file before continuing.
E 10
D 9
.Sh 3 "Checking accessibility
.PP
E 7
A process running with
D 7
different real and effective user ids
E 7
I 7
different real and effective user-ids
E 7
may interrogate the accessibility of a file to the
D 7
real user by using
the \fIaccess\fP call:
E 7
I 7
real user by using the
.Fn access
call:
E 7
.DS
I 7
.Fd access 2 "check access permissions of a file or pathname
E 7
accessible = access(path, how);
result int accessible; char *path; int how;
.DE
Here \fIhow\fP is constructed by or'ing the following bits, defined
D 3
in <sys/file.h>:
E 3
I 3
D 7
in \fI<sys/file.h>\fP:
E 7
I 7
in \fI<unistd.h>\fP:
E 7
E 3
.DS
D 7
._d
#define	F_OK	0	/* file exists */
#define	X_OK	1	/* file is executable */
#define	W_OK	2	/* file is writable */
#define	R_OK	4	/* file is readable */
E 7
I 7
.TS
l l.
F_OK	/* file exists */
X_OK	/* file is executable */
W_OK	/* file is writable */
R_OK	/* file is readable */
.TE
E 7
.DE
The presence or absence of advisory locks does not affect the
D 7
result of \fIaccess\fP\|.
.NH 3
Locking
E 7
I 7
result of
.Fn access .
E 7
.PP
D 7
The file system provides basic facilities that allow cooperating processes
E 7
I 7
The
.Fn pathconf
and
.Fn fpathconf
functions provides a method for applications to determine the current
value of a configurable system limit or option variable associated
with a pathname or file descriptor:
.DS
.Fd pathconf 2 "get configurable pathname variables
ans = pathconf(path, name)
result int ans; char *path; int name;
.DE
.DS
.Fd fpathconf 2 "get configurable pathname variables
ans = fpathconf(fd, name)
result int ans; int fd, name;
.DE
For
.Fn pathconf ,
the \fIpath\fP argument is the name of a file or directory.
For
.Fn fpathconf ,
the \fIfd\fP argument is an open file descriptor.
The \fIname\fP argument specifies the system variable to be queried.
Symbolic constants for each name value are found in the include file
\fI<unistd.h>\fP.
E 9
.Sh 3 "Locking
.PP
The filesystem provides basic facilities that allow cooperating processes
E 7
to synchronize their access to shared files.  A process may
place an advisory \fIread\fP or \fIwrite\fP lock on a file,
so that other cooperating processes may avoid interfering
with the process' access.  This simple mechanism
D 7
provides locking with file granularity.  More granular
locking can be built using the IPC facilities to provide a lock
manager.
E 7
I 7
provides locking with file granularity.
Byte range locking is available with
.Fn fcntl ;
see section
.Xr 1.5.4 .
E 7
The system does not force processes to obey the locks;
they are of an advisory nature only.
D 7
.PP
Locking is performed after an \fIopen\fP call by applying the
\fIflock\fP primitive,
E 7
I 7
.LP
Locking can be done as part of the
.Fn open
call (see section
.Xr 2.2.3.2 )
or after an
.Fn open
call by applying the
.Fn flock
primitive:
E 7
.DS
I 7
.Fd flock 2 "apply or remove an advisory lock on an open file
E 7
flock(fd, how);
int fd, how;
.DE
D 3
where the \fIhow\fP parameter is formed from bits defined in <sys/file.h>:
E 3
I 3
D 7
where the \fIhow\fP parameter is formed from bits defined in \fI<sys/file.h>\fP:
E 7
I 7
where the \fIhow\fP parameter is formed from bits
D 10
defined in \fI<sys/fcntl.h>\fP:
E 10
I 10
defined in \fI<fcntl.h>\fP:
E 10
E 7
E 3
.DS
D 7
._d
#define	LOCK_SH	1	/* shared lock */
#define	LOCK_EX	2	/* exclusive lock */
#define	LOCK_NB	4	/* don't block when locking */
#define	LOCK_UN	8	/* unlock */
E 7
I 7
.TS
l l.
LOCK_SH	/* shared file lock */
LOCK_EX	/* exclusive file lock */
LOCK_NB	/* don't block when locking */
LOCK_UN	/* unlock file */
.TE
E 7
.DE
Successive lock calls may be used to increase or
decrease the level of locking.  If an object is currently
D 7
locked by another process when a \fIflock\fP call is made,
the caller will be blocked until the current lock owner
E 7
I 7
locked by another process when a
.Fn flock
call is made, the caller will be blocked until the current lock owner
E 7
releases the lock; this may be avoided by including LOCK_NB
in the \fIhow\fP parameter.
Specifying LOCK_UN removes all locks associated with the descriptor.
Advisory locks held by a process are automatically deleted when
the process terminates.
D 7
.NH 3
Disk quotas
E 7
I 7
.Sh 3 "Disk quotas
E 7
.PP
D 7
As an optional facility, each file system may be requested to
impose limits on a user's disk usage.
E 7
I 7
D 10
As an optional facility, each local filesystem may be requested to
impose limits on a user's or a group's disk usage.
E 10
I 10
As an optional facility, each local filesystem can impose limits on a
user's or group's disk usage.
E 10
E 7
Two quantities are limited: the total amount of disk space which
D 7
a user may allocate in a file system and the total number of files
a user may create in a file system.  Quotas are expressed as
E 7
I 7
a user or group may allocate in a filesystem and the total number of files
a user or group may create in a filesystem.  Quotas are expressed as
E 7
\fIhard\fP limits and \fIsoft\fP limits.  A hard limit is
D 7
always imposed; if a user would exceed a hard limit, the operation
E 7
I 7
always imposed; if a user or group would exceed a hard limit, the operation
E 7
which caused the resource request will fail.  A soft limit results
D 7
in the user receiving a warning message, but with allocation succeeding.
E 7
I 7
in the user or group receiving a warning message,
but with allocation succeeding.
E 7
Facilities are provided to turn soft limits into hard limits if a
D 7
user has exceeded a soft limit for an unreasonable period of time.
.PP
To enable disk quotas on a file system the \fIsetquota\fP call
is used:
E 7
I 7
user or group has exceeded a soft limit for an unreasonable period of time.
.LP
The
.Fn quotactl
call enables, disables and manipulates filesystem quotas:
E 7
.DS
D 7
setquota(special, file)
char *special, *file;
E 7
I 7
.Fd quotactl 4 "manipulate filesystem quotas
D 10
quotactl(path, cmd, id, addr)
E 10
I 10
quotactl(path, cmd, id, addr);
E 10
char *path; int cmd; int id; char *addr;
E 7
.DE
D 7
where \fIspecial\fP refers to a structured device file where
a mounted file system exists, and
\fIfile\fP refers to a disk quota file (residing on the file
system associated with \fIspecial\fP) from which user quotas
should be obtained.  The format of the disk quota file is 
implementation dependent.
.PP
To manipulate disk quotas the \fIquota\fP call is provided:
E 7
I 7
A quota control command given by cmd operates on the given filename path
D 10
for the given user id. The address of an optional command specific data
E 10
I 10
for the given user ID. The address of an optional command specific data
E 10
structure, addr, may be given.
The supported commands include:
E 7
.DS
D 7
#include <sys/quota.h>

quota(cmd, uid, arg, addr)
int cmd, uid, arg; caddr_t addr;
E 7
I 7
.TS
l l.
Q_QUOTAON	/* enable quotas */
Q_QUOTAOFF	/* disable quotas */
Q_GETQUOTA	/* get limits and usage */
Q_SETQUOTA	/* set limits and usage */
Q_SETUSE	/* set usage */
Q_SYNC	/* sync disk copy of a filesystems quotas */
.TE
E 7
.DE
D 7
The indicated \fIcmd\fP is applied to the user ID \fIuid\fP.
The parameters \fIarg\fP and \fIaddr\fP are command specific.
D 3
The file <sys/quota.h> contains definitions pertinent to the
E 3
I 3
The file \fI<sys/quota.h>\fP contains definitions pertinent to the
E 3
use of this call.
E 7
I 7
.Sh 3 "Remote filesystems
.LP
D 8
There are two system calls intended to help support remote filesystems.
E 8
I 8
There are two system calls intended to help support the remote filesystem
implementation.
E 8
The call:
.DS
.Fd nfssvc 2 "NFS services
nfssvc(flags, argstructp);
int flags, void *argstructp;
.DE
is used by the NFS daemons to pass information into
and out of the kernel and also to enter the kernel as a server daemon.
The flags argument consists of several bits that show what action is to
D 10
be taken once in the kernel and the argstructp points to one of three
E 10
I 10
be taken once in the kernel and \fIargstructp\fP points to one of three
E 10
structures depending on which bits are set in flags.
.LP
The call:
.DS
.Fd getfh 2 "get file handle
getfh(path, fhp);
char *path; result fhandle_t *fhp;
.DE
returns a file handle for the specified file or directory in the
file handle pointed to by fhp.
This file handle can then be used in future calls to NFS to access 
the file without the need to repeat the pathname translation.
This system call is restricted to the superuser.
.Sh 3 "Other filesystems
.LP
The kernel supports many other filesystems.
These include:
.IP \(bu
The log-structured filesystem. It provides an alternate disk
layout than the fast filesystem optimized for writing rather
than reading.
For further information see the
.Xr mount_lfs (8)
manual page.
.\"
.\" We currently do not document the LFS calls
.\" .Fd lfs_bmapv 3
.\" .Fd lfs_markv 3
.\" .Fd lfs_segclean 2
.\" .Fd lfs_segwait 2
.IP \(bu
The ISO-standard 9660 filesystem with Rock Ridge extensions used for CD-ROMs.
For further information see the
.Xr mount_cd9660 (8)
manual page.
.IP \(bu
The file descriptor mapping filesystem.
For further information see the
.Xr mount_fdesc (8)
manual page.
.IP \(bu
The /proc filesystem as an alternative for debuggers.
For further information see section
.Xr 2.5.1
and the
.Xr mount_procfs (8)
manual page.
.IP \(bu
The memory-based filesystem,
used primarily for fast but ethereal uses such as /tmp.
For further information see the
.Xr mount_mfs (8)
manual page.
.IP \(bu
The kernel variable filesystem, used as an alternative to
.Fn sysctl .
For further information see section
.Xr 1.7.1
and the
.Xr mount_kernfs (8)
manual page.
.IP \(bu
The portal filesystem, used to mount processes in the filesystem.
For further information see the
.Xr mount_portal (8)
manual page.
.IP \(bu
D 10
The uid/gid remapping filesystem, used primary above NFS filesystems
E 10
I 10
The uid/gid remapping filesystem, usually layered above NFS filesystems
E 10
exported to an outside administrative domain.
For further information see the
.Xr mount_umap (8)
manual page.
.IP \(bu
The union filesystem, used to place a writable filesystem above
a read-only filesystem.
This filesystem is useful for compiling sources on a CD-ROM
without having to copy the CD-ROM contents to writable disk.
For further information see the
.Xr mount_union (8)
manual page.
E 7
E 1
