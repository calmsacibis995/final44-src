/*
 *  isis_lanhello.c,v 1.11 1993/01/07 22:39:27 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h" 

#ifdef	PROTO_SNMP
#include "isis_mib.h"		/* IS-IS mib */
#endif

/*
 *	Create a lan hello packet on the stack and transmit it
 */
int
sendLANHello __PF2(circuit, CircuitEntry *, 
		   type, Unsigned8)		/* L1 or L2 */
{
	u_char		buf[MaxPacketSize], *bp;
	LANHelloHeader	*hdr = (LANHelloHeader *)buf;
	u_short		pduLen;
	AdjacencyEntry	*adj;
	u_char		optLen;
	u_char		*optLenPtr;

	/* 
	 * STEVE - changed to run election before transmitting IIH;
	 * if the circuit changes, we won't transmit an IIH which 
	 * disagrees with our election results (as was the case when
	 * the election was run after transmitting the IIH.
	 */
	/* lanElection(circuit, (type == L1LANHelloType) ? 1 : 2); */

	bzero((caddr_t)buf, sizeof(buf));
	bp = buf + sizeof(LANHelloHeader);

	pduLen = (type == L1LANHelloType) ? origL1LSPBufSize : origL2LSPBufSize;
	pduLen = max(pduLen, dataLinkBlocksize);

	addCommon(&hdr->common, type);

	switch (systemType) {
		case L2IS:
			hdr->circuitType |= L2Circuit;
			if (circuit->manualL2Only) {
				if (type == L1LANHelloType) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("sendLANHello: tried to send L1 Hello when L2only"));
					return(NOTOK);
				}
				break;
			} 
			/* ELSE FALL THROUGH */
		case L1IS:
			hdr->circuitType |= L1Circuit;
			if (type == L2LANHelloType && (!(hdr->circuitType & L2Circuit))) {
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_ERR,
					     ("sendLANHello: tried to send L2 Hello when L1"));
				return(NOTOK);
			}
			break;
		default:
			assert(0);
	}
/*      hdr->circuitType |= 0x08;        Microserver compatiblity kludge */

	copyID(systemID, hdr->sourceID, 6);
	hostToU16(sysHoldingTimer, hdr->holdingTimer);
	hdr->priority = (type == L1LANHelloType) ? circuit->l1Priority : 
		circuit->l2Priority;
	
	if (type == L1LANHelloType)
		copyID(circuit->circuitId, hdr->LANID, 7);
	else
		copyID(circuit->l2CircuitId, hdr->LANID, 7);
	
	/* DUAL: add protocols supported code and IP interface address */
	bp = insertProtoSup(bp, True);
	bp = insertIPaddr(circuit, bp, True);
		
	bp = insertAreaAddrList(systemAreaAddrs, bp);

	/*
	 *	Scan list of IS adjs and add those which are of correct
	 *	type (L1 or L2) and in state UP or Initializing
	 *
	 *	The check for buffer overrun is fatal since it does may not
	 *	catch the overrun until it is too late.
	 */
	if (!(DLListEmpty(&circuit->isAdjs->links))) {
		optLen = 0;
		*bp++ = ISNeighborCode;
		optLenPtr = bp++;

		IterateDLListForw(adj, &circuit->isAdjs->links, AdjacencyEntry *) {
			if (bp > buf + MaxPacketSize) {
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_ERR,
					     ("sendLANHello: MaxPacketSize too small"));
				task_quit(0);
			}
			if (adj->state == AdjInitializing || adj->state == AdjUp) {
				if (((type == L1LANHelloType) && adj->adjacencyType == L1IS) ||
					((type == L2LANHelloType) && adj->adjacencyType == L2IS)) {
					bcopy((caddr_t)adj->neighborMAC, (caddr_t) bp, 
						sizeof(adj->neighborMAC));
					bp += sizeof(adj->neighborMAC);
					optLen += sizeof(adj->neighborMAC);
				}
			}
			if (!optSpaceLeft(optLen, sizeof(adj->neighborMAC))) {
				*optLenPtr = optLen;
				*bp++ = ISNeighborCode;
				optLenPtr = bp++;
				optLen = 0;
			}
		}
		*optLenPtr = optLen;
	}

	bp = insertPadding(bp, pduLen - (bp - buf));
	pduLen = bp - buf;

	hostToU16(pduLen, hdr->pduLength);

	IFTRACE(T_DUMPIIH)
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_INFO,
			     ("%s: sending %s (%d bytes)",
			      circuit->name,
			      typeToStr(type),
			      pduLen));
	ENDTRACE
#ifdef	notdef
	/* STEVE - this is outta there - used for T_LSPCONTENT instead */
	IFTRACE(T_HEXDUMP)
		dumpBuffer(buf, pduLen);
	ENDTRACE
#endif	/* notdef */

	transmitPacket(circuit, (type == L1LANHelloType) ? AllL1ISmac : AllL2ISmac,
		buf, pduLen);

	lanElection(circuit, (type == L1LANHelloType) ? 1 : 2);

	return(OK);
}

/*
 *	Parse a LAN IIH. If parse succeeds, return OK
 *	else NOTOK
 */
static int
parseLANHello __PF3(buf, u_char *,
		    len, int,
		    pkt, LANHelloPacket *)
{
	u_char	*bp, *end;

	bzero((caddr_t) pkt, sizeof(LANHelloPacket));
	pkt->hdr = (LANHelloHeader *)buf;
	pkt->hdr->circuitType = GetCircuitType(pkt->hdr->circuitType);
	pkt->hdr->priority = GetPriority(pkt->hdr->priority);
	U16toHost(pkt->hdr->pduLength, pkt->pduLength);
	U16toHost(pkt->hdr->holdingTimer, pkt->holdingTimer);

	/* check that we have as much data as we might think */
	if (pkt->pduLength > len) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("parseLANHello: buf (%d) too short (should be %d)",
			      len,
			      pkt->pduLength));
		return(NOTOK);
	} else if (pkt->pduLength < len) {
		len = pkt->pduLength;
	}


	/* parse the variable length fields */
	bp = buf + sizeof(LANHelloHeader);
	end = buf + len;

	while (bp+1 < end) {
		u_char	code = *bp++;
		u_char	length = *bp++;

		if (bp + length > end) {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("parseLANHello: option %d too short",
				      code));
			return(NOTOK);
		}
		switch(code) {
			case AreaAddressCode:
				if (!parseAreaAddrList(bp, length, &pkt->areaAddrs)) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("parseLANHello: can't parse area list"));
					return(NOTOK);
				}
				break;

			case ISNeighborCode:
				if (length % 6) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("parseLANHello: neighbor list incomplete"));
					return(NOTOK);
				}
				pkt->count = length/6;
				pkt->ISneighbors = (SystemID6 *)bp;
				break;

			case ProtoSupportedCode: /* DUAL */
				pkt->flags = parseProtoSup(bp, length);
				break;

			case IPIfAddrCode: /* DUAL */
				if (!parseIPIfAddr(bp, length, &pkt->ifAddr)) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("parseLANHello: can't parse IP Address"));
					return(NOTOK);
				}
				break;

			case IPAuthInfoCode: /* DUAL */
				if (!parseAuthInfo(bp, length, &pkt->authInfo)) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("parseLANHello: can't parse Authentication Info"));
					return(NOTOK);
				}
				break;

			case PaddingCode:
			default:
				break;
		}
		bp += length;
	}
	return(OK);
}

/*
 *	Print a parsed IIH packet
 */
static void
dumpLANIIH __PF2(c, CircuitEntry *,
		 pkt, LANHelloPacket *)
{
	LANHelloHeader	*hdr = pkt->hdr;
	int				i;

	trace_log_tf(isis_trace_options,
		     0,
		     LOG_INFO,
		     ("%s: %s from %s, circuit %s, ht %d, priority %d", 
		      c->name,
		      typeToStr(hdr->packetType),
		      IDToStr(hdr->sourceID, 6),
		      circuitLevelToStr(hdr->circuitType),
		      pkt->holdingTimer, 
		      hdr->priority));

	tracef("\tdesignated %s", IDToStr(hdr->LANID, 7));
	if (pkt->ifAddr.cnt) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_INFO,
			     (" supported %s, IPaddr %A",
			      flagsToStr(pkt->flags),
			      sockbuild_in(0, pkt->ifAddr.addrs[0].s_addr)));	/* XXX - multipath */
	} else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_INFO,
			     (" supported %s",
			      flagsToStr(pkt->flags)));
	}
	printAreaAddrList((const char *) "\t", &pkt->areaAddrs);
	tracef("\tneighbors: ");
	for (i=0; i<pkt->count; i++) {
		tracef("%s ", IDToStr(pkt->ISneighbors[i], 6));
	}
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_INFO,
		     (NULL));
}

/*
 *	Process a LAN Hello packet
 */
void
processLANHello __PF4(circuit, CircuitEntry *,		/* incoming circuit */
		      buf, u_char *,			
		      len, int,
		      sourceMAC, MACAddress)		/* source SNAP */
{
	LANHelloPacket	pkt;
	LANHelloHeader	*hdr;
	SystemType		adjType;
	AdjacencyEntry	*adj = NULL;
	int				i;
	int				match = 0;

        if (!parseLANHello(buf, len, &pkt)) {
                isisCounters.pduFormatErrors++;
                return;
        }
	
	IFTRACE(T_DUMPIIH)
		dumpLANIIH(circuit, &pkt);
	ENDTRACE

	hdr = pkt.hdr;

	/* if L1 IIH, check for area address match */
	if (hdr->packetType == L1LANHelloType) {
		if (!matchAreaAddrList(&pkt.areaAddrs, &systemAreaAddrs)) {
			adjInitFailureEvent(circuit, NULL, AreaMismatch, &hdr->sourceID, 1);
			return;
		}
		adjType = L1IS;
	} else {
		assert(hdr->packetType == L2LANHelloType);
		adjType = L2IS;

		/* ignore L2 IIH if we are L1 IS */
		if (systemType == L1IS)
			return;
	}
	
	/* look for an adjacency that matches the info from this packet */
	for (adj = locateAdjByMAC(sourceMAC); adj; adj = adj->hashNext) {
		if (equalID(adj->neighborMAC, sourceMAC, 6) &&
			equalID(adj->neighborSysID, hdr->sourceID, 6) &&
			circuit == adj->circuit &&
			adj->adjacencyType == adjType) {
			/*
			 *	This IIH exactly matches an existing adjacency entry.
			 *	Update ht, priority, and area list
			 */
			updateAdjHt(circuit, adj, pkt.holdingTimer);
			adj->LANPriority = hdr->priority;
			adj->ipaddrs = pkt.ifAddr;

			/* 
			 *	If the new LANID is different than current desig LAN ID, 
			 *	then this clues us in to the fact that the designated IS
			 *	has changed. Next time we run the election process, the
			 *	appropriate LnLSP IS neighbor's option will be
			 *	updated
			 */
			copyID(hdr->LANID, adj->desigLANID, 7);

			bzero((caddr_t) adj->neighborInfo, sizeof(AreaAddrList));
			bcopy((caddr_t)&pkt.areaAddrs, (caddr_t)adj->neighborInfo, 
				sizeof(AreaAddrList));
			IFTRACE(T_LANADJ)
				tracef("%s: Update Adjacency: %s %s: sys id %s", circuit->name,
					systemTypeToStr(adj->adjacencyType),
					adjStateToStr(adj->state),
					IDToStr(adj->neighborSysID, 6));
				trace_only_tf(isis_trace_options,
					      0,
					      (", snpa %s",
					       IDToStr(adj->neighborMAC, 6)));
			ENDTRACE
#ifdef	PROTO_SNMP
		{
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
						     ("processLANHello(): cannot locate entry in IS adj table for localId==%d, adj.name==%d", 
						      circuit->localId,
						      adj->name)); /* Where was adj->name assigned ??? */
				}
	            	} else {
		       		 trace_log_tf(isis_trace_options,
					      0,
					      LOG_ERR,
					      ("processLANHello(): cannot locate circ mib entry for localId==%d", 
					       circuit->localId));
	            	}
		}
#endif	/* PROTO_SNMP */
			break;
		}
	}

	if (!adj) {
		/* 
		 *	There is no adjacency entry that matches this IIH. Treat
		 *	the IIH as a new adjacency
		 */
		adj = createAdjacency(circuit, adjType, sourceMAC, pkt.holdingTimer,
			sizeof(AreaAddrList));
		if (adj == NULL)
			return;
		adj->type = AutoConfig;
		adj->state = AdjInitializing;
		adj->LANPriority = hdr->priority;
		copyID(hdr->sourceID, adj->neighborSysID, 6);
		copyID(hdr->LANID, adj->desigLANID, 7);
		adj->level2Only = circuit->manualL2Only;
		adj->ipaddrs = pkt.ifAddr;
		bcopy((caddr_t)&pkt.areaAddrs, (caddr_t)adj->neighborInfo, 
			sizeof(AreaAddrList));
		IFTRACE(T_LANADJ)
			tracef("%s: New Adjacency: %s: sys id %s", circuit->name,
				systemTypeToStr(adj->adjacencyType),
				IDToStr(adj->neighborSysID, 6));
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_INFO,
				     (", snpa %s",
				      IDToStr(adj->neighborMAC, 6)));
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
			    freshISAdjAreaAddrTable(pISAdjEntry, adj);
			    pISAdjEntry->isisISAdjState = 1;		/* state <= initializing */
			    queueAdd(&pCircEntry->isisISAdjTable, pISAdjEntry);
			} else {
		            trace_log_tf(isis_trace_options,
					 0,
					 LOG_ERR,
					 ("processLANHello(): cannot allocate entry in IS adj table for localId==%d, adj.name==%d", 
					  circuit->localId,
					  adj->name)); /* Where was adj->name assigned ??? */
			}
	            } else {
		        trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("processLANHello(): cannot locate circ mib entry for localId==%d", 
				      circuit->localId));
	            }
		}
#endif	/* PROTO_SNMP */

	}

	/*
	 *	Now make sure that I am advertised in the IIH pdu
	 *	(i.e., that the communication is two-way).
	 */
	for (i=0; i<pkt.count; i++) {
		if (match = equalID(pkt.ISneighbors[i], circuit->myMAC, 6))
			break;
	}

	if (adj->state == AdjInitializing && match) {
		/* transition adj to Up */
		adj->state = AdjUp;
		adjUpEvent(circuit, adj);
	} else if (adj->state == AdjUp && (!match)) {
		/* transition adj to Down */
		adjDownEvent(circuit, adj, OneWayConnection);
	}

	lanElection(circuit, (hdr->packetType == L1LANHelloType) ? 1 : 2);
}

/*
 *	Run the designated intermediate system election process. This function
 *	is called once by a timer. Subsequently, lanElection is
 *	called directly from the IIH transmit/receive functions.
 *
 *	The hold down flag is used to prevent the process from running until this
 *	procedure is called (initially) from a timer
 */
static Boolean holdDown = True;

void
lanFirstTimeElection(c)
CircuitEntry	*c;
{
	holdDown = False;
	switch (systemType) {
		case L1IS:
			lanElection(c, 1);
			break;
		case L2IS:
			if (!c->manualL2Only)
				lanElection(c, 1);
			lanElection(c, 2);
			break;
		default:
			assert(0);
	}
}

/*
 *	The system defined by 'adj' has become the designated IS
 *	
 *	Update c->circuitId structures and alter my LSP accordingly
 */
static void
changeDesigIS(c, level, adj)
CircuitEntry	*c;			/* circuit entry */
int				level;		/* L1 or L2 */
AdjacencyEntry	*adj;		/* adj to the elected system */
{
	lspDesigISChanged(c, level, (level==1) ? c->circuitId : c->l2CircuitId, adj->desigLANID);
	copyID(adj->desigLANID, (level==1) ? c->circuitId : c->l2CircuitId, 7);
#ifdef	PROTO_SNMP
	{
	    IsisMibEntry	*pMibEntry;
    	    IsisCircEntry	*pCircEntry;

	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable, c->localId);
	    if (pCircEntry) {
	        (level == 1)? 
		    copyOctetString(&pCircEntry->isisCircL1DesIS, adj->desigLANID, 7) :
		    copyOctetString(&pCircEntry->isisCircL2DesIS, adj->desigLANID, 7);
								/* Isis-Mib */
	    } else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("changeDesigIS(): cannot locate circ mib entry for localId==%d",
			      c->localId));
	    }
	}
#endif	/* PROTO_SNMP */
}

/*
 *	Return False if there is at least 1 IS or ES adjacency "up"
 */
int
isolated __PF1(c, CircuitEntry *)
{
	AdjacencyEntry	*scan;

	IterateDLListForw(scan, &c->isAdjs->links, AdjacencyEntry *) {
		if (scan->state == AdjUp)
			return(False);
	}
	IterateDLListForw(scan, &c->esAdjs->links, AdjacencyEntry *) {
		if ((scan->state == AdjUp) && (scan->type == AutoConfig))
			return(False);
	}
	/* guess we're isolated right now */
	return(True);
}

/*
 *	Run the designated IS election process for the level specified.
 */
void
lanElection(c, level)
CircuitEntry	*c;
int				level;
{
	AdjacencyEntry *scan;	/* placeholder */
	AdjacencyEntry *poss;	/* running best DR we've found so far */
	u_char bestPrior;	/* running highest priority we've found among our IS neighbors */
	MACAddress *bestMAC;	/* running mac address of best DR we've found so far */

	char *tmp;		/* these are all temporaries */
	char newDR[40];
	SystemID7 meAsDR;	

	if (holdDown)  
		return;
	
	/*
	 *	Even tho I may bring up adjacences to myself, 'poss' will never
	 *	be set to that adjacency because the priority and MAC addresses
	 *	are always the same
	 */
	poss = NULL;
	bestPrior = (level == 1) ? c->l1Priority : c->l2Priority;
	bestMAC = &(c->myMAC);
	IterateDLListForw(scan, &c->isAdjs->links, AdjacencyEntry *) {
		if ((scan->state == AdjUp) &&
			(scan->adjacencyType == ((level==1) ? L1IS : L2IS))) {
			/* possible candidate: check priority and MAC addr */
			if (scan->LANPriority > bestPrior) {
				poss = scan;
				bestPrior = poss->LANPriority;
				bestMAC = &(poss->neighborMAC);
			} else if (scan->LANPriority == bestPrior) {
				/* must check MAC addr for "higher" value */
				if (arrayCmp(scan->neighborMAC, *bestMAC, 6) > 0) {
					poss = scan;
					bestPrior = poss->LANPriority;
					bestMAC = &(poss->neighborMAC);
				}
			}
		}
	}

	/*
	 *	Now determine if I am elected, if I must resign, or if someone
	 *	else has been elected, or there has been no change.
	 *
	 *	If 'poss' is NULL, then I should be the designated IS. If
	 *	'poss' is not NULL, some other system should be the IS.
	 */
	if (poss) {
		/* There are other candidates for DR */
		if ((level==1) ? c->l1DR : c->l2DR) {
			/* 
			 *	I am the DR and now I lose 
			 */
			desigSysChangeEvent(c, level, False);
			changeDesigIS(c, level, poss);
			purgeMyPseudoLSP(c, level);	/* must purge BEFORE setting lnDR to false */
			if (level==1)
				c->l1DR = False;
			else
				c->l2DR = False;
		} else {
			/* 
			 *	if 'poss' was not advertised in the IIH, then it must have
			 *	just been elected (c->circuitId is filled in from
			 *	the LANID field of the IIH)
			 */
			if (!equalID(poss->desigLANID, (level==1) ? c->circuitId : c->l2CircuitId, 7)) {
				changeDesigIS(c, level, poss);
			}
		}
	} else {
		/* no other choices for DR */
		if (!((level==1) ? c->l1DR : c->l2DR)) {
			/* 
			 *	I am not the DR. If I have at least 1 adjacency up,
			 *	then declare myself DR
			 */
			if (!isolated(c)) {
				desigSysChangeEvent(c, level, True);
				if (level == 1) {
					purgeExistingPLSP(c, level);
					c->l1DR = True;
					solicitESConfig(c);

					/* make sure subsequent IIHs reflect my election results */
					copyID(systemID, meAsDR, 6);
					meAsDR[IDOFF] = c->localId;
					lspDesigISChanged(c, level, c->circuitId, meAsDR);
					/* STEVE XXX clean up this shit extra copy */
					copyID(systemID, c->circuitId, 6);
					c->circuitId[IDOFF] = c->localId;
				} else {
					purgeExistingPLSP(c, level);
					c->l2DR = True;

					/* make sure subsequent IIHs reflect my election results */
					copyID(systemID, meAsDR, 6);
					meAsDR[IDOFF] = c->localId;
					lspDesigISChanged(c, level, c->l2CircuitId, meAsDR);
					/* STEVE XXX clean up this shit extra copy */
					copyID(systemID, c->l2CircuitId, 6);
					c->l2CircuitId[IDOFF] = c->localId;
				}
				transmitMyPseudoLSP(c, level);
			} 
		}
	}
}

/*
 *	Given the information from an ESH, determine whether a new adjacency
 *	ought to be created, or if a current adjacency can be refreshed.
 *
 *	To refresh a current adj, the source MAC must match, the circuit
 *	must match, and all the NSAPs in the new ESH must be contained in
 *	the existing ESH
 */
void
processESAdj __PF5(c, CircuitEntry *,		/* incoming circuit */
		   numIds, int,			/* number of ES IDs */
		   idList, SystemID6 *,		/* ES IDs in adjacency */
		   ht, u_short,
		   sourceMAC, MACAddress)
{
	AdjacencyEntry	*adj = NULL;
	int				i;

	for (adj = locateAdjByMAC(sourceMAC); adj; adj = adj->hashNext) {
		if (equalID(adj->neighborMAC, sourceMAC, 6) &&
			c == adj->circuit &&
			numIds == adj->numIds &&
			adj->adjacencyType == ES) {
			/*
			 *	Check that all nsaps in idList are listed in the adj
			 */
			for (i=0; i<numIds; i++) {
				if (!IDMemberOf(idList[i], (SystemID6 *) adj->neighborInfo, adj->numIds))
					break;
			}
			/*
			 *	This ESH exactly matches an existing adjacency entry.
			 *	Just update ht.
			 */
			updateAdjHt(c, adj, ht);
			IFTRACE(T_LANADJ|T_P2PADJ)
				tracef("%s: Update Adjacency: ES: ", c->name);
				for (i=0; i<numIds; i++) {
					tracef("%s%c", IDToStr(idList[i], 6), 
						i<(numIds-1)?',':' ');
				}
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_INFO,
					     (NULL));
			ENDTRACE
			return;
		}
	}

	/*
	 *	This is a new adjacency
	 */
	adj = createAdjacency(c, ES, sourceMAC, ht, 6*numIds);
		if (adj == NULL)
			return;
	adj->type = AutoConfig;
	adj->state = AdjUp;
	adj->numIds = numIds;
	bcopy((caddr_t)idList, (caddr_t)adj->neighborInfo, 6*numIds);
	IFTRACE(T_LANADJ|T_P2PADJ)
		tracef("%s: New Adjacency: ES: ", c->name);
		for (i=0; i<numIds; i++) {
			tracef("%s%c", IDToStr(idList[i], 6), 
				i<(numIds-1)?',':' ');
		}
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_INFO,
			     (NULL));
	ENDTRACE

#ifdef	PROTO_SNMP_ESADJ_IS_ISADJ
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
		    freshISAdjAreaAddrTable(pISAdjEntry, adj);

		    queueAdd(&pCircEntry->isisISAdjTable, pISAdjEntry);
		} else {
	            trace_log_tf(isis_trace_options,
				 0,
				 LOG_ERR,
				 ("processESAdj(): cannot allocate entry in IS adj table for localId==%d, adj.name==%d", 
				  c->localId,
				  adj->name)); 
		}
            } else {
	        trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("processESAdj(): cannot locate circ mib entry for localId==%d", 
			      c->localId));
            }
	}
#endif	/* PROTO_SNMP_ESADJ_IS_ISADJ */

	adjUpEvent(c, adj);
}

/*
 *	Purge any existing pseudonde LSPs
 *
 *	If the circuitId (l2CircuitId) is not me, then it indicates the
 *	id of the previous designated router. Locate every LSP we know about
 *	from that router, and purge it.
 */
void
purgeExistingPLSP(c, level)
CircuitEntry	*c;
int				level;
{
	LSEntry	*ent;
	LSPID	lspID;
	if (!equalID(systemID, (level==1) ? c->circuitId : c->l2CircuitId, 6)) {
		bcopy((level==1) ? c->circuitId : c->l2CircuitId, &lspID, 7);
		if (ent = locateLowestLSP(level, lspID)) {
			while (ent && equalID(&ent->signature.id, 
				(level==1) ? c->circuitId : c->l2CircuitId, 7)) {
				if (!ent->onDeletedList)
					purgeLSP(ent);
				ent = ent->sortNext;
			}
		}
	}
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
