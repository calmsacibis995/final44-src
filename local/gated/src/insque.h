
/* Definitions for INSQUE() and REMQUE() */
typedef struct _qelement {
    struct _qelement *q_forw;
    struct _qelement *q_back;
} * qelement;

#ifndef	INSQUE
/* Systems where insque() and remque() are routine calls */
#define INSQUE(elem, pred) { \
				  ((qelement) elem)->q_back = ((qelement) pred); \
				  ((qelement) elem)->q_forw = ((qelement) pred)->q_forw; \
				  ((qelement) pred)->q_forw->q_back = ((qelement) elem); \
				  ((qelement) pred)->q_forw = ((qelement) elem); \
			      }

#define	REMQUE(elem)	{ \
			     ((qelement) elem)->q_back->q_forw = ((qelement) elem)->q_forw; \
			     ((qelement) elem)->q_forw->q_back = ((qelement) elem)->q_back; \
			 }
#endif	/* INSQUE */


#define	QUEUE_RUN(head, elem, type)	for (elem = (type) ((qelement) &head)->q_forw; \
					     (struct qelement) elem != (qelement) &head; \
					     elem = (type) ((qelement) elem)->q_forw)
#define	QUEUE_RUN_END(head, elem, type)

#define	QUEUE_RUN_END_ZERO(head, elem, type)	if ((qelement) elem == (qelement) &head)
						    elem = (type) 0;


								       
									
