

typedef struct _task_method_queue {
    struct _task_method *tmq_forw, *tmq_back;
} task_method_queue ;


#define	TMQ_TP(tmq, member)	((task *) ((void_t) ((byte *) (tmq) - offsetof(task, member))))

#define	TMQ_LIST(head, tp, member) \
	{ \
	     register task_method_queue *Xtmq_next = (tmq)->tmq_forw; \
	     while (Xtmq_next != (tmq)) { \
		 (tp) = TMQ_TP(Xtm_next, member); \
		 Xtmq_next = Xtmq_next->tmq_forw;

#define	TMQ_LIST_END(head, tp) }}


#define	TMQ_INSERT(tp, queue) \
	{ \
	     if (!(tp)->queue.tmq_forw) { \
		 register task_method_queue *Xtmq = queue.tmq_back; \
		 while (Xtmq->tmq_back != &queue \
			&& TMQ_TP(Xtmq, queue)->task_priority > (tp)->task_priority) { \
		     Xtmq = Xtmq->tmq_back; \
                 } \
	         INSQUE(&(tp)->queue, Xtmq); \
	     } \
	 }

#define	TMQ_REMOVE(tp, member) \
	{ \
	     if ((tp)->member.tmq_forw) { \
		 REMQUE(&(tp)->member); \
		 (tp)->member.tmq_forw = (tp)->member.tmq_back = (task_method_queue *) 0; \
	     } \
	} \



static task_method_queue task_read_queue = { &task_read_queue, &task_read_queue };
static task_method_queue task_write_queue = { &task_write_queue, &task_write_queue };
static task_method_queue task_flash_queue = { &task_flash_queue, &task_flash_queue };



static void
task_set_flash(tp, flash)
task *tp;
_PROTOTYPE(flash,
	   void,
	   (task *,
	    rt_list *));
{
    tp->task_flash = flash;
    if (flash) {
	TMQ_INSERT(&task_flash_queue, tp, task_flash_queue);
    } else {
	TMQ_REMOVE(tp, task_flash_queue);
    }
}


void
task_flash __PF1(change_list, rt_list *)
{
    task *tp;

    /* Change state */
    task_newstate(TASKS_FLASH, 0);

    TMQ_LIST(&task_flash_queue, tp, task_flash) {
	trace_tf(trace_global,
		 TR_TASK,
		 0,
		 ("task_flash: calling flash update routine for %s",
		  task_name(tp)));
	TASK_SAVE(tp, tp->task_flash(tp, change_list));
	trace_tf(trace_global,
		 TR_TASK,
		 0,
		 ("task_flash: return from flash update routine for %s",
		  task_name(tp)));
	TIMER_UPDATE();
    } TMQ_LIST_END(&task_flash_queue, tp, task_flash) ;

    /* Reset state */
    task_newstate(0, TASKS_FLASH);
}


/**/
void
task_set_socket __PF2(tp, task *,
		      s, int)
{
    tp->task_socket = s;

    trace_tp(tp,
	     TR_TASK,
	     0,
	     ("task_set_socket: task %s socket %d",
	      task_name(tp),
	      tp->task_socket));

    if (tp->task_socket > task_max_socket) {
	task_max_socket = tp->task_socket;
    }

    if (tp->task_recv || tp->task_accept) {
	FD_SET(tp->task_socket, &task_select_readbits);
	TMQ_INSERT(&task_read_queue, tp, task_read_queue);
    } else {
	FD_CLR(tp->task_socket, &task_select_readbits);
	TMQ_REMOVE(tp, task_read_queue);
    }

    if (tp->task_write || tp->task_connect) {
	FD_SET(tp->task_socket, &task_select_writebits);
	TMQ_INSERT(&task_write_queue, tp, task_write_queue);
    } else {
	FD_CLR(tp->task_socket, &task_select_writebits);
	TMQ_REMOVE(tp, task_write_queue);
    }
	
    if (tp->task_except) {
	FD_SET(tp->task_socket, &task_select_exceptbits);
    } else {
	FD_CLR(tp->task_socket, &task_select_exceptbits);
    }

}


void
task_reset_socket __PF1(tp, task *)
{

    trace_tp(tp,
	     TR_TASK,
	     0,
	     ("task_reset_socket: task %s socket %d",
	      task_name(tp),
	      tp->task_socket));

    FD_CLR(tp->task_socket, &task_select_readbits);
    FD_CLR(tp->task_socket, &task_select_writebits);
    FD_CLR(tp->task_socket, &task_select_exceptbits);

    /* Delete from socket to task table if no routines present */

    tp->task_socket = -1;
    BIT_RESET(tp->task_flags, TASKF_CONNECT | TASKF_ACCEPT);
    tp->task_recv = 0;
    tp->task_accept = 0;
    TMQ_REMOVE(tp, task_read_queue);
    tp->task_write = 0;
    tp->task_connect = 0;
    TMQ_REMOVE(tp, task_write_queue);
    tp->task_except = 0;
}

/**/

static void
task_process_sockets __PF3(read_bits, fd_set *,
			   write_bits, fd_set *,
			   except_bits, fd_set *)
{
    task *tp;

    if (
}
