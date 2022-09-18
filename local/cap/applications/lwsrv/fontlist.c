static char rcsid[] = " Author: cck    Date: 88/03/12 18:38:59  ";
static char rcsident[] = " Header: fontlist.c,v 1.3 88/03/12 18:38:59 cck Rel  ";
static char revision[] = " Revision: 1.3  ";

/*
 * fontlist - UNIX AppleTalk spooling program: act as a laserwriter
 *   handles simple font list - assumes we can place in a file
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *  Created Sept 5, 1987 by cck from lwsrv.
 *
 *
 */

#include <stdio.h>
#include <netat/appletalk.h>
#include "fontlist.h"
#include "spmisc.h"
#include "papstream.h"

FontList *fontlist = (FontList *) NULL;	/* fontlist header */

#define FBMAX 100

boolean
LoadFontList(fn)
char *fn;
{
  FILE *ff;
  char fb[FBMAX];
  FontList *fp = NULL;
  
  if (fontlist)			/* already loaded */
    return(TRUE);

  if ((ff = fopen(fn,"r")) == NULL)
    return(FALSE);
  while (fgets(fb,FBMAX,ff) != NULL)
    if (fb[0] != '%' &&	fb[0] != '\n') {
      fp = (FontList *) malloc(sizeof(FontList));
      fp->fl_name = (char *) malloc(strlen(fb)+1);
      strcpy(fp->fl_name,fb);
      fp->fl_next = fontlist;
      fontlist = fp;
    }
  fclose(ff);
  return(TRUE);
}

  
void
SendFontList(pf)
PFILE *pf;
{
  int i = 0;
  FontList *fl = fontlist;
  char status[255];

  /* won't do much good unless single fork */
  NewStatus("initializing fonts");
  while (fl != NULL) {
    i++; 
    p_write(pf,fl->fl_name,strlen(fl->fl_name),FALSE);
    fl = fl->fl_next;
  }
  p_write(pf,"*\n",strlen("*\n"),FALSE);
  fprintf(stderr,"lwsrv: Sending fontList: %d entries\n",i);
  /* won't do much good unless single fork */
  sprintf(status,"receiving job");
  NewStatus(status);
}
