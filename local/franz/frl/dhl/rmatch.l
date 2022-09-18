(include declar.l)

(eval-when (compile)
  (load 'dhl//rule))
;;
;;	A simple set of rules to define a simple match function.
;;
;;	Match is a domain which takes to patterns and a list of 
;;		current bindings.
;;

(rule-domain match rule-domain nil (:match1 :match2 :bindings)
  (getrule poprule)
  (putrule pushrule)
  (gather possiblerules)
  (applyrule basicapplyrule))

;;
;;
;;	Simple binding function.
;;		binds variables in a to their values in the assq list in
;;		bindings.
;;

(defun bind-to (a bindings)
  (cond ((atom a) a)
	((and (is-var a)
	      (let ((x (assq (cdr a) bindings)))
		   (cond (x (cdr x))
			 (a)))))
	((cons (bind-to (car a) bindings)
	       (bind-to (cdr a) bindings)))))

;; 3 simple rules.

(rule try-recursively rule match
  (condition (and (not (atom :match1))
		  (not (atom :match2))
		  (not (is-var :match1))
		  (not (is-var :match2))))
  (action (let ((b1 (match (car :match1) 
			   (bind-to (car :match2)
				    :bindings)
			   :bindings)))
	       (cond (b1 (match (cdr :match1) 
				(bind-to (cdr :match2)
					 b1)
				b1))))))

(rule match-var rule match
  (condition (is-var :match2))
  (action (append (list (cons (cdr :match2)
			      :match1))
		  :bindings)))

(rule is-equal rule match
  (condition (equal :match1 :match2))
  (action (or :bindings
	      (list nil))))
