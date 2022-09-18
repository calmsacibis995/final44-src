h57172
s 00011/00002/00038
d D 1.2 93/05/25 15:18:35 elan 2 1
c support for 4.4BDS
e
s 00040/00000/00000
d D 1.1 93/02/02 14:52:06 elan 1 0
c date and time created 93/02/02 14:52:06 by elan
e
u
U
t
T
I 1
#include "m68k.h"

/* See m68k.h.  7 means 68020 with 68881.  */

#define TARGET_DEFAULT 7

/* Define __HAVE_68881__ in preprocessor, unless -msoft-float is specified.
   This will control the use of inline 68881 insns in certain macros.  */

#define CPP_SPEC "%{!msoft-float:-D__HAVE_68881__ -D__HAVE_FPU__}"

/* Names to predefine in the preprocessor for this target machine.  */

#define CPP_PREDEFINES "-Dmc68000 -Dmc68020 -Dhp300 -Dhp9000 -Dunix"

/* Link with libg.a when debugging, for dbx's sake.  */

D 2
#define LIB_SPEC "%{g:-lg} %{!p:%{!pg:-lc}}%{p:-lc_p}%{pg:-lc_p} "
E 2
I 2
#define LIB_SPEC "%{g:-lgnulib} %{!p:%{!pg:-lc}}%{p:-lc_p}%{pg:-lc_p}"
E 2

/* Every structure or union's size must be a multiple of 2 bytes.  */

D 2
#define STRUCTURE_SIZE_BOUNDARY 16
E 2
I 2
#define STRUCTURE_SIZE_BOUNDARY 8
E 2

/* This is BSD, so it wants DBX format.  */

#define DBX_DEBUGGING_INFO

/* Do not break .stabs pseudos into continuations.  */

#define DBX_CONTIN_LENGTH 0

/* This is the char to use for continuation (in case we need to turn
   continuation back on).  */

#define DBX_CONTIN_CHAR '?'

/* Don't use the `xsfoo;' construct in DBX output; this system
   doesn't support it.  */

#define DBX_NO_XREFS
I 2


#define HAVE_ATEXIT

/* Don't attempt to use mcrt0.o for 'cc -p'. */

#define STARTFILE_SPEC  "%{pg:gcrt0.o%s}%{!pg:%{p:gcrt0.o%s}%{!p:crt0.o%s}}"

#define SIZE_TYPE "unsigned int"
E 2
E 1
