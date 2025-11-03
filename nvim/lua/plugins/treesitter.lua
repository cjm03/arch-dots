return {
    "nvim-treesitter/nvim-treesitter",
    event = { "BufReadPre", "BufNewFile" },
    build = ":TSUpdate",
    config = function()
        local treesitter = require("nvim-treesitter.configs")

        treesitter.setup({
            indent = { enable = true },
            ensure_installed = {
                "json",
                "javascript", "java",
                "html",
                "css",
                "python",
                "markdown", "markdown_inline",
                "bash", "fish",
                "lua",
                "vim", "vimdoc",
                "gitignore",
                "c",
                "rust",
                "asm"
            },
            incremental_selection = { enable = false },
            additional_vim_regex_highlighting = false,
            highlight = { enable = true },
        })
    end
}
