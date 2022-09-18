.\" formatted output is in installation.doc
.TL
CAP installation procedures
.AB
This document gives a step by step approach to installation of the
Columbia AppleTalk Package for Unix.
.AE
.SH
PREREQUISTES
.LP
We assume the KIP code has been properly installed in your KFPS.
You must do this before you run any CAP programs.  You must also
follow the instructions given with KIP to create
/etc/atalk.local.

Before you start here, you should have read the "README" and "NOTES"
files.  The README file gives a very basic overview of CAP necessary
to understand the following.

The installation NOTES file tries to point out places where you might
want to redefine things a little, explains configurations, and points
out machine dependencies.
.SH
Review
.LP
or the the "before you do anything else" step.  If you had a previous
distribution of CAP (1.00, 2.00, 2.01 or 3.00), you should consider
whether it is important enough to dump it to tape and put it away for
safe keeping or not.  There are often considerable changes between
distributions.  You should make sure you keep around modifications,
patches, etc. even if you think they should be installed in the new
distribution just in case they are not.  You don't have to do this,
but if you are paranoid about problems occurring, you will (and
probably would without this prompting).
.PP
In terms of installing KIP, there are two items which are directly
relevant to unix machines.  First, you must follow the directions with
KIP to create atalk.local (please make sure you use the network
address of the ethernet (UDP) KIP interface and not the appletalk
one).

Second, versions of KIP and UDP gateway code prior to April, 1988 had
"well known" DDP sockets mapped to priviledged UDP ports starting at
768 (so NBP was 770, etc).  In April, 1988, the NIC assigned a range
of UDP ports starting at 200 for the defined DDP services and assigned
the names "at-nbp", "at-rtmp", "at-echo", "at-zis".  (In addition,
ports were allocated where there were holes or unused sockets between
at-rtmp and at-zis).  CAP Release 5 only allows the above named DDP
ports to be used (cf. abkip.c).  It dynamically decides which mappings
to use by doing "getservbyname" calls based upon those names and using
the UDP port number returned.  getservbyname normally searches
/etc/services.  If the service name does not exist, then the old
mappings (based on 768) are used.

It is clear from this discussion, however, that one must make sure
that any mappings defined in /etc/services do not conflict
with the mappings used by the version of KIP you are using.  In
particular, if you are using KIP 01/88 or earlier, you should either
remove any such mappings from /etc/services or modify them so that the
old port assignments are used.  
.SH
Preparation
.LP
or the "make sure
things are okay first" step.  You should set your umask so people can
read the files when you extract the files.  Some of the steps require
that you have access to directories that are often only accessible by
a systems person.  We'll try to identify them below.  In addition,
some of the servers can only be run from the "root" id.  We'll try to
identify these too.
.SH
[1] Get CAP Files.
.LP
Assuming you have
gotten them somehow, you should now extract the files into
some convient directory like "cap" or cap[releaseid].

In the following, it is assume you are connected to the top level
directory (e.g. so an ls shows up samples, contrib, etc, lib,
applications, etc.)
.SH
[1.1] Generate system makefiles
.LP
You should run Configure to establish the baseline setup for your
system and then run gen.makes to generate your baseline makefiles.
There are "Makefile" included, but for the most part they are included
for systems without m4 and shouldn't be used unless absolutely
necessary.
.SH
[2] Install header files.
.LP
The simplest method is to connect to cap and type "make include".
This will create /usr/include/netat and copy the contents of cap/netat
to /usr/include/netat.  You can also symbolically link
/usr/include/netat to cap/netat.
.SH
[3] Make sure things will end up where you want them.
.LP
Figure out where you want everything.  The assumptions are: 
.nf
	cap libraries - /usr/local/lib - as a unix archive file
	cap programs - /usr/local/cap - as programs
	cap servers (Aufs) - /usr/local/lib/cap
	cap administrative program - /etc - as a program
.fi
If you want things elsewhere, edit m4.setup and regenerate the
makefiles.

By the way, /etc may be a bad place to put things.  At Columbia,
everything is generally put in /usr/local/lib/cap instead of /etc.
(Warning: if you want cap.printers in /etc, it is not enough to
redefine the "etcdir".  You must also uncomment the definition that
allows an alternate location for cap.printers).

This is also a good point to think about reconfiguring papif, lwsrv,
etc. to do what you want.  If you don't know yet, then don't worry,
you can recompile after you verify basic functionality.
.SH
[3.1] Testing
.LP
You can test things out without installing in system directories by
uncommenting the definition for "debug" in m4.setup and regenerating
the makefiles.  This will put:
.nf
	libraries - $cwd/cap/lib
	programs - $cwd/cap/bin (you must create this)
	etc stuff - $cwd/cap/etc
.fi
You need not install the header files if you run with debug.
.LP
.SH
[4] Build Libraries.
.LP
Make sure that you are still connected to "cap".  If not, the connect
to there.  Type: "make libsmade".  This should build the cap library.
If this
step doesn't work, then:
.nf
	(a) you didn't get the distribution correctly
	(b) you didn't install the header files correctly
	(c) you didn't Configure and gen the makefiles correctly
	(d) or worst of all the libraries don't work on your machine
.fi
If the problem is (d), you can refer to "PORTING" for some help.
.SH
[5] Installing libraries and building sample programs.
.LP
After building the libraries, you use "make programs" to install the
libraries into a readily accessible place (usually /usr/local/lib) and
compile the samples, applications and contributed programs.

You can install the various program by typing "make install", but you
might want to test them first.
.SH
[6] Installing administrative programs
.LP
This step is optional and not recommended if you do not plan to run
any CAP servers.  This step installs "atis" (nbp name server, echo server).

Connect to cap/etc.  Look at start-cap-servers and figure out if this
is what you want - modify it to be what you want.  If you don't know
what you want it to be, don't worry - you can do it later, but make
sure you don't remove the line with atis in it.  

Type "make install".  This will compile and install atis into /etc
(you probably have to do this su'ed).  It will also copy
start-cap-servers to /etc.  (Note: make install and make realinstall
above do not compile atis or install atis).
.SH
[7] At this point, primary installation is done.
.LP
.SH
[8] Verification.
.LP
To actually do things, you must have the 10/86, 2/87, 1/88 or later
revision of
the (KIP) udp gateway software already running.  You should have
already tested the software first.
You must have /etc/atalk.local installed (cf. gw software
documentation).
.LP
A.  Connect to cap/samples and run 
.I atlook.
If everything is okay, you
should see some appletalk entities.  If you installed the KIP code
correctly before, then you should minimially see the IPGATEWAY entry.
[Should you not see the IPGATEWAY entry, then the assumption is that
the UDP code isn't functional].  For example:
.nf
	$ atlook
	abInit: [ddp:  55.32, 130] starting
	01 - 128.59.35.40:IPGATEWAY@* [Net: 58.01 Node:220 Skt: 72]
	...
	$ 
.fi
Another really simple program to try is
.I "atlooklws"
which will look for
and query LaserWriters.
.LP
If 
.I atlook
doesn't work, then:
.IP
(a) you may not have installed the KIP code correctly

(b) you may not have installed atalk.local in the place
.I atlook
expects it.  It will complain if the /etc/atalk.local file is not
there or
is incorrectly formatted

(c) if
.I atlook
coredumps, then something is really wrong.  you are
probably on a machine that CAP doesn't work on.
.LP
B.  If you have a LaserWriter and you see it in 
.I atlook,
then another
level of testing is to run the sample program 
.I tlw
(just type "tlw <laserwriter name>"). 
.LP
C.  To test the server functionality, as "root" run 
.I "atis".
To see if
atis is running properly, run "atistest" from the samples directory.
If it signals proper operation with an "okay" message, then you can
confirm things again (odds are everything is okay) by:
.IP
(a) running 
.I atlook

(b) typing "atis dump" (as root) and looking at /usr/tmp/nis.db
.LP
To get rid of the extraneous entry, simply edit /usr/tmp/nis.db and
remove it and then type "atis reload" (as root).  (Alternatively,
simply kill the running atis process).

The most common problem in getting atis to run is failing to setup KIP
atalkatab properly.  Usually, the problem an incorrect broadcast
address, though others are possible too.

D.  After verification, you will want things to start up
automatically, either get someone to or edit /etc/rc.local to run the
following lines (or an equivalent):
.nf
	if [ -f /etc/start-cap-servers ]; then
		/etc/start-cap-servers & echo -n "cap " > /dev/console
	fi
.fi

