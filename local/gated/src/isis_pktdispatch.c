/*
 *  isis_pktdispatch.c,v 1.11 1993/01/07 22:39:51 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"

#ifdef	PROTO_SNMP
#include "isis_mib.h"				/* Isis-Mib */
#endif

void
pduInput(circuit, buf, len, sourceMAC)
CircuitEntry    *circuit;   /* circuit PDU arrived upon */
u_char			*buf;		/* buffer containing packet */
MACAddress sourceMAC;
int				len;		/* length of buffer */
{
        circuit->pdusReceived++;
#ifdef	PROTO_SNMP
	{
	    IsisMibEntry	*pMibEntry;
	    IsisCircEntry	*pCircEntry;

	    pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1);
	    pCircEntry = (IsisCircEntry *)locateEntry(&pMibEntry->isisCircTable,
								circuit->localId);
	    if (pCircEntry) {
	        ++pCircEntry->isisCircInCtrlPDUs;	/* Isis-Mib */
	    }
	    else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("pduInput(): cannot locate circ mib entry for localId==%d",
			      circuit->localId));
	    }
	}
#endif	/* PROTO_SNMP */

	switch (*buf) {
		case IntraDomainRPD:
			ISISpduInput(circuit, buf, len, sourceMAC);
			break;

		case ESISRPD:
			ESISpduInput(circuit, buf, len, sourceMAC);
			break;
		
		default:
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("pduInput: unknown OSI routing protocol x%x",
				      *buf));	
			break;
	}
}

/*
 *	Process the beginning of an ISIS PDU. Checks
 *		length field
 *	and dispatchs packet to correct input routine
 */
void
ISISpduInput(circuit, buf, len, sourceMAC)
CircuitEntry    *circuit;   /* circuit PDU arrived upon */
u_char			*buf;		/* buffer containing packet */
int				len;		/* length of buffer */
MACAddress		sourceMAC;
{
	CommonHeader	*hdr = (CommonHeader *)buf;
	u_short			hdrLen;	/* from packet */

	/* check that we have enough bytes to cast common header */
	if (len < sizeof(CommonHeader)) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("pduInput: buffer (%d) too small",
			      len));
                isisCounters.pduFormatErrors++;
		return;
	}

#define CHECK(field, value, errmsg)\
	if (field != value) {\
		trace_log_tf(isis_trace_options, 0, LOG_ERR, (errmsg, field, value));\
                isisCounters.pduFormatErrors++;\
		return;\
	}


	hdr->_packetType = GetPacketType(hdr->_packetType);
	switch (hdr->_packetType) {
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
				     ("pduInput: bad packet type %d", 
				      GetPacketType(hdr->_packetType)));
                        isisCounters.pduFormatErrors++;
			return;
	}

	CHECK(hdr->_headerLength, hdrLen, 
		"pduInput: bad header length %d (should be %d)");
	
	if (len < hdrLen) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("pduInput: buffer (%d) too small",
			      len));
                isisCounters.pduFormatErrors++;
		return;
	}

	CHECK(hdr->_versionProtoID, VersionProtoID, 
		"pduInput: bad version/Protocol ID %d (should be %d)");

#ifdef ndef
	CHECK(hdr->_version, Version, "pduInput: bad version %d (should be %d)");
#endif

	switch (hdr->_packetType) {
		case L1LANHelloType:
		case L2LANHelloType:
			if (circuit->circuitType == Broadcast)
				processLANHello(circuit, buf, len, sourceMAC);
			return;

		case PPHelloType:
			if (circuit->circuitType == Pt2Pt)
				processP2PHello(circuit, buf, len, sourceMAC);
			return;

		case L1LSType:
			if (!equalID(circuit->myMAC, sourceMAC, 6))
				processLSP(circuit, 1, buf, len);
			return;
		case L2LSType:
			if (!equalID(circuit->myMAC, sourceMAC, 6))
				processLSP(circuit, 2, buf, len);
			return;
		case L1CSNType:
			processCSNP(circuit, 1, buf, len);
			return;
		case L2CSNType:
			processCSNP(circuit, 2, buf, len);
			return;
		case L1PSNType:
			processPSNP(circuit, 1, buf, len);
			return;
		case L2PSNType:
			processPSNP(circuit, 2, buf, len);
			return;
		default:
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("pduInput: not done yet"));
			return;
	}
}

/*
 *	Process an incoming ESH/ISH
 */
void
ESISpduInput(circuit, buf, len, sourceMAC)
CircuitEntry    *circuit;   /* circuit PDU arrived upon */
u_char			*buf;		/* buffer containing packet */
int				len;		/* length of buffer */
MACAddress		sourceMAC;
{
	ESISHeader		*hdr = (ESISHeader	 *)buf;

	/* make sure there are enough bytes */
	if ((len < sizeof(ESISHeader)) || (hdr->headerLen > len)) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("ESISpduInput: packet too small"));
		return;
	}

	/* check checksum if necessary */
	if (!((hdr->cksum[0] == 0) && (hdr->cksum[1] == 0))) {
		if (iso_cksum((char *) hdr, hdr->headerLen, 0)) {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("ESISpduInput: invalid checksum"));
			return;
		}
	}

	hdr->type = GetPacketType(hdr->type);
	switch(hdr->type) {
		case ESHType:
			ESHInput(circuit, buf, len, sourceMAC);
			break;

		case ISHType:
			ISHInput(circuit, buf, len, sourceMAC);
			break;

		case RDType:
			;
	}
}

/*
 *	Parse the ESH into a list of system IDs. Then use
 *	that list of system IDs to create the ES adjacency
 */
void
ESHInput(circuit, buf, len, sourceMAC)
CircuitEntry    *circuit;   /* circuit PDU arrived upon */
u_char			*buf;		/* buffer containing packet */
int				len;		/* length of buffer */
MACAddress		sourceMAC;
{
	ESISHeader		*hdr = (ESISHeader	 *)buf;
	u_short			ht;		/* holding time */
	int				naddr = 0;
	SystemID6		idList[255/sizeof(SystemID6)];
	int				numIds = 0;

	U16toHost(hdr->ht, ht);
	len -= sizeof(ESISHeader);
	buf += sizeof(ESISHeader);

	if (len > 0) {
		naddr = *buf++;
		len--;
	} else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("ESHInput: packet too small"));
		return;
	}

	while (naddr-- > 0) {
		u_char	nsapLen;

		nsapLen = *buf++;
		len--;

		if (nsapLen <= len) {
			AreaAddr	areaAddr;

			if (parseNsap(buf, nsapLen, &areaAddr, idList[numIds]) < 0) {
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_ERR,
					     ("ESHInput: malformed nsap ignored"));
			} else {
				if (withinOurArea(&areaAddr)) {
					numIds++;
				} else {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("ESH Input: NSAP %A out of area ignored:",
						      sockbuild_iso((byte *) buf, nsapLen)));
				}
			}

			buf += nsapLen;
			len -= nsapLen;
		} else {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("ESHInput: packet too small"));
			return;
		}
	}

	if (numIds > 0)
		processESAdj(circuit, numIds, idList, ht, sourceMAC);
}

/*
 *	Parse the ISH and extract the NET.
 */
void
ISHInput(circuit, buf, len, sourceMAC)
CircuitEntry    *circuit;   /* circuit PDU arrived upon */
u_char			*buf;		/* buffer containing packet */
int				len;		/* length of buffer */
MACAddress		sourceMAC;
{
	ESISHeader		*hdr = (ESISHeader	 *)buf;
	u_short			ht;		/* holding time */
	u_char			netLen;

	U16toHost(hdr->ht, ht);
	len -= sizeof(ESISHeader);
	buf += sizeof(ESISHeader);

	if (len > 0) {
		netLen = *buf++;
		len--;
		if (netLen <= len) {
			/*
			 *	Buf points to the beginning of the net. The last 6 bytes
			 *	of the net is the ID. Pass this to processISH
			 */
			processISH(circuit, buf+(netLen-6), ht, sourceMAC);
		} else 
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("ISHInput: NET too small"));
	} else
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("ISHInput: packet too small"));
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
