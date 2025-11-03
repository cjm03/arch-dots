if status is-interactive
end
set fish_greeting

set -x DEBUGINFOD_URLS "https://debuginfod.archlinux.org"
set -Ux XDG_CONFIG_HOME $HOME/.config
set -gx EDITOR nvim
set -gx LANG en_US.UTF-8

# -- alias -- #
alias ls="eza"
alias la="eza --long --header --icons --all"
alias tree="eza --tree"
alias cd="z"
alias template="~/crabby/template/template"

zoxide init fish | source
