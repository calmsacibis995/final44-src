/*
 *  isis_pdus.h,v 1.11 1993/01/07 22:39:50 jch Exp
 */

/* %(Copyright.header) */


#ifndef _pdus_h
#define _pdus_h

#include "isis_base.h"

#define	Unsupported	0x80
#define Reserved	0x40
#define	ValueMask	0x3f

#define	ISL1		0x01
#define	ISL2		0x03
#define	Hippty		0x04
#define AttachedDefault	0x08
#define AttachedDelay	0x10
#define AttachedExpense	0x20
#define AttachedError	0x40
#define	PartitionRepair	0x80

/* Variable length field ID codes */
#define	AreaAddressCode			1			/* IIH and LSP */
#define LSPISNeighborCode		2			/* LSP */
#define LSPESNeighborCode		3			/* LSP */
#define	LSPPDL2ISCode			4			/* LSP */
#define LSPPrefixNeighborCode		5			/* LSP */
#define	ISNeighborCode			6			/* IIH */
#define PaddingCode			8			/* lan IIH */
#define LSPEntries			9			/* CSNP and PSNP */
#define AuthenticationCode		10			/* ISO IIH, LSP, CSNP, PSNP */
#define	IPIntReachCode			128			/* DUAL */
#define ProtoSupportedCode		129			/* DUAL */
#define	IPExtReachCode			130			/* DUAL */
#define IPInterDomInfo                  131                     /* DUAL */
#define IPIfAddrCode			132			/* DUAL */
#define IPAuthInfoCode			133			/* DUAL - different auth code allows disjoint domain for IP */
#define	leafNode			180			/* LSP - indicates whether IS Neighbor option present in this LSP */
#define	IPSumReachCode			254			/* DUAL - fake value for internal use only */

/* return true if there is space left in the option field */
#define optSpaceLeft(curLen, itemSize)\
	((255 - curLen) > itemSize)

typedef struct {
	Metric	defalt;		/* default is reserved in C */
	Metric	delay;
	Metric	expense;
	Metric	error;
} MetricList;

typedef struct _LSPID {
	SystemID6	sourceID;
	Unsigned8	pseudonodeID;
	Unsigned8	LSPNumber;
} LSPID;


typedef struct _CommonHeader {
	Unsigned8	_packetID;
	Unsigned8	_headerLength;
	Unsigned8	_versionProtoID;
	Unsigned8	_reserved1;
#define	GetPacketType(x) ((x) & ~0xe0)
#define ESHType			2
#define ISHType			4
#define RDType			6
#define	L1LANHelloType		15
#define	L2LANHelloType		16
#define PPHelloType		17
#define L1LSType		18
#define L2LSType		20
#define L1CSNType		24
#define L2CSNType		25
#define L1PSNType		26
#define L2PSNType		27
	Unsigned8	_packetType;
	Unsigned8	_version;
	Unsigned8	_eco;
	Unsigned8	_userEco;
} CommonHeader;

#define packetID common._packetID
#define headerLength common._headerLength
#define versionProtoID common._versionProtoID
#define packetType common._packetType
#define myversion common._version
#define eco common._eco
#define userEco common._userEco

typedef struct _ESISHeader {
	Unsigned8	protoID;		/* network layer protocol identifier */
	Unsigned8	headerLen;		/* length indicator (octets) */
	Unsigned8	vers;			/* version/protocol identifier extension */
	Unsigned8	res1;			/* reserved */
	Unsigned8	type;			/* type code */
	Unsigned16	ht;			/* holding time (seconds) */
	Unsigned16	cksum;			/* checksum */
} ESISHeader;

typedef struct _LSPHeader {
	CommonHeader	common;
	Unsigned16	pduLength;
	Unsigned16	remainingLifetime;
	LSPID		lspId;				/* ID of LSP originator */
	Unsigned32	sequenceNumber;
	Unsigned16	checksum;
	Unsigned8	pathhippity;
} LSPHeader;

typedef struct _LANHelloHeader {
	CommonHeader	common;
#define	GetCircuitType(x) ((x) & ~0xfc)
#define L1Circuit	0x01
#define L2Circuit	0x02
	Unsigned8	circuitType;
	SystemID6	sourceID;
	Unsigned16	holdingTimer;
	Unsigned16	pduLength;
#define	GetPriority(x) ((x) & ~0x80)
	Unsigned8	priority;
	SystemID7	LANID;
} LANHelloHeader;

typedef struct _PPHelloHeader {
	CommonHeader	common;
	Unsigned8	circuitType;
	SystemID6	sourceID;
	Unsigned16	holdingTimer;
	Unsigned16	pduLength;
	Unsigned8	localCircuitID;
} PPHelloHeader;

typedef struct _CSNHeader {
	CommonHeader	common;
	Unsigned16	pduLength;
	SystemID7	sourceID;
	LSPID		start;
	LSPID		end;
} CSNHeader;

typedef struct _PSNHeader {
	CommonHeader	common;
	Unsigned16	pduLength;
	SystemID7	sourceID;
} PSNHeader;

typedef struct _AreaAddr {
	u_char		len;
	u_char		addr[MaximumAreaAddressLen];
} AreaAddr;

typedef struct _AreaAddrList {
	char		areaAddr[MaximumAreaAddresses];	/* index into AA store */
	u_char		count;				/* current number */
} AreaAddrList;

#define MAXIPADDRS		10

typedef struct _IPAddrList {
	struct in_addr	addrs[MAXIPADDRS];
	u_short		cnt;
} IPAddrList;

typedef struct _IPReachAddr {
	MetricList	metrics;
	IPAddress	address;
	IPSubnetMask	mask;
} IPReachAddr;

typedef struct _IPReachInfo {
	IPReachAddr		*reachAddrs;	/* array */
	u_short			count;		/* size of array */
	struct _IPReachInfo	*next;
} IPReachInfo;

/* flags field */
#define	SUPPORT_IP	0x01
#define SUPPORT_CLNP	0x02

typedef struct _LANHelloPacket {
	u_int		flags;			/* DUAL: protocols supported */
	IPAddrList	ifAddr;			/* DUAL: addr of if xmitted upon */
	AuthInfo	authInfo;		/* DUAL: TODO */
	LANHelloHeader	*hdr;
	u_short		holdingTimer;		/* host order */
	u_short		pduLength;		/* host order */
	AreaAddrList	areaAddrs;		/* area addresses */
	SystemID6	*ISneighbors;		/* array of SystemIDs */
	u_short		count;			/* number in array */
} LANHelloPacket;

typedef struct _PPHelloPacket {
	caddr_t		data;			/* actual packet */
	u_short		len;			/* length of packet */
	u_int		flags;			/* DUAL: protocols supported */
	IPAddrList	ifAddr;			/* DUAL: addr of if xmitted upon */
	AuthInfo	authInfo;		/* DUAL: TODO */
	u_short		holdingTimer;		/* host order */
	u_short		pduLength;		/* host order */
	PPHelloHeader	*hdr;
	AreaAddrList	areaAddrs;		/* area addresses */
} PPHelloPacket;

typedef struct _AddrPrefix {
	MetricList	*metrics;
	AreaAddrList	addrPrefixes;
} AddrPrefix;

typedef struct _PrefixList {
	AddrPrefix		prefix;
	struct _PrefixList	*next;
} PrefixList;

typedef struct _SNEntry {
	u_short		lifetime;		/* remaining */
	LSPID		id;
	u_long		number;
	u_short		checksum;
} SNEntry;


#endif	/* _pdus_h */


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
