(defflavor vanilla () nil :no-vanilla-flavor)

(defmethod (vanilla :print-self) ()
	(msg '|#<| (cxr 0 self) '| | (get-flavor-id self) '|>|))

(defmethod (vanilla :describe) () (describe self))
(defmethod (vanilla :which-operations) ()
	(get (cxr 0 self) 'which-operations))
(defmethod (vanilla :get-handler-for) (message)
	(get-handler-for self message))
