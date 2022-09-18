/*
 *  isis_test.h,v 1.11 1993/01/07 22:40:04 jch Exp
 */

/* %(Copyright.header) */


#define ISIS_METRIC_DEFAULT 8	/* ??? */
#define MAX_IS_PCTS 20
extern int doing_isis;			/* Are we running ISIS protocols? */
extern metric_t isis_default_metric;	/* default ISIS metric */
extern void isis_init();
extern int isis_ci;			/* index for parsed circuits */
extern int isis_circuits_parsed;	/* total number of parsed circuits */
extern int isis_nodeid; /* socket identifier for simulation connection */
extern int isis_plevel; /* level variable set in parser */
extern int isis_snpa; /* fake nsap, netd requires an integer somewhere. */
extern struct is_pc {
	int configured;		/* 1 if circuit is already configured */
	char name[10];		/* name, ie qe0 */
	int index;		/* kernel index or simulator interface number */
	int mode;		/* REALD or TROLLD */
	int metric;
	int l2metric;
	int prior;
	int l2prior;
	int is_ptp;
	sockaddr_un *snpa;	
	sockaddr_un	ipaddr;		/* ip addr associated with circuit */
	char		ipaddrSet;	/* true if above ipaddr has been set */
}	isis_ca[MAX_IS_PCTS];


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
