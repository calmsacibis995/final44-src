/*
 * problem:	Bob Dillberger		bukwheat!sundance!rtd
 * example:	Glenn Fowler		ulysses!gsf
 *
 * .sget when used as a dependency causes all sccs .c file get's
 * to be collected and passed to $(SGET) for a single s-list get
 */

SGET = sget
SGETFLAGS =

.sget : .NOTOUCH .WAIT .sget0 $$(**:N=*.o) .sget1
	$(SGET) $(SGETFLAGS) $(.sget)
	...
	$(RM) $(RMFLAGS) $(.sget)

.sget0 : .NOTOUCH .MAKE
	.sget =
	.TMP1 := { $(@.c.o:V) }
	.OLD.c.o : $(.TMP1:V)
	.c.o : {}
	s. : .CLEAR .MAKE { .sget += $(<) }

.sget1 : .NOTOUCH .MAKE
	.TMP1 := { $(@.OLD.c.o:V) }
	.c.o : $(.TMP1:V)
	.UNTOUCH : $(***:BS=.o)
	$(.sget:T=N).TOUCH : $(<<)
