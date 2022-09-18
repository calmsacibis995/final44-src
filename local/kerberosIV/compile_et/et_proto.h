#ifndef ET_PROTO_H
#define ET_PROTO_H

#include <sys/cdefs.h>
#include <stdio.h>

typedef int (*int_func) __P((const char *, int, const char *));

/* from compile_et.c */
extern char *table_name;
extern FILE *hfile, *cfile;
void yyerror __P((const char *));

/* from error_message.c */
const char *error_message __P((int));

/* from error_table.y */
extern char *current_token;
extern int table_number;
extern int current;
char *gensym __P((const char *x));
char *ds __P((const char *string));

/* from et_name.c */
char *error_table_name __P((int));

/* from init_et.c */
void init_error_table __P((const char **msgs, int base, int count));

/* from perror.c */
void com_err __P((const char *, int, const char *));
int_func set_com_err_hook __P((int_func));
void reset_com_err_hook __P((void));
void perror __P((const char *));

int yyparse __P((void));

#endif /* ET_PROTO_H */
