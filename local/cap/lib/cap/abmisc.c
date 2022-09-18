/*
 *  Author: cck    Date: 88/05/13 09:29:02  
 *  Header: abmisc.c,v 1.17 88/05/13 09:29:02 cck Rel  
 *  Revision: 1.17  
*/

/*
 * abmisc.c - miscellaneous, but nevertheless useful routines
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University 
 *  in the City of New York.
 *
 *
 * Edit History:
 *
 *  June 13, 1986    Schilit    Created.
 *  June 15, 1986    CCKim	move to abmisc.c
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netat/appletalk.h>

/*
 * cpyc2pstr(char *ps, char *cs)
 * 
 * Copy a C style string to an Apple Pascal style string
 *
 * Restrictions: sizeof(*ps) must be >= 1+sizeof(*cs)
 */ 

void
cpyc2pstr(ps,cs)
char *ps,*cs;
{

  *ps++ = (u_char) strlen(cs);	/* copy in length, one byte */
  while (*ps++ = *cs++) ;	/* copy in the rest... */
}

/*
 * cpyp2cstr(char *cs, char *ps)
 * 
 * Copy a Apple Pascal style string to C string
 *
 */ 

void
cpyp2cstr(cs,ps)
char *cs,*ps;
{
  bcopy(ps+1,cs,(u_char) *ps);
  cs[*ps] = '\0';		/* tie off */
}

/*
 * pstrcpy(d, s) - like strcpy, but for pascal strings
 *
*/
pstrcpy(d, s)
byte *d, *s;
{
  int len = (int)*s;

  bcopy(s, d, len+1);		/* +1 for length too */
}

/* like strncpy, but for pascal strings */
pstrncpy(d, s, n)
byte *s;
byte *d;
int n;
{
  int len = (int)*s;

  if (len > n)
    len = n;
  bcopy(s+1, d+1, len);
  *d = len&0xff;		/* single byte */
}
/*
 * pstrlen(s) - like strlen, but for pascal strings
 *
*/
pstrlen(s)
byte *s;
{
  return((int)*s);
}

/*
 * pstrcmp(s1, s2) - like strcmp, but for pascal strings
 *
*/
pstrcmp(s1, s2)
byte *s1;
byte *s2;
{
  int len1 = ((int)*s1)+1;	/* account for length */

  s1++, s2++;			/* skip length fields */
  /* no special check for length since this will also do the "right" thing */
  /* (also, know we have at least one) */
  while (len1--) {
    if (*s1 != *s2)
      return(*s1 - *s2);	/* returns right thing? */
    s1++, s2++;
  }
  return(0);			/* equal */
}

/* 
 * dbugarg(char *argv)
 *
 * Process the -d argument from the command line, setting debug options
 * in global dbug structure.
 *
 * a - db_atp; l - db_lap; d - db_ddp; n - db_nbp;  
 * i - db_ini; p - db_pap;   
 *
*/

dbugarg(s)
char *s;
{
  int err = 0;
  while (*s != '\0' && !err) {
    switch(*s) {
    case 'l': dbug.db_lap = TRUE; printf("debugging LAP\n"); break;
    case 'd': dbug.db_ddp = TRUE; printf("debugging DDP\n"); break;
    case 'a': dbug.db_atp = TRUE; printf("debugging ATP\n"); break;
    case 'n': dbug.db_nbp = TRUE; printf("debugging NBP\n"); break;
    case 'p': dbug.db_pap = TRUE; printf("debugging PAP\n"); break;
    case 'i': dbug.db_ini = TRUE; printf("debugging INI\n"); break;
    case 's': dbug.db_asp = TRUE; printf("debugging ASP\n"); break;
    case 'k': dbug.db_skd = TRUE; printf("debugging SKD\n"); break;
    default: 
      err++;
    }
    s++;
  }
  if (err) {
    fprintf(stderr,"l lap, d ddp, a atp, n nbp, p pap, i ini, s asp\n");
    fprintf(stderr,"k scheduler\n");
    return(-1);
  }
  return(0);
}

/*
 * Establish a bds (of size most numbds) with buffer buf of size bufsiz 
 * set all bds userdata fields to userdata
 *
 * return count of bds's.  More buffer than bds is okay.
 *
*/
int
setup_bds(bds, numbds, segsize, buf, bufsiz, userdata)
BDS bds[];
int numbds;
int segsize;
char *buf;
int bufsiz;
atpUserDataType userdata;
{
  int cnt, i, cursize;

  i = cnt = 0;
  do {
    bds[i].userData = userdata;
    cursize = min(segsize, bufsiz-cnt);
    bds[i].buffSize = cursize;
    bds[i].buffPtr = buf+cnt;
    cnt += cursize;
    i++;
  } while ((cnt - bufsiz) < 0 && i < numbds);
  return(i);
}

int
sizeof_bds(bds, numbds)
BDS bds[];
int numbds;
{
  int i, cnt;

  for (i = 0, cnt = 0; i < numbds; i++)
    cnt += bds[i].dataSize;
  return(cnt);
}

/* routines to deal with "Indexed" strings */
/**** should be in abmisc ******/

/*
 * void IniIndStr(byte *istr)
 *
 * Initialize an Indexed string for calls to AddIndStr
 *
 */

void
IniIndStr(istr)
byte *istr;
{
  *istr = 0;			/* index count is zero */
}

/*
 * void AddIndStr(char *src,byte *istr)
 *
 *
 * Add a c string to a Indexed string.  The c string always
 * is added to the end of the indexed string.
 *
 */

void
AddIndStr(src,istr)
char *src;
byte *istr;
{
  byte *idx = istr;
  int i;

  for (i = *istr++; i > 0; i--)	/* step past index, count down on it */
    istr += (*istr)+1;		/* move past each pascal string */
  cpyc2pstr(istr,src);		/* copy into idx string */
  (*idx)++;			/* increment the index */
}

/*
 * GetIndStr(char *dest,byte *istr,int index)
 * 
 * Copy from an indexed string into a c string.  Use index to select
 * the string entry within the indexed string type.
 *
 */ 

void
GetIndStr(dest,istr,idx)
char *dest;
byte *istr;
int idx;
{
  if (idx > 255 || idx >= *istr || idx < 0) {
    fprintf(stderr,"GetIndString: idx out of range\n");
    return;
  }

  istr++;			/* step past idx count */
  while (idx--)
    istr += (*istr)+1;		/* step past this pstr */
  cpyp2cstr(dest,istr);		/* then copy into destination */
}


/*
 * int IndStrCnt(byte *istr)
 *
 * Return the count of entries in an indexed string.
 *
 */

int
IndStrCnt(istr)
byte *istr;
{
  return(*istr);		/* this is easy... */
}


/*
 * IndStrLen(byte *istr)
 *
 * Return the length of the indexed string istr including the count byte.
 *
 */

int 
IndStrLen(istr)
byte *istr;
{
  byte *idx = istr;
  int i;

  istr++;			/* step past index */
  for (i=1; i <= (*idx); i++)
    istr += (*istr)+1;		/* move to next pascal string */
  return((istr-idx));		/* here is the count... */
}

/*
 * PrtIndStr(istr)
 *
 * For debugging, dump the content indexed string.
 *
 */

PrtIndStr(istr)
byte *istr;
{
  char cstr[256];
  byte *idx = istr;
  int i;

  printf("Entries in indexed string: %d\n",*istr);
  istr++;			/* step past index */
  for (i=1; i <= (*idx); i++) {
    cpyp2cstr(cstr,istr);	/* copy into c string */
    printf("%d: '%s'\n",i,cstr);
    istr += (*istr)+1;		/* move to next pascal string */
  }
}


/*
 * int strcmpci(char *s, char *t)
 *
 * Case insensitive version of strcmp.
 *
*/

strcmpci(s,t)
char *s,*t;
{
  register char c,d;

  for (;;) {
    if (isalpha((c = *s++)) && isupper(c))
      c = tolower(c);
    if (isalpha((d = *t++)) && isupper(d))
      d = tolower(d);
    if (c != d)
      return(c-d);
    if (c == '\0')
      return(0);
  }
}

/*
 * int strncmpci(char *s, char *t,int n)
 *
 * Case insensitive version of strcmp.
 *
*/

strncmpci(s,t,n)
char *s,*t;
int n;
{
  register char c,d;

  for (;n > 0;n--) {
    if (isalpha((c = *s++)) && isupper(c))
      c = tolower(c);
    if (isalpha((d = *t++)) && isupper(d))
      d = tolower(d);
    if (c != d)
      return(c-d);
    if (c == '\0')
      return(0);
  }
  return(0);			/* success on runnout */
}

/*
 * Take a string pointed to by p and duplicate it in a malloc'ed block
 * of memory.
 *
 * If the passed pointer is null, a null string is returned.
 *
 * returns: pointer to new string, null if no space
 *
*/
char *
strdup(p)
char *p;
{
  char *r = (char *)malloc((p == NULL) ? 1 : (strlen(p)+1));

  if (r == NULL)
    return(NULL);
  if (p == NULL) {
    *r = 0;
    return(r);
  }
  strcpy(r, p);
  return(r);
}

/*
 * int
 * cmptime (struct timeval *t1,*t2)
 *
 * values must be pairwise across <relative,relative> or
 *  <absolute,absolute>
 *
 * cmptime compares two time values and returns an integer
 * greater than, equal to, or less than zero according to
 * whether the time represented in t1 is greater than, equal
 * to, or less than t2.
 *
*/
int
cmptime(t1,t2)
struct timeval *t1,*t2;
{
  if ((t1->tv_sec == t2->tv_sec)) 	/* seconds the same? */
    if (t1->tv_usec == t2->tv_usec) 	/* and usec the same? */
      return(0);			/* then equal */
    else				/* otherwise depends on usec */
      return((t1->tv_usec < t2->tv_usec) ? -1 : 1);
  return((t1->tv_sec < t2->tv_sec) ? -1 : 1);
}

