

/* $XConsortium: pdt.c,v 5.2 91/07/24 18:45:41 hersh Exp $ */

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
 ## pdt.c : 
 ## compares the implementation dependent data in PHIGS description table
 ## against the values returned from inquiries:
 ##
 # Supplying command line argument:
 ## 1: to test pinq_phigs_facs
 ## 2: to test pinq_list_avail_gse_facs 
 ## 3: to test pinq_model_clip_facs, 
 ## 4: to test pinq_list_avail_ws_types
 */

#include "phigs/phigs.h"
#include "pdt.h"
#include "logmsg.h"
#include "computils.h"
#define BUFSIZE 1024
#define MAXGSE 64
#define BOGUSERR -999

#define ERROR(string) \
        if (err) { \
                tfprintf("ERROR: %d in %s\n", err,string);\
                return;\
        }

static void verify_list_of_avail_ws_type();
static void verify_phigs_facilities();
static void verify_gse_facilities();
static void verify_model_clip_facilities();

/* commonly used variables */

Pint total;
Pint err;
Pint status;

main(argc,argv)
	int argc;
	char **argv;
{
	int i,test;

	tbegintest("pdt","verify data from PHIGS description table");
	i_open_phigs((char *)0, PDEF_MEM_SIZE);

	if (argc < 2) {	
		verify_phigs_facilities();
		verify_gse_facilities();
		verify_model_clip_facilities();
		verify_list_of_avail_ws_type();
	} else
 	for (i = 1; i < argc; ++i) {
		test = atoi(argv[i]);
		switch(test) {
		case 1: 
			tvprintf(2,"testing pinq_phigs_facs\n");
			verify_phigs_facilities();
			break;
		case 2: 
			tvprintf(2,"testing pinq_list_avail_gse_facs\n");
			verify_gse_facilities();
			break;
		case 3: 
			tvprintf(2,"testing pinq_model_clip_facs\n");
			verify_model_clip_facilities();
			break;
		case 4: 
			tvprintf(2,"testing pinq_list_avail_ws_types\n");
			verify_list_of_avail_ws_type();
			break;
		default:
			tabort("ERROR: invalid argument \"%s\"\n",argv[i]); 
		}
	}
	tendtest();
}

/*
 * verify_list_of_avail_ws_type() 
 * Verify the implementation dependent number and list of 
 * available workstation types
 */
static void
verify_list_of_avail_ws_type() 
{
	Pint_list 	wstypelst,expwstypelst;
	Pint		i;
	char		charbuf[BUFSIZE];
	Pint		wsbuf1[BUFSIZE];
	Pint		wsbuf2[BUFSIZE];

	err = BOGUSERR;
	wstypelst.ints = wsbuf1;
	pinq_list_avail_ws_types(BUFSIZE,0,&err,&wstypelst,&total);
	ERROR("pinq_list_avail_ws_types");
	expwstypelst.num_ints = num_ws_type;
        expwstypelst.ints = wsbuf2;
        for (i=0; i<num_ws_type; ++i)
                expwstypelst.ints[i] = *list_ws_type_ptr[i];

	if (! i_compare_Pint_list(wstypelst,expwstypelst))
		tfprintf("failed: list of available ws type != expected\n");
}

/*
 * verify_phigs_facilities() 
 * Verify the implementation dependent phigs facilities
 */
static void
verify_phigs_facilities() 
{
	Pint_list	char_sets;
	Pint_list	expchar_sets;
	Pint		open_ws;
	Pint		open_ar;
	Pint		num_names;
	Pint		norm_filt;
	Pint		inv_filt;
	Pint            intbuf[BUFSIZE];
	Pint		len_list;

	char_sets.ints = intbuf;
	err = BOGUSERR;
	pinq_phigs_facs(BUFSIZE,0,&err,&open_ws,&open_ar,&num_names,&char_sets,
		&len_list,&norm_filt,&inv_filt);
	ERROR("pinq_phigs_facs");

	if (open_ws != max_open_ws)
		tfprintf("failed: max # of open ws=%d, expected %d\n",
			open_ws, max_open_ws);

	if (open_ar != max_open_ar)
		tfprintf("failed: max # of open archive files=%d, expected %d\n",
			open_ar, max_open_ar);
	if (num_names != num_names_nameset)
		tfprintf("failed: number of available names for name sets=%d, expected %d\n",
			num_names, num_names_nameset);

	expchar_sets.num_ints = num_char_set;
	expchar_sets.ints = list_char_set;
	if (!i_compare_Pint_list(char_sets,expchar_sets))
		tfprintf("failed: list of available char sets != expected\n");

	if (norm_filt != max_norm_filter)
		tfprintf("failed: max # of normal filter list for ISS=%d, expected %d\n",
			norm_filt, max_norm_filter);	

	if (inv_filt != max_inv_filter)
		tfprintf("failed: max # of inverted filter list for ISS=%d, expected %d\n",
			inv_filt, max_inv_filter);	
}

/*
 * verify_gse_facilities() 
 * Verify the implementation dependent generalized structure element facilities
 */
static void
verify_gse_facilities() 
{

	Pgse_id_dep_list gse,expgse;
	Pgse_id_dep	gsebuf[MAXGSE];
	int 		i;

	gse.id_facs = gsebuf;
	err = BOGUSERR;
	pinq_gse_facs(MAXGSE,0,&err,&gse,&total);
	ERROR("pinq_gse_facs");
	expgse.num_id_facs = num_gse;
	expgse.id_facs = list_gse_id_wsdep;
	if (! i_compare_Pgse_id_dep_list(gse,expgse))
		tfprintf("failed: list of gse's id and wsdep != expected\n");
}

/*
 * verify_model_clip_facilities() 
 * Verify the implementation dependent modelling clipping facilities
 */
static void
verify_model_clip_facilities() 
{

	Pint_list	ops,expops;
	Pint            intbuf[BUFSIZE];
	Pint		planes;

	ops.ints = intbuf;
	err = BOGUSERR;
	pinq_model_clip_facs(BUFSIZE,0,&err,&planes,&ops,&total);
	ERROR("pinq_model_clip_facs");
	if (planes != max_distinct_planes)
		tfprintf("failed: max # of distinct planes =%d, expected %d\n",
			planes, max_distinct_planes);	
	expops.num_ints = num_model_clip_op;
	expops.ints = list_model_clip_op;
	if (! i_compare_Pint_list(ops,expops))
		tfprintf("failed: list of model clip operators != expected\n");
}

