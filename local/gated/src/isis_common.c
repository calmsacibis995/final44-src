/*
 *  isis_common.c,v 1.11 1993/01/07 22:39:06 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"
#ifdef	PROTO_SNMP
#include "isis_mib.h"				/* Isis-Mib */
#endif	/* PROTO_SNMP */
#include "isis_globals.h"

/*
 *	Fill in the common portion of an IS-IS header. Most values
 *	are zero or constants. The type is used to compute the header
 *	length field as well as to set the type field.
 */
int
addCommon(hdr, type)
CommonHeader	*hdr;
u_int 			type;
{
	u_char	hdrLen;

	bzero((caddr_t)hdr, sizeof(hdr));
	hdr->_packetID = IntraDomainRPD;
	switch(type) {
		case L1LANHelloType:	hdrLen = sizeof(LANHelloHeader); break;
		case L2LANHelloType:	hdrLen = sizeof(LANHelloHeader); break;
		case PPHelloType:	hdrLen = sizeof(PPHelloHeader); break;
		case L1LSType:	hdrLen = sizeof(LSPHeader); break;
		case L2LSType:	hdrLen = sizeof(LSPHeader); break;
		case L1CSNType:	hdrLen = sizeof(CSNHeader); break;
		case L2CSNType:	hdrLen = sizeof(CSNHeader); break;
		case L1PSNType:	hdrLen = sizeof(PSNHeader); break;
		case L2PSNType:	hdrLen = sizeof(PSNHeader); break;
		default:
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("addCommon: bad packet type"));
			return(NOTOK);
	}
	hdr->_headerLength = hdrLen;
	hdr->_versionProtoID = VersionProtoID;
	hdr->_version = Version;
	hdr->_packetType = type;

	return(OK);
}

const char *
typeToStr(type)
int	type;
{
	switch(type) {
	case L1LANHelloType:
	    return("L1 IIH");

	case L2LANHelloType:
	    return("L2 IIH");
	    
	case PPHelloType:
	    return("PP IIH");
	    
	case L1LSType:
	    return("L1 LSP");
	    
	case L2LSType:
	    return("L2 LSP");
	    
	case L1CSNType:
	    return("L1 CSNP");

	case L2CSNType:
	    return("L2 CSNP");

	case L1PSNType:
	    return("L1 PSNP");

	case L2PSNType:
	    return("L2 PSNP");
	    
	default:
	    return("unknown");
	}
}

const char *
reasonCodeToStr(code)
ReasonCode	code;
{
	switch (code) {
		case HoldingTimerExpired: return("HoldingTimerExpired");
		case ChecksumError: return("ChecksumError");
		case OneWayConnection: return("OneWayConnection");
		case CircuitDisabled: return("CircuitDisabled");
		case VersionSkew: return("VersionSkew");
		case AreaMismatch: return("AreaMismatch");
		case TooManyLANIS: return("TooManyLANIS");
		case TooManyLANES: return("TooManyLANES");
		case WrongSystemType: return("WrongSystemType");
		case IDMismatch: return("IDMismatch");
		default: {
			static char	buf[80];
			sprintf(buf, "unknown code x%x", code);
			return(buf);
		}
	}
}

#define	MAX_COLUMNS	8
/*
 *	Dump the buffer to the screen in a readable format. Format is:
 *
 *		hex/dec  where hex is the hex format, dec is the decimal format.
 *		columns of hex/dec numbers will be printed, followed by the
 *		character representations (if printable).
 */
void
dumpBuffer __PF2(buf, u_char *,
		 len, int)
{
	int		i,j;

	for (i = 0; i < len; i += MAX_COLUMNS) {
		tracef("+%3d: ", i);
		for (j = 0; j < MAX_COLUMNS; j++) {
			if (i + j < len) {
				tracef("%02x/%-3d	", buf[i+j], buf[i+j]);
			} else {
				tracef("	");
			}
		}

		for (j = 0; j < MAX_COLUMNS; j++) {
			if (i + j < len) {
				if (((buf[i+j]) > 31) && ((buf[i+j]) < 128))
					tracef("%c", buf[i+j]);
				else
					tracef(".");
			}
		}
		trace_only_tf(isis_trace_options,
			      0,
			      (NULL));
	}
}

/* 
 *	insert the area address list into the buffer. Assume the buffer
 *	is big enough
 */
u_char *
insertAreaAddrList(list, bp)
AreaAddrList	list;
u_char			*bp;
{
	int 		i;
	u_char		*optlen, *orig = bp;
	AreaAddr	*aa;

	/* first add the code and length */
	*bp++ = AreaAddressCode;
	optlen = bp++;
	for (i=0; i<list.count; i++) {
		aa = retrieveAreaAddr(list.areaAddr[i]);
		*bp++ = aa->len;
		bcopy((caddr_t)aa->addr, (caddr_t)bp, aa->len);
		bp += aa->len;
	}
	*optlen = (bp - orig) - 2;
	return(bp);
}

/*
 *	Same as above but don't include the code and length 
 */
u_char *
LSPinsertAreaAddrList(list, bp)
AreaAddrList	list;
u_char			*bp;
{
	int 		i;
	AreaAddr	*aa;

	for (i=0; i<list.count; i++) {
		aa = retrieveAreaAddr(list.areaAddr[i]);
		*bp++ = aa->len;
		bcopy((caddr_t)aa->addr, (caddr_t) bp, aa->len);
		bp += aa->len;
	}
	return(bp);
}


/*
 *	Create enough padding options to pad as close to 'len' bytes of 
 *	bp.
 */
u_char *
insertPadding(bp, len)
u_char	*bp;
int		len;
{
	u_char	padLen;

	while (len >= 2) {
		len -= 2;
		padLen = (len > 255) ? 255 : len;
		*bp++ = PaddingCode;
		*bp++ = padLen;
		len -= padLen;
		bp += padLen;
	}
	return(bp);
}

/*
 *	Malloc size bytes and zero. If memory can't be found, quit.
 */
caddr_t
mallocOrDie(size)
int size;
{
	caddr_t	bp = (caddr_t) task_mem_malloc(isis_task, size);
	bzero(bp, size);
	return(bp);
}

caddr_t
justMalloc(size)
int size;
{
	caddr_t	bp = (caddr_t) task_mem_malloc(isis_task, size);
	if (bp) bzero(bp, size);
	return(bp);
}

char *
IDToStr(id, size)
u_char	*id;
int		size;
{
	int i;
	static char buf[40];

	if (size == 6) {
		sprintf(buf, "%02x%02x.%02x%02x.%02x%02x",
			id[0],id[1],id[2],id[3],id[4],id[5]);
		return(buf);
	} else if (size == 7) {
		sprintf(buf, "%02x%02x.%02x%02x.%02x%02x[%c%x]",
			id[0],id[1],id[2],id[3],id[4],id[5],(id[6]==0)?'N':'P',id[6]);
		return(buf);
	}

	buf[0] = (char)0;
	for (i=0; i<size; i++) {
		char	tmp[4];

		sprintf(tmp, "%02x", id[i]);
		strcat(buf, tmp);
		if (i < (size-1))
			strcat(buf, ":");
	}

	return(buf);
}

const char *
circuitTypeToStr(type)
CircuitType	type;
{
	switch(type) {
		case Broadcast: return("broadcast");
		case Pt2Pt: return("Pt-2-Pt");
		default:
			return("unknown");
	}
}

char *
circuitLevelToStr __PF1(
	    level, u_char)
{
	static char buf[40];

	buf[0] = 0;
	if (level & L1Circuit)
		strcat(buf, "L1 ");
	if (level & L2Circuit)
		strcat(buf, "L2 ");
	
	return(buf);
}

char *
flagsToStr(flags)
flag_t flags;
{
	static char buf[20];

	buf[0] = 0;

	if (flags & SUPPORT_IP)
		strcat(buf, "IP ");
	if (flags & SUPPORT_CLNP)
		strcat(buf, "CLNP ");
	
	return(buf);
}


void
printAreaAddrList __PF2(indent, const char *,
			list, AreaAddrList *)
{
	int i;
	AreaAddr	*aa;

	for (i=0; i<list->count; i++) {
		int j;
		aa = retrieveAreaAddr(list->areaAddr[i]);
		tracef("%sAreaAddr [%d] ", indent, aa->len);
		for (j=0; j<aa->len; j++) {
			tracef("%02x%c", aa->addr[j], 
				j<(aa->len-1) ? '.' : ' ');
		}
		trace_only_tf(isis_trace_options,
			      0,
			      (NULL));
	}
}

/* return true if a1 matches a2 */
int
matchAreaAddr __PF2(a1, AreaAddr *,
		    a2, AreaAddr *)
{
	return (a1->len == a2->len && equalID(a1->addr, a2->addr, a1->len));
}

/*
 *	Return true if any address in l1 matches any address in l2
 */
int
matchAreaAddrList __PF2(l1, AreaAddrList *,
			l2, AreaAddrList *)
{
	int	i1, i2;

	for (i1=0; i1<l1->count; i1++) {
		for (i2=0; i2<l2->count; i2++) {
			if (l1->areaAddr[i1] == l2->areaAddr[i2])
				return(True);
		}
	}
	return(False);
}

/* 
 *	Return true if the area address is within one of the configured areas
 */
Boolean
withinOurArea __PF1(areaAddr, AreaAddr *)
{
	int	i;

	for (i=0; i<systemAreaAddrs.count; i++) {
		if (matchAreaAddr(retrieveAreaAddr(systemAreaAddrs.areaAddr[i]),
			areaAddr))
			return(True);
	}
	return(False);
}


const char *
systemTypeToStr(t)
SystemType t;
{
	switch(t) {
		case Unknown: return("Unknown");
		case ES: return("ES");
		case IS:  return("IS");
		case L1IS:  return("L1IS");
		case L2IS: return("L2IS");
		default: return("Really Unknown!");
	}
}

const char *
adjStateToStr(state)
AdjacencyState	state;
{
	switch(state) {
		case AdjInitializing: return("Initializing");
		case AdjUp: return("Up");
		case AdjFailed: return("Failed");
		default: return("unknown state");
	}
}


/*
 *	Compare a and b as unsigned len*8 bit integers. Return -1, 0, or 1 if
 *	a is less than, equal to, or greater than b, respectively.
 */
int
arrayCmp __PF3(a, u_char *,
	       b, u_char *,
	       len, int)
{
	int		i;
	for (i=0; i<len; i++) {
		if (a[i] != b[i])
			if (a[i] > b[i])
				return(1);
			else
				return(-1);
	}
	return(0);
}


/*
 *	Parse an nsap into an area address and system ID.
 *	If the nsap is malformed, return -1. 
 */
int
parseNsap __PF4(nsap, u_char *,
		nsapLen, u_char,
		areaAddr, AreaAddr *,
		sysID, u_char *)
{
	char	areaAddrLen;

	if ((nsapLen < 8) || nsapLen > 20)
		return(-1);
	
	/* STEVE - system ID and NSEL lengths hardcoded here */
	areaAddrLen = nsapLen - 7;
	bcopy((caddr_t) nsap, (caddr_t) areaAddr->addr, areaAddrLen);
	areaAddr->len = areaAddrLen;
	bcopy((caddr_t) nsap+areaAddrLen, (caddr_t) sysID, 6);

	return(areaAddrLen);
}

/*
 *	return true if Id is present in IdList
 */
int
IDMemberOf __PF3(Id, SystemID6,
		 IdList, SystemID6 *,
		 numInList, int)
{
	int i;
	for (i=0; i<numInList; i++) {
		if (equalID(Id, IdList[i], 6))
			return(True);
	}
	return(False);
}

/* these are defined in the gated test environment; we cheat
	and define them here also so link without gated will work.
*/
int run_from_log;
int isis_time;

long
getTimeOfDay()
{
	/* should be an ifdef for this but not set up right yet */
	if (run_from_log) /* simulation mode -> use isis_time */
		return isis_time;
	return(time_sec);
}


void
enableRoutingModule __PF0(void)
{
        routingModuleState = ModuleUp;
}

/* disable the routing module, set timer to enable */
void
disableRoutingModule __PF0(void)
{
        trace_tf(isis_trace_options,
		 TR_NORMAL,
		 0,
		 ("disable routing module"));
        routingModuleState = ModuleDown;
        setTimer(maximumAge+zeroAgeLifetime, enableRoutingModule, NULL);
}

char *
LSPIDtoStr __PF1(id, LSPID)
{
	static char	buf[100], tmp[100];

	if (id.pseudonodeID)
		sprintf(buf, "P%d", id.pseudonodeID);
	else
		sprintf(buf, "N");

#define HEXPRINT
#ifdef HEXPRINT
	sprintf(tmp, "#%d (%s)", id.LSPNumber,
		IDToStr((u_char *)&id.sourceID, 6)); 
#else
	bzero(tmp, 100);
	sprintf(tmp, "#%d (", id.LSPNumber);
	strncat(tmp, id.sourceID, 6);
	strcat(tmp, ")");
#endif 	/* HEXPRINT */

	strcat(buf, tmp);
	return(buf);
}

char *
LSSigToStr(sig)
LSSignature	*sig;
{
	static char	buf[100], tmp[100];

	sprintf(buf, "L%d %s", sig->level, LSPIDtoStr(sig->id));

	sprintf(tmp, " [seq:%d ttl:%d]", sig->seqNum, sig->lifetime);
	strcat(buf, tmp);

	return(buf);
}


/*
 *	Transmit a packet
 */
void
transmitPacket(c, macAddr, buf, len)
CircuitEntry	*c;
MACAddress		macAddr;
u_char			*buf;
int				len;
{
        if (routingModuleState == ModuleUp) {
                (*c->transmitFunc) (c, macAddr, buf, len);
                c->pdusSent++;
#ifdef	PROTO_SNMP
		{
		    IsisMibEntry	*pMibEntry;
		    IsisCircEntry	*pCircEntry;

		    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
		    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable,
								             c->localId);
		    if (pCircEntry) {
		        ++pCircEntry->isisCircOutCtrlPDUs;	/* Isis-Mib */
  	     	    }
		    else {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("transmitPacket(): cannot locate circ entry for localId==%d",
				      c->localId));
		    }
		}
#endif	/* PROTO_SNMP */

        }
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
