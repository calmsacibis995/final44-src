#include "sendmail.h"
#undef NIS /* symbol conflict in nis.h */
#include <rpcsvc/nis.h>
#include <rpcsvc/nislib.h>
#include <nsswitch.h>
#define EN_col(col) zo_data.objdata_u.en_data.en_cols.en_cols_val[(col)].ec_value.ec_value_val
#define DOT_TERMINATED(x) ((x)[strlen(x) - 1] == '.')

bool
hosts_table_ok(domain)
char *domain;
{
	char qbuf[MAXLINE + NIS_MAXNAMELEN];
	nis_result *res = NULL;

	sprintf(qbuf, "hosts.org_dir.%s", domain);
        while (res == NULL || res->status != NIS_SUCCESS) {
                res = nis_lookup(qbuf, FOLLOW_LINKS);

                switch (res->status) {

                case NIS_SUCCESS:
			return TRUE;
                case NIS_TRYAGAIN:
                case NIS_RPCERROR:
                        break;
                default:        /* all other nisplus errors */
                        return (FALSE);
                        break;
                };
                sleep(2);       /* try not overwhelm hosed server */
        }
}


/* conver name to short from e.g estelle.eng 	      => estelle */
/* 				 estelle.eng.sun.com  => estelle */
/* 				 estelle.eng.sun.com. => estelle */
bool
quick_convert(name, shortname, strip_last_dot)
char name[], shortname[];
bool strip_last_dot;
{
	char *p;

	p = strchr(name, '.');
	if (p == NULL) {
		strcpy(shortname, name);
		return TRUE;
	}

	if (p[1]) { /* multi token */
		char *r, *d;
		int len;
		
		r = strchr(&p[1], '.');
		if (r == NULL) {
			d = &p[1];
			len = strlen(d);
		} else {
			d = &p[1];
			len = strlen(d);
			if (strip_last_dot && DOT_TERMINATED(d))
				len--;
		}
		if (!strncasecmp(d, macvalue('m', CurEnv), len)) {
			*p = '\0';
			strcpy(shortname, name);
			*p = '.';
		} else  shortname[0] = '\0';
		return TRUE;
	} else return FALSE;
	
	
}


char *next_word(buf, word)
char buf[];
char **word;
{
	register char *p;
	register char *wd;
	char last_char;

	p = buf;
	while (*p != '\0' && isspace(*p))
		p++;
	wd = p;
	while (*p != '\0' && !isspace(*p))
		p++;
	last_char = *p;
	*p = '\0';
	*word = wd;
	if (last_char) {
		p++;
		while (*p != '\0' && isspace(*p))
			p++;
	}
	return (p);
}

/*
**  GET_COLUMN  -- look up a Column in a line buffer
*/
char *
get_column(line, col, delim, buf)
char line[], buf[];
int col;
char delim;
{
	char *p;
	char *begin, *end;
	int i;
	char delimbuf[3];
	

	if (delim != '\t') {
		delimbuf[0] = delim;
		delimbuf[1] = '\0';
	} else	strcpy(delimbuf, "\t ");
		

	p = line;
	if (*p == 0)
		return NULL; /* line empty */
	if ((*p == delim) && (col == 0))
		return NULL; /* first column empty */

	if (col == 0) {
		begin = line;
		if (delim == '\t') {
			while (*begin && isspace(*begin))
				begin++;
		}
		end = strpbrk(line, delimbuf);
		if (end == NULL) {
			strcpy(buf, begin);
		} else {
			strncpy(buf, begin, end - begin);
			buf[end-begin] = '\0';
		}
			
		return buf;
	}

	begin = line;
	for (i=0; i< col; i++) {
		if ((begin = strpbrk(begin,delimbuf)) == NULL) {
			return NULL;	 /* no such column */
		}
		begin++;
		if (delim == '\t') {
			while (*begin && isspace(*begin))
				begin++;
		}
	}

	
	end = strpbrk(begin, delimbuf);
	if (end == NULL) {
			strcpy(buf, begin);
	} else {
		strncpy(buf, begin, end - begin);
		buf[end-begin] = '\0';
	}
	return buf;
}

#ifdef CHECK_INDIRECT_SELF_REF
ADDRESS *
indirect_self_reference(a, e)
ADDRESS *a;
ENVELOPE *e;
{
	int stat;
        ADDRESS *b;
         
        b = a->q_alias;
        while (b) {
                if (!strcasecmp(a->q_user, b->q_user))
                        break;
                b = b->q_alias;
        }

	if (!b)
		return NULL;

	/* check condition  3 */
	lookup_logname_table(b->q_user, &stat);
	if (stat == EX_NOTFOUND)
		return NULL;

	if (stat == EX_OK)
		return b;

	/* we have a error condition */
	/* temp error, queue it up */
	/* try again later 	   */
 	if (e->e_message == NULL)
		e->e_message = "can not access passwd table";
	b->q_flags |= QQUEUEUP;
	return b;
}
#endif

#ifdef CONTENT_LENGTH
long
content_length(e, m)
	ENVELOPE *e;
	MAILER *m;
{

	int num_eol_chars;
	long content_length;
	
	if (e->e_bodysize < 0)
		return -1;

	content_length = e->e_bodysize;

	/* account for the eol character(s) */
	num_eol_chars = strlen(m->m_eol);
	content_length += (num_eol_chars * e->e_num_line);

	/* account for the ">" character that will be added */
	/* to escape the "From " line			    */
	if (bitnset(M_ESCFROM, m->m_flags))
		content_length += e->e_num_from;

	return(content_length);
}
#endif

#ifdef LOOKUP_MACRO
/*
**  LOOKUP_DATA - lookup value of macro/class
**
*/
#define	DEF_ACTION {1, 0, 0, 0}

#ifndef NSW_SENDMAILVARS_DB
/* this define should be in /usr/include/nsswitch.h */
#define	NSW_SENDMAILVARS_DB "sendmailvars"
#endif
#define	LOOKUP_TIMEOUT	/* we need this only if the time out code in the */
			/* name service e.g nis+ does not work, this can */
			/* be undef once, nis+ fast fail is working	 */
#ifdef LOOKUP_TIMEOUT
static jmp_buf CtxLookUpTimeOut;
static int LookUpTimeOut = 60; /* 60 seconds */
lookuptimeout()
{
	longjmp(CtxLookUpTimeOut, 1);
}
#endif

static struct __nsw_lookup lkp1 = { "nisplus", DEF_ACTION, NULL, NULL};
static struct __nsw_lookup lkp0 = { "files", DEF_ACTION, NULL, &lkp1};
static struct __nsw_switchconfig mailconf_default =
				    { 0, NSW_SENDMAILVARS_DB, 1, &lkp0};
static struct __nsw_lookup *mailconf_nsw = NULL;
lookup_data(search_key, answer_buf, bufsize)
char search_key[];
char answer_buf[];
int  bufsize;
{
	int nserr;
	enum __nsw_parse_err pserr;
	struct __nsw_switchconfig *nsw_conf = NULL;
	struct __nsw_lookup *lk;
	void *handle;


	if (!mailconf_nsw) {
		if (!(nsw_conf =
		    __nsw_getconfig(NSW_SENDMAILVARS_DB, &pserr))) {
			nsw_conf = &mailconf_default;
		}
		mailconf_nsw = nsw_conf->lookups;
	}

	for (lk = mailconf_nsw; lk; lk = lk->next) {
#ifdef LOOKUP_TIMEOUT
		EVENT *ev;
		ev = setevent(LookUpTimeOut, lookuptimeout, 0);
		if (setjmp(CtxLookUpTimeOut) != 0) {
			nserr = __NSW_UNAVAIL;
			answer_buf[0] = '\0';
		/*
			XXX faile siliently for now
			syslog(LOG_CRIT,
		"can't Lookup \"%s\", no response from name service \"%s\"",
			    search_key, lk->service_name);
		*/
			if (__NSW_ACTION(lk, nserr) == __NSW_RETURN)
				return (nserr);
			continue;
		}
#endif
		nserr = __NSW_UNAVAIL;
		if (strcmp(lk->service_name, "nisplus") == 0) {
			nisplus_TableLookUp(&nserr, search_key,
				    answer_buf, &bufsize);
		} else	{
			if (strcmp(lk->service_name, "files") == 0) {
				files_TableLookUp(&nserr, search_key,
				    answer_buf, &bufsize);
			} else	{
				syslog(LOG_CRIT,
			    "can't Lookup data via name service \"%s\"",
					lk->service_name);
			}
		}
#ifdef LOOKUP_TIMEOUT
		clrevent(ev);
#endif
		if (__NSW_ACTION(lk, nserr) == __NSW_RETURN)
				break;
	}
	return (nserr);
}

files_TableLookUp(nserrp, search_key, answer_buf, bufsizep)
int *nserrp;
char search_key[];
char answer_buf[];
int *bufsizep;
{
	extern char *fgetfolded();
	FILE *cf;
	char buf[MAXLINE];

	if ((search_key == NULL) || (answer_buf == NULL) || (*bufsizep <= 0)) {
		*nserrp = -1; /* bad param */
		return;
	}

	answer_buf[0] = '\0';
	cf = fopen(SENDMAIL_MAP_FILE, "r");
	if (cf == NULL)
	{
		*nserrp = __NSW_UNAVAIL;
		return;
	}

	*nserrp = __NSW_NOTFOUND;
	while (fgetfolded(buf, sizeof (buf), cf) != NULL) {
		char *p;
		char last_char;

		p = buf;
		if ((*p == '#') || (*p == ' ') || (*p == '\t'))
			continue; /* skip comment/blank line */
		/* find end of first field */
		while (*p) {
			if ((*p == ' ') || (*p == '\t'))
				break;
			p++;
		}

		last_char = *p;
		*p = '\0';
		if (!strcmp(buf, search_key)) {
			*nserrp = __NSW_SUCCESS;
			if (last_char)
				p++;
			/* strip leading spaces */
			while ((*p == ' ') || (*p == '\t'))
				p++;
			answer_buf[*bufsizep - 1]  = '\0';
			strncpy(answer_buf, p, *bufsizep - 1);
			*bufsizep = strlen(answer_buf) + 1;
			break;
		}
	}
	fclose(cf);
}

nisplus_TableLookUp(nserrp, search_key, answer_buf, bufsizep)
int *nserrp;
char search_key[];
char answer_buf[];
int *bufsizep;
{

	char table_name[MAXNAME];
	int  column_id;

	nis_result *result;
	char qbuf[MAXLINE];
#define EN_len zo_data.objdata_u.en_data.en_cols.en_cols_len
#define EN_col(col) zo_data.objdata_u.en_data.en_cols.en_cols_val[(col)].ec_value.ec_value_val

	if ((search_key == NULL) || (answer_buf == NULL) || (*bufsizep <= 0)) {
		*nserrp = -1; /* bad param */
		return;
	}

	*nserrp = __NSW_UNAVAIL;

	sprintf(table_name, "%s.%s", SENDMAIL_MAP_NISPLUS,
	    nis_local_directory());
	column_id = 1;

	/* construct the query */
	sprintf(qbuf, "[%s=%s],%s", "key", search_key, table_name);

	result = nis_list(qbuf, FOLLOW_LINKS | FOLLOW_PATH, NULL, NULL);
	if (result->status == NIS_SUCCESS) {
		int count;

		if ((count = (result->objects).objects_len) != 1) {
			syslog(LOG_CRIT,
			    "Lookup error, expected 1 entry, got (%d)",
			    count);
		} else {
			if (NIS_RES_OBJECT(result)->EN_len <= column_id) {
				syslog(LOG_CRIT,
			    "Lookup error, no such column (%d)", column_id);
			} else  {
				*nserrp = __NSW_SUCCESS;
				answer_buf[*bufsizep - 1] = '\0';
				strncpy(answer_buf, ((NIS_RES_OBJECT(result))->
				    EN_col(column_id)), *bufsizep - 1);
				/* set the length of the result */
				*bufsizep = strlen(answer_buf) + 1;
			}
		}
	} else {
		*nserrp = __NSW_NOTFOUND;
	}
	nis_freeresult(result);
	return (*nserrp);
}
#endif /* LOOKUP_MACRO */

#ifdef REMOTE_MODE
verify_mail_server(myhostname, remote)
char *myhostname;
bool *remote;
{
	STAB *s;
	MAP *map;
	int stat;
	char *mail_server;

	if (ConfigLevel < 2)
		mail_server = RemoteMboxHost;
	else {
		s = stab("nssmserv", ST_MAP, ST_FIND);

		/* no mailserv table defined, disable remote mode */
		if (s == NULL) {
			*remote = FALSE;
			return;
		}
		map = &s->s_map;

		mail_server = (*map->map_class->map_lookup)(map, myhostname, NULL, &stat);
	}

	/* if there are no mail server or mail_server is myself */
	/* then turn off RemoteMode				 */
	if (!mail_server || (strcasecmp(myhostname, mail_server) == 0))
		*remote = FALSE;
}
#endif /* REMOTE_MODE */

#ifdef SUN_STYLE_MACRO_M
/* this is mainly for backward compatibility in YP env */
initdomain(e)
register ENVELOPE *e;
{
	  /*
	   * Get the domain name from the kernel.
	   * If it does not start with a leading dot, then remove
	   * the first component.  Since leading dots are funny Unix
	   * files, we treat a leading "+" the same as a leading dot.
	   * Finally, force there to be at least one dot in the domain name
	   * (i.e. top-level domains are not allowed, like "com", must be
	   * something like "sun.com").
	   */
	char buf[MAXNAME];
	char *period, *autodomain;
  	
	if (getdomainname(buf, sizeof buf) < 0)
		return;

	if (buf[0] == '+')
		buf[0] = '.';
	period = strchr(buf, '.');
	if (period == NULL)
		autodomain = buf;
	else
		autodomain = newstr(period+1);
	if (strchr(autodomain, '.') == NULL)
		autodomain = newstr(buf);
	define('m', autodomain, e);
	setclass('m', autodomain);
}
#endif


#ifdef MULI_HOME_HOST
# include <netdb.h>
# include <sys/time.h>
# include <arpa/inet.h>
#include <net/if.h>
#include <sys/sockio.h>

/* support multi-homed host */
char **
myhostname(hostbuf, size)
	char hostbuf[];
	int size;
{
	extern struct hostent *gethostbyname();
	extern struct hostent *gethostbyaddr();
	struct hostent *hp;
	static char *nicknames[MAXATOM];
	register char **avp, *thisname;
	int s, n;
        struct ifconf ifc;
        struct ifreq *ifr;
	char interfacebuf[1024];
	struct in_addr inaddr;
	int i;
	extern char *inet_ntoa();

	if (gethostname(hostbuf, size) < 0)
	{
		(void) strcpy(hostbuf, "localhost");
	}
	avp = nicknames;
	*avp = NULL;
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s == -1)
		return (nicknames);

	/* get the list of known IP address from the kernel */
        ifc.ifc_len = sizeof(interfacebuf);
        ifc.ifc_buf = interfacebuf;
	if (ioctl(s, SIOCGIFCONF, (char *)&ifc) < 0)
		return (nicknames);
        ifr = ifc.ifc_req;
	i =0;
	/* scan the list of IP address */
        for (n = ifc.ifc_len/sizeof (struct ifreq); n > 0; n--, ifr++) {
		char thisbuf[256];
		struct in_addr ia;
		
		if (ifr->ifr_addr.sa_family != AF_INET)
			continue;

		/* extract IP address from the list*/
		ia =(((struct sockaddr_in *) (&ifr->ifr_addr))->sin_addr); 

		/* save IP address in text from */
		(void) sprintf(thisbuf, "[%s]", inet_ntoa(
		        ((struct sockaddr_in *)(&ifr->ifr_addr))->sin_addr));

		     
		/* skip "loopback" interface "lo" */
		if (strcmp("lo0", ifr->ifr_name)) {
			inaddr = ((struct sockaddr_in *)(&ifr->ifr_addr))->sin_addr;
			/* lookup name with IP address */
			hp = gethostbyaddr(&inaddr, sizeof(inaddr), AF_INET);
			if (hp == NULL) {
				syslog(LOG_CRIT, "gethostbyaddr() failed"); 
				*avp = NULL;
				return (nicknames);
			}
			/* save its cname */
			if (strcmp(hostbuf, hp->h_name))
				*avp++ = newstr(hp->h_name);

			/* save all it aliases name */
			while (*hp->h_aliases) {
				*avp++ = newstr(*hp->h_aliases);
				hp->h_aliases++;
			}
		}
		thisname = newstr(thisbuf);
		*avp++ = thisname;
	}
	*avp = NULL;
	return (nicknames);
}
#endif


#ifdef EXTENDED_TIMEOUT
struct xtimeout *
mail_timeout(e)
register ENVELOPE *e;

{
	HDR **hp;
	register HDR *h;

        for (hp = &e->e_header; (h = *hp) != NULL; hp = &h->h_link)
        {
                if (strcasecmp("priority", h->h_field) == 0) {
			
			if (strcasecmp("urgent", h->h_value) == 0)
				return(&uTimeOuts);
			if (strcasecmp("non-urgent", h->h_value) == 0)
				return(&tTimeOuts);
		}
        }
	return(&nTimeOuts);
}
#endif


bool
mx_enabled()
{
	static int has_mx = -1;

	if (has_mx == -1)
	{
		bool in_nsswitch_path();

		if (in_nsswitch_path(__NSW_HOSTS_DB, "dns"))
			has_mx = 1;
		else    has_mx = 0;
	}

	return has_mx;
}


struct hostent *
smart_gethostbyname(host)
char *host;
{
	struct hostent *hp;
	bool tried_short_form;
	bool tried_long_form;
	char shortform[MAXNAME];
	char longform[MAXNAME];

	hp =  gethostbyname(host);
	if (hp != NULL)
		return hp;

	if (DOT_TERMINATED(host))
		return hp;

	/* try it with short form,e.g estelle.eng => estelle */
	/* because most YP and /etc/hosts backend does not   */
	/* understand long form  e.g estelle.eng.sun.com     */
	if (quick_convert(host, shortform, TRUE)) {
		if (strcmp(host, shortform)) {
			hp = gethostbyname(shortform);
		}
	}
	if (hp != NULL)
		return hp;

	/* try it with long form,e.g estelle => estelle.eng.sun.com */
	/* because some DNS setup does not understand long form     */
	/* and many old sendmail.cf does not canonified hostname    */
	sprintf(longform, "%s.%s", host,  macvalue('m', CurEnv));
	if (!DOT_TERMINATED(longform))
		strcat(longform, ".");
	hp = gethostbyname(longform);
	return hp;
}

solaris_defaults(e)
register ENVELOPE *e;
{
	char *q;

        /*
         * Set the domain class here, in case it was re-defined in the cf
         */
        if ((q = macvalue('m', e)) != NULL)
                setclass('m', q);

	/* set up default aliases maps */
	if (stab("aliases_files", ST_MAP, ST_FIND) == NULL)
		makemapentry("aliases_files dbm /etc/mail/aliases");
	if (stab("aliases_nisplus", ST_MAP, ST_FIND) == NULL)
		makemapentry("aliases_nisplus nisplus -kalias -vexpansion -d mail_aliases.org_dir");
	if (stab("aliases_nis", ST_MAP, ST_FIND) == NULL)
		makemapentry("aliases_nis nis -d mail.aliases");
	if (stab("aliases", ST_MAP, ST_FIND) == NULL)
		makemapentry("aliases nsswitch aliases");
	if (!switched_aliases_defined)
		setalias("nsswitch:aliases");

	/* set up default logname  maps */
	if (stab("logname_files", ST_MAP, ST_FIND) == NULL)
		makemapentry("logname_files text -m -z: -k0 -v6 /etc/passwd");
	if (stab("logname_nisplus", ST_MAP, ST_FIND) == NULL)
		makemapentry("logname_nisplus nisplus -m -kname -vhome  -d passwd.org_dir");
	if (stab("logname_nis", ST_MAP, ST_FIND) == NULL)
		makemapentry("logname_nis nis -m -d passwd.byname");
	if (stab("logname", ST_MAP, ST_FIND) == NULL)
		makemapentry("logname nsswitch -m passwd");

	if (ConfigLevel >= 2) {
		/* set up default mail server  maps */
		if (stab("mserv_files", ST_MAP, ST_FIND) == NULL)
			makemapentry(
	"mserv_files text -z\t -k0 -v1 /etc/mail/mail_server");
		if (stab("mserv_nisplus", ST_MAP, ST_FIND) == NULL)
			makemapentry(
	"mserv_nisplus nisplus -khost -vmail_server -d mail_server.org_dir");
		if (stab("mserv", ST_MAP, ST_FIND) == NULL)
			makemapentry("mserv nsswitch sendmailvars");
	}
}

lookup_logname_table(name, statp)
char *name;
int  *statp;
{
	static STAB *lgnmap = NULL;

	if (lgnmap == NULL)
		lgnmap = stab("logname", ST_MAP, ST_FIND);
	if (lgnmap == NULL)
		syserr("554 can not find logname map");

	(*lgnmap->s_map.map_class->map_lookup)(&lgnmap->s_map,
                                                name, NULL, statp);

	return;
}


#ifdef REMOTE_MODE
bool
remote_mode()
{
	if (vendor_code != SUN) {
		if (ConfigLevel >= 2)
			return (RewriteRules[5] != NULL);
		else 	return FALSE;
	} else {
		if (!RemoteMode)
			return FALSE;
		if (ConfigLevel >= 2)
			return (RewriteRules[5] != NULL);
		else 	return FALSE;
	}
}

bool
is_implied_local_alias(name)
char *name;
{
	static STAB *aliasmap;
	static char *argvect[2] = {"-s", NULL};
	struct address a;
	ENVELOPE dummy_env;
	register char **pvp;
	char pvpbuf[PSBUFSIZE];
	int stat;
	char *str;
	char ** prescan();

	memset((char *) &dummy_env, 0, sizeof dummy_env);
	clearenvelope(&dummy_env, FALSE);

	/* check to see if it is a local name */
	if (parseaddr(name, &a, RF_COPYNONE, 0, '\0' , &dummy_env) == NULL) 
		return -1; /* unknown */

	if (bitset(QQUEUEUP, a.q_flags))
		return -1; /* unknown */

	if (a.q_mailer != LocalMailer)
		return 0; /* not a local alias */

	/* it is a local name , now we check if it is already qualified*/
	if (strcmp(a.q_user, a.q_paddr))
		return 0; /* not a local alias */
	
	/* it is a non-qualified local name    */
	/*  now we check if it is a local alias*/
	if (aliasmap == NULL)
		aliasmap = stab("alias", ST_MAP, ST_FIND);
	if (aliasmap == NULL)
		return -1; /* unknown */
	str = (*aliasmap->s_map.map_class->map_lookup)(&aliasmap->s_map,
                                                name, argvect, &stat);
	if (!strcmp(str, "UNKNOWN"))
		return -1; /* unknown */

	if (!strcmp(str, "files"))
		return 1;  /* is local alias */
	
	return 0; /* not a local alias */
}

char *
make_explicit_local(name, buf, buflen, e)
char *name;
char *buf;
ENVELOPE *e;
int  buflen;
{
	char *l; /* ptr to local host name; $w */

	/* make name  explicit local */
	l = macvalue('w', e);

	if ((l == NULL) || (*l == '\0')) {
		syserr("$w not defined");
		return(name);
	}

	if ((int) (strlen(l) + strlen(name) + 1) >= buflen) {
		syserr("name buffer overflow");
		return(name);
	}

	strcpy(buf, name);
	strcat(buf, "@");
	strcat(buf, l);
	return buf;
}
#endif
