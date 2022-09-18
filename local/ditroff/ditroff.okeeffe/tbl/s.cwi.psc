.ds f. samples/sample03
.lf 1 samples/sample03
.nf
.sp 2
.TS
.if \n+(b.=1 .nr d. \n(.c-\n(c.-1
.de 35
.ps \n(.s
.vs \n(.vu
.in \n(.iu
.if \n(.u .fi
.if \n(.j .ad
.if \n(.j=0 .na
..
.nf
.nr #~ 0-5
.nr #| 8
.nr Tw 7.65i
.if \n(.T .if n .nr #~ 60
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.fc
.nr 33 \n(.s
.rm 48 49 50
.nr 48 0
.nr 38 \wfour
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wseven
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wour
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wforth
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wcontinent
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wnation
.if \n(48<\n(38 .nr 48 \n(38
.48
.rm 48
.nr 49 0
.nr 38 \wscore
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wyears
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wfathers
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \won
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wa
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wconceived
.if \n(49<\n(38 .nr 49 \n(38
.49
.rm 49
.nr 50 0
.nr 38 \wand
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \wago
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \wbrought
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \wthis
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \wnew
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \win
.if \n(50<\n(38 .nr 50 \n(38
.50
.rm 50
.nr 38 1n
.nr 47 0
.nr 40 \n(47+(1*\n(38)
.nr 48 +\n(40
.nr 41 \n(48+(3*\n(38)
.nr 49 +\n(41
.nr 42 \n(49+(3*\n(38)
.nr 50 +\n(42
.nr TW \n(50
.nr TW +1*\n(38
.ne 6v+0p
.fc  
.nr #T 0-1
.nr #a 0-1
.nr #a 0-1
.eo
.de T#
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.mk ##
.nr ## -1v
.ls 1
.if \n(#T>=0 .nr #a \n(#T
.if \n(T. .vs \n(.vu-\n(.sp
.if \n(T. \h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.if \n(T. .vs
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|0'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|\n(TWu'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'
.ls
..
.ec
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.mk #a
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'four\h'|\n(41u'score\h'|\n(42u'and
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'seven\h'|\n(41u'years\h'|\n(42u'ago
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'our\h'|\n(41u'fathers\h'|\n(42u'brought
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'forth\h'|\n(41u'on\h'|\n(42u'this
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'continent\h'|\n(41u'a\h'|\n(42u'new
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'nation\h'|\n(41u'conceived\h'|\n(42u'in
.fc
.nr T. 1
.T# 1
.35
.nr #a 0
.TE
.if \n-(b.=0 .nr c. \n(.c-\n(d.-10
.lf 14
.sp 2
.TS
.if \n+(b.=1 .nr d. \n(.c-\n(c.-1
.de 35
.ps \n(.s
.vs \n(.vu
.in \n(.iu
.if \n(.u .fi
.if \n(.j .ad
.if \n(.j=0 .na
..
.nf
.nr #~ 0-5
.nr #| 8
.nr Tw 7.65i
.if \n(.T .if n .nr #~ 60
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.fc
.nr 33 \n(.s
.rm 48 49 50
.nr 48 0
.nr 38 \wAct
.if \n(48<\n(38 .nr 48 \n(38
.nr 31 0
.nr 32 0
.nr 38 \w1
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w1
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w1
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w1
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w2
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w3
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w3
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w10
.if \n(31<\n(38 .nr 31 \n(38
.48
.rm 48
.nr 44 \n(31
.nr 38 \n(44+\n(32
.if \n(38>\n(48 .nr 48 \n(38
.if \n(38<\n(48 .nr 44 +(\n(48-\n(38)/2
.nr 49 0
.nr 38 \wScene
.if \n(49<\n(38 .nr 49 \n(38
.nr 31 0
.nr 32 0
.nr 38 \w2
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w2
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w.1
.if \n(32<\n(38 .nr 32 \n(38
.nr 38 \w4
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w.3
.if \n(32<\n(38 .nr 32 \n(38
.nr 38 \w5
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w5
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w10
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w10
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w2
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w.2
.if \n(32<\n(38 .nr 32 \n(38
.49
.rm 49
.nr 45 \n(31
.nr 38 \n(45+\n(32
.if \n(38>\n(49 .nr 49 \n(38
.if \n(38<\n(49 .nr 45 +(\n(49-\n(38)/2
.nr 50 0
.nr 38 \wLine
.if \n(50<\n(38 .nr 50 \n(38
.nr 31 0
.nr 32 0
.nr 38 \w3
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w3
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w.4
.if \n(32<\n(38 .nr 32 \n(38
.nr 38 \w12
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w19
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w.23
.if \n(32<\n(38 .nr 32 \n(38
.nr 38 \w0
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w.1
.if \n(32<\n(38 .nr 32 \n(38
.nr 38 \wxxx
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \w10
.if \n(31<\n(38 .nr 31 \n(38
.50
.rm 50
.nr 46 \n(31
.nr 38 \n(46+\n(32
.if \n(38>\n(50 .nr 50 \n(38
.if \n(38<\n(50 .nr 46 +(\n(50-\n(38)/2
.nr 38 \wMacbeth-\n(48-3n-\n(49-3n-\n(50
.if \n(38>0 .nr 38 \n(38/2
.if \n(38<0 .nr 38 0
.nr 45 +\n(38/2
.nr 49 +\n(38
.nr 46 +\n(38/2
.nr 50 +\n(38
.nr 38 1n
.nr 47 0
.nr 40 \n(47+(1*\n(38)
.nr 48 +\n(40
.nr 44 +\n(40
.nr 41 \n(48+(3*\n(38)
.nr 49 +\n(41
.nr 45 +\n(41
.nr 42 \n(49+(3*\n(38)
.nr 50 +\n(42
.nr 46 +\n(42
.nr TW \n(50
.nr TW +1*\n(38
.ne 10v+0p
.fc  
.nr #T 0-1
.nr #a 0-1
.nr #c 0-1
.nr #a 0-1
.eo
.de T#
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.mk ##
.nr ## -1v
.ls 1
.if \n(#T>=0 .nr #a \n(#T
.if \n(#T>=0 .nr #c \n(#T
.if \n(T. .vs \n(.vu-\n(.sp
.if \n(T. \h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.if \n(T. .vs
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|0'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#c>=0 .sp -1
.if \n(#c>=0 \h'(|\n(41u+|\n(48u)/2u'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#cu-\n(35u'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#cu+\n(35u'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#c>=0 .sp -1
.if \n(#c>=0 \h'(|\n(42u+|\n(49u)/2u'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#cu-\n(35u'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#cu+\n(35u'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|\n(TWu'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'
.ls
..
.ec
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.mk #a
.ta \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'Macbeth
.mk #c
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'Act\h'|\n(41u'Scene\h'|\n(42u'Line
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(44u \n(45u \n(49u \n(46u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'1\h'|\n(41u'2\h'|\n(42u'3
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(44u \n(45u \n(49u \n(46u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'1\h'|\n(41u'2.1\h'|\n(42u'3.4
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(44u \n(45u \n(49u \n(46u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'1\h'|\n(41u'4.3\h'|\n(42u'12
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(44u \n(45u \n(49u \n(46u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'1\h'|\n(41u'5\h'|\n(42u'19.23
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(44u \n(45u \n(49u \n(46u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'2\h'|\n(41u'5\h'|\n(42u'0.1
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(44u \n(45u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'3\h'|\n(41u'10\h'|\n(42u'xxx
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(44u \n(45u \n(49u \n(46u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'3\h'|\n(41u'10\h'|\n(42u'10
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(44u \n(45u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'10\h'|\n(41u'2.2\h'|\n(42u'
.fc
.nr T. 1
.T# 1
.35
.nr #a 0
.nr #b 0
.TE
.if \n-(b.=0 .nr c. \n(.c-\n(d.-15
.lf 31
.sp
.TS
.if \n+(b.=1 .nr d. \n(.c-\n(c.-1
.de 35
.ps \n(.s
.vs \n(.vu
.in \n(.iu
.if \n(.u .fi
.if \n(.j .ad
.if \n(.j=0 .na
..
.nf
.nr #~ 0-5
.nr #| 8
.nr Tw 7.65i
.if \n(.T .if n .nr #~ 60
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.fc
.nr 33 \n(.s
.rm 48 49 50
.nr 48 0
.nr 38 \wPart
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \whow
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wwhere
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wDescription
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wxxx
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wabc
.if \n(48<\n(38 .nr 48 \n(38
.48
.rm 48
.nr 49 0
.nr 38 \wDate
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wJanuary
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wFebruary
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wMarch
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wyyy
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wdef
.if \n(49<\n(38 .nr 49 \n(38
.49
.rm 49
.nr 50 0
.nr 38 \wUsage
.if \n(50<\n(38 .nr 50 \n(38
.nr 31 0
.nr 32 0
.nr 38 \w250
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w125
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w30
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \w_
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \w200
.if \n(31<\n(38 .nr 31 \n(38
.nr 38 \wZzz
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \w12
.if \n(31<\n(38 .nr 31 \n(38
.50
.rm 50
.nr 46 \n(31
.nr 38 \n(46+\n(32
.if \n(38>\n(50 .nr 50 \n(38
.if \n(38<\n(50 .nr 46 +(\n(50-\n(38)/2
.nr 38 \wBell System JSPEC-\n(48-3n-\n(49-3n-\n(50
.if \n(38>0 .nr 38 \n(38/2
.if \n(38<0 .nr 38 0
.nr 49 +\n(38
.nr 46 +\n(38/2
.nr 50 +\n(38
.nr 38 1n
.nr 47 0
.nr 40 \n(47+(1*\n(38)
.nr 48 +\n(40
.nr 41 \n(48+(3*\n(38)
.nr 49 +\n(41
.nr 42 \n(49+(3*\n(38)
.nr 50 +\n(42
.nr 46 +\n(42
.nr TW \n(50
.nr TW +1*\n(38
.ne 9v+8p
.fc  
.nr #T 0-1
.nr #a 0-1
.nr #c 0-1
.nr #a 0-1
.eo
.de T#
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.mk ##
.nr ## -1v
.ls 1
.if \n(#T>=0 .nr #a \n(#T
.if \n(#T>=0 .nr #c \n(#T
.if \n(T. .vs \n(.vu-\n(.sp
.if \n(T. \h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.if \n(T. .vs
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|0'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#c>=0 .sp -1
.if \n(#c>=0 \h'(|\n(41u+|\n(48u)/2u'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#cu-\n(35u+1p'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#cu+\n(35u-1p'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#c>=0 .sp -1
.if \n(#c>=0 \h'(|\n(42u+|\n(49u)/2u'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#cu-\n(35u+1p'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#cu+\n(35u-1p'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|\n(TWu'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'
.ls
..
.ec
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.mk #a
.ta \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'Bell System JSPEC
.mk #c
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\v'-1p'\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0\v'2p'\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0\v'-1p'
.vs \n(36u
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'Part\h'|\n(41u'Date\h'|\n(42u'Usage
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(48u \n(49u \n(46u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'how\h'|\n(41u'January\h'|\n(42u'250
.ta \n(48u \n(49u \n(46u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'where\h'|\n(41u'February\h'|\n(42u'125
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(48u \n(49u \n(46u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'\h'|\n(41u'\h'|\n(42u'30
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'Description\h'|\n(41u'March\h'|\n(42u'\v'-.5m'\h'(|\n(42u+|\n(49u)/2u'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0\v'+.5m'
.ta \n(48u \n(49u \n(46u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'\h'|\n(41u'\h'|\n(42u'200
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'xxx\h'|\n(41u'yyy\h'|\n(42u'Zzz
.ta \n(48u \n(49u \n(46u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'abc\h'|\n(41u'def\h'|\n(42u'12
.fc
.nr T. 1
.T# 1
.35
.nr #a 0
.nr #b 0
.TE
.if \n-(b.=0 .nr c. \n(.c-\n(d.-18
.lf 51
.sp
.TS
.if \n+(b.=1 .nr d. \n(.c-\n(c.-1
.de 35
.ps \n(.s
.vs \n(.vu
.in \n(.iu
.if \n(.u .fi
.if \n(.j .ad
.if \n(.j=0 .na
..
.nf
.nr #~ 0-5
.nr #| 8
.nr Tw 7.65i
.if \n(.T .if n .nr #~ 60
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.fc
.nr 33 \n(.s
.rm 48 49 50
.nr 48 0
.nr 38 \wAbc
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \w_
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wJK
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wP
.if \n(48<\n(38 .nr 48 \n(38
.48
.rm 48
.nr 49 0
.nr 38 \wDef
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \w_
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wLM
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wQ
.if \n(49<\n(38 .nr 49 \n(38
.49
.rm 49
.nr 50 0
.nr 38 \wGhi
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \wNO
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \wR
.if \n(50<\n(38 .nr 50 \n(38
.50
.rm 50
.nr 38 \wConfusion-\n(48-3n-\n(49-3n-\n(50
.if \n(38>0 .nr 38 \n(38/2
.if \n(38<0 .nr 38 0
.nr 49 +\n(38
.nr 50 +\n(38
.nr 38 1n
.nr 47 0
.nr 40 \n(47+(1*\n(38)
.nr 48 +\n(40
.nr 41 \n(48+(3*\n(38)
.nr 49 +\n(41
.nr 42 \n(49+(3*\n(38)
.nr 50 +\n(42
.nr TW \n(50
.nr TW +1*\n(38
.ne 5v+2p
.fc  
.nr #T 0-1
.nr #a 0-1
.nr #b 0-1
.nr #a 0-1
.eo
.de T#
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.mk ##
.nr ## -1v
.ls 1
.if \n(#T>=0 .nr #a \n(#T
.if \n(#T>=0 .nr #b \n(#T
.if \n(T. .vs \n(.vu-\n(.sp
.if \n(T. \h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.if \n(T. .vs
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|0'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#b>=0 .sp -1
.if \n(#b>=0 \h'(|\n(41u+|\n(48u)/2u'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#bu-\n(35u+1p'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#bu+\n(35u-1p'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|\n(TWu'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'
.ls
..
.ec
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.mk #a
.ta \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'Confusion
.mk #b
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\v'-1p'\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0\v'2p'\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0\v'-1p'
.vs \n(36u
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'Abc\h'|\n(41u'Def\h'(|\n(42u+|\n(49u)/2u'\v'2p'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#bu-\n(35u-1p'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#bu+\n(35u-1p'\v'\n(33p/6u'\h'|\n(42u'Ghi
.ta \n(48u \n(49u \n(50u 
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'\h'|0'\s\n(33\v'-\n(#|n/100u'\l'(|\n(49u+|\n(42u)/2u\(ul'\v'\n(#|n/100u'\s0\h'|\n(41u'\h'|\n(42u'
.vs \n(36u
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'JK\h'|\n(41u'LM\h'|\n(42u'NO
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'P\h'|\n(41u'Q\h'|\n(42u'R
.fc
.nr T. 1
.T# 1
.35
.nr #a 0
.nr #b 0
.TE
.if \n-(b.=0 .nr c. \n(.c-\n(d.-11
.lf 64
.sp
.TS
.if \n+(b.=1 .nr d. \n(.c-\n(c.-1
.de 35
.ps \n(.s
.vs \n(.vu
.in \n(.iu
.if \n(.u .fi
.if \n(.j .ad
.if \n(.j=0 .na
..
.nf
.nr #~ 0-5
.nr #| 8
.nr Tw 7.65i
.if \n(.T .if n .nr #~ 60
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.fc
.nr 33 \n(.s
.rm 48 49 50
.nr 48 0
.nr 38 \wjanuary
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wapril
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wjune
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wseptember
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wnovember
.if \n(48<\n(38 .nr 48 \n(38
.48
.rm 48
.nr 49 0
.nr 38 \wfebruary
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wmay
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wjuly
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \woctober
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wdecember
.if \n(49<\n(38 .nr 49 \n(38
.49
.rm 49
.nr 50 0
.nr 38 \wmarch
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \waugust
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \wjanuary
.if \n(50<\n(38 .nr 50 \n(38
.50
.rm 50
.nr 38 1n
.nr 47 0
.nr 40 \n(47+(1*\n(38)
.nr 48 +\n(40
.nr 41 \n(48+(3*\n(38)
.nr 49 +\n(41
.nr 42 \n(49+(3*\n(38)
.nr 50 +\n(42
.nr TW \n(50
.nr TW +1*\n(38
.ne 5v+0p
.fc  
.nr #T 0-1
.nr #a 0-1
.nr #b 0-1
.nr #a 0-1
.eo
.de T#
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.mk ##
.nr ## -1v
.ls 1
.if \n(#T>=0 .nr #a \n(#T
.if \n(#T>=0 .nr #b \n(#T
.if \n(T. .vs \n(.vu-\n(.sp
.if \n(T. \h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.if \n(T. .vs
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|0'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|\n(TWu'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'
.ls
..
.ec
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.mk #a
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'january\h'|\n(41u'february\h'|\n(42u'march
.ta \n(48u \n(49u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'april\h'|\n(41u'may\h'|\n(42u'\v'-.5m'\h'(|\n(42u+|\n(49u)/2u'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0\v'+.5m'
.mk #b
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'june\h'|\n(41u'july\h'(|\n(42u+|\n(49u)/2u'\v'1v-.5m'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#bu-1v-(.5m)-(1v-.5m)'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#bu+1v+.5m'\v'\n(33p/6u'\h'|\n(42u'august
.ta \n(48u \n(49u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'september\h'|\n(41u'october\h'|\n(42u'\v'-.5m'\h'(|\n(42u+|\n(49u)/2u'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0\v'+.5m'
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'november\h'|\n(41u'december\h'|\n(42u'january
.fc
.nr T. 1
.T# 1
.35
.nr #a 0
.nr #c 0
.TE
.if \n-(b.=0 .nr c. \n(.c-\n(d.-12
.lf 78
.sp
.TS
.if \n+(b.=1 .nr d. \n(.c-\n(c.-1
.de 35
.ps \n(.s
.vs \n(.vu
.in \n(.iu
.if \n(.u .fi
.if \n(.j .ad
.if \n(.j=0 .na
..
.nf
.nr #~ 0-5
.nr #| 8
.nr Tw 7.65i
.if \n(.T .if n .nr #~ 60
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.fc
.nr 33 \n(.s
.rm 48 49 50
.nr 48 0
.nr 38 \wfour
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wseven
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wyears
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wforth
.if \n(48<\n(38 .nr 48 \n(38
.nr 38 \wcontinent
.if \n(48<\n(38 .nr 48 \n(38
.48
.rm 48
.nr 49 0
.nr 38 \wscore
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wago
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \wbrought
.if \n(49<\n(38 .nr 49 \n(38
.nr 38 \won
.if \n(49<\n(38 .nr 49 \n(38
.49
.rm 49
.nr 50 0
.nr 38 \wand
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \wour
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \wthis
.if \n(50<\n(38 .nr 50 \n(38
.nr 38 \wa
.if \n(50<\n(38 .nr 50 \n(38
.50
.rm 50
.nr 38 1n
.nr 47 0
.nr 40 \n(47+(1*\n(38)
.nr 48 +\n(40
.nr 41 \n(48+(3*\n(38)
.nr 49 +\n(41
.nr 42 \n(49+(3*\n(38)
.nr 50 +\n(42
.nr TW \n(50
.nr TW +1*\n(38
.ne 6v+0p
.fc  
.nr #T 0-1
.nr #a 0-1
.nr #b 0-1
.nr #a 0-1
.eo
.de T#
.ds #d .d
.if \(ts\n(.z\(ts\(ts .ds #d nl
.mk ##
.nr ## -1v
.ls 1
.if \n(#T>=0 .nr #a \n(#T
.if \n(#T>=0 .nr #b \n(#T
.if \n(T. .vs \n(.vu-\n(.sp
.if \n(T. \h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.if \n(T. .vs
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|0'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'(|\n(42u+|\n(49u)/2u'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'\h'|\n(TWu'
.if \n(#a>=0 .sp -1
.if \n(#a>=0 \h'|\n(TWu'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#au-1v'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#au+1v'\v'\n(33p/6u'
.ls
..
.ec
.nr 36 \n(.v
.vs \n(.vu-\n(.sp
\h'|0'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0
.vs \n(36u
.mk #a
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'four\h'|\n(41u'score\h'|\n(42u'and
.ta \n(48u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'seven\h'|\n(41u'\v'-.5m'\h'(|\n(41u+|\n(48u)/2u'\s\n(33\v'-\n(#|n/100u'\l'(|\n(49u+|\n(42u)/2u\(ul'\v'\n(#|n/100u'\s0\v'+.5m'\h'|\n(42u'\v'-.5m'\v'-1p'\h'(|\n(42u+|\n(49u)/2u'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0\v'2p'\h'(|\n(42u+|\n(49u)/2u'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0\v'-1p'\v'+.5m'
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'years\h'|\n(41u'ago\h'|\n(42u'our
.ta \n(49u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'\v'-.5m'\v'-1p'\h'|0'\s\n(33\v'-\n(#|n/100u'\l'(|\n(48u+|\n(41u)/2u\(ul'\v'\n(#|n/100u'\s0\v'2p'\h'|0'\s\n(33\v'-\n(#|n/100u'\l'(|\n(48u+|\n(41u)/2u\(ul'\v'\n(#|n/100u'\s0\v'-1p'\v'+.5m'\h'|\n(41u'brought\h'|\n(42u'\v'-.5m'\h'(|\n(42u+|\n(49u)/2u'\s\n(33\v'-\n(#|n/100u'\l'|\n(TWu\(ul'\v'\n(#|n/100u'\s0\v'+.5m'
.mk #b
.ta \n(48u \n(49u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'forth\h'(|\n(41u+|\n(48u)/2u'\v'1v-.5m'\s\n(33\v'-\n(33p/6u'\h'-\n(#~n/100u'\L'|\n(#bu-1v-(.5m)-(1v-.5m)-1p'\h'-\n(#~n/100u'\s0\v'\n(\*(#du-\n(#bu+1v+.5m+1p'\v'\n(33p/6u'\h'|\n(41u'on\h'|\n(42u'this
.ta \n(48u \n(50u 
.nr 31 \n(.f
.nr 35 1m
\&\h'|\n(40u'continent\h'|\n(41u'\v'-.5m'\h'(|\n(41u+|\n(48u)/2u'\s\n(33\v'-\n(#|n/100u'\l'(|\n(49u+|\n(42u)/2u\(ul'\v'\n(#|n/100u'\s0\v'+.5m'\h'|\n(42u'a
.fc
.nr T. 1
.T# 1
.35
.nr #a 0
.nr #e 0
.TE
.if \n-(b.=0 .nr c. \n(.c-\n(d.-14
.lf 94
