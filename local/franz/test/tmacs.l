;;;--- start-exer :: print "Testing ..." message
;
(defmacro start-exer (name)
   `(msg "Testing " ,name "..." D))

;;;--- done-exer :: declare that an exercise is finished
;	state : nil for failure
;
(defmacro done-exer (state)
   `(if (null ,state) ;then it bombed
       then (msg "failed -- breaking." N D)
	    (break)
       else (msg "done." N D)))
