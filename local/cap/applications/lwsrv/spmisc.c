static char rcsid[] = " Author: cck    Date: 88/03/12 18:31:21  ";
static char rcsident[] = " Header: spmisc.c,v 1.6 88/03/12 18:31:21 cck Rel  ";
static char revision[] = " Revision: 1.6  ";

/*
 * spmisc - UNIX AppleTalk spooling program: act as a laserwriter
 *   some misc. functions useful for spooler
 *   (some should be put in abmisc)
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *  Created Sept 5, 1987 by cck from lwsrv.
 *
 *
 */

#include <stdio.h>
#include <sys/param.h>
#ifndef _TYPES
/* assume included by param.h */
# include <sys/types.h>			/* don't include types if param.h */
#endif					/* is included - probs on some */
#include <netat/appletalk.h>
#include <netat/sysvcompat.h>
#include <netat/compat.h>
#ifdef USESTRINGDOTH
# include <string.h>
#else
# include <strings.h>
#endif
#include "spmisc.h"

/*
 * string input string of extra spaces and any leading and trailing ones
 * (spaces defined as space or tab)
*/
void
stripspaces(inp)
char *inp;
{
  char *p, *p2;

  for (p = inp; *p == ' ' && *p != '\0'; p++)		/* strip leading */
    /* NULL */;
  for (p2 = p; *p2 != '\0'; p2++)	/* convert tabs to space */
    if (*p2 == '\t')
      *p2 = ' ';
  while (*p != '\0')
    if (*p == ' ' && (*(p+1) == ' ' || *(p+1) == '\0'))
      p++;
    else
      *inp++ = *p++;
  *inp = '\0';
}

/*
 * Simple stack for tokens
 *
*/
#define STKSIZ 10
int mystack[STKSIZ];
int sp = 0;

boolean
push(val)
int val;
{
  mystack[sp++] = val;
  if (sp >= STKSIZ) {
    fprintf(stderr, "lwsrv: stack push: STACK OVERFLOW!\n");
    sp = STKSIZ-1;
    return(FALSE);
  }
  return(TRUE);
}

int
pop()
{
  sp--;				/* decrement stack pointer */
  if (sp < 0) {
    fprintf(stderr, "lwsrv: stack pop: STACK UNDERFLOW\n");
    sp = 0;
    return(-1);
  }
  return(mystack[sp]);
}

boolean
isstackempty()
{
  return(sp == 0);
}

void
clearstack()
{
  sp = 0;
}

void
dumpstack()
{
  while (sp--) {
    fprintf(stderr, "%d\n", mystack[sp]);
  }
}
