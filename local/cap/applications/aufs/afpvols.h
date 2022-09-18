/*
 *  Author: bill    Date: 87/05/02 15:18:36  
 *  Header: afpvols.h,v 1.4 87/05/02 15:18:36 bill Rel  
 *  Revision: 1.4  
*/

/*
 * afpvols.h - Appletalk Filing Protocol Volume definitions
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  March 1987     Schilit	Created.
 *
 */


typedef struct {		/* Volume Entry */
  IDirP v_rootd;		/* root directory (mount point) */
  word v_bitmap;		/* for packing purposes only */
  char v_path[MAXDLEN];		/* path for this volume */
  word v_attr;			/* (lsb) read-only flag */
#define V_RONLY 0x1		/*   read only flag */
  char v_name[MAXVLEN];		/* advertised name */
  char v_pwd[MAXPLEN];		/* volume password (unused) */
  boolean v_mounted;		/* mounted flag */
  word v_sig;			/* volume signature */
  word v_volid;			/* volume ID */
  sdword v_cdate;		/* volume creation date */
  sdword v_mdate;		/* volume modification date */
  sdword v_bdate;		/* volume backup date */
  sdword v_size;		/* size of volume in bytes */
  sdword v_free;		/* free bytes on volume */
} VolEntry, *VolPtr;		/* user volume table */

#define NILVOL ((VolPtr) 0)

