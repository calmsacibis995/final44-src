/*
 *  Author: cck    Date: 88/02/23 17:16:11  
 *  Header: afpfork.c,v 1.23 88/02/23 17:16:11 cck Rel  
 *  Revision: 1.23  
*/

/*
 * afpfork.c - Appletalk Filing Protocol Fork Level Routines
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
 *  FPGetForkParms()
 *  FPSetForkParms()
 *  FPOpenFork()
 *  FPCloseFork()
 *  FPRead()
 *  FPWrite() 
 *  FPFlushFork()
 *  FPByteRangeLock()
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
#include "afps.h"
#include "afpntoh.h"
#include "afposncs.h"
 

typedef struct {
  int ofn_fd;			/* file descriptor */
  sdword ofn_pos;		/* file position */
  IDirP ofn_ipdir;
  int ofn_ivol;
  int ofn_efn;			/* external file number */
  char ofn_fnam[MAXUFLEN];	/* file name */
  int ofn_mode;
  int ofn_type;			/* data or rsrc */
  int ofn_flgs;			/* file flags */
#define OF_EOF  0x020		/*  eof on file */
#define OF_NOTOPEN   0x02	/* to support non-existent files */
#define OF_INUSE 0x04		/* OFN is in use */
  int ofn_trans_table;		/* Translation table if any */
} OFN;

#define MaxOFN 30

private OFN OFNTBL[MaxOFN];

private int oinit = FALSE;

private
iniofn()
{
  int i;

  for (i=0; i < MaxOFN; i++) {
    OFNTBL[i].ofn_flgs = 0;
    OFNTBL[i].ofn_trans_table = -1; /* no index */
    OFNTBL[i].ofn_efn = i+1;
  }
  oinit = TRUE;
}

private word
ItoEOFN(o)
OFN *o;
{
  return(o->ofn_efn);
}

private OFN *
EtoIOFN(i)
int i;
{
  i = i-1;
  if (i > MaxOFN || i < 0) {
    printf("EtoIOFN: bad file number\n");
    return(NULL);
  }
  if (!oinit || (OFNTBL[i].ofn_flgs & OF_INUSE) == 0)	/* ofn assigned? */
    return(NULL);		/* no, mark as bad */
  return(&OFNTBL[i]);
}

private void
relofn(ofn)
OFN *ofn;
{
  ofn->ofn_flgs = 0;
  ofn->ofn_trans_table = -1;	/* delete */
}

private OFN *
asnofn()
{
  int i;
  if (!oinit)
    iniofn();
  for (i=0; i < MaxOFN; i++)
    if ((OFNTBL[i].ofn_flgs & OF_INUSE) == 0) {
      OFNTBL[i].ofn_trans_table = -1; /* paranoia: no index */
      OFNTBL[i].ofn_flgs = OF_INUSE;
      return(&OFNTBL[i]);
    }
  return(0);
}

/*
 * OSErr FPGetForkParms(...)
 *
 * This call is used to retrieve parameters for a file associated with
 * a particular open fork.
 *
 * Inputs:
 *   refnum	Open fork refnum
 *   bitmap	Bitmap describing which parameters are to be retrieved.
 *		This field is the same as the FPGetFileDirParms call.
 *
 * Outputs:
 *   Same as FPGetFileDirParms.
 *
 * Errors:
 *   ParamErr, BitMapErr, AccessDenied.
 *
 * The fork must be open for read.
 *
 */

OSErr 
FPGetForkParms(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  GetForkParmsPkt gfp;
  FileDirParm fdp;
  int err;
  OFN *ofn;

  ntohPackX(PsGetForkParms,p,l,(byte *) &gfp);
  if ((ofn = EtoIOFN(gfp.gfp_refnum)) == NULL)
    return(aeParamErr);
  
  fdp.fdp_pdirid = ItoEdirid(ofn->ofn_ipdir,ofn->ofn_ivol);
  fdp.fdp_dbitmap = 0;
  fdp.fdp_fbitmap = gfp.gfp_bitmap;
  fdp.fdp_zero = 0;
  err = OSFileDirInfo(ofn->ofn_ipdir,NILDIR,ofn->ofn_fnam,&fdp,ofn->ofn_ivol);
  if (err != noErr)
    return(err);
  PackWord(gfp.gfp_bitmap,r);
  *rl = 2;
  *rl += htonPackX(FilePackR,(byte *) &fdp,r+(*rl));
  return(noErr);
}

/*
 * OSErr FPSetForkParms(...)
 *
 * Inputs:
 *
 *   refnum	Open fork refnum.
 *   bitmap	Bitmap describing which params are to be set.
 *
 * Output:
 *   Function Result.
 *
 * Errors:
 *   ParamErr, BitMapErr, DiskFull, LockErr, AccessDenied.
 *
 * The bitmap is the same as FPSetFileDirParms, however in AFP 1.1
 * only the fork length may be set.
 *
 * The fork must be opened for write.
 *
 */ 

/*ARGSUSED*/
OSErr 
FPSetForkParms(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  SetForkParmsPkt sfkp;
  OFN *ofn;
  sdword len;

  ntohPackX(PsSetForkParms,p,l,(byte *) &sfkp);
  if ((ofn = EtoIOFN(sfkp.sfkp_refnum)) == NULL)
    return(aeParamErr);
  
  if (DBFRK)
    printf("FPSetForkParms: ofn=%d\n",sfkp.sfkp_refnum);

  if ((sfkp.sfkp_bitmap & ~(FP_DFLEN|FP_RFLEN)) != 0 || sfkp.sfkp_bitmap==0) {
    printf("FPSetForkParms: bad bitmap %x\n",sfkp.sfkp_bitmap);
    return(aeBitMapErr);
  }

  len = (sfkp.sfkp_bitmap & FP_DFLEN) ? sfkp.sfkp_dflen  : sfkp.sfkp_rflen;
  /* can only set fork length for now */
  return((ofn->ofn_flgs&OF_NOTOPEN) ? noErr : OSSetForklen(ofn->ofn_fd, len));
}


OSErr 
FPOpenFork(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  OpenForkPkt ofk;
  OpenForkReplyPkt ofr;
  FileDirParm fdp;
  int ivol,err,err1,flg,fhdl,len, ttidx;
  IDirP idir,ipdir;
  char file[MAXUFLEN];
  byte finderinfo[FINFOLEN];
  OFN *ofn;
  extern PackEntry ProtoOFkRP[];

  ntohPackX(PsOpenFork,p,l,(byte *) &ofk);

  err = EtoIfile(file,&idir,&ipdir,&ivol,ofk.ofk_dirid,
		 ofk.ofk_volid,ofk.ofk_ptype,ofk.ofk_path);
  if (err != noErr)
    return(err);

  if (DBFRK) 
    printf("OpenFork: rdflg=%d, mode=%d, path=%s file=%s\n",
	   ofk.ofk_rdflg,ofk.ofk_mode,pathstr(ipdir),file);

  flg = (ofk.ofk_rdflg == 0) ? F_DATA : F_RSRC;

  err = OSOpenFork(ipdir,file,ofk.ofk_mode,flg,&fhdl);
  if (err != noErr && !(flg == F_RSRC && err == aeObjectNotFound))
    return(err);
  
  /* now, if data fork exists and resource open failed, allow go ahead */
  if (err == aeObjectNotFound) {
#ifdef notdef
    /* why did I do this? */
    if (ofk.ofk_mode & OFK_MWR)	/* don't allow write access */
      return(aeAccessDenied);
#endif
    if (OSFileExists(ipdir, file, F_DATA) != noErr)
      return(aeObjectNotFound);
    else {
      if (DBFRK)
	printf("Allowing fake access to resource fork\n");
    }
  }

  ofn = asnofn();
  if (ofn == 0) {
    if (err == noErr)
      OSClose(fhdl);
    return(aeTooManyFilesOpen);
  }
  ofn->ofn_fd = fhdl;
  ofn->ofn_mode = ofk.ofk_mode;
  ofn->ofn_type = flg;
  ofn->ofn_ipdir = ipdir;
  ofn->ofn_ivol = ivol;

  if (err == aeObjectNotFound)
    ofn->ofn_flgs |= OF_NOTOPEN;

  if (flg == F_DATA) {
    /* Never translate resource fork */
    OSGetFNDR(ipdir, file, finderinfo); /* check file type */
    if ((ttidx = ncs_istrans(finderinfo, file)) >= 0) {
      ofn->ofn_trans_table = ttidx;
      if (DBFRK)
	printf("Open fork: translation table: %s\n", ncs_tt_name(ttidx));
    }
  }

  strcpy(ofn->ofn_fnam,file);

  fdp.fdp_fbitmap = ofk.ofk_bitmap;
  fdp.fdp_dbitmap = 0;
  if ((err1 = OSFileDirInfo(ipdir,NILDIR,file,&fdp,ivol)) != noErr) {
    if (err != noErr)
      OSClose(fhdl);
    relofn(ofn);
    return(err1);
  }
  ofr.ofkr_bitmap = ofk.ofk_bitmap;
  ofr.ofkr_refnum = ItoEOFN(ofn);
  len = htonPackX(ProtoOFkRP, &ofr, r);	/* pack away */
  *rl = len + htonPackX(FilePackR,(byte *) &fdp,r+len);
  return(noErr);
}

/*ARGSUSED*/
OSErr 
FPCloseFork(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  CloseForkPkt cfk;
  OFN *ofn;
  int err;

  ntohPackX(PsCloseFork,p,l,(byte *) &cfk);
  if (DBFRK)
    printf("CloseFork: refnum=%d\n",cfk.cfk_refnum);
  if ((ofn = EtoIOFN(cfk.cfk_refnum)) == NULL)
    return(aeParamErr);

  if ((ofn->ofn_mode & OFK_MWR) != 0)	/* if opened for write */
    VolModified(ofn->ofn_ivol);		/*  then set volume modification dt */
  
  err = (ofn->ofn_flgs & OF_NOTOPEN) ? noErr : OSClose(ofn->ofn_fd);
  relofn(ofn);
  return(err);
}


/*
 * 
 * FPRead(...)
 *
 * The fork is read starting offset bytes from the beginning of the fork
 * and terminating at the first newline-char encountered.
 *
 */
 
OSErr 
FPRead(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  ReadPkt rp;
  OFN *ofn;
  extern int sqs;		/* get max send quantum size */

  ntohPackX(PsRead,p,l,(byte *) &rp);
  if (DBFRK)
    printf("Read: ofn=%d, offset=%d, reqcnt=%d, flg=%d, nlc=%c\n",
	   rp.rdf_refnum,rp.rdf_offset,rp.rdf_reqcnt,
	   rp.rdf_flag,rp.rdf_nlchar);

  if ((ofn = EtoIOFN(rp.rdf_refnum)) == NULL)
    return(aeParamErr);

  if (ofn->ofn_flgs & OF_NOTOPEN) {
    *rl = 0;
    return(aeEOFErr);
  }

  return(OSRead(ofn->ofn_fd,rp.rdf_offset,
		min(rp.rdf_reqcnt,sqs),
		rp.rdf_flag,rp.rdf_nlchar,r,rl,&ofn->ofn_pos,
		ofn->ofn_trans_table));
}

OSErr 
FPWrite(p,l,r,rl,cno,reqref)
byte *p,*r;
int l,*rl;
int cno;
ReqRefNumType reqref;
{
  WritePkt wrt;
  int rcvlen;
  int comp,err;
  OFN *ofn;
  extern int n_rrpkts;

  ntohPackX(PsWrite,p,l,(byte *) &wrt);
  if ((ofn = EtoIOFN(wrt.wrt_refnum)) == NULL)
    return(aeParamErr);
  if (DBFRK)
    printf("FPWrite: ofn=%d, flg=%d, offs=%d, req=%d\n",
	   wrt.wrt_refnum,wrt.wrt_flag,wrt.wrt_offset,wrt.wrt_reqcnt);
  if (ofn->ofn_flgs & OF_NOTOPEN) {
    if (wrt.wrt_reqcnt != 0)	/* allow zero length requests */
      return(aeAccessDenied);
  }

  err = SPWrtContinue(cno,reqref,r,n_rrpkts*atpMaxData,&rcvlen,-1,&comp);
  if (err != noErr)
    return(err);
  do { abSleep(4,TRUE); } while (comp > 0);    
  if (comp < 0)
    return(comp);
  err = OSWrite(ofn->ofn_fd,r,(sdword) rcvlen,
		wrt.wrt_offset,wrt.wrt_flag,&ofn->ofn_pos,
		ofn->ofn_trans_table);
  if (err != noErr)		
    return(err);
  PackDWord(ofn->ofn_pos,r);
  *rl = sizeof(ofn->ofn_pos);
  return(noErr);
} 

/*ARGSUSED*/
OSErr 
FPFlushFork(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  OFN *ofn;
  FlushForkPkt flf;

  ntohPackX(PsFlush, p, l, (byte *)&flf);
  if ((ofn = EtoIOFN(flf.flf_refnum)) == NULL)
    return(aeParamErr);
  if (DBFRK)
    printf("FLFlush: ofn=%d\n", flf.flf_refnum);
  return((ofn->ofn_flgs & OF_NOTOPEN) ? noErr : OSFlushFork(ofn->ofn_fd));
}

/*ARGSUSED*/
OSErr 
FPByteRangeLock(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  OFN *ofn;
  ByteRangeLockPkt brl;
  OSErr err;

  ntohPackX(PsByteRangeLock, p, l, (byte *)&brl);
  if ((ofn = EtoIOFN(brl.brl_refnum)) == NULL)
    return(aeParamErr);
  if (DBFRK)
    printf("Byte Range Lock: ofn=%d (file %s)\n",ofn->ofn_fd,ofn->ofn_fnam);
  if (ofn->ofn_flgs & OF_NOTOPEN)
    ofn->ofn_pos = brl.brl_offset;
  else {
    err = OSByteRangeLock(ofn->ofn_fd, brl.brl_offset, brl.brl_length,
			  brl.brl_flg, &ofn->ofn_pos);
    if (err != noErr)
      return(err);
  }
  PackDWord(ofn->ofn_pos,r);
  *rl = sizeof(ofn->ofn_pos);
  return(noErr);
}

