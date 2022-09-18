# CFLAGS=-O -I../vt.d -DSDIR=\"/usr/lib/emacs
# CFLAGS=-O -DTERMCAP
CFLAGS=-O -I../vt.d -DVT_TERMINFO

OBJS=	Free_Window.o Key_Map.o Move_Window.o New_Rel_Win.o New_Window.o \
	Push_Rel_Win.o Ref_All_W.o Refresh.o Set_Scroll_T.o Un_Map.o \
	W_Ok.o box.o cvadjust.o get_leadin.o get_x_y.o \
	s_werase.o setup_term.o term_dep.o w_erase_char.o w_mgo.o \
	w_sgo.o w_xgo.o wc_erase.o wcflush.o wclrl.o \
	windows_vt.o wrefresh.o wscroll.o wshift.o wsputc.o \
	wstart.o wsttype.o wttystart.o wvadjust.o wxprintf.o \
	wxputl.o xwscroll.o


LOBJS=	Push_Rel_Win.o New_Rel_Win.o Free_Window.o Move_Window.o New_Window.o \
	Refresh.o Un_Map.o get_x_y.o s_werase.o setup_term.o \
	w_erase_char.o w_mgo.o w_sgo.o wc_erase.o wsputc.o \
	wttystart.o wsttype.o get_leadin.o term_dep.o wxprintf.o \
	wxputl.o wclrl.o windows_vt.o wvadjust.o cvadjust.o \
	wcflush.o wscroll.o wshift.o xwscroll.o Ref_All_W.o \
	Set_Scroll_T.o Key_Map.o box.o wrefresh.o W_Ok.o \
	wstart.o w_xgo.o


libwindows.a: ${OBJS}
	-rm -f libwindows.a
	ar q libwindows.a ${LOBJS}


clean:
	-rm -f *.o *.output


lint:
	-lint ${CFLAGS} $(OBJS:.o=.c)


print:
	-lprint makefile *.c *.h


cpio:
	-find . -cpio /dev/rmt0


lorder:
	-lorder ${OBJS} | tsort | while read line1; \
	do \
		read line2; \
		read line3; \
		read line4; \
		read line5; \
		line="$$line1 $$line2 $$line3 $$line4 $$line5"; \
		echo "	$$line \\"; \
	done > lorder.output


objs:
	-echo ${OBJS} | tr " " "\012" | sort | while read line1; \
	do \
		read line2; \
		read line3; \
		read line4; \
		read line5; \
		line="$$line1 $$line2 $$line3 $$line4 $$line5"; \
		echo "	$$line \\"; \
	done > objs.output
