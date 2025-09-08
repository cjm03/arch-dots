return {
    "neovim/nvim-lspconfig",
    event = { "BufReadPre", "BufNewFile" },
    dependencies = {
        "hrsh7th/cmp-nvim-lsp",
        { "antosha417/nvim-lsp-file-operations", config = true },
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

        local lspconfig = require("lspconfig")
        local cmp_nvim_lsp = require("cmp_nvim_lsp")
        local capabilities = cmp_nvim_lsp.default_capabilities()

        lspconfig.lua_ls.setup({
            capabilities = capabilities,
            settings = {
                Lua = {
                    diagnostics = {
                        globals = { "vim" },
                    },
                    completion = {
                        callSnippet = "Replace",
                    },
                    workspace = {
                        library = {
                            [vim.fn.expand("$VIMRUNTIME/lua")] = true,
                            [vim.fn.stdpath("config") .. "/lua"] = true,
                        },
                    },
                },
            },
        })

        lspconfig.pylsp.setup({
            capabilities = capabilities,
        })

        lspconfig.html.setup({
            capabilities = capabilities,
            filetypes = { "html", "php", "css", "javascript", "typescript", "jsx", "tsx" },
        })

        -- lspconfig.asm_lsp.setup({
        --     capabilities = capabilities,
        -- })

        lspconfig.ast_grep.setup({
            capabilities = capabilities,
        })

        lspconfig.bashls.setup({
            capabilities = capabilities,
        })

        lspconfig.intelephense.setup({
            capabilities = capabilities,
        })

        require("lspconfig")["tinymist"].setup({
            capabilities = capabilities,
            settings = {
                formatterMode = "typstyle",
                exportPdf = "never",
                semanticTokens = "enable"
            },
            on_attach = function(client, bufnr)
                vim.keymap.set("n", "<leader>Pp", function()
                    client:exec_cmd({
                        title = "pin",
                        command = "tinymist.pinMain",
                        arguments = { vim.api.nvim_buf_get_name(0) },
                    }, { bufnr = bufnr })
                end, { desc = "tinymist pin", noremap = true })

                vim.keymap.set("n", "<leader>Px", function()
                    client:exec_cmd({
                        title = "unpin",
                        command = "tinymist.pinMain",
                        arguments = { vim.v.null },
                    }, { bufnr = bufnr })
                end, { desc = "tinymist unpin", noremap = true })
            end,
        })

        require("lspconfig").clangd.setup({
            cmd = {
                "clangd",
                "--compile-commands-dir=build",
                "--background-index",
                "--clang-tidy",
                "--log=verbose",
                "--header-insertion=iwyu",
                "--completion-style=detailed",
                "--function-arg-placeholders",
                "--fallback-style=llvm",
            },
            init_options = {
                usePlaceholders = true,
                completeUnimported = true,
                clangdFileStatus = true,
            },
            filetypes = { "c", "h", "cpp" },
            capabilities = capabilities,
        })
    end,
}
