static char rcsid[] = " Author: cck    Date: 88/03/30 11:59:56  ";
static char rcsident[] = " Header: papif.c,v 1.68 88/03/30 11:59:56 cck Rel  ";
static char revision[] = " Revision: 1.68  ";

/*
 * papif - UNIX AppleTalk test program: simple line printer input filter 
 *  for LaserWriter
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  June 29, 1986    Schilit&CCKim	Created.
 *  July  5, 1986    CCKim		Clean up
 *  Aug  20, 1986    CCKim, Gave up on old version, use lwpr routines instead.
 *  Nov      1986    croft, restart after "status: idle", call pstext
 *
 */

char copyright[] = "Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the City of New York";

#include <stdio.h>
#include <ctype.h>
#include <sys/param.h>
#ifndef _TYPES
# include <sys/types.h>		/* in case param doesn't */
#endif
#include <sys/file.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <signal.h>

#include <netat/appletalk.h>		/* include appletalk definitions */
#include <netat/compat.h>
#ifndef NOWAIT3
# include <sys/wait.h>
#endif
#ifdef USESTRINGDOTH
# include <string.h>
#else
# include <strings.h>
#endif
#ifdef NEEDFCNTLDOTH
# include <fcntl.h>
#endif
#ifdef USEVPRINTF
# include <varargs.h>
#endif

#ifdef SYSLOG
#include <syslog.h>
#endif

/* Configuration options */

#ifndef CAPPRINTERS
# define CAPPRINTERS "/etc/cap.printers"
#endif

/*
 * status watch time: minimum time to wait before doing next status
 * watch 
*/
#ifndef WATCHTIME
# define WATCHTIME 10		/* status watch every 10 seconds */
#endif

/* PAP defines */
#ifndef RFLOWQ			/* default read flow quantum to use */
# define RFLOWQ atpMaxNum
#endif
#ifndef SFLOWQ			/* default send flow quantum to use */
# define SFLOWQ atpMaxNum
#endif
#define MAX_RFLOWQ atpMaxNum	/* maximum read flow quantum */
#define MAX_SFLOWQ atpMaxNum	/* maximum send flow quantum */

/* buffers sizes for papread/writes - based on maximum flow quantum */
#define R_BUFMAX PAPSegSize*MAX_RFLOWQ
#define S_BUFMAX PAPSegSize*MAX_SFLOWQ

/* default for debugging output or not */
#ifndef DEBUG
# define DEBUG 0		/* no */
#endif

/* are we running with Adobe Document Structuring parsing? */  
/* for now, do we look for %%EOF in input and send an EOF to remote */
/* based on this */
#ifndef NO_STRUCT
# define NO_STRUCT 0		/* yes */
#endif

/* default to doing accounting? */
#ifndef NOACCT
# define NOACCT 0		/* yes, do it */
#endif

/* default to stripping out ^Ds? */
#ifndef STRIPCONTROLD
# define STRIPCONTROLD 0	/* no */
#endif

/* default to mapping ^M to ^J for psrv, etc. */
#ifndef MAPCRTOLF
# define MAPCRTOLF 0		/* no */
#endif

/* default to idle check? */
#ifndef IDLESTUFF
# define IDLESTUFF 0		/* no */
#endif

/* default to charge banner? */
#ifndef CHARGEBANNER
# define CHARGEBANNER 0		/* no */
#endif

#ifndef ATPRESPONSETIMEOUT
# define ATPRESPONSETIMEOUT sectotick(60*2);
#endif

/* Transcript compatibility section */

/* allow psmagic */
/* use pstext? */
#ifndef PSTEXT
# define PSTEXT NULL		/* no */
#endif
/* use psreverse */
#ifndef PSREVERSE
# define PSREVERSE NULL		/* no */
#endif
/* need to check magic */
#ifndef PSMAGIC
# define PSMAGIC 0		/* no */
#endif

/* default to putting banner first? */
#ifndef BANNERFIRST
# define BANNERFIRST 0		/* no */
#endif

/* default to putting banner last? */
#ifndef BANNERLAST
# define BANNERLAST 0		/* no */
#endif

#ifndef BANNER
# define BANNER ".banner"
#endif


/*
 * GLOBAL VARIABLES
*/
int cno;			/* pap connection number */
int pid = -1;			/* top fork's pid */
/* don't know where I got 30 from */
char host[30];			/* host name */
char printer[30];		/* printer name */
char user[30];			/* user name */

char *lwname;			/* entity name */

/* for pap */
int rflowq = RFLOWQ;		/* flow quatum on local reads */
int sflowq = SFLOWQ;		/* flow q on remote reads (local writes) */
int r_bufsiz;			/* flow quantum translated to buffers size */
int s_bufsiz;

int debug = DEBUG;		/* debugging output? */
char *capprinters = CAPPRINTERS; /* location of cap.printers */
char *bannerfile = BANNER;	/* banner file name */
int watchtime = WATCHTIME;	/* status watch time */
int dostruct = !NO_STRUCT;	/* parse adobe structuring? */
int doacct = !NOACCT;		/* do accounting? */
int doidlestuff = IDLESTUFF;	/* handle idle watch? */
int chargebanner = CHARGEBANNER; /* charge user for banner pages? */
u_long atpresponsetimeout = ATPRESPONSETIMEOUT;	/* atp resp. cache timeout */
int strip_control_d = STRIPCONTROLD;
int map_crtolf = MAPCRTOLF;

/* Transcript compatiblity */
int neverreverse = FALSE;	/* never page reverse */
int verboselog = TRUE;		/* default */
char *pstext = PSTEXT;		/* pstext location */
char *psreverse = PSREVERSE;	/* psrv location */
int psmagic = PSMAGIC;		/* will be reset if necessary by initenv */
int bannerfirst = BANNERFIRST;	/* banner comes first? */
int bannerlast = BANNERLAST;	/* banner comes last? */

/* declarations */
char *ptime();

/* Definitions */

/* yes or no depending on the value */
#define boolvalstr(value) ((value) ? "yes" : "no")
/* string value if not null, "none" o.w. */
#define strval(str) (((str) == NULL) ? "none" : (str))

#ifndef SYSLOG
/* logging levels */
#define log_i dolog /* information */
#define log_w dolog /* warning */
#define log_e dolog /* error */
#define log_r dolog /* return from remote */
#define log_d dolog /* log debugging */
#endif

/*
 * LPD Error tokens - what to return from exit
 */
#define	lpd_OK		0	/* all is well? */
#define	lpd_REPRINT	1	/* forces a reprint */
#define lpd_ERRORS	2	/* printed with errors */

/* quit gets called when we've been killed by lprm via SIGINT */
quit()
{
  if (cno >= 0)
    PAPClose(cno);
#ifndef SYSLOG
  log_w("papif: Aborted job at %s\n",ptime());
#else
  syslog(LOG_WARNING, "Aborted job");
#endif
  exit(lpd_OK);
}

/*
 * return true: if s is "y"* or "on"* or s is a non-zero number (string)
 * return false: o.w.
 *
*/
int
getbval(s)
char *s;
{
  if (isdigit(s[0]))
    return(atoi(s));
  if (s[0] == 'y' || (s[0] == 'o' && s[1] == 'n'))
    return(TRUE);
  return(FALSE);
}

/*
 * get environment variables set by Transcript and set on that basis
 * 
*/
initenv()
{
  char *getenv();
  char *v;

  if ((v = getenv("JOBOUTPUT"))) /* Sys V lp Transcript compatibility */
    joboutput(v);
  if ((v = getenv("DOACCT")))	/* papif specific */
    doacct = getbval(v);
  if ((v = getenv("DEBUG")))	/* papif specific */
    debug = getbval(v);
  if ((v = getenv("BANNERFIRST")))
    bannerfirst = atoi(v);
  if ((v = getenv("BANNERLAST")))
    bannerlast = atoi(v);
  if ((v = getenv("BANNER")))	/* papif specific */
    bannerfile = v;
  if ((v = getenv("VERBOSELOG")))
    verboselog = getbval(v);
  if ((v = getenv("ATPRESPONSETIMEOUT"))) /* papif specific  */
    atpresponsetimeout = sectotick(60*2);
  if ((v = getenv("RFLOWQ"))) /* papif specific  */
    if ((rflowq = atoi(v)) <= 0) {
#ifndef SYSLOG
      log_w("papif: environment RFLOWQ too small, setting to 1");
#else
      syslog(LOG_WARNING, "environment RFLOWQ too small, setting to 1");
#endif
      rflowq = 1;
    }
  if (rflowq > atpMaxNum) {
    rflowq = atpMaxNum;
#ifndef SYSLOG
    log_w("papif: rflowq too large - setting to %d\n", rflowq);
#else
    syslog(LOG_WARNING, "rflowq too large - setting to %d", rflowq);
#endif
  }
  if ((v = getenv("SFLOWQ"))) /* papif specific  */
    if ((sflowq = atoi(v)) <= 0) {
#ifndef SYSLOG
      log_w("papif: environment SFLOWQ too small, setting to 1");
#else
      syslog(LOG_WARNING, "environment SFLOWQ too small, setting to 1");
#endif
      sflowq = 1;
    }
  if (sflowq > atpMaxNum) {
    sflowq = atpMaxNum;
#ifndef SYSLOG
    log_w("papif: sflowq too large - setting to %d\n", sflowq);
#else
    syslog(LOG_WARNING, "sflowq too large - setting to %d", sflowq);
#endif
  }
  if ((v = getenv("CHARGEBANNER"))) /* papif specific  */
    chargebanner = getbval(v);
  if ((v = getenv("WATCHTIME"))) /* papif specific  */
    if ((watchtime = atoi(v)) < 0) {
      watchtime = WATCHTIME;
#ifndef SYSLOG
      log_w("papif: environment watchtime too small, setting to %d\n",
#else
      syslog(LOG_WARNING, "environment watchtime too small, setting to %d",
#endif
	    watchtime);
    }
  if ((v = getenv("IDLESTUFF"))) /* papif specific  */
    doidlestuff = getbval(v);
  if ((v = getenv("ADOBE_STRUCTURED"))) /* papif specific  */
    dostruct = getbval(v);
  if ((v = getenv("MAPCRTOLF"))) /* papif specific */
    map_crtolf = getbval(v);
  if ((v = getenv("STRIPCONTROLD"))) /* papif specific */
    strip_control_d = getbval(v);
  if ((v = getenv("CAPPRINTERS"))) /* papif specific */
    if (access(v, R_OK)) 
      capprinters =  v;
  else
#ifndef SYSLOG
    log_w("papif: user specified cap.printers: %s not found, ignoring\n",v);
#else
    syslog(LOG_WARNING,
	"user specified cap.printers: %s not found, ignoring", v);
#endif
  if ((v = getenv("REVERSE")))
    if (access(v, X_OK) == 0)
      psreverse = v;		/* good enough I guess */
    else
#ifndef SYSLOG
      log_w("papif: specified psreverse filter %s not found, ignoring\n", v);
#else
      syslog(LOG_WARNING,
	  "specified psreverse filter %s not found, ignoring", v);
#endif
  if ((v = getenv("PSTEXT")))
    if (access(v, X_OK) == 0)
      pstext = v;
    else
#ifndef SYSLOG
      log_w("papif: specified pstext filter %s not found, ignoring\n", v);
#else
      syslog(LOG_WARNING,
	  "specified pstext filter %s not found, ignoring", v);
#endif
  if (psreverse != NULL || pstext != NULL)
    psmagic = 1;
  r_bufsiz = PAPSegSize*rflowq;
  s_bufsiz = PAPSegSize*sflowq;
}

/*
 * log current environment
 *
*/
logenv()
{
  if (debug) {
#ifndef SYSLOG
    log_d("papif: bannerfirst %s, bannerlast %s, verboselog %s\n",
	  boolvalstr(bannerfirst), boolvalstr(bannerlast),
	  boolvalstr(verboselog));
    log_d("papif: atpresponse timeout = %lu ticks (1/4 second units)\n",
	  atpresponsetimeout);
    if (watchtime)
      log_d("papif: status watch lower time limit %d seconds\n", watchtime);
    else
      log_d("papif: no status watch\n");
    log_d("papif: rflowq = %d packets, sflowq = %d packets\n", rflowq, sflowq);
    log_d("papif: strip control d's %s, map carriage return to line feed %s\n",
	  boolvalstr(strip_control_d), boolvalstr(map_crtolf));
    if (doacct)
      log_d("papif: accounting = %s, chargebanner %s",
	    boolvalstr(doacct), boolvalstr(chargebanner));
    else
      log_d("papif: accounting = %s, ", boolvalstr(doacct));
    log_d(", idlestuff %s, structured %s\n",
	  boolvalstr(doidlestuff), boolvalstr(dostruct));
    log_d("papif: reverse = %s\n", strval(psreverse));
    log_d("papif: pstext = %s\n", strval(pstext));
    log_d("papif: banner file = %s\n", strval(bannerfile));
    log_d("papif: cap.printers = %s\n",strval(capprinters));
#else
    syslog(LOG_DEBUG, "bannerfirst %s, bannerlast %s, verboselog %s",
	  boolvalstr(bannerfirst), boolvalstr(bannerlast),
	  boolvalstr(verboselog));
    syslog(LOG_DEBUG, "atpresponse timeout = %lu ticks (1/4 second units)",
	  atpresponsetimeout);
    if (watchtime)
      syslog(LOG_DEBUG, "status watch lower time limit %d seconds", watchtime);
    else
      syslog(LOG_DEBUG, "no status watch");
    syslog(LOG_DEBUG, "rflowq = %d packets, sflowq = %d packets",
	rflowq, sflowq);
    syslog(LOG_DEBUG,
	"strip control d's %s, map carriage return to line feed %s",
	boolvalstr(strip_control_d), boolvalstr(map_crtolf));
    if (doacct)
      syslog(LOG_DEBUG, "accounting = %s, chargebanner %s",
	    boolvalstr(doacct), boolvalstr(chargebanner));
    else
      syslog(LOG_DEBUG, "accounting = %s, ", boolvalstr(doacct));
    syslog(LOG_DEBUG, ", idlestuff %s, structured %s",
	  boolvalstr(doidlestuff), boolvalstr(dostruct));
    syslog(LOG_DEBUG, "reverse = %s", strval(psreverse));
    syslog(LOG_DEBUG, "pstext = %s", strval(pstext));
    syslog(LOG_DEBUG, "banner file = %s", strval(bannerfile));
    syslog(LOG_DEBUG, "cap.printers = %s",strval(capprinters));
#endif
  }
}

/*
 * parse arguments
*/
getargs(argc, argv, printer, user, host, acctfile)
int argc;
char **argv;
char *printer, *user, *host, **acctfile;
{
  int i;
  char *pgmname = NULL;
  char *p;

  *printer = *user = *host = '\0'; /* init to nothing */
  *acctfile = NULL;

  for (i=0; i<argc; i++) {
    p = argv[i];
    if (p[0] == '-') {
      switch (p[1]) {
      case 'd':
	dbugarg(p+2);
	break;
      case 'c':			/* specifies "pass control characters" */
				/* (literal mode) */
	break;
      case 'p':			/* program name: pscomm compat */
	pgmname = argv[++i];	/* set program name */
	break;
      case 'P':			/* printer name: pscomm compatible */
	strcpy(printer,argv[++i]);
	break;
      case 'n':			/* user name */
	strcpy(user,argv[++i]);
	break;
      case 'h':			/* host name */
	strcpy(host,argv[++i]);
	break;
      case 'r':
	neverreverse = TRUE;	/* pscomm compat */
	break;
      case 'x':			/* width in pixels */
      case 'y':			/* length in pixels */
      case 'i':			/* indentation size in chars */
      case 'l':			/* length in lines */
      case 'w':			/* width in chars */
	if (p[2] == '\0')	/* any more args for these? */
	  ++i;			/* yes, eat it */
	break;
      default:
#ifndef SYSLOG
	log_e("papif: Unknown argument %c\n",p[1]);
#else
	syslog(LOG_ERR, "Unknown argument %c", p[1]);
#endif
      }
    } else if (doacct)
      *acctfile = argv[i];
  }
  /* Get base of program name if specified with full path */
  if (pgmname == NULL) {
    if ((pgmname = rindex(argv[0], '/')) != NULL)
      pgmname++;			/* else skip over slash */
    else
      pgmname = argv[0];
  }
  /* if program name isn't papif or psif and printer name isn't there */
  /* then use name of program (psif added for Transcript compatibility) */
  if (*printer == '\0') 	/* no printer name? */
    if (strcmp(pgmname, "papif") != 0 && strcmp(pgmname, "psif") != 0)
      strcpy(printer, pgmname);
}


/*
 * our "input" filter - send input to laserwriter
 *
 * stdin - input
 * stdout - points to devices, empty here
 * stderr - points to log file on BSD4.2, Ultrix 1.0 through Ultrix 1.2
 *        - points to "err" tmp file on BSD 4.3
 *
 * Exit codes are listed above
 *
*/
main(argc,argv)
int argc;
char **argv;
{
  int pstatus();
  char *getlwname();
  char *acctfile = NULL;
  int spc, epc;

#ifdef SYSLOG
  openlog("papif", LOG_PID, LOG_LOCAL5);
#endif

  /* Initialize base vars */
  cno = -1;
  pid = getpid();		/* mark as not there for now */

  getargs(argc, argv, printer, user, host, &acctfile);
  initenv();			/* Transcript compatibility */

  lwname = getlwname(printer);	/* based on this */
  if (lwname == NULL) {
    log_e("papif: Cannot map name %s to LaserWriter name\n",printer);
    exit(lpd_REPRINT);
  }

  /* init cap */
  abInit(FALSE);		/* don't printout -- messes up with <stdin> */
  nbpInit();
  PAPInit();			/* init PAP printer routines */
  ATPSetResponseTimeout(atpresponsetimeout); /* set to 2 minutes */

  /* log message */
  log_i("papif: Starting job for %s@%s at %s on printer %s\n",
       user,host,ptime(),lwname);
  logenv();
  signal(SIGEMT, SIG_IGN);	/* used by psrev, etc to signal */
				/* they are "ready" */
  signal(SIGINT,quit);		/* this is what lprm sends us */
  signal(SIGTERM,quit);		/* this is what disable sends us */

  cno = openlw(lwname);
  if (doacct && chargebanner)
    spc = getpagecount(cno);	/* get the page count */
  if (bannerfirst)
    sendbanner(cno, host, user);
  if (doacct && !chargebanner)
    spc = getpagecount(cno);	/* get the page count */

  if (psmagic)
    dopsmagic(cno);
  sendfile(cno,fileno(stdin),host,user);/* send file to laserwriter */

  if (doacct && !chargebanner)
    epc = getpagecount(cno);	/* get the page count */
  if (bannerlast)
    sendbanner(cno, host, user);
  if (doacct && chargebanner)
    epc = getpagecount(cno);	/* get the page count */

  PAPClose(cno);

  if (doacct && acctfile != NULL)
    doaccounting(spc, epc, acctfile, user, host);
  log_i("papif: Finished job at %s\n", ptime ());
  exit(lpd_OK);			/* exit okay */
}

/*
 * send banner page: unlink afterwards so bannerfirst+bannerlast
 * won't result in two banner pages
 *
*/
sendbanner(cno, host, user)
int cno;
char *host, *user;
{
  int bannerfd;

  if ((bannerfd = open(bannerfile, 0)) >= 0) {
    sendfile(cno, bannerfd, host, user);
    close(bannerfd);
    unlink(bannerfile);
  }
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
  while ((err = PAPOpen(&cno, lwname, rflowq, &status, &ocomp) ) != noErr) {
    if (err != -1)		/* should be can't find lw.. */
      log_e("papif: PAPOpen returns %d\n",err);
    else {
      if ((i % 10) == 0) {	/* waited 5 minutes? */
	log_e("papif: Problems finding %s\n",lwname);
	i = 1;
      } else i++;
    }
    sleep(30);			/* wait N seconds */
  }
  do {
    abSleep(16, TRUE);
    if (watchtime != 0)		/* a little bogus.... */
      pstatus(status.StatusStr);
  } while (ocomp > 0);
  return(cno);
}

/*
 * reaper - deal with death of children
 *
*/
reaper()
{
#ifdef NOWAIT3
  int status;
#else /* have WAIT3 */
  union wait status;
#endif /* NOWAIT3 */
  register int i;
 
#ifdef NOWAIT3
  if ((i = wait(&status)) == 0) {
    log_w("papif: SIGCHLD but nothing from wait3\n");
    return;
  }
#else
  if ((i = wait3(&status, WNOHANG, 0)) == 0) {
    log_w("papif: SIGCHLD but nothing from wait3\n");
    return;
  }
#endif

  if (WIFSTOPPED(status)) {
    log_e("papif: Child %d stopped!\n", i);
    exit(lpd_REPRINT);
  }
 
  if (WIFSIGNALED(status)) {
    i = W_TERMSIG(status);
    if (i != SIGINT && i != SIGTERM) {
      log_e("papif: Child killed by signal %d\n", i);
      exit(lpd_REPRINT);
    }
  } else {
    if (i = W_RETCODE(status)) {
      log_w("papif: Finished job at %s with status %d\n", ptime(),i);
      /* probably psrev complaining */
      exit(lpd_ERRORS);
    }
    /* nothing to do with zero exit code */
  }
}

#define MAGICSIZE 11
#define MAXFILTERS 2
private char *filters[MAXFILTERS];
private int numfilters = 0;

/*
 * check input stream for adobe magic
 *
*/
dopsmagic()
{
  char magic[MAGICSIZE];
  int cnt, i;
  struct stat buf;
  int diskfile = FALSE;
  int retval;
  int in_front = TRUE;		/* fork filters in front of current fork */
  extern int errno;

  if (fstat(fileno(stdin), &buf) < 0) {
    perror("psmagic setup: fstat");
    diskfile = FALSE;
  } else {
    /* is it a regular file? */
    diskfile = S_ISREG(buf.st_mode);
  }
  if (!diskfile) {
    retval = fork_filter("<stdin>", TRUE);
    if (retval < 0)
      quit();
    if (retval != 0)
      return;
    in_front = FALSE;
  }
  if ((cnt = read(fileno(stdin), magic, MAGICSIZE)) < 0) {
    perror("psmagic setup: read");
    if (diskfile)
      quit();
    else
      exit(lpd_ERRORS);
  }
  if (diskfile) {
    rewind(stdin);
    lseek(fileno(stdin), 0L, 0); /* paranoia */
  }
  if (cnt < 2) {		/* nothing to do */
    log_w("papif: psmagic: only read %d, can't check magic\n", cnt);
    if (diskfile)
      return;
    else
      passalong(magic, cnt, MAGICSIZE);
  }

  if (strncmp(magic, "%!", 2) != 0) {
    if (pstext) {
      filters[numfilters++] = pstext;
      if (psreverse && !neverreverse)
	filters[numfilters++] = psreverse;
    }
  }
  /* check to see if follows Doc structuring 1.0 or better */
  /* note mutually exclusive of pstext */
  if (!neverreverse && psreverse &&
      cnt >= MAGICSIZE && strncmp(magic, "%!PS-Adobe-", MAGICSIZE) == 0)
    filters[numfilters++] = psreverse;

  if (in_front) {
    for (i = 0 ; i < numfilters; i++)
      fork_filter(filters[i], in_front);
  } else { /* must do in revse order */
    while (numfilters--)
      fork_filter(filters[numfilters], in_front);
  }
  if (diskfile)
    return;
  passalong(magic, cnt, MAGICSIZE);
}

/*
 * duplicate stdin with prefixed buffer
 *
*/
passalong(prebuf, precnt, wantcnt)
char *prebuf;
int precnt;
int wantcnt;
{
  register int cnt;
  register char *p;
  register int i;
  char buf[BUFSIZ];


  if (precnt < 0)
    exit(lpd_ERRORS);
  if (map_crtolf) {
    for (i = 0; i < precnt; i++)
      if (prebuf[i] == '\r')
	prebuf[i] = '\n';
  }
  if (write(fileno(stdout), prebuf, precnt) < 0)
    exit(lpd_ERRORS);
  if (precnt < wantcnt)
    exit(lpd_OK);
  while ((cnt = read(fileno(stdin), buf, sizeof(buf))) > 0)
    /* dangerous */
    if (map_crtolf) {
      for (i = 0, p = buf; i < cnt; i++)
	if (*p  == '\r')
	  *p = '\n';
    }
    if (write(fileno(stdout), buf, cnt) < 0)
      exit(lpd_ERRORS);
  exit(cnt < 0 ? lpd_ERRORS : lpd_OK);
}


char *current_fork = "papif";

/*
 * Run a filter program in a child process;  diddle the descriptors so that
 * the filter eats the parent process's former stdin, and pipes its output
 * into the parent's new stdin.
 *
*/
fork_filter(fp, in_front)
char *fp;
{
  int fdpipe[2];
  int fpid;
  char *fn;
  int not_stdin_fork;
  int mask;

  not_stdin_fork = (fp != NULL) && (strcmp(fp, "<stdin>") != 0);
  if (debug) {
#ifndef SYSLOG
    log_d("papif: Forking %s %s current fork %s\n",
	  not_stdin_fork ?  fp : "<stdin>",
	  in_front ? "in front of" : "behind",
	  current_fork);
#else
    syslog(LOG_DEBUG, "Forking %s %s current fork %s",
	  not_stdin_fork ?  fp : "<stdin>",
	  in_front ? "in front of" : "behind",
	  current_fork);
#endif
  }
  if (pipe(fdpipe) != 0) {
    perror("filter setup: pipe");
    quit();
  }

  if (fp) {
    fn = rindex(fp, '/');
    if (fn == NULL || fn[1] == '\0')
      fn = fp;
    else
      fn++;
  } else fn = NULL;
  if (!not_stdin_fork)
    fn = "<stdin>";

  /* interlock */
  mask = sigblock(sigmask(SIGCHLD)|sigmask(SIGINT)|sigmask(SIGTERM));
#ifdef NOVFORK
  fpid = fork();
#else
  fpid = not_stdin_fork ? vfork() : fork();
#endif
  switch (fpid) {
  case 0:			/* child */
    if (in_front) {
      if (dup2(fdpipe[1], fileno(stdout)) == -1) {
	perror("filter setup: child dup2");
	exit(lpd_ERRORS);
      }
    } else {
      if (dup2(fdpipe[0], fileno(stdin)) == -1) {
	perror("filter setup: child dup2");
	exit(lpd_ERRORS);
      }
    }
    close(fdpipe[1]);		/* ignore errs */
    close(fdpipe[0]);
    if (not_stdin_fork) {
      sigsetmask(mask);
      execl(fp, fn, 0);
      /* if we are here again, then... */
      perror("filter setup: child exec");
      exit(1);
    } else {
      current_fork = fn;
      signal(SIGINT, SIG_DFL);
      signal(SIGTERM, SIG_DFL);
      sigsetmask(mask);
      PAPShutdown(cno);		/* make sure child doesn't have the */
				/* fd's, etc. */
      return(0);
    }
    break;
  case -1:
    perror("filter setup: fork");
    return(-1);
    break;
  default:			/* parent continues */
    /* set up stdin to be pipe */
    signal(SIGCHLD, reaper);
    sigsetmask(mask);
    if (in_front) {
      if (dup2(fdpipe[0],fileno(stdin)) == -1) {
	perror("filter setup: parent dup2");
	return(-1);
      }
    } else {
      if (dup2(fdpipe[1],fileno(stdout)) == -1) {
	perror("filter setup: parent dup2");
	return(-1);
      }
    }
    close(fdpipe[1]);		/* ignore errs */
    close(fdpipe[0]);
    return(fpid);
  }
  return(0);
}

#ifdef NODUP2
#ifndef NOFILE
YOU MUST SET THIS TO THE MAXIMUM NUMBER OF FILE DESCRIPTORS AVAILABLE ON YOUR SYSTEM
#endif

/* emulate dup2 (hopefully) */
dup2(fdcur, fdwant)
int fdcur;
int fdwant;
{
  int fdarr[NOFILE];
  int i,j;
  int fd;

  close(fdwant);
  for (i = 0 ; i < NOFILE; i++) {
    fd = dup(fdcur);		/* duplicate */
    if (fd == fdwant)
      break;
    fdarr[i] = fd;		/* remember so we can close off */
  }
  if (i == NOFILE)
    return(-1);
  for (j = 0; j < i; j++)
    close(fdarr[j]);
  return(fdwant);
}
#endif

private char ps_buf[S_BUFMAX+10];
private char pr_buf[R_BUFMAX+10];

/*
 * Send a file to the specified connection
 */
sendfile(cno,fd,host,user)
int cno;
int fd;
char *host;
char *user;
{
  int eof, wcomp, paperr, err, doeof = FALSE;
  char *bp = ps_buf;
  wcomp = 0;


  strcpy(ps_buf, "/statusdict where {pop statusdict /jobname (");
  strcat(ps_buf, host);
  strcat(ps_buf, ":");
  strcat(ps_buf, user);
  strcat(ps_buf, ") put} if\n");
  if ((paperr=PAPWrite(cno, ps_buf,strlen(ps_buf), FALSE, &wcomp)) < 0) {
    log_e("papif: sendfile: 1st PAPWrite: call error %d\n", paperr);
    PAPClose(cno);
    exit(lpd_REPRINT);
  }
  /* post initial read from LW */
  err = 1;
  /* this is the main read/write loop */
  inithandleread();		/* initialze handleread */
  initgetbuf();			/* initialize getbuf */
  do {
    if ((eof = handleread(cno)))
      break;
    if (wcomp <= 0) {
      if (wcomp != noErr) {
	log_e("papif: sendfile: PAPWrite completion error %d\n",wcomp);
	PAPClose(cno);		/* sigh... */
	exit(lpd_REPRINT);
      } else {
	err = getbuf(fd, ps_buf, s_bufsiz, &bp, &doeof);
	/* err == 0 and no doeof means that we didn't see input */
	/* within a second or so, so we should try going ahead first */
	if (err || doeof) {
	  if ((paperr=PAPWrite(cno, bp, ((err<0)?0 :err), doeof, &wcomp)) < 0)
	    break;
	} else err = 1;
      }
    }

    statuswatch();
    abSleep(4, TRUE);		/* wait a bit */
  } while (err > 0 );

  if (err < 0)			/* this is a little overloaded */
    perror("read");
  if (paperr != noErr) {
    log_e("papif: sendfile: PAPWrite call error %d\n",paperr);
    wcomp = 0;
  }
  while (!eof || wcomp > 0) {		/* wait for completion */
    statuswatch();
    abSleep(4,TRUE);
    if (!eof)
      eof = handleread(cno);
  }
}

/*
 * return page count from a laserwriter
 *
*/
int
getpagecount(cno)
int cno;
{
  static char gpcstr[] = "statusdict begin pagecount (*) print == ";
  char buf[100];		/* enough for page count! */
  char *p;
  int err, wcomp, rlen, eof, rcomp, started;

  err = PAPWrite(cno, gpcstr, sizeof(gpcstr), TRUE, &wcomp);
  if (err != noErr)
    return(-1);
  err = PAPRead(cno, pr_buf, &rlen, &eof, &rcomp);
  if (err != noErr)
    return(-1);
  started = 0;
  do {
    if (rcomp <= 0) {
      if (rcomp == noErr && rlen > 0) {
	pr_buf[rlen] = '\0';	/* tie off string */
	if (!started) {
	  started = 1;
	  p = index(pr_buf, '*'); /* look for marker */
	  if (p != NULL) 
	    strcpy(buf, p+1);
	} else
	  strcat(buf, p);
      }
      if (eof)
	break;
      err = PAPRead(cno, pr_buf, &rlen, &eof, &rcomp);
      if (err != noErr)
	return(-1);
    }
    statuswatch();
    abSleep(4, TRUE);
  } while (!eof);
  return(atoi(buf));
}

/*
 * write out accounting information
 *
*/
doaccounting(spc, epc, acctfile, user, host)
int spc, epc;
char *acctfile, *user, *host;
{
  FILE *afd;

  if (epc >= spc && epc > 0 && spc > 0)  {
    if (user[0] != '\0' && acctfile && access(acctfile, W_OK) >= 0 &&
	(afd = fopen(acctfile, "a")) != NULL)
      fprintf(afd,"%7.2f\t%s:%s\n", (float)(epc-spc), host, user);
  } else
    log_w("papif: Problems getting pagecount: start %d, end %d\n",spc,epc);
}

/*
 * output status message to disk so lpq et al. can show it
 * Note: input string is a pascal string
 * Keeps around status until we have written out the status file again
 * so looks for status aren't there are minimized
 *
*/
pstatus(s)
char *s;
{
  int fd;
  int okay = TRUE;

  unlink("newstatus");
  if ((fd = open("newstatus",O_CREAT|O_WRONLY,0664)) < 0)
    return;
  if (write(fd, s+1, *s) < 0)
    okay = FALSE;
  write(fd, "\n", 1);
  close(fd);
  if (okay) {
    unlink("status");
    link("newstatus","status");
    unlink("newstatus");
  }
}

/*
 * returns nicely formated time string
*/
char *
ptime()
{
  long clock;
  char *timestr;
  char *p;

  clock = time(0);
  timestr = (char *)asctime(localtime(&clock));
  /* truncate after first linefeed */
  if ((p = index(timestr, '\n')))
    *p = '\0';
  return(timestr);
}

/*
 * get the laserwriter name of the unix spooled printer
 *
 * returns NULL if nothing found
 * returns 'LaserWriter Plus' if printer is null
*/
char *
getlwname(printer)
char *printer;
{
  FILE *fd;
  static char buf[1024];
  char *ep;
  char *getenv();

  if (printer[0] == '\0') {	/* no printer */
    /* try last resort */
    if ((printer = getenv("PRINTER")) == NULL) {
      return("LaserWriter Plus:LaserWriter@*");	/* default */
    }
  }

  if ((fd = fopen(capprinters,"r")) == NULL) {
    perror(capprinters);
    return(NULL);
  }
  do {
    if (fgets(buf, 256, fd) == NULL)
      break;
    buf[strlen(buf)-1] = '\0';	/* get rid of the lf */
    if (buf[0] == '#' || buf[0] == '\0')
      continue;
    if ((ep=index(buf,'=')) == NULL) /* find first = */
      continue;			/* no = in string */
    *ep = '\0';			/* set = to null now */
    if (strcmp(buf,printer) == 0) {
      if (strlen(ep+1) == 0)	/* no name */
	continue;
      fclose(fd);
      return(ep+1);		/* return pointer to value */
    }
  } while (1);
  fclose(fd);
  return(NULL);
}

/* MODULE: statuswatch EXPORTS(statuswatch) IMPORTS(lwname, pstatus) */

private time_t oldtime = -1;
private time_t newtime;
/*
 * Listens for status messages from lw
 *
*/
statuswatch()
{
  AddrBlock addr;
  PAPStatusRec status;
  int i;
  char retry[255];
  char tmpbuf[255];
  static int idletime = 0;
  OSErr err;

  if (watchtime == 0)		/* no status watch */
    return;
  if (oldtime == -1)
    time(&oldtime);
  else {
    time(&newtime);
    if ((newtime - oldtime) < watchtime) /* delay this much */
      return;
  }
  addr.net = 0;		/* sufficient */
  err = PAPStatus(lwname, &status, &addr);
  if (err < 0) {
    if (err != reqFailed)	/* no status message */
      return;
  } else
    oldtime = newtime;		/* reset */
  if (doidlestuff) {
    cpyp2cstr(tmpbuf, status.StatusStr);
    /* idletimeout if 40 seconds of "status: idle" or if papifidletest is */
    /* set.  Note: I have seen cases when the open reply pkt was lost */
    /* and never got back into open state, but only when running without */
    /* xo on the opens (a bug) */
    if (idletime == 0)
      time(&idletime);
    if ((strncmp("status: idle", tmpbuf, 12) == 0 && (time(0)-idletime)>40) || 
	access("/tmp/papifidletest", F_OK) == 0) {
      log_e("papif: status: idle bug; restarting\n");
      fflush(stderr);
      unlink("/tmp/papifidletest");
      for (i = 0 ; i < NSIG ; i++)
	signal(i, SIG_IGN);
      sprintf(retry, "(/usr/bin/sleep 2;/etc/lpc abort %s;/usr/bin/sleep 2;/etc/lpc start %s)&", 
	      printer, printer);
      system(retry);
      exit(lpd_REPRINT);
    }
  }
  pstatus(status.StatusStr);
}
/* END MODULE */


/* MODULE: getbuf EXPORTS(initgetbuf, getbuf) IMPORTS() */
/*
 * handle reads from file/pipe
 *
*/

static int gb_bc = 0, gb_stage = 0;
static char *gb_bp;
static char *gb_eofstr = "%%EOF\n";

initgetbuf()
{
  gb_bc = 0;
  gb_stage = 0;
}

/*
 * do a read, but don't let it hangup protocol if the read is blocking
 *
*/
private
dosread(fd, buf, length, nodata)
int fd;
char *buf;
int length;
int *nodata;
{
  int rdy;
  struct timeval t;
  gfd_set aset;
  int j;

  t.tv_sec = 0;
  t.tv_usec = 250;		/* 1/4 second? */
  FD_ZERO(&aset);
  FD_SET(fd, &aset);
  rdy = -1, j = 0;
  *nodata = FALSE;
  while (rdy <= 0 && j < 4) {
    FD_SET(fd, &aset);
    rdy = select(fd+1, &aset, 0, 0, &t);
    if (rdy > 0)
      break;
    abSleep(1, TRUE);
    j++;
  }
  if (rdy <= 0) {
    *nodata = TRUE;
    return(0);
  }
  return(read(fd, buf, length));
}

/*
 * Get a buffer looking for "%%EOF" at the start of a line if dostruct is set
 * otherwise just return a buffer
 *
*/
getbuf(fd, buf, maxbufsiz, bstart, doeof)
int fd;
char *buf;
int maxbufsiz;
char **bstart;
int *doeof;
{
  char *p;
  int i, j, nodata;

  if (!dostruct) {
    i = dosread(fd, buf, maxbufsiz, &nodata);
    if (nodata)
      return(i);
    if (i <= 0)
      *doeof = TRUE;
    if (strip_control_d) {
      /* dangerous, but may be necessary in some cases */
      for (p = buf, j = 0 ; j < i; j++)
	if (*p == '\004')
	  *p = '\n';
    }
    return(i);
  }
  if (gb_bc <= 0) {
    /* feed in previously read here: maybe backup this way? */
    if ((gb_bc = dosread(fd, buf, maxbufsiz, &nodata)) <= 0) {
      if (nodata)
	return(gb_bc);
      *doeof = TRUE;
      return(gb_bc);
    }
    gb_bp = buf;
  }
  /* scan gb_stage */
  *doeof = FALSE;
  for (p = gb_bp, i = 0; i < gb_bc; i++, p++) {
    if (strip_control_d) {
      if (*p == '\004')
	*p = '\n';
    }    
    if (gb_stage == 0)  {
      if (*p == '\r' || *p == '\n')
	gb_stage++;
    } else {
      if (*p == '\r')
	*p = '\n';
      if (*p == gb_eofstr[gb_stage-1]) {
	gb_stage++;
	if (gb_eofstr[gb_stage] == '\0') {
	  p++;
	  *doeof = TRUE;
	  gb_stage = 0;
	  break;
	}
      } else gb_stage = 0;
    }
  }
  *bstart = gb_bp;
  if (i != gb_bc)
    i++;			/* okay, have offset to convert to count */
  gb_bp = p;
  gb_bc -= i;			/* decrement by count */
  return(i);			/* return count */
}
/* END MODULE: getbuf */

/* MODULE: handleread EXPORTS(inithandleread,handleread) */
/* IMPORTS() */
private int hr_rcomp = noErr;
private int hr_rlen = 0;
private char hr_rbuf[R_BUFMAX+10];
private int hr_eof = 0;

inithandleread()
{
  hr_rcomp = noErr;
  hr_rlen = 0;
  hr_eof = 0;
}

/*
 * handle the papread
 *  return: -1 paperr
 *           0 ok
 *           1 eof
*/
handleread(cno)
{
  int paperr;

  if (hr_rcomp > 0)
    return(0);
  switch (hr_rcomp) {
  case noErr:
    break;
  default:
    log_e("papif: handleread: PAPRead error %d\n", hr_rcomp);
    return(-1);
  }
  hr_rbuf[hr_rlen] = '\0';
  if (hr_rlen) {
    log_r("%s", hr_rbuf);
  }
  if (hr_eof) {
    return(1);
  }
  paperr = PAPRead(cno, hr_rbuf, &hr_rlen, &hr_eof, &hr_rcomp);
  switch (paperr) {
  case noErr:
    break;
  default:
    log_e("papif: handleread: PAPRead error %d\n", paperr);
    return(-1);
  }
  return(0);
}

/* END MODULE: handleread */

#ifndef SYSLOG
/* BEGIN MODULE: log EXPORTS(log,joboutput) */

/*
 * Setup this so we can be smarter about errors in future
 * logging level are setup as: i - information, w - warning
 * e - error, r - return from laserwriter, and d - for debugging
 *
*/

private FILE *jobout;

#ifndef USEVPRINTF
/* Bletch - gotta do it because pyramids don't work the other way */
/* (using _doprnt and &args) and don't have vprintf */
/* of course, there will be something that is just one arg larger :-) */
/* VARARGS1 */
dolog(fmt, a1,a2,a3,a4,a5,a6,a7,a8,a9,aa,ab,ac,ad,ae,af)
char *fmt;
#else
dolog(va_alist)
va_dcl
#endif
{
#ifdef USEVPRINTF
  register char *fmt;
  va_list args;

  va_start(args);
  fmt = va_arg(args, char *);
  if (jobout)
    vfprintf(jobout, fmt, args);
  vfprintf(stderr, fmt, args);
  va_end(args);
#else
  if (jobout)
    fprintf(jobout, fmt, a1,a2,a3,a4,a5,a6,a7,a8,a9,aa,ab,ac,ad,ae,af);
      fprintf(stderr, fmt, a1,a2,a3,a4,a5,a6,a7,a8,a9,aa,ab,ac,ad,ae,af);
#endif
}

/*
 * Open the jobout file if possible - used for lp model
 *
*/
joboutput(filename)
char *filename;
{
  if ((jobout = fopen(filename, "w"))) {
    /* put a return at the start */
    putc('\n', jobout);
  }
}
/* END MODULE: log */
#endif
