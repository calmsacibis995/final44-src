static char rcsid[] = " Author: cck    Date: 88/03/20 16:49:26  ";
static char rcsident[] = " Header: lwsrv.c,v 1.16 88/03/20 16:49:26 cck Rel  ";
static char revision[] = " Revision: 1.16  ";

/*
 * lwsrv - UNIX AppleTalk spooling program: act as a laserwriter
 *  driver: handles setup and farms out incoming jobs
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  Feb  15, 1987	Schilit		Created, based on lsrv
 *  Mar  17, 1987	Schilit		Fixed nonprintables, added -r
 *  May  15, 1987	CCKim		Add support for LaserPrep 4.0
 *					Make multifork by default (turn
 *					off by defining SINGLEFORK)
 *
 */

char copyright[] = "Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the City of New York";

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <signal.h>
#include <sys/param.h>
#ifndef _TYPES
# include <sys/types.h>			/* assume included by param.h */
#endif
#include <sys/file.h>
#include <sys/ioctl.h>
#include <sys/dir.h>
#include <sys/stat.h>

#include <netat/appletalk.h>		/* include appletalk definitions */
#include <netat/compat.h>
#ifdef USESTRINGDOTH
# include <string.h>
#else
# include <strings.h>
#endif
#ifndef NOWAIT3
# include <sys/wait.h>
#endif
#ifdef NEEDFCNTLDOTH
# include <fcntl.h>
#endif
#include "papstream.h"

private char *tracefile = NULL;
private char *fontfile = NULL;
private char *logfile = NULL;
private char *prtname = NULL;
private char *unixpname = NULL;
private char *prttype = "LaserWriter";
private char *dictdir = ".";	/* assume local dir */
private int rflag = FALSE;		/* retain print file */
private int hflag = TRUE;	/* default to print banner */
private int singlefork = FALSE;
export PAPStatusRec statbuff;			/* status buffer */

private char username[80],jobname[80];


#ifndef TEMPFILE
# define TEMPFILE "/tmp/lwsrvXXXXXX"	/* temporary file holds job */
#endif

#define RFLOWQ atpMaxNum
#define BUFMAX (PAPSegSize*RFLOWQ)+10

private void
usage(s,err) 
char *s,*err;
{
  if (err != NULL)
    fprintf(stderr,"%s: %s\n",s,err);
  fprintf(stderr,"usage: %s -n <PrinterName> -p <unix printer name>\n",s);
  fprintf(stderr,"usage:\t\t-a <DictionaryDirectory> -f <FontFile>\n");
  fprintf(stderr,"usage:\t\t[-l <LogFile>] [-t <TraceFile>] [-r] [-h]\n");
  fprintf(stderr,"usage:\t\t[-T crtolf] [-T quote8bit]\n\n");
  fprintf(stderr,"\t-p*<unix printer name> is the unix printer to print to\n");
  fprintf(stderr,"\t-n*<PrinterName> specifies the name lwsrv registers.\n");
  fprintf(stderr,"\t-a*<DictionaryDirectory> is the ProcSet directory.\n");
  fprintf(stderr,"\t-f*<FontFile> contains an font coordination list.\n");
  fprintf(stderr,"\t-t <Tracefile> stores session and appledict in\n");
  fprintf(stderr,"\t   <Tracefile> without printing.\n");
  fprintf(stderr,"\t-l <LogFile> specifies a file to log the lwsrv session\n");
  fprintf(stderr,"\t-e Allow an eexec to occur in a procset\n");
  fprintf(stderr,"     warning: this may cause problems, use carefully\n");
  fprintf(stderr,"\t-r Will retain temp print file for inspection\n");
  fprintf(stderr,"\t-h means to print without a banner page\n");
  if (is_simple_dsc()) 
    fprintf(stderr,"\t-A [on*|off] means to turn on or off Adobe document\n");
  else
    fprintf(stderr,"\t-A [on|off*] means to turn on or off Adobe document\n");
  fprintf(stderr,"\tstructuring revision 2 compatibility\n");
  fprintf(stderr,"\t(this can cause problems, *'ed item is default)\n");
  fprintf(stderr,"\t-S single lwsrv fork (default is multiforking)\n");
  fprintf(stderr,"\t-T Transcript compatibilty options\n");
  fprintf(stderr,"\t-T crtolf: translate cr to lf for Transcript filters\n");
  fprintf(stderr,"\t-T quote8bit: quote 8 bit chars for Transcript\n");
  fprintf(stderr,"\t-T makenondscconformant: make non DSC conformant: use\n");
  fprintf(stderr,"\t   if psrv only works with DSC 1.0 conventions\n");
  fprintf(stderr,"\nexample: %s -n Laser -p ps -a/usr/lib/ADicts\n",s);
  fprintf(stderr,"\t\t-f /usr/lib/LW+Fonts\n");
  fprintf(stderr,"\t(note the starred items above are required)\n");
  exit(0);
}

private void
doargs(argc,argv)
int argc;
char **argv;
{
  int c;
  extern char *optarg;
  extern int optind;
  
  while ((c = getopt(argc,argv,"a:f:l:p:P:t:d:n:rehT:A:S")) != EOF) {
    switch (c) {
    case 'a':
      if (index(optarg, '/') == NULL) {
	dictdir = (char *)malloc(strlen(optarg)+4);
	strcpy(dictdir, "./");
	strcat(dictdir, optarg);
      } else 
	dictdir = optarg;	/* remember dictionary directory */
      break;
    case 'd':
      dbugarg(optarg);
      break;
    case 'f':
      fontfile = optarg;		/* -f fontfile */
      break;
    case 'l':				/* -l logfile */
      logfile = optarg;
      break;
    case 'n':				/* lwsrv printer name */
      prtname = optarg;
      break;
    case 'p':				/* -p unix printer name */
    case 'P':
      unixpname = optarg;
      break;
    case 'h':
      hflag = FALSE;		/* do not print banner */
      break;
    case 'r':				/* do not remove file */
      rflag = TRUE;
      break;
    case 't':				/* -t tracefile */
      tracefile = optarg;
      break;
    case 'e':
      setflag_encrypted_instream(TRUE);	/* maybe "eexec" in code */
      break;
    case 'T':
      if (simple_TranscriptOption(optarg) < 0)
	usage(argv[0], NULL);
      break;
    case 'A':
      if (simple_dsc_option(optarg) < 0)
	usage(argv[0], NULL);
      break;
    case 'S':
      singlefork = TRUE;
      fprintf(stderr, "lwsrv: single fork\n");
      break;
    case '?':				/* illegal character */
      usage(argv[0],NULL);		/* usage and exit */
      break;
    }
  }

  if (unixpname == NULL)
    usage(argv[0],"No Unix Printer Name");
  if (prtname == NULL)
    usage(argv[0],"No AppleTalk Printer Name");
  if (fontfile == NULL)
    usage(argv[0],"No FontFile specified");    
}


private
childdone()
{
#ifndef NOWAIT3
  union wait status;
  while (wait3(&status, WNOHANG, 0) > 0) ;
  signal(SIGCHLD, childdone);
#else
  int status;
  (void)wait(&status);
  signal(SIGCHLD, childdone);
#endif /* NOWAIT3 */
}

main(argc,argv)
int argc;
char **argv;
{
  char buf[100];
  int err,i,cno;
  int rcomp;
  int srefnum;
  int childdone();

  doargs(argc,argv);			/* handle args */
  

  if (!dbug.db_flgs) {			/* disassociate */
    if (fork())
      exit(0);				/* kill off parent */
    for (i=0; i < 20; i++)
      close(i);				/* close all files */
    (void) open("/dev/null",0);
#ifndef NODUP2
    (void) dup2(0,1);
#else
    (void)dup(0);		/* for slot 1 */
#endif
    if (logfile == NULL) {
#ifndef NODUP2
      (void) dup2(0,2);
#else
      (void) dup(0);		/* for slot 2 */
#endif
    } else {
      if ((i = open(logfile,O_WRONLY|O_APPEND)) < 0)
	i = creat(logfile,0666);
      if (i != 2) {
#ifndef NODUP2
	(void) dup2(i,2);
#else
	close(2);		/* try again */
	(void) dup(0);		/* for slot 2 */
#endif
	(void) close(i);
      }
    }
#ifdef TIOCNOTTY
    if ((i = open("/dev/tty",2)) > 0) {
      ioctl(i, TIOCNOTTY,(char *) 0);
      close(i);
    }
#endif
  }

/*  dbug.db_pap = TRUE; */
  
  abInit(FALSE);		/* initialize appletalk driver */
  nbpInit();
  PAPInit();			/* init PAP printer routines */

  fprintf(stderr,"lwsrv: Spooler starting for %s.%s.*\n",prtname,prttype);
  if (!spool_setup(tracefile, fontfile, prtname, dictdir)) {
    usage(argv[0]);
    exit(1);
  }
  sprintf(buf,"%s:%s@*",prtname,prttype);

  cpyc2pstr(statbuff.StatusStr,"status: idle");
  err = SLInit(&srefnum, buf, 8, &statbuff);
  if (err != noErr) {
    fprintf(stderr,"lwsrv: SLInit failed: %d\n",err);
    exit(1);
  }

  if (!singlefork)
    signal(SIGCHLD, childdone);
  while (TRUE) {
    NewStatus("idle");
    err = GetNextJob(srefnum, &cno, &rcomp);
    if (err != noErr) {
      fprintf(stderr,"lwsrv: GetNextJob failed: %d\n",err);
      exit(1);
    }
    while (rcomp > 0)
      abSleep(20,TRUE);
    fprintf(stderr,"lwsrv: Starting print job for %s\n",prtname);
    if (!singlefork) {
      if (fork() != 0) {
	PAPShutdown(cno);	/* kill off connection */
	continue;
      }
      SLClose(srefnum);		/* close server for child */
      nbpShutdown();		/* shutdown nbp for child */
    } else NewStatus("busy, processing job");
    /* need for multi-forking, nice for single forking */
    /* handle the connection in cno */
    childjob(p_opn(cno, BUFMAX)); 
    if (!singlefork)
      exit(0);
  }
}

export
childjob(pf)
PFILE *pf;
{
  long t;
  char tname[100],status[80];
  char buf[256];
  FILE *outfile;
  
  jobname[0] = username[0] = '\0';

  if (tracefile != NULL)		/* is this a trace? */
    strcpy(tname,tracefile);		/* yes... then output is tracefile */
  else {				/* otherwise use a temp file */
    strcpy(tname,TEMPFILE);
    mktemp(tname);
  }
  
  if ((outfile = fopen(tname, "w+")) == NULL) {
    perror(tname);
  }

  if (singlefork)
    NewStatus("initializing");
  sprintf(status,"receiving job for %s",prtname);

  scandicts(dictdir);

  while (getjob(pf,outfile)) {	/* while still open... */
    if (singlefork)
      NewStatus(status);
    /* don't send out real eof - causes real problems */
    /* given that we are prepending procsets */
    fprintf(outfile,"%% *EOF*\n");
  }

  fclose(outfile);

  (void) time(&t);

  if (tracefile != NULL)
    fprintf(stderr,"lwsrv: Tracing to file: %s; job %s; user %s; on %s\n",
	    tracefile,jobname,username,ctime(&t));
  else {
    if (rflag)
      fprintf(stderr,"lwsrv: Preserving file in %s\n",tname);
    fprintf(stderr,"lwsrv: Printing job: %s; user %s; on %s\n",
	    jobname,username,ctime(&t));
    sprintf(buf,"/usr/ucb/lpr -P%s %s %s -J 'MacUser: %s' %s\n",
	    unixpname,rflag ? "" : "-r",hflag ? "" : "-h", username,tname);
    system(buf);
  }
  p_cls(pf);				/* close out the pap connection */
}

export void
setjobname(ts)
char *ts;
{
  strcpy(username, ts);
}

setusername(ts)
char *ts;
{
  strcpy(username, ts);
}

export
NewStatus(status)
char *status;
{
  char tmp[255];

  if (*username != '\0')
    sprintf(tmp,"job: %s for %s; status: %s",
	    jobname,username,status);
  else
    sprintf(tmp,"status: %s",status);
  cpyc2pstr(statbuff.StatusStr, tmp);
  abSleep(0,TRUE);			/* make sure protocol runs */
}
