
#
#      Copyright (c) 1984, 1985 AT&T
#      All Rights Reserved
#
#      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
#      CODE OF AT&T.
#      The copyright notice above does not 
#      evidence any actual or intended
#      publication of such source code.
#
#
# G. S. Fowler
# AT&T Bell Laboratories
#
# new->old makefile converter
# this glues the two passes together
#
# @(#)mkold (AT&T Bell Laboratories) 08/30/85a
#
make=${BINDIR}/nmake
file=0
pass1=
pass2=
targets=
while true
do	case $1 in
	-f)	file=1; pass1="$pass1 $1"; shift; pass1="$pass1 $1" ;;
	-g)	pass1="$pass1 $1"; shift; pass1="$pass1 $1" ;;
	-x)	pass2="$pass2 $1"; shift; pass2="$pass2 $1" ;;
	-x*)	pass2="$pass2 $1" ;;
	-*|+*)	pass1="$pass1 $1" ;;
	"")	break ;;
	*)	if	test "$file" = "0" -a ! -f Makefile -a ! -f makefile -a -f $1.mk
		then	pass1="$pass1 $1"
		else	targets="$targets $1"
		fi
		file=1 ;;
	esac
	shift
done
for i in ""$targets
do
	j=$i	# ksh problem
	$make -o '.READONLY.c:.CLEAR' '.READONLY.l:.CLEAR' '.READONLY.y:.CLEAR' \
		'AS=$$(AS) $$(AFLAGS)' 'CC=$$(CC) $$(CFLAGS)' \
		'CPIO=$$(CPIO) $$(CPIOFLAGS)' 'F77=$$(F77) $$(FFLAGS)' \
		'INSTALL=$$(INSTALL)' 'LD=$$(LD) $$(LDFLAGS)' \
		'LEX=$$(LEX) $$(LFLAGS)' 'LP=$$(LP)' 'LPFLAGS=$$(LPFLAGS)' \
		'MAKE=$$(MAKE) -$$(MAKEFLAGS)$$(MFLAGS)' 'PR=$$(PR)' \
		'PRFLAGS=$$(PRFLAGS)' 'TAR=$$(TAR)' 'YACC=$$(YACC) $$(YFLAGS)' \
		'* : *.a { $(AR) ru $(<) $$(?) $(ARUPDATE) }' \
		$pass1 $j
done | ${LIBDIR}/mkold2 $pass2
