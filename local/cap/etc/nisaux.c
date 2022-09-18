/*
 *  Author: cck    Date: 88/03/20 16:50:33  
 *  Header: nisaux.c,v 1.14 88/03/20 16:50:33 cck Rel  
 *  Revision: 1.14  
*/

/*
 * nisaux.c - name table management routines
 *
 * Follow are a set of simple minded name table management routines for
 *  the unix name server.
 * 
 * Needs some cleaning.
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University 
 *  in the City of New York.
 *
 * Edit History:
 *
 *   July 10, 1986    CCKim	Created
 *
*/

#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netat/appletalk.h>
#include <netat/abnbp.h>

/*
 * Network Table - internal use
 *
 * We do NOT assume that the only entries in this table will be for this
 * node.
 *
*/

typedef struct {
  AddrBlock addr;
  AddrBlock nc_addr;		/* address of nbp in client */
  u_char enume;
  EntityName ent;
} SNBPTEntry;

#define NUMNVE 20		/* careful - no more than 255 */
SNBPTEntry nbptable[NUMNVE];
private int numnve = 0;
private int newenum = 0;

nbptab_init()
{
  numnve = 0;
}

nbptab_insert(addr, nbpaddr, en)
AddrBlock *addr;
AddrBlock *nbpaddr;
EntityName *en;
{
  int i;
  SNBPTEntry *nve;
  extern char this_zone[];

  if (numnve == NUMNVE) {
    log(4, "register: nbptab overflow with %s:%s@%s",
	en->objStr.s, en->typeStr.s, en->zoneStr.s);
    return(nbpSR_overflow);
  }

  if (en->objStr.s[0] == '=' || en->typeStr.s[0] == '=') {
    log(4, "register: bad entity: wildcards in object or type %s:%s@%s", 
	en->objStr.s, en->typeStr.s, en->zoneStr.s);
    return(nbpSR_access);
  }
  /* only allow name registration of local zone */
  if (en->zoneStr.s[0] == '=' && en->zoneStr.s[1] == '\0') {
    log(4, "register: bad zone name '=' in %s:%s@%s",
	en->objStr.s, en->typeStr.s, en->zoneStr.s);
    return(nbpSR_access);
  }
  if (!(en->zoneStr.s[0] == '*' && en->zoneStr.s[1] == '\0'))
    if (strcmpci((char *)en->zoneStr.s, this_zone) != 0) {
    log(4, "register: our zone is %s, bad register attempted in zone %s",
	this_zone, en->zoneStr.s);
      return(nbpSR_access);
    }
  
  strcpy((char *)en->zoneStr.s, "*"); /* replace zone name with * in records */

  /* scan the list - see if we should be in the list at all. */
  for (newenum = 0, i = 0; i < numnve; i++) {
    nve = &nbptable[i];
    if (strncmp((char *)en->objStr.s, (char *)nve->ent.objStr.s, 32) == 0 &&
	strncmp((char *)en->typeStr.s, (char *)nve->ent.typeStr.s, 32) == 0 && 
	strncmp((char *)en->zoneStr.s, (char *)nve->ent.zoneStr.s, 32) == 0)
      if (bcmp((caddr_t)addr, (caddr_t)&nve->addr, sizeof(AddrBlock)) == 0) {
	log(4, "register: %s:%s@%s already registered: updating",
	    en->objStr.s, en->typeStr.s, en->zoneStr.s);	    
	/* update */
	bcopy((caddr_t)nbpaddr, (caddr_t)&nve->nc_addr, sizeof(AddrBlock));
	return(0);		/* in list, but okay */
      }
      else {
	log(4, "register: %s:%s@%s already registered, different address",
	    en->objStr.s, en->typeStr.s, en->zoneStr.s);	    
	return(nbpSR_access);	/* name already in list, diff addr */
      }
  }
  nve = &nbptable[numnve];
  nve->enume = (u_char)numnve; /* assumes less than 255 */
  bcopy((caddr_t)addr, (caddr_t)&nve->addr, sizeof(AddrBlock));
  /* update */
  bcopy((caddr_t)nbpaddr, (caddr_t)&nve->nc_addr, sizeof(AddrBlock));
  bcopy((caddr_t)en, (caddr_t)&nve->ent, sizeof(EntityName));
  numnve++;
  log(4, "register: NVE count is %d", numnve);
  return(nbpSR_noErr);
}

nbptab_delete(addr, nve)
AddrBlock *addr;
EntityName *nve;
{
  int i;

  for (i=0; i < numnve; i++) {
    if (bcmp((caddr_t)nve, (caddr_t)&nbptable[i].ent, sizeof(EntityName)) == 0)
      break;			/* found it */
  }
  if (i==numnve) {
    log(4, "deregister: name %s:%s@%s not found", 
	nve->objStr.s, nve->typeStr.s, nve->zoneStr.s);
    return(nbpSR_nsn);			/* err: nbpNotFound */
  }
  if (bcmp((caddr_t)addr,(caddr_t)&nbptable[i].nc_addr,sizeof(AddrBlock))!=0) {
    log(4, "deregister: %s:%s@%s access error -- address mismatch", 
	nve->objStr.s, nve->typeStr.s, nve->zoneStr.s);
    return(nbpSR_access);
  }
  log(4, "deregister: %s:%s@%s removed", 
      nve->objStr.s, nve->typeStr.s, nve->zoneStr.s);
  if (i != (numnve - 1) && i != (NUMNVE - 1)) {
    bcopy((caddr_t)&nbptable[i+1], (caddr_t)&nbptable[i],
	  sizeof(NBPTEntry)*((numnve-1) - i));
  }
  numnve--;
  log(4, "deregister: NVE count is %d", numnve);
  return(nbpSR_noErr);
}

nbpt_find(sent, start, reptab, reptabcnt)
EntityName *sent;
int *start;
NBPTEntry *reptab;
int reptabcnt;
{
  SNBPTEntry *p = nbptable;
  EntityName *pent;
  int i, cnt;
  extern char this_zone[];

  if ((*start) < numnve) {
    log(4, "look: starting at nbptab entry %d", *start);
    p = nbptable+(*start);
  } else {
    log(4, "look: start index %d beyond range of table", *start);
    return(0);			/* nothing then */
  }

  /* If not in local zone, then forget it */
  if (!((sent->zoneStr.s[0] == '*' && sent->zoneStr.s[1] == '\0') ||
	(sent->zoneStr.s[0] == '\0') || /* zero length string is "*" */
	strcmpci((char *)sent->zoneStr.s, this_zone) == 0)) {
    log(4, "look: name %s:%s@%s not in local zone, ignoring",
	sent->objStr.s, sent->typeStr.s, sent->zoneStr.s);
    return(0);
  }
    
  for (i=(*start),cnt=0; i < numnve && reptabcnt > 0; i++, p++) {
    pent = &p->ent;
    log(5, "look: checking %s:%s@%s", 
	pent->objStr.s, pent->typeStr.s, pent->zoneStr.s);
    if (!(sent->objStr.s[0] == '=' && sent->objStr.s[1] == '\0') &&
	strcmpci((char *)sent->objStr.s,(char *)pent->objStr.s) != 0) {
      log(5, "look: object mismatch");
      continue;
    }
    if (!(sent->typeStr.s[0] == '=' && sent->typeStr.s[1] == '\0') &&
	strcmpci((char *)sent->typeStr.s,(char *)pent->typeStr.s) != 0) {
      log(5, "look: type mismatch");
      continue;
    }
    log(5, "look: match at addr, match count is %d", cnt);
    reptab->addr = p->addr;	/* copy in entry */
    reptab->ent = p->ent;
    reptab->enume = p->enume;
    cnt++;
    reptab++;			/* move to next answer */
    reptabcnt--;
  }
  *start = i;
  return(cnt);
}

private boolean
getentry(fd, nve)
FILE *fd;
SNBPTEntry *nve;
{
  char str[256];
  int osl, tsl, zsl;
  int kipnet, kipsubnet;
  int node, skt;
  int enume;
  char *cp;
  extern char this_zone[];

  do {
    if (fgets(str, 256, fd) == NULL)
      return(TRUE);
    if (str[0] == '#' || str[0] == '\n')
      continue;
    sscanf(str, "net=%d.%d, node=%d, skt=%d, enum=%d, !%d!%d!%d! ? ",
	   &kipnet, &kipsubnet, &node, &skt, &enume,
	   &osl, &tsl, &zsl);
    nve->addr.node = node;
    nve->addr.skt = skt;
    nve->addr.net = htons(tokipnet(kipnet, kipsubnet));
    if (osl < 0 || tsl < 0 || zsl < 0) {
      log(6, "nis load: entry has negative lengths!");
      continue;
    }
      
    if ((cp = (char *)index(str, '?')) == NULL) {
      log(6, "nis load: Can't find ? delimiter, bad file");
      continue;
    }
    cp += 2;			/* move past '?' and space */
    if (strlen(cp) < (osl+tsl+zsl+2)) {
      log(6, "nis load: name length exceed available data");
      continue;
    }
    bzero((caddr_t)&nve->ent, sizeof(nve->ent));
    strncpy((char *)nve->ent.objStr.s, cp, min(32, osl)); /* get object */
    cp += (osl+1);		/* move past object and : */
    strncpy((char *)nve->ent.typeStr.s, cp, min(32, tsl)); /* get object */
    cp += (tsl+1);		/* move past object and @ */
    if (zsl > 1 || *cp != '*') {
      if (strcmpci(cp,this_zone) != 0) {
        log(6, "%s is not the current zone",cp);
        continue;		/* skip entry */
      }
      log(6, "nis load: only '*' allowed for zone");
    } 
    nve->ent.zoneStr.s[0] = '*';
    nve->ent.zoneStr.s[1] = '\0';
    nve->enume = enume;
    log(5, "Load: %s:%s@%s [%d] - [net %d.%d, node %d, skt %d]",
	nve->ent.objStr.s, nve->ent.typeStr.s, nve->ent.zoneStr.s,
	enume, kipnet, kipsubnet, node, skt);
    return(FALSE);
  } while(1);
  return(TRUE);			/* should never get here... */
}

int
nbptab_load(fd)
FILE *fd;
{
  int i;
  SNBPTEntry *nve;

  for (i=0; i < NUMNVE; i++) {
    nve = &nbptable[i];
    if (getentry(fd, nve))
      break;
  }
  numnve = i;
  return(numnve);
}

int
nbptab_dump(fd)
FILE *fd;
{
  long clock;
  int i;
  SNBPTEntry *nve;
  extern char this_zone[];
  int net;

  clock = time(0);
  fprintf(fd, "# Dump of NIS name table at %s", asctime(localtime(&clock)));
  fprintf(fd, "# Zone is fixed as %s (This is '*' - my zone)\n",this_zone);
  fprintf(fd,"# Format: ddp net, node, skt, and nbp enumerator followed by\n");
  fprintf(fd,"# obj, type, zone length enclosed in !'s and then the name\n");
  fprintf(fd, "# %d entries\n\n",numnve);
  for (i=0; i < numnve; i++) {
    nve = &nbptable[i];
    net = ntohs(nve->addr.net);
    fprintf(fd, "net=%d.%d, node=%d, skt=%d, enum=%d, !%d!%d!%d! ? %s:%s@%s\n",
	    net>>8, net&0xff, nve->addr.node, nve->addr.skt, nve->enume,
	    strlen((char *)nve->ent.objStr.s),
	    strlen((char *)nve->ent.typeStr.s),
	    strlen((char *)nve->ent.zoneStr.s),
	    nve->ent.objStr.s, nve->ent.typeStr.s, nve->ent.zoneStr.s);
  }
  return(numnve);
}

