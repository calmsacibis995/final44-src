/*
 *  Author: cck    Date: 88/03/30 11:52:01  
 *  Header: afposfi.c,v 1.29 88/03/30 11:52:01 cck Rel  
 *  Revision: 1.29  
*/

/*
 * afposfi.c - Appletalk Filing Protocol OS FNDR File Interface. 
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  March 1987     Schilit	Created.
 *  Jan   1988     CCKim        New finderinfo format
 *
 */

#include <stdio.h>
#include <errno.h>
extern int errno;
#include <sys/param.h>
#ifndef _TYPES
# include <sys/types.h>
#endif
#include <sys/file.h>
#include <sys/stat.h>
#include <netinet/in.h>  /* for htons, htonl */
#include <netat/appletalk.h>
#include <netat/compat.h>
#include <netat/afp.h>
#include "afps.h"
#include "afpgc.h"
#ifdef NEEDFCNTLDOTH
# include <fcntl.h>
#endif
#include "afpudb.h"

typedef struct FCacheEnt {
  struct FCacheEnt *next;	/* link for free queue */
  IDirP fe_pdir;		/* directory */
  int fe_okay;			/* last internal modify count */
  char  *fe_fnam;		/* file */
  /* should we use ctime instead perhaps? */
  time_t fe_mtime;		/* last modify time: file system */
  time_t fe_vtime;		/* last time validated */
  FileInfo fe_fi;		/* file info */
} FCacheEnt;
 
export GCHandle *fich;		/* handle on cache */
private FCacheEnt *fce, *lfce;	/* recycle purge-load */
private FCacheEnt *getfe;	/* last os_getfi */

private int fc_valid();
private int fc_compare();
private char *fc_load();
private void WriteFA();
private void fc_purge();
private void fc_flush();
private void fc_flush_start();
private void fc_flush_end();
private FileInfo *os_getfi();

#define FICacheSize 128
/* Each cache entry has a lifetime that it goes through before it must */
/* be revalidated before reuse: this prevents cache entries from getting */
/* "stale". */
/* The revalidation consists of seeing if the disk copy has changed */
#define FI_VALID_TIME (60*5)		/* 5 minutes */

InitOSFI()
{
  fich = GCNew(FICacheSize,fc_valid,fc_compare,fc_load,fc_purge,fc_flush);
  lfce = fce = (FCacheEnt *) 0; 
  getfe = (FCacheEnt *) 0;
}



/*
 * Our flush doesn't flush modified entries since our cache is
 * write through, but attempts instead to check validity of items in
 * our cache
 *
 * can bracket with fc_flush_start and fc_flush_end to reduce # of
 *  stats.  This depends on the .finderinfo directory modify time
 *  getting changed when a finderinfo entry is modified.  WriteFA
 *  guarantees this as best it can (can you say hack?)
 *
 *
*/
private time_t fcf_val_time = 0; /* validate time */
private IDirP fcf_val_dir = NILDIR; /* directory val time is for */

private void
fc_flush_start(pdir)
IDirP pdir;
{
  char path[MAXPATHLEN];
  struct stat stb;

  OSfname(path, pdir, "", F_FNDR); /* get directory */
  if (stat(path, &stb) < 0) {
    fcf_val_dir = NILDIR;
    fcf_val_time = 0;
    return;			/* nothing else we can do */
  }
  fcf_val_dir = pdir;
  fcf_val_time = stb.st_mtime;	/* remember */
}

private void
fc_flush_end()
{
  fcf_val_time = 0;		/* mark none */
  fcf_val_dir = NILDIR;
}

private void
fc_flush(fe, pdir)
FCacheEnt *fe;
IDirP pdir;
{
  char path[MAXPATHLEN];
  struct stat stb;

  /* if passed directory isn't nildir (flush all), then the file */
  /* will only be check if the particular item has the same directory */
  if (pdir != NILDIR && (fe->fe_pdir != pdir))
    return;
  if ((fe->fe_pdir->flags & DID_FINDERINFO)) { /* always okay */
    OSfname(path, fe->fe_pdir, fe->fe_fnam, F_FNDR);
    /* if we have a .finderinfo directory update time */
    /* and it is more recent than cache entry, then check the */
    /* cache entry */
    /* also add a check against vtime.  Makes it much more useful */
    /* since it is more than likely that fcf_val_time is later */
    /* than the mtime for the majority of the files */
    if (fcf_val_dir == fe->fe_pdir &&
	(fcf_val_time > fe->fe_mtime) &&
	(fcf_val_time > fe->fe_vtime)) {
      if (stat(path, &stb) < 0)
	return;				/* nothing else we can do */
      if (stb.st_mtime != fe->fe_mtime)	/* reload entry */
	fe->fe_okay = FALSE;		/* make entry as bad */
    }
  }
  time(&fe->fe_vtime);			/* mark last validate time */
}

private
fc_valid(fe)
FCacheEnt *fe;
{
  char path[MAXPATHLEN];
  struct stat stb;
  time_t mtime;

  if (!fe->fe_okay)			/* if not okay, don't */
    return(fe->fe_okay);		/* bother with checks */
  time(&mtime);
  if (fe->fe_vtime + FI_VALID_TIME < mtime) {
    fe->fe_vtime = mtime;		/* mark as new validate time */
    if ((fe->fe_pdir->flags & DID_FINDERINFO) == 0) /* always okay */
      return(fe->fe_okay);
    OSfname(path, fe->fe_pdir, fe->fe_fnam, F_FNDR);
    if (stat(path, &stb) < 0)
      return(fe->fe_okay);		/* nothing else we can do */
    if (stb.st_mtime != fe->fe_mtime)	/* reload entry */
      return(FALSE);			/* bad entry */
  }
  return(fe->fe_okay);
}

private void
fc_purge(fe)
FCacheEnt *fe;
{
  if (DBOSI)
    printf("fc_purge: %s\n",fe->fe_fnam);
  
  if (fe == getfe)			/* purging last get? */
    getfe = (FCacheEnt *) 0;		/* yes... then zero */
  
  free(fe->fe_fnam);			/* always free the name */
  fe->fe_fnam = (char *) 0;		/*  and zero... */
  fe->next = NULL;			/* trash it here since want in both */
  if (fce == (FCacheEnt *) 0)		/* check for recycled entry */
    lfce = fce = fe;			/* if none then save */
  else {
    lfce->next = fe;			/* put at end of free list */
    lfce = fe;				/* remember the end */
#ifdef notdef
    free(fe);				/* and the struct itself */
#endif
  }
}

private
fc_compare(fe,key)
FCacheEnt *fe,*key;
{
  if (fe->fe_pdir != key->fe_pdir)
    return(FALSE);
  return(strcmp(fe->fe_fnam,key->fe_fnam) == 0);
}

private char *
fc_load(key)
FCacheEnt *key;
{
  FCacheEnt *fe;
  
  if (DBOSI)
    printf("fc_load: %s\n",key->fe_fnam);

  if (fce != (FCacheEnt *) 0) {		/* recycled fc avail? */
    fe = fce;				/* yes... use that */
    fce = fce->next;
  } else				/* else allocate */
    fe = (FCacheEnt *) malloc(sizeof(FCacheEnt));

  fe->fe_pdir = key->fe_pdir;
  fe->fe_fnam = (char *) malloc(strlen(key->fe_fnam)+1);
  fe->fe_okay = TRUE;
  fe->fe_mtime = 0;
  time(&fe->fe_vtime);			/* validate time stamp */
  strcpy(fe->fe_fnam,key->fe_fnam);
  fc_readent(fe);
  return((char *) fe);
}



private
fc_readent(fe)
FCacheEnt *fe;
{
  struct stat stb;
  char path[MAXPATHLEN];
  int fd, ft, len, err;
  FileInfo *fi = &fe->fe_fi;
  FinderInfo *fndr;
  extern struct ufinderdb uf[];
  
  bzero((char *) fi,sizeof(FileInfo)); /* make sure clear before */
  if (fe->fe_pdir->flags & DID_FINDERINFO) {
    OSfname(path,fe->fe_pdir,fe->fe_fnam,F_FNDR); 
    if (DBOSI)
      printf("fc_readent: reading %s\n",path);

    fd = open(path,O_RDONLY);
    if (fd >= 0) {
      OSLockFileforRead(fd);
      err = fstat(fd, &stb);
      len = read(fd,(char *) fi,sizeof(FileInfo));
      OSUnlockFile(fd);
      if (len < FI_BASELENGTH) {
	close(fd);
	if (len == 0)		/* length zero means creat'd */
	  goto dummy;
	if (DBOSI)
	  printf("fc_readent: finderinfo too short\n");
	goto nofileinfo;
      }
      if (fi->fi_magic1 != FI_MAGIC1) {
	OldFileInfo *ofi = (OldFileInfo *)fi;

	bcopy(ofi->fi_comnt, fi->fi_comnt, fi->fi_magic1);
	fi->fi_comln = fi->fi_magic1;
	if (ofi->fi_attr & FI_ATTR_SETCLEAR)
	  fi->fi_attr = ofi->fi_attr &
	    (FI_ATTR_READONLY|FI_ATTR_MUSER|FI_ATTR_INVISIBLE);
	else
	  fi->fi_attr = 0;
	fi->fi_magic1 = FI_MAGIC1;
	fi->fi_magic = FI_MAGIC;
	fi->fi_version = FI_VERSION;
	fi->fi_bitmap = FI_BM_MACINTOSHFILENAME;
	ItoEName(fe->fe_fnam, fi->fi_macfilename);
	/* make sure we update it */
	WriteFA(fe->fe_pdir, fe->fe_fnam, fi);
      } else {
	if (fi->fi_magic != FI_MAGIC || fi->fi_version != FI_VERSION) {
	  if (DBOSI)
	    printf("fc_readent: fileinfo check fail\n");
	  close(fd);
	  goto nofileinfo;
	}
	fi->fi_attr = ntohs(fi->fi_attr);
	if (err == 0)		/* stat okay */
	  fe->fe_mtime = stb.st_mtime;	/* remember mtime */
      }
      if (close(fd) != 0)
	printf("fc_readent: close error");
      return(noErr);
    }

    /* Open failed for .finderinfo file.  Use defaults finfo or zero if dir */

    if (DBOSI)
      printf("fc_readent: Open failed for %s\n",path);
  }

nofileinfo:

  /* convert name to internal name */
  OSfname(path,fe->fe_pdir,fe->fe_fnam,F_DATA); /* create plain name */
  if (stat(path,&stb) != 0)		/* check if it exists */
    return(aeObjectNotFound);		/* no... */
  if (S_ISDIR(stb.st_mode)) {
    fi->fi_comln = 0;
  } else {
    ft = os_getunixtype(path, &stb);
    fndr = (FinderInfo *)fi->fi_fndr; /* get pointer to finder info */
    bcopy(uf[ft].ufd_ftype, fndr->file.fdType, sizeof(fndr->file.fdType));
    bcopy(DEFFCREATOR,fndr->file.fdCreator, sizeof(fndr->file.fdCreator));
    bcopy(uf[ft].ufd_comment, fi->fi_comnt, uf[ft].ufd_commentlen);
    fi->fi_comln = uf[ft].ufd_commentlen;
  }
  fi->fi_attr = DEFATTR;	/* set default attributes */
dummy:
  fi->fi_magic1 = FI_MAGIC1;
  fi->fi_version = FI_VERSION;
  fi->fi_magic = 0;		/* mark as "default" entry */
  fi->fi_bitmap = FI_BM_MACINTOSHFILENAME;
  ItoEName(fe->fe_fnam, fi->fi_macfilename);  
  return(noErr);
}

private void
WriteFA(ipdir,fn,fi)
IDirP ipdir;
char *fn;
FileInfo *fi;
{
  char path[MAXPATHLEN];
  int fd;
  int needu = 0;

  if ((ipdir->flags & DID_FINDERINFO) == 0) {
    if (DBOSI)
      printf("WriteFA skipped, no finderinfo directory\n");
    return;
  }
  OSfname(path,ipdir,fn,F_FNDR); 	/* convert to internal name */

  if (DBOSI)
    printf("WriteFA: writing %s\n",path);

  needu++;
  if ((fd = open(path,O_WRONLY)) < 0) {		/* open for write */
    if (errno != ENOENT) {
      printf("WriteFA: error openning %s errno=%d\n",path,errno);
      return;
    }
    if ((fd = open(path,O_WRONLY|O_CREAT,0666)) < 0) {
      if (DBOSI)
	printf("fc_flush: create failed for %s %d\n",path,errno);
      return;
    }
    if (DBOSI)
      printf("fc_flush: created %s\n",path);
  } else needu++;
  fi->fi_attr = htons(fi->fi_attr); /* swab!!!@ */
  fi->fi_magic = FI_MAGIC;
  OSLockFileforWrite(fd);
  (void)write(fd,(char *) fi,sizeof(FileInfo)); /* write stuff */
  OSUnlockFile(fd);
  if (close(fd) != 0)
    printf("WriteFA: close error");
  /* horrible hack, but can't use utimes, because we must be owner then */
  if (needu) {			/* update directory modified time */
    OSfname(path,ipdir,FIDIRFN,F_FNDR);	/* pick bad name */
    if ((fd = open(path, O_WRONLY|O_CREAT,0666)) < 0)
      return;
    close(fd);
    unlink(path);
  }
/*  EModified(fe->fe_pdir);		/* and mark directory as modified */
}

private FileInfo *
os_getfi(pdir,fn)
IDirP pdir;
char *fn;
{
  FCacheEnt key;

  key.fe_pdir = pdir;
  key.fe_fnam = fn;
  
  /* do the "quick" check first */
  if (getfe == 0 || !fc_compare(getfe,&key)) {
    /* nope, either find in cache or load from disk */
    getfe = (FCacheEnt *)GCLocate(fich,(char *)&key);
  }
  return(&getfe->fe_fi);		/* and return the FileInfo */
}

FModified(pdir, fn)
IDirP pdir;     
char *fn;
{
  FCacheEnt key;
  int idx;

  key.fe_pdir = pdir;
  key.fe_fnam = fn;

  EModified(pdir);		/* make parent directory as modified */
  if (getfe == 0 || !fc_compare(getfe,&key)) {
    /* no kept entry */
    if (!GCScan(fich, &key, &idx)) /* not in cache, already flushed */
      return;
    getfe = (FCacheEnt *)GCidx2ent(fich, idx);

  }
  if (DBOSI)
    printf("Invalidating file cache entry %s/%s\n",pathstr(pdir),fn);
  getfe->fe_okay = FALSE;		/* invalidate entry */
}

/*
 * OSValidateFICacheforEnum(directory)
 *
 * validate a file cache for enumerate
 *
 *  make fc_flush only stat if .finderinfo directory modification time
 *  has changed -- writefa guarantees us that
 * 
*/
OSValFICacheForEnum(pdir)
IDirP pdir;
{
  fc_flush_start(pdir);
  GCFlush(fich, pdir);		/* make sure valid */
  fc_flush_end();
}

/*
 * OSSetFA(IDirP pdir, char *fn, word bm, FileDirParm *fdp)
 *
 * Set finder and attr for a file specified by ancestor directory
 * (pdir) and file name (fn).  The bitmap in bm specifies which
 * FP_FINFO (DP_FINFO) or FP_ATTR (DP_ATTR) are to be set.
 *
 */
OSSetFA(pdir,fn,bm,fdp)
IDirP pdir;     
char *fn;
word bm;
FileDirParm *fdp;
{
  FileInfo *fi;
  word attr;

  fi = os_getfi(pdir,fn);
  if (bm & FP_ATTR) {
    attr = fdp->fdp_attr;
    /* limit to these: allow readonly and MUSER even if directory */
    attr &= (FI_ATTR_READONLY|FI_ATTR_MUSER|FI_ATTR_INVISIBLE);
    if (fdp->fdp_attr & FI_ATTR_SETCLEAR)
      fi->fi_attr |= attr;
    else
      fi->fi_attr &= ~attr;
  }
  if (bm & FP_FINFO)
    bcopy(fdp->fdp_finfo,fi->fi_fndr,FINFOLEN);
  if (bm & (FP_ATTR|FP_FINFO))
    WriteFA(pdir,fn,fi);
  return(noErr);
}

OSGetAttr(pdir,fn,attr)
IDirP pdir;
char *fn;
word *attr;
{
  FileInfo *fi;

  fi = os_getfi(pdir,fn);
  *attr = fi->fi_attr;
  return(noErr);
}

OSGetFNDR(pdir,fn,finfo)
IDirP pdir;
char *fn;
byte *finfo;
{
  FileInfo *fi;

  fi = os_getfi(pdir,fn);
  bcopy(fi->fi_fndr,finfo,FINFOLEN);
  return(noErr);
}

OSSetComment(pdir,fn,cs,cl)
IDirP pdir;
char *fn;
byte *cs;
byte cl;
{
  FileInfo *fi;

  fi = os_getfi(pdir,fn);
  bcopy(cs,fi->fi_comnt,cl);
  fi->fi_comln = cl;
  WriteFA(pdir,fn,fi);
  return(noErr);
}

OSGetComment(pdir,fn,cs,cl)
IDirP pdir;
char *fn;
byte *cs;
byte *cl;
{
  FileInfo *fi;
  
  fi = os_getfi(pdir,fn);
  *cl = fi->fi_comln;
  if (*cl == 0)
    *cs = 0;
  bcopy(fi->fi_comnt,cs,*cl);
  return(noErr);
}

/*
 * Establish the mac file name after a os_move
 *
*/
OSSetMacFileName(pdir, fn)
IDirP pdir;
char *fn;
{
  FileInfo *fi;
  
  fi = os_getfi(pdir,fn);
  ItoEName(fn, fi->fi_macfilename);
  WriteFA(pdir, fn, fi);
  return(noErr);
}
