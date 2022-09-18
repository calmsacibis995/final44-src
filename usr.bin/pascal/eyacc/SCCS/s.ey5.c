h58061
s 00002/00002/00051
d D 8.1 93/06/06 15:11:34 bostic 4 3
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00006/00005/00047
d D 5.3 91/04/12 16:47:21 bostic 3 2
c new copyright; att/bsd/shared
e
s 00000/00004/00052
d D 5.2 88/09/22 17:25:52 bostic 2 1
c fixes for ANSI C
e
s 00056/00000/00000
d D 5.1 85/04/29 18:37:01 mckusick 1 0
c date and time created 85/04/29 18:37:01 by mckusick
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1979 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
D 4
 * Copyright (c) 1979 The Regents of the University of California.
 * All rights reserved.
E 4
I 4
 * Copyright (c) 1979, 1993
 *	The Regents of the University of California.  All rights reserved.
E 4
 *
 * %sccs.include.proprietary.c%
E 3
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 3
#endif not lint
E 3
I 3
#endif /* not lint */
E 3

/* fake portable I/O routines, for those
    sites so backward as to not have the
     port. library */
/* munged for standard i/o library: peter and louise 5 may 80 */
#include <stdio.h>

FILE *cin, *cout;

FILE *copen( s, c )
    char *s;
    char c;
  {
  FILE *f;

	  if( c == 'r' ){
	    f = fopen( s, "r" );
  } else  if( c == 'a' ){
	    f = fopen( s, "a" );
	    fseek( f, 0L, 2 );
  } else {  /* c == w */
	    f = fopen( s, "w" );
  }

  return( f );
  }

cflush(x) FILE *x; { /* fake! sets file to x */
  fflush( cout );
  cout = x;
  }

D 2
system(){
  error( "The function \"system\" is called" );
  }

E 2
cclose(i) FILE *i; {
  fclose(i);
  }

cexit(i){
  fflush( cout );
  if ( i != 0 ) {
    abort();
  }
  exit(i);
  }
E 1
