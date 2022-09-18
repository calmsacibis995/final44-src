/*
 *  Author: cck    Date: 88/02/23 17:15:33  
 *  Header: afpdir.c,v 1.19 88/02/23 17:15:33 cck Rel  
 *  Revision: 1.19  
*/

/*
 * afpdir.c - Appletalk Filing Protocol Directory Level Routines
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

/*
 * Non OS dependant support routines for:
 *
 * FPGetDirParms()
 * FPSetDirParms()
 * FPOpenDir()
 * FPCloseDir()
 * FPEnumerate()
 * FPCreateDir()
 * FPGetFileDirInfo()
 *
 */

#include <stdio.h>
#include <sys/param.h>
#ifndef _TYPES
 /* assume included by param.h */
# include <sys/types.h>
#endif
#include <netat/appletalk.h>
#include <netat/afp.h>
#include <netat/afpcmd.h>
#include "afpntoh.h"
#include "afps.h"			/* common server header */

/*
 * OSErr FPGetDirParms(byte *p,byte *r,int *rl)
 *
 * This call is used to retrieve parameters for a particular directory.
 *
 */

OSErr
FPGetFileDirParms(p,l,r,rl)
byte *p,*r;
int l;
int *rl;
{
  GetFileDirParmsPkt gfdp;
  FileDirParm fdp;
  IDirP idir,ipdir;
  char file[MAXUFLEN];
  int ivol,err;

  ntohPackX(PsGetFileDirParms,p,l,(byte *) &gfdp);

  err = EtoIfile(file,&idir,&ipdir,&ivol,gfdp.gdp_dirid,
		 gfdp.gdp_volid,gfdp.gdp_ptype,gfdp.gdp_path);

  if (err != noErr) {
    if (DBFIL || DBDIR)
      printf("FPGetFileDirParms: EtoIfile returns %d\n",err);
    return(err);
  }

  fdp.fdp_pdirid = ItoEdirid(ipdir,ivol);
  fdp.fdp_dbitmap = gfdp.gdp_dbitmap;
  fdp.fdp_fbitmap = gfdp.gdp_fbitmap;
  fdp.fdp_zero = 0;
  err = OSFileDirInfo(ipdir,idir,file,&fdp,ivol); /* fill in information */
  if (err != noErr) {
    if (DBFIL || DBDIR)
      printf("FPGetFileDirParms: OSFileDirInfo returns %d on %s/%s\n",
	     err,pathstr(ipdir),file);
    return(err);
  }
  if (FDP_ISDIR(fdp.fdp_flg)) {
    *rl = htonPackX(DirParmPackR,(byte *)&fdp,r);
    *rl += htonPackX(DirPackR,(byte *)&fdp,r+(*rl));
  }
  if (!FDP_ISDIR(fdp.fdp_flg)) {
    *rl = htonPackX(DirParmPackR,(byte *)&fdp,r);    
    *rl += htonPackX(FilePackR,(byte *)&fdp,r+(*rl));
  }
  return(noErr);
}

/*
 * OSErr FPEnumerate(...)
 *
 * This call is used to enumerate the contents of a directory.  The
 * reply is composed of a number of file and/or directory parameter
 * structures.
 *
 */

OSErr 
FPEnumerate(p,l,r,rl)
byte *p,*r;
int l;
int *rl;
{
  FileDirParm fdp;
  EnumeratePkt enup;
  EnumerateReplyPkt enpr;
  IDirP idir,ipdir;
  char file[MAXUFLEN];
  byte *cntptr;
  int ivol,stidx,idx,maxidx;
  word cnt;
  int reqcnt,maxreply,len,elen,err;
  extern int sqs;		/* maximum send qs */

  ntohPackX(PsEnumerate,p,l,(byte *) &enup);
  err = EtoIfile(file,&idir,&ipdir,&ivol,enup.enu_dirid,
		 enup.enu_volid,enup.enu_ptype,enup.enu_path);

  if (err != noErr)
    return(err);

  /* set the bitmaps for return message and packing */
  
  fdp.fdp_fbitmap = enpr.enur_fbitmap = enup.enu_fbitmap;
  fdp.fdp_dbitmap = enpr.enur_dbitmap = enup.enu_dbitmap;

  /* set the parent dirid to the enumerated directory */

  fdp.fdp_pdirid = ItoEdirid(idir,ivol); 

  /* fetch the max size of a reply packet, start index, request count */

  maxreply = enup.enu_maxreply;
  maxreply = min(sqs, maxreply);
  stidx = enup.enu_stidx;
  reqcnt = enup.enu_reqcnt;

  maxidx = OSEnumInit(idir);		/* init, and fetch count of entries */
  if (maxidx < 0)			/* error? */
    return(maxidx);			/* return error */

  if (stidx > maxidx) {			/* start index gt count of entries? */
    OSEnumDone(idir);
    return(aeObjectNotFound);		/* yes... object not found then */
  }

  cntptr = &r[ENUR_ACTCNT_OFF];		/* address of packed actcnt word */

  len = htonPackX(EnumPackR,(byte *)&enpr,r);

  /* starting with the file/directory at stidx, load upto reqcnt
   * entries into the reply buffer.  The size of the reply buffer must
   * not exceed maxreply bytes.  Do not include a file/directory if
   * the associated bitmap is zero.
   */

  for (idx=stidx,cnt=0; idx <= maxidx && cnt < reqcnt; idx++) {
    elen = EnumPack(idir,&fdp,ivol,idx,&r[len]);
    if (elen > 0) {			/* something packed for this entry? */
      if (len+elen > maxreply)		/* yes... check if overflow */
	break;				/* yes.. break out */
      cnt++;				/* else include entry in count */
      len += elen;			/* include entry in len */
      if (len > maxreply-30)		/* if close to the limit */
	break;				/*  then break out now */
    }
  }

  OSEnumDone(idir);			/* finished with enumerate */

  if (cnt == 0)				/* filter tossed all */
    return(aeObjectNotFound);

  PackWord(cnt,cntptr);			/* pack the actual count */
  *rl = len;				/* length of packet for reply */

  if (DBDIR)
    printf("OSEnum: maxreply=%d, ourreply=%d, reqcnt=%d, ourcnt=%d\n",
	   maxreply,len,reqcnt,cnt);
  
  return(noErr);			/* all ok */
}

/*
 * int EnumPack(IDirP ipdir, FileDirParm *fdp, int ivol, 
 *		int idx, byte *r);
 *
 * Pack a single enumeration entry as specified by the enumeration
 * idx and the enumeration direcotry ipdir.
 *
 * Fetch file/directory information for the entry as specified by
 * the parent directory (ipdir), the volume (ivol), and the name
 * from enumeration index (idx).
 *
 * If the file bitmap passed in fdp is zero and the entry is a file
 * then return 0.  If the directory bitmap passed in fdp is zero and
 * the entry is a directory then return 0.  
 *
 * In the normal case pack a length byte, directory flag byte, and
 * the file/directory information as specified by the fdp bitmaps
 * int r and return the length of of this entry.
 *
 */ 

private int
EnumPack(ipdir,fdp,ivol,idx,r)
IDirP ipdir;
FileDirParm *fdp;
int ivol,idx;
byte *r;
{
  char *fn;
  int len;
  int err;

  fn = (char *) OSEnumGet(ipdir,idx);	/* get the file name */
  /* and the info for this entry (nildir - no info on whether */
  /* directory or not) */
  err = OSFileDirInfo(ipdir,NILDIR,fn,fdp,ivol);
  if (err == aeAccessDenied)		/* if no access */
    return(0);				/*  then forget the entry */

  if (FDP_ISDIR(fdp->fdp_flg)) {	/* if a directory */
    if (fdp->fdp_dbitmap == 0)		/*  and dir bitmap is zero */
      return(0);			/*  then skip the entry */
    len = htonPackX(DirPackR,(byte *) fdp,r+2);	/* else pack */
  }  else {				/* else, if a file */
    if (fdp->fdp_fbitmap == 0)		/*  and file bitmap is zero  */
      return(0);			/*  then skip the entry */
    len = htonPackX(FilePackR,(byte *) fdp,r+2); /* else pack */
  }

  len += 2;				/* include size, flg into sum */
  if ((len % 2) != 0)			/* if odd number of bytes */
    r[len++] = 0;			/* then even out the length */
  r[0] = (byte) len;			/* store length of structure */
  r[1] = fdp->fdp_flg;			/* directory flag */
  return(len);				/* return length of this item */
}

/*ARGSUSED*/
OSErr
FPSetDirParms(p,l,r,rl)
byte *p,*r;
int l;
int *rl;
{
  SetDirParmsPkt sdp;
  FileDirParm fdp;
  IDirP ipdir,idir;
  int ivol,len,err;
  char file[MAXUFLEN];

  len = ntohPackX(PsSetDirParms,p,l,(byte *) &sdp);
  ntohPackXbitmap(ProtoDirAttr,p+len,l-len,
		  (byte *) &fdp,sdp.sdp_bitmap);

  err = EtoIfile(file,&idir,&ipdir,&ivol,sdp.sdp_dirid,
		 sdp.sdp_volid,sdp.sdp_ptype,sdp.sdp_path);
  if (err != noErr)
    return(err);  

  fdp.fdp_dbitmap = sdp.sdp_bitmap;	/* using this bitmap  */

  if (DBDIR) 
    printf("FPSetDirParms: path=%s, file=%s, bm=%d\n",
	   pathstr(ipdir),file,sdp.sdp_bitmap);

  err = OSSetDirParms(ipdir,file,&fdp);	/* set dirparms */
  if (err == noErr)
    VolModified(ivol);
  return(err);
}
  
OSErr 
FPOpenDir()
{
  return(aeParamErr);
}


OSErr 
FPCloseDir()
{
  return(aeParamErr);
}


OSErr
FPCreateDir(p,l,r,rl)
byte *p,*r;
int l;
int *rl;
{
  CreateDirPkt crd;
  IDirP idir,ipdir;
  int ivol,err;
  char file[MAXUFLEN];

  ntohPackX(PsCreateDir,p,l,(byte *) &crd);

  err = EtoIfile(file,&idir,&ipdir,&ivol,crd.crd_dirid,
		 crd.crd_volid,crd.crd_ptype,crd.crd_path);
  if (err != noErr)
    return(err);

  if (DBFIL)
    printf("FPCreateDir: create path=%s name=%s\n",pathstr(ipdir),file);

  if ((err = OSCreateDir(ipdir,file, &idir)) == noErr) {
    PackDWord(ItoEdirid(idir,ivol),r);
    *rl = 4;
  }
  if (err == noErr)			/* if success  */
    VolModified(ivol);			/*  then volume modified */
  return(err);
}


/*
 * Preliminary version - just does files
 *
*/

/*ARGSUSED*/
OSErr
FPSetFileDirParms(p,l,r,rl)
byte *p, *r;
int l;
int *rl;
{
  SetFileDirParmsPkt scp;
  FileDirParm fdp;
  IDirP idir,ipdir;
  char file[MAXUFLEN];
  int ivol,len,err;

  len = ntohPackX(PsSetFileDirParms,p,l,(byte *) &scp);
  ntohPackXbitmap(ProtoFileDirAttr,p+len,l-len,(byte *) &fdp,scp.scp_bitmap);

  err = EtoIfile(file,&idir,&ipdir,&ivol,scp.scp_dirid,
		 scp.scp_volid,scp.scp_ptype,scp.scp_path);
  if (err != noErr)
    return(err);

  fdp.fdp_dbitmap = fdp.fdp_fbitmap = scp.scp_bitmap;

  if (DBFIL) 
    printf("FPSetFileDirParms: setting bm=%d for %s %s\n",
	   scp.scp_bitmap,pathstr(ipdir),file);

  return(OSSetFileDirParms(ipdir,idir,file,&fdp));
}
