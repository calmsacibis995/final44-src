/*
 *  $Header: /vol/src/devel/gated/master/gated/src/isis_mib_tables.c,v 1.6.2.1 1995/01/23 12:39:45 jch Exp $
 */

/*
**	isis_mib_tables.c
**
**	This file contains tables storing the isis mib and prodedures manipulating
**	the data.
**
**
**	John Chu <jychu@watson.ibm.com>
**
*/

/************************
*			*
*    Include Files 	*
*			*
************************/


#include "include.h"

#if	defined(PROTO_SNMP)

#include <fcntl.h>
#include <nlist.h>

#include <net/route.h>

#include "isis_includes.h"
#include "isis_test.h"


#include "isis_mib.h"


/************************
*			*
*   External References *
*			*
************************/

extern Boolean l1HippityBit;
extern Boolean l2HippityBit;


/************************
*			*
*   Local definitions   *
*			*
************************/

typedef struct sockaddr SockAddr;
typedef struct sockaddr_in SockAddrIn;
typedef struct sockaddr_iso SockAddrIso;
typedef struct radix_node_head RadixNodeHead;
typedef struct radix_node RadixNode;
typedef struct radix_mask RadixMask;
typedef struct rtentry RouteTreeEntry;


#define KMEM	"/dev/kmem"


/************************
*			*
*   Memory Allocation   *
*			*
************************/

/* Maximum Number of Area Addresses, per ISO/IEC 10589:1992 (E), 7.1.5 */
int	maximumAreaAddresses = MAXAREAADDRESSES;   /* at least 3, setable by sys mgmnt */


static int kernel_fd=-1;		/* kernel file descriptor */


/* The IS-IS MIB all-instances table */
IsisMibTable 	isisMibTable;



/************************
*			*
*      Procedures	*
*			*
************************/


/*
**	Init Short or Long Octet String
*/
void initOctetString(poctetstring, maxsize)
LongOctetString	*poctetstring;
int		maxsize;
{
    poctetstring->len = 0;
    poctetstring->maxlen = maxsize;		/* per isis mib var defs */

} /* end of initOctetString() */


/*
**	Copy an octet string
*/
int copyOctetString(poctetstring, from, fromlen)
LongOctetString	*poctetstring;
unsigned char 	*from;
int		fromlen;
{
    int		lencopied;

    lencopied = ((unsigned short)fromlen <= poctetstring->maxlen)? fromlen :
								   poctetstring->maxlen;
    bcopy(from, poctetstring->contents, lencopied);

    return(poctetstring->len = lencopied);


} /* end of copyOctetString() */


/*
**	Extend an octet string
*/
int extendOctetString(poctetstring, from, fromlen)
LongOctetString	*poctetstring;
unsigned char 	*from;
int		fromlen;
{
    int		lencopied;

    lencopied = ((unsigned short)fromlen <= poctetstring->maxlen - poctetstring->len)? 
					fromlen :
					poctetstring->maxlen - poctetstring->len;

    bcopy(from, poctetstring->contents+poctetstring->len, lencopied);

    return(poctetstring->len += lencopied);


} /* end of extendOctetString() */


/*
**	Compare two octet strings by their byte values
*/
int cmpOctetString(postr1, postr2)
LongOctetString	*postr1;
LongOctetString	*postr2;
{
    int		i;
    int		cmplen;		/* length to be compared */

    if ((cmplen = postr1->len) > postr2->len) cmplen = postr2->len;

    for (i = 0; i < cmplen; ++i) {
  	if (postr1->contents[i] > postr2->contents[i]) return(1);
  	else if (postr1->contents[i] < postr2->contents[i]) return(-1);
    }

    if (postr1->len > postr2->len) return(1);
    else if (postr1->len < postr2->len) return(-1);
    else return(0);


} /* end of cmpOctetString() */




/*
**	Init the isis mib tables cold; per isis mib definition
*/
void initIsisMibCold()
{
    int		i,j,k,l;
    IsisMibEntry		*pMibEntry;
    IsisSysEntry	 	*pSysEntry;
    IsisManAreaAddrTable 	*pManAreaAddrTable;
    IsisManAreaAddrEntry 	*pManAreaAddrEntry;
    IsisAreaAddrTable 	 	*pAreaAddrTable;
    IsisAreaAddrEntry 	 	*pAreaAddrEntry;
    IsisSysProtSuppTable	*pSysProtSuppTable;
    IsisSysProtSuppEntry	*pSysProtSuppEntry;
    IsisL2SummAddrTable		*pL2SummAddrTable;
    IsisL2SummAddrEntry		*pL2SummAddrEntry;
    IsisAuthAreaRecPwdTable 	*pAuthAreaRecPwdTable;
    IsisAuthAreaRecPwdEntry 	*pAuthAreaRecPwdEntry;
    IsisAuthDomainRecPwdTable 	*pAuthDomainRecPwdTable;
    IsisAuthDomainRecPwdEntry 	*pAuthDomainRecPwdEntry;
    IsisPartRepTable		*pPartRepTable;
    IsisPartRepEntry		*pPartRepEntry;
    IsisPartAreaAddrTable	*pPartAreaAddrTable;
    IsisPartAreaAddrEntry	*pPartAreaAddrEntry;
    IsisVirtAdjTable		*pVirtAdjTable;
    IsisVirtAdjEntry		*pVirtAdjEntry;
    IsisCircTable		*pCircTable;
    IsisCircEntry		*pCircEntry;
    IsisISAdjTable		*pISAdjTable;
    IsisISAdjEntry	 	*pISAdjEntry;
    IsisISAdjAreaAddrTable	*pISAdjAreaAddrTable;
    IsisISAdjAreaAddrEntry	*pISAdjAreaAddrEntry;
    IsisISAdjIPAddrTable   	*pISAdjIPAddrTable;
    IsisISAdjIPAddrEntry   	*pISAdjIPAddrEntry;
    IsisISAdjProtSuppTable 	*pISAdjProtSuppTable;
    IsisISAdjProtSuppEntry 	*pISAdjProtSuppEntry;
    IsisCircAuthRecPwdTable 	*pCircAuthRecPwdTable;
    IsisCircAuthRecPwdEntry 	*pCircAuthRecPwdEntry;
    IsisESAdjTable	        *pESAdjTable;
    IsisESAdjEntry	        *pESAdjEntry;
    IsisRATable	       		*pRATable;
    IsisRAEntry	       		*pRAEntry;
    IsisIPRATable	       	*pIPRATable;
    IsisIPRAEntry	       	*pIPRAEntry;
    IsisCircISTable		*pCircISTable;
    IsisCircISEntry		*pCircISEntry;

    /* Zero out all tables of all instances */
    bzero(&isisMibTable, sizeof(IsisMibTable));		


    /* Initialize per instance entry */
    queueInit(&isisMibTable, MIBSYSTEM, MAXISISSYSINSTANCES);

    for (i = 0; i < MAXISISSYSINSTANCES; ++i) {	/* for all possible isis instances */
	pMibEntry = &isisMibTable.isisMibEntry[i];

	/* System Entry */
	pSysEntry = &pMibEntry->isisSysEntry;

	/* Octet strings */
	initOctetString(&pSysEntry->isisSysVersion,MAXOCTETSTRINGSIZESHORT);
	initOctetString(&pSysEntry->isisSysID, 8);
	initOctetString(&pSysEntry->isisSysAuthAreaTransPwd, 254);
	initOctetString(&pSysEntry->isisSysAuthDomainTransPwd, 254);

	/* Default valuse */
        pSysEntry->isisSysMaxPathSplits = 2;
        pSysEntry->isisSysMinLSPTransInt = 5;
        pSysEntry->isisSysMaxLSPGenInt = 900;
        pSysEntry->isisSysMinBroadLSPTransInt = 33;
        pSysEntry->isisSysCompSNPInt = 10;
        pSysEntry->isisSysOrigL1LSPBuffSize = 1492;
        pSysEntry->isisSysMaxAreaAddresses = 3;
        pSysEntry->isisSysMinLSPGenInt = 30;
        pSysEntry->isisSysPollESHelloRate = 50;
        pSysEntry->isisSysPartSNPInt = 2;
        pSysEntry->isisSysWaitTime = 60;
        pSysEntry->isisSysDRISISHelloTimer = 1;
        pSysEntry->isisSysOrigL2LSPBuffSize = 1492;

	/* State variables */
       	pSysEntry->isisSysInstance = i + 1;
        pSysEntry->isisSysExistState = 1;	/* off */
        pSysEntry->isisSysOperState = 1;	/* off */
        pSysEntry->isisSysL1State = 1;	/* off */
        pSysEntry->isisSysL2State = 1;	/* off */


   	/* The Level 1 Manual Area Address Table */
    	pManAreaAddrTable = &pSysEntry->isisManAreaAddrTable;
        queueInit(pManAreaAddrTable, MIBMANAREAADDR, MAXAREAADDRESSES);

	for (j = 0; j < MAXAREAADDRESSES; ++j) {
	    
    	    pManAreaAddrEntry = &pManAreaAddrTable->isisManAreaAddrEntry[j];

	    /* Octet strings */
	    initOctetString(&pManAreaAddrEntry->isisManAreaAddr, 20);

	    /* State variables */
	    pManAreaAddrEntry->isisManAreaAddrSysInstance = i + 1;
	    pManAreaAddrEntry->isisManAreaAddrExistState = 1;
							/* off, at least one on */

  	} /* end of for all possible manual area addresses */


	/* The Level 1 Area Address Table */
    	pAreaAddrTable = &pSysEntry->isisAreaAddrTable;
        queueInit(pAreaAddrTable, MIBAREAADDR, MAXAREAADDRESSES);

	for (j = 0; j < MAXAREAADDRESSES; ++j) {
    	    pAreaAddrEntry = &pAreaAddrTable->isisAreaAddrEntry[j];

	    /* Octet strings */
	    initOctetString(&pAreaAddrEntry->isisAreaAddr, 20);

	    /* State variables */
	    pAreaAddrEntry->isisAreaAddrSysInstance = i + 1;


  	} /* end of for all possible area addresses */


	/* Supported protocol table */
        pSysProtSuppTable = &pMibEntry->isisSysProtSuppTable;
     	queueInit(pSysProtSuppTable, MIBPROTSUPP, MAXPROTSUPPPERINSTANCE);

	for (j = 0; j < MAXPROTSUPPPERINSTANCE; ++j) {
	    pSysProtSuppEntry = &pSysProtSuppTable->isisSysProtSuppEntry[j];

	    pSysProtSuppEntry->isisSysProtSuppSysInstance = i + 1;
	    pSysProtSuppEntry->isisSysProtSuppExistState = 1;      	/* off */

	} /* end of all possible protocol supported entries */


	/* Level 2 summary address table */
	pL2SummAddrTable = &pMibEntry->isisL2SummAddrTable;
     	queueInit(pL2SummAddrTable, MIBL2SUMMADDR, MAXL2SUMMADDRPERINSTANCE);
	for (j = 0; j < MAXL2SUMMADDRPERINSTANCE; ++j) {
	    pL2SummAddrEntry = &pL2SummAddrTable->isisL2SummAddrEntry[j];

	    pL2SummAddrEntry->isisL2SummAddrSysInstance = i + 1;
	    pL2SummAddrEntry->isisL2SummAddrExistState = 2;		/* on */
	    pL2SummAddrEntry->isisL2SummAddrOperState = 1;		/* off */
	    pL2SummAddrEntry->isisL2SummAddrDefaultMetric = 20;

	} /* end of for all possible L2 summary address entries */


	/* Authentication area received password table */
	pAuthAreaRecPwdTable = &pMibEntry->isisAuthAreaRecPwdTable;
     	queueInit(pAuthAreaRecPwdTable, MIBAREARECPWD, MAXAUTHAREARECPWDPERINSTANCE);
	for (j = 0; j < MAXAUTHAREARECPWDPERINSTANCE; ++j) {
	    pAuthAreaRecPwdEntry = &pAuthAreaRecPwdTable->isisAuthAreaRecPwdEntry[j];

	    pAuthAreaRecPwdEntry->isisAuthAreaRecPwdSysInstance = i + 1;
	    initOctetString(&pAuthAreaRecPwdEntry->isisAuthAreaRecPwd, 254);
	    pAuthAreaRecPwdEntry->isisAuthAreaRecPwdExistState = 2;	/* on */

	} /* end of for all possible area received password entries */


	/* Authentication domain received password table */
	pAuthDomainRecPwdTable = &pMibEntry->isisAuthDomainRecPwdTable;
     	queueInit(pAuthDomainRecPwdTable, MIBDOMAINRECPWD, MAXAUTHDOMAINRECPWDPERINSTANCE);
	for (j = 0; j < MAXAUTHDOMAINRECPWDPERINSTANCE; ++j) {
	    pAuthDomainRecPwdEntry = &pAuthDomainRecPwdTable->isisAuthDomainRecPwdEntry[j];

	    pAuthDomainRecPwdEntry->isisAuthDomainRecPwdSysInstance = i + 1;
	    initOctetString(&pAuthDomainRecPwdEntry->isisAuthDomainRecPwd, 254);
	    pAuthDomainRecPwdEntry->isisAuthDomainRecPwdExistState = 2;  	/* on */

	} /* end of for all possible domain received password entries */


	/* Partition repair table */
	pPartRepTable = &pMibEntry->isisPartRepTable;
     	queueInit(pPartRepTable, MIBPARTREP, MAXPARTREPPERINSTANCE);
	for (j = 0; j < MAXPARTREPPERINSTANCE; ++j) {
	    pPartRepEntry = &pPartRepTable->isisPartRepEntry[j];

	    pPartRepEntry->isisPartRepSysInstance = i + 1;
	    pPartRepEntry->isisPartRepMaxVirtAdj = 2;
	    initOctetString(&pPartRepEntry->isisPartRepDesL2IS, 8);

	} /* end of for all possible partition repair entries */


	/* Partition area address table */
	pPartAreaAddrTable = &pMibEntry->isisPartAreaAddrTable;
     	queueInit(pPartAreaAddrTable, MIBPARTAREAADDR, MAXPARTAREAADDRPERINSTANCE);
	for (j = 0; j < MAXPARTAREAADDRPERINSTANCE; ++j) {
	    pPartAreaAddrEntry = &pPartAreaAddrTable->isisPartAreaAddrEntry[j];

	    pPartAreaAddrEntry->isisPartAreaAddrSysInstance = i + 1;
	    initOctetString(&pPartAreaAddrEntry->isisPartAreaAddr, 20);

	} /* end of for all possible partition area address entries */


	/* Partition virtual adjacency table */
	pVirtAdjTable = &pMibEntry->isisVirtAdjTable;
     	queueInit(pVirtAdjTable, MIBVIRTADJ, MAXVIRTADJPERINSTANCE);
	for (j = 0; j < MAXVIRTADJPERINSTANCE; ++j) {
	    pVirtAdjEntry = &pVirtAdjTable->isisVirtAdjEntry[j];

	    pVirtAdjEntry->isisVirtAdjSysInstance = i + 1;
	    pVirtAdjEntry->isisVirtAdjIndex = j + 1;
	    initOctetString(&pVirtAdjEntry->isisVirtAdjNET, 20);

	} /* end of for all possible virtual adj entries */


	/* Circuit Table */
	pCircTable = &pMibEntry->isisCircTable;
     	queueInit(pCircTable, MIBCIRCUIT, MAXCIRCSPERINSTANCE);

	for (j = 0; j < MAXCIRCSPERINSTANCE; ++j) {
	    pCircEntry = &pCircTable->isisCircEntry[j];
	    
	    /* Octet strings */
	    initOctetString(&pCircEntry->isisCircL1CircID, 9);
	    initOctetString(&pCircEntry->isisCircL1DesIS, 8);
	    initOctetString(&pCircEntry->isisCircL2CircID, 9);
	    initOctetString(&pCircEntry->isisCircL2DesIS, 8);
	    initOctetString(&pCircEntry->isisCircPtToPtCircID, 9);
	    initOctetString(&pCircEntry->isisCircAuthTransPwd, 254);

	    /* State variables */
	    pCircEntry->isisCircSysInstance = i + 1;
	    pCircEntry->isisCircIndex = j + 1;
	    pCircEntry->isisCircOperState = 1;			/* off */
	    pCircEntry->isisCircExistState = 2;			/* on */

	    /* Default values */
	    pCircEntry->isisCircISISHelloTimer = 3;
    	    pCircEntry->isisCircL1DefaultMetric = 20;
	    pCircEntry->isisCircL1DelayMetric = 0;
	    pCircEntry->isisCircL1ExpenseMetric = 0;
	    pCircEntry->isisCircL1ErrorMetric = 0;
	    pCircEntry->isisCircL2DefaultMetric = 20;
	    pCircEntry->isisCircL2DelayMetric = 0;
	    pCircEntry->isisCircL2ExpenseMetric = 0;
	    pCircEntry->isisCircL2ErrorMetric = 0;
	    pCircEntry->isisCircManL2Only = 1;			/* false */
	    pCircEntry->isisCircL1ISPriority = 64;
	    pCircEntry->isisCircL2ISPriority = 64;
	    pCircEntry->isisCircDACallDefMetInc = 0;
	    pCircEntry->isisCircDACallDelMetInc = 0;
	    pCircEntry->isisCircDACallErrMetInc = 0;
	    pCircEntry->isisCircDACallExpMetInc = 0;	    

	    /* Circuit IS Entry */
	    pCircISEntry = &pCircEntry->isisCircISEntry;
	    pCircISEntry->isisCircISExistState = 2;			/* on */
	    pCircISEntry->isisCircISOperState = 1;			/* off */
	    pCircISEntry->isisCircISHoldTimerMult = 3;
	    pCircISEntry->isisCircISConfTimer = 10;
	    pCircISEntry->isisCircISSuggESConfTimer = 600;
	    pCircISEntry->isisCircISRedHoldTime = 600;
	    pCircISEntry->isisCircISMCAddr = 1;


	    /* Circuit receive password table */
	    pCircAuthRecPwdTable = &pCircEntry->isisCircAuthRecPwdTable;
	    queueInit(pCircAuthRecPwdTable, MIBCIRCAUTHRECPWD, MAXCIRCAUTHRECPWDPERCIRC);
	    for (k = 0; k < MAXCIRCAUTHRECPWDPERCIRC; ++k) {
		pCircAuthRecPwdEntry = &pCircAuthRecPwdTable->isisCircAuthRecPwdEntry[k];

	  	pCircAuthRecPwdEntry->isisCircAuthRecPwdSysInstance = i + 1;
	  	pCircAuthRecPwdEntry->isisCircAuthRecPwdCircIndex = j + 1;
	    	initOctetString(&pCircAuthRecPwdEntry->isisCircAuthRecPwd, 254);
	  	pCircAuthRecPwdEntry->isisCircAuthRecPwdExistState = 2; 	/* on */

	    } /* end of for all possible CircAuthRecPwd entries */


	    /* IS Adjacency Table */
	    pISAdjTable = &pCircEntry->isisISAdjTable;
	    queueInit(pISAdjTable, MIBISADJ, MAXISADJPERCIRC);
	    
	    for (k = 0; k < MAXISADJPERCIRC; ++k) {
		pISAdjEntry = &pISAdjTable->isisISAdjEntry[k];

		/* Octet strings */
		initOctetString(&pISAdjEntry->isisISAdjNeighSNPAAddress, 20);
	        initOctetString(&pISAdjEntry->isisISAdjNeighSysID, 9);		

		/* State variables */
		pISAdjEntry->isisISAdjSysInstance = i + 1;
		pISAdjEntry->isisISAdjCircIndex = j + 1;
		pISAdjEntry->isisISAdjIndex = k + 1;
		pISAdjEntry->isisISAdjState = 4;		/* down */


		/* IS Adjacency Area Address Table */
		pISAdjAreaAddrTable = &pISAdjEntry->isisISAdjAreaAddrTable;
		queueInit(pISAdjAreaAddrTable, MIBISADJAREAADDR, MAXAREAADDRESSESPERISADJ);

		for (l = 0; l < MAXAREAADDRESSESPERISADJ; ++l) {
		    pISAdjAreaAddrEntry = &pISAdjAreaAddrTable->isisISAdjAreaAddrEntry[l];
		
		    /* Octet strings */
		    initOctetString(&pISAdjAreaAddrEntry->isisISAdjAreaAddress, 20);

		    /* State variables */
		    pISAdjAreaAddrEntry->isisISAdjAreaAddrSysInstance = i + 1;
		    pISAdjAreaAddrEntry->isisISAdjAreaAddrCircIndex = j + 1;
		    pISAdjAreaAddrEntry->isisISAdjAreaAddrAdjIndex = k + 1;


		} /* end of for all possible IS adj area addresses */


		/* IS adj IP address table */
		pISAdjIPAddrTable = &pISAdjEntry->isisISAdjIPAddrTable;
		queueInit(pISAdjIPAddrTable, MIBISADJIPADDR, MAXISADJIPADDRPERISADJ);

		for (l = 0; l < MAXISADJIPADDRPERISADJ; ++l) {
		    pISAdjIPAddrEntry = &pISAdjIPAddrTable->isisISAdjIPAddrEntry[l];

		    /* State variables */
		    pISAdjIPAddrEntry->isisISAdjIPAddrSysInstance = i + 1;
		    pISAdjIPAddrEntry->isisISAdjIPAddrCircIndex = j + 1;
		    pISAdjIPAddrEntry->isisISAdjIPAddrAdjIndex = k + 1;


		} /* end of for all possible entries */

		/* IS adj protocol supported table */
		pISAdjProtSuppTable = &pISAdjEntry->isisISAdjProtSuppTable;
		queueInit(pISAdjProtSuppTable, MIBISADJPROTSUPP, MAXISADJPROTSUPPPERISADJ);

		for (l = 0; l < MAXISADJPROTSUPPPERISADJ; ++l) {
		    pISAdjProtSuppEntry = &pISAdjProtSuppTable->isisISAdjProtSuppEntry[l];
		    /* State variables */
		    pISAdjProtSuppEntry->isisISAdjProtSuppSysInstance = i + 1;
		    pISAdjProtSuppEntry->isisISAdjProtSuppCircIndex = j + 1;
		    pISAdjProtSuppEntry->isisISAdjProtSuppAdjIndex = k + 1;

		} /* end of for all possible entries */

	    } /* end of for all possible IS adjacencies */


	    /* ES adjacency table */
	    pESAdjTable = &pCircEntry->isisESAdjTable;
	    queueInit(pESAdjTable, MIBESADJ, MAXESADJPERCIRC);
	    for (k = 0; k < MAXESADJPERCIRC; ++k) {
		pESAdjEntry = &pESAdjTable->isisESAdjEntry[k];

		pESAdjEntry->isisESAdjSysInstance = i + 1;
		pESAdjEntry->isisESAdjCircIndex = j + 1;
		pESAdjEntry->isisESAdjAdjIndex = k + 1;
		pESAdjEntry->isisESAdjState = 2;		/* up */
		initOctetString(&pESAdjEntry->isisESAdjNeighSNPAAddress, 20);
		pESAdjEntry->isisESAdjExistState = 2;		/* on */
	        initOctetString(&pESAdjEntry->isisESAdjESID, 8);		

	    } /* end of for all possible ES adj entries */


	    /* Reachable address table */
	    pRATable = &pCircEntry->isisRATable;
	    queueInit(pRATable, MIBRA, MAXRAPERCIRC);
	    for (k = 0; k < MAXRAPERCIRC; ++k) {
		pRAEntry = &pRATable->isisRAEntry[k];

		pRAEntry->isisRASysInstance = i + 1;
		pRAEntry->isisRACircIndex = j + 1;
		pRAEntry->isisRAIndex = k + 1;
		pRAEntry->isisRAExistState = 2;			/* on */
		pRAEntry->isisRAOperState = 1;
	        initOctetString(&pRAEntry->isisRAAddrPrefix, 21);
		pRAEntry->isisRAType = 1;			/* manual */
		pRAEntry->isisRADefMetric = 20;
		pRAEntry->isisRADelMetric = 0;
		pRAEntry->isisRAExpMetric = 0;
		pRAEntry->isisRAErrMetric = 0;
		pRAEntry->isisRADefMetricType = 1;		/* internal */
		pRAEntry->isisRADelMetricType = 1;		/* internal */
		pRAEntry->isisRAExpMetricType = 1;		/* internal */
		pRAEntry->isisRAErrMetricType = 1;		/* internal */
	        initOctetString(&pRAEntry->isisRASNPAAddress, 20);
	        initOctetString(&pRAEntry->isisRASNPAMask, 21);
	        initOctetString(&pRAEntry->isisRASNPAPrefix, 21);

	    } /* end of for all possible ra entries */


	    /* IP reachable address table */
	    pIPRATable = &pCircEntry->isisIPRATable;
	    queueInit(pIPRATable, MIBIPRA, MAXIPRAPERCIRC);
	    for (k = 0; k < MAXIPRAPERCIRC; ++k) {
		pIPRAEntry = &pIPRATable->isisIPRAEntry[k];

		pIPRAEntry->isisIPRASysInstance = i + 1;
		pIPRAEntry->isisIPRACircIndex = j + 1;
		pIPRAEntry->isisIPRAIndex = k + 1;
		pIPRAEntry->isisIPRAExistState = 2;		/* on */
		pIPRAEntry->isisIPRAOperState = 1;		/* off */
		pIPRAEntry->isisIPRADefMetric = 20;
		pIPRAEntry->isisIPRADelMetric = 0;
		pIPRAEntry->isisIPRAExpMetric = 0;
		pIPRAEntry->isisIPRAErrMetric = 0;
		pIPRAEntry->isisIPRADefMetricType = 1;		/* internal */
		pIPRAEntry->isisIPRADelMetricType = 1;		/* internal */
		pIPRAEntry->isisIPRAExpMetricType = 1;		/* internal */
		pIPRAEntry->isisIPRAErrMetricType = 1;		/* internal */
	        initOctetString(&pIPRAEntry->isisIPRASNPAAddress, 20);

	    } /* end of for all possible IP ra entries */

	} /* end of for all possible circuits */

    } /* end of for all possible instances */



    /* Initialize non-per-instance tables */



} /* end of initIsisMibCold() */


/*
**	Init the isis mib tables cool; for the isis systems running
*/
int initIsisMibCool()
{
    int		nSystems=1;		/* one isis system now */
    int		i;
    IsisMibEntry	*pMibEntry;
    IsisSysEntry	*pSysEntry;

    for (i = 0; i < nSystems; ++i) {
        /* Get a new IS system-wide mib entry */
        if ((pMibEntry = (IsisMibEntry *)queueNew(&isisMibTable)) == 
							(IsisMibEntry *)NULL) {
	    trace_log_tf(isis_trace_options,
			 0,
			 LOG_ERR,
			 ("initIsisMibCool: cannot allocate sys entry"));
	    return(-1);
        }

        pSysEntry = &pMibEntry->isisSysEntry;


        /* Fill the system entry */
						/* Sys Instance has been assigned */
        pSysEntry->isisSysExistState = 2;	/* valid for an IS-IS system */


        /* Add the system-wide mib entry to its table */
        if (queueAdd(&isisMibTable, pMibEntry)) {
	    trace_log_tf(isis_trace_options,
			 0,
			 LOG_ERR,
			 ("initIsisMibCool: cannot add sys entry"));
       	    return(-1);
        }

    } /* end of for all isis systems running */


    return(0);

} /* end of initIsisMibCool() */




/*
**	Init the isis mib tables warm; per the isis system running
*/
int 
initIsisMibWarm __PF1(initial_isis_config, int)
{
    int			i,j,k;
    IsisMibEntry	*pMibEntry;
    IsisSysEntry	*pSysEntry;
    IsisManAreaAddrTable *pManAreaAddrTable;
    IsisManAreaAddrEntry *pManAreaAddrEntry;
    IsisAreaAddrTable 	*pAreaAddrTable;
    IsisAreaAddrEntry 	*pAreaAddrEntry;
    IsisSysProtSuppTable *pProtSuppTable;
    IsisSysProtSuppEntry *pProtSuppEntry;
    IsisCircTable	*pCircTable;
    IsisCircEntry	*pCircEntry;    
    CircuitEntry	*pcirc;		/* to ckt control block def'ed in isis.h */
    IsisISAdjTable	*pISAdjTable;
    IsisISAdjEntry	*pISAdjEntry;
    IsisISAdjAreaAddrTable	*pISAdjAreaAddrTable;
    IsisISAdjAreaAddrEntry	*pISAdjAreaAddrEntry;


    kmeminit();

    /* Get the only IS system-wide mib entry */
    if ((pMibEntry = (IsisMibEntry *)locateEntry(&isisMibTable, 1)) == 
							(IsisMibEntry *)NULL) {
        trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("initIsisMibWarm: cannot locate sys entry"));
	return(-1);
    }

    pSysEntry = &pMibEntry->isisSysEntry;


    /* Fill the system entry */
						/* Sys Instance has been assigned */
    						/* existState on */

    pSysEntry->isisSysVersion.contents[0] = Version;	/* in isis_base.h */
    pSysEntry->isisSysVersion.len = 1;

    if (systemType == L1IS) pSysEntry->isisSysType = 1;
    else if (systemType == L2IS) pSysEntry->isisSysType = 2;
    else pSysEntry->isisSysType = 0;

    copyOctetString(&pSysEntry->isisSysID, systemID, 6); 

/* 	Integer         isisSysMaxPathSplits; */

    pSysEntry->isisSysMinLSPTransInt = minLSPXmitInterval;

    pSysEntry->isisSysMaxLSPGenInt = maxLSPGenInterval;

    pSysEntry->isisSysMinBroadLSPTransInt = minBLSPXmitInterval; 

    pSysEntry->isisSysCompSNPInt = completeSNPInterval;

    pSysEntry->isisSysOrigL1LSPBuffSize = origL1LSPBufSize;

    pSysEntry->isisSysMaxAreaAddresses = MaximumAreaAddresses;

    pSysEntry->isisSysMinLSPGenInt = minLSPGenInterval;

    pSysEntry->isisSysPollESHelloRate = sysPollESHelloRate;

    pSysEntry->isisSysPartSNPInt = partialSNPInterval;

    pSysEntry->isisSysWaitTime = waitingTime;

    pSysEntry->isisSysDRISISHelloTimer = sysDRIIHInterval;

    pSysEntry->isisSysOperState = 2;			/* set it on */

    if (l1HippityBit == True) pSysEntry->isisSysL1State = 3;   	/* wait */
    else if (L1LSP) pSysEntry->isisSysL1State = 2;		/* on   */
    else pSysEntry->isisSysL1State = 1;				/* off  */

    pSysEntry->isisSysCorrLSPs = isisCounters.corruptLSPDetected;

    pSysEntry->isisSysLSPL1DbaseOloads = isisCounters.l1LSPOverload;

    pSysEntry->isisSysManAddrDropFromAreas = isisCounters.manualAreaDropped;

    pSysEntry->isisSysAttemptToExMaxSeqNums = isisCounters.exceedSeqNum;

    pSysEntry->isisSysSeqNumSkips = isisCounters.seqNumSkipped;

    pSysEntry->isisSysOwnLSPPurges = isisCounters.purgeOwnLSP;

/*
        Counter         isisSysIDFieldLenMismatches;
        Counter         isisSysMaxAreaAddrMismatches;
*/

    pSysEntry->isisSysOrigL2LSPBuffSize = origL2LSPBufSize;

    if (l2HippityBit == True) pSysEntry->isisSysL2State = 3;   	/* wait */
    else if (L2LSP) pSysEntry->isisSysL2State = 2;		/* on   */
    else pSysEntry->isisSysL2State = 1;				/* off  */

    pSysEntry->isisSysLSPL2DbaseOloads = isisCounters.l2LSPOverload;

/*
        LongOctetString isisSysAuthAreaTransPwd;
	LongOctetString isisSysAuthDomainTransPwd;
        Counter         isisSysAuthFails;
*/


    pManAreaAddrTable = &pSysEntry->isisManAreaAddrTable;
    /* Fill the manual area address table */
    if (initial_isis_config) { 
    /* STEVE XXX - fix this to deal with reconfigs */
    for (i = 0; i < MAXAREAADDRESSES && i < systemAreaAddrs.count; ++i) {
	AreaAddr	*pAreaAddr;

        if ((pManAreaAddrEntry = (IsisManAreaAddrEntry *)queueNew(pManAreaAddrTable)) ==
							  (IsisManAreaAddrEntry *)NULL) {
            trace_log_tf(isis_trace_options,
			 0,
			 LOG_ERR,
			 ("initIsisMibWarm: cannot alloc ManAreaAddr entry"));
 	    break;
        }

/*	Integer		isisManAreaAddrSysInstance; */

	pAreaAddr = retrieveAreaAddr(systemAreaAddrs.areaAddr[i]);
        copyOctetString(&pManAreaAddrEntry->isisManAreaAddr, 
			pAreaAddr->addr, pAreaAddr->len     );

    
      	pManAreaAddrEntry->isisManAreaAddrExistState = 2;

        if (queueAdd(pManAreaAddrTable, pManAreaAddrEntry)) {
            trace_log_tf(isis_trace_options,
			 0,
			 LOG_ERR,
			 ("initIsisMibWarm: cannot add ManAreaAddr entry"));
	    return(-1);
        }

    }

    /* Level 1 area address table */
    pAreaAddrTable = &pSysEntry->isisAreaAddrTable;
    /* To be updated by Level 1 LSP received later */

    } 	/* initial_isis_config */


    /* The System Protocol Supported table */
    pProtSuppTable = &pMibEntry->isisSysProtSuppTable;
    if ((pProtSuppEntry = (IsisSysProtSuppEntry *)queueNew(pProtSuppTable)) ==
							(IsisSysProtSuppEntry *)NULL) {
        trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("initIsisMibWarm: cannot alloc SysProtSupp entry"));
	return(-1);

    }

/*	Integer		isisSysProtSuppSysInstance; */

    pProtSuppEntry->isisSysProtSuppProtocol = ProtoSupportedCode;  /* in isis_puds.h */
    pProtSuppEntry->isisSysProtSuppExistState = 2;	/* set it on */

    if (queueAdd(pProtSuppTable, pProtSuppEntry)) {
        trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("initIsisMibWarm: cannot add SysProtSupp entry"));
	return(-1);
    }


    /* The L2 Summary Address table */

    /* The L1 Area Receive Password table */

    /* The L2 Domain Receive Password Table */

    /* The Partition Repair table */

    /* The Partition Area Address table */

    /* The Virtual Adjacency table */


    /* The Circuit table */
    pCircTable = &pMibEntry->isisCircTable;
    /* Fill the circuit table */
    for (i = 0; i < MAXCIRCSPERINSTANCE; ++i) {
	if ((pcirc = circuitList[i]) == NULL) continue;
        /* Locate circuit entry from the circuit table */
        if ((pCircEntry = (IsisCircEntry *)locateEntry(pCircTable, 
						       pcirc->localId)) == 
							(IsisCircEntry *)NULL) {

  	    continue;	/* STEVE XXX - silently ignore this? */
        }    


/*
	Integer                isisCircSysInstance;
	Integer                isisCircIndex;
*/
	pCircEntry->isisCircIfIndex = pcirc->kernindex;

	pCircEntry->isisCircOperState = (pcirc->up)? 2 : 1;

/*      isisCircExistState		has been assigned in isis_set_circuit() */

        switch (pcirc->circuitType) {
	case Broadcast: pCircEntry->isisCircType = 1; break;
	case Pt2Pt: 	pCircEntry->isisCircType = 2; break;
       	default: 	pCircEntry->isisCircType = 0; break;
        }

	pCircEntry->isisCircISISHelloTimer = pcirc->ISIShelloInterval;

	pCircEntry->isisCircL1DefaultMetric = pcirc->l1Metric.defalt & 0x3f;
	pCircEntry->isisCircL1DelayMetric   = pcirc->l1Metric.delay & 0x3f;
	pCircEntry->isisCircL1ExpenseMetric = pcirc->l1Metric.expense & 0x3f;
	pCircEntry->isisCircL1ErrorMetric   = pcirc->l1Metric.error & 0x3f;

	pCircEntry->isisCircExtDomain = 1;		/* false */

        pCircEntry->isisCircAdjChanges = pcirc->adjacencyEvents;

        pCircEntry->isisCircInitFails = pcirc->initFailures;

        pCircEntry->isisCircRejAdjs = pcirc->rejAdjs;

        pCircEntry->isisCircOutCtrlPDUs = pcirc->pdusSent;	/* control puds ??? */
        pCircEntry->isisCircInCtrlPDUs = pcirc->pdusReceived;	/* control pdus ??? */

/*
        Counter                isisCircIDFieldLenMismatches;
        Counter                isisCircMaxAreaAddrMismatches;
*/

	pCircEntry->isisCircL2DefaultMetric = pcirc->l2Metric.defalt & 0x3f;
	pCircEntry->isisCircL2DelayMetric   = pcirc->l2Metric.delay & 0x3f;
	pCircEntry->isisCircL2ExpenseMetric = pcirc->l2Metric.expense & 0x3f;
	pCircEntry->isisCircL2ErrorMetric   = pcirc->l2Metric.error & 0x3f;

	if (pcirc->manualL2Only == True) pCircEntry->isisCircManL2Only = 2;
	else pCircEntry->isisCircManL2Only = 1;

	pCircEntry->isisCircL1ISPriority = pcirc->l1Priority;

	copyOctetString(&pCircEntry->isisCircL1CircID, pcirc->circuitId, 7);


	copyOctetString(&pCircEntry->isisCircL1DesIS, pcirc->circuitId, 7);

        pCircEntry->isisCircLANL1DesISChanges = pcirc->l1DesignateChanges; /* planting */


	pCircEntry->isisCircL2ISPriority = pcirc->l2Priority;

	copyOctetString(&pCircEntry->isisCircL2CircID, pcirc->l2CircuitId, 7);

	copyOctetString(&pCircEntry->isisCircL2DesIS, pcirc->l2CircuitId, 7);

        pCircEntry->isisCircLANL2DesISChanges = pcirc->l2DesignateChanges;

/*
	CircuitID              isisCircPtToPtCircID;
	ObjectIdentifier       isisCircStaticCallInfo;
	OtherMetric            isisCircDACallDefMetInc;
	OtherMetric            isisCircDACallDelMetInc;
	OtherMetric            isisCircDACallErrMetInc;
	OtherMetric            isisCircDACallExpMetInc;
	Password               isisCircAuthTransPwd;	
        Counter                isisCircAuthFails;	

*/


	/* The Circuit Receive Password table */


	/* The IS Adjacency table */
	/* STEVE XXX - fix this to deal with reconfigs too */
	pISAdjTable = &pCircEntry->isisISAdjTable;
        /* Fill the IS adj table */
	for (j = 0; j < MAXISADJPERCIRC; ++j) {
            if ((pISAdjEntry = (IsisISAdjEntry *)locateEntry(pISAdjTable, j+1)) ==
							    (IsisISAdjEntry *)NULL) {

	        break;
            }
/*
        Integer                isisISAdjSysInstance;		
	Integer                isisISAdjCircIndex;		
	Integer                isisISAdjIndex;			
	Integer                isisISAdjState;			
	SNPAAddress            isisISAdjNeighSNPAAddress;	
	Integer                isisISAdjNeighSysType;		
	ShortOctetString       isisISAdjNeighSysID;		
	Integer                isisISAdjUsage;			
	Integer                isisISAdjHoldTimer;		
	ISPriority             isisISAdjNeighPriority;		
*/


	    /* The IS Adj Area Address table */
	    pISAdjAreaAddrTable = &pISAdjEntry->isisISAdjAreaAddrTable;
	    /* Fill the IS adj area address table */
	    for (k = 0; k < MAXAREAADDRESSESPERISADJ; ++k) {
                if ((pISAdjAreaAddrEntry = 
		    (IsisISAdjAreaAddrEntry *)queueNew(pISAdjAreaAddrTable)) ==
							(IsisISAdjAreaAddrEntry *)NULL) {

	            break;
                }
/*
	Integer 	isisISAdjAreaAddrSysInstance;
	Integer         isisISAdjAreaAddrCircIndex;
	Integer         isisISAdjAreaAddrAdjIndex;
        OSINSAddress    isisISAdjAreaAddress;
*/
                if (queueAdd(pISAdjAreaAddrTable, pISAdjAreaAddrEntry)) {
 
	            return(-1);
                }

	    }

	    /* The IS Adj IP Address table */


	    /* The IS Adj Protocol Supported table */


    	} /* end of for all existing IS adjacencies */


	/* The ES Adjacency table */


	/* The Reachable Address table */


	/* The IP Reachable Address table */




    } /* end of for all existing circuits */



    return(0);



} /* end of initIsisMibWarm() */


/*
**	Locate a table entry by the instance, given the table
*/
unsigned char *
locateEntry(pq, key)
Queue		*pq;
unsigned int	key;
{
    int 	i;
    int		nentries=pq->nentries;
    int		found=FALSE;

    i = 0; /* get gcc to shut up */
    switch (pq->mib) {
    case MIBSYSTEM:
	for (i = 0; i < nentries; ++i) 
	    if (key == ((IsisMibEntry *)(pq->pentry[i]))->isisSysEntry.isisSysInstance) {
		found = TRUE;
		break;
	    }
	break;

    case MIBCIRCUIT:
	for (i = 0; i < nentries; ++i) 
	    if (key == ((IsisCircEntry *)(pq->pentry[i]))->isisCircIndex) {
		found = TRUE;
		break;
	    }
	break;

    case MIBISADJ:
	for (i = 0; i < nentries; ++i) 
	    if (key == ((IsisISAdjEntry *)(pq->pentry[i]))->isisISAdjIndex) {
		found = TRUE;
		break;
	    }
	break;

    case MIBPROTSUPP:
	for (i = 0; i < nentries; ++i) 
	    if (key == ((IsisSysProtSuppEntry *)(pq->pentry[i]))->isisSysProtSuppProtocol) {
		found = TRUE;
		break;
	    }
	break;

    case MIBPARTREP:
        if (key && key <= nentries) {	
	    return(pq->pentry[key-1]);
        }
        else {
	    return((unsigned char *)0);

        }

    case MIBVIRTADJ:
        if (key && key <= nentries) {	
	    return(pq->pentry[key-1]);
        }
        else {
	    return((unsigned char *)0);

        }
   
    case MIBCIRCIS:
	for (i = 0; i < nentries; ++i) 
	    if (key == ((IsisCircISEntry *)(pq->pentry[i]))->isisCircISIndex) {
		found = TRUE;
		break;
	    }

    	break;

    case MIBCIRCAUTHRECPWD:
        if (key && key <= nentries) {	
	    return(pq->pentry[key-1]);
        }
        else {
	    return((unsigned char *)0);

        }

	break;

    case MIBISADJIPADDR:
	for (i = 0; i < nentries; ++i) 
	    if (key == ((IsisISAdjIPAddrEntry *)(pq->pentry[i]))->isisISAdjIPAddress) {
		found = TRUE;
		break;
	    }
	break;

    case MIBISADJPROTSUPP:
	for (i = 0; i < nentries; ++i) 
	    if (key == ((IsisISAdjProtSuppEntry *)(pq->pentry[i]))->isisISAdjProtSuppProtocol) {
		found = TRUE;
		break;
	    }
	break;

    case MIBRA:
	for (i = 0; i < nentries; ++i) 
	    if (key == ((IsisRAEntry *)(pq->pentry[i]))->isisRAIndex) {
		found = TRUE;
		break;
	    }
	break;

    case MIBIPRA:
	for (i = 0; i < nentries; ++i) 
	    if (key == ((IsisIPRAEntry *)(pq->pentry[i]))->isisIPRAIndex) {
		found = TRUE;
		break;
	    }
	break;

    default:
	break;

    }

    
    if (found) {
	return(pq->pentry[i]);
    }
    else {
	return((unsigned char *)0);
    }


} /* end of locateEntry() */



/*
**	Locate the next table entry by instance, given the table
*/
unsigned char *locateNextEntry(pq, key)
Queue	*pq;
int	key;
{
    if (key < pq->nentries) {	
	return(pq->pentry[key]);

    }
    else {
	return((unsigned char *)0);

    }

} /* end of locateNextEntry() */


/*
**	Locate the closest table entry. No one can be closer than itself
*/
unsigned char *locateClosestEntry(staircase, offset)
StairStep	staircase[];
unsigned int 	offset;			/* what to be matched */
{
    int 	i;
    int		nentries;
    int		found=FALSE;
    Queue	*pq;			/* table to be searched */
    unsigned int key;

    i = 0; /* get gcc to shut up */
    key = staircase[offset].key;
    pq  = (Queue *)staircase[offset].keyhole;
    nentries = pq->nentries;

    switch (pq->mib) {
    case MIBSYSTEM:
	for (i = 0; i < nentries; ++i) 
	    if (key <= ((IsisMibEntry *)(pq->pentry[i]))->isisSysEntry.isisSysInstance) {
		found = TRUE;
		key = ((IsisMibEntry *)(pq->pentry[i]))->isisSysEntry.isisSysInstance;
		break;
	    }
        if (!found) key = 1;
	break;

    case MIBMANAREAADDR:
	for (i = 0; i < nentries; ++i) {
	    if (cmpOctetString(&staircase[offset].longkey,
			       &((IsisManAreaAddrEntry *)(pq->pentry[i]))->isisManAreaAddr) <= 0) {
		found = TRUE;
		break;
	    }
	}

        if (found) return(pq->pentry[i]);
	else return((unsigned char *)0);

    case MIBAREAADDR:
	for (i = 0; i < nentries; ++i) {
	    if (cmpOctetString(&staircase[offset].longkey,
			       &((IsisAreaAddrEntry *)(pq->pentry[i]))->isisAreaAddr) <= 0) {
		found = TRUE;
		break;
	    }
	}

        if (found) return(pq->pentry[i]);
	else return((unsigned char *)0);

    case MIBCIRCUIT:
	for (i = 0; i < nentries; ++i) 
	    if (key <= ((IsisCircEntry *)(pq->pentry[i]))->isisCircIndex) {
		found = TRUE;
		key = ((IsisCircEntry *)(pq->pentry[i]))->isisCircIndex;
		break;
	    }
        if (!found) key = 1;
	break;

    case MIBISADJ:
	for (i = 0; i < nentries; ++i) 
	    if (key <= ((IsisISAdjEntry *)(pq->pentry[i]))->isisISAdjIndex) {
		found = TRUE;
		key = ((IsisISAdjEntry *)(pq->pentry[i]))->isisISAdjIndex;
		break;
	    }
        if (!found) key = 1;
	break;

    case MIBISADJAREAADDR:
	for (i = 0; i < nentries; ++i) {
	    if (cmpOctetString(&staircase[offset].longkey,
		       &((IsisISAdjAreaAddrEntry *)(pq->pentry[i]))->isisISAdjAreaAddress) <= 0) {
		found = TRUE;
		break;
	    }
	}

        if (found) return(pq->pentry[i]);
	else return((unsigned char *)0);

    case MIBPROTSUPP:
	for (i = 0; i < nentries; ++i) 
	    if (key <= ((IsisSysProtSuppEntry *)(pq->pentry[i]))->isisSysProtSuppProtocol) {
		found = TRUE;
		key = ((IsisSysProtSuppEntry *)(pq->pentry[i]))->isisSysProtSuppProtocol;
		break;
	    }
        if (!found) key = PROTSUPP_LOWEST;
	break;

    case MIBL2SUMMADDR:
	for (i = 0; i < nentries; ++i) 
	    if (key <= ((IsisL2SummAddrEntry *)(pq->pentry[i]))->isisL2SummAddress) {
		found = TRUE;
		key = ((IsisL2SummAddrEntry *)(pq->pentry[i]))->isisL2SummAddress;
		break;
	    }

	if (found) {
	    unsigned int key2 = staircase[2].key;	/* get the ip mask */
	    
	    found = FALSE;
	    while (i < nentries &&
		   key == ((IsisL2SummAddrEntry *)(pq->pentry[i]))->isisL2SummAddress) {
	        if (key2 <= ((IsisL2SummAddrEntry *)(pq->pentry[i]))->isisL2SummAddrMask) {
		    found = TRUE;
		    key2 = ((IsisL2SummAddrEntry *)(pq->pentry[i]))->isisL2SummAddrMask;
		    break;
	        }
	    }
	    if (found) staircase[2].key = key2;
 	    else staircase[2].key = 1;
        }

        if (!found) key = 1;
	
	break;

    case MIBAREARECPWD:
	for (i = 0; i < nentries; ++i) {
	    if (cmpOctetString(&staircase[offset].longkey,
		       &((IsisAuthAreaRecPwdEntry *)(pq->pentry[i]))->isisAuthAreaRecPwd) <= 0) {
		found = TRUE;
		break;
	    }
	}

        if (found) return(pq->pentry[i]);
	else return((unsigned char *)0);

    case MIBDOMAINRECPWD:
	for (i = 0; i < nentries; ++i) {
	    if (cmpOctetString(&staircase[offset].longkey,
	        &((IsisAuthDomainRecPwdEntry *)(pq->pentry[i]))->isisAuthDomainRecPwd) <= 0) {
		found = TRUE;
		break;
	    }
	}

        if (found) return(pq->pentry[i]);
	else return((unsigned char *)0);

    case MIBPARTREP:
        if (key && key <= nentries) {	
	    return(pq->pentry[key-1]);
        }
        else {
	    return((unsigned char *)0);

        }

    case MIBPARTAREAADDR:
	for (i = 0; i < nentries; ++i) {
	    if (cmpOctetString(&staircase[offset].longkey,
		       &((IsisPartAreaAddrEntry *)(pq->pentry[i]))->isisPartAreaAddr) <= 0) {
		found = TRUE;
		break;
	    }
	}

        if (found) return(pq->pentry[i]);
	else return((unsigned char *)0);

    case MIBVIRTADJ:
        if (key && key <= nentries) {	
	    return(pq->pentry[key-1]);
        }
        else {
	    return((unsigned char *)0);

        }

    case MIBCIRCIS:
	for (i = 0; i < nentries; ++i) 
	    if (key <= ((IsisCircISEntry *)(pq->pentry[i]))->isisCircISIndex) {
		found = TRUE;
		key = ((IsisCircISEntry *)(pq->pentry[i]))->isisCircISIndex;
		break;
	    }
        if (!found) key = 1;
	break;

    case MIBCIRCAUTHRECPWD:
        if (key && key <= nentries) {	
	    return(pq->pentry[key-1]);
        }
        else {
	    return((unsigned char *)0);

        }

    case MIBISADJIPADDR:
	for (i = 0; i < nentries; ++i)
	    if (key <= ((IsisISAdjIPAddrEntry *)(pq->pentry[i]))->isisISAdjIPAddress) {
		found = TRUE;
		key = ((IsisISAdjIPAddrEntry *)(pq->pentry[i]))->isisISAdjIPAddress;
		break;
	    }
	if (!found) key = 1;
	break;

    case MIBISADJPROTSUPP:
	for (i = 0; i < nentries; ++i) 
	    if (key <= ((IsisISAdjProtSuppEntry *)(pq->pentry[i]))->isisISAdjProtSuppProtocol) {
		found = TRUE;
		key = ((IsisISAdjProtSuppEntry *)(pq->pentry[i]))->isisISAdjProtSuppProtocol;
		break;
	    }
        if (!found) key = PROTSUPP_LOWEST;
	break;

    case MIBESADJ:
	for (i = 0; i < nentries; ++i) 
	    if (key <= ((IsisESAdjEntry *)(pq->pentry[i]))->isisESAdjAdjIndex) {
		found = TRUE;
		key = ((IsisESAdjEntry *)(pq->pentry[i]))->isisESAdjAdjIndex;
		break;
	    }

        if (!found) key = 1;
	
	break;

    case MIBRA:
	for (i = 0; i < nentries; ++i) 
	    if (key <= ((IsisRAEntry *)(pq->pentry[i]))->isisRAIndex) {
		found = TRUE;
		key = ((IsisRAEntry *)(pq->pentry[i]))->isisRAIndex;
		break;
	    }
        if (!found) key = 1;
	break;

    case MIBIPRA:
	for (i = 0; i < nentries; ++i) 
	    if (key <= ((IsisIPRAEntry *)(pq->pentry[i]))->isisIPRAIndex) {
		found = TRUE;
		key = ((IsisIPRAEntry *)(pq->pentry[i]))->isisIPRAIndex;
		break;
	    }
        if (!found) key = 1;
	break;

    default:
	break;

    }


    staircase[offset].key = key;		
    
    if (found) {
	return(pq->pentry[i]);
    }
    else {
	return((unsigned char *)0);
    }


} /* end of locateClosestEntry() */





/*
**	Locate an entry in the manAreaAddr table
*/
IsisManAreaAddrEntry *locateManAreaAddrEntry(Queue *pq, 
				             OSINSAddress *paddr)
{
    int		i;
    int		nentries=pq->nentries;
    int		found=FALSE;
    IsisManAreaAddrEntry	*pentry = 0;

    for (i = 0; i < nentries; ++i) {
	pentry = (IsisManAreaAddrEntry *)(pq->pentry[i]);

	if (cmpOctetString(paddr, &pentry->isisManAreaAddr) == 0) {
	    found = TRUE;
	    break;
	}
    }

    if (found) return(pentry);
    else return(0);


} /* end of locateManAreaAddrEntry() */



/*
**	Locate an entry in the Level 1 AreaAddr table
*/
IsisAreaAddrEntry *locateAreaAddrEntry(Queue *pq, 
				       OSINSAddress *paddr)
{
    int		i;
    int		nentries=pq->nentries;
    int		found=FALSE;
    IsisAreaAddrEntry	*pentry = 0;

    for (i = 0; i < nentries; ++i) {
	pentry = (IsisAreaAddrEntry *)(pq->pentry[i]);

	if (cmpOctetString(paddr, &pentry->isisAreaAddr) == 0) {
	    found = TRUE;
	    break;
	}
    }

    if (found) return(pentry);
    else return(0);


} /* end of locateAreaAddrEntry() */


/*
**	Locate an entry in the L2SummAddr Table
*/
IsisL2SummAddrEntry *locateEntryL2SummAddr(pq, address, mask)
Queue		*pq;			/* table to be searched */
IpAddress	address;
IpAddress	mask;
{
    int 	i;
    int		nentries=pq->nentries;
    int		found=FALSE;
    IsisL2SummAddrEntry *pentry = 0;

    for (i = 0; i < nentries; ++i) {
	pentry = (IsisL2SummAddrEntry *)(pq->pentry[i]);

	if (pentry->isisL2SummAddress == address &&
	    pentry->isisL2SummAddrMask == mask      ) {
	    found = TRUE;
	    break;
      	}
    }

    if (found) return(pentry);
    else return(0);

} /* end of locateEntryL2SummAddr() */


/*
**	Locate an entry in the AuthAreaRecPwd tabel
*/
IsisAuthAreaRecPwdEntry *locateAuthAreaRecPwdEntry(Queue *pq,
					           Password *ppw)
{
    int		i;
    int		nentries=pq->nentries;
    int		found=FALSE;
    IsisAuthAreaRecPwdEntry	*pentry = 0;

    for (i = 0; i < nentries; ++i) {
	pentry = (IsisAuthAreaRecPwdEntry *)(pq->pentry[i]);

	if (cmpOctetString(ppw, &pentry->isisAuthAreaRecPwd) == 0) {
	    found = TRUE;
	    break;
	}
    }

    if (found) return(pentry);
    else return(0);

} /* end of locateAuthAreaRecPwdEntry() */


/*
**	Locate an entry in the AuthDomainRecPwd tabel
*/
IsisAuthDomainRecPwdEntry *locateAuthDomainRecPwdEntry(Queue *pq,
					               Password *ppw)
{
    int		i;
    int		nentries=pq->nentries;
    int		found=FALSE;
    IsisAuthDomainRecPwdEntry	*pentry = 0;

    for (i = 0; i < nentries; ++i) {
	pentry = (IsisAuthDomainRecPwdEntry *)(pq->pentry[i]);

	if (cmpOctetString(ppw, &pentry->isisAuthDomainRecPwd) == 0) {
	    found = TRUE;
	    break;
	}
    }

    if (found) return(pentry);
    else return(0);

} /* end of locateAuthDomainRecPwdEntry() */



/*
**	Locate an entry in the PartAreaAddr table
*/
IsisPartAreaAddrEntry *locatePartAreaAddrEntry(Queue *pq, 
				               OSINSAddress *paddr)
{
    int		i;
    int		nentries=pq->nentries;
    int		found=FALSE;
    IsisPartAreaAddrEntry	*pentry = 0;

    for (i = 0; i < nentries; ++i) {
	pentry = (IsisPartAreaAddrEntry *)(pq->pentry[i]);

	if (cmpOctetString(paddr, &pentry->isisPartAreaAddr) == 0) {
	    found = TRUE;
	    break;
	}
    }

    if (found) return(pentry);
    else return(0);


} /* end of locatePartAreaAddrEntry() */



/*
**	Locate an entry in the CircAuthRecPwd tabel
*/
IsisCircAuthRecPwdEntry *locateCircAuthRecPwdEntry(Queue *pq,
					           Password *ppw)
{
    int		i;
    int		nentries=pq->nentries;
    int		found=FALSE;
    IsisCircAuthRecPwdEntry	*pentry = 0;

    for (i = 0; i < nentries; ++i) {
	pentry = (IsisCircAuthRecPwdEntry *)(pq->pentry[i]);

	if (cmpOctetString(ppw, &pentry->isisCircAuthRecPwd) == 0) {
	    found = TRUE;
	    break;
	}
    }

    if (found) return(pentry);
    else return(0);

} /* end of locateCircAuthRecPwdEntry() */



/*
**	Locate an entry in the IsAdjAreaAddr table
*/
IsisISAdjAreaAddrEntry *locateIsAdjAreaAddrEntry(Queue *pq, 
				                 OSINSAddress *paddr)
{
    int		i;
    int		nentries=pq->nentries;
    int		found=FALSE;
    IsisISAdjAreaAddrEntry	*pentry = 0;

    for (i = 0; i < nentries; ++i) {
	pentry = (IsisISAdjAreaAddrEntry *)(pq->pentry[i]);

	if (cmpOctetString(paddr, &pentry->isisISAdjAreaAddress) == 0) {
	    found = TRUE;
	    break;
	}
    }

    if (found) return(pentry);
    else return(0);


} /* end of locateIsAdjAreaAddrEntry() */


/*
**	Locate an entry in the ES Adj Table
*/
IsisESAdjEntry *locateEntryESAdj(Queue *pq, 
				 int adjIndex)
{
    int 	i;
    int		nentries=pq->nentries;
    int		found=FALSE;
    IsisESAdjEntry *pentry = 0;

    for (i = 0; i < nentries; ++i) {
	pentry = (IsisESAdjEntry *)(pq->pentry[i]);

	if (pentry->isisESAdjAdjIndex == adjIndex) {
	    found = TRUE;
	    break;
      	}
    }

    if (found) return(pentry);
    else return(0);

} /* end of locateEntryESAdj() */


/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.
*/
unsigned char * searchEntry(staircase, height, depth)
StairStep	staircase[];
unsigned int	height;			/* MUST BE [1, 4] */
unsigned int	depth;			/* MUST BE [1, 4] */
{
    unsigned char *pEntry;

    if (depth == 0 || depth > 4) return((unsigned char *)0);
    if (height == 0 || height > 4) return((unsigned char *)0);

    if (staircase[depth-1].key == 0) staircase[depth-1].key = 1;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

        if (depth == height) return(pEntry);	/* found one */

	switch (depth) {
	case 1:			/* Mib instance */
	    staircase[depth].keyhole = (unsigned char *)&((IsisMibEntry *)pEntry)->isisCircTable;
	    break;
	case 2:			/* Circuit */
	    staircase[depth].keyhole = (unsigned char *)&((IsisCircEntry *)pEntry)->isisISAdjTable;
	    break;
	case 3:			/* IS Adjacency */
	    staircase[depth].keyhole = (unsigned char *)&((IsisISAdjEntry *)pEntry)->isisISAdjAreaAddrTable;
	    break;
  	}

	return searchEntry(staircase, height, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntry(staircase, height, depth-1);	 /* backtrack */

    }


} /* end of searchEntry() */



/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it.  Else,
**	return null.  ManAreaAddr table.
*/
unsigned char *searchEntryManAreaAddr(StairStep staircase[],
				      unsigned int depth    )
{
    unsigned char *pentry = 0;

    if (pentry = locateClosestEntry(staircase, depth-1)) {

	switch (depth) {
	case 1:			
	    staircase[depth].keyhole = 
		(unsigned char *)&((IsisMibEntry *)pentry)->isisSysEntry.isisManAreaAddrTable;
	    
	    break;
	
	case 2:
	    return(pentry);
	}

	return searchEntryManAreaAddr(staircase, depth+1);	/* depth */

    }
    else {

	switch (depth) {
	case 1:
	     return((unsigned char *)0);

	case 2:
	    staircase[0].key += 1;	/* breadth */
	    staircase[1].longkey.len = 0;
	    return searchEntryManAreaAddr(staircase, depth-1);	 /* backtrack */

	}

    }

    return(0);

} /* end of searchEntryManAreaAddr() */




/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it.  Else,
**	return null.  Level 1 AreaAddr table.
*/
unsigned char *searchEntryAreaAddr(StairStep staircase[],
				   unsigned int depth    )
{
    unsigned char *pentry = 0;

    if (pentry = locateClosestEntry(staircase, depth-1)) {

	switch (depth) {
	case 1:			
	    staircase[depth].keyhole = 
		(unsigned char *)&((IsisMibEntry *)pentry)->isisSysEntry.isisAreaAddrTable;
	    
	    break;
	
	case 2:
	    return(pentry);
	}

	return searchEntryAreaAddr(staircase, depth+1);	/* depth */

    }
    else {

	switch (depth) {
	case 1:
	     return((unsigned char *)0);

	case 2:
	    staircase[0].key += 1;	/* breadth */
	    staircase[1].longkey.len = 0;
	    return searchEntryAreaAddr(staircase, depth-1);	 /* backtrack */

	}

    }

    return(0);
} /* end of searchEntryAreaAddr() */


/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  ProtSupp Table.
*/
unsigned char * searchEntryProtSupp(staircase, height, depth)
StairStep	staircase[];
unsigned int	height;			/* MUST BE [1, 2] */
unsigned int	depth;			/* MUST BE [1, 2] */
{
    unsigned char *pEntry;

    if (depth == 0 || depth > 2) return((unsigned char *)0);
    if (height == 0 || height > 2) return((unsigned char *)0);

    if (staircase[depth-1].key == 0) staircase[depth-1].key = 1;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

        if (depth == height) return(pEntry);	/* found one */

	switch (depth) {
	case 1:			/* Mib instance */
	    staircase[depth].keyhole = (unsigned char *)&((IsisMibEntry *)pEntry)->isisSysProtSuppTable;
	    break;

  	}

	return searchEntryProtSupp(staircase, height, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntryProtSupp(staircase, height, depth-1);	 /* backtrack */

    }


} /* end of searchEntryProtSupp() */


/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  L2SummAddr Table.
*/
unsigned char * searchEntryL2SummAddr(staircase, height, depth)
StairStep	staircase[];
unsigned int	height;			/* MUST BE [1, 3] */
unsigned int	depth;			/* MUST BE [1, 3] */
{
    unsigned char *pEntry;

    if (depth == 0 || depth > 3) return((unsigned char *)0);
    if (height == 0 || height > 3) return((unsigned char *)0);

    if (staircase[depth-1].key == 0) staircase[depth-1].key = 1;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

	switch (depth) {
	case 1:			/* Mib instance */
	    staircase[depth].keyhole = (unsigned char *)&((IsisMibEntry *)pEntry)->isisL2SummAddrTable;
	    break;

	case 2:
	    return(pEntry);	/* found one */

  	}

	return searchEntryL2SummAddr(staircase, height, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntryL2SummAddr(staircase, height, depth-1);	 /* backtrack */

    }


} /* end of searchEntryL2SummAddr() */


/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  AreaRecPwd Table.
*/
unsigned char * searchEntryAreaRecPwd(StairStep	staircase[],
				      unsigned int depth    )
{
    unsigned char *pEntry;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

	switch (depth) {
	case 1:
	    staircase[depth].keyhole = 
			(unsigned char *)&((IsisMibEntry *)pEntry)->isisAuthAreaRecPwdTable;
	    break;

	case 2:
	    return(pEntry);

  	}

	return searchEntryAreaRecPwd(staircase, depth+1);	/* depth */

    }
    else {

	switch (depth) {
	case 1:
	    return((unsigned char *)0);

	case 2:
	    staircase[0].key += 1;	/* breadth */
	    staircase[1].longkey.len = 0;
	    return searchEntryAreaRecPwd(staircase, depth-1); 	 /* backtrack */

	}
    }

    return(0);
} /* end of searchEntryAreaRecPwd() */



/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  DomainRecPwd Table.
*/
unsigned char * searchEntryDomainRecPwd(StairStep staircase[],
					unsigned int	depth )
{
    unsigned char *pEntry;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

	switch (depth) {
	case 1:	
	    staircase[depth].keyhole = 
			(unsigned char *)&((IsisMibEntry *)pEntry)->isisAuthDomainRecPwdTable;
	    break;

	case 2:
	    return(pEntry);

  	}

	return searchEntryDomainRecPwd(staircase, depth+1);	/* depth */

    }
    else {

	switch (depth) {
	case 1:
	    return((unsigned char *)0);

	case 2:
	    staircase[0].key += 1;	/* breadth */
	    staircase[1].longkey.len = 0;
	    return searchEntryDomainRecPwd(staircase, depth-1); 	 /* backtrack */

	}

    }

    return(0);
} /* end of searchEntryDomainRecPwd() */



/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  PartRep Table.
*/
unsigned char * searchEntryPartRep(staircase, height, depth)
StairStep	staircase[];
unsigned int	height;			/* MUST BE [1, 2] */
unsigned int	depth;			/* MUST BE [1, 2] */
{
    unsigned char *pEntry;

    if (depth == 0 || depth > 2) return((unsigned char *)0);
    if (height == 0 || height > 2) return((unsigned char *)0);

    if (staircase[depth-1].key == 0) staircase[depth-1].key = 1;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

        if (depth == height) return(pEntry);	/* found one */

	switch (depth) {
	case 1:			/* Mib instance */
	    staircase[depth].keyhole = (unsigned char *)&((IsisMibEntry *)pEntry)->isisPartRepTable;
	    break;

  	}

	return searchEntryPartRep(staircase, height, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntryPartRep(staircase, height, depth-1); 	 /* backtrack */

    }

    return(0);
} /* end of searchEntryPartRep() */



/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it.  Else,
**	return null.  PartAreaAddr table.
*/
unsigned char *searchEntryPartAreaAddr(StairStep staircase[],
				       unsigned int depth    )
{
    unsigned char *pentry;

    if (pentry = locateClosestEntry(staircase, depth-1)) {

	switch (depth) {
	case 1:			
	    staircase[depth].keyhole = 
		(unsigned char *)&((IsisMibEntry *)pentry)->isisPartAreaAddrTable;
	    
	    break;
	
	case 2:
	    return(pentry);
	}

	return searchEntryPartAreaAddr(staircase, depth+1);	/* depth */

    }
    else {

	switch (depth) {
	case 1:
	     return((unsigned char *)0);

	case 2:
	    staircase[0].key += 1;	/* breadth */
	    staircase[1].longkey.len = 0;
	    return searchEntryPartAreaAddr(staircase, depth-1);	 /* backtrack */

	}

    }

    return(0);
} /* end of searchEntryPartAreaAddr() */



/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  VirtAdj Table.
*/
unsigned char * searchEntryVirtAdj(staircase, height, depth)
StairStep	staircase[];
unsigned int	height;			/* MUST BE [1, 2] */
unsigned int	depth;			/* MUST BE [1, 2] */
{
    unsigned char *pEntry;

    if (depth == 0 || depth > 2) return((unsigned char *)0);
    if (height == 0 || height > 2) return((unsigned char *)0);

    if (staircase[depth-1].key == 0) staircase[depth-1].key = 1;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

        if (depth == height) return(pEntry);	/* found one */

	switch (depth) {
	case 1:			/* Mib instance */
	    staircase[depth].keyhole = (unsigned char *)&((IsisMibEntry *)pEntry)->isisVirtAdjTable;
	    break;

  	}

	return searchEntryVirtAdj(staircase, height, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntryVirtAdj(staircase, height, depth-1); 	 /* backtrack */

    }


} /* end of searchEntryVirtAdj() */



/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  CircAuthRecPwd Table.
*/
unsigned char * searchEntryCircAuthRecPwd(StairStep staircase[],
					  unsigned int	depth   )
{
    unsigned char *pEntry;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

	switch (depth) {
	case 1:			
	    staircase[depth].keyhole = 
			(unsigned char *)&((IsisMibEntry *)pEntry)->isisCircTable;
	    break;
	case 2:			
	    staircase[depth].keyhole = 
			(unsigned char *)&((IsisCircEntry *)pEntry)->isisCircAuthRecPwdTable;
	    break;
	case 3:
	    return(pEntry);
  	}

	return searchEntryCircAuthRecPwd(staircase, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntryCircAuthRecPwd(staircase, depth-1);	 /* backtrack */

    }


} /* end of searchEntryCircAuthRecPwd() */


/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  ISAdjIPAddr Table.
*/
unsigned char * searchEntryISAdjIPAddr(staircase, height, depth)
StairStep	staircase[];
unsigned int	height;			/* MUST BE [1, 4] */
unsigned int	depth;			/* MUST BE [1, 4] */
{
    unsigned char *pEntry;

    if (depth == 0 || depth > 4) return((unsigned char *)0);
    if (height == 0 || height > 4) return((unsigned char *)0);

    if (staircase[depth-1].key == 0) staircase[depth-1].key = 1;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

        if (depth == height) return(pEntry);	/* found one */

	switch (depth) {
	case 1:			/* Mib instance */
	    staircase[depth].keyhole = (unsigned char *)&((IsisMibEntry *)pEntry)->isisCircTable;
	    break;
	case 2:			/* Circuit */
	    staircase[depth].keyhole = (unsigned char *)&((IsisCircEntry *)pEntry)->isisISAdjTable;
	    break;
	case 3:			/* IS Adjacency */
	    staircase[depth].keyhole = (unsigned char *)&((IsisISAdjEntry *)pEntry)->isisISAdjIPAddrTable;
	    break;
  	}

	return searchEntryISAdjIPAddr(staircase, height, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntryISAdjIPAddr(staircase, height, depth-1);	 /* backtrack */

    }


} /* end of searchEntryISAdjIPAddr() */




/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  ISAdjProtSupp Table.
*/
unsigned char * searchEntryISAdjProtSupp(staircase, height, depth)
StairStep	staircase[];
unsigned int	height;			/* MUST BE [1, 4] */
unsigned int	depth;			/* MUST BE [1, 4] */
{
    unsigned char *pEntry;

    if (depth == 0 || depth > 4) return((unsigned char *)0);
    if (height == 0 || height > 4) return((unsigned char *)0);

    if (staircase[depth-1].key == 0) staircase[depth-1].key = 1;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

        if (depth == height) return(pEntry);	/* found one */

	switch (depth) {
	case 1:			/* Mib instance */
	    staircase[depth].keyhole = (unsigned char *)&((IsisMibEntry *)pEntry)->isisCircTable;
	    break;
	case 2:			/* Circuit */
	    staircase[depth].keyhole = (unsigned char *)&((IsisCircEntry *)pEntry)->isisISAdjTable;
	    break;
	case 3:			/* IS Adjacency */
	    staircase[depth].keyhole = (unsigned char *)&((IsisISAdjEntry *)pEntry)->isisISAdjProtSuppTable;
	    break;
  	}

	return searchEntryISAdjProtSupp(staircase, height, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntryISAdjProtSupp(staircase, height, depth-1);	 /* backtrack */

    }


} /* end of searchEntryISAdjProtSupp() */



/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  ESAdj Table.
*/
unsigned char * searchEntryESAdj(StairStep staircase[],
				 unsigned int	depth  )			
{
    unsigned char *pEntry;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

	switch (depth) {
	case 1:			
	    staircase[depth].keyhole = (unsigned char *)&((IsisMibEntry *)pEntry)->isisCircTable;
	    break;

	case 2:			
	    staircase[depth].keyhole = (unsigned char *)&((IsisCircEntry *)pEntry)->isisESAdjTable;
	    break;

	case 3:
	    return(pEntry);	/* found one */

  	}

	return searchEntryESAdj(staircase, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntryESAdj(staircase, depth-1);	 /* backtrack */

    }


} /* end of searchEntryESAdj() */


/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  RA TAble.
*/
unsigned char * searchEntryRA(staircase, height, depth)
StairStep	staircase[];
unsigned int	height;			/* MUST BE [1, 3] */
unsigned int	depth;			/* MUST BE [1, 3] */
{
    unsigned char *pEntry;

    if (depth == 0 || depth > 3) return((unsigned char *)0);
    if (height == 0 || height > 3) return((unsigned char *)0);

    if (staircase[depth-1].key == 0) staircase[depth-1].key = 1;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

        if (depth == height) return(pEntry);	/* found one */

	switch (depth) {
	case 1:			/* Mib instance */
	    staircase[depth].keyhole = (unsigned char *)&((IsisMibEntry *)pEntry)->isisCircTable;
	    break;
	case 2:			/* Circuit */
	    staircase[depth].keyhole = (unsigned char *)&((IsisCircEntry *)pEntry)->isisRATable;
	    break;
  	}

	return searchEntryRA(staircase, height, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntryRA(staircase, height, depth-1);	 /* backtrack */

    }


} /* end of searchEntryRA() */



/*
**	Search for the entry specified in staircase.  If found, return it.
**	Else, search for the next in tree.  If found, return it. Else,
**	return null.  IP RA TAble.
*/
unsigned char * searchEntryIPRA(staircase, height, depth)
StairStep	staircase[];
unsigned int	height;			/* MUST BE [1, 3] */
unsigned int	depth;			/* MUST BE [1, 3] */
{
    unsigned char *pEntry;

    if (depth == 0 || depth > 3) return((unsigned char *)0);
    if (height == 0 || height > 3) return((unsigned char *)0);

    if (staircase[depth-1].key == 0) staircase[depth-1].key = 1;

    if (pEntry = locateClosestEntry(staircase, depth-1)){

        if (depth == height) return(pEntry);	/* found one */

	switch (depth) {
	case 1:			/* Mib instance */
	    staircase[depth].keyhole = (unsigned char *)&((IsisMibEntry *)pEntry)->isisCircTable;
	    break;
	case 2:			/* Circuit */
	    staircase[depth].keyhole = (unsigned char *)&((IsisCircEntry *)pEntry)->isisIPRATable;
	    break;
  	}

	return searchEntryIPRA(staircase, height, depth+1);	/* depth */

    }
    else {
	if (depth == 1) return((unsigned char *)0);

	staircase[depth-2].key += 1;	/* breadth */
	return searchEntryIPRA(staircase, height, depth-1);	 /* backtrack */

    }


} /* end of searchEntryIPRA() */



/* Sorted-Queue related routines */


/*
**	Initialize a queue
*/
void 
queueInit(pq, mib, maxentries)
Queue	*pq;
int	mib;
int	maxentries;
{
    int		i;

    switch (mib) {
    case MIBSYSTEM:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisMibTable *)pq)->isisMibEntry[i];

	break;

    case MIBMANAREAADDR:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisManAreaAddrTable *)pq)->isisManAreaAddrEntry[i];

	break;

    case MIBAREAADDR:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisAreaAddrTable *)pq)->isisAreaAddrEntry[i];

	break;

    case MIBCIRCUIT:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisCircTable *)pq)->isisCircEntry[i];

	break;

    case MIBISADJ:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisISAdjTable *)pq)->isisISAdjEntry[i];

	break;

    case MIBISADJAREAADDR:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisISAdjAreaAddrTable *)pq)->isisISAdjAreaAddrEntry[i];

	break;

    case MIBPROTSUPP:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisSysProtSuppTable *)pq)->isisSysProtSuppEntry[i];

	break;

    case MIBL2SUMMADDR:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisL2SummAddrTable *)pq)->isisL2SummAddrEntry[i];

	break;

    case MIBAREARECPWD:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisAuthAreaRecPwdTable *)pq)->isisAuthAreaRecPwdEntry[i];

	break;

    case MIBDOMAINRECPWD:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisAuthDomainRecPwdTable *)pq)->isisAuthDomainRecPwdEntry[i];

	break;

    case MIBPARTREP:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisPartRepTable *)pq)->isisPartRepEntry[i];

	break;

    case MIBPARTAREAADDR:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisPartAreaAddrTable *)pq)->isisPartAreaAddrEntry[i];

	break;

    case MIBVIRTADJ:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisVirtAdjTable *)pq)->isisVirtAdjEntry[i];

	break;

    case MIBCIRCIS:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisCircISTable *)pq)->isisCircISEntry[i];

	break;

    case MIBCIRCAUTHRECPWD:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisCircAuthRecPwdTable *)pq)->isisCircAuthRecPwdEntry[i];

	break;

    case MIBISADJIPADDR:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisISAdjIPAddrTable *)pq)->isisISAdjIPAddrEntry[i];

	break;

    case MIBISADJPROTSUPP:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisISAdjProtSuppTable *)pq)->isisISAdjProtSuppEntry[i];

	break;

    case MIBESADJ:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisESAdjTable *)pq)->isisESAdjEntry[i];

	break;

    case MIBRA:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisRATable *)pq)->isisRAEntry[i];

	break;

    case MIBIPRA:
	for (i = 0; i < maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisIPRATable *)pq)->isisIPRAEntry[i];

	break;

    default:
	return;

    }

    pq->mib = mib;
    pq->nentries = 0;
    pq->maxentries = maxentries;

    return;

} /* end of queueInit() */


/*
**	Get a new entry from a table; must be followed by queueAdd()
*/
unsigned char *queueNew(pq)
Queue	*pq;
{
    if (pq->nentries < pq->maxentries) {
	return(pq->pentry[pq->nentries]);
    }
    else {
	return((unsigned char *)0);
    }


} /* end of queueNew() */


/*
**	Add a new entry to a table; must be preceded by queueNew()
*/
int queueAdd(pq, pentry)
Queue	*pq;
unsigned char *pentry;			/* ptr to entry to be added */
{
    int		i;
    int		found;		/* found the availabe entry */

    for (i = pq->nentries, found = FALSE; i < pq->maxentries; ++i) {
	if (pq->pentry[i] == pentry) {
	    found = TRUE;
	    break;
	}
    }
    
    if (found) {		/* immediately following the bucket */
	++pq->nentries;		/* enclose it into the bucket */
        
	switch (pq->mib) {
	case MIBSYSTEM:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpSysEntry);
	    break;

	case MIBMANAREAADDR:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpManAreaAddrEntry);
	    break;

	case MIBAREAADDR:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpAreaAddrEntry);
	    break;

	case MIBCIRCUIT:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpCircEntry);
	    break;

	case MIBISADJ:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpISAdjEntry);
	    break;

	case MIBISADJAREAADDR:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpISAdjAreaAddrEntry);
	    break;

	case MIBPROTSUPP:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpProtSuppEntry);
	    break;

	case MIBL2SUMMADDR:
	    { 
	    int j;
	    IsisL2SummAddrEntry **pptrs;

	    /* Sorted by the IP addresses first */
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpL2SummAddrEntryi);

	    pptrs = (IsisL2SummAddrEntry **)pq->pentry;
	    for (i = 0; i < pq->nentries-1; i += j) {
		
		for (j = 0; j < pq->nentries-i-1; ++j) {
		    if ((pptrs[i+j])->isisL2SummAddress != 
		 	(pptrs[i+j+1])->isisL2SummAddress  ) 
		    	break;
		}

		if (++j >= 2)	/* need sorting by mask */
                    qsort(&pq->pentry[i], j, sizeof *(pq->pentry), cmpL2SummAddrEntryj);

	    } /* end of for all valid entries in table */

	    }

	    break;

	case MIBAREARECPWD:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpAreaRecPwdEntry);
	    break;

	case MIBDOMAINRECPWD:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpDomainRecPwdEntry);
	    break;

	case MIBPARTREP:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpPartRepEntry);
	    break;

	case MIBPARTAREAADDR:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpPartAreaAddrEntry);
	    break;

	case MIBVIRTADJ:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpVirtAdjEntry);
	    break;

	case MIBCIRCIS:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpCircISEntry);
	    break;

	case MIBCIRCAUTHRECPWD:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpCircAuthRecPwdEntry);
	    break;

	case MIBISADJIPADDR:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpISAdjIPAddrEntry);
	    break;

	case MIBISADJPROTSUPP:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpISAdjProtSuppEntry);
	    break;

	case MIBESADJ:
	    { 
	    int j;
	    IsisESAdjEntry **pptrs;

	    /* Sorted by the ES adj index first */
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpESAdjEntryi);

	    pptrs = (IsisESAdjEntry **)pq->pentry;
	    for (i = 0; i < pq->nentries-1; i += j) {
		
		for (j = 0; j < pq->nentries-i-1; ++j) {
		    if ((pptrs[i+j])->isisESAdjAdjIndex != 
		 	(pptrs[i+j+1])->isisESAdjAdjIndex ) 
		    	break;
		}

		if (++j >= 2)	/* need sorting by ESID */
                    qsort(&pq->pentry[i], j, sizeof *(pq->pentry), cmpESAdjEntryj);

	    } /* end of for all valid entries in table */

	    }

	    break;

	case MIBRA:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpRAEntry);
	    break;

	case MIBIPRA:
	    qsort(pq->pentry, pq->nentries, sizeof *(pq->pentry), cmpIPRAEntry);
	    break;

	default:
	    --pq->nentries;
	    return(-1);

	}

	return(0);
    }
    else {
	return(-1);

    }
    

} /* end of queueAdd() */


/*
**	Comparison routines, by entry type
*/
int cmpSysEntry(a, b)
IsisSysEntry	**a;
IsisSysEntry	**b;
{
    if ((*a)->isisSysInstance < (*b)->isisSysInstance) return(-1);
    else if ((*a)->isisSysInstance > (*b)->isisSysInstance) return(1);
    else return(0);
}

int cmpManAreaAddrEntry(a, b)
IsisManAreaAddrEntry	**a;
IsisManAreaAddrEntry	**b;
{

    return(cmpOctetString(&(*a)->isisManAreaAddr, &(*b)->isisManAreaAddr));

}

int cmpAreaAddrEntry(a, b)
IsisAreaAddrEntry	**a;
IsisAreaAddrEntry	**b;
{

    return(cmpOctetString(&(*a)->isisAreaAddr, &(*b)->isisAreaAddr));

}


int cmpCircEntry(a, b)
IsisCircEntry	**a;
IsisCircEntry	**b;
{
    if ((*a)->isisCircIndex < (*b)->isisCircIndex) return(-1);
    else if ((*a)->isisCircIndex > (*b)->isisCircIndex) return(1);
    else return(0);
}


int cmpISAdjEntry(a, b)
IsisISAdjEntry	**a;
IsisISAdjEntry	**b;
{
    if ((*a)->isisISAdjIndex < (*b)->isisISAdjIndex) return(-1);
    else if ((*a)->isisISAdjIndex > (*b)->isisISAdjIndex) return(1);
    else return(0);

}


int cmpISAdjAreaAddrEntry(a, b)
IsisISAdjAreaAddrEntry	**a;
IsisISAdjAreaAddrEntry	**b;
{

    return(cmpOctetString(&(*a)->isisISAdjAreaAddress, &(*b)->isisISAdjAreaAddress));

}

int cmpProtSuppEntry(a, b)
IsisSysProtSuppEntry	**a;
IsisSysProtSuppEntry	**b;
{
    if ((*a)->isisSysProtSuppProtocol < (*b)->isisSysProtSuppProtocol) return(-1);
    else if ((*a)->isisSysProtSuppProtocol > (*b)->isisSysProtSuppProtocol) return(1);
    else return(0);

}

int cmpL2SummAddrEntryi(a, b)
IsisL2SummAddrEntry	**a;
IsisL2SummAddrEntry	**b;
{
    if ((*a)->isisL2SummAddress < (*b)->isisL2SummAddress) return(-1);
    else if ((*a)->isisL2SummAddress > (*b)->isisL2SummAddress) return(1);
    else return(0);

}

int cmpL2SummAddrEntryj(a, b)
IsisL2SummAddrEntry	**a;
IsisL2SummAddrEntry	**b;
{
    if ((*a)->isisL2SummAddrMask < (*b)->isisL2SummAddrMask) return(-1);
    else if ((*a)->isisL2SummAddrMask > (*b)->isisL2SummAddrMask) return(1);
    else return(0);

}

int cmpAreaRecPwdEntry(a, b)
IsisAuthAreaRecPwdEntry	**a;
IsisAuthAreaRecPwdEntry	**b;
{

    return(cmpOctetString(&(*a)->isisAuthAreaRecPwd, &(*b)->isisAuthAreaRecPwd));

}

int cmpDomainRecPwdEntry(a, b)
IsisAuthDomainRecPwdEntry	**a;
IsisAuthDomainRecPwdEntry	**b;
{

    return(cmpOctetString(&(*a)->isisAuthDomainRecPwd, &(*b)->isisAuthDomainRecPwd));

}

int cmpPartRepEntry(a, b)
IsisPartRepEntry	**a;
IsisPartRepEntry	**b;
{
    if ((*a)->isisPartRepSysInstance < (*b)->isisPartRepSysInstance) return(-1);
    else if ((*a)->isisPartRepSysInstance > (*b)->isisPartRepSysInstance) return(1);
    else return(0);
}

int cmpPartAreaAddrEntry(a, b)
IsisPartAreaAddrEntry	**a;
IsisPartAreaAddrEntry	**b;
{

    return(cmpOctetString(&(*a)->isisPartAreaAddr, &(*b)->isisPartAreaAddr));

}

int cmpVirtAdjEntry(a, b)
IsisVirtAdjEntry	**a;
IsisVirtAdjEntry	**b;
{
    if ((*a)->isisVirtAdjIndex < (*b)->isisVirtAdjIndex) return(-1);
    else if ((*a)->isisVirtAdjIndex > (*b)->isisVirtAdjIndex) return(1);
    else return(0);
}

int cmpCircISEntry(a, b)
IsisCircISEntry	**a;
IsisCircISEntry	**b;
{
    if ((*a)->isisCircISIndex < (*b)->isisCircISIndex) return(-1);
    else if ((*a)->isisCircISIndex > (*b)->isisCircISIndex) return(1);
    else return(0);
}

int cmpCircAuthRecPwdEntry(a, b)
IsisCircAuthRecPwdEntry	**a;
IsisCircAuthRecPwdEntry	**b;
{

    return(cmpOctetString(&(*a)->isisCircAuthRecPwd, &(*b)->isisCircAuthRecPwd));

}

int cmpISAdjIPAddrEntry(a, b)
IsisISAdjIPAddrEntry	**a;
IsisISAdjIPAddrEntry	**b;
{
    if ((*a)->isisISAdjIPAddress < (*b)->isisISAdjIPAddress) return(-1);
    else if ((*a)->isisISAdjIPAddress > (*b)->isisISAdjIPAddress) return(1);
    else return(0);
}

int cmpISAdjProtSuppEntry(a, b)
IsisISAdjProtSuppEntry	**a;
IsisISAdjProtSuppEntry	**b;
{
    if ((*a)->isisISAdjProtSuppProtocol < (*b)->isisISAdjProtSuppProtocol) return(-1);
    else if ((*a)->isisISAdjProtSuppProtocol > (*b)->isisISAdjProtSuppProtocol) return(1);
    else return(0);
}

int cmpESAdjEntryi(a, b)
IsisESAdjEntry	**a;
IsisESAdjEntry	**b;
{
    if ((*a)->isisESAdjAdjIndex < (*b)->isisESAdjAdjIndex) return(-1);
    else if ((*a)->isisESAdjAdjIndex > (*b)->isisESAdjAdjIndex) return(1);
    else return(0);
}

int cmpESAdjEntryj(a, b)
IsisESAdjEntry	**a;
IsisESAdjEntry	**b;
{

    return(cmpOctetString(&(*a)->isisESAdjESID, &(*b)->isisESAdjESID));

}

int cmpRAEntry(a, b)
IsisRAEntry	**a;
IsisRAEntry	**b;
{
    if ((*a)->isisRAIndex < (*b)->isisRAIndex) return(-1);
    else if ((*a)->isisRAIndex > (*b)->isisRAIndex) return(1);
    else return(0);
}

int cmpIPRAEntry(a, b)
IsisIPRAEntry	**a;
IsisIPRAEntry	**b;
{
    if ((*a)->isisIPRAIndex < (*b)->isisIPRAIndex) return(-1);
    else if ((*a)->isisIPRAIndex > (*b)->isisIPRAIndex) return(1);
    else return(0);
}

/* 
**	Delete an entry from a table
*/
int queueDelete(pq, pentry)
Queue	*pq;
unsigned char *pentry;		/* ptr to entry to be deleted from table */
{
    int		i, found;
    unsigned char *temp;

    for (i = 0, found = FALSE; i < pq->nentries; ++i) {
    	if (pq->pentry[i] == pentry) {
	    found = TRUE;		/* found entry to be deleted */
	    break;
	}
    }

    if (found) {
	for (; i < pq->nentries; ++i) {
	    pq->pentry[i] = pq->pentry[i+1];
     	}
	--pq->nentries;
        pq->pentry[pq->nentries] = pentry;

	return(0);			/* deleted the entry from table */
    }
    else {
	return(-1);			/* didn't find the entry */

    }

} /* end of queueDelete() */



/*
**	Flush a table
*/
void queueFlush(pq)
Queue	*pq;
{
    int		i;

    pq->nentries = 0;

    switch (pq->mib) {
    case MIBSYSTEM:
	for (i = 0; i < pq->maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisMibTable *)pq)->isisMibEntry[i];

	break;

    case MIBMANAREAADDR:
	for (i = 0; i < pq->maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisManAreaAddrTable *)pq)->isisManAreaAddrEntry[i];

	break;

    case MIBAREAADDR:
	for (i = 0; i < pq->maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisAreaAddrTable *)pq)->isisAreaAddrEntry[i];

	break;

    case MIBCIRCUIT:
	for (i = 0; i < pq->maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisCircTable *)pq)->isisCircEntry[i];

	break;

    case MIBISADJ:
	for (i = 0; i < pq->maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisISAdjTable *)pq)->isisISAdjEntry[i];

	break;

    case MIBISADJAREAADDR:
	for (i = 0; i < pq->maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisISAdjAreaAddrTable *)pq)->isisISAdjAreaAddrEntry[i];

	break;

    case MIBPROTSUPP:
	for (i = 0; i < pq->maxentries; ++i) 
	    pq->pentry[i] = (unsigned char *)&((IsisSysProtSuppTable *)pq)->isisSysProtSuppEntry[i];

	break;

    defualt:
	break;

    }

} /* end of queueFlush() */



/*
**	Fresh an IS Adj Table entry by a gated isis AdjacencyEntry
*/
int freshISAdjEntry(pISAdjEntry, padj)
IsisISAdjEntry		*pISAdjEntry;
AdjacencyEntry		*padj;
{
    switch (padj->state) {
    case AdjInitializing:
	pISAdjEntry->isisISAdjState = 1; break;
    case AdjUp:
   	pISAdjEntry->isisISAdjState = 2; break;
    case AdjFailed:
	pISAdjEntry->isisISAdjState = 3; break;
    default:
	pISAdjEntry->isisISAdjState = 4; break;
    }

    copyOctetString(&pISAdjEntry->isisISAdjNeighSNPAAddress, padj->neighborMAC, 6);

    switch (padj->adjacencyType) {
    case Unknown: pISAdjEntry->isisISAdjNeighSysType = 1; break;
    case ES:	  pISAdjEntry->isisISAdjNeighSysType = 2; break;
    case IS:      pISAdjEntry->isisISAdjNeighSysType = 3; break;
    case L1IS:    pISAdjEntry->isisISAdjNeighSysType = 4; break;
    case L2IS:    pISAdjEntry->isisISAdjNeighSysType = 5; break;
    defualt:      pISAdjEntry->isisISAdjNeighSysType = 0; break;
    }

    copyOctetString(&pISAdjEntry->isisISAdjNeighSysID, padj->neighborSysID, 6);

    pISAdjEntry->isisISAdjUsage = 1;		/* unknown for now */

    pISAdjEntry->isisISAdjHoldTimer = padj->holdingTime;

    pISAdjEntry->isisISAdjNeighPriority = padj->LANPriority;


    return(0);

} /* end of freshISAdjEntry() */





/*
**	Fresh an IS Adj Area Address Table by a gated isis AdjacencyEntry.neighborInfo
*/
int freshISAdjAreaAddrTable(pISAdjEntry, padj)
IsisISAdjEntry		*pISAdjEntry;
AdjacencyEntry		*padj;
{
    int				i;
    IsisISAdjAreaAddrTable	*pISAdjAATable;
    IsisISAdjAreaAddrEntry	*pISAdjAAEntry;
    AreaAddrList		*pAAList;
    AreaAddr			*pAA;

    pISAdjAATable = &pISAdjEntry->isisISAdjAreaAddrTable;

    queueFlush(pISAdjAATable);

    if (padj->numIds) {		/* neighbor is ES */
	for (i = 0; i < padj->numIds; ++i) {
	    pISAdjAAEntry = (IsisISAdjAreaAddrEntry *)queueNew(pISAdjAATable);

	    if (pISAdjAAEntry) {
		copyOctetString(&pISAdjAAEntry->isisISAdjAreaAddress, 
				padj->neighborInfo+(6*i), 6          );
			       
		queueAdd(pISAdjAATable, pISAdjAAEntry);
	    }
	    else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("freshISAdjAreaAddrTable: cannot allocate IS adj area address Entry"));
		return(-1);

	    }
	}
    }
    else {			/* neighbor is IS */
	pAAList = (AreaAddrList *)padj->neighborInfo;

	for (i = 0; i < pAAList->count; ++i) {
	    pISAdjAAEntry = (IsisISAdjAreaAddrEntry *)queueNew(pISAdjAATable);

	    if (pISAdjAAEntry) {
		pAA = retrieveAreaAddr(pAAList->areaAddr[i]);
		copyOctetString(&pISAdjAAEntry->isisISAdjAreaAddress, 
							pAA->addr, pAA->len);
			       
		queueAdd(pISAdjAATable, pISAdjAAEntry);
	    }
	    else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("freshISAdjAreaAddrTable(): cannot allocate IS adj area address Entry"));
		return(-1);

	    }

      	}

    }

    return(0);

} /* end of freshISAdjAreaAddrTable() */



/*
**	Fresh an IS Adj IP Address Table by a gated isis AdjacencyEntry.ipaddrs
*/
int freshISAdjIPAddrTable(IsisISAdjEntry *pISAdjEntry,
		 	  AdjacencyEntry *padj	      )
{
    int				i;
    IsisISAdjIPAddrTable	*pISAdjIPAddrTable;
    IsisISAdjIPAddrEntry	*pISAdjIPAddrEntry;
    IPAddrList			*pIPList;

    pISAdjIPAddrTable = &pISAdjEntry->isisISAdjIPAddrTable;
    pIPList = &padj->ipaddrs;

    if (padj->numIds) {		/* neighbor is ES */
	;
    }
    else {			/* neighbor is IS */
	queueFlush(pISAdjIPAddrTable);

	for (i = 0; i < pIPList->cnt; ++i) {
	    pISAdjIPAddrEntry = (IsisISAdjIPAddrEntry *)queueNew(pISAdjIPAddrTable);

	    if (pISAdjIPAddrEntry) {
		pISAdjIPAddrEntry->isisISAdjIPAddress = pIPList->addrs[i].s_addr;
			       
		queueAdd(pISAdjIPAddrTable, pISAdjIPAddrEntry);
	    }
	    else {
		trace_log_tf(isis_trace_options,
			     0,
			     LOG_ERR,
			     ("freshISAdjIPAddrTable(): cannot allocate IS adj IP address Entry"));
		return(-1);

	    }

      	}

    }

    return(0);

} /* end of freshISAdjIPAddrTable() */




/*
**	Convert a dotted representation of IP address to its binary value
*/
void dot2binary(dotted, size, pbinary)
unsigned int 	dotted[];
int		size;			/* size of to be converted, letf justify */
IpAddress	*pbinary;
{
    int		i;

    for (i = 0, *pbinary = 0; i < size; ++i) {
        *pbinary <<= 8;
	*pbinary += dotted[i];
    }

    for (; i < 4; ++i) {
        *pbinary <<= 8;

    }

    return;

} /* end of dot2binary() */



/*
**	Convert a binary representation of IP address to its dotted value
*/
void binary2dot(binary, dotted)
IpAddress	binary;
unsigned int 	dotted[];
{
    int		i;
    unsigned char *pbyte;

    for (i = 0, pbyte = (unsigned char *)&binary; i < 4; ++i, ++pbyte) {
	dotted[i] = *pbyte;
    }

    return;

} /* end of binary2dot() */



/*
**	Convert the tail of an OID into the 20-byte net address
*/
void oid2net20(unsigned int	*poid,
	       OSINSAddress	*paddr,
	       int		size	)
{
    int		i;

    paddr->maxlen = 20;
    if (size > paddr->maxlen) size = paddr->maxlen;

    for (i = 0; i < size; ++i) {
	paddr->contents[i] = (u_char)(poid[i]);
    }
    paddr->len = size;

    return;

} /* end of oid2net20() */


/*
**	Convert the tail of an OID into Password
*/
void oid2password(unsigned int	*poid,
	          Password	*ppw,
	          int		size	)
{
    int		i;

    ppw->maxlen = 254;
    if (size > ppw->maxlen) size = ppw->maxlen;

    for (i = 0; i < size; ++i) {
	ppw->contents[i] = (u_char)(poid[i]);
    }
    ppw->len = size;

    return;

} /* end of oid2password() */



/*
**	Convert an octet string to oid elements
*/
void octetString2oid(LongOctetString *pstring,
		     unsigned int *poid       )		/* oid must have enough space */
{
    int		i;

    for (i = 0; i < pstring->len; ++i) {

	poid[i] = (unsigned int)(pstring->contents[i]);

    }

    return;


} /* end of octetString2oid() */




/* Routines used to access kernel memory */

/*
**	Initialize access to kernel memory
*/

int kmeminit()
{

    if ((kernel_fd = open(KMEM, O_RDONLY)) < 0) {
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("kmeminit(): cannot open %s, %m",
		      KMEM));
	return(-1);
    }

    return(0);

} /* end of kmeminit() */

/*
**	Locate kernel address of an exported kernel symbol
*/
int kmemlocate(symbol, paddr)
char 	*symbol;
char    **paddr;
{
    NLIST_T nlist={ 0 };

    nlist.n_name = symbol;
    *paddr = 0;
    if (knlist(&nlist, 1, sizeof(NLIST_T)) < 0) {
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("kmemlocate(): knlist(%s) failed: %m", 
		      symbol));
	return(-1);
    }
    
    *paddr = (char *) nlist.n_value;
    return(0);

} /* end of kmemlocate() */


/*
**	Read kernel memory into a local buffer
*/
int kmemread(from, to, length)
int 	from;
caddr_t to;
int	length;
{

    if (from == 0) return(-1);
    if (lseek(kernel_fd, from, SEEK_SET) != from) {
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("kmemread(): lseek() failed: %m"));
	return(-1);
    }

    if (read(kernel_fd, to, length) != length) {
	trace_log_tf(isis_trace_options,
		     0,
		     LOG_ERR,
		     ("kmemread(): read() failed: %m"));
	return(-1);
    }

    return(0);

} /* end of kmemread() */




/*
**	Locate a specific entry in the IP route table
*/
IsisIPDestEntry *locateIPRouteEntry(ipAddress, ipMask)
IpAddress	ipAddress;		/* destination ip address */
IpAddress	ipMask;			/* its mask */
{
    u_long 		addrRTree;
    RadixNodeHead	rNHead, *prNHead;
    RouteTreeEntry	routeTreeEntry;
    IsisIPDestEntry	*pIPRouteEntry=0;

    if (kmemlocate("radix_node_head", &addrRTree)) {
	return(0);
    }

    if (kmemread(addrRTree, &prNHead, sizeof prNHead)) {
	return(0);
    }

    /* Scan thru radix node heads for proper address family */
    for (; prNHead; prNHead = rNHead.rnh_next) {
    	if (kmemread(prNHead, &rNHead, sizeof rNHead)) {
	    return(0);
	}

	if (rNHead.rnh_af != AF_INET) continue;
	/* Address family is IP */

	pIPRouteEntry = &isisMibTable.isisIPDestEntry;
 	pIPRouteEntry->isisIPRouteDest = ipAddress;
 	pIPRouteEntry->isisIPRouteMask = ipMask;
 	pIPRouteEntry->isisIPRouteMetTOS = 0;
 	pIPRouteEntry->isisIPRouteForw.oid_nelem = 0;

trace_tf(isis_trace_options, TR_NORMAL, 0, ("locateIPRouteEntry: ipAddr=%x, ipMask=%x", ipAddress,ipMask));

	if (searchIPRouteEntry(rNHead.rnh_treetop, pIPRouteEntry)) {
	    break;			/* found the route entry */
	}
	else {
	    pIPRouteEntry = 0;		/* didn't find one in this tree */
	}
    }

    return(pIPRouteEntry);

} /* end of locateIPRouteEntry() */


/*
**	Search a specific IP route entry
*/
static	RouteTreeEntry routeTreeEntry;		/* so it does not take up stack */

int searchIPRouteEntry(prNode, pIPDestEntry)
RadixNode		*prNode;		/* what to be looked at */
IsisIPDestEntry		*pIPDestEntry;		/* what we are looking for */
{
    RadixNode	rNode;
    SockAddrIn	key, mask;
    int		found=FALSE;		/* rNode contains the found node */

    /* Read the pointed radix node from kernel */
    if (kmemread(prNode, &rNode, sizeof rNode)) return(0);

    if (rNode.rn_b < 0) {			/* a leaf node */

trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchIPRouteEntry: read a leaf: b=%d, bmask=%x, flags=%x, pkey=%x, pmask=%x, dupkey=%x", rNode.rn_b, rNode.rn_bmask, rNode.rn_flags, rNode.rn_key, rNode.rn_mask, rNode.rn_dupedkey));

	if (rNode.rn_flags & RNF_ROOT) {	/* a leaf marked 'root' */
	    /* A leaf node marked RNF_ROOT serves as a leaf node with the lowerst */
	    /* key (0x00000000) or the highest key (0xffffffff) so that all the */
	    /* other leaf nodes are situated in between the two. */
	    ;			/* no point to look at */
	}
	else {
	    do {
		/* Get the key of this leaf node */
	        if (kmemread(rNode.rn_key, &key, sizeof key) == 0) {

trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchIPRouteEntry: read a key=%x at %x", 
							key.sin_addr.s_addr,
							rNode.rn_key        ));

		    if (key.sin_addr.s_addr == pIPDestEntry->isisIPRouteDest) {

	     	    	/* Get the mask of this leaf */	    
	    	        if (kmemread(rNode.rn_mask, &mask, sizeof mask)) {
			    /* Mask is not specified or read failed */
	
			    mask.sin_addr.s_addr = 0xffffffff;
			}
		 	else {
			    if (mask.sin_addr.s_addr == 0) {
				/* Read a 0 mask */
			        mask.sin_addr.s_addr = 0xffffffff;
			    }
			}

trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchIPRouteEntry: read a mask=%x at %x for key=%x at %x", 
					    mask.sin_addr.s_addr,
					    rNode.rn_mask, 
					    key.sin_addr.s_addr, rNode.rn_key));

            	        if (mask.sin_addr.s_addr == pIPDestEntry->isisIPRouteMask) {
			    found = TRUE;
			    break;
		    	}
		    } /* end of a matching key */

		} /* end of a good key read */

	    } while (kmemread(prNode=rNode.rn_dupedkey, &rNode, sizeof rNode) == 0);

	} /* end of leaf node, with possible duplicates */
    }
    else {	/* not a leaf node */

	/* Guided by the bit mask */

trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchIPRouteEntry: read a nonleaf: b=%d, bmask=%x, flags=%x, Off=%d, L=%x, R=%x", rNode.rn_b, rNode.rn_bmask, rNode.rn_flags, rNode.rn_off, rNode.rn_l, rNode.rn_r));

	/* Just a exhausting depth-first search */
	if (searchIPRouteEntry(rNode.rn_l, pIPDestEntry) ||
	    searchIPRouteEntry(rNode.rn_r, pIPDestEntry)   )
	    return(1);
	else
	    return(0);

    }

    if (!found) return(0);

    /* rNode is the node found, pointed to by prNode in kernel */

    /* Get the route tree entry from kernel */
    if (kmemread(prNode, &routeTreeEntry, sizeof routeTreeEntry)) return(0);

    /* Find the info needed from the route tree entry */

    pIPDestEntry->isisIPRouteMetTOS = 0;			/* part of index */
    pIPDestEntry->isisIPRouteMetType = -1;
    pIPDestEntry->isisIPRouteIntMetric = -1;
    pIPDestEntry->isisIPRouteExtMetric = -1;
    pIPDestEntry->isisIPRouteForw.oid_nelem = 0;		/* part of index */
    pIPDestEntry->isisIPRouteSource = -1;
    pIPDestEntry->isisIPRouteSysInstance = 1;

    return(1);

} /* end of searchIPRouteEntry() */




/*
**	Locate a specific entry in the IP route table.  If not found, locate
**	the closest next entry in the table if one exists.
**
*/
IsisIPDestEntry *locateClosestIPRouteEntry(ipAddress, ipMask)
IpAddress	ipAddress;		/* destination ip address */
IpAddress	ipMask;			/* its mask */
{
    u_long 		addrRTree;
    RadixNodeHead	rNHead, *prNHead;
    /* RouteTreeEntry	routeTreeEntry; */
    IsisIPDestEntry	*pIPRouteEntry=0;

    if (kmemlocate("radix_node_head", &addrRTree)) {
	return(0);
    }

    if (kmemread(addrRTree, &prNHead, sizeof prNHead)) {
	return(0);
    }

    /* Scan thru radix node heads for proper address family */
    for (; prNHead; prNHead = rNHead.rnh_next) {
    	if (kmemread(prNHead, &rNHead, sizeof rNHead)) {
	    return(0);
	}

	if (rNHead.rnh_af != AF_INET) continue;
	/* Address family is IP */

	pIPRouteEntry = &isisMibTable.isisIPDestEntry;
 	pIPRouteEntry->isisIPRouteDest = ipAddress;
 	pIPRouteEntry->isisIPRouteMask = ipMask;
 	pIPRouteEntry->isisIPRouteMetTOS = 0;
 	pIPRouteEntry->isisIPRouteForw.oid_nelem = 0;

trace_tf(isis_trace_options, TR_NORMAL, 0, ("locateClosestIPRouteEntry: ipAddr=%x, ipMask=%x", ipAddress,ipMask));

	if (searchClosestIPRouteEntry(rNHead.rnh_treetop, pIPRouteEntry)) {
	    break;			/* found the route entry */
	}
	else {
	    pIPRouteEntry = 0;		/* didn't find one in this tree */
	}
    }

    return(pIPRouteEntry);


} /* end of locateClosestIPRouteEntry() */


/*
**	Search a specified IP route entry.  If not found, return the next
**	closest entry.
*/

int searchClosestIPRouteEntry(prNode, pIPDestEntry)
RadixNode		*prNode;		/* what to be looked at */
IsisIPDestEntry		*pIPDestEntry;		/* what we are looking for */
{
    RadixNode	rNode;
    SockAddrIn	key, mask;
    IpAddress	maskImplied=0;
    int		found=FALSE;		/* rNode contains the found node */

    /* Read the pointed radix node from kernel */
    if (kmemread(prNode, &rNode, sizeof rNode)) return(0);

    if (rNode.rn_b < 0) {			/* a leaf node */

trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchClosestIPRouteEntry: read a leaf: b=%d, bmask=%x, flags=%x, pkey=%x, pmask=%x, dupkey=%x", rNode.rn_b, rNode.rn_bmask, rNode.rn_flags, rNode.rn_key, rNode.rn_mask, rNode.rn_dupedkey));

	if (rNode.rn_flags & RNF_ROOT) {	/* a leaf marked 'root' */
	    /* A leaf node marked RNF_ROOT serves as a leaf node with the lowerst */
	    /* key (0x00000000) or the highest key (0xffffffff) so that all the */
	    /* other leaf nodes are situated in between the two. */
	    ;			/* no point to look at */
	}
	else {
	    do {
		/* Get the key of this leaf node */
	        if (kmemread(rNode.rn_key, &key, sizeof key) == 0) {

trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchClosestIPRouteEntry: read a key=%x at %x", 
							key.sin_addr.s_addr,
							rNode.rn_key        ));

		    /* Examine the mask implied by the key (IP address) in node */
		    if (key.sin_addr.s_addr & 0x80000000) 
		        if (key.sin_addr.s_addr & 0x40000000) {
			    maskImplied = 0xffffff00;	/* Class C */
			}
			else {
			    maskImplied = 0xffff0000;	/* Class B */
			}
		    else {
			maskImplied = 0xff000000;	/* Class A */
		    }

		    /* The query mask may need repair */
		    if ((pIPDestEntry->isisIPRouteMask & maskImplied) != maskImplied) {
			pIPDestEntry->isisIPRouteMask |= maskImplied;
trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchClosestIPRouteEntry: repaired mask=%x",
						pIPDestEntry->isisIPRouteMask));
		    }

		    /* Need to compare the queried mask with the mask in node. */

	    	    if (key.sin_addr.s_addr >= pIPDestEntry->isisIPRouteDest) {
trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchClosestIPRouteEntry: matched key"));			
		     	    /* Get the mask of this leaf */	    
	    	        if (kmemread(rNode.rn_mask, &mask, sizeof mask)) {
			        /* Mask is not specified or read failed */

			        mask.sin_addr.s_addr = 0xffffffff;
			}
			else {
			    if (mask.sin_addr.s_addr == 0) {
			        mask.sin_addr.s_addr = 0xffffffff;
			    }
			}

trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchClosestIPRouteEntry: read a mask=%x at %x for key=%x at %x", 
						mask.sin_addr.s_addr,
					        rNode.rn_mask, 
					  	key.sin_addr.s_addr, rNode.rn_key    ));


	            	if (mask.sin_addr.s_addr >= pIPDestEntry->isisIPRouteMask) {

trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchClosestIPRouteEntry: matched mask"));			
			    pIPDestEntry->isisIPRouteDest = key.sin_addr.s_addr;
			    pIPDestEntry->isisIPRouteMask = mask.sin_addr.s_addr;
			    found = TRUE;
			    break;
		    	}
trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchClosestIPRouteEntry: going to the next node"));
		        /* The 'smallest' mask for the next leaf */
			pIPDestEntry->isisIPRouteMask = 0xff000000;

		    } /* end of a matching key */

		} /* end of a good key read */

	    } while (kmemread(prNode=rNode.rn_dupedkey, &rNode, sizeof rNode) == 0);

	} /* end of leaf node, with possible duplicates */
    }
    else {	/* not a leaf node */

	/* Guided by the bit mask */

trace_tf(isis_trace_options, TR_NORMAL, 0, ("searchClosestIPRouteEntry: read a nonleaf: b=%d, bmask=%x, flags=%x, Off=%d, L=%x, R=%x", rNode.rn_b, rNode.rn_bmask, rNode.rn_flags, rNode.rn_off, rNode.rn_l, rNode.rn_r));

	/* Just a exhausting depth-first search */
	if (searchClosestIPRouteEntry(rNode.rn_l, pIPDestEntry) ||
	    searchClosestIPRouteEntry(rNode.rn_r, pIPDestEntry)   )
	    return(1);
	else
	    return(0);

    }

    if (!found) return(0);

    /* rNode is the node found, pointed to by prNode in kernel */

    /* Get the route tree entry from kernel */
    if (kmemread(prNode, &routeTreeEntry, sizeof routeTreeEntry)) return(0);

    /* Find the info needed from the route tree entry */

    pIPDestEntry->isisIPRouteMetTOS = 0;			/* part of index */
    pIPDestEntry->isisIPRouteMetType = -1;
    pIPDestEntry->isisIPRouteIntMetric = -1;
    pIPDestEntry->isisIPRouteExtMetric = -1;
    pIPDestEntry->isisIPRouteForw.oid_nelem = 0;		/* part of index */
    pIPDestEntry->isisIPRouteSource = -1;
    pIPDestEntry->isisIPRouteSysInstance = 1;

    return(1);

} /* end of searchClosestIPRouteEntry() */




/*
**	Increment a byte stream by 1
*/
int incByteStream(LongOctetString *pstream)
{
    int		i;

    for (i = pstream->len; i != 0; --i) {

	if (++pstream->contents[i-1]) break;

    }

    if (i) return(0);	/* carry=0 */
    else {
	if (pstream->len == pstream->maxlen) return(1);	/* carry=1 */
	else {
	    pstream->contents[pstream->len++] = 0x01;
	    return(0);	/* carry=0 */
	}
    }

} /* end of incByteStream() */







#endif	/* defined(PROTO_SNMP) */





/* end of isis_mib_tables.c */






