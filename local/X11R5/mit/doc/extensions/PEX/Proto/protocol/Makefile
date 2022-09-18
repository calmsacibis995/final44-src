
ps:	null
	soelim doc | eqn |  psroff -t -i -ms 2> toc.out > doc.ps

tocps:	null
	cat toc.hdr > contents
	echo ".Bg 1" >> contents
	echo "PEX Protocol Specification" >> contents
	echo ".Ed 1" >> contents
	cat toc.out >> contents
	psroff -t -ms contents > toc.ps

null:
