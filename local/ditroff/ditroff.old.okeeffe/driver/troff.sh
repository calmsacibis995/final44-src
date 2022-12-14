#! /bin/csh -f			These three lines come from Makefile
# set troff = /usr/local/troff_p
# set dterm = (/usr/local/dterm -m -c)
set typesetter = ip
set lineprinter = vx
if ($?PRINTER) then
	set typesetter = $PRINTER
	set lineprinter = $PRINTER
endif
if ($?TYPESETTER) then
	set typesetter = $TYPESETTER
endif
set lpr = /usr/ucb/lpr
umask 0
set flags=() noglob files=() rv1=-rv1
unset t
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
		case -Pversatec:
		case -Pvp:
		case -W:
			set typesetter = vp
			set rv1 = " "
			shift argv
			goto top
		case -Pxerox:
		case -Ppress:
		case -Pdp:
			set typesetter = dp
			shift argv
			goto top
		case -Pipress2:
		case -Pop:
			set typesetter = op
			shift argv
			goto top
		case -Pimagen:
		case -Pip:
		case -I:
			set typesetter = ip
			shift argv
			goto top
		case -Pimagen-cx:
		case -P300:
		case -Pcx:
			set typesetter = cx
			shift argv
			goto top
		case -Ppsc:
		case -Plz:
		case -PPostScript:
			set typesetter = lz
			shift argv
			goto top
		case -Pter:
			set typesetter = ter
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
set name = ditroff
if ($#files > 0) then
	set name = $files[1]
endif
if ($?t) then
    if ($typesetter == ter) then
	$troff -Pter $rv1 $flags $files | $dterm
    else
	$troff -P$typesetter $rv1 $flags $files
    endif
else if ($typesetter == ter) then
    $troff -Pter $flags $rv1 $files | $dterm -L | $lpr -P$lineprinter -J$name
else
    $troff -P$typesetter $rv1 $flags $files | $lpr -P$typesetter -n -J$name
endif
