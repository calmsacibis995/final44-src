(File ../array.l)
(d-arrayindexcomp lambda *throw throw |1+| terpri niceprint patom comp-msg progn comp-err apply list setq quote cons do length eq car cdr null cond if)
(d-dostore lambda |1-| decr d-move d-superrplacx car list rplaca ncons d-pushargs gensym cdr d-arrayindexcomp quote cons setq cond makecomment let)
(d-handlearrayref lambda d-supercxr list d-arrayindexcomp cddr cadr d-dostore cdr length |1+| eq if cons setq cond makecomment quote car get let)
