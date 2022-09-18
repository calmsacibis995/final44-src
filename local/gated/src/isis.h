/*
 *  isis.h,v 1.11 1993/01/07 22:37:58 jch Exp
 */

/* %(Copyright.header) */


#ifndef _isis_h
#define _isis_h

#include "isis_pdus.h"
#include "isis_lsp.h"

/*
 *	Contains a list of items that are to be aged. List is maintained
 *	in acending order of time-to-live, (with deltas rather than absolutes
 *	used between nodes. When an item's time-to-live reaches zero, the
 *	delete function is called with the item as argument.
 */
typedef struct _AgeList {
	DLList	links;
	PTIF	delete;
	u_short	ttlOffset;		/* byte offset into 'item' of ttl field */
} AgeList;

typedef enum {ManualConfig, AutoConfig} ConfigurationType;
typedef enum {AdjInitializing, AdjUp, AdjFailed} AdjacencyState;
typedef enum {Unknown, ES, IS, L1IS, L2IS} SystemType;
typedef enum {HoldingTimerExpired, ChecksumError, OneWayConnection,
	CircuitDisabled, VersionSkew, AreaMismatch, TooManyLANIS,
	TooManyLANES, WrongSystemType, IDMismatch} ReasonCode;
typedef enum {Broadcast, Pt2Pt} CircuitType;

/* TODO: maybe make this a union to clarify what is used for IIH and ESH */
typedef struct _AdjacencyEntry {
	DLList			links;
	u_short			name;		/* unique identifier within circuit */
	ConfigurationType	type;
	struct _CircuitEntry	*circuit;	/* back pointer to circuit */
	AdjacencyState		state;
	struct _AdjacencyEntry	*hashNext;
	u_short			hashIndex;	/* index into hashtable */
	MACAddress		neighborMAC;	/* broadcast circuit only */
	u_char			LANPriority;	/* broadcast circuit only */
	SystemType		adjacencyType;	/* type of adjacency */
	SystemID6		neighborSysID;	/* from IIH */
	SystemID7		desigLANID;	/* from IIH */
	IPAddrList		ipaddrs;	/* from IIH (DUAL) */
	Boolean			level2Only;	/* true -> L2 link only */
	u_short			holdingTime;	/* original value from IIH, ESH, ISH */
	u_short			remainingTime;	/* time to live */
	u_short			numIds;		/* ES only */
	u_char			*neighborInfo;	/* either IS areas or ES ids */
} AdjacencyEntry;

/* adjacencies which should be freed upon next run on spf algorithm */
typedef struct _OldAdjacencyEntry {
	DLList	links;
} OldAdjacencyEntry;

#define CircuitNameLen	8

typedef struct _CircuitEntry {
	char		name[CircuitNameLen];	/* name of circuit, ie. un0 */
	int		kernindex;		/* kernel index of circuit */
	int		summarized;		/* true if already summarized (broadcast only) */
	int		fd;			/* socket */
	CircuitType	circuitType;		/* pt2pt or broadcast */
	SystemID6	myMAC;			/* MAC address of this system */
	u_short		helloInterval;		/* clause 11.1.3 */
	u_short		ISIShelloInterval;	/* clause 11.1.3 */
	u_short		holdingTimer;		/* HT for this system */
	MetricList	l1Metric;
	MetricList	l2Metric;
	u_char		l1Priority;		/* for becoming LAN L1 designated IS */
	u_char		l2Priority;		/* for becoming LAN L2 designated IS */
	Boolean		manualL2Only;		/* true if used for L2 only */
	Boolean		up;			/* true if circuit is UP */
	u_char		localId;		/* locally assigned circuit ID */
	SystemID7	circuitId;		/* LAN ID of L1 designated sys, or the ID of the circuit (if pt-to-pt) */
	SystemID7	l2CircuitId;		/* LAN ID of the L2 designated sys */
	AgeList		*esAdjs;		/* ES adjacencies */
	AgeList		*isAdjs;		/* IS adjacencies */
	LSPGroup	*l1PLSP;		/* L1 pseudonode LSP for this circuit */
	LSPGroup	*l2PLSP;		/* L2 pseudonode LSP for this circuit */

	/* the next two boolean control whether pseudonode LSPs are generated */
	Boolean		l1DR;			/* True if L1 designated router */
	Boolean		l2DR;			/* True if L2 designated router */

	Counter		circuitChanges;		/* # circuit up/down */
	Counter		adjacencyEvents;	/* # adjacency state change events */
	Counter		initFailures;		/* # initialization failure events */
	Counter		rejAdjs;		/* # rejected adjacency events */
	Counter		corruptedLSPs;		/* # corrupted LSPs received */
	Counter		l1DesignateChanges;	/* # L1 designated IS changes */
	Counter		l2DesignateChanges;	/* # L2 designated IS changes */
	Counter		pdusSent;
	Counter		pdusReceived;
	struct _CircuitEntry *next;
	u_char		simSubnetId;		/* used by simulator only */
	int		(*transmitFunc)();	/* packet transmission function */
	IPAddrList	ipAddrs;		/* list of IP addresses for this circuit */
	LSEntry		*lastFlooded[2];	/* last LSP flooded on this circuit */
	task		*task;			/* task handling timers for this circuit */
	char		task_name[40];		/* hack to hold task name in heap */
	task_timer	*timer_l1iih;		/* L1 IIH timer */
	task_timer	*timer_l2iih;		/* L2 IIH timer */
	task_timer	*timer_p2piih;		/* P2P IIH timer */
} CircuitEntry;


#define ISIS_INTERNAL           1
#define ISIS_EXTERNAL           2
#define ISIS_SUMMARY            3
#define ISIS_AUTOSUMMARY        4

#define	ISIS_LIMIT_METRIC	1, 63

#endif	/* _isis_h */


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
