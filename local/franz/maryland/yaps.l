;
; YAPS:  Yet Another Production System
;
; written by Liz Allen, Univ of Maryland
;
; YAPS is a production system based on a discrimination net similar
; to the net used by OPS5 written Forgey.  YAPS runs at comparable
; speeds with OPS5 and allows more flexibility in tests allowed on
; the left hand side of productions and in the right hand side actions.
;
; A YAPS User's Manual is available:  TR-1146 Univ of Maryland Computer
; Science Center
;

(declare
  (special
	*root*		; root of discrimination net
	*facts*		; list of facts in data base, ordered by cycle number
			;	in descending order
	*rules*		; names of all active rules in the system
	*strategy*
	*conflict-set*	; list of bindings that completely match some rule,
			;	in order of domination
	*cycle*		; current fact number
	*binding*	; bound to binding that is currently firing
	*halt*		; t iff execution should be halted after current cycle
	*trace*
	*pbreaks*	; names of production rules that will currently
			;	cause a break
	*fatal-error*
	*debugging-yaps*
	*debugging-flavors*
	)
  (macros t))

(or (boundp '*facts*)
    (progn
     (setsyntax '|^| 'macro #'(lambda nil (cons '|^| (read))))
     (allocate 'hunk1 20)
     (allocate 'hunk2 30)
     (allocate 'hunk3 40)
     (setq *facts*		nil
	   *cycle*		0
	   *conflict-set*	nil
	   *strategy*		'goal
	   *trace*		t
	   *pbreaks*		nil
	   *rules*		nil
	   *debugging-yaps*	nil
	   )))

;
; A rule object is stored on the property list:
;	(get 'rule-name 'rule) -> a rule
;

(defflavor rule (
	name
	lhs
	nots
	tests
	out-node	; node out of discrimination net where successful
			;	bindings come out.
	not-nodes	; nodes out of discrimination which contain matches
			;	for not clauses and bindings which were
			;	blocked by those matches
	)
  nil)

;
; user functions to handle production rules
;

(defmacro p (name &rest rule)
 (attempt
  (let (lhs nots
	(tests (car (for x in (cdr (memq 'test rule))
			 until (eq x '-->)
			 tcollect x)))
	(rhs (cdr (memq '--> rule))))
   (setq lhs (car
	      (for x in rule
		   unless (and (eq (car x) '|~|)
			       (push nots x))
		   until (or (eq x '-->) (eq x 'test))
		   tcollect x)))
   (if (not (atom name)) (Error "Missing rule name") (fail))
   (if (null rhs) (Error "Missing rhs") (fail))
   `(progn 'compile
	   (add-rule ',name ',lhs ',nots ',tests)
	   (and *trace* (msg T "defining rhs"))
	   (defun ,(concat '|RHS-| name) ,(get-vars lhs)
		,@rhs)))))

(defun buildp (name rule)
  (funcall 'p `(p ,name ,@rule)))

(defun rp (&rest lst)
 (for name in lst
      do (<- (get name 'rule) 'remove)
	 (remprop name 'rule)
	 (setq *rules* (delq name *rules* 1))))

(defun printp (&rest names)
 (for r in names
      bind rule
      do (setq rule (get r 'rule))
	 (if rule then (<- rule 'print)
		  else (msg r " is not a rule"))))

(defun allp nil
  (msg "Active production rules")
  (for r in (reverse *rules*) do (msg T r)))

;
; Functions and methods for manipulating rules
;

(defun add-rule (name lhs nots tests)
  (let ((old (get name 'rule))
	 *fatal-error*)
    (cond ((and old
		(equal lhs (<< old 'lhs))
		(equal nots (<< old 'nots))
		(equal tests (<< old 'tests))
		(null *debugging-yaps*))
	     (and *trace* (msg name ":" N T "already have lhs")))
	  (old
	     (and *trace* (msg name ":" N T "compiling new lhs"))
	     (<- old 'remove)
	     (add-new-rule name lhs nots tests))
	  (t (and *trace* (msg name ":" N T "compiling lhs"))
	     (push *rules* name)
	     (add-new-rule name lhs nots tests)))
    (if *fatal-error* (rp name)
		      (msg "Rule " name " not be added to system"))))

(defmethod (rule print) nil
  (msg "(p " (L name))
  (for x in lhs do (msg T (L x)))
  (and nots (for x in nots do (msg T (L x))))
  (and tests (for initially (msg "   test" -D)
		  x in tests
		  do (msg T (L x))))
  (let ((rhs (getd (concat '|RHS-| name))))
       (cond ((bcdp rhs)
		(msg "   -->" T "The rhs is compiled"))
	     (t (msg "   -->" -D)
		(for x in (cddr rhs) do (msg T (L x)))))
       (msg T ")")))

(defun add-new-rule (name lhs nots tests)
  (let ((new-rule (make-instance 'rule
		    'name name
		    'lhs lhs
		    'nots nots
		    'tests tests
		    )))
   (<- new-rule 'process-lhs)
   (putprop name new-rule 'rule)))

(defmethod (rule process-lhs) nil
 (let ((test-list (build-test-list tests)))
  (setq out-node (add-patterns-net lhs))
  (>> out-node 'next-node self)
  (<- out-node 'add-tests test-list)
  (check-test-list test-list)
  (setq not-nodes
    (car (for not-clause in nots
	      tcollect (create-not-node not-clause self
					(<< out-node 'vars)))))))

(defmethod (rule remove) nil
  (<- out-node 'remove)
  (for not-node in not-nodes do (<- not-node 'remove))
  (for x in *conflict-set*
       while (eq self (<< x 'back-link))
       do (pop *conflict-set*))
  (for bind (back *conflict-set*)
       while (cdr back)
       do (cond ((eq self (<< (cadr back) 'back-link))
		   (rplacd back (cddr back)))
		(t (setq back (cdr back))))))

(defmethod (rule add-binding) (binding xxx)
 (let ((lhs-vars (<< out-node 'vars))
	not-vars)
  (or (for not-node in not-nodes
	   thereis (setq not-vars (<< (<< not-node 'not-feed) 'vars))
		   (for cmp in (<< not-node 'not-bindings)
			bind values
			eachtime (setq values
				  (match-bindings
				    binding lhs-vars cmp not-vars
				    (<< not-node 'test-list)
				    (<< not-node 'vars)))
			when (not (eq values '$$FAIL))
			quit (>> binding 'back-link not-node)
			     (>> not-node 'blocked-bindings
				 (cons binding
				       (<< not-node 'blocked-bindings)))))
      (add-conflict-set binding))))

(defmethod (rule remove-binding) (binding)
  (setq *conflict-set* (delq binding *conflict-set* 1)))

;
; facts contain descriptions of objects stored in the database.  *facts*
; contains a list of all the facts currently stored.
;

(defflavor fact (
	cycle		; the unique cycle number for a fact
	value		; the lisp expression for the fact itself
	bindings	; the bindings which contain this fact
	)
  nil)

(defmacro fact (&rest x)
 `(add-fact ,(quotify x)))

(defun loadfacts (lst)
  (for x in lst do (add-fact x)))

(defun add-fact (x)
 (setq *cycle* (add1 *cycle*))
 (and *trace* (msg T "Adding fact:" T *cycle* ". " x))
 (let ((new-fact (make-instance 'fact
		   'cycle *cycle*
		   'value x
		   )))
  (push *facts* new-fact)
  (<- *root* 'add-fact new-fact)))

(defun db nil
 (for	initially (msg "Cycle" T "Fact")
	f in (reverse *facts*)
	do (msg (<< f 'cycle) "." T (<< f 'value))))

(defun remove (&rest lst)
 (cond ((and (boundp '*binding*) *binding*)
	  (for	x in lst
		bind f
		do (setq f (nthelem x (<< *binding* 'fact-list)))
		   (if (null f)
		       (msg x " is not the number of a lhs fact")
		       (error))
		   (<- (nthelem x (<< *binding* 'fact-list)) 'remove)))
       (t (msg "Use 'rm' when not in the scope of a rhs")
	   nil)))

(defun rm (&rest lst)
 (if (eq (car lst) '*)
  then (remove-all-facts)
  else (for cycle in lst
	    do (or (for f in *facts*
			thereis (if (eq (<< f 'cycle) cycle)
				    (<- f 'remove)
				    t))
		   (msg "There is not a fact with cycle " cycle
			" in the database.")))))

(defun remove-all-facts nil
  (for r in *rules*
       do (setq r (get r 'rule))
	  (<- (<< r 'out-node) 'remove-all-bindings)
	  (for n in (<< r 'not-nodes)
	       do (<- n 'remove-all-bindings)))
  (setq *facts* nil)
  (setq *conflict-set* nil)
  (and *trace* (msg "All facts removed from database")))

(defun refresh (&rest lst)
 (let (lst2)
  (cond ((and lst (boundp '*binding*) *binding*)
	   (setq lst2
		 (car (for bind (flst (<< *binding* 'fact-list))
			   x in lst
			   bind f
			   tcollect (setq f
				      (nthelem x (<< *binding* 'fact-list)))
				    (if (null f)
				      (msg x " is not the number of a lhs fact")
				      (error))
				    (<- f 'remove)
				    (<< f 'value)))))
	(lst
	   (msg "Use 'ref' when not in the scope of a rhs"))
	(t (setq lst2
		 (nreverse (car (for f in *facts* tcollect (<< f 'value)))))
	   (remove-all-facts)))
   (for	f in lst2 do (add-fact f))))

(defun ref (&rest cycles)
 (let (lst)
  (cond (cycles
	   (for	cycle in cycles
		do (or (for f in *facts*
			    thereis (if (eq (<< f 'cycle) cycle)
				      (<- f 'remove)
				      (push lst (<< f 'value))))
		       (msg cycle
			    " is not a cycle for a fact in the database"))))
	(t (for	f in (nreverse *facts*)
		do (<- f 'remove)
		   (push lst (<< f 'value)))))
  (for	f in (nreverse lst) do (add-fact f))))

(defmethod (fact remove-binding) (bndg)
  (delq bndg bindings 1))

(defmethod (fact add-binding) (bndg)
  (setq bindings (cons bndg bindings)))

(defmethod (fact remove) nil
 (and *trace* (msg T "Removing: " T cycle ". " value))
 (setq *facts* (delq self *facts* 1))
 (for b in bindings do (<- (<< b 'back-link) 'remove-binding b)
		       (<- b 'remove self)))

;
; The following functions are for running the system.  The user may
; set break points and traces as he desires.
;

(defun run (&optional n)
  (for	bind *binding* rule-name *halt*
	while (and *conflict-set*
		   (not (eq n 0))
		   (not *halt*))
	do (and (numberp n) (setq n (sub1 n)))
	   (setq *binding*	(pop *conflict-set*)
		 rule-name	(<< (<< *binding* 'back-link) 'name)
		 )
	   (and *trace*
		(for initially (msg "Running rule " rule-name)
			       (msg T "Facts used:")
		     f in (<< *binding* 'fact-list)
		     do (msg (T 2) (<< f 'cycle) ". " (<< f 'value))))
	   (checkpbreak (<< *binding* 'back-link))
	   (<- *binding* 'remove)
	   (apply (concat '|RHS-| rule-name)
		  (<< *binding* 'values))
	   (and *trace* (terpri)))
  (and *trace*
       (null *conflict-set*)
       (msg "No rules currently in the conflict set")))

(defun halt () (setq *halt* t))

(defun checkpbreak (rule)
 (cond ((memq (<< rule 'name) *pbreaks*)
	  (msg "Break point at rule: " (<< rule 'name))
	  (apply `(lambda ,(<< (<< rule 'out-node) 'vars) (lispbreak))
		 (<< *binding* 'values)))))

(defun trace nil (setq *trace* t))

(defun untrace nil (setq *trace* nil))

(defun pbreak (&rest lst)
 (for	p in lst
	unless (memq p *pbreaks*)
	do (push *pbreaks* p)))

(defun unbreak (&rest lst)
  (setq *pbreaks*
	(car (for p in *pbreaks*
		  unless (memq p lst)
		  tcollect p)))
   nil)

(defun prbreaks nil
 (for	initially (msg "Current break points:")
	p in *pbreaks*
	do (msg T p)))

;
; The folllowing functions manipulate and maintain the conflict set.
;

(defun cs nil
  (msg "Conflict set")
  (for	b in *conflict-set*
	i from 1
	do (msg i ". " (<< (<< b 'back-link) 'name))))

(defun rmcs (&rest lst)
 (setq *conflict-set*
       (car
	(for b in *conflict-set*
	     i from 1
	     unless (memq i lst)
	     tcollect b)))
  nil)

(defun matches (&rest lst)
  (msg "Rules matched" T "Facts used")
  (for b in *conflict-set*
       i from 1
       when (or (null lst) (memq (<< (<< b 'back-link) 'name) lst))
       do (msg i ". " (<< (<< b 'back-link) 'name))
	  (for f in (<< b 'fact-list)
	       do (msg (T 2) (<< f 'cycle) ". " (<< f 'value)))))

(defun resort-conflict-set nil
  (for  b in *conflict-set*
	do (>> b 'age-list (get-ages (<< b 'fact-list))))
  (sort *conflict-set* 'cmp-ages))

(defun add-conflict-set (b)
 (>> b 'age-list (get-ages (<< b 'fact-list)))
 (setq *conflict-set* (insert b *conflict-set* 'cmp-ages)))

(defun get-ages (fact-list)
  (cond (*strategy*
	   (let (lst1 lst2)
	     (for f in fact-list
		  do (cond ((eq (car (<< f 'value)) *strategy*)
			      (push lst1 (<< f 'cycle)))
			   (t (push lst2 (<< f 'cycle)))))
	     (cons (sort lst1 'greaterp)
		   (sort lst2 'greaterp))))
	(t (sort (car (for f in fact-list tcollect (<< f 'cycle)))
		 'greaterp))))

(defun cmp-ages (b1 b2)
  (cond (*strategy*
	   (let ((cmp (cmp-lsts (car (<< b1 'age-list))
				(car (<< b2 'age-list)))))
	     (cond ((eq cmp 'eq)
		      (cmp-lsts (cdr (<< b1 'age-list))
				(cdr (<< b2 'age-list))))
		   (t cmp))))
	(t (cmp-lsts (<< b1 'age-list)
		     (<< b2 'age-list)))))

(defun cmp-lsts (lst1 lst2)
 (for	n1 in lst1
	n2 in lst2
	do (cond ((greaterp n1 n2) (return t))
		 ((greaterp n2 n1) (return nil)))
	finally (cond (n1 t)
		      (n2 nil)
		      (t 'eq))))

;
; The following functions are used to change the strategy for ordering the
; conflict set.  By default, the system sorts the conflict set by the ages of
; the newest goals.
;

(defun directed-strategy (&optional (x 'goal))
  (cond ((eq x *strategy*))
	(t (setq *strategy* x)
	   (resort-conflict-set)))
   nil)

(defun age-only-strategy nil
  (cond ((null *strategy*))
	(t (setq *strategy* nil)
	   (resort-conflict-set)))
   nil)

(defun prstrategy nil
  (cond (*strategy*
	   (msg "(directed-strategy " '*strategy* ")"))
	(t (msg "(age-only-strategy)")))
   nil)

;
; net-nodes encode the patterns on the lhs's of production rules.  When
; facts are added to the database, they are compared against the
; net-nodes.
;

(declare (special ADD-CONS))
(or (boundp 'ADD-CONS) (setq ADD-CONS (ncons nil)))

(defflavor net-node (
	bind-nodes	; a fact that has reached this net-node may be
			;	bound to patterns via these nodes
	path		; atom like  c..r
	assoc-branch	; list of (value . net-node)
	else-branch	; don't care branch - if you don't care what the
			;	the value at the path
	)
  nil)

(defun add-patterns-net (pats)
  (let ((nodes (car (for p in pats
			 tcollect (<- *root* 'add-pattern p (get-paths p))))))
       (for while (cdr nodes)
	    do (setq nodes
		     (car
		      (for bind (pair nodes (cddr pair))
			   while pair
			   tcollect (cond ((cdr pair)
					     (join-together (car pair)
							    (cadr pair)))
					  (t (car pair)))))))
       (car nodes)))
 
(defmethod (net-node add-pattern) (pattern path-list)
 (let (new-bind path-pair next)
  (cond ((null path-list)
	   (setq new-bind (make-instance 'bind-node
			     'pattern pattern
			     'vars (get-vars pattern)
			     'net-link self
			     ))
	   (setq bind-nodes (cons new-bind bind-nodes))
	    new-bind)
	((null path)
	   (setq path (caar path-list))
	   (setq next (make-instance 'net-node))
	   (setq assoc-branch `((,(cdar path-list) . ,next)))
	   (<- next 'add-pattern pattern (cdr path-list)))
	((and (setq path-pair (assq path path-list))
	      (setq next (cdr (assq (cdr path-pair) assoc-branch))))
	   (<- next 'add-pattern pattern (delq path-pair path-list 1)))
	(path-pair
	   (setq next (make-instance 'net-node))
	   (setq assoc-branch (cons `(,(cdr path-pair) . ,next)
				     assoc-branch))
	   (<- next 'add-pattern pattern (delq path-pair path-list 1)))
	(else-branch
	   (<- else-branch 'add-pattern pattern path-list))
	(t (setq else-branch (make-instance 'net-node))
	   (<- else-branch 'add-pattern pattern path-list)))))

(defmethod (net-node add-fact) (fact)
  (for b in bind-nodes do (<- b 'add-fact fact))
  (and path
       (let ((val (apply path (rplaca ADD-CONS (<< fact 'value))))
	      next)
	    (setq next (and val (cdr (assq val assoc-branch))))
	    (and next (<- next 'add-fact fact))
	    (and else-branch (<- else-branch 'add-fact fact)))))

(defmethod (net-node remove-bind) (bnd)
  (setq bind-nodes (delq bnd bind-nodes 1)))

(or (boundp '*root*)
    (setq *root* (make-instance 'net-node 'path 'car)))

;
; bind-nodes contain patterns.  When a fact is added to the database,
; and it is sent by the net-node above this bind node as a possible
; match to its pattern, the value of the fact is compared against the
; bind-node and if there is a match, a binding is created and is fed to
; the next-node
;

(defflavor bind-node (
	pattern		; a pattern from the lhs of some rule
	vars		; the vars used in the pattern
	test-list	; tests that must be passed involving only vars
			;	appearing in this pattern
	next-node	; either a join-node, the rule matched, or a not-node
	join-how	; if next-node is a join, either 'left or 'right
	net-link	; to net-node parent
	)
  nil)

(defmethod (bind-node add-tests) (tsts)
  (setq test-list (usable-tests tsts vars)))

(defmethod (bind-node remove) nil
  (<- net-link 'remove-bind self))

(defmethod (bind-node remove-all-bindings) nil nil)

(defmethod (bind-node add-fact) (fact)
  (let ((values (unify pattern (<< fact 'value) vars))
	 new-binding)
   (if (and (not (eq values '$$FAIL))
	    (or (null test-list) (run-tests vars values test-list)))
       (create-binding (list fact) values next-node join-how))))

;
; join-nodes are the way facts that match different parts of the lhs
; of rules get matched together.  Anytime a binding is fed to a
; join-node, it is compared to all the facts that were fed in earlier
; from the other side of the join-node.  Anytime a match is found,
; a new binding is generated and passed on down to the next-node.
;

(defflavor join-node (
	left-feed
	right-feed
	left-bindings
	right-bindings
	vars
	test-list	; to join a left binding to a right binding, these
			;	tests must return something non-nil
	next-node	; either a join-node, the rule matched, or a not-node
	join-how	; either 'left or 'right if next-node is a
			;	join-node
	)
  nil)

(defun join-together (n1 n2)
 ; n1 & n2 are either bind-nodes or join-nodes
 (let ((new-join-node (make-instance 'join-node
			'left-feed n1
			'right-feed n2
			'vars (merge (<< n1 'vars) (<< n2 'vars))
			)))
      (>> n1 'next-node new-join-node) 
      (>> n1 'join-how 'left)
      (>> n2 'next-node new-join-node) 
      (>> n2 'join-how 'right)
  new-join-node))

(defmethod (join-node add-tests) (tsts)
  (if (for tst in tsts thereis tst)
      (<- left-feed 'add-tests tsts)
      (<- right-feed 'add-tests tsts)
      (setq test-list (usable-tests tsts vars))))

(defmethod (join-node add-binding) (binding how)
  ; how is 'left or 'right
  (let (cmp-bdgs left-vars right-vars)
    (setq left-vars (<< left-feed 'vars))
    (setq right-vars (<< right-feed 'vars))
    (selectq how
	     (left  (setq left-bindings (cons binding left-bindings))
		    (for cmp in right-bindings
			 do (<- self 'join-bindings binding cmp)))
	     (right (setq right-bindings (cons binding right-bindings))
		    (for cmp in left-bindings
			 do (<- self 'join-bindings cmp binding)))
	      nil)))

(defmethod (join-node join-bindings) (left-binding right-binding)
  (let ((all-values (match-bindings left-binding (<< left-feed 'vars)
				    right-binding (<< right-feed 'vars)
				    test-list vars))
	 all-facts)
       (or (eq all-values '$$FAIL)
	   (progn (setq all-facts (append (<< left-binding 'fact-list)
					  (<< right-binding 'fact-list)))
		  (create-binding all-facts all-values next-node join-how)))))

(defmethod (join-node remove-binding) (binding)
  (setq left-bindings (delq binding left-bindings 1))
  (setq right-bindings (delq binding right-bindings 1)))

(defmethod (join-node remove-all-bindings) nil
  (setq left-bindings nil)
  (setq right-bindings nil)
  (<- left-feed 'remove-all-bindings)
  (<- right-feed 'remove-all-bindings))

(defmethod (join-node remove) nil
  (for b in left-bindings do (<- b 'remove))
  (for b in right-bindings do (<- b 'remove))
  (<- left-feed 'remove)
  (<- right-feed 'remove))

;
; not-nodes are for not-clauses.  Each not-node contains bindings of facts
; which match the given not-clause and a list of bindings that would
; completely match the lhs of the production rule if it were not for the
; not clause.  Before a binding is added to the conflict set, it is compared
; against all the not-nodes to see if it is blocked.  And, whenever a new
; binding is generated that matches a not-clause, the bindings in the conflict
; set are checked to see if any of those are now blocked.
;

(defflavor not-node (
	not-feed
	not-bindings
	blocked-bindings
	vars
	test-list
	rule
	)
  nil)

(defun create-not-node (not-clause rule lhs-vars)
  (let ((new-not (make-instance 'not-node
		   'rule rule
		   'not-feed)))
       (<- new-not 'process-clause not-clause lhs-vars)
	new-not))

(defmethod (not-node process-clause) (not-clause lhs-vars)
  (let ((tsts (build-test-list (cdr (memq 'with not-clause)))))
       (setq not-feed
	 (add-patterns-net (car (for x in (cdr not-clause)
				     until (eq x 'with)
				     tcollect x))))
       (setq vars (merge lhs-vars (<< not-feed 'vars)))
       (>> not-feed 'next-node self)
       (if (for tst in tsts thereis tst)
	   (<- not-feed 'add-tests tsts)
	   (setq test-list (usable-tests tsts vars)))
       (check-test-list test-list)))

(defmethod (not-node add-binding) (binding xxx)
 (let ((lhs-vars (<< (<< rule 'out-node) 'vars))
       (not-vars (<< not-feed 'vars)))
      (setq not-bindings (cons binding not-bindings))
      (setq *conflict-set*
	(car
	 (for cmp in *conflict-set*
	      unless (if (and (eq rule (<< cmp 'back-link))
			      (not (eq (match-bindings
					 cmp lhs-vars binding not-vars
					 test-list vars)
				       '$$FAIL)))
			 (>> cmp 'back-link self)
			 (setq blocked-bindings (cons cmp blocked-bindings)))
	      tcollect cmp)))))

(defmethod (not-node remove-binding) (binding)
  (let (bdg-lst)
       (cond ((memq binding not-bindings)
		(setq not-bindings (delq binding not-bindings 1))
		(setq bdg-lst blocked-bindings)
		(setq blocked-bindings nil)
		(for bdg in bdg-lst
		     do (>> bdg 'back-link rule)
			(<- rule 'add-binding bdg nil)))
	     (t (setq blocked-bindings (delq binding blocked-bindings 1))
		 nil))))

(defmethod (not-node remove-all-bindings) nil
  (setq not-bindings nil)
  (setq blocked-bindings nil)
  (<- not-feed 'remove-all-bindings))

;
; bindings are partial (or complete) matches of facts to the lhs of
; production rules.  They may hang from join-nodes, rules or not-nodes.
;

(defflavor binding (
	fact-list	; list of facts already joined
	values		; the values of the variables matched by the facts
	back-link	; to parent join node, to rule these facts completely
			;	match, or to not-node
	age-list	; list of fact ages in descending order
	)
  nil)

(defun create-binding (fact-list values node how)
  (let ((new-binding (make-instance 'binding
		       'fact-list fact-list
		       'values values
		       'back-link node
		       )))
       (for f in fact-list do (<- f 'add-binding new-binding))
       (<- node 'add-binding new-binding how)))

(defun match-bindings (b1 vars1 b2 vars2 test-list all-vars)
 (attempt
  (let ((values (for bind result
		     var2 in vars2
		     value2 in (<< b2 'values)
		     unless (for var1 in vars1
				 value1 in (<< b1 'values)
				 thereis (and (eq var1 var2)
					      (or (equal value1 value2)
						  (fail))))
		     tcollect value2)))
   (setq values (car (lconc values (<< b1 'values))))
   (if (or (null test-list) (run-tests all-vars values test-list))
       then values
       else '$$FAIL))))

(defmethod (binding remove) (&optional fact-removed)
  (for fact in fact-list
       unless (eq fact fact-removed)
       do (<- fact 'remove-binding self)))

;
; These functions aid in adding tests to bind-nodes, join-nodes and
; not-nodes, and in running tests.
;

(defun build-test-list (tsts)
  (car (for tst in tsts tcollect (cons tst (get-vars tst)))))

(defun usable-tests (tsts vars)
  (car (for tst on tsts
	    when (and (car tst) (allmemq (cdar tst) vars))
	    tcollect (prog1 (caar tst) (rplaca tst nil)))))

(defun check-test-list (tsts)
   (and (for tst in tsts thereis tst)
	(Warn "These tests contain variables not on the lhs:"
	  N T (car (for tst in tsts
			when tst
			tcollect (car tst))))))

(defun run-tests (vars values test-list)
   (apply `(lambda ,vars (and ,@test-list)) values))

;
; Utility functions
;
; get-paths returns list of (path . atom)
;

(declare (special *paths* *vars* *values*))

(defun get-paths (x)
 (let ((*paths* (ncons nil)))
   (get-paths2 x nil)
   (car *paths*)))

(defun get-paths2 (x sofar)
 (cond ((null x))
       ((varp x))
       ((atom x)
	  (tconc *paths* (cons (concatl `(c ,@sofar r))
				x)))
       ((hunkp x)
	  (Error "Cannot have a hunk in a fact or a pattern, "
		 N T x " is ignored"))
       (t (get-paths2 (car x) (cons 'a sofar))
	  (get-paths2 (cdr x) (cons 'd sofar)))))

(defun cr (x) x)

(defun varp (x)
  (and (symbolp x)
       (eq (getchar x 1) '-)))

(defun get-vars (x)
 (let (*vars*)
   (get-vars2 x)
    *vars*))

(defun get-vars2 (x)
 (cond ((eq x '-))
       ((varp x)
	  (or (memq x *vars*)
	      (push *vars* x)))
       ((atom x))
       (t (get-vars2 (car x))
	  (get-vars2 (cdr x)))))

(defun unify (pat fact *vars*)
 (let ((*values* (car (for var in *vars* tcollect '$$NONE$$))))
  (cond ((eq (attempt (unify2 pat fact)) '$$FAIL)
	   '$$FAIL)
	(t *values*))))

(defun unify2 (pat fact)
 (let (bnd)
  (cond	((eq pat '-))
	((varp pat) (for var in *vars*
			 value on *values*
			 when (eq var pat)
			 quit (or (and (eq (car value) '$$NONE$$)
				       (rplaca value fact))
				  (equal (car value) fact)
				  (fail))))
	((numberp pat) (or (eq pat fact)
			   (equal pat fact)
			   (fail)))
	((eq pat fact))
	((atom pat) (fail))
	(t (unify2 (car pat) (car fact))
	   (unify2 (cdr pat) (cdr fact))))))

(defun allmemq (lst1 lst2)
 (for x in lst1
      always (memq x lst2)))

(defun merge (lst1 lst2)
  (car (lconc
	  (for x in lst2
	       unless (memq x lst1)
	       tcollect x)
	   lst1)))

(defun quotify (x)
 (cond ((varp x) x)
       ((atom x) `',x)
       ((hunkp x) (Error "Cannot have a hunk in a fact"))
       ((eq (car x) '|^|) (cdr x))
       (t (for y on x
	       bind tail
	       tcollect (cond ((atom y)
				(setq tail y)
				(setq y nil)
				(if (varp tail)
				    then tail
				    else `',tail))
			     (t (quotify (car y))))
	       finally (if tail
			   then `(list* ,@(car $$val))
			   else `(list ,@(car $$val)))))))

(defun list* (&rest lst)
  (cond ((null lst) nil)
	((null (cdr lst)) (car lst))
	(t (for x on lst
		do (if (null (cddr x))
		       (rplacd x (cadr x))
		       (return lst))))))

(defun insert (x lst fcn)
  (cond ((null lst) (ncons x))
	((funcall fcn x (car lst))
	   (cons x lst))
	(t (for	y in (cdr lst)
		back on lst
		when (funcall fcn x y)
		do (return (rplacd back (cons x (cdr back))))
		finally ; x belongs at the end
			(rplacd back (ncons x)))
	    lst)))
;
; Some extra arithmetic functions.
;

(defmacro >= (&rest x) `(not (< ,@x)))
(defmacro <= (&rest x) `(not (> ,@x)))
(defmacro <> (&rest x) `(not (= ,@x)))
(putd 'printline (getd 'msg))

;
; Error routines
;

(defmacro Error (&rest msg)
 `(progn (msg "Error: " ,@msg)
	 (setq *fatal-error* t)))

(defmacro Warn (&rest msg)
 `(msg "Warning: " ,@msg))

(defmacro Debug (&rest msg)
 `(if *debugging-yaps*
      (msg ,@msg)
      (lispbreak)))

(defun debug-yaps (&optional (flg t))
  (setq *debugging-yaps* flg
	*debugging-flavors* flg))

(defmacro attempt (x) `(catch ,x LBattempt))

(def fail (lambda nil
 (throw '$$FAIL LBattempt)))
