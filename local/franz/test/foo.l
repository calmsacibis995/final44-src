(defun lexprfoo nargs
  (cond ((eq nargs '2) 
	 (cond ((null (arg 1)) (arg 2))
	       (t (arg 1))))
	(t nargs)))
