/*
 *  $Id: krt_ipmulti.c,v 1.1 1995/01/26 07:47:09 pusateri Exp $
 */

/*%Copyright%*/

#include "include.h"
#include "inet.h"
#include "inet_multi.h"
#include "krt.h"
#include "krt_var.h"
#include "krt_ipmulti.h"

extern task *krt_task;

static block_t krt_mfc_recv_block_index;
	/*
	 * intialize double linked list of callback routines
	 */
struct krt_mfc_recv krt_mfc_recv_head =
	{ &krt_mfc_recv_head, &krt_mfc_recv_head };

/*
 * krt_init_mfc()
 */

void
krt_init_mfc __PF0(void)
{
    krt_mfc_recv_block_index = task_block_init(sizeof (struct krt_mfc_recv),
					       "krt_mfc_recv");
}


void
krt_register_mfc(error, callback)
int error;
_PROTOTYPE(callback,
	   void,
	   (int,
	    if_addr *,
	    mfc *));
{
    struct krt_mfc_recv *recv_list;

    MFC_RECV_SCAN(recv_list, &krt_mfc_recv_head) {
	if (recv_list->errno == error && recv_list->recv_routine == callback) {
		return;		/* ignore duplicates */
	}
    } MFC_RECV_SCAN_END(recv_list, &krt_mfc_recv_head);

    recv_list = (struct krt_mfc_recv *) task_block_alloc(krt_mfc_recv_block_index);
    recv_list->errno = error;
    recv_list->recv_routine = callback;

		/* just insert at head of list */
    INSQUE(recv_list, &krt_mfc_recv_head);
}


void
krt_unregister_mfc(error, callback)
int error;
_PROTOTYPE(callback,
	   void,
	   (int,
	    if_addr *,
	    mfc *));
{
    struct krt_mfc_recv *recv_list;

    MFC_RECV_SCAN(recv_list, &krt_mfc_recv_head) {
	if (recv_list->errno == error && recv_list->recv_routine == callback) {
		REMQUE(recv_list);
		task_block_free(krt_mfc_recv_block_index, (void_t) recv_list);
		return;
	}
    } MFC_RECV_SCAN_END(recv_list, &krt_mfc_recv_head);
}

void
krt_check_mfc  __PF3(use, int,
		     dst, sockaddr_un *,
		     src, sockaddr_un *)
{
    mfc *mfcp = mfc_locate_mfc(dst, src);
    if (mfcp) {
	    mfcp->mfc_lastuse = mfcp->mfc_use;
	    mfcp->mfc_use = use;
	    (*mfcp->mfc_callback)(mfcp);
    } else {
	trace_log_tp(krt_task,
		     0,
		     LOG_ERR,
		     ("krt_check_mfc: can't locate group %A source %A",
		      dst,
		      src));
    }
}

void
krt_update_mfc  __PF1(mfcp, mfc *)
{

    krt_resolve_cache(sockbuild_in(0, mfcp->mfc_group->group_key),
		      sockbuild_in(0, mfcp->mfc_src),
		      mfcp);
}


/*
 * Find the upstream interface for this source
 * Look up source on behalf of protocol specified in request_proto.
 */

upstream *
krt_locate_upstream  __PF2(src_addr, sockaddr_un *,
			   request_proto, int)
{
    static upstream up;

    up.ifap = (if_addr *) 0;
    up.nbr = (sockaddr_un *) 0;
    up.protocol = 0;
    up.metric = (metric_t) 0;

    switch(request_proto) {

	case IPMULTI_PROTO_PIM:
	{
	    rt_list *rtl;
	    rt_head *rth = (rt_head *) 0;
	    krt_parms *krtp = (krt_parms *) 0;

	    rtl = rthlist_match(src_addr);

	    RT_LIST(rth, rtl, rt_head) {

		/*
		 * Use the one thats installed in the kernel
		 */

		if ((krtp = krt_kernel_rt(rth))) {
		    break;
		}
	    } RT_LIST_END(rth, rtl, rt_head) ;

	    RTLIST_RESET(rtl);

	    if (krtp) {
		up.ifap = krtp->krtp_ifap;
		up.nbr = krtp->krtp_router;
		up.protocol = krtp->krtp_protocol;
		up.metric = krtp->krtp_metric;
	    }
	}
	break;

	case IPMULTI_PROTO_DVMRP:
	{
	    rt_entry *rt;
	    
	    rt = rt_lookup(RTS_NOTINSTALL|RTS_NOADVISE,
			   (flag_t) 0,
			   src_addr,
			   RTPROTO_BIT(RTPROTO_DVMRP));

	    if (rt) {
		up.ifap = RT_IFAP(rt);
		up.nbr = RT_ROUTER(rt);
		up.protocol = RTPROTO_DVMRP;
		up.metric = rt->rt_metric;
	    }
	}
	break;

	default:
	    return (upstream *) 0;
    }

    return(&up);
}
