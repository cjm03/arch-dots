return {
    "nvim-lualine/lualine.nvim",
    dependencies = { "echasnovski/mini.icons" },
    config = function()
        require("lualine").setup({
            options = {
                -- theme = "auto",
                theme = 'citruszest',
                global_status = false,
                section_separators = '',
                component_separators = '',
            },
        })
    end
}
