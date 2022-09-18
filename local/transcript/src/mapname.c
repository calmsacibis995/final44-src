#ifndef lint
static char Notice[] = "Copyright (c) 1985 Adobe Systems Incorporated";
static char *RCSID="$Header: mapname.c,v 2.1 85/11/24 11:49:15 shore Rel $";
#endif
/* mapname.c
 *
 * Copyright (c) 1985 Adobe Systems Incorporated
 *
 * Maps long PostScript font names to short file names via
 * mapping table
 *
 * for non-4.2bsd systems (e.g., System V) which do not
 * allow long Unix file names
 *
 * RCSLOG:
 * $Log:	mapname.c,v $
 * Revision 2.1  85/11/24  11:49:15  shore
 * Product Release 2.0
 * 
 * Revision 1.1  85/11/20  00:15:39  shore
 * Initial revision
 * 
 *
 */

#include <stdio.h>
#ifdef SYSV
#include <string.h>
#else
#include <strings.h>
#endif
#include "transcript.h"

/* psname (long name of a PostScript font) to a filename */
/* returns filename is successful, NULL otherwise */

char MapFile[512];

char *mapname(psname,filename)
char *psname, *filename;
{
    FILE *mapfile;
    char longname[128], shortname[128];
    char *libdir;
    int retcode;

    *filename = '\0';
    if ((libdir = envget("PSLIBDIR")) == NULL) libdir = LibDir;
    VOIDC mstrcat(MapFile,libdir,FONTMAP,sizeof MapFile);
    if ((mapfile = fopen(MapFile, "r")) == NULL) {
	fprintf(stderr,"can't open file %s\n",MapFile);
	exit(2);
    }

    while (fscanf(mapfile, " %s %s\n", longname, shortname) != EOF) {
	if ((retcode = strcmp(longname, psname)) > 0) break;
	else if (retcode == 0) {
	    strcpy(filename, shortname);
	    return (filename);
	}
    }
    return ((char *)NULL);
}

