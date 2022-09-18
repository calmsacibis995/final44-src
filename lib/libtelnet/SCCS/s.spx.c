h52432
s 00135/00135/00427
d D 8.2 95/05/30 20:13:26 dab 4 3
c Code cleanup, use mem*() instead of b*()
e
s 00002/00002/00560
d D 8.1 93/06/04 17:37:31 bostic 3 2
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00558
d D 5.2 93/05/20 10:51:41 dab 2 1
c Fix all the "#if defined(ENCRYPTION)" lines to just
c be "#ifdef ENCRYPTION", so that unifdef can be used to strip
c out all the encryption code.
e
s 00562/00000/00000
d D 5.1 93/01/20 12:51:45 dab 1 0
c date and time created 93/01/20 12:51:45 by dab
e
u
U
t
T
I 1
/*-
D 3
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 3
I 3
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 3
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

#ifdef	SPX
/*
 * COPYRIGHT (C) 1990 DIGITAL EQUIPMENT CORPORATION
 * ALL RIGHTS RESERVED
 *
 * "Digital Equipment Corporation authorizes the reproduction,
 * distribution and modification of this software subject to the following
 * restrictions:
 *
 * 1.  Any partial or whole copy of this software, or any modification
 * thereof, must include this copyright notice in its entirety.
 *
 * 2.  This software is supplied "as is" with no warranty of any kind,
 * expressed or implied, for any purpose, including any warranty of fitness
 * or merchantibility.  DIGITAL assumes no responsibility for the use or
 * reliability of this software, nor promises to provide any form of
 * support for it on any basis.
 *
 * 3.  Distribution of this software is authorized only if no profit or
 * remuneration of any kind is received in exchange for such distribution.
 *
 * 4.  This software produces public key authentication certificates
 * bearing an expiration date established by DIGITAL and RSA Data
 * Security, Inc.  It may cease to generate certificates after the expiration
 * date.  Any modification of this software that changes or defeats
 * the expiration date or its effect is unauthorized.
 *
 * 5.  Software that will renew or extend the expiration date of
 * authentication certificates produced by this software may be obtained
 * from RSA Data Security, Inc., 10 Twin Dolphin Drive, Redwood City, CA
 * 94065, (415)595-8782, or from DIGITAL"
 *
 */

#include <sys/types.h>
#include <arpa/telnet.h>
#include <stdio.h>
#include "gssapi_defs.h"
#ifdef	__STDC__
#include <stdlib.h>
#endif
#ifdef	NO_STRING_H
#include <strings.h>
#else
#include <string.h>
#endif

#include <pwd.h>
#include "encrypt.h"
#include "auth.h"
#include "misc.h"

extern auth_debug_mode;

static unsigned char str_data[1024] = { IAC, SB, TELOPT_AUTHENTICATION, 0,
			  		AUTHTYPE_SPX, };
static unsigned char str_name[1024] = { IAC, SB, TELOPT_AUTHENTICATION,
					TELQUAL_NAME, };

#define	SPX_AUTH	0		/* Authentication data follows */
#define	SPX_REJECT	1		/* Rejected (reason might follow) */
#define SPX_ACCEPT	2		/* Accepted */

D 2
#if	defined(ENCRYPTION)
E 2
I 2
#ifdef	ENCRYPTION
E 2
static Block	session_key	= { 0 };
D 2
#endif
E 2
I 2
#endif	/* ENCRYPTION */
E 2
static Schedule sched;
D 2
static Block	challange	= { 0 };
E 2
I 2
static Block	challenge	= { 0 };
E 2


/*******************************************************************/

D 4
gss_OID_set           actual_mechs;
gss_OID               actual_mech_type, output_name_type;
int                   major_status, status, msg_ctx = 0, new_status;
int                   req_flags = 0, ret_flags, lifetime_rec;
gss_cred_id_t         gss_cred_handle;
gss_ctx_id_t          actual_ctxhandle, context_handle;
gss_buffer_desc       output_token, input_token, input_name_buffer;
gss_buffer_desc       status_string;
gss_name_t            desired_targname, src_name;
gss_channel_bindings  input_chan_bindings;
char                  lhostname[GSS_C_MAX_PRINTABLE_NAME];
char                  targ_printable[GSS_C_MAX_PRINTABLE_NAME];
int                   to_addr=0, from_addr=0;
char                  *address;
gss_buffer_desc       fullname_buffer;
gss_OID               fullname_type;
gss_cred_id_t         gss_delegated_cred_handle;
E 4
I 4
gss_OID_set		actual_mechs;
gss_OID			actual_mech_type, output_name_type;
int			major_status, status, msg_ctx = 0, new_status;
int			req_flags = 0, ret_flags, lifetime_rec;
gss_cred_id_t		gss_cred_handle;
gss_ctx_id_t		actual_ctxhandle, context_handle;
gss_buffer_desc		output_token, input_token, input_name_buffer;
gss_buffer_desc		status_string;
gss_name_t		desired_targname, src_name;
gss_channel_bindings	input_chan_bindings;
char			lhostname[GSS_C_MAX_PRINTABLE_NAME];
char			targ_printable[GSS_C_MAX_PRINTABLE_NAME];
int			to_addr=0, from_addr=0;
char			*address;
gss_buffer_desc		fullname_buffer;
gss_OID			fullname_type;
gss_cred_id_t		gss_delegated_cred_handle;
E 4

/*******************************************************************/



	static int
Data(ap, type, d, c)
	Authenticator *ap;
	int type;
	void *d;
	int c;
{
D 4
        unsigned char *p = str_data + 4;
E 4
I 4
	unsigned char *p = str_data + 4;
E 4
	unsigned char *cd = (unsigned char *)d;

	if (c == -1)
		c = strlen((char *)cd);

D 4
        if (0) {
                printf("%s:%d: [%d] (%d)",
                        str_data[3] == TELQUAL_IS ? ">>>IS" : ">>>REPLY",
                        str_data[3],
                        type, c);
                printd(d, c);
                printf("\r\n");
        }
E 4
I 4
	if (0) {
		printf("%s:%d: [%d] (%d)",
			str_data[3] == TELQUAL_IS ? ">>>IS" : ">>>REPLY",
			str_data[3],
			type, c);
		printd(d, c);
		printf("\r\n");
	}
E 4
	*p++ = ap->type;
	*p++ = ap->way;
	*p++ = type;
D 4
        while (c-- > 0) {
                if ((*p++ = *cd++) == IAC)
                        *p++ = IAC;
        }
        *p++ = IAC;
        *p++ = SE;
E 4
I 4
	while (c-- > 0) {
		if ((*p++ = *cd++) == IAC)
			*p++ = IAC;
	}
	*p++ = IAC;
	*p++ = SE;
E 4
	if (str_data[3] == TELQUAL_IS)
		printsub('>', &str_data[2], p - (&str_data[2]));
D 4
        return(net_write(str_data, p - str_data));
E 4
I 4
	return(net_write(str_data, p - str_data));
E 4
}

	int
spx_init(ap, server)
	Authenticator *ap;
	int server;
{
D 4
        gss_cred_id_t    tmp_cred_handle;
E 4
I 4
	gss_cred_id_t	tmp_cred_handle;
E 4

	if (server) {
		str_data[3] = TELQUAL_REPLY;
		gethostname(lhostname, sizeof(lhostname));
		strcpy(targ_printable, "SERVICE:rcmd@");
		strcat(targ_printable, lhostname);
		input_name_buffer.length = strlen(targ_printable);
		input_name_buffer.value = targ_printable;
		major_status = gss_import_name(&status,
D 4
                                       &input_name_buffer,
                                       GSS_C_NULL_OID,
                                       &desired_targname);
E 4
I 4
					&input_name_buffer,
					GSS_C_NULL_OID,
					&desired_targname);
E 4
		major_status = gss_acquire_cred(&status,
D 4
                                        desired_targname,
                                        0,
                                        GSS_C_NULL_OID_SET,
                                        GSS_C_ACCEPT,
                                        &tmp_cred_handle,
                                        &actual_mechs,
                                        &lifetime_rec);
E 4
I 4
					desired_targname,
					0,
					GSS_C_NULL_OID_SET,
					GSS_C_ACCEPT,
					&tmp_cred_handle,
					&actual_mechs,
					&lifetime_rec);
E 4
		if (major_status != GSS_S_COMPLETE) return(0);
	} else {
		str_data[3] = TELQUAL_IS;
	}
	return(1);
}

	int
spx_send(ap)
	Authenticator *ap;
{
	Block enckey;
	int r;

D 4
	gss_OID  actual_mech_type, output_name_type;
	int           msg_ctx = 0, new_status, status;
	int           req_flags = 0, ret_flags, lifetime_rec, major_status;
E 4
I 4
	gss_OID	actual_mech_type, output_name_type;
	int	msg_ctx = 0, new_status, status;
	int	req_flags = 0, ret_flags, lifetime_rec, major_status;
E 4
	gss_buffer_desc  output_token, input_token, input_name_buffer;
	gss_buffer_desc  output_name_buffer, status_string;
	gss_name_t    desired_targname;
	gss_channel_bindings  input_chan_bindings;
	char targ_printable[GSS_C_MAX_PRINTABLE_NAME];
	int  from_addr=0, to_addr=0, myhostlen, j;
	int  deleg_flag=1, mutual_flag=0, replay_flag=0, seq_flag=0;
	char *address;

	printf("[ Trying SPX ... ]\n");
	strcpy(targ_printable, "SERVICE:rcmd@");
	strcat(targ_printable, RemoteHostName);

	input_name_buffer.length = strlen(targ_printable);
	input_name_buffer.value = targ_printable;

	if (!UserNameRequested) {
		return(0);
	}

	major_status = gss_import_name(&status,
D 4
				       &input_name_buffer,
				       GSS_C_NULL_OID,
				       &desired_targname);
E 4
I 4
					&input_name_buffer,
					GSS_C_NULL_OID,
					&desired_targname);
E 4


	major_status = gss_display_name(&status,
					desired_targname,
					&output_name_buffer,
					&output_name_type);

	printf("target is '%s'\n", output_name_buffer.value); fflush(stdout);

	major_status = gss_release_buffer(&status, &output_name_buffer);

	input_chan_bindings = (gss_channel_bindings)
	  malloc(sizeof(gss_channel_bindings_desc));

	input_chan_bindings->initiator_addrtype = GSS_C_AF_INET;
	input_chan_bindings->initiator_address.length = 4;
	address = (char *) malloc(4);
	input_chan_bindings->initiator_address.value = (char *) address;
	address[0] = ((from_addr & 0xff000000) >> 24);
	address[1] = ((from_addr & 0xff0000) >> 16);
	address[2] = ((from_addr & 0xff00) >> 8);
	address[3] = (from_addr & 0xff);
	input_chan_bindings->acceptor_addrtype = GSS_C_AF_INET;
	input_chan_bindings->acceptor_address.length = 4;
	address = (char *) malloc(4);
	input_chan_bindings->acceptor_address.value = (char *) address;
	address[0] = ((to_addr & 0xff000000) >> 24);
	address[1] = ((to_addr & 0xff0000) >> 16);
	address[2] = ((to_addr & 0xff00) >> 8);
	address[3] = (to_addr & 0xff);
	input_chan_bindings->application_data.length = 0;

D 4
        req_flags = 0;
        if (deleg_flag)  req_flags = req_flags | 1;
        if (mutual_flag) req_flags = req_flags | 2;
        if (replay_flag) req_flags = req_flags | 4;
        if (seq_flag)    req_flags = req_flags | 8;
E 4
I 4
	req_flags = 0;
	if (deleg_flag)  req_flags = req_flags | 1;
	if (mutual_flag) req_flags = req_flags | 2;
	if (replay_flag) req_flags = req_flags | 4;
	if (seq_flag)    req_flags = req_flags | 8;
E 4

D 4
        major_status = gss_init_sec_context(&status,         /* minor status */
E 4
I 4
	major_status = gss_init_sec_context(&status,         /* minor status */
E 4
					GSS_C_NO_CREDENTIAL, /* cred handle */
D 4
                                        &actual_ctxhandle,   /* ctx handle */
                                        desired_targname,    /* target name */
                                        GSS_C_NULL_OID,      /* mech type */
                                        req_flags,           /* req flags */
                                        0,                   /* time req */
                                        input_chan_bindings, /* chan binding */
                                        GSS_C_NO_BUFFER,     /* input token */
                                        &actual_mech_type,   /* actual mech */
                                        &output_token,       /* output token */
                                        &ret_flags,          /* ret flags */
                                        &lifetime_rec);      /* time rec */
E 4
I 4
					&actual_ctxhandle,   /* ctx handle */
					desired_targname,    /* target name */
					GSS_C_NULL_OID,      /* mech type */
					req_flags,           /* req flags */
					0,                   /* time req */
					input_chan_bindings, /* chan binding */
					GSS_C_NO_BUFFER,     /* input token */
					&actual_mech_type,   /* actual mech */
					&output_token,       /* output token */
					&ret_flags,          /* ret flags */
					&lifetime_rec);      /* time rec */
E 4

	if ((major_status != GSS_S_COMPLETE) &&
	    (major_status != GSS_S_CONTINUE_NEEDED)) {
D 4
          gss_display_status(&new_status,
                             status,
                             GSS_C_MECH_CODE,
                             GSS_C_NULL_OID,
                             &msg_ctx,
                             &status_string);
          printf("%s\n", status_string.value);
E 4
I 4
	  gss_display_status(&new_status,
				status,
				GSS_C_MECH_CODE,
				GSS_C_NULL_OID,
				&msg_ctx,
				&status_string);
	  printf("%s\n", status_string.value);
E 4
	  return(0);
	}

	if (!auth_sendname(UserNameRequested, strlen(UserNameRequested))) {
		return(0);
	}

	if (!Data(ap, SPX_AUTH, (void *)output_token.value, output_token.length)) {
		return(0);
	}

	return(1);
}

	void
spx_is(ap, data, cnt)
	Authenticator *ap;
	unsigned char *data;
	int cnt;
{
	Session_Key skey;
	Block datablock;
	int r;

	if (cnt-- < 1)
		return;
	switch (*data++) {
	case SPX_AUTH:
D 4
	        input_token.length = cnt;
E 4
I 4
		input_token.length = cnt;
E 4
		input_token.value = (char *) data;

		gethostname(lhostname, sizeof(lhostname));

		strcpy(targ_printable, "SERVICE:rcmd@");
		strcat(targ_printable, lhostname);

		input_name_buffer.length = strlen(targ_printable);
		input_name_buffer.value = targ_printable;

		major_status = gss_import_name(&status,
D 4
                                       &input_name_buffer,
                                       GSS_C_NULL_OID,
                                       &desired_targname);
E 4
I 4
					&input_name_buffer,
					GSS_C_NULL_OID,
					&desired_targname);
E 4

		major_status = gss_acquire_cred(&status,
D 4
                                        desired_targname,
                                        0,
                                        GSS_C_NULL_OID_SET,
                                        GSS_C_ACCEPT,
                                        &gss_cred_handle,
                                        &actual_mechs,
                                        &lifetime_rec);
E 4
I 4
					desired_targname,
					0,
					GSS_C_NULL_OID_SET,
					GSS_C_ACCEPT,
					&gss_cred_handle,
					&actual_mechs,
					&lifetime_rec);
E 4

		major_status = gss_release_name(&status, desired_targname);

		input_chan_bindings = (gss_channel_bindings)
		  malloc(sizeof(gss_channel_bindings_desc));

		input_chan_bindings->initiator_addrtype = GSS_C_AF_INET;
		input_chan_bindings->initiator_address.length = 4;
		address = (char *) malloc(4);
		input_chan_bindings->initiator_address.value = (char *) address;
		address[0] = ((from_addr & 0xff000000) >> 24);
		address[1] = ((from_addr & 0xff0000) >> 16);
		address[2] = ((from_addr & 0xff00) >> 8);
		address[3] = (from_addr & 0xff);
		input_chan_bindings->acceptor_addrtype = GSS_C_AF_INET;
		input_chan_bindings->acceptor_address.length = 4;
		address = (char *) malloc(4);
		input_chan_bindings->acceptor_address.value = (char *) address;
		address[0] = ((to_addr & 0xff000000) >> 24);
		address[1] = ((to_addr & 0xff0000) >> 16);
		address[2] = ((to_addr & 0xff00) >> 8);
		address[3] = (to_addr & 0xff);
		input_chan_bindings->application_data.length = 0;

		major_status = gss_accept_sec_context(&status,
D 4
					      &context_handle,
                                              gss_cred_handle,
                                              &input_token,
                                              input_chan_bindings,
                                              &src_name,
                                              &actual_mech_type,
                                              &output_token,
                                              &ret_flags,
                                              &lifetime_rec,
                                              &gss_delegated_cred_handle);
E 4
I 4
						&context_handle,
						gss_cred_handle,
						&input_token,
						input_chan_bindings,
						&src_name,
						&actual_mech_type,
						&output_token,
						&ret_flags,
						&lifetime_rec,
						&gss_delegated_cred_handle);
E 4


		if (major_status != GSS_S_COMPLETE) {

		  major_status = gss_display_name(&status,
D 4
					  src_name,
                                          &fullname_buffer,
                                          &fullname_type);
E 4
I 4
					src_name,
					&fullname_buffer,
					&fullname_type);
E 4
			Data(ap, SPX_REJECT, (void *)"auth failed", -1);
			auth_finished(ap, AUTH_REJECT);
			return;
		}

		major_status = gss_display_name(&status,
D 4
                                          src_name,
                                          &fullname_buffer,
                                          &fullname_type);
E 4
I 4
					src_name,
					&fullname_buffer,
					&fullname_type);
E 4


		Data(ap, SPX_ACCEPT, (void *)output_token.value, output_token.length);
		auth_finished(ap, AUTH_USER);
		break;

	default:
		Data(ap, SPX_REJECT, 0, 0);
		break;
	}
}


	void
spx_reply(ap, data, cnt)
	Authenticator *ap;
	unsigned char *data;
	int cnt;
{
	Session_Key skey;

	if (cnt-- < 1)
		return;
	switch (*data++) {
	case SPX_REJECT:
		if (cnt > 0) {
			printf("[ SPX refuses authentication because %.*s ]\r\n",
				cnt, data);
		} else
			printf("[ SPX refuses authentication ]\r\n");
		auth_send_retry();
		return;
	case SPX_ACCEPT:
		printf("[ SPX accepts you ]\n");
		if ((ap->way & AUTH_HOW_MASK) == AUTH_HOW_MUTUAL) {
			/*
D 2
			 * Send over the encrypted challange.
E 2
I 2
			 * Send over the encrypted challenge.
E 2
		 	 */
		  input_token.value = (char *) data;
		  input_token.length = cnt;

		  major_status = gss_init_sec_context(&status, /* minor stat */
D 4
                                        GSS_C_NO_CREDENTIAL, /* cred handle */
                                        &actual_ctxhandle,   /* ctx handle */
                                        desired_targname,    /* target name */
                                        GSS_C_NULL_OID,      /* mech type */
                                        req_flags,           /* req flags */
                                        0,                   /* time req */
                                        input_chan_bindings, /* chan binding */
                                        &input_token,        /* input token */
                                        &actual_mech_type,   /* actual mech */
                                        &output_token,       /* output token */
                                        &ret_flags,          /* ret flags */
                                        &lifetime_rec);      /* time rec */
E 4
I 4
					GSS_C_NO_CREDENTIAL, /* cred handle */
					&actual_ctxhandle,   /* ctx handle */
					desired_targname,    /* target name */
					GSS_C_NULL_OID,      /* mech type */
					req_flags,           /* req flags */
					0,                   /* time req */
					input_chan_bindings, /* chan binding */
					&input_token,        /* input token */
					&actual_mech_type,   /* actual mech */
					&output_token,       /* output token */
					&ret_flags,          /* ret flags */
					&lifetime_rec);      /* time rec */
E 4

		  if (major_status != GSS_S_COMPLETE) {
		    gss_display_status(&new_status,
D 4
				       status,
				       GSS_C_MECH_CODE,
				       GSS_C_NULL_OID,
				       &msg_ctx,
				       &status_string);
E 4
I 4
					status,
					GSS_C_MECH_CODE,
					GSS_C_NULL_OID,
					&msg_ctx,
					&status_string);
E 4
		    printf("[ SPX mutual response fails ... '%s' ]\r\n",
			 status_string.value);
		    auth_send_retry();
		    return;
		  }
		}
		auth_finished(ap, AUTH_USER);
		return;

	default:
		return;
	}
}

	int
spx_status(ap, name, level)
	Authenticator *ap;
	char *name;
	int level;
{

	gss_buffer_desc  fullname_buffer, acl_file_buffer;
	gss_OID          fullname_type;
D 4
        char acl_file[160], fullname[160];
        int major_status, status = 0;
E 4
I 4
	char acl_file[160], fullname[160];
	int major_status, status = 0;
E 4
	struct passwd  *pwd;

D 4
        /*
         * hard code fullname to
         *   "SPX:/C=US/O=Digital/OU=LKG/OU=Sphinx/OU=Users/CN=Kannan Alagappan"
         * and acl_file to "~kannan/.sphinx"
         */
E 4
I 4
	/*
	 * hard code fullname to
	 *   "SPX:/C=US/O=Digital/OU=LKG/OU=Sphinx/OU=Users/CN=Kannan Alagappan"
	 * and acl_file to "~kannan/.sphinx"
	 */
E 4

	pwd = getpwnam(UserNameRequested);
	if (pwd == NULL) {
D 4
          return(AUTH_USER);   /*  not authenticated  */
        }
E 4
I 4
	  return(AUTH_USER);   /*  not authenticated  */
	}
E 4

	strcpy(acl_file, pwd->pw_dir);
	strcat(acl_file, "/.sphinx");
D 4
        acl_file_buffer.value = acl_file;
        acl_file_buffer.length = strlen(acl_file);
E 4
I 4
	acl_file_buffer.value = acl_file;
	acl_file_buffer.length = strlen(acl_file);
E 4

	major_status = gss_display_name(&status,
					src_name,
					&fullname_buffer,
					&fullname_type);

	if (level < AUTH_USER)
		return(level);

D 4
        major_status = gss__check_acl(&status, &fullname_buffer,
                                      &acl_file_buffer);
E 4
I 4
	major_status = gss__check_acl(&status, &fullname_buffer,
					&acl_file_buffer);
E 4

D 4
        if (major_status == GSS_S_COMPLETE) {
E 4
I 4
	if (major_status == GSS_S_COMPLETE) {
E 4
	  strcpy(name, UserNameRequested);
	  return(AUTH_VALID);
D 4
        } else {
           return(AUTH_USER);
        }
E 4
I 4
	} else {
	   return(AUTH_USER);
	}
E 4

}

#define	BUMP(buf, len)		while (*(buf)) {++(buf), --(len);}
#define	ADDC(buf, len, c)	if ((len) > 0) {*(buf)++ = (c); --(len);}

	void
spx_printsub(data, cnt, buf, buflen)
	unsigned char *data, *buf;
	int cnt, buflen;
{
	char lbuf[32];
	register int i;

	buf[buflen-1] = '\0';		/* make sure its NULL terminated */
	buflen -= 1;

	switch(data[3]) {
	case SPX_REJECT:		/* Rejected (reason might follow) */
		strncpy((char *)buf, " REJECT ", buflen);
		goto common;

	case SPX_ACCEPT:		/* Accepted (name might follow) */
		strncpy((char *)buf, " ACCEPT ", buflen);
	common:
		BUMP(buf, buflen);
		if (cnt <= 4)
			break;
		ADDC(buf, buflen, '"');
		for (i = 4; i < cnt; i++)
			ADDC(buf, buflen, data[i]);
		ADDC(buf, buflen, '"');
		ADDC(buf, buflen, '\0');
		break;

	case SPX_AUTH:			/* Authentication data follows */
		strncpy((char *)buf, " AUTH", buflen);
		goto common2;

	default:
		sprintf(lbuf, " %d (unknown)", data[3]);
		strncpy((char *)buf, lbuf, buflen);
	common2:
		BUMP(buf, buflen);
		for (i = 4; i < cnt; i++) {
			sprintf(lbuf, " %d", data[i]);
			strncpy((char *)buf, lbuf, buflen);
			BUMP(buf, buflen);
		}
		break;
	}
}

#endif

#ifdef notdef

prkey(msg, key)
	char *msg;
	unsigned char *key;
{
	register int i;
	printf("%s:", msg);
	for (i = 0; i < 8; i++)
		printf(" %3d", key[i]);
	printf("\r\n");
}
#endif
E 1
