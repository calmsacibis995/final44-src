h01434
s 00000/00000/00128
d D 8.1 93/06/06 16:28:37 bostic 3 2
c 4.4BSD snapshot (revision 8.1)
e
s 00006/00002/00122
d D 4.2 91/04/16 16:48:23 bostic 2 1
c new copyright; att/bsd/shared
e
s 00124/00000/00000
d D 4.1 83/02/11 15:43:56 rrh 1 0
c date and time created 83/02/11 15:43:56 by rrh
e
u
U
t
T
I 2
/*-
 * %sccs.include.proprietary.c%
 */

E 2
I 1
#ifndef lint
D 2
static char sccsid[] = "%W%	(Berkeley)	%G%";
#endif not lint
E 2
I 2
static char sccsid[] = "%W% (Berkeley) %G%";
#endif /* not lint */
E 2

#include <stdio.h>
#include "def.h"

char *typename[TYPENUM]	= {"STLNVX",	"IFVX",		"DOVX",		"IOVX",	"FMTVX",
			"COMPVX",	"ASVX",		"ASGOVX",	"LOOPVX",	"WHIVX",
			"UNTVX",	"ITERVX",	"THENVX",	"STOPVX",	"RETVX",
			"DUMVX",	"GOVX",		"BRKVX",	"NXTVX",	"SWCHVX",
			"ACASVX",	"ICASVX"
	};
int hascom[TYPENUM]	= {2,		2,		2,		2,		2,
			2,		2,		2,		0,		0,
			0,		0,		2,		0,		0,
			0,		0,		0,		0,		2,
			2,		0
			};

int nonarcs[TYPENUM]  	= {FIXED+3,   	FIXED+4,	FIXED+2,	FIXED+3, 	FIXED+2,
			FIXED+2,	FIXED+2,	FIXED+2,	FIXED+1,	FIXED+1,
			FIXED+1,	FIXED+4,	FIXED+3,	FIXED,		FIXED,
			FIXED+2,	FIXED+1,	FIXED + 1,	FIXED + 1,	FIXED+3,
			FIXED+4,	FIXED+2
			};

int childper[TYPENUM]	= {0,	2,	1,	0,	0,
			0,	0,	0,	1,	1,
			1,	1,	1,	0,	0,
			1,	0,	0,	0,	1,
			2,	1
			};

int arcsper[TYPENUM]	= {1,		2,		2,	3,	0,
			-(FIXED+1),	1,	-(FIXED+1),	1,	1,
			1,		1,		2,	0,	0,
			-FIXED,		1,	1,		1,	-(FIXED+1),
			2,		1
			};

VERT *arc(v,i)
VERT v;
int i;
	{
	ASSERT(DEFINED(v),arc);
	ASSERT(0 <= i && i < ARCNUM(v), arc);
	return(&graph[v][nonarcs[NTYPE(v)] + i ]);
	}

VERT *lchild(v,i)
VERT v; int i;
	{
	ASSERT(DEFINED(v),lchild);
	ASSERT(0 <= i && i < childper[NTYPE(v)],lchild);
	return(&graph[v][nonarcs[NTYPE(v)]-i-1]);
	}

int *vxpart(v,type,j)
VERT v;
int type,j;
	{
	ASSERT((NTYPE(v) == type) && (0 <= j) && (j < nonarcs[type] - FIXED), vxpart);
	return(&graph[v][FIXED+j]);
	}

int *expres(v)
VERT v;
	{
	int ty;
	ty = NTYPE(v);
	ASSERT(ty == COMPVX || ty == ASGOVX || ty == ASVX || ty == SWCHVX || ty == ICASVX,expres);
	return(&graph[v][FIXED]);
	}

int *negpart(v)
VERT v;
	{
	ASSERT(NTYPE(v) == IFVX || NTYPE(v) == ACASVX,negpart);
	return(&graph[v][FIXED+1]);
	}

int *predic(v)
VERT v;
	{
	ASSERT(NTYPE(v) == IFVX || NTYPE(v) == ACASVX, predic);
	return(&graph[v][FIXED]);
	}

int *level(v)
VERT v;
	{
	ASSERT(NTYPE(v) == GOVX || NTYPE(v) == BRKVX || NTYPE(v) == NXTVX, level);
	return(&graph[v][FIXED]);
	}
int *stlfmt(v,n)
VERT v;
int n;
	{
	ASSERT(NTYPE(v) == STLNVX || NTYPE(v) == FMTVX,stlfmt);
	return(&graph[v][FIXED + n]);
	}

create(type,arcnum)
int type, arcnum;
	{
	int i, *temp, wds;
	if (nodenum >= maxnode)
		{
		maxnode += 100;
		temp=realloc(graph,maxnode*sizeof(*graph));
		free(graph);
		graph=temp;
		}
	wds = nonarcs[type] + arcnum;
	graph[nodenum] = galloc(sizeof(*graph) * wds);
	for (i = 0; i < wds; i++)  graph[nodenum][i] = 0;
	NTYPE(nodenum) = type;
	if (arcsper[type] < 0)
		ARCNUM(nodenum) = arcnum;
	
	return(nodenum++);
	}

E 1
