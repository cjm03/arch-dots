return {
    "nvim-lualine/lualine.nvim",
    dependencies = { "nvim-tree/nvim-web-devicons" },
    config = function()

-- github ---------------------------------------------------------
        -- local custom_auto = require'lualine.themes.auto'
        -- custom_auto.normal.a.bg = '#0366d6'
        -- custom_auto.normal.a.gui = 'bold'
        -- custom_auto.insert.a.bg = '#ea8c2e'
        -- custom_auto.insert.a.gui = 'bold'
        -- custom_auto.insert.b.fg = '#ea8c2e'
        -- custom_auto.insert.c.fg = '#ea8c2e'
        -- custom_auto.visual.a.gui = 'bold'
        -- custom_auto.command.a.gui = 'bold'
-- kanagawa --------------------------------------------------------
        -- local custom_k = require'lualine.themes.kanagawa'
        -- custom_k.normal.a.gui = 'bold'
        -- custom_k.normal.c.bg = '#000000'
        -- custom_k.insert.a.gui = 'bold'
        -- custom_k.command.a.gui = 'bold'
        -- custom_k.visual.a.gui = 'bold'
-- oasis ---------------------------------------------------------
        local Utils = require("oasis.utils")
        local c = Utils.load_and_extract_palette("oasis.color_palettes.oasis_starlight")
        local custom_oasis = require'lualine.themes.auto'
        custom_oasis.normal.a.bg = c.syntax.statement
        custom_oasis.normal.a.fg = c.bg.core
        custom_oasis.normal.b.bg = c.bg.surface
        custom_oasis.normal.b.fg = c.syntax.statement
        custom_oasis.normal.c.bg = c.bg.core
        custom_oasis.normal.c.fg = c.syntax.statement

        custom_oasis.insert.a.bg = c.syntax.string
        custom_oasis.insert.a.fg = c.bg.core
        custom_oasis.insert.b.bg = c.bg.surface
        custom_oasis.insert.b.fg = c.syntax.string
        custom_oasis.insert.c.bg = c.bg.core
        custom_oasis.insert.c.fg = c.syntax.string

        custom_oasis.command.a.bg = c.syntax.parameter
        custom_oasis.command.a.fg = c.bg.core
        custom_oasis.command.b.bg = c.bg.surface
        custom_oasis.command.b.fg = c.syntax.parameter
        custom_oasis.command.c.bg = c.bg.core
        custom_oasis.command.c.fg = c.syntax.parameter

        custom_oasis.visual.a.bg = c.syntax.special
        custom_oasis.visual.a.fg = c.bg.core
        custom_oasis.visual.b.bg = c.bg.surface
        custom_oasis.visual.b.fg = c.syntax.special
        custom_oasis.visual.c.bg = c.bg.core
        custom_oasis.visual.c.fg = c.syntax.special

        require("lualine").setup({
            options = {
                -- theme = custom_auto,
                -- theme = "auto",
                theme = custom_oasis,
                global_status = false,
                section_separators = "",
                component_separators = "",
            },
        })
    end
}


