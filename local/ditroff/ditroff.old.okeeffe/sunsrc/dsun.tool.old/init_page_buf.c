#include "dsun.tool.hs_h"
extern struct list * pg;
extern struct page * page_image[];
extern int total_pages;

/* 
 * Sets up the page buffer to contain five buffers arranged in a circularly
 * linked list.
 *
 * CURR_PROC_PAGE is set to point to one of the buffers. This page represents
 * the page currently being processed...i.e. the one into which characters
 * are being written.
 */

init_page_buf()
{
	struct list * first_element;
	int i;
	int lastx = 0;

	first_element = pg = (struct list *)calloc(1, sizeof(struct list));
	pg->num = 0;

	for (i = 1; i <= 4; i++){
		pg = pg->next = (struct list *)calloc(1, sizeof(struct list));
		pg->num = 0;
	}
	pg->next = first_element;

	for (i = 0; i <= 100; i++){
		page_image[i] = (struct page *)calloc(1, sizeof(struct page));
		page_image[i]->pg_image = (struct pixrect *)NULL;
	}
}

