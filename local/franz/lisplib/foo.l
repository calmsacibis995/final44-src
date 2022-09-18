(defmacro top-print (&rest args)
   `(cond ((and top-level-print
		(getd top-level-print))
	   (funcall top-level-print ,@args))
	  (t (print ,@args))))
