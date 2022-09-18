#! /bin/csh -f
# troff to the IMAGEN imPrint printer
umask 0
set flags=() noglob
set facp=(-F/usr/local/lib/ifont)
set macp=(/usr/lib/tmac/tmac.vcat /usr/lib/tmac/tmac.imagen)
set troff = (/usr/bin/troff) lpr = (/usr/ucb/lpr -t)
set prntr=(-Pimagen)
unset t
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

		case -x:
			set macp=()
			shift argv
			goto top

		case -F:
			shift argv
			if ($#argv > 0) then
				set facp = (-F$argv[1])
				shift argv
			endif
			goto top

		case -F*:
			set facp = ($argv[1])
			shift argv
			goto top

		case -P?*:
			set prntr = $argv[1]
			shift argv
			goto top

		case -P:
			shift argv
			if ($#argv > 0) then
				set prntr = (-P$argv[1])
				shift argv
			else
				echo "Usage: -P printer ..."
				exit (1)
			endif
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
	set banner=itroff
else
	set banner="$argv[1]:t"
endif

set tflags=(-x -t $flags $facp/$prntr/ftXX $macp)

if ($?host) then
    if ($?t) then
        set cmd=("(" soelim $* | rsh $host \"$troff $tflags -\" ")")
    else
        set cmd=("(" soelim $* | rsh $host \"$troff $tflags - | $lpr $prntr -J $banner\" ")")
    endif
else
    if ($?t) then
	set cmd=("(" $troff $tflags $* ")")
    else
	set cmd=("(" $troff $tflags $* | $lpr $prntr -J $banner ")")
    endif
endif

eval $cmd
