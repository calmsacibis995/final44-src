/*
 *  isis_globals.h,v 1.11 1993/01/07 22:39:23 jch Exp
 */

/* %(Copyright.header) */


#ifndef _globals_h
#define _globals_h

#include "isis.h"

#ifndef EXTERN
#define EXTERN extern
#endif

EXTERN  RoutingModuleState              routingModuleState;

/*
 *	The ID of this intermediate system 
 */
EXTERN SystemID6		systemID;

/*
 *	The area addresses configured for this system
 */
EXTERN AreaAddrList	systemAreaAddrs;

/*
 *	Maximum size of L1 and L2 LSPs and SNPs originated by this
 *	system.
 */
EXTERN u_short 	origL1LSPBufSize;
EXTERN u_short 	origL2LSPBufSize;
EXTERN u_short	dataLinkBlocksize;	/* TODO: on per circuit ? */

/*
 *	Type of system. Should only have value L1IS or L2IS
 */
EXTERN SystemType	systemType;

/*
 *	Holding timer (in seconds)
 */
EXTERN u_short	sysHoldingTimer;

/*
 *	Rate (in seconds) for transmitting ISH and IIH pdus
 */
EXTERN u_short  sysISHInterval;                 /* system wide default */
EXTERN u_short  sysIIHInterval;                 /* system wide default */
EXTERN u_short  sysDRIIHInterval;               /* for designated router */
EXTERN u_short  sysPollESHelloRate;
EXTERN u_short  sysDefaultESHelloTimer;

/*
 *	Parameters which control the flooding and generation of LSPs
 */
EXTERN u_short	minLSPGenInterval;		/* min time between generations of an LSP */
EXTERN u_short	maxLSPGenInterval;		/* max time between generations of an LSP */
EXTERN u_short	minBLSPXmitInterval;	/* transmission on broadcast circuit */
EXTERN u_short	minLSPXmitInterval;		/* transmission on pt 2 pt circuit */
EXTERN u_short	BLSPThrottle;			/* max # of LSPs to xmit per circuit
										   per minBLSPXmitInterval */
EXTERN u_short	maximumAge;				/* number of seconds fore LSP expired*/
EXTERN u_short	completeSNPInterval;
EXTERN u_short	partialSNPInterval;
EXTERN u_short	zeroAgeLifetime;
EXTERN u_short  waitingTime;                    /* time to stay in overload state */

#define	minBroadcastLSPXmitInterval	33 /* milliseconds */

/*
 *	The list of circuits configured into the system
 */
EXTERN CircuitEntry	*circuitList[MaximumCircuits];

/*
 *	Logging device
 */
EXTERN Logger debugLog;
EXTERN int		dumpDBinterval;

/*
 *	LSPs for this system
 */
LSPGroup	*L1LSP, *L2LSP;
AgeList		*normalLSPAge, *deletedLSPAge;

/*
 *	Multicast addresses
 */
EXTERN MACAddress	AllL1ISmac, AllL2ISmac, AllESmac;

/*
 * Our task (whatever it is at the time).
 */
EXTERN task *isis_task;

/*
 * Our tracing options.
 */
EXTERN trace *isis_trace_options;
EXTERN const bits isis_trace_types[];

/* 
 * Preferences for gated (L1 higher preference than L2).
 */
EXTERN pref_t isis_preference[3];

/* 
 * Mode of operation (set by parser).
 */
EXTERN int ip_supported;
EXTERN int clnp_supported;

/*
 * Import and export policy (set by parser).
 */
EXTERN adv_entry *isis_import_list_ip;
EXTERN adv_entry *isis_import_list_iso;
EXTERN adv_entry *isis_export_list_ip;
EXTERN adv_entry *isis_export_list_iso;

/*
 * Flags set by reception of LSPs.
 */
EXTERN int runL1spf;
EXTERN int runL2spf;
EXTERN int adjustPrefsOnly;

#endif /* _globals_h */


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
