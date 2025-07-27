local opts = { noremap = true, silent = true }

vim.g.mapleader = " "
vim.g.maplocalleader = " "

vim.keymap.set("n", "n", "nzzzv")
vim.keymap.set("n", "N", "Nzzzv")

-- Exit insert mode
vim.keymap.set("i", "jk", "<ESC>")

-- leader + w to save
vim.keymap.set("n", "<leader>w", ":w<CR>")

-- tabs
vim.keymap.set('n', '<leader>to', '<cmd>tabnew<CR>')
vim.keymap.set('n', '<leader>tx', '<cmd>tabclose<CR>')
vim.keymap.set('n', '<leader>tn', '<cmd>tabn<CR>')
vim.keymap.set('n', '<leader>tp', '<cmd>tabp<CR>')
vim.keymap.set('n', '<leader>tf', '<cmd>tabnew %<CR>')

-- vim tmux nav
vim.keymap.set('n', '<c-k>', ':wincmd k<CR>')
vim.keymap.set('n', '<c-j>', ':wincmd j<CR>')
vim.keymap.set('n', '<c-h>', ':wincmd h<CR>')
vim.keymap.set('n', '<c-l>', ':wincmd l<CR>')
