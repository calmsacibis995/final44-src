/* " Author: cck    Date: 87/09/05 18:07:49  " */
/* " Header: procset.h,v 1.2 87/09/05 18:07:49 cck Rel  " */
/* " Revision: 1.2  " */

/*
 * procset - UNIX AppleTalk spooling program: act as a laserwriter
 *   handles simple procset list - assumes procsets in a directory
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986,1987 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  Created sept 5, 1987 by cck from lwsrv
 *
 */

typedef struct Dict_List {		/* known dictionary list */
  struct Dict_List *ad_next;		/* pointer to next */
  char *ad_fn;				/* the file name */
  char *ad_ver;				/* the version number */
} DictList;

DictList *GetProcSet();		/* DictList *GetProcSet(char *) */
void newdictionary();		/* void newdictionary(DictList *) */
void ListProcSet();
