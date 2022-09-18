





           Berkeley UNIX Project Funding Proposal
                  DRAFT of January 6, 1989


                   Marshall Kirk McKusick
                      Michael J Karels
                       Keith Sklower
                      Susan L. Graham
                      Domenico Ferrari



1.  Introduction

     This is a proposal for DARPA support of operating  sys-
tem and networking research in the UNIX project at UC Berke-
ley.  The goal  of  the  project  is  to  use  leading  edge
research  ideas in a stable and reliable implementation that
solves current problems in operating systems research.   The
project also includes incorporation of network protocols and
other subsystems into the operating system while maintaining
consistency  with  the  existing system call interface.  The
resulting system is widely  used  by  other  researchers  in
operating systems and network protocols and implementations.

     The last major release of Berkeley UNIX, in June, 1986,
was  4.3BSD  [CSRG86].   Projects  completed since that time
have been made available in a July, 1988 test release  known
as  the  4.3BSD  Tahoe release, named for the CCI Power 6/32
processor for which support was added.

2.  Proposed Research

     Since the 4.3BSD release, we have been working on  four
major new areas of research, which we propose to continue:

1)   Integration of an OSI network protocol suite and exist-
     ing  ISO applications into Berkeley UNIX.  Several pro-
     tocol layers were originally implemented at the Univer-
     sity of Wisconsin.  The network architecture and system
     interface of 4.2BSD accommodates multiple network  pro-
     tocol  families  and  address  formats,  although  some
     extensions have been required  to  accommodate  certain
     protocol  features.   Ongoing work includes development
     of those interfaces and a more flexible kernel  routing
     interface.

2)   Support for an interface  compliant  with  the  P1003.1
     POSIX standard recently approved by the IEEE.  Convert-
     ing the kernel to be POSIX compliant requires the  com-
     pletion  of  several  new kernel facilities including a
     new terminal driver and job control facilities.

3)   Refinement   of   the    network    architecture    and



                      January 6, 1989





                           - 2 -


     implementation  to  improve  its  performance and func-
     tionality.  Since the most recent  networking  release,
     additional  performance  experiments  have been done by
     Van Jacobson of the Lawrence Berkeley  Laboratory;  the
     resulting  performance  improvements  are  ready  to be
     merged into the Berkeley TCP.

4)   Provision of a standard interface to  file  systems  so
     that multiple local and remote file systems can be sup-
     ported, much as multiple networking protocols are  sup-
     ported   by   4.3BSD.   The  proposal  currently  under
     development adopts the 4.3BSD  calling  convention  for
     file  name  lookup  but otherwise is closely related to
     Sun's VFS.  We ultimately  hope  to  support  a  public
     domain implementation of Sun's NFS.

In addition to the four projects already underway,  we  will
add a fifth project, expanding on work already done:

5)   The recent invasion of the DARPA Internet by a  quickly
     reproducing  worm  highlighted  the need for a thorough
     review of the access safeguards built into the  system.
     We  will  conduct a complete audit of the system utili-
     ties, especially network  servers,  to  check  for  and
     eliminate unintended system access mechanisms.  Part of
     this proposal includes the addition and integration  of
     a  real  authentication mechanism for utilities such as
     telnet, login, remote shell, etc.

An expanded description of each of these  projects  is  pro-
vided in the following five subsections.

2.1.  OSI Network Protocol Development

     The network architecture  of  4.2BSD  was  designed  to
accommodate  multiple  network protocol families and address
formats.  The current prototype implementation  of  the  ISO
OSI  network protocols makes use of all the existing facili-
ties, but will be aided by some architectural changes.

     The architectural changes that have already  been  com-
pleted  include  improved network buffer layouts, changes to
allow variable length network addresses, and  the  construc-
tion of a uniform hierarchical routing lookup algorithm.  We
have made alterations  to  the  socket  interface  to  allow
transmission   of  record  boundaries,  distinction  between
dequeuing connection requests and explicit confirmation, and
passage  of  ancillary  data  such  as  user  connection- or
disconnection-request data.

     At the beginning of the period covered by  this  propo-
sal,  we  expect to have initial versions of the OSI connec-
tionless internet protocol (CLNP), an OSI transport class  4
(TP-4)  implementation,  device drivers for 802.2/802.3, and



                      January 6, 1989





                           - 3 -


the End System to Intermediate System (ES-IS) protocol.   We
will  add  support  for  X.25 interfaces using CLNP and will
then develop a software layer  allowing  connection-oriented
access to X.25 as well as packet-switching service.  We will
investigate a more general framework for  802.2-based  link-
level  interfaces  with  more  graceful support of ES-IS and
related protocols.  If hardware is available, we will incor-
porate  support  for 802.5 and/or ProNET-80 token rings.  We
will receive an updated ISO Development Environment  (ISODE)
and  incorporate  this  into the Berkeley Software Distribu-
tion.  ISODE implements the session and presentation  layers
of  the  OSI protocol suite, and will include an implementa-
tion of the file transfer protocol FTAM.   If  possible,  an
X.400  implementation  now being done at University College,
London and the University of Nottingham will also be  avail-
able  for  testing and distribution.  This work will include
participation in interoperability  tests  with  vendors  and
users on OSINET.

     We are designing modifications to the  current  network
architecture  (analogous  to the ``Streams'' concept of Bell
Laboratories 9th Edition UNIX or System V.3) to improve com-
munication  between  protocol layers, to allow more flexible
layering, to incorporate terminal  and  asynchronous  serial
I/O  modules into the same processing framework, and to pro-
vide a more natural framework for devices already  providing
virtual  circuit  services  (such  as  X.25  devices).  Such
layering will provide a natural setting for  kernel-resident
virtual  terminal  services, and will allow direct access to
communications-layer devices for network monitoring or  pro-
totyping of new protocols.  This structure will also make it
easier to tunnel one protocol through  another.   Additional
work  may be necessary for IP (in particular for the address
resolution protocol, ARP) to allow such revisions.

     We have become members of the IEEE 1003.8 group working
on  a  POSIX networking interface.  We intend to introduce a
proposal for a high-level protocol-independent interface for
network  services  suitable  for  distributed  applications.
This interface will be based on the UNI  interface  proposed
by Marshall Rose [Rose88].

2.2.  Compliance with POSIX 1003

     Bringing the Berkeley UNIX kernel into compliance  with
the  P1003.1  POSIX  interface recently approved by the IEEE
requires two major projects  and  many  smaller  ones.   The
first  major  project is the development of a completely new
terminal driver.   The  new  terminal  driver  must  have  a
binary-compatibility  interface  to  allow a transition path
for programs using the old Berkeley  terminal  driver.   The
other  major  project  is the development of a POSIX session
and job control implementation.  Those system utilities that
create sessions and manipulate jobs must be converted to use



                      January 6, 1989





                           - 4 -


the new facilities.  These two projects are nearly finished,
and we are completing the conversion of the standard utility
programs that are affected by this change.  These facilities
will be tested and made available to other groups during the
period covered by this proposal.

     The smaller POSIX related changes  that  must  be  made
include  expanded  signal functionality, restructured direc-
tory access  routines,  and  new  set-user-identifier  func-
tionality.   Many of these interfaces will be developed as a
superset of both the  POSIX  and  existing  BSD  facilities.
This  work  will  involve  coordination  with  other  groups
intending to support both POSIX and BSD interfaces.

     We intend to remain involved with the IEEE P1003.1 com-
mittee  that  will work on corrections and extensions to the
existing standard.  We will also continue to  work  actively
with  the  1003.2 committee developing a shell and utilities
POSIX standard.

2.3.  Improvements to the Networking Architecture and Proto-
cols

     The networking architecture introduced in  4.2BSD  pro-
vided  a framework for multiple networking protocols using a
single consistent user interface.  This  framework  includes
three  distinct layers: socket, transport and network proto-
cols, and network link layer.  This framework has been  used
for  implementations of TCP/IP, Xerox NS, the OSI protocols,
and local interprocess communication.  Our  experience  with
this  framework  and in performance analysis of the existing
implementations suggest some refinements  to  the  framework
and its implementation.  One refinement is the use of struc-
turing techniques similar to those of the Stream I/O system,
described  in section 2.1, unifying two existing interfaces.
In addition to  providing  additional  flexibility,  careful
structuring  will  allow  improved pipelining of the network
protocols using upcalls [Clark85].  Such pipelining has been
prototyped  by Van Jacobson of the Lawrence Berkeley Labora-
tory, along with several caching strategies that  will  also
be  incorporated.   With  this work, it will be necessary to
improve communication among the  levels  of  the  system  to
improve performance.  In particular, the transport protocols
must influence the way in which data are buffered by  higher
layers  for optimal performance.  We will investigate layer-
ing techniques that are both modular and efficient, two con-
flicting  goals.   At  the  same  time,  we  will modify the
current buffer management to be more portable and  to  allow
efficient use on machines with different I/O architectures.

     The communication mechanisms between  the  layers  must
also  be  extended  for robustness of the network: the tran-
sport level must be able to notify the network and link lev-
els of failures detected by timeouts; the link level must be



                      January 6, 1989





                           - 5 -


able to  inform  the  network  level  of  failures  that  it
detects,  and the routing layer needs to use all this infor-
mation.

     The Internet and the Berkeley collection of  local-area
networks  have  both  grown  at high rates in the last year.
The Bay Area Regional Research  Network  (BARRNet)  connects
several  UC  campuses,  Stanford  and NASA-Ames with the NSF
network, increasing the complexity of  the  network  connec-
tivity.   Both  Internet  and  local  routing algorithms are
showing the  strain  of  continued  growth.   We  have  made
several  changes  in  the local routing algorithm to keep up
with the current topology,  and  are  participating  in  the
development of new routing algorithms and protocols.  In the
period covered by this proposal,  we  expect  to  merge  the
current  version  of the Berkeley routing daemon routed with
the multi-protocol daemon gated  (which  currently  supports
the  RIP and EGP protocols), and to update the RIP implemen-
tation for full conformance with  the  recent  specification
[Hedrick88].   We also expect to collaborate on an implemen-
tation of a new EGP protocol, version 3 [Lepp88] in a  gated
framework,  and  may  also  incorporate or collaborate on an
implementation of the SPF-based IGP protocol being developed
within the Internet Engineering Task Force.  We are continu-
ing our involvement with that  group  in  the  evolution  of
standards for the DARPA Internet.

     We will review the VMTP and IP multicast  support  done
by  David  Cheriton  and Steve Deering at Stanford, evaluate
the necessary changes  to  the  system  layering,  and  then
incorporate  these  modifications  into  the  system  if the
changes are found to be compatible with our goals.

2.4.  Toward a Compatible File System Interface

     The most critical shortcoming of our current UNIX  sys-
tem  is in the area of remote file access.  As with network-
ing protocols, there is no single remote  file  system  that
provides  enough  speed  and functionality for all problems.
It is frequently  necessary  to  support  several  different
remote file system protocols, just as it is necessary to run
several different network protocols.  The proposal currently
under  development  adopts the 4.3BSD calling convention for
file name lookup and allows stateful file systems, but  oth-
erwise  is  closely  related  to  Sun's  virtual file system
interface.  This interface has been advanced (to  Sun,  DEC,
AT&T and others) as a potential standard; when the implemen-
tation is complete, we intend to explore consensus  in  this
area,  so that file system implementations could be as port-
able as device drivers.  We do not intend to develop our own
remote  file  system  protocol;  instead we will support the
full semantics of existing file systems, including the local
UNIX  file  system  and Sun's network file system (NFS).  We
are currently negotiating  with  several  groups  that  have



                      January 6, 1989





                           - 6 -


developed  their own implementations of NFS to convince them
to contribute their code to Berkeley; we  will  not  include
NFS support unless it may be distributed with no new licens-
ing requirement.  We currently  expect  receipt  of  an  NFS
implementation  from  Apollo  that  uses  a different system
interface; if feasible, we will adapt it to our file  system
interface.

2.5.  System Security

     The recent invasion of the ARPANET by a quickly  repro-
ducing  worm  highlighted  the need for a thorough review of
the access safeguards built into the system.  Until  now  we
have  taken a passive approach to dealing with weaknesses in
the system access mechanisms, rather than actively searching
for  possible weaknesses.  When we are notified of a problem
or loophole in a system utility by one of our users, we have
a  well defined procedure for fixing the problem and expedi-
tiously disseminating the fix to the BSD mailing list.  This
procedure has proven itself to be effective in solving known
problems as they arise (witness its success in handling  the
recent  worm).   However, we feel that it would be useful to
take a more active role in identifying problems before  they
are  reported (or exploited).  We will make a complete audit
of the system utilities and network servers  to  find  unin-
tended system access mechanisms.  Once identified, we expect
that they can be corrected through the existing mechanism.

     As a part of the work to make the system more resistant
to  attack  from  local users or via the network, it will be
necessary to produce additional documentation on the  confi-
guration  and  operation  of the system.  This documentation
will cover such topics as file and directory  ownership  and
access,  network  and  server  configuration, and control of
privileged operations such as file system backups.

     In addition, we have been discussing with DARPA  possi-
ble  plans  for  response  to emergencies such as the recent
worm attack.  We believe that a plan such  as  the  proposed
Computer  Emergency Response Team (CERT) can respond to such
attacks effectively, and intend to  cooperate  with  such  a
plan.   We  can  provide at least two members for a response
team and can serve as the primary coordinators for  problems
involving BSD UNIX and networking software.

     A group within the Internet Engineering Task Force  has
been  drafting  a  Host  Requirements  standard for Internet
hosts.  We reviewed this draft recently and joined the work-
ing  group.  For the most part, the existing Berkeley TCP/IP
and networking application software conforms with the draft.
We  will review conformance with the Host Requirements stan-
dard at the same time that we review the robustness  of  the
network  software.   We expect that some additions will have
to be made to the kernel  network  protocols  to  make  them



                      January 6, 1989





                           - 7 -


compliant.   In  particular,  support for IP type-of-service
options and routing needs to be added, and recent  proposals
for gateway monitoring should be implemented and tested.

     A major shortcoming  of  the  present  system  is  that
authentication  over  the  network  is  based  solely on the
privileged port mechanism between trusting hosts and  users.
Although  privileged  ports can only be created by processes
running as root, such processes are easy for  a  workstation
user to obtain; they simply reboot their workstation in sin-
gle user mode.  Thus, a  real  authentication  mechanism  is
needed.   At  present,  we  believe  that  the  MIT Kerberos
authentication server provides the  best  solution  to  this
problem.  We propose to investigate Kerberos further as well
as other authentication mechanisms and then to integrate the
best one into Berkeley UNIX.  Part of this integration would
be the addition of the authentication mechanism into  utili-
ties   such  as  telnet,  login,  remote  shell,  etc.   MIT
currently supports the use of Kerberos for authentication of
rlogin,  rsh, certain other servers used at MIT, and the NFS
mount protocol.  If we choose Kerberos, we will add  support
for  telnet (eventually replacing rlogin), the X window sys-
tem, and the mail system within an authentication domain  (a
Kerberos  realm).   We  would  also  need to add support for
transparent third-party operations.  (The existing  Kerberos
software  allows  a  user  to connect to a server on another
system without supplying a  password,  but  does  not  allow
processes  started  on  the  server  to  access  the network
without sending another password over the network.) We  hope
to replace the existing password authentication on each host
with the network authentication system.

     Another subject of active work, at MIT  and  elsewhere,
is the interaction between servers for different authentica-
tion realms.  Currently, the servers for two Kerberos realms
may  be  mutually authenticated only by realm administrators
with a manual exchange of keys.  We  would  like  to  add  a
mechanism  for  a  user  in  two  realms  to  request that a
equivalence be established between his identities in the two
realms.   Such  a  facility could greatly reduce the need to
transmit passwords in the clear over wide-area networks.



3.  Milestones

     The first  four  efforts  outlined  above  are  already
underway.   We  expect  that we will have working prototypes
early in 1989.  When the prototypes  are  moderately  stable
and  functional, we will produce a test release that we will
distribute to our alpha sites for testing and feedback.   If
major design flaws turn up during the alpha testing, we will
reenter  the  development  phase  to  resolve  the  problems
resulting  in  another  test  release.   Otherwise,  we will



                      January 6, 1989





                           - 8 -


incorporate feedback from the testing and produce a  revised
distribution by the end of the period covered by this propo-
sal.

     The security work  described  above  has  already  been
started informally, and will be conducted more thoroughly at
the start of the period covered by this proposal.   We  will
distribute  the  changes  to  the  servers electronically as
groups of servers are completed, with immediate distribution
of fixes for serious problems.  We will also incorporate all
such changes into following releases.

4.  Statement of Work

     The University of California at  Berkeley,  during  the
proposed  one-year  period,  shall do work involving several
parallel but related threads:

+    Integration of an OSI network protocol suite and exist-
     ing ISO applications into Berkeley UNIX.

+    Support for an interface  compliant  with  the  P1003.1
     POSIX standard recently approved by the IEEE.

+    Refinement of the network architecture and  implementa-
     tion to improve its performance and functionality.

+    Implementation of a standard interface to file  systems
     so  that  multiple local and remote file systems can be
     supported.  We will pursue the acquisition and integra-
     tion of a public domain implementation of Sun's NFS.

+    Audit of the system utilities to check  for  and  elim-
     inate  unintended system access mechanisms, and to com-
     plete conformance with the Internet  Host  Requirements
     when that standard is released.

+    Identification, evaluation,  and  incorporation  of  an
     authentication mechanism into the system.

5.  Deliverables

     We are planning to implement  prototypes  for  each  of
these  outlined areas of work over the period of this propo-
sal.  We will do an informal release to interested  develop-
ers during the proposal period.  In particular, the informal
release will be made available to the group at Mt Xinu  that
is  producing  a commercially supported MACH release.  After
incorporating feedback and  refinements  from  the  testers,
another  release  will  be made to interested parties at the
end of the proposal period.






                      January 6, 1989





                           - 9 -


6.  References

Clark85
     D. Clark, ``The Structuring of Systems Using Upcalls,''
     Proceedings  of  the  Tenth  ACM Symposium on Operating
     Systems   Principles,   Association    for    Computing
     Machinery, Baltimore, MD, 1985.

CSRG86CSRG, UNIX Programmer's Manual, 4.3 Berkeley  Software
     Distribution,  Virtual  VAX-11  Version,  University of
     California Computer Systems Research  Group,  Berkeley,
     CA, 1986.

Hedrick88
     C. Hedrick, ``Routing Information Protocol,'' RFC-1058,
     SRI Network Information Center, Menlo Park, CA, 1988.

Lepp88M. Lepp and M. Karels,  ``Exterior  Gateway  Protocol,
     Version  3, Revisions and Extensions to EGP,'' IDEA009,
     Internet Engineering Task Force working document, 1988.

Rose88
     Marshall T. Rose, UNI network interface,  IEEE  P1003.8
     subcommittee working document.

































                      January 6, 1989





                           - 10 -


                           UNIX BUDGET
                 April 1, 1989 - March 31, 1990



A. SALARIES AND WAGES

     1. Academic (Assistant Research Engineer @ 100%)                 $ 54,389
     2. Technical (Programmer V @ 100%)                               $ 59,392
     3. Clerical Assistance (Assistant III @ 10%, Assistant II @ 50%) $ 14,769
     4. Administrative Services                                       $ 12,286

     TOTAL SALARIES AND WAGES                                        $ 140,836

B. EMPLOYEE BENEFITS                                                  $ 39,339

     TOTAL SALARIES AND EMPLOYEE BENEFITS                            $ 180,175

C. EQUIPMENT

     1. 3 ea. DEC/Sun 8MB Workstations                                $ 29,085
     2. 4 ea. SMD Disk Drives                                         $ 44,000
     3. 3 Ethernet Interfaces                                          $ 9,000
     4. 1 ea. Sun Fileserver upgrade                                   $ 9,030
     5. 3 ea. 4 Mb Upgrades for Sun Workstations                       $ 9,000
     6. 2 ea. 16 Mb Upgrades for VAX                                  $ 20,000
     7. 1 ea. Gateway, MicroVAX                                       $ 15,000

     TOTAL EQUIPMENT                                                 $ 135,115

D. TRAVEL

     1. 9 R/Ts to the East Coast @ $700/trip
     2. 2 R/Ts to Europe (IEEE 1003, IETF) @ $1,760/trip

     TOTAL TRAVEL                                                      $ 9,820

E. SUPPLIES AND EXPENSES

     1. Computer Maintenance                                          $ 43,908
     2. Network Access                                                 $ 1,440
     3. Mailing, Telephone, Manuals & Expendable Supplies              $ 9,270

     TOTAL SUPPLIES AND EXPENSES                                      $ 54,618

F. TOTAL DIRECT COSTS                                                $ 379,728

G. INDIRECT COSTS (47% of $244,613 Modified Total Direct Costs)      $ 114,968

H.  TOTAL COST OF PROJECT                                            $ 494,696







                      January 6, 1989





                           - 11 -


                         SECURITY BUDGET
                 April 1, 1989 - March 31, 1990



A. SALARIES AND WAGES

     1. Technical (Programmer II @ 100% & Programmer III @ 100%)      $ 85,361
     2. Clerical Assistance (Assistant III @ 10%, Assistant II @ 50%) $ 14,769
     3. Administrative Services                                       $ 10,227

     TOTAL SALARIES AND WAGES                                        $ 110,357

B. EMPLOYEE BENEFITS                                                  $ 33,383

     TOTAL SALARIES AND EMPLOYEE BENEFITS                            $ 143,740

C. EQUIPMENT

     1. 2 ea. DEC/Sun 8MB Workstations                                $ 19,390
     2. 3 ea. SMD Disk Drives                                         $ 33,000
     3. 3 Ethernet Interfaces                                          $ 9,000
     4. 4 ea. 9600 Baud Telebit Modems                                 $ 6,400
     5. 3 ea. 4 Mb Upgrades for Sun Workstations                       $ 9,000
     6. 2 ea. 16 Mb Upgrades for Micro VAX                            $ 16,000
     7. 3 ea. SCSI Disks                                                $9,600
     8. 4 ea. Interphase 4400 Disk Controllers                        $ 20,000
     9. 4 ea. High-speed Network Interfaces                           $ 30,000
    10. 2 ea. X.25 Network Interfaces                                 $ 10,000
    11. 2 Exabyte 8mm Tape Backup Systems                             $ 15,000

     TOTAL EQUIPMENT                                                 $ 177,390

D. TRAVEL

     1. 10 R/Ts to the East Coast @ $700/trip
     2. 2 R/Ts to Europe (IEEE 1003) @ $1,760/trip

     TOTAL TRAVEL                                                     $ 10,520

E. SUPPLIES AND EXPENSES

     1. Computer Maintenance                                          $ 42,908
     2. Network Access                                                 $ 1,080
     3. Mailing, Telephone, Xeroxing & Expendable Supplies             $ 5,370

     TOTAL SUPPLIES AND EXPENSES                                      $ 49,358

F. TOTAL DIRECT COSTS                                                $ 381,008

G. INDIRECT COSTS (47% of $203,618 Modified Total Direct Costs)       $ 95,700

H.  TOTAL COST OF PROJECT                                            $ 476,708




                      January 6, 1989





                           - 12 -


                           OSI BUDGET
                 April 1, 1989 - March 31, 1990



A. SALARIES AND WAGES

     1. Technical (Programmer IV @ 80%)                        $ 43,350

     2. Administrative Services                                   3,417

     TOTAL SALARIES AND WAGES                                  $ 46,767

B. EMPLOYEE BENEFITS                                             14,147

     TOTAL SALARIES AND EMPLOYEE BENEFITS                      $ 60,914

C. SUPPLIES AND EXPENSES (Network connection & manuals)         $ 7,113

D. TOTAL DIRECT COSTS                                          $ 68,027

E. INDIRECT COSTS (47% of $68,027 Modified Total Direct Costs) $ 31,973

F. TOTAL COST OF PROJECT                                      $ 100,000

































                      January 6, 1989


