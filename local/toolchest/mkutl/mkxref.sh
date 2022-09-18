
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
case $# in
        1) cd $1
           ls *.mk^while read line || break
                        do
                           echo COMMAND: $line
                           make -n -f $line install
                           echo "MANUAL: \c"
                           man -w `echo $line^cut -d"." -f1` 2>/dev/null
                           case $? in
                                   1) echo "*** NOT FOUND";;
                                   esac
                        done^mkxref.pgm $1 1 0 >> $HOME/mkxref.temp
           echo "SYSTEM:`uname` --- LIBRARY:$1 --- `date`">$HOME/mkxref.rpt
           cat $HOME/mkxref.temp>>$HOME/mkxref.rpt
           echo "Report is in $HOME/mkxref.rpt";
           rm $HOME/mkxref.temp;;
        2) cd $1
           ls $2.mk^while read line || break
                        do
                           echo COMMAND: $line
                           make -n -f $line install
                           echo "MANUAL: \c"
                           man -w `echo $line^cut -d"." -f1` 2>/dev/null
                           case $? in
                                   1) echo "*** NOT FOUND";;
                                   esac
                        done^mkxref.pgm $1 1 0 >> $HOME/mkxref.temp
           cat $HOME/mkxref.temp
           rm $HOME/mkxref.temp;;
        *) echo "USAGE: mkxref PATHNAME {command}";;
esac
