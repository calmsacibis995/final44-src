h42734
s 00001/00000/00036
d D 8.2 95/05/16 07:02:55 bostic 2 1
c unistd.h for optarg
e
s 00036/00000/00000
d D 8.1 95/05/16 06:00:31 bostic 1 0
c date and time created 95/05/16 06:00:31 by bostic
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
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
I 2
#include <unistd.h>
E 2
#include <errno.h>
#include <assert.h>
#include <math.h>
#include "errarg.h"
#include "error.h"
#include "font.h"
#include "printer.h"
#include "lib.h"

void do_file(const char *);
extern printer *pr;
E 1
