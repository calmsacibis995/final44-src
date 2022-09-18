h03276
s 00002/00002/00057
d D 8.1 93/06/04 17:44:46 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00005/00004/00054
d D 5.2 91/04/22 15:55:15 bostic 2 1
c new copyright; att/bsd/shared
e
s 00058/00000/00000
d D 5.1 85/09/21 15:05:44 sam 1 0
c date and time created 85/09/21 15:05:44 by sam
e
u
U
t
T
I 1
D 2
/*
 * Copyright (c) 1985 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 2
I 2
/*-
D 3
 * Copyright (c) 1985 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1985, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.proprietary.c%
E 2
 *
 *	%W% (Berkeley) %G%
 */

#define	imP_SP	128
#define	imP_SP1	129
#define	imP_OLD_MMOVE	130
#define	imP_MPLUS	131
#define	imP_MMINUS	132
#define	imP_MMOVE	133
#define	imP_SMOVE	134

#define	imP_SET_ABS_H	135
#define	imP_SET_REL_H	136
#define	imP_SET_ABS_V	137
#define	imP_SET_REL_V	138

#define	imP_SRULE	192
#define	imP_BRULE	193

#define	imP_SET_HPOS	195
#define	imP_SET_VPOS	196
#define	imP_CRLF	197
#define	imP_SGLY	198
#define	imP_BGLY	199
#define	imP_DELG	200
#define	imP_DELC	201
#define	imP_DELF	202

#define	imP_SET_HV_SYSTEM	205
#define	imP_SET_ADV_DIRS	206
#define	imP_SET_FAMILY	207
#define	imP_SET_IL	208
#define	imP_SET_BOL	209
#define	imP_SET_SP	210
#define	imP_PUSH	211
#define	imP_POP	212
#define	imP_PAGE	213
#define	imP_SET_PUSH_MASK	214
#define	imP_ENDPAGE	219

#define	imP_CREATE_FAMILY_TABLE	221
#define	imP_CREATE_MAP	222

#define	imP_CREATE_PATH	230
#define	imP_SET_TEXTURE	231
#define	imP_SET_PEN	232
#define	imP_FILL_PATH	233
#define	imP_DRAW_PATH	234
#define	imP_BITMAP	235
#define	imP_SET_MAGN	236

#define	imP_EOF	255

E 1
