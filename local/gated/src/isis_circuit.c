/*
 *  isis_circuit.c,v 1.11 1993/01/07 22:39:05 jch Exp
 */

/* %(Copyright.header) */


#define	INCLUDE_IOCTL
#define	INCLUDE_CLNP
#define	INCLUDE_ESIS
#define	INCLUDE_SNPA
#include "include.h"
#include "isis_includes.h"

PROTOTYPE(startSolicitES, static void, (CircuitEntry *));
PROTOTYPE(stopSolicitES, static void, (CircuitEntry *));

static char localId = 1;

/*
 * Change circuit's metric, priority, or timer values.
 */
void
changeCircuit __PF5(c, CircuitEntry *,
		    l1Metric, MetricList,
		    l2Metric, MetricList,
		    l1Priority, u_char,
		    l2Priority, u_char)
{
	c->helloInterval = sysISHInterval;
	c->ISIShelloInterval = sysIIHInterval;
	c->holdingTimer = sysHoldingTimer;
	c->l1Metric = l1Metric;
	c->l2Metric = l2Metric;
	c->l1Priority = l1Priority;
	c->l2Priority = l2Priority;
}

static void
isis_circuit_terminate __PF1(tp, task *)
{
    CircuitEntry *c = (CircuitEntry *) tp->task_data;

    task_delete(tp);
    c->timer_l1iih = c->timer_l2iih = c->timer_p2piih = (task_timer *) 0;
}


CircuitEntry *
createCircuit __PF10(
	    fd, int,
	    type, CircuitType,
	    name, char *,
	    l1Metric, MetricList, l2Metric, MetricList,
	    l1Priority, u_char, l2Priority, u_char,
	    manl2, Boolean,
	    myMAC, MACAddress,
	    kernindex, int)
{
	CircuitEntry	*c;
	int i;

	if (!(c = castMalloc(CircuitEntry *, sizeof(CircuitEntry)))) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("createCircuit: can't allocate circuit entry"));
		isisDie();
	}
	isisCounters.circuitEntries++;

	/* set the metric S bits */
	l1Metric.defalt = (l1Metric.defalt & 0x3f);
	l1Metric.delay = 0x80 | (l1Metric.delay & 0x3f);
	l1Metric.expense = 0x80 | (l1Metric.expense & 0x3f);
	l1Metric.error = 0x80 | (l1Metric.error & 0x3f);

	l2Metric.defalt = (l2Metric.defalt & 0x3f);
	l2Metric.delay = 0x80 | (l2Metric.delay & 0x3f);
	l2Metric.expense = 0x80 | (l2Metric.expense & 0x3f);
	l2Metric.error = 0x80 | (l2Metric.error & 0x3f);

	strncpy(c->name, name, CircuitNameLen-1);
	c->kernindex = kernindex;
	c->summarized = 0;
	c->circuitType = type;
	c->helloInterval = sysISHInterval;
	c->ISIShelloInterval = sysIIHInterval;
	c->holdingTimer = sysHoldingTimer;
	c->l1Metric = l1Metric;
	c->l2Metric = l2Metric;
	c->l1Priority = l1Priority;
	c->l2Priority = l2Priority;
	c->manualL2Only = manl2;
	c->up = False;
	c->localId = localId++;

	/* the local ID may be the pseudonode ID -- so it can't be zero */
	assert(c->localId != 0);

	/* initially, the LANID is this system's ID and I am the designated IS */
	copyID(systemID, c->circuitId, 6);
	c->circuitId[IDOFF] = c->localId;
	copyID(c->circuitId, c->l2CircuitId, 7);
	c->l1DR = c->l2DR = False;

	copyID(myMAC, c->myMAC, 6);

	/* initialize my pseudonode LSPs (broadcast only) */
	if (c->circuitType == Broadcast) {
		c->l1PLSP = newLSPGroup(L1LSType, c->localId);
		c->l2PLSP = newLSPGroup(L2LSType, c->localId);
	}

	c->esAdjs = newAgeList(adjacencyExpired, 
		Offset(AdjacencyEntry, remainingTime));

	c->isAdjs = newAgeList(adjacencyExpired, 
		Offset(AdjacencyEntry, remainingTime));

	for (i=0; i<MaximumCircuits; i++) {
		if (circuitList[i] == NULL) {
			circuitList[i] = c;
			break;
		}
	}
	if (i >= MaximumCircuits) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("createCircuit: maximum number of circuits exceeded"));
		isisDie();
	}

	c->fd = fd;

	/* associate a task to handle the timers */
	sprintf(c->task_name, "IS-IS %s", c->name);
	c->task = task_alloc(c->task_name,
			     TASKPRI_PROTO,
			     isis_trace_options);
	task_set_terminate(c->task, isis_circuit_terminate);
	c->task->task_data = (void_t) c;
	if (!task_create(c->task)) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("createCircuit: can't create task for %s", c->name));
		isisDie();
	}
	/* STEVE XXX - should probably set rtproto bit on ifap here rather than in isis_main */

	/* create the hello timers */
	if (c->circuitType == Broadcast) {
		c->timer_l1iih =  task_timer_create(c->task,
						    "L1.hello",
						    (flag_t) 0,
						    (time_t) 0,
						    (time_t) 0,
						    circuitL1IIHTimeout,
						    (void_t) 0);
		c->timer_l2iih = task_timer_create(c->task,
						   "L2.hello",
						   (flag_t) 0,
						   (time_t) 0,
						   (time_t) 0,
						   circuitL2IIHTimeout,
						   (void_t) 0);
	} else {
		c->timer_p2piih=  task_timer_create(c->task,
						    "P2P.hello",
						    (flag_t) 0,
						    (time_t) 0,
						    (time_t) 0,
						    circuitP2PIIHTimeout,
						    (void_t) 0);
	}

	return(c);
}


/*
 *	Called periodically to transmit IIHs for the circuit
 */
void
circuitL1IIHTimeout __PF2(tip, task_timer *,
			  interval, time_t)
{
	CircuitEntry *c = (CircuitEntry *) tip->task_timer_task->task_data;

	switch (systemType) {
		case L1IS:
			sendLANHello(c, L1LANHelloType);
			break;
		case L2IS:
			if (!c->manualL2Only)
				sendLANHello(c, L1LANHelloType);
			break;
		default:
			assert(0);
	}
        if (c->l1DR) {
		task_timer_set(tip, sysDRIIHInterval, (time_t) 0);
        } else {
		task_timer_set(tip, c->ISIShelloInterval, (time_t) 0);
	}
}

void
circuitL2IIHTimeout __PF2(tip, task_timer *,
			  interval, time_t)
{
	CircuitEntry *c = (CircuitEntry *) tip->task_timer_task->task_data;
	time_t offset;

	switch (systemType) {
		case L2IS:
			sendLANHello(c, L2LANHelloType);
			break;
		default:
			assert(0);
	}

	/* add a small offset to avoid sending L2 immediately after L1 (this isn't a guarantee, however) */
	offset = (interval == (time_t) 0) ? 1 : 0;
        if (c->l2DR) {
		task_timer_set(tip, sysDRIIHInterval, offset);
        } else {
		task_timer_set(tip, c->ISIShelloInterval, offset);
	}
}

/*
 *	Transmit a packet on circuit 'c'. If the identity of the system at the
 *	other end of the link is known, and it is a router, then send an IIH.
 *	Otherwise, send an ISH.
 */
void
circuitP2PIIHTimeout __PF2(tip, task_timer *,
			   interval, time_t)
{
	CircuitEntry *c = (CircuitEntry *) tip->task_timer_task->task_data;

	if (!DLListEmpty(&c->isAdjs->links)) {
		AdjacencyEntry	*adj = DLListForw(&c->isAdjs->links, AdjacencyEntry *);
		switch (adj->adjacencyType) {
			case L1IS:
			case L2IS:
			case IS:
				sendP2PHello(c, 0);	/* send P2P hello without padding */
				break;
			
			default:
				sendISHello(c);
		}
	} else {
		sendISHello(c);
	}

	task_timer_set(tip, sysIIHInterval, (time_t) 0);
}

static Boolean inESConfigure = False;
static int configSock = -1;

void
solicitESConfig(c)
CircuitEntry    *c;
{
#if (_BSD > 43) || (BSD > 43)
        startSolicitES(c);
#endif  
}

/*
 *      Close up shop. Change into an ES and exit.
 */
void
isisDie()
{
#if	(_BSD > 43) || (BSD > 43)
        struct systype_req      req;

        req.sr_type = SNPA_ES;
        req.sr_esconfigt = sysDefaultESHelloTimer;
        req.sr_configt = 60;
        req.sr_holdt = 120;

        /* set settings */
	ioctl(configSock, SIOCSSTYPE, &req);
#endif  
        task_quit(EINVAL);
}

#if	(_BSD > 43) || (BSD > 43)
static void
stopSolicitES(c)
CircuitEntry *c;
{
        struct systype_req      req;

        req.sr_type = SNPA_IS;
        req.sr_esconfigt = sysDefaultESHelloTimer;
        req.sr_configt = c->helloInterval;
        req.sr_holdt = c->holdingTimer;

        /* set settings */
	if (ioctl(configSock, SIOCSSTYPE, &req) < 0) {
        	perror("stopSolicitES: cannot set system configuration ");
		return;
    	}
        inESConfigure = False;
}

/*
 *      Tell kernel to start sending out ISHs
 */
void
switchToIS __PF0(void)
{
        struct systype_req req;

	if (configSock == -1) {
		if ((configSock = socket(AF_ISO, SOCK_DGRAM, ISOPROTO_CLTP)) < 0) {
			perror("kernel ES/IS control socket: socket");
			isisDie();
		}
	}
	if (ioctl(configSock, SIOCGSTYPE, &req) < 0) {
		perror("switchToIS - can't get system configuration: ");
		isisDie();
	}
        req.sr_type = SNPA_IS;
	if (ioctl(configSock, SIOCSSTYPE, &req) < 0) {
		perror("switchToIS: can't set system configuration ");
		isisDie();
	}
}

static void
startSolicitES(c)
CircuitEntry *c;
{
        struct systype_req      req;

        if (inESConfigure)
                return;

        req.sr_type = SNPA_IS;
        req.sr_esconfigt = sysPollESHelloRate;
        req.sr_configt = c->ISIShelloInterval;
        req.sr_holdt = c->holdingTimer * HoldingMultiplier;
        /* set settings */
	if (ioctl(configSock, SIOCSSTYPE, &req) < 0) {
		perror("startSolicitES: ioctl set");
		return;
	}
        inESConfigure = True;
        setTimer(HoldingMultiplier * c->ISIShelloInterval, stopSolicitES, c);
}
#endif	/* (_BSD > 43) || (BSD > 43) */



/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
