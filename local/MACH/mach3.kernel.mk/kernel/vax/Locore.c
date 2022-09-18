/* 
 * Mach Operating System
 * Copyright (c) 1988 Carnegie-Mellon University
 * All rights reserved.  The CMU software License Agreement specifies
 * the terms and conditions for use and redistribution.
 */
/*
 * HISTORY
 * $Log:	Locore.c,v $
 * Revision 2.2  91/06/19  11:59:48  rvb
 * 	cputypes.h->platforms.h
 * 	[91/06/12  13:57:39  rvb]
 * 
 * 	Support for VaxStation 3100: cvax like VAX6x0
 * 	[91/06/04            rvb]
 * 
*/
#include <cpus.h>
#include <platforms.h>
#include <mba.h>
#include <uba.h>
#include <bi.h>
#include <mach_load.h>
#include <mach_mpm.h>

#include <mach/boolean.h>
#include <kern/lock.h>
#include <kern/thread.h>

#include <vax/pmap.h>	/* cpu_set */
#include <mach/vax/vm_param.h>

#include <vaxuba/ubareg.h>
#include <vaxuba/ubavar.h>

/*
 *	Definitions of assembler routines, for lint.
 */
/*ARGSUSED*/
int	badaddr(addr, len)
	char	*addr;
	int	len;
{
	return (0);
}

/*ARGSUSED*/
int	copyin(from, to, len)
	char	*from;
	char	*to;
	unsigned int	len;
{
	return (0);
}

/*ARGSUSED*/
int	copyout(from, to, len)
	char	*from;
	char	*to;
	unsigned int	len;
{
	return (0);
}

/*ARGSUSED*/
blkcpy(from, to, len)
	char	*from, *to;
	unsigned int	len;
{}
/*ARGSUSED*/
bcopy(from, to, len)
	char	*from, *to;
	unsigned int	len;
{}
/*ARGSUSED*/
blkclr(addr, len)
	char *addr;
	unsigned int len;
{}
/*ARGSUSED*/
bzero(addr, len)
	char *addr;
	unsigned int len;
{}

/*ARGSUSED*/
bit_lock(bit, addr)
	int	bit;
	char	*addr;
{}
/*ARGSUSED*/
bit_unlock(bit, addr)
	int	bit;
	char	*addr;
{}
/*ARGSUSED*/
boolean_t bit_lock_try(bit, addr)
	int	bit;
	char	*addr;
{
	return(TRUE);
}
/*
 * i_bit_set and i_bit_clear are always used on cpu_sets
 */
/*ARGSUSED*/
i_bit_set(bit, addr)
	int	bit;
	cpu_set	*addr;
{}
/*ARGSUSED*/
i_bit_clear(bit, addr)
	int	bit;
	cpu_set	*addr;
{}

int	spl0()		{ return (0); }
int	spl1()		{ return (0); }
int	splsoftclock()	{ return (0); }
int	splnet()	{ return (0); }
int	splimp()	{ return (0); }
int	spl4()		{ return (0); }
int	splbio()	{ return (0); }
int	splclock()	{ return (0); }
int	splhigh()	{ return (0); }
int	splsched()	{ return (0); }
int	splvm()		{ return (0); }

/*ARGSUSED*/
splx(s)
	int s;
{
}

/*ARGSUSED*/
mtpr(reg,val)
	int reg, val;
{
}

int	mfpr(reg)
	int reg;
{
	return (reg);
}

setsoftclock()	{}

int	movpsl()	{ return (0); }
int	save_context()	{ return (0); }

/*ARGSUSED*/
load_context(th)
	thread_t	th;
{}

#if	NCPUS > 1
int	cpu_number()	{ return (0); }
#endif	NCPUS > 1

thread_t current_thread()
{
	return ((thread_t)0);
}

#if	NCPUS > 1
/*ARGSUSED*/
void	simple_lock_init(l)
	simple_lock_t	l;
{}
/*ARGSUSED*/
void	simple_lock(l)
	simple_lock_t	l;
{}
/*ARGSUSED*/
void	simple_unlock(l)
	simple_lock_t	l;
{}
/*ARGSUSED*/
boolean_t simple_lock_try(l)
	simple_lock_t	l;
{
	return (FALSE);
}
#endif	NCPUS > 1

/*ARGSUSED*/
phys_zero(phys_addr, size)
	vm_offset_t	phys_addr;
	vm_size_t	size;
{}
/*ARGSUSED*/
pmap_zero_page(phys_addr)
	vm_offset_t	phys_addr;
{}
/*ARGSUSED*/
pmap_copy_page(src_phys_addr, dst_phys_addr)
	vm_offset_t	src_phys_addr;
	vm_offset_t	dst_phys_addr;
{}
/*ARGSUSED*/
copy_to_phys(src_addr_v, dst_addr_p, count)
	vm_offset_t	src_addr_v;
	vm_offset_t	dst_addr_p;
	vm_size_t	count;
{}
/*ARGSUSED*/
copy_from_phys(src_addr_p, dst_addr_v, count)
	vm_offset_t	src_addr_p;
	vm_offset_t	dst_addr_v;
	vm_size_t	count;
{}
int getmemc(phys_addr)
	char	*phys_addr;
{
	return (*phys_addr);
}
putmemc(phys_addr, byte)
	char	*phys_addr;
	int	byte;
{
	*phys_addr = byte;
}

dfloat_test()
{
}

/*
 * Fake main program, to reference routines called from assembler.
 */
extern void	clock_interrupt(),
		machine_startup(),
		slave_main(),
		trap(),
		machinecheck();
extern int	cold;
extern int	mach_trap_count;

#if	NCPUS > 1
extern void	pmap_update_interrupt();
#endif
#if	NBI > 0
extern int	bi_bus_error();
extern int	bi_err();
#endif

void lowinit()
{
	lowinit();	/* LINT */
	vax_init();
	machine_startup();
	slave_main();

	clock_interrupt(10000, FALSE, FALSE);
	cnrint(0);
	cnxint(0);
	machinecheck((char *)0);

	trap(0, 0, 0, 0, 0);

	cold++;
	mach_trap_count = mach_trap_count;

	wtime(0, 0, (pcb_t)0);

#if	VAX750
	turintr();
	tuxintr();
	crlintr();
#endif
#if	VAX820
	rxcd_intr();
#endif
#if	NMBA > 0
	mbintr(0);
#endif
#if	NUBA > 0
	ubaerror(0, (struct uba_hd *)0, 0, 0, (struct uba_regs *)0);
#endif
#if	NMACH_MPM > 0
	mpmintr(0);
	mpmcintr(0);
	mpm_off(0);
#endif
#if	NCPUS > 1
	pmap_update_interrupt();
#endif
#if	NBI > 0
	bi_bus_error();
	bi_err(0, 0, 0);
#endif
}

/*
 * Declarations of assembler structures.
 */
#if	VAX630 || VAX650 || VAX3100
int	D_float;
#endif
char *	esym;
char	etext, edata;
int	end;		/* ?? */

int	intstack[INTSTACK_SIZE/sizeof(int)];

#if	NUBA > 0
int	(*UNIvec[128])();
#if	NUBA > 1
int	(*UNI1vec[128])();
#endif
#endif

struct scb	scb;
struct rpb	rpb;
int		catcher[256];

int	boot_reg7, boot_reg8;

#if	MACH_LOAD
vm_offset_t	loadpt;
#endif	MACH_LOAD
