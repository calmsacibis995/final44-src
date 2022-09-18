/*
 *  $Header: /vol/src/devel/gated/master/gated/src/isis_mib.h,v 1.4 1993/07/16 16:41:10 jch Exp $
 */

/*
**	isis_mib.h
**
**	This file contains isis mib related definitions.
**
**
**	John Chu <jychu@watson.ibm.com>
**
*/


#define TRUE	1
#define FALSE	0


typedef struct OIDentifier *ObjectID;		/* ASN.1 OBJECT IDENTIFIER */


/* C types for ASN.1 or SMI types */
typedef int		Integer;		/* ASN.1 INTEGER */
typedef unsigned long	TimeTicks;		/* SMI TimeTicks */
#ifdef	USE_ISIS_MIB_COUNTER_DEF
typedef unsigned long	Counter;		/* SMI Counter */
#endif
typedef unsigned long	Gauge;			/* SMI Gauge */
typedef unsigned long	IpAddress;		/* SMI IpAddress */

typedef struct qbuf 	*OctetStr;		/* ASN.1 OCTET STRING */


/* Structure to model an object type */
typedef struct object_type ObjectType;

/* Structure to model an object instance */
typedef struct object_instance ObjectInstance;


/* ISIS mib table entries */
#define MAXOIDSIZE	64		/* a reasonal value */
typedef struct	{
	int	oid_nelem;		/* number of sub-identifers */
	unsigned int oid_elements[MAXOIDSIZE];	/* list of sub-identifers */

} ObjectIdentifier;


#define MAXOCTETSTRINGSIZELONG	256		/* number of bytes allocated */
#define MAXOCTETSTRINGSIZESHORT 32		/* number of bytes allocated */

typedef struct 	{
	unsigned short len;			/* actual length in contents */
	unsigned short maxlen;			/* max length defined by isis mib */
	unsigned char contents[MAXOCTETSTRINGSIZELONG];

} LongOctetString;

typedef struct 	{
	unsigned short len;			/* actual length in contents */
	unsigned short maxlen;			/* max length defined by isis mib */
	unsigned char contents[MAXOCTETSTRINGSIZESHORT];

} ShortOctetString;

/* Types defined in the mib */
typedef ShortOctetString 	OSINSAddress;
typedef ShortOctetString 	SNPAAddress;
typedef ShortOctetString 	NSAPPrefix;
typedef ShortOctetString 	SNPAPrefix;
typedef ShortOctetString 	SystemID;
typedef Integer			ExistState;
typedef Integer			OperState;
typedef Integer 		LSPBuffSize;
typedef Integer			LevelState;
typedef LongOctetString 	Password;
typedef Integer			SupportedProtocol;
typedef Integer			DefaultMetric;
typedef Integer			OtherMetric;
typedef Integer			MetricType;
typedef Integer			PathCost;
typedef ShortOctetString 	CircuitID;
typedef Integer			ISPriority;
typedef Integer			TOS;

/* The System Group, mandatory */

/* Maximum Number of Area Addresses, per ISO/IEC 10589:1992 (E), 7.1.5 */
#define MAXAREAADDRESSES	4	/* it should be equal or larger than the number 
					   setable by the system management */

/* The Level 1 Manual Area Address Entry and Table */
typedef struct 	{
	Integer		isisManAreaAddrSysInstance;
        OSINSAddress    isisManAreaAddr;
	ExistState 	isisManAreaAddrExistState;

} IsisManAreaAddrEntry;

typedef struct	{	/* sorted by isisManAreaAddr */
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisManAreaAddrEntry *pentry[MAXAREAADDRESSES];
	IsisManAreaAddrEntry isisManAreaAddrEntry[MAXAREAADDRESSES];
} IsisManAreaAddrTable;


/* The Level 1 Area Address Entry and Table */
typedef struct	{
	Integer		isisAreaAddrSysInstance;
        OSINSAddress    isisAreaAddr;

} IsisAreaAddrEntry;

typedef struct	{	/* sorted by isisAreaAddr */
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisAreaAddrEntry *pentry[MAXAREAADDRESSES];
	IsisAreaAddrEntry isisAreaAddrEntry[MAXAREAADDRESSES];
} IsisAreaAddrTable;


/* The System Table Entry */
typedef struct 	{
        Integer		isisSysInstance;			/* planted */
	ExistState      isisSysExistState;			/* planted */
	ShortOctetString isisSysVersion;			/* planted */
	Integer         isisSysType;				/* planted */
	SystemID        isisSysID;				/* planted */
	Integer         isisSysMaxPathSplits;			/* unfeatured */
	Integer         isisSysMinLSPTransInt;			/* jaded */
	Integer         isisSysMaxLSPGenInt;			/* jaded */
	Integer         isisSysMinBroadLSPTransInt;		/* jaded */
	Integer         isisSysCompSNPInt;			/* jaded */
	LSPBuffSize     isisSysOrigL1LSPBuffSize;		/* jaded */
	Integer         isisSysMaxAreaAddresses;		/* jaded */
	Integer         isisSysMinLSPGenInt;			/* jaded */
	Integer         isisSysPollESHelloRate;			/* jaded */
	Integer         isisSysPartSNPInt;			/* jaded */
	Integer         isisSysWaitTime;			/* jaded */
	Integer	        isisSysDRISISHelloTimer;		/* jaded */
	OperState       isisSysOperState;			/* planted */
	LevelState      isisSysL1State;				/* planted */
        Counter         isisSysCorrLSPs;			/* planted */
        Counter         isisSysLSPL1DbaseOloads;		/* planted */
        Counter         isisSysManAddrDropFromAreas;
        Counter         isisSysAttemptToExMaxSeqNums;		/* planted */
        Counter         isisSysSeqNumSkips;
        Counter         isisSysOwnLSPPurges;			/* planted */
        Counter         isisSysIDFieldLenMismatches;
        Counter         isisSysMaxAreaAddrMismatches;
	LSPBuffSize	isisSysOrigL2LSPBuffSize;		/* jaded */
	LevelState      isisSysL2State;				/* planted */
        Counter         isisSysLSPL2DbaseOloads;		/* planted */
        Password        isisSysAuthAreaTransPwd;		/* unfeatured */
	Password        isisSysAuthDomainTransPwd;		/* unfeatured */
        Counter         isisSysAuthFails;			/* unfeatured */
	IsisManAreaAddrTable	isisManAreaAddrTable;		
	IsisAreaAddrTable	isisAreaAddrTable;		

} IsisSysEntry;


/* The System Integrated Group */
/* The System Protocol Supported Table */
typedef struct	{
	Integer		isisSysProtSuppSysInstance;
        SupportedProtocol isisSysProtSuppProtocol;
        ExistState      isisSysProtSuppExistState;

} IsisSysProtSuppEntry;

#define PROTSUPP_LOWEST		129		/* lowest protocol number */

/* Maximum Protocols Supported Per System Instance */
#define MAXPROTSUPPPERINSTANCE	4

typedef struct 	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisSysProtSuppEntry 	*pentry[MAXPROTSUPPPERINSTANCE];
	IsisSysProtSuppEntry	isisSysProtSuppEntry[MAXPROTSUPPPERINSTANCE];

} IsisSysProtSuppTable;


/* The Level 2 IP Group */
/* The Level 2 Summary Address Table */
typedef struct	{
	Integer		isisL2SummAddrSysInstance;
        IpAddress       isisL2SummAddress;
        IpAddress       isisL2SummAddrMask;
        ExistState      isisL2SummAddrExistState;
        OperState       isisL2SummAddrOperState;
        DefaultMetric   isisL2SummAddrDefaultMetric;
        OtherMetric     isisL2SummAddrDelayMetric;
        OtherMetric     isisL2SummAddrExpenseMetric;
        OtherMetric     isisL2SummAddrErrorMetric;

} IsisL2SummAddrEntry;

#define MAXL2SUMMADDRPERINSTANCE	4

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisL2SummAddrEntry 	*pentry[MAXL2SUMMADDRPERINSTANCE];
	IsisL2SummAddrEntry	isisL2SummAddrEntry[MAXL2SUMMADDRPERINSTANCE];

} IsisL2SummAddrTable;


/* The Authentication Group */
/* The Level 1 Area Receive Password Table */
typedef struct	{
	Integer		isisAuthAreaRecPwdSysInstance;
        Password        isisAuthAreaRecPwd;
        ExistState      isisAuthAreaRecPwdExistState;

} IsisAuthAreaRecPwdEntry;

#define MAXAUTHAREARECPWDPERINSTANCE	4

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisAuthAreaRecPwdEntry	*pentry[MAXAUTHAREARECPWDPERINSTANCE];
	IsisAuthAreaRecPwdEntry	isisAuthAreaRecPwdEntry[MAXAUTHAREARECPWDPERINSTANCE];

} IsisAuthAreaRecPwdTable;

/* The Level 2 Domain Receive Password Table */
typedef struct	{
	Integer		isisAuthDomainRecPwdSysInstance;
        Password        isisAuthDomainRecPwd;
        ExistState      isisAuthDomainRecPwdExistState;

} IsisAuthDomainRecPwdEntry;

#define MAXAUTHDOMAINRECPWDPERINSTANCE	4

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisAuthDomainRecPwdEntry *pentry[MAXAUTHDOMAINRECPWDPERINSTANCE];
	IsisAuthDomainRecPwdEntry isisAuthDomainRecPwdEntry[MAXAUTHDOMAINRECPWDPERINSTANCE];

} IsisAuthDomainRecPwdTable;


/* The Partition Repair Group */
/* The Partition Repair Table */
typedef struct 	{
	Integer		isisPartRepSysInstance;
	Integer         isisPartRepMaxVirtAdj;
        SystemID        isisPartRepDesL2IS;
        Counter         isisPartRepVirtLinkChgs;

} IsisPartRepEntry;

#define MAXPARTREPPERINSTANCE	1

typedef struct 	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisPartRepEntry *pentry[MAXPARTREPPERINSTANCE];
	IsisPartRepEntry isisPartRepEntry[MAXPARTREPPERINSTANCE];

} IsisPartRepTable;

/* The Partition Area Address Table */
typedef struct	{
	Integer		isisPartAreaAddrSysInstance;
        OSINSAddress    isisPartAreaAddr;

} IsisPartAreaAddrEntry;

#define MAXPARTAREAADDRPERINSTANCE	4

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisPartAreaAddrEntry *pentry[MAXPARTAREAADDRPERINSTANCE];
	IsisPartAreaAddrEntry isisPartAreaAddrEntry[MAXPARTAREAADDRPERINSTANCE];

} IsisPartAreaAddrTable;

/* The Virtual Adjacency Table */
typedef struct	{
	Integer		isisVirtAdjSysInstance;
	Integer         isisVirtAdjIndex;
        OSINSAddress    isisVirtAdjNET;
        PathCost        isisVirtAdjMetric;

} IsisVirtAdjEntry;

#define MAXVIRTADJPERINSTANCE	4

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisVirtAdjEntry *pentry[MAXVIRTADJPERINSTANCE];
	IsisVirtAdjEntry isisVirtAdjEntry[MAXVIRTADJPERINSTANCE];

} IsisVirtAdjTable;



/* The Circuit Authentication Group */
/* The Circuit Receive Password Table */
typedef struct	{
	Integer		isisCircAuthRecPwdSysInstance;
	Integer		isisCircAuthRecPwdCircIndex;
        Password        isisCircAuthRecPwd;
        ExistState      isisCircAuthRecPwdExistState;

} IsisCircAuthRecPwdEntry;

#define MAXCIRCAUTHRECPWDPERCIRC	2

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisCircAuthRecPwdEntry	*pentry[MAXCIRCAUTHRECPWDPERCIRC];
	IsisCircAuthRecPwdEntry	isisCircAuthRecPwdEntry[MAXCIRCAUTHRECPWDPERCIRC];

} IsisCircAuthRecPwdTable;


/* The IS Adjacency Group, mandatory */
/* The IS Adjacency Area Address Table Entry */
typedef struct 	{
	Integer 	isisISAdjAreaAddrSysInstance;
	Integer         isisISAdjAreaAddrCircIndex;
	Integer         isisISAdjAreaAddrAdjIndex;
        OSINSAddress    isisISAdjAreaAddress;

} IsisISAdjAreaAddrEntry;

/* Maximum IS Adjacency Area Addresses Per IS Adjacency */
#define MAXAREAADDRESSESPERISADJ	4

typedef struct	{	/* sorted by isisISAdjAreaAddress */
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisISAdjAreaAddrEntry 	*pentry[MAXAREAADDRESSESPERISADJ];
	IsisISAdjAreaAddrEntry	isisISAdjAreaAddrEntry[MAXAREAADDRESSESPERISADJ];

} IsisISAdjAreaAddrTable;


/* The IS Adjacency IP Group */
/* The IS Adjacency IP Address Table */
typedef struct	{
	Integer		isisISAdjIPAddrSysInstance;
	Integer		isisISAdjIPAddrCircIndex;
	Integer		isisISAdjIPAddrAdjIndex;
        IpAddress       isisISAdjIPAddress;

} IsisISAdjIPAddrEntry;

#define MAXISADJIPADDRPERISADJ	10	/* defined by IPAddrList in isis_pdus */

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisISAdjIPAddrEntry 	*pentry[MAXISADJIPADDRPERISADJ];
	IsisISAdjIPAddrEntry	isisISAdjIPAddrEntry[MAXISADJIPADDRPERISADJ];

} IsisISAdjIPAddrTable;


/* The IS Adjacency Integerated Group */
/* The IS Adjacency Protocol Supported Table */

typedef struct 	{
	Integer		isisISAdjProtSuppSysInstance;
	Integer		isisISAdjProtSuppCircIndex;
	Integer		isisISAdjProtSuppAdjIndex;
        SupportedProtocol isisISAdjProtSuppProtocol;

} IsisISAdjProtSuppEntry;

#define MAXISADJPROTSUPPPERISADJ	4

typedef struct 	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisISAdjProtSuppEntry 	*pentry[MAXISADJPROTSUPPPERISADJ];
	IsisISAdjProtSuppEntry	isisISAdjProtSuppEntry[MAXISADJPROTSUPPPERISADJ];
			
} IsisISAdjProtSuppTable;
 

/* The IS Adjacency Table Entry */
typedef struct 	{
        Integer                isisISAdjSysInstance;		/* planted */
	Integer                isisISAdjCircIndex;		/* planted */
	Integer                isisISAdjIndex;			/* planted */
	Integer                isisISAdjState;			/* planted */
	SNPAAddress            isisISAdjNeighSNPAAddress;	/* planted */
	Integer                isisISAdjNeighSysType;		/* planted */
	ShortOctetString       isisISAdjNeighSysID;		/* planted */
	Integer                isisISAdjUsage;			/* unknown */
	Integer                isisISAdjHoldTimer;		/* planted */
	ISPriority             isisISAdjNeighPriority;		/* planted */
	IsisISAdjAreaAddrTable isisISAdjAreaAddrTable;
	IsisISAdjIPAddrTable   isisISAdjIPAddrTable;
	IsisISAdjProtSuppTable isisISAdjProtSuppTable;

} IsisISAdjEntry;

/* Maximum IS Adjacencies Per Circuit */
#define MAXISADJPERCIRC		12	

typedef struct	{	/* sorted by isisISAdjCircIndex */
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisISAdjEntry	*pentry[MAXISADJPERCIRC];
	IsisISAdjEntry	isisISAdjEntry[MAXISADJPERCIRC];

} IsisISAdjTable;


/* The ES Adjacency Group */
/* The ES Adjacency Table */

typedef struct	{
	Integer		isisESAdjSysInstance;
	Integer		isisESAdjCircIndex;
	Integer		isisESAdjAdjIndex;
	Integer		isisESAdjType;
	Integer		isisESAdjState;
        SNPAAddress     isisESAdjNeighSNPAAddress;
        ExistState      isisESAdjExistState;
        SystemID        isisESAdjESID;

} IsisESAdjEntry;

#define MAXESADJPERCIRC		8

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisESAdjEntry	*pentry[MAXESADJPERCIRC];
	IsisESAdjEntry	isisESAdjEntry[MAXESADJPERCIRC];

} IsisESAdjTable;



/* The Reachable Address Group */
/* The Reachable Address Table */
typedef struct	{
	Integer		isisRASysInstance;
	Integer		isisRACircIndex;
	Integer		isisRAIndex;
        ExistState      isisRAExistState;
        OperState       isisRAOperState;
        NSAPPrefix      isisRAAddrPrefix;
	Integer		isisRAType;
	Integer		isisRAMapType;
        DefaultMetric   isisRADefMetric;
        OtherMetric     isisRADelMetric;
        OtherMetric     isisRAExpMetric;
        OtherMetric     isisRAErrMetric;
        MetricType      isisRADefMetricType;
        MetricType      isisRADelMetricType;
        MetricType      isisRAExpMetricType;
        MetricType      isisRAErrMetricType;
        SNPAAddress     isisRASNPAAddress;
        SNPAPrefix      isisRASNPAMask;
        SNPAPrefix      isisRASNPAPrefix;

} IsisRAEntry;

#define MAXRAPERCIRC	4

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisRAEntry	*pentry[MAXRAPERCIRC];
	IsisRAEntry	isisRAEntry[MAXRAPERCIRC];

} IsisRATable;



/* The IP Reachable Address Group */
/* The IP Reachable Address Table */
typedef struct	{
	Integer		isisIPRASysInstance;
	Integer		isisIPRACircIndex;
	Integer		isisIPRAIndex;
        IpAddress       isisIPRADest;
        IpAddress       isisIPRAMask;
        ExistState      isisIPRAExistState;
        OperState       isisIPRAOperState;
        DefaultMetric   isisIPRADefMetric;
        OtherMetric     isisIPRADelMetric;
        OtherMetric     isisIPRAExpMetric;
        OtherMetric     isisIPRAErrMetric;
        MetricType      isisIPRADefMetricType;
        MetricType      isisIPRADelMetricType;
        MetricType      isisIPRAExpMetricType;
        MetricType      isisIPRAErrMetricType;
        SNPAAddress     isisIPRASNPAAddress;

} IsisIPRAEntry;

#define MAXIPRAPERCIRC		4

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisIPRAEntry	*pentry[MAXIPRAPERCIRC];
	IsisIPRAEntry	isisIPRAEntry[MAXIPRAPERCIRC];

} IsisIPRATable;



/* The Circuit Group, mandatory */

/* Circuit IS entry */
typedef struct	{
	Integer         isisCircISSysInstance;	     
	Integer		isisCircISIndex;
        ExistState      isisCircISExistState;
        OperState       isisCircISOperState;
	Integer		isisCircISHoldTimerMult;
	Integer		isisCircISConfTimer;
	Integer		isisCircISSuggESConfTimer;
	Integer		isisCircISRedHoldTime;
	Integer		isisCircISMCAddr;
        Counter         isisCircISESReachChgs;
        Counter         isisCircISInv9542PDUs;

} IsisCircISEntry;


/* The Circuit Entry and Table */
typedef struct 	{
	Integer                isisCircSysInstance;		/* planted */
	Integer                isisCircIndex;			/* planted */
	Integer                isisCircIfIndex;			/* planted */
	OperState              isisCircOperState;
	ExistState             isisCircExistState;		/* planted */
	Integer                isisCircType;			/* planted */
	Integer                isisCircISISHelloTimer;		/* jaded */
	DefaultMetric          isisCircL1DefaultMetric;		/* jaded */
	OtherMetric            isisCircL1DelayMetric;		/* jaded */
	OtherMetric            isisCircL1ExpenseMetric;		/* jaded */
	OtherMetric            isisCircL1ErrorMetric;		/* jaded */
	Boolean                isisCircExtDomain;		/* unfeatured */
        Counter                isisCircAdjChanges;		/* planted */
        Counter                isisCircInitFails;		/* planted */
        Counter                isisCircRejAdjs;
        Counter                isisCircOutCtrlPDUs;		/* planted */
        Counter                isisCircInCtrlPDUs;		/* planted */
        Counter                isisCircIDFieldLenMismatches;
        Counter                isisCircMaxAreaAddrMismatches;
	DefaultMetric          isisCircL2DefaultMetric;		/* jaded */
	OtherMetric            isisCircL2DelayMetric;		/* jaded */
	OtherMetric            isisCircL2ExpenseMetric;		/* jaded */
	OtherMetric            isisCircL2ErrorMetric;		/* jaded */
	Boolean                isisCircManL2Only;		/* planted */
	ISPriority             isisCircL1ISPriority;		/* planted */
	CircuitID              isisCircL1CircID;		/* planted */
	SystemID               isisCircL1DesIS;			/* planted */
        Counter                isisCircLANL1DesISChanges;	/* planted */
	ISPriority             isisCircL2ISPriority;		/* planted */
	CircuitID              isisCircL2CircID;		/* planted */
	SystemID               isisCircL2DesIS;			/* planted */
        Counter                isisCircLANL2DesISChanges;	/* planted */
	Integer		       isisCircMCAddr;			/* 02new */
	CircuitID              isisCircPtToPtCircID;
	ObjectIdentifier       isisCircStaticCallInfo;
	OtherMetric            isisCircDACallDefMetInc;
	OtherMetric            isisCircDACallDelMetInc;
	OtherMetric            isisCircDACallErrMetInc;
	OtherMetric            isisCircDACallExpMetInc;
	Password               isisCircAuthTransPwd;		/* unfeatured */
        Counter                isisCircAuthFails;		/* unfeatured */
	IsisCircISEntry	       isisCircISEntry;
	IsisCircAuthRecPwdTable isisCircAuthRecPwdTable;
	IsisISAdjTable	       isisISAdjTable;
	IsisESAdjTable	       isisESAdjTable;
	IsisRATable	       isisRATable;
	IsisIPRATable	       isisIPRATable;

} IsisCircEntry;

#define MAXCIRCSPERINSTANCE 10	 	/* must conform with MaximumCircuits in 
				   	   isis_base.h */

typedef struct 	{	/* sorted by isisCircIndex */
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisCircEntry	*pentry[MAXCIRCSPERINSTANCE];
	IsisCircEntry   isisCircEntry[MAXCIRCSPERINSTANCE];

} IsisCircTable;


/* The Circuit IS Group */
/* The Circuit IS Table */

#define	MAXCIRCISPERNODE	4

typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisCircISEntry	*pentry[MAXCIRCISPERNODE];
	IsisCircISEntry	isisCircISEntry[MAXCIRCISPERNODE];

} IsisCircISTable;



/* Tables per instance of IS-IS */
typedef struct 	{
	IsisSysEntry		isisSysEntry;
        IsisSysProtSuppTable	isisSysProtSuppTable;
	IsisL2SummAddrTable	isisL2SummAddrTable;
	IsisAuthAreaRecPwdTable isisAuthAreaRecPwdTable;
	IsisAuthDomainRecPwdTable isisAuthDomainRecPwdTable;
	IsisPartRepTable	isisPartRepTable;
	IsisPartAreaAddrTable	isisPartAreaAddrTable;
	IsisVirtAdjTable	isisVirtAdjTable;
	IsisCircTable		isisCircTable;

} IsisMibEntry;


/* The Level 1 CLNP Destination Group */
/* The Level 1 CLNP Destination Table */
typedef struct	{
	SystemID	isisL1CLNPRouteDest;
        TOS		isisL1CLNPRouteMetQOS;
        PathCost        isisL1CLNPRouteMetric;
        ObjectIdentifier isisL1CLNPRouteForw;
	Integer		isisL1CLNPRouteSource;
	Integer		isisL1CLNPSysInstance;

} IsisL1CLNPDestEntry;

#define MAXL1CLNPDESTPERNODE	1	/* this table might not be needed other than */
					/* a cache */
typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisL1CLNPDestEntry	*pentry[MAXL1CLNPDESTPERNODE];
	IsisL1CLNPDestEntry	isisL1CLNPDestEntry[MAXL1CLNPDESTPERNODE];

} IsisL1CLNPDestTable;



/* The Level 2 CLNP Destination Group */
/* The Level 2 CLNP Destination Table */
typedef struct	{
	NSAPPrefix	isisL2CLNPRouteDest;
        TOS             isisL2CLNPRouteMetQOS;
	Integer		isisL2CLNPRouteMetType;
        PathCost        isisL2CLNPRouteIntMetric;
	Integer		isisL2CLNPRouteExtMetric;
        ObjectIdentifier isisL2CLNPRouteForw;
	Integer		isisL2CLNPRouteSource;
	Integer		isisL2CLNPSysInstance;

} IsisL2CLNPDestEntry;

#define MAXL2CLNPDESTPERNODE	1	/* this table might not be needed other than */
					/* a cache */
typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisL2CLNPDestEntry	*pentry[MAXL2CLNPDESTPERNODE];
	IsisL2CLNPDestEntry	isisL2CLNPDestEntry[MAXL2CLNPDESTPERNODE];

} IsisL2CLNPDestTable;


/* The IP Destination Group */
/* The IP Destination Table */
typedef struct	{
	IpAddress	isisIPRouteDest;
        IpAddress       isisIPRouteMask;
        TOS             isisIPRouteMetTOS;
	Integer		isisIPRouteMetType;
        PathCost        isisIPRouteIntMetric;
 	Integer		isisIPRouteExtMetric;
	ObjectIdentifier isisIPRouteForw;
	Integer		isisIPRouteSource;
	Integer		isisIPRouteSysInstance;

} IsisIPDestEntry;

#define MAXIPDESTPERNODE	1	/* this table might not be needed other than */
					/* a cache */
typedef struct	{
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisIPDestEntry	*pentry[MAXIPDESTPERNODE];
	IsisIPDestEntry	isisIPDestEntry[MAXIPDESTPERNODE];

} IsisIPDestTable;


/* Maximum IS-IS System Instances in this Intermediate-System */
#define MAXISISSYSINSTANCES	2

typedef struct 	{	/* sorted by isisSysInstance */
	int		mib;
  	int		nentries;		
	int		maxentries;
	IsisMibEntry	*pentry[MAXISISSYSINSTANCES];
	IsisMibEntry	isisMibEntry[MAXISISSYSINSTANCES];

	/* non-per-instance tables, per-node tables, entries used as cache */

	IsisL1CLNPDestTable	isisL1CLNPDestTable;
	IsisL2CLNPDestEntry	isisL2CLNPDestEntry;
	IsisIPDestEntry		isisIPDestEntry;

} IsisMibTable;


/* For mapping the queue part of a mib table */
typedef struct	{
	int		mib;			/* which mib table */
  	int		nentries;		/* valid number of entries */
	int		maxentries;		/* maximum number of valid entries */
	unsigned char	*pentry[1];		/* ptr to the entries */

} Queue;



/* Memory structures in isis_mib_table.c */
extern IsisMibTable isisMibTable;

/* Routines defined in isis_mib_table.c */
void initIsisMibCold();
int initIsisMibWarm();
unsigned char *locateEntry();
unsigned char *locateNextEntry();
unsigned char *locateClosestEntry();
IsisL2SummAddrEntry *locateEntryL2SummAddr();
IsisESAdjEntry *locateEntryESAdj();
IsisIPDestEntry *locateIPRouteEntry();
IsisIPDestEntry *locateClosestIPRouteEntry();

unsigned char *searchEntry();			/* recursively search mib tree */
unsigned char *searchEntryManAreaAddr();
unsigned char *searchEntryAreaAddr();
unsigned char *searchEntryProtSupp();
unsigned char *searchEntryL2SummAddr();
unsigned char *searchEntryAreaRecPwd();
unsigned char *searchEntryDomainRecPwd();
unsigned char *searchEntryPartRep();
unsigned char *searchEntryPartAreaAddr();
unsigned char *searchEntryVirtAdj();
unsigned char *searchEntryCircAuthRecPwd();
unsigned char *searchEntryISAdjIPAddr();
unsigned char *searchEntryISAdjProtSupp();

int kmeminit();



/* Indices for the depth of mib tree */
#define DEPTHSYSTEM		1
#define DEPTHMANAREAADDR	2
#define DEPTHAREAADDR		2
#define DEPTHCIRCUIT		2
#define DEPTHISADJ		3
#define DEPTHISADJAREAADDR	4
#define DEPTHPROTSUPP		2
#define DEPTHL2SUMMADDR		3
#define DEPTHAREARECPWD		2
#define DEPTHDOMAINRECPWD	2
#define	DEPTHPARTREP		2
#define DEPTHPARTAREAADDR	2
#define DEPTHVIRTADJ		2
#define DEPTHCIRCIS		2
#define DEPTHCIRCAUTHRECPWD	3
#define DEPTHISADJIPADDR	4
#define DEPTHISADJPROTSUPP	4
#define DEPTHESADJ		3
#define DEPTHRA			3
#define DEPTHIPRA		3

#define HEIGHTSYSTEM		1
#define HEIGHTMANAREAADDR	2
#define HEIGHTAREAADDR		2
#define HEIGHTCIRCUIT		2
#define HEIGHTISADJ		3
#define HEIGHTISADJAREAADDR	4
#define HEIGHTPROTSUPP		2
#define HEIGHTL2SUMMADDR	3
#define HEIGHTAREARECPWD	2
#define HEIGHTDOMAINRECPWD	2
#define HEIGHTPARTREP		2
#define HEIGHTPARTAREAADDR	2
#define HEIGHTVIRTADJ		2
#define HEIGHTCIRCIS		2
#define HEIGHTCIRCAUTHRECPWD	3
#define HEIGHTISADJIPADDR	4
#define HEIGHTISADJPROTSUPP	4
#define HEIGHTESADJ		3
#define HEIGHTRA		3
#define HEIGHTIPRA		3

typedef struct	{
	unsigned int 	key;
	LongOctetString longkey;
	unsigned char  	*keyhole;

} StairStep;

/* Type of mib table */
#define MIBSYSTEM		1
#define MIBMANAREAADDR		2
#define MIBAREAADDR		3
#define MIBCIRCUIT		4
#define MIBISADJ		5
#define MIBISADJAREAADDR	6
#define MIBPROTSUPP		7
#define MIBL2SUMMADDR		8
#define MIBAREARECPWD		9
#define MIBDOMAINRECPWD	       	10
#define MIBPARTREP		11
#define MIBPARTAREAADDR		12
#define MIBVIRTADJ		13
#define MIBCIRCIS		14
#define MIBCIRCAUTHRECPWD	15
#define MIBISADJIPADDR		16
#define MIBISADJPROTSUPP	17
#define MIBESADJ		18
#define MIBRA			19
#define MIBIPRA			20

void queueInit();
void queueFlush();
unsigned char *queueNew();
int queueAdd();
int queueDelete();

int cmpSysEntry();
int cmpManAreaAddrEntry();
int cmpAreaAddrEntry();
int cmpCircEntry();
int cmpISAdjEntry();
int cmpISAdjAreaAddrEntry();
int cmpProtSuppEntry();
int cmpL2SummAddrEntryi();
int cmpL2SummAddrEntryj();
int cmpAreaRecPwdEntry();
int cmpDomainRecPwdEntry();
int cmpPartRepEntry();
int cmpPartAreaAddrEntry();
int cmpVirtAdjEntry();
int cmpCircISEntry();
int cmpCircAuthRecPwdEntry();
int cmpISAdjIPAddrEntry();
int cmpISAdjProtSuppEntry();
int cmpESAdjEntryi();
int cmpESAdjEntryj();
int cmpRAEntry();
int cmpIPRAEntry();


void initOctetString();
int copyOctetString();

int freshISAdjEntry();
int freshISAdjAreaAddrTable();

void dot2binary();
void binary2dot();

void oid2net20(unsigned int *, OSINSAddress *, int);
void oid2password(unsigned int	*, Password *, int);
void octetString2oid(LongOctetString *, unsigned int *);

IsisManAreaAddrEntry *locateManAreaAddrEntry(Queue *, OSINSAddress *);
IsisAreaAddrEntry *locateAreaAddrEntry(Queue *, OSINSAddress *);



/* end of isis_mib.h */
