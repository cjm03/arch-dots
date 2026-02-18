---@module "lazy"
---@type LazySpec
return {
    "nvim-treesitter/nvim-treesitter",
    dependencies = { 
        {
            "nvim-treesitter/nvim-treesitter-context",
            opts = { max_lines = 4, multiline_threshold = 2, },
        },
    },
    lazy = false,
    branch = 'main',
    -- event = { "BufReadPre", "BufNewFile" },
    build = ":TSUpdate",
    config = function()
        local treesitter = require("nvim-treesitter")

        treesitter.install({
            -- indent = { enable = true },
            -- ensure_installed = {
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
        }, {
            max_jobs = 8,
        })

        local group = vim.api.nvim_create_augroup('TreesitterSetup', { clear = true })

        vim.api.nvim_create_autocmd('FileType', {
            group = group,
            desc = 'Enable treesitter highlighting and indentation',
            callback = function(event)
                local ft = event.match

                local ignore = { oil = true, cmp_menu = true, }

                if ignore[ft] then
                    return
                end

                local lang = vim.treesitter.language.get_lang(event.match) or event.match
                local buf = event.buf

                pcall(vim.treesitter.start, buf, lang)

                vim.bo[buf].indentexpr = "v:lua.require'nvim-treesitter'.indentexpr()"

                treesitter.install({ lang })
            end,
        })
            -- incremental_selection = { enable = false },
            -- additional_vim_regex_highlighting = false,
            -- highlight = { enable = true },
    end,
}
