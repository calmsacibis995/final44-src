"
" Mach Operating System
" Copyright (c) 1989 Carnegie-Mellon University
" All rights reserved.  The CMU software License Agreement specifies
" the terms and conditions for use and redistribution.
"
"
" HISTORY
" $Log:	gmon.ex,v $
" Revision 2.2  89/02/25  20:19:23  gm0w
" 	Changes for cleanup.
" 

"
" @(#)gmon.ex	4.2 (Berkeley) 7/26/83
"
" fix funny things done by mcount()
" fix its name, make it jsb'able, change registers to protect the caller
"
g/_mcount/s//mcount/g
/mcount:/-
/.word/s/.word.*//
/the beginning of mcount()/mark a
/the end of mcount()/mark b
'a,'bs/r11/r5/g
'a,'bs/r10/r4/g
'a,'bs/r9/r3/g
'a,'bs/r8/r2/g
'a,'bs/r7/r1/g
""
"	fix funny name for minbrk used by monstartup() to limit brk()"
g/_minbrk/s//minbrk/g
w
q
