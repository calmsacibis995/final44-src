C
C Copyright (c) 1980 The Regents of the University of California.
C All rights reserved.
C
C This module is believed to contain source code proprietary to AT&T.
C Use and redistribution is subject to the Berkeley Software License
C Agreement and your Software Agreement with AT&T (Western Electric).
C
C	@(#)sigfpe.f	5.2 (Berkeley) 4/12/91
C

	subroutine sigfpe()
	call signal(8, sigfpe, -1)
	return
	end
