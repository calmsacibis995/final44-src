h44861
s 00002/00002/00059
d D 8.1 93/06/06 12:09:44 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00060
d D 5.4 92/02/09 08:46:16 pendry 4 3
c merge in new release
e
s 00011/00011/00050
d D 5.3 91/05/12 16:00:22 pendry 3 2
c checkpoint for network tape
e
s 00001/00001/00060
d D 5.2 91/03/17 13:55:24 pendry 2 1
c from amd5.3 alpha11
e
s 00061/00000/00000
d D 5.1 90/06/29 12:44:21 mckusick 1 0
c from Jan Pendry
e
u
U
t
T
I 1
#!/bin/sh -
#
D 3
# Start amd
#
D 2
# $Id: amd.start.ex,v 5.2 90/06/23 22:21:29 jsp Rel $
E 2
I 2
# $Id: amd.start.ex,v 5.2.1.1 90/10/21 22:31:39 jsp Exp $
E 2
#
E 3
# Copyright (c) 1989 Jan-Simon Pendry
# Copyright (c) 1989 Imperial College of Science, Technology & Medicine
D 5
# Copyright (c) 1989 The Regents of the University of California.
# All rights reserved.
E 5
I 5
# Copyright (c) 1989, 1993
#	The Regents of the University of California.  All rights reserved.
E 5
#
# This code is derived from software contributed to Berkeley by
# Jan-Simon Pendry at Imperial College, London.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#
D 3
PATH=/usr/local/etc:/bin:/usr/bin:/usr/ucb:$PATH export PATH
E 3
I 3
# Start amd
#
D 4
# $Id: amd.start.ex,v 5.2.1.3 91/05/07 22:20:41 jsp Alpha $
E 4
I 4
# $Id: amd.start.ex,v 5.2.2.1 1992/02/09 15:11:32 jsp beta $
E 4
#
PATH=/usr/sbin:/bin:/usr/bin:$PATH export PATH
E 3

#
# Either name of logfile or "syslog"
#
#LOGFILE=syslog
D 3
LOGFILE=/var/adm/am.log
E 3
I 3
LOGFILE=/var/run/amd.log
E 3

#
# Figure out whether domain name is in host name
# If the hostname is just the machine name then
# pass in the name of the local domain so that the
# hostnames in the map are domain stripped correctly.
#
case `hostname` in
*.*) dmn= ;;
*) dmn='-d doc.ic.ac.uk'
esac

#
# Zap earlier log file
#
case "$LOGFILE" in
*/*)
	mv "$LOGFILE" "$LOGFILE"-
	> "$LOGFILE"
	;;
syslog)
	: nothing
	;;
esac

D 3
cd /usr/local/etc
E 3
I 3
cd /usr/sbin
E 3
#
# -r 		restart
# -d dmn	local domain
# -w wait	wait between unmount attempts
# -l log	logfile or "syslog"
#
D 3
eval nice --4 ./amd -p > /etc/amd.pid -r $dmn -w 240 -l "$LOGFILE" \
	/homes amd.homes -cache=inc \
	/home amd.home -cache=inc \
	/vol amd.vol -cache=inc
E 3
I 3
eval nice --4 ./amd -p > /var/run/amd.pid -r $dmn -w 240 -l "$LOGFILE" \
	/homes amd.homes -cache:=inc \
	/home amd.home -cache:=inc \
	/vol amd.vol -cache:=inc
E 3
E 1
