h59347
s 00003/00002/00056
d D 8.2 95/04/28 12:43:25 bostic 9 8
c need return value for sparc; clean up offensive misuse of NULL too
c From: Chris Torek <torek@BSDI.COM>
e
s 00005/00005/00053
d D 8.1 93/06/06 14:57:24 bostic 8 7
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00011/00057
d D 4.7 90/06/01 16:55:14 bostic 7 6
c new copyright notice
e
s 00001/00001/00067
d D 4.6 89/05/19 19:10:19 bostic 6 5
c don't use gets
e
s 00028/00002/00040
d D 4.5 89/05/04 16:11:20 bostic 5 4
c add Berkeley specific copyright notices
e
s 00005/00006/00037
d D 4.4 89/05/04 13:50:19 jak 4 3
c use MAXPATHLEN
e
s 00015/00021/00028
d D 4.3 89/03/29 16:01:31 jak 3 2
c sped it up by 20%
e
s 00002/00002/00047
d D 4.2 83/07/21 11:22:53 mckusick 2 1
c move database to /usr/lib/find; restrict database to /usr
e
s 00049/00000/00000
d D 4.1 83/07/21 00:14:45 mckusick 1 0
c date and time created 83/07/21 00:14:45 by mckusick
e
u
U
t
T
I 5
/*
D 8
 * Copyright (c) 1989 The Regents of the University of California.
 * All rights reserved.
E 8
I 8
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
E 8
 *
 * This code is derived from software contributed to Berkeley by
 * James A. Woods.
 *
D 7
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the University of California, Berkeley.  The name of the
 * University may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
E 7
I 7
 * %sccs.include.redist.c%
E 7
 */

E 5
I 1
#ifndef lint
D 5
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 5
I 5
D 8
char copyright[] =
"%Z% Copyright (c) 1989 The Regents of the University of California.\n\
 All rights reserved.\n";
E 8
I 8
static char copyright[] =
"%Z% Copyright (c) 1989, 1993\n\
	The Regents of the University of California.  All rights reserved.\n";
E 8
#endif /* not lint */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 5

/*
 *  bigram < text > bigrams
 * 
D 2
 * List bigrams for 'find.squeeze' script.
 * Use 'find.code' to encode a file using this output.
E 2
I 2
 * List bigrams for 'updatedb' script.
 * Use 'code' to encode a file using this output.
E 2
 */

#include <stdio.h>
I 4
#include <sys/param.h>			/* for MAXPATHLEN */
E 4

D 4
#define MAXPATH	1024		/* maximum pathname length */
E 4
I 4
char buf1[MAXPATHLEN] = " ";	
char buf2[MAXPATHLEN];
E 4

D 3
char path[MAXPATH];
char oldpath[MAXPATH] = " ";	
E 3
I 3
D 4
char buf1[MAXPATH] = " ";	
char buf2[MAXPATH];
E 3

E 4
main ( )
{
D 3
  	register int count, j;
E 3
I 3
  	register char *cp;
	register char *oldpath = buf1, *path = buf2;
E 3

D 6
     	while ( gets ( path ) != NULL ) {
E 6
I 6
     	while ( fgets ( path, sizeof(buf2), stdin ) != NULL ) {
E 6

D 3
		count = prefix_length ( oldpath, path );
E 3
I 3
		/* skip longest common prefix */
		for ( cp = path; *cp == *oldpath; cp++, oldpath++ )
D 9
			if ( *oldpath == NULL )
E 9
I 9
			if ( *oldpath == '\0' )
E 9
				break;
E 3
		/*
D 4
		   output post-residue bigrams only
		*/
E 4
I 4
		 * output post-residue bigrams only
		 */
E 4
D 3
		for ( j = count; path[j] != NULL; j += 2 ) {
			if ( path[j + 1] == NULL ) 
				break;
			putchar ( path[j] );
			putchar ( path[j + 1] );
E 3
I 3
D 9
		while ( *cp != NULL && *(cp + 1) != NULL ) {
E 9
I 9
		while ( *cp != '\0' && *(cp + 1) != '\0' ) {
E 9
			putchar ( *cp++ );
			putchar ( *cp++ );
E 3
			putchar ( '\n' );
		}
D 3
		strcpy ( oldpath, path );
E 3
I 3
		if ( path == buf1 )		/* swap pointers */
			path = buf2, oldpath = buf1;
		else
			path = buf1, oldpath = buf2;
E 3
   	}
I 9
	return (0);
E 9
D 3
}

prefix_length ( s1, s2 )	/* return length of longest common prefix */
	char *s1, *s2;		/* ... of strings s1 and s2 */
{
	register char *start;

    	for ( start = s1; *s1 == *s2; s1++, s2++ )	
		if ( *s1 == NULL )		
	    		break;
    	return ( s1 - start );
E 3
}
E 1
