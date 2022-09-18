h31012
s 00000/00000/00033
d D 8.1 93/06/06 15:54:51 bostic 8 7
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00027
d D 4.7 91/04/18 16:28:43 bostic 7 6
c new copyright; att/bsd/shared
e
s 00018/00018/00011
d D 4.6 89/07/24 16:57:07 bostic 6 5
c move to subdirectory of /usr/libexec
e
s 00001/00000/00028
d D 4.5 86/08/29 15:29:47 sklower 5 4
c add entry for grn output "driver"
e
s 00001/00000/00027
d D 4.4 85/09/21 15:19:20 sam 4 3
c add imagen
e
s 00001/00000/00026
d D 4.3 85/01/04 14:03:06 jak 3 2
c add 4013 option
e
s 00016/00007/00010
d D 4.2 83/11/11 15:02:39 ralph 2 1
c added new devices.
e
s 00017/00000/00000
d D 4.1 83/07/04 11:08:41 sam 1 0
c date and time created 83/07/04 11:08:41 by sam
e
u
U
t
T
I 1
D 2
#! /bin/sh
E 2
I 2
D 7
#!/bin/sh
E 2
#	%W%	(Berkeley)	%G%
E 7
I 7
#!/bin/sh -
E 7
#
I 7
# %sccs.include.proprietary.sh%
#
#	%W% (Berkeley) %G%
#

E 7
D 2
PATH=/bin:/usr/bin
E 2
I 2
D 6
PATH=/bin:/usr/bin:/usr/ucb
E 6
I 6
PATH=/bin:/usr/bin:/usr/libexec/plot
E 6
E 2
case $1 in
-T*)	t=$1
	shift ;;
*)	t=-T$TERM
esac
case $t in
D 2
-T450)	exec t450 $*;;
-T300)	exec t300 $*;;
-T300S|-T300s)	exec t300s $*;;
-Tver)	exec vplot $*;;
E 2
I 2
D 6
-T450)			exec t450 $*;;
-T300)			exec t300 $*;;
-T300S|-T300s)		exec t300s $*;;
-Tver)			exec lpr -Pversatec -g $*;;
-Tvar)			exec lpr -Pvarian -g $*;;
E 2
-Ttek|-T4014|-T)	exec tek $* ;;
I 3
-T4013)			exec t4013 $* ;;
E 3
D 2
*)  echo plot: terminal type $t not known 1>&2; exit 1
E 2
I 2
-Tbitgraph|-Tbg)	exec bgplot $*;;
-Tgigi|-Tvt125)		exec gigiplot $*;;
-Taed)			exec aedplot $*;;
-Thp7221|-Thp7|-Th7)	exec hp7221plot $*;;
E 6
I 6
-T450)			exec t450 "$@";;
-T300)			exec t300 "$@";;
-T300S|-T300s)		exec t300s "$@";;
-Tver)			exec lpr -Pversatec -g "$@";;
-Tvar)			exec lpr -Pvarian -g "$@";;
-Ttek|-T4014|-T)	exec tek "$@" ;;
-T4013)			exec t4013 "$@" ;;
-Tbitgraph|-Tbg)	exec bgplot "$@";;
-Tgigi|-Tvt125)		exec gigiplot "$@";;
-Taed)			exec aedplot "$@";;
-Thp7221|-Thp7|-Th7)	exec hp7221plot "$@";;
E 6
-Thp|-T2648|-T2648a|-Thp2648|-Thp2648a|h8)
D 6
			exec hpplot $*;;
I 4
-Tip|-Timagen)		exec implot $*;;
I 5
-Tgrn)			exec grnplot $*;;
E 5
E 4
-Tcrt)			exec crtplot $*;;
-Tdumb|un|unknown)	exec dumbplot $*;;
*)  			exec crtplot $*;;
E 6
I 6
			exec hpplot "$@";;
-Tip|-Timagen)		exec implot "$@";;
-Tgrn)			exec grnplot "$@";;
-Tcrt)			exec crtplot "$@";;
-Tdumb|un|unknown)	exec dumbplot "$@";;
*)  			exec crtplot "$@";;
E 6
E 2
esac
E 1
