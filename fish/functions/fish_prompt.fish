function fish_prompt

    set -l colorcwd $fish_color_cwd
    set -l color '#e3b341'
    set -l symcolor '#26cd4d'
    set -l gitcolor '#4f4f52'

    set -l customuser '\033[1;97mcrab\033[0m'
    set -l customhost '\033[1mvault-1\033[0m'

    set -g __fish_git_prompt_show_informative_status true
    set -g __fish_git_prompt_hide_untrackedfiles true
    set -g __fish_git_prompt_char_stateseparator ""
    set -g __fish_git_prompt_showupstream "informative"
    set -g __fish_git_prompt_color_branch blue
    set -g __fish_git_prompt_char_cleanstate '✔'
    set -g __fish_git_prompt_char_dirtystate "*"
    set -g __fish_git_prompt_char_conflictedstate "✖"
    set -g __fish_git_prompt_char_untrackedfiles "…"
    set -g __fish_git_prompt_char_stagedstate "+"
    set -g __fish_git_prompt_char_upstream_ahead "↑"
    set -g __fish_git_prompt_char_upstream_behind "↓"
    set -g __fish_git_prompt_char_upstream_diverged "↓↑"
    set -g __fish_git_prompt_char_upstream_equal "~"
    set -g __fish_git_prompt_color_prefix $gitcolor
    set -g __fish_git_prompt_color_suffix $gitcolor
    set -g __fish_git_prompt_color_cleanstate blue
    set -g __fish_git_prompt_color_dirtystate red
    set -g __fish_git_prompt_color_invalidstate $gitcolor
    set -g __fish_git_prompt_color_stagedstate magenta
    set -g __fish_git_prompt_color_untrackedfiles $fish_color_normal
    set -g __fish_git_prompt_color_bare white
    set -g __fish_git_prompt_color_merging brcyan

    set -l st '['
    set -l end ']'
    set -l symbol ' 󰘧 '
    set -l customsymbol ' \033[1m󰘧\033[0m '

    if fish_is_root_user
        set symbol ' # '
        set -q fish_color_cwd_root
        and set color $fish_color_cwd_root
    end

    set_color $gitcolor
    echo -n $st

    set_color normal
    echo -ne $customuser
    set_color $gitcolor
    echo -n @

    set_color $color
    echo -ne $customhost

    set_color $colorcwd
    echo -n (prompt_pwd)
    # echo -n '~'

    set_color $gitcolor
    echo -n $end

    set_color normal
    printf '%s' (fish_git_prompt)
    # echo -n $(fish_git_prompt)

    # set_color normal
    set_color $symcolor
    # echo -n $symbol
    echo -ne $customsymbol
    set_color normal
end
