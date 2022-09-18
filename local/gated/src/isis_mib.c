/*
 *  $Header: /vol/src/devel/gated/master/gated/src/isis_mib.c,v 1.5 1993/07/16 16:40:59 jch Exp $
 */


/*
**    isis_mib.c
**
**    
**
**    John Chu <jychu@watson.ibm.com>
**
**
*/



/****************************
*                           *
*       Include Files       *
*                           *
****************************/



#define	INCLUDE_ISODE_SNMP
#include "include.h"



#if	defined(PROTO_SNMP)

#define	USE_SNMP_OK_NOTOK
#include "isis_pdus.h"
#include "isis_flood.h"
#include "snmp_isode.h"
#include "isis_mib.h"



/****************************
*                           *
*   External References     *
*                           *
****************************/


AreaAddrList parseLSPAreaAddrList();
AreaAddrList mergeAreaAddrList();


/****************************
*                           *
*   Local Definitions       *
*                           *
****************************/



/* IS-IS object request processors defined in this module */
/* for the get requests */
static int get_isisSysTable();
static int get_isisManAreaAddrTable();
static int get_isisAreaAddrTable();
static int get_isisL2SummAddrTable();
static int get_isisAuthAreaRecPwdTable();
static int get_isisAuthDomainRecPwdTable();
static int get_isisPartRepTable();
static int get_isisPartAreaAddrTable();
static int get_isisVirtAdjTable();
static int get_isisCircTable();
static int get_isisCircAuthRecPwdTable();
static int get_isisISAdjTable();
static int get_isisISAdjAreaAddrTable();
static int get_isisISAdjIPAddrTable();
static int get_isisISAdjProtSuppTable();
static int get_isisESAdjTable();
static int get_isisRATable();
static int get_isisIPRATable();
static int get_isisCLNPDestTable();
static int get_isisIPDestTable();
static int get_isisTestL1LSPDbaseTable();
static int get_isisTestL2LSPDbaseTable();
static int get_isisSysProtSuppTable();
static int get_isisCircISTable();
static int get_isisL1CLNPDestTable();
static int get_isisL2CLNPDestTable();

/* for the set requests */
static void set_isisSysTable();
static void set_isisManAreaAddrTable();
static void set_isisL2SummAddrTable();
static void set_isisAuthAreaRecPwdTable();
static void set_isisAuthDomainRecPwdTable();
static void set_isisPartRepTable();
static void set_isisCircTable();
static void set_isisCircAuthRecPwdTable();
static void set_isisESAdjTable();
static void set_isisRATable();
static void set_isisIPRATable();
static void set_isisTestL1LSPDbaseTable();
static void set_isisTestL2LSPDbaseTable();
static void set_isisSysProtSuppTable();
static void set_isisCircISTable();
static void set_isisL1CLNPDestTable();
static void set_isisL2CLNPDestTable();

/****************************
*                           *
*   Memory Allocation       *
*                           *
****************************/

char dummyOctetString[20];			/* for those not supported */

struct sockaddr_in netaddr;			/* for those not supported */



/*
**	For building the isis object tree
*/

static struct object_table isis_objects[] = {

    /* The System Group objects */

    /* Initialize the System Table, read-write */
   {"isisSysInstance",	      	get_isisSysTable, NULL,		1},
   {"isisSysExistState",	get_isisSysTable, NULL,		2},
   {"isisSysVersion",	      	get_isisSysTable, NULL,		3},
   {"isisSysType",		get_isisSysTable, NULL,		4},
   {"isisSysID",		get_isisSysTable, NULL,		5},
   {"isisSysMaxPathSplits",	get_isisSysTable, NULL,		6},
   {"isisSysMinLSPTransInt",    get_isisSysTable, NULL,		7},
   {"isisSysMaxLSPGenInt",	get_isisSysTable, NULL,		8},
   {"isisSysMinBroadLSPTransInt",get_isisSysTable, NULL,	9},
   {"isisSysCompSNPInt",	get_isisSysTable, NULL,		10},
   {"isisSysOrigL1LSPBuffSize", get_isisSysTable, NULL,		11},
   {"isisSysMaxAreaAddresses",  get_isisSysTable, NULL,		12},
   {"isisSysMinLSPGenInt",	get_isisSysTable, NULL,		13},
   {"isisSysPollESHelloRate",   get_isisSysTable, NULL,		14},
   {"isisSysPartSNPInt",	get_isisSysTable, NULL,		15},
   {"isisSysWaitTime",	        get_isisSysTable, NULL,		16},
   {"isisSysDRISISHelloTimer",  get_isisSysTable, NULL,		17},
   {"isisSysOperState",	        get_isisSysTable, NULL,		18},
   {"isisSysL1State",	        get_isisSysTable, NULL,		19},
   {"isisSysCorrLSPs",	        get_isisSysTable, NULL,		20},
   {"isisSysLSPL1DbaseOloads",  get_isisSysTable, NULL,		21},
   {"isisSysManAddrDropFromAreas",	get_isisSysTable, NULL,	22},
   {"isisSysAttemptToExMaxSeqNums",	get_isisSysTable, NULL,	23},
   {"isisSysSeqNumSkips",		get_isisSysTable, NULL, 24},
   {"isisSysOwnLSPPurges",		get_isisSysTable, NULL,	25},
   {"isisSysIDFieldLenMismatches",	get_isisSysTable, NULL,	26},
   {"isisSysMaxAreaAddrMismatches",	get_isisSysTable, NULL,	27},
   {"isisSysOrigL2LSPBuffSize",  get_isisSysTable, NULL,	28},
   {"isisSysL2State",	        get_isisSysTable, NULL,		29},
   {"isisSysLSPL2DbaseOloads",  get_isisSysTable, NULL,		30},
   {"isisSysAuthAreaTransPwd",  get_isisSysTable, NULL,		31},
   {"isisSysAuthDomainTransPwd",get_isisSysTable, NULL,		32},
   {"isisSysAuthFails",	        get_isisSysTable, NULL,		33},

    /* Initialize the Level 1 Manual Area Address Table, read-write */
   {"isisManAreaAddrSysInstance",	get_isisManAreaAddrTable, NULL,	1},
   {"isisManAreaAddr",			get_isisManAreaAddrTable, NULL,	2},
   {"isisManAreaAddrExistState",	get_isisManAreaAddrTable, NULL,	3},

    /* Initialize the Level 1 Area Address Table, read-only */
   {"isisAreaAddrSysInstance",		get_isisAreaAddrTable, NULL,	1},
   {"isisAreaAddr",			get_isisAreaAddrTable, NULL,	2},

    /* The System Integrated Group objects */

    /* Initialize the System Protocol Supported Table, read-write */
   {"isisSysProtSuppSysInstance", 	get_isisSysProtSuppTable, NULL, 1},
   {"isisSysProtSuppProtocol", 		get_isisSysProtSuppTable, NULL, 2},
   {"isisSysProtSuppExistState", 	get_isisSysProtSuppTable, NULL, 3},

    /* The Level 2 IP Group, present if the system is a level 2 IS and supports
    /* integrated IS-IS */

    /* Initialize the Level 2 IP Summary Address Table, read-write */
   {"isisL2SummAddrSysInstance",	get_isisL2SummAddrTable, NULL,	1},
   {"isisL2SummAddress",		get_isisL2SummAddrTable, NULL,	2},
   {"isisL2SummAddrMask",		get_isisL2SummAddrTable, NULL,	3},
   {"isisL2SummAddrExistState",		get_isisL2SummAddrTable, NULL,	4},
   {"isisL2SummAddrOperState",		get_isisL2SummAddrTable, NULL,	5},
   {"isisL2SummAddrDefaultMetric",	get_isisL2SummAddrTable, NULL,	6},
   {"isisL2SummAddrDelayMetric",	get_isisL2SummAddrTable, NULL,	7},
   {"isisL2SummAddrExpenseMetric",	get_isisL2SummAddrTable, NULL,	8},
   {"isisL2SummAddrErrorMetric",	get_isisL2SummAddrTable, NULL,	9},


    /* The Authentication Group, present if the authentication procedures are
    /* supported */

    /* Initialize the Level 1 Area Receive Password Table, read-write */
   {"isisAuthAreaRecPwdSysInstance",	get_isisAuthAreaRecPwdTable, NULL,	1},
   {"isisAuthAreaRecPwd",           	get_isisAuthAreaRecPwdTable, NULL,	2},
   {"isisAuthAreaRecPwdExistState", 	get_isisAuthAreaRecPwdTable, NULL,	3},

    /* Initialize the Level 2 Domain Receive Password Table, read-write */
   {"isisAuthDomainRecPwdSysInstance",	get_isisAuthDomainRecPwdTable, NULL,	1},
   {"isisAuthDomainRecPwd",		get_isisAuthDomainRecPwdTable, NULL,	2},
   {"isisAuthDomainRecPwdExistState", 	get_isisAuthDomainRecPwdTable, NULL,	3},


    /* The Partition Repair Group, present if the system is a Level 2 IS and
    /* the partition repair option is implemented */

    /* Initialize the Partition Repair Table, read-write */
   {"isisPartRepSysInstance",	get_isisPartRepTable, NULL,	1},
   {"isisPartRepMaxVirtAdj",	get_isisPartRepTable, NULL,	2},
   {"isisPartRepDesL2IS",	get_isisPartRepTable, NULL,	3},
   {"isisPartRepVirtLinkChgs",	get_isisPartRepTable, NULL,	4},

    /* Initialize the Partition Area Address Table, read-only */
   {"isisPartAreaAddrSysInstance",	get_isisPartAreaAddrTable, NULL,	1},
   {"isisPartAreaAddr",			get_isisPartAreaAddrTable, NULL,	2},

    /* Initialize the Virtual Adjacency Table, read-only */
   {"isisVirtAdjSysInstance",	get_isisVirtAdjTable, NULL,	1},
   {"isisVirtAdjIndex",		get_isisVirtAdjTable, NULL,	2},
   {"isisVirtAdjNET",		get_isisVirtAdjTable, NULL,	3},
   {"isisVirtAdjMetric",	get_isisVirtAdjTable, NULL,	4},


    /* The Circuit Group, mandatory */

    /* Initialize the Circuit Table, read-write */
   {"isisCircSysInstance",	get_isisCircTable, NULL,	1},
   {"isisCircIndex",		get_isisCircTable, NULL,	2},
   {"isisCircIfIndex",		get_isisCircTable, NULL,	3},
   {"isisCircOperState",	get_isisCircTable, NULL,	4},
   {"isisCircExistState",	get_isisCircTable, NULL,	5},
   {"isisCircType",		get_isisCircTable, NULL,	6},
   {"isisCircISISHelloTimer",	get_isisCircTable, NULL,	7},
   {"isisCircL1DefaultMetric",	get_isisCircTable, NULL,	8},
   {"isisCircL1DelayMetric",	get_isisCircTable, NULL,	9},
   {"isisCircL1ExpenseMetric",	get_isisCircTable, NULL,	10},
   {"isisCircL1ErrorMetric",	get_isisCircTable, NULL,	11},
   {"isisCircExtDomain",	get_isisCircTable, NULL,	12},
   {"isisCircAdjChanges",	get_isisCircTable, NULL,	13},
   {"isisCircInitFails",	get_isisCircTable, NULL,	14},
   {"isisCircRejAdjs",		get_isisCircTable, NULL,	15},
   {"isisCircOutCtrlPDUs",	get_isisCircTable, NULL,	16},
   {"isisCircInCtrlPDUs",	get_isisCircTable, NULL,	17},
   {"isisCircIDFieldLenMismatches",	get_isisCircTable, NULL,	18},
   {"isisCircMaxAreaAddrMismatches",	get_isisCircTable, NULL,	19},
   {"isisCircL2DefaultMetric",	get_isisCircTable, NULL,	20},
   {"isisCircL2DelayMetric",	get_isisCircTable, NULL,	21},
   {"isisCircL2ExpenseMetric",	get_isisCircTable, NULL,	22},
   {"isisCircL2ErrorMetric",	get_isisCircTable, NULL,	23},
   {"isisCircManL2Only",	get_isisCircTable, NULL,	24},
   {"isisCircL1ISPriority",	get_isisCircTable, NULL,	25},
   {"isisCircL1CircID",		get_isisCircTable, NULL,	26},
   {"isisCircL1DesIS",		get_isisCircTable, NULL,	27},
   {"isisCircLANL1DesISChanges",get_isisCircTable, NULL,	28},
   {"isisCircL2ISPriority",	get_isisCircTable, NULL,	29},
   {"isisCircL2CircID",		get_isisCircTable, NULL,	30},
   {"isisCircL2DesIS",		get_isisCircTable, NULL,	31},
   {"isisCircLANL2DesISChanges",get_isisCircTable, NULL,	32},
   {"isisCircMCAddr",		get_isisCircTable, NULL,	33},
   {"isisCircPtToPtCircID",	get_isisCircTable, NULL,	34},
   {"isisCircStaticCallInfo",	get_isisCircTable, NULL,	35},
   {"isisCircDACallDefMetInc",	get_isisCircTable, NULL,	36},
   {"isisCircDACallDelMetInc",	get_isisCircTable, NULL,	37},
   {"isisCircDACallErrMetInc",	get_isisCircTable, NULL,	38},
   {"isisCircDACallExpMetInc",	get_isisCircTable, NULL,	39},
   {"isisCircAuthTransPwd",	get_isisCircTable, NULL,	40},
   {"isisCircAuthFails",	get_isisCircTable, NULL,	41},

    /* The Circuit IS Group objects */

    /* Initialize the Circuit IS Table, read-write */
   {"isisCircISSysInstance",	get_isisCircISTable, NULL, 1},
   {"isisCircISIndex",		get_isisCircISTable, NULL, 2},
   {"isisCircISExistState",	get_isisCircISTable, NULL, 3},
   {"isisCircISOperState",	get_isisCircISTable, NULL, 4},
   {"isisCircISHoldTimerMult",	get_isisCircISTable, NULL, 5},
   {"isisCircISConfTimer",	get_isisCircISTable, NULL, 6},
   {"isisCircISSuggESConfTimer",get_isisCircISTable, NULL, 7},
   {"isisCircISRedHoldTime",	get_isisCircISTable, NULL, 8},
   {"isisCircISMCAddr",		get_isisCircISTable, NULL, 9},
   {"isisCircISESReachChgs",	get_isisCircISTable, NULL, 10},
   {"isisCircISInv9542PDUs",	get_isisCircISTable, NULL, 11},

    /* The Circuit Authentication Group, present if the Circuit authentication 
    /* procedures are implemented */

    /* Initialize the Circuit Receive Password Table, read-write */
   {"isisCircAuthRecPwdSysInstance",	get_isisCircAuthRecPwdTable, NULL,	1},
   {"isisCircAuthRecPwdCircIndex",	get_isisCircAuthRecPwdTable, NULL,	2},
   {"isisCircAuthRecPwd",		get_isisCircAuthRecPwdTable, NULL,	3},
   {"isisCircAuthRecPwdExistState",	get_isisCircAuthRecPwdTable, NULL,	4},


    /* The IS Adjacency Group, mandatory and contains info about adjacencies to 
    /* routers maintained by the Integrated IS-IS protocol */

    /* Initialize the IS Adjacency Table, read-only */
   {"isisISAdjSysInstance",		get_isisISAdjTable, NULL,	1},
   {"isisISAdjCircIndex",		get_isisISAdjTable, NULL,	2},
   {"isisISAdjIndex",			get_isisISAdjTable, NULL,	3},
   {"isisISAdjState",			get_isisISAdjTable, NULL,	4},
   {"isisISAdjNeighSNPAAddress",	get_isisISAdjTable, NULL,	5},
   {"isisISAdjNeighSysType",		get_isisISAdjTable, NULL,	6},
   {"isisISAdjNeighSysID",		get_isisISAdjTable, NULL,	7},
   {"isisISAdjUsage",			get_isisISAdjTable, NULL,	8},
   {"isisISAdjHoldTimer",		get_isisISAdjTable, NULL,	9},
   {"isisISAdjNeighPriority",		get_isisISAdjTable, NULL,	10},

    /* Initialize the IS Adjacency Area Address Table, read-only */
   {"isisISAdjAreaAddrSysInstance",	get_isisISAdjAreaAddrTable, NULL,	1},
   {"isisISAdjAreaAddrCircIndex", 	get_isisISAdjAreaAddrTable, NULL,	2},
   {"isisISAdjAreaAddrAdjIndex", 	get_isisISAdjAreaAddrTable, NULL,	3},
   {"isisISAdjAreaAddress",		get_isisISAdjAreaAddrTable, NULL,	4},


    /* The IS Adjacency IP Group, present if the system supports Integrated IS-IS */

    /* Initialize the IS Adjacency IP Address Table, read-only */
   {"isisISAdjIPAddrSysInstance",	get_isisISAdjIPAddrTable, NULL,	1},
   {"isisISAdjIPAddrCircIndex",		get_isisISAdjIPAddrTable, NULL,	2},
   {"isisISAdjIPAddrAdjIndex",		get_isisISAdjIPAddrTable, NULL,	3},
   {"isisISAdjIPAddress",		get_isisISAdjIPAddrTable, NULL,	4},

    /* The IS Adjacency Integrated Group objects */

    /* Initialize the IS Adjacency Protocol Supported Table, read-only */
   {"isisISAdjProtSuppSysInstance",	get_isisISAdjProtSuppTable, NULL,	1},
   {"isisISAdjProtSuppCircIndex", 	get_isisISAdjProtSuppTable, NULL,	2},
   {"isisISAdjProtSuppAdjIndex",  	get_isisISAdjProtSuppTable, NULL,	3},
   {"isisISAdjProtSuppProtocol",  	get_isisISAdjProtSuppTable, NULL,	4},


    /* The ES Adjacency Group, present if the system supports reception of ES Hellos */

    /* Initialize the ES Adjacency Table, read-write */
   {"isisESAdjSysInstance",	get_isisESAdjTable, NULL,	1},
   {"isisESAdjCircIndex",	get_isisESAdjTable, NULL,	2},
   {"isisESAdjAdjIndex",	get_isisESAdjTable, NULL,	3},
   {"isisESAdjType",		get_isisESAdjTable, NULL,	4},
   {"isisESAdjState",		get_isisESAdjTable, NULL,	5},
   {"isisESAdjNeighSNPAAddress",get_isisESAdjTable, NULL,	6},
   {"isisESAdjExistState",	get_isisESAdjTable, NULL,	7},
   {"isisESAdjESID",		get_isisESAdjTable, NULL,	8},


    /* The Reachable Address Group, optional */

    /* Initialize the Reachable Address Table, read-write */
   {"isisRASysInstance",	get_isisRATable, NULL,	1},
   {"isisRACircIndex",		get_isisRATable, NULL,	2},
   {"isisRAIndex",		get_isisRATable, NULL,	3},
   {"isisRAExistState",		get_isisRATable, NULL,	4},
   {"isisRAOperState",		get_isisRATable, NULL,	5},
   {"isisRAAddrPrefix",		get_isisRATable, NULL,	6},
   {"isisRAType",		get_isisRATable, NULL,	7},
   {"isisRAMapType",		get_isisRATable, NULL,	8},
   {"isisRADefMetric",		get_isisRATable, NULL,	9},
   {"isisRADelMetric",		get_isisRATable, NULL,	10},
   {"isisRAExpMetric",		get_isisRATable, NULL,	11},
   {"isisRAErrMetric",		get_isisRATable, NULL,	12},
   {"isisRADefMetricType",	get_isisRATable, NULL,	13},
   {"isisRADelMetricType",	get_isisRATable, NULL,	14},
   {"isisRAExpMetricType",	get_isisRATable, NULL,	15},
   {"isisRAErrMetricType",	get_isisRATable, NULL,	16},
   {"isisRASNPAAddress",	get_isisRATable, NULL,	17},
   {"isisRASNPAMask",		get_isisRATable, NULL,	18},
   {"isisRASNPAPrefix",		get_isisRATable, NULL,	19},




    /* The IP Reachable Address Group, optional */

    /* Initialize the IP Reachable Address Table, read-write */
   {"isisIPRASysInstance", 	get_isisIPRATable, NULL,	1},
   {"isisIPRACircIndex", 	get_isisIPRATable, NULL,	2},
   {"isisIPRAIndex", 		get_isisIPRATable, NULL,	3},
   {"isisIPRADest", 		get_isisIPRATable, NULL,	4},
   {"isisIPRAMask", 		get_isisIPRATable, NULL,	5},
   {"isisIPRAExistState", 	get_isisIPRATable, NULL,	6},
   {"isisIPRAOperState", 	get_isisIPRATable, NULL,	7},
   {"isisIPRADefMetric", 	get_isisIPRATable, NULL,	8},
   {"isisIPRADelMetric", 	get_isisIPRATable, NULL,	9},
   {"isisIPRAExpMetric", 	get_isisIPRATable, NULL,	10},
   {"isisIPRAErrMetric", 	get_isisIPRATable, NULL,	11},
   {"isisIPRADefMetricType",	get_isisIPRATable, NULL,	12},
   {"isisIPRADelMetricType",	get_isisIPRATable, NULL,	13},
   {"isisIPRAExpMetricType",	get_isisIPRATable, NULL,	14},
   {"isisIPRAErrMetricType",	get_isisIPRATable, NULL,	15},
   {"isisIPRASNPAAddress", 	get_isisIPRATable, NULL,	16},


    /* The CLNP Destination Group, present if the system forwards ISO 8473 packets */

    /* Initialize the Level 1 CLNP Destination Table */
   {"isisL1CLNPRouteDest",	get_isisL1CLNPDestTable, NULL,	1},
   {"isisL1CLNPRouteMetQOS",	get_isisL1CLNPDestTable, NULL,	2},
   {"isisL1CLNPRouteMetric",	get_isisL1CLNPDestTable, NULL,	3},
   {"isisL1CLNPRouteForw",	get_isisL1CLNPDestTable, NULL,	4},
   {"isisL1CLNPRouteSource",	get_isisL1CLNPDestTable, NULL,	5},
   {"isisL1CLNPSysInstance",	get_isisL1CLNPDestTable, NULL,	6},

    /* Initialize the Level 2 CLNP Destination Table */
   {"isisL2CLNPRouteDest",	get_isisL2CLNPDestTable, NULL,	1},
   {"isisL2CLNPRouteMetQOS",	get_isisL2CLNPDestTable, NULL,	2},
   {"isisL2CLNPRouteMetType",	get_isisL2CLNPDestTable, NULL,	3},
   {"isisL2CLNPRouteIntMetric",	get_isisL2CLNPDestTable, NULL,	4},
   {"isisL2CLNPRouteExtMetric",	get_isisL2CLNPDestTable, NULL,	5},
   {"isisL2CLNPRouteForw",	get_isisL2CLNPDestTable, NULL,	6},
   {"isisL2CLNPRouteSource",	get_isisL2CLNPDestTable, NULL,	7},
   {"isisL2CLNPSysInstance",	get_isisL2CLNPDestTable, NULL,	8},

    /* The IP Destination Group, present if the system forwards IP packets */

    /* Initialize the IP Destination Table, read-only */
   {"isisIPRouteDest",		get_isisIPDestTable, NULL,	1},
   {"isisIPRouteMask",		get_isisIPDestTable, NULL,	2},
   {"isisIPRouteMetTOS",	get_isisIPDestTable, NULL,	3},
   {"isisIPRouteMetType",	get_isisIPDestTable, NULL,	4},
   {"isisIPRouteIntMetric",	get_isisIPDestTable, NULL,	5},
   {"isisIPRouteExtMetric",	get_isisIPDestTable, NULL,	6},
   {"isisIPRouteForw",		get_isisIPDestTable, NULL,	7},
   {"isisIPRouteSource",	get_isisIPDestTable, NULL,	8},
   {"isisIPRouteSysInstance",	get_isisIPDestTable, NULL,	9},

   /* The Test Group */

   /* Initialize the Level 1 LSP Database Table */
   {"isisL1LSPIndex",		get_isisTestL1LSPDbaseTable, NULL,	1},
   {"isisL1LSPLinkForw",	get_isisTestL1LSPDbaseTable, NULL,	2},
   {"isisL1LSPLinkBack",	get_isisTestL1LSPDbaseTable, NULL,	3},
   {"isisL1LSPSigIdSourceId",	get_isisTestL1LSPDbaseTable, NULL,	4},
   {"isisL1LSPSigIdPseudonodeID", get_isisTestL1LSPDbaseTable, NULL,	5},
   {"isisL1LSPSigIdLSPNum",	get_isisTestL1LSPDbaseTable, NULL,	6},
   {"isisL1LSPSigSeqNum",	get_isisTestL1LSPDbaseTable, NULL,	7},
   {"isisL1LSPSigLifeTime",	get_isisTestL1LSPDbaseTable, NULL,	8},
   {"isisL1LSPSigLevel",	get_isisTestL1LSPDbaseTable, NULL,	9},
   {"isisL1LSPSigChecksum",	get_isisTestL1LSPDbaseTable, NULL,	10},
   {"isisL1LSPOrigLifeTime",	get_isisTestL1LSPDbaseTable, NULL,	11},
   {"isisL1LSPRemainTime",	get_isisTestL1LSPDbaseTable, NULL,	12},
   {"isisL1LSPArrivalTimestamp",get_isisTestL1LSPDbaseTable, NULL,	13},
   {"isisL1LSPSRM",		get_isisTestL1LSPDbaseTable, NULL,	14},
   {"isisL1LSPSSN",		get_isisTestL1LSPDbaseTable, NULL,	15},
   {"isisL1LSPFoundInSNP",	get_isisTestL1LSPDbaseTable, NULL,	16},
   {"isisL1LSPOnDeletedList",	get_isisTestL1LSPDbaseTable, NULL,	17},
   {"isisL1LSPBuf",		get_isisTestL1LSPDbaseTable, NULL,	18},
   {"isisL1LSPLen",		get_isisTestL1LSPDbaseTable, NULL,	19},
   {"isisL1LSPDesc",		get_isisTestL1LSPDbaseTable, NULL,	20},
   {"isisL1LSPHashNext",	get_isisTestL1LSPDbaseTable, NULL,	21},
   {"isisL1LSPSortNext",	get_isisTestL1LSPDbaseTable, NULL,	22},

   /* Initialize the Level 2 LSP Database Table */
   {"isisL2LSPIndex",		get_isisTestL2LSPDbaseTable, NULL,	1},
   {"isisL2LSPLinkForw",	get_isisTestL2LSPDbaseTable, NULL,	2},
   {"isisL2LSPLinkBack",	get_isisTestL2LSPDbaseTable, NULL,	3},
   {"isisL2LSPSigIdSourceId",	get_isisTestL2LSPDbaseTable, NULL,	4},
   {"isisL2LSPSigIdPseudonodeID", get_isisTestL2LSPDbaseTable, NULL,	5},
   {"isisL2LSPSigIdLSPNum",	get_isisTestL2LSPDbaseTable, NULL,	6},
   {"isisL2LSPSigSeqNum",	get_isisTestL2LSPDbaseTable, NULL,	7},
   {"isisL2LSPSigLifeTime",	get_isisTestL2LSPDbaseTable, NULL,	8},
   {"isisL2LSPSigLevel",	get_isisTestL2LSPDbaseTable, NULL,	9},
   {"isisL2LSPSigChecksum",	get_isisTestL2LSPDbaseTable, NULL,	10},
   {"isisL2LSPOrigLifeTime",	get_isisTestL2LSPDbaseTable, NULL,	11},
   {"isisL2LSPRemainTime",	get_isisTestL2LSPDbaseTable, NULL,	12},
   {"isisL2LSPArrivalTimestamp",get_isisTestL2LSPDbaseTable, NULL,	13},
   {"isisL2LSPSRM",		get_isisTestL2LSPDbaseTable, NULL,	14},
   {"isisL2LSPSSN",		get_isisTestL2LSPDbaseTable, NULL,	15},
   {"isisL2LSPFoundInSNP",	get_isisTestL2LSPDbaseTable, NULL,	16},
   {"isisL2LSPOnDeletedList",	get_isisTestL2LSPDbaseTable, NULL,	17},
   {"isisL2LSPBuf",		get_isisTestL2LSPDbaseTable, NULL,	18},
   {"isisL2LSPLen",		get_isisTestL2LSPDbaseTable, NULL,	19},
   {"isisL2LSPDesc",		get_isisTestL2LSPDbaseTable, NULL,	20},
   {"isisL2LSPHashNext",	get_isisTestL2LSPDbaseTable, NULL,	21},
   {"isisL2LSPSortNext",	get_isisTestL2LSPDbaseTable, NULL,	22},

   {NULL}

}; /* end of isis_objects[] */


/* Object tree node for isis */
struct snmp_tree isis_mib_tree = {
	NULL,
	NULL,
	"isis",
	NULLOID,
	readOnly,			/* for now */
	isis_objects,
	0
};


/****************************
*                           *
*  Procedure Definitions    *
*                           *
****************************/

/*
**	Initialize IS-IS mib
*/
void isis_init_mib(enabled)
int	enabled;
{
    if (enabled) {
        snmp_tree_register(&isis_mib_tree);
    }
    else {
        snmp_tree_unregister(&isis_mib_tree);
    }
}



/* Request processors */


/* The System Group */

/*
**	Process a request referencing a variable in the System Table
*/
static int get_isisSysTable(ObjectInstance * poi,
			    struct type_SNMP_VarBind * pvarbind,
			    int request				)
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			/* leaf node in object tree */
    int		instance=0;		/* instance of an object */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisSysEntry	*pSysEntry;	/* ptr to a Sys entry */

    /* Validate the request and adjust variable name if necessary */
    switch (request) {
    case type_SMUX_PDUs_get__request:
	/* Examine the suffix to the object id whose value is requested */
	/* For 'get' request, the object identifier must be one element larger than */
 	/* that in the object type, and the extra element cannot be of value zero */

	if (poid->oid_nelem != pot->ot_name->oid_nelem+1) {
	    /* Instance was not specified in the request; it has to be */
	    return int_SNMP_error__status_noSuchName;
	}
	if ((instance = poid->oid_elements[poid->oid_nelem-1]) == 0) {
	    /* Instance was specified as 0 in the request; there is no 0th instance */
	    return int_SNMP_error__status_noSuchName;
	}
  	
        /* Get the instance if it exists */
        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    /* Instance does not exist */
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:
	/* Examine the suffix to the object id */
	/* For 'get-next' request, the object id name should have the same number of */
	/* elements or more than that in the object type */

	if (poid->oid_nelem == pot->ot_name->oid_nelem) {  	/* same */
	    ObjectID pnewoid;		/* ptr to a new object identifier */

	    /* Copy the object id and extend it by one element, in VarBind */
	    if ((pnewoid = oid_extend(poid, 1)) == NULLOID) {
		return int_SNMP_error__status_genErr;
	    }
	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

	    /* No instance was specified in the request */
	    instance = 0;
     	}
	else {		/* more */
	    /* Get the instance specified */
            instance = poid->oid_elements[pot->ot_name->oid_nelem];

	}

	/* Get the next instance if it exists */
        if ((pMibEntry = (IsisMibEntry *)locateNextEntry(&isisMibTable, instance)) ==
							         (IsisMibEntry *)NULL) {
            /* The next instance of the object does not exist  */
            /* The next object in the object tree should be handled */
	    return NOTOK;
        }        

	/* Place it in the variable binding struct */
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = ++instance;
  	    
	break;

    default:
	/* Unsupported request */
	return int_SNMP_error__status_genErr;

    } /* end of switch on request */

    pSysEntry = &pMibEntry->isisSysEntry;

    /* Extract the column number of the variable in the entry of this table */
    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    /* Put the requested variables's current value into the name/value binding struct */
    switch (column) {
    case 1:			/* isisSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysInstance);

    case 2:			/* isisSysExistState, ExistState */
	return o_integer(poi, pvarbind, pSysEntry->isisSysExistState);

    case 3:                	/* isisSysVersion, OCTET STRING */
	return o_string(poi, pvarbind, pSysEntry->isisSysVersion.contents,
				       pSysEntry->isisSysVersion.len      );	

    case 4:			/* isisSysType, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysType);

    case 5: 			/* isisSysID, SystemID */
	return o_string(poi, pvarbind, pSysEntry->isisSysID.contents,
				       pSysEntry->isisSysID.len      );

    case 6:			/* isisSysMaxPathSplits, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysMaxPathSplits);

    case 7: 			/* isisSysMinLSPTransInt, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysMinLSPTransInt);

    case 8:			/* isisSysMaxLSPGenInt, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysMaxLSPGenInt);

    case 9: 			/* isisSysMinBroadLSPTransInt, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysMinBroadLSPTransInt);

    case 10:			/* isisSysCompSNPInt, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysCompSNPInt);

    case 11:			/* isisSysOrigL1LSPBuffSize, LSPBuffSize */
	return o_integer(poi, pvarbind, pSysEntry->isisSysOrigL1LSPBuffSize);

    case 12:			/* isisSysMaxAreaAddresses, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysMaxAreaAddresses);

    case 13:			/* isisSysMinLSPGenInt, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysMinLSPGenInt);

    case 14:			/* isisSysPollESHelloRate, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysPollESHelloRate);

    case 15:			/* isisSysPartSNPInt, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysPartSNPInt);

    case 16:			/* isisSysWaitTime, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysWaitTime);

    case 17:			/* isisSysDRISISHelloTimer, INTEGER */
	return o_integer(poi, pvarbind, pSysEntry->isisSysDRISISHelloTimer);

    case 18:			/* isisSysOperState, OperState */
	return o_integer(poi, pvarbind, pSysEntry->isisSysOperState);

    case 19:			/* isisSysL1State, LevelState */
	return o_integer(poi, pvarbind, pSysEntry->isisSysL1State);

    case 20:			/* isisSysCorrLSPs, Counter */
	return o_number(poi, pvarbind, pSysEntry->isisSysCorrLSPs);

    case 21:			/* isisSysLSPL1DbaseOloads, Counter */
	return o_number(poi, pvarbind, pSysEntry->isisSysLSPL1DbaseOloads);

    case 22:			/* isisSysManAddrDropFromAreas, Counter */
	return o_number(poi, pvarbind, pSysEntry->isisSysManAddrDropFromAreas);

    case 23:			/* isisSysAttemptToExMaxSeqNums, Counter */
	return o_number(poi, pvarbind, pSysEntry->isisSysAttemptToExMaxSeqNums);

    case 24:			/* isisSysSeqNumSkips, Counter */
	return o_number(poi, pvarbind, pSysEntry->isisSysSeqNumSkips);

    case 25:			/* isisSysOwnLSPPurges, Counter */
	return o_number(poi, pvarbind, pSysEntry->isisSysOwnLSPPurges);

    case 26:			/* isisSysIDFieldLenMismatches, Counter */
	return o_number(poi, pvarbind, pSysEntry->isisSysIDFieldLenMismatches);

    case 27:			/* isisSysMaxAreaAddrMismatches, Counter */
	return o_number(poi, pvarbind, pSysEntry->isisSysMaxAreaAddrMismatches);

    case 28:			/* isisSysOrigL2LSPBuffSize, LSPBuffSize */
	return o_integer(poi, pvarbind, pSysEntry->isisSysOrigL2LSPBuffSize);

    case 29:			/* isisSysL2State, LevelState */
	return o_integer(poi, pvarbind, pSysEntry->isisSysL2State);

    case 30:			/* isisSysLSPL2DbaseOloads, Counter */
	return o_number(poi, pvarbind, pSysEntry->isisSysLSPL2DbaseOloads);

    case 31:			/* isisSysAuthAreaTransPwd, Password */
	return o_string(poi, pvarbind, pSysEntry->isisSysAuthAreaTransPwd.contents,
				       pSysEntry->isisSysAuthAreaTransPwd.len      );

    case 32:			/* isisSysAuthDomainTransPwd, Password */
	return o_string(poi, pvarbind, pSysEntry->isisSysAuthDomainTransPwd.contents,
				       pSysEntry->isisSysAuthDomainTransPwd.len      );

    case 33:			/* isisSysAuthFails, Counter */
	return o_number(poi, pvarbind, pSysEntry->isisSysAuthFails);

    default:
	return int_SNMP_error__status_noSuchName;

    } /* end of switch on colume */




} /* end of get_isisSysTable() */

static void set_isisSysTable(ObjectInstance * poi,
			    struct type_SNMP_VarBind * pvarbind,
 			    int request         		    )
{




} /* end of set_isisSysTable() */


/*
**	Process a request referencing a variable in the Level 1 Manual Area
**      Address Table
*/
static int get_isisManAreaAddrTable(ObjectInstance * poi,
 				    struct type_SNMP_VarBind * pvarbind,
 				    int request         		    )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    int		sysInstance=0;		/* sysInstance, primary index */
    OSINSAddress	manAreaAddr;	/* manAreaAddress, secondary index */
    StairStep		instances[HEIGHTMANAREAADDR];
    int			indexLen;	/* number of elements in the indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisSysEntry	*pSysEntry;	/* ptr to a Sys entry */
    IsisManAreaAddrEntry *pManAreaAddrEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem < pot->ot_name->oid_nelem+2) 
	    return int_SNMP_error__status_noSuchName;

	if ((sysInstance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, sysInstance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pSysEntry = &pMibEntry->isisSysEntry;	

	/* Convert the oid after sysInstance into OSINSAddress */
	oid2net20(&poid->oid_elements[pot->ot_name->oid_nelem+1], 
		  (OSINSAddress *) &manAreaAddr,
		  poid->oid_nelem-pot->ot_name->oid_nelem-1);

        if ((pManAreaAddrEntry = 
	     (IsisManAreaAddrEntry *)locateManAreaAddrEntry((Queue *) &pSysEntry->isisManAreaAddrTable, 
					         	    &manAreaAddr                     )) ==
					          	    (IsisManAreaAddrEntry *)NULL         ){
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+2) {      
	    /* sysInstance and at least one byte of address are specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

	    /* Move the index values into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    oid2net20(&poid->oid_elements[pot->ot_name->oid_nelem+1], 
		      (OSINSAddress *) &instances[1].longkey,
		      poid->oid_nelem-pot->ot_name->oid_nelem-1);

	    /* Increment the secondary index */
	    if (incByteStream(&instances[1].longkey)) {
		/* The secondary key is overflown */
		if (++instances[0].key == 0) {
		    /* The primary key is overflown */
		    return NOTOK;
		}
	    }
     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Only sysInstance was specified */
	    indexLen = 1;

	    /* Move the index value into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].longkey.maxlen = 20;
	    instances[1].longkey.len = 0;

	    /* Increment the secondary index */
	    instances[1].longkey.len = 1;		/* implementation determines the */
	    instances[1].longkey.contents[0] = 0x01;	/* order of this index */
	    
	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

	    instances[0].key = 1;
	    instances[1].longkey.maxlen = 20;
	    instances[1].longkey.len = 0;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pManAreaAddrEntry = (IsisManAreaAddrEntry *)searchEntryManAreaAddr(instances,
								        DEPTHSYSTEM       )) ==
							           (IsisManAreaAddrEntry *)NULL) {

	    return NOTOK;
	}


	extendOID = (1 + pManAreaAddrEntry->isisManAreaAddr.len) - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid in new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = 
					pManAreaAddrEntry->isisManAreaAddrSysInstance;
	octetString2oid((LongOctetString *) &pManAreaAddrEntry->isisManAreaAddr,
		  	&(pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1]));
					

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisManAreaAddrSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pManAreaAddrEntry->isisManAreaAddrSysInstance);

    case 2: 			/* isisManAreaAddr, OSINSAddress */
 	return o_string(poi, pvarbind, pManAreaAddrEntry->isisManAreaAddr.contents,
				       pManAreaAddrEntry->isisManAreaAddr.len      );

    case 3: 			/* isisManAreaAddrExistState, ExistState */
	return o_integer(poi, pvarbind, pManAreaAddrEntry->isisManAreaAddrExistState);

    default:
	return int_SNMP_error__status_noSuchName;

    } 



} /* end of get_isisManAreaAddrTable() */

static void set_isisManAreaAddrTable(ObjectInstance * poi,
			            struct type_SNMP_VarBind * pvarbind,
 			            int request         		)
{


} /* end of set_isisManAreaAddrTable() */



/*
**	Process a request referencing a variable in the Level 1 Area Address Table
*/
static int get_isisAreaAddrTable(ObjectInstance * poi,
			         struct type_SNMP_VarBind * pvarbind,
 				 int request           		     )
{

    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    int		sysInstance=0;		/* sysInstance, primary index */
    OSINSAddress	areaAddr;	/* areaAddress, secondary index */
    StairStep		instances[HEIGHTAREAADDR];
    int			indexLen;	/* number of elements in the indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisSysEntry	*pSysEntry;	/* ptr to a Sys entry */
    IsisAreaAddrEntry   *pAreaAddrEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem < pot->ot_name->oid_nelem+2) 
	    return int_SNMP_error__status_noSuchName;

	if ((sysInstance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, sysInstance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pSysEntry = &pMibEntry->isisSysEntry;	

	/* Convert the oid after sysInstance into OSINSAddress */
	oid2net20(&poid->oid_elements[pot->ot_name->oid_nelem+1], 
		  (OSINSAddress *) &areaAddr,
		  poid->oid_nelem-pot->ot_name->oid_nelem-1);

        if ((pAreaAddrEntry = 
	     (IsisAreaAddrEntry *)locateAreaAddrEntry((Queue *) &pSysEntry->isisAreaAddrTable, 
					              &areaAddr                     )) ==
					                        (IsisAreaAddrEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+2) {      
	    /* sysInstance and at least one byte of address are specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

	    /* Move the index values into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    oid2net20(&poid->oid_elements[pot->ot_name->oid_nelem+1], 
		      (OSINSAddress *) &instances[1].longkey,
		      poid->oid_nelem-pot->ot_name->oid_nelem-1);

	    /* Increment the secondary index */
	    if (incByteStream(&instances[1].longkey)) {
		/* The secondary key is overflown */
		if (++instances[0].key == 0) {
		    /* The primary key is overflown */
		    return NOTOK;
		}
	    }
     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Only sysInstance was specified */
	    indexLen = 1;

	    /* Move the index value into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].longkey.maxlen = 20;
	    instances[1].longkey.len = 0;

	    /* Increment the secondary index */
	    instances[1].longkey.len = 1;		/* implementation determines the */
	    instances[1].longkey.contents[0] = 0x01;	/* order of this index */
	    
	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

	    instances[0].key = 1;
	    instances[1].longkey.maxlen = 20;
	    instances[1].longkey.len = 0;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pAreaAddrEntry = (IsisAreaAddrEntry *)searchEntryAreaAddr(instances,
								       DEPTHSYSTEM       )) ==
							             (IsisAreaAddrEntry *)NULL) {

	    return NOTOK;
	}


	extendOID = (1 + pAreaAddrEntry->isisAreaAddr.len) - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid in new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = 
					pAreaAddrEntry->isisAreaAddrSysInstance;
	octetString2oid((LongOctetString *) &pAreaAddrEntry->isisAreaAddr,
		  	&(pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1]));
					

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisAreaAddrSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pAreaAddrEntry->isisAreaAddrSysInstance);

    case 2: 			/* isisAreaAddr, OSINSAddress */
 	return o_string(poi, pvarbind, pAreaAddrEntry->isisAreaAddr.contents,
				       pAreaAddrEntry->isisAreaAddr.len      );

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisAreaAddrTable() */



/* The System Integrated Group */

/*
**	Process a request to the System Protocol Supported Table
*/
static int get_isisSysProtSuppTable(ObjectInstance * poi,
				    struct type_SNMP_VarBind * pvarbind,
 				    int request         		       )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		instance=0;		/* SysInstance */
    int		protocol=0;		/* SuppProtocol */
    int		column;			
    StairStep 	instances[HEIGHTPROTSUPP];
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisSysProtSuppTable *pProtSuppTable;
    IsisSysProtSuppEntry *pProtSuppEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;

    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem != pot->ot_name->oid_nelem+2) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[poid->oid_nelem-2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pProtSuppTable = &pMibEntry->isisSysProtSuppTable;

	if ((protocol = poid->oid_elements[poid->oid_nelem-1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pProtSuppEntry = 
	     (IsisSysProtSuppEntry *)locateEntry(pProtSuppTable, protocol)) ==
					          (IsisSysProtSuppEntry *)NULL ){
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+2) {      
	    /* Instance and protocol were specified */
	    extendOID = 0;

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1] + 1;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    extendOID = 1;

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = PROTSUPP_LOWEST;

	}
	else {
	    /* Only object id was specified */
	    extendOID = 2;

	    instances[0].key = 1;
	    instances[1].key = PROTSUPP_LOWEST;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
    	if ((pProtSuppEntry = (IsisSysProtSuppEntry *)searchEntryProtSupp(instances,
		                                                  HEIGHTPROTSUPP,
						                  DEPTHSYSTEM    )) ==
		                                         (IsisSysProtSuppEntry *)NULL) {
	    
	    return NOTOK;
	}
	/* pProtSuppEntry points to the desired entry */

	if (extendOID) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* New binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = instances[0].key;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = instances[1].key;

	break;

    default:
	return int_SNMP_error__status_genErr;

    }

    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisSysProtSuppSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pProtSuppEntry->isisSysProtSuppSysInstance);

    case 2:			/* isisSysProtSuppProtocol, SupportedProtocol */
	return o_integer(poi, pvarbind, pProtSuppEntry->isisSysProtSuppProtocol);

    case 3:			/* isisSysProtSuppExistState, ExistState */
	return o_integer(poi, pvarbind, pProtSuppEntry->isisSysProtSuppExistState);

    default:
	return int_SNMP_error__status_noSuchName;

    }



} /* end of get_isisSysProtSuppTable() */


static void set_isisSysProtSuppTable(ObjectInstance * poi,
				   struct type_SNMP_VarBind * pvarbind,
 				   int request         		       )
{

} /* end of set_isisSysProtSuppTable() */




/* The Level 2 IP Group */

/*
**	Process a request referencing a variable in the Level 2 IP Group,
**      the Level 2 IP summary address table
*/
static int get_isisL2SummAddrTable(ObjectInstance * poi,
				   struct type_SNMP_VarBind * pvarbind,
 				   int request         		       )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    int		instance=0;		
    IpAddress	ipAddr=0;
    IpAddress	ipMask=0;
    StairStep	instances[HEIGHTL2SUMMADDR];
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisL2SummAddrTable *pL2SummAddrTable;
    IsisL2SummAddrEntry *pL2SummAddrEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem != pot->ot_name->oid_nelem+9) /* inst.a.d.d.r.m.a.s.k */
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[poid->oid_nelem-9]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pL2SummAddrTable = &pMibEntry->isisL2SummAddrTable;

        dot2binary(&(poid->oid_elements[poid->oid_nelem-8]), 4, &ipAddr);
        dot2binary(&(poid->oid_elements[poid->oid_nelem-4]), 4, &ipMask);

        if ((pL2SummAddrEntry = locateEntryL2SummAddr(pL2SummAddrTable, 
						      ipAddr, ipMask )) ==
					          (IsisL2SummAddrEntry *)NULL ){
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+9) {      
	    /* Instance.a.d.d.r.m.a.s.k were specified */
	    extendOID = 0;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+1]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+5]), 4, &ipMask);

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = ipAddr;
	    instances[2].key = ipMask + 1;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+8) {
	    /* Instance.a.d.d.r.m.a.s were specified */
	    extendOID = 1;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+1]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+5]), 3, &ipMask);

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = ipAddr;
	    instances[2].key = ipMask + 1;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+7) {
	    /* Instance.a.d.d.r.m.a were specified */
	    extendOID = 2;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+1]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+5]), 2, &ipMask);

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = ipAddr;
	    instances[2].key = ipMask + 1;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+6) {
	    /* Instance.a.d.d.r.m were specified */
	    extendOID = 3;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+1]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+5]), 1, &ipMask);

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = ipAddr;
	    instances[2].key = ipMask + 1;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+5) {
	    /* Instance.a.d.d.r were specified */
	    extendOID = 4;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+1]), 4, &ipAddr);

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = ipAddr;
	    instances[2].key = 1;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+4) {
	    /* Instance.a.d.d were specified */
	    extendOID = 5;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+1]), 3, &ipAddr);

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = ipAddr;
	    instances[2].key = 1;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+3) {
	    /* Instance.a.d were specified */
	    extendOID = 6;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+1]), 2, &ipAddr);

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = ipAddr;
	    instances[2].key = 1;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+2) {
	    /* Instance.a were specified */
	    extendOID = 7;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+1]), 1, &ipAddr);

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = ipAddr;
	    instances[2].key = 1;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    extendOID = 8;

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = 1;
	    instances[2].key = 1;

	}
	else {
	    /* Only object id was specified */
	    extendOID = 9;

	    instances[0].key = 1;
	    instances[1].key = 1;
	    instances[2].key = 1;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
    	if ((pL2SummAddrEntry = (IsisL2SummAddrEntry *)searchEntryL2SummAddr(instances,
		                                                  HEIGHTL2SUMMADDR,
						                  DEPTHSYSTEM    )) ==
		                                         (IsisL2SummAddrEntry *)NULL) {
	    
	    return NOTOK;
	}
	/* pL2SummAddrEntry points to the entry with matching or higher ipaddress */
	/* and matching or higher ipmask */


	if (extendOID) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* New binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = instances[0].key;
        binary2dot(instances[1].key, 
		   &pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1]);
        binary2dot(instances[2].key, 
		   &pvarbind->name->oid_elements[pot->ot_name->oid_nelem+5]);

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisL2SummAddrSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pL2SummAddrEntry->isisL2SummAddrSysInstance);

    case 2: 			/* isisL2SummAddress, IpAddress */
	return o_ipaddr(poi, pvarbind, &pL2SummAddrEntry->isisL2SummAddress);

    case 3:			/* isisL2SummAddrMask, IpAddress */
	return o_ipaddr(poi, pvarbind, &pL2SummAddrEntry->isisL2SummAddrMask);

    case 4: 			/* isisL2SummAddrExistState, ExistState */
	return o_integer(poi, pvarbind, pL2SummAddrEntry->isisL2SummAddrExistState);

    case 5:			/* isisL2SummAddrOperState, OperState */
	return o_integer(poi, pvarbind, pL2SummAddrEntry->isisL2SummAddrOperState);

    case 6:			/* isisL2SummAddrDefaultMetric, DefaultMetric */
	return o_integer(poi, pvarbind, pL2SummAddrEntry->isisL2SummAddrDefaultMetric);

    case 7:			/* isisL2SummAddrDelayMetric, OtherMetric */
	return o_integer(poi, pvarbind, pL2SummAddrEntry->isisL2SummAddrDelayMetric);

    case 8:			/* isisL2SummAddrExpenseMetric, OtherMetric */
	return o_integer(poi, pvarbind, pL2SummAddrEntry->isisL2SummAddrExpenseMetric);

    case 9:			/* isisL2SummAddrErrorMetric, OtherMetric */
	return o_integer(poi, pvarbind, pL2SummAddrEntry->isisL2SummAddrErrorMetric);

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisL2SummAddrTable() */


static void set_isisL2SummAddrTable(ObjectInstance * poi,
			           struct type_SNMP_VarBind * pvarbind,
 			           int request         		    )
{




} /* end of set_isisL2SummAddrTable() */


/* The Authentication Group */

/*
**	Process a request referencing a variable in the Authentication Group,
**      the Level 1 Area Receive Password Table
*/
static int get_isisAuthAreaRecPwdTable(ObjectInstance * poi,
				       struct type_SNMP_VarBind * pvarbind,
 				       int request         		   )
{

    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    int		sysInstance=0;		/* sysInstance, primary index */
    Password	areaRecPwd;		/* areaRecPwd, secondary index */
    StairStep		instances[HEIGHTAREARECPWD];
    int			indexLen;	/* number of elements in the indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisAuthAreaRecPwdEntry   *pAuthAreaRecPwdEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:	    return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem < pot->ot_name->oid_nelem+2) 
	    return int_SNMP_error__status_noSuchName;

	if ((sysInstance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, sysInstance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }

	/* Convert the oid after sysInstance into Password */
	oid2password(&poid->oid_elements[pot->ot_name->oid_nelem+1], &areaRecPwd,
					poid->oid_nelem-pot->ot_name->oid_nelem-1);

        if ((pAuthAreaRecPwdEntry = 
	     (IsisAuthAreaRecPwdEntry *)locateAuthAreaRecPwdEntry(
						&pMibEntry->isisAuthAreaRecPwdTable, 
					        &areaRecPwd                         )) ==
					                       (IsisAuthAreaRecPwdEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+2) {      
	    /* sysInstance and at least one byte of password are specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

	    /* Move the index values into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    oid2password(&poid->oid_elements[pot->ot_name->oid_nelem+1], &instances[1].longkey,
					              poid->oid_nelem-pot->ot_name->oid_nelem-1);

	    /* Increment the secondary index */
	    if (incByteStream(&instances[1].longkey)) {
		/* The secondary key is overflown */
		if (++instances[0].key == 0) {
		    /* The primary key is overflown */
		    return NOTOK;
		}
	    }
     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Only sysInstance was specified */
	    indexLen = 1;

	    /* Move the index value into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].longkey.maxlen = 254;
	    instances[1].longkey.len = 0;

	    /* Increment the secondary index */
	    instances[1].longkey.len = 1;		/* implementation determines the */
	    instances[1].longkey.contents[0] = 0x01;	/* order of this index */
	    
	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

	    instances[0].key = 1;
	    instances[1].longkey.maxlen = 254;
	    instances[1].longkey.len = 0;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pAuthAreaRecPwdEntry = (IsisAuthAreaRecPwdEntry *)searchEntryAreaRecPwd(
							       instances,
							       DEPTHSYSTEM           )) ==
							   (IsisAuthAreaRecPwdEntry *)NULL) {

	    return NOTOK;
	}


	extendOID = (1 + pAuthAreaRecPwdEntry->isisAuthAreaRecPwd.len) - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid in new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = 
				pAuthAreaRecPwdEntry->isisAuthAreaRecPwdSysInstance;
	octetString2oid((LongOctetString *) &pAuthAreaRecPwdEntry->isisAuthAreaRecPwd,
		  	&(pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1]));
					

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 

    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisAuthAreaRecPwdSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pAuthAreaRecPwdEntry->isisAuthAreaRecPwdSysInstance);

    case 2:			/* isisAuthAreaRecPwd, Password */
        return o_string(poi, pvarbind, pAuthAreaRecPwdEntry->isisAuthAreaRecPwd.contents,
				       pAuthAreaRecPwdEntry->isisAuthAreaRecPwd.len  );

    case 3:			/* isisAuthAreaRecPwdExistState, ExistState */
	return o_integer(poi, pvarbind, pAuthAreaRecPwdEntry->isisAuthAreaRecPwdExistState);

    default:
	return int_SNMP_error__status_noSuchName;

    } 



} /* end of get_isisAuthAreaRecPwdTable() */

static void set_isisAuthAreaRecPwdTable(ObjectInstance * poi,
			    struct type_SNMP_VarBind * pvarbind,
 			    int request         		    )
{




} /* set_isisAuthAreaRecPwdTable() */

/*
**	Process a request referencing a variable in the Authentication Group,
**   	the Level 2 Domain Receive Password Table
*/
static int get_isisAuthDomainRecPwdTable(ObjectInstance * poi,
					 struct type_SNMP_VarBind * pvarbind,
 					 int request         		     )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    int		sysInstance=0;		/* sysInstance, primary index */
    Password	domainRecPwd;		/* domainRecPwd, secondary index */
    StairStep		instances[HEIGHTDOMAINRECPWD];
    int			indexLen;	/* number of elements in the indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisAuthDomainRecPwdEntry   *pAuthDomainRecPwdEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem < pot->ot_name->oid_nelem+2) 
	    return int_SNMP_error__status_noSuchName;

	if ((sysInstance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, sysInstance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }

	/* Convert the oid after sysInstance into Password */
	oid2password(&poid->oid_elements[pot->ot_name->oid_nelem+1], &domainRecPwd,
					poid->oid_nelem-pot->ot_name->oid_nelem-1);

        if ((pAuthDomainRecPwdEntry = 
	     (IsisAuthDomainRecPwdEntry *)locateAuthDomainRecPwdEntry(
						&pMibEntry->isisAuthDomainRecPwdTable, 
					        &domainRecPwd                         )) ==
					                       (IsisAuthDomainRecPwdEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+2) {      
	    /* sysInstance and at least one byte of password are specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

	    /* Move the index values into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    oid2password(&poid->oid_elements[pot->ot_name->oid_nelem+1], &instances[1].longkey,
					              poid->oid_nelem-pot->ot_name->oid_nelem-1);

	    /* Increment the secondary index */
	    if (incByteStream(&instances[1].longkey)) {
		/* The secondary key is overflown */
		if (++instances[0].key == 0) {
		    /* The primary key is overflown */
		    return NOTOK;
		}
	    }
     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Only sysInstance was specified */
	    indexLen = 1;

	    /* Move the index value into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].longkey.maxlen = 254;
	    instances[1].longkey.len = 0;

	    /* Increment the secondary index */
	    instances[1].longkey.len = 1;		/* implementation determines the */
	    instances[1].longkey.contents[0] = 0x01;	/* order of this index */
	    
	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

	    instances[0].key = 1;
	    instances[1].longkey.maxlen = 254;
	    instances[1].longkey.len = 0;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pAuthDomainRecPwdEntry = (IsisAuthDomainRecPwdEntry *)searchEntryDomainRecPwd(
							       instances,
							       DEPTHSYSTEM           )) ==
							   (IsisAuthDomainRecPwdEntry *)NULL) {

	    return NOTOK;
	}


	extendOID = (1 + pAuthDomainRecPwdEntry->isisAuthDomainRecPwd.len) - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid in new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = 
				pAuthDomainRecPwdEntry->isisAuthDomainRecPwdSysInstance;
	octetString2oid((LongOctetString *) &pAuthDomainRecPwdEntry->isisAuthDomainRecPwd,
		  	&(pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1]));
					

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisAuthDomainRecPwdSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pAuthDomainRecPwdEntry->isisAuthDomainRecPwdSysInstance);

    case 2:			/* isisAuthDomainRecPwd, Password */
	return o_string(poi, pvarbind, pAuthDomainRecPwdEntry->isisAuthDomainRecPwd.contents,
				       pAuthDomainRecPwdEntry->isisAuthDomainRecPwd.len);

    case 3:			/* isisAuthDomainRecPwdExistState, ExistState */
	return o_integer(poi, pvarbind, pAuthDomainRecPwdEntry->isisAuthDomainRecPwdExistState);

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisAuthDomainRecPwdTable() */

static void set_isisAuthDomainRecPwdTable(ObjectInstance * poi,
			    struct type_SNMP_VarBind * pvarbind,
 			    int request         		    )
{




} /* end of set_isisAuthDomainRecPwdTable() */



/* The Partition Repair Group */

/*
**	Process a request referencing a variable in the Partition Repair Group,
**	the Part Repair Table
*/
static int get_isisPartRepTable(ObjectInstance * poi,
				struct type_SNMP_VarBind * pvarbind,
 				int request         		    )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    int		instance=0;		
    int		indx=0;		/* assumed index */
    StairStep 	instances[HEIGHTPARTREP];
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisPartRepTable 	*pPartRepTable;    
    IsisPartRepEntry 	*pPartRepEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;

    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem != pot->ot_name->oid_nelem+1) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[poid->oid_nelem-1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pPartRepTable = &pMibEntry->isisPartRepTable;

	indx = 1;

        if ((pPartRepEntry = 
	     (IsisPartRepEntry *)locateEntry(pPartRepTable, indx)) ==
					          (IsisPartRepEntry *)NULL ){
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    extendOID = 0;

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = 1;		/* assumed index */

	}
	else {
	    /* Only object id was specified */
	    extendOID = 1;

	    instances[0].key = 1;
	    instances[1].key = 1;		/* assumed index */

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
    	if ((pPartRepEntry = (IsisPartRepEntry *)searchEntryPartRep(
								  instances,
		                                                  HEIGHTPARTREP,
						                  DEPTHSYSTEM      )) ==
		                                              (IsisPartRepEntry *)NULL) {
	    
	    return NOTOK;
	}
	/* pPartRepEntry points to the desired entry */

	if (extendOID) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* New binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = instances[0].key;

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisPartRepSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pPartRepEntry->isisPartRepSysInstance);

    case 2:			/* isisPartRepMaxVirtAdj, INTEGER */
	return o_integer(poi, pvarbind, pPartRepEntry->isisPartRepMaxVirtAdj);

    case 3:			/* isisPartRepDesL2IS, SystemID */
	return o_string(poi, pvarbind, pPartRepEntry->isisPartRepDesL2IS.contents,
				       pPartRepEntry->isisPartRepDesL2IS.len );

    case 4:			/* isisPartRepVirtLinkChgs, Counter */
	return o_number(poi, pvarbind, pPartRepEntry->isisPartRepVirtLinkChgs);

    default:
	return int_SNMP_error__status_noSuchName;

    } 



} /* end of get_isisPartRepTable() */

static void set_isisPartRepTable(ObjectInstance * poi,
			    struct type_SNMP_VarBind * pvarbind,
 			    int request         		    )
{


} /* set_isisPartRepTable() */

/*
**	Process a request referencing a variable in the Partition Repair Group,
**	the Partition Area Address Table
*/
static int get_isisPartAreaAddrTable(ObjectInstance * poi,
				     struct type_SNMP_VarBind * pvarbind,
 				     int request         		 )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    int		sysInstance=0;		/* sysInstance, primary index */
    OSINSAddress	partAreaAddr;	/* partAreaAddress, secondary index */
    StairStep		instances[HEIGHTPARTAREAADDR];
    int			indexLen;	/* number of elements in the indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisPartAreaAddrEntry *pPartAreaAddrEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;

    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem < pot->ot_name->oid_nelem+2) 
	    return int_SNMP_error__status_noSuchName;

	if ((sysInstance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, sysInstance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }

	/* Convert the oid after sysInstance into OSINSAddress */
	oid2net20(&poid->oid_elements[pot->ot_name->oid_nelem+1], 
		  (OSINSAddress *) &partAreaAddr,
		  poid->oid_nelem-pot->ot_name->oid_nelem-1);

        if ((pPartAreaAddrEntry = 
	     (IsisPartAreaAddrEntry *)locatePartAreaAddrEntry(&pMibEntry->isisPartAreaAddrTable, 
					         	      &partAreaAddr                   )) ==
					          	    (IsisPartAreaAddrEntry *)NULL        ){
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+2) {      
	    /* sysInstance and at least one byte of address are specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

	    /* Move the index values into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    oid2net20(&poid->oid_elements[pot->ot_name->oid_nelem+1], 
		      (OSINSAddress *) &instances[1].longkey,
		      poid->oid_nelem-pot->ot_name->oid_nelem-1);

	    /* Increment the secondary index */
	    if (incByteStream(&instances[1].longkey)) {
		/* The secondary key is overflown */
		if (++instances[0].key == 0) {
		    /* The primary key is overflown */
		    return NOTOK;
		}
	    }
     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Only sysInstance was specified */
	    indexLen = 1;

	    /* Move the index value into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].longkey.maxlen = 20;
	    instances[1].longkey.len = 0;

	    /* Increment the secondary index */
	    instances[1].longkey.len = 1;		/* implementation determines the */
	    instances[1].longkey.contents[0] = 0x01;	/* order of this index */
	    
	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

	    instances[0].key = 1;
	    instances[1].longkey.maxlen = 20;
	    instances[1].longkey.len = 0;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pPartAreaAddrEntry = (IsisPartAreaAddrEntry *)searchEntryPartAreaAddr(instances,
								        DEPTHSYSTEM       )) ==
							           (IsisPartAreaAddrEntry *)NULL) {

	    return NOTOK;
	}


	extendOID = (1 + pPartAreaAddrEntry->isisPartAreaAddr.len) - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid in new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = 
					pPartAreaAddrEntry->isisPartAreaAddrSysInstance;
	octetString2oid((LongOctetString *) &pPartAreaAddrEntry->isisPartAreaAddr,
		  	&(pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1]));
					

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisPartAreaAddrSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pPartAreaAddrEntry->isisPartAreaAddrSysInstance);

    case 2:			/* isisPartAreaAddr, OSINSAddress */
	return o_string(poi, pvarbind, pPartAreaAddrEntry->isisPartAreaAddr.contents,
				       pPartAreaAddrEntry->isisPartAreaAddr.len);
    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisPartAreaAddrTable() */



/*
**	Process a request referencing a variable in the Virtual Adjacency Table
*/
static int get_isisVirtAdjTable(ObjectInstance * poi,
			        struct type_SNMP_VarBind * pvarbind,
 				int request         		    )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    int		instance=0;		/* SysInstance */
    int		virtAdjIndex=0;		/* virtual adj index */
    StairStep 	instances[HEIGHTVIRTADJ];
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisVirtAdjTable	*pVirtAdjTable;
    IsisVirtAdjEntry 	*pVirtAdjEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem != pot->ot_name->oid_nelem+2) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[poid->oid_nelem-2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pVirtAdjTable = &pMibEntry->isisVirtAdjTable;

	if ((virtAdjIndex = poid->oid_elements[poid->oid_nelem-1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pVirtAdjEntry = (IsisVirtAdjEntry *)locateEntry(pVirtAdjTable, 
							     virtAdjIndex  )) ==
					                    (IsisVirtAdjEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+2) {      
	    /* Instance and virtAdj index were specified */
	    extendOID = 0;

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1] + 1;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    extendOID = 1;

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = 1;

	}
	else {
	    /* Only object id was specified */
	    extendOID = 2;

	    instances[0].key = 1;
	    instances[1].key = 1;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
    	if ((pVirtAdjEntry = (IsisVirtAdjEntry *)searchEntryVirtAdj(instances,
		                                             HEIGHTVIRTADJ,
						             DEPTHSYSTEM   )) ==
		                                     (IsisVirtAdjEntry *)NULL) {
	    
	    return NOTOK;
	}
	/* pVirtAdjEntry points to the desired entry */


	if (extendOID) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* New binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = instances[0].key;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = instances[1].key;

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisVirtAdjSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pVirtAdjEntry->isisVirtAdjSysInstance);

    case 2:			/* isisVirtAdjIndex, INTEGER */
	return o_integer(poi, pvarbind, pVirtAdjEntry->isisVirtAdjIndex);

    case 3:			/* isisVirtAdjNET, OSINSAddress */
	return o_string(poi, pvarbind, pVirtAdjEntry->isisVirtAdjNET.contents,
				       pVirtAdjEntry->isisVirtAdjNET.len	);

    case 4:			/* isisVirtAdjMetric, PathCost */
	return o_integer(poi, pvarbind, pVirtAdjEntry->isisVirtAdjMetric);

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisVirtAdjTable() */


/* The Circuit Group */

/*
**	Process a request referencing a variable in the Circuit Group,
**   	the Circuit Table
*/
static int get_isisCircTable(ObjectInstance * poi,
			     struct type_SNMP_VarBind * pvarbind,
 			     int request         		     )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    StairStep 	instances[HEIGHTCIRCUIT];
    int		instance=0;		/* SysInstance */
    int		circIndex=0;		/* index to a circuit */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisCircTable	*pCircTable;
    IsisCircEntry 	*pCircEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem != pot->ot_name->oid_nelem+2) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[poid->oid_nelem-2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pCircTable = &pMibEntry->isisCircTable;

	if ((circIndex = poid->oid_elements[poid->oid_nelem-1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, circIndex)) ==
					                    (IsisCircEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+2) {      
	    /* Instance and circuit index were specified */
	    extendOID = 0;

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1] + 1;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    extendOID = 1;

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = 1;

	}
	else {
	    /* Only object id was specified */
	    extendOID = 2;

	    instances[0].key = 1;
	    instances[1].key = 1;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
    	if ((pCircEntry = (IsisCircEntry *)searchEntry(instances,
		                                       HEIGHTCIRCUIT,
						       DEPTHSYSTEM   )) ==
		                                     (IsisCircEntry *)NULL) {
	    
	    return NOTOK;
	}
	/* pCircEntry points to the desired circuit entry */


	if (extendOID) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* New binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = instances[0].key;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = instances[1].key;

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisCircSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pCircEntry->isisCircSysInstance);

    case 2:			/* isisCircIndex, INTEGER */
	return o_integer(poi, pvarbind, pCircEntry->isisCircIndex);

    case 3:			/* isisCircIfIndex, INTEGER */
	return o_integer(poi, pvarbind, pCircEntry->isisCircIfIndex);

    case 4:			/* isisCircOperState, OperState */
	return o_integer(poi, pvarbind, pCircEntry->isisCircOperState);

    case 5:			/* isisCircExistState, ExistState */
	return o_integer(poi, pvarbind, pCircEntry->isisCircExistState);

    case 6:			/* isisCircType, INTEGER */
	return o_integer(poi, pvarbind, pCircEntry->isisCircType);

    case 7:			/* isisCircISISHelloTimer, INTEGER */
	return o_integer(poi, pvarbind, pCircEntry->isisCircISISHelloTimer);

    case 8:			/* isisCircL1DefaultMetric, DefaultMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircL1DefaultMetric);

    case 9:			/* isisCircL1DelayMetric, OtherMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircL1DelayMetric);

    case 10:			/* isisCircL1ExpenseMetric, OtherMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircL1ExpenseMetric);

    case 11:			/* isisCircL1ErrorMetric, OtherMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircL1ErrorMetric);

    case 12:			/* isisCircExtDomain, Boolean */
	return o_integer(poi, pvarbind, pCircEntry->isisCircExtDomain);

    case 13:			/* isisCircAdjChanges, Counter */
	return o_number(poi, pvarbind, pCircEntry->isisCircAdjChanges);

    case 14:			/* isisCircInitFails, Counter */
	return o_number(poi, pvarbind, pCircEntry->isisCircInitFails);

    case 15:			/* isisCircRejAdjs, Counter */
	return o_number(poi, pvarbind, pCircEntry->isisCircRejAdjs);

    case 16:			/* isisCircOutCtrlPDUs, Counter */
	return o_number(poi, pvarbind, pCircEntry->isisCircOutCtrlPDUs);

    case 17:			/* isisCircInCtrlPDUs, Counter */
	return o_number(poi, pvarbind, pCircEntry->isisCircInCtrlPDUs);

    case 18:			/* isisCircIDFieldLenMismatches, Counter */
	return o_number(poi, pvarbind, pCircEntry->isisCircIDFieldLenMismatches);

    case 19:			/* isisCircMaxAreaAddrMismatches, Counter */
	return o_number(poi, pvarbind, pCircEntry->isisCircMaxAreaAddrMismatches);

    case 20:			/* isisCircL2DefaultMetric, DefaultMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircL2DefaultMetric);

    case 21:			/* isisCircL2DelayMetric, OtherMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircL2DelayMetric);

    case 22:			/* isisCircL2ExpenseMetric, OtherMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircL2ExpenseMetric);

    case 23:			/* isisCircL2ErrorMetric, OtherMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircL2ErrorMetric);

    case 24:			/* isisCircManL2Only, Boolean */
	return o_integer(poi, pvarbind, pCircEntry->isisCircManL2Only);

    case 25:			/* isisCircL1ISPriority, ISPriority */
	return o_integer(poi, pvarbind, pCircEntry->isisCircL1ISPriority);

    case 26:			/* isisCircL1CircID, CircuitID */
	return o_string(poi, pvarbind, pCircEntry->isisCircL1CircID.contents,
				       pCircEntry->isisCircL1CircID.len  	);

    case 27:			/* isisCircL1DesIS, SystemID */
	return o_string(poi, pvarbind, pCircEntry->isisCircL1DesIS.contents,
				       pCircEntry->isisCircL1DesIS.len  	);

    case 28:			/* isisCircLANL1DesISChanges, Counter */
  	return o_number(poi, pvarbind, pCircEntry->isisCircLANL1DesISChanges);

    case 29:			/* isisCircL2ISPriority, ISPriority */
	return o_integer(poi, pvarbind, pCircEntry->isisCircL2ISPriority);

    case 30:			/* isisCircL2CircID, CiucuitID */
	return o_string(poi, pvarbind, pCircEntry->isisCircL2CircID.contents,
				       pCircEntry->isisCircL2CircID.len  	);

    case 31:			/* isisCircL2DesIS, SystemID */
	return o_string(poi, pvarbind, pCircEntry->isisCircL2DesIS.contents,
				       pCircEntry->isisCircL2DesIS.len  	);

    case 32:			/* isisCircLANL2DesISChanges, Counter */
	return o_number(poi, pvarbind, pCircEntry->isisCircLANL2DesISChanges);

    case 33:			/* isisCircMCAddr, INTEGER */
	return o_integer(poi, pvarbind, pCircEntry->isisCircMCAddr);

    case 34:			/* isisCircPtToPtCircID, CircuitID */
	return o_string(poi, pvarbind, pCircEntry->isisCircPtToPtCircID.contents,
				       pCircEntry->isisCircPtToPtCircID.len  	 );

    case 35:			/* isisCircStaticCallInfo, OBJECT IDENTIFIER */
	return o_specific(poi, pvarbind, text2oid("0.0"));     /* ??? */

    case 36:			/* isisCircDACallDefMetInc, OtherMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircDACallDefMetInc);

    case 37:			/* isisCircDACallDelMetInc, OtherMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircDACallDelMetInc);

    case 38:			/* isisCircDACallErrMetInc, OtherMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircDACallErrMetInc);

    case 39:			/* isisCircDACallExpMetInc, OtherMetric */
	return o_integer(poi, pvarbind, pCircEntry->isisCircDACallExpMetInc);

    case 40:			/* isisCircAuthTransPwd. Password */
   	return o_string(poi, pvarbind, pCircEntry->isisCircAuthTransPwd.contents,
				       pCircEntry->isisCircAuthTransPwd.len   	 );

    case 41:			/* isisCircAuthFails, Counter */
	return o_number(poi, pvarbind, pCircEntry->isisCircAuthFails);

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisCircTable() */


static void set_isisCircTable(ObjectInstance * poi,
			    struct type_SNMP_VarBind * pvarbind,
 			    int request         		    )
{




} /* end of set_isisCircTable() */


/* The Ciucuit IS Group */

/*
**	Process a request to the Circuit IS Table 
*/
static int get_isisCircISTable(ObjectInstance * poi,
			       struct type_SNMP_VarBind * pvarbind,
 			       int request         		    )
{

    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    StairStep 	instances[HEIGHTCIRCIS];
    int		instance=0;		/* SysInstance, primary index */
    int		circIndex=0;		/* index to a circuit, secondary index */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisCircTable	*pCircTable;
    IsisCircEntry 	*pCircEntry;
    IsisCircISEntry	*pCircISEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem != pot->ot_name->oid_nelem+2) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[poid->oid_nelem-2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pCircTable = &pMibEntry->isisCircTable;

	if ((circIndex = poid->oid_elements[poid->oid_nelem-1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, circIndex)) ==
					                    (IsisCircEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }

	pCircISEntry = &pCircEntry->isisCircISEntry;

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+2) {      
	    /* Instance and circuit index were specified */
	    extendOID = 0;

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1] + 1;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    extendOID = 1;

	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = 1;

	}
	else {
	    /* Only object id was specified */
	    extendOID = 2;

	    instances[0].key = 1;
	    instances[1].key = 1;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
    	if ((pCircEntry = (IsisCircEntry *)searchEntry(instances,
		                                       HEIGHTCIRCUIT,
						       DEPTHSYSTEM   )) ==
		                                     (IsisCircEntry *)NULL) {
	    
	    return NOTOK;
	}
	/* pCircEntry points to the desired circuit entry */

	pCircISEntry = &pCircEntry->isisCircISEntry;


	if (extendOID) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid for new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = instances[0].key;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = instances[1].key;

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisCircISSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pCircEntry->isisCircSysInstance); /* in parent entry */

    case 2:			/* isisCircISIndex, INTEGER */
	return o_integer(poi, pvarbind, pCircEntry->isisCircIndex); /* in parent entry */

    case 3:			/* isisCircISExistState, ExistState */
	return o_integer(poi, pvarbind, pCircISEntry->isisCircISExistState);

    case 4:			/* isisCircISOperState, OperState */
	return o_integer(poi, pvarbind, pCircISEntry->isisCircISOperState);

    case 5:			/* isisCircISHoldTimerMult, INTEGER */
	return o_integer(poi, pvarbind, pCircISEntry->isisCircISHoldTimerMult);

    case 6:			/* isisCircISConfTimer, INTEGER */
	return o_integer(poi, pvarbind, pCircISEntry->isisCircISConfTimer);

    case 7:			/* isisCircISSuggESConfTimer, INTEGER */
	return o_integer(poi, pvarbind, pCircISEntry->isisCircISSuggESConfTimer);

    case 8:			/* isisCircISRedHoldTime, INTEGER */
	return o_integer(poi, pvarbind, pCircISEntry->isisCircISRedHoldTime);

    case 9:			/* isisCircISMCAddr, INTEGER */
	return o_integer(poi, pvarbind, pCircISEntry->isisCircISMCAddr);

    case 10:			/* isisCircISESReachChgs, Counter */
	return o_number(poi, pvarbind, pCircISEntry->isisCircISESReachChgs);

    case 11:			/* isisCircISInv9542PDUs, Counter */
	return o_number(poi, pvarbind, pCircISEntry->isisCircISInv9542PDUs);

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisCircISTable() */


static void set_isisCircISTable(ObjectInstance * poi,
			       struct type_SNMP_VarBind * pvarbind,
 			       int request         		    )
{


} /* end of set_isisCircISTable() */



/* The Circuit Authentication Group */

/*
**	Process a request referencing a variable in the Circuit Authentication Group,
**   	the Circuit Receive Password Table
*/
static int get_isisCircAuthRecPwdTable(ObjectInstance * poi,
				       struct type_SNMP_VarBind * pvarbind,
 				       int request         		       )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    StairStep   instances[HEIGHTCIRCAUTHRECPWD];
    int		instance=0;		/* SysInstance, primary index */
    int		circIndex=0;		/* index to a circuit, secondary index */
    Password	circRecPwd;		/* password, tertiary index */
    int		indexLen;		/* number of elements in the indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisCircTable	*pCircTable;
    IsisCircEntry 	*pCircEntry;
    IsisCircAuthRecPwdTable	*pCircAuthRecPwdTable;
    IsisCircAuthRecPwdEntry	*pCircAuthRecPwdEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem < pot->ot_name->oid_nelem+3) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pCircTable = &pMibEntry->isisCircTable;

	if ((circIndex = poid->oid_elements[pot->ot_name->oid_nelem+1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, circIndex)) ==
					                    (IsisCircEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
        pCircAuthRecPwdTable = &pCircEntry->isisCircAuthRecPwdTable;

	oid2password(&poid->oid_elements[pot->ot_name->oid_nelem+2], &circRecPwd,
					poid->oid_nelem-pot->ot_name->oid_nelem-2);

        if ((pCircAuthRecPwdEntry = 
	     (IsisCircAuthRecPwdEntry *)locateCircAuthRecPwdEntry(pCircAuthRecPwdTable, 
						                  &circRecPwd          )) ==
				  	                     (IsisCircAuthRecPwdEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	/* pCircAuthRecPwdEntry points to the desired entry */

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+3) {      
	    /* Instance, circuit index and at least one byte of recPwd were specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

	    /* Move the index values into the stair structure */
	    instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
	    instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
	    oid2password(&poid->oid_elements[pot->ot_name->oid_nelem+2], &instances[2].longkey,
					              poid->oid_nelem-pot->ot_name->oid_nelem-2);

	    /* Increment the tertiary index */
	    if (incByteStream(&instances[2].longkey)) {
		/* The tertiary key is overflown */
		if (++instances[1].key == 0) {
		    /* The secondary key is overflown */
		    if (++instances[0].key == 0) {
		     	/* The primary key is overflown */
		    	return NOTOK;
		    }
		}
	    }
        }
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+2) {      
	    /* Only instance, circuit index were specified */
	    indexLen = 2;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].longkey.maxlen = 254;
            instances[2].longkey.len = 0;

	    /* Increment tertiary index */
            instances[2].longkey.len = 1;
            instances[2].longkey.contents[0] = 0x01;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Only instance was specified */
	    indexLen = 1;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = 1;
            instances[2].longkey.maxlen = 254;
            instances[2].longkey.len = 0;

	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

            instances[0].key = 1;
            instances[1].key = 1;
            instances[2].longkey.maxlen = 254;
            instances[2].longkey.len = 0;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pCircAuthRecPwdEntry = 
	     (IsisCircAuthRecPwdEntry *)searchEntryCircAuthRecPwd(instances,
							          DEPTHSYSTEM)) ==
						   (IsisCircAuthRecPwdEntry *)NULL) {

	    return NOTOK;
	}
    	/* pCircAuthRecPwdEntry points to the desired entry */


	extendOID = (2 + pCircAuthRecPwdEntry->isisCircAuthRecPwd.len) - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid in new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = 
				pCircAuthRecPwdEntry->isisCircAuthRecPwdSysInstance;
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = 
				pCircAuthRecPwdEntry->isisCircAuthRecPwdCircIndex;
	octetString2oid((LongOctetString *) &pCircAuthRecPwdEntry->isisCircAuthRecPwd,
		  	&(pvarbind->name->oid_elements[pot->ot_name->oid_nelem+2]));

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:           		/* isisCircAuthRecPwdSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pCircAuthRecPwdEntry->isisCircAuthRecPwdSysInstance);

    case 2:			/* isisCircAuthRecPwdCircIndex, INTEGER */
	return o_integer(poi, pvarbind, pCircAuthRecPwdEntry->isisCircAuthRecPwdCircIndex);

    case 3:			/* isisCircAuthRecPwd, Password */
        return o_string(poi, pvarbind, pCircAuthRecPwdEntry->isisCircAuthRecPwd.contents,
				       pCircAuthRecPwdEntry->isisCircAuthRecPwd.len      );

    case 4:			/* isisCircAuthRecPwdExistState, ExistState */
	return o_integer(poi, pvarbind, pCircAuthRecPwdEntry->isisCircAuthRecPwdExistState);

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisCircAuthRecPwdTable() */

static void set_isisCircAuthRecPwdTable(ObjectInstance * poi,
			    struct type_SNMP_VarBind * pvarbind,
 			    int request         		    )
{

} /* end of set_isisCircAuthRecPwdTable() */



/* The IS Adjacency Group */

/*
**	Process a request referencing a variable in the IS Adjacency Group,
**    	the IS Adjacency Table
*/
static int get_isisISAdjTable(ObjectInstance * poi,
			      struct type_SNMP_VarBind * pvarbind,
 			      int request         		      )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    StairStep   instances[HEIGHTISADJ];
    int		instance=0;		/* SysInstance */
    int		circIndex=0;		/* index to a circuit */
    int		adjIndex=0;		/* index to an adjacency */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisCircTable	*pCircTable;
    IsisCircEntry 	*pCircEntry;
    IsisISAdjTable	*pISAdjTable;
    IsisISAdjEntry	*pISAdjEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem != pot->ot_name->oid_nelem+3) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[poid->oid_nelem-3]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pCircTable = &pMibEntry->isisCircTable;

	if ((circIndex = poid->oid_elements[poid->oid_nelem-2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, circIndex)) ==
					                    (IsisCircEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
        pISAdjTable = &pCircEntry->isisISAdjTable;

	if ((adjIndex = poid->oid_elements[poid->oid_nelem-1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pISAdjEntry = (IsisISAdjEntry *)locateEntry(pISAdjTable, adjIndex)) ==
					                    (IsisISAdjEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	/* pISAdjEntry points to the desired IS Adj entry */

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem == pot->ot_name->oid_nelem+3) {      
	    /* Instance and circuit index and adj index  were specified */
	    extendOID = 0;	    

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = poid->oid_elements[pot->ot_name->oid_nelem+2] + 1;

        }
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+2) {      
	    /* Instance and circuit index were specified */
	    extendOID = 1;	    

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = 1;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    extendOID = 2;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = 1;
            instances[2].key = 1;

	}
	else {
	    /* Only object id was specified */
	    extendOID = 3;

            instances[0].key = 1;
            instances[1].key = 1;
            instances[2].key = 1;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pISAdjEntry = (IsisISAdjEntry *)searchEntry(instances,
							 HEIGHTISADJ,
							 DEPTHSYSTEM )) ==
						     (IsisISAdjEntry *)NULL) {

	    return NOTOK;
	}
    	/* pISAdjEntry points to the desired IS Adj entry */

	if (extendOID) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* New binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = instances[0].key;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = instances[1].key;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+2] = instances[2].key;

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisISAdjSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pISAdjEntry->isisISAdjSysInstance);

    case 2:			/* isisISAdjCircIndex, INTEGER */
	return o_integer(poi, pvarbind, pISAdjEntry->isisISAdjCircIndex);

    case 3:			/* isisISAdjIndex, INTEGER */
	return o_integer(poi, pvarbind, pISAdjEntry->isisISAdjIndex);

    case 4:			/* isisISAdjState, INTEGER */
	return o_integer(poi, pvarbind, pISAdjEntry->isisISAdjState);

    case 5:			/* isisISAdjNeighSNPAAddress, SNPAAddress */
	return o_string(poi, pvarbind, pISAdjEntry->isisISAdjNeighSNPAAddress.contents,
				       pISAdjEntry->isisISAdjNeighSNPAAddress.len    );

    case 6:			/* isisISAdjNeighSysType, INTEGER */
	return o_integer(poi, pvarbind, pISAdjEntry->isisISAdjNeighSysType);

    case 7:			/* isisISAdjNeighSysID, OCTET STRING */
	return o_string(poi, pvarbind, pISAdjEntry->isisISAdjNeighSysID.contents,
				       pISAdjEntry->isisISAdjNeighSysID.len      );

    case 8:			/* isisISAdjUsage, INTEGER */
	return o_integer(poi, pvarbind, pISAdjEntry->isisISAdjUsage);

    case 9:			/* isisISAdjHoldTimer, INTEGER */
	return o_integer(poi, pvarbind, pISAdjEntry->isisISAdjHoldTimer);

    case 10:			/* isisISAdjNeighPriority, ISPriority */
	return o_integer(poi, pvarbind, pISAdjEntry->isisISAdjNeighPriority);

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisISAdjTable() */

/*
**	Process a request referencing a variable in the IS Adjacency Group,
**	the IS Adjacency Area Address Table
*/
static int get_isisISAdjAreaAddrTable(ObjectInstance * poi,
				      struct type_SNMP_VarBind * pvarbind,
 				      int request         		  )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    StairStep   instances[HEIGHTISADJAREAADDR];
    int		instance=0;		/* SysInstance */
    int		circIndex=0;		/* index to a circuit */
    int		adjIndex=0;		/* index to an adjacency */
    OSINSAddress	isAdjAreaAddr;	/* index to areaAddr */
    int			indexLen;	/* number of elements in indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisCircTable	*pCircTable;
    IsisCircEntry 	*pCircEntry;
    IsisISAdjTable	*pISAdjTable;
    IsisISAdjEntry	*pISAdjEntry;
    IsisISAdjAreaAddrTable	*pISAdjAreaAddrTable;
    IsisISAdjAreaAddrEntry	*pISAdjAreaAddrEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;

    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem < pot->ot_name->oid_nelem+4) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pCircTable = &pMibEntry->isisCircTable;

	if ((circIndex = poid->oid_elements[pot->ot_name->oid_nelem+1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, circIndex)) ==
					                    (IsisCircEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
        pISAdjTable = &pCircEntry->isisISAdjTable;

	if ((adjIndex = poid->oid_elements[pot->ot_name->oid_nelem+2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pISAdjEntry = (IsisISAdjEntry *)locateEntry(pISAdjTable, adjIndex)) ==
					                    (IsisISAdjEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	pISAdjAreaAddrTable = &pISAdjEntry->isisISAdjAreaAddrTable;

	/* Convert the oid after adj index into OSINSAddress */
	oid2net20(&poid->oid_elements[pot->ot_name->oid_nelem+3], 
		  (OSINSAddress *) &isAdjAreaAddr,
		  poid->oid_nelem-pot->ot_name->oid_nelem-3);

        if ((pISAdjAreaAddrEntry = (IsisISAdjAreaAddrEntry *)locateIsAdjAreaAddrEntry(
							pISAdjAreaAddrTable, &isAdjAreaAddr)) ==
				                                  (IsisISAdjAreaAddrEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	/* pISAdjAreaAddrEntry points to the desired IS Adj Area Address entry */

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+4) {      
	    /* Instance, circuit index, adj index and area addr were specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

	    /* Move the index values into the stair structure */
            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = poid->oid_elements[pot->ot_name->oid_nelem+2];

	    oid2net20(&poid->oid_elements[pot->ot_name->oid_nelem+3], 
		      (OSINSAddress *) &instances[3].longkey,
		      poid->oid_nelem-pot->ot_name->oid_nelem-3);

	    /* Increment the area addr index */
	    if (incByteStream(&instances[3].longkey)) {
		/* The area addr is overflown */
		if (++instances[2].key == 0) {
		    /* The adj index is overflown */
		    if (++instances[1].key == 0) {
			/* The circ index is overflown */
			if (++instances[0].key == 0) {
			    /* The sysInstance is overflown */
			    return NOTOK;
			}
		    }
		}
	    }
	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+3) {      
	    /* Instance, circuit index and adj index were specified */
	    indexLen = 3;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key= poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = poid->oid_elements[pot->ot_name->oid_nelem+2];
            instances[3].longkey.maxlen = 20;
	    instances[3].longkey.len = 1;
	    instances[3].longkey.contents[0] = 0x01;
	
        }
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+2) {      
	    /* Instance and circuit index were specified */
	    indexLen = 2;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = 1;
            instances[3].longkey.maxlen = 20;
	    instances[3].longkey.len = 1;
	    instances[3].longkey.contents[0] = 0x01;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    indexLen = 1;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = 1;
            instances[2].key = 1;
            instances[3].longkey.maxlen = 20;
	    instances[3].longkey.len = 1;
	    instances[3].longkey.contents[0] = 0x01;

	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

            instances[0].key = 1;
            instances[1].key = 1;
            instances[2].key = 1;
            instances[3].longkey.maxlen = 20;
	    instances[3].longkey.len = 1;
	    instances[3].longkey.contents[0] = 0x01;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pISAdjAreaAddrEntry = (IsisISAdjAreaAddrEntry *)searchEntry(instances,
							            HEIGHTISADJAREAADDR,
							            DEPTHSYSTEM     )) ==
						        (IsisISAdjAreaAddrEntry *)NULL) {

	    return NOTOK;
	}
    	/* pISAdjAreaAddrEntry points to the desired IS Adj Area Address entry */

	extendOID = (3 + pISAdjAreaAddrEntry->isisISAdjAreaAddress.len) - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid in new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = 
					pISAdjAreaAddrEntry->isisISAdjAreaAddrSysInstance;
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = 
					pISAdjAreaAddrEntry->isisISAdjAreaAddrCircIndex;
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+2] = 
					pISAdjAreaAddrEntry->isisISAdjAreaAddrAdjIndex;
	octetString2oid((LongOctetString *) &pISAdjAreaAddrEntry->isisISAdjAreaAddress,
		  	&(pvarbind->name->oid_elements[pot->ot_name->oid_nelem+3]));

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisISAdjAreaAddrSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pISAdjAreaAddrEntry->isisISAdjAreaAddrSysInstance);

    case 2:			/* isisISAdjAreaAddrCircIndex, INTEGER */
	return o_integer(poi, pvarbind, pISAdjAreaAddrEntry->isisISAdjAreaAddrCircIndex);

    case 3:			/* isisISAdjAreaAddrAdjIndex, INTEGER */
	return o_integer(poi, pvarbind, pISAdjAreaAddrEntry->isisISAdjAreaAddrAdjIndex);

    case 4:			/* isisISAdjAreaAddress, OSINSAddress */
	return o_string(poi, pvarbind, pISAdjAreaAddrEntry->isisISAdjAreaAddress.contents,
				       pISAdjAreaAddrEntry->isisISAdjAreaAddress.len    );

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisISAdjAreaAddrTable() */




/* The IS Adjacency IP Group */

/*
**	Process a request referencing a variable in the IS Adjacency IP Group,
**	the IS Adjacency IP Address Table
*/
static int get_isisISAdjIPAddrTable(ObjectInstance * poi,
				    struct type_SNMP_VarBind * pvarbind,
 				    int request         		)
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    StairStep   instances[HEIGHTISADJIPADDR];
    int		instance=0;		/* SysInstance */
    int		circIndex=0;		/* index to a circuit */
    int		adjIndex=0;		/* index to an adjacency */
    IpAddress	isAdjIPAddr;		/* IP address as index */
    int 	indexLen;		/* number of elements in indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisCircTable	*pCircTable;
    IsisCircEntry 	*pCircEntry;
    IsisISAdjTable	*pISAdjTable;
    IsisISAdjEntry	*pISAdjEntry;
    IsisISAdjIPAddrTable	*pISAdjIPAddrTable;
    IsisISAdjIPAddrEntry	*pISAdjIPAddrEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem != pot->ot_name->oid_nelem+7) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pCircTable = &pMibEntry->isisCircTable;

	if ((circIndex = poid->oid_elements[pot->ot_name->oid_nelem+1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, circIndex)) ==
					                    (IsisCircEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
        pISAdjTable = &pCircEntry->isisISAdjTable;

	if ((adjIndex = poid->oid_elements[pot->ot_name->oid_nelem+2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pISAdjEntry = (IsisISAdjEntry *)locateEntry(pISAdjTable, adjIndex)) ==
					                    (IsisISAdjEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	pISAdjIPAddrTable = &pISAdjEntry->isisISAdjIPAddrTable;


        dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+3]), 4, &isAdjIPAddr);

        if ((pISAdjIPAddrEntry = (IsisISAdjIPAddrEntry *)locateEntry(pISAdjIPAddrTable, 
								     isAdjIPAddr       )) ==
				                                (IsisISAdjIPAddrEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	/* pISAdjIPAddrEntry points to the desired IS Adj IP Address entry */

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+4) {      
	    /* Instance, circuit index, adj index and at least 1 byte of ipaddr were specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = poid->oid_elements[pot->ot_name->oid_nelem+2];
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+3]), indexLen-3, &isAdjIPAddr);
            instances[3].key = isAdjIPAddr + 1 ;
	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+3) {      
	    /* Instance, circuit index and adj index were specified */
	    indexLen = 3;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = poid->oid_elements[pot->ot_name->oid_nelem+2];
            instances[3].key = 1;
        }
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+2) {      
	    /* Instance and circuit index were specified */
	    indexLen = 2;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = 1;
            instances[3].key = 1;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    indexLen = 1;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = 1;
            instances[2].key = 1;
            instances[3].key = 1;

	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

            instances[0].key = 1;
            instances[1].key = 1;
            instances[2].key = 1;
            instances[3].key = 1;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pISAdjIPAddrEntry = (IsisISAdjIPAddrEntry *)searchEntryISAdjIPAddr(
								    instances,
							            HEIGHTISADJIPADDR,
							            DEPTHSYSTEM     )) ==
						             (IsisISAdjIPAddrEntry *)NULL) {

	    return NOTOK;
	}
    	/* pISAdjIPAddrEntry points to the desired IS Adj IP Address entry */


	extendOID = 7 - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid for new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = 
					pISAdjIPAddrEntry->isisISAdjIPAddrSysInstance;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = 
					pISAdjIPAddrEntry->isisISAdjIPAddrCircIndex;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+2] = 
					pISAdjIPAddrEntry->isisISAdjIPAddrAdjIndex;
	binary2dot(pISAdjIPAddrEntry->isisISAdjIPAddress,
		   &pvarbind->name->oid_elements[pot->ot_name->oid_nelem+3]);

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisISAdjIPAddrSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pISAdjIPAddrEntry->isisISAdjIPAddrSysInstance);

    case 2:			/* isisISAdjIPAddrCircIndex, INTEGER */
	return o_integer(poi, pvarbind, pISAdjIPAddrEntry->isisISAdjIPAddrCircIndex);

    case 3:			/* isisISAdjIPAddrAdjIndex, INTEGER */
	return o_integer(poi, pvarbind, pISAdjIPAddrEntry->isisISAdjIPAddrAdjIndex);

    case 4:			/* isisISAdjIPAddress, IpAddress */
	return o_ipaddr(poi, pvarbind, sock2unix(sockbuild_in(0,
				 			   pISAdjIPAddrEntry->isisISAdjIPAddress),
					         (int *)0                                      ));

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisISAdjIPAddrTable() */


 
/* The IS Adjacency Integrated Group */

/*
**	Process a request referencing a variable in the IS Adjacency Integrated Group,
**	the IS Adjacency Protocol Supported Table
*/
static int get_isisISAdjProtSuppTable(ObjectInstance * poi,
				      struct type_SNMP_VarBind * pvarbind,
 				      int request         		  )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    StairStep   instances[HEIGHTISADJPROTSUPP];
    int		instance=0;		/* SysInstance */
    int		circIndex=0;		/* index to a circuit */
    int		adjIndex=0;		/* index to an adjacency */
    int		protocol=0;		/* protocol specified */
    int		indexLen;		/* number of elements in indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisCircTable	*pCircTable;
    IsisCircEntry 	*pCircEntry;
    IsisISAdjTable	*pISAdjTable;
    IsisISAdjEntry	*pISAdjEntry;
    IsisISAdjProtSuppTable	*pISAdjProtSuppTable;
    IsisISAdjProtSuppEntry	*pISAdjProtSuppEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem != pot->ot_name->oid_nelem+4) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pCircTable = &pMibEntry->isisCircTable;

	if ((circIndex = poid->oid_elements[pot->ot_name->oid_nelem+1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, circIndex)) ==
					                    (IsisCircEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
        pISAdjTable = &pCircEntry->isisISAdjTable;

	if ((adjIndex = poid->oid_elements[pot->ot_name->oid_nelem+2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pISAdjEntry = (IsisISAdjEntry *)locateEntry(pISAdjTable, adjIndex)) ==
					                    (IsisISAdjEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	pISAdjProtSuppTable = &pISAdjEntry->isisISAdjProtSuppTable;

	if ((protocol = poid->oid_elements[pot->ot_name->oid_nelem+3]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pISAdjProtSuppEntry = (IsisISAdjProtSuppEntry *)locateEntry(pISAdjProtSuppTable, 
									 protocol            )) ==
				                                  (IsisISAdjProtSuppEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	/* pISAdjProtSuppEntry points to the desired IS Adj Prot Supp entry */

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+4) {      
	    /* Instance, circuit index, adj index and protocol were specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = poid->oid_elements[pot->ot_name->oid_nelem+2];
            instances[3].key = poid->oid_elements[pot->ot_name->oid_nelem+3] + 1;
	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+3) {      
	    /* Instance, circuit index and adj index  were specified */
	    indexLen = 3;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key= poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = poid->oid_elements[pot->ot_name->oid_nelem+2];
            instances[3].key = PROTSUPP_LOWEST;
        }
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+2) {      
	    /* Instance and circuit index were specified */
	    indexLen = 2;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = 1;
            instances[3].key = PROTSUPP_LOWEST;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    indexLen = 1;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = 1;
            instances[2].key = 1;
            instances[3].key = PROTSUPP_LOWEST;

	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

            instances[0].key = 1;
            instances[1].key = 1;
            instances[2].key = 1;
            instances[3].key = PROTSUPP_LOWEST;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pISAdjProtSuppEntry = (IsisISAdjProtSuppEntry *)searchEntryISAdjProtSupp(
								    instances,
							            HEIGHTISADJPROTSUPP,
							            DEPTHSYSTEM     )) ==
						        (IsisISAdjProtSuppEntry *)NULL) {

	    return NOTOK;
	}
    	/* pISAdjProtSuppEntry points to the desired IS Adj Prot Supp entry */

	extendOID = 4 - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid for new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = 
					pISAdjProtSuppEntry->isisISAdjProtSuppSysInstance;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = 
					pISAdjProtSuppEntry->isisISAdjProtSuppCircIndex;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+2] = 
					pISAdjProtSuppEntry->isisISAdjProtSuppAdjIndex;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+3] = 
					pISAdjProtSuppEntry->isisISAdjProtSuppProtocol;

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisISAdjProtSuppSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pISAdjProtSuppEntry->isisISAdjProtSuppSysInstance);

    case 2:			/* isisISAdjProtSuppCircIndex, INTEGER */
	return o_integer(poi, pvarbind, pISAdjProtSuppEntry->isisISAdjProtSuppCircIndex);

    case 3:			/* isisISAdjProtSuppAdjIndex, INTEGER */
	return o_integer(poi, pvarbind, pISAdjProtSuppEntry->isisISAdjProtSuppAdjIndex);

    case 4:			/* isisISAdjProtSuppProtocol, SupportedProtocol */
	return o_integer(poi, pvarbind, pISAdjProtSuppEntry->isisISAdjProtSuppProtocol);

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisISAdjProtSuppTable() */



/* The ES Adjacency Group */

/*
**	Process a request referencing a variable in the ES Adjacency Group,
**	the ES Adjacency Table
*/
static int get_isisESAdjTable(ObjectInstance * poi,
			      struct type_SNMP_VarBind * pvarbind,
 			      int request         		      )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    StairStep   instances[HEIGHTESADJ];
    int		instance=0;		/* SysInstance */
    int		circIndex=0;		/* index to a circuit */
    int		adjIndex=0;		/* index to an ES adjacency */
    int		indexLen;		/* number of elements in indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisCircTable	*pCircTable;
    IsisCircEntry 	*pCircEntry;
    IsisESAdjTable	*pESAdjTable;
    IsisESAdjEntry	*pESAdjEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:

	if (poid->oid_nelem < pot->ot_name->oid_nelem+3) /* ignore ESAdjESID and adjType as */
							/* indices, too messy to deal with now */
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pCircTable = &pMibEntry->isisCircTable;

	if ((circIndex = poid->oid_elements[pot->ot_name->oid_nelem+1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, circIndex)) ==
					                    (IsisCircEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
    	pESAdjTable = &pCircEntry->isisESAdjTable;

	if ((adjIndex = poid->oid_elements[pot->ot_name->oid_nelem+2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pESAdjEntry = locateEntryESAdj(pESAdjTable, adjIndex)) ==
				                (IsisESAdjEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	/* pESAdjEntry points to the desired ES Adj entry */

    	break;

    case type_SMUX_PDUs_get__next__request:

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+3) {      
	    /* Instance, circuit index and adj index were specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = poid->oid_elements[pot->ot_name->oid_nelem+2] + 1;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+2) {      
	    /* Instance and circuit index were specified */
	    indexLen = 2;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key= poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = 1;

        }
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {      
	    /* Instance was specified */
	    indexLen = 1;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = 1;
            instances[2].key = 1;

     	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

            instances[0].key = 1;
            instances[1].key = 1;
            instances[2].key = 1;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pESAdjEntry = (IsisESAdjEntry *)searchEntryESAdj(instances,
							      DEPTHSYSTEM     )) ==
						             (IsisESAdjEntry *)NULL) {

	    return NOTOK;
	}
    	/* pESAdjEntry points to the desired ES Adj entry */


	extendOID = 3 - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid for new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = 
					pESAdjEntry->isisESAdjSysInstance;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = 
					pESAdjEntry->isisESAdjCircIndex;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+2] = 
					pESAdjEntry->isisESAdjAdjIndex;

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisESAdjSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pESAdjEntry->isisESAdjSysInstance);

    case 2:			/* isisESAdjCircIndex, INTEGER */
	return o_integer(poi, pvarbind, pESAdjEntry->isisESAdjCircIndex);

    case 3:			/* isisESAdjAdjIndex, INTEGER */
	return o_integer(poi, pvarbind, pESAdjEntry->isisESAdjAdjIndex);

    case 4:			/* isisESAdjType, INTEGER */
	return o_integer(poi, pvarbind, pESAdjEntry->isisESAdjType);

    case 5:			/* isisESAdjState, INTEGER */
	return o_integer(poi, pvarbind, pESAdjEntry->isisESAdjState);

    case 6: 	 		/* isisESAdjNeighSNPAAddress, SNPAAddress */
 	return o_string(poi, pvarbind, pESAdjEntry->isisESAdjNeighSNPAAddress.contents,
				       pESAdjEntry->isisESAdjNeighSNPAAddress.len      );

    case 7:			/* isisESAdjExistState, ExistState */
	return o_integer(poi, pvarbind, pESAdjEntry->isisESAdjExistState);

    case 8:			/* isisESAdjESID, SystemID */
 	return o_string(poi, pvarbind, pESAdjEntry->isisESAdjESID.contents,
				       pESAdjEntry->isisESAdjESID.len      );

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisESAdjTable() */


static void set_isisESAdjTable(ObjectInstance * poi,
			    struct type_SNMP_VarBind * pvarbind,
 			    int request         		    )
{


} /* end of set_isisESAdjTable() */



/* The Reachable Address Group */

/*
**	Process a request referencing a variable in the Reachable Address Group,
**	the Reachable Address Table
*/
static int get_isisRATable(ObjectInstance * poi,
			   struct type_SNMP_VarBind * pvarbind,
 			   int request         		       )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    StairStep   instances[HEIGHTRA];
    int		instance=0;		/* SysInstance */
    int		circIndex=0;		/* index to a circuit */
    int		raIndex=0;		/* index to an RA */
    int		indexLen;		/* number of elements in indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisCircTable	*pCircTable;
    IsisCircEntry 	*pCircEntry;
    IsisRATable		*pRATable;
    IsisRAEntry		*pRAEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem != pot->ot_name->oid_nelem+3) /* ignore RAType, too messy to */
							  /* deal with now */

							/* On the other hand, RAIndex is uniqur */
							/* within the parent citcuit. Why do we */
							/* need RAType as an index??? */
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pCircTable = &pMibEntry->isisCircTable;

	if ((circIndex = poid->oid_elements[pot->ot_name->oid_nelem+1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, circIndex)) ==
					                    (IsisCircEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
        pRATable = &pCircEntry->isisRATable;

	if ((raIndex = poid->oid_elements[pot->ot_name->oid_nelem+2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pRAEntry = (IsisRAEntry *)locateEntry(pRATable, raIndex)) ==
					                 (IsisRAEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	/* pRAEntry points to the desired RA entry */

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+3) {      
	    /* Instance, circuit index and raindex were specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = poid->oid_elements[pot->ot_name->oid_nelem+2] + 1;

        }
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+2) {      
	    /* Instance and circuit index were specified */
	    indexLen = 2;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = 1;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    indexLen = 1;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = 1;
            instances[2].key = 1;

	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

            instances[0].key = 1;
            instances[1].key = 1;
            instances[2].key = 1;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pRAEntry = (IsisRAEntry *)searchEntryRA(instances,
						     HEIGHTRA,
						     DEPTHSYSTEM )) ==
						     (IsisRAEntry *)NULL) {

	    return NOTOK;
	}
    	/* pRAEntry points to the desired ra entry */

	extendOID = 3 - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid for new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = pRAEntry->isisRASysInstance;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = pRAEntry->isisRACircIndex;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+2] = pRAEntry->isisRAIndex;

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisRASysInstance, INTEGER */
	return o_integer(poi, pvarbind, pRAEntry->isisRASysInstance);

    case 2:			/* isisRACircIndex, INTEGER */
	return o_integer(poi, pvarbind, pRAEntry->isisRACircIndex);

    case 3:			/* isisRAIndex, INTEGER */
	return o_integer(poi, pvarbind, pRAEntry->isisRAIndex);

    case 4:			/* isisRAExistState, ExistState */
	return o_integer(poi, pvarbind, pRAEntry->isisRAExistState);

    case 5:			/* isisRAOperState, OperState */
	return o_integer(poi, pvarbind, pRAEntry->isisRAOperState);

    case 6:			/* isisRAAddrPrefix, NSAPPrefix */
	return o_string(poi, pvarbind, pRAEntry->isisRAAddrPrefix.contents,
				       pRAEntry->isisRAAddrPrefix.len      );

    case 7:			/* isisRAType, INTEGER */
	return o_integer(poi, pvarbind, pRAEntry->isisRAType);

    case 8:			/* isisRAMapType, INTEGER */
	return o_integer(poi, pvarbind, pRAEntry->isisRAMapType);

    case 9:			/* isisRADefMetric, DefaultMetric */
	return o_integer(poi, pvarbind, pRAEntry->isisRADefMetric);

    case 10:			/* isisRADelMetric, OtherMetric */
	return o_integer(poi, pvarbind, pRAEntry->isisRADelMetric);

    case 11:			/* isisRAExpMetric, OtherMetric */
	return o_integer(poi, pvarbind, pRAEntry->isisRAExpMetric);

    case 12:			/* isisRAErrMetric, OtherMetric */
	return o_integer(poi, pvarbind, pRAEntry->isisRAErrMetric);

    case 13:			/* isisRADefMetricType, MetricType */
	return o_integer(poi, pvarbind, pRAEntry->isisRADefMetricType);

    case 14:			/* isisRADelMetricType, MetricType */
	return o_integer(poi, pvarbind, pRAEntry->isisRADelMetricType);

    case 15:			/* isisRAExpMetricType, MetricType */
	return o_integer(poi, pvarbind, pRAEntry->isisRAExpMetricType);

    case 16:			/* isisRAErrMetricType, MetricType */
	return o_integer(poi, pvarbind, pRAEntry->isisRAErrMetricType);

    case 17:			/* isisRASNPAAddress, SNPAAddress */
	return o_string(poi, pvarbind, pRAEntry->isisRASNPAAddress.contents,
				       pRAEntry->isisRASNPAAddress.len      );

    case 18:			/* isisRASNPAMask, SNPAPrefix */
	return o_string(poi, pvarbind, pRAEntry->isisRASNPAMask.contents,
				       pRAEntry->isisRASNPAMask.len      );

    case 19:			/* isisRASNPAPrefix, SNPAPrefix */
	return o_string(poi, pvarbind, pRAEntry->isisRASNPAPrefix.contents,
				       pRAEntry->isisRASNPAPrefix.len      );

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisRATable() */

static void set_isisRATable(ObjectInstance * poi,
			    struct type_SNMP_VarBind * pvarbind,
 			    int request         		    )
{




} /* end of set_isisRATable() */




/* The IP Reachable Address Group */


/*
**	Process a request referencing a variable in the IP Reachable Address Group,
**	the IP Reachable Address Table
*/
static int get_isisIPRATable(ObjectInstance * poi,
			     struct type_SNMP_VarBind * pvarbind,
 			     int request         		    )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    StairStep   instances[HEIGHTIPRA];
    int		instance=0;		/* SysInstance */
    int		circIndex=0;		/* index to a circuit */
    int		ipRAIndex=0;		/* index to an IPRA */
    int		indexLen;		/* number of elements in indices */
    IsisMibEntry	*pMibEntry;	/* ptr to an isis mib entry */
    IsisCircTable	*pCircTable;
    IsisCircEntry 	*pCircEntry;
    IsisIPRATable	*pIPRATable;
    IsisIPRAEntry	*pIPRAEntry;
    ObjectID 		pnewoid;	
    int			extendOID=0;


    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem != pot->ot_name->oid_nelem+3) /* ignore IPRAType as an index. */
							  /* IPRAIndex is unique within the */
							  /* the parent circuit. Why do we */
							  /* need IPRAType as an index ??? */
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[pot->ot_name->oid_nelem]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, instance)) ==
	    					             (IsisMibEntry *)NULL){
	    return int_SNMP_error__status_noSuchName;
        }
	pCircTable = &pMibEntry->isisCircTable;

	if ((circIndex = poid->oid_elements[pot->ot_name->oid_nelem+1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, circIndex)) ==
					                    (IsisCircEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
        pIPRATable = &pCircEntry->isisIPRATable;

	if ((ipRAIndex = poid->oid_elements[pot->ot_name->oid_nelem+2]) == 0) 
	    return int_SNMP_error__status_noSuchName;

        if ((pIPRAEntry = (IsisIPRAEntry *)locateEntry(pIPRATable, ipRAIndex)) ==
					                 (IsisIPRAEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
        }
	/* pIPRAEntry points to the desired IP RA entry */

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem == pot->ot_name->oid_nelem+3) {      
	    /* Instance, circuit index and ipra index were specified */
	    indexLen = poid->oid_nelem - pot->ot_name->oid_nelem;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = poid->oid_elements[pot->ot_name->oid_nelem+2] + 1;

        }
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+2) {      
	    /* Instance and circuit index were specified */
	    indexLen = 2;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = poid->oid_elements[pot->ot_name->oid_nelem+1];
            instances[2].key = 1;

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* Instance was specified */
	    indexLen = 1;

            instances[0].key = poid->oid_elements[pot->ot_name->oid_nelem];
            instances[1].key = 1;
            instances[2].key = 1;

	}
	else {
	    /* Only object id was specified */
	    indexLen = 0;

            instances[0].key = 1;
            instances[1].key = 1;
            instances[2].key = 1;

	}

	instances[0].keyhole = (unsigned char *)&isisMibTable;
	if ((pIPRAEntry = (IsisIPRAEntry *)searchEntryIPRA(instances,
						           HEIGHTIPRA,
						           DEPTHSYSTEM )) ==
						        (IsisIPRAEntry *)NULL) {

	    return NOTOK;
	}
    	/* pIPRAEntry points to the desired ipra entry */

   	extendOID = 3 - indexLen;
	if (extendOID > 0) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* Oid for new binding */
    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = pIPRAEntry->isisIPRASysInstance;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+1] = pIPRAEntry->isisIPRACircIndex;
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+2] = pIPRAEntry->isisIPRAIndex;

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisIPRASysInstance, INTEGER */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRASysInstance);

    case 2:			/* isisIPRACircIndex, INTEGER */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRACircIndex);

    case 3:			/* isisIPRAIndex, INTEGER */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRAIndex);

    case 4:			/* isisIPRADest, IpAddress */
	return o_ipaddr(poi, pvarbind, &pIPRAEntry->isisIPRADest);

    case 5:			/* isisIPRAMask, IpAddress */
	return o_ipaddr(poi, pvarbind, &pIPRAEntry->isisIPRAMask);

    case 6:			/* isisIPRAExistState, ExistState */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRAExistState);

    case 7:			/* isisIPRAOperState, OperState */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRAOperState);

    case 8:			/* isisIPRADefMetric, DefaultMetric */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRADefMetric);

    case 9:			/* isisIPRADelMetric, OtherMetric */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRADelMetric);

    case 10:			/* isisIPRAExpMetric, OtherMetric */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRAExpMetric);

    case 11:			/* isisIPRAErrMetric, OtherMetric */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRAErrMetric);

    case 12:			/* isisIPRADefMetricType, MetricType */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRADefMetricType);

    case 13:			/* isisIPRADelMetricType, MetricType */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRADelMetricType);

    case 14:			/* isisIPRAExpMetricType, MetricType */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRAExpMetricType);

    case 15:			/* isisIPRAErrMetricType, MetricType */
	return o_integer(poi, pvarbind, pIPRAEntry->isisIPRAErrMetricType);

    case 16:			/* isisIPRASNPAAddress, SNPAAddress */
	return o_string(poi, pvarbind, pIPRAEntry->isisIPRASNPAAddress.contents,
				       pIPRAEntry->isisIPRASNPAAddress.len      );

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisIPRATable() */

static void set_isisIPRATable(ObjectInstance * poi,
			    struct type_SNMP_VarBind * pvarbind,
 			    int request         		    )
{




} /* end of set_isisIPRATable() */



/* The Level 1 CLNP Destination Group */

/*
**	Process a request referencing a variable in the CLNP Destination Group,
**	the Level 1 CLNP Destination Table
*/
static int get_isisL1CLNPDestTable(ObjectInstance * poi,
				   struct type_SNMP_VarBind * pvarbind,
 				   int request         		       )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			

    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;



    case type_SMUX_PDUs_get__next__request:	return NOTOK;



    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisL1CLNPRouteDest, SystemID */
	return o_string(poi, pvarbind, dummyOctetString, 20);

    case 2:			/* isisL1CLNPRouteMetQOS, TOS */
	return o_integer(poi, pvarbind, 0);

    case 3:			/* isisL1CLNPRouteMetric, PathCost */
	return o_integer(poi, pvarbind, 0);

    case 4:			/* isisL1CLNPRouteForw, OBJECT IDENTIFIER */
	return o_specific(poi, pvarbind, text2oid("0.0"));

    case 5:			/* isisL1CLNPRouteSource, INTEGER */
	return o_integer(poi, pvarbind, 0);

    case 6:			/* isisL1CLNPSysInstance, INTEGER */
	return o_integer(poi, pvarbind, 0);


    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisL1CLNPDestTable() */

static void set_isisL1CLNPDestTable(ObjectInstance * poi,
				   struct type_SNMP_VarBind * pvarbind,
 				   int request         		       )
{

} /* end of set_isisL1CLNPDestTable() */



/* The Level 2 CLNP Destination Group */

/*
**	Process a request referencing a variable in the L2 CLNP Destination Group,
**	the Level 2 CLNP Destination Table
*/
static int get_isisL2CLNPDestTable(ObjectInstance * poi,
				   struct type_SNMP_VarBind * pvarbind,
 				   int request         		     )
{

    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    IsisL2CLNPDestEntry	*pL2CLNPDestEntry;

    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;



    case type_SMUX_PDUs_get__next__request:	return NOTOK;



    default:
	return int_SNMP_error__status_genErr;

    } 

    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisL2CLNPRouteDest, NSAPPrefix */
	return o_string(poi, pvarbind, pL2CLNPDestEntry->isisL2CLNPRouteDest.contents,
				       pL2CLNPDestEntry->isisL2CLNPRouteDest.len      );

    case 2:			/* isisL2CLNPRouteMetQOS, TOS */
	return o_integer(poi, pvarbind, pL2CLNPDestEntry->isisL2CLNPRouteMetQOS);

    case 3:			/* isisL2CLNPRouteMetType, INTEGER */
	return o_integer(poi, pvarbind, pL2CLNPDestEntry->isisL2CLNPRouteMetType);

    case 4:			/* isisL2CLNPRouteIntMetric, PathCost */
	return o_integer(poi, pvarbind, pL2CLNPDestEntry->isisL2CLNPRouteIntMetric);

    case 5:			/* isisL2CLNPRouteExtMetric, INTEGER */
	return o_integer(poi, pvarbind, pL2CLNPDestEntry->isisL2CLNPRouteExtMetric);

    case 6:			/* isisL2CLNPRouteForw, OBJECT IDENTIFIER */
	return o_specific(poi, pvarbind, text2oid("0.0"));

    case 7:			/* isisL2CLNPRouteSource, INTEGER */
	return o_integer(poi, pvarbind, pL2CLNPDestEntry->isisL2CLNPRouteSource);

    case 8:			/* isisL2CLNPSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pL2CLNPDestEntry->isisL2CLNPSysInstance);

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisL2CLNPDestTable() */


static void set_isisL2CLNPDestTable(ObjectInstance * poi,
				   struct type_SNMP_VarBind * pvarbind,
 				   int request         		     )
{

} /* end of set_isisL2CLNPDestTable() */



/* The IP Destination Group */

/*
**	Process a request referencing a variable in the IP Destination Group,
**	the IP Destination Table
*/
static int get_isisIPDestTable(ObjectInstance * poi,
			       struct type_SNMP_VarBind * pvarbind,
 			       int request         		   )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    IpAddress	ipAddr=0;
    IpAddress	ipMask=0;
    int		tos;
    int		objIdSize,i;
    IsisIPDestEntry 	*pIPDestEntry;
    int		extendOID=0;
    ObjectID	pnewoid;	
    struct sockaddr_in ipAddrTemp={0};


    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem < pot->ot_name->oid_nelem+11) /* a.d.d.r.m.a.s.k.tos.fo.rw */
	    return int_SNMP_error__status_noSuchName;

	/* Parse the object id into addr, mask, tos, and forw */
        dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 4, &ipAddr);
        dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+4]), 4, &ipMask);
	tos = poid->oid_elements[pot->ot_name->oid_nelem+8];
	objIdSize = poid->oid_nelem - pot->ot_name->oid_nelem - 9; /* at least two */

	/* Locate the IP route entry in the routing table */
	if ((pIPDestEntry = locateIPRouteEntry(ipAddr, ipMask)) == 
							(IsisIPDestEntry *)NULL) {
	    return int_SNMP_error__status_noSuchName;
	}

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem >= pot->ot_name->oid_nelem+11) {      
	    /* a.d.d.r.m.a.s.k.tos.fo.rw or more were specified */
	    extendOID = 0;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+4]), 4, &ipMask);
	    tos = poid->oid_elements[pot->ot_name->oid_nelem+8];
	    objIdSize = poid->oid_nelem - pot->ot_name->oid_nelem - 9; /* at least two */

	    if (ipMask == 0xffffffff) {
		ipMask = 0xff000000;
		ipAddr += 1;
	    }
	    else ipMask = ((ipMask >> 1) | 0x80000000);

     	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+10) {
	    /* a.d.d.r.m.a.s.k.tos.fo were specified */
	    extendOID = 1;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+4]), 4, &ipMask);
	    tos = poid->oid_elements[pot->ot_name->oid_nelem+8];
	    objIdSize = 1;

	    if (ipMask == 0xffffffff) {
		ipMask = 0xff000000;
		ipAddr += 1;
	    }
	    else ipMask = ((ipMask >> 1) | 0x80000000);

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+9) {
	    /* a.d.d.r.m.a.s.k.tos were specified */
	    extendOID = 2;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+4]), 4, &ipMask);
	    tos = poid->oid_elements[pot->ot_name->oid_nelem+8];
	    objIdSize = 0;

	    if (ipMask == 0xffffffff) {
		ipMask = 0xff000000;
		ipAddr += 1;
	    }
	    else ipMask = ((ipMask >> 1) | 0x80000000);

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+8) {
	    /* a.d.d.r.m.a.s.k were specified */
	    extendOID = 3;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+4]), 4, &ipMask);
	    tos = 0;
	    objIdSize = 0;

	    if (ipMask == 0xffffffff) {
		ipMask = 0xff000000;
		ipAddr += 1;
	    }
	    else ipMask = ((ipMask >> 1) | 0x80000000);

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+7) {
	    /* a.d.d.r.m.a.s were specified */
	    extendOID = 4;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+4]), 3, &ipMask);
	    tos = 0;
	    objIdSize = 0;

	    ipMask = ((ipMask >> 1) | 0x80000000);

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+6) {
	    /* a.d.d.r.m.a were specified */
	    extendOID = 5;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+4]), 2, &ipMask);
	    tos = 0;
	    objIdSize = 0;

	    ipMask = ((ipMask >> 1) | 0x80000000);

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+5) {
	    /* a.d.d.r.m were specified */
	    extendOID = 6;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 4, &ipAddr);
            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem+4]), 1, &ipMask);
	    tos = 0;
	    objIdSize = 0;

	    ipMask = ((ipMask >> 1) | 0x80000000);

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+4) {
	    /* a.d.d.r were specified */
	    extendOID = 7;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 4, &ipAddr);
	    ipMask = 0xff000000;
	    tos = 0;
	    objIdSize = 0;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+3) {
	    /* a.d.d was specified */
	    extendOID = 8;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 3, &ipAddr);
	    ipMask = 0xff000000;
	    tos = 0;
	    objIdSize = 0;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+2) {
	    /* a.d was specified */
	    extendOID = 9;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 2, &ipAddr);
	    ipMask = 0xff000000;
	    tos = 0;
	    objIdSize = 0;

	}
	else if (poid->oid_nelem == pot->ot_name->oid_nelem+1) {
	    /* a was specified */
	    extendOID = 10;

            dot2binary(&(poid->oid_elements[pot->ot_name->oid_nelem]), 1, &ipAddr);
	    ipMask = 0xff000000;
	    tos = 0;
	    objIdSize = 0;

	}
	else {
	    /* Only object id was specified */
	    extendOID = 11;

	    ipAddr = 1;
	    ipMask = 0xff000000;
	    tos = 0;
	    objIdSize = 0;

	}

	/* Locate the IP route entry or the closest in the routing table */
	if ((pIPDestEntry = locateClosestIPRouteEntry(ipAddr, ipMask)) == 
							(IsisIPDestEntry *)NULL) {
	    return NOTOK;
	}

	if (extendOID) {	/* binding oid needs to be extended */
	    if ((pnewoid = oid_extend(poid, extendOID)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

   	}

	/* New binding */
        binary2dot(pIPDestEntry->isisIPRouteDest,
		   &pvarbind->name->oid_elements[pot->ot_name->oid_nelem]);
        binary2dot(pIPDestEntry->isisIPRouteMask,
		   &pvarbind->name->oid_elements[pot->ot_name->oid_nelem+4]);

    	pvarbind->name->oid_elements[pot->ot_name->oid_nelem+8] = 
		                           	pIPDestEntry->isisIPRouteMetTOS;

	if (objIdSize < 2) objIdSize = 2;
	for (i = 0; i < objIdSize; ++i) {
    	    pvarbind->name->oid_elements[pot->ot_name->oid_nelem+9+i] = 0;
	    
	}

	break;

    default:
	return int_SNMP_error__status_genErr;

    } 


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisIPRouteDest, IpAddress */
	ipAddrTemp.sin_addr.s_addr = pIPDestEntry->isisIPRouteDest;
	return o_ipaddr(poi, pvarbind, &ipAddrTemp); 

    case 2:			/* isisIPRouteMask, IpAddress */
	ipAddrTemp.sin_addr.s_addr = pIPDestEntry->isisIPRouteMask;       
	return o_ipaddr(poi, pvarbind, &ipAddrTemp);

    case 3:			/* isisIPRouteMetTOS, TOS */
	return o_integer(poi, pvarbind, pIPDestEntry->isisIPRouteMetTOS);

    case 4:			/* isisIPRouteMetType, INTEGER */
	return o_integer(poi, pvarbind, pIPDestEntry->isisIPRouteMetType);

    case 5:			/* isisIPRouteIntMetric, PathCost */
	return o_integer(poi, pvarbind, pIPDestEntry->isisIPRouteIntMetric);

    case 6:			/* isisIPRouteExtMetric, INTEGER */
	return o_integer(poi, pvarbind, pIPDestEntry->isisIPRouteExtMetric);

    case 7:			/* isisIPRouteForw, OBJECT IDENTIFIER */
 	return o_specific(poi, pvarbind, text2oid("0.0"));

    case 8:			/* isisIPRouteSource, INTEGER */
	return o_integer(poi, pvarbind, pIPDestEntry->isisIPRouteSource);

    case 9:			/* isisIPRouteSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pIPDestEntry->isisIPRouteSysInstance);

    default:
	return int_SNMP_error__status_noSuchName;

    } 


} /* end of get_isisIPDestTable() */




/*
**	Process a request referencing a variable in the Test Group,
**	the Level 1 LSP Database Table
*/

static int get_isisTestL1LSPDbaseTable(ObjectInstance * poi,
			               struct type_SNMP_VarBind * pvarbind,
 			               int request	     		    )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    int		instance=0;		
    LSEntry	*pLSEntry;
    int		i, found;

    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem != pot->ot_name->oid_nelem+1) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[poid->oid_nelem-1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem == pot->ot_name->oid_nelem) {      
	    ObjectID pnewoid;		

	    if ((pnewoid = oid_extend(poid, 1)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

	    instance = 0;
     	}
	else {	       
            instance = poid->oid_elements[pot->ot_name->oid_nelem];
	}
	instance += 1;
  	    
	break;

    default:
	return int_SNMP_error__status_genErr;

    } 

    /* Locate the desired instance */
    for (i = 1, found = FALSE, pLSEntry = (LSEntry *) firstLSP(1); pLSEntry; ++i) {
	if (i == instance) {
	    found = TRUE;		/* the desired instance */
	    break;
	}
	
	pLSEntry = pLSEntry->sortNext;
    }

    if (found) {
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = instance;
    }
    else {
	if (request == type_SMUX_PDUs_get__request)
	    return int_SNMP_error__status_noSuchName;
	else return NOTOK;

    }


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:				/* isisL1LSPIndex, INTEGER */
	return o_integer(poi, pvarbind, instance);

    case 2:				/* isisL1LSPLinkForw, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->links.forw);

    case 3:				/* isisL1LSPLinkBack, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->links.back);

    case 4:				/* isisL1LSPSigIdSourceId, OCTET STRING */
	return o_string(poi, pvarbind, pLSEntry->signature.id.sourceID, 6);

    case 5:				/* isisL1LSPSigIdPseudonodeID, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.id.pseudonodeID);

    case 6:				/* isisL1LSPSigIdLSPNum, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.id.LSPNumber);

    case 7:				/* isisL1LSPSigSeqNum, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.seqNum);

    case 8:				/* isisL1LSPSigLifeTime, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.lifetime);

    case 9:				/* isisL1LSPSigLevel, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.level);

    case 10:				/* isisL1LSPSigChecksum, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.checksum);

    case 11:				/* isisL1LSPOrigLifeTime, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->originalLifetime);

    case 12:				/* isisL1LSPRemainTime, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->remainingTime);

    case 13:				/* isisL1LSPArrivalTimestamp, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->arrivalTimestamp);

    case 14:				/* isisL1LSPSRM, OCTET STRING */
	return o_string(poi, pvarbind, pLSEntry->SRM, 10);

    case 15:				/* isisL1LSPSSN, OCTET STRING */
	return o_string(poi, pvarbind, pLSEntry->SSN, 10);

    case 16:				/* isisL1LSPFoundInSNP, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->foundInSNP);

    case 17:				/* isisL1LSPOnDeletedList, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->onDeletedList);

    case 18:				/* isisL1LSPBuf, INTEGER */ 
	return o_string(poi, pvarbind, pLSEntry->buf, pLSEntry->len);

    case 19:				/* isisL1LSPLen, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->len);

    case 20:				/* isisL1LSPDesc, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->lspDesc);

    case 21:				/* isisL1LSPHashNext, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->hashNext);

    case 22:				/* isisL1LSPSortNext, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->sortNext);

    default:
	return int_SNMP_error__status_noSuchName;

    } 






} /* end of get_isisTestL1LSPDbaseTable() */



static void set_isisTestL1LSPDbaseTable(ObjectInstance * poi,
			               struct type_SNMP_VarBind * pvarbind,
 			               int request	     		    )
{




} /* end of set_isisTestL1LSPDbaseTable() */



/*
**	Process a request referencing a variable in the Test Group,
**	the Level 2 LSP Database Table
*/

static int get_isisTestL2LSPDbaseTable(ObjectInstance * poi,
			               struct type_SNMP_VarBind * pvarbind,
 			               int request	     		    )
{
    ObjectID	poid = poi->oi_name;
    ObjectType	*pot = poi->oi_type;
    int		column;			
    int		instance=0;		
    LSEntry	*pLSEntry;
    int		i, found;

    switch (request) {
    case type_SMUX_PDUs_get__request:	return int_SNMP_error__status_noSuchName;

	if (poid->oid_nelem != pot->ot_name->oid_nelem+1) 
	    return int_SNMP_error__status_noSuchName;

	if ((instance = poid->oid_elements[poid->oid_nelem-1]) == 0) 
	    return int_SNMP_error__status_noSuchName;

    	break;

    case type_SMUX_PDUs_get__next__request:	return NOTOK;

	if (poid->oid_nelem == pot->ot_name->oid_nelem) {      
	    ObjectID pnewoid;		

	    if ((pnewoid = oid_extend(poid, 1)) == NULLOID) 
		return int_SNMP_error__status_genErr;

	    if (pvarbind->name) free_SMI_ObjectName(pvarbind->name);
	    pvarbind->name = pnewoid;

	    instance = 0;
     	}
	else {	       
            instance = poid->oid_elements[pot->ot_name->oid_nelem];
	}
	instance += 1;
  	    
	break;

    default:
	return int_SNMP_error__status_genErr;

    } 

    /* Locate the desired instance */
    for (i = 1, found = FALSE, pLSEntry = (LSEntry *) firstLSP(2); pLSEntry; ++i) {
	if (i == instance) {
	    found = TRUE;		/* the desired instance */
	    break;
	}
	
	pLSEntry = pLSEntry->sortNext;
    }

    if (found) {
	pvarbind->name->oid_elements[pot->ot_name->oid_nelem] = instance;
    }
    else {
	if (request == type_SMUX_PDUs_get__request)
	    return int_SNMP_error__status_noSuchName;
	else return NOTOK;

    }


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:				/* isisL2LSPIndex, INTEGER */
	return o_integer(poi, pvarbind, instance);

    case 2:				/* isisL2LSPLinkForw, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->links.forw);

    case 3:				/* isisL2LSPLinkBack, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->links.back);

    case 4:				/* isisL2LSPSigIdSourceId, OCTET STRING */
	return o_string(poi, pvarbind, pLSEntry->signature.id.sourceID, 6);

    case 5:				/* isisL2LSPSigIdPseudonodeID, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.id.pseudonodeID);

    case 6:				/* isisL2LSPSigIdLSPNum, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.id.LSPNumber);

    case 7:				/* isisL2LSPSigSeqNum, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.seqNum);

    case 8:				/* isisL2LSPSigLifeTime, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.lifetime);

    case 9:				/* isisL2LSPSigLevel, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.level);

    case 10:				/* isisL2LSPSigChecksum, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->signature.checksum);

    case 11:				/* isisL2LSPOrigLifeTime, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->originalLifetime);

    case 12:				/* isisL2LSPRemainTime, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->remainingTime);

    case 13:				/* isisL2LSPArrivalTimestamp, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->arrivalTimestamp);

    case 14:				/* isisL2LSPSRM, OCTET STRING */
	return o_string(poi, pvarbind, pLSEntry->SRM, 10);

    case 15:				/* isisL2LSPSSN, OCTET STRING */
	return o_string(poi, pvarbind, pLSEntry->SSN, 10);

    case 16:				/* isisL2LSPFoundInSNP, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->foundInSNP);

    case 17:				/* isisL2LSPOnDeletedList, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->onDeletedList);

    case 18:				/* isisL2LSPBuf, INTEGER */ 
	return o_string(poi, pvarbind, pLSEntry->buf, pLSEntry->len);

    case 19:				/* isisL2LSPLen, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->len);

    case 20:				/* isisL2LSPDesc, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->lspDesc);

    case 21:				/* isisL2LSPHashNext, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->hashNext);

    case 22:				/* isisL2LSPSortNext, INTEGER */
	return o_integer(poi, pvarbind, pLSEntry->sortNext);

    default:
	return int_SNMP_error__status_noSuchName;

    } 





} /* end of get_isisTestL2LSPDbaseTable() */



static void set_isisTestL2LSPDbaseTable(ObjectInstance * poi,
			               struct type_SNMP_VarBind * pvarbind,
 			               int request	     		    )
{




} /* end of set_isisTestL2LSPDbaseTable() */







/*
**	For the objects not supported, yet.
*/
int locateinstance(instance) 
int		instance;
{


    return(instance);


} /* end of locateinstance() */



int locatenextinstance(instance) 
int		instance;
{

    if (instance > 8) return(0);	/* limit the breadth for dummys */
    return(instance+1);


} /* end of locatenextinstance() */



#endif	/* defined(PROTO_SNMP) */

/* end of isis_mib.c */




#ifdef	THIS_PIECE_IS_NEEDED

    /* Use the L1 LSP database directly */
    {
    
    LSEntry		*pLSEntry;		/* ptr to L1 LSP db */
    AreaAddrList 	aggregatedList;
    AreaAddr		*pAreaAddr;

    for (pLSEntry = firstLSP(1); pLSEntry; pLSEntry = pLSEntry->sortNext) {
	if (pLSEntry->signature.id.LSPNumber != 0) { /* not locally gen'ed */
	    aggregatedList = mergeAreaAddrList(parseLSPAreaAddrList(pLSEntry->buf,
								    pLSEntry->len ),
					       aggregatedList                       );

 	}
    }

    if (addrIndex > aggregatedList.count) {
	/* Not that many area addresses */
	if (request == type_SMUX_PDUs_get__request) 	    
	    return int_SNMP_error__status_noSuchName;
	else return NOTOK;
    }    

    pAreaAddr = retrieveAreaAddr(aggregatedList.areaAddr[addrIndex-1]);


    column = pot->ot_name->oid_elements[pot->ot_name->oid_nelem-1];

    switch (column) {
    case 1:			/* isisAreaAddrSysInstance, INTEGER */
	return o_integer(poi, pvarbind, pAreaAddrEntry->isisAreaAddrSysInstance);

    case 2: 			/* isisAreaAddr, OSINSAddress */
 	return o_string(poi, pvarbind, pAreaAddr->addr, pAreaAddr->len);

/* 	return o_string(poi, pvarbind, pAreaAddrEntry->isisAreaAddr.contents,
				       pAreaAddrEntry->isisAreaAddr.len      );
*/

    default:
	return int_SNMP_error__status_noSuchName;

    } 

    } /* end of using L1 LSP database directly */


#endif
