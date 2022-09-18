/*
 *  $Id: isis_parseutil.c,v 1.14 1993/10/27 01:40:44 jch Exp $
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h"

static AreaAddr	knownAAs[AreaAddressStoreSize];

void
initAreaAddrs()
{
	bzero((caddr_t)systemAreaAddrs.areaAddr, sizeof(systemAreaAddrs.areaAddr));
	systemAreaAddrs.count = 0;
	bzero((caddr_t)knownAAs, sizeof(knownAAs));
}

/*
 *	Store the area addresses in a 'store'. This allows other data structures
 *	to simply use area address indexes, rather than actual addresses.
 */
char
storeAreaAddr __PF1(
	    bp, u_char *)
{
	char	i;
	for (i=0; i<AreaAddressStoreSize; i++) {
		if (knownAAs[i].len == 0) {
			knownAAs[i].len = *bp++;
			bcopy((caddr_t) bp, (caddr_t) knownAAs[i].addr, knownAAs[i].len);
			return(i);
		} else {
			if (knownAAs[i].len == (*bp) &&
			    !bcmp((caddr_t) knownAAs[i].addr, (caddr_t) bp+1, knownAAs[i].len))
				return(i);
		}
	}
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("storeAreaAddr: AreaAddressStoreSize exceeded"));
	task_quit(0);
	return(0);
}

AreaAddr *
retrieveAreaAddr __PF1(
	    indx, char)
{
    return &knownAAs[indx];
}

/*
 *	copy the area addrs listed in new into old.
 *	If old is full, then selectively replace entries in old with
 *	those from new. Replace addrs with the numerically highest area addr.
 */
AreaAddrList
mergeAreaAddrList(new, old)
AreaAddrList	new, old;
{
	int		i, j;
	for (i=0; i<new.count; i++) {
		char	aa = new.areaAddr[i];

		/* see if aa is already in old */
		for (j=0; j<old.count; j++) {
			if (aa == old.areaAddr[j]) {
				break;		/* fine! its in there already */
			}
		}
		if (j == old.count) {
			/* not in old, see if there is room */
			if (old.count < MaximumAreaAddresses) {
				/* just add it */
				old.areaAddr[old.count++] = aa;
			} else {
				/* should selectively replace an entry in old, for now just replace 
					first */
				old.areaAddr[0] = aa;
			}
		}
	}
	return(old);
}

/*
 *	Parse a list of area addresses. Setup 'list' so it can access the
 *	fields in the list. Note: 'list' contains pointers that point into
 *	buf. Return OK or NOTOK depending on parse success.
 */
int
parseAreaAddrList(bp, len, list)
u_char			*bp;
u_char			len;
AreaAddrList	*list;
{
	u_char		*end = bp + len;
	u_char		count = 0;

	while (bp < end) {
		/* 
		 *	make sure the address length is not wacko (greater than zero,
		 *	and not so big that it exceeds our buffer). Note that
		 *	*bp contains the addr length 
		 */
		if ((*bp == 0) || ((*bp + bp) > end))
			return(NOTOK);
		
		list->areaAddr[count] = storeAreaAddr(bp);
		bp += *bp;
		bp ++;	/* include length byte */
		count++;
	}

	list->count = count;
	return(OK);
}

/*
 *	Parse the Protocols Supported option. Return a bit mask containing
 *	the value of the option
 */
u_int
parseProtoSup __PF2(
	    bp, u_char *,
	    len, u_char)
{
	u_int	flags = 0;

	while (len--) {
		switch(*bp++) {
			case OSI_NLPID: 
				flags |= SUPPORT_CLNP;
				break;
			case IP_NLPID:
				flags |= SUPPORT_IP;
				break;
		}
	}
	return(flags);
}

/*
 *	Parse the IP Interface Address option. Place the address in 'addr'.
 *	Return OK or NOTOK depending on success of parse
 */
int
parseIPIfAddr(bp, len, addr)
u_char		*bp;
u_char		len;
IPAddrList	*addr;
{
	int i = 0;
	if (len % 4)
		return(NOTOK);
	while (len) {
		bcopy((caddr_t) bp, (caddr_t) &addr->addrs[i], sizeof(struct in_addr));
		len -= sizeof(struct in_addr);
		i++;
	}
	addr->cnt = i;
	return(OK);
}

/* 
 *	Parse the Authentication Information option
 */
int
parseAuthInfo(bp, len, info)
u_char		*bp;
u_char		len;
AuthInfo	*info;
{
	*info = NULL;
	return(OK);
}

/*
 *	assumes buf is not malformed. Parse the LSP, locate the area address
 *	list, parse it and return an AreaAddrList struct.
 */
AreaAddrList
parseLSPAreaAddrList(buf, length)
u_char	*buf;	/* buffer containing packet */
int		length;	/* length of buffer */
{
	u_char	*bp, *end;
	AreaAddrList	aal;

	bzero((caddr_t) &aal, sizeof(aal));
	bp = buf + sizeof(LSPHeader);
	end = buf + length;

	while (bp+1 < end) {
		u_char	code = *bp++;
		u_char	len = *bp++;

		if (bp + len > end) {
			trace_log_tf(isis_trace_options,
				     0,
				     LOG_ERR,
				     ("parseLSPAreaAddrList: option %d too short",
				      code));
			return(aal);
		}

		switch(code) {
			case AreaAddressCode:
				if (!parseAreaAddrList(bp, len, &aal)) {
					trace_log_tf(isis_trace_options,
						     0,
						     LOG_ERR,
						     ("parseLSPAreaAddrList: can't parse area list"));
				}
				return(aal);

			default:
				break;
		}
		bp += len;
	}
	return(aal);
}



/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
