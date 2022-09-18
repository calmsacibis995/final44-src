/*
 *  isis_spf_iter.c,v 1.11 1993/01/07 22:40:01 jch Exp
 */

/* %(Copyright.header) */


#include "include.h"
#include "isis_includes.h" 

extern int spf_level;	/* from isis_spf.c */

void
spf_init_lsp_iter __PF3(state, struct lsp_iter_state *, 
		  	oselect, octet, 
		  	is_addr, IS_ID *)
{
	state->selector = oselect;
	state->lsp_id.is_addr = *is_addr;
	state->lsp_id.packet_num = 0;
	spf_get_first_lsp(state);
}

/* 
 * Get the first LSP associated with a 7 byte is_id.  Save the additional
 * state to scan down the sorted LSPs.
 */
void
spf_get_first_lsp __PF1(state, struct lsp_iter_state *)
{
	struct is_lsp_header *lsp_pt;

	/* following cast to LSPID is needed because it is a struct, passed by value */
	state->cur_lsentry = locateLowestLSP(spf_level,*(LSPID *)&state->lsp_id);

	if (state->cur_lsentry && state->cur_lsentry->len > 0) {
		state->cur_lsp = state->cur_lsentry->buf;
		lsp_pt = (struct is_lsp_header *) state->cur_lsp;
		state->packet_number = lsp_pt->lsp_id[7];
		/* 
		 * Move the pointer past the header.  Use sizeof rather 
		 * than hdr length field (lsp_pt->len) in case header is 
		 * hosing us down.
		 */
		state->cur_lsp_loc = state->cur_lsp + sizeof(*lsp_pt);
		state->cur_lsp_len = GETNSHORT(lsp_pt->pdu_len);
	} else {
		/* no lsp found */
		state->cur_lsp = 0;
		state->cur_lsp_loc = 0;
		state->cur_lsp_len = 0;
	}
}


/* 
 * Get next lsp given current lsp.  
 */
void
spf_get_next_lsp __PF1(state, struct lsp_iter_state *)
{
	struct is_lsp_header * lsp_pt;
	if (state->cur_lsentry) {
		state->cur_lsentry = state->cur_lsentry->sortNext;
		/* skip past 0 length lsp dummies */
		while (state->cur_lsentry && state->cur_lsentry->len == 0)
			state->cur_lsentry = state->cur_lsentry->sortNext;
		if (state->cur_lsentry && equalID(&state->lsp_id,&state->cur_lsentry->signature.id,7)) {
			/* we are still in the same LSP ID */
			state->cur_lsp = state->cur_lsentry->buf;
			lsp_pt = (struct is_lsp_header *) state->cur_lsp;
			state->packet_number = lsp_pt->lsp_id[7];
			/* move the pointer past the header */
			state->cur_lsp_loc = state->cur_lsp + sizeof(*lsp_pt);
			state->cur_lsp_len = GETNSHORT(lsp_pt->pdu_len);
		} else {
			/* no lsp found */
			state->cur_lsentry = 0;
			state->cur_lsp = 0;
			state->cur_lsp_loc = 0;
			state->cur_lsp_len = 0;
		}
		
	}
}

char *
spf_get_next_lsp_rfield __PF1(state, struct lsp_iter_state *)
{
	char *ret_pt = 0;
	while (state->cur_lsp) {
		if ((state->cur_lsp_loc - state->cur_lsp) >= state->cur_lsp_len) {
			/* we are past the end of the lsp; move on to next lsp, maybe */
			state->lsp_id.packet_num++;
			spf_get_next_lsp(state);
			state->lsp_id.packet_num++;
		}
		if (!state->cur_lsp) {
			return ret_pt;
		}
		if ((state->cur_lsp_loc - state->cur_lsp) >= state->cur_lsp_len) {
			/* an lsp with no options?  continue on */
			continue;
		}
		switch(state->cur_lsp_loc[0]) {
			case IS_NEIGHBOR_SELECTOR:
			case IN_EXTERN_SELECTOR:
			case IN_INTERN_SELECTOR:
			case IPInterDomInfo:
			case PREFIX_NEIGHBOR_SELECTOR:
			case ES_NEIGHBOR_SELECTOR:
			case AREA_ADDR_SELECTOR:
				/* found something we need to process */
				state->selector = state->cur_lsp_loc[0];
				ret_pt = (char *) state->cur_lsp_loc;
		}
		/* now move cursor to next field. */
		state->cur_lsp_loc += ((unsigned char *)state->cur_lsp_loc)[1] + 2;
		if (ret_pt) {
			return ret_pt;
		}
	}
	return ret_pt;
}


/* 
 * Iterate through all the lsp's, getting the next relevant node 
 * address.
 */
octet *
get_next_nodeaddr __PF1(state, struct subfield_iter_state *)
{
	octet * ret_pt = 0;
	static doIDRPi = 1;

	while (state->cfu.cur_field) {
		/* loop until we can't get any more fields */
		switch(state->lsp_iter.selector) {
			/* check if there are any subfields left in the current option */
			/* if so, return the current one and advance to the next */
			case IN_INTERN_SELECTOR: /* get next IN field */
			case IN_EXTERN_SELECTOR:
				if (state->iu.inf.num_inn > state->iu.inf.cur_inn) {
					/* return the next offset */
					ret_pt = (octet *)state->cfu.cur_inn_field->inet_neighbors[state->iu.inf.cur_inn].inet_addr;
					state->metrics = state->cfu.cur_inn_field->inet_neighbors[state->iu.inf.cur_inn].metrics;
					state->iu.inf.cur_inn ++;
					return ret_pt;
				}
			break;
			case IPInterDomInfo:
				/* allow caller to look at lsp_iter.selector and suck out attributes if desired */
				if (doIDRPi) {
					doIDRPi = 0;
					return (octet *) state->cfu.cur_field;
				}
			break;
			case IS_NEIGHBOR_SELECTOR: /* get next IS field */
				if (state->iu.isf.num_isn > state->iu.isf.cur_isn) {
					/* return the next offset */
					ret_pt = (octet *) 
						 state->cfu.cur_isn_field->is_neighbors[state->iu.isf.cur_isn].is_neighbor_id;
					state->metrics = state->cfu.cur_isn_field->is_neighbors[state->iu.isf.cur_isn].metrics;
					state->iu.isf.cur_isn ++;
					return ret_pt;
				}
			break;
			case ES_NEIGHBOR_SELECTOR: /* get next ES field */
				if (state->iu.esf.num_esn > state->iu.esf.cur_esn) {
					/* return the next offset */
					ret_pt = (octet *)state->cfu.cur_esn_field->es_neighbors[state->iu.esf.cur_esn];
					state->iu.esf.cur_esn ++;
					return ret_pt;
				}
			break;
			case PREFIX_NEIGHBOR_SELECTOR: /* get next PREFIX field */
				if (state->iu.pff.next_prefix < 
				    ((octet *)state->cfu.cur_prefix_field) 
				    + state->cfu.cur_prefix_field->length + 2) {
					/* return the next offset */
					ret_pt = state->iu.pff.next_prefix;
					state->iu.pff.next_prefix += 1 + ((*ret_pt + 1) >> 1); 
					/* first byte is length of prefix in nibbles */
					return ret_pt;
				}
			break;
			case AREA_ADDR_SELECTOR: /* get next area addr field */
				if (state->iu.arf.next_area < 
				    ((octet *)state->cfu.cur_area_field) 
				    + state->cfu.cur_area_field->length + 2) {
					/* return the next offset */
					ret_pt = state->iu.arf.next_area;
					state->iu.arf.next_area += (*ret_pt + 1); 
					/* first byte is length of area address in bytes */
					return ret_pt;
				}
			break;
			default:
				trace_log_tf(isis_trace_options,
					     0,
					     LOG_ERR,
					     ("get_next_nodeaddr found bogus selector"));
		} /* end of switch on state->selector */

		/* if we got here, the current field is exhausted, so get the next one. */
		doIDRPi = 1;
		state->cfu.cur_field = spf_get_next_lsp_rfield(&(state->lsp_iter));
		/* got next relevant field; now set up state accordingly. */
		if (!state->cfu.cur_field) {
			/* all done */
			return 0;
		}
		set_subfield_state(state);
		/* sets up subfield iteration on the selected option */
	} /* back to top of loop */
	/* should never actually get here */
	return 0;
} 

static octet zero_metrics[] = { 0,0,0,0 };

/* 
 * Sets up subfield iteration on the selected option.
 * Called after a new option field is obtained.
 */
void
set_subfield_state __PF1(state, struct subfield_iter_state *)
{
	switch(state->lsp_iter.selector) {
		/* note that es and prefix neighbors have a common metric field,
			while is and inet neighbors have a distinct metric for each addr.
		*/
		case ES_NEIGHBOR_SELECTOR: /* get next ES field */
			state->iu.esf.cur_esn = 0;
			state->iu.esf.num_esn = (state->cfu.cur_esn_field->length)/ES_NID_SIZE;
			state->addr_type = es_id;
			state->metrics = state->cfu.cur_esn_field->metrics;
		break;
		case PREFIX_NEIGHBOR_SELECTOR: /* get next PREFIX field */
			state->iu.pff.next_prefix = state->cfu.cur_prefix_field->space;
			state->addr_type = addr_pref;
			state->metrics = state->cfu.cur_prefix_field->metrics;
		break;
		case AREA_ADDR_SELECTOR: /* get next area addr field */
			state->iu.arf.next_area = state->cfu.cur_area_field->space;
			state->addr_type = area_addr;
			state->metrics = zero_metrics; /* dummy for no cost */
		break;
		case IS_NEIGHBOR_SELECTOR: /* get next IS field */
			/* initialize the is-is neighbor lsp iterator */
			state->iu.isf.cur_isn = 0;
			state->iu.isf.num_isn = (state->cfu.cur_isn_field->length-1)/sizeof( struct is_neighbor);
			state->addr_type = is_id;
		break;
		case IN_INTERN_SELECTOR: /* get next IN field */
		case IN_EXTERN_SELECTOR:
			state->iu.inf.cur_inn = 0;
			state->iu.inf.num_inn = (state->cfu.cur_inn_field->length)/sizeof( struct inet_neighbor);
			state->addr_type = inet_net;
		break;
		case IPInterDomInfo:
			/* save the current attributes, assuming cur_field+2 == 1 */
			bcopy(state->cfu.cur_field+2, &state->attributes, *(state->cfu.cur_field+1));
		break;
	}
}

/* 
 * Get the given node's first neighbor.
 */
octet *
get_first_nodeaddr __PF2(state, struct subfield_iter_state *,
		   	 is_addr, IS_ID *)
{
	spf_init_lsp_iter(&(state->lsp_iter),0,is_addr);
	bzero(&state->attributes, sizeof(isis_asp));
	state->cfu.cur_field = spf_get_next_lsp_rfield((struct lsp_iter_state *) state);
	if (state->cfu.cur_field) {
		set_subfield_state(state);
		return get_next_nodeaddr(state);
	}
	return 0;
}



/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
