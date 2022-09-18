/*
 *  $Id: standalone.c,v 1.2.2.1 1994/07/12 20:30:01 jch Exp $
 */

/* %(Copyright.header) */

#define	MALLOC_OK
#include "include.h"

/* Support for stand-alone programs (ripquery, gdc) */

struct gtime task_time;

const bits ll_type_bits[] = {
    { LL_OTHER,		"Unknown" },
    { LL_8022,		"802.2" },
    { LL_X25,		"X.25" },
    { LL_PRONET,	"ProNET" },
    { LL_HYPER,		"HyperChannel" }
};


void
task_assert __PF3(file, const char *,
		  line, const int,
		  test, const char *)
{
    fprintf(stderr,
	    "Assertion failed: file \"%s\", line %d: %s",
	    file,
	    line,
	    test);

    /* Exit with a core dump */
    abort();
}


void_t
task_mem_malloc __PF2(tp, task *,
		      size, size_t)
{
    void_t p;

    p = (void_t) malloc(size);
    if (!p) {
	(void) fprintf(stderr,
		       "malloc: Can not malloc(%d)",
		       size);
	abort();
    }

    return p;
}


void_t
task_mem_calloc __PF3(tp, task *,
		      number, u_int,
		      size, size_t)
{
    void_t p;

    p = (void_t) calloc(number, size);
    if (!p) {
	(void) fprintf(stderr,
		       "calloc: Can not calloc(%d, %d)",
		       number,
		       size);
	abort();
    }

    return p;
}


/*ARGSUSED*/
void
task_mem_free __PF2(tp, task *,
		    p, void_t)
{
    if (p) {
	free((caddr_t) p);
    }
}


/**/

u_short
task_get_port __PF4(tf, trace *,
		    name, const char *,
		    proto, const char *,
		    default_port, u_short)
{
    struct servent *se = getservbyname(name, proto);
    u_short port;

    if (se) {
	port = se->s_port;
    } else {
	port = default_port;
	(void) fprintf(stderr,
		       "task_get_port: getservbyname(\"%s\", \"%s\") failed, using port %d\n",
		       name,
		       proto,
		       htons(port));
    }

    return port;
}

int
task_get_proto __PF3(tf, trace *,
		     name, const char *,
		     default_proto, int)
{
    struct protoent *pe = getprotobyname(name);
    int proto;

    if (pe) {
	proto = pe->p_proto;
    } else {
	proto = default_proto;
	(void) fprintf(stderr,
		       "task_get_proto: getprotobyname(\"%s\") failed, using proto %d\n",
		       name,
		       proto);
    }

    return proto;
}


/*
 * %(Copyright)
 */
