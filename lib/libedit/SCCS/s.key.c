h11705
s 00002/00002/00698
d D 8.1 93/06/04 16:51:31 bostic 5 4
c 4.4BSD snapshot (revision 8.1); add 1993 to copyright
e
s 00001/00000/00699
d D 5.4 93/03/02 17:28:00 marc 4 3
c fix per ~bugs/4.4BSD-alpha/bin/3
e
s 00013/00002/00686
d D 5.3 92/10/12 01:56:19 christos 3 2
c Fixed bug with incorrectly freeing xk_exe nodes
e
s 00006/00035/00682
d D 5.2 92/07/03 00:23:45 christos 2 1
c Up-to-date with cornell's last RCS version
e
s 00717/00000/00000
d D 5.1 92/06/22 18:08:21 bostic 1 0
c date and time created 92/06/22 18:08:21 by bostic
e
u
U
t
T
I 1
/*-
D 5
 * Copyright (c) 1992 The Regents of the University of California.
 * All rights reserved.
E 5
I 5
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
E 5
 *
 * This code is derived from software contributed to Berkeley by
 * Christos Zoulas of Cornell University.
 *
 * %sccs.include.redist.c%
 */

D 2
#ifndef lint
E 2
I 2
#if !defined(lint) && !defined(SCCSID)
E 2
static char sccsid[] = "%W% (Berkeley) %G%";
D 2
#endif /* not lint */
E 2
I 2
#endif /* not lint && not SCCSID */
E 2

/*
D 2
 * el.key.c: This module contains the procedures for maintaining
 *	      the extended-key map.
E 2
I 2
 * key.c: This module contains the procedures for maintaining
 *	  the extended-key map.
E 2
 *
 *      An extended-key (key) is a sequence of keystrokes introduced 
 *	with an sequence introducer and consisting of an arbitrary 
 *	number of characters.  This module maintains a map (the el->el_key.map) 
 *	to convert these extended-key sequences into input strs 
 *	(XK_STR), editor functions (XK_CMD), or unix commands (XK_EXE).
 *
 *      Warning:
 *	  If key is a substr of some other keys, then the longer
 *	  keys are lost!!  That is, if the keys "abcd" and "abcef"
 *	  are in el->el_key.map, adding the key "abc" will cause the first two
 *	  definitions to be lost.
 *
 *      Restrictions:
 *      -------------
 *      1) It is not possible to have one key that is a
 *	   substr of another.
 */
#include "sys.h"
#include <string.h>
#include <stdlib.h>

#include "el.h"

/* 
 * The Nodes of the el->el_key.map.  The el->el_key.map is a linked list 
 * of these node elements
 */
struct key_node_t {
    char        ch;		/* single character of key 		*/
    int         type;		/* node type				*/
    key_value_t val; 		/* command code or pointer to str, 	*/
				/* if this is a leaf 			*/
    struct key_node_t *next;	/* ptr to next char of this key 	*/
    struct key_node_t *sibling;	/* ptr to another key with same prefix 	*/
};

private	int            node_trav	__P((EditLine *, key_node_t *, char *, 
					     key_value_t *));
private	int            node__try	__P((key_node_t *, char *, 
					     key_value_t *, int));
private	key_node_t    *node__get	__P((int));
private	void	       node__put	__P((key_node_t *));
private	int	       node__delete	__P((key_node_t **, char *));
private	int	       node_lookup 	__P((EditLine *, char *, key_node_t *,
					     int));
private	int	       node_enum	__P((EditLine *, key_node_t *, int));
D 2
private	void	       key_kprint	__P((EditLine *, char *, 
					     key_value_t *, int));
E 2
private	int	       key__decode_char	__P((char *, int, int));

#define KEY_BUFSIZ	EL_BUFSIZ


/* key_init():
 *	Initialize the key maps
 */
protected int
key_init(el)
    EditLine *el;
{
    el->el_key.buf = (char *) el_malloc(KEY_BUFSIZ);
    el->el_key.map = NULL;
    key_reset(el);
    return 0;
} 


/* key_end():
 *	Free the key maps
 */
protected void
key_end(el)
    EditLine *el;
{
    el_free((ptr_t) el->el_key.buf);
    el->el_key.buf = NULL;
    /* XXX: provide a function to clear the keys */
    el->el_key.map = NULL;
} 


/* key_map_cmd():
 *	Associate cmd with a key value
 */
protected key_value_t *
key_map_cmd(el, cmd)
    EditLine *el;
    int cmd;
{
    el->el_key.val.cmd = (el_action_t) cmd;
    return &el->el_key.val;
}


/* key_map_str():
 *	Associate str with a key value
 */
protected key_value_t *
key_map_str(el, str)
    EditLine *el;
    char  *str;
{
    el->el_key.val.str = str;
    return &el->el_key.val;
}


/* key_reset():
 *	Takes all nodes on el->el_key.map and puts them on free list.  Then
 *	initializes el->el_key.map with arrow keys
 *	[Always bind the ansi arrow keys?]
 */
protected void
key_reset(el)
    EditLine *el;
{
D 2
    static char strA[] = {033, '[', 'A', '\0'};
    static char strB[] = {033, '[', 'B', '\0'};
    static char strC[] = {033, '[', 'C', '\0'};
    static char strD[] = {033, '[', 'D', '\0'};
    static char stOA[] = {033, 'O', 'A', '\0'};
    static char stOB[] = {033, 'O', 'B', '\0'};
    static char stOC[] = {033, 'O', 'C', '\0'};
    static char stOD[] = {033, 'O', 'D', '\0'};

E 2
    node__put(el->el_key.map);
    el->el_key.map = NULL;
D 2
	key_add(el, strA, key_map_cmd(el, ED_PREV_HISTORY), XK_CMD);
	key_add(el, strB, key_map_cmd(el, ED_NEXT_HISTORY), XK_CMD);
	key_add(el, strC, key_map_cmd(el, ED_NEXT_CHAR),    XK_CMD);
	key_add(el, strD, key_map_cmd(el, ED_PREV_CHAR),    XK_CMD);
	key_add(el, stOA, key_map_cmd(el, ED_PREV_HISTORY), XK_CMD);
	key_add(el, stOB, key_map_cmd(el, ED_NEXT_HISTORY), XK_CMD);
	key_add(el, stOC, key_map_cmd(el, ED_NEXT_CHAR),    XK_CMD);
	key_add(el, stOD, key_map_cmd(el, ED_PREV_CHAR),    XK_CMD);
    if (el->el_map.type == MAP_VI) {
	key_add(el, &strA[1], key_map_cmd(el, ED_PREV_HISTORY), XK_CMD);
	key_add(el, &strB[1], key_map_cmd(el, ED_NEXT_HISTORY), XK_CMD);
	key_add(el, &strC[1], key_map_cmd(el, ED_NEXT_CHAR),    XK_CMD);
	key_add(el, &strD[1], key_map_cmd(el, ED_PREV_CHAR),    XK_CMD);
	key_add(el, &stOA[1], key_map_cmd(el, ED_PREV_HISTORY), XK_CMD);
	key_add(el, &stOB[1], key_map_cmd(el, ED_NEXT_HISTORY), XK_CMD);
	key_add(el, &stOC[1], key_map_cmd(el, ED_NEXT_CHAR),    XK_CMD);
	key_add(el, &stOD[1], key_map_cmd(el, ED_PREV_CHAR),    XK_CMD);
    }
    return;
E 2
I 2
    return;
E 2
}


/* key_get():
 *	Calls the recursive function with entry point el->el_key.map
 *      Looks up *ch in map and then reads characters until a
 *      complete match is found or a mismatch occurs. Returns the
 *      type of the match found (XK_STR, XK_CMD, or XK_EXE).
 *      Returns NULL in val.str and XK_STR for no match.  
 *      The last character read is returned in *ch.
 */
protected int
key_get(el, ch, val)
    EditLine    *el;
    char        *ch;
    key_value_t *val;
{
    return node_trav(el, el->el_key.map, ch, val);
}



/* key_add():
 *      Adds key to the el->el_key.map and associates the value in val with it.
 *      If key is already is in el->el_key.map, the new code is applied to the
 *      existing key. Ntype specifies if code is a command, an
 *      out str or a unix command.
 */
protected void
key_add(el, key, val, ntype)
    EditLine    *el;
    char        *key;
    key_value_t *val;
    int          ntype;
{
    if (key[0] == '\0') {
	(void) fprintf(el->el_errfile, 
		       "key_add: Null extended-key not allowed.\n");
	return;
    }

    if (ntype == XK_CMD && val->cmd == ED_SEQUENCE_LEAD_IN) {
	(void) fprintf(el->el_errfile,
		       "key_add: sequence-lead-in command not allowed\n");
	return;
    }

    if (el->el_key.map == NULL)
	/* tree is initially empty.  Set up new node to match key[0] */
	el->el_key.map = node__get(key[0]);	/* it is properly initialized */

    /* Now recurse through el->el_key.map */
    (void) node__try(el->el_key.map, key, val, ntype);	
    return;
}


/* key_clear():
 *
 */
protected void
key_clear(el, map, in)
    EditLine *el;
    el_action_t *map;
    char   *in;
{
    if ((map[(unsigned char) *in] == ED_SEQUENCE_LEAD_IN) &&
	((map == el->el_map.key && 
	  el->el_map.alt[(unsigned char) *in] != ED_SEQUENCE_LEAD_IN) ||
	 (map == el->el_map.alt && 
	  el->el_map.key[(unsigned char) *in] != ED_SEQUENCE_LEAD_IN)))
	(void) key_delete(el, in);
}


/* key_delete():
 *      Delete the key and all longer keys staring with key, if
 *      they exists.
 */
protected int
key_delete(el, key)
    EditLine *el;
    char   *key;
{
    if (key[0] == '\0') {
	(void) fprintf(el->el_errfile, 
		       "key_delete: Null extended-key not allowed.\n");
	return -1;
    }

    if (el->el_key.map == NULL)
	return 0;

    (void) node__delete(&el->el_key.map, key);
    return 0;
}


/* key_print():
 *	Print the binding associated with key key.
 *	Print entire el->el_key.map if null
 */
protected void
key_print(el, key)
    EditLine *el;
    char   *key;
{
    /* do nothing if el->el_key.map is empty and null key specified */
    if (el->el_key.map == NULL && *key == 0)
	return;

    el->el_key.buf[0] =  '"';
    if (node_lookup(el, key, el->el_key.map, 1) <= -1)
	/* key is not bound */
	(void) fprintf(el->el_errfile, "Unbound extended key \"%s\"\n", key);
    return;
}


/* node_trav():
 *	recursively traverses node in tree until match or mismatch is
 * 	found.  May read in more characters.
 */
private int
node_trav(el, ptr, ch, val)
    EditLine     *el;
    key_node_t   *ptr;
    char         *ch;
    key_value_t  *val;
{
    if (ptr->ch == *ch) {
	/* match found */
	if (ptr->next) {
	    /* key not complete so get next char */
	    if (el_getc(el, ch) != 1) {	/* if EOF or error */
		val->cmd = ED_END_OF_FILE;
		return XK_CMD;/* PWP: Pretend we just read an end-of-file */
	    }
	    return node_trav(el, ptr->next, ch, val);
	}
	else {
	    *val = ptr->val;
	    if (ptr->type != XK_CMD)
		*ch = '\0';
	    return ptr->type;
	}
    }
    else {
	/* no match found here */
	if (ptr->sibling) {
	    /* try next sibling */
	    return node_trav(el, ptr->sibling, ch, val);
	}
	else {
	    /* no next sibling -- mismatch */
	    val->str = NULL;
	    return XK_STR;
	}
    }
}


/* node__try():
 * 	Find a node that matches *str or allocate a new one
 */
private int
node__try(ptr, str, val, ntype)
    key_node_t   *ptr;
    char         *str;
    key_value_t  *val;
    int           ntype;
{
    if (ptr->ch != *str) {
	key_node_t *xm;

	for (xm = ptr; xm->sibling != NULL; xm = xm->sibling)
	    if (xm->sibling->ch == *str)
		break;
	if (xm->sibling == NULL)
	    xm->sibling = node__get(*str);	/* setup new node */
	ptr = xm->sibling;
    }

    if (*++str == '\0') {
	/* we're there */
	if (ptr->next != NULL) {
	    node__put(ptr->next);	/* lose longer keys with this prefix */
	    ptr->next = NULL;
	}
D 3
	switch (ptr->type = ntype) {
E 3
I 3
	switch (ptr->type) {
E 3
	case XK_CMD:
I 4
	case XK_NOD:
E 4
D 3
	    ptr->val = *val;
E 3
	    break;
	case XK_STR:
	case XK_EXE:
	    if (ptr->val.str)
		el_free((ptr_t) ptr->val.str);
I 3
	    break;
	default:
	    abort();
	    break;
	}

	switch (ptr->type = ntype) {
	case XK_CMD:
	    ptr->val = *val;
	    break;
	case XK_STR:
	case XK_EXE:
E 3
	    ptr->val.str = strdup(val->str);
	    break;
	default:
	    abort();
	    break;
	}
    }
    else {
	/* still more chars to go */
	if (ptr->next == NULL)
	    ptr->next = node__get(*str);	/* setup new node */
	(void) node__try(ptr->next, str, val, ntype);
    }
    return 0;
}


/* node__delete():
 *	Delete node that matches str
 */
private int
node__delete(inptr, str)
    key_node_t **inptr;
    char   *str;
{
    key_node_t *ptr;
    key_node_t *prev_ptr = NULL;

    ptr = *inptr;

    if (ptr->ch != *str) {
	key_node_t *xm;

	for (xm = ptr; xm->sibling != NULL; xm = xm->sibling)
	    if (xm->sibling->ch == *str)
		break;
	if (xm->sibling == NULL)
	    return 0;
	prev_ptr = xm;
	ptr = xm->sibling;
    }

    if (*++str == '\0') {
	/* we're there */
	if (prev_ptr == NULL)
	    *inptr = ptr->sibling;
	else
	    prev_ptr->sibling = ptr->sibling;
	ptr->sibling = NULL;
	node__put(ptr);
	return 1;
    }
    else if (ptr->next != NULL && node__delete(&ptr->next, str) == 1) {
	if (ptr->next != NULL)
	    return 0;
	if (prev_ptr == NULL)
	    *inptr = ptr->sibling;
	else
	    prev_ptr->sibling = ptr->sibling;
	ptr->sibling = NULL;
	node__put(ptr);
	return 1;
    }
    else {
	return 0;
    }
}

/* node__put():
 *	Puts a tree of nodes onto free list using free(3).
 */
private void
node__put(ptr)
    key_node_t *ptr;
{
    if (ptr == NULL)
	return;

    if (ptr->next != NULL) {
	node__put(ptr->next);
	ptr->next = NULL;
    }

    node__put(ptr->sibling);

    switch (ptr->type) {
    case XK_CMD:
    case XK_NOD:
	break;
    case XK_EXE:
    case XK_STR:
	if (ptr->val.str != NULL)
	    el_free((ptr_t) ptr->val.str);
	break;
    default:
	abort();
	break;
    }
    el_free((ptr_t) ptr);
}


/* node__get():
 *	Returns pointer to an key_node_t for ch.
 */
private key_node_t *
node__get(ch)
    int    ch;
{
    key_node_t *ptr;

    ptr = (key_node_t *) el_malloc((size_t) sizeof(key_node_t));
    ptr->ch = ch;
    ptr->type = XK_NOD;
    ptr->val.str = NULL;
    ptr->next = NULL;
    ptr->sibling = NULL;
    return ptr;
}



/* node_lookup():
 *	look for the str starting at node ptr.
 *	Print if last node
 */
private int
node_lookup(el, str, ptr, cnt)
    EditLine   *el;
    char       *str;
    key_node_t *ptr;
    int         cnt;
{
    int     ncnt;

    if (ptr == NULL)
	return -1;		/* cannot have null ptr */

    if (*str == 0) {
	/* no more chars in str.  node_enum from here. */
	(void) node_enum(el, ptr, cnt);
	return 0;
    }
    else {
	/* If match put this char into el->el_key.buf.  Recurse */
	if (ptr->ch == *str) {
	    /* match found */
	    ncnt = key__decode_char(el->el_key.buf, cnt, 
				    (unsigned char) ptr->ch);
	    if (ptr->next != NULL)
		/* not yet at leaf */
		return node_lookup(el, str + 1, ptr->next, ncnt + 1);
	    else {
		/* next node is null so key should be complete */
		if (str[1] == 0) {
		    el->el_key.buf[ncnt + 1] = '"';
		    el->el_key.buf[ncnt + 2] = '\0';
		    key_kprint(el, el->el_key.buf, &ptr->val, ptr->type);
		    return 0;
		}
		else
		    return -1;/* mismatch -- str still has chars */
	    }
	}
	else {
	    /* no match found try sibling */
	    if (ptr->sibling)
		return node_lookup(el, str, ptr->sibling, cnt);
	    else
		return -1;
	}
    }
}


/* node_enum():
 *	Traverse the node printing the characters it is bound in buffer
 */
private int
node_enum(el, ptr, cnt)
    EditLine *el;
    key_node_t *ptr;
    int     cnt;
{
    int     ncnt;

    if (cnt >= KEY_BUFSIZ - 5) {	/* buffer too small */
	el->el_key.buf[++cnt] = '"';
	el->el_key.buf[++cnt] = '\0';
	(void) fprintf(el->el_errfile, 
		    "Some extended keys too long for internal print buffer");
	(void) fprintf(el->el_errfile, " \"%s...\"\n", el->el_key.buf);
	return 0;
    }

    if (ptr == NULL) {
#ifdef DEBUG_EDIT
	(void) fprintf(el->el_errfile, "node_enum: BUG!! Null ptr passed\n!");
#endif
	return -1;
    }

    /* put this char at end of str */
    ncnt = key__decode_char(el->el_key.buf, cnt, (unsigned char) ptr->ch);
    if (ptr->next == NULL) {
	/* print this key and function */
	el->el_key.buf[ncnt + 1] = '"';
	el->el_key.buf[ncnt + 2] = '\0';
	key_kprint(el, el->el_key.buf, &ptr->val, ptr->type);
    }
    else
	(void) node_enum(el, ptr->next, ncnt + 1);

    /* go to sibling if there is one */
    if (ptr->sibling)
	(void) node_enum(el, ptr->sibling, cnt);
    return 0;
}


/* key_kprint():
 *	Print the specified key and its associated
 *	function specified by val
 */
D 2
private void
E 2
I 2
protected void
E 2
key_kprint(el, key, val, ntype)
    EditLine      *el;
    char          *key;
    key_value_t   *val;
    int            ntype;
{
    el_bindings_t *fp;
    char unparsbuf[EL_BUFSIZ];
    static char *fmt = "%-15s->  %s\n";

    if (val != NULL)
	switch (ntype) {
	case XK_STR:
	case XK_EXE:
	    (void) fprintf(el->el_errfile, fmt, key, 
			   key__decode_str(val->str, unparsbuf, 
					      ntype == XK_STR ? "\"\"" : "[]"));
	    break;
	case XK_CMD:
	    for (fp = el->el_map.help; fp->name; fp++) 
		if (val->cmd == fp->func) {
		    (void) fprintf(el->el_errfile, fmt, key, fp->name);
		    break;
		}
#ifdef DEBUG_KEY
	    if (fp->name == NULL) 
		(void) fprintf(el->el_errfile, "BUG! Command not found.\n");
#endif

	    break;
	default:
	    abort();
	    break;
	}
    else
	(void) fprintf(el->el_errfile, fmt, key, "no input");
}


/* key__decode_char():
 *	Put a printable form of char in buf.
 */
private int
key__decode_char(buf, cnt, ch)
    char *buf;
    int   cnt, ch;
{
    if (ch == 0) {
	buf[cnt++] = '^';
	buf[cnt] = '@';
	return cnt;
    }

    if (iscntrl(ch)) {
	buf[cnt++] = '^';
	if (ch == '\177')
	    buf[cnt] = '?';
	else
	    buf[cnt] = ch | 0100;
    }
    else if (ch == '^') {
	buf[cnt++] = '\\';
	buf[cnt] = '^';
    }
    else if (ch == '\\') {
	buf[cnt++] = '\\';
	buf[cnt] = '\\';
    }
    else if (ch == ' ' || (isprint(ch) && !isspace(ch))) {
	buf[cnt] = ch;
    }
    else {
	buf[cnt++] = '\\';
	buf[cnt++] = ((ch >> 6) & 7) + '0';
	buf[cnt++] = ((ch >> 3) & 7) + '0';
	buf[cnt] = (ch & 7) + '0';
    }
    return cnt;
}

/* key__decode_str():
 *	Make a printable version of the ey
 */
protected char *
key__decode_str(str, buf, sep)
    char   *str;
    char   *buf;
    char   *sep;
{
    char *b, *p;

    b = buf;
    if (sep[0] != '\0')
	*b++ = sep[0];
    if (*str == 0) {
	*b++ = '^';
	*b++ = '@';
	if (sep[0] != '\0' && sep[1] != '\0')
	    *b++ = sep[1];
	*b++ = 0;
	return buf;
    }

    for (p = str; *p != 0; p++) {
	if (iscntrl((unsigned char) *p)) {
	    *b++ = '^';
	    if (*p == '\177')
		*b++ = '?';
	    else
		*b++ = *p | 0100;
	}
	else if (*p == '^' || *p == '\\') {
	    *b++ = '\\';
	    *b++ = *p;
	}
	else if (*p == ' ' || (isprint((unsigned char) *p) && 
			       !isspace((unsigned char) *p))) {
	    *b++ = *p;
	}
	else {
	    *b++ = '\\';
	    *b++ = ((*p >> 6) & 7) + '0';
	    *b++ = ((*p >> 3) & 7) + '0';
	    *b++ = (*p & 7) + '0';
	}
    }
    if (sep[0] != '\0' && sep[1] != '\0')
	*b++ = sep[1];
    *b++ = 0;
    return buf;			/* should check for overflow */
}
E 1
