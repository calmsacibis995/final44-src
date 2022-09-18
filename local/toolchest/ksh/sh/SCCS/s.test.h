h03993
s 00044/00000/00000
d D 1.1 88/07/21 17:34:29 marc 1 0
c date and time created 88/07/21 17:34:29 by marc
e
u
U
t
T
I 1
/*

 *      Copyright (c) 1984, 1985, 1986 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
/* %W% */

/*
 *	UNIX shell
 *
 *	David Korn
 *	AT&T Bell Laboratories
 *
 */

/*
 *  These are the valid test operators
 */

#define TEST_ARITH	0100	/* arithmetic operators */
#define TEST_BINOP	0200	/* binary operator */

#define TEST_SEQ	1
#define TEST_SNE	2
#define TEST_EQ		TEST_ARITH|3
#define TEST_NE		TEST_ARITH|4
#define TEST_GT		TEST_ARITH|5
#define TEST_GE		TEST_ARITH|6
#define TEST_LT		TEST_ARITH|7
#define TEST_LE		TEST_ARITH|8
#define TEST_EF		9
#define TEST_OT		10
#define TEST_NT		11
#define TEST_OR		TEST_BINOP|12
#define TEST_AND	TEST_BINOP|13

extern MSG	btest;
E 1
