static char rcsid[] = " Author: cck    Date: 88/03/29 20:29:13  ";
static char rcsident[] = " Header: tlw.c,v 1.18 88/03/29 20:29:13 cck Rel  ";
static char revision[] = " Revision: 1.18  ";

/*
 * tlw - UNIX AppleTalk test program - talk to laserwriter
 *
 * Talk to the LaserWriter - interactive session
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986,1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  June 13, 1986    Schilit	Created.
 *  June 30, 1986    CCKim      Convert to TLW from lwpr
 *  July  2, 1986    Schilit	Make work with new stuff
 *  July  5, 1986    CCKim      Really make work with new stuff
 */

char copyright[] = "Copyright (c) 1986, 1988 by The Trustees of Columbia University in the City of New York";

#include <stdio.h>
#include <sys/param.h>
#ifndef _TYPES
 /* assume included by param.h */
# include <sys/types.h>
#endif

#include <sys/time.h>
#include <signal.h>

#include <netat/appletalk.h>	/* include appletalk definitions */
#include <netat/compat.h>	/* overrides for non-4.3 systems */

int cno;
#define RFLOWQ 8
#ifndef SFLOWQ
# define SFLOWQ 8
#endif
#define BUFMAX 512*RFLOWQ
#define SBUFMAX 512*SFLOWQ
char buf[SBUFMAX+10];
char rbuf[BUFMAX+10];

main(argc,argv)
int argc;
char **argv;
{
  char *LWNAME;
  char tbuf[sizeof(EntityName)*3+1];
  int stopall();
  int hangup();
  int pstatus();
  char *s;

  abInit(TRUE);			/* initialize appletalk driver */
  PAPInit();			/* init pap */
  nbpInit();			/* init nbp */

  switch (argc) {
  case 1:
    LWNAME = "LaserWriter Plus:LaserWriter@*"; /* default */
    break;
  case 2:
    LWNAME = argv[1];
    break;
  case 3:
    LWNAME = argv[1];
    s = argv[2];
    if (*s++ == '-' && *s++ == 'd')
      dbugarg(s);
    break;
  default:
    printf("Usage: %s <lw name> <timeout>\n",argv[0]);
    exit(1);
    break;
  }
  if (index(LWNAME,':') == NULL) {
    (void)sprintf(tbuf,"%s:LaserWriter@*", LWNAME);
    LWNAME = tbuf;
  }
  printf("Starting session with %s\n",LWNAME);

  setbuf(stdin, (char *)NULL);

  cno = openlw(LWNAME);
  signal(SIGHUP, stopall);
  signal(SIGINT, stopall);
  talk(cno);
  PAPClose(cno);		/* close connection */
  exit(0);			/* exit okay */
}


/*
 * open laserwriter connection
 * log errors every 5 minutes to stderr
 *
*/
int
openlw(lwname)
char *lwname;
{
  int i, cno, ocomp, err;
  PAPStatusRec status;

  i = 0;
  /* Keep trying to open */
  while ((err = PAPOpen(&cno, lwname, RFLOWQ, &status, &ocomp) ) != noErr) {
    if (err != -1)		/* should be can't find lw.. */
      fprintf(stderr,"PAPOpen returns %d\n",err);
    else {
      if ((i % 10) == 0) {	/* waited 5 minutes? */
	fprintf(stderr, "Problems finding %s\n",lwname);
	i = 1;
      } else i++;
    }
    sleep(30);			/* wait N seconds */
  }
  do {
    abSleep(16, TRUE);
    pstatus(status.StatusStr);
  } while (ocomp  > 0);
  return(cno);
}

dataready(fd, tcomp, dummy)
int fd;
int *tcomp;
int dummy;
{
  fdlistensuspend(fd);		/* no more select until we read */
  *tcomp = noErr;		/* data ready */
}

/*
 * Send a file to the specified connection
 */
talk(cno)
int cno;
{
  int eof, rlen, rcomp, wcomp, paperr, err;
  int tcomp, teof;
  char *getusername();

  printf("\nOkay\n");
  wcomp = 0;
  strcpy(buf, "/statusdict where {pop statusdict /jobname");
  strcat(buf, "(interactive session for ");
  strcat(buf, getusername());
  strcat(buf, ") put} if\nexecutive\n");
  if ((paperr=PAPWrite(cno, buf,strlen(buf), FALSE, &wcomp)) < 0) {
    printf("Error in first line\n");
  }
    
  /* post initial read from LW */
  if ((paperr = PAPRead(cno, rbuf, &rlen, &eof, &rcomp)) < 0) {
	fprintf(stderr,"PAPRead error %d\n",paperr);
  }
  tcomp = 1;			/* no data */
  fdlistener(fileno(stdin), dataready, &tcomp, 0);
  /* this is the main read/write loop */
  do {
    if (rcomp <= 0) {
      if (rcomp != noErr) {
	fprintf(stderr,"PAPRead error %d\n",rcomp);
	break;
      } else if (rlen > 0)
	(void)write(fileno(stdout), rbuf, rlen);
      if ((paperr = PAPRead(cno, rbuf, &rlen, &eof, &rcomp)) < 0) {
	fprintf(stderr,"PAPRead error %d\n",paperr);
	break;
      }
    }
    if (wcomp <= 0)
      if (wcomp != noErr) {
	fprintf(stderr,"PAPWrite error %d\n",wcomp);
        break;
     }
      else if (tcomp == noErr) {
	tcomp = 1;			/* no data */
	fdlistenresume(fileno(stdin)); /* can do here, because not until  */
				/* abSleep */
	/* should only read up to ready */
	err = read(fileno(stdin), buf, SBUFMAX);
	if (err <= 0)		/* eof */
	  break;
	paperr = PAPWrite(cno, buf, err, FALSE, &wcomp);
	if (paperr != noErr)
	  break;
      }
    abSleep(4, TRUE);		/* wait a bit */
  } while (err >= 0 );

  strcpy(buf, "quit\n");	/* toss ourselves into the  */
  if ((paperr = PAPWrite(cno, buf,sizeof("quit\n")-1, TRUE, &wcomp)) < 0) {
    printf("Error in first line\n");
  }
  while (!eof) {		/* wait for completion */
    if (rcomp <= 0) {
      if (rcomp != noErr)  {
	fprintf(stderr,"PAPRead error %d\n",rcomp);
	break;
      } else if (rlen > 0)
	(void)write(fileno(stdout),rbuf,rlen);
      if (eof) break;
      PAPRead(cno, rbuf, &rlen, &eof, &rcomp);
    }
    abSleep(4,TRUE);
  } 
  if (paperr != noErr)
    fprintf(stderr,"PAPWrite error %d\n",paperr);
  else
    do { abSleep(4, TRUE); } while (wcomp > 0);
}


pstatus(s)
byte *s;
{
  (void)write(1, s+1, *s);
  write(1, "\n", 1);		/* put out a cr */
}

/*
 * user sent interrupt - close down shop
*/
stopall()
{
  PAPClose(cno);
  exit(1);
}

#include <pwd.h>
char *
getusername()
{
  struct passwd *pw;
  static char buf[256+20];	/* enough for host + user */
  if (gethostname(buf, 255) < 0)
    strcpy(buf, "unknown host");
  strcat(buf, ":");
  if ((pw = getpwuid(getuid())) == NULL)
    strcat(buf, "unknown user");
  else
    strcat(buf, pw->pw_name);
  return(buf);
}

