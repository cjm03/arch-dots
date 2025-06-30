if status is-interactive
end
set fish_greeting
set -x DEBUGINFOD_URLS "https://debuginfod.archlinux.org"
set -Ux XDG_CONFIG_HOME $HOME/.config
set -gx EDITOR nvim
set -gx LANG en_US.UTF-8
fish_config theme choose rosepinemoon
# -- alias -- #
alias cat="bat -p"
alias ls="eza"
alias la="eza --long --header --icons --all"
alias tree="eza --tree"
alias fd="fd -HI"
alias cd="z"

zoxide init fish | source
