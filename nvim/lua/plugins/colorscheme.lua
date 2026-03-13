-- return {
--     "CosecSecCot/cosec-twilight.nvim",
-- }

return {
    "uhs-robert/oasis.nvim",
    lazy = false,
    priority = 1000,
    config = function()
        require("oasis").setup({
            -- style = "abyss",
            style = "starlight",
            styles = {
                italic = false
            },
        })
        vim.cmd("colorscheme oasis")
    end
}

-- return {
--     "rebelot/kanagawa.nvim",
--     lazy = false,
--     priority = 1000,
--     config = function()
--         require("kanagawa").setup({
--             commentStyle = { italic = false },
--             keywordStyle = { italic = false },
--             theme = "dragon",
--             colors = {
--                 theme = {
--                     dragon = {
--                         ui = {
--                             bg = "#000000",
--                             bg_gutter = "none",
--                         },
--                     },
--                 },
--             }
--         })
--         vim.cmd("colorscheme kanagawa-dragon")
--     end
-- }

-- return {
--     "projekt0n/github-nvim-theme",
--     name = "github-theme",
--     lazy = false,
--     priority = 1000,
--     config = function()
--         require("github-theme").setup({
--             palletes = {
--                 github_dark_colorblind = {
--                     comment = '#4FC809'
--                 },
--             },
--             options = {
--                 hide_end_of_buffer = false,
--                 transparent = true,
--                 darken = {
--                     floats = true,
--                     sidebars = { enable = true, },
--                 },
--             },
--         })
--         vim.cmd("colorscheme github_dark_colorblind")
--
--     end
-- }

