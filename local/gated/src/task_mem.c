struct task_block {
    struct task_size_block *tb_block;	/* Pointer to parent */
    struct task_block *tb_next;		/* Pointer to next in chain */

    const char *tb_name;    		/* Name for this block */

    u_int	tb_n_alloc;		/* Number of alloc requests */
    u_int	tb_n_free;		/* Number of free requests */
};


struct task_size_block {
    struct task_size_block *tsb_forw;	/* Queue glue */
    struct task_size_block *tsb_back;

    struct task_block tsb_block;	/* First block using this size */

    u_int tsb_size;			/* Size of this block */
    u_int tsb_count;			/* Number per page */
    u_int tsb_n_free;			/* Number free */
    block_t tsb_runt;			/* Where to hide the runt */
    qelement tsb_free;			/* Free list */
    qelement tsb_tmp;			/* Work area for allocation macro */

};



/* Free a clear block */
#define	task_block_free_clear(tbp, p) \
    do { \
	register qelement Xqp = (qelement) (p); \
	/* Put this element on the head of the list */ \
	Xqp->q_forw = (tbp)->tb_block->tsb_free; \
	(tbp)->tb_block->tsb_free = Xqp; \
	(tbp)->tb_block->tsb_n_free++, (tbp)->tb_n_free++; \
    } while (0)

/* Clear a block and return it */
#define	task_block_free(tbp, p) \
    do { \
	register void_t Xp = (void_t) (p); \
	bzero((caddr_t) Xp, (tbp)->tb_block->tsb_size); \
	task_block_free_clear(tbp, Xp); \
    } while (0)

/* Allocate a block */
#define	task_block_alloc(tbp) \
    ((tbp)->tb_block->tsb_tmp = ((tbp)->tb_block->tsb_free ? (tbp)->tb_block->tsb_free : task_block__alloc(tbp)), \
     (tbp)->tb_block->tsb_free = (tbp)->tb_block->tsb_tmp->q_forw, \
     (tbp)->tb_block->tsb_tmp->q_forw = (qelement) 0, \
     (tbp)->tb_block->tsb_n_free--, (tbp)->tb_n_alloc++, \
     (void_t) (tbp)->tb_block->tsb_tmp)


/**/


/* Head of block size queue */
static struct task_size_block task_block_head = {
	    &task_block_head, &task_block_head
	};

/* Pre-allocated block for size blocks */
static struct task_size_block task_block_sizes = {
    	    &task_block_sizes, &task_block_sizes,
	    {
		&task_block_sizes,
		(struct task_block *) 0,
		"task_size_block"
	    }
	};

static block_t task_block_name = (block_t) 0;

block_t task_block_pagesize = (block_t) 0;


block_t
task_block__init __PF2(size, register size_t,
		      name, const char *)
{
    register struct task_size_block *tsb = task_block_head.tsb_forw;
    struct task_block *tbp;
    register int count;
    size_t runt;

    /* Round up to the minimum size */
    size = ROUNDUP(size, TASK_BLOCK_ALIGN);

    count = task_pagesize / size;
    if (count < 1) {
    	/* Greater than a page, allocate one at a time */
	count = 1;
    }
    runt = (task_pagesize - ((size * count) % task_pagesize)) % task_pagesize;

    /* Look for this size in current list */
    do {
	if (tsb->tsb_size == size) {
	    /* Found the size block */

	    /* Check for duplicate request */
	    for (tbp = &tsb->tsb_block, tbp, tbp = tbp->tb_next) {
		assert(strcmp(name, tbp->tb_name));
	    }

	    /* Allocate a block for this caller */
	    tbp = task_block_alloc(task_block_name);
	    tbp->tb_next = tsb->tsb_block.tb_next;
	    goto Found;
	} else if (size < tsb->tsb_size) {
	    /* Insert before this one */

	    break;
	}
    } while ((tsb = tbp->tsb_forw) != &task_size_blocks) ;

    tsb = tsb->tsb_back;

    /* Allocate a block before this element */
    INSQUE(task_block_alloc(&task_block_blocks), tsb);
    tsb = tsb->tsb_forw;

    /* Fill in the info */
    tsb->tsb_size = size;
    tsb->tsb_count = count;

    /* Allocate a block for the runt */
    if (runt) {
	tsb->tsb_runt = task_block_init(runt, "runt");
    }

    tbp = &tsb->tsb_block;

 Found:
    tbp->tb_name = name;
    tsb->tsb_block.tb_next = tbp;

    return tbp;
}


static void_t
task_block_sbrk __PF1(size, size_t)
{
    size_t my_size = ROUNDUP(size, task_pagesize);
    void_t vp = (void_t) sbrk((int) my_size);

    if (vp == (caddr_t) -1) {
	int error = errno;
	
	trace_log_tf(trace_global,
		     0,
		     LOG_ERR,
		     ("task_block_sbrk: %m"));
	task_quit(error);
    }

    bzero(vp, my_size);
    return vp;
}


void_t
task_block_malloc __PF1(size, size_t)
{
    if (size > task_pagesize) {
	return task_block_sbrk(size);
    } else {
	return task_block_alloc(task_block_pagesize);
    }
}


void
task_block_reclaim __PF2(size, size_t,
			 p, void_t)
{
    int count = ROUNDUP(size, task_pagesize) / task_pagesize;

    while (count--) {
	task_block_free(task_block_pagesize, p);
	p = (void_t) ( (caddr_t) p + task_pagesize);
    }
}


qelement
task_block__alloc __PF1(tbp, register block_t)
{
    register qelement cp;
    register task_size_block *tsb = tbp->tb_block;

    /* Allocate another block of structures */
    register u_int n = tsb->tsb_count;
    register size_t size = n * tsb->tsb_size;
    register union {
	qelement qp;
	caddr_t cp;
    } np;

    if (size > task_pagesize ||
	tbp == task_block_pagesize ||
	!task_block_pagesize->tb_block->tsb_free) {
	/* Trying to get more pagesize blocks, just sbrk them */

	np.cp = (caddr_t) task_block_sbrk(size);
    } else {
	/* Getting one page, recurse */
	np.cp = (caddr_t) task_block_alloc(task_block_pagesize);
    }
    cp = np.qp;

    tsb->tsb_n_free += n;

    while (--n) {
	register qelement qp = np.qp;
	    
	np.cp += tsb->tsb_size;
	qp->q_forw = np.qp;
    }

    if (tsb->tsb_runt) {
	/* Find a home for the runt */

	np.cp += tsb->tsb_size;
	np.qp->q_forw = tsb->tsb_runt->tb_block->tsb_free;
	tsb->tsb_runt->tb_block->tsb_free = np.qp;
	tsb->tsb_runt->tb_block->tsb_n_free++;
    }

    return cp;
}


static void
task_block_init_all __PF0(void)
{
    size_t runt;

    /* Init the size block */
    task_block_size.tsb_size = ROUNDUP(sizeof (struct task_size_block), TASK_BLOCK_ALIGN);
    task_block_size.tsb_count = task_pagesize / task_block_size.tsb_size;

    /* Put it on the linked list */
    INSQUE(&task_block_size, &task_blocks);

    /* Create a block for runts if necessary */
    if ((runt = task_pagesize - (task_block_size.tsb_size * task_block_size.tsb_count))) {
	task_block_size.tsb_runt = task_block_init(runt, "runt");
    }

    /* Create a block for alternate allocations */
    task_block_name = task_block_init(sizeof (struct task_block), "task_block");

    /* Create a block for pages */
    task_block_pagesize = task_block_init(task_pagesize, "task_pagesize");
}


static void
task_block_dump __PF1(fp, FILE *)
{
    register struct task_size_block *tsb = task_block_head.tsb_forw;

    fprintf(fp, "Task Blocks:\n\tAllocation size: %5d\n\n",
	    task_pagesize);

    do {
	struct task_block *tbp = &tsb_block;

	fprintf(fp, "\tSize: %5u\tN_free: %u\tLastAlloc: %08X",
		tsb->tsb_size,
		tsb->tsb_n_free,
		tsb->tsb_tmp);

	do {
	    fprintf(fp, "\t\t%s\tAllocReq: %d\tFreeReq: %d\n",
		    tbp->tb_name,
		    tbp->tb_n_alloc,
		    tbp->tb_n_free);
	} while ((tbp = tbp->tb_next)) ;

    } while ((tbp = tsb->tsb_forw) != &task_block_head) ;

    fprintf(fp, "\n");
}
