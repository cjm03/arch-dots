return {
    "nvim-lualine/lualine.nvim",
    dependencies = {
        -- "nvim-mini/mini.icons",
        "nvim-tree/nvim-web-devicons"
    },
    config = function()
        require("lualine").setup({
            options = {
                theme = "ayu_dark",
                global_status = false,
                section_separators = '',
                component_separators = '',
            },
            sections = {
                lualine_a = {
                    {
                        'mode',
                        icon = {
                            '',
                            align='left',
                            color={fg='#000000', gui='bold'},
                        },
                    },
                },
            },
        })
    end
}
-- #0f1419 #36a3d9
-- #0f1419 #3498db
-- #0f1419 #2980b9
-- #e6e1cf #14191f
-- #3e4b59 #0f1419
-- #0a0c10
-- Ꙛλ𜲸𜱃
-- #0f1419 #b8cc52
-- #e6e1cf #14191f
-- 
-- #e6e1cf #14191f
-- #e6e1cf #14191f
-- #e6e1cf #0f1419
-- 
-- file:///home/crab/Downloads/icons8-vim-24.png
