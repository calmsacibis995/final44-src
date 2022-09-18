#ifndef lint
static char Notice[] = "Copyright (c) 1985 Adobe Systems Incorporated";
static char *RCSID="$Header: map.c,v 2.1 85/11/24 11:49:13 shore Rel $";
#endif
/* map.c
 *
 * Copyright (c) 1985 Adobe Systems Incorporated
 *
 * front end to mapname -- font mapping for users
 *
 * for non-4.2bsd systems (e.g., System V) which do not
 * allow long Unix file names
 *
 * RCSLOG:
 * $Log:	map.c,v $
 * Revision 2.1  85/11/24  11:49:13  shore
 * Product Release 2.0
 * 
 * Revision 1.1  85/11/20  00:14:39  shore
 * Initial revision
 * 
 *
 */

#include <stdio.h>
#include "transcript.h"

main(argc,argv)
int argc;
char **argv;
{
    char result[128];

    if (argc != 2) exit(1);
    if (mapname(argv[1],result) == NULL) exit(1);

    printf("%s\n",result);
    exit(0);
}
