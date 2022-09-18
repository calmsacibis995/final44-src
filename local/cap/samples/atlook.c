static char rcsid[] = " Author: cck    Date: 88/05/13 09:26:48  ";
static char rcsident[] = " Header: atlook.c,v 1.25 88/05/13 09:26:48 cck Rel  ";
static char revision[] = " Revision: 1.25  ";

/*
 * atlook - UNIX AppleTalk test program: lookup entities
 * with "ATLOOKLWS" defined, will also get pap status and confirm address.
 * with "ATPINGER" defined will "ping" remote with "echo request"
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  June 13, 1986    Schilit	Created.
 *  Dec  23, 1986    Schilit	Sort result, display in columns, clean up.
 *				add usage and options.
 *  Mar  16, 1987    CCKim	Clean up some more, merge with looks and pinger
 *
 */

char copyright[] = "Copyright (c) 1986,1988 by The Trustees of Columbia University in the City of New York";

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>			/* so htons() works for non-vax */
#include <netat/appletalk.h>		/* include appletalk definitions */

#define NUMNBPENTRY 100			/* max names we can lookup */

#ifndef ATPINGER
# define ATPINGER 0;
#endif
#ifndef ATLOOKLWS
# define ATLOOKLWS 0
#endif

/* ping defs */
typedef struct {
  u_char echoFunction;		/* echo function */
  int echoID;			/* internal id */
  int echoSLen;			/* send packet length */
  int echoRLen;			/* what we got back */
  struct timeval echo_send_time; /* time echo pkt was sent */
  struct timeval echo_response_time; /* time echo pkt came back */
} PINGPKT;

typedef struct {
  u_char echoFunction;
  char epdata[585];		/* cheap */
} ECHOPKT;

/* vars */
int pinger = ATPINGER;
int lwstatus = ATLOOKLWS;
char *deftype = "=";		/* default entity type */

int nbpretry = 3;		/* 3 retries */
int nbptimeout = 3;		/* 3/4 second by default */
int pingtimeout = sectotick(5);	/* 5 seconds by default */
int pingpktlen = sizeof(PINGPKT); /* size of ping pkt by default (min) */



/*
 * int compare(NBPTEntry *n1, NBPTEntry *n2)
 *
 * This is the comparison routine for the qsort() library function. 
 * Our comparison is on the entity's type string, and then the object 
 * string. In otherwords primary sort is type, secondary sort is object.
 *
 */

int
comparebyname(n1,n2)
NBPTEntry *n1,*n2;
{
  int rslt;

  if ((rslt = strcmp(n1->ent.typeStr.s,	/* compare types */
		     n2->ent.typeStr.s)) != 0)
    return(rslt);			/* return if they differ */
  return(strcmp(n1->ent.objStr.s,	/* types are the same, return */
		n2->ent.objStr.s));	/* the comparison of objects */
}

int
comparebynet(n1,n2)
NBPTEntry *n1,*n2;
{
  if (n1->addr.net != n2->addr.net) {
    if (n1->addr.net > n2->addr.net)
      return(1);
    return(-1);
  }
  if (n1->addr.node != n2->addr.node) {
    if (n1->addr.node > n2->addr.node)
      return(1);
    return(-1);
  }
  if (n1->addr.skt != n2->addr.skt) {
    if (n1->addr.skt > n2->addr.skt)
      return(1);
    return(-1);
  }
  return(0);
}

int
comparebyskt(n1,n2)
NBPTEntry *n1,*n2;
{
  if (n1->addr.skt != n2->addr.skt) {
    if (n1->addr.skt > n2->addr.skt)
      return(1);
    return(-1);
  }
  if (n1->addr.net != n2->addr.net) {
    if (n1->addr.net > n2->addr.net)
      return(1);
    return(-1);
  }
  if (n1->addr.node != n2->addr.node) {
    if (n1->addr.node > n2->addr.node)
      return(1);
    return(-1);
  }
  return(0);
}

int (*sortcomp)() = comparebyname;


usage(s)
char *s;
{
  fprintf(stderr,"usage: %s [-d FLAGS] [-P] [-S] [-n] [-s] [-t [p]<n>] \
[-r <n>] [-l <n>] nbpentity\n",s);
  fprintf(stderr,"\t -n means sort by net numbers\n");
  fprintf(stderr,"\t -s means sort by socket numbers\n");
  fprintf(stderr,"\t -r <n> - specifies number of retries (>=0)\n");
  fprintf(stderr,"\t -t [p]<n> - timeout between retries\n");
  fprintf(stderr,"\t    unless timeout modified by 'p' for ping timeout\n");
  fprintf(stderr,"\t -l <n> - specifies ping packet length\n");
  fprintf(stderr,"\t -P makes look pings the entities\n");
  fprintf(stderr,"\t   -t p<n> or -l <n> turns on pinging\n");
  fprintf(stderr,"\t -S makes look get the \"laserwriter\" status\n");
  fprintf(stderr,"\t    and makes the default type \"LaserWriter\"\n");
  fprintf(stderr,"\t -d FLAGS - cap library debugging flags\n");
  fprintf(stderr,"\tTimeouts are in ticks (1/4 units)\n");
  exit(1);
}

getnum(s)
char *s;
{
  int r;
  if (*s == '\0')
    return(0);
  r = atoi(s);
  if (r == 0 && *s != '0')
    return(-1);
  return(r);
}

tickout(n)
int n;
{
  int t = n % 4;		/* ticks */
  int s = n / 4;		/* seconds */
  int m = s / 60;		/* minutes */

  if (m != 0) {
    if (m >= 60)		/* an hour??????? */
      printf(" (are you crazy?)");
    printf(" %d %s", m, m > 1 ? "minutes" : "minute");
    s %= 60;			/* reset seconds to remainder */
  }
  if (s)			/* print seconds if any */
    printf(" %d",s);
  if (t) {			/* print ticks */
    if (s)
      printf(" and");
    if (t == 2) 
      printf(" one half");
    else
      printf(" %d fourths",t);
  }
  if (s || t)
    printf(" second");
  if (s > 1 || (t && s))
    printf("s");
}

doargs(argc,argv)
int argc;
char **argv;
{
  char *whoami = argv[0];
  extern char *optarg;
  extern int optind;
  int c;

  while ((c = getopt(argc, argv, "d:D:l:r:t:nsSP")) != EOF) {
    switch (c) {
    case 'd':
    case 'D':
      dbugarg(optarg);		/* some debug flags */
      break;
    case 'r':
      nbpretry = getnum(optarg);
      if (nbpretry <= 0)
	usage(whoami);
      printf("Number of NBP retries %d\n",nbpretry);
      break;
    case 't':
      if (optarg[0] != 'p')  {
	nbptimeout = getnum(optarg);
	if (nbptimeout < 0)
	  usage(whoami);
	printf("NBP Timeout");
	tickout(nbptimeout);
      } else {
	pingtimeout = getnum(optarg+1);
	if (pingtimeout == 0) {
	  /* message ? */
	  pingtimeout = 1;
	}
	pinger++;
	printf("ping timeout");
	tickout(pingtimeout);
      }
      putchar('\n');
      break;
    case 'l':
      pinger++;
      pingpktlen = atoi(optarg);
      break;
    case 'P':
      pinger++;
      break;
    case 'S':
      lwstatus++;
      deftype = "LaserWriter";	/* switch over */
      break;
    case 'n':
      sortcomp = comparebynet;
      break;
    case 's':
      sortcomp = comparebyskt;
      break;
    case '?':
    default:
      usage(whoami);
    }
  }
  return(optind);
}

my_create_entity(s, en)
char *s;
EntityName *en;
{
  create_entity(s, en);	/* must be fully specified name */
  if (*en->objStr.s == '\0')
    en->objStr.s[0] = '=';
  if (*en->typeStr.s == '\0')
    strcpy(en->typeStr.s,deftype); /*  to lookup... */
  if (*en->zoneStr.s == '\0')
    en->zoneStr.s[0] = '*';
}
    
main(argc,argv)
int argc;
char **argv;
{
  int i;
  EntityName en;			/* network entity name */

  abInit(TRUE);				/* initialize appletalk driver */
  nbpInit();				/* initialize nbp */
  checksum_error(FALSE);		/* ignore these errors */

  i = doargs(argc,argv);		/* handle arguments */
  if (pinger)
    pingInit();
  if (lwstatus)
    deftype = "LaserWriter";
  strcpy(en.objStr.s,"=");		/* create default entity */
  strcpy(en.typeStr.s,deftype);		/*  to lookup... */
  strcpy(en.zoneStr.s,"*");


  if (i == argc) {
    dolookup(&en);
  } else {
    for (; i < argc ; i++) {
      my_create_entity(argv[i], &en);
      dolookup(&en);
    }
  }
}

/*
 * given to timevals, compute the number of seconds
 *
*/
float
evtime(tvs, tve)
struct timeval *tvs, *tve;
{
  return(((float)(tve->tv_sec - tvs->tv_sec)) + 
	 (((float)(tve->tv_usec - tvs->tv_usec))/1000000.0));
}

dolookup(en)
EntityName *en;			/* network entity name */
{
  int err,i, len;
  AddrBlock addr;		/* Address of entity */
  PINGPKT *pingpkt;		/* ping packet */
  char *pbuf = NULL;		/* ping buf */
  NBPTEntry nbpt[NUMNBPENTRY];	/* table of entity names */
  nbpProto nbpr;		/* nbp protocol record */
  char name[sizeof(EntityName)*4*3+3];	/* for formatted entity name */
				/* 3 entries, of size entity name */
				/* each char can be up to 4 in length */
				/* +3 for :@ and null */


  nbpr.nbpRetransmitInfo.retransInterval = nbptimeout;
  nbpr.nbpRetransmitInfo.retransCount = nbpretry;
  nbpr.nbpBufPtr = nbpt;		/* place to store entries */
  nbpr.nbpBufSize = sizeof(nbpt);	/* size of above */
  nbpr.nbpDataField = NUMNBPENTRY;	/* max entries */
  nbpr.nbpEntityPtr = en;		/* look this entity up */

  len = dumptostr(name, en->objStr.s);
  name[len++] = ':';
  len += dumptostr(name+len, en->typeStr.s);
  name[len++] = '@';
  dumptostr(name+len, en->zoneStr.s);
  printf("Looking for %s ...\n",name);

  /* Find all objects in specified zone */
  err = NBPLookup(&nbpr,FALSE);		/* try synchronous */
  if (err != noErr)
    fprintf(stderr,"NBPLookup returned err %d\n",err);

  /* Sort the result for better viewing */

  qsort((char *)nbpt,(int) nbpr.nbpDataField,sizeof(NBPTEntry),sortcomp);

  /* malloc this so we make sure long enough */
  if (pinger) {
    if (pingpktlen < sizeof(PINGPKT))
      pingpktlen = sizeof(PINGPKT);
    pbuf = (char *)malloc(pingpktlen);	/* get ping packet */
    if (pbuf == NULL) {
      pinger = 0;
      fprintf(stderr,"Can't allocate packet for ping\n");
    }
    pingpkt = (PINGPKT *)pbuf;
  }
  /* Extract and print the items */
  for (i = 1; i <= nbpr.nbpDataField; i++) {
    NBPExtract(nbpt,nbpr.nbpDataField,i,en,&addr);
    len = dumptostr(name, en->objStr.s);
    name[len++] = ':';
    len += dumptostr(name+len, en->typeStr.s);
    name[len++] = '@';
    dumptostr(name+len, en->zoneStr.s);
    printf("%02d - %-40s [Net:%3d.%02d Node:%3d Skt:%3d]\n",
	   i,name,htons(addr.net)>>8, htons(addr.net)&0xff,addr.node,addr.skt);
    if (lwstatus)
      getstatus(en, &addr);
    if (pinger) {
      printf("Ping...");
      if (PingSend(&addr, pingtimeout, pbuf, pingpktlen) == noErr) {
	if (pingpkt->echoSLen != pingpkt->echoRLen) {
	  printf("sent length = %d, received %d...",
		 pingpkt->echoSLen, pingpkt->echoRLen);
	}
	if (pingpkt->echo_response_time.tv_sec != 0 ||
	    pingpkt->echo_response_time.tv_usec != 0) {
	  printf("round trip %f...",
		 evtime(&pingpkt->echo_send_time,
			&pingpkt->echo_response_time));
	}
	printf("Okay\n");
      } else
	printf("no response\n");
    }
  }
  if (pbuf)
    free(pbuf);
}

getstatus(en, addr)
EntityName *en;
AddrBlock *addr;
{
  PAPStatusRec statusbuf;
  char namebuf[100];		/* place to put name of entity */
  nbpProto nbpr;		/* NBP protocol record */
  int err;

  sprintf(namebuf, "%s:%s@%s", en->objStr.s, en->typeStr.s, en->zoneStr.s);
  PAPStatus(namebuf, &statusbuf, addr);
  printf("---");
  dumpstatus(&statusbuf);
  putchar('\n');

  nbpr.nbpRetransmitInfo.retransInterval = 4;
  nbpr.nbpRetransmitInfo.retransCount = 3;
  nbpr.nbpEntityPtr = en;	/* entity name */
  nbpr.nbpAddress = *addr;	/* all other old values */
    err = NBPConfirm(&nbpr,FALSE);
    if (err != noErr)
      printf("Confirm failed, code = %d...\n",err);
    else
      printf("Address confirmed for socket %d\n",nbpr.nbpDataField);
}

/*
 * Dump a PAP status message
*/
dumpstatus(statusbuf)
PAPStatusRec *statusbuf;
{
  int len = (int)(statusbuf->StatusStr[0]);
  unsigned char *s = &statusbuf->StatusStr[1];

  while (len--) {
    if (isprint(*s))
      putchar(*s);
    else
      printf("\\%o",*s&0xff);
    s++;
  }
}

dumptostr(str, todump)
char *str;
char *todump;
{
  char c;
  int i = 0;

  while ((c = *todump++)) {
    if (c > 0 && isprint(c)) {
      *str++ = c;
      i++;
    } else {
      sprintf(str,"\\%3o",c&0xff);
      str+=4;
      i+=4;
    }
  }
  *str = '\0';
  return(i);
}

/*
 * PING MODULE: single ping outstanding
 *
 * Good part of the definitions should be moved to appletalk.h
 * Good part of the routines should be rewritten and moved to abping.c
 *
*/


private int pingskt;
private int echoID;
private ABusRecord pingAbr;
private int pingout = 0;

OSErr
pingInit()
{
  void echo_listener();
  int err;

  echoID = 0;
  pingout = 0;
  pingskt = 0;
  err = DDPOpenSocket(&pingskt, echo_listener);
  if (err != noErr)
    fprintf(stderr, "no dynamic sockets left for ping\n");
  return(err);
}

void
echo_listener(skt, type, pkt, len, addr)
u_char skt;
u_char type;
char *pkt;
int len;
AddrBlock *addr;
{
  int cmd;
  PINGPKT copy_rpp;		/* copy of received ping packet */
  PINGPKT *rpp;			/* ptr to received ping pkt */
  PINGPKT *spp;			/* ptr to send ping pkt */
  ABusRecord *abr;
  struct timezone tz;

#ifdef DEBUG
  printf("Got pkt from %d.%d (skt %d) of size %d\n",
	 ntohs(addr->net), addr->node, addr->skt, len);
#endif

  /* reasons to drop packet */
  if (type != ddpECHO)
    return;
  if ((u_char )*pkt != echoReply)
    return;
  /* some day this will go down a queue... */
  abr = (pingout) ? &pingAbr : NULL;
  /* no outstanding pings */
  if (abr == NULL)
    return;

  /* just in case of byte aligment problems */
  bcopy(pkt, &copy_rpp, sizeof(copy_rpp));
  rpp = &copy_rpp;
  spp = (PINGPKT *)abr->proto.ddp.ddpDataPtr;
  if (rpp->echoID != spp->echoID) {
    return;			/* drop */
  }
  spp->echoRLen = len;		/* mark: can check for ip frags this way */
  gettimeofday(&spp->echo_response_time, &tz);
  abr->abResult = noErr;
}

echo_timeout(abr)
ABusRecord *abr;
{
  abr->abResult = reqFailed;
}

PingSend(addr, to, pingpkt, pingpktlen)
AddrBlock *addr;
int to;
PINGPKT *pingpkt;
int pingpktlen;
{
  ABusRecord *abr = &pingAbr;
  struct timezone tz;
  OSErr err;

  if (pingpktlen < sizeof(PINGPKT))
    return(-1);
  if (pingpktlen > ddpMaxData)	/* truncate silently */
    pingpktlen = ddpMaxData;
  abr->proto.ddp.ddpAddress = *addr;
  abr->proto.ddp.ddpAddress.skt = echoSkt;
  abr->proto.ddp.ddpSocket = pingskt;
  abr->proto.ddp.ddpType = ddpECHO;
  pingpkt->echoFunction = echoRequest;
  pingpkt->echoID = echoID++;	/* mark id */
  /* just in case someone tries to use it */
  bzero(&pingpkt->echo_response_time, sizeof(pingpkt->echo_response_time));
  pingpkt->echoSLen = pingpktlen; /* mark as length */
  pingpkt->echoRLen = 0;	/* mark as zero */
  abr->proto.ddp.ddpDataPtr = (u_char *)pingpkt;
  abr->proto.ddp.ddpReqCount = pingpktlen;
  gettimeofday(&pingpkt->echo_send_time, &tz); /* mark outgoing time */
  if ((err = DDPWrite(abr, FALSE)) < 0)
    return(err);
  pingout = 1;
  abr->abResult=1;
  Timeout(echo_timeout, (caddr_t)abr, to);
  while (abr->abResult > 0)
    abSleep(to, TRUE);
  remTimeout(echo_timeout, (caddr_t)abr);
  pingout = 1;
  return(abr->abResult);
}

