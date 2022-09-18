h18026
s 00009/00000/00000
d D 5.1 88/07/21 18:53:00 bostic 1 0
c distribution by Mark Nudleman
e
u
U
t
T
I 1
BEGIN { FS="("; state = 0 }

/^	public/ { ftype = $0; state = 1 }

{ if (state == 1)
	state = 2
  else if (state == 2)
	{ print ftype,$1,"();"; state = 0 }
}
E 1
