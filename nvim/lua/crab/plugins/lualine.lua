return {
    "nvim-lualine/lualine.nvim",
    dependencies = { "echasnovski/mini.icons" },
    config = function()
        require("lualine").setup({
            options = {
                theme = "auto",
                -- theme = 'black-metal',
                global_status = false,
                section_separators = '',
                component_separators = '',
            },
        })
    end
}
