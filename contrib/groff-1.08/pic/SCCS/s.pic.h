h26674
s 00001/00000/00101
d D 8.2 95/05/16 07:03:27 bostic 2 1
c unistd.h for optarg
e
s 00101/00000/00000
d D 8.1 95/05/16 05:55:33 bostic 1 0
c date and time created 95/05/16 05:55:33 by bostic
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
#include <math.h>
#include <stdlib.h>
#include <errno.h>

extern "C" {
  double hypot(double, double);
}

#include "assert.h"
#include "cset.h"
#include "lib.h"
#include "stringclass.h"
#include "errarg.h"
#include "error.h"
#include "position.h"
#include "text.h"
#include "output.h"

#ifndef M_SQRT2
#define M_SQRT2	1.41421356237309504880
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

class input {
  input *next;
public:
  input();
  virtual ~input();
  virtual int get() = 0;
  virtual int peek() = 0;
  virtual int get_location(const char **, int *);
  friend class input_stack;
  friend class copy_rest_thru_input;
};

class file_input : public input {
  FILE *fp;
  const char *filename;
  int lineno;
  string line;
  const char *ptr;
  int read_line();
public:
  file_input(FILE *, const char *);
  ~file_input();
  int get();
  int peek();
  int get_location(const char **, int *);
};

void lex_init(input *);
int get_location(char **, int *);

void do_copy(const char *file);
void parse_init();
void parse_cleanup();

void lex_error(const char *message,
	       const errarg &arg1 = empty_errarg,
	       const errarg &arg2 = empty_errarg,
	       const errarg &arg3 = empty_errarg);

void lex_warning(const char *message,
		 const errarg &arg1 = empty_errarg,
		 const errarg &arg2 = empty_errarg,
		 const errarg &arg3 = empty_errarg);

void lex_cleanup();

extern int flyback_flag;
extern int command_char;
// zero_length_line_flag is non-zero if zero-length lines are drawn 
// as dots by the output device
extern int zero_length_line_flag;
extern int driver_extension_flag;
extern int compatible_flag;
E 1
