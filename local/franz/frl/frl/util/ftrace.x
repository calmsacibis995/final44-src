(File |frl/util/ftrace.l|)
(generate-trace-name lambda quote concatenate)
(ftrace-entry-or-exit lambda chrct nreverse cdr car eval cons setq null liszt-internal-do mapcar sprint quote princ progn and if get for)
(ftrace-print-method lambda prin1 ftrace-indent terpri for)
(ftrace-indent lambda linel cdr - indent-to)
(ftrace-reset lambda setq)
(ftrace-instantiate lambda - finstantiate1 *break break + ftrace-entry-or-exit cdr null cond append cons shout-indented ftrace-indent terpri progn get or eval and if quote setq prog)
(ftrace-destroy lambda cons - fdestroy1 *break break cdr + ftrace-entry-or-exit list shout-indented ftrace-indent terpri progn get or eval and if quote setq prog)
(ftrace-create lambda cons - fcreate1 *break break cdr + ftrace-entry-or-exit list shout-indented ftrace-indent terpri progn get or eval and if quote setq prog)
(frun-and-trace-if-needed lambda return cons - frun *break break cdr + ftrace-print-method ftrace-entry-or-exit fname list shout-indented ftrace-indent terpri progn get or eval and if quote setq prog)
(frun-and-trace-if-removed lambda return - frun *break break cdr + ftrace-print-method ftrace-entry-or-exit fname cons shout-indented ftrace-indent terpri progn get or eval and if quote setq prog)
(frun-and-trace-if-added lambda return - frun *break break cdr + ftrace-print-method ftrace-entry-or-exit fname cons shout-indented ftrace-indent terpri progn get or eval and if quote setq prog)
(funtrace nlambda shout0 remprop liszt-internal-do mapc cons setf push set progn symeval generate-trace-name memq cond cdr car do null and if quote sremove setq)
(ftrace nlambda cddr shout0 cadr putprop set apply memq list atom if ftrace cons generate-trace-name cdr symeval and car nreverse do filter null cond quote sadd setq ftrace-reset)