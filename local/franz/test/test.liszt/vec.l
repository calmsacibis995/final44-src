(defun test ()
  (do ((i 0 (1+ i))
       (v (new-vectori-long 10)))
      ((eq i 10) v)
      (vseti-long v i i)
      (msg "v[" i "] = " (vrefi-long v i) N)))
