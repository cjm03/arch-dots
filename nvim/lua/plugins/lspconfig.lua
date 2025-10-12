return {
    "neovim/nvim-lspconfig",
    event = { "BufReadPre", "BufNewFile" },
    dependencies = {
        "hrsh7th/cmp-nvim-lsp",
        -- { "antosha417/nvim-lsp-file-operations", config = true },
    },
    config = function()
        vim.api.nvim_create_autocmd("LspAttach", {
            group = vim.api.nvim_create_augroup("UserLspConfig", {}),
            callback = function(ev)
                local opts = { buffer = ev.buf, silent = true }
                opts.desc = "docs for under cursor"
                vim.keymap.set("n", "K", vim.lsp.buf.hover, opts)
                opts.desc = "definition"
                vim.keymap.set("n", "<leader>gd", vim.lsp.buf.definition, opts)
                opts.desc = "references"
                vim.keymap.set("n", "<leader>gr", vim.lsp.buf.references, opts)
                opts.desc = "codeaction"
                vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action, opts)
                opts.desc = "open diagnostic float"
                vim.keymap.set("n", "<leader>go", vim.diagnostic.open_float, opts)
            end,
        })

        local signs = {
            [vim.diagnostic.severity.ERROR] = "",
            [vim.diagnostic.severity.WARN]  = "",
            [vim.diagnostic.severity.HINT]  = "󰠠",
            [vim.diagnostic.severity.INFO]  = "",
        }

        -- Set the diagnostic config with all icons
        vim.diagnostic.config({
            signs = {
                text = signs -- Enable signs in the gutter
            },
            virtual_text = true,  -- Specify Enable virtual text for diagnostics
            underline = true,     -- Specify Underline diagnostics
            update_in_insert = false,  -- Keep diagnostics active in insert mode
        })

        local cmp_nvim_lsp = require("cmp_nvim_lsp")
        local capabilities = cmp_nvim_lsp.default_capabilities()
        local lsps = {
            { 
                'pyright', { capabilities = capabilities }
            },

            { 
                'html',
                {
                    filetypes = { "html", "php", "css", "javascript", "typescript", "jsx", "tsx" },
                    capabilities = capabilities,
                }
            },

            {
                'asm_lsp', { capabilities = capabilities }
            },

            {
                'lua_ls', 
                {
                    cmd = { 'lua-language-server' },
                    filetypes = { 'lua' },
                    root_markers = {'.luarc.json', '.luarc.jsonc', '.stylua.toml'},
                    capabilities = capabilities,
                }
            },
            {
                'ts_ls', { capabilities = capabilities }
            },
            {
                'ast_grep', { capabilities = capabilities }
            },

            { 
                'bashls', { capabilities = capabilities }
            },
            {
                'clangd',
                {
                    cmd = {
                        "clangd",
                        "--compile-commands-dir=build",
                        "--background-index",
                        "--clang-tidy",
                        "--log=verbose",
                        "--header-insertion=iwyu",
                        "--completion-style=detailed",
                        "--function-arg-placeholders",
                        "--fallback-style=llvm"
                    },
                    init_options = {
                        -- fallbackFlags = { '-std=c99' },
                        usePlaceholders = true,
                        completeUnimported = true,
                        clangdFileStatus = true,
                    },
                    filetypes = { "c", "h", "cpp" },
                    capabilities = capabilities,
                }
            },
        }

        for _, lsp in pairs(lsps) do
            local name, conf = lsp[1], lsp[2]
            vim.lsp.enable(name)
            if conf then
                vim.lsp.config(name, conf)
            end
        end

    end,
}
