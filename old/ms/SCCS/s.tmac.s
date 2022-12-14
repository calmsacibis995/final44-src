h47599
s 00001/00001/01027
d D 5.2 91/10/07 21:05:51 cael 9 8
c modify pathname
e
s 00003/00000/01025
d D 5.1 91/04/17 15:42:54 bostic 8 7
c new copyright; att/bsd/shared
e
s 00004/00004/01021
d D 1.6 90/06/02 17:47:48 karels 7 5
c reorg; insert keyworks
e
s 00001/00001/01024
d R 1.6 90/06/02 17:35:49 karels 6 5
c version distributed with 4.3BSD, dated Jun 23, 1983
e
s 00115/00031/00910
d D 1.5 90/06/02 16:58:40 karels 5 4
c currently installed version, dated 5/11/88:
c ditroff merged, provision for local macros (.LT, .HE), rename included files,
c fixes in keep handling; fixes for non-arabic page 1;
c remove CAT dependencies, remove cutmarks unless forced; fix footnote/ref
c conflicts; add ideal/grn/pic macros; fixes in diacrit.; new .UX
e
s 00002/00002/00939
d D 1.4 90/06/02 16:34:49 karels 4 3
c version distributed with 4.3BSD, dated Jan 11, 1986
e
s 00561/01186/00380
d D 1.3 90/06/02 16:24:52 karels 3 2
c version distributed with 4.2BSD, dated Jul 10, 1983
c (new version from Bill Tuthill, UCB Computer Center)
e
s 00000/00001/01566
d D 1.2 90/05/31 21:51:26 karels 2 1
c macros distributed with 4.1BSD, dated May 3, 1980
e
s 01567/00000/00000
d D 1.1 90/05/31 21:43:58 karels 1 0
c from 32/V, dated Nov 27, 78
e
u
U
f b 
t
T
I 8
.\" %sccs.include.proprietary.roff%
.\"
E 8
I 5
D 7
.\"	@(#)tmac.s	1.5 (Berkeley) 5/11/88
E 7
I 7
.\"	%W% (Berkeley) %G%
I 8
.\"
E 8
E 7
.\" ancillary files reside in \*(//,
.\" except local which are in \*(L/,
E 5
I 1
D 3
.nr TN 0
.\"	RT -  reset everything to normal state
.de RT
.if !\\n(1T .BG
.if !\\n(IK .if !\\n(IF .if !\\n(IX .if !\\n(BE .di
.ce 0
.ul 0
.if \\n(NX<=1 .if \\n(AJ=0 .ll \\n(LLu
.if \\n(IF=0 \{\
.	ps \\n(PS
.	if \\n(VS>=40 .vs \\n(VSu
.	if \\n(VS<=39 .vs \\n(VSp\}
.if \\n(IP .in -\\n(I\\n(IRu
.if \\n(IP=0 .nr I0 \\n(PIu
.if \\n(IP .nr IP -1
.if \\n(QP \{\
.	ll +\\n(QIu
.	in -\\n(QIu
.	nr QP -1\}
.ft 1
.bd 1
.ta 5n 10n 15n 20n 25n 30n 35n 40n 45n 50n 55n 60n 65n 70n 75n 80n
.fi
..
.	\"IZ - initialization
E 3
I 3
D 7
.ds // /usr/lib/ms/
E 7
I 7
D 9
.ds // /usr/share/ms/
E 9
I 9
.ds // /usr/old/lib/ms/
E 9
E 7
I 5
.ds L/ /usr/local/lib/tmac/
E 5
.	\" IZ - initialize (before text begins)
E 3
.de IZ
D 3
.if \\n(FM=0 .nr FM 1i
E 3
I 3
.nr FM 1i
E 3
.nr YY -\\n(FMu
.nr XX 0 1
.nr IP 0
.nr PI 5n
.nr QI 5n
I 3
.nr FI 2n
E 3
.nr I0 \\n(PIu
I 3
.if n .nr PD 1v
.if t .nr PD .3v
.if n .nr DD 1v
.if t .nr DD .5v
E 3
.nr PS 10
.nr VS 12
D 3
.if !\\n(PD .if n .nr PD 1v
.if !\\n(PD .if t .nr PD 0.3v
.nr ML 3v
E 3
.ps \\n(PS
D 3
.if \\n(VS>40 .vs \\n(VSu
.if \\n(VS<=39 .vs \\n(VSp
E 3
I 3
.vs \\n(VSp
.nr ML 3v
E 3
.nr IR 0
.nr TB 0
.nr SJ \\n(.j
I 3
.nr PO \\n(.o
E 3
.nr LL 6i
.ll \\n(LLu
D 3
.nr LT \\n(.l
.lt \\n(LTu
E 3
I 3
.lt 6i
E 3
.ev 1
D 3
.nr FL \\n(LLu*11u/12u
E 3
I 3
.nr FL 5.5i
E 3
.ll \\n(FLu
.ps 8
.vs 10p
.ev
D 3
.if \\*(CH .ds CH "\(hy \\\\n(PN \(hy
.if n .ds CF "\\*(DY
E 3
I 3
.ds CH - \\\\n(PN -
.if n .ds CF \\*(DY
E 3
.wh 0 NP
.wh -\\n(FMu FO
.ch FO 16i
.wh -\\n(FMu FX
.ch FO -\\n(FMu
.wh -\\n(FMu/2u BT
..
D 3
.de TM
.if \\n(IM=0 .if \\n(MN=0 .pn 0
.so /usr/lib/tmac/tmac.scover
.if \\n(IM=0 .if \\n(MN=0 .rm IM
.if \\n(IM=0 .if \\n(MN=0 .rm MF
.if \\n(IM=0 .if \\n(MN=0 .rm MR
.if \\n(.T=0 .pi /usr/bin/col
.nr ST 1
.ds QF MEMORANDUM FOR FILE
.br
.ds MN \\$1
.if !"\\$1"" .nr MM 1
.if !"\\$2"" .nr MC 1
.if !"\\$3"" .nr MG 1
.nr TN 1
.if \\n(.$-1 .ds CA \\$2
.if \\n(.$-2 .ds CC \\$3
.rm RP
.rm S0
.rm S2
.rm AX
E 3
I 3
.	\" RT - reset (at new paragraph)
.de RT
.if !\\n(1T .BG
.if !\\n(IK .if !\\n(IF .if !\\n(IX .if !\\n(BE .di
.if \\n(TM .ls 2
.ce 0
.ul 0
.if \\n(QP \{\
.	ll +\\n(QIu
.	in -\\n(QIu
.	nr QP -1
.\}
.if \\n(NX<=1 .if !\\n(AJ .ll \\n(LLu
.if !\\n(IF \{\
.	ps \\n(PS
.	if \\n(VS>=40 .vs \\n(VSu
.	if \\n(VS<=39 .vs \\n(VSp
.\}
.if !\\n(IP .nr I0 \\n(PIu
.if \\n(IP \{\
.	in -\\n(I\\n(IRu
.	nr IP -1
.\}
.ft 1
.TA
.fi
E 3
..
D 3
.		\" IM - internal memorandum
.de IM
.nr IM 1
.TM "\\$1" "\\$2" "\\$3"
.rm QF
.RA
.rm RA
.rm RP
.rm MF
.rm MR
E 3
I 3
.	\" TA - set default tabs
.de TA
.if n .ta 8n 16n 24n 32n 40n 48n 56n 64n 72n 80n
.if t .ta 5n 10n 15n 20n 25n 30n 35n 40n 45n 50n 55n 60n 65n 70n 75n
E 3
..
D 3
.		\" MF - memorandum for file.
.de MF
.nr MN 1
.TM "\\$1" "\\$2" "\\$3"
.rm MR
.rm IM
.RA
.rm RA
.rm RP
.rm TM
..
.		\" MR - memo for record
.de MR
.nr MN 2
.TM "\\$1" "\\$2" "\\$3"
.ds QF MEMORANDUM FOR RECORD
.rm MF
.RA
.rm RA
.rm RP
.rm IM
.rm TM
..
.de EG
.nr MN 3
.TM "\\$1" "\\$2" "\\$3"
.ds QF ENGINEER'S NOTES
.rm MF
.rm RP
.rm IM
.RA
.rm RA
.rm TM
..
.de OK
E 3
I 3
.	\" BG - begin (at first paragraph)
.de BG
E 3
.br
I 3
.nr YE 1
E 3
.di
D 3
.di OD
..
.de RP
.nr ST 2
.pn 0
.rm SG
.rm CS
.rm TM
.rm QF
.rm IM
.rm MR
.rm MF
.rm EG
.br
..
.de TR \" Comp. Sci. Tech Rept series.
.nr ST 3
.pn 0
.ds MN \\$1
.rm SG
.rm CS
.rm TM
.rm QF
.rm IM
.rm MR
.rm MF
.rm EG
.br
..
.	\"TL - title and initialization
E 3
I 3
.ce 0
.nr KI 0
.hy 14
.nr 1T 1
.S\\n(ST
.rm S0 S1 S2 SY TX AX WT RP
.\"redefs
E 3
.de TL
D 3
.br
.nr TV 1
.if \\n(IM>0 .rm CS
.if \\n(MN>0 .rm CS
.ME
.rm ME
.di WT
.nr SJ \\n(.j
.na
.fi
.ll 5.0i
.if n .if \\n(TN .ll 30
.if t .if \\n(TN .ll 3.5i
E 3
.ft 3
D 3
.ps 10
.if !\\n(TN .ps 12
.if !\\n(TN .rm CS
.hy 0
..
.de TX
.rs
.sp .5i
.ce 1000
.if n .ul 1000
.ps 12
.ft 3
.vs 15p
.ne 4
.hy 0
.WT
.hy 14
.ce 0
.ul 0
..
.	\"	AU - author(s)
E 3
I 3
.ce 99
.sp
.LG
\\..
E 3
.de AU
D 3
.nr AV 1
.ad \\n(SJ
.br
.di
.br
.nf
.nr NA +1
.ds R\\n(NA \\$1
.ds E\\n(NA \\$2
.di A\\n(NA
.ll \\n(LLu
.if \\n(TN=0 .if t .ft 2
.if \\n(TN=0 .if n .ft 1
.if \\n(TN>0 .ft 3
.if \\n(TN .if n .ll 16
.if \\n(TN .if t .ll 1.4i
.ps 10
..
.de AX
.ft 1
.rs
.ce 1000
E 3
I 3
.ft 2
E 3
.if n .ul 0
D 3
.ps 10
.vs 12p
.if n .sp 2
.if t .sp
.A1
.if n .sp 
.if t .sp 0.5
.ns
.I1
.if \\n(NA-1 .if n .sp 2
.if \\n(NA-1 .if t .sp
.A2
.if \\n(NA-1 .if n .sp
.if \\n(NA-1 .if t .sp 0.5
.ns
.I2
.if \\n(NA-2 .if t .sp
.if \\n(NA-2 .if n .sp 2
.A3
.if \\n(NA-2 .if t .sp 0.5
.if \\n(NA-2 .if n .sp
.ns
.I3
.if \\n(NA-3 .if t .sp
.if \\n(NA-3 .if n .sp 2
.A4
.if \\n(NA-3 .if t .sp 0.5
.if \\n(NA-3 .if n .sp
.ns
.I4
.if \\n(NA-4 .if t .sp
.if \\n(NA-4 .if n .sp 2
.A5
.if \\n(NA-4 .if n .sp
.if \\n(NA-4 .if t .sp 0.5
.ns
.I5
.if \\n(NA-5 .if t .sp
.if \\n(NA-5 .if n .sp 2
.A6
.if \\n(NA-5 .if n .sp
.if \\n(NA-5 .if t .sp 0.5
.ns
.I6
.if \\n(NA-6 .if t .sp
.if \\n(NA-6 .if n .sp 2
.A7
.if \\n(NA-6 .if n .sp
.if \\n(NA-6 .if t .sp 0.5
.ns
.I7
.if \\n(NA-7 .if t .sp
.if \\n(NA-7 .if n .sp 2
.A8
.if \\n(NA-7 .if n .sp
.if \\n(NA-7 .if t .sp 0.5
.ns
.I8
.if \\n(NA-8 .if t .sp
.if \\n(NA-8 .if n .sp 2
.A9
.if \\n(NA-8 .if n .sp
.if \\n(NA-8 .if t .sp 0.5
.ns
.I9
..
.	\"AI - authors institution
E 3
I 3
.ce 99
.sp
.NL
\\..
E 3
.de AI
D 3
.br
E 3
.ft 1
D 3
.di
.di I\\n(NA
E 3
I 3
.if n .ul 0
.ce 99
.if n .sp
.if t .sp .5
.NL
\\..
.RA
.rn FJ FS
.rn FK FE
E 3
.nf
I 3
.ev 1
.ps \\n(PS-2
.vs \\n(.s+2p
.ev
.if !\\n(KG .nr FP 0
.nr KG 0
.if \\n(FP \{\
.	FS
.	FG
.	FE
.\}
.br
.if \\n(TV .if n .sp 2
.if \\n(TV .if t .sp 1
.fi
.ll \\n(LLu
E 3
..
D 3
.	\"AB - begin an abstract
E 3
I 3
.	\" RA - redefine abstract
.de RA
E 3
.de AB
.br
D 3
.di
.ul 0
.ce 0
.nr 1T 1
.nr IK 1
.nr KI 1
.di WB
.rs
E 3
I 3
.if !\\n(1T .BG
.ce
.sp
.if !\\n(.$ ABSTRACT
.if \\n(.$ .if !\\$1no \\$1
.if !\\n(.$ .sp
.if \\n(.$ .if !\\$1no .sp
.sp
E 3
.nr AJ 1
D 3
.ce 1
.ft 2
.if n .ul
.ll \\n(LLu
.if \\n(.$=0 ABSTRACT
.if \\n(.$>0 .if !"\\$1"-" .if !"\\$1"no"  \\$1
.if \\n(.$=0 .sp
.if \\n(.$>0 .if !"\\$1"-" .if !"\\$1"no" .sp
.hy 14
.ul 0
.ce 0
.fi
.ft 1
.nr OJ \\n(.i
E 3
.in +\\n(.lu/12u
.ll -\\n(.lu/12u
D 3
.br
.ps \\n(PS
.if \\n(VS>40 .vs \\n(VSu
.if \\n(VS<=39 .vs \\n(VSp
.ti +\\n(PIu
..
.	\"AE - end of an abstract
E 3
I 3
.RT
.if \\n(TM .ls 1
\\..
E 3
.de AE
I 3
.nr AJ 0
E 3
.br
D 3
.di
E 3
I 3
.in 0
E 3
.ll \\n(LLu
D 3
.ps \\n(PS
.if \\n(VS>40 .vs \\n(VSu
E 3
I 3
.if \\n(VS>=40 .vs \\n(VSu
E 3
.if \\n(VS<=39 .vs \\n(VSp
D 3
.nr 1T 0
.nr IK 0
.in \\n(OJu
.nr AJ 0
.di
.ce 0
.if \\n(ST=2 .SY
.if \\n(ST<3 .rm SY
E 3
I 3
.if \\n(TM .ls 2
\\..
E 3
..
D 3
.	\"S2 - release paper style
.	\"SY - cover sheet of released paper
.de SY
.ll \\n(LLu
.ns
.if \\n(TV .TX
.if \\n(AV .AX
.rs
.ce 0
.nf
.sp 3
.ls 1
.WB
.ls 
.sp 3v
\\*(DY
.sp |9i
.if \\n(FP>0 .FA
.FG
.if \\n(GA=1 .nr GA 2
.fi
..
.	\"S2 - first text page, released paper format
.de S2
.ce 0
E 3
I 3
.	\" RP - released paper format
.de RP
.nr ST 2
.if \\$1no .nr ST 1
.pn 0
E 3
.br
D 3
.SY
.rm SY
.bp 1
.if \\n(TV .TX
.if \\n(AV .AX
.rs
.ce 0
.ft 1
.ad \\n(SJ
E 3
..
D 3
.	\"S0- mike lesk conserve paper style
.de S0
.ce 0
.br
.ll \\n(LLu
.if \\n(TV+\\n(AV>0 .ns
.if \\n(TV .TX
.if \\n(AV .AX
.if \\n(TV+\\n(AV>0 .rs
.ce 0
.if \\n(TV>0 .sp 2
.ls 1
.if \\n(FP>0 \{\
.	FJ
.	nf
.	FG
.	fi
.	FK
.	nr FP 0\}
.nf
.WB
.ls
.fi
.ad \\n(SJ
E 3
I 3
.	\" TL - source file for cover sheet
.de TL
.rn TL @T
D 5
.so \*(//s.cov
E 5
I 5
.so \*(//cov.ms
E 5
.TL
.rm @T
E 3
..
D 3
.	\"S3 - CSTR style
.de S3
.rs
.sp |2.25i
.ce 1000
.I1
.if \\n(NA>1 .sp .5
.if \\n(NA>1 .I2
.if \\n(NA>2 .sp .5
.if \\n(NA>2 .I3
.if \\n(NA>3 .sp .5
.if \\n(NA>3 .I4
.if \\n(NA>4 .sp .5
.if \\n(NA>4 .I5
.if \\n(NA>5 .sp .5
.if \\n(NA>5 .I6
.if \\n(NA>6 .sp .5
.if \\n(NA>6 .I7
.if \\n(NA>7 .sp .5
.if \\n(NA>7 .I8
.if \\n(NA>8 .sp .5
.if \\n(NA>8 .I9
.sp |4i
.	\"check how long title is: can space extra .25 inch if short
.di EZ
.WT
.di
.if \\n(dn<1.5v .if \\n(NA=1 .sp .25i
.ft 1
Computing Science Technical Report No. \\*(MN
.sp
.if t .ft 3
.if n .ul 100
.ps 12
.vs 15p
.hy 0
.WT
.hy 14
.ft 1
.if n .ul 0
.ps 10
.vs 12p
.sp
.ft 1
.A1
.A2
.A3
.A4
.A5
.A6
.A7
.A8
.A9
.ce 0
.sp |8.5i
.ce 0
\\*(DY
.bp 0
.ft 1
.S2
E 3
I 3
.	\" PP - regular paragraph
.de PP
.RT
.if \\n(1T .sp \\n(PDu
.ne 1.1
.ti +\\n(PIu
..
.	\" LP - left paragraph
.de LP
.RT
.if \\n(1T .sp \\n(PDu
.ne 1.1
.ti \\n(.iu
..
.	\" IP - indented paragraph
.de IP
.RT
.if \\n(1T .sp \\n(PDu
.ne 1.1
.if !\\n(IP .nr IP +1
.if \\n(.$-1 .nr I\\n(IR \\$2n
.in +\\n(I\\n(IRu
.ta \\n(I\\n(IRu
.if \\n(.$ \{\
.ds HT \&\\$1
.ti -\\n(I\\n(IRu
\\*(HT\t\c
D 7
.if \w'\\*(HT'u>(\\n(I\\n(IRu+1n) .br
E 7
I 7
.if \w\\*(HTu>(\\n(I\\n(IRu+1n) .br
E 7
.\}
E 3
..
D 3
.	\"SG - signature
.de SG
.br
.KS
.in +2u*\\n(.lu/3u
.sp 2
.A1
.if \\n(NA-1 .sp 2
.A2
.if \\n(NA-2 .sp 2
.A3
.if \\n(NA-3 .sp 2
.A4
.if \\n(NA-4 .sp 2
.A5
.if \\n(NA>5 .sp 2
.A6
.if \\n(NA>6 .sp 2
.A7
.if \\n(NA>7 .sp 2
.A8
.if \\n(NA>8 .sp 2
.A9
.in
.nf
.sp -1
.if \\n(.$>=1 \\$1
.if \\n(.$>=2 \\$2
.if \\n(.$>=3 \\$3
.if \\n(.$>=4 \\$4
.if \\n(.$>=5 \\$5
.if \\n(.$>=6 \\$6
.if \\n(.$>=7 \\$7
.if \\n(.$>=8 \\$8
.if \\n(.$>=9 \\$9
.fi
.br
.KE
E 3
I 3
.	\" XP - exdented paragraph
.de XP
.RT
.if \\n(1T .sp \\n(PDu
.ne 1.1
.if !\\n(IP .nr IP +1
.in +\\n(I\\n(IRu
.ti -\\n(I\\n(IRu
E 3
..
D 3
.	\"Tables.  TS - table start, TE - table end
.de TS
.br
.if !\\n(1T .RT
.ul 0
E 3
I 3
.	\" QP - quote paragraph
.de QP
E 3
.ti \\n(.iu
D 3
.if t .sp 0.5
.if n .sp
.if \\$1H .TQ
.nr IX 1
E 3
I 3
.RT
.if \\n(1T .sp \\n(PDu
.ne 1.1
.nr QP 1
.in +\\n(QIu
.ll -\\n(QIu
.ti \\n(.iu
.if \\n(TM .ls 1
E 3
..
D 3
.de TQ
.di TT
.nr IT 1
E 3
I 3
.	\" SH - section header
.de SH
.ti \\n(.iu
.RT
.if \\n(1T .sp
.RT
.ne 3.1
.B
E 3
..
D 3
.de TH
.if \\n(.d>0.5v .nr T. 0
.if \\n(.d>0.5v .T# 0
.di
.nr TQ \\n(.i
.nr HT 1
.in 0
.TT
.in \\n(TQu
.mk #T
E 3
I 3
.	\" NH - numbered header
.de NH
.SH
.nr NS \\$1
.if !\\n(.$ .nr NS 1
.if !\\n(NS .nr NS 1
.nr H\\n(NS +1
.if !\\n(NS-4 .nr H5 0
.if !\\n(NS-3 .nr H4 0
.if !\\n(NS-2 .nr H3 0
.if !\\n(NS-1 .nr H2 0
.if !\\$1 .if \\n(.$ .nr H1 1
.if \\$1S \{\
.	nr NS \\n(.$-1
.	nr H1 \\$2
.	nr H2 \\$3
.	nr H3 \\$4
.	nr H4 \\$5
.	nr H5 \\$6
.\}
.ds SN \\n(H1.
.if \\n(NS-1 .as SN \\n(H2.
.if \\n(NS-2 .as SN \\n(H3.
.if \\n(NS-3 .as SN \\n(H4.
.if \\n(NS-4 .as SN \\n(H5.
\\*(SN
E 3
..
D 3
.de TE
.nr IX 0
.if \\n(IT>0 .if \\n(HT=0 .di
.if \\n(IT>0 .if \\n(HT=0 .nr EF \\n(.u
.if \\n(IT>0 .if \\n(HT=0 .nf
.if \\n(IT>0 .if \\n(HT=0 .TT
.if \\n(IT>0 .if \\n(HT=0 .if \\n(EF>0 .fi
.nr IT 0
.nr HT 0
.if n .sp 1
.if t .sp 0.5
.rm a+ b+ c+ d+ e+ f+ g+ h+ i+ j+ k+ l+ n+ m+
.rr 32 33 34 35 36 37 38 40 79 80 81 82
.rr a| b| c| d| e| f| g| h| i| j| k| l| m|
.rr a- b- c- d- e- f- g- h- i- j- k- l- m-
..
.	\"DS - display.  If .DS C, center; L, left-adjust; I, indent.
E 3
I 3
.	\" DS - display with keep (L=left I=indent C=center B=block)
E 3
.de DS
D 3
.XD
E 3
.KS
.nf
.\\$1D \\$2 \\$1
.ft 1
.ps \\n(PS
D 3
.if \\n(VS>40 .vs \\n(VSu
E 3
I 3
.if \\n(VS>=40 .vs \\n(VSu
E 3
.if \\n(VS<=39 .vs \\n(VSp
..
.de D
.ID \\$1
..
D 3
.de CD
.ce 1000
..
E 3
I 3
.	\" ID - indented display with no keep
E 3
.de ID
D 3
.if t .in +0.5i
E 3
I 3
.XD
.if t .in +.5i
E 3
.if n .in +8
D 3
.if \\n(.$ .if !"\\$1"I" .in \\n(OIu
.if \\n(.$ .if !"\\$1"I" .in +\\$1n
E 3
I 3
.if \\n(.$ .if !\\$1I .if !\\$1 \{\
.	in \\n(OIu
.	in +\\$1n
.\}
E 3
..
I 3
.	\" LD - left display with no keep
E 3
.de LD
I 3
.XD
E 3
..
I 3
.	\" CD - centered display with no keep
.de CD
.XD
.ce 999
..
.	\" XD - real display macro
E 3
.de XD
.nf
.nr OI \\n(.i
D 3
.if t .sp 0.5
.if n .sp 1
E 3
I 3
.sp \\n(DDu
.if \\n(TM .ls 1
E 3
..
D 3
.de BD \" block display: save everything, then center it.
.nr BD 1
.nf
.di DD
..
.	\"DE - display end
E 3
I 3
.	\" DE - end display of any kind
E 3
.de DE
.ce 0
D 3
.if \\n(BD>0 .DF
E 3
I 3
.if \\n(BD .DF
E 3
.nr BD 0
D 3
.KE
E 3
.in \\n(OIu
D 3
.if t .sp 0.5
.if n .sp 1
E 3
I 3
.KE
.if \\n(TM .ls 2
.sp \\n(DDu
E 3
.fi
..
D 3
.de DF \" finish a block display to be recentered.
E 3
I 3
.	\" BD - block display: center entire block
.de BD
.XD
.nr BD 1
.nf
.in \\n(OIu
.di DD
..
.	\" DF - finish block display
.de DF
E 3
.di
.if \\n(dl>\\n(BD .nr BD \\n(dl
.if \\n(BD<\\n(.l .in (\\n(.lu-\\n(BDu)/2u
.nr EI \\n(.l-\\n(.i
.ta \\n(EIuR
.DD
.in \\n(OIu
..
D 3
.	\"KS keep - for keep release features. As in IFM
E 3
I 3
.	\" KS - begin regular keep
E 3
.de KS
.nr KN \\n(.u
D 3
.if \\n(IK=0 .if \\n(IF=0 .KQ
E 3
I 3
.if !\\n(IK .if !\\n(IF .KQ
E 3
.nr IK +1
..
D 3
.	\"KQ - real keep processor
E 3
I 3
.	\" KQ - real keep processor
E 3
.de KQ
.br
.nr KI \\n(.i
.ev 2
I 3
.TA
E 3
.br
.in \\n(KIu
.ps \\n(PS
D 3
.if \\n(VS>40 .vs \\n(VSu
E 3
I 3
.if \\n(VS>=40 .vs \\n(VSu
E 3
.if \\n(VS<=39 .vs \\n(VSp
.ll \\n(LLu
.lt \\n(LTu
.if \\n(NX>1 .ll \\n(CWu
.if \\n(NX>1 .lt \\n(CWu
.di KK
.nr TB 0
..
D 3
.	\"KF - floating keep
E 3
I 3
.	\" KF - begin floating keep
E 3
.de KF
.nr KN \\n(.u
.if !\\n(IK .FQ
.nr IK +1
..
D 3
.	\"FQ real floating keep processor
E 3
I 3
.	\" FQ - real floating keep processor
E 3
.de FQ
.nr KI \\n(.i
.ev 2
I 3
.TA
E 3
.br
.in \\n(KIu
.ps \\n(PS
D 3
.if \\n(VS>40 .vs \\n(VSu
E 3
I 3
.if \\n(VS>=40 .vs \\n(VSu
E 3
.if \\n(VS<=39 .vs \\n(VSp
.ll \\n(LLu
.lt \\n(LTu
.if \\n(NX>1 .ll \\n(CWu
.if \\n(NX>1 .lt \\n(CWu
.di KK
.nr TB 1
..
D 3
.	\"KE release - everything between keep and release is together
E 3
I 3
.	\" KE - end keep
E 3
.de KE
D 3
.if \\n(IK .if !\\n(IK-1 .if \\n(IF=0 .RQ
E 3
I 3
.if \\n(IK .if !\\n(IK-1 .if !\\n(IF .RQ
E 3
.if \\n(IK .nr IK -1
..
D 3
.	\"RQ real release
E 3
I 3
.	\" RQ - real keep release
E 3
.de RQ
.br
.di
.nr NF 0
.if \\n(dn-\\n(.t .nr NF 1
.if \\n(TC .nr NF 1
.if \\n(NF .if !\\n(TB .sp 200
.if !\\n(NF .if \\n(TB .nr TB 0
.nf
.rs
.nr TC 5
.in 0
.ls 1
D 3
.if \\n(TB=0 .ev
.if \\n(TB=0 .br
.if \\n(TB=0 .ev 2
.if \\n(TB=0 .KK
E 3
I 3
.if !\\n(TB \{\
.	ev
.	br
.	ev 2
.	KK
I 5
.	rm KK
E 5
.\}
E 3
.ls
.ce 0
D 3
.if \\n(TB=0 .rm KK
E 3
I 3
D 5
.if !\\n(TB .rm KK
E 5
E 3
.if \\n(TB .da KJ
.if \\n(TB \!.KD \\n(dn
.if \\n(TB .KK
.if \\n(TB .di
.nr TC \\n(TB
.if \\n(KN .fi
.in
.ev
..
D 3
.de EQ  \"equation, breakout and display
.nr EF \\n(.u
.rm EE
.nr LE 1	\" 1 is center
.ds EL \\$1
.if "\\$1"L" .ds EL \\$2
.if "\\$1"L" .nr LE 0
.if "\\$1"C" .ds EL \\$2
.if "\\$1"I" .nr LE 0
.if "\\$1"I" .ds EE \\h'|10n'
.if "\\$1"I" .if !"\\$3"" .ds EE \\h'\\$3'
.if "\\$1"I" .ds EL \\$2
.if \\n(YE>0 .nf
.di EZ
E 3
I 3
.	\" KD - keep redivert
.de KD
.nr KM 0
.if \\n(.zKJ .nr KM 1
.if \\n(KM \!.KD \\$1
.if !\\n(KM .if \\n(.t<\\$1 .di KJ
E 3
..
D 3
.de EN  \" end of a displayed equation
E 3
I 3
.	\" EM - end macro (process leftover keep)
.de EM
E 3
.br
D 3
.di
.rm EZ
.nr ZN \\n(dn
.if \\n(ZN>0 .if \\n(YE=0 .LP
.if \\n(ZN=0 .if !"\\*(EL"" .nr ZN 1
.if "\\n(.z"" .if \\n(ZN>0 .if !\\n(nl=\\n(PE .if t .sp .5
.if "\\n(.z"" .if \\n(ZN>0 .if !\\n(nl=\\n(PE .if n .sp 1
.if !"\\n(.z"" .if \\n(ZN>0 .if !\\n(.d=\\n(PE .if t .sp .5
.if !"\\n(.z"" .if \\n(ZN>0 .if !\\n(.d=\\n(PE .if n .sp 1
.pc
.if \\n(BD>0 .nr LE 0 \" can't mean centering in this case.
.if \\n(MK>0 .if \\n(LE=1 .ds EE \\h'|10n'
.if \\n(MK>0 .nr LE 0 \" don't center if mark/lineup
.lt \\n(.lu
.if \\n(EP=0 .if \\n(ZN>0 .if \\n(LE>0 .tl \(ts\(ts\\*(10\(ts\\*(EL\(ts
.if \\n(EP=0 .if \\n(ZN>0 .if \\n(LE=0 .if \\n(BD=0 .tl \(ts\\*(EE\\*(10\(ts\(ts\\*(EL\(ts
.if \\n(EP=0 .if \\n(ZN>0 .if \\n(LE=0 .if \\n(BD>0 .if \\n(BD<\\w\(ts\\*(10\(ts .nr BD \\w\(ts\\*(10\(ts
.if \\n(EP=0 .if \\n(ZN>0 .if \\n(LE=0 .if \\n(BD>0 \!\\*(10\\t\\*(EL
.if \\n(EP>0 .if \\n(ZN>0 .if \\n(LE>0 .tl \(ts\\*(EL\(ts\\*(10\(ts\(ts
.if \\n(EP>0 .if \\n(ZN>0 .if \\n(LE=0 .if \\n(BD=0 .tl \(ts\\*(EL\\*(EE\\*(10\(ts\(ts\(ts
.if \\n(EP>0 .if \\n(ZN>0 .if \\n(LE=0 .if \\n(BD>0 .if \\n(BD<\\w\(ts\\*(10\(ts .nr BD \\w\(ts\\*(10\(ts
.if \\n(EP>0 .if \\n(ZN>0 .if \\n(LE=0 .if \\n(BD>0 \!\\h'-\\\\n(.iu'\\*(EL\\h'|0'\\*(10
.\".di EZ \" GCOS patch
.\"\\*(10 \" GCOS patch
.\".br \" GCOS patch
.\".di \" GCOS patch
.\".rm EZ \" GCOS patch
.lt \\n(LLu
.pc %
.if \\n(YE>0 .if \\n(EF>0 .fi
.rm EL 10 11 12 13 14 15 16 17 18 19 20 21 22 23
.rr 10 11 12 13 14 15 16 17 18 19 20 21 22 23
.if \\n(ZN>0 .if t .sp .5
.if \\n(ZN>0 .if n .sp
.if "\\n(.z"" .nr PE \\n(nl
.if !"\\n(.z"" .nr PE \\n(.d
E 3
I 3
D 5
.if !\\n(TB .if t .wh -1p CM
E 5
I 5
.if !\\n(TB .wh -1p CM
E 5
.if \\n(TB \{\
\&\c
'	bp
.	NP
.	ch CM 160
.\}
E 3
..
D 3
.de ME
.nr SJ \\n(.j
.if \\n(LL>0 .nr LT \\n(LL
.nr YE 1
.if \\n(PO=0 .nr PO \\n(.o
..
.	\"EM end up macro - process left over keep-release
.de EM
E 3
I 3
.de XK
.nr TD 1
.nf
.ls 1
.in 0
.rn KJ KL
.KL
.rm KL
.if \\n(.zKJ .di
.nr TB 0
.if \\n(.zKJ .nr TB 1
E 3
.br
D 3
.if \\n(TB=0 .if t .wh -1p CM
.if \\n(TB \&\c
.if \\n(TB 'bp
.if \\n(TB .NP
.if \\n(TB .ch CM 160
E 3
I 3
.in
.ls
.fi
.nr TD 0
E 3
..
D 3
.	\"NP new page
E 3
I 3
.	\" NP - new page
E 3
.de NP
D 3
.if \\n(FM+\\n(HM>=\\n(.p .tm Margins bigger than page length.
.if \\n(FM+\\n(HM>=\\n(.p .ab
.if \\n(FM+\\n(HM>=\\n(.p .ex
.nr PX \\n(.s
.nr PF \\n(.f
E 3
I 3
.if !\\n(LT .nr LT \\n(LLu
.if \\n(FM+\\n(HM>=\\n(.p \{\
.	tm HM + FM longer than page
.	ab
.\}
E 3
D 5
.if t .CM
E 5
I 5
.CM
E 5
D 3
.if \\n(HM=0 .nr HM 1i
'sp \\n(HMu/2u
.lt \\n(LTu
.ps \\n(PS
E 3
I 3
.if !\\n(HM .nr HM 1i
.po \\n(POu
.nr PF \\n(.f
.nr PX \\n(.s
E 3
.ft 1
D 3
.if \\n(PO>0 .po \\n(POu
E 3
I 3
.ps \\n(PS
'sp \\n(HMu/2u
E 3
.PT
I 3
'sp |\\n(HMu
.HD	\"undefined
E 3
.ps \\n(PX
.ft \\n(PF
D 3
'sp |\\n(HMu
E 3
.nr XX 0 1
.nr YY 0-\\n(FMu
.ch FO 16i
.ch FX 17i
.ch FO -\\n(FMu
.ch FX \\n(.pu-\\n(FMu
.if \\n(MF .FV
.nr MF 0
.mk
.os
D 5
.ev 1
E 5
I 5
.ev 2
E 5
D 3
.if \\n(TD=0 .if \\n(TC<5  .XK
E 3
I 3
.if !\\n(TD .if \\n(TC<5 .XK
E 3
.nr TC 0
D 3
.ns
E 3
.ev
.nr TQ \\n(.i
.nr TK \\n(.u
D 3
.if \\n(IT>0 \{\
E 3
I 3
.if \\n(IT \{\
E 3
.	in 0
.	nf
.	TT
.	in \\n(TQu
D 3
.	if \\n(TK .fi\
\}
E 3
I 3
.	if \\n(TK .fi
.\}
.ns
E 3
.mk #T
D 3
.if t .if \\n(.o+\\n(LL>7.75i .tm Offset + line length exceeds 7.75 inches, too wide
E 3
I 3
D 5
.if t .if \\n(.o+\\n(LL>7.54i .tm PO + LL wider than 7.54i
E 5
E 3
..
D 3
.de XK
.nr TD 1
.nf
.ls 1
.in 0
.rn KJ KL
.KL
.rm KL
.if "\\n(.z"KJ" .di
.nr TB 0
.if "\\n(.z"KJ" .nr TB 1
.br
.in
.ls
.fi
.nr TD 0
..
.de KD
.nr KM 0
.if "\\n(.z"KJ" .nr KM 1 \" KM is 1 if in a rediversion of keeps
.if \\n(KM>0 \!.KD \\$1
.if \\n(KM=0 .if \\n(.t<\\$1 .di KJ
..
E 3
I 3
.	\" PT - page titles
E 3
.de PT
D 3
.lt \\n(LLu
E 3
I 3
.lt \\n(LTu
E 3
.pc %
.nr PN \\n%
D 3
.if \\n%-1 .tl '\\*(LH'\\*(CH'\\*(RH'
E 3
I 3
.nr PT \\n%
I 5
.if !'\\n%'0' .if !'\\n%'1' .if !'\\n%'i' .nr PT 2
E 5
.if \\n(P1 .nr PT 2
.if \\n(PT>1 .if !\\n(EH .if !\\n(OH .tl \\*(LH\\*(CH\\*(RH
.if \\n(PT>1 .if \\n(OH .if o .tl \\*(O1
.if \\n(PT>1 .if \\n(EH .if e .tl \\*(E2
E 3
.lt \\n(.lu
..
D 3
.	\"FO - footer of page
E 3
I 3
.	\" OH - odd page header
.de OH
.nr OH 1
.if !\\n(.$ .nr OH 0
.ds O1 \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
..
.	\" EH - even page header
.de EH
.nr EH 1
.if !\\n(.$ .nr EH 0
.ds E2 \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
..
.	\" P1 - PT on 1st page
.de P1
.nr P1 1
..
.	\" FO - footer
E 3
.de FO
.rn FO FZ
D 3
.if \\n(K1>0 .tm This memo has a multi-page cover sheet.  You are
.if \\n(K1>0 .tm rebuked in the name of the Committee on Technical Memoranda.
.if \\n(IT>0 .nr T. 1
.if \\n(IT>0 .if \\n(FC=0  .T# 1
.if \\n(IT>0 .br
E 3
I 3
.if \\n(IT .nr T. 1
.if \\n(IT .if !\\n(FC .T# 1
.if \\n(IT .br
E 3
.nr FC +1
.if \\n(NX<2 .nr WF 0
.nr dn 0
.if \\n(FC<=1 .if \\n(XX .XF
.rn FZ FO
.nr MF 0
D 3
.if \\n(dn  .nr MF 1
E 3
I 3
.if \\n(dn .nr MF 1
E 3
.if !\\n(WF .nr YY 0-\\n(FMu
.if !\\n(WF .ch FO \\n(YYu
.if !\\n(dn .nr WF 0
D 3
.if \\n(FC<=1 .if \\n(XX=0  .if \\n(NX>1 .RC
.if \\n(FC<=1 .if \\n(XX=0  .if \\n(NX<1 'bp
E 3
I 3
.if \\n(FC<=1 .if !\\n(XX \{\
.	if \\n(NX>1 .RC
.	if \\n(NX<2 'bp
.\}
E 3
.nr FC -1
D 3
.if \\n(ML>0 .ne \\n(MLu
E 3
I 3
.if \\n(ML .ne \\n(MLu
E 3
..
D 3
.	\"2C - begin double column
E 3
I 3
.	\" BT - bottom title
.de BT
.nr PF \\n(.f
.nr PX \\n(.s
.ft 1
.ps \\n(PS
.lt \\n(LTu
.po \\n(POu
.if \\n(TM .if \\n(CT \{\
.	tl ''\\n(PN''
.	nr CT 0
.\}
D 5
.if \\n% .if !\\n(EF .if !\\n(OF .tl \\*(LF\\*(CF\\*(RF
.if \\n% .if \\n(OF .if o .tl \\*(O3
.if \\n% .if \\n(EF .if e .tl \\*(E4
E 5
I 5
.if !'\\n%'0' .if !\\n(EF .if !\\n(OF .tl \\*(LF\\*(CF\\*(RF
.if !'\\n%'0' .if \\n(OF .if o .tl \\*(O3
.if !'\\n%'0' .if \\n(EF .if e .tl \\*(E4
E 5
.ft \\n(PF
.ps \\n(PX
..
.	\" OF - odd page footer
.de OF
.nr OF 1
.if !\\n(.$ .nr OF 0
.ds O3 \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
..
.	\" EF - even page footer
.de EF
.nr EF 1
.if !\\n(.$ .nr EF 0
.ds E4 \\$1 \\$2 \\$3 \\$4 \\$5 \\$6 \\$7 \\$8 \\$9
..
.	\" 2C - double column
E 3
.de 2C
D 3
.MC \" default MC is double column
E 3
I 3
.MC
E 3
..
D 3
.de MC \" multiple columns- arg is line length
E 3
I 3
.	\" 1C - single column
.de 1C
.MC \\n(LLu
.hy 14
..
.	\" MC - multiple columns, arg is col width
.de MC
E 3
.nr L1 \\n(LL*7/15
D 3
.if \\n(.$>0 .nr L1 \\$1n
.nr GW 0-1
.if \\n(.$>1 .nr GW \\$1n
E 3
I 3
.if \\n(.$ .nr L1 \\$1n
E 3
.nr NQ \\n(LL/\\n(L1
.if \\n(NQ<1 .nr NQ 1
.if \\n(NQ>2 .if (\\n(LL%\\n(L1)=0 .nr NQ -1
D 3
.if \\n(1T=0 \{\
E 3
I 3
.if !\\n(1T \{\
E 3
.	BG
.	if n .sp 4
D 3
.	if t .sp 2\}
.if \\n(NX=0 .nr NX 1
E 3
I 3
.	if t .sp 2
.\}
.if !\\n(NX .nr NX 1
E 3
.if !\\n(NX=\\n(NQ \{\
.	RT
.	if \\n(NX>1 .bp
.	mk
.	nr NC 1
D 3
.	po \\n(POu\}
E 3
I 3
.	po \\n(POu
.\}
E 3
.if \\n(NQ>1 .hy 12
.nr NX \\n(NQ
.nr CW \\n(L1
.ll \\n(CWu
.nr FL \\n(CWu*11u/12u
.if \\n(NX>1 .nr GW (\\n(LL-(\\n(NX*\\n(CW))/(\\n(NX-1)
.nr RO \\n(CW+\\n(GW
.ns
..
.de RC
.if \\n(NC>=\\n(NX .C2
.if \\n(NC<\\n(NX .C1
.nr NC \\n(ND
..
.de C1
.rt
.po +\\n(ROu
.nr ND \\n(NC+1
.nr XX 0 1
.if \\n(MF .FV
.ch FX \\n(.pu-\\n(FMu
D 5
.ev 1
E 5
I 5
.ev 2
E 5
.if \\n(TB .XK
.nr TC 0
.ev
.nr TQ \\n(.i
D 3
.if \\n(IT>0 .in 0
.if \\n(IT>0 .TT
.if \\n(IT>0 .in \\n(TQu
E 3
I 3
.if \\n(IT .in 0
.if \\n(IT .TT
.if \\n(IT .in \\n(TQu
E 3
.mk #T
.ns
..
D 3
.ch FO \\n(YYu
E 3
.de C2
.po \\n(POu
'bp
.nr ND 1
..
D 3
.	\"1C - return to single column format
.de 1C
.MC \\n(LLu
.hy 14
..
.	\".de R3
.	\".pl 102
.	\".nr LT \\n(.l
.	\"..
.de MH
Bell Laboratories
Murray Hill, New Jersey 07974
..
.de PY
Bell Laboratories
Piscataway, New Jersey 08854
..
.de BT
.nr PX \\n(.s
.nr PF \\n(.f
.ft 1
.ps \\n(PS
'lt \\n(LTu
.po \\n(POu
.if \\n%>0 .tl '\\*(LF'\\*(CF'\\*(RF'
.ft \\n(PF
.ps \\n(PX
..
.	\"PP - paragraph
.de PP
.RT
.ne 1.1
.if \\n(1T .sp \\n(PDu
.ti +\\n(PIu
..
.	\"SH - (unnumbered) section heading
.de SH
.ti \\n(.iu
.RT
.if \\n(1T .sp 1
.if !\\n(1T .BG
.RT
.ne 4
.ft 3
.if n .ul 1000
..
.	\"NH - numbered heading
.de NH
.RT
.if \\n(1T .sp 1
.if !\\n(1T .BG
.RT
.ne 4
.ft 3
.if n .ul 1000
.nr NS \\$1
.if !\\n(.$ .nr NS 1
.if !\\n(NS .nr NS 1
.nr H\\n(NS +1
.if !\\n(NS-4 .nr H5 0
.if !\\n(NS-3 .nr H4 0
.if !\\n(NS-2 .nr H3 0
.if !\\n(NS-1 .nr H2 0
.if !\\$1 .if \\n(.$ .nr H1 1
.ds SN \\n(H1.
.ti \\n(.iu
.if \\n(NS-1 .as SN \\n(H2.
.if \\n(NS-2 .as SN \\n(H3.
.if \\n(NS-3 .as SN \\n(H4.
.if \\n(NS-4 .as SN \\n(H5.
\\*(SN
..
.	\"BG - begin, execute at first PP
.de BG
.br
.ME
.rm ME
.di
.ce 0
.nr KI 0
.hy 14
.nr 1T 1
.S\\n(ST
.rm S0
.rm S1
.rm S2
.rm S3
.rm OD
.rm OK
.rm TX
.rm AX
.rm WT
.rm CS
.rm TM
.rm IM
.rm MF
.rm MR
.rm RP
.rm I1
.rm I2
.rm I3
.rm I4
.rm I5
.rm CB
.rm E1
.rm E2
.de TL
.ft 3
.sp
.if n .ul 100
.ce 100
.LG
\\..
.de AU
.ft 2
.if n .ul 0
.ce 100
.sp
.NL
\\..
.de AI
.ft 1
.ce 100
.if n .ul 0
.if n .sp
.if t .sp .5
.NL
\\..
.RA
.rm RA
.rn FJ FS
.rn FK FE
.nf
.ev 1
.ps \\n(PS-2
.vs \\n(.s+2p
.ev
.if \\n(KG=0 .nr FP 0 
.if \\n(GA>1 .if \\n(KG=0 .nr GA 0 \" next UNIX must be flagged.
.nr KG 0 
.if \\n(FP>0 .FS
.if \\n(FP>0 .FG
.if \\n(FP>0 .FE
.br
.if \\n(TV>0 .if n .sp 2
.if \\n(TV>0 .if t .sp 1
.fi
.ll \\n(LLu
..
.de RA \"redefine abstract macros
.de AB
.br
.if !\\n(1T .BG
.ce 1
.sp 1
.if \\n(.$=0 ABSTRACT
.if \\n(.$>0 .if !"\\$1"-" .if !"\\$1"no"  \\$1
.if \\n(.$=0 .sp
.if \\n(.$>0 .if !"\\$1"-" .if !"\\$1"no" .sp
.sp 1
.nr AJ 1
.in +\\n(.lu/12u
.ll -\\n(.lu/12u
.RT
\\..
.de AE
.nr AJ 0
.br
.in 0
.ll \\n(LLu
.if \\n(VS>40 .vs \\n(VSu
.if \\n(VS<=39 .vs \\n(VSp
\\..
..
.	\"IP - indented paragraph
.de IP
.RT
.if !\\n(IP .nr IP +1
.sp \\n(PDu
.ne 3v
.if \\n(.$-1 .nr I\\n(IR \\$2n
.in +\\n(I\\n(IRu
.nr TY \\n(TZ-\\n(.i
.ta \\n(I\\n(IRu \\n(TYuR
.if \\n(.$>0 \{\
.ti -\\n(I\\n(IRu
\&\\$1\t\c\}
..
.	\"LP - left aligned (block) paragraph
.de LP
.ti \\n(.iu
.RT
.if \\n(1T .sp \\n(PDu
.ne 1.1
..
.de QP
.ti \\n(.iu
.RT
.if \\n(1T .sp \\n(PDu
.ne 1.1
.nr QP 1
.in +\\n(QIu
.ll -\\n(QIu
.ti \\n(.iu
..
.	\"IE - synonym for .LP
.de IE
.LP
..
.	\"LB - label paragraph
.de LB
.in +\\n(I\\n(IRu
.ta \\n(I\\n(IRu
.if \\n(.$ .ti -\\n(I\\n(IRu
.if \\n(.$ \&\\$1\t\c
..
.de XP
.RT
.if !\\n(IP .nr IP +1
.sp \\n(PDu
.ne 3
.if \\n(.$-2 .nr I\\n(IR \\$3n
.in +\\n(I\\n(IRu
.ta \\n(I\\n(IRu/2u \\n(I\\n(IRu
.ti -\\n(I\\n(IRu
\0\\$1\t\\$2\t\c
..
.	\"RS - prepare for double indenting
E 3
I 3
.	\" RS - right shift
E 3
.de RS
.nr IS \\n(IP
.RT
.nr IP \\n(IS
D 3
.if \\n(IP>0 .in +\\n(I\\n(IRu
E 3
I 3
.if \\n(IP .in +\\n(I\\n(IRu
E 3
.nr IR +1
.nr I\\n(IR \\n(PIu
.in +\\n(I\\n(IRu
D 3
.nr TY \\n(TZ-\\n(.i
.ta \\n(TYuR
E 3
..
D 3
.	\"RE - retreat to the left
E 3
I 3
.	\" RE - retreat left
E 3
.de RE
.nr IS \\n(IP
.RT
.nr IP \\n(IS
D 3
.nr IR -1
E 3
I 3
.if \\n(IR .nr IR -1
E 3
.if \\n(IP<=0 .in -\\n(I\\n(IRu
..
D 3
.de TC
.nr TZ \\n(.lu
.if \\n(.$ .nr TZ \\$1n
.ta \\n(TZuR
..
.de TD
.LP
.nr TZ 0
..
.	\"CM - cut mark
E 3
I 3
.	\" CM - cut mark
I 5
.	\" only in troff when register v isn't one
.	\" if string .T is set (ditroff), only if .T is "vp"
.	\" may be forced if register v is two
.if n .ig
.if \nv=1 .ig
.if !\nv=2 .if !"\*(.T"" .if !"\*(.T"vp" .ig
E 5
E 3
.de CM
.po 0
.lt 7.6i
.ft 1
.ps 10
.vs 4p
.tl '--''--'
.po
.vs
.lt
.ps
.ft
..
D 3
.	\"B - bold font
E 3
I 3
.	\" I - italic font
.de I
.nr PQ \\n(.f
.if t .ft 2
.ie \\$1 .if n .ul 999
.el .if n .ul 1
.if t .if !\\$1 \&\\$1\|\f\\n(PQ\\$2
.if n .if \\n(.$=1 \&\\$1
.if n .if \\n(.$>1 \&\\$1\c
.if n .if \\n(.$>1 \&\\$2
..
.	\" B - bold font
E 3
.de B
.nr PQ \\n(.f
.if t .ft 3
D 3
.if "\\$1"" .if n .ul 1000
.if !"\\$1"" .if n .ul 1
.if t .if !"\\$1"" \&\\$1\\f\\n(PQ\\$2
E 3
I 3
.ie \\$1 .if n .ul 999
.el .if n .ul 1
.if t .if !\\$1 \&\\$1\f\\n(PQ\\$2
E 3
.if n .if \\n(.$=1 \&\\$1
D 3
.if n .if \\n(.$>1 \&\\$1\\c
.if n .if \\n(.$>1 \\&\\$2
E 3
I 3
.if n .if \\n(.$>1 \&\\$1\c
.if n .if \\n(.$>1 \&\\$2
E 3
..
D 3
.	\"R - Roman font
E 3
I 3
.	\" R - Roman font
E 3
.de R
.if n .ul 0
.ft 1
..
D 3
.	\"I - italic font
.de I
.nr PQ \\n(.f
.if t .ft 2
.if "\\$1"" .if n .ul 1000
.if !"\\$1"" .if n .ul 1
.if t .if !"\\$1"" \&\\$1\\f\\n(PQ\\$2
.if n .if \\n(.$=1 \&\\$1
.if n .if \\n(.$>1 \&\\$1\\c
.if n .if \\n(.$>1 \\&\\$2
E 3
I 3
.	\" UL - underline in troff
.de UL
.if t \\$1\l'|0\(ul'\\$2
D 4
.if n .I \\$1 \\$2
E 4
I 4
.if n .I "\\$1" "\\$2"
E 4
E 3
..
D 3
.	\"TA - tabs set in ens or chars
.de TA
.ta \\$1n \\$2n \\$3n \\$4n \\$5n \\$6n \\$7n \\$8n \\$9n
..
.	\"SM - make smaller size
E 3
I 3
.	\" SM - smaller
E 3
.de SM
.ps -2
..
D 3
.	\"LG - make larger size
E 3
I 3
.	\" LG - larger
E 3
.de LG
.ps +2
..
D 3
.	\"NL - return to normal size
E 3
I 3
.	\" NL - normal
E 3
.de NL
.ps \\n(PS
..
D 3
.	\"DA - force date; ND - no date or new date.
E 3
I 3
.	\" DA - force date
E 3
.de DA
.if \\n(.$ .ds DY \\$1 \\$2 \\$3 \\$4
.ds CF \\*(DY
..
I 3
.	\" ND - no date or new date
E 3
.de ND
D 3
.ds DY \\$1 \\$2 \\$3 \\$4
E 3
I 3
.if \\n(.$ .ds DY \\$1 \\$2 \\$3 \\$4
E 3
.rm CF
..
D 3
.if \n(mo-0 .ds MO January
.if \n(mo-1 .ds MO February
.if \n(mo-2 .ds MO March
.if \n(mo-3 .ds MO April
.if \n(mo-4 .ds MO May
.if \n(mo-5 .ds MO June
.if \n(mo-6 .ds MO July
.if \n(mo-7 .ds MO August
.if \n(mo-8 .ds MO September
.if \n(mo-9 .ds MO October
.if \n(mo-10 .ds MO November
.if \n(mo-11 .ds MO December
.if \n(dw-0 .ds DW Sunday
.if \n(dw-1 .ds DW Monday
.if \n(dw-2 .ds DW Tuesday
.if \n(dw-3 .ds DW Wednesday
.if \n(dw-4 .ds DW Thursday
.if \n(dw-5 .ds DW Friday
.if \n(dw-6 .ds DW Saturday
.ds DY \*(MO \n(dy, 19\n(yr
.IZ
.rm IZ
.rm MO
.de FN
.FS
..
.	\"FS - begin footnote
E 3
I 3
.	\" \** - numbered footnote
D 5
.ds * \\*([.\\n+*\\*(.]
E 5
I 5
.ds * \\*[\\n+*\\*]
E 5
.	\" FJ - replaces FS after cover
E 3
.de FJ
'ce 0
D 2
.di
E 2
D 3
.ev1
E 3
I 3
.di
.ev 1
E 3
.ll \\n(FLu
.da FF
.br
D 3
.if \\n(IF>0 .tm Footnote within footnote-illegal.
E 3
I 3
.if \\n(IF .tm Nested footnote
E 3
.nr IF 1
.if !\\n+(XX-1 .FA
I 3
.if !\\n(MF .if !\\n(.$ .if \\n* .FP \\n*
.if !\\n(MF .if \\n(.$ .FP \\$1 no
E 3
..
D 3
.	\"FE - footnote end
E 3
I 3
.	\" FK - replaces FE after cover
E 3
.de FK
.br
.in 0
.nr IF 0
.di
.ev
.if !\\n(XX-1 .nr dn +\\n(.v
.nr YY -\\n(dn
D 3
.if \\n(NX=0 .nr WF 1
E 3
I 3
.if !\\n(NX .nr WF 1
E 3
.if \\n(dl>\\n(CW .nr WF 1
.if (\\n(nl+\\n(.v)<=(\\n(.p+\\n(YY) .ch FO \\n(YYu
D 3
.if (\\n(nl+\\n(.v)>(\\n(.p+\\n(YY) .if \\n(nl>(\\n(HM+1.5v) .ch FO \\n(nlu+\\n(.vu
.if (\\n(nl+\\n(.v)>(\\n(.p+\\n(YY) .if \\n(nl+\\n(FM+1v>\\n(.p .ch FX \\n(.pu-\\n(FMu+2v
.if (\\n(nl+\\n(.v)>(\\n(.p+\\n(YY) .if \\n(nl<=(\\n(HM+1.5v) .ch FO \\n(HMu+(4u*\\n(.vu)
E 3
I 3
.if (\\n(nl+\\n(.v)>(\\n(.p+\\n(YY) \{\
.	if \\n(nl>(\\n(HM+1.5v) .ch FO \\n(nlu+\\n(.vu
.	if \\n(nl+\\n(FM+1v>\\n(.p .ch FX \\n(.pu-\\n(FMu+2v
.	if \\n(nl<=(\\n(HM+1.5v) .ch FO \\n(HMu+(4u*\\n(.vu)
.\}
E 3
..
D 3
.\"	First page footer.
E 3
I 3
.	\" FS - begin footnote on cover
E 3
.de FS
D 3
.ev1
E 3
I 3
.ev 1
E 3
.br
.ll \\n(FLu
.da FG
I 3
.if !\\n(.$ .if \\n* .FP \\n*
.if \\n(.$ .FP \\$1 no
E 3
..
I 3
.	\" FE - end footnote on cover
E 3
.de FE
.br
.di
.nr FP \\n(dn
D 3
.if \\n(1T=0 .nr KG 1 \"not in abstract repeat next page.
.if "\\n(.z"OD" .nr KG 0 \" if in OK, don't repeat.
E 3
I 3
.if !\\n(1T .nr KG 1
E 3
.ev
..
I 3
.	\" FA - print line before footnotes
E 3
.de FA
D 3
.if n __________________________
E 3
I 3
.in 0
.if n _________________________
E 3
.if t \l'1i'
.br
..
I 3
.	\" FP - footnote paragraph
.de FP
.sp \\n(PDu/2u
.if \\n(FF<2 .ti \\n(FIu
.if \\n(FF=3 \{\
.	in \\n(FIu*2u
.	ta \\n(FIu*2u
.	ti 0
.\}
.if !\\n(FF \{\
.	ie "\\$2"no" \\$1\0\c
D 5
.	el \\*([.\\$1\\*(.]\0\c
E 5
I 5
.	el \\*[\\$1\\*]\0\c
E 5
.\}
.if \\n(FF .if \\n(FF<3 \{\
.	ie "\\$2"no" \\$1\0\c
.	el \\$1.\0\c
.\}
.if \\n(FF=3 \{\
.	ie "\\$2"no" \\$1\t\c
.	el \\$1.\t\c
.\}
..
.	\" FV - get leftover footnote from previous page
E 3
.de FV
.FS
.nf
.ls 1
.FY
.ls
.fi
.FE
..
I 3
.	\" FX - divert leftover footnote for next page
E 3
.de FX
D 3
.if \\n(XX>0 .di FY
.if \\n(XX>0 .ns
E 3
I 3
.if \\n(XX .di FY
.if \\n(XX .ns
E 3
..
I 3
.	\" XF - actually print footnote
E 3
.de XF
.if \\n(nlu+1v>(\\n(.pu-\\n(FMu) .ch FX \\n(nlu+1.9v
D 3
.ev1
E 3
I 3
.ev 1
E 3
.nf
.ls 1
.FF
.rm FF
.nr XX 0 1
.br
.ls
.di
.fi
.ev
..
I 5
.de IS			\" *** start ideal picture
.nr g7 \\n(.u
.ls 1
..
.de IF
.if \\n(g7 .fi
.ls
..
.de IE			\" *** end ideal picture
.if \\n(g7 .fi
.ls
..
.de PS		\" *** start picture: $1=height, $2=width in units or inches
.if t .sp .3
.nr g7 \\$2
.in (\\n(.lu-\\n(g7u)/2u
.ne \\$1u
.nr g7 \\n(.u
.ls 1
..
.de PE			\" *** end picture
.in
.if \\n(g7 .fi
.if t .sp .6
.ls
..
.\"	GS called with C (default), L or R  (\n(g1=width, \n(g2=height)
.de GS			\" *** start gremlin picture
.nr g7 (\\n(.lu-\\n(g1u)/2u
.if "\\$1"L" .nr g7 \\n(.iu
.if "\\$1"R" .nr g7 \\n(.lu-\\n(g1u
.in \\n(g7u
.nr g7 \\n(.u
.ls 1
.nf
.ne \\n(g2u
..
.de GE			\" *** end gremlin picture
.ls
.in
.if \\n(g7 .fi
.if t .sp .6
..
.de GF			\" *** finish gremlin picture; stay at top
.ls
.in
.if \\n(g7 .fi
..
E 5
D 3
.de FL
.ev1
.nr FL \\$1n
.ll \\$1
.ev
E 3
I 3
.	\" TS - source file for tbl
.de TS
.rn TS @T
D 5
.so \*(//s.tbl
E 5
I 5
.so \*(//tbl.ms
E 5
.TS \\$1 \\$2
.rm @T
E 3
..
D 3
.de HO
Bell Laboratories
Holmdel, New Jersey 07733
E 3
I 3
.	\" EQ - source file for eqn
.de EQ
.rn EQ @T
D 5
.so \*(//s.eqn
E 5
I 5
.so \*(//eqn.ms
E 5
.EQ \\$1 \\$2
.rm @T
E 3
..
D 3
.de WH
Bell Laboratories
Whippany, New Jersey 07981
E 3
I 3
.	\" ]- - source file for refer
.de ]-
.rn ]- @T
D 5
.so \*(//s.ref
E 5
I 5
.so \*(//ref.ms
E 5
.]-
.rm @T
E 3
..
I 5
.if !"\*(.T"" \{\
.	\" LT and HE - source for letter head
.de LT
.rn LT @T
.so \*(L/hed.ms
.LT
.rm @T
..
.de HE
.rn HE @T
.so \*(L/hed.ms
.HE
.rm @T
..
.\}
E 5
D 3
.de IH
Bell Laboratories
Naperville, Illinois 60540
..
.de UL \" underline argument, don't italicize
.if t \\$1\l'|0\(ul'\\$2
.if n .I \\$1 \\$2
..
.em EM
. \"  ACCENTS  say \*'e or \*`e to get e acute or e grave
.ds ' \h'\w'e'u*4/10'\z\(aa\h'-\w'e'u*4/10'
.ds ` \h'\w'e'u*4/10'\z\(ga\h'-\w'e'u*4/10'
. \"  UMLAUT  \*:u, etc.
.ds : \v'-0.6m'\h'(1u-(\\n(.fu%2u))*0.13m+0.06m'\z.\h'0.2m'\z.\h'-((1u-(\\n(.fu%2u))*0.13m+0.26m)'\v'0.6m'
. \" TILDE and CIRCUMFLEX
.ds ^ \\k:\h'-\\n(.fu+1u/2u*2u+\\n(.fu-1u*0.13m+0.06m'\z^\h'|\\n:u'
.ds ~ \\k:\h'-\\n(.fu+1u/2u*2u+\\n(.fu-1u*0.13m+0.06m'\z~\h'|\\n:u'
.	\" czech v symbol
.ds C \\k:\\h'+\\w'e'u/4u'\\v'-0.6m'\\s6v\\s0\\v'0.6m'\\h'|\\n:u'
.ds v \\k:\\h'+\\w'e'u/4u'\\v'-0.6m'\\s6v\\s0\\v'0.6m'\\h'|\\n:u'
.		\" cedilla
.ds , \\k:\\h'\\w'c'u*0.4u'\\z,\\h'|\\n:u'
.de []
.][ \\$1
..
.de ][
.if \\$1>5 .tm Bad arg to []
.[\\$1
..
.if n .ds [. [
.if t .ds [. \s-2\v'-.4m'\f1
.if n .ds .] ]
.if t .ds .] \v'.4m'\s+2\fP
.if n .ds [o ""
.if n .ds [c ""
.if t .ds [o ``
.if t .ds [c ''
.de [5 \" tm style
.FS
.IP "\\*([F.\0"
\\*([A, \\f2\\*([T\\f1,
.ie \\n(TN \\*([M.
.el Bell Laboratories internal memorandum (\\*([D).
.RT
.FE
..
.de [0 \" other
.FS
.IP "\\*([F.\0"
.if !"\\*([A"" \\*([A,
.if !"\\*([T"" \\f2\\*([T\\f1\c
.if !"\\*([T"" .if !"\\*([O"" ,\ 
.ie !"\\*([O"" \\*([O
.el .if !"\\*([T"" \&.
.if !"\\*([D"" \\*([D.
.RT
.FE
..
.de [1 \" journal article
.FS
.IP "\\*([F.\0"
\\*([A,
.if !"\\*([T"" \\*([o\\*([T,\\*([c
.if "\\*([V"" \\f2\\*([J\\f1,
.if !"\\*([V"" \\f2\\*([J\\f1
.if !"\\*([V"" \{.if n Vol.\&
\\f3\\*([V\\f1\c\}
.if !"\\*([N"" (\\*([N)\c
.if !"\\*([P"" \{\
.ie \\n([P>0 \ pp.\&
.el \ p.\&
\\*([P\}
.if !"\\*([I"" .if "\\*([R"" \\*([I,
(\\*([D).
.if !"\\*([O"" \\*([O
.RT
.FE
..
.de [2 \" book
.FS
.IP "\\*([F.\0"
\\*([A, \\f2\\*([T,\\f1
\\*([I\c
.if !"\\*([C"" , \\*([C\c
 (\\*([D).
.if !"\\*([G"" Gov't. ordering no. \\*([G
.if !"\\*([O"" \\*([O
.RT
.FE
..
.de [4 \" report
.FS
.IP "\\*([F.\0"
\\*([A, \\*([o\\*([T,\\*([c
\\*([R\c
.if !"\\*([G"" \& (\\*([G)\c
.if !"\\*([I"" ,  \\*([I\c
.if !"\\*([C"" ,  \\*([C\c
 (\\*([D).
.if !"\\*([O"" \\*([O
.RT
.FE
..
.de [3 \" article in book
.FS
.IP "\\*([F.\0"
\\*([A, \\*([o\\*([T,\\*([c
.if !"\\*([P"" pp. \\*([P
in \\f2\\*([B\\f1, \c
.if !"\\*([E"" ed. \\*([E,\c
.if !"\\*([I"" \\*([I\c
.if !"\\*([C"" ,  \\*([C\c
 (\\*([D).
.if !"\\*([O"" \\*([O
.RT
.FE
..
.de [<
E 3
I 3
.	\" [< - for refer -s or -e
.de ]<
.rn ]< @T
D 5
.so \*(//s.ref
E 5
I 5
.so \*(//ref.ms
E 5
E 3
.]<
I 3
.rm @T
E 3
..
D 3
.de ]<
.SH
References
.LP
.rm FS FE
E 3
I 3
D 5
.if \n(.V>19 .ds [. \f1[
.if \n(.V>19 .ds .] ]\fP
.if \n(.V<20 .ds [. \f1\s-2\v'-.4m'
.if \n(.V<20 .ds .] \v'.4m'\s+2\fP
.ds <. .
.ds <, ,
E 5
I 5
.	\" footnote delimiters
.if \n(.V>19 .ds [ \f1[
.if \n(.V>19 .ds ] ]\fP
.if \n(.V<20 .ds [ \f1\s-2\v'-.4m'
.if \n(.V<20 .ds ] \v'.4m'\s+2\fP
.	\" refer strings
.if n .ds [. [
.if t .ds [. \s-2\v'-.4m'\f1
.if n .ds .] ]
.if t .ds .] \v'.4m'\s+2\fP
.if n .ds <. "
.if t .ds <. .
.if n .ds >. .
.if t .ds >. "
.if n .ds >; ;
.if t .ds >; "
E 5
.if n .ds Q \&"
.if n .ds U \&"
.if n .ds - \%--
.if t .ds Q ``
.if t .ds U ''
.if t .ds - \(em
.ds ' \h'\w'e'u/5'\z\'\h'-\w'e'u/5'
.ds ` \h'\w'e'u/5'\z\`\h'-\w'e'u/5'
D 5
.ds ^ \h'\w'o'u/10'\z^\h'-\w'e'u/10'
.ds , \h'\w'c'u/5'\z,\h'-\w'e'u/5'
.ds : \h'\w'u'u/5'\z"\h'-\w'e'u/5'
.ds ~ \h'\w'n'u/10'\z~\h'-\w'e'u/10'
E 5
I 5
.ds ^ \h'\w'o'u/10'\z^\h'-\w'o'u/10'
.ds , \h'\w'c'u/5'\z,\h'-\w'c'u/5'
.ds : \h'\w'u'u/5'\u\z.\h'\w'u'u*2/5'\z.\d\h'-\w'u'u*3/5'
.ds ~ \h'\w'n'u/10'\z~\h'-\w'n'u/10'
E 5
.ds C \h'\w'c'u/5'\v'-.6m'\s-4\zv\s+4\v'.6m'\h'-\w'c'u/5'
.	\" AM - better accent marks
.de AM
D 5
.so \*(//s.acc
E 5
I 5
.so \*(//acc.ms
E 5
E 3
..
D 3
.de [>
.]>
E 3
I 3
.	\" TM - thesis mode
.de TM
D 5
.so \*(//s.ths
E 5
I 5
.so \*(//ths.ms
E 5
E 3
..
D 3
.de ]>
.sp
E 3
I 3
.	\" BX - word in a box
.de BX
.if t \(br\|\\$1\|\(br\l'|0\(rn'\l'|0\(ul'
.if n \(br\\kA\|\\$1\|\\kB\(br\v'-1v'\h'|\\nBu'\l'|\\nAu'\v'1v'\l'|\\nAu'
E 3
..
D 3
.de [-
.]-
E 3
I 3
.	\" B1 - source file for boxed text
.de B1
.rn B1 @T
D 5
.so \*(//s.tbl
E 5
I 5
.so \*(//tbl.ms
E 5
.B1 \\$1
.rm @T
E 3
..
D 3
.de ]-
.rm [V [P [A [T [N [C [B [O [R [I [E [D
E 3
I 3
.	\" XS - table of contents
.de XS
.rn XS @T
D 5
.so \*(//s.toc
E 5
I 5
.so \*(//toc.ms
E 5
.XS \\$1 \\$2
.rm @T
E 3
..
I 3
.	\" IX - index words to stderr
.de IX
.tm \\$1\t\\$2\t\\$3\t\\$4 ... \\n(PN
..
.	\" UX - UNIX macro
E 3
.de UX
D 3
.ie \\n(GA>0 \\$2\s-2UNIX\s0\\$1
E 3
I 3
.ie \\n(UX \s-1UNIX\s0\\$1
E 3
.el \{\
D 3
.if n \\$2UNIX\\$1*
.if t \\$2\s-2UNIX\\s0\\$1\\f1\(dg\\fP
E 3
I 3
\s-1UNIX\s0\\$1\(dg
E 3
.FS
D 3
.if n *UNIX
.if t \(dgUNIX
.ie \\$3=1 is a Footnote of Bell Laboratories.
.el is a Trademark of Bell Laboratories.
E 3
I 3
D 4
\(dg \s-1UNIX\s0 is a trademark of Bell Laboratories.
E 4
I 4
D 5
\(dg \s-1UNIX\s0 is a trademark of AT&T Bell Laboratories.
E 5
I 5
\(dg \s-1UNIX\s0 is a registered trademark of AT&T Bell Laboratories
in the USA and other countries.
E 5
E 4
E 3
.FE
D 3
.nr GA 1\}
E 3
I 3
.nr UX 1
.\}
E 3
..
D 3
.de US
the
.UX
operating system
..
.de QS
.br
.in +\\n(QIu
.ll -\\n(QIu
.LP
..
.de QE
.br
.ll +\\n(QIu
.in -\\n(QIu
.LP
..
.de B1 \" begin boxed stuff
.br
.di BB
.nr BC 0
.if "\\$1"C" .nr BC 1
.nr BE 1
..
.de B2 \" end boxed stuff
.br
.nr BI 1n
.if \\n(.$>0 .nr BI \\$1n
.di
.nr BE 0
.nr BW \\n(dl
.nr BH \\n(dn
.ne \\n(BHu+\\n(.Vu
.nr BQ \\n(.j
.nf
.ti 0
.if \\n(BC>0 .in +(\\n(.lu-\\n(BWu)/2u
.in +\\n(BIu
.BB
.in -\\n(BIu
.nr BW +2*\\n(BI
.sp -1
\l'\\n(BWu\(ul'\L'-\\n(BHu'\l'|0\(ul'\h'|0'\L'\\n(BHu'
.if \\n(BC>0 .in -(\\n(.lu-\\n(BWu)/2u
.if \\n(BQ .fi
.br
..
.de AT
.nf
.sp
.ne 2
Attached:
..
.de CT
.nf
.sp
.ne 2
.ie \\n(.$ Copy to \\$1:
.el Copy to:
..
.de BX
.if t \(br\|\\$1\|\(br\l'|0\(rn'\l'|0\(ul'
.if n \(br\\kA\|\\$1\|\\kB\(br\v'-1v'\h'|\\nBu'\l'|\\nAu'\v'1v'\l'|\\nAu'
..
E 3
I 3
.co
.if \n(mo-0 .ds MO January
.if \n(mo-1 .ds MO February
.if \n(mo-2 .ds MO March
.if \n(mo-3 .ds MO April
.if \n(mo-4 .ds MO May
.if \n(mo-5 .ds MO June
.if \n(mo-6 .ds MO July
.if \n(mo-7 .ds MO August
.if \n(mo-8 .ds MO September
.if \n(mo-9 .ds MO October
.if \n(mo-10 .ds MO November
.if \n(mo-11 .ds MO December
.ds DY \*(MO \n(dy, 19\n(yr
.nr * 0 1
.IZ
.em EM
D 7
.rm IZ RA //
E 7
I 7
.rm IZ RA // L/
E 7
E 3
E 1
