h02327
s 00008/00007/00966
d D 8.2 95/05/30 20:13:23 dab 6 5
c Code cleanup, use mem*() instead of b*()
e
s 00002/00002/00971
d D 8.1 93/06/04 17:35:29 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00004/00004/00969
d D 5.4 93/05/20 10:51:38 dab 4 3
c Fix all the "#if defined(ENCRYPTION)" lines to just
c be "#ifdef ENCRYPTION", so that unifdef can be used to strip
c out all the encryption code.
e
s 00008/00002/00965
d D 5.3 92/12/18 14:11:14 dab 3 2
c Change ENCRYPT to ENCRYPTION
c Change AUTHENTICATE to AUTHENTICATION
c Latest version of Kerberos V stuff
c Bug fixes
e
s 00302/00121/00665
d D 5.2 91/03/22 13:17:47 dab 2 1
c Upgrade to the latest & greatest authentication/encryption
e
s 00786/00000/00000
d D 5.1 91/02/28 22:01:28 dab 1 0
c date and time created 91/02/28 22:01:28 by dab
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * %sccs.include.redist.c%
 */

#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */

/*
 * Copyright (C) 1990 by the Massachusetts Institute of Technology
 *
 * Export of this software from the United States of America is assumed
 * to require a specific license from the United States Government.
 * It is the responsibility of any person or organization contemplating
 * export to obtain such a license before exporting.
 *
 * WITHIN THAT CONSTRAINT, permission to use, copy, modify, and
 * distribute this software and its documentation for any purpose and
 * without fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation, and that
 * the name of M.I.T. not be used in advertising or publicity pertaining
 * to distribution of the software without specific, written prior
 * permission.  M.I.T. makes no representations about the suitability of
 * this software for any purpose.  It is provided "as is" without express
 * or implied warranty.
 */

D 3
#if	defined(ENCRYPT)
E 3
I 3
D 4
#if	defined(ENCRYPTION)
E 4
I 4
#ifdef	ENCRYPTION
E 4
E 3

#define	ENCRYPT_NAMES
#include <arpa/telnet.h>

#include "encrypt.h"
#include "misc.h"

#ifdef	__STDC__
#include <stdlib.h>
#endif
#ifdef	NO_STRING_H
#include <strings.h>
#else
#include <string.h>
#endif

/*
 * These functions pointers point to the current routines
 * for encrypting and decrypting data.
 */
void	(*encrypt_output) P((unsigned char *, int));
int	(*decrypt_input) P((int));

int encrypt_debug_mode = 0;
static int decrypt_mode = 0;
static int encrypt_mode = 0;
static int encrypt_verbose = 0;
static int autoencrypt = 0;
static int autodecrypt = 0;
static int havesessionkey = 0;
D 2
static int encrypt_mark = 0;
static int decrypt_mark = 0;
E 2
static int Server = 0;
static char *Name = "Noname";

#define	typemask(x)	((x) > 0 ? 1 << ((x)-1) : 0)

D 2
static long i_support_encrypt = typemask(ENCTYPE_KRBDES);
static long i_support_decrypt = typemask(ENCTYPE_KRBDES);
E 2
I 2
static long i_support_encrypt = typemask(ENCTYPE_DES_CFB64)
				| typemask(ENCTYPE_DES_OFB64);
static long i_support_decrypt = typemask(ENCTYPE_DES_CFB64)
				| typemask(ENCTYPE_DES_OFB64);
static long i_wont_support_encrypt = 0;
static long i_wont_support_decrypt = 0;
#define	I_SUPPORT_ENCRYPT	(i_support_encrypt & ~i_wont_support_encrypt)
#define	I_SUPPORT_DECRYPT	(i_support_decrypt & ~i_wont_support_decrypt)

E 2
static long remote_supports_encrypt = 0;
static long remote_supports_decrypt = 0;

static Encryptions encryptions[] = {
D 2
#if	defined(KRBDES_ENCRYPT)
    { "KRBDES",		ENCTYPE_KRBDES,
			krbdes_encrypt,	
			krbdes_decrypt,
			krbdes_init,
			krbdes_start,
			krbdes_is,
			krbdes_reply,
			krbdes_session,
			krbdes_printsub },
E 2
I 2
D 3
#if	defined(DES_ENCRYPT)
E 3
I 3
D 4
#if	defined(DES_ENCRYPTION)
E 4
I 4
#ifdef	DES_ENCRYPTION
E 4
E 3
    { "DES_CFB64",	ENCTYPE_DES_CFB64,
D 6
			cfb64_encrypt,	
E 6
I 6
			cfb64_encrypt,
E 6
			cfb64_decrypt,
			cfb64_init,
			cfb64_start,
			cfb64_is,
			cfb64_reply,
			cfb64_session,
			cfb64_keyid,
			cfb64_printsub },
    { "DES_OFB64",	ENCTYPE_DES_OFB64,
D 6
			ofb64_encrypt,	
E 6
I 6
			ofb64_encrypt,
E 6
			ofb64_decrypt,
			ofb64_init,
			ofb64_start,
			ofb64_is,
			ofb64_reply,
			ofb64_session,
			ofb64_keyid,
			ofb64_printsub },
E 2
D 4
#endif
E 4
I 4
#endif	/* DES_ENCRYPTION */
E 4
    { 0, },
};

static unsigned char str_send[64] = { IAC, SB, TELOPT_ENCRYPT,
D 2
					 ENCRYPT_SUPPORT, };
E 2
I 2
					 ENCRYPT_SUPPORT };
E 2
static unsigned char str_suplen = 0;
D 2
static unsigned char str_start[] = { IAC, SB, TELOPT_ENCRYPT, 0, IAC, SE };
E 2
I 2
static unsigned char str_start[72] = { IAC, SB, TELOPT_ENCRYPT };
E 2
static unsigned char str_end[] = { IAC, SB, TELOPT_ENCRYPT, 0, IAC, SE };

	Encryptions *
findencryption(type)
	int type;
{
	Encryptions *ep = encryptions;

D 2
	if (!(i_support_encrypt & remote_supports_decrypt & typemask(type)))
E 2
I 2
	if (!(I_SUPPORT_ENCRYPT & remote_supports_decrypt & typemask(type)))
E 2
		return(0);
	while (ep->type && ep->type != type)
		++ep;
	return(ep->type ? ep : 0);
}

	Encryptions *
finddecryption(type)
	int type;
{
	Encryptions *ep = encryptions;

D 2
	if (!(i_support_decrypt & remote_supports_encrypt & typemask(type)))
E 2
I 2
	if (!(I_SUPPORT_DECRYPT & remote_supports_encrypt & typemask(type)))
E 2
		return(0);
	while (ep->type && ep->type != type)
		++ep;
	return(ep->type ? ep : 0);
}

I 2
#define	MAXKEYLEN 64

static struct key_info {
	unsigned char keyid[MAXKEYLEN];
	int keylen;
	int dir;
	int *modep;
	Encryptions *(*getcrypt)();
} ki[2] = {
	{ { 0 }, 0, DIR_ENCRYPT, &encrypt_mode, findencryption },
	{ { 0 }, 0, DIR_DECRYPT, &decrypt_mode, finddecryption },
};

E 2
	void
encrypt_init(name, server)
	char *name;
	int server;
{
	Encryptions *ep = encryptions;

	Name = name;
	Server = server;
	i_support_encrypt = i_support_decrypt = 0;
	remote_supports_encrypt = remote_supports_decrypt = 0;
	encrypt_mode = 0;
	decrypt_mode = 0;
	encrypt_output = 0;
	decrypt_input = 0;
#ifdef notdef
	encrypt_verbose = !server;
#endif

	str_suplen = 4;

	while (ep->type) {
		if (encrypt_debug_mode)
			printf(">>>%s: I will support %s\r\n",
				Name, ENCTYPE_NAME(ep->type));
		i_support_encrypt |= typemask(ep->type);
		i_support_decrypt |= typemask(ep->type);
D 2
		if ((str_send[str_suplen++] = ep->type) == IAC)
			str_send[str_suplen++] = IAC;
E 2
I 2
		if ((i_wont_support_decrypt & typemask(ep->type)) == 0)
			if ((str_send[str_suplen++] = ep->type) == IAC)
				str_send[str_suplen++] = IAC;
E 2
		if (ep->init)
			(*ep->init)(Server);
		++ep;
	}
	str_send[str_suplen++] = IAC;
	str_send[str_suplen++] = SE;
}

	void
encrypt_list_types()
{
	Encryptions *ep = encryptions;

	printf("Valid encryption types:\n");
	while (ep->type) {
D 2
		printf("\t%s\n\n", ENCTYPE_NAME(ep->type));
E 2
I 2
		printf("\t%s (%d)\r\n", ENCTYPE_NAME(ep->type), ep->type);
E 2
		++ep;
	}
}

	int
EncryptEnable(type, mode)
	char *type, *mode;
{
	if (isprefix(type, "help") || isprefix(type, "?")) {
		printf("Usage: encrypt enable <type> [input|output]\n");
		encrypt_list_types();
		return(0);
	}
	if (EncryptType(type, mode))
		return(EncryptStart(mode));
	return(0);
}

	int
I 2
EncryptDisable(type, mode)
	char *type, *mode;
{
	register Encryptions *ep;
	int ret = 0;

	if (isprefix(type, "help") || isprefix(type, "?")) {
		printf("Usage: encrypt disable <type> [input|output]\n");
		encrypt_list_types();
	} else if ((ep = (Encryptions *)genget(type, encryptions,
						sizeof(Encryptions))) == 0) {
		printf("%s: invalid encryption type\n", type);
	} else if (Ambiguous(ep)) {
		printf("Ambiguous type '%s'\n", type);
	} else {
		if ((mode == 0) || (isprefix(mode, "input") ? 1 : 0)) {
			if (decrypt_mode == ep->type)
				EncryptStopInput();
			i_wont_support_decrypt |= typemask(ep->type);
			ret = 1;
		}
		if ((mode == 0) || (isprefix(mode, "output"))) {
			if (encrypt_mode == ep->type)
				EncryptStopOutput();
			i_wont_support_encrypt |= typemask(ep->type);
			ret = 1;
		}
		if (ret == 0)
			printf("%s: invalid encryption mode\n", mode);
	}
	return(ret);
}

	int
E 2
EncryptType(type, mode)
	char *type;
	char *mode;
{
	register Encryptions *ep;
I 2
	int ret = 0;
E 2

	if (isprefix(type, "help") || isprefix(type, "?")) {
		printf("Usage: encrypt type <type> [input|output]\n");
		encrypt_list_types();
D 2
		return(0);
	}

	ep = (Encryptions *)genget(type, encryptions, sizeof(Encryptions));

	if (ep == 0) {
E 2
I 2
	} else if ((ep = (Encryptions *)genget(type, encryptions,
						sizeof(Encryptions))) == 0) {
E 2
		printf("%s: invalid encryption type\n", type);
D 2
		return(0);
	}
	if (Ambiguous(ep)) {
E 2
I 2
	} else if (Ambiguous(ep)) {
E 2
		printf("Ambiguous type '%s'\n", type);
D 2
		return(0);
	}

	if (mode) {
		if (isprefix(mode, "input"))
E 2
I 2
	} else {
		if ((mode == 0) || isprefix(mode, "input")) {
E 2
			decrypt_mode = ep->type;
D 2
		else if (isprefix(mode, "output"))
E 2
I 2
			i_wont_support_decrypt &= ~typemask(ep->type);
			ret = 1;
		}
		if ((mode == 0) || isprefix(mode, "output")) {
E 2
			encrypt_mode = ep->type;
D 2
		else {
			printf("%s: invalid encryption mode\n", mode);
			return(0);
E 2
I 2
			i_wont_support_encrypt &= ~typemask(ep->type);
			ret = 1;
E 2
		}
D 2
	} else
		decrypt_mode = encrypt_mode = ep->type;
	return(1);
E 2
I 2
		if (ret == 0)
			printf("%s: invalid encryption mode\n", mode);
	}
	return(ret);
E 2
}

	int
EncryptStart(mode)
	char *mode;
{
	register int ret = 0;
	if (mode) {
		if (isprefix(mode, "input"))
			return(EncryptStartInput());
		if (isprefix(mode, "output"))
			return(EncryptStartOutput());
		if (isprefix(mode, "help") || isprefix(mode, "?")) {
			printf("Usage: encrypt start [input|output]\n");
			return(0);
		}
		printf("%s: invalid encryption mode 'encrypt start ?' for help\n", mode);
		return(0);
	}
	ret += EncryptStartInput();
	ret += EncryptStartOutput();
	return(ret);
}

	int
EncryptStartInput()
{
	if (decrypt_mode) {
		encrypt_send_request_start();
		return(1);
	}
	printf("No previous decryption mode, decryption not enabled\r\n");
	return(0);
}

	int
EncryptStartOutput()
{
	if (encrypt_mode) {
		encrypt_start_output(encrypt_mode);
		return(1);
	}
	printf("No previous encryption mode, encryption not enabled\r\n");
	return(0);
}

	int
EncryptStop(mode)
	char *mode;
{
	int ret = 0;
	if (mode) {
		if (isprefix(mode, "input"))
			return(EncryptStopInput());
		if (isprefix(mode, "output"))
			return(EncryptStopOutput());
		if (isprefix(mode, "help") || isprefix(mode, "?")) {
			printf("Usage: encrypt stop [input|output]\n");
			return(0);
		}
		printf("%s: invalid encryption mode 'encrypt stop ?' for help\n", mode);
		return(0);
	}
	ret += EncryptStopInput();
	ret += EncryptStopOutput();
	return(ret);
}

	int
EncryptStopInput()
{
	encrypt_send_request_end();
	return(1);
}

	int
EncryptStopOutput()
{
	encrypt_send_end();
	return(1);
}

	void
encrypt_display()
{
	if (encrypt_output)
		printf("Currently encrypting output with %s\r\n",
			ENCTYPE_NAME(encrypt_mode));
	if (decrypt_input)
		printf("Currently decrypting input with %s\r\n",
			ENCTYPE_NAME(decrypt_mode));
}

	int
EncryptStatus()
{
	if (encrypt_output)
		printf("Currently encrypting output with %s\r\n",
			ENCTYPE_NAME(encrypt_mode));
	else if (encrypt_mode) {
		printf("Currently output is clear text.\r\n");
		printf("Last encryption mode was %s\r\n",
			ENCTYPE_NAME(encrypt_mode));
	}
	if (decrypt_input) {
		printf("Currently decrypting input with %s\r\n",
			ENCTYPE_NAME(decrypt_mode));
	} else if (decrypt_mode) {
		printf("Currently input is clear text.\r\n");
		printf("Last decryption mode was %s\r\n",
			ENCTYPE_NAME(decrypt_mode));
	}
	return 1;
}

	void
encrypt_send_support()
{
	if (str_suplen) {
		/*
		 * If the user has requested that decryption start
		 * immediatly, then send a "REQUEST START" before
		 * we negotiate the type.
		 */
		if (!Server && autodecrypt)
			encrypt_send_request_start();
		net_write(str_send, str_suplen);
		printsub('>', &str_send[2], str_suplen - 2);
		str_suplen = 0;
	}
}

	int
D 2
EncryptTogDebug()
E 2
I 2
EncryptDebug(on)
	int on;
E 2
{
D 2
	encrypt_debug_mode ^= 1;
E 2
I 2
	if (on < 0)
		encrypt_debug_mode ^= 1;
	else
		encrypt_debug_mode = on;
E 2
	printf("Encryption debugging %s\r\n",
		encrypt_debug_mode ? "enabled" : "disabled");
	return(1);
}

	int
D 2
EncryptTogVerbose()
E 2
I 2
EncryptVerbose(on)
	int on;
E 2
{
D 2
	encrypt_verbose ^= 1;
E 2
I 2
	if (on < 0)
		encrypt_verbose ^= 1;
	else
		encrypt_verbose = on;
E 2
	printf("Encryption %s verbose\r\n",
		encrypt_verbose ? "is" : "is not");
	return(1);
}

	int
D 2
EncryptTogAuto()
E 2
I 2
EncryptAutoEnc(on)
	int on;
E 2
{
D 2
	autoencrypt ^= 1;
	autodecrypt ^= 1;
	printf("Automatic encryption of data is %s\r\n",
E 2
I 2
	encrypt_auto(on);
	printf("Automatic encryption of output is %s\r\n",
E 2
		autoencrypt ? "enabled" : "disabled");
	return(1);
}

I 2
	int
EncryptAutoDec(on)
	int on;
{
	decrypt_auto(on);
	printf("Automatic decryption of input is %s\r\n",
		autodecrypt ? "enabled" : "disabled");
	return(1);
}
E 2

/*
 * Called when ENCRYPT SUPPORT is received.
 */
	void
encrypt_support(typelist, cnt)
	unsigned char *typelist;
	int cnt;
{
	register int type, use_type = 0;
	Encryptions *ep;

	/*
	 * Forget anything the other side has previously told us.
	 */
	remote_supports_decrypt = 0;

	while (cnt-- > 0) {
		type = *typelist++;
		if (encrypt_debug_mode)
			printf(">>>%s: He is supporting %s (%d)\r\n",
				Name,
				ENCTYPE_NAME(type), type);
		if ((type < ENCTYPE_CNT) &&
D 2
		    (i_support_encrypt & typemask(type))) {
E 2
I 2
		    (I_SUPPORT_ENCRYPT & typemask(type))) {
E 2
			remote_supports_decrypt |= typemask(type);
			if (use_type == 0)
				use_type = type;
		}
	}
	if (use_type) {
		ep = findencryption(use_type);
		if (!ep)
			return;
		type = ep->start ? (*ep->start)(DIR_ENCRYPT, Server) : 0;
		if (encrypt_debug_mode)
			printf(">>>%s: (*ep->start)() returned %d\r\n",
					Name, type);
		if (type < 0)
			return;
D 2
		encrypt_mode = type;
E 2
I 2
		encrypt_mode = use_type;
E 2
		if (type == 0)
			encrypt_start_output(use_type);
	}
}

	void
encrypt_is(data, cnt)
	unsigned char *data;
	int cnt;
{
	Encryptions *ep;
	register int type, ret;

	if (--cnt < 0)
		return;
	type = *data++;
	if (type < ENCTYPE_CNT)
		remote_supports_encrypt |= typemask(type);
	if (!(ep = finddecryption(type))) {
		if (encrypt_debug_mode)
			printf(">>>%s: Can't find type %s (%d) for initial negotiation\r\n",
				Name,
D 2
				ENCTYPE_NAME(data[-1]), data[1]);
E 2
I 2
				ENCTYPE_NAME_OK(type)
					? ENCTYPE_NAME(type) : "(unknown)",
				type);
E 2
		return;
	}
	if (!ep->is) {
		if (encrypt_debug_mode)
			printf(">>>%s: No initial negotiation needed for type %s (%d)\r\n",
				Name,
D 2
				ENCTYPE_NAME(type), type);
E 2
I 2
				ENCTYPE_NAME_OK(type)
					? ENCTYPE_NAME(type) : "(unknown)",
				type);
E 2
		ret = 0;
	} else {
		ret = (*ep->is)(data, cnt);
D 2
/*@*/		if (encrypt_debug_mode)
/*@*/			printf("(*ep->is)(%x, %d) returned %s(%d)\n", data, cnt,
/*@*/				(ret < 0) ? "FAIL " :
/*@*/				(ret == 0) ? "SUCCESS " : "MORE_TO_DO ", ret);
E 2
I 2
		if (encrypt_debug_mode)
			printf("(*ep->is)(%x, %d) returned %s(%d)\n", data, cnt,
				(ret < 0) ? "FAIL " :
				(ret == 0) ? "SUCCESS " : "MORE_TO_DO ", ret);
E 2
	}
	if (ret < 0) {
		autodecrypt = 0;
	} else {
		decrypt_mode = type;
		if (ret == 0 && autodecrypt)
			encrypt_send_request_start();
	}
}

	void
encrypt_reply(data, cnt)
	unsigned char *data;
	int cnt;
{
	Encryptions *ep;
	register int ret, type;

	if (--cnt < 0)
		return;
	type = *data++;
	if (!(ep = findencryption(type))) {
		if (encrypt_debug_mode)
			printf(">>>%s: Can't find type %s (%d) for initial negotiation\r\n",
				Name,
D 2
				ENCTYPE_NAME(data[-1]), data[1]);
E 2
I 2
				ENCTYPE_NAME_OK(type)
					? ENCTYPE_NAME(type) : "(unknown)",
				type);
E 2
		return;
	}
	if (!ep->reply) {
		if (encrypt_debug_mode)
			printf(">>>%s: No initial negotiation needed for type %s (%d)\r\n",
				Name,
D 2
				ENCTYPE_NAME(data[-1]), data[1]);
E 2
I 2
				ENCTYPE_NAME_OK(type)
					? ENCTYPE_NAME(type) : "(unknown)",
				type);
E 2
		ret = 0;
	} else {
		ret = (*ep->reply)(data, cnt);
D 2
/*@*/		if (encrypt_debug_mode)
/*@*/			printf("(*ep->reply)(%x, %d) returned %s(%d)\n",
/*@*/				data, cnt,
/*@*/				(ret < 0) ? "FAIL " :
/*@*/				(ret == 0) ? "SUCCESS " : "MORE_TO_DO ", ret);
E 2
I 2
		if (encrypt_debug_mode)
			printf("(*ep->reply)(%x, %d) returned %s(%d)\n",
				data, cnt,
				(ret < 0) ? "FAIL " :
				(ret == 0) ? "SUCCESS " : "MORE_TO_DO ", ret);
E 2
	}
	if (encrypt_debug_mode)
		printf(">>>%s: encrypt_reply returned %d\n", Name, ret);
	if (ret < 0) {
		autoencrypt = 0;
	} else {
		encrypt_mode = type;
		if (ret == 0 && autoencrypt)
			encrypt_start_output(type);
	}
}

/*
 * Called when a ENCRYPT START command is received.
 */
	void
D 2
encrypt_start()
E 2
I 2
encrypt_start(data, cnt)
	unsigned char *data;
	int cnt;
E 2
{
	Encryptions *ep;

	if (!decrypt_mode) {
		/*
		 * Something is wrong.  We should not get a START
		 * command without having already picked our
		 * decryption scheme.  Send a REQUEST-END to
		 * attempt to clear the channel...
		 */
		printf("%s: Warning, Cannot decrypt input stream!!!\r\n", Name);
		encrypt_send_request_end();
		return;
	}

	if (ep = finddecryption(decrypt_mode)) {
		decrypt_input = ep->input;
		if (encrypt_verbose)
			printf("[ Input is now decrypted with type %s ]\r\n",
				ENCTYPE_NAME(decrypt_mode));
		if (encrypt_debug_mode)
			printf(">>>%s: Start to decrypt input with type %s\r\n",
				Name, ENCTYPE_NAME(decrypt_mode));
	} else {
		printf("%s: Warning, Cannot decrypt type %s (%d)!!!\r\n",
D 2
				Name, ENCTYPE_NAME(decrypt_mode), decrypt_mode);
E 2
I 2
				Name,
				ENCTYPE_NAME_OK(decrypt_mode)
					? ENCTYPE_NAME(decrypt_mode)
					: "(unknown)",
				decrypt_mode);
E 2
		encrypt_send_request_end();
	}
}

	void
encrypt_session_key(key, server)
	Session_Key *key;
	int server;
{
	Encryptions *ep = encryptions;

	havesessionkey = 1;

	while (ep->type) {
		if (ep->session)
			(*ep->session)(key, server);
I 3
#ifdef notdef
		if (!encrypt_output && autoencrypt && !server)
			encrypt_start_output(ep->type);
		if (!decrypt_input && autodecrypt && !server)
			encrypt_send_request_start();
#endif
E 3
D 2
		if (!encrypt_output && autoencrypt && !server)
			encrypt_start_output(ep->type);
		if (!decrypt_input && autodecrypt && !server)
			encrypt_send_request_start();
E 2
		++ep;
	}
}

/*
 * Called when ENCRYPT END is received.
 */
	void
encrypt_end()
{
	decrypt_input = 0;
	if (encrypt_debug_mode)
		printf(">>>%s: Input is back to clear text\r\n", Name);
	if (encrypt_verbose)
		printf("[ Input is now clear text ]\r\n");
}

/*
 * Called when ENCRYPT REQUEST-END is received.
 */
	void
encrypt_request_end()
{
	encrypt_send_end();
}

/*
 * Called when ENCRYPT REQUEST-START is received.  If we receive
 * this before a type is picked, then that indicates that the
 * other side wants us to start encrypting data as soon as we
D 6
 * can. 
E 6
I 6
 * can.
E 6
 */
	void
D 2
encrypt_request_start()
E 2
I 2
encrypt_request_start(data, cnt)
	unsigned char *data;
	int cnt;
E 2
{
D 2
	if (!encrypt_mode && Server) {
		autoencrypt = 1;
E 2
I 2
	if (encrypt_mode == 0)  {
		if (Server)
			autoencrypt = 1;
E 2
		return;
	}
	encrypt_start_output(encrypt_mode);
}

I 2
static unsigned char str_keyid[(MAXKEYLEN*2)+5] = { IAC, SB, TELOPT_ENCRYPT };

encrypt_enc_keyid(keyid, len)
	unsigned char *keyid;
	int len;
{
	encrypt_keyid(&ki[1], keyid, len);
}

encrypt_dec_keyid(keyid, len)
	unsigned char *keyid;
	int len;
{
	encrypt_keyid(&ki[0], keyid, len);
}

encrypt_keyid(kp, keyid, len)
	struct key_info *kp;
	unsigned char *keyid;
	int len;
{
	Encryptions *ep;
	unsigned char *strp, *cp;
	int dir = kp->dir;
	register int ret = 0;

	if (!(ep = (*kp->getcrypt)(*kp->modep))) {
		if (len == 0)
			return;
		kp->keylen = 0;
	} else if (len == 0) {
		/*
		 * Empty option, indicates a failure.
		 */
		if (kp->keylen == 0)
			return;
		kp->keylen = 0;
		if (ep->keyid)
			(void)(*ep->keyid)(dir, kp->keyid, &kp->keylen);

D 6
	} else if ((len != kp->keylen) || (bcmp(keyid, kp->keyid, len) != 0)) {
E 6
I 6
	} else if ((len != kp->keylen) ||
		   (memcmp(keyid, kp->keyid, len) != 0)) {
E 6
		/*
		 * Length or contents are different
		 */
		kp->keylen = len;
D 6
		bcopy(keyid, kp->keyid, len);
E 6
I 6
		memmove(kp->keyid, keyid, len);
E 6
		if (ep->keyid)
			(void)(*ep->keyid)(dir, kp->keyid, &kp->keylen);
	} else {
		if (ep->keyid)
			ret = (*ep->keyid)(dir, kp->keyid, &kp->keylen);
		if ((ret == 0) && (dir == DIR_ENCRYPT) && autoencrypt)
			encrypt_start_output(*kp->modep);
		return;
	}

	encrypt_send_keyid(dir, kp->keyid, kp->keylen, 0);
}

E 2
	void
D 2
encrypt_auto()
E 2
I 2
encrypt_send_keyid(dir, keyid, keylen, saveit)
	int dir;
	unsigned char *keyid;
	int keylen;
	int saveit;
E 2
{
D 2
	autoencrypt = 1;
	autodecrypt = 1;
E 2
I 2
	unsigned char *strp;

	str_keyid[3] = (dir == DIR_ENCRYPT)
			? ENCRYPT_ENC_KEYID : ENCRYPT_DEC_KEYID;
	if (saveit) {
		struct key_info *kp = &ki[(dir == DIR_ENCRYPT) ? 0 : 1];
D 6
		bcopy(keyid, kp->keyid, keylen);
E 6
I 6
		memmove(kp->keyid, keyid, keylen);
E 6
		kp->keylen = keylen;
	}

	for (strp = &str_keyid[4]; keylen > 0; --keylen) {
		if ((*strp++ = *keyid++) == IAC)
			*strp++ = IAC;
	}
	*strp++ = IAC;
	*strp++ = SE;
	net_write(str_keyid, strp - str_keyid);
	printsub('>', &str_keyid[2], strp - str_keyid - 2);
E 2
}

	void
I 2
encrypt_auto(on)
	int on;
{
	if (on < 0)
		autoencrypt ^= 1;
	else
		autoencrypt = on ? 1 : 0;
}

	void
decrypt_auto(on)
	int on;
{
	if (on < 0)
		autodecrypt ^= 1;
	else
		autodecrypt = on ? 1 : 0;
}

	void
E 2
encrypt_start_output(type)
	int type;
{
	Encryptions *ep;
D 2
	register int ret;
E 2
I 2
	register unsigned char *p;
	register int i;
E 2

	if (!(ep = findencryption(type))) {
		if (encrypt_debug_mode) {
D 2
			printf(">>>%s: Marking type %s for later encryption use\r\n",
E 2
I 2
			printf(">>>%s: Can't encrypt with type %s (%d)\r\n",
E 2
				Name,
D 2
				ENCTYPE_NAME(type));
E 2
I 2
				ENCTYPE_NAME_OK(type)
					? ENCTYPE_NAME(type) : "(unknown)",
				type);
E 2
		}
D 2
		encrypt_mark |= typemask(type);
E 2
		return;
	}
	if (ep->start) {
D 2
		ret = (*ep->start)(DIR_ENCRYPT, Server);
		if (ret) {
			if (encrypt_debug_mode) {
				if (ret < 0)
					printf(">>>%s: Start failed for %s\r\n",
						Name, ENCTYPE_NAME(type));
				else
					printf(">>>%s: Start: initial negotiation in progress%s\r\n",
						Name, ENCTYPE_NAME(type));
			}

			return;
E 2
I 2
		i = (*ep->start)(DIR_ENCRYPT, Server);
		if (encrypt_debug_mode) {
			printf(">>>%s: Encrypt start: %s (%d) %s\r\n",
D 6
				Name, 
E 6
I 6
				Name,
E 6
				(i < 0) ? "failed" :
					"initial negotiation in progress",
				i, ENCTYPE_NAME(type));
E 2
		}
I 2
		if (i)
			return;
E 2
	}
D 2
	str_start[3] = ENCRYPT_START;
	net_write(str_start, sizeof(str_start));
E 2
I 2
	p = str_start + 3;
	*p++ = ENCRYPT_START;
	for (i = 0; i < ki[0].keylen; ++i) {
		if ((*p++ = ki[0].keyid[i]) == IAC)
			*p++ = IAC;
	}
	*p++ = IAC;
	*p++ = SE;
	net_write(str_start, p - str_start);
E 2
	net_encrypt();
D 2
	printsub('>', &str_start[2], sizeof(str_start) - 2);
E 2
I 2
	printsub('>', &str_start[2], p - &str_start[2]);
E 2
	/*
	 * If we are already encrypting in some mode, then
	 * encrypt the ring (which includes our request) in
	 * the old mode, mark it all as "clear text" and then
	 * switch to the new mode.
	 */
	encrypt_output = ep->output;
	encrypt_mode = type;
	if (encrypt_debug_mode)
		printf(">>>%s: Started to encrypt output with type %s\r\n",
			Name, ENCTYPE_NAME(type));
	if (encrypt_verbose)
		printf("[ Output is now encrypted with type %s ]\r\n",
			ENCTYPE_NAME(type));
}

	void
encrypt_send_end()
{
	if (!encrypt_output)
		return;

	str_end[3] = ENCRYPT_END;
	net_write(str_end, sizeof(str_end));
	net_encrypt();
	printsub('>', &str_end[2], sizeof(str_end) - 2);
	/*
	 * Encrypt the output buffer now because it will not be done by
	 * netflush...
	 */
	encrypt_output = 0;
	if (encrypt_debug_mode)
		printf(">>>%s: Output is back to clear text\r\n", Name);
	if (encrypt_verbose)
		printf("[ Output is now clear text ]\r\n");
}

	void
encrypt_send_request_start()
{
D 2
#ifdef notdef
	Encryptions *ep;
E 2
I 2
	register unsigned char *p;
	register int i;
E 2

D 2
	if (!(ep = findencryption(type))) {
		if (encrypt_debug_mode) {
			printf(">>>%s: Marking type %s for later decryption use\r\n",
				Name,
				ENCTYPE_NAME(type));
		}
		decrypt_mark |= typemask(type);
		return;
E 2
I 2
	p = &str_start[3];
	*p++ = ENCRYPT_REQSTART;
	for (i = 0; i < ki[1].keylen; ++i) {
		if ((*p++ = ki[1].keyid[i]) == IAC)
			*p++ = IAC;
E 2
	}
D 2

	if (ep->start && (*ep->start)(DIR_DECRYPT, Server)) {
		if (encrypt_debug_mode) {
			printf(">>>%s: Request failed for %s\r\n",
				Name,
				ENCTYPE_NAME(type));
		}
		return;
	}
#endif

	str_start[3] = ENCRYPT_REQSTART;
	net_write(str_start, sizeof(str_start));
	printsub('>', &str_start[2], sizeof(str_start) - 2);
E 2
I 2
	*p++ = IAC;
	*p++ = SE;
	net_write(str_start, p - str_start);
	printsub('>', &str_start[2], p - &str_start[2]);
E 2
	if (encrypt_debug_mode)
		printf(">>>%s: Request input to be encrypted\r\n", Name);
}

	void
encrypt_send_request_end()
{
	str_end[3] = ENCRYPT_REQEND;
	net_write(str_end, sizeof(str_end));
	printsub('>', &str_end[2], sizeof(str_end) - 2);

	if (encrypt_debug_mode)
		printf(">>>%s: Request input to be clear text\r\n", Name);
}

	void
encrypt_wait()
{
	register int encrypt, decrypt;
	if (encrypt_debug_mode)
		printf(">>>%s: in encrypt_wait\r\n", Name);
D 2
	if (!havesessionkey || !(i_support_encrypt & remote_supports_decrypt))
E 2
I 2
	if (!havesessionkey || !(I_SUPPORT_ENCRYPT & remote_supports_decrypt))
E 2
		return;
	while (autoencrypt && !encrypt_output)
		if (telnet_spin())
			return;
}

	void
encrypt_debug(mode)
	int mode;
{
	encrypt_debug_mode = mode;
}

	void
encrypt_gen_printsub(data, cnt, buf, buflen)
	unsigned char *data, *buf;
	int cnt, buflen;
{
	char tbuf[16], *cp;

	cnt -= 2;
	data += 2;
	buf[buflen-1] = '\0';
	buf[buflen-2] = '*';
	buflen -= 2;;
	for (; cnt > 0; cnt--, data++) {
		sprintf(tbuf, " %d", *data);
		for (cp = tbuf; *cp && buflen > 0; --buflen)
			*buf++ = *cp++;
		if (buflen <= 0)
			return;
	}
	*buf = '\0';
}

	void
encrypt_printsub(data, cnt, buf, buflen)
	unsigned char *data, *buf;
	int cnt, buflen;
{
	Encryptions *ep;
	register int type = data[1];

	for (ep = encryptions; ep->type && ep->type != type; ep++)
		;

	if (ep->printsub)
		(*ep->printsub)(data, cnt, buf, buflen);
	else
		encrypt_gen_printsub(data, cnt, buf, buflen);
}
D 4
#endif
E 4
I 4
#endif	/* ENCRYPTION */
E 4
E 1
