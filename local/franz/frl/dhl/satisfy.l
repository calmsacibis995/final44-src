(include declar.l)

(eval-when (compile)
  (load 'dhl//rule))

(defun newvar ()
  (cons '*var* (gensym 'x)))

(declare (special replace-list)
  	 (localf replace-vars1))

(defun replace-vars (pattern)
  (let ((replace-list nil))
       (replace-vars1 pattern)))

(defun replace-vars1 (pattern)
  (cond ((null pattern) nil)
	((atom pattern) pattern)
	((is-var pattern)
	 (cond ((cdr (assq (cdr pattern) replace-list)))
	       ((t (let ((x (newvar)))
			(setq replace-list (append replace-list
						   (cons (cdr pattern) x)))
			x)))))
	((cons (replace-vars1 (car pattern))
	       (replace-vars1 (cdr pattern))))))

(defun satisfy (condition bindings)
  (cond ((eq (car condition) 'and)
	 (satisfy-all (cdr condition) bindings))
	((eq (car condition) 'or)
	 (satisfy-any (cdr condition) bindings))
	((eq (car condition) 'not)
	 (cond ((satisfy (cadr condition) bindings)
		nil)
	       (t bindings)))
	((eq (car condition) 'eval)
	 (and (eval (cadr condition))
	      bindings))
	((and (atom (car condition))
	      (getd (car condition))
	      (eq (getdisc (getd (car condition))) 'macro))
	 (satisfy (macroexpand condition) bindings))
	(t (find-possible-solutions condition bindings))))

(declare (special *donttest*))

(defun update (pattern add-flag)
  (cond ((eq (car pattern) 'and)
	 (update-all (cdr pattern) (list nil) add-flag))
	((eq (car pattern) 'eval)
	 (eval (cadr pattern))
	 (list nil))
	((eq (car pattern) 'or)
	 (update-any (cdr pattern) (list nil) add-flag))
	((eq (car pattern) 'not)
	 (update pattern (null add-flag)))
	((and add-flag
	      (atom (eval (car pattern)))
	      (eq (eval (cadr pattern)) 'instance)
	      (is-var (eval (caddr pattern))))
	 (let (($x (newsym (eval (car pattern)))))
	      (update (list (car pattern)
			    (cadr pattern)
			    (list 'quote $x))
		      add-flag)
	      (list (list (list (cdr (eval (caddr pattern)))
				$x)))))
	(t (cond ((or (is-var (eval (car pattern)))
		      (is-var (eval (cadr pattern)))
		      (is-var (eval (caddr pattern))))
		  (let ((*donttest* t))
		       (let ((s (satisfy pattern (list ()))))
			    (mapcar '(lambda (x)
					     (update (bind-to pattern x) add-flag))
				    s)
			    s)))
		 (t (cond (add-flag
			   (cond ((getd 'update-function)
				  (update-function (eval (car pattern))
						   (eval (cadr pattern))
						   (eval (caddr pattern))))
				 ((fput (eval (car pattern)) (eval (cadr pattern))
					'$value (eval (caddr pattern))))))
			  ((fremove (eval (car pattern)) (eval (cadr pattern))
				    '$value (eval (caddr pattern)))))
		    (list nil))))))
  
(defun satisfy-any (sets bindings)
  (cond ((null sets) nil)
	((and bindings
	      (append (satisfy (car sets) (copy bindings))
		      (satisfy-any (cdr sets) (copy bindings)))))))

(defun satisfy-all (sets bindings)
  (cond ((null sets) bindings)
	((mapcan '(lambda (b)
			  (let ((u (bind-to sets b)))
			       (satisfy-all (cdr u)
					    (satisfy (car u) (list b)))))
		 (copy bindings)))))

(defun update-any (sets bindings addflag)
  (do ((c sets (cdr c)))
      ((null c) 
       (return nil))
      (let ((x (update (car c) addflag)))
	   (cond (x (return x))))))

(defun update-all (sets bindings addflag)
  (cond ((null sets) bindings)
	((mapcan '(lambda (b)
			  (let ((u (bind-to sets b)))
			       (update-all (cdr u)
					   (join bindings
						 (update (car u) addflag))
					   addflag)))
		 bindings))))

(defun find-possible-solutions (c bindings)
  (let ((condition (mapcar 'eval c)))
       (cond ((or (is-var (car condition))
		  (is-var (cadr condition))
		  (is-var (caddr condition)))
	      (possible-solutions condition bindings))
	     ((eq (cadr condition) 'ako)
	      (and (ako/? (car condition)
			  (caddr condition))
		   bindings))
	     ((let ((v (fvalues-only (car condition)
				     (cadr condition)))
		    (c (caddr condition)))
		   (cond ((member c v)
			  bindings)))))))

(defun possible-solutions (condition bindings)
  (mapcan '(lambda (b)
		   (mapcar '(lambda (y) (append b y))
			   (get-possible-solutions (bind-to condition 
							    b))))
	  bindings))

(defun join (b1 b2)
  (mapcan '(lambda (x) 
		   (mapcar '(lambda (y)
				    (append (copy x) (copy y)))
			   b2))
	  b1))

;;
;;	A set of functions which searched the database for 
;;		a match to a given pattern (frame slot value),
;;		and returns all possible bindings to satisfy it,
;;		nil if none.
;;
(declare (special *donttest*))

(defvar *donttest* nil)
;;
;;	special variable to allow return patterns to include
;;	frames that were considered but don't have the desired slot/value.
;;

(defun get-possible-solutions (pattern)
  (let ((frames (car pattern))
	(slots (cadr pattern))
	(values (caddr pattern)))
       (mapcan 
	'(lambda (frame)
		 (mapcan 
		  '(lambda (slot)
			   (mapcar '(lambda (value)
					    (get-one-match frames frame
							   slots slot
							   values value))
				   (cond ((is-var values)
					  (cond ((eq slot 'instance)
						 (*rvalues-only frame slot))
						((rvalues-only frame slot))))
					 ((or *donttest* 
					      (assoc values
						     (rvalues
						      frame slot)))
					  (list values)))))
		  (cond ((is-var slots)
			 (fslots frame (cdr slots)))
			((list slots)))))
	(cond ((is-var frames)
	       (flatten-tree (ftree (cond ((frame/? (cdr frames))
					   (cdr frames))
					  ('thing)) 'instance)))
	      ((list frames))))))

(defun get-one-match (frames frame slots slot values value)
  `(,@(cond ((is-var frames)
	    `((,(cdr frames) . ,frame))))
      ,@(cond ((is-var slots)
	       `((,(cdr slots) . ,slot))))
      ,@(cond ((is-var values)
	       `((,(cdr values) . ,value))))))

(defun flatten-tree (x)
  (cond ((atom x)
	 (list x))
	((mapcan '(lambda (y)
			  (cond ((atom y)
				 (list y))
				((flatten-tree y))))
		 x))))
