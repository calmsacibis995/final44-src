#
#	Some crude documentation for Tab
#
#		F must point to the Tab directory for libs and header files
#
DRAFT=-rC3

F=/iaa/rd/forms.d

F_LIBS=${F}/Tab.d/libform.a ${F}/windows.d/libwindows.a ${F}/vt.d/libvt.a

#
# use the first one if curses is using termcap
# use the second one if curses is not up to date on your system
#
# CURSES=-ltermlib
# CURSES=../small_curses.d/libcurses.a
CURSES=-lcurses

CFLAGS=-O -I${F}/Tab.d -I${F}/windows.d -I${F}/vt.d

all:	x1 x2 x3 x4 x5 x6 x7 x8 x9 x10 x11 x12 x13 x14 x15 x16 \
	x17 x18 x19

x1:	x1.o ${F_LIBS}
	cc -o x1 x1.o ${F_LIBS} ${CURSES}

x2:	x2.o ${F_LIBS}
	cc -o x2 x2.o ${F_LIBS} ${CURSES}

x3:	x3.o ${F_LIBS}
	cc -o x3 x3.o ${F_LIBS} ${CURSES}

x4:	x4.o ${F_LIBS}
	cc -o x4 x4.o ${F_LIBS} ${CURSES}

x5:	x5.o ${F_LIBS}
	cc -o x5 x5.o ${F_LIBS} ${CURSES}

x6:	x6.o ${F_LIBS}
	cc -o x6 x6.o ${F_LIBS} ${CURSES}

x7:	x7.o ${F_LIBS}
	cc -o x7 x7.o ${F_LIBS} -lPW ${CURSES}

x8:	x8.o ${F_LIBS}
	cc -o x8 x8.o ../Tab.d/Get_List.o ${F_LIBS} ${CURSES}

x9:	x9.o ${F_LIBS}
	cc -o x9 x9.o ${F_LIBS} ${CURSES}

x10:	x10.o ${F_LIBS}
	cc -o x10 x10.o ${F_LIBS} ${CURSES}

x11:	x11.o ${F_LIBS}
	cc -o x11 x11.o ${F_LIBS} ${CURSES}

x12:	x12.o ${F_LIBS}
	cc -o x12 x12.o ${F_LIBS} ${CURSES}

x13:	x13.o ${F_LIBS}
	cc -o x13 x13.o ${F_LIBS} ${CURSES}

x14:	x14.o ${F_LIBS}
	cc -o x14 x14.o ${F_LIBS} ${CURSES}

x15:	x15.o ${F_LIBS}
	cc -o x15 x15.o ${F_LIBS} ${CURSES}

x16:	x16.o ${F_LIBS}
	cc -o x16 x16.o ${F_LIBS} ${CURSES}

x17:	x17.o ${F_LIBS}
	cc -o x17 x17.o ${F_LIBS} ${CURSES}

x18:	x18.o ${F_LIBS}
	cc -o x18 x18.o ${F_LIBS} ${CURSES}

x19:	x19.o ${F_LIBS}
	cc -o x19 x19.o ${F_LIBS} ${CURSES}


Tabs.mem:	Tabs.mm f_procs.mm windows.mm makefile.mm field.mm \
		Tabs.t1.mm Tabs.t2.mm Tabs.keys.mm Tabs.spec.mm \
		auto.mm edit.mm char.mm \
		err.mm extend.mm field.mm field_dis.mm form.mm help.mm \
		menus.mm print.mm scratch.mm scroll.mm
	nroff -mm ${DRAFT} Tabs.mm | col > Tabs.mem

Tabs.proof:	Tabs.mm f_procs.mm windows.mm makefile.mm field.mm \
		Tabs.t1.mm Tabs.t2.mm Tabs.keys.mm Tabs.spec.mm
	troff -Taps -mm Tabs.mm > Tabs.proof


Tabs.EPS:	Tabs.mm f_procs.mm windows.mm makefile.mm field.mm \
		Tabs.t1.mm Tabs.t2.mm Tabs.keys.mm Tabs.spec.mm \
		auto.mm edit.mm char.mm \
		err.mm extend.mm field.mm field_dis.mm form.mm help.mm \
		menus.mm print.mm scratch.mm scroll.mm
	-/eagle/lbin/mmt -Teps Tabs.mm > Tabs.EPS

Tabs.cov:	Tabs.cover
	-PATH=:/eagle/lbin${PATH} docsend -Teps -mcs Tabs.cover

Tabs.c.draft:	Tabs.cover
	-PATH=:/eagle/lbin${PATH} docsend -Teps -mcs -x Tabs.cover

Tabs.spec.mm:	Tabs.spec.tbl
	tbl Tabs.spec.tbl > Tabs.spec.mm


Tabs.t1.mm:	Tabs.t1.tbl
	tbl Tabs.t1.tbl > Tabs.t1.mm


Tabs.t2.mm:	Tabs.t2.tbl
	tbl Tabs.t2.tbl > Tabs.t2.mm


Tabs.keys.mm:	Tabs.keys.tbl
	tbl Tabs.keys.tbl > Tabs.keys.mm


Overview.proof:	Overview.mm arrow_keys.pic control.pic form1.pic form2.pic \
		form3.pic read_path.pic Tabs.keys.mm
	pic Overview.mm | troff -Taps -mm - > Overview.proof

Overview.EPS:	Overview.mm arrow_keys.pic control.pic form1.pic form2.pic \
		form3.pic read_path.pic Tabs.keys.mm
	-/eagle/lbin/mmt -Teps -p Overview.mm > Overview.EPS
	-/eagle/lbin/eps -op < Overview.EPS


clean:
	-rm -f x1.o x1 x2.o x2 x3.o x3 x4.o x4 x5 x5.o x6.o x6 \
		x7.o x7 x8.o x8 x9.o x9 x10.o x10 x11.o x11 \
		x12.o x12 x13.o x13 x14.o x14 x15.o x15 x16.o x16 \
		x17.o x17 x18.o x18 x19 x19.o


print:	Tabs.mem
	-lprint *.c makefile
	-lp Tabs.mem
