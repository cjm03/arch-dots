-- return {
--     "metalelf0/black-metal-theme-neovim",
--     lazy = false,
--     priority = 1000,
--     config = function()
--         require("black-metal").setup({
--             -- theme = "immortal",
--             theme = "burzum",
--             -- theme = "marduk",
--             variant = "dark",
--             alt_bg = false,
--             -- cursorline_gutter = true,
--             cursorline_gutter = false,
--             dark_gutter = false,
--             -- plain_float = false,
--             plain_float = true,
--             show_eob = true,
--             term_colors = false,
--             transparent = true,
--             code_style = {
--                 comments = "none",
--                 headings = "none",
--             },
--             diagnostics = {
--                 darker = true,
--                 undercurl = true,
--                 background = false,
--             },
--             plugin = {
--                 lualine = {
--                     bold = true,
--                     plain = false,
--                 },
--             },
--             colors = {},
--             highlights = {},
--         })
--         require("black-metal").load()
--     end
-- }

-- return {
--     "slugbyte/lackluster.nvim",
--     lazy = false,
--     priority = 1000,
--     config = function()
--         require("lackluster").setup({
--             tweak_background = {
--                 normal = 'none',
--                 telescope = 'none',
--                 -- menu = lackluster.color.gray3,
--                 popup = 'default',
--             },
--         })
--         vim.cmd.colorscheme("lackluster-hack")
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
                transparent = true,
                darken = {
                    floats = false,
                    sidebars = { enable = false, },
                },
            },
            palettes = {
                github_dark_default = {
                    -- bg0 = '#000000',
                },
            },
        })
        vim.cmd("colorscheme github_dark_dimmed")
        -- vim.cmd("colorscheme github_dark_default")
    end,
}
