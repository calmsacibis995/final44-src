static char rcsid[] = " Author: cck    Date: 88/05/21 14:02:19  ";
static char rcsident[] = " Header: simple.c,v 1.16 88/05/21 14:02:19 cck Rel  ";
static char revision[] = " Revision: 1.16  ";

/*
 * lwsrv - UNIX AppleTalk spooling program: act as a laserwriter
 * simple.c - simple spooler.  Understands enough of Adobe's Document
 * Structuring Conventions to work, but doesn't really abide by them.
 *
 * should be replaced by a conforming implementation.
 *
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 * Sept 5, 1987 created by cck
 *
 */

#include <stdio.h>
#include <ctype.h>
#include <sys/param.h>
#ifndef _TYPES
/* assume included by param.h */
# include <sys/types.h>
#endif
#include <netat/appletalk.h>
#include <netat/sysvcompat.h>
#include <netat/compat.h>
#ifdef USESTRINGDOTH
# include <string.h>
#else
# include <strings.h>
#endif
#include "spmisc.h"
#include "procset.h"
#include "fontlist.h"
#include "papstream.h"


/* TOKEN types */
/* token types above: 4095 are not valid */
/* integer type should be at least 16 bits */
/* top 4 bits are used in to validate, invalidate things */
#define TOK_INVALID 0x1000	/* token shouldn't be considered */
#define TOK_VAL_MASK 0xfff	/* token value mask */
#define TOK_EOF 200		/* end of file marker */
#define TOK_UNK 201		/* unknown token */
#define TOK_ADV 0		/* AppleDict Version */
#define TOK_FLS 1		/* FontList */
#define TOK_ENDOLD 2		/* End of one of above */
#define TOK_TIT 3
#define TOK_CRE 4
#define TOK_FOR 5
#define TOK_ENC 6
#define TOK_BPSQ 7
#define TOK_EPSQ 8
#define TOK_BFLQ 9
#define TOK_EFLQ 10
#define TOK_BPS 11
#define TOK_EPS 12
#define TOK_IPS 13		/* include procset */
#define TOK_BEGINR 101		/* begin of query */
#define TOK_ENDR 102		/* end queyr with response */
#define TOK_BEGIN 103		/* begin item */
#define TOK_END 104		/* end item */
#define TOK_DROP 105		/* simply drop */

/* token table */
struct atoken {
  char *token;
  int toklen;
  int tokval;
} toktbl[] =  {
#define TOKEN(token, tag) { (token), (sizeof(token)-1), (tag)}
  TOKEN("%%EOF", TOK_DROP),
  TOKEN("%%Title", TOK_TIT),
  TOKEN("%%Creator", TOK_CRE),
  TOKEN("%%For", TOK_FOR),
  TOKEN("%%EndComments", TOK_ENC),
  TOKEN("%%?BeginProcSetQuery", TOK_BPSQ),
  TOKEN("%%?EndProcSetQuery", TOK_EPSQ),
  TOKEN("%%?BeginFontListQuery", TOK_BFLQ),
  TOKEN("%%?EndFontListQuery", TOK_EFLQ),
  TOKEN("%%?BeginFontQuery", TOK_BEGINR),
  TOKEN("%%?EndFontQuery", TOK_ENDR),
  TOKEN("%%?BeginFeatureQuery", TOK_BEGINR),
  TOKEN("%%?EndFeatureQuery", TOK_ENDR), 
  TOKEN("%%?BeginVMStatus", TOK_BEGINR),
  TOKEN("%%?EndVMStatus", TOK_ENDR),
  TOKEN("%%BeginExitServer", TOK_BEGIN),
  TOKEN("%%EndExitServer", TOK_END),
  TOKEN("%%BeginProcSet", TOK_BPS),
  TOKEN("%%EndProcSet", TOK_EPS),
  TOKEN("%%?BeginPrinterQuery", TOK_BEGINR),
  TOKEN("%%?EndPrinterQuery", TOK_ENDR),
  TOKEN("%%?BeginQuery", TOK_BEGINR),
  TOKEN("%%?EndQuery", TOK_ENDR),
#ifdef ADOBE_DSC2_CONFORMANT
  TOKEN("%%IncludeProcSet", TOK_IPS),
#else
  TOKEN("%%IncludeProcSet", TOK_IPS|TOK_INVALID),
#endif
  /* very old type of queries */
  TOKEN("%?appledict version #", TOK_ADV),
  TOKEN("%?fontList", TOK_FLS),
  TOKEN("%?end",TOK_ENDOLD),
  {NULL, TOK_UNK, 0}
};

private char *tracefile;
private char *dictdir;
private char *prtname;
private FILE *procsetfile = NULL;
private char tmpstr[MAXPATHLEN];
private FILE *outfile;
private int crtolf = FALSE;
private int needquote = FALSE;
private int nodsc = FALSE;
#ifdef ADOBE_DSC2_CONFORMANT
private int adobe_dsc2_conformant = TRUE;
#else
private int adobe_dsc2_conformant = FALSE;
#endif

export int is_simple_dsc();
export int simple_dsc_option();
export int simple_TranscriptOption();
export int spool_setup();
private void validate_token_type();
private void invalidate_token_type();
private int tokval();
private void dumpout();
private int scantoken();
int getjob();
private void SendVAck();

export int
is_simple_dsc()
{
  return(adobe_dsc2_conformant);
}

export int
simple_dsc_option(ioption)
char *ioption;
{
  int i;
  char *p;
  char option[5];		/* big enough for biggest */

  for (i = 0, p = ioption; i < 4; i++, p++)
    if (*p == '\0')
      break;
    else
      option[i] = (isupper(*p)) ? tolower(*p) : *p;
  option[i] = '\0';		/* tie off string */

  if (strcmp(option, "on") == 0) {
    fprintf(stderr, "lwsrv: simple: Turning on DSC2 compatibility, was %s\n",
	        adobe_dsc2_conformant ? "on" : "off");
    adobe_dsc2_conformant = TRUE;
    validate_token_type(TOK_IPS);
  } else if (strcmp(option, "off") == 0) {
    fprintf(stderr, "lwsrv: simple: Turning off DSC2 compatibility, was %s\n",
	        adobe_dsc2_conformant ? "on" : "off");
    adobe_dsc2_conformant = FALSE;
    invalidate_token_type(TOK_IPS);
  } else {
    fprintf(stderr,"lwsrv: simple: unknown Transcript compatiblity option: %s\n",
	    option);
    return(-1);
  }
  return(0);
}

/*
 * establish transcript compatibility options if any
 *
*/
export int
simple_TranscriptOption(ioption)
char *ioption;
{
  register char *p;
  register char *q;
  int i;
  char option[100];		/* big enough for biggest option */

  /* leave one for null (99 vs. 100) */
  for (p = ioption, q = option, i = 0; i < 99; i++, p++)
    if (*p == '\0') {
      break;
    } else if (*p == ' ' || *p == '\t' || *p == '-' || *p == '_')
      continue;
    else if (isupper(*p))
      *q++ = tolower(*p);
    else
      *q++ = *p;
  *q = '\0';
    
  if (strcmp(option, "quote8bit") == 0) {
    needquote = TRUE;
    fprintf(stderr, "lwsrv: simple: quoting 8 bit characters\n");
  } else if (strcmp(option, "crtolf") == 0) {
    crtolf = TRUE;
    fprintf(stderr,"lwsrv: simple: translate carrage return to line feed\n");
  } else if (strcmp(option, "makenondscconformant") == 0) {
    nodsc = TRUE;
    fprintf(stderr,"lwsrv: simple: will make documents non DSC conformant\n");
  } else {
  fprintf(stderr,"lwsrv:simple: unknown Transcript compatibility option: %s\n",
	  ioption);
    return(-1);
  }
  return(0);
}

/*
 * establish tracefile if any
 * establish fontfile name
 * (prtname unused) 
 * establish procset/dictionary directory and scan for dictionaries
 *
*/
export int
spool_setup(itracefile, fontfile, iprtname, idictdir)
char *itracefile;
char *fontfile;
char *iprtname;
char *idictdir;
{
  int errs;

  tracefile = itracefile;
  prtname = iprtname;
  dictdir = idictdir;

  if (prtname == NULL)
    prtname = "unknown";
    
  if (fontfile == NULL || !LoadFontList(fontfile)) {
    fprintf(stderr,"lwsrv: simple: Bad FontList\n");
    return(FALSE);
  }
  fprintf(stderr,"lwsrv: simple: Font list from file %s\n",fontfile);
  scandicts(dictdir);			/* scan for dictionary files */
  return(TRUE);
}

/*
 * validate/invalidate a token type for use
 *
*/
private void
validate_token_type(toktype)
int toktype;
{
  register struct atoken *tp;

  for (tp = toktbl; tp->token != NULL; tp++)
    if ((tp->tokval & TOK_VAL_MASK) == toktype)
      tp->tokval &= (~TOK_INVALID);
}

private void
invalidate_token_type(toktype)
int toktype;
{
  register struct atoken *tp;

  /* can't invalidate these */
  if (toktype == TOK_UNK || toktype == TOK_EOF)
    return;
  for (tp = toktbl; tp->token != NULL; tp++)
    if ((tp->tokval & TOK_VAL_MASK) == toktype)
      tp->tokval |= TOK_INVALID;
}

/*
 * scan "str" for a token and return the token type.
 * set ptr to the position after the token
 * 
*/
private int
tokval(str,ptr)
char *str,**ptr;
{
  char *p;
  register struct atoken *tp;

  /* all tokens start with "%?" or "%%" or "%!" */
  if (str[0] != '%')
    return(TOK_UNK);
  if (str[1] != '?' && str[1] != '%' && str[1] != '!')
    return(TOK_UNK);

  for (tp = toktbl; tp->token != NULL; tp++) {	/* locate token value */
    if (tp->tokval & TOK_INVALID)
      continue;
    if (strncmp(str,tp->token,tp->toklen) == 0) {
      p = &str[tp->toklen];
      if (*p == ':')		/* skip ':' */
	p++;
      /* skip leading white space */
      while (*p != '\0' && (*p == ' ' || *p == '\t'))
	p++;
      *ptr = p;				/* set tokstr */
      return(tp->tokval);		/* and return the value */
    }
  }
  return(TOK_UNK);
}


/*
 * dump the string to the outfile and procset file if necesary
 *
*/
private void
dumpout(str,len)
char *str;
int len;
{
  int i,c;

  for (i=0; i < len; i++) {
    c = str[i];
    if (crtolf && c == '\r')
      c = '\n';
    if (needquote) {
      if (isascii(c))	/* is it standard ascii? */
	putc(c,outfile);	/* yes... so echo */
      else		/* otherwise echo \ddd */
	fprintf(outfile,"\\%03o",(unsigned char) c);
    } else
      putc(c,outfile);
    if (procsetfile)		/* never quote */
      putc(c, procsetfile);
  }
  putc('\n',outfile);
  if (procsetfile)
    putc('\n', procsetfile);
}



/*
 * int scantoken(PFILE *pf,int echo,char *tokstr)
 *
 * Read characters from the PAP connection specified by pf.
 * Echo characters to stdout if echo is TRUE.  Return token value
 * and tokstr pointing past token characters.
 *
*/

#define MAXTOKSTR 1024
/* We assume all tokens begin with "%" */
private int
scantoken(pf,echo,tptr)
PFILE *pf;
int echo;
char **tptr;
{
  static char tokstr[MAXTOKSTR];
  int atstart,i,c,tv,maybetoken;

  i = 0;
  atstart = TRUE;
  maybetoken = FALSE;
  while ((c = p_getc(pf)) != EOF) {
    if (c == '%' && atstart)
      maybetoken = TRUE;
    atstart = (c == '\r' || c == '\n') ? TRUE : FALSE;
    if (maybetoken) {
      if (atstart) {		/* last char is cr or lf */
	tokstr[i] = '\0';	/* tie off token */
	if ((tv = tokval(tokstr,tptr)) != TOK_UNK) {
	  if (tracefile != NULL)
	    dumpout(tokstr,i);
	  return(tv);
	} else if ((tracefile != NULL) || echo)
	  dumpout(tokstr, i);
	i = 0;
	maybetoken = FALSE;
	continue;		/* skip everything else */
      }
      if (i < MAXTOKSTR)
	tokstr[i++] = c;
      continue;
    }
    /* papif handles it right, but others like transcript don't, so... */
    if ((tracefile != NULL) || echo) { /* do we want to echo this? */
      /* papif handles it right, but others like transcript don't, so... */
      /* make it a compilable option */
      if (crtolf && c == '\r')
	c = '\n';
      if (needquote) {
	if (isascii(c))	/* is it standard ascii? */
	  putc(c,outfile);	/* yes... so echo */
	else		/* otherwise echo \ddd */
	  fprintf(outfile,"\\%03o",(unsigned char) c);
      } else
	putc(c,outfile);
    }
    if (procsetfile)
      putc(c, procsetfile);
  }

  /* found EOF */
  
  if ((tracefile != NULL) || echo)
    putc('\n',outfile);			/* yes... echo eol */
  if (procsetfile)
    putc('\n', procsetfile);
  return(TOK_EOF);			/* return now */
}

/*
 * handle an incoming job
 *
*/
int
getjob(pf,of)
PFILE *pf;
FILE *of;
{
  char *ts,adictver[80];
  int ltokval,tokval,echo;
  DictList *dl = NULL;		/* current dictionary */
  DictList *dlnew = NULL;	/* new dictionary */
  
  outfile = of;
  p_clreof(pf);				/* clear EOF indicator */
  echo = TRUE;
  if (nodsc) {
    fprintf(outfile, "%%! PostScript Document, but non-conformant\n");
    fprintf(outfile, "%%  so psrv is not invoked\n");
  }

  clearstack();
  while ((tokval = scantoken(pf,echo,&ts)) != TOK_EOF) {
    switch (tokval) {
    case TOK_DROP:
      break;
    case TOK_BPS:
      /* really smart would install into dict */
      /* remember to flush off "appledict" part */
      push(tokval);			/* remember where */
      echo = FALSE;
      stripspaces(ts);			/* clear off extra spaces */
      if ((dl = GetProcSet(ts)) != NULL) {
	fprintf(stderr, "lwsrv: simple: procset already known\n");
	break;
      }
      sprintf(tmpstr, "%s/FoundProcSet.%d",dictdir,time(0));
      fprintf(stderr, "lwsrv: simple: Saving to %s BeginProcSet: %s\n",
	      tmpstr, ts);
      if (procsetfile != NULL) {
	fprintf(stderr, "lwsrv: simple: Already logging prep file!");
	break;
      }
      if ((procsetfile = fopen(tmpstr, "w+")) == NULL) {
	procsetfile = NULL;
	perror(tmpstr);
      } else {
	dlnew = dl = (DictList *)malloc(sizeof(DictList));
	dl->ad_ver = strdup(ts);
	dl->ad_fn = strdup(tmpstr+strlen(dictdir)+1);
	dl->ad_next = NULL;
	fprintf(procsetfile, "%%%%BeginProcSet: %s\n", ts);
      }
      /* copy from BPS to end into file or memory */
      /* tag given is new proc set */
      break;
    case TOK_EPS:
      if (pop() != TOK_BPS) {
	fprintf(stderr,"lwsrv: simple: Framing error on Begin/End Proc Set\n");
      }
      if (procsetfile) {			/* if remember file */
	fprintf(procsetfile, "%%%%EndProcSet\n");
	fclose(procsetfile);		/* close outfile */
      }
      procsetfile = NULL;
      echo = TRUE;
      if (dlnew) {
	newdictionary(dlnew);
	dlnew = NULL;		/* close off */
      }
      if (dl) {
	fprintf(stderr,
		((adobe_dsc2_conformant) ?
		 "lwsrv: simple: dsc2: document supplied procset %s = %s\n" :
		 "lwsrv: simple: non-dsc2: Including ProcSet %s = %s\n"),
		dl->ad_ver,dl->ad_fn);
	fprintf(outfile,"%% ** Procset From File: %s **\n",dl->ad_fn);
	ListProcSet(dl->ad_fn, dictdir, outfile);
	fprintf(outfile,"%% ** End of ProcSet **\n");
      }
      dl = NULL;		/* Close off */
      break;
    case TOK_BEGIN:
      push(tokval);
      echo = FALSE;
      break;
    case TOK_END:
      if (pop() != TOK_BEGIN)
	fprintf(stderr, "lwsrv: simple: Framing error on TOK_BEGIN/END\n");
      echo = TRUE;
      break;
    case TOK_BEGINR:
      push(tokval);			/* remember last token value */
      echo = FALSE;
      break;
    case TOK_ENDR:
      if (pop() != TOK_BEGINR)
       fprintf(stderr,"lwsrv: simple: Stack Frame error on TOK_BEGINR/ENDR\n");
      echo = TRUE;			/* we are now echoing */
      p_write(pf,ts,strlen(ts),FALSE);
      break;
    case TOK_BPSQ:
    case TOK_BFLQ:
    case TOK_FLS:			/* fontList */
    case TOK_ADV:			/* appledict version */
      push(tokval);
      if (tracefile == NULL)		/* unless tracing there is no */
	echo = FALSE;			/*  echoing between token and End */
      if (tokval == TOK_ADV ||		/* is this appledict query? */
	  tokval == TOK_BPSQ)
	strcpy(adictver,ts);		/*  yes, remember appledict version */
      break;
    case TOK_FOR:			/* For: */
      setusername(ts);
      break;
    case TOK_TIT:			/* Title: */
      setjobname(ts);
      break;
    case TOK_ENC:			/* EndComments */
      break;
    case TOK_IPS:
      if (!adobe_dsc2_conformant)
	break;
      stripspaces(ts);		/* strip extra spaces */
      if ((dl = GetProcSet(ts)) != NULL) {
	fprintf(stderr,"lwsrv: simple: Including ProcSet %s = %s\n",
		dl->ad_ver,dl->ad_fn);
	fprintf(outfile,"%% ** Include Procset From File: %s **\n",dl->ad_fn);
	ListProcSet(dl->ad_fn, dictdir, outfile);
	fprintf(outfile,"%% ** End of ProcSet **\n");
	dl = NULL;		/* close off */
      } else
	fprintf(stderr,"lwsrv: simple: Unknown ProcSet file for '%s'\n",ts);
      break;
    case TOK_EFLQ:
    case TOK_EPSQ:
    case TOK_ENDOLD:			/* End */
      echo = TRUE;			/* we are now echoing */
      ltokval = pop();
      switch (ltokval) {		/* according to last found token */
      case TOK_BPSQ:
      case TOK_ADV:			/* if last token was AppleDict */
	SendVAck(pf,adictver);		/*  then handle appledict */
	break;
      case TOK_BFLQ:
      case TOK_FLS:			/* if last token was FontList */
	SendFontList(pf);		/*  then send out the fontlist  */
	break;
      default:
	fprintf(stderr, "lwsrv: simple: Stack framing error: got %d\n",
		ltokval);
	break;
      }
    }
  }
  if (!isstackempty()) {
    fprintf(stderr, "lwsrv: simple: EOF and tokens still on stack!\n");
    dumpstack();
  }
  if (procsetfile) {
    fclose(procsetfile);
    if (dlnew) {
      unlink(dlnew->ad_fn);
      free(dlnew->ad_fn);	/* free fn */
      free(dlnew);
    }
  }
  if (p_isopn(pf))			/* if connection is still open */
    p_write(pf,"",0,TRUE);		/* send EOF for this job */
  return(p_isopn(pf));			/* return open state */
}

#define MD_UNK		"0\n"		/* Mac dictionary not loaded */
#define MD_AVOK		"1\n"		/* AppleDict version ok (av) */
#define MD_AVBAD	"2\n"		/* AppleDict version not ok */
/*
 * answer a query as to whether a particular procset is known or not
 *
*/
private void
SendVAck(pf,ver)
PFILE *pf;
char *ver;
{
  DictList *dl;
  char status[80];

  stripspaces(ver);			/* strip any extra spaces */

  dl = GetProcSet(ver);			/* find any procset */

  if (tracefile != NULL || dl == (DictList *)NULL) { 
    p_write(pf,MD_UNK,2,FALSE);		/* if tracing download the dict */
    fprintf(stderr,"lwsrv: simple: Receiving AppleDict version %s\n",ver);
    /* won't do much good unless single fork */
    sprintf(status,"Receiving AppleDict version #%s",ver);
    NewStatus(status);
    return;			/* by pass the prepend */
  } else
    p_write(pf,MD_AVOK,2,FALSE);	/* otherwise we use local file */

  if (!adobe_dsc2_conformant) {
    if (dl != (DictList *) NULL) {
      if (tracefile == NULL) {
	/* won't do much good unless single fork */
	sprintf(status,"prepending AppleDict version #%s",ver);
	NewStatus(status);
	fprintf(stderr,"lwsrv: simple: Using ProcSet %s = %s\n",ver,dl->ad_fn);
	fprintf(outfile,"%% ** Prepending ProcSet from: %s **\n",dl->ad_fn);
	ListProcSet(dl->ad_fn, dictdir, outfile); /* prepend appledict */
	fprintf(outfile,"%% ** End of ProcSet **\n");
      }
    } else {
      fprintf(stderr,"lwsrv: simple: Unknown ProcSet file for '%s'\n",ver);
    }
  }
}

