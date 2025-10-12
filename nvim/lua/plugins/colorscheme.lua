return {
    "Shatur/neovim-ayu",
    lazy = false,
    priority = 1000,
    config = function()
        require('ayu').setup({
            mirage = false,
            terminal = true,
            overrides = {
                Comment = { italic = false },
                Normal = { bg = "None" },
                NormalFloat = { bg = "none" },
                ColorColumn = { bg = "None" },
                SignColumn = { bg = "None" },
                Folded = { bg = "None" },
                FoldColumn = { bg = "None" },
                CursorLine = { bg = "None" },
                CursorColumn = { bg = "None" },
                VertSplit = { bg = "None" },
            },
        })
        vim.cmd("colorscheme ayu")
    end
}

-- return {
--     "projekt0n/github-nvim-theme",
--     name = "github-theme",
--     lazy = false,
--     priority = 1000,
--     config = function()
--         require("github-theme").setup({
--             options = {
--                 transparent = true,
--                 darken = {
--                     floats = true,
--                     sidebars = { enable = true, },
--                     -- floats = false,
--                     -- sidebars = { enable = false, },
--                 },
--             },
--         })
--         vim.cmd("colorscheme github_dark_dimmed")
--     end
-- }
