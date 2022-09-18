#ifndef lint
static char *sccsid = "@(#)tcp_conn.c	4.1     ULTRIX  9/13/88";
#endif

#include "lp.h"

/*
 *		T C P _ c o n n
 *
 * Create a TCP connection to the remote printer server.
 *
 * Inputs:		char *rhost;
 * Outputs:		none
 * Returns:		FD open on network printer
 *
 * The string "rhost" is expected to be something like "decwrl", or
 * "decwrl.dec.com", or "decwrl.dec.com/servicename". If the / is present,
 * then the string following it is the name of the service, to be looked
 * up in /etc/services. If no name is provided (the / is absent), then
 * the service "printserver" is assumed.
 *
 */
tcp_conn(rhost)
char *rhost;
{
    struct hostent *hp;
    struct servent *sp;
    struct sockaddr_in sin;
    int s, retries, aval;
    int err;
    char hostString[512];
    char serviceName[512];

    extern int sys_nerr;
    extern char *sys_errlist[];

    /*
     * Get the host address and port number to connect to.
     */
    strcpy(serviceName,"printserver");
    sscanf(rhost,"%[^/]/%[^/]", hostString, serviceName);
    bzero((char *)&sin, sizeof(sin));

    aval = inet_addr(hostString);
    if (aval != -1) {
	sin.sin_addr.s_addr = aval;
    } else {
	hp = gethostbyname(hostString);
	if (hp == (struct hostent *) NULL)
	    fatal("unknown host %s", hostString);
	sin.sin_addr.s_addr = *(int *) hp->h_addr;
    }
    sp = getservbyname(serviceName, "tcp");
    if (sp == (struct servent *) NULL)
        fatal("Service '%s/tcp' not defined. Fix /etc/services.",serviceName);
    sin.sin_family = AF_INET;
    sin.sin_port = sp->s_port;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        if ((errno > 0) && (errno <= sys_nerr))
            fatal("Can't get socket: %s",sys_errlist[errno]);
        else    fatal("Can't get socket, errno=%d",errno);
    }
    retries = 0;
    while (1) {
        if (connect(s, (caddr_t)&sin, sizeof(sin), 0) < 0) {
            err = errno;
            close(s);
	    retries = (retries > 5) ? 6 : retries+1;
	    status("Trying to connect to %s",hostString);
            if (err == ECONNREFUSED) sleep(1<<retries);
        } else
	    return(s);
    }
}

/*VARARGS1*/
static
status(msg, a1, a2, a3)
	char *msg;
{
	register int fd;
	char buf[BUFSIZ];

	umask(0);
	fd = open(ST, O_WRONLY|O_CREAT, 0664);
	if (fd < 0 || flock(fd, LOCK_EX) < 0)
		fatal("cannot create status file");
	ftruncate(fd, 0);
	sprintf(buf, msg, a1, a2, a3);
	strcat(buf, "\n");
	(void) write(fd, buf, strlen(buf));
	(void) close(fd);
}

