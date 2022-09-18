/*
 *  isis_adjacency.c,v 1.11 1993/01/07 22:39:02 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"

/*
 *	Hash table used to locate adjacencies quickly
 *	Hash is based upon the MAC address and chains adjacency entries
 *	off of each entry in the table.
 */
static AdjacencyEntry *adjHash[AdjHashTableSize];

/* 
 * This list keeps track of adjacencies which must be
 * deleted after next spf run.
 */
OldAdjacencyEntry OldL1AdjList;
OldAdjacencyEntry OldL2AdjList;

void
initOldAdjacencies()
{
	DLLInit(&OldL1AdjList.links);
	DLLInit(&OldL2AdjList.links);
}

void
addOldAdjacency __PF1(adj, AdjacencyEntry *)
{
	OldAdjacencyEntry *adjList;

	if (adj->adjacencyType == L1IS) adjList = &(OldL1AdjList);
	else adjList = &(OldL2AdjList);
        DLLInsque(adj, &adjList->links);
}

void
deleteOldAdjacencies __PF1(level, int)
{
	AdjacencyEntry *adj, *temp;
	OldAdjacencyEntry *adjList;

	adjList = (level == 1) ? &OldL1AdjList : &OldL2AdjList;
	temp = NULL;
	IterateDLListForw(adj, &adjList->links, AdjacencyEntry *) {
		if (temp) task_mem_free(isis_task, temp);
		DLLRemque(adj);
		isisCounters.adjEntries--;
        	if (adj->neighborInfo) {
			task_mem_free(isis_task, adj->neighborInfo);
			isisCounters.adjNeighborInfo--;
		}
		temp = adj;
	}
	if (temp) task_mem_free(isis_task, temp);
}

static u_short 
MACHash __PF1(mac, MACAddress)
{
	u_short	hash = 0;

	hash ^= mac[3];
	hash ^= mac[4];
	hash ^= mac[5];
	
	return(hash);
}

/* insert adj into hash table based upon mac address */
static void
insertAdjByMAC __PF2(adj, AdjacencyEntry *,
		     mac, MACAddress)
{
	u_short indx = MACHash(mac) % AdjHashTableSize;

	adj->hashIndex = indx;
	if (adjHash[indx]) {
		adj->hashNext = adjHash[indx];
	}
	adjHash[indx] = adj;
}

/*
 *	Remove adj from the adjacency hash table
 */
void
removeAdjFromHash(adj)
AdjacencyEntry	*adj;
{
#ifdef	notdef
/* this won't happen */
	if (adj->hashIndex < 0 || adj->hashIndex > AdjHashTableSize) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("removeAdjFromHash: bad hash index"));
		return;
	}
#endif	/* notdef */
	if (adjHash[adj->hashIndex] == adj)
		adjHash[adj->hashIndex] = adj->hashNext;
	else {
		AdjacencyEntry	*scan, *lastScan = NULL;
		
		for (scan = adjHash[adj->hashIndex]; scan; lastScan=scan, 
			scan=scan->hashNext) {
			if (scan == adj)
				lastScan->hashNext = adj->hashNext;
		}
	}
}

/* 
 *	return a pointer to (or NULL) the first matching adjacency 
 *	entry in hashtable 
 */
AdjacencyEntry *
locateAdjByMAC(mac)
MACAddress	mac;
{
	u_short indx = MACHash(mac) % AdjHashTableSize;
	return(adjHash[indx]);
}

/*
 *	Remove adj from circuit list, and then re-insert with new
 *	holding time
 */
void
updateAdjHt __PF3(circuit, CircuitEntry *,
		  adj, AdjacencyEntry *,
		  ht, u_short)
{
	switch (adj->adjacencyType) {
		case L1IS:
		case L2IS:
			assert(!DLListEmpty(&circuit->isAdjs->links));
			ageListRemove(circuit->isAdjs, (u_char*) adj);
			adj->holdingTime = ht;
			adj->remainingTime = ht;
			ageListInsert(circuit->isAdjs, (u_char *) adj);
			break;
		case ES:
			assert(!DLListEmpty(&circuit->esAdjs->links));
			ageListRemove(circuit->esAdjs, (u_char*) adj);
			adj->holdingTime = ht;
			adj->remainingTime = ht;
			ageListInsert(circuit->esAdjs, (u_char*) adj);
			break;
		default:
			;
	}
}

/*
 *	Create an adjacency, link into the circuit and insert into
 *	adjacency hash table. If memory is not available to store this
 *	adjacency, then steal the memory from another adjacency.
 */
AdjacencyEntry *
createAdjacency __PF5(
	    circuit, CircuitEntry *,
	    adjType, SystemType,
	    srcMAC, MACAddress,
	    ht, u_short,
	    infoLen, int)
{
	AdjacencyEntry	*adj;

	if ((!(adj = castMalloc(AdjacencyEntry *, sizeof(AdjacencyEntry)))) ||
		(!(adj->neighborInfo = castMalloc(u_char *, infoLen)))) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("%s: Adjacency %s: src mac %s: insufficient memory to store", 
			      circuit->name,
			      systemTypeToStr(adjType),
			      IDToStr(srcMAC, 6)));
		return(NULL);
	}
	isisCounters.adjEntries++;
	isisCounters.adjNeighborInfo++;

	adj->circuit = circuit;
	adj->adjacencyType = adjType;
	adj->holdingTime = ht;
	adj->remainingTime = ht;
	copyID(srcMAC, adj->neighborMAC, sizeof(MACAddress));
	insertAdjByMAC(adj, srcMAC);

	switch (adj->adjacencyType) {
		case L1IS:
		case L2IS:
		case IS:
		case Unknown:
			ageListInsert(circuit->isAdjs, (u_char*) adj);
			break;
		case ES:
			ageListInsert(circuit->esAdjs, (u_char*) adj);
			break;
		default:
			;
	}

	return(adj);
}


/*
 *	Called when an adjacency entry expires
 */
int
adjacencyExpired(adj)
AdjacencyEntry	*adj;
{
	CircuitEntry	*c = adj->circuit;
	IFTRACE(T_LANADJ|T_P2PADJ)
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("%s: Adjacency %s: %s %s: timed out", 
			      c->name, systemTypeToStr(adj->adjacencyType),
			      (adj->adjacencyType != ES) ? "SysID" : "MAC",
			      (adj->adjacencyType != ES) ? IDToStr(adj->neighborSysID, 6) : IDToStr(adj->neighborMAC, 6)));
	ENDTRACE
	adjDownEvent(c, adj, HoldingTimerExpired);
	return(0);
}

static int	scanOff;
static AdjacencyEntry	*scan;

AdjacencyEntry *
startAdjScan()
{
	scanOff = 0;
	while (((scan = adjHash[scanOff]) == NULL) && scanOff < AdjHashTableSize)
		scanOff++;
	if (scanOff >= AdjHashTableSize)
		return(NULL);
	else
		return(scan);
}

AdjacencyEntry *
nextAdj()
{
	if (scan->hashNext) {
		return(scan = scan->hashNext);
	} else {
		while (((scan = adjHash[++scanOff]) == NULL) && 
			scanOff < AdjHashTableSize)
			scanOff++;
		if (scanOff >= AdjHashTableSize)
			return(NULL);
		else
			return(scan);
	}
}

#define AgeListCount	((MaximumCircuits*2) + 3)

static AgeList	*ageListBase[AgeListCount];

AgeList *
newAgeList __PF2(
	    deleteFunc, PTIF,
	    offset, u_short)
{
	int		i;
	AgeList	*al;

	for (i=0; i<AgeListCount; i++) {
		if (!ageListBase[i]) {
			al = ageListBase[i] = castMalloc(AgeList *, sizeof(AgeList));
			isisCounters.agelists++;
			DLLInit(&al->links);
			al->delete = deleteFunc;
			al->ttlOffset = offset;
			return(al);
		}
	}
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("out of AgeList entries"));
	task_quit(0);
	return((AgeList *) 0);
}

#define ttl(al, item) (*((u_short *)(((u_char *)item)+(al->ttlOffset))))

void
ageListAge()
{
	int		i;
	AgeList	*al;

	for (i=0; i<AgeListCount; i++) {
		if (al = ageListBase[i]) {
			if (!DLListEmpty(&al->links)) {
				u_char	*item, *nextItem;

				item = DLListForw(&al->links, u_char *);
				/* STEVE - check for 0 before decrementing */
				if ((ttl(al, item) == 0) || (--(ttl(al, item)) == 0)) {
					while (item && (ttl(al, item) == 0)) {
						nextItem = DLListNext(item, &al->links, u_char *);
						DLLRemque(item);
						(al->delete)(item);
						item = nextItem;
					}
				}
			}
		}
	}
	setTimer(1, ageListAge, NULL);
}

/*
 *	Insert item in the age list specified. List is maintained in ascending
 *	order based upon time-to-live. Dis is ya basic
 *	clock queue algorithm
 */
void
ageListInsert(al, item)
AgeList		*al;
u_char		*item;
{
	u_short		remaining = ttl(al, item);
	u_char		*ascan;

	/* consistency check - don't want to insert the same thing twice! */
	IterateDLListForw(ascan, &al->links, u_char *) {
		assert((ascan) && (ascan != item));
	}

	IterateDLListForw(ascan, &al->links, u_char *) {
		if (remaining < ttl(al, ascan)) {
			/* insert before ascan */
			DLLInsque(item, DLListBack(ascan, DLList *));	
			ttl(al, ascan) -= remaining;
			ttl(al, item) = remaining;
			return;
		} else {
			remaining -= ttl(al, ascan);
		}
	}
	DLLInsque(item, DLListBack(&al->links, DLList *));	
	ttl(al, item) = remaining;
}

/*
 *	Remove item from age list 
 */
void
ageListRemove(al, item)
AgeList		*al;
u_char		*item;
{
	u_char		*nextItem;

	assert(!DLListEmpty(&al->links));

	if (ttl(al, item) > 0) {
		/* Must add this remaining time to next item's remaining time */
		if (nextItem = DLListNext(item, &al->links, u_char *)) {
			ttl(al, nextItem) += ttl(al, item);
		}
	}
	DLLRemque(item);
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
