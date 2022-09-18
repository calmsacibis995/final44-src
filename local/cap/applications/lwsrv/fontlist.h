/* " Author: cck    Date: 87/09/05 17:26:27  " */
/* " Header: fontlist.h,v 1.1 87/09/05 17:26:27 cck Rel  " */
/* " Revision: 1.1  " */

/*
 * fontlist - UNIX AppleTalk spooling program: act as a laserwriter
 *   handles simple font list - assumes we can place in a file
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

typedef struct Font_List {		/* fontlist as read from fonts file */
  struct Font_List *fl_next;		/*  pointer to next font name */
  char *fl_name;			/*  the name itself */
} FontList;

boolean LoadFontList();
void SendFontList();
