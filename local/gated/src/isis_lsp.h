/*
 *  isis_lsp.h,v 1.11 1993/01/07 22:39:33 jch Exp
 */

/* %(Copyright.header) */


#include "isis_dll.h"

struct _LSPDesc;

#include "isis_flood.h"

/*
 *	
 *	The following structures are used to represent a system's own LSP.
 *
 *	The idea to this whole mess is to keep adjacencies from migrating
 *	from one LSP to another. The scheme is that LSP 0 is special and
 *	only contains one or two options. Other options (ES neighbors
 *	IS neighbors, etc) are placed in their own individual LSPs.
 *
 *	Each LSP to be generated is described by the LSPDesc structure. This
 *	represents a single LSP with a list of options. The 'order' parameter
 *	is used to constrain the order in which the LSPDesc structs are mapped
 *	to LSP numbers: a lower value in the 'order' field indicates that the
 *	LSPDesc should be sent as a lower numbered LSP number. (This field
 *	is used to keep the IS options before the ES options and the
 *	IS options before the Prefix neighbor options. The use of this field
 *	implies that ES options/IS options/Prefix neighbor options are
 *	not placed in the same individual LSP.
 */

#define MaxOptLen		256

typedef enum {LSPzero, LSPlow, LSPhigh} LSPOrder;

/* 
 * These are new structures to deal with large numbers of prefixes.  We
 * use these to optimize prefix additions, deletions, and changes rather 
 * than LSP construction.  Eventually, similar prefixes (e.g., aspath,
 * rdpath, nexthop) will be lumped together in the same LSP in order
 * to reduce the amount of flooding necessary during "steady-state" 
 * operation.  Note that these structures are not identical to the PDU
 * formats.
 *
 * In the future, the as_path structure will be able to hold TSI which
 * I'll use to index the first LSPDesc containing that info.  Each LSPDesc
 * may contain 0 or more as_paths.  Each prefix LSPOption will contain
 * exactly 1 as_path.  Each LSPPrefixNeighborCode LSPOption will contain
 * exactly 1 (as_path, MetricList) tuple.  This makes it possible that
 * two different LSPDesc's will list the same as_path among their attributes,
 * with the MetricList being different among the options in each.  This
 * can also occur as a result of an LSPOption filling up, in turn filling
 * and LSPDesc, thereby bumping an LSPOption with a similar as_path - or 
 * even (as_path, MetricList) tuple - into another LSPDesc.  As for the 
 * difficulty related to prefix movement caused by metric changes, I expect
 * in the common case for the metric to be policy-based (slowly changing)
 * rather than eGP-derived (changing at the whim of external domains).  
 * This complexity exists only for ISO prefixes, because the metric is 
 * carried with the entire option rather than with each prefix.
 */

/* 
 * This guy keeps track of the path attributes referenced in a 
 * given LSPDesc's options. 
 */
typedef struct _LSPattr {
	as_path	*path;			/* path attributes */
	int refcount;			/* number of prefixes in a given option with these attributes */
	struct _LSPOption *idrpiOpt;	/* the IDRPi option for this set of attributes */
} LSPattr;

/* 
 * A single LSPDesc can have many LSPOptions (though we try to optimize
 * in the prefix case - see above).
 */
typedef struct _LSPOption {
	DLList		links;			/* must be first */
	struct _LSPDesc	*lspDesc;		/* ptr to parent LSPDesc */
	LSPOrder	key;			/* sort criteria for insertion with parent */
	LSPattr		*attr;			/* back pointer to the path attributes */
	int		refcount;		/* number of prefix options referring to this option (used by IDRPi option) */
	int		type;			/* type of option */
	int		len;			/* bytes of 'data' used so far */
	u_char 		*data;			/* pointer to the data */
} LSPOption;
#define LSPOptionSize(opt) 	 (opt->len+2)
#define LSPOptionUnused(opt) 	 (255-(LSPOptionSize(opt)))
#define	LSPOptionUnusedData(opt) (opt->data + opt->len)

typedef struct _prefIP {
	struct _prefIP	*prev, *next;
	LSPOption	*opt;		/* back pointer to the option */
	MetricList	metrics;			
	u_long		addr;
	u_long		mask;
} prefIP;

typedef struct _prefISO {
	struct _prefISO	*prev, *next;
	LSPOption	*opt;		/* back pointer to the option */
	MetricList	metrics;		
	int		len;		/* prefix length, in semi-octets */
	byte		addr[20];
} prefISO;

typedef struct _isis_asp {
	byte	code;		/* == 1, local format */
	u_long	version;	/* == 1 */
	u_long	data;		/* encoded path attributes */
} isis_asp;

/*
 *	This structure is used to identify a location in a LSPOption.
 */
typedef struct _LSPOptPtr {
	LSPOption	*opt;	/* ptr to option */
	u_char		off;	/* offset within option to start of entry data */
} LSPOptPtr;

/*
 *	a collection of individual LSPs together represent one "logical" LSP
 *	the LSPDesc structures are kept in order of increasing LSP number.
 */
typedef struct _LSPgroup {
	DLList		list;		/* list of individual LSPs */
	u_char		type;			/* type of LSP */
} LSPGroup;

/*
 *	Identifies an individual LSP
 */
typedef struct _LSPDesc {
	DLList		links;			/* must be first */
	u_char		lspNumber;
	u_char		lspPseudoID;		/* pseudonode ID */
	u_char		lspType;		/* type of LSP (L1 vs. L2) */
	u_short		lspInitLifetime;	/* initial value of the lifetime field */
	long		seqNumber;
	DLList		options;
	DLList		paths;			/* path attributes for prefixes in this LSPDesc's options */
	Boolean		schedRegenerate;	/* true if the LSP is scheduled to be regenerated (via timer) */
	Boolean		mustRegenerate;		/* true if the LSP must be regenerated (because it has changed) */
	time_t		lastGenerated;		/* used for generation throttle */
	short		spaceLeft;		/* remaining space in LSPDesc */
	u_char		*pktBuf;		/* buffer to build actual LSP in */
	u_short		pktSize;		/* size of pktBuf */
	LSEntry		*lspEntry;		/* place holder in LSP database */
	LSPGroup	*group;			/* back pointer to group */
        int		timer;			/* index of timer set for this LSP */
} LSPDesc;


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
