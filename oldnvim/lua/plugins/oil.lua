return {
    "stevearc/oil.nvim",
    dependencies = { "nvim-mini/mini.icons" },
    config = function()
        require("oil").setup({
            default_file_explorer = true,
            columns = { "icon", "permissions", "size", "mtime" },
            keymaps = {
                ["<C-h>"] = false,
                ["<C-c>"] = false,
                ["<M-h>"] = "actions.select_split",
                ["q"] = "actions.close",
            },
            delete_to_trash = true,
            view_options = { show_hidden = true, },
            skip_confirm_for_simple_edits = true,
        })
        vim.keymap.set("n", "-", "<CMD>Oil<CR>", { desc = "oil nonfloat currentdir"})
        vim.keymap.set("n", "<leader>-", "<CMD>Oil /home/crab/<CR>", { desc = "oil nonfloat homedir"})
        vim.api.nvim_create_autocmd("FileType", {
            pattern = "oil",
            callback = function()
                vim.opt_local.cursorline = false
            end,
        })
    end
}
