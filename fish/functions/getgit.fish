function getgit
    eval (ssh-agent -c)
    ssh-add ~/.ssh/cjmgit
    ssh -T git@github.com
end
