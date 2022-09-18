: run this script through /bin/sh

# for a non standard base directory, set MANDIR

# set MANOPTS in config/CONFIG.make -- may be one of:
# -bsd42  man<n>/<file>
# -bsd44  cat<n>/thing.0
# -ros    man<n>/<file>			 -- using @(INSTALL)
# -sys5   <a|p|u>_man/man<n>/<file>
# -aix    <a|p|u>_man/man<n>/<file>
# -local  manl/<base>.l
# -l      man<n>/<base>.<n>l
# -hpux   hpux

M=BSD42

if test -z "${MANDIR}"
then
    echo "inst-man: MANDIR not set" 1>&2
    exit 1
fi

if test ! -d ${MANDIR}
then
    echo "inst-man: ${MANDIR} non-existant directory" 1>&2
    exit 1
fi

for A in $*
do
    case $A in
	-bsd42)	M=BSD42
		;;

	-bsd44)	M=BSD44
		;;

	-ros)	M=ROS
		;;

	-local)	M=LOCAL
		;;

	-l)	M=L
		;;

	-sys5)	M=SYS5
		;;

	-aix)	M=AIX
		;;

	-hpux)  M=HPUX
		;;

	-*)	echo "inst-man: $A unknown" 1>&2
		exit 1
		;;

	*)	if test ! -f  $A
		then
		    exit 1
		fi
		F=`basename $A`
		E=`echo $F | @(SED) -e "s%^.*\.\([1-8]\).*%\1%"`

		case $M in
		    BSD42)
			echo @(INSTALL) -m 0644 -c $A ${MANDIR}/man$E/$F
			@(INSTALL) -m 0644 -c $A ${MANDIR}/man$E/$F
			;;

		    BSD44)
			echo "nroff -man $A > ${MANDIR}/cat$E/$F" | \
			@(SED) -e 's%\.\([1-8]\)[1-8cn]*$%.0%' | \
			sh -ve
			;;

		    LOCAL)
			(echo $F | \
			    @(SED) -e "s%.*%@(INSTALL) -m 0644 -c & ${MANDIR}/manl/&%" | \
			    @(SED) -e 's%\.[1-8cn]*$%.l%' | \
			    sh -ve)
			;;

		    L)
			(echo "@(INSTALL) -m 0644 -c $F ${MANDIR}/man$E/$F" | \
			    @(SED) -e 's%\.\([1-8]\)[1-8cn]*$%.\1l%' | \
			    sh -ve)
			;;

		    SYS5|AIX)
			case $E in
			    3)      D=p_man     ;;
			    5)	    D=p_man E=4 ;;
			    8)	    D=a_man E=1 ;;
			    *)	    D=u_man     ;;
			esac
			echo @(INSTALL) -m 0644 -f ${MANDIR}/$D/man$E $A
			@(INSTALL) -m 0644 -f ${MANDIR}/$D/man$E $A
			case $D in
			    a_man)
				F=`basename $A .8c`.1m
				echo @(MV) ${MANDIR}/$D/man$E/$A \
				     ${MANDIR}/$D/man$E/$F
				@(MV) ${MANDIR}/$D/man$E/$A ${MANDIR}/$D/man$E/$F
				;;

			    p_man)
				if [ "$E" = "4" ]; then
				    F=`basename $A .5`.4
				    echo @(MV) ${MANDIR}/$D/man$E/$A \
				         ${MANDIR}/$D/man$E/$F
				    @(MV) ${MANDIR}/$D/man$E/$A \
					 ${MANDIR}/$D/man$E/$F
				fi
				;;
			esac
			;;

		    HPUX)
			case $E in
			    5)  E=4 ;;
			    8)  E=1m ;;
			esac
			echo @(INSTALL) -m 0644 -f ${MANDIR}/man$E $A
			@(INSTALL) -m 0644 -f ${MANDIR}/man$E $A
			case $E in
			    4)  F=`basename $A .5`.4
				echo @(MV) ${MANDIR}/man$E/$A ${MANDIR}/man$E/$F
				@(MV) ${MANDIR}/man$E/$A ${MANDIR}/man$E/$F
				;;

			    1m)	F=`basename $A .8c`.1m
				echo @(MV) ${MANDIR}/man$E/$A ${MANDIR}/man$E/$F
				@(MV) ${MANDIR}/man$E/$A ${MANDIR}/man$E/$F
				;;
			esac
			;;
  
		    ROS)
			echo @(INSTALL) -m 0644 -c $A ${MANDIR}/man$E/$F
			@(INSTALL) -m 0644 -c $A ${MANDIR}/man$E/$F
			;;

		    *)  echo "inst-man: mode botch" 1>&2
			exit 1
			;;
		esac
		;;
    esac
done

exit 0
