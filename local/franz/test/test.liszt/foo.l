(defun baz fexpr (a)
   (print a)
   (do ((xx 1 (add1 x))
	(yy 3 (sub1 y)))
       ((null xx))
       (declare (special xx))
       (break)))

(defun foo (a b)
   (declare (*fexpr bar)
	    (fixnum c d)
	    (special c d))
   (add c d)
   (baz e f)
   (fif g h)
   (sss g))

(defun xxx (a b) (foo c d))


