/*
 *  Author: cck    Date: 88/05/19 13:11:35  
 *  Header: aufs.c,v 1.53 88/05/19 13:11:35 cck Rel  
 *  Revision: 1.53  
*/

/*
 * aufs - UNIX AppleTalk Unix File Server
 *
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  March 1987 	Schilit		Created.
 *
 */

char copyright[] = "Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the City of New York";

#include <stdio.h>
#include <sys/param.h>
#ifndef _TYPES
 /* assume included by param.h */
#include <sys/types.h>
#endif
#include <sys/file.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/ioctl.h>
#include <netinet/in.h>		/* for htons, etc. */
#include <signal.h>

#include <netat/appletalk.h>		/* include appletalk definitions */
#include <netat/compat.h>
#include <netat/afp.h>
#include "afps.h"			/* server includes */

#ifdef USETIMES
# include <time.h>
#endif

#ifndef NOWAIT3
# include <sys/wait.h>
#endif

#ifdef USESTRINGDOTH
# include <string.h>
#else
# include <strings.h>
#endif

#ifdef USEVPRINTF
# include <varargs.h>
#endif

#ifdef NOPGRP
# define NOSHUTDOWNCODE
#endif

/* known attention codes */
#define AFPSHUTDOWNTIME(x) (0x8000|((x)&0xfff))
#define AFPSHUTDOWNCANCEL (0x8fff)
#define AFPSHUTDOWNNOW (0x8000)

char *mytod();			/* return tod */

export int statflg = FALSE;	/* default is not to show stats */

private char *sysvolfile = NULL; /* system afpvols file */
private char *srvrname = NULL;
private char *passwdlookaside = NULL; /* local password file??? */
private char *guestid = NULL;	/* any guest ids? */
private char *coredir = NULL;	/* place to put coredumps */
export int mcs, qs;		/* maxcmdsize and quantum size */
export int sqs = atpMaxNum;	/* maximum send quantum */
export int n_rrpkts = atpMaxNum; /* maximum send quantum to allow remote */
				/* (used in spwrtcontinue) */
private int maxsess = 10;

private EntityName srvr_entity_name; /* our entity name */
private char zonetorun[34];	/* zone to run in if different than std. */
private char logfile[MAXPATHLEN]; /* log file name if any */
private int parent_pid;		/* pid of main server */
private int mypid;		/* pid of running process */
private int nomoresessions = FALSE; /* set true of out of asp sessions */
private int sesscount = 0;	/* number of asp sessions active */
private int cno = -1;		/* current connection */
#ifndef NOSHUTDOWNCODE
private int minutes_to_shutdown = -1;
#endif

/* if wait3 and usetimes isn't set, then we handle rusage from wait3 */
#ifndef NOWAIT3
# ifndef USETIMES
#  define DORUSAGE
# endif
#endif

/*
 * CNO TO PID handling
 *
 * Must keep a table to session reference numbers (aka connection
 * numbers) to pid mappings for the server since sessions are
 * "half"-closed.  This handling was previously in the asp protocol
 * handler, but this doesn't make sense and there is much better
 * control over things here
 *
 * internal strategy at this point is to record fork terminations
 * and handling via garbage collector at a later point.  maximum time
 * to scan is around 5 seconds at this point.  to minimize scan time
 * for gc, the "dead" ones are pushed onto a stack.
 *
 * an alternative strategy is to have the signal handler write to an
 * internal pipe watched by a fdlistener.  if this is done the sleeps
 * can be made much longer.  carefully handled this will work very
 * well, but it is a little ugly.  (note: best way to do is probably
 * to have the listener set a variable and the inferior termination
 * handler write the pids out.  the scan process would then pick up
 * the pids from the pipe.)
 *
*/

typedef struct cno_to_pid {
  int state;			/* back reference */
#define CP_NOTINUSE 0x1		/* to mark not in use */
#define CP_RUNNING 0x2		/* inferior is running? */
#define CP_TIMEDOUT 0x4		/* tickle timeout on inferior */
  int pid;			/* recorded pid */
  long timeval;			/* time when pid died */
#ifdef NOWAIT3
  int status;
#else
  union wait status;
#endif
#ifdef DORUSAGE
  struct rusage rusage;
#endif
} CTP, *CTPP;

private struct cno_to_pid *ctp_tab;
private int *ctp_stack;
private int ctp_stack_cnt;

usage(name)
char *name;
{
  char *DBLevelOpts();

  fprintf(stderr,"usage: %s [-d cap-flags] [-a afp-levels] ",name);
  fprintf(stderr,"[-n name] [-t packets] [-s] [-V afpvols]\n");
  fprintf(stderr,"\t-d for CAP debugging flags:\n");
  fprintf(stderr,"\t   l = lap, d = ddp, a = atp, n = nbp, p = pap,");
  fprintf(stderr,"i = ini, s = asp\n");
  fprintf(stderr,"\t-Ds[shct] for ASP debug limiting flags:\n");
  fprintf(stderr,"\t   s = socket, h = handlers, c = call, t = tickle\n");
  fprintf(stderr,"\t-a for AFP debugging by level (or setenv AUFSDEBUG):\n");
  fprintf(stderr,"\t   %s\n",DBLevelOpts());
  fprintf(stderr,"\t-t for packet traces (or setenv AUFSTRACE):\n");
  fprintf(stderr,"\t   [I|O|B]CmdName\n");
  fprintf(stderr,"\t-n for setting the server's name\n");
  fprintf(stderr,"\t-s for statistics\n");
  fprintf(stderr,"\t-V VolsFile for server wide afp volumes\n");
  fprintf(stderr,"\t-G <username> to set guest id for <anonymous> logins\n");
  fprintf(stderr,"\t-P LookAsidePasswordFile for scrambled transactions\n");
  fprintf(stderr,"\t-U <number> to allow <number> sessions\n");
  fprintf(stderr,"\t-c directory to specify a directory to coredump to\n");
  fprintf(stderr,"\t-l file to send logfile to other than <servername>.log\n");
  fprintf(stderr,"\t-S <n> limit responses to <n> packets\n");
  fprintf(stderr,"\t-R <n> limit remote to sending <n> packets\n");
  fprintf(stderr,"\nExample: %s -t 'bdelete irename' -a 'file fork dir' -s\n",
	  name);
  exit(1);
}

/*
 * generate default name from host name
 *
*/
char *
afs_default_name()
{
  char hostname[255];
  static char afsname[255];
  char *ap;

  gethostname(hostname,(int) sizeof(hostname));
  if ((ap = index(hostname,'.')) != NULL)
    *ap = '\0';				/* remove trailing domain name */
  sprintf(afsname,"%s Aufs",hostname);
  return(afsname);
}

doargs(argc,argv)
int argc;
char **argv;
{
  int c;
  extern char *optarg;
  extern int optind;
  
  while ((c = getopt(argc,argv,"a:d:D:n:N:t:sV:U:G:P:c:l:z:S:R:")) != EOF) {
    switch (c) {
    case 'z':
      strncpy(zonetorun, optarg, 32);
      break;
    case 'l':
      strncpy(logfile, optarg, sizeof(logfile)-1);
      break;
    case 'c':
      coredir = optarg;
      break;
    case 's':
      statflg = TRUE;
      break;
    case 'd':
      dbugarg(optarg);			/* '-d' is debug */
      break;
    case 'D':
      if (optarg[0] != 's')
	usage(argv[0]);
      aspdebug(optarg+1);		/* call asp debug */
      break;
    case 'a':
      if (!SetDBLevel(optarg))		/* -a for afp debug */
	usage(argv[0]);
      break;
    case 'n':
    case 'N':
      srvrname = optarg;		/* '-n' to set server name */
      break;
    case 't':
      if (!SetPktTrace(optarg))
	usage(argv[0]);
      break;
    case 'V':				/* system afpvols file */
      sysvolfile = optarg;
      break;
    case 'U':
      maxsess = atoi(optarg);
      break;
    case 'P':
      passwdlookaside = optarg;
      break;
    case 'G':
      guestid = optarg;
      break;
    case 'S':
      sqs = atoi(optarg);
      if (sqs <= 0) {
	fprintf(stderr, "Must have at least one packet in a response, resetting to one\n");
	sqs = 1;
      }
      if (sqs > atpMaxNum) {
	fprintf(stderr, "No more than %d packets allowed in a response\n",
		atpMaxNum);
	sqs = atpMaxNum;
      }
      break;
    case 'R':
      n_rrpkts = atoi(optarg);
      if (n_rrpkts <= 0) {
	fprintf(stderr, "Must have at least one packet in a response, resetting to one\n");
	n_rrpkts = 1;
      }
      if (n_rrpkts > atpMaxNum) {
	fprintf(stderr, "No more than %d packets allowed in a response\n",
		atpMaxNum);
	n_rrpkts = atpMaxNum;
      }
      break;
    default:
      usage(argv[0]);
      break;
    }
  }
}


main(argc,argv)
int argc;
char **argv;
{
  int inferiordone(), timedout(), dienow();
#ifndef NOSHUTDOWNCODE
  int killnow(), killin5(), diein5();
#endif
  int err,atpskt,slsref;
  AddrBlock addr;
  int comp,comp2;
  byte *srvinfo;
  int srvinfolen;
  import word this_net;
  import byte this_node;
  char *getenv(),*env;
  int pid;
  int mask;
  byte *buf;			/* [atpMaxData]; */
  byte *rspbuf;			/* [atpMaxData*atpMaxNum]; */
  import byte aufsicon[];	/* aufs icon */
  import int aufsiconsize;	/* and its size */
  import char *aufs_versiondate;
  import int aufs_version[];
  extern int errno;
  
  /* initial os dependent items first */
  OSEnable();			/* enable OS dependent items */

  IniServer();
  srvrname = afs_default_name();	/* set default server name */
  logfile[0] = '\0';
  zonetorun[0] = '\0';
  doargs(argc,argv);			/* handle command line */

  env = getenv("AUFSTRACE");		/* See if user wants to */
  if (env != NULL)			/*  trace some packets */
    SetPktTrace(env);
  env = getenv("AUFSDEBUG");
  if (env != NULL)
    SetDBLevel(env);

  if (!DBDEB)
    fprintf(stderr,"Apple Unix File Server (%s:%s@*) starting\n",
	    srvrname,AFSTYPE);

  /* here's the place to fork off */
  if (!DBDEB) {
    if (fork())
      _exit(0);
    {
      int f;
      for (f = 0; f < 10; f++)
	(void) close(f);
    }
    (void) open("/", 0);
#ifndef NODUP2
    (void) dup2(0, 1);
    (void) dup2(0, 2);
#else
    (void)dup(0);		/* for slot 1 */
    (void)dup(0);		/* for slot 2 */
#endif
#ifdef TIOCNOTTY
    {
      int t;
      t = open("/dev/tty", 2);	
      if (t >= 0) {
	ioctl(t, TIOCNOTTY, (char *)0);
	(void) close(t);
      }
    }
#endif    
  }
  
  mypid = parent_pid = getpid();	/* remember who we are */
  if (logfile[0] == '\0')
    sprintf(logfile, "%s.log", srvrname);
  log("****************************************");
  log("Apple Unix File Server (%s:%s@*) starting", srvrname, AFSTYPE);
  log("Aufs version: %d(%d) as of %s",aufs_version[0], aufs_version[1],
      aufs_versiondate);
  if (sysvolfile != NULL) {		/* if known system vols file */
    FILE *fd = fopen(sysvolfile, "r");

    if (fd == NULL)
      log("Aufs: no such system volumes file %s", sysvolfile);
    else if (!VRdVFile(fd))	/* then try to read it now */
      log("Aufs: system volumes file %s bad",sysvolfile);
  }
  if (zonetorun[0] != '\0')
    zoneset(zonetorun);
  abInit(TRUE);				/* initialize applebus */
  nbpInit();				/* initialize nbp */
  maxsess = aspInit(maxsess);	/* init asp */
  log("%d sessions allowed",maxsess);
  if ((ctp_tab = (CTPP)malloc(sizeof(struct cno_to_pid)*maxsess)) == NULL) {
    log("couldn't malloc table for pid recording, fatal!");
  }
  if ((ctp_stack = (int *)malloc(sizeof(int)*maxsess)) == NULL) {
    log("couldn't malloc stack for pid recording, fatal!");
  }
  ctp_stack_cnt = 0;
  { int i;
    for (i = 0 ; i < maxsess; i++) {
      ctp_tab[i].state = CP_NOTINUSE;
      ctp_tab[i].pid = -1;
    }
  }
  
  tellaboutos();		/* tell about os stuff */

  if (sqs < atpMaxNum)
    log("maximum of %d packet%s will be sent on a response", sqs,
	sqs > 1 ? "s" : "");
  sqs *= atpMaxData;
  if (n_rrpkts < atpMaxNum)
    log("remote limited to %d packet%s in a response", n_rrpkts,
	n_rrpkts > 1 ? "s" : "");
  SPGetParms(&mcs, &qs);
  if (DBDEB)
    printf("Command buffer size is %d, Quantum size is %d\n", mcs, qs);
  buf = (byte *)malloc(mcs);
  rspbuf = (byte *)malloc(qs);
  if (buf == NULL || rspbuf == NULL) {
    log("memory allocation failure!\n");
    exit(999);
  }

  addr.net = addr.node = addr.skt = 0;	/* use any */
  atpskt = 0;			/* make sure we use dynamic skt */
  err = ATPOpenSocket(&addr,&atpskt);
  if (err != noErr) {
    log("ATPOpenSocket failed with error %d\n",err);
    exit(0);
  }
  
  addr.net = this_net;
  addr.node = this_node;
  addr.skt = atpskt;

  if (SrvrRegister(atpskt,srvrname,AFSTYPE,"*", &srvr_entity_name) != noErr) {
    log("SrvrRegister for %s failed...",srvrname); 
    exit(2);
  }

  if (guestid != NULL)
    allowguestid(guestid);
  allowcleartext();
  if (passwdlookaside != NULL) 
    allowrandnum(passwdlookaside);


  if (coredir)
    if (chdir(coredir) < 0) {
      perror("chdir for coredumps");
      log("chdir to %s for coredumps failed",coredir);
    } else
      log("***CORE DUMPS WILL BE IN %s",coredir);
    
  /* Get server info once and stash away*/
  srvinfolen = GetSrvrInfo(rspbuf,srvrname,aufsicon,aufsiconsize);
  srvinfo = (byte *) malloc(srvinfolen);
  bcopy(rspbuf,srvinfo,srvinfolen);

  if (DBSRV)
    PrtSrvrInfo(srvinfo,srvinfolen);
  
  /* Init asp */
  err = SPInit(&addr,srvinfo,srvinfolen,&slsref);
  if (err != noErr) {
    log("SPInit failed with code %d, fatal",err);
    exit(0);
  }

  log("Aufs Starting (%s)",srvrname);
  if (sysvolfile)
    log("System vols in '%s'",sysvolfile);
  log("SPInit Completed.  Waiting for connection...");

#ifndef NOSHUTDOWNCODE
  setpgrp(0, parent_pid);	/* set our process group */
				/* (inherited) */
#endif

#ifndef DEBUGFORK
  if (!DBDEB)
#endif
    signal(SIGCHLD, inferiordone);
#ifndef NOSHUTDOWNCODE
  signal(SIGHUP, killnow);	/* kill -HUP -- Immediate shutdown */
  signal(SIGTERM, killin5);	/* kill -TERM -- Timed (5 min) shutdown */
#endif

  do {
    pid = -1;			/* make sure zero at start */
    SPGetSession(slsref,&cno,&comp);
    if (comp > 0)
      log("Waiting for session %d to activate", cno);
    /* won't wait if we set comp above */
    while (comp > 0) {
      abSleep(sectotick(5),TRUE);
      gcinferior();
    }
    if (comp == NoMoreSessions) {
      nomoresessions = TRUE;
      log("Woops, no more sessions");
      while (nomoresessions) {
	gcinferior();
	abSleep(sectotick(5), TRUE);
      }
      log("Okay, sessions should be available");
      continue;
    }
    if (comp != noErr) {
      log("GetSession returned %d on server socket %d",comp,slsref);
      continue;
    } else {
      sesscount++;
      log("New session %d started on server socket %d, count %d",
	  cno,slsref,sesscount);
      if ((err = SPGetNetworkInfo(cno, &addr)) != noErr) {
	log("Get Network info failed with error %d", err);
      } else {
	log("Session %d from [Network %d.%d, node %d, socket %d]",
	    cno,
	    nkipnetnumber(addr.net), nkipsubnetnumber(addr.net),
	    addr.node, addr.skt);
      }
    }
#ifndef DEBUGFORK
    if (!DBDEB) {
#endif
#ifndef NOSHUTDOWNCODE
      mask = sigblock(sigmask(SIGCHLD)|sigmask(SIGHUP)|sigmask(SIGTERM));
#else
      mask = sigblock(sigmask(SIGCHLD)|sigmask(SIGHUP));
#endif
      /* fork on connection - only tickle from parent */
      if ((pid = SPFork(cno, TRUE, FALSE)) < 0) {
	log("SPFork failed on session %d, last system error %d",cno, errno);
	/* try to close, but don't worry too much */
	SPCloseSession(cno, 1, 1, &comp2);
	sigsetmask(mask);
	continue;
      }
      if (pid) {
	SPTickleUserRoutine(cno, timedout, pid);
	log("pid %d starting for session %d",pid, cno);
	addinferior(cno, pid);	/* addinferior scans (phew) */
      } else {
#ifndef NOSHUTDOWNCODE
	alarm(0);		/* make sure off */
#endif
	nbpShutdown();		/* don't need this in inferior */
	signal(SIGCHLD, SIG_DFL);
#ifndef NOSHUTDOWNCODE
	signal(SIGTERM, diein5); /* die in 5 minutes */
#endif
	signal(SIGHUP, dienow);	/* superior signaled us to shutdown */
	mypid = getpid();
#ifndef NOSHUTDOWNCODE
	setpgrp(0, parent_pid);	/* set our process group */
	dying();		/* are we dying? if so, handle it*/
#endif
      }
      sigsetmask(mask);
#ifndef DEBUGFORK
    } else pid = 0;
#endif
  } while (pid != 0);		/* pid = 0 implies inferior process */

  if (pid == 0)
    inferior_handler(buf, rspbuf);

  if (statflg)
    SrvrPrintStats();			/* print stats */
  if (mypid == parent_pid)
    if ((err = SrvrShutdown(&srvr_entity_name)) != noErr)
      log("NBPRemove failed: code %d\n", err);
  exit(0);
}

inferior_handler(buf, rspbuf)
byte *buf;
byte *rspbuf;
{
  int mask;
  OSErr err;
  int comp;
  int type,rlen,rsplen;
  ReqRefNumType reqref;

  umask(0);			/* file creates have explict modes */
  for (;;) {
    SPGetRequest(cno,buf,mcs,&reqref,&type,&rlen,&comp);
    while (comp > 0) { abSleep(sectotick(60),TRUE); }
    if (comp == SessClosed || comp == ParamErr) {
      log("Session (%d) closed",cno);
      return;
    }
    if (comp < 0) {
      log("SPGetRequest failed %d",comp);
      continue;
    }
    if (rlen == 0)
      continue;
#ifndef NOSHUTDOWNCODE
    /* mask off potential race condition */
    mask = sigblock(sigmask(SIGTERM)|sigmask(SIGALRM));
#endif
    switch (type) {
    case aspWrite:
    case aspCommand:
      err = SrvrDispatch(buf,rlen,rspbuf,&rsplen,cno,reqref);
      if (DBSRV) {
	printf("Sending reply len=%d err=%s ...",rsplen,afperr(err));
	fflush(stdout);			/* force out */
      }
      if (type == aspWrite)
	SPWrtReply(cno,reqref,(dword) err,rspbuf,rsplen,&comp);
      else
	SPCmdReply(cno,reqref,(dword) err,rspbuf,rsplen,&comp);
      while (comp > 0) { abSleep(sectotick(60),TRUE); }
      if (DBSRV)
	printf("done\n");
      break;
    case aspCloseSession:
      log("Closing ASP Session...");
      SPCloseSession(cno,10,3,&comp); /* 5 times, .75 seconds */
      while (comp > 0)
	abSleep(1, TRUE);
      sigsetmask(mask);
      return;
    default:
      log("Unknown asp command type = %d",type);
      break;
    }
#ifndef NOSHUTDOWNCODE
    sigsetmask(mask);
#endif
  }
}

/*
 * Deals with inferior process termination - just close off the
 * "half closed" socket
 *
*/
inferiordone()
{
#ifndef NOWAIT3
  union wait status;
#else
  int status;
#endif
#ifdef DORUSAGE
  struct rusage rusage;
# define RUSAGEVAR &rusage
#else
# define RUSAGEVAR 0		/* may not be used, but.. */
#endif
  int pid;
  int i;
  struct cno_to_pid *cp;

#ifndef NOWAIT3
# define DOWAIT while ((pid=wait3(&status, WNOHANG, RUSAGEVAR)) > 0) 
#else
# define DOWAIT  if ((pid=wait(&status)) > 0)
#endif
  DOWAIT {
    /* remember for later */
    for (i = 0, cp = ctp_tab; i < maxsess; i++, cp++) {
      if (cp->pid == pid && (cp->state & CP_NOTINUSE) == 0) {
	/* one of alive, dead or timedout */
	/* if alive, move to dead */
	/* if dead, shouldn't be here */
	/* if timedout, then leave state */
	if ((cp->state & CP_RUNNING) == 0)
	  log("Internal error: pid %d has died twice according to wait",pid);
	cp->state &= ~CP_RUNNING; /* not running anymore */
	(void)time(&cp->timeval); /* log time */
	bcopy(&status, &cp->status, sizeof(status)); /* copy status */
#ifdef DORUSAGE
	bcopy(&rusage, &cp->rusage, sizeof(rusage));
#endif
	ctp_stack[ctp_stack_cnt++] = i;	/* mark cno */
	log("Recorded terminated inferior Aufs PID %d", pid);
	break;
      }
    }
    if (i == maxsess)
      log("Unknown terminating inferior pid %d ignored", pid);
  }
  signal(SIGCHLD, inferiordone);
}

/*
 * scan for dead inferiors and handle gracefully.  Know we are never
 * called from a "bad" context.  e.g. we won't be called while in a
 * "critical" section where data structures are being updated
 *
*/
gcinferior()
{
  char tmpbuf[30];		/* reasonable */
  int srn, comp;
  struct cno_to_pid *cp;
  int mask;

  if (ctp_stack_cnt <= 0) {	/* stack of died pids empty? */
    if (ctp_stack_cnt < 0)
      log("internal error: unsafe condition: ctp stack count less than zero");
    return;			/* yes, just return */
  }

  mask = sigblock(sigmask(SIGCHLD));
  do {
    srn = ctp_stack[--ctp_stack_cnt]; /* get pid */
    cp = &ctp_tab[srn];		/* pointer to info on died pid */
    if (cp->state & CP_NOTINUSE) /* nothing to do */
      continue;
    /* fork termination has three cases: */
    /* [?,0177] - stopped */
    /* [?, 0] - exit status */
    /* [0, ?] - terminated due to signal */
    if (cp->state & CP_TIMEDOUT) {
      log("process %d, session %d was terminated due to a timeout",
	  cp->pid, srn);
    } else if (WIFSTOPPED(cp->status)) {
      log("process %d, session %d was suspended! gads what is happening?",
	  cp->pid, srn);
    } else if (WIFSIGNALED(cp->status)) {
      SPAttention(srn, AFPSHUTDOWNNOW, 1, -1, &comp);
      while (comp > 0) {abSleep(30, TRUE);} /* ignore error */
      SPCloseSession(srn, 3, 2, &comp); /* try 3 times every .5 seconds */
      while (comp > 0) { abSleep(30, TRUE); } /* close down if we can */
      log("process %d, session %d was terminated on signal %d",
	  cp->pid, srn, W_TERMSIG(cp->status));
      if (W_COREDUMP(cp->status)) {
	log("woops: we just dumped core on pid %d", cp->pid);
	sprintf(tmpbuf, "core%d",cp->pid);
	if (link("core", tmpbuf) == 0) { /* making copy */
	  if (unlink("core") != 0)
	    log("woops: couldn't unlink core for pid %d", cp->pid);
	  log("core dump for pid %d is in %s",cp->pid, tmpbuf);
	} else
	  log("core dump for pid %d is in core - plz be careful though!",
	      cp->pid);
      }
    } else {
      log("process %d, session %d terminated with exit code %d",
	  cp->pid, srn, W_RETCODE(cp->status));
    }
    SPShutdown(srn);
    nomoresessions = FALSE;	/* if this was set, unset now */
#ifdef DORUSAGE
    log("%d messages out, %d in, CPU %.2f user %.2f system",
	cp->rusage.ru_msgsnd,cp->rusage.ru_msgrcv,
	((float)cp->rusage.ru_utime.tv_sec)+
	((float)cp->rusage.ru_utime.tv_usec)/1000000.0,
	((float)cp->rusage.ru_stime.tv_sec)+
	((float)cp->rusage.ru_stime.tv_usec)/1000000.0);
#endif
    log("Process %d terminated at %s",cp->pid,
	mytod(cp->timeval));
    cp->state = CP_NOTINUSE;
    cp->pid = -1;		/* make -1 to speed up sigchld handler */
  } while (ctp_stack_cnt);
  sigsetmask(mask);		/* restore mask */
}

/*
 *
 * record inferior pid for later handling
 *
 * must be called with sigchild and other signals,etc. that could
 * affect ctp_tab off. 
 * 
 *
*/
addinferior(cno, pid)
int cno;
int pid;
{
  struct cno_to_pid *cp;

  /* need to scan here in case something timed out */
  gcinferior();
  cp = &ctp_tab[cno];		/* get pointer to table entry */
  /* If was in table, just smash because we have a new pid on cno */
  /* should we scan table for duplicates? */
  cp->state = CP_RUNNING;
  cp->pid = pid;
}

/*
 * Connection timed because remote didn't tickle us enough
 * Kill inferior and shutdown half closed skt.
 *
 * Note: called from abSleep scheduler.
 *
*/
timedout(srn, pid)
int srn;
int pid;
{
  nomoresessions = FALSE;	/* if this was set, unset now */
  log("Server timeout on session %d pid %d, not talking to remote anymore",
      srn, pid);
  /* shouldn't need to do anymore here since remote stopped talking */
  /* assume sigchild interlocked here */
  if (ctp_tab[srn].state & CP_RUNNING)
    ctp_tab[srn].state |= CP_TIMEDOUT;
  SPShutdown(srn);		/* ignore errors */
  kill(pid, SIGHUP);		/* hangup inferior */
}

/* got a hup and are inferior of server */
dienow()
{
  int comp;

  log("Superior told us to shutdown - probably tickle timeout");
  /* The following shouldn't really do anything since remote should be gone */
  /* be in case it really isn't, let's go through this rigamorle */
  /* Tell remote we are shutting down */
  SPAttention(cno, AFPSHUTDOWNNOW, 1, -1, &comp);
  while (comp > 0) {abSleep(30, TRUE);} /* ignore error */
  /* Try closing just in case */
  SPCloseSession(cno, 3, 2, &comp); /* 3 times, .5 seconds */
  while (comp > 0) { abSleep(30, TRUE); } /* close down if we can */
  exit(0);
}

#ifndef NOSHUTDOWNCODE

/*
 * inferior handler: setup and handle: terminate in minutes_to_shutdown
 *
*/
dying()
{
  int comp;
  int dying();

  if (minutes_to_shutdown < 0)		/* not in die mode */
    return;
  if (!minutes_to_shutdown)
    dienow();
  signal(SIGALRM, dying);
  /* Tell remote we are shutting down */
  if (minutes_to_shutdown % 2) {		/* all odd minutes */
    /* there is a potential race condition here */
    SPAttention(cno, AFPSHUTDOWNTIME(minutes_to_shutdown), 1, -1, &comp);
    while (comp > 0) {abSleep(30, TRUE);} /* ignore error */
  }
  minutes_to_shutdown--;
  alarm(60);
}

/*
 * inferior handler: setup and handle: terminate in 5 minutes 
 *
*/
diein5()
{
  int dying();

  if (minutes_to_shutdown >= 0)		/* already in shutdown mode */
    return;
  log("Superior told us to shutdown by time -- initiating 5 minute shutdown");
  minutes_to_shutdown = 5;
  dying();			/* start */
}

/*
 * Call when the master process receives a SIGHUP -- immediate shutdown
 *
 */
killnow()
{
  OSErr err;

  signal (SIGHUP, SIG_IGN);
  log("Parent received SIGHUP -- immediate shutdown");
  killpg (parent_pid, SIGHUP);
  if ((err = SrvrShutdown(&srvr_entity_name)) != noErr)
    log("NBPRemove failed: code %d\n", err);
  exit(0);
}

/*
 * Called with the master process receives a SIGTERM
 */
killin5()
{
  int killinn();

  signal (SIGTERM, SIG_IGN);
  log("Shutdown by time -- initiating 5 minute shutdown");
  killpg (parent_pid, SIGTERM);
  minutes_to_shutdown = 4;
  /* in case children get blocked up */
  signal(SIGALRM, killinn);
  alarm(68);			/* a litte more than a minute */
}

killinn()
{
  int killinn();

  if (minutes_to_shutdown < 0)		/* not in die mode */
    return;
  if (!minutes_to_shutdown)
    killnow();
  killpg (parent_pid, SIGTERM);	/* in case inferior was blocked up */
  signal(SIGALRM, killinn);
  minutes_to_shutdown--;
  alarm(60);
}


#endif /* NOSHUTDOWNCODE */

/*
 * log an error message 
 */
#ifndef USEVPRINTF
/* Bletch - gotta do it because pyramids don't work the other way */
/* (using _doprnt and &args) and don't have vprintf */
/* of course, there will be something that is just one arg larger :-) */
/*VARARGS1*/
log(fmt, a1,a2,a3,a4,a5,a6,a7,a8,a9,aa,ab,ac,ad,ae,af)
char *fmt;
#else /* USEVPRINTF */
log(va_alist)
va_dcl
#endif /* USEVPRINTF */
{
  static FILE *fp = NULL;
#ifdef USEVPRINTF
  register char *fmt;
  va_list args;
#endif

  if (fp == NULL)
    if (DBDEB)
      fp = stderr;
    else
      if ((fp = fopen(logfile, "a+")) == NULL) 
	return;
  
  if (mypid != parent_pid)
    fprintf(fp, "%05d: ", mypid);
  else
    fprintf(fp, "%05d* ",mypid);
  tmprt(fp);
#ifdef USEVPRINTF
  va_start(args);
  fmt = va_arg(args, char *);
  vfprintf(fp, fmt, args);
  va_end(args);
#else /* USEVPRINTF */
  fprintf(fp, fmt,  a1,a2,a3,a4,a5,a6,a7,a8,a9,aa,ab,ac,ad,ae,af);
#endif /* USEVPRINTF */
  putc('\n', fp);
  fflush(fp);
}

tmprt(fp)
FILE *fp;
{
  fprintf(fp, "%s", mytod(0L));
}

/*
 * return tod in a static buffer, rotate among <n> buffers to
 * allow at least <n> calls "uses" to be active at a time
 *
 * <n> is currently 2
 *
*/
char *
mytod(ptime)
long ptime;
{
  long tloc;
  struct tm *tm, *localtime();
#define NTODBUF 2
  char * buf;
  static char buffers[NTODBUF][100];
  static int idx = 0;

  if (ptime == 0L)
    (void)time(&tloc);
  else
    tloc = ptime;
  tm = localtime(&tloc);
  buf = buffers[idx];
  ++idx;			/* move to next */
  idx %= NTODBUF;		/* make sure in range */
  if (tm->tm_year > 99)
    sprintf(buf, "%02d:%02d:%02d %02d/%02d/%04d ",
	    tm->tm_hour, tm->tm_min, tm->tm_sec,
	    tm->tm_mon+1, tm->tm_mday, tm->tm_year+1900);
  else
    sprintf(buf, "%02d:%02d:%02d %02d/%02d/%02d ",
	    tm->tm_hour, tm->tm_min, tm->tm_sec,
	    tm->tm_mon+1, tm->tm_mday, tm->tm_year);
  return(buf);
}


