(include declar.l)

(eval-when (compile)
  (load 'dhl//rule))
;;:vi:set lisp ai
;;
;;	Auxiliary Rule file.
;;		Contains sets of functions which the user
;;		can use in rule-domains.
;;

(declare (special ruledomain))
;;
;;	Basic queue control functions.
;;
;;	The first set make the rule domain dequeue a stack.
;;	attributes:
;;  		(getrule poprule)
;;  		(putrule pushrule)
;;  		(gather possiblerules)
;;

(defun poprule (stack)
  stack)

(defun pushrule (stack rule)
  (cond ((null rule)
	 stack)
	((append (list rule) stack))))

(defun possiblerules (goal)
  (*rvalues-only ruledomain 'rule))

;;
;;	The second set make the rule domain dequeue a queue.
;;
;;	attributes:
;;  		(getrule enqueue)
;;	  	(putrule dequeue)
;;		(gather possiblerules)
;;

(defun enqueue (queue rule)
  (cond ((null rule)
	 queue)
	((append queue (list rule)))))

(defun dequeue (queue)
  queue)

;;
;;	end of system provided rule queue functions.
;;

;;
;;	Some simple applyrule functions and macros necessary.
;;
;;	The user picks or writes an applyrule function, and combines
;;		it with his choice of rule queue functions to define
;;		how the system operates.
;;

;;
;;	First is a planner style applyrule where
;;		rules have slots lhs and rhs.
;;	This one uses the match function to match the given goal
;;		to the lhs of a rule, and then bind the
;;		variables matched to the right hand side, which
;;		it tries to prove.
;;	Match is a rule domain with a set of rules defined in
;;		the file dhl//rmatch.l
;;	A faster version of match has been compiled into lisp
;;		into the file dhl//compmatch.l
;;
(defmacro rhs (rule)
  `(*rvalue-only ,rule 'rhs))

(defmacro lhs (rule)
  `(*rvalue-only ,rule 'lhs))

(defun tryrule (rule goal)
  (let ((bindings (match goal (lhs rule) nil)))
       (cond (bindings
	      (let ((result (basicprove (bind-to (rhs rule) bindings))))
		   (cond (result
			  (proved (bind-to (lhs rule) bindings)
				  ruledomain)
			  result)))))))

;;
;;	A second applyrule function,
;;		For this one, rules have slots:
;;			condition, assertion and action,
;;		The condition is evaluated as a lisp expression,
;;		If it is not nil, then list of assertions in
;;		the slot assertions is asserted using the function
;;		set up by the user in the ruledomain slot : assert.
;;		Then the action of the rule is interpreted as a lisp
;;		expression, and its value is returned as the value
;;		of the rule.
;;
;;	Thus the condition is one lisp expression.
;;	The assertions is a list of lisp expressions, each which
;;		are sent to the assert function if it is defined.
;;	And the actions is one lisp expression.
;;
;;
;;	Note: this function is used by the match rule domain.
;;
;;	Also note, the function 'basicapplyrule' doesn't use the
;;		:goal variable so in compiled code, it will work
;;		no matter how many goal-arguments the rule domain has.
;;

(defmacro condition (rule)
  `(*rvalue-only ,rule 'condition))

(defmacro assertions (rule)
  `(eval (*rvalue-only ,rule 'assertion)))

(defmacro action (rule)
  `(*rvalue-only ,rule 'action))

(declare (special :goal))

(defun basicapplyrule (rule :goal)
  (cond ((eval (condition rule))
	 (mapcar '(lambda (x)
			  (succeed x ruledomain))
		 (assertions rule))
	 (eval (action rule)))))

;;
;;	A third applyrule function.
;;		For this one rules have slots:
;;		condition, and action
;;		The condition is of the form (frame slot value).
;;		any of frame, slot or value may be variables.
;;		in this version if frame is a variable ofthe form
;;		?s and s is a real frame, then only its descendents are
;;		considered.
;;		Else All possible solutions are tried.
;;		If there are none, the rule fails.
;;		All solutions are returned and each is tried,
;;		binding the appropriate variable in the action,
;;		Where the action is a list of the form (frame slot value),
;;		and is put into the data base when the condition is satisfied.
;;

(declare (special rulequeue))

(defun production-applyrule (rule goal)
  (let ((possibilities
	 (get-possible-solutions (condition rule))))
       (cond (possibilities
	      (enqueue rule rulequeue)
	      (mapc '(lambda (binding)
			     (mapc '(lambda 
				     (fact)
				     (cond ((eq (car fact) 'eval)
					    (eval fact))
					   ((fput (car fact)
						  (cadr fact)
						  '$value
						  (caddr fact)))))
				   (bind-to (action rule) binding)))
		    possibilities)))))

;;
;;	A fourth applyrule is usualable with sentinels, in that
;;	it lets you run sentinels or rules created as sentinels
;;	in the rule system. (see functions make-rule in rule/sentin.l?)
;;
;;
;;	An applyrule function to run sentinels as rules.
;;
;;	Each value in the (frame,slot) is tried and the first
;;	to succeeds triggers the evaluation of the action
;;	with :frame, :slot, and :value bound to its path.
;;
;;	The return value is nil if none succeeded, and the 
;;	return value of the action otherwise.
;;
;;	Note: the type field is ignored if the frame created
;;	as a sentinel is run as a rule in the rule system.
;;
;;
;;	attributes : (applyrule sentin-applyrule)
;;
;;	note: this one needs no goal arguments.

(defun sentin-applyrule (rule)
  (let ((condition (condition rule))
	(action (action rule)))
       (let ((:frame (car condition))
	     (:slot (cadr condition))
	     (:test (caddr condition)))
	    (do ((:values (fvalues-only :frame :slot)
			  (cdr :values)))
		((null :values))
		(let ((:value (car :values)))
		     (cond ((eval :test)
			    (return (eval action)))))))))
;;
;;	A set of functions which searched the database for 
;;		a match to a given pattern (frame slot value),
;;		and returns all possible bindings to satisfy it,
;;		nil if none.
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
					  (rvalues-only 
					   frame slot))
					 ((assoc values
						 (rvalues
						  frame slot))
					  (list values)))))
		  (cond ((is-var slots)
			 (fslots frame (cdr slots)))
			((list slots)))))
	(cond ((is-var frames)
	       (flatten-tree (ftree (cdr frames) 'instance)))
	      ((list frames))))))

(defun get-one-match (frames frame slots slot values value)
  `(,@(cond ((is-var frames)
	    `((,frames ,frame))))
      ,@(cond ((is-var slots)
	       `((,slots ,slot))))
      ,@(cond ((is-var values)
	       `((,values ,value))))))

(defun flatten-tree (x)
  (cond ((atom x)
	 (list x))
	((mapcan '(lambda (y)
			  (cond ((atom y)
				 (list y))
				((flatten-tree y))))
		 x))))

;;
;;	End of system supplied applyrule functions.
;;
;;

;;
;;	System supplied functions for the user to use
;;		for mark, unmark, and is-marked attributes:
;;		(initialtest notprovedyet)
;;		(initgoal wanttoprove)
;;		(succeed removewantedmark)
;;
(defun notprovedyet (goal)
  (assoc (caddr goal) 
	 (cdr (rlistget (car goal) (cadr goal) '$wanted))))

(defun wanttoprove (goal)
  (rput (car goal) (cadr goal) '$wanted (caddr goal)))

(defun removewantedmark (goal)
  (fremove (car goal) (cadr goal) '$wanted (caddr goal)))

;;
;;	System supplied function for the user for asserting facts,
;;		Facts are of the form (frame slot value)
;;		The fact is added to trigger any sentinel, and
;;		then are removed.
;;

(defun assert-fact (fact)
  (let ((frame (car fact))
	(slot (cadr fact))
	(datum (caddr fact)))
       (cond ((null (assoc datum (*rvalues frame slot '$value)))
	      (rput frame slot '$value datum)
	      (fremove frame slot '$value datum)))))

;;
;;	End of system supplied functions for the user.
;;


;;
;;	some system functions for proved and fail
;;
;;	prove takes a goal, unmarks it with the given
;;		domain unmark function, and then asserts it using the given
;;		domain assert function.
;;
(declare (special ruledomain))

(defun proved (goal)
  ((lambda (frame slot datum)
	   (succeed goal ruledomain)
	   (patom '|True : |)
	   (patom (list frame slot datum))
	   (terpri)
	   (exitcontinue goal ruledomain)
	   t)
   (car goal)
   (cadr goal)
   (caddr goal)))

;;
;;	two simple functions you can use when rules fail:
;;	attributes: (fail basicfail)
;;	or:	    (fail userfailgoal)
;;	
;;	basicfail just prints what goal failed.
;;
;;	userfailgoal creates a sentinel waiting for the
;;		goal to come true and also places a sentinel
;;		on the goal which caused the current goal to
;;		be requested, such that if it ever comes true,
;;		this goal will be asserted also, and the rule
;;		will be reactivated.
;;	
;;

(defun basicfail (goal)
  (patom '|Fail: |)
  (patom goal)
  (terpr))

(declare (special :rulestack :goalstack))

(defun userfailgoal (goal)
  (let ((frame (car goal))
	(slot (cadr goal))
	(datum (caddr goal)))
       (cond (:rulestack
	      (eval `(sentinel if-ever 
			       () 
			       ((',frame ',slot (equal :value ',datum))
				(succeed ',goal ',ruledomain)
				(applyrule ',(car :rulestack) 
					   ',(car :goalstack))))))
	     (t (eval `(sentinel if-ever 
				 () 
				 ((',frame ',slot (equal :value ',datum))
				  (succeed ',goal ',ruledomain)
				  (proved ',goal ',ruledomain))))))
       (patom '|User Fail: |)
       (patom goal)
       (terpr)))

;;
;;	A simple set of trace functions for tracing which
;;	rules are tried.
;;	attributes: (entertrace print-rule-trace)
;;		    (exittrace print-rule-exit-trace)
;;

(defun indent (level)
  (do ((a level (- a 2)))
      ((< a 1))
      (cond ((eq a 1)
	     (patom '/|))
	    ((eq a 2)
	     (patom '/|/ ))
	    (t (patom '/|/ )))))

(defun print-rule-trace args
  ((lambda (rule tracelevel goal)
	   (indent tracelevel) (patom tracelevel)
	   (patom '| Entering |) (patom ruledomain) (patom '|:|)
	   (patom rule) (patom '|: |)
	   (patom goal) 
	   (terpr))
   (arg 1)
   (arg 2)
   (listify (- 2 args))))

(defun print-rule-exit-trace (rule tracelevel result)
  (indent tracelevel) (patom tracelevel)
  (patom '| Exiting |) (patom ruledomain) (patom '|:|)
  (patom rule) (patom '|: |) (patom result)
  (terpr))

;;
;;	End of simple trace functions.
;;

;;
;;	setting default trace programs on a given domain.
;;

(defun trace-rules (rule-domain flag)
  (cond ((null flag)
	 (fremove rule-domain 'entertrace)
	 (fremove rule-domain 'exittrace)
	 'tracing-off)
	(t (fput rule-domain 'entertrace '$value 'print-rule-trace)
	   (fput rule-domain 'exittrace '$value 'print-rule-exit-trace)
	   'tracing-on)))

;;
;;	End of file with functions for the user.
;;
