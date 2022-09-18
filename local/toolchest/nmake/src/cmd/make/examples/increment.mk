/*
 * problem:	Neal McBurnett		druny!neal
 * example:	Glenn Fowler		ulysses!gsf
 *
 * these rules increment a counter each time a .o file is generated
 */

.COUNTER = 0

.GLOBAL.o : .increment .POST

.increment : .NOTOUCH .FOREGROUND
	(( i = $(.COUNTER) + 1 ))
	_make_ read .COUNTER = $i
