# startup .cshrc

set history=20 ignoreeof notify
alias a alias
alias hi history
alias z suspend
alias j jobs
alias mail Mail
alias pd pushd
alias pop popd
alias so source
if ($?prompt) then
	set	prompt="`hostname | sed s/.Berkeley.EDU//`% "
endif
