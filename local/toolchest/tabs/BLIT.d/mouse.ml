;;;
;;; Support for the mouse on the Blit.
;;; Use with the "netty" terminal program.
;;; TPM 8-23-82
;;; CDB 10-17-83
;;;
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
	(delete-to-killbuffer)
	(yank-from-killbuffer)
    )
    (netty-kill
	(set-mark)
	(netty-mouse)
	(delete-to-killbuffer)
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
