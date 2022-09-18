/*-
 * Copyright (c) 1980 The Regents of the University of California.
 * All rights reserved.
 *
 * This module is believed to contain source code proprietary to AT&T.
 * Use and redistribution is subject to the Berkeley Software License
 * Agreement and your Software Agreement with AT&T (Western Electric).
 *
 *	@(#)conv.h	5.2 (Berkeley) 4/12/91
 */

#if TARGET != TAHOE
	}}}}}	WRONG MACHINE!!!	}}}}}
#endif

/*  The code for converting the types of constants is not  */
/*  portable.  The problems involved in dealing with       */
/*  features such as reserved operands and byte orderings  */
/*  have proven very difficult to deal with in a portable  */
/*  manner.						   */

#define	BLANK	' '

#define MAXWORD  0x7fff
#define MINWORD -0x8000

typedef
  struct Dreal
    {
#if HERE == VAX
      unsigned fract1: 7;
      unsigned exp: 8;
      unsigned sign: 1;
#else
#if HERE == TAHOE
      unsigned sign: 1;
      unsigned exp: 8;
      unsigned fract1: 7;
#else
	}}}}}	WRONG MACHINE!!!	}}}}}
#endif
#endif
      unsigned fract2: 16;
      unsigned short fract3;
      unsigned short fract4;
    }
  dreal;

typedef
  struct Quad
    {
      long word1;
      long word2;
    }
  quad;

typedef
  union RealValue
    {
      double d;
      quad   q;
      dreal  f;
    }
  realvalue;
