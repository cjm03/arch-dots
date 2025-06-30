vim.opt.expandtab = true
vim.opt.tabstop = 4
vim.opt.softtabstop = 4
vim.opt.shiftwidth = 4
vim.opt.clipboard:append("unnamedplus")
vim.opt.swapfile = false

vim.opt.number = true
vim.opt.relativenumber = false
vim.opt.cursorline = true

vim.opt.scrolloff = 20
vim.opt.wrap = false

-- vim.opt.ignorecase = true
-- vim.opt.smartcase = true
vim.opt.showmode = false
vim.opt.cmdheight = 0
vim.opt.background = "dark"
vim.opt.termguicolors = true

vim.o.statuscolumn = [[%!v:lua.StatusColumn()]]
function _G.StatusColumn()
--     local relnum = vim.v.relnum
    local linenum = vim.v.lnum
--     if relnum == 0 then
    return "%#LineNrAbsolute#"..string.format("%d    ", linenum)
--     else
--         return "%#LineNrRelative#"..string.format("  %d   ", relnum)
--     end
end
--
vim.opt.signcolumn = "auto:1"

-- LineNr , LineNrAbove , LineNrBelow




---- Desire unknown ----
vim.opt.mouse = "a"
vim.g.editorconfig = true
vim.opt.hlsearch = true
vim.opt.autoindent = true
vim.opt.smartindent = true
vim.opt.guicursor = ""

---- Potentially undesireable ----
-- vim.opt.backup = false
-- vim.opt.undofile = true
-- vim.opt.incsearch = true
-- vim.opt.inccommand = "split"
-- vim.opt.backspace = {"start", "eol", "indent" }
-- vim.opt.splitright = true
-- vim.opt.splitbelow = true
-- vim.opt.isfname:append("@-@")
-- vim.opt.updatetime = 50
-- vim.opt.colorcolumn = "80"



