(File ../vector.l)
(d-vectorsize lambda e-write2 e-quick-call e-call-qnewint concat e-write4 e-move bigp not cdr null and zerop cond if d-exp quote let)
(c-vsize-word lambda quote cadr d-vectorsize)
(c-vsize-byte lambda quote cadr d-vectorsize)
(c-vsize lambda quote cadr d-vectorsize)
(cc-vectorip lambda cadr d-typesimp)
(cc-vectorp lambda cadr d-typesimp)
(d-vectorindexcode lambda setq d-calltran e-write2 e-quick-call e-call-qnewint d-move quote e-label e-goto d-genlab let null cond if)
(d-vref lambda d-vectorindexcode e-goto not e-quick-call e-call-qnewint return caar null do assq d-handlecc e-cvt d-clearreg concat e-write4 e-write3 e-cmp eq e-label e-write2 e-tst cdr car prog1 pop |1-| decr d-fixnumexp incr setf push e-move d-move d-exp d-simple *throw throw |1+| terpri niceprint patom comp-msg progn comp-err <& fixp if list cons setq cond makecomment d-genlab quote caddr cadr let)
(d-vset lambda d-vectorindexcode e-goto e-quick-call e-call-qnewint return caar do assq d-handlecc d-clearreg concat e-write4 e-write3 e-cmp e-label e-write2 e-tst cdr car prog1 pop |1-| decr d-fixnumexp incr setf push d-move e-move and not e-cvt d-exp d-simple eq null *throw throw |1+| terpri niceprint patom comp-msg progn comp-err <& fixp if list cons setq cond makecomment d-genlab quote cadddr caddr cadr let)
(cc-vrefi-long lambda quote d-vref)
(cc-vseti-long lambda quote d-vset)
(cc-vrefi-word lambda quote d-vref)
(cc-vseti-word lambda quote d-vset)
(cc-vrefi-byte lambda quote d-vref)
(cc-vseti-byte lambda quote d-vset)
(cc-vref lambda quote d-vref)
(cc-vset lambda quote d-vset)
