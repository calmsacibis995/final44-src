/*
 * $Id: asmatch.h,v 1.3.2.1 1994/04/20 13:58:24 jch Exp $
 */

/*%Copyright%*/

/*
 *  controls avl_tree - originally from avl.h
 */
struct avl_tree {
    struct avl_tree *back, *mid, *forw;
};

#define ASP_SKIP_SET 0x0001	/* part of a skip set */

struct _asp_trans {
  struct _asp_trans *next;
  struct _asp_state *state;
  u_short flags;
};

struct _asp_state {
  u_short asps_use_count;
  struct _asp_state *asps_grp;
  struct _asp_state *asps_grp_prev, *asps_grp_next;
  u_char asps_min, asps_max;
  /* u_char next_min, next_max; */
  struct _asp_table *asps_tree;
};

struct _asp_table {
  struct avl_tree search;	/* must be first */
  u_short use_count;
  as_t lo_as, hi_as;
  struct _asp_trans *trans;
};

typedef struct _asp_table asp_table;
typedef struct _asp_state asp_state;
typedef struct _asp_trans asp_trans;

struct _asmatch_t {
  flag_t origin_mask;
  struct _asp_table *first;
};

union _asp_alloc_blk {
  struct _asp_state state;
  struct _asp_table table;
  struct _asmatch_t regex;
};

typedef struct _asmatch_t asmatch_t;

struct _asp_range {
  u_short begin;
  u_short end;
};

typedef struct _asp_range asp_range;

typedef struct _asp_table * asp_stack; /* backward compatibility w/ parser.y */

PROTOTYPE(aspath_init_regex,
	  void,
	  (void));
PROTOTYPE(aspath_consume_current,
	  asmatch_t *,
	  (asp_stack));
PROTOTYPE(aspath_simple_regex,
	  void,
	  (asp_stack *,
	   asp_stack *));
PROTOTYPE(aspath_copy_regex,
	  void,
	  (asp_stack *,
	   asp_stack *));
PROTOTYPE(aspath_merge_regex,
	  void,
	  (asp_stack *,
	   asp_stack *,
	   asp_stack *));
PROTOTYPE(aspath_prepend_regex,
	  int,
	  (asp_stack *,
	   asp_stack *,
	   asp_stack *));
PROTOTYPE(aspath_zero_or_more_term,
	  void,
	  (asp_stack *,
	   asp_stack *));
PROTOTYPE(aspath_one_or_more_term,
	  void,
	  (asp_stack *,
	   asp_stack *));
PROTOTYPE(aspath_zero_or_one_term,
	  void,
	  (asp_stack *,
	   asp_stack *));
PROTOTYPE(aspath_range_term,
	  int,
	  (asp_stack *,
	   asp_stack *,
	   asp_range *));
PROTOTYPE(aspath_as_transition,
	  int,
	  (asp_stack *,
	   int));
PROTOTYPE(aspath_any_transition,
	  int,
	  (asp_stack *));


/* Routines to handle control information */

PROTOTYPE(aspath_adv_match,
	  extern int,
	  (void_t,
	   as_path *));
PROTOTYPE(aspath_adv_compare,
	  extern int,
	  (void_t,
	   void_t));
PROTOTYPE(aspath_adv_print,
	  void,
	  (FILE *, void_t));
PROTOTYPE(aspath_adv_free,
	  extern void,
	  (void_t));
PROTOTYPE(aspath_adv_origins,
	  extern char *,
	  (flag_t));

PROTOTYPE(init_asmatch_alloc,
	  void,
	  (void));
