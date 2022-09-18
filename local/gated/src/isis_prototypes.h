/*
 *  isis_prototypes.h,v 1.11 1993/01/07 22:39:53 jch Exp
 */

/* %(Copyright.header) */


#ifndef _isis_prototypes_h
#define _isis_prototypes_h

/* from isis_main.c */
PROTOTYPE(isis_init, extern void, (void));
PROTOTYPE(isis_var_init, extern void, (void));

/* from isis_globals.c */
PROTOTYPE(setAreaAddr, extern void, (u_char *));
PROTOTYPE(initGlobals, extern void, (int));

/* from isis_spf.c */
PROTOTYPE(isis_spf, extern void, (int));

/* from isis_spf_iter.c */
PROTOTYPE(spf_get_first_lsp, extern void, (struct lsp_iter_state *));
PROTOTYPE(set_subfield_state, extern void, (struct subfield_iter_state *));
PROTOTYPE(get_first_nodeaddr, extern octet *, (struct subfield_iter_state *, IS_ID *));
PROTOTYPE(get_next_nodeaddr, extern octet *, (struct subfield_iter_state *));

/* from isis_events.c */
PROTOTYPE(logAdjEvent, extern void, (CircuitEntry *, AdjacencyEntry *, const char *));
PROTOTYPE(adjInitFailureEvent, extern void, (CircuitEntry *, AdjacencyEntry *, ReasonCode, SystemID6 *, int));
PROTOTYPE(adjDownEvent, extern void, (CircuitEntry *, AdjacencyEntry *, ReasonCode));
PROTOTYPE(adjUpEvent, extern void, (CircuitEntry *, AdjacencyEntry *));
PROTOTYPE(desigSysChangeEvent, extern void, (CircuitEntry *, int, Boolean));
PROTOTYPE(circuitUpEvent, extern void, (CircuitEntry *));

/* from isis_flood.c */
PROTOTYPE(removeFromDeletedList, extern void, (LSEntry *));
PROTOTYPE(updateLifetime, extern void, (LSEntry *));
PROTOTYPE(normalLSPExpired, extern int, (LSEntry *));
PROTOTYPE(deletedLSPExpired, extern int, (LSEntry *));
PROTOTYPE(signalDecisionProcess, extern void, (int));
PROTOTYPE(firstLSP, extern LSEntry *, (int));
PROTOTYPE(newLSEntry, extern LSEntry *, (u_char *, int, LSSignature *));
PROTOTYPE(locateLSPByID, extern LSEntry *, (int, LSPID));
PROTOTYPE(locateLowestLSP, extern LSEntry *, (int, LSPID));
PROTOTYPE(correctedLifetime, extern u_short, (LSEntry *));
PROTOTYPE(floodPt2Pt, extern void, (task_timer *, time_t));
PROTOTYPE(floodBroadcast, extern void, (task_timer *, time_t));
PROTOTYPE(dumpDB, extern void, (void));
PROTOTYPE(storeLSEntry, extern void, (LSEntry *));
PROTOTYPE(updateLSEntry, extern Boolean, (LSEntry *, u_char *, int, LSSignature *));
PROTOTYPE(setFlags, extern void, (Boolean *, int, int));
PROTOTYPE(clrFlags, extern void, (Boolean *, int, int));
PROTOTYPE(printLSPContents, extern void, (FILE *, u_char *, int));
PROTOTYPE(CEToIndex, extern int, (CircuitEntry *));
PROTOTYPE(ackLSP, extern void, (CircuitEntry *, LSEntry *));
PROTOTYPE(sendLSP, extern void, (CircuitEntry *, LSEntry *));
PROTOTYPE(updateSeqAndFlood, extern void, (LSEntry *, long));
PROTOTYPE(ackAndFlood, extern void, (CircuitEntry *, LSEntry *));
PROTOTYPE(markForDeletion, extern void, (LSEntry *, int));
PROTOTYPE(purgeLSP, extern void, (LSEntry *));
PROTOTYPE(dumpLSPList, extern void, (AgeList *));
PROTOTYPE(dumpLSPDB, extern void, (FILE *, int));
PROTOTYPE(floodAllLSPs, extern void, (CircuitEntry *, int));
PROTOTYPE(isis_freelseChangeList, extern void, (void));

/* from isis_lanhello.c */
PROTOTYPE(lanElection, extern void, (CircuitEntry *, int));
PROTOTYPE(lanFirstTimeElection, extern void, (CircuitEntry *));
PROTOTYPE(purgeExistingPLSP, extern void, (CircuitEntry *, int));
PROTOTYPE(isolated, extern int, (CircuitEntry *));
PROTOTYPE(sendLANHello, extern int, (CircuitEntry *, Unsigned8));
PROTOTYPE(processLANHello, extern void, (CircuitEntry *, u_char *, int, MACAddress));
PROTOTYPE(processESAdj, extern void, (CircuitEntry *, int, SystemID6 *, u_short, MACAddress));

/* from isis_lsp.c */
PROTOTYPE(updateAreaAddrs, extern void, (AreaAddrList *, LSPOption *));
PROTOTYPE(lspChanged, extern void, (LSPDesc *));
PROTOTYPE(enterLSPOverload, extern void, (LSSignature *));
PROTOTYPE(newLSPGroup, extern LSPGroup *, (u_char, u_char));
PROTOTYPE(addIPReachToLSP, extern prefIP *, (LSPGroup *, MetricList, struct in_addr, struct in_addr, u_char, as_path *));
PROTOTYPE(addPrefixNeighbor, extern prefISO *, (LSPGroup *, MetricList, octet *, int, as_path *));
PROTOTYPE(addESNeighbor, extern LSPOptPtr, (LSPGroup *, MetricList, int, SystemID6));
PROTOTYPE(lspIPPrefixChanged, extern void, (prefIP *, MetricList));

/* from isis_pktdispatch.c */
PROTOTYPE(ISISpduInput, extern void, (CircuitEntry *, u_char *, int, MACAddress));
PROTOTYPE(ESISpduInput, extern void, (CircuitEntry *, u_char *, int, MACAddress));
PROTOTYPE(ISHInput, extern void, (CircuitEntry *, u_char *, int, MACAddress));
PROTOTYPE(ESHInput, extern void, (CircuitEntry *, u_char *, int, MACAddress));

/* from isis_snp.c */
PROTOTYPE(sendCSNP, extern void, (CircuitEntry *, int));
PROTOTYPE(generateCSNP, extern void, (task_timer *, time_t));
PROTOTYPE(generatePSNP, extern void, (task_timer *, time_t));

/* from isis_adjacency.c */
PROTOTYPE(ageListInsert, extern void, (AgeList *, u_char *));
PROTOTYPE(ageListRemove, extern void, (AgeList *, u_char *));
PROTOTYPE(locateAdjByMAC, extern AdjacencyEntry *, (MACAddress));
PROTOTYPE(startAdjScan, extern AdjacencyEntry *, (void));
PROTOTYPE(nextAdj, extern AdjacencyEntry *, (void));
PROTOTYPE(newAgeList, extern AgeList *, (PTIF, u_short));
PROTOTYPE(createAdjacency, extern AdjacencyEntry *, (CircuitEntry *, SystemType, MACAddress, u_short, int));
PROTOTYPE(adjacencyExpired, extern int, (AdjacencyEntry *));
PROTOTYPE(ageListAge, extern void, (void));
PROTOTYPE(removeAdjFromHash, extern void, (AdjacencyEntry *));
PROTOTYPE(initOldAdjacencies, extern void, (void));
PROTOTYPE(deleteOldAdjacencies, extern void, (int));
PROTOTYPE(addOldAdjacency, extern void, (AdjacencyEntry *));
PROTOTYPE(updateAdjHt, extern void, (CircuitEntry *, AdjacencyEntry *, u_short));

/* from isis_circuit.c */
PROTOTYPE(createCircuit, extern CircuitEntry *, (int, CircuitType, char *, MetricList, MetricList, 
						 u_char, u_char, Boolean, MACAddress, int));
PROTOTYPE(changeCircuit, extern void, (CircuitEntry *, MetricList, MetricList, u_char, u_char));

PROTOTYPE(circuitL1IIHTimeout, extern void, (task_timer *, time_t));
PROTOTYPE(circuitL2IIHTimeout, extern void, (task_timer *, time_t));
PROTOTYPE(circuitP2PIIHTimeout, extern void, (task_timer *, time_t));
PROTOTYPE(isisDie, extern void, (void));
PROTOTYPE(solicitESConfig, extern void, (CircuitEntry *));
PROTOTYPE(switchToIS, extern void, (void));

/* from isis_common.c */
PROTOTYPE(getTimeOfDay, extern long, (void));
PROTOTYPE(LSPinsertAreaAddrList, extern u_char *, (AreaAddrList, u_char *));
PROTOTYPE(insertAreaAddrList, extern u_char *, (AreaAddrList, u_char *));
PROTOTYPE(insertPadding, extern u_char *, (u_char *, int));
PROTOTYPE(typeToStr, extern const char *, (int));
PROTOTYPE(circuitLevelToStr, extern char *, (u_char));
PROTOTYPE(circuitTypeToStr, extern const char *, (CircuitType));
PROTOTYPE(IDToStr, extern char *, (u_char *, int));
PROTOTYPE(LSPIDToStr, extern char *, (LSPID));
PROTOTYPE(flagsToStr, extern char *, (flag_t));
PROTOTYPE(systemTypeToStr, extern const char *, (SystemType));
PROTOTYPE(reasonCodeToStr, extern const char *, (ReasonCode));
PROTOTYPE(adjStateToStr, extern const char *, (AdjacencyState));
PROTOTYPE(LSSigToStr, extern char *, (LSSignature *));
PROTOTYPE(addCommon, extern int, (CommonHeader *, u_int));
PROTOTYPE(mallocOrDie, extern caddr_t, (int));
PROTOTYPE(justMalloc, extern char *, (int));
PROTOTYPE(dumpBuffer, extern void, (u_char *, int));
PROTOTYPE(transmitPacket, extern void, (CircuitEntry *, MACAddress, u_char *, int));
PROTOTYPE(printAreaAddrList, extern void, (const char *, AreaAddrList *));
PROTOTYPE(matchAreaAddr, extern int, (AreaAddr *, AreaAddr *));
PROTOTYPE(matchAreaAddrList, extern int, (AreaAddrList *, AreaAddrList *));
PROTOTYPE(withinOurArea, extern Boolean, (AreaAddr *));
PROTOTYPE(arrayCmp, extern int, (u_char *, u_char *, int));
PROTOTYPE(parseNsap, extern int, (u_char *, u_char, AreaAddr *, u_char *));
PROTOTYPE(IDMemberOf, extern int, (SystemID6, SystemID6 *, int));
PROTOTYPE(enableRoutingModule, extern void, (void));
PROTOTYPE(disableRoutingModule, extern void, (void));
PROTOTYPE(LSPIDtoStr, extern char *, (LSPID));

/* from isis_dual.c */
PROTOTYPE(insertProtoSup, extern u_char *, (u_char *, Boolean));
PROTOTYPE(insertIPaddr, extern u_char *, (CircuitEntry *, u_char *, Boolean));
PROTOTYPE(setIPReachable, extern prefIP *, (int, u_char, MetricList, struct in_addr, struct in_addr, as_path *));
PROTOTYPE(clearIPReachable, extern void, (int, u_char, prefIP *));
PROTOTYPE(addIPAddr, extern void, (CircuitEntry *, struct in_addr));

/* from isis_gated_util.c */
#if (_BSD > 43) || (BSD > 43)
PROTOTYPE(Transmit, extern int, (CircuitEntry *, MACAddress, u_char *, int));
#else
PROTOTYPE(Transmit, extern int, (void));
#endif

/* from isis_netdutil.c */
PROTOTYPE(netdTransmitSock, extern int, (void));
PROTOTYPE(netdReceiveSock, extern int, (char *));
PROTOTYPE(netdTransmit, extern void, (int, int, char *, char *, int));
PROTOTYPE(netdReceive, extern int, (int, char *, int, sockaddr_un *, int, int *));

/* from isis_parseutil.c */
PROTOTYPE(retrieveAreaAddr, extern AreaAddr *, (char));
PROTOTYPE(storeAreaAddr, extern char, (u_char *));
PROTOTYPE(parseProtoSup, extern u_int, (u_char *, u_char));

/* from isis_timer.c */
PROTOTYPE(feepTimer, extern void, (void));

/* from isis_trollutil.c */
PROTOTYPE(trollTransmit, extern int, (CircuitEntry *, MACAddress, char *, int));

#endif	/* _isis_prototypes_h */

/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
