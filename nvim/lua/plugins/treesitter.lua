return {
    {
        "nvim-treesitter/nvim-treesitter",
        event = { "BufReadPre", "BufNewFile" },
        build = ":TSUpdate",
        config = function()
            local treesitter = require("nvim-treesitter.configs")

            treesitter.setup({
                indent = { enable = true },
                ensure_installed = {
                    "json",
                    "javascript",
                    "go",
                    "yaml",
                    "html",
                    "css",
                    "python",
                    "http",
                    "markdown",
                    "markdown_inline",
                    "bash",
                    "lua",
                    "vim",
                    "gitignore",
                    "query",
                    "vimdoc",
                    "c",
                    "java",
                    "rust",
                    "asm",
                },
                incremental_selection = { enable = false, },
                additional_vim_regex_highlighting = false,
                highlight = { enable = true, },
            })
        end
    }
}
