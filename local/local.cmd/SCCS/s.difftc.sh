h10870
s 00017/00007/00042
d D 1.4 85/11/01 19:19:17 serge 4 3
c allow passing of flags to showtc
e
s 00006/00011/00043
d D 1.3 83/04/25 19:19:03 layer 3 2
c changed semantics a little
e
s 00029/00016/00025
d D 1.2 83/04/25 18:25:18 layer 2 1
c added -s flag to showtc, and
c changed difftc to diff two entries in one file.
e
s 00041/00000/00000
d D 1.1 83/04/25 13:22:28 layer 1 0
c date and time created 83/04/25 13:22:28 by layer
e
u
U
t
T
I 1
#! /bin/csh -f
#
# SCCS id: %W%	(Berkeley) %G%
#
# diff termcap files
D 2
@ n = 1
set files=() term=()
E 2
I 2
D 4
set n=1 files=() term=()
E 4
I 4
set path=(/usr/ucb /bin /usr/bin /usr/new /usr/local . $path)
set n=1 files=() flags=() term=()
E 4
E 2

I 4
if (! $?cwd) then
	set cwd=.
endif
if ("$cwd" !~ /*) then
	set cwd=`pwd`
endif

E 4
while ($n <= $#argv)
D 2
	if ("$argv[$n]" == "-e") then
E 2
I 2
	if ("$argv[$n]" == "-f") then
E 2
		@ n++
D 2
		set term=($argv[$n])
	else
E 2
		if ($argv[$n] !~ /*) then
			set files=($files $cwd/$argv[$n])
		else
			set files=($files $argv[$n])
		endif
I 4
	else if ("$argv[$n]" =~ -*) then
		set flags=($flags $argv[$n])
E 4
I 2
	else
		set term=($term $argv[$n])
E 2
	endif
	@ n++
end
I 2

E 2
switch ($#files)
D 2
	case 0:
		echo 'difftc: need at least one termcap file'
E 2
I 2
case 0:
I 3
	set files=(/etc/termcap)
case 1:
E 3
	if ($#term != 2) then
D 3
		echo need at least one termcap file
E 3
I 3
D 4
		echo need two entries to diff
E 4
I 4
		echo difftc: need two entries to diff
E 4
E 3
E 2
		exit 1
D 2
	case 1:
		set files=(/etc/termcap $files)
		breaksw
	case 2:
		breaksw
	default:
		echo 'difftc: too many termcap files'
E 2
I 2
	endif
	breaksw
D 3
case 1:
	set files=(/etc/termcap $files)
	breaksw
E 3
case 2:
D 3
	if ($#term > 1) then
		echo "can't specify two files and two entries"
E 2
		exit 1
I 2
	endif
E 3
	breaksw
default:
D 4
	echo too many termcap files
E 4
I 4
	echo difftc: too many termcap files
E 4
	exit 1
E 2
endsw

onintr cleanup
D 2
/usr/local/showtc -f $files[1] $term > /tmp/tcd$$.old
/usr/local/showtc -f $files[2] $term | diff /tmp/tcd$$.old -
E 2
I 2

D 3
if ($files == "") then
	/usr/local/showtc -s -f /etc/termcap $term[1] > /tmp/tcd$$.old
	/usr/local/showtc -s -f /etc/termcap $term[2] | diff /tmp/tcd$$.old -
E 3
I 3
if ($#files == 1) then
D 4
	/usr/local/showtc -s -f $files $term[1] > /tmp/tcd$$.old
	/usr/local/showtc -s -f $files $term[2] | diff /tmp/tcd$$.old -
E 4
I 4
	showtc -s $flags -f $files $term[1] > /tmp/tcd$$.old
	showtc -s $flags -f $files $term[2] | diff /tmp/tcd$$.old -
E 4
E 3
else
D 4
	/usr/local/showtc -f $files[1] $term > /tmp/tcd$$.old
	/usr/local/showtc -f $files[2] $term | diff /tmp/tcd$$.old -
E 4
I 4
	showtc $flags -f $files[1] $term > /tmp/tcd$$.old
	showtc $flags -f $files[2] $term | diff /tmp/tcd$$.old -
E 4
endif
E 2

cleanup:
rm -f /tmp/tcd$$.old
E 1
