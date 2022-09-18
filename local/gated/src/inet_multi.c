/*
 *  $Id: inet_multi.c,v 1.2 1995/01/26 07:53:12 pusateri Exp $
 */

/*%Copyright%*/


#include "include.h"

#ifdef	IP_MULTICAST

#ifdef	PROTO_INET
#include "inet.h"
#endif	/* PROTO_INET */
#ifdef	PROTO_ISO
#include "iso.h"
#endif	/* PROTO_ISO */

#include "inet_multi.h"

PROTOTYPE(mfc_delete_group, static void, (group_node *));
PROTOTYPE(mfc_insert_group, static group_node *, (group_node *, u_long));
PROTOTYPE(mfc_insert_node, static void, (group_node *, mfc *, mfc *));
PROTOTYPE(mfc_print_node, static void, (mfc *, caddr_t));

static block_t mfc_node_block_index;
static block_t mfc_downstream_block_index;
static block_t group_node_block_index;
block_t mfc_unicast_block_index;

#define MFC_NODE_FREE(dp) \
		task_block_free(mfc_node_block_index, (void_t)(dp))
#define GROUP_NODE_ALLOC() \
		(task_block_alloc(group_node_block_index))
#define GROUP_NODE_FREE(dp) \
		task_block_free(group_node_block_index, (void_t)(dp))


/*
 * mfc_init()
 */

void
mfc_init  __PF0(void)
{
    mfc_node_block_index = task_block_init(sizeof (struct _mfc),
					       "mfc_node");
    mfc_downstream_block_index = task_block_init(sizeof (downstream),
					       "mfc_downstream");
    group_node_block_index = task_block_init(sizeof (struct _group_node),
					       "group_node");
    mfc_unicast_block_index = task_block_init(sizeof (struct _mfc),
					       "mfc_unicast");
}

mfc *
mfc_alloc_node  __PF0(void)
{
    return((mfc *) task_block_alloc(mfc_node_block_index));
}

downstream *
mfc_alloc_downstream  __PF0(void)
{
    return((downstream *) task_block_alloc(mfc_downstream_block_index));
}

void
mfc_free_downstream  __PF1(ds, downstream *)
{
    task_block_free(mfc_downstream_block_index, ds);
}

/*
 * mfc_source_link_unicast()
 *
 * This routine links the mfc to the unicast route it depends on.
 * If the route changes later, then it will be easy to determine
 * if the cache entry needs to be updated or moved to a different
 * unicast route.
 */

void
mfc_source_link_unicast __PF2(tp, task *, mfcp, mfc *)
{
    mfc_src_list *head = 0, *msl;
    register rt_head *rth;
    register rt_list *rtl = rthlist_match(sockbuild_in(0, mfcp->mfc_src));

    rt_open(tp);

    RT_LIST(rth, rtl, rt_head) {

	    /*
	     * Check the one thats installed in the kernel
	     */

	if (krt_kernel_rt(rth)) {
	    if (rtbit_isset(rth->rth_active, tp->task_rtbit)) {
		rttsi_get(rth, tp->task_rtbit, (byte *) &head);
		if (head && mfcp->msl) {
			/*
			 * Already in table.
			 */
		    goto reset;
		}
	    }
	    if (!head) {
		msl = task_block_alloc(mfc_unicast_block_index);
		msl->forw = msl;
		msl->back = msl;
		head = msl;

		rttsi_set(rth, tp->task_rtbit, (byte *) &head);
		rtbit_set(rth->rth_active, tp->task_rtbit);
	    }
		/*
		 * add to head of list
		 */
	    msl = task_block_alloc(mfc_unicast_block_index);
	    msl->mfcp = mfcp;
	    mfcp->msl = msl;
	    INSQUE(msl, head->forw);

	    break;
	}
    } RT_LIST_END(rth, rtl, rt_head) ;

reset:
    RTLIST_RESET(rtl);

    /* Close the table */
    rt_close(tp, (gw_entry *) 0, 0, NULL);
}

void
mfc_source_unlink_unicast __PF2(tp, task *, mfcp, mfc *)
{
    mfc_src_list *head = 0;
    register rt_head *rth;
    register rt_list *rtl = rthlist_match(sockbuild_in(0, mfcp->mfc_src));

    rt_open(tp);

    RT_LIST(rth, rtl, rt_head) {

	    /*
	     * Check the one thats installed in the kernel
	     */

	if (krt_kernel_rt(rth) &&
	    rtbit_isset(rth->rth_active, tp->task_rtbit)) {

	    rttsi_get(rth, tp->task_rtbit, (byte *) &head);
	    assert(head);
	    assert(mfcp->msl);
	    REMQUE(mfcp->msl);
	    task_block_free(mfc_unicast_block_index, (void_t) mfcp->msl);
	    mfcp->msl = (mfc_src_list *) 0;
	    if (head->forw == head) {
		    /*
		     * delete head of list
		     */
		task_block_free(mfc_unicast_block_index, head);
		rtbit_reset(rth->rth_active, tp->task_rtbit);
		rttsi_reset(rth, tp->task_rtbit);
	    }
	    goto reset;
	}
    } RT_LIST_END(rth, rtl, rt_head) ;

reset:
    RTLIST_RESET(rtl);

    /* Close the table */
    rt_close(tp, (gw_entry *) 0, 0, NULL);
}

#define NODE_NOMASK     0xffffffff

static int group_node_count = 0;

static group_node *group_node_head = NULL;

/*
 * Lookup table to do an ffs() from the high order end (the ffs() routine
 * runs from the other end), on a byte.  This is useful to find the first
 * differing bit for the patricia tree.
 */
const byte node_bit_table[256] = {
    0x00, 0x01, 0x02, 0x02, 0x04, 0x04, 0x04, 0x04,
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
    0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80
};

static void
mfc_terminate_source  __PF1(head, group_node *)
{
    int i,n,doing_right;
    mfc *stack[sizeof(u_int32) * NBBY];
    register mfc *dp, *dprev = head->src_head;

    if (head->src_node_count == 0) {
        return;
    }

	/* catch the case where only one node in the tree. */
    if (dprev->mfc_mask == NODE_NOMASK) {
	krt_delete_cache(sockbuild_in(0, head->group_key),
			 sockbuild_in(0, dprev->mfc_src));
        return;
    }

    doing_right = 0;
    i = n = 0;
    for (;;) {
        if (doing_right) {
            dp = dprev->right;
        } else {
            dp = dprev->left;
        }

        if (dp->mfc_mask >= dprev->mfc_mask) {

	    krt_delete_cache(sockbuild_in(0, head->group_key),
			     sockbuild_in(0, dp->mfc_src));

	    if (++n >= head->src_node_count) {
		/* All found */
		break;
	    }

            if (doing_right) {
                /*
                 * Finished right hand, back up stack for another
                 * node to be checked on the right.
                 */
                assert(i != 0);
                dprev = stack[--i];
            } else {
                /*
                 * Finished left, try right on next pass
                 */
                doing_right = 1;
            }
        } else {
            if (doing_right) {
                /*
                 * Node on right has children.  Step down the tree,
                 * starting on the left.  No need to stack the previous,
                 * we've already checked both children
                 */
                doing_right = 0;
            } else {
                /*
                 * Node on left has children, stack the previous node
                 * so we check its right child later.
                 */
                stack[i++] = dprev;
            }
            dprev = dp;
        }
    }
}

void
mfc_terminate  __PF0(void)
{
    int i,n,doing_right;
    group_node *stack[sizeof(u_int32) * NBBY];
    register group_node *dp, *dprev = group_node_head;

    if (group_node_count == 0) {
        return;
    }

	/* catch the case where only one node in the tree. */
    if (dprev->group_mask == NODE_NOMASK) {
	mfc_terminate_source(dprev);
        return;
    }

    doing_right = 0;
    i = n = 0;
    for (;;) {
        if (doing_right) {
            dp = dprev->right;
        } else {
            dp = dprev->left;
        }

        if (dp->group_mask >= dprev->group_mask) {

	    mfc_terminate_source(dp);

	    if (++n >= group_node_count) {
		/* All found */
		break;
	    }

            if (doing_right) {
                /*
                 * Finished right hand, back up stack for another
                 * node to be checked on the right.
                 */
                assert(i != 0);
                dprev = stack[--i];
            } else {
                /*
                 * Finished left, try right on next pass
                 */
                doing_right = 1;
            }
        } else {
            if (doing_right) {
                /*
                 * Node on right has children.  Step down the tree,
                 * starting on the left.  No need to stack the previous,
                 * we've already checked both children
                 */
                doing_right = 0;
            } else {
                /*
                 * Node on left has children, stack the previous node
                 * so we check its right child later.
                 */
                stack[i++] = dprev;
            }
            dprev = dp;
        }
    }
}


void
mfc_visit(callback, arg1)
_PROTOTYPE(callback,
	   void,
	   (mfc *,
	    caddr_t));
caddr_t arg1;
{
    int i,n,doing_right;
    group_node *stack[sizeof(u_int32) * NBBY];
    register group_node *dp, *dprev = group_node_head;

    if (group_node_count == 0) {
        return;
    }

	/* catch the case where only one node in the tree. */
    if (dprev->group_mask == NODE_NOMASK) {
	mfc_source_visit(dprev, callback, arg1);
        return;
    }

    doing_right = 0;
    i = n = 0;
    for (;;) {
        if (doing_right) {
            dp = dprev->right;
        } else {
            dp = dprev->left;
        }

        if (dp->group_mask >= dprev->group_mask) {

	    mfc_source_visit(dprev, callback, arg1);

	    if (++n >= group_node_count) {
		/* All found */
		break;
	    }

            if (doing_right) {
                /*
                 * Finished right hand, back up stack for another
                 * node to be checked on the right.
                 */
                assert(i != 0);
                dprev = stack[--i];
            } else {
                /*
                 * Finished left, try right on next pass
                 */
                doing_right = 1;
            }
        } else {
            if (doing_right) {
                /*
                 * Node on right has children.  Step down the tree,
                 * starting on the left.  No need to stack the previous,
                 * we've already checked both children
                 */
                doing_right = 0;
            } else {
                /*
                 * Node on left has children, stack the previous node
                 * so we check its right child later.
                 */
                stack[i++] = dprev;
            }
            dprev = dp;
        }
    }
}


void
mfc_dump  __PF2(tp, task *,
		fd, FILE *)
{
    int i,n,doing_right;
    group_node *stack[sizeof(u_int32) * NBBY];
    register group_node *dp, *dprev = group_node_head;

    fprintf(fd, "\tMulticast Forwarding Cache:\n");
    if (group_node_count == 0) {
        return;
    }

	/* catch the case where only one node in the tree. */
    if (dprev->group_mask == NODE_NOMASK) {
	fprintf(fd, "\tGroup %A:\n", sockbuild_in(0, dprev->group_key));
	mfc_source_visit(dprev, mfc_print_node, (caddr_t) fd);
        return;
    }

    doing_right = 0;
    i = n = 0;
    for (;;) {
        if (doing_right) {
            dp = dprev->right;
        } else {
            dp = dprev->left;
        }

        if (dp->group_mask >= dprev->group_mask) {

	    fprintf(fd, "\tGroup %A:\n", sockbuild_in(0, dp->group_key));

	    mfc_source_visit(dprev, mfc_print_node, (caddr_t) fd);

	    if (++n >= group_node_count) {
		/* All found */
		break;
	    }

            if (doing_right) {
                /*
                 * Finished right hand, back up stack for another
                 * node to be checked on the right.
                 */
                assert(i != 0);
                dprev = stack[--i];
            } else {
                /*
                 * Finished left, try right on next pass
                 */
                doing_right = 1;
            }
        } else {
            if (doing_right) {
                /*
                 * Node on right has children.  Step down the tree,
                 * starting on the left.  No need to stack the previous,
                 * we've already checked both children
                 */
                doing_right = 0;
            } else {
                /*
                 * Node on left has children, stack the previous node
                 * so we check its right child later.
                 */
                stack[i++] = dprev;
            }
            dprev = dp;
        }
    }
}

static void
mfc_print_node  __PF2(mfcp, mfc *,
		      fd, caddr_t)
{
	int lifetime;
	downstream *dsp;

	fprintf((FILE *)fd, "\t  Source %A", sockbuild_in(0, mfcp->mfc_src));
	if (mfcp->upstream_ifap) {
	    fprintf((FILE *)fd, " UpIF %A(%s)\n",
			mfcp->upstream_ifap->ifa_addr,
			mfcp->upstream_ifap->ifa_link->ifl_name);
	}
	DOWNSTREAM_LIST(dsp, mfcp->ds) {
	    fprintf((FILE *)fd, "\t  DownIF %A  Min TTL %d\n",
		    dsp->ds_addr, dsp->ds_ttl);
	} DOWNSTREAM_LIST_END(dsp, mfcp->ds);
	lifetime = time_sec - mfcp->mfc_ctime;
	fprintf((FILE *)fd,
		"\t  Lifetime: %02u:%02u:%02u Use: %d LastUse: %d\n\n",
		lifetime/3600,
		(lifetime%3600)/60,
		lifetime%60,
		mfcp->mfc_use,
		mfcp->mfc_lastuse);
}

void
mfc_source_visit(head, callback, arg1)
group_node *head;
_PROTOTYPE(callback,
	   void,
	   (mfc *,
	    caddr_t));
caddr_t arg1;
{
    int i,n,doing_right;
    mfc *stack[sizeof(u_int32) * NBBY];
    register mfc *dp, *dprev = head->src_head;

    if (head->src_node_count == 0) {
        return;
    }

	/* catch the case where only one node in the tree. */
    if (dprev->mfc_mask == NODE_NOMASK) {
	(*callback)(dprev, arg1);
        return;
    }

    doing_right = 0;
    i = n = 0;
    for (;;) {
        if (doing_right) {
            dp = dprev->right;
        } else {
            dp = dprev->left;
        }

        if (dp->mfc_mask >= dprev->mfc_mask) {

	    (*callback)(dp, arg1);

	    if (++n >= head->src_node_count) {
		/* All found */
		break;
	    }

            if (doing_right) {
                /*
                 * Finished right hand, back up stack for another
                 * node to be checked on the right.
                 */
                assert(i != 0);
                dprev = stack[--i];
            } else {
                /*
                 * Finished left, try right on next pass
                 */
                doing_right = 1;
            }
        } else {
            if (doing_right) {
                /*
                 * Node on right has children.  Step down the tree,
                 * starting on the left.  No need to stack the previous,
                 * we've already checked both children
                 */
                doing_right = 0;
            } else {
                /*
                 * Node on left has children, stack the previous node
                 * so we check its right child later.
                 */
                stack[i++] = dprev;
            }
            dprev = dp;
        }
    }
}

group_node *
mfc_locate_group  __PF1(group, u_long)
{
    register group_node *dp = group_node_head;

    /*
     * Try to find the group in the tree
     */
    if (dp) {
	register u_long mask;
	do {
	    mask = dp->group_mask;
	    if (group & mask) {
		dp = dp->right;
	    } else {
		dp = dp->left;
	    }
	} while (mask > dp->group_mask);
    }

    /*
     * If the group exists, return it
     */
    if (dp && dp->group_key == group) {
	return(dp);
    }
    return((group_node *) 0);
}

mfc *
mfc_locate_mfc  __PF2(dst, sockaddr_un *,
		      src, sockaddr_un *)
{
    register group_node *dp = mfc_locate_group(dst->in.gin_addr.s_addr);

    if (dp) {
	register mfc *mp = dp->src_head;

	/*
	 * Try to find the mfc in the tree
	 */
	if (mp) {
	    register u_long mask;
	    do {
		mask = mp->mfc_mask;
		if (src->in.gin_addr.s_addr & mask) {
		    mp = mp->right;
		} else {
		    mp = mp->left;
		}
	    } while (mask > mp->mfc_mask);
	}
	if (mp && mp->mfc_src == src->in.gin_addr.s_addr) {
	    return(mp);
	}
    }
    return((mfc *) 0);
}

int
mfc_add_node  __PF2(dst, sockaddr_un *,
	       mfcp, mfc *)
{
    register group_node *dp = group_node_head;

    /*
     * Try to find the group in the tree
     */
    if (dp) {
	register u_long mask;
	do {
	    mask = dp->group_mask;
	    if (dst->in.gin_addr.s_addr & mask) {
		dp = dp->right;
	    } else {
		dp = dp->left;
	    }
	} while (mask > dp->group_mask);
    }

    /*
     * If the group exists, we can look up source
     * If not, insert new group in group tree
     */
    if (dp && dp->group_key == dst->in.gin_addr.s_addr) {
	register mfc *mp = dp->src_head;

	/*
	 * Try to find the mfc in the tree
	 */
	if (mp) {
	    register u_long mask;
	    do {
		mask = mp->mfc_mask;
		if (mfcp->mfc_src & mask) {
		    mp = mp->right;
		} else {
		    mp = mp->left;
		}
	    } while (mask > mp->mfc_mask);
	}
	if (mp && mp->mfc_src == mfcp->mfc_src) {
		/*
		 * already there, log error
		 */
	    trace_only_tp(inet_task,
			  0,
			  ("mfc_add_node: Duplicate MFC request for group %A source %A",
			  dst,
			  sockbuild_in(0, mfcp->mfc_src)));
	    return(1);
	} else {
	    mfc_insert_node(dp, mp, mfcp);
	}
    } else {
	register mfc *mp;

	dp = mfc_insert_group(dp, dst->in.gin_addr.s_addr);

	mp = dp->src_head;

	mfc_insert_node(dp, mp, mfcp);
    }
    return(0);
}

void
mfc_delete_node  __PF1(dp, mfc *)
{
    register mfc *tmp;
    register mfc *dprev, *dcurr;
    register u_int32 key;
    mfc *intprev;

    /*
     * Free up the downstream list head
     */

    mfc_free_downstream(dp->ds);

    /*
     * Detect the trivial case, that there is only one guy in the tree,
     * and fix this up.
     */
    dcurr = dp->mfc_group->src_head;
    if (dcurr->mfc_mask == NODE_NOMASK) {
	assert(dcurr == dp);
	dp->mfc_group->src_head = (mfc *) 0;
	dp->mfc_group->src_node_count = 0;

	mfc_delete_group(dp->mfc_group);

	MFC_NODE_FREE(dp);
	return;
    }

    /*
     * We will be in the tree twice, once as an internal node and once
     * as an external (or up-)node.  Find the guy who points to our man
     * in the tree in both cases, and the guy who points to him in the
     * latter.
     */
    dprev = (mfc *) 0;
    intprev = (mfc *) 0;
    key = dp->mfc_src;
    for (;;) {
	if (key & dcurr->mfc_mask) {
	    tmp = dcurr->right;
	} else {
	    tmp = dcurr->left;
	}
	if (tmp == dp) {
	    if (dp->mfc_mask >= dcurr->mfc_mask) {
		break;		/* got it */
	    }
	    intprev = dcurr;	/* current is in front of internal */
	} else {
	    assert(tmp->mfc_mask < dcurr->mfc_mask);
	}
	dprev = dcurr;
	dcurr = tmp;
    }

    /*
     * Now we have dcurr pointing at the node which contains the up-link
     * to our deleted node, nprev pointing at the node which points to
     * ncurr and intprev pointing at the guy who precedes our node in its
     * internal incarnation.
     *
     * There are several cases here.  We know the information in dcurr
     * is no longer needed, and that the sibling pointer in dcurr will
     * be moved to dprev (replacing dcurr).  If our node is the special
     * one with no internal information, we make dcurr the special.
     * If dcurr is our node (i.e. intprev == dprev) then we simply
     * point nprev at our sibling and we're done.  Otherwise we
     * additionally copy our information to dcurr, and point intprev
     * at dcurr.
     *
     * There is probably a better way to do this, but I'm an engineer,
     * not a (mere) programmer.
     */
    if (dcurr->right == dp) {
	tmp = dcurr->left;
    } else {
	tmp = dcurr->right;
    }
    if (!dprev) {
	dp->mfc_group->src_head = tmp;
    } else if (dprev->right == dcurr) {
	dprev->right = tmp;
    } else {
	dprev->left = tmp;
    }
    if (dcurr != dp) {
	if (dp->mfc_mask == NODE_NOMASK) {
	    dcurr->mfc_mask = NODE_NOMASK;
	    dcurr->left = dcurr->right = dcurr;
	} else {
	    dcurr->mfc_mask = dp->mfc_mask;
	    dcurr->left = dp->left;
	    dcurr->right = dp->right;
	    if (!intprev) {
		dp->mfc_group->src_head = dcurr;
	    } else if (intprev->right == dp) {
		intprev->right = dcurr;
	    } else {
		intprev->left = dcurr;
	    }
	}
    }

    dp->mfc_group->src_node_count--;
    MFC_NODE_FREE(dp);
}

static void
mfc_delete_group  __PF1(dp, group_node *)
{
    register group_node *tmp;
    register group_node *dprev, *dcurr;
    register u_int32 key;
    group_node *intprev;

    /*
     * Detect the trivial case, that there is only one guy in the tree,
     * and fix this up.
     */
    dcurr = group_node_head;
    if (dcurr->group_mask == NODE_NOMASK) {
	assert(dcurr == dp);
	group_node_count--;
	GROUP_NODE_FREE(dp);
	group_node_head = (group_node *) 0;
	return;
    }

    /*
     * We will be in the tree twice, once as an internal node and once
     * as an external (or up-)node.  Find the guy who points to our man
     * in the tree in both cases, and the guy who points to him in the
     * latter.
     */
    dprev = (group_node *) 0;
    intprev = (group_node *) 0;
    key = dp->group_key;
    for (;;) {
	if (key & dcurr->group_mask) {
	    tmp = dcurr->right;
	} else {
	    tmp = dcurr->left;
	}
	if (tmp == dp) {
	    if (dp->group_mask >= dcurr->group_mask) {
		break;		/* got it */
	    }
	    intprev = dcurr;	/* current is in front of internal */
	} else {
	    assert(tmp->group_mask < dcurr->group_mask);
	}
	dprev = dcurr;
	dcurr = tmp;
    }

    /*
     * Now we have dcurr pointing at the node which contains the up-link
     * to our deleted node, nprev pointing at the node which points to
     * ncurr and intprev pointing at the guy who precedes our node in its
     * internal incarnation.
     *
     * There are several cases here.  We know the information in dcurr
     * is no longer needed, and that the sibling pointer in dcurr will
     * be moved to dprev (replacing dcurr).  If our node is the special
     * one with no internal information, we make dcurr the special.
     * If dcurr is our node (i.e. intprev == dprev) then we simply
     * point nprev at our sibling and we're done.  Otherwise we
     * additionally copy our information to dcurr, and point intprev
     * at dcurr.
     *
     * There is probably a better way to do this, but I'm an engineer,
     * not a (mere) programmer.
     */
    if (dcurr->right == dp) {
	tmp = dcurr->left;
    } else {
	tmp = dcurr->right;
    }
    if (!dprev) {
	group_node_head = tmp;
    } else if (dprev->right == dcurr) {
	dprev->right = tmp;
    } else {
	dprev->left = tmp;
    }
    if (dcurr != dp) {
	if (dp->group_mask == NODE_NOMASK) {
	    dcurr->group_mask = NODE_NOMASK;
	    dcurr->left = dcurr->right = dcurr;
	} else {
	    dcurr->group_mask = dp->group_mask;
	    dcurr->left = dp->left;
	    dcurr->right = dp->right;
	    if (!intprev) {
		group_node_head = dcurr;
	    } else if (intprev->right == dp) {
		intprev->right = dcurr;
	    } else {
		intprev->left = dcurr;
	    }
	}
    }

    group_node_count--;
    GROUP_NODE_FREE(dp);
}

/*
 * mfc_insert_node - add a mfc node to the demux tree.  Note that
 *		   found_dp points to the mfc node that was "found" when the
 *		   tree was searched for the address we are adding.
 *		   If it is NULL we do the search on our own.
 */

static void
mfc_insert_node  __PF3(found_dp, group_node *,
		       found_mp, mfc *,
		       mp, mfc *)
{

    register mfc *mprev, *mcurr;
    register u_long mask, omask;

    /*
     * Increment count in group head
     */
    found_dp->src_node_count++;

    /*
     * If he didn't include a "found" demux node, but there are nodes
     * to "find", "find" it.  If there are no nodes to find then
     * this is the first node in the tree and just needs to get
     * initialized appropriately.
     */
    if (!found_mp) {
	if (!(mcurr = found_dp->src_head)) {
	    found_dp->src_head = mp->right = mp->left = mp;
	    mp->mfc_mask = NODE_NOMASK;
	    mp->mfc_group = found_dp;
	    return;
        }
	mask = NODE_NOMASK;
	while (mask > mcurr->mfc_mask) {
	    mask = mcurr->mfc_mask;
	    if (mp->mfc_src & mask) {
		mcurr = mcurr->right;
	    } else {
		mcurr = mcurr->left;
	    }
	}
	found_mp = mcurr;
    }

    /*
     * Here we have an insertion to do.  Figure out the first
     * (most significant) bit which differs from the "found" node.  This
     * tells us the bit we need to test in the node we insert.
     *
     * Do a binary search to find the byte the first bit is in, then use
     * the table to form the mask.
     */
    mask = mp->mfc_src ^ found_mp->mfc_src;
    if (mask >= 0x10000) {
	if (mask >= 0x1000000) {
	    mask = ((u_int32)(node_bit_table[mask >> 24])) << 24;
	} else {
	    mask = ((u_int32)(node_bit_table[mask >> 16])) << 16;
	}
    } else {
	if (mask >= 0x100) {
	    mask = ((u_int32)(node_bit_table[mask >> 8])) << 8;
	} else {
	    mask = (u_int32)(node_bit_table[mask]);
	}
    }

    /*
     * XXX Sanity.  This could only happen if a node with the same key
     * is in the tree already, which should never happen.
     */
    assert(mask != 0);
    mp->mfc_mask = mask;

    /*
     * Now we locate where this guy needs to be inserted.  Search down
     * the tree until we find either an end node (i.e. an upward link)
     * or a node with a mask smaller than ours.  We insert our node
     * above this (watch for the case where the node we find is the
     * current root node), making one of the pointers an uplink pointing
     * at the node itself.
     */
    mprev = (mfc *) 0;
    mcurr = found_dp->src_head;
    omask = NODE_NOMASK;
    while (omask > mcurr->mfc_mask) {
	omask = mcurr->mfc_mask;
	if (mask >= omask) {
	    break;
	}
	mprev = mcurr;
	if (mp->mfc_src & omask) {
	    mcurr = mcurr->right;
	} else {
	    mcurr = mcurr->left;
	}
    }
    assert(mask != mcurr->mfc_mask);

    /*
     * Point the new node at the current node, and at itself.  The
     * pointer to the current node in the previous node is changed to
     * point at the new node.  Simple(?).
     */
    if (mp->mfc_src & mask) {
	mp->right = mp;
	mp->left = mcurr;
    } else {
	mp->right = mcurr;
	mp->left = mp;
    }

    if (!mprev) {
	/* New root node */
	found_dp->src_head = mp;
    } else if (mprev->right == mcurr) {
	mprev->right = mp;
    } else {
	mprev->left = mp;
    }
    mp->mfc_group = found_dp;
}

static group_node *
mfc_insert_group  __PF2(found_dp, group_node *,
			 key, u_long)
{
    register group_node *dp;
    register group_node *dprev, *dcurr;
    register u_long mask, omask;

    /*
     * Fetch a new demux structure and initialize it
     */
    dp = GROUP_NODE_ALLOC();
    dp->group_key = key;
    dp->src_node_count = 0;
    dp->graft_pending = 0;
    dp->src_head = (mfc *) 0;

    group_node_count++;

    /*
     * If he didn't include a "found" demux node, but there are nodes
     * to "find", "find" it.  If there are no nodes to find then
     * this is the first node in the tree and just needs to get
     * initialized appropriately.
     */
    if (!found_dp) {
	if (!(dcurr = group_node_head)) {
	    group_node_head = dp->right = dp->left = dp;
	    dp->group_mask = NODE_NOMASK;
	    return(dp);
        }
	mask = NODE_NOMASK;
	while (mask > dcurr->group_mask) {
	    mask = dcurr->group_mask;
	    if (key & mask) {
		dcurr = dcurr->right;
	    } else {
		dcurr = dcurr->left;
	    }
	}
	found_dp = dcurr;
    }

    /*
     * Here we have an insertion to do.  Figure out the first
     * (most significant) bit which differs from the "found" node.  This
     * tells us the bit we need to test in the node we insert.
     *
     * Do a binary search to find the byte the first bit is in, then use
     * the table to form the mask.
     */
    mask = key ^ found_dp->group_key;
    if (mask >= 0x10000) {
	if (mask >= 0x1000000) {
	    mask = ((u_int32)(node_bit_table[mask >> 24])) << 24;
	} else {
	    mask = ((u_int32)(node_bit_table[mask >> 16])) << 16;
	}
    } else {
	if (mask >= 0x100) {
	    mask = ((u_int32)(node_bit_table[mask >> 8])) << 8;
	} else {
	    mask = (u_int32)(node_bit_table[mask]);
	}
    }

    /*
     * XXX Sanity.  This could only happen if a node with the same key
     * is in the tree already, which should never happen.
     */
    assert(mask != 0);
    dp->group_mask = mask;

    /*
     * Now we locate where this guy needs to be inserted.  Search down
     * the tree until we find either an end node (i.e. an upward link)
     * or a node with a mask smaller than ours.  We insert our node
     * above this (watch for the case where the node we find is the
     * current root node), making one of the pointers an uplink pointing
     * at the node itself.
     */
    dprev = (group_node *) 0;
    dcurr = group_node_head;
    omask = NODE_NOMASK;
    while (omask > dcurr->group_mask) {
	omask = dcurr->group_mask;
	if (mask >= omask) {
	    break;
	}
	dprev = dcurr;
	if (key & omask) {
	    dcurr = dcurr->right;
	} else {
	    dcurr = dcurr->left;
	}
    }
    assert(mask != dcurr->group_mask);

    /*
     * Point the new node at the current node, and at itself.  The
     * pointer to the current node in the previous node is changed to
     * point at the new node.  Simple(?).
     */
    if (key & mask) {
	dp->right = dp;
	dp->left = dcurr;
    } else {
	dp->right = dcurr;
	dp->left = dp;
    }

    if (!dprev) {
	/* New root node */
	group_node_head = dp;
    } else if (dprev->right == dcurr) {
	dprev->right = dp;
    } else {
	dprev->left = dp;
    }

    return(dp);
}

#endif	/* IP_MULTICAST */
