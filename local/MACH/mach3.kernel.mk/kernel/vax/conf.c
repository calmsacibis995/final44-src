/* 
 * Mach Operating System
 * Copyright (c) 1993-1988 Carnegie Mellon University
 * All Rights Reserved.
 * 
 * Permission to use, copy, modify and distribute this software and its
 * documentation is hereby granted, provided that both the copyright
 * notice and this permission notice appear in all copies of the
 * software, derivative works or modified versions, and any portions
 * thereof, and that both notices appear in supporting documentation.
 * 
 * CARNEGIE MELLON ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS"
 * CONDITION.  CARNEGIE MELLON DISCLAIMS ANY LIABILITY OF ANY KIND FOR
 * ANY DAMAGES WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
 * 
 * Carnegie Mellon requests users of this software to return to
 * 
 *  Software Distribution Coordinator  or  Software.Distribution@CS.CMU.EDU
 *  School of Computer Science
 *  Carnegie Mellon University
 *  Pittsburgh PA 15213-3890
 * 
 * any improvements or extensions that they make and grant Carnegie Mellon
 * the rights to redistribute these changes.
 */

/*
 * HISTORY
 * $Log:	conf.c,v $
 * Revision 2.12  93/05/19  12:41:09  rvb
 * 	Type casts, etc to quiet gcc 2.3.3 warnings
 * 	[93/05/18            rvb]
 * 
 * Revision 2.11  93/02/05  08:18:04  danner
 * 	Fix includes.
 * 	[93/02/04            danner]
 * 
 * Revision 2.10  92/02/23  22:45:45  elf
 * 	Added/modified the get_status routines for a number of disks.
 * 	[92/02/22  19:01:10  af]
 * 
 * Revision 2.9  91/08/28  11:17:47  jsb
 * 	Added entries for new dev_info field.
 * 	[91/08/27  17:57:06  jsb]
 * 
 * Revision 2.8  91/08/24  12:29:48  af
 * 	Generic console.
 * 	[91/08/02  04:30:46  af]
 * 
 * Revision 2.7  91/07/31  18:18:11  dbg
 * 	Correct an '#ifdef' to an '#if'.
 * 	[91/07/30  17:22:22  dbg]
 * 
 * Revision 2.6  91/06/20  11:38:49  rvb
 * 	X support
 * 	[91/06/18  21:36:41  rvb]
 * 
 * 	Support for VaxStation 3100: devices like DEC Station 3100
 * 	[91/06/04            rvb]
 * 
 * Revision 2.5  91/05/14  17:41:56  mrt
 * 	Correcting copyright
 * 
 * Revision 2.4  91/05/08  13:14:34  dbg
 * 	Changed to new copyright.
 * 	[91/04/25            dbg]
 * 
 * Revision 2.3  90/01/11  11:45:06  dbg
 * 	Add ni device.
 * 	[89/11/20            dbg]
 * 
 * Revision 2.2  89/08/09  14:33:26  rwd
 * 	Added time device
 * 	[89/08/08            rwd]
 * 
 * Revision 2.1  89/08/03  16:12:25  rwd
 * Created.
 * 
 * 12-May-89  David Golub (dbg) at Carnegie-Mellon University
 *	Made console serial line (former 'qs') unconditional.  Added
 *	indirection entry for console, initially set to serial line.
 *
 * 27-Apr-89  David Golub (dbg) at Carnegie-Mellon University
 *	Conditionalized 'qs' (console serial line) under either QD or QV.
 *
 * 12-Apr-89  David Golub (dbg) at Carnegie-Mellon University
 *	Added port_death routines.
 *
 * 24-Aug-88  David Golub (dbg) at Carnegie-Mellon University
 *	Created.
 *
 */

/*
 * Device switch for VAX.
 */

#include <mach/machine/vm_types.h>
#include <device/conf.h>

extern vm_offset_t block_io_mmap();

#include <hp.h>
#if NHP > 0
int	hpopen(),hpread(),hpwrite(),hpgetstat();
#define	hpname		"hp"
#endif

#include <tu.h>
#if NHT > 0
int	htopen(),htclose(),htread(),htwrite(),htioctl();
#define	htname		"tu"
#endif

#include <rk.h>
#if NHK > 0
int	rkopen(),rkread(),rkwrite(),rkgetstat(),rkreset();
#define	rkname		"rk"
#endif

#include <ra.h>
#if NUDA > 0
int	udopen(),udread(),udwrite(),udgetstat(),udreset();
#define	udname		"ra"
#endif

#include <scsi.h>
#if NSCSI > 0
int     rz_open(), rz_close(), rz_read(), rz_write();
int     rz_get_status(), rz_set_status();
#define rzname "rz"
#define tzname "tz"
#endif

int	cnopen(),cnclose(),cnread(),cnwrite(),cngetstat(),cnsetstat(),
	cnportdeath();
#define	cnname		"sl"

extern int timeopen(),timeclose();
extern vm_offset_t timemmap();
#define timename	"time"

#include <dz.h>
#if NDZ > 0
int	dzopen(),dzclose(),dzread(),dzwrite(),dzgetstat(),dzsetstat(),
	dzreset(),dzportdeath();
#define	dzname		"dz"
#endif

#include <qv.h>
#if NQV > 0
int	qvopen(),qvclose(),qvread(),qvwrite(),qvgetstat(),qvsetstat(),
	qvreset(),qvportdeath();
vm_offset_t qvmap();
#define	qvname		"qv"
#endif

#include <qd.h>
#if	NQD > 0
int	qdopen(),qdclose(),qdread(),qdwrite(),qdgetstat(),qdsetstat(),
	qdreset(),qdportdeath();
#define	qdname		"qd"
#endif

#include <qe.h>
#if	NQE > 0
int	qeopen(),qeoutput(),qegetstat(),qesetstat(),qeallreset(),
	qesetinput();
#define	qename		"qe"
#endif

#include <de.h>
#if	NDE > 0
int	deopen(),deoutput(),degetstat(),desetstat(),deallreset(),
	desetinput();
#define	dename		"de"
#endif

#include <ni.h>
#if	NNI > 0
int	niopen(),nioutput(),nigetstat(),nisetstat(),
	nisetinput();
#define	niname		"ni"
#endif

#include <constty.h>
#if	NCONSTTY > 0
int	cons_open(),cons_close(),cons_read(),cons_write(),
	cons_get_status(),cons_set_status(), cons_portdeath();
vm_offset_t	screen_mmap();
#define	cons_name		"dz_"
#endif

#include <ln.h>
#if	NLN > 0
int	se_open(), se_output(), se_get_status(), se_set_status(),
	se_setinput(), se_restart();
#define se_name "se"
#endif

/*
 * List of devices - console must be at slot 0
 */
struct dev_ops	dev_name_list[] =
{
	/*name,		open,		close,		read,
	  write,	getstat,	setstat,	mmap,
	  async_in,	reset,		port_death,	subdev,
	  dev_info */

	{ cnname,	cnopen,		cnclose,	cnread,
	  cnwrite,	cngetstat,	cnsetstat,	nomap,
	  nodev,	nulldev,	cnportdeath,	0,
	  nodev },

#if	NCONSTTY > 0
	{ cons_name,	cons_open,	cons_close,	cons_read,
	  cons_write,	cons_get_status,cons_set_status,screen_mmap,
	  nodev,	nulldev,	cons_portdeath,	4,
	  nodev },
#endif
	{ timename,	timeopen,	timeclose,	nulldev,
	  nulldev,	nulldev,	nulldev,	timemmap,
	  nodev,	nulldev,	nulldev,	0,
	  nodev },

#if	NHP > 0
	{ hpname,	hpopen,		nulldev,	hpread,
	  hpwrite,	hpgetstat,	nulldev,	block_io_mmap,
	  nodev,	nulldev,	nulldev,	8,
	  nodev },
#endif
#if	NHT > 0
	{ htname,	htopen,		htclose,	htread,
	  htwrite,	htioctl,	nulldev,	nomap,
	  nodev,	nulldev,	nulldev,	0,
	  nodev },
#endif
#if	NHK > 0
	{ rkname,	rkopen,		nulldev,	rkread,
	  rkwrite,	rkgetstat,	nulldev,	block_io_mmap,
	  nodev,	rkreset,	nulldev,	8,
	  nodev },
#endif
#if	NUDA > 0
	{ udname,	udopen,		nulldev,	udread,
	  udwrite,	udgetstat,	nulldev,	block_io_mmap,
	  nodev,	udreset,	nulldev,	8,
	  nodev },
#endif
#if	NSCSI > 0
        { rzname,       rz_open,        rz_close,       rz_read,
          rz_write,     rz_get_status,  rz_set_status,  block_io_mmap,
          nodev,        nulldev,        nulldev,        8,
	  nodev },

        { tzname,       rz_open,        rz_close,       rz_read,
          rz_write,     rz_get_status,  rz_set_status,  nomap,
          nodev,        nulldev,        nulldev,        8,
	  nodev },
#endif
#if	NDZ > 0
	{ dzname,	dzopen,		dzclose,	dzread,
	  dzwrite,	dzgetstat,	dzsetstat,	nomap,
	  nodev,	dzreset,	dzportdeath,	0,
	  nodev },
#endif
#if	NQV > 0
	{ qvname,	qvopen,		qvclose,	qvread,
	  qvwrite,	qvgetstat,	qvsetstat,	qvmap,
	  nodev,	qvreset,	qvportdeath,	4,
	  nodev },
#endif
#if	NQD > 0
	{ qdname,	qdopen,		qdclose,	qdread,
	  qdwrite,	qdgetstat,	qdsetstat,	nomap,
	  nodev,	qdreset,	qdportdeath,	4,
	  nodev },
#endif
#if	NQE > 0
	{ qename,	qeopen,		nulldev,	nodev,
	  qeoutput,	qegetstat,	qesetstat,	nomap,
	  qesetinput,	qeallreset,	nulldev,	0,
	  nodev },
#endif
#if	NDE > 0
	{ dename,	deopen,		nulldev,	nodev,
	  deoutput,	degetstat,	desetstat,	nomap,
	  desetinput,	deallreset,	nulldev,	0,
	  nodev },
#endif
#if	NNI > 0
	{ niname,	niopen,		nulldev,	nodev,
	  nioutput,	nigetstat,	nisetstat,	nomap,
	  nisetinput,	nulldev,	nulldev,	0,
	  nodev },
#endif
#if	NLN > 0
	{ se_name,	se_open,	nulldev,	nodev,
	  se_output,	se_get_status,	se_set_status,	nomap,
	  se_setinput,	se_restart,	nulldev,	0,
	  nodev },
#endif
};
int	dev_name_count = sizeof(dev_name_list)/sizeof(dev_name_list[0]);

/*
 * Indirect list.
 */
struct dev_indirect dev_indirect_list[] = {

	/* console */
	{ "console",	&dev_name_list[0],	0 }
};
int	dev_indirect_count = sizeof(dev_indirect_list)
				/sizeof(dev_indirect_list[0]);
