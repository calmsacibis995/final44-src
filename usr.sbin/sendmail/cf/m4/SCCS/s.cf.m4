h05362
s 00001/00001/00117
d D 8.20 95/05/24 15:34:33 eric 58 57
c default confCHECK_ALIASES off -- too confusing for many folks
e
s 00000/00005/00118
d D 8.19 95/05/18 08:23:38 eric 57 56
c eliminate dotted users in favor of plussed users
e
s 00001/00000/00122
d D 8.18 95/04/26 09:27:34 eric 56 55
c add _OPTINS (optional insert) macro to shorten lines in mailers
e
s 00001/00002/00121
d D 8.17 95/04/21 11:07:14 eric 55 54
c avoid random tab characters after OSTYPE macro
e
s 00001/00001/00122
d D 8.16 95/04/21 10:11:44 eric 54 53
c copyright update
e
s 00007/00001/00116
d D 8.15 95/04/21 08:42:30 eric 53 52
c insist on an OSTYPE macro (4.3 defaults don't cut it any more)
e
s 00001/00001/00116
d D 8.14 95/04/10 11:04:24 eric 52 51
c eliminate BrokenSmtpPeers and two line SMTP greeting messages
e
s 00003/00018/00114
d D 8.13 95/03/30 11:00:56 eric 51 50
c clean up option setting and move it to 8.7 long option name syntax
e
s 00001/00001/00131
d D 8.12 95/01/24 07:35:59 eric 50 49
c change SortQueueByHost option to QueueSortOrder
e
s 00001/00001/00131
d D 8.11 94/11/13 16:46:36 eric 49 48
c accept user+detail
e
s 00001/00000/00131
d D 8.10 94/10/16 11:52:54 eric 48 47
c add confRECEIVED_HEADER to set the format of the Received: line
e
s 00001/00000/00130
d D 8.9 94/10/15 08:32:09 eric 47 46
c add confDONT_PRUNE_ROUTES to set option R
e
s 00002/00000/00128
d D 8.8 94/08/17 08:44:42 eric 46 45
c add confSORT_QUEUE_BY_HOST and confBROKEN_SMTP_PEERS
e
s 00001/00000/00127
d D 8.7 94/07/23 10:49:17 eric 45 44
c MIME support
e
s 00005/00000/00122
d D 8.6 94/07/16 10:21:09 eric 44 43
c add dotted users
e
s 00000/00001/00122
d D 8.5 94/07/02 08:16:36 eric 43 42
c delete OLD_SENDMAIL support
e
s 00001/00001/00122
d D 8.4 93/12/24 06:34:40 eric 42 41
c be sure to include $U.UUCP in the list of local names
e
s 00001/00000/00122
d D 8.3 93/12/22 16:08:16 eric 41 40
c hpux portability change -- don't make "hpux" symbol special
e
s 00001/00000/00121
d D 8.2 93/07/18 10:58:53 eric 40 39
c add confTRY_NULL_MX_LIST
e
s 00002/00002/00119
d D 8.1 93/06/07 10:11:00 bostic 39 38
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00120
d D 6.17 93/06/05 09:22:07 eric 38 37
c add 'l' option on confUSE_ERRORS_TO
e
s 00001/00001/00119
d D 6.16 93/06/01 12:03:41 eric 37 36
c use ^A as comment character (so we interpolate in comments)
e
s 00002/00001/00118
d D 6.15 93/05/11 08:42:24 eric 36 35
c O8 => O7; add Oj
e
s 00001/00000/00118
d D 6.14 93/05/01 14:43:02 eric 35 34
c new GNU m4 hacks
e
s 00004/00004/00114
d D 6.13 93/05/01 14:35:34 eric 34 33
c be more conservative about saving diversions
e
s 00003/00003/00115
d D 6.12 93/03/25 10:29:17 eric 33 32
c change some of the defaults
e
s 00004/00004/00114
d D 6.11 93/03/23 16:14:23 eric 32 31
c let FEATURE, HACK, OSTYPE, and DOMAIN take an optional argument
e
s 00001/00001/00117
d D 6.10 93/03/15 13:05:26 eric 31 30
c delete $<
e
s 00017/00001/00101
d D 6.9 93/03/15 13:04:25 eric 30 29
c add LOCAL_RULE_1 and LOCAL_RULE_2
e
s 00001/00000/00101
d D 6.8 93/03/03 10:06:58 eric 29 28
c allow redefinition of sendmail.cw path
e
s 00001/00001/00100
d D 6.7 93/02/24 09:36:34 eric 28 27
c don't use word "define" even in a comment
e
s 00001/00002/00100
d D 6.6 93/02/21 12:40:33 eric 27 26
c adjust timeout values
e
s 00002/00000/00100
d D 6.5 93/02/20 13:48:07 eric 26 25
c add defaults for b (minimum free blocks) and p (privacy) options
e
s 00001/00000/00099
d D 6.4 93/02/19 16:30:10 eric 25 24
c add SMART_HOST support and ability to route to local net hosts
c and send remote traffic to UUCP (or other long haul transport agent)
e
s 00001/00000/00098
d D 6.3 93/02/15 12:01:22 eric 24 23
c fix botches with confNO_WILDCARD_MX and confMATCH_GECOS
e
s 00033/00000/00065
d D 6.2 93/02/12 12:10:49 eric 23 22
c make everything configurable on M4 macros
e
s 00000/00000/00065
d D 6.1 92/12/21 16:08:14 eric 22 21
c Release 6
e
s 00004/00001/00061
d D 2.21 92/12/20 13:21:54 eric 21 20
c cleanup for new features and release engineering
e
s 00004/00002/00058
d D 2.20 92/11/14 08:21:23 eric 20 19
c remove hacks for dead m4 versions
e
s 00001/00001/00059
d D 2.19 92/11/14 00:53:02 eric 19 18
c fake a non-zero exit status code
e
s 00001/00000/00059
d D 2.18 92/11/13 23:29:07 eric 18 17
c give a diagnostic if the M4 is too old
e
s 00003/00004/00056
d D 2.17 92/11/13 23:00:29 eric 17 16
c hacks to make it work for GNU m4 (ugh)
e
s 00002/00001/00058
d D 2.16 92/11/13 21:57:45 eric 16 15
c make it so it will work on systems without m4_wrap
e
s 00004/00003/00055
d D 2.15 92/11/13 21:50:27 eric 15 14
c make more portable to other versions of m4
e
s 00001/00001/00057
d D 2.14 91/12/17 15:54:30 eric 14 13
c make NEWSENDMAIL the default
e
s 00001/00000/00057
d D 2.13 91/12/12 11:53:52 eric 13 12
c "OLDSENDMAIL" macro undefines "NEWSENDMAIL"
e
s 00001/00000/00056
d D 2.12 91/12/12 10:49:20 eric 12 11
c modifications for CS subdomain server
e
s 00001/00001/00055
d D 2.11 91/10/05 12:38:21 eric 11 10
c bug in MAILER macro
e
s 00000/00003/00056
d D 2.10 91/10/05 11:46:19 eric 10 9
c don't pull in local immediately; there may be pathname overrides
e
s 00006/00001/00053
d D 2.9 91/10/03 15:05:28 eric 9 8
c allow respecification of mailers; local mailer is assumed
e
s 00001/00000/00053
d D 2.8 91/10/03 10:24:16 eric 8 7
c include uucp name in $=w
e
s 00001/00000/00052
d D 2.7 91/10/03 00:57:16 eric 7 6
c more cleaning up...
e
s 00004/00002/00048
d D 2.6 91/10/03 00:35:27 eric 6 5
c make "smart" uucp hosts into an option on the SITE macro
e
s 00002/00000/00048
d D 2.5 91/10/02 23:53:42 eric 5 4
c allow definitions of names that override $R
e
s 00005/00001/00043
d D 2.4 91/10/02 21:20:16 eric 4 3
c enhancements for ucbvax
e
s 00004/00005/00040
d D 2.3 91/10/02 18:38:51 eric 3 2
c make it work on 4.4bsd m4
e
s 00002/00001/00043
d D 2.2 91/10/02 15:32:39 eric 2 1
c hack around System V M4 definitions of $*, $@, etc.; also, $N
c is interpolated in arguments even if the args are quoted.
e
s 00044/00000/00000
d D 2.1 91/10/02 14:48:10 eric 1 0
c date and time created 91/10/02 14:48:10 by eric
e
u
U
t
T
I 1
divert(0)dnl
#
D 54
# Copyright (c) 1983 Eric P. Allman
E 54
I 54
# Copyright (c) 1983, 1995 Eric P. Allman
E 54
D 39
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 39
I 39
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 39
#
# %sccs.include.redist.sh%
#
D 17
#	%W% (Berkeley) %G%
#
E 17


######################################################################
######################################################################
#####
#####		SENDMAIL CONFIGURATION FILE
#####
define(`TEMPFILE', maketemp(/tmp/cfXXXXXX))dnl
syscmd(sh ../sh/makeinfo.sh > TEMPFILE)dnl
include(TEMPFILE)dnl
syscmd(rm -f TEMPFILE)dnl
#####
######################################################################
######################################################################

divert(-1)

I 15
D 37
changecom()
E 37
I 37
changecom()
E 37
I 35
undefine(`format')
I 41
undefine(`hpux')
E 41
E 35
I 18
D 19
ifdef(`pushdef', `', `errprint(`You need a newer version of M4')m4exit(70)')
E 19
I 19
D 20
ifdef(`pushdef', `', `errprint(`You need a newer version of M4')include(NoSuchFile)')
E 20
I 20
ifdef(`pushdef', `',
	`errprint(`You need a newer version of M4, at least as new as
System V or GNU')
	include(NoSuchFile)')
E 20
E 19
E 18
E 15
define(`PUSHDIVERT', `pushdef(`__D__', divnum)divert($1)')
define(`POPDIVERT', `divert(__D__)popdef(`__D__')')
D 32
define(`OSTYPE', `include(../ostype/$1.m4)')
E 32
I 32
D 34
define(`OSTYPE', `define(`_ARG_', $2)include(../ostype/$1.m4)')
E 34
I 34
D 53
define(`OSTYPE', `PUSHDIVERT(-1)define(`_ARG_', $2)include(../ostype/$1.m4)POPDIVERT`'')
E 53
I 53
define(`OSTYPE',
	`PUSHDIVERT(-1)
	ifdef(`__OSTYPE__', `errprint(`duplicate OSTYPE')')
	define(`__OSTYPE__', $1)
	define(`_ARG_', $2)
D 55
	include(../ostype/$1.m4)
	POPDIVERT`'')
E 55
I 55
	include(../ostype/$1.m4)POPDIVERT`'')
E 55
E 53
E 34
E 32
D 9
define(`MAILER', `PUSHDIVERT(7)include(../mailer/$1.m4)POPDIVERT`'')
E 9
I 9
define(`MAILER',
D 11
`ifdef(`_MAILER_$1_', `dnl',
E 11
I 11
`ifdef(`_MAILER_$1_', `dnl`'',
E 11
D 15
`define(`_MAILER_$1_')PUSHDIVERT(7)include(../mailer/$1.m4)POPDIVERT`'')')
E 15
I 15
`define(`_MAILER_$1_', `')PUSHDIVERT(7)include(../mailer/$1.m4)POPDIVERT`'')')
E 15
E 9
D 32
define(`DOMAIN', `include(../domain/$1.m4)')
define(`FEATURE', `include(../feature/$1.m4)')
define(`HACK', `include(../hack/$1.m4)')
E 32
I 32
D 34
define(`DOMAIN', `define(`_ARG_', $2)include(../domain/$1.m4)')
define(`FEATURE', `define(`_ARG_', $2)include(../feature/$1.m4)')
define(`HACK', `define(`_ARG_', $2)include(../hack/$1.m4)')
E 34
I 34
define(`DOMAIN', `PUSHDIVERT(-1)define(`_ARG_', $2)include(../domain/$1.m4)POPDIVERT`'')
define(`FEATURE', `PUSHDIVERT(-1)define(`_ARG_', $2)include(../feature/$1.m4)POPDIVERT`'')
define(`HACK', `PUSHDIVERT(-1)define(`_ARG_', $2)include(../hack/$1.m4)POPDIVERT`'')
E 34
E 32
I 13
D 14
define(`OLDSENDMAIL', `undefine(`NEWSENDMAIL')')
E 14
I 14
D 15
define(`OLDSENDMAIL', `define(`_OLD_SENDMAIL_')')
E 15
I 15
D 43
define(`OLDSENDMAIL', `define(`_OLD_SENDMAIL_', `')')
E 43
E 15
E 14
E 13
D 3
#define(`VERSIONID', `PUSHDIVERT(1)#	$1
#POPDIVERT')
define(`VERSIONID', ``#####'  $1  #####')
m4wrap(`include(../m4/proto.m4)')
E 3
I 3
define(`VERSIONID', ``#####  $1  #####'')
E 3
D 30
define(`LOCAL_RULE_3', `divert(2)')
E 30
define(`LOCAL_RULE_0', `divert(3)')
I 30
define(`LOCAL_RULE_1',
`divert(9)dnl
#######################################
###  Ruleset 1 -- Sender Rewriting  ###
#######################################

S1
')
define(`LOCAL_RULE_2',
`divert(9)dnl
##########################################
###  Ruleset 2 -- Recipient Rewriting  ###
##########################################

S2
')
define(`LOCAL_RULE_3', `divert(2)')
E 30
I 12
define(`LOCAL_CONFIG', `divert(6)')
I 25
define(`LOCAL_NET_CONFIG', `define(`_LOCAL_RULES_', 1)divert(1)')
I 44
D 57
define(`DOTTED_USER',
	`ifdef(`__DOTTED_USER_LIST__',
		`define(`__DOTTED_USER_LIST__', __DOTTED_USER_LIST__
CD $1)',
		`define(`__DOTTED_USER_LIST__', CD $1)')')
E 57
E 44
E 25
E 12
D 2
define(`UUCPSMTP', ``R$* < @' $1 `.UUCP > $*	$1 < @' $2 `< $3'')
E 2
I 2
D 3
define(`UUCPSMTP', `R DOL(*) < @' $1 `.UUCP > DOL(*)	DOL(1) < @ $2 > DOL(3)')
E 3
I 3
D 4
define(`UUCPSMTP', `R DOL(*) < @ $1 .UUCP > DOL(*)	DOL(1) < @ $2 > DOL(3)')
E 4
I 4
define(`UUCPSMTP', `R DOL(*) < @ $1 .UUCP > DOL(*)	DOL(1) < @ $2 > DOL(2)')
E 4
E 3
E 2
define(`CONCAT', `$1$2$3$4$5$6$7')
I 2
define(`DOL', ``$'$1')
I 4
define(`SITECONFIG',
D 6
`ifelse($2, -, `dnl', `CONCAT(D, $3, $2)')
define(`SITE', CONCAT(C, $3, DOL(1)))dnl
E 6
I 6
`CONCAT(D, $3, $2)
I 7
D 15
define(`_CLASS_$3_')dnl
E 15
I 15
define(`_CLASS_$3_', `')dnl
E 15
I 8
D 42
ifelse($3, U, Cw$2, `dnl')
E 42
I 42
ifelse($3, U, Cw$2 $2.UUCP, `dnl')
E 42
E 8
E 7
define(`SITE', `ifelse(CONCAT($'2`, $3), SU,
		CONCAT(CY, $'1`),
		CONCAT(C, $3, $'1`))')
E 6
sinclude(../siteconfig/$1.m4)')
I 5
D 21
define(`LOCAL_NAME', `PUSHDIVERT(5)CL$1
E 21
I 21
define(`EXPOSED_USER', `PUSHDIVERT(5)CE$1
E 21
POPDIVERT`'dnl')
I 21
define(`LOCAL_USER', `PUSHDIVERT(5)CL$1
POPDIVERT`'dnl')
define(`MASQUERADE_AS', `define(`MASQUERADE_NAME', $1)')
I 56
define(`_OPTINS', `ifdef(`$1', `$2$1$3')')
E 56
E 21
I 16
D 17
define(`DOIT', `include(`../m4/proto.m4')')
E 17
I 17
D 20
define(`DOIT', ifdef(`m4wrap', ``dnl'', ``include(`../m4/proto.m4')''))
E 20
E 17
E 16
E 5
E 4
I 3

D 16
m4wrap(`include(`../m4/proto.m4')')
E 16
I 16
D 17
m4wrap(`DOIT')
E 17
I 17
m4wrap(`include(`../m4/proto.m4')')
E 17
E 16
I 9

I 23
D 28
# define default values for options
E 28
I 28
# set up default values for options
E 28
define(`confMAILER_NAME', ``MAILER-DAEMON'')
D 31
define(`confFROM_LINE', `From $?<$<$|$g$.  $d')
E 31
I 31
define(`confFROM_LINE', `From $g  $d')
E 31
D 49
define(`confOPERATORS', `.:%@!^/[]')
E 49
I 49
define(`confOPERATORS', `.:%@!^/[]+')
E 49
D 52
define(`confSMTP_LOGIN_MSG', `$j Sendmail $v/$Z ready at $b')
E 52
I 52
define(`confSMTP_LOGIN_MSG', `$j Sendmail $v/$Z; $b')
E 52
I 48
define(`confRECEIVED_HEADER', `$?sfrom $s $.$?_($?s$|from $.$_) $.by $j ($v/$Z)$?r with $r$. id $i$?u for $u$.; $b')
E 48
D 33
define(`confEIGHT_BIT_INPUT', `False')
E 33
I 33
D 36
define(`confEIGHT_BIT_INPUT', `True')
E 36
I 36
define(`confSEVEN_BIT_INPUT', `False')
I 45
define(`confEIGHT_BIT_HANDLING', `pass8')
E 45
E 36
E 33
define(`confALIAS_WAIT', `10')
I 26
D 51
define(`confMIN_FREE_BLOCKS', `4')
E 51
I 51
define(`confMIN_FREE_BLOCKS', `100')
E 51
E 26
define(`confBLANK_SUB', `.')
define(`confCON_EXPENSIVE', `False')
D 51
define(`confCHECKPOINT_INTERVAL', `10')
E 51
define(`confDELIVERY_MODE', `background')
D 51
define(`confAUTO_REBUILD', `False')
define(`confSAVE_FROM_LINES', `False')
E 51
define(`confTEMP_FILE_MODE', `0600')
I 24
D 51
define(`confMATCH_GECOS', `False')
E 24
define(`confDEF_GROUP_ID', `1')
define(`confMAX_HOP', `17')
define(`confIGNORE_DOTS', `False')
define(`confBIND_OPTS', `')
E 51
define(`confMCI_CACHE_SIZE', `2')
define(`confMCI_CACHE_TIMEOUT', `5m')
I 38
define(`confUSE_ERRORS_TO', `False')
E 38
define(`confLOG_LEVEL', `9')
D 51
define(`confME_TOO', `False')
E 51
D 58
define(`confCHECK_ALIASES', `True')
E 58
I 58
define(`confCHECK_ALIASES', `False')
E 58
define(`confOLD_STYLE_HEADERS', `True')
I 26
D 33
define(`confPRIVACY_FLAGS', `public')
E 33
I 33
define(`confPRIVACY_FLAGS', `authwarnings')
I 47
D 51
define(`confDONT_PRUNE_ROUTES', `False')
E 51
E 47
E 33
E 26
D 27
define(`confREAD_TIMEOUT', `20m')
E 27
define(`confSAFE_QUEUE', `True')
D 27
define(`confMESSAGE_TIMEOUT', `3d')
E 27
I 27
D 33
define(`confMESSAGE_TIMEOUT', `5d')
E 33
I 33
define(`confMESSAGE_TIMEOUT', `5d/4h')
E 33
E 27
define(`confTIME_ZONE', `USE_SYSTEM')
D 51
define(`confDEF_USER_ID', `1')
define(`confQUEUE_LA', `8')
define(`confREFUSE_LA', `12')
define(`confSEPARATE_PROC', `False')
E 51
I 51
define(`confDEF_USER_ID', `1:1')
E 51
I 29
define(`confCW_FILE', `/etc/sendmail.cw')
I 36
define(`confMIME_FORMAT_ERRORS', `True')
I 40
D 51
define(`confTRY_NULL_MX_LIST', `False')
I 46
D 50
define(`confSORT_QUEUE_BY_HOST', `False')
E 50
I 50
define(`confQUEUE_SORT_ORDER', `Priority')
E 50
define(`confBROKEN_SMTP_PEERS', `False')
E 51
I 51
define(`confFORWARD_PATH', `$z/.forward.$w:$z/.forward')
E 51
E 46
E 40
E 36
E 29

E 23
D 10
# a local mailer is required
MAILER(local)
E 9
E 3
E 2

E 10
divert(0)dnl
I 17
VERSIONID(`%W% (Berkeley) %G%')
E 17
E 1
