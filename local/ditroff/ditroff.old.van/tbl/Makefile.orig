BINDIR	= /usr/local
TBL	= dtbl
DEVDIR	= "/usr/local/lib/font"
CFLAGS	= -O '-DDEVDIR=$(DEVDIR)'

OBJECTS	= t0.o t1.o t2.o t3.o t4.o t5.o t6.o t7.o t8.o t9.o tb.o tc.o te.o \
	tf.o tg.o ti.o tm.o tr.o ts.o tt.o tu.o tv.o

tbl:	$(OBJECTS)
	cc t?.o -o tbl

$(OBJECTS):	t..c

install:	$(BINDIR)/$(TBL)

$(BINDIR)/$(TBL):	tbl
	install -c -s tbl $(BINDIR)/$(TBL)

tbl-test:
	sh compr sample01
	sh compr sample02
	sh compr sample03
	sh compr sample04
	sh compr sample05
	sh compr sample06
	sh compr sample07
	sh compr sample08
	sh compeq sample09
	sh compeq sample10
	sh compeq sample11
	sh compr sample12
	sh compr sample13
	sh compr sample14
	sh compr sample15
	sh compr sample16
	sh compr sample17
	sh compr sample18
	sh compr sample19
	sh compr sample20
	sh compr sample21
	sh compr sample22
	sh compr sample23
	sh compms sample24
	sh compr sample25
	sh compr sample26
	sh compr sample27
	sh compr sample28
	sh compr sample29
	sh compr sample30
	sh compr sample31
	sh compr sample32
	sh compr sample33
	sh compms sample34
	sh compeq sample35
	sh compeq sample36
	sh compnr sample37
	sh compr sample38
	sh compr sample39
	sh compr sample40
	sh compr sample41
	sh compr sample42
	sh compeq sample43
	sh compr sample44
	sh compms sample45
	sh compms sample46
	sh compr sample47
	sh compnr sample48
	sh compr sample49
	sh compr sample50
	sh compr sample51
	sh compr sample52
	sh compr sample53
	sh compr sample54
	sh compr sample55
	sh compeq /usr/doc/mel/tables

tbl-ichk: /usr/bin/tbl
	/usr/bin/tbl sample1 >junk1
	cmp -s junk1 out1

tbl-comp: tbl
	cmp -s tbl /usr/bin/tbl

clean:
	/bin/rm -f *.o make.out tbl
