(include declar)

(eval-when (compile)
  (load 'dhl//rule)
  (load 'dhl//rule2))

;;
;;	Fast hand coded towers of hanoi example, same functionality
;;		as the file dhl//tower.l
;;	Do not load dhl//tower and dhl//besttower together into the
;;		same FRL.
;;

(fassert disk 
  (ako ($value (thing)))
  (size)
  (peg)
  (on)
  (underneath))

(fassert disk1 
  (ako ($value (disk)))
  (size ($value (1)))
  (peg ($value (peg1)))
  (on ($value (disk2))))

(fassert disk2 
  (ako ($value (disk)))
  (size ($value (2)))
  (peg ($value (peg1)))
  (on ($value (disk3)))
  (underneath ($value (disk1))))

(fassert disk3 
  (ako ($value (disk)))
  (size ($value (3)))
  (peg ($value (peg1)))
  (on ($value (disk4)))
  (underneath ($value (disk2))))

(fassert disk4 
  (ako ($value (disk)))
  (size ($value (4)))
  (peg ($value (peg1)))
  (on ($value (disk5)))
  (underneath ($value (disk3))))

(fassert disk5 
  (ako ($value (disk)))
  (size ($value (5)))
  (peg ($value (peg1)))
  (underneath ($value (disk4))))

(fassert peg (ako ($value (thing)))
	     (topdisk))

(fassert peg1 (ako ($value (peg)))
	      (topdisk ($value (disk1))))

(fassert peg2 (ako ($value (peg)))
	      (disk))

(fassert peg3 (ako ($value (peg)))
	      (disk))

(defun move (disk topeg)
  (let ((frompeg (fvalue-only disk 'peg)))
       (patom `(moving ,disk from ,frompeg to ,topeg))
       (terpr)
       (freplace disk 'peg '$value topeg)
       (let ((below (fvalue-only disk 'on)))
	    (cond (below (fremove below 'underneath '$value)
			 (freplace frompeg 'topdisk '$value below)
			 (fremove disk 'on '$value))
		  (t (fremove frompeg 'topdisk '$value))))
       (let ((oldtopdisk (fvalue-only topeg 'topdisk)))
	    (cond (oldtopdisk (freplace topeg 'topdisk '$value disk)
			      (fput oldtopdisk 'underneath '$value disk)
			      (fput disk 'on '$value oldtopdisk))
		  (t (fput topeg 'topdisk '$value disk))))))

;;
;;	Information to help sort and select rules.
;;

(fassert toh-rules 
  (ako ($value (thing))))

(defun slot-for-rule (:goal)
  (let ((a (car :goal)))
       (cond ((is-var a)
	      (concat (length :goal)))
	     (a))))
;;
;;	:value is the new rule being added.
;;

(defun add-toh-rule ()
  (fput 'toh-rules 
	(slot-for-rule (lhs :value))
	'$value
	:value))

(defun remove-toh-rule ()
  (fremove 'toh-rules
	   (slot-for-rule (lhs :value))
	   '$value
	   :value))

(defun best-select-toh-rule (domain :goal)
  (cond ((*fvalues-only 'toh-rules (car :goal)))
	((*fvalues-only 'toh-rules (concat (length :goal))))))

(rule-domain toh rule-domain nil (:goal)
  (getrule poprule)
  (putrule pushrule)
  (applyrule toh-applyrule)
  (gather best-select-toh-rule)
  (put add-toh-rule)
  (remove remove-toh-rule))

(defun toh-applyrule (rule goal)
  (let ((bindings (match goal (lhs rule) nil)))
       (cond (bindings
	      (interpret (bind-to (rhs rule) bindings))))))

(setsyntax '/? 'macro 'makvar)

(defun interpret (rhs)
  (cond ((atom rhs) rhs)
	((dtpr (car rhs))
	 (interpret (cons (interpret (car rhs))
			  (cond ((interpret (cdr rhs)))
				((cdr rhs))))))
	((eq (car rhs) 'quote)
	 rhs)
	((eq (car rhs) 'eval)
	 (apply (car rhs) (cdr rhs)))
	((eq (car rhs) 'and)
	 (do-and (cdr rhs)))
	((eq (car rhs) 'or)
	 (do-or (cdr rhs)))
	((toh (mapcar 'interpret rhs)))))

(defun do-and (args)
  (do ((andargs args (cdr andargs))
       (result t (interpret (car andargs))))
      ((null andargs)
       result)
      (cond ((null result)
	     (return nil)))))

(defun do-or (args)
  (cond ((zerop args) t)
	((do ((orargs args (cdr orargs))
	      (result nil (interpret (car orargs))))
	     (result result)
	     (cond ((null orargs)
		    (return result)))))))

(rule move-disk rule toh
  (lhs (move ?disk to ?peg))
  (rhs (and (legal-move ?disk to ?peg)
	    (eval (move '?disk '?peg)))))

(rule legal-move rule toh
  (lhs (legal-move ?disk to ?peg))
  (rhs (or (and (or (?peg topdisk nil)
		    (> ((?peg topdisk) size)
		       (?disk size)))
		(?disk underneath nil))
	   (and (cleartop ?disk to ?peg)
		(move-smaller-disks-than ?disk ?peg)
		(legal-move ?disk to ?peg)))))

(rule move-smaller-disks rule toh
  (lhs (move-smaller-disks-than ?disk ?peg))
  (rhs (or (?peg topdisk nil)
	   (> ((?peg topdisk) size)
	      (?disk size))
	   (and (move (?peg topdisk) to
		      (otherpeg ?peg (?disk peg)))
		(move-smaller-disks-than ?disk ?peg)))))

(rule >-rule rule toh
  (lhs (> ?a ?b))
  (rhs (eval (> (interpret '?a) 
		(interpret '?b)))))

(rule cleartop rule toh
  (lhs (cleartop ?disk to ?dontusethispeg))
  (rhs (or (?disk underneath nil)
	   (and (move (?disk underneath) to
		      (otherpeg ?dontusethispeg (?disk peg)))
		(cleartop ?disk to ?dontusethispeg)))))

(rule getvalue rule toh
  (lhs (?x ?y))
  (rhs (eval (and (fframe (interpret '?x))
		  (fvalue-only (interpret '?x) 
			       (interpret '?y))))))

(rule checkvalue rule toh
  (lhs (?x ?y ?z))
  (rhs (eval (and (or (and (null (interpret '?z))
			   (null (fvalues-only (interpret '?x)
					       (interpret '?y))))
		      (and (fframe (interpret '?x))
			   (memq (interpret '?z)
				 (fvalues-only (interpret '?x)
					       (interpret '?y)))))))))

(rule otherpeg rule toh
  (lhs (otherpeg ?peg1 ?peg2))
  (rhs (eval (getotherpeg (interpret '?peg1)
			  (interpret '?peg2)))))

(defun getotherpeg (peg1 peg2)
  (car (delete peg1 (delete peg2 (copy '(peg1 peg2 peg3))))))
