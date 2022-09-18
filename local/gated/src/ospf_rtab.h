/*
 * $Id: ospf_rtab.h,v 1.17.2.3 1994/10/18 03:14:07 jch Exp $
 */

/* %(Copyright.header) */


#ifndef RTAB_H
#define RTAB_H

/*
 * For accessing router route information
 */

#define RRT_INFO(R)	(R)->ospf_rt_info
#define RRT_DEST(R) 	(R)->dest
#define RRT_MASK(R) 	(R)->mask
#define RRT_DTYPE(R) 	RRT_INFO(R).dtype
#define RRT_ETYPE(R) 	RRT_INFO(R).etype
#define RRT_CHANGE(R) 	RRT_INFO(R).change
#define RRT_PTYPE(R) 	RRT_INFO(R).ptype
#define RRT_REV(R) 	RRT_INFO(R).revision
#define RRT_AREA(R) 	RRT_INFO(R).area
#define RRT_COST(R)	RRT_INFO(R).cost
#define RRT_NH_ADDR(R) 	RRT_INFO(R).nh_ndx[0]->nh_addr
#define RRT_NH_IFAP(R) 	RRT_INFO(R).nh_ndx[0]->nh_ifap
#define	RRT_NH_CNT(R)	RRT_INFO(R).nh_cnt
#define	RRT_NH(R)	RRT_INFO(R).nh_ndx
#define RRT_ADVRTR(R) 	RRT_INFO(R).advrtr
#define RRT_V(R) 	RRT_INFO(R).v
#define RRT_NEXT(R) 	(R)->ptr[NEXT]
#define RRT_LAST(R) 	(R)->ptr[LAST]


typedef struct ospf_rt_info {
    struct NH_BLOCK *nh_ndx[RT_N_MULTIPATH];	/* Better all around if an odd number like 3 */
    u_int8 nh_cnt;
    u_int8 etype;		/* external metric type */
    u_int8 dtype;		/* destination type */
    u_int8 change;		/* this entry has been changed flag */
    u_int8 ptype;		/* LS_RTR and LS_NET are internal, LS_SUM
			           are inter area and LS_ASE are external */
    struct LSDB *v;		/* vertex */
    struct AREA *area;		/* associatiated area */
    u_int32 cost;
    u_int32 advrtr;
    u_int32 revision;
} OSPF_RT_INFO;


#define ORT_INFO_NULL 	((OSPF_RT_INFO *) 0)

/*
 * Type router entries - Area border, AS border and AS border summary
 */
struct OSPF_ROUTE {
    struct OSPF_ROUTE *ptr[2];
    u_int32 dest;
    u_int32 mask;
    OSPF_RT_INFO ospf_rt_info;
};

/*
 * Cache for forwarding address
 */
#define FORWARD_CACHE_SIZE 5


/*
 * OSPF next-hop list
 */
#define NH_DIRECT		1
#define NH_NBR			2
#define	NH_LOCAL		3
#define	NH_DIRECT_FORWARD	4

/* May want to include link address here... */
struct NH_BLOCK {
    struct NH_BLOCK *nh_forw;
    struct NH_BLOCK *nh_back;
    u_short	nh_type;	/* type of next hop */
    u_short	nh_refcount;	/* Number of references */
    if_addr *nh_ifap;		/* pointer to interface */
#define	NH_NET(nhp)	sock2ip((nhp)->nh_ifap->ifa_net)
    u_int32 nh_addr;		/* next hop ip address */
};

#define	NH_LIST(np) \
	do { \
	    register struct NH_BLOCK *Xnp = ospf.nh_list.nh_forw; \
	    while (((np) = Xnp) != &ospf.nh_list) { \
		Xnp = (np)->nh_forw;
#define	NH_LIST_END(np) \
	    } \
	} while (0)

#define	OSPF_NH_ALLOC(np) \
	do { \
	    register struct NH_BLOCK *Xnp = (np); \
	    if (Xnp) { \
		Xnp->nh_refcount++; \
	    } \
	} while (0)

#define	ospf_nh_free(npp) \
	do { \
	    register struct NH_BLOCK *Xnp = *(npp); \
	    assert(!Xnp || Xnp->nh_back || !Xnp->nh_refcount); \
	    if (Xnp) { \
		register u_int Xrefcount = Xnp->nh_refcount; \
		Xnp->nh_refcount--; \
		assert(Xrefcount > Xnp->nh_refcount); \
	    } \
	    *(npp) = (struct NH_BLOCK *) 0; \
	} while (0)

#define	ospf_nh_free_list(cnt, list) \
	do { \
	    register u_int Xi = (cnt); \
	    while (Xi--) { \
		if (list[Xi]) { \
		    ospf_nh_free(&(list)[Xi]); \
		} \
		(cnt) = 0; \
	    } \
	} while (0)

#define	ospf_nh_set(cnt, ndx, n, nh) \
	do { \
	    register int Xn = (n); \
	    ospf_nh_free_list(cnt, ndx); \
	    while (Xn--) { \
	        OSPF_NH_ALLOC((ndx)[Xn] = (nh)[Xn]); \
	    } \
	    (cnt) = (n); \
	} while (0)

#define	ospf_nh_compare(cnt, ndx, n, nh) \
	((cnt) == (n) \
	 && !bcmp((byte *) (ndx), (byte *) (nh), (cnt) * sizeof (*ndx)))

PROTOTYPE(ospf_nh_add,
	  extern struct NH_BLOCK *,
	  (if_addr *,
	   u_int32,
	   int));
PROTOTYPE(ospf_nh_collect,
	  extern int,
	  (void));
PROTOTYPE(ospf_nh_merge,
	  extern u_int,
	  (u_int,
	   struct NH_BLOCK **,
	   u_int,
	   struct NH_BLOCK **));


/* Destination types */
#define DTYPE_NET  	0
#define DTYPE_ASBR 	1	/* autonomous system border rtr */
#define DTYPE_ABR  	2	/* area border rtr */
#define DTYPE_VIRT 	3
#define DTYPE_ASE  	4

/* Change types */
#define E_UNCHANGE              0
#define E_NEW                   1       /* New route */
#define E_NEXTHOP               2       /* Next hop has changed */
#define E_METRIC                3       /* Metric has changed */
#define E_WAS_INTER_NOW_INTRA   4       /* Was sum now intra */
#define E_WAS_INTRA_NOW_INTER   5       /* Was intra now sum */
#define E_ASE_METRIC            6       /* ASE metric has changed */
#define E_WAS_ASE               7       /* Was ase now internal */
#define E_WAS_INTRA_NOW_ASE     8       /* Was intra now ase */
#define E_WAS_INTER_NOW_ASE     9       /* Was inter now ase */
#define E_ASE_TYPE              10      /* From type 2 to type 1 or visa versa*/
#define E_ASE_TAG               11      /* Tag has changed */
#define E_DELETE                12

/* Path types */
#define PTYPE_ANY    	0x3F	/* internal and external routes */
#define PTYPE_INTRA  	0x7	/* intra route */
#define PTYPE_INTER  	0x18	/* inter route */
#define PTYPE_INT    	0x1F	/* intra or inter routes */
#define	PTYPE_INTNET	0x0f	/* inter area network routes */
#define PTYPE_EXT    	0x20	/* external routes */
#define PTYPE_LEAVES 	0x38	/* inter or ext */
#define PTYPE_BIT(T) 	(1 << (T))	/* T is lsa type */

/*
 * Check to see if the route is an active inter area route
 * - pass the level that has just been run, the area that
 *   is running the spf algorithm, and the route
 */
#define  INTER_ACTIVE(FROM,A,R)\
	   ( (PTYPE_BIT(ORT_PTYPE(R)) & PTYPE_INTER) &&\
	     ( (!((FROM) & PTYPE_INTER)) ||\
	       ( (((FROM) & PTYPE_INTER) &&\
	         ((ORT_REV(R) == RTAB_REV))) ||\
	         (ORT_AREA(R) != (A)) ) ) )

/* Function prototypes */
PROTOTYPE(addroute,
	  extern int,
	  (struct AREA *,
	   struct LSDB *,
	   int,
	   struct AREA *));
PROTOTYPE(rtr_findroute,
	  extern struct OSPF_ROUTE *,
	  (struct AREA *,
	   u_int32,
	   int,
	   int));
PROTOTYPE(ospf_int_active,
	  extern int,
	  (int,
	   struct AREA *,
	   rt_entry *));

#endif	/* RTAB_H */


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
