static char rcsid[] = " Author: cck    Date: 88/03/20 16:49:38  ";
static char rcsident[] = " Header: procset.c,v 1.9 88/03/20 16:49:38 cck Rel  ";
static char revision[] = " Revision: 1.9  ";

/*
 * procset - UNIX AppleTalk spooling program: act as a laserwriter
 *   handles simple procset list - assumes procsets in a directory
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *  Created Sept 5, 1987 by cck from lwsrv.
 *
 *
 */
#include <stdio.h>
#include <sys/param.h>
#ifndef _TYPES
# include <sys/types.h>		/* assume included by param.h */
#endif
#include <sys/file.h>
#include <sys/dir.h>
#include <sys/stat.h>
#include <netat/appletalk.h>
#include <netat/sysvcompat.h>
#include <netat/compat.h>
#ifdef USESTRINGDOTH
# include <string.h>
#else
# include <strings.h>
#endif
#include "procset.h"
#include "spmisc.h"

DictList *dicthead = (DictList *) NULL;	/* dictionary list header */

void
newdictionary(dl)
DictList *dl;
{
  dl->ad_next = dicthead;		/* link it into the list */
  dicthead = dl;
}

DictList *
GetProcSet(psn)
char *psn;
{
  DictList *dl;

  for (dl = dicthead; dl != (DictList *) NULL; dl = dl->ad_next)
    if (strcmp(psn,dl->ad_ver) == 0)
      return(dl);
  return(NULL);
}


/*
 * checks if the file is there and should be readable
 *
*/
private boolean
checkfile(fn)
char *fn;
{
  struct stat stb;
  if (stat(fn, &stb) < 0)
    return(FALSE);
  if (!S_ISREG(stb.st_mode))		/* make sure regular file */
    return(FALSE);
  if (access(fn, R_OK) < 0)
    return(FALSE);
  return(TRUE);
}

private boolean
dictselect(d)
struct direct *d;
{

  if (d->d_name[0] != '.')
    return(TRUE);
  if (d->d_name[1] == '\0')		/* exclude "." */
    return(FALSE);
  if (d->d_name[1] == '.' && d->d_name[2] == '\0') /* exclude ".." */
    return(FALSE);
  return(checkfile(d->d_name));
}

/*
 * scan dict dir for valid proc sets
 *
*/
void
scandicts(dfn)
char *dfn;
{
  DictList *dl;
  struct direct **namelist;
  register struct direct *dp;
  struct stat stb;
  int i, j,nlst;
  char path[MAXPATHLEN];
  char line[1024];			/* reasonable size */
  char *psn;
  static time_t lastried = 0;
  FILE *fp;

  if (stat(dfn, &stb) >= 0) {
    if (lastried == stb.st_mtime) /* directory modified? */
      return;			/* no, nothing to do */
    lastried = stb.st_mtime;
  }
  fprintf(stderr, "lwsrv: (re)Scanning for Procsets\n");
#ifdef USEGETCWD
  if (getcwd(path,sizeof(path)-1) == 0) {
    fprintf(stderr, "lwsrv: Can't get working directory: %s\n", path);
    return;
  }
#else
  if (getwd(path) == 0) {
    fprintf(stderr, "lwsrv: Can't get working directory: %s\n", path);
    return;
  }
#endif
  if ((nlst = scandir(dfn, &namelist, dictselect, NULL)) < 0) {
    perror(dfn);
    fprintf(stderr, "Can't find dictionary files!\n");
    return;
  }
  if (chdir(dfn) < 0) {
    perror("chdir");
    fprintf(stderr, "on path %s\n",dfn);
    (void)chdir(path);			/* try to go back in case... */
    return;
  }
  for (i = 0, dp = namelist[0]; i < nlst ; i++, dp = namelist[i]) {
    if ((fp = fopen(dp->d_name, "r")) == NULL) 
      goto baddict;
    if (fgets(line, sizeof(line)-1, fp) == NULL) {
      fclose(fp);
      goto baddict;
    }
    if (strncmp(line, "%%BeginProcSet: ",sizeof("%%BeginProcSet: ")-1) != 0) {
      fclose(fp);
      goto baddict;
    }
    fclose(fp);
    for (j = 0; line[j] != '\0'; j++)	/* treat '\r' as eol */
      if (line[j] == '\r' || line[j] == '\n') {
	line[j] = '\0';
	break;
      }
    psn = line+sizeof("%%BeginProcSet:");
    stripspaces(psn);
    if (*psn == '\0')
      goto baddict;
    if ((dl=GetProcSet(psn)) != NULL) {
      if (checkfile(dl->ad_fn))
	goto baddict;
      free(dl->ad_fn);		/* reuse old dl, but drop fn space */
      free(dl->ad_ver);		/* drop ver space */
      dl->ad_fn = NULL;
    } else {
      if ((dl = (DictList *)malloc(sizeof(DictList))) == NULL)
	goto baddict;
    }
    dl->ad_ver = strdup(psn);		/* remember proc set name */
    dl->ad_fn = strdup(dp->d_name);	/* remember file name */
    dl->ad_next = dicthead;		/* link into list */
    dicthead = dl;
baddict:
    free(dp);
  }
  free(namelist);

  (void)chdir(path);

  for (dl = dicthead; dl != (DictList *) NULL; dl = dl->ad_next)
    fprintf(stderr,"lwsrv: ProcSet '%s' file is '%s/%s'\n",
	    dl->ad_ver,dfn,dl->ad_fn);
}


#define ADBUFZ MAXPATHLEN

private int domultijob = FALSE;

void
setflag_encrypted_instream(flg)
int flg;
{
  domultijob = flg;
}

void
ListProcSet(fn, dictdir, outfile)
char *fn;
char *dictdir;
FILE *outfile;
{
  char adbuf[ADBUFZ+1];
  FILE *fd;
  int cnt;

  sprintf(adbuf, "%s/%s",dictdir,fn);
  if ((fd = fopen(adbuf,"r")) != NULL) {
    if (domultijob) {
      fprintf(stderr, "lwsrv: Running in eexec mode\n");
      fprintf(outfile, "%%The following fixes problems where the prep file\n");
      fprintf(outfile, "%%assumes that it is permanently downloaded and an\n");
      fprintf(outfile, "%%eof occurs at the end of the prep (e.g. eexec)\n");
      fprintf(outfile, "2 {(%%stdin) (r) file cvx exec } repeat\n");
    }
    while ((cnt = fread(adbuf,sizeof(char),ADBUFZ,fd)) > 0)
      fwrite(adbuf,sizeof(char),cnt,outfile);
    if (domultijob)
      fprintf(outfile, "%%%%EOF\n");
    fclose(fd);
  } else {
    fprintf(stderr,"lwsrv: ListProcSet: file not found %s\n",adbuf);
    fprintf(outfile,"%% ** ProcSet file %s not found **\n",adbuf);
  }
}


