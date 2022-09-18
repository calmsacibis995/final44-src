#! /bin/csh -f
#
umask 0
set flags=() noglob files=()
unset t
unset sun
set dest = (va)
set lpr = (/usr/ucb/lpr)
set troff = (/usr/local/troff_p)
set dsun = (/usr/local/dsun)
top:
	if ($#argv > 0) then
		switch ($argv[1])
		case -z:
		case -a:
			set flags = ($flags $argv[1])
		case -t:
			set t
			shift argv
			goto top
		case -l*:
		case -Pvarian:
		case -Pva:
		case -V:
			set dest = (va)
			shift argv
			goto top
		case -Pversatec:
		case -Pvp:
		case -W:
			set dest = (vp)
			shift argv
			goto top
		case -Pimagen:
		case -Pip:
		case -I:
			set dest = (ip)
			shift argv
			goto top
		case -Psun:
			set dest = (va)
			set sun
			shift argv
			goto top
		case -P*: 
			echo "undefined -P typesetter"
			exit(1)
		case -:
			set files = ($files -)
			shift argv
			goto top
		case -*:
			set flags = ($flags $argv[1])
			shift argv
			goto top
		default:
			set files = ($files $argv[1])
			shift argv
			goto top
		endsw
	endif
set name = (ditroff)
if ($#files > 0) then
	set name = ($files[1])
endif
if ($?t) then
	$troff -P$dest $flags $files
else if ($?sun) then
	$troff -Psun $flags $files | $dsun
else
	$troff -P$dest $flags $files | $lpr -P$dest -n -J$name
endif
