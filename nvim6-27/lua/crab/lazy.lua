vim.g.loaded_netrw = 1
vim.g.loaded_netrwPlugin = 1

local lazypath = vim.fn.stdpath("data") .. "/lazy/lazy.nvim"
if not vim.loop.fs_stat(lazypath) then
    vim.fn.system({
        "git",
        "clone",
        "--filter=blob:none",
        "https://github.com/folke/lazy.nvim.git",
        "--branch=stable",
        lazypath
    })
end
vim.opt.rtp:prepend(lazypath)

require("lazy").setup(
    {
        { import = "crab.plugins" },
        { import = "crab.plugins.lsp" },
    },
    {
        checker = {
            enabled = true,
            notify = false,
        },
        change_detection = {
            notify = false,
        },
    }
)
vim.api.nvim_set_hl(0, "CursorLineNr", { fg = "#ddeecc", bg = "#000000" })

-- vim.api.nvim_set_hl(0, "LineNrAbsolute", { fg = "#ddeecc", bg = "#000000", bold = true })
-- vim.api.nvim_set_hl(0, "LineNrRelative", { fg = "#c1c1c1", bg = "#000000" })
