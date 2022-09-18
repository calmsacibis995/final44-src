h57226
s 00001/00001/00082
d D 5.2 90/03/06 19:28:53 bostic 2 1
c the dictionary moved
e
s 00083/00000/00000
d D 5.1 90/03/06 19:28:21 bostic 1 0
c date and time created 90/03/06 19:28:21 by bostic
e
u
U
t
T
I 1
#! /bin/sh

: 'correct: create a spelling correction editor script'
: 'usage:'
:		correct file1 file2 file3 file4 file5
:
: 'list of words in file1 are queried for corrections'
: 'correction script is placed in file2'
: 'file3 gets list of exceptions, sorted'
: 'file4 gets list of questionable corrections'
: 'file5 is name of original source file, for grepping'
:
FIXES=/usr/tmp/$$fixes
QUEST=/usr/tmp/$$quest
EXCEPT=$3
rm -f $2
if [ ! -t 1 ]
then
	exit
fi
D 2
DICT=/usr/dict/words
E 2
I 2
DICT=/usr/share/dict/words
E 2
trap "echo This set of corrections not made.;rm -f $FIXES $QUEST; exit 1"  1 2 15
for WORD in `cat $1`
do
	echo -n $WORD "?"
	read FIX
	RESP=new
	while [ "$RESP" != "ok" ]
	do
		case "$FIX" in

		"&"|"-")
			RESP=ok ;;
		"?"*)
			echo 'Try one of these:'
			grep `expr "$FIX" : "? \(.*\)"` $DICT
			echo -n "$WORD ?"
			read FIX
			RESP=incomplete
			;;
		"^"*|*"$"|*"."*|*"*"*)
			echo 'Try one of these:'
			grep "$FIX" $DICT
			echo -n "$WORD ?"
			read FIX
			RESP=incomplete
			;;
		/)
			grep -w $WORD $5
			echo -n "$WORD ?"
			read FIX
			RESP=incomplete
			;;
		""|"!")
			echo $WORD >> $EXCEPT
			RESP=ok
			;;
		*)
			echo "$FIX" >> $FIXES
			echo "g/\<$WORD\>/s::$FIX:g" >> $2
			RESP=ok
			;;
		esac
	done
done
echo w >> $2
echo q >> $2
if [ -s $FIXES ]
then
	spell <$FIXES >$QUEST
	if [ -s $QUEST ]
	then
		echo "Some questionable corrections:"
		cat $QUEST | sed -e "s/./	&/"
		sort $QUEST -o $4
	else
		echo "Corrections appear ok."
		rm -f $4; touch $4
	fi
	rm -f $FIXES $QUEST
else
	rm -f $4; touch $4;
fi
E 1
