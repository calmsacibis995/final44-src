/*

 *      Copyright (c) 1984, 1985 AT&T
 *      All Rights Reserved

 *      THIS IS UNPUBLISHED PROPRIETARY SOURCE 
 *      CODE OF AT&T.
 *      The copyright notice above does not 
 *      evidence any actual or intended
 *      publication of such source code.

 */
#include <stdio.h>
#include <setjmp.h>
#include "vt.h"
#include "windows.h"
#include "fields.h"

/*
 *	Sample program for constructing fancy date fields.
 *	The date_fields() function creates three fields that
 *	may be collected directly or used as a CMREGN field.
 *
 *	Alice Yeuh - hlexa!yea - HL 2220
 *
 */

main()
{
	extern int chk_date ();
	int  i;
	struct field_item *fdate1[3];
	struct field_item *fdate2[3];
	struct field_item *fdate3[3];
	struct field_item *fg[3];

	Start_Form( stdwindow);

	date_fields (10, 10, fdate1);
	fg[0] = New_Field(10,10,CMREGN,(char *)fdate1,(char *)3,0);
	date_fields (12, 20, fdate2);
	fg[1] = New_Field(12,20,CMREGN,(char *)fdate2,(char *)3,0);
	date_fields (14, 30, fdate3);
	fg[2] = New_Field(14,30,CMREGN,(char *)fdate3,(char *)3,0);

	Show_List(fg,3);
	Show_Default_Field(fdate1[2],"83");
	Get_List(fg,3,FALSE ,FALSE);

	End_Form ();
}

static char *month_keys[12] =
{
"Jan",
"Feb",
"Mar",
"Apr",
"May",
"Jun",
"Jul",
"Aug",
"Sep",
"Oct",
"Nov",
"Dec",
};

date_fields (row, col, f)
int row;
int col;
struct field_item *f[];
{
	static struct field_item *conf;
	struct field_item *months;
	int  i;

	if (conf == 0)
		conf = New_Field(0,0,CMCFM,"_",0,0);

	f[0] = New_Field(row,col,CMNUM,"   ",0,"0,1,12");
	months = New_Field(0,0,CMKEY,"   ", 0,
		"Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec");
	Set_Label(f[0],"l","date[ ",FANORMAL);
	Link_Fields (f[0], months);
	Link_Fields(months,conf);
	Set_Actions (f[0], 0, chk_date);

	f[1] = New_Field(row,col+6, CMNUM,"  ",0,"0,1,31");
	Set_Label(f[1],"l","/ ",FANORMAL);
	Set_Label(f[1],"r"," /",FANORMAL);
	Link_Fields(f[1],conf);

	f[2] = New_Field(row,col+11, CMNUM,"  ",0,"0,0,99");
	Set_Label(f[2],"r"," ]",FANORMAL);
	Link_Fields(f[2],conf);

	for ( i=0; i<3; i++)
	{
		Set_Tab_Movement(f[i],TRUE,TRUE,TRUE,TRUE,FALSE);
		Set_Auto_Advance(f[i],TRUE);
		Set_EOF(f[i],TRUE,TRUE);
		Set_Attributes (f[i], FARIGHT);
	}

	Set_Attributes (months, FACASE);
}

static
chk_date (f, count, index, rc)
struct field_item *f[];
int count;
int index;
int rc;
{
	if ((f[index] -> txbuf[0] >= '0') &&
		    (f[index] -> txbuf[0] <= '9'))
	{
		Show_Default_Field (f[index],
				month_keys[atoi(f[index]->txbuf)-1]);
	}
	return (index);
}
