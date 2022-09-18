/*
 *  Author: cck    Date: 88/03/20 18:37:22  
 *  Header: afposenum.c,v 1.15 88/03/20 18:37:22 cck Rel  
 *  Revision: 1.15  
*/

/*
 * afposenum.c - Appletalk Filing Protocol OS enumeration. 
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  March 1987     Schilit	Created.
 *
 */

#include <stdio.h>
#include <sys/param.h>
#ifndef _TYPES
 /* assume included by param.h */
# include <sys/types.h>
#endif
#include <sys/dir.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <netat/appletalk.h>
#include <netat/afp.h>
#include "afps.h"
#include "afpdt.h"
#include "afpgc.h"

typedef struct {			/* Enumeration cache entry */
  IDirP ece_dirid;			/* enumerated directory id */
  int   ece_lru;
  int	ece_lock;			/* do not purge lock */
  int   ece_cnt;			/* count of entries */
  struct direct **ece_nlst;		/* direct info */
  time_t ece_ctime;			/* last directory write dt */
  int  ece_mmode;			/* last directory mode */
  int ece_mcnt;				/* last internal modify count */
  int ece_idx;				/* our index in the cache */
} EnumCE;

#define NILECE ((EnumCE *) 0)

private EnumCE *EnumCache[NECSIZE];
private int EC_Clock;			/* lru clock */

#define NILNLST ((struct direct **) 0)

private EnumCE *EC_Min(),*EC_Find(),*EC_Fetch(),*EC_Load();
private boolean EC_Valid();
private void EC_Free();
private iselect();

/*
 * int iselect(struct direct *d)
 * 
 * See if this directory entry should be included in our enumeration.
 * Special files are skipped ("." , ".." ".finderinfo", etc) and
 * a length check is made to see if the name is too long for AFP.
 *
 */

private
iselect(d)
struct direct *d;
{
  if (ENameLen(d->d_name) > MAXLFLEN)	/* external name too long? */
    return(FALSE);			/* sorry this name is too long */
  if (d->d_name[0] != '.')		/* all special dirs begin with dot */
    return(TRUE);
  if (d->d_namlen == 1)			/* check for dot */
    return(FALSE);
  if (d->d_namlen == 2 &&		/* check for dot dot */
      d->d_name[1] == '.')
    return(FALSE);
  if (strcmp(d->d_name,RFDIRFN) == 0)	/* resource fork directory? */
    return(FALSE);			/* yes... don't include */
  if (strcmp(d->d_name,FIDIRFN) == 0)	/* finder info directory? */
    return(FALSE);			/* yes... don't include */
  if (strcmp(d->d_name,DESKTOP_ICON) == 0) /* check for desktop files */
    return(FALSE);
  if (strcmp(d->d_name,DESKTOP_APPL) == 0)
    return(FALSE);
  return(TRUE);
}

/*
 * void ECacheInit()
 *
 * Initialize the cache table.
 *
 */

void
ECacheInit()
{
  int i;

  if (DBENU)
    printf("ECacheInit: Cache size is %d\n",NECSIZE);

  EC_Clock = 1;				/* init clock */
  for (i=0; i < NECSIZE; i++) {
    EnumCache[i] = (EnumCE *) malloc(sizeof(EnumCE));
    EnumCache[i]->ece_dirid = NILDIR;
    EnumCache[i]->ece_idx = i;
  }
}

private EnumCE *
EC_Min()
{
  int i,mi = -1;
  int mlru = EC_Clock+1;

  for (i=0; i < NECSIZE; i++) {
    if (EnumCache[i]->ece_dirid == NILDIR)
      return(EnumCache[i]);		/* found unused slot */
    if (!EnumCache[i]->ece_lock &&	/* if not locked and... */
	EnumCache[i]->ece_lru < mlru) {	/* is older than current */
	  mlru = EnumCache[i]->ece_lru;	/* remember new clock */
	  mi = i;			/* and new index */
	}
  }

  if (mi == -1)				/* all locked? big problem */
    log("EC_Min: no entry found\n");	/* at least we will know */

  return(EnumCache[mi]);
}

/*
 * void EC_Free(EnumCE *ec)
 *
 * Free storage associate with a cache entry and set the entry to be
 * unused by making ece_dirid = NILDIR.
 *
 */

private void 
EC_Free(ec)
EnumCE *ec;
{
  int i;

  if (ec->ece_dirid == NILDIR)		/* unused entry? */
    return;				/* yes, just return */

  if (DBENU)
    printf("EC_Free: releasing %s\n",pathstr(ec->ece_dirid));

  for (i=0; i < ec->ece_cnt; i++)
    free((char *) ec->ece_nlst[i]);

  free((char *) ec->ece_nlst);
  (ec->ece_dirid)->eceidx = NOECIDX;	/* not in cache */
  ec->ece_dirid = NILDIR;		/* indicate free entry */
}

/*
 * boolean EC_Valid(EnumCE *ec, struct stat *stb)
 *
 * Check if the cache entry is valid by comparing information in
 * the cache entry with information provided from the stat.
 *
 * If the cache entry is empty, the internal modification counters
 * are different, or the directory modification time_t differs from 
 * the time_t the entry was created, then return FALSE.
 *
 */

private boolean
EC_Valid(ec,stb)
EnumCE *ec;
struct stat *stb;
{
  IDirP dirid = ec->ece_dirid;

  if (ec->ece_dirid == NILDIR)		/* no entry? */
    return(FALSE);			/* should not happen */

  /* See if the directory has been modified and needs to be reread */
  /* Check both the internal modified counter and the os modify times. */
  /* The internal mod counts are to prevent a race condition with the */
  /* file's mod times not getting set/read correctly */

  if (ec->ece_dirid->modified != ec->ece_mcnt) { /* modified by us? */
    if (DBENU)
      printf("EC_Valid: internal modify invalidates %s\n",pathstr(dirid));
    return(FALSE);			/* yes... */
  }

  if ((stb->st_ctime != ec->ece_ctime) || (stb->st_mode != ec->ece_mmode)) {
    if (DBENU)
      printf("EC_Valid: external modify invalidates %s\n",pathstr(dirid));
    return(FALSE);
  }
  return(TRUE);				/* not modified */
}

/*
 * EnumCE * EC_Find(IDirP dirid)
 *
 * Given a dirid return the cached Enum entry or NILECE.
 *
 */

private EnumCE *
EC_Find(dirid)
IDirP dirid;
{
  int cidx = dirid->eceidx;		/* cache index */

  if (cidx == NOECIDX)			/* check dir for cache entry */
    return(NILECE);			/* no cache entry */
  EnumCache[cidx]->ece_lru = EC_Clock++; /* this is a reference */
  return(EnumCache[cidx]);		/* return the cache */
}

/*
 * EnumCE * EC_Fetch(IDirP dirid)
 *
 * Get the EnumCE entry for this dirid.  If the entry is in the
 * cache then validate it by calling EC_Valid.  If not valid
 * (changed) then reload the information.  If the directory info
 * is not in the cache then recycle the min cache entry and load
 * a new entry.
 * 
 * Returns NILECE on failure, ece on success.
 *
 */

private EnumCE *
EC_Fetch(dirid)
IDirP dirid;
{
  EnumCE *ec;
  struct stat stb;

  if (DBENU)
    printf("EC_Fetch: request for %s\n",pathstr(dirid));

  ec = EC_Find(dirid);			/* see if entry is cached */
  if (ec != NILECE && ec->ece_lock)	/* found and locked? */
    return(ec);				/* then being enumerated, return */

  if (stat(pathstr(dirid),&stb) != 0) {	/* else do a stat for checks */
    Idrdirid(Ipdirid(dirid),dirid);	/* unlink from directory tree */
    return(NILECE);			/* nothing there... */
  }

  if (ec != NILECE) {			/* find anything? */
    if (EC_Valid(ec,&stb))		/* yes... do validity check */
      return(ec);			/* seems ok, return it */
  } else
    ec = EC_Min();			/* else get a current min */

  EC_Free(ec);				/* free entry or min */

  return(EC_Load(dirid,ec,&stb));	/* load dir and return */
}

/*
 * EnumCE *EC_Load(IDirP dirid, EnumCE *ec, struct stat *stb)
 *
 * Read the directory dirid into ec, filling in information from 
 * the stat structure stb.
 *
 * Return ec on success, or NILECE if failure.
 *
 */

private EnumCE *
EC_Load(dirid,ec,stb)
IDirP dirid;
EnumCE *ec;
struct stat *stb;
{
  char *path = pathstr(dirid);

  if (DBENU)
    printf("EC_Load: adding %s\n",path);
  
  ec->ece_cnt = scandir(path,&ec->ece_nlst,iselect,0);

  if (ec->ece_cnt < 0) {
    if (DBENU)
      printf("EC_Load: scandir failed for %s\n",path);
    return(NILECE);
  }

  ec->ece_ctime = stb->st_ctime;	/* copy last modify time */
  ec->ece_mmode = stb->st_mode;		/* copy the last mode */
  ec->ece_dirid = dirid;		/* copy directory id */
  ec->ece_mcnt = dirid->modified;	/* copy modify count */
  ec->ece_lru = EC_Clock++;		/* set LRU from clock */
  dirid->eceidx = ec->ece_idx;		/* add new entry */
  return(ec);				/* and return table */
}    

/*
 * char * OSEnumGet(dirid,idx)
 *
 * Fetch the idx'th file/dir name from an enumerated directory.  
 * Index starts at 1.  
 *
 * You must have first called OSEnumIni() to initialize and
 * discover the maximun count of entries in the directory.
 *
 */

char *
OSEnumGet(dirid,idx)
IDirP dirid;
int idx;				/* ranges from 1..count */
{
  EnumCE *ec;

  ec = EC_Find(dirid);			/* find enum entry given dirid */
  if (ec == NILECE) {			/* was locked could not be purged */
    log("OSEnumGet: bad enum!\n");
    return("");
  }

  if (idx > ec->ece_cnt) {		/* check for bad idx */
    log("OSEnumGet: Bad idx!\n");
    return("");
  }

  if (!ec->ece_lock)			/* check for bad lock */
    log("OSEnumGet: Handle not locked!\n");
  
  if (DBENU)
    printf("OSEnumGet: %d:%s\n",idx,ec->ece_nlst[idx-1]->d_name);

  return(ec->ece_nlst[idx-1]->d_name);
}

/*
 * int OSEnumInit(IDirP idir)
 *
 * Call OSEnumInit to initialize enumeration information.  This
 * procedure must be called before OSEnumGet which returns the
 * nth entry for a directory.
 *
 * OSEnumDone must be called when finished to release enumeration
 * information for a directory.
 *
 * Returns the count of entries in the directory or a negative error
 * code.
 *
 */

int
OSEnumInit(idir)
IDirP idir;
{
  EnumCE *ec;

  if (DBENU)
    printf("OSEnumInit: %s\n",pathstr(idir));

  OSValFICacheForEnum(idir);	/* make sure fi cache for directory is valid */
  ec = EC_Fetch(idir);		/* get directory info */
  if (ec == NILECE)		/* access problem? */
    return(aeAccessDenied);	/* yes... */

  if (ec->ece_lock == TRUE)
    log("OSEnumInit: directory already locked!\n");

  ec->ece_lock = TRUE;		/* entry is locked, no purge */
  return(ec->ece_cnt);		/* return count */
}

/*
 * void OSEnumDone(dirid)
 *
 * Call this routine to say that enumeration is no longer active for
 * a directory.
 *
 * OSEnumDone unlocks the directory entry and allows it to be removed
 * from the cache.
 *
 */

void
OSEnumDone(dirid)
IDirP dirid;
{
  EnumCE *ec;

  ec = EC_Find(dirid);			/* get cached entry */
  if (ec == NILECE)			/* should not happen */
    log("OSEnumDone: no cache for dirid\n");
  else
    ec->ece_lock = FALSE;		/* unlock */
}

/*
 * int OSEnumCount(dirid)
 * 
 * Return the count of entries in a directory.
 *
 */

int OSEnumCount(dirid)
IDirP dirid;
{
  EnumCE *ec;

  ec = EC_Fetch(dirid);			/* get directory info */
  if (ec == NILECE)			/* access problem? */
    return(aeAccessDenied);		/* yes... */

  if (DBENU)
    printf("OSEnumCount: %s = %d\n",pathstr(ec->ece_dirid),ec->ece_cnt);

  return(ec->ece_cnt);			/* return the count */
}

OSfname(r,idir,fn,typ)
IDirP idir;
char *fn,*r;
int typ;
{
  char *p;

  for (p = pathstr(idir); *p != '\0';)		/* copy the directory */
    *r++ = *p++;

  if (typ != F_DATA) 
    *r++ = '/';

  if (typ == F_RSRC || typ == F_FNDR) /* append directory names */
    for (p = ((typ == F_RSRC) ? RFDIRFN : FIDIRFN); *p != '\0'; )
      *r++ = *p++;

  if (*fn != '\0')		/* add slash */
    *r++ = '/';			/*  if not null file */
  while (*fn != '\0')
    *r++ = *fn++;
  *r = '\0';
}
  


