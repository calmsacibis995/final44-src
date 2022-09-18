h33978
s 00006/00001/00059
d D 4.3 91/04/18 17:52:59 bostic 3 2
c new copyright; att/bsd/shared
e
s 00001/00001/00059
d D 4.2 85/02/14 11:27:33 ralph 2 1
c fix plotoff sequence to not switch back from 12 pitch to 10 pitch.
e
s 00060/00000/00000
d D 4.1 83/08/05 13:35:31 sam 1 0
c date and time created 83/08/05 13:35:31 by sam
e
u
U
t
T
I 1
D 3
/*	%M%	%I%	%E%	*/
E 3
I 3
/*-
 * %sccs.include.proprietary.c%
 *
 *	%W% (Berkeley) %G%
 */

E 3
#define INCH 240
/*
 * NEC Spinwriter 5500 or 7700 12 Pitch
 * nroff driving table
 * Courier - 72/Manifold thimble
 * by Skip Walker, ucbvax!c:bodega, 21nov82
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
/*breset*/	0,
/*Hor*/		INCH/120,
/*Vert*/	INCH/48,
/*Newline*/	INCH/6,
/*Char*/	INCH/12,
/*Em*/		INCH/12,
/*Halfline*/	INCH/12,
/*Adj*/		INCH/12,
/*twinit*/	"",
/*twrest*/	"",
/*twnl*/	"\n",
/*hlr*/		"\033]S\0339\033]W",
/*hlf*/		"\033]S\033ZA\033]W",
/*flr*/		"\0339",
/*bdon*/	"\033+",
/*bdoff*/	"\033,",
/*ploton*/	"\033]A\033]P",
D 2
/*plotoff*/	"\033]L\033]W",
E 2
I 2
/*plotoff*/	"\033]J\033]W",
E 2
/*up*/		"\0339",
/*down*/	"\033ZA",
/*right*/	" ",
/*left*/	"\b",
/*codetab*/
#include "code.nec"
E 1
