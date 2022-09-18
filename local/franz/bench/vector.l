(declare (macros t))

; vector package for franz
;; contents:
;   vector creator (*vector 'name 'type 'ind1 'ind2 ...)
;	creates a vector and places it in the value cell of name.
;   vector declare (franz-vector name type ind1 ind2 ...)
;
;   (vref 'name 'ind1 'ind2 ...)  reference name[ind1][ind2]
;
;   (vstore (name 'ind1 'ind2 ...) 'val) name[ind1][ind2] := val
;
(defun *vector n
  (let ((args (listify n)))
       (let ((name (car args)))
	    (apply '*array args)
	    (set (car args) (getdata (getd (car args)))))))

(defun franz-vector fexpr (allargs)
  (do ((argsls allargs (cdr argsls))
       (args))
      ((null argsls))
      (setq args (car argsls))
      (let ((name (car args))
	    (indicies (cddr args)))
	   (putprop name indicies '*vector))))

(defmacro vref (name &rest indicies)
  `(cxr (indexexpand ,name ,indicies) ,name))

(defmacro vstore (nameandindicies value)
  `(rplacx (indexexpand ,(cadr nameandindicies) ,(cddr nameandindicies))
	   ,(cadr nameandindicies)
	   ,value))

(defmacro indexexpand (name indicies)
  (let ((formal (get name '*vector)))
       (cond ((null formal) (error "reference to undeclared vector " name))
	     (t (indexsub formal indicies)))))


(defun indexsub (formal actual)
  (cond ((null (cdr actual)) (car actual))	; always allow one arg
	((eq (length actual) (length formal))
	 (do ((ac actual (cdr ac))
	      (fo formal (cdr fo))
	      (res))
	     ((null ac) (cons '+ res))
	     (setq res (cons 
			(cond ((null (cdr fo)) (car ac))
			      (t `(* ,(car ac) ,(apply 'times (cdr fo)))))
			res))))
	(t (vector "Wrong number of subscripts to array " actual))))
