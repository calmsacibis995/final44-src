Liszt = liszt
As =  test.s test2.s test3.s
Obj = test.o test2.o test3.o

.DEFAULT:test
.SUFFIXES: .l

.l.o:
	${Liszt} -qa $*
.l.s:
	${Liszt} -qaS $*

test:	${Obj}
asfiles:${As}
