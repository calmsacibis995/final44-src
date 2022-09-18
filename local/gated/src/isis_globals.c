/*
 *  isis_globals.c,v 1.11 1993/01/07 22:39:21 jch Exp
 */

/* %(Copyright.header) */


#define EXTERN 

#include "include.h"
#include "isis_includes.h"

char areaAddr[] = { 11, 0x47, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, /* res */
	0x01, 0x01 /* RD */};

/*
 *	these multicast addrs may not work on any 802.5 networks
 *	that have MSb first transmission order
 */
static MACAddress	l1is[] = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x14};
static MACAddress	l2is[] = {0x01, 0x80, 0xc2, 0x00, 0x00, 0x15};
static MACAddress	is[] = {0x09, 0x00, 0x2b, 0x00, 0x00, 0x05};
static MACAddress	es[] = {0x09, 0x00, 0x2b, 0x00, 0x00, 0x04};

/*
 *	define 'addr' as an area addr for this router
 *
 *	ASSUMES THE FIRST BYTE OF ADDR IS THE LENGTH IN BYTES!
 */
void
setAreaAddr __PF1(addr, u_char *)
{
	int i;
	AreaAddr *AA;

	for (i=0; i<systemAreaAddrs.count; i++) {
		AA = retrieveAreaAddr(systemAreaAddrs.areaAddr[i]);
		if ((AA) && (AA->len == *addr) && equalID(addr+1, AA->addr, *addr)) {
			/* we have a match */
			return;
		}
	}

	if (systemAreaAddrs.count == MaximumAreaAddresses) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("Maximum Area Addresses exceeded (%d), ignoring ...", 
			      MaximumAreaAddresses));
		return;
	}
	systemAreaAddrs.areaAddr[systemAreaAddrs.count++] = storeAreaAddr(addr);
}

GlobalCounters  isisCounters;

void
initGlobals __PF1(isis_initial_config, int)
{
	if (isis_initial_config) {
		copyID(l1is, AllL1ISmac, 6);
		copyID(l2is, AllL2ISmac, 6);
		copyID(es, AllESmac, 6);
        	bzero((caddr_t) &isisCounters, sizeof(isisCounters));
		/* 	setIPSystemID(gethostid(), systemID);*/
		/* 
		if (systemID[0] == 0)
			sprintf((char *) systemID, "%d", getpid());
		*/
		if (systemType == Unknown)
			systemType = L1IS;
        	origL1LSPBufSize = origL2LSPBufSize = dataLinkBlocksize = 1492;
		sysHoldingTimer = 20;			/* adj hold time */
        	sysISHInterval = 10;
        	sysIIHInterval = 3;
        	sysDRIIHInterval = 1;
        	sysPollESHelloRate = 50;                /* seconds */
        	sysDefaultESHelloTimer = 600;   	/* seconds */
		minLSPGenInterval = 30;			/* min between LSP generations */
		maxLSPGenInterval = 900;		/* max between LSP generations */
		minLSPXmitInterval = 2;			/* min between LSP propagations (from given source) */
		minBLSPXmitInterval = 5;		/* same, but on broadcast circuits */
		BLSPThrottle = 50;			/* packets */
		maximumAge = 1200;			/* of LSP */
		completeSNPInterval = 10;		/* complete SNP xmit time for broadcast media */
		partialSNPInterval = 2;			/* seconds */
		zeroAgeLifetime = 60;			/* expired LSP header retain time after flood */
        	waitingTime = 60;			/* time to stay in overload state */
		dumpDBinterval = 30;			/* seconds */
        	routingModuleState = ModuleUp;
	}

	/* DTS 12-8-90 check if any of the above have been reset by parser */
	isis_check_parms();

	if (isis_initial_config) {
		runL1spf = runL2spf = 0;
		LSPInit();	/* STEVE XXX - check interaction with updateAreaSummary (may need work for reconfig) */
		setTimer(dumpDBinterval, dumpDB);
		/*
	 	 * Start timers to age things.
	 	 */
		setTimer(1, ageListAge, NULL);
	}
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
