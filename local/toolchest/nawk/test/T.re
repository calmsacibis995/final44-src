echo T.re: tests of regular expression code

awk=${awk-../a.out}

$awk '
BEGIN {
	FS = "\t"
	awk = "../a.out"
}
NF == 0 {
	next
}
$1 != "" {	# new test
	re = $1
}
$2 != "" {	# either ~ or !~
	op = $2
	if (op == "~")
		neg = "!"
	else if (op == "!~")
		neg = ""
}
$3 != "" {	# new test string
	str = $3
}
$3 == "\"\"" {	# explicit empty line
	$3 = ""
}
NF > 2 {	# generate a test
	input = $3
	test = sprintf("echo '"'"'%s'"'"' | %s '"'"'%s/%s/ {print \"%d fails %s %s %s\"}'"'"'",
		input, awk, neg, re, NR, re, op, input)
	print re, op, input ":"
	system(test)
}
' <<\!!!
a	~	a
		ba
		bab
	!~	""
		x
		xxxxx
.	~	x
		xxx
	!~	""			
.a	~	xa
		xxa
		xax
	!~	a
		ab
		""
$	~	x
		""
.$	~	x
	!~	""
a$	~	a
		ba
		bbba
	!~	ab
		x
		""
^	~	x
		""
		^
^a$	~	a
	!~	xa
		ax
		xax
		""
^a.$	~	ax
		aa
	!~	xa
		aaa
		axy
		""
^$	~	""
	!~	x
		^
^.a	~	xa
		xaa
	!~	a
		""
^.*a	~	a
		xa
		xxxxxxa
	!~	""
^.+a	~	xa
		xxxxxxa
	!~	""
		a
		ax
a*	~	""
		a
		aaaa
		xa
		xxxx
aa*	~	a
		aaa
		xa
	!~	xxxx
		""
\$	~	x$
		$
		$x
	!~	""
		x
\.	~	.
	!~	x
		""
xr+y	~	xry
		xrry
		xrrrrrry
	!~	ry
		xy
xr?y	~	xy
		xry
	!~	xrry
[0-9]	~	1
		567
		x0y
	!~	abc
		""
[^0-9]	!~	1
		567
		""
	~	abc
		x0y
x[0-9]+y	~	x0y
		x23y
		x12345y
	!~	0y
		xy
x[0-9]?y	~	xy
		x1y
	!~	x23y
