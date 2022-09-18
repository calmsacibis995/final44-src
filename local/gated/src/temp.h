
/**/
#define	SLSP_CONFIG_HELLO	1
#define	SLSP_CONFIG_DEAD	2
#define	SLSP_CONFIG_COST	3
#define	SLSP_CONFIG_PRIORITY	4
#define	SLSP_CONFIG_MAX		5

PROTOTYPE(slsp_config_free,
	  extern void,
	  (config_entry *));
PROTOTYPE(slsp_parse_instance_alloc,
	  extern instance *,
	  (sockaddr_un *,
	   sockaddr_un *));
PROTOTYPE(slsp_parse_instance_check,
	  extern int,
	  (instance *,
	   char *));
PROTOTYPE(slsp_parse_gateway_alloc,
	  extern gateway *,
	  (sockaddr_un *));
PROTOTYPE(slsp_parse_gateway_check,
	  extern int,
	  (gateway *,
	   parse_error));

#define	SLSP_LIMIT_COST			xx, yy
#define	SLSP_LIMIT_HELLOINTERVAL	xx, yy
#define	SLSP_LIMIT_ROUTERDEADINTERVAL	xx, yy
#define	SLSP_LIMIT_PRIORITY		xx, yy

/**/

void
slsp_config_free __PF1(cp, config_entry *)
{
    /* Nothing is allocated so nothing to free */
    return;
}


void
slsp_config __PF1(instance, instance,
		  ifap, if_addr)
{
    config_list *list = config_resolv(instance->policy,
				      ifap,
				      SLSP_CONFIG_MAX);

    if (list) {
	int type = SLSP_CONFIG_MAX;

	XXX - allocate an interface structure;
	XXX - Copy in defaults;

	while (--type) {
	    register config_entry *cp = list[type];

	    switch (type) {
	    case SLSP_CONFIG_HELLO:
		blah->blap_hello = (type) cp->config_data;
		break;

	    case SLSP_CONFIG_DEAD:
		blah->blap_dead = (type) cp->config_data;
		break;

	    case SLSP_CONFIG_COST:
		blah->blap_cost = (type) cp->config_data;
		break;

	    case SLSP_CONFIG_PRIORITY:
		blah->blap_priority = (type) cp->config_data;
		break;
	    }
	}

	config_resolv_free(list, SLSP_CONFIG_MAX);
    }
}


...
slsp_cleanup()
{
    adv_free_list(instance->policy);
}
