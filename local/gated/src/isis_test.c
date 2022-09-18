/*
 *  $Id: isis_test.c,v 1.9 1992/12/07 03:17:19 jch Exp $
 */

/* %(Copyright.header) */


#ifdef notdef

/* these includes are overkill; they are what's included in krt.c */
#include "include.h"
#ifdef	notdef
#include <nlist.h>
#include <sys/ioctl.h>
#include <sys/mbuf.h>
#include <sys/file.h>
#endif	/* notdef */
#include "isis.h"
#include "isis_netd.h"

int isis_test_krt = 1; /* enable test interface */
int isis_ci = 0; /* used in parser */
int isis_circuits_parsed = 0; /* used in parser */
struct is_pc isis_ca[MAX_IS_PCTS]; /* used in parser */
int isis_get_krt_socket()
/* dummy routine to test krt interface.  For the time being, we just
	open a file that the routine updates get dumped into. */
{
	int fd;
	fd = creat("kernet_updates",0644);
	if (fd >= 0)
		return fd;
	perror("krt test creat failed");
	exit(-1) ;
}

int isis_get_recv_socket()
/* dummy routine for seting up the receive socket. As a gross hack, 
	we open a file here. yuck.
*/
{
	int fd;
	int dsocket;
	dsocket = task_get_socket(AF_UNIX,SOCK_DGRAM,0);
	if (dsocket < 0)
	{
	    perror("krt test creat failed");
	    exit(-1) ;
	}
	close(dsocket); /* we want to reallocate the fd */
	fd = netdReceiveSock(0);

	/* fd = open("isis_input",O_RDONLY,0644); */
	if (fd != dsocket)
		trace(TR_ALL,0,"fd %d != socket %d\n",fd,dsocket);
	if (fd >= 0)
	{
		return fd;
	}
	perror("krt test creat failed");
	exit(-1) ;
}
int 
isis_ioctl(fd,req,argp)
int fd,req;
char *argp;
/* dummy ioctl call */
{
	int rc;
	struct rtentry *rpt = (struct rtentry *) argp;
	rc = write(fd,argp, sizeof(*rpt));
	if (rc < 0)
		return -1;
	return 0;
}


/* initial startup code */
int doing_isis = FALSE;
pref_t isis_preference[3] = {255, RTPREF_ISIS_L1, RTPREF_ISIS_L2};	/* Preference for ISIS routes */
metric_t isis_default_metric = ISIS_METRIC_DEFAULT;

void
isis_cleanup(tp)
task *tp;
{}

void
isis_dump(tp)
task *tp;
{}

#define TBUF_SIZE 80
#define ISISMAXPACKETSIZE 1500 /* or something */
void 
isis_recv(tp)
task *tp;
{
    char  test_buf[TBUF_SIZE+1];
    int nread;
    struct netdHeader ndhdr;
    struct sockaddr_un      from;

    /* nread = read(tp->task_socket,test_buf,TBUF_SIZE); */
    netdRecvData(tp->task_socket,&ndhdr,test_buf,TBUF_SIZE,&from);
#ifdef oldcode
    test_buf[nread]=0;
    if ( nread <= 0) 
    {
	/* close(tp->task_socket); */
	/* may want task_reset here, but ignore temporarily */
	task_reset_socket(tp);
	return;
    }
#endif
    printf("netd: received %s\n",test_buf);
    /* trace(TR_ALL,0,"test input %s\n",test_buf); */
}

/*
 *	Initialize ISIS socket and task
 */
void
isis_init()
{
    if_addr *ifap;
    struct sockaddr_in addr;
    static task *isis_task = (task *) 0;

    sockclear_in(&addr);

    if (doing_isis) {
	if (!isis_task) {
	    char msgb[200];
	    isis_task = task_alloc("isis");
	    isis_task->task_cleanup = isis_cleanup;
	    isis_task->task_dump = isis_dump;
	    isis_task->task_recv = isis_recv;
	    isis_task->task_socket = isis_get_recv_socket();
	    if (!task_create(isis_task, ISISMAXPACKETSIZE)) {
		task_quit(EINVAL);
	    }
	    sprintf(msgb,"Hello there, I'm %d\n",getpid());
	    /* initialize the circuits */
	    {	int i;
		for (i=1; i<= isis_circuits_parsed; i++)
		{
		    sprintf(msgb,"Hello there, I'm %d on %d\n",
			getpid(),isis_ca[i].cid);
		    printf("open circuit %d id %d\n",i,isis_ca[i].cid);
		    netdJoinGroup(isis_task->task_socket,isis_ca[i].cid);
		    printf("sending msg %s\n",msgb);
		    netdTransmit(isis_task->task_socket,isis_ca[i].cid,0,msgb,strlen(msgb));
		}
	    }

	}
    } else {
	/* Delete any neighbors without tasks */

	isis_cleanup((task *) 0);
	if (isis_task) {
	    task_delete(isis_task);
	    isis_task = (task *) 0;
	}
    }
}

#endif	/* notdef */


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
