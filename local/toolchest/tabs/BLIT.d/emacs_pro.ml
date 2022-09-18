;;;
;;; Wild Card Filenames for Visit File
;;;
(defun
    (Wild_Card_Filename
	(temp-use-buffer "*Wild_Card*")
	(beginning-of-file)
	(set-mark)
	(end-of-file)
	(delete-to-killbuffer)
	(insert-string "exec ls -d ")
	(set-mark)
	(insert-string (get-tty-string "Filename: "))
	(end-of-file)
	(newline)
	(beginning-of-file)
	(set-mark)
	(end-of-file)
	(filter-region "sh")
	(beginning-of-file)
	(set-mark)
	(end-of-line)
    )
    (Wild_Visit_File Name
	(Wild_Card_Filename)
	(setq Name (region-to-string))
	(visit-file Name)
    )
)
(bind-to-key "Wild_Visit_File" "\^X\^F")

;;;
;;;	Concept108
;;;
(if (= (getenv "TERM") "blewett")
	(progn
		(defun
		    (Concept100-pad c
			(setq c (get-tty-character))
			(if
			   (= c '>') (backward-character)
			   (= c '=') (forward-character)
			   (= c ';') (previous-line)
			   (= c '<') (next-line)
			   (= c '.') (previous-page)
			   (= c '-') (next-page)
			   (= c '[') (progn
					   (next-line) (next-line) (next-line))
			   (= c '?') (beginning-of-window)
			   (= c '`') (end-of-window)
			   (= c ']') (progn
					   (set-mark) (message "Mark Set."))
			   (= c '_') (exchange-dot-and-mark)
			   (= c ':') (backward-word)
			   (= c '{') (forward-word)
			   (= c '\\') (progn
					    (previous-line)
					    (previous-line)
					    (previous-line)
				      )
			   (= c '+') (scroll-one-line-up)
			   (= c ',') (scroll-one-line-down)
			   (message "Concept Cursor Pad Key Undefined.")
			)
		    )
		)
		(bind-to-key "Concept100-pad" 034)
	)
)

;;;
;;; Blit running etty
;;;
;;; (load "mouse.ml")
;;;
(if (= (getenv "TERM") "netty")
	(progn
		(defun
		    (netty-mouse button x y olddot
			   (setq button (get-tty-character))
			   (setq x (- (get-tty-character) 31))
			   (setq y (- (get-tty-character) 31))
			   (if (= button '1')
			       (move-dot-to-x-y x y)
			   )
		    )
		)
		(bind-to-key "netty-mouse" "\030\037") ; Control-X Control-_
		
		(defun
		    (netty-func-keys c
			(setq c (get-tty-character))
			(if
			   (= c 'A') (prefix-argument-loop
					 (previous-line))
			   (= c 'B') (prefix-argument-loop
					 (next-line))
			   (= c 'C') (prefix-argument-loop
					 (backward-character))
			   (= c 'D') (prefix-argument-loop
					 (forward-character))
			   (= c 'E') (prefix-argument-loop
					 (backward-word))
			   (= c 'F') (prefix-argument-loop
					 (progn (scroll-one-line-down)
						(beginning-of-window)
						(beginning-of-line)))
			   (= c 'G') (prefix-argument-loop
					 (progn (scroll-one-line-up)
						(end-of-window)
						(beginning-of-line)))
			   (= c 'H') (prefix-argument-loop
					 (forward-word))
			   (message "Blit Cursor Pad Key Undefined.")
			)
		    )
		)
		(bind-to-key "netty-func-keys" "\030O") ; Control-X O - ohh
		
		(defun
		    (netty-mark
			(set-mark)
			(netty-mouse)
		    )
		    (netty-copy
			(set-mark)
			(netty-mouse)
			(copy-region)
		    )
		    (netty-kill
			(set-mark)
			(netty-mouse)
			(kill-region)
		    )
		    (netty-change-mouse-action
			(if
			   (= prefix-argument 2)
			   (progn
				 (bind-to-key "netty-copy" "\030\035")
				 (message "Mouse button two picks up the region")
			   )
			   (= prefix-argument 3)
			   (progn
				 (bind-to-key "netty-kill" "\030\035")
				 (message "Mouse button two kills the region")
			   )
			   (progn
				 (bind-to-key "netty-mark" "\030\035")
				 (message "Mouse button two marks the region")
			   )
			)
		    )
		)
		
		(bind-to-key "netty-change-mouse-action" "\030\066")	; ^X 6
		(bind-to-key "netty-mark" "\030\035")			; ^X ^]
		
		(bind-to-key "set-mark" "\e ")				; ESC-<SPACE>
		(bind-to-key "scroll-one-line-up" "\e\016")		; ESC-^N
		(bind-to-key "scroll-one-line-down" "\e\020")		; ESC-^P
	)
)
;;;
;;; The good delete and recover stuff
;;;
;;;	(load "killring.ml")
;;;
(defun
    (kill-region
	(if (= (previous-command) 11)
	    (progn
		(c-append-region)
		(erase-region))
	    (progn
		(next-killbuffer)
		(delete-region-to-buffer killbuffer)))
	(setq this-command 11))
    (copy-region
	(if (= (previous-command) 11)
	    (c-append-region)
	    (progn
		(next-killbuffer)
		(copy-region-to-buffer killbuffer)))
	(setq this-command 11))
    (c-append-region
	(if (>= (dot) (mark))
	    (append-region-to-buffer killbuffer)
	    (progn
		(exchange-dot-and-mark)
		(yank-buffer killbuffer)
		(copy-region-to-buffer killbuffer))))
    (append-next-kill
	(setq this-command 11))
    (unkill				; leaves region around restored text
	(set-mark)
	(yank-buffer killbuffer))
    (unkill-pop
	(delete-region-to-buffer killbuffer)
	(previous-killbuffer)
	(set-mark)
	(yank-buffer killbuffer))
    (set-up-killbuffer
	(setq killbuffer (concat "KB-" ringpos)))
    (next-killbuffer
	(setq ringpos (+ ringpos 1))
	(if (> ringpos nrings)
	    (setq ringpos (- ringpos nrings)))
	(set-up-killbuffer))
    (previous-killbuffer
	(setq ringpos (- ringpos 1))
	(if (< ringpos 1)
	    (setq ringpos (+ ringpos nrings)))
	(set-up-killbuffer))
    (forward-lines
	(if (& &kill-lines-magic (bolp))
	    (progn			; beginning of line--kill whole lines
		(beginning-of-line)	; flush target column
		(provide-prefix-argument prefix-argument (next-line)))
	    (if (eolp)
		(forward-character)	; end of line--kill crlf
	        (end-of-line))))	; else--kill to end of line
    (kill-lines		; to append to killbuffer, set dot before killing
	(set-mark)
	(provide-prefix-argument prefix-argument (forward-lines))
	(kill-region))
    (copy-lines
	(set-mark)
	(provide-prefix-argument prefix-argument (forward-lines))
	(copy-region))
    (kill-word
	(set-mark)
	(provide-prefix-argument prefix-argument (forward-word))
	(kill-region))
    (backward-kill-word
	(set-mark)
	(provide-prefix-argument prefix-argument (backward-word))
	(kill-region))
    )
(declare-global nrings)
(if (= nrings 0) (setq-default nrings 8))
(declare-global ringpos)
(declare-global killbuffer)
(declare-global &kill-lines-magic)
(setq-default &kill-lines-magic 0)

(save-excursion
    (setq ringpos (+ nrings 1))
    (while (> ringpos 1)
	(setq ringpos (- ringpos 1))
	(set-up-killbuffer)
	(switch-to-buffer killbuffer)
	(setq needs-checkpointing 0)))

(bind-to-key "kill-region" "\^W")
(bind-to-key "copy-region" "\ew")
(bind-to-key "kill-lines" "\^K")
(bind-to-key "copy-lines" "\ek")
(bind-to-key "kill-word" "\ed")
(bind-to-key "backward-kill-word" "\eh")
(bind-to-key "backward-kill-word" "\e\177")	 	; esc rubout
(bind-to-key "append-next-kill" "\ea")
(bind-to-key "unkill" "\^Y")
(bind-to-key "unkill-pop" "\ey")
;;;
;;; end load killrings.ml
;;;

;;;
;;; BTL EMACS compatability
;;;
(bind-to-key "set-mark" "\e ")		; ESC-<SPACE>
(bind-to-key "copy-region" "\ep")	; Copy without deleting

(autoload "new-undo" "undo.ml")
(autoload "goto-line" "goto.ml")
(autoload "spell" "spell.ml")
(autoload "incremental-search" "incr-search.ml")
(autoload "reverse-incremental-search" "incr-search.ml")
(autoload "dired" "dired.ml")
(autoload "electric-c-mode" "electric-c.ml")
(autoload "electric-lisp-mode" "electric-lisp")
(autoload "electric-mlisp-mode" "electric-lisp")
(autoload "rmail" "rmail.ml")
(setq right-margin 72)
(setq tab-size 8)
(setq checkpoint-frequency -1)
(setq default-mode-line-format " CMU EMACS: %20b %M (%m)    %[%3p%] %*")
(setq quick-redisplay 1)
(setq track-eol-on-^N-^P 0)
(setq ctlchar-with-^ 1)
(setq help-on-command-completion-error 1)
(setq wrap-long-lines 1)
(setq default-case-fold-search 1)
(setq backup-by-copying 0)
(setq unlink-checkpoint-files 1)
(bind-to-key "new-undo" "\^X\^U")
(bind-to-key "re-search-forward" "\e\^S")
(bind-to-key "re-search-reverse" "\e\^R")
(bind-to-key "delete-white-space" "\ek")
(bind-to-key "case-word-capitalize" "\ec")
(bind-to-key "incremental-search" '^S')
(bind-to-key "reverse-incremental-search" '^R')
(bind-to-key "rmail" "\^Xr")
(bind-to-key "smail" "\^Xm")
(bind-to-key "define-global-abbrev" "\^X\^A")
(auto-execute "electric-c-mode" "*.c")
(auto-execute "electric-c-mode" "*.h")
(auto-execute "text-mode" "*.mm")
(auto-execute "electric-mlisp-mode" "*.ml")
(auto-execute "electric-lisp-mode" "*.l")
(auto-execute "electric-mlisp-mode" "*.emacs_pro")
