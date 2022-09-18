(File ../instr.l)
(d-movespec lambda e-cvt e-move e-uncvt quote list cons setq cond makecomment)
(d-move lambda e-move e-cvt e-write2 eq e-uncvt quote list cons setq cond makecomment)
(e-move lambda e-write3 e-write2 cadr car quote eq dtpr and cond if)
