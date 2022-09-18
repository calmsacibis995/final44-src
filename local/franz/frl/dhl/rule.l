(include declar.l)

(eval-when (compile)
  (load 'dhl//domain))

(declare (macros t))
;;:vi:set lisp ai
;;
;;	Rule Processor and Interpretor.

;;
;;	(rule) => creates a rule frame.
;;
;;	(rule name ako domain 
;;	      attributes)
;;
;;		attributes => (action a)
;;			      (condition b)
;;			      (fail c)
;;
(defun rule macro (x)
  `(progn 'compile
	  (fassert ,(cadr x)
		   (ako ($value (,(caddr x))))
		   ,@(mapcar '(lambda (y)
				      `(,(car y) ($value (,@(cdr y)))))
			     (cddddr x))
		   (domain ($value . ,(cond ((atom (cadddr x))
					     (list (list (cadddr x))))
					    ((cadddr x))))))))

;;
;;	rule domains and knowledge domains have similar syntax.
;;		(see later for rule domains which is slightly different.)
;;
;;	(domain name ako domain (arguments)
;;		attributes)
;;
;;	(rule-domain) => creates a rule domain frame.
;;		rule domains have special attributes used,
;;		some are specific to only rule-domains.
;;
;; (rule-domain name ako domain (arguments) attributes)
;;
;;	attributes in a domain are usually of the form
;;		(slot function-value)
;;		
;;	Some simple system functions are provided for rule
;;		domains in the file dhl//rule2.l
;;		The user is always free to write his own.
;;
;;	necessary attributes for rule domains:
;;		(putrule pushrule)
;;		(getrule poprule)
;;		(applyrule basic-applyrule)
;;
;;	optional attributes for rule domains defined by the system:
;;		(newgoal mark-goal-function)		(formally mark)
;;		(initialtest tell-if-marked-function) 	(formally is-mark)
;;		(succeed unmark-goal-function) 	(formally unmark)
;;							(also formally assert)
;;		(fail basicfail)
;;		(entertrace print-rule-trace)
;;		(exittrace print-exit-rule-trace)
;;
;;	See detailed documentation to find arguments which are passed by
;;		the system to these functions.
;;	Detailed documentation : "dhl//Read-Me".
;;

(defun rule-domain macro (x)
  `(progn 'compile
	  (declare (special . ,(cond ((atom (caddddr x))
				      (list (caddddr x)))
				     ((caddddr x)))))
	  (fassert ,(cadr x)
		   (ako ($value (,(caddr x))))
		   ,@(mapcar '(lambda (y)
				      `(,(car y) ($value (,@(cdr y)))))
			     (cdddddr x))
		   ,@(cond ((cadddr x)
			    `((domain ($value . ,(cond ((atom (cadddr x))
							(list (list (cadddr x))))
						       ((cadddr x)))))))))
	  (fput ',(cadr x) 'arguments '$value ',(caddddr x))
	  (defun ,(cadr x) ,(caddddr x)
		 ,(cond ((and (atom (caddddr x))
			      (caddddr x))
			 `((lambda (,(caddddr x))
				   (changedomain ',(cadr x) 
						 ,(caddddr x)))
			   (listify ,(caddddr x))))
			(t `(changedomain 
			     ',(cadr x)
			     (list . ,(caddddr x))))))))

(putd 'domain (getd 'rule-domain))

;;
;;	variables are ?atomname - used by the simple matcher in
;;		dhl//compmatch.l
;;

(setsyntax '/? 'macro 'makvar)

(defun makvar ()
  (cons '*var* (read)))

(defmacro is-var (x) 
  `(and (dtpr ,x)
	(eq (car ,x) '*var*)))

(putprop '/*var/* '|?| 'printmacrochar)

;;
;; System Functions for handling the rule queue.
;;	The user can specify how the rule queue works by providing
;;	the right functions and attributes to the rule domain,
;;	some functions for simple stacks and queues are provided
;;	in dhl//rule2.l
;;

(declare (special rulequeue rulelevel ruledomain))
(defvar rulequeue nil)
(defvar rulelevel 0)
(defvar ruledomain nil)

(defmacro getrule (r)
  `(funcall (rvalue-only ruledomain 'getrule) ,r))

(defmacro putrule (putrulefunction goal r rq level)
  `(funcall ,putrulefunction ,rq
	    (list ,r ,goal ,level)))

(defmacro rule:getrule (r)
  `(caar ,r))

(defmacro goal:getrule (r)
  `(cadar ,r))

(defmacro level:getrule (r)
  `(caddar ,r))

(defun setuprules (goal level)
  (do ((rules (gather ruledomain goal) 
	      (cdr rules))
       (rq rulequeue)
       (putrule-func (rvalue-only ruledomain 'putrule)))
      ((null rules)
       rq)
      (setq rq (putrule putrule-func goal (car rules) rq level))))

(defmacro entertrace (rule level goal)
  `(let ((entertrace (rvalue-only ruledomain 'entertrace)))
	(cond (entertrace
	       (apply entertrace 
		      (append (list ,rule ,level)
			      ,goal))))))

(defmacro exittrace (rule level result)
  `(let ((exittrace (rvalue-only ruledomain 'exittrace)))
	(cond (exittrace
	       (funcall exittrace ,rule ,level ,result)))))

;;
;;	Basic macros for rule interpretor control structure.
;;

(defmacro initialtest (goal domain)
   `(let ((x (rvalue-only ,domain 'initialtest)))
	 (cond (x (apply x ,goal)))))

(defmacro newgoal (goal domain)
  `(let ((x (rvalue-only ,domain 'newgoal)))
	(cond (x (apply x ,goal)))))

(defmacro succeed (domain result goal)
  `(let ((succeed (rvalue-only ,domain 'succeed)))
	(cond (succeed
	       (apply succeed (append ,goal (list ,result)))))))

(defmacro fail (goal domain)
  `(let ((/$f (rvalue-only ,domain 'fail)))
	(cond (/$f (apply /$f ,goal)))))

;;
;;	:rulestack and :goalstack are two global FRL system variables
;;		which contain the current stack of goals and rules
;;		which are used by the system, any user procedure
;;		or function or rule can access these variables.
;;		the most recent goal and rule are on the top of
;;		the stack.  These varaibles are maintained by
;;		the system prove loop (see basicprove, prove0, and
;;		runrules below).
;;

(declare (special :rulestack :goalstack))
(defvar :rulestack nil)
(defvar :goalstack nil)

(declare (special $rulecount $rulesucceed))
(defvar $rulecount 0)
(defvar $rulesucceed 0)

(defmacro applyrule (r goal level)
  `(let ((result)
	 (:rulestack (cons ,r :rulestack))
	 (:goalstack (cons ,goal :goalstack)))
	(entertrace ,r ,level ,goal)
	(setq $rulecount (1+ $rulecount))
	(cond ((setq result (cond ((rvalue-only ,r 'role-domain)
				   (apply (rvalue-only (rvalue-only
							,r 'role-domain)
						       'applyrule)
					  (cons ,r ,goal)))
				  (t (apply (rvalue-only ruledomain 'applyrule)
					    (cons ,r ,goal)))))
	       (setq $rulesucceed (1+ $rulesucceed))))
	(exittrace ,r ,level result)
	result))

;;
;;	Basic prove function - given a goal - applies the rules
;;		in the current domain to it.
;;

(defun basicprove (goal)
  (prove0 goal 
	  (setuprules goal (1+ rulelevel))
	  (1+ rulelevel)))

;;
;;	bind rulequeue so that it will be reset upon leaving.
;;	rule and goal are set only if called by other rules (nil if
;;	prove was called by the user and are used in setting up the
;;	sentinels if prove fails.)
;;	Eventually this function should be replaced with rules which
;;	can do the appropriate thing.
;;

(defun prove0 (goal rulequeue rulelevel)
  (cond ((initialtest goal ruledomain)
	 nil)
	((newgoal goal ruledomain))	;; this should always returns nil.
					;; unless you want to use it to
					;; return a value and exit.
					;; returning non-nil = success.
					;; without running assert or
					;; succeed functions.
	((*catch rulelevel (runrules)))
	((fail goal ruledomain))))	;; this should return nil.

(declare (special *rule-level))

(defun runrules ()
  (do ((record (getrule rulequeue)
	       (getrule rulequeue))
       (*rule-level)
       (lastgoal) (result) (resultlist))
      ((null record) 
       (or (succeed ruledomain resultlist lastgoal)
	   resultlist))
      (setq rulequeue (cdr record))
      (setq lastgoal (goal:getrule record))
      (setq *rule-level (level:getrule record))
      (cond ((setq result (applyrule (rule:getrule record)
				     lastgoal
				     *rule-level))
	     (cond ((fvalue-only ruledomain 'succeedcontinue)
		    (setq resultlist (append resultlist (list result))))
		   (t (let ((r (succeed ruledomain
					result
					(goal:getrule record))))
			   (cond (r (*throw *rule-level r))
				 ((*throw *rule-level result))))))))))

;;
;;	ruledomain-throw : throws one out of the current domain with
;;		the given result.  Overrides all succeed functions, and
;;		continue-succeed flags.  If the return value is
;;		nil, then the goal of the rule-domain failed, and
;;		the appropriate fail function will be executed.
;;
(defun ruledomain-throw (result)
  (*throw *rule-level result))

;;
;;	changedomain - run prove in a new domain on the given goal.
;;
;;	note about rulequeue - default setting, is a new rulequeue is
;;	created for each new level, except in the case when a ruledomain
;;	calls itself, when the old rulequeue is used.
;;	Using the scope slot of a ruledomain can override these defaults.
;;
;;	scope -- close : new rulequeue for a domain when called by itself.
;;		 open : use previous rulequeue when called by other domains.
;;

(defun changedomain (newruledomain goal)
  (cond ((eq newruledomain ruledomain)
	 (cond ((eq 'close (rvalue-only ruledomain 'scope))
		(let ((rulequeue nil))
		     (basicprove goal)))
	       ((basicprove goal))))
	(t (let ((ruledomain newruledomain))
		(cond ((null (eq 'open (rvalue-only ruledomain 'scope)))
		       (let ((rulequeue nil))
			    (basicprove goal)))
		      ((basicprove goal)))))))

;;
;;	newsym - a nice version of gensym.  for creating
;;		new frame names.
;;

(defmacro newsym (word)
  `(do ((n (1+ (cond ((get ,word 'newsym-index))
		     (0)))
	   (1+ n)))
       ((or (null (getd 'frame/?))
	    (null (frame/? (concat ,word n))))
	(putprop ,word n 'newsym-index)
	(concat ,word n))))

;;
;;	newframe -- create a new frame of a given type.
;;

(defmacro newframe (type)
  `(eval (list 'fassert 
	       (newsym ,type)
	       (list 'ako (list '$value (list ,type))))))
