return {
    "nvim-lualine/lualine.nvim",
    dependencies = { "nvim-tree/nvim-web-devicons" },
    config = function()

        local custom_auto = require'lualine.themes.auto'

        custom_auto.normal.a.bg = '#0366d6'
        custom_auto.normal.a.gui = 'bold'

        custom_auto.insert.a.bg = '#ea8c2e'
        custom_auto.insert.a.gui = 'bold'
        custom_auto.insert.b.fg = '#ea8c2e'
        custom_auto.insert.c.fg = '#ea8c2e'

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


