/*
 *  isis_lsp.c,v 1.11 1993/01/07 22:39:31 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"

#ifdef	PROTO_SNMP
#include "isis_mib.h"				/* Isis-Mib */
#endif

#define firstLSPdesc(grp)\
	DLListForw((&grp->list), LSPDesc *)

#define lastLSPdesc(grp)\
	DLListBack((&grp->list), LSPDesc *)

#define nextLSPdesc(grp, cur)\
	DLListNext(cur, &grp->list, LSPDesc *)

#define firstOption(desc)\
	DLListNext(&desc->options, &desc->options, LSPOption *)

#define lastOption(desc)\
	DLListPrev(&(desc->options), &(desc->options), LSPOption *)

#define hasOptions(desc)\
	(!DLListEmpty(&desc->options))

extern MetricList noMetric;             /* all unsupported metric */

static block_t isis_lspoption_block;
static block_t isis_optiondata_block;
static block_t isis_prefIP_block;
static block_t isis_prefISO_block;
static block_t isis_lspattr_block;
static block_t isis_lspdesc_block;
extern block_t isis_lsentry_block;
extern block_t isis_lseChangeList_block;
extern block_t isis_lspbuf_block[];

struct searchkey {
	as_path *path;
	MetricList *metrics;
};

PROTOTYPE(addToLSP, static void, (LSPGroup *, LSPDesc *, LSPOption *)); 
PROTOTYPE(rmESNeighbor, static void, (AdjacencyEntry *, LSPOptPtr)); 
PROTOTYPE(rmISNeighbor, static void, (LSPOptPtr)); 
PROTOTYPE(rmPrefNeighbor, static void, (prefISO *)); 


/*
 *	TODO: add NLPID, IP interface addrs, IP reachability info
 *	to the LSPs
 */

/*
 *	Certain DUAL options are placed into every LSP. In order to avoid
 *	duplicating the same LSPOption in each LSPDesc, a special list
 *	'globalOptions' is maintained. Options present in this list are
 *	always added to the number zero LSP. Options in this list are not
 *	contained in an LSPDesc structure.
 */
DLList	globalOptions;

/*
 *	LSP Generation: The general idea is to build the non-pseudonode LSPs and
 *	pseudonode LSPs for each broadcast circuit, regardless of whether
 *	this system is actually *the* designated router on the circuit. If
 *	the status changes and the router becomes designated, the pseudonode
 *	LSPs will be already built and ready to transmit.
 */

static MetricList zeroMetric = { 0x00, 0x80, 0x80, 0x80 };

/*
 *	This structure contains the summary of area addresses seen in the
 *	area (it is only used if we are a L2 router). 'optPtr' identifies
 *	the option that contains the summary of area addrs.
 */
static struct {
	LSPOptPtr		optPtr;		/* option that contains the L2 area addrs */
	AreaAddrList	summaryList;
} l2AreaSummary;

/*
 *	1) Initialize an area address summary to my area addrs.
 *	2) scan the L2 LSP database and add to that summary any new area addr
 *	3) if this list is different than the l2AreaSummary, regenerate my
 *		L2 LSP
 */
void
updateAreaSummary()
{
	AreaAddrList	aal, parseLSPAreaAddrList(), mergeAreaAddrList();
	LSEntry			*ent = firstLSP(1);

	assert(systemType == L2IS);

	if (l2AreaSummary.optPtr.opt == NULL)
		return; /* We are still initializing */

	bcopy((caddr_t) &systemAreaAddrs, (caddr_t) &aal, sizeof(AreaAddrList));

	/* scan LSP database */
	for (;ent; ent = ent->sortNext) {
		if (ent->signature.id.LSPNumber == 0) {
			/* parse area addr option */
			aal = mergeAreaAddrList(
				parseLSPAreaAddrList(ent->buf, ent->len), aal);
		}
	}

	if (bcmp(&aal, &l2AreaSummary.summaryList, sizeof(AreaAddrList))) {
		updateAreaAddrs(&aal, l2AreaSummary.optPtr.opt);
		bcopy((caddr_t) &aal,
		      (caddr_t) &l2AreaSummary.summaryList, 
		      sizeof(AreaAddrList));
	}
}

void
dumpLSPOption(opt)
LSPOption	 *opt;
{
	trace_only_tf(isis_trace_options,
		      0,
		      ("\tOption x%x: key %d, type %d, len %d",
		       opt,
		       opt->key,
		       opt->type,
		       opt->len));
}

void
dumpLSPDesc(desc, msg)
LSPDesc	*desc;
char	*msg;
{
	LSPOption	 *opt;
	tracef("%s", msg);
	if (desc->lspEntry) {
		trace_tf(isis_trace_options,
			 TR_NORMAL,
			 0,
			 ("%s",
			  LSSigToStr(&desc->lspEntry->signature)));
                IFTRACE(T_LSPCONTENT)
                        printLSPContents(0, desc->lspEntry->buf, desc->lspEntry->len);
                ENDTRACE
	} else
		trace_tf(isis_trace_options,
			 TR_NORMAL,
			 0,
			 (NULL));
#define VERBOSE
#ifdef	VERBOSE
	/* try to figure out which LSPDesc this is */
	if (desc->group == L1LSP)
		tracef("L1 LSP");
	else if (desc->group == L2LSP)
		tracef("L2 LSP");
	else {
		int i;
		CircuitEntry	*c;
		for (i=0; i<MaximumCircuits; i++)
			if (c = circuitList[i]) {
				if (c->l1PLSP == desc->group) {
					tracef("%s L1 PLSP", c->name);
					break;
				} else if (c->l2PLSP == desc->group) {
					tracef("%s L2 PLSP", c->name);
					break;
				}
			}
	} 

	trace_tf(isis_trace_options,
		 TR_NORMAL,
		 0,
		 (" #%d, type %d, spaceLeft %d",
		  desc->lspNumber,
		  desc->lspType, 
		  desc->spaceLeft));

	IterateDLListForw(opt, &desc->options, LSPOption *) {
		dumpLSPOption(opt);
	}
#endif	/* VERBOSE */
}

void
dumpLSPGroup(grp)
LSPGroup	*grp;
{
	LSPDesc	*desc;
	trace_tf(isis_trace_options,
		 TR_NORMAL,
		 0,
		 ("Group x%x",
		  grp));
	IterateDLListForw(desc, &grp->list, LSPDesc *) {
		dumpLSPDesc(desc, "");
	}
}

/* append a zero octet to the 6 byte id */
#ifdef ibm032	/* PC/RT */
SystemID7 *
_appendZero(id)
SystemID6	id;
{
	static SystemID7	id7;

	bzero(id7, sizeof(id7));
	copyID(id, id7, 6);
	return(&id7);
}
#define appendZero(id) ((SystemID7) _appendZero(id))
#else
u_char *
appendZero(id)
SystemID6	id;
{
	static SystemID7	id7;

	/* STEVE XXX - why does this sometimes blow chunks? */

	bzero((caddr_t) id7, sizeof(id7));
	copyID(id, id7, 6);
	return(id7);
}
#endif

/*
 *	Return a pointer to the first option found in the
 *	LSP group that is of type 'type', where both the option
 *	and the LSP it is contained within have at least minSpace
 *	remaining and where the auxCheck (if defined) returns
 *	true. Return NULL if no such option exists in the group.
 */
static LSPOption * 
findOption(grp, type, minSpace, auxCheck, auxData)
LSPGroup	*grp;		/* "logical" LSP to search through */
u_char		type;		/* type of option to search for */
int		minSpace;	/* must be avail in both option and LSP */
PTIF		auxCheck;	/* optional comparison routine */
u_char		*auxData;	/* optional data for comparison routine */
{
	LSPDesc	*desc;

	/*
	 *	Search through each individual LSP's list of options
	 *	to locate the first option of a particular type.
	 */
	IterateDLListForw(desc, &grp->list, LSPDesc *) {
		LSPOption	*opt;
		IterateDLListForw(opt, &desc->options, LSPOption *) {
			if ((opt->type == type) &&
				(LSPOptionUnused(opt) > minSpace) &&
				(desc->spaceLeft > minSpace)) {
				if ((auxCheck) && (!(auxCheck)(opt, auxData)))
					continue;
				return(opt);
			}
		}
	}
	return(NULL);
}

/* 
 * Hints about new prefix placement.  The attribute option is
 * needed so its prefix option refcount can be bumped.  When
 * the last prefix option in an LSP is deleted we must delete
 * the corresponding attribute option.  STEVE XXX - we can waste
 * space and leave it around, hopefully reusing it later.
 */
struct _prefixHints {
	LSPOption *prefOpt;	/* a full option which shares the same attributes as the new prefix 
				 * and whose LSP has space for a new prefix option */
	LSPOption *attrOpt;	/* an attribute option which applies for the new prefix (already encoded in an LSP) */
	LSPDesc *availLSP;	/* any LSP with space for new attribute and prefix options (used if no prefOpt) */
};

/*
 *	Same as above, but if we find an option without space which
 *      matches, remember its LSPDesc so that I am able to create a 
 *      new option in the same LSP segment.  Returns an option if one
 * 	with the same attributes (checked in auxCheck) exists and has
 * 	space.  If such an option does not exist, it returns NULL; in
 * 	this case, if a similar full option exists but its 
 * 	LSPDesc has enough space to create a following prefix neighbor
 *	option, lastOption points to that full option.
 */
static LSPOption * 
findPrefixOption(grp, type, minSpace, auxCheck, auxData, fullOpt, pathSpace, availLSP)
LSPGroup	*grp;		/* "logical" LSP to search through */
u_char		type;		/* type of option to search for */
int		minSpace;	/* must be avail in both option and LSP */
PTIF		auxCheck;	/* optional comparison routine */
u_char		*auxData;	/* optional data for comparison routine */
LSPOption	**fullOpt;	/* previous (full) option, if any */
int		pathSpace;	/* extra needed if must add path attributes too */
LSPDesc		**availLSP;	/* an LSP with space for path attributes and prefix options */
{
	LSPDesc	*desc;

	*availLSP = (LSPDesc *) NULL;
	*fullOpt = (LSPOption *) NULL;

	/*
	 *	Search through each individual LSP's list of options
	 *	to locate the first option of a particular type.
	 */
	IterateDLListForw(desc, &grp->list, LSPDesc *) {
		LSPOption	*opt;
		IterateDLListForw(opt, &desc->options, LSPOption *) {
			if ((opt->type == type) && auxCheck && ((auxCheck)(opt, auxData))) {
				/* this is a similar prefix option */
				if ((LSPOptionUnused(opt) > minSpace) && (desc->spaceLeft > minSpace)) {
					/* and space is available */
					return(opt);
				} else if (desc->spaceLeft > (minSpace+2)) {
					/* no space in this option but space is available in this LSP for a new option */
					*fullOpt = opt;
				} 
			} 
		}
		if (*availLSP && hasOptions((*availLSP))) 
			opt = lastOption((*availLSP));
		else 
			opt = (LSPOption *) 0;
		if (!(*fullOpt) && (!(*availLSP) || (opt && (opt->type != leafNode)))) {
			/* 
			 * No candidates in this LSP, so check if we could stick 
			 * a pair of options (idrpi, prefix) into this LSP.  We prefer
			 * to stick this pair in an empty LSP (or if not empty, in an
			 * LSP with a leftover leafNode option).
			 */
			if (hasOptions(desc)) {
				opt = lastOption(desc);
				if ((opt->key == LSPhigh) && (desc->spaceLeft > (minSpace+pathSpace+4))) {
					*availLSP = desc;
				}
			} else if (desc->lspNumber == 255) {
				/* no options and the last LSP */
				*availLSP = desc;
			} else {
				/* no options and not the last LSP */
				/* 
				 * STEVE XXX - we make the huge mistaken assumption that this LSP
				 * formerly held prefixes - if it's empty but precedes a LSP with LSPlow
				 * options, we're hosed bigtime.  I have to use a loop to check all of the
				 * following LSPs until I find one with LSPhigh options.
				 */
				*availLSP = desc;
			}
		}
	}
	return(NULL);
}

/*
 *	Add opt to the beginning of the list of options in desc
 */
void
addAsFirst(desc, opt)
LSPDesc		*desc;
LSPOption	*opt;
{
	desc->spaceLeft -= LSPOptionSize(opt);
	DLLInsque(opt, &desc->options);
	opt->lspDesc = desc;
}

/*
 *	Add opt to the end of the list of options in desc
 */
void
addAsLast __PF2(desc, LSPDesc *,
		opt, LSPOption *)
{
	desc->spaceLeft -= LSPOptionSize(opt);
	DLLInsque(opt, DLListBack(&desc->options, DLList *));
	opt->lspDesc = desc;
}

/* 
 * Add an option in the middle of an LSP, after the given option.
 */
void
addAfterOpt __PF2(opt, LSPOption *,
		  prevOpt, LSPOption *)
{
	LSPDesc *availLSP = prevOpt->lspDesc;

	availLSP->spaceLeft -= LSPOptionSize(opt);
	DLLInsque(opt, prevOpt);
	opt->lspDesc = availLSP;
}

/* Unlink option from its descriptor. */
void
removeOption(opt)
LSPOption *opt;
{
	opt->lspDesc->spaceLeft += LSPOptionSize(opt);
	DLLRemque(opt);
}

/* remove option and free space */
void
removeAndFreeOption(opt)
LSPOption *opt;
{
	LSPOption *idrpi;

	removeOption(opt);

	switch(opt->type) {
	case IPExtReachCode:
	case IPIntReachCode: {
		prefIP *pref, *tmp;
		pref = (prefIP *) opt->data;
		while (pref) {
			tmp = pref->next;
			task_block_free(isis_prefIP_block, pref);
			isisCounters.prefIP--;
			pref = tmp;
		}	
		if (opt->attr) {
			if ((idrpi = opt->attr->idrpiOpt) && (--idrpi->refcount == 0)) {
				/* no more options in this LSP refer to this IDRPi option */
				removeOption(idrpi);
				task_block_free(isis_optiondata_block, idrpi->data);
				isisCounters.optiondata--;
				task_block_free(isis_lspoption_block, idrpi);
				isisCounters.option--;
                		isisCounters.idrpi--;
			}
			task_block_free(isis_lspattr_block, opt->attr);
			isisCounters.lspattr--;
		}
                if (opt->type == IPExtReachCode) isisCounters.ipext--;
                else isisCounters.ipint--;
		}
		break;
	case LSPPrefixNeighborCode: {
		prefISO *pref, *tmp;
		pref = (prefISO *) opt->data;
		while (pref) {
			tmp = pref->next;
			task_block_free(isis_prefISO_block, pref);
			isisCounters.prefISO--;
			pref = tmp;
		}	
		if (opt->attr) task_block_free(isis_lspattr_block, opt->attr);
		isisCounters.lspattr--;
                isisCounters.isopref--;
		}
		break;
	default:
		task_block_free(isis_optiondata_block, opt->data);
		isisCounters.optiondata--;
		switch (opt->type) {
		case IPInterDomInfo:
			isisCounters.idrpi--;
			break;
		case AreaAddressCode:
			isisCounters.aa--;
			break;
		case LSPISNeighborCode:
			isisCounters.isn--;
			break;
		case LSPESNeighborCode:
			isisCounters.esn--;
			break;
		case IPIfAddrCode:
			isisCounters.ipintf--;
			break;
		case ProtoSupportedCode:
			isisCounters.protosup--;
			break;
		case IPSumReachCode:
			isisCounters.ipsum--;
			break;
		case LSPPDL2ISCode:
			isisCounters.pdl2is--;
			break;
		case IPAuthInfoCode:
			isisCounters.ipauth--;
			break;
		case AuthenticationCode:
			isisCounters.auth--;
			break;
		}
	}
	task_block_free(isis_lspoption_block, opt);
	isisCounters.option--;
}

/* create a new LSP descriptor, initialize, but do not link into any list */
static LSPDesc *
newLSPDesc(type, number, grp, pseudoID)
int			type;
int			number;
LSPGroup	*grp;
u_char		pseudoID;		/* pseudonode ID */
{
	int size;
	LSPDesc	*new = (LSPDesc *) task_block_alloc(isis_lspdesc_block);

	isisCounters.lspdescs++;

	size = (type == L1LSType) ? origL1LSPBufSize : origL2LSPBufSize;
	new->lspNumber = number;
	new->seqNumber = 1;
	new->lspInitLifetime = maximumAge;
	new->lspType = type;
	new->lspPseudoID = pseudoID;
	DLLInit(&new->options);
	DLLInit(&new->paths);
	new->spaceLeft = size - sizeof(LSPHeader);
	new->pktBuf = castMalloc(u_char *, size);
	isisCounters.lspbufs++;
	isisCounters.lspbytes += size;
	new->pktSize = size;
	new->group = grp;

	/* new->lastGenerated = timeStamp;*/		/* delay initial generation until minLSPGenInterval */
	new->mustRegenerate = True;
	new->schedRegenerate = False;

	return(new);
}

/*
 *	destroy an LSP
 *
 *	if this procedure is written, note that the LSPdesc that is to be deleted
 *	could have been passed to the LSPGenerate timer. This timer must be
 *	cancelled so that it does not fire only to find that the lsp desc 
 *	structure has been deleted.
 */
void
destroyLSP(desc)
LSPDesc *desc;
{
}

/*
 *	Create a new LSP group of type specified
 *
 *	Also create 2 LSPs: number zero and number 1
 */
LSPGroup *
newLSPGroup __PF2(type, u_char,
	    	  pseudoNodeID, u_char)	/* non-zero only for Pseudonode LSPs */
{
	LSPGroup *grp = castMalloc(LSPGroup *, sizeof(LSPGroup));
	LSPDesc	*lsp0;

	grp->type = type;
	DLLInit(&grp->list);
	DLLInsque(lsp0 = newLSPDesc(type, 0, grp, pseudoNodeID), &grp->list);
	DLLInsque(newLSPDesc(type, 1, grp, pseudoNodeID), lsp0);
	return(grp);
}


/*
 *	Create a new LSP. Link it into the list under LSPGroup after cur.
 */
static LSPDesc *
newLSP(grp, cur)
LSPGroup	*grp;
LSPDesc		*cur;
{
	LSPDesc	*new = newLSPDesc(grp->type, cur->lspNumber+1, grp, cur->lspPseudoID);
	DLLInsque(new, cur);
	return(new);
}

static LSPOption *
createOption  __PF2(key, LSPOrder,
		    type, u_char)
{
	LSPOption *opt;

	opt = (LSPOption *) task_block_alloc(isis_lspoption_block);
	isisCounters.option++;
	switch(type) {
	case IPExtReachCode:
	case IPIntReachCode:
	case LSPPrefixNeighborCode:
		opt->data = (u_char *) 0;
		opt->attr = (LSPattr *) task_block_alloc(isis_lspattr_block);
		isisCounters.lspattr++;
		opt->attr->refcount = 0;
		break;
	case IPInterDomInfo:
		opt->refcount = 0;
	default:
		opt->data = (u_char *) task_block_alloc(isis_optiondata_block);
		isisCounters.optiondata++;
		opt->attr = (LSPattr *) 0;
	}
	opt->key = key;
	opt->type = type;
	opt->len = 0;

	/* statistics */
	switch (type) {
	case IPExtReachCode:
		isisCounters.ipext++;
		break;
	case IPIntReachCode:
		isisCounters.ipint++;
		break;
	case LSPPrefixNeighborCode:
		isisCounters.isopref++;
		break;
	case IPInterDomInfo:
		isisCounters.idrpi++;
		break;
	case AreaAddressCode:
		isisCounters.aa++;
		break;
	case LSPISNeighborCode:
		isisCounters.isn++;
		break;
	case LSPESNeighborCode:
		isisCounters.esn++;
		break;
	case IPIfAddrCode:
		isisCounters.ipintf++;
		break;
	case ProtoSupportedCode:
		isisCounters.protosup++;
		break;
	case IPSumReachCode:
		isisCounters.ipsum++;
		break;
	case LSPPDL2ISCode:
		isisCounters.pdl2is++;
		break;
	case IPAuthInfoCode:
		isisCounters.ipauth++;
		break;
	case AuthenticationCode:
		isisCounters.auth++;
		break;
	case leafNode:
		isisCounters.leaves++;
		break;
	}

	return(opt);
}

void_t
createPref __PF1(af, int)
{
	void_t pref;

	pref = task_block_alloc(af == AF_INET ? isis_prefIP_block : isis_prefISO_block);
	if (af == AF_INET) isisCounters.prefIP++;
	else isisCounters.prefISO++;
	return(pref);
}

/*
 *	Reduce the current LSP by at least size bytes to make room for
 *	new options. This is the procedure that determines how much options
 *	float from LSP to LSP. The current scheme is simple. Remove the option
 *	from the end of this LSP, and add it to the beginning of the next.
 *
 *	Must remove options from the end. If they are removed from the
 *	beginning, it is possible that LSPlow options might be placed after
 *	LSPhigh options.
 * 
 * 	STEVE XXX - this must now update the LSPDesc's attribute list and 
 * 	the attribute index.  XXX - this will really hose us down if we have
 * 	to move prefix or IDRPi options.
 */
static void
reduceLSP(grp, desc, size)
LSPGroup	*grp;
LSPDesc		*desc;
int			size;
{
	LSPOption	*opt;

	if (grp == L2LSP) 
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("IS-IS reduceLSP called - big hosing forthcoming"));
	
	IterateDLListBack(opt, &desc->options, LSPOption *) {
		removeOption(opt);
		size -= LSPOptionSize(opt);
		if (nextLSPdesc(grp, desc) == NULL) {
			addToLSP(grp, newLSP(grp, desc), opt);
		} else {
			addToLSP(grp, nextLSPdesc(grp, desc), opt);
		}

		IFTRACE(T_BUILDLSP)
			dumpLSPDesc(desc, "LSP: changed (reduceLSP) ");
		ENDTRACE

		lspChanged(opt->lspDesc);	/* must flood lsp with new option */
		if (size <= 0)
			break;
	}
}

/*
 *	Add the option to the LSP. If the option can not fit in this LSP,
 *	place it in the next LSP or make room in this LSP.  This routine
 *	may need to create a new LSP (and LSP Desc) in order to insert the
 *	option in the correct place.
 */
static void
addToLSP(grp, desc, newOpt)
LSPGroup	*grp;
LSPDesc		*desc;
LSPOption	*newOpt;
{
	LSPOption *opt;

	if (newOpt->key == LSPlow) {
		if (desc->spaceLeft > LSPOptionSize(newOpt)) {
			addAsFirst(desc, newOpt);
		} else {
			/* No space left in current lsp */
			if (nextLSPdesc(grp, desc) == NULL) {
				/* next LSP does not exist */
				if (lastOption(desc)->key == LSPlow) {
					/* create new LSP after desc, add opt to it */
					addToLSP(grp, newLSP(grp, desc), newOpt);
				} else {
					/* must move some "LSPhigh" options out of this LSP */
					assert(lastOption(desc)->key == LSPhigh);
					reduceLSP(grp, desc, LSPOptionSize(newOpt));
					addToLSP(grp, desc, newOpt);
				}
			} else {
				addToLSP(grp, nextLSPdesc(grp, desc), newOpt);
			}
		}
	} else {
		assert(newOpt->key == LSPhigh);
		if (desc->spaceLeft > LSPOptionSize(newOpt)) {
			if (nextLSPdesc(grp, desc) == NULL) {
				addAsLast(desc, newOpt);
			} else {
				if (hasOptions(nextLSPdesc(grp, desc))) {
					if (firstOption(nextLSPdesc(grp, desc))->key == LSPhigh) {
						addAsLast(desc, newOpt);
					} else {
						assert(firstOption(nextLSPdesc(grp, desc))->key == LSPlow);
						addToLSP(grp, nextLSPdesc(grp, desc), newOpt);
					}
				} else {
					addToLSP(grp, nextLSPdesc(grp, desc), newOpt);
				}
			}
		} else {
			/* no space left, append to next LSP (create if necessary) */
			if (nextLSPdesc(grp, desc) == NULL) {
				addToLSP(grp, newLSP(grp, desc), newOpt);
			} else {
				addToLSP(grp, nextLSPdesc(grp, desc), newOpt);
			}
		}
	}
}

/*
 *	Add option 'newOpt' into the "logical" LSP. The option will be placed 
 *	into one of the real LSPs contained in the group. All the options in the
 *	group are kept in ascending order sorted on the option 'key'. 
 *	Multiple key values are not allowed in a single LSP.
 */
static void
addToGroup(grp, newOpt)
LSPGroup	*grp;		/* "logical" LSP */
LSPOption	*newOpt;	/* option to add to grp */
{
	if (newOpt->key == LSPzero) {
		addAsLast(firstLSPdesc(grp), newOpt);
	} else {
		addToLSP(grp, nextLSPdesc(grp, firstLSPdesc(grp)), newOpt);
	}
}

/*
 *	Return true if the option has the same metrics as those passed
 */
static int
metricCheck(opt, metrics)
LSPOption 	*opt;
MetricList	*metrics;
{
	MetricList *m;

	switch(opt->type) {
	case IPExtReachCode:
	case IPIntReachCode: {
		prefIP *tmp = (prefIP *) opt->data;
		m = &tmp->metrics;
		break;
	}
	case LSPPrefixNeighborCode: {
		prefISO *tmp = (prefISO *) opt->data;
		m = &tmp->metrics;
		break;
	}
	default:
		m = (MetricList *) opt->data;
	}

	return !bcmp(m, metrics, sizeof(MetricList));
}

/*
 * Return true if the prefix option has the path attributes
 * as those passed.  If this is an ISO prefix option, check
 * the metrics as well.
 */
static int
attrCheck  __PF2(opt, LSPOption *,
		 sk, struct searchkey *)
{
	switch(opt->type) {
	case IPExtReachCode:
	case IPIntReachCode: {
		if (opt->attr->path != sk->path) return(0);
		else return(1);
	}
	case LSPPrefixNeighborCode: {
		MetricList *m;
		prefISO *tmp = (prefISO *) opt->data;
		if (opt->attr->path != sk->path) return(0);
		m = &tmp->metrics;
		return !bcmp(m, sk->metrics, sizeof(MetricList));
	}
	default:
		assert(0);
	}
	return(0);
}

/*

/*
 *	Add a list of system IDs to an ES option in one of the
 *	LSPs associated with 'grp'. Return an identifier that
 *	describes where the IDs were placed.
 */
LSPOptPtr
addESNeighbor(grp, metrics, numIds, ids)
LSPGroup	*grp;		/* logical LSP to place entry in */
MetricList	metrics;	/* metrics for entries */
int		numIds;		/* number of 6 byte IDs below */
SystemID6	ids;		/* array 'numIds' of 6 byte IDs */
{
	LSPOption	*opt;
	u_char		*cp;
	LSPOptPtr	optID;
	Boolean		mustAdd = False;

	/*
	 *	If this assertion is false, need to break 'numIds' into
	 *	several options (which would be a ROYAL pain in the ass for
	 *	when deleting entries)
	 */
	assert(numIds*6 < MaxOptLen-1);

	opt = findOption(grp, LSPESNeighborCode, numIds*6, 
		metricCheck, (u_char *)&metrics);
	if (opt) {
		cp = LSPOptionUnusedData(opt);
	} else {
		opt = createOption(LSPhigh, LSPESNeighborCode);
		cp = LSPOptionUnusedData(opt);
		bcopy((caddr_t) &metrics, (caddr_t) cp, sizeof(MetricList));
		cp += sizeof(MetricList);
		opt->len += sizeof(MetricList);
		mustAdd = True;
	}

	optID.opt = opt;
	optID.off = opt->len;

	bcopy((caddr_t) ids, (caddr_t) cp, 6*numIds);
	opt->len += 6*numIds;

	if (mustAdd)
		addToGroup(grp, opt);
	else
		opt->lspDesc->spaceLeft -= 6*numIds;

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(opt->lspDesc, "LSP: changed (add ES) ");
	ENDTRACE

	lspChanged(opt->lspDesc);

	return(optID);
}

/*
 * findESNeighbor
 * TS This routine finds a particular option within an LSP group
 */
LSPOptPtr
findESNeighbor (grp, metrics, numIds, ids)
LSPGroup *grp;		/* logical LSP to find entry */
MetricList metrics;	/* metric for entry */
int numIds;		/* number of 6 bytes ids below */
SystemID6 ids;		/* array of ids to find */
{
	int offset;
	u_char *cp;
	LSPDesc *desc;
	static LSPOptPtr optPtr;

	optPtr.opt = NULL;
	optPtr.off = 0;

	IterateDLListForw(desc, &grp->list, LSPDesc *) {
		LSPOption *opt;
		IterateDLListForw (opt, &desc->options, LSPOption *) {
			cp = opt->data;
			if ((opt->type == LSPESNeighborCode) &&
				(!bcmp (cp, &metrics, sizeof (MetricList)))) {
				/* go through the options an Id at a time*/
				for (offset = sizeof (MetricList); offset < opt->len; offset+=6) {
					cp = opt->data + offset;
					if (!bcmp (ids, cp, 6*numIds)) {
					 	optPtr.opt = opt;
					 	optPtr.off = offset;
					 	return (optPtr);
					}
				}
			}
		}
	}
	return (optPtr) ; /* not found */
}

/*
 * findISNeighbor
 * TS This routine finds a particular option within an LSP group
 */
LSPOptPtr
findISNeighbor (grp, metrics, id)
LSPGroup *grp;		/* logical LSP to find entry */
MetricList metrics;	/* metric for entry */
SystemID7 id;		/* id to find */
{
	int offset;
	u_char *cp;
	LSPDesc *desc;
	static LSPOptPtr optPtr;

	optPtr.opt = NULL;
	optPtr.off = 0;

	IterateDLListForw(desc, &grp->list, LSPDesc *) {
		LSPOption *opt;
		IterateDLListForw (opt, &desc->options, LSPOption *) {
			if (opt->type == LSPISNeighborCode) {
				/* go through the options after ignoring the 1st virtual flag byte*/
				for (offset = 1; offset < opt->len; offset+=11) {
					cp = opt->data + offset;
					if (equalID (id, cp + sizeof (MetricList), 7) &&
					 (!bcmp (cp, &metrics, sizeof (MetricList)))) {
					 	optPtr.opt = opt;
					 	optPtr.off = offset;
					 	return (optPtr);
					}
				}
			}
		}
	}
	return (optPtr) ; /* not found */
}

/*
 * Find IP reachability information using the hint given.
 */
LSPOptPtr
findIPReach __PF6(grp, LSPGroup *,	/* LSP group in which to find entry */
		  metrics, MetricList,	/* metrics */
		  addr, struct in_addr,	/* address */
		  mask, struct in_addr,	/* and mask */
		  code, u_char,		/* internal or external info */
		  hint, LSPOptPtr)	/* hint about where to find this (addr, mask, metrics, code) tuple */
{
	int offset;
	u_char *cp;
	LSPDesc *desc;
	static LSPOptPtr optPtr;
	LSPOption *opt;

#define	sameIPReach(addr, mask, metrics, bp) \
	((* (u_long *) &addr == * (u_long *) (cp+4)) && \
	 (* (u_long *) &mask == * (u_long *) (cp+8)) && \
	 (!bcmp (cp, &metrics, sizeof (MetricList)))) 
	
	optPtr.opt = NULL;
	optPtr.off = 0;

	/* use the hint first */
	if ((opt = hint.opt) == NULL)
		goto fullsearch;
	if (opt->type == code) {
		cp = opt->data + hint.off;
		if (sameIPReach(addr, mask, metrics, cp)) {
			/* would you believe a direct hit */
			optPtr.opt = opt;
			optPtr.off = hint.off;
			return (optPtr);
		}
		/* well, maybe it moved within the hinted option */
		for (offset = 0; offset < opt->len; offset+=12) {
			cp = opt->data + offset;
			if (sameIPReach(addr, mask, metrics, cp)) {
				/* a near miss */
				optPtr.opt = opt;
				optPtr.off = offset;
				return (optPtr);
			}
		}
	}

	/* a complete miss - this shouldn't happen unless the code is munged somehow */
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("IS-IS route TSI info was bogus for 0x%08x/0x%08x - recovery performed",
		      addr,
		      mask));
	fullsearch:
	IterateDLListForw(desc, &grp->list, LSPDesc *) {
		IterateDLListForw (opt, &desc->options, LSPOption *) {
			if (opt->type == code) {
				/* go through the options */
				for (offset = 0; offset < opt->len; offset+=12) {
					cp = opt->data + offset;
					if (sameIPReach(addr, mask, metrics, cp)) {
					 	optPtr.opt = opt;
					 	optPtr.off = offset;
					 	return (optPtr);
					}
				}
			}
		}
	}
	return (optPtr) ; /* not found */
}

/*
 * This routine finds the given prefix neighbor's option in
 * an LSP group.
 */
LSPOptPtr
findPrefNeighbor __PF4(grp, LSPGroup *,		/* logical LSP in which to find entry */
		       metrics, MetricList,	/* metrics we're looking for */
		       pref, octet *,		/* prefix we're looking for */
		       prefLen, int)		/* and it's length in octets */
{
	int offset;
	octet *thisPref;
	int thisLen;
	LSPDesc *desc;
	static LSPOptPtr optPtr;

	optPtr.opt = NULL;
	optPtr.off = 0;

	IterateDLListForw(desc, &grp->list, LSPDesc *) {
		LSPOption *opt;
		IterateDLListForw (opt, &desc->options, LSPOption *) {
			if (opt->type == LSPPrefixNeighborCode) {
				/* skip this option if metric is different */
				if (bcmp(opt->data, &metrics, sizeof(MetricList))) continue;
				/* go through each prefix listed */
				offset = sizeof(MetricList);
				while (offset < opt->len) {
					thisLen = (*(opt->data + offset) + 1) >> 1;
					if (thisLen == prefLen) {
						thisPref = opt->data + offset + 1;
						if (!bcmp(pref, thisPref, prefLen)) {
							/* found it */
					 		optPtr.opt = opt;
					 		optPtr.off = offset;
					 		return (optPtr);
						}
					}
					offset += thisLen + 1;
				}
			}
		}
	}
	return (optPtr) ; /* not found */
}


/*
 * delESNeighbor
 * TS This routine attempts to find the specified option, and removes it.
 */
Boolean
delESNeighbor(adj, grp, metrics, numIds, ids)
AdjacencyEntry *adj;	/* adj referring to this ES info */
LSPGroup *grp;		/* logical LSP to find entry */
MetricList metrics;	/* metric for entry */
int numIds;		/* number of 6 bytes ids below */
SystemID6 ids;		/* array of ids to remove */
{
	LSPOptPtr optPtr;
	optPtr = findESNeighbor (grp, metrics, numIds, ids);
	assert (optPtr.opt);
	rmESNeighbor (adj, optPtr);
	return (True);
}

/*
 * delISNeighbor
 * TS This routine attempts to find the specified option, and removes it.
 */
Boolean
delISNeighbor(grp, metrics, id)
LSPGroup *grp;		/* logical LSP to find entry */
MetricList metrics;	/* metric for entry */
SystemID7 id;		/* id to remove */
{
	LSPOptPtr optPtr;

	optPtr = findISNeighbor (grp, metrics, id);
	assert(optPtr.opt);
	rmISNeighbor (optPtr);
	return (True);
}

/*
 * Remove IP reachable information (metrics, addr, mask) from LSP.
 */
void
delIPReach __PF1(p, prefIP *)		/* where to find this (addr, mask, metrics, code) tuple */
{
	LSPOption	*opt = p->opt;
	LSPDesc 	*desc = opt->lspDesc;

	opt->len -= 12;
	desc->spaceLeft += 12;

	/* unlink and free the duiker */
	if (p->prev) p->prev->next = p->next;
	else opt->data = (u_char *) p->next;
	if (p->next) p->next->prev = p->prev;
	opt->attr->refcount--;
	task_block_free(isis_prefIP_block, p);
	isisCounters.prefIP--;

	if (opt->len == 0) {
		/* this was the last prefix, so remove the entire option */
		removeAndFreeOption(opt);
	}

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(desc, "LSP: changed (remove IP Reachable) ");
	ENDTRACE

	lspChanged(desc);
}

/*
 * This routine attempts to find the specified prefix neighbor
 * and removes it.
 */
void
delPrefNeighbor __PF5(grp, LSPGroup *,		/* logical LSP in which to find entry */
		      metrics, MetricList,	/* metrics we're looking for */
		      pref, octet *,		/* prefix we're looking for */
		      prefLen, int,		/* and it's length in octets */
		      p, prefISO *)		/* where to find the prefix */
{
#ifdef notdef
	LSPOptPtr optPtr;

	optPtr = findPrefNeighbor(grp, metrics, pref, prefLen);
	assert(optPtr.opt);
#endif

	rmPrefNeighbor(p);
}


/*
 *	Remove the ES option specified by 'optPtr' from its LSP
 */
static void
rmESNeighbor __PF2(adj, AdjacencyEntry *,
		   optPtr, LSPOptPtr)
{
	LSPOption	*opt = optPtr.opt;
	u_char		off = optPtr.off;
	int			idLen = (adj->numIds * 6);
	LSPDesc		*desc = opt->lspDesc;

	/* there should always be at least 1 id in an adjacency */
	assert (adj->numIds > 0);

	/* 
	 *	idLen represents the total number of bytes to be removed from
	 *	this option. (metric list plus some number of system IDs)
	 */

	if (off == (opt->len - idLen)) {
		/* What luck! The option to be removed is at the end of opt */
		opt->len -= idLen;
	} else {
		/* Bummer dude, gotta copy existing options up */
		u_char	*from = opt->data+off+idLen, *to = opt->data+off;
		u_char	len = opt->len - (off+idLen);
		bcopy((caddr_t)from, (caddr_t)to, len);
		opt->len -= idLen;
	}
	desc->spaceLeft += idLen;
	if (opt->len == sizeof(MetricList))
		removeAndFreeOption(opt);

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(desc, "LSP: changed (remove ES) ");
	ENDTRACE

	lspChanged(desc);
}

/*
 *	Remove the IS option specified by 'optPtr' from its LSP
 */
static void
rmISNeighbor __PF1(optPtr, LSPOptPtr)
{
	LSPOption	*opt = optPtr.opt;
	u_char		off = optPtr.off;

	if (off == (opt->len - 11)) {
		/* What luck! The option to be removed is at the end of opt */
		opt->len -= 11;
	} else {
		/* Bummer dude, gotta copy existing options up */
		u_char	*from = opt->data+off+11, *to = opt->data+off;
		u_char	len = opt->len - (off+11);
		bcopy((caddr_t)from, (caddr_t)to, len);
		opt->len -= 11;
	}
	opt->lspDesc->spaceLeft += 11;

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(opt->lspDesc, "LSP: changed (remove IS) ");
	ENDTRACE

	lspChanged(opt->lspDesc);
}

/*
 * Remove the given ISO prefix. 
 */
static void
rmPrefNeighbor __PF1(p, prefISO *)
{
	LSPOption	*opt = p->opt;
	LSPDesc		*desc = opt->lspDesc;
	int plen;

	plen = ((p->len + 1) >> 1) + 1;
	opt->len -= plen;
	desc->spaceLeft += plen;

	/* unlink and free the duiker */
	if (p->prev) p->prev->next = p->next;
	else opt->data = (u_char *) p->next;
	if (p->next) p->next->prev = p->prev;
	if (--opt->attr->refcount == 0) {
		task_block_free(isis_lspattr_block, opt->attr);
		isisCounters.lspattr--;
		opt->attr = 0;
	}
	task_block_free(isis_prefISO_block, p);
	isisCounters.prefISO--;

	if (opt->len == sizeof(MetricList)) {
		removeAndFreeOption(opt);
	}

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(desc, "LSP: changed (remove prefix) ");
	ENDTRACE

	lspChanged(desc);
}

/*
 *	replace the option specified by 'optPtr' with new
 *	information.
 */
void
replaceISNeighbor(optPtr, metrics, id)
LSPOptPtr	optPtr;		/* option to be replaced */
MetricList	metrics;	/* metrics for entries */
SystemID7	id;			/* ID to add */
{
	LSPOption	*opt = optPtr.opt;
	u_char		*cp = opt->data+optPtr.off;

	bcopy((caddr_t) &metrics, (caddr_t) cp, sizeof(MetricList));
	cp += sizeof(MetricList);
	copyID(id, cp, 7);

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(opt->lspDesc, "LSP: changed (replace IS) ");
	ENDTRACE

	lspChanged(opt->lspDesc);
}

static LSPOptPtr
addISNeighbor(grp, metrics, id)
LSPGroup	*grp;		/* logical LSP to place entry in */
MetricList	metrics;	/* metrics for entries */
SystemID7	id;		/* ID to add */
{
	LSPOption	*opt;
	u_char		*cp;
	LSPOptPtr	optID;
	Boolean		mustAdd = False;

	opt = findOption(grp, LSPISNeighborCode, 11, NULL, NULL);
	if (opt) {
		cp = LSPOptionUnusedData(opt);
	} else {
		opt = createOption(LSPlow, LSPISNeighborCode);
		cp = LSPOptionUnusedData(opt);
		*cp++ = 0;	/* virtual flag */
		opt->len++;	/* len of virtual flag */
		mustAdd = True;
	}

	optID.opt = opt;
	optID.off = opt->len;

	bcopy((caddr_t) &metrics, (caddr_t) cp, sizeof(MetricList));
	cp += sizeof(MetricList);
	copyID(id, cp, 7);
	opt->len += 11;

	if (mustAdd)
		addToGroup(grp, opt);	/* will decrement spaceLeft */
	else
		opt->lspDesc->spaceLeft -= 11;

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(opt->lspDesc, "LSP: changed (add IS) ");
	ENDTRACE

	lspChanged(opt->lspDesc);

	return(optID);
}

/*
 *      Add a reachable address prefix to the
 *      LSPs associated with 'grp'.
 */
prefISO *
addPrefixNeighbor __PF5(grp, LSPGroup *,	/* group in which to place prefix */
			metrics, MetricList,	
			prefix, octet *,
			prefixLen, int,		/* prefix length in semi-octets */
			path, as_path *)	/* prefix path attributes */
{
	LSPOption	*opt, *idrpi, *leaf;
        Boolean         mustAdd = False;
        int             lenInBytes;
	prefISO		*p;
	LSPDesc		*lastLSP;
	LSPDesc		*availLSP;
	LSPOption	*fullOpt = 0;
	struct searchkey sk;
	int pathSpace;
	isis_asp	*asp;

        lenInBytes = (prefixLen + 1) >> 1;

	sk.path = path;
	sk.metrics = &metrics;
	pathSpace = sizeof(isis_asp);	/* IDRPi type + sizeof(u_long) + sizeof(path_id) */
		opt = findPrefixOption(grp, LSPPrefixNeighborCode, lenInBytes+1, attrCheck, &sk, &fullOpt,pathSpace,&availLSP);
        if (!opt) {
                opt = createOption(LSPhigh, LSPPrefixNeighborCode);
                opt->len += sizeof(MetricList);
                mustAdd = True;
		opt->attr->path = path;
        }

	/* link this prefix into the option */
	p = (prefISO *) createPref(AF_ISO);
	p->prev = (prefISO *) 0;
	p->next = (prefISO *) opt->data;
	if (p->next) p->next->prev = p;
	opt->data = (u_char *) p;
	p->opt = opt;

	p->metrics = metrics;
	p->len = prefixLen;
        bcopy(prefix, p->addr, lenInBytes);
        opt->len += lenInBytes+1;
	opt->attr->refcount++;

        if (mustAdd) {
		lastLSP = lastLSPdesc(grp);
		if (fullOpt)
			addAfterOpt(opt, fullOpt);
		else if (lastLSP && (lastLSP->lspNumber < 255)) {
                        /* stick IDRPi and prefix options in a new LSP */
                        availLSP = newLSP(grp, lastLSP);
			/* this is a leaf node, so indicate that with our implementation-specific option */
			leaf = createOption(LSPhigh, leafNode);
			leaf->len = 1;
			*(leaf->data) = 1;
			addToLSP(grp, availLSP, leaf);
                        opt->attr->idrpiOpt = idrpi = createOption(LSPhigh, IPInterDomInfo);
                        idrpi->refcount++;
                        idrpi->len = pathSpace;
                        asp = (isis_asp *) idrpi->data;
                        asp->code = 1;  /* local type */
                        asp->version = 1;
                        * (u_long *) &asp->data = path ? path->path_id : 0;
                        /* addToLSP(grp, availLSP, idrpi); */
			addAfterOpt(idrpi, leaf);	
                        addAfterOpt(opt, idrpi);
		} else if (availLSP) {
                        /* stick IDRPi and prefix options in an existing LSP */
                        opt->attr->idrpiOpt = idrpi = createOption(LSPhigh, IPInterDomInfo);
                        idrpi->refcount++;
                        idrpi->len = pathSpace;
                        asp = (isis_asp *) idrpi->data;
                        asp->code = 1;  /* local type */
                        asp->version = 1;
                        * (u_long *) &asp->data = path ? path->path_id : 0;
                        addToLSP(grp, availLSP, idrpi);
                        addAfterOpt(opt, idrpi);
		} else {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("addPrefNeighbor used addToGroup"));
			addToGroup(grp, opt);
		}
        } else
                opt->lspDesc->spaceLeft -= lenInBytes+1;

        IFTRACE(T_BUILDLSP)
                dumpLSPDesc(opt->lspDesc, "LSP: changed (add Prefix) ");
        ENDTRACE

        lspChanged(opt->lspDesc);

	return(p);
}

void
removeAllOptions(grp,code)
LSPGroup	*grp;		/* logical LSP to place entry in */
u_char		code;
/* delete all options of given code from the lsp grp.
*/
{
	LSPOption	*opt;
	opt = findOption(grp , code, 0, NULL, NULL);
	while(opt) {
		removeAndFreeOption(opt);
		opt = findOption(grp , code, 0, NULL, NULL);
	}
}

prefIP *
addIPReachToLSP __PF6(
	    grp, LSPGroup *,		/* logical LSP in which to place entry */
	    metrics, MetricList,	/* metrics for entries */
	    addr, struct in_addr,
	    mask, struct in_addr,
	    code, u_char,
	    path, as_path *)
{
	LSPOption	*opt, *idrpi, *leaf;
	Boolean		mustAdd;
	prefIP		*p;
	LSPDesc		*lastLSP;
	LSPDesc		*availLSP;
	LSPOption	*fullOpt = 0;	/* similar but full option - create new option immediately following this one */
	struct searchkey sk;
	int pathSpace;
	isis_asp	*asp;

	assert (code == IPIntReachCode || code == IPExtReachCode);

	mustAdd = False;
	sk.path = path;
	sk.metrics = &metrics;
	pathSpace = (grp == L2LSP) ? sizeof(isis_asp) : 0;	/* IDRPi type + sizeof(u_long) + sizeof(path_id) */

	opt = findPrefixOption(grp, code, 12, attrCheck, &sk, &fullOpt, pathSpace, &availLSP);
	if (!opt) {
		opt = createOption(LSPhigh, code);
		mustAdd = True;
		opt->attr->path = path;
	}

	/* link this prefix into the option */
	p = (prefIP *) createPref(AF_INET);
	p->prev = (prefIP *) 0;
	p->next = (prefIP *) opt->data;
	if (p->next) p->next->prev = p;
	opt->data = (u_char *) p;
	p->opt = opt;

	p->metrics = metrics;
	p->addr = addr.s_addr;
	p->mask = mask.s_addr;
	opt->len += 12;
	opt->attr->refcount++;

	if (mustAdd) {
		lastLSP = lastLSPdesc(grp);
		if (fullOpt) {
			addAfterOpt(opt, fullOpt);
			if (grp == L2LSP) {
				opt->attr->idrpiOpt = fullOpt->attr->idrpiOpt;
				opt->attr->idrpiOpt->refcount++;
			}
		} else if (lastLSP && (lastLSP->lspNumber < 255)) {
			if (grp == L2LSP) {
				availLSP = newLSP(grp, lastLSP); 
				/* this is a leaf node, so indicate that with our implementation-specific option */
				leaf = createOption(LSPhigh, leafNode);
				leaf->len = 1;
				*(leaf->data) = 1;
				addToLSP(grp, availLSP, leaf);
				/* stick IDRPi and prefix options in a new LSP */
				opt->attr->idrpiOpt = idrpi = createOption(LSPhigh, IPInterDomInfo);
				idrpi->refcount++;
				idrpi->len = pathSpace;
				asp = (isis_asp *) idrpi->data;
				asp->code = 1;	/* local type */
				asp->version = 1;
				* (u_long *) &asp->data = path ? path->path_id : 0;
				/* addToLSP(grp, availLSP, idrpi); */
				addAfterOpt(idrpi, leaf);	
				addAfterOpt(opt, idrpi);
			} else {
				/* L1 prefix - no IDRPi needed */
				/* STEVE XXX - add the leaf node option here too */
				addToLSP(grp, newLSP(grp, lastLSP), opt);
			}
		} else if (availLSP) {
			if (grp == L2LSP) {
				/* stick IDRPi and prefix options in an existing LSP */
				opt->attr->idrpiOpt = idrpi = createOption(LSPhigh, IPInterDomInfo);
				idrpi->refcount++;
				idrpi->len = pathSpace;
				asp = (isis_asp *) idrpi->data;
				asp->code = 1;	/* local type */
				asp->version = 1;
				* (u_long *) &asp->data = path ? path->path_id : 0;
				addToLSP(grp, availLSP, idrpi);
				addAfterOpt(opt, idrpi);
			} else {
				/* L1 prefix - no IDRPi needed */
				addToLSP(grp, availLSP, opt);
			}
		} else {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("addIPreach used addToGroup"));
			addToGroup(grp, opt);
		}
	} else
		opt->lspDesc->spaceLeft -= 12;

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(opt->lspDesc, "LSP: changed (add IP Reach) ");
	ENDTRACE

	lspChanged(opt->lspDesc);

	return(p);
}

/* DUAL: add the Inter-Domain Information Type field */
void
addInterDomInfo(grp, info, len)
LSPGroup        *grp;           /* logical LSP to place entry in */
char            *info;          /* the Inter-Domain Information */
int                     len;            /* total len of field */
{
        LSPOption       *opt;
        u_char          *cp;

        opt = createOption(LSPhigh, IPInterDomInfo);
        cp = LSPOptionUnusedData(opt);

        bcopy(info, (caddr_t) cp, len);
        opt->len = len;

        addToGroup(grp, opt);

        IFTRACE(T_BUILDLSP)
                dumpLSPDesc(opt->lspDesc, "LSP: changed (add Inter-Domain Info) ");
        ENDTRACE

        lspChanged(opt->lspDesc);
}

static LSPOptPtr
addAreaAddrs(list, grp)
AreaAddrList	list;
LSPGroup	*grp;		/* logical LSP to place entry in */
{
	LSPOption	*opt;
	u_char		*cp;
	LSPOptPtr	optID;

	/* should never add this option twice */
	assert(findOption(grp, AreaAddressCode, 1, NULL, NULL) == NULL);

	opt = createOption(LSPzero, AreaAddressCode);
	cp = LSPOptionUnusedData(opt);

	opt->len = LSPinsertAreaAddrList(list, cp) - cp;
	addToGroup(grp, opt);

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(opt->lspDesc, "LSP: changed (add AreaAddrs) ");
	ENDTRACE

	optID.opt = opt;
	optID.off = 0;	/* starts at beginning of option */

	lspChanged(opt->lspDesc);

	return(optID);
}

/*
 *	Overwrite the existing area addr option with new data
 *	taking care if the new size is different than the old
 */
void
updateAreaAddrs(list, opt)
AreaAddrList	*list;
LSPOption		*opt;
{
	u_char		*cp = opt->data;

	opt->lspDesc->spaceLeft += LSPOptionSize(opt);
	opt->len = LSPinsertAreaAddrList(*list, cp) - cp;
	opt->lspDesc->spaceLeft -= LSPOptionSize(opt);

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(opt->lspDesc, "LSP: changed (update AreaAddrs) ");
	ENDTRACE

	lspChanged(opt->lspDesc);
}

/*
 *	Create an option structure that contains the protocols supported
 *	option. Link this into the global options list
 */
static void
createProtoSupOption()
{
	LSPOption	*opt;
	u_char		*cp;

	opt = createOption(LSPzero, ProtoSupportedCode);
	cp = LSPOptionUnusedData(opt);
	opt->len = insertProtoSup(cp, False) - cp;

	DLLInsque(opt, &globalOptions);

	IFTRACE(T_BUILDLSP)
		trace_only_tf(isis_trace_options,
			      0,
			      ("LSP: global options changed: set protocols supported"));
	ENDTRACE
}

/*
 *	Run through all the circuits and build up the IP address option
 */
static LSPOptPtr	addrOption;
void
buildIPAddrOption()
{
	LSPOption	*opt;
	u_char		*cp, *start;
	int			i;

	if (addrOption.opt == NULL) {
		addrOption.off = 0;	/* starts at beginning of option */
		addrOption.opt = opt = createOption(LSPzero, IPIfAddrCode);
		DLLInsque(opt, &globalOptions);
	}
	else 
		opt = addrOption.opt;
	start = cp = opt->data;
	for (i=0; i<MaximumCircuits; i++) {
		CircuitEntry *c;
		if (c = circuitList[i]) {
			cp = insertIPaddr(c, cp, False);
		}
	}
	opt->len = cp - start;

	IFTRACE(T_BUILDLSP)
		trace_only_tf(isis_trace_options,
			      0,
			      ("LSP: global options changed: IPAddr Option"));
	ENDTRACE
}

/*
 *	Allocate space for LSPs for this system
 */
void
LSPInit()
{
	LSPOptPtr optPtr;
	int i;

	isis_lspoption_block = task_block_init(sizeof(LSPOption), "isis_LSPOption");
	isis_optiondata_block = task_block_init(MaxOptLen-2, "isis_optiondata");
	isis_prefIP_block = task_block_init(sizeof(prefIP), "isis_prefIP");
	isis_prefISO_block = task_block_init(sizeof(prefISO), "isis_prefISO");
	isis_lspattr_block = task_block_init(sizeof(LSPattr), "isis_LSPattr"); 
	isis_lspdesc_block = task_block_init(sizeof(LSPDesc), "isis_LSPDesc");
	isis_lsentry_block = task_block_init(sizeof(LSEntry), "isis_LSEntry");
	isis_lseChangeList_block = task_block_init(sizeof(struct _lseChangeList), "isis_lseChangeList");
	for (i=1; i<=12; i++) 
		isis_lspbuf_block[i] = task_block_init(i*128, "isis_lspbuf");

	DLLInit(&globalOptions);
	createProtoSupOption();

	L1LSP = newLSPGroup(L1LSType, 0);
	L2LSP = newLSPGroup(L2LSType, 0);

	normalLSPAge = newAgeList(normalLSPExpired, 
		Offset(LSEntry, remainingTime));
	deletedLSPAge = newAgeList(deletedLSPExpired, 
		Offset(LSEntry, remainingTime));

	/* place myself in the ES neighbor option of my L1LSP */
	addESNeighbor(L1LSP, zeroMetric, 1, systemID); 

	/* store my area addresses in the L1LSP */
	optPtr = addAreaAddrs(systemAreaAddrs, L1LSP);

	if (systemType == L2IS) {
		/*
		 *	Initialize the Area Address summary to the manually configured
		 *	area addresses and store in my L2LSP
		 */
		bcopy((caddr_t) &systemAreaAddrs,
		      (caddr_t) &l2AreaSummary.summaryList, 
		      sizeof(AreaAddrList));
		l2AreaSummary.optPtr = addAreaAddrs(l2AreaSummary.summaryList, L2LSP);
		/* XXX - stick myself in prefix neighbor options of my L2LSP */
	}
}

/*
 *	Adjacency has come up. Create a entry in the option field of the
 *	non-pseudonode (or pseudonode, if necessary) LSPs. Store a pointer
 *	to the option entry in the adjacency, so that if the adjacency changes
 *	state, the option entry can be revised accordingly.
 *
 *	This routine assumes that given an individual adjacency, it can determine
 *	whether that adjacency should be placed into the non-pseudonode (if it
 *	is pt2pt) or pseudonode (if it is broadcast) LSP.
 */
void
lspAdjUp(c, adj)
CircuitEntry	*c;
AdjacencyEntry	*adj;
{
	assert(c == adj->circuit);

	switch(adj->adjacencyType) {
		case ES:
			if ((c->circuitType == Broadcast) && (adj->type == AutoConfig)) {
				addESNeighbor(c->l1PLSP, zeroMetric, 
					adj->numIds, adj->neighborInfo);
			} else {
				addESNeighbor(L1LSP, c->l1Metric, 
					adj->numIds, adj->neighborInfo);
			}
			break;
				
		case L1IS:
			if (c->circuitType == Broadcast) {
				addISNeighbor(c->l1PLSP, zeroMetric, 
					appendZero(adj->neighborSysID));
			} else {
				assert(c->circuitType == Pt2Pt);
				addISNeighbor(L1LSP, c->l1Metric, 
					appendZero(adj->neighborSysID));
			}
			break;
		
		case L2IS:
			if (c->circuitType == Broadcast) {
				addISNeighbor(c->l2PLSP, zeroMetric, 
					appendZero(adj->neighborSysID));
			} else {
				assert(c->circuitType == Pt2Pt);
				if (!adj->level2Only) {
					addISNeighbor(L1LSP, c->l1Metric, 
						appendZero(adj->neighborSysID));
				}
				addISNeighbor(L2LSP, c->l2Metric, 
					appendZero(adj->neighborSysID));
			}
			break;
		default:
			assert(0);
	}

	if ((c->circuitType == Pt2Pt) && 
		(adj->adjacencyType == L1IS || adj->adjacencyType == L2IS)) {
/* 		floodEverything(c);*/
		switch (systemType) {
			case L2IS:
				floodAllLSPs(c, 2);
				sendCSNP(c, 2);
				if (c->manualL2Only || adj->level2Only)
					break;
				/* ELSE FALL THROUGH */
			case L1IS:
				floodAllLSPs(c, 1);
				sendCSNP(c, 1);
				break;
			default:
				assert(0);
		}
	}
}

/*
 *	Want to flood all LSPs out on a particular link
 *
 *	NOTE - currently ignores the schedRegenerate flag
 *	If an LSP has the schedRegenerate flag set, it will be sent shortly
 *	(when a timer expires), so don't flood that from here. Otherwise,
 *	if the lsp has been built, flood it out
 */
void
floodEverything(c)
CircuitEntry	*c;
{
	LSPDesc		*desc;
	int				i;

	/* first my regular LSPs */
	switch (systemType) {
		case L2IS:
			IterateDLListForw(desc, &L2LSP->list, LSPDesc *)
				if ((desc->lspEntry))
					sendLSP(c, desc->lspEntry);

			if (c->manualL2Only)
				break;
			/* ELSE FALL THROUGH */
		case L1IS:
			IterateDLListForw(desc, &L1LSP->list, LSPDesc *)
				if ((desc->lspEntry))
					sendLSP(c, desc->lspEntry);
			break;
		default:
			assert(0);
	}

	/* now any pseudonode LSPs I may have */
	for (i=0; i<MaximumCircuits; i++) {
		CircuitEntry	*tmp;
		if (tmp = circuitList[i]) {
			if (tmp->l1DR) {
				IterateDLListForw(desc, &tmp->l1PLSP->list, LSPDesc *)
					if ((desc->lspEntry))
						sendLSP(c, desc->lspEntry);
			}
			if (tmp->l2DR) {
				IterateDLListForw(desc, &tmp->l2PLSP->list, LSPDesc *)
					if ((desc->lspEntry))
						sendLSP(c, desc->lspEntry);
			}
		}
	}
}

/*
 *	Called when a circuit is enabled. If this is a broadcast circuit,
 *	then log its LnCircuitID in the lnNLSPs. (This logs the neighbouring
 *	pseudonode IDS).
 *
 */
void
lspCircuitUp(c)
CircuitEntry	*c;
{
	c->up = True;
	if (c->circuitType == Broadcast) {
		/* it is possible that circuitId or L2CircuitId are zero */
		switch (systemType) {
			case L2IS:
				addISNeighbor(L2LSP, c->l2Metric, c->l2CircuitId);
				addISNeighbor(c->l2PLSP, zeroMetric, appendZero(systemID));
				if (c->manualL2Only)
					break;
				/* ELSE FALL THROUGH */
			case L1IS:
				addISNeighbor(L1LSP, c->l1Metric, c->circuitId);
				addISNeighbor(c->l1PLSP, zeroMetric, appendZero(systemID));
				break;
			default:
				assert(0);
		}
		floodEverything(c);
	}

#ifdef	PROTO_SNMP
	{
	    IsisMibEntry	*pMibEntry;
	    IsisCircEntry	*pCircEntry;

	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable, c->localId);
	    if (pCircEntry) {
	        pCircEntry->isisCircOperState = 2;		/* Isis-Mib */
	    } else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("lspCircuitUp(): cannot locate circ mib entry for localId==%d",
			      c->localId));
	    }

	}
#endif	/* PROTO_SNMP */
}

/*
 * TS - add this routine
 * Called when a circuit is disabled.
 *
 */
void lspCircuitDown(c)
CircuitEntry	*c;
{
	if (c->circuitType == Broadcast) {
		switch (systemType) {
			case L2IS:
				delISNeighbor(L2LSP, c->l2Metric, c->l2CircuitId) ;
				delISNeighbor(c->l2PLSP, zeroMetric, appendZero(systemID));
				if (c->manualL2Only)
					break;
				/* ELSE FALL THROUGH */
			case L1IS:
				delISNeighbor(L1LSP, c->l1Metric, c->circuitId);
				delISNeighbor(c->l1PLSP, zeroMetric, appendZero(systemID));
				break;
			default:
				assert(0);
		}
		floodEverything(c);
	}
	c->up = False;
#ifdef	PROTO_SNMP
	{
	    IsisMibEntry	*pMibEntry;
	    IsisCircEntry	*pCircEntry;

	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable, c->localId);
	    if (pCircEntry) {
	        pCircEntry->isisCircOperState = 1;		/* Isis-Mib */
	    } else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("lspCircuitDown(): cannot locate circ mib entry for localId==%d", c->localId));
	    }

	}
#endif	/* PROTO_SNMP */
}

/*
 * Call this baby when an active (and still active) circuit changes
 * metrics.
 */
void
lspCircuitChanged __PF3(c, CircuitEntry *,
			l1metric, MetricList,
			l2metric, MetricList)
{
	LSPOptPtr optPtr, optPtr2;
	AdjacencyEntry *adj;
	u_char *cp;

	if (c->circuitType == Broadcast) {
		switch (systemType) {
			/* change the cost to the DR, if there is one */
			case L2IS:
				optPtr = findISNeighbor(L2LSP, c->l2Metric, c->l2CircuitId);
				if (!optPtr.opt) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("couldn't find IS neighbor option for level 2, metric %d (0x%02x), id %s",
						      c->l2Metric.defalt,
						      c->l2Metric.defalt,
						      IDToStr(c->l2CircuitId, 7)));
				}
				assert (optPtr.opt);
				cp = optPtr.opt->data + optPtr.off;
        			bcopy((caddr_t) &l2metric, (caddr_t) cp, sizeof(MetricList));
				lspChanged(optPtr.opt->lspDesc);	
        			IFTRACE(T_BUILDLSP)
                			dumpLSPDesc(optPtr.opt->lspDesc, "LSP: changed (replaced metrics) ");
        			ENDTRACE
				if (c->manualL2Only)
					break;
				/* ELSE FALL THROUGH */
			case L1IS:
				optPtr = findISNeighbor(L1LSP, c->l1Metric, c->circuitId);
				if (!optPtr.opt) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("couldn't find IS neighbor option for level 1, metric %d (0x%02x), id %s",
						      c->l1Metric.defalt,
						      c->l1Metric.defalt,
						      IDToStr(c->circuitId, 7)));
				}
				assert(optPtr.opt);
				cp = optPtr.opt->data + optPtr.off;
        			bcopy((caddr_t) &l1metric, (caddr_t) cp, sizeof(MetricList));
				lspChanged(optPtr.opt->lspDesc);	
        			IFTRACE(T_BUILDLSP)
                			dumpLSPDesc(optPtr.opt->lspDesc, "LSP: changed (replaced metrics) ");
        			ENDTRACE
				break;
			default:
				assert(0);
		}
	}
	/* change the cost associated with any Pt2Pt or manually configured ES adjacencies */
	if (c->esAdjs && !DLListEmpty(&c->esAdjs->links)) {
		IterateDLListForw(adj, &c->esAdjs->links, AdjacencyEntry *) {
			if ((c->circuitType == Pt2Pt) || (adj->type != AutoConfig)) {
				/* 
				 * STEVE - this is a delete followed by an add because
				 * a single metric applies to ALL ESNs in an option, which
				 * is built based on metric rather than circuit.
				 */
				delESNeighbor(adj, L1LSP, c->l1Metric, adj->numIds, adj->neighborInfo);
				addESNeighbor(L1LSP, l1metric, adj->numIds, adj->neighborInfo);
			}
		}
	}
	/* change the cost to the neighboring IS */
	if (c->circuitType == Pt2Pt) {
		/* if it's broadcast, we handled cost adjustment to DR and manually configured ES above */
		if (c->isAdjs && !DLListEmpty(&c->isAdjs->links)) {
			IterateDLListForw(adj, &c->isAdjs->links, AdjacencyEntry *) {
				if (adj->adjacencyType == L1IS) {
					optPtr = findISNeighbor(L1LSP, c->l1Metric, appendZero(adj->neighborSysID));
					assert(optPtr.opt);
					cp = optPtr.opt->data + optPtr.off;
					bcopy((caddr_t) &l1metric, (caddr_t) cp, sizeof(MetricList));
					lspChanged(optPtr.opt->lspDesc);	
        				IFTRACE(T_BUILDLSP)
                				dumpLSPDesc(optPtr.opt->lspDesc, "LSP: changed (replaced metrics) ");
        				ENDTRACE
				} else {
					/* it's a L2IS */
					optPtr = findISNeighbor(L2LSP, c->l2Metric, appendZero(adj->neighborSysID));
					assert(optPtr.opt);
					cp = optPtr.opt->data + optPtr.off;
					bcopy((caddr_t) &l2metric, (caddr_t) cp, sizeof(MetricList));
					lspChanged(optPtr.opt->lspDesc);	
        				IFTRACE(T_BUILDLSP)
                				dumpLSPDesc(optPtr.opt->lspDesc, "LSP: changed (replaced metrics) ");
        				ENDTRACE
					if (!adj->level2Only) {
						optPtr = findISNeighbor(L1LSP, c->l1Metric, appendZero(adj->neighborSysID));
						assert(optPtr.opt);
						cp = optPtr.opt->data + optPtr.off;
						bcopy((caddr_t) &l1metric, (caddr_t) cp, sizeof(MetricList));
						lspChanged(optPtr.opt->lspDesc);	
        					IFTRACE(T_BUILDLSP)
                					dumpLSPDesc(optPtr.opt->lspDesc, "LSP: changed (replaced metrics) ");
        					ENDTRACE
					}
				}
			}
		}
	}
	/* change the cost to reachable address prefixes */
}

/* 
 * Call this when a prefix changes its metric or if it disappears.
 */
prefISO *
lspPrefixChanged __PF7(grp, LSPGroup *,		/* logical LSP in which to find entry */
		       oldMetrics, MetricList,	/* current metric */
		       newMetrics, MetricList,	/* new metric */
		       pref, octet *,		/* prefix we're looking for */
		       prefLen, int,		/* and its length in semi-octets */
		       p, prefISO *,		/* where to find this prefix */
		       path, as_path *) 	/* prefix's path attributes */
{
	prefISO *newp = (prefISO *) 0;

	delPrefNeighbor(grp, oldMetrics, pref, (prefLen+1) >> 1, p);
	if (bcmp((u_char *) &newMetrics, (u_char *) &noMetric, sizeof(MetricList)))
		newp = addPrefixNeighbor(grp, newMetrics, pref, prefLen, path);

	return(newp);
}

/* 
 * Call this when an IP prefix changes its metric.
 */
void
lspIPPrefixChanged __PF2(p, prefIP *,			/* where to find this prefix */
		       	 newMetrics, MetricList)	/* new metric */
{
	p->metrics = newMetrics;
	lspChanged(p->opt->lspDesc);
}

/*
 *	Called when the system notices that the Ln designated IS has 
 *	changed. This procedure must remove the IS Neighbor option entry
 *	referring to the old pseudonode, and add an entry for the new
 *	pseudonode.
 */
void
lspDesigISChanged(c, level, oldID, newID)
CircuitEntry	*c;
int				level;
SystemID7		oldID, newID;	/* old/new pseudonode ID */
{
	LSPOptPtr optPtr;
	MetricList metric;

	metric = (level == 1) ? c->l1Metric : c->l2Metric;
	optPtr = findISNeighbor((level == 1) ? L1LSP : L2LSP, metric, oldID);
	if (!optPtr.opt) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("couldn't find IS neighbor option for level %d, metric %d (0x%02x), id %s",
			      level,
			      metric.defalt,
			      metric.defalt,
			      IDToStr(oldID, 7)));
	}
	assert(optPtr.opt);
	replaceISNeighbor(optPtr, metric, newID);
}

/* these bits may be changed by entering lsp overload condition */
Boolean l1HippityBit = False;
Boolean l2HippityBit = False;

u_char
genHippity(type)
u_char  type;   /* l1 vs l2 */
{
	u_char c = 0;
        u_char  hippity;

        if (type == L1LSType)
                hippity = (l1HippityBit == True) ? 1 : 0;
        else
                hippity = (l2HippityBit == True) ? 1 : 0;

	c = 0x10;				/* only support default metric */
	c |= (hippity << 2);	/* hippity bit */
	switch (systemType) {
		case L2IS:
			c |= 0x02;		/* L2 IS */
			/* FALL THROUGH */
		case L1IS:
			c |= 0x01;		/* L1 IS */
			break;
		default:
			assert(0);
	}
	return(c);
}

/*
 *	Basically, rebuild the LSP into the pktBuf, and place the
 *	LSP on the flooding list.
 */
void
lspChangedTimeout(desc)
LSPDesc *desc;
{
	u_char		*bp = desc->pktBuf, *start = bp;
	LSPHeader	*hdr = (LSPHeader *)bp;
	LSPOption	*opt;
	u_short		len;
	LSEntry		*ent;
	Boolean		new = False;
	time_t		now;		/* STEVE - used to set next timer */

	now = timeStamp;
	if ((!desc->mustRegenerate) && (now - desc->lastGenerated < maxLSPGenInterval)) {
		/* 
	 	 * Don't bother if LSP hasn't changed and we haven't reached 
	 	 * our maxLSPGenInterval.
	  	 */
		goto newtimer;		/* restart our timer */
	}
	
	bzero((caddr_t) bp, desc->pktSize);
	bp += sizeof(LSPHeader);

	addCommon(&hdr->common, desc->lspType);
	hostToU16(desc->lspInitLifetime, hdr->remainingLifetime);

	/* set LSP ID */
	copyID(systemID, hdr->lspId.sourceID, 6);
	hdr->lspId.pseudonodeID = desc->lspPseudoID;
	hdr->lspId.LSPNumber = desc->lspNumber;

	if (desc->seqNumber == SequenceModulus) {
                isisCounters.exceedSeqNum++;
#ifdef	PROTO_SNMP
		{
		    IsisMibEntry	*pMibEntry;
		    IsisSysEntry	*pSysEntry;

		    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
		    pSysEntry = &pMibEntry->isisSysEntry;
		    
		    ++pSysEntry->isisSysAttemptToExMaxSeqNums;	/* Isis-Mib */

		}
#endif	/* PROTO_SNMP */

		disableRoutingModule();
	}
		
	hostToU32(desc->seqNumber, hdr->sequenceNumber);
	desc->seqNumber++;

        hdr->pathhippity = genHippity(desc->lspType);

#define	opt2pdu(opt, bp) \
	*bp++ = opt->type; \
	*bp++ = opt->len; \
	switch(opt->type) { \
	case IPIntReachCode: \
	case IPExtReachCode: { \
		prefIP *p; \
		u_long *lp; \
		lp = (u_long *) bp; \
		p = (prefIP *) opt->data; \
		while (p) { \
			*lp++ = * ((u_long *) &p->metrics); \
			*lp++ = p->addr; \
			*lp++ = p->mask; \
			p = p->next; \
		} \
		bp = (u_char *) lp; \
		} \
		break; \
	case LSPPrefixNeighborCode: { \
		prefISO *p; \
		p = (prefISO *) opt->data; \
		* ((u_long *) bp) = * ((u_long *) &p->metrics); \
		bp += 4; \
		while (p) { \
			int lenInBytes = (p->len + 1) >> 1; \
			*bp++ = (u_char) p->len; \
			bcopy(p->addr, bp, lenInBytes); \
			bp += lenInBytes; \
			p = p->next; \
		} \
		} \
		break; \
	default: \
		bcopy((caddr_t) opt->data, (caddr_t) bp, opt->len); \
		bp += opt->len; \
	} 

	/*
	 *	Add any global, dual options first
	 */
	if (desc->lspNumber == 0) {
		IterateDLListForw(opt, &globalOptions, LSPOption *) {
			assert (bp + opt->len + 2 < start + desc->pktSize);	/* sanity */
			opt2pdu(opt, bp);
		}
	}

	IterateDLListForw(opt, &desc->options, LSPOption *) {
		assert (bp + opt->len + 2 < start + desc->pktSize);	/* sanity check */
		opt2pdu(opt, bp);
	}

	len = bp - start;
	hostToU16(len, hdr->pduLength);

	/*
	 *	Generate checksum
	 */
	hostToU16(0, hdr->checksum);
	iso_cksum(&hdr->lspId, len-12, (byte *)(&hdr->checksum));

	
	/*
	 *	If the lspEntry is NULL, this is a new LSP, so we must allocate
	 *	an entry, and store it in the database. If the entry is not new,
	 *	must at least update the signature
	 */
	if ((ent = desc->lspEntry) == NULL) {
		ent = desc->lspEntry = (LSEntry *) task_block_alloc(isis_lsentry_block);
		ent->lspDesc = desc;
		ent->buf = start;
		new = True;
	}

	ent->len = len;
	parseLSP(start, len, &ent->signature);

	IFTRACE(T_BUILDLSP)
		trace_only_tf(isis_trace_options,
			      0,
			      ("LSP: constructed %s",
			       LSSigToStr(&ent->signature)));
	ENDTRACE

	setFlags(ent->SRM, AllCircuits, 0);
	clrFlags(ent->SSN, AllCircuits, 0);

	/* can't call storeLSEntry until the signature is extracted above */
	if (new)
		storeLSEntry(ent);

	adjustPrefsOnly = 0;	/* STEVE XXX - force complete SPF run for now */
	signalDecisionProcess(ent->signature.level);

	/* 
	 * STEVE - and do it all again 
	 */
	desc->lastGenerated = now;
	desc->mustRegenerate = False;	
	newtimer:
	desc->schedRegenerate = True;
	desc->timer = setTimer(minLSPGenInterval, lspChangedTimeout, desc);
}

/*
 *	Return false if 'desc' refers to a pseudonode LSP and we are not the
 *	DR.	Otherwise, if we are the DR, or the LSP is not for the pseudonode, then
 *	return True.
 */
static Boolean
genPseudoOk(desc)
LSPDesc	*desc;
{
	int			i;
	LSPGroup	*grp = desc->group;
	CircuitEntry	*c;
	/*
	 *	Determine if this is a pseudonode LSP - this will be true
	 *	if one of the circuit entries points to the associated LSP group
	 */
	for (i=0; i<MaximumCircuits; i++) {
		if ((c = circuitList[i]) && ((c->l1PLSP == grp) || (c->l2PLSP == grp))) {
			/* only return true if we are LnDR for this circuit */
			if (((desc->lspType == L1LSType) && (c->l1DR)) ||
				(((desc->lspType == L2LSType) && (c->l2DR))))
				return(True);
			else
				return False;
		}
	}
	return(True);
}

/*
 *      Force transmission of LSP regardless of the minLSPGenInterval
 *      throttle
 */
void
lspForceTransmit(desc)
LSPDesc *desc;
{
        if (desc->schedRegenerate) {
                clearTimer(desc->timer);
        }
	desc->mustRegenerate = True;	/* force regeneration */
        lspChangedTimeout(desc);
}

/*
 *	Called to indicate that the LSP must be regenerated.
 *	The dirty work is done by lspChangedTimeout
 *
 *	However, must not regenerate the LSP more frequently than
 *	minLSPGenInterval.
 *
 */
void
lspChanged(desc)
LSPDesc	*desc;
{
	time_t	now;

	/* another sanity check. Spaceleft in LSP can't be bigger than lsp buf */
	assert(desc->spaceLeft <= desc->pktSize - sizeof(LSPHeader));

	/*
	 *	We may be modifing our pseudonode lsp, but we are not really the DR.
	 *	In this case, call decision because something has changed that may
	 *	affect our routes.
	 */
	if (!genPseudoOk(desc)) {
		/* can't call signalDecisionProcess because it may loop via updateArea */
		adjustPrefsOnly = 0;	/* force complete SPF run */
		isis_spf((desc->lspType == L1LSType) ? 1 : 2);
		return;
	}
	
	/* STEVE XXX - does this have to be moved above the clause above? */
	desc->mustRegenerate = True;	/* force regeneration on next lspChangedTimeout */
	if (desc->schedRegenerate) {
		/*
		 *	The LSP has already been scheduled to be regenerated 
		 * 	via the timer job.
		 */
	} else {
		now = timeStamp;
		if (desc->lastGenerated + minLSPGenInterval <= now) {
			/* ok to regenerate LSP now */
			lspChangedTimeout(desc);
		} else {
			/* must wait before rebuilding */
			desc->schedRegenerate = True;
                	desc->timer = setTimer((desc->lastGenerated + minLSPGenInterval) - now,
                        			lspChangedTimeout, desc);
		}
	}
}

/*
 *	The adjacency 'adj' is down. Remove the entry in the LSP about this
 *	adjacency and rebuild the LSP.
 */
void
lspAdjDown(c, adj)
CircuitEntry	*c;
AdjacencyEntry	*adj;
{
	switch(adj->adjacencyType) {
		case ES:
			if ((c->circuitType == Broadcast) && (adj->type == AutoConfig)) {
				delESNeighbor (adj, c->l1PLSP, zeroMetric,
					adj->numIds, adj->neighborInfo);
			} else {
				delESNeighbor(adj, L1LSP, c->l1Metric, 
					adj->numIds, adj->neighborInfo);
			}
			break;
		case L2IS:
			if (c->circuitType == Broadcast) {
				delISNeighbor(c->l2PLSP, zeroMetric, 
					appendZero(adj->neighborSysID));
			} else {
				assert(c->circuitType == Pt2Pt);
				if (!adj->level2Only) {
					delISNeighbor(L1LSP, c->l1Metric, 
						appendZero(adj->neighborSysID));
				}
				delISNeighbor(L2LSP, c->l2Metric, 
					appendZero(adj->neighborSysID));
			}
			break;
		case L1IS:
			if (c->circuitType == Broadcast) {
				delISNeighbor(c->l1PLSP, zeroMetric, 
					appendZero(adj->neighborSysID));
			} else {
				assert(c->circuitType == Pt2Pt);
				delISNeighbor(L1LSP, c->l1Metric, 
					appendZero(adj->neighborSysID));
			}
			break;
		default:
			;
	}
}

/* extract the pertinent info from the LSP */
int
parseLSP(buf, len, sig)
u_char		*buf;
int			len;
LSSignature	*sig;
{
	LSPHeader	*hdr = (LSPHeader *)buf;
	u_short		realLen;

	switch (hdr->packetType) {
		case L1LSType:
			sig->level = 1;
			break;
		case L2LSType:
			sig->level = 2;
			break;
		default:
			assert(False);
	}
	bcopy((caddr_t)&hdr->lspId, (caddr_t)&sig->id, sizeof(LSPID));
	U16toHost(hdr->remainingLifetime, sig->lifetime);
	U16toHost(hdr->checksum, sig->checksum);
	U32toHost(hdr->sequenceNumber, sig->seqNum);
	U16toHost(hdr->pduLength, realLen);
	if (realLen < len)
		len = realLen;
	return(len);
}

/* 
 *	True if sequence numbers are the same and either both have non-zero
 *	ttl or both have zero ttl 
 */
Boolean
equalLSP(sig1, sig2)
LSSignature	*sig1, *sig2;
{
	return(sig1->seqNum == sig2->seqNum && (
		((sig1->lifetime == 0) && (sig2->lifetime == 0)) ||
		((sig1->lifetime != 0) && (sig2->lifetime != 0))));
}

/*
 *	True if sig1 is older than sig2
 */
Boolean
olderLSP(sig1, sig2)
LSSignature	*sig1, *sig2;
{
	if (sig1->seqNum == sig2->seqNum)
		return((sig1->lifetime != 0) && (sig2->lifetime == 0));
	else
		return(sig1->seqNum < sig2->seqNum);
}


/*
 *	Section 7.3.16.4: LSP arrived with zero lifetime, but it exists in
 *	the database
 */
void
processExpiredLSP(c, buf, len, newSig, dbLSP)
CircuitEntry	*c;
u_char			*buf;
int				len;
LSSignature		*newSig;	/* signature from new LSP */
LSEntry			*dbLSP;
{
	IFTRACE(T_LSPINPUT)
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("LSPinput(expired): %s",
			      LSSigToStr(newSig)));
	ENDTRACE

        if ((equalID(systemID, newSig->id.sourceID, 6)) &&
                (!locallyGenerated(dbLSP))) {
                isisCounters.purgeOwnLSP++;
#ifdef	PROTO_SNMP
		{
		    IsisMibEntry	*pMibEntry;
		    IsisSysEntry	*pSysEntry;

		    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
		    pSysEntry = &pMibEntry->isisSysEntry;

		    ++pSysEntry->isisSysOwnLSPPurges;	/* Isis-Mib */

		}
#endif	/* PROTO_SNMP */
        }

	if ((equalID(systemID, newSig->id.sourceID, 6)) && (locallyGenerated(dbLSP))) {
		/* 
		 *	LSP is from us 
		 */
		if (dbLSP->signature.lifetime == 0) {
			/* 
			 *	Our copy has zero lifetime, just ack (step b.2) 
			 */
			ackLSP(c, dbLSP);
		} else {
			/* 
			 *	Our copy has non-zero lifetime, flood it (step c) 
			 */
			updateSeqAndFlood(dbLSP, newSig->seqNum);
		}
	} else if (olderLSP(newSig, &dbLSP->signature)) {
		/*
		 *	Received LSP is older than database copy, so send
		 *	current version back (step b.3)
		 */
		sendLSP(c, dbLSP);
	} else if ((equalLSP(newSig, &dbLSP->signature)) && 
		dbLSP->signature.lifetime == 0) {
		/*
		 *	LSPs are equal, both have lifetime of zero, so
		 *	just ack. (step b.2)
		 */
		ackLSP(c, dbLSP);
	} else {
		/*
		 *	LSP is newer than database copy, or equal to the
		 *	database copy, but the database copy has not yet
		 *	expired. This LSP was not generated by us. 
		 *	flood and ack. Note: LSP will be added to age list with
		 *	zero lifetime which will cause it to expire immediately. It will
		 *	then be retained for zeroAgeLifetime as per normal LSP expiration.
		 */
		if (updateLSEntry(dbLSP, buf, len, newSig))
			ackAndFlood(c, dbLSP);
		else
                        enterLSPOverload(newSig);
	}
} 

/*
 *	An LSP has been received that is expired.
 *	We have no knowledge of the LSP. Ack it and throw it away.
 */
void
processExpiredNewLSP(c, buf, len, newSig)
CircuitEntry	*c;
u_char			*buf;
int				len;
LSSignature		*newSig;	/* signature from new LSP */
{
	IFTRACE(T_LSPINPUT)
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("LSPinput(new&expired): %s",
			      LSSigToStr(newSig)));
	ENDTRACE

	/* 
	 * STEVE XXX - protocol error here?  Clause 7.3.16.4 specifies:
	 * a) if no LSP is in memory, then the IS shall
	 *    1) send an ACK of the LSP on circuit C, but
	 *    2) shall not retain the LSP after the ACK has been sent
	 * 
	 * This code seems to violate (1) above.
	 */ 

	/* only send an ack on pt2pt circuits */
	if (c->circuitType == Pt2Pt) {
		sendSpecificPSNP(c, newSig->level, newSig);
	}
}

void
processOkNewLSP(c, buf, len, newSig)
CircuitEntry	*c;
u_char			*buf;
int				len;
LSSignature		*newSig;	/* signature from new LSP */
{
	LSEntry		*ent = newLSEntry(buf, len, newSig);

	IFTRACE(T_LSPINPUT)
		trace_only_tf(isis_trace_options,
			      0,
			      ("LSPinput(new): %s <%d>",
			       LSSigToStr(newSig),
			       len));
	ENDTRACE

	if (ent == NULL) {
                enterLSPOverload(newSig);
	} else {
        	if (equalID(systemID, newSig->id.sourceID, 6)) {
			/* 
			 * This is ours from a previous incarnation, and we haven't
			 * yet built ours for this incarnation, so purge the old one
			 * as per 7.3.15.1.c.
			 */
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("IS-IS purging my previous incarnation's LSP: %s",
				      LSSigToStr(newSig)));
			purgeLSP(ent);
		} else {
			/*
		 	 * Ack the sender and flood to everyone else
		 	 */
			ackAndFlood(c, ent);
		}
	}
}

/*
 *	Process an LSP that is not expired and already exists in the
 *	database (see 7.3.15.1)
 */
void
processOkLSP(c, buf, len, newSig, dbLSP)
CircuitEntry	*c;
u_char			*buf;
int				len;
LSSignature		*newSig;	/* signature from new LSP */
LSEntry			*dbLSP;
{
	IFTRACE(T_LSPINPUT)
		tracef("LSPinput(found): %s <%d>", LSSigToStr(newSig), len);
		trace_only_tf(isis_trace_options,
			      0,
			      (" (%s)",
			       LSSigToStr(&dbLSP->signature)));
	ENDTRACE

	if (equalLSP(newSig, &dbLSP->signature)) {
		if (newSig->checksum == dbLSP->signature.checksum) {
			/* 
			 *	LSPs are really the same. Ack the one received 
			 *	(step 2)
			 */
			ackLSP(c, dbLSP);
		} else {
			/* 
			 *	Section 7.3.16.2: LSP confusion
			 *
			 *	LSPs claim to be equal, but the checksums differ.
			 *	If the LSP is from us, then inc the sequence number
			 *	and flood it. If the LSP is not from us,
			 *	purge it
			 */
			if ((equalID(systemID, newSig->id.sourceID, 6)) && (locallyGenerated(dbLSP))) {
				/* 
				 *	LSP was originated from us 
				 */
				assert(equalID(newSig->id.sourceID,dbLSP->signature.id.sourceID, 6));
				
				updateSeqAndFlood(dbLSP, dbLSP->signature.seqNum);
			} else {
				/* the LSP is not from us, purge it */
				purgeLSP(dbLSP);
			}
		}
	} else if (olderLSP(newSig, &dbLSP->signature)) {
		/* 
		 *	the received LSP is older than the database copy, so 
		 *	send the database copy back
		 *	(step d.3)
		 */
		sendLSP(c, dbLSP);
	} else { 
		/*	The LSP is newer than the database copy */

		if (equalID(systemID, newSig->id.sourceID, 6)) {
			/* 
			 *	The LSP appears
			 *	to be from us. If we really did generate it, then 
			 *	increase the sequence number to make it newer and
			 *	flood
			 */
			if (locallyGenerated(dbLSP)) {
				/* 
				 * STEVE - fixed this to jump sequence number to
				 * be > that of incoming LSP.  It used to be:
				 * updateSeqAndFlood(dbLSP, dbLSP->signature.seqNum);
				 */
				updateSeqAndFlood(dbLSP, newSig->seqNum);
			} else {
				/*
				 *	Claims to be from us, but we did not generate it.
				 *	Purge it.
				 */
				purgeLSP(dbLSP);
			}
		} else {
			/*
			 *	The LSP is not
			 *	from us. Overwrite the database copy, ack
			 *	the sender, and flood to other neighbors
			 */
			if (updateLSEntry(dbLSP, buf, len, newSig))
				ackAndFlood(c, dbLSP);
			else
                                enterLSPOverload(newSig);
		}
	}
}

/*
 *	Process an incoming LSP
 *
 *	This code is loosly based upon the formal specification of the
 *	update process from the Network Routing Layer Functional Specification
 *	(Version T3.0.4). This code embodies functionality from the DP spec
 *	sections 7.3.15, 7.3.16.1, and 7.3.16.2
 */
void
processLSP(c, level, buf, len)
CircuitEntry	*c;
int				level;		/* level 1 or 2 */
u_char			*buf;
int				len;
{
	LSSignature	sig;
	LSEntry		*ent;

	len = parseLSP(buf, len, &sig);

	if (sig.checksum == 0)
		sig.lifetime = 0;

	if (sig.lifetime != 0) {
		LSPHeader	*hdr = (LSPHeader *)buf;
		if (iso_cksum(&hdr->lspId, len-12, 0) || (sig.lifetime > maximumAge)) { 
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("Corrupted LSP received: %s",
				      LSSigToStr(&sig)));
                        isisCounters.corruptLSPDetected++;
#ifdef	PROTO_SNMP
			{
			    IsisMibEntry	*pMibEntry;
			    IsisSysEntry	*pSysEntry;

			    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
			    pSysEntry = &pMibEntry->isisSysEntry;

			    ++pSysEntry->isisSysCorrLSPs;	/* Isis-Mib */

			}
#endif	/* PROTO_SNMP */
                        c->corruptedLSPs++;
			IFTRACE(T_DUMPLSP)
				dumpBuffer(buf, len);
			ENDTRACE
			hostToU16(0, hdr->checksum);
			/* updateLifetime will change ttl to zero in buf */
			sig.checksum = sig.lifetime = 0;
		}
	}
	ent = locateLSPByID(level, sig.id);

	if (sig.lifetime == 0) {
		if (ent)
			processExpiredLSP(c, buf, len, &sig, ent);
		else
			processExpiredNewLSP(c, buf, len, &sig);
	} else {
		if (ent)
			processOkLSP(c, buf, len, &sig, ent);
		else
			processOkNewLSP(c, buf, len, &sig);
	}
/* 	dumpLSPList();*/
}

/*
 *	Initiate a network wide purge of all pseudonode LSPs at the level
 *	specified (set ttl to zero). This assumes that every one of
 *	my pseudonode LSPs has been created and stored in the database
 *	(ie. lspEntry is not NULL)
 */
void
purgeMyPseudoLSP(c, level)
CircuitEntry	*c;
int				level;
{
	LSPGroup	*grp = (level==1) ? c->l1PLSP : c->l2PLSP;
	LSPDesc		*desc;

	IterateDLListForw(desc, &grp->list, LSPDesc *) {
		desc->lspInitLifetime = 0;
		markForDeletion(desc->lspEntry, zeroAgeLifetime);
		lspChanged(desc);
	}
}

/*
 *	Force all of my pseudonode LSPs to be transmitted
 *	Reset their lifetime to maximum age
 */
void
transmitMyPseudoLSP __PF2(c, CircuitEntry *,
			  level, int)
{
	LSPGroup	*grp = (level==1) ? c->l1PLSP : c->l2PLSP;
	LSPDesc		*desc;

	IterateDLListForw(desc, &grp->list, LSPDesc *) {
		if ((desc->lspEntry) && (desc->lspEntry->onDeletedList == True))
			removeFromDeletedList(desc->lspEntry);
		desc->lspInitLifetime = maximumAge;
		/* send it immediately (don't holddown on my being elected) */
		lspForceTransmit(desc);		
	}
}

/*
 *      Leave wait state. Clear hippity bit and re-issue #0 lsp
 */
void
clearLSPOverload(desc)
LSPDesc *desc;
{
#ifdef	PROTO_SNMP
      	IsisMibEntry	*pMibEntry;
	IsisSysEntry	*pSysEntry;

	pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	pSysEntry = &pMibEntry->isisSysEntry;		/* Isis-Mib */
#endif	/* PROTO_SNMP */

        if (desc->lspType == L1LSType) {
                l1HippityBit = False;
#ifdef	PROTO_SNMP
	        pSysEntry->isisSysL1State = 2;		/* Isis-Mib */
#endif	/* PROTO_SNMP */
        } else {
                l2HippityBit = False;
#ifdef	PROTO_SNMP
		pSysEntry->isisSysL2State = 2;		/* Isis-Mib */
#endif	/* PROTO_SNMP */
        }
        lspForceTransmit(desc);
}

static int      l1Timer, l2Timer;       /* timers used for maintaining wait state */

/*
 *      Enter overload condition.
 *      Flood #0 LSP out with hippity bit set. Wait for
 *      WaitingTime seconds, then continue normally. If we are already in
 *      wait state, restart timer.
 */
void
enterLSPOverload(sig)
LSSignature     *sig;
{
        LSPGroup        *grp;
        LSPDesc         *desc;
        int                     Timer;

        trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("LSP Overload (level %d)",
		      sig->level));

        /* determine which level */
        if (sig->level == 1) {
                isisCounters.l1LSPOverload++;
#ifdef	PROTO_SNMP
		{
		    IsisMibEntry	*pMibEntry;
		    IsisSysEntry	*pSysEntry;

		    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
		    pSysEntry = &pMibEntry->isisSysEntry;

		    ++pSysEntry->isisSysLSPL1DbaseOloads;	/* Isis-Mib */
		    pSysEntry->isisSysL1State = 3;

		}
#endif	/* PROTO_SNMP */

                if (l1HippityBit) {
                        resetTimer(l1Timer, waitingTime);
                        return;
                }
                l1HippityBit = True;
                grp = L1LSP;
        } else {
                isisCounters.l2LSPOverload++;
#ifdef	PROTO_SNMP
		{
		    IsisMibEntry	*pMibEntry;
		    IsisSysEntry	*pSysEntry;

		    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
		    pSysEntry = &pMibEntry->isisSysEntry;

		    ++pSysEntry->isisSysLSPL2DbaseOloads;	/* Isis-Mib */
		    pSysEntry->isisSysL2State = 3;
		}
#endif	/* PROTO_SNMP */

                if (l2HippityBit) {
                        resetTimer(l2Timer, waitingTime);
                        return;
                }
                l2HippityBit = True;
                grp = L2LSP;
        }

        /* flood the #0 LSP at the appointed level */
        IterateDLListForw(desc, &grp->list, LSPDesc *) {
                if (desc->lspNumber == 0)
                        lspForceTransmit(desc);
        }

        /* set a timer to clear the hippity bit */
        Timer = setTimer(waitingTime, clearLSPOverload, desc);
        if (sig->level == 1)
                l1Timer = Timer;
        else
                l2Timer = Timer;
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
