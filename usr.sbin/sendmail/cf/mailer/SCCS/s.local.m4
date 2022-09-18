h32333
s 00006/00004/00037
d D 8.15 95/04/26 09:25:10 eric 31 30
c add *_MAILER_CHARSET; UUCP_MAX_SIZE => UUCP_MAILER_MAX
e
s 00001/00001/00040
d D 8.14 95/04/23 13:52:04 eric 30 29
c update DSN types to be more realistic
e
s 00002/00002/00039
d D 8.13 95/02/15 16:48:59 eric 29 28
c add LOCAL_MAILER_MAX and PROCMAIL_MAILER_MAX
e
s 00000/00001/00041
d D 8.12 95/01/24 07:36:29 eric 28 27
c more hacks to get + to work properly
e
s 00002/00002/00040
d D 8.11 94/11/27 15:15:17 eric 27 26
c add MTS type information
e
s 00001/00001/00041
d D 8.10 94/11/27 10:16:06 eric 26 25
c prog mailer needs "o" flag by default
e
s 00002/00001/00040
d D 8.9 94/11/24 09:18:26 eric 25 24
c add LOCAL_SHELL_DIR
e
s 00001/00000/00040
d D 8.8 94/11/13 16:46:11 eric 24 23
c accept user+detail
e
s 00001/00001/00039
d D 8.7 94/07/16 11:23:00 eric 23 22
c set A, w, 5, :, /, |, and @ on the local mailer
e
s 00001/00001/00039
d D 8.6 93/10/24 16:27:17 eric 22 21
c don't strip host name on header recipient addresses in prog mailer
e
s 00007/00001/00033
d D 8.5 93/10/23 17:25:15 eric 21 20
c fix host name on local mailer -- add it to recipients if
c FEATURE(always_add_domain) specified; strip it from envelope
e
s 00002/00002/00032
d D 8.4 93/08/08 09:59:37 eric 20 19
c don't assume "m" in local mailer flags
e
s 00004/00002/00030
d D 8.3 93/07/13 13:00:27 eric 19 18
c add uucp-dom mailer, OSTYPE(aix3), LOCAL_SHELL_{FLAGS,ARGS}, UUCP_MAX_SIZE
e
s 00002/00001/00030
d D 8.2 93/07/11 08:17:52 eric 18 17
c many changes including: add LOCAL_MAILER_ARGS; FEATURE(allmasquerade);
c use $U as UUCP name instead of $k for masquerading; new "esmtp" mailer
e
s 00002/00002/00029
d D 8.1 93/06/07 10:11:22 bostic 17 16
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00002/00001/00029
d D 6.10 93/06/03 19:07:29 eric 16 15
c use $M (masquerade-as) instead of $j in _ALWAYS_ADD_DOMAIN_
e
s 00004/00000/00026
d D 6.9 93/05/24 09:21:44 eric 15 14
c add FEATURE(always_add_domain)
e
s 00005/00003/00021
d D 6.8 93/05/06 14:37:13 eric 14 13
c add SMTP_MAILER_FLAGS and UUCP_MAILER_FLAGS
e
s 00001/00001/00023
d D 6.7 93/04/03 07:21:55 eric 13 12
c add directory search path on prog mailer
e
s 00001/00001/00023
d D 6.6 93/03/19 16:25:52 eric 12 11
c prog mailer should preserve case
e
s 00001/00001/00023
d D 6.5 93/03/05 14:47:29 eric 11 10
c avoid having C flag qualify list:; and error <> syntax
e
s 00001/00001/00023
d D 6.4 93/03/01 13:42:07 eric 10 9
c change error address convention to avoid conflict with C flag
e
s 00001/00001/00023
d D 6.3 93/02/21 12:39:53 eric 9 8
c changes to handle <> properly as an error address indicator
e
s 00004/00002/00020
d D 6.2 93/02/20 14:20:13 eric 8 6
c make M4 macro names more consistent
e
s 00000/00000/00022
d R 6.2 92/12/21 16:10:28 eric 7 6
c Release 6
e
s 00000/00000/00022
d D 6.1 92/12/21 16:10:18 eric 6 5
c Release 6
e
s 00001/00001/00021
d D 2.5 92/11/13 22:56:10 eric 5 4
c quote versionid to avoid # problems
e
s 00002/00002/00020
d D 2.4 92/07/14 12:32:01 eric 4 3
c generalize local mailer flags (for different OS types)
e
s 00002/00001/00020
d D 2.3 91/12/12 10:49:45 eric 3 2
c hacks for HP-UX (ugh)
e
s 00002/00002/00019
d D 2.2 91/10/02 18:39:38 eric 2 1
c make it work on 4.4bsd m4
e
s 00021/00000/00000
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
D 17
# Copyright (c) 1988 The Regents of the University of California.
# All rights reserved.
E 17
I 17
# Copyright (c) 1988, 1993
#	The Regents of the University of California.  All rights reserved.
E 17
#
# %sccs.include.redist.sh%
#
I 14
D 20
ifdef(`LOCAL_MAILER_FLAGS',, `define(`LOCAL_MAILER_FLAGS', `rn')')
E 20
I 20
ifdef(`LOCAL_MAILER_FLAGS',, `define(`LOCAL_MAILER_FLAGS', `rmn')')
E 20
ifdef(`LOCAL_MAILER_PATH',, `define(`LOCAL_MAILER_PATH', /bin/mail)')
I 18
ifdef(`LOCAL_MAILER_ARGS',, `define(`LOCAL_MAILER_ARGS', `mail -d $u')')
I 19
ifdef(`LOCAL_SHELL_FLAGS',, `define(`LOCAL_SHELL_FLAGS', `eu')')
E 19
E 18
ifdef(`LOCAL_SHELL_PATH',, `define(`LOCAL_SHELL_PATH', /bin/sh)')
I 19
ifdef(`LOCAL_SHELL_ARGS',, `define(`LOCAL_SHELL_ARGS', `sh -c $u')')
I 25
ifdef(`LOCAL_SHELL_DIR',, `define(`LOCAL_SHELL_DIR', `$z:/')')
E 25
E 19
E 14
POPDIVERT

##################################################
###   Local and Program Mailer specification   ###
##################################################

D 5
VERSIONID(%W% (Berkeley) %G%)
E 5
I 5
VERSIONID(`%W% (Berkeley) %G%')
E 5

D 2
Mlocal,	P=ifdef(`LOCAL_MAILER', LOCAL_MAILER, /bin/mail), F=rlsDFMmn, S=10, R=20, A=mail -d $u
Mprog,	P=ifdef(`LOCAL_SHELL', LOCAL_SHELL, /bin/sh),   F=lsDFMe,   S=10, R=20, A=sh -c $u
E 2
I 2
D 3
Mlocal,	P=ifdef(`LOCAL_MAILER', `LOCAL_MAILER', /bin/mail), F=rlsDFMmn, S=10, R=20, A=mail -d $u
E 3
I 3
D 4
define(`_LOCAL_FLAGS_', CONCAT(`lsDFMm', ifdef(`_HPUX_', `', `rn')))dnl
Mlocal,	P=ifdef(`LOCAL_MAILER', `LOCAL_MAILER', /bin/mail), F=_LOCAL_FLAGS_, S=10, R=20, A=mail -d $u
E 4
I 4
D 14
ifdef(`LOCAL_MAILER_FLAGS',, `define(`LOCAL_MAILER_FLAGS', `rn')')dnl
D 8
Mlocal,	P=ifdef(`LOCAL_MAILER', `LOCAL_MAILER', /bin/mail), F=CONCAT(`lsDFMm', LOCAL_MAILER_FLAGS), S=10, R=20, A=mail -d $u
E 4
E 3
Mprog,	P=ifdef(`LOCAL_SHELL', `LOCAL_SHELL', /bin/sh),   F=lsDFMe,   S=10, R=20, A=sh -c $u
E 8
I 8
Mlocal,		P=ifdef(`LOCAL_MAILER_PATH', `LOCAL_MAILER_PATH', /bin/mail), F=CONCAT(`lsDFMm', LOCAL_MAILER_FLAGS), S=10, R=20,
E 14
I 14
D 20
Mlocal,		P=LOCAL_MAILER_PATH, F=CONCAT(`lsDFMm', LOCAL_MAILER_FLAGS), S=10, R=20,
E 20
I 20
D 21
Mlocal,		P=LOCAL_MAILER_PATH, F=CONCAT(`lsDFM', LOCAL_MAILER_FLAGS), S=10, R=20,
E 21
I 21
D 23
Mlocal,		P=LOCAL_MAILER_PATH, F=CONCAT(`lsDFM', LOCAL_MAILER_FLAGS), S=10, R=20/40,
E 23
I 23
D 27
Mlocal,		P=LOCAL_MAILER_PATH, F=CONCAT(`lsDFMAw5:/|@', LOCAL_MAILER_FLAGS), S=10, R=20/40,
E 27
I 27
D 30
Mlocal,		P=LOCAL_MAILER_PATH, F=CONCAT(`lsDFMAw5:/|@', LOCAL_MAILER_FLAGS), S=10, R=20/40, T=X-Unix,
E 30
I 30
D 31
Mlocal,		P=LOCAL_MAILER_PATH, F=CONCAT(`lsDFMAw5:/|@', LOCAL_MAILER_FLAGS), S=10, R=20/40, T=DNS/RFC822/X-Unix,
E 30
E 27
E 23
E 21
E 20
E 14
D 18
		A=mail -d $u
E 18
I 18
D 29
		A=LOCAL_MAILER_ARGS
E 29
I 29
		ifdef(`LOCAL_MAILER_MAX', `M=LOCAL_MAILER_MAX, ')A=LOCAL_MAILER_ARGS
E 29
E 18
D 12
Mprog,		P=ifdef(`LOCAL_SHELL_PATH', `LOCAL_SHELL_PATH', /bin/sh), F=lsDFMe, S=10, R=20,
E 12
I 12
D 13
Mprog,		P=ifdef(`LOCAL_SHELL_PATH', `LOCAL_SHELL_PATH', /bin/sh), F=lsDFMeu, S=10, R=20,
E 13
I 13
D 14
Mprog,		P=ifdef(`LOCAL_SHELL_PATH', `LOCAL_SHELL_PATH', /bin/sh), F=lsDFMeu, S=10, R=20, D=$z:/,
E 14
I 14
D 19
Mprog,		P=LOCAL_SHELL_PATH, F=lsDFMeu, S=10, R=20, D=$z:/,
E 14
E 13
E 12
		A=sh -c $u
E 19
I 19
D 22
Mprog,		P=LOCAL_SHELL_PATH, F=CONCAT(`lsDFM', LOCAL_SHELL_FLAGS), S=10, R=20, D=$z:/,
E 22
I 22
D 25
Mprog,		P=LOCAL_SHELL_PATH, F=CONCAT(`lsDFM', LOCAL_SHELL_FLAGS), S=10, R=20/40, D=$z:/,
E 25
I 25
D 26
Mprog,		P=LOCAL_SHELL_PATH, F=CONCAT(`lsDFM', LOCAL_SHELL_FLAGS), S=10, R=20/40, D=LOCAL_SHELL_DIR,
E 26
I 26
D 27
Mprog,		P=LOCAL_SHELL_PATH, F=CONCAT(`lsDFMo', LOCAL_SHELL_FLAGS), S=10, R=20/40, D=LOCAL_SHELL_DIR,
E 27
I 27
Mprog,		P=LOCAL_SHELL_PATH, F=CONCAT(`lsDFMo', LOCAL_SHELL_FLAGS), S=10, R=20/40, D=LOCAL_SHELL_DIR, T=X-Unix,
E 27
E 26
E 25
E 22
D 29
		A=LOCAL_SHELL_ARGS
E 29
I 29
		ifdef(`LOCAL_MAILER_MAX', `M=LOCAL_MAILER_MAX, ')A=LOCAL_SHELL_ARGS
E 31
I 31
Mlocal,		P=LOCAL_MAILER_PATH, F=CONCAT(`lsDFMAw5:/|@', LOCAL_MAILER_FLAGS), S=10, R=20/40,
		_OPTINS(`LOCAL_MAILER_MAX', `M=', `, ')_OPTINS(`LOCAL_MAILER_CHARSET', `C=', `, ')T=DNS/RFC822/X-Unix,
		A=LOCAL_MAILER_ARGS
Mprog,		P=LOCAL_SHELL_PATH, F=CONCAT(`lsDFMo', LOCAL_SHELL_FLAGS), S=10, R=20/40, D=LOCAL_SHELL_DIR
		_OPTINS(`LOCAL_MAILER_MAX', `M=', `, ')T=X-Unix,
		A=LOCAL_SHELL_ARGS
E 31
E 29
E 19
E 8
E 2

S10
D 9
R@			$n			errors to mailer-daemon
E 9
I 9
D 10
R<@>			$n			errors to mailer-daemon
E 10
I 10
D 11
R<>			$n			errors to mailer-daemon
E 11
I 11
R<@>			$n			errors to mailer-daemon
I 21
R$+			$: $>40 $1

S20
R$+ < @ $* >		$: $1			strip host part
I 24
D 28
R$+ + $*		$: $1			strip +argument part
E 28
E 24

S40
E 21
I 15
ifdef(`_ALWAYS_ADD_DOMAIN_',
`R$* < @ $* > $*		$@ $1 < @ $2 > $3	already fully qualified
D 16
R$*			$@ $1 @ $j		add local qualification',
E 16
I 16
R$*			$: $1 @ $M		add local qualification
R$* @			$: $1 @ $j		if $M not defined',
E 16
`dnl')
E 15
E 11
E 10
E 9
E 1
