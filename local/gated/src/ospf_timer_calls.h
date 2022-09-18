/*
 * $Id: ospf_timer_calls.h,v 1.9 1992/12/14 22:25:38 jch Exp $
 */

/* %(Copyright.header) */


#define OSPF_TQ_HANDLE()	/* Null routine for now */

/*
 * Reset the inactivity timer - have seen hello from this neighbor
 */
#define reset_inact_tmr(N) (N)->last_hello = time_sec


/*
 * Set the holding timer (entering slave hold mode)
 */
#define set_hold_tmr(N) (N)->last_exch = time_sec


/*
 * Remove the holding timer (exiting slave hold mode)
 */
#define rem_hold_tmr(N) (N)->last_exch = 0


/*
 * Remove the inactivity - neighbor state has changed to down
 */
#define rem_inact_tmr(N) (N)->last_hello = 0


/*
 * Remove the wait timer - backup seen or interface down
 */
#define rem_wait_tmr(I) (I)->wait_time = 0


/*
 * Start the wait timer - interface up
 */
#define start_wait_tmr(I) (I)->wait_time = time_sec

/*
 * Lock out nets for MinLSInterval
 * - can't generate new LSA with MinLSInterval
 */
#define net_lsa_lockout(I)  ((I)->lock_time = time_sec)

#define set_net_sched(I)    {if ((I)->lock_time == 0) net_lsa_lockout(I);\
				BIT_SET((I)->flags, OSPF_INTFF_NETSCHED);}

#define rtr_lsa_lockout(A)  ((A)->lock_time = time_sec)

#define set_rtr_sched(A)    {if ((A)->lock_time == 0) rtr_lsa_lockout(A);\
				((A)->lsalock |= RTRSCHED);}

#define reset_net_lock(I)   ((I)->lock_time = 0)
#define reset_net_sched(I)  BIT_RESET((I)->flags, OSPF_INTFF_NETSCHED|OSPF_INTFF_BUILDNET);

#define reset_rtr_lock(A)   ((A)->lock_time = 0)
#define reset_rtr_sched(A)  ((A)->lsalock &= ~RTRSCHED)

#define NET_LSA_LOCK(I)     ((I)->lock_time != 0)
#define RTR_LSA_LOCK(A)     ((A)->lock_time != 0)


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
