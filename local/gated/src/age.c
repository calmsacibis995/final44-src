

static void
rip_gw_delete __PF1(jp, task_job *)
{
}


static void
rip_age __PF2(tip, task_timer *,
	      interval, time_t)
{
    gw_entry *gwp;
    time_t next_time = (time_t) -1;

    GW_LIST(rip_gw_list, gwp) {
	rt_entry *rt;

	if (!gwp->gw_n_routes) {
	    /* No routes for this gateway */

	    if (!gwp->gw_import
		&& !gwp->gw_export
		&& !BIT_TEST(gwp->gw_flags, GWF_SOURCE|GWF_TRUSTED)) {
		/* No routes, delete this gateway */

		/* XXX */
	    }
	    continue;
	}

	/* Age any routes for this gateway */
	RTQ_LIST(&gwp->gw_rtq, rt) {
	    if (rt_age(rt) < RIP_T_EXPIRE) {
		/* This entry has yet to expire */

		next_time = MIN(next_time, RIP_T_EXPIRE - rt_age(rt));
		break;
	    } else if (!BIT_TEST(rt->rt_state, RTS_DELETE)) {
		/* This entry has expired */
		
		rt_delete(rt);
	    }	    
	} RTQ_LIST_END(&gwp->gw_rtq, rt) ;
    } GW_LIST_END(rip_gw_list, gwp) ;

    task_timer_set(tip, (time_t) 0, next_time);
}
