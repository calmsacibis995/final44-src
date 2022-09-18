/*
 *  Author: cck    Date: 88/02/23 17:15:25  
 *  Header: afpdid.c,v 1.31 88/02/23 17:15:25 cck Rel  
 *  Revision: 1.31  
*/

/*
 * afpdid.c - Directory id routines
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
#include <ctype.h>
#include <sys/param.h>
#ifndef _TYPES
 /* assume included by param.h */
# include <sys/types.h>
#endif
#include <sys/dir.h>
#include <sys/stat.h>
#include <netat/appletalk.h>
#include <netat/afp.h>
#include "afps.h"
#ifdef USESTRINGDOTH
# include <string.h>
#else
# include <strings.h>
#endif

/*
 *
 * EtoIdirid()	- external to internal translation of directory id.
 * ItoEdirid()	- internal to external translation of directory id.
 * EtoIfile() - return info on file
 * Idirid()	- given a path, return an internal directory id.
 * Ipdirid()	- given a directory id, return parent's directory id.
 * Idndirid()   - given a directory id and a directory name, return
 *                 the directory id of the "directory", creating did if
 *                 non-existant
 * Idrdirid()   - remove the specified directory
 * pathstr()	- given a directory id, return a path.
 * ppathstr()	- given a "root" dirid and dirid, return a path relative
 *                to root dirid
 * InitDID()	- called once to init this module.
 * InitDIDVol   - mark the volume of a dirid
 * ItoEName()   - translate internal to external name
 * EtoIName()   - translate external to internal name
 * ENameLen()   - figure length of interal file name in external terms
 * EModified()  - mark dirid as modified
 *
 */
 
#define TRUE 1
#define FALSE 0
 
private IDirP rootd;

/* 
 * ExtDir structure maps external directory numbers into internal (IDir) 
 * pointers.  It is not a good idea to simply pass back the IDir pointer
 * since the mac expects forever constant ids and will remember these
 * ids between logins to the server.
 *
 * Although we can't generate forever constant ids the ExtDir table will
 * at least verify that we are not looking at a random pointer address.
 *
 * Failure from the table lookup generates a aeParamErr which is usually
 * handled ok the mac by restarting the selection process at root dir.
 *
 */

struct {				/* Maps external to internal safely */
  int xd_base;				/* base edir number */
  int xd_count;				/* number in use */
  IDirP *xd_idirs;			/* pointers to the internal dirids */
  int xd_idsize;			/* size of idirs array */
} ExtDir;

/*
 * nfind scans and finds whether a particular directory "dir" has a
 * subdirectory by the name "nam"
 *
*/
private IDirP
nfind(dir,nam)
IDirP dir;
char *nam;
{
  for (; dir != (IDirP) 0 && strcmp(dir->name,nam) != 0; dir = dir->next)
    /* NULL */;
  return(dir);
}
 
 
/*
 * Create a new directory entry under the specified parent
 * (Should we check existance?)
 *
*/
private IDirP
mkdirset(parent,name)
IDirP parent;
char *name;
{
  IDirP dir;
  sdword NewEDirid();

  dir = (IDirP) malloc(sizeof(IDir));
  dir->name = (char *) malloc((unsigned) strlen(name)+1);
  strcpy(dir->name,name);
  dir->pdir = parent;			/* set pointer to parent in node */
  dir->subs = NILDIR;			/* no children */
  if (parent != NILDIR) {		/* if parent different than root */
    V_COPY(dir->volbm,parent->volbm);	/* duplicate info... */
    dir->next = parent->subs;		/* make us a sub dir of parent */
    parent->subs = dir;			/*  ... */
  } else {				/* if no parent then */
    V_ZERO(dir->volbm);			/* no ownership */
    dir->next = NILDIR;			/* no siblings */
  }
  dir->flags = 0;			/* no flags yet */
  dir->modified = 0;
  dir->eceidx = NOECIDX;		/* no index for enum cache */
  dir->edirid = -1;			/* create new external dirid */
  OSValidateDIDDirInfo(dir);		/* validate directory info */
  if (parent && (dir->flags & DID_DATA) == 0) {
    parent->subs = dir->next;	/* unlink it */
    free(dir->name);		/* nada */
    free(dir);			/* nada */
    return(NILDIR);
  }
  if (parent)
    OSValidateDIDDirInfo(parent);	/* revalidate parent */
  return(dir);
}

 
IDirP
Ipdirid(dir)			
IDirP dir;
{
  return(dir->pdir);			/* return parent */
}

IDirP lastcd = NILDIR;

/*
 * return an absolute path
 *
*/
char *
pathstr(cd)
IDirP cd;
{
  static char paths[MAXPATHLEN];
  char *ipathstr();

  if (lastcd == cd)			/* same as last request? */
    return(paths);			/* yes.. just return old paths */
  lastcd = cd;				/* else set new dir */
  return(ipathstr(cd,paths));		/* and do the work... */
}

private char *
ipathstr(cd,p)
IDirP cd;
char *p;
{
  int len;

  if (cd == rootd) 			/* check for root directory  */
    strcpy(p,"/");			/* at top of tree, init path */
  else {
    (void)ipathstr(cd->pdir,p);		/* recurse on parent until root */
    len = strlen(p);
    if (cd->pdir != rootd) 
      p[len++] = '/';			/* add path component */
    strcpy(p+len, cd->name);		/* concatenate current dir to path */
  }
  return(p);				/* and return a pointer... */
}

/*
 * return a path relative to vroot
 *
*/
char *
ppathstr(vrootd,cd)
IDirP vrootd,cd;
{
  static char path[MAXPATHLEN];
  int len;

  if (cd == vrootd) 			/* check for root directory  */
    strcpy(path,"");			/* at top of tree, init path */
  else {
    (void) ppathstr(vrootd,cd->pdir);	/* recurse on parent until root */
    len = strlen(path);
    if (cd->pdir != vrootd)		/* ... */
      path[len++] = '/';		/* add path component */
    strcpy(path+len, cd->name);		/* concatenate current dir to path */
  }
  return(path);
}


/*
 * void printtree(dir,start)
 *
 * Print the directory tree starting from dir, start is a copy
 * of dir.
 *
 */

private void
printtree(dir,start)
IDirP dir,start;
{
  if (dir == NILDIR)
    return;
  printf("Path %s Idirid = 0x%x = %d\n",pathstr(dir),dir,dir);
  printtree(dir->subs,start);
  if (dir != start) 
    printtree(dir->next,start);
}
 
/*
 * void InitDID()
 *
 * Called once to initialize directory id mechanism.
 *
 * Create root directory in rootd.
 *
 */
void
InitDID()
{
  ExtDir.xd_count = 0;			/* no known external dirs */
  ExtDir.xd_base = 320;			/* anything will do above EROOTD */
  ExtDir.xd_idsize = 100;		/* inital size of table */
  ExtDir.xd_idirs = (IDirP *) malloc(sizeof(IDirP)*100);
  rootd = mkdirset(NILDIR,"");		/* allocate root directory */
}

/*
 * InitDIDVol(dirid)
*/
InitDIDVol(dirid, volid)
IDirP dirid;
int volid;
{
  V_BITSET(dirid->volbm,volid);		/* remember ownership */
}

/*
 * IDirP Idirid(char *path,char *dn)
 * 
 * Make sure path is valid
 *
*/

IDirP
Idirid(path)
char *path;
{
  char c, *p;
  IDirP cd, ncd;
  int len;
 
  if (*path == '\0') {			/* any argument specified? */
    log("internal error: Idirid has a bad arg count\n");
    return(NILDIR);
  }
 
  /* scan down path, creating dirids as necessary */
  if (*path != '/') {			/* check if root is starting point? */
    if (DBDIR)
      log("internal error: Idirid has bad starting point %s\n",path);
  }
  len = strlen(path);		/* get length of path */
  while ((len-1) && path[len-1] == '/')	/* chew off trailing /s */
    len--;
  cd = rootd;
  do {
    while (*path == '/')		/* step to start of component  */
      path++,len--;

    /* find end */
    for (p = path; *p != '/' && len; p++, len--)
      /* NULL */;
    c = *p;			/* remember char here */
    *p = '\0';			/* change to null */
    ncd = nfind(cd->subs, path); /* find component if it exists */
    if (ncd == NILDIR) 
      cd = mkdirset(cd, path);	/* create new */
    else
      cd = ncd;
    *p = c;			/* set back to org. */
    path = p;
  } while (len && cd != NILDIR);
  return(cd);			/* final point */
}

/*
 *
 * IDirP Indirid(IDirP idirid,char *dn)
 *
 * Return an internal directory ID for the directory "path/dn" --
 * where path specifies the parent path and dn the directory name.
 * The string dn may be null in which case a directory id for path
 * is returned.
 *
 * This routine always returns an internal directory id, creating a
 * new IDir node if necessary.  One of only two routine which causes
 * the creation of new IDir nodes.
 *
 * WILL RETURN NULL IF PATH IS BAD
 */
IDirP
Idndirid(parent,dn)
IDirP parent;
char *dn;
{
  IDirP dp;

  if (dn == NULL || *dn == '\0')	/* is the name specified? */
    return(parent);			/* no, so return parent */
  dp = nfind(parent->subs,dn);		/* see if already present */
  if (dp != NILDIR)			/* yes... */
    return(dp);				/* return info */
  return(mkdirset(parent,dn));		/* create new directory */
}

/*
 * Idname(pdir, dirid)
 * 
 * return name of directory dirid in directory pdir
 *
 * MODIFY return value at your own risk!
 *
*/
char *
Idname(pdir, dirid)
IDirP pdir;
IDirP dirid;
{
  register IDirP p = pdir->subs;
  do {
    if (p == dirid)
      return(p->name);
    p = p->next;
  } while (p != NILDIR);
  return(NULL);
}

/*
 * sdword NewEDirid(IDirP idir)
 *
 * Allocate a new unique external directory id for a newly created
 * directory.  The id is is used as an index into a table of internal
 * directory ids.  The returned external id is this index plus some
 * random base number to map past EROOTD (2).
 *
 * If the table of internal directory pointers overgrows its bounds
 * then realloc the table at a larger size.
 *
 */

private sdword
NewEDirid(idir)
IDirP idir;
{
  sdword edir;

  if (ExtDir.xd_count >= ExtDir.xd_idsize) {
    ExtDir.xd_idirs = (IDirP *)		/* realloc larger table  */
      realloc((char *) ExtDir.xd_idirs,
	      sizeof(IDirP)*((unsigned) ExtDir.xd_idsize+100)); 
    ExtDir.xd_idsize += 100;		/* larger table now */
    if (DBDIR)
      printf("NewEDirid: Realloc occured.\n");
  }
  edir = ExtDir.xd_count;		/* current counter is idx */
  ExtDir.xd_count++;			/* increment count */
  ExtDir.xd_idirs[edir] = idir;		/* save new handle */
  return(ExtDir.xd_base+edir);		/* return base + idx */
}

/*
 * IDirP GetIDirid(sdword edir)
 *
 * Given an external ID check to see if we know about the external->internal
 * mapping by verifying the edir as an index into a table.
 *
 * If no known mapping then return NILDIR.
 *
 */

private IDirP
GetIDirid(edir)
sdword edir;
{
  edir -= ExtDir.xd_base;		/* subtract base */
  if (edir < 0 ||			/* below base? */
      edir > ExtDir.xd_count-1)	{	/* or above count? */
	if (DBDIR)			/* then invalid */
	  printf("GetIDirid: Bad directory idx %d, highest is %d\n",
		 edir,ExtDir.xd_count-1);
	return(NILDIR);			/* yes... not allocated */
      }
  return(ExtDir.xd_idirs[edir]);	/* return handle */
}


/*
 * IDirP EtoIdirid(sdword dirid,word volid)
 *
 * Convert an external directory id (dirid) to an internal directory
 * id.
 *
 * Internal directory ids are pointers of type IDir into the directory
 * tree built and maintained by these procedures.  There is only one
 * directory tree, and each AFP volume contains a root id which is the
 * mount point for that volume (which may be different from the
 * directory trees root of "/").
 *
 * There are two special external directory IDs, EROOTD (1) and
 * EPROOTD (2), for the volume's root directory and parent of root
 * directory.  
 *
 * If the external id is neither of these call GetIDirid to 
 * do the real work.
 *
 */

IDirP
EtoIdirid(dirid,volid)
sdword dirid;
int volid;
{
  IDirP VolRootD(),idir;

  if (dirid == EROOTD)			/* check for root id */
    return(VolRootD(volid));		/* yes, so return volumes root */
  if (dirid == EPROOTD)			/* check for parent of root */
    return(Ipdirid(VolRootD(volid)));	/* yes, so return that too... */
  idir = GetIDirid(dirid);		/* get internal dirid */
  if (idir != NILDIR &&			/* if directory exists and  */
      V_BITTST(idir->volbm,volid))	/* is on specified volume... */
    return(idir);			/* then return dirid */
  return(NILDIR);			/* else return nil directory */
}

/* 
 * sdword ItoEdirid(IDirP dirid, word volid)
 *
 * Convert an internal directory id to an external directory id.
 *
 * See EtoIdirid() above.
 *
 */

sdword
ItoEdirid(dirid,volid)
IDirP dirid;
int volid;
{
  IDirP rd,VolRootD();

  rd = VolRootD(volid);			/* fetch volumes root directory id */
  if (dirid == rd)			/* converting root id? */
    return(EROOTD);			/* yes, return special code */
  if (dirid == Ipdirid(rd))		/* converting parent of root? */
    return(EPROOTD);			/* yes, return code for that too */

  if (DBDIR && !V_BITTST(dirid->volbm,volid)) /* know this ownership? */
      printf("ItoEdirid: bad volid for %s\n",pathstr(dirid));

  if (dirid->edirid == -1)
    dirid->edirid = NewEDirid(dirid);
  if ((dirid->flags & DID_VALID) == 0)	/* validate info if invalid */
    OSValidateDIDDirInfo(dirid);

  return(dirid->edirid);		/* else return external form */
}

/*
 * OSErr EtoIFile(char *file, IDirP *idir, IDirP *ipdir, int *ivol
 *		  sdword edir, word evol, byte eptype, byte *epath);
 *
 * Convert external arguments which specify a file/dir into internal
 * handles.
 *
 * edir, evol, eptype and epath are the external ancestor directory
 * id, the external volume id, the path type and the external path.
 *
 * Returned values are file (the last component of the path), idir,
 * the directory handle if file is a directory, ipdir, the ancestor
 * handle, and ivol the internal volume id.
 *
 * This is the major routine for converting volume, dir, path type,
 * and path into unix form and proceeds as follows:
 *
 * Convert volume and ancestor directory (ivol, ipdir from evol and edir).
 *
 * Ignore the path type, we do not handle short path names.
 *
 * For each component in the path, convert the component name to internal
 * form and locate the component in the IDir tree.
 *
 * Return the last component name in file, and if this component exists 
 * in the IDir tree, return the handle in idir.  Set ipdir to be the
 * ancestor of the file.
 *
 * Only allow the volume root directory (dirid EROOTD) in the volume
 * root parent directory (dirid EPROOTD)
 *
 */
OSErr
EtoIfile(file,idir,ipdir,ivol,edir,evol,eptype,epath)
char *file;
IDirP *idir,*ipdir;
int *ivol;
sdword edir;
word evol;
byte eptype;
byte *epath;
{
  int pl;
  byte efn[MAXLFLEN+1],*fn;
  char c,lc;
  OSErr err;
  IDirP id;
  IDirP iprootd, irootd;	/* has parent of root and root respectively */

  /* Should we return an error on etype == shortname since we don't */
  /* support them? */

  *ivol = EtoIVolid(evol);		/* set internal volid */
  if (*ivol < 0)
    return(*ivol);			/* error */

  id = EtoIdirid(edir,*ivol);		/* fetch internal id */
  if (id == NILDIR)			/* exists? */
    return(aeParamErr);			/* no.... */
  irootd = VolRootD(*ivol);		/* get root directory internal id */
  /* assert(irootd != NULL) */
  iprootd = Ipdirid(irootd);		/* and then its parent */
  pl = *epath++;			/* pascal string length */
  lc = ' ';				/* non-null last char */

  for (fn=efn; pl-- > 0;) {
    c = *fn++ = *epath++;		/* copy the char */
    if (c == '\0') {			/* found a component seperator? */
      if (lc == '\0') {			/* yes.... was last char also null? */
	/* yes... then want parent since we have "null,null" */
	if (id == iprootd)		/* can't go above here! */
	  return(aeObjectNotFound);
	id = Ipdirid(id);		/* okay, move to parent */
      } else				/* otherwise */
	if (*efn != '\0') {		/* check if we have a component  */
	  if (id == iprootd) {
	    /* only possible subdir */
	    if (strcmp(efn, VolName(*ivol)) != 0)
	      return(aeObjectNotFound);
	    id = irootd;
	  } else  {
	    if ((err=EtoIName(efn,file)) != noErr) /* convert e to i */
	      return(err);
	    id = Idndirid(id,file);	 /*  and move to new */
	  }
	}
      fn = efn;				/* init ptr for next component */
    }
    lc = c;				/* remember last char */
    if (id == NILDIR) {			/* did we hit something bad? */
      printf("No such component %s\n",fn);
      return(aeParamErr);
    }
  }
  *fn = '\0';				/* tie off with a null */
  if (id == iprootd && *efn != '\0') {	/* special check */
    if (strcmp(efn, VolName(*ivol)) != 0)
      return(aeObjectNotFound);
    *file = '\0';
    id = irootd;
  } else
    if ((err=EtoIName(efn,file)) != noErr) /* convert last file component */
      return(err);

  if (*file == '\0') {			/* did we have a file name? */
    strcpy(file, id->name);
    if (id == iprootd)			/* tch, tch - don't want above here */
      return(aeObjectNotFound);
    *idir = id;				/* set directory name */
    *ipdir = Ipdirid(id);		/* set parent id */
  } else {
    /* disallow "." or ".." */
    if (file[0] == '.' &&
	(file[1] == '\0' || (file[1] == '.' && file[2] == '\0')))
      return(aeObjectNotFound);
    *ipdir = id;			/* else parent is dir itself */
    *idir = Idndirid(id,file);		/* and dir is possibly the file */
    /* can only access "rootd" in parent of root directory */
    if (id == iprootd && *idir != irootd)
      return(aeObjectNotFound);
  }
  return(noErr);
}


/*
 * dir_link(IDirP pdir, IDirP dir)
 *
 * Make the directory dir a subdirectory of parent pdir.
 *
 */

private void
dir_link(pdir,dir)
IDirP pdir,dir;
{
  dir->pdir = pdir;			/* set parent */
  dir->next = pdir->subs;		/* link to front */
  pdir->subs = dir;

}

/*
 * dir_unlink(IDirP pdir, IDirP dir)
 *
 * Remove the directory dir from it's parent pdir.
 *
 */

private void
dir_unlink(pdir,dir)
IDirP pdir,dir;
{
  IDirP prev,this;

  for (prev = NILDIR, this = pdir->subs;
       this != NILDIR && this != dir;
       prev = this, this = this->next);

  if (this == NILDIR) {			/* moby trouble */
    printf("dir_unlink: dir %s not found\n",this);
    return;
  }

  if (prev == NILDIR)			/* first on the list? */
    pdir->subs = this->next;		/* yes... link to parent */
  else
    prev->next = this->next;		/* else link to prev */
  this->next = NILDIR;			/* next no longer valid */
  this->pdir = NILDIR;			/* parent no longer known */
}

Idrdirid(ipdir, idir)
IDirP ipdir, idir;
{
  /* simple solution - simply unlink from extdir list and "mark" */
  /* it is as invalid - set the idir's extdir bad and when used */
  /* we will "revalidate" it.  Sufficient checking is done to */
  /* prevent returnning "bad" info anyway.  Basically, the whole */
  /* point is to prevent mac side from getting to entries which aren't */
  /* valid - this will simply eliminate work */
  ExtDir.xd_idirs[idir->edirid - ExtDir.xd_base] = NILDIR;
  idir->edirid = -1;
  idir->flags &= ~DID_VALID;
#ifdef notdef
  /* until problem of "old" ones is figured out */
  /* the fix is to make all things that "stash" dirids check validity */
  /* possibly store a refcnt in it to figure when we may kill off */
  dir_unlink(ipdir, idir);	/* unlink from the tree */
  ExtDir.xd_idirs[idir->edirid - ExtDir.xd_base] = NILDIR; /* set to nil */
  /* would like to delete space, but bad thing to do */
  idir->flags &= ~DID_VALID;	/* mark as not valid */
  idir->subs = NILDIR;		/* make sure not valid (shouldn't be) */
#endif
}

/*
 * Idmove(IDirP fpdir, char *from, IDirP tpdir, char *to)
 *
 * Maintains consistency in internal structures when a directory
 * is renamed or moved.
 *
 * The directory "from" in parent fpdir is being renamed to be
 * "to" in the parent tpdir.  Because directory ids may not
 * change we must modify the tree instead of recreating nodes.
 *
 */ 
void
Idmove(fpdir,from,tpdir,to)
IDirP fpdir,tpdir;
char *from,*to;
{
  IDirP fdir;

  if (DBFIL) {
    printf("Idmove: changing path=%s, file=%s",pathstr(fpdir),from);
    if (tpdir == fpdir)
      printf(" to new name %s\n",to);
    else
      printf(" to path=%s, file=%s\n",pathstr(tpdir),to);
  }

  fdir = nfind(fpdir->subs,from);	/* locate source dir */
  
  if (fdir == NILDIR) {
    printf("Idmove: no known directory %s\n",from);
    return;
  }

  if (strcmp(from,to) != 0) {		/* if different names then... */
    free(fdir->name);			/* release the old name */
    fdir->name = (char *) malloc((unsigned) strlen(to)+1);
    strcpy(fdir->name,to);		/* copy new name */
  }

  if (fpdir != tpdir) {			/* if different parents then... */
    if (nfind(tpdir->subs,to) != NILDIR) {
      printf("Idmove: name already exists %s\n",to);
      return;
    }
    dir_unlink(fpdir,fdir);		/* unlink from old parent */
    dir_link(tpdir,fdir);		/* relink into new parent */
  }
  lastcd = NILDIR;			/* names have changed  */
}

static char *hexdigits = "0123456789abcdef";

/* problem with length of enp */

byte *
ItoEName(in,enp)
char *in;
byte *enp;
{
  char c,c2;
  char *cp,*cp2;
  byte *en = enp;

  while ((c = *in++) != '\0') {
    if (c != ':')
      *en++ = c;
    else {
      /* must convert to external form */
      if ((c = *in++) == '\0' || (c2 = *in++) == '\0') {
	*en++ = '|';
	if (c != '\0')
	  *en++ = (c == ':') ? '|' : c;	/* found null, deposit c or | */
	break;				/* done with while */
      }
      if ((cp = index(hexdigits,c)) == NULL || 
	  (cp2 = index(hexdigits,c2)) == NULL) 
	{
	  *en++ = '|';				/* deposit initial | */
	  *en++ = (c == ':') ? '|' : c;		/* deposit c or | */
	  *en++ = (c2 == ':') ? '|' : c2;	/* deposit c2 or | */
	  continue;				/* continue with while */
	}

#ifndef hpux
      *en++ = ((cp-hexdigits) << 4) | (cp2-hexdigits);
#else
      /* hpux compiler barfs on the above */
      *en = ((cp-hexdigits) << 4);
      *en |= (cp2-hexdigits);
      en++;
#endif
    }
  }	
  *en++ = '\0';
  return(enp);
}	

OSErr
EtoIName(en,inp)
register byte *en;		/* max is 31 or so */
char *inp;
{
  byte c;			/* unsigned char */
  register char *in = inp;
  register int cnt = 0;

  while ((c = *en++) != '\0') {
    if (isascii(c) && !iscntrl(c) && isprint(c) && c != '/') {
      *in++ = c;
      cnt++;
    } else {
      /* must convert to */
      *in++ = ':';			/* : */
      *in++ = hexdigits[(c >> 4) & 0xf];
      *in++ = hexdigits[(c & 0xf)];
      cnt += 3;
    }
  }
  *in++ = '\0';
  if (cnt > MAXNAMLEN)
    return(aeAccessDenied);	/* bogus */
  return(noErr);
}

/*
 * Given an internal file name, compute the length of the external
 * file name
 */
int
ENameLen(in)
register char *in;
{
  register int len = 0;
  register char c;
  register char c2;

  while ((c = *in++) != '\0') {
    if (c != ':')
      len++;
    else {
      /* must convert to external form */
      if ((c = *in++) == '\0' || (c2 = *in++) == '\0') {
	len++;
	if (c != '\0')
	  len++;
	break;				/* done with while */
      }
      if (index(hexdigits,c) == NULL || index(hexdigits,c2) == NULL) 
	len += 3;
      else
	len++;
    }
  }	
  return(len);
}	

void
EModified(dirid)
IDirP dirid;
{
  /* what to do on overflow of 2^35-1? */
  dirid->modified++;			/* push the modified flag */
  VolModified(dirid->volbm);		/* and here too! */
}
