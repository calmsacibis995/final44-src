h18276
s 00002/00002/00089
d D 8.1 93/06/06 16:12:33 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00086
d D 5.2 91/04/16 16:25:28 bostic 7 6
c new copyright; att/bsd/shared
e
s 00007/00003/00083
d D 5.1 85/06/05 16:02:31 dist 6 5
c Add copyright
e
s 00000/00000/00086
d D 2.1 84/02/08 20:43:11 aoki 5 4
c synchronize to version 2
e
s 00002/00000/00084
d D 1.4 84/02/08 00:39:45 mckusick 4 3
c merge in conformant array code by Carol Nishizak
e
s 00000/00000/00084
d D 1.3 83/09/19 07:08:51 thien 3 2
c changing to unlinted source
e
s 00000/00001/00084
d D 1.2 82/08/27 00:34:13 mckusick 2 1
c convert "assert" from being a reserved word to being a non-standard procedure
e
s 00085/00000/00000
d D 1.1 80/08/27 19:54:29 peter 1 0
c date and time created 80/08/27 19:54:29 by peter
e
u
U
t
T
I 1
D 6
/* Copyright (c) 1979 Regents of the University of California */

/* static	char sccsid[] = "%Z%%M% %I% %G%"; */
E 6
I 6
D 7
/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 7
I 7
/*-
D 8
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1980, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * %sccs.include.redist.c%
E 7
 *
 *	%W% (Berkeley) %G%
 */
E 6

#define T_MINUS 1
#define T_MOD 2
#define T_DIV 3
#define T_DIVD 4
#define T_MULT 5
#define T_ADD 6
#define T_SUB 7
#define T_EQ 8
#define T_NE 9
#define T_LT 10
#define T_GT 11
#define T_LE 12
#define T_GE 13
#define T_NOT 14
#define T_AND 15
#define T_OR 16
#define T_ASGN 17
#define T_PLUS 18
#define T_IN 19
#define T_LISTPP 20
#define T_PDEC 21
#define T_FDEC 22
#define T_PVAL 23
#define T_PVAR 24
#define T_PFUNC 25
#define T_PPROC 26
#define T_NIL 27
#define T_STRNG 28
#define T_CSTRNG 29
#define T_PLUSC 30
#define T_MINUSC 31
#define T_ID 32
#define T_INT 33
#define T_FINT 34
#define T_CINT 35
#define T_CFINT 36
#define T_TYPTR 37
#define T_TYPACK 38
#define T_TYSCAL 39
#define T_TYRANG 40
#define T_TYARY 41
#define T_TYFILE 42
#define T_TYSET 43
#define T_TYREC 44
#define T_TYFIELD 45
#define T_TYVARPT 46
#define T_TYVARNT 47
#define T_CSTAT 48
#define T_BLOCK 49
#define T_BSTL 50
#define T_LABEL 51
#define T_PCALL 52
#define T_FCALL 53
#define T_CASE 54
#define T_WITH 55
#define T_WHILE 56
#define T_REPEAT 57
#define T_FORU 58
#define T_FORD 59
#define T_GOTO 60
#define T_IF 61
D 2
#define T_ASRT 62
E 2
#define T_CSET 63
#define T_RANG 64
#define T_VAR 65
#define T_ARGL 66
#define T_ARY 67
#define T_FIELD 68
#define T_PTR 69
#define T_WEXP 70
#define T_PROG 71
#define T_BINT 72
#define T_CBINT 73
#define T_IFEL 74
#define T_IFX 75
#define T_TYID 76
#define T_COPSTR 77
#define T_BOTTLE 78
#define T_RFIELD 79
#define T_FLDLST 80
#define T_LAST 81
I 4
#define T_TYCRANG 82
#define T_TYCARY 83
E 4
E 1
