/*
 *  isis_flood.c,v 1.11 1993/01/07 22:39:17 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"

block_t isis_lsentry_block;
block_t isis_lseChangeList_block;
block_t isis_lspbuf_block[13];	/* size is (index * 128) */

static struct _lseChangeList *lseChangeList = 0;

/*
 *	Hash table used to locate LSPs quickly
 *	Hash is based upon the sourceID and chains LSPs entries
 *	off of each entry in the table.
 */

static LSEntry *L1Hash[L1HashTableSize];
static LSEntry *L2Hash[L2HashTableSize];

static u_short 
IDHash(sourceID)
LSPID	sourceID;
{
	u_short	hash = 0;
	int i;
	u_char	*cp = (u_char *)&sourceID;

	for (i=0; i<7; i++)
		hash ^= *cp++;
	
	return(hash);
}


/* insert LSP into hash table based upon sourceID address */
static void
insertLSPByID __PF2(lsp, LSEntry *,
		    sourceID, LSPID)
{
	if (lsp->signature.level == 1) {
		u_short indx = IDHash(sourceID) % L1HashTableSize;
		if (L1Hash[indx]) {
			lsp->hashNext = L1Hash[indx];
		}
		L1Hash[indx] = lsp;
	} else {
		u_short indx = IDHash(sourceID) % L2HashTableSize;
		assert(lsp->signature.level == 2);
		if (L2Hash[indx]) {
			lsp->hashNext = L2Hash[indx];
		}
		L2Hash[indx] = lsp;
	}
}

/*
 *	Remove 'ent' from hash table
 */
static void
removeLSP __PF1(ent, LSEntry *)
{
	LSEntry	*scan, *lastScan = (LSEntry *) 0;
	u_short	indx;

	if (ent->signature.level == 1) {
		indx = IDHash(ent->signature.id) % L1HashTableSize;
		if (L1Hash[indx] == ent) {
			L1Hash[indx] = ent->hashNext;
			return;
		} else
			scan = L1Hash[indx];
	} else {
		assert(ent->signature.level == 2);
		indx = IDHash(ent->signature.id) % L2HashTableSize;
		if (L2Hash[indx] == ent) {
			L2Hash[indx] = ent->hashNext;
			return;
		} else
			scan = L2Hash[indx];
	}
	for ( ; scan; lastScan=scan, scan=scan->hashNext) {
		if (scan == ent) {
			lastScan->hashNext = ent->hashNext;
			return;
		}
	}
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("removeLSP: can't find entry"));
}

/*
 *	Sorted LSP list. Two sorted lists of LSEntries are maintained - a
 *	level 1 and a level 2 list. The lists are sorted in ascending order
 *	based upon LSPID. These lists are used to build and process
 *	sequence number pdus. The lists are singly linked.
 */
static LSEntry *sortL1 = NULL, *sortL2 = NULL;

/*
 *	Return the head of the sort list.
 */
LSEntry *
firstLSP(level)
int	level;
{
	return(level == 1 ? sortL1 : sortL2);
}

/*
 *	Add 'ent' to proper sort list. This is basically an insertion sort
 */
static void
addToSortList __PF1(ent, LSEntry *)
{
	LSEntry	**listPtr, *scan, *lastScan = NULL;

	listPtr = (ent->signature.level == 1) ? &sortL1 : &sortL2;

	if (*listPtr == NULL) {
		*listPtr = ent;
	} else {
		for (scan = *listPtr; scan; lastScan = scan, scan = scan->sortNext) {
			if (LSPIDcmp(&scan->signature.id, &ent->signature.id) > 0) {
				if (scan == *listPtr) {
					ent->sortNext = *listPtr;
					*listPtr = ent;
				} else {
					ent->sortNext = lastScan->sortNext;
					lastScan->sortNext = ent;
				}
				return;
			}
		}
		lastScan->sortNext = ent;
	}
}

/*
 *	Remove 'ent' from the sort list.
 */
static void
rmFromSortList __PF1(ent, LSEntry *)
{
	LSEntry	**listPtr, *scan, *lastScan = NULL;
	extern LSEntry *lastL1Ent, *lastL2Ent;

	/*
	 *	Check if 'ent' is pointed to by lastLnEnt (maintained for 
	 *	transmission of PSNPs). If so, set lastLnEnt to NULL
	 */
	if (ent == lastL1Ent)
		lastL1Ent = NULL;
	else if (ent == lastL2Ent)
		lastL2Ent = NULL;

	listPtr = (ent->signature.level == 1) ? &sortL1 : &sortL2;
	if (*listPtr) {
		for (scan = *listPtr; scan; lastScan = scan, scan = scan->sortNext) {
			if (scan == ent) {
				if (scan == *listPtr) {
					*listPtr = ent->sortNext;
				} else {
					lastScan->sortNext = ent->sortNext;
				}
				return;
			}
		}
		lastScan->sortNext = NULL;
	}
}

/* Store LSEntry in hash table and sorted list */
void
storeLSEntry __PF1(ent, LSEntry *)
{
	insertLSPByID(ent, ent->signature.id);
	addToSortList(ent);
}


/*
 *	Allocate an LSP Entry & initialize
 *	Return null or pointer to LSP entry
 */
LSEntry *
newLSEntry __PF3(buf, u_char *,
		 len, int, 
		 sig, LSSignature *)
{
	LSEntry	*ent = (LSEntry *) task_block_alloc(isis_lsentry_block);

	isisCounters.lsentries++;

	if (ent == NULL)
		return(NULL);
	
	if (len > 0) {
		/* allocate a block rounded up to nearest 128 bytes */
		ent->allocLen = (len + 127) & 0xffffff80;
		ent->buf = (u_char *) task_block_alloc(isis_lspbuf_block[ent->allocLen >> 7]);
		if (ent->buf == NULL)
			return(NULL);
		isisCounters.lspbufs++;
		isisCounters.lspbytes += ent->allocLen;
	} else {
		ent->buf = NULL;
	}

	ent->signature = *sig;
	ent->len = len;
	ent->arrivalTimestamp = timeStamp;
	ent->originalLifetime = ent->remainingTime = sig->lifetime;
	if (len) bcopy((caddr_t) buf, (caddr_t) ent->buf, len);
	storeLSEntry(ent);
	ageListInsert(normalLSPAge, (u_char *) ent);
	adjustPrefsOnly = 0;
	signalDecisionProcess(ent->signature.level);

	return(ent);
}

/*
 *	Update LSEntry 'ent' with new contents. This may fail if we need
 *	to allocate more memory to store the new buf. Return false if we
 *	can't allocate, otherwise true.
 */
Boolean
updateLSEntry __PF4(ent, LSEntry *,
		    buf, u_char *,
		    len, int,
		    sig, LSSignature *)
{
	Boolean	whatMeWorry = False;
	byte *cp, *cp0, seq[4];
	byte *optcode, *optval;
	struct _lseChangeList *tmp;
	long d0, d1, dx, dy;

	assert(ent->lspDesc == NULL);		/*should not call this on my own LSP */

	/*
	 *	Determine if this new LSP is sufficently different that we
	 *	ought to signal the decision process. 
	 */
	if ((ent->len == len) && (sig->lifetime) && (ent->signature.lifetime) && (ent->signature.seqNum == (sig->seqNum-1))) {
		/* 
		 * Perhaps this is just a refreshed LSP, so do the incremental Fletcher
		 * shuffle courtesy of Anastase Nakassis, "Fletcher's Error Detection 
		 * Algorithm:  How to implement it efficiently and how to avoid the most
		 * common pitfalls," ACM CCR, Vol. 18, No. 5, October 1988, pp. 63-88.
		 */
#ifdef	notyet
		/* STEVE XXX - ok, so this is only 1 off... */
		cp = (byte *) &sig->seqNum;
		cp0 = (byte *) &ent->signature.seqNum;
		seq[0] = (*cp >= *cp0) ? *cp - *cp0 : *cp + (255 - *cp0);
		seq[1] = (*++cp >= *++cp0) ? *cp - *cp0 : *cp + (255 - *cp0);
		seq[2] = (*++cp >= *++cp0) ? *cp - *cp0 : *cp + (255 - *cp0);
		seq[3] = (*++cp >= *++cp0) ? *cp - *cp0 : *cp + (255 - *cp0);
		d0 = d1 = 0;
		d1 += (d0 += (long) (seq[0]));
		d1 += (d0 += (long) (seq[1]));
		d1 += (d0 += (long) (seq[2]));
		d1 += (d0 += (long) (seq[3]));
		dx = (254*d0 + (255-d1)) % 255; 
		dy = ((255-dx) + (255-d0)) % 255;
		if (!dx) dx = 255;
		if (!dy) dy = 255;
		if ((((byte) (ent->signature.checksum & 0xFF) + dy) != (sig->checksum & 0xFF)) ||
		    ((((byte) (ent->signature.checksum >> 8) & 0xFF) + dx) != ((sig->checksum >> 8) & 0xFF))) {
			whatMeWorry = True;
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("SPF needed for %s, diff ck = %04x, df = %04x, dx = %d,dy = %d", 
				      LSSigToStr(sig),
				      (short) sig->checksum-ent->signature.checksum,
				      (short) ((dx << 8) | dy), dx, dy));
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("new seq = %08x, old seq = %08x, diff bytes = %08x",
				      sig->seqNum,
				      ent->signature.seqNum,
				      * ((u_long *) seq)));
		} else {
		    trace_log_tf(isis_trace_options,
				 0,
				 LOG_ERR,
				 ("LSP refresh - SPF avoided for %s",
				  LSSigToStr(sig)));
		}
#else	/* notyet */
		if (!bcmp((caddr_t) ent->buf+26, (caddr_t) buf+26, ent->len-26))
			whatMeWorry = True;
		else {
		    trace_log_tf(isis_trace_options,
				 0,
				 LOG_ERR,
				 ("LSP refresh for %s",
				  LSSigToStr(sig)));
		}
#endif	/* notyet */
	} else if ((ent->len != len) || (ent->signature.checksum != sig->checksum) ||
		(!bcmp((caddr_t) ent->buf, (caddr_t) buf, ent->len)))
			whatMeWorry = True;

	if (ent->allocLen < len) {
		/* need to enlarge buf */
		if (ent->buf) {
			task_block_free(isis_lspbuf_block[ent->allocLen >> 7], ent->buf);
			isisCounters.lspbufs--;
			isisCounters.lspbytes -= ent->allocLen;
		}
		ent->allocLen = (len + 127) & 0xffffff80;
		ent->buf = (u_char *) task_block_alloc(isis_lspbuf_block[ent->allocLen >> 7]);
		if (ent->buf == NULL) {
			ent->allocLen = 0;
			return(False);
		}
		isisCounters.lspbufs++;
		isisCounters.lspbytes += ent->allocLen;
	}
	ent->signature = *sig;
	ent->arrivalTimestamp = timeStamp;
	ent->len = len;
	bcopy((caddr_t) buf, (caddr_t) ent->buf, len);

	/*
	 *	This entry could be on the deleted list. If so, remove it from
	 *	that and add to the normal list. 
	 */
	if (ent->onDeletedList) {
		removeFromDeletedList(ent);
	} else {
		ageListRemove(normalLSPAge, (u_char *) ent);
	}
	ent->originalLifetime = ent->remainingTime = sig->lifetime;
	ageListInsert(normalLSPAge, (u_char *) ent);

	if (whatMeWorry) {
		if (adjustPrefsOnly) {
			/* assume we only need to adjust prefixes until determined otherwise */
			optcode = buf + sizeof(struct is_lsp_header);
			optval = optcode + 2;
			if ((*optcode == leafNode) && (*optval = 1)) {
				/* prefixes only - add this LS entry to change list */
                		tmp = (struct _lseChangeList *) task_block_alloc(isis_lseChangeList_block);
                		isisCounters.lseChangeList++;
                		tmp->next = lseChangeList;
                		tmp->lse = ent;
                		lseChangeList = tmp;
				adjustPrefsOnly = 0; /* STEVE XXX - for now */
			} else {
				/* force complete SPF run */
				adjustPrefsOnly = 0;
			}
		}
		signalDecisionProcess(ent->signature.level);
	}

	return(True);
}

void
removeFromDeletedList(ent)
LSEntry	*ent;
{
	assert(ent->onDeletedList == True);
	ageListRemove(deletedLSPAge, (u_char *) ent);
	ent->onDeletedList = False;
}

/* 
 *	return a pointer to (or NULL) the first matching LSPs 
 *	entry in hashtable 
 */
LSEntry *
locateLSPByID(level, id)
int		level;
LSPID	id;
{
	LSEntry	*ent;

	if (level == 1) {
		ent = L1Hash[IDHash(id) % L1HashTableSize];
	} else {
		assert(level == 2);
		ent = L2Hash[IDHash(id) % L2HashTableSize];
	}
	while (ent) {
		if (equalID(&id, &ent->signature.id, 8))
			return(ent);
		ent = ent->hashNext;
	} 
	return(NULL);
}

/* 
 *	return a pointer to (or NULL) the LSP with the lowest LSP number 
 *	in the hash table
 */
LSEntry *
locateLowestLSP __PF2(level, int,
		      id, LSPID)
{
	LSEntry	*ent, *poss = NULL;
	u_char	lowest = 255;

	if (level == 1) {
		ent = L1Hash[IDHash(id) % L1HashTableSize];
	} else {
		assert(level == 2);
		ent = L2Hash[IDHash(id) % L2HashTableSize];
	}
	while (ent) {
		if (equalID(&id, &ent->signature.id, 7)) {
			if (ent->signature.id.LSPNumber < lowest) {
				lowest = ent->signature.id.LSPNumber;
				poss = ent;
			}
		}
		ent = ent->hashNext;
	} 
	return(poss);
}

/*
 *	Insure that flag bits are only set if there is a circuit
 *	enabled at that bit position
 */
void
setFlags __PF3(flags, Boolean *,	/* array MaximumCircuits of flags */
	       mode, int,		/* which flags to set */
	       c, int)			/* optional circuit identifier */
{
	int i;

	if (mode == AllCircuits) {
		for (i=0; i<MaximumCircuits; i++) {
			flags[i] = False;
			if (circuitList[i])
				flags[i] = True;
		}
	} else {
		assert(mode == SingleCircuit);
		flags[c] = True;
	}
}


void
clrFlags __PF3(flags, Boolean *,
	       mode, int,
	       c, int)
{
	int i;

	if (mode == AllCircuits) {
		for (i=0; i<MaximumCircuits; i++)
			flags[i] = False;
	} else {
		assert(mode == SingleCircuit);
		flags[c] = False;
	}
}

/*
 *	Return true if is is ok to flood an lsp of the level specified on the
 *	circuit.
 *
 *	If level is 1, there must be at least 1 L1 adj or at least one L2
 *		adj not marked Level 2 only
 *
 *	If level is 2, there must be at least one L2 adj.
 */
static int
okToFlood __PF2(c, CircuitEntry *,
		level, int)
{
	AdjacencyEntry  *scan;

	IterateDLListForw(scan, &c->isAdjs->links, AdjacencyEntry *) {
		if (scan->state == AdjUp) {
			if (level == 2 && scan->adjacencyType == L2IS)
				return(True);
			if (level == 1) {
				if ((scan->adjacencyType == L1IS) || 
					((scan->adjacencyType == L2IS) && (!scan->level2Only)))
					return(True);
			}
		}
	}
	return(False);
}


/* 
 * Print LSP IS Neighbors in human-readable form.
 */
static void
printLSPISN __PF4(fd, FILE *,
		  lsp, struct is_lsp_header *,
		  cp, char *,
		  len, u_char)
{
	int metric;
	int idLen;
	int vFlag;
	char *EndOfField;
	char *isn;
	char pseudo;

	EndOfField = cp + len;
	if (lsp->idLen == 0) 
		idLen = 6;
	else if (lsp->idLen == 255)
		idLen = 0;
	else idLen = lsp->idLen;
	vFlag = *cp++;
#define	PRINTISN \
	metric = *cp; \
	cp += 4; \
	isn = cp; \
	cp += idLen + 1; \
	pseudo = (isn[idLen] == 0) ? 'N' : 'P'; \
	if (fd) fprintf(fd, "%s[%c%x] (%d)", IDToStr((u_char *) isn, idLen), pseudo, isn[idLen], metric); \
	else tracef("%s[%c%x] (%d)", IDToStr((u_char *) isn, idLen), pseudo, isn[idLen], metric); 
	while (cp < EndOfField) {
		if (fd) 
			if (vFlag) fprintf(fd, "  vISNs: ");
			else fprintf(fd, "  ISNs: ");
		else 
			if (vFlag) tracef("  vISNs: ");
			else tracef("  ISNs: ");
		PRINTISN;
		if (cp >= EndOfField) {
			if (fd) fprintf(fd, "\n");
			else trace_log_tf(isis_trace_options,
					  0,
					  LOG_INFO,
					  (NULL));
			break;
		}
		if (fd) fprintf(fd, ", ");
		else tracef(", ");
		PRINTISN;
		if (fd) fprintf(fd, "\n");
		else trace_log_tf(isis_trace_options,
				  0,
				  LOG_INFO,
				  (NULL));
	}
}     

/* 
 * Print LSP ES Neighbors in human-readable form.
 */
static void
printLSPESN __PF4(fd, FILE *,
		  lsp, struct is_lsp_header *,
		  cp, char *,
		  len, u_char)
{
	int metric;
	int idLen;
	char *EndOfField;
	char *esn;

	EndOfField = cp + len;
	if (lsp->idLen == 0) 
		idLen = 6;
	else if (lsp->idLen == 255)
		idLen = 0;
	else idLen = lsp->idLen;
#define	PRINTESN \
	esn = cp; \
	cp += idLen; \
	if (fd) fprintf(fd, "%s (%d)", IDToStr((u_char *) esn, idLen), metric); \
	else tracef("%s (%d)", IDToStr((u_char *) esn, idLen), metric); 
	metric = *cp; 
	cp += 4; 
	while (cp < EndOfField) {
		if (fd) fprintf(fd, "  ESNs: ");
		else tracef("  ESNs: ");
		PRINTESN;
		if (cp >= EndOfField) {
			if (fd) fprintf(fd, "\n");
			else trace_log_tf(isis_trace_options,
					  0,
					  LOG_INFO,
					  (NULL));
			break;
		}
		if (fd) fprintf(fd, ", ");
		else tracef(",  ");
		PRINTESN;
		if (fd) fprintf(fd, "\n");
		else trace_log_tf(isis_trace_options,
				  0,
				  LOG_INFO,
				  (NULL));
	}
}     

/* 
 * Print LSP Area Addresses in human-readable form.
 */
static void
printLSPArea __PF3(fd, FILE *,
		   cp, char *,
		   len, u_char)
{
	char *EndOfField;
	int alen;
	char *area;
	sockaddr_un *sa; 

	EndOfField = cp + len;
#define	PRINTAREA \
	alen = *cp++; \
	area = cp; \
	cp += alen; \
	sa = sockbuild_iso((byte *) area, alen); \
	if (fd) fprintf(fd, "%A", sa); \
	else tracef("%A", sa); \

	while (cp < EndOfField) {
		if (fd) fprintf(fd, "  AA: ");
		else tracef("  AA: ");
		PRINTAREA;
		if (fd) fprintf(fd, "\n");
		else trace_log_tf(isis_trace_options,
				  0,
				  LOG_INFO,
				  (NULL));
	}
}     

/* 
 * Print LSP Reachable Address Prefix Neighbors in human-readable form.
 */
static void
printLSPPref __PF3(fd, FILE *,
		   cp, char *,
		   len, u_char)
{
	int metric;
	int prefLen;
	char *EndOfField;
	char *prefix;
	char metricType;
	sockaddr_un *sa;

	EndOfField = cp + len;
#define	PRINTPREFIX \
	prefLen = (*cp++ + 1) >> 1; \
	prefix = cp; \
	cp += prefLen; \
	sa = sockbuild_iso((byte *) prefix, prefLen); \
	if (fd) fprintf(fd, "%A", sa); \
	else tracef("%A", sa); \
	if (fd) fprintf(fd, " (%c.%d)", metricType, metric & 0x3f); \
	else tracef(" (%c.%d)", metricType, metric & 0x3f); 
	metric = *cp;
	metricType = (metric & 0x40) ? 'E' : 'I'; 
	cp += 4;
	while (cp < EndOfField) {
		if (fd) fprintf (fd, "  PREF: ");
		else tracef("  PREF: ");
		PRINTPREFIX;
		if (fd) fprintf(fd, "\n");
		else trace_log_tf(isis_trace_options,
				  0,
				  LOG_INFO,
				  (NULL));
	}
}     

/* 
 * Print protocols supported field in human-readable form.
 */
static void
printProtoSupported __PF3(fd, FILE *,
			  cp, char *,
		  	  len, u_char)
{
	char *EndOfField;
	int nlpid;

	EndOfField = cp + len;
#define	PRINTProto \
	nlpid = *cp++; \
	if (nlpid == OSI_NLPID) if (fd) fprintf(fd, "CLNP"); else tracef("CLNP"); \
	else if (nlpid == IP_NLPID) if (fd) fprintf(fd, "IP"); else tracef("IP"); \
	else if (fd) fprintf(fd, "0x%02x", nlpid); else tracef("0x%02x", nlpid); 
	if (fd) fprintf(fd, "  Protocols Supported: ");
	else tracef("  Protocols Supported: ");
	PRINTProto;
	while (cp < EndOfField) {
		if (fd) fprintf(fd, ", ");
		else tracef(", ");
		PRINTProto;
	}
	if (fd) fprintf(fd, "\n");
	else trace_log_tf(isis_trace_options,
			  0,
			  LOG_INFO,
			  (NULL));
}     

/* 
 * Print ISO authentication information.
 */
static void
printISOAuth __PF3(fd, FILE *,
		   cp, char *,
		   len, u_char)
{
	char *authinfo;
	int authType;

	authType = *cp++; 
	authinfo = cp; 
	if (fd) fprintf(fd, "  ISO Authentication: ");
	else tracef("  ISO Authentication: ");
	if (authType == 1) if (fd) fprintf(fd, "cleartext password\n"); 
				else {
				    trace_only_tf(isis_trace_options,
						  0,
						  ("cleartext password"));
				}
	else if (fd) fprintf(fd, "private\n"); else {
	    trace_only_tf(isis_trace_options,
			  0,
			  ("private"));
	}
}     

/* 
 * Print partition designated L2 IS in human-readable form.
 */
static void
printPDL2IS __PF4(fd, FILE *,
		  lsp, struct is_lsp_header *,
		  cp, char *,
		  len, u_char)
{
	int idLen;

	if (lsp->idLen == 0) 
		idLen = 6;
	else if (lsp->idLen == 255)
		idLen = 0;
	else idLen = lsp->idLen;
	if (fd) fprintf(fd, "  Partition Designated L2 IS: %s\n", IDToStr((u_char *) cp, idLen));
	else trace_log_tf(isis_trace_options,
			  0,
			  LOG_INFO,
			  ("  Partition Designated L2 IS: %s",
			   IDToStr((u_char *) cp, idLen)));
}     

/* 
 * Print IP interface addresses in human-readable form.
 */
static void
printLSPipIfAddr __PF3( fd, FILE *,
			cp, char *,
			len, u_char)
{
	char *EndOfField;
	char *addr;

	EndOfField = cp + len;
#define	PRINTipIfAddr \
	addr = cp; \
	cp += 4; \
	if (fd) fprintf(fd, "%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]); \
	else tracef("%d.%d.%d.%d", addr[0], addr[1], addr[2], addr[3]);
	while (cp < EndOfField) {
		if (fd) fprintf(fd, "  IP interfaces: ");
		else tracef("  IP interfaces: ");
		PRINTipIfAddr;
		if (cp >= EndOfField) {
			if (fd) fprintf(fd, "\n"); 
			else trace_log_tf(isis_trace_options,
					  0,
					  LOG_INFO,
					  (NULL));
			break;
		}
		if (fd) fprintf(fd, ",  ");
		else tracef(",  ");
		PRINTipIfAddr;
		if (fd) fprintf(fd, "\n");
		else trace_log_tf(isis_trace_options,
				  0,
				  LOG_INFO,
				  (NULL));
	}
}     

/* 
 * Print LSP IP internal reachability info in human-readable form.
 */
static void
printLSPipReach  __PF4(fd, FILE *,
		       cp, char *,
		       len, u_char,
		       internal, int)
{
	int metric;
	char *EndOfField;
	char *net;
	char *mask;
	char metricType;
	char buf[300];

	EndOfField = cp + len;
#define	PRINTipInt \
	metric = *cp; \
	net = &cp[4]; \
	mask = &cp[8]; \
	cp += 12; \
	sprintf(buf, "%d.%d.%d.%d\t%02x.%02x.%02x.%02x ", net[0],net[1],net[2],net[3],mask[0],mask[1],mask[2],mask[3]); \
	if (fd) fprintf(fd, "%s", buf); \
	else tracef("%s", buf); \
	if (internal) if (fd) fprintf(fd, "(%d)", metric); else tracef("(%d)", metric); \
	else { \
		metricType = (metric & 0x40) ? 'E' : 'I'; \
		if (fd) fprintf(fd, "(%c.%d)", metricType, metric & 0x3f); \
		else tracef("(%c.%d)", metricType, metric & 0x3f); \
	}
	while (cp < EndOfField) {
		if (fd) fprintf(fd, "  IP: ");
		else tracef("  IP: ");
		PRINTipInt;
		if (fd) fprintf(fd, "\n");
		else trace_log_tf(isis_trace_options,
				  0,
				  LOG_INFO,
				  (NULL));
	}
}     

/* 
 * Print implementation-specific leaf node option in human-readable form.
 */
static void
printLSPleafNode __PF3(fd, FILE *,
		       cp, char *,
		       len, u_char)
{
	if (*cp == 1) {
		if (fd) fprintf(fd, "  Prefixes Only\n");
		else trace_only_tf(isis_trace_options,
				   0,
				   ("  Prefixes Only"));
	} else {
		if (fd) fprintf(fd, "  Possible ISN LSP\n");
		else trace_only_tf(isis_trace_options,
				   0,
				   ("  Possible ISN LSP"));
	}
}

/* 
 * Print IP inter-domain info in human-readable form.
 */
static void
printLSPipInterDomInfo __PF3(fd, FILE *,
		   	     cp, char *,
		   	     len, u_char)
{
	int infoType;
	u_short asTag;
	isis_asp *asp;

	asp = (isis_asp *) cp;

	infoType = *cp++;
	switch(infoType) {
	case 0:
		if (fd) fprintf(fd, "  IDRPI: reserved (ignored)\n"); 
		else trace_log_tf(isis_trace_options,
				  0,
				  LOG_INFO,
				  ("  IDRPI: reserved (ignored)")); 
		break;
	case 1:
		/* locally defined format */
		if (fd) {
			fprintf(fd, "  IDRPI: attribute ID %d\n", asp->data); 
		} else {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_INFO,
				     ("  IDRPI: attribute ID %d\n",
				      asp->data)); 
		}
		break;
	case 2:
		/* AS tag */
		asTag = * (u_short *) cp;
		if (fd) fprintf(fd, "  IDRPI: AS %d\n", asTag); 
		else trace_log_tf(isis_trace_options,
				  0,
				  LOG_INFO,
				  ("  IDRPI: AS %d",
				   asTag)); 
		break;
	}
}     

/*
 * Print LSP contents (variable length fields) in human-readable
 * form.
 */
void
printLSPContents __PF3(fd, FILE *,
		       pdu, u_char *,
		       len, int)
{
	struct is_lsp_header *lsp;
	char *cp;
	u_char vcode;			/* variable length field code */
	u_char vlen;			/* variable length field length */

	lsp = (struct is_lsp_header *) pdu;
	cp = (char *) pdu + sizeof(struct is_lsp_header);	/* get to the option part */

	while (cp < (char *) (pdu + len)) {
		vcode = *cp++;
		vlen = *cp++;
		switch (vcode) {
		case LSPESNeighborCode:
			printLSPESN(fd, lsp, cp, vlen);
			break;
		case LSPISNeighborCode:
			printLSPISN(fd, lsp, cp, vlen);
			break;
		case LSPPrefixNeighborCode:
			printLSPPref(fd, cp, vlen); 
			break;
		case AreaAddressCode:
			printLSPArea(fd, cp, vlen);
			break;
		case AuthenticationCode:
			printISOAuth(fd, cp, vlen);
			break;
		case LSPPDL2ISCode:
			printPDL2IS(fd, lsp, cp, vlen);
			break;
		case ProtoSupportedCode:
			printProtoSupported(fd, cp, vlen);
			break;
		case IPExtReachCode:
			printLSPipReach(fd, cp, vlen, 0); 
			break;
		case IPIntReachCode:
			printLSPipReach(fd, cp, vlen, 1); 
			break;
		case IPIfAddrCode:
			printLSPipIfAddr(fd, cp, vlen);
			break;
		case IPInterDomInfo:
			printLSPipInterDomInfo(fd, cp, vlen);
			break;
		case leafNode:
			printLSPleafNode(fd, cp, vlen);
			break;
		default:
			if (fd) fprintf(fd, "  Unsupported Field (code %d)\n", vcode);
			else trace_log_tf(isis_trace_options,
					  0,
					  LOG_INFO,
					  ("  Unsupported Field (code %d)",
					   vcode));
		}
		cp += vlen;
	}
}

/*
 *	Transmit lsp in 'ent' on circuit 'c'
 */
static void
transmitLSP __PF2(c, CircuitEntry *,
		  ent, LSEntry *)
{
	updateLifetime(ent);
	IFTRACE(T_FLOODING)
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_INFO,
			     ("Flooding: %s: (%d bytes) %s",
			      c->name,
			      ent->len,
			      LSSigToStr(&ent->signature)));
	ENDTRACE

	IFTRACE(T_DUMPLSP)
                trace_log_tf(isis_trace_options,
			     0,
			     LOG_INFO,
			     ("LSP %s (%d bytes) - xmit on %s", 
			      LSSigToStr(&ent->signature),
			      ent->len,
			      c->name));
		IFTRACE(T_LSPCONTENT)
			printLSPContents(0, ent->buf, ent->len);
		ENDTRACE
	ENDTRACE
			
	transmitPacket(c, ent->signature.level == 1 ? AllL1ISmac : AllL2ISmac,
		ent->buf, ent->len);
}

/*
 *	Scan the list of lsps. For each LSEntry, transmit the LSP on
 *	any circuit where the SRM flag is set and the circuit is a
 *	pt-2-pt. Do not clear the SRM flag after transmission (this is
 *	down when an acknowledgement - via the seq number packet - is 
 *	received).
 */
void
floodPt2Pt __PF2(tip, task_timer *,
		 interval, time_t)
{
	int						level;

	for (level = 1; level < 3; level++) {
		LSEntry				*ent;
		for (ent = firstLSP(level); ent; ent = ent->sortNext) {
			int				i;
			CircuitEntry	*c;
			for (i=0; i<MaximumCircuits; i++) {
				if ((c = circuitList[i]) && 
					(c->circuitType == Pt2Pt) && 
					(ent->SRM[i])) {
					if (okToFlood(c, ent->signature.level)) {
						transmitLSP(c, ent);
					} else {
						/* take off of flood queue */
						clrFlags(ent->SRM, SingleCircuit, i);
					}
				}
			}
		}
	}
	task_timer_set(tip, (time_t) minLSPXmitInterval, (time_t) 0);
}

/*
 *	For every Broadcast circuit, transmit up to BLSPThrottle LSPs queued for 
 *	flooding on that circuit. Clear the SRM flag after transmission.
 */
void
floodBroadcast __PF2(tip, task_timer *,
		     interval, time_t)
{
	int level;
	CircuitEntry *c;
	LSEntry *ent;
	int i;
	int count, octets;
#define MAXOCTETS (48*1024)	

	for (level = 1; level <= 2; level++) {
		for (i=0; i<MaximumCircuits; i++) {
			if ((c = circuitList[i]) && (c->circuitType == Broadcast)) {
				/* this coding is a little sloppy */
				octets = 0;
				count = BLSPThrottle; 
				ent = c->lastFlooded[level-1];
				do {
					ent = (ent == (LSEntry *) 0) ? firstLSP(level) : ent->sortNext;
					if (ent) {
						if (ent->SRM[i] && okToFlood(c, ent->signature.level)) {
							transmitLSP(c, ent);
							/* STEVE - thank me for this most tremendous hack */
							octets += (ent->len > MLEN) ? (MSIZE << 1) + MCLBYTES : (MSIZE << 1);
							count--;
						}
						clrFlags(ent->SRM, SingleCircuit, i);
					}
				} while (ent && (octets < MAXOCTETS) && count);
				c->lastFlooded[level-1] = ent;
			}
		}
	}
	task_timer_set(tip, (time_t) minBLSPXmitInterval, (time_t) 0);
}

/*
 *	Map the pointer to CircuitEntry back to an index into the
 *	circuitList. It would be, like, a total bummer for this to
 *	fail.
 */
int
CEToIndex __PF1(c, CircuitEntry *)
{
	int	i;
	for (i=0; i<MaximumCircuits; i++) {
		if (circuitList[i] == c)
			return(i);
	}
	assert(False);
	return(0);
}

void
ackLSP __PF2(c, CircuitEntry *,
       	     ent, LSEntry *)
{
	clrFlags(ent->SRM, SingleCircuit, CEToIndex(c));
	if (c->circuitType == Pt2Pt) {
		setFlags(ent->SSN, SingleCircuit, CEToIndex(c));
	}
}

void
sendLSP __PF2(c, CircuitEntry *,
	      ent, LSEntry *)
{
	setFlags(ent->SRM, SingleCircuit, CEToIndex(c));
	clrFlags(ent->SSN, SingleCircuit, CEToIndex(c));
}

/*
 *	Increment the sequence number and flood the LSP on all
 *	links
 */
void
updateSeqAndFlood __PF2(ent, LSEntry *,
			seqNum, long)
{
	LSPDesc		*desc = ent->lspDesc;

	assert(desc != NULL);
	desc->seqNumber = seqNum+1;

	IFTRACE(T_BUILDLSP)
		dumpLSPDesc(desc, "LSP changed (Seq Update) ");
	ENDTRACE

	lspChanged(desc);
}

/*
 *	acknowledge sender,
 *	and flood to all other neighbors
 */
void
ackAndFlood __PF2(c, CircuitEntry *,
		  ent, LSEntry *)
{
	int	i;
	ackLSP(c, ent);
	for (i=0; i<MaximumCircuits; i++) {
		if ((circuitList[i]) && (circuitList[i] != c))
			setFlags(ent->SRM, SingleCircuit, CEToIndex(circuitList[i]));
	}
}

/* make this LSEntry disappear in 'delay' seconds */
void
markForDeletion __PF2(ent, LSEntry *,
		      delay, int)
{
	if (ent->onDeletedList) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("IS-IS markForDeletion: %s already on deleted list - ignored",
			      LSSigToStr(&ent->signature)));
	} else {
		ent->remainingTime = delay;
		ageListInsert(deletedLSPAge, (u_char *) ent);
		ent->onDeletedList = True;
	}
}

/*
 * Smoke him.
 */
void
purgeLSP __PF1(ent, LSEntry *)
{
	assert(ent->lspDesc == NULL); 	/* shouldn't do this to my own LSP */
									/* it isn't on 'normalLSPAge' */
	ageListRemove(normalLSPAge, (u_char *) ent);

	/*
	 *	If the sequence number is zero, then this is actually a dummy
	 *	LSP entry created during sequence number processing. Don't
	 *	keep it around.
	 */
	if (ent->signature.seqNum == 0) {
		deletedLSPExpired(ent);
	} else {
		normalLSPExpired(ent);
		adjustPrefsOnly = 0;
		signalDecisionProcess(ent->signature.level);
	}
}

/*
 *	Return the correct value for the lifetime value of the PDU based upon
 *	the original lifetime field (stored in the LSEntry) and the
 *	amount of time the PDU has spent in storage. If the signature lifetime
 *	has been set to zero, then return zero as the corrected lifetime.
 *	Also, special case for my own LSPs - they never age before I send them
 */
u_short
correctedLifetime(ent)
LSEntry	*ent;
{
	u_long	clt;	/* corrected lifetime */

	if (ent->signature.lifetime && (!(locallyGenerated(ent)))) {
		/* determine how long the pdu has been hanging around */
		/* calculate this in longs so as to avoid overflow */

		if ((timeStamp - ent->arrivalTimestamp) > ent->originalLifetime)
			clt = 0;
		else
			clt = ent->originalLifetime - (timeStamp - ent->arrivalTimestamp);

		ent->signature.lifetime = clt;
	}
	return(ent->signature.lifetime);
}

/*
 *	Update the lifetime field in the PDU to be consistent with the
 *	corrected Lifetime
 */
void
updateLifetime(ent)
LSEntry	*ent;
{
	/* check for empty header here */
	if (ent->len && ent->buf) {
		LSPHeader	*hdr = (LSPHeader *)ent->buf;
		hostToU16(correctedLifetime(ent), hdr->remainingLifetime);
	}
}

/*
 *	Called when an LSP's ttl expires
 *	Mark LSP to be deleted
 *	Retain only the header, and flood on all circuits.
 */
int
normalLSPExpired(ent)
LSEntry	*ent;
{
	LSPHeader	*hdr = (LSPHeader *)ent->buf;

	setFlags(ent->SRM, AllCircuits, 0);

	IFTRACE(T_FLOODING)
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("LSP: %s: %s",
			      ent->remainingTime > 0 ? "Purged" : "Expired",
			      LSSigToStr(&ent->signature)));
			
	ENDTRACE

	if (ent->remainingTime)
		markForDeletion(ent, maximumAge);
	else
		markForDeletion(ent, zeroAgeLifetime);

	ent->signature.lifetime = 0;
	ent->len = sizeof(LSPHeader);
	/* DTS 12-5-90 check for null hdr here; buf pointer  is sometimes null */
	/* if so, zero the length; this should be ok to indicate a dummy entry */
	/* but should check with rob on this. */
	if (hdr) {
		hostToU16(sizeof(LSPHeader), hdr->pduLength); 
	} else
		ent->len = 0;

	return(0);
}


int
deletedLSPExpired(ent)
LSEntry	*ent;
{
	IFTRACE(T_FLOODING)
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("LSP Deleted: %s",
			      LSSigToStr(&ent->signature)));
	ENDTRACE

	removeLSP(ent);				/* remove from hash table */
	rmFromSortList(ent);		/* remove from sorted list */

	/*
	 *	Delete an LSEntry. Special case for our own LSPs because the
	 *	buf is part of the LSPDesc
	 */
	if (locallyGenerated(ent)) {
		assert(ent == ent->lspDesc->lspEntry);
		if (ent->lspDesc->schedRegenerate) {
			/* clear LSP timer if it's set */
			clearTimer(ent->lspDesc->timer);
		}
		ent->lspDesc->lspEntry = NULL;
	} else if (ent->len) {
		task_block_free(isis_lspbuf_block[ent->allocLen >> 7], ent->buf);
		isisCounters.lspbufs--;
		isisCounters.lspbytes -= ent->allocLen;
		ent->allocLen = 0;
	}
	task_block_free(isis_lsentry_block, ent);
	isisCounters.lsentries--;
	return(0);
}


void
dumpLSPList __PF1(al, AgeList *)
{
	LSEntry	*scan;

	IterateDLListForw(scan, &al->links, LSEntry *) {
		printf("LSP: rt %d, %s x%x\n", scan->remainingTime, LSSigToStr(&scan->signature), scan);
	}
}


/*
 *  Cause decision to run
 */
void
signalDecisionProcess(level)
int level;    /* level 1 or level 2 */
{
	if (level == 1) 
		runL1spf = 1;
	else 
		runL2spf = 1;

#ifdef notdef
	if (systemType == L2IS)
		updateAreaSummary();
	isis_spf(level);
#endif
}

/*
 *	dump the contents of the LSP database at level specified
 */
void
dumpLSPDB __PF2(fd, FILE *,
		level, int)
{
	LSEntry	*ent = firstLSP(level);
	char scratch[40];

	if (fd) fprintf(fd, "L%d LSP Database\n", level);
	else trace_log_tf(isis_trace_options,
			  0,
			  LOG_INFO,
			  ("******* L%d LSP Database",
			   level));
	while (ent) {
		(void) correctedLifetime(ent);	/* correct the lifetime for display */
		/* STEVE - if I only knew how strcat worked ... */
		if (!locallyGenerated(ent) || ent->onDeletedList) {
			if (locallyGenerated(ent)) sprintf(scratch, "local|will delete|rt:%d", ent->remainingTime);
			else if (ent->onDeletedList) sprintf(scratch, "\twill delete|rt:%d", ent->remainingTime);
			else sprintf(scratch, "rt:%d", ent->remainingTime);
		} else sprintf(scratch, "local");
		if (fd) {
			fprintf(fd, "LSP %s  \t%s\n", LSSigToStr(&ent->signature), scratch);
			printLSPContents(fd, ent->buf, ent->len);
		} else {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_INFO,
				     ("LSP %s  \t%s",
				      LSSigToStr(&ent->signature),
				      scratch));
			IFTRACE(T_LSPCONTENT)
				printLSPContents(0, ent->buf, ent->len);
			ENDTRACE
		}
		ent = ent->sortNext;
	}
	if (fd) fprintf(fd, "\n");
	else trace_log_tf(isis_trace_options,
			  0,
			  LOG_INFO,
			  (NULL));
}


void
dumpDB()
{
	IFTRACE(T_DUMPDB)
		dumpLSPDB(0, 1);
		if (systemType == L2IS)
			dumpLSPDB(0, 2);
	ENDTRACE

	setTimer(dumpDBinterval, dumpDB);
}

/* flood all lsps on a particular circuit */
void
floodAllLSPs __PF2(c, CircuitEntry *,
		   level, int)
{
	LSEntry	*ent = firstLSP(level);

	while (ent) {
		setFlags(ent->SRM, SingleCircuit, CEToIndex(c));
		ent = ent->sortNext;
	}
}

/* 
 * Free the LS entry change list.
 */
void
isis_freelseChangeList __PF0(void)
{
	struct _lseChangeList *tmp;

	while (lseChangeList) {
		tmp = lseChangeList->next;
		task_block_free(isis_lseChangeList_block, lseChangeList);
		isisCounters.lseChangeList--;
		lseChangeList = tmp;
	}
	lseChangeList = (struct _lseChangeList *) 0;
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
