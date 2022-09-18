h05391
s 00002/00002/00085
d D 1.3 94/08/13 13:56:27 bostic 3 2
c more types problems, make it compile again   
e
s 00005/00005/00082
d D 1.2 93/05/25 15:30:15 elan 2 1
c support for 4.4BSD
e
s 00087/00000/00000
d D 1.1 93/02/24 15:07:31 elan 1 0
c date and time created 93/02/24 15:07:31 by elan
e
u
U
t
T
I 1
#ifndef _G_curses_h

#include <_G_config.h>

#if _G_HAVE_CURSES

#ifdef __curses_h_recursive
#include_next <curses.h>
#else
#define __curses_h_recursive

extern "C" {
#include_next <curses.h>

/* Some systems (SVR4 for example) allow the definition of CHTYPE to set the
   type of some arguments to the curses functions.  It can be set to "char"
   to save space, or it can be set to something longer to store both a
   character and some attributes.  By default they do not define CHTYPE,
   and when CHTYPE is not defined, the default type is "unsigned long" instead
   of the traditional "char".  However, SVR4 <curses.h> does define
   _VR3_COMPAT_CODE, so we can use that to detect when we should use the SVR4
   default if CHTYPE is not defined.  For other systems, just default to the
   traditional default "char". */

#ifdef CHTYPE
      typedef CHTYPE _G_chtype;		/* Use specified type. */
#else
#ifdef _VR3_COMPAT_CODE
      typedef unsigned long _G_chtype;	/* SVR4 default is "unsigned long" */
#elif defined(hpux)
      typedef unsigned int _G_chtype;
#else
      typedef char _G_chtype;		/* Traditional default is "char" */
#endif
#endif

/* Some args are conceptually const, but SVR4 (and others?) get it wrong. */
#define _C_const /* const */

WINDOW * (newwin)(int lines, int cols, int sy, int sx);
WINDOW * (subwin)(WINDOW *w, int lines, int cols, int sy, int sx);
WINDOW * (initscr)();
D 2
int      (box) (WINDOW*, _G_chtype, _G_chtype);
E 2
I 2
int      (box) (WINDOW*, int, int);
E 2
int      (delwin)(WINDOW*);
int      (getcurx)(WINDOW*);
int      (getcury)(WINDOW*);
int      (mvcur)(int, int, int, int);
int      (overlay)(WINDOW*, WINDOW*);
int      (overwrite)(WINDOW*, WINDOW*);
int      (scroll)(WINDOW*);
int      (touchwin)(WINDOW*);
D 2
int      (waddch)(WINDOW*, _G_chtype);
E 2
I 2
int      (waddch)(WINDOW*, int);
E 2
int      (waddstr)(WINDOW*, _C_const char*);
int      (wclear)(WINDOW*);
int      (wclrtobot)(WINDOW*);
int      (wclrtoeol)(WINDOW*);
int      (wdelch)(WINDOW*);
int      (wdeleteln)(WINDOW*);
int      (werase)(WINDOW*);
int      (wgetch)(WINDOW*);
int      (wgetstr)(WINDOW*, char*);
D 2
int      (winsch)(WINDOW*, _G_chtype);
E 2
I 2
int      (winsch)(WINDOW*, int);
E 2
int      (winsertln)(WINDOW*);
int      (wmove)(WINDOW*, int, int);
int      (wrefresh)(WINDOW*);
D 2
int      (wstandend)(WINDOW*);
int      (wstandout)(WINDOW*);
E 2
I 2
D 3
char     *(wstandend)(WINDOW*);
char     *(wstandout)(WINDOW*);
E 3
I 3
int	 (wstandend)(WINDOW*);
int	 (wstandout)(WINDOW*);
E 3
E 2

// SVR4 rather inanely bundles the format-string parameter with the '...'.
// This breaks VMS, and I don't want to penalize VMS for being right for once!
#ifdef _VR3_COMPAT_CODE /* Magic cookie to recognize SVR4 */
#define _CURSES_FORMAT_ARG /*const char* fmt, */
#else
#define _CURSES_FORMAT_ARG const char* fmt,
#endif

int      (wprintw)(WINDOW*, _CURSES_FORMAT_ARG ...);
int      (mvwprintw)(WINDOW*, int y, int x, _CURSES_FORMAT_ARG ...);
int      (wscanw)(WINDOW*, _CURSES_FORMAT_ARG ...);
int      (mvwscanw)(WINDOW*, int, int, _CURSES_FORMAT_ARG ...);
int      (endwin)();

}
#define _G_curses_h
#endif
#endif /* _G_HAVE_CURSES */
#endif /* _G_curses_h */
E 1
