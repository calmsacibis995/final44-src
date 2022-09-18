/*
 *  isis_snp.c,v 1.11 1993/01/07 22:39:55 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"

PROTOTYPE(sendPSNP, static void, (CircuitEntry *, int));

/*
 *	Sequence number PDU routines
 */

/*
 *	Called every completeSNPInterval seconds
 *
 *	Construct and transmit CSNPs for every circuit for which we are a
 *	designated router (L1 and L2).
 */
void
generateCSNP __PF2(tip, task_timer *,
		   interval, time_t)

{
	int	i;
	CircuitEntry	*c;

	for (i=0; i<MaximumCircuits; i++) {
		if ((c = circuitList[i]) && (c->circuitType == Broadcast)) {
			if (c->l1DR)
				sendCSNP(c, 1);
			if (c->l2DR)
				sendCSNP(c, 2);
		}
	}
	task_timer_set(tip, (time_t) completeSNPInterval, (time_t) 0);
}

/*
 *	Called every partialSNPInterval seconds
 *
 *	Construct and transmit a PSNP for every circuit
 *
 *	Send PSNPs on every circuit for which we are not the designated router
 */
void
generatePSNP __PF2(tip, task_timer *,
		   interval, time_t)
{
	int	i;
	CircuitEntry	*c;

	for (i=0; i<MaximumCircuits; i++) {
		if (c = circuitList[i]) {
			switch (systemType) {
				case L2IS:
					if (!c->l2DR)
						sendPSNP(c, 2);
					if (c->manualL2Only)
						break;
					/* ELSE FALL THROUGH */
				case L1IS:
					if (!c->l1DR)
						sendPSNP(c, 1);
					break;
				default:
					assert(0);
			}
		}
	}
	task_timer_set(tip, (time_t) partialSNPInterval, (time_t) 0);
}

/* 
 *	Create a entry in a SNP from the info in 'ent'.
 *	Return the new value of bp
 */
static u_char *
addEntry(ent, bp)
LSEntry	*ent;
u_char	*bp;
{
	Unsigned16	u16;
	Unsigned32	u32;

	/* remaining lifetime */
	hostToU16(correctedLifetime(ent), u16); 
	bcopy((caddr_t)&u16, (caddr_t)bp, sizeof(u16)); bp += sizeof(u16);

	/* lsp id */
	copyID(&ent->signature.id, bp, sizeof(LSPID)); bp += sizeof(LSPID);

	/* lsp seq number */
	hostToU32(ent->signature.seqNum, u32);
	bcopy((caddr_t)&u32, (caddr_t)bp, sizeof(u32)); bp += sizeof(u32);

	/* checksum */
	hostToU16(ent->signature.checksum, u16); 
	bcopy((caddr_t)&u16, (caddr_t)bp, sizeof(u16)); bp += sizeof(u16);

	return(bp);
}

/*
 *	Parse a 16 byte sequence numbers entry
 */
static u_char *
parseEntry(snent, bp)
SNEntry	*snent;
u_char	*bp;
{
	Unsigned16	u16;
	Unsigned32	u32;

	/* remaining lifetime */
	bcopy((caddr_t)bp, (caddr_t)&u16, sizeof(u16)); bp += sizeof(u16);
	U16toHost(u16, snent->lifetime); 

	/* lsp id */
	copyID(bp, &snent->id, sizeof(LSPID)); bp += sizeof(LSPID);

	/* lsp seq number */
	bcopy((caddr_t)bp, (caddr_t)&u32, sizeof(u32)); bp += sizeof(u32);
	U32toHost(u32, snent->number); 

	/* checksum */
	bcopy((caddr_t)bp, (caddr_t)&u16, sizeof(u16)); bp += sizeof(u16);
	U16toHost(u16, snent->checksum); 

	return(bp);
}

#define	EncodedSNEntrySize	16	/* space taken by each SN entry */
#define MaxOptionEntries	15	/* entries per option */

/*
 *	Build PSNP for circuit and level specified.
 */
LSEntry	*lastL1Ent = NULL, *lastL2Ent = NULL;

static void
sendPSNP(c, level)
CircuitEntry	*c;				/* circuit to transmit CSNPs on */
int				level;			/* level 1 or 2 */
{
	u_char		buf[MaxPacketSize], *bp = buf;
	u_short		bufSize = 0, len;
	LSEntry		*scan, *scanStart;
	PSNHeader	*hdr = NULL;
	Boolean		firstPass = True;
	u_char		*optLength = NULL;	/* ptr to option length byte */
	int			entryCount = 0;		/* # of entries in current option */

	if (level == 1) {
		if (lastL1Ent == NULL)
			lastL1Ent = firstLSP(1);
		scan = lastL1Ent;
	} else {
		if (lastL2Ent == NULL)
			lastL2Ent = firstLSP(2);
		scan = lastL2Ent;
	}

	scanStart = scan;

	/*
	 *	Initialize the PSNP header
	 */
	bzero((caddr_t)buf, sizeof(buf));
	hdr = (PSNHeader *)buf;
	bp = buf + sizeof(PSNHeader);
	bufSize = (level == 1) ? origL1LSPBufSize : origL2LSPBufSize;
	addCommon(&hdr->common, (level == 1) ? L1PSNType : L2PSNType);
	copyID(systemID, hdr->sourceID, 6);

	/*
	 *	Add to the PSNP while there is room in the PSNP and there
	 *	are LSEntries we have not yet scanned. May need to create
	 *	new option header
	 */
	while (((bufSize - (bp - buf)) >= (EncodedSNEntrySize+2)) &&
		(firstPass || (scan != scanStart))) {

		/* add PSNP entry if SSN flag is set for this circuit */
		if (scan->SSN[CEToIndex(c)]) {

			/* fuss with option header */
			if ((optLength == NULL) || (entryCount >= MaxOptionEntries)) {
				if (optLength) {
					/* finish option if necessary */
					assert(entryCount*EncodedSNEntrySize < 255);
					*optLength = entryCount*EncodedSNEntrySize;
				}
				/* Initialize new option header */
				entryCount = 0;
				*bp++ = LSPEntries;
				optLength = bp++;
			}

			bp = addEntry(scan, bp);
			entryCount++;
			IFTRACE(T_PSNP)
				trace_only_tf(isis_trace_options,
					      0,
					      ("PSNPoutput: %s: add %s",
					       c->name, 
					       LSSigToStr(&scan->signature)));
			ENDTRACE
			clrFlags(scan->SSN, SingleCircuit, CEToIndex(c));
		}

		/* go to next entry in a circular fashion */
		firstPass = 0;
		scan = scan->sortNext;
		if (scan == NULL)
			scan = firstLSP(level);
	}

	/* save where we left off */
	if (level == 1) {
		lastL1Ent = scan;
	} else {
		lastL2Ent = scan;
	}

	/* tidy up the packet and transmit (only if we have something to send) */
	if (bp > (buf + sizeof(PSNHeader))) {
		/* finish option last option */
		assert(entryCount*EncodedSNEntrySize < 255);
		assert(optLength != NULL);
		*optLength = entryCount*EncodedSNEntrySize;

		len = bp - buf;
		hostToU16(len, hdr->pduLength); 
		transmitPacket(c, level == 1 ? AllL1ISmac : AllL2ISmac, buf, len);
	}
}

static LSPID lastId = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

/*
 *	Build a series of CSNPs and xmit them on the broadcast circuit
 *	Currently, ignores the throttle on transmission of CSNPs.
 */
void
sendCSNP(c, level)
CircuitEntry	*c;				/* circuit to transmit CSNPs on */
int				level;			/* level 1 or 2 */
{
	u_char		buf[MaxPacketSize], *bp = buf;
	u_short		bufSize = 0, len;
	LSEntry		*ent, *lastEnt = NULL;
	Boolean		firstPass = True;
	CSNHeader	*hdr = NULL;
	u_char		*optLength = NULL;	/* ptr to option length byte */
	int			entryCount = 0;		/* # of entries in current option */

	for (ent = firstLSP(level); ent; lastEnt = ent, ent = ent->sortNext) {
		if (firstPass || ((bufSize - (bp - buf)) < (EncodedSNEntrySize+2))) {
			if (!firstPass) {
				/*
				 *	Finish off packet and transmit
				 */
				assert(entryCount*EncodedSNEntrySize < 255);
				*optLength = entryCount*EncodedSNEntrySize;
				optLength = NULL;

				copyID(&lastEnt->signature.id, &hdr->end, sizeof(LSPID));
				len = bp - buf;
				hostToU16(len, hdr->pduLength); 
				IFTRACE(T_CSNP)
					trace_only_tf(isis_trace_options,
						      0,
						      ("CSNPoutput: %s: end %s",
						       c->name, 
						       LSPIDtoStr(hdr->end)));
				ENDTRACE
				transmitPacket(c, level == 1 ? AllL1ISmac : AllL2ISmac, 
					buf, len);
			}

			/*
			 *	Initialize the CSNP header
			 */
			bzero((caddr_t)buf, sizeof(buf));
			hdr = (CSNHeader *)buf;
			bp = buf + sizeof(CSNHeader);
			bufSize = (level == 1) ? origL1LSPBufSize : origL2LSPBufSize;
			addCommon(&hdr->common, (level == 1) ? L1CSNType : L2CSNType);
			copyID(systemID, hdr->sourceID, 6);
			if (firstPass) {
				/* first CSNP must start with lsp id of all zeros */
				bzero((caddr_t) &hdr->start, sizeof(LSPID));
			} else {
				copyID(&ent->signature.id, &hdr->start, sizeof(LSPID));
			}
			firstPass = False;

			IFTRACE(T_CSNP)
				trace_only_tf(isis_trace_options,
					      0,
					      ("CSNPoutput: %s: start %s",
					       c->name, 
					       LSPIDtoStr(hdr->start)));
			ENDTRACE
		}

		/* fuss with option header */
		if ((optLength == NULL) || (entryCount >= MaxOptionEntries)) {
			if (optLength) {
				/* finish option if necessary */
				assert(entryCount*EncodedSNEntrySize < 255);
				*optLength = entryCount*EncodedSNEntrySize;
			}
			/* Initialize new option header */
			entryCount = 0;
			*bp++ = LSPEntries;
			optLength = bp++;
		}
		bp = addEntry(ent, bp);
		entryCount++;
		IFTRACE(T_CSNP)
			trace_only_tf(isis_trace_options,
				      0,
				      ("CSNPoutput: add %s",
				       LSSigToStr(&ent->signature)));
		ENDTRACE
	}

	if (bp > (buf + sizeof(CSNHeader))) {
		/*
		 *	Finish off packet and transmit
		 */
		assert(entryCount*EncodedSNEntrySize < 255);
		*optLength = entryCount*EncodedSNEntrySize;
		copyID(&lastId, &hdr->end, sizeof(LSPID));
		len = bp - buf;
		hostToU16(len, hdr->pduLength); 
		IFTRACE(T_CSNP)
			trace_only_tf(isis_trace_options,
				      0,
				      ("CSNPoutput: %s: end %s",
				       c->name, 
				       LSPIDtoStr(hdr->end)));
		ENDTRACE
		transmitPacket(c, level == 1 ? AllL1ISmac : AllL2ISmac, buf, len);
	}
}

void
processSNPEntry __PF3(c, CircuitEntry *,
		      snSig, LSSignature *,		/* from SNP */
		      isCSNP, int)			/* true if this is on behalf of CSNP, false for PSNP */
{
	LSEntry		*dbent;

	IFTRACE(T_PSNP|T_CSNP)
		tracef("SNPlookup: %s: %s", c->name, LSSigToStr(snSig));
	ENDTRACE

	if (dbent = locateLSPByID(snSig->level, snSig->id)) {
		IFTRACE(T_PSNP|T_CSNP)
			tracef(" Found");
		ENDTRACE
/* STEVE XXX - 
		if (isCSNP) dbent->foundInSNP = True;
 */
		if (equalLSP(snSig, &dbent->signature)) {
			IFTRACE(T_PSNP|T_CSNP)
				trace_only_tf(isis_trace_options,
					      0,
					      (" Equal"));
			ENDTRACE
			if (((snSig->lifetime) && (dbent->signature.lifetime)) && 
				(snSig->checksum != dbent->signature.checksum)) {
				/*
				 *	LSPs claim to be identical, but are really different
				 *	If I generated it, flood it back out. Otherwise, purge it.
				 */
				if ((equalID(systemID, snSig->id.sourceID, 6)) &&
					(locallyGenerated(dbent))) {
					updateSeqAndFlood(dbent, dbent->signature.seqNum);
				} else {
					purgeLSP(dbent);
				}
			} else {
				/* LSPs are really the same */
/* STEVE XXX -
 * moved it here
 */
				if (isCSNP) dbent->foundInSNP = True;
				if (c->circuitType == Pt2Pt) {
					clrFlags(dbent->SRM, SingleCircuit, CEToIndex(c));
				}
			}
		} else if (olderLSP(snSig, &dbent->signature)) {
			/*
			 *	The neighbor has an older version. Send a newer copy back
			 */
			IFTRACE(T_PSNP|T_CSNP)
				trace_only_tf(isis_trace_options,
					      0,
					      (" Older (SRM)"));
			ENDTRACE
			sendLSP(c, dbent);
		} else {
			/*
			 *	snent is newer than the database pdu. Set the SSN flags
			 *	so that a PSNP will be sent (acting as a request for the
			 *	newer info).
			 */
			IFTRACE(T_PSNP|T_CSNP)
				trace_only_tf(isis_trace_options,
					      0,
					      (" Newer (SSN)"));
			ENDTRACE
			setFlags(dbent->SSN, SingleCircuit, CEToIndex(c));
			if (c->circuitType == Pt2Pt) {
				clrFlags(dbent->SRM, SingleCircuit, CEToIndex(c));
			}
		}
	} else {
		/*
		 *	We don't have any info about this LSP. Create a dummy entry
		 *	in the LSP database, and set the SSN flag so that a subsequently
		 *	generated PSNP will request that we get that LSP
		 */
		IFTRACE(T_PSNP|T_CSNP)
			tracef(" Not Found");
		ENDTRACE
		if (equalID(systemID, snSig->id.sourceID, 6)) {
			/* 
		 	 * Don't do anything if this LSP is ours (we just haven't gotten 
		 	 * around to generating our own LSP yet).
		 	 */
			IFTRACE(T_PSNP|T_CSNP)
				tracef(" ours - ignored");
			ENDTRACE
		} else if ((snSig->lifetime) && (snSig->seqNum) && (snSig->checksum)) {
			snSig->seqNum = 0;
			if ((dbent = newLSEntry(NULL, 0, snSig)) == NULL) {
				enterLSPOverload(snSig);
			} else {
				setFlags(dbent->SSN, SingleCircuit, CEToIndex(c));
				IFTRACE(T_PSNP|T_CSNP)
					tracef(" set SSN");
				ENDTRACE
			}
		}
		IFTRACE(T_PSNP|T_CSNP)
			trace_only_tf(isis_trace_options,
				      0,
				      (NULL));
		ENDTRACE
	}
}

/*
 *	Fill in the LSSignature from the SNEntry 
 */
void
snToSig(snEnt, snSig, level)
SNEntry		*snEnt;
LSSignature	*snSig;
int level;
{
	snSig->lifetime = snEnt->lifetime;
	snSig->seqNum = snEnt->number;
	snSig->id = snEnt->id;
	snSig->checksum = snEnt->checksum;
	snSig->level = level;
}

void
processCSNP(c, level, buf, len)
CircuitEntry	*c;
int				level;
u_char			*buf;
int				len;
{
	CSNHeader	*hdr = (CSNHeader *)buf;
	u_char		*bp = buf + sizeof(CSNHeader);
	SNEntry		snEnt;
	LSSignature	snSig;
	u_short		pduLen;
	LSEntry		*startEnt, *scanEnt;

	U16toHost(hdr->pduLength, pduLen); 
	if (len < pduLen) {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("processCSNP: short CSNP ignored"));
		return;
	} else if (len > pduLen)
		len = pduLen;

	/* ignore my own CSNP */
	if (equalID(systemID, hdr->sourceID, 6))
		return;

	len -= sizeof(CSNHeader);

	IFTRACE(T_CSNP)
		trace_only_tf(isis_trace_options,
			      0,
			      ("CSNPinput: %s: from %s",
			       c->name, 
			       IDToStr((u_char *)&hdr->sourceID, 7)));
		trace_only_tf(isis_trace_options,
			      0,
			      ("CSNPinput: %s: start %s",
			       c->name, 
			       LSPIDtoStr(hdr->start)));
	ENDTRACE

	while (len >= 2) {
		u_char	optCode = *bp++;
		u_char	optLen = *bp++;

		if (optLen > (len - 2)) {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("CSNPinput: option too long"));
			return;
		}
		len -= (2 + optLen);

		switch (optCode) {
			case LSPEntries:
				while (optLen >= EncodedSNEntrySize) {
					bp = parseEntry(&snEnt, bp);
					optLen -= EncodedSNEntrySize;
					snToSig(&snEnt, &snSig, level);
					processSNPEntry(c, &snSig, 1);	/* 1 tells it to set foundInSNP */
				}
				break;
			case IPAuthInfoCode:
				bp += optLen;
				break;
			default:
				IFTRACE(T_PSNP)
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("CSNPinput: %s: unknown packet option", 	
						      c->name));
				ENDTRACE
				bp += optLen;
				break;
		}
	}

	IFTRACE(T_CSNP)
		trace_only_tf(isis_trace_options,
			      0,
			      ("CSNPinput: %s: end %s",
			       c->name, 
			       LSPIDtoStr(hdr->end)));
	ENDTRACE

	/*
	 *	Now look for any LSPID within start & end range
	 *	that were not present in the CSNP. Set the SRM flags for
	 *	those LSPs (except if they have zero ttl or seq num)
	 */
#ifdef notdef
/* STEVE XXX - sorry, this doesn't work when the complete database doesn't fit
   into one CSNP.  In that case this turns into a floodfest.  In the
   case that the neighbor is missing stuff, he's broken and is basically
   screwed (see section 7.3.15.3, which defines "complete set of CSNPs").
*/

	if (hdr->start.LSPNumber != 0) {
		/*
		 *	To cover the case where my neighbor has only LSPs numbered
		 *	greater than zero, I will start my check from #0 (so those
		 *	numbered less than "start.LSPNumber" will be transmitted 
		 *	(if my neighbor needs them). Ditto case for 'end': my
		 *	neighbor may have up to LSP #4, but I have #5 and #6. So set
		 *	end.LSPNumber to 255, so that I will catch those LSP #s greater
		 *	than end.
		 */
		hdr->start.LSPNumber = 0;
		hdr->end.LSPNumber = 255;
	}
#endif
	startEnt = locateLSPByID(level, hdr->start);
	if (startEnt == NULL) {
		/* 
		 *	I can't find the starting LSP by hashing (perhaps because I
		 *	changed the LSPNumber above to zero. Resort to a linear scan 
		 *	of the LSP database and set startEnt equal to the first
		 *	LSP with ID >= start
		 */
		for (startEnt = firstLSP(level); startEnt &&
			(LSPIDcmp(&startEnt->signature.id, &hdr->start) < 0);
			startEnt = startEnt->sortNext)
			;
	}

	for (scanEnt = startEnt; scanEnt && 
		(LSPIDcmp(&scanEnt->signature.id, &hdr->end) <= 0);
		scanEnt = scanEnt->sortNext) {

		if (scanEnt->foundInSNP) 
			scanEnt->foundInSNP = False;
		else {
			if (scanEnt->signature.lifetime && scanEnt->signature.seqNum) {
				setFlags(scanEnt->SRM, SingleCircuit, CEToIndex(c));
				IFTRACE(T_CSNP)
					trace_only_tf(isis_trace_options,
						      0,
						      ("CSNPinput: %s: XMIT %s",
						       c->name, 
						       LSSigToStr(&scanEnt->signature)));
				ENDTRACE
			}
		}
	}
}

/*
 *	Process a partial sequence numbers packet.
 *	Only look at the packet if this is a pt2pt link, or I am
 *	the designated router
 */
void
processPSNP(c, level, buf, len)
CircuitEntry	*c;
int				level;
u_char			*buf;
int				len;
{
	if ((c->circuitType == Pt2Pt) || (level == 1 && c->l1DR) ||
		(level == 2 && c->l2DR)) {
		PSNHeader	*hdr = (PSNHeader *)buf;
		u_char		*bp = buf + sizeof(PSNHeader);
		SNEntry		snEnt;
		LSSignature	snSig;
		u_short		pduLen;

		U16toHost(hdr->pduLength, pduLen); 
		if (len < pduLen) {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("processPSNP: short PSNP ignored"));
			return;
		} else if (len > pduLen)
			len = pduLen;

		/* ignore my own PSNP */
		if (equalID(systemID, hdr->sourceID, 6))
			return;


		len -= sizeof(PSNHeader);

		IFTRACE(T_PSNP)
			trace_only_tf(isis_trace_options,
				      0,
				      ("PSNPinput: %s: from %s",
				       c->name, 
				       IDToStr((u_char *)&hdr->sourceID, 7)));
		ENDTRACE

		while (len >= 2) {
			u_char	optCode = *bp++;
			u_char	optLen = *bp++;

			if (optLen > (len - 2)) {
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_ERR,
					     ("PSNPinput: option too long"));
				return;
			}
			len -= (2 + optLen);

			switch (optCode) {
				case LSPEntries:
					while (optLen >= EncodedSNEntrySize) {
						bp = parseEntry(&snEnt, bp);
						optLen -= EncodedSNEntrySize;
						snToSig(&snEnt, &snSig, level);
						processSNPEntry(c, &snSig, 0);	/* 0 tells it not to set foundInSNP */
					}
					break;
				case IPAuthInfoCode:
					bp += optLen;
					break;
				default:
					IFTRACE(T_PSNP)
						trace_log_tf(isis_trace_options,
							     0,
							     LOG_ERR,
							     ("PSNPinput: %s: unknown packet option", 	
							      c->name));
					ENDTRACE
					bp += optLen;
					break;
			}
		}
	}
}

/*
 *	Build and transmit a specific PSNP for signature, 
 *	circuit and level specified.
 */
void
sendSpecificPSNP(c, level, sig)
CircuitEntry	*c;				/* circuit to transmit CSNPs on */
int				level;			/* level 1 or 2 */
LSSignature		*sig;
{
	u_char		buf[MaxPacketSize], *bp = buf;
	u_short		bufSize = 0, len;
	PSNHeader	*hdr = NULL;
	Unsigned16	u16;
	Unsigned32	u32;

	/*
	 *	Initialize the PSNP header
	 */
	bzero((caddr_t)buf, sizeof(buf));
	hdr = (PSNHeader *)buf;
	bp = buf + sizeof(PSNHeader);
	bufSize = (level == 1) ? origL1LSPBufSize : origL2LSPBufSize;
	addCommon(&hdr->common, (level == 1) ? L1PSNType : L2PSNType);
	copyID(systemID, hdr->sourceID, 6);

	/*
	 *	Add specific entry to PSNP
	 */
	*bp++ = LSPEntries;			/* code */
	*bp++ = EncodedSNEntrySize;	/* length */

	/* remaining lifetime: leave it zero */
	bp += sizeof(u16);

	/* lsp id */
	copyID(&sig->id, bp, sizeof(LSPID)); bp += sizeof(LSPID);

	/* lsp seq number */
	hostToU32(sig->seqNum, u32);
	bcopy((caddr_t)&u32, (caddr_t)bp, sizeof(u32)); bp += sizeof(u32);

	/* checksum */
	hostToU16(sig->checksum, u16); 
	bcopy((caddr_t)&u16, (caddr_t)bp, sizeof(u16)); bp += sizeof(u16);
	
	IFTRACE(T_PSNP)
		trace_only_tf(isis_trace_options,
			      0,
			      ("sendSpecificPSNP: %s: add %s",
			       c->name, 
			       LSSigToStr(sig)));
	ENDTRACE

	/* tidy up the packet and transmit */
	if (bp > (buf + sizeof(PSNHeader))) {
		len = bp - buf;
		hostToU16(len, hdr->pduLength); 
		transmitPacket(c, level == 1 ? AllL1ISmac : AllL2ISmac, buf, len);
	}
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
