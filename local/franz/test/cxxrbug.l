(defun bug ()
   (prog (labs v-form label)
       (setq labs '((L00039 (loop . L00038)) nil))
       (setq v-form '(go loop))
       (If (setq label
	     (do ((lbs (cdar labs) (cdr lbs)))
		 ((null lbs))
		 (If (eq (caar lbs) (cadr v-form))
		    then (return (cdar lbs)))))
	   then (print 'hi))
       (return label)))

   
