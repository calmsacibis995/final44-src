.ev 0
.nf
.LP
.nf
.ev 1
.ll +10
.ND
.ps 12
.ft B
UNIVERSITY OF CALIFORNIA, BERKELEY
.ft R 
.sp
.vs 7p
.ie \nv \s20\l'25_'\s6
.el \s20\l'22_'\s6
.br
.sp 3p
BERKELEY \  \(bu \  DAVIS \  \(bu \  IRVINE \  \(bu \ 
LOS ANGELES \  \(bu \  RIVERSIDE \  \(bu \  SAN DIEGO
\  \(bu \  SAN FRANCISCO \  \(bu \  SANTA BARBARA \  \(bu \  SANTA CRUZ
.br
.sp -3p
.ie \nv \s20\l'25_'\s7
.el \s20\l'22_'\s7
.nf
.vs 9p
.sp
COLLEGE OF ENGINEERING  \l'25 '        BERKELEY, CALIFORNIA 94720
DEPARTMENT OF ELECTRICAL ENGINEERING
  AND COMPUTER SCIENCES \l'30 ' \s10August 3, 1983\s0
COMPUTER SCIENCE DIVISION
.fi
.sp
.ev 0
.LP
.rs
.sp .75i
.tl '''August 3, 1983'
.LP
Dear Colleague:
.PP
We are happy to send you information about our August
1983 revision of the Fourth
Berkeley Software Distribution.  The Fourth Berkeley Software
Distribution is available to VAX\(dg users with UNIX/32V\(dd, System III, or
System V
.FS
\(dgVAX is a trademark of Digital Equipment Corporation
.FE
.FS
\(ddUNIX, UNIX/32V, UNIX System III, and UNIX System V
are trademarks of Western Electric.
.FE
source licenses with AT & T.
This distribution is called 4.2BSD and supersedes the
4.1BSD distribution made in June 1981, which will no longer be available.
.PP
The enclosed information is designed to serve two purposes.  The first
purpose is to acquaint you with the details of our distribution so you
can decide whether or not you would like to receive it.  The second
purpose is to tell you how to obtain our distribution.
.SH
What is 4.2BSD?
.PP
The distribution consists of two magnetic tapes, printed
documentation, and console media.
The magnetic tapes contain copies of all binaries,
source code, and documentation.  The console media, a TU58
cassette tape and RX01 floppy disk are used in installing
the system.  The printed documentation contains a
complete manual set including both the Berkeley documentation and
material which is unchanged from the original Western Electric
distribution.  In addition, a high-quality one-sided typeset
duplication master is provided for Volume One of the UNIX Programmer's
Manual and for the sections of Volume Two which were added at
Berkeley.
.PP
Because we have a very limited capability for providing individual
information to the many sites which wish to run 4.2BSD, we are including
several documents which answer in great detail many of the
questions which we have been asked.  Please do not contact us with
questions until you have satisfied yourself that the answer you need is
not in one of these enclosed documents:
.RS
.IP \(bu
.B
Berkeley Software for UNIX on the VAX
.R
describes the basic differences between Western Electric's UNIX/32V and
Berkeley's 4.2BSD.  This document will help you decide whether or not
to try 4.2BSD.
.IP \(bu
.B
Bug Fixes and Changes in 4.2BSD
.R
describes the external differences between 4.2BSD and 4.1BSD.  This
document will help you decide whether or not to upgrade from 4.1BSD.
.IP \(bu
.B
Changes to the Kernel in 4.2BSD
.R
describes the internal differences between 4.2BSD and 4.1BSD.  This
document will help you plan for carrying any local changes you may
have made from 4.1BSD to 4.2BSD.
.IP \(bu
.B
Hints on Configuring VAX Systems for UNIX
.R
provides some basic information about hardware known to work with
4.2BSD.  This document will help you plan further hardware
acquisition.
.IP \(bu
.B
Performance Effects of Disk Subsystem Choices for VAX
Systems Running 4.2BSD UNIX.
.R
describes the results of performance tests carried
out with the 4.2BSD file system and several disk
controllers and disk drives.  This document is a companion
paper to ``Hints on Configuring VAX Systems for UNIX''.
.IP \(bu
.B
4.2BSD System Manual
.R
provides a detailed description of the system facilities.
This document gives an extremely concise definition
of the 4.2BSD system interface.
.IP \(bu
.B
Installing and Operating 4.2BSD
.R
describes what is involved in running 4.2BSD.  This document will
help you plan your operations staffing.
.RE
.SH
Consideration for the Future
.PP
Future releases of the Fourth Berkeley Software Distribution may include material from
System V which will require all future licensees to have a System V license.
AT&T has provided an inexpensive way for each educational site to upgrade
all their CPU's to System V.  We recommend that you consider this generous
offer.
.SH
How to obtain 4.2 BSD?
.PP
This section should be read by existing licensees as well as new licensees.
All previous 4BSD licensees will be required to sign
the revised license agreement for 4.2BSD.
The new License Agreement will allow other research and development
organizations to convey interesting software to our licensees while
providing these contributors with protection under the Berkeley License Agreement.
Please note the changes in procedures for your future interactions with
our distribution group.
.PP
Because we are a research and development organization and not a commercial
organization, we make our research results available at the cost of 
distributing the system.  In this sense, the payment we ask for is
not a licensing fee but only a fee to cover our costs of distributing the system.
It is not in lieu of licensing fees due AT&T.
Also, we only distribute the whole system
and cannot send individual pieces of the system.
Because the software is distributed `as is' and is partially derived
from licensed material, we are required by the
University of California to have a formal license arrangement with each
organization to which we distribute. 
All material is considered licensed material regardless of its
availability from other sources which make such material publicly available.
In addition, we are required
to secure a copy of the AT&T Software Agreement with your organization 
and confirm it with AT&T before the software can be shipped.
Finally, we ask that you supply us with the configuration
of your system and identify the administrative and technical contacts.
.PP
Specifically, we must receive from your organization the
following material before the distribution can be sent:
.IP \(bu
An \fBentire\fR copy of the Software Agreement between your company or institution and
AT&T (Western Electric) which authorizes you as a source licensee for
UNIX/32V, System III, or System V.  Note that a complete copy of the
agreement is required, not just the cover and/or signature page.
Letters authorizing additional CPU's are not sufficient and not necessary
in this process; however, it is your legal responsibility to obtain
an additional CPU authorization from AT&T.
.IP \(bu
Two signed and executed copies of the Berkeley License Agreement between
your company or institution and the Regents of the University of California.
The name of the organization on the Berkeley License Agreement must be the same as
that which appears on the Software Agreement with AT&T (or Western Electric).
This agreement must be signed by the same individual (or his replacement)
who appears on the signed copy of your agreement with AT&T (or Western Electric).
Please have this person's name and title typed in the available
space next to ``Title''.
This license agreement applies to all the CPU's covered
by the Software Agreement with AT&T (or Western Electric)
that you have provided.  One of the signed copies of the Berkeley License
Agreement will be
returned to you after it has been executed on behalf of the Regents of the 
University of California along with Schedule A (a list of the material
being licensed).
.IP \(bu
A check from a U.S. bank for $750 U.S. payable to the
``Regents of the University of California''
must be received before the distribution can be sent.  The only
exception to payment in advance is in the case 
of an organization which is legally 
unable to do so; in such a case, a purchase order is required which
cites the State or Federal law which prohibits payment in advance.
.IP \(bu
The Site Information Form completely filled out and dated.
The signed Berkeley License Agreement will be sent to the person listed
as the administrative contact.  The distribution itself will be sent to
the technical contact.  The site information is kept confidential
and is for our use in identifying sites with specific configurations.
Please note that we cannot ship to post office boxes; 
therefore, please have the
technical contact's address supplied without use of a post office box.
.PP
A checklist is included to aid you in assembling this material.
All the above material must be sent to:
.DS
Pauline Schwartz, Distribution Coordinator
Computer Systems Research Group
Computer Science Division, EECS
University of California
Berkeley, California 94720
.DE
Once all these items have been received and are in proper order, the
distribution will be sent to the technical address indicated on the
Site Information Form.  We cannot provide delivery dates.  Once
the material is assembled and packaged, the distribution is shipped by
commercial carrier.  Order of shipment will be based on time
of arrival of the properly completed paperwork and
confirmation with AT&T.
Because of the differential in costs of shipping outside the United States,
we ask that organizations beyond the North American continent pay
the collect shipping charges.
.PP
The most expedient way to insure that your distribution is sent as quickly
as possible is to include in a single package the completed and properly
signed Berkeley License Agreement (\fBwithout modification\fR), a complete copy of
your AT&T Software Agreement, the check for $750 properly made out to the
``Regents of the University of California'', and a completely filled out
Site Information form and to send this single package to the proper address as stated above.
.PP
Please note that if you modify the Berkeley License Agreement, you may experience
a delay of three months or more before receiving an acceptance or denial of the changes.
.SH
Large Organizations
.PP
Many large organizations have multiple entities which act independently
from one another and wish to be licensed independently 
from AT&T.  Others may wish
to have the parent organization licensed 
by AT&T and copies of the software distribution sent
to each independent entity.  We recommend that you have the parent organization
licensed first for AT&T software and then for 4.2 BSD.
.PP
Once your organization has
an AT&T license, these rules apply:
.IP \(bu
If your AT&T Software Agreement is with the parent organization,
the initial Berkeley License Agreement must be with the parent organization.
.RS
.IP a)
Because the Berkeley License Agreement references your parent organization's
AT&T Software Agreement without specification of CPU, the parent organization
may distribute 4.2BSD to entities within its organizations, provided of course
that each CPU is properly licensed with AT&T.
.IP b)
If your parent organization 
chooses not to redistribute internally, each entity
may receive 4.2 BSD from the distribution group by forwarding a letter from
the parent organization to the Regents of the University of California
authorizing this entity to receive 4.2BSD.
The form of the authorization should be:
.DS
I authorize (entity's name) a (division, company) of (organization's name)
to receive a copy of 4.2BSD under the terms and condition of the Revised
Berkeley License Agreement for 4.2 held
between (organization's name) and the Regents of the University of California.
I warrant that (entity's name) will abide by the Berkeley License Agreement for 4.2BSD
and that I have the authority to make this authorization on behalf of
(organization's name).
.DE
This statement must be signed by the same individual (or his replacement)
who signed the Berkeley License Agreement for 4.2 BSD.
.RE
The cost of the distribution
is unchanged.
.IP \(bu
If your AT&T Software Agreement is with an individual entity within a large organization,
the Berkeley License Agreement must be signed by a representative of that individual entity.
Each such entity will have to pay the cost of the distribution.
.sp
.SH
Special Cases
.PP
\fBUniversity of California Sites\fR.
If you are a part of the University of California,
\fByou must use the following procedure:\fR
Ask Pam True (415) 642-6348 in Berkeley Campus Material Management
for an application for an additional CPU 
authorization under the Regents of University
of California's Software Agreement with AT&T.  You will need to send
a copy of this application to
the distribution group along with the following:
1) a letter requesting 4.2 BSD stating that you have read and understood the Berkeley
License Agreement and that your organization will abide by it, 2)
an IOC for $750, and 3) a Site information Form.
.PP
\fBDARPA Sites\fR.
This research is sponsored by DARPA (Defense Advanced Research Projects
Agency).  Provision has been made for prepayment of distribution
costs for a few designated DARPA sites.  In place of the check for $750,
you should include a letter
from your Program Manager stating that you are designated as such a site.
However, you \fBmust\fR comply with all
other requirements in applying for the distribution.
.PP
\fBGovernment Agencies and Government Subcontractors\fR.
.IP \(bu
The U.S. Government has a source Software Agreement with AT&T dated Sept. 1, 1975.
If you are operating under the 1975 Software Agreement,
you do not need a copy of the aforementioned Software Agreement;
rather you must send a copy of your additional CPU authorization from AT&T.
The Berkeley License Agreement for 4.2 BSD should be signed by the 
contracting officer who signed the request for an additional CPU
authorization from AT&T.
.IP \(bu
A number of government agencies have acquired their own AT&T Software
Agreement.  In this case, we must obtain, as stated, a copy of this
Software Agreement with AT&T.  The Berkeley License Agreement must
be signed by the same individual (or his replacement) whose
signature appears on the Software Agreement with AT&T.
.IP \(bu
If you are a subcontractor of the Government and have obtained an
additional CPU authorization from AT&T for your contract work,
the Berkeley License Agreement must be signed by the Administrative
Contracting Officer for the contract.
The contractor should address a letter
to the Administrative Contracting Officer stating that the contractor
agrees to abide by the terms and conditions of the Berkeley License Agreement
for 4.2 BSD and ask that
the Administrative Contracting Officer sign the Berkeley License
Agreements for 4.2 BSD. 
The Administrative Contracting Officer should then return the signed 
Berkeley License Agreements directly to the distribution group with a cover
letter stating that the contractor is hereby authorized to receive a copy
of 4.2 BSD.
.SH
If You Currently Have 4BSD
.PP
If your AT&T Software Agreement is on file at Berkeley
in proper form and is confirmed, you need not send a new copy of your
AT&T license with your request for 4.2BSD.
Instead, your letter should include
the full name which appears on the AT&T Software Agreement,
with a specific reference to the distribution
you currently have.
All other items, including the Berkeley license,
must be submitted as listed above.
.SH
A Special Note 
.PP
The procedures and rules set out in this document are University and AT&T constraints
which must be followed in order for the distribution of software
to be possible.
The distribution group has no control over these constraints and must reject
your application if material submitted is not in order.
.SH
If You Have Read Everything and Still Need Help
.PP
If you have questions about the licensing process after reading
this letter, you may call Pauline Schwartz at (415) 642-7780,
write to her, or contact her via electric mail at ucbvax!pauline or
pauline@berkeley.  She will not be able to answer technical questions.
.sp 2
.ti +2.5i
Sincerely yours,
.sp 3
.ti +2.5i
Professor Robert S. Fabry
.br
.ti +2.5i
Computer Systems Research Group
