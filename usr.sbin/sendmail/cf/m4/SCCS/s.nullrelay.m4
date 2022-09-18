h03320
s 00001/00001/00080
d D 8.8 95/04/21 10:11:44 eric 8 7
c copyright update
e
s 00000/00198/00081
d D 8.7 95/03/30 11:00:59 eric 7 6
c clean up option setting and move it to 8.7 long option name syntax
e
s 00003/00000/00276
d D 8.6 94/07/23 10:49:20 eric 6 5
c MIME support
e
s 00001/00001/00275
d D 8.5 94/02/01 10:16:31 eric 5 4
c fix route-addr syntax
e
s 00012/00009/00264
d D 8.4 93/09/03 09:20:37 eric 4 3
c allow FEATURE(nocanonify) to turn off canonification of names
e
s 00001/00001/00272
d D 8.3 93/08/24 14:20:49 eric 3 2
c fix time zone USE_TZ special case
e
s 00002/00000/00271
d D 8.2 93/08/21 16:19:07 eric 2 1
c add comment regarding Bryan's contribution
e
s 00271/00000/00000
d D 8.1 93/08/21 15:02:39 eric 1 0
c date and time created 93/08/21 15:02:39 by eric
e
u
U
t
T
I 1
divert(-1)
#
D 8
# Copyright (c) 1983 Eric P. Allman
E 8
I 8
# Copyright (c) 1983, 1995 Eric P. Allman
E 8
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
#
# %sccs.include.redist.sh%
#
divert(0)

VERSIONID(`%W% (Berkeley) %G%')

#
#  This configuration applies only to relay-only hosts.  They send
#  all mail to a hub without consideration of the address syntax
#  or semantics, except for adding the hub qualification to the
#  addresses.
#
I 2
#	This is based on a prototype done by Bryan Costales of ICSI.
#
E 2

D 7
# hub host (to which all mail is sent)
DH`'ifdef(`MAIL_HUB', MAIL_HUB,
D 4
	ifdef(`LOCAL_RELAY', LOCAL_RELAY,
	ifdef(`SMART_HOST', SMART_HOST)))
E 4
I 4
	`errprint(`MAIL_HUB not defined for nullclient feature')')
E 4

I 4
# name from which everyone will appear to come
DM`'ifdef(`MASQUERADE_NAME', MASQUERADE_NAME, MAIL_HUB)

E 4
# route-addr separators
C: : ,

undivert(6)dnl

######################
#   Special macros   #
######################

# SMTP initial login message
De`'confSMTP_LOGIN_MSG

# UNIX initial From header format
Dl`'confFROM_LINE

# my name for error messages
Dn`'confMAILER_NAME

# delimiter (operator) characters
Do`'confOPERATORS

# format of a total name
Dq<$g>
include(`../m4/version.m4')

###############
#   Options   #
###############

# strip message body to 7 bits on input?
O7`'confSEVEN_BIT_INPUT

I 6
# eight bit data handling
O8`'confEIGHT_BIT_HANDLING

E 6
# no aliases here

# substitution for space (blank) characters
OB`'confBLANK_SUB

# default delivery mode
Od`'confDELIVERY_MODE

# error message header/file
ifdef(`confERROR_MESSAGE',
	OE`'confERROR_MESSAGE,
	#OE/etc/sendmail.oE)

# error mode
ifdef(`confERROR_MODE',
	Oe`'confERROR_MODE,
	#Oep)

# save Unix-style "From_" lines at top of header?
Of`'confSAVE_FROM_LINES

# temporary file mode
OF`'confTEMP_FILE_MODE

# default GID
Og`'confDEF_GROUP_ID

# maximum hop count
Oh`'confMAX_HOP

# location of help file
OH`'ifdef(`HELP_FILE', HELP_FILE, /usr/lib/sendmail.hf)

# ignore dots as terminators in incoming messages?
Oi`'confIGNORE_DOTS

# Insist that the BIND name server be running to resolve names
ifdef(`confBIND_OPTS',
	OI`'confBIND_OPTS,
	#OI)

# deliver MIME-encapsulated error messages?
Oj`'confMIME_FORMAT_ERRORS

# open connection cache size
Ok`'confMCI_CACHE_SIZE

# open connection cache timeout
OK`'confMCI_CACHE_TIMEOUT

# use Errors-To: header?
Ol`'confUSE_ERRORS_TO

# log level
OL`'confLOG_LEVEL

# send to me too, even in an alias expansion?
Om`'confME_TOO

# default messages to old style headers if no special punctuation?
Oo`'confOLD_STYLE_HEADERS

# SMTP daemon options
ifdef(`confDAEMON_OPTIONS',
	OO`'confDAEMON_OPTIONS,
	#OOPort=esmtp)

# privacy flags
Op`'confPRIVACY_FLAGS

# who (if anyone) should get extra copies of error messages
ifdef(`confCOPY_ERRORS_TO',
	OP`'confCOPY_ERRORS_TO,
	#OPPostmaster)

# slope of queue-only function
ifdef(`confQUEUE_FACTOR',
	Oq`'confQUEUE_FACTOR,
	#Oq600000)

# queue directory
OQ`'ifdef(`QUEUE_DIR', QUEUE_DIR, /var/spool/mqueue)

# read timeout -- now OK per RFC 1123 section 5.3.2
ifdef(`confREAD_TIMEOUT',
	Or`'confREAD_TIMEOUT,
	#Ordatablock=10m)

# queue up everything before forking?
Os`'confSAFE_QUEUE

# status file
OS`'ifdef(`STATUS_FILE', STATUS_FILE, /etc/sendmail.st)

# default message timeout interval
OT`'confMESSAGE_TIMEOUT

# time zone handling:
#  if undefined, use system default
#  if defined but null, use TZ envariable passed in
#  if defined and non-null, use that info
ifelse(confTIME_ZONE, `USE_SYSTEM', `#Ot',
D 3
	confTIME_ZONE, `USE_TZ', `',
E 3
I 3
	confTIME_ZONE, `USE_TZ', `Ot',
E 3
	`Ot`'confTIME_ZONE')

# default UID
Ou`'confDEF_USER_ID

# deliver each queued job in a separate process?
OY`'confSEPARATE_PROC

# work class factor
ifdef(`confWORK_CLASS_FACTOR',
	Oz`'confWORK_CLASS_FACTOR,
	#Oz1800)

# work time factor
ifdef(`confWORK_TIME_FACTOR',
	OZ`'confWORK_TIME_FACTOR,
	#OZ90000)

###########################
#   Message precedences   #
###########################

Pfirst-class=0
Pspecial-delivery=100
Plist=-30
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

H?P?Return-Path: $g
HReceived: $?sfrom $s $.$?_($_) $.by $j ($v/$Z)$?r with $r$. id $i$?u for $u$.; $b
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
#
E 7
######################################################################
######################################################################
#####
#####			REWRITING RULES
#####
######################################################################
######################################################################

###########################################
###  Rulset 3 -- Name Canonicalization  ###
###########################################
S3

# handle null input and list syntax (translate to <@> special case)
R$@			$@ <@>
R$*:;$*			$@ $1 :; <@>

# basic textual canonicalization -- note RFC733 heuristic here
R$*<$*>$*<$*>$*		$2$3<$4>$5			strip multiple <> <>
R$*<$*<$+>$*>$*		<$3>$5				2-level <> nesting
R$*<>$*			$@ <@>				MAIL FROM:<> case
R$*<$+>$*		$2				basic RFC821/822 parsing

D 4
# eliminate local host if present
R@ $=w $=: $+		$@ @ $H $2 $3			@thishost ...
E 4
I 4
ifdef(`_NO_CANONIFY_', `dnl',
`# eliminate local host if present
R@ $=w $=: $+		$@ @ $M $2 $3			@thishost ...
E 4
D 5
R@ $+			$@ $1				@somewhere ...
E 5
I 5
R@ $+			$@ @ $1				@somewhere ...
E 5

D 4
R$+ @ $=w		$@ $1 @ $H			...@thishost
E 4
I 4
R$+ @ $=w		$@ $1 @ $M			...@thishost
E 4
R$+ @ $+		$@ $1 @ $2			...@somewhere

D 4
R$=w ! $+		$@ $2 @ $H			thishost!...
R$+ ! $+		$@ $1 ! $2 @ $H			somewhere ! ...
E 4
I 4
R$=w ! $+		$@ $2 @ $M			thishost!...
R$+ ! $+		$@ $1 ! $2 @ $M			somewhere ! ...
E 4

D 4
R$+ % $=w		$@ $1 @ $H			...%thishost
E 4
I 4
R$+ % $=w		$@ $1 @ $M			...%thishost
E 4
R$+ % $+		$@ $1 @ $2			...%somewhere

D 4
R$+			$@ $1 @ $H			unadorned user
E 4
I 4
R$+			$@ $1 @ $M			unadorned user')
E 4


######################################
###   Ruleset 0 -- Parse Address   ###
######################################

S0

R$*:;<@>		$#error $@ USAGE $: "list:; syntax illegal for recipient addresses"

# pass everything else to a relay host
R$*			$#_RELAY_ $@ $H $: $1

#
######################################################################
######################################################################
#####
`#####			MAILER DEFINITIONS'
#####
######################################################################
######################################################################
undivert(7)dnl
E 1
