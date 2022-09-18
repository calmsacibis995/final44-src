/*
 *  Author: cck    Date: 88/02/23 17:16:09  
 *  Header: afpfile.c,v 1.13 88/02/23 17:16:09 cck Rel  
 *  Revision: 1.13  
*/

/*
 * afpfile.c - Appletalk Filing Protocol File Level Routines
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
 *  FPSetFileParms()
 *  FPCreateFile()
 *  FPCopyFile()
 *  FPRename()
 *  FPDelete() 
 *  FPMove()
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
#include "afps.h"

/*
 * OSErr FPSetFileParms(...)
 *
 */

/*ARGSUSED*/
OSErr
FPSetFileParms(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  SetFileParmsPkt sfp;
  FileDirParm fdp;
  IDirP idir,ipdir;
  char file[MAXUFLEN];
  int ivol,len,err;

  len = ntohPackX(PsSetFileParms,p,l,(byte *) &sfp);
  ntohPackXbitmap(ProtoFileAttr,p+len,l-len,(byte *) &fdp,sfp.sfp_bitmap);

  err = EtoIfile(file,&idir,&ipdir,&ivol,sfp.sfp_dirid,
		 sfp.sfp_volid,sfp.sfp_ptype,sfp.sfp_path);
  if (err != noErr)
    return(err);

  fdp.fdp_fbitmap = sfp.sfp_bitmap; 	/* set file bitmap */

  if (DBFIL) 
    printf("FPSetFileParms: setting bm=%d for %s %s\n",
	   fdp.fdp_fbitmap,pathstr(ipdir),file);

  return(OSSetFileParms(ipdir,file,&fdp));
}

/*
 * OSErr FPCreateFile(byte *p,byte *r,int *rl)
 *
 * This call is used to create a file.
 *
 */


/*ARGSUSED*/
OSErr 
FPCreateFile(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  CreateFilePkt crf;
  int ivol,delf,err;
  IDirP idir,ipdir;
  char file[MAXUFLEN];

  ntohPackX(PsCreateFile,p,l,(byte *) &crf);
  err = EtoIfile(file,&idir,&ipdir,&ivol,crf.crf_dirid,
		 crf.crf_volid,crf.crf_ptype,crf.crf_path);
  if (err != noErr)
    return(err);

  delf = (crf.crf_flg & CRF_HARD) != 0;

  if (DBFIL) 
    printf("FPCreateFile flg=%s, path=%s, fn=%s\n",
	   crf.crf_flg,pathstr(ipdir),file);

  err = OSCreateFile(ipdir,file,delf);
  if (err == noErr)			/* if success */
    VolModified(ivol);			/*  then volume modified */
  return(err);
}

  
/*
 * FPCopyFile(byte *p,byte *r,int *rl) [NOP]
 * 
 * Optional, may not be supported on all servers.
 *
 *
 */

/*ARGSUSED*/
OSErr 
FPCopyFile(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  CopyFilePkt cpf;
  char sfile[MAXUFLEN],dfile[MAXUFLEN],newname[MAXUFLEN];
  char *dfilep;
  IDirP sidir,sipdir,didir,dipdir;
  int sivol,divol;
  int err;

  ntohPackX(PsCopyFile,p,l,(byte *) &cpf);
  err = EtoIfile(sfile,&sidir,&sipdir,&sivol,cpf.cpf_sdirid,
		 cpf.cpf_svolid,cpf.cpf_sptype,cpf.cpf_spath);
  if (err != noErr)
    return(err);
  err = EtoIfile(dfile,&didir,&dipdir,&divol,cpf.cpf_ddirid,
		 cpf.cpf_dvolid,cpf.cpf_dptype,cpf.cpf_dpath);
  if (err != noErr)
    return(err);

  if (didir == NILDIR)			/* destination directory */
    return(aeParamErr);			/* must be around */

  if ((err = EtoIName(cpf.cpf_newname,newname)) != noErr)
    return(err);

  if (*newname != '\0')			/* if new name was specified */
    dfilep = newname;			/*  then use that */
  else					/* otherwise if no new name */
   dfilep = sfile;			/*  then use the source file name */

  if (DBFIL) {
    printf("FPCopyFile: srcvol=%d, srcdir=%s srcfil=%s\n",
	   sivol,pathstr(sipdir),sfile);
    printf("FPCopyFile: dstvol=%d, dstdir=%s, dstname=%s\n",
	   divol,pathstr(didir),dfilep);
  }
  
  err = OSCopyFile(sipdir,sfile,didir,dfilep);
  if (err == noErr)			/* if success */
    VolModified(divol);			/*  then dest volume modified */
  return(err);
}

/*
 * FPRename(byte *p,byte *r,int *rl)
 *
 * This call is used to rename either a file or directory.
 *
 */

/*ARGSUSED*/
OSErr 
FPRename(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  RenamePkt ren;
  IDirP idir,ipdir,nidir,nipdir;
  int ivol,err;
  char file[MAXUFLEN],nfile[MAXUFLEN];
 
  ntohPackX(PsRename,p,l,(byte *) &ren);
  
  err = EtoIfile(file,&idir,&ipdir,&ivol,ren.ren_dirid,
		 ren.ren_volid,ren.ren_ptype,ren.ren_path);
  if (err != noErr) 
    return(err);

  err = EtoIfile(nfile,&nidir,&nipdir,&ivol,ren.ren_dirid,
		 ren.ren_volid,ren.ren_ntype,ren.ren_npath);
  if (err != noErr)
    return(err);

  if (DBFIL) {    
    printf("FPRename path=%s, name=%s,",pathstr(ipdir),file);
    printf("to path=%s, name=%s\n",pathstr(nipdir),nfile);
  }

  if (ipdir != nipdir) {
    printf("FPRename: different parent directory\n");
    return(aeParamErr);
  }

  return(OSRename(ipdir,file,nfile));
}

  
/*
 * FPDelete(byte *p,byte *r,int *rl)
 *
 * This call is used to delete either a file or directory.
 *
 */

/*ARGSUSED*/
OSErr 
FPDelete(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  DeletePkt del;
  IDirP idir,ipdir;
  int ivol,err;
  char file[MAXUFLEN];

  ntohPackX(PsDelete,p,l,(byte *) &del);
  err = EtoIfile(file,&idir,&ipdir,&ivol,del.del_dirid,
		 del.del_volid,del.del_ptype,del.del_path);
  if (err != noErr)
    return(err);
  
  if (DBFIL)
    printf("FPDelete: path=%s file=%s\n",pathstr(ipdir),file);
  err = OSDelete(ipdir,idir,file);
  if (err == noErr)			/* if success */
    VolModified(ivol);			/*  then volume modified */
  return(err);
}

/*
 * FPMove(...)
 *
 * This call is used to move (not just copy) a directory or file
 * to another location on a single volume (source and destination
 * must be on the same volume).  An object cannot be moved from one
 * volume to another with this call, even though both volumes may be
 * managed by the server.  The destination of the move is specified
 * by providing a DirID and Pathname that indicates the object's new
 * Parent Directory.
 *
 */

/*ARGSUSED*/
OSErr
FPMove(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  MovePkt mov;
  IDirP idir,ipdir,nidir,nipdir;
  int ivol,err;
  char file[MAXUFLEN],nfile[MAXUFLEN];
  char *nf;
 
  ntohPackX(PsMove,p,l,(byte *) &mov);
  
  err = EtoIfile(file,&idir,&ipdir,&ivol,mov.mov_sdirid,
		 mov.mov_volid,mov.mov_sptype,mov.mov_spath);
  if (err != noErr)
    return(err);

  err = EtoIfile(nfile,&nidir,&nipdir,&ivol,mov.mov_ddirid,
		 mov.mov_volid,mov.mov_dptype,mov.mov_dpath);
  if (err != noErr)
    return(err);

  /* nidir, nfile must be a directory! */
  if (nidir == NILDIR)
    return(aeParamErr);
  /* where should this be done if not here? */
  if (mov.mov_newtype != 0x2)
    return(aeParamErr);
  if (mov.mov_newname[0] != '\0') {
    EtoIName(mov.mov_newname, nfile);
    nf = nfile;
  } else nf = file;

  if (DBFIL) {    
    printf("FPMove path=%s, name=%s,",pathstr(ipdir),file);
    printf("to path=%s, name=%s\n",pathstr(nidir),nf);
  }

  err = OSMove(ipdir,file,nidir,nf);
  if (err == noErr)			/* if success */
    VolModified(ivol);			/*  then volume modified */
  return(err);
}

