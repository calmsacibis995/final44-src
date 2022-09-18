/*
 *  isis_main.c,v 1.11 1993/01/07 22:39:35 jch Exp
 */

/* %(Copyright.header) */


/* these includes are overkill; they are what's included in krt.c */
#define	INCLUDE_ROUTE
#define	INCLUDE_FILE
#define	INCLUDE_CTYPE
#include "include.h"
#include "isis_includes.h"
#include "isis_test.h"
#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#ifdef 	PROTO_SNMP
#include "isis_mib.h"				/* Isis-Mib */
#endif  /* PROTO_SNMP */

PROTOTYPE(isis_init_ca, void, (struct is_pc *, int));
PROTOTYPE(isis_set_sysid, void, (char *, int));

#define MAX_DUMP 40
/* number of i/o bytes to dump if tracing */
#define DUMP_LEN(buflen) ((buflen<MAX_DUMP)?(buflen):MAX_DUMP)

int isis_test_krt; 		/* enable test interface */
int isis_log_input;
int isis_input_cnt; 		/* sequence # for logging */
int isis_log_fd;
int isis_log_output;
int isis_output_cnt; 		/* sequence # for logging */
int isis_out_fd;
int isis_ci;			/* used in parser */
int isis_circuits_parsed;
int isis_ci_reconfig;		/* used in parser during reconfig */
int isis_time; 			/* simulated time */
int isis_packet_id; 		/* input packet # for logging */
int run_from_log; 		/* if 1, read input log */
int input_fd; 			/* if run_from_log, fd we are reading from */

int useSim;			/* if we should enable the troll sockets */
int useRealNet;			/* if we should enable the real network sockets */

#define	MAXLOCALID	255
CircuitEntry *ifIndexToCircuit[MAXLOCALID];	/* map interface kernel index to circuit */
CircuitEntry *simIdToCircuit[MAXLOCALID];	/* map simulator subnet id to circuit */

struct is_pc isis_ca[MAX_IS_PCTS]; /* used in parser */
char * isis_areas[MaximumAreaAddresses];
int isis_num_areas;

struct isis_ipr  * IPRList = 0; /* initialization */
struct isis_pref * prefixList = 0;
/* struct isis_ipr isis_iprs[MAX_IS_IPRS]; */
/* test dummies */
static MACAddress myMAC;
MetricList noMetric = {0xff, 0xff, 0xff, 0xff};
static int sysIDisset = 0;

/* task stuff */
static task *isisUtilTask = (task *) 0;
static task *isisRealTask = (task *) 0;
static task *isisSimTask = (task *) 0;
static task_timer *isis_timer = 0;
static task_timer *spf_timer = 0;
static task_timer *csnp_timer = 0;
static task_timer *psnp_timer = 0;
static task_timer *flood_p2p_timer = 0;
static task_timer *flood_broadcast_timer = 0;

#define	SPF_TIMER			/* enable SPF timer */

/* tsi stuff */
static block_t isis_tsi_info_block; 
static u_int isis_rtbit = 0;
struct isis_tsi_info {
	char 		*tsi_opt;	/* where to find this prefix */
	int		tsi_level;	/* 1 or 2 */
	struct isis_ann *tsi_ia;	/* where we remembered this announcement */
};
#define	ISIS_TSI_SIZE	(sizeof(struct isis_tsi_info *))
#define	ISIS_TSI_PUT(rth, rtbit, p, level, ann) \
	do { \
		struct isis_tsi_info *Xtsi = (struct isis_tsi_info *) task_block_alloc(isis_tsi_info_block); \
		isisCounters.tsi_info++; \
		Xtsi->tsi_opt = (char *) p; \
		Xtsi->tsi_level = level; \
		Xtsi->tsi_ia = ann; \
		rttsi_set(rth, rtbit, (byte *) &Xtsi); \
	} while(0);
#define	ISIS_TSI_GET(rth, rtbit, p, ptype, level, ann, tsi) \
	do { \
		/* struct isis_tsi_info *tsi;*/ \
		rttsi_get(rth, rtbit, (byte *) &(tsi)); \
		p = (ptype) (tsi)->tsi_opt; \
		level = (tsi)->tsi_level; \
		ann = (tsi)->tsi_ia; \
	} while(0);
#define	ISIS_TSI_FREE(rth, rtbit) \
	do { \
		struct isis_tsi_info *Xtsi; \
		rttsi_get(rth, rtbit, (byte *) &Xtsi); \
		task_block_free(isis_tsi_info_block, (void_t) Xtsi); \
		isisCounters.tsi_info--; \
	} while(0);

/* 
 * List of routes we're announcing.
 */
struct isis_ann {
	struct isis_ann *ia_forw;
	struct isis_ann *ia_back;
	rt_entry *rt;
};
static struct isis_ann isis_ann_list = { &isis_ann_list, &isis_ann_list };
static block_t isis_ann_block = (block_t) 0;

#define ISIS_ANN(p) for ((p)=isis_ann_list.ia_forw; (p)!= &isis_ann_list; (p)=p->ia_forw)
#define ISIS_ANN_END(p)
	

bits isis_update_bits[] = {
        {ISIS_NEWPOLICY, "new policy"},
        {ISIS_INITIAL, "initial"},
        {ISIS_FLASH, "flash"},
        {0}
};

/* 
 * Save the info from an ipreach statement for updating 
 * isis after parse.
 */
void
save_ipreach  __PF5(level, int,
		    type, int,
		    addr, sockaddr_un *,
		    mask, sockaddr_un *,
		    metric, int)
{
	struct isis_ipr *ipreach;

	ipreach = castMalloc(struct isis_ipr *, sizeof(struct isis_ipr));

	/* test for out of bounds, later. */
	ipreach->level = level;
	switch(type) {
	case ISIS_INTERNAL:	
		ipreach->type = IPIntReachCode; 
		break;
	case ISIS_EXTERNAL:  
		ipreach->type = IPExtReachCode; 
		ipreach->level = 2; /* always */
		break;
	case ISIS_SUMMARY: 
		ipreach->type = IPSumReachCode; 
		ipreach->level = 2; /* always */
		ipreach->autoSum = 0;
		break;
	case ISIS_AUTOSUMMARY:
		/* automatically added by level 1 for each IFF_UP circuit */
		ipreach->type = IPSumReachCode; 
		ipreach->level = 2; /* always */
		ipreach->autoSum= 1;
		break;
	default: 
		ipreach->type = IPIntReachCode; 
		break;
	}
	ipreach->addr = sock2in(addr);
	ipreach->mask = sock2in(mask);
	ipreach->metric = noMetric;
	ipreach->metric.defalt = metric;
	ipreach->next = IPRList;
	IPRList = ipreach;
}


int
isis_get_krt_socket()
/* dummy routine to test krt interface.  For the time being, we just
	open a file that the routing updates get dumped into. */
{
	int fd;
	fd = creat("kernel_updates",0644);
	if (fd < 0) {
	    perror("krt test creat failed");
	    exit(-1) ;
	}

	return fd;
}

int 
isis_ioctl(fd,req,argp)
int fd,req;
char *argp;
/* dummy ioctl call */
{
	int rc;
	struct rtentry *rpt = (struct rtentry *) argp;
	rc = write(fd,argp, sizeof(*rpt));
	if (rc < 0)
		return -1;
	return 0;
}


/* startup code */
int doing_isis;
int isis_initial_config = 1;	/* 0 if this is a reconfig of a running IS-IS */
int isis_snpa = 0; 		/* test code only */
int isis_plevel;		/* level 1 or level 2; set to T_LEVEL1/T_LEVEL2 in parser */
metric_t isis_default_metric;


/* 
 * Start of reconfig.  Free any policy stuff here.
 */
void
isis_cleanup __PF1(tp, task *)
{
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_INFO,
		     ("IS-IS reinitializing"));
	isis_initial_config = 0;
	/* no policy */
}

/*
 * Pretty print IS-IS tsi info.
 */
static void
isis_tsi_dump __PF4(fp, FILE *,
		    rth, rt_head *,
		    data, void_t,
		    pfx, const char *)
{
    task *tp = (task *) data;
    prefIP *p;
    int level;
    struct isis_ann *ia;
    struct isis_tsi_info *tsi;

    if (rth->rth_active
	&& rtbit_isset(rth->rth_active, isis_rtbit)) {
	ISIS_TSI_GET(rth, isis_rtbit, p, prefIP *, level, ia, tsi);
	switch(p->opt->type) {
	case IPExtReachCode:
	    (void) fprintf(fp, "%sIS-IS L%d IP External (E.%d)\n",
			   pfx,
			   level,
			   p->metrics.defalt & 0x3f);
	    break;

	case LSPPrefixNeighborCode:
	    (void) fprintf(fp, "%sIS-IS L%d Prefix (E.%d)\n",
			   pfx,
			   level,
			   p->metrics.defalt & 0x3f);
	    break;

	case IPIntReachCode:
	    (void) fprintf(fp, "%sIS-IS L%d IP Internal (I.%d)\n",
			   pfx,
			   level,
			   p->metrics.defalt & 0x3f);
	    break;
	}
    }
}

/*
 * Pick up any valid changes to routes exported from gated.
 */
void
isis_policy __PF3(tp, task *,
		  rtl, rt_list *,
		  why, int)
{
	rt_head *rth;
	rt_entry *rt, *oldrt;
	adv_results result;
	adv_entry *export_list;
	rt_changes *rtc;
	int pathchanged, metricchanged;
	int oldmetric;
	as_path *oldpath;
	MetricList metric;
	int numBits;
	int level, code;
	prefIP *p;
	int af;
	utime_t start, end;
	int totalms, ipdel, ipadd, ipmetchange, pathchange;
	struct isis_ann *ia;
	struct isis_tsi_info *tsi;

#define	horkOldRt(rth, oldrt) \
	{ \
	ISIS_TSI_GET(rth, isis_rtbit, p, prefIP *, level, ia, tsi); \
	if (p->opt->type != LSPPrefixNeighborCode) { \
		ipdel++; \
		clearIPReachable(level,p->opt->type, p); \
	} else { \
		numBits = mask_bits(rth->rth_dest_mask); \
		delPrefNeighbor(L2LSP, metric, rth->rth_dest->iso.giso_addr, (numBits+7) >> 3, (prefISO *) p); \
	} \
	ISIS_TSI_FREE(rth, isis_rtbit); \
	rtbit_reset(oldrt, isis_rtbit); \
	REMQUE(ia); \
	isisCounters.isis_announced--; \
	task_block_free(isis_ann_block, (void_t) ia); \
	}

	IFTRACE(T_ROUTE1)
		TIMER_PEEK();
		start = utime_current;	/* struct copy */
	ENDTRACE

	ipdel = ipadd = pathchange = ipmetchange = 0;
	(void) bcopy((caddr_t) &noMetric, (caddr_t) &metric, sizeof(MetricList));

	rt_open(tp);

	RT_LIST(rth, rtl, rt_head) {
		af = socktype(rth->rth_dest);
		if (((af == AF_INET) && !ip_supported) ||
		    ((af == AF_ISO) && !clnp_supported)) {
			continue;
		}
		oldrt = (rt_entry *) 0;
		if ((rth->rth_last_active != NULL) && rtbit_isset(rth->rth_last_active, isis_rtbit)) {
			/* a route I was exporting has changed */
			oldrt = rth->rth_last_active;
		}
		/* basic optimizations to avoid calling export() */
		if ((rt = rth->rth_active) == (rt_entry *) 0) {
			if (oldrt) horkOldRt(rth, oldrt);
			continue;
		}
		if (!rt->rt_aspath) {
			/* suggestion from Dennis - don't export route (e.g., imported by OSPF) before attributes arrive */
			if (oldrt) horkOldRt(rth, oldrt);
			continue;
		}
		if (BIT_TEST(rt->rt_state, RTS_NOADVISE|RTS_PENDING))
			rt = (rt_entry *) 0;
		else {
			switch(rt->rt_gwp->gw_proto) {
			case RTPROTO_DIRECT:
				/* ignore interface routes for circuits over which I'm running */
				if (BIT_TEST(rt->rt_state, RTS_NOTINSTALL) ||
				    BIT_TEST(RT_IFAP(rt)->ifa_rtactive, RTPROTO_BIT(RTPROTO_ISIS)) ||
				    BIT_TEST(RT_IFAP(rt)->ifa_state, IFS_LOOPBACK)) {
					rt = (rt_entry *) 0;
				}
				break;
			case RTPROTO_ISIS:
				/* ignore our own routes */
				rt = (rt_entry *) 0;
				break;
			default:
				break;
			}
		}
		/* 
		 * We change the LS database iff one of the following is true:
		 * 1) we have an old route and will advertise a different new route
		 * 2) we do not have an old route and will advertise the new route
		 * 3) we have an old route and will not advertise the new route
		 */
		export_list = (af == AF_INET) ? isis_export_list_ip : isis_export_list_iso;
		result.res_metric = 0x3f;
		if ((rt) 
#define	EXPORT
#ifdef	EXPORT
		    && 
		    export(rt, (proto_t) 0,
			   export_list,		/* proto list */
			   (adv_entry *) 0, 	/* interface list */
			   (adv_entry *) 0, 	/* gateway list */
			   &result)) {
#else
		) {
			result.res_metric = rt->rt_preference;
			metric.defalt = (result.res_metric & 0x3f) | 0x40;	/* XXX - export() will eventually do this */
#endif	/* EXPORT */
			metric = noMetric;
			metric.defalt = result.res_metric | 0x40;		/* turn on external metric flag */
			if (oldrt) {
				/* 
				 * This is case (1) above.
				 * 
				 * Optimizations:
				 * a) if no AS path changes and no metric changes, just change rtbits and continue
				 * b) if just a metric change and AF_INET, just change existing option, rtbits, and continue
				 */
				pathchanged = metricchanged = 0;
				oldpath = oldrt->rt_aspath;
				ISIS_TSI_GET(rth, isis_rtbit, p, prefIP *, level, ia, tsi); 
				oldmetric = p->metrics.defalt;	
				rtc = rth->rth_changes;
				if (rtc && BIT_TEST(rtc->rtc_flags, RTCF_ASPATH)) 
					oldpath = rtc->rtc_aspath;
				if (oldpath != rt->rt_aspath) pathchanged = 1;
				if (oldmetric != metric.defalt) metricchanged = 1;
				if (!pathchanged) {
					if (!metricchanged) {
						rtbit_reset(oldrt, isis_rtbit); 
						rtbit_set(rt, isis_rtbit);
						ia->rt = rt;
						continue;
					} else if (af == AF_INET) {
						lspIPPrefixChanged(p, metric);
						rtbit_reset(oldrt, isis_rtbit); 
						rtbit_set(rt, isis_rtbit);
						ia->rt = rt;
						ipmetchange++;
						continue; 
					}
				} else pathchange++;
				horkOldRt(rth, oldrt);
			}
			rtbit_set(rt, isis_rtbit);
			ia = (struct isis_ann *) task_block_alloc(isis_ann_block);
			INSQUE(ia, isis_ann_list.ia_back);
			ia->rt = rt;
			switch (af) {
			case AF_INET:
				p = setIPReachable(2, IPExtReachCode, metric, 
						   sock2in(rth->rth_dest), 
						   sock2in(rth->rth_dest_mask),
						   rt->rt_aspath);
				ISIS_TSI_PUT(rth, isis_rtbit, p, 2, ia);
				ipadd++;
				break;
			case AF_ISO:
				numBits = mask_bits(rth->rth_dest_mask);
				if ((numBits % 4) != 0) {
					/* prefix doesn't end on a nibble boundary */
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("IS-IS rounding prefix %A/%A to next semi-octet boundary",
						      rth->rth_dest,
						      rth->rth_dest_mask));
				}
				p = (prefIP *) addPrefixNeighbor(L2LSP, metric, 
								 rth->rth_dest->iso.giso_addr, 
								 (numBits+3) >> 2,
								 rt->rt_aspath);
				ISIS_TSI_PUT(rth, isis_rtbit, p, 2, ia);
				break;
			default:
				rt = (rt_entry *) 0;
			}
		} else if (oldrt) {
			/* this is case (3) above */
			horkOldRt(rth, oldrt);
		}
	} RT_LIST_END(rth, rtl, rt_head);

	rt_close(tp, 0, 0, 0);

	IFTRACE(T_ROUTE1)
		TIMER_PEEK();
		end = utime_current;	/* struct copy */
		totalms = (end.ut_sec - start.ut_sec) * 1000 + (end.ut_usec - start.ut_usec) / 1000;
		tracef("IS-IS: %s update", trace_state(isis_update_bits, why));
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_INFO,
			     (" - IP: %d adds, %d deletions, %d path changes, %d metric changes, %d ms", 
			      ipadd,
			      ipdel,
			      pathchange,
			      ipmetchange,
			      totalms));
	ENDTRACE
}

/* 
 * Reevaluate export policy here.
 */
void
isis_newpolicy __PF2(tp, task *,
		     rtl, rt_list *)
{
	isis_policy(tp, rtl, ISIS_NEWPOLICY);
}

/*
 * Process flash update from gated.
 */
void
isis_flash __PF2(tp, task *,
		 rtl, rt_list *)
{
	isis_policy(tp, rtl, ISIS_FLASH);
}

void
isis_dump __PF2(tp, task *,
		fd, FILE *)
{
	int i;
	CircuitEntry *c;
	AdjacencyEntry *adj;
        LSPDesc *desc;
	LSPOption *opt;
	long t;
	long totmem;

	fprintf(fd,"\nRouting Bit: %u\n", isis_rtbit);

	fprintf(fd,"PDU Format Errors       \t%d\n", isisCounters.pduFormatErrors);
	fprintf(fd,"Corrupt LSPs Detected   \t%d\n", isisCounters.corruptLSPDetected);
	fprintf(fd,"L1 LSP Overload         \t%d\n", isisCounters.l1LSPOverload);
	fprintf(fd,"L2 LSP Overload         \t%d\n", isisCounters.l2LSPOverload);
	fprintf(fd,"Manual Areas Dropped    \t%d\n", isisCounters.manualAreaDropped);
	fprintf(fd,"Sequence Number Exceeded\t%d\n", isisCounters.exceedSeqNum);
	fprintf(fd,"Sequence Number Skipped \t%d\n", isisCounters.seqNumSkipped);
	fprintf(fd,"Purge Local LSP         \t%d\n", isisCounters.purgeOwnLSP);

	fprintf(fd,"\nMemory Usage\n");
	t=isisCounters.option;
	fprintf(fd,"option blocks\t\t%d\t%d bytes\n", t, t*sizeof(LSPOption));
	t=isisCounters.optiondata;
	fprintf(fd,"option data blocks\t%d\t%d bytes\n", t, t*(MaxOptLen-2));
	t=isisCounters.prefIP;
	fprintf(fd,"IP prefix blocks\t%d\t%d bytes\n", t, t*sizeof(prefIP));
	t=isisCounters.prefISO;
	fprintf(fd,"ISO prefix blocks\t%d\t%d bytes\n", t, t*sizeof(prefISO));
	t=isisCounters.lspattr;
	fprintf(fd,"attribute blocks\t%d\t%d bytes\n", t, t*sizeof(LSPattr));
	t=isisCounters.tsi_info;
	fprintf(fd,"route tsi blocks\t%d\t%d bytes\n", t, t*sizeof(struct isis_tsi_info));
	t=isisCounters.intnode;
	fprintf(fd,"interior node blocks\t%d\t%d bytes\n", t, t*sizeof(struct interior_node));
	t=isisCounters.ipleaf;
	fprintf(fd,"IP leaf blocks\t\t%d\t%d bytes\n", t, t*sizeof(struct ip_leaf));
	t=isisCounters.isoleaf;
	fprintf(fd,"ISO leaf blocks\t\t%d\t%d bytes\n", t, t*sizeof(struct iso_leaf));
	t=isisCounters.lspdescs;
	fprintf(fd,"lsp desc blocks\t\t%d\t%d bytes\n", t, t*sizeof(LSPDesc));
	t=isisCounters.lsentries;
	fprintf(fd,"lsp entry blocks\t%d\t%d bytes\n", t, t*sizeof(LSEntry));
	t=isisCounters.sumnodes;
	fprintf(fd,"IP summary blocks\t%d\t%d bytes\n", t, t*sizeof(struct sumlist));
	t=isisCounters.lseChangeList;
	fprintf(fd,"Prefix change blocks\t%d\t%d bytes\n", t, t*sizeof(struct _lseChangeList));
	t=isisCounters.lspbufs;
	fprintf(fd,"lsp buffers\t\t%d\t%d bytes\n", t, isisCounters.lspbytes);
	t=isisCounters.adjEntries;
	fprintf(fd,"adj entries\t\t%d\t%d bytes\n", t, t*sizeof(AdjacencyEntry));
	t=isisCounters.agelists;
	fprintf(fd,"agelists\t\t%d\t%d bytes\n", t, t*sizeof(AgeList));
	t=isisCounters.circuitEntries;
	fprintf(fd,"circuit entries\t\t%d\t%d bytes\n", t, t*sizeof(CircuitEntry));
	fprintf(fd,"adj neighbor info\t%d\n", isisCounters.adjNeighborInfo);

	fprintf(fd,"\nOption Breakdown\n");
	fprintf(fd,"IP external prefix\t%d\n", isisCounters.ipext);
	fprintf(fd,"IP internal prefix\t%d\n", isisCounters.ipint);
	fprintf(fd,"IP summary prefix\t%d\n", isisCounters.ipsum);
	fprintf(fd,"ISO prefix\t\t%d\n", isisCounters.isopref);
	fprintf(fd,"Leaf node\t\t%d\n", isisCounters.leaves);
	fprintf(fd,"IDRP info\t\t%d\n", isisCounters.idrpi);
	fprintf(fd,"IS neighbors\t\t%d\n", isisCounters.isn);
	fprintf(fd,"ES neighbors\t\t%d\n", isisCounters.esn);
	fprintf(fd,"Area Address\t\t%d\n", isisCounters.aa);
	fprintf(fd,"IP interface\t\t%d\n", isisCounters.ipintf);
	fprintf(fd,"Protos supported\t%d\n", isisCounters.protosup);
	fprintf(fd,"PD L2 IS\t\t%d\n", isisCounters.pdl2is);
	fprintf(fd,"IP authentication\t%d\n", isisCounters.ipauth);
	fprintf(fd,"Authentication\t\t%d\n", isisCounters.auth);

	fprintf(fd,"\ncircuits\nname\tstate\tmetrics\t\tpdus (corrupt)\n");
	for (i=0; i<MaximumCircuits; i++) {
		if ((c = circuitList[i]) == NULL) continue;
		if (c->manualL2Only)
			fprintf(fd,"%s\t%s\tL2.%d      \tTX.%d RX.%d (%d)\n",
				c->name, (c->up) ? "up":"down", c->l2Metric.defalt,
				c->pdusSent, c->pdusReceived, c->corruptedLSPs);
		else 
			fprintf(fd,"%s\t%s\tL1.%d L2.%d\tTX.%d RX.%d (%d)\n",
				c->name, (c->up) ? "up":"down", c->l1Metric.defalt, c->l2Metric.defalt,
				c->pdusSent, c->pdusReceived, c->corruptedLSPs);
	}
	fprintf(fd,"\nadjacencies\nneighbor\t\ttype\tht\tstate\n");
	for (i=0; i<MaximumCircuits; i++) {
		if ((c = circuitList[i]) == NULL) continue;
		if (c->isAdjs && !(DLListEmpty(&c->isAdjs->links)) ) {
			IterateDLListForw(adj, &c->isAdjs->links, AdjacencyEntry *) {
				fprintf(fd,"%s:%s\t%s%s\t%d\t%s\n", c->name, IDToStr(adj->neighborSysID, 6),
					((adj->adjacencyType==L2IS) && !adj->level2Only && (c->circuitType==Pt2Pt)) ? "L1 ":"",
					systemTypeToStr(adj->adjacencyType), 
					adj->holdingTime, adjStateToStr(adj->state));
			}
		}
	}
	fprintf(fd, "\n");
	fprintf(fd, "Level 2 Path Attribute Distribution by LSP:\n");
        IterateDLListForw(desc, &L2LSP->list, LSPDesc *) {
		fprintf(fd, "LSP N#%d:\n\t", desc->lspNumber);
		if (DLListEmpty(&desc->options)) {
			fprintf(fd, "empty\n");
			continue;
		} 
		i = 0;
        	IterateDLListForw(opt, &desc->options, LSPOption *) {
			if (opt->attr) {
				if (i++ == 6) {
					fprintf(fd, "\n\t");
					i = 0;
				}
				if (opt->attr->path)
                			fprintf(fd, "Id %d (%d)  ", (u_int) opt->attr->path->path_id, (u_int) opt->attr->refcount);
				else
                			fprintf(fd, "IGP (%d)  ", (u_int) opt->attr->refcount);
			}
		}
		fprintf(fd, "\n");
        }
	fprintf(fd, "\n");
	dumpLSPDB(fd, 1);
	dumpLSPDB(fd, 2);
	fprintf(fd, "End of %s Dump\n", tp->task_name);
}

/* 
 * Reevaluate import policy here.
 */
static void
isis_reinit __PF1(tp, task *)
{
	rt_entry *rt;
	pref_t pref;
	int changes = 0;
	extern gw_entry *isis_gwp[];

	/* start with all of our level 2 routes */
	pref = isis_preference[2];

	rt_open(tp);

	RTQ_LIST(&isis_gwp[2]->gw_rtq, rt) {
		if (!(BIT_TEST(rt->rt_state, RTS_EXTERIOR))) continue;		/* no policy on interior routes */
		(void) import(	rt->rt_dest, 
				rt->rt_dest_mask,
				(socktype(rt->rt_dest) == AF_INET) ? isis_import_list_ip : isis_import_list_iso,
				(adv_entry *) 0,
				(adv_entry *) 0,
				&pref,
				(if_addr *) 0,
				(void_t) 0);	
		if (rt->rt_preference != pref) {
			/* preference has changed, so deal with it */
			(void) rt_change(rt,
					 rt->rt_metric,
					 rt->rt_metric2,
					 rt->rt_tag,
					 pref,
					 rt->rt_preference2,
					 rt->rt_n_gw, rt->rt_routers);
		}
		changes++;
	} RTQ_LIST_END(&isis_gwp[2]->gw_rtq, rt);

	rt_close(tp, (gw_entry *) 0, changes, NULL);
}

#define TBUF_SIZE 80

/* 
 * Open a file to log all input data in binary;
 * return the file descriptor.
 */
int
open_input_log()
{
    int fd;

    fd = creat("input_log", 0644);
    if (fd < 0) {
	perror("input log creat failed");
	exit(-1) ;
    }

    write(fd,&time_sec,sizeof(time_sec));
    return fd;
}

/* 
 * Open a file to log all output data in binary;
 * return the file descriptor.
 */
int
open_output_log()
{
    int fd;

    fd = creat("output_log",0644);
    if (fd < 0) {
	perror("output log  creat failed");
	exit(-1) ;
    }

    write(fd, &time_sec, sizeof(time_sec));
    return fd;
}	

/* 
 * Save the input as binary data in a file.
 */
void
isisLogPacket(buf, len, src, c)
char		*buf;
int			len;
MACAddress	src;
CircuitEntry 	*c;
{
	if (isis_log_input) {
		struct log_header in_log; 
		in_log.io_time = isis_time;
		in_log.io_count = ++ isis_input_cnt;
		in_log.io_len = len;
		bcopy((caddr_t) src, (caddr_t) in_log.io_src, sizeof(MACAddress));
		in_log.io_id = c->localId;
		if (!isis_log_fd)
			isis_log_fd = open_input_log();
		write(isis_log_fd,&in_log,sizeof(in_log));
		write(isis_log_fd,buf,len);
	}
}

/* 
 * Demultiplex on circuit number.
 */
void
isis_recv(c, buf, len, src)
CircuitEntry	*c;
char		*buf;
int			len;
MACAddress	src;
{
	int	i;

	/* NSS STEVE - filter out my own packets */
	if (bcmp((caddr_t) src, (caddr_t) c->myMAC, sizeof(MACAddress))) pduInput(c, buf, len, src);
}

task *isis_task = 0; /* currently running isis task, if there is one */
trace *isis_trace_options = (trace *) 0;
const bits isis_trace_types[] = {
    { 0, NULL }
};


void
isisCheckSPF __PF2(tip, task_timer *,
		   interval, time_t)
{
	if ((runL1spf || runL2spf) && (systemType == L2IS)) updateAreaSummary();
	if (runL1spf) isis_spf(1);
	if (runL2spf) {
		if (adjustPrefsOnly) ; /* isis_adjustPrefs(); */
		else isis_spf(2);
	}
	runL1spf = runL2spf = 0;
	isis_freelseChangeList();
	adjustPrefsOnly = 1;
}

/* 
 * Read a real packet from network and input.
 */
void
isisRealRecv(tp)
task *tp;
{
	char buf[MaxPacketSize];
	int indx, len, totalbytes;
	MACAddress src;
	CircuitEntry *c;
	int n_packets;

	isis_task = tp;
	n_packets = max(TASK_PACKET_LIMIT, BLSPThrottle << 1);
	totalbytes = 0;

	while (n_packets-- && ((len=RecvData(tp->task_socket, &indx, buf, sizeof(buf), src)) > 0)) {
		totalbytes += len;
		if ((c = ifIndexToCircuit[indx]) == 0) continue;	/* unconfigured circuit */
		isis_recv(c, buf, len, src);
	}

	/* 
	 * If no more in the socket, we should run SPF immediately.  If we
	 * read out the limit, there is likely to be more waiting for us
	 * which we'll process when gated returns control to us.  In this
	 * case, we will postpone the SPF hoping to read yet more from the
	 * socket, avoiding an extra run of the SPF.  If the actual number
	 * of packets in the socket was exactly our limit (there is no more
	 * waiting), then we will run the SPF on the next firing of our SPF
	 * timer.  The timer also handles the cases when 1) we've become
	 * isolated from the rest of the IS-IS world and must inform gated
	 * of that fact (there will be no input on which to trigger this
	 * particular check) and 2) we changed our own LSPs because of a 
	 * flash or new policy update.
	 */
	if (n_packets) 
		isisCheckSPF((task_timer *) 0, (time_t) 0); 
}

/* 
 * Read a packet from the simulator.
 */
void
isisSimRecv(tp)
task	*tp;
{
	struct NetMessage thdr;
	MACAddress src;
	CircuitEntry *c;

	isis_task = tp;
	trollRecvData(tp->task_socket, &thdr);
	c = simIdToCircuit[thdr.subnetId];

	bzero((caddr_t) src, sizeof(MACAddress));
	sprintf((char *) src, "%d", thdr.snpa);

	isisLogPacket(thdr.buf, thdr.buflen, src, c);

	isis_recv(c, thdr.buf, thdr.buflen, src);
}

/* 
 * Process a log record as if it were an input packet.
 */
void 
process_log_input(lpt)
struct log_header *lpt;
{
	char  test_buf[MaxPacketSize];
	int len;

	len = read(input_fd,test_buf,lpt->io_len);
	isis_recv(lpt->io_id, test_buf, len, lpt->io_src);
}

#ifdef notdef
void
check_send_trace(sid,hdr,test_buf,len)
int sid;
struct netdHeader *hdr;
char * test_buf;
int len;
{
/* TODO: use new fields of larger io record */
	if (isis_log_output)
	/* save the input as binary data in a file */
	{
		struct log_header in_log; 
		in_log.io_time = isis_time;
		in_log.io_count = ++ isis_output_cnt;
		in_log.io_len = len /* + sizeof(*hdr) */;
		if (!isis_out_fd)
			isis_out_fd = open_output_log();
		write(isis_out_fd,&in_log,sizeof(in_log));
/* 		write(isis_out_fd,hdr,sizeof(*hdr)); so same format as input rec */
		write(isis_out_fd,test_buf,len);
	}
}
#endif

int 
str_to_hex (cstr, result, resultLen)
char *cstr; 
unsigned char *result;
int resultLen;
{
	int len = 0;
	int val;
	char *cpt = cstr;
	bzero((caddr_t) result, resultLen);
	while (*cpt && len < resultLen*2) {
		char c = *cpt;
		cpt++;
		if (isdigit(c))
			val = c - '0';
		else if (isxdigit(c))
		{
			if (isupper(c))
				val = (c - 'A') + 10;
			else /* lower presumably */
				val = (c - 'a') + 10;
		}
		else /* not a hex digit */
			continue;
		if ((len % 2) == 0) /* even */
			result[len/2] = val << 4;
		else /* odd */
			result[len/2] |= val;
		len++;
	}
/* 	printf("str_to_hex %s\n", cstr);*/
	return len;
}
			

void 
isis_set_circuit(iscpt)
struct is_pc *iscpt;
{
	CircuitEntry *c;
	CircuitType ctype;
	int prior, l2prior;
	octet *lMac;
	Boolean manl2 = False; 	/* level 2 only? */
	MetricList l1metric;
	MetricList l2metric;
	int metricChange, priorChange;
	int sock;
	if_addr *ifap;

	if (!iscpt->configured) {
		/* this is an unconfigured circuit */
		isis_init_ca(iscpt, 0);
	}

	l1metric = l2metric = noMetric;
	if (iscpt->metric)
		l1metric.defalt = iscpt->metric;
	if (iscpt->l2metric)
		l2metric.defalt = iscpt->l2metric;
	ctype = iscpt->is_ptp ? Pt2Pt : Broadcast;
	prior = iscpt->prior ? iscpt->prior : 1;
	l2prior = iscpt->l2prior ? iscpt->l2prior : 1;

	lMac = (octet *) (iscpt->snpa) ? iscpt->snpa->ll.gll_addr : myMAC;

	/* we have a level 2 metric but no level 1; assume l2 only */
	if ( iscpt->l2metric && !iscpt->metric)
		manl2 = True;

	if (run_from_log)
		sock = -1;
	else if (iscpt->mode == REALD)
		sock = isisRealTask->task_socket;
	else {
		assert(iscpt->mode == TROLLD);
		sock = isisSimTask->task_socket;
	}

	/* set circuit's IP address */
	if ((ip_supported) && (iscpt->mode == REALD)) {
		IF_ADDR(ifap) {
                	if (BIT_TEST(ifap->ifa_state, IFS_UP)
			    && (!strcasecmp(iscpt->name, ifap->ifa_link->ifl_name)) &&
                        	(socktype(ifap->ifa_addr) == AF_INET))
                        	break;
    		} IF_ADDR_END(ifap);
		if (ifap == NULL) {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("no IP address for %s - you lose bigtime",
				      iscpt->name));
		} else {
                	iscpt->ipaddr = *(ifap->ifa_addr_local);
                        iscpt->ipaddrSet = 1;
		}
	}

	/* check for priority or metric change on already active circuit */
	if (iscpt->configured) {
		/* 
		 * The circuit's next timer pop will fire off some hellos 
		 * and run the DR election if necessary.  We update the
		 * relevant LSPs first (using the values from the original
		 * CircuitEntry), then we update the CircuitEntry itself.
		 */
		l1metric.defalt &= 0x3f;				/* 0x3f => supported internal metric */
		l2metric.defalt &= 0x3f;
		l1metric.delay = 0x80 | (l1metric.delay & 0x3f);	/* 0x80 => unsupported */
		l1metric.expense = 0x80 | (l1metric.expense & 0x3f);
		l1metric.error = 0x80 | (l1metric.error & 0x3f);
		l2metric.delay = 0x80 | (l2metric.delay & 0x3f);
		l2metric.expense = 0x80 | (l2metric.expense & 0x3f);
		l2metric.error = 0x80 | (l2metric.error & 0x3f);

		/* take appropriate actions if metric or priority is different */
		c = ifIndexToCircuit[iscpt->index];
		metricChange = priorChange = 0;
		if ((bcmp(&c->l2Metric, &l2metric, sizeof(MetricList))) ||
		    (bcmp(&c->l1Metric, &l1metric, sizeof(MetricList)))) {
			metricChange = 1;
		}
		if ((c->l2Priority != l2prior) || (c->l1Priority != prior)) {
			priorChange = 1;
		}
		if (metricChange) {
			/* 
			 * STEVE - we only really need to alter the appropriate LSP, 
			 * not necessarily both here, but for now...
			 */
			trace_tf(isis_trace_options,
				 TR_NORMAL,
				 0,
				 ("IS-IS changing metrics for circuit %s",
				  c->name));
			lspCircuitChanged(c, l1metric, l2metric);	
		}
		if (metricChange || priorChange) {
			if (priorChange) {
				trace_tf(isis_trace_options,
					 TR_NORMAL,
					 0,
					 ("IS-IS changing priorities for circuit %s",
					  c->name));
			    }
			changeCircuit(c, l1metric, l2metric, prior, l2prior);	/* updates timer intervals too */
		}

		return;
	}

	c = createCircuit(sock, ctype, iscpt->name, l1metric, l2metric,
		prior, l2prior, manl2, lMac, iscpt->index);

	/* these are different arrays because a simulator and real interface could
		have the same index number */
	if (iscpt->mode == REALD) {
		ifIndexToCircuit[iscpt->index] = c;
		c->transmitFunc = Transmit;
	} else {
		simIdToCircuit[iscpt->index] = c;
		c->simSubnetId = iscpt->index;
		c->transmitFunc = trollTransmit;
		trollJoinGroup(c->fd, iscpt->index);
	}
#ifdef 	PROTO_SNMP
        {
	    IsisMibEntry	*pMibEntry;
	    IsisCircTable	*pCircTable;
	    IsisCircEntry	*pCircEntry;

	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	    pCircTable = &pMibEntry->isisCircTable;
	    pCircEntry = (IsisCircEntry *)queueNew(pCircTable);

	    if (pCircEntry) { 	/* a new entry has been allocated in circ table */
		pCircEntry->isisCircIndex = c->localId;
		pCircEntry->isisCircExistState = 2;		/* Isis-Mib */
		queueAdd(pCircTable, pCircEntry);
	    }
	    else {	/* cannot allocate circ entry */
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("Cannot allocate Circ Mib table entry"));
	    }
    	}
#endif  /* PROTO_SNMP */

	if (iscpt->ipaddrSet) {
		addIPAddr(c, sock2in(&iscpt->ipaddr));
	}

	iscpt->configured = 1;	/* this completes the circuit configuration procedure */
	circuitUpEvent(c);
}

/* 
 * Called from parser to save area address.
 */
void
isis_saveArea(cpt)
char *cpt;
{
	if (isis_num_areas > MaximumAreaAddresses) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("IS-IS: too many areas - %s not saved",
			      cpt));
	} else {
		isis_areas[isis_num_areas] = cpt;
		isis_num_areas++;
		trace_tf(isis_trace_options,
			 TR_NORMAL,
			 0,
			 ("IS-IS: new area address %s",
			  cpt));
	}
}

typedef struct _InterDomInfo {
        u_char  data[255];
        int             len;
        struct _InterDomInfo    *next;
} InterDomInfo;

InterDomInfo    *interDomInfoList = NULL;

void
isis_saveInterDomInfo(s)
u_char  *s;
{
        InterDomInfo *idi;
        int nibbleLen;

        idi = castMalloc(InterDomInfo *, sizeof(InterDomInfo));

        nibbleLen = str_to_hex(s, idi->data, sizeof(idi->data));
        idi->len = nibbleLen/2;
        if (0x00000001 & nibbleLen)
                idi->len++;
        idi->next = interDomInfoList;
        interDomInfoList = idi;
}


/* 
 * Called from parser to save prefix address.  We may need 
 * to extend this to allow a route to be configured.
 */
void
isis_savePrefix __PF3(pstr, u_char *,		/* prefix as a string */
		      parsedMetric, int,	/* cost */
		      prefType, int)		/* internal or external */
{
	struct isis_pref *ppt;
	int metric;
	ADDR_PREF newPref;

	/* find existing prefix, if any */
	ppt = NULL;
	newPref.pref_len = str_to_hex(pstr,newPref.addr,sizeof(newPref.addr));
	for (ppt=prefixList; ppt; ppt=ppt->next) {
		if ((newPref.pref_len == ppt->pref_addr.pref_len) &&
		    !bcmp(newPref.addr, ppt->pref_addr.addr, (newPref.pref_len+1) >> 1)) break;
	}
	if (ppt) {
		/* this is an existing prefix */
		if (prefType == ISIS_INTERNAL) metric = parsedMetric & 0x3f;
		else metric = parsedMetric | 0x40;
		if (ppt->metric.defalt != metric) {
			ppt->oldMetric = ppt->metric;
			ppt->metric.defalt = metric;
			ppt->changed = 1;
			trace_tf(isis_trace_options,
				 TR_NORMAL,
				 0,
				 ("IS-IS changing metric for prefix %s to [%s,%d]",
				  pstr,
				  (prefType == ISIS_INTERNAL) ? "internal" : "external",
				  parsedMetric));
		}
	} else {
		/* this is a new prefix */
		ppt = castMalloc(struct isis_pref *, sizeof(struct isis_pref));
		ppt->new = 1;
		ppt->pref_addr.pref_len = str_to_hex(pstr,ppt->pref_addr.addr,sizeof(ppt->pref_addr.addr));
		ppt->metric = noMetric;
		if (prefType == ISIS_INTERNAL) ppt->metric.defalt = parsedMetric & 0x3f;
		else ppt->metric.defalt = parsedMetric | 0x40;
		ppt->next = prefixList;
		prefixList = ppt;
	}
}
	

char dummyArea[] = { 4,'f','f','f','f'};
/* 
 * Set the area addresses from those saved during parse.
 */
void
isis_set_areas()
{
	u_char  abuf[200];
	int i;
	int alen;
	int a_strlen;
	struct is_pc *iscpt;
	if_addr	*ifap = NULL;
	char scratch[ISO_MAXADDRLEN*2];

	for (i=1; i <= isis_circuits_parsed; i++) {
#ifdef notdef
/* XXX - hack from INRIA */
		if ((i == 1) && (isis_num_areas >= 1)) {
			/* already set */
			break;
		}
#endif
		iscpt = &isis_ca[i];
		IF_ADDR(ifap) {
			if (BIT_TEST(ifap->ifa_state, IFS_UP)
			    && (!strcasecmp(iscpt->name, ifap->ifa_link->ifl_name)) && (socktype(ifap->ifa_addr) == AF_ISO)) break;
		} IF_ADDR_END(ifap);
		if (ifap) {
			sprintf(scratch, "%A", ifap->ifa_net);
			isis_saveArea(scratch);
		}
	}

	for (i=0; i<isis_num_areas; i++) {
		a_strlen = strlen(isis_areas[i])/2;
		alen = str_to_hex(isis_areas[i], &abuf[1], a_strlen);
		if (alen > MaximumAreaAddressLen*2) {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("area address %s too long: %d",
				      isis_areas[i],
				      a_strlen));
			continue;
		}
		/* str_to_hex returns number of hex digits, so round up and divide by 2 to get number of bytes */
		alen = (alen + 1) >> 1;
		abuf[0] = alen;
		setAreaAddr(abuf);
	}
	if (!isis_num_areas) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("Invalid IS-IS configuration: no area address specified - quitting"));
		isisDie();
		/* setAreaAddr(dummyArea); */
	}
}

/*
 * Called by parser to find existing circuits.
 */
int
isis_GetIspcByName __PF1(name, char *)
{
	int i;

	for (i=1; i<=isis_circuits_parsed; i++) {
		if (!strcmp(name, isis_ca[i].name)) {
			if (isis_ca[i].mode == REALD) useRealNet = 1;
			return(i);
		}
	}
	return(0);
}

/* initialize the is_pc entry for the circuit identified */
void
isis_init_ca __PF2(pcptr, struct is_pc *,
		   sysIDonly, int)
{
	if_addr	*ifap = NULL;
	if_addr	*ifap_inet = NULL;
	if_addr	*ifap_iso = NULL;
	char tmp[20];
CircuitEntry *c;
int i;

#if	(defined(AF_LINK) && ((_BSD > 43) || (BSD > 43)))
	/* look for a data link interface with this name */
	IF_ADDR(ifap) {
		/* 
		 * STEVE XXX - why did I make this AF_ISO and not AF_LINK?
		 * Because if you ain't running ISO, you ain't running IS-IS.
		 */
		if (BIT_TEST(ifap->ifa_state, IFS_UP)
		    && !strcasecmp(pcptr->name, ifap->ifa_link->ifl_name)) {
			if (socktype(ifap->ifa_addr) == AF_ISO) 
				ifap_iso = ifap;
			else if (socktype(ifap->ifa_addr) == AF_INET) 
				ifap_inet = ifap;
		}
	} IF_ADDR_END(ifap);
#endif	/* AF_LINK */

	if (ifap_iso) {
		if (sysIDonly && !sysIDisset) {
			int sysidlen;
			sockaddr_un *sysid;
			/* STEVE XXX - gated hasn't yet determined the ifa_systemid:  bring on the grunge */
/*
			if (ifap_iso->ifa_netmask && (socksize(ifap_iso->ifa_addr) - socksize(ifap_iso->ifa_netmask)) > 0) {
				sysidlen = socksize(ifap_iso->ifa_addr) - socksize(ifap_iso->ifa_net) - 1;
				bcopy((byte *) ifap_iso->ifa_addr + socksize(ifap_iso->ifa_net), tmp, sysidlen);
				isis_set_sysid(tmp, sysidlen);
			} 
*/
			sysid = ifap_iso->ifa_systemid->ifae_addr;
			sysidlen = sysid->ll.gll_len - sizeof(sysid->ll) + 1;
			bcopy(sysid->ll.gll_addr, tmp, sysidlen);
			isis_set_sysid(tmp, sysidlen);
			return;
		}
		pcptr->index = ifap_iso->ifa_link->ifl_index;
		if (BIT_TEST(ifap_iso->ifa_state, IFS_POINTOPOINT)) {
			pcptr->is_ptp = 1;
			pcptr->snpa = (sockaddr_un *) 0;
			trace_tf(isis_trace_options,
				 TR_NORMAL,
				 0,
				 ("configuring %s: point to point",
				  pcptr->name));
		} else {
			/* it's broadcast, so get SNPA */
			pcptr->snpa = ifap_iso->ifa_link->ifl_addr;
			trace_tf(isis_trace_options,
				 TR_NORMAL,
				 0,
				 ("configuring %s: %A",
				  pcptr->name,
				  pcptr->snpa));
		}
		pcptr->mode = REALD;
		useRealNet = 1;
		/* indicate that IS-IS is running over this interface */
		BIT_SET(ifap_iso->ifa_rtactive, RTPROTO_BIT(RTPROTO_ISIS));
		if (ip_supported && ifap_inet) BIT_SET(ifap_inet->ifa_rtactive, RTPROTO_BIT(RTPROTO_ISIS));
		return;
	} else {
		if (!strncasecmp(pcptr->name, "sim", 3)) {
			trace_tf(isis_trace_options,
				 TR_NORMAL,
				 0,
				 ("configuring %s: simulated",
				  pcptr->name));
			pcptr->index = atoi(pcptr->name+3);
			pcptr->mode = TROLLD;
			useSim = 1;
			return;
		}
	}
	if (!run_from_log) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("isis_init_ca: unrecognized interface name %s",
			      pcptr->name));
		isisDie();
	}
}

/* 
 * Initialize system id from a string from the parser.  
 */
void
isis_set_sysid __PF2(str, char *,
		     len, int)
{
    /*
    strncpy((caddr_t) systemID, str, sizeof(systemID));
    */
	if (!sysIDisset) {
		if (!len) str_to_hex(str, systemID, sizeof(systemID));
		else bcopy(str, systemID, len);
		sysIDisset = 1;
	}
}

void
isis_save_trace __PF1(tracebits, flag_t)
{
	static int MorrisTitanic = 0;
	const char *WaltFrazier;

	WaltFrazier = (MorrisTitanic ? "changing" : "setting");
	MorrisTitanic = 1;
	if (debugLog.flags != (int) tracebits) {
		debugLog.flags = (int) tracebits;
		trace_tf(isis_trace_options,
			 TR_NORMAL,
			 0,
			 ("%s IS-IS trace bits to %x",
			  WaltFrazier,
			  tracebits));
	}
}

/* 
 * Open the input log file and return its file descriptor.
 */
int
get_input_log_fd()
{
	int ret_fd;

	if ((ret_fd = open("input_log",O_RDONLY,0)) < 0) {
		perror("input log open");
	}
	read(ret_fd,&time_sec,sizeof(time_sec));
	printf("simulation run start time %d:%s\n",time_sec,ctime(&time_sec));

	return ret_fd;
}

/* 
 * The once-per-second isis timer, run out of the gated timer system,
 * which in turn drives all internal is-is timers.  This is also used
 * to rerun is-is out of the input log if so desired.
 */
void
isis_timef __PF2(tip, task_timer *,
		 interval, time_t)
{

	isis_time++; 					/* increment time */
	isis_task =  tip->task_timer_task;
	if (run_from_log) time_sec = isis_time;		/* use isis_time for the global time */
	feepTimer(); 					/* check for isis events */

	if (run_from_log) {
		/* check if there is input to process */
		while (1) {
			struct log_header log_buf;
			int rc;

			if (!input_fd) input_fd = get_input_log_fd();
			rc = read(input_fd,&log_buf,sizeof(log_buf));
			if (rc == sizeof(log_buf)) {
				if (log_buf.io_time <= isis_time)
					process_log_input(&log_buf);
				else {
					/* no more input ready; reset the file and return */
					/* XXX - fix this shit */
					lseek(input_fd,-sizeof(log_buf),L_INCR);
					break;
				}
			} else if (rc < 0) {
				perror("log file input");
				exit(1);
			} else if (rc == 0) {
				/* input log is exhausted. We used to just exit here, but 
					a bug came up later, so now we run simulated time for a while. */
				static int countdown = 0;
				if (countdown == 0) {
					printf("input log file exhausted, simulated time %d\n",isis_time);
					countdown++;
					return;
				}
				countdown++;
				if (countdown > 30) {
					/* used to exit; try return */
					run_from_log = 2;
					return;
					printf("exiting gated at simulated time %d \n",isis_time);
					/* exit(0); */
				} else
					return;
			} else
				break; /* bad size?? */
		}
	}
}

/* 
 * Initialize ISIS variables to default state (assuming not running).
 * This baby is called before parse; it's called just after cleanup
 * on reconfigs.
 */
void
isis_var_init()
{
	debugLog.flags = 0;		/* disable tracing */
	isis_plevel = 0;		/* level 1 or 2 */
	isis_preference[1] = RTPREF_ISIS_L1;	/* we use gated to prefer L1 routes over L2 routes */
	isis_preference[2] = RTPREF_ISIS_L2;
	isis_default_metric = ISIS_METRIC_DEFAULT;
	isis_test_krt = 1; 		/* enable test interface */
	isis_log_input = 0;
	isis_input_cnt = 0; 		/* sequence # for logging */
	isis_log_fd = 0;
	isis_log_output = 0;
	isis_output_cnt = 0; 		/* sequence # for logging */
	isis_out_fd = 0;
	isis_time = 0; 			/* simulated time */
	isis_packet_id = 0; 		/* input packet # for logging */
	run_from_log = 0; 		/* if 1, read input log */
	input_fd = 0; 			/* if run_from_log, fd we are reading from */
	useSim = 0;			/* if we should enable the troll sockets */
	useRealNet = 0;			/* if we should enable the real network sockets */
	isis_num_areas = 0;		/* number of area addresses we have (set in parse) */
	initAreaAddrs();		/* clear them out */
	isis_ci = 0; 			/* circuit index - used in parser */
	if (isis_initial_config) {
		/* this is an initial config of this instance */
		isis_circuits_parsed = 0; 			/* total circuits parsed */
		bzero((caddr_t) ifIndexToCircuit, MAXLOCALID);	/* kernel index -> circuit mapping */
		bzero((caddr_t) simIdToCircuit, MAXLOCALID);	/* simulated subnet id -> circuit mapping */
		bzero((caddr_t) circuitList, MaximumCircuits*sizeof(CircuitEntry *));
	}
	doing_isis = FALSE;
}
		
/*
 *	Initialize ISIS.  This could be part of a reconfig as well.
 *
 *	We create up to 3 tasks in this function.
 *		isisUtil task - always created. Handles timers
 *		isisReal task - optionally created to handle real network events
 *		isisSim task - optionally created to handle simulated events
 */
void
isis_init()
{
	int i;
	struct isis_ipr *ipt;
	struct isis_pref *ppt;
	InterDomInfo *p;
	struct isis_ann *ia;

	/*
	 * Initialization call sequence:
	 * isis_cleanup (only on reconfig)
	 * isis_var_init
	 * parse
	 * isis_init
	 * isis_reinit
	 * isis_flash
	 * isis_newpolicy
	 */

	if (!doing_isis) {
		if (isisUtilTask) {
		        ISIS_ANN(ia) {
			        rtbit_reset(ia->rt, isis_rtbit); 
				REMQUE(ia);
 				task_block_free(isis_ann_block, (void_t) ia);
 			} ISIS_ANN_END(ia);
 			isisCounters.isis_announced = 0;

			if (isis_timer)
				task_timer_delete(isis_timer);
#ifdef	SPF_TIMER
			task_timer_delete(spf_timer);
#endif	/* SPF_TIMER */
			task_timer_delete(csnp_timer);
			task_timer_delete(psnp_timer);
			task_timer_delete(flood_p2p_timer);
			task_timer_delete(flood_broadcast_timer);
			task_delete(isisUtilTask);
			isisUtilTask = (task *) 0;
		}
		if (isisRealTask) {
			task_delete(isisRealTask);
			isisRealTask = (task *) 0;
		}
		if (isisSimTask) {
			task_delete(isisSimTask);
			isisSimTask = (task *) 0;
		}
#ifdef	PROTO_SNMP
		isis_init_mib(FALSE);		/* unregister IS-IS mib subtree with SNMP */
#endif	/* PROTO_SNMP */

		isis_initial_config = 1;	/* next time it will be a start from scratch */
		sysIDisset = 0;
		trace_tf(isis_trace_options,
			 TR_NORMAL,
			 0,
			 ("IS-IS disabled"));
		return;
	}

	/* turn our kernel into an ISH-sending monster */
	switchToIS();

	trace_inherit_global(isis_trace_options, isis_trace_types, (flag_t) 0);
	
	/* create utility task */
	if (!isisUtilTask) {
		isisUtilTask = task_alloc("Tyrone Shoelaces",
					  TASKPRI_PROTO,
					  isis_trace_options);
		task_set_cleanup(isisUtilTask, isis_cleanup);
		task_set_dump(isisUtilTask, isis_dump);
		task_set_recv(isisUtilTask, NULL);
		task_set_reinit(isisUtilTask, isis_reinit);
		task_set_flash(isisUtilTask, isis_flash);
		task_set_newpolicy(isisUtilTask, isis_newpolicy);
		isisUtilTask->task_rtproto = RTPROTO_ISIS;
		isis_rtbit = isisUtilTask->task_rtbit = rtbit_alloc(isisUtilTask,
								    FALSE,
								    ISIS_TSI_SIZE, 
								    (void_t) isisUtilTask,
								    isis_tsi_dump);
		if (!isis_tsi_info_block) 
			isis_tsi_info_block = task_block_init(sizeof(struct isis_tsi_info), "isis_tsi_info");
		if (!isis_ann_block)
			isis_ann_block = task_block_init(sizeof(struct isis_ann), "isis_ann");
		if (!task_create(isisUtilTask))
			task_quit(EINVAL);
		task_alloc_recv(isisUtilTask, MaxPacketSize);
		if (run_from_log) {
			/* need a dummy timer structure */
			isis_timer = (task_timer *) task_mem_malloc(isisUtilTask, sizeof(task_timer));
			isis_timer->task_timer_task = isisUtilTask;
		}
		else {
			/* set a real timer */
			isis_timer = task_timer_create(isisUtilTask,
						       "timerO'9Tails  ",
						       (flag_t) 0, 
						       (time_t) 1, /* interval */
						       (time_t) 0, /* offset */
						       isis_timef, /* job */
						       (void_t) 0 /* data */
						       );
			/* task_timer_set(isis_timer,(time_t)1, (time_t)0); */
		}
#ifdef SPF_TIMER
		spf_timer = task_timer_create(isisUtilTask,
					      "spf            ",
					      (flag_t) 0, 
					      (time_t) 5,
					      (time_t) 0,
					      isisCheckSPF,
					      (void_t) 0);
#endif
		isis_task = isisUtilTask;
		initOldAdjacencies();		/* initialize old adjacency delete list */
#ifdef 	PROTO_SNMP
		isis_init_mib(TRUE);		/* register IS-IS mib subtree with SNMP */
		initIsisMibCold();		/* clear all IS-IS mib variables */
        	initIsisMibCool();		/* set IS-IS mib variables for this IS-IS protocol instance */
#endif  /* PROTO_SNMP */
	}

	/* set up RX sockets */
	if (!isisRealTask) {
		isisRealTask = task_alloc("IS-IS pdu",
					  TASKPRI_PROTO,
					  isis_trace_options);
		task_set_recv(isisRealTask, isisRealRecv);
		if (!run_from_log) {
			/* listen to ESIS traffic */
			ReceiveSock(isisRealTask); 
		}
		if (!task_create(isisRealTask))
			task_quit(EINVAL);
		task_alloc_recv(isisRealTask, MaxPacketSize);
	}

	if (!isisSimTask && useSim) {
		isisSimTask = task_alloc("IS-IS simulator",
					 TASKPRI_PROTO,
					 isis_trace_options);
		task_set_recv(isisSimTask, isisSimRecv);
		if (!run_from_log)
			isisSimTask->task_socket = trollReceiveSock();
		if (!task_create(isisSimTask))
			task_quit(EINVAL);
		task_alloc_recv(isisSimTask, MaxPacketSize);
	}

	/* store our knownAAs from the parse */
	isis_set_areas();
		
	/* allow the following changes only during initial config (STEVE - for now) */
	if (isis_initial_config) {
		if (!run_from_log && !isis_log_input) {
			isis_time = time_sec;
		} else {
			/* set time from the input log */
			input_fd = get_input_log_fd();
			isis_time = time_sec;
		}
		/* set systemType from parser flag */
		systemType = (isis_plevel == 2) ? L2IS : L1IS;

		/* set fake mac address if necessary */
		if (!isis_snpa) isis_snpa = getpid();
		sprintf((char *) myMAC, "%d", isis_snpa);
		isis_spf_init();
		initTimers();
	} else {
		/* remove gunk associated with no-longer-configured stuff */
	}

	/* these things have to be in this order (big big grunge) */
	for (i=1; (i<=isis_circuits_parsed) && !sysIDisset; i++) {
		/* try to set the system ID */
		isis_init_ca(&isis_ca[i], 1);
	}
	if (!sysIDisset) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("IS-IS - no system ID found in config or in interface NSAPs"));
		isisDie();
	}
	initGlobals(isis_initial_config);
	for (i=1; i <= isis_circuits_parsed; i++) {
		trace_tf(isis_trace_options,
			 TR_NORMAL,
			 0,
			 ("checking circuit %s",
			  isis_ca[i].name));
		isis_set_circuit(&isis_ca[i]);
	}
	if (isis_initial_config) {
		csnp_timer = task_timer_create(isisUtilTask,
					       "csnp           ",
					       (flag_t) 0, 
					       (time_t) completeSNPInterval,
					       (time_t) 0,
					       generateCSNP,
					       (void_t) 0);
		psnp_timer = task_timer_create(isisUtilTask,
					       "psnp           ",
					       (flag_t) 0, 
					       (time_t) partialSNPInterval,
					       (time_t) 0,
					       generatePSNP,
					       (void_t) 0);
		flood_p2p_timer = task_timer_create(isisUtilTask,
						    "flood_p2p      ",
						    (flag_t) 0, 
						    (time_t) minLSPXmitInterval,
						    (time_t) 0,
						    floodPt2Pt,
						    (void_t) 0);
		flood_broadcast_timer = task_timer_create(isisUtilTask,
							  "flood_broadcast",
							  (flag_t) 0, 
							  (time_t) minBLSPXmitInterval,
							  (time_t) 0,
							  floodBroadcast,
							  (void_t) 0);
	}

	/* initialize ip reachables, ignore summary addresses which get updated later */
	for (ipt=IPRList; ipt; ipt = ipt->next) 
		if (ipt->type != IPSumReachCode) {
			ipt->p = setIPReachable(ipt->level, ipt->type, ipt->metric, ipt->addr, ipt->mask, (as_path *) 0);
		}

        /* set any inter-domain info */
	for (p=interDomInfoList; p; p=p->next) 
		addInterDomInfo(L2LSP, p->data, p->len);

	if (run_from_log) {
		while (run_from_log == 1) {
			/* run until input log is exhausted */
			isis_timef(isis_timer,0);
		}
		/* continue with timer after input log is exhausted */
		isis_timer = task_timer_create(isisUtilTask,
					       "agelist",
					       (flag_t) 0,
					       1,
					       (time_t) 0, /* offset */
					       isis_timef,
					       (caddr_t) 0 );
		/* task_timer_set(isis_timer,(time_t)1, (time_t)0); */
	}

#ifdef	PROTO_SNMP
	initIsisMibWarm(isis_initial_config);			/* Isis-Mib */
#endif 	/* PROTO_SNMP */

}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
