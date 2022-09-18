/*
 * $Id: ospf_monitor.c,v 1.31.2.8 1995/04/04 20:05:10 jch Exp $
 */

/* %(Copyright.header) */


#define	INCLUDE_CTYPE
#define	INCLUDE_TIME
#define	INCLUDE_SIGNAL
#define	MALLOC_OK

#include "include.h"
#include "inet.h"
#include "ospf.h"
#include "string.h"

#define HISTORY_SIZE 30			/* Size of history cache */

#define HNEXT(NDX) (((NDX+1) == HISTORY_SIZE) ? 0 : (NDX + 1))
#define HLAST(NDX) (((NDX) == 0) ? HISTORY_SIZE - 1 : (NDX - 1))

static int gwsock = -1;		/* socket to receive gw info from */
static u_int16 port;			/* port to listen on */
static FILE *localfp;
static int got_signal;

static SIGTYPE
got_int __PF1(sig, int)
{
    got_signal = 1;

    SIGRETURN;
}


static const char *
lntoa __PF1(addr, u_long)
{
    static int i = 0;
    static char bufs[8][20];
    unsigned char *p = (unsigned char *) &addr;

    i = (i + 1) % (sizeof bufs / sizeof bufs[0]);
    sprintf(bufs[i], "%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
    return bufs[i];
}


static void
print_params __PF2(fp, FILE *,
		   buf, char *)
{
    int i;

    for (i = 0; i < 70; i++) {
	if (buf[i] == '\0')
	    fprintf(fp, " ");
	else if ((buf[i] == '\n') || (buf[i] == '\r'))
	    break;
	else
	    fprintf(fp, "%c", buf[i]);
    }
    fprintf(fp, "\n");
    fflush(fp);
}


static void
remote_help __PF0(void)
{
    printf("Remote-commands:\n");
    printf("   a <area id> <type> <ls id> <adv rtr>: show link state advertisement\n");
    printf("   c: show cumulative log\n");
    printf("   e: show cumulative errors\n");
    printf("   l: <retrans> dump lsdb (except for ASEs)\n");
    printf("   A: <retrans> dump ASEs\n");
    printf("   o: print ospf routing table\n");
    printf("   I: show interfaces\n");
    printf("   h: show next hops\n");
    printf("   N <r>: show neighbors - if r is set will print retrans lst\n");
}


static void
help __PF0(void)
{
    printf("Local commands:\n");
    printf("   ?: help \n");
    printf("   ?R: remote command information \n");
    printf("   d: show configured destinations\n");
    printf("   h: show history\n");
    printf("   x: exit\n");
    printf("   @ <remote command>: use last destination \n");
    printf("   @<dest index> <remote command>: use configured destination \n");
    printf("   F <filename>: write monitor information to filename\n");
    printf("   S: write monitor information to stdout (defalut)\n");
}


struct DEST {
    u_int32 dest;
    char *name;
    byte *auth;
} *dtab[100];

int destcnt;


/*
 * Syntax:
 *    <gw ip addr> <gw name> [<password>]
 *
 */
static void
monconf __PF1(fn, char *)
{
    int line = 0;
    FILE *fp;
    char buf[LINE_MAX];
    static const char *tokens = " \t\n";

    if (!(fp = fopen(fn, "r"))) {
	fprintf(stderr, "monconf: Can't open monitor conf file %s\n", fn);
	exit(1);
    }

    while (fgets(buf, sizeof(buf), fp)) {
	char *cp = buf;
	char *name = (char *) 0;
	byte *auth = (byte *) 0;
	struct in_addr addr;
	
	line++;
	
	switch (*cp) {
	case '\0':
	case '\n':
	case '#':
	    /* Blank line or a comment */
	    continue;
	}

	if (!(cp = strtok(cp, tokens))) {
	    /* Blank line */
	    continue;
	}

	if (!inet_aton(cp, &addr)) {
	    fprintf(stderr, "invalid address (%s) on line %d\n",
		    cp,
		    line);
	}
	
	name = strtok(NULL, tokens);
	if (!name) {
	    fprintf(stderr, "router name missing on line %d\n",
		    line);
	}

	/* Authentication field is optional */
	auth = (byte *) strtok(NULL, tokens);

	dtab[destcnt] = (struct DEST *) ((void_t) calloc(1,
							 (size_t) (sizeof (struct DEST) +
								   strlen(name) +
								   (auth ? strlen((char *) auth) : 0) + 2)));
	if (!dtab[destcnt]) {
	    fprintf(stderr, "out of memory reading %s at line %d\n",
		    fn,
		    line);
	    exit (1);
	}

	dtab[destcnt]->dest = addr.s_addr;
	if (name) {
	    dtab[destcnt]->name = (char *) (dtab[destcnt] + 1);
	    (void) strcpy(dtab[destcnt]->name, name);
	    if (auth) {
		dtab[destcnt]->auth = (byte *) (dtab[destcnt]->name + strlen(dtab[destcnt]->name) + 1);
		(void) strcpy((char *)dtab[destcnt]->auth, (char *) auth);
	    }
	}

	destcnt++;
    }
    
    fclose(fp);
}


static void
print_local __PF3(fp, FILE *,
		  to, u_int32,
		  name, char *)
{
#ifdef FD_ZERO
    fd_set ready;
#else	/* FD_ZERO */
    int ready;
#endif	/* FD_ZERO */
    struct timeval wait;
    struct sockaddr_in from;
    char buf[16*BUFSIZ];
    int i;

#ifndef FD_ZERO
#define FD_ZERO(SET) (*SET) = 0
#define FD_SET(FD,SET)	((*SET) |= (1 << (FD)))
#define FD_ISSET(FD,SET) ((*SET) & (1 << (FD)))
#endif
    FD_ZERO(&ready);
    FD_SET(gwsock, &ready);
    wait.tv_sec = 20;
    wait.tv_usec = 0;

    while ((i = select(gwsock + 1, &ready, 0, 0, &wait)) > 0) {
	if (FD_ISSET(gwsock, &ready)) {
	    int gw;

	    wait.tv_sec = 0;
	    i = sizeof (from);
	    if ((gw = accept(gwsock, (struct sockaddr *) &from, &i)) < 0) {
		perror("accept");
		return;
	    }
	    fprintf(fp, "\n          Source <<%-16s",
		    lntoa(from.sin_addr.s_addr));

	    if (name)
		fprintf(fp, " %s", name);

	    fprintf(fp, ">>\n");

	    while ((i = read(gw, buf, sizeof buf - 1)) > 0) {
		buf[i] = (char) 0;
		fputs(buf, fp);
	    }
	    if (i < 0) {
		switch (errno) {
		case EINTR:
		    if (got_signal) {
			got_signal = 0;
		    }
		    break;

		default:
		    perror("read");
		    break;
		}
	    }
	    if (close(gw) < 0)
		perror("close");
	    fprintf(fp, "\n");
	}
	FD_SET(gwsock, &ready);
    }

    if (i < 0) {
	switch (errno) {
	case EINTR:
	    if (got_signal) {
		got_signal = 0;
	    }
	    break;

	default:
	    perror("select");
	    break;
	}
    } else if (wait.tv_sec) {
	printf("Connection timeout: try again...\n");
    }
	
}


static void
txmon __PF6(fd, int,
	    req, u_int8,
	    buf, char *,
	    to, u_int32,
	    name, char *,
	    auth, byte *)
{
    size_t len = OSPF_HDR_SIZE + MON_REQ_SIZE;
    byte packet[OSPF_HDR_SIZE + MON_REQ_SIZE];
    struct OSPF_HDR *o_hdr = (struct OSPF_HDR *) ((void_t) packet);
    struct MON_HDR *m = &o_hdr->ospfh_un.mon;
    struct sockaddr_in dst;
    int dstlen = sizeof(dst);
    int local_wait = FALSE, i;
    int ret;
    char ip_addr_st[20], ip_mask_st[20], area_id_st[20];
    struct in_addr addr;

    /* sendit */
    bzero((caddr_t) m->p, sizeof m->p);
    printf("   remote-command <%c",
	   req);

    switch(req) {
    case 'a':
 	/* 
 	 * show advertisement 
 	 */
 	ret = sscanf(buf, "%*s %*s %s %lu %s %s",
		     area_id_st,
		     &m->p[1],
		     ip_addr_st,
		     ip_mask_st);

	if (ret != 4) {
	    fprintf(stderr, "usage: a <area id> <type> <ls id> <adv rtr>\n");
	    return;
	}

	if (!inet_aton(area_id_st, &addr)) {
	    fprintf(stderr, "Invalid Area ID: %s\n",
		    area_id_st);
	    return;
	}
	m->p[0] = addr.s_addr;
	if (!inet_aton(ip_addr_st, &addr)) {
	    fprintf(stderr, "Invalid LinkState-ID: %s\n",
		    ip_addr_st);
	    return;
	}
	GHTONL(m->p[1]);
 	m->p[2] = addr.s_addr;
	if (!inet_aton(ip_mask_st, &addr)) {
	    fprintf(stderr, "Invalid Advertising Router: %s\n",
		    ip_mask_st);
	    return;
	}
 	m->p[3] = addr.s_addr;
	ret = 4;
 	local_wait = TRUE;
	printf(" %s %u %s %s",
	       lntoa(m->p[0]),
	       m->p[1],
	       lntoa(m->p[2]),
	       lntoa(m->p[3]));
	break;
 	
    case 'c':
    case 'e':
    case 'l':
    case 'A':
    case 'o':
    case 'N':
    case 'I':
    case 'h':
    case 'V':
	local_wait = TRUE;
	/* Fall through */

    default:
 	ret = sscanf(buf, "%*s %*s %lu %lu %lu %lu %lu %lu %lu",
		     &m->p[0],
		     &m->p[1],
		     &m->p[2],
		     &m->p[3],
		     &m->p[4],
		     &m->p[5],
		     &m->p[6]);

 	for (i = 0; i < ret; i++) {
	    if (m->p[i]) {
		GHTONL(m->p[i]);
		printf(" %lu",
		       ntohl(m->p[i]));
	    }
  	}
    }
    printf("> sent to %s\n",
	   lntoa(to));

    m->type = MREQUEST;
    m->req = req;
    m->more = 0;
    m->param_cnt = ret;
    if (local_wait) {
	m->port = port;
	m->local = 1;
    } else {
	m->port = 0;
	m->local = 0;
    }
	
    o_hdr->ospfh_version = OSPF_VERSION;
    o_hdr->ospfh_type = OSPF_PKT_MON;
    o_hdr->ospfh_length = htons((u_int16) len);
    o_hdr->ospfh_rtr_id = 0;
    o_hdr->ospfh_area_id = 0;
    o_hdr->ospfh_checksum = 0;
    o_hdr->ospfh_auth_key[0] = o_hdr->ospfh_auth_key[1] = 0;

    o_hdr->ospfh_auth_type = htons(auth ? OSPF_AUTH_SIMPLE : OSPF_AUTH_NONE);
    o_hdr->ospfh_checksum = inet_cksum((caddr_t) packet, len);

    if (auth) {
	size_t al = strlen((char *) auth);

	if (al > OSPF_AUTH_SIMPLE_SIZE) {
	    al = OSPF_AUTH_SIMPLE_SIZE;
	}
	
	bcopy((caddr_t) auth, (caddr_t) o_hdr->ospfh_auth_key, al);
    }

    dst.sin_family = AF_INET;
    dst.sin_port = 0;
    dst.sin_addr.s_addr = (u_int32) to;
    while ((sendto(fd,
		 (char *) packet,
		 len,
		 0,
		 (struct sockaddr *) &dst,
		 dstlen)) < 0) {
	switch (errno) {
	case EINTR:
	    continue;
	    
	case ENETDOWN:
	case ENETUNREACH:
	case EHOSTDOWN:
	case EHOSTUNREACH:
	    perror("send");
	    break;

	default:
	    perror("send");
	    exit(1);
	}
	break;
    }
    if (local_wait)
	print_local(localfp, to, name);
}


int
main __PF2(argc, int,
	   argv, char **)
{
    int ndx, n;
    int sock;				/* Socket to send requests on */
    int bufndx = 0, curndx = 0;
    int length, cc, val;
    char buf[50][200];
    char dest_st[30], req_st[5], ndx_st[10], filename[30];
    char *name = 0, *lastname = 0;
    byte *auth = 0, *lastauth = 0;
    u_int32 p[MAXPARAMS], dest, lastdest = 0;
    struct sockaddr_in saddr;
    FILE *hp = (FILE *) NULL;
    struct in_addr addr;
    uid_t uid = getuid();

    /* Init file descriptor */
    localfp = stdout;
    
    signal(SIGINT, got_int);
    /* create a raw Multicast socket */
    if ((sock = socket(AF_INET, 
		       SOCK_RAW,
		       task_get_proto((trace *) 0,
				      "ospf",
				      IPPROTO_OSPF))) < 0) {
	perror("> socket(AF_INET, SOCK_RAW) fails");
	return 1;
    }

    /* Now that we have a socket, become a normal user */
    if (uid != 0
	&& setuid(getuid()) < 0) {
	perror("setuid");
	return 1;
    }

    /* Don't read from output socket */
    shutdown(sock, 0);

    /* create a stream socket for receiving info */
    if ((gwsock = socket(AF_INET, SOCK_STREAM, 0)) == (u_int) -1) {
	perror("> socket(AF_INET, SOCK_STREAM) fails");
	return 1;
    }
    cc = sizeof(val);
#ifdef SO_RCVBUF
    if (getsockopt(gwsock, SOL_SOCKET, SO_RCVBUF,
		   (char *) &val, &cc)) {
	perror("getsockopt");
	exit(1);
    }
#endif
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = 0;
    if (bind(gwsock, (struct sockaddr *) &saddr, sizeof(saddr))) {
	perror("bind: gw sock");
	exit(1);
    }
    length = sizeof(saddr);
    if (getsockname(gwsock, (struct sockaddr *) &saddr, &length)) {
	perror("getsockname failed");
	exit(1);
    }
    port = saddr.sin_port;
    listen(gwsock, 5);
    printf("listening on %s.%u\n",
	   inet_ntoa(saddr.sin_addr),
	   ntohs(saddr.sin_port));

    if (argc > 1)
	monconf(argv[1]);

    while (1) {
	register char *str;
	register size_t len;

	bufndx = HNEXT(bufndx);
	curndx++;
	bzero(buf[bufndx], 200);
	printf("[ %d ] dest command params > ", curndx);

	bzero((caddr_t) p, (MAXPARAMS * 4));
	dest = 0;
	name = (char *) NULL;
	bzero(dest_st, 30);
	bzero(req_st, 5);

	if (!(str = fgets(buf[bufndx], 200, stdin))) {
	    exit(1);
	}
	if (got_signal) {
	    got_signal = 0;
	}

	for (len = 0; *str; str++, len++) {
	    if (*str == '\n') {
		*str = 0;
		break;
	    }
	}
	if (!len) {	/* blank line */
	    ndx = curndx - 1;
	    goto history;
	}
	str = buf[bufndx];
	sscanf(str, "%s %s",
	       dest_st,
	       req_st);

	if (str[0] == '!') {
	    sscanf(&str[1], "%s", ndx_st);
	    if (!str[1] || isspace(str[1]))
		ndx = curndx - 1;
	    else {
		ndx = atoi(ndx_st);
		if ((ndx > (curndx - 1)) ||
		    (ndx < (curndx + 1 - HISTORY_SIZE))) {
		    printf("Bad history index: %d\n",
			   ndx);
		    continue;
		}
	    }
	history:
	    ndx = (ndx % HISTORY_SIZE);
	    sscanf(buf[ndx], "%s %s",
		   dest_st,
		   req_st);
	    bcopy(buf[ndx], str, 200);
	}
	
	if (isalpha(dest_st[0]) || ispunct(dest_st[0])) {
	    switch (dest_st[0]) {
	    case 'd':
		if (destcnt) {
		    for (ndx = 0; ndx < destcnt; ndx++) {
			printf("%d: %-15s %s\n",
			       ndx + 1,
			       lntoa(dtab[ndx]->dest),
			       dtab[ndx]->name);
		    }
		} else
		    printf("No destinations configured\n");
		break;

	    case 'h':
	    {
		int i;
		int start = (curndx > (HISTORY_SIZE - 1)) ? curndx - HISTORY_SIZE + 2 : 1;
		int end = curndx;

		for (i = start; i <= end; i++) {
		    printf("%d > ", i);
		    print_params(stdout,
				 buf[i % HISTORY_SIZE]);
		}
	    }
		break;

	    case '?':
		if (dest_st[1] == 'r' || dest_st[1] == 'R') {
		    remote_help();
		    break;
		}
		help();
		break;

	    case 'x':
		if (localfp != stdout) {
		    fclose(localfp);
		    if (hp)
			fclose(hp);
		}
		exit(1);

	    case '@':
		if (dest_st[1] == 0) {
		    if (lastdest) {
			name = lastname;
			dest = lastdest;
			auth = lastauth;
			goto lastd;
		    } else {
			printf("No last dest\n");
			continue;
		    }
		} else if (isdigit(dest_st[1])) {
		    if (!destcnt) {
			printf("Destination table not configured\n");
			continue;
		    }
		    ndx = atoi(&dest_st[1]);
		    if (ndx > 0 && ndx <= destcnt) {
			dest = dtab[ndx-1]->dest;
			name = dtab[ndx-1]->name;
			auth = dtab[ndx-1]->auth;
			lastdest = dest;
			lastname = name;
			lastauth = auth;
			goto lastd;
		    } else {
			printf("Invalid index %c\n", dest_st[1]);
			continue;
		    }
		} else {
		    printf("Invalid index %c\n", dest_st[1]);
		    continue;
		}

	    case 'F':
		n = sscanf(str, "%*s %s", filename);
		if (n < 0) {
		    printf("Filename not given\n");
		} else if ((localfp = fopen(filename, "w")) == (FILE *) NULL) {
		    fprintf(stderr, "Can't open %s\n",
			    filename);
		    localfp = stdout;
		}
		break;
	    case 'H':
		n = sscanf(str, "%*s %s", filename);
		if (n < 0) {
		    printf("Turning off history log\n");
		    if (hp) {
			fclose(hp);
			hp = (FILE *) NULL;
			}
		} else if ((hp = fopen(filename, "w")) == (FILE *) NULL) {
		    fprintf(stderr, "Can't open %s\n",
			    filename);
		    hp = (FILE *) NULL;;
		} else
		    printf("Turning on history log\n");
		break;

	    case 'S':
		if (localfp != stdout) {
		    fclose(localfp);
		    localfp = stdout;
		}
		break;

	    case 'q':
		goto exit;
	    }	
	    continue;
	} else {
	    if (dest_st[0] == '\n' || !strlen(dest_st)) {
		bufndx = HLAST(bufndx);
		curndx--;
		continue;
	    }
	    if (!inet_aton(dest_st, &addr)) {
		printf("   dest: (%s): unknown host \n", dest_st);
		continue;
	    }
	    dest = addr.s_addr;
	    lastdest = dest;
	    lastname = name;
	    lastauth = auth;
	}
      lastd:
	if (!strlen(req_st)) {
	    printf("   Illegal request: %s\n\n", req_st);
	    help();
	    continue;
	}
	if (hp)
	    print_params(hp, buf[bufndx]);
	txmon(sock, req_st[0], buf[bufndx], dest, name, auth);
    }

 exit:
    return 0;
}


/*
 * %(Copyright)
 * %(Copyright.OSPF)
 */
