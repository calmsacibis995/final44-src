h31866
s 00001/00001/00012
d D 8.6.12.8 95/06/21 08:49:14 eric 73 72
c Beta.7
e
s 00001/00001/00012
d D 8.6.12.7 95/06/19 20:50:31 eric 72 71
c Beta.6
e
s 00001/00001/00012
d D 8.6.12.6 95/06/16 12:04:30 eric 71 70
c Beta.5
e
s 00001/00001/00012
d D 8.6.12.5 95/06/10 14:53:41 eric 70 69
c add confCF_VERSION to set local version info
e
s 00001/00001/00012
d D 8.6.12.4 95/05/29 10:29:26 eric 69 68
c Beta.2
e
s 00001/00001/00012
d D 8.6.12.3 95/05/26 06:38:15 eric 68 67
c beta.1
e
s 00002/00002/00011
d D 8.6.12.2 95/05/24 17:17:25 eric 67 66
c make it 8.7.Beta
e
s 00000/00000/00013
d D 8.6.12.1 95/03/28 18:27:09 eric 66 65
c no changes -- just to make version number match binary
e
s 00000/00000/00013
d D 8.6.11.1 95/03/04 08:40:37 eric 65 64
c update for 8.6.11 (no changes in configuration proper)
e
s 00000/00000/00013
d D 8.6.10.1 95/02/10 08:14:40 eric 64 63
c bump version number for 8.6.10 (no config changes)
e
s 00000/00000/00013
d D 8.6.9.1 94/04/18 22:17:39 eric 63 62
c UUCP hacks to avoid bogus $h problems
e
s 00000/00000/00013
d D 8.6.8.1 94/04/18 22:17:17 eric 62 61
c 
e
s 00000/00000/00013
d D 8.6.7.1 94/04/18 22:17:14 eric 61 60
c 
e
s 00000/00000/00013
d D 8.6.6.1 94/03/13 09:44:58 eric 60 59
c 8.6.6 -- see RELEASE_NOTES for details
e
s 00000/00000/00013
d D 8.6.5.1 94/01/13 06:42:08 eric 59 58
c version 8.6.5 -- see RELEASE_NOTES for details
e
s 00000/00000/00013
d D 8.6.4.1 93/10/31 12:35:41 eric 58 57
c see RELEASE_NOTES
e
s 00000/00000/00013
d D 8.6.3.1 93/10/24 10:38:32 eric 57 56
c 8.6.3: mainly domain masquerading
e
s 00000/00000/00013
d D 8.6.2.1 93/10/15 08:58:30 eric 56 55
c placeholder to make version number match binary
e
s 00001/00001/00012
d D 8.6.1.1 93/10/15 08:35:23 eric 55 54
c fix mailer:host syntax for UUCP relays
e
s 00000/00000/00013
d D 8.6 93/10/05 11:00:00 eric 54 53
c many changes -- see RELEASE_NOTES
e
s 00000/00000/00013
d D 8.5 93/07/23 14:54:26 eric 53 52
c default confSMTP_MAILER to smtp, not esmtp; add confRELAY_MAILER
c and generalize relaying syntax processing -- fixes problem with
c route-addrs misinterpreted as relays
e
s 00000/00000/00013
d D 8.4 93/07/22 15:58:35 eric 52 51
c w option; generalize all relays to accept mailer:host; move LOCAL_RULE_0
c processing up; add confSMTP_MAILER to define the mailer used; misc changes
e
s 00000/00000/00013
d D 8.3 93/07/13 12:59:32 eric 51 50
c add uucp-dom mailer, OSTYPE(aix3), LOCAL_SHELL_{FLAGS,ARGS}, UUCP_MAX_SIZE
e
s 00001/00001/00012
d D 8.2 93/07/11 11:59:11 eric 50 49
c many changes including: SMART_HOST overrides SMTP mailer (use
c LOCAL_NET_CONFIG instead); add FEATURE(domaintable).  See RELEASE_NOTES
c for details.
e
s 00002/00002/00011
d D 8.1 93/06/27 18:37:49 bostic 49 48
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00001/00012
d D 6.35 93/06/24 18:16:26 eric 48 46
c concat => CONCAT
e
s 00002/00002/00011
d R 8.1 93/06/07 10:11:11 bostic 47 46
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00000/00000/00013
d D 6.34 93/06/06 21:24:50 eric 46 45
c fix yet more mailertable bugs (sigh)
e
s 00000/00000/00013
d D 6.33 93/06/05 09:23:42 eric 45 44
c fix stupid mailertable typos; add confUSE_ERRORS_TO for 'l' option;
c use $M instead of $j on ALWAYS_ADD_DOMAIN; don't add dots to relay names
c (can be added by hand)
e
s 00000/00000/00013
d D 6.32 93/06/01 12:04:48 eric 44 43
c put $r into Received: line; ruleset 6 => 96, 7 => 97; fix ruleset
c 90 typo; recognize $=w as local instead of $j (major fix)
e
s 00000/00000/00013
d D 6.31 93/05/28 07:19:51 eric 43 42
c have mailertable look for partial domains as well as full domains
e
s 00000/00000/00013
d D 6.30 93/05/24 09:21:01 eric 42 41
c add FEATURE(always_add_domain); avoid rewriting $=w into $j
c (some hosts have multiple "canonical" names)
e
s 00000/00000/00013
d D 6.29 93/05/22 09:43:39 eric 41 40
c don't pass pseudo-domains to $[ ... $] (can cause wierd problems
c with wildcard MX records); dot terminate relay hostnames in S0.
e
s 00000/00000/00013
d D 6.28 93/05/11 08:33:22 eric 40 39
c Option 8 => option 7; add Oj (confMIME_FORMAT_ERRORS)
e
s 00000/00000/00013
d D 6.27 93/05/01 17:57:44 eric 39 38
c undo botch with not stripping trailing dots off addresses
e
s 00000/00000/00013
d D 6.26 93/05/01 08:28:45 eric 38 37
c clean up UUCP route-addrs; delete unnecessary angle brackets
c (they are just stripped by S4 anyway) in user part of $# triple
e
s 00000/00000/00013
d D 6.25 93/04/12 14:34:12 eric 37 36
c back out hack to hide unqualified domains behind %-hack -- it breaks
c local aliases and .forward files
e
s 00000/00000/00013
d D 6.24 93/04/10 10:22:27 eric 36 35
c %-hack single token hostnames behind $s if $r is specified
e
s 00000/00000/00013
d D 6.23 93/04/04 16:05:43 eric 35 34
c log $_ (authenticated sender info) in Received: line; use D= on
c prog mailer
e
s 00000/00000/00013
d D 6.22 93/03/29 17:26:38 eric 34 33
c add O and V options; fix typo in mailertable code
e
s 00000/00000/00013
d D 6.21 93/03/25 10:38:16 eric 33 32
c default several new options on; use dequote map; minor typo fixes
e
s 00000/00000/00013
d D 6.20 93/03/23 16:16:43 eric 32 31
c add FEATURE(mailertable); let FEATURE, HACK, OSTYPE, and DOMAIN
c take an optional parameter
e
s 00000/00000/00013
d D 6.19 93/03/23 07:48:39 eric 31 30
c prog mailer: preserve upper case; strip trailing dots in uucp
c mailer before converting to bang format; use relay mailer for $H
c (MAIL_HUB) and $R (LOCAL_RELAY) mail so that unqualified recipient
c addresses don't get the local hostname
e
s 00000/00000/00013
d D 6.18 93/03/18 11:49:17 eric 30 29
c fix typo in list syntax (;: => :;)
e
s 00000/00000/00013
d D 6.17 93/03/16 12:28:14 eric 29 28
c delete $<; add LOCAL_RULE_1 and LOCAL_RULE_2
e
s 00000/00000/00013
d D 6.16 93/03/06 09:59:25 eric 28 27
c FEATURE(notsticky) lets UDB get at even specific addresses
e
s 00000/00000/00013
d D 6.15 93/03/05 14:47:03 eric 27 26
c avoid having C flag qualify list:; and error <> syntax
e
s 00000/00000/00013
d D 6.14 93/03/05 07:37:15 eric 26 25
c GNU portability; treat user@ (no host) as user; don't put two domains
c on $=E in SMTP mailer
e
s 00000/00000/00013
d D 6.13 93/03/03 10:07:23 eric 25 24
c allow redefinition of sendmail.cw path; FlexFAX updates to match
c Sam's distribution
e
s 00000/00000/00013
d D 6.12 93/03/02 13:48:09 eric 24 23
c extensions for Sam Leffler's FlexFAX software
e
s 00000/00000/00013
d D 6.11 93/03/01 13:42:25 eric 23 22
c change error address convention to avoid conflict with C flag
e
s 00000/00000/00013
d D 6.10 93/02/27 12:02:45 eric 22 21
c FEATURE(nouucp)
e
s 00000/00000/00013
d D 6.9 93/02/24 09:13:22 eric 21 20
c catch null input to S3 as equivalent to <>
e
s 00000/00000/00013
d D 6.8 93/02/20 15:27:58 eric 20 19
c add FEATURE(redirect) and MAILER(usenet); add support for
c b and p flags; clean up M4 macro naming
e
s 00000/00000/00013
d D 6.7 93/02/19 16:30:12 eric 19 18
c add SMART_HOST support and ability to route to local net hosts
c and send remote traffic to UUCP (or other long haul transport agent)
e
s 00000/00000/00013
d D 6.6 93/02/16 20:14:19 eric 18 17
c fixes to bugs noted by Bruce Lilly for UUCP mailer
e
s 00000/00000/00013
d D 6.5 93/02/15 12:01:24 eric 17 16
c fix botches with confNO_WILDCARD_MX and confMATCH_GECOS
e
s 00001/00004/00012
d D 6.4 93/02/12 12:10:51 eric 16 15
c make everything configurable on M4 macros
e
s 00000/00000/00016
d D 6.3 93/01/20 13:16:02 eric 15 14
c use $k as UUCP node name instead of $U
e
s 00000/00000/00016
d D 6.2 93/01/13 16:38:51 eric 14 13
c allow definition of hub machine that gets *all* local traffic
e
s 00000/00000/00016
d D 6.1 92/12/21 16:08:18 eric 13 12
c Release 6
e
s 00000/00000/00016
d D 2.12 92/12/20 13:21:57 eric 12 11
c cleanup for new features and release engineering
e
s 00000/00000/00016
d D 2.11 92/12/07 16:41:19 eric 11 10
c handle multiple <> <> in S3
e
s 00001/00001/00015
d D 2.10 92/11/13 23:00:39 eric 10 9
c quote versionid to avoid # problems
e
s 00000/00000/00016
d D 2.9 92/11/13 21:50:29 eric 9 8
c make more portable to other versions of m4
e
s 00000/00000/00016
d D 2.8 92/07/20 08:00:26 eric 8 7
c readability changes
e
s 00000/00000/00016
d D 2.7 92/07/14 12:34:07 eric 7 6
c change handling of local mailer flags
e
s 00000/00000/00016
d D 2.6 92/02/24 16:15:19 eric 6 5
c new configuration version level control line
e
s 00000/00000/00016
d D 2.5 91/12/20 19:00:02 eric 5 4
c many hacks to get mail.cs working well
e
s 00000/00000/00016
d D 2.4 91/12/15 15:12:39 eric 4 3
c fix botch in MX forwarding rules on mail.cs and ucbvax
e
s 00000/00000/00016
d D 2.3 91/12/12 11:34:30 eric 3 2
c substantial changes to handle CS subdomain
e
s 00000/00000/00016
d D 2.2 91/10/02 18:38:52 eric 2 1
c make it work on 4.4bsd m4
e
s 00016/00000/00000
d D 2.1 91/10/02 14:48:11 eric 1 0
c date and time created 91/10/02 14:48:11 by eric
e
u
U
f b 
t
T
I 1
divert(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 49
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 49
I 49
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 49
#
# %sccs.include.redist.sh%
#
D 10
VERSIONID(%W% (Berkeley) %G%)
E 10
I 10
D 67
VERSIONID(`%W% (Berkeley) %G%')
E 67
I 67
VERSIONID(`%Z%%M%	8.7.Beta (Berkeley) %G%')
E 67
E 10
#
divert(0)
D 16
######################
#   Version Number   #
######################

E 16
I 16
# Configuration version number
E 16
D 48
DZ%I%
E 48
I 48
D 50
DZ8.1B
E 50
I 50
D 55
DZ%I%
E 55
I 55
D 67
DZ%R%.%L%.%B%
E 67
I 67
D 68
DZ8.7.Beta.0
E 68
I 68
D 69
DZ8.7.Beta.1
E 69
I 69
D 70
DZ8.7.Beta.2
E 70
I 70
D 71
DZ8.7.Beta.3`'ifdef(`confCF_VERSION', `/confCF_VERSION')
E 71
I 71
D 72
DZ8.7.Beta.5`'ifdef(`confCF_VERSION', `/confCF_VERSION')
E 72
I 72
D 73
DZ8.7.Beta.6`'ifdef(`confCF_VERSION', `/confCF_VERSION')
E 73
I 73
DZ8.7.Beta.7`'ifdef(`confCF_VERSION', `/confCF_VERSION')
E 73
E 72
E 71
E 70
E 69
E 68
E 67
E 55
E 50
E 48
E 1
