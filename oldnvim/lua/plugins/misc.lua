return {
    {
        "catgoose/nvim-colorizer.lua",
        event = "BufReadPre",
        opts = {},
        config = function()
            require("colorizer").setup({})
        end
    },
    {
        "fladson/vim-kitty",
        ft = "kitty",
    },
    {
        "nvim-tree/nvim-web-devicons",
        config = function()
            require("nvim-web-devicons").setup()
        end
    -- },
    -- {
    --     "nvim-mini/mini.tabline",
    --     version = "*",
    --     config = function()
    --         require('mini.tabline').setup()
    --     end
    }
}
