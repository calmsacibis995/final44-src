#! /bin/csh -f
set troff = /usr/local/libexec/troff_p
set dterm = (/usr/local/dterm -m -c)
#! /bin/csh -f			These three lines come from Makefile
# set troff = /usr/local/troff_p
# set dterm = (/usr/local/dterm -m -c)

set typesetter = -Pip
set type = -Tip
if ($?PRINTER) then
	set typesetter = -P$PRINTER
	set lineprinter = -P$PRINTER
	set type = -T$PRINTER
endif
if ($?TYPESETTER) then
	set typesetter = -P$TYPESETTER
	set type = -T$TYPESETTER
endif
set lpr = /usr/bin/lpr
umask 0
set flags=() noglob files=() rv1=-rv1
unset t gottype
unsetenv t gottype

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
			set typesetter = -Pvp
			set type = -Tvp
			shift argv
			goto top
		case -Pxerox:
		case -Ppress:
		case -Pdp:
			set typesetter = -Pdp
			set type = -Tdp
			shift argv
			goto top
		case -Pipress2:
		case -Pop:
			set typesetter = -Pop
			set type = -Tdp
			shift argv
			goto top
		case -Pimagen:
		case -Pip:
		case -I:
			set typesetter = -Pip
			set type = -Tip
			shift argv
			goto top
		case -Pimagen-cx:
		case -P300:
		case -Pcx:
			set typesetter = -Pcx
			set type = -Tcx
			shift argv
			goto top
		case -Papple-lz:
		case -Plazy:
		case -Plz:
		case -Ppsc:
		case -PPostScript:
			set typesetter = -Plz
			set type = -Tpsc
			shift argv
			goto top
		case -Pps:
			set typesetter = -Pps
			set type = -Tpsc
			shift argv
			goto top
		case -PAp:
			set typesetter = -PAp
			set type = -Tpsc
			shift argv
			goto top
		case -Paps:
			set typesetter = -Paps
			set type = -Taps
			shift argv
			goto top
		case -Pter:
			set typesetter = -Pter
			set type = -Tter
			shift argv
			goto top
		case -P*: 
			set typesetter = $argv[1]
			if (! $?gottype) set type = $argv[1]
			shift argv
			goto top
		case -T*: 
			set type = $argv[1]
			set gottype
			shift argv
			goto top
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

switch ($type)
case -Tvp:
	set rv1=""
	breaksw
case -Tlz:
	set type = -Tpsc
	breaksw
case -Taps:
	set troff=/usr/old/ditroff
	set rv1="-rv2"
	# incomplete, need to replace lpr
	set t
	breaksw
endsw

if ($#files > 0) then
	set name = $files[1]
else
	set name = ditroff
endif

if ($?t) then
    if ($typesetter == -Pter) then
	$troff -Tter $rv1 $flags $files | $dterm
    else
	$troff $type $rv1 $flags $files
    endif
else if ($typesetter == -Pter) then
    $troff -Tter $rv1 $flags $files | $dterm -L | $lpr $lineprinter -J$name
else
    $troff $type $rv1 $flags $files | $lpr $typesetter -n -J$name
endif
