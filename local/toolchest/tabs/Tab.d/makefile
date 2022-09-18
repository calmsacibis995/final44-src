CFLAGS=-O -I../vt.d -I../windows.d -DVT_TERMINFO

OBJS=	A_Show_List.o Clear_Area.o Clear_Form.o Def_Char_Act.o Def_Editing.o \
	Def_Match_T.o Def_Scratch.o Del_Field.o Del_P_Center.o Del_P_Form.o \
	Dump_Field.o Dump_Form.o Dup_Field.o Extend.o Extend_Field.o \
	Extend_Long.o F_Ok.o Field_Value.o Free_Field.o Free_Region.o \
	Get_Field.o Get_List.o Get_Position.o Link_Fields.o Move_Field.o \
	New_Area.o New_F_Menu.o New_Field.o New_M_Menu.o New_Menu.o \
	New_P_Menu.o New_Region.o New_S_Menu.o New_S_Region.o Print_Center.o \
	Print_Form.o Print_Help.o Print_Mesg.o Push_Window.o ReShow.o \
	Right_Field.o SCRN_Dump.o Set_Actions.o Set_An_Attr.o Set_Attrib.o \
	Set_Auto_A.o Set_CMP_Def.o Set_EOF.o Set_Error.o Set_Extend.o \
	Set_Help.o Set_Label.o Set_Reader.o Set_Tab_M.o Set_Window.o \
	Show_Def.o Show_Field.o Show_Label.o Start_Form.o Unlink_Field.o \
	brk_list_ins.o brk_list_rem.o brk_list_set.o brkchar.o chartyp.o \
	clean_err.o cm_get_keys.o cm_start.o cmcfm.o cmenv.o \
	cmfile.o cmini.o cmkey.o cmnum.o cmstr.o \
	comnd.o complete.o corchar.o crosscor.o deflt.o \
	expand.o f_length.o fc_length.o fields.o getachar.o \
	getatm.o imatch.o in_field.o in_window.o insert_field.o \
	insert_line.o menu_utils.o move_txcurs.o prhlp.o regchar.o \
	slide_region.o texti.o txdel.o


LOBJS=	A_Show_List.o Def_Match_T.o Def_Scratch.o Def_Editing.o Del_P_Center.o \
	Del_P_Form.o Dump_Field.o Dump_Form.o Extend_Field.o Extend_Long.o \
	Extend.o Field_Value.o Free_Region.o Get_Position.o Link_Fields.o \
	New_Area.o New_F_Menu.o New_M_Menu.o New_Menu.o New_S_Menu.o \
	New_S_Region.o New_Field.o New_Region.o Dup_Field.o Print_Center.o \
	SCRN_Dump.o Set_Actions.o Set_An_Attr.o Set_Attrib.o Set_Auto_A.o \
	Set_CMP_Def.o Set_EOF.o Set_Error.o Set_Extend.o Set_Help.o \
	Set_Label.o Free_Field.o Set_Reader.o Set_Tab_M.o Set_Window.o \
	Start_Form.o Def_Char_Act.o Unlink_Field.o brk_list_ins.o brk_list_rem.o \
	cmnum.o insert_field.o insert_line.o comnd.o Get_List.o \
	Get_Field.o Show_Field.o clean_err.o cmcfm.o getatm.o \
	brk_list_set.o cmstr.o slide_region.o Move_Field.o Del_Field.o \
	texti.o menu_utils.o New_P_Menu.o Clear_Form.o Print_Form.o \
	crosscor.o brkchar.o Clear_Area.o ReShow.o Show_Def.o \
	Right_Field.o Show_Label.o cmini.o cmkey.o cm_get_keys.o \
	in_field.o in_window.o move_txcurs.o cmfile.o cmenv.o \
	cm_start.o deflt.o complete.o expand.o imatch.o \
	prhlp.o Print_Help.o F_Ok.o f_length.o getachar.o \
	corchar.o Print_Mesg.o Push_Window.o chartyp.o regchar.o \
	fields.o txdel.o fc_length.o


libform.a: ${OBJS}
	-rm -f libform.a
	@echo "	ar q libform.a {LOBJS}"
	@ar q libform.a ${LOBJS}


tests:	tests.o libform.a ../windows.d/libwindows.a ../vt.d/libvt.a
	cc -o tests tests.o libform.a ../windows.d/libwindows.a ../vt.d/libvt.a \
	 -lcurses


clean:
	-rm -f *.o *.output tests


lint:
	@lint  -DCP_ENV -DCP_FILES -I../vt.d -I../windows.d $(OBJS:.o=.c)


print:
	-lprint makefile *.c *.h


cpio:
	-find . -cpio /dev/rmt0


lorder:
	-lorder comnd.o ${OBJS} | tsort | while read line1; \
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
