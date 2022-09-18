/*
 *  Author: cck    Date: 88/05/19 13:14:04  
 *  Header: abkip.c,v 1.36 88/05/19 13:14:04 cck Rel  
 *  Revision: 1.36  
*/

/*
 * abkip.c - KIP (UDP encapsulated DDP packets) network module
 *
 *  abkip provides the interface from DDP to the outside world as it
 *  sees it.  It includes the DDP module "routeddp".
 *
 *  NOTE: when running KIP, no other LAP protocols are allowed
 * 
 *  The justification for including parts of "lap", "ddp", etc. is that
 *  that we are "gatewaying" and are allowed to do funny things at the
 *  boundaries
 *
 * AppleTalk package for UNIX (4.2 BSD).
 *
 * Copyright (c) 1986, 1987, 1988 by The Trustees of Columbia University 
 *  in the City of New York.
 *
 *
 * Edit History:
 *
 *  June 14, 1986    Schilit	Created.
 *  June 18, 1986    CCKim      Chuck's handler runs protocol
 *
 */
/*
 * The following list of exported routines is provided so you'll know what
 * have to be done to do another interface type (ethertalk, etc)
 *
 * EXPORTED ROUTINES:
 *
 *  OSErr GetNodeAddress(int *mynode, int *mynet)
 *     Return node addresses
 *  int abInit(boolean dispay_message)
 *     Initialize AppleTalk
 *  int abOpen(int *returnsocket, int wantsocket, struct iovec iov[], iovlen)
 *     Open a DDP socket
 *  int abClose(int socket)
 *     Close a DDP socket
 *  void abnet_cacheit(word srcNet, byte srcNode)
 *     Call in DDP protocol layer to tell the lower layer that
 *      the last packet that came in was from srcNet, srcNode
 *  int routeddp(struct iovec *iov, int iovlen)
 *     This is the DDP incursion.  With a full AppleTalk implementation,
 *     this would be part of DDP (abddp2).  This routes the DDP packet:
 *     normally would decide where to send and then send via lap, with KIP
 *     decides where and sends via UDP.
 *
*/

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/param.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netat/appletalk.h>
#include <netat/abnbp.h>	/* for nbpNIS */
#include <netat/compat.h>	/* to cover difference between bsd systems */

/*
 * Configuration defines
 *
 * NORECVMSG - no recvmsg
 * NOSENDMSG - no sendmsg
 * NEEDMSGHDR - no msghdr in sockets.h - define our own
 *
*/
#ifdef NORECVMSG
# ifndef NEEDNETBUF
#  define NEEDNETBUF
# endif
#endif
#ifdef NOSENDMSG
# ifndef NEEDNETBUF
#  define NEEDNETBUF
# endif
#endif

/* for forwarding */
/* These three define a lookaside */
/* could possibly be an array */
/* cf. ip_resolve */
private struct in_addr ipaddr_src; /* ip address */
/* ddp address */
private word ddp_srcnet;	/* ddp network part */
private byte ddp_srcnode;	/* ddp node part */

import struct in_addr bridge_addr; /* .. nearest known bridge */

private struct sockaddr_in from_sin; /* network struct of last packet rec. */

#define rebPort 902		/* 0x386 */
word rebport;			/* used to hold swabbed rebPort */

private struct sockaddr_in abfsin; /* apple bus foreign socketaddr/internet */

import word this_net;		/* our network number */
import byte this_node;		/* our node number */
import word nis_net;		/* network number of our nis */
import byte nis_node;		/* node number of our nis */

import int ddp_protocol();	/* DDP protocol handler */
private int kip_get();
export DBUG dbug;		/* debug flags */

/* BUG: bind doesn't work when lsin is on the stack! */
private struct sockaddr_in lsin; /* local socketaddr/internet */
private int skt2fd[ddpMaxSkt+1]; /* translate socket to file descriptor */
private int ddpskt2udpport[ddpMaxWKS+1]; /* ddp "wks" socket to udp port */

private LAP laph;

/* don't really need this */
#ifdef notdef
private char lapdata[lapMaxData];
private struct iovec lapiov[IOV_LAP_SIZE+1]; /* lap header + data */
#endif

/*
 * OSErr GetNodeAddress(int *myNode,*myNet)
 *
 * GetNodeAddress returns the net and node numbers for the current
 * host.
 *
 * N.B. - the myNet address is in net (htons) format.
 *
*/
export OSErr
GetNodeAddress(myNode,myNet)
int *myNode,*myNet;
{
  *myNode = this_node;
  *myNet = this_net;
  return(noErr);			   /* is ok */
}

/*
 * ddp to udp wks translate table
 *
*/
struct wks {
  char *name;			/* name of wks (as in /etc/services) */
  int ddpport;			/* ddp port to map from */
  int udpport;			/* udp port to map to */
  int notinited;		/* tried /etc/services? */
};

/* udpport is set to the old values for compatiblity */
/* insert in order to be nice */
#define WKS_entry(name, ddpsock) {(name), (ddpsock), ddpWKSUnix+(ddpsock), 1}

private struct wks wks[] = {
  WKS_entry("at-rtmp",rtmpSkt),
  WKS_entry("at-nbp",nbpNIS),
  WKS_entry("at-echo",echoSkt),
  WKS_entry("at-zip",zipZIS),
  WKS_entry(NULL, 0)
};

/*
 * Translate ddp socket to UDP port: returns 0 if no mapping
 *
*/
ddp2ipskt(ddpskt)
int ddpskt;
{
  struct wks *wksp;
  struct servent *serv;

  if (ddpskt < 0 || ddpskt > ddpMaxSkt)
    return(0);
  if (ddpskt & ddpWKS)		/* 128+x means non-wks */
    return(ddpskt + ddpNWKSUnix);
  if (ddpskt2udpport[ddpskt] < 0) {
    for (wksp = wks; wksp->name != NULL; wksp++)
      if (wksp->ddpport == ddpskt) {
	if ((serv = getservbyname(wksp->name, "udp")) != NULL)
	  wksp->udpport = ntohs(serv->s_port); /* silliness */
	if (dbug.db_ini)
	  fprintf(stderr, "port for %s is %d\n",wksp->name,wksp->udpport);
	endservent();
	ddpskt2udpport[ddpskt] = wksp->udpport;
	return(wksp->udpport);
      }
    ddpskt2udpport[ddpskt] = 0;
  }
  return(ddpskt2udpport[ddpskt]);
}

/*
 * initialize
 *
*/
export
abInit(disp)
{
  int i;

  for (i=0; i < ddpMaxSkt+1; i++) {
    skt2fd[i] = -1;		/* mark all these as unused */
  }
  for (i=0; i < ddpMaxWKS; i++)
    ddpskt2udpport[i] = -1;	/* mark unknown */


  rebport = htons(rebPort);	/* swap to netorder */
  init_fdlistening();

  abfsin.sin_family = AF_INET;
  abfsin.sin_addr.s_addr = INADDR_ANY;

  openatalkdb(NULL);		/* sets up this_* (take default file) */

  if (disp) {
      printf("abInit: [ddp: %3d.%02d, %d]",
	     ntohs(this_net)>>8, htons(this_net)&0xff, this_node);
      if (this_net != nis_net || this_node != nis_node)
	printf(", [NBP (atis) Server: %3d.%02d, %d]",
	       ntohs(nis_net)>>8, htons(nis_net)&0xff, nis_node);
      printf(" starting\n");
  }
  DDPInit();
#ifdef notdef
  /* nonsensical */
  LAPOpenProtocol(lapDDP,ddp_protocol); /* open protocol */
#endif

  return(0);
}  

/*
 * int abOpen(int *skt,rskt, iov, iovlen)
 *
 * abOpen opens the ddp socket in "skt" or if "skt" is zero allocates
 * and opens a new socket.  Upon return "skt" contains the socket number
 * and the returned value is >=0 if no error, < 0 if error.
 *
 * iov should be an array of type "struct iov" of length at least
 * IOV_LAP_SIZE+1.  Levels after IOV_LAP_LVL are assume to filled.
 *
*/
int abOpen(skt,rskt, iov, iovlen)
int *skt;
int rskt;
struct iovec *iov;
int iovlen;
{
  int i,fd,err;
  word ipskt;

#ifdef notdef
    /* could check iov not null and set to lapiov if not, etc */
    /* but necessary since only (likely) client is ddp */
    /* note: story is different for ethertalk, etc */
#endif
  /* good enough for now */
  if (iov == NULL || iovlen < IOV_LAP_SIZE+1 || iovlen > IOV_READ_MAX)
    return(-1);

  if ((fd = socket(AF_INET,SOCK_DGRAM,0)) < 0) {
    perror("abopen");
    return(fd);
  }
  lsin.sin_family = AF_INET;
  lsin.sin_addr.s_addr = INADDR_ANY;

  *skt = (rskt == 0 ? ddpWKS : rskt); /* zero rskt is free choice */
  ipskt = ddp2ipskt(*skt);	/* translate into ip socket number */
  if (ipskt == 0)		/* bad socket? */
    return(ddpSktErr);
  for (i=0; i < 128; i++,ipskt++,(*skt)++) {
    lsin.sin_port = htons(ipskt);
    if ((err = bind(fd, (caddr_t)&lsin, sizeof(lsin))) == 0)
      break;
    if (rskt != 0)		/* bind failed and wanted exact? */
      return(err);		/* yes... */
  }
  if (err == 0 && i < 128) {
    iov[IOV_LAP_LVL].iov_base = (caddr_t)&laph; /* remember this */
    iov[IOV_LAP_LVL].iov_len = lapSize; /* and this */
    fdlistener(fd, kip_get, iov, iovlen); /* remember for later */
    skt2fd[*skt] = fd;		/* remember file descriptor for socket */
    return(noErr);
  }
  perror("abopen bind");
  close(fd);
  return(err);
}

/*
 * close off socket opened by abClose
 *
*/
export int
abClose(skt)
int skt;
{
  int fd;

  if (skt < 0 || skt > ddpMaxSkt) {
    fprintf(stderr,"abClose: skt out of range\n");
    exit(0);
  }
  fd = skt2fd[skt];
  if (fd < 0)
    return(0);
  if (close(fd) != 0)
    perror("abClose");		/* some error... */
  fdunlisten(fd);
  skt2fd[skt] = -1;		/* mark as unused */
  return(0);
}

#ifdef NEEDNETBUF
#ifdef NEEDMSGHDR
struct msghdr {
  caddr_t msg_name;		/* name to send to */
  int msg_namelen;		/* size of name */
  struct iovec *msg_iov;	/* io vec */
  int msg_iovlen;		/* length */
  int msg_accrights;		/* dummy */
  int msg_accrightslen;
};
#endif

/* buffer larger than maximum ddp pkt by far */
private char net_buffer[ddpMaxData*2];

#ifdef NOSENDMSG
/*
 * limited sendmsg - limits to sizeof(net_buffer)
 *
*/
sendmsg(fd, msg, flags)
int fd;
struct msghdr *msg;
int flags;
{
  int err;
  int i, pos, len;
  struct iovec *iov;

  iov = msg->msg_iov;
  for (i=0, pos=0; i < msg->msg_iovlen; i++, iov++) {
    len = iov->iov_len;
    if (len+pos > sizeof(net_buffer)) /* if overflow */
      len = sizeof(net_buffer)-pos; /* then limit */
    bcopy(iov->iov_base, net_buffer+pos, len);
    pos+= len;
    if (len != iov->iov_len)	/* we don't have any more space */
      break;
  }
  len = pos;
  if ((err=sendto(fd,net_buffer,len,0,msg->msg_name,msg->msg_namelen)) < 0)
    perror("abwrite");
  return(err);
}

#endif /* NO SENDMSG */

#ifdef NORECVMSG
recvmsg(fd, msg, flags)
int fd;
struct msghdr *msg;
int flags;
{
  int err;
  int i, pos, len, blen;
  struct iovec *iov;

  err = recvfrom(fd, net_buffer, sizeof(net_buffer), 0,
		 msg->msg_name, &msg->msg_namelen);
  if (err < 0)
    perror("abread");
  for (blen=err,pos=0,i=0,iov=msg->msg_iov; i < msg->msg_iovlen; i++, iov++) {
    len = min(iov->iov_len, blen);
    if ((pos + len) > sizeof(net_buffer)) /* if asking for too much */
      len = sizeof(net_buffer) - pos; /* then limit */
    bcopy(net_buffer+pos, iov->iov_base, len);
    pos += len;
    blen -= len;
    /* either no more room or no more data */
    if (len != iov->iov_len)
      break;
  }
  return(err);  
}
#endif /* NO RECVMSG */
#endif

private int
kip_get(fd, iov, iovlen)
int fd;
struct iovec *iov;
int iovlen;
{
  struct msghdr msg;
  int len;
  LAP *lap;

  msg.msg_name = (caddr_t) &from_sin;
  msg.msg_namelen = sizeof(from_sin);
  msg.msg_iov = iov;
  msg.msg_iovlen = iovlen;
  msg.msg_accrights = 0;
  msg.msg_accrightslen = 0;
  if ((len = recvmsg(fd,&msg,0)) < 0) {
    perror("abread");
    return(len);
  }
  if (iov->iov_len != lapSize) /* check */
    return(-1);
  lap = (LAP *)iov->iov_base;
  switch (lap->type) {
  case lapDDP:
    return(ddp_protocol(iov+1, iovlen-1, len-lapSize));
    break;
  default:
    return(-1);
  }
  return(-1);
}

/*
 * This is the DDP/UDP interface 
 *
*/

/* srcNet and node of last incoming packet sent to DDP */
/* and valid */
export void
abnet_cacheit(srcNet, srcNode)
word srcNet;
byte srcNode;
{
  ddp_srcnet = srcNet;		/* remember where last packet came from */
  ddp_srcnode = srcNode;
  ipaddr_src.s_addr = (from_sin.sin_port == rebport) ? 0 :
    from_sin.sin_addr.s_addr;
}

private int
ip_resolve(ddpnet, ddpnode, iphost)
word ddpnet;
byte ddpnode;
struct in_addr *iphost;
{
  if (ipaddr_src.s_addr != 0 && ddpnet == ddp_srcnet && ddpnode == ddp_srcnode)
    iphost->s_addr = ipaddr_src.s_addr;
  else
    iphost->s_addr = bridge_addr.s_addr;
}

private LAP lap;

export int
routeddp(iov, iovlen)
struct iovec *iov;
int iovlen;
{
  struct msghdr msg;
  word destskt;
  struct in_addr desthost;
  DDP *ddp;
  int err;
  int fd;

  ddp = (DDP *)iov[IOV_DDP_LVL].iov_base; /* pick out ddp header */

  /* check ddp socket(s) for validity */
  if ( ddp->srcSkt == 0 || ddp->srcSkt == ddpMaxSkt ||
       ddp->dstSkt == 0 || ddp->dstSkt == ddpMaxSkt ||
      (fd = skt2fd[ddp->srcSkt]) == -1 )
    return(ddpSktErr);

  /* KIP routing code */
  /* establish dest socket */
  destskt = (word)htons(ddp2ipskt(ddp->dstSkt));
  if (destskt == 0)		/* byte swapped zero is still zero */
    return(ddpSktErr);
  /* resolve mapping */
  ip_resolve(ddp->dstNet, ddp->dstNode, &desthost);

  /* establish a dummy lap header */
  lap.type = lapDDP;
  lap.dst = ddp->dstNode;
  lap.src = this_node;
  iov[IOV_LAP_LVL].iov_base = (caddr_t) &lap; /* LAP header */
  iov[IOV_LAP_LVL].iov_len = lapSize; 	  /* size  */

  /* send through */
  abfsin.sin_addr = desthost;
  abfsin.sin_port = destskt;
  msg.msg_name = (caddr_t) &abfsin;
  msg.msg_namelen = sizeof(abfsin);
  msg.msg_iov = iov;
  msg.msg_iovlen = iovlen;
  msg.msg_accrights = 0;
  msg.msg_accrightslen = 0;
  if ((err = sendmsg(fd,&msg,0)) < 0)
    perror("abwrite");
  return(err);  
}
