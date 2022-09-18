/*
 *  isis_p2phello.c,v 1.11 1993/01/07 22:39:46 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"
#ifdef	PROTO_SNMP
#include "isis_mib.h"                         /* Isis-Mib */
#endif	/* PROTO_SNMP */
#include "isis_globals.h"


/*
 *	Create a p2p hello packet with or without padding and transmit it.
 */
void
sendP2PHello __PF2(circuit, CircuitEntry *,
		   pad, int)			
{
	u_char		buf[MaxPacketSize], *bp;
	PPHelloHeader	*hdr = (PPHelloHeader *)buf;
	u_short		pduLen;

	bzero((caddr_t)buf, sizeof(buf));
	bp = buf + sizeof(PPHelloHeader);

	addCommon(&hdr->common, PPHelloType);

	switch (systemType) {
		case L2IS:
			hdr->circuitType |= L2Circuit;
			if (circuit->manualL2Only)
				break;
			/* ELSE FALL THROUGH */
		case L1IS:
			hdr->circuitType |= L1Circuit;
			break;
		default:
			assert(0);
	}
	copyID(systemID, hdr->sourceID, 6);
	hostToU16(sysHoldingTimer, hdr->holdingTimer);
	hdr->localCircuitID = circuit->localId;
	
	/* DUAL: add protocols supported code and IP interface address */
	bp = insertProtoSup(bp, True);
	bp = insertIPaddr(circuit, bp, True);
		
	bp = insertAreaAddrList(systemAreaAddrs, bp);

	if (pad) {
		pduLen = max(origL1LSPBufSize, origL2LSPBufSize);
		pduLen = max(pduLen, dataLinkBlocksize);
		bp = insertPadding(bp, pduLen - (bp - buf));
	}

	pduLen = bp - buf;
	hostToU16(pduLen, hdr->pduLength);

	IFTRACE(T_P2PADJ)
		trace_only_tf(isis_trace_options,
			      0,
			      ("%s: sending PP IIH (%d bytes)",
			       circuit->name,
			       pduLen));
	ENDTRACE

	/* MAC address here is not used (on point2point link) */
	transmitPacket(circuit, AllL1ISmac, buf, pduLen);
}

/*
 *	Parse a P2P IIH. If parse succeeds, return OK
 *	else NOTOK
 */
int
parseP2PHello(buf, length, pkt)
u_char	*buf;	/* buffer containing packet */
int		length;	/* length of buffer */
PPHelloPacket	*pkt;
{
	u_char	*bp, *end;

	bzero((caddr_t) pkt, sizeof(PPHelloPacket));
	pkt->hdr = (PPHelloHeader *)buf;
	pkt->hdr->circuitType = GetCircuitType(pkt->hdr->circuitType);
	U16toHost(pkt->hdr->pduLength, pkt->pduLength);
	U16toHost(pkt->hdr->holdingTimer, pkt->holdingTimer);

	/* check that we have as much data as we might think */
	if (pkt->pduLength > length) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("parseP2PHello: buf (%d) too short (should be %d)",
			      length,
			      pkt->pduLength));
		return(NOTOK);
	} else if (pkt->pduLength < length) {
		length = pkt->pduLength;
	}


	/* parse the variable length fields */
	bp = buf + sizeof(PPHelloHeader);
	end = buf + length;

	while (bp+1 < end) {
		u_char	code = *bp++;
		u_char	len = *bp++;

		if (bp + len > end) {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("parseP2PHello: option %d too short",
				      code));
			return(NOTOK);
		}
		switch(code) {
			case AreaAddressCode:
				if (!parseAreaAddrList(bp, len, &pkt->areaAddrs)) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("parseP2PHello: can't parse area list"));
					return(NOTOK);
				}
				break;

			case ProtoSupportedCode: /* DUAL */
				pkt->flags = parseProtoSup(bp, len);
				break;

			case IPIfAddrCode: /* DUAL */
				if (!parseIPIfAddr(bp, len, &pkt->ifAddr)) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("parseP2PHello: can't parse IP Address"));
					return(NOTOK);
				}
				break;

			case IPAuthInfoCode: /* DUAL */
				if (!parseAuthInfo(bp, len, &pkt->authInfo)) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("parseP2PHello: can't parse Authentication Info"));
					return(NOTOK);
				}
				break;

			case PaddingCode:
			default:
				break;
		}
		bp += len;
	}
	return(OK);
}

/*
 *	Print a parsed IIH packet
 */
void
dumpP2PIIH(c, pkt)
PPHelloPacket	*pkt;
CircuitEntry *c;
{
	PPHelloHeader	*hdr = pkt->hdr;

	trace_tf(isis_trace_options,
		 TR_NORMAL,
		 0,
		 ("%s: %s from %s, circuit %s, ht %d, circuitID %d", 
		  c->name,
		  typeToStr(hdr->packetType),
		  IDToStr(hdr->sourceID, 6),
		  circuitLevelToStr(hdr->circuitType),
		  pkt->holdingTimer, 
		  hdr->localCircuitID));

	tracef("\tsupported %s", flagsToStr(pkt->flags));
	if (pkt->flags & SUPPORT_IP) 
		tracef(", IPaddr %A",sockbuild_in(0, pkt->ifAddr.addrs[0].s_addr));  /* XXX - MULTIPATH */
	trace_tf(isis_trace_options,
		 TR_NORMAL,
		 0,
		 (NULL));
	printAreaAddrList("\t", &pkt->areaAddrs);
	trace_tf(isis_trace_options,
		 TR_NORMAL,
		 0,
		 (NULL));
}

/*
 *	Return the adjacency entry corresponding to an IS adjacency on
 *	a point2point circuit. It is assumed that there is only one adjacency
 *	and that it is stored off the isAdjs link. Return ptr to the adjacency
 *	structure or NULL
 */
static AdjacencyEntry	*
findPt2PtAdj(c)
CircuitEntry	*c;			/* circuit ISH arrived upon */
{
	AdjacencyEntry	*adj = NULL;

	if (!DLListEmpty(&c->isAdjs->links)) {
		adj = DLListForw(&c->isAdjs->links, AdjacencyEntry *);
		/* there should only be one adjacency on a Pt2Pt circuit */
		assert(DLListNext(adj, &c->isAdjs->links, AdjacencyEntry *) == NULL);
	}
	return(adj);
}

/*
 *	State table bogosity
 */
int
adjTypeIndex(adj)
AdjacencyEntry	*adj;
{
	if ((adj == 0) || (adj->state != AdjUp))
		return(0);
	else if (adj->adjacencyType == L1IS)
		return(1);
	else if ((adj->adjacencyType == L2IS) && (!adj->level2Only))
		return(2);
	else if ((adj->adjacencyType == L2IS) && (adj->level2Only))
		return(3);
	else
		return(0);
}

/* possible actions (the result of a lookup in a state table */
#define	ActionUp		1
#define ActionDown		2
#define ActionReject	3
#define ActionAccept	4

static const char *
actionToStr(action)
int action;
{
    switch(action) {
    case ActionUp:
	return "Up";
	    
    case ActionDown:
	return "Down";
	    
    case ActionReject:
	return "Reject";

    case ActionAccept:
	return "Accept";
    }

    return 0;
}


#define EncodeAction(act, data)\
	(((act) << 16) | (data))

#define DecodeAction(encoded, act, data)\
	act = encoded >> 16;\
	data = encoded & 0x0000ffff;

#define EncodeUpData(level, manl2)\
	((level << 8) | (manl2))

#define DecodeUpData(encoded, level, manl2)\
	level = (encoded) >> 8;\
	manl2 = (encoded) & 0x000000ff;

#define UP(level, manualL2)\
	EncodeAction(ActionUp, EncodeUpData(level, manualL2))

#define DOWN(code)\
	EncodeAction(ActionDown, code)
	
#define REJECT(code)\
	EncodeAction(ActionReject, code)
	
#define ACCEPT\
	EncodeAction(ActionAccept, 0)

#define wst	WrongSystemType
#define	am	AreaMismatch

/* Level 1 state table for matching areas (table 4) */
u_int	l1AreaMatch[3][4] = {
	/* none */			/* L1 */	/* L2 */
{	UP(L1IS, False),	ACCEPT, 	DOWN(wst)},
{	REJECT(wst),		DOWN(wst),	DOWN(wst)},
/* {	UP(L1IS, False),	DOWN(wst),	ACCEPT } - original */
{	UP(L1IS, False),	ACCEPT,		ACCEPT }
};

/* Level 2 state table for matching areas (table 5) */
u_int	l2AreaMatch[3][4] = {
	/* none */			/* L1 */	/* L2 */		/* L2 Only */
{	UP(L1IS, False),	ACCEPT,		DOWN(wst),		DOWN(wst) },
{	UP(L2IS, True),		DOWN(wst),	DOWN(wst),		ACCEPT },
{	UP(L2IS, False),	DOWN(wst),	ACCEPT,			DOWN(wst) },
};

/* Level 2 Only  state table for matching areas (table 6) */
u_int	l2OAreaMatch[3][4] = {
	/* none */			/* L1 */	/* L2 */		/* L2 Only */
{	REJECT(wst),		(u_int) NULL,		DOWN(wst),		DOWN(wst) },
{	UP(L2IS, True),		(u_int) NULL,		DOWN(wst),		ACCEPT },
{	UP(L2IS, True),		(u_int) NULL,		DOWN(wst),		ACCEPT }
};

/* Level 2 state table for non-matching areas */
u_int	l2AreaMisMatch[3][4] = {
	/* none */			/* L1 */	/* L2 */		/* L2 Only */
{	REJECT(am),			DOWN(am),	DOWN(wst),		DOWN(wst) },
{	UP(L2IS, True),		DOWN(wst),	DOWN(wst),		ACCEPT },
{	UP(L2IS, True),		DOWN(wst),	DOWN(am),		ACCEPT },
};

/*
 *	Process a P2P Hello packet
 */
void
processP2PHello(circuit, buf, len, sourceMAC)
CircuitEntry	*circuit;	/* circuit IIH arrived upon */
u_char			*buf;	/* buffer containing packet */
int				len;	/* length of buffer */
MACAddress		sourceMAC;	/* source MAC of packet */
{
	PPHelloPacket	pkt;
	PPHelloHeader	*hdr;
	AdjacencyEntry	*adj = findPt2PtAdj(circuit);
	u_int			(*table)[3][4] = NULL, result;
	short			action, actionData;
	SystemID7		newCircuitID;

        if (!parseP2PHello(buf, len, &pkt)) {
                isisCounters.pduFormatErrors++;
                return;
        }

	IFTRACE(T_DUMPIIH)
		dumpP2PIIH(circuit, &pkt);
	ENDTRACE

	hdr = pkt.hdr;

	/*
	 *	Ignore my own PP IIH - don't need to establish an adjacency to
	 *	myself
	 */
	if (equalID(systemID, hdr->sourceID, 6))
		return;

	/* 
	 *	If the adjacency does not exist, then we have not yet received an
	 *	ISH on the circuit. Create an adjacency that is unknown and
	 *	initializing.
	 */
	if (adj == NULL) {
		adj = createAdjacency(circuit, Unknown, sourceMAC, pkt.holdingTimer,
			sizeof(AreaAddrList));
		if (adj == NULL)
			return;
		adj->type = AutoConfig;
		adj->state = AdjInitializing;
		IFTRACE(T_P2PADJ)
			trace_only_tf(isis_trace_options,
				      0,
				      ("%s: New Adjacency: %s: sys id %s", 
				       circuit->name,
				       systemTypeToStr(adj->adjacencyType),
				       IDToStr(adj->neighborSysID, 6)));
		ENDTRACE
#ifdef	PROTO_SNMP
		{
	    	    IsisMibEntry	*pMibEntry;
    	    	    IsisCircEntry	*pCircEntry;
		    IsisISAdjEntry	*pISAdjEntry;

	    	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	    	    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable, circuit->localId);
	    	    if (pCircEntry) {
			pISAdjEntry = (IsisISAdjEntry *)queueNew(&pCircEntry->isisISAdjTable);
			if (pISAdjEntry) {
			    adj->name = pISAdjEntry->isisISAdjIndex;
			    freshISAdjEntry(pISAdjEntry, adj);		/* Isis-Mib */

			    queueAdd(&pCircEntry->isisISAdjTable, pISAdjEntry);
			} else {
		            trace_log_tf(isis_trace_options,
					 0,
					 LOG_ERR,
					 ("processP2PHello(): cannot allocate entry in IS adj table for localId==%d, adj.name==%d", 
					  circuit->localId,
					  adj->name)); /* Where was adj->name assigned ??? */
			}
	            } else {
		        trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("processP2PHello(): cannot locate circ mib entry for localId==%d", 
				      circuit->localId));
	            }
		}
#endif	/* PROTO_SNMP */
	}

	if (matchAreaAddrList(&pkt.areaAddrs, &systemAreaAddrs)) {
		/* there is a match in the area addresses */
		switch (systemType) {
			case L1IS:
				table = &l1AreaMatch;
				break;
			case L2IS:
				if (circuit->manualL2Only)
					table = &l2OAreaMatch;
				else
					table = &l2AreaMatch;
				break;
			default:
				assert(0);
		}
	} else {
		/* there is NOT a match in the area addresses */
		if (systemType == L1IS) {
			if (adj->state != AdjUp)
				adjInitFailureEvent(circuit, NULL, AreaMismatch, 
					&hdr->sourceID, 1);
			adjDownEvent(circuit, adj, AreaMismatch);
			return;
		} else {
			table = &l2AreaMisMatch;
		}
	}

	assert(table != NULL);

	result = (*table)[hdr->circuitType-1][adjTypeIndex(adj)];
	DecodeAction(result, action, actionData);

	IFTRACE(T_P2PADJ)
		trace_only_tf(isis_trace_options,
			      0,
			      ("%s: IIH received: Adj State %s, Adj Type %s%s, action %s (%x)", 
			       circuit->name,
			       adjStateToStr(adj->state), 
			       ((adj->adjacencyType == L2IS) && !adj->level2Only) ? "L1" : "",
			       systemTypeToStr(adj->adjacencyType),
			       actionToStr(action), 
			       actionData));
	ENDTRACE

	switch (action) {
			SystemType	newLevel;
			Boolean		manL2;
		case ActionUp:

			if (adj->adjacencyType == Unknown)
				sendP2PHello(circuit, 1);	/* send this baby with padding */

			DecodeUpData(actionData, newLevel, manL2);
			adj->level2Only = manL2;
			adj->state = AdjUp;
			adj->adjacencyType = newLevel;

			/* FALL THROUGH TO NEXT CASE */
		case ActionAccept:
			if (compareID(systemID, hdr->sourceID, 6) >= 0) {
				copyID(systemID, newCircuitID, 6);
				newCircuitID[IDOFF] = circuit->localId;
			} else {
				copyID(hdr->sourceID, newCircuitID, 6);
				newCircuitID[IDOFF] = hdr->localCircuitID;
			}

			/* if action is accept and the new circuit id is different
				then take the adj down */
			if ((action == ActionAccept) && 
				compareID(circuit->circuitId, newCircuitID, 7)) {
				adjDownEvent(circuit, adj, IDMismatch);
				return;
			}

			copyID(hdr->sourceID, adj->neighborSysID, 6);
			updateAdjHt(circuit, adj, pkt.holdingTimer);
			bzero((caddr_t) adj->neighborInfo, sizeof(AreaAddrList));
			adj->ipaddrs = pkt.ifAddr;
			bcopy((caddr_t)&pkt.areaAddrs, (caddr_t)adj->neighborInfo, 
				sizeof(AreaAddrList));

			if (action == ActionUp) {
				copyID(newCircuitID, circuit->circuitId, 7);
				adjUpEvent(circuit, adj);
			}
#ifdef	PROTO_SNMP
			else {
	    	    IsisMibEntry	*pMibEntry;
    	    	    IsisCircEntry	*pCircEntry;
		    IsisISAdjEntry	*pISAdjEntry;

	    	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	    	    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable, circuit->localId);
	    	    if (pCircEntry) {
			pISAdjEntry = (IsisISAdjEntry *)locateEntry(&pCircEntry->isisISAdjTable, adj->name);
			if (pISAdjEntry) {
			    freshISAdjEntry(pISAdjEntry, adj);		/* Isis-Mib */
			    freshISAdjAreaAddrTable(pISAdjEntry, adj);  
			    freshISAdjIPAddrTable(pISAdjEntry, adj);  

			} else {
		            trace_log_tf(isis_trace_options,
					 0,
					 LOG_ERR,
					 ("processP2PHello(): cannot locate entry in IS adj table for localId==%d, adj.name==%d", 
					  circuit->localId,
					  adj->name));
			}
	            } else {
		        trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("processP2PHello(): cannot locate circ mib entry for localId==%d", 
				      circuit->localId));
	            }
			} /* end of if else action == ActionUp */
#endif	/* PROTO_SNMP */
			
			return;

		case ActionReject:
			adjInitFailureEvent(circuit, NULL, actionData, &hdr->sourceID, 1);
			/* FALL THROUGH */

		case ActionDown:
			adjDownEvent(circuit, adj, actionData);
			return;
			
		default:
			/* unknown action was encoded in table */
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("P2PHello: ignoring IIH (causes unknown action)"));
			return;
	}
}


/*
 *	Process an incoming ISH. Ignore it if this is not a point2point circuit
 */
void
processISH(c, id, ht, sourceMAC)
CircuitEntry	*c;			/* circuit ISH arrived upon */
SystemID6		id;			/* system ID from ISH NET */
u_short			ht;			/* holding timer */
MACAddress		sourceMAC;	/* source of packet */
{
	AdjacencyEntry		*adj = NULL;

	if (c->circuitType == Broadcast)
		return;
	
	/* ignore my own ISH */
	if (equalID(systemID, id, 6))
		return;
	
	if (adj = findPt2PtAdj(c)) {
		/* if the ID from the ISH does not match, blow away the adjacency */
		if ((adj->state == AdjUp) && (!equalID(id, adj->neighborSysID, 6))) {
			adjDownEvent(c, adj, IDMismatch);
			adj = NULL;
		}
	}

	if (adj == NULL) {
		adj = createAdjacency(c, Unknown, sourceMAC, ht, sizeof(AreaAddrList));
		if (adj == NULL)
			return;
		adj->type = AutoConfig;
		adj->state = AdjInitializing;
#ifdef	PROTO_SNMP
		{
	    	    IsisMibEntry	*pMibEntry;
    	    	    IsisCircEntry	*pCircEntry;
		    IsisISAdjEntry	*pISAdjEntry;

	    	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	    	    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable, c->localId);
	    	    if (pCircEntry) {
			pISAdjEntry = (IsisISAdjEntry *)queueNew(&pCircEntry->isisISAdjTable);
			if (pISAdjEntry) {
			    adj->name = pISAdjEntry->isisISAdjIndex;
			    freshISAdjEntry(pISAdjEntry, adj);		/* Isis-Mib */
			    queueAdd(&pCircEntry->isisISAdjTable, pISAdjEntry);
			} else {
		            trace_log_tf(isis_trace_options,
					 0,
					 LOG_ERR,
					 ("processISH(): cannot allocate entry in IS adj table for localId==%d, adj.name==%d", 
					  c->localId,
					  adj->name)); /* Where was adj->name assigned ??? */
			}
	            } else {
		        trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("processISH(): cannot locate circ mib entry for localId==%d",
				      c->localId));
	            }
		}
#endif	/* PROTO_SNMP */
	}

	IFTRACE(T_P2PADJ)
		trace_only_tf(isis_trace_options,
			      0,
			      ("%s: ISH received: Adj State %s, Adj Type %s",
			       c->name,
			       adjStateToStr(adj->state),
			       systemTypeToStr(adj->adjacencyType)));
	ENDTRACE

	/* this ISH was added in Defect Report 10589/001, section 6 */
	sendP2PHello(c, 1);	/* send this guy with padding */

	if (adj->state == AdjInitializing && adj->adjacencyType == IS)
		return;	
	
#ifdef	defect
	if (adj->state == AdjInitializing && adj->adjacencyType != IS)
		sendP2PHello(c, 1);	/* send this guy with padding */
#endif	/* defect - corrected above */

	/* 
	 * STEVE - change this only if adjacency is not already up 
	 * (this is my interpretation of 10589 8.2.2).  If we just go
	 * ahead and change this regardless of existing adjacency state,
	 * we end up adding this neighbor as a duplicate in our LSP when
	 * we receive its next IIH.  This can happen when a neighbor 
	 * cycles (down then up) within an adjacency holding timer period 
	 * (as may be common during a maintenance window).
	 */
	if (adj->state != AdjUp) adj->adjacencyType = IS;
}

/*
 *	Transmit an ISH packet on circuit 'c' for every NET configured into 
 *	the system.
 */
void
sendISHello(c)
CircuitEntry	*c;
{
	u_char		buf[MaxPacketSize], *bp, *savebp;
	ESISHeader	*hdr = (ESISHeader *)buf;
	u_char		pduLen = 0;
	int			i;

	bzero((caddr_t)buf, sizeof(buf));
	bp = buf + sizeof(ESISHeader);

	hdr->protoID = ESISRPD;
	hdr->vers = 1;
	hdr->type = 0x04;
	hostToU16(sysHoldingTimer, hdr->ht);

	/*
	 *	Send ISH for each area address configured
	 */
	assert(systemAreaAddrs.count > 0);
	savebp = bp;
	for (i=0; i<systemAreaAddrs.count; i++) {
		AreaAddr *aa = retrieveAreaAddr(systemAreaAddrs.areaAddr[i]);

		bp = savebp;
		*bp++ = aa->len + 6;	/* NET length - STEVE XXX - hardcoding length bad news */
		bcopy((caddr_t)aa->addr, (caddr_t) bp, aa->len); 
		bp += aa->len;
		bcopy((caddr_t) systemID, (caddr_t) bp, 6); 
		bp += 6;

                bp = insertProtoSup(bp, True);

		pduLen = bp - buf;
		hdr->headerLen = pduLen;

		iso_cksum((char *) hdr, pduLen, (byte *) hdr + 7);

		IFTRACE(T_P2PADJ)
			trace_only_tf(isis_trace_options,
				      0,
				      ("%s: sending ISH (%d bytes)",
				       c->name,
				       pduLen));
		ENDTRACE

		transmitPacket(c, AllESmac, buf, pduLen);
	}
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
