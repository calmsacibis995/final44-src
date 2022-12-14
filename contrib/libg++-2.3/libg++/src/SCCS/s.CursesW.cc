h32758
s 00000/00000/00284
d D 1.2 93/05/25 15:30:44 elan 2 1
c support for 4.4BSD
e
s 00284/00000/00000
d D 1.1 93/02/24 15:00:38 elan 1 0
c date and time created 93/02/24 15:00:38 by elan
e
u
U
t
T
I 1
/* 
Copyright (C) 1989, 1992 Free Software Foundation
    written by Eric Newton (newton@rocky.oswego.edu)

This file is part of the GNU C++ Library.  This library is free
software; you can redistribute it and/or modify it under the terms of
the GNU Library General Public License as published by the Free
Software Foundation; either version 2 of the License, or (at your
option) any later version.  This library is distributed in the hope
that it will be useful, but WITHOUT ANY WARRANTY; without even the
implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the GNU Library General Public License for more details.
You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the Free Software
Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifdef __GNUG__
#pragma implementation
#endif
#include <stdio.h>
#include <stdarg.h>
#include <builtin.h>
#include <values.h>
#ifndef _OLD_STREAMS
#include <strstream.h>
#include <ioprivate.h>
#endif
// Include CurseW.h and/or curses.h *after* iostream includes,
// because curses.h defines a clear macro that conflicts with iostream. Sigh.
#include <CursesW.h>

#if _G_HAVE_CURSES

int CursesWindow::count = 0;

/*
 * C++ interface to curses library.
 *
 */

/*
 * varargs functions are handled conservatively:
 * They interface directly into the underlying 
 * _doscan, _doprnt and/or vfprintf routines rather than
 * assume that such things are handled compatibly in the curses library
 */

int CursesWindow::scanw(const char * fmt, ...)
{
  va_list args;
  va_start(args, fmt);
#ifdef VMS
  int result = wscanw(w , fmt , args);
#else /* NOT VMS */
  char buf[BUFSIZ];
  int result = wgetstr(w, buf);
  if (result == OK) {
#ifndef _OLD_STREAMS
    strstreambuf ss(buf, BUFSIZ);
    result = ss.vscan(fmt, args);
#else /* _OLD_STREAMS */
#ifndef HAVE_VSCANF
      FILE b;
      b._flag = _IOREAD|_IOSTRG;
      b._base = buf;
      b._ptr = buf;
      b._cnt = BUFSIZ;
      result = _doscan(&b, fmt, args);
#else /* HAVE_VSCANF */
      result = vsscanf(buf, fmt, args);
#endif /* HAVE_VSCANF */
#endif /* _OLD_STREAMS */
  }
#endif /* !VMS */
  va_end(args);
  return result;
}

int CursesWindow::mvscanw(int y, int x, const char * fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  char buf[BUFSIZ];
  int result = wmove(w, y, x);
  if (result == OK)
#ifdef VMS
  result=wscanw(w , fmt , args);
#else /* !VMS */
 {
    result = wgetstr(w, buf);
    if (result == OK) {
#ifndef _OLD_STREAMS
    strstreambuf ss(buf, BUFSIZ);
    result = ss.vscan(fmt, args);
#else /* OLD_STREAMS */
#ifndef HAVE_VSCANF
	FILE b;
	b._flag = _IOREAD|_IOSTRG;
	b._base = buf;
	b._ptr = buf;
	b._cnt = BUFSIZ;
	result = _doscan(&b, fmt, args);
#else
	result = vsscanf(buf, fmt, args);
#endif
#endif /* OLD_STREAMS */
  }
  }
#endif /* !VMS */
  va_end(args);
  return result;
}

int CursesWindow::printw(const char * fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  char buf[BUFSIZ];
#ifndef _OLD_STREAMS
  strstreambuf ss(buf, BUFSIZ);
  ss.vform(fmt, args);
  ss.sputc(0);
#else /* _OLD_STREAMS */
#ifndef HAVE_VPRINTF
  FILE b;
  b._flag = _IOWRT|_IOSTRG;
  b._ptr = buf;
  b._cnt = BUFSIZ;
  _doprnt(fmt, args, &b);
  putc('\0', &b);
#else
  vsprintf(buf, fmt, args);
#endif
#endif /* _OLD_STREAMS */
  va_end(args);
  return waddstr(w, buf);
}


int CursesWindow::mvprintw(int y, int x, const char * fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  int result = wmove(w, y, x);
  if (result == OK)
  {
    char buf[BUFSIZ];
#ifndef _OLD_STREAMS
    strstreambuf ss(buf, BUFSIZ);
    ss.vform(fmt, args);
    ss.sputc(0);
#else /* _OLD_STREAMS */
#ifndef HAVE_VPRINTF
    FILE b;
    b._flag = _IOWRT|_IOSTRG;
    b._ptr = buf;
    b._cnt = BUFSIZ;
    _doprnt(fmt, args, &b);
    putc('\0', &b);
#else
    vsprintf(buf, fmt, args);
#endif
#endif /* _OLD_STREAMS */
    result = waddstr(w, buf);
  }
  va_end(args);
  return result;
}

CursesWindow::CursesWindow(int lines, int cols, int begin_y, int begin_x)
{
  if (count==0)
    initscr();

  w = newwin(lines, cols, begin_y, begin_x);
  if (w == 0)
  {
    (*lib_error_handler)("CursesWindow", "Cannot construct window");
  }

  alloced = 1;
  subwins = par = sib = 0;
  count++;
}

CursesWindow::CursesWindow(WINDOW* &window)
{
  if (count==0)
    initscr();

  w = window;
  alloced = 0;
  subwins = par = sib = 0;
  count++;
}

CursesWindow::CursesWindow(CursesWindow& win, int l, int c, 
                           int by, int bx, char absrel)
{

  if (absrel == 'r') // relative origin
  {
    by += win.begy();
    bx += win.begx();
  }

  // Even though we treat subwindows as a tree, the standard curses
  // library needs the `subwin' call to link to the root in
  // order to correctly perform refreshes, etc.

  CursesWindow* root = &win;
  while (root->par != 0) root = root->par;

  w = subwin(root->w, l, c, by, bx);
  if (w == 0)
  {
    (*lib_error_handler)("CursesWindow", "Cannot construct subwindow");
  }

  par = &win;
  sib = win.subwins;
  win.subwins = this;
  subwins = 0;
  alloced = 1;
  count++;
}


void CursesWindow::kill_subwindows()
{
  for (CursesWindow* p = subwins; p != 0; p = p->sib)
  {
    p->kill_subwindows();
    if (p->alloced)
    {
      if (p->w != 0)
        ::delwin(p->w);
      p->alloced = 0;
    }
    p->w = 0; // cause a run-time error if anyone attempts to use...
  }
}
    
CursesWindow::~CursesWindow() 
{
  kill_subwindows();

  if (par != 0)   // Snip us from the parent's list of subwindows.
  {
    CursesWindow * win = par->subwins;
    CursesWindow * trail = 0;
    for (;;)
    {
      if (win == 0)
        break;
      else if (win == this)
      {
        if (trail != 0)
          trail->sib = win->sib;
        else
          par->subwins = win->sib;
        break;
      }
      else
      {
        trail = win;
        win = win->sib;
      }
    }
  }

  if (alloced && w != 0) 
    delwin(w);

  --count;
  if (count == 0) 
    endwin();
  else if (count < 0) // cannot happen!
  {
    (*lib_error_handler)("CursesWindow", "Too many windows destroyed");
  }
}

#endif /* _G_HAVE_CURSES */
E 1
