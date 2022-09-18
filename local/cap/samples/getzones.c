static char rcsid[] = " Author: cck    Date: 88/03/20 16:54:11  ";
static char rcsident[] = " Header: getzones.c,v 1.2 88/03/20 16:54:11 cck Rel  ";
static char revision[] = " Revision: 1.2  ";

/*
 * getzones - retrieves the zone list from our bridge
 *
 * MUST BE RUNNING KIP 1/88 to work properly (KIP 9/87 was the first
 * revision with zones, but the code didn't return properly)
 *
 * Test program: most of this code will eventually be moved to abzip
 * 
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia
 * University in the City of New York.
 *
 * Edit History:
 *
 *  March 1988, CCKim, Created
 *
 */

char copyright[] = "Copyright (c) 1988 by The Trustees of Columbia \
University in the City of New York";

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <netinet/in.h>			/* so htons() works for non-vax */
#include <netat/appletalk.h>		/* include appletalk definitions */

#define NUMZONES 100

main(argc, argv)
int argc;
char **argv;
{
  int i,cnt;
  OSErr err;
  char *zones[NUMZONES];	/* room for pointers to zone names */
  char *myzone;

  abInit(TRUE);

  if ((err = GetZoneList(zones, NUMZONES, &cnt)) != noErr) {
    fprintf(stderr, "error %d getting zone list\n", err);
    exit(1);
  }
  if (cnt > NUMZONES) {
    printf("only asked for %d zones when there were actually %d\n",
	   NUMZONES,cnt);
    cnt = NUMZONES;
  }
  printf("Count is %d\n", cnt);
  myzone = GetMyZone();
  for (i = 0; i < cnt ; i++) {
    printf("ZONE %s", zones[i]);
    if (strcmp(zones[i],myzone) == 0)
      putchar('*');
    putchar('\n');
  }
  FreeZoneList(zones, cnt);
}

