/*
 *  Author: cck    Date: 88/05/13 09:22:55  
 *  Header: afpvols.c,v 1.22 88/05/13 09:22:55 cck Rel  
 *  Revision: 1.22  
*/

/*
 * afpvols.c - Appletalk Filing Protocol Volume Routines
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986,1987,1988 by The Trustees of Columbia University in the
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
 *  FPGetVolParms()
 *  FPSetVolParms()
 *  FPOpenVol()
 *  FPCloseVol()
 *  FPFlush()
 *
 */

#include <stdio.h>
#include <sys/param.h>
#ifndef _TYPES
# include <sys/types.h>		/* assume included by param.h */
#endif
#include <netat/appletalk.h>
#include <netat/afp.h>
#include <netat/afpcmd.h>
#include "afps.h"
#include "afpntoh.h"
#include "afpvols.h"
#ifdef USESTRINGDOTH
# include <string.h>
#else
# include <strings.h>
#endif


private VolPtr VolTbl[MAXVOLS];		/* table of VolEntry records */
private int VolCnt = 0;			/* number of volumes */
private VolBitMap VolModBitMap = 0;	/* bitmap of modified volumes */

private PackEntry VolPackR[] = { 	/* Volume Parms Reply */
  PACK(VolPtr,P_WORD,v_bitmap),		/* bitmap specifies below items */
  PACK(VolPtr,P_BMAP,v_bitmap),		/* bitmap specifies below items */
  PAKB(VolPtr,P_WORD,v_attr,VP_ATTR),	/* attributes word */
  PAKB(VolPtr,P_WORD,v_sig,VP_SIG),	/* signature word */
  PAKB(VolPtr,P_TIME,v_cdate,VP_CDATE),	/* creation date */
  PAKB(VolPtr,P_TIME,v_mdate,VP_MDATE),	/* modification date */
  PAKB(VolPtr,P_TIME,v_bdate,VP_BDATE),	/* last back date */
  PAKB(VolPtr,P_WORD,v_volid,VP_VOLID),	/* volume id */
  PAKB(VolPtr,P_DWRD,v_free,VP_FREE),	/* free bytes */
  PAKB(VolPtr,P_DWRD,v_size,VP_SIZE),	/* size in bytes */
  PKSB(VolPtr,P_OSTR,v_name,VP_NAME),	/* name of volume */
  PACKEND()
};

/*
 * void VNew(char *path, char *name, char *pwd)
 *
 * Given a path, volume name, and password string, create a new volume
 * in VolTbl.
 *
 */

void
VNew(path,name,pwd)
char *name;
char *path;
char *pwd;
{
  VolPtr vp;
  char *malloc();

  if ((strlen(name) > MAXVLEN) ||
      (strlen(path) > MAXDLEN) ||
      (strlen(pwd)  > MAXPLEN)) {
	log("VNew: path, name or password too long on path = %s\n",path);
	return;
      }
    
  if (DBVOL)
    printf("Adding vol '%s' on path '%s' pwd='%s'\n",name,path,pwd);

  /* create volume record */
  vp = (VolPtr) malloc(sizeof(VolEntry));
  strcpy(vp->v_name,name);		/* copy the name */
  strcpy(vp->v_path,path);		/*  the path */
  strcpy(vp->v_pwd,pwd);		/*  and the password */
  vp->v_mounted = FALSE;		/* not opened */
  vp->v_volid = VolCnt+1;		/* will be volcnt+1 */
  vp->v_sig = VOL_FIXED_DIRID;		/* signature word */
  vp->v_attr = 0;			/* clear attributes */

  /* Now make sure entry is valid */
  if (OSVolInfo(path,vp,VP_ALL) != noErr) {	/* get volume info */
    free((char *) vp);			/* bad... release storage */
    printf("VNew: No volinfo for %s on path %s\n",name,path);
    return;
  }

  /* This is deferred because I'm not sure how to deallocate :-) */
  /* and isn't needed until we have validated the entry anyway */
  vp->v_rootd = Idirid(path);		/* create directory handle */
  InitDIDVol(vp->v_rootd, VolCnt);	/* initialize volume info for list */
  
  /* Okay, stick it into the table */
  VolTbl[VolCnt++] = vp;		/* set volume record */
}

private char *
spanspace(p)
char *p;
{
  while (*p == ' ' || *p == '\t' || *p == '\n')
    p++;
  return(p);
}

/*
 * char *vskip(char *p)
 *
 * vskip skips to the next field in a line containing volume information
 * as read from the VOLFILE.  The field seperator ":" or the end of line
 * character is set to NULL in order to terminate the field.
 *
 */

private char *
vskip(p)
char *p;
{
  while (*p != '\0' && *p != ':' && *p != '\n')
    p++;
  if (*p != '\0')		/* at end of string? */
    *p++ = '\0';		/* no tie off this field */
  return(p);			/* and return pointer */
}

/*
 * VRdVFile(FILE *fd)
 *
 * Reads a file containing volume information from the specified path.
 * The file descriptor is closed after reading the file
 *
 * VRdVFile is intended to read VOLFILE from the user's home directory
 * after FPLogin.  The information in this file is stored in the VolTbl.
 *
 * Format of VOLFILE:
 *  path:volume name[:optional password][:]
 *
 *  blank lines and lines starting with '#' are ignored.
 *
 */

VRdVFile(fd)
FILE *fd;
{
  char line[MAXLLEN+1];
  char *pathp,*namep,*pswdp,*p,*tilde();
  int origVolCnt;

  origVolCnt = VolCnt;
  while ((p = fgets(line,MAXLLEN,fd)) != NULL) { /* read lines */
    p = spanspace(p);			/* span spaces */
    if (*p == '#' || *p == '\0')	/* comment or blank line? */
      continue;				/* yes, skip it */
    pathp = p; p = vskip(p);		/* save ptr to start of path */
    namep = p; p = vskip(p);		/* start of name */
    pswdp = p; p = vskip(p);		/* save it */
    pathp = tilde(pathp);		/* expand the path */
    VNew(pathp,namep,pswdp);		/* add new entry */
  }
  fclose(fd);				/* close file */
  return(VolCnt != origVolCnt);	        /* return true if found any entries */
}

/*
 * void VInit(char *usr,char *home)
 *
 * VInit adds entries to the table of volumes by reading the user's
 * VOLFILE or VOLFILE1.  If no VOLFILE exists on the path specified by
 * "home" then a default entry entry of path=home and name=usr is
 * setup.
 *
 */

void
VInit(usr,home)
char *usr;
char *home;
{
  char vfn[MAXDLEN+20];			/* afpvols file name */
  FILE *fd;

  if (home == NULL)			/* no home, then nothing to do */
    return;

  strcpy(vfn,home);			/* copy directory */
  strcat(vfn,"/");			/*  terminator */
  strcat(vfn,VOLFILE);			/*  and then the volsfile name */

  if ((fd = fopen(vfn, "r")) == NULL) {
    strcpy(vfn,home);		/* copy directory */
    strcat(vfn,"/");		/*  terminator */
    strcat(vfn,VOLFILE1);	/*  and then the volsfile name */
    if ((fd = fopen(vfn, "r")) == NULL) {
      if (DBVOL)
	printf("VRdVFile: no afpvols or .afpvols in %s\n",home);
      VNew(home,usr,"");	/* if none, then setup home dir */
      return;
    }
  }
  (void)VRdVFile(fd);		/* read vols file from user */
  if (VolCnt == 0)
    VNew(home, usr, "");
}

/*
 * return count of volumes
 *
*/
int
VCount()
{
  return(VolCnt);
}

/*
 * int VMakeVList(VolParm *vp,byte *vpl)
 *
 * Store into vp a number of VolParm entries, one for each volume
 * we know about.  Return in vpl the length of the information.
 * Return the count of volumes.
 * 
 * Used by GetSrvrParms.
 *
 */

int
VMakeVList(r)
byte *r;			/* ptr to place to store */
{
  VolParm vpp;
  int v, len;
  extern PackEntry ProtoGSPRPvol[];

  for (v=0,len=0; v < VolCnt; v++) {
    if (*VolTbl[v]->v_pwd != '\0')
      vpp.volp_flag = SRVRP_PASSWD;	/* is password protected */
    else
      vpp.volp_flag = 0;		/* no flags */
    cpyc2pstr(vpp.volp_name,VolTbl[v]->v_name);
    len += htonPackX(ProtoGSPRPvol, &vpp, r+len);
  }
  return(len);			/* return size used */
}

/*
 * OSErr FPGetVolParms(byte *p,int l,byte *r,int *rl);
 *
 * This call is used to retrieve paramters for a particular volume.
 * The volume is specified by its Volume ID as returned from the
 * FPOpenVol call.
 *
 *
 */

OSErr 
FPGetVolParms(p,l,r,rl)
byte *p,*r;
int *rl,l;
{
  GetVolParmsPkt gvp;			/* cast to packet type */
  int ivol,err;
  VolPtr vp;

  ntohPackX(PsGetVolParms,p,l,(byte *) &gvp); /* decode packet */
  ivol = EtoIVolid(gvp.gvp_volid); 	/* pick up volume id */
  if (ivol < 0)
    return(ivol);			/* unknown volume */
  if (!VolTbl[ivol]->v_mounted)		/* must have called FPOpenVol first */
    return(aeParamErr);			/* not opened */
  vp = VolTbl[ivol];			/* ptr to volume */
  err = OSVolInfo(pathstr(vp->v_rootd),vp,gvp.gvp_bitmap); /* get vol info */

  if (V_BITTST(VolModBitMap,ivol)) {	/* modified since last call? */
    V_BITCLR(VolModBitMap,ivol);	/* yes... clear the flag */
    vp->v_mdate = CurTime();		/* set modify time */
  }

  if (err != noErr)
    return(err);
  vp->v_bitmap = gvp.gvp_bitmap;
  *rl = htonPackX(VolPackR,(byte *) vp,r);
  return(noErr);			/* all ok */
}

/*
 * OSErr FPSetVolParms(byte *p,byte *r,int *rl) [NOOP]
 *
 * This call is used to set the parameters for a particular volume.  The
 * volume is specified by its VolumeID as returned from the FPOpenVol
 * call.
 *
 * In AFP Version 1.0 only the Backup Date field may be set.  Under
 * Unix this is a noop.
 *
 */

/*ARGSUSED*/  
OSErr
FPSetVolParms(p,l,r,rl)
byte *p,*r;
int *rl;
{
  SetVolParmsPkt svp;
  int ivol;

  ntohPackX(PsSetVolParms,p,l,(byte *) &svp); /* unpack */

  ivol = EtoIVolid(svp.svp_volid);
  if (ivol < 0)
    return(aeParamErr);			/* unknown volume */

  if ((svp.svp_bitmap & ~VP_BDATE) != 0)
    return(aeBitMapErr);		/* trying to set unknown parms */

  if (svp.svp_bitmap & VP_BDATE)	/* want to set backup date? */
    VolTbl[ivol]->v_bdate = svp.svp_backdata; /* yes... */

  return(noErr);			/* return ok... */
}

/*
 * OSErr FPOpenVol(byte *p, byte *r, int *rl)
 *
 * This call is used to "mount" a volume.  It must be called before any
 * other call can be made to access objects on the volume.
 *
 */

OSErr 
FPOpenVol(p,l,r,rl)
byte *p;
int l;
byte *r;
int *rl;
{
  OpenVolPkt ovl;
  char pwd[MAXPASSWD+1];		/* null terminated password */
  int v;
  OSErr err;
  VolPtr vp;
  
  ovl.ovl_pass[0] = '\0';		/* zero optional password */
  ntohPackX(PsOpenVol,p,l,(byte *) &ovl); /* decode packet */
  strncpy(pwd,(char *) ovl.ovl_pass,MAXPASSWD);	/* copy optional pwd */
  pwd[MAXPASSWD] = '\0';		/* tie off with a null */

  if (DBVOL)
    printf("FPOpenVol: name=%s, pwd=%s, bm=%d\n",
	   ovl.ovl_name,pwd,ovl.ovl_bitmap);
  
  for (v=0; v < VolCnt; v++)		/* locate the volume */
    if (strcmp(VolTbl[v]->v_name,(char *) ovl.ovl_name) == 0)
      break;

  if (v >= VolCnt)			/* did we find a vol in the scan? */
    return(aeParamErr);			/* no... unknown volume name */

  vp = VolTbl[v];			/* dereference */
  if (*vp->v_pwd != '\0') 	/* password exists on volume? */
    if (strcmp(vp->v_pwd,pwd) != 0) /* yes, check for match */
      return(aeAccessDenied);		/* not the same... return failure */

  if (DBVOL)
    printf("FPOpenVol: name=%s volid=%d\n", vp->v_name,vp->v_volid);

  vp->v_mounted = TRUE;		/* now it is opened... */
  
  /* update volume info */
  if ((err = OSVolInfo(vp->v_path,vp,VP_ALL)) != noErr)
    return(err);

  vp->v_bitmap = ovl.ovl_bitmap;	/* bitmap for packing result */

  *rl = htonPackX(VolPackR,(byte *) vp,r);
  return(noErr);			/* return ok */
}


/*
 * OSErr FPCloseVol(byte *p,byte *r,int *rl)
 *
 * This call is used to "unmount" a volume.
 *
 */

/*ARGSUSED*/
OSErr 
FPCloseVol(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  CloseVolPkt cv;
  int ivol;

  ntohPackX(PsCloseVol,p,l,(byte *) &cv);
  
  ivol = EtoIVolid(cv.cv_volid); /* convert to internal format */
  if (ivol < 0)			/* error code */
    return(ivol);

  if (DBVOL)
    printf("FPCloseVol %d=%s\n",ivol,VolTbl[ivol]->v_name);

  if (!VolTbl[ivol]->v_mounted)		/* was it mounted? */
    return(aeMiscErr);			/* no... not mounted */

  VolTbl[ivol]->v_mounted = FALSE;	/* indicate no longer mounted */
  return(noErr);			/* and return ok */
}


/*
 * OSErr FPFlush(byte *p,byte *r, int *rl)
 *
 * This call is used to flush to disk any data relating to the specified
 * volume that has been modified by the user.
 *
 */

/*ARGSUSED*/
OSErr
FPFlush(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  FlushPkt fls;
  int ivol;

  ntohPackX(PsFlush,p,l,(byte *) &fls);

  if (DBVOL)
    printf("FPFLush: ...\n");

  ivol = EtoIVolid(fls.fls_volid);
  if (ivol < 0)
    return(ivol);

  return(OSFlush(ivol));
}

/*
 * IDirP VolRootD(int volid)
 *
 * Return the internal directory pointer for this volumes root directory.
 * Root directory is the volumes mount point, or initial path.
 *
 */

IDirP
VolRootD(volid)
int volid;
{
  if (volid > VolCnt)
    return(NILDIR);
  return(VolTbl[volid]->v_rootd);
}

/*
 * void VolModified(VolBitMap volbm)
 *
 * Indicate that the volumes specified in volbm have been modified.
 *
 */

void
VolModified(volbm)
VolBitMap volbm;
{
  V_BITOR(VolModBitMap,			/* result */
	  VolModBitMap,volbm);		/* is OR of these two */
}


char *
VolName(volid)
{
  if (volid > VolCnt)
    return("");
  return(VolTbl[volid]->v_name);
}


word 
ItoEVolid(iv)
int iv;
{
  return(VolTbl[iv]->v_volid);		/* return volume id */
}

int
EtoIVolid(ev)
word ev;
{
  int iv;
  for (iv=0; iv < VolCnt; iv++)
    if (VolTbl[iv]->v_volid == ev)
      return(iv);
  if (DBVOL)
    printf("EtoIVolid: Bad Volid %d\n",ev);
  return(aeParamErr);
}
