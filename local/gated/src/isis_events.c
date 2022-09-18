/*
 *  isis_events.c,v 1.11 1993/01/07 22:39:15 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"

#ifdef	PROTO_SNMP
#include "isis_mib.h"				/* Isis-Mib */
#endif

void
adjInitFailureEvent __PF5(circuit, CircuitEntry *,
			  adj, AdjacencyEntry *,
			  reason, ReasonCode,
			  id, SystemID6 *,		/* list of IDs of failing system */
			  numIds, int)			/* number in list */
{
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("%s: IS-IS adj init failure: reason %s",
		      circuit->name,
		      reasonCodeToStr(reason)));
        circuit->initFailures++;
#ifdef	PROTO_SNMP
	{
	    IsisMibEntry	*pMibEntry;
	    IsisCircEntry	*pCircEntry;

	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable,
								circuit->localId);
	    if (pCircEntry) {
	        ++pCircEntry->isisCircInitFails;		/* Isis-Mib */
	    }
	    else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("adjInitFailureEvent(): cannot locate circ mib entry for localId==%d",
			      circuit->localId));
	    }
	}
#endif	/* PROTO_SNMP */

}

void
adjUpEvent __PF2(circuit, CircuitEntry *,
		 adj, AdjacencyEntry *)
{
	logAdjEvent(circuit, adj, "IS-IS adj up");
	lspAdjUp(circuit, adj);
#ifdef	PROTO_SNMP
	{
    	    IsisMibEntry	*pMibEntry;
    	    IsisCircEntry	*pCircEntry;
	    IsisISAdjEntry	*pISAdjEntry;

    	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
    	    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable,
							       circuit->localId);
    	    if (pCircEntry) {
		pISAdjEntry = (IsisISAdjEntry *)locateEntry(&pCircEntry->isisISAdjTable, adj->name);
		if (pISAdjEntry) {
		    freshISAdjEntry(pISAdjEntry, adj);		/* Isis-Mib */
		    freshISAdjAreaAddrTable(pISAdjEntry, adj);
		    pISAdjEntry->isisISAdjState = 2;		/* state <= up */
		} else {
	            trace_log_tf(isis_trace_options,
				 0,
				 LOG_ERR,
				 ("adjUpEvent(): cannot locate entry in IS adj table for localId==%d, adj.name==%d", 
				  circuit->localId,
				  adj->name));
		}
            } else {
	        trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("adjUpEvent(): cannot locate circ mib entry for localId==%d",
			      circuit->localId));
            }
	}
#endif	/* PROTO_SNMP */
}


void
adjDownEvent(circuit, adj, reason)
CircuitEntry	*circuit;	/* circuit adjacency is on */
AdjacencyEntry	*adj;
ReasonCode	reason;		/* reason for failure */
{
	char s[80];

	if ((adj->state == AdjUp) && (reason == OneWayConnection)) {
		/* we went from up to initializing - neighbor must have restarted */
		const char *t = "IS-IS adj up->initializing (neighbor not hearing me or restarted)"; 
		logAdjEvent(circuit, adj, t);
		lspAdjDown(circuit, adj);
		adj->state = AdjInitializing;
	} else if (adj->state == AdjUp) {
		sprintf(s, "IS-IS adj up->down (%s)", reasonCodeToStr(reason));
		logAdjEvent(circuit, adj, s);
		adj->state = AdjFailed;
		lspAdjDown(circuit, adj);
	} else if (adj->state == AdjInitializing) {
		/* we went from initializing to down */
		sprintf(s, "IS-IS adj initializing->down (%s)", reasonCodeToStr(reason));
		logAdjEvent(circuit, adj, s);
		adj->state = AdjFailed;
	}
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
		    if (adj->state == AdjFailed) {
		        if (queueDelete(&pCircEntry->isisISAdjTable, pISAdjEntry)) {
	                    trace_log_tf(isis_trace_options,
					 0,
					 LOG_ERR,
					 ("adjDownEvent(): cannot delete entry in IS adj table for circIndex==%d, adjIndex==%d", 
					  pISAdjEntry->isisISAdjIndex,
					  pISAdjEntry->isisISAdjIndex)); /* Isis-Mib */
		        }
		    } else {
		    	pISAdjEntry->isisISAdjState = 1;		/* state <= initializing */
		    }
		} else {
	            trace_log_tf(isis_trace_options,
				 0,
				 LOG_ERR,
				 ("adjDownEvent(): cannot locate entry in IS adj table for localId==%d, adj.name==%d", 
				  circuit->localId,
				  adj->name));
		}
            } else {
	        trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("adjDownEvent(): cannot locate circ mib entry for localId==%d",
			      circuit->localId));
            }
	}
#endif	/* PROTO_SNMP */

	if (adj->state == AdjFailed) {
		removeAdjFromHash(adj);
		/* 
	 	 *	if we are called due to a timer expiration, the adj has already been
	 	 *	removed from the linked list. Otherwise, remove it now.
	 	 */
		if (reason != HoldingTimerExpired)
			DLLRemque(adj);

		/* schedule this adjacency to be deleted after next spf is run */
		addOldAdjacency(adj);
	}
}


void
desigSysChangeEvent __PF3(circuit, CircuitEntry *,
			  level, int,
			  elected, Boolean)		/* true => elected, false => resigned */
{
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("IS-IS DR change: %s: L%d %s",
		      circuit->name,
		      level, 
		      elected ? "elected" : "resigned"));
        if (level == 1) {
                circuit->l1DesignateChanges++;
#ifdef	PROTO_SNMP
		{
		    IsisMibEntry	*pMibEntry;
	    	    IsisCircEntry	*pCircEntry;

		    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
		    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable,
								circuit->localId);
		    if (pCircEntry) {
		        ++pCircEntry->isisCircLANL1DesISChanges;	/* Isis-Mib */
		    }
		    else {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("desigSysChangeEvent(): cannot locate circ mib entry for localId==%d",
				      circuit->localId));
		    }
		}
#endif	/* PROTO_SNMP */

	}
        else {
                circuit->l2DesignateChanges++;
#ifdef	PROTO_SNMP
		{
	    	    IsisMibEntry	*pMibEntry;
	    	    IsisCircEntry	*pCircEntry;

		    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
		    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable,
								circuit->localId);
		    if (pCircEntry) {
		        ++pCircEntry->isisCircLANL2DesISChanges;	/* Isis-Mib */
		    }
		    else {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("desigSysChangeEvent: cannot locate circ mib entry for localId==%d",
				      circuit->localId));
		    }
		}
#endif	/* PROTO_SNMP */

	}
}


void
logAdjEvent __PF3(circuit, CircuitEntry *,
		  adj, AdjacencyEntry *,
		  msg, const char *)
{
	int i;

	tracef("%s: %s: %s %s",
	       msg,
	       circuit->name,
	       systemTypeToStr(adj->adjacencyType),
	       adj->level2Only ? "(L2 only)" : "");

        circuit->adjacencyEvents++;
#ifdef	PROTO_SNMP
	{
	    IsisMibEntry	*pMibEntry;
	    IsisCircEntry	*pCircEntry;

	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable,
								circuit->localId);
	    if (pCircEntry) {
	        ++pCircEntry->isisCircAdjChanges;	/* Isis-Mib */
	    }
	    else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("logAdjEvent(): cannot locate circ mib entry for localId==%d",
			      circuit->localId));
	    }

	}
#endif	/* PROTO_SNMP */

	switch (adj->adjacencyType) {
		case L1IS:
		case L2IS:
#define	HEXPRINT
#ifdef	HEXPRINT
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("%s",
				      IDToStr(adj->neighborSysID, 6)));
#else
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("%s",
				      adj->neighborSysID));
#endif	/* HEXPRINT */
			break;
		case ES:
			if (circuit->circuitType == Broadcast) {
			    trace_log_tf(isis_trace_options,
					 0,
					 LOG_ERR,
					 ("SNPA %s",
					  IDToStr(adj->neighborMAC, 6)));
			} else {
			    tracef("Neighbor%s", (adj->numIds>1) ? "s":" ");
			    for (i=0; i<adj->numIds; i++) {
				tracef("%s%c", IDToStr(&adj->neighborInfo[i*6], 6),
				       i<(adj->numIds-1)?',':' ');
			    }
			    trace_log_tf(isis_trace_options,
					 0,
					 LOG_ERR,
					 (NULL));
			}

			break;
		default:
			assert(0);
	}
}

/*
 *	Called when a circuit is turned on
 *
 *	1) transmit an IIH PDU
 *	2) solicit the end system configuration
 *	3) set a timer to run the election process
 */
void
circuitUpEvent __PF1(c, CircuitEntry *)
{
	c->circuitChanges++;

	if (c->circuitType == Broadcast) {
		switch (systemType) {
			case L1IS:
				circuitL1IIHTimeout(c->timer_l1iih, (time_t) 0);
				break;

			case L2IS:
				if (!c->manualL2Only) {
					circuitL1IIHTimeout(c->timer_l1iih, (time_t) 0);
				}
				circuitL2IIHTimeout(c->timer_l2iih, (time_t) 0);
				break;
			default:
				assert(0);
		}

		setTimer(sysIIHInterval * 2, lanFirstTimeElection, c);
		solicitESConfig(c);
	} else if (c->circuitType == Pt2Pt) {
		circuitP2PIIHTimeout(c->timer_p2piih, (time_t) 0);
	}

	lspCircuitUp(c);
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
