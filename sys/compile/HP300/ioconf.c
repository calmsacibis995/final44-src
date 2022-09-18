#include "sys/param.h"
#include "sys/buf.h"
#include "sys/map.h"

#include "hp/dev/device.h"


#define C (caddr_t)
#define D (struct driver *)

extern struct driver hpibdriver;
extern struct driver hpibdriver;
extern struct driver hpibdriver;
extern struct driver rddriver;
extern struct driver rddriver;
extern struct driver rddriver;
extern struct driver rddriver;
extern struct driver ctdriver;
extern struct driver ctdriver;
extern struct driver scsidriver;
extern struct driver scsidriver;
extern struct driver scsidriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver sddriver;
extern struct driver stdriver;
extern struct driver stdriver;
extern struct driver ledriver;
extern struct driver ledriver;
extern struct driver dcadriver;
extern struct driver dcmdriver;
extern struct driver dcmdriver;
extern struct driver dcmdriver;
extern struct driver dcmdriver;
extern struct driver grfdriver;
extern struct driver grfdriver;
extern struct driver grfdriver;

struct hp_ctlr hp_cinit[] = {
/*	driver,		unit,	alive,	addr,	flags */
	{ &hpibdriver,	0,	0,	C 0x7,	0x0 },
	{ &hpibdriver,	1,	0,	C 0x0,	0x0 },
	{ &hpibdriver,	2,	0,	C 0x0,	0x0 },
	{ &scsidriver,	0,	0,	C 0x0,	0x0 },
	{ &scsidriver,	1,	0,	C 0x0,	0x0 },
	{ &scsidriver,	2,	0,	C 0x0,	0x0 },
	0
};

struct hp_device hp_dinit[] = {
/*driver,	cdriver,	unit,	ctlr,	slave,	addr,	dk,	flags*/
{ &rddriver,	&hpibdriver,	0,	-1,	-1,	C 0x0,	1,	0x0 },
{ &rddriver,	&hpibdriver,	1,	-1,	-1,	C 0x0,	1,	0x0 },
{ &rddriver,	&hpibdriver,	2,	-1,	-1,	C 0x0,	1,	0x0 },
{ &rddriver,	&hpibdriver,	3,	-1,	-1,	C 0x0,	1,	0x0 },
{ &ctdriver,	&hpibdriver,	0,	0,	-1,	C 0x0,	0,	0x0 },
{ &ctdriver,	&hpibdriver,	1,	0,	-1,	C 0x0,	0,	0x0 },
{ &sddriver,	&scsidriver,	0,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	1,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	2,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	3,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	4,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	5,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	6,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	7,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	8,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	9,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	10,	-1,	-1,	C 0x0,	1,	0x0 },
{ &sddriver,	&scsidriver,	11,	-1,	-1,	C 0x0,	1,	0x0 },
{ &stdriver,	&scsidriver,	0,	-1,	-1,	C 0x0,	0,	0x0 },
{ &stdriver,	&scsidriver,	1,	-1,	-1,	C 0x0,	0,	0x0 },
{ &ledriver,	D 0x0,		0,	-1,	-1,	C 0x0,	0,	0x0 },
{ &ledriver,	D 0x0,		1,	-1,	-1,	C 0x0,	0,	0x0 },
{ &dcadriver,	D 0x0,		0,	-1,	-1,	C 0x9,	0,	0x1 },
{ &dcmdriver,	D 0x0,		0,	-1,	-1,	C 0x0,	0,	0xe },
{ &dcmdriver,	D 0x0,		1,	-1,	-1,	C 0x0,	0,	0x0 },
{ &dcmdriver,	D 0x0,		2,	-1,	-1,	C 0x0,	0,	0xe },
{ &dcmdriver,	D 0x0,		3,	-1,	-1,	C 0x0,	0,	0xe },
{ &grfdriver,	D 0x0,		0,	-1,	-1,	C 0x0,	0,	0x0 },
{ &grfdriver,	D 0x0,		1,	-1,	-1,	C 0x0,	0,	0x0 },
{ &grfdriver,	D 0x0,		2,	-1,	-1,	C 0x0,	0,	0x0 },
0
};

#include <sys/device.h>

extern void slattach __P((int));
extern void bpfilterattach __P((int));
extern void ptyattach __P((int));
extern void loopattach __P((int));
extern void etherattach __P((int));
extern void iteattach __P((int));
extern void vnattach __P((int));

#include <sys/systm.h> /* XXX */
#define etherattach (void (*)__P((int)))nullop
#define iteattach (void (*) __P((int)))nullop

struct pdevinit pdevinit[] = {
	{ slattach, 4 },
	{ bpfilterattach, 16 },
	{ ptyattach, 1 },
	{ loopattach, 1 },
	{ etherattach, 1 },
	{ iteattach, 1 },
	{ vnattach, 1 },
	{ 0, 0 }
};
