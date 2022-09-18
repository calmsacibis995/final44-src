h31710
s 00016/00000/00000
d D 5.1 90/05/02 08:40:52 bostic 1 0
c date and time created 90/05/02 08:40:52 by bostic
e
u
U
t
T
I 1
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* hack.version.c - version 1.0.3 */
/* $Header: hack.version.c,v 1.5 85/05/09 00:40:41 aeb Exp $ */

#include	"date.h"

doversion(){
	pline("%s 1.0.3 - last edit %s.", (
#ifdef QUEST
		"Quest"
#else
		"Hack"
#endif QUEST
		), datestring);
	return(0);
}
E 1
