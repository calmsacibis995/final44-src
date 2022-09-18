h12459
s 00012/00008/00095
d D 8.22 95/04/26 09:25:11 eric 41 40
c add *_MAILER_CHARSET; UUCP_MAX_SIZE => UUCP_MAILER_MAX
e
s 00004/00004/00099
d D 8.21 95/04/23 14:01:14 eric 40 39
c update DNS type codes for new draft
e
s 00002/00002/00101
d D 8.20 95/04/10 07:54:18 eric 39 38
c strip off group:; syntax (needed to match new code behaviour)
e
s 00004/00004/00099
d D 8.19 94/11/27 15:15:18 eric 38 37
c add MTS type information
e
s 00010/00004/00093
d D 8.18 94/11/13 15:20:09 eric 37 36
c add smtp8 mailer and *_MAILER_ARGS parameters
e
s 00001/00002/00096
d D 8.17 94/08/07 13:42:03 eric 36 35
c avoid qualifying all UUCP addresses with $Y
e
s 00004/00006/00094
d D 8.16 94/07/02 08:16:20 eric 35 34
c delete OLD_SENDMAIL support
e
s 00003/00002/00097
d D 8.15 94/02/14 08:31:20 eric 34 33
c don't map $=w to $M if $M is undefined
e
s 00002/00002/00097
d D 8.14 94/01/24 12:06:56 eric 33 32
c allow localized specification of maximum message size
e
s 00013/00007/00086
d D 8.13 93/12/27 14:49:20 eric 32 31
c changes to try to improve UUCP rewriting
e
s 00004/00009/00089
d D 8.12 93/12/22 05:25:14 eric 31 30
c qualify unqualifed names in relay mailer
e
s 00004/00004/00094
d D 8.11 93/12/20 10:51:12 eric 30 29
c delete CSNET domain support; patch bug in relay rewriting
e
s 00004/00004/00094
d D 8.10 93/12/18 08:25:36 eric 29 28
c don't dot terminate .BITNET. when sending to bitnet relay -- the
c dot never gets stripped
e
s 00005/00005/00093
d D 8.9 93/11/30 09:01:23 eric 28 27
c add dot on pseudo-domains for consistency
e
s 00001/00001/00097
d D 8.8 93/11/20 07:53:12 eric 27 26
c relay mailer shouldn't rewrite recipients
e
s 00009/00008/00089
d D 8.7 93/10/31 11:38:08 eric 26 25
c renumber some rulesets to be consistent with numbering plan
e
s 00046/00021/00051
d D 8.6 93/10/23 17:23:22 eric 25 24
c adjust header addresses to match masquerade host even if pre-qualified
e
s 00004/00002/00068
d D 8.5 93/09/19 20:02:49 eric 24 23
c strip mailer: information off of $B and $C (BITNET and CSNET) relays
e
s 00003/00003/00067
d D 8.4 93/07/18 09:08:34 eric 23 22
c turn off `e' and `C' flags by default
e
s 00002/00002/00068
d D 8.3 93/07/11 11:54:50 eric 22 21
c fix M4 cruft with quote == apostrophe
e
s 00007/00004/00063
d D 8.2 93/07/11 08:17:53 eric 21 20
c many changes including: add LOCAL_MAILER_ARGS; FEATURE(allmasquerade);
c use $U as UUCP name instead of $k for masquerading; new "esmtp" mailer
e
s 00002/00002/00065
d D 8.1 93/06/07 10:11:27 bostic 20 19
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00003/00062
d D 6.10 93/05/06 14:44:41 eric 19 18
c _OLD_SENDMAIL_ compatibility
e
s 00005/00004/00060
d D 6.9 93/05/06 14:37:15 eric 18 17
c add SMTP_MAILER_FLAGS and UUCP_MAILER_FLAGS
e
s 00002/00000/00062
d D 6.8 93/03/23 07:46:48 eric 17 16
c add "relay" mailer that doesn't dicker with unqualified recipient
c addresses
e
s 00003/00003/00059
d D 6.7 93/03/05 14:47:30 eric 16 15
c avoid having C flag qualify list:; and error <> syntax
e
s 00001/00001/00061
d D 6.6 93/03/04 19:31:26 eric 15 14
c don't put two @host.domain on users in $=E
e
s 00001/00001/00061
d D 6.5 93/03/01 13:42:08 eric 14 13
c change error address convention to avoid conflict with C flag
e
s 00002/00001/00060
d D 6.4 93/02/27 12:02:16 eric 13 12
c hooks for FEATURE(nouucp) mode
e
s 00002/00002/00059
d D 6.3 93/02/21 12:39:54 eric 12 11
c changes to handle <> properly as an error address indicator
e
s 00002/00001/00059
d D 6.2 93/02/20 14:20:14 eric 11 9
c make M4 macro names more consistent
e
s 00000/00000/00060
d R 6.2 92/12/21 16:10:28 eric 10 9
c Release 6
e
s 00000/00000/00060
d D 6.1 92/12/21 16:10:18 eric 9 8
c Release 6
e
s 00001/00000/00059
d D 2.8 92/12/20 13:14:27 eric 8 7
c add $=E class for exposed names
e
s 00001/00001/00058
d D 2.7 92/11/13 22:56:11 eric 7 6
c quote versionid to avoid # problems
e
s 00006/00000/00053
d D 2.6 92/06/16 17:50:09 eric 6 5
c don't put local host name on list:; syntax
e
s 00001/00001/00052
d D 2.5 91/11/19 15:30:08 eric 5 4
c fix last delta: qualification of recipient names botched
e
s 00024/00008/00029
d D 2.4 91/11/13 15:41:18 eric 4 3
c don't masquerade recipient addresses, only sender addresses
e
s 00002/00002/00035
d D 2.3 91/10/03 01:15:26 eric 3 2
c use $j instead of $w so it can be fully qualified on ultrix
e
s 00007/00007/00030
d D 2.2 91/10/02 19:35:34 eric 2 1
c strip unnecessary quotes
e
s 00037/00000/00000
d D 2.1 91/10/02 14:48:26 eric 1 0
c date and time created 91/10/02 14:48:26 by eric
e
u
U
t
T
I 1
PUSHDIVERT(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 20
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 20
I 20
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 20
#
# %sccs.include.redist.sh%
#
I 18
D 19
ifdef(`SMTP_MAILER_FLAGS',, `define(`SMTP_MAILER_FLAGS', `')')
E 19
I 19
D 35
ifdef(`SMTP_MAILER_FLAGS',,
	`define(`SMTP_MAILER_FLAGS',
		`ifdef(`_OLD_SENDMAIL_', `L', `')')')
E 35
I 35
ifdef(`SMTP_MAILER_FLAGS',, `define(`SMTP_MAILER_FLAGS', `')')
I 37
ifdef(`SMTP_MAILER_ARGS',, `define(`SMTP_MAILER_ARGS', `IPC $h')')
ifdef(`ESMTP_MAILER_ARGS',, `define(`ESMTP_MAILER_ARGS', `IPC $h')')
ifdef(`SMTP8_MAILER_ARGS',, `define(`SMTP8_MAILER_ARGS', `IPC $h')')
ifdef(`RELAY_MAILER_ARGS',, `define(`RELAY_MAILER_ARGS', `IPC $h')')
E 37
E 35
E 19
E 18
POPDIVERT
#####################################
###   SMTP Mailer specification   ###
#####################################

D 7
VERSIONID(%W% (Berkeley) %G%)
E 7
I 7
VERSIONID(`%W% (Berkeley) %G%')
E 7

D 4
Msmtp,	P=[IPC], F=mDFMueXLC, S=11, R=11, A=IPC $h, E=\r\n
E 4
I 4
D 11
Msmtp,	P=[IPC], F=mDFMueXLC, S=11, R=21, A=IPC $h, E=\r\n
E 11
I 11
D 18
Msmtp,		P=[IPC], F=mDFMueXLC, S=11, R=21, E=\r\n,
		A=IPC $h
I 17
Mrelay,		P=[IPC], F=mDFMueXLC, S=11, R=19, E=\r\n,
		A=IPC $h
E 18
I 18
D 21
Msmtp,		P=[IPC], F=CONCAT(mDFMueXC, SMTP_MAILER_FLAGS), S=11, R=21, E=\r\n,
E 21
I 21
D 23
Msmtp,		P=[IPC], F=CONCAT(mDFMueXC, SMTP_MAILER_FLAGS), S=11, R=ifdef(`_ALL_MASQUERADE_', `11', `21'), E=\r\n,
E 23
I 23
D 25
Msmtp,		P=[IPC], F=CONCAT(mDFMuX, SMTP_MAILER_FLAGS), S=11, R=ifdef(`_ALL_MASQUERADE_', `11', `21'), E=\r\n,
E 25
I 25
D 38
Msmtp,		P=[IPC], F=CONCAT(mDFMuX, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n,
E 38
I 38
D 40
Msmtp,		P=[IPC], F=CONCAT(mDFMuX, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n, T=Internet,
E 40
I 40
D 41
Msmtp,		P=[IPC], F=CONCAT(mDFMuX, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n, T=DNS/RFC822/SMTP,
E 40
E 38
E 25
E 23
E 21
D 19
		L=990, A=IPC $h
E 19
I 19
D 33
		ifdef(`_OLD_SENDMAIL_',, `L=990, ')A=IPC $h
E 33
I 33
D 35
		ifdef(`_OLD_SENDMAIL_',, `L=990, ')ifdef(`SMTP_MAILER_MAX', `M=SMTP_MAILER_MAX, ')A=IPC $h
E 35
I 35
D 37
		L=990, ifdef(`SMTP_MAILER_MAX', `M=SMTP_MAILER_MAX, ')A=IPC $h
E 37
I 37
		L=990, ifdef(`SMTP_MAILER_MAX', `M=SMTP_MAILER_MAX, ')A=SMTP_MAILER_ARGS
E 37
E 35
E 33
E 19
D 21
Mrelay,		P=[IPC], F=CONCAT(mDFMueXC, SMTP_MAILER_FLAGS), S=11, R=19, E=\r\n,
E 21
I 21
D 23
Mesmtp,		P=[IPC], F=CONCAT(mDFMueXCa, SMTP_MAILER_FLAGS), S=11, R=ifdef(`_ALL_MASQUERADE_', `11', `21'), E=\r\n,
E 23
I 23
D 25
Mesmtp,		P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), S=11, R=ifdef(`_ALL_MASQUERADE_', `11', `21'), E=\r\n,
E 25
I 25
D 38
Mesmtp,		P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n,
E 38
I 38
D 40
Mesmtp,		P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n, T=Internet,
E 40
I 40
Mesmtp,		P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n, T=DNS/RFC822/SMTP,
E 40
E 38
E 25
E 23
D 33
		ifdef(`_OLD_SENDMAIL_',, `L=990, ')A=IPC $h
E 33
I 33
D 35
		ifdef(`_OLD_SENDMAIL_',, `L=990, ')ifdef(`SMTP_MAILER_MAX', `M=SMTP_MAILER_MAX, ')A=IPC $h
E 35
I 35
D 37
		L=990, ifdef(`SMTP_MAILER_MAX', `M=SMTP_MAILER_MAX, ')A=IPC $h
E 35
E 33
D 23
Mrelay,		P=[IPC], F=CONCAT(mDFMueXCa, SMTP_MAILER_FLAGS), S=11, R=19, E=\r\n,
E 23
I 23
D 25
Mrelay,		P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), S=11, R=19, E=\r\n,
E 25
I 25
D 26
Mrelay,		P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), S=11/31, R=19, E=\r\n,
E 26
I 26
D 27
Mrelay,		P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), S=11/31, R=51, E=\r\n,
E 27
I 27
D 31
Mrelay,		P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), S=11/31, R=0, E=\r\n,
E 31
I 31
Mrelay,		P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), S=11/31, R=61, E=\r\n,
E 31
E 27
E 26
E 25
E 23
E 21
D 19
		L=990, A=IPC $h
E 19
I 19
D 35
		ifdef(`_OLD_SENDMAIL_',, `L=2040, ')A=IPC $h
E 35
I 35
		L=2040, A=IPC $h
E 37
I 37
		L=990, ifdef(`SMTP_MAILER_MAX', `M=SMTP_MAILER_MAX, ')A=ESMTP_MAILER_ARGS
D 38
Msmtp8,		P=[IPC], F=CONCAT(mDFMuX8, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n,
E 38
I 38
D 40
Msmtp8,		P=[IPC], F=CONCAT(mDFMuX8, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n, T=Internet,
E 40
I 40
Msmtp8,		P=[IPC], F=CONCAT(mDFMuX8, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n, T=DNS/RFC822/SMTP,
E 40
E 38
		L=990, ifdef(`SMTP_MAILER_MAX', `M=SMTP_MAILER_MAX, ')A=SMTP8_MAILER_ARGS
D 38
Mrelay,		P=[IPC], F=CONCAT(mDFMuXa8, SMTP_MAILER_FLAGS), S=11/31, R=61, E=\r\n,
E 38
I 38
D 40
Mrelay,		P=[IPC], F=CONCAT(mDFMuXa8, SMTP_MAILER_FLAGS), S=11/31, R=61, E=\r\n, T=Internet,
E 40
I 40
Mrelay,		P=[IPC], F=CONCAT(mDFMuXa8, SMTP_MAILER_FLAGS), S=11/31, R=61, E=\r\n, T=DNS/RFC822/SMTP,
E 40
E 38
		L=2040, A=RELAY_MAILER_ARGS
E 41
I 41
Msmtp,		P=[IPC], F=CONCAT(mDFMuX, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n, L=990,
		_OPTINS(`SMTP_MAILER_MAX', `M=', `, ')_OPTINS(`SMTP_MAILER_CHARSET', `C=', `, ')T=DNS/RFC822/SMTP,
		A=SMTP_MAILER_ARGS
Mesmtp,		P=[IPC], F=CONCAT(mDFMuXa, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n, L=990,
		_OPTINS(`SMTP_MAILER_MAX', `M=', `, ')_OPTINS(`SMTP_MAILER_CHARSET', `C=', `, ')T=DNS/RFC822/SMTP,
		A=ESMTP_MAILER_ARGS
Msmtp8,		P=[IPC], F=CONCAT(mDFMuX8, SMTP_MAILER_FLAGS), S=11/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), E=\r\n, L=990,
		_OPTINS(`SMTP_MAILER_MAX', `M=', `, ')_OPTINS(`SMTP_MAILER_CHARSET', `C=', `, ')T=DNS/RFC822/SMTP,
		A=SMTP8_MAILER_ARGS
Mrelay,		P=[IPC], F=CONCAT(mDFMuXa8, SMTP_MAILER_FLAGS), S=11/31, R=61, E=\r\n, L=2040,
		_OPTINS(`RELAY_MAILER_CHARSET', `C=', `, ')T=DNS/RFC822/SMTP,
		A=RELAY_MAILER_ARGS
E 41
E 37
E 35
E 19
E 18
E 17
E 11
E 4

I 25
#
#  envelope sender and masquerading recipient rewriting
#
E 25
S11
I 25
D 26
R$+			$: $>19 $1			sender/recipient common
E 26
I 26
R$+			$: $>51 $1			sender/recipient common
E 26
D 39
R$* :; <@>		$@ $1 :;			list:; special case
E 39
I 39
R$* :; <@>		$@				list:; special case
E 39
I 31
R$*			$@ $>61 $1			qualify unqual'ed names
E 31
E 25

I 4
D 25
# do sender/recipient common rewriting
R$+			$: $>19 $1

# if already @ qualified, we are done
E 25
I 25
D 31
# handle unqualified names
E 25
D 12
R$* < @ $+ > $*		$@ $1 < @ $2 > $3		already qualified
E 12
I 12
R$* < @ $* > $*		$@ $1 < @ $2 > $3		already qualified
I 25
D 26
R$*			$@ $>29 $1
E 26
I 26
R$*			$@ $>61 $1
E 31
E 26
E 25
E 12

I 6
D 22
# don't qualify list:; syntax
E 22
I 22
D 25
# do not qualify list:; syntax
E 22
D 16
R$* :;			$@ $1 :;
E 16
I 16
R$* :; <@>		$@ $1 :;
E 25
E 16
D 31

E 31
E 6
D 25
# unqualified names (e.g., "eric") "come from" $M
I 8
D 15
R$=E			$: $1 < @ $j>			show exposed names
E 15
I 15
R$=E			$@ $1 < @ $j>			show exposed names
E 15
E 8
R$+			$: $1 < @ $M >			user w/o host
D 14
R$+ < @ >		$: $1 < @ $j >			in case $M undefined
E 14
I 14
D 16
R$+ <>			$: $1 < @ $j >			in case $M undefined
E 16
I 16
R$+ <@>			$: $1 < @ $j >			in case $M undefined
E 25
I 25
#
#  header recipient rewriting if not masquerading recipients
#
S21
E 25
E 16
E 14

D 21
S21
E 21
I 21
D 25
ifdef(`_ALL_MASQUERADE_', `dnl',
`S21
E 21

E 25
# do sender/recipient common rewriting
D 26
R$+			$: $>19 $1
E 26
I 26
R$+			$: $>51 $1
E 26

D 25
# if already @ qualified, we are done
E 25
I 25
# unqualified names (e.g., "eric") are qualified by local host
E 25
D 12
R$* < @ $+ > $*		$@ $1 < @ $2 > $3		already qualified
E 12
I 12
R$* < @ $* > $*		$@ $1 < @ $2 > $3		already qualified
I 25
R$+			$: $1 < @ $j >			add local domain
E 25
E 12
I 6

D 22
# don't qualify list:; syntax
E 22
I 22
D 25
# do not qualify list:; syntax
E 22
D 16
R$* :;			$@ $1 :;
E 16
I 16
R$* :; <@>		$@ $1 :;
E 25
E 16
E 6

D 25
# unqualified names (e.g., "eric") are qualified by local host
D 5
R$+ < @ >		$: $1 < @ $j >
E 5
I 5
D 21
R$+			$: $1 < @ $j >
E 21
I 21
R$+			$: $1 < @ $j >')
E 25
I 25
#
#  header sender and masquerading recipient rewriting
#
S31
D 26
R$+			$: $>19 $1			sender/recipient common
E 26
I 26
R$+			$: $>51 $1			sender/recipient common
E 26
D 39
R$* :; <@>		$@ $1 :;			list:; special case
E 39
I 39
R:; <@>			$@				list:; special case
E 39
E 25
E 21
E 5

I 25
# do special header rewriting
R$* <@> $*		$@ $1 <@> $2			pass null host through
R< @ $* > $*		$@ < @ $1 > $2			pass route-addr through
R$=E < @ $=w . >	$@ $1 < @ $2 >			exposed user as is
D 34
R$* < @ $=w . >		$: $1 < @ $M >			masquerade as domain
R$* < @ >		$: $1 < @ $j >			in case $M undefined
E 34
I 34
R$* < @ $=w . >		$: $1 < @ $2 @ $M >		masquerade as domain
R$* < @ $+ @ >		$@ $1 < @ $2 >			in case $M undefined
R$* < @ $+ @ $+ >	$@ $1 < @ $3 >			$M is defined -- use it
E 34
I 31
R$*			$@ $>61 $1			qualify unqual'ed names
E 31

D 31
# handle unqualified names
R$* < @ $* > $*		$@ $1 < @ $2 > $3		already qualified
D 26
R$*			$@ $>29 $1
E 26
I 26
R$*			$@ $>61 $1
E 31
E 26

D 31

E 31
#
D 32
#  common rewriting for all SMTP addresses
E 32
I 32
#  convert pseudo-domain addresses to real domain addresses
E 32
#
E 25
D 26
S19
E 26
I 26
S51
E 26

E 4
# pass <route-addr>s through
D 2
`R< @ $+ > $*		$@ < @ $1 > $2			resolve <route-addr>'
E 2
I 2
R< @ $+ > $*		$@ < @ $1 > $2			resolve <route-addr>
E 2

# output fake domains as user%fake@relay
ifdef(`BITNET_RELAY',
D 2
``R$+ <@ $+ . BITNET >	$: $1 % $2 .BITNET < @ $B >	user@host.BITNET'',
E 2
I 2
D 24
`R$+ <@ $+ . BITNET >	$: $1 % $2 .BITNET < @ $B >	user@host.BITNET',
E 24
I 24
D 28
`R$+ <@ $+ . BITNET >	$: $1 % $2 .BITNET < @ $B >	user@host.BITNET
R$+.BITNET <@ $+:$+ >	$: $1 .BITNET < @ $3 >		strip mailer: part',
E 28
I 28
D 29
`R$+ <@ $+ .BITNET. >	$: $1 % $2 .BITNET. < @ $B >	user@host.BITNET
R$+.BITNET. <@ $+:$+ >	$: $1 .BITNET. < @ $3 >		strip mailer: part',
E 29
I 29
`R$+ <@ $+ .BITNET. >	$: $1 % $2 .BITNET < @ $B >	user@host.BITNET
D 30
R$+.BITNET. <@ $+:$+ >	$: $1 .BITNET < @ $3 >		strip mailer: part',
E 30
I 30
R$+.BITNET <@ $+:$+ >	$: $1 .BITNET < @ $3 >		strip mailer: part',
E 30
E 29
E 28
E 24
E 2
	`dnl')
D 30
ifdef(`CSNET_RELAY',
D 2
``R$+ <@ $+ . CSNET >	$: $1 % $2 .CSNET < @ $C >	user@host.CSNET'',
E 2
I 2
D 24
`R$+ <@ $+ . CSNET >	$: $1 % $2 .CSNET < @ $C >	user@host.CSNET',
E 24
I 24
D 28
`R$+ <@ $+ . CSNET >	$: $1 % $2 .CSNET < @ $C >	user@host.CSNET
R$+.CSNET <@ $+:$+ >	$: $1 .CSNET < @ $3 >		strip mailer: part',
E 28
I 28
D 29
`R$+ <@ $+ .CSNET. >	$: $1 % $2 .CSNET. < @ $C >	user@host.CSNET
R$+.CSNET. <@ $+:$+ >	$: $1 .CSNET. < @ $3 >		strip mailer: part',
E 29
I 29
`R$+ <@ $+ .CSNET. >	$: $1 % $2 .CSNET < @ $C >	user@host.CSNET
R$+.CSNET. <@ $+:$+ >	$: $1 .CSNET < @ $3 >		strip mailer: part',
E 30
I 30
D 32
ifdef(`UUCP_RELAY',
`R$+ <@ $+ .UUCP. >	$: $1 % $2 .UUCP < @ $Y >	user@host.UUCP
R$+.UUCP <@ $+:$+ >	$: $1 .UUCP < @ $3 >		strip mailer: part',
E 30
E 29
E 28
E 24
E 2
	`dnl')
D 2
`R$+ <@ $+ . UUCP >	$: $2 ! $1 < @ $w >		user@host.UUCP'
E 2
I 2
D 3
R$+ <@ $+ . UUCP >	$: $2 ! $1 < @ $w >		user@host.UUCP
E 3
I 3
D 13
R$+ <@ $+ . UUCP >	$: $2 ! $1 < @ $j >		user@host.UUCP
E 13
I 13
ifdef(`_NO_UUCP_', `dnl',
D 28
`R$+ <@ $+ . UUCP >	$: $2 ! $1 < @ $j >		user@host.UUCP')
E 28
I 28
`R$+ <@ $+ .UUCP. >	$: $2 ! $1 < @ $j >		user@host.UUCP')
E 32
I 32
ifdef(`_NO_UUCP_', `dnl', `
# do UUCP heuristics; note that these are shared with UUCP mailers
R$+ < @ $+ .UUCP. >	$: < $2 ! > $1			convert to UUCP form
R$+ < @ $* > $*		$@ $1 < @ $2 > $3		not UUCP form

# leave these in .UUCP form to avoid further tampering
R< $&h ! > $- ! $+	$@ $2 < @ $1 .UUCP. >
R< $&h ! > $-.$+ ! $+	$@ $3 < @ $1.$2 >
R< $&h ! > $+		$@ $1 < @ $&h .UUCP. >
D 36
R< $+ ! > $+		$: $1 ! $2 < @ $Y >
R$+ < @ >		$: $1 < @ $j >			in case $Y undefined
E 36
I 36
R< $+ ! > $+		$: $1 ! $2 < @ $j >
E 36
R$+ < @ $+ : $+ >	$: $1 < @ $3 >			strip mailer: part')
E 32
E 28
I 25


#
#  common sender and masquerading recipient rewriting
#
D 26
S29
E 26
I 26
S61

I 31
R$* < @ $* > $*		$@ $1 < @ $2 > $3		already qualified
E 31
E 26
R$=E			$@ $1 < @ $j>			show exposed names
R$+			$: $1 < @ $M >			user w/o host
R$+ <@>			$: $1 < @ $j >			in case $M undefined
E 25
E 13
E 3
E 2
D 4

# if already @ qualified, we are done
D 2
`R$+ < @ $+ >		$@ $1 < @ $2 >			already qualified'
E 2
I 2
R$+ < @ $+ >		$@ $1 < @ $2 >			already qualified
E 2

# unqualified names (e.g., "eric") "come from" $M
D 2
`R$+			$: $1 < @ $M >			user w/o host'
`R$+ < @ >		$: $1 < @ $w >			in case $M undefined'
E 2
I 2
R$+			$: $1 < @ $M >			user w/o host
D 3
R$+ < @ >		$: $1 < @ $w >			in case $M undefined
E 3
I 3
R$+ < @ >		$: $1 < @ $j >			in case $M undefined
E 4
E 3
E 2
E 1
