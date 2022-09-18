/*
 *  isis_spf.h,v 1.11 1993/01/07 22:39:59 jch Exp
 */

/* %(Copyright.header) */

#ifndef	_isis_spf_h
#define	_isis_spf_h

#define SYSID_SIZE 	6
#define NUM_METRICS 	4	/* number of supported metrics */
#define IS_NID_SIZE 	7	/* octets in an IS Neighbor id */
#define ES_NID_SIZE 	6	/* octets in an ES Neighbor id */
#define MAX_PREF_SIZE 	20 	/* max size in bytes of address prefix */
#define INET_ADDR_SIZE 	4 	/* size of internet address */

typedef unsigned char octet;
typedef octet SYSID[SYSID_SIZE];

struct is_neighbor {
	octet metrics[4];
	octet is_neighbor_id[IS_NID_SIZE];
};
typedef struct is_neighbor IS_NEIGHBOR;

#define IS_NEIGHBOR_SELECTOR 2 				/* selector code for is_neighbor field in lsp */
#define MAX_IS_NEIGHBORS (254/sizeof(IS_NEIGHBOR))	/* max IS neighbor fields in lsp code 2 field (see spec section 9.8) */
struct is_neighbor_field {
	octet code; 		/* 2 */
	octet length;		/* 1 + multiple of sizeof(IS_NEIGHBOR) */
	octet virtual_flag; 	/* virtual flag for level 1, reserved in level 2 */
	IS_NEIGHBOR is_neighbors[MAX_IS_NEIGHBORS];
};

struct inet_neighbor {
	octet metrics[4];
	octet inet_addr[4];
	octet inet_mask[4];
};

typedef struct inet_neighbor INET_NEIGHBOR;

#define MAX_INET_NEIGHBORS ((256-2)/sizeof(struct inet_neighbor))
#define IN_INTERN_SELECTOR	128
#define IN_EXTERN_SELECTOR 	130 

struct inet_neighbor_field {
	octet code; 		/* 128 */
	octet length; 		/* # of fields * sizeof(INET_NEIGHBOR)  */
	INET_NEIGHBOR inet_neighbors[MAX_INET_NEIGHBORS];
};

#define ES_NEIGHBOR_SELECTOR 3
#define MAX_ES_NEIGHBORS  ((255-4)/ES_NID_SIZE)
struct es_neighbor_field {
	octet code; 		/* 3 */
	octet length;
	octet metrics[4];
	octet es_neighbors[MAX_ES_NEIGHBORS][ES_NID_SIZE];
};

#define PREFIX_NEIGHBOR_SELECTOR 5
struct prefix_neighbor_field {
	octet code; 		/* 5 */
	octet length;
	octet metrics[4];
	octet space[250];
};

#define AREA_ADDR_SELECTOR 1
struct area_addr_field {
	octet code; 		/* 1 */
	octet length;
	octet space[254];
};

struct is_lsp_header {
	octet disc;
	octet len;
	octet h_version;
	octet idLen;
	octet type;
	octet h_version2;
	octet reserved;
	octet maxAreaAddrs;
	octet pdu_len[2]; 
	octet remaining_life[2];
	octet lsp_id[8];
	octet sequence_number[4];
	octet checksum[2];
	octet flags;
};

/* byte order macro; shorts handled as array of 2 octets */
/* temporary cheat: cast pointers only */
/* cheat doesn't work due to alignment */
#ifdef bigend
#define GETNSHORT(cpt) ( *(unsigned short *)(cpt))
#define SETNSHORT(cpt,val) (GETNSHORT(cpt) = (val))
#else
#define GETNSHORT(cpt) (((cpt)[0]<<8)+ (cpt)[1])
#define SETNSHORT(cpt,val) (((cpt)[0]=((val)>>8)&0xff),((cpt)[1]=(val)&0xff))
#define GETNLONG(cpt) (((cpt)[0]<<24)+ ((cpt)[1]<<16) +((cpt[2])<<8 + cpt[0]))
#endif

/* program constants + more data structures */
#define MAX_COST 1024 			/* per spec */
#define SPF_HASHTAB_SIZE 4093 		/* should be prime, probably isn't */

typedef struct {
	octet addr[IS_NID_SIZE];
} IS_ID;

typedef struct {
	octet addr[ES_NID_SIZE];
} ES_ID;

typedef struct {
	octet area_len;
	octet addr[MaximumAreaAddressLen];
} AREA_ADDR;

typedef struct {
	octet pref_len;
	octet addr[MAX_PREF_SIZE];
} ADDR_PREF;

typedef struct {
	octet addr[INET_ADDR_SIZE];
	octet mask[INET_ADDR_SIZE];
} INET_NET;

typedef struct {
	struct in_addr addr, mask;
} INET_N2;

/* lsp addrs toss in an extra byte for the packet number, odd. */
typedef struct {
	IS_ID is_addr;
	octet packet_num;
} LSP_ID;

enum addr_types {is_id, es_id, area_addr, addr_pref, inet_net} ;
struct route_addr {
	enum addr_types addr_t;
	union {
		IS_ID is_addr;
		ES_ID es_addr; 	
		AREA_ADDR area_addr;
		ADDR_PREF addr_prefix;
		INET_NET inet_net;
		INET_N2 in2;
	} au;
#define INaddr au.in2.addr
#define INmask au.in2.mask
};

struct isis_spf_aa {
	AREA_ADDR areas[MaximumAreaAddresses];	/* for an IS, the list of its areas */
	int numAAs;				/* and how many it's in */
};

typedef union _GPT {
	/* values for gtype below */
#define	INTERIOR 1	
#define	ISOLEAF	 2
#define IPLEAF   3
	/* generic (common stuff) */
	struct graph_node {
		byte gtype;
		short internal_cost;		/* internal cost from home */
		short extern_cost; 		/* external metric */
		union _GPT *hash_chain; 	/* a hash is used to find node based on dest */
		union _GPT *parent; 		/* upstream neighbor for this destination (the node from which we took the route) */
		union _GPT *pend_q; 		/* queue pointer for pending queues */
		u_long generation;		/* generation number (curr_generation applies to current spf run) */
		rt_entry *gated_route;		/* pointer to route in gated's tables (if any) */
	} g;
	/* interior node */
	struct interior_node {
		byte gtype;
		short internal_cost;		/* internal cost from home */
		short extern_cost; 		/* external metric (always == 0) */
		union _GPT *hash_chain; 	/* a hash is used to find node based on dest */
		union _GPT *parent; 		/* upstream neighbor for this destination (the node from which we took the route) */
		union _GPT *pend_q; 		/* queue pointer for pending queues */
		u_long generation;		/* generation number (curr_generation applies to current spf run) */
		rt_entry *gated_route;		/* pointer to route in gated's tables (if any) */
		struct route_addr Addr;		/* the destination */
		AdjacencyEntry *adj; 		/* adjacency corresponding to route to this destination */
		AdjacencyEntry *oldadj; 	/* adjacency from previous spf run */
		struct isis_spf_aa aa;		/* area addresses to which this IS belongs */
	} interior;
	struct iso_leaf {
		byte gtype;
		short internal_cost;		/* internal cost from home */
		short extern_cost; 		/* external metric */
		union _GPT *hash_chain; 	/* a hash is used to find node based on dest */
		union _GPT *parent; 		/* upstream neighbor for this destination (the node from which we took the route) */
		union _GPT *pend_q; 		/* queue pointer for pending queues */
		u_long generation;		/* generation number (curr_generation applies to current spf run) */
		rt_entry *gated_route;		/* pointer to route in gated's tables (if any) */
		as_path *asp;			/* AS path for new generation */
		union _GPT *oldparent;		/* parent from previous spf run */
		struct route_addr Addr;		/* the destination */
	} isoleaf;
	struct ip_leaf {
		byte gtype;
		short internal_cost;		/* internal cost from home */
		short extern_cost; 		/* external metric */
		union _GPT *hash_chain; 	/* a hash is used to find node based on dest */
		union _GPT *parent; 		/* upstream neighbor for this destination (the node from which we took the route) */
		union _GPT *pend_q; 		/* queue pointer for pending queues */
		u_long generation;		/* generation number (curr_generation applies to current spf run) */
		rt_entry *gated_route;		/* pointer to route in gated's tables (if any) */
		as_path *asp;			/* AS path for new generation */
		union _GPT *oldparent;		/* parent from previous spf run */
		INET_NET Addr;			/* the destination */
		prefIP *p;			/* where to find the unsummarized IP prefixes */
	} ipleaf;
} *GRAPH_PT;

struct sumlist {
	struct sumlist *next;
	union _GPT *node;
};


/* 
 * Various iterator state structures.  The following structure is used 
 * to iterate through the lsps associated with a particular node, 
 * looking for a particular type of field.  Once we arrive at that
 * field, we search through it using a more specialized iterator
 * structure.
 */
struct lsp_iter_state {
	octet selector;		/* the code for the field we are scanning for */
	LSP_ID lsp_id;
	int packet_number;	/* packet number for this lsp */
	octet *cur_lsp;
	int cur_lsp_len;	/* length of the current lsp */
	octet *cur_lsp_loc; 	/* location we are at in the current lsp */
	LSEntry *cur_lsentry;
};


/* 
 * The more specialized iterator structure referred to above.
 */
struct isn_iter_sstate {
	int num_isn;
	int cur_isn;
};
struct inn_iter_sstate {
	int num_inn;
	int cur_inn;
};
struct esn_iter_sstate {
	int num_esn;
	int cur_esn;
};
struct prefix_iter_sstate {
	octet *next_prefix;
	octet metrics[NUM_METRICS];
};
struct area_iter_sstate {
	octet *next_area;
};
struct subfield_iter_state {
	struct lsp_iter_state lsp_iter;
	enum addr_types addr_type;
	octet *metrics;
	isis_asp attributes;
	union {
		char *cur_field; 				/* generic case */
		struct is_neighbor_field *cur_isn_field;
		struct inet_neighbor_field *cur_inn_field; 
		struct es_neighbor_field *cur_esn_field;
		struct area_addr_field *cur_area_field;
		struct prefix_neighbor_field *cur_prefix_field;
	} cfu;
	union {
		struct isn_iter_sstate isf;
		struct inn_iter_sstate inf;
		struct esn_iter_sstate esf;
		struct area_iter_sstate arf;
		struct prefix_iter_sstate pff;
	} iu;
};

/*
 * Input log binary header.
 */
struct log_header { 
	int io_time; 		/* time of the input/output */
	int io_count; 		/* sequence number of this io */
	int io_len;   		/* length of this log record, not including header */
	MACAddress io_src;	/* where the packet came from */
	char io_id;		/* local circuit id */
};

/* 
 * Structure used to save ip reachable addresses.
 */
extern int isis_ipri; 		/* number of ip reachable addrsp parsed */
#define MAX_IS_IPRS 20
struct isis_ipr {
	int level;
	int type;
	int autoSum;
	struct in_addr addr;
	struct in_addr mask;
	MetricList metric;
	Boolean inUse;
	prefIP *p;
	struct isis_ipr *next;
};
struct isis_pref {
	ADDR_PREF pref_addr;
	MetricList oldMetric;		/* what it was before changed */
	MetricList metric;		/* what it is if new or after change */
	int changed;			/* true if metric has changed during reconfig */
	int new;			/* true if this is a newly configured prefix (and changed == false) */
	struct isis_pref *next;
};
extern struct isis_ipr isis_iprs[MAX_IS_IPRS];
extern struct isis_ipr *IPRList;

#endif	/* _isis_spf_h */


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
