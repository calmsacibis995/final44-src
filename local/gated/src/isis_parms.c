/*
 *  isis_parms.c,v 1.11 1993/01/07 22:39:47 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"


struct parm_set {
	char * parm_addr;
	const char * parm_name;
	int parm_size;
	int set_val;
	int low_val;
	int high_val;
};

#define PARMS(n,lb,ub) { (char *)&n, "n" ,sizeof(n),0,lb,ub }
struct parm_set parm_def [] =
{
PARMS(dataLinkBlocksize,200,4096), 
/* this is receiveLSPBufferSize, max is dubious */
/* note that this must come before the following */
PARMS(origL1LSPBufSize,200,4096), 
PARMS(origL2LSPBufSize,200,4096), 
PARMS(sysHoldingTimer,1,65535),
PARMS(sysISHInterval,5,30),
PARMS(origL1LSPBufSize,1,10000),
PARMS(origL2LSPBufSize,1,10000),
PARMS(dataLinkBlocksize,1,10000),
PARMS(sysHoldingTimer,1,10000),
PARMS(sysISHInterval,1,10000),
PARMS(sysIIHInterval,1,10000),
PARMS(minLSPGenInterval,1,10000),
PARMS(maxLSPGenInterval,1,10000),
PARMS(minBLSPXmitInterval,1,10000),
PARMS(minLSPXmitInterval,1,10000),
PARMS(BLSPThrottle,1,10000),
PARMS(maximumAge,1,10000),
PARMS(completeSNPInterval,1,10000),
PARMS(partialSNPInterval,1,10000),
PARMS(zeroAgeLifetime,1,10000),
{0,0,0,0,0}} ;

void
isis_set_parm(str,val)
char * str; int val;
/* sleazy linear table lookup */
{
	int i;
	for (i=0; i<sizeof(parm_def)/sizeof(struct parm_set); i++) {
		struct parm_set *
		ppt = &parm_def[i];
		if (!ppt->parm_name) break;
		if (!strncmp(str, ppt->parm_name,strlen(ppt->parm_name)))
		/* note: we should do something a little more sophisticated here */
		/* we use strncmp to avoid figuring out the length of str, which
			is just a pointer into the parser text stream and isn't null
			terminated. Yuck. */
		{
			trace_tf(isis_trace_options,
				 TR_NORMAL,
				 0,
				 ("setting parm %s val %d\n",
				  str,
				  val));
			if ((val< ppt->low_val) || (ppt->high_val < val)) {
				trace_tf(isis_trace_options,
					 TR_NORMAL,
					 0,
					 ("value for %s : %d out of range (%d,%d)\n",
					  ppt->parm_name,
					  val,ppt->low_val,
					  ppt->high_val));
				return;
			}
			ppt->set_val = val;
			return;
		}
	}
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("parameter %s not found\n",
		      str));
}


/* 
 * Check if any parms have been reset in config file.
 */
void
isis_check_parms()
{
	int i;
	struct parm_set *ppt;

	for (i=0; i<sizeof(parm_def)/sizeof(struct parm_set); i++) {
		ppt = &parm_def[i];
		if (ppt->set_val) {
			trace_tf(isis_trace_options,
				 TR_NORMAL,
				 0,
				 ("setting parm %s val %d",
				  ppt->parm_name,
				  ppt->set_val));
			switch(ppt->parm_size) {
			case sizeof(char): 
				*(char *)ppt->parm_addr = ppt->set_val;
				break;
			case sizeof(short): 
				*(short *)ppt->parm_addr = ppt->set_val;
				break;
			case sizeof(long): 
				*(long *)ppt->parm_addr = ppt->set_val;
				break;
#ifdef	FLOATING_POINT
			case sizeof(double): 
				*(double *)ppt->parm_addr = ppt->set_val;
				break;
#endif	/* FLOATING_POINT */
			default:
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_ERR,
					     ("unexpected parm size %d",
					      ppt->parm_size));
			}
		}
	}
}



/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
