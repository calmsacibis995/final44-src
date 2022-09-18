h48584
s 00006/00012/00003
d D 8.2 94/04/04 14:25:23 bostic 3 2
c 4.4BSD-Lite
e
s 00000/00000/00015
d D 8.1 93/06/08 11:34:57 bostic 2 1
c 4.4BSD snapshot (revision 8.1)
e
s 00015/00000/00000
d D 5.1 89/05/28 15:21:45 bostic 1 0
c date and time created 89/05/28 15:21:45 by bostic
e
u
U
t
T
I 1
D 3
#csh login file
E 3
I 3
#csh .login file
E 3

D 3
if ( ! $?TERMCAP ) then
	tset -Q  '-mdialup:?vt100' $TERM
endif

stty	newcrt crterase

set	savehist=100
set	ignoreeof

setenv	EXINIT		'set ai sm noeb'
setenv	HOSTALIASES	 $HOME/.hostaliases
E 3
I 3
setenv SHELL /bin/csh
set noglob
eval `tset -s -m 'network:?xterm'`
unset noglob
stty status '^T' crt -tostop
E 3

/usr/games/fortune
E 1
