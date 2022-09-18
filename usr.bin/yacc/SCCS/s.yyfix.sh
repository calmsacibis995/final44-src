h05003
s 00006/00000/00039
d D 5.2 90/05/12 19:36:38 bostic 2 1
c pick up debug tables if they're there
e
s 00039/00000/00000
d D 5.1 90/05/12 19:27:28 bostic 1 0
c date and time created 90/05/12 19:27:28 by bostic
e
u
U
t
T
I 1
#!/bin/sh -
#
# Copyright (c) 1990 The Regents of the University of California.
# All rights reserved.
#
# %sccs.include.redist.sh%
#
#	%W% (Berkeley) %G%
#
OLDYACC="yyexca yyact yypact yypgo yyr1 yyr2 yychk yydef"
NEWYACC="yylhs yylen yydefred yydgoto yysindex yyrindex yygindex \
	 yytable yycheck"

file=$1
>$file
shift

if [ $# -eq 0 ] ; then
	if grep yylhs y.tab.c > /dev/null ; then
I 2
		if grep yyname y.tab.c > /dev/null ; then
			NEWYACC="$NEWYACC yyname"
		fi
		if grep yyrule y.tab.c > /dev/null ; then
			NEWYACC="$NEWYACC yyrule"
		fi
E 2
		set $NEWYACC
	else
		set $OLDYACC
	fi
fi

for i
do
ed - y.tab.c << END
/^\(.*\)$i[ 	]*\[]/s//extern \1 $i[];\\
\1 $i []/
.ka
/}/kb
'br $file
'a,.w $file
'a,.d
w
q
END
done
E 1
