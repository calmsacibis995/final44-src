
/* $XConsortium: wdt4.c,v 5.2 91/07/24 18:46:01 hersh Exp $ */

/*****************************************************************
Copyright (c) 1989,1990, 1991 by Sun Microsystems, Inc. and the X Consortium.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Sun Microsystems,
the X Consortium, and MIT not be used in advertising or publicity 
pertaining to distribution of the software without specific, written 
prior permission.  

SUN MICROSYSTEMS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, 
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT 
SHALL SUN MICROSYSTEMS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL 
DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/



/*
 ## wdt4.c : 
 ## compares the implementation dependent data in workstation description table
 ## against the values returned from inquiries.
 ## Testing input inquires:
 ##
 #  Supplying command line argument:
 ## 1: to test pinq_num_avail_in 
 ## 2: to test pinq_def_loc_data 
 ## 3: to test pinq_def_loc_data3 
 ## 4: to test pinq_def_choice_data 
 ## 5: to test pinq_def_choice_data3 
 ## 6: to test pinq_def_pick_data 
 ## 7: to test pinq_def_pick_data3 
 ## 8: to test pinq_def_string_data 
 ## 9: to test pinq_def_string_data3 
 ## 10:to test pinq_def_stroke_data 
 ## 11:to test pinq_def_stroke_data3 
 ## 12:to test pinq_def_val_data 
 ## 13:to test pinq_def_val_data3 
 */

#include "phigs/phigs.h"
#include "imath.h"
#include "wdt.h"
#include "logmsg.h"
#include "X11/Xlib.h"
#include "X11/Xutil.h"
#include "X11/Xatom.h"


/* constants */
#define BUFSIZE 1024
#define BOGUSERR -999

static void verify_num_input();
static void verify_def_loc();
static void verify_def_loc3();
static void verify_def_choice();
static void verify_def_choice3();
static void verify_def_pick();
static void verify_def_pick3();
static void verify_def_string();
static void verify_def_string3();
static void verify_def_stroke();
static void verify_def_stroke3();
static void verify_def_val();
static void verify_def_val3();


/* commonly used variables */
Pint err;
Pint total;
Pint wstype;         /* specific workstation type */


#define ERROR(string) \
	if (err) { \
		tfprintf("ERROR: %d in %s\n", err,string);\
		return;\
	}

main(argc,argv)
        int argc;
        char **argv;
{
	char *getenv();
        char testdesc[256];
	int i,test;
	char charbuf[BUFSIZE];
	Pconnid cid;

        sprintf(testdesc,"\"%s\" workstation's default input data inquiries",WSTYPE);
	tbegintest("wdt4",testdesc);
	i_open_phigs((char *)0, PDEF_MEM_SIZE);
	/* ws type dependent procedure to open a ws */
	OPEN_WS1();
	err = BOGUSERR;
	cid = charbuf;
        pinq_ws_conn_type(1,BUFSIZE,&err,&cid,&wstype);
        ERROR("pinq_ws_conn_type");

        if (argc < 2) {
		verify_num_input();
		verify_def_loc();
		verify_def_loc3();
		verify_def_choice();
		verify_def_choice3();
		verify_def_pick();
		verify_def_pick3();
		verify_def_string();
		verify_def_string3();
		verify_def_stroke();
		verify_def_stroke3();
		verify_def_val();
		verify_def_val3();
        }
        for (i = 1; i < argc; ++i) {
                test = atoi(argv[i]);
                switch(test) {
		case 1:
			tvprintf(2,"testing  pinq_num_avail_in \n");
			verify_num_input();
			break;
		case 2:
			tvprintf(2,"testing  pinq_def_loc_data \n");
			verify_def_loc();
			break;
		case 3:
			tvprintf(2,"testing  pinq_def_loc_data3 \n");
			verify_def_loc3();
			break;
		case 4:
			tvprintf(2,"testing  pinq_def_choice_data \n");
			verify_def_choice();
			break;
		case 5:
			tvprintf(2,"testing  pinq_def_choice_data3 \n");
			verify_def_choice3();
			break;
		case 6:
			tvprintf(2,"testing  pinq_def_pick_data \n");
			verify_def_pick();
			break;
		case 7:
			tvprintf(2,"testing  pinq_def_pick_data3 \n");
			verify_def_pick3();
			break;
		case 8:
			tvprintf(2,"testing  pinq_def_string_data \n");
			verify_def_string();
			break;
		case 9:
			tvprintf(2,"testing  pinq_def_string_data3 \n");
			verify_def_string3();
			break;
		case 10:
			tvprintf(2,"testing  pinq_def_stroke_data \n");
			verify_def_stroke();
			break;
		case 11:
			tvprintf(2,"testing  pinq_def_stroke_data3 \n");
			verify_def_stroke3();
			break;
		case 12:
			tvprintf(2,"testing  pinq_def_val_data \n");
			verify_def_val();
			break;
		case 13:
			tvprintf(2,"testing  pinq_def_val_data3 \n");
			verify_def_val3();
			break;
                default:
                        tabort("ERROR: invalid argument \"%s\"\n",argv[i]);
		}
	}
	tendtest();
}

/*
 * verify_num_input
 */
static void
verify_num_input() 
{

	Pnum_in numdev;

	err = BOGUSERR;
	pinq_num_avail_in(wstype,&err,&numdev);
	ERROR("pinq_num_avail_in");
	if (numdev.loc!= num_locator_dev) 
		tfprintf("failed: # of locator device = %d, expected %d\n",
			numdev.loc, num_locator_dev);
	if (numdev.stroke != num_stroke_dev) 
		tfprintf("failed: # of stroke device = %d, expected %d\n",
			numdev.stroke, num_stroke_dev);
	if (numdev.val!= num_valuator_dev) 
		tfprintf("failed: # of valuator device = %d, expected %d\n",
			numdev.val, num_valuator_dev);
	if (numdev.choice != num_choice_dev) 
		tfprintf("failed: # of choice device = %d, expected %d\n",
			numdev.choice, num_choice_dev);
	if (numdev.pick != num_pick_dev) 
		tfprintf("failed: # of pick device = %d, expected %d\n",
			numdev.pick, num_pick_dev);
	if (numdev.string != num_string_dev) 
		tfprintf("failed: # of string device = %d, expected %d\n",
			numdev.string, num_string_dev);
}

/*
 * verify_def_loc
 */
static void
verify_def_loc() 
{
	Pint dev;
	Pint_list exppet;
	int i;
	Ploc_data *data;
	Pstore store;
	Ppoint pos;
	Pint_list pets;
	Pint_list *p_pets;
	Plimit earea;
	Pint intbuf[BUFSIZE];

	pets.ints = intbuf;
	p_pets = &pets;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_locator_dev; i++) {
		dev = list_locator_dev_num[i];
		pinq_def_loc_data(wstype,dev,store,&err,&pos,
			&p_pets,&earea,&data);
		ERROR("pinq_def_loc_data");
		if (! i_compare_Ppoint(pos,list_locator_init_pos[i]))
			tfprintf("failed: locator device (%d): initial position != expected\n",dev);
		exppet.num_ints = list_locator_num_pet[i];
		exppet.ints = list_locator_list_pet[i];
		if (! i_compare_Pint_list(&pets,exppet))
			tfprintf("failed: locator device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit(earea,list_locator_def_echo_area[i]))
			tfprintf("failed: locator device (%d): default echo area!= expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_loc3
 */
static void
verify_def_loc3()
{
	Pint dev;
	Pint_list exppet;
	Ploc_data3 data;
	int i;
	Pstore store;
	Ppoint3 pos;
	Pint_list pets;
	Pint_list *p_pets;
	Plimit3 evolume;
	Pint intbuf[BUFSIZE];

	pets.ints = intbuf;
	p_pets = &pets;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_locator_dev; i++) {
		dev = list_locator3_dev_num[i];
		pinq_def_loc_data3(wstype,dev,store,&err,&pos,
			&p_pets,&evolume,&data);
		ERROR("pinq_def_loc_data3");
		if (! i_compare_Ppoint3(pos,list_locator3_init_pos[i]))
			tfprintf("failed: locator3 device (%d): initial position != expected\n",dev);
		exppet.num_ints = list_locator3_num_pet[i];
		exppet.ints = list_locator3_list_pet[i];
		if (! i_compare_Pint_list(&pets,exppet))
			tfprintf("failed: locator3 device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit3(evolume,list_locator3_def_echo_volume[i]))
			tfprintf("failed: locator3 device (%d): default echo volume != expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_choice
 */
static void
verify_def_choice() 
{
	Pint dev;
	Pint_list exppet;
	int i;
	Pchoice_data *data;
	Pstore store;
	Pint_list pets;
	Pint_list *p_pets;
	Plimit earea;
	Pint maxchoice;
	Pint intbuf[BUFSIZE];

	pets.ints = intbuf;
	p_pets = &pets;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_choice_dev; i++) {
		dev = list_choice_dev_num[i];
		pinq_def_choice_data(wstype,dev,store,&err,
			&maxchoice,&p_pets, &earea,&data);
		ERROR("pinq_def_choice_data");
		if ( maxchoice != list_choice_max_num_choice[i])
			tfprintf("failed: choice device (%d): maximum # of choices = %d,expected %d\n",dev,maxchoice,list_choice_max_num_choice[i]);
		exppet.num_ints = list_choice_num_pet[i];
		exppet.ints = list_choice_list_pet[i];
		if (! i_compare_Pint_list(&pets,exppet))
			tfprintf("failed: choice device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit(earea,list_choice_def_echo_area[i]))
			tfprintf("failed: choice device (%d): default echo area!= expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_choice3
 */
static void
verify_def_choice3() 
{
	Pint dev;
	Pint_list exppet;
	int i;
	Pchoice_data3 *data;
	Pstore store;
	Pint_list *pets;
	Plimit3 evolume;
	Pint maxchoice;
	Pint intbuf[BUFSIZE];

	(*pets).ints = intbuf;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_choice_dev; i++) {
		dev = list_choice3_dev_num[i];
		pinq_def_choice_data3(wstype,dev,store,&err,
			&maxchoice,&pets, &evolume,&data);
		ERROR("pinq_def_choice_data3");
		if ( maxchoice != list_choice3_max_num_choice[i])
			tfprintf("failed: choice3 device (%d): maximum # of choices = %d,expected %d\n",dev,maxchoice,list_choice3_max_num_choice[i]);
		exppet.num_ints = list_choice3_num_pet[i];
		exppet.ints = list_choice3_list_pet[i];
		if (! i_compare_Pint_list(*pets,exppet))
			tfprintf("failed: choice3 device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit3(evolume,list_choice3_def_echo_volume[i]))
			tfprintf("failed: choice3 device (%d): default echo volume!= expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_val
 */
static void
verify_def_val() 
{
	Pint dev;
	Pint_list exppet;
	int i;
	Pval_data *data;
	Pstore store;
	Pfloat defval;
	Pint_list *pets;
	Plimit earea;
	Pint intbuf[BUFSIZE];

	(*pets).ints = intbuf;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_valuator_dev; i++) {
		dev = list_valuator_dev_num[i];
		pinq_def_val_data(wstype,dev,store,&err,&defval,
			&pets,&earea,&data);
		ERROR("pinq_def_val_data");
		if ( fne(defval, list_valuator_def_init_value[i]))
			tfprintf("failed: valuator device (%d): default initial value = %.4f,expected %.4f\n",dev,defval,list_valuator_def_init_value[i]);
		exppet.num_ints = list_valuator_num_pet[i];
		exppet.ints = list_valuator_list_pet[i];
		if (! i_compare_Pint_list(*pets,exppet))
			tfprintf("failed: valuator device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit(earea,list_valuator_def_echo_area[i]))
			tfprintf("failed: valuator device (%d): default echo area!= expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_val3
 */
static void
verify_def_val3()
{
	Pint dev;
	Pint_list exppet;
	int i;
	Pval_data3 *data;
	Pstore store;
	Pfloat defval;
	Pint_list *pets;
	Plimit3 evolume;
	Pint intbuf[BUFSIZE];

	(*pets).ints = intbuf;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_valuator_dev; i++) {
		dev = list_valuator3_dev_num[i];
		pinq_def_val_data3(wstype,dev,store,&err,&defval,
			&pets,&evolume,&data);
		ERROR("pinq_def_val_data3");
		if ( fne(defval , list_valuator3_def_init_value[i]))
			tfprintf("failed: valuator3 device (%d): default initial value = %.4f,expected %.4f\n",dev,defval,list_valuator3_def_init_value[i]);
		exppet.num_ints = list_valuator3_num_pet[i];
		exppet.ints = list_valuator3_list_pet[i];
		if (! i_compare_Pint_list(*pets,exppet))
			tfprintf("failed: valuator3 device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit3(evolume,list_valuator3_def_echo_volume[i]))
			tfprintf("failed: valuator3 device (%d): default echo volume!= expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_stroke
 */
static void
verify_def_stroke() 
{
	Pint dev;
	Pint_list exppet;
	int i;
	Pstroke_data *data;
	Pstore store;
	Pint maxbuf;
	Pint_list *pets;
	Plimit earea;
	Pint intbuf[BUFSIZE];

	(*pets).ints = intbuf;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_stroke_dev; i++) {
		dev = list_stroke_dev_num[i];
		pinq_def_stroke_data(wstype,dev,store,&err,&maxbuf,
			&pets,&earea, &data);
		ERROR("pinq_def_stroke_data");
		if ( maxbuf != list_stroke_avail_bufsize[i])
			tfprintf("failed: stroke device (%d): available input buffer size = %d,expected %d\n",dev,maxbuf,list_stroke_avail_bufsize[i]);
		exppet.num_ints = list_stroke_num_pet[i];
		exppet.ints = list_stroke_list_pet[i];
		if (! i_compare_Pint_list(*pets,exppet))
			tfprintf("failed: stroke device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit(earea,list_stroke_def_echo_area[i]))
			tfprintf("failed: stroke device (%d): default echo area!= expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_stroke3
 */
static void
verify_def_stroke3() 
{
	Pint dev;
	Pint_list exppet;
	int i;
	Pstroke_data3 *data;
	Pstore store;
	Pint maxbuf;
	Pint_list *pets;
	Plimit3 evolume;
	Pint intbuf[BUFSIZE];

	(*pets).ints = intbuf;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_stroke_dev; i++) {
		dev = list_stroke3_dev_num[i];
		pinq_def_stroke_data3(wstype,dev,store,&err,&maxbuf,
			&pets,&evolume,&data);
		ERROR("pinq_def_stroke_data3");
		if ( maxbuf != list_stroke3_avail_bufsize[i])
			tfprintf("failed: stroke3 device (%d): available input buffer size = %d,expected %d\n",dev,maxbuf,list_stroke3_avail_bufsize[i]);
		exppet.num_ints = list_stroke3_num_pet[i];
		exppet.ints = list_stroke3_list_pet[i];
		if (! i_compare_Pint_list(*pets,exppet))
			tfprintf("failed: stroke3 device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit3(evolume,list_stroke3_def_echo_volume[i]))
			tfprintf("failed: stroke3 device (%d): default echo volume!= expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_string
 */
static void
verify_def_string() 
{
	Pint dev;
	Pint_list exppet;
	int i;
	Pstring_data *data;
	Pstore store;
	Pint maxbuf;
	Pint_list *pets;
	Plimit earea;
	Pint intbuf[BUFSIZE];

	(*pets).ints = intbuf;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_string_dev; i++) {
		dev = list_string_dev_num[i];
		pinq_def_string_data(wstype,dev,store,&err,&maxbuf,
			&pets, &earea, &data);
		ERROR("pinq_def_string_data");
		if ( maxbuf != list_string_avail_bufsize[i])
			tfprintf("failed: string device (%d): available input buffer size = %d,expected %d\n",dev,maxbuf,list_string_avail_bufsize[i]);
		exppet.num_ints = list_string_num_pet[i];
		exppet.ints = list_string_list_pet[i];
		if (! i_compare_Pint_list(*pets,exppet))
			tfprintf("failed: string device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit(earea,list_string_def_echo_area[i]))
			tfprintf("failed: string device (%d): default echo area!= expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_string3
 */
static void
verify_def_string3() 
{
	Pint dev;
	Pint_list exppet;
	int i;
	Pstring_data3 *data;
	Pstore store;
	Pint maxbuf;
	Pint_list *pets;
	Plimit3 evolume;
	Pint intbuf[BUFSIZE];

	(*pets).ints = intbuf;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_string_dev; i++) {
		dev = list_string3_dev_num[i];
		pinq_def_string_data3(wstype,dev,store,&err,&maxbuf,
			&pets,&evolume,&data);
		ERROR("pinq_def_string_data3");
		if ( maxbuf != list_string3_avail_bufsize[i])
			tfprintf("failed: string3 device (%d): available input buffer size = %d,expected %d\n",dev,maxbuf,list_string3_avail_bufsize[i]);
		exppet.num_ints = list_string3_num_pet[i];
		exppet.ints = list_string3_list_pet[i];
		if (! i_compare_Pint_list(*pets,exppet))
			tfprintf("failed: string3 device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit3(evolume,list_string3_def_echo_volume[i]))
			tfprintf("failed: string3 device (%d): default echo volume!= expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_pick
 */
static void
verify_def_pick() 
{
	Pint dev;
	Pint_list exppet;
	int i;
	Ppick_data *data;
	Pstore store;
	Pint_list *pets;
	Plimit earea;
	Pint intbuf[BUFSIZE];

	(*pets).ints = intbuf;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_pick_dev; i++) {
		dev = list_pick_dev_num[i];
		pinq_def_pick_data(wstype,dev,store,&err,&pets,
			&earea,&data);
		ERROR("pinq_def_pick_data");
		exppet.num_ints = list_pick_num_pet[i];
		exppet.ints = list_pick_list_pet[i];
		if (! i_compare_Pint_list(*pets,exppet))
			tfprintf("failed: pick device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit(earea,list_pick_def_echo_area[i]))
			tfprintf("failed: pick device (%d): default echo area!= expected\n",dev);

	}
	pdel_store(store);
}

/*
 * verify_def_pick3
 */
static void
verify_def_pick3() 
{
	Pint dev;
	Pint_list exppet;
	int i;
	Ppick_data3 *data;
	Pstore store;
	Pint_list *pets;
	Plimit3 evolume;
	Pint intbuf[BUFSIZE];

	(*pets).ints = intbuf;
	err = BOGUSERR;
	pcreate_store(&err,&store);
	ERROR("pcreate_store");
	for (i=0;i< num_pick_dev; i++) {
		dev = list_pick3_dev_num[i];
		pinq_def_pick_data3(wstype,dev,store,&err,&pets,
			&evolume,&data);
		ERROR("pinq_def_pick_data3");
		exppet.num_ints = list_pick3_num_pet[i];
		exppet.ints = list_pick3_list_pet[i];
		if (! i_compare_Pint_list(*pets,exppet))
			tfprintf("failed: pick3 device (%d): list of prompt and echo types != expected\n",dev);
		if (! i_compare_Plimit3(evolume,list_pick3_def_echo_volume[i]))
			tfprintf("failed: pick3 device (%d): default echo volume != expected\n",dev);

	}
	pdel_store(store);
}

