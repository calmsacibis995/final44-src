(defun test ()
  (let ((v))
       (setf (vref (setq v (get-vector)) (get-index)) (get-val))
       v
       ))

(defun get-vector ()
  (new-vector 10 t))

(defun get-index () 6)

(defun get-val () 'foobar)
