h56900
s 00001/00000/00016
d D 5.4 92/08/31 10:19:48 elan 4 3
c Added errno.h to includes.
e
s 00001/00000/00015
d D 5.3 90/03/05 12:26:33 bostic 3 2
c make it work with ANSI C preprocessor
e
s 00000/00001/00015
d D 5.2 89/03/06 08:42:41 bostic 2 1
c OK_TO_PLAY no longer necessary, we have dm(8)
e
s 00016/00000/00000
d D 5.1 88/06/01 18:39:36 bostic 1 0
c date and time created 88/06/01 18:39:36 by bostic
e
u
U
t
T
I 1
/*
 * include.h - includes all important files for Phantasia
 */

#include <ctype.h>
#include <curses.h>
#include <math.h>
D 2
#include <pwd.h>
E 2
#include <setjmp.h>
#include <signal.h>
#include <time.h>
I 4
#include <errno.h>
E 4

#include "macros.h"
#include "phantdefs.h"
#include "phantstruct.h"
#include "phantglobs.h"
I 3
#include "pathnames.h"
E 3
E 1
