h27845
s 00045/00045/00120
d D 6.2 93/02/12 12:09:58 eric 13 12
c make everything configurable on M4 macros
e
s 00000/00000/00165
d D 6.1 92/12/21 16:08:11 eric 12 11
c Release 6
e
s 00004/00004/00161
d D 2.11 92/12/20 13:21:53 eric 11 10
c cleanup for new features and release engineering
e
s 00001/00001/00164
d D 2.10 92/11/13 23:00:37 eric 10 9
c quote versionid to avoid # problems
e
s 00011/00001/00154
d D 2.9 92/07/20 08:00:23 eric 9 8
c readability changes
e
s 00001/00002/00154
d D 2.8 92/05/15 06:44:01 eric 8 7
c put Received: on one line
e
s 00056/00015/00100
d D 2.7 92/01/05 09:23:38 eric 7 6
c spell out options to make local tuning easier
e
s 00002/00002/00113
d D 2.6 91/12/15 14:17:04 eric 6 5
c $<, if defined, is the return-path equivalent of $g
e
s 00003/00003/00112
d D 2.5 91/11/22 14:54:21 eric 5 4
c change pathname defaults to be more like modern systems
e
s 00001/00001/00114
d D 2.4 91/10/05 10:47:03 eric 4 3
c don't need | as operator any more
e
s 00001/00001/00114
d D 2.3 91/10/03 11:16:33 eric 3 2
c add vertical bar to list of operators
e
s 00001/00001/00114
d D 2.2 91/10/02 18:38:50 eric 2 1
c make it work on 4.4bsd m4
e
s 00115/00000/00000
d D 2.1 91/10/02 14:48:09 eric 1 0
c date and time created 91/10/02 14:48:09 by eric
e
u
U
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
#
# %sccs.include.redist.sh%
#
divert(0)
######################################################################
######################################################################
#####
#####			CONFIGURATION BOILERPLATE
#####
######################################################################
######################################################################

D 10
VERSIONID(%W% (Berkeley) %G%)
E 10
I 10
VERSIONID(`%W% (Berkeley) %G%')
E 10

######################
#   Special macros   #
######################

# my name
D 2
DnMAILER-DAEMON
E 2
I 2
D 13
Dn`MAILER'-DAEMON
E 13
I 13
CONCAT(Dn, confMAILERNAME)
E 13
I 9

E 9
E 2
# UNIX header format
D 6
DlFrom $g  $d
E 6
I 6
D 13
DlFrom $?<$<$|$g$.  $d
E 13
I 13
CONCAT(Dl, confFROMLINE)
E 13
I 9

E 9
E 6
# delimiter (operator) characters
D 3
Do.:%@!^=/[]
E 3
I 3
D 4
Do.:%@!^=/[]|
E 4
I 4
D 9
Do.:%@!^=/[]
E 9
I 9
D 13
Do.:%@!^/[]
E 13
I 13
CONCAT(Do, confOPERATORS)
E 13

E 9
E 4
E 3
# format of a total name
D 11
Dq$g$?x ($x)$.
E 11
I 11
D 13
Dq`'ifdef(`_OLD_SENDMAIL_', `$g$?x ($x)$.', `$?x$x <$g>$|$g$.')
E 13
I 13
CONCAT(Dq, ifdef(`confFROMHEADER', confFROMHEADER, ifdef(`_OLD_SENDMAIL_', `$g$?x ($x)$.', `$?x$x <$g>$|$g$.')
E 13
E 11
I 9

E 9
# SMTP login message
D 13
De$j Sendmail $v/$Z ready at $b
E 13
I 13
CONCAT(De, confSMTPLOGIN)
E 13

###############
#   Options   #
###############

D 7
# location of alias file
D 5
CONCAT(OA, ifdef(`ALIAS_FILE', ALIAS_FILE, /usr/lib/aliases))
E 5
I 5
CONCAT(OA, ifdef(`ALIAS_FILE', ALIAS_FILE, /etc/aliases))
E 7
I 7
D 13
# (don't) preserve 8 bits on message body on input
O8False
E 13
I 13
# preserve 8 bits on message body on input?
CONCAT(O8, confEIGHTBITS)
E 13

E 7
E 5
D 13
# wait up to ten minutes for alias file rebuild
Oa10
E 13
I 13
# wait (in minutes) for alias file rebuild
CONCAT(Oa, confALIASWAIT)
E 13
I 7

# location of alias file
D 13
OA`'ifdef(`ALIAS_FILE', ALIAS_FILE, /etc/aliases)
E 13
I 13
CONCAT(OA, ifdef(`ALIAS_FILE', ALIAS_FILE, /etc/aliases))
E 13

E 7
# substitution for space (blank) characters
D 13
OB.
E 13
I 13
CONCAT(OB, confBLANKSUB)
E 13
I 7

E 7
D 13
# (don't) connect to "expensive" mailers
D 7
#Oc
E 7
I 7
OcFalse
E 13
I 13
# connect to "expensive" mailers on initial submission?
CONCAT(Oc, confCONEXPENSIVE)
E 13

D 13
# checkpoint queue runs after every 10 successful deliveries
OC10
E 13
I 13
# checkpoint queue runs after every N successful deliveries
CONCAT(OC, confCHECKPOINTINTERVAL)
E 13

E 7
D 13
# default delivery mode (deliver in background)
Odbackground
E 13
I 13
# default delivery mode
CONCAT(Od, confDELIVERYMODE)
E 13
I 7

D 13
# (don't) automatically rebuild the alias database
ODFalse
E 13
I 13
# automatically rebuild the alias database?
CONCAT(OD, confAUTOREBUILD)
E 13

# discard Unix-style "From_" lines at top of header
D 13
OfFalse
E 13
I 13
CONCAT(Of, confDISCARDFROM)
E 13

E 7
# temporary file mode
D 13
OF0600
E 13
I 13
CONCAT(OF, confTEMPMODE)
E 13
I 7

E 7
# default GID
D 13
Og1
E 13
I 13
CONCAT(Og, confDEFGROUPID)
E 13
I 7

# maximum hop count
D 13
Oh17
E 13
I 13
CONCAT(Oh, confMAXHOP)
E 13

E 7
# location of help file
D 7
CONCAT(OH, ifdef(`HELP_FILE', HELP_FILE, /usr/lib/sendmail.hf))
E 7
I 7
D 13
OH`'ifdef(`HELP_FILE', HELP_FILE, /usr/lib/sendmail.hf)
E 13
I 13
CONCAT(OH, ifdef(`HELP_FILE', HELP_FILE, /usr/lib/sendmail.hf))
E 13

# (don't) ignore dots as terminators in incoming messages
D 13
OiFalse
E 13
I 13
CONCAT(Oi, confIGNOREDOTS)
E 13

# Insist that the BIND name server be running to resolve names
D 11
OITrue
E 11
I 11
D 13
OI
E 13
I 13
CONCAT(OI, confBINDOPTS)
E 13
E 11
I 9

# open connection cache size
D 11
Ok2
E 11
I 11
D 13
Ok`'ifdef(`MCI_CACHE_SIZE', MCI_CACHE_SIZE, 2)
E 13
I 13
CONCAT(Ok, confMCICACHESIZE)
E 13
E 11

# open connection cache timeout
D 11
OK5m
E 11
I 11
D 13
OK`'ifdef(`MCI_CACHE_TIMEOUT', MCI_CACHE_TIMEOUT, 5m)
E 13
I 13
CONCAT(OK, confMCICACHETIMEOUT)
E 13
E 11
E 9

E 7
# log level
D 13
OL9
E 13
I 13
CONCAT(OL, confLOGLEVEL)
E 13
D 7
# default network name
ONARPA
E 7
I 7

# (don't) send to me too, even in an alias expansion
D 13
OmFalse
E 13
I 13
CONCAT(Om, confMETOO)
E 13

E 7
D 13
# default messages to old style
D 7
Oo
E 7
I 7
OoTrue
E 13
I 13
# default messages to old style headers if no special punctuation
CONCAT(Oo, confOLDSTYLEHEADERS)
E 13

E 7
# queue directory
D 5
CONCAT(OQ, ifdef(`QUEUE_DIR', QUEUE_DIR, /usr/spool/mqueue))
E 5
I 5
D 7
CONCAT(OQ, ifdef(`QUEUE_DIR', QUEUE_DIR, /var/spool/mqueue))
E 7
I 7
D 13
OQ`'ifdef(`QUEUE_DIR', QUEUE_DIR, /var/spool/mqueue)
E 13
I 13
CONCAT(OQ, ifdef(`QUEUE_DIR', QUEUE_DIR, /var/spool/mqueue))
E 13

E 7
E 5
D 13
# read timeout -- violates protocols
Or2h
E 13
I 13
# read timeout -- now OK per RFC 1123 section 5.3.2
CONCAT(Or, confREADTIMEOUT)
E 13
D 7
# status file
D 5
CONCAT(OS, ifdef(`STATUS_FILE', STATUS_FILE, /usr/lib/sendmail.st))
E 5
I 5
CONCAT(OS, ifdef(`STATUS_FILE', STATUS_FILE, /etc/sendmail.st))
E 7
I 7

E 7
E 5
# queue up everything before starting transmission
D 7
Os
E 7
I 7
D 13
OsTrue
E 13
I 13
CONCAT(Os, confSAFEQUEUE)
E 13

# status file
D 13
OS`'ifdef(`STATUS_FILE', STATUS_FILE, /etc/sendmail.st)
E 13
I 13
CONCAT(OS, ifdef(`STATUS_FILE', STATUS_FILE, /etc/sendmail.st))
E 13

E 7
D 13
# default timeout interval
OT3d
E 13
I 13
# default message timeout interval
CONCAT(OT, confMESSAGETIMEOUT)
E 13
D 7
# time zone names (V6 only)
OtPST,PDT
E 7
I 7

# time zone names (System V only)
D 13
OtPST8PDT
E 13
I 13
CONCAT(Ot, confTIMEZONE)
E 13

E 7
# default UID
D 13
Ou1
E 13
I 13
CONCAT(Ou, confDEFUSERID)
E 13
D 7
# wizard's password
OW*
E 7
I 7

E 7
# load average at which we just queue messages
D 13
Ox8
E 13
I 13
CONCAT(Ox, confQUEUELA)
E 13
I 7

E 7
# load average at which we refuse connections
D 13
OX12
E 13
I 13
CONCAT(OX, confREFUSELA)
E 13
I 7

D 13
# (don't) deliver each queued job in a separate process
OYFalse
E 13
I 13
# deliver each queued job in a separate process?
CONCAT(OY, confSEPARATEPROC)
E 13
E 7

###########################
#   Message precedences   #
###########################

Pfirst-class=0
Pspecial-delivery=100
Pbulk=-60
Pjunk=-100

#####################
#   Trusted users   #
#####################

Troot
Tdaemon
Tuucp

#########################
#   Format of headers   #
#########################

D 6
H?P?Return-Path: <$g>
E 6
I 6
H?P?Return-Path: <$?<$<$|$g$.>
E 6
D 8
HReceived: $?sfrom $s $.by $j ($v/$Z)
	id $i; $b
E 8
I 8
HReceived: $?sfrom $s $.by $j ($v/$Z) id $i; $b
E 8
H?D?Resent-Date: $a
H?D?Date: $a
H?F?Resent-From: $q
H?F?From: $q
H?x?Full-Name: $x
HSubject:
# HPosted-Date: $a
# H?l?Received-Date: $b
H?M?Resent-Message-Id: <$t.$i@$j>
H?M?Message-Id: <$t.$i@$j>
E 1
