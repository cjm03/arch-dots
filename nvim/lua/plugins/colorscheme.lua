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

        local custom_auto = require'lualine.themes.auto'
        custom_auto.normal.a.gui = 'bold'
        custom_auto.insert.a.bg = '#ea8c2e'
        custom_auto.insert.b.fg = '#ea8c2e'
        custom_auto.insert.a.gui = 'bold'
        custom_auto.visual.a.gui = 'bold'
        custom_auto.command.a.gui = 'bold'

        require("lualine").setup({
            options = {
                theme = custom_auto,
                global_status = false,
                section_separators = "",
                component_separators = "",
            },
        })
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

-- return {
--     "projekt0n/caret.nvim",
--     lazy = false,
--     priority = 1000,
--     config = function()
--         require("caret").setup({
--             options = {
--                 transparent = true,
--                 styles = {
--                     italics = false,
--                     bold = true
--                 },
--             },
--         })
--         vim.cmd('colorscheme caret')  -- jellybeans-muted, jellybeans-mono
--     end
-- }

