PRINTER	= ip

print: g.out
	lpr -P$(PRINTER) -n g.out

g.out:	g.man.grn
	ditroff -t -P$(PRINTER) -me g.man.grn > g.out

g.man.grn:	g.man
	grn -P$(PRINTER) g.man > g.man.grn
