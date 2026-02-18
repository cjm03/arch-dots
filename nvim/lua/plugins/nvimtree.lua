return {
    "nvim-tree/nvim-tree.lua",
    version = "*",
    lazy = false,
    dependencies = { "nvim-tree/nvim-web-devicons" },
    config = function()
        require("nvim-tree").setup({
            view = { width = 24 },
            filters = { dotfiles = true },
            renderer = {
                indent_markers = { enable = true, },
            },
        })
        vim.keymap.set('n', '<leader>ex', ':NvimTreeToggle<CR>')
        vim.keymap.set('n', '<leader>ee', ':NvimTreeFocus<CR>')
    end
}
