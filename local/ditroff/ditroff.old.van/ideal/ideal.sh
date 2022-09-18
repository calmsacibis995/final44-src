#! /bin/csh -f			These three lines inserted by Makefile
# set ideal = /usr/local/ideal_p
# set filter = /usr/local/ideal_f
set typesetter = va
if ($?PRINTER) then
	typesetter = $PRINTER
endif
if ($?TYPESETTER) then
	typesetter = $TYPESETTER
endif
umask 0
unset t
set flags = ()
set files = ()
top:
if ($#argv > 0) then
	switch ($argv[1])
	case -n:
		set t
	case -Pvarian:
	case -Pva:
	case -V:
		set typesetter = va
		shift argv
		goto top
	case -Pversatec:
	case -Pvp:
	case -W:
		set typesetter = vp
		shift argv
		goto top
	case -Pxerox:
	case -Ppress:
	case -Pdp:
		set typesetter = dp
		shift argv
		goto top
	case -Pimagen:
	case -Pip:
	case -I:
		set typesetter = ip
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

if ($?t) then
	$ideal $flags $files
else
	$ideal $flags $files | $filter -P$typesetter
endif
