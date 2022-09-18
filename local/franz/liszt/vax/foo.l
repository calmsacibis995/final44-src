(eval-when (compile) (msg "foo" N)) ; printed at compile time
(eval-when (load) (msg "bar" N))  ; printed at fasl time
(eval-when (eval) (msg "baz" N))  ; printed at load time (from lisp)
