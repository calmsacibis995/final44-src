h45284
s 00007/00007/00019
d D 8.2 94/03/17 06:31:33 bostic 7 6
c cleanup pass
e
s 00000/00000/00026
d D 8.1 93/06/09 12:56:05 bostic 6 5
c 4.4BSD snapshot (revision 8.1)
e
s 00002/00001/00024
d D 5.5 92/04/22 11:21:27 bostic 5 4
c add Kirk's hup alias
e
s 00002/00002/00023
d D 5.4 92/04/02 14:14:11 bostic 4 3
c dot shouldn't be in root's path at all
e
s 00002/00001/00023
d D 5.3 92/03/21 11:16:53 bostic 3 2
c root logins should always start with a umask of 022
e
s 00002/00014/00022
d D 5.2 92/03/16 13:42:44 bostic 2 1
c delete -k flags, no reason for root to have SCCS aliases
e
s 00036/00000/00000
d D 5.1 90/06/25 11:42:52 bostic 1 0
c date and time created 90/06/25 11:42:52 by bostic
e
u
U
t
T
I 1
D 3
alias mail Mail
E 3
set history=1000
D 4
set path=(/sbin /usr/sbin /bin /usr/bin /usr/local /usr/hosts /usr/contrib .)
E 4
I 4
D 7
set path=(/sbin /usr/sbin /bin /usr/bin)
E 7
I 7
set path=(/sbin /usr/sbin /bin /usr/bin /usr/contrib/bin /usr/old/bin)
E 7
E 4

# directory stuff: cdpath/cd/back
D 5
set cdpath=(/sys /usr/src/{bin,sbin,usr.{bin,sbin},pgrm,lib,libexec,share,contrib,local,devel,games,old,})
E 5
I 5
set cdpath=(/sys /usr/src/{bin,sbin,usr.{bin,sbin},lib,libexec,share,contrib,local,games,old})
E 5
D 7
alias	cd	'set old=$cwd; chdir \!*'
E 7
D 4
alias	h	history
E 4
I 4
alias	h	history -r
I 5
alias	hup	'kill -HUP `cat /var/run/\!$.pid`'
E 5
E 4
alias	j	jobs -l
D 7
alias	ll	ls -lg
D 2
alias	ls	ls -g -k
E 2
I 2
alias	ls	ls -g
E 2
alias	back	'set back=$old; set old=$cwd; cd $back; unset back; dirs'

D 2
# sccs stuff: sd/co/ci/allout/out/unedit
alias	sd	sccs diffs
alias	co	sccs get -e
alias	ci	sccs delget
alias	allout	"(cd ..; echo */SCCS/p.*|sed s/SCCS\\/p.//g)"
alias	out	"echo SCCS/p.*|sed s/SCCS\\/p.//g"
alias	info	sccs info
alias	unedit	sccs unedit
alias	get	sccs get
alias	prt	sccs prt
alias	z		suspend
E 2
I 2
alias	z	suspend
E 7
I 7
alias	k	jobs -l
alias	ll	ls -l
E 7
E 2
alias	x	exit
I 7
alias	z	suspend

alias	back	'set back=$old; set old=$cwd; cd $back; unset back; dirs'
alias	cd	'set old=$cwd; chdir \!*'
E 7
alias	pd	pushd
alias	pd2	pushd +2
alias	pd3	pushd +3
alias	pd4	pushd +4
D 2
alias	df	df -k
alias	du 	du -k
E 2
alias	tset	'set noglob histchars=""; eval `\tset -s \!*`; unset noglob histchars'

if ($?prompt) then
	set prompt="`hostname -s`# "
endif
I 3

umask 022
E 3
E 1
