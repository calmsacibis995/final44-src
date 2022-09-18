#include "../tw.h"
#include <sgtty.h>

#define INCH 240
/*
Diablo 1640, 1650 printer with 10 letters an inch
nroff driving tables
width and code tables
*/

struct t_w t = {
/*bset*/	0,
/*breset*/	XTABS|CRMOD,
/*Hor*/		INCH/60,
/*Vert*/	INCH/48,
/*Newline*/	INCH/6,
/*Char*/	INCH/12,
/*Em*/		INCH/12,
/*Halfline*/	INCH/12,
/*Adj*/		INCH/60,
/*twinit*/	"\0334\033\036\011\033\037\013",
/*twrest*/	"\0334\033I\033S",
/*Pagej*/	"\033I",
/*twnl*/	"\015\n",
/*hlr*/		"\033D",
/*hlf*/		"\033U",
/*flr*/		"\033\n",
/*bdon*/	"",
/*bdoff*/	"",
/*ploton*/	"\0333",
/*plotoff*/	"\0334",
/*up*/		"\033\n",
/*down*/	"\n",
/*right*/	" ",
/*left*/	"\b",
/*codetab*/
#include "code.300"
