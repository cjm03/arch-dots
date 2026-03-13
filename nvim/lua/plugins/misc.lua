return {
    {
        "catgoose/nvim-colorizer.lua",
        event = "BufReadPre",
        -- opts = {},
        config = function()
            require("colorizer").setup({
                user_default_options = { suppress_deprecation = true, }
            })
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
    },
    {
        "3rd/image.nvim",
        build = false,
        config = function()
            require('image').setup({
                backend = "kitty",
                processor = "magick_cli"
            })
        end
    },
    {
        "folke/which-key.nvim",
        event = "VeryLazy",
        opts = { preset = "helix", },
        keys = {},
    }
}
