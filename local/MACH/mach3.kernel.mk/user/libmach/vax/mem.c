/* 
 * Mach Operating System
 * Copyright (c) 1993 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */
/*
 * HISTORY
 * $Log:	mem.c,v $
 * Revision 2.2  93/01/24  14:17:45  danner
 * 	Created.
 * 	[93/01/14            danner]
 * 
 * 
 */
/*
 * ansi compliant mem functions 
 */

#include <string.h>

void *memset(void *addr, int val, unsigned long bcount)
{
  void *ret = addr;
  if (!bcount) return ret;
  if (val) /* nonzero */
    {
      while (bcount--)
	*((char *) addr++) = (unsigned char) val;
    }
  else
    { /* bzero */
      register int    i;

      if (bcount == 0)	/* sanity */
	return ret;
      switch ((unsigned int) addr & 3) {
      case 1:
	*((char *) addr++) = 0;
	if (--bcount == 0)
	  return ret;
      case 2:
	*((char *) addr++) = 0;
	if (--bcount == 0)
	  return ret;
      case 3:
	*((char *) addr++) = 0;
	if (--bcount == 0)
	  return ret;
      default:
	break;
      }

      for (i = bcount >> 2; i; i--, addr += 4)
	*((int *) addr) = 0;
      
      switch (bcount & 3) {
      case 3: *((char*)addr++) = 0;
      case 2: *((char*)addr++) = 0;
      case 1: *((char*)addr++) = 0;
      default:break;
      }
    }
  return ret;
}

