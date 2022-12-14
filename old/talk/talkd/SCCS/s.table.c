h26364
s 00005/00004/00212
d D 5.3 94/04/02 15:23:57 bostic 3 2
c put redistributable notice on it, I'm putting it in 4.4BSD-Lite
e
s 00001/00001/00215
d D 5.2 92/10/17 13:26:53 bostic 2 1
c TWO BUGS (printf doesn't take a FILE *, plus wrong arg to gettimeofday)
c lint to make cc shut up
e
s 00216/00000/00000
d D 5.1 92/10/17 13:23:57 bostic 1 0
c date and time created 92/10/17 13:23:57 by bostic
e
u
U
t
T
I 1
D 3
/*
 * Copyright (c) 1983 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
E 3
I 3
/*-
 * Copyright (c) 1983, 1985
 *	The Regents of the University of California.  All rights reserved.
 *
 * %sccs.include.redist.c%
E 3
 */

#ifndef lint
static char sccsid[] = "@(#)table.c	5.1 (Berkeley) 6/6/85";
#endif not lint

/*
 * Routines to handle insertion, deletion, etc on the table
 * of requests kept by the daemon. Nothing fancy here, linear
 * search on a double-linked list. A time is kept with each 
 * entry so that overly old invitations can be eliminated.
 *
 * Consider this a mis-guided attempt at modularity
 */
#include <stdio.h>
#include <sys/time.h>

#include "ctl.h"

#define MAX_ID 16000	/* << 2^15 so I don't have sign troubles */

#define NIL ((TABLE_ENTRY *)0)

extern	int debug;
struct	timeval tp;
D 2
struct	timezone *txp;
E 2
I 2
struct	timezone txp;
E 2

typedef struct table_entry TABLE_ENTRY;

struct table_entry {
	CTL_MSG request;
	long	time;
	TABLE_ENTRY *next;
	TABLE_ENTRY *last;
};

TABLE_ENTRY	*table = NIL;
CTL_MSG *find_request();
CTL_MSG *find_match();
char	*malloc();

/*
 * Look in the table for an invitation that matches the current
 * request looking for an invitation
 */
CTL_MSG *
find_match(request)
	CTL_MSG *request;
{
	TABLE_ENTRY *ptr;
	extern FILE *debugout;
	long current_time;

	gettimeofday(&tp, &txp);
	current_time = tp.tv_sec;
	if (debug) {
		fprintf(debugout, "Entering Look-Up with : \n");
		print_request(request);
	}
	for (ptr = table; ptr != NIL; ptr = ptr->next) {
		if ((ptr->time - current_time) > MAX_LIFE) {
			/* the entry is too old */
			if (debug) {
				fprintf(debugout
					,"Deleting expired entry : \n");
				print_request(&ptr->request);
			}
			delete(ptr);
			continue;
		}
		if (debug)
			print_request(&ptr->request);
		if (strcmp(request->l_name, ptr->request.r_name) == 0 &&
		    strcmp(request->r_name, ptr->request.l_name) == 0 &&
		     ptr->request.type == LEAVE_INVITE)
			return (&ptr->request);
	}
	return ((CTL_MSG *)0);
}

/*
 * Look for an identical request, as opposed to a complimentary
 * one as find_match does 
 */
CTL_MSG *
find_request(request)
	CTL_MSG *request;
{
	TABLE_ENTRY *ptr;
	extern FILE *debugout;
	long current_time;

	gettimeofday(&tp, &txp);
	current_time = tp.tv_sec;
	/*
	 * See if this is a repeated message, and check for
	 * out of date entries in the table while we are it.
	 */
	if (debug) {
		fprintf(debugout, "Entering find_request with : \n");
		print_request(request);
	}
	for (ptr = table; ptr != NIL; ptr = ptr->next) {
		if ((ptr->time - current_time) > MAX_LIFE) {
			/* the entry is too old */
			if (debug) {
				fprintf(debugout
					, "Deleting expired entry : \n");
				print_request(&ptr->request);
			}
			delete(ptr);
			continue;
		}
		if (debug)
			print_request(&ptr->request);
		if (strcmp(request->r_name, ptr->request.r_name) == 0 &&
		    strcmp(request->l_name, ptr->request.l_name) == 0 &&
		    request->type == ptr->request.type &&
		    request->pid == ptr->request.pid) {
			/* update the time if we 'touch' it */
			ptr->time = current_time;
			return (&ptr->request);
		}
	}
	return ((CTL_MSG *)0);
}

insert_table(request, response)
	CTL_MSG *request;
	CTL_RESPONSE *response;
{
	TABLE_ENTRY *ptr;
	long current_time;

	gettimeofday(&tp, &txp);
	current_time = tp.tv_sec;
	response->id_num = request->id_num = new_id();
	/* insert a new entry into the top of the list */
	ptr = (TABLE_ENTRY *)malloc(sizeof(TABLE_ENTRY));
	if (ptr == NIL) {
		fprintf(stderr, "malloc in insert_table");
		exit(1);
	}
	ptr->time = current_time;
	ptr->request = *request;
	ptr->next = table;
	if (ptr->next != NIL)
		ptr->next->last = ptr;
	ptr->last = NIL;
	table = ptr;
}

/*
 * Generate a unique non-zero sequence number
 */
new_id()
{
	static int current_id = 0;

	current_id = (current_id + 1) % MAX_ID;
	/* 0 is reserved, helps to pick up bugs */
	if (current_id == 0)
		current_id = 1;
	return (current_id);
}

/*
 * Delete the invitation with id 'id_num'
 */
delete_invite(id_num)
	int id_num;
{
	TABLE_ENTRY *ptr;
	extern FILE *debugout;

	ptr = table;

	if (debug)
		fprintf(debugout,"Entering delete_invite with %d\n", id_num);
	for (ptr = table; ptr != NIL; ptr = ptr->next) {
		if (ptr->request.id_num == id_num)
			break;
		if (debug)
			print_request(&ptr->request);
	}
	if (ptr != NIL) {
		delete(ptr);
		return (SUCCESS);
	}
	return (NOT_HERE);
}

/*
 * Classic delete from a double-linked list
 */
delete(ptr)
	TABLE_ENTRY *ptr;
{
	extern FILE *debugout;

	if (debug) {
		fprintf(debugout, "Deleting : ");
		print_request(&ptr->request);
	}
	if (table == ptr)
		table = ptr->next;
	else if (ptr->last != NIL)
		ptr->last->next = ptr->next;
	if (ptr->next != NIL)
		ptr->next->last = ptr->last;
	free((char *)ptr);
}
E 1
