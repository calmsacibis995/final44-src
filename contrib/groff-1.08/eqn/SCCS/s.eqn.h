h15279
s 00001/00000/00051
d D 8.2 95/05/16 07:02:36 bostic 2 1
c unistd.h for optarg
e
s 00051/00000/00000
d D 8.1 95/05/16 05:56:20 bostic 1 0
c date and time created 95/05/16 05:56:20 by bostic
e
u
U
t
T
I 1
// -*- C++ -*-
/* Copyright (C) 1989, 1990, 1991, 1992 Free Software Foundation, Inc.
     Written by James Clark (jjc@jclark.com)

This file is part of groff.

groff is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 2, or (at your option) any later
version.

groff is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with groff; see the file COPYING.  If not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. */

#include <stdio.h>
I 2
#include <unistd.h>
E 2
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include "cset.h"
#include "errarg.h"
#include "error.h"
#include "lib.h"

#include "box.h"

extern char start_delim;
extern char end_delim;
extern int non_empty_flag;
extern int inline_flag;
extern int draw_flag;
extern int one_size_reduction_flag;
extern int compatible_flag;
extern int nroff;

void init_lex(const char *str, const char *filename, int lineno);
void lex_error(const char *message,
	       const errarg &arg1 = empty_errarg,
	       const errarg &arg2 = empty_errarg,
	       const errarg &arg3 = empty_errarg);

void init_table(const char *device);

// prefix for all registers, strings, macros
#define PREFIX "0"
E 1
