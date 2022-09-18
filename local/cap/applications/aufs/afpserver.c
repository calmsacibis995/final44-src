/*
 *  Author: cck    Date: 88/05/13 09:23:25  
 *  Header: afpserver.c,v 1.27 88/05/13 09:23:25 cck Rel  
 *  Revision: 1.27  
*/

/*
 * afpserver.c - Appletalk Filing Protocol Server Level Routines
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
 * Various server support routines:
 *
 *  SrvrInfo()
 *  SrvrRegister()
 *  SrvrSetTrace()
 *
 * Non OS dependant support routines:
 *
 *  FPLogin()
 *  FPLoginCont()
 *  FPLogout()
 *  FPGetSrvrParms()
 *  FPMapID() 
 *  FPMapName()
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <sys/param.h>
#ifndef _TYPES
 /* assume included by param.h */
# include <sys/types.h>
#endif
#include <sys/time.h>
#include <sys/resource.h>
#include <netat/appletalk.h>
#include <netat/afp.h>
#include <netat/afpcmd.h>
#include "afpntoh.h"
#include "afps.h"
#ifdef USETIMES
# include <sys/times.h>
#endif

/* consistency */
#ifdef USETIMES
# define NORUSAGE
#endif

typedef struct {
  int   dsp_cmd;
  PFE   dsp_rtn;
  char *dsp_name;
  int	dsp_flg;
#define DSPF_DMPIN  01
#define DSPF_DMPOUT 02
#define DSPF_DOESSPWRITE 0x4	/* needs more args.. */
#define DSPF_DMPBOTH (DSPF_DMPIN | DSPF_DMPOUT)
  int   dsp_cnt;
#ifndef NORUSAGE
  struct timeval dsp_utime;
  struct timeval dsp_stime;
#endif
#ifdef USETIMES
  time_t dsp_utime;
  time_t dsp_stime;
#endif
} AFPDispEntry;

private char *afpmtyp = "Unix";

#define AFPVERSZ (4*16)			/* room for IndStr hold all versions */
/* define 1 more than needed just in case */
struct afpversionstruct {
  char *version_name;
  int version;
} afpversions[] = {
  {"AFPVersion 1.0", AFPVersion1DOT0},
  {"AFPVersion 1.1", AFPVersion1DOT1},
  {"AFPVersion 2.0", AFPVersion2DOT0},
  {NULL, AFPVersionUnknown}
};

#define MAX_USE_UAM 4			/* maximum number at one time */
#define NUAM "No User Authent"
#define CUAM "Cleartxt passwrd"
#define RUAM "Randnum exchange"
private int numuam = 0;
struct afpuamstruct {
  char *uamname;
  int uam;
};
private struct afpuamstruct afpuams[MAX_USE_UAM];

private byte uamflags[] = {
    0,					/* no flags for "No User Authent" */
    UAMP_USER|UAMP_PASS|UAMP_ZERO,	/* user and password for cleartext */
					/* zero means put a zero to even */
					/* out packet between user & passwd */
    UAMP_USER				/* user only in randnum */
					/* (not implemented) */
    };

#define AFPUAMSZ (MAX_USE_UAM*17+1)	/* room for IndStr */


private AFPDispEntry *DispTab[AFPMaxCmd+1];

private AFPDispEntry Entries[] = {
  {AFPByteRangeLock,FPByteRangeLock,"ByteRangeLock",0,0},
  {AFPChgPasswd, FPChgPasswd, "ChangePassword", 0, 0},
  {AFPCloseVol,FPCloseVol,"CloseVol",0,0},
  {AFPCloseDir,FPCloseDir,"CloseDir",0,0},
  {AFPCloseFork,FPCloseFork,"CloseFork",0,0},
  {AFPCopyFile,FPCopyFile,"CopyFile",0,0},
  {AFPCreateDir,FPCreateDir,"CreateDir",0,0},
  {AFPCreateFile,FPCreateFile,"CreateFile",0,0},
  {AFPDelete,FPDelete,"Delete",0,0},
  {AFPEnumerate,FPEnumerate,"Enumerate",0,0},
  {AFPFlush,FPFlush,"Flush",0,0},
  {AFPFlushFork,FPFlushFork,"FlushFork",0,0},
  {AFPGetForkParms,FPGetForkParms,"GetForkParms",0,0},
  {AFPGetSrvrParms,FPGetSrvrParms,"GetSrvrParms",0,0},
  {AFPGetVolParms,FPGetVolParms,"GetVolParms",0,0},
  {AFPLogin,FPLogin,"Login",0,0},
  {AFPLoginCont,FPLoginCont,"LoginCont",0,0},
  {AFPLogout,FPLogout,"Logout",0,0},
  {AFPMapID,FPMapID,"MapID",0,0},
  {AFPMapName,FPMapName,"MapName",0,0},
  {AFPMove,FPMove,"Move",0,0},
  {AFPOpenVol,FPOpenVol,"OpenVol",0,0},
  {AFPOpenDir,FPOpenDir,"OpenDir",0,0},
  {AFPOpenFork,FPOpenFork,"OpenFork",0,0},
  {AFPRead,FPRead,"Read",0,0},
  {AFPRename,FPRename,"Rename",0,0},
  {AFPSetDirParms,FPSetDirParms,"SetDirParms",0,0},
  {AFPSetFileParms,FPSetFileParms,"SetFileParms",0,0},
  {AFPSetForkParms,FPSetForkParms,"SetForkParms",0,0},
  {AFPSetVolParms,FPSetVolParms,"SetVolParms",0,0},
  {AFPWrite,FPWrite,"Write",DSPF_DOESSPWRITE,0},
  {AFPGetFileDirParms,FPGetFileDirParms,"GetFileDirParms",0,0},
  {AFPSetFileDirParms,FPSetFileDirParms,"SetFileDirParms",0,0},
  {AFPOpenDT,FPOpenDT,"OpenDT",0,0},
  {AFPCloseDT,FPCloseDT,"CloseDT",0,0},
  {AFPGetIcon,FPGetIcon,"GetIcon",0,0},
  {AFPGetIconInfo,FPGetIconInfo,"GetIconInfo",0,0},
  {AFPAddAPPL,FPAddAPPL,"AddAPPL",0,0},
  {AFPRmvAPPL,FPRmvAPPL,"RmvAPPL",0,0},
  {AFPGetAPPL,FPGetAPPL,"GetAPPL",0,0},
  {AFPAddComment,FPAddComment,"AddComment",0,0},
  {AFPRmvComment,FPRmvComment,"RmvComment",0,0},
  {AFPGetComment,FPGetComment,"GetComment",0,0},
  {AFPAddIcon,FPAddIcon,"AddIcon",DSPF_DOESSPWRITE,0}
};

#define NumEntries (sizeof(Entries)/sizeof(AFPDispEntry))

IniServer()			/* ini disp entries */
{
  int i;

  for (i=0; i < AFPMaxCmd; i++)		/* clear all pointers */
    DispTab[i] = (AFPDispEntry *) 0;	/* in dispatch table */
    
  for (i=0; i < NumEntries; i++) {	/* for each entry add into dispatch */
    DispTab[Entries[i].dsp_cmd] = &Entries[i];
#ifndef NORUSAGE
    Entries[i].dsp_utime.tv_sec = 0;
    Entries[i].dsp_utime.tv_usec = 0;
    Entries[i].dsp_stime.tv_sec = 0;
    Entries[i].dsp_stime.tv_usec = 0;
#endif
#ifdef USETIMES
    Entries[i].dsp_utime = 0;
    Entries[i].dsp_stime = 0;    
#endif
  }

  InitOSFI();			/* init finder file info */
  ECacheInit();			/* init afposenum cache */
  InitIconCache();		/* init afpdt cache */
  InitDID();			/* init directory stuff  */
}

private int loggedin = FALSE;

OSErr
SrvrDispatch(pkt,len,rsp,rlen,cno,reqref)
byte *pkt,*rsp;
int len,*rlen;
int cno;
ReqRefNumType reqref;
{
  AFPDispEntry *d; 
  int err;
  byte *p;
  byte cmd;
  

  *rlen = 0;
  cmd = *pkt;
  if ((d = DispTab[cmd]) == (AFPDispEntry *) 0) {
    printf("SrvrDispatch: Unknown cmd=%d (%x)\n",cmd,cmd);
    DumpBuf(pkt,len,"Unknown Cmd",cmd);
    return(aeCallNotSupported);    
  }

  if (DBSRV)
    printf("SrvrDispatch cmd=%s (%d 0x%x), len=%d\n",
	   d->dsp_name,cmd,cmd,len);


  d->dsp_cnt++;			/* increment counter */

  if (d->dsp_flg & DSPF_DMPIN)
   DumpBuf(pkt,len,d->dsp_name,cmd);

  if (statflg)
    clockstart();

  if (!loggedin && d->dsp_cmd != AFPLogin && d->dsp_cmd != AFPLoginCont) {
    log("SrvrDispath: Security. Cmd before login %s\n",d->dsp_name);
    err = aeMiscErr;
  } else {
    if (d->dsp_flg & DSPF_DOESSPWRITE) 
      err = (*d->dsp_rtn)(pkt,len,rsp,rlen,cno,reqref);
    else
      err = (*d->dsp_rtn)(pkt,len,rsp,rlen);
  }

  if (statflg) 
    clockend(d);

  if (d->dsp_flg & DSPF_DMPOUT)
    DumpBuf(rsp,*rlen,d->dsp_name,cmd);
  return(err);
}

#define PERLINE 20

/*
 * If you can understand this, then you are far better person than I...
 * This code is convoluted unecessarily, but it really isn't important
 * code, so...
 *
*/
private 
DumpBuf(p,l,s,c)
byte *p;
int l;
char *s;
byte c;
{
  int ln,ll,left;
  int lll;

  printf("DmpBuf for %s (%d 0x%x) length = %d\n",s,c,c,l);
  if (l > 1000)
    lll = 1000;
  else
    lll = l;

  for (ll = 0; ll < lll; ll += PERLINE) {
    
    printf(" %06d ",ll);
    left = (lll-ll < PERLINE ? lll-ll : PERLINE);
    for (ln=0; ln < left; ln++)
      printf("%02x ",(unsigned int) p[ln]);

    printf("\n        ");
    for (ln=0; ln < left; ln++)
      if ((p[ln] < 0200) && isprint(p[ln]))
	printf("%2c ",p[ln]);
      else
	printf(" . ");
    printf("\n");
    p += PERLINE;
  }
  if (lll < l)
    printf(" ... too large to print ... ");
}

 
/*ARGSUSED*/
OSErr
FPMapName(p,l,r,rl)
byte *p,*r;
int *rl,l;
{
  char name[MAXPSTR];
  OSErr err;
  sdword id;
  MNPPtr mnp = (MNPPtr) p;

  cpyp2cstr(name,mnp->mpn_name);	/* copy into c string */
  err = OSMapName(mnp->mpn_fcn,name,&id);
  if (err != noErr)
    return(err);
  PackDWord(id,r);		/* pack long format */
  *rl = 4;			/* length of reply */
  return(noErr);
}


OSErr
FPMapID(p,l,r,rl)
byte *p,*r;			/* packet and response */
int *rl,l;			/* response length */
{
  char name[MAXPSTR];
  OSErr err;
  MapIDPkt mip;

  ntohPackX(PsMapID,p,l,(byte *) &mip);
  err = OSMapID(mip.mpi_fcn,name,mip.mpi_id);
  if (err != noErr)
    return(err);
  cpyc2pstr(r,name);		/* copy to pascal string for return */
  *rl = strlen(name)+1;		/* return length of reply packet */
  return(noErr);
}


/*
 * Begin login code
 *
 * Login methods assume we are "forked" from main server!!!
 *
*/

/*
 * map a uam string to internal uam number
 *
*/
private int
mapuamstr(uamstr)
char *uamstr;
{
  int i;

  if (uamstr == NULL)
    return(UAM_UNKNOWN);
  for (i = 0; i < numuam; i++) 
    /* do it case insenstive */
    if (strcmpci(uamstr, afpuams[i].uamname) == 0) 
      return(afpuams[i].uam);
  return(UAM_UNKNOWN);
}

private int
mapverstr(verstr)
char *verstr;
{
  struct afpversionstruct *av;

  for (av = afpversions; av->version_name != NULL ; av++) 
    if (strcmpci(verstr, av->version_name) == 0)
      return(av->version);
  return(AFPVersionUnknown);
}

export void
allowguestid(gn)
char *gn;
{
  if (!setguestid(gn))
    return;
  afpuams[numuam].uamname = NUAM;
  afpuams[numuam].uam = UAM_ANON;
  numuam++;
}

export void
allowcleartext()
{
  afpuams[numuam].uamname = CUAM;
  afpuams[numuam].uam = UAM_CLEAR;
  numuam++;
}

export void
allowrandnum(pw)
char *pw;
{
  if (!setpasswdfile(pw))
    return;
  afpuams[numuam].uamname = RUAM;
  afpuams[numuam].uam = UAM_RANDNUM;
  numuam++;
}

/* follow vars are used for randnum exchange */
private LoginReplyPkt rne = {	/* initialize to minimize */
  0x0,				/* possiblity of bad transaction */
  0xffff,			/* when starting */
  {0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8}
};
private char username[50];	/* some reasonable length */

/*ARGSUSED*/
OSErr
FPLogin(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  LoginPkt lg;
  char upwd[MAXPASSWD+1];
  int uam, i, vers;
  OSErr err;

  if (loggedin)			/* already logged in */
    return(aeMiscErr);

  (void) ntohPackX(PsLogin,p,l,(byte *) &lg);

  /* locate user authentication method and unpack accordingly */

  if ((vers = mapverstr(lg.log_ver)) == AFPVersionUnknown) {
    log("Bad version %s", lg.log_ver);
    return(aeBadVersNum);
  }
  /* mactime <-> unix time is different for afp 1.1 */
  /* this calldown is to afpcmd */
  InitPackTime(vers == AFPVersion1DOT0);

  if ((uam = mapuamstr(lg.log_uam)) == UAM_UNKNOWN) {	/* map the uam */
    log("BAD UAM %s in connection attempt", lg.log_uam);
    return(aeBadUAM);			/* no... forget it */
  }

  (void) ntohPackXbitmap(PsLogin,p,l,(byte *) &lg, uamflags[uam]);
  if (uam == UAM_RANDNUM) {
    if ((err = OSLoginRand(lg.log_user)) != noErr)
      return(err);
    for (i = 0; i < 8; i++)
      rne.logr_randnum[i] = (byte)OSRandom();
    strcpy(username, lg.log_user); /* remember it */
    rne.logr_flag = UAMP_RAND|UAMP_INUM;
    rne.logr_idnum = OSRandom(); /* some random number */
    *rl = htonPackXbitmap(PsLoginReply, (byte *)&rne, r, rne.logr_flag);
    return(aeAuthContinue);
  }

  if (uamflags[uam] & UAMP_PASS) {
    bcopy(lg.log_passwd,upwd,MAXPASSWD);	/* copy the password */
    upwd[MAXPASSWD] = '\0';		/* make sure null terminated */
  }
  if (DBSRV) {
    printf("Login ver=%s, uam=%s, user=%s, pwd=%s\n",
	    lg.log_ver,lg.log_uam,
	  ((uamflags[uam] & UAMP_USER) ? (char *)lg.log_user : "<anonymous>"),
	    ((uamflags[uam] & UAMP_PASS) ? upwd : "no passwd"));
  }

  err = OSLogin((char *)lg.log_user, upwd, NULL, uam);
  if (err == noErr)
    loggedin = TRUE;
  return(err);
}  

/*ARGSUSED*/
OSErr
FPLoginCont(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  LoginContPkt lcp;
  OSErr err;

  ntohPackXbitmap(PsLoginCont, p, l, &lcp, UAMP_INUM); /* get id num */
  if (lcp.lgc_idno != rne.logr_idnum)
    return(aeParamErr);		/* what else to do? */
  /* everything okay, so unpack encrypted passwd */
  ntohPackXbitmap(PsLoginCont, p, l, &lcp, UAMP_INUM|UAMP_ENCR);
  if (DBSRV) {
    printf("Login Randnum exchange for %s\n",username );
  }
  err = OSLogin(username, lcp.lgc_encrypted, rne.logr_randnum, UAM_RANDNUM);
  if (err == noErr)
    loggedin = TRUE;
  return(err);
}

OSErr
FPChgPasswd(p, l, r, rl)
byte *p, *r;
int l, *rl;
{
  ChgPasswdPkt cpp;
  ChgPasswdReplyPkt cprp;
  int uam;
  OSErr err;

  (void)ntohPackX(PsChangePassword, p, l, (byte *)&cpp);
  if ((uam = mapuamstr(cpp.cp_uam)) == UAM_UNKNOWN) {
    log("BAD UAM %s in change password attempt", cpp.cp_uam);
    return(aeBadUAM);			/* no... forget it */
  }
  if (uam == UAM_ANON)
    return(aeBadUAM);
  if (DBSRV) {
    printf("ChangePassword uam=%s, user=%s\n",
	   cpp.cp_uam, cpp.cp_user);
  }
  err = OSChangePassword(cpp.cp_user, cpp.cp_oldpass, cpp.cp_newpass, uam);
  if (err != noErr || uam != UAM_CLEAR)
    return(err);
  /* only here if noErr in change and cleartext */
  bzero(&cprp, sizeof(cprp));	/* make sure zero first */
  cprp.cpr_cmd = 0;
  cprp.cpr_zero = 0;
  strcpy(cprp.cpr_uam, cpp.cp_uam); /* copy uam */
  bcopy(cpp.cp_newpass, cprp.cpr_newpass, sizeof(cprp.cpr_newpass));
  *rl = htonPackX(PsChangePasswordReply, (byte *)&cprp, r);
  return(noErr);
}

/*
 * AFP2.0: get user information 
*/
FPGetUserInfo(p, l, r, rl)
byte *p, *r;
int l, *rl;
{
  GetUserInfoPkt guip;
  GetUserInfoReplyPkt guirp;
  OSErr err;

  (void)ntohPackX(PsGetUserInfo, p, l, (byte *)&guip);
  guirp.guir_bitmap = guip.gui_bitmap;
  err=OSGetUserInfo((guip.gui_flag & GUI_THIS_USER)!=0,guip.gui_userid,&guirp);
  if (err != noErr)
    return(err);
  *rl=htonPackXbitmap(PsGetUserInfoReply,(byte *)&guirp,r,guirp.guir_bitmap);
  return(noErr);
}

#ifdef notdef
int IndStrPack(d,s)
byte *d;
char *s[];
{
  IniIndStr(d);				/* init indexed string */
  for (; *s != NULL; s++)		/* copy entries from array */
    AddIndStr(*s,d);			/*  adding each array element */
  return(IndStrLen(d));			/* return length */
}
#endif

int 
GetSrvrInfo(r,sname,icon,iconsize)
byte *r;
char *sname;
byte icon[];
int iconsize;
{
  GetSrvrInfoReplyPkt sr;
  int i,len;
  byte avobuf[AFPVERSZ],uamobuf[AFPUAMSZ];
  OPTRType avo,uamo,vicono;

  strcpy(sr.sr_machtype,afpmtyp);
  cpyc2pstr(sr.sr_servername,sname);
  sr.sr_flags = SupportsFPCopyFile;

  vicono.optr_loc = icon;
  vicono.optr_len = iconsize;
  sr.sr_vicono = (char *) &vicono;

  IniIndStr(avobuf);
  for (i = 0; afpversions[i].version_name != NULL; i++)
    AddIndStr(afpversions[i].version_name, avobuf);
  avo.optr_len = IndStrLen(avobuf);
  avo.optr_loc = avobuf;
  sr.sr_avo = (byte *) &avo;

  IniIndStr(uamobuf);
  for (i=0 ; i < numuam; i++)
    AddIndStr(afpuams[i].uamname, uamobuf);
  uamo.optr_len = IndStrLen(uamobuf);
  uamo.optr_loc = uamobuf;
  sr.sr_uamo = (byte *) &uamo;
  return(htonPackX(ProtoSRP,(byte *) &sr,r));
}

PrtSrvrInfo(pkt,pktl)
byte *pkt;
int pktl;
{
  GetSrvrInfoReplyPkt sr;
  char name[MAXSNAM+1];

  ntohPackX(ProtoSRP,pkt,pktl,(byte *) &sr); /* unpack from net */
  cpyp2cstr(name,sr.sr_servername);

  printf("PrtSrvrInfo Packet length is %d\n",pktl);
  printf("  Machine Type = %s\n",sr.sr_machtype);
  printf("  Server Name  = %s\n",name);
  printf("  Flags = %d\n",sr.sr_flags);
  printf("  AFP Versions Supported:\n");
  PrtIndStr(sr.sr_avo);
  printf("  User Authentication Methods:\n");
  PrtIndStr(sr.sr_uamo);
  printf("  Icon %s present\n",(sr.sr_vicono == 0) ? "is not" : "is");
}

/*ARGSUSED*/
OSErr
FPLogout(p,l,r,rl)
char *p,*r;
int l,*rl;
{
  printf("FPLogout\n");
  return(noErr);
}

/*
 * OSErr FPGetSrvrParms(byte *p,byte *r,int *rl)
 *
 * This call is used to retrieve server-level parameters (for now only
 * the volume names)
 *
 */

/*ARGSUSED*/
OSErr
FPGetSrvrParms(p,l,r,rl)
byte *p,*r;
int l,*rl;
{
  extern PackEntry ProtoGSPRP[];
  GetSrvrParmsReplyPkt gpr;
  byte *up;
  int cnt;

  gpr.gspr_time = CurTime();
  gpr.gspr_nvols = VCount();
  cnt = htonPackX(ProtoGSPRP, (byte *)&gpr, r);
  cnt += VMakeVList(r+cnt);	/* add vols, return count */
  *rl = cnt;			/* pkt length */
  return(noErr);		/* no error */
}

/*
 * void SrvrSetTrace(char *tstr)
 *
 * Set trace of command packets on input, output, or both.  Tstr 
 * is a string containing items of the form:
 *
 *	[I|O|B]CmdName [I|O|B]CmdName ...
 *
 * The first character of an item specifies if you want the packet
 * displayed on input, output, or both input and output. The rest
 * of the item is the name of the command, Enumerate or AddAPPL for
 * example.
 *
 */

int SetPktTrace(tstr)
char *tstr;
{
  int flg,i;
  char cmdbuf[40],*cp,*opt,c;
  
  while (*tstr != '\0') {
    while (*tstr == ' ' || *tstr == '\t')
      tstr++;

    if (*tstr == '\0')
      break;
    
    switch (c = *tstr++) {
    case 'I': case 'i':
      flg = DSPF_DMPIN; opt = "input"; break;
    case 'O': case 'o':
      flg = DSPF_DMPOUT; opt = "output"; break;
    case 'B': case 'b':
      flg = DSPF_DMPBOTH; opt = "input and output"; break;
    default:
      fprintf(stderr,"SetPktTrace: I, O, or B required.  %c unknown\n",c);
      return(FALSE);
    }

    cp = cmdbuf;
    while (*tstr != ' ' && *tstr != '\t' && *tstr != '\0')
      *cp++ = *tstr++;
    *cp++ = '\0';
    for (i=0; i < NumEntries; i++)
      if (strcmpci(cmdbuf,Entries[i].dsp_name) == 0) {
	fprintf(stderr,"SetPktTrace: Tracing %s on %s\n",
		Entries[i].dsp_name,opt);
	Entries[i].dsp_flg = flg;
	break;
      }
    if (i >= NumEntries) {
      fprintf(stderr,"SetPktTrace: Unknown command %s\n",cmdbuf);
      return(FALSE);
    }
  }
  return(TRUE);
}

#ifndef NORUSAGE
private 
acctime(b,a,s)
struct timeval *b,*a,*s;
{
  s->tv_sec += a->tv_sec - b->tv_sec;
  s->tv_usec += a->tv_usec - b->tv_usec;
  if (s->tv_usec < 0) {
    s->tv_sec--;
    s->tv_usec += uSEC;
  }
  if (s->tv_sec > uSEC) {
    s->tv_sec++;
    s->tv_usec -= uSEC;
  }
}

private
printt(s,tv)
char *s;
struct timeval *tv;
{
  printf("%3d.%06d %s ",tv->tv_sec,tv->tv_usec,s);
}

private struct rusage before;

private
clockstart()
{
  getrusage(RUSAGE_SELF,&before);
}

private
clockend(d)
AFPDispEntry *d; 
{
  struct rusage after;

  getrusage(RUSAGE_SELF,&after);

  acctime(&before.ru_utime,&after.ru_utime,&d->dsp_utime);
  acctime(&before.ru_stime,&after.ru_stime,&d->dsp_stime);
}
#endif

#ifdef USETIMES
private struct tms before;

private
clockstart()
{
  (void)times(&before);
}

private
clockend(d)
AFPDispEntry *d; 
{
  struct tms after;

  (void)times(&after);

  d->dsp_utime += after.tms_utime - before.tms_utime;
  d->dsp_stime += after.tms_stime - before.tms_stime;
  d->dsp_utime += after.tms_cutime - before.tms_cutime;
  d->dsp_stime += after.tms_cstime - before.tms_cstime;
}

#ifndef HZ			/* in case not defined... */
# define HZ 60
#endif
private
printt(s,tv)
char *s;
time_t *tv;
{
  float pval;
  pval = ((float)*tv)/((float)HZ);
  printf("%.06f %s ",pval,s);
}

#endif

SrvrPrintStats()
{
  int i;

  printf("\nServer Statistics:\n");
  for (i=0; i < NumEntries; i++)
    if (Entries[i].dsp_cnt != 0) {
      printf("  %20s Count=%5d ",Entries[i].dsp_name,
	     Entries[i].dsp_cnt);
      printt("Usr",&Entries[i].dsp_utime);
      printt("Sys",&Entries[i].dsp_stime);
      printf("\n");
    }
}
