h56376
s 00002/00000/00023
d D 8.4 94/04/04 14:31:18 bostic 7 6
c set EDITOR, PAGER
e
s 00002/00000/00021
d D 8.3 94/04/04 14:27:10 bostic 6 5
c set up vi
e
s 00005/00011/00016
d D 8.2 94/04/04 14:24:31 bostic 5 4
c 4.4BSD-Lite
e
s 00000/00000/00027
d D 8.1 93/06/08 11:34:55 bostic 4 3
c 4.4BSD snapshot (revision 8.1)
e
s 00008/00003/00019
d D 5.3 90/07/25 14:08:45 bostic 3 2
c update for Reno
e
s 00001/00001/00021
d D 5.2 89/05/28 15:24:24 bostic 2 1
c add alias f for finger
e
s 00022/00000/00000
d D 5.1 89/05/28 15:21:44 bostic 1 0
c date and time created 89/05/28 15:21:44 by bostic
e
u
U
t
T
I 1
D 5
# .cshrc initialization
E 5
I 5
#csh .cshrc file
E 5

I 3
D 5
alias df	df -k
alias du	du -k
E 3
I 2
alias f		finger
E 2
alias h		'history -r | more'
E 5
I 5
alias h		history 25
E 5
alias j		jobs -l
alias la	ls -a
alias lf	ls -FA
D 5
alias ll	ls -lgsA
E 5
I 5
alias ll	ls -lA
E 5
I 3
alias su	su -m
E 3
D 5
alias tset	'set noglob histchars=""; eval `\tset -s \!*`; unset noglob histchars'
alias x		exit
alias z		suspend
E 5

I 7
setenv	EDITOR	vi
E 7
I 6
setenv	EXINIT	'set autoindent'
I 7
setenv	PAGER	more
E 7

E 6
D 3
set path=(/usr/ucb /bin /usr/bin /usr/new /usr/local /usr/hosts /usr/games .)
E 3
I 3
D 5
set path = (~/bin /bin /usr/{bin,new,games,local,old} .)
E 5
I 5
set path = (~/bin /bin /usr/{bin,X11/bin,contrib/bin,games,old/bin} /usr/local/bin)
E 5
E 3

if ($?prompt) then
	# An interactive shell -- set some stuff up
I 3
	set filec
	set history = 1000
E 3
	set ignoreeof
I 3
	set mail = (/var/mail/$USER)
E 3
	set mch = `hostname -s`
D 5
	set prompt = "$mch:q:$cwd:t {\!} "
E 5
I 5
	set prompt = "${mch:q}: {\!} "
E 5
D 3
	set filec
	set mail = (/usr/spool/mail/$USER)
E 3
I 3
	umask 2
E 3
endif
D 2

E 2
E 1
