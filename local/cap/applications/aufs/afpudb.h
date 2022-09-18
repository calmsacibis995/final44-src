/*
 *  Author: cck    Date: 87/08/29 19:02:47  
 *  Header: afpudb.h,v 1.2 87/08/29 19:02:47 cck Rel  
 *  Revision: 1.2  
*/

/*
 * afpudb.c - Appletalk Filing Protocol Unix Finder Information
 *  database.  Header file.
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  August 1987     CCKim	Created.
 *
 */

struct ufinderdb {
  byte ufd_ftype[4];
  char *ufd_comment;
  int ufd_commentlen;
  byte *ufd_icon;
  int ufd_iconsize;
};

int os_getunixtype();
