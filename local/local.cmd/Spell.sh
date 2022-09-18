#! /bin/sh

: Spell -- make spelling corrections, with help
CAPS='[ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789]'
NAMES="$CAPS"'*$'
for ARG
do case $ARG in
	-n)
	    shift
	    NAMES=""  ;;
	-*)
	    echo Option $ARG not recognized.
	    exit 1   ;;
	*)
	    break    ;;
	esac
done
if [ ! -f $1 ]
then
	echo usage: Spell file
	exit 1
fi
if [ -f .except ]
then
	EX=.except
else
	EX=$HOME/.except
fi
ERRS=/usr/tmp/SpA$$
NEX=/usr/tmp/SpB$$
CORR=/usr/tmp/SpC$$
trap "rm -f $ERRS $NEX $CORR; exit 1" 1 2 15
touch $EX
for FILE
do
	echo $FILE:
	ANS=y
	spell $FILE | sed "/^$CAPS$NAMES/d" | sort | comm -23 - $EX >$ERRS
	while [ `expr "$ANS" : "[Yy].*"` != "0" ]
	do
		if [ -s $ERRS ]
		then
			touch $NEX
			/usr/local/Correct $ERRS $CORR $NEX $ERRS $FILE
			ex $FILE <$CORR >/dev/null
			sort -m $NEX $EX -o $EX
			rm -f $NEX $CORR
		else
			echo Perfection!
			rm -f $ERRS
			break
		fi
		if [ -s $ERRS ]
		then
			echo -n "Try again?"
			read ANS
		else
			ANS=n
		fi
	done
done
rm -f $ERRS
