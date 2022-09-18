/*
 *  Author: cck    Date: 88/03/19 20:55:18  
 *  Header: abzip.c,v 1.3 88/03/19 20:55:18 cck Rel  
 *  Revision: 1.3  
*/

/*
 * abzip.c - AppleTalk Zone Information Protocol
 *
 * Only support for GetZoneList.  GetMyZone is faked.
 *
 * MUST BE RUNNING KIP 1/88 or later to work properly (KIP 9/87 was the first
 * revision with zones, but the code didn't return properly)
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University in the
 * City of New York.
 *
 * Edit History:
 *
 *  March 1988, CCKim Create
 *
*/

#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>			/* so htons() works for non-vax */
#include <netat/appletalk.h>		/* include appletalk definitions */

/* move these defines to appletalk.h */
#ifndef zip_GetMyZone		/* in case defined */
/* define atp zip commands */
#define zip_GetMyZone 7		/* get my zone command */
#define zip_GetZoneList 8	/* get zone list command */

/* atp user bytes for zip commands */
/* no reply struct since return is packed array of pascal strings */

typedef struct zipUserBytes {
  byte zip_cmd;			/* zip command (LastFlag on return) */
  byte zip_zero;		/* always zero */
  word zip_index;		/* zip index (count on return) */
} zipUserBytes;

#endif

/*
 * send a get zone list command to our bridge
 * arguments:
 *   start_index: zone start index (first is 1)
 *   buffer to return zone list reply in - must be atpMaxData
 *   zipuserbytes: on noErr return: set to user bytes returned by bridge
 *
*/
OSErr
atpgetzonelist(start_index, buf, zipuserbytes)
int start_index;
char *buf;
zipUserBytes *zipuserbytes;
{
  AddrBlock addr;
  BDS bds[1];			/* 1 for zip */
  import u_short bridge_net;
  import u_char bridge_node;
  zipUserBytes *zub;
  atpProto *ap;
  ABusRecord abr;
  OSErr err;

  ap = &abr.proto.atp;

  ap->atpUserData = 0L;
  zub = (zipUserBytes *)&ap->atpUserData;
  zub->zip_cmd = zip_GetZoneList;
  zub->zip_zero = 0;
  zub->zip_index = htons(start_index); /* start at 1 */

  addr.net = bridge_net;
  addr.node = bridge_node;
  addr.skt = ddpZIP;

  ap->atpAddress.net = bridge_net;
  ap->atpAddress.node = bridge_node;
  ap->atpAddress.skt = ddpZIP;

  ap->atpSocket = 0;
  ap->atpReqCount = 0;
  ap->atpDataPtr = 0;
  ap->atpNumBufs = 1;
  bds[0].buffPtr = buf;		/* expect single reply from kip */
  bds[0].buffSize = atpMaxData;
  bds[0].userData = 0L;
  ap->atpRspBDSPtr = bds;
  ap->fatpXO = 0;
  ap->atpTimeOut = 4;
  ap->atpRetries = 3;

  /* send off request */
  err = ATPSndRequest(&abr, FALSE);
  if (err == noErr)
    bcopy(&bds[0].userData, zipuserbytes, sizeof(bds[0].userData));
  return(err);
}

/*
 * Given an array of char pointers
 *  return: array filled with pointers to zone names (malloc'ed)
 *   up the the size of the array
 *  return: the real count in realcnt
 *  return: any errors
 *
*/
OSErr
GetZoneList(zones, numzones, realcnt)
byte *zones[];
int numzones;
int *realcnt;
{
  OSErr err;
  byte *bp;
  byte *p;
  byte buf[atpMaxData+1];
  int gotcnt, zc, zi, i;
  zipUserBytes zub;

  /* setup GetZoneList command */

  zc = 0;
  zi = 1;
  do {
    if ((err=atpgetzonelist(zi, buf, &zub)) != noErr)
      return(err);
    gotcnt = ntohs(zub.zip_index); /* get count */
    if (gotcnt && numzones) {
      for (bp = buf, i = 0; i < gotcnt; i++) {
	if (numzones) {
	  p = (byte *)malloc(*bp+1); /* room for string */
	  cpyp2cstr(p, bp);	/* copy out */
	  zones[zc++] = p;	/* mark it */
	  numzones--;
	}
	bp += (*bp + 1);
      }
    }
    zi += gotcnt;		/* new index */
  } while (zub.zip_cmd == 0);
  *realcnt = zi - 1;
  return(noErr);
}

/*
 * Don't ask bridge because it may be in a different zone
 *
*/
char *
GetMyZone()
{
  extern char this_zone[];
  return(this_zone);
}

/*
 * Get rid of memory malloc'ed by GetZoneList
 *
*/
FreeZoneList(zones, cnt)
char **zones;
int cnt;
{
  while (cnt--) {
    if (zones[cnt])
      free(zones[cnt]);
    zones[cnt] = NULL;
  }
}
