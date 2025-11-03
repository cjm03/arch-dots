return {
    "neovim/nvim-lspconfig",
    event = { "BufReadPre", "BufNewFile" },
    dependencies = { "hrsh7th/cmp-nvim-lsp" },
    config = function()
        vim.api.nvim_create_autocmd("LspAttach", {
            group = vim.api.nvim_create_augroup("MyLspGroup", {}),
            callback = function(ev)
                local opts = { buffer = ev.buf, silent = true }
                opts.desc = "Docs for Under Cursor"
                vim.keymap.set("n", "K", vim.lsp.buf.hover, opts)
                opts.desc = "Definition"
                vim.keymap.set("n", "<leader>gd", vim.lsp.buf.definition, opts)
                opts.desc = "Open Diagnostic Float"
                vim.keymap.set("n", "<leader>go", vim.diagnostic.open_float, opts)
                opts.desc = "Code Actions"
                vim.keymap.set("n", "<leader>ca", vim.lsp.buf.code_action, opts)
            end
        })

        local signs = {
            [vim.diagnostic.severity.ERROR] = "",
            [vim.diagnostic.severity.WARN]  = "",
            [vim.diagnostic.severity.HINT]  = "󰠠",
            [vim.diagnostic.severity.INFO]  = "",
        }

        vim.diagnostic.config({
            signs = { text = signs },
            virtual_text = true,
            underline = true,
            update_in_insert = false,
        })

        -- vim.lsp.set_log_level("debug")
        local cmp_nvim_lsp = require("cmp_nvim_lsp")
        local capabilities = cmp_nvim_lsp.default_capabilities()
        local lsps = {
            {
                "pyright", { capabilities = capabilities }
            },

            {
                "html",
                {
                    filetypes = { "html", "php", "css", "javascript", "typescript", "jsx", "tsx" },
                    capabilities = capabilities,
                }
            },

            -- {
            --     "asm_lsp", { capabilities = capabilities }
            -- },

            {
                "lua_ls",
                {
                    cmd = { "lua-language-server" },
                    filetypes = { "lua" },
                    root_markers = { ".luarc.json", ".luarc.jsonc", ".stylua.toml" },
                    capabilities = capabilities,
                }
            },

            -- {
            --     "ast_grep", { capabilities = capabilities }
            -- },
            --
            -- {
            --     "bashls", { capabilities = capabilities }
            -- },

            {
                "clangd",
                {
                    cmd = { "clangd", "--background-index" }, -- "--function-arg-placeholders=0", "--clang-tidy" }, -- "--header-insertion=iwyu", "--completion-style=detailed", "--fallback-style=llvm", "--fallback-style=llvm" },
                    init_options = { usePlaceholders = true, completeUnimported = true, clangdFileStatus = true },
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
