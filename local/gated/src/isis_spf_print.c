/*
 *  isis_spf_print.c,v 1.11 1993/01/07 22:40:03 jch Exp
 */

/* %(Copyright.header) */


#define	INCLUDE_CTYPE
#include "include.h"
#include "isis_includes.h"


static char  transd[]  = "0123456789abcdef";
/* used to translate hex digits for printing */

/* 
 * Format the address in sysid as a printable string in buf.
 */
char * 
spf_print_addr __PF3(buf, char *,
		     sysid, char *,
		     addr_type, enum addr_types)
{
	int i;

	switch(addr_type) {
		case is_id: {
			IS_ID * ispt = (IS_ID *)sysid;
			/* add this to print hex sysids */
			sprintf(buf,"IS:%x-%x-%x-%x-%x-%x:%x",
				ispt->addr[0], ispt->addr[1], ispt->addr[2],
				ispt->addr[3], ispt->addr[4], ispt->addr[5],
				ispt->addr[6]);
#ifdef addr_string
			sprintf(buf,"%c%c%c%c%c%c:%x ",
				ispt->addr[0], ispt->addr[1], ispt->addr[2],
				ispt->addr[3], ispt->addr[4], ispt->addr[5],
				ispt->addr[6]);
			/* get rid of non-printing chars */
			for (i=0; i<=6;i++)
				if (!isprint(buf[i]))
					buf[i]=' ';
#endif
		}
		break;
		case es_id: {
			ES_ID * espt = (ES_ID *)sysid;
			sprintf(buf,"ES:%x-%x-%x-%x-%x-%x",
				espt->addr[0],
				espt->addr[1],
				espt->addr[2],
				espt->addr[3],
				espt->addr[4],
				espt->addr[5]);
		}
		break;
		case addr_pref: {
			ADDR_PREF *prpt = (ADDR_PREF *) sysid;
			sockaddr_un *sa;
			sa = sockbuild_iso(prpt->addr, (prpt->pref_len + 1) >> 1);
			sprintf(buf,"PREF:%A",sa);
		}
		break;
		case inet_net: {
			INET_NET * ipt = (INET_NET *) sysid;
			/* ignore mask for now */
			sprintf(buf,"%d.%d.%d.%d",
				ipt->addr[0],ipt->addr[1],ipt->addr[2],ipt->addr[3]);
		}
		break;
		case area_addr: {
			AREA_ADDR *apt = (AREA_ADDR *) sysid;
			sockaddr_un *sa;
			sa = sockbuild_iso(apt->addr, apt->area_len);
			sprintf(buf,"AREA:%A",sa);
		}
		break;
		default:
			printf("unexpected addr_type %d\n",addr_type);
	}
	return buf;
}


/*
 * %(Copyright)
 * %(Copyright.ISIS)
 */
