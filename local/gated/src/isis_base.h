/*
 *  isis_base.h,v 1.11 1993/01/07 22:39:03 jch Exp
 */

/* %(Copyright.header) */


#ifndef _base_h
#define _base_h

#include <sys/time.h>

#ifdef	notdef
#include "isis_netd.h"
#endif	/* notdef */
#include "isis_troll.h" /* say a prayer */
#define REALD 0
#define NETD 1
#define TROLLD 2
#include "isis_dll.h"
#include "isis_rtrace.h"

/*
 *	"Architectural Constants"
 */
#define MaximumAreaAddresses		3
#define	AreaAddressStoreSize		100
#define	MaximumAreaAddressLen		13
#define MaximumCircuits			10
/* #define	SequenceModulus			(u_int) 4294967295 */
#define	SequenceModulus			(u_int32) 0xffffffff
#define	MaxPacketSize			4096
#define	IntraDomainRPD			0x83
#define	ESISRPD				0x82
#define HoldingMultiplier               3
#define ISISHoldingMultiplier           10
#define	VersionProtoID			1
#define	Version				1
#ifndef USE_SNMP_OK_NOTOK
#define OK				1 
#define NOTOK				0 
#endif
#define	True				1
#define	False				0
#define	IDOFF				6		/* offset of local ID */
#define	OSI_NLPID			0x81		/* STEVE - this is the ISO 9577 value */
#define	IP_NLPID			0xCC		/* STEVE - this is the ISO 9577 value */


/*
 *	Size of the adjacency hash table; TODO: some comments on sizing
 */
#define AdjHashTableSize	100

/*
 *      The LSP hash table size. This table is used to hash all LSPs at the
 *      given level (hash is based upon sourceID address). Chained bucket
 *      hashing is used.
 */
#define	L1HashTableSize		100
#define L2HashTableSize		50

/*
 *	Use these types for PDU declarations. They are arrays so that
 *	the structures that result do not have padding that would
 *	screw up the packet format
 */
typedef u_char Unsigned8;
typedef u_char Unsigned16[2];
typedef u_char Unsigned32[4];

#define hostToU16(s, u) \
    do { \
        register u_short Xtmp = (u_short)(s); \
        register byte *Xcp = (byte *)(u); \
        *Xcp++ = Xtmp >> 8; \
        *Xcp = Xtmp; \
    } while (0)

#define hostToU32(l, u) \
    do { \
        register u_long Xtmp = (u_long)(l); \
        register byte *Xcp = (byte *)(u); \
        *Xcp++ = Xtmp >> 24; \
        *Xcp++ = Xtmp >> 16; \
        *Xcp++ = Xtmp >> 8; \
        *Xcp = Xtmp; \
    } while (0)

#define U16toHost(u, s) \
    do { \
        register u_short Xtmp; \
        register byte *Xcp = (byte *)(u); \
        Xtmp = ((u_short)(*Xcp++)) << 8; \
        Xtmp |= (u_short)(*Xcp); \
        (s) = Xtmp; \
    } while (0)

#define U32toHost(u, l) \
    do { \
        register u_long Xtmp; \
        register byte *Xcp = (byte *)(u); \
        Xtmp = ((u_long)(*Xcp++)) << 24; \
        Xtmp |= ((u_long)(*Xcp++)) << 16; \
        Xtmp |= ((u_long)(*Xcp++)) << 8; \
        Xtmp |= (u_long)(*Xcp); \
        (l) = Xtmp; \
    } while (0)

	
/*
 *	Generic pointer to integer returning function
 */
typedef int			(* PTIF)();
typedef	caddr_t 	AuthInfo;		/* Authentication Information */
typedef u_char		Boolean;
typedef u_char		SystemID6[6];
typedef u_char		SystemID7[7];
typedef SystemID6	MACAddress;
typedef u_char 		Metric;
typedef u_int		Counter;
typedef long		IPAddress;
typedef u_int		IPSubnetMask;
typedef u_int		SeqNumber;

typedef enum {ModuleUp, ModuleDown} RoutingModuleState;

#define MetricUnsupported	0x80	/* bit that indicates unsupported metric */

#ifndef max
#define max(a,b) ((a) < (b) ? (b) : (a))
#endif
#ifndef min
#define min(a,b) ((a) < (b) ? (a) : (b))
#endif

#define castMalloc(cast, size)\
	((cast)mallocOrDie(size))

#ifdef	ibm032
#define Offset(type, field)	_offsetof(type, field)
#else
#define Offset(type, field) /* ala fldoff in struct.h */ \
	((unsigned int) (( &(((type *)NULL)->field))  ))
#endif

#define timeStamp	getTimeOfDay()

#define copyID(from, to, len)\
	bcopy((caddr_t)(from), (caddr_t)(to), len)

#define equalID(a, b, len)\
	(!bcmp((caddr_t)a, (caddr_t)b, len))

#define compareID(a, b, len)\
	arrayCmp((u_char *) a, (u_char *) b, len)

#define LSPIDcmp(a,b) /* replace int LSPIDcmp(LSPID *a,LSPID *b) */ \
	arrayCmp((u_char *) a, (u_char *) b, sizeof(LSPID))

#define BroadcastLSPThrottle\
	min(10, (1000/minBroadcastLSPXmitInterval))

typedef struct _globalCounters {
        Counter         pduFormatErrors;
        Counter         corruptLSPDetected;
        Counter         l1LSPOverload;
        Counter         l2LSPOverload;
        Counter         manualAreaDropped;
        Counter         exceedSeqNum;
        Counter         seqNumSkipped;
        Counter         purgeOwnLSP;
        long    	option;         /* blocks allocated */
        long    	optiondata;
        long    	prefIP;
        long    	prefISO;
        long    	lspattr;
        long    	tsi_info;
        long    	spfNode;        
        long    	intnode;        
        long    	ipleaf;        
        long    	isoleaf;        
	long		spfAA;
	long		lspdescs;
	long		lsentries;
	long		sumnodes;
	long		lseChangeList;
	long		isis_announced;
	long		adjEntries;	/* other allocated */
	long		adjNeighborInfo;
	long		agelists;
	long		circuitEntries;
	long		lspbufs;
	long		lspbytes;
	long		ipext;		/* option type breakdown */
	long		ipint;
	long		isopref;
	long		leaves;	
	long		idrpi;
	long		aa;
	long		isn;
	long		esn;
	long		ipintf;
	long		protosup;
	long		ipsum;
	long		pdl2is;
	long		ipauth;
	long		auth;
} GlobalCounters;

extern GlobalCounters   isisCounters;

/*
 * Definitions for exported update types.  It is either an initial update,
 * a flash update or a newpolicy update.
 */
#define ISIS_NEWPOLICY	(0)
#define ISIS_INITIAL	(1)
#define ISIS_FLASH	(2)

#endif	/* _base_h */


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
