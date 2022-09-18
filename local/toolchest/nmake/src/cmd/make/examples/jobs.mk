/*
 * example:	Glenn Fowler		ulysses!gsf
 *
 * concurrent execution example
 * run with and without -j4
 */

test : a b c d { echo $(<) done }
a : { sleep 4; echo $(<) done }
b : { sleep 3; echo $(<) done }
c : { sleep 2; echo $(<) done }
d : { sleep 1; echo $(<) done }
