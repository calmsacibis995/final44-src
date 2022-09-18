/*
 *  Author: cck    Date: 88/05/13 09:28:13  
 *  Header: afpcmd.c,v 1.11 88/05/13 09:28:13 cck Rel  
 *  Revision: 1.11  
*/

/*
 * afpcmd.c - Packing and unpacking commands
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987 by The Trustees of Columbia University in the
 * City of New York.
 *
 * WARNING: if your machine is not a vax, sun, ibm pc/rt or pyramid
 * you must define BYTESWAPPED if you machine is byteswapped
 *
 * Edit History:
 *
 *  Thu Oct 30	Schilit    Created
 *
 */

#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>		/* for ntohs, etc. */
#include <netat/appletalk.h>
#include <netat/afp.h>
#include <netat/afpcmd.h>
/* following would be really simple if we could use #if, but vms */
/* c doesn't like and hopefully someday... */
#ifndef BYTESWAPPED
# ifdef vax
/* This should be defined if you are byte swapped. */
#  define BYTESWAPPED
# endif
#endif
/* What bogusity */
#ifndef LOOSE_BYTESWAPPED
# ifdef vax
/* This should only be defined if you are byte swapped and you can be sure */
/* (byte *) would be the same as a (word *) or (dword *) */
#  define LOOSE_BYTESWAPPED
# endif
#endif

#ifndef BYTESWAPPED
# ifdef ns16000
#  define BYTESWAPPED
# endif
#endif
#ifndef BYTESWAPPED
# ifdef ns32000
#  define BYTESWAPPED
# endif
#endif
/* add this in case sequent doesn't define nsxxxxx */
#ifndef BYTESWAPPED
# ifdef sequent
#  define BYTESWAPPED
# endif
#endif

/* machines that aren't byteswapped include: ibm032, pyr, sun, hpux, etc */

#define NULL 0

export void InitPackTime();
private void ItoETime();
private void EtoITime();

char *PackNames[] = {
  "Word",			/* P_WORD */
  "Byte",			/* P_BYTE */
  "Double Word",		/* P_DWRD */
  "Bytes",			/* P_BYTS */
  "Pascal String",		/* P_PSTR */
  "BitMap",			/* P_BMAP */
  "Offset String",		/* P_OSTR */
  "Path String",		/* P_PATH */
  "Offset to Pointer",		/* P_OPTR */
  "Offset Path",		/* P_OPTH */
  "Even boundary",		/* P_EVEN */
  "Zero",			/* P_ZERO */
  "Time"			/* P_TIME */
  };

int
ntohPackX(pt, net, nlen, host)
PackEntry *pt;
byte *net;
byte *host;
int nlen;
{
  int ntohPackXbitmap();

  return(ntohPackXbitmap(pt, net, nlen, host, (word)0));
}

int ntohPackXbitmap(pt,net,nlen,host, bitmap)
PackEntry *pt;
byte *net;
byte *host;
int nlen;
word bitmap;
{
  int i;
  int si = 0;
  word bmap = bitmap;
  void upack();

  /* need to find bmap */

  for (i=0; pt[i].pe_typ != P_END; i++)
    if (si < nlen)
      upack(&pt[i],net,&si,host,&bmap); /* unpack each item */
  return(si);
}

typedef struct Var_Object {
  int vo_typ;				/* type of variable object */
  byte *vo_offset;			/* store offset word (INT) here */
  byte *vo_object;			/* pointer to the object to store */
} VarObject;

typedef struct {
  int vol_first;			/* index at start of var objects */
  int vol_count;			/* count of var objects */
  VarObject vol_vos[10];		/* array of variable objects */
} VarObjList;

/*
 * Convert Packet from Host to Net, returns size of net packet.
 *
 */

int htonPackX(pe, host, net)
PackEntry *pe;
byte *host;
byte *net;
{
  return(htonPackXbitmap(pe, host, net, 0));
}

int
htonPackXbitmap(pe,host,net, bitmap)
PackEntry *pe;
byte *host;
byte *net;
word bitmap;
{
  VarObjList vol;
  int i;
  word bmap = bitmap;
  int nidx = 0;
  void pack();

  vol.vol_first = 0;			/* position 0 for first var object */
  vol.vol_count = 0;			/* no var objects */

  for (i=0; pe[i].pe_typ != P_END; i++)
   pack(&pe[i],host,net,&nidx,&bmap,&vol);

  /* scan variable length object list and pack them now */
  
  for (i = 0; i < vol.vol_count; i++) {
    byte *d;
    VarObject *vo;
    OPTRType *optr,**optrr;
    word wrd;

    vo = &vol.vol_vos[i];		/* handle on a var object */
    /* set offset from start (in remember spot) */
    wrd = htons(nidx-vol.vol_first);
    bcopy(&wrd, vo->vo_offset, sizeof(word));
    d = &net[nidx];			/* destination */
					/* assume object is PSTR */
    switch (vo->vo_typ) {
    case P_OSTR:
      cpyc2pstr(d,vo->vo_object);	/* copy the pascal string */
      nidx += (*d)+1;
      break;
    case P_OPTR:			/* is a variable length object */
      optrr = (OPTRType **) (vo->vo_object); 
      optr = *optrr;
      bcopy(optr->optr_loc,d,optr->optr_len); /* copy the bytes */
      nidx += optr->optr_len;		/* increment length */
      break;
    }
  }
  return(nidx);			/* return length */
}  
    

  
void pack(pe,src,dest,di,bmap,vol)
PackEntry *pe;
byte *src,*dest;
int *di;
VarObjList *vol;
word *bmap;
{
  byte *s,*d;
  int siz;
  word wrd;
  dword dwrd;

  if (pe->pe_bit != 0) {		/* check if bitmap item */
    if ((*bmap & pe->pe_bit) == 0)	/* see if a requested bitmap item */
      return;				/*  no, forget it */
  }

  d = &dest[*di];			/* destination is net */
  s = &src[pe->pe_off];			/* source is host */
  siz = pe->pe_siz;

  switch (pe->pe_typ) {			/* according to the data type */
  case P_BMAP:				/* bitmap (2 bytes) */
    bcopy(s, bmap, sizeof(word));	/* copy bitmap */
    vol->vol_first = *di;		/*  offset */
    break;				/* BITMAP does NOT get included */
#ifdef BYTESWAPPED
  case P_WORD:
# ifdef LOOSE_BYTESWAPPED
    /* we should be able to get away with this */
    *((word *)d) = htons(*(word *)s);
# else
    bcopy(s, &wrd, sizeof(word));	/* copy in case not byte aligned */
    wrd = htons(wrd);			/* convert to netorder */
    bcopy(&wrd, d, sizeof(word));	/* and copy into dest */
# endif
    *di += 2;
    break;
  case P_DWRD:				/* long (4 bytes) */
# ifdef LOOSE_BYTESWAPPED
    *((dword *)d) = htonl(*(dword *)s);
# else
    bcopy(s, &dwrd, sizeof(dword));	/* copy in case not byte aligned */
    dwrd = htonl(dwrd);			/* convert to netorder */
    bcopy(&dwrd, d, sizeof(dword));	/* and copy into dest */
# endif
    *di += 4;
    break;
#else
  case P_WORD:				/* int (2 bytes) */
  case P_DWRD:
#endif
  case P_BYTE:
  case P_BYTS:
    bcopy(s, d, siz);			/* copy the word */
    *di += siz;
    break;
  case P_TIME:			/* do external to internal time conversion */
    /* assumes time_t input, sdword output */
    bcopy(s,&dwrd,sizeof(dwrd)); /* copy it */
    *di += 4;			/* advance */
    ItoETime(dwrd, d);		/* convert to internal time */
    break;
  case P_PSTR:				/* c to pascal string */
    cpyc2pstr(d,s);
    *di += (*d)+1;
    break;
  case P_OPTR:
  case P_OSTR:				/* offset string */
    {
      VarObject *vo;

      vo = &vol->vol_vos[vol->vol_count++]; /* handle on object entry */
      vo->vo_typ = pe->pe_typ;		/* save type */
      vo->vo_object = s;		/* the object to pack */
      vo->vo_offset = d;		/* location to store offset */
      *di += 2;				/* increment by offset size */
    }
    break;
  case P_PATH:
    bcopy(s,d,(int) (*s)+1);	/* pascal string with imbedded nulls */
    *di += (*s)+1;
    break;
  case P_EVEN:
    if ((*di % 2) != 0) {
      *d = 0;			/* zero the current byte */
      (*di)++;
    }
    break;
  case P_ZERO:
    bzero(d, siz);
    *di += siz;
    break;
  }
  return;
}


/*
 *
 * Unpack net to host. Source is net, dest is host.
 *
 */

void upack(pe,src,si,dest,bmap)
PackEntry *pe;
int *si;
byte *src,*dest;
word *bmap;
{
  word sos;
  byte *d,*s;
  word wrd;
  dword dwrd;
  int siz;

  if (pe->pe_bit != 0)			/* check bitmap active */
    if ((*bmap & pe->pe_bit) == 0) 	/* then if not a bitmap item */
      return;				/*  forget it */

  d = &dest[pe->pe_off];		/* remember host destination */
  s = &src[*si];			/* net source */
  siz = pe->pe_siz;

  switch (pe->pe_typ) {			/* according to the data type */
  case P_BMAP:				/* bitmap (2 bytes) */
    bcopy(d, bmap, sizeof(word));	/* copy bitmap */
    break;
#ifdef BYTESWAPPED
  case P_WORD:				/* word (2 bytes) */ 
# ifdef LOOSE_BYTESWAPPED
    *((word *)d) = ntohs(*(word *)s);    
# else
    bcopy(s, &wrd, sizeof(word));	/* copy in case unaligned */
    wrd = ntohs(wrd);			/* convert to net order */
    bcopy(&wrd, d, sizeof(word));	/* and copy it back */
# endif
    *si += 2;
    break;
  case P_DWRD:				/* double word (4 bytes) */
# ifdef LOOSE_BYTESWAPPED
    *((dword *)d) = ntohl(*(dword *)s);
# else
    bcopy(s, &dwrd, sizeof(dword));	/* copy in case unaligned */
    dwrd = ntohl(dwrd);			/* convert to net order */
    bcopy(&dwrd, d, sizeof(dword));	/* and copy it back */
# endif
    *si += 4;
    break;
#else
  case P_WORD:				/* word (2 bytes) */
  case P_DWRD:				/* double word (4 bytes) */
#endif
  case P_BYTE:				/* byte (1 byte) */
  case P_BYTS:				/* byte string  */
    bcopy(s,d,siz);			/* copy bytes */
    *si += siz;
    break;
  case P_TIME:			/* do external to internal time conversion */
    /* assumes sdword input, time_t output */
    bcopy(s,&dwrd,sizeof(dwrd)); /* copy it */
    *si += 4;			/* advance */
    EtoITime(dwrd, d);		/* convert to internal time */
    break;
  case P_PSTR:				/* c to pascal string */
    cpyp2cstr(d,s);
    *si += (*s)+1;
    break;
  case P_OSTR:				/* offset string */
    sos = ntohs(*(word *)s);		/* pick up offset from base */
    *si += 2;
    cpyp2cstr(d,&src[sos]);		/* copy string */
    break;
  case P_OPTH:
    sos = ntohs(*(word *)s);		/* pick up offset from base */
    *si += 2;
    bcopy(&src[sos],d,(int)src[sos]+1);	/* copy string */
    break;
  case P_PATH:
    bcopy(s,d,(int) (*s)+1);		/* pascal string with imbedded nulls */
    *si += (*s)+1;
    break;
  case P_OPTR:
    sos = ntohs(*(word *)s);		/* pick up offset from base */
    *si += 2;
    *((char **)d) = (char *)&src[sos];
    break;
  case P_EVEN:
    if ((*si % 2) != 0)			/* even boundary? */
      (*si)++;				/* no, move ahead */
    break;
  case P_ZERO:				/* supposed to be zero? */
    *si += siz;				/* then, just skip */
    *d = 0;				/* zero dest */
    break;
  }
}

/*
 * void PackDWord(dword s, byte *d)
 *
 * Pack a double word into destination.
 *
 */

void PackDWord(s,d)
dword s;
byte *d;
{
#ifdef LOOSE_BYTESWAPPED
  *((dword *)d) = htonl(s);
#else
# ifdef BYTESWAPPED
  s = htonl(s);
# endif
  bcopy(&s, d, sizeof(dword));
#endif
}


void PackWord(s,d)
word s;
byte *d;
{
#ifdef LOOSE_BYTESWAPPED
  *((word *)d) = htons(s);
#else
# ifdef BYTESWAPPED
  s = htons(s);
# endif
  bcopy(&s, d, sizeof(word));
#endif
}

/*
 *
 * Unpack double word (4 bytes) from src into dest.
 * The src pointer is updated.
 *
 */
void
UnpackDWord(src,dest)
byte **src;
dword *dest;
{
#ifdef BYTESWAPPED
# ifdef LOOSE_BYTESWAPPED
  *dest = ntohl(*(dword *)(*src));
# else
  dword dwrd;

  bcopy(*src, &dwrd, sizeof(dword));
  dwrd = ntohl(dwrd);
  bcopy(&dwrd, dest, sizeof(dword));
# endif
#else
  bcopy(*src, dest, sizeof(dword));
#endif
  *src += 4;			/* update source pointer */
}


/*
 *
 * Unpack word (2 bytes) from src into dest.  The src pointer is updated.
 *
 */
void UnpackWord(src,dest)
byte **src;
word *dest;
{
#ifdef BYTESWAPPED
# ifdef LOOSE_BYTESWAPPED
  *dest = ntohs(*(word *)(*src));
# else
  word wrd;

  bcopy(*src, &wrd, sizeof(word));
  wrd = ntohs(wrd);
  bcopy(&wrd, dest, sizeof(word));
# endif
#else
  bcopy(*src, dest, sizeof(word));
#endif
  *src += 2;			/* update source pointer */
}

/*
 * void ItoETime(time_t it, dword *et)
 * void EtoITime(dowrd et, time_t *it) 
 *
 * Convert between Internal Unix time and External AFP time.
 * 
 * All date and time quantities used by AFP are Greenwich Mean Time (GMT)
 * values.  They are 32 bit signed integers corresponding to the number of
 * seconds measured from 12:00AM January 1, 2000 (the start of the next
 * century corresponds to datetime=0).
 *
 * BSD time base is 12:00AM January 1, 1970
 * AFP time base is 12:00AM January 1, 2000
 *
 * Actually, it seems that the Mac sends MacTime - could it be
 * that our copy of AppleShare does the wrong thing?  Version 1.00 was
 * bad.  Fixed in 1.10 and (hopefully) beyond.
 * 
 * Another problem exists with DST which is not handled here.
 * I mean, things will be within 2 hours isn't that good enough :-)
 *
 * WARNING: if this code breaks, it will be on or near Jan 1, 2000
 *  or Jan 18, 2038.  Of course, it's doubtful that this code
 *  will last that long :-)
 *
 */
private int mactime_not_inited = 1;
private long mymactime;
private long maczerotime;
/* difference btwn unix and mac in seconds */
/* mac starts at jan 1, 1904 for appleshare 1.0 */
#define AS1DOT0_MACZEROTIME 0	/* zero time - see comments above */
#define AS1DOT0_MACTIME (66*365+17)*24*60*60L

/* difference btween midnight jan 1, 1970 and midnight jan 1, 2000 */
/* for all others */
#define MACTIME (((30*365+7)*(-24)*3600L))
#define MACZEROTIME 0x80000000	/* zero time - from AppleShare 1.1 on */

/* Does time zone adjustment */

/* call with flag set for appleshare 10 style */
export void
InitPackTime(flag)
int flag;
{
  struct timeval tp;
  struct timezone tzp;

  mactime_not_inited = 0;
  gettimeofday(&tp, &tzp);
  if (flag) {
    mymactime = AS1DOT0_MACTIME;
    maczerotime = AS1DOT0_MACZEROTIME;
  } else {
    mymactime = MACTIME;
    maczerotime = MACZEROTIME;
  }
  mymactime -= ((long)tzp.tz_minuteswest*60);
}

private void
ItoETime(ost,atpt)
time_t ost;
sdword *atpt;			/* signed double word */
{
  sdword temp;

  if (mactime_not_inited)
    InitPackTime(0);		/* assume past version 1.0 */
  temp = htonl((ost) ? ((sdword)ost + mymactime) : maczerotime);
  bcopy(&temp, atpt, sizeof(temp));
}

private void
EtoITime(atpt,ost)
sdword atpt;			/* signed double word */
time_t *ost;
{
  time_t temp;
  if (mactime_not_inited)
    InitPackTime(0);		/* assume past version 1.0 */
  atpt = ntohl(atpt);
  temp = (atpt == maczerotime) ? 0 : ((time_t)atpt - mymactime);
  bcopy(&temp, ost, sizeof(time_t)); /* copy out */
}
