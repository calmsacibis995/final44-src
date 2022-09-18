h31494
s 00008/00001/00227
d D 5.4 91/04/04 18:01:48 bostic 4 3
c new copyright; att/bsd/shared
e
s 00002/00002/00226
d D 5.3 89/09/15 16:04:55 bostic 3 2
c compiler doesn't like empty array declaration
e
s 00027/00018/00201
d D 5.2 89/02/04 23:24:34 torek 2 1
c mr-frog reminded me: need to invalidate ptrace cache
c when subprocess runs.  how did I ever forget?
e
s 00219/00000/00000
d D 5.1 89/01/16 20:24:41 bostic 1 0
c new version from Chris Torek
e
u
U
t
T
I 4
/*-
 * Copyright (c) 1991 The Regents of the University of California.
 * All rights reserved.
 *
 * %sccs.include.proprietary.c%
 */

E 4
I 1
#ifndef lint
static char sccsid[] = "%W% (Berkeley) %G%";
D 4
#endif
E 4
I 4
#endif /* not lint */
E 4

/*
 * Adb: access data in file/process address space.
 */

#include "defs.h"
#include <sys/file.h>
#include <sys/ptrace.h>

off_t	lseek();

/*
 * Read or write from or to the given address, accessing or altering
 * only the given byte(s).  Return the number of bytes transferred.
 * Remote (debuggee) addresses are specified as a <space,address> pair.
 * Neither the remote nor the local address need be aligned.
 *
 * If there is a current process, ask the system to do this (via ptrace
 * [ick]).  If debugging the kernel, use vtophys() to map virtual to
 * physical locations (in a system-dependent manner).  Otherwise we
 * can just read or write the files being debugged directly.
 */
int
adbio(rw, space, rmtaddr, localaddr, cnt)
	enum rwmode rw;
	int space;
	addr_t rmtaddr;
	caddr_t localaddr;
	int cnt;
{
	register int ret;
	register struct map *mp;
	struct m1 *mm;

D 3
	static char derr[] = "data address not found";
	static char terr[] = "text address not found";
E 3
I 3
	static char *derr = "data address not found";
	static char *terr = "text address not found";
E 3
#define rwerr() errflag = space & SP_DATA ? derr : terr
#define	within(which) (rmtaddr >= which.b && rmtaddr < which.e)

	if (space == SP_NONE) {
		/* The no-space is all zero. */
		bzero(localaddr, cnt);
		return (cnt);
	}
	if (pid) {
		ret = io_ptrace(rw, space, rmtaddr, localaddr, cnt);
		if (ret != cnt)
			rwerr();
		return (ret);
	}
	if (rw == RWMODE_WRITE && !wtflag)
		error("not in write mode");
	mp = space & SP_DATA ? &datmap : &txtmap;
	if ((space & SP_STAR) == 0 && within(mp->m1))
		mm = &mp->m1;
	else if (within(mp->m2))
		mm = &mp->m2;
	else {
		rwerr();
		return (0);
	}
	rmtaddr += mm->f - mm->b;
	if (kernel && space == SP_DATA) {
		char *err = NULL;

		rmtaddr = vtophys(rmtaddr, &err);
		if (err) {
			errflag = err;
			return (0);
		}
	}
	if (lseek(mp->ufd, (off_t)rmtaddr, 0) == -1) {
		rwerr();
		return (0);
	}
	if (rw == RWMODE_READ) {
		ret = read(mp->ufd, localaddr, cnt);
		/* gratuitously supply extra zeroes at end of file */
		if (ret > 0 && ret < cnt) {
			bzero(localaddr + ret, cnt - ret);
			ret = cnt;
		}
	} else
		ret = write(mp->ufd, localaddr, cnt);
	if (ret != cnt)
		rwerr();
	return (ret);
#undef rwerr
#undef within
}

/*
 * Read a single object of length `len' from the core file at the
 * given offset.  Return the length read.  (This routine allows vtophys
 * and kernel crash startup code to read ptes, etc.)
 */
int
readcore(off, addr, len)
	off_t off;
	caddr_t addr;
	int len;
{

	if (lseek(corefile.fd, off, L_SET) == -1)
		return (-1);
	return (read(corefile.fd, addr, len));
}

/*
 * THE FOLLOWING IS GROSS.  WE SHOULD REPLACE PTRACE WITH SPECIAL
 * FILES A LA /proc.
 *
 * Read or write using ptrace.  io_ptrace arranges that the
 * addresses passed to ptrace are an even multiple of sizeof(int),
 * and is able to read or write single bytes.
 *
 * Since ptrace is so horribly slow, and some commands do repeated
 * reading of units smaller than an `int', io_ptrace calls cptrace
 * (cached ptrace) to allow some cacheing.  cptrace also converts a
 * read/write op and a space into a ptrace op, and returns 0 on success
 * and hence takes a pointer to the value cell rather than the value.
D 2
 *
 * N.B.: The cache retains the pid, so that killing and restarting
 * a process invalidates the cache entry.  If pid's were reused fast
 * enough this could fail, and we would need a cache-invalidate
 * routine, to be called whenever a process is started.  Fortunately
 * that is not now the case.
E 2
 */
I 2
struct cache {
	short	rop, wop;		/* ptrace ops for read and write */
	int	valid;			/* true iff cache entry valid */
	int	*addr;			/* address of cached value */
	int	val;			/* and the value */
};
static struct cache icache = { PT_READ_I, PT_WRITE_I };
static struct cache dcache = { PT_READ_D, PT_WRITE_D };

/*
 * Invalidate one or both caches.
 * This is the only function that accepts two spaces simultaneously.
 */
cacheinval(space)
	int space;
{

	if (space & SP_INSTR)
		icache.valid = 0;
	if (space & SP_DATA)
		dcache.valid = 0;
}

E 2
int	cachehit, cachemiss;		/* statistics */

static int
cptrace(rw, space, p, addr, val)
	enum rwmode rw;
	int space, p, *addr, *val;
{
D 2
	static struct cache {
		short	rop, wop;	/* ptrace ops for read and write */
		int	pid;		/* pid, iff cache entry valid */
		int	*addr;		/* address of cached value */
		int	val;		/* and the value */
	} cache[2] = { {PT_READ_D, PT_WRITE_D}, {PT_READ_I, PT_WRITE_I} };
	register struct cache *c;
E 2
I 2
	register struct cache *c = space & SP_DATA ? &dcache : &icache;
E 2
	int v;

D 2
	/* set c to point to cache[0] for dspace, cache[1] for ispace */
	c = space & SP_DATA ? &cache[0] : &cache[1];
E 2
	if (rw == RWMODE_READ) {
D 2
		if (c->pid == p && c->addr == addr) {
E 2
I 2
		if (c->valid && c->addr == addr) {
E 2
			cachehit++;
			*val = c->val;
			return (0);
		}
		cachemiss++;
		errno = 0;
		if ((v = ptrace(c->rop, p, addr, 0)) == -1 && errno)
			return (-1);
		*val = v;
	} else {
D 2
		c->pid = 0;		/* paranoia */
E 2
I 2
		c->valid = 0;		/* paranoia */
E 2
		errno = 0;
		if (ptrace(c->wop, p, addr, v = *val) == -1 && errno)
			return (-1);
	}
D 2
	c->pid = p;
E 2
I 2
	c->valid = 1;
E 2
	c->addr = addr;
	c->val = v;
	return (0);
}

int
io_ptrace(rw, space, rmtaddr, localaddr, cnt)
	register enum rwmode rw;
	register int space;
	addr_t rmtaddr;
	register caddr_t localaddr;
	register int cnt;
{
	register addr_t addr;
	register int nbytes, ret = 0, off;
	int tmp;

	/*
	 * Start by aligning rmtaddr; set nbytes to the number of bytes of
	 * useful data we shall obtain.
	 */
	off = rmtaddr % sizeof(int);	/* addr_t is unsigned */
	addr = rmtaddr - off;
	nbytes = sizeof(int) - off;
	while (cnt != 0) {
		if (cnt < nbytes)
			nbytes = cnt;
		if (rw == RWMODE_READ) {
			if (cptrace(rw, space, pid, (int *)addr, &tmp))
				return (ret);
			bcopy((caddr_t)&tmp + off, localaddr, nbytes);
		} else {
			if (nbytes < sizeof(int) &&
			    cptrace(RWMODE_READ, space, pid, (int *)addr, &tmp))
				return (ret);
			bcopy(localaddr, (caddr_t)&tmp + off, nbytes);
			if (cptrace(rw, space, pid, (int *)addr, &tmp))
				return (ret);
		}
		addr += sizeof(int);
		localaddr += nbytes;
		ret += nbytes;
		cnt -= nbytes;
		/*
		 * For the rest of the loop, the offset is 0 and we can
		 * use all the bytes obtained.
		 */
		off = 0;
		nbytes = sizeof(int);
	}
	return (ret);
}
E 1
