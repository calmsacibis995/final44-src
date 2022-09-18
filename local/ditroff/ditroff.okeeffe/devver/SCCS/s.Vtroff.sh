h39680
s 00005/00003/00084
d D 1.4 88/03/04 17:01:55 jaap 4 3
c cleaning up
e
s 00001/00001/00086
d D 1.3 86/10/21 11:02:46 jaap 3 2
c saving this version
e
s 00007/00001/00080
d D 1.2 86/06/02 19:09:14 jaap 2 1
c Adden flag -N to test new spooler filter.
e
s 00081/00000/00000
d D 1.1 86/06/02 17:07:44 jaap 1 0
c date and time created 86/06/02 17:07:44 by jaap
e
u
U
t
T
I 1
#! /bin/csh -f
#
D 2
#	@(#)vtroff.sh	4.4	(Berkeley)	5/4/84; CWI	1.4	84/11/15
E 2
I 2
#	@(#)vtroff.sh	4.4	(Berkeley)	5/4/84;	%I%	(CWI)	%E%
E 2
#
umask 0
set flags=() noglob length=() fonts=() fontf=() banner=() Tflags=(-Tver) Dflags=()
unset t
set sort = (/usr/lib/vsort80)
set lpr = (/usr/ucb/lpr -Pvp -n)
set troff = (/usr/local/ditroff)
set class = (`hostname`)
top:
	if ($#argv > 0) then
		switch ($argv[1])
		case -t:
			set t
			shift argv
			goto top
		case -h:
			if ($#argv < 2) then
				echo -h takes following host name.
				exit(1)
			endif
			set host = $argv[2]
			shift argv
			shift argv
			goto top
		case -D:
			set Dflags = -D
			shift argv
			goto top
		case -J:
			shift argv
			set banner = $argv[1]
			shift argv
			goto top
		case -C:
			shift argv
			set class = $argv[1]
			shift argv
			goto top
		case -x:
			set Tflags = -Thar
D 4
			set banner = Harris
E 4
I 4
			set banner = NewHarris
			set lpr = (/usr/ucb/lpr -Pnvp -n)
			set sort = (/usr/lib/nvsort80)
E 4
I 2
			shift argv
			goto top
		case -N:
			set Tflags = -Tnver
D 3
			set banner = (New Harris)
E 3
I 3
			set banner = (NewHarris)
E 3
			set lpr = (/usr/ucb/lpr -Pnvp -n)
E 2
			shift argv
			goto top
		case -*:
			set flags = ($flags $argv[1])
			shift argv
			goto top
		case -:
			breaksw
		endsw
	endif

if ($#argv == 0) then
	set argv=(-)
	if ($#banner == 0) then
		set banner=Vtroff
	endif
else
	if ($#banner == 0) then
		set banner=$argv[1]
	endif
endif

set tflags=(-t -rv2 $flags)

if ($?host) then
    if ($?t) then
	soelim $* | rsh $host \"$troff $tflags - | $sort \"
    else
D 4
	soelim $* | rsh $host \"$troff $Tflags $Dflags $tflags - | $sort | $lpr -Tvp -J$banner -n \"
E 4
I 4
	soelim $* | rsh $host \"$troff $Tflags $Dflags $tflags - | $sort | $lpr -Tvp -J$banner \"
E 4
    endif
else
    if ($?t) then
	$troff $tflags $* | $sort
    else
D 4
	$troff $Tflags $Dflags $tflags $* | $sort | $lpr -J$banner -C$class -n
E 4
I 4
	$troff $Tflags $Dflags $tflags $* | $sort | $lpr -J$banner -C$class
E 4
    endif
endif
E 1
