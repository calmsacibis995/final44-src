h24544
s 00002/00002/00502
d D 8.1 93/06/08 14:06:42 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00212/00034/00292
d D 5.3 93/06/08 11:42:46 mckusick 3 2
c update from Rick Macklem
e
s 00116/00177/00210
d D 5.2 93/06/05 16:42:56 mckusick 2 1
c merge together for NFS paper
e
s 00387/00000/00000
d D 5.1 92/07/02 16:24:36 bostic 1 0
c date and time created 92/07/02 16:24:36 by bostic
e
u
U
t
T
I 2
D 4
.\" Copyright (c) 1993 The Regents of the University of California.
.\" All rights reserved.
E 4
I 4
.\" Copyright (c) 1993
.\"	The Regents of the University of California.  All rights reserved.
E 4
.\"
.\" This document is derived from software contributed to Berkeley by
.\" Rick Macklem at The University of Guelph.
.\"
.\" %sccs.include.redist.roff%
.\"
E 2
I 1
.\"	%W% (Berkeley) %G%
.\"
D 2
.\" troff -ms
.\" Here is half a paper on the cache consistency protocol. It won't
.\" make much sense unless you have read the [Nelson88] or [Srinivasan89]
.\" and [Gray89] references.
.TL
PRELIMINARY DRAFT: Not Quite NFS, Crash Tolerant Cache Consistency for NFS
.AU
Rick Macklem
rick@snowhite.cis.uoguelph.ca
.AI
University of Guelph
.AB
.PP
E 2
I 2
.sh 1 "Not Quite NFS, Crash Tolerant Cache Consistency for NFS"
.pp
E 2
Not Quite NFS (NQNFS) is an NFS like protocol designed to maintain full cache
D 2
consistency between clients in a crash tolerant manner. It is an adaptation
of the NFS protocol such that the server supports both NFS
E 2
I 2
consistency between clients in a crash tolerant manner.
It is an adaptation of the NFS protocol such that the server supports both NFS
E 2
and NQNFS clients while maintaining full consistency between the server and
NQNFS clients.
D 2
It borrows heavily from work done on Spritely-NFS [Srinivasan89], but uses
Leases [Gray89] to avoid the need to recover server state information
E 2
I 2
This section borrows heavily from work done on Spritely-NFS [Srinivasan89],
but uses Leases [Gray89] to avoid the need to recover server state information
E 2
after a crash.
D 2
.AE
.SH
1. Overview
.PP
The protocol maintains cache consistency by using a somewhat Sprite [Nelson88] like
protocol, but is based on short term leases\** instead of hard state information
E 2
I 2
The reader is strongly encouraged to read these references before
trying to grasp the material presented here.
.sh 2 "Overview"
.pp
The protocol maintains cache consistency by using a somewhat
Sprite [Nelson88] like protocol,
but is based on short term leases\** instead of hard state information
E 2
about open files.
D 2
.FS
A lease is a ticket permitting an activity that is valid until some expiry time.
.FE
E 2
I 2
.(f
\** A lease is a ticket permitting an activity that is
valid until some expiry time.
.)f
E 2
The basic principal is that the protocol will disable client caching of a
file whenever that file is write shared\**.
D 2
.FS
Write sharing occurs when at least one client is modifying a file while
E 2
I 2
.(f
\** Write sharing occurs when at least one client is modifying a file while
E 2
other client(s) are reading the file.
D 2
.FE
E 2
I 2
.)f
E 2
Whenever a client wishes to cache data for a file it must hold a valid lease.
There are three types of leases: read caching, write caching and non-caching.
The latter type requires that all file operations be done synchronously with
the server via. RPCs.
A read caching lease allows for client data caching, but no file modifications
may be done.
A write caching lease allows for client caching of writes,
but requires that all writes be pushed to the server when the lease expires.
If a client has dirty buffers\**
D 2
.FS
cached write data not yet pushed (written) to the
server
.FE
E 2
I 2
.(f
\** Cached write data is not yet pushed (written) to the server.
.)f
E 2
when a write cache lease has almost expired, it will attempt to
extend the lease but is required to push the dirty buffers if extension fails.
A client gets leases by either doing a \fBGetLease RPC\fR or by piggybacking
a \fBGetLease Request\fR onto another RPC. Piggybacking is supported for the
frequent RPCs Getattr, Setattr, Lookup, Readlink, Read, Write and Readdir
in an effort to minimize the number of \fBGetLease RPCs\fR required.
All leases are at the granularity of a file, since all NFS RPCs operate on
individual files and NFS has no intrinsic notion of a file hierarchy.
D 2
Directories, symbolic links and file attributes may be read cached but are not write cached.
E 2
I 2
Directories, symbolic links and file attributes may be read cached but
are not write cached.
E 2
The exception here is the attribute file_size, which is updated during cached
writing on the client to reflect a growing file.
D 2
.PP
E 2
I 2
.pp
E 2
It is the server's responsibility to ensure that consistency is maintained
among the NQNFS clients by disabling client caching whenever a server file
operation would cause inconsistencies.
D 2
This occurs whenever a client has a write caching lease and any other client\**
.FS
including local operations on the server
.FE
E 2
I 2
The possibility of inconsistencies occurs whenever a client has
a write caching lease and any other client,
or local operations on the server,
E 2
tries to access the file or when
a modify operation is attempted on a file being read cached by client(s).
At this time, the server sends an \fBeviction notice\fR to all clients holding
the lease and then waits for lease termination.
Lease termination occurs when a \fBvacated the premises\fR message has been
received from all the clients that have signed the lease or when the lease
expires via. timeout.
The message pair \fBeviction notice\fR and \fBvacated the premises\fR roughly
correspond to a Sprite server\(->client callback, but are not implemented as an
actual RPC, to avoid the server waiting indefinitely for a reply from a dead
client.
D 2
.PP
E 2
I 2
.pp
E 2
Server consistency checking can be viewed as issuing intrinsic leases for a
file operation for the duration of the operation only. For example, the
\fBCreate RPC\fR will get an intrinsic write lease on the directory in which
the file is being created, disabling client read caches for that directory.
D 2
.PP
E 2
I 2
.pp
E 2
By relegating this responsibility to the server, consistency between the
server and NQNFS clients is maintained when NFS clients are modifying the
file system as well.\**
D 2
.FS
The NFS clients will continue to be \fIapproximately\fR consistent with
E 2
I 2
.(f
\** The NFS clients will continue to be \fIapproximately\fR consistent with
E 2
the server.
D 2
.FE
.PP
E 2
I 2
.)f
.pp
E 2
The leases are issued as time intervals to avoid the requirement of time of day
clock synchronization. There are three important time constants known to
the server. The \fBmaximum_lease_term\fR sets an upper bound on lease duration.
The \fBclock_skew\fR is added to all lease terms on the server to correct for
differing clock speeds between the client and server and \fBwrite_slack\fR is
D 2
the number of seconds the server is willing to wait for a client with an expired
write caching lease to push dirty writes.
.PP
E 2
I 2
the number of seconds the server is willing to wait for a client with
an expired write caching lease to push dirty writes.
.pp
E 2
The server maintains a \fBmodify_revision\fR number for each file. It is
defined as a unsigned quadword integer that is never zero and that must
increase whenever the corresponding file is modified on the server.
It is used
by the client to determine whether or not cached data for the file is
stale.
Generating this value is easier said than done. The current implementation
D 3
uses the following technique, which I believe to be adequate.
E 3
I 3
uses the following technique, which is believed to be adequate.
E 3
The high order longword is stored in the ufs inode and is initialized to one
when an inode is first allocated.
The low order longword is stored in main memory only and is initialized to
zero when an inode is read in from disk.
D 2
When the file is modified for the first time within a given second of wall clock
time, the high order longword is incremented by one and the low order longword
reset to zero. For subsequent modifications within the same second of wall clock
E 2
I 2
When the file is modified for the first time within a given second of
wall clock time, the high order longword is incremented by one and
the low order longword reset to zero.
For subsequent modifications within the same second of wall clock
E 2
time, the low order longword is incremented. If the low order longword wraps
around to zero, the high order longword is incremented again.
Since the high order longword only increments once per second and the inode
is pushed to disk frequently during file modification, this implies
0 \(<= Current\(miDisk \(<= 5.
When the inode is read in from disk, 10
is added to the high order longword, which ensures that the quadword
is greater than any value it could have had before a crash.
This introduces apparent modifications every time the inode falls out of
the LRU inode cache, but this should only reduce the client caching performance
by a (hopefully) small margin.
D 2
.SH
2. Crash Recovery and other Failure Scenarios
.PP
E 2
I 2
.sh 2 "Crash Recovery and other Failure Scenarios"
.pp
E 2
The server must maintain the state of all the current leases held by clients.
The nice thing about short term leases is that maximum_lease_term seconds
after the server stops issuing leases, there are no current leases left.
As such, server crash recovery does not require any state recovery. After
rebooting, the server refuses to service any RPCs except for writes until
write_slack seconds after the last lease would have expired\**.
D 2
.FS
The last lease expiry time may be safely estimated as
E 2
I 2
.(f
\** The last lease expiry time may be safely estimated as
E 2
"boottime+maximum_lease_term+clock_skew" for machines that cannot store
it in nonvolatile RAM.
D 2
.FE
E 2
I 2
.)f
E 2
By then, the server would not have any outstanding leases to recover the
state of and the clients have had at least write_slack seconds to push dirty
writes to the server and get the server sync'd up to date. After this, the
server simply services requests in a manner similar to NFS.
D 2
In an effort to minimize the effect of "recovery storms" [Baker91], the server replies
\fBtry_again_later\fR to the RPCs it is not
E 2
I 2
In an effort to minimize the effect of "recovery storms" [Baker91],
the server replies \fBtry_again_later\fR to the RPCs it is not
E 2
yet ready to service.
D 2
.PP
E 2
I 2
.pp
E 2
After a client crashes, the server may have to wait for a lease to timeout
before servicing a request if write sharing of a file with a cachable lease
on the client is about to occur.
As for the client, it simply starts up getting any leases it now needs. Any
outstanding leases for that client on the server prior to the crash will either be renewed or expire
via timeout.
D 2
.PP
E 2
I 2
.pp
E 2
Certain network partitioning failures are more problematic. If a client to
server network connection is severed just before a write caching lease expires,
the client cannot push the dirty writes to the server. After the lease expires
on the server, the server permits other clients to access the file with the
potential of getting stale data. Unfortunately I believe this failure scenario
is intrinsic in any delay write caching scheme unless the server is required to
wait \fBforever\fR for a client to regain contact\**.
D 2
.FS
Gray and Cheriton avoid this problem by using a \fBwrite through\fR policy.
.FE
Since the write caching lease has expired on the client, it will sync up with the
E 2
I 2
.(f
\** Gray and Cheriton avoid this problem by using a \fBwrite through\fR policy.
.)f
Since the write caching lease has expired on the client,
it will sync up with the
E 2
server as soon as the network connection has been re-established.
D 2
.PP
E 2
I 2
.pp
E 2
There is another failure condition that can occur when the server is congested.
The worst case scenario would have the client pushing dirty writes to the server
but a large request queue on the server delays these writes for more than
\fBwrite_slack\fR seconds. It is hoped that a congestion control scheme using
D 3
the \fBtry_again_later\fR RPC reply can minimize the risk of this occurrence.
E 3
I 3
the \fBtry_again_later\fR RPC reply after booting combined with
the following lease termination rule for write caching leases
can minimize the risk of this occurrence.
A write caching lease is only terminated on the server when there are have
been no writes to the file and the server has not been overloaded during
the previous write_slack seconds. The server has not been overloaded
is approximated by a test for sleeping nfsd(s) at the end of the write_slack
period.
E 3
D 2
.SH
3. Server Disk Full
.PP
E 2
I 2
.sh 2 "Server Disk Full"
.pp
E 2
There is a serious unresolved problem for delayed write caching with respect to
server disk space allocation.
When the disk on the file server is full, delayed write RPCs can fail
due to "out of space".
For NFS, this occurrence results in an error return from the close system
call on the file, since the dirty blocks are pushed on close.
Processes writing important files can check for this error return
to ensure that the file was written successfully.
For NQNFS, the dirty blocks are not pushed on close and as such the client
may not attempt the write RPC until after the process has done the close
which implies no error return from the close.
D 2
For the current prototype, the only solution is to modify programs writing important
E 2
I 2
For the current prototype,
the only solution is to modify programs writing important
E 2
file(s) to call fsync and check for an error return from it instead of close.
D 2
.SH
4. Protocol Details
.PP
The protocol specification is identical to that of NFS [RFC1094] except for
E 2
I 2
.sh 2 "Protocol Details"
.pp
The protocol specification is identical to that of NFS [Sun89] except for
E 2
the following changes.
D 2
.IP \(bu
E 2
I 2
.ip \(bu
I 3
RPC Information
.(l
        Program Number 300105
        Version Number 1
.)l
.ip \(bu
Readdir_and_Lookup RPC
.(l
        struct readdirlookargs {
                fhandle file;
                nfscookie cookie;
                unsigned count;
                unsigned duration;
        };

        struct entry {
                unsigned cachable;
                unsigned duration;
                modifyrev rev;
                fhandle entry_fh;
                nqnfs_fattr entry_attrib;
                unsigned fileid;
                filename name;
                nfscookie cookie;
                entry *nextentry;
        };

        union readdirlookres switch (stat status) {
        case NFS_OK:
                struct {
                        entry *entries;
                        bool eof;
                } readdirlookok;
        default:
                void;
        };

        readdirlookres
        NQNFSPROC_READDIRLOOK(readdirlookargs) = 18;
.)l
Reads entries in a directory in a manner analogous to the NFSPROC_READDIR RPC
in NFS, but returns the file handle and attributes of each entry as well.
This allows the attribute and lookup caches to be primed.
.ip \(bu
E 3
E 2
Get Lease RPC
D 2
.sp
.nf
E 2
I 2
.(l
E 2
        struct getleaseargs {
                fhandle file;
                cachetype readwrite;
                unsigned duration;
        };

        union getleaseres switch (stat status) {
        case NFS_OK:
D 3
                boolean cachable;
E 3
I 3
                bool cachable;
E 3
                unsigned duration;
                modifyrev rev;
D 3
                fattr attributes;
E 3
I 3
                nqnfs_fattr attributes;
E 3
        default:
                void;
        };

        getleaseres
D 3
        NQNFSPROC_GETLEASE(getleaseargs) = 18;
E 3
I 3
        NQNFSPROC_GETLEASE(getleaseargs) = 19;
E 3
D 2

.fi
E 2
I 2
.)l
E 2
Gets a lease for "file" valid for "duration" seconds from when the lease
D 2
was issued on the server\**. The lease permits client caching if "cachable"
.FS
To be safe, the client may only assume that the lease is valid for "duration"
seconds from when the RPC request was sent to the server.
.FE
is true. The modify revision level and attributes for the file are also
returned.
.IP \(bu
E 2
I 2
was issued on the server\**.
.(f
\** To be safe, the client may only assume that the lease is valid
for ``duration'' seconds from when the RPC request was sent to the server.
.)f
The lease permits client caching if "cachable" is true.
The modify revision level and attributes for the file are also returned.
.ip \(bu
E 2
Eviction Message
D 2
.sp
.nf
E 2
I 2
.(l
E 2
        void
D 3
        NQNFSPROC_EVICTION (fhandle) = 19;
E 3
I 3
        NQNFSPROC_EVICTED (fhandle) = 21;
E 3
D 2

.fi
E 2
I 2
.)l
E 2
This message is sent from the server to the client. When the client receives
the message, it should flush data associated with the file represented by
"fhandle" from its caches and then send the \fBVacated Message\fR back to
the server. Flushing includes pushing any dirty writes via. write RPCs.
D 2
.IP \(bu
E 2
I 2
.ip \(bu
E 2
Vacated Message
D 2
.sp
.nf
E 2
I 2
.(l
E 2
        void
        NQNFSPROC_VACATED (fhandle) = 20;
D 2

.fi
E 2
I 2
.)l
E 2
This message is sent from the client to the server in response to the
\fBEviction Message\fR. See above.
D 2
.IP \(bu
E 2
I 2
.ip \(bu
I 3
Access RPC
.(l
        struct accessargs {
                fhandle file;
                bool read_access;
                bool write_access;
                bool exec_access;
        };

        stat
        NQNFSPROC_ACCESS(accessargs) = 22;
.)l
The access RPC does permission checking on the server for the given type
of access required by the client for the file.
Use of this RPC avoids accessibility problems caused by client->server uid
mapping.
.ip \(bu
E 3
E 2
Piggybacked Get Lease Request
D 2
.sp
E 2
I 2
.pp
E 2
The piggybacked get lease request is functionally equivalent to the Get Lease
RPC except that is attached to one of the other NQNFS RPC requests as follows.
D 3
A getleaserequest is prepended to all of the NFS request arguments for NQNFS
E 3
I 3
A getleaserequest is prepended to all of the request arguments for NQNFS
E 3
and a getleaserequestres is inserted in all NFS result structures just after
the "stat" field only if "stat == NFS_OK".
D 2
.sp
.nf
E 2
I 2
.(l
E 2
        union getleaserequest switch (cachetype type) {
D 3
        case NQNFS_READCACHE:
        case NQNFS_WRITECACHE:
E 3
I 3
        case NQLREAD:
        case NQLWRITE:
E 3
                unsigned duration;
        default:
                void;
        };

        union getleaserequestres switch (cachetype type) {
D 3
        case NQNFS_READCACHE:
        case NQNFS_WRITECACHE:
                boolean cachable;
E 3
I 3
        case NQLREAD:
        case NQLWRITE:
                bool cachable;
E 3
                unsigned duration;
                modifyrev rev;
        default:
                void;
        };
D 2

.fi
E 2
I 2
.)l
E 2
The get lease request applies to the file that the attached RPC operates on
and the file attributes remain in the same location as for the NFS RPC reply
structure.
D 2
.IP \(bu
E 2
I 2
.ip \(bu
D 3
Write and Setattr RPCs
E 3
I 3
Three additional "stat" values
E 3
.pp
E 2
D 3
The Write and Setattr RPCs return a modified "attrstat" with a "modifyrev"
added
E 3
I 3
Three additional values have been added to the enumerated type "stat".
E 3
D 2
.sp
.nf
E 2
I 2
.(l
E 2
D 3
        union modattrstat switch (stat status) {
        case NFS_OK:
                union getleaserequestres piggy;
                fattr attributes;
                modifyrev rev;
        default:
                void;
        };
E 3
I 3
        NQNFS_EXPIRED=500
        NQNFS_TRYLATER=501
        NQNFS_AUTHERR=502
E 3
D 2

NB: Note that I have included the "getleaserequestres" union in the above
    as it is positioned in all NQNFS RPC replies.
    Also, the modifyrev in "piggy" will not be the same as "rev", since
    any piggybacked lease is acquired before the write operation.
.fi
.IP \(bu
E 2
I 2
.)l
D 3
.lp
Note that I have included the "getleaserequestres" union in the above
as it is positioned in all NQNFS RPC replies.
Also, the modifyrev in "piggy" will not be the same as "rev", since
any piggybacked lease is acquired before the write operation.
.ip \(bu
E 2
An additional "stat" value
D 2
.sp
E 2
I 2
.pp
E 2
An additional value has been added to the enumerated type "stat"
NQNFS_TRYAGAINLATER=501.
This value is returned by the server when it wishes the client to retry the
E 3
I 3
The "expired" value indicates that a lease has expired.
The "try later"
value is returned by the server when it wishes the client to retry the
E 3
RPC request after a short delay. It is used during crash recovery (Section 2)
and may also be useful for server congestion control.
I 3
The "authetication error" value is returned for kerberized mount points to
indicate that there is no cached authentication mapping and a Kerberos ticket
for the principal is required.
E 3
D 2
.SH
4. Data Types
.IP \(bu
E 2
I 2
.sh 2 "Data Types"
.ip \(bu
E 2
cachetype
D 2
.sp
.nf
E 2
I 2
.(l
E 2
        enum cachetype {
                NQLNONE = 0,
                NQLREAD = 1,
                NQLWRITE = 2
        };
D 2

.fi
E 2
I 2
.)l
E 2
Type of lease requested. NQLNONE is used to indicate no piggybacked lease
request.
D 2
.IP \(bu
E 2
I 2
.ip \(bu
E 2
modifyrev
D 2
.sp
.nf
E 2
I 2
.(l
E 2
        typedef unsigned hyper modifyrev;
D 2

.fi
E 2
I 2
.)l
E 2
The "modifyrev" is a unsigned quadword integer value that is never zero
and increases every time the corresponding file is modified on the server.
I 3
.ip \(bu
nqnfs_time
.(l
        struct nqnfs_time {
                unsigned seconds;
                unsigned nano_seconds;
        };
.)l
For NQNFS times are handled at nano second resolution instead of micro second
resolution for NFS.
.ip \(bu
nqnfs_fattr
.(l
        struct nqnfs_fattr {
                ftype type;
                unsigned mode;
                unsigned nlink;
                unsigned uid;
                unsigned gid;
                unsigned hyper size;
                unsigned blocksize;
                unsigned rdev;
                unsigned hyper bytes;
                unsigned fsid;
                unsigned fileid;
                nqnfs_time atime;
                nqnfs_time mtime;
                nqnfs_time ctime;
                unsigned flags;
                unsigned generation;
                modifyrev rev;
        };
.)l
The nqnfs_fattr structure is modified from the NFS fattr so that it stores
the file size as a 64bit quantity and the storage occupied as a 64bit number
of bytes. It also has fields added for the 4.4BSD va_flags and va_gen fields
as well as the file's modify rev level.
.ip \(bu
nqnfs_sattr
.(l
        struct nqnfs_sattr {
                unsigned mode;
                unsigned uid;
                unsigned gid;
                unsigned hyper size;
                nqnfs_time atime;
                nqnfs_time mtime;
                unsigned flags;
                unsigned rdev;
        };
.)l
The nqnfs_sattr structure is modified from the NFS sattr structure in the
same manner as fattr.
.lp
The arguments to several of the NFS RPCs have been modified as well. Mostly,
these are minor changes to use 64bit file offsets or similar. The modified
argument structures follow.
.ip \(bu
Lookup RPC
.(l
        struct lookup_diropargs {
                unsigned duration;
                fhandle dir;
                filename name;
        };

        union lookup_diropres switch (stat status) {
        case NFS_OK:
                struct {
                        union getleaserequestres lookup_lease;
                        fhandle file;
                        nqnfs_fattr attributes;
                } lookup_diropok;
        default:
                void;
        };

.)l
The additional "duration" argument tells the server to get a lease for the
name being looked up if it is non-zero and the lease is specified
in "lookup_lease".
.ip \(bu
Read RPC
.(l
        struct nqnfs_readargs {
                fhandle file;
                unsigned hyper offset;
                unsigned count;
        };
.)l
.ip \(bu
Write RPC
.(l
        struct nqnfs_writeargs {
                fhandle file;
                unsigned hyper offset;
                bool append;
                nfsdata data;
        };
.)l
The "append" argument is true for apeend only write operations.
.ip \(bu
Get Filesystem Attributes RPC
.(l
        union nqnfs_statfsres (stat status) {
        case NFS_OK:
                struct {
                        unsigned tsize;
                        unsigned bsize;
                        unsigned blocks;
                        unsigned bfree;
                        unsigned bavail;
                        unsigned files;
                        unsigned files_free;
                } info;
        default:
                void;
        };
.)l
The "files" field is the number of files in the file system and the "files_free"
is the number of additional files that can be created.
E 3
D 2
.SH
References
.IP [Baker91]
Mary Baker and John Ousterhout, Availability in the Sprite Distributed
File System, In \fIOperating System Review\fR, (25)2, pg. 95-98,
April 1991.
.IP [Baker91a]
Mary Baker, Private Email Communication, May 1991.
.IP [Burrows88]
Michael Burrows, Efficient Data Sharing, Technical Report #153,
Computer Laboratory, University of Cambridge, Dec. 1988.
.IP [Gray89]
Cary G. Gray and David R. Cheriton, Leases: An Efficient Fault-Tolerant
Mechanism for Distributed File Cache Consistency, In \fIProc. of the
Twelfth ACM Symposium on Operating Systems Principals\fR, Litchfield Park,
AZ, Dec. 1989.
.IP [Howard88]
John H. Howard, Michael L. Kazar, Sherri G. Menees, David A. Nichols,
M. Satyanarayanan, Robert N. Sidebotham and Michael J. West,
Scale and Performance in a Distributed File System, \fIACM Trans. on
Computer Systems\fR, (6)1, pg 51-81, Feb. 1988.
.IP [Juszczak89]
Chet Juszczak, Improving the Performance and Correctness of an NFS Server,
In \fIProc. Winter 1989 USENIX Conference,\fR pg. 53-63, San Diego, CA, January 1989.
.IP [Kent87]
Christopher. A. Kent, \fICache Coherence in Distributed Systems\fR, Research Report 87/4,
Digital Equipment Corporation Western Research Laboratory, April 1987.
.IP [Nelson88]
Michael N. Nelson, Brent B. Welch, and John K. Ousterhout, Caching in the
Sprite Network File System, \fIACM Transactions on Computer Systems\fR (6)1
pg. 134-154, February 1988.
.IP [Ousterhout90]
John K. Ousterhout, Why Aren't Operating Systems Getting Faster As Fast as
Hardware? In \fIProc. Summer 1990 USENIX Conference\fR, pg. 247-256, Anaheim,
CA, June 1990.
.IP [Sandberg85]
Russel Sandberg, David Goldberg, Steve Kleiman, Dan Walsh, and Bob Lyon,
Design and Implementation of the Sun Network filesystem, In \fIProc. Summer
1985 USENIX Conference\fR, pages 119-130, Portland, OR, June 1985.
.IP [Schroeder85]
Michael D. Schroeder, David K. Gifford and Roger M. Needham, A Caching
File System For A Programmer's Workstation, In \fIProc. of the Tenth
ACM Symposium on Operating Systems Principals\fR, pg. 25-34, Orcas Island,
WA, Dec. 1985.
.IP [Srinivasan89]
V. Srinivasan and Jeffrey. C. Mogul, \fISpritely NFS: Implementation and
Performance of Cache-Consistency Protocols\fR, Research Report 89/5,
Digital Equipment Corporation Western Research Laboratory, May 1989.
.IP [RFC1094]
Sun Microsystems Inc., \fINFS: Network File System Protocol Specification\fR,
ARPANET Working Group Requests for Comment, DDN Network Information Center,
SRI International, Menlo Park, CA, March 1989, RFC-1094.
E 2
I 2
.sh 1 "Summary"
.pp
The configuration and tuning of an NFS environment tends to be a bit of a
mystic art, but hopefully this paper along with the man pages and other
reading will be helpful. Good Luck.
E 2
E 1
