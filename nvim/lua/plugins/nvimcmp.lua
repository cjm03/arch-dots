return {
    "hrsh7th/nvim-cmp",
    dependencies = {
        "hrsh7th/cmp-buffer",
        "hrsh7th/cmp-path",
        {
            "L3MON4D3/LuaSnip",
            version = "v2.*",
            build = "make install_jsregexp",
        },
        "saadparwaiz1/cmp_luasnip", -- autocompletion
        "rafamadriz/friendly-snippets", -- snippets
        "nvim-treesitter/nvim-treesitter",
        "onsails/lspkind.nvim", -- vs-code pictograms
        "roobert/tailwindcss-colorizer-cmp.nvim",       
    },
    config = function()
        local cmp = require("cmp")
        local has_luasnip, luasnip = pcall(require, 'luasnip')
        local lspkind = require("lspkind")

        local rhs = function(keys)
            return vim.api.nvim_replace_termcodes(keys, true, true, true)
        end

        local lsp_kinds = {
            Class = ' ',
            Color = ' ',
            Constant = ' ',
            Constructor = ' ',
            Enum = ' ',
            EnumMember = ' ',
            Event = ' ',
            Field = ' ',
            File = ' ',
            Folder = ' ',
            Function = ' ',
            Interface = ' ',
            Keyword = ' ',
            Method = ' ',
            Module = ' ',
            Operator = ' ',
            Property = ' ',
            Reference = ' ',
            -- Snippet = ' ',
            Struct = ' ',
            Text = ' ',
            TypeParameter = ' ',
            Unit = ' ',
            Value = ' ',
            Variable = ' ',
        }

        require("luasnip.loaders.from_vscode").lazy_load()

        cmp.setup({
            completion = {
                completeopt = "menuone,noselect,preview",
                -- completeopt = "menu,menuone,noinsert",
            },
            window = {
                completion = cmp.config.window.bordered(),
                documentation = cmp.config.window.bordered(),
            },
            snippet = {
                expand = function(args)
                    luasnip.lsp_expand(args.body)
                end,
            },
            sources = cmp.config.sources({
                -- { name = "copilot" },
                -- { name = "luasnip" },
                { name = "lazydev" },
                { name = "nvim_lsp" },
                { name = "buffer" },
                { name = "path" },
            }),
            mapping = cmp.mapping.preset.insert({
                ["<C-k>"] = cmp.mapping.select_prev_item(),
                ["<C-j>"] = cmp.mapping.select_next_item(),
                ["<C-b>"] = cmp.mapping.scroll_docs(-4),
                ["<C-f>"] = cmp.mapping.scroll_docs(4),
                ["<C-space>"] = cmp.mapping.complete(),
                ["<C-e>"] = cmp.mapping.abort(),
                ["<CR>"] = cmp.mapping.confirm({ select = true }),
            }),
            formatting = {
                format = function(entry, vim_item)
                    vim_item.kind = string.format('%s %s', lsp_kinds[vim_item.kind] or '', vim_item.kind)

                    vim_item.menu = ({
                        buffer = "[Buffer]",
                        nvim_lsp = "[LSP]",
                        -- luasnip = "[LuaSnip]",
                        -- nvim_lua = "[Lua]",
                        latex_symbols = "[LaTeX]",
                    })[entry.source.name]

                    vim_item = lspkind.cmp_format({
                        maxwidth = 25,
                        ellipsis_char = "...",
                    })(entry, vim_item)
                    return vim_item
                end,
            },
        })
        local config = require('cmp.config')
        local toggle_ghost_text = function()
            if vim.api.nvim_get_mode().mode ~= 'i' then
                return
            end

            local cursor_column = vim.fn.col('.')
            local current_line_contents = vim.fn.getline('.')
            local character_after_cursor = current_line_contents:sub(cursor_column, cursor_column)

            local should_enable_ghost_text = character_after_cursor == '' or vim.fn.match(character_after_cursor, [[\k]]) == -1

            local current = config.get().experimental.ghost_text
            if current ~= should_enable_ghost_text then
                config.set_global({
                    experimental = {
                        ghost_text = should_enable_ghost_text,
                    },
                })
            end
        end

        vim.api.nvim_create_autocmd({ 'InsertEnter', 'CursorMovedI' }, {
            callback = toggle_ghost_text,
        })
    end
}
