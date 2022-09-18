/*
 *  Author: cck    Date: 88/05/19 13:12:43  
 *  Header: afperr.c,v 1.3 88/05/19 13:12:43 cck Rel  
 *  Revision: 1.3  
*/

/*
 * afperr.c - Error messages
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  Wed Apr  1	Schilit	   Created, based on Charlies routine
 *
 */
#include <stdio.h>
#include <netat/appletalk.h>
#include <netat/afp.h>

#define NUMERR 32

private char *afperrs[NUMERR] = {
  "Access Denied",					/* 5000 */
  "Authorization not yet complete",			/* 5001 */
  "Unknown User Authentication Method (UAM)",		/* 5002 */
  "Unknown AFP version",				/* 5003 */
  "Bitmap error",					/* 5004 */
  "Move of a directory to an inferior is illegal",	/* 5005 */
  "Deny conflict",					/* 5006 */
  "Directory is not empty",				/* 5007 */
  "Disk is full",					/* 5008 */
  "End of File",					/* 5009 */
  "File is busy",					/* 5010 */
  "Volume is a flat volume",				/* 5011 */
  "Item not found",					/* 5012 */
  "Lock error",						/* 5013 */
  "Miscellaneous error, seriously",			/* 5014 */
  "No more locks available",				/* 5015 */
  "Server not responding",				/* 5016 */
  "Object Exists",					/* 5017 */
  "Object not found",					/* 5018 */
  "Parameter error",					/* 5019 */
  "Range not locked",					/* 5020 */
  "Range overlap",					/* 5021 */
  "Session Closed",					/* 5022 */
  "Authorization failure",				/* 5023 */
  "Call not supported",					/* 5024 */
  "Object type error",					/* 5025 */
  "Too many files open",				/* 5026 */
  "Server going down",					/* 5027 */
  "Can't rename",					/* 5028 */
  "Directory not found",				/* 5029 */
  "Icon Type error",					/* 5030 */
  "Volume locked"		/* 5031 (2.0) */
};

char *afperr(err)
int err;
{
  static char errbuf[50];
  int e;

  if (err == 0)
    return("noErr");

  e = (-err) - 5000;		/* get index */
  if (e < 0 || e >= NUMERR) {
    (void) sprintf(errbuf,"unknown error %d",err);
    return(errbuf);
  }
  return(afperrs[e]);
}

aerror(msg, err)
char *msg;
int err;
{
  int e ;

  if (err == noErr) {
    fprintf(stderr, "%s: no error\n",msg);
    return;
  }
  e = (-err) - 5000;		/* get index */
  if (e < 0 || e >= NUMERR) {
    fprintf(stderr, "%s: unknown error %d\n",msg, err);
    return;
  }
  fprintf(stderr,"%s: %s\n", msg, afperrs[e]);
}
