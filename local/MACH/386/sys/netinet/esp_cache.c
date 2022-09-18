/* 
 * Mach Operating System
 * Copyright (c) 1989 Carnegie-Mellon University
 * Copyright (c) 1988 Carnegie-Mellon University
 * Copyright (c) 1987 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	esp_cache.c,v $
 * Revision 2.3  89/03/09  20:41:15  rpd
 * 	More cleanup.
 * 
 * Revision 2.2  89/02/25  18:56:13  gm0w
 * 	Updated copyright.
 * 	[89/02/12            gm0w]
 * 
 * 01-Jul-87  Daniel Julin (dpj) at Carnegie-Mellon University
 *	Created from Stanford sources (as of June 87).
 *
 */
 
#include <mach_vmtp.h>

/*
 * $ Header: esp_cache.c,v 2.1 87/08/18 16:30:28 mrt Exp $
 */

/*
 * 	esp_cache.c		2/26/87
 *	Written by Erik Nordmark
 */

/* 
 * The server host cache used in the Entity State Protocol
 */

/* 
 * TODO
 */

#include <sys/param.h>
#include <sys/systm.h>
#include <sys/mbuf.h>
#include <sys/protosw.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <sys/kernel.h>

#include <net/if.h>
#include <net/route.h>

#include "in.h"
#include "in_pcb.h"
#include "in_systm.h"
#include "ip.h"
#include "ip_var.h"
#include "vmtp_so.h"
#include "vmtp.h"
#include "vmtp_ip.h"
#include "vmtp_var.h"
#include "vmtp_send.h"
#include "vmtp_group.h"
#include "vmtp_buf.h"
#include "esp.h"
#include "esp_var.h"
#include "esp_cache.h"

#ifdef	CACHE_DEBUG
esp_dumpcache(str)
	char *str;
{	
	int i, k;
	int s = splimp();
	struct vmtpsce	*sc = NULL;

	printf("esp_dumpcache(): %s\n", str);
	
	for (i = 0; i < ESP_CACHEMAPSIZE; i++) {
		k = 0;
		for (sc = vecachemap[i]; sc && k < 10; 
		    sc = sc->ve_nextmap, k++) {
			printf("\t%d,%d: server = %x:%x\n", i, k, 
			    sc->ve_server.ve_fltm, sc->ve_server.ve_inaddr);
		}
		if (sc)
			printf("vecachemap[%d] cycling ??\n", i);
	}
	printf("esp_dumpcache(): first = 0x%x, last =0x%x\n", vesceLRU.first,
		vesceLRU.last);
	for (sc = vesceLRU.first, k = 0; sc && k < ESP_SERVERCACHE_SIZE-1;
	    sc = sc->ve_next, k++) {
		printf("\t%d:: server = %x:%x\n", k, 
			    sc->ve_server.ve_fltm,
			    sc->ve_server.ve_inaddr);
	}
	if (!sc) {
		printf("esp_dumpcache(): TOO short LRU list\n");
		splx(s);
		return;
	}
	printf("\t%d:: server = %x:%x\n", k, 
		sc->ve_server.ve_fltm,
		sc->ve_server.ve_inaddr);
	if (sc != vesceLRU.last)
		printf("esp_dumpcache(): last pointer wrong!\n");
	if (sc->ve_next) {
		printf("esp_dumpcache(): too long LRU list\n");
		for (k = 0; sc && k < ESP_SERVERCACHE_SIZE;
	    	    sc = sc->ve_next, k++) {
			printf("\tEXTRA %d:: server = %x:%x\n", k, 
			    sc->ve_server.ve_fltm,
			    sc->ve_server.ve_inaddr);
		}
	}
	splx(s);
} /* esp_dumpcache */
#endif

/*
 * Initialize the cache and the cache map 
 */
esp_initcache()
{
	int i;
	int s = splimp();
	struct vmtpsce	*sc = NULL;

#ifdef	ESP_DEBUG
	printf("esp_initcache(): called\n");
#endif
	
	for (i = 0; i < ESP_SERVERCACHE_SIZE; i++) {
		veservers[i].ve_nextmap = NULL;
		veservers[i].ve_next = sc;
		veservers[i].ve_iflags = 0;
		veservers[i].ve_flags = 0;
		sc = &veservers[i];
	}
	vesceLRU.first = sc;
	vesceLRU.last = &veservers[0];

	for (i = 0; i < ESP_CACHEMAPSIZE; i++) {
		vecachemap[i] = NULL;
	}
	splx(s);
#ifdef	CACHE_DEBUG
	esp_dumpcache("esp_initcache");
#endif
} /* esp_initcache */

/*
 * Find a free slot in the cache.
 * If none return take the first one in the LRU list and remove that one from
 * the cache map. The entry is inserted at the end of the LRU list i.e.
 * it is touched.
 *
 * The caller has to set the initial value in the cache entry.
 */
struct vmtpsce *esp_allocentry(server)
	struct vmtpeid server;
{
	register struct vmtpsce *sc;
	register int h, s = splimp();

#ifdef	ESP_DEBUG
	printf("esp_allocentry(): called\n");
	vmtp_dumpeid(&server,"server","esp_allocentry");
#endif
#ifdef	CACHE_DEBUG
	esp_dumpcache("esp_allocentry - before");
#endif
	sc = vesceLRU.first;
	if (entry_used(sc)) {
#ifdef	ESP_DEBUG
		printf("esp_allocentry(): grabbing old entry\n");
		vmtp_dumpeid(&sc->ve_server,"sc->ve_server","esp_allocentry");
#endif

		esp_removeentry(sc->ve_server);
	}
	vesceLRU.first = vesceLRU.first->ve_next;
	if (sc->ve_nextmap)
		panic("esp_allocentry");
	sc->ve_iflags = VEIF_USED;
	sc->ve_flags = 0;
	sc->ve_next = NULL;
	sc->ve_server = server;
	vesceLRU.last->ve_next = sc;
	vesceLRU.last = sc;
	h = esp_hash(&server);		/* insert into map */
	sc->ve_nextmap = vecachemap[h];
	vecachemap[h] = sc;
	splx(s);
#ifdef	CACHE_DEBUG
	esp_dumpcache("esp_allocentry - after");
#endif
	return sc;
} /* vmtp_allocentry */

/*
 * Find a given entry in the cache by using the map.
 * The entry is touched i.e. it's moved to the end of the list.
 * Return NULL if not found.
 */
struct vmtpsce *esp_findentry(server)
	struct vmtpeid server;
{
	register struct vmtpsce **a_sc;
	register struct vmtpsce *sc;
	register int s;

#ifdef	ESP_DEBUG
	printf("esp_findentry(): called\n");
	vmtp_dumpeid(&server,"server","esp_findentry");
#endif
#ifdef	CACHE_DEBUG
	esp_dumpcache("esp_findentry - before");
#endif
	s = splimp();
	a_sc = &vecachemap[esp_hash(&server)];
	while (*a_sc != NULL && !vmtp_sameeid((*a_sc)->ve_server, server))
		a_sc = &((*a_sc)->ve_nextmap);
	if (*a_sc == NULL) {
		splx(s);
		return NULL;
	}

	/* move to end of LRU list */
	if ((*a_sc)->ve_next) {
		/* 
		 * Not already at end:
		 * Find it in the LRU list and move it to its tail
		 */
		sc = vesceLRU.first;
		if (sc == *a_sc) {
			vesceLRU.first = sc->ve_next;
		} else {
			while (sc && sc->ve_next != *a_sc)
				sc = sc->ve_next;
			if (!sc)
				panic("esp_findentry");

			sc->ve_next = (*a_sc)->ve_next;
		}
		vesceLRU.last->ve_next = *a_sc;
		vesceLRU.last = *a_sc;
		(*a_sc)->ve_next = NULL;
	}

	(*a_sc)->ve_iflags |= VEIF_TOUCHED;
	splx(s);
#ifdef	CACHE_DEBUG
	esp_dumpcache("esp_findentry - after");
#endif
	return(*a_sc);
} /* esp_findentry */

/* 
 * Remove an entry from the cache map.
 * Move to the begining of the LRU list with the used bit reset.
 */
esp_removeentry(server)
	struct vmtpeid server;
{
	register struct vmtpsce **a_sc1, *sc2, *sc3;
	register int s;

#ifdef	ESP_DEBUG
	printf("esp_removeentry(): called\n");
	vmtp_dumpeid(&server,"server","esp_removeentry");
#endif

#ifdef	CACHE_DEBUG
	esp_dumpcache("esp_removeentry - before");
#endif
	s = splimp();
	a_sc1 = vecachemap + esp_hash(&server);
	while (*a_sc1 != NULL && !vmtp_sameeid((*a_sc1)->ve_server, server)) {
		a_sc1 = &((*a_sc1)->ve_nextmap);
	}

	if (*a_sc1 != NULL) {
		/* remove from map */
		sc2 = *a_sc1;
		*a_sc1 = (*a_sc1)->ve_nextmap;
		sc2->ve_nextmap = NULL;

		/* 
		 * Find it in the LRU list and move it to its beginning
		 */
		sc3 = vesceLRU.first;
		if (sc3 != sc2) {
			while (sc3 && sc3->ve_next != sc2)
				sc3 = sc3->ve_next;
			if (!sc3)
				panic("esp_removeentry");

			sc3->ve_next = sc2->ve_next;
			if (sc2->ve_next == NULL) {
				/* update last pointer */
				vesceLRU.last = sc3;
			}
		}
		sc2->ve_iflags &= ~VEIF_USED;
		sc2->ve_next = vesceLRU.first;
		vesceLRU.first = sc2;
	}

	splx(s);
#ifdef	CACHE_DEBUG
	esp_dumpcache("esp_removeentry - after");
#endif
} /* esp_removeentry */

/*
 * Periodically called to free up some space in the cache
 * The goal is to avoid freeing space on demand, so we always have a
 * portion of the cache empty.
 *
 * For now just the first entry is freed.
 */
vmtp_cachetimeo()
{
	register struct vmtpsce *sc;
	register int s = splimp();

	sc = vesceLRU.first;
	if (entry_used(sc)) {
#ifdef	ESP_DEBUG
		printf("esp_cachetimeo(): grabbing old entry\n");
		vmtp_dumpeid(&sc->ve_server,"sc->ve_server","esp_allocentry");
#endif

		esp_removeentry(sc->ve_server);
	}
	splx(s);

	timeout(vmtp_cachetimeo, (caddr_t)0, hz/ESP_CACHEFREQ);
} /* vmtp_cachetimeo */
