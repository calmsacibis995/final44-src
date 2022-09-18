h36622
s 00015/00007/00139
d D 8.22 95/04/26 09:25:12 eric 42 41
c add *_MAILER_CHARSET; UUCP_MAX_SIZE => UUCP_MAILER_MAX
e
s 00006/00006/00140
d D 8.21 95/04/23 13:52:05 eric 41 40
c update DSN types to be more realistic
e
s 00008/00008/00138
d D 8.20 95/04/10 07:54:19 eric 40 39
c strip off group:; syntax (needed to match new code behaviour)
e
s 00006/00006/00140
d D 8.19 94/12/11 14:01:24 eric 39 38
c specify the F=d (don't use brackets on envelope route-addrs) flag
e
s 00001/00001/00145
d D 8.18 94/12/06 09:44:31 eric 38 37
c use $g instead of $f for -a argument to get around bug in Taylor UUCP
e
s 00006/00006/00140
d D 8.17 94/11/27 15:15:19 eric 37 36
c add MTS type information
e
s 00020/00005/00126
d D 8.16 94/04/14 16:03:18 eric 36 35
c don't let envelope recipients ever get $U! or $k! prepended;
c this causes loops
e
s 00001/00001/00130
d D 8.15 94/02/16 07:58:06 eric 35 34
c fix typo in $=Z matching
e
s 00001/00001/00130
d D 8.14 94/02/10 09:03:52 eric 34 33
c reverse sense of uux -z flag
e
s 00006/00006/00125
d D 8.13 94/01/10 08:01:10 eric 33 32
c botch with trailing dots
e
s 00011/00007/00120
d D 8.12 94/01/07 09:09:08 eric 32 31
c use full domain name in UUCP mailer for consistency with mailertable
e
s 00020/00005/00107
d D 8.11 93/12/27 14:49:21 eric 31 30
c changes to try to improve UUCP rewriting
e
s 00005/00003/00107
d D 8.10 93/12/20 10:51:30 eric 30 29
c make uucp-uudom not add unnecessary domains
e
s 00031/00007/00079
d D 8.9 93/12/10 23:30:50 eric 29 28
c add uucp-uudom mailer; provide aliases for suucp & uucp mailers
e
s 00007/00007/00079
d D 8.8 93/11/30 09:01:24 eric 28 27
c add dot on pseudo-domains for consistency
e
s 00001/00001/00085
d D 8.7 93/11/20 07:52:48 eric 27 26
c fix typo in list syntax handling
e
s 00020/00003/00066
d D 8.6 93/10/31 11:38:35 eric 26 25
c avoid null return path passed to uux -- it doesn't grok it
e
s 00003/00001/00066
d D 8.5 93/07/28 10:23:45 eric 25 24
c add $=Z class for UUCP hosts directed to uucp-dom mailer
e
s 00011/00002/00056
d D 8.4 93/07/13 13:00:28 eric 24 23
c add uucp-dom mailer, OSTYPE(aix3), LOCAL_SHELL_{FLAGS,ARGS}, UUCP_MAX_SIZE
e
s 00001/00001/00057
d D 8.3 93/07/11 11:54:51 eric 23 22
c fix M4 cruft with quote == apostrophe
e
s 00004/00003/00054
d D 8.2 93/07/11 08:17:54 eric 22 21
c many changes including: add LOCAL_MAILER_ARGS; FEATURE(allmasquerade);
c use $U as UUCP name instead of $k for masquerading; new "esmtp" mailer
e
s 00002/00002/00055
d D 8.1 93/06/07 10:11:35 bostic 21 20
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00003/00002/00054
d D 6.12 93/05/06 14:37:16 eric 20 19
c add SMTP_MAILER_FLAGS and UUCP_MAILER_FLAGS
e
s 00002/00002/00054
d D 6.11 93/05/01 08:25:17 eric 19 18
c fix route-addr syntax
e
s 00002/00002/00054
d D 6.10 93/03/24 07:09:52 eric 18 17
c fix botch in dot stripping line
e
s 00004/00002/00052
d D 6.9 93/03/21 08:56:04 eric 17 16
c strip trailing dots off addresses before converting to UUCP format
e
s 00003/00003/00051
d D 6.8 93/03/05 14:47:31 eric 16 15
c avoid having C flag qualify list:; and error <> syntax
e
s 00001/00001/00053
d D 6.7 93/03/01 13:42:08 eric 15 14
c change error address convention to avoid conflict with C flag
e
s 00002/00002/00052
d D 6.6 93/02/28 19:38:48 eric 14 13
c add commas after M= arg
e
s 00003/00000/00051
d D 6.5 93/02/21 12:39:55 eric 13 12
c changes to handle <> properly as an error address indicator
e
s 00006/00004/00045
d D 6.4 93/02/20 14:20:15 eric 12 11
c make M4 macro names more consistent
e
s 00014/00003/00035
d D 6.3 93/02/16 20:14:32 eric 11 10
c fixes to bugs noted by Bruce Lilly for UUCP mailer
e
s 00001/00001/00037
d D 6.2 93/01/20 13:15:47 eric 10 9
c use $k as UUCP node name instead of $U
e
s 00000/00000/00038
d D 6.1 92/12/21 16:10:19 eric 9 8
c Release 6
e
s 00001/00001/00037
d D 2.8 92/11/13 22:56:12 eric 8 7
c quote versionid to avoid # problems
e
s 00000/00002/00038
d D 2.7 92/07/20 08:00:59 eric 7 6
c don't need _UUCP_LINKED_ -- use _MAILER_uucp_ instead
e
s 00003/00000/00037
d D 2.6 92/06/16 17:50:11 eric 6 5
c don't put local host name on list:; syntax
e
s 00001/00001/00036
d D 2.5 91/10/03 01:16:07 eric 5 4
c use $j instead of $w so it can be fully qualified
e
s 00003/00003/00034
d D 2.4 91/10/03 00:39:44 eric 4 3
c adjust UUCP macro naming
e
s 00010/00001/00027
d D 2.3 91/10/02 21:19:02 eric 3 2
c hacks for ucbvax
e
s 00004/00004/00024
d D 2.2 91/10/02 19:35:34 eric 2 1
c strip unnecessary quotes
e
s 00028/00000/00000
d D 2.1 91/10/02 14:48:27 eric 1 0
c date and time created 91/10/02 14:48:27 by eric
e
u
U
t
T
I 1
PUSHDIVERT(-1)
#
# Copyright (c) 1983 Eric P. Allman
D 21
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 21
I 21
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 21
#
# %sccs.include.redist.sh%
#
I 12

ifdef(`UUCP_MAILER_PATH',, `define(`UUCP_MAILER_PATH', /usr/bin/uux)')
I 22
D 34
ifdef(`UUCP_MAILER_ARGS',, `define(`UUCP_MAILER_ARGS', `uux - -r -z -a$f -gC $h!rmail ($u)')')
E 34
I 34
D 38
ifdef(`UUCP_MAILER_ARGS',, `define(`UUCP_MAILER_ARGS', `uux - -r -a$f -gC $h!rmail ($u)')')
E 38
I 38
ifdef(`UUCP_MAILER_ARGS',, `define(`UUCP_MAILER_ARGS', `uux - -r -a$g -gC $h!rmail ($u)')')
E 38
E 34
E 22
I 20
ifdef(`UUCP_MAILER_FLAGS',, `define(`UUCP_MAILER_FLAGS', `')')
I 24
D 42
ifdef(`UUCP_MAX_SIZE',, `define(`UUCP_MAX_SIZE', 100000)')
E 42
I 42
ifdef(`UUCP_MAILER_MAX',,
	`define(`UUCP_MAILER_MAX',
		`ifdef(`UUCP_MAX_SIZE', `UUCP_MAX_SIZE', 100000)')')
E 42
E 24
E 20
E 12
POPDIVERT
#####################################
###   UUCP Mailer specification   ###
#####################################

D 8
VERSIONID(%W% (Berkeley) %G%)
E 8
I 8
VERSIONID(`%W% (Berkeley) %G%')
E 8

D 11
Msuucp,	P=ifdef(`UUCP_MAILER', `UUCP_MAILER', /usr/bin/uux), F=mDFMhuU, S=12, R=12, M=100000
E 11
I 11
D 12
Msuucp,	P=ifdef(`UUCP_MAILER', `UUCP_MAILER', /usr/bin/uux), F=mDFMhuU, S=12, R=22, M=100000
E 11
	A=uux - -r -z -a$f -gC $h!rmail ($u)
E 12
I 12
D 14
Msuucp,		P=UUCP_MAILER_PATH, F=mDFMhuU, S=12, R=22, M=100000
E 14
I 14
D 20
Msuucp,		P=UUCP_MAILER_PATH, F=mDFMhuU, S=12, R=22, M=100000,
E 20
I 20
D 24
Msuucp,		P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuU, UUCP_MAILER_FLAGS), S=12, R=22, M=100000,
E 24
I 24
D 29
# old UUCP mailer
E 29
I 29
#
#  There are innumerable variations on the UUCP mailer.  It really
#  is rather absurd.
#

# old UUCP mailer (two names)
E 29
D 36
Muucp,		P=UUCP_MAILER_PATH, F=CONCAT(DFMhuU, UUCP_MAILER_FLAGS), S=12, R=22, M=UUCP_MAX_SIZE,
E 36
I 36
D 37
Muucp,		P=UUCP_MAILER_PATH, F=CONCAT(DFMhuU, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE,
E 37
I 37
D 39
Muucp,		P=UUCP_MAILER_PATH, F=CONCAT(DFMhuU, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP,
E 39
I 39
D 41
Muucp,		P=UUCP_MAILER_PATH, F=CONCAT(DFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP,
E 41
I 41
D 42
Muucp,		P=UUCP_MAILER_PATH, F=CONCAT(DFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP/X-UUCP/X-Unix,
E 42
I 42
Muucp,		P=UUCP_MAILER_PATH, F=CONCAT(DFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAILER_MAX,
		_OPTINS(`UUCP_MAILER_CHARSET', `C=', `, ')T=X-UUCP/X-UUCP/X-Unix,
E 42
E 41
E 39
E 37
E 36
E 24
E 20
E 14
D 22
		A=uux - -r -z -a$f -gC $h!rmail ($u)
E 22
I 22
		A=UUCP_MAILER_ARGS
I 29
D 36
Muucp-old,	P=UUCP_MAILER_PATH, F=CONCAT(DFMhuU, UUCP_MAILER_FLAGS), S=12, R=22, M=UUCP_MAX_SIZE,
E 36
I 36
D 37
Muucp-old,	P=UUCP_MAILER_PATH, F=CONCAT(DFMhuU, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE,
E 37
I 37
D 39
Muucp-old,	P=UUCP_MAILER_PATH, F=CONCAT(DFMhuU, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP,
E 39
I 39
D 41
Muucp-old,	P=UUCP_MAILER_PATH, F=CONCAT(DFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP,
E 41
I 41
D 42
Muucp-old,	P=UUCP_MAILER_PATH, F=CONCAT(DFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP/X-UUCP/X-Unix,
E 42
I 42
Muucp-old,	P=UUCP_MAILER_PATH, F=CONCAT(DFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAILER_MAX,
		_OPTINS(`UUCP_MAILER_CHARSET', `C=', `, ')T=X-UUCP/X-UUCP/X-Unix,
E 42
E 41
E 39
E 37
E 36
		A=UUCP_MAILER_ARGS
E 29
E 22
E 12

D 11
Muucp,	P=ifdef(`UUCP_MAILER', `UUCP_MAILER', /usr/bin/uux), F=DFMhuU, S=12, R=12, M=100000
E 11
I 11
D 12
Muucp,	P=ifdef(`UUCP_MAILER', `UUCP_MAILER', /usr/bin/uux), F=DFMhuU, S=12, R=22, M=100000
E 11
	A=uux - -r -z -a$f -gC $h!rmail ($u)
E 12
I 12
D 14
Muucp,		P=UUCP_MAILER_PATH, F=DFMhuU, S=12, R=22, M=100000
E 14
I 14
D 20
Muucp,		P=UUCP_MAILER_PATH, F=DFMhuU, S=12, R=22, M=100000,
E 20
I 20
D 24
Muucp,		P=UUCP_MAILER_PATH, F=CONCAT(DFMhuU, UUCP_MAILER_FLAGS), S=12, R=22, M=100000,
E 24
I 24
D 29
# smart UUCP mailer (handles multiple addresses)
E 29
I 29
# smart UUCP mailer (handles multiple addresses) (two names)
E 29
D 36
Msuucp,		P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuU, UUCP_MAILER_FLAGS), S=12, R=22, M=UUCP_MAX_SIZE,
E 36
I 36
D 37
Msuucp,		P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuU, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE,
E 37
I 37
D 39
Msuucp,		P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuU, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP,
E 39
I 39
D 41
Msuucp,		P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP,
E 41
I 41
D 42
Msuucp,		P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP/X-UUCP/X-Unix,
E 42
I 42
Msuucp,		P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAILER_MAX,
		_OPTINS(`UUCP_MAILER_CHARSET', `C=', `, ')T=X-UUCP/X-UUCP/X-Unix,
E 42
E 41
E 39
E 37
E 36
E 24
E 20
E 14
D 22
		A=uux - -r -z -a$f -gC $h!rmail ($u)
E 22
I 22
		A=UUCP_MAILER_ARGS
I 29
D 36
Muucp-new,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuU, UUCP_MAILER_FLAGS), S=12, R=22, M=UUCP_MAX_SIZE,
E 36
I 36
D 37
Muucp-new,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuU, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE,
E 37
I 37
D 39
Muucp-new,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuU, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP,
E 39
I 39
D 41
Muucp-new,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP,
E 41
I 41
D 42
Muucp-new,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAX_SIZE, T=X-UUCP/X-UUCP/X-Unix,
E 42
I 42
Muucp-new,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhuUd, UUCP_MAILER_FLAGS), S=12, R=22/42, M=UUCP_MAILER_MAX,
		_OPTINS(`UUCP_MAILER_CHARSET', `C=', `, ')T=X-UUCP/X-UUCP/X-Unix,
E 42
E 41
E 39
E 37
E 36
		A=UUCP_MAILER_ARGS
E 29
I 24

ifdef(`_MAILER_smtp_',
`# domain-ized UUCP mailer
D 26
Muucp-dom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhu, UUCP_MAILER_FLAGS), S=11, R=21, M=UUCP_MAX_SIZE,
E 26
I 26
D 37
Muucp-dom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhu, UUCP_MAILER_FLAGS), S=52/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), M=UUCP_MAX_SIZE,
E 37
I 37
D 39
Muucp-dom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhu, UUCP_MAILER_FLAGS), S=52/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), M=UUCP_MAX_SIZE, T=X-UUCP,
E 39
I 39
D 41
Muucp-dom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhud, UUCP_MAILER_FLAGS), S=52/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), M=UUCP_MAX_SIZE, T=X-UUCP,
E 41
I 41
D 42
Muucp-dom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhud, UUCP_MAILER_FLAGS), S=52/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), M=UUCP_MAX_SIZE, T=X-UUCP/X-UUCP/X-Unix,
E 42
I 42
Muucp-dom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhud, UUCP_MAILER_FLAGS), S=52/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), M=UUCP_MAILER_MAX,
		_OPTINS(`UUCP_MAILER_CHARSET', `C=', `, ')T=X-UUCP/X-UUCP/X-Unix,
E 42
E 41
E 39
E 37
I 29
		A=UUCP_MAILER_ARGS

# domain-ized UUCP mailer with UUCP-style sender envelope
D 37
Muucp-uudom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhu, UUCP_MAILER_FLAGS), S=72/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), M=UUCP_MAX_SIZE,
E 37
I 37
D 39
Muucp-uudom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhu, UUCP_MAILER_FLAGS), S=72/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), M=UUCP_MAX_SIZE, T=X-UUCP,
E 39
I 39
D 41
Muucp-uudom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhud, UUCP_MAILER_FLAGS), S=72/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), M=UUCP_MAX_SIZE, T=X-UUCP,
E 41
I 41
D 42
Muucp-uudom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhud, UUCP_MAILER_FLAGS), S=72/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), M=UUCP_MAX_SIZE, T=X-UUCP/X-UUCP/X-Unix,
E 42
I 42
Muucp-uudom,	P=UUCP_MAILER_PATH, F=CONCAT(mDFMhud, UUCP_MAILER_FLAGS), S=72/31, R=ifdef(`_ALL_MASQUERADE_', `11/31', `21'), M=UUCP_MAILER_MAX,
		_OPTINS(`UUCP_MAILER_CHARSET', `C=', `, ')T=X-UUCP/X-UUCP/X-Unix,
E 42
E 41
E 39
E 37
E 29
E 26
		A=UUCP_MAILER_ARGS')

E 24
E 22
E 12

I 11
D 26
# sender rewriting
E 26
I 26
#
#  envelope and header sender rewriting
#
E 26
E 11
I 3
D 7
define(`_UUCP_LINKED_')dnl
E 3

E 7
S12

I 13
# handle error address as a special case
D 15
R<@>				$n			errors to mailer-daemon
E 15
I 15
D 16
R<>				$n			errors to mailer-daemon
E 16
I 16
R<@>				$n			errors to mailer-daemon
E 16
E 15

E 13
I 6
D 23
# don't qualify list:; syntax
E 23
I 23
D 40
# do not qualify list:; syntax
E 23
D 16
R$* :;				$@ $1 :;
E 16
I 16
R$* :; <@>			$@ $1 :;
E 40
I 40
# list:; syntax should disappear
R:; <@>				$@
E 40
E 16

E 6
D 2
`R$* < @ $w >			$1			strip local name'
`R$* < @ $- . UUCP >		$2 ! $1			convert to UUCP format'
`R$* < @ $+ >			$2 ! $1			convert to UUCP format'
`R$+				$: $U ! $1		prepend our name'
E 2
I 2
D 5
R$* < @ $w >			$1			strip local name
E 5
I 5
D 11
R$* < @ $j >			$1			strip local name
E 11
I 11
D 17
R$* < @ $j. >			$1			strip local name
E 17
I 17
D 18
R** < @ $* . >			$1 < @ $2 >		strip trailing dots
E 18
I 18
R$* < @ $* . >			$1 < @ $2 >		strip trailing dots
E 18
D 28
R$* < @ $j >			$1			strip local name
E 28
I 28
R$* < @ $=w >			$1			strip local name
E 28
E 17
E 11
E 5
D 32
R$* < @ $- . UUCP >		$2 ! $1			convert to UUCP format
E 32
I 32
D 33
R<@ $- . UUCP. > : $+		$1 ! $2			convert to UUCP format
E 33
I 33
R<@ $- . UUCP > : $+		$1 ! $2			convert to UUCP format
E 33
R<@ $+ > : $+			$1 ! $2			convert to UUCP format
D 33
R$* < @ $- . UUCP. >		$2 ! $1			convert to UUCP format
E 33
I 33
R$* < @ $- . UUCP >		$2 ! $1			convert to UUCP format
E 33
E 32
R$* < @ $+ >			$2 ! $1			convert to UUCP format
I 31
R$&h ! $+ ! $+			$@ $1 ! $2		$h!...!user => ...!user
R$&h ! $+			$@ $&h ! $1		$h!user => $h!user
E 31
D 3
R$+				$: $U ! $1		prepend our name
E 3
I 3
D 4
R$+				$: $V ! $1		prepend our name
E 4
I 4
D 10
R$+				$: $U ! $1		prepend our name
E 10
I 10
D 22
R$+				$: $k ! $1		prepend our name
E 22
I 22
R$+				$: $U ! $1		prepend our name
I 30
R! $+				$: $k ! $1		in case $U undefined
E 30
E 22
I 11

D 26
# recipient rewriting
E 26
I 26
#
D 36
#  envelope and header recipient rewriting
E 36
I 36
#  envelope recipient rewriting
E 36
#
E 26
S22
I 36

D 40
# don't touch list:; syntax
R$* :; <@>			$@ $1 :;
E 40
I 40
# list:; should disappear
R:; <@>				$@
E 40

R$* < @ $* . >			$1 < @ $2 >		strip trailing dots
R$* < @ $j >			$1			strip local name
R<@ $- . UUCP > : $+		$1 ! $2			convert to UUCP format
R<@ $+ > : $+			$1 ! $2			convert to UUCP format
R$* < @ $- . UUCP >		$2 ! $1			convert to UUCP format
R$* < @ $+ >			$2 ! $1			convert to UUCP format

#
#  header recipient rewriting
#
S42
E 36

D 40
# don't touch list:; syntax
D 16
R$* :;				$@ $1 ;:
E 16
I 16
D 27
R$* :; <@>			$@ $1 ;:
E 27
I 27
R$* :; <@>			$@ $1 :;
E 40
I 40
# list:; syntax should disappear
R:; <@>				$@
E 40
E 27
E 16

D 17
R$* < @ $j. >			$1			strip local name
E 17
I 17
D 18
R** < @ $* . >			$1 < @ $2 >		strip trailing dots
E 18
I 18
R$* < @ $* . >			$1 < @ $2 >		strip trailing dots
E 18
R$* < @ $j >			$1			strip local name
E 17
D 32
R$* < @ $- . UUCP >		$2 ! $1			convert to UUCP format
E 32
I 32
D 33
R<@ $- . UUCP. > : $+		$1 ! $2			convert to UUCP format
E 33
I 33
R<@ $- . UUCP > : $+		$1 ! $2			convert to UUCP format
E 33
R<@ $+ > : $+			$1 ! $2			convert to UUCP format
D 33
R$* < @ $- . UUCP. >		$2 ! $1			convert to UUCP format
E 33
I 33
R$* < @ $- . UUCP >		$2 ! $1			convert to UUCP format
E 33
E 32
R$* < @ $+ >			$2 ! $1			convert to UUCP format
I 31
R$&h ! $+ ! $+			$@ $1 ! $2		$h!...!user => ...!user
R$&h ! $+			$@ $&h ! $1		$h!user => $h!user
R$+				$: $U ! $1		prepend our name
R! $+				$: $k ! $1		in case $U undefined
E 31
I 26


D 29
#
E 29
I 29
ifdef(`_MAILER_smtp_',
`#
E 29
#  envelope sender rewriting for uucp-dom mailer
#
S52

# handle error address as a special case
R<@>				$n			errors to mailer-daemon

# pass everything to standard SMTP mailer rewriting
R$*				$@ $>11 $1

I 29
#
#  envelope sender rewriting for uucp-uudom mailer
#
S72
E 29
E 26
E 11
E 10
E 4

I 29
D 31
R$+				$: $>12 $1		uucp-ify
D 30
R $=w ! $+			$2			prepare for following
R $+				$: $M ! $1		prepend masquerade name
R ! $+				$: $j ! $1		in case $M undefined')
E 30
I 30
R$=w ! $+			$2			prepare for following
R$-.$+ ! $+			$@ $1.$2 ! $3		already got domain
E 31
I 31
# handle error address as a special case
R<@>				$n			errors to mailer-daemon

D 40
# do not qualify list:; syntax
R$* :; <@>			$@ $1 :;
E 40
I 40
# list:; syntax should disappear
R:; <@>				$@
E 40

R$* < @ $* . >			$1 < @ $2 >		strip trailing dots
R$* < @ $=w >			$1			strip local name
D 32
R$* < @ $- . UUCP >		$2 ! $1			convert to UUCP format
E 32
I 32
D 33
R<@ $- . UUCP. > : $+		$1 ! $2			convert to UUCP format
E 33
I 33
R<@ $- . UUCP > : $+		$1 ! $2			convert to UUCP format
E 33
R<@ $+ > : $+			$1 ! $2			convert to UUCP format
D 33
R$* < @ $- . UUCP. >		$2 ! $1			convert to UUCP format
E 33
I 33
R$* < @ $- . UUCP >		$2 ! $1			convert to UUCP format
E 33
E 32
R$* < @ $+ >			$@ $2 ! $1		convert to UUCP format

R$&h ! $+ ! $+			$@ $1 ! $2		$h!...!user => ...!user
R$&h ! $+			$@ $&h ! $1		$h!user => $h!user
E 31
R$+				$: $M ! $1		prepend masquerade name
R! $+				$: $j ! $1		in case $M undefined')
E 30


E 29
PUSHDIVERT(4)
# resolve locally connected UUCP links
I 25
D 28
R< @ $=Z . UUCP > : $+		$#uucp-dom $@ $1 $: $2	@host.UUCP: ...
R$+ < @ $=Z . UUCP >		$#uucp-dom $@ $2 $: $1	user@host.UUCP
E 25
D 4
R< @ $=V . UUCP > : $+		$#suucp $@ $1 $: $1:$2	@host.UUCP: ...
E 4
I 4
D 19
R< @ $=Y . UUCP > : $+		$#suucp $@ $1 $: $1:$2	@host.UUCP: ...
E 4
R< @ $=U . UUCP > : $+		$#uucp $@ $1 $: $1:$2	@host.UUCP: ...
E 19
I 19
R< @ $=Y . UUCP > : $+		$#suucp $@ $1 $: $2	@host.UUCP: ...
D 25
R< @ $=U . UUCP > : $+		$#uucp $@ $1 $: $2	@host.UUCP: ...
E 25
E 19
D 4
R$+ < @ $=V . UUCP >		$#suucp $@ $2 $: $1	user@host.UUCP
E 4
I 4
R$+ < @ $=Y . UUCP >		$#suucp $@ $2 $: $1	user@host.UUCP
I 25
R< @ $=U . UUCP > : $+		$#uucp $@ $1 $: $2	@host.UUCP: ...
E 25
E 4
R$+ < @ $=U . UUCP >		$#uucp $@ $2 $: $1	user@host.UUCP
E 28
I 28
D 31
R< @ $=Z . UUCP. > : $+		$#uucp-dom $@ $1 $: $2	@host.UUCP: ...
R$+ < @ $=Z . UUCP. >		$#uucp-dom $@ $2 $: $1	user@host.UUCP
E 31
I 31
D 35
R$* < @ $=Z . UUCP. > $*	$#uucp-uudom $@ $1 $: $1 < @ $2 .UUCP. > $3	@host.UUCP: ...
E 35
I 35
R$* < @ $=Z . UUCP. > $*	$#uucp-uudom $@ $2 $: $1 < @ $2 .UUCP. > $3
E 35
E 31
D 29
R< @ $=Y . UUCP. > : $+		$#suucp $@ $1 $: $2	@host.UUCP: ...
R$+ < @ $=Y . UUCP. >		$#suucp $@ $2 $: $1	user@host.UUCP
R< @ $=U . UUCP. > : $+		$#uucp $@ $1 $: $2	@host.UUCP: ...
R$+ < @ $=U . UUCP. >		$#uucp $@ $2 $: $1	user@host.UUCP
E 29
I 29
D 32
R< @ $=Y . UUCP. > : $+		$#uucp-new $@ $1 $: $2	@host.UUCP: ...
R$+ < @ $=Y . UUCP. >		$#uucp-new $@ $2 $: $1	user@host.UUCP
R< @ $=U . UUCP. > : $+		$#uucp-old $@ $1 $: $2	@host.UUCP: ...
R$+ < @ $=U . UUCP. >		$#uucp-old $@ $2 $: $1	user@host.UUCP
E 32
I 32
R$* < @ $=Y . UUCP. > $*	$#uucp-new $@ $2 $: $1 < @ $2 .UUCP. > $3
R$* < @ $=U . UUCP. > $*	$#uucp-old $@ $2 $: $1 < @ $2 .UUCP. > $3
E 32
E 29
E 28
POPDIVERT
E 3
E 2
E 1
