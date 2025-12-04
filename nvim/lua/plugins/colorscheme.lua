-- return {
--     "metalelf0/black-metal-theme-neovim",
--     lazy = false,
--     priority = 1000,
--     config = function()
--         require("black-metal").setup({
--             theme = "immortal",
--             variant = "dark",
--             transparent = true,
--             code_style = {
--                 comments = "none",
--                 headings = "none"
--             },
--         })
--         require("black-metal").load()
--     end
-- }

return {
    "projekt0n/github-nvim-theme",
    name = "github-theme",
    lazy = false,
    priority = 1000,
    config = function()
        require("github-theme").setup({
            options = {
                hide_end_of_buffer = false,
                transparent = true,
                darken = {
                    floats = true,
                    sidebars = { enable = true, },
                },
            },
        })
        vim.cmd("colorscheme github_dark_colorblind")

    end
}

-- return {
--     "dgox16/oldworld.nvim",
--     lazy = false,
--     priority = 1000,
--     config = function()
--         require("oldworld").setup({
--             -- variant = "default",
--             -- variant = "oled",
--             variant = "cooler",
--             styles = {
--                 comments = { italic = false },
--                 keywords = { italic = false },
--                 identifiers = { italic = false },
--                 functions = { italic = false },
--                 variables = { italic = false },
--                 booleans = { italic = false },
--             },
--             highlight_overrides = {
--                 EndOfBuffer = { fg = "#444448" },
--                 CursorLineNr = { fg = "#FFFFFF" }
--             },
--         })
--         vim.cmd('colorscheme oldworld')
--     end
-- }
