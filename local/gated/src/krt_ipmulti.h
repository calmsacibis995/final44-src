/*
 *  $Id: krt_ipmulti.h,v 1.1 1995/01/26 07:46:32 pusateri Exp $
 */

/*%Copyright%*/


/*
 * Create callback list of routines to be called when
 * we are asked to resolve a forwarding cache entry.
 */

struct krt_mfc_recv {
    struct krt_mfc_recv *forw, *back;
    int errno;
    void (*recv_routine)();
};

#define	MFC_RECV_SCAN(cur, head) \
		{ for (cur = (head)->forw; cur != head; cur = cur->forw)
#define MFC_RECV_SCAN_END(cur, head) \
		if (cur == head) cur = (struct krt_mfc_recv *) 0; }

extern struct krt_mfc_recv krt_mfc_recv_head;

PROTOTYPE(krt_init_mfc,
	  extern void,
	  (void));

PROTOTYPE(krt_generate_mfc,
	  extern void,
	  (int,
	   sockaddr_un *,
	   if_addr *,
	   sockaddr_un *));

PROTOTYPE(krt_update_mfc,
	  extern void,
	  (mfc *));

PROTOTYPE(krt_check_mfc,
	  extern void,
	  (int,
	   sockaddr_un *,
	   sockaddr_un *));

PROTOTYPE(krt_register_mfc,
	  extern void,
	  (int,
	  _PROTOTYPE(func,
		     void,
		     (int,
		      if_addr *,
		      mfc *))));

PROTOTYPE(krt_unregister_mfc,
	  extern void,
	  (int,
	  _PROTOTYPE(func,
		     void,
		     (int,
		      if_addr *,
		      mfc *))));

PROTOTYPE(krt_resolve_cache,
	  extern void,
	  (sockaddr_un *,
	   sockaddr_un *,
	   mfc *));

PROTOTYPE(krt_delete_cache,
	  extern int,
	  (sockaddr_un *,
	   sockaddr_un *));

PROTOTYPE(krt_request_cache,
	  extern int,
	  (mfc *,
	   _PROTOTYPE(callback,
		      void,
		      (mfc *))));

PROTOTYPE(krt_enable_cache,
	  extern void,
	  (task *));

PROTOTYPE(krt_disable_cache,
	  extern void,
	  (task *));

PROTOTYPE(krt_locate_upstream,
	  extern upstream *,
	  (sockaddr_un *,
	   int));

PROTOTYPE(krt_add_vif,
	  extern void,
	  (if_addr *,
	   sockaddr_un *,
	   u_int32,
	   u_int32));

PROTOTYPE(krt_del_vif,
	  extern void,
	  (if_addr *));

