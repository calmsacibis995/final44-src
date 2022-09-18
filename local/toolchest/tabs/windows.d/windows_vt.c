/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include "vt.h"
#include "windows.h"

/*
 *	This file contains a window based virtual terminal.  It currently
 *	expects the virtual terminal from vt.c to be running under it.
 *	It would not be much work to use this with another virtual terminal
 *	for example termcap.  The *go routines and wxputl would have to be
 *	modified.
 *
 */

/* Globals for windows_vt */

int     Total_Windows;
struct window   _Windows[TOTAL_WINDOWS];
int Need_Set_Scroll;
unsigned int   *kmap[NSCRLIN];
CHAR *cmap2[NSCRLIN];
struct window  *C_window;
struct Area	Area[ 3 ];
int	Area_Attribute = 0;
int	Area_On = FALSE;
