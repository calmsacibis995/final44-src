/* 
 * $Id: rk_rpc.c,v 1.3 1993/12/23 16:47:09 dglo Exp dglo $
 * $Source: /a/guest/dglo/nuk/librkinit/RCS/rk_rpc.c,v $
 * $Author: dglo $
 *
 * This file contains functions that are used for network communication.
 * See the comment at the top of rk_lib.c for a description of the naming
 * conventions used within the rkinit library.
 */

#if !defined(lint) && !defined(SABER) && !defined(LOCORE) && defined(RCS_HDRS)
static char *rcsid = "$Id: rk_rpc.c,v 1.3 1993/12/23 16:47:09 dglo Exp dglo $";
#endif /* lint || SABER || LOCORE || RCS_HDRS */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#ifndef GOT_NETINET_IN_H
#include <netinet/in.h>
#define GOT_NETINET_IN_H
#endif /* GOT_NETINET_IN_H */
#include <netdb.h>
#include <errno.h>

#include <rkinit.h>
#include <rkinit_err.h>
#include <rkinit_private.h>

#include "bit32.h"
#include "sys_proto.h"

extern int errno;

static int sock;
struct sockaddr_in saddr;

static char errbuf[BUFSIZ];

#ifdef __STDC__
int rki_send_packet(int lsock, char type, BIT32 length, const char *data)
#else
int rki_send_packet(lsock, type, length, data)
  int lsock;
  char type;
  BIT32 length;
  const char *data;
#endif /* __STDC__ */
{
    int len;
    u_char *packet;
    BIT32 pkt_len;
    BIT32 net_pkt_len;

    pkt_len = length + PKT_DATA;

    if ((packet = (u_char *)calloc(pkt_len, sizeof(u_char))) == NULL) {
	sprintf(errbuf, "rki_send_packet: failure allocating %d bytes",
		pkt_len * sizeof(u_char));
	rkinit_errmsg(errbuf);
	return(RKINIT_MEMORY);
    }

    net_pkt_len = htonl(pkt_len);

    packet[PKT_TYPE] = type;
    bcopy((char *)&net_pkt_len, packet + PKT_LEN, sizeof(BIT32));
    bcopy(data, packet + PKT_DATA, length);
    
    if ((len = write(lsock, packet, pkt_len)) != pkt_len) {
	if (len == -1) 
	    sprintf(errbuf, "write: %s", sys_errlist[errno]);
	else 
	    sprintf(errbuf, "write: %d bytes written; %d bytes actually sent", 
		    pkt_len, len);
	rkinit_errmsg(errbuf);
	return(RKINIT_WRITE);
    }

    free(packet);
    return(RKINIT_SUCCESS);
}

#ifdef __STDC__
int rki_get_packet(int lsock, char type, BIT32 *length, char *data)
#else
int rki_get_packet(lsock, type, length, data)
  int lsock;
  char type;
  BIT32 *length;
  char *data;
#endif /* __STDC__ */
{
    int len;
    int len_sofar = 0;
    BIT32 expected_length = 0;
    int got_full_packet = FALSE;
    u_char *packet;

    BIT32 max_pkt_len;

    max_pkt_len = *length + PKT_DATA;

    if ((packet = (u_char *)calloc(max_pkt_len, sizeof(u_char))) == NULL) {
	sprintf(errbuf, "rki_get_packet: failure allocating %d bytes",
		max_pkt_len * sizeof(u_char));
	rkinit_errmsg(errbuf);
	return(RKINIT_MEMORY);
    }

    while (! got_full_packet) {
	if ((len = read(lsock, packet + len_sofar, 
			max_pkt_len - len_sofar)) < 0) {
	    sprintf(errbuf, "read: %s", sys_errlist[errno]);
	    rkinit_errmsg(errbuf);
	    return(RKINIT_READ);
	}
	len_sofar += len;
	if (len_sofar >= PKT_DATA) {
	    bcopy(packet + PKT_LEN, (char *)&expected_length, sizeof(BIT32));
	    expected_length = ntohl(expected_length);
	    if (expected_length == len_sofar)
		got_full_packet = TRUE;
	    else if (expected_length < len_sofar) {
		sprintf(errbuf, 
			"read: expected to receive only %d bytes; received %d",
			expected_length, len_sofar);
		rkinit_errmsg(errbuf);
		return(RKINIT_PACKET);
	    }
	    else if (expected_length > max_pkt_len) {
		sprintf(errbuf, "%s %d %s %d",
			"read: expected to receive", expected_length,
			"bytes, but only had room for", max_pkt_len);
		rkinit_errmsg(errbuf);
		return(RKINIT_PACKET);
	    }
	}
    }

    if (packet[PKT_TYPE] == MT_DROP) {
	BCLEAR(errbuf);
	rkinit_errmsg(errbuf);
	return(RKINIT_DROPPED);
    }

    if (packet[PKT_TYPE] != type) {
	sprintf(errbuf, "Expected packet type of %s; got %s",
		rki_mt_to_string(type), 
		rki_mt_to_string(packet[PKT_TYPE]));
	rkinit_errmsg(errbuf);
	return(RKINIT_PACKET); 
    }

    *length = len_sofar - PKT_DATA;
    bcopy(packet + PKT_DATA, data, *length);

    free(packet);

    return(RKINIT_SUCCESS);
}

#ifdef __STDC__
int rki_setup_rpc(char *host)
#else
int rki_setup_rpc(host)
  char *host;
#endif /* __STDC__ */
{
    struct hostent *hp;
    struct servent *sp;
    int port;

    SBCLEAR(saddr);
    SBCLEAR(hp);
    SBCLEAR(sp);

    if ((hp = gethostbyname(host)) == NULL) {
	sprintf(errbuf, "%s: unknown host.", host);
	rkinit_errmsg(errbuf);
	return(RKINIT_HOST);
    }

    if ((sp = getservbyname(SERVENT, "tcp")))
	port = sp->s_port;
    else 
	/* Fall back on known port number */
	port = htons(PORT);

    saddr.sin_family = hp->h_addrtype;
    bcopy(hp->h_addr, (char *)&saddr.sin_addr, hp->h_length);
    saddr.sin_port = port;

    if ((sock = socket(hp->h_addrtype, SOCK_STREAM, IPPROTO_IP)) < 0) {
	sprintf(errbuf, "socket: %s", sys_errlist[errno]);
	rkinit_errmsg(errbuf);
	return(RKINIT_SOCKET);
    }
    
    if (connect(sock, (char *)&saddr, sizeof (saddr)) < 0) {
	sprintf(errbuf, "connect: %s", sys_errlist[errno]);
	rkinit_errmsg(errbuf);
	close(sock);
	return(RKINIT_CONNECT);
    }

    return(RKINIT_SUCCESS);
}    

#ifdef __STDC__
int rki_rpc_exchange_version_info(int c_lversion, int c_hversion, 
				  int *s_lversion, int *s_hversion)
#else
int rki_rpc_exchange_version_info(c_lversion, c_hversion, 
				  s_lversion, s_hversion)
  int c_lversion;
  int c_hversion;
  int *s_lversion;
  int *s_hversion;
#endif /* __STDC__ */
{
    int status = RKINIT_SUCCESS;
    u_char version_info[VERSION_INFO_SIZE];
    BIT32 length = sizeof(version_info);
    
    version_info[0] = (u_char) c_lversion;
    version_info[1] = (u_char) c_hversion;
    
    if ((status = rki_send_packet(sock, MT_CVERSION, length,
				  (char *)version_info)) != RKINIT_SUCCESS)
	return(status);
    
    if ((status = rki_get_packet(sock, MT_SVERSION, &length, 
				 (char *)version_info)) != RKINIT_SUCCESS) 
	return(status);

    *s_lversion = (int) version_info[0];
    *s_hversion = (int) version_info[1];
    
    return(RKINIT_SUCCESS);
}

#ifdef __STDC__
int rki_rpc_send_rkinit_info(rkinit_info *info)
#else
int rki_rpc_send_rkinit_info(info)
  rkinit_info *info;
#endif /* __STDC__ */
{
    rkinit_info info_copy;
    
    bcopy(info, &info_copy, sizeof(rkinit_info));
    info_copy.lifetime = htonl(info_copy.lifetime);
    return(rki_send_packet(sock, MT_RKINIT_INFO, sizeof(rkinit_info), 
			   (char *)&info_copy));
}

#ifdef __STDC__
int rki_rpc_get_status(void)
#else
int rki_rpc_get_status()
#endif /* __STDC__ */
{
    char msg[BUFSIZ];
    int status = RKINIT_SUCCESS;
    BIT32 length = sizeof(msg);
   
    if ((status = rki_get_packet(sock, MT_STATUS, &length, msg)))
	return(status);

    if (length == 0)
	return(RKINIT_SUCCESS);
    else {
	rkinit_errmsg(msg);
	return(RKINIT_DAEMON);
    }
}

#ifdef __STDC__
int rki_rpc_get_ktext(int lsock, KTEXT auth, u_char type)
#else
int rki_rpc_get_ktext(lsock, auth, type)
  int lsock;
  KTEXT auth;
  u_char type;
#endif /* __STDC__ */
{
    int status = RKINIT_SUCCESS;
    BIT32 length = MAX_KTXT_LEN;

    if ((status = rki_get_packet(lsock, type, &length, (char *)auth->dat)))
	return(status);
    
    auth->length = length;
    
    return(RKINIT_SUCCESS);
}

#ifdef __STDC__
int rki_rpc_sendauth(KTEXT auth)
#else
int rki_rpc_sendauth(auth)
  KTEXT auth;
#endif /* __STDC__ */
{
    return(rki_send_packet(sock, MT_AUTH, auth->length, (char *)auth->dat));
}


#ifdef __STDC__
int rki_rpc_get_skdc(KTEXT scip)
#else
int rki_rpc_get_skdc(scip)
  KTEXT scip;
#endif /* __STDC__ */
{
    return(rki_rpc_get_ktext(sock, scip, MT_SKDC));
}

#ifdef __STDC__
int rki_rpc_send_ckdc(MSG_DAT *scip)
#else
int rki_rpc_send_ckdc(scip)
  MSG_DAT *scip;
#endif /* __STDC__ */
{
    return(rki_send_packet(sock, MT_CKDC, scip->app_length, 
			   (char *)scip->app_data));
}

#ifdef __STDC__
int rki_get_csaddr(struct sockaddr_in *caddrp, struct sockaddr_in *saddrp)
#else
int rki_get_csaddr(caddrp, saddrp)
  struct sockaddr_in *caddrp;
  struct sockaddr_in *saddrp;
#endif /* __STDC__ */
{
    int addrlen = sizeof(struct sockaddr_in);
    
    bcopy((char *)&saddr, (char *)saddrp, addrlen);

    if (getsockname(sock, caddrp, (struct sockaddr *)&addrlen) < 0) {
	sprintf(errbuf, "getsockname: %s", sys_errlist[errno]);
	rkinit_errmsg(errbuf);
	return(RKINIT_GETSOCK);
    }

    return(RKINIT_SUCCESS);
}

#ifdef __STDC__
void rki_drop_server(void)
#else
void rki_drop_server()
#endif /* __STDC__ */
{
    (void) rki_send_packet(sock, MT_DROP, 0, "");
}

#ifdef __STDC__
void rki_cleanup_rpc(void)
#else
void rki_cleanup_rpc()
#endif /* __STDC__ */
{
    rki_drop_server();
    (void) close(sock);
}
