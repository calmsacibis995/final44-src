h15046
s 00006/00001/00059
d D 4.2 91/04/18 17:52:50 bostic 2 1
c new copyright; att/bsd/shared
e
s 00060/00000/00000
d D 4.1 83/08/05 13:35:04 sam 1 0
c date and time created 83/08/05 13:35:04 by sam
e
u
U
t
T
I 1
D 2
/*	%M%	%I%	%E%	*/
E 2
I 2
/*-
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */

E 2
#define INCH 240
/*
 * DTC 382 12 pitch
 * nroff driving tables
 * width and code tables
 */

struct {
	int bset;
	int breset;
	int Hor;
	int Vert;
	int Newline;
	int Char;
	int Em;
	int Halfline;
	int Adj;
	char *twinit;
	char *twrest;
	char *twnl;
	char *hlr;
	char *hlf;
	char *flr;
	char *bdon;
	char *bdoff;
	char *ploton;
	char *plotoff;
	char *up;
	char *down;
	char *right;
	char *left;
	char *codetab[256-32];
	int zzz;
	} t = {
/*bset*/	0,
/*breset*/	0177420,
/*Hor*/		INCH/60,
/*Vert*/	INCH/48,
/*Newline*/	INCH/6,
/*Char*/	INCH/12,
/*Em*/		INCH/12,
/*Halfline*/	INCH/12,
/*Adj*/		INCH/12,
/*twinit*/	"\033\006",
/*twrest*/	"\033\006",
/*twnl*/	"\r\n",
/*hlr*/		"\033H",
/*hlf*/		"\033h",
/*flr*/		"\032",
/*bdon*/	"\033Z",
/*bdoff*/	"\033z",
/*ploton*/	"\006",
/*plotoff*/	"\033\006",
/*up*/		"\032",
/*down*/	"\n",
/*right*/	" ",
/*left*/	"\b",
/*codetab*/
#include "code.300"
E 1
