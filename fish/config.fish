if status is-interactive
end
set fish_greeting
set -Ux CUDA_PATH /opt/cuda
set -Ux NVCC_CCBIN /usr/bin/g++-14
set -Ux LD_LIBRARY_PATH /opt/gtk/lib
set -Ux GDK_BACKEND x11
fish_add_path /opt/cuda/bin
fish_add_path /opt/cuda/nsight_compute
fish_add_path /opt/cuda/nsight_systems/bin
fish_add_path /opt/gtk/bin
set -x DEBUGINFOD_URLS "https://debuginfod.archlinux.org"
set -Ux XDG_CONFIG_HOME $HOME/.config
set -gx EDITOR nvim
set -gx LANG en_US.UTF-8
# fish_config theme choose rosepinemoon
# -- alias -- #
alias cat="bat -p"
alias ls="eza"
alias la="eza --long --header --icons --all"
alias tree="eza --tree"
alias fd="fd -HI"
alias cd="z"
alias template="~/crabby/ctemplate/template"
alias authgit="~/authgit.fish"
alias mvin="/home/crab/Downloads/nvim-linux-x86_64/bin/nvim"

zoxide init fish | source
